/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-6 by Raw Material Software ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the
   GNU General Public License, as published by the Free Software Foundation;
   either version 2 of the License, or (at your option) any later version.

   JUCE is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with JUCE; if not, visit www.gnu.org/licenses or write to the
   Free Software Foundation, Inc., 59 Temple Place, Suite 330,
   Boston, MA 02111-1307 USA

  ------------------------------------------------------------------------------

   If you'd like to release a closed-source product which uses JUCE, commercial
   licenses are also available: visit www.rawmaterialsoftware.com/juce for
   more information.

  ==============================================================================
*/

#ifndef __JUCE_SEQUENCEAUDIOSOURCE_JUCEHEADER__
#define __JUCE_SEQUENCEAUDIOSOURCE_JUCEHEADER__

#include "juce_PositionableAudioSource.h"
#include "juce_PositionableResamplingAudioSource.h"
#include "../../threads/juce_CriticalSection.h"
#include "../../containers/juce_OwnedArray.h"


//==============================================================================
/**
    An PositionableAudioSource that mixes together the output of a set of other
    PositionableAudioSources.

    Input sources can be added and removed while the mixer is running as long as their
    prepareToPlay() and releaseResources() methods are called before and after adding
    them to the mixer.
*/
class JUCE_API  SequenceAudioSource  : public PositionableAudioSource
{
public:

    //==============================================================================
    /** Creates a SequenceAudioSource. */
    SequenceAudioSource();

    /** Destructor. */
    ~SequenceAudioSource();

    //==============================================================================
    /** Structure used to hold audio events in the sequence.

        These structures act as 'handles' on the events as they are moved about in
        the list, and make it quick to find in the whole sequence

        @see SequenceAudioSource::getEventPointer
    */
    class AudioEventHolder
    {
    public:
        //==============================================================================
        /** Destructor. */
        ~AudioEventHolder ();

        /** The source reader we can delete, and refers to real one */
        AudioFormatReader* sourceReader;

        /** This is the source we will stream */
        PositionableResamplingAudioSource* resampleSource;
        
        /** This is the internal buffer, used for display */
        AudioSampleBuffer* audioBuffer;

        /** Offset in samples where this event occurs */
        int startOffset;

        /** Resampling ratio, in case you need the sample at a different pitch */
        double resampleRatio;

        //==============================================================================
        juce_UseDebuggingNewOperator

    private:
        friend class SequenceAudioSource;
        AudioEventHolder (AudioFormatReader* const sourceReader,
                          const int startOffset,
                          const double resampleRatio = 1.0,
                          const bool deleteWhenRemoved = true);
    };

    //==============================================================================
    /** Adds an audio event to the sequence.

        If the mixer is running you'll need to make sure that the input source
        is ready to play by calling its prepareToPlay() method before adding it.
        If the mixer is stopped, then its input sources will be automatically
        prepared when the mixer's prepareToPlay() method is called.

        @param newInput             the source to add to the mixer
        @param deleteWhenRemoved    if true, then this source will be deleted when
                                    the mixer is deleted or when removeAllInputs() is
                                    called (unless the source is previously removed
                                    with the removeInputSource method)
    */
    void addAudioEvent (AudioFormatReader* const sourceReader,
                        const int startOffset,
                        const double resampleRatio = 1.0,
                        const bool deleteWhenRemoved = true);

    /** Removes an input source.

        If the mixer is running, this will remove the source but not call its
        releaseResources() method, so the caller might want to do this manually.

        @param input            the source to remove
        @param deleteSource     whether to delete this source after it's been removed
    */
    void removeAudioEvent (const int index);

    /** Returns the number of events in the sequence. */
    int getNumEvents() const;

    /** Returns a pointer to one of the events. */
    AudioEventHolder* getEventPointer (const int index) const;

    /** Returns the index of an event. */
    int getIndexOf (AudioEventHolder* const event) const;

    /** Returns the index of the first event on or after the given timestamp.

        If the time is beyond the end of the sequence, this will return the
        number of events.

        TODO - should we use samples instead of seconds ?
    */
    int getNextIndexAtTime (const double timeStamp) const;

    /** Clears the sequence. */
    void clear();

    //==============================================================================
    /** Returns the time in samples of the first event in the sequence.

        @see getEndTime
    */
    int getStartTime() const;

    /** Returns the time in samples of the last event in the sequence.

        @see getStartTime
    */
    int getEndTime() const;

    /** Returns the time in samples of the event and its duration at a given index.

        If the index is out-of-range, this will return 0 for both references
    */
    void getEventTimeAndLength (const int index,
                                int& sampleOffset,
                                int& sampleDuration) const;

    //==============================================================================
    /** Implementation of the AudioSource method.

        This will call prepareToPlay() on all its input sources.
    */
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate);

    /** Implementation of the AudioSource method.

        This will call releaseResources() on all its input sources.
    */
    void releaseResources();

    /** Implementation of the AudioSource method. */
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill);

    //==============================================================================
    /** Tells the stream to move to a new position.

        Calling this indicates that the next call to AudioSource::getNextAudioBlock()
        should return samples from this position.

        Note that this may be called on a different thread to getNextAudioBlock(),
        so the subclass should make sure it's synchronised.
    */
    void setNextReadPosition (int newPosition);

    /** Returns the position from which the next block will be returned.

        @see setNextReadPosition
    */
    int getNextReadPosition() const;

    /** Returns the total length of the stream (in samples). */
    int getTotalLength() const;

    /** Returns true if this source is actually playing in a loop. */
    bool isLooping() const;

    //==============================================================================
    juce_UseDebuggingNewOperator

    /** @internal */
    static int compareElements (const SequenceAudioSource::AudioEventHolder* const first,
                                const SequenceAudioSource::AudioEventHolder* const second) throw();

private:
    //==============================================================================
    OwnedArray <AudioEventHolder> list;
    CriticalSection lock;
    double currentSampleRate;
    int bufferSizeExpected;
    int currentPlayingPosition;
    int currentPlayingPart;
    bool isPlayingLoop;

    int samplesToNextEvent (const int currentPosition);
    void updatePlayingEvent (const int newPosition);
    void sort();

    SequenceAudioSource (const SequenceAudioSource&);
    const SequenceAudioSource& operator= (const SequenceAudioSource&);
};


#endif   // __JUCE_SEQUENCEAUDIOSOURCE_JUCEHEADER__
