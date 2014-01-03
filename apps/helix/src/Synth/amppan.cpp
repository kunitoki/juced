
// Copyright (c) 2007, Nils Jonas Norberg, See COPYING.txt for details

#define _USE_MATH_DEFINES
#include <math.h>

#include "amppan.h"
#include "voice.h"
#include "params.h"

#include <string.h>

AmpPanSettings::AmpPanSettings()
{
}

void AmpPanSettings::fillParams( Params* p )
{
	amp = .25f;

	char tmp[256];

    p->AddLayoutDirective( Params::LAYOUT_HGROUP_BEGIN, "" );
    p->AddLayoutDirective( Params::LAYOUT_LABEL, "Ampl", 42, 17 );

    snprintf(tmp,256,"VA|Voice Amplitude");
	p->data.push_back(Params::Param(32, 32, tmp,"", &amp, Params::Param::POW2, .25f, 3.f ));

    p->AddLayoutDirective( Params::LAYOUT_GROUP_END, "" );
}

AmpPanInstance::AmpPanInstance()
{
    voice = 0;
    amppan = 0;
   	amp = 0;
	firstframe = true;
}

void AmpPanInstance::noteOn( AmpPanSettings* f, VoiceInstance* v, bool reset)
{
	voice = v;
	amppan = f;
    if ( reset )
    {
    	firstframe = true;
        amp = 0;
    }
}

void AmpPanInstance::processReplace(float* lr, float* src, int count)
{
	float* in = src;
	float* ctrl = voice->settings->modsrc_voice; // hardcoded to first EG

	float amp_add;

	if (firstframe)
	{
		amp = *ctrl * amppan->amp;
		firstframe = false;
	}

	while ( count )
	{
		int tempcount = count;
		if (tempcount > ACSCALE)
			tempcount = ACSCALE;

		count -= tempcount;

		amp_add = (*ctrl * amppan->amp - amp) / (float)ACSCALE;
		++ctrl;

		// should unroll like there's no tomorrow
		for ( ; tempcount ; --tempcount, lr+=2, in+=2, amp+=amp_add )
		{
			lr[0] += in[0] * amp;
			lr[1] += in[1] * amp;
		}

	}
}
