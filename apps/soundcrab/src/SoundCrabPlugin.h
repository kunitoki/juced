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

#ifndef __JUCETICE_SOUNDCRAB_HEADER__
#define __JUCETICE_SOUNDCRAB_HEADER__

#include "Synth/fluid_synth.h"

#include "StandardHeader.h"
#include "JucePluginCharacteristics.h"

#include "SoundCrabConfig.h"
#include "SoundCrabParameters.h"


class SoundCrabEditor;

//==============================================================================
/**
    A simple plugin filter that just applies a gain change to its input.

*/
class SoundCrabPlugin  : public AudioPlugin
{
public:

    //==============================================================================
    SoundCrabPlugin();
    ~SoundCrabPlugin();

    //==============================================================================
    const String getName() const          { return JucePlugin_Name; }
    bool acceptsMidi() const              { return JucePlugin_WantsMidiInput; }
    bool producesMidi() const             { return JucePlugin_ProducesMidiOutput; }

    //==============================================================================
    AudioProcessorEditor* createEditor();
    SoundCrabEditor* getEditor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();
    void processBlock (AudioSampleBuffer& buffer,
                       MidiBuffer& midiMessages);

    //==============================================================================
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);

    //==============================================================================
    bool loadSoundFont (const File& fileToLoad);
    File getCurrentSoundFontFile () const              { return currentSoundFile; }

    void setCurrentAbsolutePreset (const int index);
    int getCurrentAbsolutePreset () const              { return currentPreset; }

    void fillComboboxWithPresets (ComboBox* combo);

    //==============================================================================
    double getAverageCpuLoad ();

    //==============================================================================
    juce_UseDebuggingNewOperator

    static int instances;

protected:

    static void errorFunction (int level, char* message, void* data);
    static void logFunction (int level, char* message, void* data);

    friend class SoundCrabEditor;
    friend class SoundCrabParameters;

    SoundCrabParameters* parameters;

    fluid_settings_t* settings;
    fluid_synth_t* synth;
    fluid_sequencer_t* sequencer;
    int currentSynthChannel;

    File newSoundFont;
    int newSoundFontPreset;

    File currentSoundFile;
    int currentSound;
    int currentBank;
    int currentPreset;
};


#endif // __JUCETICE_SOUNDCRAB_HEADER__
