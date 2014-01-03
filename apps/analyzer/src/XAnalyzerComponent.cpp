/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2004 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2004 by Julian Storer.

 ------------------------------------------------------------------------------

 JUCE and JUCETICE can be redistributed and/or modified under the terms of
 the GNU General Public License, as published by the Free Software Foundation;
 either version 2 of the License, or (at your option) any later version.

 JUCE and JUCETICE are distributed in the hope that they will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with JUCE and JUCETICE; if not, visit www.gnu.org/licenses or write to
 Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 Boston, MA 02111-1307 USA

 ------------------------------------------------------------------------------

 If you'd like to release a closed-source product which uses JUCE, commercial
 licenses are also available: visit www.rawmaterialsoftware.com/juce for
 more information.

 ==============================================================================
*/

#include "XAnalyzerComponent.h"

const char *XAnalyzerComponent::_flogstr [31] = 
{
     "20",   0, 0, "40",   0, 0,  "80",   0, 0,  "160",  0, 0, "315",  0, 0,
     "630",  0, 0, "1k25", 0, 0,  "2k5",  0, 0,  "5k",   0, 0, "10k",  0, 0,
     "20k"
};     

const char *XAnalyzerComponent::_f440str [31] = 
{
    0, "27.5", 0, 0, "55",   0, 0,  "110",   0, 0,  "220",  0, 0, "440",   0,
    0, "880",  0, 0, "1k76", 0, 0,  "3k52",  0, 0,  "7k04", 0, 0, "14.1k", 0,
    0
};  

//==============================================================================
XAnalyzerComponent::XAnalyzerComponent (XAnalyzerPlugin* const ownerFilter_)
    : AudioProcessorEditor (ownerFilter_)
{
    DBG ("XAnalyzerComponent::XAnalyzerComponent");
    
    static JuceticeLookAndFeel juceticeLookAndFeel;
    LookAndFeel::setDefaultLookAndFeel (&juceticeLookAndFeel);

    _chan [0] = 0;
    _chan [1] = 0;
    _memX = 0;
    _memY = 0;
    _fsamp = 44100.0f;
    
    _xs = XDEF; // - XSCW - XSCW - RMAR;
    _ys = YDEF; // - TMAR - YSCH - BMAR;
    
    init_analyser ();

    // set filters    
    getFilter()->setDataBuffer (_chan [0]->ipdata (), _chan [1]->ipdata (), _ipsize, _ipstep);

    // register ourselves with the plugin - it will use its ChangeBroadcaster base
    // class to tell us when something has changed.
    getFilter()->addChangeListener (this);

    // set its size
    setSize (_xs, _ys);
    
    startTimer (1000 / 10);
}

XAnalyzerComponent::~XAnalyzerComponent()
{
    stopTimer ();

    DBG ("XAnalyzerComponent::~XAnalyzerComponent");

    getFilter()->setDataBuffer (0, 0, 0, 0);
    getFilter()->removeChangeListener (this);

    delete _memX;
    delete _memY;
    delete _chan [0];
    delete _chan [1];
}

//==============================================================================
void XAnalyzerComponent::resized()
{
    DBG ("XAnalyzerComponent::resized");
    
    _xs = getWidth()  - XSCW - XSCW - RMAR;
    _ys = getHeight() - TMAR - YSCH - BMAR;
}

//==============================================================================
void XAnalyzerComponent::paint (Graphics& g)
{
    g.fillAll (Colour (64, 64, 64));

    g.setFont (Font (10.0f));

    plot_ascale (g);
    plot_fscale (g);

    plot_grid (g);
    plot_data (g);
}

//==============================================================================
void XAnalyzerComponent::timerCallback ()
{
    {
        const ScopedLock sl (getFilter()->getCallbackLock ());
        _chan [0]->process (_ipstep, false /*_gui_memory [0].get_peak ()*/);
        _chan [1]->process (_ipstep, false /*_gui_memory [1].get_peak ()*/);
    }

    repaint ();
}

//==============================================================================
void XAnalyzerComponent::changeListenerCallback (void* source)
{
    DBG ("XAnalyzerComponent::changeListenerCallback");

    if (source == getFilter())
    {
    }
}

//==============================================================================
void XAnalyzerComponent::parameterChanged (AudioParameter* parameter, const int index)
{
}

//==============================================================================
void XAnalyzerComponent::init_analyser ()
{
    _ipstep = (_fsamp > 64e3f) ? 0x2000 : 0x1000;
    _ipsize = 2 * _ipstep;
    _chan [0] = new Analyser (_ipsize, FFT_MAX, _fsamp);
    _chan [1] = new Analyser (_ipsize, FFT_MAX, _fsamp);
    _memX = new Trace (FFT_MAX);
    _memY = new Trace (FFT_MAX);
    _fmode = 1 /*_gui_display.get_fscale ()*/;
    _range = 20 * (3 /*_gui_display.get_ascale ()*/ + 1);
    _gain [0] = powf (10.0f, 0.1f * 10.0f /*_gui_input [0].get_gain ()*/);
    _gain [1] = powf (10.0f, 0.1f * 10.0f /*_gui_input [1].get_gain ()*/);
    _warps [0] = 0.8517 * sqrt (atan (65.83e-6 * _fsamp)) - 0.1916;
    _warps [1] = 0.9000;
    _warps [2] = 0.9500;
    set_resol ();
    set_wfact ();
    set_speed ();
}

void XAnalyzerComponent::set_resol ()
{
    _xstep = (FFT_MAX / FFT_MIN) >> 0 /*_gui_analys.get_resol ()*/;
    _chan [0]->set_fftlen (FFT_MAX / _xstep);
    _chan [1]->set_fftlen (FFT_MAX / _xstep);
    _memX->_valid = _memY->_valid = false;
}

void XAnalyzerComponent::set_wfact ()
{
    _wfact = _warps [0 /*_gui_analys.get_wfact ()*/];
    _chan [0]->set_wfact (_wfact);
    _chan [1]->set_wfact (_wfact);
    _memX->_valid = _memY->_valid = false;
    calc_fscales ();
}

void XAnalyzerComponent::set_speed ()
{
    float v;

    switch (2 /*_gui_analys.get_speed ()*/)
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

void XAnalyzerComponent::set_memory (Trace *d, Trace *s, float gain)
{
    if (s->_valid)
    {
    	d->_valid = true;

        for (int i = 0; i <= FFT_MAX / _xstep; i++)
            d->_data [i] = s->_data [i] * gain;
    }
}

void XAnalyzerComponent::plot_ascale (Graphics& g)
{
    int      i, n, v, y; 
    float    s;
    char     p [8];
    float    ascent = Font (10.0f).getAscent();

    g.setColour (Colours::grey);

    s = _ys - 1;
    _ytick = (_range == 20) ? 5 : 10;
    n = _range / _ytick;
    v = ascent / 3;

    for (i = 0; i <= n; i++)
    {
    	y = TMAR + (int)(i * s / n + 0.5);

        sprintf (p, "%d", _ytick * (1 - i));

        g.drawLine (XSCW - 2, y, XSCW, y);
        g.drawSingleLineText (p, XSCW - 16, v + y);

        //D.move (XSCW - 1, y);
        //D.rdraw (-4, 0);
        //D.rmove (-2, v);
        //D.drawstring (p, 1);         

        //sprintf (p, "%d", _ytick * (n / 2 - i));

        g.drawLine (XSCW + _xs, y, XSCW + _xs + 2, y);
        g.drawSingleLineText (p, XSCW + _xs + 2, v + y);

        //D.move (XSCW +_xs, y);
        //D.rdraw (4, 0);
        //D.rmove (2, v);
        //D.drawstring (p, -1);         
    }
}

void XAnalyzerComponent::plot_fscale (Graphics& g)
{
    int         i, d, x, y;
    int         sk1, sk2; 
    float       s;
    const char  **p;
    float       ascent = Font (10.0f).getAscent();

    g.setColour (Colours::grey);

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

    d = ascent + 2;
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
        
        g.drawRect (x + XSCW, y, 1, 4);
        //D.move (x + XSCW, y);
        //D.rdraw (0, 4);

        if (sk2 & 1) continue;

        if (p [i])
	    {
	        g.drawSingleLineText (p [i], x + XSCW, y + 10);
	        //D.rmove (0, d);
            //D.drawstring (p [i], 0);
	    }
    }        
}

void XAnalyzerComponent::plot_grid (Graphics& g)
{
    int     i, n, x, y;
    float   s;

    g.setColour (Colours::grey);

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
        g.drawLine (x + XSCW, TMAR + 0, x + XSCW, TMAR + _ys);
    }

    if (_fmode == 0)
    {
        g.drawLine (0 + XSCW, TMAR + 0, 0 + XSCW, TMAR + _ys);
        g.drawLine (_xs - 1 + XSCW, TMAR + 0, _xs - 1 + XSCW, TMAR + _ys);
    }

    s = _ys - 1;
    n = _range / _ytick;
    for (i = 0; i <= n; i++)    
    {
    	y = TMAR + (int)(i * s / n + 0.5);
        g.drawLine (0 + XSCW, y, _xs + XSCW, y);
    }
}


void XAnalyzerComponent::plot_data (Graphics& g)
{
    Trace *trA, *pkA, *trB, *pkB;

    trA = _chan [0]->power ();
    pkA = _chan [0]->peakp ();
    trB = _chan [1]->power ();
    pkB = _chan [1]->peakp ();

    Colour spect_pkA = Colours::red;
    Colour spect_trA = Colours::red.brighter (0.5f);
    Colour spect_pkB = Colours::blue;
    Colour spect_trB = Colours::blue.brighter (0.5f);
    Colour spect_trM = Colours::green;

    switch (0 /*_gui_traces.get_traceA ()*/)
    {
    case 0:
        if (pkA->_valid) plot_trace (g, spect_pkA, pkA->_data, 0, _gain [0]);
        if (trA->_valid) plot_trace (g, spect_trA, trA->_data, 0, _gain [0]);
        break;

    case 1:
        if (pkA->_valid && pkB->_valid) plot_trace (g, spect_pkA, pkA->_data, pkB->_data, _gain [0] / _gain [1]); 
        if (trA->_valid && trB->_valid) plot_trace (g, spect_trA, trA->_data, trB->_data, _gain [0] / _gain [1]); 
        break;

    case 2:
       if (_memX->_valid)
       {
           if (pkA->_valid) plot_trace (g, spect_pkA, pkA->_data, _memX->_data, _gain [0]); 
           if (trA->_valid) plot_trace (g, spect_trA, trA->_data, _memX->_data, _gain [0]); 
       }
       break;
    }

    switch (0 /*_gui_traces.get_traceB ()*/)
    {
    case 0:
       if (pkB->_valid) plot_trace (g, spect_pkB, pkB->_data, 0, _gain [1]);
       if (trB->_valid) plot_trace (g, spect_trB, trB->_data, 0, _gain [1]);
       break;

    case 1:
	    if (_memX->_valid)
	    {
            if (pkB->_valid) plot_trace (g, spect_pkB, pkB->_data, _memX->_data, _gain [1]); 
            if (trB->_valid) plot_trace (g, spect_trB, trB->_data, _memX->_data, _gain [1]); 
	    }
        break;

    case 2:
	    if (_memY->_valid)
	    {
            if (pkB->_valid) plot_trace (g, spect_pkB, pkB->_data, _memY->_data, _gain [1]); 
            if (trB->_valid) plot_trace (g, spect_trB, trB->_data, _memY->_data, _gain [1]); 
	    }
        break;
    }

    switch (0 /*_gui_traces.get_traceM ()*/)
    {
    case 0:
        if (_memX->_valid)
            plot_trace (g, spect_trM, _memX->_data, 0, 1.0f);
        break;

    case 1:
        if (_memY->_valid)
            plot_trace (g, spect_trM, _memY->_data, 0, 1.0f);
        break;

    case 2:
        if (_memX->_valid && _memY->_valid)
            plot_trace (g, spect_trM, _memX->_data, _memY->_data, 1.0f); 
    	break;
    }
}

void XAnalyzerComponent::plot_trace (Graphics& g,
                                     const Colour& color,
                                     float *tr1,
                                     float *tr2,
                                     float gain)
{
    int     i, n, ry;
    float   sx, sy, v; 
    Point   P [FFT_MAX + 1];

    g.setColour (color);

    sx = _xs - 1;
    sy = (_ys - 1) / _range;
    ry = (int)(sy * (tr2 ? _range / 2 : _ytick) + 1000.5f);
    sy *= 10.0f;
 
    if (_fmode == 2)
    {
        sx /= _inds;
	    for (i = n = 0; i <= FFT_MAX; i += _xstep)
	    {
	        P [n].setXY ((sx * (i - _ind0) + 0.5f), P [n].getY());
	        n++;
	    }
    }
    else
    {
	    for (i = n = 0; i <= FFT_MAX; i += _xstep)
	    {
	        P [n].setXY ((sx * _fscale [i] + 0.5f), P [n].getY());
	        n++;
	    }
    }

    if (tr2)
    {
	    for (i = n = 0; i <= FFT_MAX; i += _xstep)
	    {
	        v = (*tr1++ + 1e-30) / (*tr2++ + 1e-30) * gain;
	        P [n].setXY (P [n].getX(), ry - (sy * log10f (v) + 1000.5f));
	        n++;
	    }
    }
    else if (0 /*_gui_display.get_arespf ()*/)
    {
	    for (i = n = 0; i <= FFT_MAX; i += _xstep)
	    {
	        v = (*tr1++ + 1e-30) / _bwcorr [i] * gain;
	        P [n].setXY (P [n].getX(), ry - (sy * log10f (v) + 1000.5f));
	        n++;
	    }
    }
    else
    {
	    for (i = n = 0; i <= FFT_MAX; i += _xstep)
	    {
	        v = (*tr1++ + 1e-30) * gain;
	        P [n].setXY (P [n].getX(), ry - (sy * log10f (v) + 1000.5f));
	        n++;
	    }
    }

//    Path path;
//    path.startNewSubPath (P[0].getX(), P[0].getY());

    for (i = 1; i < n; i++)
    {
//        path.lineTo (P[i].getX(), P[i].getY());

        g.drawLine (P[i-1].getX() + XSCW, TMAR + P[i-1].getY(),
                    P[i].getX() + XSCW,   TMAR + P[i].getY());
    }

//    g.strokePath (path, PathStrokeType (1.0f));
}

double XAnalyzerComponent::warp_freq (double w, double f)
{
    f *= 2 * M_PI;
    return fabs (atan2 ((1 - w * w) * sin (f), (1 + w * w) * cos (f) - 2 * w) / (2 * M_PI));
}

void XAnalyzerComponent::calc_fscales ()
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

