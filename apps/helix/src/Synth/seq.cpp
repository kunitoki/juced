
// Copyright (c) 2007, Nils Jonas Norberg, See COPYING.txt for details

#include "seq.h"
#include "params.h"
#include "voice.h"
#include "synth.h"

#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <float.h>

#include "fastmath.inl"

// FIXME!!! sync to host!!!


SEQSettings::SEQSettings()
{
}

void SEQSettings::fillParams( int i, Params* p )
{
    loopBegin = 0;
    loopEnd = 16;

    for (int j = 0 ; j != STEP_COUNT ; ++j )
		steps[j] = sinf( (float)j * 3.14159265358979323846f * 2.f / (float)STEP_COUNT );

	char tmp[256];
   	snprintf(tmp,256,"Seq %d",i );
    p->AddLayoutDirective( Params::LAYOUT_HGROUP_BEGIN, tmp );

   	snprintf(tmp,256,"SQ%dP|Sequencer %d Period",i,i);
	p->data.push_back(Params::Param( 8, 13, tmp,"",&period, Params::Param::POW2, .2f, 4.f  ));

	//float swing;

	snprintf(tmp,256,"SQ%dLAG|Sequencer %d Lag",i,i); // percentage of period
	p->data.push_back(Params::Param( 8, 13, tmp,"",&lagging, Params::Param::POW2, .05f, 5.f  ));

  	snprintf(tmp,256,"SQ%dLB|Sequencer %d Loop Begin",i,i);
	p->data.push_back(Params::Param( 8, 13, tmp,"",&loopBegin, Params::Param::INTEGER, STEP_COUNT*.5f - 1.f, STEP_MASK*.5f ));
	p->data.back().SetEnums( "0|1|2|3|4|5|6|7|8|9|A|B|C|D|E|F" );

  	snprintf(tmp,256,"SQ%dLE|Sequencer %d Loop End",i,i);
	p->data.push_back(Params::Param( 8, 13, tmp,"",&loopEnd, Params::Param::INTEGER, STEP_COUNT*.5f - 1.f, STEP_MASK*.5f ));
	p->data.back().SetEnums( "0|1|2|3|4|5|6|7|8|9|A|B|C|D|E|F" );

    p->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, "", 4, 8 );

    for (int j = 0 ; j != STEP_COUNT ; ++j )
	{
		snprintf(tmp,256,"SQ%d%X|Sequencer %d Step %X",i,j,i,j);
		p->data.push_back(Params::Param(8, 13, tmp,"",steps+j, Params::Param::LINJ, 0.f, 1.f ));
	}

    p->AddLayoutDirective( Params::LAYOUT_GROUP_END, "" );
}

void SEQInstance::noteOn(const SEQSettings* in_SEQ, const Synth* s)
{
	synth = s;
	seq = in_SEQ;
	samples_left_on_step = 0;
	currstep = SEQSettings::STEP_COUNT - 1;
	currval = 0;
	float samples = seq->lagging * seq->period * synth->getSampleRate() / ACSCALE;
	blendval = 1.f - powf(.5f, 1.f / samples );
}

void SEQInstance::processReplace(float* out, int count)
{
    int iLoopBegin = fast_ftol1023( seq->loopBegin + .5f );
    int iLoopEnd = fast_ftol1023( seq->loopEnd + 1.5f );

    float target = seq->steps[currstep];

	while (count)
	{
		int tempcount = count;
		if (tempcount > samples_left_on_step)
			tempcount = samples_left_on_step;

		count -= tempcount;
		samples_left_on_step -= tempcount;

		if (samples_left_on_step == 0)
		{
			++currstep;
            if (currstep >= iLoopEnd )
                currstep = iLoopBegin;

            currstep &= SEQSettings::STEP_MASK;
			target = seq->steps[currstep];
			samples_left_on_step = (u32)(seq->period * synth->getSampleRate() / ACSCALE);
		}

		for ( ; tempcount ; --tempcount, ++out )
		{
			currval += (target-currval) * blendval;
			*out = currval;
		}
	}
}
