JUCETICE / JOST v0.5.4 / multi-technology audio host for native plugins on linux

Copyright (C) 2008 kRAkEn/gORe (www.anticore.org/jucetice)


-------------------------------------------------------------------------------------------
Informations ------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------

JOST is a audio host application for plugins that can be used as plugin itself, or be
compiled as a cross bridge between multiple audio plugin technologies...
It is the first open source multi-technology (internal, native vst, ladspa, dssi) host in
linux. It will mainly host a chain of plugins per instance, publishing jack, alsa and
alsa_seq ports in order to be connected in your main stream flow. It is actually under
heavy development, but it still have some very good features that makes it a first class
host.

Started in middle feb 2007 by Lucio Asnaghi a.k.a. kRAkEn/gORe, is written completely
in C++ (with a bit of C) using the JUCE framework (www.rawmaterialsoftware.com/juce).

Features:

- modular design with routable audio/midi flows
- audio routing to/from JACK or ALSA
- can sync to MIDI with the start/stop/continue events (i.e. from seq24)
- can load native VST, LADSPA, DSSI plugins
- support for GUI plugins
- midi learn for plugins parameters
- mixer with one channel strip for each plugin and mute-bypass buttons
- audio meter plugin with peak, rms and octave spectrum
- midi sequencer with recording
- midi processors: monitor, filter, controller, pads
- internal disk browser with bookmarks support
- session state load / save with auomatic recall of last session
- colour scheme support


-------------------------------------------------------------------------------------------
Changelog ---------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------

[2009-05-xx] - 0.5.5
+ added windows build (thanx Domenic Tihanyi aka spankache)
+ added macosx build (thanx Rui Haszard Morris aka haszari)
+ aligned to latest juce in svn repository
+ added editing for midi CC to the midi sequencer plugin
+ added oppressor, detuner and overdose plugins
+ added channel plugins for sub channel graphs
+ added a basic midi CC editor in the midi sequencer internal plugin 
~ fixed mouse cursor not set correctly when dragging the graph component
~ take the drop position when dragging plugins from the bookmarks

[2008-12-02] - 0.5.4
~ fixed a problem in compilation step

[2008-11-30] - 0.5.3
+ added midi learn for each slider in plugins (right click from internal editor)
+ added ability to select which midi CC is automating the slider directly from a menu
+ added midi CC for automation recorded with the session
+ main graph is bigger and inside a viewport so the currently modular area is bigger
+ added a viewport navigator for the main graph besides the browser
+ added colour selector for nodes in modular
+ added middle click navigation in the modular view
+ added a simple midi filter plugin (should be improved)
+ added a midi controller plugin (should be improved)
~ selecting and moving more than one object in the modular view is now possible
~ fixed a problem with locking of plugins in the modular area
~ plugins in modular view now are limited to the main area so you can't drag off the component
~ changed plugin window handling (may rewrite this completely later on)
~ fixed a problem in plugin window menu (first window only responded to commands)
~ rewrote parameter manager update mechanism (no more memory allocations in realtime thread)
~ changed the slider in the plugin parameters window
~ fixed a problem when saving presets with midipads
~ tweaked to make it compile and run with gcc 4.3.2

[2008-11-05] - 0.5.2
~ fixed a problem in AudioDeviceSelectorComponent (thanx Dave !)
~ the window was not more resizable (thanx Dave !)

[2008-11-03] - 0.5.1
~ fixed a problem introduced with newer JUCE (AudioSampleBuffer segfault) (thanx Dave !)

[2008-10-29] - 0.5.0
+ aligned to latest juce in svn repository
+ added juce_amalgamated instead of libjuce to improve build time (and to favour gcc optimizations)
+ added initial ALSA support besides JACK
+ added a device selection window (alsa, jack) with output selection (and buffersize)
+ added plugin MIDIPADS courtesy by ThePiz (http://www.thepiz.org/) !
+ added a midi monitor plugin
+ added an audio meter (gain/spectrum) plugin
+ added lasso component to select plugins (still moving plugins with mouse is not implemented)
~ fixed plugin version to work with QTractor (latest cvs) and Renoise (i hope finally...)
~ fixed lash support (still disabled by default but can be enabled using premake)
~ fixed a couple of asserts in midi output code
~ cleaned a bit the internal host handling of the selected plugins
~ cleaned the GUI plugin window managed by the host (may experience problems on some plugins)
~ fixed the menu option New session was not present
~ improved makefiles, while still using premake (runpremake --help to see the options)
- zapped the options panel from the plugins window and placed a "options" menu instead
- disabled jackbridge for 32<>64 bit, until i write it as a specific JUCE's AudioDevice
- disabled external jack sync, until it will be supported in JUCE's AudioDeviceManager

[2008-02-29] - 0.4.6
+ added a jost icon for use in your desktop or menus
~ fixed 32bit version in makefile

[2008-02-28] - 0.4.5
+ added jostbridge to connect to jack64bit from a 32bit binary (thanx drumfix)
+ added auto_connect_inputs/outputs in config file for automatic jack port connection
+ added more debug messages to spot problems (obviously only in debug mode) 
~ fixed in some cases there were artifacts on audio when swapping the audio graph
~ fixed no more application close when you shutdown the jack process while jost is running
~ now less jack process zombified when jost exits
~ lowered a bit the number of inputs/outputs to favour overall speed
~ fixed problems with dssi plugins (namely whysynth, wsynth and others) and dssi-gui support is under testing
~ fixed problems loading ladspas with high number of parameters
~ changed the way the scrollbars are drawn, because the old style was causing an assert hit in my pc
~ improved look and feel buttons colour
- OSC support have been removed (not working after 0.2.3), but it will be reorganized back in the future... 

[2008-02-15] - 0.4.4
+ reorganized a bit the internal handling of classes. no more singletons (plugin mode will work, see below)
+ added the VST plugin version (works in jost itself !!! also in energyXT2, renoise who knows why it doesn't?)
+ added bar/beat/ticks info on the toolbar
+ now jucetice is compiled as an external standalone library
+ added plugin/loop/buttons to toolbar
+ added facilities to configure/compile it with fewer commands
~ improved a bit the vst plugins initialization/deinitialization stuff
~ constantly aligning every plugin instance to juce AudioProcessor
~ now trying to lower a bit priority of the gui to favour audio thread
~ fixed problem with ladspa plugins not loading back session state (thanx kokoko3k)
~ spotted a bug of a dangling pointer when deallocating the command manager in the editor
~ changed the default icon/colour theme
- removed lash dependancy (off by default)
- disabled osc support (via #define but isn't tested)

[2007-11-18] - 0.4.3
+ aligned to latest changes of juce (svn trunk)
+ added "add" button to bookmarks
~ now keyboard shortcuts (visible in menus) work as expected
~ improved ability of reordering bookmarks
~ fixed a bug with midi plugins (using sendVstEventsToHost was discarding events) 
~ improved behaviour of popup menu over connectors
~ improved paint of connectors pin (thanx Jules !)

[2007-11-04] - 0.4.2
+ aligned to latest changes in AudioProcessor class in juce 1.45 (svn trunk)
+ added mute and bypass toggle button to the mixer
+ changed default meter colours (and updated them in the default scheme)
+ added right click submenu for meter and opening plugin editor
+ added right click load plugin in modular view (still no bookmarks shown in that anyway)
+ added (an untested and disabled by default) initial lash support
+ added ability to drag a session file over the graph (previously you can only drag plugins)
~ meter now working ok in output plugin
~ regression to normal priority by default (RT-mode was causing more xruns when using set_rlimits or pam)
~ fixed a bug with right click menu checked values in channel strip
~ fixed a nasty plugin order initialization bug introduced with last version
~ now the plugin gain is saved with its presets as it should
~ added a tick to the "Lock" property in the popup menu of the graph component
~ plugins windows stay always on top, but must be a per plugin configuration

[2007-07-31] - 0.4.1
+ added dynamic mixer with settable label and width (double click)
+ added decibel scale to mixer strip
+ added selectable peak / rms meter to mixer strip
+ added force realtime priority if selected in config file. turn it on if you have problems in certain situations
+ changed the default graph direction from top to bottom to save space
~ added a couple of checks in audio loops for safe guard plugin removal
~ fixed a segfault when removing a playing plugin from the new audio graph classes
~ reorganized the config class

[2007-07-24] - 0.4.0
+ rewritten internal graph to achieve asyncronous changes (will be in a background thread in the future!)
+ now sequencer is syncable with seq24 using midi start/stop/continue messages
+ added support for plugins that want to open file selectors (vst only)
+ added main component with modular tab
+ added browser component with disk browser and bookmarks
+ added ability to remove selected bookmarks
+ added dynamic resizer bar
+ added button to show/hide the tabbed browser
+ added option to select the browser on the left or the right (default.conf only)
+ added option for setting tab panel buttons' height (default.conf only)
~ more fixes for building on 64bit machines
~ removed version check on plugin preset and global session restore (why it was there ?)
~ fixed when you can't load a session file for some reason, the current session isn't replaced
~ some more fixes loading wrong cable patches
~ renamed session files to jxs (jostXsession) and presets to jxp (jostXpreset)

[2007-06-17] - 0.3.4
~ fixed the tempo slider was not restored with the session load
~ fixed a bug when recording and have some note selected
~ optimized recording notes update
~ fixes for building on 64bit machines

[2007-06-14] - 0.3.3
+ added single midi track sequencer
+ added transport class
+ added preset selector for dssi plugins
+ added remember last preset directory for each plugin
+ added sequencer toolbar/menu on main window
+ added ability to have graph directed from left to right or from top to bottom (config file)
~ improved dssi plugins audio / parameters handling
~ improved look and feel draw for toggle buttons
~ improved colour scheme
~ fixed a bug when restoring session and we got some windows open
~ fixed not restoring midi keyboards on plugins when reloading session
~ fixed blocking audio thread for too long (jack say thanks a lot)
~ fixed a nasty bug when having multiple midi i/o plugins (identified as a single one)

[2007-06-04] - 0.3.2
+ added dssi plugins support (some plugins still crash jost)
~ improved alsa seq midi i/o device creation
~ changed alsa seq midi port names
~ fixed in some cases plugins were restored with 0 size icons
~ fixed crash reloading a session with a plugin that doesn't exists anymore
~ fixed a problem reloading saved ladspa plugins

[2007-06-03] - 0.3.1
+ added internal midi i/o plugins for having more than one midi i/o
+ added support for ladspa plugins (experimental)
+ rewritten midi engine, now midi processing plugins are supported
+ added support for opening more than one plugin window
+ added close window with double click on plugin icon
+ added tooltip capabilities to graph nodes
+ added ability to load / save presets for plugins in their editor window
+ added options page in plugin editor window
+ save of plugin editor window size (when using the native editor)
+ saved the window layouts with the session
+ added more properties to the colour scheme
~ improved midi handling, every plugin gets his own midi messages separately
~ improved usage of midi-keyboards on plugin editor (each keyboard plays only its parent plugin)

[2007-05-28] - 0.3.0
+ added a directed graph for plugin handling
+ added plugin audio i/o routing (connecting from input to output and the opposite)
+ added plugin midi i/o routing (basically working for synths only)
+ added property set for each plugin
+ added for each plugin save last window position / last page displayed
+ added save of routings to preset files
+ added main window position / size save
+ added autoconnection for i/o of plugins (only selectable via config file, and disabled by default)
+ doubled ports to 4 in / 4 out
+ added basic colour scheme support (look in ~/colourscheme.conf)
+ added support for callback audioMasterUpdateDisplay
~ improved plugin handling, now adding more technology like ladspa or dssi should be straightforward
~ improved handling of physical jack inputs and outputs (now wrapped as plugins)
~ improved graph rebalancing method
~ fixed a buffer problem that was causing zipper noise when disconnecting devices
~ fixed z-order of some nodes / connection wires
~ fixed a bug when loading presets with plugins not found
~ reordered the window calls to show the window only when is completely built
~ was possible get same connection twice. fixed

[2007-04-18] - 0.2.3 
+ added ability to clear all open plugins
~ extremely important fixes in juce codebase bindings for linux
~ fixed functions for loading .so that could cause loading the same plugin with different .so
~ fixed plugin editor window returning BadWindow errors when sending wrong XEvents
~ fixed OSC control that was unusable due to bad string manipulation
~ improved handling of already open windows
~ improved handling of plugins with their own GUI
~ fixed a problem with some gui plugins not reparenting correctly in some cases
- temporarily removed support to sizeWindow calls

[2007-03-27] - 0.2.2
+ added internal drag and drop of plugins with placement indicator
+ added session load / save to and from XML files
+ added basic plugins preset / chunk save support with session
+ added recent sessions sub menu for fast recall of sessions
+ added open window on main track right click

[2007-03-26] - 0.2.1 
+ added bypass when host have no plugins loaded
+ added plugin support for fxIdle calls (outside editor window)
+ added support for plugin asking for VstTimeInfo (fixed as we have no transport...)
+ added support for send events to host
+ added tracks component with draggable vsts on it
+ added application command manager
+ added recent plugin list
+ plugin processing and handling moved to tracks (now only a fixed one for now)
~ increased max internal buffers to 16 (which plugin have more than this ?)
~ when loading a plugin, we compute the maximum number of buffers for input/output
~ fixed now plugin editor window is a DialogWindow instead of a DocumentWindow

[2007-03-23] - 0.2.0
+ added OSC server: now plugin can be controlled by an external OSC client (port 6789)
+ added midi keyboard for synthesizers
+ added tabbed panel for future selections
+ added preset list to window menu
+ added an empty option page (for future plugin specific configuration)
+ added about box :)
+ added internal buffer allocations (more flexibility with slightly cpu increase)
+ added new sliders graphics
~ plugins with gui have also the parameter browser
~ fixed problem with computing midi bytes to send to plugin

[2007-03-09] - 0.1.2
+ added a brief menubar (will be filled with commands, presets browser, etc.)
+ added possibility to launch plugin from command line
~ plugin with vstgui and made with JUCE will now work (with some small issues)
~ various bug fixes in the VstPluginExternalEditor
~ improved marshaling in  VstPluginExternalEditor

[2007-02-27] - 0.1.1
+ added plugin drag and drop support

[2007-02-14] - 0.1.0
* initial release


-------------------------------------------------------------------------------------------
Copyrights --------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------
    
- JOST (c) by Asnaghi Lucio @ jucetice
- JUCE (c) by Julian Storer @ rawmaterialsoftware
- DSSI (c) by Chris Cannam, Steve Harris and Sean Bolton
- LADSPA (c) by Richard Furse
- VST (c) by Steinberg
- Rubber Band (c) by Chris Cannam
- Niall's OSC Lib / UDPSocket (c) by Niall Moody
- kissfft (c) by Mark Borgerding
- libsamplerate (c) by Erik de Castro Lopo
- MidiPads (c) by ThePiz
- AudioSpecMeter (c) mda


-------------------------------------------------------------------------------------------
License -----------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------

 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; version 2 of the
 * License.
 *
 * This program is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, write to the Free
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307, USA.


-------------------------------------------------------------------------------------------
Shootouts ---------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------

Giulia. Without her patience, this would have never happened.
Julian, for his framework and for listening a poor developer.
The other JUCE folks, for some good classes used inside jost.
Dave Phillips and Rui Nuno Capela, for the support, the interest, the massive testing.
Thomas (Gimpel), for loosing hours making jost ebuilds in the proaudio overlay.
The #JackLab people, for the continue help and ideas.

