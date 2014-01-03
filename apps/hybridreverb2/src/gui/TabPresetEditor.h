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


#ifndef __JUCER_HEADER_TABPRESETEDITOR_TABPRESETEDITOR_23EBC2D4__
#define __JUCER_HEADER_TABPRESETEDITOR_TABPRESETEDITOR_23EBC2D4__

//[Headers]     -- You can add your own extra header files here --
#include "juce_amalgamated.h"

// forward declarations
class MasterAndCommander;
class PresetManager;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TabPresetEditor  : public Component,
                         public TextEditorListener,
                         public ListBoxModel,
                         public ButtonListener
{
public:
    //==============================================================================
    TabPresetEditor (MasterAndCommander *m);
    ~TabPresetEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void setPresetManager (PresetManager *man);
    void updateListBox();
    void onComponentSelected(void);
    String getWavFileChooserOpen(String dir);
    String getXmlFileChooserOpen(String dir);
    String getXmlFileChooserSave(String dir);

    // ListBoxModel methods
    int getNumRows();
    void paintListBoxItem(int rowNumber,
                          Graphics &g,
                          int width, int height,
                          bool rowIsSelected);
    void listBoxItemClicked(int row);
    void listBoxItemClicked(int row, const MouseEvent &e);
    void listBoxItemDoubleClicked(int row, const MouseEvent &e);
    void deleteKeyPressed(int lastRowSelected);
//    Component * refreshComponentForRow(int rowNumber,
//                                       bool isRowSelected,
//                                       Component *existingComponentToUpdate);
//    void backgroundClicked();
//    void selectedRowsChanged(int lastRowSelected);
//    void returnKeyPressed(int lastRowSelected);
//    void listWasScrolled();
//    const String getDragSourceDescription(const SparseSet< int > &currentlySelectedRows);

    // TextEditorListener methods
    void textEditorTextChanged(TextEditor & editor);
    void textEditorReturnKeyPressed(TextEditor & editor);
    void textEditorEscapeKeyPressed(TextEditor & editor);
    void textEditorFocusLost(TextEditor & editor);

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    MasterAndCommander* master;
    PresetManager* presetManager;
    std::vector<ParamPreset> presetDB_copy;
    int selectedRow;
    int currentPresetNum;
    int defaultPresetNum;
    //[/UserVariables]

    //==============================================================================
    GroupComponent* groupPresetSelection;
    TextEditor* textEditor;
    ListBox* listBox;
    GroupComponent* groupNotes;
    Label* label;
    Label* label2;
    Label* label3;
    Label* label4;
    Label* label5;
    Label* label6;
    Label* label7;
    Label* label8;
    Label* label9;
    TextButton* textButtonChooserLL;
    TextEditor* textEditorFileLL;
    TextEditor* textEditorFileLR;
    TextEditor* textEditorFileRL;
    TextEditor* textEditorFileRR;
    TextButton* textButtonChooserLR;
    TextButton* textButtonChooserRL;
    TextButton* textButtonChooserRR;
    TextEditor* textEditorNotes;
    TextEditor* textEditorTag;
    TextEditor* textEditorCat1;
    TextEditor* textEditorCat2;
    TextEditor* textEditorCat3;
    TextEditor* textEditorCat4;
    TextButton* textButtonSave;
    TextButton* textButtonSaveAs;
    TextButton* textButtonApply;
    TextButton* textButtonOpen;
    TextButton* textButtonAdd;
    TextButton* textButtonDelete;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    TabPresetEditor (const TabPresetEditor&);
    const TabPresetEditor& operator= (const TabPresetEditor&);
};


#endif   // __JUCER_HEADER_TABPRESETEDITOR_TABPRESETEDITOR_23EBC2D4__
