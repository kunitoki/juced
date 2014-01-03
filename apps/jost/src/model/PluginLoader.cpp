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

#include "PluginLoader.h"


//==============================================================================
bool PluginLoader::canUnderstand (const File& file)
{
    DBG ("PluginLoader::canUnderstand");

    if (! file.exists ())
    {
        printf ("Plugin %s doesn't exists on disk !", (const char*) file.getFullPathName ());
        return false;
    }

    // try with VST
#if JOST_USE_VST
    {
        VstPlugin* loadedPlugin = new VstPlugin ();
        bool loadedOk = loadedPlugin->loadPluginFromFile (file);
        
        if (loadedOk)
        {
            deleteAndZero (loadedPlugin);
            return true;
        }
        
        deleteAndZero (loadedPlugin);
    }
#endif

    // try with DSSI
#if JOST_USE_DSSI
    {
        DssiPlugin* loadedPlugin = new DssiPlugin ();
        bool loadedOk = loadedPlugin->loadPluginFromFile (file);
        
        if (loadedOk)
        {
            deleteAndZero (loadedPlugin);
            return true;
        }
        
        deleteAndZero (loadedPlugin);
    }
#endif

    // try with LADSPA
#if JOST_USE_LADSPA
    {
        LadspaPlugin* loadedPlugin = new LadspaPlugin ();
        bool loadedOk = loadedPlugin->loadPluginFromFile (file);
        
        if (loadedOk)
        {
            deleteAndZero (loadedPlugin);
            return true;
        }
        
        deleteAndZero (loadedPlugin);
    }
#endif

    return false;
}

//==============================================================================
BasePlugin* PluginLoader::getFromFile (const File& file)
{
    DBG ("PluginLoader::getFromFile");

    BasePlugin* loadedPlugin = 0;

    if (! file.exists ())
    {
        printf ("Plugin %s doesn't exists on disk !", (const char*) file.getFullPathName ());
        return loadedPlugin;
    }

    // try with VST
#if JOST_USE_VST
    {
        loadedPlugin = new VstPlugin ();
        if (loadedPlugin->loadPluginFromFile (file))
            return loadedPlugin;
        deleteAndZero (loadedPlugin);
    }
#endif

    // try with DSSI
#if JOST_USE_DSSI
    {
        loadedPlugin = new DssiPlugin ();
        if (loadedPlugin->loadPluginFromFile (file))
            return loadedPlugin;
        deleteAndZero (loadedPlugin);
    }
#endif

    // try with LADSPA
#if JOST_USE_LADSPA
    {
        loadedPlugin = new LadspaPlugin ();
        if (loadedPlugin->loadPluginFromFile (file))
            return loadedPlugin;
        deleteAndZero (loadedPlugin);
    }
#endif

    return 0;
}

//==============================================================================
BasePlugin* PluginLoader::getFromTypeID (const int typeID,
                                         BasePlugin* inputPlugin,
                                         BasePlugin* outputPlugin,
                                         const bool subChannelPlugin,
                                         ChannelPlugin* plug,
										 HostFilterBase* base)
{
    DBG ("PluginLoader::getFromTypeID");
    
    if (subChannelPlugin)
    {
        switch (typeID)
        {
        case JOST_PLUGINTYPE_CHANNELINPUT:
			return new ChannelInputPlugin(inputPlugin->getNumOutputChannels(), plug);
        case JOST_PLUGINTYPE_CHANNELOUTPUT:
            return new ChannelOutputPlugin(outputPlugin->getNumInputChannels());
	    case JOST_PLUGINTYPE_TRACK:
            return new TrackPlugin (1);
        }
    }
    else
    {
        switch (typeID)
        {
        case JOST_PLUGINTYPE_INPUT:
            return inputPlugin;
        case JOST_PLUGINTYPE_OUTPUT:
            return outputPlugin;
        case JOST_PLUGINTYPE_MIDIIN:
            return new MidiInputPlugin (0);
        case JOST_PLUGINTYPE_MIDIOUT:
            return new MidiOutputPlugin (0);
        }
    }
    
    switch (typeID)
    {
    case JOST_PLUGINTYPE_MIDISEQ:
        return new MidiSequencePlugin ();
    case JOST_PLUGINTYPE_MIDIKEY:
        return new MidiKeyboardPlugin ();
    case JOST_PLUGINTYPE_MIDIMONITOR:
        return new MidiMonitorPlugin ();
    case JOST_PLUGINTYPE_MIDIFILTER:
        return new MidiFilterPlugin ();
    case JOST_PLUGINTYPE_MIDIPADS:
        return new MidiPadsPlugin ();
    case JOST_PLUGINTYPE_AUDIOSPECMETER:
        return new AudioSpecMeterPlugin ();
	case JOST_PLUGINTYPE_OVERDOSE:
        return new OverdosePlugin ();
	case JOST_PLUGINTYPE_DETUNER:
        return new DetunerPlugin ();
	case JOST_PLUGINTYPE_OPPRESSOR:
        return new OppressorPlugin ();
	case JOST_PLUGINTYPE_CHANNEL:
        return new ChannelPlugin (1, base);
	case JOST_PLUGINTYPE_CHANNELSTEREO:
        return new ChannelPlugin (2, base);
    case JOST_PLUGINTYPE_VST:
    case JOST_PLUGINTYPE_LADSPA:
    case JOST_PLUGINTYPE_DSSI:
        break;
    default:
        jassertfalse
        // You are trying to instantiate an internal plugin which doesn't exist !
        // Probably you have not keep in sync this function with handlePopupMenu one...
        break;
    }
    
    return 0;
}

//==============================================================================
BasePlugin* PluginLoader::handlePopupMenu (const bool subChannelPlugin,
                                           ChannelPlugin* plug,
                                           HostFilterBase* base)
{
    DBG ("PluginLoader::handlePopupMenu");

    PopupMenu menu;
    PopupMenu midiMenu;
    PopupMenu audioMenu;

    {
        if (!subChannelPlugin)
        {
            midiMenu.addItem (JOST_PLUGINTYPE_MIDIIN,      "Input");
            midiMenu.addItem (JOST_PLUGINTYPE_MIDIOUT,     "Output");
        }

        midiMenu.addItem (JOST_PLUGINTYPE_MIDISEQ,         "Sequencer");
        midiMenu.addItem (JOST_PLUGINTYPE_MIDIKEY,         "Controller");
        midiMenu.addItem (JOST_PLUGINTYPE_MIDIPADS,        "Pads");
        midiMenu.addItem (JOST_PLUGINTYPE_MIDIFILTER,      "Filter");
        midiMenu.addItem (JOST_PLUGINTYPE_MIDIMONITOR,     "Monitor");
    }

    {
        if (!subChannelPlugin)
        {
            audioMenu.addItem (JOST_PLUGINTYPE_CHANNEL,       "Mono Channel");
	        audioMenu.addItem (JOST_PLUGINTYPE_CHANNELSTEREO, "Stereo Channel");
        }

        PopupMenu effectsMenu;
	    effectsMenu.addItem (JOST_PLUGINTYPE_DETUNER,		"Detuner");
	    effectsMenu.addItem (JOST_PLUGINTYPE_OPPRESSOR,	    "Oppressor");
	    effectsMenu.addItem (JOST_PLUGINTYPE_OVERDOSE,		"Overdose");
        audioMenu.addSubMenu("Effects", effectsMenu);

        PopupMenu metersMenu;
	    metersMenu.addItem (JOST_PLUGINTYPE_AUDIOSPECMETER, "Meter");
        audioMenu.addSubMenu("Meters", metersMenu);
    }

    menu.addSubMenu("Midi", midiMenu);
    menu.addSubMenu("Audio", audioMenu);

    BasePlugin* plugin = 0;

    const int result = menu.show();
    if (result)
    {
        plugin = PluginLoader::getFromTypeID (result, 0, 0, subChannelPlugin, plug, base);
    }
        
    return plugin;
}

