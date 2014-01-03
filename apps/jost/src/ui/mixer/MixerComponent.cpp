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

#include "MixerComponent.h"
#include "../../HostFilterComponent.h"


//==============================================================================
MixerComponent::MixerComponent (HostFilterComponent* owner_)
    : host (0),
      owner (owner_)
{
    setOpaque (false);
    setBufferedToImage (false);
}

MixerComponent::~MixerComponent()
{
    clearChannels ();

    setHost (0);
}

//==============================================================================
void MixerComponent::setHost (Host* hostToDisplay)
{
    host = hostToDisplay;

    if (host)
        rebuildChannels ();
}

//==============================================================================
void MixerComponent::rebuildChannels ()
{
    jassert (host != 0);

    clearChannels ();

    int totalWidth = 0;

    for (int i = 0; i < host->getPluginsCount (); i++)
    {
        BasePlugin* plugin = host->getPluginByIndex (i);

        if (plugin
            && (plugin->getNumOutputs () > 0 || plugin->getNumInputs () > 0))
        {
            MixerStripComponent* mixerStrip = new MixerStripComponent (owner, this, plugin);

            addAndMakeVisible (mixerStrip);
            channels.add (mixerStrip);

            totalWidth += mixerStrip->isNarrow () ? 26 : 48;
        }
    }

//    setSize (getWidth(), getHeight ());

    if (getWidth() != totalWidth)
        setSize (totalWidth, getHeight ());
}

void MixerComponent::clearChannels ()
{
    for (int i = 0; i < channels.size (); i++)
        delete (MixerStripComponent*) channels.getUnchecked (i);

    channels.clear ();
}

/*
void MixerComponent::toggleSoloChannel (MixerStripComponent* const strip)
{
    for (int i = 0; i < channels.size (); i++)
    {
       MixerStripComponent* channel = (MixerStripComponent*) channels.getUnchecked (i);

       strip->setSolo (i == channel);
    }
}
*/

//==============================================================================
void MixerComponent::paint (Graphics& g)
{
//    Colour backgroundColour = Config::getInstance ()->getColour (T("mainBackground"));

//    g.fillAll (backgroundColour);
}

void MixerComponent::resized ()
{
    int stripWidth, totalWidth = 0;

    for (int i = 0; i < channels.size (); i++)
    {
        MixerStripComponent* mixerStrip = (MixerStripComponent*) channels.getUnchecked (i);

        stripWidth = mixerStrip->isNarrow () ? 26 : 48;

        mixerStrip->setBounds (totalWidth, 0, stripWidth, getHeight ());

        totalWidth += stripWidth;
    }
}

void MixerComponent::timerCallback ()
{
    for (int i = 0; i < channels.size (); i++)
        ((MixerStripComponent*) channels.getUnchecked (i))->computeMeters ();
}

//==============================================================================
void MixerComponent::mouseDown (const MouseEvent& e)
{
}

void MixerComponent::mouseDrag (const MouseEvent& e)
{
}

void MixerComponent::mouseUp (const MouseEvent& e)
{
}

void MixerComponent::mouseDoubleClick (const MouseEvent& e)
{
}

void MixerComponent::filesDropped (const StringArray& filenames,
                                   int mouseX,
                                   int mouseY)
{
}

//==============================================================================
bool MixerComponent::isInterestedInDragSource (const String& sourceDescription,
                                               Component* /*source*/)
{
    // normally you'd check the sourceDescription value to see if it's the
    // sort of object that you're interested in before returning true, but for
    // the demo, we'll say yes to anything..
    return false;
}

void MixerComponent::itemDragEnter (const String& sourceDescription,
                                    Component* sourceComponent,
                                    int x, int y)
{
}

void MixerComponent::itemDragMove (const String& sourceDescription,
                                   Component* sourceComponent,
                                   int x, int y)
{
}

void MixerComponent::itemDragExit (const String& sourceDescription,
                                   Component* sourceComponent)
{
}

void MixerComponent::itemDropped (const String& sourceDescription,
                                  Component* sourceComponent,
                                  int x, int y)
{
}

