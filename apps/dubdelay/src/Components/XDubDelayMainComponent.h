/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  18 Jan 2010 2:02:57 pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_XDUBDELAYMAINCOMPONENT_XDUBDELAYMAINCOMPONENT_778BDD28__
#define __JUCER_HEADER_XDUBDELAYMAINCOMPONENT_XDUBDELAYMAINCOMPONENT_778BDD28__

//[Headers]     -- You can add your own extra header files here --
#include "../StandardHeader.h"
class XDubDelayPlugin;
class XDubDelayComponent;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class XDubDelayMainComponent  : public Component,
                                public SliderListener
{
public:
    //==============================================================================
    XDubDelayMainComponent (XDubDelayComponent* const editor_, XDubDelayPlugin* const plugin_);
    ~XDubDelayMainComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void updateControls ();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    XDubDelayComponent* editor;
    XDubDelayPlugin* plugin;
    //[/UserVariables]

    //==============================================================================
    Label* label;
    ImageSlider* delaySlider;
    ImageSlider* feedbackSlider;
    ImageSlider* toneSlider;
    ImageSlider* lfoDepthSlider;
    ImageSlider* lfoSpeedSlider;
    ImageSlider* dryWetSlider;
    ImageSlider* outputSlider;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    XDubDelayMainComponent (const XDubDelayMainComponent&);
    const XDubDelayMainComponent& operator= (const XDubDelayMainComponent&);
};


#endif   // __JUCER_HEADER_XDUBDELAYMAINCOMPONENT_XDUBDELAYMAINCOMPONENT_778BDD28__
