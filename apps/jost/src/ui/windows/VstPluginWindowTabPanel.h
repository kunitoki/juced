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

#ifndef __JUCETICE_VSTPLUGINWINDOWTABPANEL_HEADER__
#define __JUCETICE_VSTPLUGINWINDOWTABPANEL_HEADER__

#include "VstPluginExternalEditor.h"
#include "VstPluginNativeEditor.h"


class VstPluginWindow;
class VstPluginWindowContent;
class HostFilterComponent;
class PluginEditorWindowHolder;


//==============================================================================
/**
    Tabbed panel which owns the External / Native GUI for plugins and
    also will host pages for fast tweaking, options... whatever
*/
class VstPluginWindowTabPanel : public TabbedComponent
{
public:
    //==============================================================================
    VstPluginWindowTabPanel (PluginEditorWindowHolder* owner_,
                             BasePlugin* plugin_,
                             VstPluginWindow* window,
                             VstPluginWindowContent* content_,
                             VstPluginNativeEditor* nativeEditor_,
                             VstPluginExternalEditor* externalEditor_);

    ~VstPluginWindowTabPanel ();

    //==============================================================================
    void currentTabChanged (const int newCurrentTabIndex,
                            const String &newCurrentTabName);

protected:

    PluginEditorWindowHolder* owner;
    BasePlugin* plugin;

    VstPluginWindow* window;
    VstPluginWindowContent* content;
    VstPluginNativeEditor* nativeEditor;
    VstPluginExternalEditor* externalEditor;

    Viewport* viewport;
};


#endif
