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

#ifndef __JUCETICE_SOUNDCRABCONFIG_HEADER__
#define __JUCETICE_SOUNDCRABCONFIG_HEADER__

#include "StandardHeader.h"
#include "JucePluginCharacteristics.h"


//==============================================================================
/**
    These are the MACROS global to the whole application
*/
#define SOUNDCRAB_COLOUR                 Colour (210, 210, 210)
#define SOUNDCRAB_STRING                 T("soundcrab")

#ifdef JUCE_WIN32
  #define SOUNDCRAB_CONFIG_DIRECTORY     T("soundcrab")
#elif defined JUCE_LINUX
  #define SOUNDCRAB_CONFIG_DIRECTORY     T(".soundcrab")
#elif defined JUCE_MAC
  #define SOUNDCRAB_CONFIG_DIRECTORY     T(".soundcrab")
#endif

#define SOUNDCRAB_CONFIG_FILENAME        T("default")
#define SOUNDCRAB_CONFIG_EXTENSION       T("conf")

#define SOUNDCRAB_PRESET_COMPRESSION     0
#define SOUNDCRAB_PRESET_ENCODE          0


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
    RecentlyOpenedFilesList recentSoundfonts;
    File lastSoundfontDirectory;

    //==============================================================================
    void addRecentSoundfont (const File& file);

    //==============================================================================
    /** This will ensure the file is written out */
    void flush ();

    //==============================================================================
    /** Singleton declaration */
    juce_DeclareSingleton (Config, true)

protected:

    /** Internal helper and resources */
    PropertiesFile* configFile;
};



#endif // __JUCETICE_SOUNDCRABCONFIG_HEADER__
