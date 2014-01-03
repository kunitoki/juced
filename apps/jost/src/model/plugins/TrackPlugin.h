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


#ifndef __JUCETICE_JOSTTRACKPLUGIN_HEADER__
#define __JUCETICE_JOSTTRACKPLUGIN_HEADER__

#include "../BasePlugin.h"
//#include "ChannelHost.h"
//#include "TrackEditor.h"
//#include "../../HostFilterBase.h"

//class TrackEditor;
//==============================================================================
/**
    This plugin will record and play audio files.
	Its editor will be a sequencer audio track.
	It still needs some work, so now it does nothing.
	@Spankache
*/
class TrackPlugin : public BasePlugin
					//public ChangeListener
{
public:

    //==============================================================================
    TrackPlugin (const int numChannels);
    ~TrackPlugin ();

    //==============================================================================
    int getType () const                  { return JOST_PLUGINTYPE_TRACK; }

    //==============================================================================
    const  String getName () const        { return T("Track"); }
    int getNumOutputs () const            { return numChannels; }
	int getNumInputs () const            { return numChannels; }
    int getNumMidiOutputs () const        { return 0; }
    bool producesMidi() const             { return false; }
    bool isMidiInput () const             { return false; }

    //==============================================================================
    bool hasEditor () const               { return true; }
    bool wantsEditor () const             { return true; }
    bool isEditorInternal () const        { return true; }
    AudioProcessorEditor* createEditor();

	/** Handy function to return the typecast editor */
    //TrackEditor* getEditor ();

	/** Handy function to return the real host */
    //ChannelHost* getChannelHost () ;

	/** Handy function to return the real transport */
    //Transport* getTransport ()                              { return transporter; }

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
	void createReader(const StringArray &files);

	void playFile();
	void stopFile();
	//==============================================================================
	//void changeListenerCallback (void* objectThatHasChanged);


private:

    int numChannels;

	AudioFormatManager formatManager;
	String audioFile;

	AudioTransportSource transportSource;
	AudioSourcePlayer audioSourcePlayer;
	Transport* transport;

protected:

    // a dummy parameter
    // TODO - make parameters array to follow plugin parameters
    //AudioParameter dummyParameter;


#if JUCE_LASH
    // if we choose to use lash we will have this set
    LashManager* lashManager;
#endif
};


#endif
