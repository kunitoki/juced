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

#include <math.h>
#include "audio.h"
#include "messages.h"


Audio::Audio (ITC_ctrl *cmain, const char *name) :
    A_thread ("Audio"), _name (name), _cmain (cmain), _run_alsa (0), _run_jack (0),
    _inputA (-1), _inputB (-1), _dataA (0), _dataB (0), _frand (0), _out1 (0), _out2 (0)
{
}


Audio::~Audio (void)
{
    if (_run_alsa) close_alsa ();
    if (_run_jack) close_jack ();
    delete[] _frand;
    delete[] _out1;
    delete[] _out2;
}


void Audio::init (void)
{
    int   i;
    float s;

    _rngen.init (0);
    _frand = new float [LRAND];
    s = 0.0f;
    for (i = 0; i < LRAND; i++) s += _frand [i] = 0.5f * _rngen.grandf (); 
    s /= LRAND;
    for (i = 0; i < LRAND; i++) _frand [i] -= s;
    _b0 = _b1 = _b2 = _b3 = _b4 = _b5 = _b6 = 0.0f;
}


void Audio::init_alsa (const char *device, int fsamp, int fsize, int nfrags)
{
    _run_alsa = true;
    _alsa_handle = new Alsa_driver (device, fsamp, fsize, nfrags, true, true, false);
    if (_alsa_handle->stat () < 0)
    {
        fprintf (stderr, "Can't connect to ALSA\n");
        exit (1);
    } 
    _ncapt = _alsa_handle->ncapt ();
    _nplay = _alsa_handle->nplay ();
    _fsamp  = fsamp;
    _fsize = fsize;

    if (_nplay >= 2)
    {
	_out1 = new float [fsize];
	_out2 = new float [fsize];
    }

    init ();
   
    _cmain->put_event (EV_MESG, new M_audio (fsamp, _ncapt, _nplay, _name));
    _alsa_handle->printinfo ();
//    fprintf (stderr, "Connected to ALSA with %d inputs and %d outputs\n", _ncapt, _nplay); 

    if (thr_start (SCHED_FIFO, -10, 0x00010000))
    {
        fprintf (stderr, "Can't create ALSA thread with RT priority\n");
        if (thr_start (SCHED_OTHER, 0, 0x00010000))
        {
            fprintf (stderr, "Can't create ALSA thread\n");
            exit (1);
	}
    }
}


void Audio::close_alsa ()
{
//    fprintf (stderr, "Closing ALSA...\n");
    _run_alsa = false;
    get_event (1 << EV_EXIT);
    delete _alsa_handle;
}


void Audio::thr_main (void) 
{
    unsigned long k, m, n;

    _alsa_handle->pcm_start ();

    while (_run_alsa)
    {
	k = _alsa_handle->pcm_wait ();  
        while (k >= _fsize)
       	{
            if (_ncapt)
	    { 
		_alsa_handle->capt_init (_fsize);

		if (_dataA)
		{
		    m = _fsize;
		    n = _size - _dind;
		    if (m >= n)
		    {
			if (_inputA < 0) memset (_dataA + _dind, 0, n * sizeof (float));
                        else _alsa_handle->capt_chan (_inputA, _dataA + _dind, n);
			if (_inputB < 0) memset (_dataB + _dind, 0, n * sizeof (float));
                        else 
			{
			    if (_inputB == _inputA) memcpy (_dataB + _dind, _dataA + _dind, n * sizeof (float));
                            else _alsa_handle->capt_chan (_inputB, _dataB + _dind, n);
			}
			_dind = 0;
			m -= n;
		    }
		    if (m)
		    {
			if (_inputA < 0) memset (_dataA + _dind, 0, m * sizeof (float));
                        else _alsa_handle->capt_chan (_inputA, _dataA + _dind, m);
			if (_inputB < 0) memset (_dataB + _dind, 0, m * sizeof (float));
                        else
			{
			    if (_inputB == _inputA) memcpy (_dataB + _dind, _dataA + _dind, m * sizeof (float));
                            else _alsa_handle->capt_chan (_inputB, _dataB + _dind, m);
			}
			_dind += m;
		    }
		}

		_alsa_handle->capt_done (_fsize);
	    }

            if (_nplay)
	    {
		_alsa_handle->play_init (_fsize);

		if (_nplay >= 2)
		{
                    gen_noise (_fsize, _out1, _out2);
                    _alsa_handle->play_chan (0, _out1, _fsize);
                    _alsa_handle->play_chan (1, _out2, _fsize);
		}

		_alsa_handle->play_done (_fsize);
	    }

            k -= _fsize;
            _scnt += _fsize;
	}
        get_messages ();
    }

    _alsa_handle->pcm_stop ();
    put_event (EV_EXIT);
}


void Audio::init_jack (void)
{
    char           s [16];
    jack_status_t  stat;
    
    _run_jack = true;

    if ((_jack_handle = jack_client_open (_name, (jack_options_t) 0, &stat)) == 0)
    {
        fprintf (stderr, "Can't connect to JACK\n");
        exit (1);
    }

    jack_set_process_callback (_jack_handle, jack_static_callback, (void *)this);
    jack_on_shutdown (_jack_handle, jack_static_shutdown, (void *)this);

    _ncapt = 4;
    for (int i = 0; i < _ncapt; i++)
    {
        sprintf(s, "in_%d", i + 1);
        _jack_in [i] = jack_port_register (_jack_handle, s, JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
    }

    _nplay = 2;
    _jack_out [0] = jack_port_register (_jack_handle, "white", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
    _jack_out [1] = jack_port_register (_jack_handle, "pink",  JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);

    init ();
    
    if (jack_activate (_jack_handle))
    {
        fprintf(stderr, "Can't activate JACK");
        exit (1);
    }

    _fsamp = jack_get_sample_rate (_jack_handle);
    _fsize = jack_get_buffer_size (_jack_handle);
    _name = jack_get_client_name (_jack_handle);
    _cmain->put_event (EV_MESG, new M_audio (_fsamp, _ncapt, _nplay, _name));
//    fprintf (stderr, "Connected to JACK with %d inputs and %d outputs\n", _ncapt, _nplay); 
}


void Audio::close_jack ()
{
//    fprintf (stderr, "Closing JACK...\n");
    jack_deactivate (_jack_handle);
//    for (int i = 0; i < _nplay; i++) jack_port_unregister(_jack_handle, _jack_out[i]);
//    for (int i = 0; i < _ncapt; i++) jack_port_unregister(_jack_handle, _jack_in[i]);
    jack_client_close (_jack_handle);
}


void Audio::jack_static_shutdown (void *arg)
{
    return ((Audio *) arg)->jack_shutdown ();
}


void Audio::jack_shutdown (void)
{
    _cmain->put_event (EV_JACK);
}


int Audio::jack_static_callback (jack_nframes_t nframes, void *arg)
{
    return ((Audio *) arg)->jack_callback (nframes);
}


int Audio::jack_callback (jack_nframes_t nframes)
{
    unsigned long  m, n;
    float  *pA, *pB;

    if (_dataA)
    {
        pA = (_inputA >= 0) ? (float *)(jack_port_get_buffer (_jack_in [_inputA], nframes)) : 0;
        pB = (_inputB >= 0) ? (float *)(jack_port_get_buffer (_jack_in [_inputB], nframes)) : 0;
	m = nframes;
        n = _size - _dind;
        if (m >= n)
	{
            if (pA) memcpy (_dataA + _dind, pA, sizeof(float) * n);
	    else    memset (_dataA + _dind, 0,  sizeof(float) * n);
            if (pB) memcpy (_dataB + _dind, pB, sizeof(float) * n);
	    else    memset (_dataB + _dind, 0,  sizeof(float) * n);
            m -= n;
            pA += n;
            pB += n;
            _dind = 0;
        }
        if (m)
	{
            if (pA) memcpy (_dataA + _dind, pA, sizeof(float) * m);
	    else    memset (_dataA + _dind, 0,  sizeof(float) * m);
            if (pB) memcpy (_dataB + _dind, pB, sizeof(float) * m);
	    else    memset (_dataB + _dind, 0,  sizeof(float) * m);
            _dind += m;
	}
        _scnt += nframes;
    }

    gen_noise (nframes, 
               (float *)(jack_port_get_buffer (_jack_out [0], nframes)),
               (float *)(jack_port_get_buffer (_jack_out [1], nframes)));

    get_messages ();

    return 0;
}


void Audio::gen_noise (int n, float *op1, float *op2 ) 
{
    float x;

    while (n--)
    {
        x  = _frand [_rngen.irand () & MRAND]
           + _frand [_rngen.irand () & MRAND]
           + _frand [_rngen.irand () & MRAND]
           + _frand [_rngen.irand () & MRAND];
	*op1++ = 0.07071f * x;       	   
        x *= 0.023f;
        _b0 = 0.99886f * _b0 + 0.0555179f * x;
        _b1 = 0.99332f * _b1 + 0.0750759f * x;
        _b2 = 0.96900f * _b2 + 0.1538520f * x;
        _b3 = 0.86650f * _b3 + 0.3104856f * x;
        _b4 = 0.55000f * _b4 + 0.5329522f * x;
        _b5 = -0.7616f * _b5 - 0.0168980f * x;
        *op2++ = _b0 + _b1 + _b2 + _b3 + _b4 + _b5 + _b6 + x * 0.5362f;
        _b6 = x * 0.115926f;
    }
}


void Audio::get_messages (void) 
{
    int       k;
    ITC_mesg *M;

    if (_dataA)
    {
        k = _scnt / _step;
        if (k && _cmain->put_event_try (EV_TRIG, k) == ITC_ctrl::NO_ERROR) _scnt -= k * _step;
    }
   
    if (get_event_nowait (1 << EV_MESG) == EV_MESG)
    {
	M = get_message ();
	if (M->type () == MT_BUFFP)
	{
	    M_buffp *Z = (M_buffp *) M; 
	    _dataA = Z->_dataA;
	    _dataB = Z->_dataB;
	    _size  = Z->_size;
	    _step  = Z->_step; 
	    _dind  = 0;
	    _scnt  = 0;
	}
	else if (M->type () == MT_INPUT)
	{
	    M_input *Z = (M_input *) M; 
	    _inputA = Z->_inputA;
	    _inputB = Z->_inputB;
            if (_inputA >= _ncapt) _inputA = -1; 
            if (_inputB >= _ncapt) _inputB = -1; 
	}
	M->recover ();
    }
}

#endif

