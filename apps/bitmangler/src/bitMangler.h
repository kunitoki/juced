/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-7 by Raw Material Software ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the
   GNU General Public License, as published by the Free Software Foundation;
   either version 2 of the License, or (at your option) any later version.

   JUCE is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with JUCE; if not, visit www.gnu.org/licenses or write to the
   Free Software Foundation, Inc., 59 Temple Place, Suite 330,
   Boston, MA 02111-1307 USA

  ------------------------------------------------------------------------------

   If you'd like to release a closed-source product which uses JUCE, commercial
   licenses are also available: visit www.rawmaterialsoftware.com/juce for
   more information.

  ==============================================================================
*/

#ifndef DEMOJUCEPLUGINFILTER_H
#define DEMOJUCEPLUGINFILTER_H

#include "StandardHeader.h"
#include "bitFloat.h"

class bitManglerEditor;

//==============================================================================
/**
    A simple plugin filter that just applies a gain change to the audio
    passing through it.

*/

class DemoJuceFilter  : public AudioProcessor,
                        public ChangeBroadcaster
{
public:
    //==============================================================================
    DemoJuceFilter();
    ~DemoJuceFilter();

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
    // These properties are public so that our editor component can access them
    //  - a bit of a hacky way to do it, but it's only a demo!

    // this is kept up to date with the midi messages that arrive, and the UI component
    // registers with it so it can represent the incoming messages
    MidiKeyboardState keyboardState;

    // this keeps a copy of the last set of time info that was acquired during an audio
    // callback - the UI component will read this and display it.
    AudioPlayHead::CurrentPositionInfo lastPosInfo;

    //==============================================================================
    juce_UseDebuggingNewOperator

	float getCurrentSample();
	float getCurrentConvertedSample();
	void stopProcessing();
	void startProcessing();
	bool isProcessing();
	float process(float sample);

	void setXorBit (int pos, bool bit);
	void setAndBit (int pos, bool bit);
	void setSetBit (int pos);
	void setClearBit (int pos);
	void clearTable();
	void clearXorTable();
	void clearAndTable();
	void clearSetTable();
	void clearClearTable();
	void setProcess (int processDef, bool b);
	String serializeArray (Array <bool>a);
	void unserializeArray (String data, Array <bool>&a);
	int getXorFirst();
	int getXorLast();
	int getAndFirst();
	int getAndLast();
	int getClearFirst();
	int getClearLast();
	int getSetFirst();
	int getSetLast();
	bool getXorWith();
	bool getAndWith();
	void setXorWith(bool b);
	void setAndWith(bool b);

	bool xorProcessing, andProcessing, clearProcessing, setProcessing;
	
	enum params
	{
		kXorToggle,
		kAndToggle,
		kClearToggle,
		kSetToggle,
		kXorMod,
		kAndMod,
		kXorMin,
		kXorMax,
		kAndMin,
		kAndMax,
		kClearMin,
		kClearMax,
		kSetMin,
		kSetMax,
		kProces,
		kParams
	};

private:
    // this is our gain - the UI and the host can access this by getting/setting
    // parameter 0.
	bitManglerEditor *editor;
	float currentSample;
	float currentConvertedSample;
	unsigned int bufferCycle;
	bool processing;

	Array <bool>xorBits;
	bool xorWith;

	Array <bool>andBits;
	bool andWith;

	Array <bool>orBits;
	Array <bool>orWith;

	Array <bool>clearBits;
	Array <bool>setBits;

	bitFloat myFloat;
};


#endif
