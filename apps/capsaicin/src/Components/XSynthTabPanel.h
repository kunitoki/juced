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

#ifndef __JUCETICE_XSYNTHTABPANEL_HEADER__
#define __JUCETICE_XSYNTHTABPANEL_HEADER__

#include "../XSynthPlugin.h"
#include "XSynthPatch.h"
#include "XSynthMixer.h"
#include "XSynthBankSelect.h"
#include "XSynthOptions.h"
#include "XSynthAbout.h"

//==============================================================================
/**
    This is the Component that our filter will use as its UI.

*/
class XSynthTabPanel  : public TabbedComponent
{
public:

    //==============================================================================
    /** Constructor.
    */
    XSynthTabPanel (XSynthPlugin* plugin_,
                    Master* master_);

    /** Destructor. */
    ~XSynthTabPanel ();

    //==============================================================================
    /** XXX
    */
    void currentTabChanged (const int newCurrentTabIndex,
                            const String &newCurrentTabName);

    //==============================================================================
    void openPartEditor (const int partNumber);
    void updatePresetSelector ();
    void updateControls ();

private:

    XSynthPlugin* plugin;
    Master* master;

    TabbedComponent* mainTab;
    XSynthPatch* patchComponent;
    XSynthMixer* mixerComponent;
    XSynthBankSelect* presetComponent;
    XSynthOptions* optionsComponent;
    XSynthAbout* aboutComponent;
};


#endif // __JUCETICE_XSYNTHTABPANEL_HEADER__
