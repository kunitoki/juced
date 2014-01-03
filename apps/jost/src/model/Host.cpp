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

#include "Host.h"
#include "../HostFilterBase.h"


//==============================================================================
Host::Host (HostFilterBase* owner_,
            const int maxNumInputChannels,
            const int maxNumOutputChannels)
  : owner (owner_),
    currentPlugin (0),
    audioGraph (0),
    sampleRate (44100.0),
    samplesPerBlock (512)
{
    DBG ("Host::Host");

    transport = owner->getTransport ();

    // create an empty audio processing graph
    audioGraph = new ProcessingGraph ();

    // add generic plugins
    addPlugin (inputPlugin = new InputPlugin (maxNumInputChannels));
    addPlugin (outputPlugin = new OutputPlugin (maxNumOutputChannels));
}

Host::~Host()
{
    DBG ("Host::~Host");

    // free plugins
    closeAllPlugins (false);
    plugins.clear (true);

    // remove listeners after
    removeAllListeners ();

    // delete audio graph
    deleteAndZero (audioGraph);
}

//==============================================================================
BasePlugin* Host::getPluginByUniqueHash (const int hash) const
{
    for (int i = plugins.size (); --i >= 0;)
    {
        BasePlugin* plugin = plugins.getUnchecked (i);
        if (plugin->getUniqueHash () == hash)
            return plugin;
    }

    return 0;
}

//==============================================================================
void Host::addPlugin (BasePlugin* plugin)
{
    if (plugin)
    {
        DBG ("Host::addPlugin");

        // add plugin to the list
        plugins.add (plugin);
    }
}

//==============================================================================
BasePlugin* Host::loadPlugin (const File& pluginFile)
{
    DBG ("Host::loadPlugin");

    // vst hosting a new plugin
    BasePlugin* plugin = PluginLoader::getFromFile (pluginFile);

    if (plugin)
    {
        // prepare plugin
        openPlugin (plugin);

        printf ("Plugin %s loaded OK \n", (const char*) pluginFile.getFullPathName());
    }
    else
    {
        printf ("Plugin %s could not be loaded \n", (const char*) pluginFile.getFullPathName());
    }

    return plugin;
}

//==============================================================================
void Host::changePluginAudioGraph (ProcessingGraph* newAudioGraph)
{
    DBG ("Host::changePluginAudioGraph");

    ProcessingGraph* oldAudioGraph = audioGraph;

    {
        const ScopedLock sl (owner->getCallbackLock());
        audioGraph = newAudioGraph;
    }

    if (oldAudioGraph)
        delete oldAudioGraph;

    // notify listeners        
    for (int i = 0; i < listeners.size (); i++)
        ((HostListener*) listeners.getUnchecked (i))->processingGraphChanged (this, audioGraph);
}

//==============================================================================
void Host::openPlugin (BasePlugin* plugin, const bool suspendAudio)
{
    if (plugin)
    {
        DBG ("Host::openPlugin");

        if (suspendAudio)
             owner->suspendProcessing (true);

        // make it a child, and allocate buffers
        plugin->setParentHost (owner);

        plugin->allocateBuffers (plugin->getNumInputs(),
                                 plugin->getNumOutputs(),
                                 plugin->getNumMidiInputs(),
                                 plugin->getNumMidiOutputs(),
                                 samplesPerBlock);

        plugin->setPlayConfigDetails (plugin->getNumInputs(),
                                      plugin->getNumOutputs(),
                                      sampleRate,
                                      samplesPerBlock);

        // try to open correctly the plugin
        plugin->prepareToPlay (sampleRate, samplesPerBlock);

        if (suspendAudio)
             owner->suspendProcessing (false);
             
        // notify listeners        
        for (int i = 0; i < listeners.size (); i++)
            ((HostListener*) listeners.getUnchecked (i))->pluginAdded (this, plugin);
    }
}

//==============================================================================
void Host::closePlugin (BasePlugin* plugin, const bool suspendAudio)
{
    if (plugin)
    {
        DBG ("Host::closePlugin");

        if (suspendAudio)
             owner->suspendProcessing (true);

        if (audioGraph)
            audioGraph->resetNodeData (plugin);

        // release resources and close plugin
        plugin->releaseResources ();
        plugins.removeObject (plugin, false);

        if (suspendAudio)
             owner->suspendProcessing (false);

        // notify listeners
        for (int i = 0; i < listeners.size (); i++)
            ((HostListener*) listeners.getUnchecked (i))->pluginRemoved (this, plugin);

       if (suspendAudio)
           delete plugin;
    }
}

//==============================================================================
void Host::closeAllPlugins (const bool suspendAudio)
{
    DBG ("Host::closeAllPlugins");

    if (suspendAudio)
        owner->suspendProcessing (true);

    // remove and close all plugins except i/o
    for (int i = plugins.size (); --i >= 0;)
    {
        BasePlugin* plugin = plugins.getUnchecked (i);

        if (plugin->getType() != JOST_PLUGINTYPE_INPUT
            && plugin->getType() != JOST_PLUGINTYPE_OUTPUT)
        {
           closePlugin (plugin, false);
        }
    }

    if (suspendAudio)
        owner->suspendProcessing (false);
}

//==============================================================================
void Host::prepareToPlay (double sampleRate_, int samplesPerBlock_)
{
    DBG ("Host::prepareToPlay");

    sampleRate = sampleRate_;
    samplesPerBlock = samplesPerBlock_;

    transport->prepareToPlay (sampleRate, samplesPerBlock);

    for (int i = 0; i < plugins.size (); i++)
    {
        BasePlugin* plugin = plugins.getUnchecked (i);
        if (plugin)
        {
            plugin->allocateBuffers (plugin->getNumInputs(),
                                     plugin->getNumOutputs(),
                                     plugin->getNumMidiInputs(),
                                     plugin->getNumMidiOutputs(),
                                     samplesPerBlock);

            plugin->setPlayConfigDetails (plugin->getNumInputs(),
                                          plugin->getNumOutputs(),
                                          sampleRate,
                                          samplesPerBlock);

            plugin->prepareToPlay (sampleRate, samplesPerBlock);
        }
    }
}

void Host::releaseResources()
{
    DBG ("Host::releaseResources");

    for (int i = 0; i < plugins.size (); i++)
        plugins.getUnchecked (i)->releaseResources ();

    transport->releaseResources ();
}

//==============================================================================
void Host::processBlock (AudioSampleBuffer& buffer,
                         MidiBuffer& midiMessages)
{
    int blockSamples = buffer.getNumSamples();
    int currentPluginType = JOST_PLUGINTYPE_INVALID;

     // handle incoming midi messages for SYNCHRONIZATION
    transport->processIncomingMidi (midiMessages);
    transport->processAudioPlayHead (owner->getPlayHead());

    // process midi for plugins
    for (int j = plugins.size (); --j >= 0;)
        plugins.getUnchecked (j)->clearMidiBuffers ();
    
    // process audio for plugins
    if (audioGraph)
    {
        for (int j = 0; j < audioGraph->getNodeCount (); j++)
        {
            ProcessingNode* node = audioGraph->getNode (j);
            currentPlugin = (BasePlugin*) node->getData ();
            
            if (! currentPlugin)
                continue;
            
            currentPluginType = currentPlugin->getType ();

            // handle logic of mapping i/o --
            AudioSampleBuffer* inBuffers = currentPlugin->getInputBuffers ();
            AudioSampleBuffer* outBuffers = currentPlugin->getOutputBuffers ();

            // process audio --
            if (currentPlugin->isBypass ()
                && ! (currentPluginType == JOST_PLUGINTYPE_INPUT
                      || currentPluginType == JOST_PLUGINTYPE_OUTPUT))
            {
                // bypass mode
                if (inBuffers && outBuffers && inBuffers->getNumChannels() > 0)
                {
                    for (int channel = 0; channel < outBuffers->getNumChannels(); ++channel)
                    {
                        outBuffers->copyFrom (channel,
                                              0,
                                              *inBuffers,
                                              jmin (channel, inBuffers->getNumChannels() - 1),
                                              0,
                                              blockSamples);
                    }
                }
            }
            else
            {
                currentPlugin->processBlock (buffer, midiMessages);

#if 0
                // this should be keep or not ? probably it will create problems
                // with the meters
                if (currentPluginType == JOST_PLUGINTYPE_OUTPUT)
                {
                    outBuffers->clear ();
                    outBuffers = 0;            
                }
#endif
            }

            if (outBuffers)
            {
                const float currentOutputGain = currentPlugin->getCurrentOutputGain ();
                const float desiredOutputGain = currentPlugin->isMuted() ? 0.0f
                                                                         : currentPlugin->getOutputGain ();

                // apply mixer gains --
                for (int i = currentPlugin->getNumOutputs (); --i >= 0;)
                {
                    outBuffers->applyGainRamp (i,
                                               0,
                                               blockSamples,
                                               currentOutputGain,
                                               desiredOutputGain);
                }

                currentPlugin->setCurrentOutputGain (desiredOutputGain);

                // process routing --
                for (int i = node->getLinksCount (JOST_LINKTYPE_AUDIO); --i >= 0;)
                {
                    ProcessingLink* link = node->getLink (JOST_LINKTYPE_AUDIO, i);
                    BasePlugin* destination = (BasePlugin*) link->destination->getData ();

                    if (destination)
                    {
                        AudioSampleBuffer* destBuffer = destination->getInputBuffers();
                        if (destBuffer)
                        {
                            destBuffer->addFrom (link->destinationPort,
                                                 0,
                                                 outBuffers->getSampleData (link->sourcePort),
                                                 blockSamples);
                        }
                    }
                }
            }

            // clear input buffers (avoid zipper noise, but can be optimized) --
            if (inBuffers)
                inBuffers->clear ();

            // copy over midi processing --    
            for (int i = node->getLinksCount (JOST_LINKTYPE_MIDI); --i >= 0;)
            {
                ProcessingLink* link = node->getLink (JOST_LINKTYPE_MIDI, i);
                BasePlugin* destination = (BasePlugin*) link->destination->getData ();

                if (destination)
                {
                    MidiBuffer* sourceBuffer = currentPlugin->getMidiBuffer (link->sourcePort);
                    MidiBuffer* destinationBuffer = destination->getMidiBuffer (link->destinationPort);
                    if (destinationBuffer && sourceBuffer)
                    {
                        destinationBuffer->addEvents (*sourceBuffer, 0, blockSamples, 0);
                    }
                }
            }
        } // for
    }

    currentPlugin = 0;

    // process transport
    transport->processBlock (blockSamples);
}

//==============================================================================
void Host::suspendProcessing (const bool suspend)
{
    DBG ("Host::suspendProcessing");

    owner->suspendProcessing (suspend);
}

//==============================================================================
void Host::addListener (HostListener* listener)
{
    listeners.addIfNotAlreadyThere (listener);
}

void Host::removeListener (HostListener* listener)
{
    listeners.removeValue (listener);
}

void Host::removeAllListeners ()
{
    listeners.clear ();
}

//==============================================================================
void Host::saveToXml (XmlElement* xml)
{
    xml->setAttribute (T("version"), JucePlugin_VersionCode);

    // save transport state
    XmlElement* trans = new XmlElement (T("transport"));
    transport->saveToXml (trans);
    xml->addChildElement (trans);

    // save plugins and connections
    for (int i = 0; i < plugins.size (); i++)
    {
        BasePlugin* plugin = plugins.getUnchecked (i);

        XmlElement* e = new XmlElement (T("plugin"));
        e->setAttribute (T("hash"), plugin->getUniqueHash());
        e->setAttribute (T("type"), plugin->getType());
        e->setAttribute (T("uniqueid"), plugin->getID());
        e->setAttribute (T("path"), plugin->getFile().getFullPathName());
        e->setAttribute (T("preset"), plugin->getCurrentProgram());

        // extended options
        XmlElement* ext = new XmlElement (T("options"));
        plugin->savePropertiesToXml (ext);
        e->addChildElement (ext);

        // current internal parameter state
        XmlElement* chunk = new XmlElement (T("state"));
        plugin->savePresetToXml (chunk);
        e->addChildElement (chunk);

        // add to main
        xml->addChildElement (e);
    }

    // save graph !
    saveGraphToXml (xml);
}

void Host::saveGraphToXml (XmlElement* xml)
{
    if (! audioGraph)
        return;

    // save audio routing
    XmlElement* audio = new XmlElement (T("audio"));
    for (int j = 0; j < audioGraph->getNodeCount (); j++)
    {
        ProcessingNode* node = audioGraph->getNode (j);
        BasePlugin* plugin = (BasePlugin*) node->getData ();

        XmlElement* audioPlugin = new XmlElement (T("plugin"));
        audioPlugin->setAttribute (T("hash"), plugin->getUniqueHash ());

        for (int i = 0; i < node->getLinksCount (JOST_LINKTYPE_AUDIO); i++)
        {
            ProcessingLink* link = node->getLink (JOST_LINKTYPE_AUDIO, i);

            XmlElement* wire = new XmlElement (T("wire"));
            wire->setAttribute (T("srcPort"), link->sourcePort);
            wire->setAttribute (T("dstPlugin"), ((BasePlugin*)link->destination->getData())->getUniqueHash());
            wire->setAttribute (T("dstPort"), link->destinationPort);
            audioPlugin->addChildElement (wire);
        }

        audio->addChildElement (audioPlugin);
    }
    xml->addChildElement (audio);

    // save midi routing
    XmlElement* midi = new XmlElement (T("midi"));
    for (int j = 0; j < audioGraph->getNodeCount (); j++)
    {
        ProcessingNode* node = audioGraph->getNode (j);
        BasePlugin* plugin = (BasePlugin*) node->getData ();

        XmlElement* midiPlugin = new XmlElement (T("plugin"));
        midiPlugin->setAttribute (T("hash"), plugin->getUniqueHash ());

        for (int i = 0; i < node->getLinksCount (JOST_LINKTYPE_MIDI); i++)
        {
            ProcessingLink* link = node->getLink (JOST_LINKTYPE_MIDI, i);

            XmlElement* wire = new XmlElement (T("wire"));
            wire->setAttribute (T("srcPort"), link->sourcePort);
            wire->setAttribute (T("dstPlugin"), ((BasePlugin*)link->destination->getData())->getUniqueHash());
            wire->setAttribute (T("dstPort"), link->destinationPort);
            midiPlugin->addChildElement (wire);
        }

        midi->addChildElement (midiPlugin);
    }
    xml->addChildElement (midi);
}

//==============================================================================
void Host::loadFromXml (XmlElement* xml)
{
    int version = xml->getIntAttribute (T("version"), -1);
    if (version < JucePlugin_VersionCode)
        printf ("Session made with a previous version of jost. "
                "Something may be broken... sorry for that! \n");

    // remove already added plugins
    closeAllPlugins (false);

    if (plugins.contains (inputPlugin));
        plugins.removeObject (inputPlugin, false);

    if (plugins.contains (outputPlugin));
        plugins.removeObject (outputPlugin, false);

    // load transport
    XmlElement* trans = xml->getChildByName (T("transport"));
    if (trans) transport->loadFromXml (trans);

    // start adding stuff
    Array<int> oldHash, newHash;
    ProcessingGraph* newAudioGraph = new ProcessingGraph ();

    forEachXmlChildElement (*xml, e)
    {
        if (e->hasTagName (T("plugin")))
        {
            // default vst values
            int pluginHash =  e->getIntAttribute (T("hash"), -1);
            int pluginUniqueType = e->getIntAttribute (T("type"), 0);
            int pluginUniqueID = e->getIntAttribute (T("uniqueid"), 0);
            String pluginPath = e->getStringAttribute (T("path"), String::empty);
            int pluginPreset = e->getIntAttribute (T("preset"), 0);

            // handle input plugin (hash is fixed between sessions)
            bool isExternalSharedLibrary = false;
            BasePlugin* plugin = PluginLoader::getFromTypeID (pluginUniqueType,
                                                              inputPlugin,
                                                              outputPlugin,
                                                              false,
                                                              0,
															  owner);
            if (plugin == 0)
            {
                plugin = PluginLoader::getFromFile (pluginPath == String::empty ? File::nonexistent
                                                                                : pluginPath);
                isExternalSharedLibrary = true;
            }

            if (plugin
                && ((isExternalSharedLibrary && plugin->getID() == pluginUniqueID) || true))
            {
                // extended options
                XmlElement* ext = e->getChildByName (T("options"));
                if (ext) plugin->loadPropertiesFromXml (ext);

                // add plugin (do not suspend processing)
                openPlugin (plugin, false);
                addPlugin (plugin);

                // XXX - is this needed here ?
                if (plugin->getNumPrograms() > 0)
                    plugin->setCurrentProgram (pluginPreset);

                // current preset
                XmlElement* state = e->getChildByName (T("state"));
                if (state) plugin->loadPresetFromXml (state);

                // add to the graph
                newAudioGraph->addNode (plugin);

                oldHash.add (pluginHash);
                newHash.add (plugin->getUniqueHash());

                printf ("Plugin %s loaded OK \n", (const char*) plugin->getName ());
            }
            else
            {
                printf ("Plugin %s could not be loaded \n", (const char*) pluginPath);

                deleteAndZero (plugin);
            }
        }
    }

    // load back graphs !
    loadGraphFromXml (xml, newAudioGraph, oldHash, newHash);

    // swap graphs !
    changePluginAudioGraph (newAudioGraph);
}

//==============================================================================
void Host::loadGraphFromXml (XmlElement* xml,
                             ProcessingGraph* newAudioGraph,
                             Array<int>& oldHash,
                             Array<int>& newHash)
{
    // restore audio wires
    XmlElement* audio = xml->getChildByName (T("audio"));
    if (audio)
    {
        forEachXmlChildElement (*audio, e)
        {
            if (e->hasTagName (T("plugin")))
            {
                int pluginHash = e->getIntAttribute (T("hash"), -1);
                BasePlugin* srcPlugin = getPluginByUniqueHash (newHash [oldHash.indexOf (pluginHash)]);

                forEachXmlChildElement (*e, wire)
                {
                    if (wire->hasTagName (T("wire")))
                    {
                        int srcPort = wire->getIntAttribute (T("srcPort"), -1);
                        int dstPort = wire->getIntAttribute (T("dstPort"), -1);
                        int destPluginHash = wire->getIntAttribute (T("dstPlugin"), -1);

                        BasePlugin* dstPlugin =
                            getPluginByUniqueHash (newHash [oldHash.indexOf (destPluginHash)]);
                        if (dstPlugin != 0 && srcPort >= 0 && dstPort >= 0)
                        {
                            newAudioGraph->connectTo (srcPlugin,
                                                      srcPort,
                                                      dstPlugin,
                                                      dstPort,
                                                      JOST_LINKTYPE_AUDIO);
                        }
                    }
                }
            }
        }
    }
    // end

    // restore midi wires
    XmlElement* midi = xml->getChildByName (T("midi"));
    if (midi)
    {
        forEachXmlChildElement (*midi, e)
        {
            if (e->hasTagName (T("plugin")))
            {
                int pluginHash = e->getIntAttribute (T("hash"), -1);
                BasePlugin* srcPlugin = getPluginByUniqueHash (newHash [oldHash.indexOf (pluginHash)]);

                forEachXmlChildElement (*e, wire)
                {
                    if (wire->hasTagName (T("wire")))
                    {
                        int srcPort = wire->getIntAttribute (T("srcPort"), -1);
                        int dstPort = wire->getIntAttribute (T("dstPort"), -1);
                        int destPluginHash = wire->getIntAttribute (T("dstPlugin"), -1);

                        BasePlugin* dstPlugin =
                            getPluginByUniqueHash (newHash [oldHash.indexOf (destPluginHash)]);
                        if (dstPlugin != 0 && srcPort >= 0 && dstPort >= 0)
                        {
                            newAudioGraph->connectTo (srcPlugin,
                                                      srcPort,
                                                      dstPlugin,
                                                      dstPort,
                                                      JOST_LINKTYPE_MIDI);
                        }
                    }
                }
            }
        }
    }
    // end
}

