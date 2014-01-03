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

#ifndef __JOST_COMMANDS_HEADER__
#define __JOST_COMMANDS_HEADER__


#include "StandardHeader.h"


//==============================================================================
namespace CommandIDs
{
    static const int pluginOpen         = 0x2000;
    static const int pluginClose        = 0x2001;
    static const int pluginClear        = 0x2002;
    static const int pluginPresetLoad   = 0x2003;
    static const int pluginPresetSave   = 0x2004;
    static const int pluginShowKeyboard = 0x2005;

    static const int sessionLoad        = 0x2100;
    static const int sessionSave        = 0x2101;
    static const int sessionNew         = 0x2102;

    static const int audioOptions       = 0x2200;
    static const int audioPlay          = 0x2201;
    static const int audioStop          = 0x2202;
    static const int audioRecord        = 0x2203;
    static const int audioRewind        = 0x2204;
    static const int audioLoop          = 0x2205;

    static const int appToolbar         = 0x2400;
    static const int appBrowser         = 0x2401;
    static const int appExit            = 0x2402;
    static const int appAbout           = 0x2403;
    static const int appFullScreen      = 0x2404;

    static const int surfaceLock        = 0x2500;
    static const int surfaceProperties  = 0x2501;

    static const int recentPlugins      = 0x9000;
    static const int recentSessions     = 0x9900;
};


//==============================================================================
namespace CommandCategories
{
    static const tchar* const file = T("File");
    static const tchar* const audio = T("Audio");
    static const tchar* const presets = T("Presets");
    static const tchar* const surface = T("Surface");
    static const tchar* const options = T("Options");
    static const tchar* const about = T("?");
}


//==============================================================================
class CommandManager : public ApplicationCommandManager
{
public:

    CommandManager ();
    ~CommandManager ();

    juce_DeclareSingleton (CommandManager, true)
};


#endif // __ANGELJUICE_COMMAND_HEADER__
