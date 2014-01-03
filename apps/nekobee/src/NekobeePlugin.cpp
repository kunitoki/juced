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

#include "NekobeePlugin.h"
#include "NekobeeComponent.h"

//==============================================================================
int NekobeePlugin::numInstances = 0;

//==============================================================================
NekobeePlugin::NekobeePlugin()
    : output (1,1)
{
    DBG ("NekobeePlugin::NekobeePlugin");

    // defaults !
    tuning = 1.0f;
	waveform = 0;
    cutoff =	5.0f;
    resonance = 0.8f;
	envmod = 0.3f;
	decay = 0.0002f;
    accent = 0.3;
	volume = 0.75;

    // create dssi descriptor
    plugin = 0;
    dssi = dssi_descriptor (0);
    ladspa = dssi->LADSPA_Plugin;
   
    // setup parameters
    setNumParameters (NUM_PARAMETERS);

    registerParameter (PAR_TUNING, &params[PAR_TUNING].name (T("Tuning")).unit (T("%"))
                                   .set (MakeDelegate (this, &NekobeePlugin::setTuning))
                                   .get (MakeDelegate (this, &NekobeePlugin::getTuning)));

    registerParameter (PAR_WAVEFORM, &params[PAR_WAVEFORM].name (T("Wave")).unit (T("%"))
                                     .set (MakeDelegate (this, &NekobeePlugin::setWaveform))
                                     .get (MakeDelegate (this, &NekobeePlugin::getWaveform)));

    registerParameter (PAR_CUTOFF, &params[PAR_CUTOFF].name (T("Cutoff")).unit (T("%"))
                                   .set (MakeDelegate (this, &NekobeePlugin::setCutoff))
                                   .get (MakeDelegate (this, &NekobeePlugin::getCutoff)));

    registerParameter (PAR_RESONANCE, &params[PAR_RESONANCE].name (T("Res")).unit (T("%"))
                                      .set (MakeDelegate (this, &NekobeePlugin::setResonance))
                                      .get (MakeDelegate (this, &NekobeePlugin::getResonance)));

    registerParameter (PAR_ENVMOD, &params[PAR_ENVMOD].name (T("EnvMod")).unit (T("%"))
                                   .set (MakeDelegate (this, &NekobeePlugin::setEnvmod))
                                   .get (MakeDelegate (this, &NekobeePlugin::getEnvmod)));

    registerParameter (PAR_DECAY, &params[PAR_DECAY].name (T("Decay")).unit (T("%"))
                                  .set (MakeDelegate (this, &NekobeePlugin::setDecay))
                                  .get (MakeDelegate (this, &NekobeePlugin::getDecay)));

    registerParameter (PAR_ACCENT, &params[PAR_ACCENT].name (T("Accent")).unit (T("%"))
                                   .set (MakeDelegate (this, &NekobeePlugin::setAccent))
                                   .get (MakeDelegate (this, &NekobeePlugin::getAccent)));

    registerParameter (PAR_VOLUME, &params[PAR_VOLUME].name (T("Volume")).unit (T("%"))
                                   .set (MakeDelegate (this, &NekobeePlugin::setVolume))
                                   .get (MakeDelegate (this, &NekobeePlugin::getVolume)));

}

NekobeePlugin::~NekobeePlugin()
{
    DBG ("NekobeePlugin::~NekobeePlugin");

    if (--NekobeePlugin::numInstances == 0)
    {
        _fini_dssi();
    }
}

//==============================================================================
float NekobeePlugin::getTuning (int n)               { return (tuning - 0.5f) / 1.5f; }
void NekobeePlugin::setTuning (int n, float v)       { tuning = 0.5f + v * 1.5f; }
//==============================================================================
float NekobeePlugin::getWaveform (int n)             { return waveform; }
void NekobeePlugin::setWaveform (int n, float v)     { waveform = v; }
//==============================================================================
float NekobeePlugin::getCutoff (int n)               { return cutoff / 40.0f; }
void NekobeePlugin::setCutoff (int n, float v)       { cutoff = v * 40.0f; }
//==============================================================================
float NekobeePlugin::getResonance (int n)            { return resonance / 0.95f; }
void NekobeePlugin::setResonance (int n, float v)    { resonance = v * 0.95f; }
//==============================================================================
float NekobeePlugin::getEnvmod (int n)               { return envmod; }
void NekobeePlugin::setEnvmod (int n, float v)       { envmod = v; }
//==============================================================================
float NekobeePlugin::getDecay (int n)                { return (decay - 0.000009f) / (0.0007f - 0.000009f); }
void NekobeePlugin::setDecay (int n, float v)        { decay = 0.000009f + (0.0007f - 0.000009f) * v; }
//==============================================================================
float NekobeePlugin::getAccent (int n)               { return accent; }
void NekobeePlugin::setAccent (int n, float v)       { accent = v; }
//==============================================================================
float NekobeePlugin::getVolume (int n)               { return volume; }
void NekobeePlugin::setVolume (int n, float v)       { volume = v; }

//==============================================================================
void NekobeePlugin::prepareToPlay (double newSampleRate, int samplesPerBlock)
{
    // create output buffer
    output.setSize (1, samplesPerBlock * 2, false, false, false);
    output.clear ();

    if (plugin == 0)
    {
        plugin = ladspa->instantiate (ladspa, (unsigned int) newSampleRate);

        // connect ports for parameters
        ladspa->connect_port (plugin, XSYNTH_PORT_WAVEFORM, &waveform);
        ladspa->connect_port (plugin, XSYNTH_PORT_TUNING, &tuning);
        ladspa->connect_port (plugin, XSYNTH_PORT_CUTOFF, &cutoff);
        ladspa->connect_port (plugin, XSYNTH_PORT_RESONANCE, &resonance);
        ladspa->connect_port (plugin, XSYNTH_PORT_ENVMOD, &envmod);
        ladspa->connect_port (plugin, XSYNTH_PORT_DECAY, &decay);
        ladspa->connect_port (plugin, XSYNTH_PORT_ACCENT, &accent);
        ladspa->connect_port (plugin, XSYNTH_PORT_VOLUME, &volume);

        // connect port for output
        ladspa->connect_port (plugin, XSYNTH_PORT_OUTPUT, output.getSampleData(0));

        // activate plugin
        if (ladspa && ladspa->activate)
            ladspa->activate (plugin);
    }
}

void NekobeePlugin::releaseResources()
{
    if (plugin)
    {
        if (ladspa && ladspa->deactivate)
            ladspa->deactivate (plugin);

        if (ladspa && ladspa->cleanup)
            ladspa->cleanup (plugin);
        plugin = 0;
    }
}

void NekobeePlugin::processBlock (AudioSampleBuffer& buffer,
                                  MidiBuffer& midiMessages)
{
    // start processing    
    int blockSamples = buffer.getNumSamples();
    buffer.clear ();

    if (plugin)
    {
        // process incoming midi
        midiAutomatorManager.handleMidiMessageBuffer (midiMessages);

        // if any midi messages come in, use them to update the keyboard state object. This
        // object sends notification to the UI component about key up/down changes
        keyboardState.processNextMidiBuffer (midiMessages,
                                             0, blockSamples,
                                             true);

        // try to run dssi
        if (dssi->run_synth)
        {
            // convert midi messages
            midiManager.convertMidiMessages (midiMessages, blockSamples);

            dssi->run_synth (plugin,
                             blockSamples,
                             midiManager.getMidiEvents (),
                             midiManager.getMidiEventsCount ());

            // produce output buffers
            buffer.addFrom (0, 0, output, 0, 0, blockSamples, 10.0f);
            buffer.addFrom (1, 0, output, 0, 0, blockSamples, 10.0f);
        }
    }
}

//==============================================================================
void NekobeePlugin::getStateInformation (MemoryBlock& destData)
{
#ifndef JUCE_DEBUG
    try
    {
#endif

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

void NekobeePlugin::setStateInformation (const void* data, int sizeInBytes)
{
    suspendProcessing (true);

#ifndef JUCE_DEBUG
    try
    {
#endif

        if (data && sizeInBytes > 0)
        {
            XmlDocument xmlDoc ((char*) data);

            DBG (String ((char*) data));

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
NekobeeComponent* NekobeePlugin::getEditor()
{
    return (NekobeeComponent*) getActiveEditor();
}

AudioProcessorEditor* NekobeePlugin::createEditor()
{
    return new NekobeeComponent (this);
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter (const String& createArgs)
{
    if (NekobeePlugin::numInstances++ == 0)
    {
        _init_dssi();
    }

    return new NekobeePlugin();
}

