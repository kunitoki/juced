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

#ifndef __JUCETICE_JOSTPLUGINLOADER_HEADER__
#define __JUCETICE_JOSTPLUGINLOADER_HEADER__

#include "../Config.h"
#include "../Commands.h"

#include "BasePlugin.h"

#include "plugins/InputPlugin.h"
#include "plugins/OutputPlugin.h"

#include "plugins/ChannelInputPlugin.h"
#include "plugins/ChannelOutputPlugin.h"
#include "plugins/TrackPlugin.h"

#include "plugins/midiplugins/MidiInputPlugin.h"
#include "plugins/midiplugins/MidiOutputPlugin.h"
#include "plugins/midiplugins/MidiSequencePlugin.h"
#include "plugins/midiplugins/MidiKeyboardPlugin.h"
#include "plugins/midiplugins/MidiMonitorPlugin.h"
#include "plugins/midiplugins/MidiFilterPlugin.h"
#include "plugins/midiplugins/MidiPads.h"

#include "plugins/meters/AudioSpecMeterPlugin.h"

#include "plugins/effects/OverdosePlugin.h"
#include "plugins/effects/DetunerPlugin.h"
#include "plugins/effects/OppressorPlugin.h"

#include "plugins/channelplugin/ChannelPlugin.h"

#include "plugins/VstPlugin.h"
#include "plugins/LadspaPlugin.h"
#include "plugins/DssiPlugin.h"


//==============================================================================
/**
    Plugin loader class. It will try to load each plugin type in series,
    returning the first plugin technology it is able to open.
*/
class PluginLoader
{
public:

    //==============================================================================
    /** Try to see if we can load the file as a plugin

        This method will try to load the file, managing to check if is one
        of the known plugin type

        @param file     the file to try to load
        @returns        true if it can load it, false otherwise.
    */
    static bool canUnderstand (const File& file);

    //==============================================================================
    /** Loads a plugin from a file

        This method will try to load the file, managing to check if is one
        of the known plugin type, and return it.

        @param file     the file to try to load
        @returns        the plugin, or null if it there was an error loading it
    */
    static BasePlugin* getFromFile (const File& file);

    //==============================================================================
    /** Loads an internal plugin based on type ID

        This method will try to load the intern plugin

        @param typeID   the internal type id
        @returns        the plugin, or null if it there was an error loading it
    */
    static BasePlugin* getFromTypeID (const int typeID,
                                      BasePlugin* inputPlugin,
                                      BasePlugin* outputPlugin,
                                      const bool subChannelPlugin = false,
                                      ChannelPlugin* plug = 0,
									  HostFilterBase* base = 0);

    /** Loads an internal plugin from a popup menu selector

        This method will try to load the intern plugin

        @param typeID   the internal type id
        @returns        the plugin, or null if it there was an error loading it
    */
    static BasePlugin* handlePopupMenu (const bool subChannelPlugin = false,
                                         ChannelPlugin* plug = 0,
                                         HostFilterBase* base = 0);

};


#endif // __JUCETICE_JOSTPLUGINLOADER_HEADER__
