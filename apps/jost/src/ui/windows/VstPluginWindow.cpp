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
#include "VstPluginNativeEditor.h"
#include "VstPluginWindow.h"
#include "VstPluginWindowContent.h"

#include "../../Commands.h"
#include "../../HostFilterComponent.h"
#include "../../resources/Resources.h"

const int PluginMenuCommandIDMask = 0x80000000; 

//==============================================================================
VstPluginWindow::VstPluginWindow (PluginEditorWindowHolder* owner_,
                                  BasePlugin* plugin_)
  : DialogWindow (String::empty, Colours::beige, true, false),
    plugin (0),
    owner (owner_),
    specialEditor (0),
    nativeEditor (0),
    externalEditor (0),
    content (0)
{
    DBG ("VstPluginWindow::VstPluginWindow");

    // add to desktop
    addToDesktop (getDesktopWindowStyleFlags());

    // setup window default values
    setTitleBarHeight (24);
    centreWithSize (400, 300);
    setWantsKeyboardFocus (true);
    setBackgroundColour (Config::getInstance ()->getColour (T("mainBackground")));

    // try to move the window to its old position
    int oldX = -1, oldY = -1, oldW = -1, oldH = -1, lastPage = 0;
    if (plugin_)
    {
        oldX = plugin_->getIntValue (PROP_WINDOWXPOS, -1);
        oldY = plugin_->getIntValue (PROP_WINDOWYPOS, -1);
        oldW = plugin_->getIntValue (PROP_WINDOWWSIZE, -1);
        oldH = plugin_->getIntValue (PROP_WINDOWHSIZE, -1);
        lastPage = plugin_->getIntValue (PROP_WINDOWPAGE, 0);
    }

    // try to move the window to its old position
    if (oldX >= 0 && oldY >= 0)
        setTopLeftPosition (oldX, oldY);

    // try to set the window to its old size
    if ((lastPage == 0 && ! externalEditor)
        || (lastPage == 1 && externalEditor))
    {
        if (oldW >= 0 && oldY >= 0)
            setSize (oldW, oldH);
    }

    // default plugin to open
    setPlugin (plugin_);
    
    // setMenuBar here, after setting the plugin, so the plugin's menu items are there immediately
    setMenuBar (this, getMenuBarHeight ());

    // restore window to front
    toFront (false);
    setVisible (true);
}

VstPluginWindow::~VstPluginWindow ()
{
    DBG ("VstPluginWindow::~VstPluginWindow");

    // remove manually the menu !
    setMenuBar (0);

    // remove existent plugin editors
    setPlugin (0);

    // kill this window before it gets killed by juce !
    removeFromDesktop ();
}

//==============================================================================
void VstPluginWindow::setPlugin (BasePlugin* plugin_)
{
    DBG ("VstPluginWindow::setPlugin");

    externalEditor = 0; // DO NOT DELETE IT (it is deleted by setContentComponent (0))
    specialEditor = 0;  // DO NOT DELETE IT (it is deleted by setContentComponent (0))
    nativeEditor = 0;   // DO NOT DELETE IT (it is deleted by setContentComponent (0))
    content = 0;

    setContentComponent (0);

    plugin = plugin_;

    if (plugin)
    {
        int preferredWidth = 400;
        int preferredHeight = 300;
        bool limitHeight = false;

        // we got a plugin to show
        setName (plugin->getName ());

        if (plugin->hasEditor ())
        {
            // plugin have its internal editor, but don't want others !
            if (plugin->isEditorInternal ())
            {
                specialEditor = (PluginEditorComponent*) plugin->createEditor ();
                if (specialEditor)
                {
                    preferredWidth = specialEditor->getPreferredWidth();
                    preferredHeight = specialEditor->getPreferredHeight();

                    setResizable (specialEditor->isResizable (), false);

                    setContentComponent (specialEditor);
                }
            }
            // plugin have external editor by its own
            else
            {
                nativeEditor = new VstPluginNativeEditor (plugin, this);
                externalEditor = new VstPluginExternalEditor (plugin, this);

                setContentComponent (content = new VstPluginWindowContent (owner,
                                                                           plugin,
                                                                           this,
                                                                           nativeEditor,
                                                                           externalEditor));

                int lastSelectedTab = plugin->getIntValue (PROP_WINDOWPAGE, 0);
                if (lastSelectedTab == 0)
                {
                    preferredWidth = externalEditor->getPreferredWidth();
                    preferredHeight = externalEditor->getPreferredHeight();
                }
                else
                {
                    preferredWidth = nativeEditor->getPreferredWidth();
                    preferredHeight = nativeEditor->getPreferredHeight();
                }
            }
        }
        else
        {
            // plugin don't have a editor, but wants a host provided one
            nativeEditor = new VstPluginNativeEditor (plugin, this);

            preferredWidth = nativeEditor->getPreferredWidth();
            preferredHeight = nativeEditor->getPreferredHeight();

            setContentComponent (content = new VstPluginWindowContent (owner,
                                                                       plugin,
                                                                       this,
                                                                       nativeEditor,
                                                                       externalEditor));
        }

        resizeContentComponent (preferredWidth,
                                preferredHeight,
                                limitHeight);

        updateParameters();
    }
    else
    {
        // we do not have any plugin
        setResizable (true, false);
    }
}

//==============================================================================
void VstPluginWindow::updateParameters()
{
    DBG ("VstPluginWindow::updateParameters");

    if (specialEditor)  specialEditor->updateParameters ();
    if (nativeEditor)   nativeEditor->updateParameters ();
    if (externalEditor) externalEditor->updateParameters ();
}

void VstPluginWindow::resizeContentComponent (const int width,
                                              const int height,
                                              const bool limitHeight)
{
    DBG ("VstPluginWindow::resizeContentComponent");

    int desiredWidth = width + 2
                       /* + getBorderThickness().getLeftAndRight ()*/;

    int desiredHeight = getTitleBarHeight()
                        + getMenuBarHeight()
                        + getBorderThickness().getTopAndBottom ()
                        + (content ? content->getTabbedPanelHeight () : 0)
                        + (content ? (content->hasMidiKeyboardOpen() ? content->getMidiKeyboardHeight() : 0) : 0);

    int maxHeight = height + desiredHeight;
    maxHeight = limitHeight ? jmin (700, maxHeight) : maxHeight;

    setSize (desiredWidth, maxHeight);

    if (limitHeight)
        setResizeLimits (desiredWidth, desiredHeight,
                         desiredWidth, maxHeight);
}

//==============================================================================
void VstPluginWindow::paint (Graphics& g)
{
    if (plugin != 0 && externalEditor != 0)
    {
        externalEditor->paint (g);
    }

    DialogWindow::paint(g);
}

//==============================================================================
void VstPluginWindow::resized()
{
    DialogWindow::resized();

    if (plugin)
    {
        // save plugin values
        if (content && (plugin->isEditorInternal ()
                        || ((content->getCurrentTabIndex() == 0 && ! externalEditor)
                            || (content->getCurrentTabIndex() == 1 && externalEditor))))
        {
            plugin->setValue (PROP_WINDOWWSIZE, getWidth ());
            plugin->setValue (PROP_WINDOWHSIZE, getHeight ());
        }
    }
}

//==============================================================================
void VstPluginWindow::moved()
{
    DialogWindow::moved();

    if (plugin)
    {
        if (externalEditor)
        {
            externalEditor->updateWindowPosition (getScreenX (),
                                                  getScreenY ());
        }

        plugin->setValue (PROP_WINDOWXPOS, getScreenX ());
        plugin->setValue (PROP_WINDOWYPOS, getScreenY ());
    }
}

//==============================================================================
void VstPluginWindow::filesDropped (const StringArray& filenames,
                                    int mouseX,
                                    int mouseY)
{
}

//==============================================================================
void VstPluginWindow::broughtToFront ()
{
    DialogWindow::broughtToFront();

    if (plugin != 0 && externalEditor != 0)
    {
        externalEditor->repaint ();
    }
}

void VstPluginWindow::minimisationStateChanged (bool isNowMinimised)
{
    DialogWindow::minimisationStateChanged (isNowMinimised);

    if (! isNowMinimised && plugin != 0 && externalEditor != 0)
    {
        externalEditor->repaint ();
    }
}

void VstPluginWindow::closeButtonPressed ()
{
    owner->closePluginEditorWindow (plugin);
}

//==============================================================================
const int VstPluginWindow::getMenuBarHeight () const
{
    return 20;
}

// the window main menu
const StringArray VstPluginWindow::getMenuBarNames ()
{
    pluginMenuNames.clear();
    ourMenuNames.clear();
    combinedMenuNames.clear();

    // does our plugin want to add some menus?
    if (specialEditor)
        specialEditor->getMenuBarNames(pluginMenuNames);
        
    // now our menus
    const tchar* const names[] = {
                                    CommandCategories::presets,
                                    CommandCategories::options,
                                    0
    };
    ourMenuNames = StringArray((const tchar**) names);

    // and merge the arrays, so common items collapse to one menu
    combinedMenuNames = pluginMenuNames;
    combinedMenuNames.addArray(ourMenuNames);
    combinedMenuNames.removeDuplicates(true);
    
    return combinedMenuNames;
}

// where the menu is constructed
const PopupMenu VstPluginWindow::getMenuForIndex (int menuIndex,
                                                  const String& menuName)
{
    PopupMenu menu;

	if (menuName.compare(CommandCategories::presets) == 0)
	{
		menu.addItem (1, T("Load preset..."), true);
		menu.addItem (2, T("Save preset..."), true);
		menu.addSeparator ();

		for (int i = 1; i < plugin->getNumPrograms (); i++)
		{
		menu.addItem (i + 100, plugin->getProgramName (i), true);
		}
	}
	else if (menuName.compare(CommandCategories::options) == 0)
	{
		bool itemActive = (plugin != 0 && content != 0 && plugin->acceptsMidi());
		bool itemTicked = (plugin != 0 && content != 0 && plugin->getBoolValue (PROP_WINDOWVISIBLEMIDIKEY, false));

		menu.addItem (1, T("Show midi keyboard"), itemActive, itemTicked);
	}

	if (specialEditor)
	{
		PopupMenu pluginMenuItems;
		if (specialEditor->getMenuForMenuName(menuName, pluginMenuItems))
		{
			menu.addSeparator();
			PopupMenu::MenuItemIterator iter(pluginMenuItems);
			while (iter.next())
			{
				jassert((iter.itemId & PluginMenuCommandIDMask) == 0); // plugin ids must leave that bit free so we know who owns the item!
				iter.itemId = (iter.itemId | PluginMenuCommandIDMask);

				if (iter.isSeparator)
					menu.addSeparator();
				else if (iter.isSectionHeader)
					menu.addSectionHeader(iter.itemName);
				else if (iter.subMenu)
					menu.addSubMenu(iter.itemName, *iter.subMenu);
				else if (iter.customColour)
					menu.addColouredItem(iter.itemId, iter.itemName, *iter.customColour, iter.isEnabled, iter.isTicked, iter.customImage);
				else if (iter.commandManager)
					menu.addCommandItem(iter.commandManager, iter.itemId, iter.itemName);
				else 
					menu.addItem(iter.itemId, iter.itemName, iter.isEnabled, iter.isTicked, iter.customImage);
			}
		}
	}

    return menu;
}

void VstPluginWindow::menuItemSelected (int menuItemID,
                                        int topLevelMenuIndex)
{
    if ((menuItemID & PluginMenuCommandIDMask) == PluginMenuCommandIDMask)
        specialEditor->menuItemSelected(combinedMenuNames[topLevelMenuIndex], (menuItemID & ~PluginMenuCommandIDMask));

    else if (topLevelMenuIndex == combinedMenuNames.indexOf(CommandCategories::presets))
    {
		switch (menuItemID)
		{
		case 1:
			loadPreset ();
			break;
		case 2:
			savePreset ();
			break;
		default:
			if (menuItemID >= 100 && menuItemID < (100 + plugin->getNumPrograms ()))
			{
				plugin->setCurrentProgram (menuItemID - 100);
				updateParameters ();
			}
		}
	}
    else if (topLevelMenuIndex == combinedMenuNames.indexOf(CommandCategories::options))
	{
		if (menuItemID == 1)
		{
			bool keysVisible = plugin->getBoolValue (PROP_WINDOWVISIBLEMIDIKEY, true);

			if (content)
				content->activateMidiKeyboard (! keysVisible);

			plugin->setValue (PROP_WINDOWVISIBLEMIDIKEY, ! keysVisible);
		}
	}

    toFront (false);
}

//==============================================================================
void VstPluginWindow::loadPreset ()
{
    File lastPresetDirectory = File (plugin->getValue (PROP_PLUGPRESETDIR, String::empty));
    if (! lastPresetDirectory.exists())
        lastPresetDirectory = Config::getInstance ()->lastPresetDirectory;

    FileChooser myChooser (T("Load a preset file..."),
                           lastPresetDirectory,
                           JOST_PRESET_WILDCARD, JOST_USE_NATIVE_FILE_CHOOSER);

    if (myChooser.browseForFileToOpen())
    {
        File fileToLoad = myChooser.getResult();

        if (fileToLoad.existsAsFile())
        {
            XmlDocument xmlDoc (fileToLoad.loadFileAsString ());
            XmlElement* xml = xmlDoc.getDocumentElement();

            if (xml == 0 || ! xml->hasTagName (JOST_PRESET_PRESETTAG))
            {
                String errString = xmlDoc.getLastParseError();
                printf ("Error parsing preset: %s \n", (const char*) errString);
            }
            else
            {
                plugin->loadPresetFromXml (xml);

                updateParameters ();
                repaint ();

                Config::getInstance()->addRecentPreset (fileToLoad);

                plugin->setValue (PROP_PLUGPRESETDIR, fileToLoad.getParentDirectory().getFullPathName());
            }
        }
    }
}

void VstPluginWindow::savePreset ()
{
    File lastPresetDirectory = File (plugin->getValue (PROP_PLUGPRESETDIR, String::empty));
    if (! lastPresetDirectory.exists())
        lastPresetDirectory = Config::getInstance ()->lastPresetDirectory;

    FileChooser myChooser (T("Save a preset file..."),
                           lastPresetDirectory,
                           JOST_PRESET_WILDCARD, JOST_USE_NATIVE_FILE_CHOOSER);

    if (myChooser.browseForFileToSave (true))
    {
        File fileToSave = myChooser.getResult().withFileExtension (JOST_PRESET_EXTENSION);

        XmlElement xml (JOST_PRESET_PRESETTAG);
        plugin->savePresetToXml (&xml);

        if (fileToSave.replaceWithText (xml.createDocument (String::empty)))
        {
            Config::getInstance()->addRecentPreset (fileToSave);

            plugin->setValue (PROP_PLUGPRESETDIR, fileToSave.getParentDirectory().getFullPathName());
        }
    }
}

