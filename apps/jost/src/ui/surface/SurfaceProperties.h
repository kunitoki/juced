/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  22 Feb 2008 2:55:49 pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_SURFACEPROPERTIES_SURFACEPROPERTIES_28FDA4EC__
#define __JUCER_HEADER_SURFACEPROPERTIES_SURFACEPROPERTIES_28FDA4EC__

//[Headers]     -- You can add your own extra header files here --
#include "../../Config.h"

class SurfaceObject;
class SurfaceComponent;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SurfaceProperties  : public Component,
                           public ComboBoxListener
{
public:

    //==============================================================================
    SurfaceProperties (SurfaceComponent* owner_);
    ~SurfaceProperties();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void setCurrentSurfaceObject (SurfaceObject* object);
    void fillParametersComboBox ();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    SurfaceComponent* owner;
    SurfaceObject* currentObject;
    //[/UserVariables]

    //==============================================================================
    ComboBox* pluginCombo;
    ComboBox* parameter1Combo;
    Label* labelPlugin;
    Label* labelParameter1;
    ComboBox* parameter2Combo;
    Label* labelParameter2;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    SurfaceProperties (const SurfaceProperties&);
    const SurfaceProperties& operator= (const SurfaceProperties&);
};


#endif   // __JUCER_HEADER_SURFACEPROPERTIES_SURFACEPROPERTIES_28FDA4EC__
