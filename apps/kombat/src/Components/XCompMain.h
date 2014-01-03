/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  18 Jan 2010 2:34:24 pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_XCOMPMAIN_XCOMPMAIN_664CF200__
#define __JUCER_HEADER_XCOMPMAIN_XCOMPMAIN_664CF200__

//[Headers]     -- You can add your own extra header files here --
#include "../StandardHeader.h"
#include "Utils/MultipleEQGraph.h"

class XCompPlugin;
class XCompComponent;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class XCompMain  : public Component,
                   public SliderListener
{
public:
    //==============================================================================
    XCompMain (XCompPlugin* plugin_,XCompComponent* editor_);
    ~XCompMain();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    XCompPlugin* plugin;
    XCompComponent* editor;
    //[/UserVariables]

    //==============================================================================
    GroupComponent* lowGroup;
    GroupComponent* midGroup;
    GroupComponent* hiGroup;
    EQGraph* loGraph;
    GroupComponent* globalGroup;
    ImageSlider* loGainSlider;
    ImageSlider* loThresoldSlider;
    ImageSlider* loRatioSlider;
    ImageSlider* loMakeupSlider;
    ParameterSlider* loAttackSlider;
    ParameterSlider* loReleaseSlider;
    GroupComponent* loFreqGroup;
    GroupComponent* loFreqGroup2;
    ImageSlider* loFreqSlider;
    ImageSlider* hiFreqSlider;
    EQGraph* midGraph;
    EQGraph* hiGraph;
    ImageSlider* midGainSlider;
    ImageSlider* midThresoldSlider;
    ImageSlider* midRatioSlider;
    ImageSlider* midMakeupSlider;
    ParameterSlider* midAttackSlider;
    ParameterSlider* midReleaseSlider;
    ImageSlider* hiGainSlider;
    ImageSlider* hiThresoldSlider;
    ImageSlider* hiRatioSlider;
    ImageSlider* hiMakeupSlider;
    ParameterSlider* hiAttackSlider;
    ParameterSlider* hiReleaseSlider;
    ParameterSlider* bwSlider;
    ParameterSlider* gainSlider;
    ParameterSlider* drywetSlider;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    XCompMain (const XCompMain&);
    const XCompMain& operator= (const XCompMain&);
};


#endif   // __JUCER_HEADER_XCOMPMAIN_XCOMPMAIN_664CF200__
