/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  18 Jan 2010 2:13:56 pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_XIMPULSEMAINCOMPONENT_XIMPULSEMAINCOMPONENT_7F79EA79__
#define __JUCER_HEADER_XIMPULSEMAINCOMPONENT_XIMPULSEMAINCOMPONENT_7F79EA79__

//[Headers]     -- You can add your own extra header files here --
#include "../StandardHeader.h"
class XImpulsePlugin;
class XImpulseComponent;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class XImpulseMainComponent  : public Component,
                               public FilenameComponentListener,
                               public ComboBoxListener
{
public:
    //==============================================================================
    XImpulseMainComponent (XImpulseComponent* const editor_, XImpulsePlugin* const plugin_);
    ~XImpulseMainComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void filenameComponentChanged (FilenameComponent*);
    void updateControls ();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void filesDropped (const StringArray& filenames, int mouseX, int mouseY);


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    bool loadImpulseResponse (const File& irFile);

    XImpulseComponent* editor;
    XImpulsePlugin* plugin;
    //[/UserVariables]

    //==============================================================================
    ComboBox* presetBox;
    FilenameComponent* fileChooser;
    Label* label;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    XImpulseMainComponent (const XImpulseMainComponent&);
    const XImpulseMainComponent& operator= (const XImpulseMainComponent&);
};


#endif   // __JUCER_HEADER_XIMPULSEMAINCOMPONENT_XIMPULSEMAINCOMPONENT_7F79EA79__
