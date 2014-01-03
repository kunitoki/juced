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

#include "Transport.h"
#include "../HostFilterBase.h"


//==============================================================================
Transport::Transport (HostFilterBase* owner_)
  : owner (owner_),
    sequencePositionCounter (0),
    sequenceDurationFrames (0),
    framesPerBeat (0),
    leftLocator (0),
    rightLocator (1000000000),
    sampleRate (44100.0),
    bpmTempo (120),
    numBars (4),
    divDenominator (4),
    playing (false),
    looping (true),
    recording (false),
    doStopRecord (false),
    doRewind (false),
    doAllNotesOff (false),
    externalTransport (0)
{
    DBG ("Transport::Transport");

#if JOST_USE_VST
    // zero time info
    zerostruct (timeInfo);
#endif
}

Transport::~Transport ()
{
    DBG ("Transport::~Transport");
}

//==============================================================================
void Transport::setExternalTransport (ExternalTransport* externalTransport_)
{
    externalTransport = externalTransport_;

    // TODO - we should make this as change listener !
    /*
    if (externalTransport)
    {
        externalTransport->grabTransport (false);
        externalTransport->stopTransport ();
    }
    */
}

//==============================================================================
void Transport::play ()
{
    DBG ("Transport::play");

    if (! playing)
    {
        playing = true;

        sendChangeMessage (this);

        // TODO - we should make this as change listener !
        if (externalTransport)
#if 0
            && config->externalTempoSync
            && config->externalTempoMaster)
#endif
        {
            externalTransport->playTransport ();
        }
    }
}

void Transport::stop ()
{
    DBG ("Transport::stop");

    if (playing)
    {
        doAllNotesOff = true;
        playing = false;

        if (recording)
            doStopRecord = true;
        else
            sendChangeMessage (this);

        // TODO - we should make this as change listener !
        if (externalTransport)
#if 0
            && config->externalTempoSync
            && config->externalTempoMaster)
#endif
        {
            externalTransport->stopTransport ();
        }
    }
}

void Transport::record ()
{
    DBG ("Transport::record");

    if (playing)
    {
        if (recording && ! doStopRecord)
            doStopRecord = true;
    }
    else
    {
        if (recording)
        {
            recording = false;
            doStopRecord = false;
        }
        else
        {
            recording = true;
            doStopRecord = false;
        }
    }
}

void Transport::rewind ()
{
    DBG ("Transport::rewind");

    if (playing)
    {
        if (recording)
            doStopRecord = true;

        doAllNotesOff = true;
        doRewind = true;
    }
    else
    {
        sequencePositionCounter = leftLocator;
        doRewind = false;
        sendChangeMessage (this);
    }

    // TODO - we should make this as change listener !
    if (externalTransport)
        externalTransport->seekTransportToFrame (0);
}

void Transport::allNotesOff ()
{
    DBG ("Transport::allNotesOff");

    doAllNotesOff = true;
}

void Transport::resetRecording ()
{
    DBG ("Transport::resetRecording");

    doStopRecord = false;
    recording = false;
}

//==============================================================================
void Transport::prepareToPlay (double sampleRate_, int samplesPerBlock_)
{
    DBG ("Transport::prepareToPlay");

    // TODO - we should make this as change listener !
    if (externalTransport)
    {
        externalTransport->grabTransport (false);
        externalTransport->seekTransportToFrame (0);
        externalTransport->stopTransport ();
    }

    sampleRate = sampleRate_;

    setTimeSignature (bpmTempo,         // 120 bpm
                      numBars,          // 4 bars
                      divDenominator);  // 4 beatsXbar

//    setRightLocator (numBars * divDenominator);

#if JOST_USE_VST
    // prepare vsttimeinfo
    timeInfo.samplePos = 0.0;
    timeInfo.sampleRate = sampleRate;
    timeInfo.nanoSeconds = 0.0;
    timeInfo.ppqPos = 0.0;
    timeInfo.tempo = bpmTempo;                        // in bpm
    timeInfo.barStartPos = 0;                         // last bar start, in 1 ppq
    timeInfo.cycleStartPos = 0;                       // 1 ppq
    timeInfo.cycleEndPos = 0;                         // 1 ppq
    timeInfo.barStartPos = 0;                         // last bar start, in 1 ppq
    timeInfo.barStartPos = 0;                         // last bar start, in 1 ppq
    timeInfo.timeSigNumerator = divDenominator;       // time signature numerator
    timeInfo.timeSigDenominator = divDenominator;     // time signature denominator
    timeInfo.smpteOffset = 0;
    timeInfo.smpteFrameRate = 1;
    timeInfo.samplesToNextClock = 0;
    timeInfo.flags = 0 | kVstTransportPlaying
                       | kVstNanosValid
                       | kVstTransportChanged
                       | kVstPpqPosValid
                       | kVstTempoValid
                       | kVstTimeSigValid
                       | kVstClockValid;
                       // kVstBarsValid | kVstCyclePosValid | kVstTimeSigValid | kVstSmpteValid | kVstClockValid
#endif
}

void Transport::releaseResources()
{
    DBG ("Transport::releaseResources");

    if (isPlaying ())
        stop ();

    // TODO - we should make this as change listener !
    if (externalTransport)
        externalTransport->releaseTransport ();
}

void Transport::processBlock (const int blockSize)
{
#if JOST_USE_VST
    timeInfo.tempo = bpmTempo;
    timeInfo.nanoSeconds = (double) Time::getMillisecondCounterHiRes () * 1000000.0;
#endif

    if (playing)
    {
#if JOST_USE_VST
        static double smpteDiv[] = { 24.f, 25.f, 24.f, 30.f, 29.97f, 30.f };

        const double ppqPos = sequencePositionCounter / timeInfo.sampleRate;
        timeInfo.ppqPos = ppqPos * timeInfo.tempo / 60.0;
        timeInfo.smpteOffset = (long) ((ppqPos - floor (ppqPos))
                                       * smpteDiv [timeInfo.smpteFrameRate] * 80.0);
        timeInfo.flags |= kVstTransportPlaying;
        timeInfo.flags &= ~kVstTransportChanged;
#endif

        // we should update rewind button
        if (sequencePositionCounter == leftLocator)
            sendChangeMessage (this);

        // increase counter
        sequencePositionCounter += blockSize;

        // we should update play button
        if (sequencePositionCounter >= sequenceDurationFrames) // rightLocator
        {
            if (looping)
            {
                sequencePositionCounter = leftLocator;
            }
            else
            {
                playing = false;
                sendChangeMessage (this);

#if JOST_USE_VST
                timeInfo.flags &= ~kVstTransportPlaying;
                timeInfo.flags |= kVstTransportChanged;
#endif
            }
        }
    }

    if (doAllNotesOff)
    {
        doAllNotesOff = false;
    }

    if (doRewind)
    {
        sequencePositionCounter = leftLocator;
        doRewind = false;
    }

#if JOST_USE_VST
    timeInfo.samplePos = (float) sequencePositionCounter;
#endif
}

//==============================================================================
void Transport::processAudioPlayHead (AudioPlayHead* head)
{
    AudioPlayHead::CurrentPositionInfo info;
    if (head->getCurrentPosition (info))
    {
/*
        std::cout << "bpm " << info.bpm << std::endl;
        std::cout << "timeSigNumerator " << info.timeSigNumerator << std::endl;
        std::cout << "timeSigDenominator " << info.timeSigDenominator << std::endl;
        std::cout << "timeInSeconds " << info.timeInSeconds << std::endl;
        std::cout << "ppqPosition " << info.ppqPosition << std::endl;
        std::cout << "ppqPositionOfLastBarStart " << info.ppqPositionOfLastBarStart << std::endl;
        std::cout << "frameRate " << info.frameRate << std::endl;
        std::cout << "isPlaying" << info.isPlaying << std::endl;
        std::cout << std::endl;
*/
    }
}

void Transport::processIncomingMidi (MidiBuffer& midiMessages)
{
    int hours, minutes, seconds, frames;

    int samplePosition;
    MidiMessage msg (0xf4, 0.0);
    MidiBuffer::Iterator it (midiMessages);

    while (it.getNextEvent (msg, samplePosition))
    {
        if (msg.isNoteOnOrOff ())
            continue;

        if (msg.isTimeSignatureMetaEvent ())
        {
            int newNumerator, newDenominator;

            msg.getTimeSignatureInfo (newNumerator, newDenominator);

            setTimeSignature (bpmTempo,
                              numBars,
                              newDenominator);
        }
        else if (msg.isTempoMetaEvent ())
        {
            // double  getTempoMetaEventTickLength (const short timeFormat) const throw ()
            DBG ("isTempoMetaEvent " + String (msg.getTempoSecondsPerQuarterNote ()));
//            leftLocator = jmax (0, roundFloatToInt (beatNumber * framesPerBeat));
        }
        else if (msg.isMidiStart ())
        {
            rewind ();
            play ();
        }
        else if (msg.isMidiContinue ())
        {
            play ();
        }
        else if (msg.isMidiStop ())
        {
            stop ();
        }
        else if (msg.isSongPositionPointer ())
        {
            DBG ("isSongPositionPointer " + String (msg.getSongPositionPointerMidiBeat ()));
        }
        else if (msg.isQuarterFrame ())
        {
            DBG ("isQuarterFrame " + String (msg.getQuarterFrameSequenceNumber ())
                             + " " + String (msg.getQuarterFrameValue ()));
        }
        else if (msg.isFullFrame ())
        {
            // void    getFullFrameParameters (int &hours, int &minutes, int &seconds, int &frames, SmpteTimecodeType &timecodeType) const throw ()
        }
        else if (msg.isMidiMachineControlGoto (hours, minutes, seconds, frames))
        {
        }
    }
}

//==============================================================================
void Transport::setTimeSignature (const int bpmTempo_,
                                  const int barsCount_,
                                  const int timeDenominator_)
{
    bpmTempo = bpmTempo_;
    numBars = barsCount_;
    divDenominator = timeDenominator_;

    framesPerBeat = roundFloatToInt (sampleRate * 60.0 / (float) bpmTempo);
    sequenceDurationFrames = framesPerBeat * (numBars * divDenominator);

//    setRightLocator (rightLocator / (float) framesPerBeat);

//    if (playing)
//        doAllNotesOff = true;

    if (sequencePositionCounter >= sequenceDurationFrames)
        doRewind = true;

    sendChangeMessage (this);

    // TODO - we should make this as change listener !
    if (externalTransport)
        externalTransport->setTempo (bpmTempo);
}

void Transport::setLeftLocator (const float beatNumber)
{
    leftLocator = jmax (0, roundFloatToInt (beatNumber * framesPerBeat));

    sendChangeMessage (this);
}

void Transport::setRightLocator (const float beatNumber)
{
//    rightLocator = jmin (sequenceDurationFrames, roundFloatToInt (beatNumber * framesPerBeat));
    rightLocator = sequenceDurationFrames;

    sendChangeMessage (this);
}

//==============================================================================
void Transport::setTempo (const int newTempo)
{
    setTimeSignature (newTempo, numBars, divDenominator);
}

//==============================================================================
void Transport::setPositionAbsolute (const float newPos)
{
    sequencePositionCounter = roundFloatToInt (newPos * sequenceDurationFrames);

    if (playing)
        doAllNotesOff = true;

    sendChangeMessage (this);

    // TODO - we should make this as change listener !
    if (externalTransport)
        externalTransport->seekTransportToFrame (sequencePositionCounter);
}

//==============================================================================
void Transport::saveToXml (XmlElement* xml)
{
    xml->setAttribute (T("tempo"), bpmTempo);
    xml->setAttribute (T("bars"), numBars);
    xml->setAttribute (T("numerator"), divDenominator);
    xml->setAttribute (T("denominator"), divDenominator);
    xml->setAttribute (T("ppq"), 960 /* ppq */);
    xml->setAttribute (T("position"), getPositionAbsolute());
    xml->setAttribute (T("llocator"), getLeftLocator());
    xml->setAttribute (T("rlocator"), getRightLocator());
    xml->setAttribute (T("looping"), looping);
}

void Transport::loadFromXml (XmlElement* xml)
{
//    divNumerator = xml->getIntAttribute (T("numerator"), 4);
//    ppq = xml->getIntAttribute (T("ppq"), 960);

    setTimeSignature (xml->getIntAttribute (T("tempo"), 120),
                      xml->getIntAttribute (T("bars"), 4),
                      xml->getIntAttribute (T("denominator"), 4));

    setPositionAbsolute (xml->getDoubleAttribute (T("position"), 0.0));
    setLeftLocator (xml->getDoubleAttribute (T("llocator"), 0.0));
    setRightLocator (xml->getDoubleAttribute (T("rlocator"), 1.0));
    looping = xml->getIntAttribute (T("looping"), 1) == 1;

    sendChangeMessage (this);
}


