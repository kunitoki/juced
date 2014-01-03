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

#ifndef __JUCETICE_JOST_PLUGINEDITORCOMPONENT_HEADER__
#define __JUCETICE_JOST_PLUGINEDITORCOMPONENT_HEADER__

#include "../../model/PluginLoader.h"


//==============================================================================
/**
    This is the base interface for the editor, holding a plugin
*/
class PluginEditorComponent  : public AudioProcessorEditor
{
public:

    //==============================================================================
    virtual ~PluginEditorComponent ();

    //==============================================================================
    /** Return the preferred width for the editor */
    virtual int getPreferredWidth ()                { return 1; }

    /** Return the preferred height for the editor */
    virtual int getPreferredHeight ()               { return 1; }

    /** Return the preferred height for the editor */
    virtual bool isResizable ()                     { return true; }

    //==============================================================================
    /** This will be called by the host when it needs to update the parameters of
        the editor, especially after a program change. */
    virtual void updateParameters () {}

    //==============================================================================
    // Support for adding menu items when this component is used within a window.
    // The window will call these and merge in any plugin items.
    virtual bool getMenuBarNames(StringArray& names)                     { return false; }
    virtual bool getMenuForMenuName(const String& menuName, PopupMenu& menu) { return false; }
    virtual void menuItemSelected(const String& menuName, int menuItemID) { }

protected:

    //==============================================================================
    void updateOuterWindowSize (int width, int height);

    //==============================================================================
    PluginEditorComponent (BasePlugin* plugin_);

    //==============================================================================
    BasePlugin* plugin;
};


#endif // __JUCETICE_JOST_PLUGINEDITORCOMPONENT_HEADER__
