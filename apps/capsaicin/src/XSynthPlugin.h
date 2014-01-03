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

#ifndef __JUCETICE_XSYNTHPLUGIN_HEADER__
#define __JUCETICE_XSYNTHPLUGIN_HEADER__

#include "Misc/Config.h"
#include "Misc/Master.h"
#include "XSynthParameters.h"

class XSynthEditor;
class XSynthPlugin;


//==============================================================================
/**
            Capsaicin is a powerful additive synthesizer
*/
class XSynthPlugin  : public AudioPlugin
{
public:
    //==============================================================================
    XSynthPlugin();
    ~XSynthPlugin();

    //==============================================================================
    const String getName() const          { return JucePlugin_Name; }
    bool acceptsMidi() const              { return JucePlugin_WantsMidiInput; }
    bool producesMidi() const             { return JucePlugin_ProducesMidiOutput; }

    //==============================================================================
    AudioProcessorEditor* createEditor();
    XSynthEditor* getEditor();

    //==============================================================================
    Master* getMaster ()                                       { return &master; }

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();
    void processBlock (AudioSampleBuffer& buffer,
                       MidiBuffer& midiMessages);

    //==============================================================================
    void initialiseStateToDefault ();
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);
    void setCurrentProgram (int index);

    //==============================================================================
    static int numInstances;

    //==============================================================================
    juce_UseDebuggingNewOperator

protected:

    friend class XSynthEditor;
    friend class XSynthParameters;

    //==============================================================================
    int getMidiController (uint8 data);

    //==============================================================================
    // synth master
    Master master;

    // parameters helper
    XSynthParameters* parameters;

    // keyboard state
    MidiKeyboardState keyboardState;
};


#endif // __JUCETICE_XSYNTHPLUGIN_HEADER__
