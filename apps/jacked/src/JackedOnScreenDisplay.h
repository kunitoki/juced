/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  15 Aug 2008 11:58:19 am

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.11

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_JACKEDONSCREENDISPLAY_JACKEDONSCREENDISPLAY_8FD00CB2__
#define __JUCER_HEADER_JACKEDONSCREENDISPLAY_JACKEDONSCREENDISPLAY_8FD00CB2__

//[Headers]     -- You can add your own extra header files here --
#include "juce.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class JackedOnScreenDisplay  : public Component,
                               public ButtonListener
{
public:
    //==============================================================================
    JackedOnScreenDisplay ();
    ~JackedOnScreenDisplay();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void moved();
    void mouseDown (const MouseEvent& e);
    void mouseDrag (const MouseEvent& e);
    void mouseUp (const MouseEvent& e);


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    ComponentDragger dragger;
    //[/UserVariables]

    //==============================================================================
    TextButton* playButton;
    TextButton* stopButton;
    Label* cpuUsage;
    TextButton* connectionButton;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    JackedOnScreenDisplay (const JackedOnScreenDisplay&);
    const JackedOnScreenDisplay& operator= (const JackedOnScreenDisplay&);
};


#endif   // __JUCER_HEADER_JACKEDONSCREENDISPLAY_JACKEDONSCREENDISPLAY_8FD00CB2__
