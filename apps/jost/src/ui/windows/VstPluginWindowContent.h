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

#ifndef __JUCETICE_VSTPLUGINWINDOWCONTENT_HEADER__
#define __JUCETICE_VSTPLUGINWINDOWCONTENT_HEADER__

#include "VstPluginExternalEditor.h"
#include "VstPluginNativeEditor.h"
#include "VstPluginWindowTabPanel.h"


class VstPluginWindow;
class HostFilterComponent;
class PluginEditorWindowHolder;


//==============================================================================
/**
    This is the main content component for the vst window
*/
class VstPluginWindowContent : public Component
{
public:
    //==============================================================================
    VstPluginWindowContent (PluginEditorWindowHolder* owner,
                            BasePlugin* plugin,
                            VstPluginWindow* window,
                            VstPluginNativeEditor* nativeEditor,
                            VstPluginExternalEditor* externalEditor);

    ~VstPluginWindowContent ();

    //==============================================================================
    void resized ();

    //==============================================================================
    int getCurrentTabIndex () const;

    void setCurrentTabIndex (const int tabIndex);

    //==============================================================================
    int getTabbedPanelHeight () const;

    //==============================================================================
    void activateMidiKeyboard (const bool isActive);

    bool hasMidiKeyboardOpen () const                { return midiKeyboard != 0; }

    int getMidiKeyboardHeight () const               { return 40; }

protected:

    PluginEditorWindowHolder* owner;
    BasePlugin* plugin;

    VstPluginWindow* window;

    VstPluginWindowTabPanel* mainPanel;
    MidiKeyboardComponent* midiKeyboard;
};


#endif
