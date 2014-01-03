/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  27 Jul 2008 12:24:04 pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.11

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_MIDIPADSEDITOR_MIDIPADSEDITOR_HEADER__
#define __JUCER_HEADER_MIDIPADSEDITOR_MIDIPADSEDITOR_HEADER__

#include "../../../Config.h"
#include "../../../HostFilterComponent.h"
#include "../../../ui/plugins/PluginEditorComponent.h"

#include "MidiPads.h"


class MidiPadsPluginEditor   : public PluginEditorComponent,
                               public ChangeListener,
                               public ButtonListener,
                               public SliderListener,
                               public TextEditorListener
                              
{
public:

    //==============================================================================
    MidiPadsPluginEditor (MidiPadsPlugin* owner);
    ~MidiPadsPluginEditor ();

    //==============================================================================
    int getPreferredWidth ();
    int getPreferredHeight ();
    bool isResizable ();
    void updateParameters ();

    //==============================================================================
    void changeListenerCallback (void* source);

    void buttonClicked (Button*);
    void buttonStateChanged (Button*);
    void sliderValueChanged (Slider*);

    //==============================================================================
    /** @internal */
    void textEditorTextChanged(TextEditor&);
    /** @internal */
    void textEditorReturnKeyPressed(TextEditor&);
    /** @internal */
    void textEditorEscapeKeyPressed(TextEditor&);
    /** @internal */
    void textEditorFocusLost(TextEditor&);
    /** @internal */
    void mouseDrag (const MouseEvent&);
    /** @internal */
    void mouseUp (const MouseEvent&);
    /** @internal */
    void paint (Graphics&);
    /** @internal */
    void resized ();

    //==============================================================================
    juce_UseDebuggingNewOperator

private:

    //==============================================================================
    void updateParametersFromFilter();
    void padTriggered();
    void dotMoved(int pad);
    void sendMidi(int i, bool shiftclicked=false);
    void sendMidiOff(int i);

    //==============================================================================
    Drawable* createImageFromZipFile (const String& filename);

    //==============================================================================
    MidiPadsPlugin* owner;

    ColourSelector* colourSelector1[numPads];
    MidiPad* midiPad[numPads];
    Slider* vSlider[numPads];
    Slider* nSlider[numPads];
    Slider* ySlider[numPads];
    Slider* oSlider[numPads];
    Slider* triggerSlider[numPads];
    Slider* xSlider[numPads];
    Slider* xoSlider[numPads];
    Slider* cSlider;
    Slider* icSlider;
    Slider* slider;
    Slider* slider2;
    Slider* slider3;
    Slider* slider4;
    Slider* slider5;
    Slider* velocitySlider;
    Slider* valueSlider;
    TextEditor* textEditor[numPads];
    TextButton* menuButton;
    TooltipWindow tooltipWindow;

    StringArray iconNames;
    OwnedArray<Drawable> iconsFromZipFile;

    Colour color, color2;
    int lastx[numPads];
    int lasty[numPads];
    int squares;
    bool showdots;
    bool toggled[numPads];
    bool dontsend;
};


#endif
