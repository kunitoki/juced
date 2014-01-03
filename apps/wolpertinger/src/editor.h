/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  8 Aug 2009 12:26:56 pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_EDITOR_EDITOR_C20B912A__
#define __JUCER_HEADER_EDITOR_EDITOR_C20B912A__

//[Headers]     -- You can add your own extra header files here --
#include "StandardHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class editor  : public AudioProcessorEditor,
                public ChangeListener,
                public SliderListener
{
public:
    //==============================================================================
    editor (AudioProcessor *const ownerFilter);
    ~editor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void changeListenerCallback(void *objectThatHasChanged);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    GroupComponent* groupComponent2;
    GroupComponent* groupComponent;
    Label* label;
    Label* label2;
    Slider* slgain;
    Slider* slclip;
    Slider* slsaw;
    Label* label3;
    Slider* slrect;
    Label* label4;
    Slider* sltri;
    Label* label5;
    Slider* sltune;
    Label* label6;
    GroupComponent* groupComponent3;
    Label* label7;
    Slider* slcutoff;
    Label* label8;
    Slider* slreso;
    Label* label9;
    Slider* slbandwidth;
    Label* label10;
    Slider* slpasses;
    Label* label11;
    Slider* slvelocity;
    Label* label12;
    Slider* slinertia;
    Label* label13;
    Slider* slcurcutoff;
    Label* label14;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    editor (const editor&);
    const editor& operator= (const editor&);
};


#endif   // __JUCER_HEADER_EDITOR_EDITOR_C20B912A__
