/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  18 Jan 2010 11:32:46 am

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include "../XSynthEditor.h"
//[/Headers]

#include "XSynthOptions.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
XSynthOptions::XSynthOptions ()
    : globalGroup (0),
      keysVisible (0)
{
    addAndMakeVisible (globalGroup = new GroupComponent (String::empty,
                                                         T("Global Options")));
    globalGroup->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    globalGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (keysVisible = new ToggleButton (String::empty));
    keysVisible->setButtonText (T("Midi keyboard visible"));
    keysVisible->addButtonListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (680, 400);

    //[Constructor] You can add your own custom stuff here..
    Config* config = Config::getInstance ();

    keysVisible->setToggleState (config->IsKeyboardVisible == 1, false);
    //[/Constructor]
}

XSynthOptions::~XSynthOptions()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (globalGroup);
    deleteAndZero (keysVisible);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void XSynthOptions::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff827474));

    g.setGradientFill (ColourGradient (Colour (0xff827474),
                                       330.0f, 390.0f,
                                       Colours::black,
                                       330.0f, 410.0f,
                                       false));
    g.fillRect (0, 370, 680, 30);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void XSynthOptions::resized()
{
    globalGroup->setBounds (10, 10, 660, 380);
    keysVisible->setBounds (30, 40, 150, 20);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void XSynthOptions::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == keysVisible)
    {
        //[UserButtonCode_keysVisible] -- add your button handler code here..
        XSynthEditor* editor = findParentComponentOfClass <XSynthEditor> ();
        if (editor != 0)
            editor->setKeyboardVisible (buttonThatWasClicked->getToggleState());
        //[/UserButtonCode_keysVisible]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="XSynthOptions" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="10" snapActive="1" snapShown="0" overlayOpacity="0.330000013"
                 fixedSize="1" initialWidth="680" initialHeight="400">
  <BACKGROUND backgroundColour="ff827474">
    <RECT pos="0 370 680 30" fill="linear: 330 390, 330 410, 0=ff827474, 1=ff000000"
          hasStroke="0"/>
  </BACKGROUND>
  <GROUPCOMPONENT name="" id="225f3f52138da9f4" memberName="globalGroup" virtualName=""
                  explicitFocusOrder="0" pos="10 10 660 380" outlinecol="66ffffff"
                  textcol="ffffffff" title="Global Options"/>
  <TOGGLEBUTTON name="" id="a1c30c166bc0503b" memberName="keysVisible" virtualName=""
                explicitFocusOrder="0" pos="30 40 150 20" buttonText="Midi keyboard visible"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
