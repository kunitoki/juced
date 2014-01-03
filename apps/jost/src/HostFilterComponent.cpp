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

#include "HostFilterComponent.h"
#include "resources/Resources.h"

#ifndef JOST_VST_PLUGIN
  #include "wrapper/Standalone/juce_AudioFilterStreamer.h"
  #include "wrapper/Standalone/juce_StandaloneFilterWindow.h"
#endif

//==============================================================================
HostFilterComponent::HostFilterComponent (HostFilterBase* const ownerFilter_)
    : AudioProcessorEditor (ownerFilter_),
      tooltipWindow (0),
      toolbar (0),
      main (0),
      browser (0),
      verticalDividerBar (0),
      horizontalDividerBar (0)
{
    DBG ("HostFilterComponent::HostFilterComponent");

    Config* config = Config::getInstance();

    // global look and feel
    lookAndFeel.readColourFromConfig ();
    LookAndFeel::setDefaultLookAndFeel (&lookAndFeel);

    // register tooltip window
    tooltipWindow = 0;
    if (config->showTooltips)
        tooltipWindow = new TooltipWindow (0, 1000);

    // register ourselves with the plugin - it will use its ChangeBroadcaster base
    // class to tell us when something has changed.
    getFilter()->addChangeListener (this);
    // getFilter()->addListenerToParameters (this);

    // add toolbar / main tabbed component / tabbed browser / divider
    factory = new ToolbarMainItemFactory (this);
    
    addAndMakeVisible (toolbar = new Toolbar ());
    addAndMakeVisible (main = new MainTabbedComponent (this));
    addAndMakeVisible (browser = new BrowserTabbedComponent (this));
    addAndMakeVisible (navigator = new ViewportNavigator (0));

    addAndMakeVisible (resizer = new ResizableCornerComponent (this, &resizeLimits));
    resizeLimits.setSizeLimits (150, 150, 1280, 1024);

    // And use our item factory to add a set of default icons to it...
    toolbar->setVertical (false);
    if (config->toolbarSet != String::empty)
        toolbar->restoreFromString (*factory, config->toolbarSet);
    else
        toolbar->addDefaultItems (*factory);

    // build layout
    setBrowserVisible (config->showBrowser,
                       config->browserLeft,
                       false);

    // set its size
    int initialWidth = 800, initialHeight = 600;
    setSize (initialWidth, initialHeight);

    // get the command manager
    CommandManager* commandManager = CommandManager::getInstance();
    commandManager->registerAllCommandsForTarget (this);
    commandManager->setFirstCommandTarget (this);
#ifdef JOST_VST_PLUGIN
    addKeyListener (commandManager->getKeyMappings());
#endif

    // start up if first time !
    if (config->firstTime)
        commandManager->invokeDirectly (CommandIDs::appAbout, false);

    // register as listener to transport
    getFilter()->getTransport()->addChangeListener (this);
}

//==============================================================================
HostFilterComponent::~HostFilterComponent()
{
    DBG ("HostFilterComponent::~HostFilterComponent");

    // register as listener to transport
    getFilter()->getTransport()->removeChangeListener (this);

    // deregister ouselves from the plugin (in this case the host)
    getFilter()->removeChangeListener (this);
    // getFilter()->removeListenerToParameters (this);

    // save toolbar layout
    Config::getInstance()->toolbarSet = toolbar->toString ();

    // close and free editor window
    closePluginEditorWindows ();

    // clear all childrens and objects
    clearComponents();
//     deleteAndZero (navigator);
    deleteAndZero (toolbar);
    deleteAndZero (factory);
    deleteAndZero (main);
    deleteAndZero (browser);
    deleteAndZero (verticalDividerBar);
    deleteAndZero (horizontalDividerBar);
    deleteAndZero (tooltipWindow);
    deleteAndZero (resizer);

    // clear command manager commands... save keymappings before this point !
    CommandManager* commandManager = CommandManager::getInstance();
    commandManager->setFirstCommandTarget (0);
    commandManager->clearCommands ();
}

//==============================================================================
void HostFilterComponent::resized()
{
    if (! main->areComponentsCreated ())
        rebuildComponents ();

    int toolbarHeight = JOST_DEFAULT_TOOLBAR_HEIGHT;
    if (toolbar)
        toolbar->setBounds (0, 0, getWidth(), toolbarHeight);
    else
        toolbarHeight = 0;

    Config* config = Config::getInstance();

    if (config->showBrowser)
    {
        if (config->browserLeft)
        {
            Component* vcomps[] = { 0, verticalDividerBar, main };
            verticalLayout.layOutComponents (vcomps, 3,
                                             0,
                                             toolbarHeight,
                                             getWidth(),
                                             getHeight() - toolbarHeight,
                                             false,     // lay out side-by-side
                                             true);     // resize the components' heights as well as widths

            Component* hcomps[] = { browser, horizontalDividerBar, navigator };
            horizontalLayout.layOutComponents (hcomps, 3,
                                               verticalLayout.getItemCurrentPosition (0),
                                               toolbarHeight,
                                               verticalLayout.getItemCurrentPosition (1),
                                               getHeight() - toolbarHeight,
                                               true,     // lay out side-by-side
                                               true);     // resize the components' heights as well as widths
        }
        else
        {
            Component* vcomps[] = { main, verticalDividerBar, 0 };
            verticalLayout.layOutComponents (vcomps, 3,
                                             0,
                                             toolbarHeight,
                                             getWidth(),
                                             getHeight() - toolbarHeight,
                                             false,     // lay out side-by-side
                                             true);     // resize the components' heights as well as widths

            Component* hcomps[] = { browser, horizontalDividerBar, navigator };
            horizontalLayout.layOutComponents (hcomps, 3,
                                               verticalLayout.getItemCurrentPosition (2),
                                               toolbarHeight,
                                               getWidth() - verticalLayout.getItemCurrentPosition (2),
                                               getHeight() - toolbarHeight,
                                               true,     // lay out side-by-side
                                               true);     // resize the components' heights as well as widths
        }
    }
    else
    {
        main->setBounds (0, toolbarHeight, getWidth(), getHeight() - toolbarHeight);
    }
    
    resizer->setBounds (getWidth() - 16, getHeight() - 16, 16, 16);
}

//==============================================================================
void HostFilterComponent::paint (Graphics& g)
{
#ifdef JOST_VST_PLUGIN
    g.fillAll (Config::getInstance ()->getColour (T("mainBackground")));
#endif
}

//==============================================================================
void HostFilterComponent::loadPluginFromFile (const File& file)
{
    DBG ("HostFilterComponent::loadPluginFromFile");

    GraphComponent* graph = main->getGraph ();

    if (graph) graph->loadAndAppendPlugin (file, 100, 100);
}

//==============================================================================
bool HostFilterComponent::isPluginEditorWindowOpen (BasePlugin* plugin) const
{
    for (int i = pluginWindows.size(); --i >= 0;)
    {
        VstPluginWindow* window = pluginWindows.getUnchecked (i);
        if (window && window->getPlugin() == plugin)
            return window->isVisible ();
    }
    return false;
}

void HostFilterComponent::openPluginEditorWindow (BasePlugin* plugin)
{
    DBG ("HostFilterComponent::openPluginEditorWindow");

    if (plugin)
    {
        VstPluginWindow* pluginWindow = 0;
        for (int i = pluginWindows.size(); --i >= 0;)
        {
            VstPluginWindow* window = pluginWindows.getUnchecked (i);
            if (window && window->getPlugin() == plugin)
            {
                pluginWindow = window;
                break;
            }
        }

        if (! pluginWindow)
        {
            pluginWindow = new VstPluginWindow (this, plugin);
            pluginWindows.add (pluginWindow);
        }
        else
        {
            if (pluginWindow->getPlugin () != plugin)
                pluginWindow->setPlugin (plugin);

            if (! pluginWindow->isVisible ())
                pluginWindow->setVisible (true);
            pluginWindow->toFront (false);
        }

        // save property with plugin
        plugin->setValue (PROP_WINDOWOPEN, 1);
    }
}

void HostFilterComponent::closePluginEditorWindow (BasePlugin* plugin)
{
    DBG ("HostFilterComponent::closePluginEditorWindow");

    for (int i = pluginWindows.size(); --i >= 0;)
    {
        VstPluginWindow* window = pluginWindows.getUnchecked (i);
        if (window && window->getPlugin() == plugin)
        {
            // save property with plugin
            plugin->setValue (PROP_WINDOWOPEN, 0);

            pluginWindows.removeObject (window, true);
            break;
        }
    }
}

void HostFilterComponent::closePluginEditorWindows()
{
    DBG ("HostFilterComponent::closePluginEditorWindows");

    pluginWindows.clear (true);
}

void HostFilterComponent::resizePluginEditorWindow (BasePlugin* plugin,
                                                    const int width,
                                                    const int height)
{
    DBG ("HostFilterComponent::resizePluginEditorWindow");

    for (int i = pluginWindows.size(); --i >= 0;)
    {
        VstPluginWindow* window = pluginWindows.getUnchecked (i);
        if (window && window->getPlugin() == plugin)
        {
            window->resizeContentComponent (width, height);
            break;
        }
    }
}

void HostFilterComponent::updatePluginEditorWindowDisplay ()
{
    for (int i = pluginWindows.size(); --i >= 0;)
        pluginWindows.getUnchecked (i)->repaint ();
}

//==============================================================================
void HostFilterComponent::clearComponents ()
{
    DBG ("HostFilterComponent::clearComponents");

    closePluginEditorWindows ();

    main->clearComponents ();
}

void HostFilterComponent::rebuildComponents ()
{
    DBG ("HostFilterComponent::rebuildComponents");

    // update navigator with an empty view !
    if (navigator)
        navigator->setViewedViewport (0);

    // recreate main components !
    main->rebuildComponents ();
    
    // update navigator with the main area viewport !
    if (navigator) 
    {
        navigator->setViewedViewport (main->getGraphViewport ());
        navigator->updateVisibleArea (false);
    }
}

//==============================================================================
void HostFilterComponent::setBrowserVisible (const bool isVisible,
                                             const bool positionLeft,
                                             const bool issueResize)
{
    DBG ("HostFilterComponent::setBrowserVisible");

    Config* config = Config::getInstance();
    config->showBrowser = isVisible;
    config->browserLeft = positionLeft;

    deleteAndZero (verticalDividerBar);
    deleteAndZero (horizontalDividerBar);
    verticalLayout.clearAllItems ();
    horizontalLayout.clearAllItems ();

    // show or not, checking for config
    browser->setVisible (config->showBrowser);
    navigator->setVisible (config->showBrowser);

    if (config->showBrowser)
    {
        // check for vertical position
        if (config->browserLeft)
        {
            browser->setOrientation (TabbedButtonBar::TabsAtLeft);

            verticalLayout.setItemLayout (0, 150, -0.8, 350);     // browser
            verticalLayout.setItemLayout (1, 2, 2, 2);            // divider bar
            verticalLayout.setItemLayout (2, -0.2, -1.0, -0.8);   // main area
        }
        else
        {
            browser->setOrientation (TabbedButtonBar::TabsAtRight);

            verticalLayout.setItemLayout (0, -0.2, -1.0, -0.8); // main area
            verticalLayout.setItemLayout (1, 2, 2, 2);          // divider bar
            verticalLayout.setItemLayout (2, 150, -0.8, 350);   // browser
        }

        verticalDividerBar = new StretchableLayoutResizerBar (&verticalLayout, 1, true);
        addAndMakeVisible (verticalDividerBar);

        // check for horizontal position
        horizontalLayout.setItemLayout (0, -0.1, -1.0, -0.8); // browser area
        horizontalLayout.setItemLayout (1, 2, 2, 2);          // divider bar
        horizontalLayout.setItemLayout (2, 150, 150, 150);    // navigator

        horizontalDividerBar = new StretchableLayoutResizerBar (&horizontalLayout, 1, false);
        addAndMakeVisible (horizontalDividerBar);
    }

    if (issueResize)
        resized ();
}

//==============================================================================
void HostFilterComponent::changeListenerCallback (void* source)
{
    if (source == this)
    {
        closePluginEditorWindows ();
    }
    else if (source == getFilter())
    {
        clearComponents ();
        rebuildComponents ();

        // reopen windows saved with session
        Host* host = getFilter()->host;
        for (int j = 0; j < host->getPluginsCount(); j++)
        {
            BasePlugin* plugin = host->getPluginByIndex (j);
            if (plugin && plugin->getIntValue (PROP_WINDOWOPEN, 0))
                openPluginEditorWindow (plugin);
        }

        resized ();
    }
    else if (source == getFilter()->getTransport())
    {
        // update transport !
        CommandManager::getInstance()->commandStatusChanged ();
    }
    else
    {
        for (int i = pluginWindows.size(); --i >= 0;)
        {
            VstPluginWindow* window = pluginWindows.getUnchecked (i);
            if (window)
                window->updateParameters ();
        }
    }
}

void HostFilterComponent::parameterChanged (AudioParameter* parameter, const int index)
{
    // DBG (T("PARAMETER ") + String (index) + T(" changed"));
}


//==============================================================================
// the window main menu
const StringArray HostFilterComponent::getMenuBarNames ()
{
    const tchar* const names[] = {
                                    CommandCategories::file,
                                    CommandCategories::audio,
                                    CommandCategories::about,
                                    0
    };

    return StringArray ((const tchar**) names);
}

// where the menu is constructed
const PopupMenu HostFilterComponent::getMenuForIndex (int menuIndex,
                                                      const String& menuName)
{
    PopupMenu menu;

    Config* config = Config::getInstance();
    CommandManager* commandManager = CommandManager::getInstance();

    switch (menuIndex)
    {
    case 0: // CommandCategories::file
        {
            PopupMenu recentSessionsSubMenu;
            config->recentSessions.createPopupMenuItems (recentSessionsSubMenu,
                                                         CommandIDs::recentSessions,
                                                         false,
                                                         true);

            PopupMenu recentPluginsSubMenu;
            config->recentPlugins.createPopupMenuItems (recentPluginsSubMenu,
                                                        CommandIDs::recentPlugins,
                                                        false,
                                                        true);

            menu.addCommandItem (commandManager, CommandIDs::sessionNew);
            menu.addCommandItem (commandManager, CommandIDs::sessionLoad);
            menu.addCommandItem (commandManager, CommandIDs::sessionSave);
            menu.addSubMenu (T("Recent sessions"), recentSessionsSubMenu);
            menu.addSeparator();
            menu.addCommandItem (commandManager, CommandIDs::pluginOpen);
            menu.addCommandItem (commandManager, CommandIDs::pluginClose);
            menu.addCommandItem (commandManager, CommandIDs::pluginClear);
            menu.addSubMenu (T("Recent plugins"), recentPluginsSubMenu);
            menu.addSeparator();
            menu.addCommandItem (commandManager, CommandIDs::appExit);
            break;
        }

    case 1: // CommandCategories::audio
        {
#ifndef JOST_VST_PLUGIN
            menu.addCommandItem (commandManager, CommandIDs::audioOptions);
            menu.addSeparator ();
#endif
            menu.addCommandItem (commandManager, CommandIDs::audioPlay);
            menu.addCommandItem (commandManager, CommandIDs::audioRecord);
            menu.addCommandItem (commandManager, CommandIDs::audioStop);
            menu.addCommandItem (commandManager, CommandIDs::audioRewind);
            break;
        }
    case 2: // CommandCategories::about
        {
            menu.addCommandItem (commandManager, CommandIDs::appAbout);
            break;
        }
    }

    return menu;
}

void HostFilterComponent::menuItemSelected (int menuItemID,
                                            int topLevelMenuIndex)
{
    Config* config = Config::getInstance();
    GraphComponent* graph = main->getGraph ();

    switch (topLevelMenuIndex)
    {
    case 0: // CommandCategories::file
        {
            // handle recent plugins selection
            int fileID = menuItemID - CommandIDs::recentPlugins;
            if (fileID >= 0 && fileID < config->recentPlugins.getNumFiles())
            {
                File fileToLoad = config->recentPlugins.getFile (fileID);

                if (graph)
                    graph->loadAndAppendPlugin (config->recentPlugins.getFile (fileID), 100, 100);

                break;
            }

            // handle recent session selection
            fileID = menuItemID - CommandIDs::recentSessions;
            if (fileID >= 0 && fileID < config->recentSessions.getNumFiles())
            {
                MemoryBlock fileData;
                File fileToLoad = config->recentSessions.getFile (fileID);

                if (fileToLoad.existsAsFile()
                    && fileToLoad.loadFileAsData (fileData))
                {
                    getFilter ()->setStateInformation (fileData.getData (), fileData.getSize());

                    Config::getInstance()->addRecentSession (fileToLoad);
                }
            }
            break;
        }
    }

    toFront (true);
}

//==============================================================================
// The following methods implement the ApplicationCommandTarget interface, allowing
// this window to publish a set of actions it can perform, and which can be mapped
// onto menus, keypresses, etc.
ApplicationCommandTarget* HostFilterComponent::getNextCommandTarget()
{
    return findFirstTargetParentComponent();
}

// this returns the set of all commands that this target can perform..
void HostFilterComponent::getAllCommands (Array <CommandID>& commands)
{
    const CommandID ids[] = {
                                CommandIDs::pluginOpen,
                                CommandIDs::pluginClose,
                                CommandIDs::pluginClear,
#ifndef JOST_VST_PLUGIN
                                CommandIDs::audioOptions,
#endif
                                CommandIDs::audioPlay,
                                CommandIDs::audioStop,
                                CommandIDs::audioRecord,
                                CommandIDs::audioRewind,
                                CommandIDs::audioLoop,

                                CommandIDs::sessionNew,
                                CommandIDs::sessionLoad,
                                CommandIDs::sessionSave,

                                CommandIDs::appToolbar,
                                CommandIDs::appBrowser,
                                CommandIDs::appFullScreen,
                                CommandIDs::appAbout,
                                CommandIDs::appExit
    };

    commands.addArray (ids, sizeof (ids) / sizeof (ids [0]));
}

// This method is used when something needs to find out the details about one of the commands
// that this object can perform..
void HostFilterComponent::getCommandInfo (const CommandID commandID, ApplicationCommandInfo& result)
{
    const int none = 0;
    const int cmd = ModifierKeys::commandModifier;
    // const int shift = ModifierKeys::shiftModifier;

    GraphComponent* graph = main->getGraph ();
    Transport* transport = getFilter()->getTransport();

    switch (commandID)
    {
    //----------------------------------------------------------------------------------------------
    case CommandIDs::pluginOpen:
        result.setInfo (T("Open plugin..."), T("Open a plugin"), CommandCategories::file, 0);
        result.addDefaultKeypress (T('l'), cmd);
        result.setActive (true);
        break;
    case CommandIDs::pluginClose:
        {
        result.setInfo (T("Close plugins"), T("Close selected plugins"), CommandCategories::file, 0);
        result.addDefaultKeypress (T('k'), cmd);
        // TODO - have to update this !
//        GraphComponent* track = tracks.getUnchecked (0);
//        result.setActive ((track ? (track->getSelectedPlugin () != -1) : false));
        result.setActive (false);
        break;
        }
    case CommandIDs::pluginClear:
        {
        result.setInfo (T("Clear plugins"), T("Close all plugins"), CommandCategories::file, 0);
        result.addDefaultKeypress (T('j'), cmd);
        result.setActive ((graph ? (graph->getPluginsCount () > 2) : false));
        break;
        }
    //----------------------------------------------------------------------------------------------
#ifndef JOST_VST_PLUGIN
    case CommandIDs::audioOptions:
        {
        result.setInfo (T("Show device manager"), T("Show device manager"), CommandCategories::audio, 0);
        // result.addDefaultKeypress (KeyPress::backspaceKey, none);
        result.setActive (true);
        break;
        }
#endif
    case CommandIDs::audioPlay:
        {
        result.setInfo (T("Play"), T("Play sequencers"), CommandCategories::audio, 0);
        if (! transport->isPlaying())
            result.addDefaultKeypress (KeyPress::spaceKey, none);
        result.setActive (! transport->isPlaying());
        break;
        }
    case CommandIDs::audioStop:
        {
        result.setInfo (T("Stop"), T("Stop sequencers"), CommandCategories::audio, 0);
        if (transport->isPlaying())
            result.addDefaultKeypress (KeyPress::spaceKey, none);
        result.setActive (transport->isPlaying());
        break;
        }
    case CommandIDs::audioRecord:
        {
        result.setInfo (T("Record"), T("Activate recording"), CommandCategories::audio, 0);
        result.addDefaultKeypress (T('r'), cmd);
        result.setTicked (transport->isRecording());
        result.setActive (true);
        break;
        }
    case CommandIDs::audioRewind:
        {
        result.setInfo (T("Rewind"), T("Rewind sequencers"), CommandCategories::audio, 0);
        result.addDefaultKeypress (KeyPress::backspaceKey, none);
        result.setActive (transport->getPositionInFrames() != 0);
        break;
        }
    case CommandIDs::audioLoop:
        {
        result.setInfo (T("Looping"), T("Loop sequencers"), CommandCategories::audio, 0);
        result.addDefaultKeypress (T('l'), cmd);
        result.setTicked (transport->isLooping());
        result.setActive (true);
        break;
        }
    //----------------------------------------------------------------------------------------------
    case CommandIDs::sessionNew:
        {
        result.setInfo (T("New session"), T("New session"), CommandCategories::file, 0);
        result.addDefaultKeypress (T('n'), cmd);
        result.setActive (true);
        break;
        }
    case CommandIDs::sessionLoad:
        result.setInfo (T("Load session..."), T("Open an session"), CommandCategories::file, 0);
        result.addDefaultKeypress (T('a'), cmd);
        result.setActive (true);
        break;
    case CommandIDs::sessionSave:
        {
        result.setInfo (T("Save session"), T("Save a session"), CommandCategories::file, 0);
        result.addDefaultKeypress (T('s'), cmd);
        result.setActive ((graph ? (graph->getPluginsCount () > 0) : false));
        break;
        }
    //----------------------------------------------------------------------------------------------
    case CommandIDs::appToolbar:
        result.setInfo (T("Edit toolbar"), T("Edit toolbar items"), CommandCategories::about, 0);
        result.setActive (toolbar != 0);
        break;
    case CommandIDs::appBrowser:
        result.setInfo (T("Show/Hide browser"), T("Show or hide the file browser"), CommandCategories::about, 0);
        result.setActive (true);
        break;
    case CommandIDs::appFullScreen:
        result.setInfo (T("FullScreen"), T("Set main window full screen"), CommandCategories::file, 0);
        result.addDefaultKeypress (T('t'), cmd);
        result.setActive (true);
        break;
    case CommandIDs::appExit:
        result.setInfo (T("Quit"), T("Quit application"), CommandCategories::file, 0);
        result.addDefaultKeypress (T('q'), cmd);
        result.setActive (true);
        break;
    case CommandIDs::appAbout:
        result.setInfo (T("About..."), T("About application"), CommandCategories::about, 0);
        result.setActive (true);
        break;
    //----------------------------------------------------------------------------------------------
    default:
        break;
    }
}

bool HostFilterComponent::perform (const InvocationInfo& info)
{
    Config* config = Config::getInstance();

    GraphComponent* graph = main->getGraph ();
    Transport* transport = getFilter()->getTransport();

    switch (info.commandID)
    {
    //----------------------------------------------------------------------------------------------
    case CommandIDs::pluginOpen:
        {
            graph->loadAndAppendPlugin ();
            break;
        }
    case CommandIDs::pluginClose:
        {
            graph->closeSelectedPlugins ();
            break;
        }
    case CommandIDs::pluginClear:
        {
            graph->closeAllPlugins ();
            break;
        }

    //----------------------------------------------------------------------------------------------
#ifndef JOST_VST_PLUGIN
    case CommandIDs::audioOptions:
        {
            StandaloneFilterWindow* window = findParentComponentOfClass ((StandaloneFilterWindow*) 0);
            if (window)
                window->showAudioSettingsDialog ();

            break;
        }
#endif

    case CommandIDs::audioPlay:
        {
            transport->play ();
            break;
        }
    case CommandIDs::audioStop:
        {
            transport->stop ();
            break;
        }
    case CommandIDs::audioRecord:
        {
            transport->record ();
            break;
        }
    case CommandIDs::audioRewind:
        {
            transport->rewind ();
            break;
        }
    case CommandIDs::audioLoop:
        {
            transport->setLooping (! transport->isLooping());
            break;
        }

    //----------------------------------------------------------------------------------------------
    case CommandIDs::sessionNew:
        {
			closePluginEditorWindows ();
            getFilter()->getHost ()->closeAllPlugins (true);

            clearComponents ();
            rebuildComponents ();
            break;
        }
    
    case CommandIDs::sessionLoad:
        {
            FileChooser myChooser (T("Load a session file..."),
                                    Config::getInstance ()->lastSessionDirectory,
                                    JOST_SESSION_WILDCARD, JOST_USE_NATIVE_FILE_CHOOSER);

            if (myChooser.browseForFileToOpen())
            {
                MemoryBlock fileData;
                File fileToLoad = myChooser.getResult();

                if (fileToLoad.existsAsFile()
                    && fileToLoad.loadFileAsData (fileData))
                {
                    getFilter ()->setStateInformation (fileData.getData (), fileData.getSize());

                    Config::getInstance()->addRecentSession (fileToLoad);
                }
            }
            break;
        }
    case CommandIDs::sessionSave:
        {
            FileChooser myChooser (T("Save a session file..."),
                                    Config::getInstance ()->lastSessionDirectory,
                                    JOST_SESSION_WILDCARD,
									JOST_USE_NATIVE_FILE_CHOOSER);

            if (myChooser.browseForFileToSave (true))
            {
                MemoryBlock fileData;
                getFilter ()->getStateInformation (fileData);

                File fileToSave = myChooser.getResult().withFileExtension (JOST_SESSION_EXTENSION);

                if (fileToSave.replaceWithData (fileData.getData (), fileData.getSize()))
                {
                    Config::getInstance()->addRecentSession (fileToSave);
                }
            }
            break;
        }

    //----------------------------------------------------------------------------------------------
    case CommandIDs::appToolbar:
        {
            toolbar->showCustomisationDialog (*factory,
                                              Toolbar::allCustomisationOptionsEnabled);
                                              // (Toolbar::allowIconsOnlyChoice | Toolbar::showResetToDefaultsButton));
            break;
        }
    case CommandIDs::appBrowser:
        {
            setBrowserVisible (! config->showBrowser, config->browserLeft);
            break;
        }
    case CommandIDs::appFullScreen:
        {
            DocumentWindow* window = findParentComponentOfClass <DocumentWindow> ();
            if (window) {
                window->setFullScreen (! window->isFullScreen ());
                window->setMenuBar (window->isFullScreen () ? 0 : this);
            }
            break;
        }
    case CommandIDs::appExit:
        {
            JUCEApplication::getInstance()->systemRequestedQuit();
            break;
        }
    case CommandIDs::appAbout:
        {
            Image* splashImage = ImageCache::getFromMemory (Resource::jost_about,
                                                            Resource::jost_about_size);

            SplashScreen* splash = new SplashScreen();
            splash->show (T(JucePlugin_Name), splashImage, 3500, true);
            break;
        }

    //----------------------------------------------------------------------------------------------
    default:
        return false;
    }

    return true;
}

