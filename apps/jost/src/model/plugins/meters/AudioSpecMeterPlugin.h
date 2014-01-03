/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2007 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2007 by Julian Storer.

 ------------------------------------------------------------------------------

 JUCE and JUCETICE can be redistributed and/or modified under the terms of
 the GNU Lesser General Public License, as published by the Free Software
 Foundation; either version 2 of the License, or (at your option) any later
 version.

 JUCE and JUCETICE are distributed in the hope that they will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with JUCE and JUCETICE; if not, visit www.gnu.org/licenses or write to
 Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 Boston, MA 02111-1307 USA

 ==============================================================================

    Original plugin: Paul Kellett (mda-vst.com)

 ==============================================================================
*/

#ifndef __JUCETICE_JOSTAUDIOSPECMETERPLUGIN_HEADER__
#define __JUCETICE_JOSTAUDIOSPECMETERPLUGIN_HEADER__

#include "../../BasePlugin.h"




//==============================================================================
class AudioSpecMeterPlugin : public BasePlugin
{
public:

    //==============================================================================
    enum 
    {
	    _PARAM0, //peak decay
	    _PARAM1, //RMS speed
	    _PARAM2, //spectrum speed
	    _PARAM3, //peak reset?

	    NPARAMS
    };

    //==============================================================================
    AudioSpecMeterPlugin ();
    ~AudioSpecMeterPlugin ();

    //==============================================================================
    int getType () const                 { return JOST_PLUGINTYPE_AUDIOSPECMETER; }

    //==============================================================================
    const String getName () const        { return T("Audio Meter"); }
    int getNumInputs () const            { return 2; }
    int getNumOutputs () const           { return 0; }
    int getNumMidiInputs () const        { return 0; }
    int getNumMidiOutputs () const       { return 0; }
    bool canReceiveMidiEvents () const   { return false; }
    bool canSendMidiEvents () const      { return false; }
    bool isMidiOutput () const           { return false; }

    //==============================================================================
    bool hasEditor () const              { return true; }
    bool wantsEditor () const            { return true; }
    bool isEditorInternal () const       { return true; }
    AudioProcessorEditor* createEditor ();

    //==============================================================================
    void setParameter (int paramNumber, float value);
    float getParameter (int paramNumber);
    const String getParameterName (int paramNumber);
    const String getParameterText (int paramNumber);

    //==============================================================================
    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();

    //==============================================================================
    long  counter;
    float Lpeak, Lhold, Lmin, Lrms, Rpeak, Rhold, Rmin, Rrms, Corr; // #11  #12
    float band[2][16]; //8  16  31  64  125  250  500  1k  2k  4k  8k  16k  32k
 
private:

	float param[NPARAMS];

    float iK, lpeak, lmin, lrms, rpeak, rmin, rrms, corr, den;
    float lpp[6][16], rpp[6][16];
    long  topband, K, kmax;

    float gain;
};


#endif

