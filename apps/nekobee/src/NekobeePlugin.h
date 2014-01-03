/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2008 by Lucio Asnaghi.

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

#ifndef __JUCETICE_NEKOBEEPLUGIN_HEADER__
#define __JUCETICE_NEKOBEEPLUGIN_HEADER__

#include "NekobeeGlobals.h"


//==============================================================================
/**
    Parameters enum definition
*/
enum
{
    PAR_TUNING = 0,
    PAR_WAVEFORM,
    PAR_CUTOFF,
    PAR_RESONANCE,
    PAR_ENVMOD,
    PAR_DECAY,
    PAR_ACCENT,
    PAR_VOLUME,

    NUM_PARAMETERS
};


class NekobeeComponent;

//==============================================================================
/**
    A simple plugin filter that just applies a gain change to its input.

*/
class NekobeePlugin  : public AudioPlugin
{
public:

    //==============================================================================
    NekobeePlugin();
    ~NekobeePlugin();

    //==============================================================================
    const String getName() const          { return JucePlugin_Name; }
    bool acceptsMidi() const              { return JucePlugin_WantsMidiInput; }
    bool producesMidi() const             { return JucePlugin_ProducesMidiOutput; }

    //==============================================================================
    AudioProcessorEditor* createEditor();
    NekobeeComponent* getEditor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();
    void processBlock (AudioSampleBuffer& buffer,
                       MidiBuffer& midiMessages);

    //==============================================================================
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);

    //==============================================================================
    static int numInstances;
    
    //==============================================================================
    juce_UseDebuggingNewOperator

protected:

    //==============================================================================
    friend class NekobeeComponent;

    const DSSI_Descriptor* dssi;
    const LADSPA_Descriptor* ladspa;
    LADSPA_Handle plugin;

    float         tuning;
    float         waveform;
    float         cutoff;
    float         resonance;
    float         envmod;
    float         decay;
    float         accent;
    float         volume;
    
    AudioSampleBuffer output;
    DssiPluginMidiManager midiManager;

    //==============================================================================
    float getTuning (int n);
    void setTuning (int n, float v);
    float getWaveform (int n);
    void setWaveform (int n, float v);
    float getCutoff (int n);
    void setCutoff (int n, float v);
    float getResonance (int n);
    void setResonance (int n, float v);
    float getEnvmod (int n);
    void setEnvmod (int n, float v);
    float getDecay (int n);
    void setDecay (int n, float v);
    float getAccent (int n);
    void setAccent (int n, float v);
    float getVolume (int n);
    void setVolume (int n, float v);

    AudioParameter params [NUM_PARAMETERS];
};


#endif
