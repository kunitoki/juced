
// Copyright (c) 2007, Nils Jonas Norberg, See COPYING.txt for details

#define _USE_MATH_DEFINES
#include <math.h>

#include "shaper.h"
#include "voice.h"
#include "params.h"

#include "fastmath.inl"


#include <string.h>

ShaperSettings::ShaperSettings()
{
}

void ShaperSettings::fillParams( int i, Params* p )
{
	drive = 0.f;
	shape = 0.f;
	postgain = 1.f;
	mix = .8f;

	char tmp[256];

    snprintf(tmp,256,"SHAPER %d", i );
    p->AddLayoutDirective( Params::LAYOUT_HGROUP_BEGIN, tmp );

	snprintf(tmp,255,"S%dO|Shaper %d On",i,i);
	p->data.push_back(Params::Param( 8, 13, tmp,"on", &on , Params::Param::INTEGER ));

	snprintf(tmp,255,"S%dD|Shaper %d Drive",i,i);
	p->data.push_back(Params::Param( 8, 13, tmp,"drive", &drive ));

	snprintf(tmp,255,"S%dS|Shaper %d Shape",i,i);
	p->data.push_back(Params::Param( 8, 13, tmp,"shape", &shape, Params::Param::INTEGER, (SHAPE_COUNT-1.f)*.5f , (SHAPE_COUNT-1.f)*.5f ));
	p->data.back().SetEnums( "Soft|Hard|HF0|HF1|HF2|Sine|Rct|Bit|Clip" );

	snprintf(tmp,255,"S%dM|Shaper %d Mix",i,i);
	p->data.push_back(Params::Param( 8, 13, tmp,"mix", &mix ));

	snprintf(tmp,255,"S%dG|Shaper %d Gain",i,i);
	p->data.push_back(Params::Param( 8, 13, tmp,"", &postgain, Params::Param::POW2, 1.f, 4.f ));

    p->AddLayoutDirective( Params::LAYOUT_GROUP_END, "" );
}

ShaperInstance::ShaperInstance()
		:voice(0)
		,shaper(0)
{
	dl = dr = 0.f;
}

void ShaperInstance::noteOn( ShaperSettings* s, VoiceInstance* v, bool reset )
{
	voice = v;
	shaper = s;
    if ( reset )
    {
    	dl = dr = 0.f;
    }
}

void ShaperInstance::processReplace( float* audio, int count )
{
	if (shaper->on < .5f)
		return;

	float* out = audio;

	float a = 1.f + 15.f * shaper->drive;
	float b = shaper->mix * shaper->postgain;
	float c = (1.f - shaper->mix) * shaper->postgain;

	int shape_int = fast_ftol1023( shaper->shape + .5f );
	switch ( shape_int )
	{
	default:
		break;

	case ShaperSettings::SOFT:
		for ( ; count ; --count, out+=2 )
		{
			float l = out[0] * a;
			float r = out[1] * a;
			out[0] = c*l + b*l / (fabsf(l) + .7f);
			out[1] = c*r + b*r / (fabsf(r) + .7f);
		}
		break;

	case ShaperSettings::HARD:
		for ( ; count ; --count, out+=2 )
		{
			float l = out[0] * a;
			float r = out[1] * a;
			out[0] = c*l + b * (l*fabs(l) + l) / (l*l + 1.f);
			out[1] = c*r + b * (r*fabs(r) + r) / (r*r + 1.f);
		}
		break;

	case ShaperSettings::HF0:
		for ( ; count ; --count, out+=2 )
		{
			float l = out[0] * a;
			float r = out[1] * a;
			out[0] = c*l + b*l / (l*l + .7f);
			out[1] = c*r + b*r / (r*r + .7f);
		}
		break;

	case ShaperSettings::HF1:
		for ( ; count ; --count, out+=2 )
		{
			float l = out[0] * a;
			float r = out[1] * a;
			out[0] = c*l + b*(l-l*fabsf(l)) / (l*l + .6f);
			out[1] = c*r + b*(r-r*fabsf(r)) / (r*r + .6f);
		}
		break;

	case ShaperSettings::HF2:
		for ( ; count ; --count, out+=2 )
		{
			float l = out[0] * a;
			float r = out[1] * a;
			out[0] = c*l + b*(l-l*fabsf(l)) / (l*l*fabsf(l) + .6f);
			out[1] = c*r + b*(r-r*fabsf(r)) / (r*r*fabsf(r) + .6f);
		}
		break;

	case ShaperSettings::ADDSINE:
		{
			float amp = a /16.f;

			float x;
			float y;
			int &i = *(int*)&x;
			int &j = *(int*)&y;

			// weird bit-reducer...
			for ( ; count ; --count, out+=2 )
			{
#define BITS2KEEP 18
				x = out[0]; // x should be is in range [-8..8)
				x += 8 + 4.f; // will make range [8..16) hopefully that's enough headroom
				i &= ((1<<BITS2KEEP)-1); // keep 18bits
				i <<= (23-BITS2KEEP); // make mantissa
				i |= 0x40000000; // make [2..4)
				x -= 3.f; // make [-1..1)
				x = fabsf(x)*x - x;
				out[0] = c*out[0] + b * (out[0] + x * amp);

				y = out[1]; // x should be is in range [-8..8)
				y += 8 + 4.f; // will make range [8..16) hopefully that's enough headroom
				j &= ((1<<BITS2KEEP)-1); // keep 18bits
				j <<= (23-BITS2KEEP); // make mantissa
				j |= 0x40000000; // make [2..4)
				y -= 3.f; // make [-1..1)
				y = fabsf(y)*y - y;
				out[1] = c*out[1] + b * (out[1] + y * amp);
			}

		}
		break;

	case ShaperSettings::RECTIFY:
		{
			// needs highpass to remove dc...
			float f = a / 8.f;
			for ( ; count ; --count, out+=2 )
			{
				float l = b * fabsf( out[0] * f );
				float r = b * fabsf( out[1] * f );
				dl += (l-dl) * .001f;
				dr += (r-dr) * .001f;
				out[0] = c*out[0] +l - dl;
				out[1] = c*out[1] +r - dr;
			}
		}
		break;

	case ShaperSettings::BITCRUSH:
		{
			float f = 64.f / a;
			b *= a / 64.f;
			c *= a / 64.f;
			for ( ; count ; --count, out+=2 )
			{
				float l = out[0] * f;
				float r = out[1] * f;
				int li = fast_ftol1023( l + 512.f ) - 512;
				int ri = fast_ftol1023( r + 512.f ) - 512;
				out[0] = c*l + b*li;
				out[1] = c*r + b*ri;
			}
		}

	case ShaperSettings::DIGITAL:
		{
			b *= .5f;
			for ( ; count ; --count, out+=2 )
			{
				float l = out[0] * a;
				float r = out[1] * a;
				out[0] = c*l + b*fast_clamp_mul2( l , -.5f, .5f );
				out[1] = c*r + b*fast_clamp_mul2( r , -.5f, .5f );
			}
		}
		break;
	}
}
