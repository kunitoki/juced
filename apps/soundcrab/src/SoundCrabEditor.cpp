/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2004 by Lucio Asnaghi.

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

#include "SoundCrabEditor.h"


//==============================================================================
SoundCrabEditor::SoundCrabEditor (SoundCrabPlugin* const ownerFilter_)
    : AudioProcessorEditor (ownerFilter_)
{
    static JuceticeLookAndFeel juceticeLookAndFeel;
    LookAndFeel::setDefaultLookAndFeel (&juceticeLookAndFeel);

    getFilter()->addChangeListener (this);
    // getFilter()->addListenerToParameters (this);

    // soundfont file chooser
    mainComponent = new SoundCrabMainComponent (this, getFilter ());
    aboutComponent = new SoundCrabAboutComponent (this, getFilter ());

    addAndMakeVisible (tabComponent = new TabbedComponent (TabbedButtonBar::TabsAtRight));
    tabComponent->addTab (T("Player"), Colour (0xff598868), mainComponent, false);
    tabComponent->addTab (T("About"), Colour (0xff598868), aboutComponent, false);
    tabComponent->setCurrentTabIndex (0);
    tabComponent->setTabBarDepth (26);

    // set visible
    setSize (480 + tabComponent->getTabBarDepth (),
             245);
}

SoundCrabEditor::~SoundCrabEditor()
{
    deleteAllChildren();

    getFilter()->removeChangeListener (this);
    // getFilter()->removeListenerToParameters (this);
}

//==============================================================================
void SoundCrabEditor::resized()
{
    tabComponent->setBounds (0, 0, getWidth(), getHeight());
}

//==============================================================================
void SoundCrabEditor::paint (Graphics& g)
{
    g.fillAll (Colour (64, 64, 64));
}

//==============================================================================
void SoundCrabEditor::changeListenerCallback (void* source)
{
    if (source == getFilter())
    {
        // if it's the param manager telling us that it's changed
        // we should update the correct control controls

        // TODO - update other gui controls
        mainComponent->updateControls ();
    }
}

//==============================================================================
void SoundCrabEditor::parameterChanged (AudioParameter* parameter, const int index)
{
    // DBG (T("PARAMETER ") + String (index) + T(" changed"));
}
