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

//[Headers] You can add your own extra header files here...
#include "XSynthTabPanel.h"
//[/Headers]

#include "XSynthMixerStrip.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
XSynthMixerStrip::XSynthMixerStrip (XSynthPlugin* plugin_, Master* master_, const int partNumber_)
    : plugin (plugin_),
      master (master_),
      partNumber (partNumber_),
      groupComponent (0),
      volumeSlider (0),
      panSlider (0),
      panLabel (0),
      editButton (0),
      volumeLabel (0),
      meter (0),
      muteButton (0),
      soloButton (0),
      ctrl1Slider (0),
      ctrl1Label (0),
      ctrl2Slider (0),
      ctrl2Label (0),
      ctrl3Slider (0),
      ctrl3Label (0),
      ctrl4Slider (0),
      ctrl4Label (0)
{
    addAndMakeVisible (groupComponent = new GroupComponent (String::empty,
                                                            T("xx")));
    groupComponent->setTextLabelPosition (Justification::centredRight);
    groupComponent->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    groupComponent->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (volumeSlider = new ImageSlider (String::empty));
    volumeSlider->setRange (0, 1, 0.0001);
    volumeSlider->setSliderStyle (Slider::LinearVertical);
    volumeSlider->setTextBoxStyle (Slider::NoTextBox, true, 30, 18);
    volumeSlider->setColour (Slider::trackColourId, Colour (0x70ffffff));
    volumeSlider->addListener (this);

    addAndMakeVisible (panSlider = new ParameterSlider (String::empty));
    panSlider->setRange (0, 1, 0.0001);
    panSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    panSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    panSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fcbcbcb));
    panSlider->addListener (this);

    addAndMakeVisible (panLabel = new Label (String::empty,
                                             T("PAN")));
    panLabel->setFont (Font (15.0000f, Font::plain));
    panLabel->setJustificationType (Justification::centred);
    panLabel->setEditable (false, false, false);
    panLabel->setColour (Label::backgroundColourId, Colour (0x0));
    panLabel->setColour (Label::textColourId, Colours::white);
    panLabel->setColour (Label::outlineColourId, Colour (0x0));
    panLabel->setColour (TextEditor::textColourId, Colours::black);
    panLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (editButton = new TextButton (String::empty));
    editButton->setButtonText (T("EDIT"));
    editButton->setConnectedEdges (Button::ConnectedOnBottom);
    editButton->addButtonListener (this);

    addAndMakeVisible (volumeLabel = new Label (T("new label"),
                                                T("GAIN")));
    volumeLabel->setFont (Font (15.0000f, Font::plain));
    volumeLabel->setJustificationType (Justification::centred);
    volumeLabel->setEditable (false, false, false);
    volumeLabel->setColour (Label::backgroundColourId, Colour (0x0));
    volumeLabel->setColour (Label::textColourId, Colours::white);
    volumeLabel->setColour (Label::outlineColourId, Colour (0x0));
    volumeLabel->setColour (TextEditor::textColourId, Colours::black);
    volumeLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (meter = new MeterComponent (MeterComponent::MeterVertical,
                                                   0,
                                                   2,
                                                   Colours::blue,
                                                   Colours::lightblue,
                                                   Colours::white,
                                                   Colours::black,
                                                   0.6));

    addAndMakeVisible (muteButton = new TextButton (String::empty));
    muteButton->setButtonText (T("MUTE"));
    muteButton->setConnectedEdges (Button::ConnectedOnTop | Button::ConnectedOnBottom);
    muteButton->addButtonListener (this);
    muteButton->setColour (TextButton::buttonColourId, Colours::grey);
    muteButton->setColour (TextButton::buttonOnColourId, Colour (0xff970600));
    muteButton->setColour (TextButton::textColourOnId, Colours::black);

    addAndMakeVisible (soloButton = new TextButton (String::empty));
    soloButton->setButtonText (T("SOLO"));
    soloButton->setConnectedEdges (Button::ConnectedOnTop);
    soloButton->addButtonListener (this);
    soloButton->setColour (TextButton::buttonColourId, Colours::grey);
    soloButton->setColour (TextButton::buttonOnColourId, Colour (0xff055c0d));
    soloButton->setColour (TextButton::textColourOnId, Colours::black);

    addAndMakeVisible (ctrl1Slider = new DynamicParameterSlider (String::empty));
    ctrl1Slider->setRange (0, 1, 0.0001);
    ctrl1Slider->setSliderStyle (Slider::RotaryVerticalDrag);
    ctrl1Slider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    ctrl1Slider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fcbcbcb));
    ctrl1Slider->addListener (this);

    addAndMakeVisible (ctrl1Label = new Label (String::empty,
                                               T("C1")));
    ctrl1Label->setFont (Font (15.0000f, Font::plain));
    ctrl1Label->setJustificationType (Justification::centred);
    ctrl1Label->setEditable (false, false, false);
    ctrl1Label->setColour (Label::backgroundColourId, Colour (0x0));
    ctrl1Label->setColour (Label::textColourId, Colours::white);
    ctrl1Label->setColour (Label::outlineColourId, Colour (0x0));
    ctrl1Label->setColour (TextEditor::textColourId, Colours::black);
    ctrl1Label->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (ctrl2Slider = new DynamicParameterSlider (String::empty));
    ctrl2Slider->setRange (0, 1, 0.0001);
    ctrl2Slider->setSliderStyle (Slider::RotaryVerticalDrag);
    ctrl2Slider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    ctrl2Slider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fcbcbcb));
    ctrl2Slider->addListener (this);

    addAndMakeVisible (ctrl2Label = new Label (String::empty,
                                               T("C2")));
    ctrl2Label->setFont (Font (15.0000f, Font::plain));
    ctrl2Label->setJustificationType (Justification::centred);
    ctrl2Label->setEditable (false, false, false);
    ctrl2Label->setColour (Label::backgroundColourId, Colour (0x0));
    ctrl2Label->setColour (Label::textColourId, Colours::white);
    ctrl2Label->setColour (Label::outlineColourId, Colour (0x0));
    ctrl2Label->setColour (TextEditor::textColourId, Colours::black);
    ctrl2Label->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (ctrl3Slider = new DynamicParameterSlider (String::empty));
    ctrl3Slider->setRange (0, 1, 0.0001);
    ctrl3Slider->setSliderStyle (Slider::RotaryVerticalDrag);
    ctrl3Slider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    ctrl3Slider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fcbcbcb));
    ctrl3Slider->addListener (this);

    addAndMakeVisible (ctrl3Label = new Label (String::empty,
                                               T("C3")));
    ctrl3Label->setFont (Font (15.0000f, Font::plain));
    ctrl3Label->setJustificationType (Justification::centred);
    ctrl3Label->setEditable (false, false, false);
    ctrl3Label->setColour (Label::backgroundColourId, Colour (0x0));
    ctrl3Label->setColour (Label::textColourId, Colours::white);
    ctrl3Label->setColour (Label::outlineColourId, Colour (0x0));
    ctrl3Label->setColour (TextEditor::textColourId, Colours::black);
    ctrl3Label->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (ctrl4Slider = new DynamicParameterSlider (String::empty));
    ctrl4Slider->setRange (0, 1, 0.0001);
    ctrl4Slider->setSliderStyle (Slider::RotaryVerticalDrag);
    ctrl4Slider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    ctrl4Slider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fcbcbcb));
    ctrl4Slider->addListener (this);

    addAndMakeVisible (ctrl4Label = new Label (String::empty,
                                               T("C4")));
    ctrl4Label->setFont (Font (15.0000f, Font::plain));
    ctrl4Label->setJustificationType (Justification::centred);
    ctrl4Label->setEditable (false, false, false);
    ctrl4Label->setColour (Label::backgroundColourId, Colour (0x0));
    ctrl4Label->setColour (Label::textColourId, Colours::white);
    ctrl4Label->setColour (Label::outlineColourId, Colour (0x0));
    ctrl4Label->setColour (TextEditor::textColourId, Colours::black);
    ctrl4Label->setColour (TextEditor::backgroundColourId, Colour (0x0));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (36, 380);

    //[Constructor] You can add your own custom stuff here..
    int partNumberCorrect = partNumber + 1;
    String partString = String (partNumberCorrect);
    partString = (partNumberCorrect >= 10) ? (partString) : (T("0") + partString);
    groupComponent->setText (partString);

    meter->setFrame (1);

    ctrl1Slider->setOwner (plugin, partNumber, 0);
    ctrl2Slider->setOwner (plugin, partNumber, 1);
    ctrl3Slider->setOwner (plugin, partNumber, 2);
    ctrl4Slider->setOwner (plugin, partNumber, 3);

    plugin->getParameterLock().enter ();
        plugin->addListenerToParameter (PPAR(partNumber,PP_GAIN), volumeSlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_PAN), panSlider);

        ctrl1Slider->setDynamicParameter (master->part [partNumber]->Pctrl [0]);
        ctrl2Slider->setDynamicParameter (master->part [partNumber]->Pctrl [1]);
        ctrl3Slider->setDynamicParameter (master->part [partNumber]->Pctrl [2]);
        ctrl4Slider->setDynamicParameter (master->part [partNumber]->Pctrl [3]);
    plugin->getParameterLock().exit ();

    //[/Constructor]
}

XSynthMixerStrip::~XSynthMixerStrip()
{
    //[Destructor_pre]. You can add your own custom destruction code here..

    plugin->getParameterLock().enter ();
        plugin->removeListenerToParameter (PPAR(partNumber,PP_GAIN), volumeSlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_PAN), panSlider);

        ctrl1Slider->resetOwner ();
        ctrl2Slider->resetOwner ();
        ctrl3Slider->resetOwner ();
        ctrl4Slider->resetOwner ();
    plugin->getParameterLock().exit ();

    //[/Destructor_pre]

    deleteAndZero (groupComponent);
    deleteAndZero (volumeSlider);
    deleteAndZero (panSlider);
    deleteAndZero (panLabel);
    deleteAndZero (editButton);
    deleteAndZero (volumeLabel);
    deleteAndZero (meter);
    deleteAndZero (muteButton);
    deleteAndZero (soloButton);
    deleteAndZero (ctrl1Slider);
    deleteAndZero (ctrl1Label);
    deleteAndZero (ctrl2Slider);
    deleteAndZero (ctrl2Label);
    deleteAndZero (ctrl3Slider);
    deleteAndZero (ctrl3Label);
    deleteAndZero (ctrl4Slider);
    deleteAndZero (ctrl4Label);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void XSynthMixerStrip::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void XSynthMixerStrip::resized()
{
    groupComponent->setBounds (-2, 0, 40, 380);
    volumeSlider->setBounds (6, 272, 10, 100);
    panSlider->setBounds (5, 237, 25, 23);
    panLabel->setBounds (5, 227, 26, 12);
    editButton->setBounds (5, 18, 26, 13);
    volumeLabel->setBounds (3, 264, 30, 12);
    meter->setBounds (22, 277, 6, 92);
    muteButton->setBounds (5, 30, 26, 13);
    soloButton->setBounds (5, 42, 26, 13);
    ctrl1Slider->setBounds (5, 72, 25, 23);
    ctrl1Label->setBounds (5, 62, 26, 12);
    ctrl2Slider->setBounds (5, 112, 25, 23);
    ctrl2Label->setBounds (5, 102, 26, 12);
    ctrl3Slider->setBounds (5, 152, 25, 23);
    ctrl3Label->setBounds (5, 142, 26, 12);
    ctrl4Slider->setBounds (5, 192, 25, 23);
    ctrl4Label->setBounds (5, 182, 26, 12);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void XSynthMixerStrip::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == volumeSlider)
    {
        //[UserSliderCode_volumeSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_GAIN), sliderThatWasMoved->getValue());
        //[/UserSliderCode_volumeSlider]
    }
    else if (sliderThatWasMoved == panSlider)
    {
        //[UserSliderCode_panSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_PAN), sliderThatWasMoved->getValue());
        //[/UserSliderCode_panSlider]
    }
    else if (sliderThatWasMoved == ctrl1Slider)
    {
        //[UserSliderCode_ctrl1Slider] -- add your slider handling code here..
        int parameterNumber = ctrl1Slider->getCurrentParameter();
        if (parameterNumber >= 0)
            plugin->setParameterNotifyingHost (parameterNumber, sliderThatWasMoved->getValue());
        //[/UserSliderCode_ctrl1Slider]
    }
    else if (sliderThatWasMoved == ctrl2Slider)
    {
        //[UserSliderCode_ctrl2Slider] -- add your slider handling code here..
        int parameterNumber = ctrl2Slider->getCurrentParameter();
        if (parameterNumber >= 0)
            plugin->setParameterNotifyingHost (parameterNumber, sliderThatWasMoved->getValue());
        //[/UserSliderCode_ctrl2Slider]
    }
    else if (sliderThatWasMoved == ctrl3Slider)
    {
        //[UserSliderCode_ctrl3Slider] -- add your slider handling code here..
        int parameterNumber = ctrl3Slider->getCurrentParameter();
        if (parameterNumber >= 0)
            plugin->setParameterNotifyingHost (parameterNumber, sliderThatWasMoved->getValue());
        //[/UserSliderCode_ctrl3Slider]
    }
    else if (sliderThatWasMoved == ctrl4Slider)
    {
        //[UserSliderCode_ctrl4Slider] -- add your slider handling code here..
        int parameterNumber = ctrl4Slider->getCurrentParameter();
        if (parameterNumber >= 0)
            plugin->setParameterNotifyingHost (parameterNumber, sliderThatWasMoved->getValue());
        //[/UserSliderCode_ctrl4Slider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void XSynthMixerStrip::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == editButton)
    {
        //[UserButtonCode_editButton] -- add your button handler code here..
        XSynthTabPanel* parent = findParentComponentOfClass <XSynthTabPanel> ();
        if (parent != 0)
            parent->openPartEditor (partNumber);
        //[/UserButtonCode_editButton]
    }
    else if (buttonThatWasClicked == muteButton)
    {
        //[UserButtonCode_muteButton] -- add your button handler code here..
        bool enabled = master->part[partNumber]->Penabled == 1;

        master->partonoff (partNumber, ! enabled);
        muteButton->setColour (TextButton::buttonColourId,
                               (enabled) ? Colour (0xff808080) : Colour (0xffdf2e2e));

        volumeSlider->setEnabled (enabled);
        panSlider->setEnabled (enabled);
        ctrl1Slider->setEnabled (enabled);
        ctrl2Slider->setEnabled (enabled);
        ctrl3Slider->setEnabled (enabled);
        ctrl4Slider->setEnabled (enabled);

        //[/UserButtonCode_muteButton]
    }
    else if (buttonThatWasClicked == soloButton)
    {
        //[UserButtonCode_soloButton] -- add your button handler code here..

        XSynthMixer* parent = findParentComponentOfClass <XSynthMixer> ();
        if (parent != 0)
        {
            int thisPart = partNumber + 1;

            if (master->Psolopart == thisPart)
                parent->setSoloChannel (0);
            else
                parent->setSoloChannel (thisPart);
        }

        //[/UserButtonCode_soloButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void XSynthMixerStrip::updateControls ()
{
    bool enabled = master->part[partNumber]->Penabled == 1;

    volumeSlider->setValue (plugin->getParameter (PPAR(partNumber,PP_GAIN)), false);
    panSlider->setValue (plugin->getParameter (PPAR(partNumber,PP_PAN)), false);

    muteButton->setColour (TextButton::buttonColourId,
                           (enabled) ? Colours::grey : Colour (0xffdf2e2e));

    volumeSlider->setEnabled (enabled);
    panSlider->setEnabled (enabled);
    ctrl1Slider->setEnabled (enabled);
    ctrl2Slider->setEnabled (enabled);
    ctrl3Slider->setEnabled (enabled);
    ctrl4Slider->setEnabled (enabled);

    // update dynamic slider
    plugin->getParameterLock().enter ();
        ctrl1Slider->setDynamicParameter (master->part [partNumber]->Pctrl [0]);
        ctrl2Slider->setDynamicParameter (master->part [partNumber]->Pctrl [1]);
        ctrl3Slider->setDynamicParameter (master->part [partNumber]->Pctrl [2]);
        ctrl4Slider->setDynamicParameter (master->part [partNumber]->Pctrl [3]);
    plugin->getParameterLock().exit ();

    // now set the current slider values to their parameter ones
    int parameterNumber;
    parameterNumber = ctrl1Slider->getCurrentParameter();
    if (parameterNumber >= 0)
        ctrl1Slider->setValue (plugin->getParameter (parameterNumber), false);

    parameterNumber = ctrl2Slider->getCurrentParameter();
    if (parameterNumber >= 0)
        ctrl2Slider->setValue (plugin->getParameter (parameterNumber), false);

    parameterNumber = ctrl3Slider->getCurrentParameter();
    if (parameterNumber >= 0)
        ctrl3Slider->setValue (plugin->getParameter (parameterNumber), false);

    parameterNumber = ctrl4Slider->getCurrentParameter();
    if (parameterNumber >= 0)
        ctrl4Slider->setValue (plugin->getParameter (parameterNumber), false);
}

void XSynthMixerStrip::setMeterValue (const float newValue)
{
    meter->setValue (newValue);
}

void XSynthMixerStrip::enableSolo (const bool enable)
{
    Colour buttonColour (0xff808080);
    if (enable)
        buttonColour = Colour (0xff26a800);

    soloButton->setColour (TextButton::buttonColourId, buttonColour);
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="XSynthMixerStrip" componentName=""
                 parentClasses="public Component" constructorParams="XSynthPlugin* plugin_, Master* master_, const int partNumber_"
                 variableInitialisers="plugin (plugin_)&#10;master (master_)&#10;partNumber (partNumber_)"
                 snapPixels="8" snapActive="0" snapShown="0" overlayOpacity="0.330000013"
                 fixedSize="1" initialWidth="36" initialHeight="380">
  <BACKGROUND backgroundColour="ffffff"/>
  <GROUPCOMPONENT name="" id="e6a4306055cdbdec" memberName="groupComponent" virtualName=""
                  explicitFocusOrder="0" pos="-2 0 40 380" outlinecol="66ffffff"
                  textcol="ffffffff" title="xx" textpos="34"/>
  <SLIDER name="" id="a31d7d8c3f158e3c" memberName="volumeSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="6 272 10 100" trackcol="70ffffff"
          min="0" max="1" int="0.0001" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="30" textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="1d42331dc76f21dd" memberName="panSlider" virtualName="ParameterSlider"
          explicitFocusOrder="0" pos="5 237 25 23" rotarysliderfill="7fcbcbcb"
          min="0" max="1" int="0.0001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="" id="9efc231682d3a556" memberName="panLabel" virtualName=""
         explicitFocusOrder="0" pos="5 227 26 12" bkgCol="0" textCol="ffffffff"
         outlineCol="0" edTextCol="ff000000" edBkgCol="0" labelText="PAN"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="" id="33dbe62a9f31003" memberName="editButton" virtualName=""
              explicitFocusOrder="0" pos="5 18 26 13" buttonText="EDIT" connectedEdges="8"
              needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="8f03476d68885b79" memberName="volumeLabel"
         virtualName="" explicitFocusOrder="0" pos="3 264 30 12" bkgCol="0"
         textCol="ffffffff" outlineCol="0" edTextCol="ff000000" edBkgCol="0"
         labelText="GAIN" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <GENERICCOMPONENT name="" id="68764fb5ce4a2a0c" memberName="meter" virtualName=""
                    explicitFocusOrder="0" pos="22 277 6 92" class="MeterComponent"
                    params="MeterComponent::MeterVertical,&#10;0, &#10;2,&#10;Colours::blue,&#10;Colours::lightblue,&#10;Colours::white,&#10;Colours::black,&#10;0.6"/>
  <TEXTBUTTON name="" id="e6f02c756ebc4bdf" memberName="muteButton" virtualName=""
              explicitFocusOrder="0" pos="5 30 26 13" bgColOff="ff808080" bgColOn="ff970600"
              textCol="ff000000" buttonText="MUTE" connectedEdges="12" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="" id="54f641994b4de421" memberName="soloButton" virtualName=""
              explicitFocusOrder="0" pos="5 42 26 13" bgColOff="ff808080" bgColOn="ff055c0d"
              textCol="ff000000" buttonText="SOLO" connectedEdges="4" needsCallback="1"
              radioGroupId="0"/>
  <SLIDER name="" id="a94570f7bc65574b" memberName="ctrl1Slider" virtualName="DynamicParameterSlider"
          explicitFocusOrder="0" pos="5 72 25 23" rotarysliderfill="7fcbcbcb"
          min="0" max="1" int="0.0001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="" id="3846d407a060d152" memberName="ctrl1Label" virtualName=""
         explicitFocusOrder="0" pos="5 62 26 12" bkgCol="0" textCol="ffffffff"
         outlineCol="0" edTextCol="ff000000" edBkgCol="0" labelText="C1"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="" id="f66198b12cbd2262" memberName="ctrl2Slider" virtualName="DynamicParameterSlider"
          explicitFocusOrder="0" pos="5 112 25 23" rotarysliderfill="7fcbcbcb"
          min="0" max="1" int="0.0001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="" id="6e2d667d756e500b" memberName="ctrl2Label" virtualName=""
         explicitFocusOrder="0" pos="5 102 26 12" bkgCol="0" textCol="ffffffff"
         outlineCol="0" edTextCol="ff000000" edBkgCol="0" labelText="C2"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="" id="1d1749d71d880fb2" memberName="ctrl3Slider" virtualName="DynamicParameterSlider"
          explicitFocusOrder="0" pos="5 152 25 23" rotarysliderfill="7fcbcbcb"
          min="0" max="1" int="0.0001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="" id="860d6f06cd6a97be" memberName="ctrl3Label" virtualName=""
         explicitFocusOrder="0" pos="5 142 26 12" bkgCol="0" textCol="ffffffff"
         outlineCol="0" edTextCol="ff000000" edBkgCol="0" labelText="C3"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="" id="7485f0ac102e097d" memberName="ctrl4Slider" virtualName="DynamicParameterSlider"
          explicitFocusOrder="0" pos="5 192 25 23" rotarysliderfill="7fcbcbcb"
          min="0" max="1" int="0.0001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="" id="e8a5fc810e0f29ed" memberName="ctrl4Label" virtualName=""
         explicitFocusOrder="0" pos="5 182 26 12" bkgCol="0" textCol="ffffffff"
         outlineCol="0" edTextCol="ff000000" edBkgCol="0" labelText="C4"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
