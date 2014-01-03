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

#ifndef __JUCER_HEADER_XSYNTHBANKSELECT_XSYNTHBANKSELECT_A0E6A987__
#define __JUCER_HEADER_XSYNTHBANKSELECT_XSYNTHBANKSELECT_A0E6A987__

//[Headers]     -- You can add your own extra header files here --
#include "../StandardHeader.h"
#include "../XSynthPlugin.h"
#include "../Misc/Master.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class XSynthBankSelect  : public Component,
                          public DragAndDropContainer,
                          public ComboBoxListener
{
public:
    //==============================================================================
    XSynthBankSelect (XSynthPlugin* plugin_, Master* master_);
    ~XSynthBankSelect();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void updatePresetSelector ();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    XSynthPlugin* plugin;
    Master* master;
    //[/UserVariables]

    //==============================================================================
    GroupComponent* nameGroup;
    GroupComponent* authorGroup;
    GroupComponent* commentGroup;
    TextEditor* commentsText;
    TextEditor* authorText;
    TextEditor* nameText;
    GroupComponent* typeGroup;
    ComboBox* categoryBox;
    PresetSelectorComponent* presetSelector;
    GroupComponent* presetGroup;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    XSynthBankSelect (const XSynthBankSelect&);
    const XSynthBankSelect& operator= (const XSynthBankSelect&);
};


#endif   // __JUCER_HEADER_XSYNTHBANKSELECT_XSYNTHBANKSELECT_A0E6A987__
