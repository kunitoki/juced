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

#include "SoundCrabPlugin.h"
#include "SoundCrabEditor.h"


//==============================================================================
int SoundCrabPlugin::instances = 0;

//==============================================================================
SoundCrabPlugin::SoundCrabPlugin()
  : settings (0),
    synth (0),
    sequencer (0),
    currentSynthChannel (0),
    newSoundFont (File::nonexistent),
    newSoundFontPreset (-1),
    currentSound (0),
    currentBank (0),
    currentPreset (0)
{
    // prepare the parameters
    parameters = new SoundCrabParameters (this);

    // set log function
    fluid_set_log_function (FLUID_PANIC, &SoundCrabPlugin::errorFunction, (void*) this);
    fluid_set_log_function (FLUID_ERR, &SoundCrabPlugin::errorFunction, (void*) this);

#if JUCE_DEBUG
    fluid_set_log_function (FLUID_WARN, &SoundCrabPlugin::logFunction, (void*) this);
    fluid_set_log_function (FLUID_INFO, &SoundCrabPlugin::logFunction, (void*) this);
    fluid_set_log_function (FLUID_DBG, &SoundCrabPlugin::logFunction, (void*) this);
#else
    fluid_set_log_function (FLUID_WARN, NULL, NULL);
    fluid_set_log_function (FLUID_INFO, NULL, NULL);
    fluid_set_log_function (FLUID_DBG, NULL, NULL);
#endif
}

SoundCrabPlugin::~SoundCrabPlugin()
{
    // force a release of the resources
    releaseResources();

    // free parameters
    deleteAndZero (parameters);

    // delete config
    if (--SoundCrabPlugin::instances == 0)
        Config::deleteInstance ();
}

//==============================================================================
void SoundCrabPlugin::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // setup settings
    releaseResources();

    DBG ("SoundCrabPlugin::prepareToPlay");
    
    settings = new_fluid_settings();
    if (settings)
    {
#ifdef JUCE_DEBUG
        fluid_settings_setstr (settings, "synth.verbose", "yes");
#else
        fluid_settings_setstr (settings, "synth.verbose", "no");
#endif
        fluid_settings_setstr (settings, "synth.dump", "no");
        fluid_settings_setint (settings, "synth.midi-channels", 1);
        fluid_settings_setint (settings, "synth.audio-channels", 1);
        fluid_settings_setint (settings, "synth.effects-channels", 0);
        fluid_settings_setstr (settings, "synth.reverb.active", "no");
        fluid_settings_setstr (settings, "synth.chorus.active", "no");
        fluid_settings_setnum (settings, "synth.gain", 1.0f);
        fluid_settings_setint (settings, "synth.polyphony", 128);
        fluid_settings_setnum (settings, "synth.sample-rate", (float) sampleRate);
        // fluid_settings_setint (settings, "audio.periods", samplesPerBlock / FLUID_BUFSIZE);
        // fluid_settings_setint (settings, "audio.period-size", samplesPerBlock);
        // fluid_settings_setstr (settings, "audio.sample-format", "float");

        // setup synthesizer
        synth = new_fluid_synth (settings);
        if (synth)
        {
            synth->effects_channels = 0;

            // setup interpolation
            // FLUID_INTERP_NONE
            // FLUID_INTERP_LINEAR
            // FLUID_INTERP_DEFAULT
            // FLUID_INTERP_4THORDER
            // FLUID_INTERP_7THORDER
            // FLUID_INTERP_HIGHEST
#ifdef JUCE_DEBUG
            fluid_synth_set_interp_method (synth, currentSynthChannel, FLUID_INTERP_LINEAR);
#else
            fluid_synth_set_interp_method (synth, currentSynthChannel, FLUID_INTERP_HIGHEST);
#endif

            // try to load stuff if we got it (BUGGY HOSTS !)
            if (newSoundFont != File::nonexistent)
            {
                // we are initializing a previously loaded soundfont
                loadSoundFont (newSoundFont);
                setCurrentAbsolutePreset (newSoundFontPreset);
                    
                newSoundFontPreset = -1;
                newSoundFont = File::nonexistent;
            }
            else
            {
                // we are initializing without any soundfont
                currentSound = 0;
            }
        }
    }
}

void SoundCrabPlugin::releaseResources()
{
    DBG ("SoundCrabPlugin::releaseResources");

    // free memory and stuff
    if (synth)
    {
        fluid_synth_stop (synth, currentSynthChannel);

        // unload the only one soundfont
        if (fluid_synth_sfcount (synth) > 0)
        {
            newSoundFont = currentSoundFile;
            newSoundFontPreset = currentPreset;

            fluid_synth_sfunload (synth, currentSound, 1);
        }
        
        delete_fluid_synth (synth);
        synth = 0;

        currentSound = 0;
    }

    if (settings)
    {
        delete_fluid_settings (settings);
        settings = 0;
    }
}

void SoundCrabPlugin::processBlock (AudioSampleBuffer& buffer,
                                    MidiBuffer& midiMessages)
{
    // start processing    
    buffer.clear ();

    // render audio
    if (synth && fluid_synth_sfcount (synth) > 0)
    {
        // process incoming midi
        midiAutomatorManager.handleMidiMessageBuffer (midiMessages);

        // process midi messages
        const unsigned char* midiData;
        int numBytesOfMidiData, samplePosition;
        MidiBuffer::Iterator ev (midiMessages);

        while (ev.getNextEvent (midiData, numBytesOfMidiData, samplePosition))
        {
            int status = midiData[0] / 16;
            // int chan = midiData[0] & 0x0f;
            int chan = currentSynthChannel; // translate all channels through currentSynthChannel
            int cntl;

            switch (status)
            {
            case 0x9: // note on
                fluid_synth_noteon (synth, chan, midiData[1] & 0x7f, midiData[2] & 0x7f);
                break;
            case 0x8: // note off
                fluid_synth_noteoff (synth, chan, midiData[1] & 0x7f);
                break;
            case 0xB: // cc
                cntl = midiData[1] & 0x7f;
                fluid_synth_cc (synth, chan, cntl, midiData[2] & 0x7f);
                break;
            case 0xE: // pitch bend
                fluid_synth_pitch_bend (synth, chan, midiData[1] + midiData[2] * (long int) 128 - 8192);
                break;
            case 0xF: // system reset
                fluid_synth_system_reset (synth);
                break;
            }
        }

        fluid_synth_write_float (synth, buffer.getNumSamples(),
                                 buffer.getSampleData (0), 0, 1,
                                 buffer.getSampleData (1), 0, 1);
    }
}

//==============================================================================
bool SoundCrabPlugin::loadSoundFont (const File& fileToLoad)
{
    DBG ("SoundCrabPlugin::loadSoundFont");

    bool loadedOK = false;

    if (synth /*&& fluid_is_soundfont (fileToLoad.getFullPathName().toUTF8()))*/)
    {
        fluid_synth_stop (synth, currentSynthChannel);
    
        // unload previous soundfont
        if (currentSound > 0)
            fluid_synth_sfunload (synth, currentSound, /*true*/ 1);

        // try to load the new one !
        if ((currentSound = fluid_synth_sfload (synth, fileToLoad.getFullPathName().toUTF8(), 1)) == -1)
        {
            // something has gone bad
            printf ("Unable to load %s \n", (const char*) fileToLoad.getFullPathName());

            currentSound = 0;
            loadedOK = false;
        }
        else
        {
            // we were able to load it !
            printf ("%s loaded correctly \n", (const char*) fileToLoad.getFullPathName());

            // save it as fast recall
            Config::getInstance ()->addRecentSoundfont (fileToLoad);

            currentSoundFile = fileToLoad;
            loadedOK = true;
        }
    }
    else
    {
        newSoundFont = fileToLoad;
    }

    return loadedOK;
}

void SoundCrabPlugin::setCurrentAbsolutePreset (const int index)
{
    DBG ("SoundCrabPlugin::setCurrentAbsolutePreset " + String (index));

    if (synth)
    {
        int presetIndex = 1;
        int bankOffset = 0; // fluid_synth_get_bank_offset (synth, currentSound);

        fluid_synth_stop (synth, currentSynthChannel);

        for (int b = bankOffset; b < FLUID_NUM_PROGRAMS; b++)
        {
            for (int p = 0; p < FLUID_NUM_PROGRAMS; p++)
            {
                fluid_preset_t* preset = fluid_synth_get_preset (synth, currentSound, b, p);
                if (preset != NULL && presetIndex++ == index)
                {
                    if (fluid_synth_program_select (synth, currentSynthChannel, currentSound, b, p) == -1)
                        printf ("Failed to set preset %d of bank %d \n", p, b);
                    else
                        printf ("Set preset %d of bank %d \n", p, b);

                    currentBank = b;
                    currentPreset = index; // TODO - should be p
                    break;
                }
            }
        }
    }
    else
    {
        newSoundFontPreset = index;
    }
}

void SoundCrabPlugin::fillComboboxWithPresets (ComboBox* combo)
{
    DBG ("SoundCrabPlugin::fillComboboxWithPresets");

    if (synth)
    {
        int presetIndex = 1;
        int bankOffset = 0; // fluid_synth_get_bank_offset (synth, currentSound);

        for (int b = bankOffset; b < FLUID_NUM_PROGRAMS; b++)
        {
            for (int p = 0; p < FLUID_NUM_PROGRAMS; p++)
            {
                fluid_preset_t* preset = fluid_synth_get_preset (synth, currentSound, b, p);
                if (preset != NULL)
                    combo->addItem (String (preset->get_name (preset)),
                                    presetIndex++);
            }
        }
    }
}

double SoundCrabPlugin::getAverageCpuLoad ()
{
    return synth ? fluid_synth_get_cpu_load (synth) : 0.0;
}

void SoundCrabPlugin::errorFunction (int level, char* message, void* data)
{
//    SoundCrabPlugin* plugin = (SoundCrabPlugin*) data;
    
    AlertWindow::showMessageBox (AlertWindow::WarningIcon,
                                 T("Soundcrab generic error"),
                                 message);
}

void SoundCrabPlugin::logFunction (int level, char* message, void* data)
{
//    SoundCrabPlugin* plugin = (SoundCrabPlugin*) data;
    
    printf ("%s\n", message);
}

//==============================================================================
void SoundCrabPlugin::getStateInformation (MemoryBlock& destData)
{
    DBG ("SoundCrabPlugin::getStateInformation");

    try
    {
        MemoryBlock tempBlock;
        XmlElement xml (T("main"));
        xml.setAttribute (T("version"), JucePlugin_VersionCode);

        { // save soundfont file full path
        XmlElement* e = new XmlElement (T("file"));
        e->setAttribute (T("fullpath"), currentSoundFile.getFullPathName());
        xml.addChildElement (e);
        }

        { // save which bank and preset we have selected
        XmlElement* e = new XmlElement (T("sound"));
        e->setAttribute (T("bank"), currentBank);
        e->setAttribute (T("preset"), currentPreset);
        xml.addChildElement (e);
        }

        { // save parameters
        XmlElement* e = new XmlElement (T("parameters"));
        writeParametersToXmlElement (e);
        xml.addChildElement (e);
        }

        String xmlString = xml.createDocument (String::empty);

//        DBG ((const char*) xmlString);

        destData.append ((const char*) xmlString, xmlString.length());
    }
    catch (...)
    {
        AlertWindow::showMessageBox (AlertWindow::WarningIcon,
                                     T("Error !"),
                                     T("Something bad occurred while saving presets data !"));
    }
}

void SoundCrabPlugin::setStateInformation (const void* data, int sizeInBytes)
{
    DBG ("SoundCrabPlugin::setStateInformation");

    suspendProcessing (true);

    try
    {
        if (data && sizeInBytes > 0)
        {
            XmlDocument xmlDoc ((char*) data);

            DBG (String ((char*) data));

            XmlElement* xml = xmlDoc.getDocumentElement();

            if (xml == 0 || ! xml->hasTagName (T("main")))
            {
                String errString = xmlDoc.getLastParseError();
                printf ("Error restoring preset: %s \n", (const char*) errString);
            }
            else
            {
                // TODO - take care of versioning
                // int version = xml->getIntAttribute (T("version"), -1);

                XmlElement* e = xml->getChildByName (T("file"));
                if (e)
                {
                    loadSoundFont (e->getStringAttribute (T("fullpath"), String::empty));

                    XmlElement* sound = xml->getChildByName (T("sound"));
                    if (sound)
                        setCurrentAbsolutePreset (sound->getIntAttribute (T("preset"), 1));

                    XmlElement* params = xml->getChildByName (T("parameters"));
                    if (params)
                        readParametersFromXmlElement (params);
                }

                delete xml;
            }

            sendChangeMessage (this);
        }
    }
    catch (...)
    {
        AlertWindow::showMessageBox (AlertWindow::WarningIcon,
                                     T("Error !"),
                                     T("Something bad occurred while restoring presets data !"));
    }

    suspendProcessing (false);
}

//==============================================================================
SoundCrabEditor* SoundCrabPlugin::getEditor()
{
    return (SoundCrabEditor*) getActiveEditor();
}

AudioProcessorEditor* SoundCrabPlugin::createEditor()
{
    return new SoundCrabEditor (this);
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter (const String& createArgs)
{
    if (SoundCrabPlugin::instances++ == 0)
    {
        // create the config
        /* Config* config = */ Config::getInstance ();
    }

    return new SoundCrabPlugin();
}
