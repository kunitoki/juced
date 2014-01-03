/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2008 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2008 by Julian Storer.

 ------------------------------------------------------------------------------

 JUCE and JUCETICE can be redistributed and/or modified under the terms of
 the GNU Lesser General Public License, as published by the Free Software
 Foundation; either version 2 of the License, or (at your option) any later
 version.

 JUCE and JUCETICE are distributed in the hope that they will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with JUCE and JUCETICE; if not, visit www.gnu.org/licenses or write to
 Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 Boston, MA 02111-1307 USA

 ==============================================================================

   @author  rockhardbuns
   @tweaker Lucio Asnaghi

 ==============================================================================
*/

#ifndef __JUCETICE_VEXPEGGYVIEWCOMPONENT_HEADER__
#define __JUCETICE_VEXPEGGYVIEWCOMPONENT_HEADER__

#include "VexFilter.h"
#include "PeggySettings.h"
#include "gui/BoolGridComponent.h"
#include "gui/SliderFieldComponent.h"


class PeggyViewComponent :	public Component,
							public SliderListener,
							public ComboBoxListener,
							public ChangeListener,
							public ButtonListener
{
public:

	PeggyViewComponent(VexFilter* f, int partID)
	{
		filter = f;
		part = partID;

		myPeggySet = filter->getPeggySet(part);

		addAndMakeVisible(boolGrid = new BoolGridComponent());
		boolGrid->addChangeListener (this);

		addAndMakeVisible(sliderField = new SliderFieldComponent());
		sliderField->addChangeListener (this);

		addAndMakeVisible(length = new Slider(T("sdf")));
		length->setRange(1, 16, 1);
		length->setTextBoxStyle(Slider::NoTextBox, true, 0, 0 );
		length->addListener(this);
		length->setValue(8);

		addAndMakeVisible(timeMode = new ComboBox(T("a")));
		timeMode->setEditableText (false);
		timeMode->setJustificationType (Justification::centredLeft);
		timeMode->setTextWhenNothingSelected (String(T("_")));
		timeMode->setTextWhenNoChoicesAvailable (String(T("_")));
		timeMode->setColour(ComboBox::backgroundColourId, Colours::black);
		timeMode->setColour(ComboBox::textColourId, Colours::lightgrey);
		timeMode->setColour(ComboBox::outlineColourId, Colours::grey);
		timeMode->setColour(ComboBox::buttonColourId, Colours::grey);
		timeMode->setWantsKeyboardFocus(false);
		timeMode->addItem(T("1/8"),  1);
		timeMode->addItem(T("1/16"), 2);
		timeMode->addItem(T("1/32"), 3);
		timeMode->setSelectedId(2);
		timeMode->addListener (this);

		addAndMakeVisible(syncMode = new ComboBox(T("a")));
		syncMode->setEditableText (false);
		syncMode->setJustificationType (Justification::centredLeft);
		syncMode->setTextWhenNothingSelected (String(T("_")));
		syncMode->setTextWhenNoChoicesAvailable (String(T("_")));
		syncMode->setColour(ComboBox::backgroundColourId, Colours::black);
		syncMode->setColour(ComboBox::textColourId, Colours::lightgrey);
		syncMode->setColour(ComboBox::outlineColourId, Colours::grey);
		syncMode->setColour(ComboBox::buttonColourId, Colours::grey);
		syncMode->setWantsKeyboardFocus(false);
		syncMode->addItem(T("Key Sync"), 1);
		syncMode->addItem(T("Bar Sync"), 2);
		syncMode->setSelectedId(1);
		syncMode->addListener (this);

		addAndMakeVisible(failMode = new ComboBox(T("a")));
		failMode->setEditableText (false);
		failMode->setJustificationType (Justification::centredLeft);
		failMode->setTextWhenNothingSelected (String(T("_")));
		failMode->setTextWhenNoChoicesAvailable (String(T("_")));
		failMode->setColour(ComboBox::backgroundColourId, Colours::black);
		failMode->setColour(ComboBox::textColourId, Colours::lightgrey);
		failMode->setColour(ComboBox::outlineColourId, Colours::grey);
		failMode->setColour(ComboBox::buttonColourId, Colours::grey);
		failMode->setWantsKeyboardFocus(false);
		failMode->addItem(T("Silent Step"),		1);
		failMode->addItem(T("Skip One"),		2);
		failMode->addItem(T("Skip Two"),		3);
		failMode->setSelectedId(1);
		failMode->addListener (this);


		addAndMakeVisible(velMode = new ComboBox(T("a")));
		velMode->setEditableText (false);
		velMode->setJustificationType (Justification::centredLeft);
		velMode->setTextWhenNothingSelected (String(T("_")));
		velMode->setTextWhenNoChoicesAvailable (String(T("_")));
		velMode->setColour(ComboBox::backgroundColourId, Colours::black);
		velMode->setColour(ComboBox::textColourId, Colours::lightgrey);
		velMode->setColour(ComboBox::outlineColourId, Colours::grey);
		velMode->setColour(ComboBox::buttonColourId, Colours::grey);
		velMode->setWantsKeyboardFocus(false);
		velMode->addItem(T("Pattern Velocity"),	1);
		velMode->addItem(T("Input Velocity"),	2);
		velMode->addItem(T("Sum Velocities"),	3);
		velMode->setSelectedId(1);
		velMode->addListener (this);

		
		addAndMakeVisible (onOffBtn = new ToggleButton (T("new button")));
		onOffBtn->setButtonText (String(T("On")));
		onOffBtn->addButtonListener (this);
		onOffBtn->setClickingTogglesState(true);
		onOffBtn->setToggleState(false,false);

	}
	~PeggyViewComponent()
	{
		deleteAllChildren();
	}
	void resized()
	{
		boolGrid->setBounds (5, 5, 193, 63);
		sliderField->setBounds (5, 68, 193, 63);
		length->setBounds (4, 140, 194, 16);
		timeMode->setBounds(6,   160, 93, 23);
		syncMode->setBounds(102, 160, 93, 23);
		failMode->setBounds(6,  190, 189, 23);
		velMode-> setBounds(6,  220, 189, 23);

		onOffBtn->setBounds(6, 250, 60, 24);
	}
	void paint (Graphics& g)
	{	
		g.setColour(Colours::black.withAlpha(.5f));
		g.fillRect(5,5,getWidth(), getHeight());

		g.setGradientFill (ColourGradient(Colour(0xffffffff), 0.0f, 0.0f,
                                          Colour(0xff888899), (float)getWidth(), (float)getHeight(),
							              false));

		g.fillRect(0,0,getWidth() - 5, getHeight() - 5);

		g.setColour(Colours::black);
		g.drawRect(0,0,getWidth() - 5, getHeight() - 5);
	}
	void changeListenerCallback (void* caller)
	{
		if(caller == boolGrid)
		{
			int i = boolGrid->getLastChanged();
			myPeggySet->grid[i] = boolGrid->getCellState(i);
			return;
		}

		if(caller == sliderField)
		{
			int i = sliderField->getLastSlider();
			myPeggySet->velocities[i] = sliderField->getValue(i);
			return;
		}
	}
	void comboBoxChanged (ComboBox* caller)
	{
		if(caller == timeMode) myPeggySet->timeMode = timeMode->getSelectedId();
		if(caller == syncMode) myPeggySet->syncMode = syncMode->getSelectedId();
		if(caller == failMode) myPeggySet->failMode = failMode->getSelectedId();
		if(caller == velMode)  myPeggySet->velMode =  velMode->getSelectedId();
	}
	void sliderValueChanged (Slider* caller)
	{
		boolGrid->setLength((int)length->getValue());
		sliderField->setLength((int)length->getValue());
		myPeggySet->length = (int)length->getValue();
	}
	void buttonClicked (Button* buttonThatWasClicked)
	{
		myPeggySet->on = onOffBtn->getToggleState();
	}

	void update()
	{	
		DBG("Updating PeggyView");
		myPeggySet = filter->getPeggySet(part);
		onOffBtn->setToggleState(myPeggySet->on, false);

		sliderField->setLength(myPeggySet->length);
		boolGrid->setLength(myPeggySet->length);
		for(int i = 0; i < 16; i++)
		{
			sliderField->setValue(i, myPeggySet->velocities[i]);
		}
		for(int i = 0; i < 80; i++)
		{
			boolGrid->setCellState(i, myPeggySet->grid[i]);
		}
		timeMode->setSelectedId(myPeggySet->timeMode);
		syncMode->setSelectedId(myPeggySet->syncMode);
		failMode->setSelectedId(myPeggySet->failMode);
		velMode->setSelectedId(myPeggySet->velMode);
	}

private:

	BoolGridComponent* boolGrid;
	SliderFieldComponent* sliderField;

	VexFilter* filter;

	ComboBox* timeMode;
	ComboBox* syncMode;
	ComboBox* failMode;
	ComboBox* velMode;

	ToggleButton* onOffBtn;
	Slider* length;
	int part;
	peggySettings* myPeggySet;

};


#endif
