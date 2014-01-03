/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  19 Oct 2009 8:41:04 pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.11

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_TABABOUT_TABABOUT_34B27909__
#define __JUCER_HEADER_TABABOUT_TABABOUT_34B27909__

//[Headers]     -- You can add your own extra header files here --
#include "juce_amalgamated.h"

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
class TabAbout  : public Component
{
public:
    //==============================================================================
    TabAbout (MasterAndCommander *m);
    ~TabAbout();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();

    // Binary resources:
    static const char* aes_cb_jpg;
    static const int aes_cb_jpgSize;

    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    MasterAndCommander* master;
    //[/UserVariables]

    //==============================================================================
    GroupComponent* groupComponent;
    Label* label;
    TextEditor* textEditor;
    Image* cachedImage_aes_cb_jpg;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    TabAbout (const TabAbout&);
    const TabAbout& operator= (const TabAbout&);
};


#endif   // __JUCER_HEADER_TABABOUT_TABABOUT_34B27909__
