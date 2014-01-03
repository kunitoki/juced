/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  18 Jan 2010 2:40:42 pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_SOUNDCRABABOUTCOMPONENT_SOUNDCRABABOUTCOMPONENT_E48FC44D__
#define __JUCER_HEADER_SOUNDCRABABOUTCOMPONENT_SOUNDCRABABOUTCOMPONENT_E48FC44D__

//[Headers]     -- You can add your own extra header files here --
#include "../StandardHeader.h"
class SoundCrabEditor;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SoundCrabAboutComponent  : public Component
{
public:
    //==============================================================================
    SoundCrabAboutComponent (SoundCrabEditor* const editor_, SoundCrabPlugin* const plugin_);
    ~SoundCrabAboutComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void filesDropped (const StringArray& filenames, int mouseX, int mouseY);

    // Binary resources:
    static const char* scrab_png;
    static const int scrab_pngSize;

    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    SoundCrabEditor* editor;
    SoundCrabPlugin* plugin;
    //[/UserVariables]

    //==============================================================================
    HyperlinkButton* anticoreLink;
    Label* titleLabel;
    Image* cachedImage_scrab_png;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    SoundCrabAboutComponent (const SoundCrabAboutComponent&);
    const SoundCrabAboutComponent& operator= (const SoundCrabAboutComponent&);
};


#endif   // __JUCER_HEADER_SOUNDCRABABOUTCOMPONENT_SOUNDCRABABOUTCOMPONENT_E48FC44D__
