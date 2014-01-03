/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  18 Jan 2010 2:20:35 pm

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
#include "MidiKeyboardPlugin.h"
//[/Headers]

#include "MidiKeyboardEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MidiKeyboardEditor::MidiKeyboardEditor (MidiKeyboardPlugin* owner_)
    : PluginEditorComponent (owner_),
      owner (owner_),
      slPitchBend (0),
      cmbChannel (0),
      lbChannel (0),
      slVelocity (0),
      grControllers (0),
      btnTranspose (0),
      slTranspose (0),
      slVolume (0),
      lbController (0),
      slController1 (0),
      slController2 (0),
      slController3 (0),
      slController4 (0),
      slController5 (0),
      slController6 (0),
      slController7 (0),
      slController8 (0),
      lbController2 (0),
      lbController3 (0),
      lbController4 (0),
      lbController5 (0),
      lbController6 (0),
      lbController7 (0),
      lbController8 (0),
      lbController9 (0),
      slModWheel (0),
      slBendRange (0)
{
    addAndMakeVisible (slPitchBend = new Slider (String::empty));
    slPitchBend->setTooltip (T("Pitch bender"));
    slPitchBend->setRange (-8192, 8191, 1);
    slPitchBend->setSliderStyle (Slider::LinearHorizontal);
    slPitchBend->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    slPitchBend->setColour (Slider::thumbColourId, Colour (0xffd77f00));
    slPitchBend->setColour (Slider::trackColourId, Colour (0x7f7e7e7e));
    slPitchBend->addListener (this);

    addAndMakeVisible (cmbChannel = new ComboBox (String::empty));
    cmbChannel->setTooltip (T("MIDI output channel number"));
    cmbChannel->setEditableText (false);
    cmbChannel->setJustificationType (Justification::centred);
    cmbChannel->setTextWhenNothingSelected (T("1"));
    cmbChannel->setTextWhenNoChoicesAvailable (T("-"));
    cmbChannel->addItem (T("1"), 1);
    cmbChannel->addItem (T("2"), 2);
    cmbChannel->addItem (T("3"), 3);
    cmbChannel->addItem (T("4"), 4);
    cmbChannel->addItem (T("5"), 5);
    cmbChannel->addItem (T("6"), 6);
    cmbChannel->addItem (T("7"), 7);
    cmbChannel->addItem (T("8"), 8);
    cmbChannel->addItem (T("9"), 9);
    cmbChannel->addItem (T("10"), 10);
    cmbChannel->addItem (T("11"), 11);
    cmbChannel->addItem (T("12"), 12);
    cmbChannel->addItem (T("13"), 13);
    cmbChannel->addItem (T("14"), 14);
    cmbChannel->addItem (T("15"), 15);
    cmbChannel->addItem (T("16"), 16);
    cmbChannel->addListener (this);

    addAndMakeVisible (lbChannel = new Label (String::empty,
                                              T("midi ch")));
    lbChannel->setFont (Font (15.0000f, Font::plain));
    lbChannel->setJustificationType (Justification::centredRight);
    lbChannel->setEditable (false, false, false);
    lbChannel->setColour (Label::textColourId, Colours::white);
    lbChannel->setColour (TextEditor::textColourId, Colours::black);
    lbChannel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (slVelocity = new Slider (String::empty));
    slVelocity->setTooltip (T("The velocity range of output notes"));
    slVelocity->setRange (0, 127, 1);
    slVelocity->setSliderStyle (Slider::LinearHorizontal);
    slVelocity->setTextBoxStyle (Slider::NoTextBox, false, 35, 20);
    slVelocity->setColour (Slider::thumbColourId, Colour (0xffeeeeee));
    slVelocity->setColour (Slider::trackColourId, Colour (0x66777777));
    slVelocity->setColour (Slider::textBoxTextColourId, Colours::white);
    slVelocity->setColour (Slider::textBoxBackgroundColourId, Colour (0x27ffffff));
    slVelocity->setColour (Slider::textBoxHighlightColourId, Colour (0x4061a2ff));
    slVelocity->addListener (this);

    addAndMakeVisible (grControllers = new GroupComponent (String::empty,
                                                           T("controllers")));
    grControllers->setTextLabelPosition (Justification::centredRight);
    grControllers->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    grControllers->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (btnTranspose = new ToggleButton (String::empty));
    btnTranspose->setTooltip (T("Switch note transpose on/off"));
    btnTranspose->setButtonText (T("transpose"));
    btnTranspose->addButtonListener (this);
    btnTranspose->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (slTranspose = new Slider (String::empty));
    slTranspose->setTooltip (T("Number of semitones to transpose"));
    slTranspose->setRange (-48, 48, 1);
    slTranspose->setSliderStyle (Slider::IncDecButtons);
    slTranspose->setTextBoxStyle (Slider::TextBoxLeft, false, 35, 20);
    slTranspose->setColour (Slider::thumbColourId, Colour (0xffbfbfbf));
    slTranspose->setColour (Slider::textBoxTextColourId, Colours::white);
    slTranspose->setColour (Slider::textBoxBackgroundColourId, Colour (0x27ffffff));
    slTranspose->setColour (Slider::textBoxOutlineColourId, Colour (0x36ffffff));
    slTranspose->addListener (this);

    addAndMakeVisible (slVolume = new Slider (String::empty));
    slVolume->setTooltip (T("Volume"));
    slVolume->setRange (0, 127, 1);
    slVolume->setSliderStyle (Slider::RotaryVerticalDrag);
    slVolume->setTextBoxStyle (Slider::NoTextBox, false, 35, 15);
    slVolume->setColour (Slider::textBoxBackgroundColourId, Colour (0x27ffffff));
    slVolume->addListener (this);

    addAndMakeVisible (lbController = new Label (String::empty,
                                                 T("volume")));
    lbController->setFont (Font (Font::getDefaultSansSerifFontName(), 12.9000f, Font::plain));
    lbController->setJustificationType (Justification::centred);
    lbController->setEditable (false, false, false);
    lbController->setColour (Label::textColourId, Colours::white);
    lbController->setColour (Label::outlineColourId, Colour (0x0));
    lbController->setColour (TextEditor::textColourId, Colours::black);
    lbController->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (slController1 = new Slider (String::empty));
    slController1->setTooltip (T("Panning"));
    slController1->setRange (-63, 64, 1);
    slController1->setSliderStyle (Slider::RotaryVerticalDrag);
    slController1->setTextBoxStyle (Slider::TextBoxAbove, false, 35, 15);
    slController1->setColour (Slider::textBoxBackgroundColourId, Colour (0x27ffffff));
    slController1->setColour (Slider::textBoxOutlineColourId, Colour (0x808080));
    slController1->addListener (this);

    addAndMakeVisible (slController2 = new Slider (String::empty));
    slController2->setTooltip (T("Expression"));
    slController2->setRange (0, 127, 1);
    slController2->setSliderStyle (Slider::RotaryVerticalDrag);
    slController2->setTextBoxStyle (Slider::TextBoxAbove, false, 35, 15);
    slController2->setColour (Slider::textBoxBackgroundColourId, Colour (0x27ffffff));
    slController2->setColour (Slider::textBoxOutlineColourId, Colour (0x808080));
    slController2->addListener (this);

    addAndMakeVisible (slController3 = new Slider (String::empty));
    slController3->setTooltip (T("Filter cutoff frequency"));
    slController3->setRange (0, 127, 1);
    slController3->setSliderStyle (Slider::RotaryVerticalDrag);
    slController3->setTextBoxStyle (Slider::TextBoxAbove, false, 35, 15);
    slController3->setColour (Slider::textBoxBackgroundColourId, Colour (0x27ffffff));
    slController3->setColour (Slider::textBoxOutlineColourId, Colour (0x808080));
    slController3->addListener (this);

    addAndMakeVisible (slController4 = new Slider (String::empty));
    slController4->setTooltip (T("Filter cutoff resonance (Q-factor)"));
    slController4->setRange (0, 127, 1);
    slController4->setSliderStyle (Slider::RotaryVerticalDrag);
    slController4->setTextBoxStyle (Slider::TextBoxAbove, false, 35, 15);
    slController4->setColour (Slider::textBoxBackgroundColourId, Colour (0x27ffffff));
    slController4->setColour (Slider::textBoxOutlineColourId, Colour (0x808080));
    slController4->addListener (this);

    addAndMakeVisible (slController5 = new Slider (String::empty));
    slController5->setTooltip (T("Envelope Attack"));
    slController5->setRange (0, 127, 1);
    slController5->setSliderStyle (Slider::RotaryVerticalDrag);
    slController5->setTextBoxStyle (Slider::TextBoxAbove, false, 35, 15);
    slController5->setColour (Slider::textBoxBackgroundColourId, Colour (0x27ffffff));
    slController5->setColour (Slider::textBoxOutlineColourId, Colour (0x808080));
    slController5->addListener (this);

    addAndMakeVisible (slController6 = new Slider (String::empty));
    slController6->setTooltip (T("Envelope Decay"));
    slController6->setRange (0, 127, 1);
    slController6->setSliderStyle (Slider::RotaryVerticalDrag);
    slController6->setTextBoxStyle (Slider::TextBoxAbove, false, 35, 15);
    slController6->setColour (Slider::textBoxBackgroundColourId, Colour (0x27ffffff));
    slController6->setColour (Slider::textBoxOutlineColourId, Colour (0x808080));
    slController6->addListener (this);

    addAndMakeVisible (slController7 = new Slider (String::empty));
    slController7->setTooltip (T("Envelope Sustain"));
    slController7->setRange (0, 127, 1);
    slController7->setSliderStyle (Slider::RotaryVerticalDrag);
    slController7->setTextBoxStyle (Slider::TextBoxAbove, false, 35, 15);
    slController7->setColour (Slider::textBoxBackgroundColourId, Colour (0x27ffffff));
    slController7->setColour (Slider::textBoxOutlineColourId, Colour (0x808080));
    slController7->addListener (this);

    addAndMakeVisible (slController8 = new Slider (String::empty));
    slController8->setTooltip (T("Envelope Release"));
    slController8->setRange (0, 127, 1);
    slController8->setSliderStyle (Slider::RotaryVerticalDrag);
    slController8->setTextBoxStyle (Slider::TextBoxAbove, false, 35, 15);
    slController8->setColour (Slider::textBoxBackgroundColourId, Colour (0x27ffffff));
    slController8->setColour (Slider::textBoxOutlineColourId, Colour (0x808080));
    slController8->addListener (this);

    addAndMakeVisible (lbController2 = new Label (String::empty,
                                                  T("pan")));
    lbController2->setFont (Font (Font::getDefaultSansSerifFontName(), 11.0000f, Font::plain));
    lbController2->setJustificationType (Justification::centred);
    lbController2->setEditable (false, false, false);
    lbController2->setColour (Label::textColourId, Colours::white);
    lbController2->setColour (Label::outlineColourId, Colour (0x0));
    lbController2->setColour (TextEditor::textColourId, Colours::black);
    lbController2->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (lbController3 = new Label (String::empty,
                                                  T("expr")));
    lbController3->setFont (Font (Font::getDefaultSansSerifFontName(), 11.0000f, Font::plain));
    lbController3->setJustificationType (Justification::centred);
    lbController3->setEditable (false, false, false);
    lbController3->setColour (Label::textColourId, Colours::white);
    lbController3->setColour (Label::outlineColourId, Colour (0x0));
    lbController3->setColour (TextEditor::textColourId, Colours::black);
    lbController3->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (lbController4 = new Label (String::empty,
                                                  T("cutoff")));
    lbController4->setFont (Font (Font::getDefaultSansSerifFontName(), 11.0000f, Font::plain));
    lbController4->setJustificationType (Justification::centred);
    lbController4->setEditable (false, false, false);
    lbController4->setColour (Label::textColourId, Colours::white);
    lbController4->setColour (Label::outlineColourId, Colour (0x0));
    lbController4->setColour (TextEditor::textColourId, Colours::black);
    lbController4->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (lbController5 = new Label (String::empty,
                                                  T("reso")));
    lbController5->setFont (Font (Font::getDefaultSansSerifFontName(), 11.0000f, Font::plain));
    lbController5->setJustificationType (Justification::centred);
    lbController5->setEditable (false, false, false);
    lbController5->setColour (Label::textColourId, Colours::white);
    lbController5->setColour (Label::outlineColourId, Colour (0x0));
    lbController5->setColour (TextEditor::textColourId, Colours::black);
    lbController5->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (lbController6 = new Label (String::empty,
                                                  T("A")));
    lbController6->setFont (Font (Font::getDefaultSansSerifFontName(), 11.0000f, Font::plain));
    lbController6->setJustificationType (Justification::centred);
    lbController6->setEditable (false, false, false);
    lbController6->setColour (Label::textColourId, Colours::white);
    lbController6->setColour (Label::outlineColourId, Colour (0x0));
    lbController6->setColour (TextEditor::textColourId, Colours::black);
    lbController6->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (lbController7 = new Label (String::empty,
                                                  T("D")));
    lbController7->setFont (Font (Font::getDefaultSansSerifFontName(), 11.0000f, Font::plain));
    lbController7->setJustificationType (Justification::centred);
    lbController7->setEditable (false, false, false);
    lbController7->setColour (Label::textColourId, Colours::white);
    lbController7->setColour (Label::outlineColourId, Colour (0x0));
    lbController7->setColour (TextEditor::textColourId, Colours::black);
    lbController7->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (lbController8 = new Label (String::empty,
                                                  T("S")));
    lbController8->setFont (Font (Font::getDefaultSansSerifFontName(), 11.0000f, Font::plain));
    lbController8->setJustificationType (Justification::centred);
    lbController8->setEditable (false, false, false);
    lbController8->setColour (Label::textColourId, Colours::white);
    lbController8->setColour (Label::outlineColourId, Colour (0x0));
    lbController8->setColour (TextEditor::textColourId, Colours::black);
    lbController8->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (lbController9 = new Label (String::empty,
                                                  T("R")));
    lbController9->setFont (Font (Font::getDefaultSansSerifFontName(), 11.0000f, Font::plain));
    lbController9->setJustificationType (Justification::centred);
    lbController9->setEditable (false, false, false);
    lbController9->setColour (Label::textColourId, Colours::white);
    lbController9->setColour (Label::outlineColourId, Colour (0x0));
    lbController9->setColour (TextEditor::textColourId, Colours::black);
    lbController9->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (slModWheel = new Slider (String::empty));
    slModWheel->setTooltip (T("Modulation wheel"));
    slModWheel->setRange (0, 127, 1);
    slModWheel->setSliderStyle (Slider::RotaryVerticalDrag);
    slModWheel->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    slModWheel->addListener (this);

    addAndMakeVisible (slBendRange = new Slider (String::empty));
    slBendRange->setTooltip (T("Pitch bend range in semitones"));
    slBendRange->setRange (-24, 24, 1);
    slBendRange->setSliderStyle (Slider::IncDecButtons);
    slBendRange->setTextBoxStyle (Slider::TextBoxLeft, false, 30, 20);
    slBendRange->setColour (Slider::thumbColourId, Colour (0xffbfbfbf));
    slBendRange->setColour (Slider::textBoxTextColourId, Colours::white);
    slBendRange->setColour (Slider::textBoxBackgroundColourId, Colour (0x27ffffff));
    slBendRange->setColour (Slider::textBoxOutlineColourId, Colour (0x36ffffff));
    slBendRange->addListener (this);


    //[UserPreSize]

    midiChannel = 1;

    MidiKeyboardState* keyboardState = owner->getKeyboardState ();
    addAndMakeVisible (keyboardComponent = new MidiKeyboardComponent (*keyboardState,
                                                                      MidiKeyboardComponent::horizontalKeyboard));

    cmbChannel->setSelectedId (midiChannel);
    slTranspose->setEnabled (false);
    //[/UserPreSize]

    setSize (696, 200);

    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

MidiKeyboardEditor::~MidiKeyboardEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    deleteAndZero (keyboardComponent);
    //[/Destructor_pre]

    deleteAndZero (slPitchBend);
    deleteAndZero (cmbChannel);
    deleteAndZero (lbChannel);
    deleteAndZero (slVelocity);
    deleteAndZero (grControllers);
    deleteAndZero (btnTranspose);
    deleteAndZero (slTranspose);
    deleteAndZero (slVolume);
    deleteAndZero (lbController);
    deleteAndZero (slController1);
    deleteAndZero (slController2);
    deleteAndZero (slController3);
    deleteAndZero (slController4);
    deleteAndZero (slController5);
    deleteAndZero (slController6);
    deleteAndZero (slController7);
    deleteAndZero (slController8);
    deleteAndZero (lbController2);
    deleteAndZero (lbController3);
    deleteAndZero (lbController4);
    deleteAndZero (lbController5);
    deleteAndZero (lbController6);
    deleteAndZero (lbController7);
    deleteAndZero (lbController8);
    deleteAndZero (lbController9);
    deleteAndZero (slModWheel);
    deleteAndZero (slBendRange);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MidiKeyboardEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff8796af));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MidiKeyboardEditor::resized()
{
    slPitchBend->setBounds (8, 56, 192, 24);
    cmbChannel->setBounds (72, 8, 40, 20);
    lbChannel->setBounds (8, 8, 56, 24);
    slVelocity->setBounds (8, 32, 296, 24);
    grControllers->setBounds (304, 0, 392, 88);
    btnTranspose->setBounds (120, 8, 88, 24);
    slTranspose->setBounds (208, 8, 96, 24);
    slVolume->setBounds (632, 16, 56, 56);
    lbController->setBounds (632, 72, 56, 8);
    slController1->setBounds (312, 16, 40, 56);
    slController2->setBounds (352, 16, 40, 56);
    slController3->setBounds (392, 16, 40, 56);
    slController4->setBounds (432, 16, 40, 56);
    slController5->setBounds (472, 16, 40, 56);
    slController6->setBounds (512, 16, 40, 56);
    slController7->setBounds (552, 16, 40, 56);
    slController8->setBounds (592, 16, 40, 56);
    lbController2->setBounds (312, 72, 40, 8);
    lbController3->setBounds (352, 72, 40, 8);
    lbController4->setBounds (392, 72, 40, 8);
    lbController5->setBounds (432, 72, 40, 8);
    lbController6->setBounds (472, 72, 40, 8);
    lbController7->setBounds (512, 72, 40, 8);
    lbController8->setBounds (552, 72, 40, 8);
    lbController9->setBounds (592, 72, 40, 8);
    slModWheel->setBounds (272, 48, 32, 40);
    slBendRange->setBounds (200, 56, 72, 24);
    //[UserResized] Add your own custom resize handling here..
    keyboardComponent->setBounds ((getWidth() / 2) - ((696) / 2), getHeight() - 112, 696, 112);
    //[/UserResized]
}

void MidiKeyboardEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == slPitchBend)
    {
        //[UserSliderCode_slPitchBend] -- add your slider handling code here..
        MidiMessageCollector* midiCollector = owner->getMessageCollector ();

        MidiMessage message = MidiMessage::pitchWheel (midiChannel, 8192 + (int) slPitchBend->getValue ());
        message.setTimeStamp (Time::getMillisecondCounterHiRes());

        midiCollector->addMessageToQueue (message);
        //[/UserSliderCode_slPitchBend]
    }
    else if (sliderThatWasMoved == slVelocity)
    {
        //[UserSliderCode_slVelocity] -- add your slider handling code here..
        //keyboardComponent->setVelocity (slVelocity->getValue () * float_MidiScaler);
        //[/UserSliderCode_slVelocity]
    }
    else if (sliderThatWasMoved == slTranspose)
    {
        //[UserSliderCode_slTranspose] -- add your slider handling code here..
        //[/UserSliderCode_slTranspose]
    }
    else if (sliderThatWasMoved == slVolume)
    {
        //[UserSliderCode_slVolume] -- add your slider handling code here..
        addControllerMessage (0x07 /*VOL(0x07)*/, (int) slVolume->getValue ());
        //[/UserSliderCode_slVolume]
    }
    else if (sliderThatWasMoved == slController1)
    {
        //[UserSliderCode_slController1] -- add your slider handling code here..
        addControllerMessage (0x08 /*VOL(0x07)*/, (int) slController1->getValue ());
        //[/UserSliderCode_slController1]
    }
    else if (sliderThatWasMoved == slController2)
    {
        //[UserSliderCode_slController2] -- add your slider handling code here..
        addControllerMessage (0x0A /*VOL(0x07)*/, (int) slController2->getValue ());
        //[/UserSliderCode_slController2]
    }
    else if (sliderThatWasMoved == slController3)
    {
        //[UserSliderCode_slController3] -- add your slider handling code here..
        addControllerMessage (0x0B /*VOL(0x07)*/, (int) slController3->getValue ());
        //[/UserSliderCode_slController3]
    }
    else if (sliderThatWasMoved == slController4)
    {
        //[UserSliderCode_slController4] -- add your slider handling code here..
        addControllerMessage (0x0C /*VOL(0x07)*/, (int) slController4->getValue ());
        //[/UserSliderCode_slController4]
    }
    else if (sliderThatWasMoved == slController5)
    {
        //[UserSliderCode_slController5] -- add your slider handling code here..
        addControllerMessage (0x0D /*VOL(0x07)*/, (int) slController5->getValue ());
        //[/UserSliderCode_slController5]
    }
    else if (sliderThatWasMoved == slController6)
    {
        //[UserSliderCode_slController6] -- add your slider handling code here..
        addControllerMessage (0x0E /*VOL(0x07)*/, (int) slController6->getValue ());
        //[/UserSliderCode_slController6]
    }
    else if (sliderThatWasMoved == slController7)
    {
        //[UserSliderCode_slController7] -- add your slider handling code here..
        addControllerMessage (0x0F /*VOL(0x07)*/, (int) slController7->getValue ());
        //[/UserSliderCode_slController7]
    }
    else if (sliderThatWasMoved == slController8)
    {
        //[UserSliderCode_slController8] -- add your slider handling code here..
        addControllerMessage (0x10 /*VOL(0x07)*/, (int) slController8->getValue ());
        //[/UserSliderCode_slController8]
    }
    else if (sliderThatWasMoved == slModWheel)
    {
        //[UserSliderCode_slModWheel] -- add your slider handling code here..
        //[/UserSliderCode_slModWheel]
    }
    else if (sliderThatWasMoved == slBendRange)
    {
        //[UserSliderCode_slBendRange] -- add your slider handling code here..
        //[/UserSliderCode_slBendRange]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void MidiKeyboardEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == cmbChannel)
    {
        //[UserComboBoxCode_cmbChannel] -- add your combo box handling code here..
        midiChannel = cmbChannel->getSelectedId ();
        keyboardComponent->setMidiChannel (midiChannel);
        //[/UserComboBoxCode_cmbChannel]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void MidiKeyboardEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == btnTranspose)
    {
        //[UserButtonCode_btnTranspose] -- add your button handler code here..
        slTranspose->setEnabled (btnTranspose->getToggleState ());
        //[/UserButtonCode_btnTranspose]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

bool MidiKeyboardEditor::keyPressed (const KeyPress& key)
{
    //[UserCode_keyPressed] -- Add your code here...
    return false;  // Return true if your handler uses this key event, or false to allow it to be passed-on.
    //[/UserCode_keyPressed]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void MidiKeyboardEditor::updateParameters ()
{

}

void MidiKeyboardEditor::addControllerMessage (const int controllerNumber,
                                               const int controllerValue)
{
    MidiMessageCollector* midiCollector = owner->getMessageCollector ();

    MidiMessage message = MidiMessage::controllerEvent (midiChannel,
                                                        controllerNumber,
                                                        controllerValue);

    message.setTimeStamp (Time::getMillisecondCounterHiRes());

    midiCollector->addMessageToQueue (message);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MidiKeyboardEditor" componentName=""
                 parentClasses="public PluginEditorComponent" constructorParams="MidiKeyboardPlugin* owner_"
                 variableInitialisers="PluginEditorComponent (owner_)&#10;owner (owner_)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="1" initialWidth="696" initialHeight="200">
  <METHODS>
    <METHOD name="keyPressed (const KeyPress&amp; key)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ff8796af"/>
  <SLIDER name="" id="4eb58391be3c3aa4" memberName="slPitchBend" virtualName=""
          explicitFocusOrder="0" pos="8 56 192 24" tooltip="Pitch bender"
          thumbcol="ffd77f00" trackcol="7f7e7e7e" min="-8192" max="8191"
          int="1" style="LinearHorizontal" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <COMBOBOX name="" id="1979cabebb18c1ae" memberName="cmbChannel" virtualName=""
            explicitFocusOrder="0" pos="72 8 40 20" tooltip="MIDI output channel number"
            editable="0" layout="36" items="1&#10;2&#10;3&#10;4&#10;5&#10;6&#10;7&#10;8&#10;9&#10;10&#10;11&#10;12&#10;13&#10;14&#10;15&#10;16"
            textWhenNonSelected="1" textWhenNoItems="-"/>
  <LABEL name="" id="5865d1247260d6f0" memberName="lbChannel" virtualName=""
         explicitFocusOrder="0" pos="8 8 56 24" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="midi ch" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="34"/>
  <SLIDER name="" id="cd148c8a7160d1b0" memberName="slVelocity" virtualName=""
          explicitFocusOrder="0" pos="8 32 296 24" tooltip="The velocity range of output notes"
          thumbcol="ffeeeeee" trackcol="66777777" textboxtext="ffffffff"
          textboxbkgd="27ffffff" textboxhighlight="4061a2ff" min="0" max="127"
          int="1" style="LinearHorizontal" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="35" textBoxHeight="20" skewFactor="1"/>
  <GROUPCOMPONENT name="" id="e568262b90faf2f4" memberName="grControllers" virtualName=""
                  explicitFocusOrder="0" pos="304 0 392 88" outlinecol="66ffffff"
                  textcol="ffffffff" title="controllers" textpos="34"/>
  <TOGGLEBUTTON name="" id="551a3faa58c0f160" memberName="btnTranspose" virtualName=""
                explicitFocusOrder="0" pos="120 8 88 24" tooltip="Switch note transpose on/off"
                txtcol="ffffffff" buttonText="transpose" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <SLIDER name="" id="a4bce73124a54ba6" memberName="slTranspose" virtualName=""
          explicitFocusOrder="0" pos="208 8 96 24" tooltip="Number of semitones to transpose"
          thumbcol="ffbfbfbf" textboxtext="ffffffff" textboxbkgd="27ffffff"
          textboxoutline="36ffffff" min="-48" max="48" int="1" style="IncDecButtons"
          textBoxPos="TextBoxLeft" textBoxEditable="1" textBoxWidth="35"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="5a9c70062c5bc5a2" memberName="slVolume" virtualName=""
          explicitFocusOrder="0" pos="632 16 56 56" tooltip="Volume" textboxbkgd="27ffffff"
          min="0" max="127" int="1" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="35" textBoxHeight="15" skewFactor="1"/>
  <LABEL name="" id="84fa83bce3aba6c1" memberName="lbController" virtualName=""
         explicitFocusOrder="0" pos="632 72 56 8" textCol="ffffffff" outlineCol="0"
         edTextCol="ff000000" edBkgCol="0" labelText="volume" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default sans-serif font"
         fontsize="12.9" bold="0" italic="0" justification="36"/>
  <SLIDER name="" id="81290e488fc0b85f" memberName="slController1" virtualName=""
          explicitFocusOrder="0" pos="312 16 40 56" tooltip="Panning" textboxbkgd="27ffffff"
          textboxoutline="808080" min="-63" max="64" int="1" style="RotaryVerticalDrag"
          textBoxPos="TextBoxAbove" textBoxEditable="1" textBoxWidth="35"
          textBoxHeight="15" skewFactor="1"/>
  <SLIDER name="" id="c1c34631bc0e298a" memberName="slController2" virtualName=""
          explicitFocusOrder="0" pos="352 16 40 56" tooltip="Expression"
          textboxbkgd="27ffffff" textboxoutline="808080" min="0" max="127"
          int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="35" textBoxHeight="15" skewFactor="1"/>
  <SLIDER name="" id="51f9efdafc33203b" memberName="slController3" virtualName=""
          explicitFocusOrder="0" pos="392 16 40 56" tooltip="Filter cutoff frequency"
          textboxbkgd="27ffffff" textboxoutline="808080" min="0" max="127"
          int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="35" textBoxHeight="15" skewFactor="1"/>
  <SLIDER name="" id="100bea74a4eb80e1" memberName="slController4" virtualName=""
          explicitFocusOrder="0" pos="432 16 40 56" tooltip="Filter cutoff resonance (Q-factor)"
          textboxbkgd="27ffffff" textboxoutline="808080" min="0" max="127"
          int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="35" textBoxHeight="15" skewFactor="1"/>
  <SLIDER name="" id="b52a0622993b4b4c" memberName="slController5" virtualName=""
          explicitFocusOrder="0" pos="472 16 40 56" tooltip="Envelope Attack"
          textboxbkgd="27ffffff" textboxoutline="808080" min="0" max="127"
          int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="35" textBoxHeight="15" skewFactor="1"/>
  <SLIDER name="" id="f1dd8894b455a936" memberName="slController6" virtualName=""
          explicitFocusOrder="0" pos="512 16 40 56" tooltip="Envelope Decay"
          textboxbkgd="27ffffff" textboxoutline="808080" min="0" max="127"
          int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="35" textBoxHeight="15" skewFactor="1"/>
  <SLIDER name="" id="d49f2baa32fd3b8a" memberName="slController7" virtualName=""
          explicitFocusOrder="0" pos="552 16 40 56" tooltip="Envelope Sustain"
          textboxbkgd="27ffffff" textboxoutline="808080" min="0" max="127"
          int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="35" textBoxHeight="15" skewFactor="1"/>
  <SLIDER name="" id="1d4dce24537e1892" memberName="slController8" virtualName=""
          explicitFocusOrder="0" pos="592 16 40 56" tooltip="Envelope Release"
          textboxbkgd="27ffffff" textboxoutline="808080" min="0" max="127"
          int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="35" textBoxHeight="15" skewFactor="1"/>
  <LABEL name="" id="2e620dc08f4b1b93" memberName="lbController2" virtualName=""
         explicitFocusOrder="0" pos="312 72 40 8" textCol="ffffffff" outlineCol="0"
         edTextCol="ff000000" edBkgCol="0" labelText="pan" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default sans-serif font"
         fontsize="11" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="139ab7a074c03d8" memberName="lbController3" virtualName=""
         explicitFocusOrder="0" pos="352 72 40 8" textCol="ffffffff" outlineCol="0"
         edTextCol="ff000000" edBkgCol="0" labelText="expr" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default sans-serif font"
         fontsize="11" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="fb357e740beda113" memberName="lbController4" virtualName=""
         explicitFocusOrder="0" pos="392 72 40 8" textCol="ffffffff" outlineCol="0"
         edTextCol="ff000000" edBkgCol="0" labelText="cutoff" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default sans-serif font"
         fontsize="11" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="771a551220ceb111" memberName="lbController5" virtualName=""
         explicitFocusOrder="0" pos="432 72 40 8" textCol="ffffffff" outlineCol="0"
         edTextCol="ff000000" edBkgCol="0" labelText="reso" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default sans-serif font"
         fontsize="11" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="c5226259e13fdcf1" memberName="lbController6" virtualName=""
         explicitFocusOrder="0" pos="472 72 40 8" textCol="ffffffff" outlineCol="0"
         edTextCol="ff000000" edBkgCol="0" labelText="A" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default sans-serif font"
         fontsize="11" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="24c9a0a012e777c1" memberName="lbController7" virtualName=""
         explicitFocusOrder="0" pos="512 72 40 8" textCol="ffffffff" outlineCol="0"
         edTextCol="ff000000" edBkgCol="0" labelText="D" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default sans-serif font"
         fontsize="11" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="d6f12b87a6900369" memberName="lbController8" virtualName=""
         explicitFocusOrder="0" pos="552 72 40 8" textCol="ffffffff" outlineCol="0"
         edTextCol="ff000000" edBkgCol="0" labelText="S" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default sans-serif font"
         fontsize="11" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="5289c5283c5f9fc7" memberName="lbController9" virtualName=""
         explicitFocusOrder="0" pos="592 72 40 8" textCol="ffffffff" outlineCol="0"
         edTextCol="ff000000" edBkgCol="0" labelText="R" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default sans-serif font"
         fontsize="11" bold="0" italic="0" justification="36"/>
  <SLIDER name="" id="543a00b9dcc0777a" memberName="slModWheel" virtualName=""
          explicitFocusOrder="0" pos="272 48 32 40" tooltip="Modulation wheel"
          min="0" max="127" int="1" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="d63f24505dd3a3de" memberName="slBendRange" virtualName=""
          explicitFocusOrder="0" pos="200 56 72 24" tooltip="Pitch bend range in semitones"
          thumbcol="ffbfbfbf" textboxtext="ffffffff" textboxbkgd="27ffffff"
          textboxoutline="36ffffff" min="-24" max="24" int="1" style="IncDecButtons"
          textBoxPos="TextBoxLeft" textBoxEditable="1" textBoxWidth="30"
          textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
