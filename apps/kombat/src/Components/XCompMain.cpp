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

//[Headers] You can add your own extra header files here...
#include "../XCompPlugin.h"
#include "../XCompComponent.h"
//[/Headers]

#include "XCompMain.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
XCompMain::XCompMain (XCompPlugin* plugin_,XCompComponent* editor_)
    : plugin (plugin_),
      editor (editor_),
      lowGroup (0),
      midGroup (0),
      hiGroup (0),
      loGraph (0),
      globalGroup (0),
      loGainSlider (0),
      loThresoldSlider (0),
      loRatioSlider (0),
      loMakeupSlider (0),
      loAttackSlider (0),
      loReleaseSlider (0),
      loFreqGroup (0),
      loFreqGroup2 (0),
      loFreqSlider (0),
      hiFreqSlider (0),
      midGraph (0),
      hiGraph (0),
      midGainSlider (0),
      midThresoldSlider (0),
      midRatioSlider (0),
      midMakeupSlider (0),
      midAttackSlider (0),
      midReleaseSlider (0),
      hiGainSlider (0),
      hiThresoldSlider (0),
      hiRatioSlider (0),
      hiMakeupSlider (0),
      hiAttackSlider (0),
      hiReleaseSlider (0),
      bwSlider (0),
      gainSlider (0),
      drywetSlider (0)
{
    addAndMakeVisible (lowGroup = new GroupComponent (String::empty,
                                                      T("LOW")));
    lowGroup->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    lowGroup->setColour (GroupComponent::textColourId, Colour (0x66ffffff));

    addAndMakeVisible (midGroup = new GroupComponent (String::empty,
                                                      T("MID")));
    midGroup->setTextLabelPosition (Justification::centred);
    midGroup->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    midGroup->setColour (GroupComponent::textColourId, Colour (0x66ffffff));

    addAndMakeVisible (hiGroup = new GroupComponent (String::empty,
                                                     T("HI")));
    hiGroup->setTextLabelPosition (Justification::centredRight);
    hiGroup->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    hiGroup->setColour (GroupComponent::textColourId, Colour (0x66ffffff));

    addAndMakeVisible (loGraph = new EQGraph());

    addAndMakeVisible (globalGroup = new GroupComponent (String::empty,
                                                         T("GLOBALS")));
    globalGroup->setTextLabelPosition (Justification::centred);
    globalGroup->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    globalGroup->setColour (GroupComponent::textColourId, Colour (0x66ffffff));

    addAndMakeVisible (loGainSlider = new ImageSlider (String::empty));
    loGainSlider->setRange (0, 1, 0.0001);
    loGainSlider->setSliderStyle (Slider::LinearVertical);
    loGainSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    loGainSlider->addListener (this);

    addAndMakeVisible (loThresoldSlider = new ImageSlider (String::empty));
    loThresoldSlider->setRange (0, 1, 0.0001);
    loThresoldSlider->setSliderStyle (Slider::LinearVertical);
    loThresoldSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    loThresoldSlider->addListener (this);

    addAndMakeVisible (loRatioSlider = new ImageSlider (String::empty));
    loRatioSlider->setRange (0, 1, 0.0001);
    loRatioSlider->setSliderStyle (Slider::LinearVertical);
    loRatioSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    loRatioSlider->addListener (this);

    addAndMakeVisible (loMakeupSlider = new ImageSlider (String::empty));
    loMakeupSlider->setRange (0, 1, 0.0001);
    loMakeupSlider->setSliderStyle (Slider::LinearVertical);
    loMakeupSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    loMakeupSlider->addListener (this);

    addAndMakeVisible (loAttackSlider = new ParameterSlider (String::empty));
    loAttackSlider->setRange (0, 1, 0.0001);
    loAttackSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    loAttackSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    loAttackSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    loAttackSlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    loAttackSlider->setColour (Slider::textBoxTextColourId, Colours::black);
    loAttackSlider->addListener (this);

    addAndMakeVisible (loReleaseSlider = new ParameterSlider (String::empty));
    loReleaseSlider->setRange (0, 1, 0.0001);
    loReleaseSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    loReleaseSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    loReleaseSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    loReleaseSlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    loReleaseSlider->setColour (Slider::textBoxTextColourId, Colours::black);
    loReleaseSlider->addListener (this);

    addAndMakeVisible (loFreqGroup = new GroupComponent (String::empty,
                                                         String::empty));
    loFreqGroup->setTextLabelPosition (Justification::centred);
    loFreqGroup->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    loFreqGroup->setColour (GroupComponent::textColourId, Colour (0x66ffffff));

    addAndMakeVisible (loFreqGroup2 = new GroupComponent (String::empty,
                                                          String::empty));
    loFreqGroup2->setTextLabelPosition (Justification::centred);
    loFreqGroup2->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    loFreqGroup2->setColour (GroupComponent::textColourId, Colour (0x66ffffff));

    addAndMakeVisible (loFreqSlider = new ImageSlider (String::empty));
    loFreqSlider->setRange (0, 1, 0.0001);
    loFreqSlider->setSliderStyle (Slider::LinearHorizontal);
    loFreqSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    loFreqSlider->addListener (this);

    addAndMakeVisible (hiFreqSlider = new ImageSlider (String::empty));
    hiFreqSlider->setRange (0, 1, 0.0001);
    hiFreqSlider->setSliderStyle (Slider::LinearHorizontal);
    hiFreqSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    hiFreqSlider->addListener (this);

    addAndMakeVisible (midGraph = new EQGraph());

    addAndMakeVisible (hiGraph = new EQGraph());

    addAndMakeVisible (midGainSlider = new ImageSlider (String::empty));
    midGainSlider->setRange (0, 1, 0.0001);
    midGainSlider->setSliderStyle (Slider::LinearVertical);
    midGainSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    midGainSlider->addListener (this);

    addAndMakeVisible (midThresoldSlider = new ImageSlider (String::empty));
    midThresoldSlider->setRange (0, 1, 0.0001);
    midThresoldSlider->setSliderStyle (Slider::LinearVertical);
    midThresoldSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    midThresoldSlider->addListener (this);

    addAndMakeVisible (midRatioSlider = new ImageSlider (String::empty));
    midRatioSlider->setRange (0, 1, 0.0001);
    midRatioSlider->setSliderStyle (Slider::LinearVertical);
    midRatioSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    midRatioSlider->addListener (this);

    addAndMakeVisible (midMakeupSlider = new ImageSlider (String::empty));
    midMakeupSlider->setRange (0, 1, 0.0001);
    midMakeupSlider->setSliderStyle (Slider::LinearVertical);
    midMakeupSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    midMakeupSlider->addListener (this);

    addAndMakeVisible (midAttackSlider = new ParameterSlider (String::empty));
    midAttackSlider->setRange (0, 1, 0.0001);
    midAttackSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    midAttackSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    midAttackSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    midAttackSlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    midAttackSlider->setColour (Slider::textBoxTextColourId, Colours::black);
    midAttackSlider->addListener (this);

    addAndMakeVisible (midReleaseSlider = new ParameterSlider (String::empty));
    midReleaseSlider->setRange (0, 1, 0.0001);
    midReleaseSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    midReleaseSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    midReleaseSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    midReleaseSlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    midReleaseSlider->setColour (Slider::textBoxTextColourId, Colours::black);
    midReleaseSlider->addListener (this);

    addAndMakeVisible (hiGainSlider = new ImageSlider (String::empty));
    hiGainSlider->setRange (0, 1, 0.0001);
    hiGainSlider->setSliderStyle (Slider::LinearVertical);
    hiGainSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    hiGainSlider->addListener (this);

    addAndMakeVisible (hiThresoldSlider = new ImageSlider (String::empty));
    hiThresoldSlider->setRange (0, 1, 0.0001);
    hiThresoldSlider->setSliderStyle (Slider::LinearVertical);
    hiThresoldSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    hiThresoldSlider->addListener (this);

    addAndMakeVisible (hiRatioSlider = new ImageSlider (String::empty));
    hiRatioSlider->setRange (0, 1, 0.0001);
    hiRatioSlider->setSliderStyle (Slider::LinearVertical);
    hiRatioSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    hiRatioSlider->addListener (this);

    addAndMakeVisible (hiMakeupSlider = new ImageSlider (String::empty));
    hiMakeupSlider->setRange (0, 1, 0.0001);
    hiMakeupSlider->setSliderStyle (Slider::LinearVertical);
    hiMakeupSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    hiMakeupSlider->addListener (this);

    addAndMakeVisible (hiAttackSlider = new ParameterSlider (String::empty));
    hiAttackSlider->setRange (0, 1, 0.0001);
    hiAttackSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    hiAttackSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    hiAttackSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    hiAttackSlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    hiAttackSlider->setColour (Slider::textBoxTextColourId, Colours::black);
    hiAttackSlider->addListener (this);

    addAndMakeVisible (hiReleaseSlider = new ParameterSlider (String::empty));
    hiReleaseSlider->setRange (0, 1, 0.0001);
    hiReleaseSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    hiReleaseSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    hiReleaseSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    hiReleaseSlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    hiReleaseSlider->setColour (Slider::textBoxTextColourId, Colours::black);
    hiReleaseSlider->addListener (this);

    addAndMakeVisible (bwSlider = new ParameterSlider (String::empty));
    bwSlider->setRange (0, 1, 0.0001);
    bwSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    bwSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    bwSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    bwSlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    bwSlider->setColour (Slider::textBoxTextColourId, Colours::black);
    bwSlider->addListener (this);

    addAndMakeVisible (gainSlider = new ParameterSlider (String::empty));
    gainSlider->setRange (0, 1, 0.0001);
    gainSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    gainSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    gainSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    gainSlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    gainSlider->setColour (Slider::textBoxTextColourId, Colours::black);
    gainSlider->addListener (this);

    addAndMakeVisible (drywetSlider = new ParameterSlider (String::empty));
    drywetSlider->setRange (0, 1, 0.0001);
    drywetSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    drywetSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    drywetSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    drywetSlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    drywetSlider->setColour (Slider::textBoxTextColourId, Colours::black);
    drywetSlider->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (400, 480);

    //[Constructor] You can add your own custom stuff here..

    loFreqSlider->setOrientation (ImageSlider::LinearHorizontal);
    hiFreqSlider->setOrientation (ImageSlider::LinearHorizontal);

    loGraph->setEffectManager (plugin->getEqualizer (0));
    midGraph->setEffectManager (plugin->getEqualizer (1));
    hiGraph->setEffectManager (plugin->getEqualizer (2));

    loGraph->setLineColour (Colours::red);
    midGraph->setLineColour (Colours::green);
    hiGraph->setLineColour (Colours::orange);

    plugin->getParameterLock().enter ();
        plugin->addListenerToParameter (PAR_GAIN, gainSlider);
        plugin->addListenerToParameter (PAR_DRYWET, drywetSlider);
        plugin->addListenerToParameter (PAR_BW, bwSlider);
        plugin->addListenerToParameter (PAR_BAND1GAIN, loGainSlider);
        plugin->addListenerToParameter (PAR_BAND1ATTACK, loAttackSlider);
        plugin->addListenerToParameter (PAR_BAND1RELEASE, loReleaseSlider);
        plugin->addListenerToParameter (PAR_BAND1THRESOLD, loThresoldSlider);
        plugin->addListenerToParameter (PAR_BAND1RATIO, loRatioSlider);
        // plugin->addListenerToParameter (PAR_BAND1KNEE, loKneeSlider);
        plugin->addListenerToParameter (PAR_BAND1MAKEUP, loMakeupSlider);
            plugin->addListenerToParameter (PAR_BAND12SPLIT, loFreqSlider);
        plugin->addListenerToParameter (PAR_BAND2GAIN, midGainSlider);
        plugin->addListenerToParameter (PAR_BAND2ATTACK, midAttackSlider);
        plugin->addListenerToParameter (PAR_BAND2RELEASE, midReleaseSlider);
        plugin->addListenerToParameter (PAR_BAND2THRESOLD, midThresoldSlider);
        plugin->addListenerToParameter (PAR_BAND2RATIO, midRatioSlider);
        // plugin->addListenerToParameter (PAR_BAND2KNEE, midKneeSlider);
        plugin->addListenerToParameter (PAR_BAND2MAKEUP, midMakeupSlider);
            plugin->addListenerToParameter (PAR_BAND23SPLIT, hiFreqSlider);
        plugin->addListenerToParameter (PAR_BAND3GAIN, hiGainSlider);
        plugin->addListenerToParameter (PAR_BAND3ATTACK, hiAttackSlider);
        plugin->addListenerToParameter (PAR_BAND3RELEASE, hiReleaseSlider);
        plugin->addListenerToParameter (PAR_BAND3THRESOLD, hiThresoldSlider);
        plugin->addListenerToParameter (PAR_BAND3RATIO, hiRatioSlider);
        // plugin->addListenerToParameter (PAR_BAND3KNEE, hiKneeSlider);
        plugin->addListenerToParameter (PAR_BAND3MAKEUP, hiMakeupSlider);
    plugin->getParameterLock().exit ();

    //[/Constructor]
}

XCompMain::~XCompMain()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    plugin->getParameterLock().enter ();
        plugin->removeListenerToParameter (PAR_GAIN, gainSlider);
        plugin->removeListenerToParameter (PAR_DRYWET, drywetSlider);
        plugin->removeListenerToParameter (PAR_BW, bwSlider);
        plugin->removeListenerToParameter (PAR_BAND1GAIN, loGainSlider);
        plugin->removeListenerToParameter (PAR_BAND1ATTACK, loAttackSlider);
        plugin->removeListenerToParameter (PAR_BAND1RELEASE, loReleaseSlider);
        plugin->removeListenerToParameter (PAR_BAND1THRESOLD, loThresoldSlider);
        plugin->removeListenerToParameter (PAR_BAND1RATIO, loRatioSlider);
        // plugin->removeListenerToParameter (PAR_BAND1KNEE, loKneeSlider);
        plugin->removeListenerToParameter (PAR_BAND1MAKEUP, loMakeupSlider);
            plugin->removeListenerToParameter (PAR_BAND12SPLIT, loFreqSlider);
        plugin->removeListenerToParameter (PAR_BAND2GAIN, midGainSlider);
        plugin->removeListenerToParameter (PAR_BAND2ATTACK, midAttackSlider);
        plugin->removeListenerToParameter (PAR_BAND2RELEASE, midReleaseSlider);
        plugin->removeListenerToParameter (PAR_BAND2THRESOLD, midThresoldSlider);
        plugin->removeListenerToParameter (PAR_BAND2RATIO, midRatioSlider);
        // plugin->removeListenerToParameter (PAR_BAND2KNEE, midKneeSlider);
        plugin->removeListenerToParameter (PAR_BAND2MAKEUP, midMakeupSlider);
            plugin->removeListenerToParameter (PAR_BAND23SPLIT, hiFreqSlider);
        plugin->removeListenerToParameter (PAR_BAND3GAIN, hiGainSlider);
        plugin->removeListenerToParameter (PAR_BAND3ATTACK, hiAttackSlider);
        plugin->removeListenerToParameter (PAR_BAND3RELEASE, hiReleaseSlider);
        plugin->removeListenerToParameter (PAR_BAND3THRESOLD, hiThresoldSlider);
        plugin->removeListenerToParameter (PAR_BAND3RATIO, hiRatioSlider);
        // plugin->removeListenerToParameter (PAR_BAND3KNEE, hiKneeSlider);
        plugin->removeListenerToParameter (PAR_BAND3MAKEUP, hiMakeupSlider);
    plugin->getParameterLock().exit ();
    //[/Destructor_pre]

    deleteAndZero (lowGroup);
    deleteAndZero (midGroup);
    deleteAndZero (hiGroup);
    deleteAndZero (loGraph);
    deleteAndZero (globalGroup);
    deleteAndZero (loGainSlider);
    deleteAndZero (loThresoldSlider);
    deleteAndZero (loRatioSlider);
    deleteAndZero (loMakeupSlider);
    deleteAndZero (loAttackSlider);
    deleteAndZero (loReleaseSlider);
    deleteAndZero (loFreqGroup);
    deleteAndZero (loFreqGroup2);
    deleteAndZero (loFreqSlider);
    deleteAndZero (hiFreqSlider);
    deleteAndZero (midGraph);
    deleteAndZero (hiGraph);
    deleteAndZero (midGainSlider);
    deleteAndZero (midThresoldSlider);
    deleteAndZero (midRatioSlider);
    deleteAndZero (midMakeupSlider);
    deleteAndZero (midAttackSlider);
    deleteAndZero (midReleaseSlider);
    deleteAndZero (hiGainSlider);
    deleteAndZero (hiThresoldSlider);
    deleteAndZero (hiRatioSlider);
    deleteAndZero (hiMakeupSlider);
    deleteAndZero (hiAttackSlider);
    deleteAndZero (hiReleaseSlider);
    deleteAndZero (bwSlider);
    deleteAndZero (gainSlider);
    deleteAndZero (drywetSlider);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void XCompMain::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff973e8b));

    g.setGradientFill (ColourGradient (Colour (0xff1fa388),
                                       209.0f, 14.0f,
                                       Colour (0x99000000),
                                       505.0f, 594.0f,
                                       true));
    g.fillRect (0, 0, 400, 480);

    g.setGradientFill (ColourGradient (Colour (0x1fa388),
                                       204.0f, 470.0f,
                                       Colours::black,
                                       204.0f, 484.0f,
                                       false));
    g.fillRect (0, 355, 400, 125);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void XCompMain::resized()
{
    lowGroup->setBounds (3, 262, 130, 212);
    midGroup->setBounds (135, 262, 130, 212);
    hiGroup->setBounds (266, 262, 130, 212);
    loGraph->setBounds (6, 8, 388, 110);
    globalGroup->setBounds (3, 120, 392, 105);
    loGainSlider->setBounds (15, 282, 10, 160);
    loThresoldSlider->setBounds (31, 282, 10, 160);
    loRatioSlider->setBounds (47, 282, 10, 160);
    loMakeupSlider->setBounds (63, 282, 10, 160);
    loAttackSlider->setBounds (84, 286, 33, 32);
    loReleaseSlider->setBounds (84, 322, 33, 32);
    loFreqGroup->setBounds (3, 219, 195, 44);
    loFreqGroup2->setBounds (199, 219, 196, 44);
    loFreqSlider->setBounds (15, 238, 173, 13);
    hiFreqSlider->setBounds (211, 238, 173, 13);
    midGraph->setBounds (6, 8, 388, 110);
    hiGraph->setBounds (6, 8, 388, 110);
    midGainSlider->setBounds (150, 282, 10, 160);
    midThresoldSlider->setBounds (166, 282, 10, 160);
    midRatioSlider->setBounds (182, 282, 10, 160);
    midMakeupSlider->setBounds (198, 282, 10, 160);
    midAttackSlider->setBounds (219, 286, 33, 32);
    midReleaseSlider->setBounds (219, 322, 33, 32);
    hiGainSlider->setBounds (279, 282, 10, 160);
    hiThresoldSlider->setBounds (295, 282, 10, 160);
    hiRatioSlider->setBounds (311, 282, 10, 160);
    hiMakeupSlider->setBounds (327, 282, 10, 160);
    hiAttackSlider->setBounds (348, 286, 33, 32);
    hiReleaseSlider->setBounds (348, 322, 33, 32);
    bwSlider->setBounds (20, 139, 33, 32);
    gainSlider->setBounds (343, 137, 33, 32);
    drywetSlider->setBounds (342, 175, 33, 32);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void XCompMain::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == loGainSlider)
    {
        //[UserSliderCode_loGainSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_BAND1GAIN, sliderThatWasMoved->getValue());

        loGraph->repaint ();
        midGraph->repaint ();
        hiGraph->repaint ();
        //[/UserSliderCode_loGainSlider]
    }
    else if (sliderThatWasMoved == loThresoldSlider)
    {
        //[UserSliderCode_loThresoldSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_BAND1THRESOLD, sliderThatWasMoved->getValue());
        //[/UserSliderCode_loThresoldSlider]
    }
    else if (sliderThatWasMoved == loRatioSlider)
    {
        //[UserSliderCode_loRatioSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_BAND1RATIO, sliderThatWasMoved->getValue());
        //[/UserSliderCode_loRatioSlider]
    }
    else if (sliderThatWasMoved == loMakeupSlider)
    {
        //[UserSliderCode_loMakeupSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_BAND1MAKEUP, sliderThatWasMoved->getValue());
        //[/UserSliderCode_loMakeupSlider]
    }
    else if (sliderThatWasMoved == loAttackSlider)
    {
        //[UserSliderCode_loAttackSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_BAND1ATTACK, sliderThatWasMoved->getValue());
        //[/UserSliderCode_loAttackSlider]
    }
    else if (sliderThatWasMoved == loReleaseSlider)
    {
        //[UserSliderCode_loReleaseSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_BAND1RELEASE, sliderThatWasMoved->getValue());
        //[/UserSliderCode_loReleaseSlider]
    }
    else if (sliderThatWasMoved == loFreqSlider)
    {
        //[UserSliderCode_loFreqSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_BAND12SPLIT, sliderThatWasMoved->getValue());

        if (plugin->getParameter (PAR_BAND12SPLIT) > plugin->getParameter (PAR_BAND23SPLIT))
            plugin->setParameterNotifyingHost (PAR_BAND23SPLIT, sliderThatWasMoved->getValue());

        loGraph->repaint ();
        midGraph->repaint ();
        hiGraph->repaint ();
        //[/UserSliderCode_loFreqSlider]
    }
    else if (sliderThatWasMoved == hiFreqSlider)
    {
        //[UserSliderCode_hiFreqSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_BAND23SPLIT, sliderThatWasMoved->getValue());

        if (plugin->getParameter (PAR_BAND12SPLIT) > plugin->getParameter (PAR_BAND23SPLIT))
            plugin->setParameterNotifyingHost (PAR_BAND12SPLIT, sliderThatWasMoved->getValue());

        loGraph->repaint ();
        midGraph->repaint ();
        hiGraph->repaint ();
        //[/UserSliderCode_hiFreqSlider]
    }
    else if (sliderThatWasMoved == midGainSlider)
    {
        //[UserSliderCode_midGainSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_BAND2GAIN, sliderThatWasMoved->getValue());

        loGraph->repaint ();
        midGraph->repaint ();
        hiGraph->repaint ();
        //[/UserSliderCode_midGainSlider]
    }
    else if (sliderThatWasMoved == midThresoldSlider)
    {
        //[UserSliderCode_midThresoldSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_BAND2THRESOLD, sliderThatWasMoved->getValue());
        //[/UserSliderCode_midThresoldSlider]
    }
    else if (sliderThatWasMoved == midRatioSlider)
    {
        //[UserSliderCode_midRatioSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_BAND2RATIO, sliderThatWasMoved->getValue());
        //[/UserSliderCode_midRatioSlider]
    }
    else if (sliderThatWasMoved == midMakeupSlider)
    {
        //[UserSliderCode_midMakeupSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_BAND2MAKEUP, sliderThatWasMoved->getValue());
        //[/UserSliderCode_midMakeupSlider]
    }
    else if (sliderThatWasMoved == midAttackSlider)
    {
        //[UserSliderCode_midAttackSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_BAND2ATTACK, sliderThatWasMoved->getValue());
        //[/UserSliderCode_midAttackSlider]
    }
    else if (sliderThatWasMoved == midReleaseSlider)
    {
        //[UserSliderCode_midReleaseSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_BAND2RELEASE, sliderThatWasMoved->getValue());
        //[/UserSliderCode_midReleaseSlider]
    }
    else if (sliderThatWasMoved == hiGainSlider)
    {
        //[UserSliderCode_hiGainSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_BAND3GAIN, sliderThatWasMoved->getValue());

        loGraph->repaint ();
        midGraph->repaint ();
        hiGraph->repaint ();
        //[/UserSliderCode_hiGainSlider]
    }
    else if (sliderThatWasMoved == hiThresoldSlider)
    {
        //[UserSliderCode_hiThresoldSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_BAND3THRESOLD, sliderThatWasMoved->getValue());
        //[/UserSliderCode_hiThresoldSlider]
    }
    else if (sliderThatWasMoved == hiRatioSlider)
    {
        //[UserSliderCode_hiRatioSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_BAND3RATIO, sliderThatWasMoved->getValue());
        //[/UserSliderCode_hiRatioSlider]
    }
    else if (sliderThatWasMoved == hiMakeupSlider)
    {
        //[UserSliderCode_hiMakeupSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_BAND3MAKEUP, sliderThatWasMoved->getValue());
        //[/UserSliderCode_hiMakeupSlider]
    }
    else if (sliderThatWasMoved == hiAttackSlider)
    {
        //[UserSliderCode_hiAttackSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_BAND3ATTACK, sliderThatWasMoved->getValue());
        //[/UserSliderCode_hiAttackSlider]
    }
    else if (sliderThatWasMoved == hiReleaseSlider)
    {
        //[UserSliderCode_hiReleaseSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_BAND3RELEASE, sliderThatWasMoved->getValue());
        //[/UserSliderCode_hiReleaseSlider]
    }
    else if (sliderThatWasMoved == bwSlider)
    {
        //[UserSliderCode_bwSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_BW, sliderThatWasMoved->getValue());

        loGraph->repaint ();
        midGraph->repaint ();
        hiGraph->repaint ();
        //[/UserSliderCode_bwSlider]
    }
    else if (sliderThatWasMoved == gainSlider)
    {
        //[UserSliderCode_gainSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_GAIN, sliderThatWasMoved->getValue());
        //[/UserSliderCode_gainSlider]
    }
    else if (sliderThatWasMoved == drywetSlider)
    {
        //[UserSliderCode_drywetSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_DRYWET, sliderThatWasMoved->getValue());
        //[/UserSliderCode_drywetSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="XCompMain" componentName=""
                 parentClasses="public Component" constructorParams="XCompPlugin* plugin_,XCompComponent* editor_"
                 variableInitialisers="plugin (plugin_)&#10;editor (editor_)" snapPixels="8"
                 snapActive="0" snapShown="0" overlayOpacity="0.330000013" fixedSize="1"
                 initialWidth="400" initialHeight="480">
  <BACKGROUND backgroundColour="ff973e8b">
    <RECT pos="0 0 400 480" fill=" radial: 209 14, 505 594, 0=ff1fa388, 1=99000000"
          hasStroke="0"/>
    <RECT pos="0 355 400 125" fill="linear: 204 470, 204 484, 0=1fa388, 1=ff000000"
          hasStroke="0"/>
  </BACKGROUND>
  <GROUPCOMPONENT name="" id="755b142c0e7297fd" memberName="lowGroup" virtualName=""
                  explicitFocusOrder="0" pos="3 262 130 212" outlinecol="66ffffff"
                  textcol="66ffffff" title="LOW"/>
  <GROUPCOMPONENT name="" id="1d1888866b2c0e65" memberName="midGroup" virtualName=""
                  explicitFocusOrder="0" pos="135 262 130 212" outlinecol="66ffffff"
                  textcol="66ffffff" title="MID" textpos="36"/>
  <GROUPCOMPONENT name="" id="9c48b7ce05fc5a44" memberName="hiGroup" virtualName=""
                  explicitFocusOrder="0" pos="266 262 130 212" outlinecol="66ffffff"
                  textcol="66ffffff" title="HI" textpos="34"/>
  <GENERICCOMPONENT name="" id="1b16858e745291c9" memberName="loGraph" virtualName=""
                    explicitFocusOrder="0" pos="6 8 388 110" class="EQGraph" params=""/>
  <GROUPCOMPONENT name="" id="7890eb9ef5b3f105" memberName="globalGroup" virtualName=""
                  explicitFocusOrder="0" pos="3 120 392 105" outlinecol="66ffffff"
                  textcol="66ffffff" title="GLOBALS" textpos="36"/>
  <SLIDER name="" id="6c8c25e677998e85" memberName="loGainSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="15 282 10 160" min="0" max="1" int="0.0001"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="1809bfa27c8cab36" memberName="loThresoldSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="31 282 10 160" min="0" max="1" int="0.0001"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="bbac7ad61a304d2e" memberName="loRatioSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="47 282 10 160" min="0" max="1" int="0.0001"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="5510349f59c0eabb" memberName="loMakeupSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="63 282 10 160" min="0" max="1" int="0.0001"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="b42ad42f51834220" memberName="loAttackSlider" virtualName="ParameterSlider"
          explicitFocusOrder="0" pos="84 286 33 32" rotarysliderfill="7fffffff"
          rotaryslideroutline="66ffffff" textboxtext="ff000000" min="0"
          max="1" int="0.0001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="f40c4270eba23cff" memberName="loReleaseSlider" virtualName="ParameterSlider"
          explicitFocusOrder="0" pos="84 322 33 32" rotarysliderfill="7fffffff"
          rotaryslideroutline="66ffffff" textboxtext="ff000000" min="0"
          max="1" int="0.0001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <GROUPCOMPONENT name="" id="fbb9445880f55e1e" memberName="loFreqGroup" virtualName=""
                  explicitFocusOrder="0" pos="3 219 195 44" outlinecol="66ffffff"
                  textcol="66ffffff" title="" textpos="36"/>
  <GROUPCOMPONENT name="" id="d6292681bc99c76d" memberName="loFreqGroup2" virtualName=""
                  explicitFocusOrder="0" pos="199 219 196 44" outlinecol="66ffffff"
                  textcol="66ffffff" title="" textpos="36"/>
  <SLIDER name="" id="f63a0df867071c47" memberName="loFreqSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="15 238 173 13" min="0" max="1" int="0.0001"
          style="LinearHorizontal" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="d45902542219c3f8" memberName="hiFreqSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="211 238 173 13" min="0" max="1" int="0.0001"
          style="LinearHorizontal" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <GENERICCOMPONENT name="" id="1f59a2da57f74a0b" memberName="midGraph" virtualName=""
                    explicitFocusOrder="0" pos="6 8 388 110" class="EQGraph" params=""/>
  <GENERICCOMPONENT name="" id="aeaa736dfd855be1" memberName="hiGraph" virtualName=""
                    explicitFocusOrder="0" pos="6 8 388 110" class="EQGraph" params=""/>
  <SLIDER name="" id="bc39627c0efe5d92" memberName="midGainSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="150 282 10 160" min="0" max="1" int="0.0001"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="20f45872ba918c23" memberName="midThresoldSlider"
          virtualName="ImageSlider" explicitFocusOrder="0" pos="166 282 10 160"
          min="0" max="1" int="0.0001" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="cc0ec12c3d7d7bd9" memberName="midRatioSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="182 282 10 160" min="0" max="1" int="0.0001"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="4a4e83d3318dc0a2" memberName="midMakeupSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="198 282 10 160" min="0" max="1" int="0.0001"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="a5de853954040f56" memberName="midAttackSlider" virtualName="ParameterSlider"
          explicitFocusOrder="0" pos="219 286 33 32" rotarysliderfill="7fffffff"
          rotaryslideroutline="66ffffff" textboxtext="ff000000" min="0"
          max="1" int="0.0001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="4023b889db962259" memberName="midReleaseSlider" virtualName="ParameterSlider"
          explicitFocusOrder="0" pos="219 322 33 32" rotarysliderfill="7fffffff"
          rotaryslideroutline="66ffffff" textboxtext="ff000000" min="0"
          max="1" int="0.0001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="54aaf670d1b770c4" memberName="hiGainSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="279 282 10 160" min="0" max="1" int="0.0001"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="7b8e5702846b6d52" memberName="hiThresoldSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="295 282 10 160" min="0" max="1" int="0.0001"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="dc0c02ada5e6a6e" memberName="hiRatioSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="311 282 10 160" min="0" max="1" int="0.0001"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="e022cef1ab0c3584" memberName="hiMakeupSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="327 282 10 160" min="0" max="1" int="0.0001"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="3e411b1f8c5d66a7" memberName="hiAttackSlider" virtualName="ParameterSlider"
          explicitFocusOrder="0" pos="348 286 33 32" rotarysliderfill="7fffffff"
          rotaryslideroutline="66ffffff" textboxtext="ff000000" min="0"
          max="1" int="0.0001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="616741a9b9afcebd" memberName="hiReleaseSlider" virtualName="ParameterSlider"
          explicitFocusOrder="0" pos="348 322 33 32" rotarysliderfill="7fffffff"
          rotaryslideroutline="66ffffff" textboxtext="ff000000" min="0"
          max="1" int="0.0001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="b04d0b25ff4d1e23" memberName="bwSlider" virtualName="ParameterSlider"
          explicitFocusOrder="0" pos="20 139 33 32" rotarysliderfill="7fffffff"
          rotaryslideroutline="66ffffff" textboxtext="ff000000" min="0"
          max="1" int="0.0001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="822441c734f6d4bb" memberName="gainSlider" virtualName="ParameterSlider"
          explicitFocusOrder="0" pos="343 137 33 32" rotarysliderfill="7fffffff"
          rotaryslideroutline="66ffffff" textboxtext="ff000000" min="0"
          max="1" int="0.0001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="d8bc3aaf25d28e73" memberName="drywetSlider" virtualName="ParameterSlider"
          explicitFocusOrder="0" pos="342 175 33 32" rotarysliderfill="7fffffff"
          rotaryslideroutline="66ffffff" textboxtext="ff000000" min="0"
          max="1" int="0.0001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
