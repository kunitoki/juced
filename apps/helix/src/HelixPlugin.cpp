/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2008 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2004 by Julian Storer.

 ------------------------------------------------------------------------------

 JUCE and JUCETICE can be redistributed and/or modified under the terms of
 the GNU General Public License, as published by the Free Software Foundation;
 either version 2 of the License, or (at your option) any later version.

 JUCE and JUCETICE are distributed in the hope that they will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with JUCE and JUCETICE; if not, visit www.gnu.org/licenses or write to
 Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 Boston, MA 02111-1307 USA

 ------------------------------------------------------------------------------

 If you'd like to release a closed-source product which uses JUCE, commercial
 licenses are also available: visit www.rawmaterialsoftware.com/juce for
 more information.

 ==============================================================================
*/

#include "HelixPlugin.h"
#include "HelixComponent.h"

//==============================================================================
int HelixPlugin::numInstances = 0;

//==============================================================================
HelixPlugin::HelixPlugin()
{
    DBG ("HelixPlugin::HelixPlugin");

    // defaults !
    Params* p = s.getParams();

    // setup parameters
    setNumParameters (p->data.size());

    // output params
    for (int i = 0; i < p->data.size(); i++)
    {
        AudioParameter* param = new AudioParameter ();
        param->name (p->data[i].GetLongName ().c_str());
        param->part (i);
        param->set (MakeDelegate (this, &HelixPlugin::setGenericParameter));
        param->get (MakeDelegate (this, &HelixPlugin::getGenericParameter));
        param->text (MakeDelegate (this, &HelixPlugin::getParameterDisplay));

        registerParameter (i, param);
    }
}

HelixPlugin::~HelixPlugin()
{
    DBG ("HelixPlugin::~HelixPlugin");

    removeAllParameters (true);

    if (--HelixPlugin::numInstances == 0)
    {
    }
}

//==============================================================================
float HelixPlugin::getGenericParameter (int index)
{
	Params* p = s.getParams();

	if (index >= p->data.size())
		return 0;

	return p->data[index].GetSliderValue();
}

void HelixPlugin::setGenericParameter (int index, float value)
{
	Params* p = s.getParams();

	if (index >= p->data.size())
		return;

	p->data[index].SetValueFromSlider (value);
}

String HelixPlugin::getParameterNameLong (int index)
{
    Params* p = s.getParams();

    return String (p->data[index].GetLongName ().c_str());
}

const String HelixPlugin::getParameterDisplay (int index, float value)
{
    Params* p = s.getParams();
    
    char displayText [512];
    p->data[index].GetDisplay(displayText);

    return String (displayText);
}

//==============================================================================
void HelixPlugin::prepareToPlay (double newSampleRate, int samplesPerBlock)
{
	s.setSampleRate (newSampleRate);
}

void HelixPlugin::releaseResources()
{
}

void HelixPlugin::processBlock (AudioSampleBuffer& buffer,
                                MidiBuffer& midiMessages)
{
    // start processing    
    int blockSamples = buffer.getNumSamples();
    buffer.clear ();

    // if any midi messages come in, use them to update the keyboard state object. This
    // object sends notification to the UI component about key up/down changes
    keyboardState.processNextMidiBuffer (midiMessages,
                                         0, blockSamples,
                                         true);

    // process incoming midi
    midiAutomatorManager.handleMidiMessageBuffer (midiMessages);

	long currentOffset = 0, currentLength = 0;
	float *outs_left = buffer.getSampleData (0);
	float *outs_right = buffer.getSampleData (1);

    int sampleNumber;
    MidiBuffer::Iterator midiIterator (midiMessages);
    MidiMessage midiMessage (0xf4);

    while (midiIterator.getNextEvent (midiMessage, sampleNumber))
    {
        if (midiMessage.isNoteOn())
        {
            s.noteOn (midiMessage.getNoteNumber(), midiMessage.getFloatVelocity());
        }
        else if (midiMessage.isNoteOff())
        {
            s.noteOff (midiMessage.getNoteNumber());
        }
        else if (midiMessage.isAllNotesOff())
        {
            s.noteOffAll();
        }
        else
        {
            uint8* rawData = midiMessage.getRawData ();
            s.RawMidi (rawData[0] & 0xf0, rawData[1], rawData[2]);
        }

        currentLength = (sampleNumber - currentOffset);

        if (currentLength > 0)
        {
            s.process (outs_left, outs_right, currentLength, false);
            currentOffset += currentLength;
            outs_left += currentLength;
    		outs_right += currentLength;
        }
    }
    
    if (currentOffset < blockSamples)
        s.process (outs_left, outs_right, blockSamples - currentOffset, false);
}

//==============================================================================
void HelixPlugin::getStateInformation (MemoryBlock& destData)
{
#ifndef JUCE_DEBUG
    try
    {
#endif

/*
        MemoryBlock tempBlock;
        XmlElement xml (T("preset"));
        xml.setAttribute (T("version"), JucePlugin_VersionCode);

        for (int i = 0; i < getNumParameters (); i++)
        {
            XmlElement* e = new XmlElement (T("p"));
            e->setAttribute (T("key"), i);
            e->setAttribute (T("value"), (double) getParameter (i));
            xml.addChildElement (e);
        }

        String xmlString = xml.createDocument (String::empty);
        destData.append ((const char*) xmlString, xmlString.length());
*/

#ifndef JUCE_DEBUG
    }
    catch (...)
    {
        AlertWindow::showMessageBox (AlertWindow::WarningIcon,
                                     T("Error !"),
                                     T("Something bad occurred while saving presets data !"));
    }
#endif
}

void HelixPlugin::setStateInformation (const void* data, int sizeInBytes)
{
    suspendProcessing (true);

#ifndef JUCE_DEBUG
    try
    {
#endif

/*
        if (data && sizeInBytes > 0)
        {
            XmlDocument xmlDoc ((char*) data);

            //DBG (String ((char*) data));

            XmlElement* xml = xmlDoc.getDocumentElement();
            if (xml == 0 || ! xml->hasTagName (T("preset")))
            {
                String errString = xmlDoc.getLastParseError();
                printf ("Error restoring preset: %s \n", (const char*) errString);
            }
            else
            {
                // TODO - take care of versioning
                // int version = xml->getIntAttribute (T("version"), -1);

                forEachXmlChildElement (*xml, e)
                {
                    if (e->hasTagName (T("p")))
                    {
                        int key = e->getIntAttribute (T("key"), -1);
                        double value = e->getDoubleAttribute (T("value"), 0.0f);
                        
                        if (key >= 0 && key < getNumParameters ())
                            setParameter (key, (float) value);
                    }
                }

                delete xml;
            }

            sendChangeMessage (this);
        }
*/

#ifndef JUCE_DEBUG
    }
    catch (...)
    {
        AlertWindow::showMessageBox (AlertWindow::WarningIcon,
                                     T("Error !"),
                                     T("Something bad occurred while restoring presets data !"));
    }
#endif

    suspendProcessing (false);
}

//==============================================================================
HelixComponent* HelixPlugin::getEditor()
{
    return (HelixComponent*) getActiveEditor();
}

AudioProcessorEditor* HelixPlugin::createEditor()
{
    return new HelixComponent (this);
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter (const String& createArgs)
{
    if (HelixPlugin::numInstances++ == 0)
    {
    }

    return new HelixPlugin();
}

