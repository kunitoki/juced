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

#include "juce_PositionableMixerAudioSource.h"
#include "../../threads/juce_ScopedLock.h"


//==============================================================================
PositionableMixerAudioSource::PositionableMixerAudioSource()
    : tempBuffer (2, 0),
      currentSampleRate (0.0),
      bufferSizeExpected (0),
      currentPlayingPosition (0),
      isPlayingLoop (false)
{
}

PositionableMixerAudioSource::~PositionableMixerAudioSource()
{
    removeAllInputs();
}

//==============================================================================
void PositionableMixerAudioSource::addInputSource (PositionableAudioSource* input,
                                                   const bool deleteWhenRemoved)
{
    if (input != 0 && ! inputs.contains (input))
    {
        lock.enter();
        double localRate = currentSampleRate;
        int localBufferSize = bufferSizeExpected;
        lock.exit();

        if (localRate != 0.0)
            input->prepareToPlay (localBufferSize, localRate);

        const ScopedLock sl (lock);

        inputsToDelete.setBit (inputs.size(), deleteWhenRemoved);
        inputs.add (input);
    }
}

void PositionableMixerAudioSource::removeInputSource (PositionableAudioSource* input,
                                                      const bool deleteInput)
{
    if (input != 0)
    {
        lock.enter();
        const int index = inputs.indexOf ((void*) input);

        if (index >= 0)
        {
            inputsToDelete.shiftBits (index, 1);
            inputs.remove (index);
        }

        lock.exit();

        if (index >= 0)
        {
            input->releaseResources();

            if (deleteInput)
                delete input;
        }
    }
}

void PositionableMixerAudioSource::removeAllInputs()
{
    lock.enter();
    VoidArray inputsCopy (inputs);
    BitArray inputsToDeleteCopy (inputsToDelete);
    inputs.clear();
    lock.exit();

    for (int i = inputsCopy.size(); --i >= 0;)
        if (inputsToDeleteCopy[i])
            delete (PositionableAudioSource*) inputsCopy[i];
}

//==============================================================================
void PositionableMixerAudioSource::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    tempBuffer.setSize (2, samplesPerBlockExpected);

    const ScopedLock sl (lock);

    currentSampleRate = sampleRate;
    bufferSizeExpected = samplesPerBlockExpected;

    for (int i = inputs.size(); --i >= 0;)
        ((PositionableAudioSource*) inputs.getUnchecked(i))->prepareToPlay (samplesPerBlockExpected,
                                                                            sampleRate);
}

void PositionableMixerAudioSource::releaseResources()
{
    const ScopedLock sl (lock);

    for (int i = inputs.size(); --i >= 0;)
        ((PositionableAudioSource*) inputs.getUnchecked(i))->releaseResources();

    tempBuffer.setSize (2, 0);

    currentSampleRate = 0;
    bufferSizeExpected = 0;
}

void PositionableMixerAudioSource::getNextAudioBlock (const AudioSourceChannelInfo& info)
{
    const ScopedLock sl (lock);

    if (inputs.size() > 0)
    {
        ((PositionableAudioSource*) inputs.getUnchecked(0))->getNextAudioBlock (info);

        if (inputs.size() > 1)
        {
            tempBuffer.setSize (jmax (1, info.buffer->getNumChannels()),
                                info.buffer->getNumSamples());

            AudioSourceChannelInfo info2;
            info2.buffer = &tempBuffer;
            info2.numSamples = info.numSamples;
            info2.startSample = 0;

            for (int i = 1; i < inputs.size(); ++i)
            {
                ((PositionableAudioSource*) inputs.getUnchecked(i))->getNextAudioBlock (info2);

                for (int chan = 0; chan < info.buffer->getNumChannels(); ++chan)
                    info.buffer->addFrom (chan, info.startSample, tempBuffer, chan, 0, info.numSamples);
            }
        }
    }
    else
    {
        info.clearActiveBufferRegion();
    }
}

//==============================================================================
void PositionableMixerAudioSource::setNextReadPosition (int newPosition)
{
    currentPlayingPosition = newPosition;

    for (int i = inputs.size(); --i >= 0;)
        ((PositionableAudioSource*) inputs.getUnchecked(i))->setNextReadPosition (newPosition);
}

int PositionableMixerAudioSource::getNextReadPosition() const
{
    return currentPlayingPosition;
}

int PositionableMixerAudioSource::getTotalLength() const
{
    int maxLength = 0;

    for (int i = inputs.size(); --i >= 0;)
        maxLength = jmax (maxLength,
                          ((PositionableAudioSource*) inputs.getUnchecked(i))->getTotalLength());

    return maxLength;
}

bool PositionableMixerAudioSource::isLooping() const
{
    return isPlayingLoop;
}

END_JUCE_NAMESPACE
