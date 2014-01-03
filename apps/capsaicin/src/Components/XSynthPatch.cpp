/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  18 Jan 2010 11:31:29 am

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
#include "../XSynthEditor.h"
//[/Headers]

#include "XSynthPatch.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
XSynthPatch::XSynthPatch (XSynthPlugin* plugin_, Master* master_)
    : plugin (plugin_),
      master (master_),
      osc1Select (0),
      osc2Select (0),
      osc3Select (0),
      osc4Select (0),
      chorusGroup (0),
      toneGroup (0),
      filterGroup (0),
      ampGroup (0),
      partials (0),
      scope (0),
      ampAttackSlider (0),
      ampDecaySlider (0),
      ampSustainSlider (0),
      ampReleaseSlider (0),
      filterCutoffSlider (0),
      filterResoSlider (0),
      filterTrackingSlider (0),
      ampAdsrLabel (0),
      filterLabel (0),
      driveGroup (0),
      eqGroup (0),
      delayGroup (0),
      destructDriveSlider (0),
      destructLowpassSlider (0),
      toneAttackValueSlider (0),
      toneAttackSlider (0),
      toneDecayValueSlider (0),
      toneDecaySlider (0),
      toneMasterSlider (0),
      toneDetuneSlider (0),
      toneAdsrLabel (0),
      masterGroup (0),
      masterGainSlider (0),
      enableButton (0),
      partNumberSlider (0),
      destructHighpassSlider (0),
      driveLabel (0),
      masterPanSlider (0),
      filterAttackValueSlider (0),
      filterAttackTimeSlider (0),
      filterDecayValueSlider (0),
      filterDecayTimeSlider (0),
      filterEnvelopeLabel (0),
      partKeyboardSlider (0),
      portaButton (0),
      polyButton (0),
      masterLabel (0),
      stereoButton (0),
      chorusFreqSlider (0),
      chorusDelaySlider (0),
      chorusDepthSlider (0),
      chorusFeedbackSlider (0),
      chorusGainSlider (0),
      chorusLabel (0),
      eqgraph (0),
      eqFreq1Slider (0),
      eqGain1Slider (0),
      eqFreq2Slider (0),
      eqGain2Slider (0),
      eqFreq3Slider (0),
      eqGain3Slider (0),
      filterLfoDepthSlider (0),
      filterLfoFrequencySlider (0),
      filterLfoRandomSlider (0),
      toneReleaseValueSlider (0),
      toneReleaseSlider (0),
      eqBw2Slider (0),
      eqBw3Slider (0),
      eqFreq4Slider (0),
      eqGain4Slider (0),
      eq1Label (0),
      eq2Label (0),
      delayVolumeSlider (0),
      delayTimeSlider (0),
      delayFeedbackSlider (0),
      delayPanSlider (0),
      delayFilterSlider (0),
      echoLabel (0),
      ampEnvelope (0),
      joystick (0),
      noiseGroup (0),
      noiseGainSlider (0),
      noiseLabel (0),
      pitchEnvelope (0),
      osc1SelectPhase (0),
      osc2SelectPhase (0),
      osc3SelectPhase (0),
      osc4SelectPhase (0),
      eqBw1Slider (0),
      eqBw4Slider (0),
      filterLfoLabel (0),
      filterTypeBox (0)
{
    addAndMakeVisible (osc1Select = new TextButton (String::empty));
    osc1Select->setButtonText (T("1"));
    osc1Select->setConnectedEdges (Button::ConnectedOnRight | Button::ConnectedOnBottom);
    osc1Select->addButtonListener (this);
    osc1Select->setColour (TextButton::buttonColourId, Colour (0xff827474));

    addAndMakeVisible (osc2Select = new TextButton (String::empty));
    osc2Select->setButtonText (T("2"));
    osc2Select->setConnectedEdges (Button::ConnectedOnRight | Button::ConnectedOnBottom);
    osc2Select->addButtonListener (this);
    osc2Select->setColour (TextButton::buttonColourId, Colour (0xff827474));

    addAndMakeVisible (osc3Select = new TextButton (String::empty));
    osc3Select->setButtonText (T("3"));
    osc3Select->setConnectedEdges (Button::ConnectedOnRight | Button::ConnectedOnBottom);
    osc3Select->addButtonListener (this);
    osc3Select->setColour (TextButton::buttonColourId, Colour (0xff827474));

    addAndMakeVisible (osc4Select = new TextButton (String::empty));
    osc4Select->setButtonText (T("4"));
    osc4Select->setConnectedEdges (Button::ConnectedOnRight | Button::ConnectedOnBottom);
    osc4Select->addButtonListener (this);
    osc4Select->setColour (TextButton::buttonColourId, Colour (0xff827474));

    addAndMakeVisible (chorusGroup = new GroupComponent (String::empty,
                                                         T("Chorus")));
    chorusGroup->setTextLabelPosition (Justification::centred);
    chorusGroup->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    chorusGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (toneGroup = new GroupComponent (String::empty,
                                                       T("Tone")));
    toneGroup->setTextLabelPosition (Justification::centred);
    toneGroup->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    toneGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (filterGroup = new GroupComponent (String::empty,
                                                         T("Filter")));
    filterGroup->setTextLabelPosition (Justification::centred);
    filterGroup->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    filterGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (ampGroup = new GroupComponent (String::empty,
                                                      T("Amp")));
    ampGroup->setTextLabelPosition (Justification::centred);
    ampGroup->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    ampGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (partials = new OscillatorPartials (master));

    addAndMakeVisible (scope = new OscillatorScope (master));

    addAndMakeVisible (ampAttackSlider = new ImageSlider (String::empty));
    ampAttackSlider->setTooltip (T("Amp attack"));
    ampAttackSlider->setRange (0, 1, 0.0001);
    ampAttackSlider->setSliderStyle (Slider::LinearVertical);
    ampAttackSlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    ampAttackSlider->setColour (Slider::thumbColourId, Colour (0xff9ba6da));
    ampAttackSlider->addListener (this);

    addAndMakeVisible (ampDecaySlider = new ImageSlider (String::empty));
    ampDecaySlider->setTooltip (T("Amp decay"));
    ampDecaySlider->setRange (0, 1, 0.0001);
    ampDecaySlider->setSliderStyle (Slider::LinearVertical);
    ampDecaySlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    ampDecaySlider->setColour (Slider::thumbColourId, Colour (0xff9ba6da));
    ampDecaySlider->addListener (this);

    addAndMakeVisible (ampSustainSlider = new ImageSlider (String::empty));
    ampSustainSlider->setTooltip (T("Amp sustain"));
    ampSustainSlider->setRange (0, 1, 0.0001);
    ampSustainSlider->setSliderStyle (Slider::LinearVertical);
    ampSustainSlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    ampSustainSlider->setColour (Slider::thumbColourId, Colour (0xff9ba6da));
    ampSustainSlider->addListener (this);

    addAndMakeVisible (ampReleaseSlider = new ImageSlider (String::empty));
    ampReleaseSlider->setTooltip (T("Amp release"));
    ampReleaseSlider->setRange (0, 1, 0.0001);
    ampReleaseSlider->setSliderStyle (Slider::LinearVertical);
    ampReleaseSlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    ampReleaseSlider->setColour (Slider::thumbColourId, Colour (0xff9ba6da));
    ampReleaseSlider->addListener (this);

    addAndMakeVisible (filterCutoffSlider = new ImageSlider (String::empty));
    filterCutoffSlider->setTooltip (T("Filter cutoff frequency"));
    filterCutoffSlider->setRange (0, 1, 0.0001);
    filterCutoffSlider->setSliderStyle (Slider::LinearVertical);
    filterCutoffSlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    filterCutoffSlider->setColour (Slider::thumbColourId, Colour (0xfff2f2f2));
    filterCutoffSlider->addListener (this);

    addAndMakeVisible (filterResoSlider = new ImageSlider (String::empty));
    filterResoSlider->setTooltip (T("Filter resonance"));
    filterResoSlider->setRange (0, 1, 0.0001);
    filterResoSlider->setSliderStyle (Slider::LinearVertical);
    filterResoSlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    filterResoSlider->setColour (Slider::thumbColourId, Colour (0xfff2f2f2));
    filterResoSlider->addListener (this);

    addAndMakeVisible (filterTrackingSlider = new ImageSlider (String::empty));
    filterTrackingSlider->setTooltip (T("Keyboard tracking"));
    filterTrackingSlider->setRange (0, 1, 0.0001);
    filterTrackingSlider->setSliderStyle (Slider::LinearVertical);
    filterTrackingSlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    filterTrackingSlider->setColour (Slider::thumbColourId, Colour (0xfff2f2f2));
    filterTrackingSlider->addListener (this);

    addAndMakeVisible (ampAdsrLabel = new Label (String::empty,
                                                 T("A D S R")));
    ampAdsrLabel->setFont (Font (15.0000f, Font::plain));
    ampAdsrLabel->setJustificationType (Justification::centredLeft);
    ampAdsrLabel->setEditable (false, false, false);
    ampAdsrLabel->setColour (Label::backgroundColourId, Colour (0x0));
    ampAdsrLabel->setColour (Label::textColourId, Colours::black);
    ampAdsrLabel->setColour (Label::outlineColourId, Colour (0x0));
    ampAdsrLabel->setColour (TextEditor::textColourId, Colours::black);
    ampAdsrLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (filterLabel = new Label (String::empty,
                                                T("C Q T")));
    filterLabel->setFont (Font (15.0000f, Font::plain));
    filterLabel->setJustificationType (Justification::centredLeft);
    filterLabel->setEditable (false, false, false);
    filterLabel->setColour (Label::backgroundColourId, Colour (0x0));
    filterLabel->setColour (Label::textColourId, Colours::black);
    filterLabel->setColour (Label::outlineColourId, Colour (0x0));
    filterLabel->setColour (TextEditor::textColourId, Colours::black);
    filterLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (driveGroup = new GroupComponent (String::empty,
                                                        T("Drive")));
    driveGroup->setTextLabelPosition (Justification::centred);
    driveGroup->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    driveGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (eqGroup = new GroupComponent (String::empty,
                                                     T("EQ")));
    eqGroup->setTextLabelPosition (Justification::centred);
    eqGroup->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    eqGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (delayGroup = new GroupComponent (String::empty,
                                                        T("Delay")));
    delayGroup->setTextLabelPosition (Justification::centred);
    delayGroup->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    delayGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (destructDriveSlider = new ImageSlider (String::empty));
    destructDriveSlider->setTooltip (T("Destruct drive"));
    destructDriveSlider->setRange (0, 1, 0.0001);
    destructDriveSlider->setSliderStyle (Slider::LinearVertical);
    destructDriveSlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    destructDriveSlider->setColour (Slider::thumbColourId, Colour (0xff666666));
    destructDriveSlider->addListener (this);

    addAndMakeVisible (destructLowpassSlider = new ImageSlider (String::empty));
    destructLowpassSlider->setTooltip (T("Destruct lowpass"));
    destructLowpassSlider->setRange (0, 1, 0.0001);
    destructLowpassSlider->setSliderStyle (Slider::LinearVertical);
    destructLowpassSlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    destructLowpassSlider->setColour (Slider::thumbColourId, Colour (0xff666666));
    destructLowpassSlider->addListener (this);

    addAndMakeVisible (toneAttackValueSlider = new ImageSlider (String::empty));
    toneAttackValueSlider->setTooltip (T("Tone attack value"));
    toneAttackValueSlider->setRange (0, 1, 0.0001);
    toneAttackValueSlider->setSliderStyle (Slider::LinearVertical);
    toneAttackValueSlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    toneAttackValueSlider->setColour (Slider::thumbColourId, Colour (0xffdabb9b));
    toneAttackValueSlider->addListener (this);

    addAndMakeVisible (toneAttackSlider = new ImageSlider (String::empty));
    toneAttackSlider->setTooltip (T("Tone attack time"));
    toneAttackSlider->setRange (0, 1, 0.0001);
    toneAttackSlider->setSliderStyle (Slider::LinearVertical);
    toneAttackSlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    toneAttackSlider->setColour (Slider::thumbColourId, Colour (0xffdabb9b));
    toneAttackSlider->addListener (this);

    addAndMakeVisible (toneDecayValueSlider = new ImageSlider (String::empty));
    toneDecayValueSlider->setTooltip (T("Tone release value"));
    toneDecayValueSlider->setRange (0, 1, 0.0001);
    toneDecayValueSlider->setSliderStyle (Slider::LinearVertical);
    toneDecayValueSlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    toneDecayValueSlider->setColour (Slider::thumbColourId, Colour (0xffdabb9b));
    toneDecayValueSlider->addListener (this);

    addAndMakeVisible (toneDecaySlider = new ImageSlider (String::empty));
    toneDecaySlider->setTooltip (T("Tone release time"));
    toneDecaySlider->setRange (0, 1, 0.0001);
    toneDecaySlider->setSliderStyle (Slider::LinearVertical);
    toneDecaySlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    toneDecaySlider->setColour (Slider::thumbColourId, Colour (0xffdabb9b));
    toneDecaySlider->addListener (this);

    addAndMakeVisible (toneMasterSlider = new ImageSlider (String::empty));
    toneMasterSlider->setTooltip (T("Tone release"));
    toneMasterSlider->setRange (0, 1, 0.0001);
    toneMasterSlider->setSliderStyle (Slider::LinearVertical);
    toneMasterSlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    toneMasterSlider->setColour (Slider::thumbColourId, Colour (0xffce8f4d));
    toneMasterSlider->addListener (this);

    addAndMakeVisible (toneDetuneSlider = new ImageSlider (String::empty));
    toneDetuneSlider->setTooltip (T("Tone release"));
    toneDetuneSlider->setRange (0, 1, 0.0001);
    toneDetuneSlider->setSliderStyle (Slider::LinearVertical);
    toneDetuneSlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    toneDetuneSlider->setColour (Slider::thumbColourId, Colour (0xffce8f4d));
    toneDetuneSlider->addListener (this);

    addAndMakeVisible (toneAdsrLabel = new Label (String::empty,
                                                  T("T D    A at D dt R rt")));
    toneAdsrLabel->setFont (Font (15.0000f, Font::plain));
    toneAdsrLabel->setJustificationType (Justification::centredLeft);
    toneAdsrLabel->setEditable (false, false, false);
    toneAdsrLabel->setColour (Label::backgroundColourId, Colour (0x0));
    toneAdsrLabel->setColour (Label::textColourId, Colours::black);
    toneAdsrLabel->setColour (Label::outlineColourId, Colour (0x0));
    toneAdsrLabel->setColour (TextEditor::textColourId, Colours::black);
    toneAdsrLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (masterGroup = new GroupComponent (String::empty,
                                                         T("Master")));
    masterGroup->setTextLabelPosition (Justification::centred);
    masterGroup->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    masterGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (masterGainSlider = new ImageSlider (String::empty));
    masterGainSlider->setTooltip (T("Master gain"));
    masterGainSlider->setRange (0, 1, 0.0001);
    masterGainSlider->setSliderStyle (Slider::LinearVertical);
    masterGainSlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    masterGainSlider->setColour (Slider::thumbColourId, Colour (0xff6479df));
    masterGainSlider->addListener (this);

    addAndMakeVisible (enableButton = new ParameterToggleButton (String::empty));
    enableButton->setButtonText (T("ON"));
    enableButton->addButtonListener (this);

    addAndMakeVisible (partNumberSlider = new Slider (String::empty));
    partNumberSlider->setTooltip (T("Part number"));
    partNumberSlider->setRange (1, 16, 1);
    partNumberSlider->setSliderStyle (Slider::IncDecButtons);
    partNumberSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 20, 20);
    partNumberSlider->addListener (this);

    addAndMakeVisible (destructHighpassSlider = new ImageSlider (String::empty));
    destructHighpassSlider->setTooltip (T("Destruct highpass"));
    destructHighpassSlider->setRange (0, 1, 0.0001);
    destructHighpassSlider->setSliderStyle (Slider::LinearVertical);
    destructHighpassSlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    destructHighpassSlider->setColour (Slider::thumbColourId, Colour (0xff666666));
    destructHighpassSlider->addListener (this);

    addAndMakeVisible (driveLabel = new Label (String::empty,
                                               T("dr lp hp")));
    driveLabel->setFont (Font (15.0000f, Font::plain));
    driveLabel->setJustificationType (Justification::centredLeft);
    driveLabel->setEditable (false, false, false);
    driveLabel->setColour (Label::backgroundColourId, Colour (0x0));
    driveLabel->setColour (Label::textColourId, Colours::black);
    driveLabel->setColour (Label::outlineColourId, Colour (0x0));
    driveLabel->setColour (TextEditor::textColourId, Colours::black);
    driveLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (masterPanSlider = new ImageSlider (String::empty));
    masterPanSlider->setTooltip (T("Master pan"));
    masterPanSlider->setRange (0, 1, 0.0001);
    masterPanSlider->setSliderStyle (Slider::LinearVertical);
    masterPanSlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    masterPanSlider->setColour (Slider::thumbColourId, Colour (0xff6479df));
    masterPanSlider->addListener (this);

    addAndMakeVisible (filterAttackValueSlider = new ImageSlider (String::empty));
    filterAttackValueSlider->setTooltip (T("Filter cutoff attack value"));
    filterAttackValueSlider->setRange (0, 1, 0.0001);
    filterAttackValueSlider->setSliderStyle (Slider::LinearVertical);
    filterAttackValueSlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    filterAttackValueSlider->setColour (Slider::thumbColourId, Colour (0xfff2f2f2));
    filterAttackValueSlider->addListener (this);

    addAndMakeVisible (filterAttackTimeSlider = new ImageSlider (String::empty));
    filterAttackTimeSlider->setTooltip (T("Filter cutoff attack time"));
    filterAttackTimeSlider->setRange (0, 1, 0.0001);
    filterAttackTimeSlider->setSliderStyle (Slider::LinearVertical);
    filterAttackTimeSlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    filterAttackTimeSlider->setColour (Slider::thumbColourId, Colour (0xfff2f2f2));
    filterAttackTimeSlider->addListener (this);

    addAndMakeVisible (filterDecayValueSlider = new ImageSlider (String::empty));
    filterDecayValueSlider->setTooltip (T("Filter cutoff decay value"));
    filterDecayValueSlider->setRange (0, 1, 0.0001);
    filterDecayValueSlider->setSliderStyle (Slider::LinearVertical);
    filterDecayValueSlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    filterDecayValueSlider->setColour (Slider::thumbColourId, Colour (0xfff2f2f2));
    filterDecayValueSlider->addListener (this);

    addAndMakeVisible (filterDecayTimeSlider = new ImageSlider (String::empty));
    filterDecayTimeSlider->setTooltip (T("Filter cutoff decay time"));
    filterDecayTimeSlider->setRange (0, 1, 0.0001);
    filterDecayTimeSlider->setSliderStyle (Slider::LinearVertical);
    filterDecayTimeSlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    filterDecayTimeSlider->setColour (Slider::thumbColourId, Colour (0xfff2f2f2));
    filterDecayTimeSlider->addListener (this);

    addAndMakeVisible (filterEnvelopeLabel = new Label (String::empty,
                                                        T("A at D dt")));
    filterEnvelopeLabel->setFont (Font (15.0000f, Font::plain));
    filterEnvelopeLabel->setJustificationType (Justification::centredLeft);
    filterEnvelopeLabel->setEditable (false, false, false);
    filterEnvelopeLabel->setColour (Label::backgroundColourId, Colour (0x0));
    filterEnvelopeLabel->setColour (Label::textColourId, Colours::black);
    filterEnvelopeLabel->setColour (Label::outlineColourId, Colour (0x0));
    filterEnvelopeLabel->setColour (TextEditor::textColourId, Colours::black);
    filterEnvelopeLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (partKeyboardSlider = new Slider (String::empty));
    partKeyboardSlider->setTooltip (T("Part number"));
    partKeyboardSlider->setRange (0, 127, 1);
    partKeyboardSlider->setSliderStyle (Slider::TwoValueHorizontal);
    partKeyboardSlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 20);
    partKeyboardSlider->setColour (Slider::thumbColourId, Colour (0xffd22d27));
    partKeyboardSlider->addListener (this);

    addAndMakeVisible (portaButton = new ParameterToggleButton (String::empty));
    portaButton->setButtonText (T("PORTA"));
    portaButton->addButtonListener (this);

    addAndMakeVisible (polyButton = new ParameterToggleButton (String::empty));
    polyButton->setButtonText (T("POLY"));
    polyButton->addButtonListener (this);

    addAndMakeVisible (masterLabel = new Label (String::empty,
                                                T("G P     KEYS RANGE")));
    masterLabel->setFont (Font (15.0000f, Font::plain));
    masterLabel->setJustificationType (Justification::centredLeft);
    masterLabel->setEditable (false, false, false);
    masterLabel->setColour (Label::backgroundColourId, Colour (0x0));
    masterLabel->setColour (Label::textColourId, Colours::black);
    masterLabel->setColour (Label::outlineColourId, Colour (0x0));
    masterLabel->setColour (TextEditor::textColourId, Colours::black);
    masterLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (stereoButton = new ParameterToggleButton (String::empty));
    stereoButton->setButtonText (T("STEREO"));
    stereoButton->addButtonListener (this);

    addAndMakeVisible (chorusFreqSlider = new ImageSlider (String::empty));
    chorusFreqSlider->setTooltip (T("Chorus frequency"));
    chorusFreqSlider->setRange (0, 1, 0.0001);
    chorusFreqSlider->setSliderStyle (Slider::LinearVertical);
    chorusFreqSlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    chorusFreqSlider->setColour (Slider::thumbColourId, Colour (0xff47596b));
    chorusFreqSlider->addListener (this);

    addAndMakeVisible (chorusDelaySlider = new ImageSlider (String::empty));
    chorusDelaySlider->setTooltip (T("Chorus delay"));
    chorusDelaySlider->setRange (0, 1, 0.0001);
    chorusDelaySlider->setSliderStyle (Slider::LinearVertical);
    chorusDelaySlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    chorusDelaySlider->setColour (Slider::thumbColourId, Colour (0xff47596b));
    chorusDelaySlider->addListener (this);

    addAndMakeVisible (chorusDepthSlider = new ImageSlider (String::empty));
    chorusDepthSlider->setTooltip (T("Chorus depth"));
    chorusDepthSlider->setRange (0, 1, 0.0001);
    chorusDepthSlider->setSliderStyle (Slider::LinearVertical);
    chorusDepthSlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    chorusDepthSlider->setColour (Slider::thumbColourId, Colour (0xff47596b));
    chorusDepthSlider->addListener (this);

    addAndMakeVisible (chorusFeedbackSlider = new ImageSlider (String::empty));
    chorusFeedbackSlider->setTooltip (T("Chorus feedback"));
    chorusFeedbackSlider->setRange (0, 1, 0.0001);
    chorusFeedbackSlider->setSliderStyle (Slider::LinearVertical);
    chorusFeedbackSlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    chorusFeedbackSlider->setColour (Slider::thumbColourId, Colour (0xff47596b));
    chorusFeedbackSlider->addListener (this);

    addAndMakeVisible (chorusGainSlider = new ImageSlider (String::empty));
    chorusGainSlider->setTooltip (T("Chorus gain"));
    chorusGainSlider->setRange (0, 1, 0.0001);
    chorusGainSlider->setSliderStyle (Slider::LinearVertical);
    chorusGainSlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    chorusGainSlider->setColour (Slider::thumbColourId, Colour (0xff47596b));
    chorusGainSlider->addListener (this);

    addAndMakeVisible (chorusLabel = new Label (String::empty,
                                                T("G fq dl dp fe")));
    chorusLabel->setFont (Font (15.0000f, Font::plain));
    chorusLabel->setJustificationType (Justification::centredLeft);
    chorusLabel->setEditable (false, false, false);
    chorusLabel->setColour (Label::backgroundColourId, Colour (0x0));
    chorusLabel->setColour (Label::textColourId, Colours::black);
    chorusLabel->setColour (Label::outlineColourId, Colour (0x0));
    chorusLabel->setColour (TextEditor::textColourId, Colours::black);
    chorusLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (eqgraph = new EQGraph());

    addAndMakeVisible (eqFreq1Slider = new ParameterSlider (String::empty));
    eqFreq1Slider->setTooltip (T("Eq 1 Frequency"));
    eqFreq1Slider->setRange (0, 1, 0.0001);
    eqFreq1Slider->setSliderStyle (Slider::RotaryVerticalDrag);
    eqFreq1Slider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    eqFreq1Slider->setColour (Slider::thumbColourId, Colour (0xff47596b));
    eqFreq1Slider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    eqFreq1Slider->addListener (this);

    addAndMakeVisible (eqGain1Slider = new ParameterSlider (String::empty));
    eqGain1Slider->setTooltip (T("Eq 1 Gain"));
    eqGain1Slider->setRange (0, 1, 0.0001);
    eqGain1Slider->setSliderStyle (Slider::RotaryVerticalDrag);
    eqGain1Slider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    eqGain1Slider->setColour (Slider::thumbColourId, Colour (0xff47596b));
    eqGain1Slider->setColour (Slider::trackColourId, Colour (0x7fbebaba));
    eqGain1Slider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    eqGain1Slider->addListener (this);

    addAndMakeVisible (eqFreq2Slider = new ParameterSlider (String::empty));
    eqFreq2Slider->setTooltip (T("Eq 2 Frequency"));
    eqFreq2Slider->setRange (0, 1, 0.0001);
    eqFreq2Slider->setSliderStyle (Slider::RotaryVerticalDrag);
    eqFreq2Slider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    eqFreq2Slider->setColour (Slider::thumbColourId, Colour (0xff47596b));
    eqFreq2Slider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    eqFreq2Slider->addListener (this);

    addAndMakeVisible (eqGain2Slider = new ParameterSlider (String::empty));
    eqGain2Slider->setTooltip (T("Eq 2 Gain"));
    eqGain2Slider->setRange (0, 1, 0.0001);
    eqGain2Slider->setSliderStyle (Slider::RotaryVerticalDrag);
    eqGain2Slider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    eqGain2Slider->setColour (Slider::thumbColourId, Colour (0xff47596b));
    eqGain2Slider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    eqGain2Slider->addListener (this);

    addAndMakeVisible (eqFreq3Slider = new ParameterSlider (String::empty));
    eqFreq3Slider->setTooltip (T("Eq 3 Frequency"));
    eqFreq3Slider->setRange (0, 1, 0.0001);
    eqFreq3Slider->setSliderStyle (Slider::RotaryVerticalDrag);
    eqFreq3Slider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    eqFreq3Slider->setColour (Slider::thumbColourId, Colour (0xff47596b));
    eqFreq3Slider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    eqFreq3Slider->addListener (this);

    addAndMakeVisible (eqGain3Slider = new ParameterSlider (String::empty));
    eqGain3Slider->setTooltip (T("Eq 3 Gain"));
    eqGain3Slider->setRange (0, 1, 0.0001);
    eqGain3Slider->setSliderStyle (Slider::RotaryVerticalDrag);
    eqGain3Slider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    eqGain3Slider->setColour (Slider::thumbColourId, Colour (0xff47596b));
    eqGain3Slider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    eqGain3Slider->addListener (this);

    addAndMakeVisible (filterLfoDepthSlider = new ParameterSlider (String::empty));
    filterLfoDepthSlider->setTooltip (T("Filter lfo depth"));
    filterLfoDepthSlider->setRange (0, 1, 0.001);
    filterLfoDepthSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    filterLfoDepthSlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    filterLfoDepthSlider->setColour (Slider::thumbColourId, Colour (0xff47596b));
    filterLfoDepthSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7ff5f5f5));
    filterLfoDepthSlider->addListener (this);

    addAndMakeVisible (filterLfoFrequencySlider = new ParameterSlider (String::empty));
    filterLfoFrequencySlider->setTooltip (T("Filter lfo frequency"));
    filterLfoFrequencySlider->setRange (0, 1, 0.001);
    filterLfoFrequencySlider->setSliderStyle (Slider::RotaryVerticalDrag);
    filterLfoFrequencySlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    filterLfoFrequencySlider->setColour (Slider::thumbColourId, Colour (0xff47596b));
    filterLfoFrequencySlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    filterLfoFrequencySlider->addListener (this);

    addAndMakeVisible (filterLfoRandomSlider = new ParameterSlider (String::empty));
    filterLfoRandomSlider->setTooltip (T("Filter lfo random"));
    filterLfoRandomSlider->setRange (0, 1, 0.001);
    filterLfoRandomSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    filterLfoRandomSlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    filterLfoRandomSlider->setColour (Slider::thumbColourId, Colour (0xff47596b));
    filterLfoRandomSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    filterLfoRandomSlider->addListener (this);

    addAndMakeVisible (toneReleaseValueSlider = new ImageSlider (String::empty));
    toneReleaseValueSlider->setTooltip (T("Tone release value"));
    toneReleaseValueSlider->setRange (0, 1, 0.0001);
    toneReleaseValueSlider->setSliderStyle (Slider::LinearVertical);
    toneReleaseValueSlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    toneReleaseValueSlider->setColour (Slider::thumbColourId, Colour (0xffdabb9b));
    toneReleaseValueSlider->addListener (this);

    addAndMakeVisible (toneReleaseSlider = new ImageSlider (String::empty));
    toneReleaseSlider->setTooltip (T("Tone release time"));
    toneReleaseSlider->setRange (0, 1, 0.0001);
    toneReleaseSlider->setSliderStyle (Slider::LinearVertical);
    toneReleaseSlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    toneReleaseSlider->setColour (Slider::thumbColourId, Colour (0xffdabb9b));
    toneReleaseSlider->addListener (this);

    addAndMakeVisible (eqBw2Slider = new ParameterSlider (String::empty));
    eqBw2Slider->setTooltip (T("Eq 2 Q"));
    eqBw2Slider->setRange (0, 1, 0.0001);
    eqBw2Slider->setSliderStyle (Slider::RotaryVerticalDrag);
    eqBw2Slider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    eqBw2Slider->setColour (Slider::thumbColourId, Colour (0xff47596b));
    eqBw2Slider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    eqBw2Slider->addListener (this);

    addAndMakeVisible (eqBw3Slider = new ParameterSlider (String::empty));
    eqBw3Slider->setTooltip (T("Eq 3 Q"));
    eqBw3Slider->setRange (0, 1, 0.0001);
    eqBw3Slider->setSliderStyle (Slider::RotaryVerticalDrag);
    eqBw3Slider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    eqBw3Slider->setColour (Slider::thumbColourId, Colour (0xff47596b));
    eqBw3Slider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    eqBw3Slider->addListener (this);

    addAndMakeVisible (eqFreq4Slider = new ParameterSlider (String::empty));
    eqFreq4Slider->setTooltip (T("Eq 4 Frequency"));
    eqFreq4Slider->setRange (0, 1, 0.0001);
    eqFreq4Slider->setSliderStyle (Slider::RotaryVerticalDrag);
    eqFreq4Slider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    eqFreq4Slider->setColour (Slider::thumbColourId, Colour (0xff47596b));
    eqFreq4Slider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    eqFreq4Slider->addListener (this);

    addAndMakeVisible (eqGain4Slider = new ParameterSlider (String::empty));
    eqGain4Slider->setTooltip (T("Eq 4 Gain"));
    eqGain4Slider->setRange (0, 1, 0.0001);
    eqGain4Slider->setSliderStyle (Slider::RotaryVerticalDrag);
    eqGain4Slider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    eqGain4Slider->setColour (Slider::thumbColourId, Colour (0xff47596b));
    eqGain4Slider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    eqGain4Slider->addListener (this);

    addAndMakeVisible (eq1Label = new Label (String::empty,
                                             T("1\n\n2\n\n3\n\n4")));
    eq1Label->setFont (Font (12.0000f, Font::plain));
    eq1Label->setJustificationType (Justification::centred);
    eq1Label->setEditable (false, false, false);
    eq1Label->setColour (Label::backgroundColourId, Colour (0x0));
    eq1Label->setColour (Label::textColourId, Colours::black);
    eq1Label->setColour (Label::outlineColourId, Colour (0x0));
    eq1Label->setColour (TextEditor::textColourId, Colours::black);
    eq1Label->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (eq2Label = new Label (String::empty,
                                             T("G     F     Q")));
    eq2Label->setFont (Font (12.0000f, Font::plain));
    eq2Label->setJustificationType (Justification::centred);
    eq2Label->setEditable (false, false, false);
    eq2Label->setColour (Label::backgroundColourId, Colour (0x0));
    eq2Label->setColour (Label::textColourId, Colours::black);
    eq2Label->setColour (Label::outlineColourId, Colour (0x0));
    eq2Label->setColour (TextEditor::textColourId, Colours::black);
    eq2Label->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (delayVolumeSlider = new ImageSlider (String::empty));
    delayVolumeSlider->setTooltip (T("Delay volume"));
    delayVolumeSlider->setRange (0, 1, 0.0001);
    delayVolumeSlider->setSliderStyle (Slider::LinearVertical);
    delayVolumeSlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    delayVolumeSlider->setColour (Slider::thumbColourId, Colour (0xff715ec3));
    delayVolumeSlider->addListener (this);

    addAndMakeVisible (delayTimeSlider = new ImageSlider (String::empty));
    delayTimeSlider->setTooltip (T("Delay time"));
    delayTimeSlider->setRange (0, 1, 0.0001);
    delayTimeSlider->setSliderStyle (Slider::LinearVertical);
    delayTimeSlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    delayTimeSlider->setColour (Slider::thumbColourId, Colour (0xff715ec3));
    delayTimeSlider->addListener (this);

    addAndMakeVisible (delayFeedbackSlider = new ImageSlider (String::empty));
    delayFeedbackSlider->setTooltip (T("Delay feedback"));
    delayFeedbackSlider->setRange (0, 1, 0.0001);
    delayFeedbackSlider->setSliderStyle (Slider::LinearVertical);
    delayFeedbackSlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    delayFeedbackSlider->setColour (Slider::thumbColourId, Colour (0xff715ec3));
    delayFeedbackSlider->addListener (this);

    addAndMakeVisible (delayPanSlider = new ImageSlider (String::empty));
    delayPanSlider->setTooltip (T("Delay pan"));
    delayPanSlider->setRange (0, 1, 0.0001);
    delayPanSlider->setSliderStyle (Slider::LinearVertical);
    delayPanSlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    delayPanSlider->setColour (Slider::thumbColourId, Colour (0xff715ec3));
    delayPanSlider->addListener (this);

    addAndMakeVisible (delayFilterSlider = new ImageSlider (String::empty));
    delayFilterSlider->setTooltip (T("Delay filter"));
    delayFilterSlider->setRange (0, 1, 0.0001);
    delayFilterSlider->setSliderStyle (Slider::LinearVertical);
    delayFilterSlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    delayFilterSlider->setColour (Slider::thumbColourId, Colour (0xff715ec3));
    delayFilterSlider->addListener (this);

    addAndMakeVisible (echoLabel = new Label (String::empty,
                                              T("G P T F lp")));
    echoLabel->setFont (Font (15.0000f, Font::plain));
    echoLabel->setJustificationType (Justification::centredLeft);
    echoLabel->setEditable (false, false, false);
    echoLabel->setColour (Label::backgroundColourId, Colour (0x0));
    echoLabel->setColour (Label::textColourId, Colours::black);
    echoLabel->setColour (Label::outlineColourId, Colour (0x0));
    echoLabel->setColour (TextEditor::textColourId, Colours::black);
    echoLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (ampEnvelope = new EnvelopeEditor (master));

    addAndMakeVisible (joystick = new ParameterJoystick());

    addAndMakeVisible (noiseGroup = new GroupComponent (String::empty,
                                                        T("Nz")));
    noiseGroup->setTextLabelPosition (Justification::centred);
    noiseGroup->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    noiseGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (noiseGainSlider = new ImageSlider (String::empty));
    noiseGainSlider->setTooltip (T("Noise volume"));
    noiseGainSlider->setRange (0, 1, 0.0001);
    noiseGainSlider->setSliderStyle (Slider::LinearVertical);
    noiseGainSlider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    noiseGainSlider->setColour (Slider::thumbColourId, Colour (0xff5c8f50));
    noiseGainSlider->addListener (this);

    addAndMakeVisible (noiseLabel = new Label (String::empty,
                                               T("Gain")));
    noiseLabel->setFont (Font (15.0000f, Font::plain));
    noiseLabel->setJustificationType (Justification::centredLeft);
    noiseLabel->setEditable (false, false, false);
    noiseLabel->setColour (Label::backgroundColourId, Colour (0x0));
    noiseLabel->setColour (Label::textColourId, Colours::black);
    noiseLabel->setColour (Label::outlineColourId, Colour (0x0));
    noiseLabel->setColour (TextEditor::textColourId, Colours::black);
    noiseLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (pitchEnvelope = new EnvelopeEditor (master));

    addAndMakeVisible (osc1SelectPhase = new TextButton (String::empty));
    osc1SelectPhase->setButtonText (T("1P"));
    osc1SelectPhase->setConnectedEdges (Button::ConnectedOnRight | Button::ConnectedOnTop);
    osc1SelectPhase->addButtonListener (this);
    osc1SelectPhase->setColour (TextButton::buttonColourId, Colour (0xff805f8b));

    addAndMakeVisible (osc2SelectPhase = new TextButton (String::empty));
    osc2SelectPhase->setButtonText (T("2P"));
    osc2SelectPhase->setConnectedEdges (Button::ConnectedOnRight | Button::ConnectedOnTop);
    osc2SelectPhase->addButtonListener (this);
    osc2SelectPhase->setColour (TextButton::buttonColourId, Colour (0xff805f8b));

    addAndMakeVisible (osc3SelectPhase = new TextButton (String::empty));
    osc3SelectPhase->setButtonText (T("3P"));
    osc3SelectPhase->setConnectedEdges (Button::ConnectedOnRight | Button::ConnectedOnTop);
    osc3SelectPhase->addButtonListener (this);
    osc3SelectPhase->setColour (TextButton::buttonColourId, Colour (0xff805f8b));

    addAndMakeVisible (osc4SelectPhase = new TextButton (String::empty));
    osc4SelectPhase->setButtonText (T("4P"));
    osc4SelectPhase->setConnectedEdges (Button::ConnectedOnRight | Button::ConnectedOnTop);
    osc4SelectPhase->addButtonListener (this);
    osc4SelectPhase->setColour (TextButton::buttonColourId, Colour (0xff805f8b));

    addAndMakeVisible (eqBw1Slider = new ParameterSlider (String::empty));
    eqBw1Slider->setTooltip (T("Eq 1 Q"));
    eqBw1Slider->setRange (0, 1, 0.0001);
    eqBw1Slider->setSliderStyle (Slider::RotaryVerticalDrag);
    eqBw1Slider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    eqBw1Slider->setColour (Slider::thumbColourId, Colour (0xff47596b));
    eqBw1Slider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    eqBw1Slider->addListener (this);

    addAndMakeVisible (eqBw4Slider = new ParameterSlider (String::empty));
    eqBw4Slider->setTooltip (T("Eq 4 Q"));
    eqBw4Slider->setRange (0, 1, 0.0001);
    eqBw4Slider->setSliderStyle (Slider::RotaryVerticalDrag);
    eqBw4Slider->setTextBoxStyle (Slider::NoTextBox, false, 30, 18);
    eqBw4Slider->setColour (Slider::thumbColourId, Colour (0xff47596b));
    eqBw4Slider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    eqBw4Slider->addListener (this);

    addAndMakeVisible (filterLfoLabel = new Label (String::empty,
                                                   T("lfoA   lfoF   lfoR")));
    filterLfoLabel->setFont (Font (15.0000f, Font::plain));
    filterLfoLabel->setJustificationType (Justification::centredLeft);
    filterLfoLabel->setEditable (false, false, false);
    filterLfoLabel->setColour (Label::backgroundColourId, Colour (0x0));
    filterLfoLabel->setColour (Label::textColourId, Colours::black);
    filterLfoLabel->setColour (Label::outlineColourId, Colour (0x0));
    filterLfoLabel->setColour (TextEditor::textColourId, Colours::black);
    filterLfoLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (filterTypeBox = new ComboBox (String::empty));
    filterTypeBox->setEditableText (false);
    filterTypeBox->setJustificationType (Justification::centredLeft);
    filterTypeBox->setTextWhenNothingSelected (String::empty);
    filterTypeBox->setTextWhenNoChoicesAvailable (String::empty);
    filterTypeBox->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (680, 400);

    //[Constructor] You can add your own custom stuff here..
    partNumber = -1;
    setPartNumber (0);
    setOscillatorNumber (0);

    // filter ? mh
    filterTypeBox->addItem (T("Lowpass"), 1);
    filterTypeBox->addItem (T("Hipass"), 2);
    filterTypeBox->addItem (T("Bandpass"), 3);
    filterTypeBox->addItem (T("Notch"), 4);

    // TODO
    stereoButton->setEnabled (false);
    partKeyboardSlider->setEnabled (false);

    // joystick
    joystick->setBackgroundColour (Colours::black);
    joystick->setInsetColours (Colour (0xff827474).brighter (0.5f),
                               Colour (0xff827474).darker (0.5f));
    joystick->addListener (this);
    joystick->setRanges (0.0, 1.0,
                         0.0, 1.0,
                         0.0001);

    partials->setLinkedComponent (scope);
    //[/Constructor]
}

XSynthPatch::~XSynthPatch()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    setPartNumber (-1);
    //[/Destructor_pre]

    deleteAndZero (osc1Select);
    deleteAndZero (osc2Select);
    deleteAndZero (osc3Select);
    deleteAndZero (osc4Select);
    deleteAndZero (chorusGroup);
    deleteAndZero (toneGroup);
    deleteAndZero (filterGroup);
    deleteAndZero (ampGroup);
    deleteAndZero (partials);
    deleteAndZero (scope);
    deleteAndZero (ampAttackSlider);
    deleteAndZero (ampDecaySlider);
    deleteAndZero (ampSustainSlider);
    deleteAndZero (ampReleaseSlider);
    deleteAndZero (filterCutoffSlider);
    deleteAndZero (filterResoSlider);
    deleteAndZero (filterTrackingSlider);
    deleteAndZero (ampAdsrLabel);
    deleteAndZero (filterLabel);
    deleteAndZero (driveGroup);
    deleteAndZero (eqGroup);
    deleteAndZero (delayGroup);
    deleteAndZero (destructDriveSlider);
    deleteAndZero (destructLowpassSlider);
    deleteAndZero (toneAttackValueSlider);
    deleteAndZero (toneAttackSlider);
    deleteAndZero (toneDecayValueSlider);
    deleteAndZero (toneDecaySlider);
    deleteAndZero (toneMasterSlider);
    deleteAndZero (toneDetuneSlider);
    deleteAndZero (toneAdsrLabel);
    deleteAndZero (masterGroup);
    deleteAndZero (masterGainSlider);
    deleteAndZero (enableButton);
    deleteAndZero (partNumberSlider);
    deleteAndZero (destructHighpassSlider);
    deleteAndZero (driveLabel);
    deleteAndZero (masterPanSlider);
    deleteAndZero (filterAttackValueSlider);
    deleteAndZero (filterAttackTimeSlider);
    deleteAndZero (filterDecayValueSlider);
    deleteAndZero (filterDecayTimeSlider);
    deleteAndZero (filterEnvelopeLabel);
    deleteAndZero (partKeyboardSlider);
    deleteAndZero (portaButton);
    deleteAndZero (polyButton);
    deleteAndZero (masterLabel);
    deleteAndZero (stereoButton);
    deleteAndZero (chorusFreqSlider);
    deleteAndZero (chorusDelaySlider);
    deleteAndZero (chorusDepthSlider);
    deleteAndZero (chorusFeedbackSlider);
    deleteAndZero (chorusGainSlider);
    deleteAndZero (chorusLabel);
    deleteAndZero (eqgraph);
    deleteAndZero (eqFreq1Slider);
    deleteAndZero (eqGain1Slider);
    deleteAndZero (eqFreq2Slider);
    deleteAndZero (eqGain2Slider);
    deleteAndZero (eqFreq3Slider);
    deleteAndZero (eqGain3Slider);
    deleteAndZero (filterLfoDepthSlider);
    deleteAndZero (filterLfoFrequencySlider);
    deleteAndZero (filterLfoRandomSlider);
    deleteAndZero (toneReleaseValueSlider);
    deleteAndZero (toneReleaseSlider);
    deleteAndZero (eqBw2Slider);
    deleteAndZero (eqBw3Slider);
    deleteAndZero (eqFreq4Slider);
    deleteAndZero (eqGain4Slider);
    deleteAndZero (eq1Label);
    deleteAndZero (eq2Label);
    deleteAndZero (delayVolumeSlider);
    deleteAndZero (delayTimeSlider);
    deleteAndZero (delayFeedbackSlider);
    deleteAndZero (delayPanSlider);
    deleteAndZero (delayFilterSlider);
    deleteAndZero (echoLabel);
    deleteAndZero (ampEnvelope);
    deleteAndZero (joystick);
    deleteAndZero (noiseGroup);
    deleteAndZero (noiseGainSlider);
    deleteAndZero (noiseLabel);
    deleteAndZero (pitchEnvelope);
    deleteAndZero (osc1SelectPhase);
    deleteAndZero (osc2SelectPhase);
    deleteAndZero (osc3SelectPhase);
    deleteAndZero (osc4SelectPhase);
    deleteAndZero (eqBw1Slider);
    deleteAndZero (eqBw4Slider);
    deleteAndZero (filterLfoLabel);
    deleteAndZero (filterTypeBox);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void XSynthPatch::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff827474));

    g.setGradientFill (ColourGradient (Colour (0xff827474),
                                       330.0f, 390.0f,
                                       Colours::black,
                                       330.0f, 410.0f,
                                       false));
    g.fillRect (0, 370, 680, 30);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void XSynthPatch::resized()
{
    osc1Select->setBounds (269, 14, 18, 18);
    osc2Select->setBounds (269, 43, 18, 18);
    osc3Select->setBounds (269, 71, 18, 18);
    osc4Select->setBounds (269, 99, 18, 18);
    chorusGroup->setBounds (203, 263, 80, 126);
    toneGroup->setBounds (284, 135, 345, 126);
    filterGroup->setBounds (3, 263, 199, 126);
    ampGroup->setBounds (3, 135, 280, 126);
    partials->setBounds (287, 14, 266, 115);
    scope->setBounds (558, 14, 115, 115);
    ampAttackSlider->setBounds (13, 150, 10, 90);
    ampDecaySlider->setBounds (25, 150, 10, 90);
    ampSustainSlider->setBounds (37, 150, 10, 90);
    ampReleaseSlider->setBounds (49, 150, 10, 90);
    filterCutoffSlider->setBounds (13, 278, 10, 90);
    filterResoSlider->setBounds (25, 278, 10, 90);
    filterTrackingSlider->setBounds (37, 278, 10, 90);
    ampAdsrLabel->setBounds (11, 240, 50, 11);
    filterLabel->setBounds (10, 368, 39, 11);
    driveGroup->setBounds (284, 263, 61, 126);
    eqGroup->setBounds (346, 263, 251, 126);
    delayGroup->setBounds (598, 263, 77, 126);
    destructDriveSlider->setBounds (297, 278, 10, 90);
    destructLowpassSlider->setBounds (309, 278, 10, 90);
    toneAttackValueSlider->setBounds (329, 150, 10, 90);
    toneAttackSlider->setBounds (341, 150, 10, 90);
    toneDecayValueSlider->setBounds (353, 150, 10, 90);
    toneDecaySlider->setBounds (365, 150, 10, 90);
    toneMasterSlider->setBounds (294, 150, 10, 90);
    toneDetuneSlider->setBounds (306, 150, 10, 90);
    toneAdsrLabel->setBounds (294, 240, 109, 11);
    masterGroup->setBounds (3, 5, 144, 126);
    masterGainSlider->setBounds (13, 20, 10, 90);
    enableButton->setBounds (38, 39, 49, 17);
    partNumberSlider->setBounds (41, 25, 50, 12);
    destructHighpassSlider->setBounds (321, 278, 10, 90);
    driveLabel->setBounds (294, 367, 42, 13);
    masterPanSlider->setBounds (25, 20, 10, 90);
    filterAttackValueSlider->setBounds (146, 278, 10, 90);
    filterAttackTimeSlider->setBounds (158, 278, 10, 90);
    filterDecayValueSlider->setBounds (170, 278, 10, 90);
    filterDecayTimeSlider->setBounds (182, 278, 10, 90);
    filterEnvelopeLabel->setBounds (143, 368, 53, 11);
    partKeyboardSlider->setBounds (40, 98, 98, 10);
    portaButton->setBounds (38, 52, 49, 17);
    polyButton->setBounds (38, 65, 49, 17);
    masterLabel->setBounds (11, 112, 119, 11);
    stereoButton->setBounds (38, 78, 49, 17);
    chorusFreqSlider->setBounds (226, 278, 10, 90);
    chorusDelaySlider->setBounds (238, 278, 10, 90);
    chorusDepthSlider->setBounds (250, 278, 10, 90);
    chorusFeedbackSlider->setBounds (262, 278, 10, 90);
    chorusGainSlider->setBounds (214, 278, 10, 90);
    chorusLabel->setBounds (211, 367, 65, 13);
    eqgraph->setBounds (434, 282, 152, 97);
    eqFreq1Slider->setBounds (387, 280, 22, 22);
    eqGain1Slider->setBounds (365, 280, 22, 22);
    eqFreq2Slider->setBounds (387, 303, 22, 22);
    eqGain2Slider->setBounds (365, 303, 22, 22);
    eqFreq3Slider->setBounds (387, 326, 22, 22);
    eqGain3Slider->setBounds (365, 326, 22, 22);
    filterLfoDepthSlider->setBounds (52, 302, 25, 25);
    filterLfoFrequencySlider->setBounds (84, 302, 26, 25);
    filterLfoRandomSlider->setBounds (117, 302, 27, 25);
    toneReleaseValueSlider->setBounds (377, 150, 10, 90);
    toneReleaseSlider->setBounds (389, 150, 10, 90);
    eqBw2Slider->setBounds (409, 303, 22, 22);
    eqBw3Slider->setBounds (409, 326, 22, 22);
    eqFreq4Slider->setBounds (387, 348, 22, 22);
    eqGain4Slider->setBounds (365, 348, 22, 22);
    eq1Label->setBounds (354, 278, 9, 95);
    eq2Label->setBounds (370, 370, 56, 11);
    delayVolumeSlider->setBounds (607, 278, 10, 90);
    delayTimeSlider->setBounds (631, 278, 10, 90);
    delayFeedbackSlider->setBounds (643, 278, 10, 90);
    delayPanSlider->setBounds (619, 278, 10, 90);
    delayFilterSlider->setBounds (655, 278, 10, 90);
    echoLabel->setBounds (604, 370, 65, 12);
    ampEnvelope->setBounds (66, 154, 207, 97);
    joystick->setBounds (149, 14, 115, 115);
    noiseGroup->setBounds (630, 135, 45, 126);
    noiseGainSlider->setBounds (647, 150, 10, 90);
    noiseLabel->setBounds (638, 240, 29, 11);
    pitchEnvelope->setBounds (409, 154, 210, 97);
    osc1SelectPhase->setBounds (269, 31, 18, 13);
    osc2SelectPhase->setBounds (269, 59, 18, 13);
    osc3SelectPhase->setBounds (269, 88, 18, 13);
    osc4SelectPhase->setBounds (269, 116, 18, 13);
    eqBw1Slider->setBounds (409, 280, 22, 22);
    eqBw4Slider->setBounds (409, 348, 22, 22);
    filterLfoLabel->setBounds (50, 328, 94, 11);
    filterTypeBox->setBounds (52, 285, 89, 15);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void XSynthPatch::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == osc1Select)
    {
        //[UserButtonCode_osc1Select] -- add your button handler code here..
        setOscillatorNumber (0, true);
        //[/UserButtonCode_osc1Select]
    }
    else if (buttonThatWasClicked == osc2Select)
    {
        //[UserButtonCode_osc2Select] -- add your button handler code here..
        setOscillatorNumber (1, true);
        //[/UserButtonCode_osc2Select]
    }
    else if (buttonThatWasClicked == osc3Select)
    {
        //[UserButtonCode_osc3Select] -- add your button handler code here..
        setOscillatorNumber (2, true);
        //[/UserButtonCode_osc3Select]
    }
    else if (buttonThatWasClicked == osc4Select)
    {
        //[UserButtonCode_osc4Select] -- add your button handler code here..
        setOscillatorNumber (3, true);
        //[/UserButtonCode_osc4Select]
    }
    else if (buttonThatWasClicked == enableButton)
    {
        //[UserButtonCode_enableButton] -- add your button handler code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_ENABLED), (float) buttonThatWasClicked->getToggleState());
        //[/UserButtonCode_enableButton]
    }
    else if (buttonThatWasClicked == portaButton)
    {
        //[UserButtonCode_portaButton] -- add your button handler code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_PORTA), (float) buttonThatWasClicked->getToggleState());
        //[/UserButtonCode_portaButton]
    }
    else if (buttonThatWasClicked == polyButton)
    {
        //[UserButtonCode_polyButton] -- add your button handler code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_POLY), (float) buttonThatWasClicked->getToggleState());
        //[/UserButtonCode_polyButton]
    }
    else if (buttonThatWasClicked == stereoButton)
    {
        //[UserButtonCode_stereoButton] -- add your button handler code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_STEREO), (float) buttonThatWasClicked->getToggleState());
        masterPanSlider->setEnabled (buttonThatWasClicked->getToggleState());
        //[/UserButtonCode_stereoButton]
    }
    else if (buttonThatWasClicked == osc1SelectPhase)
    {
        //[UserButtonCode_osc1SelectPhase] -- add your button handler code here..
        setOscillatorNumber (0, false);
        //[/UserButtonCode_osc1SelectPhase]
    }
    else if (buttonThatWasClicked == osc2SelectPhase)
    {
        //[UserButtonCode_osc2SelectPhase] -- add your button handler code here..
        setOscillatorNumber (1, false);
        //[/UserButtonCode_osc2SelectPhase]
    }
    else if (buttonThatWasClicked == osc3SelectPhase)
    {
        //[UserButtonCode_osc3SelectPhase] -- add your button handler code here..
        setOscillatorNumber (2, false);
        //[/UserButtonCode_osc3SelectPhase]
    }
    else if (buttonThatWasClicked == osc4SelectPhase)
    {
        //[UserButtonCode_osc4SelectPhase] -- add your button handler code here..
        setOscillatorNumber (3, false);
        //[/UserButtonCode_osc4SelectPhase]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void XSynthPatch::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == ampAttackSlider)
    {
        //[UserSliderCode_ampAttackSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_AMP_ATTACK), sliderThatWasMoved->getValue());
        ampEnvelope->repaint ();
        //[/UserSliderCode_ampAttackSlider]
    }
    else if (sliderThatWasMoved == ampDecaySlider)
    {
        //[UserSliderCode_ampDecaySlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_AMP_DECAY), sliderThatWasMoved->getValue());
        ampEnvelope->repaint ();
        //[/UserSliderCode_ampDecaySlider]
    }
    else if (sliderThatWasMoved == ampSustainSlider)
    {
        //[UserSliderCode_ampSustainSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_AMP_SUSTAIN), sliderThatWasMoved->getValue());
        ampEnvelope->repaint ();
        //[/UserSliderCode_ampSustainSlider]
    }
    else if (sliderThatWasMoved == ampReleaseSlider)
    {
        //[UserSliderCode_ampReleaseSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_AMP_RELEASE), sliderThatWasMoved->getValue());
        ampEnvelope->repaint ();
        //[/UserSliderCode_ampReleaseSlider]
    }
    else if (sliderThatWasMoved == filterCutoffSlider)
    {
        //[UserSliderCode_filterCutoffSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_FILTERCUTOFF), sliderThatWasMoved->getValue());
        //[/UserSliderCode_filterCutoffSlider]
    }
    else if (sliderThatWasMoved == filterResoSlider)
    {
        //[UserSliderCode_filterResoSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_FILTERRESO), sliderThatWasMoved->getValue());
        //[/UserSliderCode_filterResoSlider]
    }
    else if (sliderThatWasMoved == filterTrackingSlider)
    {
        //[UserSliderCode_filterTrackingSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_FILTERTRACK), sliderThatWasMoved->getValue());
        //[/UserSliderCode_filterTrackingSlider]
    }
    else if (sliderThatWasMoved == destructDriveSlider)
    {
        //[UserSliderCode_destructDriveSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_DRIVE_AMOUNT), sliderThatWasMoved->getValue());
        //[/UserSliderCode_destructDriveSlider]
    }
    else if (sliderThatWasMoved == destructLowpassSlider)
    {
        //[UserSliderCode_destructLowpassSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_DRIVE_LP), sliderThatWasMoved->getValue());
        //[/UserSliderCode_destructLowpassSlider]
    }
    else if (sliderThatWasMoved == toneAttackValueSlider)
    {
        //[UserSliderCode_toneAttackValueSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_TONE_ATTACK), sliderThatWasMoved->getValue());
        pitchEnvelope->repaint ();
        //[/UserSliderCode_toneAttackValueSlider]
    }
    else if (sliderThatWasMoved == toneAttackSlider)
    {
        //[UserSliderCode_toneAttackSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_TONE_ATTACKTIME), sliderThatWasMoved->getValue());
        pitchEnvelope->repaint ();
        //[/UserSliderCode_toneAttackSlider]
    }
    else if (sliderThatWasMoved == toneDecayValueSlider)
    {
        //[UserSliderCode_toneDecayValueSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_TONE_DECAY), sliderThatWasMoved->getValue());
        pitchEnvelope->repaint ();
        //[/UserSliderCode_toneDecayValueSlider]
    }
    else if (sliderThatWasMoved == toneDecaySlider)
    {
        //[UserSliderCode_toneDecaySlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_TONE_DECAYTIME), sliderThatWasMoved->getValue());
        pitchEnvelope->repaint ();
        //[/UserSliderCode_toneDecaySlider]
    }
    else if (sliderThatWasMoved == toneMasterSlider)
    {
        //[UserSliderCode_toneMasterSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_TONE), sliderThatWasMoved->getValue());
        //[/UserSliderCode_toneMasterSlider]
    }
    else if (sliderThatWasMoved == toneDetuneSlider)
    {
        //[UserSliderCode_toneDetuneSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_FINETUNE), sliderThatWasMoved->getValue());
        //[/UserSliderCode_toneDetuneSlider]
    }
    else if (sliderThatWasMoved == masterGainSlider)
    {
        //[UserSliderCode_masterGainSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_GAIN), sliderThatWasMoved->getValue());
        //[/UserSliderCode_masterGainSlider]
    }
    else if (sliderThatWasMoved == partNumberSlider)
    {
        //[UserSliderCode_partNumberSlider] -- add your slider handling code here..
        setPartNumber ((int) (sliderThatWasMoved->getValue () - 1.0f));
        updateControls ();
        //[/UserSliderCode_partNumberSlider]
    }
    else if (sliderThatWasMoved == destructHighpassSlider)
    {
        //[UserSliderCode_destructHighpassSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_DRIVE_HP), sliderThatWasMoved->getValue());
        //[/UserSliderCode_destructHighpassSlider]
    }
    else if (sliderThatWasMoved == masterPanSlider)
    {
        //[UserSliderCode_masterPanSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_PAN), sliderThatWasMoved->getValue());
        //[/UserSliderCode_masterPanSlider]
    }
    else if (sliderThatWasMoved == filterAttackValueSlider)
    {
        //[UserSliderCode_filterAttackValueSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_FILTER_ATTACK), sliderThatWasMoved->getValue());
        //[/UserSliderCode_filterAttackValueSlider]
    }
    else if (sliderThatWasMoved == filterAttackTimeSlider)
    {
        //[UserSliderCode_filterAttackTimeSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_FILTER_ATTACKTIME), sliderThatWasMoved->getValue());
        //[/UserSliderCode_filterAttackTimeSlider]
    }
    else if (sliderThatWasMoved == filterDecayValueSlider)
    {
        //[UserSliderCode_filterDecayValueSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_FILTER_DECAY), sliderThatWasMoved->getValue());
        //[/UserSliderCode_filterDecayValueSlider]
    }
    else if (sliderThatWasMoved == filterDecayTimeSlider)
    {
        //[UserSliderCode_filterDecayTimeSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_FILTER_DECAYTIME), sliderThatWasMoved->getValue());
        //[/UserSliderCode_filterDecayTimeSlider]
    }
    else if (sliderThatWasMoved == partKeyboardSlider)
    {
        //[UserSliderCode_partKeyboardSlider] -- add your slider handling code here..
        /* TODO
        int minKey = (int)(sliderThatWasMoved->getMaxValue() * 127);
        int maxKey = (int)(sliderThatWasMoved->getMinValue() * 127);
        if (minKey > maxKey) swapVariables (minKey, maxKey);
        else if (minKey == maxKey)
        {
            if (maxKey == 127) minKey--;
            else maxKey++;
        }
        master->part[partNumber]->Pminkey = minKey;
        master->part[partNumber]->Pmaxkey = maxKey;
        */
        //[/UserSliderCode_partKeyboardSlider]
    }
    else if (sliderThatWasMoved == chorusFreqSlider)
    {
        //[UserSliderCode_chorusFreqSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_CHORUS_FREQ), sliderThatWasMoved->getValue());
        //[/UserSliderCode_chorusFreqSlider]
    }
    else if (sliderThatWasMoved == chorusDelaySlider)
    {
        //[UserSliderCode_chorusDelaySlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_CHORUS_DELAY), sliderThatWasMoved->getValue());
        //[/UserSliderCode_chorusDelaySlider]
    }
    else if (sliderThatWasMoved == chorusDepthSlider)
    {
        //[UserSliderCode_chorusDepthSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_CHORUS_DEPTH), sliderThatWasMoved->getValue());
        //[/UserSliderCode_chorusDepthSlider]
    }
    else if (sliderThatWasMoved == chorusFeedbackSlider)
    {
        //[UserSliderCode_chorusFeedbackSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_CHORUS_FEEDBACK), sliderThatWasMoved->getValue());
        //[/UserSliderCode_chorusFeedbackSlider]
    }
    else if (sliderThatWasMoved == chorusGainSlider)
    {
        //[UserSliderCode_chorusGainSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_CHORUS_GAIN), sliderThatWasMoved->getValue());
        //[/UserSliderCode_chorusGainSlider]
    }
    else if (sliderThatWasMoved == eqFreq1Slider)
    {
        //[UserSliderCode_eqFreq1Slider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_EQ_LS_F), sliderThatWasMoved->getValue());
        eqgraph->repaint ();
        //[/UserSliderCode_eqFreq1Slider]
    }
    else if (sliderThatWasMoved == eqGain1Slider)
    {
        //[UserSliderCode_eqGain1Slider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_EQ_LS_G), sliderThatWasMoved->getValue());
        eqgraph->repaint ();
        //[/UserSliderCode_eqGain1Slider]
    }
    else if (sliderThatWasMoved == eqFreq2Slider)
    {
        //[UserSliderCode_eqFreq2Slider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_EQ_PK0_F), sliderThatWasMoved->getValue());
        eqgraph->repaint ();
        //[/UserSliderCode_eqFreq2Slider]
    }
    else if (sliderThatWasMoved == eqGain2Slider)
    {
        //[UserSliderCode_eqGain2Slider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_EQ_PK0_G), sliderThatWasMoved->getValue());
        eqgraph->repaint ();
        //[/UserSliderCode_eqGain2Slider]
    }
    else if (sliderThatWasMoved == eqFreq3Slider)
    {
        //[UserSliderCode_eqFreq3Slider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_EQ_PK1_F), sliderThatWasMoved->getValue());
        eqgraph->repaint ();
        //[/UserSliderCode_eqFreq3Slider]
    }
    else if (sliderThatWasMoved == eqGain3Slider)
    {
        //[UserSliderCode_eqGain3Slider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_EQ_PK1_G), sliderThatWasMoved->getValue());
        eqgraph->repaint ();
        //[/UserSliderCode_eqGain3Slider]
    }
    else if (sliderThatWasMoved == filterLfoDepthSlider)
    {
        //[UserSliderCode_filterLfoDepthSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_FILTER_LFODEPTH), sliderThatWasMoved->getValue());
        //[/UserSliderCode_filterLfoDepthSlider]
    }
    else if (sliderThatWasMoved == filterLfoFrequencySlider)
    {
        //[UserSliderCode_filterLfoFrequencySlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_FILTER_LFOFREQ), sliderThatWasMoved->getValue());
        //[/UserSliderCode_filterLfoFrequencySlider]
    }
    else if (sliderThatWasMoved == filterLfoRandomSlider)
    {
        //[UserSliderCode_filterLfoRandomSlider] -- add your slider handling code here..
//        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_FILTER_LFORANDOM), sliderThatWasMoved->getValue());
        //[/UserSliderCode_filterLfoRandomSlider]
    }
    else if (sliderThatWasMoved == toneReleaseValueSlider)
    {
        //[UserSliderCode_toneReleaseValueSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_TONE_RELEASE), sliderThatWasMoved->getValue());
        pitchEnvelope->repaint ();
        //[/UserSliderCode_toneReleaseValueSlider]
    }
    else if (sliderThatWasMoved == toneReleaseSlider)
    {
        //[UserSliderCode_toneReleaseSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_TONE_RELEASETIME), sliderThatWasMoved->getValue());
        pitchEnvelope->repaint ();
        //[/UserSliderCode_toneReleaseSlider]
    }
    else if (sliderThatWasMoved == eqBw2Slider)
    {
        //[UserSliderCode_eqBw2Slider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_EQ_PK0_BW), sliderThatWasMoved->getValue());
        eqgraph->repaint ();
        //[/UserSliderCode_eqBw2Slider]
    }
    else if (sliderThatWasMoved == eqBw3Slider)
    {
        //[UserSliderCode_eqBw3Slider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_EQ_PK1_BW), sliderThatWasMoved->getValue());
        eqgraph->repaint ();
        //[/UserSliderCode_eqBw3Slider]
    }
    else if (sliderThatWasMoved == eqFreq4Slider)
    {
        //[UserSliderCode_eqFreq4Slider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_EQ_HS_F), sliderThatWasMoved->getValue());
        eqgraph->repaint ();
        //[/UserSliderCode_eqFreq4Slider]
    }
    else if (sliderThatWasMoved == eqGain4Slider)
    {
        //[UserSliderCode_eqGain4Slider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_EQ_HS_G), sliderThatWasMoved->getValue());
        eqgraph->repaint ();
        //[/UserSliderCode_eqGain4Slider]
    }
    else if (sliderThatWasMoved == delayVolumeSlider)
    {
        //[UserSliderCode_delayVolumeSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_DELAY_GAIN), sliderThatWasMoved->getValue());
        //[/UserSliderCode_delayVolumeSlider]
    }
    else if (sliderThatWasMoved == delayTimeSlider)
    {
        //[UserSliderCode_delayTimeSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_DELAY_TIME), sliderThatWasMoved->getValue());
        //[/UserSliderCode_delayTimeSlider]
    }
    else if (sliderThatWasMoved == delayFeedbackSlider)
    {
        //[UserSliderCode_delayFeedbackSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_DELAY_FEED), sliderThatWasMoved->getValue());
        //[/UserSliderCode_delayFeedbackSlider]
    }
    else if (sliderThatWasMoved == delayPanSlider)
    {
        //[UserSliderCode_delayPanSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_DELAY_PAN), sliderThatWasMoved->getValue());
        //[/UserSliderCode_delayPanSlider]
    }
    else if (sliderThatWasMoved == delayFilterSlider)
    {
        //[UserSliderCode_delayFilterSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_DELAY_LP), sliderThatWasMoved->getValue());
        //[/UserSliderCode_delayFilterSlider]
    }
    else if (sliderThatWasMoved == noiseGainSlider)
    {
        //[UserSliderCode_noiseGainSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_NOISE), sliderThatWasMoved->getValue());
        //[/UserSliderCode_noiseGainSlider]
    }
    else if (sliderThatWasMoved == eqBw1Slider)
    {
        //[UserSliderCode_eqBw1Slider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_EQ_LS_BW), sliderThatWasMoved->getValue());
        eqgraph->repaint ();
        //[/UserSliderCode_eqBw1Slider]
    }
    else if (sliderThatWasMoved == eqBw4Slider)
    {
        //[UserSliderCode_eqBw4Slider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_EQ_HS_BW), sliderThatWasMoved->getValue());
        eqgraph->repaint ();
        //[/UserSliderCode_eqBw4Slider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void XSynthPatch::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == filterTypeBox)
    {
        //[UserComboBoxCode_filterTypeBox] -- add your combo box handling code here..
        float newType = (comboBoxThatHasChanged->getSelectedId() - 1.0f) / 8.0f /*(float) comboBoxThatHasChanged->getNumItems ()*/;
        plugin->setParameterNotifyingHost (PPAR(partNumber,PP_FILTERTYPE), newType);

        // master->part[partNumber]->kit[0].adpars->GlobalPar.GlobalFilter->Ptype = ;
        //[/UserComboBoxCode_filterTypeBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void XSynthPatch::setPartNumber (const int newPartNumber)
{
    if (partNumber == newPartNumber)
        return;

    if (partNumber >= 0 && partNumber < 16)
    {
        // remove controls listeners
        plugin->getParameterLock().enter ();
        plugin->removeListenerToParameter (PPAR(partNumber,PP_GAIN), masterGainSlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_PAN), masterPanSlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_ENABLED), enableButton);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_PORTA), portaButton);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_POLY), polyButton);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_STEREO), stereoButton);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_X), joystick);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_Y), joystick);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_AMP_ATTACK), ampAttackSlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_AMP_DECAY), ampDecaySlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_AMP_SUSTAIN), ampSustainSlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_AMP_RELEASE), ampReleaseSlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_TONE_ATTACK), toneAttackValueSlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_TONE_ATTACKTIME), toneAttackSlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_TONE_DECAY), toneDecayValueSlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_TONE_DECAYTIME), toneDecaySlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_TONE_RELEASE), toneReleaseValueSlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_TONE_RELEASETIME), toneReleaseSlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_TONE), toneMasterSlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_FINETUNE), toneDetuneSlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_NOISE), noiseGainSlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_FILTERCUTOFF), filterCutoffSlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_FILTERRESO), filterResoSlider);
        // TODO plugin->removeListenerToParameter (PPAR(partNumber,PP_FILTERTYPE), noiseGainSlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_FILTERTRACK), filterTrackingSlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_FILTER_LFODEPTH), filterLfoDepthSlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_FILTER_LFOFREQ), filterLfoFrequencySlider);
//        plugin->removeListenerToParameter (PPAR(partNumber,PP_FILTER_LFORANDOM), filterLfoRandomSlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_FILTER_ATTACK), filterAttackValueSlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_FILTER_ATTACKTIME), filterAttackTimeSlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_FILTER_DECAY), filterDecayValueSlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_FILTER_DECAYTIME), filterDecayTimeSlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_CHORUS_GAIN), chorusGainSlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_CHORUS_FREQ), chorusFreqSlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_CHORUS_DELAY), chorusDelaySlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_CHORUS_DEPTH), chorusDepthSlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_CHORUS_FEEDBACK), chorusFeedbackSlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_DRIVE_AMOUNT), destructDriveSlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_DRIVE_LP), destructLowpassSlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_DRIVE_HP), destructHighpassSlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_EQ_LS_F), eqFreq1Slider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_EQ_LS_G), eqGain1Slider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_EQ_LS_BW), eqBw1Slider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_EQ_PK0_F), eqFreq2Slider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_EQ_PK0_G), eqGain2Slider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_EQ_PK0_BW), eqBw2Slider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_EQ_PK1_F), eqFreq3Slider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_EQ_PK1_G), eqGain3Slider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_EQ_PK1_BW), eqBw3Slider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_EQ_HS_F), eqFreq4Slider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_EQ_HS_G), eqGain4Slider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_EQ_HS_BW), eqBw4Slider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_EQ_LS_G), eqgraph);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_EQ_LS_F), eqgraph);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_EQ_PK0_G), eqgraph);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_EQ_PK0_F), eqgraph);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_EQ_PK0_BW), eqgraph);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_EQ_PK1_G), eqgraph);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_EQ_PK1_F), eqgraph);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_EQ_PK1_BW), eqgraph);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_EQ_HS_G), eqgraph);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_EQ_HS_F), eqgraph);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_DELAY_GAIN), delayVolumeSlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_DELAY_PAN), delayPanSlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_DELAY_TIME), delayTimeSlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_DELAY_FEED), delayFeedbackSlider);
        plugin->removeListenerToParameter (PPAR(partNumber,PP_DELAY_LP), delayFilterSlider);
        plugin->getParameterLock().exit ();
    }


    // add new controls listeners
    if (newPartNumber >= 0 && newPartNumber < 16)
    {
        // update part number
        partNumber = jmax (0, jmin (newPartNumber, 15));

        plugin->getParameterLock().enter ();
        plugin->addListenerToParameter (PPAR(partNumber,PP_GAIN), masterGainSlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_PAN), masterPanSlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_ENABLED), enableButton);
        plugin->addListenerToParameter (PPAR(partNumber,PP_PORTA), portaButton);
        plugin->addListenerToParameter (PPAR(partNumber,PP_POLY), polyButton);
        plugin->addListenerToParameter (PPAR(partNumber,PP_STEREO), stereoButton);
        plugin->addListenerToParameter (PPAR(partNumber,PP_X), joystick);
        plugin->addListenerToParameter (PPAR(partNumber,PP_Y), joystick);
            joystick->setIndexForValues (PPAR(partNumber,PP_X), PPAR(partNumber,PP_Y));
        plugin->addListenerToParameter (PPAR(partNumber,PP_AMP_ATTACK), ampAttackSlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_AMP_DECAY), ampDecaySlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_AMP_SUSTAIN), ampSustainSlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_AMP_RELEASE), ampReleaseSlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_TONE_ATTACK), toneAttackValueSlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_TONE_ATTACKTIME), toneAttackSlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_TONE_DECAY), toneDecayValueSlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_TONE_DECAYTIME), toneDecaySlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_TONE_RELEASE), toneReleaseValueSlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_TONE_RELEASETIME), toneReleaseSlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_TONE), toneMasterSlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_FINETUNE), toneDetuneSlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_NOISE), noiseGainSlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_FILTERCUTOFF), filterCutoffSlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_FILTERRESO), filterResoSlider);
        // TODO plugin->addListenerToParameter (PPAR(partNumber,PP_FILTERTYPE), noiseGainSlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_FILTERTRACK), filterTrackingSlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_FILTER_LFODEPTH), filterLfoDepthSlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_FILTER_LFOFREQ), filterLfoFrequencySlider);
//        plugin->addListenerToParameter (PPAR(partNumber,PP_FILTER_LFORANDOM), filterLfoRandomSlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_FILTER_ATTACK), filterAttackValueSlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_FILTER_ATTACKTIME), filterAttackTimeSlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_FILTER_DECAY), filterDecayValueSlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_FILTER_DECAYTIME), filterDecayTimeSlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_CHORUS_GAIN), chorusGainSlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_CHORUS_FREQ), chorusFreqSlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_CHORUS_DELAY), chorusDelaySlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_CHORUS_DEPTH), chorusDepthSlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_CHORUS_FEEDBACK), chorusFeedbackSlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_DRIVE_AMOUNT), destructDriveSlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_DRIVE_LP), destructLowpassSlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_DRIVE_HP), destructHighpassSlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_EQ_LS_F), eqFreq1Slider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_EQ_LS_G), eqGain1Slider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_EQ_LS_BW), eqBw1Slider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_EQ_PK0_F), eqFreq2Slider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_EQ_PK0_G), eqGain2Slider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_EQ_PK0_BW), eqBw2Slider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_EQ_PK1_F), eqFreq3Slider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_EQ_PK1_G), eqGain3Slider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_EQ_PK1_BW), eqBw3Slider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_EQ_HS_F), eqFreq4Slider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_EQ_HS_G), eqGain4Slider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_EQ_HS_BW), eqBw4Slider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_EQ_LS_G), eqgraph);
        plugin->addListenerToParameter (PPAR(partNumber,PP_EQ_LS_F), eqgraph);
        plugin->addListenerToParameter (PPAR(partNumber,PP_EQ_PK0_G), eqgraph);
        plugin->addListenerToParameter (PPAR(partNumber,PP_EQ_PK0_F), eqgraph);
        plugin->addListenerToParameter (PPAR(partNumber,PP_EQ_PK0_BW), eqgraph);
        plugin->addListenerToParameter (PPAR(partNumber,PP_EQ_PK1_G), eqgraph);
        plugin->addListenerToParameter (PPAR(partNumber,PP_EQ_PK1_F), eqgraph);
        plugin->addListenerToParameter (PPAR(partNumber,PP_EQ_PK1_BW), eqgraph);
        plugin->addListenerToParameter (PPAR(partNumber,PP_EQ_HS_G), eqgraph);
        plugin->addListenerToParameter (PPAR(partNumber,PP_EQ_HS_F), eqgraph);
        plugin->addListenerToParameter (PPAR(partNumber,PP_DELAY_GAIN), delayVolumeSlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_DELAY_PAN), delayPanSlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_DELAY_TIME), delayTimeSlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_DELAY_FEED), delayFeedbackSlider);
        plugin->addListenerToParameter (PPAR(partNumber,PP_DELAY_LP), delayFilterSlider);
        plugin->getParameterLock().exit ();
    }
}

void XSynthPatch::setOscillatorNumber (const int newOscNumber, const bool isMagnitude)
{
    // @TODO - (not good to have here)

    switch (oscNumber) {
        case 0: osc1Select->setColour (TextButton::buttonColourId, Colour (0xff827474));
                osc1SelectPhase->setColour (TextButton::buttonColourId, Colour (0xff805f8b)); break;
        case 1: osc2Select->setColour (TextButton::buttonColourId, Colour (0xff827474));
                osc2SelectPhase->setColour (TextButton::buttonColourId, Colour (0xff805f8b)); break;
        case 2: osc3Select->setColour (TextButton::buttonColourId, Colour (0xff827474));
                osc3SelectPhase->setColour (TextButton::buttonColourId, Colour (0xff805f8b)); break;
        case 3: osc4Select->setColour (TextButton::buttonColourId, Colour (0xff827474));
                osc4SelectPhase->setColour (TextButton::buttonColourId, Colour (0xff805f8b)); break;
    }

    oscNumber = jmax (0, jmin (newOscNumber, 3));

    switch (oscNumber) {
        case 0: if (isMagnitude) osc1Select->setColour (TextButton::buttonColourId, Colours::lightblue);
                else             osc1SelectPhase->setColour (TextButton::buttonColourId, Colours::violet); break;
        case 1: if (isMagnitude) osc2Select->setColour (TextButton::buttonColourId, Colours::lightblue);
                else             osc2SelectPhase->setColour (TextButton::buttonColourId, Colours::violet); break;
        case 2: if (isMagnitude) osc3Select->setColour (TextButton::buttonColourId, Colours::lightblue);
                else             osc3SelectPhase->setColour (TextButton::buttonColourId, Colours::violet); break;
        case 3: if (isMagnitude) osc4Select->setColour (TextButton::buttonColourId, Colours::lightblue);
                else             osc4SelectPhase->setColour (TextButton::buttonColourId, Colours::violet); break;
    }

    partials->setVisualMode (isMagnitude ? OscillatorPartials::MagnitudeMode : OscillatorPartials::PhaseMode);
    partials->setOscillator (master->part[partNumber]->kit[0].adpars->VoicePar[oscNumber].OscilSmp);
    scope->setOscillator (master->part[partNumber]->kit[0].adpars->VoicePar[oscNumber].OscilSmp);
    partials->repaint ();
    scope->repaint ();
}

void XSynthPatch::joystickValueChanged (Joystick* joystick)
{
    plugin->setParameterNotifyingHost (PPAR(partNumber,PP_X), joystick->getHorizontalValue ());
    plugin->setParameterNotifyingHost (PPAR(partNumber,PP_Y), joystick->getVerticalValue ());
}

void XSynthPatch::updateControls ()
{
    XSynthEditor* parent = findParentComponentOfClass <XSynthEditor> ();
    if (parent != 0)
        parent->setMidiChannel (master->part[partNumber]->Prcvchn + 1);

    enableButton->setToggleState ((int) plugin->getParameter (PPAR(partNumber, PP_ENABLED)), false);
    portaButton->setToggleState ((int) plugin->getParameter (PPAR(partNumber, PP_PORTA)), false);
    polyButton->setToggleState ((int) plugin->getParameter (PPAR(partNumber, PP_POLY)), false);
    stereoButton->setToggleState ((int) plugin->getParameter (PPAR(partNumber, PP_STEREO)), false);

    partNumberSlider->setValue ((float) (partNumber + 1), false);
    masterGainSlider->setValue (plugin->getParameter (PPAR(partNumber, PP_GAIN)), false);
    masterPanSlider->setValue (plugin->getParameter (PPAR(partNumber, PP_PAN)), false);
    masterPanSlider->setEnabled (stereoButton->getToggleState());

    partKeyboardSlider->setMinValue (master->part[partNumber]->Pminkey / 127.0f, false);
    partKeyboardSlider->setMaxValue (master->part[partNumber]->Pmaxkey / 127.0f, false);

    noiseGainSlider->setValue (plugin->getParameter (PPAR(partNumber, PP_NOISE)), false);

    ampAttackSlider->setValue (plugin->getParameter (PPAR(partNumber, PP_AMP_ATTACK)), false);
    ampDecaySlider->setValue (plugin->getParameter (PPAR(partNumber, PP_AMP_DECAY)), false);
    ampSustainSlider->setValue (plugin->getParameter (PPAR(partNumber, PP_AMP_SUSTAIN)), false);
    ampReleaseSlider->setValue (plugin->getParameter (PPAR(partNumber, PP_AMP_RELEASE)), false);

    toneAttackSlider->setValue (plugin->getParameter (PPAR(partNumber, PP_TONE_ATTACKTIME)), false);
    toneAttackValueSlider->setValue (plugin->getParameter (PPAR(partNumber, PP_TONE_ATTACK)), false);
    toneDecaySlider->setValue (plugin->getParameter (PPAR(partNumber, PP_TONE_DECAYTIME)), false);
    toneDecayValueSlider->setValue (plugin->getParameter (PPAR(partNumber, PP_TONE_DECAY)), false);
    toneReleaseSlider->setValue (plugin->getParameter (PPAR(partNumber, PP_TONE_RELEASETIME)), false);
    toneReleaseValueSlider->setValue (plugin->getParameter (PPAR(partNumber, PP_TONE_RELEASE)), false);
    toneMasterSlider->setValue (plugin->getParameter (PPAR(partNumber, PP_TONE)), false);
    toneDetuneSlider->setValue (plugin->getParameter (PPAR(partNumber, PP_FINETUNE)), false);
//    toneShiftSlider

    filterTypeBox->setSelectedId ((int) (plugin->getParameter (PPAR(partNumber, PP_FILTERTYPE)) * 8.0f) + 1);
    filterCutoffSlider->setValue (plugin->getParameter (PPAR(partNumber, PP_FILTERCUTOFF)), false);
    filterResoSlider->setValue (plugin->getParameter (PPAR(partNumber, PP_FILTERRESO)), false);
    filterTrackingSlider->setValue (plugin->getParameter (PPAR(partNumber, PP_FILTERTRACK)), false);
    filterAttackValueSlider->setValue (plugin->getParameter (PPAR(partNumber, PP_FILTER_ATTACK)), false);
    filterAttackTimeSlider->setValue (plugin->getParameter (PPAR(partNumber, PP_FILTER_ATTACKTIME)), false);
    filterDecayValueSlider->setValue (plugin->getParameter (PPAR(partNumber, PP_FILTER_DECAY)), false);
    filterDecayTimeSlider->setValue (plugin->getParameter (PPAR(partNumber, PP_FILTER_DECAYTIME)), false);
    filterLfoDepthSlider->setValue (plugin->getParameter (PPAR(partNumber, PP_FILTER_LFODEPTH)), false);
    filterLfoFrequencySlider->setValue (plugin->getParameter (PPAR(partNumber, PP_FILTER_LFOFREQ)), false);
//    filterLfoRandomSlider->setValue (plugin->getParameter (PPAR(partNumber, PP_FILTER_LFORANDOM)), false);

    chorusGainSlider->setValue (plugin->getParameter (PPAR(partNumber, PP_CHORUS_GAIN)), false);
    chorusFreqSlider->setValue (plugin->getParameter (PPAR(partNumber, PP_CHORUS_FREQ)), false);
    chorusDelaySlider->setValue (plugin->getParameter (PPAR(partNumber, PP_CHORUS_DELAY)), false);
    chorusDepthSlider->setValue (plugin->getParameter (PPAR(partNumber, PP_CHORUS_DEPTH)), false);
    chorusFeedbackSlider->setValue (plugin->getParameter (PPAR(partNumber, PP_CHORUS_FEEDBACK)), false);

    destructDriveSlider->setValue (plugin->getParameter (PPAR(partNumber, PP_DRIVE_AMOUNT)), false);
    destructLowpassSlider->setValue (plugin->getParameter (PPAR(partNumber, PP_DRIVE_LP)), false);
    destructHighpassSlider->setValue (plugin->getParameter (PPAR(partNumber, PP_DRIVE_HP)), false);

    eqFreq1Slider->setValue (plugin->getParameter (PPAR(partNumber, PP_EQ_LS_F)), false);
    eqGain1Slider->setValue (plugin->getParameter (PPAR(partNumber, PP_EQ_LS_G)), false);
    eqBw1Slider->setValue (plugin->getParameter (PPAR(partNumber, PP_EQ_LS_BW)), false);
    eqFreq2Slider->setValue (plugin->getParameter (PPAR(partNumber, PP_EQ_PK0_F)), false);
    eqGain2Slider->setValue (plugin->getParameter (PPAR(partNumber, PP_EQ_PK0_G)), false);
    eqBw2Slider->setValue (plugin->getParameter (PPAR(partNumber, PP_EQ_PK0_BW)), false);
    eqFreq3Slider->setValue (plugin->getParameter (PPAR(partNumber, PP_EQ_PK1_F)), false);
    eqGain3Slider->setValue (plugin->getParameter (PPAR(partNumber, PP_EQ_PK1_G)), false);
    eqBw3Slider->setValue (plugin->getParameter (PPAR(partNumber, PP_EQ_PK1_BW)), false);
    eqFreq4Slider->setValue (plugin->getParameter (PPAR(partNumber, PP_EQ_HS_F)), false);
    eqGain4Slider->setValue (plugin->getParameter (PPAR(partNumber, PP_EQ_HS_G)), false);
    eqBw4Slider->setValue (plugin->getParameter (PPAR(partNumber, PP_EQ_HS_BW)), false);

    delayVolumeSlider->setValue (plugin->getParameter (PPAR(partNumber, PP_DELAY_GAIN)), false);
    delayPanSlider->setValue (plugin->getParameter (PPAR(partNumber, PP_DELAY_PAN)), false);
    delayTimeSlider->setValue (plugin->getParameter (PPAR(partNumber, PP_DELAY_TIME)), false);
    delayFeedbackSlider->setValue (plugin->getParameter (PPAR(partNumber, PP_DELAY_FEED)), false);
    delayFilterSlider->setValue (plugin->getParameter (PPAR(partNumber, PP_DELAY_LP)), false);

    joystick->setValues (plugin->getParameter (PPAR(partNumber,PP_X)),
                         plugin->getParameter (PPAR(partNumber,PP_Y)), false);

    partials->setOscillator (master->part[partNumber]->kit[0].adpars->VoicePar[oscNumber].OscilSmp);
    scope->setOscillator (master->part[partNumber]->kit[0].adpars->VoicePar[oscNumber].OscilSmp);
    eqgraph->setEffectManager (master->part[partNumber]->partefx [2]);
    ampEnvelope->setEnvelope (master->part[partNumber]->kit[0].adpars->GlobalPar.AmpEnvelope, false);
    pitchEnvelope->setEnvelope (master->part[partNumber]->kit[0].adpars->GlobalPar.FreqEnvelope, true);

    joystick->repaint();
    partials->repaint ();
    scope->repaint ();
    eqgraph->repaint ();
    ampEnvelope->repaint ();
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="XSynthPatch" componentName=""
                 parentClasses="public Component, public JoystickListener" constructorParams="XSynthPlugin* plugin_, Master* master_"
                 variableInitialisers="plugin (plugin_)&#10;master (master_)" snapPixels="5"
                 snapActive="0" snapShown="0" overlayOpacity="0.330000013" fixedSize="1"
                 initialWidth="680" initialHeight="400">
  <BACKGROUND backgroundColour="ff827474">
    <RECT pos="0 370 680 30" fill="linear: 330 390, 330 410, 0=ff827474, 1=ff000000"
          hasStroke="0"/>
  </BACKGROUND>
  <TEXTBUTTON name="" id="9f93adc260880011" memberName="osc1Select" virtualName=""
              explicitFocusOrder="0" pos="269 14 18 18" bgColOff="ff827474"
              buttonText="1" connectedEdges="10" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="fff82a831cc4d1c8" memberName="osc2Select" virtualName=""
              explicitFocusOrder="0" pos="269 43 18 18" bgColOff="ff827474"
              buttonText="2" connectedEdges="10" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="b143da09762590b1" memberName="osc3Select" virtualName=""
              explicitFocusOrder="0" pos="269 71 18 18" bgColOff="ff827474"
              buttonText="3" connectedEdges="10" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="4086c4eeb32669a3" memberName="osc4Select" virtualName=""
              explicitFocusOrder="0" pos="269 99 18 18" bgColOff="ff827474"
              buttonText="4" connectedEdges="10" needsCallback="1" radioGroupId="0"/>
  <GROUPCOMPONENT name="" id="801d5a5c1906b80a" memberName="chorusGroup" virtualName=""
                  explicitFocusOrder="0" pos="203 263 80 126" outlinecol="66ffffff"
                  textcol="ffffffff" title="Chorus" textpos="36"/>
  <GROUPCOMPONENT name="" id="b5209686262fb628" memberName="toneGroup" virtualName=""
                  explicitFocusOrder="0" pos="284 135 345 126" outlinecol="66ffffff"
                  textcol="ffffffff" title="Tone" textpos="36"/>
  <GROUPCOMPONENT name="" id="b756917fb3ac2023" memberName="filterGroup" virtualName=""
                  explicitFocusOrder="0" pos="3 263 199 126" outlinecol="66ffffff"
                  textcol="ffffffff" title="Filter" textpos="36"/>
  <GROUPCOMPONENT name="" id="692696bb1b731a29" memberName="ampGroup" virtualName=""
                  explicitFocusOrder="0" pos="3 135 280 126" outlinecol="66ffffff"
                  textcol="ffffffff" title="Amp" textpos="36"/>
  <GENERICCOMPONENT name="" id="bfaa4a1729a14480" memberName="partials" virtualName=""
                    explicitFocusOrder="0" pos="287 14 266 115" class="OscillatorPartials"
                    params="master"/>
  <GENERICCOMPONENT name="" id="535c181119851a85" memberName="scope" virtualName=""
                    explicitFocusOrder="0" pos="558 14 115 115" class="OscillatorScope"
                    params="master"/>
  <SLIDER name="" id="de7eb376e7783320" memberName="ampAttackSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="13 150 10 90" tooltip="Amp attack"
          thumbcol="ff9ba6da" min="0" max="1" int="0.0001" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="30"
          textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="d441bc17a5b87c0" memberName="ampDecaySlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="25 150 10 90" tooltip="Amp decay"
          thumbcol="ff9ba6da" min="0" max="1" int="0.0001" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="30"
          textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="7bbb1b051e921ceb" memberName="ampSustainSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="37 150 10 90" tooltip="Amp sustain"
          thumbcol="ff9ba6da" min="0" max="1" int="0.0001" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="30"
          textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="90aefb612e01ffe0" memberName="ampReleaseSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="49 150 10 90" tooltip="Amp release"
          thumbcol="ff9ba6da" min="0" max="1" int="0.0001" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="30"
          textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="66eb8749a6607ee4" memberName="filterCutoffSlider"
          virtualName="ImageSlider" explicitFocusOrder="0" pos="13 278 10 90"
          tooltip="Filter cutoff frequency" thumbcol="fff2f2f2" min="0"
          max="1" int="0.0001" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="30" textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="5c700d31e3045e2c" memberName="filterResoSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="25 278 10 90" tooltip="Filter resonance"
          thumbcol="fff2f2f2" min="0" max="1" int="0.0001" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="30"
          textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="adac665571eaa189" memberName="filterTrackingSlider"
          virtualName="ImageSlider" explicitFocusOrder="0" pos="37 278 10 90"
          tooltip="Keyboard tracking" thumbcol="fff2f2f2" min="0" max="1"
          int="0.0001" style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="30" textBoxHeight="18" skewFactor="1"/>
  <LABEL name="" id="96d8b9b486a9e336" memberName="ampAdsrLabel" virtualName=""
         explicitFocusOrder="0" pos="11 240 50 11" bkgCol="0" textCol="ff000000"
         outlineCol="0" edTextCol="ff000000" edBkgCol="0" labelText="A D S R"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="" id="b67e2f7f49212a7f" memberName="filterLabel" virtualName=""
         explicitFocusOrder="0" pos="10 368 39 11" bkgCol="0" textCol="ff000000"
         outlineCol="0" edTextCol="ff000000" edBkgCol="0" labelText="C Q T"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <GROUPCOMPONENT name="" id="8c4ec565ea6a46e" memberName="driveGroup" virtualName=""
                  explicitFocusOrder="0" pos="284 263 61 126" outlinecol="66ffffff"
                  textcol="ffffffff" title="Drive" textpos="36"/>
  <GROUPCOMPONENT name="" id="5e82dcd303be212a" memberName="eqGroup" virtualName=""
                  explicitFocusOrder="0" pos="346 263 251 126" outlinecol="66ffffff"
                  textcol="ffffffff" title="EQ" textpos="36"/>
  <GROUPCOMPONENT name="" id="9b9bbe81fd2b0f02" memberName="delayGroup" virtualName=""
                  explicitFocusOrder="0" pos="598 263 77 126" outlinecol="66ffffff"
                  textcol="ffffffff" title="Delay" textpos="36"/>
  <SLIDER name="" id="799caacdc37f5a12" memberName="destructDriveSlider"
          virtualName="ImageSlider" explicitFocusOrder="0" pos="297 278 10 90"
          tooltip="Destruct drive" thumbcol="ff666666" min="0" max="1"
          int="0.0001" style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="30" textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="b0f9a13f9ea7b4df" memberName="destructLowpassSlider"
          virtualName="ImageSlider" explicitFocusOrder="0" pos="309 278 10 90"
          tooltip="Destruct lowpass" thumbcol="ff666666" min="0" max="1"
          int="0.0001" style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="30" textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="6068e0b29681f2bd" memberName="toneAttackValueSlider"
          virtualName="ImageSlider" explicitFocusOrder="0" pos="329 150 10 90"
          tooltip="Tone attack value" thumbcol="ffdabb9b" min="0" max="1"
          int="0.0001" style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="30" textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="de117dcc86c00596" memberName="toneAttackSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="341 150 10 90" tooltip="Tone attack time"
          thumbcol="ffdabb9b" min="0" max="1" int="0.0001" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="30"
          textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="b33397738f27c1d2" memberName="toneDecayValueSlider"
          virtualName="ImageSlider" explicitFocusOrder="0" pos="353 150 10 90"
          tooltip="Tone release value" thumbcol="ffdabb9b" min="0" max="1"
          int="0.0001" style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="30" textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="89be8d5685fd2fbf" memberName="toneDecaySlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="365 150 10 90" tooltip="Tone release time"
          thumbcol="ffdabb9b" min="0" max="1" int="0.0001" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="30"
          textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="897a8fc05ec84436" memberName="toneMasterSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="294 150 10 90" tooltip="Tone release"
          thumbcol="ffce8f4d" min="0" max="1" int="0.0001" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="30"
          textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="7dff255782ffd653" memberName="toneDetuneSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="306 150 10 90" tooltip="Tone release"
          thumbcol="ffce8f4d" min="0" max="1" int="0.0001" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="30"
          textBoxHeight="18" skewFactor="1"/>
  <LABEL name="" id="f1352a75d37d9e6d" memberName="toneAdsrLabel" virtualName=""
         explicitFocusOrder="0" pos="294 240 109 11" bkgCol="0" textCol="ff000000"
         outlineCol="0" edTextCol="ff000000" edBkgCol="0" labelText="T D    A at D dt R rt"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <GROUPCOMPONENT name="" id="a7ae272eeb238ab7" memberName="masterGroup" virtualName=""
                  explicitFocusOrder="0" pos="3 5 144 126" outlinecol="66ffffff"
                  textcol="ffffffff" title="Master" textpos="36"/>
  <SLIDER name="" id="b7bef453ff75d039" memberName="masterGainSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="13 20 10 90" tooltip="Master gain"
          thumbcol="ff6479df" min="0" max="1" int="0.0001" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="30"
          textBoxHeight="18" skewFactor="1"/>
  <TOGGLEBUTTON name="" id="9bab54ebac5162f9" memberName="enableButton" virtualName="ParameterToggleButton"
                explicitFocusOrder="0" pos="38 39 49 17" buttonText="ON" connectedEdges="0"
                needsCallback="1" radioGroupId="0" state="0"/>
  <SLIDER name="" id="7a32b8f313b0fe87" memberName="partNumberSlider" virtualName=""
          explicitFocusOrder="0" pos="41 25 50 12" tooltip="Part number"
          min="1" max="16" int="1" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="20" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="86739f6a616f3058" memberName="destructHighpassSlider"
          virtualName="ImageSlider" explicitFocusOrder="0" pos="321 278 10 90"
          tooltip="Destruct highpass" thumbcol="ff666666" min="0" max="1"
          int="0.0001" style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="30" textBoxHeight="18" skewFactor="1"/>
  <LABEL name="" id="356f50f6333ff78b" memberName="driveLabel" virtualName=""
         explicitFocusOrder="0" pos="294 367 42 13" bkgCol="0" textCol="ff000000"
         outlineCol="0" edTextCol="ff000000" edBkgCol="0" labelText="dr lp hp"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <SLIDER name="" id="51a7c1a245ad1a09" memberName="masterPanSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="25 20 10 90" tooltip="Master pan"
          thumbcol="ff6479df" min="0" max="1" int="0.0001" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="30"
          textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="3bde9f811fa45529" memberName="filterAttackValueSlider"
          virtualName="ImageSlider" explicitFocusOrder="0" pos="146 278 10 90"
          tooltip="Filter cutoff attack value" thumbcol="fff2f2f2" min="0"
          max="1" int="0.0001" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="30" textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="d410bd3edecba038" memberName="filterAttackTimeSlider"
          virtualName="ImageSlider" explicitFocusOrder="0" pos="158 278 10 90"
          tooltip="Filter cutoff attack time" thumbcol="fff2f2f2" min="0"
          max="1" int="0.0001" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="30" textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="dbaa72e8bd25e196" memberName="filterDecayValueSlider"
          virtualName="ImageSlider" explicitFocusOrder="0" pos="170 278 10 90"
          tooltip="Filter cutoff decay value" thumbcol="fff2f2f2" min="0"
          max="1" int="0.0001" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="30" textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="e1970c6da7904b4c" memberName="filterDecayTimeSlider"
          virtualName="ImageSlider" explicitFocusOrder="0" pos="182 278 10 90"
          tooltip="Filter cutoff decay time" thumbcol="fff2f2f2" min="0"
          max="1" int="0.0001" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="30" textBoxHeight="18" skewFactor="1"/>
  <LABEL name="" id="52923ca81507223f" memberName="filterEnvelopeLabel"
         virtualName="" explicitFocusOrder="0" pos="143 368 53 11" bkgCol="0"
         textCol="ff000000" outlineCol="0" edTextCol="ff000000" edBkgCol="0"
         labelText="A at D dt" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <SLIDER name="" id="329a9cf66a3f8b6f" memberName="partKeyboardSlider"
          virtualName="" explicitFocusOrder="0" pos="40 98 98 10" tooltip="Part number"
          thumbcol="ffd22d27" min="0" max="127" int="1" style="TwoValueHorizontal"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="30"
          textBoxHeight="20" skewFactor="1"/>
  <TOGGLEBUTTON name="" id="584fd49bd5bd2ce9" memberName="portaButton" virtualName="ParameterToggleButton"
                explicitFocusOrder="0" pos="38 52 49 17" buttonText="PORTA" connectedEdges="0"
                needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="" id="da66e88e43568c4d" memberName="polyButton" virtualName="ParameterToggleButton"
                explicitFocusOrder="0" pos="38 65 49 17" buttonText="POLY" connectedEdges="0"
                needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="" id="6ca8bb66eced2b19" memberName="masterLabel" virtualName=""
         explicitFocusOrder="0" pos="11 112 119 11" bkgCol="0" textCol="ff000000"
         outlineCol="0" edTextCol="ff000000" edBkgCol="0" labelText="G P     KEYS RANGE"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="" id="745fbe6d4728011b" memberName="stereoButton" virtualName="ParameterToggleButton"
                explicitFocusOrder="0" pos="38 78 49 17" buttonText="STEREO"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <SLIDER name="" id="c62c9035e6342fb5" memberName="chorusFreqSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="226 278 10 90" tooltip="Chorus frequency"
          thumbcol="ff47596b" min="0" max="1" int="0.0001" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="30"
          textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="3438921e9dab2cda" memberName="chorusDelaySlider"
          virtualName="ImageSlider" explicitFocusOrder="0" pos="238 278 10 90"
          tooltip="Chorus delay" thumbcol="ff47596b" min="0" max="1" int="0.0001"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="30" textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="c178adaa52e442ea" memberName="chorusDepthSlider"
          virtualName="ImageSlider" explicitFocusOrder="0" pos="250 278 10 90"
          tooltip="Chorus depth" thumbcol="ff47596b" min="0" max="1" int="0.0001"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="30" textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="9851639636fcaadc" memberName="chorusFeedbackSlider"
          virtualName="ImageSlider" explicitFocusOrder="0" pos="262 278 10 90"
          tooltip="Chorus feedback" thumbcol="ff47596b" min="0" max="1"
          int="0.0001" style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="30" textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="c1e42212dc2bc850" memberName="chorusGainSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="214 278 10 90" tooltip="Chorus gain"
          thumbcol="ff47596b" min="0" max="1" int="0.0001" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="30"
          textBoxHeight="18" skewFactor="1"/>
  <LABEL name="" id="eb7194886504bb87" memberName="chorusLabel" virtualName=""
         explicitFocusOrder="0" pos="211 367 65 13" bkgCol="0" textCol="ff000000"
         outlineCol="0" edTextCol="ff000000" edBkgCol="0" labelText="G fq dl dp fe"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="" id="c2f676d960caa34c" memberName="eqgraph" virtualName=""
                    explicitFocusOrder="0" pos="434 282 152 97" class="EQGraph" params=""/>
  <SLIDER name="" id="edca3ef713af1958" memberName="eqFreq1Slider" virtualName="ParameterSlider"
          explicitFocusOrder="0" pos="387 280 22 22" tooltip="Eq 1 Frequency"
          thumbcol="ff47596b" rotarysliderfill="7fffffff" min="0" max="1"
          int="0.0001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="30" textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="493efb3fe3cabdb6" memberName="eqGain1Slider" virtualName="ParameterSlider"
          explicitFocusOrder="0" pos="365 280 22 22" tooltip="Eq 1 Gain"
          thumbcol="ff47596b" trackcol="7fbebaba" rotarysliderfill="7fffffff"
          min="0" max="1" int="0.0001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="30" textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="99aee10cb55c9a2a" memberName="eqFreq2Slider" virtualName="ParameterSlider"
          explicitFocusOrder="0" pos="387 303 22 22" tooltip="Eq 2 Frequency"
          thumbcol="ff47596b" rotarysliderfill="7fffffff" min="0" max="1"
          int="0.0001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="30" textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="c849864c40e7d4bb" memberName="eqGain2Slider" virtualName="ParameterSlider"
          explicitFocusOrder="0" pos="365 303 22 22" tooltip="Eq 2 Gain"
          thumbcol="ff47596b" rotarysliderfill="7fffffff" min="0" max="1"
          int="0.0001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="30" textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="d00c722974f720b8" memberName="eqFreq3Slider" virtualName="ParameterSlider"
          explicitFocusOrder="0" pos="387 326 22 22" tooltip="Eq 3 Frequency"
          thumbcol="ff47596b" rotarysliderfill="7fffffff" min="0" max="1"
          int="0.0001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="30" textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="fdc8e401dfacb003" memberName="eqGain3Slider" virtualName="ParameterSlider"
          explicitFocusOrder="0" pos="365 326 22 22" tooltip="Eq 3 Gain"
          thumbcol="ff47596b" rotarysliderfill="7fffffff" min="0" max="1"
          int="0.0001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="30" textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="e894353dce94a260" memberName="filterLfoDepthSlider"
          virtualName="ParameterSlider" explicitFocusOrder="0" pos="52 302 25 25"
          tooltip="Filter lfo depth" thumbcol="ff47596b" rotarysliderfill="7ff5f5f5"
          min="0" max="1" int="0.001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="30" textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="aede61cfa60a2715" memberName="filterLfoFrequencySlider"
          virtualName="ParameterSlider" explicitFocusOrder="0" pos="84 302 26 25"
          tooltip="Filter lfo frequency" thumbcol="ff47596b" rotarysliderfill="7fffffff"
          min="0" max="1" int="0.001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="30" textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="5b10dc5a4b1e4529" memberName="filterLfoRandomSlider"
          virtualName="ParameterSlider" explicitFocusOrder="0" pos="117 302 27 25"
          tooltip="Filter lfo random" thumbcol="ff47596b" rotarysliderfill="7fffffff"
          min="0" max="1" int="0.001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="30" textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="d6e92e4d888e98fa" memberName="toneReleaseValueSlider"
          virtualName="ImageSlider" explicitFocusOrder="0" pos="377 150 10 90"
          tooltip="Tone release value" thumbcol="ffdabb9b" min="0" max="1"
          int="0.0001" style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="30" textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="7fb1d184ff3cda07" memberName="toneReleaseSlider"
          virtualName="ImageSlider" explicitFocusOrder="0" pos="389 150 10 90"
          tooltip="Tone release time" thumbcol="ffdabb9b" min="0" max="1"
          int="0.0001" style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="30" textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="d6bf80247faaba20" memberName="eqBw2Slider" virtualName="ParameterSlider"
          explicitFocusOrder="0" pos="409 303 22 22" tooltip="Eq 2 Q" thumbcol="ff47596b"
          rotarysliderfill="7fffffff" min="0" max="1" int="0.0001" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="30"
          textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="5481b8ca5a1c375d" memberName="eqBw3Slider" virtualName="ParameterSlider"
          explicitFocusOrder="0" pos="409 326 22 22" tooltip="Eq 3 Q" thumbcol="ff47596b"
          rotarysliderfill="7fffffff" min="0" max="1" int="0.0001" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="30"
          textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="eadeb84db8dadc81" memberName="eqFreq4Slider" virtualName="ParameterSlider"
          explicitFocusOrder="0" pos="387 348 22 22" tooltip="Eq 4 Frequency"
          thumbcol="ff47596b" rotarysliderfill="7fffffff" min="0" max="1"
          int="0.0001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="30" textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="3bfa7f9a49ab37c2" memberName="eqGain4Slider" virtualName="ParameterSlider"
          explicitFocusOrder="0" pos="365 348 22 22" tooltip="Eq 4 Gain"
          thumbcol="ff47596b" rotarysliderfill="7fffffff" min="0" max="1"
          int="0.0001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="30" textBoxHeight="18" skewFactor="1"/>
  <LABEL name="" id="ee3ef37e4e5a1604" memberName="eq1Label" virtualName=""
         explicitFocusOrder="0" pos="354 278 9 95" bkgCol="0" textCol="ff000000"
         outlineCol="0" edTextCol="ff000000" edBkgCol="0" labelText="1&#10;&#10;2&#10;&#10;3&#10;&#10;4"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="44fa8d5148166107" memberName="eq2Label" virtualName=""
         explicitFocusOrder="0" pos="370 370 56 11" bkgCol="0" textCol="ff000000"
         outlineCol="0" edTextCol="ff000000" edBkgCol="0" labelText="G     F     Q"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="12" bold="0" italic="0" justification="36"/>
  <SLIDER name="" id="b949bee10a76e923" memberName="delayVolumeSlider"
          virtualName="ImageSlider" explicitFocusOrder="0" pos="607 278 10 90"
          tooltip="Delay volume" thumbcol="ff715ec3" min="0" max="1" int="0.0001"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="30" textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="1483e91255977779" memberName="delayTimeSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="631 278 10 90" tooltip="Delay time"
          thumbcol="ff715ec3" min="0" max="1" int="0.0001" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="30"
          textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="b83ae40702f753cd" memberName="delayFeedbackSlider"
          virtualName="ImageSlider" explicitFocusOrder="0" pos="643 278 10 90"
          tooltip="Delay feedback" thumbcol="ff715ec3" min="0" max="1"
          int="0.0001" style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="30" textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="66e768d882948163" memberName="delayPanSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="619 278 10 90" tooltip="Delay pan"
          thumbcol="ff715ec3" min="0" max="1" int="0.0001" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="30"
          textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="4d2d801b9774688d" memberName="delayFilterSlider"
          virtualName="ImageSlider" explicitFocusOrder="0" pos="655 278 10 90"
          tooltip="Delay filter" thumbcol="ff715ec3" min="0" max="1" int="0.0001"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="30" textBoxHeight="18" skewFactor="1"/>
  <LABEL name="" id="d8b3dcd94acfed6" memberName="echoLabel" virtualName=""
         explicitFocusOrder="0" pos="604 370 65 12" bkgCol="0" textCol="ff000000"
         outlineCol="0" edTextCol="ff000000" edBkgCol="0" labelText="G P T F lp"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="" id="5786da5a6173d5ea" memberName="ampEnvelope" virtualName=""
                    explicitFocusOrder="0" pos="66 154 207 97" class="EnvelopeEditor"
                    params="master"/>
  <GENERICCOMPONENT name="" id="df3bafd09667a126" memberName="joystick" virtualName="ParameterJoystick"
                    explicitFocusOrder="0" pos="149 14 115 115" class="Joystick"
                    params=""/>
  <GROUPCOMPONENT name="" id="c8d81f419eb99704" memberName="noiseGroup" virtualName=""
                  explicitFocusOrder="0" pos="630 135 45 126" outlinecol="66ffffff"
                  textcol="ffffffff" title="Nz" textpos="36"/>
  <SLIDER name="" id="27314c18cae9e2d9" memberName="noiseGainSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="647 150 10 90" tooltip="Noise volume"
          thumbcol="ff5c8f50" min="0" max="1" int="0.0001" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="30"
          textBoxHeight="18" skewFactor="1"/>
  <LABEL name="" id="777ba335071dbc0e" memberName="noiseLabel" virtualName=""
         explicitFocusOrder="0" pos="638 240 29 11" bkgCol="0" textCol="ff000000"
         outlineCol="0" edTextCol="ff000000" edBkgCol="0" labelText="Gain"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="" id="babdccf0e8d89b1b" memberName="pitchEnvelope" virtualName=""
                    explicitFocusOrder="0" pos="409 154 210 97" class="EnvelopeEditor"
                    params="master"/>
  <TEXTBUTTON name="" id="402a4c05bd6571fb" memberName="osc1SelectPhase" virtualName=""
              explicitFocusOrder="0" pos="269 31 18 13" bgColOff="ff805f8b"
              buttonText="1P" connectedEdges="6" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="d82af53d92a58bdf" memberName="osc2SelectPhase" virtualName=""
              explicitFocusOrder="0" pos="269 59 18 13" bgColOff="ff805f8b"
              buttonText="2P" connectedEdges="6" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="5f2e42db4d919c9a" memberName="osc3SelectPhase" virtualName=""
              explicitFocusOrder="0" pos="269 88 18 13" bgColOff="ff805f8b"
              buttonText="3P" connectedEdges="6" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="8aab839b3a8e0f72" memberName="osc4SelectPhase" virtualName=""
              explicitFocusOrder="0" pos="269 116 18 13" bgColOff="ff805f8b"
              buttonText="4P" connectedEdges="6" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="" id="86ae655961e79bf7" memberName="eqBw1Slider" virtualName="ParameterSlider"
          explicitFocusOrder="0" pos="409 280 22 22" tooltip="Eq 1 Q" thumbcol="ff47596b"
          rotarysliderfill="7fffffff" min="0" max="1" int="0.0001" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="30"
          textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="" id="553838d7d68b4f0e" memberName="eqBw4Slider" virtualName="ParameterSlider"
          explicitFocusOrder="0" pos="409 348 22 22" tooltip="Eq 4 Q" thumbcol="ff47596b"
          rotarysliderfill="7fffffff" min="0" max="1" int="0.0001" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="30"
          textBoxHeight="18" skewFactor="1"/>
  <LABEL name="" id="7d0a54c907ced322" memberName="filterLfoLabel" virtualName=""
         explicitFocusOrder="0" pos="50 328 94 11" bkgCol="0" textCol="ff000000"
         outlineCol="0" edTextCol="ff000000" edBkgCol="0" labelText="lfoA   lfoF   lfoR"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="" id="8656d682796c591c" memberName="filterTypeBox" virtualName=""
            explicitFocusOrder="0" pos="52 285 89 15" editable="0" layout="33"
            items="" textWhenNonSelected="" textWhenNoItems=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
