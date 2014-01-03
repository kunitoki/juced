/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  3 Dec 2009 10:21:58 am

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_NEKOBEEMAIN_NEKOBEEMAIN_3A97CFD8__
#define __JUCER_HEADER_NEKOBEEMAIN_NEKOBEEMAIN_3A97CFD8__

//[Headers]     -- You can add your own extra header files here --
#include "../StandardHeader.h"

class NekobeePlugin;
class NekobeeComponent;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class NekobeeMain  : public Component,
                     public SliderListener
{
public:
    //==============================================================================
    NekobeeMain (NekobeePlugin* plugin_, NekobeeComponent* parent_);
    ~NekobeeMain();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void updateControls ();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);

    // Binary resources:
    static const char* bee_logo_png;
    static const int bee_logo_pngSize;

    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    NekobeePlugin* plugin;
    NekobeeComponent* parent;
    //[/UserVariables]

    //==============================================================================
    ParameterSlider* accentSlider;
    ParameterSlider* volumeSlider;
    ImageSlider* cutoffSlider;
    ImageSlider* resonanceSlider;
    ParameterSlider* decaySlider;
    ParameterSlider* envSlider;
    ParameterSlider* tuningSlider;
    ParameterSlider* waveformSlider;
    Label* versionLabel;
    MidiKeyboardComponent* keyboard;
    Image* cachedImage_bee_logo_png;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    NekobeeMain (const NekobeeMain&);
    const NekobeeMain& operator= (const NekobeeMain&);
};


#endif   // __JUCER_HEADER_NEKOBEEMAIN_NEKOBEEMAIN_3A97CFD8__
