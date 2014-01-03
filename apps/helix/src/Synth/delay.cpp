
// Copyright (c) 2007, Nils Jonas Norberg, See COPYING.txt for details

#include "delay.h"
#include "voice.h"
#include "synth.h"

#include "params.h"

#include "fastmath.inl"

#include <math.h>
#include <memory.h>

void DelaySettings::fillParams( Params* p )
{
    mode = 0;

	on = 0;
	timeL = .25f;
	timeR = .501f;

	feedback = .3f;

	lp = .7f;
	hp = .2f;

	mixKeyDown = .25f;
	mixKeyUp = .5f;

	char tmp[256];

    p->AddLayoutDirective( Params::LAYOUT_VGROUP_BEGIN, "" );
    p->AddLayoutDirective( Params::LAYOUT_LABEL, "On", 42, 17 );
    p->AddLayoutDirective( Params::LAYOUT_LABEL, "Mode", 42, 17 );
    p->AddLayoutDirective( Params::LAYOUT_LABEL, "Left", 42, 17 );
    p->AddLayoutDirective( Params::LAYOUT_LABEL, "Right", 42, 17 );
   	p->AddLayoutDirective( Params::LAYOUT_LABEL, "FB", 42, 17 );
    p->AddLayoutDirective( Params::LAYOUT_LABEL, "LP", 42, 17 );
   	p->AddLayoutDirective( Params::LAYOUT_LABEL, "HP", 42, 17 );
  	p->AddLayoutDirective( Params::LAYOUT_LABEL, "MixD", 42, 17 );
	p->AddLayoutDirective( Params::LAYOUT_LABEL, "MixU", 42, 17 );
    p->AddLayoutDirective( Params::LAYOUT_GROUP_END, "" );

    p->AddLayoutDirective( Params::LAYOUT_VGROUP_BEGIN, "" );
	snprintf(tmp,255,"DlyOn|Delay On");
	p->data.push_back(Params::Param( 17, 17, tmp,"on", &on , Params::Param::INTEGER ));

  	snprintf(tmp,255,"DlyM|Delay Mode");
	p->data.push_back(Params::Param( 17, 17, tmp,"mode", &mode , Params::Param::INTEGER, (ModeCount-1.f)*.5f, (ModeCount-1.f)*.5f) );
	p->data.back().SetEnums( "SX|LX|RX|S" );

	snprintf(tmp,255,"DlyTL|Delay Time Left");
	p->data.push_back(Params::Param( 17, 17, tmp,"s", &timeL ));

	snprintf(tmp,255,"DlyTR|Delay Time Right");
	p->data.push_back(Params::Param( 17, 17, tmp,"s", &timeR ));

	snprintf(tmp,255,"DlyFB|Delay Feedback");
	p->data.push_back(Params::Param( 17, 17, tmp,"fb", &feedback ));

	snprintf(tmp,255,"DlyLP|Delay LP");
	p->data.push_back(Params::Param( 17, 17, tmp,"lopass", &lp ));

	snprintf(tmp,255,"DlyHP|Delay HP");
	p->data.push_back(Params::Param( 17, 17, tmp,"highpass", &hp ));

	snprintf(tmp,255,"DlyMKD|Delay Mix Key Down");
	p->data.push_back(Params::Param( 17, 17, tmp,"mix", &mixKeyDown , Params::Param::POW2, .25f, 2.f ));

	snprintf(tmp,255,"DlyMKU|Delay Mix Key Up");
	p->data.push_back(Params::Param( 17, 17, tmp,"mix", &mixKeyUp , Params::Param::POW2, .25f, 2.f ));
    p->AddLayoutDirective( Params::LAYOUT_GROUP_END, "" );
}

void DelayInstance::reset( Synth* s, DelaySettings* del )
{
	synth = s;
	delay = del;

	mix = delay->mixKeyUp;

	memset(lbuffer,0,DLY_BUFSIZE * sizeof(float));
	memset(rbuffer,0,DLY_BUFSIZE * sizeof(float));

	runner = 0;

	llp = 0;
	rlp = 0;
	lhp = 0;
	rhp = 0;
}


inline int calc_run_len(int a, int b, int c, int limit)
{
	if (c>b)
		b=c;
	if(b>a)
		a=b;
	return limit - a;
}

void DelayInstance::processStereoCross(float* outlr, int count )
{
  	float mixTarget = synth->getKeysPressed() ? delay->mixKeyDown : delay->mixKeyUp;

	float sr = synth->getSampleRate();

	// get delaytime from settings
	int ltime = (int)(delay->timeL * sr);
	if ( ltime > DLY_BUFSIZE-1 )
		ltime = DLY_BUFSIZE-1;

	int rtime = (int)(delay->timeR * sr);
	if ( rtime > DLY_BUFSIZE-1 )
		rtime = DLY_BUFSIZE-1;

	float lp = FreqToCoef( delay->lp * 22000.f / sr );
	float hp = FreqToCoef( delay->hp * 3000.f / sr );

    while (count)
	{
		// who can run the shortest?
		int lpos = runner-ltime;
		if (lpos<0)
			lpos+=DLY_BUFSIZE;
		int rpos = runner-rtime;
		if (rpos<0)
			rpos+=DLY_BUFSIZE;

		int tempcount = calc_run_len(runner,lpos,rpos, DLY_BUFSIZE);

		if (count < tempcount)
			tempcount = count;

		float* lrun_write = lbuffer + runner;
		float* rrun_write = rbuffer + runner;
		float* lrun = lbuffer + lpos;
		float* rrun = rbuffer + rpos;

		count -= tempcount;
		runner += tempcount;
		if (runner == DLY_BUFSIZE)
			runner = 0;

        static const float normalThresh = 1e-15f;

        // clamp small values to 0
        if ( fabsf( llp ) < normalThresh ) llp = 0.f;
        if ( fabsf( rlp ) < normalThresh ) rlp = 0.f;
        if ( fabsf( lhp ) < normalThresh ) lhp = 0.f;
        if ( fabsf( rhp ) < normalThresh ) rhp = 0.f;

        // FIXME!!! unroll
		for ( ; tempcount ; --tempcount, ++lrun_write, ++rrun_write, ++lrun, ++rrun, outlr+=2 )
		{
			// get damped result from buffer
			llp += (*lrun - llp) * lp;
			rlp += (*rrun - rlp) * lp;

			lhp += (llp - lhp) * hp;
			rhp += (rlp - rhp) * hp;

			float rin = (rlp-rhp);
			float lin = (llp-lhp);

			// write internal (ping pong) (feedback)
			*lrun_write = outlr[0] - rin * delay->feedback;
			*rrun_write = outlr[1] - lin * delay->feedback;

			mix += (mixTarget-mix) * .01f;

			// write outs (mix)
			outlr[0] += lin * mix;
			outlr[1] += rin * mix;

		}
	}
}

void DelayInstance::processLeftCross(float* outlr, int count )
{
  	float mixTarget = synth->getKeysPressed() ? delay->mixKeyDown : delay->mixKeyUp;

	float sr = synth->getSampleRate();

	// get delaytime from settings
	int ltime = (int)(delay->timeL * sr);
	if ( ltime > DLY_BUFSIZE-1 )
		ltime = DLY_BUFSIZE-1;

	int rtime = (int)(delay->timeR * sr);
	if ( rtime > DLY_BUFSIZE-1 )
		rtime = DLY_BUFSIZE-1;

	float lp = FreqToCoef( delay->lp * 22000.f / sr );
	float hp = FreqToCoef( delay->hp * 3000.f / sr );

    while (count)
	{
		// who can run the shortest?
		int lpos = runner-ltime;
		if (lpos<0)
			lpos+=DLY_BUFSIZE;
		int rpos = runner-rtime;
		if (rpos<0)
			rpos+=DLY_BUFSIZE;

		int tempcount = calc_run_len(runner,lpos,rpos, DLY_BUFSIZE);

		if (count < tempcount)
			tempcount = count;

		float* lrun_write = lbuffer + runner;
		float* rrun_write = rbuffer + runner;
		float* lrun = lbuffer + lpos;
		float* rrun = rbuffer + rpos;

		count -= tempcount;
		runner += tempcount;
		if (runner == DLY_BUFSIZE)
			runner = 0;

        static const float normalThresh = 1e-15f;

        // clamp small values to 0
        if ( fabsf( llp ) < normalThresh ) llp = 0.f;
        if ( fabsf( rlp ) < normalThresh ) rlp = 0.f;
        if ( fabsf( lhp ) < normalThresh ) lhp = 0.f;
        if ( fabsf( rhp ) < normalThresh ) rhp = 0.f;

        // FIXME!!! unroll
		for ( ; tempcount ; --tempcount, ++lrun_write, ++rrun_write, ++lrun, ++rrun, outlr+=2 )
		{
			// get damped result from buffer
			llp += (*lrun - llp) * lp;
			lhp += (llp - lhp) * hp;

			float rin = *rrun;;
			float lin = (llp-lhp);

			// write internal (ping pong) (feedback)
			*lrun_write = ( outlr[0] + outlr[1] ) * .5f - rin * delay->feedback;
			*rrun_write = lin;

			mix += (mixTarget-mix) * .01f;

			// write outs (mix)
			outlr[0] += lin * mix;
			outlr[1] += rin * mix;

		}
	}

}

void DelayInstance::processRightCross(float* outlr, int count )
{
  	float mixTarget = synth->getKeysPressed() ? delay->mixKeyDown : delay->mixKeyUp;

	float sr = synth->getSampleRate();

	// get delaytime from settings
	int ltime = (int)(delay->timeL * sr);
	if ( ltime > DLY_BUFSIZE-1 )
		ltime = DLY_BUFSIZE-1;

	int rtime = (int)(delay->timeR * sr);
	if ( rtime > DLY_BUFSIZE-1 )
		rtime = DLY_BUFSIZE-1;

	float lp = FreqToCoef( delay->lp * 22000.f / sr );
	float hp = FreqToCoef( delay->hp * 3000.f / sr );

    while (count)
	{
		// who can run the shortest?
		int lpos = runner-ltime;
		if (lpos<0)
			lpos+=DLY_BUFSIZE;
		int rpos = runner-rtime;
		if (rpos<0)
			rpos+=DLY_BUFSIZE;

		int tempcount = calc_run_len(runner,lpos,rpos, DLY_BUFSIZE);

		if (count < tempcount)
			tempcount = count;

		float* lrun_write = lbuffer + runner;
		float* rrun_write = rbuffer + runner;
		float* lrun = lbuffer + lpos;
		float* rrun = rbuffer + rpos;

		count -= tempcount;
		runner += tempcount;
		if (runner == DLY_BUFSIZE)
			runner = 0;

        static const float normalThresh = 1e-15f;

        // clamp small values to 0
        if ( fabsf( llp ) < normalThresh ) llp = 0.f;
        if ( fabsf( rlp ) < normalThresh ) rlp = 0.f;
        if ( fabsf( lhp ) < normalThresh ) lhp = 0.f;
        if ( fabsf( rhp ) < normalThresh ) rhp = 0.f;

        // FIXME!!! unroll
		for ( ; tempcount ; --tempcount, ++lrun_write, ++rrun_write, ++lrun, ++rrun, outlr+=2 )
		{
			// get damped result from buffer
			rlp += (*rrun - rlp) * lp;
			rhp += (rlp - rhp) * hp;

			float rin = (rlp-rhp);
			float lin = *lrun;

			// write internal (ping pong) (feedback)
			*lrun_write = rin;
			*rrun_write = ( outlr[0] + outlr[1] ) * .5f - lin * delay->feedback;

			mix += (mixTarget-mix) * .01f;

			// write outs (mix)
			outlr[0] += lin * mix;
			outlr[1] += rin * mix;

		}
	}
}

void DelayInstance::processStereo(float* outlr, int count )
{
  	float mixTarget = synth->getKeysPressed() ? delay->mixKeyDown : delay->mixKeyUp;

	float sr = synth->getSampleRate();

	// get delaytime from settings
	int ltime = (int)(delay->timeL * sr);
	if ( ltime > DLY_BUFSIZE-1 )
		ltime = DLY_BUFSIZE-1;

	int rtime = (int)(delay->timeR * sr);
	if ( rtime > DLY_BUFSIZE-1 )
		rtime = DLY_BUFSIZE-1;

	float lp = FreqToCoef( delay->lp * 22000.f / sr );
	float hp = FreqToCoef( delay->hp * 3000.f / sr );

    while (count)
	{
		// who can run the shortest?
		int lpos = runner-ltime;
		if (lpos<0)
			lpos+=DLY_BUFSIZE;
		int rpos = runner-rtime;
		if (rpos<0)
			rpos+=DLY_BUFSIZE;

		int tempcount = calc_run_len(runner,lpos,rpos, DLY_BUFSIZE);

		if (count < tempcount)
			tempcount = count;

		float* lrun_write = lbuffer + runner;
		float* rrun_write = rbuffer + runner;
		float* lrun = lbuffer + lpos;
		float* rrun = rbuffer + rpos;

		count -= tempcount;
		runner += tempcount;
		if (runner == DLY_BUFSIZE)
			runner = 0;

        static const float normalThresh = 1e-15f;

        // clamp small values to 0
        if ( fabsf( llp ) < normalThresh ) llp = 0.f;
        if ( fabsf( rlp ) < normalThresh ) rlp = 0.f;
        if ( fabsf( lhp ) < normalThresh ) lhp = 0.f;
        if ( fabsf( rhp ) < normalThresh ) rhp = 0.f;

        // FIXME!!! unroll
		for ( ; tempcount ; --tempcount, ++lrun_write, ++rrun_write, ++lrun, ++rrun, outlr+=2 )
		{
			// get damped result from buffer
			llp += (*lrun - llp) * lp;
			rlp += (*rrun - rlp) * lp;

			lhp += (llp - lhp) * hp;
			rhp += (rlp - rhp) * hp;

			float rin = (rlp-rhp);
			float lin = (llp-lhp);

			// write internal (ping pong) (feedback)
			*lrun_write = outlr[0] - lin * delay->feedback;
			*rrun_write = outlr[1] - rin * delay->feedback;

			mix += (mixTarget-mix) * .01f;

			// write outs (mix)
			outlr[0] += lin * mix;
			outlr[1] += rin * mix;

		}
	}
}

void DelayInstance::processReplace(float* outlr, int count )
{
	if (delay->on < .5f)
		return;

    DelaySettings::Mode imode = (DelaySettings::Mode)fast_ftol1023( delay->mode + .5f );
    switch( imode )
    {
        case DelaySettings::StereoCross: processStereoCross( outlr, count ); break;
        case DelaySettings::LeftCross: processLeftCross( outlr, count ); break;
        case DelaySettings::RightCross: processRightCross( outlr, count ); break;
        case DelaySettings::Stereo: processStereo( outlr, count ); break;
        case DelaySettings::ModeCount: break;
    }
}
