/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2008 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2008 by Julian Storer.

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

   @author  haydxn
   @tweaker Lucio Asnaghi

 ==============================================================================
*/

#include "MidiNoteMapFilter.h"
#include "MidiNoteMapEditor.h"

//==============================================================================
MidiNoteMapFilter::MidiNoteMapFilter()
{
    lastUIWidth = 550;
    lastUIHeight = 320;
}

MidiNoteMapFilter::~MidiNoteMapFilter()
{
}

//==============================================================================
int MidiNoteMapFilter::getNumParameters()
{
    return 1;
}

float MidiNoteMapFilter::getParameter (int index)
{
    return 0.0f;
}

void MidiNoteMapFilter::setParameter (int index, float newValue)
{
    if (index == 0)
    {
    }
}

const String MidiNoteMapFilter::getParameterName (int index)
{
    if (index == 0)
        return T("N/A");

    return String::empty;
}

const String MidiNoteMapFilter::getParameterText (int index)
{
    return String::empty;
}

//==============================================================================
void MidiNoteMapFilter::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // do your pre-playback setup stuff here..
}

void MidiNoteMapFilter::releaseResources()
{
    // when playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void MidiNoteMapFilter::processBlock (AudioSampleBuffer& buffer,
                                      MidiBuffer& midiMessages)
{
/*
    if (accumulateOutput)
    {
        // if we're accumulating, we should add our results to the existing contents of the
        // output buffer..

        if (input.getNumChannels() > 0)
        {
            for (int channel = 0; channel < output.getNumChannels(); ++channel)
            {
                // for each output channel, add the contents of the corresponding
                // input channel (or if there are more outputs than inputs, just
                // keep using the last input channel)
                output.addFrom (channel,
                                0,
                                input,
                                jmin (channel, input.getNumChannels() - 1),
                                0,
                                input.getNumSamples());
            }
        }
    }
    else
    {
        // if we're not accumulating, the output buffer's contents are undefined
        // (don't assume they're zero!) and we should overwrite it.

        if (input.getNumChannels() > 0)
        {
            for (int channel = 0; channel < output.getNumChannels(); ++channel)
            {
                // for each output channel, copy the contents of the corresponding
                // input channel (or if there are more outputs than inputs, just
                // keep using the last input channel)
                output.copyFrom (channel,
                                 0,
                                 input,
                                 jmin (channel, input.getNumChannels() - 1),
                                 0,
                                 input.getNumSamples());
            }

//           output.applyGain (0, output.getNumSamples(), gain);
        }
        else
        {
            // when not accumulating, you always have to put something into
            // the output buffer, even if in this case we have no inputs to copy.
            output.clear();
        }
    }
*/

    // if any midi messages come in, use them to update the keyboard state object. This
    // object sends notification to the UI component about key up/down changes

	if (!midiMessages.isEmpty ())
	{
		MidiBuffer::Iterator i (midiMessages);
		MidiMessage m (0);
		int pos;
		while (i.getNextEvent (m, pos))
		{
			// if it's a note message...
			if (m.isNoteOnOrOff ())
			{
				NoteMap& map = maps.getMapForChannel (m.getChannel ());
				// alter the message according to the map...
				int note = m.getNoteNumber ();
				m.setNoteNumber (map.getOutputNoteFor (note));
				m.setChannel (map.getOutputChannelFor (note));
			}
			// put the message in the output buffer...
			midiOutput.addEvent (m, pos);
		}
	}

	midiMessages.clear ();
	midiMessages = midiOutput;
	midiOutput.clear ();

//	keyboardState.processNextMidiBuffer (midiMessages,
//                                         0, output.getNumSamples(),
//                                         true);
}

//==============================================================================
AudioProcessorEditor* MidiNoteMapFilter::createEditor()
{
    return new MidiNoteMapEditor (this);
}

//==============================================================================
void MidiNoteMapFilter::getStateInformation (MemoryBlock& destData)
{
    // create an outer XML element..
    XmlElement xmlState (T("MidiNoteMap"));

    // add some attributes to it..

    // you could also add as many child elements as you need to here..
    xmlState.addChildElement (maps.xml ());
    // then use this helper function to stuff it into the binary blob and return it..
    copyXmlToBinary (xmlState, destData);
}

void MidiNoteMapFilter::setStateInformation (const void* data, int sizeInBytes)
{
    // use this helper function to get the XML from this binary blob..
    XmlElement* const xmlState = getXmlFromBinary (data, sizeInBytes);

    if (xmlState != 0)
    {
        // check that it's the right type of xml..
        if (xmlState->hasTagName (T("MidiNoteMap")))
        {
            maps.processXml (xmlState->getChildByName (T("InputChannels")));
            sendChangeMessage (this);
        }

        delete xmlState;
    }
}

//==============================================================================
NoteMap* MidiNoteMapFilter::getMap (int channel)
{
    return &(maps.getMapForChannel (channel));
}

SixteenChannelMaps& MidiNoteMapFilter::getChannelMaps ()
{
    return maps;
}

//==============================================================================
/**
    This function must be implemented to create the actual plugin object that
    you want to use.
*/
AudioProcessor* JUCE_CALLTYPE createPluginFilter (const String& commandLine)
{
    return new MidiNoteMapFilter();
}

