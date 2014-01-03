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

#include "MainTabbedComponent.h"
#include "../HostFilterComponent.h"


//==============================================================================
MainTabbedComponent::MainTabbedComponent (HostFilterComponent* owner_)
  : TabbedComponent (TabbedButtonBar::TabsAtBottom),
    owner (owner_),
    graph (0),
    mixer (0),
    surface (0),
    graphViewport (0)
{
    DBG ("MainTabbedComponent::MainTabbedComponent");

    setTabBarDepth (Config::getInstance ()->defaultTabThickness);
}

MainTabbedComponent::~MainTabbedComponent ()
{
    DBG ("MainTabbedComponent::~MainTabbedComponent");

    clearComponents ();
}

//==============================================================================
void MainTabbedComponent::rebuildComponents ()
{
    DBG ("MainTabbedComponent::rebuildComponents");

    jassert (graphViewport == 0)
    jassert (graph == 0)
    jassert (mixer == 0)
    jassert (surface == 0);

    Colour backgroundColour = Config::getInstance ()->getColour (T("mainBackground"));

    graph = new GraphComponent (owner);
    graph->setHost (owner->getHost());
    graph->setSize (1280, 1280);
    
    graphViewport = new Viewport ();
    graphViewport->setViewedComponent (graph);
    graphViewport->setScrollBarsShown (true, true);
//    graphViewport->setScrollBarThickness (10);
//    graphViewport->setViewPositionProportionately (0.5f, 0.5f);

    addTab (T("Modular"), backgroundColour, graphViewport, false);

    mixer = new MixerComponent (owner);
    mixer->setHost (owner->getHost());
    addTab (T("Mixer"), backgroundColour, mixer, false);

#if JOST_USE_SURFACE
    surface = new SurfaceComponent (owner);
    surface->setHost (owner->getHost());
    addTab (T("Surface"), backgroundColour, surface, false);
#endif

    // change last saved tab
    // int lastSelectedTab = plugin->getIntValue (PROP_WINDOWPAGE, 0);
    // setCurrentTabIndex (lastSelectedTab);
}

void MainTabbedComponent::clearComponents ()
{
    DBG ("MainTabbedComponent::clearComponents");

    clearTabs ();

    // graph = 0;
    // deleteAndZero (graphViewport); // this deletes graph
    deleteAndZero (mixer);
#if JOST_USE_SURFACE
    deleteAndZero (surface);
#endif
}

//==============================================================================
void MainTabbedComponent::currentTabChanged (const int newCurrentTabIndex,
                                             const String &newCurrentTabName)
{
    DBG ("MainTabbedComponent::currentTabChanged");

    HostFilterComponent* parent = findParentComponentOfClass<HostFilterComponent> ();
    if (parent && mixer)
    {
//        int lastPageIndex = 0;

        if (newCurrentTabName == T("Modular"))
        {
            if (mixer->isTimerRunning ())
                mixer->stopTimer ();
        }
        else if (newCurrentTabName == T("Mixer"))
        {
            mixer->rebuildChannels ();

            if (! mixer->isTimerRunning ())
                mixer->startTimer (50);
        }
#if JOST_USE_SURFACE
        else if (newCurrentTabName == T("Surface"))
        {
            if (mixer->isTimerRunning ())
                mixer->stopTimer ();
        }
#endif

        // save property
//        plugin->setValue (PROP_WINDOWPAGE, lastPageIndex);
    }
}
