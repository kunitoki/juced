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

#ifndef __JUCETICE_JOST_VSTEXTERNALEDITOR_HEADER__
#define __JUCETICE_JOST_VSTEXTERNALEDITOR_HEADER__

#if defined(LINUX)
  #include <X11/Xlib.h>
  #include <X11/Xutil.h>
  #include <X11/Xatom.h>
  #undef KeyPress
  #undef Drawable
  #undef Font
  #undef Time
#elif defined(_WIN32)
  #include <windows.h>
#endif

#include "../plugins/PluginEditorComponent.h"

class VstPluginWindow;

#ifdef JUCE_MAC
class MacVSTGUIPositionHelperWindow;
#endif

#ifdef LINUX
  #define Font JUCE_NAMESPACE::Font
  #define KeyPress JUCE_NAMESPACE::KeyPress
  #define Drawable JUCE_NAMESPACE::Drawable
  #define Time JUCE_NAMESPACE::Time
  typedef void (*EventProcPtr) (XEvent* ev);
#endif


//==============================================================================
class VstPluginExternalEditor : public PluginEditorComponent,
                                public Timer
{
public:

    //==============================================================================
    VstPluginExternalEditor (BasePlugin* plugin_,
                             VstPluginWindow* parent_);
    ~VstPluginExternalEditor ();

    //==============================================================================
    /** The window owner of this component is moving around.

        This will tell our child Window to update it's position
    */
    void updateWindowPosition (const int x, const int y);

    //==============================================================================
    /** Get the preferred width for the native GUI */
    int getPreferredWidth ();

    /** Get the preferred width for the native GUI */
    int getPreferredHeight ();

    /** Get the preferred resizable for the native GUI */
    bool isResizable ();
    
    //==============================================================================
    /** @internal */
    void mouseEnter (const MouseEvent& e);
    /** @internal */
    void mouseExit (const MouseEvent& e);
    /** @internal */
    void mouseMove (const MouseEvent& e);
    /** @internal */
    void mouseDown (const MouseEvent& e);
    /** @internal */
    void mouseDrag (const MouseEvent& e);
    /** @internal */
    void mouseUp (const MouseEvent& e);
    /** @internal */
    void mouseWheelMove (const MouseEvent& e, float incrementX, float incrementY);
    /** @internal */
    bool keyPressed (const KeyPress &key);

    //==============================================================================
    /** @internal */
    void filesDropped (const StringArray& filenames,
                       int mouseX,
                       int mouseY);
    /** @internal */
    void visibilityChanged ();
    /** @internal */
    void timerCallback ();
    /** @internal */
    void resized ();
    /** @internal */
    void paint (Graphics& g);

protected:

    /** @internal */
    void internalRepaint (int x, int y, int w, int h);

#if defined(LINUX)

    void sendEventToChild (XEvent* ev);
    Window getChildWindow (Window windowToCheck);
    bool isWindowVisible (Window windowToCheck);

    EventProcPtr eventProc;
    Window handle;

#elif defined(_WIN32)

    HWND handle;

#else
	
    MacVSTGUIPositionHelperWindow* vstGuiWindow;
	void* handle; // actually a Carbon WindowRef for the VST GUI overlay.
    void setGuiWindow(MacVSTGUIPositionHelperWindow*);

public:
    void showGUI(bool bVisible);

#endif

protected:
    VstPluginWindow* window;
    int editorWidth, editorHeight;
    int offsetX, offsetY;
};


#endif
