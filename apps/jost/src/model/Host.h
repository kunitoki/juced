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

#ifndef __JUCETICE_JOSTHOST_HEADER__
#define __JUCETICE_JOSTHOST_HEADER__

#include "../Config.h"
#include "../Commands.h"
#include "ProcessingGraph.h"
#include "PluginLoader.h"
#include "Transport.h"


//==============================================================================
/**
    This will let you register some callbacks with the current host
*/
class HostListener
{
public:

    virtual ~HostListener () {}

    /** This will be called when the processing graph changes for any reason */
    virtual  void processingGraphChanged (Host* host, ProcessingGraph* audioGraph) = 0;

    /** This will be called when a new plugin is added to the graph */
    virtual  void pluginAdded (Host* host, BasePlugin* plugin) = 0;

    /** This will be called when a new plugin is removed from the graph */
    virtual  void pluginRemoved (Host* host, BasePlugin* plugin) = 0;

protected:

    HostListener () {}
};


//==============================================================================
/**
    The main host processing.

    It holds plugins and dispatch callbacks between them. It is the centre of
    Jost, as it do a lot of underground work trying to handle plugins with
    different technologies and considering them a single sort of them.

    You will mainly have a single host, since it will process the Transport
    singleton along with the plugins, and have 2 hosts touching directly
    the shared transport is a bad thing.

    @see Transport

*/
class Host
{
public:

    //==============================================================================
    /** Host constructor */
    Host (HostFilterBase* owner,
          const int maxNumInputChannels,
          const int maxNumOutputChannels);

    /** Destructor */
    ~Host ();

    //==============================================================================
    /** This is called when the host is first activated, and before the callback */
    void prepareToPlay (double sampleRate, int samplesPerBlock);

    /** Called when the host is released: the audio setup is reset or changed */
    void releaseResources();

    /** This is the audio/midi callback.

        You will process audio and midi, calling every loaded effect.
    */
    void processBlock (AudioSampleBuffer& buffer,
                       MidiBuffer& midiMessages);

    //==============================================================================
    void suspendProcessing (const bool shouldBeSuspended);

    //==============================================================================
    /** Get a plugin from the host

        It will return 0 if there is no plugin at the index specified
    */
    BasePlugin* getPluginByIndex (const int index) const { return plugins [index]; }

    /** Get a plugin from the host

        It will return 0 if there is no plugin at the index specified
    */
    BasePlugin* getPluginByUniqueHash (const int hash) const;

    //==============================================================================
    /** Return the current plugin that is processing */
    BasePlugin* getCurrentProcessingPlugin () const      { return currentPlugin; }

    //==============================================================================
    /** Get the total number of plugins for this host

        It will return 0 if there is no plugin at the index specified
    */
    int getPluginsCount () const                         { return plugins.size (); }

    //==============================================================================
    /** Add a plugin to the end of the host processing chain

        This will add the plugin after already added plugins

        @see closePlugin
    */
    void addPlugin (BasePlugin* plugin);

    /** Open a plugin

        This will only call the initial functions and set initial
        samplerate and blocksize

        @see closePlugin
    */
    void openPlugin (BasePlugin* plugin, const bool suspendAudio = false);

    /** Close a plugin registered with the host

        This will also free any previously allocated plugin buffers.
        Internal input / output plugins will not be freed !

        @see addPlugin
    */
    void closePlugin (BasePlugin* plugin, const bool suspendAudio = true);

    /** Close all plugins registered with the host

        This will free every plugin currently playing, apart
        from in / out plugins !
    */
    void closeAllPlugins (const bool suspendAudio = true);

    //==============================================================================
    /** Try to load a plugin given a string with the absolute path

        It will returns 0 if it wasn't successful. Otherwise if the plugin
        is a valid plugin, it will be opened and the internal buffers
        will be allocated regarding how many inputs/outputs the plugin have.

        Remember that plugin will not be added to the internal array !

        @see allocateBuffers
    */
    BasePlugin* loadPlugin (const File& pluginFile);

    //==============================================================================
    /** This changes the AUDIO processing order of the plugins

        It takes as input an array of integers which are the unique hash
        that represent every plugin.
    */
    void changePluginAudioGraph (ProcessingGraph* newAudioGraph);

    //==============================================================================
    /** Returns the current audio graph */
    ProcessingGraph* getAudioGraph () const            { return audioGraph; }

    //==============================================================================
    /** Add a listener to this host */
    void addListener (HostListener* listener);

    /** Remove a previously registered listener */
    void removeListener (HostListener* listener);
    
    /** Clear all listeners from this host */
    void removeAllListeners ();

    //==============================================================================
    /** Serialize host to an Xml element */
    void saveToXml (XmlElement* element);

    /** Deserialize host from an Xml element */
    void loadFromXml (XmlElement* element);

private:

    //==============================================================================
    void saveGraphToXml (XmlElement* element);
    void loadGraphFromXml (XmlElement* element,
                           ProcessingGraph* newAudioGraph,
                           Array<int>& oldHash,
                           Array<int>& newHash);

    //==============================================================================
    // host holder
    HostFilterBase* owner;

    // main host transport
    Transport* transport;

    // host plugins
    InputPlugin* inputPlugin;
    OutputPlugin* outputPlugin;
    OwnedArray<BasePlugin> plugins;
    BasePlugin* currentPlugin;

    ProcessingGraph* audioGraph;

    VoidArray listeners;

    double sampleRate;
    int samplesPerBlock;

    Host (const Host&);
    const Host& operator= (const Host&);
};


#endif // __JUCETICE_JOSTHOST_HEADER__
