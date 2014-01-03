
// Copyright (c) 2007, Nils Jonas Norberg, See COPYING.txt for details

#include "lfo.h"
#include "params.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "synth.h"

#include "fastmath.inl"

// FIXME!!! sync to host!!!

// FIXME!!! add waveforms
void LFOSettings::fillParams( int i, Params* p )
{
	form = 0;
	phase = 0;
	period = .1666666f;

	hold = .0f;
	attack = .125f;
	release = 1.5f;

	char tmp[256];

    if ( i == 0 )
    {
        p->AddLayoutDirective( Params::LAYOUT_VGROUP_BEGIN, "" );

        p->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, "", 42, 17 );

        p->AddLayoutDirective( Params::LAYOUT_LABEL, "Form", 42, 17 );
        p->AddLayoutDirective( Params::LAYOUT_LABEL, "Ohase", 42, 17 );
        p->AddLayoutDirective( Params::LAYOUT_LABEL, "Period", 42, 17 );
   	    p->AddLayoutDirective( Params::LAYOUT_LABEL, "Hold", 42, 17 );
        p->AddLayoutDirective( Params::LAYOUT_LABEL, "Attack", 42, 17 );
   	    p->AddLayoutDirective( Params::LAYOUT_LABEL, "Release", 42, 17 );

        p->AddLayoutDirective( Params::LAYOUT_GROUP_END, "" );
    }

    p->AddLayoutDirective( Params::LAYOUT_VGROUP_BEGIN, "" );

    if ( i == 100 )
    {
       p->AddLayoutDirective( Params::LAYOUT_LABEL, "G", 17, 17 );
    }
    else
    {
    	snprintf(tmp,256,"%d",i);
        p->AddLayoutDirective( Params::LAYOUT_LABEL, tmp, 17, 17 );
    }

	snprintf(tmp,255,"LF%dF|Low Frequency Oscillator %d Form",i,i);
	p->data.push_back(Params::Param( 17, 17, tmp,"form", &form, Params::Param::INTEGER, (FORM_COUNT-1.f)*.5f, (FORM_COUNT-1.f)*.5f));
    p->data.back().SetEnums( "S|R|#1|#2" );

	snprintf(tmp,255,"LF%dPH|Low Frequency Oscillator %d Phase",i,i);
	p->data.push_back(Params::Param( 17, 17, tmp,"",&phase ));

	snprintf(tmp,255,"LF%dPRD|Low Frequency Oscillator %d Period",i,i);
	p->data.push_back(Params::Param( 17, 17, tmp,"",&period, Params::Param::POW2, .2f, 4.f  ));

	snprintf(tmp,255,"LF%dHT|Low Frequency Oscillator %d Hold Time",i,i);
	p->data.push_back(Params::Param( 17, 17, tmp,"s",&hold, Params::Param::LINJ, 2.f, 2.f ));

	snprintf(tmp,255,"LF%dAT|Low Frequency Oscillator %d Attack Time",i,i);
	p->data.push_back(Params::Param( 17, 17, tmp,"s",&attack, Params::Param::POW2, .1f, 4.f ));

	snprintf(tmp,255,"LF%dRT|Low Frequency Oscillator %d Release Time",i,i);
	p->data.push_back(Params::Param( 17, 17, tmp,"s",&release, Params::Param::POW2, .3f, 4.f ));

    p->AddLayoutDirective( Params::LAYOUT_GROUP_END, "" );
}

void LFOInstance::noteOff()
{
	har_state = RELEASE;
}

void LFOInstance::noteOn(const LFOSettings* in_lfo, const Synth* s )
{
	float cr = s->getSampleRate() / ACSCALE;

	lfo = in_lfo;
	phase = (u32)(lfo->phase * 4294967296.f);

	int form = fast_ftol1023( lfo->form + .5f );
	switch ( form )
	{
	case LFOSettings::RND:
		add = (u32)(((4294967296.f / VALUES) / (cr * lfo->period)) );
		break;
	case LFOSettings::SIN:
	case LFOSettings::SQR1:
	case LFOSettings::SQR2:
		add = (u32)((4294967296.f / (cr * lfo->period)) );
		break;
	}


	har_state = HOLD;
	hold_smps = (int)(lfo->hold * cr );
	amp = 0.f;

	att_blend = 1.f - powf( .5f, 1.f / (lfo->attack * cr) );
	if (att_blend > .077f)
		att_blend = 1.f;

	rel_blend = 1.f - powf( .5f, 1.f / (lfo->release * cr) );

	smps_in_state = 0;

	for (int i = 0 ; i != VALUES ; ++i )
		values[i] = frand( 1.f );
}

void LFOInstance::clearValues()
{
	int pos = phase >> (32-VALUESBITS);
	int pos2 = (pos + 1) & VALUESMASK;

	for (int i = 0 ; i != VALUES ; ++i )
	{
		if (i != pos && i != pos2)
			values[i] = frand( 1.f );
	}
}

void LFOInstance::processReplace(float* out, int count)
{
	int form = fast_ftol1023( lfo->form + .5f );
	switch ( form )
	{
	case LFOSettings::SIN:	processReplaceSin(out, count); break;
	case LFOSettings::RND:	processReplaceRnd(out, count); break;
	case LFOSettings::SQR1:	processReplaceSqr1(out, count); break;
	case LFOSettings::SQR2:	processReplaceSqr2(out, count); break;
	}
}

void LFOInstance::processReplaceSin(float* out, int count)
{
	float target = 0;
	float blendspeed = 0;

	while (count)
	{
		int tempcount = count;

		switch ( har_state )
		{
		case HOLD:
			{
				int smps_left = hold_smps - smps_in_state;
				if (tempcount >= smps_left)
				{
					tempcount = smps_left;
					har_state = ATTACK;
				}
			}
			break;

		case ATTACK:
			target = 1.f;
			blendspeed = att_blend;
			break;

		case RELEASE:
			target = 0.f;
			blendspeed = rel_blend;
			break;
		}

		count -= tempcount;
		smps_in_state += tempcount;

		for ( ; tempcount ; --tempcount, ++out )
		{
			phase += add;
			amp += (target - amp) * blendspeed;
			*out = amp * fake_sin2( fast_bipolar(phase) );
		}
	}
}

void LFOInstance::processReplaceRnd(float* out, int count)
{
	float target = 0;
	float blendspeed = 0;

	while (count)
	{
		clearValues();
		int tempcount = count;

		int phase_left = (~phase / add);
		if (phase_left > 2 && phase_left < tempcount)
			tempcount = phase_left;

		switch ( har_state )
		{
		case HOLD:
			{
				int smps_left = hold_smps - smps_in_state;
				if (tempcount >= smps_left)
				{
					tempcount = smps_left;
					har_state = ATTACK;
				}
			}
			break;

		case ATTACK:
			target = 1.f;
			blendspeed = att_blend;
			break;

		case RELEASE:
			target = 0.f;
			blendspeed = rel_blend;
			break;
		}

		count -= tempcount;
		smps_in_state += tempcount;

		for ( ; tempcount ; --tempcount, ++out )
		{
			phase += add;
			amp += (target - amp) * blendspeed;
			int pos = phase >> (32-VALUESBITS);
			float prevv = values[ pos ];
			float nextv = values[ (pos + 1) & VALUESMASK ];
			float v = prevv + ( nextv - prevv ) * smooth( fast_phase2float(phase << VALUESBITS ) );

			*out = amp * v;
		}
	}
}

void LFOInstance::processReplaceSqr1(float* out, int count)
{
	float target = 0;
	float blendspeed = 0;

	while (count)
	{
		int tempcount = count;

		switch ( har_state )
		{
		case HOLD:
			{
				int smps_left = hold_smps - smps_in_state;
				if (tempcount >= smps_left)
				{
					tempcount = smps_left;
					har_state = ATTACK;
				}
			}
			break;

		case ATTACK:
			target = 1.f;
			blendspeed = att_blend;
			break;

		case RELEASE:
			target = 0.f;
			blendspeed = rel_blend;
			break;
		}

		count -= tempcount;
		smps_in_state += tempcount;

		for ( ; tempcount ; --tempcount, ++out )
		{
			phase += add;
			amp += (target - amp) * blendspeed;
			float val = (phase < 0x80000000) ? 1.f : -1.f; // FIXME!!! faster than conditional
			*out = amp * val;
		}
	}
}

void LFOInstance::processReplaceSqr2(float* out, int count)
{
	float target = 0;
	float blendspeed = 0;

	while (count)
	{
		int tempcount = count;

		switch ( har_state )
		{
		case HOLD:
			{
				int smps_left = hold_smps - smps_in_state;
				if (tempcount >= smps_left)
				{
					tempcount = smps_left;
					har_state = ATTACK;
				}
			}
			break;

		case ATTACK:
			target = 1.f;
			blendspeed = att_blend;
			break;

		case RELEASE:
			target = 0.f;
			blendspeed = rel_blend;
			break;
		}

		count -= tempcount;
		smps_in_state += tempcount;

		for ( ; tempcount ; --tempcount, ++out )
		{
			phase += add;
			amp += (target - amp) * blendspeed;
			float val = (phase < 0x80000000) ?1.f : 0.f; // FIXME!!! faster than conditional
			*out = amp * val;
		}
	}
}


