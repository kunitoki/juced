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

#ifndef __JUCETICE_VEXPLUGINFILTER_HEADER__
#define __JUCETICE_VEXPLUGINFILTER_HEADER__

#include <list>

#include "JucePluginCharacteristics.h"
#include "PeggySettings.h"
#include "PresetMan.h"

#include "synth/cChorus.h"
#include "synth/cReverb.h"
#include "synth/cDelay.h"
#include "synth/cArp.h"
#include "synth/cSyntModule.h"


class VexFilter  : public AudioProcessor,
                   public ChangeBroadcaster
{
public:

    VexFilter();
    ~VexFilter();

    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();
	void processBlock (AudioSampleBuffer& output, MidiBuffer& midiMessages);

    const String getName() const { return JucePlugin_Name; }
    bool acceptsMidi() const { return JucePlugin_WantsMidiInput; }
    bool producesMidi() const { return JucePlugin_ProducesMidiOutput; }

    const String getInputChannelName (const int channelIndex) const;
    const String getOutputChannelName (const int channelIndex) const;
    bool isInputChannelStereoPair (int index) const;
    bool isOutputChannelStereoPair (int index) const;

    int getNumParameters()	{	return 92;	}
    float getParameter (int index);
    void  setParameter (int index, float newValue);
	void setParameter (int index, float newValue, bool fromGUI);

    const String getParameterName (int index);
    const String getParameterText (int index);

    int getNumPrograms();
    int getCurrentProgram();
    void setCurrentProgram (int index);
    const String getProgramName (int index);
    void changeProgramName (int index, const String& newName);

    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);
	void setCurrentProgramStateInformation (const void* data, int sizeInBytes);
	void getCurrentProgramStateInformation (MemoryBlock& destData);

    AudioProcessorEditor* createEditor();

	void setWave(int part, const String& waveName);
	String getWave(int part);
	peggySettings* getPeggySet(int part);

	std::list<int> dirtyList;

    juce_UseDebuggingNewOperator

private:

	AudioSampleBuffer * obf;
	AudioSampleBuffer * abf;
	AudioSampleBuffer * dbf;
	AudioSampleBuffer * dbf2;
	AudioSampleBuffer * dbf3;
	int snum;
	cSyntModule* s1;
	cChorus* c1;
	cReverb* r1;
	cDelay* d1;
	cArp* a1;
	cArp* a2;
	cArp* a3;
	float* pra;
	peggySettings* p1;
	peggySettings* p2;
	peggySettings* p3;
	PresetMan* pMan;
};


#endif
