/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  18 Jan 2010 2:40:48 pm

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
#include "../SoundCrabEditor.h"
//[/Headers]

#include "SoundCrabMainComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
SoundCrabMainComponent::SoundCrabMainComponent (SoundCrabEditor* const editor_, SoundCrabPlugin* const plugin_)
    : editor (editor_),
      plugin (plugin_),
      presetBox (0),
      fileChooser (0),
      gainSlider (0),
      panSlider (0),
      attackSlider (0),
      decaySlider (0),
      sustainSlider (0),
      releaseSlider (0),
      coarseSlider (0),
      fineSlider (0),
      cutoffSlider (0),
      resoSlider (0),
      attackModSlider (0),
      decayModSlider (0),
      sustainModSlider (0),
      releaseModSlider (0),
      coarseLfoSlider (0),
      coarseEnvSlider (0),
      filterLfoSlider (0),
      filterEnvSlider (0),
      polySlider (0),
      lfoFreqSlider (0),
      lfoDelaySlider (0),
      label (0),
      cpuIndicator (0)
{
    addAndMakeVisible (presetBox = new ComboBox (String::empty));
    presetBox->setEditableText (false);
    presetBox->setJustificationType (Justification::centredLeft);
    presetBox->setTextWhenNothingSelected (T("(no preset selected)"));
    presetBox->setTextWhenNoChoicesAvailable (T("(no presets available)"));
    presetBox->addListener (this);

    addAndMakeVisible (fileChooser = new FilenameComponent (T("soundfont"),
                                                            File::nonexistent,
                                                            true, false, false,
                                                            T("*.sf2"),
                                                            String::empty,
                                                            T("(choose a SF2 file)")));

    addAndMakeVisible (gainSlider = new ImageSlider (String::empty));
    gainSlider->setRange (0, 1, 0.001);
    gainSlider->setSliderStyle (Slider::LinearVertical);
    gainSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    gainSlider->addListener (this);

    addAndMakeVisible (panSlider = new ImageSlider (String::empty));
    panSlider->setRange (0, 1, 0.001);
    panSlider->setSliderStyle (Slider::LinearVertical);
    panSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    panSlider->addListener (this);

    addAndMakeVisible (attackSlider = new ImageSlider (String::empty));
    attackSlider->setRange (0, 1, 0.001);
    attackSlider->setSliderStyle (Slider::LinearVertical);
    attackSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    attackSlider->addListener (this);

    addAndMakeVisible (decaySlider = new ImageSlider (String::empty));
    decaySlider->setRange (0, 1, 0.001);
    decaySlider->setSliderStyle (Slider::LinearVertical);
    decaySlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    decaySlider->addListener (this);

    addAndMakeVisible (sustainSlider = new ImageSlider (String::empty));
    sustainSlider->setRange (0, 1, 0.001);
    sustainSlider->setSliderStyle (Slider::LinearVertical);
    sustainSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    sustainSlider->addListener (this);

    addAndMakeVisible (releaseSlider = new ImageSlider (String::empty));
    releaseSlider->setRange (0, 1, 0.001);
    releaseSlider->setSliderStyle (Slider::LinearVertical);
    releaseSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    releaseSlider->addListener (this);

    addAndMakeVisible (coarseSlider = new ImageSlider (String::empty));
    coarseSlider->setRange (0, 1, 0.001);
    coarseSlider->setSliderStyle (Slider::LinearVertical);
    coarseSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    coarseSlider->addListener (this);

    addAndMakeVisible (fineSlider = new ImageSlider (String::empty));
    fineSlider->setRange (0, 1, 0.001);
    fineSlider->setSliderStyle (Slider::LinearVertical);
    fineSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    fineSlider->addListener (this);

    addAndMakeVisible (cutoffSlider = new ImageSlider (String::empty));
    cutoffSlider->setRange (0, 1, 0.001);
    cutoffSlider->setSliderStyle (Slider::LinearVertical);
    cutoffSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    cutoffSlider->addListener (this);

    addAndMakeVisible (resoSlider = new ImageSlider (String::empty));
    resoSlider->setRange (0, 1, 0.001);
    resoSlider->setSliderStyle (Slider::LinearVertical);
    resoSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    resoSlider->addListener (this);

    addAndMakeVisible (attackModSlider = new ImageSlider (String::empty));
    attackModSlider->setRange (0, 1, 0.001);
    attackModSlider->setSliderStyle (Slider::LinearVertical);
    attackModSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    attackModSlider->addListener (this);

    addAndMakeVisible (decayModSlider = new ImageSlider (String::empty));
    decayModSlider->setRange (0, 1, 0.001);
    decayModSlider->setSliderStyle (Slider::LinearVertical);
    decayModSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    decayModSlider->addListener (this);

    addAndMakeVisible (sustainModSlider = new ImageSlider (String::empty));
    sustainModSlider->setRange (0, 1, 0.001);
    sustainModSlider->setSliderStyle (Slider::LinearVertical);
    sustainModSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    sustainModSlider->addListener (this);

    addAndMakeVisible (releaseModSlider = new ImageSlider (String::empty));
    releaseModSlider->setRange (0, 1, 0.001);
    releaseModSlider->setSliderStyle (Slider::LinearVertical);
    releaseModSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    releaseModSlider->addListener (this);

    addAndMakeVisible (coarseLfoSlider = new ParameterSlider (String::empty));
    coarseLfoSlider->setRange (0, 1, 0.001);
    coarseLfoSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    coarseLfoSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    coarseLfoSlider->setColour (Slider::rotarySliderFillColourId, Colour (0xffd0e6db));
    coarseLfoSlider->addListener (this);

    addAndMakeVisible (coarseEnvSlider = new ParameterSlider (String::empty));
    coarseEnvSlider->setRange (0, 1, 0.001);
    coarseEnvSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    coarseEnvSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    coarseEnvSlider->setColour (Slider::rotarySliderFillColourId, Colour (0xffd0e6db));
    coarseEnvSlider->addListener (this);

    addAndMakeVisible (filterLfoSlider = new ParameterSlider (String::empty));
    filterLfoSlider->setRange (0, 1, 0.001);
    filterLfoSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    filterLfoSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    filterLfoSlider->setColour (Slider::rotarySliderFillColourId, Colour (0xffd0e6db));
    filterLfoSlider->addListener (this);

    addAndMakeVisible (filterEnvSlider = new ParameterSlider (String::empty));
    filterEnvSlider->setRange (0, 1, 0.001);
    filterEnvSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    filterEnvSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    filterEnvSlider->setColour (Slider::rotarySliderFillColourId, Colour (0xffd0e6db));
    filterEnvSlider->addListener (this);

    addAndMakeVisible (polySlider = new ParameterSlider (String::empty));
    polySlider->setTooltip (T("Number of voices"));
    polySlider->setRange (1, 128, 1);
    polySlider->setSliderStyle (Slider::IncDecButtons);
    polySlider->setTextBoxStyle (Slider::TextBoxLeft, true, 80, 20);
    polySlider->setColour (Slider::rotarySliderFillColourId, Colour (0xffd0e6db));
    polySlider->addListener (this);

    addAndMakeVisible (lfoFreqSlider = new ParameterSlider (String::empty));
    lfoFreqSlider->setRange (0, 1, 0.001);
    lfoFreqSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    lfoFreqSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    lfoFreqSlider->setColour (Slider::rotarySliderFillColourId, Colour (0xffd0e6db));
    lfoFreqSlider->addListener (this);

    addAndMakeVisible (lfoDelaySlider = new ParameterSlider (String::empty));
    lfoDelaySlider->setRange (0, 1, 0.001);
    lfoDelaySlider->setSliderStyle (Slider::RotaryVerticalDrag);
    lfoDelaySlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    lfoDelaySlider->setColour (Slider::rotarySliderFillColourId, Colour (0xffd0e6db));
    lfoDelaySlider->addListener (this);

    addAndMakeVisible (label = new Label (T("new label"),
                                          T("v0.1.1")));
    label->setFont (Font (11.2000f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (cpuIndicator = new Label (String::empty,
                                                 T("75%")));
    cpuIndicator->setFont (Font (17.2000f, Font::bold));
    cpuIndicator->setJustificationType (Justification::centred);
    cpuIndicator->setEditable (false, false, false);
    cpuIndicator->setColour (Label::textColourId, Colour (0xff1b1a1a));
    cpuIndicator->setColour (TextEditor::textColourId, Colours::black);
    cpuIndicator->setColour (TextEditor::backgroundColourId, Colour (0x0));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (480, 245);

    //[Constructor] You can add your own custom stuff here..
    String soundcrabVersion;
    soundcrabVersion << T("v") << T(JucePlugin_VersionString);
    label->setText (soundcrabVersion, false);

    Config* config = Config::getInstance ();
    fileChooser->setDefaultBrowseTarget (config->lastSoundfontDirectory);
    fileChooser->setRecentlyUsedFilenames (config->recentSoundfonts.getAllFilenames());
    fileChooser->setBrowseButtonText (T("browse"));
    fileChooser->addListener (this);

    plugin->getParameterLock().enter ();
        plugin->addListenerToParameter (PAR_GAIN, gainSlider);
        plugin->addListenerToParameter (PAR_PAN, panSlider);
        plugin->addListenerToParameter (PAR_POLY, polySlider);
        plugin->addListenerToParameter (PAR_COARSETUNE, coarseSlider);
        plugin->addListenerToParameter (PAR_FINETUNE, fineSlider);
        plugin->addListenerToParameter (PAR_MODLFOTOPITCH, coarseLfoSlider);
        plugin->addListenerToParameter (PAR_MODENVTOPITCH, coarseEnvSlider);
        plugin->addListenerToParameter (PAR_FILTERFC, cutoffSlider);
        plugin->addListenerToParameter (PAR_FILTERQ, resoSlider);
        plugin->addListenerToParameter (PAR_MODLFOTOFILTERFC, filterLfoSlider);
        plugin->addListenerToParameter (PAR_MODENVTOFILTERFC, filterEnvSlider);
        plugin->addListenerToParameter (PAR_VOLENVATTACK, attackSlider);
        plugin->addListenerToParameter (PAR_VOLENVDECAY, decaySlider);
        plugin->addListenerToParameter (PAR_VOLENVSUSTAIN, sustainSlider);
        plugin->addListenerToParameter (PAR_VOLENVRELEASE, releaseSlider);
        plugin->addListenerToParameter (PAR_MODENVATTACK, attackModSlider);
        plugin->addListenerToParameter (PAR_MODENVDECAY, decayModSlider);
        plugin->addListenerToParameter (PAR_MODENVSUSTAIN, sustainModSlider);
        plugin->addListenerToParameter (PAR_MODENVRELEASE, releaseModSlider);
        plugin->addListenerToParameter (PAR_MODLFODELAY, lfoDelaySlider);
        plugin->addListenerToParameter (PAR_MODLFOFREQ, lfoFreqSlider);
    plugin->getParameterLock().exit ();

    updateControls ();

    startTimer (1000 / 1);
    //[/Constructor]
}

SoundCrabMainComponent::~SoundCrabMainComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    stopTimer ();

    plugin->getParameterLock().enter ();
        plugin->removeListenerToParameter (PAR_GAIN, gainSlider);
        plugin->removeListenerToParameter (PAR_PAN, panSlider);
        plugin->removeListenerToParameter (PAR_POLY, polySlider);
        plugin->removeListenerToParameter (PAR_COARSETUNE, coarseSlider);
        plugin->removeListenerToParameter (PAR_FINETUNE, fineSlider);
        plugin->removeListenerToParameter (PAR_MODLFOTOPITCH, coarseLfoSlider);
        plugin->removeListenerToParameter (PAR_MODENVTOPITCH, coarseEnvSlider);
        plugin->removeListenerToParameter (PAR_FILTERFC, cutoffSlider);
        plugin->removeListenerToParameter (PAR_FILTERQ, resoSlider);
        plugin->removeListenerToParameter (PAR_MODLFOTOFILTERFC, filterLfoSlider);
        plugin->removeListenerToParameter (PAR_MODENVTOFILTERFC, filterEnvSlider);
        plugin->removeListenerToParameter (PAR_VOLENVATTACK, attackSlider);
        plugin->removeListenerToParameter (PAR_VOLENVDECAY, decaySlider);
        plugin->removeListenerToParameter (PAR_VOLENVSUSTAIN, sustainSlider);
        plugin->removeListenerToParameter (PAR_VOLENVRELEASE, releaseSlider);
        plugin->removeListenerToParameter (PAR_MODENVATTACK, attackModSlider);
        plugin->removeListenerToParameter (PAR_MODENVDECAY, decayModSlider);
        plugin->removeListenerToParameter (PAR_MODENVSUSTAIN, sustainModSlider);
        plugin->removeListenerToParameter (PAR_MODENVRELEASE, releaseModSlider);
        plugin->removeListenerToParameter (PAR_MODLFODELAY, lfoDelaySlider);
        plugin->removeListenerToParameter (PAR_MODLFOFREQ, lfoFreqSlider);
    plugin->getParameterLock().exit ();
    //[/Destructor_pre]

    deleteAndZero (presetBox);
    deleteAndZero (fileChooser);
    deleteAndZero (gainSlider);
    deleteAndZero (panSlider);
    deleteAndZero (attackSlider);
    deleteAndZero (decaySlider);
    deleteAndZero (sustainSlider);
    deleteAndZero (releaseSlider);
    deleteAndZero (coarseSlider);
    deleteAndZero (fineSlider);
    deleteAndZero (cutoffSlider);
    deleteAndZero (resoSlider);
    deleteAndZero (attackModSlider);
    deleteAndZero (decayModSlider);
    deleteAndZero (sustainModSlider);
    deleteAndZero (releaseModSlider);
    deleteAndZero (coarseLfoSlider);
    deleteAndZero (coarseEnvSlider);
    deleteAndZero (filterLfoSlider);
    deleteAndZero (filterEnvSlider);
    deleteAndZero (polySlider);
    deleteAndZero (lfoFreqSlider);
    deleteAndZero (lfoDelaySlider);
    deleteAndZero (label);
    deleteAndZero (cpuIndicator);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SoundCrabMainComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.setGradientFill (ColourGradient (Colour (0xff598868),
                                       221.0f, 57.0f,
                                       Colour (0xffb9dcbc),
                                       221.0f, 12.0f,
                                       false));
    g.fillRect (0, 0, 480, 234);

    g.setGradientFill (ColourGradient (Colour (0xff598868),
                                       231.0f, 237.0f,
                                       Colours::black,
                                       231.0f, 251.0f,
                                       false));
    g.fillRect (0, 232, 480, 13);

    g.setColour (Colour (0x34bbeab8));
    g.fillRoundedRectangle (422.0f, 65.0f, 53.0f, 161.0f, 5.0000f);

    g.setColour (Colour (0xa2ffffff));
    g.setFont (Font (9.4000f, Font::bold));
    g.drawText (T("PAN  GAIN"),
                422, 209, 52, 17,
                Justification::centred, true);

    g.setColour (Colour (0x34bbeab8));
    g.fillRoundedRectangle (5.0f, 65.0f, 86.0f, 161.0f, 5.0000f);

    g.setColour (Colour (0x34bbeab8));
    g.fillRoundedRectangle (320.0f, 65.0f, 97.0f, 161.0f, 5.0000f);

    g.setColour (Colour (0xa2ffffff));
    g.setFont (Font (9.4000f, Font::bold));
    g.drawText (T("A       D       S       R"),
                324, 209, 91, 17,
                Justification::centred, true);

    g.setColour (Colour (0x34bbeab8));
    g.fillRoundedRectangle (96.0f, 65.0f, 86.0f, 161.0f, 5.0000f);

    g.setColour (Colour (0xa2ffffff));
    g.setFont (Font (9.4000f, Font::bold));
    g.drawText (T("CUT     Q"),
                97, 208, 46, 17,
                Justification::centred, true);

    g.setColour (Colour (0xa2ffffff));
    g.setFont (Font (9.4000f, Font::bold));
    g.drawText (T("MAIN FINE"),
                6, 208, 48, 17,
                Justification::centred, true);

    g.setColour (Colour (0xa2ffffff));
    g.setFont (Font (9.4000f, Font::bold));
    g.drawText (T("LFO                            LFO"),
                58, 94, 117, 17,
                Justification::centred, true);

    g.setColour (Colour (0xa2ffffff));
    g.setFont (Font (9.4000f, Font::bold));
    g.drawText (T("ENV                            ENV"),
                58, 129, 117, 17,
                Justification::centred, true);

    g.setColour (Colour (0x34bbeab8));
    g.fillRoundedRectangle (187.0f, 65.0f, 128.0f, 161.0f, 5.0000f);

    g.setColour (Colour (0xa2ffffff));
    g.setFont (Font (9.4000f, Font::bold));
    g.drawText (T("A       D       S       R"),
                191, 209, 91, 17,
                Justification::centred, true);

    g.setColour (Colour (0xa2ffffff));
    g.setFont (Font (9.4000f, Font::bold));
    g.drawText (T("FREQ"),
                282, 94, 31, 17,
                Justification::centred, true);

    g.setColour (Colour (0xa2ffffff));
    g.setFont (Font (9.4000f, Font::bold));
    g.drawText (T("DELAY"),
                283, 128, 31, 17,
                Justification::centred, true);

    g.setColour (Colour (0xa2ffffff));
    g.setFont (Font (14.3000f, Font::bold));
    g.drawText (T("TONE"),
                5, 228, 84, 12,
                Justification::centred, true);

    g.setColour (Colour (0xa2ffffff));
    g.setFont (Font (14.3000f, Font::bold));
    g.drawText (T("FILTER"),
                97, 228, 84, 12,
                Justification::centred, true);

    g.setColour (Colour (0xa2ffffff));
    g.setFont (Font (14.3000f, Font::bold));
    g.drawText (T("MOD ENV/LFO"),
                201, 228, 100, 12,
                Justification::centred, true);

    g.setColour (Colour (0xa2ffffff));
    g.setFont (Font (14.3000f, Font::bold));
    g.drawText (T("AMP ENV"),
                323, 228, 94, 12,
                Justification::centred, true);

    g.setGradientFill (ColourGradient (Colour (0xff84a192),
                                       8.0f, (float) (-2),
                                       Colour (0xff517b51),
                                       186.0f, 23.0f,
                                       false));
    g.setFont (Font (21.3000f, Font::bold));
    g.drawText (T("S O U N D C R A B"),
                8, -1, 181, 24,
                Justification::centred, true);

    g.setColour (Colour (0x34bbeab8));
    g.fillRoundedRectangle (422.0f, 44.0f, 53.0f, 17.0f, 5.0000f);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void SoundCrabMainComponent::resized()
{
    presetBox->setBounds (5, 43, 351, 18);
    fileChooser->setBounds (5, 21, 470, 18);
    gainSlider->setBounds (453, 68, 15, 141);
    panSlider->setBounds (428, 68, 15, 141);
    attackSlider->setBounds (326, 68, 15, 141);
    decaySlider->setBounds (350, 68, 15, 141);
    sustainSlider->setBounds (374, 68, 15, 141);
    releaseSlider->setBounds (398, 68, 15, 141);
    coarseSlider->setBounds (10, 68, 15, 141);
    fineSlider->setBounds (35, 68, 15, 141);
    cutoffSlider->setBounds (101, 68, 15, 141);
    resoSlider->setBounds (126, 68, 15, 141);
    attackModSlider->setBounds (192, 69, 15, 141);
    decayModSlider->setBounds (216, 69, 15, 141);
    sustainModSlider->setBounds (240, 69, 15, 141);
    releaseModSlider->setBounds (264, 69, 15, 141);
    coarseLfoSlider->setBounds (58, 72, 26, 27);
    coarseEnvSlider->setBounds (58, 106, 26, 27);
    filterLfoSlider->setBounds (149, 72, 26, 27);
    filterEnvSlider->setBounds (149, 106, 26, 27);
    polySlider->setBounds (359, 43, 61, 18);
    lfoFreqSlider->setBounds (284, 72, 26, 27);
    lfoDelaySlider->setBounds (284, 106, 26, 27);
    label->setBounds (439, 4, 36, 13);
    cpuIndicator->setBounds (427, 44, 45, 17);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void SoundCrabMainComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == presetBox)
    {
        //[UserComboBoxCode_presetBox] -- add your combo box handling code here..
        plugin->setCurrentAbsolutePreset (presetBox->getSelectedId ());
        //[/UserComboBoxCode_presetBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void SoundCrabMainComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == gainSlider)
    {
        //[UserSliderCode_gainSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_GAIN, sliderThatWasMoved->getValue());
        //[/UserSliderCode_gainSlider]
    }
    else if (sliderThatWasMoved == panSlider)
    {
        //[UserSliderCode_panSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_PAN, sliderThatWasMoved->getValue());
        //[/UserSliderCode_panSlider]
    }
    else if (sliderThatWasMoved == attackSlider)
    {
        //[UserSliderCode_attackSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_VOLENVATTACK, sliderThatWasMoved->getValue());
        //[/UserSliderCode_attackSlider]
    }
    else if (sliderThatWasMoved == decaySlider)
    {
        //[UserSliderCode_decaySlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_VOLENVDECAY, sliderThatWasMoved->getValue());
        //[/UserSliderCode_decaySlider]
    }
    else if (sliderThatWasMoved == sustainSlider)
    {
        //[UserSliderCode_sustainSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_VOLENVSUSTAIN, sliderThatWasMoved->getValue());
        //[/UserSliderCode_sustainSlider]
    }
    else if (sliderThatWasMoved == releaseSlider)
    {
        //[UserSliderCode_releaseSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_VOLENVRELEASE, sliderThatWasMoved->getValue());
        //[/UserSliderCode_releaseSlider]
    }
    else if (sliderThatWasMoved == coarseSlider)
    {
        //[UserSliderCode_coarseSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_COARSETUNE, sliderThatWasMoved->getValue());
        //[/UserSliderCode_coarseSlider]
    }
    else if (sliderThatWasMoved == fineSlider)
    {
        //[UserSliderCode_fineSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_FINETUNE, sliderThatWasMoved->getValue());
        //[/UserSliderCode_fineSlider]
    }
    else if (sliderThatWasMoved == cutoffSlider)
    {
        //[UserSliderCode_cutoffSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_FILTERFC, sliderThatWasMoved->getValue());
        //[/UserSliderCode_cutoffSlider]
    }
    else if (sliderThatWasMoved == resoSlider)
    {
        //[UserSliderCode_resoSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_FILTERQ, sliderThatWasMoved->getValue());
        //[/UserSliderCode_resoSlider]
    }
    else if (sliderThatWasMoved == attackModSlider)
    {
        //[UserSliderCode_attackModSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_MODENVATTACK, sliderThatWasMoved->getValue());
        //[/UserSliderCode_attackModSlider]
    }
    else if (sliderThatWasMoved == decayModSlider)
    {
        //[UserSliderCode_decayModSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_MODENVDECAY, sliderThatWasMoved->getValue());
        //[/UserSliderCode_decayModSlider]
    }
    else if (sliderThatWasMoved == sustainModSlider)
    {
        //[UserSliderCode_sustainModSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_MODENVSUSTAIN, sliderThatWasMoved->getValue());
        //[/UserSliderCode_sustainModSlider]
    }
    else if (sliderThatWasMoved == releaseModSlider)
    {
        //[UserSliderCode_releaseModSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_MODENVRELEASE, sliderThatWasMoved->getValue());
        //[/UserSliderCode_releaseModSlider]
    }
    else if (sliderThatWasMoved == coarseLfoSlider)
    {
        //[UserSliderCode_coarseLfoSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_MODLFOTOPITCH, sliderThatWasMoved->getValue());
        //[/UserSliderCode_coarseLfoSlider]
    }
    else if (sliderThatWasMoved == coarseEnvSlider)
    {
        //[UserSliderCode_coarseEnvSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_MODENVTOPITCH, sliderThatWasMoved->getValue());
        //[/UserSliderCode_coarseEnvSlider]
    }
    else if (sliderThatWasMoved == filterLfoSlider)
    {
        //[UserSliderCode_filterLfoSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_MODLFOTOFILTERFC, sliderThatWasMoved->getValue());
        //[/UserSliderCode_filterLfoSlider]
    }
    else if (sliderThatWasMoved == filterEnvSlider)
    {
        //[UserSliderCode_filterEnvSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_MODENVTOFILTERFC, sliderThatWasMoved->getValue());
        //[/UserSliderCode_filterEnvSlider]
    }
    else if (sliderThatWasMoved == polySlider)
    {
        //[UserSliderCode_polySlider] -- add your slider handling code here..
        plugin->setParameterMappedNotifyingHost (PAR_POLY, sliderThatWasMoved->getValue());
        //[/UserSliderCode_polySlider]
    }
    else if (sliderThatWasMoved == lfoFreqSlider)
    {
        //[UserSliderCode_lfoFreqSlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_MODLFOFREQ, sliderThatWasMoved->getValue());
        //[/UserSliderCode_lfoFreqSlider]
    }
    else if (sliderThatWasMoved == lfoDelaySlider)
    {
        //[UserSliderCode_lfoDelaySlider] -- add your slider handling code here..
        plugin->setParameterNotifyingHost (PAR_MODLFODELAY, sliderThatWasMoved->getValue());
        //[/UserSliderCode_lfoDelaySlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void SoundCrabMainComponent::filesDropped (const StringArray& filenames, int mouseX, int mouseY)
{
    //[UserCode_filesDropped] -- Add your code here...
    if (filenames.size() > 0)
        loadSoundFont (filenames [0]);
    //[/UserCode_filesDropped]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//==============================================================================
void SoundCrabMainComponent::filenameComponentChanged (FilenameComponent*)
{
    loadSoundFont (fileChooser->getCurrentFile());
}

//==============================================================================
void SoundCrabMainComponent::updateControls ()
{
    // update file choose
    fileChooser->setCurrentFile (plugin->getCurrentSoundFontFile (),
                                 true,
                                 false);

    // update combobox
    presetBox->clear ();
    plugin->fillComboboxWithPresets (presetBox);
    presetBox->setSelectedId (plugin->getCurrentAbsolutePreset (), true);

    // update sliders
    gainSlider->setValue (plugin->getParameter (PAR_GAIN), false);
    panSlider->setValue (plugin->getParameter (PAR_PAN), false);
    polySlider->setValue (plugin->getParameterMapped (PAR_POLY), false);
    coarseSlider->setValue (plugin->getParameter (PAR_COARSETUNE), false);
    fineSlider->setValue (plugin->getParameter (PAR_FINETUNE), false);
    coarseLfoSlider->setValue (plugin->getParameter (PAR_MODLFOTOPITCH), false);
    coarseEnvSlider->setValue (plugin->getParameter (PAR_MODENVTOPITCH), false);
    cutoffSlider->setValue (plugin->getParameter (PAR_FILTERFC), false);
    resoSlider->setValue (plugin->getParameter (PAR_FILTERQ), false);
    filterLfoSlider->setValue (plugin->getParameter (PAR_MODLFOTOFILTERFC), false);
    filterEnvSlider->setValue (plugin->getParameter (PAR_MODENVTOFILTERFC), false);
    attackSlider->setValue (plugin->getParameter (PAR_VOLENVATTACK), false);
    decaySlider->setValue (plugin->getParameter (PAR_VOLENVDECAY), false);
    sustainSlider->setValue (plugin->getParameter (PAR_VOLENVSUSTAIN), false);
    releaseSlider->setValue (plugin->getParameter (PAR_VOLENVRELEASE), false);
    attackModSlider->setValue (plugin->getParameter (PAR_MODENVATTACK), false);
    decayModSlider->setValue (plugin->getParameter (PAR_MODENVDECAY), false);
    sustainModSlider->setValue (plugin->getParameter (PAR_MODENVSUSTAIN), false);
    releaseModSlider->setValue (plugin->getParameter (PAR_MODENVRELEASE), false);
    lfoDelaySlider->setValue (plugin->getParameter (PAR_MODLFODELAY), false);
    lfoFreqSlider->setValue (plugin->getParameter (PAR_MODLFOFREQ), false);
}

bool SoundCrabMainComponent::loadSoundFont (const File& soundFontFile)
{
    if (soundFontFile.existsAsFile ())
    {
        presetBox->clear ();

        if (plugin->loadSoundFont (soundFontFile) == true)
        {
            plugin->fillComboboxWithPresets (presetBox);

            presetBox->setSelectedId (1);

            return true;
        }
        else
        {
            String message;
            message << "Unable to load "
                    << soundFontFile.getFullPathName ();

            AlertWindow::showMessageBox (AlertWindow::WarningIcon,
                                         T("Soundfont load failed"),
                                         message);
        }
    }

    return false;
}

void SoundCrabMainComponent::timerCallback ()
{
    // printf ("%s\n", (const char*) String (plugin->getAverageCpuLoad ()));

    String cpuLoadString;
    cpuLoadString.printf (T("%d%%"), roundFloatToInt (plugin->getAverageCpuLoad ()));

    cpuIndicator->setText (cpuLoadString, false);
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SoundCrabMainComponent" componentName=""
                 parentClasses="public Component, public FilenameComponentListener, public Timer"
                 constructorParams="SoundCrabEditor* const editor_, SoundCrabPlugin* const plugin_"
                 variableInitialisers="editor (editor_),&#10;plugin (plugin_)" snapPixels="8"
                 snapActive="0" snapShown="1" overlayOpacity="0.330000013" fixedSize="1"
                 initialWidth="480" initialHeight="245">
  <METHODS>
    <METHOD name="filesDropped (const StringArray&amp; filenames, int mouseX, int mouseY)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ffffff">
    <RECT pos="0 0 480 234" fill="linear: 221 57, 221 12, 0=ff598868, 1=ffb9dcbc"
          hasStroke="0"/>
    <RECT pos="0 232 480 13" fill="linear: 231 237, 231 251, 0=ff598868, 1=ff000000"
          hasStroke="0"/>
    <ROUNDRECT pos="422 65 53 161" cornerSize="5" fill="solid: 34bbeab8" hasStroke="0"/>
    <TEXT pos="422 209 52 17" fill="solid: a2ffffff" hasStroke="0" text="PAN  GAIN"
          fontname="Default font" fontsize="9.4" bold="1" italic="0" justification="36"/>
    <ROUNDRECT pos="5 65 86 161" cornerSize="5" fill="solid: 34bbeab8" hasStroke="0"/>
    <ROUNDRECT pos="320 65 97 161" cornerSize="5" fill="solid: 34bbeab8" hasStroke="0"/>
    <TEXT pos="324 209 91 17" fill="solid: a2ffffff" hasStroke="0" text="A       D       S       R"
          fontname="Default font" fontsize="9.4" bold="1" italic="0" justification="36"/>
    <ROUNDRECT pos="96 65 86 161" cornerSize="5" fill="solid: 34bbeab8" hasStroke="0"/>
    <TEXT pos="97 208 46 17" fill="solid: a2ffffff" hasStroke="0" text="CUT     Q"
          fontname="Default font" fontsize="9.4" bold="1" italic="0" justification="36"/>
    <TEXT pos="6 208 48 17" fill="solid: a2ffffff" hasStroke="0" text="MAIN FINE"
          fontname="Default font" fontsize="9.4" bold="1" italic="0" justification="36"/>
    <TEXT pos="58 94 117 17" fill="solid: a2ffffff" hasStroke="0" text="LFO                            LFO"
          fontname="Default font" fontsize="9.4" bold="1" italic="0" justification="36"/>
    <TEXT pos="58 129 117 17" fill="solid: a2ffffff" hasStroke="0" text="ENV                            ENV"
          fontname="Default font" fontsize="9.4" bold="1" italic="0" justification="36"/>
    <ROUNDRECT pos="187 65 128 161" cornerSize="5" fill="solid: 34bbeab8" hasStroke="0"/>
    <TEXT pos="191 209 91 17" fill="solid: a2ffffff" hasStroke="0" text="A       D       S       R"
          fontname="Default font" fontsize="9.4" bold="1" italic="0" justification="36"/>
    <TEXT pos="282 94 31 17" fill="solid: a2ffffff" hasStroke="0" text="FREQ"
          fontname="Default font" fontsize="9.4" bold="1" italic="0" justification="36"/>
    <TEXT pos="283 128 31 17" fill="solid: a2ffffff" hasStroke="0" text="DELAY"
          fontname="Default font" fontsize="9.4" bold="1" italic="0" justification="36"/>
    <TEXT pos="5 228 84 12" fill="solid: a2ffffff" hasStroke="0" text="TONE"
          fontname="Default font" fontsize="14.3" bold="1" italic="0" justification="36"/>
    <TEXT pos="97 228 84 12" fill="solid: a2ffffff" hasStroke="0" text="FILTER"
          fontname="Default font" fontsize="14.3" bold="1" italic="0" justification="36"/>
    <TEXT pos="201 228 100 12" fill="solid: a2ffffff" hasStroke="0" text="MOD ENV/LFO"
          fontname="Default font" fontsize="14.3" bold="1" italic="0" justification="36"/>
    <TEXT pos="323 228 94 12" fill="solid: a2ffffff" hasStroke="0" text="AMP ENV"
          fontname="Default font" fontsize="14.3" bold="1" italic="0" justification="36"/>
    <TEXT pos="8 -1 181 24" fill="linear: 8 -2, 186 23, 0=ff84a192, 1=ff517b51"
          hasStroke="0" text="S O U N D C R A B" fontname="Default font"
          fontsize="21.3" bold="1" italic="0" justification="36"/>
    <ROUNDRECT pos="422 44 53 17" cornerSize="5" fill="solid: 34bbeab8" hasStroke="0"/>
  </BACKGROUND>
  <COMBOBOX name="" id="fff8c82083bf2e04" memberName="presetBox" virtualName=""
            explicitFocusOrder="0" pos="5 43 351 18" editable="0" layout="33"
            items="" textWhenNonSelected="(no preset selected)" textWhenNoItems="(no presets available)"/>
  <GENERICCOMPONENT name="" id="f0a225bf2015810d" memberName="fileChooser" virtualName=""
                    explicitFocusOrder="0" pos="5 21 470 18" class="FilenameComponent"
                    params="T(&quot;soundfont&quot;),&#10;File::nonexistent,&#10;true, false, false,&#10;T(&quot;*.sf2&quot;),&#10;String::empty,&#10;T(&quot;(choose a SF2 file)&quot;)"/>
  <SLIDER name="" id="f9fbcec9adb4f33b" memberName="gainSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="453 68 15 141" min="0" max="1" int="0.001"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="61f7677768e37770" memberName="panSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="428 68 15 141" min="0" max="1" int="0.001"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="af31d28c164040cc" memberName="attackSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="326 68 15 141" min="0" max="1" int="0.001"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="c9b5f126e162d57e" memberName="decaySlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="350 68 15 141" min="0" max="1" int="0.001"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="387f68e53287580f" memberName="sustainSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="374 68 15 141" min="0" max="1" int="0.001"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="e8ae7b34e107b574" memberName="releaseSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="398 68 15 141" min="0" max="1" int="0.001"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="564aeda193126ac3" memberName="coarseSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="10 68 15 141" min="0" max="1" int="0.001"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="426db378ae8160b" memberName="fineSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="35 68 15 141" min="0" max="1" int="0.001"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="ba2bc8efe0fd63bc" memberName="cutoffSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="101 68 15 141" min="0" max="1" int="0.001"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="b3000d664083ee47" memberName="resoSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="126 68 15 141" min="0" max="1" int="0.001"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="67a3985542568ec" memberName="attackModSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="192 69 15 141" min="0" max="1" int="0.001"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="301f1f075d4a9858" memberName="decayModSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="216 69 15 141" min="0" max="1" int="0.001"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="56bbf98067770d02" memberName="sustainModSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="240 69 15 141" min="0" max="1" int="0.001"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="24bc6f7c574f8b29" memberName="releaseModSlider" virtualName="ImageSlider"
          explicitFocusOrder="0" pos="264 69 15 141" min="0" max="1" int="0.001"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="e3068015fe1817a9" memberName="coarseLfoSlider" virtualName="ParameterSlider"
          explicitFocusOrder="0" pos="58 72 26 27" rotarysliderfill="ffd0e6db"
          min="0" max="1" int="0.001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="169ba8bb15789576" memberName="coarseEnvSlider" virtualName="ParameterSlider"
          explicitFocusOrder="0" pos="58 106 26 27" rotarysliderfill="ffd0e6db"
          min="0" max="1" int="0.001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="9acef09192d4dd42" memberName="filterLfoSlider" virtualName="ParameterSlider"
          explicitFocusOrder="0" pos="149 72 26 27" rotarysliderfill="ffd0e6db"
          min="0" max="1" int="0.001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="f97a6c4973d29807" memberName="filterEnvSlider" virtualName="ParameterSlider"
          explicitFocusOrder="0" pos="149 106 26 27" rotarysliderfill="ffd0e6db"
          min="0" max="1" int="0.001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="eb3b341d53566d3c" memberName="polySlider" virtualName="ParameterSlider"
          explicitFocusOrder="0" pos="359 43 61 18" tooltip="Number of voices"
          rotarysliderfill="ffd0e6db" min="1" max="128" int="1" style="IncDecButtons"
          textBoxPos="TextBoxLeft" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="178fadf1f4d29c0a" memberName="lfoFreqSlider" virtualName="ParameterSlider"
          explicitFocusOrder="0" pos="284 72 26 27" rotarysliderfill="ffd0e6db"
          min="0" max="1" int="0.001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="8f523295cfaec1c5" memberName="lfoDelaySlider" virtualName="ParameterSlider"
          explicitFocusOrder="0" pos="284 106 26 27" rotarysliderfill="ffd0e6db"
          min="0" max="1" int="0.001" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="2dc5acc563ebd2bc" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="439 4 36 13" edTextCol="ff000000"
         edBkgCol="0" labelText="v0.1.1" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="11.2"
         bold="0" italic="0" justification="33"/>
  <LABEL name="" id="d41286354d6172b4" memberName="cpuIndicator" virtualName=""
         explicitFocusOrder="0" pos="427 44 45 17" textCol="ff1b1a1a"
         edTextCol="ff000000" edBkgCol="0" labelText="75%" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="17.2" bold="1" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
