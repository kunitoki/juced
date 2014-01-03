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
#include <stdio.h>
#include <math.h>
#include "styles.h"
#include "mainwin.h"
#include "messages.h"



const char *Mainwin::_flogstr [31] = 
{
     "20",   0, 0, "40",   0, 0,  "80",   0, 0,  "160",  0, 0, "315",  0, 0,
     "630",  0, 0, "1k25", 0, 0,  "2k5",  0, 0,  "5k",   0, 0, "10k",  0, 0,
     "20k"
};     


const char *Mainwin::_f440str [31] = 
{
    0, "27.5", 0, 0, "55",   0, 0,  "110",   0, 0,  "220",  0, 0, "440",   0,
    0, "880",  0, 0, "1k76", 0, 0,  "3k52",  0, 0,  "7k04", 0, 0, "14.1k", 0,
    0
};     


Mainwin::Mainwin (X_window *parent, X_resman *xres, ITC_ctrl *audio) :
    X_window (parent, XPOS, YPOS, XDEF, YDEF, Colors.spect_bg), _state (50),
    _audio (audio), 
    _plotmap (0),
    _plotgc (0)
{
    X_hints   H;

    _xatom = XInternAtom (dpy (), "WM_DELETE_WINDOW", True);
    XSetWMProtocols (dpy (), win (), &_xatom, 1);
    _xatom = XInternAtom (dpy (), "WM_PROTOCOLS", True);

    H.position (XPOS, YPOS);
    H.size (XMIN, YMIN);
    H.minsize (XMIN, YMIN);
    H.maxsize (disp()->xsize(), disp()->ysize());
    H.sizeinc (20, 20);
    H.rname (xres->rname ());
    H.rclas (xres->rclas ());
    x_apply (&H); 

    _xs = XDEF - XSCW - XSCW - RMAR;
    _ys = YDEF - TMAR - YSCH - BMAR;
    _bwin1 = new X_window (this, XSCW + _xs + XSCW, 0, RMAR, 2000, Colors.main_bg);
    _bwin1->x_set_win_gravity (NorthEastGravity);
    _bwin1->x_map (); 
    _bwin2 = new X_window (this, 0, TMAR + _ys + YSCH, 2000, BMAR, Colors.main_bg);
    _bwin2->x_set_win_gravity (SouthWestGravity);
    _bwin2->x_map (); 

    _plotwin = new X_window (this, XSCW, TMAR, _xs, _ys, 0);
    new_plotmap ();
    _plotwin->x_map ();     

    _gui_input [0].init (_bwin1, this, 0,  4, 4);
    _gui_input [1].init (_bwin1, this, 1, 84, 4);
    _gui_analys.init (_bwin1, this, 4, 84);
    _gui_memory [0].init (_bwin1, this, 0,  4, 164);
    _gui_memory [1].init (_bwin1, this, 1, 84, 164);
    _gui_traces.init (_bwin1, this, 4, 226);
    _gui_display.init (_bwin2, this, 0, 2);

    x_add_events (ExposureMask | StructureNotifyMask);
    x_map ();
    _chan [0] = 0;
    _chan [1] = 0;
    _memX = 0;
    _memY = 0;
}


Mainwin::~Mainwin (void)
{
    delete _memX;
    delete _memY;
    delete _chan [0];
    delete _chan [1];
    x_unmap ();
    del_plotmap ();
}


void Mainwin::handle_event (XEvent *E)
{
    switch (E->type)
    {
    case Expose:
        expose ((XExposeEvent *) E);
        break;  

    case ConfigureNotify:
        resize ((XConfigureEvent *) E);
        break;

    case ClientMessage:
        message ((XClientMessageEvent *) E);
        break;
    }
}


void Mainwin::expose (XExposeEvent *E)
{
    if (E->count == 0) redraw ();
}


void Mainwin::resize (XConfigureEvent *E)
{
    _xs = E->width  - XSCW - XSCW - RMAR;
    _ys = E->height - TMAR - YSCH - BMAR;
    _plotwin->x_resize (_xs, _ys); 
    new_plotmap ();
    redraw ();
}


void Mainwin::message (XClientMessageEvent *E)
{
    if (E->message_type == _xatom) _state = 0;
}


void Mainwin::new_plotmap (void)
{
    del_plotmap ();
    _plotmap = XCreatePixmap (dpy (), _plotwin->win (), _xs, _ys, disp ()->depth ());
    _plotgc = XCreateGC (dpy (), _plotmap, 0, NULL);
    XSetWindowBackgroundPixmap (dpy (), _plotwin->win (), _plotmap);
}


void Mainwin::del_plotmap (void)
{
    if (!  _plotmap) return;
    XFreePixmap (dpy (), _plotmap);
    XFreeGC (dpy (), _plotgc);
}


void Mainwin::handle_callb (int k, X_window *W, _XEvent *E )
{
    int    c, d;
    Trace  *ts, *td;
 
    c = (k >> 16) - 1;
    k &= 0xFFFF;

    switch (k)
    {
    case CB_INPUT:
        _audio->put_event (EV_MESG, new M_input (_gui_input [0].get_input (), _gui_input [1].get_input ()));     
	break;

    case CB_GAIN:
        _gain [c] = powf (10.0f, 0.1f * _gui_input [c].get_gain ());
	if (c == 0 && _gui_input [1].get_link ())
	{
            _gui_input [1].set_gain (_gui_input [0].get_gain ());
            _gain [1] = _gain [0];
	} 
	break;

    case CB_AUTO:
        if (_gui_input [c].get_input () < 0) break;
        d = -5 * (int)(floorf (2 * log10 (_chan [c]->pmax ())));
        if (d < -10) d = -10;
        if (d >  60) d =  60;
        _gui_input [c].set_gain (d);
        _gain [c] = powf (10.0f, 0.1f * d);
	if (c == 0 && _gui_input [1].get_link ())
	{
            _gui_input [1].set_gain (d);
            _gain [1] = _gain [0];
	} 
	break;

    case CB_LINK:
        _gui_input [c].set_gain (_gui_input [0].get_gain ());
        _gain [c] = _gain [0];
	break;

    case CB_RESOL:
        set_resol ();
        break;

    case CB_WFACT:
        set_wfact ();
        if (_fmode == 2) redraw (); 
        break;

    case CB_SPEED:
        set_speed ();
	break;

    case CB_PEAK:
        assert (c >= 0);
        if (! _gui_memory [c].get_peak ()) _chan [c]->clr_peak ();       
	break;

    case CB_MEMX:
    case CB_MEMY:
        ts = (_gui_memory [c].get_peak ()) ? _chan [c]->peakp () : _chan [c]->power ();
        td = (k == CB_MEMX) ? _memX : _memY;
        set_memory (td, ts, _gain [c]);        
	break;

    case CB_ASCALE:
	_range = 20 * (_gui_display.get_ascale () + 1);
        redraw ();
        break;

    case CB_FSCALE:
	_fmode = _gui_display.get_fscale ();
        redraw ();
        break;
    }
}


void Mainwin::redraw (void)
{
    X_draw D (dpy (), win (), disp ()->dgc (), 0);

    if (_state > 1) show_about ();
    else
    {
        D.clearwin ();
        plot_ascale ();
        plot_fscale ();
        update ();
    }
}


void Mainwin::update (void)
{
    plot_grid ();
    plot_data ();
    _plotwin->x_clear ();
}


void Mainwin::show_about (void)
{
    int x, y;
    X_draw   D (dpy (), _plotmap, _plotgc, xft ());

    x = _xs / 2;
    y = _ys / 2;

    D.setfunc (GXcopy);
    D.setcolor (Colors.spect_bg);
    D.fillrect (0, 0, _xs, _ys);

    D.setfont (XftFonts.about1);
    D.setcolor (XftColors.spect_fg);
    D.move (x, y - 50);
    D.drawstring (PROGNAME, 0); 
    D.setfont (XftFonts.about2);
    D.move (x, y);
    D.drawstring ("(C) 2005 Fons Adriaensen", 0); 
    D.move (x, y + 50);
    D.drawstring ("This is free software, and you are welcome to distribute it", 0); 
    D.move (x, y + 70);
    D.drawstring ("under certain conditions. See the file COPYING for details.", 0); 

    _plotwin->x_clear ();
}


void Mainwin::set_resol (void)
{
    _xstep = (FFT_MAX / FFT_MIN)  >> _gui_analys.get_resol ();
    _chan [0]->set_fftlen (FFT_MAX / _xstep);
    _chan [1]->set_fftlen (FFT_MAX / _xstep);
    _memX->_valid = _memY->_valid = false;
}


void Mainwin::set_wfact (void)
{
    _wfact = _warps [_gui_analys.get_wfact ()];
    _chan [0]->set_wfact (_wfact);
    _chan [1]->set_wfact (_wfact);
    _memX->_valid = _memY->_valid = false;
    calc_fscales ();
}


void Mainwin::set_speed (void)
{
    float v;

    switch (_gui_analys.get_speed ())
    {
    case 0:  v = 20.00f; break;
    case 1:  v =  2.00f; break;
    case 2:  v =  0.20f; break;
    case 3:  v =  0.03f; break;
    default: v =  0.20f; break;
    }    
    _chan [0]->set_speed (v); 
    _chan [1]->set_speed (v); 
}


void Mainwin::set_memory (Trace *d, Trace *s, float gain)
{
    if (s->_valid)
    {
	d->_valid = true;
        for (int i = 0; i <= FFT_MAX / _xstep; i++) d->_data [i] = s->_data [i] * gain;
    }
}


void Mainwin::plot_ascale (void)
{
    int      i, n, v, y; 
    float    s;
    char     p [8];
    X_draw   D (dpy (), win (), dgc (), xft ());

    D.setfont (XftFonts.scales);
    D.setcolor (XftColors.spect_sc);
    D.setfunc (GXcopy);

    s = _ys - 1;
    _ytick = (_range == 20) ? 5 : 10;
    n = _range / _ytick;
    v = XftFonts.scales->ascent / 3;
    for (i = 0; i <= n; i++)
    {
	y = TMAR + (int)(i * s / n + 0.5);
        D.move (XSCW - 1, y);
        D.rdraw (-4, 0);
        D.rmove (-2, v);
        sprintf (p, "%d", _ytick * (1 - i));
        D.drawstring (p, 1);         
        D.move (XSCW +_xs, y);
        D.rdraw (4, 0);
        D.rmove (2, v);
        sprintf (p, "%d", _ytick * (n / 2 - i));
        D.drawstring (p, -1);         
    }
}


void Mainwin::plot_fscale (void)
{
    int         i, d, x, y;
    int         sk1, sk2; 
    float       s;
    const char  **p;
    X_draw      D (dpy (), win (), dgc (), xft ());

    D.setfont (XftFonts.scales);
    D.setcolor (XftColors.spect_sc);
    D.setfunc (GXcopy);

    p = _flogstr;
    s = _xs - 1;
    sk1 = sk2 = 0;
    if (_fmode == 2)
    {
        if (s * (_fmarks [6] - _fmarks [3]) < 26)
	{
	    sk1 |= (6 << 0) | (6 << 3);
            sk2 |= (1 << 3);
	}
        if (s * (_fmarks [9] - _fmarks [6]) < 26)
	{
	    sk1 |= (6 << 6);
            sk2 |= (1 << 6);
	}
        if (s * (_fmarks [30] - _fmarks [27]) < 26)
	{
	    sk1 |= (6 << 24) | (6 << 27);
            sk2 |= (1 << 27);
	}
    }
    else if (_fmode == 0) p = _f440str;

    d = XftFonts.scales->ascent + 2;
    x = 0;
    for (i = 0; i <= 30; i++, sk1 >>= 1, sk2 >>= 1) 
    {
        if (sk1 & 1) continue; 
        switch (_fmode)
        {
	case 0:
	    x = (int)((i + 0.3783) * s / 29.897f + 0.5);
	    break;

	case 1:
	    x = (int)(i * s / 30.0f + 0.5f);
	    break;

	case 2:
	    x = (int)(s * _fmarks [i] + 0.5f);
	    break;
	}
        if (x > _xs) break;
        y = TMAR + _ys;
        D.move (x + XSCW, y);
        D.rdraw (0, 4);
        if (sk2 & 1) continue;
        if (p [i])
	{
	    D.rmove (0, d);
            D.drawstring (p [i], 0);   
	}
    }        
}


void Mainwin::plot_grid (void)
{
    int     i, n, x, y;
    float   s;
    X_draw  D (dpy (), _plotmap, _plotgc, 0);

    D.setfunc (GXcopy);
    D.setcolor (Colors.spect_bg);
    D.fillrect (0, 0, _xs, _ys);
    D.setcolor (Colors.spect_gr);

    s = _xs - 1;
    x = 0;
    for (i = 0; i <= 30; i += 3) 
    {
        switch (_fmode)
        {
	case 0:
	    x = (int)((i + 1.3783) * s / 29.897f + 0.5);
	    break;

	case 1:
	    x = (int)(i * s / 30.0f + 0.5f);
	    break;

	case 2:
	    x = (int)(s * _fmarks [i] + 0.5f);
	    break;
	}
        if (x > _xs) break;
        D.move (x, 0);
        D.draw (x, _ys);
    }        
    if (_fmode == 0)
    {
        D.move (0, 0);
        D.draw (0, _ys);
        D.move (_xs - 1, 0);
        D.draw (_xs - 1, _ys);
    }

    s = _ys - 1;
    n = _range / _ytick;
    for (i = 0; i <= n; i++)    
    {
	y = (int)(i * s / n + 0.5);
        D.move (0, y);
        D.draw (_xs, y);
    }
}


void Mainwin::plot_data (void)
{
    Trace *trA, *pkA, *trB, *pkB;

    trA = _chan [0]->power ();
    pkA = _chan [0]->peakp ();
    trB = _chan [1]->power ();
    pkB = _chan [1]->peakp ();

    switch (_gui_traces.get_traceA ())
    {
    case 0:
        if (pkA->_valid) plot_trace (Colors.spect_pkA, pkA->_data, 0, _gain [0]);
        if (trA->_valid) plot_trace (Colors.spect_trA, trA->_data, 0, _gain [0]);
        break;

    case 1:
        if (pkA->_valid && pkB->_valid) plot_trace (Colors.spect_pkA, pkA->_data, pkB->_data, _gain [0] / _gain [1]); 
        if (trA->_valid && trB->_valid) plot_trace (Colors.spect_trA, trA->_data, trB->_data, _gain [0] / _gain [1]); 
        break;

    case 2:
	if (_memX->_valid)
	{
            if (pkA->_valid) plot_trace (Colors.spect_pkA, pkA->_data, _memX->_data, _gain [0]); 
            if (trA->_valid) plot_trace (Colors.spect_trA, trA->_data, _memX->_data, _gain [0]); 
	}
       break;
    }

    switch (_gui_traces.get_traceB ())
    {
    case 0:
       if (pkB->_valid) plot_trace (Colors.spect_pkB, pkB->_data, 0, _gain [1]);
       if (trB->_valid) plot_trace (Colors.spect_trB, trB->_data, 0, _gain [1]);
       break;

    case 1:
	if (_memX->_valid)
	{
            if (pkB->_valid) plot_trace (Colors.spect_pkB, pkB->_data, _memX->_data, _gain [1]); 
            if (trB->_valid) plot_trace (Colors.spect_trB, trB->_data, _memX->_data, _gain [1]); 
	}
        break;

    case 2:
	if (_memY->_valid)
	{
            if (pkB->_valid) plot_trace (Colors.spect_pkB, pkB->_data, _memY->_data, _gain [1]); 
            if (trB->_valid) plot_trace (Colors.spect_trB, trB->_data, _memY->_data, _gain [1]); 
	}
        break;
    }

    switch (_gui_traces.get_traceM ())
    {
    case 0:
        if (_memX->_valid) plot_trace (Colors.spect_trM, _memX->_data, 0, 1.0f);
        break;

    case 1:
        if (_memY->_valid) plot_trace (Colors.spect_trM, _memY->_data, 0, 1.0f);
        break;

    case 2:
        if (_memX->_valid && _memY->_valid) plot_trace (Colors.spect_trM, _memX->_data, _memY->_data, 1.0f); 
	break;
    }
}


void Mainwin::plot_trace (unsigned long color, float *tr1, float *tr2, float gain)
{
    int     i, n, ry;
    float   sx, sy, v; 
    XPoint  P [FFT_MAX + 1];
    X_draw  D (dpy (), _plotmap, _plotgc, 0);

    D.setline (0);
    D.setfunc (GXcopy);
    D.setcolor (color);

    sx = _xs - 1;
    sy = (_ys - 1.0f) / _range;
    ry = (int)(sy * (tr2 ? _range / 2 : _ytick) + 1000.5f);
    sy *= 10.0f;
 
    if (_fmode == 2)
    {
        sx /= _inds;
	for (i = n = 0; i <= FFT_MAX; i += _xstep)
	{
	    P [n++].x = (int)(sx * (i - _ind0) + 0.5f);
	}
    }
    else
    {
	for (i = n = 0; i <= FFT_MAX; i += _xstep)
	{
	    P [n++].x = (int)(sx * _fscale [i] + 0.5f);
	}
    }

    if (tr2)
    {
	for (i = n = 0; i <= FFT_MAX; i += _xstep)
	{
	    v = (*tr1++ + 1e-30) / (*tr2++ + 1e-30) * gain;
	    P [n++].y = ry - (int)(sy * log10f (v) + 1000.5f);
	}
    }
    else if (_gui_display.get_arespf ())
    {
	for (i = n = 0; i <= FFT_MAX; i += _xstep)
	{
	    v = (*tr1++ + 1e-30) / _bwcorr [i] * gain;
	    P [n++].y = ry - (int)(sy * log10f (v) + 1000.5f);
	}
    }
    else
    {
	for (i = n = 0; i <= FFT_MAX; i += _xstep)
	{
	    v = (*tr1++ + 1e-30) * gain;
	    P [n++].y = ry - (int)(sy * log10f (v) + 1000.5f);
	}
    }

    D.drawlines (n, P);
}


void Mainwin::handle_mesg (ITC_mesg *M)
{
    char s [256];

    if (M->type () == MT_AUDIO)
    {
        M_audio *Z = (M_audio *) M;
        _fsamp = Z->_fsamp;
        sprintf (s, "%s-%s  [%s]", PROGNAME, VERSION, Z->_name);
        x_set_title (s);
        init_analyser ();
        _audio->put_event (EV_MESG, new M_buffp (_chan [0]->ipdata (), _chan [1]->ipdata (), _ipsize, _ipstep));     
        _audio->put_event (EV_MESG, new M_input (_gui_input [0].get_input (), _gui_input [1].get_input ()));     
    }
    M->recover ();
}


void Mainwin::init_analyser (void)
{
    _ipstep = (_fsamp > 64e3f) ? 0x2000 : 0x1000;
    _ipsize= 2 * _ipstep;
    _chan [0] = new Analyser (_ipsize, FFT_MAX, _fsamp);
    _chan [1] = new Analyser (_ipsize, FFT_MAX, _fsamp);
    _memX = new Trace (FFT_MAX);
    _memY = new Trace (FFT_MAX);
    _fmode = _gui_display.get_fscale ();
    _range = 20 * (_gui_display.get_ascale () + 1);
    _gain [0] = powf (10.0f, 0.1f * _gui_input [0].get_gain ());
    _gain [1] = powf (10.0f, 0.1f * _gui_input [1].get_gain ());
    _warps [0] = 0.8517 * sqrt (atan (65.83e-6 * _fsamp)) - 0.1916;
    _warps [1] = 0.9000;
    _warps [2] = 0.9500;
    set_resol ();
    set_wfact ();
    set_speed ();
}


void Mainwin::handle_trig ()
{
    if (_state > 1)
    {
	if (--_state == 1) redraw ();
        _chan [0]->ipskip (_ipstep);
        _chan [1]->ipskip (_ipstep);
        return;
    }        
    if (_gui_input [0].get_input () < 0) _chan [0]->ipskip (_ipstep);
    else _chan [0]->process (_ipstep, _gui_memory [0].get_peak ());
    if (_gui_input [1].get_input () < 0) _chan [1]->ipskip (_ipstep);
    else _chan [1]->process (_ipstep, _gui_memory [1].get_peak ());
    update ();
}


double Mainwin::warp_freq (double w, double f)
{
    f *= 2 * M_PI;
    return fabs (atan2 ((1 - w * w) * sin (f), (1 + w * w) * cos (f) - 2 * w) / (2 * M_PI));
}


void Mainwin::calc_fscales (void)
{
    int    i;
    double f, g0, g1;

    g0 = warp_freq (_wfact, 20.0 / _fsamp);
    g1 = warp_freq (_wfact, 20e3 / _fsamp);
    _ind0 = 2 * FFT_MAX * g0;
    _inds = 2 * FFT_MAX * (g1 - g0);

    _fmarks [0] = 0.0f;
    for (i = 1; i < 30; i++)
    {
	f = 20.0 * pow (10.0, 0.1 * i) / _fsamp;
        _fmarks [i] = (warp_freq (_wfact, f) - g0) / (g1 - g0);
    }
    _fmarks [30] = 1.0f;

    for (i = 0; i <= FFT_MAX; i++)
    {
	f = 0.5 * i / FFT_MAX;
        _fscale [i] = warp_freq (-_wfact, f);
    }

    for (i = 1; i < FFT_MAX; i++)
    {
        _bwcorr [i] = 30.0f * (_fscale [i + 1] - _fscale [i - 1]) / _fscale [i];
    }
    _bwcorr [0]       = _bwcorr [1];
    _bwcorr [FFT_MAX] = _bwcorr [FFT_MAX - 1];

    _fscale [0] = -1;
    for (i = 1; i <= FFT_MAX; i++)
    {
        _fscale [i] = log10f (_fscale [i] * _fsamp / 20.0f) / 3.0f;
    }
}

#endif

