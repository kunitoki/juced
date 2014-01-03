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


#if 0

#include <stdlib.h>
#include <math.h>
#include "rngen.h"


class Audio
{
public:

    Audio ();
    virtual ~Audio ();

    void  init_alsa (const char *device, int fsamp, int frsize, int nfrags);
    void  init_jack (void);

private:

    

    virtual void thr_main (void);

    void  init (void);
    void  close_alsa (void);
    void  close_jack (void);
    void  gen_noise (int n, float *op1, float *op2);
    void  get_messages (void);
    void  jack_shutdown (void);
    int   jack_callback (jack_nframes_t nframes);

    const char *    _name;
    ITC_ctrl       *_cmain;

    volatile bool   _run_alsa;
    Alsa_driver    *_alsa_handle;

    volatile bool   _run_jack;
    jack_client_t  *_jack_handle;
    jack_port_t    *_jack_in [4];
    jack_port_t    *_jack_out [2];

    unsigned long  _fsamp;
    unsigned long  _fsize;
    int            _ncapt;
    int            _nplay;
    int            _inputA;
    int            _inputB;
    float         *_dataA;
    float         *_dataB;
    int            _dind;
    int            _size;
    int            _step;
    int            _scnt;
    Rngen          _rngen;
    float         *_frand;
    float         *_out1;
    float         *_out2;
    float          _b0, _b1, _b2, _b3, _b4, _b5, _b6;
  
    static void jack_static_shutdown (void *arg);
    static int  jack_static_callback (jack_nframes_t nframes, void *arg);
};

#endif

