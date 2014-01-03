
// Copyright (c) 2007, Nils Jonas Norberg, See COPYING.txt for details

#include "kbd.h"
#include "params.h"
#include "voice.h"
#include "synth.h"

#include "fastmath.inl"

#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <float.h>

// FIXME!!! use "current" float-note and not last destination-note

KBDSettings::KBDSettings()
{
	on = 0.f;
	glide = .00005f;
	reset_on_first = 1.f;
	glide_mode = EXP;
}

void KBDSettings::fillParams( int i, Params* p )
{
	char tmp[256];

   	snprintf(tmp,256,"KBD %d",i );
    p->AddLayoutDirective( Params::LAYOUT_HGROUP_BEGIN, tmp );

	snprintf(tmp,255,"Kbd%dOn|Keyboard %d On",i,i);
	p->data.push_back(Params::Param( 8, 13, tmp,"on", &on, Params::Param::INTEGER ));

	snprintf(tmp,255,"Kbd%dM|Keyboard %d Mode",i,i);
	p->data.push_back(Params::Param( 8, 13, tmp,"",&glide_mode, Params::Param::INTEGER, (MODE_COUNT-1.f) * .5f, (MODE_COUNT-1.f) * .5f ));
	p->data.back().SetEnums("EXP|C.TIME|C.SPEED");

	snprintf(tmp,255,"Kbd%dG|Keyboard %d Glide",i,i);
	p->data.push_back(Params::Param( 8, 13, tmp,"",&glide, Params::Param::POW2, .05f, 2.8f ));

	snprintf(tmp,255,"Kbd%dR|Keyboard %d Reset",i,i);
	p->data.push_back(Params::Param( 8, 13, tmp,"",&reset_on_first, Params::Param::INTEGER, .5f, .5f ));

	snprintf(tmp,255,"Kbd%dVS|Keyboard %d Velocity Sensitivity",i,i);
	p->data.push_back(Params::Param( 8, 13, tmp,"", &vel_sens ) );

    p->AddLayoutDirective( Params::LAYOUT_GROUP_END, "" );
}

void KBDInstance::noteOn(float target, float vel , const KBDSettings* in_KBD, const VoiceInstance* v, bool use_current_freq )
{
	voice = v;
	kbd = in_KBD;

	int mode = fast_ftol1023(kbd->glide_mode + .5f );

	// FIXME!!! don't see the last "destination" see where the freq actually is...
    if ( !use_current_freq )
        value = v->settings->synth->getLastPitch();

    target_value = target;

	frame_count = 0;

	float glide_time = kbd->glide * powf( 2.f, (.5f - vel) * 6.f * kbd->vel_sens );

	if ((0 == v->settings->synth->getKeysPressed()) && (kbd->reset_on_first > .5f))
	{
		// no glide if no note pressed
		value = target_value;
		blend = 1.f;
	}
	else
	{
		float samples = glide_time * v->settings->synth->getSampleRate() / ACSCALE;
		if (samples < 1 )
			samples = 1;

		switch ( mode )
		{
		case KBDSettings::EXP:
			{
			blend = 1.f - powf( .5f, 1.f / samples );
			}
			break;

		case KBDSettings::CONST_TIME:
			{
				samples *= 4.f; // to be comparable with halflife
				// blend == speed
				float note_diff = target_value - value;
				blend = note_diff / samples;
			}
			break;

		case KBDSettings::CONST_SPEED:
			{
				samples *= 4.f; // to be comparable with halflife
				// blend == speed
				float note_diff = target_value - value;
				blend = (7.f / 127.f) / samples;
				if(note_diff < 0)
					blend = -blend;
			}
			break;
		}
	}

	original_target_value = target_value;
}

float KBDInstance::getOriginalKey()
{
	return original_target_value;
}

void KBDInstance::processReplace(float* out, int count)
{
	int mode = fast_ftol1023(kbd->glide_mode + .5f );

	while (count)
	{
		// first test if pure fill
		if (
			(kbd->on < .5f) ||
			(fabsf(value-target_value) < FLT_EPSILON )
			)
		{
			value = target_value;

			for ( ; count > 7 ; count -= 8, out += 8)
			{
				out[0] = value;
				out[1] = value;
				out[2] = value;
				out[3] = value;
				out[4] = value;
				out[5] = value;
				out[6] = value;
				out[7] = value;
			}

			for ( ; count ; --count, ++out)
				*out = value;

			return;
		}

		// nope, still gliding
		switch ( mode )
		{
		case KBDSettings::EXP:
			{
				for ( ; count ; --count, ++out)
				{
					value += (target_value - value) * blend;
					out[0] = value;
				}
			}
			break;

		case KBDSettings::CONST_TIME:
		case KBDSettings::CONST_SPEED:
			{
				int temp_count = (int)(fabsf(target_value - value) / fabsf(blend));
				if (temp_count < 1)
 				{
					value = target_value;
				}
				else
				{
					if ( count < temp_count )
						temp_count = count;

					count-= temp_count;
					for ( ; temp_count ; --temp_count, ++out)
					{
						value += blend;
						out[0] = value;
					}
				}
			}
			break;
		}
	}
}
