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

#include "LadspaPlugin.h"

#ifdef JOST_USE_LADSPA

//==============================================================================
LadspaPlugin::LadspaPlugin ()
  : ptrLibrary (0),
    ptrPlug (0),
    plugin (0),
    params (0),
    normalized (0),
    samplingRate (44100.0f)
{
}

LadspaPlugin::~LadspaPlugin ()
{
    if (ptrPlug && ptrPlug->cleanup)
        ptrPlug->cleanup (plugin);
    ptrPlug = 0;

    removeAllParameters (true);

    if (ptrLibrary)
        PlatformUtilities::freeDynamicLibrary (ptrLibrary);
    ptrLibrary = 0;

    if (params) delete[] params;
    if (normalized) delete[] normalized;
}

//==============================================================================
bool LadspaPlugin::loadPluginFromFile (const File& filePath)
{
    ptrLibrary = PlatformUtilities::loadDynamicLibrary (filePath.getFullPathName());

    if (ptrLibrary != 0)
    {
        LADSPA_Descriptor_Function pfDescriptorFunction
                = (LADSPA_Descriptor_Function)
                        PlatformUtilities::getProcedureEntryPoint (ptrLibrary, T("ladspa_descriptor"));

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
    plugin = ptrPlug->instantiate (ptrPlug, (unsigned int) samplingRate);

    ins.clear ();
    outs.clear ();
    pars.clear ();

    for (unsigned int i = 0; i < ptrPlug->PortCount; i++)
    {
        if (ptrPlug->PortDescriptors [i] & LADSPA_PORT_CONTROL)      pars.add (i);
        if (ptrPlug->PortDescriptors [i] & LADSPA_PORT_AUDIO)
        {
            if (ptrPlug->PortDescriptors [i] & LADSPA_PORT_INPUT)    ins.add (i);
            if (ptrPlug->PortDescriptors [i] & LADSPA_PORT_OUTPUT)   outs.add (i);
        }
    }

    int numParams = pars.size ();
    params = new float [numParams];
    normalized = new float [numParams];
    memset (params, 0, numParams * sizeof (float));
    memset (normalized, 0, numParams * sizeof (float));

    for (int i = 0; i < numParams; i++)
        ptrPlug->connect_port (plugin, pars [i], &normalized[i]);

    // create params
    setNumParameters (numParams);

    for (int i = 0; i < numParams; i++)
    {
        AudioParameter* parameter = new AudioParameter ();
        
        parameter->part (i);
        parameter->name (ptrPlug->PortNames [pars [i]]);
        parameter->get (MakeDelegate (this, &LadspaPlugin::getParameterReal));
        parameter->set (MakeDelegate (this, &LadspaPlugin::setParameterReal));
        parameter->text (MakeDelegate (this, &LadspaPlugin::getParameterTextReal));
        
        registerParameter (i, parameter);
    }

//    setCurrentProgram (0);

    return true;
}

//==============================================================================
const String LadspaPlugin::getName () const
{
    return (ptrPlug && ptrPlug->Label) ? String (ptrPlug->Label)
                                       : pluginFile.getFileNameWithoutExtension ();
}

int LadspaPlugin::getID () const
{
    return ptrPlug ? ptrPlug->UniqueID : 0;
}

void* LadspaPlugin::getLowLevelHandle ()
{
    return (void*) ptrPlug;
}

int LadspaPlugin::getNumInputs () const
{
    return ins.size ();
}

int LadspaPlugin::getNumOutputs () const
{
    return outs.size ();
}

int LadspaPlugin::getNumMidiInputs () const
{
    return 1;
}

int LadspaPlugin::getNumMidiOutputs () const
{
    return 0;
}

//==============================================================================
void LadspaPlugin::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    samplingRate = sampleRate;

    if (ptrPlug && ptrPlug->activate)
        ptrPlug->activate (plugin);
}

void LadspaPlugin::releaseResources()
{
    if (ptrPlug && ptrPlug->deactivate)
        ptrPlug->deactivate (plugin);
}

//==============================================================================
void LadspaPlugin::processBlock (AudioSampleBuffer& buffer,
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

    if (ptrPlug)
    {
        // connect ports
        for (int i = 0; i < ins.size (); i++)
            ptrPlug->connect_port (plugin, ins [i], inputBuffer->getSampleData (i));
        for (int i = 0; i < outs.size (); i++)
            ptrPlug->connect_port (plugin, outs [i], outputBuffer->getSampleData (i));

        // run ladspa
        if (ptrPlug->run)
        {
            ptrPlug->run (plugin, blockSize);
        }
        else if (ptrPlug->run_adding)
        {
            outputBuffer->clear ();
            
            ptrPlug->run_adding (plugin, blockSize);
        }
    }
}

//==============================================================================
void LadspaPlugin::setParameterReal (int index, float value)
{
    jassert (index >= 0 && index < pars.size ());

    const LADSPA_PortRangeHint* hint = & ptrPlug->PortRangeHints [pars [index]];

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
        if (LADSPA_IS_HINT_LOGARITHMIC(hint->HintDescriptor)
            && lower > 0.0f && upper > 0.0f)
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

float LadspaPlugin::getParameterReal (int index)
{
    return params [index];
}

const String LadspaPlugin::getParameterTextReal (int index, float value)
{
    if (ptrPlug)
    {
        const LADSPA_PortRangeHint* hint = & ptrPlug->PortRangeHints [pars [index]];

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
int LadspaPlugin::getNumPrograms ()
{
    return 1;
}
void LadspaPlugin::setCurrentProgram (int programNumber)
{
    if (ptrPlug == 0)
        return;

    for (int i = 0; i < pars.size (); i++)
    {
        const LADSPA_PortRangeHint* hint = & ptrPlug->PortRangeHints [pars [i]];

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

int LadspaPlugin::getCurrentProgram ()
{
    return 0;
}

const String LadspaPlugin::getProgramName (int programNumber)
{
    return T("Default preset");
}

const String LadspaPlugin::getCurrentProgramName ()
{
    return T("Default preset");
}

//==============================================================================
bool LadspaPlugin::wantsEditor () const
{
    return true;
}


#endif
