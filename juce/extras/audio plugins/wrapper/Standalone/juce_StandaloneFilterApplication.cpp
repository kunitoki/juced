/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-7 by Raw Material Software ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the
   GNU General Public License, as published by the Free Software Foundation;
   either version 2 of the License, or (at your option) any later version.

   JUCE is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with JUCE; if not, visit www.gnu.org/licenses or write to the
   Free Software Foundation, Inc., 59 Temple Place, Suite 330,
   Boston, MA 02111-1307 USA

  ------------------------------------------------------------------------------

   If you'd like to release a closed-source product which uses JUCE, commercial
   licenses are also available: visit www.rawmaterialsoftware.com/juce for
   more information.

  ==============================================================================
*/

#include "juce_StandaloneFilterApplication.h"
#include "../juce_PluginHeaders.h"

//==============================================================================
StandaloneFilterApplication::StandaloneFilterApplication()
  : window (0)
{
}

StandaloneFilterApplication::~StandaloneFilterApplication()
{
}

//==============================================================================
void StandaloneFilterApplication::initialise (const String& commandLine)
{
    DBG ("StandaloneFilterApplication::initialise");

    // set thread priority
    //Process::setPriority(Process::LowPriority);
    //Thread::setCurrentThreadPriority (8);

    // open up config
    ApplicationProperties* appProperties = ApplicationProperties::getInstance(); 
    appProperties->setStorageParameters (T(JucePlugin_Name),
                                         T("conf"),
                                         T(".jucetice"),
                                         2000,
                                         PropertiesFile::ignoreCaseOfKeyNames
                                         | PropertiesFile::storeAsXML);    

    // setup window name
    String pluginWindowName;
    pluginWindowName << JucePlugin_Name << " v" << JucePlugin_VersionString;
#ifdef JUCE_DEBUG       
    pluginWindowName << " (DEBUG)";
#endif

    // create the window
    window = new StandaloneFilterWindow (pluginWindowName,
                                         Colour (32, 32, 32),
                                         DocumentWindow::closeButton | DocumentWindow::minimiseButton,
                                         true);

    // set window visible
    window->toFront (true);
    window->setVisible (true);
}

void StandaloneFilterApplication::shutdown()
{
    DBG ("StandaloneFilterApplication::shutdown");

    if (window)
    {
        window->setVisible (false);
        window->setMenuBar (0);

        deleteAndZero (window);
    }

    ApplicationProperties::getInstance()->closeFiles ();
    ApplicationProperties::deleteInstance();
}

//==============================================================================
void StandaloneFilterApplication::systemRequestedQuit()
{
    DBG ("StandaloneFilterApplication::systemRequestedQuit");

    quit ();
}

void StandaloneFilterApplication::unhandledException (const std::exception* e,
                                                      const String& sourceFilename,
                                                      const int lineNumber)
{
#ifndef JUCE_DEBUG
    AlertWindow::showMessageBox (AlertWindow::WarningIcon,
                                 T("Unhandled Exception"),
                                 T("Something bad happened to the application.") );
    quit ();
#endif
}

//==============================================================================
const String StandaloneFilterApplication::getApplicationName()
{
    return T(JucePlugin_Name);
}

const String StandaloneFilterApplication::getApplicationVersion()
{
    return T(JucePlugin_VersionString);
}

//==============================================================================
bool StandaloneFilterApplication::moreThanOneInstanceAllowed()
{
    return true;
}

