/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2008 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2008 by Julian Storer.

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

   @author  haydxn
   @tweaker Lucio Asnaghi

 ==============================================================================
*/

#ifndef __JUCETICE_MIDINOTEMAPFILTER_HEADER__
#define __JUCETICE_MIDINOTEMAPFILTER_HEADER__

#include "StandardHeader.h"
#include "JucePluginCharacteristics.h"
#include "NoteMap.h"

//==============================================================================
/**

*/
class MidiNoteMapFilter  : public AudioProcessor,
                           public ChangeBroadcaster
{
public:
    //==============================================================================
    MidiNoteMapFilter();
    ~MidiNoteMapFilter();

    //==============================================================================
    const String getName() const          { return JucePlugin_Name; }
    bool acceptsMidi() const              { return JucePlugin_WantsMidiInput; }
    bool producesMidi() const             { return JucePlugin_ProducesMidiOutput; }

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();

    void processBlock (AudioSampleBuffer& buffer,
                       MidiBuffer& midiMessages);

    //==============================================================================
    AudioProcessorEditor* createEditor();

    //==============================================================================
    int getNumParameters();

    float getParameter (int index);
    void setParameter (int index, float newValue);

    const String getParameterName (int index);
    const String getParameterText (int index);

    //==============================================================================
    int getNumPrograms()                                        { return 0; }
    int getCurrentProgram()                                     { return 0; }
    void setCurrentProgram (int index)                          { }
    const String getProgramName (int index)                     { return String::empty; }
    void changeProgramName (int index, const String& newName)   { }

    //==============================================================================
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);

    //==============================================================================
    const String getInputChannelName (int channel) const        { return String (channel + 1); }
    const String getOutputChannelName (int channel) const       { return String (channel + 1); }
    bool isInputChannelStereoPair (int channel) const           { return true; }
    bool isOutputChannelStereoPair (int channel) const          { return true; }

    //==============================================================================
    // These properties are public so that our editor component can access them
    //  - a bit of a hacky way to do it, but it's only a demo!

    // this is kept up to date with the midi messages that arrive, and the UI component
    // registers with it so it can represent the incoming messages
    MidiKeyboardState keyboardState;

    // this keeps a copy of the last set of time info that was acquired during an audio
    // callback - the UI component will read this and display it.
    AudioPlayHead::CurrentPositionInfo lastPosInfo;

    // these are used to persist the UI's size - the values are stored along with the
    // filter's other parameters, and the UI component will update them when it gets
    // resized.
    int lastUIWidth, lastUIHeight;

    NoteMap* getMap (int channel = 1);
    SixteenChannelMaps& getChannelMaps ();

    //==============================================================================
    juce_UseDebuggingNewOperator

private:

    SixteenChannelMaps maps;
    MidiBuffer midiOutput;
};

#endif
