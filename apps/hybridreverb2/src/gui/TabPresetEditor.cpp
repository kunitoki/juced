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
#include "../ParamCategory.h"
#include "../ParamImpulseResponses.h"
//[/Headers]

#include "TabPresetEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
TabPresetEditor::TabPresetEditor (MasterAndCommander *m)
    : master (m),
      presetManager(0),
      groupPresetSelection (0),
      textEditor (0),
      listBox (0),
      groupNotes (0),
      label (0),
      label2 (0),
      label3 (0),
      label4 (0),
      label5 (0),
      label6 (0),
      label7 (0),
      label8 (0),
      label9 (0),
      textButtonChooserLL (0),
      textEditorFileLL (0),
      textEditorFileLR (0),
      textEditorFileRL (0),
      textEditorFileRR (0),
      textButtonChooserLR (0),
      textButtonChooserRL (0),
      textButtonChooserRR (0),
      textEditorNotes (0),
      textEditorTag (0),
      textEditorCat1 (0),
      textEditorCat2 (0),
      textEditorCat3 (0),
      textEditorCat4 (0),
      textButtonSave (0),
      textButtonSaveAs (0),
      textButtonApply (0),
      textButtonOpen (0),
      textButtonAdd (0),
      textButtonDelete (0)
{
    addAndMakeVisible (groupPresetSelection = new GroupComponent (T("new group"),
                                                                  T("Preset Selection")));

    addAndMakeVisible (textEditor = new TextEditor (T("new text editor")));
    textEditor->setMultiLine (false);
    textEditor->setReturnKeyStartsNewLine (false);
    textEditor->setReadOnly (true);
    textEditor->setScrollbarsShown (false);
    textEditor->setCaretVisible (false);
    textEditor->setPopupMenuEnabled (false);
    textEditor->setText (String::empty);

    addAndMakeVisible (listBox = new ListBox (JUCE_T("new listbox"), this));
    listBox->setName (T("new listbox"));

    addAndMakeVisible (groupNotes = new GroupComponent (T("new group"),
                                                        T("Notes")));

    addAndMakeVisible (label = new Label (T("new label"),
                                          T("Tag:")));
    label->setFont (Font (15.0000f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label2 = new Label (T("new label"),
                                           T("Category 1:")));
    label2->setFont (Font (15.0000f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label3 = new Label (T("new label"),
                                           T("Category 2:")));
    label3->setFont (Font (15.0000f, Font::plain));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label4 = new Label (T("new label"),
                                           T("Category 3:")));
    label4->setFont (Font (15.0000f, Font::plain));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label5 = new Label (T("new label"),
                                           T("Category 4:")));
    label5->setFont (Font (15.0000f, Font::plain));
    label5->setJustificationType (Justification::centredLeft);
    label5->setEditable (false, false, false);
    label5->setColour (TextEditor::textColourId, Colours::black);
    label5->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label6 = new Label (T("new label"),
                                           T("Wavefile: L->L")));
    label6->setFont (Font (15.0000f, Font::plain));
    label6->setJustificationType (Justification::centredLeft);
    label6->setEditable (false, false, false);
    label6->setColour (TextEditor::textColourId, Colours::black);
    label6->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label7 = new Label (T("new label"),
                                           T("Wavefile: L->R")));
    label7->setFont (Font (15.0000f, Font::plain));
    label7->setJustificationType (Justification::centredLeft);
    label7->setEditable (false, false, false);
    label7->setColour (TextEditor::textColourId, Colours::black);
    label7->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label8 = new Label (T("new label"),
                                           T("Wavefile: R->L")));
    label8->setFont (Font (15.0000f, Font::plain));
    label8->setJustificationType (Justification::centredLeft);
    label8->setEditable (false, false, false);
    label8->setColour (TextEditor::textColourId, Colours::black);
    label8->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label9 = new Label (T("new label"),
                                           T("Wavefile: R->R")));
    label9->setFont (Font (15.0000f, Font::plain));
    label9->setJustificationType (Justification::centredLeft);
    label9->setEditable (false, false, false);
    label9->setColour (TextEditor::textColourId, Colours::black);
    label9->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (textButtonChooserLL = new TextButton (T("new button")));
    textButtonChooserLL->setButtonText (T("..."));
    textButtonChooserLL->addButtonListener (this);

    addAndMakeVisible (textEditorFileLL = new TextEditor (T("textEditorFileLL")));
    textEditorFileLL->setMultiLine (false);
    textEditorFileLL->setReturnKeyStartsNewLine (false);
    textEditorFileLL->setReadOnly (false);
    textEditorFileLL->setScrollbarsShown (true);
    textEditorFileLL->setCaretVisible (true);
    textEditorFileLL->setPopupMenuEnabled (true);
    textEditorFileLL->setText (String::empty);

    addAndMakeVisible (textEditorFileLR = new TextEditor (T("textEditorFileLR")));
    textEditorFileLR->setMultiLine (false);
    textEditorFileLR->setReturnKeyStartsNewLine (false);
    textEditorFileLR->setReadOnly (false);
    textEditorFileLR->setScrollbarsShown (true);
    textEditorFileLR->setCaretVisible (true);
    textEditorFileLR->setPopupMenuEnabled (true);
    textEditorFileLR->setText (String::empty);

    addAndMakeVisible (textEditorFileRL = new TextEditor (T("textEditorFileRL")));
    textEditorFileRL->setMultiLine (false);
    textEditorFileRL->setReturnKeyStartsNewLine (false);
    textEditorFileRL->setReadOnly (false);
    textEditorFileRL->setScrollbarsShown (true);
    textEditorFileRL->setCaretVisible (true);
    textEditorFileRL->setPopupMenuEnabled (true);
    textEditorFileRL->setText (String::empty);

    addAndMakeVisible (textEditorFileRR = new TextEditor (T("textEditorFileRR")));
    textEditorFileRR->setMultiLine (false);
    textEditorFileRR->setReturnKeyStartsNewLine (false);
    textEditorFileRR->setReadOnly (false);
    textEditorFileRR->setScrollbarsShown (true);
    textEditorFileRR->setCaretVisible (true);
    textEditorFileRR->setPopupMenuEnabled (true);
    textEditorFileRR->setText (String::empty);

    addAndMakeVisible (textButtonChooserLR = new TextButton (T("new button")));
    textButtonChooserLR->setButtonText (T("..."));
    textButtonChooserLR->addButtonListener (this);

    addAndMakeVisible (textButtonChooserRL = new TextButton (T("new button")));
    textButtonChooserRL->setButtonText (T("..."));
    textButtonChooserRL->addButtonListener (this);

    addAndMakeVisible (textButtonChooserRR = new TextButton (T("new button")));
    textButtonChooserRR->setButtonText (T("..."));
    textButtonChooserRR->addButtonListener (this);

    addAndMakeVisible (textEditorNotes = new TextEditor (T("textEditorNotes")));
    textEditorNotes->setMultiLine (true);
    textEditorNotes->setReturnKeyStartsNewLine (true);
    textEditorNotes->setReadOnly (false);
    textEditorNotes->setScrollbarsShown (true);
    textEditorNotes->setCaretVisible (true);
    textEditorNotes->setPopupMenuEnabled (true);
    textEditorNotes->setText (String::empty);

    addAndMakeVisible (textEditorTag = new TextEditor (T("textEditorTag")));
    textEditorTag->setMultiLine (false);
    textEditorTag->setReturnKeyStartsNewLine (false);
    textEditorTag->setReadOnly (false);
    textEditorTag->setScrollbarsShown (true);
    textEditorTag->setCaretVisible (true);
    textEditorTag->setPopupMenuEnabled (true);
    textEditorTag->setText (String::empty);

    addAndMakeVisible (textEditorCat1 = new TextEditor (T("textEditorCat1")));
    textEditorCat1->setMultiLine (false);
    textEditorCat1->setReturnKeyStartsNewLine (false);
    textEditorCat1->setReadOnly (false);
    textEditorCat1->setScrollbarsShown (true);
    textEditorCat1->setCaretVisible (true);
    textEditorCat1->setPopupMenuEnabled (true);
    textEditorCat1->setText (String::empty);

    addAndMakeVisible (textEditorCat2 = new TextEditor (T("textEditorCat2")));
    textEditorCat2->setMultiLine (false);
    textEditorCat2->setReturnKeyStartsNewLine (false);
    textEditorCat2->setReadOnly (false);
    textEditorCat2->setScrollbarsShown (true);
    textEditorCat2->setCaretVisible (true);
    textEditorCat2->setPopupMenuEnabled (true);
    textEditorCat2->setText (String::empty);

    addAndMakeVisible (textEditorCat3 = new TextEditor (T("textEditorCat3")));
    textEditorCat3->setMultiLine (false);
    textEditorCat3->setReturnKeyStartsNewLine (false);
    textEditorCat3->setReadOnly (false);
    textEditorCat3->setScrollbarsShown (true);
    textEditorCat3->setCaretVisible (true);
    textEditorCat3->setPopupMenuEnabled (true);
    textEditorCat3->setText (String::empty);

    addAndMakeVisible (textEditorCat4 = new TextEditor (T("textEditorCat4")));
    textEditorCat4->setMultiLine (false);
    textEditorCat4->setReturnKeyStartsNewLine (false);
    textEditorCat4->setReadOnly (false);
    textEditorCat4->setScrollbarsShown (true);
    textEditorCat4->setCaretVisible (true);
    textEditorCat4->setPopupMenuEnabled (true);
    textEditorCat4->setText (String::empty);

    addAndMakeVisible (textButtonSave = new TextButton (T("new button")));
    textButtonSave->setButtonText (T("Save"));
    textButtonSave->addButtonListener (this);

    addAndMakeVisible (textButtonSaveAs = new TextButton (T("new button")));
    textButtonSaveAs->setButtonText (T("Save as..."));
    textButtonSaveAs->addButtonListener (this);

    addAndMakeVisible (textButtonApply = new TextButton (T("new button")));
    textButtonApply->setButtonText (T("Apply"));
    textButtonApply->addButtonListener (this);

    addAndMakeVisible (textButtonOpen = new TextButton (T("new button")));
    textButtonOpen->setButtonText (T("Open..."));
    textButtonOpen->addButtonListener (this);

    addAndMakeVisible (textButtonAdd = new TextButton (T("new button")));
    textButtonAdd->setButtonText (T("Add"));
    textButtonAdd->addButtonListener (this);

    addAndMakeVisible (textButtonDelete = new TextButton (T("new button")));
    textButtonDelete->setButtonText (T("Delete"));
    textButtonDelete->addButtonListener (this);


    //[UserPreSize]
    listBox->setRowHeight(18);
    selectedRow = 0;
    currentPresetNum = 1;
    defaultPresetNum = 1;

    textEditorTag->setEnabled(false);
    textEditorCat1->setEnabled(false);
    textEditorCat2->setEnabled(false);
    textEditorCat3->setEnabled(false);
    textEditorCat4->setEnabled(false);
    textEditorFileLL->setEnabled(false);
    textEditorFileLR->setEnabled(false);
    textEditorFileRL->setEnabled(false);
    textEditorFileRR->setEnabled(false);
    textEditorNotes->setEnabled(false);
    //[/UserPreSize]

    setSize (828, 548);

    //[Constructor] You can add your own custom stuff here..
//    master->print("TabPresetEditor::TabPresetEditor : Waiting for your commands, Sir!");
    textEditorTag->addListener (this);
    textEditorCat1->addListener (this);
    textEditorCat2->addListener (this);
    textEditorCat3->addListener (this);
    textEditorCat4->addListener (this);
    textEditorFileLL->addListener (this);
    textEditorFileLR->addListener (this);
    textEditorFileRL->addListener (this);
    textEditorFileRR->addListener (this);
    textEditorNotes->addListener (this);

    master->registerTabPresetEditor(this);
    //[/Constructor]
}

TabPresetEditor::~TabPresetEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (groupPresetSelection);
    deleteAndZero (textEditor);
    deleteAndZero (listBox);
    deleteAndZero (groupNotes);
    deleteAndZero (label);
    deleteAndZero (label2);
    deleteAndZero (label3);
    deleteAndZero (label4);
    deleteAndZero (label5);
    deleteAndZero (label6);
    deleteAndZero (label7);
    deleteAndZero (label8);
    deleteAndZero (label9);
    deleteAndZero (textButtonChooserLL);
    deleteAndZero (textEditorFileLL);
    deleteAndZero (textEditorFileLR);
    deleteAndZero (textEditorFileRL);
    deleteAndZero (textEditorFileRR);
    deleteAndZero (textButtonChooserLR);
    deleteAndZero (textButtonChooserRL);
    deleteAndZero (textButtonChooserRR);
    deleteAndZero (textEditorNotes);
    deleteAndZero (textEditorTag);
    deleteAndZero (textEditorCat1);
    deleteAndZero (textEditorCat2);
    deleteAndZero (textEditorCat3);
    deleteAndZero (textEditorCat4);
    deleteAndZero (textButtonSave);
    deleteAndZero (textButtonSaveAs);
    deleteAndZero (textButtonApply);
    deleteAndZero (textButtonOpen);
    deleteAndZero (textButtonAdd);
    deleteAndZero (textButtonDelete);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TabPresetEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xffffe000));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TabPresetEditor::resized()
{
    groupPresetSelection->setBounds (8, 8, 280, 500);
    textEditor->setBounds (24, 32, 248, 428);
    listBox->setBounds (27, 35, 242, 424);
    groupNotes->setBounds (296, 232, 520, 232);
    label->setBounds (296, 16, 104, 20);
    label2->setBounds (296, 40, 104, 20);
    label3->setBounds (296, 64, 104, 20);
    label4->setBounds (296, 88, 104, 20);
    label5->setBounds (296, 112, 104, 20);
    label6->setBounds (296, 136, 104, 20);
    label7->setBounds (296, 160, 104, 20);
    label8->setBounds (296, 184, 104, 20);
    label9->setBounds (296, 208, 104, 20);
    textButtonChooserLL->setBounds (784, 136, 30, 20);
    textEditorFileLL->setBounds (400, 136, 380, 20);
    textEditorFileLR->setBounds (400, 160, 380, 20);
    textEditorFileRL->setBounds (400, 184, 380, 20);
    textEditorFileRR->setBounds (400, 208, 380, 20);
    textButtonChooserLR->setBounds (784, 160, 30, 20);
    textButtonChooserRL->setBounds (784, 184, 30, 20);
    textButtonChooserRR->setBounds (784, 208, 30, 20);
    textEditorNotes->setBounds (312, 256, 488, 192);
    textEditorTag->setBounds (400, 16, 190, 20);
    textEditorCat1->setBounds (400, 40, 380, 20);
    textEditorCat2->setBounds (400, 64, 380, 20);
    textEditorCat3->setBounds (400, 88, 380, 20);
    textEditorCat4->setBounds (400, 112, 380, 20);
    textButtonSave->setBounds (512, 472, 94, 32);
    textButtonSaveAs->setBounds (616, 472, 94, 32);
    textButtonApply->setBounds (720, 472, 94, 32);
    textButtonOpen->setBounds (408, 472, 94, 32);
    textButtonAdd->setBounds (24, 468, 64, 24);
    textButtonDelete->setBounds (100, 468, 64, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void TabPresetEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == textButtonChooserLL)
    {
        //[UserButtonCode_textButtonChooserLL] -- add your button handler code here..
        String dir = master->getDBdir();
        String filename = getWavFileChooserOpen(dir);
        if (filename != String::empty)
        {
            if (filename.startsWith(dir) == true)
                filename = filename.substring(dir.length());
            presetDB_copy[selectedRow].impulseResponses.ll = filename;
            textEditorFileLL->setText(filename);
        }
        //[/UserButtonCode_textButtonChooserLL]
    }
    else if (buttonThatWasClicked == textButtonChooserLR)
    {
        //[UserButtonCode_textButtonChooserLR] -- add your button handler code here..
        String dir = master->getDBdir();
        String filename = getWavFileChooserOpen(dir);
        if (filename != String::empty)
        {
            if (filename.startsWith(dir) == true)
                filename = filename.substring(dir.length());
            presetDB_copy[selectedRow].impulseResponses.lr = filename;
            textEditorFileLR->setText(filename);
        }
        //[/UserButtonCode_textButtonChooserLR]
    }
    else if (buttonThatWasClicked == textButtonChooserRL)
    {
        //[UserButtonCode_textButtonChooserRL] -- add your button handler code here..
        String dir = master->getDBdir();
        String filename = getWavFileChooserOpen(dir);
        if (filename != String::empty)
        {
            if (filename.startsWith(dir) == true)
                filename = filename.substring(dir.length());
            presetDB_copy[selectedRow].impulseResponses.rl = filename;
            textEditorFileRL->setText(filename);
        }
        //[/UserButtonCode_textButtonChooserRL]
    }
    else if (buttonThatWasClicked == textButtonChooserRR)
    {
        //[UserButtonCode_textButtonChooserRR] -- add your button handler code here..
        String dir = master->getDBdir();
        String filename = getWavFileChooserOpen(dir);
        if (filename != String::empty)
        {
            if (filename.startsWith(dir) == true)
                filename = filename.substring(dir.length());
            presetDB_copy[selectedRow].impulseResponses.rr = filename;
            textEditorFileRR->setText(filename);
        }
        //[/UserButtonCode_textButtonChooserRR]
    }
    else if (buttonThatWasClicked == textButtonSave)
    {
        //[UserButtonCode_textButtonSave] -- add your button handler code here..
        master->savePresetDB(presetDB_copy);
        //[/UserButtonCode_textButtonSave]
    }
    else if (buttonThatWasClicked == textButtonSaveAs)
    {
        //[UserButtonCode_textButtonSaveAs] -- add your button handler code here..
        String dir = master->getUserdir();
        String filename = getXmlFileChooserSave(dir);
        if (filename != String::empty)
            master->savePresetDBas(presetDB_copy, filename);
        //[/UserButtonCode_textButtonSaveAs]
    }
    else if (buttonThatWasClicked == textButtonApply)
    {
        //[UserButtonCode_textButtonApply] -- add your button handler code here..
        master->setPresetDB(presetDB_copy);
        //[/UserButtonCode_textButtonApply]
    }
    else if (buttonThatWasClicked == textButtonOpen)
    {
        //[UserButtonCode_textButtonOpen] -- add your button handler code here..
        String dir = master->getUserdir();
        String filename = getXmlFileChooserOpen(dir);
        if (filename != String::empty)
        {
            presetManager->readFile(filename);
            presetDB_copy.clear();
            presetDB_copy = presetManager->getPresetDB();
            updateListBox();
            master->setPresetDB(presetDB_copy, false);
        }
        //[/UserButtonCode_textButtonOpen]
    }
    else if (buttonThatWasClicked == textButtonAdd)
    {
        //[UserButtonCode_textButtonAdd] -- add your button handler code here..
        ParamPreset newPreset;
        newPreset.name = JUCE_T("new preset");
        newPreset.category.cat_1 = JUCE_T("new category");
        newPreset.category.cat_2 = JUCE_T("new category");
        newPreset.category.cat_3 = JUCE_T("new category");
        newPreset.category.cat_4 = JUCE_T("new category");
        presetDB_copy.insert(presetDB_copy.begin() + selectedRow, newPreset);
        updateListBox();
        //[/UserButtonCode_textButtonAdd]
    }
    else if (buttonThatWasClicked == textButtonDelete)
    {
        //[UserButtonCode_textButtonDelete] -- add your button handler code here..
        if (presetDB_copy.size() > 0)
        {
            presetDB_copy.erase(presetDB_copy.begin() + selectedRow);
            updateListBox();
        }
        //[/UserButtonCode_textButtonDelete]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void TabPresetEditor::setPresetManager(PresetManager *man)
{
    presetManager = man;
    presetDB_copy = presetManager->getPresetDB();
    selectedRow = 0;
    updateListBox();
}


void TabPresetEditor::updateListBox()
{
    int dbSize = presetDB_copy.size();
    if (selectedRow > dbSize)
        selectedRow = dbSize;
    listBox->selectRow(selectedRow);
    listBoxItemClicked(selectedRow);
    for (int i = 0; i < dbSize; i++)
        listBox->repaintRow(i);
    listBox->updateContent();
}


void TabPresetEditor::onComponentSelected(void)
{
    //FIXME: remove this
    printf("TabPresetEditor selected\n");

    presetDB_copy = presetManager->getPresetDB();
    defaultPresetNum = presetManager->getDefaultPresetNum();
    currentPresetNum = presetManager->getCurrentPresetNum();
    selectedRow = currentPresetNum - 1;
    updateListBox();
}


String TabPresetEditor::getWavFileChooserOpen(String dir)
{
    FileChooser fc(JUCE_T("Choose a WAV file to open..."),
                   dir,
                   JUCE_T("*.wav"),
                   true);

    if (fc.browseForFileToOpen())
    {
        File chosenFile = fc.getResult();
        return chosenFile.getFullPathName();
    }

    return String::empty;
}


String TabPresetEditor::getXmlFileChooserOpen(String dir)
{
    FileChooser fc(JUCE_T("Choose a XML file to open..."),
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


String TabPresetEditor::getXmlFileChooserSave(String dir)
{
    FileChooser fc(JUCE_T("Choose a XML file to save..."),
                   dir,
                   JUCE_T("*.xml"),
                   true);

    if (fc.browseForFileToSave(true))
    {
        File chosenFile = fc.getResult();
        chosenFile.create();
        return chosenFile.getFullPathName();
    }
    else
        int debug_me = 1;

    return String::empty;
}


int TabPresetEditor::getNumRows()
{
    if (presetManager == 0)
        return 0;

    return presetDB_copy.size() + 1;
}


void TabPresetEditor::paintListBoxItem(int rowNumber,
                                       Graphics &g,
                                       int width, int height,
                                       bool rowIsSelected)
{
    int num = rowNumber + 1;

    if (rowIsSelected)
        g.fillAll (Colour (0xffbbbbff));

    Font font(height - 2);
    g.setFont(font);

    if (num == defaultPresetNum)
        g.setColour(Colour(0xff800000));

    String text = String::formatted(JUCE_T("%d: "), num);
    if (num <= presetDB_copy.size())
        text += presetDB_copy[rowNumber].name;
    else
        text += String(JUCE_T("<Empty>"));
    g.drawText(text,
               4, 0,
               width - 4, height,
               Justification::centredLeft,
               true);
}


void TabPresetEditor::listBoxItemClicked(int row)
{
    String text;

    selectedRow = row;

    if (row < presetDB_copy.size())
    {
        text = presetDB_copy[row].name;
        textEditorTag->setText(text);
        textEditorTag->setEnabled(true);

        ParamCategory cat = presetDB_copy[row].category;
        textEditorCat1->setText(cat.cat_1);
        textEditorCat2->setText(cat.cat_2);
        textEditorCat3->setText(cat.cat_3);
        textEditorCat4->setText(cat.cat_4);
        textEditorCat1->setEnabled(true);
        textEditorCat2->setEnabled(true);
        textEditorCat3->setEnabled(true);
        textEditorCat4->setEnabled(true);

        ParamImpulseResponses ir = presetDB_copy[row].impulseResponses;
        textEditorFileLL->setText(ir.ll);
        textEditorFileLR->setText(ir.lr);
        textEditorFileRL->setText(ir.rl);
        textEditorFileRR->setText(ir.rr);
        textEditorFileLL->setEnabled(true);
        textEditorFileLR->setEnabled(true);
        textEditorFileRL->setEnabled(true);
        textEditorFileRR->setEnabled(true);

        text = presetDB_copy[row].notes;
        textEditorNotes->setText(text);
        textEditorNotes->setEnabled(true);
    }
    else
    {
        textEditorTag->setText(String::empty);
        textEditorTag->setEnabled(false);

        textEditorCat1->setText(String::empty);
        textEditorCat2->setText(String::empty);
        textEditorCat3->setText(String::empty);
        textEditorCat4->setText(String::empty);
        textEditorCat1->setEnabled(false);
        textEditorCat2->setEnabled(false);
        textEditorCat3->setEnabled(false);
        textEditorCat4->setEnabled(false);

        textEditorFileLL->setText(String::empty);
        textEditorFileLR->setText(String::empty);
        textEditorFileRL->setText(String::empty);
        textEditorFileRR->setText(String::empty);
        textEditorFileLL->setEnabled(false);
        textEditorFileLR->setEnabled(false);
        textEditorFileRL->setEnabled(false);
        textEditorFileRR->setEnabled(false);

        textEditorNotes->setText(String::empty);
        textEditorNotes->setEnabled(false);
    }
}


void TabPresetEditor::listBoxItemClicked(int row, const MouseEvent &e)
{
    listBoxItemClicked(row);
}


void TabPresetEditor::listBoxItemDoubleClicked(int row, const MouseEvent &e)
{
    listBoxItemClicked(row, e);
}


void TabPresetEditor::deleteKeyPressed(int lastRowSelected)
{
    if (selectedRow < presetDB_copy.size())
    {
        presetDB_copy.erase(presetDB_copy.begin() + selectedRow);
        updateListBox();
    }
}


void TabPresetEditor::textEditorTextChanged (TextEditor &editor)
{
}


void TabPresetEditor::textEditorReturnKeyPressed (TextEditor &editor)
{
    String text = editor.getText();

    if (editor.getName() == String(JUCE_T("textEditorTag")))
    {
        presetDB_copy[selectedRow].name = text;
    }
    else if (editor.getName() == String(JUCE_T("textEditorCat1")))
    {
        presetDB_copy[selectedRow].category.cat_1 = text;
    }
    else if (editor.getName() == String(JUCE_T("textEditorCat2")))
    {
        presetDB_copy[selectedRow].category.cat_2 = text;
    }
    else if (editor.getName() == String(JUCE_T("textEditorCat3")))
    {
        presetDB_copy[selectedRow].category.cat_3 = text;
    }
    else if (editor.getName() == String(JUCE_T("textEditorCat4")))
    {
        presetDB_copy[selectedRow].category.cat_4 = text;
    }
    else if (editor.getName() == String(JUCE_T("textEditorFileLL")))
    {
        presetDB_copy[selectedRow].impulseResponses.ll = text;
    }
    else if (editor.getName() == String(JUCE_T("textEditorFileLR")))
    {
        presetDB_copy[selectedRow].impulseResponses.lr = text;
    }
    else if (editor.getName() == String(JUCE_T("textEditorFileRL")))
    {
        presetDB_copy[selectedRow].impulseResponses.rl = text;
    }
    else if (editor.getName() == String(JUCE_T("textEditorFileRR")))
    {
        presetDB_copy[selectedRow].impulseResponses.rr = text;
    }
    else if (editor.getName() == String(JUCE_T("textEditorNotes")))
    {
        presetDB_copy[selectedRow].notes = text;
    }
}


void TabPresetEditor::textEditorEscapeKeyPressed (TextEditor &editor)
{
}


void TabPresetEditor::textEditorFocusLost (TextEditor &editor)
{
    // focus change is interpreted as user input completion
    textEditorReturnKeyPressed(editor);
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TabPresetEditor" componentName=""
                 parentClasses="public Component, public TextEditorListener, public ListBoxModel"
                 constructorParams="MasterAndCommander *m" variableInitialisers="master (m),&#10;presetManager(0)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="1" initialWidth="828" initialHeight="548">
  <BACKGROUND backgroundColour="ffffe000"/>
  <GROUPCOMPONENT name="new group" id="5bbb615c6111dfeb" memberName="groupPresetSelection"
                  virtualName="" explicitFocusOrder="0" pos="8 8 280 500" title="Preset Selection"/>
  <TEXTEDITOR name="new text editor" id="d542415b872610f0" memberName="textEditor"
              virtualName="" explicitFocusOrder="0" pos="24 32 248 428" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="1" scrollbars="0"
              caret="0" popupmenu="0"/>
  <GENERICCOMPONENT name="new listbox" id="90b42c658c2c4f06" memberName="listBox"
                    virtualName="" explicitFocusOrder="0" pos="27 35 242 424" class="ListBox"
                    params="JUCE_T(&quot;new listbox&quot;), this"/>
  <GROUPCOMPONENT name="new group" id="feef6879e095fd42" memberName="groupNotes"
                  virtualName="" explicitFocusOrder="0" pos="296 232 520 232" title="Notes"/>
  <LABEL name="new label" id="2a92bdd8797a5c0c" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="296 16 104 20" edTextCol="ff000000"
         edBkgCol="0" labelText="Tag:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="d60f95ae51be6fc9" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="296 40 104 20" edTextCol="ff000000"
         edBkgCol="0" labelText="Category 1:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="da0065a01bd61087" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="296 64 104 20" edTextCol="ff000000"
         edBkgCol="0" labelText="Category 2:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="5e4e7210d6b88d44" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="296 88 104 20" edTextCol="ff000000"
         edBkgCol="0" labelText="Category 3:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="89087cb7602b5cf1" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="296 112 104 20" edTextCol="ff000000"
         edBkgCol="0" labelText="Category 4:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="474b7e931bda8352" memberName="label6" virtualName=""
         explicitFocusOrder="0" pos="296 136 104 20" edTextCol="ff000000"
         edBkgCol="0" labelText="Wavefile: L-&gt;L" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="63a88d206c97e029" memberName="label7" virtualName=""
         explicitFocusOrder="0" pos="296 160 104 20" edTextCol="ff000000"
         edBkgCol="0" labelText="Wavefile: L-&gt;R" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="63e75ec5961dcc92" memberName="label8" virtualName=""
         explicitFocusOrder="0" pos="296 184 104 20" edTextCol="ff000000"
         edBkgCol="0" labelText="Wavefile: R-&gt;L" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="220822917c93aab0" memberName="label9" virtualName=""
         explicitFocusOrder="0" pos="296 208 104 20" edTextCol="ff000000"
         edBkgCol="0" labelText="Wavefile: R-&gt;R" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="new button" id="c9dea607df14f877" memberName="textButtonChooserLL"
              virtualName="" explicitFocusOrder="0" pos="784 136 30 20" buttonText="..."
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTEDITOR name="textEditorFileLL" id="46c2d54dbfae1739" memberName="textEditorFileLL"
              virtualName="" explicitFocusOrder="0" pos="400 136 380 20" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="textEditorFileLR" id="f707b69bdbfdd0b9" memberName="textEditorFileLR"
              virtualName="" explicitFocusOrder="0" pos="400 160 380 20" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="textEditorFileRL" id="b6400ded9229175" memberName="textEditorFileRL"
              virtualName="" explicitFocusOrder="0" pos="400 184 380 20" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="textEditorFileRR" id="17bae52fab2672ad" memberName="textEditorFileRR"
              virtualName="" explicitFocusOrder="0" pos="400 208 380 20" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="new button" id="5e63fc03d289e661" memberName="textButtonChooserLR"
              virtualName="" explicitFocusOrder="0" pos="784 160 30 20" buttonText="..."
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="126729682c326da3" memberName="textButtonChooserRL"
              virtualName="" explicitFocusOrder="0" pos="784 184 30 20" buttonText="..."
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="5a4b3d02c3c9b36a" memberName="textButtonChooserRR"
              virtualName="" explicitFocusOrder="0" pos="784 208 30 20" buttonText="..."
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTEDITOR name="textEditorNotes" id="2e7167da16d79c0" memberName="textEditorNotes"
              virtualName="" explicitFocusOrder="0" pos="312 256 488 192" initialText=""
              multiline="1" retKeyStartsLine="1" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="textEditorTag" id="27591352b6e79c34" memberName="textEditorTag"
              virtualName="" explicitFocusOrder="0" pos="400 16 190 20" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="textEditorCat1" id="eb6538ed8c693c7f" memberName="textEditorCat1"
              virtualName="" explicitFocusOrder="0" pos="400 40 380 20" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="textEditorCat2" id="4a356d146f0932bd" memberName="textEditorCat2"
              virtualName="" explicitFocusOrder="0" pos="400 64 380 20" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="textEditorCat3" id="da136f3e3d107a28" memberName="textEditorCat3"
              virtualName="" explicitFocusOrder="0" pos="400 88 380 20" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="textEditorCat4" id="f10d7c42ed179cbd" memberName="textEditorCat4"
              virtualName="" explicitFocusOrder="0" pos="400 112 380 20" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="new button" id="6a7feedb9b89f7ad" memberName="textButtonSave"
              virtualName="" explicitFocusOrder="0" pos="512 472 94 32" buttonText="Save"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="f91685d349299ec3" memberName="textButtonSaveAs"
              virtualName="" explicitFocusOrder="0" pos="616 472 94 32" buttonText="Save as..."
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="98eaa2308e3dff56" memberName="textButtonApply"
              virtualName="" explicitFocusOrder="0" pos="720 472 94 32" buttonText="Apply"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="bb782d1bce6654d4" memberName="textButtonOpen"
              virtualName="" explicitFocusOrder="0" pos="408 472 94 32" buttonText="Open..."
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="a317b7ab8939b36b" memberName="textButtonAdd"
              virtualName="" explicitFocusOrder="0" pos="24 468 64 24" buttonText="Add"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="d19eab292b14a30a" memberName="textButtonDelete"
              virtualName="" explicitFocusOrder="0" pos="100 468 64 24" buttonText="Delete"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
