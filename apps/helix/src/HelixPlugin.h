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

#ifndef __JUCETICE_HELIXPLUGIN_HEADER__
#define __JUCETICE_HELIXPLUGIN_HEADER__

#include "HelixGlobals.h"


//==============================================================================
/**
    Parameters enum definition
*/
enum
{
    PAR_NONE = 0,
    NUM_PARAMETERS
};


class HelixComponent;

//==============================================================================
/**
    A simple plugin filter that just applies a gain change to its input.

*/
class HelixPlugin  : public AudioPlugin
{
public:

    //==============================================================================
    HelixPlugin();
    ~HelixPlugin();

    //==============================================================================
    const String getName() const          { return JucePlugin_Name; }
    bool acceptsMidi() const              { return JucePlugin_WantsMidiInput; }
    bool producesMidi() const             { return JucePlugin_ProducesMidiOutput; }

    //==============================================================================
    AudioProcessorEditor* createEditor();
    HelixComponent* getEditor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();
    void processBlock (AudioSampleBuffer& buffer,
                       MidiBuffer& midiMessages);

    //==============================================================================
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);

    //==============================================================================
    float getGenericParameter (int n);
    void setGenericParameter (int n, float v);

    const String getParameterDisplay (int, float);
    String getParameterNameLong (int index);

    //==============================================================================
    static int numInstances;
    
    //==============================================================================
    juce_UseDebuggingNewOperator

protected:

    //==============================================================================
    friend class HelixComponent;

    Synth s;
};


#endif
