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

#include "BrowserTabbedComponent.h"
#include "../HostFilterComponent.h"


//==============================================================================
BrowserTabbedComponent::BrowserTabbedComponent (HostFilterComponent* owner_)
  : TabbedComponent (TabbedButtonBar::TabsAtLeft),
    owner (owner_)
{
    DBG ("BrowserTabbedComponent::BrowserTabbedComponent");

    Config* config = Config::getInstance ();

    setTabBarDepth (config->defaultTabThickness);
    Colour backgroundColour = config->getColour (T("mainBackground"));

    // add the disk browser component
    String patterns;
    patterns << JOST_PLUGIN_WILDCARD << ";"
             << JOST_SESSION_WILDCARD << ";"
             << JOST_PRESET_WILDCARD;

    diskBrowser = new DiskBrowserComponent (patterns);
    diskBrowser->addListener (this);
    addTab (T("Disk"), backgroundColour, diskBrowser, false);

    // add the bookmarks component
    String sessionName (T("Sessions"));
    sessionBookmarks = new BookmarksComponent (owner, sessionName, JOST_SESSION_WILDCARD, false);
    addTab (sessionName, backgroundColour, sessionBookmarks, false);

    String pluginName (T("Plugins"));
    pluginBookmarks = new BookmarksComponent (owner, pluginName, JOST_PLUGIN_WILDCARD, true);
    addTab (pluginName, backgroundColour, pluginBookmarks, false);

    String presetName (T("Presets"));
    presetBookmarks = new BookmarksComponent (owner, presetName, JOST_PRESET_WILDCARD, false);
    addTab (presetName, backgroundColour, presetBookmarks, false);

    // load bookmarks
    loadBookmarksFromFile (File (JOST_BOOKMARK_PATH));

    // the selected tab
    setCurrentTabIndex (config->browserLastOpenPage);
}

BrowserTabbedComponent::~BrowserTabbedComponent ()
{
    DBG ("BrowserTabbedComponent::~BrowserTabbedComponent");

    clearTabs ();

    // save bookmarks
    saveBookmarksToFile (File (JOST_BOOKMARK_PATH));

    deleteAndZero (sessionBookmarks);
    deleteAndZero (pluginBookmarks);
    deleteAndZero (presetBookmarks);
    deleteAndZero (diskBrowser);
}

//==============================================================================
void BrowserTabbedComponent::mouseUp (const MouseEvent& e)
{
    if (e.mods.isRightButtonDown ())
    {
        Config* config = Config::getInstance ();

        PopupMenu menu;
        menu.addItem (1, String ("Switch browser to ") + (config->browserLeft ? "right" : "left"));
        menu.addItem (2, String ("Close browser"));

        const int result = menu.show();
        switch (result)
        {
        case 1:
            owner->setBrowserVisible (config->showBrowser, ! config->browserLeft);
            break;
        case 2:
            owner->setBrowserVisible (false, config->browserLeft);
            break;
        default:
            break;
        }
    }
}

//==============================================================================
void BrowserTabbedComponent::selectionChanged()
{
    DBG ("BrowserTabbedComponent::selectionChanged");

    File currentFile = diskBrowser->getHighlightedFile();
    if (currentFile.existsAsFile ())
        currentFile = currentFile.getParentDirectory ();

    Config* config = Config::getInstance ();
    config->lastBrowsedDirectory = currentFile;
}

void BrowserTabbedComponent::fileClicked (const File& file, const MouseEvent& e)
{
    if (e.mods.isRightButtonDown())
    {
        PopupMenu menu;
        String fileExtension = file.getFileExtension().toLowerCase();

        if (file.isDirectory ())
        {
            menu.addItem (10, "Scan and Add");
            menu.addItem (11, "Scan and Add recursively");
        }
        else
        {

            menu.addItem (1, "Add to bookmarks");

            if (fileExtension == JOST_PLUGIN_EXTENSION
                && PluginLoader::canUnderstand (file))
            {
                menu.addSeparator ();
                menu.addItem (2, "Load plugin in modular");
            }

            if (fileExtension == JOST_SESSION_EXTENSION)
            {
                menu.addSeparator ();
                menu.addItem (3, "Load session file");
            }

            if (fileExtension == JOST_PRESET_EXTENSION)
            {
                menu.addSeparator ();
                menu.addItem (4, "Load preset into plugin", false, false);
            }
        }
        
        if (menu.getNumItems () > 0)
        {
            const int result = menu.show();
            switch (result)
            {
            case 1: // Add plugin to bookmarks
                if (fileExtension == JOST_PLUGIN_EXTENSION)
                {
                    pluginBookmarks->addBookmark (file);
                    pluginBookmarks->updateContent ();
                    break;
                }

                if (fileExtension == JOST_SESSION_EXTENSION)
                {
                    sessionBookmarks->addBookmark (file);
                    sessionBookmarks->updateContent ();
                    break;
                }

                if (fileExtension == JOST_PRESET_EXTENSION)
                {
                    presetBookmarks->addBookmark (file);
                    presetBookmarks->updateContent ();
                    break;
                }
                break;
            case 2: // Load plugin in modular
                owner->loadPluginFromFile (file);
                break;
            case 3: // Load session file
                {
                    MemoryBlock data;
                    if (file.existsAsFile()
                        && file.loadFileAsData (data))
                    {
                        owner->getFilter ()->setStateInformation (data.getData (), data.getSize());

                        Config::getInstance()->addRecentSession (file);
                    }
                }
                break;
            case 4: // Load preset into plugin
                // TODO
                break;
			case 10: 
				{
					OwnedArray<File> pluginFiles;
					file.findChildFiles(pluginFiles, 2, false, JOST_PLUGIN_WILDCARD);
					

					for (int i = 0; i < pluginFiles.size(); i++)
					{
						pluginBookmarks->addBookmark (*pluginFiles.getUnchecked(i));
					    pluginBookmarks->updateContent ();
					}
				}
				break;
			case 11: 
				{
					OwnedArray<File> pluginFiles;
					file.findChildFiles(pluginFiles, 2, true, JOST_PLUGIN_WILDCARD);
					

					for (int i = 0; i < pluginFiles.size(); i++)
					{
						pluginBookmarks->addBookmark (*pluginFiles.getUnchecked(i));
					    pluginBookmarks->updateContent ();
					}
				}
				break;
            default:
                break;
            }
        }
    }
}

void BrowserTabbedComponent::fileDoubleClicked (const File& file)
{
/*
    String fileExtension = file.getFileExtension().toLowerCase();

    if (fileExtension == JOST_PLUGIN_EXTENSION
        && PluginLoader::canUnderstand (file))
    {
        owner->loadPluginFromFile (file);
    }
*/
}

//==============================================================================
void BrowserTabbedComponent::popupMenuClickOnTab (const int tabIndex,
                                                  const String &tabName)
{
    DBG ("BrowserTabbedComponent::popupMenuClickOnTab");
}

void BrowserTabbedComponent::currentTabChanged (const int newCurrentTabIndex,
                                                const String &newCurrentTabName)
{
    DBG ("BrowserTabbedComponent::currentTabChanged");

    HostFilterComponent* hackTest = findParentComponentOfClass<HostFilterComponent> ();
    if (hackTest)
    {
        Config* config = Config::getInstance ();
        config->browserLastOpenPage = newCurrentTabIndex;
    }

/*
    int lastPageIndex = 0;

    // plugins have an external XLib gui editor
    if (newCurrentTabName == T("Interface"))
    {
    }
    // plugins have internal parameters gui
    else if (newCurrentTabName == T("Parameters"))
    {
    }
    // plugins options page
    else if (newCurrentTabName == T("Options"))
    {
    }
*/
}

//==============================================================================
void BrowserTabbedComponent::loadBookmarksFromFile (const File& file)
{
    DBG ("BrowserTabbedComponent::loadBookmarksFromFile");

    if (file.existsAsFile ())
    {
        XmlDocument myDocument (file);
        XmlElement* xml = myDocument.getDocumentElement();

        if (xml == 0)
        {
            String error = myDocument.getLastParseError();
            printf ("Error restoring bookmarks: %s \n", (const char*) error);
        }
        else
        {
            if (! xml->hasTagName (JOST_BOOKMARK_TAG))
            {
                printf ("Error restoring bookmarks: %s is not a valid bookmark file! \n",
                        (const char*) file.getFullPathName ());
            }
            else
            {
                {
                    XmlElement* e = xml->getChildByName (JOST_BOOKMARK_SESSIONTAG);
                    if (e) sessionBookmarks->loadFromXml (e);
                }
                {
                    XmlElement* e = xml->getChildByName (JOST_BOOKMARK_PLUGINTAG);
                    if (e) pluginBookmarks->loadFromXml (e);
                }
                {
                    XmlElement* e = xml->getChildByName (JOST_BOOKMARK_PRESETTAG);
                    if (e) presetBookmarks->loadFromXml (e);
                }
            }
        }
    }
}

void BrowserTabbedComponent::saveBookmarksToFile (const File& file)
{
    DBG ("BrowserTabbedComponent::saveBookmarksToFile");

    XmlElement xml (JOST_BOOKMARK_TAG);

    {
    XmlElement* e = new XmlElement (JOST_BOOKMARK_SESSIONTAG);
    sessionBookmarks->saveToXml (e);
    xml.addChildElement (e);
    }
    {
    XmlElement* e = new XmlElement (JOST_BOOKMARK_PLUGINTAG);
    pluginBookmarks->saveToXml (e);
    xml.addChildElement (e);
    }
    {
    XmlElement* e = new XmlElement (JOST_BOOKMARK_PRESETTAG);
    presetBookmarks->saveToXml (e);
    xml.addChildElement (e);
    }

    if (file.existsAsFile ())
        file.deleteFile ();

    file.appendText (xml.createDocument (String::empty));
}

