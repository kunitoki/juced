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

#include "VstPluginWindowContent.h"
#include "../../HostFilterComponent.h"

//==============================================================================
VstPluginWindowContent::VstPluginWindowContent (PluginEditorWindowHolder* owner_,
                                                BasePlugin* plugin_,
                                                VstPluginWindow* window_,
                                                VstPluginNativeEditor* nativeEditor,
                                                VstPluginExternalEditor* externalEditor)
  : owner (owner_),
    plugin (plugin_),
    window (window_),
    mainPanel (0),
    midiKeyboard (0)
{
    DBG ("VstPluginWindowContent::VstPluginWindowContent");

    // main tabbed panel
    addAndMakeVisible (mainPanel = new VstPluginWindowTabPanel (owner,
                                                                plugin,
                                                                window,
                                                                this,
                                                                nativeEditor,
                                                                externalEditor));

    mainPanel->setTabBarDepth (getTabbedPanelHeight ());

    // midi keyboard
    int shouldActivateKeys = plugin->getIntValue (PROP_WINDOWVISIBLEMIDIKEY, plugin->acceptsMidi ());
    activateMidiKeyboard (shouldActivateKeys == 1);
}

VstPluginWindowContent::~VstPluginWindowContent ()
{
    DBG ("VstPluginWindowContent::~VstPluginWindowContent");

    deleteAndZero (mainPanel);
    deleteAndZero (midiKeyboard);
}

//==============================================================================
void VstPluginWindowContent::resized ()
{
    if (midiKeyboard)
    {
        int keyboardHeight = getMidiKeyboardHeight ();
        mainPanel->setBounds (0, 0, getWidth(), getHeight() - keyboardHeight);
        midiKeyboard->setBounds (0, getHeight() - keyboardHeight, getWidth(), keyboardHeight);
    }
    else
    {
        mainPanel->setBounds (0, 0, getWidth(), getHeight());
    }
}

//==============================================================================
int VstPluginWindowContent::getTabbedPanelHeight () const
{
    return Config::getInstance ()->defaultTabThickness;
}

//==============================================================================
int VstPluginWindowContent::getCurrentTabIndex () const
{
    return mainPanel->getCurrentTabIndex ();
}

void VstPluginWindowContent::setCurrentTabIndex (const int tabIndex)
{
    mainPanel->setCurrentTabIndex (tabIndex);
}

//==============================================================================
void VstPluginWindowContent::activateMidiKeyboard (const bool isActive)
{
    DBG ("VstPluginWindowContent::activateMidiKeyboard " + String (isActive));

    if (plugin->acceptsMidi ())
    {
        if (isActive)
        {
            if (midiKeyboard == 0)
            {
                Colour backgroundColour = window->getBackgroundColour ();

                addAndMakeVisible (midiKeyboard = new MidiKeyboardComponent (plugin->getKeyboardState (),
                                                                             MidiKeyboardComponent::horizontalKeyboard));
                midiKeyboard->setMidiChannel (1);
                midiKeyboard->setMidiChannelsToDisplay (1 << 0);
                midiKeyboard->setKeyPressBaseOctave (3);
                midiKeyboard->setLowestVisibleKey (12);
                midiKeyboard->setKeyWidth (11);
                midiKeyboard->setColour (MidiKeyboardComponent::upDownButtonBackgroundColourId, backgroundColour);
                midiKeyboard->setColour (MidiKeyboardComponent::upDownButtonArrowColourId, backgroundColour.contrasting (1.0f));

                window->setSize (window->getWidth(), window->getHeight () + getMidiKeyboardHeight ());
            }
        }
        else
        {
            if (midiKeyboard != 0)
            {
                deleteAndZero (midiKeyboard);

                window->setSize (window->getWidth(), window->getHeight () - getMidiKeyboardHeight ());
            }
        }

        plugin->setValue (PROP_WINDOWVISIBLEMIDIKEY, isActive ? 1 : 0);
    }
}
