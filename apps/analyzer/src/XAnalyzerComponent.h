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

#ifndef __JUCETICE_XANALYZERCOMPONENT_HEADER__
#define __JUCETICE_XANALYZERCOMPONENT_HEADER__

#include "XAnalyzerPlugin.h"
#include "Dsp/analyser.h"

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


//==============================================================================
/**
    This is the Component that our filter will use as its UI.

*/
class XAnalyzerComponent  : public AudioProcessorEditor,
                            public AudioParameterListener,
                            public ChangeListener,
                            public Timer
{
public:

    //==============================================================================
    /** Constructor.
        When created, this will register itself with the filter for changes. It's
        safe to assume that the filter won't be deleted before this object is.
    */
    XAnalyzerComponent (XAnalyzerPlugin* const ownerFilter);

    /** Destructor. */
    ~XAnalyzerComponent ();

    //==============================================================================
    /** Our demo filter is a ChangeBroadcaster, and will call us back when one of
        its parameters changes.
    */
    void changeListenerCallback (void* source);

    /** Parameter listener callback */
    void parameterChanged (AudioParameter* parameter, const int index);

    //==============================================================================
    /**@internal*/
    void paint (Graphics& g);
    /**@internal*/
    void resized ();
    /**@internal*/
    void timerCallback ();

private:

    //==============================================================================
    friend class XAnalyzerPlugin;

    TooltipWindow tooltipWindow;

    void set_resol ();
    void set_wfact ();
    void set_speed ();
    void set_memory (Trace *d, Trace *s, float gain);

    void plot_ascale (Graphics& g);
    void plot_fscale (Graphics& g);
    void plot_grid (Graphics& g);
    void plot_data (Graphics& g);
    void plot_trace (Graphics& g, const Colour& color, float *tr1, float *tr2, float gain);

    void init_analyser ();
    void calc_fscales ();   
    double warp_freq (double w, double f);

    int         _xs;
    int         _ys;
    int         _state;

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


    // handy wrapper method to avoid having to cast the filter to a DemoJuceFilter
    // every time we need it..
    XAnalyzerPlugin* getFilter() const throw()  { return (XAnalyzerPlugin*) getAudioProcessor(); }
};


#endif // __JUCETICE_VECTORCOMPONENT_H
