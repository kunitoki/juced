/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  18 Jan 2010 2:20:35 pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_MIDIKEYBOARDEDITOR_MIDIKEYBOARDEDITOR_5A1BA855__
#define __JUCER_HEADER_MIDIKEYBOARDEDITOR_MIDIKEYBOARDEDITOR_5A1BA855__

//[Headers]     -- You can add your own extra header files here --
#include "../../../Config.h"
#include "../../../HostFilterComponent.h"
#include "../../../ui/plugins/PluginEditorComponent.h"

class MidiKeyboardPlugin;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MidiKeyboardEditor  : public PluginEditorComponent,
                            public SliderListener,
                            public ComboBoxListener,
                            public ButtonListener
{
public:
    //==============================================================================
    MidiKeyboardEditor (MidiKeyboardPlugin* owner_);
    ~MidiKeyboardEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

    int getPreferredWidth ()                        { return 696; }
    int getPreferredHeight ()                       { return 200; }
    bool isResizable ()                             { return false; }
    void updateParameters ();

    void addControllerMessage (const int controllerNumber,
                               const int controllerValue);

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void buttonClicked (Button* buttonThatWasClicked);
    bool keyPressed (const KeyPress& key);


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    MidiKeyboardPlugin* owner;
    MidiKeyboardComponent* keyboardComponent;
    int midiChannel;
    //[/UserVariables]

    //==============================================================================
    Slider* slPitchBend;
    ComboBox* cmbChannel;
    Label* lbChannel;
    Slider* slVelocity;
    GroupComponent* grControllers;
    ToggleButton* btnTranspose;
    Slider* slTranspose;
    Slider* slVolume;
    Label* lbController;
    Slider* slController1;
    Slider* slController2;
    Slider* slController3;
    Slider* slController4;
    Slider* slController5;
    Slider* slController6;
    Slider* slController7;
    Slider* slController8;
    Label* lbController2;
    Label* lbController3;
    Label* lbController4;
    Label* lbController5;
    Label* lbController6;
    Label* lbController7;
    Label* lbController8;
    Label* lbController9;
    Slider* slModWheel;
    Slider* slBendRange;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    MidiKeyboardEditor (const MidiKeyboardEditor&);
    const MidiKeyboardEditor& operator= (const MidiKeyboardEditor&);
};


#endif   // __JUCER_HEADER_MIDIKEYBOARDEDITOR_MIDIKEYBOARDEDITOR_5A1BA855__
