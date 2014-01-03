/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-7 by Raw Material Software ltd.

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

#include "../../../../juce_Config.h"

#if JUCE_PLUGINHOST_LADSPA && JUCE_LINUX

#include <ladspa.h>

//==============================================================================
#include "../../../core/juce_StandardHeader.h"

BEGIN_JUCE_NAMESPACE

#include "juce_LADSPAPluginFormat.h"
#include "../../../threads/juce_Process.h"
#include "../../../threads/juce_ScopedLock.h"
#include "../../../core/juce_Random.h"
#include "../../../io/files/juce_DirectoryIterator.h"
#include "../../events/juce_Timer.h"
#include "../../events/juce_AsyncUpdater.h"
#include "../../events/juce_MessageManager.h"
#include "../../gui/components/layout/juce_ComponentMovementWatcher.h"
#include "../../application/juce_Application.h"
#include "../../../juce_core/misc/juce_PlatformUtilities.h"

#if ! JUCE_WIN32
 #define _fpreset()
 #define _clearfp()
#endif

static int shellLADSPAUIDToCreate = 0;
static int insideLADSPACallback = 0;

//==============================================================================
static VoidArray activeLADSPAModules;

//==============================================================================
class LADSPAModuleHandle    : public ReferenceCountedObject
{
public:
    //==============================================================================
    File file;
    String pluginName;

    LADSPA_Descriptor_Function moduleMain;

    void* hModule;
    String fullParentDirectoryPathName;

    //==============================================================================
    static LADSPAModuleHandle* findOrCreateModule (const File& file)
    {
        for (int i = activeLADSPAModules.size(); --i >= 0;)
        {
            LADSPAModuleHandle* const module = (LADSPAModuleHandle*) activeLADSPAModules.getUnchecked(i);

            if (module->file == file)
                return module;
        }

        _fpreset(); // (doesn't do any harm)
        ++insideLADSPACallback;
        shellLADSPAUIDToCreate = 0;

        printf ("Attempting to load LADSPA: %s \n", (const char*) file.getFullPathName());

        LADSPAModuleHandle* m = new LADSPAModuleHandle (file);

        if (! m->open())
            deleteAndZero (m);

        --insideLADSPACallback;
        _fpreset(); // (doesn't do any harm)

        return m;
    }

    //==============================================================================
    LADSPAModuleHandle (const File& file_)
        : file (file_),
          moduleMain (0),
          hModule (0)
    {
        activeLADSPAModules.add (this);

        fullParentDirectoryPathName = file_.getParentDirectory().getFullPathName();
    }

    ~LADSPAModuleHandle()
    {
        activeLADSPAModules.removeValue (this);

        close();
    }
    //==============================================================================
    bool open()
    {
#if JUCE_WIN32
        static bool timePeriodSet = false;

        if (! timePeriodSet)
        {
            timePeriodSet = true;
            timeBeginPeriod (2);
        }
#endif

        pluginName = file.getFileNameWithoutExtension();

        hModule = PlatformUtilities::loadDynamicLibrary (file.getFullPathName());

        moduleMain = (LADSPA_Descriptor_Function)
            PlatformUtilities::getProcedureEntryPoint (hModule, "ladspa_descriptor");

        return moduleMain != 0;
    }

    void close()
    {
        _fpreset(); // (doesn't do any harm)

        PlatformUtilities::freeDynamicLibrary (hModule);
    }

    //==============================================================================
    juce_UseDebuggingNewOperator
};


//==============================================================================
/**
    An instance of a plugin, created by a VSTPluginFormat.

*/
class LADSPAPluginInstance     : public AudioPluginInstance
{
public:
    //==============================================================================
    ~LADSPAPluginInstance();

    //==============================================================================
    // AudioPluginInstance methods:

    void fillInPluginDescription (PluginDescription& desc) const
    {
        desc.name = name;
        desc.fileOrIdentifier = module->file.getFullPathName();
        desc.uid = getUID();
        desc.lastFileModTime = module->file.getLastModificationTime();
        desc.pluginFormatName = "LADSPA";
        desc.category = getCategory();
        desc.manufacturerName = ptrPlug ? String (ptrPlug->Maker) : String::empty;
        desc.version = getVersion();
        desc.numInputChannels = getNumInputChannels();
        desc.numOutputChannels = getNumOutputChannels();
        desc.isInstrument = false;
    }

    const String getName() const;
    int getUID() const throw();
    bool acceptsMidi() const                { return false; }
    bool producesMidi() const               { return false; }

    //==============================================================================
    // AudioProcessor methods:

    void prepareToPlay (double sampleRate, int estimatedSamplesPerBlock);
    void releaseResources();
    void processBlock (AudioSampleBuffer& buffer,
                       MidiBuffer& midiMessages);

    AudioProcessorEditor* createEditor();

    const String getInputChannelName (const int index) const;
    bool isInputChannelStereoPair (int index) const;

    const String getOutputChannelName (const int index) const;
    bool isOutputChannelStereoPair (int index) const;

    //==============================================================================
    int getNumParameters()                              { return effect != 0 ? parameters.size () : 0; }
    float getParameter (int index);
    void setParameter (int index, float newValue);
    const String getParameterName (int index);
    const String getParameterText (int index);
    bool isParameterAutomatable (int index) const;

    //==============================================================================
    int getNumPrograms()                                { return 0; }
    int getCurrentProgram()                             { return 0; }
    void setCurrentProgram (int index);
    const String getProgramName (int index);
    void changeProgramName (int index, const String& newName);

    //==============================================================================
    void getStateInformation (MemoryBlock& destData);
    void getCurrentProgramStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);
    void setCurrentProgramStateInformation (const void* data, int sizeInBytes);

    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    friend class LADSPAPluginFormat;

    const LADSPA_Descriptor* ptrPlug;
    LADSPA_Handle effect;

    String name;
    CriticalSection lock;
    bool initialised, isPowerOn;
    mutable StringArray programNames;
    AudioSampleBuffer tempBuffer;
    float** channels;
    Array<int> inputs, outputs, parameters;
    float* unscaledParameters;
    float* normalParameters;

    ReferenceCountedObjectPtr <LADSPAModuleHandle> module;

    //==============================================================================
    void initialise();
    const String getVersion() const throw();
    const String getCategory() const throw();
    void setPower (const bool on);

    LADSPAPluginInstance (const ReferenceCountedObjectPtr <LADSPAModuleHandle>& module);
};

//==============================================================================
LADSPAPluginInstance::LADSPAPluginInstance (const ReferenceCountedObjectPtr <LADSPAModuleHandle>& module_)
    : ptrPlug (0),
      effect (0),
      initialised (false),
      isPowerOn (false),
      tempBuffer (1, 1),
      channels (0),
      module (module_)
{
    try
    {
        _fpreset();

        ++insideLADSPACallback;

        name = module->pluginName;
#if JUCE_DEBUG
        printf ("Creating LADSPA instance: %s \n", (const char*) name);
#endif

        if (module->moduleMain != 0)
        {
            ptrPlug = module->moduleMain (shellLADSPAUIDToCreate);
            if (ptrPlug == 0)
            {
#if JUCE_DEBUG
                printf ("Cannot find any valid descriptor in shared library\n");
#endif
                --insideLADSPACallback;
                return;
            }
        }
        else
        {
#if JUCE_DEBUG
            printf ("Cannot find any valid plugin in shared library\n");
#endif
            --insideLADSPACallback;
            return;
        }

        uint32 sampleRate = (uint32) (getSampleRate() > 0 ? getSampleRate() : 44100.0f);

        effect = ptrPlug->instantiate (ptrPlug, sampleRate);

        --insideLADSPACallback;

        _fpreset(); // some dodgy plugs fuck around with this
    }
    catch (...)
    {
        --insideLADSPACallback;
    }
}

LADSPAPluginInstance::~LADSPAPluginInstance()
{
    {
        const ScopedLock sl (lock);

        jassert (insideLADSPACallback == 0);

        try
        {
            // Must delete any editors before deleting the plugin instance!
            jassert (getActiveEditor() == 0);

            if (ptrPlug && ptrPlug->cleanup)
                ptrPlug->cleanup (effect);

            _fpreset(); // some dodgy plugs fuck around with this
        }
        catch (...)
        {}

        if (unscaledParameters) delete[] unscaledParameters;
        if (normalParameters) delete[] normalParameters;

        module = 0;
        effect = 0;
        ptrPlug = 0;
    }

    juce_free (channels);
    channels = 0;
}

//==============================================================================
void LADSPAPluginInstance::initialise()
{
    if (initialised || ptrPlug == 0 || effect == 0)
        return;

#if JUCE_DEBUG
    printf ("Initialising LADSPA: %s \n", (const char*) module->pluginName);
#endif
    initialised = true;

    // this code would ask the plugin for its name, but so few plugins
    // actually bother implementing this correctly, that it's better to
    // just ignore it and use the file name instead.
    name = module->pluginName;

    inputs.clear ();
    outputs.clear ();
    parameters.clear ();

    for (uint i = 0; i < ptrPlug->PortCount; i++)
    {
        if (ptrPlug->PortDescriptors [i] & LADSPA_PORT_CONTROL)
            parameters.add (i);

        if (ptrPlug->PortDescriptors [i] & LADSPA_PORT_AUDIO)
        {
            if (ptrPlug->PortDescriptors [i] & LADSPA_PORT_INPUT)
                inputs.add (i);

            if (ptrPlug->PortDescriptors [i] & LADSPA_PORT_OUTPUT)
                outputs.add (i);
        }
    }

    unscaledParameters = new float [parameters.size ()];
    memset (unscaledParameters, 0, parameters.size () * sizeof (float));

    normalParameters = new float [parameters.size ()];
    memset (normalParameters, 0, parameters.size () * sizeof (float));

    for (int i = 0; i < parameters.size (); i++)
        ptrPlug->connect_port (effect, parameters [i], &normalParameters[i]);

    setPlayConfigDetails (inputs.size (), outputs.size (),
                          getSampleRate() ? getSampleRate() : 44100.0f,
                          getBlockSize() ? getBlockSize() : 512);

    setCurrentProgram (0);
    setLatencySamples (0);
}


//==============================================================================
void LADSPAPluginInstance::prepareToPlay (double sampleRate_,
                                          int samplesPerBlockExpected)
{
    setPlayConfigDetails (inputs.size (), outputs.size (),
                          sampleRate_, samplesPerBlockExpected);

    setLatencySamples (0);

    juce_free (channels);
    channels = (float**) juce_calloc (sizeof (float*) * jmax (16, getNumOutputChannels() + 2, getNumInputChannels() + 2));

    initialise();

    if (initialised)
    {
        tempBuffer.setSize (jmax (1, outputs.size()), samplesPerBlockExpected);

        if (! isPowerOn)
            setPower (true);

        // dodgy hack to force some plugins to initialise the sample rate..
        if (getNumParameters() > 0)
        {
            const float old = getParameter (0);
            setParameter (0, (old < 0.5f) ? 1.0f : 0.0f);
            setParameter (0, old);
        }
    }
}

void LADSPAPluginInstance::releaseResources()
{
    if (initialised)
    {
        setPower (false);
    }

    tempBuffer.setSize (1, 1);

    juce_free (channels);
    channels = 0;
}

void LADSPAPluginInstance::processBlock (AudioSampleBuffer& buffer,
                                         MidiBuffer& midiMessages)
{
    const int numSamples = buffer.getNumSamples();

    if (initialised && ptrPlug)
    {
        int i;
        const int maxChans = jmax (inputs.size (), outputs.size ());

        for (i = 0; i < maxChans; ++i)
            channels[i] = buffer.getSampleData (i);
        channels [maxChans] = 0;

        _clearfp();

        for (i = 0; i < inputs.size (); i++)
            ptrPlug->connect_port (effect, inputs [i], channels [i]);

        if (ptrPlug->run)
        {
            for (i = 0; i < outputs.size (); i++)
                ptrPlug->connect_port (effect, outputs [i], channels [i]);

            try
            {
                ptrPlug->run (effect, numSamples);
            }
            catch (...)
            {}
        }
        else if (ptrPlug->run_adding)
        {
            tempBuffer.setSize (outputs.size(), numSamples);
            tempBuffer.clear();

            float* outs [64];

            for (i = outputs.size (); --i >= 0;)
                outs[i] = tempBuffer.getSampleData (i);
            outs [outputs.size ()] = 0;

            for (i = 0; i < outputs.size (); i++)
                ptrPlug->connect_port (effect, outputs [i], outs [i]);

            try
            {
                ptrPlug->run_adding (effect, numSamples);
            }
            catch (...)
            {}

            for (i = outputs.size (); --i >= 0;)
                buffer.copyFrom (i, 0, outs[i], numSamples);
        }
        else
        {
        }
    }
    else
    {
        // Not initialised, so just bypass..
        for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
            buffer.clear (i, 0, buffer.getNumSamples());
    }
}

//==============================================================================
AudioProcessorEditor* LADSPAPluginInstance::createEditor()
{
    return 0;
}

//==============================================================================
//==============================================================================
const String LADSPAPluginInstance::getName () const
{
    return (ptrPlug && ptrPlug->Label) ? String (ptrPlug->Label)
                                       : module->file.getFileNameWithoutExtension ();
}

const String LADSPAPluginInstance::getVersion() const throw()
{
    return T(LADSPA_VERSION);
}

int LADSPAPluginInstance::getUID() const throw()
{
    int uid = ptrPlug ? ptrPlug->UniqueID : 0;

    if (uid == 0)
        uid = module->file.hashCode();

    return uid;
}

const String LADSPAPluginInstance::getCategory() const throw()
{
    return "Effect";
}

//==============================================================================
float LADSPAPluginInstance::getParameter (int index)
{
    if (ptrPlug != 0 && ((unsigned int) index) < (unsigned int) parameters.size())
    {
        try
        {
            const ScopedLock sl (lock);
            return unscaledParameters [index];
        }
        catch (...)
        {
        }
    }

    return 0.0f;
}

void LADSPAPluginInstance::setParameter (int index, float newValue)
{
    if (ptrPlug != 0 && ((unsigned int) index) < (unsigned int) parameters.size())
    {
        try
        {
            const ScopedLock sl (lock);

            if (unscaledParameters [index] != newValue)
            {
                const LADSPA_PortRangeHint* hint = & ptrPlug->PortRangeHints [parameters [index]];

                float lower = hint->LowerBound *
                              (LADSPA_IS_HINT_SAMPLE_RATE (hint->HintDescriptor) ? getSampleRate() : 1.0f);
                float upper = hint->UpperBound *
                              (LADSPA_IS_HINT_SAMPLE_RATE (hint->HintDescriptor) ? getSampleRate() : 1.0f);

                // @TODO - Handle better lower/upper bound. this is ok for most cases
                //         but in some others it don't

                if (LADSPA_IS_HINT_TOGGLED (hint->HintDescriptor))
                {
                    normalParameters [index] = (newValue < 0.5f) ? 0.0f : 1.0f;
                }
                else if (LADSPA_IS_HINT_BOUNDED_BELOW (hint->HintDescriptor)
                         && LADSPA_IS_HINT_BOUNDED_ABOVE (hint->HintDescriptor))
                {
                    if (LADSPA_IS_HINT_LOGARITHMIC(hint->HintDescriptor)
                        && lower > 0.0f && upper > 0.0f)
                        normalParameters [index] = expf(logf(lower) * newValue + logf(upper) * (1.0f - newValue));
                    else
                        normalParameters [index] = lower + (upper - lower) * newValue;
                }
                else if (LADSPA_IS_HINT_BOUNDED_BELOW (hint->HintDescriptor))
                {
                    normalParameters [index] = newValue;
                }
                else if (LADSPA_IS_HINT_BOUNDED_ABOVE (hint->HintDescriptor))
                {
                    normalParameters [index] = newValue * upper;
                }

                if (LADSPA_IS_HINT_INTEGER (hint->HintDescriptor))
                    normalParameters [index] = (float) ((int) normalParameters [index]);

                unscaledParameters [index] = newValue;
            }
        }
        catch (...)
        {
        }
    }
}

const String LADSPAPluginInstance::getParameterName (int index)
{
    if (ptrPlug != 0)
    {
        jassert (index >= 0 && index < parameters.size ());

        return String (ptrPlug->PortNames [parameters [index]]).trim();
    }

    return String::empty;
}

const String LADSPAPluginInstance::getParameterText (int index)
{
    if (ptrPlug != 0)
    {
        jassert (index >= 0 && index < parameters.size ());

        const LADSPA_PortRangeHint* hint = & ptrPlug->PortRangeHints [parameters [index]];

        if (LADSPA_IS_HINT_INTEGER (hint->HintDescriptor))
            return String ((int) normalParameters [index]);
        else
            return String (normalParameters [index], 4);
    }

    return String::empty;
}

bool LADSPAPluginInstance::isParameterAutomatable (int index) const
{
    return true;
}

//==============================================================================
void LADSPAPluginInstance::setCurrentProgram (int newIndex)
{
    if (ptrPlug)
    {
        for (int i = 0; i < parameters.size (); i++)
        {
            const LADSPA_PortRangeHint* hint = & ptrPlug->PortRangeHints [parameters [i]];

            float lower = hint->LowerBound *
                          (LADSPA_IS_HINT_SAMPLE_RATE (hint->HintDescriptor) ? getSampleRate() : 1.0f);
            float upper = hint->UpperBound *
                          (LADSPA_IS_HINT_SAMPLE_RATE (hint->HintDescriptor) ? getSampleRate() : 1.0f);

            if (LADSPA_IS_HINT_HAS_DEFAULT (hint->HintDescriptor))
            {
                if (LADSPA_IS_HINT_DEFAULT_0 (hint->HintDescriptor))
                {
                    normalParameters [i] = 0.0f;
                    unscaledParameters [i] = 0.0f;
                }
                if (LADSPA_IS_HINT_DEFAULT_1 (hint->HintDescriptor))
                {
                    normalParameters [i] = 1.0f;
                    unscaledParameters [i] = 1.0f;
                }
                if (LADSPA_IS_HINT_DEFAULT_100 (hint->HintDescriptor))
                {
                    normalParameters [i] = 100.0f;
                    unscaledParameters [i] = 0.5f;
                }
                if (LADSPA_IS_HINT_DEFAULT_440 (hint->HintDescriptor))
                {
                    normalParameters [i] = 440.0f;
                    unscaledParameters [i] = 0.5f;
                }

                if (LADSPA_IS_HINT_BOUNDED_BELOW(hint->HintDescriptor)
                    && LADSPA_IS_HINT_DEFAULT_MINIMUM (hint->HintDescriptor))
                {
                    normalParameters [i] = lower;
                    unscaledParameters [i] = 0.0f;
                }

                if (LADSPA_IS_HINT_BOUNDED_ABOVE(hint->HintDescriptor)
                    && LADSPA_IS_HINT_DEFAULT_MAXIMUM (hint->HintDescriptor))
                {
                    normalParameters [i] = upper;
                    unscaledParameters [i] = 1.0f;
                }

                if (LADSPA_IS_HINT_BOUNDED_BELOW(hint->HintDescriptor))
                {
                    if (LADSPA_IS_HINT_LOGARITHMIC(hint->HintDescriptor)
                        && lower > 0.0f && upper > 0.0f)
                    {
                        if (LADSPA_IS_HINT_DEFAULT_LOW(hint->HintDescriptor)) {
                            normalParameters [i] = expf(logf(lower) * 0.75f + logf(upper) * 0.25f);
                            unscaledParameters [i] = 0.25f;
                        } else if (LADSPA_IS_HINT_DEFAULT_MIDDLE(hint->HintDescriptor)) {
                            normalParameters [i] = expf(logf(lower) * 0.5f + logf(upper) * 0.5f);
                            unscaledParameters [i] = 0.5f;
                        } else if (LADSPA_IS_HINT_DEFAULT_HIGH(hint->HintDescriptor)) {
                            normalParameters [i] = expf(logf(lower) * 0.25f + logf(upper) * 0.75f);
                            unscaledParameters [i] = 0.75f;
                        }
                    }
                    else
                    {
                        if (LADSPA_IS_HINT_DEFAULT_LOW(hint->HintDescriptor)) {
                            normalParameters [i] = lower * 0.75f + upper * 0.25f;
                            unscaledParameters [i] = 0.25f;
                        } else if (LADSPA_IS_HINT_DEFAULT_MIDDLE(hint->HintDescriptor)) {
                            normalParameters [i] = lower * 0.5f + upper * 0.5f;
                            unscaledParameters [i] = 0.5f;
                        } else if (LADSPA_IS_HINT_DEFAULT_HIGH(hint->HintDescriptor)) {
                            normalParameters [i] = lower * 0.25f + upper * 0.75f;
                            unscaledParameters [i] = 0.75f;
                        }
            	    }
            	}
            }
            else
            {
                normalParameters [i] = 0.0f;
                unscaledParameters [i] = 0.0f;
            }
        }
    }
}

const String LADSPAPluginInstance::getProgramName (int index)
{
#if 0
    if (index == getCurrentProgram())
    {
        return getCurrentProgramName();
    }
    else if (effect != 0)
    {
        char nm [256];
        zerostruct (nm);

        if (dispatch (effGetProgramNameIndexed,
                      jlimit (0, getNumPrograms(), index),
                      -1, nm, 0) != 0)
        {
            return String (nm).trim();
        }
    }

    return programNames [index];
#endif

    return String::empty;
}

void LADSPAPluginInstance::changeProgramName (int index, const String& newName)
{
#if 0
    if (index == getCurrentProgram())
    {
        if (getNumPrograms() > 0 && newName != getCurrentProgramName())
            dispatch (effSetProgramName, 0, 0, (void*) (const char*) newName.substring (0, 24), 0.0f);
    }
    else
    {
        jassertfalse // xxx not implemented!
    }
#endif
}

//==============================================================================
const String LADSPAPluginInstance::getInputChannelName (const int index) const
{
    if (index >= 0 && index < getNumInputChannels())
    {
        return String (ptrPlug->PortNames [inputs [index]]).trim();
    }

    return String::empty;
}

bool LADSPAPluginInstance::isInputChannelStereoPair (int index) const
{
    if (index < 0 || index >= getNumInputChannels())
        return false;

    return true;
}

const String LADSPAPluginInstance::getOutputChannelName (const int index) const
{
    if (index >= 0 && index < getNumOutputChannels())
    {
        return String (ptrPlug->PortNames [outputs [index]]).trim();
    }

    return String::empty;
}

bool LADSPAPluginInstance::isOutputChannelStereoPair (int index) const
{
    if (index < 0 || index >= getNumOutputChannels())
        return false;

    return true;
}

//==============================================================================
void LADSPAPluginInstance::setPower (const bool on)
{
    isPowerOn = on;
}

//==============================================================================
void LADSPAPluginInstance::getStateInformation (MemoryBlock& destData)
{
    destData.setSize (sizeof(float) * getNumParameters());
    destData.fillWith (0);

    float* const p = (float*) ((char*) destData.getData());
    for (int i = 0; i < getNumParameters(); ++i)
        p[i] = getParameter(i);
}

void LADSPAPluginInstance::getCurrentProgramStateInformation (MemoryBlock& destData)
{
    getStateInformation (destData);
}

void LADSPAPluginInstance::setStateInformation (const void* data, int sizeInBytes)
{
    float* p = (float*) ((char*) data);
    for (int i = 0; i < getNumParameters(); ++i)
        setParameter (i, p[i]);
}

void LADSPAPluginInstance::setCurrentProgramStateInformation (const void* data, int sizeInBytes)
{
    setStateInformation (data, sizeInBytes);
}


//==============================================================================
//==============================================================================
LADSPAPluginFormat::LADSPAPluginFormat()
{
}

LADSPAPluginFormat::~LADSPAPluginFormat()
{
}

void LADSPAPluginFormat::findAllTypesForFile (OwnedArray <PluginDescription>& results,
                                              const String& fileOrIdentifier)
{
    if (! fileMightContainThisPluginType (fileOrIdentifier))
        return;

    PluginDescription desc;
    desc.fileOrIdentifier = fileOrIdentifier;
    desc.uid = 0;

    LADSPAPluginInstance* instance = dynamic_cast <LADSPAPluginInstance*> (createInstanceFromDescription (desc));

    if (instance == 0)
        return;

    try
    {
        instance->fillInPluginDescription (desc);

        if (instance->module->moduleMain != 0)
        {
            char shellEffectName [64];
        
            for (int uid = 0;; uid++)
            {
                zerostruct (shellEffectName);
                
                const LADSPA_Descriptor* plugin = instance->module->moduleMain (uid);
                if (plugin)
                {
                    desc.uid = uid;
                    desc.name = plugin->Name ? plugin->Name : "Unknown";

                    bool alreadyThere = false;

                    for (int i = results.size(); --i >= 0;)
                    {
                        PluginDescription* const d = results.getUnchecked(i);
                        if (d->isDuplicateOf (desc))
                        {
                            alreadyThere = true;
                            break;
                        }
                    }

                    if (! alreadyThere)
                        results.add (new PluginDescription (desc));
                }
                else
                {
                    break;
                }
            }        
        }
    }
    catch (...)
    {
        // crashed while loading...
    }

    deleteAndZero (instance);
}

AudioPluginInstance* LADSPAPluginFormat::createInstanceFromDescription (const PluginDescription& desc)
{
    LADSPAPluginInstance* result = 0;

    if (fileMightContainThisPluginType (desc.fileOrIdentifier))
    {
        File file (desc.fileOrIdentifier);

        const File previousWorkingDirectory (File::getCurrentWorkingDirectory());
        file.getParentDirectory().setAsCurrentWorkingDirectory();

        const ReferenceCountedObjectPtr <LADSPAModuleHandle> module (LADSPAModuleHandle::findOrCreateModule (file));

        if (module != 0)
        {
            shellLADSPAUIDToCreate = desc.uid;

            result = new LADSPAPluginInstance (module);

            if (result->ptrPlug != 0)
            {
                result->initialise();
            }
            else
            {
                deleteAndZero (result);
            }
        }

        previousWorkingDirectory.setAsCurrentWorkingDirectory();
    }

    return result;
}

bool LADSPAPluginFormat::fileMightContainThisPluginType (const String& fileOrIdentifier)
{
    const File f (fileOrIdentifier);

#if JUCE_WIN32
    return f.existsAsFile()
            && f.hasFileExtension (T(".dll"));
#elif JUCE_MAC
    return f.existsAsFile()
            && f.hasFileExtension (T(".so"));
#elif JUCE_LINUX
    return f.existsAsFile()
            && f.hasFileExtension (T(".so"))
            && f.getFileNameWithoutExtension () != T("dssi-vst");
            // hack for special dssi-vst, which can't be instantiated like it is
            // but it needs a special activation layer called vsthost. if this is
            // commented, the audioplugin host will hang when trying to instantiate
            // dssi-vst shared library
#endif
}

const String LADSPAPluginFormat::getNameOfPluginFromIdentifier (const String& fileOrIdentifier)
{
    return fileOrIdentifier;
}

bool LADSPAPluginFormat::doesPluginStillExist (const PluginDescription& desc)
{
    return File (desc.fileOrIdentifier).exists();
}

const StringArray LADSPAPluginFormat::searchPathsForPlugins (const FileSearchPath& directoriesToSearch, const bool recursive)
{
    StringArray results;

    for (int j = 0; j < directoriesToSearch.getNumPaths(); ++j)
        recursiveFileSearch (results, directoriesToSearch [j], recursive);

    return results;
}

void LADSPAPluginFormat::recursiveFileSearch (StringArray& results, const File& dir, const bool recursive)
{
    DirectoryIterator iter (dir, false, "*", File::findFilesAndDirectories);

    while (iter.next())
    {
        const File f (iter.getFile());
        bool isPlugin = false;

        if (fileMightContainThisPluginType (f.getFullPathName()))
        {
            isPlugin = true;
            results.add (f.getFullPathName());
        }

        if (recursive && (! isPlugin) && f.isDirectory())
            recursiveFileSearch (results, f, true);
    }
}

const FileSearchPath LADSPAPluginFormat::getDefaultLocationsToSearch()
{
#if JUCE_MAC
    return FileSearchPath ("~/Library/Audio/Plug-Ins/LADSPA;/Library/Audio/Plug-Ins/LADSPA");
#elif JUCE_WIN32
    const String programFiles (File::getSpecialLocation (File::globalApplicationsDirectory).getFullPathName());
    return FileSearchPath (programFiles + "\\LadspaPlugins");
#elif JUCE_LINUX
    return FileSearchPath ("/usr/lib/ladspa");
#endif
}


END_JUCE_NAMESPACE

#endif

