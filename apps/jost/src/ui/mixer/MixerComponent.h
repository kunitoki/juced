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

#ifndef __JUCETICE_JOSTMIXERCOMPONENT_HEADER__
#define __JUCETICE_JOSTMIXERCOMPONENT_HEADER__

#include "../../Config.h"
#include "../../model/Host.h"

#include "MixerStripComponent.h"


//==============================================================================
/**
     A mixer component
*/
class MixerComponent  : public Component,
                        public Timer,
                        public DragAndDropTarget
{
public:

    //==============================================================================
    MixerComponent (HostFilterComponent* owner_);

    ~MixerComponent();

    //==============================================================================
    /** Set the host that this component will handle

        The component will not refresh its gui, the caller must issue that call.
    */
    void setHost (Host* hostToDisplay);

    //==============================================================================
    void rebuildChannels ();
    void clearChannels ();
    // void toggleSoloChannel (MixerStripComponent* const strip);

    //==============================================================================
    void mouseDown (const MouseEvent& e);
    void mouseDrag (const MouseEvent& e);
    void mouseUp (const MouseEvent& e);
    void mouseDoubleClick (const MouseEvent& e);

    void filesDropped (const StringArray& filenames,
                       int mouseX,
                       int mouseY);

    //==============================================================================
    /** Derived from DragAndDropTarget */
    bool isInterestedInDragSource (const String& sourceDescription, Component* source);

    /** Derived from DragAndDropTarget */
    void itemDragEnter (const String& sourceDescription,
                        Component* sourceComponent,
                        int x, int y);

    /** Derived from DragAndDropTarget */
    void itemDragMove (const String& sourceDescription,
                       Component* sourceComponent,
                       int x, int y);

    /** Derived from DragAndDropTarget */
    void itemDragExit (const String& sourceDescription,
                       Component* sourceComponent);

    /** Derived from DragAndDropTarget */
    void itemDropped (const String& sourceDescription,
                      Component* sourceComponent,
                      int x, int y);

    //==============================================================================
    void timerCallback ();

    //==============================================================================
    void paint (Graphics& g);
    void resized ();

protected:

    Host* host;
    HostFilterComponent* owner;

    VoidArray channels;
};


#endif // __JUCETICE_JOSTMIXERCOMPONENT_HEADER__

