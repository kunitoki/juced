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

#include "AudioSequenceComponent.h"
#include "../HostFilterComponent.h"
#include "utility/AudioBufferDisplay.h"

#if 0


//==============================================================================
AudioSequenceComponent::AudioSequenceComponent (HostFilterComponent* owner_)
    : Component (T("sequence")),
      owner (owner_),
      currentZoom (15.0f),
      selectedEvent (-1),
      draggingEventIndex (-1)
{
    setOpaque (false);
    setBufferedToImage (false);
}

AudioSequenceComponent::~AudioSequenceComponent()
{
    setSequence (0);
}

//==============================================================================
void AudioSequenceComponent::setSequence (SequenceAudioSource* sequenceToDisplay)
{
    sequence = sequenceToDisplay;
}

//==============================================================================
void AudioSequenceComponent::paint (Graphics& g)
{
    Colour backgroundColour = Config::getInstance ()->getColour (T("mainBackground"));
    g.fillAll (backgroundColour);

    if (sequence && sequence->getNumEvents () > 0)
    {
        int offsetX = 4, offsetY = 4;
        int currentX = offsetX, currentY = offsetY;

//        int width = (getWidth() - 2 * currentX);
        int height = (getHeight () - 2 * currentY);

        // determine the visible vertical dividers (bars)

        // paint each event in the queue
        float deltaEvent = getZoomDelta ();

        for (int i = 0; i < sequence->getNumEvents (); i++)
        {
            int eventOffset, eventLength;
            sequence->getEventTimeAndLength (i, eventOffset, eventLength);

            g.setColour (backgroundColour);
            g.fillRoundedRectangle (currentX + eventOffset * deltaEvent,
                                    currentY,
                                    (eventOffset + eventLength) * deltaEvent,
                                    height,
                                    5.0f);

            if (selectedEvent == i)
                g.setColour (Colours::green);
            else
                g.setColour (Colours::grey);

            g.drawRoundedRectangle (currentX + eventOffset * deltaEvent,
                                    currentY,
                                    (eventOffset + eventLength) * deltaEvent,
                                    height,
                                    5.0f, 2.0f);

            SequenceAudioSource::AudioEventHolder* event = sequence->getEventPointer (i);
            AudioBufferDisplay waveDisplay (event->audioBuffer, event->resampleRatio);
            waveDisplay.paintAudioBuffer (g,
                                          currentX + (int) (eventOffset * deltaEvent),
                                          currentY,
                                          (int) (eventLength * deltaEvent),
                                          height);

            // currentX += width + offsetX;
        }
/*
        if (draggingPluginIndex != -1)
        {
            int drawX = draggingPluginIndex * (width);

            if (draggingPluginIndex == 0) drawX += 1;
            else                          drawX += offsetX / 2;

            g.setColour (Colours::red);
            g.drawLine (drawX, currentY,
                        drawX, currentY + height, 2.0f);
        }
*/
    }
    else
    {
        g.setFont (Font (18.0f, Font::italic));
        g.setColour (backgroundColour.darker (1.5f));
        g.drawText (T("Sequence events !"),
                    0, 0,
                    getWidth (), getHeight (),
                    Justification::centred,
                    false);
    }
}

//==============================================================================
void AudioSequenceComponent::mouseDown (const MouseEvent& e)
{
    if (e.mods.isLeftButtonDown ())
    {
        int newSelectedEvent = getEventIndexFromMousePosition (e.x, e.y);
        if (newSelectedEvent != selectedEvent)
        {
            selectedEvent = newSelectedEvent;
            repaint (); // TODO - be smart please, repaint only this rectangle !
        }

        if (selectedEvent != -1)
            startDocking (e);
    }
    else if (e.mods.isPopupMenu ()
             && selectedEvent != -1)
    {
/*
        SequenceAudioSource::AudioEventHolder* event = sequence->getEventPointer (selectedEvent);

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
                if (owner->isPluginEditorWindowOpen ())
                    owner->closePluginEditorWindow ();

                if (plugin)
                    track->closePlugin (plugin);
                break;

            case 3: // Insert new plugin
                loadAndAppendPlugin ();
                break;

            case 4: // Previous
                track->swapPlugins (selectedPlugin, selectedPlugin - 1);
                selectedPlugin--;
                break;

            case 5: // Next
                track->swapPlugins (selectedPlugin, selectedPlugin + 1);
                selectedPlugin++;
                break;

            case 0: // dismiss
            default:
                break;
        }
*/
        repaint ();
    }
}

void AudioSequenceComponent::mouseDrag (const MouseEvent& e)
{
    if (e.mods.isLeftButtonDown ()
        && selectedEvent != -1)
    {
        continueDocking (e);
    }
    else if (e.mods.isPopupMenu ())
    {
        currentZoom += e.getDistanceFromDragStartY();

        currentZoom = jmax (1.0f, currentZoom);

        repaint ();
    }
}

void AudioSequenceComponent::mouseUp (const MouseEvent& e)
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

void AudioSequenceComponent::mouseDoubleClick (const MouseEvent& e)
{
/*
    if (e.mods.isLeftButtonDown () && track)
    {
        VstPlugin* plugin = getPluginFromMousePosition (e.x, e.y);
        if (plugin)
            owner->openPluginEditorWindow (plugin);
    }
*/
}

bool AudioSequenceComponent::filesDropped (const StringArray& filenames,
                                           int mouseX,
                                           int mouseY)
{
/*
    if (filenames.size())
        dropPluginOnTrack (filenames[0], mouseX, mouseY);
*/

    return true;
}


//==============================================================================
String AudioSequenceComponent::getDragDescription ()
{
    return getName();
}

Image* AudioSequenceComponent::getDragImage ()
{
/*
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
                      track->getPlugin (selectedPlugin)->getName (),
                      true);

    dragImage->multiplyAllAlphas (0.6f);
    return dragImage;
*/
    return 0;
}

Component* AudioSequenceComponent::getDragComponent ()
{
    return this;
}


//==============================================================================
bool AudioSequenceComponent::isInterestedInDragSource (const String& sourceDescription)
{
    // normally you'd check the sourceDescription value to see if it's the
    // sort of object that you're interested in before returning true, but for
    // the demo, we'll say yes to anything..
    return true;
}

void AudioSequenceComponent::itemDragEnter (const String& sourceDescription,
                                            Component* sourceComponent,
                                            int x, int y)
{
    draggingEventIndex = getEventIndexFromMousePosition (x, y);
    repaint();
}

void AudioSequenceComponent::itemDragMove (const String& sourceDescription,
                                           Component* sourceComponent,
                                           int x, int y)
{
    draggingEventIndex = getEventIndexFromMousePosition (x, y);
    repaint ();
}

void AudioSequenceComponent::itemDragExit (const String& sourceDescription,
                                           Component* sourceComponent)
{
    draggingEventIndex = -1;
    repaint();
}

void AudioSequenceComponent::itemDropped (const String& sourceDescription,
                                          Component* sourceComponent,
                                          int x, int y)
{
    draggingEventIndex = getEventIndexFromMousePosition (x, y);

/*
    if (track
        && selectedPlugin != draggingPluginIndex
        && draggingPluginIndex != -1)
    {
        DBG (String (selectedPlugin) + " " + String (draggingPluginIndex));

        track->swapPlugins (selectedPlugin, draggingPluginIndex);
        selectedPlugin = draggingPluginIndex;
    }

    draggingPluginIndex = -1;
    repaint ();
*/
}

//==============================================================================
float AudioSequenceComponent::getZoomDelta () const
{
    return 1.0f / (currentZoom * 1.0f);
}

int AudioSequenceComponent::getEventIndexFromMousePosition (const int x, const int y) const
{
    int index = -1;

    if (sequence)
    {
        int offsetX = 4; // , offsetY = 4;
        float deltaEvent = getZoomDelta ();

        for (int i = sequence->getNumEvents (); --i >= 0;)
        {
            int eventOffset, eventLength;
            sequence->getEventTimeAndLength (i, eventOffset, eventLength);

            if (x > (offsetX + eventOffset * deltaEvent)
                && x < (offsetX + (eventOffset + eventLength) * deltaEvent))
            {
                index = i;
                break;
            }
        }
    }
    return index;
}

#endif
