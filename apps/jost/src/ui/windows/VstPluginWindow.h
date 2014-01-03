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

#ifndef __JUCETICE_JOST_VSTPLUGINWINDOW_HEADER__
#define __JUCETICE_JOST_VSTPLUGINWINDOW_HEADER__

#include "../../Config.h"
#include "../../model/BasePlugin.h"
#include "../../model/plugins/VstPlugin.h"

class PluginEditorWindowHolder;
class PluginEditorComponent;
class VstPluginNativeEditor;
class VstPluginExternalEditor;
class VstPluginWindowContent;


//==============================================================================
/**
    Main window which will contain a Vst plugin editor component
*/
class VstPluginWindow : public DialogWindow,
                        public MenuBarModel
{
public:

    //==============================================================================
    /** Constructor */
    VstPluginWindow (PluginEditorWindowHolder* owner,
                     BasePlugin* plugin);

    /** Destructor */
    ~VstPluginWindow ();

    //==============================================================================
    /**
        Return the current selected plugin in this window.

        It can return 0 if there is no plugin selected in the current window.
    */
    BasePlugin* getPlugin () const                               { return plugin; }

    /**
        Set the new plugin that will be shown in this window.

        This function will take care of creating an editor component that goes
        inside this window, and will show the editor for the selected plugin.

        @param    plugin          vst plugin to show
    */
    void setPlugin (BasePlugin* plugin);

    //==============================================================================
    /** This will update all parameters in a glance */
    void updateParameters ();

    /** This will resize the window taking into account to have at
        least the specified dimension: of course it have to take into account
        about border and such
    */
    void resizeContentComponent (const int width,
                                 const int height,
                                 const bool limitHeight = false);

    //==============================================================================
    /** Returns the height of the menu bar */
    const int getMenuBarHeight () const;

    /** Returns the names of the current menu bar */
    const StringArray getMenuBarNames ();

    /** Returns a popup menu for the current index */
    const PopupMenu getMenuForIndex (int menuIndex,
                                     const String& menuName);

    /** Someone selected a menu item */
    void menuItemSelected (int menuItemID,
                           int topLevelMenuIndex);

    //==============================================================================
	// internal routines for menu indexes
    int ourMenuIDToRealMenuID(int index)
    {
        return combinedMenuNames.indexOf(ourMenuNames[index]);
    }
    
    int pluginMenuIDToRealMenuID(int index)
    {
        return combinedMenuNames.indexOf(pluginMenuNames[index]);
    }
    
    int realMenuIDToOurMenuID(int index)
    {
        return ourMenuNames.indexOf(combinedMenuNames[index]);
    }
    
    int realMenuIDToPluginMenuID(int index)
    {
        return pluginMenuNames.indexOf(combinedMenuNames[index]);
    }

    //==============================================================================
    /** @internal */
    void closeButtonPressed ();
    /** @internal */
    void broughtToFront ();
    /** @internal */
    void minimisationStateChanged (bool isNowMinimised);
    /** @internal */
    void filesDropped (const StringArray& filenames, int mouseX, int mouseY);
    /** @internal */
    void paint (Graphics& g);
    /** @internal */
    void resized ();
    /** @internal */
    void moved ();

protected:

    /** load presets */
    void loadPreset ();
    /** save presets */
    void savePreset ();

    BasePlugin* plugin;

    PluginEditorWindowHolder* owner;

    PluginEditorComponent* specialEditor;
    VstPluginNativeEditor* nativeEditor;
    VstPluginExternalEditor* externalEditor;
    VstPluginWindowContent* content;
    
    StringArray pluginMenuNames;
    StringArray ourMenuNames;
    StringArray combinedMenuNames;
};


#endif
