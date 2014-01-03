/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  18 Jan 2010 2:17:20 pm

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
#include "MidiFilterPlugin.h"
//[/Headers]

#include "MidiFilterEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MidiFilterEditor::MidiFilterEditor (MidiFilterPlugin* owner_)
    : PluginEditorComponent (owner_),
      owner (owner_),
      channelLabel (0),
      channelButton1 (0),
      channelButton2 (0),
      channelButton3 (0),
      channelButton4 (0),
      channelButton5 (0),
      channelButton6 (0),
      channelButton7 (0),
      channelButton8 (0),
      channelButton9 (0),
      channelButton10 (0),
      channelButton11 (0),
      channelButton12 (0),
      channelButton13 (0),
      channelButton14 (0),
      channelButton15 (0),
      channelButton16 (0),
      channelToggle (0),
      noteToggle (0),
      noteLabel (0),
      velocityToggle (0),
      velocityLabel (0),
      noteSlider (0),
      channelToggleButton (0),
      velocitySlider (0)
{
    addAndMakeVisible (channelLabel = new Label (String::empty,
                                                 T("Channels")));
    channelLabel->setFont (Font (15.0000f, Font::plain));
    channelLabel->setJustificationType (Justification::centredLeft);
    channelLabel->setEditable (false, false, false);
    channelLabel->setColour (Label::textColourId, Colours::white);
    channelLabel->setColour (TextEditor::textColourId, Colours::black);
    channelLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (channelButton1 = new ParameterLedButton (String::empty));
    channelButton1->setButtonText (T("01"));
    channelButton1->setConnectedEdges (Button::ConnectedOnRight);
    channelButton1->addButtonListener (this);

    addAndMakeVisible (channelButton2 = new ParameterLedButton (String::empty));
    channelButton2->setButtonText (T("02"));
    channelButton2->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    channelButton2->addButtonListener (this);

    addAndMakeVisible (channelButton3 = new ParameterLedButton (String::empty));
    channelButton3->setButtonText (T("03"));
    channelButton3->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    channelButton3->addButtonListener (this);

    addAndMakeVisible (channelButton4 = new ParameterLedButton (String::empty));
    channelButton4->setButtonText (T("04"));
    channelButton4->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    channelButton4->addButtonListener (this);

    addAndMakeVisible (channelButton5 = new ParameterLedButton (String::empty));
    channelButton5->setButtonText (T("05"));
    channelButton5->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    channelButton5->addButtonListener (this);

    addAndMakeVisible (channelButton6 = new ParameterLedButton (String::empty));
    channelButton6->setButtonText (T("06"));
    channelButton6->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    channelButton6->addButtonListener (this);

    addAndMakeVisible (channelButton7 = new ParameterLedButton (String::empty));
    channelButton7->setButtonText (T("07"));
    channelButton7->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    channelButton7->addButtonListener (this);

    addAndMakeVisible (channelButton8 = new ParameterLedButton (String::empty));
    channelButton8->setButtonText (T("08"));
    channelButton8->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    channelButton8->addButtonListener (this);

    addAndMakeVisible (channelButton9 = new ParameterLedButton (String::empty));
    channelButton9->setButtonText (T("09"));
    channelButton9->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    channelButton9->addButtonListener (this);

    addAndMakeVisible (channelButton10 = new ParameterLedButton (String::empty));
    channelButton10->setButtonText (T("10"));
    channelButton10->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    channelButton10->addButtonListener (this);

    addAndMakeVisible (channelButton11 = new ParameterLedButton (String::empty));
    channelButton11->setButtonText (T("11"));
    channelButton11->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    channelButton11->addButtonListener (this);

    addAndMakeVisible (channelButton12 = new ParameterLedButton (String::empty));
    channelButton12->setButtonText (T("12"));
    channelButton12->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    channelButton12->addButtonListener (this);

    addAndMakeVisible (channelButton13 = new ParameterLedButton (String::empty));
    channelButton13->setButtonText (T("13"));
    channelButton13->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    channelButton13->addButtonListener (this);

    addAndMakeVisible (channelButton14 = new ParameterLedButton (String::empty));
    channelButton14->setButtonText (T("14"));
    channelButton14->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    channelButton14->addButtonListener (this);

    addAndMakeVisible (channelButton15 = new ParameterLedButton (String::empty));
    channelButton15->setButtonText (T("15"));
    channelButton15->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    channelButton15->addButtonListener (this);

    addAndMakeVisible (channelButton16 = new ParameterLedButton (String::empty));
    channelButton16->setButtonText (T("16"));
    channelButton16->setConnectedEdges (Button::ConnectedOnLeft);
    channelButton16->addButtonListener (this);

    addAndMakeVisible (channelToggle = new ToggleButton (String::empty));
    channelToggle->addButtonListener (this);
    channelToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (noteToggle = new ToggleButton (String::empty));
    noteToggle->addButtonListener (this);
    noteToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (noteLabel = new Label (String::empty,
                                              T("Notes")));
    noteLabel->setFont (Font (15.0000f, Font::plain));
    noteLabel->setJustificationType (Justification::centredLeft);
    noteLabel->setEditable (false, false, false);
    noteLabel->setColour (Label::textColourId, Colours::white);
    noteLabel->setColour (TextEditor::textColourId, Colours::black);
    noteLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (velocityToggle = new ToggleButton (String::empty));
    velocityToggle->addButtonListener (this);
    velocityToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (velocityLabel = new Label (String::empty,
                                                  T("Velocity")));
    velocityLabel->setFont (Font (15.0000f, Font::plain));
    velocityLabel->setJustificationType (Justification::centredLeft);
    velocityLabel->setEditable (false, false, false);
    velocityLabel->setColour (Label::textColourId, Colours::white);
    velocityLabel->setColour (TextEditor::textColourId, Colours::black);
    velocityLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (noteSlider = new Slider (String::empty));
    noteSlider->setRange (0, 127, 1);
    noteSlider->setSliderStyle (Slider::TwoValueHorizontal);
    noteSlider->setTextBoxStyle (Slider::NoTextBox, false, 46, 16);
    noteSlider->addListener (this);

    addAndMakeVisible (channelToggleButton = new TextButton (String::empty));
    channelToggleButton->setButtonText (T("Deselect"));
    channelToggleButton->addButtonListener (this);
    channelToggleButton->setColour (TextButton::buttonColourId, Colour (0xff8a9bee));
    channelToggleButton->setColour (TextButton::textColourOnId, Colours::black);

    addAndMakeVisible (velocitySlider = new Slider (String::empty));
    velocitySlider->setRange (0, 127, 1);
    velocitySlider->setSliderStyle (Slider::TwoValueHorizontal);
    velocitySlider->setTextBoxStyle (Slider::NoTextBox, false, 46, 16);
    velocitySlider->addListener (this);


    //[UserPreSize]
    channelButton1->setOnOffColours (Colours::grey, Colours::lightblue);
    channelButton2->setOnOffColours (Colours::grey, Colours::lightblue);
    channelButton3->setOnOffColours (Colours::grey, Colours::lightblue);
    channelButton4->setOnOffColours (Colours::grey, Colours::lightblue);
    channelButton5->setOnOffColours (Colours::grey, Colours::lightblue);
    channelButton6->setOnOffColours (Colours::grey, Colours::lightblue);
    channelButton7->setOnOffColours (Colours::grey, Colours::lightblue);
    channelButton8->setOnOffColours (Colours::grey, Colours::lightblue);
    channelButton9->setOnOffColours (Colours::grey, Colours::lightblue);
    channelButton10->setOnOffColours (Colours::grey, Colours::lightblue);
    channelButton11->setOnOffColours (Colours::grey, Colours::lightblue);
    channelButton12->setOnOffColours (Colours::grey, Colours::lightblue);
    channelButton13->setOnOffColours (Colours::grey, Colours::lightblue);
    channelButton14->setOnOffColours (Colours::grey, Colours::lightblue);
    channelButton15->setOnOffColours (Colours::grey, Colours::lightblue);
    channelButton16->setOnOffColours (Colours::grey, Colours::lightblue);

    noteSlider->setPopupDisplayEnabled (true, this);
    noteSlider->setPopupMenuEnabled (false);

    velocitySlider->setPopupDisplayEnabled (true, this);
    velocitySlider->setPopupMenuEnabled (false);

    //[/UserPreSize]

    setSize (696, 200);

    //[Constructor] You can add your own custom stuff here..
    updateParameters ();
    //[/Constructor]
}

MidiFilterEditor::~MidiFilterEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (channelLabel);
    deleteAndZero (channelButton1);
    deleteAndZero (channelButton2);
    deleteAndZero (channelButton3);
    deleteAndZero (channelButton4);
    deleteAndZero (channelButton5);
    deleteAndZero (channelButton6);
    deleteAndZero (channelButton7);
    deleteAndZero (channelButton8);
    deleteAndZero (channelButton9);
    deleteAndZero (channelButton10);
    deleteAndZero (channelButton11);
    deleteAndZero (channelButton12);
    deleteAndZero (channelButton13);
    deleteAndZero (channelButton14);
    deleteAndZero (channelButton15);
    deleteAndZero (channelButton16);
    deleteAndZero (channelToggle);
    deleteAndZero (noteToggle);
    deleteAndZero (noteLabel);
    deleteAndZero (velocityToggle);
    deleteAndZero (velocityLabel);
    deleteAndZero (noteSlider);
    deleteAndZero (channelToggleButton);
    deleteAndZero (velocitySlider);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MidiFilterEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff8796af));

    g.setColour (Colour (0x7dc0c0c0));
    g.fillRoundedRectangle (4.0f, 4.0f, 688.0f, 26.0f, 5.0000f);

    g.setColour (Colour (0x7dc0c0c0));
    g.fillRoundedRectangle (4.0f, 34.0f, 688.0f, 26.0f, 5.0000f);

    g.setColour (Colour (0x7dc0c0c0));
    g.fillRoundedRectangle (4.0f, 64.0f, 688.0f, 26.0f, 5.0000f);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MidiFilterEditor::resized()
{
    channelLabel->setBounds (30, 9, 64, 16);
    channelButton1->setBounds (242, 9, 24, 16);
    channelButton2->setBounds (266, 9, 24, 16);
    channelButton3->setBounds (290, 9, 24, 16);
    channelButton4->setBounds (314, 9, 24, 16);
    channelButton5->setBounds (338, 9, 24, 16);
    channelButton6->setBounds (362, 9, 24, 16);
    channelButton7->setBounds (386, 9, 24, 16);
    channelButton8->setBounds (410, 9, 24, 16);
    channelButton9->setBounds (434, 9, 24, 16);
    channelButton10->setBounds (458, 9, 24, 16);
    channelButton11->setBounds (482, 9, 24, 16);
    channelButton12->setBounds (506, 9, 24, 16);
    channelButton13->setBounds (530, 9, 24, 16);
    channelButton14->setBounds (554, 9, 24, 16);
    channelButton15->setBounds (578, 9, 24, 16);
    channelButton16->setBounds (602, 9, 24, 16);
    channelToggle->setBounds (8, 5, 22, 22);
    noteToggle->setBounds (8, 36, 22, 22);
    noteLabel->setBounds (30, 39, 64, 16);
    velocityToggle->setBounds (8, 66, 22, 22);
    velocityLabel->setBounds (30, 69, 64, 16);
    noteSlider->setBounds (239, 37, 438, 20);
    channelToggleButton->setBounds (632, 9, 46, 16);
    velocitySlider->setBounds (239, 67, 438, 20);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MidiFilterEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    MidiFilter* filter = owner->getMidiFilter ();
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == channelButton1)
    {
        //[UserButtonCode_channelButton1] -- add your button handler code here..
        channelButtonClicked (channelButton1, 1);
        //[/UserButtonCode_channelButton1]
    }
    else if (buttonThatWasClicked == channelButton2)
    {
        //[UserButtonCode_channelButton2] -- add your button handler code here..
        channelButtonClicked (channelButton2, 2);
        //[/UserButtonCode_channelButton2]
    }
    else if (buttonThatWasClicked == channelButton3)
    {
        //[UserButtonCode_channelButton3] -- add your button handler code here..
        channelButtonClicked (channelButton3, 3);
        //[/UserButtonCode_channelButton3]
    }
    else if (buttonThatWasClicked == channelButton4)
    {
        //[UserButtonCode_channelButton4] -- add your button handler code here..
        channelButtonClicked (channelButton4, 4);
        //[/UserButtonCode_channelButton4]
    }
    else if (buttonThatWasClicked == channelButton5)
    {
        //[UserButtonCode_channelButton5] -- add your button handler code here..
        channelButtonClicked (channelButton5, 5);
        //[/UserButtonCode_channelButton5]
    }
    else if (buttonThatWasClicked == channelButton6)
    {
        //[UserButtonCode_channelButton6] -- add your button handler code here..
        channelButtonClicked (channelButton6, 6);
        //[/UserButtonCode_channelButton6]
    }
    else if (buttonThatWasClicked == channelButton7)
    {
        //[UserButtonCode_channelButton7] -- add your button handler code here..
        channelButtonClicked (channelButton7, 7);
        //[/UserButtonCode_channelButton7]
    }
    else if (buttonThatWasClicked == channelButton8)
    {
        //[UserButtonCode_channelButton8] -- add your button handler code here..
        channelButtonClicked (channelButton8, 8);
        //[/UserButtonCode_channelButton8]
    }
    else if (buttonThatWasClicked == channelButton9)
    {
        //[UserButtonCode_channelButton9] -- add your button handler code here..
        channelButtonClicked (channelButton9, 9);
        //[/UserButtonCode_channelButton9]
    }
    else if (buttonThatWasClicked == channelButton10)
    {
        //[UserButtonCode_channelButton10] -- add your button handler code here..
        channelButtonClicked (channelButton10, 10);
        //[/UserButtonCode_channelButton10]
    }
    else if (buttonThatWasClicked == channelButton11)
    {
        //[UserButtonCode_channelButton11] -- add your button handler code here..
        channelButtonClicked (channelButton11, 11);
        //[/UserButtonCode_channelButton11]
    }
    else if (buttonThatWasClicked == channelButton12)
    {
        //[UserButtonCode_channelButton12] -- add your button handler code here..
        channelButtonClicked (channelButton12, 12);
        //[/UserButtonCode_channelButton12]
    }
    else if (buttonThatWasClicked == channelButton13)
    {
        //[UserButtonCode_channelButton13] -- add your button handler code here..
        channelButtonClicked (channelButton13, 13);
        //[/UserButtonCode_channelButton13]
    }
    else if (buttonThatWasClicked == channelButton14)
    {
        //[UserButtonCode_channelButton14] -- add your button handler code here..
        channelButtonClicked (channelButton14, 14);
        //[/UserButtonCode_channelButton14]
    }
    else if (buttonThatWasClicked == channelButton15)
    {
        //[UserButtonCode_channelButton15] -- add your button handler code here..
        channelButtonClicked (channelButton15, 15);
        //[/UserButtonCode_channelButton15]
    }
    else if (buttonThatWasClicked == channelButton16)
    {
        //[UserButtonCode_channelButton16] -- add your button handler code here..
        channelButtonClicked (channelButton16, 16);
        //[/UserButtonCode_channelButton16]
    }
    else if (buttonThatWasClicked == channelToggle)
    {
        //[UserButtonCode_channelToggle] -- add your button handler code here..
        const bool channelEnabled = buttonThatWasClicked->getToggleState ();

        filter->setUseChannelFilter (channelEnabled);

        channelButton1->setEnabled (channelEnabled);
        channelButton2->setEnabled (channelEnabled);
        channelButton3->setEnabled (channelEnabled);
        channelButton4->setEnabled (channelEnabled);
        channelButton5->setEnabled (channelEnabled);
        channelButton6->setEnabled (channelEnabled);
        channelButton7->setEnabled (channelEnabled);
        channelButton8->setEnabled (channelEnabled);
        channelButton9->setEnabled (channelEnabled);
        channelButton10->setEnabled (channelEnabled);
        channelButton11->setEnabled (channelEnabled);
        channelButton12->setEnabled (channelEnabled);
        channelButton13->setEnabled (channelEnabled);
        channelButton14->setEnabled (channelEnabled);
        channelButton15->setEnabled (channelEnabled);
        channelButton16->setEnabled (channelEnabled);

        channelToggleButton->setEnabled (channelEnabled);
        //[/UserButtonCode_channelToggle]
    }
    else if (buttonThatWasClicked == noteToggle)
    {
        //[UserButtonCode_noteToggle] -- add your button handler code here..
        filter->setUseNoteFilter (buttonThatWasClicked->getToggleState ());

        noteSlider->setEnabled (buttonThatWasClicked->getToggleState ());
        //[/UserButtonCode_noteToggle]
    }
    else if (buttonThatWasClicked == velocityToggle)
    {
        //[UserButtonCode_velocityToggle] -- add your button handler code here..
        filter->setUseVelocityFilter (buttonThatWasClicked->getToggleState ());

        velocitySlider->setEnabled (buttonThatWasClicked->getToggleState ());
        //[/UserButtonCode_velocityToggle]
    }
    else if (buttonThatWasClicked == channelToggleButton)
    {
        //[UserButtonCode_channelToggleButton] -- add your button handler code here..
        //[/UserButtonCode_channelToggleButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void MidiFilterEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    MidiFilter* filter = owner->getMidiFilter ();
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == noteSlider)
    {
        //[UserSliderCode_noteSlider] -- add your slider handling code here..
        filter->setNoteMin ((int) noteSlider->getMinValue ());
        filter->setNoteMax ((int) noteSlider->getMaxValue ());
        //[/UserSliderCode_noteSlider]
    }
    else if (sliderThatWasMoved == velocitySlider)
    {
        //[UserSliderCode_velocitySlider] -- add your slider handling code here..
        filter->setVelocityMin ((int) velocitySlider->getMinValue ());
        filter->setVelocityMax ((int) velocitySlider->getMaxValue ());
        //[/UserSliderCode_velocitySlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void MidiFilterEditor::updateParameters ()
{
    MidiFilter* filter = owner->getMidiFilter ();

    const bool channelEnabled = filter->isUsingChannelFilter ();
    const bool noteEnabled = filter->isUsingNoteFilter ();
    const bool velocityEnabled = filter->isUsingVelocityFilter ();

    channelButton1->setActivated (filter->isChannelSet (1));
    channelButton2->setActivated (filter->isChannelSet (2));
    channelButton3->setActivated (filter->isChannelSet (3));
    channelButton4->setActivated (filter->isChannelSet (4));
    channelButton5->setActivated (filter->isChannelSet (5));
    channelButton6->setActivated (filter->isChannelSet (6));
    channelButton7->setActivated (filter->isChannelSet (7));
    channelButton8->setActivated (filter->isChannelSet (8));
    channelButton9->setActivated (filter->isChannelSet (9));
    channelButton10->setActivated (filter->isChannelSet (10));
    channelButton11->setActivated (filter->isChannelSet (11));
    channelButton12->setActivated (filter->isChannelSet (12));
    channelButton13->setActivated (filter->isChannelSet (13));
    channelButton14->setActivated (filter->isChannelSet (14));
    channelButton15->setActivated (filter->isChannelSet (15));
    channelButton16->setActivated (filter->isChannelSet (16));

    channelButton1->setEnabled (channelEnabled);
    channelButton2->setEnabled (channelEnabled);
    channelButton3->setEnabled (channelEnabled);
    channelButton4->setEnabled (channelEnabled);
    channelButton5->setEnabled (channelEnabled);
    channelButton6->setEnabled (channelEnabled);
    channelButton7->setEnabled (channelEnabled);
    channelButton8->setEnabled (channelEnabled);
    channelButton9->setEnabled (channelEnabled);
    channelButton10->setEnabled (channelEnabled);
    channelButton11->setEnabled (channelEnabled);
    channelButton12->setEnabled (channelEnabled);
    channelButton13->setEnabled (channelEnabled);
    channelButton14->setEnabled (channelEnabled);
    channelButton15->setEnabled (channelEnabled);
    channelButton16->setEnabled (channelEnabled);

    channelToggleButton->setEnabled (channelEnabled);
    noteSlider->setEnabled (noteEnabled);
    velocitySlider->setEnabled (velocityEnabled);

    channelToggle->setToggleState (channelEnabled, true);
    noteToggle->setToggleState (noteEnabled, true);
    velocityToggle->setToggleState (velocityEnabled, true);
}

void MidiFilterEditor::channelButtonClicked (ParameterLedButton* button, const int channel)
{
    button->toggleActivated ();

    MidiFilter* filter = owner->getMidiFilter ();
    if (button->isActivated ())
        filter->setChannel (channel);
    else
        filter->unsetChannel (channel);
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MidiFilterEditor" componentName=""
                 parentClasses="public PluginEditorComponent" constructorParams="MidiFilterPlugin* owner_"
                 variableInitialisers="PluginEditorComponent (owner_)&#10;owner (owner_)"
                 snapPixels="8" snapActive="0" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="1" initialWidth="696" initialHeight="200">
  <BACKGROUND backgroundColour="ff8796af">
    <ROUNDRECT pos="4 4 688 26" cornerSize="5" fill="solid: 7dc0c0c0" hasStroke="0"/>
    <ROUNDRECT pos="4 34 688 26" cornerSize="5" fill="solid: 7dc0c0c0" hasStroke="0"/>
    <ROUNDRECT pos="4 64 688 26" cornerSize="5" fill="solid: 7dc0c0c0" hasStroke="0"/>
  </BACKGROUND>
  <LABEL name="" id="7c6308ff71bbc6df" memberName="channelLabel" virtualName=""
         explicitFocusOrder="0" pos="30 9 64 16" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="Channels" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="" id="337f092154990c3e" memberName="channelButton1" virtualName="ParameterLedButton"
              explicitFocusOrder="0" pos="242 9 24 16" buttonText="01" connectedEdges="2"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="477fc8e0b482870" memberName="channelButton2" virtualName="ParameterLedButton"
              explicitFocusOrder="0" pos="266 9 24 16" buttonText="02" connectedEdges="3"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="f084f005f80c12f0" memberName="channelButton3" virtualName="ParameterLedButton"
              explicitFocusOrder="0" pos="290 9 24 16" buttonText="03" connectedEdges="3"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="aeaf999c3d670498" memberName="channelButton4" virtualName="ParameterLedButton"
              explicitFocusOrder="0" pos="314 9 24 16" buttonText="04" connectedEdges="3"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="eff7a34c4402f7a1" memberName="channelButton5" virtualName="ParameterLedButton"
              explicitFocusOrder="0" pos="338 9 24 16" buttonText="05" connectedEdges="3"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="41a0a9295b9b775b" memberName="channelButton6" virtualName="ParameterLedButton"
              explicitFocusOrder="0" pos="362 9 24 16" buttonText="06" connectedEdges="3"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="fb877d795326f98" memberName="channelButton7" virtualName="ParameterLedButton"
              explicitFocusOrder="0" pos="386 9 24 16" buttonText="07" connectedEdges="3"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="491e3e3dfab80e4b" memberName="channelButton8" virtualName="ParameterLedButton"
              explicitFocusOrder="0" pos="410 9 24 16" buttonText="08" connectedEdges="3"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="265ea678921c9b6b" memberName="channelButton9" virtualName="ParameterLedButton"
              explicitFocusOrder="0" pos="434 9 24 16" buttonText="09" connectedEdges="3"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="c1840a1347cd6b1d" memberName="channelButton10" virtualName="ParameterLedButton"
              explicitFocusOrder="0" pos="458 9 24 16" buttonText="10" connectedEdges="3"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="93393574390c4e11" memberName="channelButton11" virtualName="ParameterLedButton"
              explicitFocusOrder="0" pos="482 9 24 16" buttonText="11" connectedEdges="3"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="2c906e98e3a3242b" memberName="channelButton12" virtualName="ParameterLedButton"
              explicitFocusOrder="0" pos="506 9 24 16" buttonText="12" connectedEdges="3"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="3ba7b302646b7566" memberName="channelButton13" virtualName="ParameterLedButton"
              explicitFocusOrder="0" pos="530 9 24 16" buttonText="13" connectedEdges="3"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="df7e60f0333c34f5" memberName="channelButton14" virtualName="ParameterLedButton"
              explicitFocusOrder="0" pos="554 9 24 16" buttonText="14" connectedEdges="3"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="c3dfbfd01f4e12aa" memberName="channelButton15" virtualName="ParameterLedButton"
              explicitFocusOrder="0" pos="578 9 24 16" buttonText="15" connectedEdges="3"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="64891bf2c548fe9b" memberName="channelButton16" virtualName="ParameterLedButton"
              explicitFocusOrder="0" pos="602 9 24 16" buttonText="16" connectedEdges="1"
              needsCallback="1" radioGroupId="0"/>
  <TOGGLEBUTTON name="" id="8732d57d243676f3" memberName="channelToggle" virtualName=""
                explicitFocusOrder="0" pos="8 5 22 22" txtcol="ffffffff" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="" id="323a92490d22a3a" memberName="noteToggle" virtualName=""
                explicitFocusOrder="0" pos="8 36 22 22" txtcol="ffffffff" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="" id="d6867ca9a1d23209" memberName="noteLabel" virtualName=""
         explicitFocusOrder="0" pos="30 39 64 16" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="Notes" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="" id="69c37b4f2d61670b" memberName="velocityToggle" virtualName=""
                explicitFocusOrder="0" pos="8 66 22 22" txtcol="ffffffff" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="" id="47e2146a1af7bcdc" memberName="velocityLabel" virtualName=""
         explicitFocusOrder="0" pos="30 69 64 16" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="Velocity" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <SLIDER name="" id="1cad9ffcda32e0ee" memberName="noteSlider" virtualName=""
          explicitFocusOrder="0" pos="239 37 438 20" min="0" max="127"
          int="1" style="TwoValueHorizontal" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="46" textBoxHeight="16" skewFactor="1"/>
  <TEXTBUTTON name="" id="f478bbdc4ec433c0" memberName="channelToggleButton"
              virtualName="" explicitFocusOrder="0" pos="632 9 46 16" bgColOff="ff8a9bee"
              textCol="ff000000" buttonText="Deselect" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <SLIDER name="" id="6f07b837979c6c75" memberName="velocitySlider" virtualName=""
          explicitFocusOrder="0" pos="239 67 438 20" min="0" max="127"
          int="1" style="TwoValueHorizontal" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="46" textBoxHeight="16" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
