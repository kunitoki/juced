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

#include "xMonFilter.h"
#include "xMonEditor.h"


//==============================================================================
/**
    This function must be implemented to create a new instance of your
    plugin object.
*/
AudioProcessor* JUCE_CALLTYPE createPluginFilter (const String& commandLine)
{
    return new DemoJuceFilter();
}

//==============================================================================
DemoJuceFilter::DemoJuceFilter()
{
    gain = 1.0f;
    lastUIWidth = 400;
    lastUIHeight = 400;

	incomingMidiMessages.clear();
}

DemoJuceFilter::~DemoJuceFilter()
{
}

//==============================================================================
const String DemoJuceFilter::getName() const
{
    return "xJuno";
}

int DemoJuceFilter::getNumParameters()
{
    return 1;
}

float DemoJuceFilter::getParameter (int index)
{
    return (index == 0) ? gain
                        : 0.0f;
}

void DemoJuceFilter::setParameter (int index, float newValue)
{
    if (index == 0)
    {
        if (gain != newValue)
        {
            gain = newValue;

            // if this is changing the gain, broadcast a change message which
            // our editor will pick up.
            sendChangeMessage (this);
        }
    }
}

const String DemoJuceFilter::getParameterName (int index)
{
    if (index == 0)
        return T("gain");

    return String::empty;
}

const String DemoJuceFilter::getParameterText (int index)
{
    if (index == 0)
        return String (gain, 2);

    return String::empty;
}

const String DemoJuceFilter::getInputChannelName (const int channelIndex) const
{
    return String (channelIndex + 1);
}

const String DemoJuceFilter::getOutputChannelName (const int channelIndex) const
{
    return String (channelIndex + 1);
}

bool DemoJuceFilter::isInputChannelStereoPair (int index) const
{
    return false;
}

bool DemoJuceFilter::isOutputChannelStereoPair (int index) const
{
    return false;
}

bool DemoJuceFilter::acceptsMidi() const
{
    return true;
}

bool DemoJuceFilter::producesMidi() const
{
    return true;
}

//==============================================================================
void DemoJuceFilter::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // do your pre-playback setup stuff here..
}

void DemoJuceFilter::releaseResources()
{
    // when playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void DemoJuceFilter::processBlock (AudioSampleBuffer& buffer,
                                   MidiBuffer& midiMessages)
{
    // for each of our input channels, we'll attenuate its level by the
    // amount that our volume parameter is set to.
    for (int channel = 0; channel < getNumInputChannels(); ++channel)
    {
        buffer.applyGain (channel, 0, buffer.getNumSamples(), gain);
    }

    // in case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }

	// clear all messages in input buffer and fill with current data
	if (!midiMessages.isEmpty())
	{
		incomingMidiMessages.clear();
		incomingMidiMessages = midiMessages;

		sendChangeMessage (this);
	}
}

//==============================================================================
AudioProcessorEditor* DemoJuceFilter::createEditor()
{
    return new DemoEditorComponent (this);
}

//==============================================================================
void DemoJuceFilter::getStateInformation (MemoryBlock& destData)
{
    // you can store your parameters as binary data if you want to or if you've got
    // a load of binary to put in there, but if you're not doing anything too heavy,
    // XML is a much cleaner way of doing it - here's an example of how to store your
    // params as XML..

    // create an outer XML element..
    XmlElement xmlState (T("MYPLUGINSETTINGS"));

    // add some attributes to it..
    xmlState.setAttribute (T("pluginVersion"), 1);
    xmlState.setAttribute (T("gainLevel"), gain);
    xmlState.setAttribute (T("uiWidth"), lastUIWidth);
    xmlState.setAttribute (T("uiHeight"), lastUIHeight);

    // you could also add as many child elements as you need to here..


    // then use this helper function to stuff it into the binary blob and return it..
    copyXmlToBinary (xmlState, destData);
}

void DemoJuceFilter::setStateInformation (const void* data, int sizeInBytes)
{
    // use this helper function to get the XML from this binary blob..
    XmlElement* const xmlState = getXmlFromBinary (data, sizeInBytes);

    if (xmlState != 0)
    {
        // check that it's the right type of xml..
        if (xmlState->hasTagName (T("MYPLUGINSETTINGS")))
        {
            // ok, now pull out our parameters..
            gain = (float) xmlState->getDoubleAttribute (T("gainLevel"), gain);

            lastUIWidth = xmlState->getIntAttribute (T("uiWidth"), lastUIWidth);
            lastUIHeight = xmlState->getIntAttribute (T("uiHeight"), lastUIHeight);

            sendChangeMessage (this);
        }

        delete xmlState;
    }
}
