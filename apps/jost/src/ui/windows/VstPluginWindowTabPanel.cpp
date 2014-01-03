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

#include "VstPluginWindowTabPanel.h"
#include "VstPluginWindow.h"
#include "../../HostFilterComponent.h"


//==============================================================================
VstPluginWindowTabPanel::VstPluginWindowTabPanel (PluginEditorWindowHolder* owner_,
                                                  BasePlugin* plugin_,
                                                  VstPluginWindow* window_,
                                                  VstPluginWindowContent* content_,
                                                  VstPluginNativeEditor* nativeEditor_,
                                                  VstPluginExternalEditor* externalEditor_)
  : TabbedComponent (TabbedButtonBar::TabsAtBottom),
    owner (owner_),
    plugin (plugin_),
    window (window_),
    content (content_),
    nativeEditor (nativeEditor_),
    externalEditor (externalEditor_),
    viewport (0)
{
    DBG ("VstPluginWindowTabPanel::VstPluginWindowTabPanel");
    
    Colour backgroundColour = window->getBackgroundColour ();
    int lastSelectedTab = plugin->getIntValue (PROP_WINDOWPAGE, 0);

    // external GUI
    if (externalEditor)
        addTab (T("Interface"), backgroundColour, externalEditor, true);

    // native GUI
    if (nativeEditor)
    {
        viewport = new Viewport (String::empty);
        viewport->setScrollBarsShown (true, false);
        viewport->setViewedComponent (nativeEditor);
        addTab (T("Parameters"), backgroundColour, viewport, true);
    }

    // change last saved tab
    setCurrentTabIndex (jmax (0, jmin (1, lastSelectedTab)));
}

VstPluginWindowTabPanel::~VstPluginWindowTabPanel ()
{
    DBG ("VstPluginWindowTabPanel::~VstPluginWindowTabPanel");

    clearTabs ();
}

//==============================================================================
void VstPluginWindowTabPanel::currentTabChanged (const int newCurrentTabIndex,
                                                 const String &newCurrentTabName)
{
    DBG ("VstPluginWindowTabPanel::currentTabChanged " + newCurrentTabName);

    VstPluginWindow* window = findParentComponentOfClass<VstPluginWindow> ();
    if (window)
    {
        int lastPageIndex = 0;

        // plugins have an external XLib gui editor
        if (newCurrentTabName == T("Interface"))
        {
            if (externalEditor)
            {
                window->setResizable (false, false);
                window->resizeContentComponent (externalEditor->getPreferredWidth (),
                                                externalEditor->getPreferredHeight (),
                                                false);
#ifdef JUCE_MAC
				externalEditor->showGUI(true);
#else				
				plugin->openEditor(window->getWindowHandle (), (void*) 0);
				externalEditor->resized();
#endif
            }
        }
        // plugins have internal parameters gui
        else if (newCurrentTabName == T("Parameters"))
        {
            if (nativeEditor)
            {
                window->setResizable (true, true);
                window->resizeContentComponent (nativeEditor->getPreferredWidth (),
                                                nativeEditor->getPreferredHeight () + 1,
                                                true);

#ifdef JUCE_MAC
				externalEditor->showGUI(false);
#else				
				plugin->closeEditor();
#endif
            }

            // lastPageIndex = (externalEditor) ? 1 : 0;
			lastPageIndex = 0;
        }

        // save property
        plugin->setValue (PROP_WINDOWPAGE, lastPageIndex);
    }
}
