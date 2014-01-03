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

    Original code: Reuben a.k.a. Insertpizhere

 ==============================================================================
*/

#ifndef __JUCETICE_JOSTMIDIPADSPLUGIN_HEADER__
#define __JUCETICE_JOSTMIDIPADSPLUGIN_HEADER__

#include "../../BasePlugin.h"

class MidiPadsPlugin;
class MidiPadsPluginEditor;

//==============================================================================
enum
{
    kVelOffset = 0,
    kCCOffset,
    kChIn,
    kChOut,
    kUseTrigger,
    kUseVel,
    kThru,
    kSendAft,
    kMono,
    kNoteOnTrig,
    kNumGlobalParams,

    numPads = 64,
    kNumParams = kNumGlobalParams + 2 * numPads,
    kNumPresets = 32,

    xpos = kNumGlobalParams,
    ypos = xpos + numPads
};

//==============================================================================
class MidiPadsProgram
{public:

	MidiPadsProgram ();
	~MidiPadsProgram ();

private:

    friend class MidiPadsPlugin;

    float param[kNumParams];

    float Ydata1[numPads]; 
    float Ycc[numPads];
    float Ytype[numPads];
    float Ydata2[numPads]; 
    float Yoff[numPads];
    float trigger[numPads];
    float Xcc[numPads];
    float Xoff[numPads];
    bool SendOff[numPads];
    float UseX[numPads];
    float UseY[numPads];
    bool UseYCC[numPads];
    bool UseXPB[numPads];
    bool toggle[numPads];
    bool togglestate[numPads];

    int lastUIWidth, lastUIHeight;
    float bghue;
    float bgsat;
    float bgbri;
    float contrast;
    String icon[numPads];
    String text[numPads];
    Colour padcolor[numPads];
    int squares;
    bool showdots;
    bool editmode;
    float roundness;
    bool usemouseup;
    bool hex;

	String name;

    int lastx[numPads];
    int lasty[numPads];
};


//==============================================================================
/**
    A simple plugin filter that just applies a gain change to the audio
    passing through it.

*/
class MidiPadsPlugin  : public BasePlugin
{
public:
    //==============================================================================
    MidiPadsPlugin ();
    ~MidiPadsPlugin ();

    //==============================================================================
    int getType () const                 { return JOST_PLUGINTYPE_MIDIPADS; }

    //==============================================================================
    const String getName () const        { return T("MidiPads"); }
    int getNumInputs () const            { return 0; }
    int getNumOutputs () const           { return 0; }
    int getNumMidiInputs () const        { return 0; }
    int getNumMidiOutputs () const       { return 1; }
    bool acceptsMidi () const            { return false; }
    bool producesMidi () const           { return true; }

    //==============================================================================
    bool hasEditor () const              { return true; }
    bool wantsEditor () const            { return true; }
    bool isEditorInternal () const       { return true; }
    AudioProcessorEditor* createEditor();

    //==============================================================================
    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();

    //==============================================================================
    int getNumParameters ()                              { return kNumParams; }
    void setParameter (int paramNumber, float value);
    float getParameter (int paramNumber);
    const String getParameterName (int paramNumber);
    //==============================================================================
    int getNumPrograms()                                 { return kNumPresets; }
    int getCurrentProgram();
    void setCurrentProgram (int index);
    const String getProgramName (int index);
    void changeProgramName (int index, const String& newName);

    //==============================================================================
    void getCurrentProgramStateInformation (MemoryBlock& destData);
    void setCurrentProgramStateInformation (const void* data, int sizeInBytes);
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);
    //==============================================================================
    juce_UseDebuggingNewOperator

private:

    friend class MidiPadsPluginEditor;

    //==============================================================================
    int lastUIWidth, lastUIHeight;

    float Ydata1[numPads]; 
    float Ycc[numPads];
    float Ytype[numPads];
    float Ydata2[numPads]; 
    float Yoff[numPads];
    float Xcc[numPads];
    float Xoff[numPads];
    float UseX[numPads];
    float UseY[numPads];
    float trigger[numPads];
    bool SendOff[numPads];
    bool UseYCC[numPads];
    bool UseXPB[numPads];
    bool toggle[numPads];

    float midilisten[numPads];
    float send[numPads];
    float sendoff[numPads];
    float bghue;
    float bgsat;
    float bgbri;
    float contrast;
    float roundness;
    String icon[numPads];
    String text[numPads];
    Colour padcolor[numPads];
    int squares;
    bool buttondown[numPads];
    bool isplaying[128];
    bool showdots;
    bool editmode;
    bool usemouseup;
    bool hex;
    bool trig;
    bool dotmoved[numPads];
    bool triggered[numPads];
    bool togglestate[numPads];
    int lastx[numPads];
    int lasty[numPads];
    int lastxccvalue[numPads];
    int lastyccvalue[numPads];

    float param[kNumParams];
    MidiPadsProgram *programs;
    int curProgram;
    int triggervel;
    bool init;
};



#endif
