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


#ifndef __GOBJECTS_H
#define __GOBJECTS_H

#if 0

#include "styles.h"


enum 
{
    CB_INPUT,
    CB_GAIN,
    CB_AUTO,
    CB_LINK,
    CB_PEAK,
    CB_MEMX,
    CB_MEMY,
    CB_RESOL,
    CB_WFACT,
    CB_SPEED,
    CB_TRACEA,
    CB_TRACEB,
    CB_TRACEM,
    CB_ASCALE,
    CB_FSCALE,
    CB_ARESPF
};
 

class GUI_select : public X_callback
{
public:

    void init (X_window *W, X_callback *C, int k, int x, int y,
               const char *label, const char **texts);
    int  get_state (void) const { return _state; }
    void set_state (int state) { _tstat->set_text (_texts [_state = state]); }

    virtual ~GUI_select (void) {}

private:

    virtual void handle_callb (int k, X_window *W, _XEvent *E);

    X_callback  *_callb;
    X_textip    *_tstat;
    int          _cbnum;
    int          _state;
    const char **_texts;
};


class GUI_bgroup : public X_callback
{
public:

    void init (X_window *W, X_callback *C, X_button_style *B, int k, int x, int y, 
               const char *label, const char **texts);
    int  get_state (void) const { return _state; }
    void set_state (int state);

    virtual ~GUI_bgroup (void) {}

private:

    virtual void handle_callb (int k, X_window *W, _XEvent *E);

    X_callback  *_callb;
    X_button    *_butt [3];
    int          _cbnum;
    int          _state;
};


class GUI_input : public X_callback
{
public:

    void init (X_window *W, X_callback *C, int k, int x0, int y0);    
    int   get_input (void) const { return _input; }
    float get_gain  (void) const { return _gain; }
    bool  get_link  (void) const { return _blink ? _blink->stat () : 0; }
    void  set_gain (float g);

    virtual ~GUI_input (void) {}

private:

    enum { INP1, INP2, INP3, INP4, DEC, INC, AUTO, LINK };

    virtual void handle_callb (int k, X_window *W, _XEvent *E);
    
    X_callback *_callb;
    X_button   *_binp [4];
    X_textip   *_tgain;
    X_button   *_blink;
    int         _group;
    int         _input;
    float       _gain;
};


class GUI_analys
{
public:

    void init (X_window *W, X_callback *C, int x, int y);    
    int get_resol (void) const { return _resol.get_state (); } 
    int get_wfact (void) const { return _wfact.get_state (); } 
    int get_speed (void) const { return _speed.get_state (); } 

private:

    GUI_select  _resol;
    GUI_select  _wfact;
    GUI_select  _speed;    

    static const char *_resol_texts [];
    static const char *_wfact_texts [];
    static const char *_speed_texts [];
};


class GUI_memory : public X_callback
{
public:

    void init (X_window *W, X_callback *C, int k, int x, int y);    
    bool get_peak (void) const { return _peak; }

    virtual ~GUI_memory (void) {}

private:

    virtual void handle_callb (int k, X_window *W, _XEvent *E);
    
    X_callback *_callb;
    int         _group;
    bool        _peak; 
};


class GUI_traces
{
public:

    void init (X_window *W, X_callback *C, int x, int y);    
    int get_traceA (void) const { return _traceA.get_state (); } 
    int get_traceB (void) const { return _traceB.get_state (); } 
    int get_traceM (void) const { return _traceM.get_state (); } 

private:

    GUI_bgroup  _traceA;
    GUI_bgroup  _traceB;
    GUI_bgroup  _traceM;

    static const char *_traceA_texts [];
    static const char *_traceB_texts [];
    static const char *_traceM_texts [];
};


class GUI_display
{
public:

    void init (X_window *W, X_callback *C, int x, int y);    
    int get_ascale (void) const { return _ascale.get_state (); } 
    int get_fscale (void) const { return _fscale.get_state (); } 
    int get_arespf (void) const { return _arespf.get_state (); } 

private:

    GUI_select  _ascale;
    GUI_select  _fscale;
    GUI_select  _arespf;

    static const char *_ascale_texts [];
    static const char *_fscale_texts [];
    static const char *_arespf_texts [];
};

#endif

#endif

