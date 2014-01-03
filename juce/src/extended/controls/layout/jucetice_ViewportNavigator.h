/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2009 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2007 by Julian Storer.

 ------------------------------------------------------------------------------

 JUCE and JUCETICE can be redistributed and/or modified under the terms of
 the GNU General Public License, as published by the Free Software Foundation;
 either version 2 of the License, or (at your option) any later version.

 JUCE and JUCETICE are distributed in the hope that they will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with JUCE and JUCETICE; if not, visit www.gnu.org/licenses or write to
 Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 Boston, MA 02111-1307 USA

 ==============================================================================
*/

#ifndef __JUCETICE_VIEWPORTNAVIGATOR_HEADER__
#define __JUCETICE_VIEWPORTNAVIGATOR_HEADER__

#include "../../../events/juce_Timer.h"
#include "../../../gui/components/juce_Component.h"
#include "../../../gui/components/layout/juce_Viewport.h"
#include "../../../gui/graphics/imaging/juce_Image.h"


//==============================================================================
/**
    The ViewportNavigator is a special component that monitors a Viewport
    and let you have a thumbnail of the viewport and manage navigation in
    the whole Viewport area by using the mouse.

*/
//==============================================================================
class ViewportNavigator : public Component,
                          public ViewportListener,
                          public ComponentListener,
                          public Timer
{
public:

    //==============================================================================
    /** Constructor */
    ViewportNavigator (Viewport* const viewportToWatch);

    /** Destructor */
    ~ViewportNavigator ();

    //==============================================================================
    /**
        Returns the current controlled viewport  
       
        @see setViewedViewport
    */
    Viewport* getViewedViewport ();

    /**
        Sets the current controlled viewport
        
        This will unregister any previously attached Viewport and register
        the new one. If it is needed this will trigger an asynchronous repaint.
        
        @see getViewedViewport, Viewport
    */
    void setViewedViewport (Viewport* const viewportToWatch);

    //==============================================================================
    /** @see ComponentListener */
    void componentMovedOrResized (Component& component, bool wasMoved, bool wasResized);

    /** @see ViewportListener */
    void viewedComponentChanged (Viewport* const viewportThatChanged,
                                 Component* const newViewedComponent);

    /** @see ViewportListener */
    void visibleAreaChanged (Viewport* const viewportThatChanged,
                             int visibleX, int visibleY,
                             int visibleW, int visibleH);

    //==============================================================================
    /** 
        Update both the snapshot and the visible indicator 
    
        You can choose to do this asyncronously or syncronously. If you do it
        asyncronously a Timer will be triggered around 500 ms before doing the
        real update.

        @see timerCallback
    */
    void updateVisibleArea (const bool asyncronously = true);

    //==============================================================================
    /**@internal*/
    void resized ();
    /**@internal*/
    void paint (Graphics& g);
    /**@internal*/
    void mouseDown (const MouseEvent& e);
    /**@internal*/
    void mouseMove (const MouseEvent& e);
    /**@internal*/
    void mouseDrag (const MouseEvent& e);
    /**@internal*/
    void mouseUp (const MouseEvent& e);
    /**@internal*/
    void timerCallback ();

protected:

    void updateSnapshot ();
    void updateViewPosition ();

    bool isPointInsideCurrentViewArea (const float x, const float y) const;

    Viewport* watchedViewport;
    Image* componentSnapshot;

    float viewPositionX;
    float viewPositionY;
    float viewWidth;
    float viewHeight;
    float dragViewPositionX;
    float dragViewPositionY;
};


#endif // __JUCETICE_VIEWPORTNAVIGATOR_HEADER__
