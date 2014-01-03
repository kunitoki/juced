/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  18 Jan 2010 11:32:46 am

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_XSYNTHOPTIONS_XSYNTHOPTIONS_D3E16627__
#define __JUCER_HEADER_XSYNTHOPTIONS_XSYNTHOPTIONS_D3E16627__

//[Headers]     -- You can add your own extra header files here --
#include "../StandardHeader.h"
#include "../Misc/Config.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class XSynthOptions  : public Component,
                       public ButtonListener
{
public:
    //==============================================================================
    XSynthOptions ();
    ~XSynthOptions();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    GroupComponent* globalGroup;
    ToggleButton* keysVisible;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    XSynthOptions (const XSynthOptions&);
    const XSynthOptions& operator= (const XSynthOptions&);
};


#endif   // __JUCER_HEADER_XSYNTHOPTIONS_XSYNTHOPTIONS_D3E16627__
