/***************************************************************************
 *   Copyright (C) 2009 by Christian Borss                                 *
 *   christian.borss@rub.de                                                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


//[Headers] You can add your own extra header files here...
#include "../MasterAndCommander.h"
#include "../PresetManager.h"
#include "IRPlot.h"
#include <iostream>
//[/Headers]

#include "TabMain.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
TabMain::TabMain (MasterAndCommander *m)
    : master (m),
      groupComponentNotes (0),
      groupComponentMainControl (0),
      labelPresetNum (0),
      groupComponentPresetSelector (0),
      labelPresetText (0),
      comboBox (0),
      comboBox2 (0),
      comboBox3 (0),
      comboBox4 (0),
      textEditorNotes (0),
      groupComponentIRPlot (0),
      sliderInitialGap (0),
      labelInitialGap (0),
      sliderLength (0),
      labelLength (0),
      sliderPreDelay (0),
      labelPreDelay (0),
      sliderDryGain (0),
      labelDryGain (0),
      sliderWetGain (0),
      sliderMasterGain (0),
      labelWetGain (0),
      labelMasterGain (0),
      sliderPresetIncDec (0),
      irPlot (0),
      slider0ms (0),
      slider20ms (0),
      slider120ms (0),
      sliderENDms (0)
{
    addAndMakeVisible (groupComponentNotes = new GroupComponent (T("new group"),
                                                                 T("Notes")));

    addAndMakeVisible (groupComponentMainControl = new GroupComponent (T("new group"),
                                                                       T("Main Controls")));

    addAndMakeVisible (labelPresetNum = new Label (T("new label"),
                                                   T("1")));
    labelPresetNum->setFont (Font (Font::getDefaultMonospacedFontName(), 32.0000f, Font::plain));
    labelPresetNum->setJustificationType (Justification::centred);
    labelPresetNum->setEditable (false, false, false);
    labelPresetNum->setColour (Label::backgroundColourId, Colours::white);
    labelPresetNum->setColour (Label::textColourId, Colours::black);
    labelPresetNum->setColour (Label::outlineColourId, Colour (0xffa6a6a6));
    labelPresetNum->setColour (TextEditor::textColourId, Colours::black);
    labelPresetNum->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (groupComponentPresetSelector = new GroupComponent (T("new group"),
                                                                          T("Preset Selector")));

    addAndMakeVisible (labelPresetText = new Label (T("new label"),
                                                    T("123456789012345678901234")));
    labelPresetText->setFont (Font (Font::getDefaultMonospacedFontName(), 20.0000f, Font::plain));
    labelPresetText->setJustificationType (Justification::centred);
    labelPresetText->setEditable (false, false, false);
    labelPresetText->setColour (Label::backgroundColourId, Colours::white);
    labelPresetText->setColour (Label::outlineColourId, Colour (0xffa6a6a6));
    labelPresetText->setColour (TextEditor::textColourId, Colours::black);
    labelPresetText->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (comboBox = new ComboBox (T("new combo box")));
    comboBox->setEditableText (false);
    comboBox->setJustificationType (Justification::centredLeft);
    comboBox->setTextWhenNothingSelected (String::empty);
    comboBox->setTextWhenNoChoicesAvailable (T("---"));
    comboBox->addItem (T("channels: front"), 1);
    comboBox->addListener (this);

    addAndMakeVisible (comboBox2 = new ComboBox (T("new combo box")));
    comboBox2->setEditableText (false);
    comboBox2->setJustificationType (Justification::centredLeft);
    comboBox2->setTextWhenNothingSelected (String::empty);
    comboBox2->setTextWhenNoChoicesAvailable (T("---"));
    comboBox2->addItem (T("room: large concert hall"), 1);
    comboBox2->addListener (this);

    addAndMakeVisible (comboBox3 = new ComboBox (T("new combo box")));
    comboBox3->setEditableText (false);
    comboBox3->setJustificationType (Justification::centredLeft);
    comboBox3->setTextWhenNothingSelected (String::empty);
    comboBox3->setTextWhenNoChoicesAvailable (T("---"));
    comboBox3->addItem (T("purpose: music"), 1);
    comboBox3->addListener (this);

    addAndMakeVisible (comboBox4 = new ComboBox (T("new combo box")));
    comboBox4->setEditableText (false);
    comboBox4->setJustificationType (Justification::centredLeft);
    comboBox4->setTextWhenNothingSelected (String::empty);
    comboBox4->setTextWhenNoChoicesAvailable (T("---"));
    comboBox4->addItem (T("distance: 1m"), 1);
    comboBox4->addListener (this);

    addAndMakeVisible (textEditorNotes = new TextEditor (T("new text editor")));
    textEditorNotes->setMultiLine (true);
    textEditorNotes->setReturnKeyStartsNewLine (true);
    textEditorNotes->setReadOnly (true);
    textEditorNotes->setScrollbarsShown (true);
    textEditorNotes->setCaretVisible (true);
    textEditorNotes->setPopupMenuEnabled (true);
    textEditorNotes->setText (String::empty);

    addAndMakeVisible (groupComponentIRPlot = new GroupComponent (T("new group"),
                                                                  T("Impulse Response")));

    addAndMakeVisible (sliderInitialGap = new Slider (T("new slider")));
    sliderInitialGap->setRange (0, 100, 0.1);
    sliderInitialGap->setSliderStyle (Slider::Rotary);
    sliderInitialGap->setTextBoxStyle (Slider::TextBoxAbove, false, 72, 20);
    sliderInitialGap->setColour (Slider::rotarySliderFillColourId, Colour (0xff100040));
    sliderInitialGap->addListener (this);

    addAndMakeVisible (labelInitialGap = new Label (T("new label"),
                                                    T("Initial Gap")));
    labelInitialGap->setFont (Font (15.0000f, Font::plain));
    labelInitialGap->setJustificationType (Justification::centred);
    labelInitialGap->setEditable (false, false, false);
    labelInitialGap->setColour (TextEditor::textColourId, Colours::black);
    labelInitialGap->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (sliderLength = new Slider (T("new slider")));
    sliderLength->setRange (0, 1, 0.001);
    sliderLength->setSliderStyle (Slider::Rotary);
    sliderLength->setTextBoxStyle (Slider::TextBoxAbove, false, 72, 20);
    sliderLength->setColour (Slider::rotarySliderFillColourId, Colour (0xff100040));
    sliderLength->addListener (this);

    addAndMakeVisible (labelLength = new Label (T("new label"),
                                                T("Length")));
    labelLength->setFont (Font (15.0000f, Font::plain));
    labelLength->setJustificationType (Justification::centred);
    labelLength->setEditable (false, false, false);
    labelLength->setColour (TextEditor::textColourId, Colours::black);
    labelLength->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (sliderPreDelay = new Slider (T("new slider")));
    sliderPreDelay->setRange (-100, 100, 0.1);
    sliderPreDelay->setSliderStyle (Slider::Rotary);
    sliderPreDelay->setTextBoxStyle (Slider::TextBoxAbove, false, 72, 20);
    sliderPreDelay->setColour (Slider::rotarySliderFillColourId, Colour (0xff100040));
    sliderPreDelay->addListener (this);

    addAndMakeVisible (labelPreDelay = new Label (T("new label"),
                                                  T("Pre-Delay")));
    labelPreDelay->setFont (Font (15.0000f, Font::plain));
    labelPreDelay->setJustificationType (Justification::centred);
    labelPreDelay->setEditable (false, false, false);
    labelPreDelay->setColour (TextEditor::textColourId, Colours::black);
    labelPreDelay->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (sliderDryGain = new Slider (T("new slider")));
    sliderDryGain->setRange (-120, 0, 0.1);
    sliderDryGain->setSliderStyle (Slider::Rotary);
    sliderDryGain->setTextBoxStyle (Slider::TextBoxAbove, false, 72, 20);
    sliderDryGain->addListener (this);

    addAndMakeVisible (labelDryGain = new Label (T("new label"),
                                                 T("Dry Gain")));
    labelDryGain->setFont (Font (15.0000f, Font::plain));
    labelDryGain->setJustificationType (Justification::centred);
    labelDryGain->setEditable (false, false, false);
    labelDryGain->setColour (TextEditor::textColourId, Colours::black);
    labelDryGain->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (sliderWetGain = new Slider (T("new slider")));
    sliderWetGain->setRange (-40, 40, 0.1);
    sliderWetGain->setSliderStyle (Slider::Rotary);
    sliderWetGain->setTextBoxStyle (Slider::TextBoxAbove, false, 72, 20);
    sliderWetGain->addListener (this);

    addAndMakeVisible (sliderMasterGain = new Slider (T("new slider")));
    sliderMasterGain->setRange (-40, 40, 0.1);
    sliderMasterGain->setSliderStyle (Slider::Rotary);
    sliderMasterGain->setTextBoxStyle (Slider::TextBoxAbove, false, 72, 20);
    sliderMasterGain->addListener (this);

    addAndMakeVisible (labelWetGain = new Label (T("new label"),
                                                 T("Wet Gain")));
    labelWetGain->setFont (Font (15.0000f, Font::plain));
    labelWetGain->setJustificationType (Justification::centred);
    labelWetGain->setEditable (false, false, false);
    labelWetGain->setColour (TextEditor::textColourId, Colours::black);
    labelWetGain->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (labelMasterGain = new Label (T("new label"),
                                                    T("Master Gain")));
    labelMasterGain->setFont (Font (15.0000f, Font::plain));
    labelMasterGain->setJustificationType (Justification::centred);
    labelMasterGain->setEditable (false, false, false);
    labelMasterGain->setColour (TextEditor::textColourId, Colours::black);
    labelMasterGain->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (sliderPresetIncDec = new Slider (T("new slider")));
    sliderPresetIncDec->setRange (0, 257, 1);
    sliderPresetIncDec->setSliderStyle (Slider::IncDecButtons);
    sliderPresetIncDec->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sliderPresetIncDec->addListener (this);

    addAndMakeVisible (irPlot = new IRPlot (master));
    irPlot->setName (T("new component"));

    addAndMakeVisible (slider0ms = new Slider (T("new slider")));
    slider0ms->setRange (-80, 20, 0.1);
    slider0ms->setSliderStyle (Slider::LinearVertical);
    slider0ms->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 12);
    slider0ms->setColour (Slider::thumbColourId, Colour (0xffb00000));
    slider0ms->setColour (Slider::trackColourId, Colour (0x60a08080));
    slider0ms->setColour (Slider::rotarySliderFillColourId, Colour (0x7f800000));
    slider0ms->setColour (Slider::textBoxTextColourId, Colours::maroon);
    slider0ms->setColour (Slider::textBoxHighlightColourId, Colour (0x40ff0000));
    slider0ms->setColour (Slider::textBoxOutlineColourId, Colour (0x0));
    slider0ms->addListener (this);

    addAndMakeVisible (slider20ms = new Slider (T("new slider")));
    slider20ms->setRange (-80, 20, 0.1);
    slider20ms->setSliderStyle (Slider::LinearVertical);
    slider20ms->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 12);
    slider20ms->setColour (Slider::thumbColourId, Colour (0xffb00000));
    slider20ms->setColour (Slider::trackColourId, Colour (0x60a08080));
    slider20ms->setColour (Slider::rotarySliderFillColourId, Colour (0x7f800000));
    slider20ms->setColour (Slider::textBoxTextColourId, Colours::maroon);
    slider20ms->setColour (Slider::textBoxHighlightColourId, Colour (0x40ff0000));
    slider20ms->setColour (Slider::textBoxOutlineColourId, Colour (0x0));
    slider20ms->addListener (this);

    addAndMakeVisible (slider120ms = new Slider (T("new slider")));
    slider120ms->setRange (-80, 20, 0.1);
    slider120ms->setSliderStyle (Slider::LinearVertical);
    slider120ms->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 12);
    slider120ms->setColour (Slider::thumbColourId, Colour (0xffb00000));
    slider120ms->setColour (Slider::trackColourId, Colour (0x60a08080));
    slider120ms->setColour (Slider::rotarySliderFillColourId, Colour (0x7f800000));
    slider120ms->setColour (Slider::textBoxTextColourId, Colours::maroon);
    slider120ms->setColour (Slider::textBoxHighlightColourId, Colour (0x40ff0000));
    slider120ms->setColour (Slider::textBoxOutlineColourId, Colour (0x0));
    slider120ms->addListener (this);

    addAndMakeVisible (sliderENDms = new Slider (T("new slider")));
    sliderENDms->setRange (-80, 20, 0.1);
    sliderENDms->setSliderStyle (Slider::LinearVertical);
    sliderENDms->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 12);
    sliderENDms->setColour (Slider::thumbColourId, Colour (0xffb00000));
    sliderENDms->setColour (Slider::trackColourId, Colour (0x60a08080));
    sliderENDms->setColour (Slider::rotarySliderFillColourId, Colour (0x7f800000));
    sliderENDms->setColour (Slider::textBoxTextColourId, Colours::maroon);
    sliderENDms->setColour (Slider::textBoxHighlightColourId, Colour (0x40ff0000));
    sliderENDms->setColour (Slider::textBoxOutlineColourId, Colour (0x0));
    sliderENDms->addListener (this);


    //[UserPreSize]
    presetManager = 0;

    sliderInitialGap->setTextValueSuffix (T(" ms"));
    sliderInitialGap->setDoubleClickReturnValue (true, 0.0);

    sliderLength->setTextValueSuffix (T(" s"));
    sliderLength->setDoubleClickReturnValue (true, 1.0);

    sliderPreDelay->setTextValueSuffix (T(" ms"));
    sliderPreDelay->setDoubleClickReturnValue (true, 0.0);

    sliderDryGain->setTextValueSuffix (T(" dB"));
    sliderDryGain->setDoubleClickReturnValue (true, 0.0);

    sliderWetGain->setTextValueSuffix (T(" dB"));
    sliderWetGain->setDoubleClickReturnValue (true, 0.0);

    sliderMasterGain->setTextValueSuffix (T(" dB"));
    sliderMasterGain->setDoubleClickReturnValue (true, 0.0);

    slider0ms->setTextValueSuffix (T(" dB"));
    slider0ms->setDoubleClickReturnValue (true, 0.0);

    slider20ms->setTextValueSuffix (T(" dB"));
    slider20ms->setDoubleClickReturnValue (true, 0.0);

    slider120ms->setTextValueSuffix (T(" dB"));
    slider120ms->setDoubleClickReturnValue (true, 0.0);

    sliderENDms->setTextValueSuffix (T(" dB"));
    sliderENDms->setDoubleClickReturnValue (true, 0.0);

    sliderPresetIncDec->setValue(1, false);
    //[/UserPreSize]

    setSize (828, 548);

    //[Constructor] You can add your own custom stuff here..
//    master->print("TabMain::TabMain : Waiting for your commands, Sir!");
    master->registerTabMain(this);
    //[/Constructor]
}

TabMain::~TabMain()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (groupComponentNotes);
    deleteAndZero (groupComponentMainControl);
    deleteAndZero (labelPresetNum);
    deleteAndZero (groupComponentPresetSelector);
    deleteAndZero (labelPresetText);
    deleteAndZero (comboBox);
    deleteAndZero (comboBox2);
    deleteAndZero (comboBox3);
    deleteAndZero (comboBox4);
    deleteAndZero (textEditorNotes);
    deleteAndZero (groupComponentIRPlot);
    deleteAndZero (sliderInitialGap);
    deleteAndZero (labelInitialGap);
    deleteAndZero (sliderLength);
    deleteAndZero (labelLength);
    deleteAndZero (sliderPreDelay);
    deleteAndZero (labelPreDelay);
    deleteAndZero (sliderDryGain);
    deleteAndZero (labelDryGain);
    deleteAndZero (sliderWetGain);
    deleteAndZero (sliderMasterGain);
    deleteAndZero (labelWetGain);
    deleteAndZero (labelMasterGain);
    deleteAndZero (sliderPresetIncDec);
    deleteAndZero (irPlot);
    deleteAndZero (slider0ms);
    deleteAndZero (slider20ms);
    deleteAndZero (slider120ms);
    deleteAndZero (sliderENDms);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TabMain::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xffffe000));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TabMain::resized()
{
    groupComponentNotes->setBounds (336, 8, 480, 224);
    groupComponentMainControl->setBounds (8, 240, 320, 268);
    labelPresetNum->setBounds (16, 16, 64, 48);
    groupComponentPresetSelector->setBounds (8, 72, 320, 160);
    labelPresetText->setBounds (112, 16, 208, 48);
    comboBox->setBounds (24, 96, 288, 24);
    comboBox2->setBounds (24, 128, 288, 24);
    comboBox3->setBounds (24, 160, 288, 24);
    comboBox4->setBounds (24, 192, 288, 24);
    textEditorNotes->setBounds (352, 32, 448, 184);
    groupComponentIRPlot->setBounds (336, 240, 480, 268);
    sliderInitialGap->setBounds (32, 264, 64, 88);
    labelInitialGap->setBounds (24, 344, 80, 24);
    sliderLength->setBounds (136, 264, 64, 88);
    labelLength->setBounds (128, 344, 80, 24);
    sliderPreDelay->setBounds (240, 264, 64, 88);
    labelPreDelay->setBounds (232, 344, 80, 24);
    sliderDryGain->setBounds (32, 392, 64, 88);
    labelDryGain->setBounds (32, 472, 72, 24);
    sliderWetGain->setBounds (136, 392, 64, 88);
    sliderMasterGain->setBounds (240, 392, 64, 88);
    labelWetGain->setBounds (128, 472, 80, 24);
    labelMasterGain->setBounds (232, 472, 80, 24);
    sliderPresetIncDec->setBounds (88, 16, 18, 48);
    irPlot->setBounds (352, 264, 448, 228);
    slider0ms->setBounds (389, 276, 56, 178);
    slider20ms->setBounds (489, 276, 56, 178);
    slider120ms->setBounds (614, 276, 56, 178);
    sliderENDms->setBounds (739, 276, 56, 178);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void TabMain::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == comboBox)
    {
        //[UserComboBoxCode_comboBox] -- add your combo box handling code here..
        int index = comboBoxThatHasChanged->getSelectedItemIndex();
        int old_preset = sliderPresetIncDec->getValue();
        int new_preset = presetManager->getSimilarPreset(old_preset, 0, index);
        if (new_preset != old_preset)
        {
            sliderPresetIncDec->setValue(new_preset, true);
            labelPresetNum->setText(String(new_preset), false);
        }
        //[/UserComboBoxCode_comboBox]
    }
    else if (comboBoxThatHasChanged == comboBox2)
    {
        //[UserComboBoxCode_comboBox2] -- add your combo box handling code here..
        int index = comboBoxThatHasChanged->getSelectedItemIndex();
        int old_preset = sliderPresetIncDec->getValue();
        int new_preset = presetManager->getSimilarPreset(old_preset, 1, index);
        if (new_preset != old_preset)
        {
            sliderPresetIncDec->setValue(new_preset, true);
            labelPresetNum->setText(String(new_preset), false);
        }
        //[/UserComboBoxCode_comboBox2]
    }
    else if (comboBoxThatHasChanged == comboBox3)
    {
        //[UserComboBoxCode_comboBox3] -- add your combo box handling code here..
        int index = comboBoxThatHasChanged->getSelectedItemIndex();
        int old_preset = sliderPresetIncDec->getValue();
        int new_preset = presetManager->getSimilarPreset(old_preset, 2, index);
        if (new_preset != old_preset)
        {
            sliderPresetIncDec->setValue(new_preset, true);
            labelPresetNum->setText(String(new_preset), false);
        }
        //[/UserComboBoxCode_comboBox3]
    }
    else if (comboBoxThatHasChanged == comboBox4)
    {
        //[UserComboBoxCode_comboBox4] -- add your combo box handling code here..
        int index = comboBoxThatHasChanged->getSelectedItemIndex();
        int old_preset = sliderPresetIncDec->getValue();
        int new_preset = presetManager->getSimilarPreset(old_preset, 3, index);
        if (new_preset != old_preset)
        {
            sliderPresetIncDec->setValue(new_preset, true);
            labelPresetNum->setText(String(new_preset), false);
        }
        //[/UserComboBoxCode_comboBox4]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void TabMain::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == sliderInitialGap)
    {
        //[UserSliderCode_sliderInitialGap] -- add your slider handling code here..
        //[/UserSliderCode_sliderInitialGap]
    }
    else if (sliderThatWasMoved == sliderLength)
    {
        //[UserSliderCode_sliderLength] -- add your slider handling code here..
        //[/UserSliderCode_sliderLength]
    }
    else if (sliderThatWasMoved == sliderPreDelay)
    {
        //[UserSliderCode_sliderPreDelay] -- add your slider handling code here..
        //[/UserSliderCode_sliderPreDelay]
    }
    else if (sliderThatWasMoved == sliderDryGain)
    {
        //[UserSliderCode_sliderDryGain] -- add your slider handling code here..
        //[/UserSliderCode_sliderDryGain]
    }
    else if (sliderThatWasMoved == sliderWetGain)
    {
        //[UserSliderCode_sliderWetGain] -- add your slider handling code here..
        //[/UserSliderCode_sliderWetGain]
    }
    else if (sliderThatWasMoved == sliderMasterGain)
    {
        //[UserSliderCode_sliderMasterGain] -- add your slider handling code here..
        //[/UserSliderCode_sliderMasterGain]
    }
    else if (sliderThatWasMoved == sliderPresetIncDec)
    {
        //[UserSliderCode_sliderPresetIncDec] -- add your slider handling code here..
        int value = (int)sliderThatWasMoved->getValue();
        if (value == 0)
        {
            value = presetManager->getNumPresets();
            sliderPresetIncDec->setValue(value, false);
            labelPresetNum->setText(String(value), false);
        }
        if (value > presetManager->getNumPresets())
        {
            value = 1;
            sliderPresetIncDec->setValue(value, false);
            labelPresetNum->setText(String(value), false);
        }
        String str(value);
        labelPresetNum->setText (str, false);
        master->onValueChangedPresetNum(value);
        //[/UserSliderCode_sliderPresetIncDec]
    }
    else if (sliderThatWasMoved == slider0ms)
    {
        //[UserSliderCode_slider0ms] -- add your slider handling code here..
        paramEnvelope.db0ms = (float)sliderThatWasMoved->getValue();
        irPlot->setEnvelope(&paramEnvelope);
        //[/UserSliderCode_slider0ms]
    }
    else if (sliderThatWasMoved == slider20ms)
    {
        //[UserSliderCode_slider20ms] -- add your slider handling code here..
        paramEnvelope.db20ms = (float)sliderThatWasMoved->getValue();
        irPlot->setEnvelope(&paramEnvelope);
        //[/UserSliderCode_slider20ms]
    }
    else if (sliderThatWasMoved == slider120ms)
    {
        //[UserSliderCode_slider120ms] -- add your slider handling code here..
        paramEnvelope.db120ms = (float)sliderThatWasMoved->getValue();
        irPlot->setEnvelope(&paramEnvelope);
        //[/UserSliderCode_slider120ms]
    }
    else if (sliderThatWasMoved == sliderENDms)
    {
        //[UserSliderCode_sliderENDms] -- add your slider handling code here..
        paramEnvelope.dbENDms = (float)sliderThatWasMoved->getValue();
        irPlot->setEnvelope(&paramEnvelope);
        //[/UserSliderCode_sliderENDms]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void TabMain::setPresetManager(PresetManager *man)
{
    presetManager = man;
}


void TabMain::setGainDelayRange (ParamGainDelay *min,
                                 ParamGainDelay *value,
                                 ParamGainDelay *max)
{
    paramGainDelay.initialGap = value->initialGap;
    paramGainDelay.length     = value->length;
    paramGainDelay.preDelay   = value->preDelay;
    paramGainDelay.dryGain    = value->dryGain;
    paramGainDelay.wetGain    = value->wetGain;
    paramGainDelay.masterGain = value->masterGain;

    sliderInitialGap->setRange (min->initialGap, max->initialGap, 0.1);
    sliderInitialGap->setDoubleClickReturnValue (true, value->initialGap);
    sliderInitialGap->setValue (value->initialGap);

    sliderLength->setRange (min->length, max->length, 0.001);
    sliderLength->setDoubleClickReturnValue (true, value->length);
    sliderLength->setValue (value->length);

    sliderPreDelay->setRange (min->preDelay, max->preDelay, 0.1);
    sliderPreDelay->setDoubleClickReturnValue (true, value->preDelay);
    sliderPreDelay->setValue (value->preDelay);

    sliderDryGain->setRange (min->dryGain, max->dryGain, 0.1);
    sliderDryGain->setDoubleClickReturnValue (true, value->dryGain);
    sliderDryGain->setValue (value->dryGain);

    sliderWetGain->setRange (min->wetGain, max->wetGain, 0.1);
    sliderWetGain->setDoubleClickReturnValue (true, value->wetGain);
    sliderWetGain->setValue (value->wetGain);

    sliderMasterGain->setRange (min->masterGain, max->masterGain, 0.1);
    sliderMasterGain->setDoubleClickReturnValue (true, value->masterGain);
    sliderMasterGain->setValue (value->masterGain);
}


void TabMain::setEnvelope (ParamEnvelope *param)
{
    paramEnvelope.db0ms   = param->db0ms;
    paramEnvelope.db20ms  = param->db20ms;
    paramEnvelope.db120ms = param->db120ms;
    paramEnvelope.dbENDms = param->dbENDms;

    slider0ms->setDoubleClickReturnValue (true, param->db0ms);
    slider0ms->setValue (param->db0ms);

    slider20ms->setDoubleClickReturnValue (true, param->db20ms);
    slider20ms->setValue (param->db20ms);

    slider120ms->setDoubleClickReturnValue (true, param->db120ms);
    slider120ms->setValue (param->db120ms);

    sliderENDms->setDoubleClickReturnValue (true, param->dbENDms);
    sliderENDms->setValue (param->dbENDms);

    irPlot->setEnvelope(param);
}


void TabMain::setNum(int num)
{
    sliderPresetIncDec->setValue(num, true);
    labelPresetNum->setText(String(num), false);
}


void TabMain::setID(const String &id)
{
    labelPresetText->setText(id, false);
}


void TabMain::setNotes(const String &notes)
{
    textEditorNotes->setText(notes, false);
}


void TabMain::addNotes(const String &notes)
{
    textEditorNotes->setText(textEditorNotes->getText() + notes, false);
}


void TabMain::setComboText(int num, const std::vector<String> & items)
{
    ComboBox *combo = 0;

    switch (num) {
    case 0:
        combo = comboBox;
        break;
    case 1:
        combo = comboBox2;
        break;
    case 2:
        combo = comboBox3;
        break;
    case 3:
        combo = comboBox4;
        break;
    default:
        return;
    }

    combo->clear();
    int size = items.size();
    for (int i = 0; i < size; i++)
    {
        combo->addItem(items[i], i + 1);
        combo->setSelectedItemIndex(0, false);
    }
}


void TabMain::setComboIndex(int num, int index)
{
    ComboBox *combo = 0;

    switch (num) {
    case 0:
        combo = comboBox;
        break;
    case 1:
        combo = comboBox2;
        break;
    case 2:
        combo = comboBox3;
        break;
    case 3:
        combo = comboBox4;
        break;
    default:
        return;
    }

    combo->setSelectedItemIndex(index, true);
}



void TabMain::sliderDragEnded (Slider* sliderThatWasMoved)
{
    if (sliderThatWasMoved == sliderInitialGap)
    {
        paramGainDelay.initialGap = (float)sliderThatWasMoved->getValue();
        master->onValueChangedGainDelay(&paramGainDelay);
    }
    else if (sliderThatWasMoved == sliderLength)
    {
        paramGainDelay.length = (float)sliderThatWasMoved->getValue();
        master->onValueChangedGainDelay(&paramGainDelay);
    }
    else if (sliderThatWasMoved == sliderPreDelay)
    {
        paramGainDelay.preDelay = (float)sliderThatWasMoved->getValue();
        master->onValueChangedGainDelay(&paramGainDelay);
    }
    else if (sliderThatWasMoved == sliderDryGain)
    {
        paramGainDelay.dryGain = (float)sliderThatWasMoved->getValue();
        master->onValueChangedGainDelay(&paramGainDelay);
    }
    else if (sliderThatWasMoved == sliderWetGain)
    {
        paramGainDelay.wetGain = (float)sliderThatWasMoved->getValue();
        master->onValueChangedGainDelay(&paramGainDelay);
    }
    else if (sliderThatWasMoved == sliderMasterGain)
    {
        paramGainDelay.masterGain = (float)sliderThatWasMoved->getValue();
        master->onValueChangedGainDelay(&paramGainDelay);
    }
    else if (sliderThatWasMoved == slider0ms)
    {
        paramEnvelope.db0ms = (float)sliderThatWasMoved->getValue();
        master->onValueChangedEnvelope(&paramEnvelope);
    }
    else if (sliderThatWasMoved == slider20ms)
    {
        paramEnvelope.db20ms = (float)sliderThatWasMoved->getValue();
        master->onValueChangedEnvelope(&paramEnvelope);
    }
    else if (sliderThatWasMoved == slider120ms)
    {
        paramEnvelope.db120ms = (float)sliderThatWasMoved->getValue();
        master->onValueChangedEnvelope(&paramEnvelope);
    }
    else if (sliderThatWasMoved == sliderENDms)
    {
        paramEnvelope.dbENDms = (float)sliderThatWasMoved->getValue();
        master->onValueChangedEnvelope(&paramEnvelope);
    }
    else if (sliderThatWasMoved == sliderPresetIncDec)
    {
    }
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TabMain" componentName=""
                 parentClasses="public Component, public SliderListener" constructorParams="MasterAndCommander *m"
                 variableInitialisers="master (m)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330000013" fixedSize="1" initialWidth="828"
                 initialHeight="548">
  <BACKGROUND backgroundColour="ffffe000"/>
  <GROUPCOMPONENT name="new group" id="2aedd7f3e63566ae" memberName="groupComponentNotes"
                  virtualName="" explicitFocusOrder="0" pos="336 8 480 224" title="Notes"/>
  <GROUPCOMPONENT name="new group" id="ba8ec165006103c9" memberName="groupComponentMainControl"
                  virtualName="" explicitFocusOrder="0" pos="8 240 320 268" title="Main Controls"/>
  <LABEL name="new label" id="cb80d2c00f6f4fde" memberName="labelPresetNum"
         virtualName="" explicitFocusOrder="0" pos="16 16 64 48" bkgCol="ffffffff"
         textCol="ff000000" outlineCol="ffa6a6a6" edTextCol="ff000000"
         edBkgCol="0" labelText="1" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="32"
         bold="0" italic="0" justification="36"/>
  <GROUPCOMPONENT name="new group" id="4ae17a7023ba5a57" memberName="groupComponentPresetSelector"
                  virtualName="" explicitFocusOrder="0" pos="8 72 320 160" title="Preset Selector"/>
  <LABEL name="new label" id="339d5634c5d72249" memberName="labelPresetText"
         virtualName="" explicitFocusOrder="0" pos="112 16 208 48" bkgCol="ffffffff"
         outlineCol="ffa6a6a6" edTextCol="ff000000" edBkgCol="0" labelText="123456789012345678901234"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default monospaced font" fontsize="20" bold="0" italic="0"
         justification="36"/>
  <COMBOBOX name="new combo box" id="87beef21daa23739" memberName="comboBox"
            virtualName="" explicitFocusOrder="0" pos="24 96 288 24" editable="0"
            layout="33" items="channels: front" textWhenNonSelected="" textWhenNoItems="---"/>
  <COMBOBOX name="new combo box" id="bd5157c19f9c7890" memberName="comboBox2"
            virtualName="" explicitFocusOrder="0" pos="24 128 288 24" editable="0"
            layout="33" items="room: large concert hall" textWhenNonSelected=""
            textWhenNoItems="---"/>
  <COMBOBOX name="new combo box" id="e73e4e224a5962ef" memberName="comboBox3"
            virtualName="" explicitFocusOrder="0" pos="24 160 288 24" editable="0"
            layout="33" items="purpose: music" textWhenNonSelected="" textWhenNoItems="---"/>
  <COMBOBOX name="new combo box" id="10a8db346ad11563" memberName="comboBox4"
            virtualName="" explicitFocusOrder="0" pos="24 192 288 24" editable="0"
            layout="33" items="distance: 1m" textWhenNonSelected="" textWhenNoItems="---"/>
  <TEXTEDITOR name="new text editor" id="b55e466f47a1e1e2" memberName="textEditorNotes"
              virtualName="" explicitFocusOrder="0" pos="352 32 448 184" initialText=""
              multiline="1" retKeyStartsLine="1" readonly="1" scrollbars="1"
              caret="1" popupmenu="1"/>
  <GROUPCOMPONENT name="new group" id="a7877980277a1ec9" memberName="groupComponentIRPlot"
                  virtualName="" explicitFocusOrder="0" pos="336 240 480 268" title="Impulse Response"/>
  <SLIDER name="new slider" id="3a29d000adba987a" memberName="sliderInitialGap"
          virtualName="" explicitFocusOrder="0" pos="32 264 64 88" rotarysliderfill="ff100040"
          min="0" max="100" int="0.1" style="Rotary" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="72" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="5798d3217c731b41" memberName="labelInitialGap"
         virtualName="" explicitFocusOrder="0" pos="24 344 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Initial Gap" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="28765c3773e71052" memberName="sliderLength"
          virtualName="" explicitFocusOrder="0" pos="136 264 64 88" rotarysliderfill="ff100040"
          min="0" max="1" int="0.001" style="Rotary" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="72" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="f3c2b7440b347a61" memberName="labelLength"
         virtualName="" explicitFocusOrder="0" pos="128 344 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Length" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="7301188eec83b236" memberName="sliderPreDelay"
          virtualName="" explicitFocusOrder="0" pos="240 264 64 88" rotarysliderfill="ff100040"
          min="-100" max="100" int="0.1" style="Rotary" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="72" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="c38c84e89303b7bb" memberName="labelPreDelay"
         virtualName="" explicitFocusOrder="0" pos="232 344 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Pre-Delay" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="5cb4bd672fe901b9" memberName="sliderDryGain"
          virtualName="" explicitFocusOrder="0" pos="32 392 64 88" min="-120"
          max="0" int="0.1" style="Rotary" textBoxPos="TextBoxAbove" textBoxEditable="1"
          textBoxWidth="72" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="62ee2c982a920e38" memberName="labelDryGain"
         virtualName="" explicitFocusOrder="0" pos="32 472 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Dry Gain" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="8b8df4d967726bae" memberName="sliderWetGain"
          virtualName="" explicitFocusOrder="0" pos="136 392 64 88" min="-40"
          max="40" int="0.1" style="Rotary" textBoxPos="TextBoxAbove" textBoxEditable="1"
          textBoxWidth="72" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="new slider" id="1a1bd25399e125e9" memberName="sliderMasterGain"
          virtualName="" explicitFocusOrder="0" pos="240 392 64 88" min="-40"
          max="40" int="0.1" style="Rotary" textBoxPos="TextBoxAbove" textBoxEditable="1"
          textBoxWidth="72" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="578ba82700669d32" memberName="labelWetGain"
         virtualName="" explicitFocusOrder="0" pos="128 472 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Wet Gain" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="49662ce77eee2baf" memberName="labelMasterGain"
         virtualName="" explicitFocusOrder="0" pos="232 472 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Master Gain" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="32c4e582e5416a7f" memberName="sliderPresetIncDec"
          virtualName="" explicitFocusOrder="0" pos="88 16 18 48" min="0"
          max="257" int="1" style="IncDecButtons" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <GENERICCOMPONENT name="new component" id="fd905be5f952e922" memberName="irPlot"
                    virtualName="" explicitFocusOrder="0" pos="352 264 448 228" class="IRPlot"
                    params="master"/>
  <SLIDER name="new slider" id="41658652959a9450" memberName="slider0ms"
          virtualName="" explicitFocusOrder="0" pos="389 276 56 178" thumbcol="ffb00000"
          trackcol="60a08080" rotarysliderfill="7f800000" textboxtext="ff800000"
          textboxhighlight="40ff0000" textboxoutline="0" min="-80" max="20"
          int="0.1" style="LinearVertical" textBoxPos="TextBoxAbove" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="12" skewFactor="1"/>
  <SLIDER name="new slider" id="f87d8ddeeff666ea" memberName="slider20ms"
          virtualName="" explicitFocusOrder="0" pos="489 276 56 178" thumbcol="ffb00000"
          trackcol="60a08080" rotarysliderfill="7f800000" textboxtext="ff800000"
          textboxhighlight="40ff0000" textboxoutline="0" min="-80" max="20"
          int="0.1" style="LinearVertical" textBoxPos="TextBoxAbove" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="12" skewFactor="1"/>
  <SLIDER name="new slider" id="df0287b13f868f7a" memberName="slider120ms"
          virtualName="" explicitFocusOrder="0" pos="614 276 56 178" thumbcol="ffb00000"
          trackcol="60a08080" rotarysliderfill="7f800000" textboxtext="ff800000"
          textboxhighlight="40ff0000" textboxoutline="0" min="-80" max="20"
          int="0.1" style="LinearVertical" textBoxPos="TextBoxAbove" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="12" skewFactor="1"/>
  <SLIDER name="new slider" id="110b3dfc023c5cc5" memberName="sliderENDms"
          virtualName="" explicitFocusOrder="0" pos="739 276 56 178" thumbcol="ffb00000"
          trackcol="60a08080" rotarysliderfill="7f800000" textboxtext="ff800000"
          textboxhighlight="40ff0000" textboxoutline="0" min="-80" max="20"
          int="0.1" style="LinearVertical" textBoxPos="TextBoxAbove" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="12" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
