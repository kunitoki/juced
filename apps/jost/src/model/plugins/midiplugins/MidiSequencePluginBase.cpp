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

#include "MidiSequencePluginBase.h"
#include "HostFilterBase.h"
#include "SequenceComponent.h"

#define NOTE_CHANNEL       1
#define NOTE_VELOCITY      0.8f
#define NOTE_PREFRAMES     0.001


//==============================================================================
MidiSequencePluginBase::MidiSequencePluginBase ()
  : transport (0),
    midiSequence (0),
    doAllNotesOff (false),
    allNotesOff (MidiMessage::allNotesOff (1))
{
    midiSequence = new MidiMessageSequence ();
}

MidiSequencePluginBase::~MidiSequencePluginBase ()
{
    deleteAndZero (midiSequence);
}

//==============================================================================
void MidiSequencePluginBase::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	noteOffs.clear();

    transport = getParentHost()->getTransport ();

    keyboardState.reset();
    
    startTimer (1000 / 25);	
}

void MidiSequencePluginBase::releaseResources()
{
    stopTimer ();
}

void MidiSequencePluginBase::processBlock (AudioSampleBuffer& buffer,
                                            MidiBuffer& midiMessages)
{
    const int blockSize = buffer.getNumSamples ();

    MidiBuffer* midiBuffer = midiBuffers.getUnchecked (0);

    keyboardState.processNextMidiBuffer (*midiBuffer,
                                         0, blockSize,
                                         true);

    if (transport->isPlaying ())
    {
        const int frameCounter = transport->getPositionInFrames ();
        const int framesPerBeat = transport->getFramesPerBeat ();
        const double framePerBeatDelta = 1.0f / (double) framesPerBeat;

        const int nextBlockFrameNumber = frameCounter + blockSize;

		const int seqIndex = getLoopRepeatIndex();
		const double beatCount = getLoopBeatPosition();
		const double frameLenBeatCount = (nextBlockFrameNumber - frameCounter) / (double)framesPerBeat;		
		double frameEndBeatCount = beatCount + frameLenBeatCount;
		if (frameEndBeatCount > getLengthInBeats())
			frameEndBeatCount -= getLengthInBeats();

        // prepare record incoming midi messages
        if (transport->isRecording ())
        {
            int samplePos = 0;
            MidiMessage msg (0xf4, 0.0);

            MidiBuffer::Iterator eventIterator (*midiBuffer);
            while (eventIterator.getNextEvent (msg, samplePos))
            {
                msg.setTimeStamp ((frameCounter + samplePos) * framePerBeatDelta);
                recordingSequence.addEvent (msg);
            }
        }

		if (frameEndBeatCount > beatCount)
		{
			renderEventsInRange(*midiSequence, midiBuffer, beatCount, frameEndBeatCount, frameCounter, framesPerBeat, nextBlockFrameNumber, seqIndex, blockSize);
			renderEventsInRange(noteOffs, midiBuffer, beatCount, frameEndBeatCount, frameCounter, framesPerBeat, nextBlockFrameNumber, seqIndex, blockSize);
			cleanUpNoteOffs(beatCount, frameEndBeatCount);
		}
		else
		{
			renderEventsInRange(*midiSequence, midiBuffer, beatCount, getLengthInBeats(), frameCounter, framesPerBeat, nextBlockFrameNumber, seqIndex, blockSize);
			renderEventsInRange(*midiSequence, midiBuffer, 0.00, frameEndBeatCount, frameCounter, framesPerBeat, nextBlockFrameNumber, seqIndex+1, blockSize);		
			renderEventsInRange(noteOffs, midiBuffer, beatCount, getLengthInBeats(), frameCounter, framesPerBeat, nextBlockFrameNumber, seqIndex, blockSize);
			renderEventsInRange(noteOffs, midiBuffer, 0.00, frameEndBeatCount, frameCounter, framesPerBeat, nextBlockFrameNumber, seqIndex+1, blockSize);		
			cleanUpNoteOffs(beatCount, getLengthInBeats());
			cleanUpNoteOffs(0.00, frameEndBeatCount);
		}

    }

    if (doAllNotesOff || transport->willSendAllNotesOff ())
    {
        midiBuffer->addEvent (allNotesOff, blockSize - 1);
        doAllNotesOff = false;
    }
}

void MidiSequencePluginBase::renderEventsInRange(const MidiMessageSequence& sourceMidi, MidiBuffer* midiBuffer, double beatCount, double frameEndBeatCount, const int frameCounter, const int framesPerBeat, const int nextBlockFrameNumber, const int seqIndex, const int blockSize)
{
	for (int i = sourceMidi.getNextIndexInTimeRange (beatCount, frameEndBeatCount);
		i < sourceMidi.getNumEvents (); i++)
	{
		int timeStampInSeq = roundFloatToInt (sourceMidi.getEventTime (i) * framesPerBeat);
		
		int timeStamp = timeStampInSeq + (seqIndex * getLengthInBeats() * framesPerBeat);

		MidiMessage* midiMessage = &sourceMidi.getEventPointer (i)->message;
		if (timeStamp >= nextBlockFrameNumber || !midiMessage)
		{
			break;
		}

		if (timeStamp >= transport->getDurationInFrames())
		{
			break;
		}
		
		// now play the event - unless we are disabled (muted), or it is a note off (always play note offs so we don't get dangling note-ons when user disables during a note sounding)
		if (midiMessage->isNoteOff() || getBoolValue(PROP_SEQENABLED, true))
		{
			midiBuffer->addEvent (*midiMessage, timeStamp - frameCounter);

			// look for matching note off - if it is past the loop end then we need to wrap it and ensure it gets played at the right time
			if (midiMessage->isNoteOn())
			{
				int up = sourceMidi.getIndexOfMatchingKeyUp(i);
				if (sourceMidi.getEventPointer (up)->message.isNoteOff() && 
					sourceMidi.getEventPointer (up)->message.getTimeStamp() > getLengthInBeats())
					noteOffs.addEvent(sourceMidi.getEventPointer (up)->message, -getLengthInBeats());
			}
		}
		
	}
}

void MidiSequencePluginBase::cleanUpNoteOffs(double fromTime, double toTime)
{
	for (int i=noteOffs.getNumEvents()-1; i>=0; i--)
	{
		if (noteOffs.getEventPointer (i)->message.getTimeStamp() >= fromTime && noteOffs.getEventPointer (i)->message.getTimeStamp() < toTime)
			noteOffs.deleteEvent(i, false);
	}
}

void MidiSequencePluginBase::timerCallback ()
{
    if (transport->isRecording ()
        && transport->willStopRecord ())
    {
        DBG ("Finalizing recording !");

        MidiMessageSequence* oldSequence = midiSequence;
        MidiMessageSequence* sequence = new MidiMessageSequence ();

        sequence->addSequence (*oldSequence, 0.0f, 0.0f, 1000000000.0f);
        sequence->updateMatchedPairs ();
        sequence->addSequence (recordingSequence, 0.0f, 0.0f, 1000000000.0f);
        sequence->updateMatchedPairs ();

        {
        const ScopedLock sl (parentHost->getCallbackLock());
        midiSequence = sequence;
        }

        transport->resetRecording ();

        deleteAndZero (oldSequence);
        recordingSequence.clear ();

        sendChangeMessage (this);

        DBG ("Recording OK !");
    }
}


//==============================================================================
bool MidiSequencePluginBase::timeSignatureChanged (const int barsCount,
                                                    const int timeDenominator)
{
	// only change the transport if we have a bigger duration
	if (barsCount > transport->getNumBars())
	{
		transport->setTimeSignature (transport->getTempo (),
                                 barsCount,
                                 timeDenominator);
		transport->setRightLocator (barsCount * timeDenominator);
	}

    return true;
}

bool MidiSequencePluginBase::playingPositionChanged (const float absolutePosition)
{
    transport->setPositionAbsolute (absolutePosition);
    return true;
}

bool MidiSequencePluginBase::noteAdded (const int noteNumber,
                                    const float beatNumber,
                                    const float noteLength)
{
    MidiMessage msgOn = MidiMessage::noteOn (NOTE_CHANNEL, noteNumber, NOTE_VELOCITY);
    msgOn.setTimeStamp (beatNumber);
    MidiMessage msgOff = MidiMessage::noteOff (NOTE_CHANNEL, noteNumber);
    msgOff.setTimeStamp ((beatNumber + noteLength) - NOTE_PREFRAMES);

    DBG ("Adding:" + String (noteNumber) + " " + String (beatNumber));

    {
    const ScopedLock sl (parentHost->getCallbackLock ());

    midiSequence->addEvent (msgOn);
    midiSequence->addEvent (msgOff);
    midiSequence->updateMatchedPairs ();
    }

    DBG ("Added:" + String (noteNumber) + " " + String (beatNumber));

    return true;
}

bool MidiSequencePluginBase::noteRemoved (const int noteNumber,
                                      const float beatNumber,
                                      const float noteLength)
{
    DBG ("Removing:" + String (noteNumber) + " " + String (beatNumber));

    double noteOnBeats = beatNumber - NOTE_PREFRAMES;

    int eventIndex = midiSequence->getNextIndexAtTime (noteOnBeats);
    while (eventIndex < midiSequence->getNumEvents ())
    {
        MidiMessage* eventOn = &midiSequence->getEventPointer (eventIndex)->message;

        if (eventOn->isNoteOn () && eventOn->getNoteNumber () == noteNumber)
        {
            // TODO - check note off distance == noteLength
            {
            const ScopedLock sl (parentHost->getCallbackLock());

            midiSequence->deleteEvent (eventIndex, true);
            midiSequence->updateMatchedPairs ();
            }

            DBG ("Removed:" + String (eventIndex) + " > " + String (noteNumber) + " @ " + String (beatNumber));

            if (transport->isPlaying ())
                doAllNotesOff = true;

            return true;
        }

        eventIndex++;
    }

    DBG (">>> Remove failed:" + String (noteNumber) + " @ " + String (beatNumber));

    return false;
}

bool MidiSequencePluginBase::noteMoved (const int oldNote,
                                    const float oldBeat,
                                    const int noteNumber,
                                    const float beatNumber,
                                    const float noteLength)
{
    DBG ("Moving:" + String (oldNote) + " " + String (oldBeat));

    double noteOnBeats = oldBeat - NOTE_PREFRAMES;

    int eventIndex = midiSequence->getNextIndexAtTime (noteOnBeats);
    while (eventIndex < midiSequence->getNumEvents ())
    {
        MidiMessage* eventOn = &midiSequence->getEventPointer (eventIndex)->message;

        if (eventOn->isNoteOn () && eventOn->getNoteNumber () == oldNote)
        {
            // TODO - check old note off distance == oldNoteLength

            MidiMessage msgOn = MidiMessage::noteOn (NOTE_CHANNEL, noteNumber, NOTE_VELOCITY);
            msgOn.setTimeStamp (beatNumber);
            MidiMessage msgOff = MidiMessage::noteOff (NOTE_CHANNEL, noteNumber);
            msgOff.setTimeStamp ((beatNumber + noteLength) - NOTE_PREFRAMES);

            {
            const ScopedLock sl (parentHost->getCallbackLock());

            // remove old events
            midiSequence->deleteEvent (eventIndex, true);
            midiSequence->updateMatchedPairs ();
            // add new events
            midiSequence->addEvent (msgOn);
            midiSequence->addEvent (msgOff);
            midiSequence->updateMatchedPairs ();
            }

            DBG ("Moved:" + String (eventIndex) + " > "
                          + String (oldNote) + " @ " + String (oldBeat) + " to "
                          + String (noteNumber) + " @ " + String (beatNumber));

            if (transport->isPlaying ())
                doAllNotesOff = true;

            return true;
        }

        eventIndex++;
    }

    DBG (">>> Move failed:" + String (oldNote) + " @ " + String (oldBeat));

    return false;
}

bool MidiSequencePluginBase::noteResized (const int noteNumber,
                                      const float beatNumber,
                                      const float noteLength)
{
    DBG ("Resizing:" + String (noteNumber) + " " + String (beatNumber));

    double noteOnBeats = beatNumber - NOTE_PREFRAMES;

    int eventIndex = midiSequence->getNextIndexAtTime (noteOnBeats);
    while (eventIndex < midiSequence->getNumEvents ())
    {
        MidiMessage* eventOn = &midiSequence->getEventPointer (eventIndex)->message;

        if (eventOn->isNoteOn () && eventOn->getNoteNumber () == noteNumber)
        {
            // TODO - check old note off distance == oldNoteLength

            MidiMessage msgOn = MidiMessage::noteOn (NOTE_CHANNEL, noteNumber, NOTE_VELOCITY);
            msgOn.setTimeStamp (beatNumber);
            MidiMessage msgOff = MidiMessage::noteOff (NOTE_CHANNEL, noteNumber);
            msgOff.setTimeStamp ((beatNumber + noteLength) - NOTE_PREFRAMES);

            {
            const ScopedLock sl (parentHost->getCallbackLock());

            // delete old events
            midiSequence->deleteEvent (eventIndex, true);
            midiSequence->updateMatchedPairs ();
            // add new events
            midiSequence->addEvent (msgOn);
            midiSequence->addEvent (msgOff);
            midiSequence->updateMatchedPairs ();
            }

            DBG ("Resized:" + String (eventIndex) + " > "
                             + String (noteNumber) + " @ " + String (beatNumber) + " to " + String (noteLength));

            if (transport->isPlaying ())
                doAllNotesOff = true;

            return true;
        }

        eventIndex++;
    }

    DBG (">>> Resize failed:" + String (noteNumber) + " @ " + String (beatNumber));

    return false;
}

bool MidiSequencePluginBase::allNotesRemoved ()
{
    {
    const ScopedLock sl (parentHost->getCallbackLock());

    midiSequence->clear ();

    if (transport->isPlaying ())
        doAllNotesOff = true;

    }

    return true;
}

//==============================================================================
void MidiSequencePluginBase::getNoteOnIndexed (const int index, int& note, float& beat, float& length)
{
    int numNoteOn = 0;
    for (int i = 0; i < midiSequence->getNumEvents (); i++)
    {
        MidiMessageSequence::MidiEventHolder* eventOn = midiSequence->getEventPointer (i);
        MidiMessageSequence::MidiEventHolder* eventOff = midiSequence->getEventPointer (i)->noteOffObject;

        MidiMessage* msgOn = & eventOn->message;
        if (eventOn->message.isNoteOn () && eventOff)
        {
            MidiMessage* msgOff = & eventOff->message;
            if (index == numNoteOn)
            {
                note = msgOn->getNoteNumber ();
                beat = msgOn->getTimeStamp ();
                length = ((msgOff->getTimeStamp () + NOTE_PREFRAMES) - msgOn->getTimeStamp ());
                break;
            }
            numNoteOn++;
        }
    }
}

int MidiSequencePluginBase::getNumNoteOn () const
{
    int numNoteOn = 0;

    for (int i = 0; i < midiSequence->getNumEvents (); i++)
        if (midiSequence->getEventPointer (i)->message.isNoteOn ()) numNoteOn++;

    return numNoteOn;
}

//==============================================================================
static void dumpMidiMessageSequence (MidiMessageSequence* midiSequence)
{
#if JUCE_DEBUG
    for (int i = 0; i < midiSequence->getNumEvents (); i++)
    {
        MidiMessage* midiMessage = &midiSequence->getEventPointer (i)->message;

        DBG (String (midiMessage->getNoteNumber()) + " "
             + (midiMessage->isNoteOn() ? "ON " : "OFF ")
             + String (midiMessage->getTimeStamp()));

        // DBG ("Playing event @ " + String (frameCounter) + " : " + String (timeStamp));
    }
#endif
}

//==============================================================================
void MidiSequencePluginBase::getStateInformation (MemoryBlock &mb) 
{
	getChunk(mb); 
}

void MidiSequencePluginBase::setStateInformation (const void* data, int sizeInBytes)
{
	MemoryBlock tempBlock (data, sizeInBytes);
	setChunk(tempBlock);
}

void MidiSequencePluginBase::getChunk (MemoryBlock& mb)
{
    MidiFile midiFile;

#if 0
    MidiMessageSequence timeTrack;
    timeTrack.addEvent (MidiMessage::timeSignatureMetaEvent (4, divDenominator));

    // add timing informations sequence
    midiFile.addTrack (timeTrack);
#endif

    // add real sequence scaled down !
    MidiMessageSequence scaledSequence;
    for (int i = 0; i < midiSequence->getNumEvents (); i++)
    {
        MidiMessage midiMessage = midiSequence->getEventPointer (i)->message;
        midiMessage.setTimeStamp (midiMessage.getTimeStamp() * 100000.0f);
        scaledSequence.addEvent (midiMessage);
    }
    midiFile.addTrack (scaledSequence);

    MemoryOutputStream os (4096, 2048, &mb);
    midiFile.writeTo (os);

    dumpMidiMessageSequence (midiSequence);
}

void MidiSequencePluginBase::setChunk (const MemoryBlock& mb)
{
    MemoryInputStream is (mb.getData(), mb.getSize(), false);

    MidiFile midiFile;
    midiFile.readFrom (is);

#if 0
    // use the first track as signature time track !
    const MidiMessageSequence* timeSequence = midiFile.getTrack (0);
    if (timeSequence)
    {
        for (int i = 0; i < timeSequence->getNumEvents (); i++)
        {
            MidiMessage* msg = & timeSequence->getEventPointer (i)->message;
            if (msg->isTimeSignatureMetaEvent ())
            {
                int numerator, denominator;
                msg->getTimeSignatureInfo (numerator, denominator);
                setTimeSignature (bpmTempo, numBars, denominator);
            }
        }
    }

    // add the note track !
    const MidiMessageSequence* notesSequence = midiFile.getTrack (1);
#endif

    const MidiMessageSequence* notesSequence = midiFile.getTrack (0);
    if (notesSequence)
    {
        // add real sequence scaled down !
        midiSequence->clear ();
        for (int i = 0; i < notesSequence->getNumEvents (); i++)
        {
            MidiMessage midiMessage = notesSequence->getEventPointer (i)->message;
            if (midiMessage.isNoteOnOrOff() || midiMessage.isController())
            {
                midiMessage.setTimeStamp (midiMessage.getTimeStamp() / 100000.0f);
                midiSequence->addEvent (midiMessage);
            }
        }
        midiSequence->updateMatchedPairs ();

        if (transport->isPlaying ())
            doAllNotesOff = true;
    }

    dumpMidiMessageSequence (midiSequence);
}

//==============================================================================
void MidiSequencePluginBase::savePropertiesToXml (XmlElement* xml)
{
    BasePlugin::savePropertiesToXml (xml);

    xml->setAttribute (PROP_SEQROWOFFSET,            getIntValue (PROP_SEQROWOFFSET, 0));
    xml->setAttribute (PROP_SEQCOLSIZE,              getIntValue (PROP_SEQCOLSIZE, 100));
    xml->setAttribute (PROP_SEQNOTELENGTH,           getIntValue (PROP_SEQNOTELENGTH, 4));
    xml->setAttribute (PROP_SEQNOTESNAP,             getIntValue (PROP_SEQNOTESNAP, 4));
    xml->setAttribute (PROP_SEQBAR,                  getIntValue (PROP_SEQBAR, 4));
    xml->setAttribute (PROP_SEQENABLED,              getBoolValue (PROP_SEQENABLED, true));
}

void MidiSequencePluginBase::loadPropertiesFromXml (XmlElement* xml)
{
    BasePlugin::loadPropertiesFromXml (xml);

    setValue (PROP_SEQROWOFFSET,                     xml->getIntAttribute (PROP_SEQROWOFFSET, 0));
    setValue (PROP_SEQCOLSIZE,                       xml->getIntAttribute (PROP_SEQCOLSIZE, 100));
    setValue (PROP_SEQNOTELENGTH,                    xml->getIntAttribute (PROP_SEQNOTELENGTH, 4));
    setValue (PROP_SEQNOTESNAP,                      xml->getIntAttribute (PROP_SEQNOTESNAP, 4));
    setValue (PROP_SEQBAR,                           xml->getIntAttribute (PROP_SEQBAR, 4));
    setValue (PROP_SEQENABLED,                       xml->getBoolAttribute (PROP_SEQENABLED, true));
}

//==============================================================================
AudioProcessorEditor* MidiSequencePluginBase::createEditor ()
{
    return new SequenceComponent (this);
}

void MidiSequencePluginBase::setSequence(const MidiMessageSequence* mseq)
{
	if (mseq)
	{
		deleteAndZero(midiSequence);
		midiSequence = new MidiMessageSequence(*mseq);
        midiSequence->updateMatchedPairs();
	}
}

int MidiSequencePluginBase::getLoopRepeatIndex() 
{ 
	return static_cast<int>(floor(transport->getPositionInBeats())) / getLengthInBeats(); 
}

double MidiSequencePluginBase::getLoopBeatPosition() 
{
	return transport->getPositionInBeats() - (getLoopRepeatIndex() * getLengthInBeats()); 
}

