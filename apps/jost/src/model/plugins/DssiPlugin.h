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

#ifndef __JUCETICE_JOSTDSSIPLUGIN_HEADER__
#define __JUCETICE_JOSTDSSIPLUGIN_HEADER__

#include "../BasePlugin.h"


#if JOST_USE_DSSI

#include <dssi.h>
#include <alsa/asoundlib.h>


//==============================================================================
/**
    This is a helper class, that will help our poor vst plugin understand
    its wacky vst event structure.
*/
class DssiPluginMidiManager
{
public:

    //==============================================================================
    DssiPluginMidiManager ();
    ~DssiPluginMidiManager ();

    //==============================================================================
    void convertMidiMessages (MidiBuffer& midiMessages, const int blockSamples);

    //==============================================================================
    snd_seq_event_t* getMidiEvents () { return (snd_seq_event_t*) &midiEventsBuffer[0]; }
    int getMidiEventsCount () const   { return currentMidiCount; }

protected:

    // internal midi event buffer
    snd_seq_event_t midiEventsBuffer [2048];
    snd_midi_event_t* midiParser;
    int maxEventSize;
    int currentMidiCount;
};


//==============================================================================
/**
    Dssi wrapper class.
*/
class DssiPlugin : public BasePlugin,
                   public OpenSoundControllerListener
{
public:

    //==============================================================================
    DssiPlugin ();
    ~DssiPlugin ();

    //==============================================================================
    int getType () const                               { return JOST_PLUGINTYPE_DSSI; }

    //==============================================================================
    bool loadPluginFromFile (const File& filePath);
    File getFile () const                              { return pluginFile; }

    //==============================================================================
    const String getName () const;
    int getID () const;
    int getNumInputs () const;
    int getNumOutputs () const;
    int getNumMidiInputs () const;
    int getNumMidiOutputs () const;
    bool acceptsMidi () const;
    void* getLowLevelHandle ();

    //==============================================================================
    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();

    //==============================================================================
    void setParameterReal (int paramNumber, float value);
    float getParameterReal (int paramNumber);
    const String getParameterTextReal (int paramNumber, float value);

    //==============================================================================
    int getNumPrograms ();
    void setCurrentProgram (int programNumber);
    int getCurrentProgram ();
    const String getProgramName (int programNumber);
    const String getCurrentProgramName ();

    //==============================================================================
    bool hasEditor () const;
    bool wantsEditor () const;

#if 0
    void getEditorSize (int& width, int& height);
    void openEditor (void* handle, void* display);
    void idleEditor ();
    void closeEditor ();
#endif

    //==============================================================================
    bool handleOSCMessage (OpenSoundController* controller,
                           OpenSoundMessage *message);

private:

    //==============================================================================
    void setDefaultProgram ();

    //==============================================================================
    File pluginFile;

    void* ptrLibrary;
    const DSSI_Descriptor* ptrPlug;
    const LADSPA_Descriptor* ladspa;
    LADSPA_Handle plugin;

    Array<int> ins, outs, pars;

    float* params;
    float* normalized;

    int currentPreset;
    int numPrograms;
    float samplingRate;

    DssiPluginMidiManager midiManager;
    AudioSampleBuffer emptyBuffer;

    // an osc controller
    UDPSocket sock;
    OpenSoundController osc;
};

#endif

#endif // __JUCETICE_JOSTDSSIPLUGIN_HEADER__
