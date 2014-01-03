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

#include "MidiSequencePlugin.h"
#include "SequenceComponent.h"

#define NOTE_PREFRAMES     0.001
#define NOTE_CHANNEL 1

//==============================================================================
MidiSequencePlugin::MidiSequencePlugin()
:
	MidiSequencePluginBase ()
{
}

MidiSequencePlugin::~MidiSequencePlugin ()
{
}

//==============================================================================
AudioProcessorEditor* MidiSequencePlugin::createEditor ()
{
    return new SequenceComponent (this);
}

//==============================================================================
void MidiSequencePlugin::getControllerIndexed (const int index, int& controllerNum, double& value, double& beat)
{
    int numNoteOn = 0;
    for (int i = 0; i < midiSequence->getNumEvents (); i++)
    {
        MidiMessageSequence::MidiEventHolder* eventOn = midiSequence->getEventPointer (i);

        MidiMessage* msgOn = & eventOn->message;
        if (eventOn->message.isController ())
        {
            if (index == numNoteOn)
            {
				controllerNum = msgOn->getControllerNumber();
                value = msgOn->getControllerValue () / 127.0;
                beat = msgOn->getTimeStamp ();
                break;
            }
            numNoteOn++;
        }
    }
}

//==============================================================================
int MidiSequencePlugin::getNumControllerEvents () const
{
    int numNoteOn = 0;

    for (int i = 0; i < midiSequence->getNumEvents (); i++)
        if (midiSequence->getEventPointer (i)->message.isController ()) numNoteOn++;

    return numNoteOn;
}

//==============================================================================
bool MidiSequencePlugin::eventAdded (const int controller, const double automationValue, const float beatNumber)
{
    MidiMessage msgOn = MidiMessage::controllerEvent (NOTE_CHANNEL, controller, automationValue * 127);
    msgOn.setTimeStamp (beatNumber);

    DBG ("Adding:" +String (automationValue) + " " + String (beatNumber));

    {
    const ScopedLock sl (parentHost->getCallbackLock ());

    midiSequence->addEvent (msgOn);
    }

    DBG ("Added:" + String (automationValue) + " " + String (beatNumber));

    return true;
}

//==============================================================================
bool MidiSequencePlugin::eventRemoved (const int controller, const double automationValue, const float beatNumber)
{
    DBG ("Removing:" + String (automationValue) + " " + String (beatNumber));

    double noteOnBeats = beatNumber - NOTE_PREFRAMES;

    int eventIndex = midiSequence->getNextIndexAtTime (noteOnBeats);
    while (eventIndex < midiSequence->getNumEvents ())
    {
        MidiMessage* eventOn = &midiSequence->getEventPointer (eventIndex)->message;

        if (eventOn->isController() && eventOn->getControllerNumber() == controller && eventOn->getControllerValue() == floor(automationValue * 127))
        {
            {
            const ScopedLock sl (parentHost->getCallbackLock());

            midiSequence->deleteEvent (eventIndex, true);
            }

            DBG ("Removed:" + String (eventIndex) + " > " + String (automationValue) + " @ " + String (beatNumber));

            if (transport->isPlaying ())
                doAllNotesOff = true;

            return true;
        }

        eventIndex++;
    }

    DBG (">>> Remove failed:" + String (automationValue) + " @ " + String (beatNumber));

    return false;
}

//==============================================================================
bool MidiSequencePlugin::eventMoved (
							const int controllerNum,
							const double oldValue,
                            const float oldBeat,
                            const double automationValue,
                            const float beatNumber)
{
    DBG ("Moving:" + String (oldValue) + " " + String (oldBeat));

    double noteOnBeats = oldBeat - NOTE_PREFRAMES;

    int eventIndex = midiSequence->getNextIndexAtTime (noteOnBeats);
    while (eventIndex < midiSequence->getNumEvents ())
    {
        MidiMessage* eventOn = &midiSequence->getEventPointer (eventIndex)->message;


        if (eventOn->isController() && eventOn->getControllerNumber() == controllerNum && eventOn->getControllerValue() == floor(oldValue * 127)) // should make this a "matches controller" method
        {		
		    MidiMessage msgOn = MidiMessage::controllerEvent (NOTE_CHANNEL, controllerNum, automationValue * 127);
    		msgOn.setTimeStamp (beatNumber);
		
			{
			const ScopedLock sl (parentHost->getCallbackLock());

			// remove old events
			midiSequence->deleteEvent (eventIndex, true);
			midiSequence->addEvent (msgOn);
			}

            return true;
        }

        eventIndex++;
    }

    DBG (">>> Move failed:" + String (oldValue) + " @ " + String (oldBeat));

    return false;
}

//==============================================================================
bool MidiSequencePlugin::allEventsRemoved ()
{
// slight trickiness here now that the midisequence is not just notes - need to delete all events, leave notes, and vice versa in notelistener impl..
// but right now this is not practically an issue, as whenever the notes are cleared, the automation is too (when loading a new file)
// leaving this here as a reminder for when "clear automation" & "clear notes" buttons are added to sequencer UI..
/*
    {
    const ScopedLock sl (parentHost->getCallbackLock());

    midiSequence->clear ();

    if (transport->isPlaying ())
        doAllNotesOff = true;

    }
*/
    return true;
}

//==============================================================================
void MidiSequencePlugin::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	MidiSequencePluginBase::processBlock(buffer, midiMessages);
	MidiMessageSequence sourceMidi = *midiSequence;
	
	std::vector<int> doneTheseControllers;

    if (transport->isPlaying () && getBoolValue(PROP_SEQENABLED, true))
    {
		const int blockSize = buffer.getNumSamples ();
		MidiBuffer* midiBuffer = midiBuffers.getUnchecked (0);

        const int frameCounter = transport->getPositionInFrames ();
        const int framesPerBeat = transport->getFramesPerBeat ();
        const int nextBlockFrameNumber = frameCounter + blockSize;
		const int seqIndex = getLoopRepeatIndex();
		const double beatCount = getLoopBeatPosition();
		const double frameLenBeatCount = (nextBlockFrameNumber - frameCounter) / (double)framesPerBeat;		
		double frameEndBeatCount = beatCount + frameLenBeatCount;
		if (frameEndBeatCount > getLengthInBeats())
			frameEndBeatCount -= getLengthInBeats();

		// loop for each controller we need to interpolate
		MidiMessage* lastCtrlEvent = NULL;
		do 
		{
			lastCtrlEvent = NULL;
			
			// hunt for a controller event before now
			int i;
			for (i = 0;	i < sourceMidi.getNumEvents (); i++)
			{
				int timeStampInSeq = roundFloatToInt (sourceMidi.getEventTime (i) * framesPerBeat);
				int timeStamp = timeStampInSeq + (seqIndex * getLengthInBeats() * framesPerBeat);

				MidiMessage* midiMessage = &sourceMidi.getEventPointer (i)->message;
				if (timeStamp >= nextBlockFrameNumber || !midiMessage) 
					break; // event is after now, leave

				//if (midiMessage->isController() && (std::find(doneTheseControllers.begin(), doneTheseControllers.end(), midiMessage->getControllerNumber()) == doneTheseControllers.end()))
				//	lastCtrlEvent = midiMessage;
			}

			// hunt for a matching event after that one
			if (lastCtrlEvent)
			{
				// store the controller number so we know which controllers we've done
				doneTheseControllers.push_back(lastCtrlEvent->getControllerNumber());

				MidiMessage* nextCtrlEvent = NULL;
				for (;	i < sourceMidi.getNumEvents (); i++)
				{
					MidiMessage* midiMessage = &sourceMidi.getEventPointer (i)->message;
					if (midiMessage->isController() && midiMessage->getControllerNumber() == lastCtrlEvent->getControllerNumber())
					{
						nextCtrlEvent = midiMessage;
						break;
					}
				}
			
				// render an interpolated event!...
				if (nextCtrlEvent)
				{
					double bt = nextCtrlEvent->getTimeStamp();
					double at = lastCtrlEvent->getTimeStamp();
					double deltaBeats = bt - at;
					int a = lastCtrlEvent->getControllerValue();
					int b = nextCtrlEvent->getControllerValue();
					double now = beatCount + (frameEndBeatCount - beatCount) / 2.0;
					double interpRemainBeats = deltaBeats - (now - at);
					if (deltaBeats > 0)
					{
						double nextPart = interpRemainBeats / deltaBeats;
						nextPart = 1 - nextPart;
						double interpdVal = a + nextPart * (b - a);
						MidiMessage interpy = MidiMessage::controllerEvent(lastCtrlEvent->getChannel(), lastCtrlEvent->getControllerNumber(), static_cast<int>(interpdVal));
						midiBuffer->addEvent (interpy, (nextBlockFrameNumber - frameCounter) / 2);
					}
					else
					{
						DBG ("Negative delta beats when rendering automation!!");
			        }
				}
			
			} 
			
			// now we also need to do that again if there are multiple events per frame AND we are interpolating multiple times per frame
			// (at the moment only interpolating once per audio frame)
		} while (lastCtrlEvent != NULL);
	}
}

