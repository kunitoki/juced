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

#include "DssiPlugin.h"

#if JOST_USE_DSSI

//==============================================================================
DssiPluginMidiManager::DssiPluginMidiManager ()
  : maxEventSize (16 * 1024),
    currentMidiCount (0)
{
    snd_midi_event_new (maxEventSize, &midiParser);
}

DssiPluginMidiManager::~DssiPluginMidiManager ()
{
    snd_midi_event_free (midiParser);
}

void DssiPluginMidiManager::convertMidiMessages (MidiBuffer& midiMessages,
                                                 const int blockSamples)
{
    const uint8* data;
    int numBytesOfMidiData,
        samplePosition;
    MidiBuffer::Iterator it (midiMessages);

    currentMidiCount = 0;

    while (it.getNextEvent (data,
                            numBytesOfMidiData,
                            samplePosition))
    {
        if (numBytesOfMidiData > maxEventSize)
        {
            maxEventSize = numBytesOfMidiData;
            snd_midi_event_free (midiParser);
            snd_midi_event_new (maxEventSize, &midiParser);
        }

        snd_seq_event_t* event = & midiEventsBuffer [currentMidiCount];
        snd_seq_ev_clear (event);

        snd_midi_event_encode (midiParser,
                               data,
                               numBytesOfMidiData,
                               event);

        if (++currentMidiCount >= 2048)
            break;
    }

    snd_midi_event_reset_encode (midiParser);
}

//==============================================================================
DssiPlugin::DssiPlugin ()
  : ptrLibrary (0),
    ptrPlug (0),
    ladspa (0),
    plugin (0),
    params (0),
    normalized (0),
    currentPreset (0),
    numPrograms (0),
    samplingRate (44100.0f),
    emptyBuffer (1,32)
{
}

DssiPlugin::~DssiPlugin ()
{
    osc.stopListening ();

    if (ptrPlug && ladspa && ladspa->cleanup)
        ladspa->cleanup (plugin);
    ptrPlug = 0;

    removeAllParameters (true);

    if (ptrLibrary)
        PlatformUtilities::freeDynamicLibrary (ptrLibrary);
    ptrLibrary = 0;

    if (params) delete[] params;
    if (normalized) delete[] normalized;
}

//==============================================================================
bool DssiPlugin::loadPluginFromFile (const File& filePath)
{
    ptrLibrary = PlatformUtilities::loadDynamicLibrary (filePath.getFullPathName());

    if (ptrLibrary != 0)
    {
        DSSI_Descriptor_Function pfDescriptorFunction
                = (DSSI_Descriptor_Function)
                        PlatformUtilities::getProcedureEntryPoint (ptrLibrary, T("dssi_descriptor"));

        if (pfDescriptorFunction != 0)
        {
            for (uint32 iPluginIndex = 0;; iPluginIndex++)
            {
                ptrPlug = pfDescriptorFunction (iPluginIndex);
                if (ptrPlug != NULL)
                    break;
            }

            if (ptrPlug == 0)
            {
                printf ("Cannot find any valid descriptor in shared library \n");
                return false;
            }
        }
        else
        {
            // plugin raised an exception
            printf ("Cannot find any valid plugin in shared library \n");
            return false;
        }
    }
    else
    {
        printf ("You are trying to load a shared library ? \n");
        return false;
    }

    jassert (ptrPlug);

    pluginFile = filePath;
    ladspa = ptrPlug->LADSPA_Plugin;
    // version = ptrPlug->DSSI_API_Version;

    plugin = ladspa->instantiate (ladspa, (unsigned int) samplingRate);

/*
    if (ptrPlug->configure)
        ptrPlug->configure (DSSI_PROJECT_DIRECTORY_KEY, (const char*) filePath.getParentDirectory()
                                                                              .getFullPathName ());
*/

    // count ports
    ins.clear ();
    outs.clear ();
    pars.clear ();
    
    for (uint i = 0; i < ladspa->PortCount; i++)
    {
        LADSPA_PortDescriptor pod = ladspa->PortDescriptors[i];
    
        if (pod & LADSPA_PORT_AUDIO)
        {
            if (pod & LADSPA_PORT_INPUT)         ins.add (i);
            else if (pod & LADSPA_PORT_OUTPUT)   outs.add (i);
        }
        else if (pod & LADSPA_PORT_CONTROL)
        {
            pars.add (i);
        }
    }
    
    // create ports
    int numParams = pars.size ();
    params = new float [numParams];
    normalized = new float [numParams];
    memset (params, 0, numParams * sizeof (float));
    memset (normalized, 0, numParams * sizeof (float));

    // connect ports
    if (ladspa->connect_port)
    {
        for (int i = 0; i < pars.size (); i++)
            ladspa->connect_port (plugin, pars [i], &normalized[i]);
        for (int i = 0; i < ins.size (); i++)
            ladspa->connect_port (plugin, ins [i], emptyBuffer.getSampleData (0));
        for (int i = 0; i < outs.size (); i++)
            ladspa->connect_port (plugin, outs [i], emptyBuffer.getSampleData (0));
    }

    // count programs
    if (ptrPlug->get_program)
        for (numPrograms = 0; ptrPlug->get_program (plugin, numPrograms); ++numPrograms);

    // set default to 0
//    setCurrentProgram (0);
    setDefaultProgram ();

    // start osc listener to itself
    osc.setPort (18910);
    osc.setRootAddress ("dssi");
    osc.addListener (this);
    osc.startListening ();

    DBG ("DssiPlugin::loadPluginFromFile");

    // create params
    setNumParameters (numParams);

    for (int i = 0; i < numParams; i++)
    {
        AudioParameter* parameter = new AudioParameter ();
        
        parameter->part (i);
        parameter->name (ladspa->PortNames [pars [i]]);
        parameter->get (MakeDelegate (this, &DssiPlugin::getParameterReal));
        parameter->set (MakeDelegate (this, &DssiPlugin::setParameterReal));
        parameter->text (MakeDelegate (this, &DssiPlugin::getParameterTextReal));
        
        registerParameter (i, parameter);
    }

    return true;
}

//==============================================================================
const String DssiPlugin::getName () const
{
    return (ladspa && ladspa->Label) ? String (ladspa->Label)
                                     : pluginFile.getFileNameWithoutExtension ();
}

int DssiPlugin::getID () const
{
    return ladspa ? ladspa->UniqueID : 0;
}


int DssiPlugin::getNumInputs () const
{
    return ins.size ();
}

int DssiPlugin::getNumOutputs () const
{
    return outs.size ();
}

int DssiPlugin::getNumMidiInputs () const
{
    return 1;
}

int DssiPlugin::getNumMidiOutputs () const
{
    return 0;
}

void* DssiPlugin::getLowLevelHandle ()
{
    return (void*) ptrPlug;
}

bool DssiPlugin::acceptsMidi () const
{
    return true;
#if 0
    return ptrPlug && (ptrPlug->run_synth
                      || ptrPlug->run_synth_adding);
#endif
}

//==============================================================================
void DssiPlugin::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    DBG ("DssiPlugin::prepareToPlay");

    samplingRate = sampleRate;

    keyboardState.reset();

    if (ladspa && ladspa->activate)
        ladspa->activate (plugin);
}

void DssiPlugin::releaseResources()
{
    DBG ("DssiPlugin::releaseResources");

    if (ladspa && ladspa->deactivate)
        ladspa->deactivate (plugin);
}

//==============================================================================
void DssiPlugin::processBlock (AudioSampleBuffer& buffer,
                               MidiBuffer& midiMessages)
{
    const int blockSize = buffer.getNumSamples ();

    MidiBuffer* midiBuffer = midiBuffers.getUnchecked (0);

    // add events from keyboards
    keyboardState.processNextMidiBuffer (*midiBuffer,
                                         0, blockSize,
                                         true);

    // process midi automation
    midiAutomatorManager.handleMidiMessageBuffer (*midiBuffer);

    if (ptrPlug && ladspa)
    {
        // convert midi messages internally
        midiManager.convertMidiMessages (*midiBuffer, blockSize);

        // connect ports
        for (int i = 0; i < ins.size (); i++)
            ladspa->connect_port (plugin, ins [i], inputBuffer->getSampleData (i));
        for (int i = 0; i < outs.size (); i++)
            ladspa->connect_port (plugin, outs [i], outputBuffer->getSampleData (i));

#if 0
        if (ptrPlug->run_multiple_synths)
        {
            ptrPlug->run_multiple_synths (1,
                                          &plugin,
                                          blockSize,
                                          & (midiManager.getMidiEvents ()[0]),
                                          midiManager.getMidiEventsCount ());
            return;
        }
        else if (ptrPlug->run_multiple_synths_adding)
        {
            outputBuffer->clear ();
            ptrPlug->run_multiple_synths_adding (1,
                                                 &plugin,
                                                 blockSize,
                                                 & (midiManager.getMidiEvents ()[0]) ,
                                                 midiManager.getMidiEventsCount ());
            return;
        }
#endif
        if (ptrPlug->run_synth)
        {
            ptrPlug->run_synth (plugin,
                                blockSize,
                                midiManager.getMidiEvents (),
                                midiManager.getMidiEventsCount ());
            return;
        }
        else if (ptrPlug->run_synth_adding)
        {
            outputBuffer->clear ();
            ptrPlug->run_synth_adding (plugin,
                                       blockSize,
                                       midiManager.getMidiEvents (),
                                       midiManager.getMidiEventsCount ());
            return;
        }

        // run ladspa if present as 
        if (ladspa->run)
        {
            ladspa->run (plugin, blockSize);
        }
        else if (ladspa->run_adding)
        {
            outputBuffer->clear ();
            ladspa->run_adding (plugin, blockSize);
        }
        else
        {
            outputBuffer->clear ();
        }
    }
}

//==============================================================================
void DssiPlugin::setParameterReal (int index, float value)
{
    jassert (index >= 0 && index < pars.size ());

    const LADSPA_PortRangeHint* hint = & ladspa->PortRangeHints [pars [index]];

    float lower = hint->LowerBound *
                  (LADSPA_IS_HINT_SAMPLE_RATE (hint->HintDescriptor) ? samplingRate : 1.0f);
    float upper = hint->UpperBound *
                  (LADSPA_IS_HINT_SAMPLE_RATE (hint->HintDescriptor) ? samplingRate : 1.0f);

    // @TODO - Handle better lower/upper bound. this is ok for most cases
    //         but in some others it don't

    if (LADSPA_IS_HINT_TOGGLED (hint->HintDescriptor))
    {
        if (value < 0.5f)   normalized [index] = 0.0f;
        else                normalized [index] = 1.0f;
    }
    else if (LADSPA_IS_HINT_BOUNDED_BELOW (hint->HintDescriptor)
             && LADSPA_IS_HINT_BOUNDED_ABOVE (hint->HintDescriptor))
    {
        if (LADSPA_IS_HINT_LOGARITHMIC(hint->HintDescriptor) && (lower >= 1.0f && upper >= 1.0f))
            normalized [index] = expf(logf(lower) * value + logf(upper) * (1.0f - value));
        else
            normalized [index] = lower + (upper - lower) * value;
    }
    else if (LADSPA_IS_HINT_BOUNDED_BELOW (hint->HintDescriptor))
    {
        normalized [index] = value;
    }
    else if (LADSPA_IS_HINT_BOUNDED_ABOVE (hint->HintDescriptor))
    {
        normalized [index] = value * upper;
    }

    if (LADSPA_IS_HINT_INTEGER (hint->HintDescriptor))
        normalized [index] = (float) ((int) normalized [index]);

    params [index] = value;
}

float DssiPlugin::getParameterReal (int index)
{
    return params [index];
}

const String DssiPlugin::getParameterTextReal (int index, float value)
{
    if (ladspa)
    {
        const LADSPA_PortRangeHint* hint = & ladspa->PortRangeHints [pars [index]];

        if (LADSPA_IS_HINT_INTEGER (hint->HintDescriptor))
            return String ((int) normalized [index]);
        else
            return String (normalized [index], 4);
    }
    else
    {
        return T("");
    }
}

//==============================================================================
int DssiPlugin::getNumPrograms ()
{
    return numPrograms;
}

void DssiPlugin::setCurrentProgram (int programNumber)
{
    if (ptrPlug && ptrPlug->select_program)
    {
        DBG ("DssiPlugin::setCurrentPreset");
    
        const DSSI_Program_Descriptor* preset = ptrPlug->get_program (plugin, programNumber);

        if (preset)
        {
            ptrPlug->select_program (plugin, preset->Bank, preset->Program);

            currentPreset = programNumber;
        }
    }
}

int DssiPlugin::getCurrentProgram ()
{
    return currentPreset;
}

const String DssiPlugin::getProgramName (const int programNumber)
{
    if (ptrPlug && ptrPlug->get_program)
    {
        const DSSI_Program_Descriptor* preset = ptrPlug->get_program (plugin, programNumber);

        if (preset)
            return String (preset->Name);
    }

    return T("Default preset");
}

const String DssiPlugin::getCurrentProgramName ()
{
    return getProgramName (currentPreset);
}


//==============================================================================
void DssiPlugin::setDefaultProgram ()
{
    if (ladspa == 0)
        return;

    // TODO - keep in a function instead !
    for (int i = 0; i < pars.size (); i++)
    {
        const LADSPA_PortRangeHint* hint = & ladspa->PortRangeHints [pars [i]];

        float lower = hint->LowerBound *
                      (LADSPA_IS_HINT_SAMPLE_RATE (hint->HintDescriptor) ? samplingRate : 1.0f);
        float upper = hint->UpperBound *
                      (LADSPA_IS_HINT_SAMPLE_RATE (hint->HintDescriptor) ? samplingRate : 1.0f);

        if (LADSPA_IS_HINT_HAS_DEFAULT (hint->HintDescriptor))
        {
            if (LADSPA_IS_HINT_DEFAULT_0 (hint->HintDescriptor))
            {
                normalized [i] = 0.0f;
                params [i] = 0.0f;
            }
            if (LADSPA_IS_HINT_DEFAULT_1 (hint->HintDescriptor))
            {
                normalized [i] = 1.0f;
                params [i] = 1.0f;
            }
            if (LADSPA_IS_HINT_DEFAULT_100 (hint->HintDescriptor))
            {
                normalized [i] = 100.0f;
                params [i] = 0.5f;
            }
            if (LADSPA_IS_HINT_DEFAULT_440 (hint->HintDescriptor))
            {
                normalized [i] = 440.0f;
                params [i] = 0.5f;
            }

            if (LADSPA_IS_HINT_BOUNDED_BELOW(hint->HintDescriptor)
                && LADSPA_IS_HINT_DEFAULT_MINIMUM (hint->HintDescriptor))
            {
                normalized [i] = lower;
                params [i] = 0.0f;
            }

            if (LADSPA_IS_HINT_BOUNDED_BELOW(hint->HintDescriptor)
                && LADSPA_IS_HINT_DEFAULT_MINIMUM (hint->HintDescriptor))
            {
                normalized [i] = lower;
                params [i] = 0.0f;
            }

            if (LADSPA_IS_HINT_BOUNDED_ABOVE(hint->HintDescriptor)
                && LADSPA_IS_HINT_DEFAULT_MAXIMUM (hint->HintDescriptor))
            {
                normalized [i] = upper;
                params [i] = 1.0f;
            }

            if (LADSPA_IS_HINT_BOUNDED_BELOW(hint->HintDescriptor))
            {
                if (LADSPA_IS_HINT_LOGARITHMIC(hint->HintDescriptor)
                    && lower > 0.0f && upper > 0.0f)
                {
                    if (LADSPA_IS_HINT_DEFAULT_LOW(hint->HintDescriptor)) {
                        normalized [i] = expf(logf(lower) * 0.75f + logf(upper) * 0.25f);
                        params [i] = 0.25f;
                    } else if (LADSPA_IS_HINT_DEFAULT_MIDDLE(hint->HintDescriptor)) {
                        normalized [i] = expf(logf(lower) * 0.5f + logf(upper) * 0.5f);
                        params [i] = 0.5f;
                    } else if (LADSPA_IS_HINT_DEFAULT_HIGH(hint->HintDescriptor)) {
                        normalized [i] = expf(logf(lower) * 0.25f + logf(upper) * 0.75f);
                        params [i] = 0.75f;
                    }
                }
                else
                {
                    if (LADSPA_IS_HINT_DEFAULT_LOW(hint->HintDescriptor)) {
                        normalized [i] = lower * 0.75f + upper * 0.25f;
                        params [i] = 0.25f;
                    } else if (LADSPA_IS_HINT_DEFAULT_MIDDLE(hint->HintDescriptor)) {
                        normalized [i] = lower * 0.5f + upper * 0.5f;
                        params [i] = 0.5f;
                    } else if (LADSPA_IS_HINT_DEFAULT_HIGH(hint->HintDescriptor)) {
                        normalized [i] = lower * 0.25f + upper * 0.75f;
                        params [i] = 0.75f;
                    }
                }
            }
        }
        else
        {
            normalized [i] = 0.0f;
            params [i] = 0.0f;
        }
    }
}

//==============================================================================
bool DssiPlugin::hasEditor () const
{
    return false;
}

bool DssiPlugin::wantsEditor () const
{
    return true;
}

#if 0

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <dlfcn.h>
#include <unistd.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <signal.h>
#include <dirent.h>
#include <time.h>
#include <libgen.h>

static void startGUI(const char *directory, const char *dllName, const char *label,
	                 const char *oscUrl, const char *instanceTag)
{
    DBG (oscUrl);

    struct dirent *entry;
    char *dllBase = strdup(dllName);
    char *subpath;
    DIR *subdir;
    char *filename;
    struct stat buf;
    int fuzzy;

    if (strlen(dllBase) > 3 &&
        !strcasecmp(dllBase + strlen(dllBase) - 3, ".so"))
    {
        dllBase[strlen(dllBase) - 3] = '\0';
    }

    if (*dllBase == '/') {
        subpath = dllBase;
        dllBase = strdup(strrchr(subpath, '/') + 1);
    } else {
    	subpath = (char *)malloc(strlen(directory) + strlen(dllBase) + 2);
	    sprintf(subpath, "%s/%s", directory, dllBase);
    }

    for (fuzzy = 0; fuzzy <= 1; ++fuzzy) {

	if (!(subdir = opendir(subpath))) {
		fprintf(stderr, "%s: can't open plugin GUI directory \"%s\"\n", label, subpath);
	    free(subpath);
	    free(dllBase);
	    return;
	}

	while ((entry = readdir(subdir))) {
	    
	    if (entry->d_name[0] == '.') continue;
	    if (!strchr(entry->d_name, '_')) continue;

	    if (fuzzy) {
		    fprintf(stderr, "checking %s against %s\n", entry->d_name, dllBase);
            if (strlen(entry->d_name) <= strlen(dllBase) ||
                strncmp(entry->d_name, dllBase, strlen(dllBase)) ||
                entry->d_name[strlen(dllBase)] != '_')
                continue;
	    } else {
		    fprintf(stderr, "checking %s against %s\n", entry->d_name, label);
            if (strlen(entry->d_name) <= strlen(label) ||
                strncmp(entry->d_name, label, strlen(label)) ||
                entry->d_name[strlen(label)] != '_')
                continue;
	    }
	    
	    filename = (char *)malloc(strlen(subpath) + strlen(entry->d_name) + 2);
	    sprintf(filename, "%s/%s", subpath, entry->d_name);
	    
	    if (stat(filename, &buf)) {
		    perror("stat failed");
		    free(filename);
		    continue;
	    }
	    
	    if ((S_ISREG(buf.st_mode) || S_ISLNK(buf.st_mode)) &&
    		(buf.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)))
 		{
		    fprintf(stderr, "%s: trying to execute GUI at \"%s\"\n", label, filename);
		
		    if (fork() == 0) {
		        execlp(filename, filename, oscUrl, dllName, label, instanceTag, NULL);
		        perror("exec failed");
		        exit(1);
		    }
		
		    free(filename);
		    free(subpath);
		    free(dllBase);
		    return;
	    }
	    
	    free(filename);
	}
    }

	fprintf(stderr, "no GUI found for plugin \"%s\" in \"%s/\"\n", label, subpath);
    free(subpath);
    free(dllBase);
}

void DssiPlugin::getEditorSize (int& width, int& height)
{
    width = 600;
    height = 400;
}

void DssiPlugin::openEditor (void* handle, void* display)
{
    startGUI (pluginFile.getParentDirectory().getFullPathName(),
              pluginFile.getFullPathName(),
              getName (),
              "osc.udp://localhost:" + String(osc.getPort ()) + "/dssi/" + getName () + "/chan00",
              "chan00");
}

void DssiPlugin::idleEditor ()
{
}

void DssiPlugin::closeEditor ()
{
}

#endif

bool DssiPlugin::handleOSCMessage (OpenSoundController* controller,
                                   OpenSoundMessage *message)
{
    String msgString = message->getAddress();

    DBG ("handleOSCMessage >> " + msgString);

/*
    if (controller->isCorrectAddress (msgString))
    {
        String msgPlugin = controller->getPathIndexed (msgString, 1);
        String msgInstance = controller->getPathIndexed (msgString, 2);
        String msgWhat = controller->getPathIndexed (msgString, 3);

        DBG (msgPlugin
             + "/" + msgInstance
             + "/" + msgWhat);

        if (msgWhat == T("update")) {

//            OpenSoundMessage message;
//            message.setAddress ("/show");

//            sock.setAddress ("localhost");
//        	sock.setPort (osc.getPort ());

//        	sock.sendData (message.getData(), message.getSize());
        	
//        	DBG (" << ziuken !");
        
        } else if (msgWhat == T("control")) {
        } else if (msgWhat == T("configure")) {
        } else if (msgWhat == T("midi")) {
        } else if (msgWhat == T("program")) {
        } else if (msgWhat == T("exiting")) {
        }

        return true;
    }
*/

    return false;
}

#endif
