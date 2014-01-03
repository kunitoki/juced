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

#ifndef __JUCETICE_JOSTSURFACECOMPONENT_HEADER__
#define __JUCETICE_JOSTSURFACECOMPONENT_HEADER__

#include "../../Config.h"
#include "../../model/Host.h"

class SurfaceObject;
class SurfaceProperties;
class InternalSurfaceComponent;


//==============================================================================
/**
     A surface component
*/
class SurfaceComponent  : public Component,
                          public SliderListener,
                          public JoystickListener
//                          public DragAndDropTarget
{
public:

    //==============================================================================
    SurfaceComponent (HostFilterComponent* owner_);

    ~SurfaceComponent();

    //==============================================================================
    /** Set the host that this component will handle

        The component will not refresh its gui, the caller must issue that call.
    */
    void setHost (Host* hostToHandle);

    //==============================================================================
    void mouseDown (const MouseEvent& e);
    void mouseDrag (const MouseEvent& e);
    void mouseUp (const MouseEvent& e);
    void mouseDoubleClick (const MouseEvent& e);

    void filesDropped (const StringArray& filenames,
                       int mouseX,
                       int mouseY);

    //==============================================================================
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void joystickValueChanged (Joystick* joystick);

    //==============================================================================
    void surfaceObjectChanged (SurfaceObject* object);
    
    //==============================================================================
    /*
    bool isInterestedInDragSource (const String& sourceDescription, Component* source);
    void itemDragEnter (const String& sourceDescription,
                        Component* sourceComponent,
                        int x, int y);
    void itemDragMove (const String& sourceDescription,
                       Component* sourceComponent,
                       int x, int y);
    void itemDragExit (const String& sourceDescription,
                       Component* sourceComponent);
    void itemDropped (const String& sourceDescription,
                      Component* sourceComponent,
                      int x, int y);
    */

    //==============================================================================
    void fillPluginComboBox (ComboBox* combo);
    void fillParametersComboBox (ComboBox* combo, const uint32 pluginHash);

    PopupMenu buildMenuForPluginsParameters ();

    //==============================================================================
    void paint (Graphics& g);
    void resized ();

protected:

    Host* host;
    HostFilterComponent* owner;

    StretchableLayoutResizerBar* horizontalDividerBar;
    StretchableLayoutManager horizontalLayout;

    InternalSurfaceComponent* internal;
    ComponentLayoutManager* editor;
    SurfaceProperties* properties;
};


#endif // __JUCETICE_JOSTMIXERCOMPONENT_HEADER__

