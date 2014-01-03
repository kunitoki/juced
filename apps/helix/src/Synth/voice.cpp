
// Copyright (c) 2007, Nils Jonas Norberg, See COPYING.txt for details

#include "voice.h"
#include "params.h"

#include <memory.h>
#include <stdlib.h>
#include <math.h>

#include "fastmath.inl"


void VoiceSettings::calc_used()
{
	for (int d = 0 ; d != MOD_VOICE_DESTINATIONS ; ++d)
	{
		float* mixp_v = modmatrix_voice + d * MOD_VOICE_SOURCES;
		bool used = false;
		for ( int s = 0 ; s != MOD_VOICE_SOURCES ; ++s, ++mixp_v)
		{
			if ( fabs( *mixp_v ) > 0.0001f )
			{
				used = true;
				break;
			}
		}

        if (!used)
        {
      		float* mixp_s = modmatrix_synth + d * MOD_SYNTH_SOURCES;
		    for ( int s = 0 ; s != MOD_SYNTH_SOURCES ; ++s, ++mixp_s)
		    {
			    if ( fabs( *mixp_s ) > 0.0001f )
			    {
				    used = true;
				    break;
			    }
		    }

        }

		modmatrix_dst_used[ d ] = used;
		if (!used)
			memset( moddst + d*CBUFS, 0,CBUFS*sizeof(float) );
	}

	// first EG is always used (hardcoded) for voice amp.
	modmatrix_src_used_voice[ 0 ] = true;

	for (int s = 1 ; s != MOD_VOICE_SOURCES ; ++s)
	{
		float* mixp = modmatrix_voice + s;
		bool used = false;
		for ( int d = 0 ; d != MOD_VOICE_DESTINATIONS ; ++d, mixp += MOD_VOICE_SOURCES)
		{
			if ( fabs( *mixp ) > 0.0001f )
			{
				used = true;
				break;
			}
		}

		modmatrix_src_used_voice[ s ] = used;
		if (!used)
			memset( modsrc_voice + s*CBUFS, 0,CBUFS*sizeof(float) );
	}

  	for (int s = 0 ; s != MOD_SYNTH_SOURCES ; ++s)
	{
		float* mixp = modmatrix_synth + s;
		bool used = false;
		for ( int d = 0 ; d != MOD_VOICE_DESTINATIONS ; ++d, mixp += MOD_SYNTH_SOURCES)
		{
			if ( fabs( *mixp ) > 0.0001f )
			{
				used = true;
				break;
			}
		}

		modmatrix_src_used_synth[ s ] = used;
		if (!used)
			memset( modsrc_synth + s*CBUFS, 0,CBUFS*sizeof(float) );
	}

	modmatrix_touched = false;
}

VoiceSettings::VoiceSettings(Synth* s)
	:synth(s)
{
	config = 0;
//	djt = .1f;
	poly_mode = 0;

	oscs[0].on = 1.f;

	memset( modmatrix_voice, 0, MOD_VOICE_SOURCES * MOD_VOICE_DESTINATIONS * sizeof(float) );
	memset( modmatrix_synth, 0, MOD_SYNTH_SOURCES * MOD_VOICE_DESTINATIONS * sizeof(float) );

	//  EG0 EG1 LF0 LF1 SE0 KBD 
	//0  x   x   x   x   x   x  OSC0 AMP
	//1  x   x   x   x   x   x   --  PAN
	//2  x   x   x   x   x   x   --  HARM
	//3  x   x   x   x   x   x   --  MORPH
	//4  x   x   x   x   x   x   --  PITCH
	//5  x   x   x   x   x   x   --  SPREAD
	//6  x   x   x   x   x   x  OSC1 AMP
	//7  x   x   x   x   x   x   --  PAN
	//8  x   x   x   x   x   x   --  HARM
	//9  x   x   x   x   x   x   --  MORPH
	//a  x   x   x   x   x   x   --  PITCH
	//b  x   x   x   x   x   x   --  SPREAD
	//c  x   x   x   x   x   x  OSC2 AMP
	//d  x   x   x   x   x   x   --  PAN
	//e  x   x   x   x   x   x   --  HARM
	//f  x   x   x   x   x   x   --  MORPH
	//0  x   x   x   x   x   x   --  PITCH
	//1  x   x   x   x   x   x   --  SPREAD
	//2  x   x   x   x   x   x  OSC3 AMP
	//3  x   x   x   x   x   x   --  PAN
	//4  x   x   x   x   x   x   --  HARM
	//5  x   x   x   x   x   x   --  MORPH
	//6  x   x   x   x   x   x   --  PITCH
	//7  x   x   x   x   x   x   --  SPREAD
	//8  x   x   x   x   x   x  FLT0 FREQ
	//9  x   x   x   x   x   x  FLT1 FREQ
	//0  x   x   x   x   x   x  FLT2 FREQ

	for ( u32 i = 0 ; i != OSC_PER_VOICE ; ++i)
	{
        int row = MODOSCDST_VOICE_COUNT * i + MODOSCDST_VOICE_HARM;
		modmatrix_voice[ row * MOD_VOICE_SOURCES + MOD_VOICE_SOURCES - 1] = 127.f; // harm += kbd
        row = MODOSCDST_VOICE_COUNT * i + MODOSCDST_VOICE_PITCH;
		modmatrix_voice[ row * MOD_VOICE_SOURCES + MOD_VOICE_SOURCES - 1] = 127.f; // harm += kbd
	}

	calc_used();
}


VoiceInstance::VoiceInstance()
:key(-1)
,state(Unused)
{
}

u32 VoiceInstance::note_counter = 0;

void VoiceInstance::noteOn( int in_key, float in_linj_freq /*0..*/, float vel/*0..1*/, VoiceSettings* vs, bool monoMode )
{
	frames_in_state = 0;
	state = Used;
	key = in_key;
	settings = vs;

	/// AUDIO ///

	// OSC
	for(int i = 0; i != OSC_PER_VOICE ; ++i )
		osci[i].noteOn( &vs->oscs[i], !monoMode );

	// FILTER
	for(int i = 0; i != FILTER_PER_VOICE ; ++i )
		filteri[i].noteOn( !monoMode );

	// SHAPER
	for(int i = 0; i != SHAPER_PER_VOICE ; ++i )
		shaperi[i].noteOn( &vs->shapers[i] , this, !monoMode );

	// AMP-PAN
	amppani.noteOn( &vs->amppans, this, !monoMode );

	/// CONTROL ///

	// EG
	for(int i = 0; i != EG_PER_VOICE ; ++i )
		egi[i].noteOn( in_linj_freq , vel, &vs->egs[i], vs->synth, !monoMode );

	// LFO
	for(int i = 0; i != LFO_PER_VOICE ; ++i )
		lfoi[i].noteOn( &vs->lfos[i], vs->synth );

	// SEQ
	for(int i = 0; i != SEQ_PER_VOICE ; ++i )
		seqi[i].noteOn( &vs->seqs[i], vs->synth );

	// KBD
	for(int i = 0; i != KBD_PER_VOICE ; ++i )
		kbdi[i].noteOn( in_linj_freq, vel, &vs->kbds[i], this, monoMode );

	++note_counter;
}

void VoiceInstance::noteOff()
{
	if (state == Release)
		return; // die a normal death

	state = Release;
	frames_in_state = 0;

	// EG
	for(int i = 0; i != EG_PER_VOICE ; ++i )
		egi[i].noteOff();

	// LFO
	for(int i = 0; i != LFO_PER_VOICE ; ++i )
		lfoi[i].noteOff();

	// SEQ
	for(int i = 0; i != SEQ_PER_VOICE ; ++i )
		seqi[i].noteOff();

	// KBD
	for(int i = 0; i != KBD_PER_VOICE ; ++i )
		kbdi[i].noteOff();
}


void accumul8scale(float* dst, float* src, long count, float scale)
{
	for ( ; count > 7 ; count-=8, dst+=8, src+=8)
	{
		dst[0] += src[0] * scale;
		dst[1] += src[1] * scale;
		dst[2] += src[2] * scale;
		dst[3] += src[3] * scale;
		dst[4] += src[4] * scale;
		dst[5] += src[5] * scale;
		dst[6] += src[6] * scale;
		dst[7] += src[7] * scale;
	}

	for ( ; count ; --count, ++dst, ++src)
		*dst += *src * scale;
}

void accumul8(float* dst, float* src, long count)
{
	for ( ; count > 7 ; count-=8, dst+=8, src+=8)
	{
		dst[0] += src[0];
		dst[1] += src[1];
		dst[2] += src[2];
		dst[3] += src[3];
		dst[4] += src[4];
		dst[5] += src[5];
		dst[6] += src[6];
		dst[7] += src[7];
	}

	for ( ; count ; --count, ++dst, ++src)
		*dst += *src;
}

void VoiceInstance::processAccumSer( float* lr, int tempcount )
{
		// render oscs (stereo)
		memset( settings->voice_audio , 0, 2 * tempcount * sizeof(float));
		
        // stage 0
		for(int i = 0; i != OSC_PER_VOICE ; ++i )
		{
			if (settings->oscs[i].stage == 0.f)
				osci[i].processAccum( settings->synth, settings->moddst + (i*MODOSCDST_VOICE_COUNT*CBUFS), settings->voice_audio, tempcount );
		}

		// render filter 0
		filteri[0].processReplace( settings->synth, &settings->filters[0] , settings->moddst + (OSC_PER_VOICE*MODOSCDST_VOICE_COUNT*CBUFS) + (0*MODFLTDST_VOICE_COUNT*CBUFS), settings->voice_audio, tempcount );

		// stage 1
		for(int i = 0; i != OSC_PER_VOICE ; ++i )
		{
			if (settings->oscs[i].stage == 1.f)
				osci[i].processAccum( settings->synth, settings->moddst + (i*MODOSCDST_VOICE_COUNT*CBUFS), settings->voice_audio, tempcount );
		}

		// render shaper
		shaperi[0].processReplace( settings->voice_audio, tempcount );

		// stage 2
		for(int i = 0; i != OSC_PER_VOICE ; ++i )
		{
			if (settings->oscs[i].stage == 2.f)
				osci[i].processAccum( settings->synth, settings->moddst + (i*MODOSCDST_VOICE_COUNT*CBUFS), settings->voice_audio, tempcount );
		}

		// render filter 1
		filteri[1].processReplace(  settings->synth, &settings->filters[1] , settings->moddst + (OSC_PER_VOICE*MODOSCDST_VOICE_COUNT*CBUFS) + (1*MODFLTDST_VOICE_COUNT*CBUFS), settings->voice_audio, tempcount );

		// stage 3
		for(int i = 0; i != OSC_PER_VOICE ; ++i )
		{
			if (settings->oscs[i].stage == 3.f)
				osci[i].processAccum( settings->synth, settings->moddst + (i*MODOSCDST_VOICE_COUNT*CBUFS), settings->voice_audio, tempcount );
		}

		// render shaper
		shaperi[1].processReplace( settings->voice_audio, tempcount );

		// stage 4
		for(int i = 0; i != OSC_PER_VOICE ; ++i )
		{
			if (settings->oscs[i].stage == 4.f)
				osci[i].processAccum( settings->synth, settings->moddst + (i*MODOSCDST_VOICE_COUNT*CBUFS), settings->voice_audio, tempcount );
		}

   		// render filter 2
		filteri[2].processReplace(  settings->synth, &settings->filters[2] , settings->moddst + (OSC_PER_VOICE*MODOSCDST_VOICE_COUNT*CBUFS) + (2*MODFLTDST_VOICE_COUNT*CBUFS), settings->voice_audio, tempcount );

		// stage 5
		for(int i = 0; i != OSC_PER_VOICE ; ++i )
		{
			if (settings->oscs[i].stage == 5.f)
				osci[i].processAccum( settings->synth, settings->moddst + (i*MODOSCDST_VOICE_COUNT*CBUFS), settings->voice_audio, tempcount );
		}

		// render shaper
		shaperi[2].processReplace( settings->voice_audio, tempcount );

		// stage 6
		for(int i = 0; i != OSC_PER_VOICE ; ++i )
		{
			if (settings->oscs[i].stage == 6.f)
				osci[i].processAccum( settings->synth, settings->moddst + (i*MODOSCDST_VOICE_COUNT*CBUFS), settings->voice_audio, tempcount );
		}

		// amp-pan to left and right
		amppani.processReplace( lr, settings->voice_audio, tempcount );
}

void VoiceInstance::processAccumPar( float* lr, int tempcount )
{
		// render oscs (stereo)
		memset(settings->voice_audio , 0, 2 * tempcount * sizeof(float));
		memset(settings->parallel_audio , 0, 2 * tempcount * sizeof(float));
		
		// stage 0
		for(int i = 0; i != OSC_PER_VOICE ; ++i )
		{
			if (settings->oscs[i].stage == 0.f)
				osci[i].processAccum( settings->synth, settings->moddst + (i*MODOSCDST_VOICE_COUNT*CBUFS), settings->voice_audio, tempcount );
		}

		// render filter 0
		filteri[0].processReplace( settings->synth, &settings->filters[0] , settings->moddst + (OSC_PER_VOICE*MODOSCDST_VOICE_COUNT*CBUFS) + (0*MODFLTDST_VOICE_COUNT*CBUFS), settings->voice_audio, tempcount );

		// stage 1
		for(int i = 0; i != OSC_PER_VOICE ; ++i )
		{
			if (settings->oscs[i].stage == 1.f)
				osci[i].processAccum( settings->synth, settings->moddst + (i*MODOSCDST_VOICE_COUNT*CBUFS), settings->voice_audio, tempcount );
		}

		// render shaper
		shaperi[0].processReplace(settings->voice_audio, tempcount );


		// SWITCH BUFFER!!!

		// stage 2
		for(int i = 0; i != OSC_PER_VOICE ; ++i )
		{
			if (settings->oscs[i].stage == 2.f)
				osci[i].processAccum( settings->synth, settings->moddst + (i*MODOSCDST_VOICE_COUNT*CBUFS), settings->parallel_audio, tempcount );
		}

		// render filter 1
		filteri[1].processReplace(  settings->synth, &settings->filters[1] , settings->moddst + (OSC_PER_VOICE*MODOSCDST_VOICE_COUNT*CBUFS) + (1*MODFLTDST_VOICE_COUNT*CBUFS), settings->parallel_audio, tempcount );

		// stage 3
		for(int i = 0; i != OSC_PER_VOICE ; ++i )
		{
			if (settings->oscs[i].stage == 3.f)
				osci[i].processAccum( settings->synth, settings->moddst + (i*MODOSCDST_VOICE_COUNT*CBUFS), settings->parallel_audio, tempcount );
		}

		// render shaper
		shaperi[1].processReplace(settings->parallel_audio, tempcount );

		// accumulate back into original...
		accumul8( settings->voice_audio, settings->parallel_audio, ABUFS * 2);

		// stage 4
		for(int i = 0; i != OSC_PER_VOICE ; ++i )
		{
			if (settings->oscs[i].stage == 4.f)
				osci[i].processAccum( settings->synth, settings->moddst + (i*MODOSCDST_VOICE_COUNT*CBUFS), settings->voice_audio, tempcount );
		}

   		// render filter 2
		filteri[2].processReplace(  settings->synth, &settings->filters[2] , settings->moddst + (OSC_PER_VOICE*MODOSCDST_VOICE_COUNT*CBUFS) + (2*MODFLTDST_VOICE_COUNT*CBUFS), settings->voice_audio, tempcount );

		// stage 5
		for(int i = 0; i != OSC_PER_VOICE ; ++i )
		{
			if (settings->oscs[i].stage == 5.f)
				osci[i].processAccum( settings->synth, settings->moddst + (i*MODOSCDST_VOICE_COUNT*CBUFS), settings->voice_audio, tempcount );
		}

		// render shaper
		shaperi[2].processReplace( settings->voice_audio, tempcount );

		// stage 6
		for(int i = 0; i != OSC_PER_VOICE ; ++i )
		{
			if (settings->oscs[i].stage == 6.f)
				osci[i].processAccum( settings->synth, settings->moddst + (i*MODOSCDST_VOICE_COUNT*CBUFS), settings->voice_audio, tempcount );
		}


		// amp-pan to left and right
		amppani.processReplace(lr,settings->voice_audio, tempcount);
}


void VoiceInstance::processAccum( float* lr, int count )
{
	// check what parts of synth is actually used
	if (settings->modmatrix_touched)
		settings->calc_used();

	frames_in_state += count;

	while (count)
	{
		int tempcount = count;
		if (tempcount > ABUFS)
			tempcount = ABUFS;

		int modc = (tempcount+ACSCALE-1) / ACSCALE;

		float* modsrcp = settings->modsrc_voice;

		u32 sourceindex = 0;
		for (int i = 0 ; i != EG_PER_VOICE ; ++i, modsrcp+=CBUFS)
		{
			if (settings->modmatrix_src_used_voice[ sourceindex++ ])
				egi[i].processReplace(modsrcp, modc );
		}

		for (int i = 0 ; i != LFO_PER_VOICE ; ++i, modsrcp+=CBUFS)
		{
			if (settings->modmatrix_src_used_voice[ sourceindex++ ])
				lfoi[i].processReplace(modsrcp, modc );
		}

		for (int i = 0 ; i != SEQ_PER_VOICE ; ++i, modsrcp+=CBUFS)
		{
			if (settings->modmatrix_src_used_voice[ sourceindex++ ])
				seqi[i].processReplace(modsrcp, modc );
		}

		for (int i = 0 ; i != KBD_PER_VOICE ; ++i, modsrcp+=CBUFS)
		{
			if (settings->modmatrix_src_used_voice[ sourceindex++ ])
				kbdi[i].processReplace(modsrcp, modc );
		}

		// mix modulators in accordance to the mod-matrix (matrices)
		float* mixp_v = settings->modmatrix_voice;
		float* mixp_s = settings->modmatrix_synth;
		float* dstp = settings->moddst;
		for (int dst = 0 ; dst != MOD_VOICE_DESTINATIONS ; ++dst, dstp+=CBUFS )
		{
			if (settings->modmatrix_dst_used[dst])
			{
				memset(dstp,0,CBUFS*sizeof(float));
				float* srcp_v = settings->modsrc_voice;
				for (int src = 0 ; src != MOD_VOICE_SOURCES ; ++src, srcp_v+=CBUFS, ++mixp_v )
				{
					if ( fabs( *mixp_v ) > 0.0001f )
						accumul8scale(dstp, srcp_v, modc, *mixp_v );
				}

				float* srcp_s = settings->modsrc_synth;
                for (int src = 0 ; src != MOD_SYNTH_SOURCES ; ++src, srcp_s+=CBUFS, ++mixp_s )
				{
					if ( fabs( *mixp_s ) > 0.0001f )
						accumul8scale(dstp, srcp_s, modc, *mixp_s );
				}
			}
			else
			{
				mixp_v += MOD_VOICE_SOURCES;
				mixp_s += MOD_SYNTH_SOURCES;
			}
		}

		int iconf = fast_ftol1023( settings->config + .5f );

		if (iconf < VoiceSettings::CONFIG_FIRST_PARALLEL)
			processAccumSer( lr, tempcount );
		else
			processAccumPar( lr, tempcount );

		count -= tempcount;
		lr += tempcount*2;
	}

	if (
		state == Release 
		&& egi[0].isSilent()
		)
	{
		// remove yourself
		state = Unused;
	}
}
