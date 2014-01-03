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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "JackedOnScreenDisplay.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
JackedOnScreenDisplay::JackedOnScreenDisplay ()
    : playButton (0),
      stopButton (0),
      cpuUsage (0),
      connectionButton (0)
{
    addAndMakeVisible (playButton = new TextButton (String::empty));
    playButton->setButtonText (T("play"));
    playButton->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    playButton->addButtonListener (this);
    playButton->setColour (TextButton::buttonColourId, Colour (0xff25d589));

    addAndMakeVisible (stopButton = new TextButton (String::empty));
    stopButton->setButtonText (T("stop"));
    stopButton->setConnectedEdges (Button::ConnectedOnLeft);
    stopButton->addButtonListener (this);
    stopButton->setColour (TextButton::buttonColourId, Colour (0xffe14b45));

    addAndMakeVisible (cpuUsage = new Label (String::empty,
                                             T("90%\n\n")));
    cpuUsage->setFont (Font (15.0000f, Font::bold));
    cpuUsage->setJustificationType (Justification::centredRight);
    cpuUsage->setEditable (false, false, false);
    cpuUsage->setColour (TextEditor::textColourId, Colours::black);
    cpuUsage->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (connectionButton = new TextButton (String::empty));
    connectionButton->setButtonText (T("conn"));
    connectionButton->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    connectionButton->addButtonListener (this);
    connectionButton->setColour (TextButton::buttonColourId, Colour (0xffa6a6a6));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (188, 24);

    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

JackedOnScreenDisplay::~JackedOnScreenDisplay()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (playButton);
    deleteAndZero (stopButton);
    deleteAndZero (cpuUsage);
    deleteAndZero (connectionButton);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void JackedOnScreenDisplay::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff959595));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void JackedOnScreenDisplay::resized()
{
    playButton->setBounds (40, 0, 40, 24);
    stopButton->setBounds (80, 0, 40, 24);
    cpuUsage->setBounds (120, 0, 48, 24);
    connectionButton->setBounds (0, 0, 40, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void JackedOnScreenDisplay::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == playButton)
    {
        //[UserButtonCode_playButton] -- add your button handler code here..
        //[/UserButtonCode_playButton]
    }
    else if (buttonThatWasClicked == stopButton)
    {
        //[UserButtonCode_stopButton] -- add your button handler code here..
        //[/UserButtonCode_stopButton]
    }
    else if (buttonThatWasClicked == connectionButton)
    {
        //[UserButtonCode_connectionButton] -- add your button handler code here..
        //[/UserButtonCode_connectionButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void JackedOnScreenDisplay::moved()
{
    //[UserCode_moved] -- Add your code here...
    //[/UserCode_moved]
}

void JackedOnScreenDisplay::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
    if (e.mods.isLeftButtonDown())
        dragger.startDraggingComponent (this, 0);
    //[/UserCode_mouseDown]
}

void JackedOnScreenDisplay::mouseDrag (const MouseEvent& e)
{
    //[UserCode_mouseDrag] -- Add your code here...
    if (e.mods.isLeftButtonDown())
        dragger.dragComponent (this, e);
    //[/UserCode_mouseDrag]
}

void JackedOnScreenDisplay::mouseUp (const MouseEvent& e)
{
    //[UserCode_mouseUp] -- Add your code here...
    //[/UserCode_mouseUp]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="JackedOnScreenDisplay" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.329999983"
                 fixedSize="1" initialWidth="188" initialHeight="24">
  <METHODS>
    <METHOD name="moved()"/>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
    <METHOD name="mouseDrag (const MouseEvent&amp; e)"/>
    <METHOD name="mouseUp (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ff959595"/>
  <TEXTBUTTON name="" id="4c258a1c21b5cda3" memberName="playButton" virtualName=""
              explicitFocusOrder="0" pos="40 0 40 24" bgColOff="ff25d589" buttonText="play"
              connectedEdges="3" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="7c891a1769469f8c" memberName="stopButton" virtualName=""
              explicitFocusOrder="0" pos="80 0 40 24" bgColOff="ffe14b45" buttonText="stop"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <LABEL name="" id="cb6ae84a0946f1a7" memberName="cpuUsage" virtualName=""
         explicitFocusOrder="0" pos="120 0 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="90%&#10;&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="1" italic="0" justification="34"/>
  <TEXTBUTTON name="" id="d0b255412569d37e" memberName="connectionButton" virtualName=""
              explicitFocusOrder="0" pos="0 0 40 24" bgColOff="ffa6a6a6" buttonText="conn"
              connectedEdges="3" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
