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

   @author  Paul Nasca
   @tweaker Lucio Asnaghi

 ==============================================================================
*/

#include "Config.h"
#include <iostream>


//==============================================================================
juce_ImplementSingleton (Config)

//==============================================================================
Config::Config()
  : configFile (0)
{
    // defaults
    PluginVersion = JucePlugin_VersionCode;
    SampleRate = 44100;
    SoundBufferSize = 256;
    OscilSize = 512;
    LastOpenedPage = 0;
    LastOpenedPart = 0;
    IsKeyboardVisible = 0;
    CurrentBankDir = File (String ("~/")
                           + String (CONFIG_DIRECTORY)
                           + String ("/banks"));

    if (! CurrentBankDir.exists())
        CurrentBankDir.createDirectory ();
}

Config::~Config()
{
    save ();

    deleteAndZero (configFile);
}

//==============================================================================
void Config::load ()
{
    // open default app file
    if (configFile == 0)
        configFile = PropertiesFile::createDefaultAppPropertiesFile (
                                                            CONFIG_FILENAME,
                                                            CONFIG_FILEEXT,
                                                            CONFIG_DIRECTORY,
                                                            false,
                                                            -1,
                                                            PropertiesFile::ignoreCaseOfKeyNames
                                                            | PropertiesFile::storeAsXML);

    // read from property file
    if (configFile)
    {
#if 0
        if (cfg.PluginVersion <= configFile->getIntValue (T("plugin_version"), cfg.PluginVersion))
#endif
        {
            SampleRate = configFile->getIntValue ("sample_rate", SampleRate);
            SoundBufferSize = configFile->getIntValue ("buffer_size", SoundBufferSize);
            OscilSize = configFile->getIntValue ("partials_count", OscilSize);
            LastOpenedPage = configFile->getIntValue ("last_page", LastOpenedPage);
            LastOpenedPart = configFile->getIntValue ("last_part", LastOpenedPart);
            IsKeyboardVisible = configFile->getIntValue ("keys_visible", IsKeyboardVisible);
            // CurrentBankDir = configFile->getValue ("current_bank", CurrentBankDir.getFullPathName());
        }
    }
    else
        printf ("no config file found \n");

    OscilSize = (int) pow (2, ceil (log (OscilSize - 1.0) / log(2.0)));
}

//==============================================================================
void Config::save ()
{
    if (configFile)
    {
        // write configuration on files
        configFile->setValue ("plugin_version", PluginVersion);
        configFile->setValue ("sample_rate", SampleRate);
        configFile->setValue ("buffer_size", SoundBufferSize);
        configFile->setValue ("partials_count", OscilSize);
        configFile->setValue ("last_page", LastOpenedPage);
        configFile->setValue ("last_part", LastOpenedPart);
        configFile->setValue ("keys_visible", IsKeyboardVisible);
        // configFile->setValue ("current_bank", CurrentBankDir.getFullPathName ());

        // flush it
        configFile->saveIfNeeded  ();
    }
}
