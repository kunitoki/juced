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

#include "../../core/juce_StandardHeader.h"

BEGIN_JUCE_NAMESPACE

#include "juce_SequenceAudioSource.h"
#include "juce_AudioFormatReaderSource.h"
#include "../../threads/juce_ScopedLock.h"


//==============================================================================
SequenceAudioSource::SequenceAudioSource()
    : currentSampleRate (0.0),
      bufferSizeExpected (0),
      currentPlayingPosition (0),
      currentPlayingPart (-1),
      isPlayingLoop (false)
{
}

SequenceAudioSource::~SequenceAudioSource()
{
    clear();
}

//==============================================================================
void SequenceAudioSource::addAudioEvent (AudioFormatReader* const sourceReader,
                                         const int startOffset,
                                         const double resampleRatio,
                                         const bool deleteWhenRemoved)
{

    if (sourceReader != 0)
    {
        lock.enter();
        double localRate = currentSampleRate;
        int localBufferSize = bufferSizeExpected;
        lock.exit();

        AudioEventHolder* const newOne = new AudioEventHolder (sourceReader,
                                                               startOffset,
                                                               resampleRatio,
                                                               deleteWhenRemoved);

        if (localRate != 0.0)
            newOne->resampleSource->prepareToPlay (localBufferSize, localRate);

        const ScopedLock sl (lock);

        int i;
        for (i = list.size(); --i >= 0;)
            if (list.getUnchecked(i)->startOffset <= startOffset)
                break;

        list.insert (i + 1, newOne);
    }
}

void SequenceAudioSource::removeAudioEvent (const int index)
{
    if (index >= 0 && index < list.size())
    {
        const ScopedLock sl (lock);

        AudioEventHolder* const oldOne = list.getUnchecked (index);
        if (oldOne != 0)
            oldOne->resampleSource->releaseResources ();

        list.remove (index);
    }
}

void SequenceAudioSource::clear()
{
    lock.enter();
    list.clear();
    lock.exit();
}

int SequenceAudioSource::getNumEvents() const
{
    return list.size();
}

SequenceAudioSource::AudioEventHolder* SequenceAudioSource::getEventPointer (const int index) const
{
    return list [index];
}

//==============================================================================
int SequenceAudioSource::getStartTime() const
{
    if (list.size() > 0)
        return list.getUnchecked(0)->startOffset;
    else
        return 0;
}

int SequenceAudioSource::getEndTime() const
{
    if (list.size() > 0)
        return list.getLast()->startOffset;
    else
        return 0;
}

void SequenceAudioSource::getEventTimeAndLength (const int index,
                                                int& sampleOffset,
                                                int& sampleDuration) const
{
    if (index >= 0 && index < list.size())
    {
        sampleOffset = list.getUnchecked (index)->startOffset;
        sampleDuration = list.getUnchecked (index)->resampleSource->getTotalLength();
    }
    else
    {
        sampleOffset = 0;
        sampleDuration = 0;
    }
}

//==============================================================================
int SequenceAudioSource::compareElements (const SequenceAudioSource::AudioEventHolder* const first,
                                          const SequenceAudioSource::AudioEventHolder* const second) throw()
{
    const double diff = first->startOffset
                         - second->startOffset;

    return (diff == 0) ? 0
                       : ((diff > 0) ? 1
                                     : -1);
}

void SequenceAudioSource::sort()
{
    list.sort (*this);
}

//==============================================================================
void SequenceAudioSource::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    const ScopedLock sl (lock);

    currentSampleRate = sampleRate;
    bufferSizeExpected = samplesPerBlockExpected;

    for (int i = list.size(); --i >= 0;)
        list.getUnchecked(i)->resampleSource->prepareToPlay (samplesPerBlockExpected,
                                                             sampleRate);
}

void SequenceAudioSource::releaseResources()
{
    const ScopedLock sl (lock);

    for (int i = list.size(); --i >= 0;)
        list.getUnchecked(i)->resampleSource->releaseResources ();

    currentSampleRate = 0;
    bufferSizeExpected = 0;
}

void SequenceAudioSource::getNextAudioBlock (const AudioSourceChannelInfo& info)
{
    const ScopedLock sl (lock);

    updatePlayingEvent (currentPlayingPosition);

    int nextSamples = samplesToNextEvent (currentPlayingPosition);

    if (currentPlayingPart >= 0
        && currentPlayingPart < list.size ())
    {
        int sampleToDo = jmax (-1, jmin (nextSamples, info.numSamples));
        if (sampleToDo >= 0)
        {
            AudioSourceChannelInfo subInfo;
            subInfo.buffer = info.buffer;
            subInfo.startSample = info.startSample;
            subInfo.numSamples = sampleToDo;

            AudioEventHolder* event = list.getUnchecked (currentPlayingPart);
            event->resampleSource->getNextAudioBlock (subInfo);

            if (sampleToDo < info.numSamples)
            {
                DBG ("played last: " + String (sampleToDo) + "  of " + String (info.numSamples));

                subInfo.startSample = info.startSample + sampleToDo;
                subInfo.numSamples = info.numSamples - sampleToDo;

                currentPlayingPosition += subInfo.numSamples;
                updatePlayingEvent (currentPlayingPosition);

                if (currentPlayingPart >= 0
                    && currentPlayingPart < list.size ())
                {
                    AudioEventHolder* event = list.getUnchecked (currentPlayingPart);
                    event->resampleSource->getNextAudioBlock (subInfo);
                }
                else
                {
                    subInfo.clearActiveBufferRegion();
                }

                DBG ("played last: " + String (subInfo.numSamples) + " of " + String (info.numSamples));
            }

            currentPlayingPosition += subInfo.numSamples;
        }
        else
        {
            info.clearActiveBufferRegion();
            currentPlayingPosition += info.numSamples;
        }
    }
    else
    {
        info.clearActiveBufferRegion();
        currentPlayingPosition += info.numSamples;
    }
}

//==============================================================================
void SequenceAudioSource::setNextReadPosition (int newPosition)
{
    currentPlayingPosition = newPosition;

    updatePlayingEvent (newPosition);
}

int SequenceAudioSource::getNextReadPosition() const
{
    return currentPlayingPosition;
}

int SequenceAudioSource::getTotalLength() const
{
    int maxLength = 0;

    if (list.size () > 0)
    {
        AudioEventHolder* const event = list.getUnchecked (list.size () - 1);
        maxLength = event->startOffset + event->resampleSource->getTotalLength();
    }

    return maxLength;
}

bool SequenceAudioSource::isLooping() const
{
    return isPlayingLoop;
}

//==============================================================================
int SequenceAudioSource::samplesToNextEvent (const int currentPosition)
{
    int samplesToNextEvent = 100000000; // enough ?

    if (list.size ()
        && currentPlayingPart >= -1
        && currentPlayingPart < list.size () - 1)
    {
        samplesToNextEvent = list.getUnchecked (currentPlayingPart + 1)->startOffset
                             - currentPosition;
    }

    return samplesToNextEvent;
}

void SequenceAudioSource::updatePlayingEvent (const int newPosition)
{
    int oldPlayingPart = currentPlayingPart;
    currentPlayingPart = -1;

    for (int i = list.size(); --i >= 0;) // TODO - start from end, cause event with time
                                         //        (> than) current overlap (< than) current
    {
        AudioEventHolder* currentEvent = list.getUnchecked (i);

        // we are in event range
        if (newPosition > currentEvent->startOffset
            && newPosition < (currentEvent->startOffset
                              + currentEvent->resampleSource->getTotalLength()))
        {
            currentPlayingPart = i;

/*
            // we should check if next event overlap this one
            if (currentPlayingPart < list.size() - 1)
            {
                AudioEventHolder* nextEvent = list.getUnchecked (currentPlayingPart + 1);

                DBG ("next event overlap " + String (currentPlayingPart)
                     + ": " + String (newPosition)
                     + " " + String (nextEvent->startOffset)
                     + " " + String (nextEvent->resampleSource->getTotalLength()));

                if (newPosition > nextEvent->startOffset
                    && newPosition < (nextEvent->startOffset
                                      + nextEvent->resampleSource->getTotalLength()))
                {
                    ++currentPlayingPart;
                }
            }
*/

            // if we are playing a different event
            if (currentPlayingPart != oldPlayingPart)
            {
                // reset old wave not to play ?
                if (oldPlayingPart >= 0 && oldPlayingPart < list.size ())
                {
                    AudioEventHolder* oldEvent = list.getUnchecked (oldPlayingPart);
                    oldEvent->resampleSource->setNextReadPosition (oldEvent->resampleSource->getTotalLength());
                }

                // update new event
                AudioEventHolder* newEvent = list.getUnchecked (currentPlayingPart);
                newEvent->resampleSource->setNextReadPosition (newPosition - newEvent->startOffset);
            }

            break;
        }
    }
}

//==============================================================================
SequenceAudioSource::AudioEventHolder::AudioEventHolder (
                                            AudioFormatReader* const sourceReader_,
                                            const int startOffset_,
                                            const double resampleRatio_,
                                            const bool deleteWhenRemoved_)
  : sourceReader (sourceReader_),
    startOffset (startOffset_),
    resampleRatio (resampleRatio_)
{
    // create the reader source
    AudioFormatReaderSource* audioSource = new AudioFormatReaderSource (sourceReader,
                                                                        deleteWhenRemoved_);
    audioSource->setLooping (false);

    // create the resample source
    resampleSource = new PositionableResamplingAudioSource (audioSource, true);
    resampleSource->setResamplingRatio (resampleRatio);
    resampleSource->setLooping (false);
    
    // create the internal audio buffer copy
    audioBuffer = new AudioSampleBuffer (sourceReader->numChannels,
                                         sourceReader->lengthInSamples);
    audioBuffer->readFromAudioReader (sourceReader,
                                      0,
                                      sourceReader->lengthInSamples,
                                      0,
                                      true,
                                      true);
}

SequenceAudioSource::AudioEventHolder::~AudioEventHolder ()
{
    deleteAndZero (resampleSource);
    deleteAndZero (audioBuffer);
}

END_JUCE_NAMESPACE
