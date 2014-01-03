/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  3 Dec 2009 10:21:58 am

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
#include "NekobeePlugin.h"
#include "NekobeeComponent.h"
//[/Headers]

#include "NekobeeMain.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
NekobeeMain::NekobeeMain (NekobeePlugin* plugin_, NekobeeComponent* parent_)
    : plugin (plugin_),
      parent (parent_),
      accentSlider (0),
      volumeSlider (0),
      cutoffSlider (0),
      resonanceSlider (0),
      decaySlider (0),
      envSlider (0),
      tuningSlider (0),
      waveformSlider (0),
      versionLabel (0),
      keyboard (0),
      cachedImage_bee_logo_png (0)
{
    addAndMakeVisible (accentSlider = new ParameterSlider (String::empty));
    accentSlider->setTooltip (T("Accent"));
    accentSlider->setRange (0, 1, 0.0001);
    accentSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    accentSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    accentSlider->setColour (Slider::backgroundColourId, Colour (0x0));
    accentSlider->setColour (Slider::thumbColourId, Colours::white);
    accentSlider->setColour (Slider::trackColourId, Colour (0x7fffffff));
    accentSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x99ffffff));
    accentSlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x99ffffff));
    accentSlider->setColour (Slider::textBoxTextColourId, Colours::black);
    accentSlider->addListener (this);

    addAndMakeVisible (volumeSlider = new ParameterSlider (String::empty));
    volumeSlider->setTooltip (T("Volume"));
    volumeSlider->setRange (0, 1, 0.0001);
    volumeSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    volumeSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    volumeSlider->setColour (Slider::backgroundColourId, Colour (0x0));
    volumeSlider->setColour (Slider::thumbColourId, Colours::white);
    volumeSlider->setColour (Slider::trackColourId, Colour (0x7fffffff));
    volumeSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x99ffffff));
    volumeSlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x99ffffff));
    volumeSlider->setColour (Slider::textBoxTextColourId, Colours::black);
    volumeSlider->addListener (this);

    addAndMakeVisible (cutoffSlider = new ImageSlider (String::empty));
    cutoffSlider->setTooltip (T("Cutoff frequency"));
    cutoffSlider->setRange (0, 1, 0.0001);
    cutoffSlider->setSliderStyle (Slider::LinearHorizontal);
    cutoffSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    cutoffSlider->setColour (Slider::backgroundColourId, Colour (0x0));
    cutoffSlider->setColour (Slider::thumbColourId, Colours::white);
    cutoffSlider->setColour (Slider::trackColourId, Colour (0x7fffffff));
    cutoffSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x99ffffff));
    cutoffSlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x99ffffff));
    cutoffSlider->setColour (Slider::textBoxTextColourId, Colours::black);
    cutoffSlider->addListener (this);

    addAndMakeVisible (resonanceSlider = new ImageSlider (String::empty));
    resonanceSlider->setTooltip (T("Resonance amount"));
    resonanceSlider->setRange (0, 1, 0.0001);
    resonanceSlider->setSliderStyle (Slider::LinearHorizontal);
    resonanceSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    resonanceSlider->setColour (Slider::backgroundColourId, Colour (0x0));
    resonanceSlider->setColour (Slider::thumbColourId, Colours::white);
    resonanceSlider->setColour (Slider::trackColourId, Colour (0x7fffffff));
    resonanceSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x99ffffff));
    resonanceSlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x99ffffff));
    resonanceSlider->setColour (Slider::textBoxTextColourId, Colours::black);
    resonanceSlider->addListener (this);

    addAndMakeVisible (decaySlider = new ParameterSlider (String::empty));
    decaySlider->setTooltip (T("Decay"));
    decaySlider->setRange (0, 1, 0.0001);
    decaySlider->setSliderStyle (Slider::RotaryVerticalDrag);
    decaySlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    decaySlider->setColour (Slider::backgroundColourId, Colour (0x0));
    decaySlider->setColour (Slider::thumbColourId, Colours::white);
    decaySlider->setColour (Slider::trackColourId, Colour (0x7fffffff));
    decaySlider->setColour (Slider::rotarySliderFillColourId, Colour (0x99ffffff));
    decaySlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x99ffffff));
    decaySlider->setColour (Slider::textBoxTextColourId, Colours::black);
    decaySlider->addListener (this);

    addAndMakeVisible (envSlider = new ParameterSlider (String::empty));
    envSlider->setTooltip (T("Envelope Modulation"));
    envSlider->setRange (0, 1, 0.0001);
    envSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    envSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    envSlider->setColour (Slider::backgroundColourId, Colour (0x0));
    envSlider->setColour (Slider::thumbColourId, Colours::white);
    envSlider->setColour (Slider::trackColourId, Colour (0x7fffffff));
    envSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x99ffffff));
    envSlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x99ffffff));
    envSlider->setColour (Slider::textBoxTextColourId, Colours::black);
    envSlider->addListener (this);

    addAndMakeVisible (tuningSlider = new ParameterSlider (String::empty));
    tuningSlider->setTooltip (T("Tuning"));
    tuningSlider->setRange (0, 1, 0.0001);
    tuningSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    tuningSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    tuningSlider->setColour (Slider::backgroundColourId, Colour (0x0));
    tuningSlider->setColour (Slider::thumbColourId, Colours::white);
    tuningSlider->setColour (Slider::trackColourId, Colour (0x7fffffff));
    tuningSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x99ffffff));
    tuningSlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x99ffffff));
    tuningSlider->setColour (Slider::textBoxTextColourId, Colours::black);
    tuningSlider->addListener (this);

    addAndMakeVisible (waveformSlider = new ParameterSlider (String::empty));
    waveformSlider->setTooltip (T("Waveform"));
    waveformSlider->setRange (0, 1, 1);
    waveformSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    waveformSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    waveformSlider->setColour (Slider::backgroundColourId, Colour (0x0));
    waveformSlider->setColour (Slider::thumbColourId, Colours::white);
    waveformSlider->setColour (Slider::trackColourId, Colour (0x7fffffff));
    waveformSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x99ffffff));
    waveformSlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x99ffffff));
    waveformSlider->setColour (Slider::textBoxTextColourId, Colours::black);
    waveformSlider->addListener (this);

    addAndMakeVisible (versionLabel = new Label (String::empty,
                                                 T("v0.1.0")));
    versionLabel->setFont (Font (9.6000f, Font::bold | Font::italic));
    versionLabel->setJustificationType (Justification::centredLeft);
    versionLabel->setEditable (false, false, false);
    versionLabel->setColour (Label::textColourId, Colour (0x93ffffff));
    versionLabel->setColour (TextEditor::textColourId, Colours::black);
    versionLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (keyboard = new MidiKeyboardComponent (plugin->getKeyboardState(),
                                                             MidiKeyboardComponent::horizontalKeyboard));

    cachedImage_bee_logo_png = ImageCache::getFromMemory (bee_logo_png, bee_logo_pngSize);

    //[UserPreSize]
    //[/UserPreSize]

    setSize (400, 148);

    //[Constructor] You can add your own custom stuff here..

    versionLabel->setText (String ("v") + JucePlugin_VersionString, false);

    cutoffSlider->setOrientation (ImageSlider::LinearHorizontal);
    cutoffSlider->setSkewFactor (0.5f);
    resonanceSlider->setOrientation (ImageSlider::LinearHorizontal);
    resonanceSlider->setSkewFactor (0.5f);

    keyboard->setMidiChannel (1);
    keyboard->setMidiChannelsToDisplay (1 << 0);
    keyboard->setKeyPressBaseOctave (3);
    keyboard->setLowestVisibleKey (12);
    keyboard->setKeyWidth (11);
    keyboard->setColour (MidiKeyboardComponent::upDownButtonBackgroundColourId, Colours::black);
    keyboard->setColour (MidiKeyboardComponent::upDownButtonArrowColourId, Colours::white);

    plugin->getParameterLock().enter ();
        plugin->addListenerToParameter (PAR_TUNING, tuningSlider);
        plugin->addListenerToParameter (PAR_WAVEFORM, waveformSlider);
        plugin->addListenerToParameter (PAR_CUTOFF, cutoffSlider);
        plugin->addListenerToParameter (PAR_RESONANCE, resonanceSlider);
        plugin->addListenerToParameter (PAR_ENVMOD, envSlider);
        plugin->addListenerToParameter (PAR_DECAY, decaySlider);
        plugin->addListenerToParameter (PAR_ACCENT, accentSlider);
        plugin->addListenerToParameter (PAR_VOLUME, volumeSlider);
    plugin->getParameterLock().exit ();

    //[/Constructor]
}

NekobeeMain::~NekobeeMain()
{
    //[Destructor_pre]. You can add your own custom destruction code here..

    plugin->getParameterLock().enter ();
        plugin->removeListenerToParameter (PAR_TUNING, tuningSlider);
        plugin->removeListenerToParameter (PAR_WAVEFORM, waveformSlider);
        plugin->removeListenerToParameter (PAR_CUTOFF, cutoffSlider);
        plugin->removeListenerToParameter (PAR_RESONANCE, resonanceSlider);
        plugin->removeListenerToParameter (PAR_ENVMOD, envSlider);
        plugin->removeListenerToParameter (PAR_DECAY, decaySlider);
        plugin->removeListenerToParameter (PAR_ACCENT, accentSlider);
        plugin->removeListenerToParameter (PAR_VOLUME, volumeSlider);
    plugin->getParameterLock().exit ();

    //[/Destructor_pre]

    deleteAndZero (accentSlider);
    deleteAndZero (volumeSlider);
    deleteAndZero (cutoffSlider);
    deleteAndZero (resonanceSlider);
    deleteAndZero (decaySlider);
    deleteAndZero (envSlider);
    deleteAndZero (tuningSlider);
    deleteAndZero (waveformSlider);
    deleteAndZero (versionLabel);
    deleteAndZero (keyboard);
    ImageCache::release (cachedImage_bee_logo_png);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void NekobeeMain::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::black);

    g.setGradientFill (ColourGradient (Colours::black,
                                       125.0f, 95.0f,
                                       Colour (0xff515151),
                                       125.0f, 5.0f,
                                       false));
    g.fillRect (0, 0, 400, 100);

    g.setColour (Colour (0x68ffffff));
    g.fillRoundedRectangle (113.0f, 5.0f, 210.0f, 91.0f, 10.0000f);

    g.setColour (Colour (0x63ffffff));
    g.drawRoundedRectangle (113.0f, 5.0f, 210.0f, 91.0f, 10.0000f, 1.6000f);

    g.setColour (Colour (0x68ffffff));
    g.fillRoundedRectangle (330.0f, 5.0f, 63.0f, 91.0f, 10.0000f);

    g.setColour (Colour (0x63ffffff));
    g.drawRoundedRectangle (330.0f, 5.0f, 63.0f, 91.0f, 10.0000f, 1.6000f);

    g.setColour (Colours::white);
    g.setFont (Font (Font::getDefaultSansSerifFontName(), 11.2000f, Font::italic));
    g.drawText (T("Accent"),
                335, 35, 53, 12,
                Justification::centred, true);

    g.setColour (Colours::white);
    g.setFont (Font (Font::getDefaultSansSerifFontName(), 11.2000f, Font::italic));
    g.drawText (T("Volume"),
                335, 79, 53, 12,
                Justification::centred, true);

    g.setColour (Colours::black);
    g.drawImage (cachedImage_bee_logo_png,
                 18, 8, 76, 64,
                 0, 0, cachedImage_bee_logo_png->getWidth(), cachedImage_bee_logo_png->getHeight());

    g.setColour (Colour (0xc5ffffff));
    g.setFont (Font (21.3000f, Font::bold | Font::italic));
    g.drawText (T("NEKOBEE"),
                6, 72, 98, 20,
                Justification::centred, true);

    g.setColour (Colours::white);
    g.setFont (Font (Font::getDefaultSansSerifFontName(), 11.2000f, Font::italic));
    g.drawText (T("Decay"),
                113, 83, 53, 12,
                Justification::centred, true);

    g.setColour (Colours::white);
    g.setFont (Font (Font::getDefaultSansSerifFontName(), 11.2000f, Font::italic));
    g.drawText (T("Envelope"),
                166, 83, 53, 12,
                Justification::centred, true);

    g.setColour (Colours::white);
    g.setFont (Font (Font::getDefaultSansSerifFontName(), 11.2000f, Font::italic));
    g.drawText (T("Tuning"),
                217, 83, 53, 12,
                Justification::centred, true);

    g.setColour (Colours::white);
    g.setFont (Font (Font::getDefaultSansSerifFontName(), 11.2000f, Font::italic));
    g.drawText (T("Wave"),
                268, 83, 53, 12,
                Justification::centred, true);

    g.setColour (Colours::white);
    g.setFont (Font (Font::getDefaultSansSerifFontName(), 11.2000f, Font::italic));
    g.drawText (T("Cutoff"),
                267, 19, 53, 12,
                Justification::centred, true);

    g.setColour (Colours::white);
    g.setFont (Font (Font::getDefaultSansSerifFontName(), 11.2000f, Font::italic));
    g.drawText (T("Resonance"),
                257, 43, 53, 12,
                Justification::centred, true);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void NekobeeMain::resized()
{
    accentSlider->setBounds (344, 9, 35, 30);
    volumeSlider->setBounds (344, 53, 35, 30);
    cutoffSlider->setBounds (123, 9, 190, 14);
    resonanceSlider->setBounds (123, 33, 190, 14);
    decaySlider->setBounds (123, 57, 33, 30);
    envSlider->setBounds (176, 57, 31, 30);
    tuningSlider->setBounds (228, 57, 31, 30);
    waveformSlider->setBounds (279, 57, 31, 30);
    versionLabel->setBounds (78, 88, 34, 13);
    keyboard->setBounds (2, 100, getWidth() - 4, getHeight() - 102);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void NekobeeMain::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == accentSlider)
    {
        //[UserSliderCode_accentSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_ACCENT, sliderThatWasMoved->getValue());
        //[/UserSliderCode_accentSlider]
    }
    else if (sliderThatWasMoved == volumeSlider)
    {
        //[UserSliderCode_volumeSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_VOLUME, sliderThatWasMoved->getValue());
        //[/UserSliderCode_volumeSlider]
    }
    else if (sliderThatWasMoved == cutoffSlider)
    {
        //[UserSliderCode_cutoffSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_CUTOFF, sliderThatWasMoved->getValue());
        //[/UserSliderCode_cutoffSlider]
    }
    else if (sliderThatWasMoved == resonanceSlider)
    {
        //[UserSliderCode_resonanceSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_RESONANCE, sliderThatWasMoved->getValue());
        //[/UserSliderCode_resonanceSlider]
    }
    else if (sliderThatWasMoved == decaySlider)
    {
        //[UserSliderCode_decaySlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_DECAY, sliderThatWasMoved->getValue());
        //[/UserSliderCode_decaySlider]
    }
    else if (sliderThatWasMoved == envSlider)
    {
        //[UserSliderCode_envSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_ENVMOD, sliderThatWasMoved->getValue());
        //[/UserSliderCode_envSlider]
    }
    else if (sliderThatWasMoved == tuningSlider)
    {
        //[UserSliderCode_tuningSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_TUNING, sliderThatWasMoved->getValue());
        //[/UserSliderCode_tuningSlider]
    }
    else if (sliderThatWasMoved == waveformSlider)
    {
        //[UserSliderCode_waveformSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_WAVEFORM, sliderThatWasMoved->getValue());
        //[/UserSliderCode_waveformSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

//==============================================================================
void NekobeeMain::updateControls ()
{
    tuningSlider->setValue (plugin->getParameterMapped (PAR_TUNING), false);
    waveformSlider->setValue (plugin->getParameterMapped (PAR_WAVEFORM), false);
    cutoffSlider->setValue (plugin->getParameterMapped (PAR_CUTOFF), false);
    resonanceSlider->setValue (plugin->getParameterMapped (PAR_RESONANCE), false);
    decaySlider->setValue (plugin->getParameterMapped (PAR_DECAY), false);
    envSlider->setValue (plugin->getParameterMapped (PAR_ENVMOD), false);
    accentSlider->setValue (plugin->getParameterMapped (PAR_ACCENT), false);
    volumeSlider->setValue (plugin->getParameterMapped (PAR_VOLUME), false);
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="NekobeeMain" componentName=""
                 parentClasses="public Component" constructorParams="NekobeePlugin* plugin_, NekobeeComponent* parent_"
                 variableInitialisers="plugin (plugin_),&#10;parent (parent_)" snapPixels="5"
                 snapActive="0" snapShown="1" overlayOpacity="0.330000013" fixedSize="1"
                 initialWidth="400" initialHeight="148">
  <BACKGROUND backgroundColour="ff000000">
    <RECT pos="0 0 400 100" fill="linear: 125 95, 125 5, 0=ff000000, 1=ff515151"
          hasStroke="0"/>
    <ROUNDRECT pos="113 5 210 91" cornerSize="10" fill="solid: 68ffffff" hasStroke="1"
               stroke="1.60000002, mitered, butt" strokeColour="solid: 63ffffff"/>
    <ROUNDRECT pos="330 5 63 91" cornerSize="10" fill="solid: 68ffffff" hasStroke="1"
               stroke="1.60000002, mitered, butt" strokeColour="solid: 63ffffff"/>
    <TEXT pos="335 35 53 12" fill="solid: ffffffff" hasStroke="0" text="Accent"
          fontname="Default sans-serif font" fontsize="11.2" bold="0" italic="1"
          justification="36"/>
    <TEXT pos="335 79 53 12" fill="solid: ffffffff" hasStroke="0" text="Volume"
          fontname="Default sans-serif font" fontsize="11.2" bold="0" italic="1"
          justification="36"/>
    <IMAGE pos="18 8 76 64" resource="bee_logo_png" opacity="1" mode="0"/>
    <TEXT pos="6 72 98 20" fill="solid: c5ffffff" hasStroke="0" text="NEKOBEE"
          fontname="Default font" fontsize="21.3" bold="1" italic="1" justification="36"/>
    <TEXT pos="113 83 53 12" fill="solid: ffffffff" hasStroke="0" text="Decay"
          fontname="Default sans-serif font" fontsize="11.2" bold="0" italic="1"
          justification="36"/>
    <TEXT pos="166 83 53 12" fill="solid: ffffffff" hasStroke="0" text="Envelope"
          fontname="Default sans-serif font" fontsize="11.2" bold="0" italic="1"
          justification="36"/>
    <TEXT pos="217 83 53 12" fill="solid: ffffffff" hasStroke="0" text="Tuning"
          fontname="Default sans-serif font" fontsize="11.2" bold="0" italic="1"
          justification="36"/>
    <TEXT pos="268 83 53 12" fill="solid: ffffffff" hasStroke="0" text="Wave"
          fontname="Default sans-serif font" fontsize="11.2" bold="0" italic="1"
          justification="36"/>
    <TEXT pos="267 19 53 12" fill="solid: ffffffff" hasStroke="0" text="Cutoff"
          fontname="Default sans-serif font" fontsize="11.2" bold="0" italic="1"
          justification="36"/>
    <TEXT pos="257 43 53 12" fill="solid: ffffffff" hasStroke="0" text="Resonance"
          fontname="Default sans-serif font" fontsize="11.2" bold="0" italic="1"
          justification="36"/>
  </BACKGROUND>
  <SLIDER name="" id="211b3e1a175c5456" memberName="accentSlider" virtualName="ParameterSlider"
          explicitFocusOrder="0" pos="344 9 35 30" tooltip="Accent" bkgcol="0"
          thumbcol="ffffffff" trackcol="7fffffff" rotarysliderfill="99ffffff"
          rotaryslideroutline="99ffffff" textboxtext="ff000000" min="0"
          max="1" int="0.0001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="1de73b78d0d5b24e" memberName="volumeSlider" virtualName="ParameterSlider"
          explicitFocusOrder="0" pos="344 53 35 30" tooltip="Volume" bkgcol="0"
          thumbcol="ffffffff" trackcol="7fffffff" rotarysliderfill="99ffffff"
          rotaryslideroutline="99ffffff" textboxtext="ff000000" min="0"
          max="1" int="0.0001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="6ae352a6b3a2cb17" memberName="cutoffSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="123 9 190 14" tooltip="Cutoff frequency"
          bkgcol="0" thumbcol="ffffffff" trackcol="7fffffff" rotarysliderfill="99ffffff"
          rotaryslideroutline="99ffffff" textboxtext="ff000000" min="0"
          max="1" int="0.0001" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="336f03ba35576ed2" memberName="resonanceSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="123 33 190 14" tooltip="Resonance amount"
          bkgcol="0" thumbcol="ffffffff" trackcol="7fffffff" rotarysliderfill="99ffffff"
          rotaryslideroutline="99ffffff" textboxtext="ff000000" min="0"
          max="1" int="0.0001" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="2b7020ab29042d76" memberName="decaySlider" virtualName="ParameterSlider"
          explicitFocusOrder="0" pos="123 57 33 30" tooltip="Decay" bkgcol="0"
          thumbcol="ffffffff" trackcol="7fffffff" rotarysliderfill="99ffffff"
          rotaryslideroutline="99ffffff" textboxtext="ff000000" min="0"
          max="1" int="0.0001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="9326e728e27f2e8f" memberName="envSlider" virtualName="ParameterSlider"
          explicitFocusOrder="0" pos="176 57 31 30" tooltip="Envelope Modulation"
          bkgcol="0" thumbcol="ffffffff" trackcol="7fffffff" rotarysliderfill="99ffffff"
          rotaryslideroutline="99ffffff" textboxtext="ff000000" min="0"
          max="1" int="0.0001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="f03ebc0d2c390a89" memberName="tuningSlider" virtualName="ParameterSlider"
          explicitFocusOrder="0" pos="228 57 31 30" tooltip="Tuning" bkgcol="0"
          thumbcol="ffffffff" trackcol="7fffffff" rotarysliderfill="99ffffff"
          rotaryslideroutline="99ffffff" textboxtext="ff000000" min="0"
          max="1" int="0.0001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="577cb7ec9932871a" memberName="waveformSlider" virtualName="ParameterSlider"
          explicitFocusOrder="0" pos="279 57 31 30" tooltip="Waveform"
          bkgcol="0" thumbcol="ffffffff" trackcol="7fffffff" rotarysliderfill="99ffffff"
          rotaryslideroutline="99ffffff" textboxtext="ff000000" min="0"
          max="1" int="1" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="" id="22e39299a061010b" memberName="versionLabel" virtualName=""
         explicitFocusOrder="0" pos="78 88 34 13" textCol="93ffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="v0.1.0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="9.6"
         bold="1" italic="1" justification="33"/>
  <GENERICCOMPONENT name="" id="d6a98a7585c59312" memberName="keyboard" virtualName=""
                    explicitFocusOrder="0" pos="2 100 4M 102M" class="MidiKeyboardComponent"
                    params="plugin-&gt;getKeyboardState(),&#10;MidiKeyboardComponent::horizontalKeyboard"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//==============================================================================
// Binary resources - be careful not to edit any of these sections!

// JUCER_RESOURCE: bee_logo_png, 17248, "../../../../../../Desktop/bee_logo.png"
static const unsigned char resource_NekobeeMain_bee_logo_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,105,0,0,0,115,8,6,0,0,0,155,207,44,199,0,0,0,1,115,82,71,66,0,174,206,28,233,0,0,
0,6,98,75,71,68,0,255,0,255,0,255,160,189,167,147,0,0,0,9,112,72,89,115,0,0,46,35,0,0,46,35,1,120,165,63,118,0,0,32,0,73,68,65,84,120,218,236,125,119,156,164,85,149,246,115,206,189,239,91,213,57,85,87,
119,207,12,67,80,88,114,50,163,43,163,184,130,128,174,25,65,196,128,34,184,172,9,5,132,5,71,84,22,65,17,144,85,76,192,42,160,14,18,68,130,74,24,3,201,21,211,16,69,193,1,135,97,166,67,117,117,238,170,122,
239,125,190,63,238,173,208,3,204,238,247,125,27,191,143,250,253,250,55,51,61,29,222,186,231,158,115,158,243,156,4,60,251,122,246,245,236,235,217,215,179,175,255,137,175,197,245,61,171,159,61,133,255,166,
47,142,14,172,202,158,24,161,223,52,194,234,198,145,181,110,178,176,234,217,83,249,111,242,242,99,3,171,178,137,254,181,190,52,76,142,15,115,246,241,2,253,196,16,253,228,8,125,185,240,172,86,253,87,190,
42,235,219,87,101,19,197,213,156,28,162,43,23,57,253,232,114,158,255,15,3,124,233,222,57,158,249,241,110,142,255,113,25,125,121,132,126,116,144,217,120,241,89,97,253,103,191,178,241,193,213,44,23,232,
103,86,178,186,105,152,87,126,181,200,253,158,223,78,85,67,21,75,107,148,251,238,146,227,183,207,43,114,102,195,48,57,81,164,155,88,182,150,227,207,154,192,255,120,191,51,181,205,42,87,26,161,159,30,166,
47,143,240,142,31,246,242,13,251,231,153,166,150,34,134,170,54,124,24,165,26,203,52,181,220,111,159,60,127,118,77,145,149,77,203,194,247,149,134,214,62,123,146,255,17,126,167,212,191,202,79,22,215,250,
233,109,232,167,134,184,97,221,8,79,60,174,155,131,189,150,34,150,162,134,42,74,72,16,22,96,9,49,180,198,80,173,101,119,71,202,35,95,215,206,63,222,85,100,54,190,156,44,15,211,151,151,61,107,2,255,61,
94,181,77,61,171,124,121,104,173,159,28,161,159,90,193,217,245,67,188,96,117,31,183,93,102,169,34,45,218,147,16,80,138,90,2,134,128,161,136,16,80,170,216,96,6,213,114,168,223,240,228,227,186,185,249,190,
34,57,62,68,55,189,205,90,214,182,121,214,4,254,159,190,220,104,239,106,63,63,68,63,51,196,234,196,8,175,251,102,39,95,186,103,74,85,75,17,165,170,82,69,41,80,10,44,5,134,34,74,32,8,7,80,138,152,168,105,
218,248,63,17,229,46,59,164,252,250,217,125,156,94,191,34,128,139,114,97,173,159,236,124,86,88,255,102,191,51,61,184,202,79,12,146,51,1,157,221,125,253,48,223,118,104,7,219,218,18,138,38,225,160,97,162,
0,148,34,57,10,108,67,48,64,16,96,67,80,48,81,112,38,106,150,82,196,210,26,203,253,94,216,198,31,94,60,192,249,191,172,32,199,87,176,54,218,245,172,9,220,42,98,43,245,173,242,83,195,107,125,121,152,190,
92,228,31,255,101,144,31,57,170,155,61,93,134,16,67,19,125,79,16,72,64,113,245,195,23,88,138,128,2,37,0,170,106,67,136,88,162,93,66,68,237,131,8,141,26,182,231,45,15,59,164,157,247,174,29,96,182,121,152,
126,116,152,126,115,241,89,173,90,234,119,250,87,249,201,161,181,44,15,211,207,12,179,244,167,33,158,251,137,46,174,28,206,83,84,130,96,68,227,135,105,152,172,186,207,9,218,162,141,175,89,106,238,130,
144,194,231,91,191,39,104,35,68,168,154,208,154,148,197,254,60,79,60,174,147,79,222,55,196,108,116,132,110,116,37,221,134,231,60,171,89,156,42,174,246,211,195,244,179,203,184,56,58,196,75,206,235,229,
222,187,229,35,74,83,170,4,243,166,98,41,64,48,115,8,255,103,140,182,8,47,126,180,248,34,0,81,32,77,16,81,23,22,32,20,173,11,84,8,85,170,24,170,10,119,222,62,199,175,157,53,192,153,199,11,244,227,203,
232,55,15,210,143,47,255,255,79,88,44,173,92,229,202,35,244,211,35,228,244,50,174,189,182,159,175,63,176,141,109,249,164,137,206,226,7,162,80,172,73,41,72,40,81,83,4,134,42,38,28,176,42,19,171,124,254,
94,41,47,252,108,15,247,127,105,46,128,5,213,8,207,17,1,134,68,225,161,197,135,33,34,195,186,86,130,106,193,131,94,222,201,31,125,123,128,174,188,29,89,90,78,63,182,61,221,166,255,15,104,38,78,14,172,
202,198,139,49,24,45,242,254,95,12,243,61,111,110,99,123,206,82,161,84,147,18,82,23,140,137,127,143,154,17,81,93,221,212,169,152,134,230,236,182,67,202,159,124,103,136,139,79,142,208,143,15,51,219,188,
130,55,94,49,192,151,189,44,223,248,30,107,76,139,144,100,9,208,168,155,208,250,231,69,65,17,101,119,187,242,176,67,114,124,224,231,69,102,99,43,200,209,33,186,209,2,253,212,200,255,123,62,203,109,234,
91,229,198,183,89,235,203,131,244,211,35,156,120,120,71,158,115,90,39,7,6,194,193,5,64,96,130,255,80,211,184,225,33,238,209,24,15,37,17,118,155,40,64,203,101,69,229,69,255,216,205,233,245,67,244,147,5,
250,210,16,221,216,16,125,105,128,126,172,200,197,13,131,60,255,172,34,119,126,142,105,17,68,208,164,166,159,106,133,238,160,138,132,11,99,13,211,36,165,138,112,160,207,240,164,99,58,57,250,208,16,253,
228,48,221,196,16,57,241,255,16,115,225,39,134,87,251,242,114,186,233,97,86,158,24,226,154,139,6,185,247,174,41,85,44,77,93,83,16,3,211,24,211,0,118,137,227,87,85,170,6,225,40,132,221,157,150,199,189,
167,147,27,214,21,233,75,203,232,203,69,214,158,44,242,154,111,244,240,167,107,250,233,167,138,244,227,5,250,201,34,125,121,5,39,31,30,228,7,143,201,179,189,77,27,2,18,105,185,12,162,75,254,46,170,52,
198,208,52,124,85,66,21,229,115,183,75,120,241,231,122,56,247,216,16,253,230,2,253,104,129,126,180,247,127,174,9,172,109,234,93,237,74,67,244,19,35,244,165,97,222,122,109,145,7,191,172,131,57,27,224,47,
164,238,208,37,248,27,49,141,15,72,48,127,168,163,51,181,20,99,105,85,248,234,87,228,249,224,221,35,116,165,97,250,201,97,250,210,48,239,190,190,139,111,250,155,28,83,163,188,232,204,126,114,124,152,126,
188,24,14,177,188,130,110,188,64,55,186,140,15,222,49,200,55,190,166,61,66,112,211,252,249,104,94,150,134,201,147,186,54,71,86,35,130,25,163,202,23,238,157,227,77,223,238,103,117,211,16,125,233,185,244,
99,195,244,165,193,255,57,38,208,63,217,181,202,151,6,67,188,51,61,204,123,127,182,3,223,127,68,39,243,105,74,17,27,227,155,100,73,0,26,144,153,141,31,218,18,168,54,5,183,207,158,41,127,242,221,94,102,
227,43,200,241,1,114,116,128,127,190,123,128,199,29,217,205,174,118,37,34,171,112,233,231,123,233,203,5,250,201,65,250,137,193,152,87,26,164,31,45,144,99,195,204,54,21,121,195,21,253,124,222,158,105,212,
146,240,1,177,49,208,141,116,146,26,42,64,17,9,62,176,206,112,68,160,210,213,174,60,236,224,118,222,127,123,145,217,216,48,253,248,48,221,230,2,93,249,191,113,140,85,217,220,179,202,143,15,172,245,51,
203,232,166,7,57,250,208,32,207,56,161,139,43,138,1,4,136,218,24,179,88,10,130,221,23,109,82,58,77,97,9,209,224,229,148,219,173,48,188,226,162,2,103,55,46,163,159,24,166,47,173,96,249,145,2,207,250,68,
55,183,93,97,35,120,16,138,4,95,115,209,231,58,131,79,154,40,208,151,139,244,83,131,244,211,189,244,155,10,228,68,129,190,180,156,217,248,50,206,62,94,228,185,171,187,57,50,108,34,220,175,35,60,180,192,
120,165,66,2,252,175,155,72,17,170,49,132,6,193,21,11,150,103,159,220,205,177,135,10,244,227,35,225,98,140,247,175,229,232,127,51,205,114,163,197,213,126,114,136,126,106,25,103,31,31,230,197,231,245,243,
133,187,183,197,55,21,77,75,20,132,105,0,131,214,224,211,4,192,208,226,43,122,186,18,158,112,76,7,199,255,52,28,252,203,68,145,181,77,195,188,234,171,157,124,217,62,249,240,51,68,154,26,25,15,240,155,
103,119,145,147,133,0,36,70,139,244,147,203,232,202,67,65,192,227,67,244,155,135,2,171,48,58,68,183,185,159,99,15,22,248,119,239,201,179,167,91,35,83,33,241,195,80,52,109,48,22,245,56,44,240,134,209,84,
71,160,99,32,220,123,231,28,47,63,191,151,139,27,139,244,165,21,1,196,76,244,255,215,131,11,63,94,88,237,75,69,114,122,25,179,137,17,222,120,89,145,7,237,159,82,145,80,213,210,104,18,98,25,160,17,239,
64,109,11,33,106,34,249,25,77,13,12,19,107,249,186,87,183,243,129,159,15,208,151,134,201,201,97,186,241,97,222,125,93,31,143,56,56,165,181,218,162,61,45,230,50,210,68,151,126,177,147,156,26,166,159,24,
36,203,69,250,241,33,178,220,71,95,234,39,39,151,147,147,67,244,165,65,114,178,72,63,81,12,254,106,115,145,127,188,115,128,135,190,50,79,8,130,233,68,147,82,170,211,72,245,192,56,132,0,18,25,139,58,226,
76,216,153,87,30,240,226,148,55,95,209,207,234,216,48,253,68,63,125,169,64,142,246,255,231,131,11,150,123,86,185,137,2,89,94,78,63,81,224,186,219,138,124,207,235,59,216,209,30,204,143,54,222,76,210,116,
196,176,75,216,1,104,52,105,117,31,4,203,125,118,205,241,182,171,139,204,198,135,232,203,195,244,165,34,215,223,221,199,19,143,110,103,127,167,105,176,222,77,58,8,241,16,37,248,15,40,255,249,139,93,244,
99,5,250,177,34,125,105,48,104,83,212,68,63,218,31,0,197,248,178,32,164,177,34,93,41,162,192,210,114,86,54,22,120,245,37,125,220,103,247,52,34,75,211,212,174,45,24,139,6,107,33,49,132,80,161,138,82,85,
216,158,23,190,243,13,237,124,224,167,5,102,227,69,102,163,69,250,209,62,186,255,12,112,145,109,234,89,229,198,139,107,89,30,164,47,13,113,253,61,203,248,233,19,186,184,108,40,137,154,17,252,141,49,54,
222,236,250,13,111,245,59,245,64,212,196,248,72,185,98,200,240,242,47,117,114,246,177,21,161,136,164,52,192,177,7,139,252,226,169,157,220,118,88,27,140,128,105,49,57,79,9,70,97,152,203,25,126,227,243,
221,193,180,77,14,6,40,62,89,164,159,24,160,47,21,232,75,43,131,169,43,13,211,143,15,208,151,138,225,99,50,10,116,178,159,126,124,128,179,27,150,241,194,51,123,184,93,244,121,70,109,243,185,91,181,87,
155,8,84,27,136,181,121,17,87,14,27,158,118,124,39,199,238,47,210,213,127,87,185,184,214,109,234,251,223,18,150,252,219,33,117,113,173,73,117,21,188,98,113,62,197,85,215,78,225,83,231,204,225,145,191,
100,160,196,31,68,128,34,49,94,140,247,92,0,66,0,102,80,49,32,8,81,3,1,209,209,6,124,248,253,29,248,187,247,229,48,56,164,200,22,0,239,28,174,249,65,21,103,127,121,30,191,123,192,133,159,36,0,25,127,38,
8,17,133,64,224,233,208,153,55,56,224,229,6,111,121,93,14,47,122,129,226,183,191,172,226,166,91,29,246,216,213,226,229,251,39,216,115,239,4,198,8,84,50,16,10,32,5,180,10,201,12,104,13,68,171,160,147,224,
50,125,2,176,2,152,20,112,130,201,209,26,62,241,217,5,92,113,213,2,102,23,21,10,15,130,32,1,137,239,147,245,247,72,129,0,16,33,124,124,198,240,240,196,158,59,24,124,232,216,118,28,254,166,54,228,186,195,
251,240,166,246,83,219,91,122,197,191,79,188,179,177,119,117,48,25,35,116,155,7,121,203,154,62,30,240,226,60,173,9,190,197,196,172,104,157,115,107,189,225,82,143,65,226,13,51,106,153,194,178,61,159,240,
45,135,228,249,240,157,67,193,153,79,246,211,151,138,252,197,247,251,248,186,85,109,193,239,52,76,91,29,6,199,223,17,209,85,119,167,225,201,199,116,243,177,95,23,233,75,67,228,216,32,89,238,231,5,103,
117,6,198,64,149,43,87,244,243,195,199,238,204,159,95,211,207,234,198,33,250,82,63,253,166,2,221,196,96,51,216,157,92,22,255,94,247,85,253,100,169,64,63,53,68,63,49,196,108,211,16,127,119,91,129,7,190,
34,79,53,193,164,65,181,225,151,20,182,229,249,208,66,59,213,45,74,176,22,169,21,190,242,121,41,127,120,233,64,48,127,147,195,244,155,250,254,239,226,171,202,166,193,213,126,98,197,90,63,177,140,126,250,
37,252,227,29,219,242,125,71,238,194,174,246,186,83,77,90,136,74,217,66,56,102,73,80,88,207,140,230,82,195,23,61,63,229,29,215,21,152,141,175,160,159,26,161,47,109,207,7,110,31,228,177,71,118,176,45,167,
13,64,1,177,225,35,166,192,37,94,2,163,202,193,62,195,223,222,214,31,76,212,120,52,85,165,126,250,82,31,191,252,153,206,152,90,15,112,94,69,217,157,23,126,226,216,54,102,27,151,209,79,20,200,82,31,57,
62,64,63,62,24,97,249,72,64,131,229,129,32,236,137,193,96,30,203,131,116,155,135,233,39,10,92,120,114,152,55,125,167,159,187,239,146,139,126,87,98,92,21,252,80,61,149,191,37,121,187,101,186,164,171,83,
249,150,131,243,252,205,79,134,232,54,15,209,77,140,208,253,239,22,199,112,83,255,42,55,54,180,214,79,12,145,229,65,110,248,253,16,79,61,174,147,219,141,228,91,114,55,245,27,98,154,116,127,227,193,76,
243,214,55,50,161,202,231,174,204,241,251,23,247,4,136,58,53,76,95,90,198,241,7,11,252,199,19,59,217,223,165,180,241,118,214,153,0,89,242,102,151,166,26,182,27,73,89,221,48,76,55,58,64,63,214,75,142,13,
211,141,246,147,227,3,60,235,180,182,200,162,71,167,46,129,143,219,113,27,203,242,159,2,88,96,169,63,194,243,254,0,32,198,139,1,137,77,70,13,154,30,166,159,40,146,227,5,250,242,16,221,68,129,110,115,129,
126,115,63,39,31,25,228,121,159,236,226,200,80,68,173,210,154,223,106,106,125,61,188,8,154,103,40,10,154,70,154,68,184,98,153,229,39,143,239,225,227,247,212,227,191,149,172,60,209,255,175,107,85,237,137,
226,90,63,190,130,190,188,156,147,15,45,227,151,63,211,203,157,86,180,148,75,161,94,153,99,150,212,12,44,69,61,26,85,61,124,110,160,95,249,133,127,232,101,233,15,131,244,163,203,233,203,67,156,223,80,
228,37,95,236,229,243,118,173,59,253,100,105,242,46,30,112,119,119,47,141,177,45,41,133,0,127,247,220,77,153,109,30,164,31,31,12,65,235,120,145,110,124,132,190,92,228,5,103,118,18,80,90,99,27,240,89,20,
28,238,87,62,246,187,161,192,245,77,12,69,192,80,8,63,163,84,160,31,31,166,31,143,130,154,140,230,112,188,159,156,46,6,164,57,57,66,55,218,23,16,226,104,145,27,126,215,207,183,191,62,199,124,123,11,133,
212,194,88,212,47,170,52,114,87,117,168,46,13,46,82,69,185,243,142,57,126,253,115,189,156,122,36,188,15,78,253,43,140,133,27,31,166,159,30,225,143,191,51,200,23,239,150,180,4,158,91,154,182,102,37,142,
181,185,37,17,58,196,210,26,97,103,135,229,219,223,216,206,71,126,19,222,36,203,195,244,165,17,222,242,189,110,30,186,127,59,141,154,70,188,243,180,249,157,167,176,212,205,20,195,155,95,147,210,111,44,
70,120,61,64,63,218,207,108,83,145,139,79,20,120,209,231,122,184,253,138,28,123,122,18,166,86,27,156,156,177,202,7,111,47,4,161,142,70,51,89,30,36,203,131,172,61,62,28,168,163,241,1,250,201,33,186,177,
40,252,201,200,90,148,138,244,83,203,233,199,123,66,220,53,22,4,155,141,142,112,221,207,123,185,255,75,242,76,109,100,39,68,26,244,82,64,175,104,48,252,168,167,89,96,130,63,139,255,182,70,249,146,61,19,
222,251,179,101,244,51,5,110,41,23,187,4,234,209,3,53,193,37,151,207,225,151,15,56,0,6,128,11,113,28,44,72,223,64,88,170,0,233,225,28,91,80,142,64,13,177,207,222,57,124,113,117,15,246,123,177,2,137,1,
88,193,253,191,171,225,252,139,170,184,226,7,53,204,47,58,8,21,172,251,217,37,47,13,102,55,126,58,160,186,165,95,163,106,241,187,223,103,248,237,253,196,67,127,88,192,159,54,2,213,57,143,39,54,19,103,
158,220,142,123,127,209,141,185,74,130,233,114,5,191,189,151,248,243,250,12,247,62,80,69,146,100,0,21,84,11,241,0,50,1,21,48,237,4,189,2,154,64,152,65,172,2,62,107,254,94,85,160,86,131,104,39,188,171,
132,71,116,30,106,42,216,125,215,4,55,95,157,226,151,119,101,248,192,169,51,184,239,193,12,84,128,94,32,116,128,24,16,190,249,179,68,65,8,72,9,176,80,4,142,14,119,175,19,252,234,87,115,216,109,175,54,
112,182,103,181,116,78,173,126,90,33,57,245,48,73,14,213,42,32,176,32,29,4,10,192,67,197,194,209,67,68,65,122,120,223,224,29,34,220,36,118,88,110,112,214,25,157,120,237,171,83,228,58,195,247,109,126,162,
130,111,95,86,193,217,95,157,199,228,36,224,226,247,17,190,1,93,151,70,2,108,252,91,141,133,119,213,167,252,223,15,111,173,224,71,107,171,152,93,244,160,23,16,14,34,2,66,48,54,33,104,239,52,104,239,246,
24,44,38,120,206,115,25,5,223,14,32,11,0,209,17,72,21,200,124,227,94,168,119,160,17,192,1,128,3,196,6,56,46,22,200,106,160,36,0,50,132,63,52,40,117,205,1,70,160,214,97,191,151,91,220,121,83,7,190,251,
61,224,147,95,156,193,166,205,4,68,225,61,163,44,52,94,114,6,161,9,160,2,128,14,164,5,196,195,106,12,5,144,7,48,245,244,154,164,96,136,35,104,65,44,2,241,240,141,81,100,89,173,33,148,214,48,75,68,208,
211,163,248,204,199,218,113,196,17,57,244,246,132,255,159,157,172,225,154,107,42,56,247,162,69,172,251,147,15,196,80,170,240,53,192,123,7,168,66,60,91,4,20,181,84,20,136,26,235,125,83,64,34,18,180,74,
128,133,69,143,182,30,193,11,158,107,176,247,110,6,207,125,78,27,86,44,83,12,23,13,54,111,118,56,229,180,50,6,186,21,219,239,144,199,202,109,128,109,183,87,244,245,10,146,124,10,86,1,152,12,200,42,225,
48,180,10,100,22,84,23,78,77,0,129,130,25,163,160,28,96,130,134,193,43,96,20,144,12,112,10,209,20,52,10,117,10,100,14,237,237,41,142,62,218,227,144,67,122,113,222,151,23,240,245,43,22,80,158,146,248,236,
241,188,40,13,75,17,46,170,133,192,3,12,214,9,52,160,204,63,179,185,131,205,65,232,97,82,13,215,43,68,103,241,246,135,27,207,0,104,64,49,200,167,196,17,175,205,227,31,62,222,134,237,118,8,166,17,52,184,
237,230,42,206,250,210,44,110,189,59,11,1,110,212,244,90,213,3,34,80,181,240,204,0,145,168,169,193,44,8,3,149,141,250,155,106,104,153,143,102,79,33,4,62,120,84,7,62,241,241,28,6,7,5,98,17,221,89,27,96,
61,206,254,204,52,206,186,168,2,21,65,146,44,162,45,85,244,23,20,207,219,213,226,244,143,118,98,183,125,12,68,124,48,111,57,5,42,81,43,96,129,12,128,81,16,89,120,96,147,4,33,57,64,188,130,226,129,90,56,
97,209,248,117,62,4,173,98,125,16,160,203,48,92,80,156,245,201,14,28,245,182,28,62,126,250,28,110,187,203,161,90,9,1,110,211,196,199,243,100,176,2,62,94,80,241,25,104,211,103,22,18,107,139,160,245,152,
155,171,4,35,71,130,148,224,127,192,112,219,163,45,221,251,175,12,46,58,191,3,47,216,219,66,172,5,60,241,192,239,61,206,253,167,41,124,247,250,10,22,171,81,200,148,70,140,71,106,56,114,214,253,29,32,137,
129,149,28,68,29,172,205,97,113,126,14,162,22,94,8,212,252,18,189,173,63,197,225,135,165,40,14,25,0,196,226,162,65,91,90,3,109,5,88,16,228,115,128,154,4,240,25,106,153,160,90,37,166,231,106,120,116,125,
134,93,118,52,216,109,223,62,16,14,80,130,243,53,104,2,80,19,192,87,155,76,130,211,112,52,222,133,103,180,4,157,130,14,225,214,155,92,16,152,67,208,62,47,240,222,66,145,129,170,64,106,128,76,176,235,174,
9,174,251,110,14,63,187,125,17,239,254,240,44,158,220,232,225,24,217,137,200,162,104,131,247,17,228,218,4,176,10,81,121,26,47,93,255,71,162,128,181,160,10,68,195,141,14,63,44,216,84,21,27,109,43,112,230,
169,237,120,225,190,41,20,196,134,63,205,227,148,83,38,241,178,67,202,184,248,234,42,230,171,129,64,9,182,163,245,230,176,161,17,170,30,98,0,56,135,44,171,161,86,35,22,23,29,40,130,142,206,46,236,180,
227,174,1,160,136,137,119,73,1,16,133,30,139,109,70,12,170,179,10,214,20,121,88,208,19,62,179,16,147,97,177,198,96,154,36,106,61,24,237,191,96,221,253,14,82,205,26,135,130,68,64,42,224,170,160,55,80,8,
36,115,193,220,42,155,110,208,121,208,71,170,71,21,96,6,100,14,98,18,192,57,64,29,196,134,103,135,7,224,61,224,107,128,203,96,52,195,170,151,91,188,225,149,73,112,119,13,154,203,7,51,40,245,136,208,163,
230,4,116,0,179,108,43,230,206,17,66,130,222,71,19,23,253,131,196,59,28,111,26,65,228,173,2,74,108,216,32,120,211,123,231,113,207,189,25,136,40,92,15,136,18,222,55,213,58,128,139,224,228,33,14,222,27,
88,43,112,222,129,240,80,2,30,53,16,30,51,83,147,152,155,157,9,151,5,25,84,109,228,198,4,43,71,4,3,3,128,175,230,0,153,131,23,15,69,62,240,106,53,131,44,154,70,42,1,95,55,209,2,1,241,240,227,192,220,108,
21,237,38,220,84,49,30,226,227,21,18,5,211,28,144,85,163,226,71,83,166,129,175,19,35,225,240,171,237,128,89,132,8,224,107,30,2,3,250,160,117,225,114,24,64,29,160,73,40,213,200,8,73,82,84,125,221,146,184,
168,65,1,1,144,132,49,6,142,132,21,7,48,31,4,252,76,154,4,8,168,68,62,175,145,45,117,17,62,134,183,138,232,224,172,1,106,153,3,188,195,196,184,199,125,15,121,52,144,178,143,191,220,11,0,3,129,198,155,
227,162,86,249,232,164,50,100,89,173,241,125,148,32,80,129,129,167,192,185,12,244,241,82,186,42,232,29,72,143,149,43,129,36,15,228,186,22,32,10,24,147,0,166,26,80,158,51,72,145,4,237,240,65,168,148,112,
241,60,128,141,27,171,184,246,186,42,198,75,140,102,184,110,141,53,28,108,86,9,127,194,35,210,165,1,32,248,128,240,64,1,77,21,68,10,207,12,154,70,52,198,12,34,14,176,6,176,241,128,243,9,4,6,144,46,72,
173,10,173,223,222,200,24,7,175,33,16,21,56,231,34,136,16,32,203,226,239,126,38,159,196,12,194,28,22,22,17,25,15,19,108,111,244,77,225,77,57,208,43,146,92,14,200,12,178,26,225,40,80,107,97,68,81,171,101,
65,24,148,224,160,137,150,95,234,159,137,140,2,61,145,111,203,161,90,201,2,48,161,111,129,248,77,68,180,247,206,57,136,53,160,100,128,23,16,213,96,150,85,0,58,76,77,249,134,137,107,32,22,17,88,0,83,243,
196,177,167,207,99,249,151,22,240,170,87,164,120,221,170,4,123,238,149,98,112,196,66,89,3,170,4,76,64,120,84,137,144,93,3,226,68,10,248,12,162,14,168,69,235,194,12,128,133,36,53,192,153,104,52,18,192,
10,80,153,15,208,90,231,1,73,176,232,231,33,210,154,124,8,97,140,42,224,67,208,137,42,21,72,8,170,217,74,48,43,105,188,90,10,208,0,198,65,124,64,67,245,192,82,96,160,0,170,139,128,203,4,2,23,204,86,45,
104,137,170,196,84,130,34,139,106,91,23,240,214,51,38,196,226,194,60,140,201,65,69,81,203,178,6,116,13,142,54,104,90,127,191,1,12,160,142,225,32,61,3,66,244,21,208,8,114,57,194,139,15,218,33,17,143,18,
240,34,72,84,48,63,239,241,240,99,130,63,94,186,128,111,94,182,128,237,87,164,120,201,94,41,14,250,27,197,11,95,156,98,69,17,208,156,0,226,162,185,36,232,93,8,66,157,129,168,192,147,80,35,193,28,194,1,
46,164,63,0,3,58,15,33,1,171,205,160,16,25,52,139,238,34,222,29,81,105,160,58,137,151,41,69,6,48,133,96,97,43,62,9,14,48,14,181,138,15,113,3,91,2,48,70,184,76,15,42,145,75,106,48,121,15,26,15,208,193,
121,129,120,15,10,225,41,48,226,161,98,2,128,136,15,193,250,5,216,90,74,222,87,225,27,172,67,132,221,82,23,165,162,167,75,128,204,129,72,0,13,55,157,94,3,91,194,16,58,8,52,152,105,42,146,156,69,86,113,
240,240,168,102,26,127,142,3,85,81,205,20,127,88,159,225,15,235,29,46,191,137,232,239,6,246,127,81,14,111,58,52,135,55,188,62,129,26,6,4,199,216,144,97,106,128,36,208,212,7,116,26,225,51,181,22,77,166,
64,96,1,113,1,9,74,100,108,96,235,242,14,126,86,0,239,235,6,213,67,20,240,4,196,216,16,110,248,30,0,147,207,224,147,36,104,80,103,187,66,69,32,244,193,189,49,36,179,32,1,2,131,130,164,35,5,164,3,42,6,
206,133,27,149,213,3,82,198,104,128,14,130,16,23,25,171,80,5,140,154,134,249,138,78,44,10,65,3,236,129,128,244,80,85,88,107,26,201,68,64,160,234,49,52,16,133,238,61,80,51,33,234,167,139,126,208,96,161,
18,147,141,245,11,85,117,1,244,68,31,21,126,133,9,161,59,61,250,6,122,208,221,221,9,95,245,216,60,238,177,230,198,10,222,241,247,83,56,231,139,243,240,153,6,56,46,4,146,54,208,89,32,11,108,156,164,237,
128,154,240,57,53,193,44,250,224,147,145,41,196,26,212,85,135,12,38,88,4,80,104,35,226,132,4,8,79,31,206,155,38,5,188,1,182,64,119,186,84,70,4,232,225,156,139,65,168,128,162,241,13,53,45,19,1,32,171,130,
110,49,152,22,117,16,175,49,8,101,212,8,31,77,149,131,247,89,112,236,62,152,10,99,83,88,155,15,53,146,48,77,215,1,193,182,219,175,196,71,78,255,4,190,123,243,77,216,102,187,237,90,156,120,128,239,185,
238,16,71,16,4,180,206,49,85,3,221,131,12,214,250,224,132,85,160,42,112,212,136,46,9,34,139,194,139,149,17,32,86,44,219,1,63,186,235,103,56,251,162,11,240,178,85,47,133,53,22,53,111,240,217,243,231,241,
253,171,23,129,36,11,166,110,113,1,146,246,3,90,11,7,155,205,7,31,171,17,245,65,195,69,166,7,196,3,153,11,234,17,108,27,106,209,228,123,70,58,76,226,165,161,198,203,175,200,169,2,180,64,3,172,63,141,144,
232,4,98,52,154,155,250,45,88,234,224,21,132,17,66,41,160,120,40,9,53,8,15,246,20,223,35,45,102,44,3,196,131,116,200,106,11,200,178,133,72,50,134,131,78,211,20,159,251,210,151,112,251,125,191,198,169,
167,157,140,127,249,233,237,88,255,200,163,200,229,219,208,95,28,136,60,167,194,208,129,66,168,198,24,195,166,1,238,58,133,24,129,115,129,75,244,140,151,4,174,17,56,134,240,193,3,66,236,177,199,78,232,
238,233,193,186,117,247,224,71,87,253,16,71,30,253,54,92,253,163,31,226,180,207,175,134,146,152,175,0,31,252,135,5,220,114,83,22,160,115,170,64,54,21,75,1,226,193,88,129,88,129,248,52,8,78,45,144,56,192,
88,72,106,0,235,163,38,122,228,96,2,210,20,194,24,11,85,5,235,207,83,47,53,224,60,36,169,0,102,107,16,220,10,88,243,17,42,218,224,120,37,228,233,3,226,10,245,10,153,55,64,154,64,225,81,243,64,117,177,
30,3,68,136,221,96,173,125,35,120,11,62,198,63,133,76,149,88,35,240,222,191,59,26,239,125,255,145,200,89,226,142,59,238,196,69,231,158,139,193,193,33,92,118,213,119,240,229,111,127,19,70,45,20,130,133,
10,64,175,96,150,133,36,132,175,5,65,39,2,250,12,139,21,54,64,70,253,119,5,20,21,205,44,5,185,52,143,47,124,237,171,184,228,218,239,96,176,88,196,153,159,62,3,191,254,249,175,145,90,193,223,31,127,60,
78,56,253,99,16,21,76,76,59,28,123,210,44,238,191,95,129,172,30,119,5,162,213,103,12,166,175,154,129,137,15,60,164,3,196,11,192,90,0,13,76,1,73,65,17,212,92,128,223,4,80,171,213,154,214,33,166,224,4,196,
66,166,81,241,182,98,238,234,12,176,167,13,189,85,80,168,154,232,171,162,45,37,144,106,80,103,161,130,53,137,46,157,45,231,207,22,184,29,3,89,176,229,215,105,243,16,69,240,238,163,143,194,105,103,157,
137,196,26,76,79,204,226,228,99,63,6,181,6,23,254,243,55,240,170,215,28,128,231,191,224,121,24,24,42,32,35,48,177,89,32,89,160,95,98,145,28,196,91,208,101,128,17,164,106,162,159,143,232,78,180,129,168,
232,67,176,189,124,155,101,216,115,239,191,194,65,47,255,107,92,117,211,149,40,12,22,113,202,9,167,96,114,108,12,150,21,156,120,234,137,120,231,123,223,5,122,98,253,102,139,99,62,88,194,159,31,35,104,
99,243,140,25,132,230,77,8,128,173,2,198,197,112,160,13,148,72,80,215,20,194,42,96,66,12,21,56,79,129,138,130,100,176,44,244,193,67,81,224,5,200,73,240,107,76,176,21,33,73,21,2,27,236,184,85,72,98,0,31,
99,150,134,179,215,144,131,49,14,52,6,243,89,22,110,118,163,162,167,213,212,5,152,105,140,217,226,211,140,255,107,240,170,151,191,12,103,157,119,46,186,146,20,181,90,134,79,158,120,50,158,28,221,136,139,
191,123,5,94,115,208,254,72,161,40,244,118,99,255,3,94,9,130,152,174,0,16,27,82,6,90,13,38,20,12,66,113,68,121,190,22,189,91,22,106,99,213,135,88,15,12,254,131,130,191,57,232,85,104,79,243,112,168,98,
223,189,247,193,101,215,94,134,241,177,205,56,243,140,115,33,76,97,85,113,198,231,62,131,253,255,230,175,161,168,225,87,247,85,241,254,15,207,97,98,212,3,206,130,213,57,176,134,192,211,65,128,154,130,
190,10,205,230,66,30,74,98,172,70,5,88,3,171,81,111,24,226,193,214,204,139,103,180,38,222,3,105,192,2,88,76,183,34,36,182,131,73,2,171,130,84,45,186,187,58,35,217,23,156,54,225,3,80,64,60,36,24,228,196,
4,40,220,144,128,46,213,20,16,181,90,181,25,152,70,189,3,128,189,246,221,29,231,93,126,9,114,109,9,60,50,148,74,37,252,233,79,143,227,251,55,221,128,215,28,184,63,44,21,6,128,65,21,7,28,176,63,196,19,
119,222,185,24,2,7,134,24,46,64,166,144,188,3,82,100,153,54,64,79,16,141,9,161,68,132,187,170,192,107,223,252,70,0,149,80,78,2,135,231,239,187,39,46,184,248,43,24,221,248,103,212,178,26,114,52,232,239,
106,199,21,87,173,193,126,171,246,3,1,252,244,151,21,156,112,82,25,179,85,2,54,131,0,112,179,132,175,198,132,177,213,96,186,36,240,124,52,136,254,70,161,169,32,171,51,32,117,139,211,56,158,16,244,67,20,
134,18,193,208,214,132,36,10,169,5,233,214,50,135,114,169,132,204,213,66,210,42,30,190,50,188,217,44,3,188,243,48,226,144,152,102,190,164,37,226,137,41,134,86,31,165,141,76,235,78,59,239,132,43,111,184,
22,43,151,45,71,34,6,22,9,6,6,251,113,237,173,215,226,37,47,216,29,53,87,131,99,5,85,132,252,211,254,175,62,16,237,221,157,248,253,31,128,185,105,2,222,2,174,10,100,30,226,124,184,141,10,228,108,56,4,
177,225,72,234,153,99,37,225,61,48,52,52,132,189,247,217,51,92,52,81,88,40,44,115,56,240,128,87,224,155,87,174,129,77,13,68,0,131,20,61,237,93,184,232,171,95,197,138,149,203,1,2,87,220,144,225,228,147,
103,80,93,36,144,8,76,206,132,203,106,77,64,106,185,58,121,108,195,80,22,38,64,77,224,22,44,188,143,40,86,12,20,33,48,18,181,16,53,17,140,4,34,87,188,0,182,186,53,33,213,0,227,81,173,212,130,141,247,26,
35,110,31,136,81,4,223,233,73,228,12,160,190,130,42,21,181,44,250,171,58,63,213,240,63,145,125,136,12,68,248,183,65,79,95,31,206,249,242,5,24,26,26,134,208,199,44,240,34,92,117,30,22,139,168,102,11,240,
181,10,42,217,66,208,62,205,227,246,59,111,135,113,14,15,254,177,138,223,254,218,1,222,135,184,66,109,4,149,129,157,150,4,48,170,96,157,34,140,49,10,69,160,170,40,77,150,112,251,218,59,33,72,195,97,1,
80,201,32,48,232,208,192,253,73,164,109,148,11,216,110,251,21,248,193,45,55,161,56,92,132,120,143,139,175,154,197,5,95,90,132,175,217,232,151,125,72,195,123,1,51,11,216,44,36,53,43,38,92,80,147,64,83,
11,27,141,139,198,44,114,160,177,0,149,70,209,81,212,70,15,44,110,205,39,121,7,74,13,121,27,133,162,49,53,190,164,14,2,112,142,200,84,0,77,144,111,51,48,18,224,56,233,90,128,67,19,209,213,181,71,132,232,
232,104,199,101,87,94,137,253,87,237,143,36,240,54,168,98,14,115,139,11,200,231,186,209,145,47,32,49,121,180,231,187,145,75,122,224,32,184,231,183,247,226,228,163,63,128,153,133,5,212,0,252,227,23,167,
225,107,33,128,150,140,128,241,193,119,122,69,101,46,18,150,145,105,14,207,98,96,76,16,216,66,165,138,19,254,238,195,248,237,175,127,133,26,124,188,82,161,58,85,224,98,141,170,129,133,133,74,30,22,22,
187,236,176,61,46,248,234,5,72,242,57,120,90,156,246,133,105,124,253,203,179,205,90,80,113,33,97,106,130,127,10,254,49,210,70,82,3,178,69,100,89,22,41,77,19,46,178,87,0,25,232,125,131,151,204,170,129,
92,21,221,154,38,37,2,169,17,85,231,91,10,66,248,148,208,199,24,192,47,122,136,102,88,156,171,53,185,178,22,68,215,128,216,117,2,85,0,49,138,147,86,159,142,151,191,98,63,36,49,129,103,145,162,141,109,
168,101,33,1,230,152,33,162,2,24,122,108,252,243,227,56,246,109,71,162,52,53,27,82,31,4,110,190,203,227,194,127,170,192,103,2,106,72,81,192,215,0,33,58,58,162,118,196,184,4,48,216,107,87,193,239,111,41,
224,181,7,38,16,79,60,241,228,6,252,253,123,62,132,13,79,142,193,195,194,52,8,26,13,44,60,42,129,184,173,91,5,102,56,232,224,87,225,194,75,254,9,169,181,168,121,224,148,207,207,224,198,31,86,64,166,209,
140,215,34,214,183,112,46,1,172,143,32,65,0,163,144,4,160,214,211,64,178,196,51,8,234,164,110,2,168,13,89,230,103,134,224,4,109,157,133,85,120,31,233,32,160,73,229,68,138,40,215,17,19,102,198,180,68,188,
186,69,209,72,184,165,16,69,154,203,225,172,11,207,195,7,63,250,247,209,240,5,159,165,49,216,28,232,234,3,96,97,37,129,129,131,67,21,27,70,55,224,125,135,189,29,15,63,178,62,34,166,96,34,28,137,207,94,
52,135,155,111,137,122,224,215,180,12,206,0,0,32,0,73,68,65,84,124,131,189,158,158,115,161,176,36,178,17,219,44,243,248,231,243,250,177,203,78,25,190,115,81,47,14,218,63,15,122,224,247,247,173,195,9,199,
125,4,229,242,52,170,240,112,172,70,158,141,16,164,112,145,72,174,167,47,9,135,183,188,229,205,56,97,245,137,16,47,152,154,35,142,57,121,6,119,252,172,26,11,117,124,208,18,103,96,146,42,32,14,154,11,1,
47,144,33,167,190,145,145,173,211,107,245,114,129,122,153,187,181,14,172,57,184,74,101,43,140,3,21,200,82,204,47,4,18,82,90,24,108,210,65,53,248,23,239,17,73,77,129,203,60,124,164,88,26,252,31,154,14,
84,36,252,223,209,31,252,16,222,117,204,209,48,112,176,8,83,21,20,38,248,75,42,92,136,120,224,99,90,189,52,187,136,147,142,63,17,119,253,102,93,64,106,145,15,132,134,52,200,88,201,225,240,99,203,248,254,
247,107,96,18,131,76,10,172,9,197,252,219,60,119,23,108,59,98,240,195,75,11,216,99,47,7,175,138,92,187,224,194,179,114,216,97,165,194,11,112,195,245,215,227,163,199,127,4,213,138,131,147,44,62,143,143,
194,114,177,52,199,65,37,137,207,12,124,248,195,199,227,3,31,59,14,74,193,230,113,226,216,143,149,241,232,195,26,210,18,62,102,116,197,4,196,73,13,159,179,9,230,43,245,234,32,70,246,46,230,141,13,64,9,
103,153,121,11,168,133,201,97,107,220,157,66,148,200,105,208,0,209,22,13,170,243,113,240,48,70,35,36,207,144,57,134,0,45,218,255,64,196,134,195,36,67,226,240,176,163,222,141,51,206,56,13,29,32,108,180,
254,34,38,106,83,224,213,76,236,146,16,100,152,175,214,112,218,135,62,138,31,222,112,51,210,52,65,104,3,10,182,188,175,211,224,235,95,232,68,103,187,162,60,171,120,255,201,51,248,236,103,230,81,91,32,
160,6,14,30,214,8,246,218,225,49,220,241,163,62,236,177,71,184,165,27,214,103,184,228,107,179,216,110,135,4,215,127,171,31,203,11,22,10,197,85,223,251,30,206,59,231,92,120,159,128,226,224,80,129,80,98,
29,134,130,176,245,144,25,86,128,54,107,240,153,127,252,52,222,124,228,97,32,129,135,214,123,28,241,222,50,54,60,30,125,75,230,67,86,87,53,150,113,132,228,103,146,218,70,194,175,97,235,68,160,62,166,97,
196,35,241,213,224,195,152,253,43,192,193,59,100,14,209,169,201,83,124,18,99,59,135,198,100,152,209,152,117,109,112,80,33,86,170,115,159,127,115,200,235,240,133,11,191,128,182,84,96,161,104,41,65,1,225,
224,145,33,36,18,12,84,20,85,79,124,229,156,47,97,205,101,87,194,104,14,181,44,131,119,225,82,136,10,94,176,167,197,187,143,108,195,101,95,237,71,79,55,48,53,163,248,212,133,139,120,211,81,179,184,251,
23,21,108,187,34,143,53,95,235,198,154,111,228,49,50,20,82,3,163,155,128,99,79,89,192,183,110,200,32,214,99,231,221,45,46,56,167,27,249,148,112,14,248,236,234,207,226,178,139,175,8,57,63,0,139,110,22,
179,149,49,84,177,208,164,111,226,37,34,21,121,181,56,247,188,115,240,162,191,126,1,84,137,223,222,159,225,253,31,156,198,228,68,136,121,68,34,115,46,62,192,225,154,131,198,116,71,184,232,129,145,97,12,
81,196,7,6,223,228,76,64,171,57,110,45,152,53,128,55,81,0,210,224,236,36,82,251,117,96,224,51,32,171,6,139,109,21,45,112,187,94,11,17,56,169,61,246,221,11,231,95,114,33,186,58,18,36,145,125,14,78,218,
53,180,136,112,80,24,44,86,167,80,241,85,92,252,213,75,112,198,25,159,198,130,115,112,181,185,120,225,162,127,243,130,93,119,6,68,29,94,119,96,130,159,124,175,11,219,109,171,240,94,112,227,207,107,120,
221,81,211,120,253,129,9,14,61,164,13,86,66,137,212,67,15,84,241,150,119,207,224,150,95,120,60,242,72,134,242,88,6,248,10,222,240,26,197,69,95,236,70,154,11,23,252,212,143,159,140,181,183,221,141,5,198,
192,82,21,149,218,92,244,81,6,9,18,152,122,49,14,12,6,123,251,176,230,154,239,98,183,61,119,71,70,226,230,59,170,56,245,180,25,64,93,184,200,62,67,163,54,32,5,42,181,122,242,50,58,6,106,44,69,48,80,35,
16,37,170,46,66,250,69,243,204,66,114,89,59,104,129,36,141,69,124,145,103,170,215,134,197,84,39,172,1,84,107,17,20,16,182,94,42,30,83,229,2,131,237,119,220,25,87,221,112,29,86,22,6,145,135,129,129,141,
249,148,224,63,92,20,15,65,204,187,73,32,201,227,182,91,110,199,167,78,61,21,153,99,12,68,17,211,27,205,128,120,255,253,242,128,75,224,125,13,47,120,94,30,191,250,113,1,71,190,33,69,123,222,97,98,26,88,
156,119,80,159,97,126,129,184,252,178,57,28,120,216,60,110,255,141,135,203,60,198,74,192,196,68,12,60,189,195,17,111,72,241,193,163,219,1,2,51,51,51,56,238,157,239,198,3,191,126,8,198,164,200,165,61,200,
153,78,0,105,188,158,62,50,6,33,243,74,16,131,125,189,248,218,37,95,65,119,111,23,156,247,248,217,47,171,152,158,146,16,18,192,130,226,0,155,0,146,193,216,136,224,24,17,111,108,66,203,50,15,71,70,121,
106,64,132,91,45,233,50,53,72,230,145,85,67,58,32,96,120,105,86,143,70,91,154,81,144,166,128,136,71,182,104,26,57,170,58,131,79,241,56,228,160,87,99,160,39,143,80,66,72,100,240,168,69,222,202,177,130,
249,218,44,12,66,57,115,162,157,88,247,155,123,241,190,35,222,129,169,8,181,3,9,233,225,189,95,194,98,220,119,47,64,235,32,18,138,25,187,242,192,215,191,208,131,159,95,61,136,55,29,108,225,9,252,226,78,
197,17,239,156,199,209,39,47,224,137,177,90,76,246,9,94,188,143,197,224,144,130,154,128,48,80,117,248,236,234,60,222,123,120,2,18,120,242,201,205,248,200,7,62,136,169,241,89,8,18,164,218,142,140,179,88,
224,108,200,184,198,188,47,35,107,96,145,199,158,123,238,129,125,247,221,7,2,160,52,149,97,110,94,193,170,9,116,143,207,133,226,74,159,132,16,132,205,128,222,24,137,228,53,67,222,9,30,169,77,194,223,221,
86,242,73,106,107,160,7,42,89,48,125,173,44,65,157,230,17,6,0,81,137,105,101,53,190,73,166,70,244,165,36,70,182,223,22,222,213,32,8,230,129,0,84,131,23,130,8,242,182,29,14,25,170,240,248,203,134,191,224,
131,71,31,139,241,82,57,94,6,223,40,68,169,3,151,250,159,103,254,211,20,46,60,111,1,181,153,88,155,110,9,155,247,216,107,111,193,154,139,187,113,195,79,42,120,243,49,211,184,238,238,74,48,84,198,194,40,
241,146,231,167,184,244,43,5,116,247,152,96,82,210,88,3,14,131,115,62,221,141,151,188,40,5,224,113,207,111,214,225,237,111,61,10,19,165,233,248,116,30,169,228,98,48,33,48,76,225,184,24,89,200,0,207,187,
6,122,65,10,38,167,129,169,82,6,149,64,4,4,16,80,9,212,21,125,180,72,129,230,210,152,70,23,212,107,49,128,90,77,66,86,193,251,173,249,36,64,210,12,234,93,168,244,137,185,107,239,253,18,21,204,229,5,237,
38,116,27,212,124,75,199,74,61,109,173,130,222,129,62,228,218,58,33,204,64,212,96,160,112,240,48,16,44,102,11,200,80,133,67,13,27,71,39,112,228,107,15,199,189,235,238,139,116,137,70,228,103,98,8,224,90,
186,44,4,139,25,240,137,179,231,112,250,89,51,168,16,48,54,11,206,90,67,241,252,198,49,131,201,41,135,188,77,26,133,104,135,253,109,59,110,184,162,128,109,71,178,102,34,51,11,232,85,45,208,213,169,88,
115,113,63,246,218,37,212,247,253,236,231,183,226,211,167,172,134,115,68,42,109,33,155,26,153,11,39,243,176,146,66,145,193,67,97,105,145,38,161,222,33,115,64,37,243,161,250,71,21,194,20,132,1,109,168,
11,105,196,68,240,168,86,29,178,44,88,12,85,5,85,209,158,35,164,221,133,148,213,51,198,73,94,193,76,2,93,226,227,91,172,11,199,107,163,164,223,103,132,36,22,168,85,81,169,154,122,53,110,75,133,42,208,
158,90,132,153,100,161,196,218,195,69,248,237,209,101,187,144,74,138,106,45,193,201,31,62,25,235,238,251,93,252,61,62,212,215,129,241,77,213,25,139,32,188,149,195,6,93,29,192,66,13,248,194,37,51,120,219,
59,203,248,243,227,49,35,42,30,68,21,243,181,12,46,171,161,90,169,224,57,43,18,124,243,236,46,92,252,249,78,116,119,47,2,226,240,228,163,30,174,86,239,110,208,88,172,153,97,120,168,130,203,191,210,141,
193,1,192,26,139,139,47,190,20,159,58,237,51,88,200,42,240,162,145,48,18,40,242,48,72,17,240,108,160,111,218,115,249,70,253,250,98,53,9,244,80,213,131,172,134,75,87,49,200,217,102,141,133,72,128,221,170,
241,82,251,144,106,167,212,98,19,129,221,122,113,164,35,113,192,43,15,198,54,219,239,80,31,46,182,132,230,169,167,27,72,15,36,54,146,147,173,93,230,4,61,208,222,61,16,76,35,20,185,8,23,12,18,132,178,200,
42,102,42,21,124,252,239,62,130,235,190,247,61,56,154,64,239,67,154,56,223,55,15,50,40,180,195,91,94,151,199,93,55,245,97,151,29,19,208,3,55,222,150,225,192,55,76,226,252,47,204,6,248,155,229,176,56,7,
244,116,8,62,250,238,28,126,122,109,39,142,122,7,96,59,51,0,130,117,235,18,188,251,132,105,84,107,2,209,26,80,35,144,89,120,171,128,75,177,243,174,6,151,125,165,7,221,93,22,80,193,151,191,244,21,92,253,
253,27,65,212,0,212,34,201,236,65,212,98,40,168,240,66,244,245,119,133,154,9,33,230,74,149,112,76,9,129,196,7,20,219,158,97,113,54,214,218,48,166,125,234,111,209,214,9,0,143,5,103,1,87,11,236,254,51,9,
105,113,166,27,6,130,219,126,122,51,158,124,226,177,64,63,210,69,24,222,164,126,108,10,168,10,224,4,213,26,35,137,138,70,237,182,170,162,56,216,143,68,234,122,107,2,157,227,67,9,175,131,197,165,223,184,
20,151,93,114,73,96,52,26,25,202,165,193,51,90,170,106,8,193,72,63,176,243,206,138,219,111,232,195,91,95,155,135,167,224,145,39,4,31,63,103,14,251,31,58,131,11,206,159,194,123,222,102,113,223,47,122,112,
246,153,221,40,22,61,188,40,22,103,29,190,121,73,5,175,57,98,12,15,62,88,195,204,28,193,44,5,146,28,96,1,213,80,207,205,140,216,255,37,41,190,242,217,94,192,59,44,86,102,241,225,15,124,8,55,221,184,22,
62,94,48,95,207,17,33,109,0,165,29,158,251,87,161,193,0,130,201,249,186,223,112,128,11,150,68,106,161,112,146,190,149,215,140,127,58,15,231,9,208,32,159,100,225,253,102,91,225,238,242,29,147,160,35,44,
9,87,243,161,172,43,194,198,122,209,62,64,100,53,129,73,5,208,26,2,178,108,97,37,224,209,209,209,133,238,158,78,100,49,109,28,234,179,51,100,146,129,34,184,244,210,239,224,212,143,157,132,204,249,122,
26,44,26,19,52,128,67,139,136,64,42,140,40,6,7,66,166,184,187,203,227,91,95,105,199,215,206,110,195,115,182,21,120,47,120,224,209,26,78,58,167,138,29,182,55,88,182,34,137,89,83,226,225,251,128,227,63,
94,193,251,63,49,141,209,201,12,51,11,196,66,133,161,71,73,43,241,119,229,66,61,92,10,152,116,17,111,120,51,240,169,143,182,67,40,152,95,152,193,199,142,251,40,238,123,232,17,72,196,116,225,185,22,3,3,
41,25,134,86,44,107,248,186,63,175,15,157,17,144,136,212,24,10,249,69,4,214,182,148,23,215,235,71,90,234,65,52,186,156,208,72,246,140,230,46,80,67,245,130,68,15,141,220,29,27,252,157,136,192,130,240,213,
10,0,3,171,22,198,52,235,189,194,27,155,195,173,55,220,136,223,253,238,247,40,149,167,80,201,136,154,42,84,18,220,121,231,93,248,244,201,167,160,90,205,130,239,129,143,21,178,108,118,59,52,50,188,18,181,
56,164,59,250,250,92,40,0,80,15,147,19,28,253,174,28,238,186,190,7,31,121,95,30,195,131,138,170,139,120,75,136,209,141,14,95,251,102,134,85,111,42,227,210,171,231,81,15,181,166,231,128,202,98,80,110,113,
108,180,179,52,238,119,106,32,36,78,60,177,27,239,120,75,30,89,205,225,177,39,55,226,232,183,30,133,71,214,255,5,85,84,177,136,26,38,231,106,120,232,209,63,224,198,31,223,138,107,215,92,219,40,168,153,
158,174,1,89,13,66,19,250,159,124,128,217,243,11,193,245,44,61,79,192,179,73,17,101,46,16,80,89,201,110,165,130,213,16,190,18,181,199,111,217,171,202,72,201,11,212,122,164,26,174,206,244,162,71,22,59,
30,212,40,188,119,112,158,56,233,163,167,160,189,163,3,197,226,32,118,250,171,93,177,231,62,123,224,57,219,239,128,51,63,243,105,140,142,109,106,249,209,186,69,127,108,235,237,10,49,73,40,239,36,46,187,
178,138,151,190,180,130,190,193,36,210,86,41,250,139,53,124,254,140,78,156,242,225,118,124,247,170,10,54,109,4,174,185,97,30,87,92,189,128,135,255,140,6,234,172,203,254,164,99,59,177,221,14,177,195,195,
40,196,213,194,239,53,62,180,89,42,33,249,69,48,203,225,139,231,244,99,211,248,147,248,241,90,226,15,127,188,31,199,189,235,125,88,245,154,87,226,209,135,215,227,129,117,247,225,241,199,31,199,244,84,
25,213,90,214,152,144,82,169,198,10,103,141,21,189,32,32,57,216,156,52,92,66,235,123,86,149,24,192,6,82,27,234,96,219,170,91,17,18,29,196,40,102,166,107,241,6,107,75,251,74,236,122,16,143,74,77,81,149,
92,168,32,242,213,144,242,5,224,156,107,48,201,36,49,55,55,131,71,215,207,224,209,71,31,197,143,126,116,61,140,104,228,174,154,29,124,91,20,25,63,53,89,28,59,16,40,30,223,255,137,199,196,123,22,112,209,
57,9,158,179,91,7,128,74,56,28,5,250,7,4,31,56,174,13,135,191,107,26,87,222,88,9,66,104,78,207,65,177,79,112,222,153,157,56,252,205,237,33,251,41,62,4,141,141,82,162,4,200,27,96,177,10,152,28,84,129,174,
92,13,151,95,212,143,87,191,177,140,117,247,123,220,113,251,29,184,253,246,59,3,86,85,129,56,198,204,170,64,141,96,229,136,193,142,59,72,44,20,245,96,102,130,111,146,74,8,106,151,92,250,208,136,224,137,
70,231,161,49,73,104,25,50,91,211,36,0,158,38,28,10,4,141,198,6,180,168,168,8,218,82,34,77,66,81,123,206,134,102,48,58,105,144,134,177,149,98,73,159,114,72,232,5,16,107,13,145,185,102,119,251,83,45,111,
147,41,150,88,0,83,47,216,184,237,174,12,7,188,105,28,103,159,210,133,131,95,27,74,162,105,44,196,86,67,127,21,180,238,221,2,203,44,192,235,95,147,226,204,79,116,97,167,93,20,212,106,132,89,33,193,71,
201,194,41,36,0,178,133,144,255,161,0,204,1,166,138,158,94,197,55,206,47,224,245,239,40,227,177,141,139,16,6,114,121,184,215,99,251,29,44,246,220,205,224,101,47,232,192,238,187,18,59,238,64,180,117,214,
173,66,13,176,104,228,192,232,13,128,106,208,156,150,121,68,161,56,52,244,65,45,250,44,212,110,168,110,77,147,2,237,145,239,208,150,26,237,214,225,75,49,237,171,138,196,4,255,52,51,167,160,99,163,174,
44,212,114,215,101,90,231,187,226,96,40,6,45,10,44,187,54,153,243,45,17,15,154,128,5,36,210,36,13,189,76,8,204,242,95,54,19,71,125,116,6,7,94,107,177,250,19,157,216,99,119,15,171,10,24,143,44,115,65,160,
4,94,188,143,197,73,31,106,199,33,175,182,80,27,138,22,89,11,237,149,82,175,184,205,33,192,222,106,22,248,74,171,96,22,217,58,39,208,246,4,123,236,157,225,250,203,219,241,163,91,13,182,219,62,197,30,59,
43,70,70,136,142,158,122,147,157,66,124,232,93,2,98,79,46,5,98,12,192,12,132,129,152,44,74,166,222,3,140,102,15,20,0,120,19,106,132,140,133,110,173,171,130,85,11,239,128,133,121,54,58,84,229,41,237,251,
33,83,237,93,232,180,200,88,219,226,128,155,124,95,154,230,80,169,84,155,166,18,166,81,192,222,58,10,224,233,202,146,201,80,117,234,73,88,81,120,181,56,250,136,14,244,117,3,23,92,188,128,197,69,135,31,
254,212,225,142,123,166,113,200,95,91,124,232,3,121,236,190,103,130,180,211,226,21,47,85,124,224,157,57,28,122,160,65,218,110,3,35,226,21,79,110,200,227,186,27,230,241,222,247,219,80,172,162,65,80,180,
105,163,35,36,116,149,19,204,170,208,54,3,65,5,20,98,215,221,21,187,236,213,25,10,91,76,192,172,160,15,181,13,82,11,212,143,183,96,226,2,181,227,76,108,144,86,192,164,77,129,169,139,13,118,245,26,240,
80,119,23,120,231,200,229,109,141,96,149,92,2,168,194,199,42,33,97,171,223,96,163,18,165,173,61,150,237,18,200,117,228,26,202,64,178,133,123,35,170,213,106,44,142,76,2,163,174,161,248,79,180,21,185,181,
218,69,46,17,116,189,144,112,177,186,8,231,50,36,190,134,51,79,74,113,235,247,59,112,200,43,45,84,61,202,115,30,151,223,84,193,1,135,207,224,224,195,202,248,248,7,58,113,243,247,187,241,198,55,166,72,
58,195,51,186,170,226,154,171,23,113,240,97,99,184,252,7,179,48,54,106,17,67,143,171,32,246,19,193,134,162,35,91,47,39,214,160,25,20,80,210,64,61,37,245,241,110,33,247,131,44,116,36,82,44,152,132,129,
37,98,99,186,66,99,153,156,35,106,213,104,9,26,173,60,117,135,169,117,219,135,106,189,196,123,107,4,43,253,28,68,28,84,29,4,73,51,61,209,82,248,40,16,120,16,198,134,232,123,247,157,58,241,188,189,210,
38,122,110,113,140,140,29,130,62,96,79,40,67,1,161,177,182,209,243,212,138,232,130,41,110,105,130,174,231,166,226,103,238,125,160,6,111,136,23,237,75,92,245,237,78,92,122,110,55,246,217,221,66,20,152,
153,1,126,254,203,26,114,105,45,180,235,211,3,78,240,203,95,214,240,214,163,166,241,206,15,77,99,221,159,136,125,118,202,197,89,9,139,161,207,21,8,67,55,42,129,200,19,113,144,204,3,73,18,106,62,106,113,
156,64,186,16,110,125,102,155,221,35,162,193,108,102,161,63,74,232,64,88,16,73,160,131,16,123,111,53,214,9,10,66,121,92,3,205,198,105,51,245,122,201,90,64,132,91,20,104,109,161,73,62,129,171,121,84,171,
140,12,174,95,2,72,36,38,248,22,230,21,179,179,33,71,184,235,238,243,184,245,234,110,124,234,164,118,116,181,75,36,70,181,81,91,22,106,28,154,188,158,85,19,106,250,26,232,174,201,100,120,200,211,207,73,
140,45,174,79,76,70,192,161,41,172,17,28,121,68,27,126,126,125,63,46,58,183,7,251,189,56,65,106,21,214,88,100,139,192,237,63,7,142,57,126,30,175,58,108,26,215,254,100,17,243,149,0,66,158,187,147,70,255,
152,3,82,3,38,18,2,95,149,192,58,136,9,14,125,49,154,170,154,13,95,155,217,0,74,52,54,47,75,26,4,164,2,216,48,240,144,222,132,194,253,170,139,37,110,33,209,233,22,51,100,153,141,174,163,217,159,165,177,
198,62,180,102,25,228,242,4,189,121,74,59,230,22,37,93,0,105,195,23,214,243,67,75,38,146,4,181,156,91,116,56,230,248,57,220,241,11,143,172,38,232,234,54,56,245,99,121,252,234,230,33,188,243,109,249,208,
48,102,19,24,147,194,72,44,34,33,65,81,168,42,156,91,90,64,217,82,68,17,5,172,45,15,104,98,243,0,240,248,19,85,60,178,222,5,68,102,0,136,67,91,46,195,209,135,43,110,251,65,7,238,249,233,0,238,186,171,
138,3,222,60,133,215,189,179,132,139,215,44,96,97,161,209,23,128,182,28,241,226,231,105,40,139,214,44,222,116,31,102,9,137,0,129,131,13,111,220,70,74,204,2,240,139,64,90,175,240,1,196,207,135,110,190,
122,28,148,217,152,154,136,93,239,54,84,15,137,179,88,247,47,138,119,190,107,22,107,239,154,223,130,77,97,104,207,129,15,120,12,14,14,9,196,70,48,243,204,169,138,80,228,152,101,140,93,228,210,72,95,51,
150,132,214,139,227,127,246,219,10,14,122,91,25,199,252,221,28,30,249,99,6,56,96,167,157,42,184,248,188,54,92,255,173,46,188,112,79,129,203,50,184,40,12,35,166,145,227,175,51,193,75,74,197,154,234,220,
194,19,10,60,92,68,136,138,106,77,112,218,25,115,184,239,183,18,227,14,9,204,129,85,88,171,216,121,87,197,154,235,42,184,227,110,135,153,153,48,109,164,14,119,151,15,43,214,124,179,15,207,123,113,26,4,
35,10,186,88,220,239,235,155,23,34,218,180,213,112,119,114,0,210,42,144,6,84,43,2,192,72,108,122,142,65,178,55,17,168,166,177,213,42,204,157,216,248,88,21,159,60,189,132,215,190,163,132,43,110,92,196,
220,130,223,98,150,5,26,99,122,234,71,96,196,35,172,168,209,167,23,210,252,250,149,171,65,34,35,81,243,30,38,177,193,11,197,22,19,68,21,20,137,133,233,4,230,43,130,111,93,85,197,11,15,44,227,156,115,23,
48,58,26,134,117,188,250,160,4,63,187,97,24,23,127,169,3,203,71,76,28,247,20,72,84,79,223,146,31,106,237,50,143,12,3,217,24,154,212,64,147,36,60,29,20,192,53,183,100,56,244,168,9,124,225,188,10,198,55,
7,248,203,250,40,25,26,164,109,97,44,0,85,160,66,244,246,120,156,112,76,59,126,189,182,15,7,189,214,64,218,5,34,249,216,85,142,70,43,39,88,47,243,5,196,198,25,12,142,33,9,144,230,67,73,130,100,161,144,
135,73,232,65,10,106,23,106,209,37,228,170,230,203,130,239,94,50,143,215,190,189,130,51,254,169,134,13,163,161,40,178,37,242,91,218,220,208,82,232,83,111,43,16,62,3,112,240,210,5,88,3,107,20,237,185,124,
227,150,145,209,118,122,46,57,212,58,171,224,5,40,207,0,167,156,179,128,67,223,90,198,53,87,85,176,48,75,88,173,224,93,111,237,196,186,181,189,56,251,244,46,116,116,212,15,219,55,153,57,49,141,218,33,
128,75,80,15,91,166,152,169,106,44,179,10,112,245,47,155,29,78,250,204,12,94,126,112,25,151,124,99,17,165,241,224,27,232,42,104,75,130,41,45,244,19,39,30,223,137,187,127,210,135,179,63,215,134,129,97,
31,134,97,56,31,204,84,53,148,73,139,15,35,119,224,67,111,144,72,13,116,108,140,57,11,197,239,11,144,26,194,24,0,69,56,196,154,9,190,202,19,52,97,238,196,173,55,86,113,196,187,202,56,250,227,139,248,205,
125,149,70,77,68,104,31,66,179,171,79,234,29,250,108,76,156,81,40,22,124,232,172,223,146,136,105,216,154,249,199,119,92,157,239,152,254,228,220,76,14,123,188,108,51,30,123,34,84,174,120,13,99,253,234,
181,61,205,249,115,205,150,77,212,59,211,197,33,151,10,94,182,151,197,167,78,237,192,11,94,144,135,218,42,84,13,30,124,24,56,243,220,25,172,185,182,2,71,137,116,83,235,236,33,60,13,69,20,250,94,235,217,
100,145,198,120,228,198,247,137,18,59,110,103,240,238,215,39,56,228,111,243,248,241,79,170,240,106,112,248,91,218,176,124,101,61,86,14,232,82,32,160,9,36,48,141,64,170,0,19,23,25,235,136,8,27,183,3,1,
145,81,129,36,139,63,130,33,104,21,23,9,90,1,189,197,3,247,102,248,234,165,243,248,246,154,69,76,205,54,9,154,240,136,126,139,3,175,143,242,105,6,182,2,65,154,40,214,222,52,140,23,237,231,32,153,255,148,
116,143,62,253,192,119,63,53,178,214,149,70,120,221,101,61,124,201,190,245,129,176,97,20,37,90,230,122,47,29,229,105,154,27,188,226,252,84,21,101,91,106,249,158,55,118,240,79,119,246,210,141,22,233,70,
195,164,199,171,47,29,224,243,246,204,181,140,5,197,22,31,242,148,81,161,75,231,127,135,9,140,47,218,55,207,254,222,250,90,159,240,179,122,219,133,143,222,85,136,243,84,227,98,145,210,0,55,63,88,100,86,
46,210,79,15,134,105,145,243,5,250,217,1,114,118,128,126,186,16,63,250,233,103,7,233,203,253,244,51,195,244,11,5,114,122,152,126,166,72,206,246,146,241,235,56,213,71,63,85,36,167,134,56,241,199,34,47,
88,221,203,109,70,148,137,169,15,111,111,153,198,191,100,243,25,150,108,65,171,63,179,66,184,211,246,41,111,94,83,96,173,84,32,103,151,209,207,119,110,125,34,63,103,134,215,250,217,97,86,199,182,229,217,
167,21,88,28,104,110,6,19,73,150,76,42,6,154,147,122,195,240,92,219,220,224,18,87,180,21,250,148,231,156,216,193,209,251,234,194,26,224,252,99,69,94,116,118,55,139,5,219,178,118,212,60,205,152,79,44,89,
119,80,47,4,84,85,190,238,85,121,110,252,93,129,231,157,209,205,237,87,74,92,93,96,248,208,237,125,97,74,113,105,144,127,188,187,151,39,189,175,141,23,125,182,59,44,22,153,41,146,211,253,65,80,83,113,
116,231,120,156,197,58,53,76,206,22,232,103,195,84,99,63,91,164,159,25,162,159,25,33,103,6,131,144,230,151,211,143,14,114,113,83,47,215,124,185,155,47,222,43,101,146,72,203,170,212,150,245,169,98,26,123,
161,234,83,176,154,163,63,195,132,231,225,1,229,231,79,239,230,244,198,34,253,220,74,250,233,33,102,243,197,127,219,202,4,151,117,175,98,121,197,106,206,141,240,201,7,86,240,3,71,245,48,77,234,99,150,
165,177,99,66,37,161,90,219,208,176,230,38,75,219,92,21,128,176,74,96,215,29,44,127,240,181,110,206,62,90,12,99,150,55,21,184,105,221,16,79,56,182,157,105,218,212,8,72,203,223,209,186,57,204,52,183,90,
66,153,88,203,111,157,215,69,63,49,204,242,195,5,222,240,173,94,30,254,183,121,254,254,150,126,222,186,166,135,239,61,60,199,109,138,134,187,237,104,57,246,135,98,208,170,137,65,114,180,216,156,251,61,
85,164,47,15,209,207,20,200,217,56,145,127,166,176,84,187,230,10,228,236,114,250,233,34,253,228,0,239,186,174,151,135,190,34,71,107,234,51,87,245,169,35,166,91,182,157,169,52,47,87,221,62,119,117,88,190,
245,208,118,62,126,255,0,125,101,48,92,136,217,190,255,179,229,35,190,90,88,237,103,135,233,167,183,231,207,174,25,228,43,95,218,22,181,41,105,44,127,106,78,27,150,198,24,234,214,145,203,34,245,53,60,
194,52,49,252,219,87,182,241,87,63,26,100,245,201,66,48,129,99,43,120,251,245,253,252,219,131,242,20,211,106,214,36,46,244,88,186,40,177,190,64,81,161,124,206,202,132,143,222,211,31,6,223,110,14,3,216,
223,251,214,60,243,105,88,75,208,158,55,188,229,202,129,48,4,183,60,20,215,29,244,199,117,4,5,178,60,72,78,15,208,79,7,179,199,233,2,253,84,253,235,135,233,167,10,244,83,253,244,229,34,31,253,151,62,126,
224,237,237,28,232,9,7,111,52,89,162,225,97,147,116,156,105,222,50,138,187,46,180,224,54,132,207,223,35,229,61,63,234,101,54,53,76,63,93,36,231,135,214,250,241,238,255,251,29,22,126,113,155,181,126,102,
37,107,165,109,249,149,115,7,184,195,118,249,160,206,154,52,215,188,73,203,210,144,198,134,203,184,204,42,62,188,106,120,240,206,118,195,15,190,171,147,235,127,83,36,199,195,30,7,183,185,192,53,151,246,
240,175,118,76,227,14,136,180,69,72,173,27,194,108,99,65,137,138,240,165,123,39,44,61,60,64,55,30,198,68,31,118,112,27,69,132,157,29,202,111,93,212,29,119,253,13,198,169,196,195,225,208,167,10,244,229,
190,240,127,117,1,213,5,83,46,210,141,45,139,171,230,10,44,61,220,207,207,159,218,206,93,182,215,198,242,147,250,114,172,165,154,46,79,179,114,40,8,71,96,185,243,115,251,120,229,215,7,57,251,248,32,93,
41,76,45,102,101,224,223,119,193,8,103,151,173,242,11,219,172,245,211,43,56,253,196,10,158,121,82,15,7,251,211,104,206,146,168,218,245,9,243,75,111,89,56,88,19,85,62,188,89,99,132,219,20,19,158,127,122,
39,75,127,40,132,245,111,99,43,56,243,248,0,191,112,122,23,123,187,235,91,201,100,233,97,180,110,93,137,90,245,198,87,231,56,251,104,48,103,71,28,154,99,103,187,225,183,46,236,163,143,163,161,253,230,
184,131,169,92,36,203,5,250,114,63,57,29,198,77,179,28,77,223,100,88,163,192,201,65,178,60,192,108,180,192,31,94,218,203,215,188,52,105,92,62,149,250,64,120,219,178,90,78,150,0,170,250,10,188,250,231,
11,125,202,143,189,175,192,205,15,110,75,78,47,163,47,13,179,58,54,252,31,187,170,199,87,151,173,246,179,69,114,118,5,31,251,221,48,143,57,178,155,54,13,123,146,140,104,80,251,184,110,116,233,196,125,
187,197,166,150,240,97,85,185,247,206,121,94,249,181,94,46,108,12,147,237,253,248,48,31,186,163,159,239,123,123,71,240,87,18,214,253,64,130,128,151,172,92,136,43,9,14,125,101,142,99,127,42,242,157,111,
106,231,119,190,214,29,4,180,41,8,201,141,15,133,197,87,229,98,216,82,54,21,247,84,76,135,117,114,156,30,14,96,97,188,64,87,234,229,61,63,238,229,251,14,75,217,221,33,79,51,183,188,213,172,181,104,185,
180,0,41,40,219,243,202,35,94,223,198,71,238,25,161,31,127,14,253,220,8,253,236,127,242,210,43,183,56,180,214,79,47,163,159,92,198,155,214,12,113,255,151,132,205,99,106,19,138,166,113,185,85,244,83,130,
104,167,177,5,140,215,134,102,165,169,229,91,14,110,231,111,110,41,134,169,247,227,69,250,177,33,222,126,253,0,87,237,215,182,116,37,79,235,122,108,105,46,189,122,222,206,41,31,184,189,143,126,116,128,
190,212,19,253,207,112,99,89,150,47,13,208,79,46,167,47,13,5,32,49,53,28,247,92,12,145,19,69,110,186,191,200,213,31,109,103,113,48,250,153,134,95,145,37,131,229,151,0,133,198,243,212,91,80,148,251,236,
158,227,47,111,28,10,38,120,114,132,110,182,176,150,149,158,85,248,175,120,185,153,193,85,110,102,229,218,106,121,59,214,74,219,241,235,95,28,228,174,207,105,111,108,33,51,106,227,50,145,214,45,94,75,
253,76,235,62,63,21,195,193,94,195,227,143,232,224,227,247,12,177,250,196,32,221,166,2,43,143,15,241,210,11,122,184,253,138,186,95,144,166,70,137,134,75,32,202,124,162,252,243,47,227,130,145,137,62,186,
137,184,131,162,52,72,78,13,133,205,100,165,184,219,111,42,78,208,47,21,56,247,104,129,151,157,215,201,221,159,107,131,96,234,19,242,197,60,195,210,224,86,196,217,92,184,181,124,200,242,242,243,123,57,
187,33,174,86,157,44,146,83,189,255,53,194,217,242,181,56,190,235,106,78,174,164,159,89,201,201,71,183,227,137,199,15,179,163,221,54,215,94,139,93,226,104,91,133,213,64,131,88,186,198,103,89,209,240,220,
211,187,88,126,176,159,110,172,64,55,218,207,209,251,134,120,198,137,221,108,111,107,110,107,150,184,180,68,161,108,75,132,155,238,139,166,108,83,4,12,255,171,189,179,139,141,162,138,226,248,204,157,187,
195,118,187,219,221,238,204,206,206,76,11,146,96,8,242,81,99,98,4,124,128,141,130,47,168,132,104,162,198,106,52,18,130,137,26,18,244,69,67,220,7,19,241,35,250,66,132,7,99,20,99,37,240,96,130,70,77,52,
76,83,37,241,65,98,21,4,66,8,152,74,41,237,206,206,110,183,80,62,186,115,255,62,220,59,187,179,219,198,160,65,41,176,231,101,155,62,52,219,61,123,206,249,159,255,153,228,87,76,243,189,169,108,136,86,42,
84,94,201,0,43,152,232,239,75,98,237,10,5,81,149,212,104,98,1,175,79,154,134,105,144,103,172,166,100,156,96,235,230,56,134,142,9,73,95,54,0,239,58,32,226,174,106,94,77,106,14,202,22,88,197,198,225,31,
76,244,62,146,20,36,73,82,115,47,164,0,189,35,133,231,203,76,255,188,12,69,150,177,178,39,130,129,125,73,92,250,83,3,27,53,192,70,116,12,246,103,240,216,134,24,71,226,212,64,36,50,218,34,4,67,131,154,
128,202,235,64,49,203,119,35,207,20,36,48,33,191,93,11,71,29,29,79,111,104,67,103,34,220,70,73,168,66,68,139,14,218,41,81,66,114,154,255,94,165,4,185,123,35,248,173,63,11,140,103,5,251,66,119,46,23,104,
78,154,205,193,166,140,28,42,134,195,42,89,248,165,46,124,253,169,129,213,247,180,11,160,188,12,66,105,189,98,102,20,19,225,29,131,207,130,182,57,4,143,174,81,113,212,209,81,61,99,192,31,213,80,29,54,
241,217,206,20,238,92,34,184,233,18,103,149,15,15,114,192,72,77,217,185,105,174,236,10,105,176,130,142,209,35,157,120,235,149,36,22,205,87,249,223,39,138,0,15,75,77,115,71,170,45,159,193,251,34,82,29,
195,179,116,97,20,251,119,167,113,249,156,5,193,212,117,152,59,127,118,39,103,122,85,197,243,254,249,172,195,202,115,113,121,164,27,111,190,218,129,174,44,39,51,83,97,225,200,82,243,110,81,87,80,53,145,
17,162,43,107,73,138,109,207,199,113,246,87,3,190,128,197,79,14,25,216,249,118,10,93,54,69,44,74,48,118,84,96,117,198,52,78,108,118,51,96,158,134,139,103,210,216,179,35,142,149,61,180,134,13,34,129,23,
40,213,91,239,116,97,32,215,177,58,146,2,211,136,96,215,246,78,140,15,165,5,201,38,13,54,49,75,91,219,213,47,194,186,195,206,219,96,165,46,20,79,88,216,212,27,3,141,4,116,50,165,137,191,20,150,185,97,
91,168,46,119,9,145,177,112,190,138,79,222,73,97,252,100,70,248,129,89,140,29,78,35,191,165,29,238,177,20,175,34,151,83,154,253,49,29,3,123,147,88,255,64,27,84,170,212,20,88,163,74,36,161,157,44,108,244,
214,127,142,199,8,94,122,38,134,225,223,51,96,21,222,210,153,123,131,39,167,65,5,94,73,230,216,120,198,97,37,19,172,108,225,199,175,52,172,91,19,107,116,131,9,173,139,1,153,128,82,181,38,42,234,21,85,
159,91,10,33,88,177,152,226,251,207,83,184,52,100,162,58,146,129,95,200,192,47,112,161,193,70,58,113,124,64,195,150,103,219,160,167,3,213,22,94,52,195,142,123,104,14,213,232,157,117,121,159,187,59,138,
67,7,116,174,22,75,89,176,74,198,97,165,142,156,116,51,6,170,153,28,155,200,128,185,22,174,20,109,236,253,80,71,207,98,10,170,68,161,40,145,154,157,68,132,47,72,149,8,40,85,167,129,28,3,17,194,151,70,
5,189,15,170,56,62,208,129,234,40,135,210,23,143,234,120,111,91,28,11,231,41,194,149,14,240,163,202,12,85,34,53,178,112,3,78,174,68,176,96,30,193,158,93,73,92,26,201,128,21,108,48,207,116,80,201,222,156,
201,153,222,207,73,229,96,0,0,2,219,73,68,65,84,2,51,121,126,187,209,81,57,101,226,245,151,211,252,219,46,211,80,101,169,144,36,25,115,84,158,64,73,48,200,249,55,157,214,218,22,255,80,41,178,233,8,222,
216,18,69,223,142,14,44,95,166,66,165,164,166,252,234,73,110,174,34,169,70,224,172,59,213,4,233,84,4,175,189,144,128,123,66,7,43,117,243,157,199,75,228,165,91,45,112,65,203,177,11,134,227,123,22,88,197,
196,240,160,133,77,79,181,35,18,169,19,39,73,112,242,8,177,211,165,144,69,20,246,212,104,36,10,133,112,188,169,28,216,71,33,143,141,52,24,159,205,175,92,52,168,17,130,135,214,198,112,242,39,177,79,21,
179,96,165,164,35,221,234,193,198,227,57,54,161,59,172,104,2,174,137,131,223,232,120,120,77,91,141,58,73,136,224,163,75,193,204,10,19,57,149,38,39,64,14,221,116,72,195,252,9,68,1,9,39,71,220,174,104,132,
226,174,165,42,14,238,183,48,117,206,134,95,236,6,243,52,7,133,104,78,106,69,216,184,213,114,108,210,2,243,12,76,185,221,232,219,149,196,178,59,212,250,181,87,36,171,121,225,109,76,70,115,149,132,230,
143,172,52,157,173,249,21,181,219,82,176,251,253,4,46,252,193,89,235,85,47,13,84,82,173,228,252,253,73,36,147,247,75,58,88,217,196,196,41,19,219,182,166,184,225,41,139,67,96,195,46,51,83,37,205,176,144,
54,31,13,101,130,246,24,197,230,222,56,134,15,155,92,20,20,45,48,175,35,223,202,192,63,169,172,162,230,176,242,109,184,50,108,227,244,207,25,60,247,100,18,148,10,147,86,82,160,40,115,64,105,68,80,146,
229,134,75,240,204,15,177,240,106,138,69,21,172,187,47,138,193,3,252,193,24,127,204,4,43,165,90,115,231,95,39,234,226,146,28,243,12,192,235,2,115,13,124,183,79,199,218,213,115,248,124,34,50,136,66,67,
244,104,97,221,4,50,93,180,72,162,4,55,30,5,61,139,162,248,182,79,199,212,176,1,54,150,5,27,179,29,140,182,230,206,181,105,129,229,76,158,149,57,64,254,114,161,11,31,108,79,96,174,77,5,13,57,168,46,161,
222,72,227,173,74,33,50,44,157,226,163,119,19,40,159,178,197,157,202,192,212,248,178,86,114,174,121,85,141,37,114,126,217,114,224,153,96,165,110,20,142,27,120,113,99,7,18,49,90,107,101,36,196,93,151,101,
130,100,135,130,141,79,180,227,220,17,3,204,181,185,27,94,156,219,154,59,255,117,84,39,210,57,54,145,117,152,103,130,185,54,78,31,178,241,248,250,4,34,74,189,237,41,68,193,170,229,81,252,210,159,5,92,
254,0,138,239,233,206,84,161,179,85,61,255,107,178,202,169,60,43,101,193,92,19,190,119,59,190,255,66,195,253,171,162,88,188,64,197,151,31,107,184,116,214,6,243,108,248,37,195,65,161,163,149,156,235,218,
6,207,235,121,86,180,193,74,22,170,35,54,38,135,44,110,227,184,89,176,241,84,171,181,205,154,170,42,181,231,152,167,57,254,68,55,252,178,9,86,182,90,201,153,181,42,208,211,114,56,219,214,106,109,173,104,
69,43,90,113,99,198,95,39,9,56,68,161,48,235,47,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* NekobeeMain::bee_logo_png = (const char*) resource_NekobeeMain_bee_logo_png;
const int NekobeeMain::bee_logo_pngSize = 17248;
