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

#ifndef __JOST_HOSTFILTERCOMPONENT_HEADER__
#define __JOST_HOSTFILTERCOMPONENT_HEADER__

#include "Config.h"
#include "HostFilterBase.h"
#include "ui/MainTabbedComponent.h"
#include "ui/BrowserTabbedComponent.h"
#include "ui/toolbar/ToolbarMainComponent.h"
#include "ui/plugins/PluginEditorWindowHolder.h"
#include "ui/windows/VstPluginWindow.h"
#include "ui/lookandfeel/ColourScheme.h"
#include "ui/lookandfeel/JostLookAndFeel.h"

//==============================================================================
/**
    This is the Component that our filter will use as its UI.

*/
class HostFilterComponent  : public AudioProcessorEditor,
                             public AudioParameterListener,
                             public ChangeListener,
                             public DragAndDropContainer,
                             public ApplicationCommandTarget,
                             public MenuBarModel,
                             public PluginEditorWindowHolder
{
public:

    //==============================================================================
    /** Constructor.
        When created, this will register itself with the filter for changes. It's
        safe to assume that the filter won't be deleted before this object is.
    */
    HostFilterComponent (HostFilterBase* const ownerFilter);

    /** Destructor. */
    ~HostFilterComponent ();

    //==============================================================================
    /** handy wrapper method to avoid having to cast the filter to a DemoJuceFilter
        every time we need it.. */
    HostFilterBase* getFilter() const { return (HostFilterBase*) getAudioProcessor(); }

    /** handy wrapper method to avoid having to unprotect the host */
    Host* getHost() const             { return getFilter()->host; }

    //==============================================================================
    void loadPluginFromFile (const File& file);

    //==============================================================================
    /** Return true if the editor is currently open */
    bool isPluginEditorWindowOpen (BasePlugin* plugin) const;

    /** Callback from tracks */
    void openPluginEditorWindow (BasePlugin* plugin);

    /** Callback from plugin window */
    void closePluginEditorWindow (BasePlugin* plugin);

    /** Callback from plugin window */
    void closePluginEditorWindows ();

    /** Callback (from audioMaster) to resize content component */
    void resizePluginEditorWindow (BasePlugin* plugin,
                                   const int width,
                                   const int height);

    /** Callback (from audioMaster) to repaint plugin editor window */
    void updatePluginEditorWindowDisplay ();

    //==============================================================================
    void clearComponents ();
    void rebuildComponents ();

    //==============================================================================
    /** Our demo filter is a ChangeBroadcaster, and will call us back when one of
        its parameters changes.
    */
    void changeListenerCallback (void* source);

    /** Parameter listener callback */
    void parameterChanged (AudioParameter* parameter, const int index);

    //==============================================================================
    /** Returns the names of the current menu bar */
    const StringArray getMenuBarNames ();

    /** Returns a popup menu for the current index */
    const PopupMenu getMenuForIndex (int menuIndex,
                                     const String& menuName);

    /** Someone selected a menu item */
    void menuItemSelected (int menuItemID,
                           int topLevelMenuIndex);

    //==============================================================================
    /** This should return the application as that is the topmost target */
    ApplicationCommandTarget* getNextCommandTarget();

    /** This should populate what this kind of target would like to perform */
    void getAllCommands (Array <CommandID>& commands);

    /** Returns informations on the commands */
    void getCommandInfo (const CommandID commandID, ApplicationCommandInfo& result);

    /** Perform the action associated to every command */
    bool perform (const InvocationInfo& info);

    //==============================================================================
    /** @internal */
    void paint (Graphics& g);
    /** @internal */
    void resized ();

    //==============================================================================
    void setBrowserVisible (const bool isVisible,
                            const bool positionLeft,
                            const bool issueResize = true);

private:

    //==============================================================================
    friend class HostFilterBase;

    TooltipWindow* tooltipWindow;
    JostLookAndFeel lookAndFeel;

    // toolbar component and factory
    Toolbar* toolbar;
    ToolbarMainItemFactory* factory;

    // main tabbed component (graph and mixer)
    MainTabbedComponent* main;
    
    // left/right browser
    BrowserTabbedComponent* browser;

    // left right navigator
    ViewportNavigator* navigator;

    // layout
    StretchableLayoutResizerBar* verticalDividerBar;
    StretchableLayoutResizerBar* horizontalDividerBar;
    StretchableLayoutManager verticalLayout;
    StretchableLayoutManager horizontalLayout;

    // resizable corner when plugin
    ResizableCornerComponent* resizer;
    ComponentBoundsConstrainer resizeLimits;

    // The shared plugin editor window
    OwnedArray<VstPluginWindow> pluginWindows;
};


#endif // __JUCETICE_VECTORCOMPONENT_H
