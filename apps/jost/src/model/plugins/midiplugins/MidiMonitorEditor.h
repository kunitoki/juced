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

#ifndef __JUCETICE_JOST_MIDIMONITOREDITOR_HEADER__
#define __JUCETICE_JOST_MIDIMONITOREDITOR_HEADER__

#include "../../../Config.h"
#include "../../../HostFilterComponent.h"
#include "../../../ui/plugins/PluginEditorComponent.h"

class MidiMonitorPlugin;


//==============================================================================
/**

    An auto-generated component, created by the Jucer.
    Describe your class and how it works here!

*/
class MidiMonitorEditor  : public PluginEditorComponent,
                           public ButtonListener,
                           public Timer
{
public:

    //==============================================================================
    MidiMonitorEditor (MidiMonitorPlugin* owner_);
    ~MidiMonitorEditor();

    //==============================================================================
    int getPreferredWidth ()                        { return 550; }
    int getPreferredHeight ()                       { return 350; }
    bool isResizable ()                             { return true; }
    void updateParameters ();

    //==============================================================================
    void buttonClicked (Button* buttonThatWasClicked);    
    
    //==============================================================================
    /** @internal */
    void timerCallback ();
    /** @internal */
    void paint (Graphics& g);
    /** @internal */
    void resized();
    //==============================================================================
    juce_UseDebuggingNewOperator

private:

    Colour backgroundColour;
    MidiMonitorPlugin* owner;
	TextEditor* midiOutputEditor;
	TextButton* saveButton;
	TextButton* clearButton;
};


#endif
