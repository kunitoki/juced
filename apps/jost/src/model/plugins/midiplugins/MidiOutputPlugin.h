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

#ifndef __JUCETICE_JOSTMIDIOUTPUTPLUGIN_HEADER__
#define __JUCETICE_JOSTMIDIOUTPUTPLUGIN_HEADER__

#include "../../BasePlugin.h"

//==============================================================================
class MidiOutputPlugin : public BasePlugin
{
public:
    //==============================================================================
    MidiOutputPlugin (const int numChannels);
    ~MidiOutputPlugin ();

    //==============================================================================
    int getType () const                 { return JOST_PLUGINTYPE_MIDIOUT; }

    //==============================================================================
    const String getName () const        { return T("MidiOut"); }
    int getNumInputs () const            { return 0; }
    int getNumOutputs () const           { return 0; }
    int getNumMidiInputs () const        { return 1; }
    int getNumMidiOutputs () const       { return 0; }
    bool acceptsMidi () const            { return true; }
    bool isMidiOutput () const           { return true; }

    //==============================================================================
    bool hasEditor () const              { return false; }
    bool wantsEditor () const            { return false; }
    bool isEditorInternal () const       { return false; }
    AudioProcessorEditor* createEditor();

    //==============================================================================
    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();

private:

    MidiOutput* midiOutput;
};


#endif
