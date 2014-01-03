/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  18 Jan 2010 11:31:06 am

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_XSYNTHABOUT_XSYNTHABOUT_339F53DC__
#define __JUCER_HEADER_XSYNTHABOUT_XSYNTHABOUT_339F53DC__

//[Headers]     -- You can add your own extra header files here --
#include "../StandardHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class XSynthAbout  : public Component
{
public:
    //==============================================================================
    XSynthAbout ();
    ~XSynthAbout();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();

    // Binary resources:
    static const char* xt2logo_png;
    static const int xt2logo_pngSize;
    static const char* capsaicin_png;
    static const int capsaicin_pngSize;

    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    HyperlinkButton* anticoreLink;
    Image* cachedImage_xt2logo_png;
    Image* cachedImage_capsaicin_png;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    XSynthAbout (const XSynthAbout&);
    const XSynthAbout& operator= (const XSynthAbout&);
};


#endif   // __JUCER_HEADER_XSYNTHABOUT_XSYNTHABOUT_339F53DC__
