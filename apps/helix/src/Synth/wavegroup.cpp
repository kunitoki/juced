
// Copyright (c) 2007, Nils Jonas Norberg, See COPYING.txt for details

#include <float.h>

#include "wavegroup.h"

#include "fastmath.inl"

WaveGroup::WaveGroup(float* wave )
{
	fftcfg = kiss_fftr_alloc(CYCLELEN,false,0,0);
	fftcfgi = kiss_fftr_alloc(CYCLELEN,true,0,0);
	set( wave );

	for (int i = 0 ; i != GROUPCYCLES ; ++i)
		wave_exists[i] = false;
}

inline void rms_normalize(float* buffer, int len)
{
	float mv = 0.f;
	for (int i = 0 ; i != len ; ++i)
		mv += fabsf(buffer[i]);

	if (mv > .001f)
	{
		// includes the scaling to match the fft
		float scale = .4f / mv;
		for (int i = 0 ; i != len ; ++i)
			buffer[i] *= scale;
	}
}

inline void dc_fix(float* buffer, int len)
{
	float av = 0.f;
	float mul = 1.f / len;
	for (int i = 0 ; i != len ; ++i)
		av += buffer[i] * mul;

	if (fabsf(av) > FLT_EPSILON)
		for (int i = 0 ; i != len ; ++i)
			buffer[i] -= av;
}

float WaveGroup::tempwave[CYCLELEN];

void WaveGroup::set(float* wave, float fundamentalBoost, kiss_fft_cpx* useThesePhases )
{
	// pre-fix the data...
	if (!wave)
	{
		for (int i = 0 ; i != CYCLELEN ; ++i )
			tempwave[i] = (float)i / (CYCLELEN-1.f);
		wave = tempwave;
	}

	dc_fix(wave, CYCLELEN);
	// the amplitude is super low after rms_normalize (1/CYCLELEN to fit the FFT)
	rms_normalize(wave, CYCLELEN);

	kiss_fftr( fftcfg, wave, freqs );

    // BOOOOST
    if ( fundamentalBoost > FLT_EPSILON )
    {
        float fundamentalPower = sqrtf( freqs[1].r * freqs[1].r + freqs[1].i * freqs[1].i );
        fast_clamp_in_place( fundamentalPower, .001f, 2.f );

        // normalized to .4 already so ...
        float fracOfMax = fundamentalPower / .4f;

        float maxMul = 1.f / fracOfMax;
        float fundMul = 1.f + ( maxMul - 1.f) * fundamentalBoost;

        freqs[1].r *= fundMul;
        freqs[1].i *= fundMul;

        float mul = 1.f - fundamentalBoost;
	    for ( int i = 2 ; i != FREQ_DATALEN ; ++i)
	    {
		    freqs[i].r *= mul;
		    freqs[i].i *= mul;
	    }
    }

    if ( useThesePhases )
    {
        for ( int i = 1 ; i != FREQ_DATALEN ; ++i )
        {
            kiss_fft_cpx& f = freqs[i];
            kiss_fft_cpx& uf = useThesePhases[i];
            float mul = sqrtf( f.i*f.i + f.r*f.r );
            f.r = uf.r * mul;
            f.i = uf.i * mul;
        }
    }

	for (int i = 0 ; i != GROUPCYCLES ; ++i)
		wave_exists[i] = false;
}

WaveGroup::~WaveGroup()
{
	free( fftcfg );
	free( fftcfgi );
}

const float* WaveGroup::get_wave(int w /*0..GROUPC.-1*/) const
{
	float* d = wave_data + w * CYCLELEN;
	if (wave_exists[w])
	{
		return d;
	}

	wave_exists[w] = true;

	kiss_fft_cpx maskedfreqs[FREQ_DATALEN];

	// copy freqs
	int i = 0;
	for ( ; i != w ; ++i)
	{
		maskedfreqs[i].r = freqs[i].r;
		maskedfreqs[i].i = freqs[i].i;
	}

	for ( ; i != FREQ_DATALEN ; ++i)
	{
		maskedfreqs[i].r = 0.f;
		maskedfreqs[i].i = 0.f;
	}

	kiss_fftri( fftcfgi, maskedfreqs, d );

	return d;
}

