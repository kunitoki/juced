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


#include "ChannelInputPlugin.h"
#include "../../ui/plugins/PluginEditorComponent.h"
#include "channelplugin/ChannelPlugin.h"


//==============================================================================
ChannelInputPlugin::ChannelInputPlugin (const int numChannels_, ChannelPlugin* owner_)
  : numChannels (numChannels_),
	owner (owner_)
{
    setValue (PROP_GRAPHXPOS, 300);
    setValue (PROP_GRAPHYPOS, 2);
	
	
}

ChannelInputPlugin::~ChannelInputPlugin ()
{
}

//==============================================================================
void ChannelInputPlugin::processBlock (AudioSampleBuffer& buffer,
                                MidiBuffer& midiMessages)
{
    const int blockSize = buffer.getNumSamples ();

	
//TODO! Midi is not yet well implemented!
#if JucePlugin_WantsMidiInput
    MidiBuffer* midiBuffer = midiBuffers.getUnchecked (0);
	//MidiBuffer* midiInBuffer = owner->getMidiBuffer(0);
	

    if (midiMessages.getNumEvents() > 0)
        *midiBuffer = midiMessages;
		//*midiBuffer = *midiInBuffer;
#endif

	//Copy buffers from ChannelPlugin
    for (int i = 0; i < numChannels; i++)
    {
        outputBuffer->copyFrom (i,
                                0,
                                //buffer.getSampleData (i),
								owner->getInputBuffers()->
								getSampleData (i),
                                blockSize);
    }
}

//==============================================================================
AudioProcessorEditor* ChannelInputPlugin::createEditor ()
{
    return 0;
}

