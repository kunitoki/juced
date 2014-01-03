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

#ifndef __JUCETICE_JOSTINPUTPLUGIN_HEADER__
#define __JUCETICE_JOSTINPUTPLUGIN_HEADER__

#include "../BasePlugin.h"


//==============================================================================
/**
    Input plugin from audio callback processing.

    This reflects JACK state, so it will have the same nuber of outputs
    as the main jack client.

    There will be only one of this in every Host !
*/
class InputPlugin : public BasePlugin
{
public:

    //==============================================================================
    InputPlugin (const int numChannels);
    ~InputPlugin ();

    //==============================================================================
    int getType () const                  { return JOST_PLUGINTYPE_INPUT; }

    //==============================================================================
    const  String getName () const        { return T("In"); }
    int getNumOutputs () const            { return numChannels; }
    int getNumMidiOutputs () const        { return (JucePlugin_WantsMidiInput) ? 1 : 0; }
    bool producesMidi() const             { return JucePlugin_WantsMidiInput; }
    bool isMidiInput () const             { return JucePlugin_WantsMidiInput; }

    //==============================================================================
    bool hasEditor () const               { return false; }
    bool wantsEditor () const             { return false; }
    bool isEditorInternal () const        { return false; }
    AudioProcessorEditor* createEditor();

    //==============================================================================
    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);


private:

    int numChannels;
};


#endif
