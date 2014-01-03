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

#include "OutputPlugin.h"
#include "../../ui/plugins/PluginEditorComponent.h"


//==============================================================================
OutputPlugin::OutputPlugin (const int numChannels_)
  : numChannels (numChannels_)
{
    setValue (PROP_GRAPHXPOS, 300);
    setValue (PROP_GRAPHYPOS, 400);
}

OutputPlugin::~OutputPlugin ()
{
}

//==============================================================================
void OutputPlugin::processBlock (AudioSampleBuffer& buffer,
                                 MidiBuffer& midiMessages)
{
    const int blockSize = buffer.getNumSamples ();
    const float desiredOutputGain = mutedOutput ? 0.0f : outputGain;

#if JucePlugin_ProducesMidiOutput
    MidiBuffer* midiBuffer = midiBuffers.getUnchecked (0);

    if (midiBuffer->getNumEvents() > 0)
        midiMessages = *midiBuffer;
#endif

    for (int i = 0; i < outputBuffer->getNumChannels(); i++)
    {
        // copy to internal buffer (metering purpose)
        outputBuffer->copyFromWithRamp (i,
                                        0,
                                        inputBuffer->getSampleData (i),
                                        blockSize,
                                        currentOutputGain,
                                        desiredOutputGain);

		// TODO - apply a soft clipper here or AutoGainReduction instead ?

		// check for bad bad clipping!
		float max = outputBuffer->getMagnitude(i, 0, blockSize);
		if (max > 0.99999)
		{
			DBG ("MEGA BAD CLIPPING DETECTED!!");
			outputBuffer->applyGain(i, 0, blockSize, 0.6 / max); // if detected, the frame is attenuated to within 0.6 
		}
    }


    int numActiveOutChans = 0;
    const int numOutputsTotal = outputBuffer->getNumChannels();
    const int numOutputsWanted = buffer.getNumChannels();

    for (int i = 0; i < jmin (numOutputsWanted, numOutputsTotal); ++i)
    {
        // copy inputs to our intenal buffer
        buffer.copyFrom (numActiveOutChans++,
                         0,
                         outputBuffer->getSampleData (i),
                         blockSize);    
    }

    while (numActiveOutChans < numOutputsWanted)
    {
        buffer.clear (numActiveOutChans++, 0, buffer.getNumSamples());
    }

    currentOutputGain = desiredOutputGain;
}

//==============================================================================
AudioProcessorEditor* OutputPlugin::createEditor ()
{
    return 0;
}

