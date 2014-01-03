/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  27 Jul 2008 12:24:04 pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.11

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#include "MidiMonitorEditor.h"
#include "MidiMonitorPlugin.h"


//==============================================================================
MidiMonitorEditor::MidiMonitorEditor (MidiMonitorPlugin* owner_)
    : PluginEditorComponent (owner_),
      owner (owner_)
{
	addAndMakeVisible (midiOutputEditor = new TextEditor (String::empty));
	midiOutputEditor->setReadOnly(true);
	midiOutputEditor->setMultiLine (true, true);

    addAndMakeVisible (saveButton = new TextButton (String::empty));
    saveButton->setButtonText (T("save recorded data"));
    saveButton->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    saveButton->addButtonListener (this);
    saveButton->setEnabled (false);

    addAndMakeVisible (clearButton = new TextButton (String::empty));
    clearButton->setButtonText (T("clear recorded data"));
    clearButton->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    clearButton->addButtonListener (this);

    backgroundColour = Config::getInstance()->getColour (T("mainBackground"));

	startTimer (1000 / 10); // 5fps
}

MidiMonitorEditor::~MidiMonitorEditor()
{
    stopTimer ();
    
    deleteAndZero (midiOutputEditor);
}

//==============================================================================
void MidiMonitorEditor::paint (Graphics& g)
{
    g.fillAll (backgroundColour);
}

void MidiMonitorEditor::resized()
{
    const int border = 2;
    const int buttonHeight = 20;

    midiOutputEditor->setBounds (0, 0, getWidth (), getHeight () - 2*border - buttonHeight);

    saveButton->setBounds (border, getHeight () - border - buttonHeight, getWidth () / 2 - 2*border, buttonHeight);
    clearButton->setBounds (border + getWidth () / 2, getHeight () - border - buttonHeight, getWidth () / 2 - 2*border, buttonHeight);
}

//==============================================================================
void MidiMonitorEditor::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == clearButton)
    {
        midiOutputEditor->clear ();
    }
    else if (buttonThatWasClicked == saveButton)
    {
    }
}

//==============================================================================
void MidiMonitorEditor::timerCallback ()
{
    MidiBuffer tmpBuffer;
    int hours, minutes, seconds, frames;
    MidiMessage::SmpteTimecodeType timeCode;
    
    MidiMessageCollector* collector = owner->getMessageCollector ();
    collector->removeNextBlockOfMessages (tmpBuffer, 1024);
    
    if (! tmpBuffer.isEmpty())
	{
        String midiLine;

        int samplePos = 0;
        MidiMessage msg (0xf4, 0.0);
        MidiBuffer::Iterator eventIterator (tmpBuffer);

        while (eventIterator.getNextEvent (msg, samplePos))
        {
           midiLine.printf (T("[CH: %d] "), msg.getChannel());

           if (msg.isNoteOnOrOff ())
           {
                midiLine += MidiMessage::getMidiNoteName (msg.getNoteNumber(),
                                                          true, true, 0);
                midiLine += " ";
                midiLine += String ((int) msg.getVelocity ());

                if (msg.isNoteOn())
                {
                    midiLine += " ON";
                }
                else
                {
                    midiLine += " OFF";
                }
           }
           else if (msg.isAllNotesOff())
           {
                midiLine += "ALL NOTES OFF";
           }
           else if (msg.isAllSoundOff())
           {
                midiLine += "ALL SOUND OFF";
           }
           else if (msg.isPitchWheel())
           {
                midiLine += "PITCHWEEL: ";
                midiLine += String (msg.getPitchWheelValue());
           }
           else if (msg.isAftertouch())
           {
                midiLine += "AFTERTOUCH: ";
                midiLine += String (msg.getAfterTouchValue());
           }
           else if (msg.isChannelPressure())
           {
                midiLine += "CHANNELPRESSURE: ";
                midiLine += String (msg.getChannelPressureValue());
           }
           else if (msg.isSysEx())
           {
                midiLine += "SYSEX: ";
                midiLine += String (msg.getSysExDataSize());
                midiLine += " bytes";
           }
           else if (msg.isProgramChange())
           {
                midiLine += "PROGRAM CHANGE: ";
                midiLine += String (msg.getProgramChangeNumber());
                midiLine += " (";
                midiLine += MidiMessage::getGMInstrumentName (msg.getProgramChangeNumber());
                midiLine += ")";
           }
           else if (msg.isController())
           {
                midiLine += "CC: #";
                midiLine += String (msg.getControllerNumber());
                midiLine += " (";
                midiLine += MidiMessage::getControllerName (msg.getControllerNumber());
                midiLine += ") = ";
                midiLine += String (msg.getControllerValue());
           }
            else if (msg.isTimeSignatureMetaEvent ())
            {
                int newNumerator, newDenominator;
                msg.getTimeSignatureInfo (newNumerator, newDenominator);

                midiLine += "TIME SIGNATURE: ";
                midiLine += String (newNumerator);
                midiLine += " / ";
                midiLine += String (newDenominator);
            }
            else if (msg.isTempoMetaEvent ())
            {
                midiLine += "TEMPO: ";
                midiLine += String (msg.getTempoSecondsPerQuarterNote ());
                //midiLine += " ";
                //midiLine += String (msg.getTempoMetaEventTickLength (ticksPerQuarterNote));
            }
            else if (msg.isMidiMachineControlMessage())
            {
                midiLine += "MIDI CONTROL: ";
                
                switch (msg.getMidiMachineControlCommand())
                {
                    case MidiMessage::mmc_stop:             midiLine += "stop"; break;
                    case MidiMessage::mmc_play:             midiLine += "play"; break;
                    case MidiMessage::mmc_deferredplay:     midiLine += "deferredplay"; break;
                    case MidiMessage::mmc_fastforward:      midiLine += "fastforward"; break;
                    case MidiMessage::mmc_rewind:           midiLine += "rewind"; break;
                    case MidiMessage::mmc_recordStart:      midiLine += "recordStart"; break;
                    case MidiMessage::mmc_recordStop:       midiLine += "recordStop"; break;
                    case MidiMessage::mmc_pause:            midiLine += "pause"; break;
                }
            }
            else if (msg.isMidiStart ())
            {
                midiLine += "MIDI START: ";
            }
            else if (msg.isMidiContinue ())
            {
                midiLine += "MIDI CONTINUE: ";
            }
            else if (msg.isMidiStop ())
            {
                midiLine += "MIDI STOP: ";
            }
            else if (msg.isSongPositionPointer ())
            {
                midiLine += "SONG POSITION: ";
                midiLine += String (msg.getSongPositionPointerMidiBeat ());
            }
            else if (msg.isQuarterFrame ())
            {
                midiLine += "QUARTER FRAME: ";
                midiLine += String (msg.getQuarterFrameSequenceNumber ());
                midiLine += " ";
                midiLine += String (msg.getQuarterFrameValue ());
            }
            else if (msg.isFullFrame ())
            {
                midiLine += "FULL FRAME: ";

                msg.getFullFrameParameters (hours, minutes, seconds, frames, timeCode);

                midiLine += String (hours);
                midiLine += ":";
                midiLine += String (minutes);
                midiLine += ":";
                midiLine += String (seconds);
                midiLine += ":";
                midiLine += String (frames);

                midiLine += " timecode: ";
                switch (timeCode) {
                    case MidiMessage::fps24:      midiLine += "fps24"; break;
                    case MidiMessage::fps25:      midiLine += "fps25"; break;
                    case MidiMessage::fps30drop:  midiLine += "fps30drop"; break;
                    case MidiMessage::fps30:      midiLine += "fps30"; break;
                }
            }
            else if (msg.isMidiMachineControlGoto (hours, minutes, seconds, frames))
            {
                midiLine += "MIDI CONTROL GOTO: ";
                midiLine += String (hours);
                midiLine += ":";
                midiLine += String (minutes);
                midiLine += ":";
                midiLine += String (seconds);
                midiLine += ":";
                midiLine += String (frames);
            }

            midiOutputEditor->insertTextAtCursor (midiLine + T("\n"));
        }

	}

}

//==============================================================================
void MidiMonitorEditor::updateParameters ()
{

}

