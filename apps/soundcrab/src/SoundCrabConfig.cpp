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

#include "SoundCrabConfig.h"


//==============================================================================
Config::Config () :
    configFile (0)
{
    // create the default configuration file...
    configFile = PropertiesFile::createDefaultAppPropertiesFile (
                                                        SOUNDCRAB_CONFIG_FILENAME,
                                                        SOUNDCRAB_CONFIG_EXTENSION,
                                                        SOUNDCRAB_CONFIG_DIRECTORY,
                                                        false,
                                                        -1,
                                                        PropertiesFile::ignoreCaseOfKeyNames
                                                        | PropertiesFile::storeAsXML);

    if (configFile)
    {
        // control version
        // int versionCode = configFile->getIntValue (T("version"), -1);

        // restore recent plugins
        recentSoundfonts.setMaxNumberOfItems (configFile->getIntValue (T("recent_soundfonts_max"), 10));
        recentSoundfonts.restoreFromString (configFile->getValue (T("recent_soundfonts")));

        // last browsed directory for plugins
        lastSoundfontDirectory = File (configFile->getValue (T("last_soundfont_directory"),
                                                             File::getSpecialLocation (File::userHomeDirectory).getFullPathName()));
    }
}

Config::~Config ()
{
    flush();

    deleteAndZero (configFile);
}

void Config::flush ()
{
    if (! configFile) return;

    // write configuration on files
    configFile->setValue (T("version"), JucePlugin_VersionCode);
    configFile->setValue (T("recent_soundfonts"), recentSoundfonts.toString());
    configFile->setValue (T("recent_soundfonts_max"), recentSoundfonts.getMaxNumberOfItems());
    configFile->setValue (T("last_soundfont_directory"), lastSoundfontDirectory.getFullPathName());

    // flush it
    configFile->saveIfNeeded ();
}

//==============================================================================
void Config::addRecentSoundfont (const File& file)
{
    recentSoundfonts.addFile (file);
    recentSoundfonts.removeNonExistentFiles ();

    lastSoundfontDirectory = file.getParentDirectory ();
}

//==============================================================================
juce_ImplementSingleton (Config)

