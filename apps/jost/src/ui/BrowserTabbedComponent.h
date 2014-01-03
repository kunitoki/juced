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

#ifndef __JUCETICE_JOSTBROWSERTABBEDCOMPONENT_HEADER__
#define __JUCETICE_JOSTBROWSERTABBEDCOMPONENT_HEADER__

#include "../Config.h"
#include "../model/Host.h"
#include "browser/DiskBrowserComponent.h"
#include "browser/BookmarksComponent.h"


//==============================================================================
/**
    Tabbed panel which owns the External / Native GUI for plugins and
    also will host pages for fast tweaking, options... whatever
*/
class BrowserTabbedComponent : public TabbedComponent,
                               public FileBrowserListener
{
public:
    //==============================================================================
    BrowserTabbedComponent (HostFilterComponent* owner_);

    ~BrowserTabbedComponent ();

    //==============================================================================
    void currentTabChanged (const int newCurrentTabIndex,
                            const String &newCurrentTabName);

    void popupMenuClickOnTab (const int tabIndex,
                              const String &tabName);

    //==============================================================================
    void selectionChanged();
    void fileClicked (const File& file, const MouseEvent& e);
    void fileDoubleClicked (const File& file);

    //==============================================================================
    void loadBookmarksFromFile (const File& file);
    void saveBookmarksToFile (const File& file);

    //==============================================================================
    /** @internal */
    void mouseUp (const MouseEvent& e);

protected:

    HostFilterComponent* owner;

    BookmarksComponent* sessionBookmarks;
    BookmarksComponent* pluginBookmarks;
    BookmarksComponent* presetBookmarks;

    DiskBrowserComponent* diskBrowser;
};


#endif // __JUCETICE_JOSTBROWSERTABBEDCOMPONENT_HEADER__
