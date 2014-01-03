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

#if 0

#include "MultiTrack.h"
#include "../HostFilterBase.h"


//==============================================================================
MultiTrack::MultiTrack (HostFilterBase* owner_)
  : owner (owner_)
{
    Track* firstTrack = new Track (owner);
    tracks.add (firstTrack); // TODO - this isn't properly like it is

#ifdef JOST_SEQUENCER_DEMO
    // prepare the audio sources
    audioFileSource1 = 0;
    audioFileSource2 = 0;
    transportSource.stop();
    transportSource.setSource (0);
    deleteAndZero (audioFileSource1);
    deleteAndZero (audioFileSource2);

    AudioFormatManager formatManager;
    formatManager.registerBasicFormats();

    AudioFormatReader* reader1 =
//        formatManager.createReaderFor (File (T("/home/kororaa/Music/Sounds/Samples/synth2.wav")));
        formatManager.createReaderFor (File (T("/home/kororaa/Desktop/EnergyXT/sounds/synth2.wav")));
    if (reader1 != 0)
    {
        sequenceSource.addAudioEvent (reader1, 0 * 44100, 3.0, false);
//        sequenceSource.addAudioEvent (reader1, 4 * 44100, 1.0, false);
//        sequenceSource.addAudioEvent (reader1, 8 * 44100, 0.5, false);

/*
        AudioFormatReaderSource* audioSource1 = new AudioFormatReaderSource (reader1, true);
        audioSource1->setLooping (true);

        audioFileSource1 = new PositionableResamplingAudioSource (audioSource1, true);
        audioFileSource1->setLooping (true);
        audioFileSource1->setResamplingRatio (1.0);

        mixerSource.addInputSource (audioFileSource1, false);
*/
    }

    AudioFormatReader* reader2 =
//        formatManager.createReaderFor (File (T("/home/kororaa/Music/Sounds/Samples/chords.wav")));
        formatManager.createReaderFor (File (T("/home/kororaa/Desktop/EnergyXT/sounds/chords.wav")));
    if (reader2 != 0)
    {
        sequenceSource.addAudioEvent (reader2, 5 * 44100, 0.5, false);
//        sequenceSource.addAudioEvent (reader2, 12 * 44100, 0.5, false);

/*
        AudioFormatReaderSource* audioSource2 = new AudioFormatReaderSource (reader2, true);
        audioSource2->setLooping (true);

        audioFileSource2 = new PositionableResamplingAudioSource (audioSource2, true);
        audioFileSource2->setLooping (true);
        audioFileSource2->setResamplingRatio (1.0);

        mixerSource.addInputSource (audioFileSource2, false);
*/
    }

    mixerSource.addInputSource (&sequenceSource, false);
    transportSource.setGain (0.8f);

#endif
}

MultiTrack::~MultiTrack()
{
#ifdef JOST_SEQUENCER_DEMO
    // delete transports
    transportSource.stop();
    transportSource.setSource (0);
    deleteAndZero (audioFileSource1);
    deleteAndZero (audioFileSource2);
    audioSourcePlayer.setSource (0);
#endif

    // free tracks
    clearAllTracks ();
}

//==============================================================================
void MultiTrack::prepareToPlay (double sampleRate_, int samplesPerBlock_)
{
#ifdef JOST_SEQUENCER_DEMO
    transportSource.setSource (&mixerSource,
                               32768, // tells it to buffer this many samples ahead
                               0); // sampleRate_ * 1.0); // tells to up/down sample
    audioSourcePlayer.setSource (&transportSource);

    // start audio source player
    audioSourcePlayer.audioDeviceAboutToStart (sampleRate_, samplesPerBlock_);
    transportSource.setPosition (0.0);
    transportSource.start();
#endif

    // prepare tracks to play
    for (int i = 0; i < tracks.size (); i++)
        tracks.getUnchecked (i)->prepareToPlay (sampleRate_, samplesPerBlock_);

    // start timer for plugins that needs idle
    startTimer (150);
}

void MultiTrack::releaseResources()
{
    // stop timer, cause plugins don't need idle calls
    stopTimer ();

    // release the tracks
    for (int i = 0; i < tracks.size (); i++)
        tracks.getUnchecked (i)->releaseResources();

#ifdef JOST_SEQUENCER_DEMO
    // audio is stopped
    transportSource.stop();
    audioSourcePlayer.audioDeviceStopped();
#endif
}

void MultiTrack::processBlock (const AudioSampleBuffer& input,
                               AudioSampleBuffer& output,
                               const bool accumulateOutput,
                               MidiBuffer& midiMessages)
{
#ifdef JOST_SEQUENCER_DEMO
    // process the player
    float* ptrOutputBuffers [16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    for (int i = jmin (input.getNumChannels(), 16); --i >= 1;)
        ptrOutputBuffers [i] = input.getSampleData (i);

    audioSourcePlayer.audioDeviceIOCallback (0, 0,
                                             ptrOutputBuffers, jmin (input.getNumChannels(), 16),
                                             input.getNumSamples());
#endif

    // clear outputs
    output.clear ();

    // process every track, passing inputs and outputs
    for (int i = 0; i < tracks.size (); i++)
        tracks.getUnchecked (i)->processBlock (input,
                                               output,
                                               accumulateOutput,
                                               midiMessages);
}

void MultiTrack::timerCallback ()
{
    for (int i = 0; i < tracks.size (); i++)
        tracks.getUnchecked (i)->processIdle ();
}

//==============================================================================
void MultiTrack::saveToXml (XmlElement* xml)
{
    for (int i = 0; i < tracks.size (); i++)
    {
        XmlElement* e = new XmlElement (JOST_PRESET_TRACKTAG);
        tracks.getUnchecked (i)->saveToXml (e);
        xml->addChildElement (e);
    }
}

void MultiTrack::loadFromXml (XmlElement* xml)
{
    forEachXmlChildElement (*xml, e)
    {
        if (e->hasTagName (JOST_PRESET_TRACKTAG))
        {
            Track* track = new Track (owner);
            track->loadFromXml (e);
            tracks.add (track);
        }
    }
}

#endif

