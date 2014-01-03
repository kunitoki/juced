//  ----------------------------------------------------------------------------
//
//  Copyright (C) 2004-2008 Fons Adriaensen <fons@kokkinizita.net>
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
//  ----------------------------------------------------------------------------


#ifndef __ANALYSER_H
#define __ANALYSER_H

#define USE_KISS_FFT 1

#ifndef USE_KISS_FFT
 #include <fftw3.h>
#else
 #include "../../../../juce/src/extended/dependancies/kissfft/kiss_fftr.h"
#endif


class Trace
{
public:

    Trace (int size);
    ~Trace (void);

    bool   _valid;
    float *_data;
};


class Analyser
{
public:

    Analyser (int ipsize, int maxfft, float fsamp);
    ~Analyser (void);

    void set_fftlen (int fftlen);
    void set_wfact (float wfact);
    void set_speed (float speed);
    void clr_peak (void);
    void ipskip (int iplen) { _icount += iplen; if (_icount >= _ipsize) _icount -= _ipsize; _power->_valid = false; }
    void process (int iplen, bool phold);

    float *ipdata (void) const { return _ipdata; }
    Trace *power (void)  const { return _power; }
    Trace *peakp (void)  const { return _peakp; }
    float  pmax (void) const { return _pmax; }

private:

#ifndef USE_KISS_FFT
    float conv0 (fftwf_complex *);
    float conv1 (fftwf_complex *);
#else
    float conv0 (kiss_fft_cpx *);
    float conv1 (kiss_fft_cpx *);
#endif

    int              _ipsize;
    int              _icount;
    int              _fftmax;
    int              _fftlen;
#ifndef USE_KISS_FFT
    fftwf_plan       _fftplan;
#else
    kiss_fftr_cfg    _fftplan;
#endif
    float           *_ipdata;
    float           *_warped;
#ifndef USE_KISS_FFT
    fftwf_complex   *_trdata;
#else
    kiss_fft_cpx    *_trdata;
#endif
    Trace           *_power;
    Trace           *_peakp;
    float            _fsamp;
    float            _wfact;
    float            _speed;
    float            _pmax;
    float            _ptot;
};


#endif
