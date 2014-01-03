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

#ifndef __JUCETICE_JOSTMULTITRACK_HEADER__
#define __JUCETICE_JOSTMULTITRACK_HEADER__

#if 0

#include "../Config.h"
#include "../Commands.h"
#include "Track.h"


class HostFilterBase;


//==============================================================================
/**
    MultiTrack is a class that handles a series of tracks, and will share
    the transport and main mixer between them.
*/
class MultiTrack : public Timer
{
public:

    //==============================================================================
    /** Constructor */
    MultiTrack (HostFilterBase* owner);

    /** Destructor */
    ~MultiTrack ();

    //==============================================================================
    /** Return the total number of registered tracks */
    int getTracksCount() const                      { return tracks.size (); }

    /** Returns a specified track.

        If the track doesn't exists it will return 0
    */
    Track* getTrack (const int trackIndex) const    { return tracks [trackIndex]; }

    /** Free all active tracks

        This will also deallocate tracks memory
    */
    void clearAllTracks ()                          { tracks.clear (true); }

    //==============================================================================
    /** This is called when the host is first activated, and before the callback */
    void prepareToPlay (double sampleRate, int samplesPerBlock);

    /** Called when the host is released: the audio setup is reset or changed */
    void releaseResources();

    /** This is the audio/midi callback.

        You will process audio and midi, calling every loaded effect.
    */
    void processBlock (const AudioSampleBuffer& input,
                       AudioSampleBuffer& output,
                       const bool accumulateOutput,
                       MidiBuffer& midiMessages);

    /** In the timer we issue mainly NON GUI idle calls to plugin that ask for */
    void timerCallback ();

    //==============================================================================
    void saveToXml (XmlElement* xml);
    void loadFromXml (XmlElement* xml);

    //==============================================================================
#ifdef JOST_SEQUENCER_DEMO
    AudioTransportSource* getTransport ()               { return &transportSource; }
    SequenceAudioSource* getSequence ()                 { return &sequenceSource; }
#endif

protected:

    // owner of this multitrack
    HostFilterBase* owner;

    // current playing tracks (audio only)
    OwnedArray<Track> tracks;

#ifdef JOST_SEQUENCER_DEMO
    // this allows an audio source to be streamed to the IO device
    AudioSourcePlayer audioSourcePlayer;

    // this controls the playback of a positionable audio stream, handling the
    // starting/stopping and sample-rate conversion
    AudioTransportSource transportSource;

    // this source is used to mix together the output from our synth source
    // and wave player source
    PositionableMixerAudioSource mixerSource;

    // TODO - this should be part of the Track !
    SequenceAudioSource sequenceSource;

    PositionableResamplingAudioSource* audioFileSource1;
    PositionableResamplingAudioSource* audioFileSource2;
#endif
};

#endif


#endif
