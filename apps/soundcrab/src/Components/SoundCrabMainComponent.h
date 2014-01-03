/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  18 Jan 2010 2:40:48 pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_SOUNDCRABMAINCOMPONENT_SOUNDCRABMAINCOMPONENT_5D7A1A98__
#define __JUCER_HEADER_SOUNDCRABMAINCOMPONENT_SOUNDCRABMAINCOMPONENT_5D7A1A98__

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
class SoundCrabMainComponent  : public Component,
                                public FilenameComponentListener,
                                public Timer,
                                public ComboBoxListener,
                                public SliderListener
{
public:
    //==============================================================================
    SoundCrabMainComponent (SoundCrabEditor* const editor_, SoundCrabPlugin* const plugin_);
    ~SoundCrabMainComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void filenameComponentChanged (FilenameComponent*);
    void updateControls ();
    void timerCallback ();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void filesDropped (const StringArray& filenames, int mouseX, int mouseY);


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    bool loadSoundFont (const File& soundFontFile);

    SoundCrabEditor* editor;
    SoundCrabPlugin* plugin;
    //[/UserVariables]

    //==============================================================================
    ComboBox* presetBox;
    FilenameComponent* fileChooser;
    ImageSlider* gainSlider;
    ImageSlider* panSlider;
    ImageSlider* attackSlider;
    ImageSlider* decaySlider;
    ImageSlider* sustainSlider;
    ImageSlider* releaseSlider;
    ImageSlider* coarseSlider;
    ImageSlider* fineSlider;
    ImageSlider* cutoffSlider;
    ImageSlider* resoSlider;
    ImageSlider* attackModSlider;
    ImageSlider* decayModSlider;
    ImageSlider* sustainModSlider;
    ImageSlider* releaseModSlider;
    ParameterSlider* coarseLfoSlider;
    ParameterSlider* coarseEnvSlider;
    ParameterSlider* filterLfoSlider;
    ParameterSlider* filterEnvSlider;
    ParameterSlider* polySlider;
    ParameterSlider* lfoFreqSlider;
    ParameterSlider* lfoDelaySlider;
    Label* label;
    Label* cpuIndicator;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    SoundCrabMainComponent (const SoundCrabMainComponent&);
    const SoundCrabMainComponent& operator= (const SoundCrabMainComponent&);
};


#endif   // __JUCER_HEADER_SOUNDCRABMAINCOMPONENT_SOUNDCRABMAINCOMPONENT_5D7A1A98__
