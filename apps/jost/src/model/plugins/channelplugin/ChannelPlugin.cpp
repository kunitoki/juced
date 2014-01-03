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


#include "ChannelPlugin.h"
#include "../../../ui/plugins/PluginEditorComponent.h"
#include "ChannelEditor.h"


//==============================================================================
ChannelPlugin::ChannelPlugin (const int numChannels_, HostFilterBase* base_)
  : numChannels (numChannels_),
    base (base_),
    hoster(0)
{
    setValue (PROP_GRAPHXPOS, 300);
    setValue (PROP_GRAPHYPOS, 2);

	//default GUI size
	lastUIWidth = 200;
    lastUIHeight = 300;


	// add the default subhost
    hoster = new ChannelHost (base, numChannels, numChannels, this);
}

ChannelPlugin::~ChannelPlugin ()
{
	deleteAndZero (hoster);
}

int ChannelPlugin::getType() const
{
	// We can have a mono or stereo plugin

	switch (numChannels)
	{
    case 2:
        return JOST_PLUGINTYPE_CHANNELSTEREO;
    case 1:
    default:
	    return JOST_PLUGINTYPE_CHANNEL;
	}
}

void ChannelPlugin::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	hoster->prepareToPlay (sampleRate, samplesPerBlock);   
}

void ChannelPlugin::releaseResources()
{
    hoster->releaseResources();
}

//==============================================================================
void ChannelPlugin::processBlock (AudioSampleBuffer& buffer,
                                MidiBuffer& midiMessages)
{
    const int blockSize = buffer.getNumSamples ();

#if JucePlugin_WantsMidiInput
    MidiBuffer* midiBuffer = midiBuffers.getUnchecked (0);

    if (midiMessages.getNumEvents() > 0)
        *midiBuffer = midiMessages;
#endif

#if JucePlugin_ProducesMidiOutput

    if (midiBuffer->getNumEvents() > 0)
        midiMessages = *midiBuffer;
#endif

	hoster->processBlock (buffer, *midiBuffer);

    for (int i = 0; i < numChannels; i++)
    {
        outputBuffer->copyFrom (i,
                                0,
                                buffer.getSampleData (i),
                                blockSize);
    }
}

//==============================================================================
void ChannelPlugin::getStateInformation (MemoryBlock& destData)
{
	XmlElement xmlState (T("CHANNELPLUGINSETTINGS"));
	
    // add some attributes to it..
    xmlState.setAttribute (T("editorwidth"), lastUIWidth);
	xmlState.setAttribute (T("editorheight"), lastUIHeight);
	
	XmlElement* sub = new XmlElement (T("CHANNELPLUGINSETTINGS"));
    hoster->saveToXml (sub);
    xmlState.addChildElement (sub);
	
    // then use this helper function to stuff it into the binary blob and return it..
    copyXmlToBinary (xmlState, destData);
}
void ChannelPlugin::setStateInformation (const void* data, int sizeInBytes)
{

	XmlElement* const xmlState = getXmlFromBinary (data, sizeInBytes);
	
    if (xmlState != 0)
    {
        // check that it's the right type of xml..
        if (xmlState->hasTagName (T("CHANNELPLUGINSETTINGS")))
        {
			lastUIWidth = (int) xmlState->getIntAttribute (T("editorwidth"), 200);
			lastUIHeight = (int) xmlState->getIntAttribute (T("editorheight"), 300);
			
			XmlElement* sub = xmlState->getChildByName (T("CHANNELPLUGINSETTINGS"));
            if (sub)
            {
				hoster->loadFromXml (sub);
			}
			
            sendChangeMessage (this);
        }
		
        delete xmlState;
		
	}
}

AudioProcessorEditor* ChannelPlugin::createEditor ()
{
	return new ChannelEditor (this);
}

ChannelEditor* ChannelPlugin::getEditor()
{
    return (ChannelEditor*) getActiveEditor();
}

Transport* ChannelPlugin::getTransport()
{
	return base->getTransport();
}

//==============================================================================
//Please don't touch this function
void ChannelPlugin::autoOpenTrack(BasePlugin *plugin)
{
//	getEditor()->openTrackEditorContainer(plugin);
}
