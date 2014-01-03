/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  18 Jan 2010 11:31:35 am

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_XSYNTHMIXERSTRIP_XSYNTHMIXERSTRIP_960ACC42__
#define __JUCER_HEADER_XSYNTHMIXERSTRIP_XSYNTHMIXERSTRIP_960ACC42__

//[Headers]     -- You can add your own extra header files here --
#include "../StandardHeader.h"
#include "../Misc/Master.h"
#include "../XSynthPlugin.h"
#include "Utils/DynamicParameterSlider.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class XSynthMixerStrip  : public Component,
                          public SliderListener,
                          public ButtonListener
{
public:
    //==============================================================================
    XSynthMixerStrip (XSynthPlugin* plugin_, Master* master_, const int partNumber_);
    ~XSynthMixerStrip();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void updateControls ();
    void setMeterValue (const float newValue);
    void enableSolo (const bool enable);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void buttonClicked (Button* buttonThatWasClicked);


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    XSynthPlugin* plugin;
    Master* master;
    int partNumber;
    //[/UserVariables]

    //==============================================================================
    GroupComponent* groupComponent;
    ImageSlider* volumeSlider;
    ParameterSlider* panSlider;
    Label* panLabel;
    TextButton* editButton;
    Label* volumeLabel;
    MeterComponent* meter;
    TextButton* muteButton;
    TextButton* soloButton;
    DynamicParameterSlider* ctrl1Slider;
    Label* ctrl1Label;
    DynamicParameterSlider* ctrl2Slider;
    Label* ctrl2Label;
    DynamicParameterSlider* ctrl3Slider;
    Label* ctrl3Label;
    DynamicParameterSlider* ctrl4Slider;
    Label* ctrl4Label;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    XSynthMixerStrip (const XSynthMixerStrip&);
    const XSynthMixerStrip& operator= (const XSynthMixerStrip&);
};


#endif   // __JUCER_HEADER_XSYNTHMIXERSTRIP_XSYNTHMIXERSTRIP_960ACC42__
