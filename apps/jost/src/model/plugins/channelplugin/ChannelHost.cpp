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

#include "ChannelEditor.h"
#include "ChannelHost.h"
#include "../../../HostFilterBase.h"


//==============================================================================
ChannelHost::ChannelHost (HostFilterBase* owner_,
            const int maxNumInputChannels,
            const int maxNumOutputChannels,
			ChannelPlugin* plug_)
  : owner (owner_),
	plug (plug_),
    currentPlugin (0),
    audioGraph (0),
    sampleRate (44100.0),
    samplesPerBlock (512)
{
    DBG ("Host::Host");


    // create an empty audio processing graph
    audioGraph = new ProcessingGraph ();

    // add generic plugins
    addPlugin (inputPlugin = new ChannelInputPlugin (maxNumInputChannels, plug));
    addPlugin (outputPlugin = new ChannelOutputPlugin (maxNumOutputChannels));

		
	inputPlugin->setValue(PROP_GRAPHXPOS, 60);
	inputPlugin->setValue(PROP_GRAPHYPOS, 40);

	outputPlugin->setValue(PROP_GRAPHXPOS, 60);
	outputPlugin->setValue(PROP_GRAPHYPOS, 200);
	

}

ChannelHost::~ChannelHost()
{
    DBG ("ChannelHost::~ChannelHost");

    // free plugins
//    closeAllPlugins (false);
    plugins.clear (true);

    // remove listeners after
//    removeAllListeners ();

    // delete audio graph
    deleteAndZero (audioGraph);
}

//==============================================================================
BasePlugin* ChannelHost::getPluginByUniqueHash (const int hash) const
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
void ChannelHost::addPlugin (BasePlugin* plugin)
{
    if (plugin)
    {
        DBG ("ChannelHost::addPlugin");

        // add plugin to the list
        plugins.add (plugin);
    }
}

//==============================================================================
BasePlugin* ChannelHost::loadPlugin (const File& pluginFile)
{
    DBG ("ChannelHost::loadPlugin");

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
void ChannelHost::changePluginAudioGraph (ProcessingGraph* newAudioGraph)
{
    

    ProcessingGraph* oldAudioGraph = audioGraph;

    {
        const ScopedLock sl (owner->getCallbackLock());
        audioGraph = newAudioGraph;
    }

    if (oldAudioGraph)
        delete oldAudioGraph;

    // notify listeners        
    for (int i = 0; i < listeners.size (); i++)
        ((ChannelHostListener*) listeners.getUnchecked (i))->processingGraphChanged (this, audioGraph);

	DBG ("ChannelHost::changePluginAudioGraph");
}

//==============================================================================
void ChannelHost::openPlugin (BasePlugin* plugin, const bool suspendAudio)
{
    if (plugin)
    {
        DBG ("ChannelHost::openPlugin");

        if (suspendAudio)
             owner->suspendProcessing (true);
		//DBG (String(T("suspend")))

        // make it a child, and allocate buffers
        plugin->setParentHost (owner);

		//DBG (String(T("sethost")))

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
            ((ChannelHostListener*) listeners.getUnchecked (i))->pluginAdded (this, plugin);
    }
}

//==============================================================================
void ChannelHost::closePlugin (BasePlugin* plugin, const bool suspendAudio)
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
            ((ChannelHostListener*) listeners.getUnchecked (i))->pluginRemoved (this, plugin);

        delete plugin;
    }
}

//==============================================================================
void ChannelHost::closeAllPlugins (const bool suspendAudio)
{
    DBG ("ChannelHost::closeAllPlugins");

    if (suspendAudio)
        owner->suspendProcessing (true);

    // remove and close all plugins except i/o
    for (int i = plugins.size (); --i >= 0;)
    {
        BasePlugin* plugin = plugins.getUnchecked (i);

        if (plugin->getType() != JOST_PLUGINTYPE_CHANNELINPUT
            && plugin->getType() != JOST_PLUGINTYPE_CHANNELOUTPUT)
        {
           closePlugin (plugin, false);
        }
    }

    if (suspendAudio)
        owner->suspendProcessing (false);
}

//==============================================================================
void ChannelHost::prepareToPlay (double sampleRate_, int samplesPerBlock_)
{
    DBG ("ChannelHost::prepareToPlay");

    sampleRate = sampleRate_;
    samplesPerBlock = samplesPerBlock_;

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

void ChannelHost::releaseResources()
{
    DBG ("ChannelHost::releaseResources");

    for (int i = 0; i < plugins.size (); i++)
        plugins.getUnchecked (i)->releaseResources ();

}

//==============================================================================
void ChannelHost::processBlock (AudioSampleBuffer& buffer,
                         MidiBuffer& midiMessages)
{
    int blockSamples = buffer.getNumSamples();
    int currentPluginType = JOST_PLUGINTYPE_INVALID;

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
                && ! (currentPluginType == JOST_PLUGINTYPE_CHANNELINPUT
                      || currentPluginType == JOST_PLUGINTYPE_CHANNELOUTPUT))
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

				
              /*  if (currentPluginType == JOST_PLUGINTYPE_CHANNELOUTPUT)
                {
                    outBuffers->clear ();
                    outBuffers = 0;            
                }*/
            }

            if (outBuffers)
            {
				
				currentPlugin->setCurrentOutputGain (1.0f);

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

}

//==============================================================================
void ChannelHost::suspendProcessing (const bool suspend)
{
    DBG ("ChannelHost::suspendProcessing");

    owner->suspendProcessing (suspend);
}

//==============================================================================
void ChannelHost::addListener (ChannelHostListener* listener)
{
    listeners.addIfNotAlreadyThere (listener);
}

void ChannelHost::removeListener (ChannelHostListener* listener)
{
    listeners.removeValue (listener);
}

void ChannelHost::removeAllListeners ()
{
    listeners.clear ();
}

//==============================================================================
void ChannelHost::saveToXml (XmlElement* xml)
{

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

void ChannelHost::saveGraphToXml (XmlElement* xml)
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
void ChannelHost::loadFromXml (XmlElement* xml)
{
	// remove already added plugins
    closeAllPlugins (false);

    if (plugins.contains (inputPlugin));
        plugins.removeObject (inputPlugin, false);

    if (plugins.contains (outputPlugin));
        plugins.removeObject (outputPlugin, false);

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
                                                              true,
                                                              plug,
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
void ChannelHost::loadGraphFromXml (XmlElement* xml,
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

