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

#include "JackedWindow.h"

//==============================================================================
JackedWindow::JackedWindow (const String& commandLine)
  : DocumentWindow (T(""), Colour (32, 32, 32), DocumentWindow::closeButton, true),
    graph (0)
{    DBG ("JackedWindow::JackedWindow");

    // set window name
    String applicationName;
    applicationName << JACKED_NAME << " - " << JACKED_VERSION_STRING;
    setName (applicationName);
    
    // add the tray icon    
#if 0
    tray = new JackedSystemTray ();
#endif
    screen = new JackedOnScreenDisplay ();
    screen->addToDesktop (0);
    screen->setTopLeftPosition (0, 100); 
    screen->setVisible (true);

    // setup main component and menu
    setContentComponent (graph = new JackedGraph (this), true, false);
    // setMenuBar (pluginEditor, 20);

    // restore window position
    centreWithSize (800,
                    600 + getTitleBarHeight ());

    // create first stuffs
    graph->startCheckForServer ();

    // we can resize ourselves
    setResizable (true, true);
}

JackedWindow::~JackedWindow ()
{
    DBG ("JackedWindow::~JackedWindow");

    // do this before pluginFilter gets deleted
    // setMenuBar (0);

    if (getContentComponent() != 0)
        setContentComponent (0, false, false);

    // this must be the very latest thing you should do !
    deleteAndZero (graph);
#if 0
    deleteAndZero (tray);
#endif
    screen->removeFromDesktop ();
    deleteAndZero (screen);
}

//==============================================================================
void JackedWindow::closeButtonPressed ()
{
    DBG ("JackedWindow::closeButtonPressed");

    JUCEApplication::getInstance()->systemRequestedQuit();
}

