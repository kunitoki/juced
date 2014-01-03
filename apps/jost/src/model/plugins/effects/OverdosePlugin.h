/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2007 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2007 by Julian Storer.

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
*/


#ifndef __JUCETICE_JOSTOVERDOSEPLUGIN_HEADER__
#define __JUCETICE_JOSTOVERDOSEPLUGIN_HEADER__

#include "../../BasePlugin.h"
#include "OverdoseParameters.h"


//==============================================================================
/**
    A simple overdrive plugin.
	@Spankache

*/
class OverdosePlugin  : public BasePlugin
{
public:
    //==============================================================================
    OverdosePlugin();
    ~OverdosePlugin();

	//==============================================================================
    int getType () const                 { return JOST_PLUGINTYPE_OVERDOSE; }

    //==============================================================================
	const String getName () const        { return T("Overdose"); }
	int getNumInputs () const            { return 2; }
    int getNumOutputs () const           { return 2; }
    int getNumMidiInputs () const        { return 1; }
    int getNumMidiOutputs () const       { return 0; }
	bool canReceiveMidiEvents () const   { return false; }
    bool canSendMidiEvents () const      { return false; }
    bool isMidiOutput () const           { return false; }
	//==============================================================================
    bool hasEditor () const              { return true; }
    bool wantsEditor () const            { return true; }
    bool isEditorInternal () const       { return true; }

    AudioProcessorEditor* createEditor();

	 //==============================================================================
	int getNumParameters();
	void setParameter (int paramNumber, float value);
    float getParameter (int paramNumber);
    const String getParameterName (int paramNumber);
    const String getParameterText (int paramNumber);

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();
	
	void overdose (AudioSampleBuffer* buffer, AudioSampleBuffer* out, int sampleFrames);

	void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);
	
    //==============================================================================
	String ProgName[3];
	
    //==============================================================================
    int getNumPrograms()                                        { return 3; }
    int getCurrentProgram()                                     { return cp; }
	void initToDefault();
	void setCurrentProgram (int index);
    const String getProgramName (int index)                     { return ProgName[index];  }
    void changeProgramName (int index, const String& newName)   { ProgName[index] = newName;}

    //==============================================================================
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);

    //==============================================================================

    // this is kept up to date with the midi messages that arrive, and the UI component
    // registers with it so it can represent the incoming messages
    MidiKeyboardState keyboardState;

    // this keeps a copy of the last set of time info that was acquired during an audio
    // callback - the UI component will read this and display it.
    AudioPlayHead::CurrentPositionInfo lastPosInfo;

    //==============================================================================
	/** Calculate output magnitude for meters */  
	void setMagnus(float val);
	float getMagnus();

    juce_UseDebuggingNewOperator

	OverdoseParMan * Pars;
	

private:
  
  int cp; //current program
  int temppr;
  float magnus;

protected:
  float filt1, filt2; //filter buffers
  float filt;         //filter coeff.
  float gainer;         //output gain
};


#endif
