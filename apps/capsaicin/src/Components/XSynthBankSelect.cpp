/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  18 Jan 2010 11:32:34 am

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
//[/Headers]

#include "XSynthBankSelect.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
XSynthBankSelect::XSynthBankSelect (XSynthPlugin* plugin_, Master* master_)
    : plugin (plugin_),
      master (master_),
      nameGroup (0),
      authorGroup (0),
      commentGroup (0),
      commentsText (0),
      authorText (0),
      nameText (0),
      typeGroup (0),
      categoryBox (0),
      presetSelector (0),
      presetGroup (0)
{
    addAndMakeVisible (nameGroup = new GroupComponent (String::empty,
                                                       T("Patch Name")));
    nameGroup->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    nameGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (authorGroup = new GroupComponent (String::empty,
                                                         T("Author")));
    authorGroup->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    authorGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (commentGroup = new GroupComponent (T("new group"),
                                                          T("Comments")));
    commentGroup->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    commentGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (commentsText = new TextEditor (String::empty));
    commentsText->setMultiLine (true);
    commentsText->setReturnKeyStartsNewLine (true);
    commentsText->setReadOnly (false);
    commentsText->setScrollbarsShown (true);
    commentsText->setCaretVisible (false);
    commentsText->setPopupMenuEnabled (false);
    commentsText->setColour (TextEditor::textColourId, Colours::white);
    commentsText->setColour (TextEditor::backgroundColourId, Colours::black);
    commentsText->setColour (TextEditor::outlineColourId, Colour (0xc0ffffff));
    commentsText->setColour (TextEditor::shadowColourId, Colour (0x38000000));
    commentsText->setText (String::empty);

    addAndMakeVisible (authorText = new TextEditor (String::empty));
    authorText->setMultiLine (false);
    authorText->setReturnKeyStartsNewLine (false);
    authorText->setReadOnly (false);
    authorText->setScrollbarsShown (false);
    authorText->setCaretVisible (false);
    authorText->setPopupMenuEnabled (false);
    authorText->setColour (TextEditor::textColourId, Colours::white);
    authorText->setColour (TextEditor::backgroundColourId, Colours::black);
    authorText->setColour (TextEditor::outlineColourId, Colour (0xc0ffffff));
    authorText->setText (String::empty);

    addAndMakeVisible (nameText = new TextEditor (String::empty));
    nameText->setMultiLine (false);
    nameText->setReturnKeyStartsNewLine (false);
    nameText->setReadOnly (false);
    nameText->setScrollbarsShown (false);
    nameText->setCaretVisible (false);
    nameText->setPopupMenuEnabled (false);
    nameText->setColour (TextEditor::textColourId, Colours::white);
    nameText->setColour (TextEditor::backgroundColourId, Colours::black);
    nameText->setColour (TextEditor::outlineColourId, Colour (0xc0ffffff));
    nameText->setText (String::empty);

    addAndMakeVisible (typeGroup = new GroupComponent (String::empty,
                                                       T("Category")));
    typeGroup->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    typeGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (categoryBox = new ComboBox (String::empty));
    categoryBox->setEditableText (false);
    categoryBox->setJustificationType (Justification::centredLeft);
    categoryBox->setTextWhenNothingSelected (String::empty);
    categoryBox->setTextWhenNoChoicesAvailable (T("(no choices)"));
    categoryBox->addListener (this);

    addAndMakeVisible (presetSelector = new PresetSelectorComponent (plugin));

    addAndMakeVisible (presetGroup = new GroupComponent (String::empty,
                                                         T("Preset selector")));
    presetGroup->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    presetGroup->setColour (GroupComponent::textColourId, Colours::white);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (680, 400);

    //[Constructor] You can add your own custom stuff here..
    commentsText->setEnabled (false);
    authorText->setEnabled (false);
    nameText->setEnabled (false);
    categoryBox->setEnabled (false);

    presetSelector->setRowHeight (14);
    //[/Constructor]
}

XSynthBankSelect::~XSynthBankSelect()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (nameGroup);
    deleteAndZero (authorGroup);
    deleteAndZero (commentGroup);
    deleteAndZero (commentsText);
    deleteAndZero (authorText);
    deleteAndZero (nameText);
    deleteAndZero (typeGroup);
    deleteAndZero (categoryBox);
    deleteAndZero (presetSelector);
    deleteAndZero (presetGroup);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void XSynthBankSelect::paint (Graphics& g)
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

void XSynthBankSelect::resized()
{
    nameGroup->setBounds (460, 12, 215, 50);
    authorGroup->setBounds (460, 64, 215, 50);
    commentGroup->setBounds (460, 168, 215, 222);
    commentsText->setBounds (469, 185, 197, 197);
    authorText->setBounds (469, 83, 197, 20);
    nameText->setBounds (469, 31, 197, 20);
    typeGroup->setBounds (460, 116, 215, 50);
    categoryBox->setBounds (470, 135, 195, 20);
    presetSelector->setBounds (14, 31, 435, 351);
    presetGroup->setBounds (6, 12, 452, 378);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void XSynthBankSelect::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == categoryBox)
    {
        //[UserComboBoxCode_categoryBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_categoryBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void XSynthBankSelect::updatePresetSelector ()
{
    presetSelector->updateContent ();
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="XSynthBankSelect" componentName=""
                 parentClasses="public Component, public DragAndDropContainer"
                 constructorParams="XSynthPlugin* plugin_, Master* master_" variableInitialisers="plugin (plugin_)&#10;master (master_)"
                 snapPixels="10" snapActive="0" snapShown="0" overlayOpacity="0.330000013"
                 fixedSize="1" initialWidth="680" initialHeight="400">
  <BACKGROUND backgroundColour="ff827474">
    <RECT pos="0 370 680 30" fill="linear: 330 390, 330 410, 0=ff827474, 1=ff000000"
          hasStroke="0"/>
  </BACKGROUND>
  <GROUPCOMPONENT name="" id="95a857ca472148f3" memberName="nameGroup" virtualName=""
                  explicitFocusOrder="0" pos="460 12 215 50" outlinecol="66ffffff"
                  textcol="ffffffff" title="Patch Name"/>
  <GROUPCOMPONENT name="" id="c276e9e47147d40" memberName="authorGroup" virtualName=""
                  explicitFocusOrder="0" pos="460 64 215 50" outlinecol="66ffffff"
                  textcol="ffffffff" title="Author"/>
  <GROUPCOMPONENT name="new group" id="f360f1d8831cfa07" memberName="commentGroup"
                  virtualName="" explicitFocusOrder="0" pos="460 168 215 222" outlinecol="66ffffff"
                  textcol="ffffffff" title="Comments"/>
  <TEXTEDITOR name="" id="7da48ca683f74449" memberName="commentsText" virtualName=""
              explicitFocusOrder="0" pos="469 185 197 197" textcol="ffffffff"
              bkgcol="ff000000" outlinecol="c0ffffff" shadowcol="38000000"
              initialText="" multiline="1" retKeyStartsLine="1" readonly="0"
              scrollbars="1" caret="0" popupmenu="0"/>
  <TEXTEDITOR name="" id="6a1360a525d04d91" memberName="authorText" virtualName=""
              explicitFocusOrder="0" pos="469 83 197 20" textcol="ffffffff"
              bkgcol="ff000000" outlinecol="c0ffffff" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="0" caret="0" popupmenu="0"/>
  <TEXTEDITOR name="" id="f9ec1f8b62fca058" memberName="nameText" virtualName=""
              explicitFocusOrder="0" pos="469 31 197 20" textcol="ffffffff"
              bkgcol="ff000000" outlinecol="c0ffffff" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="0" caret="0" popupmenu="0"/>
  <GROUPCOMPONENT name="" id="6cadd972fb511b69" memberName="typeGroup" virtualName=""
                  explicitFocusOrder="0" pos="460 116 215 50" outlinecol="66ffffff"
                  textcol="ffffffff" title="Category"/>
  <COMBOBOX name="" id="3539fb7583b60548" memberName="categoryBox" virtualName=""
            explicitFocusOrder="0" pos="470 135 195 20" editable="0" layout="33"
            items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <GENERICCOMPONENT name="" id="b3ad5536382fd2d7" memberName="presetSelector" virtualName=""
                    explicitFocusOrder="0" pos="14 31 435 351" class="PresetSelectorComponent"
                    params="plugin"/>
  <GROUPCOMPONENT name="" id="da089d3314cb808c" memberName="presetGroup" virtualName=""
                  explicitFocusOrder="0" pos="6 12 452 378" outlinecol="66ffffff"
                  textcol="ffffffff" title="Preset selector"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
