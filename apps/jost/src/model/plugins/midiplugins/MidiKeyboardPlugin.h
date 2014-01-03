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

#ifndef __JUCETICE_JOSTMIDIKEYBOARDPLUGIN_HEADER__
#define __JUCETICE_JOSTMIDIKEYBOARDPLUGIN_HEADER__

#include "../../BasePlugin.h"


//==============================================================================
class MidiKeyboardPlugin : public BasePlugin
{
public:

    //==============================================================================
    MidiKeyboardPlugin ();
    ~MidiKeyboardPlugin ();

    //==============================================================================
    int getType () const                 { return JOST_PLUGINTYPE_MIDIKEY; }

    //==============================================================================
    const String getName () const        { return T("MidiKeyboard"); }
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
    MidiKeyboardState* getKeyboardState ()        { return &keyboardState; }
    MidiMessageCollector* getMessageCollector ()  { return &midiCollector; }

private:

    MidiKeyboardState keyboardState;
    MidiMessageCollector midiCollector;
};


#endif
