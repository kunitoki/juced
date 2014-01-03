/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004 by Julian Storer.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the
   GNU General Public License, as published by the Free Software Foundation;
   either version 2 of the License, or (at your option) any later version.

   JUCE is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with JUCE; if not, visit www.gnu.org/licenses or write to the
   Free Software Foundation, Inc., 59 Temple Place, Suite 330,
   Boston, MA 02111-1307 USA

  ------------------------------------------------------------------------------

   If you'd like to release a closed-source product which uses JUCE, commercial
   licenses are also available: visit www.rawmaterialsoftware.com/juce for
   more information.

  ==============================================================================
*/

#include "XImpulsePlugin.h"
#include "XImpulseComponent.h"

//==============================================================================
void splitLR (float * data, float * L, float * R,
	          int singleSize, int channels)
{
  for(int t = 0; t < singleSize; t++)
    {
      L[t] = data[t*channels+0];
      if(channels > 1)
	R[t] = data[t*channels+1];
      else
	R[t] = L[t];
   }
}

//==============================================================================
int XImpulsePlugin::numInstances = 0;

//==============================================================================
XImpulsePlugin::XImpulsePlugin()
  : inputBuffers (2, 1)
{    ir = new fv3::irmodel3_f();
    // ir = new fv3::irmodel2();

    // create format manager
    formatManager.registerBasicFormats();

    // initialise effect section
    initialiseToDefault ();
}

XImpulsePlugin::~XImpulsePlugin()
{
    loadImpulseResponse (File::nonexistent);

    deleteAndZero (ir);
}

//==============================================================================
void XImpulsePlugin::initialiseToDefault ()
{
    idb = -5, odb = -25;    

    ir->setdry (idb);
    ir->setwet (odb);
    ir->setwidth (1);

    setNumParameters (NUM_PARAMETERS);

    // GAIN
    registerParameter (PAR_GAIN, &params[PAR_GAIN].name (T("Gain")).unit (T("%"))
                                 .set (MakeDelegate (this, &XImpulsePlugin::setGain))
                                 .get (MakeDelegate (this, &XImpulsePlugin::getGain)));
}

//==============================================================================
float XImpulsePlugin::getGain (int n) { return 0.0f; /*equalizer.getParameter (0) / 127.0f;*/ }
void XImpulsePlugin::setGain (int n, float value) { /*equalizer.setParameter (0, (int) (value * 127.0f));*/ }

//==============================================================================
void XImpulsePlugin::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    int numSamples = samplesPerBlock + 1;

    inputBuffers.setSize (2, numSamples, false, true);

    ir->resume();
}

void XImpulsePlugin::releaseResources()
{
    ir->suspend();
}

void XImpulsePlugin::processBlock (AudioSampleBuffer& buffer,
                                   MidiBuffer& midiMessages)
{
    // process incoming midi
    midiAutomatorManager.handleMidiMessageBuffer (midiMessages);

    // overall samples to process    
    int blockSamples = buffer.getNumSamples();

    // get buffers
    float* inL = buffer.getSampleData (0);
    float* inR = buffer.getSampleData (1);
    float* bufferL = inputBuffers.getSampleData (0);
    float* bufferR = inputBuffers.getSampleData (1);

    // process impulse
    ir->processreplace (inL, inR, bufferL, bufferR, blockSamples, FV3_IR2_SKIP_FILTER);

    // copy processed back
    buffer.copyFrom (0, 0, inputBuffers, 0, 0, blockSamples);
    buffer.copyFrom (1, 0, inputBuffers, 1, 0, blockSamples);
}

//==============================================================================
void XImpulsePlugin::loadImpulseResponse (const File& fileToLoad)
{
    suspendProcessing (true);

    if (fileToLoad.existsAsFile ())
    {
        AudioFormatReader* reader = formatManager.createReaderFor (fileToLoad);

        if (reader != 0 && reader->lengthInSamples > 0)
        {
            AudioSampleBuffer impulse (reader->numChannels, reader->lengthInSamples);

            impulse.readFromAudioReader (reader, 0, reader->lengthInSamples, 0, true, true);

            ir->unloadImpulse();
            ir->loadImpulse (impulse.getSampleData (0),
                             impulse.getSampleData (1),
                             impulse.getNumSamples ());

            deleteAndZero (reader);
        }
        
        currentImpuseFile = fileToLoad;
    }

    suspendProcessing (false);
}

//==============================================================================
void XImpulsePlugin::getStateInformation (MemoryBlock& destData)
{
#ifndef JUCE_DEBUG
    try
    {
#endif

        MemoryBlock tempBlock;
        XmlElement xml ("main");

        // equalizer.addToXML (&xml);

        String xmlString = xml.createDocument (String::empty);
        tempBlock.append ((const char*) xmlString, xmlString.length ());

        xmlString = tempBlock.toBase64Encoding ();
        destData.append ((const char*) xmlString, xmlString.length());

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

void XImpulsePlugin::setStateInformation (const void* data, int sizeInBytes)
{
    suspendProcessing (true);

#ifndef JUCE_DEBUG
    try
    {
#endif
        if (data && sizeInBytes > 0)
        {
            MemoryBlock mb;
            mb.fromBase64Encoding (String ((char*) data));

            XmlDocument xmlDoc (mb.toString ());
            XmlElement* xml = xmlDoc.getDocumentElement();

            if (xml == 0 || ! xml->hasTagName (T("main")))
            {
                String errString = xmlDoc.getLastParseError();
                printf ("Error restoring preset: %s \n", (const char*) errString);
            }
            else
            {
                // equalizer.updateFromXML (xml);
                delete xml;
            }

            sendChangeMessage (this);
        }
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
XImpulseComponent* XImpulsePlugin::getEditor()
{
    return (XImpulseComponent*) getActiveEditor();
}

AudioProcessorEditor* XImpulsePlugin::createEditor()
{
    return new XImpulseComponent (this);
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter (const String& createArgs)
{
    return new XImpulsePlugin();
}

