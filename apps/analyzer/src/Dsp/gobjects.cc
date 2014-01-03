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

#include "gobjects.h"


void GUI_select::init (X_window *W, X_callback *C, int k, int x, int y,
                       const char *label, const char **texts)
{
    X_textip  *T;

    _callb = C;
    _cbnum = k;
    _texts = texts;
    T = new X_textip (W, 0, &Tst1, x, y, 60, 17, 12);
    T->set_text (label);
    T->x_map ();    
    Bst0.size.x = 15;
    Bst0.size.y = 15;
    (new X_ibutton (W, this, &Bst0, x + 65, y + 1, W->disp ()->image1515 (X_display::IMG_LT), 0))->x_map ();
    (new X_ibutton (W, this, &Bst0, x + 80, y + 1, W->disp ()->image1515 (X_display::IMG_RT), 1))->x_map ();
    _tstat = new X_textip (W, this, &Tst0, x + 96, y, 45, 16, 8);
    _tstat->x_map ();
}


void GUI_select::handle_callb (int k, X_window *W, _XEvent *E)
{
    X_button  *B;
    int       d;

    if (k == (X_callback::BUTTON | X_button::PRESS))
    {
	B = (X_button *) W;
        d = 0;
        if (B->cbid ())  
        {
	    if (_texts [_state + 1]) d = 1;
	}
        else
	{
	    if (_state) d = -1;
	}
        if (d)
	{
	    set_state (_state + d);
            _callb->handle_callb (_cbnum, 0, 0);
	}
    }
}


void GUI_bgroup::init (X_window *W, X_callback *C, X_button_style *B, int k, int x, int y,
                       const char *label, const char **texts)
{
    X_textip  *T;
    int       i;

    _callb = C;
    _cbnum = k;
    T = new X_textip (W, 0, &Tst1, x, y, 40, 17, 12);
    T->set_text (label);
    T->x_map ();    
    B->size.x = 35;
    B->size.y = 17;
    for (i = 0; texts [i]; i++)
    {
	_butt [i] = new X_tbutton (W, this, B, x + 45 + 36 * i, y, texts [i], 0, i);
        _butt [i]->x_map ();
    }
    _state = -1;
}


void GUI_bgroup::set_state (int state)
{
    if (_state != state)
    {
	if (_state >= 0) _butt [_state]->set_stat (0);
        _state = state;
	if (_state >= 0) _butt [_state]->set_stat (1);
    }
}


void GUI_bgroup::handle_callb (int k, X_window *W, _XEvent *E)
{
    X_button  *B;
    int       i;

    if (k == (X_callback::BUTTON | X_button::PRESS))
    {
	B = (X_button *) W;
        i = B->cbid ();
        set_state (i == _state ? -1 : i);
        if (_cbnum) _callb->handle_callb (_cbnum, 0, 0);
    }
}


void GUI_input::init (X_window *W, X_callback *C, int k, int x, int y)
{
    int            i;
    char           s [8];
    X_textip       *T;
    X_button_style *B;
 
    _callb = C;
    _group = (k + 1) << 16;
    
    T = new X_textip (W, 0, &Tst1, x, y, 60, 17, 8);
    sprintf (s, "Input %c", 'A' + k);
    T->set_text (s);
    T->x_map ();    


    y += 18;
    B = k ? &BstB : &BstA;
    B->size.x = 17;
    B->size.y = 17;
    for (i = 0; i < 4; i++)
    {
	sprintf (s, "%d", i + 1);
	_binp [i] = new X_tbutton (W, this, B, x + 18 * i, y, s, 0, INP1 + i);
        _binp [i]->x_map ();
    }    
    if (k) _input = -1;
    else
    {
	_binp [0]->set_stat (1);
        _input = 0;
    }

    Bst0.size.x = 15;
    Bst0.size.y = 15;
    y += 18;
    (new X_ibutton (W, this, &Bst0, x,      y + 1, W->disp ()->image1515 (X_display::IMG_LT), DEC))->x_map ();
    (new X_ibutton (W, this, &Bst0, x + 16, y + 1, W->disp ()->image1515 (X_display::IMG_RT), INC))->x_map ();
    _tgain = new X_textip (W, this, &Tst0, x + 35, y, 38, 16, 8);
    _tgain->set_text ("10");
    _tgain->x_map ();
    _gain = 10.0f;
  
    y += 18;
    Bst0.size.x = 35;
    Bst0.size.y = 17;
    (new X_tbutton (W, this, &Bst0, x, y, "Aut", 0, AUTO))->x_map ();
    if (k)
    {
      _blink =new X_tbutton (W, this, &Bst0, x + 36, y, "Lnk", 0, LINK);
      _blink->x_map ();
    }
    else _blink = 0;
}


void GUI_input::set_gain (float gain)
{
    char s [8];
 
    _gain = gain;  
    sprintf (s, "%2.0lf", gain);
    _tgain->set_text (s);
}


void GUI_input::handle_callb (int k, X_window *W, _XEvent *E)
{
    X_button  *B;
    int       i;
    float     d;

    if (k == (X_callback::BUTTON | X_button::PRESS))
    {
	B = (X_button *) W;
        switch (i = B->cbid ())
	{
	case INP1:
	case INP2:
	case INP3:
	case INP4:
            i -= INP1; 
            if (B->stat ())
	    {
		_input = -1;
                B->set_stat (0);
	    }
	    else
	    {
		if (_input >= 0) _binp [_input]->set_stat (0);
                _input = i;
                B->set_stat (1); 
	    }
            _callb->handle_callb (_group | CB_INPUT, 0, 0);
            break;
  
	case DEC:
	case INC:
            if (_blink && _blink->stat ()) break;
            d = 0.0f;
            if (i == DEC && (_gain > -10.0f)) d = -5.0f; 
            if (i == INC && (_gain <  60.0f)) d =  5.0f; 
            if (d)
	    {
    		set_gain (_gain + d);
                _callb->handle_callb (_group | CB_GAIN, 0, 0);
	    }
	    break;

        case AUTO:
            if (_blink && _blink->stat ()) break;
            _callb->handle_callb (_group | CB_AUTO, 0, 0);
	    break;

        case LINK:
            if (B->stat ()) B->set_stat (0);
            else
	    {
                B->set_stat (1); 
               _callb->handle_callb (_group | CB_LINK, 0, 0);
	    }
	    break;
	}
    }
}


void GUI_analys::init (X_window *W, X_callback *C, int x, int y)
{
    X_textip  *T;

    T = new X_textip (W, 0, &Tst1, x + 50, y, 64, 17, 12);
    T->set_text ("Analyser");
    T->x_map ();
    _resol.init (W, C, CB_RESOL, x + 5, y + 18, "Resol", _resol_texts);
    _resol.set_state (1);
    _wfact.init (W, C, CB_WFACT, x + 5, y + 36, "Warp",  _wfact_texts);
    _wfact.set_state (0);
    _speed.init (W, C, CB_SPEED, x + 5, y + 54, "Speed", _speed_texts);
    _speed.set_state (2);
}

const char *GUI_analys::_resol_texts [] = { "Low" , "Med", "High", 0 };
const char *GUI_analys::_wfact_texts [] = { "Bark", "Med", "High", 0 };
const char *GUI_analys::_speed_texts [] = { "Noise", "Slow", "Med", "Fast", 0 };


void GUI_memory::init (X_window *W, X_callback *C, int k, int x, int y)
{
    char           s [8];
    X_textip       *T;
    X_button_style *B;
 
    _callb = C;
    _group = (k + 1) << 16;
    
    T = new X_textip (W, 0, &Tst1, x, y, 60, 17, 8);
    sprintf (s, "Store %c", 'A' + k);
    T->set_text (s);
    T->x_map ();    

    B = k ? &BstB : &BstA;
    B->size.x = Bst0.size.x = 36;
    B->size.y = Bst0.size.y = 17;
    (new X_tbutton (W, this, B    , x,      y + 18, "PkH", 0, CB_PEAK))->x_map ();
    (new X_tbutton (W, this, &Bst0, x,      y + 36, "->X", 0, CB_MEMX))->x_map ();
    (new X_tbutton (W, this, &Bst0, x + 36, y + 36, "->Y", 0, CB_MEMY))->x_map ();
    _peak = false;
}


void GUI_memory::handle_callb (int k, X_window *W, _XEvent *E)
{
    X_button  *B;
    int       i;

    if (k == (X_callback::BUTTON | X_button::PRESS))
    {
	B = (X_button *) W;
        i = B->cbid ();
        if (i == CB_PEAK) B->set_stat (_peak = ! B->stat ()); 
        _callb->handle_callb (_group | i, 0, 0);
    } 
}
    

void GUI_traces::init (X_window *W, X_callback *C, int x, int y)
{
    X_textip  *T;

    T = new X_textip (W, 0, &Tst1, x + 30, y, 64, 17, 12);
    T->set_text ("Traces");
    T->x_map ();
    _traceA.init (W, C, &BstA, CB_TRACEA, x, y + 18, "In A", _traceA_texts);
    _traceB.init (W, C, &BstB, CB_TRACEB, x, y + 36, "In B", _traceB_texts);
    _traceM.init (W, C, &BstM, CB_TRACEM, x, y + 54, "Mem",  _traceM_texts);
    _traceA.set_state (0);
}

const char *GUI_traces::_traceA_texts [] = { "A" , "A/B", "A/X", 0 };
const char *GUI_traces::_traceB_texts [] = { "B" , "B/X", "B/Y", 0 };
const char *GUI_traces::_traceM_texts [] = { "X" , "Y",   "X/Y", 0 };


void GUI_display::init (X_window *W, X_callback *C, int x, int y)
{
    _ascale.init (W, C, CB_ASCALE, x,       y, "Range", _ascale_texts);
    _ascale.set_state (1);
    _fscale.init (W, C, CB_FSCALE, x + 150, y, "Scale", _fscale_texts);
    _fscale.set_state (1);
    _arespf.init (W, C, CB_ARESPF, x + 300, y, "Resp",  _arespf_texts);
    _arespf.set_state (0);
}

const char *GUI_display::_ascale_texts [] = { "20", "40", "60", "80", 0 };
const char *GUI_display::_fscale_texts [] = { "440", "Log", "Warp", 0 };
const char *GUI_display::_arespf_texts [] = { "Flat" , "Prop", 0 };

#endif

