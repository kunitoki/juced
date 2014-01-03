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

#include "TrackPlugin.h"
#include "../../ui/plugins/PluginEditorComponent.h"
//#include "TrackEditor.h"
#include "../../HostFilterBase.h"


//==============================================================================
TrackPlugin::TrackPlugin (const int numChannels_)
  : numChannels (numChannels_),
  audioFile(0),
  transport(0)

{
    setValue (PROP_GRAPHXPOS, 300);
    setValue (PROP_GRAPHYPOS, 2);

	formatManager.registerBasicFormats();
	/*transporter = getTransport();
	transporter->addChangeListener(this);*/


}

TrackPlugin::~TrackPlugin ()
{

}

void TrackPlugin::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	//transport = getParentHost()->getTransport ();
	//transport = getChannelHost()->getTransport ();

	//This is using a customized version of audioDeviceAboutToStart!!!
	// For now I commented it out, until we change the library

	//  audioSourcePlayer.audioDeviceAboutToStart(sampleRate, samplesPerBlock);
}

void TrackPlugin::releaseResources()
{
 
}

//==============================================================================
void TrackPlugin::processBlock (AudioSampleBuffer& buffer,
                                MidiBuffer& midiMessages)
{
    int blockSize = buffer.getNumSamples ();
	
	
	float* outL [1] = {0};

	for (int i = 0; i < numChannels; i++)
	{
		outL[i] = outputBuffer->getSampleData (i);
	}
		
	audioSourcePlayer.audioDeviceIOCallback(0, 0, outL, 1, blockSize);

}

//==============================================================================
void TrackPlugin::getStateInformation (MemoryBlock& destData)
{

}
void TrackPlugin::setStateInformation (const void* data, int sizeInBytes)
{

}

//==============================================================================
void TrackPlugin::createReader(const StringArray &files)
{
	audioFile = files[0];

	AudioFormatReader* reader = formatManager.createReaderFor (audioFile);
	//AudioClip* clip = getEditor()->clipsGrid->clips.getFirst();
	//AudioFormatReader* reader = clip->getWaveFile();
	DBG(T("Reader Created"))

	if (reader != 0)
	{

	AudioFormatReaderSource* audioSource1 = new AudioFormatReaderSource (reader, true);

	transportSource.setSource (audioSource1,
									   44100,
                                       reader->sampleRate);
	
	audioSourcePlayer.setSource (&transportSource);

playFile();
	}


}


AudioProcessorEditor* TrackPlugin::createEditor ()
{
    return 0;
	//return new TrackEditor (this);

}

/*TrackEditor* TrackPlugin::getEditor()
{
    return (TrackEditor*) getActiveEditor();
}*/
//==============================================================================
void TrackPlugin::playFile()
{
	transportSource.setPosition(0.0);
	transportSource.start();
}
void TrackPlugin::stopFile()
{
	transportSource.stop();
	transportSource.setPosition(0.0);
}
/*void TrackPlugin::changeListenerCallback(void *objectThatHasChanged)
{
	if (objectThatHasChanged == transporter)
    {
        if (transporter->isPlaying ())
        {
         playFile();   
        }
        else if (! transporter->isPlaying ())
        {
            stopFile ();
        }
	}

}*/
