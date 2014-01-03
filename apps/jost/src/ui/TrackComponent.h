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

#ifndef __JUCETICE_JOSTTRACKCOMPONENT_HEADER__
#define __JUCETICE_JOSTTRACKCOMPONENT_HEADER__

#if 0

#include "../Config.h"
#include "../model/Track.h"

//==============================================================================
/**
     An track component
*/
class TrackComponent  : public Component,
                        public Dockable,
                        public DragAndDropTarget
{
public:

    //==============================================================================
    TrackComponent (HostFilterComponent* owner_);

    ~TrackComponent();

    //==============================================================================
    /** Set the track that this component will handle

        The component will not refresh its gui, the caller must issue that call.
    */
    void setTrack (Track* trackToDisplay);

    //==============================================================================
    void paint (Graphics& g);

    //==============================================================================
    void mouseDown (const MouseEvent& e);
    void mouseDrag (const MouseEvent& e);
    void mouseUp (const MouseEvent& e);
    void mouseDoubleClick (const MouseEvent& e);

    bool filesDropped (const StringArray& filenames,
                       int mouseX,
                       int mouseY);

    //==============================================================================
    /** Implementation of Dockable class

        Return the description of this dragging source
    */
    String getDragDescription ();

    /** Implementation of Dockable class

        It should return the image you want to make dragable
    */
    Image* getDragImage ();

    /** Implementation of Dockable class

        Which component issued startDrag ? In this case we are itself
    */
    Component* getDragComponent ();

    //==============================================================================
    /** Derived from DragAndDropTarget */
    bool isInterestedInDragSource (const String& sourceDescription);

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
    int getSelectedPlugin () const  { return selectedPlugin; }
    int getPluginsCount () const;

    void dropPluginOnTrack (const String& pluginPath,
                            int mouseX,
                            int mouseY);

    bool loadAndAppendPlugin (const File& file);
    bool loadAndAppendPlugin ();
    bool closePlugin (const int index);

protected:

    //==============================================================================
    int getPluginIndexFromMousePosition (const int x, const int y);
    BasePlugin* getPluginFromMousePosition (const int x, const int y);

    //==============================================================================
    void paintPluginImage (Graphics& g,
                           const int x,
                           const int y,
                           const int width,
                           const int height,
                           const String& text,
                           const bool isSelected);

    HostFilterComponent* owner;
    Track* track;
    int selectedPlugin;
    int draggingPluginIndex;
};

#endif

#endif // __JUCETICE_JOSTTRACKCOMPONENT_HEADER__

