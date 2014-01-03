/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  8 Aug 2009 12:26:56 pm

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
#include "synth.h"
//[/Headers]

#include "editor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
editor::editor (AudioProcessor *const ownerFilter)
    : AudioProcessorEditor(ownerFilter),
      groupComponent2 (0),
      groupComponent (0),
      label (0),
      label2 (0),
      slgain (0),
      slclip (0),
      slsaw (0),
      label3 (0),
      slrect (0),
      label4 (0),
      sltri (0),
      label5 (0),
      sltune (0),
      label6 (0),
      groupComponent3 (0),
      label7 (0),
      slcutoff (0),
      label8 (0),
      slreso (0),
      label9 (0),
      slbandwidth (0),
      label10 (0),
      slpasses (0),
      label11 (0),
      slvelocity (0),
      label12 (0),
      slinertia (0),
      label13 (0),
      slcurcutoff (0),
      label14 (0)
{
    addAndMakeVisible (groupComponent2 = new GroupComponent (T("new group"),
                                                             T("Oscillators")));
    groupComponent2->setExplicitFocusOrder (1);
    groupComponent2->setTextLabelPosition (Justification::centredLeft);
    groupComponent2->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    groupComponent2->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (groupComponent = new GroupComponent (T("new group"),
                                                            T("Output")));
    groupComponent->setExplicitFocusOrder (1);
    groupComponent->setTextLabelPosition (Justification::centredLeft);
    groupComponent->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    groupComponent->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (label = new Label (T("new label"),
                                          T("Gain")));
    label->setFont (Font (15.0000f, Font::plain));
    label->setJustificationType (Justification::centredRight);
    label->setEditable (false, false, false);
    label->setColour (Label::textColourId, Colours::white);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label2 = new Label (T("new label"),
                                           T("Clip")));
    label2->setFont (Font (15.0000f, Font::plain));
    label2->setJustificationType (Justification::centredRight);
    label2->setEditable (false, false, false);
    label2->setColour (Label::textColourId, Colours::white);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (slgain = new Slider (T("new slider")));
    slgain->setRange (0, 4, 0.0001);
    slgain->setSliderStyle (Slider::LinearHorizontal);
    slgain->setTextBoxStyle (Slider::TextBoxRight, false, 60, 20);
    slgain->setColour (Slider::backgroundColourId, Colour (0x868686));
    slgain->setColour (Slider::textBoxTextColourId, Colours::white);
    slgain->setColour (Slider::textBoxBackgroundColourId, Colour (0x565656));
    slgain->setColour (Slider::textBoxHighlightColourId, Colour (0x409a9aff));
    slgain->setColour (Slider::textBoxOutlineColourId, Colour (0x0));
    slgain->addListener (this);
    slgain->setSkewFactor (0.3);

    addAndMakeVisible (slclip = new Slider (T("new slider")));
    slclip->setRange (0, 5, 0.0001);
    slclip->setSliderStyle (Slider::LinearHorizontal);
    slclip->setTextBoxStyle (Slider::TextBoxRight, false, 60, 20);
    slclip->setColour (Slider::backgroundColourId, Colour (0x868686));
    slclip->setColour (Slider::textBoxTextColourId, Colours::white);
    slclip->setColour (Slider::textBoxBackgroundColourId, Colour (0x565656));
    slclip->setColour (Slider::textBoxHighlightColourId, Colour (0x409a9aff));
    slclip->setColour (Slider::textBoxOutlineColourId, Colour (0x0));
    slclip->addListener (this);
    slclip->setSkewFactor (0.5);

    addAndMakeVisible (slsaw = new Slider (T("new slider")));
    slsaw->setRange (0, 1, 0);
    slsaw->setSliderStyle (Slider::Rotary);
    slsaw->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    slsaw->setColour (Slider::thumbColourId, Colour (0xffbbf2ff));
    slsaw->setColour (Slider::rotarySliderFillColourId, Colour (0x7f00b9ff));
    slsaw->setColour (Slider::rotarySliderOutlineColourId, Colour (0x80ffffff));
    slsaw->addListener (this);

    addAndMakeVisible (label3 = new Label (T("new label"),
                                           T("Saw")));
    label3->setFont (Font (15.0000f, Font::plain));
    label3->setJustificationType (Justification::centred);
    label3->setEditable (false, false, false);
    label3->setColour (Label::textColourId, Colours::white);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (slrect = new Slider (T("new slider")));
    slrect->setRange (0, 1, 0);
    slrect->setSliderStyle (Slider::Rotary);
    slrect->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    slrect->setColour (Slider::thumbColourId, Colour (0xffbbf2ff));
    slrect->setColour (Slider::rotarySliderFillColourId, Colour (0x7f00b9ff));
    slrect->setColour (Slider::rotarySliderOutlineColourId, Colour (0x80ffffff));
    slrect->addListener (this);

    addAndMakeVisible (label4 = new Label (T("new label"),
                                           T("Rect")));
    label4->setFont (Font (15.0000f, Font::plain));
    label4->setJustificationType (Justification::centred);
    label4->setEditable (false, false, false);
    label4->setColour (Label::textColourId, Colours::white);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (sltri = new Slider (T("new slider")));
    sltri->setRange (0, 1, 0);
    sltri->setSliderStyle (Slider::Rotary);
    sltri->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sltri->setColour (Slider::thumbColourId, Colour (0xffbbf2ff));
    sltri->setColour (Slider::rotarySliderFillColourId, Colour (0x7f00b9ff));
    sltri->setColour (Slider::rotarySliderOutlineColourId, Colour (0x80ffffff));
    sltri->addListener (this);

    addAndMakeVisible (label5 = new Label (T("new label"),
                                           T("Tri")));
    label5->setFont (Font (15.0000f, Font::plain));
    label5->setJustificationType (Justification::centred);
    label5->setEditable (false, false, false);
    label5->setColour (Label::textColourId, Colours::white);
    label5->setColour (TextEditor::textColourId, Colours::black);
    label5->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (sltune = new Slider (T("new slider")));
    sltune->setRange (0, 1, 0);
    sltune->setSliderStyle (Slider::Rotary);
    sltune->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sltune->setColour (Slider::thumbColourId, Colour (0xffbbf2ff));
    sltune->setColour (Slider::rotarySliderFillColourId, Colour (0x7f00b9ff));
    sltune->setColour (Slider::rotarySliderOutlineColourId, Colour (0x80ffffff));
    sltune->addListener (this);

    addAndMakeVisible (label6 = new Label (T("new label"),
                                           T("Tune")));
    label6->setFont (Font (15.0000f, Font::plain));
    label6->setJustificationType (Justification::centred);
    label6->setEditable (false, false, false);
    label6->setColour (Label::textColourId, Colours::white);
    label6->setColour (TextEditor::textColourId, Colours::black);
    label6->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (groupComponent3 = new GroupComponent (T("new group"),
                                                             T("Filter")));
    groupComponent3->setExplicitFocusOrder (1);
    groupComponent3->setTextLabelPosition (Justification::centredLeft);
    groupComponent3->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    groupComponent3->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (label7 = new Label (T("new label"),
                                           T("Filter X")));
    label7->setFont (Font (15.0000f, Font::plain));
    label7->setJustificationType (Justification::centredRight);
    label7->setEditable (false, false, false);
    label7->setColour (Label::textColourId, Colours::white);
    label7->setColour (TextEditor::textColourId, Colours::black);
    label7->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (slcutoff = new Slider (T("new slider")));
    slcutoff->setRange (0, 4, 0.0001);
    slcutoff->setSliderStyle (Slider::LinearHorizontal);
    slcutoff->setTextBoxStyle (Slider::TextBoxRight, false, 60, 20);
    slcutoff->setColour (Slider::backgroundColourId, Colour (0x868686));
    slcutoff->setColour (Slider::textBoxTextColourId, Colours::white);
    slcutoff->setColour (Slider::textBoxBackgroundColourId, Colour (0x565656));
    slcutoff->setColour (Slider::textBoxHighlightColourId, Colour (0x409a9aff));
    slcutoff->setColour (Slider::textBoxOutlineColourId, Colour (0x0));
    slcutoff->addListener (this);
    slcutoff->setSkewFactor (0.5);

    addAndMakeVisible (label8 = new Label (T("new label"),
                                           T("Resonance")));
    label8->setFont (Font (15.0000f, Font::plain));
    label8->setJustificationType (Justification::centredRight);
    label8->setEditable (false, false, false);
    label8->setColour (Label::textColourId, Colours::white);
    label8->setColour (TextEditor::textColourId, Colours::black);
    label8->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (slreso = new Slider (T("new slider")));
    slreso->setRange (0, 4, 0.0001);
    slreso->setSliderStyle (Slider::LinearHorizontal);
    slreso->setTextBoxStyle (Slider::TextBoxRight, false, 60, 20);
    slreso->setColour (Slider::backgroundColourId, Colour (0x868686));
    slreso->setColour (Slider::textBoxTextColourId, Colours::white);
    slreso->setColour (Slider::textBoxBackgroundColourId, Colour (0x565656));
    slreso->setColour (Slider::textBoxHighlightColourId, Colour (0x409a9aff));
    slreso->setColour (Slider::textBoxOutlineColourId, Colour (0x0));
    slreso->addListener (this);
    slreso->setSkewFactor (0.5);

    addAndMakeVisible (label9 = new Label (T("new label"),
                                           T("Bandwidth")));
    label9->setFont (Font (15.0000f, Font::plain));
    label9->setJustificationType (Justification::centredRight);
    label9->setEditable (false, false, false);
    label9->setColour (Label::textColourId, Colours::white);
    label9->setColour (TextEditor::textColourId, Colours::black);
    label9->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (slbandwidth = new Slider (T("new slider")));
    slbandwidth->setRange (0, 4, 0.0001);
    slbandwidth->setSliderStyle (Slider::LinearHorizontal);
    slbandwidth->setTextBoxStyle (Slider::TextBoxRight, false, 60, 20);
    slbandwidth->setColour (Slider::backgroundColourId, Colour (0x868686));
    slbandwidth->setColour (Slider::textBoxTextColourId, Colours::white);
    slbandwidth->setColour (Slider::textBoxBackgroundColourId, Colour (0x565656));
    slbandwidth->setColour (Slider::textBoxHighlightColourId, Colour (0x409a9aff));
    slbandwidth->setColour (Slider::textBoxOutlineColourId, Colour (0x0));
    slbandwidth->addListener (this);
    slbandwidth->setSkewFactor (0.5);

    addAndMakeVisible (label10 = new Label (T("new label"),
                                            T("Passes")));
    label10->setFont (Font (15.0000f, Font::plain));
    label10->setJustificationType (Justification::centredRight);
    label10->setEditable (false, false, false);
    label10->setColour (Label::textColourId, Colours::white);
    label10->setColour (TextEditor::textColourId, Colours::black);
    label10->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (slpasses = new Slider (T("new slider")));
    slpasses->setRange (0, 4, 0.0001);
    slpasses->setSliderStyle (Slider::LinearHorizontal);
    slpasses->setTextBoxStyle (Slider::TextBoxRight, false, 60, 20);
    slpasses->setColour (Slider::backgroundColourId, Colour (0x868686));
    slpasses->setColour (Slider::textBoxTextColourId, Colours::white);
    slpasses->setColour (Slider::textBoxBackgroundColourId, Colour (0x565656));
    slpasses->setColour (Slider::textBoxHighlightColourId, Colour (0x409a9aff));
    slpasses->setColour (Slider::textBoxOutlineColourId, Colour (0x0));
    slpasses->addListener (this);

    addAndMakeVisible (label11 = new Label (T("new label"),
                                            T("Velocity")));
    label11->setFont (Font (15.0000f, Font::plain));
    label11->setJustificationType (Justification::centredRight);
    label11->setEditable (false, false, false);
    label11->setColour (Label::textColourId, Colours::white);
    label11->setColour (TextEditor::textColourId, Colours::black);
    label11->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (slvelocity = new Slider (T("new slider")));
    slvelocity->setRange (0, 4, 0.0001);
    slvelocity->setSliderStyle (Slider::LinearHorizontal);
    slvelocity->setTextBoxStyle (Slider::TextBoxRight, false, 60, 20);
    slvelocity->setColour (Slider::backgroundColourId, Colour (0x868686));
    slvelocity->setColour (Slider::textBoxTextColourId, Colours::white);
    slvelocity->setColour (Slider::textBoxBackgroundColourId, Colour (0x565656));
    slvelocity->setColour (Slider::textBoxHighlightColourId, Colour (0x409a9aff));
    slvelocity->setColour (Slider::textBoxOutlineColourId, Colour (0x0));
    slvelocity->addListener (this);
    slvelocity->setSkewFactor (0.5);

    addAndMakeVisible (label12 = new Label (T("new label"),
                                            T("Inertia")));
    label12->setFont (Font (15.0000f, Font::plain));
    label12->setJustificationType (Justification::centredRight);
    label12->setEditable (false, false, false);
    label12->setColour (Label::textColourId, Colours::white);
    label12->setColour (TextEditor::textColourId, Colours::black);
    label12->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (slinertia = new Slider (T("new slider")));
    slinertia->setRange (0, 4, 0.0001);
    slinertia->setSliderStyle (Slider::LinearHorizontal);
    slinertia->setTextBoxStyle (Slider::TextBoxRight, false, 60, 20);
    slinertia->setColour (Slider::backgroundColourId, Colour (0x868686));
    slinertia->setColour (Slider::textBoxTextColourId, Colours::white);
    slinertia->setColour (Slider::textBoxBackgroundColourId, Colour (0x565656));
    slinertia->setColour (Slider::textBoxHighlightColourId, Colour (0x409a9aff));
    slinertia->setColour (Slider::textBoxOutlineColourId, Colour (0x0));
    slinertia->addListener (this);
    slinertia->setSkewFactor (0.5);

    addAndMakeVisible (label13 = new Label (T("new label"),
                                            T("Filter Freq")));
    label13->setFont (Font (15.0000f, Font::plain));
    label13->setJustificationType (Justification::centredRight);
    label13->setEditable (false, false, false);
    label13->setColour (Label::textColourId, Colours::white);
    label13->setColour (TextEditor::textColourId, Colours::black);
    label13->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (slcurcutoff = new Slider (T("new slider")));
    slcurcutoff->setRange (0, 4, 0.0001);
    slcurcutoff->setSliderStyle (Slider::LinearHorizontal);
    slcurcutoff->setTextBoxStyle (Slider::TextBoxRight, false, 60, 20);
    slcurcutoff->setColour (Slider::backgroundColourId, Colour (0x868686));
    slcurcutoff->setColour (Slider::textBoxTextColourId, Colours::white);
    slcurcutoff->setColour (Slider::textBoxBackgroundColourId, Colour (0x565656));
    slcurcutoff->setColour (Slider::textBoxHighlightColourId, Colour (0x409a9aff));
    slcurcutoff->setColour (Slider::textBoxOutlineColourId, Colour (0x0));
    slcurcutoff->addListener (this);
    slcurcutoff->setSkewFactor (0.4);

    addAndMakeVisible (label14 = new Label (T("new label"),
                                            T("Mix")));
    label14->setFont (Font (15.0000f, Font::plain));
    label14->setJustificationType (Justification::centredRight);
    label14->setEditable (false, false, false);
    label14->setColour (Label::textColourId, Colours::white);
    label14->setColour (TextEditor::textColourId, Colours::black);
    label14->setColour (TextEditor::backgroundColourId, Colour (0x0));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (400, 438);

    //[Constructor] You can add your own custom stuff here..

    ((wolp*)ownerFilter)->addChangeListener(this);

    //[/Constructor]
}

editor::~editor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    ((wolp*)getAudioProcessor())->removeChangeListener(this);
    //[/Destructor_pre]

    deleteAndZero (groupComponent2);
    deleteAndZero (groupComponent);
    deleteAndZero (label);
    deleteAndZero (label2);
    deleteAndZero (slgain);
    deleteAndZero (slclip);
    deleteAndZero (slsaw);
    deleteAndZero (label3);
    deleteAndZero (slrect);
    deleteAndZero (label4);
    deleteAndZero (sltri);
    deleteAndZero (label5);
    deleteAndZero (sltune);
    deleteAndZero (label6);
    deleteAndZero (groupComponent3);
    deleteAndZero (label7);
    deleteAndZero (slcutoff);
    deleteAndZero (label8);
    deleteAndZero (slreso);
    deleteAndZero (label9);
    deleteAndZero (slbandwidth);
    deleteAndZero (label10);
    deleteAndZero (slpasses);
    deleteAndZero (label11);
    deleteAndZero (slvelocity);
    deleteAndZero (label12);
    deleteAndZero (slinertia);
    deleteAndZero (label13);
    deleteAndZero (slcurcutoff);
    deleteAndZero (label14);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void editor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::black);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void editor::resized()
{
    groupComponent2->setBounds (8, 8, 384, 104);
    groupComponent->setBounds (8, 344, 384, 80);
    label->setBounds (16, 368, 56, 16);
    label2->setBounds (16, 392, 56, 16);
    slgain->setBounds (80, 368, 304, 16);
    slclip->setBounds (80, 392, 304, 16);
    slsaw->setBounds (56, 32, 56, 48);
    label3->setBounds (56, 80, 56, 16);
    slrect->setBounds (136, 32, 56, 48);
    label4->setBounds (136, 80, 56, 16);
    sltri->setBounds (216, 32, 56, 48);
    label5->setBounds (216, 80, 56, 16);
    sltune->setBounds (320, 32, 56, 48);
    label6->setBounds (320, 80, 56, 16);
    groupComponent3->setBounds (8, 128, 384, 200);
    label7->setBounds (16, 152, 64, 16);
    slcutoff->setBounds (80, 152, 304, 16);
    label8->setBounds (16, 176, 64, 16);
    slreso->setBounds (80, 176, 304, 16);
    label9->setBounds (16, 200, 64, 16);
    slbandwidth->setBounds (80, 200, 304, 16);
    label10->setBounds (16, 224, 64, 16);
    slpasses->setBounds (80, 224, 304, 16);
    label11->setBounds (16, 248, 64, 16);
    slvelocity->setBounds (80, 248, 304, 16);
    label12->setBounds (16, 272, 64, 16);
    slinertia->setBounds (80, 272, 304, 16);
    label13->setBounds (16, 296, 64, 16);
    slcurcutoff->setBounds (80, 296, 304, 16);
    label14->setBounds (16, (32) + (48) / 2 - ((16) / 2), 32, 16);
    //[UserResized] Add your own custom resize handling here..
#if 1
    #define initslider(slidername, param)\
    sl##slidername->setRange(synth->paraminfos[wolp::param].min, synth->paraminfos[wolp::param].max);	\
    sl##slidername->setValue(synth->getParameter(wolp::param)*(synth->paraminfos[wolp::param].max-synth->paraminfos[wolp::param].min));
    wolp *synth= (wolp*)getAudioProcessor();
    initslider(saw, gsaw);
    initslider(rect, grect);
    initslider(tri, gtri);
    initslider(tune, tune);
    initslider(gain, gain);
    initslider(clip, clip);

    initslider(cutoff, cutoff);
    initslider(reso, resonance);
    initslider(bandwidth, bandwidth);
    initslider(passes, nfilters);
    initslider(velocity, velocity);
    initslider(inertia, inertia);
    initslider(curcutoff, curcutoff);

    slpasses->setRange(synth->paraminfos[wolp::nfilters].min, synth->paraminfos[wolp::nfilters].max, 1.0);
    slpasses->setValue(synth->getParameter(wolp::nfilters)*(synth->paraminfos[wolp::nfilters].max-synth->paraminfos[wolp::nfilters].min));
    #undef initslider
#endif
    //[/UserResized]
}

void editor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
#if 1
    wolp *synth= (wolp*)getAudioProcessor();
    #define updateval(param)\
    synth->setParameterNotifyingHost( wolp::param, sliderThatWasMoved->getValue() / \
		(synth->paraminfos[wolp::param].max-synth->paraminfos[wolp::param].min) )
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == slgain)
    {
        //[UserSliderCode_slgain] -- add your slider handling code here..
		updateval(gain);
        //[/UserSliderCode_slgain]
    }
    else if (sliderThatWasMoved == slclip)
    {
        //[UserSliderCode_slclip] -- add your slider handling code here..
		updateval(clip);
        //[/UserSliderCode_slclip]
    }
    else if (sliderThatWasMoved == slsaw)
    {
        //[UserSliderCode_slsaw] -- add your slider handling code here..
		updateval(gsaw);
        //[/UserSliderCode_slsaw]
    }
    else if (sliderThatWasMoved == slrect)
    {
        //[UserSliderCode_slrect] -- add your slider handling code here..
		updateval(grect);
        //[/UserSliderCode_slrect]
    }
    else if (sliderThatWasMoved == sltri)
    {
        //[UserSliderCode_sltri] -- add your slider handling code here..
		updateval(gtri);
        //[/UserSliderCode_sltri]
    }
    else if (sliderThatWasMoved == sltune)
    {
        //[UserSliderCode_sltune] -- add your slider handling code here..
		updateval(tune);
        //[/UserSliderCode_sltune]
    }
    else if (sliderThatWasMoved == slcutoff)
    {
        //[UserSliderCode_slcutoff] -- add your slider handling code here..
		updateval(cutoff);
        //[/UserSliderCode_slcutoff]
    }
    else if (sliderThatWasMoved == slreso)
    {
        //[UserSliderCode_slreso] -- add your slider handling code here..
		updateval(resonance);
        //[/UserSliderCode_slreso]
    }
    else if (sliderThatWasMoved == slbandwidth)
    {
        //[UserSliderCode_slbandwidth] -- add your slider handling code here..
		updateval(bandwidth);
        //[/UserSliderCode_slbandwidth]
    }
    else if (sliderThatWasMoved == slpasses)
    {
        //[UserSliderCode_slpasses] -- add your slider handling code here..
		updateval(nfilters);
        //[/UserSliderCode_slpasses]
    }
    else if (sliderThatWasMoved == slvelocity)
    {
        //[UserSliderCode_slvelocity] -- add your slider handling code here..
		updateval(velocity);
        //[/UserSliderCode_slvelocity]
    }
    else if (sliderThatWasMoved == slinertia)
    {
        //[UserSliderCode_slinertia] -- add your slider handling code here..
		updateval(inertia);
        //[/UserSliderCode_slinertia]
    }
    else if (sliderThatWasMoved == slcurcutoff)
    {
        //[UserSliderCode_slcurcutoff] -- add your slider handling code here..
		updateval(curcutoff);
        //[/UserSliderCode_slcurcutoff]
    }

    //[UsersliderValueChanged_Post]
    #undef updateval
#endif
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void editor::changeListenerCallback(void *objectThatHasChanged)
{
    int idx= (int)objectThatHasChanged;
    if(idx==wolp::curcutoff)
    {
        wolp *synth= (wolp*)getAudioProcessor();
        slcurcutoff->setValue( synth->getparam(wolp::curcutoff), false );
    }
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="editor" componentName=""
                 parentClasses="public AudioProcessorEditor, public ChangeListener"
                 constructorParams="AudioProcessor *const ownerFilter" variableInitialisers="AudioProcessorEditor(ownerFilter)"
                 snapPixels="8" snapActive="1" snapShown="0" overlayOpacity="0.330000013"
                 fixedSize="0" initialWidth="400" initialHeight="438">
  <BACKGROUND backgroundColour="ff000000"/>
  <GROUPCOMPONENT name="new group" id="e5e178cd242b6420" memberName="groupComponent2"
                  virtualName="" explicitFocusOrder="1" pos="8 8 384 104" outlinecol="66ffffff"
                  textcol="ffffffff" title="Oscillators" textpos="33"/>
  <GROUPCOMPONENT name="new group" id="ad99a16746beb177" memberName="groupComponent"
                  virtualName="" explicitFocusOrder="1" pos="8 344 384 80" outlinecol="66ffffff"
                  textcol="ffffffff" title="Output" textpos="33"/>
  <LABEL name="new label" id="49509c28b7b7d12d" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="16 368 56 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Gain" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
  <LABEL name="new label" id="155d710d9c4a7bd0" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="16 392 56 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Clip" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
  <SLIDER name="new slider" id="8a7b903812862b6c" memberName="slgain" virtualName=""
          explicitFocusOrder="0" pos="80 368 304 16" bkgcol="868686" textboxtext="ffffffff"
          textboxbkgd="565656" textboxhighlight="409a9aff" textboxoutline="0"
          min="0" max="4" int="0.0001" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="60" textBoxHeight="20" skewFactor="0.3"/>
  <SLIDER name="new slider" id="5f153060103ce45b" memberName="slclip" virtualName=""
          explicitFocusOrder="0" pos="80 392 304 16" bkgcol="868686" textboxtext="ffffffff"
          textboxbkgd="565656" textboxhighlight="409a9aff" textboxoutline="0"
          min="0" max="5" int="0.0001" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="60" textBoxHeight="20" skewFactor="0.5"/>
  <SLIDER name="new slider" id="9ed6f0186f5ff937" memberName="slsaw" virtualName=""
          explicitFocusOrder="0" pos="56 32 56 48" thumbcol="ffbbf2ff"
          rotarysliderfill="7f00b9ff" rotaryslideroutline="80ffffff" min="0"
          max="1" int="0" style="Rotary" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="eb3d9855455c7a5c" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="56 80 56 16" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="Saw" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="f984b6ce867a512c" memberName="slrect" virtualName=""
          explicitFocusOrder="0" pos="136 32 56 48" thumbcol="ffbbf2ff"
          rotarysliderfill="7f00b9ff" rotaryslideroutline="80ffffff" min="0"
          max="1" int="0" style="Rotary" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="4df8bd0f758110b0" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="136 80 56 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Rect" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="787a4f0997781dd1" memberName="sltri" virtualName=""
          explicitFocusOrder="0" pos="216 32 56 48" thumbcol="ffbbf2ff"
          rotarysliderfill="7f00b9ff" rotaryslideroutline="80ffffff" min="0"
          max="1" int="0" style="Rotary" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="881dba415f31e105" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="216 80 56 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Tri" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="34b4e27fcd2e1063" memberName="sltune" virtualName=""
          explicitFocusOrder="0" pos="320 32 56 48" thumbcol="ffbbf2ff"
          rotarysliderfill="7f00b9ff" rotaryslideroutline="80ffffff" min="0"
          max="1" int="0" style="Rotary" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="2466156e2db40baf" memberName="label6" virtualName=""
         explicitFocusOrder="0" pos="320 80 56 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Tune" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <GROUPCOMPONENT name="new group" id="7ce402f8c62d5932" memberName="groupComponent3"
                  virtualName="" explicitFocusOrder="1" pos="8 128 384 200" outlinecol="66ffffff"
                  textcol="ffffffff" title="Filter" textpos="33"/>
  <LABEL name="new label" id="e57e597377fef365" memberName="label7" virtualName=""
         explicitFocusOrder="0" pos="16 152 64 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Filter X" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
  <SLIDER name="new slider" id="df34f7f508b7adb0" memberName="slcutoff"
          virtualName="" explicitFocusOrder="0" pos="80 152 304 16" bkgcol="868686"
          textboxtext="ffffffff" textboxbkgd="565656" textboxhighlight="409a9aff"
          textboxoutline="0" min="0" max="4" int="0.0001" style="LinearHorizontal"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="60"
          textBoxHeight="20" skewFactor="0.5"/>
  <LABEL name="new label" id="e2f509e8c9131813" memberName="label8" virtualName=""
         explicitFocusOrder="0" pos="16 176 64 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Resonance" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
  <SLIDER name="new slider" id="35786a165f16578e" memberName="slreso" virtualName=""
          explicitFocusOrder="0" pos="80 176 304 16" bkgcol="868686" textboxtext="ffffffff"
          textboxbkgd="565656" textboxhighlight="409a9aff" textboxoutline="0"
          min="0" max="4" int="0.0001" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="60" textBoxHeight="20" skewFactor="0.5"/>
  <LABEL name="new label" id="cefa7252c084bf3a" memberName="label9" virtualName=""
         explicitFocusOrder="0" pos="16 200 64 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Bandwidth" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
  <SLIDER name="new slider" id="5362f75ced0b9ac9" memberName="slbandwidth"
          virtualName="" explicitFocusOrder="0" pos="80 200 304 16" bkgcol="868686"
          textboxtext="ffffffff" textboxbkgd="565656" textboxhighlight="409a9aff"
          textboxoutline="0" min="0" max="4" int="0.0001" style="LinearHorizontal"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="60"
          textBoxHeight="20" skewFactor="0.5"/>
  <LABEL name="new label" id="adcc1d907bb16758" memberName="label10" virtualName=""
         explicitFocusOrder="0" pos="16 224 64 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Passes" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
  <SLIDER name="new slider" id="29e98c8c7765790" memberName="slpasses"
          virtualName="" explicitFocusOrder="0" pos="80 224 304 16" bkgcol="868686"
          textboxtext="ffffffff" textboxbkgd="565656" textboxhighlight="409a9aff"
          textboxoutline="0" min="0" max="4" int="0.0001" style="LinearHorizontal"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="60"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="eae3af57dfc37cd5" memberName="label11" virtualName=""
         explicitFocusOrder="0" pos="16 248 64 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Velocity" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
  <SLIDER name="new slider" id="f1f951fe4565a7db" memberName="slvelocity"
          virtualName="" explicitFocusOrder="0" pos="80 248 304 16" bkgcol="868686"
          textboxtext="ffffffff" textboxbkgd="565656" textboxhighlight="409a9aff"
          textboxoutline="0" min="0" max="4" int="0.0001" style="LinearHorizontal"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="60"
          textBoxHeight="20" skewFactor="0.5"/>
  <LABEL name="new label" id="145c7f21c5783bd3" memberName="label12" virtualName=""
         explicitFocusOrder="0" pos="16 272 64 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Inertia" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
  <SLIDER name="new slider" id="1f326d02c58973a" memberName="slinertia"
          virtualName="" explicitFocusOrder="0" pos="80 272 304 16" bkgcol="868686"
          textboxtext="ffffffff" textboxbkgd="565656" textboxhighlight="409a9aff"
          textboxoutline="0" min="0" max="4" int="0.0001" style="LinearHorizontal"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="60"
          textBoxHeight="20" skewFactor="0.5"/>
  <LABEL name="new label" id="77aa4e9b34a8fa81" memberName="label13" virtualName=""
         explicitFocusOrder="0" pos="16 296 64 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Filter Freq" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
  <SLIDER name="new slider" id="88030f6cab98eb34" memberName="slcurcutoff"
          virtualName="" explicitFocusOrder="0" pos="80 296 304 16" bkgcol="868686"
          textboxtext="ffffffff" textboxbkgd="565656" textboxhighlight="409a9aff"
          textboxoutline="0" min="0" max="4" int="0.0001" style="LinearHorizontal"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="60"
          textBoxHeight="20" skewFactor="0.4"/>
  <LABEL name="new label" id="bf2b92c62f94cc75" memberName="label14" virtualName=""
         explicitFocusOrder="0" pos="16 0Cc 32 16" posRelativeY="9ed6f0186f5ff937"
         textCol="ffffffff" edTextCol="ff000000" edBkgCol="0" labelText="Mix"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="34"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
