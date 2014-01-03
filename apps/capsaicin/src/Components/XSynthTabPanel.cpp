/*
  ==============================================================================

  XSynth -o- Add-Tractive delight for EnergyXT2
  Copyright 2007 by kRAkEn/gORe sounds.

  Creation:       Jan 2007
  Author:         Asnaghi Lucio
  Website:        (www.anticore.org)

  The XSynth is written with the "Jucetice library" - which is based around
  Raw Material Software ltd. "JUCE library" (Copyright 2004-7)

  ==============================================================================
*/

#include "XSynthTabPanel.h"


//==============================================================================
XSynthTabPanel::XSynthTabPanel (XSynthPlugin* plugin_,
                                Master* master_)
    : TabbedComponent (TabbedButtonBar::TabsAtRight),
      plugin (plugin_),
      master (master_)
{
    setOutline (0);

    // sub components
    patchComponent = new XSynthPatch (plugin, master);
    mixerComponent = new XSynthMixer (plugin, master);
    presetComponent = new XSynthBankSelect (plugin, master);
    optionsComponent = new XSynthOptions ();
    aboutComponent = new XSynthAbout ();

    // prepare and add tabs
    addTab (T("Patch Editor"), Colour (0xff827474), patchComponent, false);
    addTab (T("Mixer"), Colour (0xff827474), mixerComponent, false);
    addTab (T("Options"), Colour (0xff827474), optionsComponent, false);
    addTab (T("Presets"), Colour (0xff827474), presetComponent, false);
    addTab (T("About"), Colour (0xff827474), aboutComponent, false);

    // restore last opened page
    int lastOpenedPage = Config::getInstance ()->LastOpenedPage;
    setCurrentTabIndex (lastOpenedPage);
}

XSynthTabPanel::~XSynthTabPanel()
{
    // remember last opened page
    Config::getInstance ()->LastOpenedPage = getCurrentTabIndex ();

    // do cleanup
    clearTabs ();
    deleteAndZero (patchComponent);
    deleteAndZero (mixerComponent);
    deleteAndZero (optionsComponent);
    deleteAndZero (aboutComponent);
}

//==============================================================================
void XSynthTabPanel::currentTabChanged (const int newCurrentTabIndex,
                                        const String &newCurrentTabName)
{
    switch (newCurrentTabIndex)
    {
    case 0: // patchComponent
        patchComponent->updateControls ();
        mixerComponent->stopTimer ();
        break;
    case 1: // mixerComponent
        mixerComponent->updateControls ();
        mixerComponent->startTimer (50);
        break;
    case 2: // optionsComponent
        mixerComponent->stopTimer ();
        break;
    case 3: // presetComponent
        mixerComponent->stopTimer ();
        break;
    case 4: // aboutComponent
        mixerComponent->stopTimer ();
        // aboutComponent->startTimer (50);
        break;
    }
}

//==============================================================================
void XSynthTabPanel::openPartEditor (const int partNumber)
{
    patchComponent->setPartNumber (partNumber);
    patchComponent->updateControls ();

    setCurrentTabIndex (0);
}

void XSynthTabPanel::updateControls ()
{
    patchComponent->updateControls ();
    mixerComponent->updateControls ();
}

void XSynthTabPanel::updatePresetSelector ()
{
    presetComponent->updatePresetSelector ();
}

