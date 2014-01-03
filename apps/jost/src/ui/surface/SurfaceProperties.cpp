/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  22 Feb 2008 2:55:49 pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include "SurfaceObjects.h"
#include "SurfaceComponent.h"
//[/Headers]

#include "SurfaceProperties.h"



//==============================================================================
SurfaceProperties::SurfaceProperties (SurfaceComponent* owner_)
    : owner (owner_),
      pluginCombo (0),
      parameter1Combo (0),
      labelPlugin (0),
      labelParameter1 (0),
      parameter2Combo (0),
      labelParameter2 (0)
{
    addAndMakeVisible (pluginCombo = new ComboBox (String::empty));
    pluginCombo->setEditableText (false);
    pluginCombo->setJustificationType (Justification::centredLeft);
    pluginCombo->setTextWhenNothingSelected (T("(select a plugin)"));
    pluginCombo->setTextWhenNoChoicesAvailable (T("(no plugins available)"));
    pluginCombo->addListener (this);

    addAndMakeVisible (parameter1Combo = new ComboBox (String::empty));
    parameter1Combo->setEditableText (false);
    parameter1Combo->setJustificationType (Justification::centredLeft);
    parameter1Combo->setTextWhenNothingSelected (T("(select a parameter)"));
    parameter1Combo->setTextWhenNoChoicesAvailable (T("(no parameters available)"));
    parameter1Combo->addListener (this);

    addAndMakeVisible (labelPlugin = new Label (String::empty,
                                                T("Plugin")));
    labelPlugin->setFont (Font (11.6000f, Font::plain));
    labelPlugin->setJustificationType (Justification::centredLeft);
    labelPlugin->setEditable (false, false, false);
    labelPlugin->setColour (TextEditor::textColourId, Colours::black);
    labelPlugin->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (labelParameter1 = new Label (String::empty,
                                                    T("Parameter 1")));
    labelParameter1->setFont (Font (11.6000f, Font::plain));
    labelParameter1->setJustificationType (Justification::centredLeft);
    labelParameter1->setEditable (false, false, false);
    labelParameter1->setColour (TextEditor::textColourId, Colours::black);
    labelParameter1->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (parameter2Combo = new ComboBox (String::empty));
    parameter2Combo->setEditableText (false);
    parameter2Combo->setJustificationType (Justification::centredLeft);
    parameter2Combo->setTextWhenNothingSelected (T("(select a parameter)"));
    parameter2Combo->setTextWhenNoChoicesAvailable (T("(no parameters available)"));
    parameter2Combo->addListener (this);

    addAndMakeVisible (labelParameter2 = new Label (String::empty,
                                                    T("Parameter 2")));
    labelParameter2->setFont (Font (11.6000f, Font::plain));
    labelParameter2->setJustificationType (Justification::centredLeft);
    labelParameter2->setEditable (false, false, false);
    labelParameter2->setColour (TextEditor::textColourId, Colours::black);
    labelParameter2->setColour (TextEditor::backgroundColourId, Colour (0x0));

    setSize (600, 400);

    //[Constructor] You can add your own custom stuff here..
    currentObject = 0;
    //[/Constructor]
}

SurfaceProperties::~SurfaceProperties()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (pluginCombo);
    deleteAndZero (parameter1Combo);
    deleteAndZero (labelPlugin);
    deleteAndZero (labelParameter1);
    deleteAndZero (parameter2Combo);
    deleteAndZero (labelParameter2);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SurfaceProperties::paint (Graphics& g)
{
    //[UserPaint] Add your own custom paint stuff here..
    Colour backgroundColour = Config::getInstance ()->getColour ("mainBackground");

    g.setGradientFill (ColourGradient(backgroundColour.brighter (0.25f),
                                      0, 0,
                                      backgroundColour.darker (0.25f),
                                      0, getHeight (),
                                      false));
    g.fillAll ();

    g.setColour (Colours::white.withAlpha (0.2f));
    g.drawLine (0, 0, getWidth (), 0, 1);
    //[/UserPaint]
}

void SurfaceProperties::resized()
{
    pluginCombo->setBounds (116, 4, getWidth() - 124, 16);
    parameter1Combo->setBounds (116, 24, getWidth() - 124, 16);
    labelPlugin->setBounds (4, 3, 104, 18);
    labelParameter1->setBounds (4, 23, 104, 18);
    parameter2Combo->setBounds (116, 44, getWidth() - 124, 16);
    labelParameter2->setBounds (4, 43, 104, 18);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void SurfaceProperties::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    if (currentObject == 0)
        return;
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == pluginCombo)
    {
        //[UserComboBoxCode_pluginCombo] -- add your combo box handling code here..
        fillParametersComboBox ();
        currentObject->setPlugin (pluginCombo->getSelectedId());
        //[/UserComboBoxCode_pluginCombo]
    }
    else if (comboBoxThatHasChanged == parameter1Combo)
    {
        //[UserComboBoxCode_parameter1Combo] -- add your combo box handling code here..
        currentObject->setParameter (0, parameter1Combo->getSelectedId() - 1);
        //[/UserComboBoxCode_parameter1Combo]
    }
    else if (comboBoxThatHasChanged == parameter2Combo)
    {
        //[UserComboBoxCode_parameter2Combo] -- add your combo box handling code here..
        currentObject->setParameter (1, parameter1Combo->getSelectedId() - 1);
        //[/UserComboBoxCode_parameter2Combo]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void SurfaceProperties::setCurrentSurfaceObject (SurfaceObject* object)
{
    if (currentObject != object)
    {
        currentObject = object;
        
        if (currentObject != 0)
        {
            owner->fillPluginComboBox (pluginCombo);
            
            uint32 plugin = currentObject->getPlugin ();
            if (plugin) {
                pluginCombo->setSelectedId (plugin, true);
                fillParametersComboBox ();
            }
        }
        else
        {
            pluginCombo->clear ();
            parameter1Combo->clear ();
            parameter2Combo->clear ();
        }
    }
}

void SurfaceProperties::fillParametersComboBox ()
{
    if (currentObject != 0)
    {
        switch (currentObject->getMaximumParameters ())
        {
        case 0: parameter1Combo->clear ();
                parameter2Combo->clear ();
                parameter1Combo->setEnabled (false);
                parameter2Combo->setEnabled (false);
                break;
        case 1: owner->fillParametersComboBox (parameter1Combo, pluginCombo->getSelectedId ());
                parameter2Combo->clear ();
                parameter1Combo->setEnabled (true);
                parameter2Combo->setEnabled (false);
                parameter1Combo->setSelectedId (currentObject->getParameter (0), true);
                break;
        case 2: owner->fillParametersComboBox (parameter1Combo, pluginCombo->getSelectedId ());
                owner->fillParametersComboBox (parameter2Combo, pluginCombo->getSelectedId ());
                parameter1Combo->setEnabled (true);
                parameter2Combo->setEnabled (true);
                parameter1Combo->setSelectedId (currentObject->getParameter (0), true);
                parameter2Combo->setSelectedId (currentObject->getParameter (1), true);
                break;
        }
    }
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SurfaceProperties" componentName=""
                 parentClasses="public Component" constructorParams="SurfaceComponent* owner_"
                 variableInitialisers="owner (owner_)" snapPixels="4" snapActive="1"
                 snapShown="1" overlayOpacity="0.330000013" fixedSize="1" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffffff"/>
  <COMBOBOX name="" id="dc96db716f2774f8" memberName="pluginCombo" virtualName=""
            pos="116 4 124M 16" editable="0" layout="33" items="" textWhenNonSelected="(select a plugin)"
            textWhenNoItems="(no plugins available)"/>
  <COMBOBOX name="" id="ed5f6404ad678ad8" memberName="parameter1Combo" virtualName=""
            pos="116 24 124M 16" editable="0" layout="33" items="" textWhenNonSelected="(select a parameter)"
            textWhenNoItems="(no parameters available)"/>
  <COMBOBOX name="" id="13517305b0ea6deb" memberName="parameter2Combo" virtualName=""
            pos="116 44 124M 16" editable="0" layout="33" items="" textWhenNonSelected="(select a parameter)"
            textWhenNoItems="(no parameters available)"/>
  <LABEL name="" id="b3a086f2158a322d" memberName="labelPlugin" virtualName=""
         pos="4 3 104 18" edTextCol="ff000000" edBkgCol="0" labelText="Plugin"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="11.6" bold="0" italic="0" justification="33"/>
  <LABEL name="" id="3a571b0e335034b" memberName="labelParameter1" virtualName=""
         pos="4 23 104 18" edTextCol="ff000000" edBkgCol="0" labelText="Parameter 1"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="11.6" bold="0" italic="0" justification="33"/>
  <LABEL name="" id="11f6bc28786f778a" memberName="labelParameter2" virtualName=""
         pos="4 43 104 18" edTextCol="ff000000" edBkgCol="0" labelText="Parameter 2"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="11.6" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
