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

#ifndef __JUCETICE_JOSTBOOKMARKSCOMPONENT_HEADER__
#define __JUCETICE_JOSTBOOKMARKSCOMPONENT_HEADER__

#include "../../Config.h"
#include "../../model/Host.h"


//==============================================================================
// this is the listbox containing the draggable source components..

class BookmarksComponent  : public ListBox,
                            public ListBoxModel
{
public:

    //==============================================================================
    BookmarksComponent (HostFilterComponent* owner,
                        const String& title,
                        const String& wildcard,
                        const bool multipleSelection);

    ~BookmarksComponent ();

    //==============================================================================
    // The following methods implement the necessary virtual functions from ListBoxModel,
    // telling the listbox how many rows there are, painting them, etc.
    int getNumRows();

    void paintListBoxItem (int rowNumber,
                           Graphics& g,
                           int width, int height,
                           bool rowIsSelected);

    const String getDragSourceDescription (const SparseSet<int>& selectedRows);

    //==============================================================================
    void addBookmark (const File& file);
    void removeBookmark (const int bookmarkIndex);
    void clearAllBookmarks ();

    bool raiseBookmark (const int bookmarkIndex);
    bool lowerBookmark (const int bookmarkIndex);

    //==============================================================================
    const String& getBookmarksName () const              { return internalName; }
    const String& getBookmarksWildcard () const          { return wildcardString; }

    //==============================================================================
    /** Serialize to an Xml element */
    void saveToXml (XmlElement* element);

    /** Deserialize from an Xml element */
    void loadFromXml (XmlElement* element);

    //==============================================================================
    // this just fills in the background of the listbox
    void paint (Graphics& g);

protected:

    HostFilterComponent* owner;

    String internalName;
    String wildcardString;
    OwnedArray<File> files;
};

#endif
