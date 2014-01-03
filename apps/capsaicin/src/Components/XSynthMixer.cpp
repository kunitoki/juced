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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "XSynthMixer.h"



//==============================================================================
XSynthMixer::XSynthMixer (XSynthPlugin* plugin_, Master* master_)
    : plugin (plugin_),
      master (master_),
      part01 (0),
      part02 (0),
      part03 (0),
      part04 (0),
      part05 (0),
      part06 (0),
      part07 (0),
      part08 (0),
      part09 (0),
      part10 (0),
      part11 (0),
      part12 (0),
      part13 (0),
      part14 (0),
      part15 (0),
      part16 (0),
      masterGroup (0),
      masterGainSlider (0),
      reverbTimeSlider (0),
      reverbGainSlider (0),
      reverbTailSlider (0),
      reverbDampSlider (0),
      leftMeter (0),
      rightMeter (0)
{
    addAndMakeVisible (part01 = new XSynthMixerStrip (plugin, master, 0));
    addAndMakeVisible (part02 = new XSynthMixerStrip (plugin, master, 1));
    addAndMakeVisible (part03 = new XSynthMixerStrip (plugin, master, 2));
    addAndMakeVisible (part04 = new XSynthMixerStrip (plugin, master, 3));
    addAndMakeVisible (part05 = new XSynthMixerStrip (plugin, master, 4));
    addAndMakeVisible (part06 = new XSynthMixerStrip (plugin, master, 5));
    addAndMakeVisible (part07 = new XSynthMixerStrip (plugin, master, 6));
    addAndMakeVisible (part08 = new XSynthMixerStrip (plugin, master, 7));
    addAndMakeVisible (part09 = new XSynthMixerStrip (plugin, master, 8));
    addAndMakeVisible (part10 = new XSynthMixerStrip (plugin, master, 9));
    addAndMakeVisible (part11 = new XSynthMixerStrip (plugin, master, 10));
    addAndMakeVisible (part12 = new XSynthMixerStrip (plugin, master, 11));
    addAndMakeVisible (part13 = new XSynthMixerStrip (plugin, master, 12));
    addAndMakeVisible (part14 = new XSynthMixerStrip (plugin, master, 13));
    addAndMakeVisible (part15 = new XSynthMixerStrip (plugin, master, 14));
    addAndMakeVisible (part16 = new XSynthMixerStrip (plugin, master, 15));
    addAndMakeVisible (masterGroup = new GroupComponent (String::empty,
                                                         T("Master")));
    masterGroup->setTextLabelPosition (Justification::centred);
    masterGroup->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    masterGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (masterGainSlider = new ImageSlider (String::empty));
    masterGainSlider->setRange (0, 1, 0.0001);
    masterGainSlider->setSliderStyle (Slider::LinearVertical);
    masterGainSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    masterGainSlider->addListener (this);

    addAndMakeVisible (reverbTimeSlider = new Slider (String::empty));
    reverbTimeSlider->setRange (0, 1, 0.0001);
    reverbTimeSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    reverbTimeSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    reverbTimeSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    reverbTimeSlider->addListener (this);

    addAndMakeVisible (reverbGainSlider = new Slider (String::empty));
    reverbGainSlider->setRange (0, 1, 0.0001);
    reverbGainSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    reverbGainSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    reverbGainSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    reverbGainSlider->addListener (this);

    addAndMakeVisible (reverbTailSlider = new Slider (String::empty));
    reverbTailSlider->setRange (0, 1, 0.0001);
    reverbTailSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    reverbTailSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    reverbTailSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    reverbTailSlider->addListener (this);

    addAndMakeVisible (reverbDampSlider = new Slider (String::empty));
    reverbDampSlider->setRange (0, 1, 0.0001);
    reverbDampSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    reverbDampSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    reverbDampSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    reverbDampSlider->addListener (this);

    addAndMakeVisible (leftMeter = new MeterComponent (MeterComponent::MeterVertical,
                                                       0,
                                                       2,
                                                       Colours::blue,
                                                       Colours::lightblue,
                                                       Colours::white,
                                                       Colours::black,
                                                       0.6));

    addAndMakeVisible (rightMeter = new MeterComponent (MeterComponent::MeterVertical,
                                                        0,
                                                        2,
                                                        Colours::blue,
                                                        Colours::lightblue,
                                                        Colours::white,
                                                        Colours::black,
                                                        0.6));

    setSize (680, 400);

    //[Constructor] You can add your own custom stuff here..
    parts[0] = part01;
    parts[1] = part02;
    parts[2] = part03;
    parts[3] = part04;
    parts[4] = part05;
    parts[5] = part06;
    parts[6] = part07;
    parts[7] = part08;
    parts[8] = part09;
    parts[9] = part10;
    parts[10] = part11;
    parts[11] = part12;
    parts[12] = part13;
    parts[13] = part14;
    parts[14] = part15;
    parts[15] = part16;

    leftMeter->setFrame (1);
    rightMeter->setFrame (1);

    reverbTimeSlider->setVisible (false);
    reverbGainSlider->setVisible (false);
    reverbTailSlider->setVisible (false);
    reverbDampSlider->setVisible (false);

    plugin->getParameterLock().enter ();
        plugin->addListenerToParameter (PM_GAIN, masterGainSlider);
    plugin->getParameterLock().exit ();

    startTimer (25);
    //[/Constructor]
}

XSynthMixer::~XSynthMixer()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    stopTimer ();

    plugin->getParameterLock().enter ();
        plugin->removeListenerToParameter (PM_GAIN, masterGainSlider);
    plugin->getParameterLock().exit ();

    //[/Destructor_pre]

    deleteAndZero (part01);
    deleteAndZero (part02);
    deleteAndZero (part03);
    deleteAndZero (part04);
    deleteAndZero (part05);
    deleteAndZero (part06);
    deleteAndZero (part07);
    deleteAndZero (part08);
    deleteAndZero (part09);
    deleteAndZero (part10);
    deleteAndZero (part11);
    deleteAndZero (part12);
    deleteAndZero (part13);
    deleteAndZero (part14);
    deleteAndZero (part15);
    deleteAndZero (part16);
    deleteAndZero (masterGroup);
    deleteAndZero (masterGainSlider);
    deleteAndZero (reverbTimeSlider);
    deleteAndZero (reverbGainSlider);
    deleteAndZero (reverbTailSlider);
    deleteAndZero (reverbDampSlider);
    deleteAndZero (leftMeter);
    deleteAndZero (rightMeter);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void XSynthMixer::paint (Graphics& g)
{
    g.fillAll (Colour (0xff827474));

    g.setGradientFill (ColourGradient (Colour (0xff827474),
                                       330.0f, 390.0f,
                                       Colours::black,
                                       330.0f, 410.0f,
                                       false));

    g.fillRect (0, 370, 680, 30);

    //[UserPaint] Add your own custom paint stuff here..
    //[/UserPaint]
}

void XSynthMixer::resized()
{
    part01->setBounds (2, 9, 36, 380);
    part02->setBounds (39, 9, 36, 380);
    part03->setBounds (76, 9, 36, 380);
    part04->setBounds (113, 9, 36, 380);
    part05->setBounds (150, 9, 36, 380);
    part06->setBounds (187, 9, 36, 380);
    part07->setBounds (224, 9, 36, 380);
    part08->setBounds (261, 9, 36, 380);
    part09->setBounds (298, 9, 36, 380);
    part10->setBounds (335, 9, 36, 380);
    part11->setBounds (372, 9, 36, 380);
    part12->setBounds (409, 9, 36, 380);
    part13->setBounds (446, 9, 36, 380);
    part14->setBounds (483, 9, 37, 380);
    part15->setBounds (520, 9, 36, 380);
    part16->setBounds (557, 9, 36, 380);
    masterGroup->setBounds (592, 9, 86, 380);
    masterGainSlider->setBounds (620, 280, 10, 100);
    reverbTimeSlider->setBounds (647, 48, 24, 24);
    reverbGainSlider->setBounds (647, 98, 24, 24);
    reverbTailSlider->setBounds (647, 23, 24, 24);
    reverbDampSlider->setBounds (647, 73, 24, 24);
    leftMeter->setBounds (640, 280, 8, 100);
    rightMeter->setBounds (649, 280, 8, 100);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void XSynthMixer::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == masterGainSlider)
    {
        //[UserSliderCode_masterGainSlider] -- add your slider handling code here..
        // master->setPvolume ((int) (sliderThatWasMoved->getValue() * 127.0f));
        plugin->setParameterNotifyingHost (PM_GAIN, sliderThatWasMoved->getValue());
        //[/UserSliderCode_masterGainSlider]
    }
    else if (sliderThatWasMoved == reverbTimeSlider)
    {
        //[UserSliderCode_reverbTimeSlider] -- add your slider handling code here..
        master->sysefx[0]->setEffectParameter (3, (int) (sliderThatWasMoved->getValue() * 127.0f));
        //[/UserSliderCode_reverbTimeSlider]
    }
    else if (sliderThatWasMoved == reverbGainSlider)
    {
        //[UserSliderCode_reverbGainSlider] -- add your slider handling code here..
        master->sysefx[0]->setEffectParameter (0, (int) (sliderThatWasMoved->getValue() * 127.0f));
        //[/UserSliderCode_reverbGainSlider]
    }
    else if (sliderThatWasMoved == reverbTailSlider)
    {
        //[UserSliderCode_reverbTailSlider] -- add your slider handling code here..
        master->sysefx[0]->setEffectParameter (2, (int) (sliderThatWasMoved->getValue() * 127.0f));
        //[/UserSliderCode_reverbTailSlider]
    }
    else if (sliderThatWasMoved == reverbDampSlider)
    {
        //[UserSliderCode_reverbDampSlider] -- add your slider handling code here..
        master->sysefx[0]->setEffectParameter (5, (int) (sliderThatWasMoved->getValue() * 127.0f));
        //[/UserSliderCode_reverbDampSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void XSynthMixer::updateControls ()
{
    for (int i = 0; i < 16; i++)
    {
        parts [i]->enableSolo (master->Psolopart == (i + 1));
        parts [i]->updateControls ();
    }

    masterGainSlider->setValue (plugin->getParameter (PM_GAIN), false);

    reverbGainSlider->setValue (master->sysefx[0]->getEffectParameter (0) / 127.0f, false);
    reverbTimeSlider->setValue (master->sysefx[0]->getEffectParameter (3) / 127.0f, false);
    reverbTailSlider->setValue (master->sysefx[0]->getEffectParameter (2) / 127.0f, false);
    reverbDampSlider->setValue (master->sysefx[0]->getEffectParameter (5) / 127.0f, false);
}

void XSynthMixer::timerCallback ()
{
    float peak [NUM_MIDI_PARTS];
    float masterVuLeft, masterVuRight;

    master->mutex.enter ();
        memcpy (peak, master->vuoutpeakpart, NUM_MIDI_PARTS * sizeof (float));
        masterVuLeft = master->vuoutpeakl;
        masterVuRight = master->vuoutpeakr;
    master->mutex.exit ();

    for (int i = 0; i < 16; i++)
        parts [i]->setMeterValue (peak[i]);

    leftMeter->setValue (masterVuLeft);
    rightMeter->setValue (masterVuRight);
}

void XSynthMixer::setSoloChannel (const int soloChannel)
{
    for (int i = 0; i < 16; i++)
        parts [i]->enableSolo (soloChannel == (i + 1));

    master->mutex.enter ();
        master->Psolopart = soloChannel;
    master->mutex.exit ();
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="XSynthMixer" componentName=""
                 parentClasses="public Component, public Timer" constructorParams="XSynthPlugin* plugin_, Master* master_"
                 variableInitialisers="plugin (plugin_)&#10;master (master_)" snapPixels="10"
                 snapActive="1" snapShown="0" overlayOpacity="0.330000013" fixedSize="1"
                 initialWidth="680" initialHeight="400">
  <BACKGROUND backgroundColour="ff827474">
    <RECT pos="0 370 680 30" fill="linear: 330 390, 330 410, 0=ff827474, 1=ff000000"
          hasStroke="0"/>
  </BACKGROUND>
  <JUCERCOMP name="" id="21c2821c19b064ae" memberName="part01" virtualName=""
             pos="2 9 36 380" sourceFile="XSynthMixerStrip.cpp" constructorParams="plugin, master, 0"/>
  <JUCERCOMP name="" id="61ef0a7307ddd995" memberName="part02" virtualName=""
             pos="39 9 36 380" sourceFile="XSynthMixerStrip.cpp" constructorParams="plugin, master, 1"/>
  <JUCERCOMP name="" id="446e888fb673a982" memberName="part03" virtualName=""
             pos="76 9 36 380" sourceFile="XSynthMixerStrip.cpp" constructorParams="plugin, master, 2"/>
  <JUCERCOMP name="" id="ba7e3229b334c769" memberName="part04" virtualName=""
             pos="113 9 36 380" sourceFile="XSynthMixerStrip.cpp" constructorParams="plugin, master, 3"/>
  <JUCERCOMP name="" id="2e3362e2eca90d38" memberName="part05" virtualName=""
             pos="150 9 36 380" sourceFile="XSynthMixerStrip.cpp" constructorParams="plugin, master, 4"/>
  <JUCERCOMP name="" id="e02648c36c774804" memberName="part06" virtualName=""
             pos="187 9 36 380" sourceFile="XSynthMixerStrip.cpp" constructorParams="plugin, master, 5"/>
  <JUCERCOMP name="" id="68ca0e0918251882" memberName="part07" virtualName=""
             pos="224 9 36 380" sourceFile="XSynthMixerStrip.cpp" constructorParams="plugin, master, 6"/>
  <JUCERCOMP name="" id="d1ebe4204fc43bb9" memberName="part08" virtualName=""
             pos="261 9 36 380" sourceFile="XSynthMixerStrip.cpp" constructorParams="plugin, master, 7"/>
  <JUCERCOMP name="" id="f2b593ed5f570ff6" memberName="part09" virtualName=""
             pos="298 9 36 380" sourceFile="XSynthMixerStrip.cpp" constructorParams="plugin, master, 8"/>
  <JUCERCOMP name="" id="85b7775054ec69ff" memberName="part10" virtualName=""
             pos="335 9 36 380" sourceFile="XSynthMixerStrip.cpp" constructorParams="plugin, master, 9"/>
  <JUCERCOMP name="" id="6e28ffe9aadd0e8c" memberName="part11" virtualName=""
             pos="372 9 36 380" sourceFile="XSynthMixerStrip.cpp" constructorParams="plugin, master, 10"/>
  <JUCERCOMP name="" id="8cfe2f1b677363f3" memberName="part12" virtualName=""
             pos="409 9 36 380" sourceFile="XSynthMixerStrip.cpp" constructorParams="plugin, master, 11"/>
  <JUCERCOMP name="" id="80e3a34f81d83023" memberName="part13" virtualName=""
             pos="446 9 36 380" sourceFile="XSynthMixerStrip.cpp" constructorParams="plugin, master, 12"/>
  <JUCERCOMP name="" id="7aea1e7a03a576d4" memberName="part14" virtualName=""
             pos="483 9 37 380" sourceFile="XSynthMixerStrip.cpp" constructorParams="plugin, master, 13"/>
  <JUCERCOMP name="" id="9de5a9e10f3acbfd" memberName="part15" virtualName=""
             pos="520 9 36 380" sourceFile="XSynthMixerStrip.cpp" constructorParams="plugin, master, 14"/>
  <JUCERCOMP name="" id="f583bb1b911cae86" memberName="part16" virtualName=""
             pos="557 9 36 380" sourceFile="XSynthMixerStrip.cpp" constructorParams="plugin, master, 15"/>
  <GROUPCOMPONENT name="" id="3cdfe3d9c13854b6" memberName="masterGroup" virtualName=""
                  pos="592 9 86 380" outlinecol="66ffffff" textcol="ffffffff" title="Master"
                  textpos="36"/>
  <SLIDER name="" id="e6369630b32e5946" memberName="masterGainSlider" virtualName="ImageSlider"
          pos="620 280 10 100" min="0" max="1" int="0.0001" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20"/>
  <SLIDER name="" id="7cf6d1063ea0a036" memberName="reverbTimeSlider" virtualName=""
          pos="647 48 24 24" rotarysliderfill="7fffffff" min="0" max="1"
          int="0.0001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20"/>
  <SLIDER name="" id="cbac5293ede20e2b" memberName="reverbGainSlider" virtualName=""
          pos="647 98 24 24" rotarysliderfill="7fffffff" min="0" max="1"
          int="0.0001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20"/>
  <SLIDER name="" id="e799edc41e12d8f6" memberName="reverbTailSlider" virtualName=""
          pos="647 23 24 24" rotarysliderfill="7fffffff" min="0" max="1"
          int="0.0001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20"/>
  <SLIDER name="" id="ec48ada14f5ea765" memberName="reverbDampSlider" virtualName=""
          pos="647 73 24 24" rotarysliderfill="7fffffff" min="0" max="1"
          int="0.0001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20"/>
  <GENERICCOMPONENT name="" id="f26b04203791e351" memberName="leftMeter" virtualName=""
                    pos="640 280 8 100" class="MeterComponent" params="MeterComponent::MeterVertical,&#10;0,&#10;2,&#10;Colours::blue,&#10;Colours::lightblue,&#10;Colours::white,&#10;Colours::black,&#10;0.6"/>
  <GENERICCOMPONENT name="" id="d78b914ddbc8df0b" memberName="rightMeter" virtualName=""
                    pos="649 280 8 100" class="MeterComponent" params="MeterComponent::MeterVertical,&#10;0,&#10;2,&#10;Colours::blue,&#10;Colours::lightblue,&#10;Colours::white,&#10;Colours::black,&#10;0.6"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
