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

#ifndef JOST_VST_PLUGIN

#include "HostFilterBase.h"
#include "HostFilterComponent.h"

#include "wrapper/Standalone/juce_AudioFilterStreamer.cpp"
#include "wrapper/Standalone/juce_StandaloneFilterWindow.cpp"

//==============================================================================
/** Somewhere in the codebase of your plugin, you need to implement this function
    and make it create an instance of the filter subclass that you're building.
*/
extern AudioProcessor* JUCE_CALLTYPE createPluginFilter (const String& commandLine);

//==============================================================================
class HostApplication : public JUCEApplication
{
public:

    //==============================================================================
    HostApplication()
      : window (0)
    {}

    ~HostApplication()
    {}

    //==============================================================================
    void initialise (const String& commandLine)
    {
        DBG ("HostApplication::initialise " + commandLine);

        Config* config = Config::getInstance ();

        // set thread priority    
        Process::setPriority(Process::LowPriority);
        Thread::setCurrentThreadPriority (8);

        // setup window name
        String jostMainWindowName;
        jostMainWindowName << JucePlugin_Name << " v" << JucePlugin_VersionString;

#ifdef JUCE_DEBUG       
        jostMainWindowName << " (DEBUG)";
#endif

        // create the window
        window = new StandaloneFilterWindow (jostMainWindowName,
                                             config->getColour (T("mainBackground")),
                                             DocumentWindow::allButtons,
                                             false,
                                             commandLine.trim());
        
        // attach the menubar to the window
        HostFilterBase* filter = (HostFilterBase*) window->getFilter ();
        if (filter)
        {
            HostFilterComponent* editor = (HostFilterComponent*) filter->createEditorIfNeeded();
            if (editor)
            {
                window->setMenuBar (editor, JOST_DEFAULT_MENU_HEIGHT);
            }
        }
        
        // set window visible
        window->toFront (true);
        window->setVisible (true);
    }

    void shutdown()
    {
        DBG ("HostApplication::shutdown");

        if (window)
        {
            window->setVisible (false);
            window->setMenuBar (0);

            deleteAndZero (window);
        }
    }

    //==============================================================================
    void systemRequestedQuit()
    {
        DBG ("HostApplication::systemRequestedQuit");

        quit ();
    }

    void unhandledException (const std::exception* e,
                             const String& sourceFilename,
                             const int lineNumber)
    {
        DBG ("HostApplication::unhandledException");

#ifndef JUCE_DEBUG
        AlertWindow::showMessageBox (AlertWindow::WarningIcon,
                                     T("Unhandled Exception"),
                                     T("Something bad happened to the application.") );
        quit ();
#endif
    }

    //==============================================================================
    const String getApplicationName()                   { return T(JucePlugin_Name); }
    const String getApplicationVersion()                { return T(JucePlugin_VersionString); }

    //==============================================================================
    bool moreThanOneInstanceAllowed()                   { return true; }

private:

    StandaloneFilterWindow* window;
};

//==============================================================================
START_JUCE_APPLICATION (HostApplication)

#else

//==============================================================================
/** We are building a VST plugin so we need to include the main wrapper class
*/

#include "wrapper/VST/juce_VST_Wrapper.cpp"

#endif


