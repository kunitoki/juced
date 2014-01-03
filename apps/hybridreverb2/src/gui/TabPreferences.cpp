/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  18 Jan 2010 2:11:50 pm

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
#include "../windows_quirks.h"
#include "../MasterAndCommander.h"
//[/Headers]

#include "TabPreferences.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
TabPreferences::TabPreferences (MasterAndCommander *m)
    : master (m),
      groupComponentHelp (0),
      labelPreset (0),
      textEditorPreset (0),
      groupComponentStrategy (0),
      toggleButtonUniform (0),
      toggleButtonLowest (0),
      labelLatency (0),
      comboBoxLatency (0),
      textEditorHelp (0),
      textButton (0),
      label (0)
{
    addAndMakeVisible (groupComponentHelp = new GroupComponent (T("new group"),
                                                                T("Help")));

    addAndMakeVisible (labelPreset = new Label (T("new label"),
                                                T("Preset File:")));
    labelPreset->setFont (Font (15.0000f, Font::plain));
    labelPreset->setJustificationType (Justification::centredLeft);
    labelPreset->setEditable (false, false, false);
    labelPreset->setColour (TextEditor::textColourId, Colours::black);
    labelPreset->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (textEditorPreset = new TextEditor (T("new text editor")));
    textEditorPreset->setTooltip (T("XML formatted preset file"));
    textEditorPreset->setMultiLine (false);
    textEditorPreset->setReturnKeyStartsNewLine (false);
    textEditorPreset->setReadOnly (false);
    textEditorPreset->setScrollbarsShown (false);
    textEditorPreset->setCaretVisible (true);
    textEditorPreset->setPopupMenuEnabled (true);
    textEditorPreset->setText (String::empty);

    addAndMakeVisible (groupComponentStrategy = new GroupComponent (T("new group"),
                                                                    T("Segmentation Strategy")));

    addAndMakeVisible (toggleButtonUniform = new ToggleButton (T("new toggle button")));
    toggleButtonUniform->setTooltip (T("slightly higher, but constant processing load"));
    toggleButtonUniform->setButtonText (T("Uniform Processing Load"));
    toggleButtonUniform->setRadioGroupId (7007);
    toggleButtonUniform->addButtonListener (this);
    toggleButtonUniform->setToggleState (true, false);

    addAndMakeVisible (toggleButtonLowest = new ToggleButton (T("new toggle button")));
    toggleButtonLowest->setTooltip (T("lowest overal processing load with load peaks"));
    toggleButtonLowest->setButtonText (T("Lowest Mean Processing Load"));
    toggleButtonLowest->setRadioGroupId (7007);
    toggleButtonLowest->addButtonListener (this);

    addAndMakeVisible (labelLatency = new Label (T("new label"),
                                                 T("Latency:")));
    labelLatency->setFont (Font (15.0000f, Font::plain));
    labelLatency->setJustificationType (Justification::centredLeft);
    labelLatency->setEditable (false, false, false);
    labelLatency->setColour (TextEditor::textColourId, Colours::black);
    labelLatency->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (comboBoxLatency = new ComboBox (T("new combo box")));
    comboBoxLatency->setTooltip (T("latency selection"));
    comboBoxLatency->setEditableText (false);
    comboBoxLatency->setJustificationType (Justification::centredLeft);
    comboBoxLatency->setTextWhenNothingSelected (String::empty);
    comboBoxLatency->setTextWhenNoChoicesAvailable (T("(no choices)"));
    comboBoxLatency->addItem (T("64 samples (latency: 1.3ms at 48kHz)"), 1);
    comboBoxLatency->addItem (T("128 samples (latency: 2.7ms at 48kHz)"), 2);
    comboBoxLatency->addItem (T("256 samples (latency: 5.3ms at 48kHz)"), 3);
    comboBoxLatency->addItem (T("512 samples (latency: 10.7ms at 48kHz)"), 4);
    comboBoxLatency->addItem (T("1024 samples (latency: 21.3ms at 48kHz)"), 5);
    comboBoxLatency->addItem (T("2048 samples (latency: 42.7ms at 48kHz)"), 6);
    comboBoxLatency->addItem (T("4096 samples (latency: 85.3ms at 48kHz)"), 7);
    comboBoxLatency->addListener (this);

    addAndMakeVisible (textEditorHelp = new TextEditor (T("new text editor")));
    textEditorHelp->setMultiLine (true);
    textEditorHelp->setReturnKeyStartsNewLine (true);
    textEditorHelp->setReadOnly (true);
    textEditorHelp->setScrollbarsShown (true);
    textEditorHelp->setCaretVisible (true);
    textEditorHelp->setPopupMenuEnabled (true);
    textEditorHelp->setText (T("\n  Preset File:\n\n  This XML file defines the preset set.\n  (default: HybridReverb2_presets.xml)\n\n\n  Latency:\n\n  HybridReverb2 convolves the input signal with room\n  impulse responses which are partitioned into segments\n  of different size. This option specifies the size of the\n  initial segments which introduce a certain processing\n  latency. A small segment size results in a lower latency\n  at the cost of a higher computational complexity. An\n  effect plugin for musical instruments requires signal\n  processing with low latency. If the latency is not relevant\n  for your application, you can choose a larger segment\n  size for better performance.\n\n\n  Segmentation Strategy:\n\n  \"Uniform Processing Load\": This strategy tries to avoid\n  processing load peaks at the cost of a slightly higher\n  mean processing load. This is the recommended choice\n  for signal processing with low latency.\n  \"Lowest Mean Processing Load\": This strategy results in\n  the best overall performance. This is the recommended\n  choice for offline rendering.\n"));

    addAndMakeVisible (textButton = new TextButton (T("new button")));
    textButton->setTooltip (T("file chooser"));
    textButton->setButtonText (T("..."));
    textButton->addButtonListener (this);

    addAndMakeVisible (label = new Label (T("new label"),
                                          T("FIG1: Generation of a sound field as simulated in a virtual environment\nat a given listener position by a virtual coincidence microphone array with the outlined directivity pattern")));
    label->setFont (Font (T("Times New Roman"), 14.0000f, Font::italic));
    label->setJustificationType (Justification::topLeft);
    label->setEditable (false, false, false);
    label->setColour (Label::textColourId, Colour (0x89000000));
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x0));

    drawable1 = Drawable::createFromImageData (directivity2_svg, directivity2_svgSize);

    //[UserPreSize]
    textEditorPreset->addListener (this);
    comboBoxLatency->setSelectedItemIndex (0, true);
    //[/UserPreSize]

    setSize (828, 548);

    //[Constructor] You can add your own custom stuff here..
//    master->print("TabPreferences::TabPreferences : Waiting for your commands, Sir!");
    master->registerTabPreferences(this);
    //[/Constructor]
}

TabPreferences::~TabPreferences()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (groupComponentHelp);
    deleteAndZero (labelPreset);
    deleteAndZero (textEditorPreset);
    deleteAndZero (groupComponentStrategy);
    deleteAndZero (toggleButtonUniform);
    deleteAndZero (toggleButtonLowest);
    deleteAndZero (labelLatency);
    deleteAndZero (comboBoxLatency);
    deleteAndZero (textEditorHelp);
    deleteAndZero (textButton);
    deleteAndZero (label);
    deleteAndZero (drawable1);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TabPreferences::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xffffe000));

    g.setColour (Colours::black.withAlpha (0.2000f));
    jassert (drawable1 != 0);
    if (drawable1 != 0)
        drawable1->drawWithin (g, 24, 232, 362, 216,
                               RectanglePlacement::centred, 1.0f);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TabPreferences::resized()
{
    groupComponentHelp->setBounds (416, 8, 400, 500);
    labelPreset->setBounds (16, 32, 80, 24);
    textEditorPreset->setBounds (96, 32, 272, 24);
    groupComponentStrategy->setBounds (8, 112, 394, 88);
    toggleButtonUniform->setBounds (24, 136, 224, 24);
    toggleButtonLowest->setBounds (24, 160, 224, 24);
    labelLatency->setBounds (16, 72, 80, 24);
    comboBoxLatency->setBounds (96, 72, 304, 24);
    textEditorHelp->setBounds (432, 32, 368, 456);
    textButton->setBounds (372, 32, 30, 24);
    label->setBounds (16, 464, 394, 48);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void TabPreferences::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == toggleButtonUniform)
    {
        //[UserButtonCode_toggleButtonUniform] -- add your button handler code here..
        paramPreferences.strategy = STRATEGY_UNIFORM;
        master->print(String::formatted(T("TabPreferences: strategy = %d\n"), STRATEGY_UNIFORM));
        master->onValueChangedPreferences(paramPreferences);
        //[/UserButtonCode_toggleButtonUniform]
    }
    else if (buttonThatWasClicked == toggleButtonLowest)
    {
        //[UserButtonCode_toggleButtonLowest] -- add your button handler code here..
        paramPreferences.strategy = STRATEGY_LOWEST;
        master->print(String::formatted(T("TabPreferences: strategy = %d\n"), STRATEGY_LOWEST));
        master->onValueChangedPreferences(paramPreferences);
        //[/UserButtonCode_toggleButtonLowest]
    }
    else if (buttonThatWasClicked == textButton)
    {
        //[UserButtonCode_textButton] -- add your button handler code here..
        String filename = getFileChooserResult(master->getUserdir());
        if (filename != String::empty)
        {
            paramPreferences.presetFile = filename;
            textEditorPreset->setText(filename, false);
            master->print(T("TabPreferences: preset file = ") + filename);
            AlertWindow::showMessageBox(AlertWindow::InfoIcon,
                                        JUCE_T("Info"),
                                        JUCE_T("HybridReverb2 needs to be restarted to make your changes effective."));
            master->onValueChangedPreferences(paramPreferences);
        }
        //[/UserButtonCode_textButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void TabPreferences::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == comboBoxLatency)
    {
        //[UserComboBoxCode_comboBoxLatency] -- add your combo box handling code here..
        int index = comboBoxThatHasChanged->getSelectedItemIndex();
        paramPreferences.sflen = 64 << index;
        master->print(String::formatted(T("TabPreferences: SFLEN = %d\n"), paramPreferences.sflen));
        AlertWindow::showMessageBox(AlertWindow::InfoIcon,
                                    JUCE_T("Info"),
                                    JUCE_T("HybridReverb2 needs to be restarted to make your changes effective."));

        master->onValueChangedPreferences(paramPreferences);
        //[/UserComboBoxCode_comboBoxLatency]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void TabPreferences::setPreferences(const ParamPreferences & param)
{
    paramPreferences = param;
    textEditorPreset->setText(paramPreferences.presetFile, false);
    int sflenIndex = (int)log2(paramPreferences.sflen) - 6;
    comboBoxLatency->setSelectedItemIndex(sflenIndex, true);
    bool isUniform = (paramPreferences.strategy == STRATEGY_UNIFORM);
    toggleButtonUniform->setToggleState(isUniform, false);
    toggleButtonLowest->setToggleState(!isUniform, false);
}


String TabPreferences::getFileChooserResult(String dir)
{
    FileChooser fc(JUCE_T("Choose a preset file to open..."),
                   dir,
                   JUCE_T("*.xml"),
                   true);

    if (fc.browseForFileToOpen())
    {
        File chosenFile = fc.getResult();
        return chosenFile.getFullPathName();
    }

    return String::empty;
}


void TabPreferences::textEditorTextChanged (TextEditor &editor)
{
}


void TabPreferences::textEditorReturnKeyPressed (TextEditor &editor)
{
    paramPreferences.presetFile = editor.getText();
    master->print(T("TabPreferences: preset file = ") + paramPreferences.presetFile);
    AlertWindow::showMessageBox(AlertWindow::InfoIcon,
                                JUCE_T("Info"),
                                JUCE_T("HybridReverb2 needs to be restarted to make your changes effective."));
    master->onValueChangedPreferences(paramPreferences);
}


void TabPreferences::textEditorEscapeKeyPressed (TextEditor &editor)
{
}

void TabPreferences::textEditorFocusLost (TextEditor &editor)
{
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TabPreferences" componentName=""
                 parentClasses="public Component, public TextEditorListener" constructorParams="MasterAndCommander *m"
                 variableInitialisers="master (m)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330000013" fixedSize="0" initialWidth="828"
                 initialHeight="548">
  <BACKGROUND backgroundColour="ffffe000">
    <IMAGE pos="24 232 362 216" resource="directivity2_svg" opacity="0.2"
           mode="1"/>
  </BACKGROUND>
  <GROUPCOMPONENT name="new group" id="735a0a2a7a30ed50" memberName="groupComponentHelp"
                  virtualName="" explicitFocusOrder="0" pos="416 8 400 500" title="Help"/>
  <LABEL name="new label" id="9f5eff377a1b3c8f" memberName="labelPreset"
         virtualName="" explicitFocusOrder="0" pos="16 32 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Preset File:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="e8e07b2e8a259e33" memberName="textEditorPreset"
              virtualName="" explicitFocusOrder="0" pos="96 32 272 24" tooltip="XML formatted preset file"
              initialText="" multiline="0" retKeyStartsLine="0" readonly="0"
              scrollbars="0" caret="1" popupmenu="1"/>
  <GROUPCOMPONENT name="new group" id="cc8396c955dc75e8" memberName="groupComponentStrategy"
                  virtualName="" explicitFocusOrder="0" pos="8 112 394 88" title="Segmentation Strategy"/>
  <TOGGLEBUTTON name="new toggle button" id="3fe5a25a51b54518" memberName="toggleButtonUniform"
                virtualName="" explicitFocusOrder="0" pos="24 136 224 24" tooltip="slightly higher, but constant processing load"
                buttonText="Uniform Processing Load" connectedEdges="0" needsCallback="1"
                radioGroupId="7007" state="1"/>
  <TOGGLEBUTTON name="new toggle button" id="6c86fff6787f71e" memberName="toggleButtonLowest"
                virtualName="" explicitFocusOrder="0" pos="24 160 224 24" tooltip="lowest overal processing load with load peaks"
                buttonText="Lowest Mean Processing Load" connectedEdges="0" needsCallback="1"
                radioGroupId="7007" state="0"/>
  <LABEL name="new label" id="6825c569ae03a38a" memberName="labelLatency"
         virtualName="" explicitFocusOrder="0" pos="16 72 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Latency:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="new combo box" id="2c65de4dc3e7086" memberName="comboBoxLatency"
            virtualName="" explicitFocusOrder="0" pos="96 72 304 24" tooltip="latency selection"
            editable="0" layout="33" items="64 samples (latency: 1.3ms at 48kHz)&#10;128 samples (latency: 2.7ms at 48kHz)&#10;256 samples (latency: 5.3ms at 48kHz)&#10;512 samples (latency: 10.7ms at 48kHz)&#10;1024 samples (latency: 21.3ms at 48kHz)&#10;2048 samples (latency: 42.7ms at 48kHz)&#10;4096 samples (latency: 85.3ms at 48kHz)"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <TEXTEDITOR name="new text editor" id="bd5b83d29aa4002" memberName="textEditorHelp"
              virtualName="" explicitFocusOrder="0" pos="432 32 368 456" initialText="&#10;  Preset File:&#10;&#10;  This XML file defines the preset set.&#10;  (default: HybridReverb2_presets.xml)&#10;&#10;&#10;  Latency:&#10;&#10;  HybridReverb2 convolves the input signal with room&#10;  impulse responses which are partitioned into segments&#10;  of different size. This option specifies the size of the&#10;  initial segments which introduce a certain processing&#10;  latency. A small segment size results in a lower latency&#10;  at the cost of a higher computational complexity. An&#10;  effect plugin for musical instruments requires signal&#10;  processing with low latency. If the latency is not relevant&#10;  for your application, you can choose a larger segment&#10;  size for better performance.&#10;&#10;&#10;  Segmentation Strategy:&#10;&#10;  &quot;Uniform Processing Load&quot;: This strategy tries to avoid&#10;  processing load peaks at the cost of a slightly higher&#10;  mean processing load. This is the recommended choice&#10;  for signal processing with low latency.&#10;  &quot;Lowest Mean Processing Load&quot;: This strategy results in&#10;  the best overall performance. This is the recommended&#10;  choice for offline rendering.&#10;"
              multiline="1" retKeyStartsLine="1" readonly="1" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="new button" id="f637ba2e28c2e2ba" memberName="textButton"
              virtualName="" explicitFocusOrder="0" pos="372 32 30 24" tooltip="file chooser"
              buttonText="..." connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="407c242ecc8500cb" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="16 464 394 48" textCol="89000000"
         edTextCol="ff000000" edBkgCol="0" labelText="FIG1: Generation of a sound field as simulated in a virtual environment&#10;at a given listener position by a virtual coincidence microphone array with the outlined directivity pattern"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Times New Roman" fontsize="14" bold="0" italic="1"
         justification="9"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//==============================================================================
// Binary resources - be careful not to edit any of these sections!

// JUCER_RESOURCE: directivity2_svg, 24877, "../resources/directivity2.svg"
static const unsigned char resource_TabPreferences_directivity2_svg[] = { 60,63,120,109,108,32,118,101,114,115,105,111,110,61,34,49,46,48,34,32,101,110,99,111,100,105,110,103,61,34,85,84,70,45,56,34,32,
115,116,97,110,100,97,108,111,110,101,61,34,110,111,34,63,62,10,60,115,118,103,10,32,32,32,120,109,108,110,115,58,100,99,61,34,104,116,116,112,58,47,47,112,117,114,108,46,111,114,103,47,100,99,47,101,
108,101,109,101,110,116,115,47,49,46,49,47,34,10,32,32,32,120,109,108,110,115,58,99,99,61,34,104,116,116,112,58,47,47,99,114,101,97,116,105,118,101,99,111,109,109,111,110,115,46,111,114,103,47,110,115,
35,34,10,32,32,32,120,109,108,110,115,58,114,100,102,61,34,104,116,116,112,58,47,47,119,119,119,46,119,51,46,111,114,103,47,49,57,57,57,47,48,50,47,50,50,45,114,100,102,45,115,121,110,116,97,120,45,110,
115,35,34,10,32,32,32,120,109,108,110,115,58,115,118,103,61,34,104,116,116,112,58,47,47,119,119,119,46,119,51,46,111,114,103,47,50,48,48,48,47,115,118,103,34,10,32,32,32,120,109,108,110,115,61,34,104,
116,116,112,58,47,47,119,119,119,46,119,51,46,111,114,103,47,50,48,48,48,47,115,118,103,34,10,32,32,32,120,109,108,110,115,58,115,111,100,105,112,111,100,105,61,34,104,116,116,112,58,47,47,115,111,100,
105,112,111,100,105,46,115,111,117,114,99,101,102,111,114,103,101,46,110,101,116,47,68,84,68,47,115,111,100,105,112,111,100,105,45,48,46,100,116,100,34,10,32,32,32,120,109,108,110,115,58,105,110,107,115,
99,97,112,101,61,34,104,116,116,112,58,47,47,119,119,119,46,105,110,107,115,99,97,112,101,46,111,114,103,47,110,97,109,101,115,112,97,99,101,115,47,105,110,107,115,99,97,112,101,34,10,32,32,32,118,101,
114,115,105,111,110,61,34,49,46,49,34,10,32,32,32,98,97,115,101,80,114,111,102,105,108,101,61,34,102,117,108,108,34,10,32,32,32,105,100,61,34,98,111,100,121,34,10,32,32,32,119,105,100,116,104,61,34,56,
105,110,34,10,32,32,32,104,101,105,103,104,116,61,34,56,105,110,34,10,32,32,32,118,105,101,119,66,111,120,61,34,48,32,48,32,49,32,49,34,10,32,32,32,112,114,101,115,101,114,118,101,65,115,112,101,99,116,
82,97,116,105,111,61,34,110,111,110,101,34,10,32,32,32,115,111,100,105,112,111,100,105,58,118,101,114,115,105,111,110,61,34,48,46,51,50,34,10,32,32,32,105,110,107,115,99,97,112,101,58,118,101,114,115,
105,111,110,61,34,48,46,52,54,34,10,32,32,32,115,111,100,105,112,111,100,105,58,100,111,99,110,97,109,101,61,34,100,105,114,101,99,116,105,118,105,116,121,50,46,115,118,103,34,10,32,32,32,105,110,107,
115,99,97,112,101,58,111,117,116,112,117,116,95,101,120,116,101,110,115,105,111,110,61,34,111,114,103,46,105,110,107,115,99,97,112,101,46,111,117,116,112,117,116,46,115,118,103,46,105,110,107,115,99,97,
112,101,34,62,10,32,32,60,109,101,116,97,100,97,116,97,10,32,32,32,32,32,105,100,61,34,109,101,116,97,100,97,116,97,57,54,34,62,10,32,32,32,32,60,114,100,102,58,82,68,70,62,10,32,32,32,32,32,32,60,99,
99,58,87,111,114,107,10,32,32,32,32,32,32,32,32,32,114,100,102,58,97,98,111,117,116,61,34,34,62,10,32,32,32,32,32,32,32,32,60,100,99,58,102,111,114,109,97,116,62,105,109,97,103,101,47,115,118,103,43,120,
109,108,60,47,100,99,58,102,111,114,109,97,116,62,10,32,32,32,32,32,32,32,32,60,100,99,58,116,121,112,101,10,32,32,32,32,32,32,32,32,32,32,32,114,100,102,58,114,101,115,111,117,114,99,101,61,34,104,116,
116,112,58,47,47,112,117,114,108,46,111,114,103,47,100,99,47,100,99,109,105,116,121,112,101,47,83,116,105,108,108,73,109,97,103,101,34,32,47,62,10,32,32,32,32,32,32,60,47,99,99,58,87,111,114,107,62,10,
32,32,32,32,60,47,114,100,102,58,82,68,70,62,10,32,32,60,47,109,101,116,97,100,97,116,97,62,10,32,32,60,100,101,102,115,10,32,32,32,32,32,105,100,61,34,100,101,102,115,57,52,34,62,10,32,32,32,32,60,105,
110,107,115,99,97,112,101,58,112,101,114,115,112,101,99,116,105,118,101,10,32,32,32,32,32,32,32,115,111,100,105,112,111,100,105,58,116,121,112,101,61,34,105,110,107,115,99,97,112,101,58,112,101,114,115,
112,51,100,34,10,32,32,32,32,32,32,32,105,110,107,115,99,97,112,101,58,118,112,95,120,61,34,48,32,58,32,51,54,48,32,58,32,49,34,10,32,32,32,32,32,32,32,105,110,107,115,99,97,112,101,58,118,112,95,121,
61,34,48,32,58,32,49,48,48,48,32,58,32,48,34,10,32,32,32,32,32,32,32,105,110,107,115,99,97,112,101,58,118,112,95,122,61,34,55,50,48,32,58,32,51,54,48,32,58,32,49,34,10,32,32,32,32,32,32,32,105,110,107,
115,99,97,112,101,58,112,101,114,115,112,51,100,45,111,114,105,103,105,110,61,34,51,54,48,32,58,32,50,52,48,32,58,32,49,34,10,32,32,32,32,32,32,32,105,100,61,34,112,101,114,115,112,101,99,116,105,118,
101,57,56,34,32,47,62,10,32,32,60,47,100,101,102,115,62,10,32,32,60,115,111,100,105,112,111,100,105,58,110,97,109,101,100,118,105,101,119,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,119,105,110,
100,111,119,45,104,101,105,103,104,116,61,34,55,52,52,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,119,105,110,100,111,119,45,119,105,100,116,104,61,34,49,48,49,54,34,10,32,32,32,32,32,105,110,
107,115,99,97,112,101,58,112,97,103,101,115,104,97,100,111,119,61,34,50,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,112,97,103,101,111,112,97,99,105,116,121,61,34,48,46,48,34,10,32,32,32,32,
32,103,117,105,100,101,116,111,108,101,114,97,110,99,101,61,34,49,48,46,48,34,10,32,32,32,32,32,103,114,105,100,116,111,108,101,114,97,110,99,101,61,34,49,48,46,48,34,10,32,32,32,32,32,111,98,106,101,
99,116,116,111,108,101,114,97,110,99,101,61,34,49,48,46,48,34,10,32,32,32,32,32,98,111,114,100,101,114,111,112,97,99,105,116,121,61,34,49,46,48,34,10,32,32,32,32,32,98,111,114,100,101,114,99,111,108,111,
114,61,34,35,54,54,54,54,54,54,34,10,32,32,32,32,32,112,97,103,101,99,111,108,111,114,61,34,35,102,102,102,102,102,102,34,10,32,32,32,32,32,105,100,61,34,98,97,115,101,34,10,32,32,32,32,32,115,104,111,
119,103,114,105,100,61,34,102,97,108,115,101,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,122,111,111,109,61,34,48,46,54,52,55,50,50,50,50,50,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,
58,99,120,61,34,51,54,48,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,121,61,34,52,50,56,46,56,56,50,48,52,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,119,105,110,100,111,119,45,
120,61,34,49,48,50,52,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,119,105,110,100,111,119,45,121,61,34,48,34,10,32,32,32,32,32,105,110,107,115,99,97,112,101,58,99,117,114,114,101,110,116,45,
108,97,121,101,114,61,34,98,111,100,121,34,32,47,62,10,32,32,60,116,105,116,108,101,10,32,32,32,32,32,105,100,61,34,116,105,116,108,101,51,34,62,83,86,71,32,100,114,97,119,105,110,103,60,47,116,105,116,
108,101,62,10,32,32,60,100,101,115,99,10,32,32,32,32,32,105,100,61,34,100,101,115,99,53,34,62,84,104,105,115,32,119,97,115,32,112,114,111,100,117,99,101,100,32,98,121,32,118,101,114,115,105,111,110,32,
52,46,50,32,111,102,32,71,78,85,32,108,105,98,112,108,111,116,44,32,97,32,102,114,101,101,32,108,105,98,114,97,114,121,32,102,111,114,32,101,120,112,111,114,116,105,110,103,32,50,45,68,32,118,101,99,116,
111,114,32,103,114,97,112,104,105,99,115,46,60,47,100,101,115,99,62,10,32,32,60,103,10,32,32,32,32,32,105,100,61,34,99,111,110,116,101,110,116,34,10,32,32,32,32,32,116,114,97,110,115,102,111,114,109,61,
34,109,97,116,114,105,120,40,52,46,52,55,57,51,48,51,54,101,45,51,44,48,44,48,44,45,52,46,52,49,53,49,56,48,52,101,45,51,44,51,46,54,48,48,52,55,52,53,101,45,50,44,48,46,52,56,55,50,49,54,57,41,34,10,
32,32,32,32,32,120,109,108,58,115,112,97,99,101,61,34,112,114,101,115,101,114,118,101,34,10,32,32,32,32,32,115,116,114,111,107,101,45,109,105,116,101,114,108,105,109,105,116,61,34,49,48,46,52,51,51,34,
10,32,32,32,32,32,102,105,108,108,45,114,117,108,101,61,34,101,118,101,110,45,111,100,100,34,10,32,32,32,32,32,102,111,110,116,45,115,116,121,108,101,61,34,110,111,114,109,97,108,34,10,32,32,32,32,32,
102,111,110,116,45,118,97,114,105,97,110,116,61,34,110,111,114,109,97,108,34,10,32,32,32,32,32,102,111,110,116,45,119,101,105,103,104,116,61,34,110,111,114,109,97,108,34,10,32,32,32,32,32,102,111,110,
116,45,115,116,114,101,116,99,104,61,34,110,111,114,109,97,108,34,10,32,32,32,32,32,102,111,110,116,45,115,105,122,101,45,97,100,106,117,115,116,61,34,110,111,110,101,34,10,32,32,32,32,32,108,101,116,
116,101,114,45,115,112,97,99,105,110,103,61,34,110,111,114,109,97,108,34,10,32,32,32,32,32,119,111,114,100,45,115,112,97,99,105,110,103,61,34,110,111,114,109,97,108,34,10,32,32,32,32,32,115,116,121,108,
101,61,34,102,111,110,116,45,115,116,121,108,101,58,110,111,114,109,97,108,59,102,111,110,116,45,118,97,114,105,97,110,116,58,110,111,114,109,97,108,59,102,111,110,116,45,119,101,105,103,104,116,58,110,
111,114,109,97,108,59,102,111,110,116,45,115,116,114,101,116,99,104,58,110,111,114,109,97,108,59,108,101,116,116,101,114,45,115,112,97,99,105,110,103,58,110,111,114,109,97,108,59,119,111,114,100,45,115,
112,97,99,105,110,103,58,110,111,114,109,97,108,59,116,101,120,116,45,97,110,99,104,111,114,58,115,116,97,114,116,59,102,105,108,108,58,110,111,110,101,59,102,105,108,108,45,111,112,97,99,105,116,121,
58,49,59,115,116,114,111,107,101,58,35,48,48,48,48,48,48,59,115,116,114,111,107,101,45,108,105,110,101,99,97,112,58,98,117,116,116,59,115,116,114,111,107,101,45,108,105,110,101,106,111,105,110,58,109,
105,116,101,114,59,115,116,114,111,107,101,45,109,105,116,101,114,108,105,109,105,116,58,49,48,46,52,51,50,57,57,57,54,49,59,115,116,114,111,107,101,45,100,97,115,104,97,114,114,97,121,58,110,111,110,
101,59,115,116,114,111,107,101,45,100,97,115,104,111,102,102,115,101,116,58,48,59,115,116,114,111,107,101,45,111,112,97,99,105,116,121,58,49,34,62,10,60,112,111,108,121,108,105,110,101,10,32,32,32,112,
111,105,110,116,115,61,34,57,49,46,52,52,57,44,49,48,50,46,56,50,32,57,51,46,55,49,57,44,49,48,48,46,53,54,32,57,53,46,57,56,56,44,49,48,50,46,56,50,32,57,56,46,50,53,52,44,49,48,48,46,53,54,32,49,48,
48,46,53,50,44,49,48,50,46,56,50,32,49,48,50,46,55,57,44,49,48,48,46,53,54,32,49,48,53,46,48,54,44,49,48,50,46,56,50,32,49,48,55,46,51,50,44,49,48,48,46,53,54,32,49,48,57,46,53,57,44,49,48,50,46,56,50,
32,49,49,49,46,56,54,44,49,48,48,46,53,54,32,49,49,52,46,49,51,44,49,48,50,46,56,50,32,49,49,54,46,51,57,44,49,48,48,46,53,54,32,49,49,56,46,54,54,44,49,48,50,46,56,50,32,49,50,48,46,57,51,44,49,48,48,
46,53,54,32,49,50,51,46,50,44,49,48,50,46,56,50,32,49,50,53,46,52,54,44,49,48,48,46,53,54,32,49,50,55,46,55,51,44,49,48,50,46,56,50,32,49,51,48,44,49,48,48,46,53,54,32,49,51,50,46,50,55,44,49,48,50,46,
56,50,32,49,51,52,46,53,52,44,49,48,48,46,53,54,32,49,51,54,46,56,44,49,48,50,46,56,50,32,49,51,57,46,48,55,44,49,48,48,46,53,54,32,49,52,49,46,51,52,44,49,48,50,46,56,50,32,49,52,51,46,54,44,49,48,48,
46,53,54,32,49,52,53,46,56,56,44,49,48,50,46,56,50,32,49,52,56,46,49,52,44,49,48,48,46,53,54,32,49,53,48,46,52,49,44,49,48,50,46,56,50,32,49,53,50,46,54,56,44,49,48,48,46,53,54,32,49,53,52,46,57,53,44,
49,48,50,46,56,50,32,49,53,55,46,50,49,44,49,48,48,46,53,54,32,49,53,57,46,52,56,44,49,48,50,46,56,50,32,49,54,49,46,55,53,44,49,48,48,46,53,54,32,49,54,52,46,48,50,44,49,48,50,46,56,50,32,49,54,54,46,
50,57,44,49,48,48,46,53,54,32,49,54,56,46,53,53,44,49,48,50,46,56,50,32,34,10,32,32,32,105,100,61,34,112,111,108,121,108,105,110,101,57,34,10,32,32,32,115,116,121,108,101,61,34,115,116,114,111,107,101,
45,119,105,100,116,104,58,48,46,52,55,50,52,50,57,57,57,34,32,47,62,10,60,112,111,108,121,108,105,110,101,10,32,32,32,112,111,105,110,116,115,61,34,49,55,48,46,56,50,44,49,48,50,46,56,50,32,49,54,56,46,
53,53,44,49,48,48,46,53,54,32,49,55,48,46,56,50,44,57,56,46,50,56,53,32,49,54,56,46,53,53,44,57,54,46,48,50,32,49,55,48,46,56,50,44,57,51,46,55,53,32,49,54,56,46,53,53,44,57,49,46,52,56,52,32,49,55,48,
46,56,50,44,56,57,46,50,49,53,32,49,54,56,46,53,53,44,56,54,46,57,52,57,32,49,55,48,46,56,50,44,56,52,46,54,56,32,49,54,56,46,53,53,44,56,50,46,52,49,52,32,49,55,48,46,56,50,44,56,48,46,49,52,53,32,49,
54,56,46,53,53,44,55,55,46,56,55,57,32,49,55,48,46,56,50,44,55,53,46,54,48,57,32,49,54,56,46,53,53,44,55,51,46,51,52,52,32,49,55,48,46,56,50,44,55,49,46,48,55,52,32,49,54,56,46,53,53,44,54,56,46,56,48,
57,32,49,55,48,46,56,50,44,54,54,46,53,51,57,32,49,54,56,46,53,53,44,54,52,46,50,55,51,32,49,55,48,46,56,50,44,54,50,46,48,48,52,32,49,54,56,46,53,53,44,53,57,46,55,51,56,32,49,55,48,46,56,50,44,53,55,
46,52,54,57,32,49,54,56,46,53,53,44,53,53,46,50,48,51,32,49,55,48,46,56,50,44,53,50,46,57,51,52,32,49,54,56,46,53,53,44,53,48,46,54,54,56,32,49,55,48,46,56,50,44,52,56,46,51,57,56,32,49,54,56,46,53,53,
44,52,54,46,49,51,51,32,49,55,48,46,56,50,44,52,51,46,56,54,51,32,49,54,56,46,53,53,44,52,49,46,53,57,52,32,49,55,48,46,56,50,44,51,57,46,51,50,56,32,49,54,56,46,53,53,44,51,55,46,48,53,57,32,49,55,48,
46,56,50,44,51,52,46,55,57,51,32,49,54,56,46,53,53,44,51,50,46,53,50,51,32,49,55,48,46,56,50,44,51,48,46,50,53,56,32,49,54,56,46,53,53,44,50,55,46,57,56,56,32,49,55,48,46,56,50,44,50,53,46,55,50,51,32,
49,54,56,46,53,53,44,50,51,46,52,53,51,32,49,55,48,46,56,50,44,50,49,46,49,56,56,32,49,54,56,46,53,53,44,49,56,46,57,49,56,32,49,55,48,46,56,50,44,49,54,46,54,53,50,32,49,54,56,46,53,53,44,49,52,46,51,
56,51,32,49,55,48,46,56,50,44,49,50,46,49,49,55,32,49,54,56,46,53,53,44,57,46,56,52,55,55,32,49,55,48,46,56,50,44,55,46,53,56,50,32,49,54,56,46,53,53,44,53,46,51,49,50,53,32,49,55,48,46,56,50,44,51,46,
48,52,54,57,32,34,10,32,32,32,105,100,61,34,112,111,108,121,108,105,110,101,49,49,34,10,32,32,32,115,116,121,108,101,61,34,115,116,114,111,107,101,45,119,105,100,116,104,58,48,46,52,55,50,52,50,57,57,
57,34,32,47,62,10,60,112,111,108,121,108,105,110,101,10,32,32,32,112,111,105,110,116,115,61,34,49,55,48,46,56,50,44,48,46,55,55,55,51,52,32,49,54,56,46,53,53,44,51,46,48,52,54,57,32,49,54,54,46,50,57,
44,48,46,55,55,55,51,52,32,49,54,52,46,48,50,44,51,46,48,52,54,57,32,49,54,49,46,55,53,44,48,46,55,55,55,51,52,32,49,53,57,46,52,56,44,51,46,48,52,54,57,32,49,53,55,46,50,49,44,48,46,55,55,55,51,52,32,
49,53,52,46,57,53,44,51,46,48,52,54,57,32,49,53,50,46,54,56,44,48,46,55,55,55,51,52,32,49,53,48,46,52,49,44,51,46,48,52,54,57,32,49,52,56,46,49,52,44,48,46,55,55,55,51,52,32,49,52,53,46,56,56,44,51,46,
48,52,54,57,32,49,52,51,46,54,44,48,46,55,55,55,51,52,32,49,52,49,46,51,52,44,51,46,48,52,54,57,32,49,51,57,46,48,55,44,48,46,55,55,55,51,52,32,49,51,54,46,56,44,51,46,48,52,54,57,32,49,51,52,46,53,52,
44,48,46,55,55,55,51,52,32,49,51,50,46,50,55,44,51,46,48,52,54,57,32,49,51,48,44,48,46,55,55,55,51,52,32,49,50,55,46,55,51,44,51,46,48,52,54,57,32,49,50,53,46,52,54,44,48,46,55,55,55,51,52,32,49,50,51,
46,50,44,51,46,48,52,54,57,32,49,50,48,46,57,51,44,48,46,55,55,55,51,52,32,49,49,56,46,54,54,44,51,46,48,52,54,57,32,49,49,54,46,51,57,44,48,46,55,55,55,51,52,32,49,49,52,46,49,51,44,51,46,48,52,54,57,
32,49,49,49,46,56,54,44,48,46,55,55,55,51,52,32,49,48,57,46,53,57,44,51,46,48,52,54,57,32,49,48,55,46,51,50,44,48,46,55,55,55,51,52,32,49,48,53,46,48,54,44,51,46,48,52,54,57,32,49,48,50,46,55,57,44,48,
46,55,55,55,51,52,32,49,48,48,46,53,50,44,51,46,48,52,54,57,32,57,56,46,50,53,52,44,48,46,55,55,55,51,52,32,57,53,46,57,56,56,44,51,46,48,52,54,57,32,57,51,46,55,49,57,44,48,46,55,55,55,51,52,32,34,10,
32,32,32,105,100,61,34,112,111,108,121,108,105,110,101,49,51,34,10,32,32,32,115,116,121,108,101,61,34,115,116,114,111,107,101,45,119,105,100,116,104,58,48,46,52,55,50,52,50,57,57,57,34,32,47,62,10,60,
112,111,108,121,108,105,110,101,10,32,32,32,112,111,105,110,116,115,61,34,57,49,46,52,52,57,44,48,46,55,55,55,51,52,32,57,51,46,55,49,57,44,51,46,48,52,54,57,32,57,49,46,52,52,57,44,53,46,51,49,50,53,
32,57,51,46,55,49,57,44,55,46,53,56,50,32,57,49,46,52,52,57,44,57,46,56,52,55,55,32,57,51,46,55,49,57,44,49,50,46,49,49,55,32,57,49,46,52,52,57,44,49,52,46,51,56,51,32,57,51,46,55,49,57,44,49,54,46,54,
53,50,32,57,49,46,52,52,57,44,49,56,46,57,49,56,32,57,51,46,55,49,57,44,50,49,46,49,56,56,32,57,49,46,52,52,57,44,50,51,46,52,53,51,32,57,51,46,55,49,57,44,50,53,46,55,50,51,32,57,49,46,52,52,57,44,50,
55,46,57,56,56,32,57,51,46,55,49,57,44,51,48,46,50,53,56,32,57,49,46,52,52,57,44,51,50,46,53,50,51,32,57,51,46,55,49,57,44,51,52,46,55,57,51,32,57,49,46,52,52,57,44,51,55,46,48,53,57,32,57,51,46,55,49,
57,44,51,57,46,51,50,56,32,57,49,46,52,52,57,44,52,49,46,53,57,52,32,57,51,46,55,49,57,44,52,51,46,56,54,51,32,57,49,46,52,52,57,44,52,54,46,49,51,51,32,57,51,46,55,49,57,44,52,56,46,51,57,56,32,57,49,
46,52,52,57,44,53,48,46,54,54,56,32,57,51,46,55,49,57,44,53,50,46,57,51,52,32,57,49,46,52,52,57,44,53,53,46,50,48,51,32,57,51,46,55,49,57,44,53,55,46,52,54,57,32,57,49,46,52,52,57,44,53,57,46,55,51,56,
32,57,51,46,55,49,57,44,54,50,46,48,48,52,32,57,49,46,52,52,57,44,54,52,46,50,55,51,32,57,51,46,55,49,57,44,54,54,46,53,51,57,32,57,49,46,52,52,57,44,54,56,46,56,48,57,32,57,51,46,55,49,57,44,55,49,46,
48,55,52,32,57,49,46,52,52,57,44,55,51,46,51,52,52,32,57,51,46,55,49,57,44,55,53,46,54,48,57,32,57,49,46,52,52,57,44,55,55,46,56,55,57,32,57,51,46,55,49,57,44,56,48,46,49,52,53,32,57,49,46,52,52,57,44,
56,50,46,52,49,52,32,57,51,46,55,49,57,44,56,52,46,54,56,32,57,49,46,52,52,57,44,56,54,46,57,52,57,32,57,51,46,55,49,57,44,56,57,46,50,49,53,32,57,49,46,52,52,57,44,57,49,46,52,56,52,32,57,51,46,55,49,
57,44,57,51,46,55,53,32,57,49,46,52,52,57,44,57,54,46,48,50,32,57,51,46,55,49,57,44,57,56,46,50,56,53,32,57,49,46,52,52,57,44,49,48,48,46,53,54,32,34,10,32,32,32,105,100,61,34,112,111,108,121,108,105,
110,101,49,53,34,10,32,32,32,115,116,121,108,101,61,34,115,116,114,111,107,101,45,119,105,100,116,104,58,48,46,52,55,50,52,50,57,57,57,34,32,47,62,10,60,112,97,116,104,10,32,32,32,100,61,34,77,32,49,51,
53,46,54,55,44,53,49,46,50,51,52,32,76,32,49,51,53,46,54,55,44,53,49,46,48,48,49,32,76,32,49,51,53,46,54,53,44,53,48,46,55,55,49,32,76,32,49,51,53,46,54,50,44,53,48,46,53,52,52,32,76,32,49,51,53,46,53,
56,44,53,48,46,51,50,49,32,76,32,49,51,53,46,53,51,44,53,48,46,49,48,49,32,76,32,49,51,53,46,52,55,44,52,57,46,56,56,54,32,76,32,49,51,53,46,52,44,52,57,46,54,55,53,32,76,32,49,51,53,46,51,50,44,52,57,
46,52,54,57,32,76,32,49,51,53,46,50,50,44,52,57,46,50,54,57,32,76,32,49,51,53,46,49,50,44,52,57,46,48,55,51,32,76,32,49,51,53,46,48,50,44,52,56,46,56,56,51,32,76,32,49,51,52,46,57,44,52,56,46,54,57,57,
32,76,32,49,51,52,46,55,55,44,52,56,46,53,50,49,32,76,32,49,51,52,46,54,52,44,52,56,46,51,53,32,76,32,49,51,52,46,52,57,44,52,56,46,49,56,53,32,76,32,49,51,52,46,51,52,44,52,56,46,48,50,56,32,76,32,49,
51,52,46,49,57,44,52,55,46,56,55,56,32,76,32,49,51,52,46,48,50,44,52,55,46,55,51,53,32,76,32,49,51,51,46,56,53,44,52,55,46,54,32,76,32,49,51,51,46,54,55,44,52,55,46,52,55,52,32,76,32,49,51,51,46,52,57,
44,52,55,46,51,53,54,32,76,32,49,51,51,46,51,44,52,55,46,50,52,55,32,76,32,49,51,51,46,49,44,52,55,46,49,52,55,32,76,32,49,51,50,46,57,44,52,55,46,48,53,54,32,76,32,49,51,50,46,55,44,52,54,46,57,55,52,
32,76,32,49,51,50,46,52,57,44,52,54,46,57,48,51,32,76,32,49,51,50,46,50,55,44,52,54,46,56,52,50,32,76,32,49,51,50,46,48,53,44,52,54,46,55,57,49,32,76,32,49,51,49,46,56,51,44,52,54,46,55,53,49,32,76,32,
49,51,49,46,54,44,52,54,46,55,50,51,32,76,32,49,51,49,46,51,55,44,52,54,46,55,48,53,32,76,32,49,51,49,46,49,52,44,52,54,46,54,57,57,32,67,32,49,50,56,46,54,51,44,52,54,46,54,57,57,32,49,50,54,46,54,44,
52,56,46,55,51,32,49,50,54,46,54,44,53,49,46,50,51,52,32,67,32,49,50,54,46,54,44,53,51,46,55,51,56,32,49,50,56,46,54,51,44,53,53,46,55,55,32,49,51,49,46,49,52,44,53,53,46,55,55,32,67,32,49,51,51,46,54,
52,44,53,53,46,55,55,32,49,51,53,46,54,55,44,53,51,46,55,51,56,32,49,51,53,46,54,55,44,53,49,46,50,51,52,32,122,34,10,32,32,32,105,100,61,34,112,97,116,104,49,55,34,10,32,32,32,115,116,121,108,101,61,
34,115,116,114,111,107,101,45,119,105,100,116,104,58,48,46,52,55,50,52,50,57,57,57,34,32,47,62,10,60,108,105,110,101,10,32,32,32,120,49,61,34,49,51,50,46,50,49,48,48,49,34,10,32,32,32,121,49,61,34,53,
52,46,57,52,57,48,48,49,34,10,32,32,32,120,50,61,34,49,51,51,46,52,54,48,48,49,34,10,32,32,32,121,50,61,34,53,52,46,54,57,57,48,48,49,34,10,32,32,32,105,100,61,34,108,105,110,101,49,57,34,10,32,32,32,
115,116,121,108,101,61,34,115,116,114,111,107,101,45,119,105,100,116,104,58,48,46,52,55,50,52,50,57,57,57,34,32,47,62,10,60,112,111,108,121,108,105,110,101,10,32,32,32,112,111,105,110,116,115,61,34,49,
50,57,46,55,53,44,53,53,46,53,55,56,32,49,50,57,46,55,53,44,53,53,46,54,52,49,32,49,50,57,46,56,56,44,53,53,46,57,53,55,32,49,51,48,46,49,51,44,53,54,46,53,50,51,32,49,51,48,46,51,56,44,53,55,46,48,50,
55,32,49,51,48,46,55,44,53,55,46,53,51,49,32,49,51,49,46,49,52,44,53,55,46,55,50,51,32,49,51,49,46,53,49,44,53,55,46,53,57,52,32,49,51,49,46,56,51,44,53,55,46,49,53,50,32,49,51,50,46,48,56,44,53,54,46,
54,52,56,32,49,51,50,46,50,49,44,53,54,46,49,52,53,32,49,51,50,46,51,51,44,53,53,46,56,51,50,32,49,51,50,46,51,51,44,53,53,46,55,55,32,34,10,32,32,32,105,100,61,34,112,111,108,121,108,105,110,101,50,49,
34,10,32,32,32,115,116,121,108,101,61,34,115,116,114,111,107,101,45,119,105,100,116,104,58,48,46,52,55,50,52,50,57,57,57,59,115,116,114,111,107,101,45,108,105,110,101,106,111,105,110,58,98,101,118,101,
108,34,32,47,62,10,60,112,111,108,121,108,105,110,101,10,32,32,32,112,111,105,110,116,115,61,34,49,50,54,46,55,51,44,53,50,46,48,53,49,32,49,50,54,46,54,54,44,53,50,46,49,56,32,49,50,54,46,53,52,44,53,
50,46,52,51,32,49,50,54,46,51,53,44,53,50,46,55,52,54,32,49,50,54,46,49,54,44,53,50,46,57,57,54,32,49,50,53,46,57,55,44,53,51,46,49,56,56,32,49,50,53,46,55,56,44,53,51,46,50,53,32,49,50,53,46,54,54,44,
53,51,46,48,53,57,32,49,50,53,46,53,51,44,53,50,46,52,57,50,32,49,50,53,46,52,54,44,53,49,46,57,50,54,32,49,50,53,46,52,54,44,53,49,46,51,53,57,32,49,50,53,46,53,51,44,53,48,46,56,53,53,32,49,50,53,46,
53,51,44,53,48,46,50,50,55,32,49,50,53,46,54,54,44,52,57,46,54,54,32,49,50,53,46,55,56,44,52,57,46,52,54,57,32,49,50,53,46,57,55,44,52,57,46,52,54,57,32,49,50,54,46,48,57,44,52,57,46,54,54,32,49,50,54,
46,50,57,44,52,57,46,57,49,32,49,50,54,46,52,49,44,53,48,46,49,54,52,32,49,50,54,46,53,52,44,53,48,46,52,49,52,32,49,50,54,46,54,44,53,48,46,53,51,57,32,34,10,32,32,32,105,100,61,34,112,111,108,121,108,
105,110,101,50,51,34,10,32,32,32,115,116,121,108,101,61,34,115,116,114,111,107,101,45,119,105,100,116,104,58,48,46,52,55,50,52,50,57,57,57,59,115,116,114,111,107,101,45,108,105,110,101,106,111,105,110,
58,98,101,118,101,108,34,32,47,62,10,60,112,111,108,121,108,105,110,101,10,32,32,32,112,111,105,110,116,115,61,34,49,51,53,46,54,55,44,53,50,46,48,53,49,32,49,51,53,46,55,51,44,53,50,46,49,56,32,49,51,
53,46,56,44,53,50,46,51,54,55,32,49,51,53,46,57,50,44,53,50,46,54,49,55,32,49,51,54,46,48,53,44,53,50,46,56,55,49,32,49,51,54,46,49,56,44,53,51,46,48,53,57,32,49,51,54,46,51,44,53,51,46,48,53,57,32,49,
51,54,46,52,51,44,53,50,46,56,55,49,32,49,51,54,46,53,53,44,53,50,46,51,48,53,32,49,51,54,46,53,53,44,53,49,46,55,51,56,32,49,51,54,46,54,49,44,53,49,46,49,55,50,32,49,51,54,46,54,49,44,53,48,46,54,54,
56,32,49,51,54,46,53,53,44,53,48,46,48,57,56,32,49,51,54,46,52,57,44,52,57,46,53,51,49,32,49,51,54,46,51,54,44,52,57,46,51,52,52,32,49,51,54,46,50,52,44,52,57,46,51,52,52,32,49,51,54,46,48,53,44,52,57,
46,53,51,49,32,49,51,53,46,57,50,44,52,57,46,55,56,53,32,49,51,53,46,56,44,53,48,46,48,51,53,32,49,51,53,46,54,55,44,53,48,46,50,50,55,32,49,51,53,46,54,44,53,48,46,51,53,50,32,34,10,32,32,32,105,100,
61,34,112,111,108,121,108,105,110,101,50,53,34,10,32,32,32,115,116,121,108,101,61,34,115,116,114,111,107,101,45,119,105,100,116,104,58,48,46,52,55,50,52,50,57,57,57,59,115,116,114,111,107,101,45,108,105,
110,101,106,111,105,110,58,98,101,118,101,108,34,32,47,62,10,60,108,105,110,101,10,32,32,32,120,49,61,34,49,50,56,46,52,50,57,57,57,34,10,32,32,32,121,49,61,34,53,52,46,53,55,34,10,32,32,32,120,50,61,
34,49,50,57,46,54,50,34,10,32,32,32,121,50,61,34,53,53,46,48,49,50,48,48,49,34,10,32,32,32,105,100,61,34,108,105,110,101,50,55,34,10,32,32,32,115,116,121,108,101,61,34,115,116,114,111,107,101,45,119,105,
100,116,104,58,48,46,52,55,50,52,50,57,57,57,34,32,47,62,10,60,112,111,108,121,103,111,110,10,32,32,32,112,111,105,110,116,115,61,34,52,48,46,52,51,44,53,49,46,56,48,49,32,52,49,46,54,50,53,44,53,51,46,
52,51,56,32,52,51,46,48,55,52,44,53,52,46,57,52,57,32,52,52,46,56,52,44,53,54,46,50,49,49,32,52,54,46,55,57,51,44,53,55,46,49,53,50,32,52,56,46,57,51,52,44,53,55,46,55,56,53,32,53,49,46,49,57,57,44,53,
55,46,57,55,51,32,53,51,46,52,48,54,44,53,55,46,56,52,56,32,53,53,46,52,56,52,44,53,55,46,50,56,49,32,53,55,46,52,51,56,44,53,54,46,51,51,54,32,53,57,46,49,51,55,44,53,53,46,48,55,52,32,54,48,46,53,50,
51,44,53,51,46,53,54,50,32,54,49,46,53,51,49,44,53,49,46,56,48,49,32,54,50,46,49,54,44,52,57,46,57,49,32,54,50,46,52,49,52,44,52,55,46,56,57,53,32,54,50,46,50,56,53,44,52,53,46,57,52,49,32,54,49,46,55,
56,49,44,52,52,46,48,53,49,32,54,48,46,56,52,44,52,50,46,50,56,57,32,53,57,46,53,55,56,44,52,48,46,55,49,53,32,53,56,46,49,50,57,44,51,57,46,51,57,49,32,53,54,46,54,49,55,44,51,56,46,50,53,56,32,53,52,
46,57,56,44,51,55,46,50,53,32,53,51,46,51,52,52,44,51,54,46,52,51,32,53,49,46,54,52,49,44,51,53,46,56,48,49,32,52,57,46,57,52,49,44,51,53,46,51,53,57,32,52,56,46,50,51,56,44,51,53,46,48,52,51,32,52,54,
46,54,48,50,44,51,52,46,57,49,56,32,52,52,46,57,54,53,44,51,52,46,57,49,56,32,52,51,46,51,57,49,44,51,53,46,48,52,51,32,52,49,46,56,55,57,44,51,53,46,50,57,55,32,52,48,46,52,51,44,51,53,46,56,48,49,32,
51,57,46,49,48,53,44,51,54,46,51,54,55,32,51,55,46,56,52,56,44,51,55,46,48,53,57,32,51,54,46,55,49,49,44,51,55,46,56,55,57,32,51,53,46,55,48,51,44,51,56,46,56,50,52,32,51,52,46,56,56,55,44,51,57,46,56,
57,53,32,51,52,46,50,53,56,44,52,49,46,48,57,32,51,51,46,56,49,54,44,52,50,46,51,53,50,32,51,51,46,53,54,50,44,52,51,46,54,48,57,32,51,51,46,54,56,56,44,52,52,46,57,57,54,32,51,52,46,48,54,54,44,52,54,
46,52,52,53,32,51,52,46,56,50,52,44,52,55,46,56,57,53,32,51,54,46,48,56,50,44,52,57,46,50,56,49,32,51,55,46,57,49,44,53,48,46,54,48,50,32,52,48,46,52,51,44,53,49,46,56,48,49,32,34,10,32,32,32,105,100,
61,34,112,111,108,121,103,111,110,50,57,34,10,32,32,32,115,116,121,108,101,61,34,115,116,114,111,107,101,45,119,105,100,116,104,58,48,46,52,55,50,52,50,57,57,57,59,115,116,114,111,107,101,45,100,97,115,
104,97,114,114,97,121,58,51,46,55,55,57,52,34,32,47,62,10,60,112,111,108,121,103,111,110,10,32,32,32,112,111,105,110,116,115,61,34,52,48,46,52,51,44,53,49,46,56,48,49,32,51,57,46,52,50,50,44,53,51,46,
57,52,49,32,51,56,46,55,50,55,44,53,54,46,53,50,51,32,51,56,46,52,49,52,44,53,57,46,51,53,57,32,51,56,46,54,48,50,44,54,50,46,50,53,56,32,51,57,46,50,51,44,54,53,46,50,49,57,32,52,48,46,52,51,44,54,55,
46,56,48,49,32,52,50,46,48,48,52,44,55,48,46,48,48,52,32,52,51,46,56,57,53,44,55,49,46,53,49,54,32,52,53,46,57,55,51,44,55,50,46,51,51,54,32,52,55,46,57,56,56,44,55,50,46,53,56,54,32,52,57,46,57,52,49,
44,55,50,46,50,48,55,32,53,49,46,55,54,54,44,55,49,46,51,57,49,32,53,51,46,52,48,54,44,55,48,46,51,50,32,53,52,46,55,56,57,44,54,56,46,56,55,49,32,53,53,46,56,54,51,44,54,55,46,50,51,52,32,53,54,46,54,
49,55,44,54,53,46,51,52,52,32,53,54,46,57,51,52,44,54,51,46,51,57,49,32,53,54,46,56,55,49,44,54,49,46,51,49,50,32,53,54,46,51,54,55,44,53,57,46,50,51,52,32,53,53,46,52,56,52,44,53,55,46,50,56,49,32,53,
52,46,50,50,51,44,53,53,46,53,49,54,32,53,50,46,54,52,56,44,53,51,46,57,52,49,32,53,48,46,56,50,52,44,53,50,46,54,56,52,32,52,56,46,56,48,57,44,53,49,46,56,48,49,32,52,54,46,54,54,52,44,53,49,46,50,51,
52,32,52,52,46,53,50,51,44,53,49,46,49,48,53,32,52,50,46,51,56,51,44,53,49,46,50,57,55,32,52,48,46,52,51,44,53,49,46,56,48,49,32,34,10,32,32,32,105,100,61,34,112,111,108,121,103,111,110,51,49,34,10,32,
32,32,115,116,121,108,101,61,34,115,116,114,111,107,101,45,119,105,100,116,104,58,48,46,52,55,50,52,50,57,57,57,59,115,116,114,111,107,101,45,100,97,115,104,97,114,114,97,121,58,51,46,55,55,57,52,34,32,
47,62,10,60,112,111,108,121,103,111,110,10,32,32,32,112,111,105,110,116,115,61,34,52,48,46,52,51,44,53,49,46,56,48,49,32,51,56,46,52,55,55,44,53,49,46,50,57,55,32,51,54,46,51,57,56,44,53,49,46,49,48,53,
32,51,52,46,50,53,56,44,53,49,46,50,51,52,32,51,50,46,49,49,51,44,53,49,46,56,48,49,32,51,48,46,48,57,56,44,53,50,46,54,56,52,32,50,56,46,50,55,51,44,53,51,46,57,52,49,32,50,54,46,54,51,51,44,53,53,46,
53,49,54,32,50,53,46,51,55,53,44,53,55,46,50,56,49,32,50,52,46,52,57,50,44,53,57,46,50,51,52,32,50,51,46,57,56,56,44,54,49,46,51,49,50,32,50,51,46,57,50,54,44,54,51,46,51,57,49,32,50,52,46,51,48,53,44,
54,53,46,51,52,52,32,50,53,46,48,53,57,44,54,55,46,50,51,52,32,50,54,46,49,50,57,44,54,56,46,56,55,49,32,50,55,46,53,49,54,44,55,48,46,51,50,32,50,57,46,48,57,44,55,49,46,51,57,49,32,51,48,46,57,49,56,
44,55,50,46,50,48,55,32,51,50,46,56,55,49,44,55,50,46,53,56,54,32,51,52,46,57,52,57,44,55,50,46,51,51,54,32,51,54,46,57,54,53,44,55,49,46,53,49,54,32,51,56,46,56,53,53,44,55,48,46,48,48,52,32,52,48,46,
52,51,44,54,55,46,56,48,49,32,52,49,46,54,50,53,44,54,53,46,50,49,57,32,52,50,46,50,53,56,44,54,50,46,50,53,56,32,52,50,46,52,52,53,44,53,57,46,51,53,57,32,52,50,46,49,50,57,44,53,54,46,53,50,51,32,52,
49,46,52,51,56,44,53,51,46,57,52,49,32,52,48,46,52,51,44,53,49,46,56,48,49,32,34,10,32,32,32,105,100,61,34,112,111,108,121,103,111,110,51,51,34,10,32,32,32,115,116,121,108,101,61,34,115,116,114,111,107,
101,45,119,105,100,116,104,58,48,46,52,55,50,52,50,57,57,57,59,115,116,114,111,107,101,45,100,97,115,104,97,114,114,97,121,58,51,46,55,55,57,52,34,32,47,62,10,60,112,111,108,121,103,111,110,10,32,32,32,
112,111,105,110,116,115,61,34,49,57,46,49,51,55,44,52,52,46,48,53,49,32,49,56,46,54,51,51,44,52,53,46,57,52,49,32,49,56,46,53,48,56,44,52,55,46,56,57,53,32,49,56,46,55,54,50,44,52,57,46,57,49,32,49,57,
46,51,57,49,44,53,49,46,56,48,49,32,50,48,46,51,57,56,44,53,51,46,53,54,50,32,50,49,46,55,56,53,44,53,53,46,48,55,52,32,50,51,46,52,50,50,44,53,54,46,51,51,54,32,50,53,46,51,55,53,44,53,55,46,50,56,49,
32,50,55,46,53,49,54,44,53,55,46,56,52,56,32,50,57,46,55,50,51,44,53,55,46,57,55,51,32,51,49,46,57,50,54,44,53,55,46,55,56,53,32,51,52,46,48,54,54,44,53,55,46,49,53,50,32,51,54,46,48,50,44,53,54,46,50,
49,49,32,51,55,46,55,56,53,44,53,52,46,57,52,57,32,51,57,46,50,57,55,44,53,51,46,52,51,56,32,52,48,46,52,51,44,53,49,46,56,48,49,32,52,50,46,57,52,57,44,53,48,46,54,48,50,32,52,52,46,55,55,55,44,52,57,
46,50,56,49,32,52,54,46,48,51,53,44,52,55,46,56,57,53,32,52,54,46,55,57,51,44,52,54,46,52,52,53,32,52,55,46,50,51,44,52,52,46,57,57,54,32,52,55,46,50,57,55,44,52,51,46,54,48,57,32,52,55,46,49,48,53,44,
52,50,46,51,53,50,32,52,54,46,54,54,52,44,52,49,46,48,57,32,52,53,46,57,55,51,44,51,57,46,56,57,53,32,52,53,46,49,53,50,44,51,56,46,56,50,52,32,52,52,46,49,52,53,44,51,55,46,56,55,57,32,52,51,46,48,49,
50,44,51,55,46,48,53,57,32,52,49,46,56,49,54,44,51,54,46,51,54,55,32,52,48,46,52,51,44,51,53,46,56,48,49,32,51,56,46,57,56,44,51,53,46,50,57,55,32,51,55,46,52,54,57,44,51,53,46,48,52,51,32,51,53,46,56,
57,53,44,51,52,46,57,49,56,32,51,52,46,51,50,44,51,52,46,57,49,56,32,51,50,46,54,49,55,44,51,53,46,48,52,51,32,51,48,46,57,49,56,44,51,53,46,51,53,57,32,50,57,46,50,56,49,44,51,53,46,56,48,49,32,50,55,
46,53,55,56,44,51,54,46,52,51,32,50,53,46,57,52,49,44,51,55,46,50,53,32,50,52,46,51,48,53,44,51,56,46,50,53,56,32,50,50,46,55,51,44,51,57,46,51,57,49,32,50,49,46,50,56,49,44,52,48,46,55,49,53,32,50,48,
46,48,50,44,52,50,46,50,56,57,32,49,57,46,49,51,55,44,52,52,46,48,53,49,32,34,10,32,32,32,105,100,61,34,112,111,108,121,103,111,110,51,53,34,10,32,32,32,115,116,121,108,101,61,34,115,116,114,111,107,101,
45,119,105,100,116,104,58,48,46,52,55,50,52,50,57,57,57,59,115,116,114,111,107,101,45,100,97,115,104,97,114,114,97,121,58,51,46,55,55,57,52,34,32,47,62,10,60,112,111,108,121,103,111,110,10,32,32,32,112,
111,105,110,116,115,61,34,48,46,55,52,54,48,57,44,48,46,55,55,55,51,52,32,56,48,46,49,49,51,44,48,46,55,55,55,51,52,32,56,48,46,49,49,51,44,49,48,50,46,56,50,32,48,46,55,52,54,48,57,44,49,48,50,46,56,
50,32,48,46,55,52,54,48,57,44,48,46,55,55,55,51,52,32,34,10,32,32,32,105,100,61,34,112,111,108,121,103,111,110,51,55,34,10,32,32,32,115,116,121,108,101,61,34,115,116,114,111,107,101,45,119,105,100,116,
104,58,48,46,52,55,50,52,50,57,57,57,34,32,47,62,10,60,108,105,110,101,10,32,32,32,120,49,61,34,50,50,46,50,56,57,34,10,32,32,32,121,49,61,34,56,51,46,50,51,48,48,48,51,34,10,32,32,32,120,50,61,34,50,
52,46,53,53,53,34,10,32,32,32,121,50,61,34,55,57,46,50,54,50,48,48,49,34,10,32,32,32,105,100,61,34,108,105,110,101,51,57,34,10,32,32,32,115,116,121,108,101,61,34,115,116,114,111,107,101,45,119,105,100,
116,104,58,48,46,52,55,50,52,50,57,57,57,34,32,47,62,10,60,108,105,110,101,10,32,32,32,120,49,61,34,50,49,46,52,54,57,34,10,32,32,32,121,49,61,34,56,48,46,48,56,50,48,48,49,34,10,32,32,32,120,50,61,34,
50,53,46,52,51,56,34,10,32,32,32,121,50,61,34,56,50,46,51,53,49,57,57,55,34,10,32,32,32,105,100,61,34,108,105,110,101,52,49,34,10,32,32,32,115,116,121,108,101,61,34,115,116,114,111,107,101,45,119,105,
100,116,104,58,48,46,52,55,50,52,50,57,57,57,34,32,47,62,10,60,108,105,110,101,10,32,32,32,120,49,61,34,53,56,46,53,55,34,10,32,32,32,121,49,61,34,56,51,46,50,51,48,48,48,51,34,10,32,32,32,120,50,61,34,
53,54,46,51,48,48,57,57,57,34,10,32,32,32,121,50,61,34,55,57,46,50,54,50,48,48,49,34,10,32,32,32,105,100,61,34,108,105,110,101,52,51,34,10,32,32,32,115,116,121,108,101,61,34,115,116,114,111,107,101,45,
119,105,100,116,104,58,48,46,52,55,50,52,50,57,57,57,34,32,47,62,10,60,108,105,110,101,10,32,32,32,120,49,61,34,53,53,46,52,56,52,48,48,49,34,10,32,32,32,121,49,61,34,56,50,46,51,53,49,57,57,55,34,10,
32,32,32,120,50,61,34,53,57,46,51,57,48,57,57,57,34,10,32,32,32,121,50,61,34,56,48,46,48,56,50,48,48,49,34,10,32,32,32,105,100,61,34,108,105,110,101,52,53,34,10,32,32,32,115,116,121,108,101,61,34,115,
116,114,111,107,101,45,119,105,100,116,104,58,48,46,52,55,50,52,50,57,57,57,34,32,47,62,10,60,112,111,108,121,108,105,110,101,10,32,32,32,112,111,105,110,116,115,61,34,49,48,56,46,52,54,44,52,49,46,49,
53,54,32,49,49,49,46,51,54,44,51,57,46,55,55,32,49,48,56,46,50,55,44,52,56,46,50,55,51,32,49,48,54,46,56,56,44,52,53,46,51,55,53,32,49,48,56,46,52,54,44,52,49,46,49,53,54,32,49,48,53,46,50,53,44,51,57,
46,57,53,55,32,49,48,51,46,55,51,44,52,52,46,50,52,50,32,49,48,54,46,56,56,44,52,53,46,51,55,53,32,34,10,32,32,32,105,100,61,34,112,111,108,121,108,105,110,101,52,55,34,10,32,32,32,115,116,121,108,101,
61,34,115,116,114,111,107,101,45,119,105,100,116,104,58,48,46,52,55,50,52,50,57,57,57,34,32,47,62,10,60,112,111,108,121,108,105,110,101,10,32,32,32,112,111,105,110,116,115,61,34,49,49,54,46,55,49,44,55,
50,46,50,55,51,32,49,49,53,46,56,51,44,54,57,46,49,56,52,32,49,50,51,46,55,44,55,51,46,54,53,54,32,49,50,48,46,54,50,44,55,52,46,53,51,57,32,49,49,54,46,55,49,44,55,50,46,50,55,51,32,49,49,53,46,48,49,
44,55,53,46,49,54,56,32,49,49,56,46,57,49,44,55,55,46,52,51,56,32,49,50,48,46,54,50,44,55,52,46,53,51,57,32,34,10,32,32,32,105,100,61,34,112,111,108,121,108,105,110,101,52,57,34,10,32,32,32,115,116,121,
108,101,61,34,115,116,114,111,107,101,45,119,105,100,116,104,58,48,46,52,55,50,52,50,57,57,57,34,32,47,62,10,60,112,111,108,121,108,105,110,101,10,32,32,32,112,111,105,110,116,115,61,34,49,52,49,46,54,
53,44,55,52,46,53,51,57,32,49,51,56,46,53,44,55,51,46,54,53,54,32,49,52,54,46,51,56,44,54,57,46,49,56,52,32,49,52,53,46,53,54,44,55,50,46,50,55,51,32,49,52,49,46,54,53,44,55,52,46,53,51,57,32,49,52,51,
46,51,53,44,55,55,46,52,51,56,32,49,52,55,46,50,54,44,55,53,46,49,54,56,32,49,52,53,46,53,54,44,55,50,46,50,55,51,32,34,10,32,32,32,105,100,61,34,112,111,108,121,108,105,110,101,53,49,34,10,32,32,32,115,
116,121,108,101,61,34,115,116,114,111,107,101,45,119,105,100,116,104,58,48,46,52,55,50,52,50,57,57,57,34,32,47,62,10,60,112,111,108,121,108,105,110,101,10,32,32,32,112,111,105,110,116,115,61,34,49,53,
53,46,51,50,44,52,53,46,51,55,53,32,49,53,51,46,57,52,44,52,56,46,50,55,51,32,49,53,48,46,56,53,44,51,57,46,55,55,32,49,53,51,46,56,49,44,52,49,46,49,53,54,32,49,53,53,46,51,50,44,52,53,46,51,55,53,32,
49,53,56,46,53,52,44,52,52,46,50,52,50,32,49,53,54,46,57,54,44,51,57,46,57,53,55,32,49,53,51,46,56,49,44,52,49,46,49,53,54,32,34,10,32,32,32,105,100,61,34,112,111,108,121,108,105,110,101,53,51,34,10,32,
32,32,115,116,121,108,101,61,34,115,116,114,111,107,101,45,119,105,100,116,104,58,48,46,52,55,50,52,50,57,57,57,34,32,47,62,10,60,112,111,108,121,103,111,110,10,32,32,32,112,111,105,110,116,115,61,34,
57,49,46,52,52,57,44,48,46,55,55,55,51,52,32,49,55,48,46,56,50,44,48,46,55,55,55,51,52,32,49,55,48,46,56,50,44,49,48,50,46,56,50,32,57,49,46,52,52,57,44,49,48,50,46,56,50,32,57,49,46,52,52,57,44,48,46,
55,55,55,51,52,32,34,10,32,32,32,105,100,61,34,112,111,108,121,103,111,110,53,53,34,10,32,32,32,115,116,121,108,101,61,34,115,116,114,111,107,101,45,119,105,100,116,104,58,48,46,52,55,50,52,50,57,57,57,
34,32,47,62,10,60,116,101,120,116,10,32,32,32,116,114,97,110,115,102,111,114,109,61,34,109,97,116,114,105,120,40,48,46,52,55,50,52,50,44,48,44,48,44,45,48,46,52,55,50,52,50,44,49,52,46,51,50,54,44,49,
51,46,50,53,41,34,10,32,32,32,102,111,110,116,45,115,105,122,101,61,34,50,48,112,120,34,10,32,32,32,105,100,61,34,116,101,120,116,53,55,34,10,32,32,32,115,116,121,108,101,61,34,102,111,110,116,45,115,
105,122,101,58,50,48,112,120,59,102,105,108,108,58,35,48,48,48,48,48,48,59,115,116,114,111,107,101,58,110,111,110,101,59,102,111,110,116,45,102,97,109,105,108,121,58,39,84,105,109,101,115,45,82,111,109,
97,110,44,84,105,109,101,115,44,115,101,114,105,102,39,34,62,86,105,114,116,117,97,108,32,82,111,111,109,60,47,116,101,120,116,62,10,10,10,60,116,101,120,116,10,32,32,32,116,114,97,110,115,102,111,114,
109,61,34,109,97,116,114,105,120,40,48,46,52,55,50,52,50,44,48,44,48,44,45,48,46,52,55,50,52,50,44,49,48,50,46,52,49,44,49,51,46,50,53,41,34,10,32,32,32,102,111,110,116,45,115,105,122,101,61,34,50,48,
112,120,34,10,32,32,32,105,100,61,34,116,101,120,116,53,57,34,10,32,32,32,115,116,121,108,101,61,34,102,111,110,116,45,115,105,122,101,58,50,48,112,120,59,102,105,108,108,58,35,48,48,48,48,48,48,59,115,
116,114,111,107,101,58,110,111,110,101,59,102,111,110,116,45,102,97,109,105,108,121,58,39,84,105,109,101,115,45,82,111,109,97,110,44,84,105,109,101,115,44,115,101,114,105,102,39,34,62,80,104,121,115,105,
99,97,108,32,82,111,111,109,60,47,116,101,120,116,62,10,10,10,60,112,111,108,121,108,105,110,101,10,32,32,32,112,111,105,110,116,115,61,34,51,55,46,50,49,53,44,53,48,46,57,56,32,51,55,46,50,56,49,44,53,
49,46,48,52,51,32,51,55,46,52,54,57,44,53,49,46,49,55,50,32,51,55,46,55,56,53,44,53,49,46,50,57,55,32,51,56,46,50,50,51,44,53,49,46,52,56,52,32,51,56,46,55,57,51,44,53,49,46,55,51,56,32,51,57,46,53,52,
55,44,53,49,46,57,50,54,32,52,48,46,53,53,53,44,53,50,46,49,56,32,52,49,46,57,52,49,44,53,50,46,52,51,32,52,51,46,55,55,44,53,50,46,54,56,52,32,52,53,46,50,49,53,44,53,50,46,56,48,57,32,52,54,46,53,51,
57,44,53,50,46,57,51,52,32,52,55,46,53,52,55,44,53,51,46,48,53,57,32,52,56,46,51,48,53,44,53,51,46,49,50,49,32,52,56,46,54,56,44,53,51,46,49,50,49,32,52,56,46,57,51,52,44,53,51,46,49,50,49,32,52,57,46,
49,50,49,44,53,51,46,49,50,49,32,52,57,46,50,52,54,44,53,51,46,49,50,49,32,52,57,46,54,50,53,44,53,51,46,49,50,49,32,53,48,46,49,57,49,44,53,51,46,49,56,56,32,53,49,46,49,57,57,44,53,51,46,49,56,56,32,
53,50,46,55,55,51,44,53,51,46,50,53,32,53,52,46,56,53,53,44,53,51,46,50,53,32,53,55,46,51,55,53,44,53,51,46,51,49,50,32,53,57,46,53,49,54,44,53,51,46,51,49,50,32,54,49,46,53,51,49,44,53,51,46,51,55,53,
32,54,51,46,52,50,50,44,53,51,46,51,55,53,32,54,52,46,57,57,54,44,53,51,46,52,51,56,32,54,54,46,51,49,54,44,53,51,46,52,51,56,32,54,55,46,51,57,49,44,53,51,46,52,51,56,32,54,56,46,50,48,55,44,53,51,46,
53,32,54,56,46,57,54,53,44,53,51,46,53,32,54,57,46,54,53,54,44,53,51,46,53,54,50,32,55,48,46,50,56,53,44,53,51,46,53,54,50,32,55,49,46,48,52,51,44,53,51,46,54,50,53,32,55,49,46,56,53,57,44,53,51,46,54,
50,53,32,55,50,46,57,51,52,44,53,51,46,54,50,53,32,55,52,46,50,53,52,44,53,51,46,53,54,50,32,55,53,46,55,54,54,44,53,51,46,53,54,50,32,55,55,46,53,57,52,44,53,51,46,53,32,55,57,46,53,52,55,44,53,51,46,
51,55,53,32,56,49,46,54,50,53,44,53,51,46,50,53,32,56,52,46,51,57,53,44,53,50,46,57,57,54,32,56,54,46,52,55,55,44,53,50,46,56,48,57,32,56,55,46,56,53,57,44,53,50,46,54,49,55,32,56,56,46,54,49,55,44,53,
50,46,53,53,53,32,56,56,46,57,57,54,44,53,50,46,53,53,53,32,56,57,46,49,50,49,44,53,50,46,54,49,55,32,56,57,46,49,56,52,44,53,50,46,53,53,53,32,56,57,46,52,51,52,44,53,50,46,52,57,50,32,56,57,46,57,51,
56,44,53,50,46,51,54,55,32,57,48,46,56,50,44,53,49,46,57,56,56,32,57,50,46,48,56,50,44,53,49,46,52,50,50,32,57,51,46,53,57,52,44,53,48,46,54,48,50,32,57,52,46,57,56,44,52,57,46,54,54,32,57,54,46,48,53,
49,44,52,56,46,55,55,55,32,57,54,46,55,52,50,44,52,56,46,48,50,32,57,55,46,49,50,49,44,52,55,46,51,57,49,32,57,55,46,50,52,54,44,52,54,46,56,56,55,32,57,55,46,51,48,57,44,52,54,46,51,56,51,32,57,55,46,
51,48,57,44,52,53,46,57,52,49,32,57,55,46,52,51,52,44,52,53,46,52,51,56,32,57,55,46,54,56,56,44,52,52,46,56,55,49,32,57,56,46,49,57,49,44,52,52,46,49,56,32,57,56,46,56,56,51,44,52,51,46,51,53,57,32,57,
57,46,55,54,54,44,52,50,46,54,48,50,32,49,48,48,46,53,50,44,52,50,46,48,57,56,32,49,48,49,46,49,53,44,52,49,46,55,50,51,32,49,48,49,46,55,50,44,52,49,46,53,51,49,32,49,48,50,46,50,50,44,52,49,46,52,48,
54,32,49,48,50,46,54,44,52,49,46,52,48,54,32,49,48,50,46,57,56,44,52,49,46,52,54,57,32,49,48,51,46,50,57,44,52,49,46,53,57,52,32,49,48,51,46,54,49,44,52,49,46,55,50,51,32,49,48,51,46,56,54,44,52,49,46,
57,49,32,49,48,52,46,48,53,44,52,50,46,48,51,53,32,49,48,52,46,49,56,44,52,50,46,48,57,56,32,49,48,52,46,50,52,44,52,50,46,49,54,52,32,49,48,52,46,51,44,52,50,46,50,50,55,32,34,10,32,32,32,105,100,61,
34,112,111,108,121,108,105,110,101,54,49,34,10,32,32,32,115,116,121,108,101,61,34,115,116,114,111,107,101,45,119,105,100,116,104,58,48,46,52,55,50,52,50,57,57,57,59,115,116,114,111,107,101,45,108,105,
110,101,106,111,105,110,58,98,101,118,101,108,34,32,47,62,10,60,112,111,108,121,108,105,110,101,10,32,32,32,112,111,105,110,116,115,61,34,52,50,46,49,50,57,44,53,52,46,54,57,57,32,52,50,46,48,54,54,44,
53,52,46,54,51,51,32,52,50,46,48,48,52,44,53,52,46,53,55,32,52,49,46,57,52,49,44,53,52,46,53,48,56,32,52,49,46,57,52,49,44,53,52,46,52,52,53,32,52,49,46,56,55,57,44,53,52,46,52,52,53,32,52,49,46,56,55,
57,44,53,52,46,51,56,51,32,52,49,46,56,55,57,44,53,52,46,51,50,32,52,49,46,56,49,54,44,53,52,46,50,53,56,32,52,49,46,56,49,54,44,53,52,46,49,57,53,32,52,49,46,56,49,54,44,53,52,46,49,50,57,32,52,49,46,
56,55,57,44,53,52,46,48,54,54,32,52,49,46,57,52,49,44,53,52,46,48,48,52,32,52,50,46,48,48,52,44,53,52,46,48,48,52,32,52,50,46,48,54,54,44,53,52,46,48,48,52,32,52,50,46,49,57,49,44,53,51,46,57,52,49,32,
52,50,46,51,50,44,53,51,46,57,52,49,32,52,50,46,53,48,56,44,53,51,46,57,52,49,32,52,50,46,54,57,53,44,53,51,46,57,52,49,32,52,50,46,57,52,57,44,53,51,46,57,52,49,32,52,51,46,49,57,57,44,53,52,46,48,48,
52,32,52,51,46,53,49,54,44,53,52,46,48,54,54,32,52,51,46,56,57,53,44,53,52,46,48,54,54,32,52,52,46,50,55,51,44,53,52,46,49,50,57,32,52,52,46,55,49,49,44,53,52,46,50,53,56,32,52,53,46,50,49,53,44,53,52,
46,51,50,32,52,53,46,55,56,53,44,53,52,46,52,52,53,32,52,55,46,49,48,53,44,53,52,46,55,54,50,32,52,56,46,52,51,44,53,53,46,48,49,50,32,52,57,46,53,54,50,44,53,53,46,51,50,56,32,53,48,46,53,48,56,44,53,
53,46,53,49,54,32,53,49,46,49,57,57,44,53,53,46,54,52,49,32,53,49,46,55,48,51,44,53,53,46,55,55,32,53,50,46,48,56,50,44,53,53,46,56,51,50,32,53,50,46,51,57,56,44,53,53,46,56,51,50,32,53,50,46,55,49,49,
44,53,53,46,56,57,53,32,53,51,46,49,53,50,44,53,54,46,48,50,32,53,51,46,56,52,56,44,53,54,46,50,49,49,32,53,52,46,55,56,57,44,53,54,46,52,54,49,32,53,54,46,49,49,51,44,53,54,46,56,52,32,53,55,46,56,55,
57,44,53,55,46,52,48,54,32,54,48,46,48,50,44,53,56,46,48,57,56,32,54,50,46,53,51,57,44,53,56,46,57,56,32,54,52,46,54,49,55,44,53,57,46,55,51,56,32,54,54,46,54,51,51,44,54,48,46,52,51,32,54,56,46,52,54,
49,44,54,49,46,49,50,49,32,54,57,46,57,55,51,44,54,49,46,54,50,53,32,55,49,46,50,51,44,54,50,46,48,54,54,32,55,50,46,49,55,54,44,54,50,46,51,56,51,32,55,50,46,57,51,52,44,54,50,46,54,51,51,32,55,51,46,
53,44,54,50,46,55,54,50,32,55,51,46,57,52,49,44,54,50,46,56,56,55,32,55,52,46,51,49,54,44,54,51,46,48,49,50,32,55,52,46,55,53,56,44,54,51,46,49,51,55,32,55,53,46,49,57,57,44,54,51,46,50,54,54,32,55,53,
46,56,50,56,44,54,51,46,52,53,51,32,55,54,46,53,56,54,44,54,51,46,55,55,32,55,55,46,54,53,54,44,54,52,46,50,49,49,32,55,57,46,48,52,51,44,54,52,46,56,52,32,56,48,46,55,52,50,44,54,53,46,54,53,54,32,56,
50,46,56,50,44,54,54,46,54,48,50,32,56,53,46,49,53,50,44,54,55,46,55,51,56,32,56,55,46,54,55,50,44,54,57,46,48,53,57,32,57,48,46,48,48,52,44,55,48,46,51,50,32,57,50,46,49,52,53,44,55,49,46,53,49,54,32,
57,52,46,48,51,53,44,55,50,46,54,52,56,32,57,53,46,54,55,50,44,55,51,46,55,49,57,32,57,54,46,57,57,54,44,55,52,46,54,48,50,32,57,56,46,48,48,52,44,55,53,46,52,50,50,32,57,56,46,56,50,44,55,54,46,49,55,
54,32,57,57,46,51,56,55,44,55,54,46,56,48,57,32,57,57,46,55,54,54,44,55,55,46,51,55,53,32,49,48,48,46,48,50,44,55,55,46,56,55,57,32,49,48,48,46,50,55,44,55,56,46,51,50,32,49,48,48,46,53,50,44,55,56,46,
56,50,52,32,49,48,48,46,55,55,44,55,57,46,51,50,56,32,49,48,49,46,50,49,44,55,57,46,56,51,50,32,49,48,49,46,55,56,44,56,48,46,51,57,56,32,49,48,50,46,54,44,56,49,46,48,50,55,32,49,48,51,46,54,55,44,56,
49,46,55,49,57,32,49,48,53,46,48,54,44,56,50,46,52,55,55,32,49,48,54,46,56,50,44,56,51,46,50,57,55,32,49,48,56,46,56,52,44,56,52,46,49,55,54,32,49,49,49,46,49,55,44,56,53,46,48,53,57,32,49,49,51,46,54,
57,44,56,53,46,56,49,54,32,49,49,54,46,52,54,44,56,54,46,53,48,56,32,49,49,57,46,49,49,44,56,55,46,48,55,52,32,49,50,49,46,53,44,56,55,46,52,53,51,32,49,50,51,46,54,52,44,56,55,46,55,48,51,32,49,50,53,
46,52,44,56,55,46,56,51,50,32,49,50,54,46,56,53,44,56,55,46,56,57,53,32,49,50,56,46,48,53,44,56,55,46,56,57,53,32,49,50,57,46,49,50,44,56,55,46,56,51,50,32,49,51,48,44,56,55,46,55,48,51,32,49,51,48,46,
56,50,44,56,55,46,53,55,56,32,49,51,49,46,53,55,44,56,55,46,52,53,51,32,49,51,50,46,52,44,56,55,46,50,54,50,32,49,51,51,46,51,52,44,56,55,46,48,55,52,32,49,51,52,46,51,53,44,56,54,46,56,56,55,32,49,51,
53,46,54,44,56,54,46,54,57,53,32,49,51,54,46,57,57,44,56,54,46,52,52,53,32,49,51,56,46,54,51,44,56,54,46,49,57,49,32,49,52,48,46,51,51,44,56,53,46,56,55,57,32,49,52,50,46,48,57,44,56,53,46,53,32,49,52,
51,46,56,44,56,53,46,48,53,57,32,49,52,53,46,49,50,44,56,52,46,54,49,55,32,49,52,54,46,49,57,44,56,52,46,49,49,51,32,49,52,54,46,57,53,44,56,51,46,53,52,55,32,49,52,55,46,53,55,44,56,51,46,48,52,51,32,
49,52,55,46,57,53,44,56,50,46,52,55,55,32,49,52,56,46,50,49,44,56,49,46,57,49,32,49,52,56,46,50,55,44,56,49,46,51,52,52,32,49,52,56,46,50,49,44,56,48,46,55,55,51,32,49,52,56,46,48,56,44,56,48,46,50,55,
32,49,52,55,46,56,51,44,55,57,46,55,48,51,32,49,52,55,46,53,55,44,55,57,46,49,51,55,32,49,52,55,46,50,54,44,55,56,46,54,51,51,32,49,52,54,46,56,56,44,55,56,46,49,50,57,32,49,52,54,46,53,55,44,55,55,46,
54,56,56,32,49,52,54,46,49,57,44,55,55,46,50,52,54,32,49,52,53,46,57,52,44,55,54,46,57,51,52,32,49,52,53,46,54,56,44,55,54,46,54,49,55,32,49,52,53,46,53,44,55,54,46,52,51,32,49,52,53,46,51,55,44,55,54,
46,51,48,53,32,49,52,53,46,51,49,44,55,54,46,50,51,56,32,49,52,53,46,50,53,44,55,54,46,49,55,54,32,34,10,32,32,32,105,100,61,34,112,111,108,121,108,105,110,101,54,51,34,10,32,32,32,115,116,121,108,101,
61,34,115,116,114,111,107,101,45,119,105,100,116,104,58,48,46,52,55,50,52,50,57,57,57,59,115,116,114,111,107,101,45,108,105,110,101,106,111,105,110,58,98,101,118,101,108,34,32,47,62,10,60,112,111,108,
121,108,105,110,101,10,32,32,32,112,111,105,110,116,115,61,34,51,56,46,56,53,53,44,53,52,46,56,50,52,32,51,56,46,56,53,53,44,53,52,46,55,54,50,32,51,56,46,56,53,53,44,53,52,46,54,57,57,32,51,56,46,56,
53,53,44,53,52,46,54,51,51,32,51,56,46,57,49,56,44,53,52,46,53,48,56,32,51,56,46,57,56,44,53,52,46,51,50,32,51,57,46,49,48,53,44,53,52,46,49,50,57,32,51,57,46,50,51,44,53,52,46,48,48,52,32,51,57,46,52,
50,50,44,53,51,46,56,49,54,32,51,57,46,55,51,52,44,53,51,46,54,57,49,32,52,48,46,49,49,51,44,53,51,46,53,54,50,32,52,48,46,54,56,44,53,51,46,52,51,56,32,52,49,46,53,54,50,44,53,51,46,51,49,50,32,52,50,
46,49,57,49,44,53,51,46,51,49,50,32,52,50,46,52,52,53,44,53,51,46,51,49,50,32,52,50,46,53,55,44,53,51,46,51,49,50,32,52,51,46,48,49,50,44,53,51,46,51,55,53,32,52,52,46,48,56,50,44,53,51,46,53,32,52,53,
46,57,55,51,44,53,51,46,54,57,49,32,52,55,46,52,50,50,44,53,51,46,56,55,57,32,52,56,46,55,52,50,44,53,52,46,48,48,52,32,52,57,46,54,56,56,44,53,52,46,49,50,57,32,53,48,46,51,50,44,53,52,46,49,57,53,32,
53,48,46,54,57,53,44,53,52,46,50,53,56,32,53,48,46,57,52,57,44,53,52,46,51,50,32,53,49,46,50,54,50,44,53,52,46,51,56,51,32,53,49,46,55,48,51,44,53,52,46,52,52,53,32,53,50,46,53,50,51,44,53,52,46,53,55,
32,53,51,46,56,52,56,44,53,52,46,54,57,57,32,53,53,46,55,51,52,44,53,53,46,48,49,50,32,53,56,46,48,54,54,44,53,53,46,51,50,56,32,53,57,46,57,53,55,44,53,53,46,53,55,56,32,54,49,46,54,53,54,44,53,53,46,
56,51,50,32,54,51,46,49,48,53,44,53,54,46,48,50,32,54,52,46,50,51,56,44,53,54,46,50,49,49,32,54,52,46,57,57,54,44,53,54,46,50,55,51,32,54,53,46,53,54,50,44,53,54,46,51,51,54,32,54,54,46,48,48,52,44,53,
54,46,51,57,56,32,54,54,46,51,49,54,44,53,54,46,51,57,56,32,54,54,46,54,51,51,44,53,54,46,52,54,49,32,54,55,46,48,55,52,44,53,54,46,53,50,51,32,54,55,46,55,48,51,44,53,54,46,53,56,54,32,54,56,46,53,56,
54,44,53,54,46,55,49,53,32,54,57,46,56,52,52,44,53,54,46,57,48,50,32,55,49,46,53,52,55,44,53,55,46,50,49,57,32,55,51,46,53,54,50,44,53,55,46,53,51,49,32,55,53,46,56,57,49,44,53,55,46,57,55,51,32,55,55,
46,57,55,51,44,53,56,46,51,53,50,32,55,57,46,57,50,54,44,53,56,46,55,51,32,56,49,46,53,54,50,44,53,56,46,57,56,32,56,50,46,57,52,57,44,53,57,46,49,54,56,32,56,52,46,48,50,44,53,57,46,50,57,55,32,56,52,
46,56,51,54,44,53,57,46,51,53,57,32,56,53,46,52,54,57,44,53,57,46,50,57,55,32,56,53,46,57,48,54,44,53,57,46,50,57,55,32,56,54,46,51,52,56,44,53,57,46,49,54,56,32,56,54,46,55,50,55,44,53,57,46,49,54,56,
32,56,55,46,49,54,56,44,53,57,46,49,48,53,32,56,55,46,55,51,52,44,53,57,46,49,54,56,32,56,56,46,53,53,53,44,53,57,46,50,57,55,32,56,57,46,53,54,50,44,53,57,46,53,52,55,32,57,48,46,56,50,44,53,57,46,57,
56,56,32,57,50,46,51,57,53,44,54,48,46,54,49,55,32,57,52,46,49,54,44,54,49,46,51,55,53,32,57,54,46,48,53,49,44,54,50,46,51,50,32,57,56,46,48,54,54,44,54,51,46,53,49,54,32,57,57,46,56,50,56,44,54,52,46,
55,49,53,32,49,48,49,46,50,49,44,54,53,46,56,52,56,32,49,48,50,46,50,57,44,54,54,46,55,57,51,32,49,48,50,46,57,56,44,54,55,46,54,55,50,32,49,48,51,46,52,50,44,54,56,46,51,54,55,32,49,48,51,46,55,51,44,
54,57,46,48,53,57,32,49,48,51,46,57,56,44,54,57,46,54,56,56,32,49,48,52,46,49,56,44,55,48,46,50,53,56,32,49,48,52,46,52,51,44,55,48,46,56,56,55,32,49,48,52,46,56,49,44,55,49,46,53,55,56,32,49,48,53,46,
51,49,44,55,50,46,51,57,56,32,49,48,54,46,49,51,44,55,51,46,51,52,52,32,49,48,55,46,49,52,44,55,52,46,50,56,57,32,49,48,56,46,51,57,44,55,53,46,51,53,57,32,49,48,57,46,55,50,44,55,54,46,51,48,53,32,49,
49,48,46,56,53,44,55,54,46,57,57,54,32,49,49,49,46,56,44,55,55,46,53,32,49,49,50,46,54,56,44,55,55,46,56,55,57,32,49,49,51,46,52,51,44,55,56,46,48,54,54,32,49,49,52,46,48,55,44,55,56,46,49,57,49,32,49,
49,52,46,53,55,44,55,56,46,49,57,49,32,49,49,53,46,48,49,44,55,56,46,48,54,54,32,49,49,53,46,52,53,44,55,55,46,57,52,49,32,49,49,53,46,55,55,44,55,55,46,55,53,32,49,49,54,46,48,56,44,55,55,46,53,32,49,
49,54,46,51,51,44,55,55,46,51,49,50,32,49,49,54,46,53,57,44,55,55,46,48,53,57,32,49,49,54,46,55,55,44,55,54,46,56,55,49,32,49,49,54,46,57,44,55,54,46,54,56,32,49,49,54,46,57,54,44,55,54,46,54,49,55,32,
49,49,55,46,48,50,44,55,54,46,52,57,50,32,34,10,32,32,32,105,100,61,34,112,111,108,121,108,105,110,101,54,53,34,10,32,32,32,115,116,121,108,101,61,34,115,116,114,111,107,101,45,119,105,100,116,104,58,
48,46,52,55,50,52,50,57,57,57,59,115,116,114,111,107,101,45,108,105,110,101,106,111,105,110,58,98,101,118,101,108,34,32,47,62,10,60,112,111,108,121,108,105,110,101,10,32,32,32,112,111,105,110,116,115,
61,34,52,51,46,55,48,51,44,53,48,46,57,56,32,52,51,46,54,52,49,44,53,49,46,48,52,51,32,52,51,46,53,55,56,44,53,49,46,49,48,53,32,52,51,46,53,49,54,44,53,49,46,49,48,53,32,52,51,46,53,49,54,44,53,49,46,
49,55,50,32,52,51,46,52,53,51,44,53,49,46,50,51,52,32,52,51,46,51,57,49,44,53,49,46,50,57,55,32,52,51,46,51,50,56,44,53,49,46,50,57,55,32,52,51,46,51,50,56,44,53,49,46,51,53,57,32,52,51,46,50,54,54,44,
53,49,46,52,50,50,32,52,51,46,50,54,54,44,53,49,46,52,56,52,32,52,51,46,50,54,54,44,53,49,46,53,52,55,32,52,51,46,50,54,54,44,53,49,46,54,48,57,32,52,51,46,51,50,56,44,53,49,46,54,55,54,32,52,51,46,51,
50,56,44,53,49,46,55,51,56,32,52,51,46,51,57,49,44,53,49,46,56,48,49,32,52,51,46,53,49,54,44,53,49,46,56,54,51,32,52,51,46,54,52,49,44,53,49,46,57,50,54,32,52,51,46,56,51,50,44,53,49,46,57,56,56,32,52,
52,46,48,50,44,53,50,46,48,53,49,32,52,52,46,55,49,49,44,53,50,46,49,56,32,52,53,46,50,49,53,44,53,50,46,50,52,50,32,52,53,46,52,54,57,44,53,50,46,51,48,53,32,52,53,46,53,57,52,44,53,50,46,51,48,53,32,
52,53,46,55,49,57,44,53,50,46,51,48,53,32,52,54,46,50,50,51,44,53,50,46,51,48,53,32,52,55,46,50,51,44,53,50,46,51,48,53,32,52,56,46,57,51,52,44,53,50,46,51,48,53,32,53,48,46,50,53,52,44,53,50,46,51,48,
53,32,53,49,46,52,53,51,44,53,50,46,51,48,53,32,53,50,46,50,55,44,53,50,46,51,48,53,32,53,50,46,56,52,44,53,50,46,51,48,53,32,53,51,46,48,57,44,53,50,46,51,48,53,32,53,51,46,50,55,55,44,53,50,46,51,48,
53,32,53,51,46,52,54,57,44,53,50,46,51,48,53,32,53,51,46,56,52,56,44,53,50,46,51,48,53,32,53,52,46,54,48,50,44,53,50,46,51,48,53,32,53,53,46,55,57,55,44,53,50,46,50,52,50,32,53,55,46,54,50,53,44,53,50,
46,49,56,32,53,57,46,56,57,53,44,53,50,46,48,53,49,32,54,49,46,55,56,49,44,53,49,46,57,50,54,32,54,51,46,52,56,52,44,53,49,46,56,54,51,32,54,52,46,57,57,54,44,53,49,46,56,48,49,32,54,54,46,49,57,49,44,
53,49,46,55,51,56,32,54,55,46,49,51,55,44,53,49,46,55,51,56,32,54,55,46,56,50,56,44,53,49,46,56,48,49,32,54,56,46,51,57,56,44,53,49,46,56,54,51,32,54,56,46,56,51,54,44,53,49,46,57,50,54,32,54,57,46,51,
52,44,53,49,46,57,56,56,32,54,57,46,56,52,52,44,53,50,46,48,53,49,32,55,48,46,54,48,50,44,53,50,46,48,53,49,32,55,49,46,54,48,57,44,53,49,46,57,50,54,32,55,50,46,56,54,55,44,53,49,46,56,48,49,32,55,52,
46,53,48,56,44,53,49,46,52,56,52,32,55,54,46,51,57,56,44,53,49,46,49,48,53,32,55,56,46,52,55,55,44,53,48,46,53,51,57,32,56,48,46,52,57,50,44,52,57,46,57,49,32,56,50,46,51,49,54,44,52,57,46,50,56,49,32,
56,51,46,55,54,54,44,52,56,46,55,55,55,32,56,52,46,56,57,56,44,52,56,46,51,51,54,32,56,53,46,54,53,54,44,52,56,46,48,56,50,32,56,54,46,50,50,51,44,52,55,46,56,57,53,32,56,54,46,54,48,50,44,52,55,46,55,
48,55,32,56,54,46,57,49,52,44,52,55,46,54,52,53,32,56,55,46,50,51,44,52,55,46,53,49,54,32,56,55,46,53,52,55,44,52,55,46,51,50,56,32,56,56,46,48,53,49,44,52,55,46,48,49,50,32,56,56,46,55,52,50,44,52,54,
46,53,55,32,56,57,46,54,50,53,44,52,53,46,56,55,57,32,57,48,46,55,53,56,44,52,52,46,57,57,54,32,57,50,46,48,56,50,44,52,51,46,56,54,51,32,57,51,46,52,54,53,44,52,50,46,52,55,55,32,57,52,46,54,48,50,44,
52,49,46,49,53,54,32,57,53,46,53,52,55,44,51,57,46,56,57,53,32,57,54,46,49,55,54,44,51,56,46,54,57,57,32,57,54,46,53,53,53,44,51,55,46,54,57,49,32,57,54,46,54,49,55,44,51,54,46,56,48,57,32,57,54,46,52,
50,54,44,51,54,46,48,53,49,32,57,54,46,49,49,51,44,51,53,46,51,53,57,32,57,53,46,54,55,50,44,51,52,46,55,57,51,32,57,53,46,49,54,56,44,51,52,46,50,50,55,32,57,52,46,54,54,52,44,51,51,46,55,50,51,32,57,
52,46,50,56,53,44,51,51,46,49,53,54,32,57,52,46,48,57,56,44,51,50,46,53,50,51,32,57,52,46,48,57,56,44,51,49,46,56,51,50,32,57,52,46,52,55,55,44,51,49,46,48,55,56,32,57,53,46,50,51,44,51,48,46,49,57,53,
32,57,54,46,52,57,50,44,50,57,46,50,53,32,57,56,46,50,53,52,44,50,56,46,51,54,55,32,49,48,48,46,53,50,44,50,55,46,52,56,52,32,49,48,50,46,52,55,44,50,54,46,57,56,32,49,48,52,46,52,51,44,50,54,46,53,51,
57,32,49,48,54,46,52,52,44,50,54,46,50,50,55,32,49,48,56,46,50,55,44,50,54,46,48,51,53,32,49,49,48,46,48,51,44,50,53,46,57,49,32,49,49,49,46,53,52,44,50,53,46,56,52,56,32,49,49,50,46,57,51,44,50,53,46,
56,52,56,32,49,49,52,46,49,57,44,50,53,46,57,49,32,49,49,53,46,51,50,44,50,54,46,48,51,53,32,49,49,54,46,51,51,44,50,54,46,49,54,52,32,49,49,55,46,50,56,44,50,54,46,50,56,57,32,49,49,56,46,50,50,44,50,
54,46,52,55,55,32,49,49,57,46,49,55,44,50,54,46,54,54,56,32,49,50,48,46,49,49,44,50,54,46,56,53,53,32,49,50,49,46,49,56,44,50,55,46,48,52,51,32,49,50,50,46,51,50,44,50,55,46,50,51,52,32,49,50,51,46,54,
52,44,50,55,46,51,53,57,32,49,50,53,46,49,53,44,50,55,46,53,53,49,32,49,50,54,46,55,57,44,50,55,46,55,51,56,32,49,50,56,46,54,56,44,50,55,46,56,54,51,32,49,51,48,46,55,54,44,50,55,46,57,56,56,32,49,51,
51,46,48,50,44,50,56,46,49,49,55,32,49,51,53,46,51,53,44,50,56,46,51,48,53,32,49,51,55,46,54,57,44,50,56,46,52,51,32,49,52,48,46,57,44,50,56,46,54,56,52,32,49,52,51,46,54,44,50,56,46,56,55,49,32,49,52,
53,46,54,56,44,50,57,46,48,54,50,32,49,52,55,46,50,44,50,57,46,49,56,56,32,49,52,56,46,50,49,44,50,57,46,50,53,32,49,52,56,46,55,55,44,50,57,46,50,53,32,49,52,57,46,48,57,44,50,57,46,50,53,32,49,52,57,
46,50,56,44,50,57,46,50,53,32,49,52,57,46,52,44,50,57,46,50,53,32,49,52,57,46,53,57,44,50,57,46,50,53,32,49,52,57,46,57,55,44,50,57,46,51,49,50,32,49,53,48,46,53,52,44,50,57,46,53,32,49,53,49,46,52,50,
44,50,57,46,54,57,49,32,49,53,50,46,53,53,44,51,48,46,48,55,32,49,53,52,44,51,48,46,53,48,56,32,49,53,53,46,52,53,44,51,49,46,48,55,56,32,49,53,54,46,57,44,51,49,46,55,55,32,49,53,56,46,48,51,44,51,50,
46,52,54,49,32,49,53,56,46,55,57,44,51,51,46,48,57,52,32,49,53,57,46,50,57,44,51,51,46,53,51,49,32,49,53,57,46,53,52,44,51,51,46,57,49,32,49,53,57,46,54,44,51,52,46,50,50,55,32,49,53,57,46,54,44,51,52,
46,52,55,55,32,49,53,57,46,53,52,44,51,52,46,55,51,32,49,53,57,46,53,52,44,51,53,46,48,52,51,32,49,53,57,46,54,44,51,53,46,52,50,50,32,49,53,57,46,54,55,44,51,53,46,57,50,54,32,49,53,57,46,56,54,44,51,
54,46,53,53,53,32,49,54,48,46,49,49,44,51,55,46,51,49,50,32,49,54,48,46,51,54,44,51,56,46,49,51,51,32,49,54,48,46,52,57,44,51,57,46,48,49,50,32,49,54,48,46,52,51,44,51,57,46,55,55,32,49,54,48,46,49,55,
44,52,48,46,51,51,54,32,49,53,57,46,57,50,44,52,48,46,56,52,32,49,53,57,46,53,52,44,52,49,46,50,49,57,32,49,53,57,46,49,54,44,52,49,46,53,51,49,32,49,53,56,46,55,57,44,52,49,46,56,52,56,32,49,53,56,46,
52,49,44,52,50,46,48,51,53,32,49,53,56,46,48,57,44,52,50,46,50,50,55,32,49,53,55,46,57,49,44,52,50,46,50,56,57,32,49,53,55,46,56,52,44,52,50,46,51,53,50,32,34,10,32,32,32,105,100,61,34,112,111,108,121,
108,105,110,101,54,55,34,10,32,32,32,115,116,121,108,101,61,34,115,116,114,111,107,101,45,119,105,100,116,104,58,48,46,52,55,50,52,50,57,57,57,59,115,116,114,111,107,101,45,108,105,110,101,106,111,105,
110,58,98,101,118,101,108,34,32,47,62,10,60,112,97,116,104,10,32,32,32,100,61,34,77,32,51,57,46,53,53,57,44,53,55,46,56,52,56,32,76,32,51,57,46,54,49,52,44,53,55,46,55,52,53,32,76,32,51,57,46,54,54,52,
44,53,55,46,54,52,49,32,76,32,51,57,46,55,48,56,44,53,55,46,53,51,54,32,76,32,51,57,46,55,52,55,44,53,55,46,52,51,32,76,32,51,57,46,55,55,57,44,53,55,46,51,50,50,32,76,32,51,57,46,56,48,55,44,53,55,46,
50,49,52,32,76,32,51,57,46,56,50,56,44,53,55,46,49,48,53,32,76,32,51,57,46,56,52,52,44,53,54,46,57,57,53,32,76,32,51,57,46,56,53,53,44,53,54,46,56,56,53,32,76,32,51,57,46,56,54,49,44,53,54,46,55,55,54,
32,76,32,51,57,46,56,54,49,44,53,54,46,54,54,54,32,76,32,51,57,46,56,53,53,44,53,54,46,53,53,55,32,76,32,51,57,46,56,52,53,44,53,54,46,52,52,56,32,76,32,51,57,46,56,50,57,44,53,54,46,51,52,32,76,32,51,
57,46,56,48,57,44,53,54,46,50,51,51,32,76,32,51,57,46,55,56,51,44,53,54,46,49,50,55,32,76,32,51,57,46,55,53,50,44,53,54,46,48,50,51,32,76,32,51,57,46,55,49,54,44,53,53,46,57,50,32,76,32,51,57,46,54,55,
54,44,53,53,46,56,49,57,32,76,32,51,57,46,54,51,44,53,53,46,55,49,57,32,76,32,51,57,46,53,56,44,53,53,46,54,50,50,32,76,32,51,57,46,53,50,53,44,53,53,46,53,50,55,32,76,32,51,57,46,52,54,53,44,53,53,46,
52,51,53,32,76,32,51,57,46,52,48,49,44,53,53,46,51,52,53,32,76,32,51,57,46,51,51,50,44,53,53,46,50,53,57,32,76,32,51,57,46,50,53,57,44,53,53,46,49,55,53,32,76,32,51,57,46,49,56,49,44,53,53,46,48,57,53,
32,76,32,51,57,46,48,57,57,44,53,53,46,48,49,56,32,76,32,51,57,46,48,49,50,44,53,52,46,57,52,53,32,76,32,51,56,46,57,50,49,44,53,52,46,56,55,54,32,76,32,51,56,46,56,50,54,44,53,52,46,56,49,49,32,76,32,
51,56,46,55,50,55,44,53,52,46,55,53,32,67,32,51,55,46,54,52,53,44,53,52,46,49,50,53,32,51,54,46,50,53,52,44,53,52,46,52,57,54,32,51,53,46,54,50,57,44,53,53,46,53,55,56,32,67,32,51,53,46,48,48,52,44,53,
54,46,54,54,32,51,53,46,51,55,57,44,53,56,46,48,53,49,32,51,54,46,52,54,49,44,53,56,46,54,55,54,32,67,32,51,55,46,53,52,51,44,53,57,46,51,48,49,32,51,56,46,57,51,52,44,53,56,46,57,51,32,51,57,46,53,53,
57,44,53,55,46,56,52,56,32,122,34,10,32,32,32,105,100,61,34,112,97,116,104,54,57,34,10,32,32,32,115,116,121,108,101,61,34,102,105,108,108,58,35,102,102,102,102,102,102,59,115,116,114,111,107,101,58,35,
102,102,102,102,102,102,59,115,116,114,111,107,101,45,119,105,100,116,104,58,48,59,115,116,114,111,107,101,45,108,105,110,101,106,111,105,110,58,98,101,118,101,108,34,32,47,62,10,60,112,97,116,104,10,
32,32,32,100,61,34,77,32,51,57,46,53,53,57,44,53,55,46,56,52,56,32,76,32,51,57,46,54,49,52,44,53,55,46,55,52,53,32,76,32,51,57,46,54,54,52,44,53,55,46,54,52,49,32,76,32,51,57,46,55,48,56,44,53,55,46,53,
51,54,32,76,32,51,57,46,55,52,55,44,53,55,46,52,51,32,76,32,51,57,46,55,55,57,44,53,55,46,51,50,50,32,76,32,51,57,46,56,48,55,44,53,55,46,50,49,52,32,76,32,51,57,46,56,50,56,44,53,55,46,49,48,53,32,76,
32,51,57,46,56,52,52,44,53,54,46,57,57,53,32,76,32,51,57,46,56,53,53,44,53,54,46,56,56,53,32,76,32,51,57,46,56,54,49,44,53,54,46,55,55,54,32,76,32,51,57,46,56,54,49,44,53,54,46,54,54,54,32,76,32,51,57,
46,56,53,53,44,53,54,46,53,53,55,32,76,32,51,57,46,56,52,53,44,53,54,46,52,52,56,32,76,32,51,57,46,56,50,57,44,53,54,46,51,52,32,76,32,51,57,46,56,48,57,44,53,54,46,50,51,51,32,76,32,51,57,46,55,56,51,
44,53,54,46,49,50,55,32,76,32,51,57,46,55,53,50,44,53,54,46,48,50,51,32,76,32,51,57,46,55,49,54,44,53,53,46,57,50,32,76,32,51,57,46,54,55,54,44,53,53,46,56,49,57,32,76,32,51,57,46,54,51,44,53,53,46,55,
49,57,32,76,32,51,57,46,53,56,44,53,53,46,54,50,50,32,76,32,51,57,46,53,50,53,44,53,53,46,53,50,55,32,76,32,51,57,46,52,54,53,44,53,53,46,52,51,53,32,76,32,51,57,46,52,48,49,44,53,53,46,51,52,53,32,76,
32,51,57,46,51,51,50,44,53,53,46,50,53,57,32,76,32,51,57,46,50,53,57,44,53,53,46,49,55,53,32,76,32,51,57,46,49,56,49,44,53,53,46,48,57,53,32,76,32,51,57,46,48,57,57,44,53,53,46,48,49,56,32,76,32,51,57,
46,48,49,50,44,53,52,46,57,52,53,32,76,32,51,56,46,57,50,49,44,53,52,46,56,55,54,32,76,32,51,56,46,56,50,54,44,53,52,46,56,49,49,32,76,32,51,56,46,55,50,55,44,53,52,46,55,53,32,67,32,51,55,46,54,52,53,
44,53,52,46,49,50,53,32,51,54,46,50,53,52,44,53,52,46,52,57,54,32,51,53,46,54,50,57,44,53,53,46,53,55,56,32,67,32,51,53,46,48,48,52,44,53,54,46,54,54,32,51,53,46,51,55,57,44,53,56,46,48,53,49,32,51,54,
46,52,54,49,44,53,56,46,54,55,54,32,67,32,51,55,46,53,52,51,44,53,57,46,51,48,49,32,51,56,46,57,51,52,44,53,56,46,57,51,32,51,57,46,53,53,57,44,53,55,46,56,52,56,32,122,34,10,32,32,32,105,100,61,34,112,
97,116,104,55,49,34,10,32,32,32,115,116,121,108,101,61,34,115,116,114,111,107,101,45,119,105,100,116,104,58,48,46,52,55,50,52,50,57,57,57,59,115,116,114,111,107,101,45,108,105,110,101,106,111,105,110,
58,98,101,118,101,108,34,32,47,62,10,60,112,97,116,104,10,32,32,32,100,61,34,77,32,52,53,46,50,50,55,44,53,53,46,53,55,56,32,76,32,52,53,46,49,54,54,44,53,53,46,52,55,57,32,76,32,52,53,46,49,48,49,44,
53,53,46,51,56,52,32,76,32,52,53,46,48,51,50,44,53,53,46,50,57,51,32,76,32,52,52,46,57,53,56,44,53,53,46,50,48,54,32,76,32,52,52,46,56,56,50,44,53,53,46,49,50,52,32,76,32,52,52,46,56,48,49,44,53,53,46,
48,52,54,32,76,32,52,52,46,55,49,56,44,53,52,46,57,55,51,32,76,32,52,52,46,54,51,49,44,53,52,46,57,48,52,32,76,32,52,52,46,53,52,49,44,53,52,46,56,52,32,76,32,52,52,46,52,52,57,44,53,52,46,55,56,49,32,
76,32,52,52,46,51,53,52,44,53,52,46,55,50,54,32,76,32,52,52,46,50,53,55,44,53,52,46,54,55,54,32,76,32,52,52,46,49,53,56,44,53,52,46,54,51,32,76,32,52,52,46,48,53,55,44,53,52,46,53,57,32,76,32,52,51,46,
57,53,52,44,53,52,46,53,53,52,32,76,32,52,51,46,56,52,57,44,53,52,46,53,50,52,32,76,32,52,51,46,55,52,51,44,53,52,46,52,57,56,32,76,32,52,51,46,54,51,54,44,53,52,46,52,55,56,32,76,32,52,51,46,53,50,56,
44,53,52,46,52,54,50,32,76,32,52,51,46,52,50,44,53,52,46,52,53,50,32,76,32,52,51,46,51,49,49,44,53,52,46,52,52,55,32,76,32,52,51,46,50,48,49,44,53,52,46,52,52,55,32,76,32,52,51,46,48,57,49,44,53,52,46,
52,53,51,32,76,32,52,50,46,57,56,49,44,53,52,46,52,54,52,32,76,32,52,50,46,56,55,50,44,53,52,46,52,56,32,76,32,52,50,46,55,54,51,44,53,52,46,53,48,50,32,76,32,52,50,46,54,53,53,44,53,52,46,53,50,57,32,
76,32,52,50,46,53,52,55,44,53,52,46,53,54,50,32,76,32,52,50,46,52,52,44,53,52,46,54,32,76,32,52,50,46,51,51,53,44,53,52,46,54,52,52,32,76,32,52,50,46,50,51,49,44,53,52,46,54,57,52,32,76,32,52,50,46,49,
50,57,44,53,52,46,55,53,32,67,32,52,49,46,48,52,55,44,53,53,46,51,55,53,32,52,48,46,54,55,54,44,53,54,46,55,54,54,32,52,49,46,51,48,49,44,53,55,46,56,52,56,32,67,32,52,49,46,57,50,54,44,53,56,46,57,51,
32,52,51,46,51,49,54,44,53,57,46,51,48,49,32,52,52,46,51,57,56,44,53,56,46,54,55,54,32,67,32,52,53,46,52,56,44,53,56,46,48,53,49,32,52,53,46,56,53,50,44,53,54,46,54,54,32,52,53,46,50,50,55,44,53,53,46,
53,55,56,32,122,34,10,32,32,32,105,100,61,34,112,97,116,104,55,51,34,10,32,32,32,115,116,121,108,101,61,34,102,105,108,108,58,35,102,102,102,102,102,102,59,115,116,114,111,107,101,58,35,102,102,102,102,
102,102,59,115,116,114,111,107,101,45,119,105,100,116,104,58,48,59,115,116,114,111,107,101,45,108,105,110,101,106,111,105,110,58,98,101,118,101,108,34,32,47,62,10,60,112,97,116,104,10,32,32,32,100,61,
34,77,32,52,53,46,50,50,55,44,53,53,46,53,55,56,32,76,32,52,53,46,49,54,54,44,53,53,46,52,55,57,32,76,32,52,53,46,49,48,49,44,53,53,46,51,56,52,32,76,32,52,53,46,48,51,50,44,53,53,46,50,57,51,32,76,32,
52,52,46,57,53,56,44,53,53,46,50,48,54,32,76,32,52,52,46,56,56,50,44,53,53,46,49,50,52,32,76,32,52,52,46,56,48,49,44,53,53,46,48,52,54,32,76,32,52,52,46,55,49,56,44,53,52,46,57,55,51,32,76,32,52,52,46,
54,51,49,44,53,52,46,57,48,52,32,76,32,52,52,46,53,52,49,44,53,52,46,56,52,32,76,32,52,52,46,52,52,57,44,53,52,46,55,56,49,32,76,32,52,52,46,51,53,52,44,53,52,46,55,50,54,32,76,32,52,52,46,50,53,55,44,
53,52,46,54,55,54,32,76,32,52,52,46,49,53,56,44,53,52,46,54,51,32,76,32,52,52,46,48,53,55,44,53,52,46,53,57,32,76,32,52,51,46,57,53,52,44,53,52,46,53,53,52,32,76,32,52,51,46,56,52,57,44,53,52,46,53,50,
52,32,76,32,52,51,46,55,52,51,44,53,52,46,52,57,56,32,76,32,52,51,46,54,51,54,44,53,52,46,52,55,56,32,76,32,52,51,46,53,50,56,44,53,52,46,52,54,50,32,76,32,52,51,46,52,50,44,53,52,46,52,53,50,32,76,32,
52,51,46,51,49,49,44,53,52,46,52,52,55,32,76,32,52,51,46,50,48,49,44,53,52,46,52,52,55,32,76,32,52,51,46,48,57,49,44,53,52,46,52,53,51,32,76,32,52,50,46,57,56,49,44,53,52,46,52,54,52,32,76,32,52,50,46,
56,55,50,44,53,52,46,52,56,32,76,32,52,50,46,55,54,51,44,53,52,46,53,48,50,32,76,32,52,50,46,54,53,53,44,53,52,46,53,50,57,32,76,32,52,50,46,53,52,55,44,53,52,46,53,54,50,32,76,32,52,50,46,52,52,44,53,
52,46,54,32,76,32,52,50,46,51,51,53,44,53,52,46,54,52,52,32,76,32,52,50,46,50,51,49,44,53,52,46,54,57,52,32,76,32,52,50,46,49,50,57,44,53,52,46,55,53,32,67,32,52,49,46,48,52,55,44,53,53,46,51,55,53,32,
52,48,46,54,55,54,44,53,54,46,55,54,54,32,52,49,46,51,48,49,44,53,55,46,56,52,56,32,67,32,52,49,46,57,50,54,44,53,56,46,57,51,32,52,51,46,51,49,54,44,53,57,46,51,48,49,32,52,52,46,51,57,56,44,53,56,46,
54,55,54,32,67,32,52,53,46,52,56,44,53,56,46,48,53,49,32,52,53,46,56,53,50,44,53,54,46,54,54,32,52,53,46,50,50,55,44,53,53,46,53,55,56,32,122,34,10,32,32,32,105,100,61,34,112,97,116,104,55,53,34,10,32,
32,32,115,116,121,108,101,61,34,115,116,114,111,107,101,45,119,105,100,116,104,58,48,46,52,55,50,52,50,57,57,57,59,115,116,114,111,107,101,45,108,105,110,101,106,111,105,110,58,98,101,118,101,108,34,32,
47,62,10,60,112,97,116,104,10,32,32,32,100,61,34,77,32,52,53,46,48,48,56,44,52,55,46,55,49,53,32,76,32,52,52,46,56,57,57,44,52,55,46,55,53,55,32,76,32,52,52,46,55,57,52,44,52,55,46,56,48,53,32,76,32,52,
52,46,54,57,51,44,52,55,46,56,53,55,32,76,32,52,52,46,53,57,53,44,52,55,46,57,49,52,32,76,32,52,52,46,53,44,52,55,46,57,55,53,32,76,32,52,52,46,52,49,44,52,56,46,48,52,49,32,76,32,52,52,46,51,50,51,44,
52,56,46,49,49,32,76,32,52,52,46,50,52,44,52,56,46,49,56,52,32,76,32,52,52,46,49,54,49,44,52,56,46,50,54,49,32,76,32,52,52,46,48,56,55,44,52,56,46,51,52,50,32,76,32,52,52,46,48,49,54,44,52,56,46,52,50,
53,32,76,32,52,51,46,57,53,44,52,56,46,53,49,50,32,76,32,52,51,46,56,56,56,44,52,56,46,54,48,50,32,76,32,52,51,46,56,51,49,44,52,56,46,54,57,53,32,76,32,52,51,46,55,55,56,44,52,56,46,55,57,32,76,32,52,
51,46,55,50,57,44,52,56,46,56,56,56,32,76,32,52,51,46,54,56,54,44,52,56,46,57,56,56,32,76,32,52,51,46,54,52,55,44,52,57,46,48,57,32,76,32,52,51,46,54,49,51,44,52,57,46,49,57,52,32,76,32,52,51,46,53,56,
52,44,52,57,46,50,57,57,32,76,32,52,51,46,53,54,44,52,57,46,52,48,54,32,76,32,52,51,46,53,52,49,44,52,57,46,53,49,52,32,76,32,52,51,46,53,50,56,44,52,57,46,54,50,51,32,76,32,52,51,46,53,49,57,44,52,57,
46,55,51,50,32,76,32,52,51,46,53,49,54,44,52,57,46,56,52,51,32,76,32,52,51,46,53,49,57,44,52,57,46,57,53,52,32,76,32,52,51,46,53,50,55,44,53,48,46,48,54,54,32,76,32,52,51,46,53,52,44,53,48,46,49,55,55,
32,76,32,52,51,46,53,53,57,44,53,48,46,50,56,57,32,76,32,52,51,46,53,56,52,44,53,48,46,52,32,76,32,52,51,46,54,49,53,44,53,48,46,53,49,49,32,76,32,52,51,46,54,53,50,44,53,48,46,54,50,49,32,67,32,52,52,
46,48,55,56,44,53,49,46,55,57,55,32,52,53,46,51,56,55,44,53,50,46,52,48,50,32,52,54,46,53,53,57,44,53,49,46,57,55,55,32,67,32,52,55,46,55,51,52,44,53,49,46,53,53,49,32,52,56,46,51,52,44,53,48,46,50,52,
54,32,52,55,46,57,49,52,44,52,57,46,48,55,32,67,32,52,55,46,52,56,56,44,52,55,46,56,57,56,32,52,54,46,49,56,44,52,55,46,50,56,57,32,52,53,46,48,48,56,44,52,55,46,55,49,53,32,122,34,10,32,32,32,105,100,
61,34,112,97,116,104,55,55,34,10,32,32,32,115,116,121,108,101,61,34,102,105,108,108,58,35,102,102,102,102,102,102,59,115,116,114,111,107,101,58,35,102,102,102,102,102,102,59,115,116,114,111,107,101,45,
119,105,100,116,104,58,48,59,115,116,114,111,107,101,45,108,105,110,101,106,111,105,110,58,98,101,118,101,108,34,32,47,62,10,60,112,97,116,104,10,32,32,32,100,61,34,77,32,52,53,46,48,48,56,44,52,55,46,
55,49,53,32,76,32,52,52,46,56,57,57,44,52,55,46,55,53,55,32,76,32,52,52,46,55,57,52,44,52,55,46,56,48,53,32,76,32,52,52,46,54,57,51,44,52,55,46,56,53,55,32,76,32,52,52,46,53,57,53,44,52,55,46,57,49,52,
32,76,32,52,52,46,53,44,52,55,46,57,55,53,32,76,32,52,52,46,52,49,44,52,56,46,48,52,49,32,76,32,52,52,46,51,50,51,44,52,56,46,49,49,32,76,32,52,52,46,50,52,44,52,56,46,49,56,52,32,76,32,52,52,46,49,54,
49,44,52,56,46,50,54,49,32,76,32,52,52,46,48,56,55,44,52,56,46,51,52,50,32,76,32,52,52,46,48,49,54,44,52,56,46,52,50,53,32,76,32,52,51,46,57,53,44,52,56,46,53,49,50,32,76,32,52,51,46,56,56,56,44,52,56,
46,54,48,50,32,76,32,52,51,46,56,51,49,44,52,56,46,54,57,53,32,76,32,52,51,46,55,55,56,44,52,56,46,55,57,32,76,32,52,51,46,55,50,57,44,52,56,46,56,56,56,32,76,32,52,51,46,54,56,54,44,52,56,46,57,56,56,
32,76,32,52,51,46,54,52,55,44,52,57,46,48,57,32,76,32,52,51,46,54,49,51,44,52,57,46,49,57,52,32,76,32,52,51,46,53,56,52,44,52,57,46,50,57,57,32,76,32,52,51,46,53,54,44,52,57,46,52,48,54,32,76,32,52,51,
46,53,52,49,44,52,57,46,53,49,52,32,76,32,52,51,46,53,50,56,44,52,57,46,54,50,51,32,76,32,52,51,46,53,49,57,44,52,57,46,55,51,50,32,76,32,52,51,46,53,49,54,44,52,57,46,56,52,51,32,76,32,52,51,46,53,49,
57,44,52,57,46,57,53,52,32,76,32,52,51,46,53,50,55,44,53,48,46,48,54,54,32,76,32,52,51,46,53,52,44,53,48,46,49,55,55,32,76,32,52,51,46,53,53,57,44,53,48,46,50,56,57,32,76,32,52,51,46,53,56,52,44,53,48,
46,52,32,76,32,52,51,46,54,49,53,44,53,48,46,53,49,49,32,76,32,52,51,46,54,53,50,44,53,48,46,54,50,49,32,67,32,52,52,46,48,55,56,44,53,49,46,55,57,55,32,52,53,46,51,56,55,44,53,50,46,52,48,50,32,52,54,
46,53,53,57,44,53,49,46,57,55,55,32,67,32,52,55,46,55,51,52,44,53,49,46,53,53,49,32,52,56,46,51,52,44,53,48,46,50,52,54,32,52,55,46,57,49,52,44,52,57,46,48,55,32,67,32,52,55,46,52,56,56,44,52,55,46,56,
57,56,32,52,54,46,49,56,44,52,55,46,50,56,57,32,52,53,46,48,48,56,44,52,55,46,55,49,53,32,122,34,10,32,32,32,105,100,61,34,112,97,116,104,55,57,34,10,32,32,32,115,116,121,108,101,61,34,115,116,114,111,
107,101,45,119,105,100,116,104,58,48,46,52,55,50,52,50,57,57,57,59,115,116,114,111,107,101,45,108,105,110,101,106,111,105,110,58,98,101,118,101,108,34,32,47,62,10,60,112,97,116,104,10,32,32,32,100,61,
34,77,32,51,52,46,51,54,51,44,53,49,46,57,55,55,32,76,32,51,52,46,52,55,52,44,53,50,46,48,49,52,32,76,32,51,52,46,53,56,52,44,53,50,46,48,52,52,32,76,32,51,52,46,54,57,54,44,53,50,46,48,55,32,76,32,51,
52,46,56,48,55,44,53,50,46,48,56,57,32,76,32,51,52,46,57,49,57,44,53,50,46,49,48,50,32,76,32,51,53,46,48,51,44,53,50,46,49,49,32,76,32,51,53,46,49,52,49,44,53,50,46,49,49,51,32,76,32,51,53,46,50,53,50,
44,53,50,46,49,49,32,76,32,51,53,46,51,54,50,44,53,50,46,49,48,49,32,76,32,51,53,46,52,55,49,44,53,50,46,48,56,56,32,76,32,51,53,46,53,55,57,44,53,50,46,48,54,57,32,76,32,51,53,46,54,56,54,44,53,50,46,
48,52,53,32,76,32,51,53,46,55,57,49,44,53,50,46,48,49,54,32,76,32,51,53,46,56,57,53,44,53,49,46,57,56,50,32,76,32,51,53,46,57,57,54,44,53,49,46,57,52,51,32,76,32,51,54,46,48,57,54,44,53,49,46,56,57,57,
32,76,32,51,54,46,49,57,52,44,53,49,46,56,53,49,32,76,32,51,54,46,50,56,57,44,53,49,46,55,57,56,32,76,32,51,54,46,51,56,50,44,53,49,46,55,52,49,32,76,32,51,54,46,52,55,50,44,53,49,46,54,55,57,32,76,32,
51,54,46,53,53,57,44,53,49,46,54,49,51,32,76,32,51,54,46,54,52,51,44,53,49,46,53,52,50,32,76,32,51,54,46,55,50,51,44,53,49,46,52,54,56,32,76,32,51,54,46,56,48,49,44,53,49,46,51,56,57,32,76,32,51,54,46,
56,55,52,44,53,49,46,51,48,54,32,76,32,51,54,46,57,52,52,44,53,49,46,50,49,57,32,76,32,51,55,46,48,48,57,44,53,49,46,49,50,57,32,76,32,51,55,46,48,55,44,53,49,46,48,51,52,32,76,32,51,55,46,49,50,55,44,
53,48,46,57,51,54,32,76,32,51,55,46,49,56,44,53,48,46,56,51,53,32,76,32,51,55,46,50,50,55,44,53,48,46,55,51,32,76,32,51,55,46,50,55,44,53,48,46,54,50,49,32,67,32,51,55,46,54,57,53,44,52,57,46,52,52,57,
32,51,55,46,48,56,54,44,52,56,46,49,52,49,32,51,53,46,57,49,52,44,52,55,46,55,49,53,32,67,32,51,52,46,55,51,56,44,52,55,46,50,56,57,32,51,51,46,52,51,52,44,52,55,46,56,57,56,32,51,51,46,48,48,56,44,52,
57,46,48,55,32,67,32,51,50,46,53,56,50,44,53,48,46,50,52,54,32,51,51,46,49,56,56,44,53,49,46,53,53,49,32,51,52,46,51,54,51,44,53,49,46,57,55,55,32,122,34,10,32,32,32,105,100,61,34,112,97,116,104,56,49,
34,10,32,32,32,115,116,121,108,101,61,34,102,105,108,108,58,35,102,102,102,102,102,102,59,115,116,114,111,107,101,58,35,102,102,102,102,102,102,59,115,116,114,111,107,101,45,119,105,100,116,104,58,48,
59,115,116,114,111,107,101,45,108,105,110,101,106,111,105,110,58,98,101,118,101,108,34,32,47,62,10,60,112,97,116,104,10,32,32,32,100,61,34,77,32,51,52,46,51,54,51,44,53,49,46,57,55,55,32,76,32,51,52,46,
52,55,52,44,53,50,46,48,49,52,32,76,32,51,52,46,53,56,52,44,53,50,46,48,52,52,32,76,32,51,52,46,54,57,54,44,53,50,46,48,55,32,76,32,51,52,46,56,48,55,44,53,50,46,48,56,57,32,76,32,51,52,46,57,49,57,44,
53,50,46,49,48,50,32,76,32,51,53,46,48,51,44,53,50,46,49,49,32,76,32,51,53,46,49,52,49,44,53,50,46,49,49,51,32,76,32,51,53,46,50,53,50,44,53,50,46,49,49,32,76,32,51,53,46,51,54,50,44,53,50,46,49,48,49,
32,76,32,51,53,46,52,55,49,44,53,50,46,48,56,56,32,76,32,51,53,46,53,55,57,44,53,50,46,48,54,57,32,76,32,51,53,46,54,56,54,44,53,50,46,48,52,53,32,76,32,51,53,46,55,57,49,44,53,50,46,48,49,54,32,76,32,
51,53,46,56,57,53,44,53,49,46,57,56,50,32,76,32,51,53,46,57,57,54,44,53,49,46,57,52,51,32,76,32,51,54,46,48,57,54,44,53,49,46,56,57,57,32,76,32,51,54,46,49,57,52,44,53,49,46,56,53,49,32,76,32,51,54,46,
50,56,57,44,53,49,46,55,57,56,32,76,32,51,54,46,51,56,50,44,53,49,46,55,52,49,32,76,32,51,54,46,52,55,50,44,53,49,46,54,55,57,32,76,32,51,54,46,53,53,57,44,53,49,46,54,49,51,32,76,32,51,54,46,54,52,51,
44,53,49,46,53,52,50,32,76,32,51,54,46,55,50,51,44,53,49,46,52,54,56,32,76,32,51,54,46,56,48,49,44,53,49,46,51,56,57,32,76,32,51,54,46,56,55,52,44,53,49,46,51,48,54,32,76,32,51,54,46,57,52,52,44,53,49,
46,50,49,57,32,76,32,51,55,46,48,48,57,44,53,49,46,49,50,57,32,76,32,51,55,46,48,55,44,53,49,46,48,51,52,32,76,32,51,55,46,49,50,55,44,53,48,46,57,51,54,32,76,32,51,55,46,49,56,44,53,48,46,56,51,53,32,
76,32,51,55,46,50,50,55,44,53,48,46,55,51,32,76,32,51,55,46,50,55,44,53,48,46,54,50,49,32,67,32,51,55,46,54,57,53,44,52,57,46,52,52,57,32,51,55,46,48,56,54,44,52,56,46,49,52,49,32,51,53,46,57,49,52,44,
52,55,46,55,49,53,32,67,32,51,52,46,55,51,56,44,52,55,46,50,56,57,32,51,51,46,52,51,52,44,52,55,46,56,57,56,32,51,51,46,48,48,56,44,52,57,46,48,55,32,67,32,51,50,46,53,56,50,44,53,48,46,50,52,54,32,51,
51,46,49,56,56,44,53,49,46,53,53,49,32,51,52,46,51,54,51,44,53,49,46,57,55,55,32,122,34,10,32,32,32,105,100,61,34,112,97,116,104,56,51,34,10,32,32,32,115,116,121,108,101,61,34,115,116,114,111,107,101,
45,119,105,100,116,104,58,48,46,52,55,50,52,50,57,57,57,59,115,116,114,111,107,101,45,108,105,110,101,106,111,105,110,58,98,101,118,101,108,34,32,47,62,10,60,108,105,110,101,10,32,32,32,120,49,61,34,51,
51,46,53,54,50,34,10,32,32,32,121,49,61,34,53,54,46,57,54,53,34,10,32,32,32,120,50,61,34,51,57,46,52,50,50,48,48,49,34,10,32,32,32,121,50,61,34,54,48,46,51,54,55,48,48,49,34,10,32,32,32,105,100,61,34,
108,105,110,101,56,53,34,10,32,32,32,115,116,121,108,101,61,34,115,116,114,111,107,101,45,119,105,100,116,104,58,48,46,52,55,50,52,50,57,57,57,34,32,47,62,10,60,108,105,110,101,10,32,32,32,120,49,61,34,
52,49,46,53,34,10,32,32,32,121,49,61,34,54,48,46,51,54,55,48,48,49,34,10,32,32,32,120,50,61,34,52,55,46,51,53,57,48,48,49,34,10,32,32,32,121,50,61,34,53,54,46,57,54,53,34,10,32,32,32,105,100,61,34,108,
105,110,101,56,55,34,10,32,32,32,115,116,121,108,101,61,34,115,116,114,111,107,101,45,119,105,100,116,104,58,48,46,52,55,50,52,50,57,57,57,34,32,47,62,10,60,108,105,110,101,10,32,32,32,120,49,61,34,52,
57,46,48,53,56,57,57,56,34,10,32,32,32,121,49,61,34,53,50,46,51,48,53,34,10,32,32,32,120,50,61,34,52,54,46,55,50,55,48,48,49,34,10,32,32,32,121,50,61,34,52,53,46,56,55,57,48,48,50,34,10,32,32,32,105,100,
61,34,108,105,110,101,56,57,34,10,32,32,32,115,116,121,108,101,61,34,115,116,114,111,107,101,45,119,105,100,116,104,58,48,46,52,55,50,52,50,57,57,57,34,32,47,62,10,60,108,105,110,101,10,32,32,32,120,49,
61,34,51,52,46,49,50,57,48,48,50,34,10,32,32,32,121,49,61,34,52,53,46,56,55,57,48,48,50,34,10,32,32,32,120,50,61,34,51,49,46,56,48,49,48,48,49,34,10,32,32,32,121,50,61,34,53,50,46,51,48,53,34,10,32,32,
32,105,100,61,34,108,105,110,101,57,49,34,10,32,32,32,115,116,121,108,101,61,34,115,116,114,111,107,101,45,119,105,100,116,104,58,48,46,52,55,50,52,50,57,57,57,34,32,47,62,10,60,47,103,62,60,47,115,118,
103,62,10,0,0};

const char* TabPreferences::directivity2_svg = (const char*) resource_TabPreferences_directivity2_svg;
const int TabPreferences::directivity2_svgSize = 24877;
