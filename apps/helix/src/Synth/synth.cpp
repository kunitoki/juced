
// Copyright (c) 2007, Nils Jonas Norberg, See COPYING.txt for details

#include "synth.h"
#include "params.h"
#include "fastmath.inl"

#include <memory.h>
#include <math.h>

// #include <windows.h>


////////////////////////////////////////////////////////////////////////



// JUST TUNING
#include <vector>
#include <algorithm>
#include <math.h>

#include <stdio.h>

double f2o( double freqRatio )
{
	return log( freqRatio ) / log( 2. );
}

// this algo needs a lot of work
// it should only be applied if we recignize a chord and we need to establish the root key
class justTuner
{
public:
	justTuner()
	{
		for ( int oct = 1 ; oct != 8 ; ++oct )
		{
			just_ratios_.push_back( f2o( oct * 1. ));
			just_ratios_.push_back( f2o( oct * 3./2. ));
			just_ratios_.push_back( f2o( oct * 4./3. ));
			just_ratios_.push_back( f2o( oct * 5./3. ));
			just_ratios_.push_back( f2o( oct * 5./4. ));
			just_ratios_.push_back( f2o( oct * 6./5. ));
			just_ratios_.push_back( f2o( oct * 8./5. ));
			just_ratios_.push_back( f2o( oct * 9./5. ));
			just_ratios_.push_back( f2o( oct * 9./8. ));
			//           just_ratios_.push_back( f2o( oct * 15./8. ));
			//           just_ratios_.push_back( f2o( oct * 25./24. ));
			//           just_ratios_.push_back( f2o( oct * 45./32. ));
		}

		// sort the vector
		std::sort(just_ratios_.begin(), just_ratios_.end());
	}

	double getJust( double oct ) const
	{
		std::vector<double>::const_iterator it =
			std::upper_bound(just_ratios_.begin(), just_ratios_.end(), oct );
		if (it == just_ratios_.end())
			return oct;

		double hiv = *it;
		double hid = hiv - oct;

		if (it != just_ratios_.begin())
		{
			--it;
			// test against higher value
			double lov = *it;
			double lod = oct - lov;
			if (lod < hid)
			{
				hiv = lov;
				hid = lod;
			}
		}

		// far away (.4 half-notes)
		if (hid > .4/12. )
			return oct;
		return hiv;
	}

	// related notes...
	void reTuneChord(  double* chord_begin, const double* chord_end , double ratio )
	{
		// 1. find min
		double* it = chord_begin;
		double minOct = 1000000.;
		for ( ; it != chord_end ; ++it )
		{
			if (*it < minOct)
				minOct = *it;
		}

		// 2. shift everything down to make min 0
		it = chord_begin;
		for ( ; it != chord_end ; ++it )
		{
			*it -= minOct;
		}


		double totalShift = 0;
		// 3 tune all
		it = chord_begin;
		for ( ; it != chord_end ; ++it )
		{
			double newOct = *it + ratio * (getJust( *it ) - *it);
			totalShift += newOct - *it;
			*it = newOct;
		}

		totalShift /= (chord_end - chord_begin);

		// 4. adjust to get close to temperament
		it = chord_begin;
		for ( ; it != chord_end ; ++it )
		{
			*it -= totalShift;
		}

		// 5. shift everything back up
		it = chord_begin;
		for ( ; it != chord_end ; ++it )
		{
			*it += minOct;
		}
	}

	// will divide into smaller groups (ie bass + chord)
	void reTuneAll( double* chord_begin, double* chord_end, double ratio )
	{
		// 1. divide into groups
		// 2. tune them separately...

		// for now retune as one chord
		reTuneChord( chord_begin, chord_end, ratio );
	}

private:
	std::vector<double> just_ratios_;
};

//justTuner gTuner;


////////////////////////////////////////////////////////////////////////

bool ModMatrixDestIsFrequency( u32 i )
{
	if ( i >= MODOSCDST_VOICE_COUNT*OSC_PER_VOICE )
	{
		return true;
	}

	i %= MODOSCDST_VOICE_COUNT;

	switch( i )
	{
	case MODOSCDST_VOICE_HARM:
	case MODOSCDST_VOICE_PITCH:
		return true;
	}


	return false;
}

void Synth::FillParams()
{
    // VOICE is moved here so we can get creative...
  	char tmp[256];

    params->AddLayoutDirective( Params::LAYOUT_VGROUP_BEGIN, ""  );
    params->AddLayoutDirective( Params::LAYOUT_LABEL, "OSC", 110, 13 );

    params->AddLayoutDirective( Params::LAYOUT_HGROUP_BEGIN, ""  );
	// params osc
	for(int i = 0; i != OSC_PER_VOICE ; ++i )
    {
        voices.oscs[i].fillParams( i, params );
    }

    params->AddLayoutDirective( Params::LAYOUT_GROUP_END, ""  );
    params->AddLayoutDirective( Params::LAYOUT_GROUP_END, ""  );

    // space btw. params and waves...
    params->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, "", 16, 16 );


    params->AddLayoutDirective( Params::LAYOUT_VGROUP_BEGIN, ""  );
    params->AddLayoutDirective( Params::LAYOUT_LABEL, "OSC PREV.", 84, 13 );
   	for(int i = 0; i != OSC_PER_VOICE ; ++i )
    {
        if ( i != 0)
            params->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, "", 8,8 );

        params->AddLayoutDirective( Params::LAYOUT_HGROUP_BEGIN, ""  );

        snprintf(tmp,255,"O%dWaveDisplay0",i);
        params->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, tmp, 41, 21 );

        params->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, "", 1,1 );

        snprintf(tmp,255,"O%dWaveDisplay1",i);
        params->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, tmp, 41, 21 );

        params->AddLayoutDirective( Params::LAYOUT_GROUP_END, ""  );

        snprintf(tmp,255,"O%dWaveDisplay2",i);
        params->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, tmp, 83, 83 );
    }
    params->AddLayoutDirective( Params::LAYOUT_GROUP_END, ""  );







    // space btw. osc anf filters...
    params->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, tmp, 16, 16 );





    params->AddLayoutDirective( Params::LAYOUT_HGROUP_BEGIN, ""  );

    params->AddLayoutDirective( Params::LAYOUT_VGROUP_BEGIN, ""  );

    params->AddLayoutDirective( Params::LAYOUT_LABEL, "MIX STAGES (FILTER / SHAPER)", 200, 13 );

	// params filter
	int cnt = (FILTER_PER_VOICE > SHAPER_PER_VOICE)?FILTER_PER_VOICE:SHAPER_PER_VOICE;
	for(int i = 0; i != cnt ; ++i )
	{
        params->AddLayoutDirective( Params::LAYOUT_HGROUP_BEGIN, ""  );

        snprintf( tmp, 255, "%c: F.%c", 'A' + i*2+0, '0'+i );
        params->AddLayoutDirective( Params::LAYOUT_LABEL, tmp, 42, 13 );

        if (i < FILTER_PER_VOICE)
			voices.filters[i].fillParams( i, params );

        params->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, "", 4, 4 );

        snprintf( tmp, 255, "%c: S.%c", 'A' + i*2+1, '0'+i );
        params->AddLayoutDirective( Params::LAYOUT_LABEL, tmp, 42, 13 );

		if (i < SHAPER_PER_VOICE)
			voices.shapers[i].fillParams( i, params );

        params->AddLayoutDirective( Params::LAYOUT_GROUP_END, ""  );
	}

	// params shaper
	voices.amppans.fillParams( params );

    params->AddLayoutDirective( Params::LAYOUT_LABEL, "ENVELOPE", 128, 13 );

	// params EG
    params->AddLayoutDirective( Params::LAYOUT_HGROUP_BEGIN, ""  );
	for(int i = 0; i != EG_PER_VOICE ; ++i )
		voices.egs[i].fillParams( i, params );

    for (int i = 0 ; i != EG_PER_SYNTH ; ++i )
        egs[i].fillParams( 100 + i , params );

    params->AddLayoutDirective( Params::LAYOUT_GROUP_END, ""  );

    params->AddLayoutDirective( Params::LAYOUT_LABEL, "LFO", 128, 13 );

	// params LFO
    params->AddLayoutDirective( Params::LAYOUT_HGROUP_BEGIN, ""  );
	for(int i = 0; i != LFO_PER_VOICE ; ++i )
		voices.lfos[i].fillParams( i, params );

    for (int i = 0 ; i != LFO_PER_SYNTH ; ++i )
        lfos[i].fillParams( 100 + i , params );

    params->AddLayoutDirective( Params::LAYOUT_GROUP_END, ""  );

    params->AddLayoutDirective( Params::LAYOUT_LABEL, "SEQUENCER", 128, 13 );

	// params SEQ
	for(int i = 0; i != SEQ_PER_VOICE ; ++i )
		voices.seqs[i].fillParams( i, params );

    for (int i = 0 ; i != SEQ_PER_SYNTH ; ++i )
        seqs[i].fillParams( 100 + i , params );

    params->AddLayoutDirective( Params::LAYOUT_LABEL, "KBD", 128, 13 );

    // params KBD
	for(int i = 0; i != KBD_PER_VOICE ; ++i )
		voices.kbds[i].fillParams( i, params );

    params->AddLayoutDirective( Params::LAYOUT_GROUP_END, ""  );
    params->AddLayoutDirective( Params::LAYOUT_VGROUP_BEGIN, ""  );

    params->AddLayoutDirective( Params::LAYOUT_LABEL, "MATRIX", 128, 13 );

    // all dst names
    params->AddLayoutDirective( Params::LAYOUT_HGROUP_BEGIN, ""  );
    params->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, "", 37, 10 );
    params->AddLayoutDirective( Params::LAYOUT_LABEL, "OSC0", 7 * MODOSCDST_VOICE_COUNT, 12 );
    params->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, "", 1, 1 );
    params->AddLayoutDirective( Params::LAYOUT_LABEL, "OSC1", 7 * MODOSCDST_VOICE_COUNT, 12 );
    params->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, "", 1, 1 );
    params->AddLayoutDirective( Params::LAYOUT_LABEL, "OSC2", 7 * MODOSCDST_VOICE_COUNT, 12 );
    params->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, "", 1, 1 );
    params->AddLayoutDirective( Params::LAYOUT_LABEL, "OSC3", 7 * MODOSCDST_VOICE_COUNT, 12 );
    params->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, "", 1, 1 );
    params->AddLayoutDirective( Params::LAYOUT_LABEL, "FILTER", 7 * 3, 12 );
    params->AddLayoutDirective( Params::LAYOUT_GROUP_END, ""  );

    params->AddLayoutDirective( Params::LAYOUT_HGROUP_BEGIN, ""  );

    // all src names
    params->AddLayoutDirective( Params::LAYOUT_VGROUP_BEGIN, ""  );

    for (int s = 0 ; s != MOD_VOICE_SOURCES ; ++s )
	{
        params->AddLayoutDirective( Params::LAYOUT_LABEL, mod_src_names[s], 37, 12 );
	}

    params->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, "", 1, 1 );

  	for (int s = 0 ; s != MOD_SYNTH_SOURCES ; ++s )
	{
        params->AddLayoutDirective( Params::LAYOUT_LABEL, mod_src_names[MOD_VOICE_SOURCES + s], 37, 12 );
    }

    params->AddLayoutDirective( Params::LAYOUT_GROUP_END, "" );
    // all src names







    // modmatrix
	float* mixp_v = voices.modmatrix_voice;
	float* mixp_s = voices.modmatrix_synth;

	for (int d = 0 ; d != MOD_VOICE_DESTINATIONS ; ++d)
	{
        if (d != 0)
        {
            if ( (d % MODOSCDST_VOICE_COUNT) == 0 )
                params->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, "", 1, 1 );
        }

        params->AddLayoutDirective( Params::LAYOUT_VGROUP_BEGIN, ""  );

        float range = 1.f;
		if (ModMatrixDestIsFrequency( d ))
			range = 127.f;

        for (int s = 0 ; s != MOD_VOICE_SOURCES ; ++s, ++mixp_v)
		{
			char tmp[256];
			snprintf(tmp,255,"M%d<%d|Mod Matrix %s += %s",d,s,mod_dst_names[d] ,mod_src_names[s] );
			params->data.push_back( Params::Param( 7, 12, tmp,"", mixp_v, Params::Param::POWX, 0, range, &voices.modmatrix_touched ));
		}

        params->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, "", 1, 1 );

  		for (int s = 0 ; s != MOD_SYNTH_SOURCES ; ++s, ++mixp_s)
		{
			char tmp[256];
			snprintf(tmp,255,"M%d<%d|Mod Matrix %s += %s",d,MOD_VOICE_SOURCES+s,mod_dst_names[d] ,mod_src_names[MOD_VOICE_SOURCES+s] );
			params->data.push_back( Params::Param( 7, 12, tmp,"", mixp_s, Params::Param::POWX, 0, range, &voices.modmatrix_touched ) );
		}
        params->AddLayoutDirective( Params::LAYOUT_GROUP_END, "" );
	}

    params->AddLayoutDirective( Params::LAYOUT_GROUP_END, "" );









    // config
    params->AddLayoutDirective( Params::LAYOUT_LABEL, "CONFIG", 128, 13 );

    snprintf(tmp,255,"VC|Voice Configuration");
	params->data.push_back(Params::Param( 8 , 13, tmp,"config", &voices.config, Params::Param::INTEGER, (voices.CONFIG_COUNT-1.f)*.5f, (voices.CONFIG_COUNT-1.f)*.5f ));
	params->data.back().SetEnums( "SER|PAR" );

//	_snprintf(tmp,255,"DJT|Dynamic Just Tuning");
//	params->data.push_back(Params::Param(tmp,"", &djt, x += PARAM_XSTEP, y) );

	snprintf(tmp,255,"PC|Polyphony Mode Configuration");
	params->data.push_back(Params::Param(8 , 13, tmp,"Poly Mode", &voices.poly_mode, Params::Param::INTEGER, (voices.POLY_MODE_COUNT-1.f)*.5f, (voices.POLY_MODE_COUNT-1.f)*.5f ));
	params->data.back().SetEnums( "POLY|LEGATO|MONO" );
    // config


// GLOBAL !!!




    for (int i = 0 ; i != CC_PER_SYNTH ; ++i )
        midiccs[i].fillParams( 100 + i , params );


    // effects
    params->AddLayoutDirective( Params::LAYOUT_LABEL, "DELAY", 128, 13 );
    params->AddLayoutDirective( Params::LAYOUT_HGROUP_BEGIN, ""  );
    delays.fillParams( params );
    params->AddLayoutDirective( Params::LAYOUT_GROUP_END, ""  );

    params->AddLayoutDirective( Params::LAYOUT_LABEL, "REVERB", 128, 13 );
    params->AddLayoutDirective( Params::LAYOUT_HGROUP_BEGIN, ""  );
    reverbs.fillParams( params );
    params->AddLayoutDirective( Params::LAYOUT_GROUP_END, ""  );

    params->AddLayoutDirective( Params::LAYOUT_GROUP_END, "" );

}




Synth::Synth()
: voiceCount(0)
, voices(this)
, sample_rate(44100.f)
, keyCount(0)
, last_pitch(.5f) // middle of keyboard
{
	params = new Params();
    FillParams();
    params->Validate();

    vuMeter = 0.f;


	//	filteri.noteOn();
	delayi.reset( this, &delays );
	reverbi.reset( this, &reverbs );
//	dynamicsi.reset( this, &dynamicss );


    for (int i = 0 ; i != EG_PER_SYNTH ; ++i )
        egi[i].noteOn( .5f, .5f, egs + i, this, true );

    for (int i = 0 ; i != LFO_PER_SYNTH ; ++i )
        lfoi[i].noteOn( lfos + i, this );

    for (int i = 0 ; i != SEQ_PER_SYNTH ; ++i )
        seqi[i].noteOn( seqs + i, this );

}

Synth::~Synth()
{
	delete params;
}

static const float vuMeterLimit = 1.e-5f;
static const float vuMeterReset = vuMeterLimit * 100.f;
static float vuMeterFalloff = .99f;
static float vuMeterQuadFalloff = .99f;

void Synth::setSampleRate(float sr)
{
	sample_rate = sr;
    const static float vuHalfLifeSeconds = .1f;
    const float vuHalfLifeSamples = vuHalfLifeSeconds * sr;
    vuMeterFalloff = powf( .5f, 1.f / vuHalfLifeSamples );
    vuMeterQuadFalloff = powf( .5f, 4.f / vuHalfLifeSamples );
}

//-----------------------------------------------------------------------------------------
void accumulate_uninterleave(float* dst_l, float* dst_r, float* src_lr, long count, float& vuMeter)
{
	// unrolling is fun
	for ( ; count > 3 ; count-=4, dst_l+=4, dst_r+=4, src_lr+=8 )
	{
        vuMeter *= vuMeterQuadFalloff;
        vuMeter = fast_max( vuMeter, fabsf( src_lr[0] ) );
        vuMeter = fast_max( vuMeter, fabsf( src_lr[3] ) );
        vuMeter = fast_max( vuMeter, fabsf( src_lr[4] ) );
        vuMeter = fast_max( vuMeter, fabsf( src_lr[7] ) );

        dst_l[0] += src_lr[0];
		dst_r[0] += src_lr[1];
		dst_l[1] += src_lr[2];
		dst_r[1] += src_lr[3];
		dst_l[2] += src_lr[4];
		dst_r[2] += src_lr[5];
		dst_l[3] += src_lr[6];
		dst_r[3] += src_lr[7];
	}

	for ( ; count ; --count, ++dst_l, ++dst_r, src_lr+=2 )
	{
        vuMeter *= vuMeterFalloff;
        vuMeter = fast_max( vuMeter, fabsf( src_lr[0] ) );
        vuMeter = fast_max( vuMeter, fabsf( src_lr[1] ) );

        *dst_l += src_lr[0];
		*dst_r += src_lr[1];
	}
}


//-----------------------------------------------------------------------------------------
void copy_uninterleave(float* dst_l, float* dst_r, float* src_lr, long count, float& vuMeter)
{
	// unrolling is fun
	for ( ; count > 3 ; count-=4, dst_l+=4, dst_r+=4, src_lr+=8 )
	{
        vuMeter *= vuMeterQuadFalloff;
        vuMeter = fast_max( vuMeter, fabsf( src_lr[0] ) );
        vuMeter = fast_max( vuMeter, fabsf( src_lr[3] ) );
        vuMeter = fast_max( vuMeter, fabsf( src_lr[4] ) );
        vuMeter = fast_max( vuMeter, fabsf( src_lr[7] ) );

        dst_l[0] = src_lr[0];
		dst_r[0] = src_lr[1];
		dst_l[1] = src_lr[2];
		dst_r[1] = src_lr[3];
		dst_l[2] = src_lr[4];
		dst_r[2] = src_lr[5];
		dst_l[3] = src_lr[6];
		dst_r[3] = src_lr[7];
	}

	for ( ; count ; --count, ++dst_l, ++dst_r, src_lr+=2 )
	{
        vuMeter *= vuMeterFalloff;
        vuMeter = fast_max( vuMeter, fabsf( src_lr[0] ) );
        vuMeter = fast_max( vuMeter, fabsf( src_lr[1] ) );
		*dst_l = src_lr[0];
		*dst_r = src_lr[1];
	}
}

extern void securityProcess( float *lr, int frames );

//-----------------------------------------------------------------------------------------
void Synth::process( float* l, float* r, int totalSampleFrames, bool accum)
{
    // turn synth off if no sound...
    if ( vuMeter < vuMeterLimit )
    {
        vuMeter = 0.f;
        if (!accum)
        {
	        memset(l, 0, totalSampleFrames * sizeof (float));
    	    memset(r, 0, totalSampleFrames * sizeof (float));
        }
        return;
    }

    float* lr = synth_audio;

    while( totalSampleFrames )
    {
        int sampleFrames = totalSampleFrames;
	    if (sampleFrames > ABUFS)
		    sampleFrames = ABUFS;

	    int modc = (sampleFrames+ACSCALE-1) / ACSCALE;

   	    // check what parts of synth is actually used
	    if (voices.modmatrix_touched)
		    voices.calc_used();

	    // render modulators (env+lfos) FIXME!!! skip if unused
        float* modsrcp = voices.modsrc_synth;

        int sourceindex = 0;
	    for (int i = 0 ; i != EG_PER_SYNTH ; ++i, modsrcp+=CBUFS)
        {
		    if (voices.modmatrix_src_used_synth[ sourceindex++ ])
                egi[i].processReplace(modsrcp, modc );
        }

	    for (int i = 0 ; i != LFO_PER_SYNTH ; ++i, modsrcp+=CBUFS)
        {
		    if (voices.modmatrix_src_used_synth[ sourceindex++ ])
                lfoi[i].processReplace(modsrcp, modc );
        }

   	    for (int i = 0 ; i != SEQ_PER_SYNTH ; ++i, modsrcp+=CBUFS)
        {
		    if (voices.modmatrix_src_used_synth[ sourceindex++ ])
                seqi[i].processReplace( modsrcp, modc );
        }

   	    for (int i = 0 ; i != CC_PER_SYNTH ; ++i, modsrcp+=CBUFS)
        {
		    if (voices.modmatrix_src_used_synth[ sourceindex++ ])
                midicci[i].processReplace(modsrcp, modc );
        }

	    // must clear the output
	    memset(lr, 0, sampleFrames * 2 * sizeof (float));

	    // the nice way of moving voices around...
	    int last_used = -1;
	    for (int i = 0 ; i != voiceCount ; ++i)
	    {
		    if ( voiceFarm[i].state != VoiceInstance::Unused)
		    {
			    voiceFarm[i].processAccum( lr, sampleFrames );
			    last_used = i;
		    }
	    }
	    voiceCount = last_used+1;

	    // do global effects here

	    // global filter
	    //	filteri.processReplace( this, &filters, moddst, lr, sampleFrames );

   	    // amp/compressor/limiter

	    // tarncegate

        // phaser

	    // delay/chorus

	    delayi.processReplace( lr, sampleFrames );

	    // reverb
	    reverbi.processReplace( lr, sampleFrames );

	    //dynamicsi.processReplace( lr, sampleFrames );

        // when licences and stuff is in.. this would make sense to call
        // securityProcess(lr, sampleFrames );

	    if (accum)
		    accumulate_uninterleave( l, r, lr, sampleFrames, vuMeter );
	    else
		    copy_uninterleave( l, r, lr, sampleFrames, vuMeter );

        totalSampleFrames -= sampleFrames;
        l += sampleFrames;
        r += sampleFrames;
    }

}

bool Synth::LikesRawMidi(int status, int midi1, int midi2 )
{
    for ( int i = 0 ; i != CC_PER_SYNTH ; ++i )
    {
        if ( midiccs[i].Likes( status, midi1, midi2 ) )
        {
            return true;
        }
    }
    return false;
}

void Synth::RawMidi( int status, int midi1, int midi2 )
{
    for ( int i = 0 ; i != CC_PER_SYNTH ; ++i )
        midicci[i].RawMidi( status, midi1, midi2, midiccs );
}

void Synth::noteOn(char note, float vel/*0..1*/)
{
	if (vel < (1.f/128.f) )
		return;

    // always set the state to soundung when a key is hit...
    vuMeter = vuMeterReset;

	u32 ipoly = fast_ftol1023( voices.poly_mode + .5f );

	switch (ipoly)
	{
	case VoiceSettings::POLY_MODE_POLY:
		noteOnPoly( note, vel );
		break;

	case VoiceSettings::POLY_MODE_MONO_RETUNE:
        noteOnMonoRetune( note, vel );
		break;

   	case VoiceSettings::POLY_MODE_MONO_RESET:
        noteOnMonoReset( note, vel );
		break;

	}

    // add the note last
    keyDown[keyCount] = note;
	++keyCount;

}

void Synth::noteOnPoly(char note, float vel/*0..1*/)
{
	float linj_freq = note;
	linj_freq /= 127.f; // from midi to 0..1

	// FIXME... apply any global tuning to linj_freq-here

	int lowi = 0; // first unused voice

	// look for unused
	for ( ; lowi != voiceCount ; ++lowi )
		if ( voiceFarm[lowi].state == VoiceInstance::Unused )
			break;

	if (lowi == VOICEMAX)
	{
		// if full take anyone that is releasing...
		int release_max = -1;
		for ( int i = 0 ; i != VOICEMAX ; ++i )
		{
			if ( voiceFarm[i].state == VoiceInstance::Release &&
				voiceFarm[i].frames_in_state > release_max )
			{
				lowi = i;
				release_max = voiceFarm[i].frames_in_state;
			}
		}

		if (lowi == VOICEMAX)
		{
			// if full take anyone that is playing...
			int live_max = -1;
			for ( int i = 0 ; i != VOICEMAX ; ++i )
			{
				if ( voiceFarm[i].frames_in_state > live_max )
				{
					lowi = i;
					live_max = voiceFarm[i].frames_in_state;
				}
			}

		}

	}

	voiceFarm[lowi].noteOn( note, linj_freq, vel, &voices );
	if (lowi+1 > voiceCount)
		voiceCount = lowi+1;

	if (keyCount == 0)
	{
        for (int i = 0 ; i != EG_PER_SYNTH ; ++i )
        {
            egi[i].noteOn( linj_freq, vel, &egs[i], this, true );
        }

        for (int i = 0 ; i != LFO_PER_SYNTH ; ++i )
        {
            lfoi[i].noteOn( &lfos[i], this );
        }

        for (int i = 0 ; i != SEQ_PER_SYNTH ; ++i )
        {
            seqi[i].noteOn( &seqs[i], this );
        }
    }

	last_pitch = linj_freq;

	// disable just tuning until it works

	//if (keypressed > 0)
	//{
	//	// handle tuning... of everything
	//	double justTuning[VOICEMAX];
	//	int justTuningIndex[VOICEMAX];
	//	int justTuningRun = 0;

	//	for ( int i = 0 ; i != VOICEMAX ; ++i )
	//	{
	//		if ( voiceFarm[i].state != VoiceInstance::Used)
	//			continue;

	//		justTuning[justTuningRun] = voiceFarm[i].kbdi[0].getOriginalKey() * 127./12.; // convert from linj to octaves
	//		justTuningIndex[justTuningRun] = i;
	//		++justTuningRun;
	//	}

	//	if (justTuningRun > 1)
	//	{
	//		gTuner.reTuneAll( justTuning, justTuning + justTuningRun, voices.djt );

	//		for ( int i = 0 ; i != justTuningRun ; ++i )
	//		{
	//			int index = justTuningIndex[i];
	//			double key = justTuning[i];
 //               VoiceInstance* vi = voiceFarm + index;
	//			for ( u32 j = 0 ; j != KBD_PER_VOICE ; ++j)
 //               {
 //                   KBDInstance* ki = vi->kbdi + j;
 //                   const KBDSettings* ks = voices.kbds + j;
 //                   ki->noteOn( key * (float)12./127., vel, ks, vi, true ); // convert from linj to octaves;
 //               }
	//		}
	//	}
	//}
}

void Synth::noteOnMonoRetune(char note, float velocity/*0..1*/)
{
	float linj_freq = note;
	linj_freq /= 127.f; // from midi to 0..1

	// find active voice

	int found_voice = 0; // first unused voice

	// look for used
	for ( ; found_voice != voiceCount ; ++found_voice )
		if ( voiceFarm[found_voice].state == VoiceInstance::Used )
			break;

	// if no found used play like normal... early out
	if ( found_voice == voiceCount )
	{
		noteOnPoly( note, velocity );
		return;
	}

	// re tune found voice
    VoiceInstance* vi = voiceFarm + found_voice;
	for ( u32 j = 0 ; j != KBD_PER_VOICE ; ++j)
    {
        KBDInstance* ki = vi->kbdi + j;
        const KBDSettings* ks = voices.kbds + j;
        ki->noteOn( note, velocity, ks, vi, true ); // convert from linj to octaves;
        vi->kbdi[j].noteOn( linj_freq, velocity, ks, vi, true );
    }

	// set note
	voiceFarm[found_voice].key = note;
}

void Synth::noteOnMonoReset(char note, float velocity/*0..1*/)
{
	float linj_freq = note;
	linj_freq /= 127.f; // from midi to 0..1

	// find active voice

	int found_voice = 0; // first unused voice

	// look for used
	for ( ; found_voice != voiceCount ; ++found_voice )
		if ( voiceFarm[found_voice].state == VoiceInstance::Used )
			break;

	// if no found used play like normal... early out
	if ( found_voice == voiceCount )
	{
		noteOnPoly( note, velocity );
		return;
	}

	voiceFarm[found_voice].noteOn( note, linj_freq, velocity, &voices, true );
}

//-----------------------------------------------------------------------------------------
void Synth::noteOff ( char note )
{
    // find this note and remove it
    int found = 0;
    for ( ; found != keyCount ; ++found )
    {
        if ( keyDown[found] == note )
        {
            break;
        }
    }

    bool needReplay = false;

    if ( found == keyCount )
    {
        keyCount = 0; // kill all to be safe
    }
    else
    {
        --keyCount;

        if ( keyCount == found )
        {
            needReplay = true;
        }
        else
        {
            // copy over
            for ( int i = found ; i != keyCount ; ++i )
            {
                keyDown[i] = keyDown[i+1];
            }
        }
    }

    if (keyCount < 1)
	{
   	    for (int i = 0 ; i != voiceCount ; ++i)
	    {
		    if (voiceFarm[i].key == note)
			    voiceFarm[i].noteOff();
	    }

        // off...
		for (int i = 0 ; i != EG_PER_SYNTH ; ++i )
			egi[i].noteOff();

        //		noteoff global lfos and stuff
	}
    else
    {
        // trigger with another
      	u32 ipoly = fast_ftol1023( voices.poly_mode + .5f );

        switch (ipoly)
        {
    	case VoiceSettings::POLY_MODE_POLY:
	        for (int i = 0 ; i != voiceCount ; ++i)
	        {
		        if (voiceFarm[i].key == note)
			        voiceFarm[i].noteOff();
	        }
    		break;

        case VoiceSettings::POLY_MODE_MONO_RETUNE:
        case VoiceSettings::POLY_MODE_MONO_RESET:
            if (needReplay)
            {
        		noteOnMonoRetune( keyDown[keyCount-1], .1 );
            }
    		break;
        }

    }
}

void Synth::noteOffAll ()
{
	for (int i = 0 ; i != voiceCount ; ++i)
		if (voiceFarm[i].state == VoiceInstance::Used )
			voiceFarm[i].noteOff();

	keyCount = 0;
	// noteoff global lfos and stuff
	// off...
	for (int i = 0 ; i != EG_PER_SYNTH ; ++i )
		egi[i].noteOff();
	//		filteri.noteOff( this, &filters, 0,
	//		noteoff global lfos and stuff

}
