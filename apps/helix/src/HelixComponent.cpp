/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2008 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2004 by Julian Storer.

 ------------------------------------------------------------------------------

 JUCE and JUCETICE can be redistributed and/or modified under the terms of
 the GNU General Public License, as published by the Free Software Foundation;
 either version 2 of the License, or (at your option) any later version.

 JUCE and JUCETICE are distributed in the hope that they will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with JUCE and JUCETICE; if not, visit www.gnu.org/licenses or write to
 Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 Boston, MA 02111-1307 USA

 ------------------------------------------------------------------------------

 If you'd like to release a closed-source product which uses JUCE, commercial
 licenses are also available: visit www.rawmaterialsoftware.com/juce for
 more information.

 ==============================================================================
*/

#include "HelixComponent.h"


//==============================================================================
HelixComponent::HelixComponent (HelixPlugin* const ownerFilter_)
    : AudioProcessorEditor (ownerFilter_),
      mainComponent (0),
      midiKeyboard (0)
{
    static JuceticeLookAndFeel juceticeLookAndFeel;
    LookAndFeel::setDefaultLookAndFeel (&juceticeLookAndFeel);

    // register ourselves with the plugin - it will use its ChangeBroadcaster base
    // class to tell us when something has changed.
    getFilter()->addChangeListener (this);
//    getFilter()->addListenerToParameters (this);

    // add the main component
    mainComponent = new Viewport (String::empty);
    mainComponent->setScrollBarsShown (true, false);
    mainComponent->setViewedComponent (new NativeEditor (getFilter(), this));

    addAndMakeVisible (mainComponent);

    addAndMakeVisible (midiKeyboard = new MidiKeyboardComponent (getFilter()->getKeyboardState(),
                                                                 MidiKeyboardComponent::horizontalKeyboard));
    midiKeyboard->setMidiChannel (1);
    midiKeyboard->setMidiChannelsToDisplay (1 << 0);
    midiKeyboard->setKeyPressBaseOctave (3);
    midiKeyboard->setLowestVisibleKey (12);
    midiKeyboard->setKeyWidth (11);
    midiKeyboard->setColour (MidiKeyboardComponent::upDownButtonBackgroundColourId, Colours::black);
    midiKeyboard->setColour (MidiKeyboardComponent::upDownButtonArrowColourId, Colours::white);

    setSize (640, 480);

/*
    setSize (mainComponent->getWidth(),
             mainComponent->getHeight());

    mainComponent->updateControls ();
*/
}

HelixComponent::~HelixComponent()
{
    LookAndFeel::setDefaultLookAndFeel (0);

    deleteAndZero (mainComponent);
    deleteAndZero (midiKeyboard);

    getFilter()->removeChangeListener (this);
//    getFilter()->removeListenerToParameters (this);
}

//==============================================================================
void HelixComponent::resized()
{
    const int keyHeight = 45;
    
    mainComponent->setBounds (0, 0, getWidth(), getHeight() - keyHeight);
    midiKeyboard->setBounds (0, getHeight() - keyHeight, getWidth(), keyHeight);
}

//==============================================================================
void HelixComponent::paint (Graphics& g)
{
    g.fillAll (Colours::white);
}

//==============================================================================
void HelixComponent::changeListenerCallback (void* source)
{
    if (source == getFilter())
    {
        //mainComponent->updateControls ();
    }
}

//==============================================================================
void HelixComponent::parameterChanged (AudioParameter* parameter, const int index)
{
}
