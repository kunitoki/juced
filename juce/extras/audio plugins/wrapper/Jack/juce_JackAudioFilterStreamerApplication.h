/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-6 by Raw Material Software ltd.

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

#ifndef __JUCE_JACKAUDIOFILTERSTREAMERAPPLICATION_H__
#define __JUCE_JACKAUDIOFILTERSTREAMERAPPLICATION_H__

#include "juce_JackAudioFilterStreamer.h"

//==============================================================================
/** Somewhere in the codebase of your plugin, you need to implement this function
    and make it create an instance of the filter subclass that you're building.
*/
extern AudioProcessor* JUCE_CALLTYPE createPluginFilter (const String& commandLine);


//==============================================================================
class JackAudioFilterStreamerWindow  : public DocumentWindow
{
public:

    JackAudioFilterStreamerWindow (const String& commandLine)
      : DocumentWindow (T(""), Colour (32, 32, 32), DocumentWindow::closeButton, true)
    {
        // create the filter
        pluginFilter = createPluginFilter (commandLine);

        // create the streamer and assign host to it
        jackStreamer = new JackAudioFilterStreamer ();
        jackStreamer->setFilter (pluginFilter, true, false, false);

        // assign the streamer as external transport
        // pluginFilter->setExternalTransport (jackStreamer);

        // create the editor (will be the contentComponent)
        Component* pluginEditor = jackStreamer->createFilterEditorIfNeeded();

        // set window name
        setName (pluginFilter->getName());
        
        // setup main component and menu
        setContentComponent (pluginEditor, true, true);
        // setMenuBar (pluginEditor, 20);

        // restore window position
        centreWithSize (pluginEditor->getWidth(),
                        pluginEditor->getHeight() + getTitleBarHeight ());

        // we can resize ourselves
        setResizable (false, true);
    }

    ~JackAudioFilterStreamerWindow ()
    {
        // do this before pluginFilter gets deleted
        // setMenuBar (0);

        if (getContentComponent() != 0)
            setContentComponent (0);

        // this must be the very latest thing you should do !
        deleteAndZero (pluginFilter);
    }

    void closeButtonPressed ()
    {
        deleteAndZero (jackStreamer);

        JUCEApplication::getInstance()->systemRequestedQuit();
    }

protected:
    AudioProcessor* pluginFilter;
    JackAudioFilterStreamer* jackStreamer;
};


//==============================================================================
class JackAudioFilterStreamerApplication : public JUCEApplication
{
public:

    //==============================================================================
    JackAudioFilterStreamerApplication()
      : window (0)
    {}

    ~JackAudioFilterStreamerApplication()
    {}

    //==============================================================================
    void initialise (const String& commandLine)
    {
        Process::setPriority(Process::LowPriority);
        Thread::setCurrentThreadPriority (7);

        window = new JackAudioFilterStreamerWindow (commandLine);
        window->toFront (true);
        window->setVisible (true);
    }

    void shutdown()
    {
        deleteAndZero (window);
    }

    //==============================================================================
    void systemRequestedQuit()
    {
        quit ();
    }

    void unhandledException (const std::exception* e,
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
    const String getApplicationName()                   { return T(JucePlugin_Name); }
    const String getApplicationVersion()                { return T(JucePlugin_VersionString); }

    //==============================================================================
    bool moreThanOneInstanceAllowed()                   { return true; }

private:

    JackAudioFilterStreamerWindow* window;
};


#endif
