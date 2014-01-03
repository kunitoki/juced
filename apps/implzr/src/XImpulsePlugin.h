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

#ifndef __JUCETICE_XIMPLZRPLUGIN_HEADER__
#define __JUCETICE_XIMPLZRPLUGIN_HEADER__

#include "StandardHeader.h"
#include "JucePluginCharacteristics.h"

#include "freeverb/irmodel2.hpp"
#include "freeverb/irmodel3.hpp"


//==============================================================================
/**
    Parameters enum definition
*/
enum
{
    PAR_GAIN = 0,

    NUM_PARAMETERS
};


class XImpulseComponent;

//==============================================================================
/**
    A simple plugin filter that just applies a gain change to its input.

*/
class XImpulsePlugin  : public AudioPlugin
{
public:

    //==============================================================================
    XImpulsePlugin();
    ~XImpulsePlugin();

    //==============================================================================
    const String getName() const          { return JucePlugin_Name; }
    bool acceptsMidi() const              { return JucePlugin_WantsMidiInput; }
    bool producesMidi() const             { return JucePlugin_ProducesMidiOutput; }

    //==============================================================================
    AudioProcessorEditor* createEditor();
    XImpulseComponent* getEditor();

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
    File getCurrentImpulseResponse () const         { return currentImpuseFile; }
    void loadImpulseResponse (const File& fileToLoad);

    //==============================================================================
    juce_UseDebuggingNewOperator

    //==============================================================================
    static int numInstances;

protected:

    //==============================================================================
    friend class XImpulseComponent;

    fv3::irmodel3_f* ir;
    float idb, odb;

    AudioSampleBuffer inputBuffers;

    File currentImpuseFile;
    AudioFormatManager formatManager;

    //==============================================================================
    float getGain (int n);
    void setGain (int n, float newGain);

    AudioParameter params [NUM_PARAMETERS];
};


#endif
