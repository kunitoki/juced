/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  26 Jun 2007 1:01:20 pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_XSYNTHMIXER_XSYNTHMIXER_1B36DAE1__
#define __JUCER_HEADER_XSYNTHMIXER_XSYNTHMIXER_1B36DAE1__

//[Headers]     -- You can add your own extra header files here --
#include "../StandardHeader.h"
#include "../XSynthPlugin.h"
#include "../Misc/Master.h"
//[/Headers]

#include "XSynthMixerStrip.h"


//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class XSynthMixer  : public Component,
                     public Timer,
                     public SliderListener
{
public:
    //==============================================================================
    XSynthMixer (XSynthPlugin* plugin_, Master* master_);
    ~XSynthMixer();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void updateControls ();
    void timerCallback ();
    void setSoloChannel (const int soloChannel);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    friend class XSynthMixerStrip;

    XSynthPlugin* plugin;
    Master* master;
    XSynthMixerStrip* parts [16];
    //[/UserVariables]

    //==============================================================================
    XSynthMixerStrip* part01;
    XSynthMixerStrip* part02;
    XSynthMixerStrip* part03;
    XSynthMixerStrip* part04;
    XSynthMixerStrip* part05;
    XSynthMixerStrip* part06;
    XSynthMixerStrip* part07;
    XSynthMixerStrip* part08;
    XSynthMixerStrip* part09;
    XSynthMixerStrip* part10;
    XSynthMixerStrip* part11;
    XSynthMixerStrip* part12;
    XSynthMixerStrip* part13;
    XSynthMixerStrip* part14;
    XSynthMixerStrip* part15;
    XSynthMixerStrip* part16;
    GroupComponent* masterGroup;
    ImageSlider* masterGainSlider;
    Slider* reverbTimeSlider;
    Slider* reverbGainSlider;
    Slider* reverbTailSlider;
    Slider* reverbDampSlider;
    MeterComponent* leftMeter;
    MeterComponent* rightMeter;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    XSynthMixer (const XSynthMixer&);
    const XSynthMixer& operator= (const XSynthMixer&);
};


#endif   // __JUCER_HEADER_XSYNTHMIXER_XSYNTHMIXER_1B36DAE1__
