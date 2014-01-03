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

#ifndef __JUCETICE_XCOMPPLUGIN_HEADER__
#define __JUCETICE_XCOMPPLUGIN_HEADER__

#include "StandardHeader.h"
#include "JucePluginCharacteristics.h"
#include "../../capsaicin/src/Effects/EffectMgr.h"


//==============================================================================
/**
    Parameters enum definition
*/
enum
{
    PAR_GAIN = 0,
    PAR_DRYWET,
    PAR_BW,

    PAR_BAND1GAIN,
    PAR_BAND1ATTACK,
    PAR_BAND1RELEASE,
    PAR_BAND1THRESOLD,
    PAR_BAND1RATIO,
    PAR_BAND1KNEE,
    PAR_BAND1MAKEUP,

    PAR_BAND12SPLIT,

    PAR_BAND2GAIN,
    PAR_BAND2ATTACK,
    PAR_BAND2RELEASE,
    PAR_BAND2THRESOLD,
    PAR_BAND2RATIO,
    PAR_BAND2KNEE,
    PAR_BAND2MAKEUP,

    PAR_BAND23SPLIT,

    PAR_BAND3GAIN,
    PAR_BAND3ATTACK,
    PAR_BAND3RELEASE,
    PAR_BAND3THRESOLD,
    PAR_BAND3RATIO,
    PAR_BAND3KNEE,
    PAR_BAND3MAKEUP,

    NUM_PARAMETERS
};


class XCompComponent;

//==============================================================================
/**
    A simple plugin filter that just applies a gain change to its input.

*/
class XCompPlugin  : public AudioPlugin
{
public:

    //==============================================================================
    XCompPlugin();
    ~XCompPlugin();

    //==============================================================================
    const String getName() const          { return JucePlugin_Name; }
    bool acceptsMidi() const              { return JucePlugin_WantsMidiInput; }
    bool producesMidi() const             { return JucePlugin_ProducesMidiOutput; }

    //==============================================================================
    AudioProcessorEditor* createEditor();
    XCompComponent* getEditor();

    EffectMgr* getEqualizer (const int numBand);
    EffectMgr* getCompressor (const int numBand);

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
    friend class XCompComponent;

    CriticalSection dummy;
    EffectMgr* equalizer [3];
    EffectMgr* compressor [3];

    float outputGain;
    float outputDryWet;

    AudioSampleBuffer inputs;
    AudioSampleBuffer buffers;

    //==============================================================================
    float getGain (int n);
    void setGain (int n, float newGain);
    float getDryWet (int n);
    void setDryWet (int n, float newGain);
    float getBw (int n);
    void setBw (int n, float newGain);

    float getBandGain (int band);
    void setBandGain (int band, float newGain);
    float getBandFreq (int band);
    void setBandFreq (int band, float newGain);
    float getBandBw (int band);
    void setBandBw (int band, float newGain);

    float getBandAttack (int band);
    void setBandAttack (int band, float value);
    float getBandRelease (int band);
    void setBandRelease (int band, float value);
    float getBandThresold (int band);
    void setBandThresold (int band, float value);
    float getBandRatio (int band);
    void setBandRatio (int band, float value);
    float getBandKnee (int band);
    void setBandKnee (int band, float value);
    float getBandMakeup (int band);
    void setBandMakeup (int band, float value);

    AudioParameter params [NUM_PARAMETERS];
};


#endif
