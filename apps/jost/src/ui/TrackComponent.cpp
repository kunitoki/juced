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

#include "TrackComponent.h"
#include "../HostFilterComponent.h"

#if 0

//==============================================================================
TrackComponent::TrackComponent (HostFilterComponent* owner_)
    : Component (T("track")),
      owner (owner_),
      track (0),
      selectedPlugin (-1),
      draggingPluginIndex (-1)
{
    setOpaque (false);
    setBufferedToImage (true);
}

TrackComponent::~TrackComponent()
{
    setTrack (0);
}


//==============================================================================
void TrackComponent::setTrack (Track* trackToDisplay)
{
    track = trackToDisplay;
}


//==============================================================================
void TrackComponent::paint (Graphics& g)
{
    Colour backgroundColour = Config::getInstance ()->getColour (T("mainBackground"));

    g.fillAll (backgroundColour);

    if (track && track->getPluginsCount () > 0)
    {
        int offsetX = 4, offsetY = 4;
        int currentX = offsetX, currentY = offsetY;

        int width = (getWidth() - 2 * currentX) / track->getPluginsCount () - offsetX;
        int height = (getHeight () - 2 * currentY);

        for (int i = 0; i < track->getPluginsCount (); i++)
        {
            BasePlugin* plugin = track->getPluginByIndex (i);

            if (i == track->getPluginsCount () - 1) width += offsetX;

            if (plugin)
            {
                paintPluginImage (g,
                                  currentX,
                                  currentY,
                                  width,
                                  height,
                                  plugin->getName (),
                                  selectedPlugin == i);
            }

            currentX += width + offsetX;
        }

        if (draggingPluginIndex != -1)
        {
            int drawX = draggingPluginIndex * (width);

            if (draggingPluginIndex == 0) drawX += 1;
            else                          drawX += offsetX / 2;

            g.setColour (Colours::red);
            g.drawLine (drawX, currentY,
                        drawX, currentY + height, 2.0f);
        }
    }
    else
    {
        g.setFont (Font (18.0f, Font::italic));
        g.setColour (backgroundColour.darker (1.5f));
        g.drawText (T("Drop plugins here !"),
                    0, 0,
                    getWidth (), getHeight (),
                    Justification::centred,
                    false);
    }
}

void TrackComponent::paintPluginImage (Graphics& g,
                                       const int x,
                                       const int y,
                                       const int width,
                                       const int height,
                                       const String& text,
                                       const bool isSelected)
{
    Colour backgroundColour = Config::getInstance ()->getColour (T("mainBackground"));

    g.setFont (Font (15.0f, Font::bold));

    g.setColour (backgroundColour.darker (1.0f));
    g.fillRoundedRectangle (x, y,
                            width, height, 5.0f);

    if (isSelected)
        g.setColour (Colours::yellow);
    else
        g.setColour (Colours::orange);

    g.drawText (text,
                x, y,
                width, height,
                Justification::centred,
                false);

    g.drawRoundedRectangle (x, y,
                            width, height, 5.0f, 2.0f);
}

//==============================================================================
void TrackComponent::mouseDown (const MouseEvent& e)
{
    int newSelectedPlugin = getPluginIndexFromMousePosition (e.x, e.y);
    if (newSelectedPlugin != selectedPlugin)
    {
        selectedPlugin = newSelectedPlugin;
        repaint (); // TODO - be smart please, repaint only this rectangle !
    }

    if (e.mods.isPopupMenu () && track)
    {
        BasePlugin* plugin = track->getPluginByIndex (selectedPlugin);

        PopupMenu menu;

        if (plugin)
        {
            menu.addItem (1, "Open editor");
            menu.addSeparator ();
            menu.addItem (2, "Remove plugin");
        }

        menu.addItem (3, "Insert plugin...");
        menu.addSeparator ();
        menu.addItem (4, T("Move previous"),
                        (selectedPlugin > 0) ? true : false);
        menu.addItem (5, T("Move next"),
                        (selectedPlugin < track->getPluginsCount () - 1) ? true : false);

        switch (menu.show())
        {
            case 1: // Open editor
                if (owner && plugin)
                    owner->openPluginEditorWindow (plugin);
                break;

            case 2: // Close
                if (owner->isPluginEditorWindowOpen (plugin))
                    owner->closePluginEditorWindow (plugin);

                if (plugin)
                    track->closePlugin (plugin);
                break;

            case 3: // Insert new plugin
                loadAndAppendPlugin ();
                break;

            case 4: // Previous
                // track->swapPlugins (selectedPlugin, selectedPlugin - 1);
                selectedPlugin--;
                break;

            case 5: // Next
                // track->swapPlugins (selectedPlugin, selectedPlugin + 1);
                selectedPlugin++;
                break;

            case 0: // dismiss
            default:
                break;
        }

        repaint ();
    }
    else
    {
        if (track && track->getPluginsCount () > 0)
            startDocking (e);
    }
}

void TrackComponent::mouseDrag (const MouseEvent& e)
{
    if (isEnabled()
        && track
        && track->getPluginsCount () > 0)
    {
        continueDocking (e);
    }
}

void TrackComponent::mouseUp (const MouseEvent& e)
{
/*
    if (track)
    {
        VstPlugin* plugin = getPluginFromMousePosition (e.x, e.y);
        if (plugin)
            owner->openPluginEditorWindow (plugin);
    }
*/
}

void TrackComponent::mouseDoubleClick (const MouseEvent& e)
{
    if (e.mods.isLeftButtonDown () && track)
    {
        BasePlugin* plugin = getPluginFromMousePosition (e.x, e.y);
        if (plugin)
            owner->openPluginEditorWindow (plugin);
    }
}

bool TrackComponent::filesDropped (const StringArray& filenames,
                                    int mouseX,
                                    int mouseY)
{
    if (filenames.size())
        dropPluginOnTrack (filenames[0], mouseX, mouseY);

    return true;
}


//==============================================================================
String TrackComponent::getDragDescription ()
{
    return getName();
}

Image* TrackComponent::getDragImage ()
{
    if (track == 0 || track->getPluginsCount () == 0)
        return 0;

    int width = (getWidth() - 2 * 2) / track->getPluginsCount () - 2;
    int height = (getHeight () - 2 * 2);

    Image* dragImage = new Image (Image::ARGB,
                                  jmax (1, width),
                                  jmax (1, height),
                                  true);

    Graphics imageContext (*dragImage);
    paintPluginImage (imageContext,
                      0,
                      0,
                      width,
                      height,
                      track->getPluginByIndex (selectedPlugin)->getName (),
                      true);

    dragImage->multiplyAllAlphas (0.6f);
    return dragImage;
}

Component* TrackComponent::getDragComponent ()
{
    return this;
}


//==============================================================================
bool TrackComponent::isInterestedInDragSource (const String& sourceDescription)
{
    // normally you'd check the sourceDescription value to see if it's the
    // sort of object that you're interested in before returning true, but for
    // the demo, we'll say yes to anything..
    return true;
}

void TrackComponent::itemDragEnter (const String& sourceDescription,
                                    Component* sourceComponent,
                                    int x, int y)
{
    draggingPluginIndex = getPluginIndexFromMousePosition (x, y);
    repaint();
}

void TrackComponent::itemDragMove (const String& sourceDescription,
                                   Component* sourceComponent,
                                   int x, int y)
{
    draggingPluginIndex = getPluginIndexFromMousePosition (x, y);
    repaint ();
}

void TrackComponent::itemDragExit (const String& sourceDescription,
                                   Component* sourceComponent)
{
    draggingPluginIndex = -1;
    repaint();
}

void TrackComponent::itemDropped (const String& sourceDescription,
                                  Component* sourceComponent,
                                  int x, int y)
{
    draggingPluginIndex = getPluginIndexFromMousePosition (x, y);

    if (track
        && selectedPlugin != draggingPluginIndex
        && draggingPluginIndex != -1)
    {
        DBG (String (selectedPlugin) + " " + String (draggingPluginIndex));

        // track->swapPlugins (selectedPlugin, draggingPluginIndex);
        selectedPlugin = draggingPluginIndex;
    }

    draggingPluginIndex = -1;
    repaint ();
}


//==============================================================================
void TrackComponent::dropPluginOnTrack (const String& pluginPath,
                                        int mouseX,
                                        int mouseY)
{
    if (track)
    {
        int pluginIndex = getPluginIndexFromMousePosition (mouseX, mouseY);
        pluginIndex = jmax (pluginIndex + 1, 0);

        // close the previously released
        /*
        if (getWidth () - mouseX > 20)
        {
            if (plugin)
            {
                if (owner->isPluginEditorWindowOpen ())
                    owner->closePluginEditorWindow ();

                track->closePlugin (plugin);
            }
        }
        */

        // open another one, or 0 if cannot be open
        BasePlugin* plugin = track->loadPlugin (pluginPath);
        if (plugin)
        {
            Config::getInstance ()->addRecentPlugin (File (pluginPath));
            // track->insertPlugin (plugin, pluginIndex);
        }

        if (owner->isPluginEditorWindowOpen (plugin))
            owner->openPluginEditorWindow (plugin);

        // update gui
        repaint ();
    }
}

bool TrackComponent::loadAndAppendPlugin (const File& file)
{
    if (track)
    {
        BasePlugin* newPlugin = track->loadPlugin (file.getFullPathName ());
        if (newPlugin)
        {
            Config::getInstance ()->addRecentPlugin (file);
            track->addPlugin (newPlugin);

            repaint ();
            return true;
        }
    }
    return false;
}

bool TrackComponent::loadAndAppendPlugin ()
{
    FileChooser myChooser (T("Load a VST plugin..."),
                            Config::getInstance ()->lastPluginDirectory,
                            T("*.so"));

    if (myChooser.browseForFileToOpen())
    {
        File fileToLoad = myChooser.getResult();
        if (track && fileToLoad.existsAsFile())
        {
            BasePlugin* newPlugin = track->loadPlugin (fileToLoad.getFullPathName ());
            if (newPlugin)
            {
                Config::getInstance ()->addRecentPlugin (fileToLoad);
                track->addPlugin (newPlugin);

                repaint ();
                return true;
            }
        }
    }
    return false;
}

bool TrackComponent::closePlugin (const int index)
{
    if (track)
    {
        BasePlugin* plugin = track->getPluginByIndex (index);
        if (plugin)
            track->closePlugin (plugin);

        repaint ();
        return true;
    }
    return false;
}

int TrackComponent::getPluginsCount () const
{
    return track ? track->getPluginsCount() : 0;
}


//==============================================================================
int TrackComponent::getPluginIndexFromMousePosition (const int x, const int y)
{
    int index = -1;
    if (track && track->getPluginsCount ())
    {
        index = x / (getWidth() / track->getPluginsCount ());
        index = jmin (jmax (index, 0), track->getPluginsCount () - 1);
    }
    return index;
}

BasePlugin* TrackComponent::getPluginFromMousePosition (const int x, const int y)
{
    BasePlugin* plugin = 0;
    if (track && track->getPluginsCount ())
    {
        int width = getWidth() / track->getPluginsCount ();
        plugin = track->getPluginByIndex (x / width);
    }
    return plugin;
}

#endif
