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

//[Headers] You can add your own extra header files here...
#include "../XDubDelayComponent.h"
//[/Headers]

#include "XDubDelayMainComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
XDubDelayMainComponent::XDubDelayMainComponent (XDubDelayComponent* const editor_, XDubDelayPlugin* const plugin_)
    : editor (editor_),
      plugin (plugin_),
      label (0),
      delaySlider (0),
      feedbackSlider (0),
      toneSlider (0),
      lfoDepthSlider (0),
      lfoSpeedSlider (0),
      dryWetSlider (0),
      outputSlider (0)
{
    addAndMakeVisible (label = new Label (T("new label"),
                                          T("v0.1.1")));
    label->setFont (Font (Font::getDefaultMonospacedFontName(), 15.7000f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (delaySlider = new ImageSlider (String::empty));
    delaySlider->setRange (0, 1, 0.0001);
    delaySlider->setSliderStyle (Slider::LinearVertical);
    delaySlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    delaySlider->addListener (this);

    addAndMakeVisible (feedbackSlider = new ImageSlider (String::empty));
    feedbackSlider->setRange (0, 1, 0.0001);
    feedbackSlider->setSliderStyle (Slider::LinearVertical);
    feedbackSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    feedbackSlider->addListener (this);

    addAndMakeVisible (toneSlider = new ImageSlider (String::empty));
    toneSlider->setRange (0, 1, 0.0001);
    toneSlider->setSliderStyle (Slider::LinearVertical);
    toneSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    toneSlider->addListener (this);

    addAndMakeVisible (lfoDepthSlider = new ImageSlider (String::empty));
    lfoDepthSlider->setRange (0, 1, 0.0001);
    lfoDepthSlider->setSliderStyle (Slider::LinearVertical);
    lfoDepthSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    lfoDepthSlider->addListener (this);

    addAndMakeVisible (lfoSpeedSlider = new ImageSlider (String::empty));
    lfoSpeedSlider->setRange (0, 1, 0.0001);
    lfoSpeedSlider->setSliderStyle (Slider::LinearVertical);
    lfoSpeedSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    lfoSpeedSlider->addListener (this);

    addAndMakeVisible (dryWetSlider = new ImageSlider (String::empty));
    dryWetSlider->setRange (0, 1, 0.0001);
    dryWetSlider->setSliderStyle (Slider::LinearVertical);
    dryWetSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    dryWetSlider->addListener (this);

    addAndMakeVisible (outputSlider = new ImageSlider (String::empty));
    outputSlider->setRange (0, 1, 0.0001);
    outputSlider->setSliderStyle (Slider::LinearVertical);
    outputSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    outputSlider->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (480, 280);

    //[Constructor] You can add your own custom stuff here..
    String pluginVersion;
    pluginVersion << T("v") << T(JucePlugin_VersionString);
    label->setText (pluginVersion, false);

    plugin->getParameterLock().enter ();
        plugin->addListenerToParameter (PAR_DELAY,    delaySlider);
        plugin->addListenerToParameter (PAR_FEEDBACK, feedbackSlider);
        plugin->addListenerToParameter (PAR_TONE,     toneSlider);
        plugin->addListenerToParameter (PAR_LFODEPTH, lfoDepthSlider);
        plugin->addListenerToParameter (PAR_LFOSPEED, lfoSpeedSlider);
        plugin->addListenerToParameter (PAR_DRYWET,   dryWetSlider);
        plugin->addListenerToParameter (PAR_OUTPUT,   outputSlider);
    plugin->getParameterLock().exit ();

    updateControls ();
    //[/Constructor]
}

XDubDelayMainComponent::~XDubDelayMainComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    plugin->getParameterLock().enter ();
        plugin->removeListenerToParameter (PAR_DELAY,    delaySlider);
        plugin->removeListenerToParameter (PAR_FEEDBACK, feedbackSlider);
        plugin->removeListenerToParameter (PAR_TONE,     toneSlider);
        plugin->removeListenerToParameter (PAR_LFODEPTH, lfoDepthSlider);
        plugin->removeListenerToParameter (PAR_LFOSPEED, lfoSpeedSlider);
        plugin->removeListenerToParameter (PAR_DRYWET,   dryWetSlider);
        plugin->removeListenerToParameter (PAR_OUTPUT,   outputSlider);
    plugin->getParameterLock().exit ();
    //[/Destructor_pre]

    deleteAndZero (label);
    deleteAndZero (delaySlider);
    deleteAndZero (feedbackSlider);
    deleteAndZero (toneSlider);
    deleteAndZero (lfoDepthSlider);
    deleteAndZero (lfoSpeedSlider);
    deleteAndZero (dryWetSlider);
    deleteAndZero (outputSlider);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void XDubDelayMainComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.setGradientFill (ColourGradient (Colour (0xff598872),
                                       222.0f, 236.0f,
                                       Colour (0xff749a88),
                                       221.0f, 12.0f,
                                       false));
    g.fillRect (0, 0, 480, 267);

    g.setGradientFill (ColourGradient (Colour (0xff598872),
                                       231.0f, 270.0f,
                                       Colours::black,
                                       231.0f, 280.0f,
                                       false));
    g.fillRect (0, 267, 480, 13);

    g.setColour (Colour (0xff2e3538));
    g.setFont (Font (Font::getDefaultMonospacedFontName(), 37.0000f, Font::bold | Font::italic));
    g.drawText (T("DUB DELAY"),
                3, 3, 474, 27,
                Justification::centred, true);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void XDubDelayMainComponent::resized()
{
    label->setBounds (329, 16, 52, 16);
    delaySlider->setBounds (30, 57, 33, 180);
    feedbackSlider->setBounds (64, 57, 33, 180);
    toneSlider->setBounds (98, 58, 33, 180);
    lfoDepthSlider->setBounds (134, 59, 33, 180);
    lfoSpeedSlider->setBounds (170, 59, 33, 180);
    dryWetSlider->setBounds (205, 58, 33, 180);
    outputSlider->setBounds (240, 58, 33, 180);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void XDubDelayMainComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == delaySlider)
    {
        //[UserSliderCode_delaySlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_DELAY, sliderThatWasMoved->getValue());
        //[/UserSliderCode_delaySlider]
    }
    else if (sliderThatWasMoved == feedbackSlider)
    {
        //[UserSliderCode_feedbackSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_FEEDBACK, sliderThatWasMoved->getValue());
        //[/UserSliderCode_feedbackSlider]
    }
    else if (sliderThatWasMoved == toneSlider)
    {
        //[UserSliderCode_toneSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_TONE, sliderThatWasMoved->getValue());
        //[/UserSliderCode_toneSlider]
    }
    else if (sliderThatWasMoved == lfoDepthSlider)
    {
        //[UserSliderCode_lfoDepthSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_LFODEPTH, sliderThatWasMoved->getValue());
        //[/UserSliderCode_lfoDepthSlider]
    }
    else if (sliderThatWasMoved == lfoSpeedSlider)
    {
        //[UserSliderCode_lfoSpeedSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_LFOSPEED, sliderThatWasMoved->getValue());
        //[/UserSliderCode_lfoSpeedSlider]
    }
    else if (sliderThatWasMoved == dryWetSlider)
    {
        //[UserSliderCode_dryWetSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_DRYWET, sliderThatWasMoved->getValue());
        //[/UserSliderCode_dryWetSlider]
    }
    else if (sliderThatWasMoved == outputSlider)
    {
        //[UserSliderCode_outputSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_OUTPUT, sliderThatWasMoved->getValue());
        //[/UserSliderCode_outputSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//==============================================================================
void XDubDelayMainComponent::updateControls ()
{
    // update sliders
    delaySlider->setValue (plugin->getParameter (PAR_DELAY), false);
    feedbackSlider->setValue (plugin->getParameter (PAR_FEEDBACK), false);
    toneSlider->setValue (plugin->getParameter (PAR_TONE), false);
    lfoDepthSlider->setValue (plugin->getParameter (PAR_LFODEPTH), false);
    lfoSpeedSlider->setValue (plugin->getParameter (PAR_LFOSPEED), false);
    dryWetSlider->setValue (plugin->getParameter (PAR_DRYWET), false);
    outputSlider->setValue (plugin->getParameter (PAR_OUTPUT), false);
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="XDubDelayMainComponent" componentName=""
                 parentClasses="public Component" constructorParams="XDubDelayComponent* const editor_, XDubDelayPlugin* const plugin_"
                 variableInitialisers="editor (editor_),&#10;plugin (plugin_)" snapPixels="8"
                 snapActive="0" snapShown="1" overlayOpacity="0.330000013" fixedSize="1"
                 initialWidth="480" initialHeight="280">
  <BACKGROUND backgroundColour="ffffff">
    <RECT pos="0 0 480 267" fill="linear: 222 236, 221 12, 0=ff598872, 1=ff749a88"
          hasStroke="0"/>
    <RECT pos="0 267 480 13" fill="linear: 231 270, 231 280, 0=ff598872, 1=ff000000"
          hasStroke="0"/>
    <TEXT pos="3 3 474 27" fill="solid: ff2e3538" hasStroke="0" text="DUB DELAY"
          fontname="Default monospaced font" fontsize="37" bold="1" italic="1"
          justification="36"/>
  </BACKGROUND>
  <LABEL name="new label" id="2dc5acc563ebd2bc" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="329 16 52 16" edTextCol="ff000000"
         edBkgCol="0" labelText="v0.1.1" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="15.7"
         bold="0" italic="0" justification="33"/>
  <SLIDER name="" id="473e01880cd16bdb" memberName="delaySlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="30 57 33 180" min="0" max="1" int="0.0001"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="13db7fbe3b6324a5" memberName="feedbackSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="64 57 33 180" min="0" max="1" int="0.0001"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="39b153ea56775141" memberName="toneSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="98 58 33 180" min="0" max="1" int="0.0001"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="97cbdaaaa60a6fb6" memberName="lfoDepthSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="134 59 33 180" min="0" max="1" int="0.0001"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="7c351d40ddd5c3e4" memberName="lfoSpeedSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="170 59 33 180" min="0" max="1" int="0.0001"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="28daa13c5c999959" memberName="dryWetSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="205 58 33 180" min="0" max="1" int="0.0001"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="e871f54524954ac2" memberName="outputSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="240 58 33 180" min="0" max="1" int="0.0001"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
