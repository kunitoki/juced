/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  18 Jan 2010 2:17:20 pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_MIDIFILTEREDITOR_MIDIFILTEREDITOR_EDC0958D__
#define __JUCER_HEADER_MIDIFILTEREDITOR_MIDIFILTEREDITOR_EDC0958D__

//[Headers]     -- You can add your own extra header files here --
#include "../../../Config.h"
#include "../../../HostFilterComponent.h"
#include "../../../ui/plugins/PluginEditorComponent.h"

class MidiFilterPlugin;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MidiFilterEditor  : public PluginEditorComponent,
                          public ButtonListener,
                          public SliderListener
{
public:
    //==============================================================================
    MidiFilterEditor (MidiFilterPlugin* owner_);
    ~MidiFilterEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

    int getPreferredWidth ()                        { return 696; }
    int getPreferredHeight ()                       { return 200; }
    bool isResizable ()                             { return false; }
    void updateParameters ();

    void channelButtonClicked (ParameterLedButton* button, const int channel);

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void sliderValueChanged (Slider* sliderThatWasMoved);


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    MidiFilterPlugin* owner;
    //[/UserVariables]

    //==============================================================================
    Label* channelLabel;
    ParameterLedButton* channelButton1;
    ParameterLedButton* channelButton2;
    ParameterLedButton* channelButton3;
    ParameterLedButton* channelButton4;
    ParameterLedButton* channelButton5;
    ParameterLedButton* channelButton6;
    ParameterLedButton* channelButton7;
    ParameterLedButton* channelButton8;
    ParameterLedButton* channelButton9;
    ParameterLedButton* channelButton10;
    ParameterLedButton* channelButton11;
    ParameterLedButton* channelButton12;
    ParameterLedButton* channelButton13;
    ParameterLedButton* channelButton14;
    ParameterLedButton* channelButton15;
    ParameterLedButton* channelButton16;
    ToggleButton* channelToggle;
    ToggleButton* noteToggle;
    Label* noteLabel;
    ToggleButton* velocityToggle;
    Label* velocityLabel;
    Slider* noteSlider;
    TextButton* channelToggleButton;
    Slider* velocitySlider;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    MidiFilterEditor (const MidiFilterEditor&);
    const MidiFilterEditor& operator= (const MidiFilterEditor&);
};


#endif   // __JUCER_HEADER_MIDIFILTEREDITOR_MIDIFILTEREDITOR_EDC0958D__
