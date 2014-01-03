/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  18 Jan 2010 2:13:56 pm

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
#include "../XImpulseComponent.h"
//[/Headers]

#include "XImpulseMainComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
XImpulseMainComponent::XImpulseMainComponent (XImpulseComponent* const editor_, XImpulsePlugin* const plugin_)
    : editor (editor_),
      plugin (plugin_),
      presetBox (0),
      fileChooser (0),
      label (0)
{
    addAndMakeVisible (presetBox = new ComboBox (String::empty));
    presetBox->setEditableText (false);
    presetBox->setJustificationType (Justification::centredLeft);
    presetBox->setTextWhenNothingSelected (T("(no preset selected)"));
    presetBox->setTextWhenNoChoicesAvailable (T("(no presets available)"));
    presetBox->addListener (this);

    addAndMakeVisible (fileChooser = new FilenameComponent (T("impulse response"),
                                                            File::nonexistent,
                                                            true, false, false,
                                                            T("*.wav"),
                                                            String::empty,
                                                            T("(choose a IR file)")));

    addAndMakeVisible (label = new Label (T("new label"),
                                          T("v0.1.1")));
    label->setFont (Font (11.2000f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x0));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (480, 80);

    //[Constructor] You can add your own custom stuff here..
    String pluginVersion;
    pluginVersion << T("v") << T(JucePlugin_VersionString);
    label->setText (pluginVersion, false);

//    fileChooser->setDefaultBrowseTarget (config->lastSoundfontDirectory);
//    fileChooser->setRecentlyUsedFilenames (config->recentSoundfonts.getAllFilenames());
    fileChooser->setBrowseButtonText (T("browse"));
    fileChooser->addListener (this);

#if 0
    plugin->getParameterLock().enter ();
        plugin->addListenerToParameter (PAR_GAIN, gainSlider);
    plugin->getParameterLock().exit ();
#endif

    updateControls ();
    //[/Constructor]
}

XImpulseMainComponent::~XImpulseMainComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
#if 0
    plugin->getParameterLock().enter ();
        plugin->removeListenerToParameter (PAR_GAIN, gainSlider);
    plugin->getParameterLock().exit ();
#endif
    //[/Destructor_pre]

    deleteAndZero (presetBox);
    deleteAndZero (fileChooser);
    deleteAndZero (label);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void XImpulseMainComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.setGradientFill (ColourGradient (Colour (0xff596e88),
                                       221.0f, 57.0f,
                                       Colour (0xffb9c6dc),
                                       221.0f, 12.0f,
                                       false));
    g.fillRect (0, 0, 480, 67);

    g.setGradientFill (ColourGradient (Colour (0xff596e88),
                                       235.0f, 67.0f,
                                       Colours::black,
                                       235.0f, 82.0f,
                                       false));
    g.fillRect (0, 67, 480, 13);

    g.setColour (Colour (0xff2e3538));
    g.setFont (Font (24.2000f, Font::bold));
    g.drawText (T("IMPULZR"),
                1, 2, 106, 19,
                Justification::centred, true);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void XImpulseMainComponent::resized()
{
    presetBox->setBounds (5, 47, 470, 18);
    fileChooser->setBounds (5, 24, 470, 18);
    label->setBounds (439, 4, 36, 13);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void XImpulseMainComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == presetBox)
    {
        //[UserComboBoxCode_presetBox] -- add your combo box handling code here..
        // plugin->setCurrentAbsolutePreset (presetBox->getSelectedId ());
        //[/UserComboBoxCode_presetBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void XImpulseMainComponent::filesDropped (const StringArray& filenames, int mouseX, int mouseY)
{
    //[UserCode_filesDropped] -- Add your code here...
    if (filenames.size() > 0)
        loadImpulseResponse (filenames [0]);
    //[/UserCode_filesDropped]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//==============================================================================
void XImpulseMainComponent::filenameComponentChanged (FilenameComponent*)
{
    loadImpulseResponse (fileChooser->getCurrentFile());
}

//==============================================================================
void XImpulseMainComponent::updateControls ()
{
    // update file choose
    fileChooser->setCurrentFile (plugin->getCurrentImpulseResponse (),
                                 true,
                                 false);

/*
    // update sliders
    gainSlider->setValue (plugin->getParameter (PAR_GAIN), false);
    panSlider->setValue (plugin->getParameter (PAR_PAN), false);
*/
}

bool XImpulseMainComponent::loadImpulseResponse (const File& irFile)
{
    if (irFile.existsAsFile ())
    {
        plugin->loadImpulseResponse (irFile);

        return true;
    }

    return false;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="XImpulseMainComponent" componentName=""
                 parentClasses="public Component, public FilenameComponentListener"
                 constructorParams="XImpulseComponent* const editor_, XImpulsePlugin* const plugin_"
                 variableInitialisers="editor (editor_),&#10;plugin (plugin_)" snapPixels="8"
                 snapActive="0" snapShown="1" overlayOpacity="0.330000013" fixedSize="1"
                 initialWidth="480" initialHeight="80">
  <METHODS>
    <METHOD name="filesDropped (const StringArray&amp; filenames, int mouseX, int mouseY)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ffffff">
    <RECT pos="0 0 480 67" fill="linear: 221 57, 221 12, 0=ff596e88, 1=ffb9c6dc"
          hasStroke="0"/>
    <RECT pos="0 67 480 13" fill="linear: 235 67, 235 82, 0=ff596e88, 1=ff000000"
          hasStroke="0"/>
    <TEXT pos="1 2 106 19" fill="solid: ff2e3538" hasStroke="0" text="IMPULZR"
          fontname="Default font" fontsize="24.2" bold="1" italic="0" justification="36"/>
  </BACKGROUND>
  <COMBOBOX name="" id="fff8c82083bf2e04" memberName="presetBox" virtualName=""
            explicitFocusOrder="0" pos="5 47 470 18" editable="0" layout="33"
            items="" textWhenNonSelected="(no preset selected)" textWhenNoItems="(no presets available)"/>
  <GENERICCOMPONENT name="" id="f0a225bf2015810d" memberName="fileChooser" virtualName=""
                    explicitFocusOrder="0" pos="5 24 470 18" class="FilenameComponent"
                    params="T(&quot;impulse response&quot;),&#10;File::nonexistent,&#10;true, false, false,&#10;T(&quot;*.wav&quot;),&#10;String::empty,&#10;T(&quot;(choose a IR file)&quot;)"/>
  <LABEL name="new label" id="2dc5acc563ebd2bc" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="439 4 36 13" edTextCol="ff000000"
         edBkgCol="0" labelText="v0.1.1" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="11.2"
         bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
