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

#include "XSynthEditor.h"

static const int titlebarHeight = 35;
static const int keyboardHeight = 40;
static const int tabButtonWidth = 26;
static const Colour mainColour = Colour (0xff827474);

//==============================================================================
XSynthEditor::XSynthEditor (XSynthPlugin* const ownerFilter_)
    : AudioProcessorEditor (ownerFilter_),
      master (ownerFilter_->getMaster()),
      config (Config::getInstance ()),
      titlebarComponent (0),
      mainTab (0),
      midiKeyboard (0)
{
    static JuceticeLookAndFeel juceticeLookAndFeel;
    LookAndFeel::setDefaultLookAndFeel (&juceticeLookAndFeel);

    // register ourselves with the plugin - it will use its ChangeBroadcaster base
    // class to tell us when something has changed.
    getFilter()->addChangeListener (this);
    // getFilter()->addListenerToParameters (this);

    // titlebar component
    addAndMakeVisible (titlebarComponent = new XSynthTitleBar (getFilter(), master));

    // tab panel component
    addAndMakeVisible (mainTab = new XSynthTabPanel (getFilter(), master));
    mainTab->setTabBarDepth (tabButtonWidth);

    // piano component (if visible)
    if (config->IsKeyboardVisible)
        setKeyboardVisible (true);
    else
        setKeyboardVisible (false);

    // set the size
    setSize (680 + tabButtonWidth,
             400 + (config->IsKeyboardVisible ? keyboardHeight : 0)
             + titlebarHeight);
}

XSynthEditor::~XSynthEditor()
{
    getFilter()->removeChangeListener (this);
    // getFilter()->removeListenerToParameters (this);

    deleteAndZero (titlebarComponent);
    deleteAndZero (mainTab);
    deleteAndZero (midiKeyboard);
}

//==============================================================================
void XSynthEditor::paint (Graphics& g)
{
    g.fillAll (Colour (64, 64, 64));
}

void XSynthEditor::resized()
{
    int keyHeight = midiKeyboard ? keyboardHeight : 0;

    titlebarComponent->setBounds (0, 0,
                                  getWidth() - tabButtonWidth,
                                  titlebarHeight);

    mainTab->setBounds (0, titlebarHeight,
                        getWidth(),
                        getHeight() - keyHeight - titlebarHeight);

    if (midiKeyboard)
    {
        midiKeyboard->setBounds (0,
                                getHeight() - keyHeight,
                                getWidth() - tabButtonWidth,
                                keyHeight);
    }
}

//==============================================================================
void XSynthEditor::changeListenerCallback (void* source)
{
    if (source == getFilter())
    {
        // if it's the plugin manager telling us that it's changed
        // we should update the correct controls (new preset)

        mainTab->updateControls ();
    }
}

void XSynthEditor::parameterChanged (AudioParameter* parameter, const int index)
{
//    DBG (T("PARAMETER ") + String (index) + T(" changed"));
}

//==============================================================================
void XSynthEditor::updatePresetSelector ()
{
    mainTab->updatePresetSelector ();
}

//==============================================================================
void XSynthEditor::setKeyboardVisible (const bool isVisible)
{
    int dynamicHeight = 0;

    if (isVisible)
    {
        // add piano component
        if (midiKeyboard == 0)
        {
            addAndMakeVisible (midiKeyboard = new MidiKeyboardComponent (getFilter()->keyboardState,
                                                                        MidiKeyboardComponent::horizontalKeyboard));
            midiKeyboard->setMidiChannel (1);
            midiKeyboard->setMidiChannelsToDisplay (1 << 0);
            midiKeyboard->setKeyPressBaseOctave (3);
            midiKeyboard->setLowestVisibleKey (12);
            midiKeyboard->setKeyWidth (11);
            midiKeyboard->setColour (MidiKeyboardComponent::upDownButtonBackgroundColourId, mainColour);
            midiKeyboard->setColour (MidiKeyboardComponent::upDownButtonArrowColourId, Colours::white);
        }

        dynamicHeight = keyboardHeight;
    }
    else
    {
        // remove piano component
        if (midiKeyboard != 0)
        {
            removeChildComponent (midiKeyboard);
            deleteAndZero (midiKeyboard);
        }

        dynamicHeight = 0;
    }

    // set the size WITH or WITHOUT the keyboard
    setSize (680 + tabButtonWidth,
             402 + titlebarHeight + dynamicHeight);

    // update configuration
    config->IsKeyboardVisible = (isVisible == true);
}

void XSynthEditor::setMidiChannel (const int midiChannel)
{
    if (midiKeyboard)
    {
        midiKeyboard->setMidiChannel (midiChannel);
        midiKeyboard->setMidiChannelsToDisplay (1 << (midiChannel - 1));
    }
}
