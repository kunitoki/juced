/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  27 Jul 2008 12:24:04 pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.11

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCETICE_JOST_AUDIOSPECMETEREDITOR_HEADER__
#define __JUCETICE_JOST_AUDIOSPECMETEREDITOR_HEADER__

#include "../../../Config.h"
#include "../../../HostFilterComponent.h"
#include "../../../ui/plugins/PluginEditorComponent.h"

class AudioSpecMeterPlugin;


//==============================================================================
/**

    An auto-generated component, created by the Jucer.
    Describe your class and how it works here!

*/
class AudioSpecMeterEditor  : public PluginEditorComponent,
                              public Timer
{
public:

    //==============================================================================
    AudioSpecMeterEditor (AudioSpecMeterPlugin* owner_);
    ~AudioSpecMeterEditor();

    //==============================================================================
    int getPreferredWidth ()                        { return 480; }
    int getPreferredHeight ()                       { return 150; }
    bool isResizable ()                             { return false; }
    void updateParameters ();
    
    //==============================================================================
    /** @internal */
    void timerCallback ();
    /** @internal */
    void paint (Graphics& g);

    //==============================================================================
    static const char* specmeter_png;
    static const int specmeter_pngSize;

    //==============================================================================
    juce_UseDebuggingNewOperator

private:

    //==============================================================================
	int x2pix (float x);
	int x22pix (float x);

    AudioSpecMeterPlugin* owner;
    Image* backgroundCachedImage;

    float Lpeak, Lrms, Lmin, Rpeak, Rrms, Rmin, Corr;
    float band[2][16];
    int temp, xtimer;
};


#endif
