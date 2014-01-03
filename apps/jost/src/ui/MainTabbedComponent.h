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

#ifndef __JUCETICE_JOSTMAINTABBEDCOMPONENT_HEADER__
#define __JUCETICE_JOSTMAINTABBEDCOMPONENT_HEADER__

#include "../Config.h"
#include "../model/Host.h"
#include "mixer/MixerComponent.h"
#include "surface/SurfaceComponent.h"
#include "GraphComponent.h"


//==============================================================================
/**
    Tabbed panel which owns the External / Native GUI for plugins and
    also will host pages for fast tweaking, options... whatever
*/
class MainTabbedComponent : public TabbedComponent
{
public:
    //==============================================================================
    MainTabbedComponent (HostFilterComponent* owner_);

    ~MainTabbedComponent ();

    //==============================================================================
    void clearComponents ();
    void rebuildComponents ();

    bool areComponentsCreated () const              { return graph != 0; }

    //==============================================================================
    void currentTabChanged (const int newCurrentTabIndex,
                            const String &newCurrentTabName);

    //==============================================================================
    Viewport* getGraphViewport () const            { return graphViewport; }

    GraphComponent* getGraph () const              { return graph; }
    MixerComponent* getMixer () const              { return mixer; }
    SurfaceComponent* getSurface () const          { return surface; }

protected:

    HostFilterComponent* owner;

    GraphComponent* graph;
    MixerComponent* mixer;
    SurfaceComponent* surface;
    
    Viewport* graphViewport;
};


#endif // __JUCETICE_JOSTMAINTABBEDCOMPONENT_HEADER__
