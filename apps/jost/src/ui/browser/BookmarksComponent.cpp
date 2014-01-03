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

#include "BookmarksComponent.h"
#include "../../HostFilterComponent.h"

//==============================================================================
class BookmarksHeaderComponent  : public Component,
                                  public ButtonListener
{
public:

    BookmarksHeaderComponent (BookmarksComponent* owner_,
                              const String& title_)
        : owner (owner_)
    {
        addAndMakeVisible (headerLabel = new Label (String::empty, title_));
        headerLabel->setFont (Font (16.0000f, Font::bold));
        headerLabel->setJustificationType (Justification::left);
        headerLabel->setEditable (false, false, false);
        headerLabel->setColour (TextEditor::textColourId, Colours::black);
        headerLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

        addAndMakeVisible (upButton = new TextButton (String::empty));
        upButton->setButtonText (T("+"));
        upButton->setTooltip (T("Move selected bookmarks up"));
        upButton->setConnectedEdges (Button::ConnectedOnRight | Button::ConnectedOnLeft);
        upButton->addButtonListener (this);

        addAndMakeVisible (downButton = new TextButton (String::empty));
        downButton->setButtonText (T("-"));
        downButton->setTooltip (T("Move selected bookmarks down"));
        downButton->setConnectedEdges (Button::ConnectedOnRight | Button::ConnectedOnLeft);
        downButton->addButtonListener (this);

        addAndMakeVisible (addButton = new TextButton (String::empty));
        addButton->setButtonText (T("add"));
        addButton->setTooltip (T("Add a new bookmark"));
        addButton->setConnectedEdges (Button::ConnectedOnRight | Button::ConnectedOnLeft);
        addButton->addButtonListener (this);

        addAndMakeVisible (removeButton = new TextButton (String::empty));
        removeButton->setButtonText (T("del"));
        removeButton->setTooltip (T("Delete selected bookmarks"));
        removeButton->setConnectedEdges (Button::ConnectedOnRight | Button::ConnectedOnLeft);
        removeButton->addButtonListener (this);
        
        setSize (100, 18);
    }

    ~BookmarksHeaderComponent ()
    {
        deleteAndZero (headerLabel);
        deleteAndZero (upButton);
        deleteAndZero (downButton);
        deleteAndZero (addButton);
        deleteAndZero (removeButton);
    }

    void paint (Graphics& g)
    {
        const Colour background (Config::getInstance ()->getColour (T("bookmarksHeader")));

        g.setGradientFill (ColourGradient(background, 0.0f, 0.0f,
                                          background.darker (0.1f),
                                          0.0f,
                                          getHeight () - 1.0f,
                                          false));
        g.fillAll();
    }    
    
    void resized ()
    {
        headerLabel->setBounds (0, 0, getWidth () - 90, getHeight () - 2);
        upButton->setBounds (getWidth () - 90, 0, 15, getHeight () - 2);
        downButton->setBounds (getWidth () - 75, 0, 15, getHeight () - 2);
        addButton->setBounds (getWidth () - 60, 0, 30, getHeight () - 2);
        removeButton->setBounds (getWidth () - 30, 0, 30, getHeight () - 2);
    }

    void buttonClicked (Button* buttonThatWasClicked)
    {
        SparseSet<int> selection = owner->getSelectedRows ();

        if (buttonThatWasClicked == upButton)
        {
            SparseSet<int> newSet;

            for (int i = 0; i < selection.size (); i++)
            {
                if (owner->raiseBookmark (selection [i]))
                    newSet.addRange (selection [i] - 1, 1);
            }

            owner->setSelectedRows (newSet);
            owner->updateContent ();
            owner->repaint ();
        }
        else if (buttonThatWasClicked == downButton)
        {
            SparseSet<int> newSet;

            for (int i = selection.size (); --i >= 0;)
            {
                if (owner->lowerBookmark (selection [i]))
                    newSet.addRange (selection [i] + 1, 1);
            }

            owner->setSelectedRows (newSet);
            owner->updateContent ();
            owner->repaint ();
        }
        else if (buttonThatWasClicked == addButton)
        {
            FileChooser myChooser (T("Add a ") + owner->getBookmarksName() + T(" bookmark"),
                                   Config::getInstance ()->lastSessionDirectory,
                                   owner->getBookmarksWildcard (), JOST_USE_NATIVE_FILE_CHOOSER);

            if (myChooser.browseForFileToOpen())
            {
                File fileToLoad = myChooser.getResult();

                if (fileToLoad.existsAsFile())
                {
                    owner->addBookmark (fileToLoad);
                    owner->updateContent ();
                    owner->repaint ();
                }
            }
        }
        else if (buttonThatWasClicked == removeButton)
        {
            Array<int> rows;
            for (int i = 0; i < selection.size (); i++)
                rows.add (selection [i]);
            
            for (int i = 0; i < rows.size (); i++)
            {
                owner->removeBookmark (rows.getUnchecked (i));

                for (int j = 0; j < rows.size (); j++)
                    rows.getReference (j) = rows.getUnchecked (j) - 1;
            }
            
            SparseSet<int> emptySet;
            owner->setSelectedRows (emptySet);

            owner->updateContent ();
            owner->repaint ();
        }
       
    }

protected:

    BookmarksComponent* owner;

    Label* headerLabel;
    TextButton* upButton;
    TextButton* downButton;
    TextButton* addButton;
    TextButton* removeButton;
};



//==============================================================================
BookmarksComponent::BookmarksComponent (HostFilterComponent* owner_,
                                        const String& title,
                                        const String& wildcard,
                                        const bool multipleSelection)
    : ListBox (T("ddsource"), 0),
      owner (owner_),
      internalName (title),
      wildcardString (wildcard)
{
    setModel (this);
    setMultipleSelectionEnabled (multipleSelection);

    setRowHeight (18);
    setOutlineThickness (2);
    
    setHeaderComponent (new BookmarksHeaderComponent (this, internalName));

    Colour colour = Config::getInstance ()->getColour (T("bookmarksBackground"));
    setColour (ListBox::backgroundColourId, colour);

    colour = Config::getInstance ()->getColour (T("mainBackground"));
    setColour (ListBox::outlineColourId, colour);
}

BookmarksComponent::~BookmarksComponent()
{
    clearAllBookmarks ();
}

//==============================================================================
int BookmarksComponent::getNumRows()
{
    return files.size ();
}

void BookmarksComponent::paintListBoxItem (int rowNumber,
                                           Graphics& g,
                                           int width, int height,
                                           bool rowIsSelected)
{
    if (rowIsSelected)
        g.setColour (Config::getInstance ()->getColour (T("bookmarksItemSelected")));
    else
        g.setColour (Config::getInstance ()->getColour (T("bookmarksItemNormal")));
    g.fillRect (2, 2, width - 4, height - 2);

    g.setColour (Colours::black);
    g.setFont (height * 0.7f);

    File* file = files.getUnchecked (rowNumber);
    g.drawText (file->getFileName (),
                2 + 4, 2, width - 4, height - 2,
                Justification::centredLeft, true);
}

const String BookmarksComponent::getDragSourceDescription (const SparseSet<int>& selectedRows)
{
    String desc = internalName + ": ";

    for (int i = 0; i < selectedRows.size(); ++i)
        desc << files.getUnchecked (selectedRows [i])->getFullPathName () << T(" ");

    return desc.trim();
}

//==============================================================================
void BookmarksComponent::paint (Graphics& g)
{
//    Colour backgroundColour = Config::getInstance ()->getColour (T("mainBackground"));
//    g.fillAll (backgroundColour.withAlpha (0.7f));
//    g.fillAll (Colours::white); // (Colours::white.withAlpha (0.7f));
}

//==============================================================================
void BookmarksComponent::addBookmark (const File& file)
{
    files.addIfNotAlreadyThere (new File (file));
}

void BookmarksComponent::removeBookmark (const int bookmarkIndex)
{
    files.remove (bookmarkIndex);
}

void BookmarksComponent::clearAllBookmarks ()
{
    files.clear (true);
}

bool BookmarksComponent::raiseBookmark (const int bookmarkIndex)
{
    if (bookmarkIndex > 0)
    {
        files.move (bookmarkIndex, bookmarkIndex - 1);
        return true;
    }
    
    return false;
}

bool BookmarksComponent::lowerBookmark (const int bookmarkIndex)
{
    if (bookmarkIndex < files.size ())
    {
        files.move (bookmarkIndex, bookmarkIndex + 1);
        return true;
    }
    
    return false;
}

//==============================================================================
void BookmarksComponent::saveToXml (XmlElement* xml)
{
    XmlElement* category = new XmlElement (T("category"));
    category->setAttribute (T("name"), T("uncategorized"));

    for (int j = 0; j < files.size (); j++)
    {
        File* file = files.getUnchecked (j);
        
        XmlElement* fileElement = new XmlElement (T("file"));
        fileElement->setAttribute (T("path"), file->getFullPathName ());

        category->addChildElement (fileElement);
    }

    xml->addChildElement (category);
}

void BookmarksComponent::loadFromXml (XmlElement* xml)
{
    XmlElement* category = xml->getChildByName (T("category"));
    if (category)
    {
        clearAllBookmarks ();

        forEachXmlChildElement (*category, fileElement)
        {
            if (fileElement->hasTagName (T("file")))
            {
                String path = fileElement->getStringAttribute (T("path"), String::empty);
                
                File file (path);
                if (file.existsAsFile ())
                    addBookmark (file);
            }
        }

        updateContent ();
    }
}

