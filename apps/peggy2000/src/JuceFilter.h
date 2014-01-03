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

   @author  rockhardbuns
   @tweaker Lucio Asnaghi

 ==============================================================================
*/

#ifndef __JUCETICE_PEGGY2000_FILTER_HEADER__
#define __JUCETICE_PEGGY2000_FILTER_HEADER__

#include "StandardHeader.h"
#include "JucePluginCharacteristics.h"

#include "parameters.h"
#include "synth/cSyntModule.h"
#include "synth/cChorus.h"
#include "synth/cDelay.h"
#include "synth/cArp.h"

//==============================================================================
class JuceFilter  : public AudioProcessor, public ChangeBroadcaster
{
public:

    JuceFilter();
    ~JuceFilter();

    const String getName() const { return JucePlugin_Name; }
    bool acceptsMidi() const { return JucePlugin_WantsMidiInput; }
    bool producesMidi() const { return JucePlugin_ProducesMidiOutput; }

    const String getInputChannelName (const int channelIndex) const;
    const String getOutputChannelName (const int channelIndex) const;
    bool isInputChannelStereoPair (int index) const;
    bool isOutputChannelStereoPair (int index) const;

    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();

    int getNumParameters();
    float getParameter (int index);
    void setParameter (int index, float newValue);
    const String getParameterName (int index);
    const String getParameterText (int index);

    String ProgName;

    int getNumPrograms()                                        { return 1; }
    int getCurrentProgram()                                     { return 0; }
    void setCurrentProgram (int index)                          { }
    const String getProgramName (int index)                     { return ProgName; }
    void changeProgramName (int index, const String& newName)   { ProgName = newName;}

    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);

    AudioProcessorEditor* createEditor();

    ParMan* Pars;
    AudioSampleBuffer* OutBuffer;
    cSyntModule* synt;
    cChorus* chorus;
    cDelay* delay;
    cArp* arp;

private:

};


#endif

