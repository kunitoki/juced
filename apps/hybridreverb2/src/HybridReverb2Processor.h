/***************************************************************************
 *   Copyright (C) 2009 by Christian Borss                                 *
 *   christian.borss@rub.de                                                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#ifndef __AUDIOPLUGIN_H__
#define __AUDIOPLUGIN_H__


#include "SampleData.h"
#include "HybridConvolver.h"
#include "HybridConvolverTripple.h"
#include "HybridConvolverDual.h"
#include "HybridConvolverSingle.h"
#include "Partitioner.h"
#include "ParamPreferences.h"
#include "ParamPartitionWisdom.h"


// forward declarations
class MasterAndCommander;


//==============================================================================
/**
    A simple plugin filter that just applies a gain change to the audio
    passing through it.

*/
class HybridReverb2Processor  : public AudioProcessor,
                     public ChangeBroadcaster
{
public:
    //==============================================================================
    HybridReverb2Processor();
    ~HybridReverb2Processor();

    //==============================================================================
    MasterAndCommander *getMaster() { return master; }

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();

    void processBlock (AudioSampleBuffer& buffer,
                       MidiBuffer& midiMessages);

    //==============================================================================
    AudioProcessorEditor* createEditor();

    //==============================================================================
    const String getName() const;

    int getNumParameters();

    float getParameter (int index);
    void setParameter (int index, float newValue);

    const String getParameterName (int index);
    const String getParameterText (int index);

    const String getInputChannelName (const int channelIndex) const;
    const String getOutputChannelName (const int channelIndex) const;
    bool isInputChannelStereoPair (int index) const;
    bool isOutputChannelStereoPair (int index) const;

    bool acceptsMidi() const;
    bool producesMidi() const;

    int getNumPrograms();
    int getCurrentProgram();
    void setCurrentProgram (int index);
    const String getProgramName (int index);
    void changeProgramName (int index, const String& newName);

    //==============================================================================
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);

    //==============================================================================
    void setNewFilterSet(SampleData *impulses);

    //==============================================================================
    // These properties are public so that our editor component can access them
    //  - a bit of a hacky way to do it, but it's only a demo!

    // this is kept up to date with the midi messages that arrive, and the UI component
    // registers with it so it can represent the incoming messages
//    MidiKeyboardState keyboardState;

    // this keeps a copy of the last set of time info that was acquired during an audio
    // callback - the UI component will read this and display it.
//    AudioPlayHead::CurrentPositionInfo lastPosInfo;

    // these are used to persist the UI's size - the values are stored along with the
    // filter's other parameters, and the UI component will update them when it gets
    // resized.
    int lastUIWidth, lastUIHeight;

    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    // this is our current preset - the UI and the host can access this by getting/setting
    // parameter 0.
    int currentPreset;
    MasterAndCommander *master;
    Partitioner *partitioner;
    HybridConvolver *convolver;
    HybridConvolver *newConvolver;
    ParamPreferences paramPreferences;
    ParamPartitionWisdom paramPartitionWisdom;
};


#endif
