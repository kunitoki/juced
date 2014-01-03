

#include "ChannelOutputPlugin.h"
#include "../../ui/plugins/PluginEditorComponent.h"


//==============================================================================
ChannelOutputPlugin::ChannelOutputPlugin (const int numChannels_)
  : numChannels (numChannels_)
{
    setValue (PROP_GRAPHXPOS, 300);
    setValue (PROP_GRAPHYPOS, 400);
}

ChannelOutputPlugin::~ChannelOutputPlugin ()
{
}

//==============================================================================
void ChannelOutputPlugin::processBlock (AudioSampleBuffer& buffer,
                                 MidiBuffer& midiMessages)
{
    const int blockSize = buffer.getNumSamples ();

#if JucePlugin_ProducesMidiOutput
    MidiBuffer* midiBuffer = midiBuffers.getUnchecked (0);

    if (midiBuffer->getNumEvents() > 0)
        midiMessages = *midiBuffer;
#endif

    for (int i = 0; i < numChannels; i++)
    {
 

		outputBuffer->copyFrom (i,
								0,
								inputBuffer->getSampleData (i),
                                blockSize);

        // copy to real outputs (audio out)
        buffer.copyFrom (i,
                         0,
                         outputBuffer->getSampleData (i),
                         blockSize);

    }

}

//==============================================================================
AudioProcessorEditor* ChannelOutputPlugin::createEditor ()
{
    return 0;
}

