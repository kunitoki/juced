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

#ifndef __JUCETICE_XANALYZERPLUGIN_HEADER__
#define __JUCETICE_XANALYZERPLUGIN_HEADER__

#include "StandardHeader.h"
#include "JucePluginCharacteristics.h"

#include "Dsp/rngen.h"


//==============================================================================
/**
    Parameters enum definition
*/
enum
{
    PAR_GAIN = 0,

    NUM_PARAMETERS
};


class XAnalyzerComponent;

//==============================================================================
/**
    A simple plugin filter that just applies a gain change to its input.

*/
class XAnalyzerPlugin  : public AudioPlugin
{
public:

    //==============================================================================
    XAnalyzerPlugin();
    ~XAnalyzerPlugin();

    //==============================================================================
    const String getName() const          { return JucePlugin_Name; }
    bool acceptsMidi() const              { return JucePlugin_WantsMidiInput; }
    bool producesMidi() const             { return JucePlugin_ProducesMidiOutput; }

    //==============================================================================
    AudioProcessorEditor* createEditor();
    XAnalyzerComponent* getEditor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();
    void processBlock (AudioSampleBuffer& buffer,
                       MidiBuffer& midiMessages);

    //==============================================================================
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);

    void initialiseToDefault ();

    //==============================================================================
    juce_UseDebuggingNewOperator

    //==============================================================================
    static int numInstances;

protected:

    //==============================================================================
    friend class XAnalyzerComponent;

    void setDataBuffer (float* a, float* b, int ipsize, int ipstep);
    void generateNoise (int n, float *op1, float *op2 );

    enum { LRAND = 1024, MRAND = LRAND - 1 };

    volatile bool   _run_jack;
    void/*jack_client_t*/  *_jack_handle;
    void/*jack_port_t*/    *_jack_in [4];
    void/*jack_port_t*/    *_jack_out [2];

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

    //==============================================================================
    float getGain (int n);
    void setGain (int n, float newGain);

    AudioParameter params [NUM_PARAMETERS];
};


#endif
