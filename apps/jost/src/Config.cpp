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

#include "Config.h"


//==============================================================================
Config::Config () :
    scheme (0)
{
    open ();
    read ();
}

Config::~Config ()
{
    write ();
    close ();
}

//==============================================================================
void Config::open ()
{
    ApplicationProperties* appProperties = ApplicationProperties::getInstance(); 

    appProperties->setStorageParameters (JOST_CONFIG_FILENAME,
                                         JOST_CONFIG_EXTENSION,
                                         JOST_CONFIG_DIRECTORY,
                                         2000,
                                         PropertiesFile::ignoreCaseOfKeyNames
                                         | PropertiesFile::storeAsXML);    

    PropertySet* config = getGlobalSettings ();

    int version = config->getIntValue ("version", 0);

    if (version == 0)
    {
        // application is newly installed
    }
    else if (version < JucePlugin_VersionCode)
    {
        // migrate settings !
        bool retValue = 
            AlertWindow::showOkCancelBox (AlertWindow::WarningIcon,
                                          T("Configuration upgrade"),
                                          T("We are now zapping Jost configuration files.\nIf you want to exit now and make backups press Cancel"));

        if (! retValue)
            JUCEApplication::quit ();

        File colourScheme (JOST_COLOR_SCHEME_PATH);
        if (colourScheme.exists ())
            colourScheme.deleteFile ();

        File bookmarkFile (JOST_BOOKMARK_PATH);
        if (bookmarkFile.exists ())
            bookmarkFile.deleteFile ();
    }
    else if (version > JucePlugin_VersionCode)
    {
        AlertWindow::showMessageBox (AlertWindow::WarningIcon,
                                      T("Configuration error"),
                                      T("Have you downgraded jost ? Or are you using both ? mmmmh tricky..."));
    }    
}

void Config::close ()
{
    deleteAndZero (scheme);

    ApplicationProperties::getInstance()->closeFiles ();
    ApplicationProperties::deleteInstance();
}

//==============================================================================
void Config::read ()
{
    PropertySet* config = getGlobalSettings ();

    // this is the first time
    firstTime = config->getIntValue (T("first_time"), 1);
    realTime = config->getIntValue (T("real_time"), 0);

    // toolbar set items
    toolbarSet = config->getValue (T("toolbar_set"), String::empty);

    // restore recent plugins
    recentPlugins.setMaxNumberOfItems (config->getIntValue (T("recent_plugins_max"), 10));
    recentPlugins.restoreFromString (config->getValue (T("recent_plugins")));
    lastPluginDirectory = File (config->getValue (T("last_plugins_directory"),
                                                  File::getCurrentWorkingDirectory().getFullPathName()));

    // restore recent sessions
    recentSessions.setMaxNumberOfItems (config->getIntValue (T("recent_sessions_max"), 10));
    recentSessions.restoreFromString (config->getValue (T("sessions_files")));
    lastSessionDirectory = File (config->getValue (T("last_session_directory"),
                                                   File::getCurrentWorkingDirectory().getFullPathName()));

    // restore recent preset directory
    lastPresetDirectory = File (config->getValue (T("last_preset_directory"),
                                                  File::getCurrentWorkingDirectory().getFullPathName()));

    // audio options properties
    externalTempoSync = config->getBoolValue (T("external_tempo_sync"), false);
    externalTempoMaster = config->getBoolValue (T("external_tempo_master"), false);
    autoConnectInputs = config->getBoolValue (T("auto_connect_inputs"), false);
    autoConnectOutputs = config->getBoolValue (T("auto_connect_outputs"), false);

    // visual graph options
    mainWindowBounds = Rectangle::fromString (config->getValue (T("last_window_bounds"), T("0 0 1 1")));
    toolbarSet = config->getValue (T("toolbar_order"), String::empty);
    graphLeftToRight = config->getBoolValue (T("node_left_to_right"), false);
    showTooltips = config->getBoolValue (T("show_tooltips"), 1);

    // browser
    showBrowser = config->getBoolValue (T("show_browser"), true);
    browserLeft = config->getBoolValue (T("browser_position_left"), false);
    browserLastOpenPage = config->getIntValue (T("browser_last_open_page"), 0);
    lastBrowsedDirectory = File (config->getValue (T("last_browsed_directory"),
                                                   File ("~/").getFullPathName()));

    // tab thickness
    defaultTabThickness = config->getIntValue (T("tab_default_height"), JOST_DEFAULT_TAB_HEIGHT);

    // restore colour scheme
    colourSchemeFile = File (config->getValue (T("colour_scheme_file"), JOST_COLOR_SCHEME_PATH));
    scheme = new ColourScheme (colourSchemeFile.getFullPathName ());
}

void Config::write ()
{
    PropertySet* config = getGlobalSettings ();

    config->setValue (T("version"), JucePlugin_VersionCode);
    config->setValue (T("first_time"), 0);
    config->setValue (T("real_time"), realTime);
    config->setValue (T("toolbar_set"), toolbarSet);
    config->setValue (T("recent_plugins"), recentPlugins.toString());
    config->setValue (T("last_plugins_directory"), lastPluginDirectory.getFullPathName());
    config->setValue (T("sessions_files"), recentSessions.toString());
    config->setValue (T("last_session_directory"), lastSessionDirectory.getFullPathName());
    config->setValue (T("last_preset_directory"), lastPresetDirectory.getFullPathName());
    config->setValue (T("external_tempo_sync"), externalTempoSync);
    config->setValue (T("external_tempo_master"), externalTempoMaster);
    config->setValue (T("auto_connect_inputs"), autoConnectInputs);
    config->setValue (T("auto_connect_outputs"), autoConnectOutputs);
    config->setValue (T("last_window_bounds"), mainWindowBounds.toString());
    config->setValue (T("node_left_to_right"), graphLeftToRight);
    config->setValue (T("show_tooltips"), showTooltips);
    config->setValue (T("show_browser"), showBrowser);
    config->setValue (T("browser_position_left"), browserLeft);
    config->setValue (T("browser_last_open_page"), browserLastOpenPage);
    config->setValue (T("tab_default_height"), defaultTabThickness);
    config->setValue (T("last_browsed_directory"),
                      lastBrowsedDirectory.existsAsFile () ? lastBrowsedDirectory.getParentDirectory().getFullPathName()
                                                           : lastBrowsedDirectory.getFullPathName());

    ApplicationProperties::getInstance()->saveIfNeeded ();
}

//==============================================================================
PropertySet* Config::getGlobalSettings()
{
    /* If you want this class to store the plugin's settings, you can set up an
       ApplicationProperties object and use this method as it is, or override this
       method to return your own custom PropertySet.

       If using this method without changing it, you'll probably need to call
       ApplicationProperties::setStorageParameters() in your plugin's constructor to
       tell it where to save the file.
    */
    return ApplicationProperties::getInstance()->getUserSettings();
}

//==============================================================================
void Config::addRecentPlugin (const File& file)
{
    recentPlugins.addFile (file);
    recentPlugins.removeNonExistentFiles ();

    lastPluginDirectory = file.getParentDirectory ();
}

void Config::addRecentSession (const File& file)
{
    recentSessions.addFile (file);
    recentSessions.removeNonExistentFiles ();

    lastSessionDirectory = file.getParentDirectory ();
}

void Config::addRecentPreset (const File& file)
{
//    recentPlugins.addFile (file);
//    recentPlugins.removeNonExistentFiles ();

    lastPresetDirectory = file.getParentDirectory ();
}

//==============================================================================
Colour Config::getColour (const String& name, const Colour& defColour) const
{
    return scheme->getColour (name, defColour);
}

void Config::setColour (const String& name, const Colour& newColour)
{
    scheme->setColour (name, newColour);
}

//==============================================================================
juce_ImplementSingleton (Config)

