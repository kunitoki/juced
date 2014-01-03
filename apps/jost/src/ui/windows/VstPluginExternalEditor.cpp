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

#include "VstPluginExternalEditor.h"
#include "VstPluginWindow.h"

#if defined(LINUX)
  BEGIN_JUCE_NAMESPACE
    extern Display* display;
    extern XContext improbableNumber;
  END_JUCE_NAMESPACE

  bool g_xerror_value;
  int temporaryErrorHandler (Display *dp, XErrorEvent *e)
  {
      g_xerror_value = true;
      return 0;
  }

  int obtainPropertyFromXWindow (Window handle, Atom atom)
  {
      int result = 0, userSize;
      unsigned long bytes, userCount;
      unsigned char *data;
      Atom userType;
      g_xerror_value = false;
      XErrorHandler oldErrorHandler = XSetErrorHandler (temporaryErrorHandler);
      XGetWindowProperty (display, handle, atom, 0, 1, false, AnyPropertyType,
                          &userType,  &userSize, &userCount, &bytes, &data);
      if (g_xerror_value == false && userCount == 1)
          result = *(int*) data;
      XSetErrorHandler (oldErrorHandler);
      return result;
  }

  void translateJuceToXButtonModifiers (const MouseEvent& e,
                                         XEvent& ev)
  {
      int currentModifiers = e.mods.getRawFlags ();
      if (currentModifiers & ModifierKeys::leftButtonModifier)
      {
          ev.xbutton.button = Button1;
          ev.xbutton.state |= Button1Mask;
      }
      else if (currentModifiers & ModifierKeys::rightButtonModifier)
      {
          ev.xbutton.button = Button3;
          ev.xbutton.state |= Button3Mask;
      }
      else if (currentModifiers & ModifierKeys::middleButtonModifier)
      {
          ev.xbutton.button = Button2;
          ev.xbutton.state |= Button2Mask;
      }
  }

  void translateJuceToXMotionModifiers (const MouseEvent& e,
                                         XEvent& ev)
  {
      int currentModifiers = e.mods.getRawFlags ();
      if (currentModifiers & ModifierKeys::leftButtonModifier)
      {
          ev.xmotion.state |= Button1Mask;
      }
      else if (currentModifiers & ModifierKeys::rightButtonModifier)
      {
          ev.xmotion.state |= Button3Mask;
      }
      else if (currentModifiers & ModifierKeys::middleButtonModifier)
      {
          ev.xmotion.state |= Button2Mask;
      }
  }

  void translateJuceToXCrossingModifiers (const MouseEvent& e,
                                           XEvent& ev)
  {
      int currentModifiers = e.mods.getRawFlags ();
      if (currentModifiers & ModifierKeys::leftButtonModifier)
      {
          ev.xcrossing.state |= Button1Mask;
      }
      else if (currentModifiers & ModifierKeys::rightButtonModifier)
      {
          ev.xcrossing.state |= Button3Mask;
      }
      else if (currentModifiers & ModifierKeys::middleButtonModifier)
      {
          ev.xcrossing.state |= Button2Mask;
      }
  }

  void translateJuceToXMouseWheelModifiers (const MouseEvent& e,
                                             const float increment,
                                             XEvent& ev)
  {
      if (increment < 0)
      {
          ev.xbutton.button = Button5;
          ev.xbutton.state |= Button5Mask;
      }
      else if (increment > 0)
      {
          ev.xbutton.button = Button4;
          ev.xbutton.state |= Button4Mask;
      }
  }
#endif


#ifdef JUCE_MAC
// On mac it is not easy to reliable position the VST GUI - it appears at top left of parent window. 
// This class allows the mac Jost to have a special window on top of the VST plugin editor that is positioned correctly.
class MacVSTGUIPositionHelperWindow  : public DocumentWindow
{        
public:
    MacVSTGUIPositionHelperWindow(BasePlugin* plugin_, int topleftX, int topleftY);        
    ~MacVSTGUIPositionHelperWindow();
    /** @internal */
    void mouseDown (const MouseEvent& e) {};
    /** @internal */
    void mouseDrag (const MouseEvent& e) {};
    /** @internal */
    void mouseUp (const MouseEvent& e) {};
    /** @internal */
    void mouseWheelMove (const MouseEvent& e, float incrementX, float incrementY) {};
    /** @internal */
    bool keyPressed (const KeyPress &key) { return false; };
    
protected:
    BasePlugin* plugin;
};

MacVSTGUIPositionHelperWindow::MacVSTGUIPositionHelperWindow(BasePlugin* plugin_, int topleftX, int topleftY)
: 
    DocumentWindow (T(""), Colours::floralwhite, false),
    plugin(plugin_)
{
    setTitleBarHeight(0);

    setResizable (false, false); 

    int editorWidth;
    int editorHeight;
    plugin->getEditorSize (editorWidth, editorHeight);
    setSize(editorWidth, editorHeight);
    setTopLeftPosition(topleftX, topleftY);
    setVisible (true);
}

MacVSTGUIPositionHelperWindow::~MacVSTGUIPositionHelperWindow()
{

}

#endif

//==============================================================================
VstPluginExternalEditor::VstPluginExternalEditor (BasePlugin* plugin_,
                                                  VstPluginWindow* window_)
  : PluginEditorComponent (plugin_),
#if defined(LINUX)
    eventProc (0),
#endif
    handle (0),
    window (window_),
    editorWidth (0),
    editorHeight (0),
    offsetX (0),
    offsetY (0)
#ifdef JUCE_MAC
	, vstGuiWindow(0)
#endif
{
    DBG ("VstPluginExternalEditor::VstPluginExternalEditor");
    
    setWantsKeyboardFocus (true);
    setVisible (true);

#if defined(LINUX)
    plugin->openEditor (window->getWindowHandle (), display);

    handle = getChildWindow ((Window) window->getWindowHandle ());
    if (handle)
        eventProc = (EventProcPtr) obtainPropertyFromXWindow (handle,
                                                              XInternAtom (display, "_XEventProc", false));

#elif defined(_WIN32)
    plugin->openEditor (window->getWindowHandle (), (void*) 0);

	handle = GetWindow ((HWND) window->getWindowHandle(), GW_CHILD);
#endif

    if (editorWidth <= 0 || editorHeight <= 0)
        plugin->getEditorSize (editorWidth, editorHeight);

    jassert (editorWidth > 0 && editorHeight > 0);
    setSize (editorWidth, editorHeight);

    offsetX = window->getBorderThickness().getLeft ();
    offsetY = window->getTitleBarHeight()
              + window->getMenuBarHeight()
              + window->getBorderThickness().getTop ();
    
    if (handle)
    {
#if defined(LINUX)
        XResizeWindow (display, handle, editorWidth, editorHeight);
        XMoveWindow (display, handle, offsetX, offsetY);
#elif defined (_WIN32)
		MoveWindow (handle, offsetX, offsetY, editorWidth, editorHeight, true); 
#endif
    }
    
#ifdef JUCE_MAC
    setGuiWindow(new MacVSTGUIPositionHelperWindow(plugin, window->getX() + offsetX, window->getY() + offsetY));
    showGUI(true);
#endif

	repaint ();

	startTimer (1000 / 10);
}

#ifdef JUCE_MAC
// These are implemented in juce_mac_NSViewComponentPeer.mm
extern void* GetWindowRefFromComponent(Component*); // The VST API requires a WindowRef to put the GUI in.
extern void SetAsChildComponent(Component* parent, Component* child); // in order for our GUI to draw in the right place, and remain on top of the Jost editor window, our overlay window needs to be made a child window.

void VstPluginExternalEditor::setGuiWindow(MacVSTGUIPositionHelperWindow* newone)
{
    if (vstGuiWindow)
    {
        vstGuiWindow->setContentComponent(0, false);
        delete vstGuiWindow;
    }
    
    handle = 0;
    vstGuiWindow = newone;
    if (vstGuiWindow)
    {
		handle = GetWindowRefFromComponent(vstGuiWindow);
		SetAsChildComponent(window, vstGuiWindow);
    }
}

void VstPluginExternalEditor::showGUI(bool bVisible)
{
	if (vstGuiWindow)
    {
		if (bVisible)
		{
			if (vstGuiWindow)
			{
				vstGuiWindow->setSize(editorWidth, editorHeight);
				plugin->openEditor (handle, (void*) 0);        
				repaint();
				vstGuiWindow->repaint();
			}
		}
		else
		{
			vstGuiWindow->setSize(0, 0);
			plugin->closeEditor ();        
		}
	}
}
#endif // JUCE_MAC

VstPluginExternalEditor::~VstPluginExternalEditor ()
{
    DBG ("VstPluginExternalEditor::~VstPluginExternalEditor");

    if (isTimerRunning())
        stopTimer();

#if defined(LINUX)
#elif defined(_WIN32)
#endif

    if (plugin)
        plugin->closeEditor ();

#ifdef JUCE_MAC    
    setGuiWindow(0);
#endif // JUCE_MAC    
}

//==============================================================================
void VstPluginExternalEditor::resized ()
{
    offsetX = window->getBorderThickness().getLeft ();
    offsetY = window->getTitleBarHeight()
              + window->getMenuBarHeight()
              + window->getBorderThickness().getTop ();
    
    if (handle)
    {
#if defined(LINUX)
        if (isWindowVisible (handle))
            XMoveWindow (display, handle, offsetX, offsetY);
#elif defined(_WIN32)
		HWND hwnd;
		hwnd = GetWindow((HWND) window->getWindowHandle(), GW_CHILD);

    	MoveWindow (hwnd, offsetX, offsetY, editorWidth, editorHeight, true);
#endif
    }

	repaint ();
}

//==============================================================================
void VstPluginExternalEditor::mouseEnter (const MouseEvent& e)
{
#if defined(LINUX)
    if (! handle) return;

    XEvent ev;
    zerostruct (ev);
    ev.xcrossing.display = display;
    ev.xcrossing.type = EnterNotify;
    ev.xcrossing.window = handle;
    ev.xcrossing.root = RootWindow (display, DefaultScreen (display));
    ev.xcrossing.time = CurrentTime;
    ev.xcrossing.x = e.x;
    ev.xcrossing.y = e.y;
    ev.xcrossing.x_root = e.getScreenX ();
    ev.xcrossing.y_root = e.getScreenY ();
    ev.xcrossing.mode = NotifyNormal; // NotifyGrab, NotifyUngrab
    ev.xcrossing.detail = NotifyAncestor; // NotifyVirtual, NotifyInferior, NotifyNonlinear,NotifyNonlinearVirtual

    translateJuceToXCrossingModifiers (e, ev);

    sendEventToChild (& ev);
#endif
}

//==============================================================================
void VstPluginExternalEditor::mouseExit (const MouseEvent& e)
{
#if defined(LINUX)
    if (! handle) return;

    XEvent ev;
    zerostruct (ev);
    ev.xcrossing.display = display;
    ev.xcrossing.type = LeaveNotify;
    ev.xcrossing.window = handle;
    ev.xcrossing.root = RootWindow (display, DefaultScreen (display));
    ev.xcrossing.time = CurrentTime;
    ev.xcrossing.x = e.x;
    ev.xcrossing.y = e.y;
    ev.xcrossing.x_root = e.getScreenX ();
    ev.xcrossing.y_root = e.getScreenY ();
    ev.xcrossing.mode = NotifyNormal; // NotifyGrab, NotifyUngrab
    ev.xcrossing.detail = NotifyAncestor; // NotifyVirtual, NotifyInferior, NotifyNonlinear,NotifyNonlinearVirtual
    ev.xcrossing.focus = hasKeyboardFocus (true); // TODO - yes ?

    translateJuceToXCrossingModifiers (e, ev);

    sendEventToChild (& ev);
#endif
}

//==============================================================================
void VstPluginExternalEditor::mouseMove (const MouseEvent& e)
{
#if defined(LINUX)
    if (! handle) return;

    XEvent ev;
    zerostruct (ev);
    ev.xmotion.display = display;
    ev.xmotion.type = MotionNotify;
    ev.xmotion.window = handle;
    ev.xmotion.root = RootWindow (display, DefaultScreen (display));
    ev.xmotion.time = CurrentTime;
    ev.xmotion.is_hint = NotifyNormal;
    ev.xmotion.x = e.x;
    ev.xmotion.y = e.y;
    ev.xmotion.x_root = e.getScreenX ();
    ev.xmotion.y_root = e.getScreenY ();

    sendEventToChild (& ev);
#endif
}

//==============================================================================
void VstPluginExternalEditor::mouseDown (const MouseEvent& e)
{
#if defined(LINUX)
    if (! handle) return;

    XEvent ev;
    zerostruct (ev);
    ev.xbutton.display = display;
    ev.xbutton.type = ButtonPress;
    ev.xbutton.window = handle;
    ev.xbutton.root = RootWindow (display, DefaultScreen (display));
    ev.xbutton.time = CurrentTime;
    ev.xbutton.x = e.x;
    ev.xbutton.y = e.y;
    ev.xbutton.x_root = e.getScreenX ();
    ev.xbutton.y_root = e.getScreenY ();

    translateJuceToXButtonModifiers (e, ev);

    sendEventToChild (& ev);
#endif
}

//==============================================================================
void VstPluginExternalEditor::mouseDrag (const MouseEvent& e)
{
#if defined(LINUX)
    if (! handle) return;

    XEvent ev;
    zerostruct (ev);
    ev.xmotion.display = display;
    ev.xmotion.type = MotionNotify;
    ev.xmotion.window = handle;
    ev.xmotion.root = RootWindow (display, DefaultScreen (display));
    ev.xmotion.time = CurrentTime;
    ev.xmotion.x = e.x ;
    ev.xmotion.y = e.y;
    ev.xmotion.x_root = e.getScreenX ();
    ev.xmotion.y_root = e.getScreenY ();
    ev.xmotion.is_hint = NotifyNormal;

    translateJuceToXMotionModifiers (e, ev);

    sendEventToChild (& ev);
#endif
}

//==============================================================================
void VstPluginExternalEditor::mouseUp (const MouseEvent& e)
{
#if defined(LINUX)
    if (! handle) return;

    XEvent ev;
    zerostruct (ev);
    ev.xbutton.display = display;
    ev.xbutton.type = ButtonRelease;
    ev.xbutton.window = handle;
    ev.xbutton.root = RootWindow (display, DefaultScreen (display));
    ev.xbutton.time = CurrentTime;
    ev.xbutton.x = e.x;
    ev.xbutton.y = e.y;
    ev.xbutton.x_root = e.getScreenX ();
    ev.xbutton.y_root = e.getScreenY ();

    translateJuceToXButtonModifiers (e, ev);

    sendEventToChild (& ev);
#endif
}

//==============================================================================
void VstPluginExternalEditor::mouseWheelMove (const MouseEvent& e,
                                              float incrementX,
                                              float incrementY)
{
#if defined(LINUX)
    if (! handle) return;

    XEvent ev;
    zerostruct (ev);
    ev.xbutton.display = display;
    ev.xbutton.type = ButtonPress;
    ev.xbutton.window = handle;
    ev.xbutton.root = RootWindow (display, DefaultScreen (display));
    ev.xbutton.time = CurrentTime;
    ev.xbutton.x = e.x;
    ev.xbutton.y = e.y;
    ev.xbutton.x_root = e.getScreenX ();
    ev.xbutton.y_root = e.getScreenY ();

    translateJuceToXMouseWheelModifiers (e, incrementY, ev);

    sendEventToChild (& ev);

    // TODO - put a usleep here ?

    ev.xbutton.type = ButtonRelease;
    sendEventToChild (& ev);
#endif
}

bool VstPluginExternalEditor::keyPressed (const KeyPress &key)
{
#if defined(LINUX)
    if (! handle) return false;

    XEvent ev;
    zerostruct (ev);

    ev.xkey.type = 2; // KeyPress
    ev.xkey.display = display;
    ev.xkey.window = handle;
    ev.xkey.root = RootWindow (display, DefaultScreen (display));
    ev.xkey.subwindow = None;
    ev.xkey.time = CurrentTime;
//    ev.xkey.x = e.x;
//    ev.xkey.y = e.y;
//    ev.xkey.x_root = e.getScreenX ();
//    ev.xkey.y_root = e.getScreenY ();
//    ev.xkey.state = e.y;
    ev.xkey.keycode = key.getKeyCode();
    ev.xkey.same_screen = True;

    sendEventToChild (& ev);
    
    return true;

#else

	return false;

#endif
}

//==============================================================================
void VstPluginExternalEditor::filesDropped (const StringArray& filenames,
                                            int mouseX,
                                            int mouseY)
{
    DBG ("VstPluginExternalEditor::filesDropped");
}

//==============================================================================
void VstPluginExternalEditor::visibilityChanged ()
{
    if (isShowing())
    {
#if defined(LINUX)
        if (handle) XMapRaised (display, handle);
#endif
    }
    else
    {
#if defined(LINUX)
        if (handle) XUnmapWindow (display, handle);
#endif
    }
}

//==============================================================================
void VstPluginExternalEditor::timerCallback ()
{
    if (plugin)
        plugin->idleEditor ();
}

void VstPluginExternalEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);

#if defined(LINUX)
    if (handle)
    {
        Rectangle clip = g.getClipBounds ();

        XEvent ev;
        zerostruct (ev);
        ev.xexpose.type = Expose;
        ev.xexpose.display = display;
        ev.xexpose.window = handle;

        ev.xexpose.x = clip.getX();
        ev.xexpose.y = clip.getY();
        ev.xexpose.width = clip.getWidth();
        ev.xexpose.height = clip.getHeight();

        sendEventToChild (& ev);
	}
#endif
}

void VstPluginExternalEditor::internalRepaint (int x, int y, int w, int h)
{
/*
#ifdef LINUX
    if (handle)
    {
        XEvent ev;
        zerostruct (ev);
        ev.xexpose.type = Expose;
        ev.xexpose.display = display;
        ev.xexpose.window = handle;

        ev.xexpose.x = x;
        ev.xexpose.y = y;
        ev.xexpose.width = w;
        ev.xexpose.height = h;

        sendEventToChild (& ev);
    }
#endif
*/
    Component::internalRepaint (x, y, w, h);
}

//==============================================================================
int VstPluginExternalEditor::getPreferredWidth ()
{
    int width, height;

    if (plugin)
        plugin->getEditorSize (width, height);

    return width; // editorWidth
}

int VstPluginExternalEditor::getPreferredHeight ()
{
    int width, height;

    if (plugin)
        plugin->getEditorSize (width, height);

    return height; // editorHeight
}

bool VstPluginExternalEditor::isResizable ()
{
    return false;
}

void VstPluginExternalEditor::updateWindowPosition (const int x, const int y)
{
#if defined(LINUX)
    if (! handle) return;

    XEvent ev;
    zerostruct (ev);
    ev.xgravity.type = GravityNotify;
    ev.xgravity.display = display;
    ev.xgravity.window = handle;
    ev.xgravity.event = (Window) window->getWindowHandle ();
    ev.xgravity.x = x;
    ev.xgravity.y = y;

    // DBG ("Window Position Updated to: " + String (x) + " " + String (y));

    sendEventToChild (& ev);
#endif
    
#ifdef JUCE_MAC
    if (vstGuiWindow)
        vstGuiWindow->setTopLeftPosition(window->getX() + offsetX, window->getY() + offsetY);
#endif
}

//==============================================================================
#if defined(LINUX)
void VstPluginExternalEditor::sendEventToChild (XEvent* event)
{
    if (eventProc)
    {
        // if the plugin publish a event procedure, so it doesn't have
        // a message thread running, pass the event directly
        eventProc (event);
    }
    else
    {
        // if the plugin have a message thread running, then send events to
        // that window: it will be caught by the message thread !
        if (handle)
        {
            XSendEvent (display, handle, False, 0L, event);
            XFlush (display);
        }
    }
}

Window VstPluginExternalEditor::getChildWindow (Window windowToCheck)
{
    Window rootWindow, parentWindow;
    Window *childWindows;
    unsigned int nchildren;

    XQueryTree (display,
                windowToCheck,
                &rootWindow,
                &parentWindow,
                &childWindows,
                &nchildren);

    if (nchildren > 0 && childWindows)
    {
        Window returnWindow = childWindows [0];

        XFree (childWindows);

        return returnWindow;
    }
    
    if (childWindows)
        XFree (childWindows);

    return 0;
}

bool VstPluginExternalEditor::isWindowVisible (Window windowToCheck)
{
    XWindowAttributes wsa;

    XGetWindowAttributes (display, windowToCheck, &wsa);

    return wsa.map_state == IsViewable;
}

#endif

