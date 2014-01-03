#ifndef WaveGroup_INCLUDED
#define WaveGroup_INCLUDED


// Copyright (c) 2007, Nils Jonas Norberg, See COPYING.txt for details

// 512
#define CYCLEBITS 9
#define CYCLELEN (1<<CYCLEBITS)
#define CYCLEMASK (CYCLELEN-1)

#define FRACBITS (32-CYCLEBITS)
#define FRACMASK ((1<<FRACBITS)-1)
#define CYCLESHIFT FRACBITS

#define GROUPCYCLES (CYCLELEN>>1) //

#define FREQ_DATALEN (CYCLELEN / 2 + 1)

#include "../../../../juce/src/extended/dependancies/kissfft/kiss_fftr.h"

class WaveGroup
{
public:
	WaveGroup( float* wave = 0 );
	~WaveGroup();

	void set( float* wave, float fundamentalBoost = 0.f, kiss_fft_cpx* usePhases = 0 );
	const float* get_wave(int w /*0..GROUPC.-1*/) const; // will likely be cached

	static float tempwave[CYCLELEN]; // used for the default wave

    kiss_fft_cpx* GetFreqs(){ return freqs; }

private:
	kiss_fftr_cfg fftcfg;
	kiss_fftr_cfg fftcfgi;
	kiss_fft_cpx freqs[FREQ_DATALEN]; // all frequencies... masked and ifft's
	mutable float wave_data[GROUPCYCLES * CYCLELEN];
	mutable bool wave_exists[GROUPCYCLES];
};

#endif
