/***************************************************************************
 *   Copyright (C) 2009 by Christian Borss                                 *
 *   christian.borss@rub.de                                                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#include "../windows_quirks.h"
#include "includes.h"
#include "../MasterAndCommander.h"
#include "EditorComponent.h"
#include "TabMain.h"
//#include "TabModulation.h"
#include "TabTimbre.h"
#include "TabPresetEditor.h"
#include "TabPreferences.h"
#include "TabAbout.h"

//==============================================================================
EditorComponent::EditorComponent (HybridReverb2Processor* const ownerFilter)
    : AudioProcessorEditor (ownerFilter),
      tabMain(0),
//      tabModulation(0),
      tabTimbre(0),
      tabPresetEditor(0),
      tabPreferences(0),
      tabAbout(0)
{
    master = ownerFilter->getMaster();
    myTabbedComponent = new MyTabbedComponent(TabbedButtonBar::TabsAtTop, this);
    addAndMakeVisible(myTabbedComponent);
    myTabbedComponent->setTabBarDepth(30);

    tabMain = new TabMain(master);
    myTabbedComponent->addTab(JUCE_T("Main"),
                              Colour(0xffffe000),
                              tabMain,
                              true);

/*
    tabModulation = new TabModulation(master);
    myTabbedComponent->addTab(JUCE_T("Modulation"),
                              Colour(0xffffe000),
                              tabModulation,
                              true);
*/

    tabTimbre = new TabTimbre(master);
    myTabbedComponent->addTab(JUCE_T("Timbre"),
                              Colour(0xffffe000),
                              tabTimbre,
                              true);

    tabPresetEditor = new TabPresetEditor(master);
    myTabbedComponent->addTab(JUCE_T("Preset Editor"),
                              Colour(0xffffe000),
                              tabPresetEditor,
                              true);

    tabPreferences = new TabPreferences(master);
    myTabbedComponent->addTab(JUCE_T("Preferences"),
                              Colour(0xffffe000),
                              tabPreferences,
                              true);

    tabAbout = new TabAbout(master);
    myTabbedComponent->addTab(JUCE_T("About"),
                              Colour(0xffffe000),
                              tabAbout,
                              true);

    myTabbedComponent->setCurrentTabIndex (0);

    // create our gain slider..
//    addAndMakeVisible (gainSlider = new Slider (T("gain")));
//    gainSlider->addListener (this);
//    gainSlider->setRange (0.0, 1.0, 0.01);
//    gainSlider->setTooltip (T("changes the volume of the audio that runs through the plugin.."));

    // get the gain parameter from the filter and use it to set up our slider
//    gainSlider->setValue (ownerFilter->getParameter (0), false);

    // set our component's initial size to be the last one that was stored in the filter's settings
    setSize (ownerFilter->lastUIWidth,
             ownerFilter->lastUIHeight);

    // register ourselves with the filter - it will use its ChangeBroadcaster base
    // class to tell us when something has changed, and this will call our changeListenerCallback()
    // method.
    ownerFilter->addChangeListener (this);

    master->registerEditorComponent(this);
}

EditorComponent::~EditorComponent()
{
    master->print(T("%%% EditorComponent destructor called%%%\n\n"));
    getFilter()->removeChangeListener (this);
    deleteAndZero (myTabbedComponent);
    myTabbedComponent = 0;

    deleteAllChildren();
}


//==============================================================================
void EditorComponent::currentTabChanged(const int newCurrentTabIndex,
                                        const String &newCurrentTabName)
{
    switch (newCurrentTabIndex) {
    case TAB_MAIN:
        break;
//    case TAB_MODULATION:
//        break;
    case TAB_TIMBRE:
        break;
    case TAB_PRESETEDITOR:
        tabPresetEditor->onComponentSelected();
        break;
    case TAB_PREFERENCES:
        break;
    case TAB_ABOUT:
        ;
    }
}

//==============================================================================
void EditorComponent::paint (Graphics& g)
{
    // just clear the window
    g.fillAll (Colours::white);
}

void EditorComponent::resized()
{
//    gainSlider->setBounds (10, 10, 200, 22);

    // if we've been resized, tell the filter so that it can store the new size
    // in its settings
    getFilter()->lastUIWidth = getWidth();
    getFilter()->lastUIHeight = getHeight();
    myTabbedComponent->setBounds (0, 0, 828, 548);
}

//==============================================================================
void EditorComponent::changeListenerCallback (void* source)
{
    // this is the filter telling us that it's changed, so we'll update our
    // display of the time, midi message, etc.
    updateParametersFromFilter();
}

//void EditorComponent::sliderValueChanged (Slider*)
//{
//    getFilter()->setParameterNotifyingHost (0, (float) gainSlider->getValue());
//}

//==============================================================================
void EditorComponent::updateParametersFromFilter()
{
    HybridReverb2Processor* const filter = getFilter();

    // we use this lock to make sure the processBlock() method isn't writing to the
    // lastMidiMessage variable while we're trying to read it, but be extra-careful to
    // only hold the lock for a minimum amount of time..
//    filter->getCallbackLock().enter();

    // take a local copy of the info we need while we've got the lock..
    const float fvalue = filter->getParameter(0);

    // ..release the lock ASAP
//    filter->getCallbackLock().exit();

//    gainSlider->setValue (newGain, false);

    setSize (filter->lastUIWidth,
             filter->lastUIHeight);
    int currentPreset = roundf(fvalue * 255.0 + 1.0);
    master->print(String("EditorComponent::updateParametersFromFilter(): new preset nr. ") + String(currentPreset) + String("\n"));
    master->onValueChangedPresetNum(currentPreset);
}
