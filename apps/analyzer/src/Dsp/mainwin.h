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


#ifndef __MAINWIN_H
#define __MAINWIN_H

#if 0

#include <clthreads.h>
#include <fftw3.h>
#include "clxclient.h"
#include "gobjects.h"
#include "analyser.h"


#define XPOS  100
#define YPOS  100
#define XMIN  700
#define YMIN  320
#define XDEF  XMIN
#define YDEF  YMIN
#define XMAX  1200
#define YMAX  800
#define XSCW  32
#define YSCH  20
#define RMAR  160
#define TMAR  8
#define BMAR  20

#define FFT_MIN 128
#define FFT_MAX 512


class Mainwin : public X_window, public X_callback
{
public:

    Mainwin (X_window *parent, X_resman *xres, ITC_ctrl *audio);
    ~Mainwin (void);
    bool running (void) const { return _state; }
    void handle_trig (void);
    void handle_term (void) { _state = 0; }
    void handle_mesg (ITC_mesg *);
 
private:

    virtual void handle_event (XEvent *xe);
    virtual void handle_callb (int, X_window*, _XEvent*);

    void new_plotmap (void);
    void del_plotmap (void);
    void message (XClientMessageEvent *);
    void expose (XExposeEvent *);
    void resize (XConfigureEvent *);
    void set_resol (void);
    void set_wfact (void);
    void set_speed (void);
    void set_memory (Trace *d, Trace *s, float gain);
    void redraw (void);
    void update (void);
    void plot_ascale (void);
    void plot_fscale (void);
    void plot_grid (void);
    void plot_data (void);
    void plot_trace (unsigned long color, float *tr1, float *tr2, float gain);
    void show_about (void);
    void init_analyser (void);
    void calc_fscales (void);   
    double warp_freq (double w, double f);

    int         _xs;
    int         _ys;
    int         _state;
    Atom        _xatom;
    ITC_ctrl   *_audio;

    X_window   *_plotwin;
    X_window   *_bwin1;
    X_window   *_bwin2;
    Pixmap      _plotmap;
    GC          _plotgc;
    GUI_input   _gui_input [2];
    GUI_analys  _gui_analys;
    GUI_memory  _gui_memory [2];
    GUI_traces  _gui_traces;
    GUI_display _gui_display;

    Analyser   *_chan [2];

    int         _ipsize;
    int         _ipstep;
    float       _fsamp;
    float       _warps [3];
    float       _wfact;
    float       _fmarks [31];
    float       _fscale [FFT_MAX + 1];
    float       _bwcorr [FFT_MAX + 1];
    int         _fmode;
    int         _range;
    int         _ytick;
    int         _xstep; 
    float       _gain [2]; 
    float       _ind0;
    float       _inds;
    Trace      *_memX;
    Trace      *_memY;

    static const char *_flogstr [31];
    static const char *_f440str [31];
};

#endif

#endif
