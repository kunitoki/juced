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

#ifndef __JUCETICE_JOST_PLUGINEDITORWINDOWHOLDER_HEADER__
#define __JUCETICE_JOST_PLUGINEDITORWINDOWHOLDER_HEADER__

#include "../../model/PluginLoader.h"


//==============================================================================
/**
    This is the base interface for the editor, holding a plugin
*/
class PluginEditorWindowHolder
{
public:

    //==============================================================================
    virtual ~PluginEditorWindowHolder () {}

    //==============================================================================
    /** Return true if the editor is currently open */
    virtual bool isPluginEditorWindowOpen (BasePlugin* plugin) const = 0;

    /** Callback from tracks */
    virtual void openPluginEditorWindow (BasePlugin* plugin) = 0;

    /** Callback from plugin window */
    virtual void closePluginEditorWindow (BasePlugin* plugin) = 0;

    /** Callback from plugin window */
    virtual void closePluginEditorWindows () = 0;

    /** Callback (from audioMaster) to resize content component */
    virtual void resizePluginEditorWindow (BasePlugin* plugin,
                                            const int width,
                                            const int height) = 0;

protected:
    
    PluginEditorWindowHolder() {}
};


#endif // __JUCETICE_JOST_PLUGINEDITORWINDOWHOLDER_HEADER__
