/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2008 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2008 by Julian Storer.

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
#ifndef _WIN32
#include "../../../juce/src/core/juce_PlatformDefs.h" // haszari: added so can use JUCE platform conditionals here instead of raw compiler conditionals
#endif
//#define JUCE_ONLY_BUILD_CORE_LIBRARY   1
//#define JUCE_FORCE_DEBUG  1
//#define JUCE_LOG_ASSERTIONS  1
//#define JUCE_ASIO  1
//#define JUCE_ALSA  1
//#define JUCE_JACK 1
//#define JUCE_JACK_BRIDGE 1
//#define JUCE_LASH 1
//#define JUCE_QUICKTIME  1
//#define JUCE_OPENGL  1
//#define JUCE_USE_FLAC  1
//#define JUCE_USE_OGGVORBIS  1
//#define JUCE_USE_CDBURNER  1
//#define JUCE_ENABLE_REPAINT_DEBUGGING  1
//#define JUCE_USE_XINERAMA  1
//#define JUCE_USE_XSHM  1
//#define JUCE_PLUGINHOST_VST  1
//#define JUCE_PLUGINHOST_AU  1
#define JUCE_BUILD_EXT_CLASSES  1
//#define JUCE_CHECK_MEMORY_LEAKS  1
//#define JUCE_CATCH_UNHANDLED_EXCEPTIONS  1
#define JUCE_STRINGS_ARE_UNICODE  1

#ifdef JUCE_WIN32
 #define JUCE_ASIO  1
 #define JUCE_PLUGINHOST_VST  1
 #define JOST_USE_VST 1
#endif

#ifdef JUCE_MAC
 #define JUCE_PLUGINHOST_VST  1
 #define JOST_USE_LADSPA 1
 #define JOST_USE_DSSI 1
 #define JOST_USE_VST 1
 #define JUCE_USE_VSTSDK_2_4 1
 #define VST_FORCE_DEPRECATED 0
#endif

