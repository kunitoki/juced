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

#ifndef __JOST_CONFIG_HEADER__
#define __JOST_CONFIG_HEADER__

#include "StandardHeader.h"
#include "JucePluginCharacteristics.h"
#include "ui/lookandfeel/ColourScheme.h"


//==============================================================================
/**
    These are the MACROS global to the whole application
*/

// config files paths
#define JOST_CONFIG_DIRECTORY               T(".jost")
#define JOST_CONFIG_FILENAME                T("default")
#define JOST_CONFIG_EXTENSION               T("conf")
#define JOST_COLOR_SCHEME_PATH              T("~/.jost/colourscheme.conf")
#define JOST_BOOKMARK_PATH                  T("~/.jost/bookmarks.conf")

// preset configuration
#define JOST_PRESET_TRACKTAG                T("track")
#define JOST_PRESET_PLUGINTAG               T("plugin")
#define JOST_PRESET_SESSIONTAG              T("session")
#define JOST_PRESET_PRESETTAG               T("preset")
#define JOST_PRESET_COMPRESSION             0
#define JOST_PRESET_ENCODE                  0

#define JOST_BOOKMARK_TAG                   T("bookmark")
#define JOST_BOOKMARK_SESSIONTAG            T("session")
#define JOST_BOOKMARK_PLUGINTAG             T("plugin")
#define JOST_BOOKMARK_PRESETTAG             T("preset")

// common extensions
#if defined(JUCE_LINUX)
  #define JOST_PLUGIN_EXTENSION             T(".so")
  #define JOST_PLUGIN_WILDCARD              T("*.so")
#elif defined (JUCE_WIN32)
  #define JOST_PLUGIN_EXTENSION             T(".dll")
  #define JOST_PLUGIN_WILDCARD              T("*.dll")
#elif defined (JUCE_MAC)
  #define JOST_PLUGIN_EXTENSION             T(".*")
  #define JOST_PLUGIN_WILDCARD              T("*.*")
#endif

#ifdef JUCE_MAC
 #define JOST_USE_NATIVE_FILE_CHOOSER       true

#elif JUCE_WIN32
 #define JOST_USE_NATIVE_FILE_CHOOSER       true
#else

 #define JOST_USE_NATIVE_FILE_CHOOSER       false
#endif 

#define JOST_SESSION_EXTENSION              T(".jxs")
#define JOST_SESSION_WILDCARD               T("*.jxs")
#define JOST_PRESET_EXTENSION               T(".jxp")
#define JOST_PRESET_WILDCARD                T("*.jxp")
#define JOST_MIDI_WILDCARD                  T("*.mid;*.midi")

// available connection types
#define JOST_LINKTYPE_AUDIO                 0
#define JOST_LINKTYPE_MIDI                  1
#define JOST_LINKTYPE_CONTROL               2
#define JOST_LINKTYPE_SPECTRA               3

// internal plugin hash definitions
#define JOST_PLUGINTYPE_INVALID             0
#define JOST_PLUGINTYPE_INPUT               1
#define JOST_PLUGINTYPE_OUTPUT              2
#define JOST_PLUGINTYPE_MIDIIN              3
#define JOST_PLUGINTYPE_MIDIOUT             4
#define JOST_PLUGINTYPE_MIDISEQ             5
#define JOST_PLUGINTYPE_MIDIKEY             6
#define JOST_PLUGINTYPE_MIDIMONITOR         7
#define JOST_PLUGINTYPE_MIDIFILTER          8
#define JOST_PLUGINTYPE_MIDIPADS            9
#define JOST_PLUGINTYPE_AUDIOSPECMETER      51
#define JOST_PLUGINTYPE_OVERDOSE	        52
#define JOST_PLUGINTYPE_DETUNER		        53
#define JOST_PLUGINTYPE_OPPRESSOR		    54
#define JOST_PLUGINTYPE_CHANNEL             90
#define JOST_PLUGINTYPE_CHANNELSTEREO       91
#define JOST_PLUGINTYPE_CHANNELINPUT        92
#define JOST_PLUGINTYPE_CHANNELOUTPUT       93
#define JOST_PLUGINTYPE_TRACK               94
#define JOST_PLUGINTYPE_VST                 101
#define JOST_PLUGINTYPE_LADSPA              102
#define JOST_PLUGINTYPE_DSSI                103

// graph component GUI defines
#define JOST_GRAPH_NODE_WIDTH               64
#define JOST_GRAPH_NODE_HEIGHT              22

// generic gui defines
#define JOST_DEFAULT_TAB_HEIGHT             24
#define JOST_DEFAULT_MENU_HEIGHT            19
#define JOST_DEFAULT_TOOLBAR_HEIGHT         24

// technology use
#ifndef JOST_USE_JACKBRIDGE
 #define JOST_USE_JACKBRIDGE                0
#endif

#ifndef JOST_USE_VST
 #define JOST_USE_VST                       0
#endif

#ifndef JOST_USE_LADSPA
 #define JOST_USE_LADSPA                    0
#endif

#ifndef JOST_USE_DSSI
 #define JOST_USE_DSSI                      0
#endif

#ifndef JOST_USE_LASH
 #define JOST_USE_LASH                      0
#endif

#ifndef JOST_USE_SURFACE
 #define JOST_USE_SURFACE                   1
#endif

//==============================================================================
/**
    Forward declarations: this will save from typing classes
*/
class BasePlugin;
class PluginLoader;
class Host;
class Transport;
class HostFilterBase;
class HostFilterComponent;
class ChannelHost;
class ChannelPlugin;
class ChannelEditor;


//==============================================================================
/**
    Singleton global class for handling properties common to the
    whole application. To use this, just get its instance and access
    its member directly
*/
class Config
{
public:

    //==============================================================================
    /** Constructor */
    Config ();

    /** Destructor */
    ~Config ();

    //==============================================================================
    /** You can access these directly */

    /** Recent plugins directory and files list */
    RecentlyOpenedFilesList recentPlugins;
    File lastPluginDirectory;

    /** Recent session state directory and files list */
    RecentlyOpenedFilesList recentSessions;
    File lastSessionDirectory;

    /** Recent preset directory */
    File lastPresetDirectory;

    /** Audio properties */
    bool externalTempoSync;
    bool externalTempoMaster;
    bool autoConnectInputs;
    bool autoConnectOutputs;

    /** Visual properties / Colour scheme */
    Rectangle mainWindowBounds;
    String toolbarSet;
    bool showTooltips;
    bool graphLeftToRight;
    int defaultTabThickness;
    File colourSchemeFile;

    /** Browser info */
    bool showBrowser;
    bool browserLeft;
    int browserLastOpenPage;
    File lastBrowsedDirectory;

    /** First time & process info */
    bool firstTime;
    bool realTime;

    //==============================================================================
    void addRecentPlugin (const File& file);
    void addRecentSession (const File& file);
    void addRecentPreset (const File& file);

    //==============================================================================
    Colour getColour (const String& name, const Colour& defColour = Colours::white) const;
    void setColour (const String& name, const Colour& newColour);

    //==============================================================================
    /** This will open  */
    void open ();

    /** This will close */
    void close ();

    /** This will read the file */
    void read ();

    /** This will ensure the file is written out */
    void write ();

    //==============================================================================
    /** Singleton declaration */
    juce_DeclareSingleton (Config, false)

protected:

    /** @internal */
    PropertySet* getGlobalSettings();

    /** The colour scheme */
    ColourScheme* scheme;
};



#endif // __JOST_CONFIG_HEADER__
