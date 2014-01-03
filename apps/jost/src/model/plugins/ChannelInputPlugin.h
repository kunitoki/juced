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

#ifndef __JUCETICE_JOSTCHANNELINPUTPLUGIN_HEADER__
#define __JUCETICE_JOSTCHANNELINPUTPLUGIN_HEADER__

#include "../BasePlugin.h"

class ChannelPlugin;

//==============================================================================
/**
    Input plugin from audio callback processing.
    There will be only one of this in every ChannelPlugin !
	@Spankache
*/
class ChannelInputPlugin : public BasePlugin
{
public:

    //==============================================================================
    ChannelInputPlugin (const int numChannels, ChannelPlugin* owner);
    ~ChannelInputPlugin ();

    //==============================================================================
    int getType () const                  { return JOST_PLUGINTYPE_CHANNELINPUT; }

    //==============================================================================
    const  String getName () const        { return T("Input"); }
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
	ChannelPlugin* owner;
	
};


#endif
