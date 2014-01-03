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

#include "VstPlugin.h"
#include "../../HostFilterBase.h"
#include "../../HostFilterComponent.h"


#if JOST_USE_VST

BEGIN_JUCE_NAMESPACE
 extern void juce_callAnyTimersSynchronously();
END_JUCE_NAMESPACE

//==============================================================================
/**
    The magnificient host callback, which every plugin will call
*/
static int insideVSTCallback = 0;

static VstIntPtr VSTCALLBACK HostCallback (AEffect* effect,
                                           VstInt32 opcode,
                                           VstInt32 index,
                                           VstIntPtr value,
                                           void* ptr,
                                           float opt);


//==============================================================================
VstPluginMidiManager::VstPluginMidiManager ()
{
    int pointersize = sizeof (VstEvent*);
    int bufferSize = sizeof (VstEvents) - (pointersize * 2);
    bufferSize += pointersize * 2048;
    ptrEventBuffer = new char [bufferSize + 1];
}

VstPluginMidiManager::~VstPluginMidiManager ()
{
    // delete midi buffers
    delete[] ptrEventBuffer;
}

void VstPluginMidiManager::convertMidiMessages (MidiBuffer& midiMessages,
                                                const int blockSamples)
{
    const uint8* data;
    int currentMidiCount = 0,
        numBytesOfMidiData,
        samplePosition;
    MidiBuffer::Iterator it (midiMessages);

    while (it.getNextEvent (data,
                            numBytesOfMidiData,
                            samplePosition))
    {
        VstMidiEvent* ptrWrite = &midiEventsBuffer [currentMidiCount];

        ptrWrite->type = kVstMidiType;
        ptrWrite->byteSize = sizeof (VstMidiEvent); // numBytesOfMidiData * 8; // 24
        ptrWrite->deltaFrames = (samplePosition >= blockSamples)
                                 ? (blockSamples - 1) : (samplePosition);
        ptrWrite->flags = 0; // kVstMidiEventIsRealtime; // vstsdk 2.4
        ptrWrite->noteLength = 0;
        ptrWrite->noteOffset = 0;
        memcpy (ptrWrite->midiData, data, sizeof (uint32));
        ptrWrite->detune = 0;
        ptrWrite->noteOffVelocity = 0;
        ptrWrite->reserved1 = 0;
        ptrWrite->reserved2 = 0;

        if (++currentMidiCount >= 2048)
            break;
    }

    VstEvents* ev = (VstEvents*) ptrEventBuffer;
    for (int i = 0; i < currentMidiCount; i++)
    {
        ev->events[i] = (VstEvent*) & midiEventsBuffer [i];
    }
    ev->numEvents = currentMidiCount;
    ev->reserved = 0;
}


//==============================================================================
VstPlugin::VstPlugin ()
  : module (0),
    effect (0),
    flagsEx (0),
    sampleRate (44100.0),
    blockSize (512)
{
    insideVSTCallback = 0;
}

VstPlugin::~VstPlugin ()
{
    dispatch (effClose, 0, 0, 0, 0.0f);

    removeAllParameters (true);

    try
    {
        if (module)
            PlatformUtilities::freeDynamicLibrary (module);
        module = 0;
    }
    catch (...)
    {
    }
}

//==============================================================================
bool VstPlugin::loadPluginFromFile (const File& filePath)
{
    ++insideVSTCallback;

    module = PlatformUtilities::loadDynamicLibrary (filePath.getFullPathName());

    if (module != 0)
    {
        // library loaded OK
        AEffect* (*getPluginInstance) (audioMasterCallback);
        
        getPluginInstance = (AEffect* (*)(audioMasterCallback))
                                PlatformUtilities::getProcedureEntryPoint (module, "VSTPluginMain");

        if (getPluginInstance == 0)
            getPluginInstance = (AEffect* (*)(audioMasterCallback))
                                    PlatformUtilities::getProcedureEntryPoint (module, "main");

        if (getPluginInstance != 0)
        {
            // main function located OK
            try
            {
                effect = getPluginInstance (HostCallback);
            }
            catch (...)
            {
                // plugin raised an exception
                printf ("Plugin has raised an exception in main \n");
                
                PlatformUtilities::freeDynamicLibrary (module);
                --insideVSTCallback;
                module = 0;
                effect = 0;
                return false;
            }

            if (effect != 0)
            {
                // plugin instantiated OK
                if (effect->magic != kEffectMagic)
                {
                    printf ("Plugin is not a valid VST \n");

                    
                    PlatformUtilities::freeDynamicLibrary (module);
                    --insideVSTCallback;
                    module = 0;
                    effect = 0;
                    return false;
                }
            }
            else
            {
                printf ("Plugin instance cannot be created for some reason \n");
                
                PlatformUtilities::freeDynamicLibrary (module);
                --insideVSTCallback;
                module = 0;
                effect = 0;
                return false;
            }
        }
        else
        {
            printf ("Plugin does not have a main function \n");

            PlatformUtilities::freeDynamicLibrary (module);
            --insideVSTCallback;
            module = 0;
            effect = 0;
            return false;
        }
    }
    else
    {
        printf ("You are trying to load a shared library ? \n");
        --insideVSTCallback;
        return false;
    }

    --insideVSTCallback;

    pluginFile = filePath;

    effect->resvd2 = (VstIntPtr) this;

#ifndef VST_FORCE_DEPRECATED
    dispatch (effIdentify, 0, 0, 0, 0);
#endif
    dispatch (effSetSampleRate, 0, 0, 0, 44100.0f);
    dispatch (effSetBlockSize, 0, 512, 0, 0);
    dispatch (effOpen, 0, 0, 0, 0);

    if (canDo (T("sendVstEvents")))            flagsEx |= effFlagsExCanSendVstEvents;
    if (canDo (T("sendVstMidiEvent")))         flagsEx |= effFlagsExCanSendVstMidiEvents;
    if (canDo (T("sendVstTimeInfo")))          flagsEx |= effFlagsExCanSendVstTimeInfo;
    if (canDo (T("receiveVstEvents")))         flagsEx |= effFlagsExCanReceiveVstEvents;
    if (canDo (T("receiveVstMidiEvent")))      flagsEx |= effFlagsExCanReceiveVstMidiEvents;
    if (canDo (T("receiveVstTimeInfo")))       flagsEx |= effFlagsExCanReceiveVstTimeInfo;
    if (canDo (T("offline")))                  flagsEx |= effFlagsExCanProcessOffline;
    if (canDo (T("plugAsChannelInsert")))      flagsEx |= effFlagsExCanUseAsInsert;
    if (canDo (T("plugAsSend")))               flagsEx |= effFlagsExCanUseAsSend;
    if (canDo (T("mixDryWet")))                flagsEx |= effFlagsExCanMixDryWet;

    // set default program
    if (getNumPrograms() > 1)
        setCurrentProgram (0);
    else
        dispatch (effSetProgram, 0, 0, 0, 0);

    // connect inputs and outputs
#ifndef VST_FORCE_DEPRECATED
    int i;
    for (i = effect->numInputs; --i >= 0;)
        dispatch (effConnectInput, i, 1, 0, 0);

    for (i = effect->numOutputs; --i >= 0;)
        dispatch (effConnectOutput, i, 1, 0, 0);
#endif

    // create parameters
    char strName [256];
    setNumParameters (effect->numParams);

    for (int i = 0; i < effect->numParams; i++)
    {
        AudioParameter* parameter = new AudioParameter ();

        dispatch (effGetParamName, i, 0, strName, 0.0f);
        
        parameter->part (i);
        parameter->name (String (strName));
//        parameter->mapping (AudioParameter::RangeLinear);
        parameter->range (0.0f, 1.0f);
        parameter->get (MakeDelegate (this, &VstPlugin::getParameterReal));
        parameter->set (MakeDelegate (this, &VstPlugin::setParameterReal));
        parameter->text (MakeDelegate (this, &VstPlugin::getParameterTextReal));
        
        registerParameter (i, parameter);
    }

    return true;
}

//==============================================================================
void VstPlugin::prepareToPlay (double sampleRate_, int samplesPerBlock_)
{
    keyboardState.reset();

    sampleRate = sampleRate_;
    blockSize = samplesPerBlock_;

    dispatch (effSetSampleRate, 0, 0, 0, (float) sampleRate);
    dispatch (effSetBlockSize, 0, jmax (16, blockSize), 0, 0.0f);

    dispatch (effMainsChanged, 0, 1, 0, 0.0f);

    // dodgy hack to force some plugins to initialise the sample rate..
    if ((! hasEditor()) && getNumParameters() > 0)
    {
        const float old = getParameter (0);
        setParameter (0, (old < 0.5f) ? 1.0f : 0.0f);
        setParameter (0, old);
    }

    dispatch (effStartProcess, 0, 0, 0, 0);
}

void VstPlugin::releaseResources()
{
    dispatch (effStopProcess, 0, 0, 0, 0);
    
    dispatch (effMainsChanged, 0, 0, 0, 0.0f);
}

void VstPlugin::processBlock (AudioSampleBuffer& buffer,
                              MidiBuffer& midiMessages)
{
    float* ptrInputBuffers [128];
    float* ptrOutputBuffers [128];

    const int blockSize = buffer.getNumSamples ();

    // clear incoming midi
    if (flagsEx & effFlagsExCanSendVstMidiEvents)
        sendToOutMidi.clear ();

    // internal buffer coming from other plugins    
    MidiBuffer* midiBuffer = midiBuffers.getUnchecked (0);

    // add events from keyboards
    keyboardState.processNextMidiBuffer (*midiBuffer,
                                         0, blockSize,
                                         true);

    // process midi automation
    midiAutomatorManager.handleMidiMessageBuffer (*midiBuffer);

    if (flagsEx & effFlagsExCanReceiveVstMidiEvents
        || effect->flags & effFlagsIsSynth)
    {
        // convert midi messages internally
        midiManager.convertMidiMessages ((*midiBuffer), blockSize);

        // call processEvents
        dispatch (effProcessEvents, 0, 0, (VstEvents*) midiManager.getMidiEvents (), 0.0f);
    }

    // do the real processing
    if (inputBuffer)
    {
        int numInputs = jmin (effect->numInputs, 128);
        for (int i = 0; i < numInputs; i++)
            ptrInputBuffers [i] = inputBuffer->getSampleData (i);

        // effect->flags & effFlagsCanMono
    }

    if (outputBuffer)
    {
        if (! (effect->flags & effFlagsCanReplacing))
            outputBuffer->clear ();

        int numOutputs = jmin (effect->numOutputs, 128);
        for (int i = 0; i < numOutputs; i++)
            ptrOutputBuffers [i] = outputBuffer->getSampleData (i);
    }

    if (effect->flags & effFlagsCanReplacing)
    {
        effect->processReplacing (effect,
                                  ptrInputBuffers,
                                  ptrOutputBuffers,
                                  blockSize);
    }
#ifndef VST_FORCE_DEPRECATED
    else
    {
        effect->process (effect,
                         ptrInputBuffers,
                         ptrOutputBuffers,
                         blockSize);
    }
#endif

    // send midi
    if (flagsEx & effFlagsExCanSendVstMidiEvents)
    {
        // clear them
        midiBuffer->clear ();
        midiBuffer->addEvents (sendToOutMidi, 0, blockSize, 0);
    }
}

void VstPlugin::timerCallback ()
{
#ifndef VST_FORCE_DEPRECATED
    if (! dispatch (effIdle, 0, 0, 0, 0.0f))
        stopTimer ();
#endif
}

void VstPlugin::sendMidiEventToOutput (VstEvents* events)
{
    if (events != 0)
    {
        // const ScopedLock sl (midiInLock);
        for (int i = 0; i < events->numEvents; ++i)
        {
            const VstEvent* const e = events->events[i];
            if (e->type == kVstMidiType)
            {
                sendToOutMidi.addEvent ((const uint8*) ((const VstMidiEvent*) e)->midiData,
                                        3, e->deltaFrames);
            }
        }
    }
}

//==============================================================================
const String VstPlugin::getName () const
{
    char strName[256];
    if (dispatch (effGetEffectName, 0, 0, strName, 0.0f))
        return String (strName);
    else
        return pluginFile.getFileNameWithoutExtension ();
}

File VstPlugin::getFile () const
{
    return pluginFile;
}

void* VstPlugin::getLowLevelHandle ()
{
    return effect;
}

int VstPlugin::getID () const
{
    return effect->uniqueID;
}

int VstPlugin::getNumInputs () const
{
    return effect->numInputs;
}

int VstPlugin::getNumOutputs () const
{
    return effect->numOutputs;
}

int VstPlugin::getNumMidiInputs () const
{
    return 1;
}

int VstPlugin::getNumMidiOutputs () const
{
    return (flagsEx & effFlagsExCanSendVstMidiEvents) ? 1 : 0;
}

bool VstPlugin::producesMidi () const
{
    return (flagsEx & effFlagsExCanSendVstMidiEvents);
}

bool VstPlugin::acceptsMidi () const
{
    return (flagsEx & effFlagsExCanReceiveVstMidiEvents)
           || (effect->flags & effFlagsIsSynth);
}

//==============================================================================
void VstPlugin::setParameterReal (int paramNumber, float value)
{
    effect->setParameter (effect, paramNumber, value);
}

float VstPlugin::getParameterReal (int paramNumber)
{
    return effect->getParameter (effect, paramNumber);
}

const String VstPlugin::getParameterTextReal (int paramNumber, float value)
{
#if 0
    char strLabel [256];
    dispatch (effGetParamLabel, paramNumber, 0, strLabel, 0.0f);
    return String (strLabel);
#endif

    char strDisplay [256];
    dispatch (effGetParamDisplay, paramNumber, 0, strDisplay, 0.0f);
    return String (strDisplay);
}

//==============================================================================
int VstPlugin::getNumPrograms ()
{
    return effect->numPrograms;
}

void VstPlugin::setCurrentProgram (int programNumber)
{
    dispatch (effSetProgram, 0, programNumber, 0, 0.0f);
}

int VstPlugin::getCurrentProgram ()
{
    return dispatch (effGetProgram, 0, 0, 0, 0.0f);
}

const String VstPlugin::getProgramName (int programNumber)
{
    char strProgramName [128];
    char strTempProgram [128];

    if (! dispatch (effGetProgramNameIndexed, programNumber, -1, strProgramName, 0.0f))
    {
       // the hard way - have to set each program to find it's name
       int tempPreset = dispatch (effGetProgram, 0, 0, strProgramName, 0.0f);
       dispatch (effSetProgram, 0, programNumber, strProgramName, 0.0f);
       dispatch (effGetProgramName, 0, 0, strProgramName, 0.0f);
       dispatch (effSetProgram, 0, tempPreset, strTempProgram, 0.0f);
    }

    return String (strProgramName);
}

const String VstPlugin::getCurrentProgramName ()
{
    char strProgramName [128];
    dispatch (effGetProgramName, 0, 0, strProgramName, 0.0f);
    return String (strProgramName);
}

void VstPlugin::getStateInformation (MemoryBlock& destData)
{
    if (effect->flags & effFlagsProgramChunks)
    {
        void* data = 0;
        int byteSize = dispatch (effGetChunk, 0 /* bank */, 0, &data, 0.0f);

        destData.setSize (byteSize);
        destData.copyFrom (data, 0, byteSize);
        
        // free (data);
    }
    else
    {
        MemoryOutputStream out (getNumParameters () * sizeof (float),
                                256,
                                & destData);
    
        for (int j = 0; j < getNumParameters (); j++)
        {
            out.writeFloat (getParameter (j));
        }
    }
}

void VstPlugin::setStateInformation (const void* data, int sizeInBytes)
{
    if (effect->flags & effFlagsProgramChunks)
    {
        MemoryBlock tempBlock (data, sizeInBytes);
    
        /* int byteSize = */ dispatch (effSetChunk,
                                       0 /* bank */,
                                       tempBlock.getSize(),
                                       tempBlock.getData(),
                                       0.0f);
    }
    else
    {
        MemoryInputStream is (data, sizeInBytes, false);
    
        for (int j = 0; j < getNumParameters (); j++)
        {
            if (is.isExhausted ())
                break;

            setParameter (j, is.readFloat ());
        }
    }
}

//==============================================================================
bool VstPlugin::hasEditor () const
{
    return effect->flags & effFlagsHasEditor;
}

bool VstPlugin::wantsEditor () const
{
    return true;
}

void VstPlugin::openEditor (void* handle, void* display)
{
    dispatch (effEditOpen, 0, (VstIntPtr) display, handle, 0.0f);
}

void VstPlugin::closeEditor ()
{
    dispatch (effEditClose, 0, 0, 0, 0.0f);
}

void VstPlugin::idleEditor ()
{
    dispatch (effEditIdle, 0, 0, 0, 0.0f);
}

void VstPlugin::getEditorSize (int& width, int& height)
{
    ERect* editorSize;

    dispatch (effEditGetRect, 0, 0, &editorSize, 0.0f);

    width = editorSize->right - editorSize->left;
    height = editorSize->bottom - editorSize->top;
}

//==============================================================================
bool VstPlugin::canDo (const String& canDoString) const
{
    return dispatch (effCanDo, 0, 0, (void*) (const char*) canDoString, 0.0f) > 0;
}

//==============================================================================
int VstPlugin::dispatch (const int opcode, const int index, const int value, void* const ptr, float opt) const
{
//    const ScopedLock sl (lock);

    ++insideVSTCallback;
    int result = 0;

    try
    {
        if (effect != 0)
        {
            result = effect->dispatcher (effect, opcode, index, value, ptr, opt);

            --insideVSTCallback;
            return result;
        }
    }
    catch (...)
    {
#if 0 && JUCE_DEBUG
        char s[512];
        sprintf (s, "dispatcher (%d, %d, %d, %x, %f)", opcode, index, value, (int)ptr, opt);
#endif
    }

    --insideVSTCallback;
    return result;
}

//==============================================================================
int VstPlugin::openFileSelector (VstFileSelect *ptr)
{
    ptr->reserved = 0;

    if (ptr->command == kVstMultipleFilesLoad)
        return 0;  // not yet

    if ((ptr->command == kVstFileLoad) || (ptr->command == kVstFileSave))
    {
        String sFilter;
        for (int i = 0; i < ptr->nbFileTypes; i++)
        {
            sFilter += T("*.") + String (ptr->fileTypes[i].dosType);
            if (i < ptr->nbFileTypes - 1)
                sFilter += T(";");
        }

        if (sFilter == String::empty)
            sFilter += T("*.*;");

        FileChooser myChooser ((ptr->command == kVstFileLoad) ? T("Load...")
                                                              : T("Save..."),
                                File (String (ptr->initialPath)),
                                sFilter);

        if (ptr->command == kVstFileLoad)
        {
            if (myChooser.browseForFileToOpen())
            {
                String fileName = myChooser.getResult().getFullPathName ();

                if (! ptr->returnPath) {
                    ptr->returnPath = new char [fileName.length() + 1];
                    ptr->reserved = 1;
                }

                strcpy (ptr->returnPath, (const char*) fileName);
                ptr->nbReturnPath = 1;
            }
        }
        else if (ptr->command == kVstFileSave)
        {
            if (myChooser.browseForFileToSave (true))
            {
                String fileName = myChooser.getResult().getFullPathName ();

                if (! ptr->returnPath) {
                    ptr->returnPath = new char [fileName.length() + 1];
                    ptr->reserved = 1;
                }

                strcpy (ptr->returnPath, (const char*) fileName);
                ptr->nbReturnPath = 1;
            }
        }

        return ptr->nbReturnPath;
    }
    else if (ptr->command == kVstDirectorySelect)
    {
        FileChooser myChooser (T("Select directory..."),
                               File (String (ptr->initialPath)),
                               T("*.*"));

        if (myChooser.browseForDirectory ())
        {
            String fileName = myChooser.getResult().getFullPathName ();

            if (!ptr->returnPath)
            {
                ptr->returnPath = new char[fileName.length() + 1];
                ptr->reserved = 1;
            }
            
            strcpy (ptr->returnPath, (const char*) fileName);
            ptr->nbReturnPath = 1;

            return ptr->nbReturnPath;
        }
    }

    return 0;
}

int VstPlugin::closeFileSelector (VstFileSelect *ptr)
{
    if (ptr->reserved == 1 && ptr->returnPath)
    {
        delete[] ptr->returnPath;
        ptr->returnPath = 0;
        ptr->reserved = 0;
    }
    return 0;
}

//==============================================================================
// handles non plugin-specific callbacks..
static VstIntPtr handleGeneralCallback (VstInt32 opcode, VstInt32 index, VstInt32 value, void *ptr, float opt)
{
    (void) index;
    (void) value;
    (void) opt;

    switch (opcode)
    {
    case audioMasterCanDo:
        {
            static const char* canDos[] = { "supplyIdle",
                                            "sendVstEvents",
                                            "sendVstMidiEvent",
                                            "sendVstTimeInfo",
                                            "receiveVstEvents",
                                            "receiveVstMidiEvent",
                                            "openFileSelector",
                                            "closeFileSelector" };

            for (int i = 0; i < numElementsInArray (canDos); ++i)
                if (strcmp (canDos[i], (const char*) ptr) == 0)
                    return 1;

            return 0;
        }

    case audioMasterVersion:
        return 0x2300;

    case audioMasterCurrentId:
        //Input values:
        //none

        //Return Value
        //the unique id of a plug that's currently loading
        //zero is a default value and can be safely returned if not known
        return 0;

    case audioMasterGetAutomationState:
        //0: not supported
        //1: off
        //2:read
        //3:write
        //4:read/write
        return 1;

    case audioMasterGetVendorVersion:
        return JucePlugin_VersionCode;

    case audioMasterGetVendorString:
        String (JucePlugin_Manufacturer).copyToBuffer ((char*) ptr, 24); // jmin (kVstMaxVendorStrLen, kVstMaxProductStrLen) - 1
        break;

    case audioMasterGetProductString:
        String (JucePlugin_Desc).copyToBuffer ((char*) ptr, 24); // jmin (kVstMaxVendorStrLen, kVstMaxProductStrLen) - 1
        break;

    case audioMasterGetLanguage:
        return kVstLangEnglish;

    case audioMasterGetSampleRate:
        return 44100;

    case audioMasterGetBlockSize:
        return 512;

    default:
        break;
    }

    return 0;
}

//==============================================================================
static VstIntPtr VSTCALLBACK HostCallback (AEffect* effect,
                                           VstInt32 opcode,
                                           VstInt32 index,
                                           VstIntPtr value,
                                           void* ptr,
                                           float opt)
{
    try
    {
        if (effect != 0 && effect->resvd2 != 0)
        {
            return ((VstPlugin*)(effect->resvd2))
                        ->handleCallback (opcode, index, value, ptr, opt);
        }

        return handleGeneralCallback (opcode, index, value, ptr, opt);
    }
    catch (...)
    {
        return 0;
    }
}

//==============================================================================
// handles callbacks for a specific plugin
VstIntPtr VstPlugin::handleCallback (VstInt32 opcode, VstInt32 index, VstInt32 value, void *ptr, float opt)
{
    switch (opcode)
    {
    case audioMasterAutomate:
        sendParamChangeMessageToListeners (index, opt);
        break;

    case audioMasterProcessEvents:
        sendMidiEventToOutput ((VstEvents*) ptr);
        return 1;

    case audioMasterGetTime:
        // DBG ("audioMasterGetTime " + String (getParentHost()->getTransport()->getTimeInfo ()->tempo));
        if (getParentHost() && getParentHost()->getTransport())
            return (VstIntPtr) getParentHost()->getTransport()->getTimeInfo ();
        else return VstIntPtr(0); // we haven't been setParentHost()ed yet

    case audioMasterIdle:
        if (insideVSTCallback == 0 && MessageManager::getInstance()->isThisTheMessageThread())
        {
            ++insideVSTCallback;

            const MessageManagerLock mml;

            juce_callAnyTimersSynchronously();

//            handleUpdateNowIfNeeded();

            for (int i = ComponentPeer::getNumPeers(); --i >= 0;)
                ComponentPeer::getPeer (i)->performAnyPendingRepaintsNow();

            --insideVSTCallback;
        }
        break;

    case audioMasterUpdateDisplay:
/*
        HostFilterComponent* editor = host->getEditor ();
        if (editor)
        {
            editor->updatePluginEditorWindowDisplay ();
            return 1;
        }
*/
//        triggerAsyncUpdate();
        break;

    case audioMasterSizeWindow:
/* TODO
        HostFilterComponent* editor = getParentHost()->getEditor ();
        if (editor)
            editor->resizePluginEditorWindow (index, value);
*/
        return 1;

    case audioMasterGetSampleRate:
        return (VstIntPtr) sampleRate;

    case audioMasterGetBlockSize:
        return (VstIntPtr) blockSize;
        
    case audioMasterGetDirectory:
      #if JUCE_MAC
        return (VstIntPtr)  0; //(&module->parentDirFSSpec);
      #elif JUCE_WIN
        return (VstIntPtr) (pointer_sized_uint) (const char*) module->fullParentDirectoryPathName;
      #else
        return (VstIntPtr) (pointer_sized_uint) (const char*) pluginFile.getParentDirectory ().getFullPathName ();
      #endif

    case audioMasterGetAutomationState:
        // returns 0: not supported, 1: off, 2:read, 3:write, 4:read/write
        break;

    case audioMasterOpenFileSelector :
        return openFileSelector ((VstFileSelect*) ptr);

    case audioMasterCloseFileSelector :
        return closeFileSelector ((VstFileSelect*) ptr);

    // none of these are handled (yet)..
    case audioMasterBeginEdit:
    case audioMasterEndEdit:
    case audioMasterIOChanged:
    case audioMasterGetInputLatency:
    case audioMasterGetOutputLatency:
    case audioMasterGetCurrentProcessLevel:
    case audioMasterOfflineStart:
    case audioMasterOfflineRead:
    case audioMasterOfflineWrite:
    case audioMasterOfflineGetCurrentPass:
    case audioMasterOfflineGetCurrentMetaPass:
    case audioMasterVendorSpecific:
    case audioMasterGetLanguage:
#if JUCE_MAC
    case audioMasterOpenWindow:
    case audioMasterCloseWindow:
#endif
        break;

    default:
        return handleGeneralCallback (opcode, index, value, ptr, opt);
    }

    return 0;
}


#endif // JOST_USE_VST
