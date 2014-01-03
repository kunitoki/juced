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

#ifndef __JUCER_HEADER_TABPREFERENCES_TABPREFERENCES_22742E3D__
#define __JUCER_HEADER_TABPREFERENCES_TABPREFERENCES_22742E3D__

//[Headers]     -- You can add your own extra header files here --
#include "juce_amalgamated.h"
#include "../ParamPreferences.h"

// forward declarations
class MasterAndCommander;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TabPreferences  : public Component,
                        public TextEditorListener,
                        public ButtonListener,
                        public ComboBoxListener
{
public:
    //==============================================================================
    TabPreferences (MasterAndCommander *m);
    ~TabPreferences();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void setPreferences(const ParamPreferences & param);
    String getFileChooserResult(String dir);
    void textEditorTextChanged (TextEditor &editor);
    void textEditorReturnKeyPressed (TextEditor &editor);
    void textEditorEscapeKeyPressed (TextEditor &editor);
    void textEditorFocusLost (TextEditor &editor);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);

    // Binary resources:
    static const char* directivity2_svg;
    static const int directivity2_svgSize;

    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    MasterAndCommander* master;
    ParamPreferences paramPreferences;
    //[/UserVariables]

    //==============================================================================
    GroupComponent* groupComponentHelp;
    Label* labelPreset;
    TextEditor* textEditorPreset;
    GroupComponent* groupComponentStrategy;
    ToggleButton* toggleButtonUniform;
    ToggleButton* toggleButtonLowest;
    Label* labelLatency;
    ComboBox* comboBoxLatency;
    TextEditor* textEditorHelp;
    TextButton* textButton;
    Label* label;
    Drawable* drawable1;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    TabPreferences (const TabPreferences&);
    const TabPreferences& operator= (const TabPreferences&);
};


#endif   // __JUCER_HEADER_TABPREFERENCES_TABPREFERENCES_22742E3D__
