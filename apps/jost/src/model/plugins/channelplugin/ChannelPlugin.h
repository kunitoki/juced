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

#ifndef __JUCETICE_JOSTCHANNELPLUGIN_HEADER__
#define __JUCETICE_JOSTCHANNELPLUGIN_HEADER__

#include "../../BasePlugin.h"
#include "ChannelHost.h"

class ChannelEditor;

//==============================================================================
/**
    This plugin acts as a sub-host and a sub-graph.
	@Spankache
*/
class ChannelPlugin : public BasePlugin
{
public:

    //==============================================================================
    ChannelPlugin (const int numChannels, HostFilterBase* base);
    ~ChannelPlugin ();

    //==============================================================================
	int getType () const;
    //==============================================================================
    const  String getName () const        { return T("Channel"); }
    int getNumOutputs () const            { return numChannels; }
	int getNumInputs () const            { return numChannels; }
    int getNumMidiOutputs () const        { return (JucePlugin_WantsMidiInput) ? 1 : 0; }
	int getNumMidiInputs () const        { return (JucePlugin_WantsMidiInput) ? 1 : 0; }
    bool producesMidi() const             { return JucePlugin_WantsMidiInput; }
    bool isMidiInput () const             { return JucePlugin_WantsMidiInput; }

    //==============================================================================
    bool hasEditor () const               { return true; }
    bool wantsEditor () const             { return true; }
    bool isEditorInternal () const        { return true; }
    AudioProcessorEditor* createEditor();

	/** Handy function to return the typecast editor */
    ChannelEditor* getEditor ();

	/** Handy function to return the real host */
	ChannelHost* getChannelHost ()	{ return hoster; }

	/** Handy function to return the base host */
    HostFilterBase* getBaseHost ()  { return base; }

	/** Handy function to return the real transport */
	Transport* getTransport ();

    //==============================================================================
	/** This is called when the host is first activated, and before the callback */
    void prepareToPlay (double sampleRate, int samplesPerBlock);

    /** Called when the host is released: the audio setup is reset or changed */
    void releaseResources();

    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);

	//==============================================================================
    /** This is called when we need to save our internal host session state */
    void getStateInformation (MemoryBlock& destData);

    /** Called to restore host session state */
    void setStateInformation (const void* data, int sizeInBytes);

    //==============================================================================
	void autoOpenTrack(BasePlugin* plugin);
	
	static int numInstances;          /** Running instances (plugin only) */

	// our real plugin host
    
	int numChannels;
	
	HostFilterBase* base;
	
	ChannelHost* hoster;
	
	int lastUIWidth, lastUIHeight;

protected:

	//friend class ChannelEditor;
   
    // the real transport
    Transport* transport;
};


#endif
