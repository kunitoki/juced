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

#ifndef __JUCER_HEADER_XSYNTHPATCH_XSYNTHPATCH_B8769F2F__
#define __JUCER_HEADER_XSYNTHPATCH_XSYNTHPATCH_B8769F2F__

//[Headers]     -- You can add your own extra header files here --
#include "../StandardHeader.h"
#include "../XSynthPlugin.h"
#include "Utils/AudioScope.h"
#include "Utils/OscillatorScope.h"
#include "Utils/OscillatorPartials.h"
#include "Utils/EQGraph.h"
#include "Utils/EnvelopeEditor.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class XSynthPatch  : public Component,
                     public JoystickListener,
                     public ButtonListener,
                     public SliderListener,
                     public ComboBoxListener
{
public:
    //==============================================================================
    XSynthPatch (XSynthPlugin* plugin_, Master* master_);
    ~XSynthPatch();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void setPartNumber (const int newPartNumber);
    void setOscillatorNumber (const int newOscNumber, const bool isMagnitude = true);
    void joystickValueChanged (Joystick* joystick);
    void updateControls ();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    XSynthPlugin* plugin;
    Master* master;
    int partNumber;
    int oscNumber;
    //[/UserVariables]

    //==============================================================================
    TextButton* osc1Select;
    TextButton* osc2Select;
    TextButton* osc3Select;
    TextButton* osc4Select;
    GroupComponent* chorusGroup;
    GroupComponent* toneGroup;
    GroupComponent* filterGroup;
    GroupComponent* ampGroup;
    OscillatorPartials* partials;
    OscillatorScope* scope;
    ImageSlider* ampAttackSlider;
    ImageSlider* ampDecaySlider;
    ImageSlider* ampSustainSlider;
    ImageSlider* ampReleaseSlider;
    ImageSlider* filterCutoffSlider;
    ImageSlider* filterResoSlider;
    ImageSlider* filterTrackingSlider;
    Label* ampAdsrLabel;
    Label* filterLabel;
    GroupComponent* driveGroup;
    GroupComponent* eqGroup;
    GroupComponent* delayGroup;
    ImageSlider* destructDriveSlider;
    ImageSlider* destructLowpassSlider;
    ImageSlider* toneAttackValueSlider;
    ImageSlider* toneAttackSlider;
    ImageSlider* toneDecayValueSlider;
    ImageSlider* toneDecaySlider;
    ImageSlider* toneMasterSlider;
    ImageSlider* toneDetuneSlider;
    Label* toneAdsrLabel;
    GroupComponent* masterGroup;
    ImageSlider* masterGainSlider;
    ParameterToggleButton* enableButton;
    Slider* partNumberSlider;
    ImageSlider* destructHighpassSlider;
    Label* driveLabel;
    ImageSlider* masterPanSlider;
    ImageSlider* filterAttackValueSlider;
    ImageSlider* filterAttackTimeSlider;
    ImageSlider* filterDecayValueSlider;
    ImageSlider* filterDecayTimeSlider;
    Label* filterEnvelopeLabel;
    Slider* partKeyboardSlider;
    ParameterToggleButton* portaButton;
    ParameterToggleButton* polyButton;
    Label* masterLabel;
    ParameterToggleButton* stereoButton;
    ImageSlider* chorusFreqSlider;
    ImageSlider* chorusDelaySlider;
    ImageSlider* chorusDepthSlider;
    ImageSlider* chorusFeedbackSlider;
    ImageSlider* chorusGainSlider;
    Label* chorusLabel;
    EQGraph* eqgraph;
    ParameterSlider* eqFreq1Slider;
    ParameterSlider* eqGain1Slider;
    ParameterSlider* eqFreq2Slider;
    ParameterSlider* eqGain2Slider;
    ParameterSlider* eqFreq3Slider;
    ParameterSlider* eqGain3Slider;
    ParameterSlider* filterLfoDepthSlider;
    ParameterSlider* filterLfoFrequencySlider;
    ParameterSlider* filterLfoRandomSlider;
    ImageSlider* toneReleaseValueSlider;
    ImageSlider* toneReleaseSlider;
    ParameterSlider* eqBw2Slider;
    ParameterSlider* eqBw3Slider;
    ParameterSlider* eqFreq4Slider;
    ParameterSlider* eqGain4Slider;
    Label* eq1Label;
    Label* eq2Label;
    ImageSlider* delayVolumeSlider;
    ImageSlider* delayTimeSlider;
    ImageSlider* delayFeedbackSlider;
    ImageSlider* delayPanSlider;
    ImageSlider* delayFilterSlider;
    Label* echoLabel;
    EnvelopeEditor* ampEnvelope;
    ParameterJoystick* joystick;
    GroupComponent* noiseGroup;
    ImageSlider* noiseGainSlider;
    Label* noiseLabel;
    EnvelopeEditor* pitchEnvelope;
    TextButton* osc1SelectPhase;
    TextButton* osc2SelectPhase;
    TextButton* osc3SelectPhase;
    TextButton* osc4SelectPhase;
    ParameterSlider* eqBw1Slider;
    ParameterSlider* eqBw4Slider;
    Label* filterLfoLabel;
    ComboBox* filterTypeBox;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    XSynthPatch (const XSynthPatch&);
    const XSynthPatch& operator= (const XSynthPatch&);
};


#endif   // __JUCER_HEADER_XSYNTHPATCH_XSYNTHPATCH_B8769F2F__
