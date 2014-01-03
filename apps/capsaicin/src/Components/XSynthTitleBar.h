/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  18 Jan 2010 11:31:20 am

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_XSYNTHTITLEBAR_XSYNTHTITLEBAR_9D813AA3__
#define __JUCER_HEADER_XSYNTHTITLEBAR_XSYNTHTITLEBAR_9D813AA3__

//[Headers]     -- You can add your own extra header files here --
#include "../StandardHeader.h"
#include "../Misc/Master.h"

class XSynthPlugin;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class XSynthTitleBar  : public Component,
                        public ButtonListener
{
public:
    //==============================================================================
    XSynthTitleBar (XSynthPlugin* const plugin_, Master* const master_);
    ~XSynthTitleBar();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);

    // Binary resources:
    static const char* capsaicin_title_png;
    static const int capsaicin_title_pngSize;

    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    XSynthPlugin* plugin;
    Master* master;
    //[/UserVariables]

    //==============================================================================
    TextButton* panicButton;
    TextButton* loadButton;
    TextButton* saveButton;
    Image* cachedImage_capsaicin_title_png;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    XSynthTitleBar (const XSynthTitleBar&);
    const XSynthTitleBar& operator= (const XSynthTitleBar&);
};


#endif   // __JUCER_HEADER_XSYNTHTITLEBAR_XSYNTHTITLEBAR_9D813AA3__
