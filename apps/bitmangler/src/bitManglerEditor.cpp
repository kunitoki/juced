/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  18 Jan 2010 11:19:40 am

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
//[/Headers]

#include "bitManglerEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
bitManglerEditor::bitManglerEditor (DemoJuceFilter* const ownerFilter)
    : AudioProcessorEditor (ownerFilter),
      andBitMod (0),
      xorBitMod (0),
      bitDisplayInput (0),
      bitDisplayOutput (0),
      processButton (0),
      andRange (0),
      xorRange (0),
      clearRange (0),
      setRange (0),
      xorToggle (0),
      andToggle (0),
      clearToggle (0),
      setToggle (0),
      xorSlider (0),
      andSlider (0),
      clearSlider (0),
      setSlider (0),
      cachedImage_metal2_png (0)
{
    addAndMakeVisible (andBitMod = new ToggleButton (T("new toggle button")));
    andBitMod->setButtonText (T("mod"));
    andBitMod->addButtonListener (this);
    andBitMod->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (xorBitMod = new ToggleButton (T("new toggle button")));
    xorBitMod->setButtonText (T("mod"));
    xorBitMod->addButtonListener (this);
    xorBitMod->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (bitDisplayInput = new Label (T("Bit Display"),
                                                    T("0")));
    bitDisplayInput->setFont (Font (Font::getDefaultMonospacedFontName(), 16.0000f, Font::bold));
    bitDisplayInput->setJustificationType (Justification::centred);
    bitDisplayInput->setEditable (false, false, false);
    bitDisplayInput->setColour (Label::backgroundColourId, Colour (0xffffff));
    bitDisplayInput->setColour (Label::textColourId, Colour (0xff2eff3a));
    bitDisplayInput->setColour (Label::outlineColourId, Colour (0x0));
    bitDisplayInput->setColour (TextEditor::textColourId, Colours::black);
    bitDisplayInput->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (bitDisplayOutput = new Label (T("Bit Display"),
                                                     T("0")));
    bitDisplayOutput->setFont (Font (Font::getDefaultMonospacedFontName(), 16.0000f, Font::bold));
    bitDisplayOutput->setJustificationType (Justification::centred);
    bitDisplayOutput->setEditable (false, false, false);
    bitDisplayOutput->setColour (Label::backgroundColourId, Colour (0xffffff));
    bitDisplayOutput->setColour (Label::textColourId, Colour (0xfffa8b8b));
    bitDisplayOutput->setColour (Label::outlineColourId, Colour (0x0));
    bitDisplayOutput->setColour (TextEditor::textColourId, Colours::black);
    bitDisplayOutput->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (processButton = new ImageButton (T("Process")));
    processButton->setButtonText (T("new button"));
    processButton->addButtonListener (this);

    processButton->setImages (false, true, true,
                              ImageCache::getFromMemory (power_off_png, power_off_pngSize), 0.8428f, Colour (0x0),
                              0, 1.0000f, Colour (0x0),
                              ImageCache::getFromMemory (power_on_png, power_on_pngSize), 1.0000f, Colour (0x0));
    addAndMakeVisible (andRange = new Label (T("new label"),
                                             T("1-1")));
    andRange->setFont (Font (10.0000f, Font::bold));
    andRange->setJustificationType (Justification::centred);
    andRange->setEditable (false, false, false);
    andRange->setColour (Label::textColourId, Colours::white);
    andRange->setColour (TextEditor::textColourId, Colours::black);
    andRange->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (xorRange = new Label (T("new label"),
                                             T("1-1")));
    xorRange->setFont (Font (10.0000f, Font::bold));
    xorRange->setJustificationType (Justification::centred);
    xorRange->setEditable (false, false, false);
    xorRange->setColour (Label::textColourId, Colours::white);
    xorRange->setColour (TextEditor::textColourId, Colours::black);
    xorRange->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (clearRange = new Label (T("new label"),
                                               T("1-1")));
    clearRange->setFont (Font (10.0000f, Font::bold));
    clearRange->setJustificationType (Justification::centred);
    clearRange->setEditable (false, false, false);
    clearRange->setColour (Label::textColourId, Colours::white);
    clearRange->setColour (TextEditor::textColourId, Colours::black);
    clearRange->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (setRange = new Label (T("new label"),
                                             T("1-1")));
    setRange->setFont (Font (10.0000f, Font::bold));
    setRange->setJustificationType (Justification::centred);
    setRange->setEditable (false, false, false);
    setRange->setColour (Label::textColourId, Colours::white);
    setRange->setColour (TextEditor::textColourId, Colours::black);
    setRange->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (xorToggle = new ToggleButton (T("new toggle button")));
    xorToggle->setButtonText (T("XOR"));
    xorToggle->addButtonListener (this);
    xorToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (andToggle = new ToggleButton (T("new toggle button")));
    andToggle->setButtonText (T("AND"));
    andToggle->addButtonListener (this);
    andToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (clearToggle = new ToggleButton (T("new toggle button")));
    clearToggle->setButtonText (T("CLR"));
    clearToggle->addButtonListener (this);
    clearToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (setToggle = new ToggleButton (T("new toggle button")));
    setToggle->setButtonText (T("SET"));
    setToggle->addButtonListener (this);
    setToggle->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (xorSlider = new Slider (String::empty));
    xorSlider->setRange (1, 32, 1);
    xorSlider->setSliderStyle (Slider::TwoValueHorizontal);
    xorSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    xorSlider->setColour (Slider::trackColourId, Colours::white);
    xorSlider->addListener (this);

    addAndMakeVisible (andSlider = new Slider (String::empty));
    andSlider->setRange (1, 32, 1);
    andSlider->setSliderStyle (Slider::TwoValueHorizontal);
    andSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    andSlider->setColour (Slider::trackColourId, Colours::white);
    andSlider->addListener (this);

    addAndMakeVisible (clearSlider = new Slider (String::empty));
    clearSlider->setRange (1, 32, 1);
    clearSlider->setSliderStyle (Slider::TwoValueHorizontal);
    clearSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    clearSlider->setColour (Slider::trackColourId, Colours::white);
    clearSlider->addListener (this);

    addAndMakeVisible (setSlider = new Slider (String::empty));
    setSlider->setRange (1, 32, 1);
    setSlider->setSliderStyle (Slider::TwoValueHorizontal);
    setSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    setSlider->setColour (Slider::trackColourId, Colours::white);
    setSlider->addListener (this);

    cachedImage_metal2_png = ImageCache::getFromMemory (metal2_png, metal2_pngSize);

    //[UserPreSize]
	xorSlider->setMinValue (1, false);
	andSlider->setMinValue (1, false);
	clearSlider->setMinValue (1, false);
	setSlider->setMinValue (1, false);

	xorSlider->setMaxValue (1, false);
	andSlider->setMaxValue (1, false);
	clearSlider->setMaxValue (1, false);
	setSlider->setMaxValue (1, false);

	owner = ownerFilter;
	owner->addChangeListener (this);

	MemoryInputStream fontStream (lcd_bin,lcd_binSize, false);
	CustomTypeface* typeFace = new CustomTypeface (fontStream);

	lcdBigFont = new Font (typeFace);
	lcdBigFont->setExtraKerningFactor (0.05f);
	lcdBigFont->setHeight (16.0f);

	lcdSmallFont = new Font (typeFace);
	lcdSmallFont->setExtraKerningFactor (0.1f);
	lcdSmallFont->setHeight (12.0f);

	processButton->setImages (false, true, true,
                              ImageCache::getFromMemory (power_on_png, power_on_pngSize), 0.8428f, Colour (0x0),
                              0, 1.0000f, Colour (0x0),
                              ImageCache::getFromMemory (power_off_png, power_off_pngSize), 1.0000f, Colour (0x0));
    //[/UserPreSize]

    setSize (380, 155);

    //[Constructor] You can add your own custom stuff here..
	setProgram();
    //[/Constructor]
}

bitManglerEditor::~bitManglerEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	owner->removeChangeListener (this);
    //[/Destructor_pre]

    deleteAndZero (andBitMod);
    deleteAndZero (xorBitMod);
    deleteAndZero (bitDisplayInput);
    deleteAndZero (bitDisplayOutput);
    deleteAndZero (processButton);
    deleteAndZero (andRange);
    deleteAndZero (xorRange);
    deleteAndZero (clearRange);
    deleteAndZero (setRange);
    deleteAndZero (xorToggle);
    deleteAndZero (andToggle);
    deleteAndZero (clearToggle);
    deleteAndZero (setToggle);
    deleteAndZero (xorSlider);
    deleteAndZero (andSlider);
    deleteAndZero (clearSlider);
    deleteAndZero (setSlider);
    ImageCache::release (cachedImage_metal2_png);

    //[Destructor]. You can add your own custom destruction code here..
	owner->removeChangeListener (this);
    //[/Destructor]
}

//==============================================================================
void bitManglerEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    g.setColour (Colours::black);
    g.drawImage (cachedImage_metal2_png,
                 0, 0, 381, 163,
                 0, 0, cachedImage_metal2_png->getWidth(), cachedImage_metal2_png->getHeight());

    g.setGradientFill (ColourGradient (Colour (0xc2000000),
                                       184.0f, 48.0f,
                                       Colour (0x6c515151),
                                       184.0f, 8.0f,
                                       false));
    g.fillRoundedRectangle (8.0f, 8.0f, 360.0f, 40.0f, 10.0000f);

    g.setGradientFill (ColourGradient (Colour (0xc2000000),
                                       176.0f, 144.0f,
                                       Colour (0x6c515151),
                                       176.0f, 104.0f,
                                       false));
    g.fillRoundedRectangle (8.0f, 108.0f, 360.0f, 40.0f, 10.0000f);

    g.setGradientFill (ColourGradient (Colour (0xc2000000),
                                       168.0f, 104.0f,
                                       Colour (0x6c515151),
                                       168.0f, 64.0f,
                                       false));
    g.fillRoundedRectangle (13.0f, 52.0f, 315.0f, 52.0f, 10.0000f);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void bitManglerEditor::resized()
{
    andBitMod->setBounds (136, 88, 40, 16);
    xorBitMod->setBounds (136, 64, 40, 16);
    bitDisplayInput->setBounds (8, 8, 360, 40);
    bitDisplayOutput->setBounds (8, 108, 360, 40);
    processButton->setBounds (336, 64, 32, 32);
    andRange->setBounds (78, 93, 40, 8);
    xorRange->setBounds (78, 69, 40, 8);
    clearRange->setBounds (246, 69, 40, 8);
    setRange->setBounds (246, 93, 40, 8);
    xorToggle->setBounds (16, 57, 40, 16);
    andToggle->setBounds (16, 81, 40, 16);
    clearToggle->setBounds (170, 57, 38, 16);
    setToggle->setBounds (170, 81, 38, 16);
    xorSlider->setBounds (54, 61, 120, 8);
    andSlider->setBounds (54, 85, 120, 8);
    clearSlider->setBounds (206, 61, 120, 8);
    setSlider->setBounds (206, 85, 120, 8);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void bitManglerEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == andBitMod)
    {
        //[UserButtonCode_andBitMod] -- add your button handler code here..
		owner->getCallbackLock().enter();
		owner->setAndWith (andBitMod->getToggleState());
		owner->getCallbackLock().exit();
        //[/UserButtonCode_andBitMod]
    }
    else if (buttonThatWasClicked == xorBitMod)
    {
        //[UserButtonCode_xorBitMod] -- add your button handler code here..
		owner->getCallbackLock().enter();
		owner->setXorWith (xorBitMod->getToggleState());
		owner->getCallbackLock().exit();
        //[/UserButtonCode_xorBitMod]
    }
    else if (buttonThatWasClicked == processButton)
    {
        //[UserButtonCode_processButton] -- add your button handler code here..
		if (owner->isProcessing())
		{
			owner->getCallbackLock().enter();
			owner->stopProcessing();
			owner->getCallbackLock().exit();

			processButton->setImages (false, true, true,
                              ImageCache::getFromMemory (power_off_png, power_off_pngSize), 0.8428f, Colour (0x0),
                              0, 1.0000f, Colour (0x0),
                              ImageCache::getFromMemory (power_on_png, power_on_pngSize), 1.0000f, Colour (0x0));
		}
		else
		{
			owner->getCallbackLock().enter();
			owner->startProcessing();
			owner->getCallbackLock().exit();

			processButton->setImages (false, true, true,
                              ImageCache::getFromMemory (power_on_png, power_on_pngSize), 0.8428f, Colour (0x0),
                              0, 1.0000f, Colour (0x0),
                              ImageCache::getFromMemory (power_off_png, power_off_pngSize), 1.0000f, Colour (0x0));
		}


        //[/UserButtonCode_processButton]
    }
    else if (buttonThatWasClicked == xorToggle)
    {
        //[UserButtonCode_xorToggle] -- add your button handler code here..

		if (xorToggle->getToggleState())
		{
			owner->setProcess (XOR, true);
			sliderValueChanged (xorSlider);
		}
		else
		{
			owner->setProcess (XOR, false);
			owner->clearXorTable();
		}

        //[/UserButtonCode_xorToggle]
    }
    else if (buttonThatWasClicked == andToggle)
    {
        //[UserButtonCode_andToggle] -- add your button handler code here..

		if (andToggle->getToggleState())
		{
			owner->setProcess (AND, true);
			sliderValueChanged (andSlider);
		}
		else
		{
			owner->setProcess (AND, false);
			owner->clearAndTable();
		}
        //[/UserButtonCode_andToggle]
    }
    else if (buttonThatWasClicked == clearToggle)
    {
        //[UserButtonCode_clearToggle] -- add your button handler code here..

		if (clearToggle->getToggleState())
		{
			owner->setProcess (CLEAR, true);
			sliderValueChanged (clearSlider);
		}
		else
		{
			owner->setProcess (CLEAR, false);
			owner->clearClearTable();
		}

        //[/UserButtonCode_clearToggle]
    }
    else if (buttonThatWasClicked == setToggle)
    {
        //[UserButtonCode_setToggle] -- add your button handler code here..

		if (setToggle->getToggleState())
		{
			owner->setProcess (SET, true);
			sliderValueChanged (setSlider);
		}
		else
		{
			owner->setProcess (SET, false);
			owner->clearSetTable();
		}

        //[/UserButtonCode_setToggle]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void bitManglerEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == xorSlider)
    {
        //[UserSliderCode_xorSlider] -- add your slider handling code here..
		if (!xorToggle->getToggleState())
			return;

		const int min = (int)xorSlider->getMinValue();
		const int max = (int)xorSlider->getMaxValue();

		Logger::writeToLog (T("xorSlider: ") + String(min) + T("-") + String(max));
		if (min < 1 || max > 32)
			return;

		if (min > max)
			return;

		owner->clearXorTable();

		for (int x=min; x<=max; x++)
		{
			owner->setXorBit (x, xorBitMod->getToggleState());
		}

		Logger::writeToLog (T("setParameterNotifyingHost()") + String (32/(float)min) + T("-") + String (32/(float)max));
		owner->setParameterNotifyingHost(DemoJuceFilter::kXorMin, (float)min/32);
		owner->setParameterNotifyingHost(DemoJuceFilter::kXorMax, (float)max/32);

		xorRange->setText (String(min) + T("-") + String(max), false);
        //[/UserSliderCode_xorSlider]
    }
    else if (sliderThatWasMoved == andSlider)
    {
        //[UserSliderCode_andSlider] -- add your slider handling code here..
		if (!andToggle->getToggleState())
			return;

		const int min = (int)andSlider->getMinValue();
		const int max = (int)andSlider->getMaxValue();

		if (min < 1 || max > 32)
			return;

		if (min > max)
			return;

		owner->clearAndTable();

		for (int x=min; x<=max; x++)
		{
			owner->setAndBit (x, xorBitMod->getToggleState());
		}

		owner->setParameterNotifyingHost(DemoJuceFilter::kAndMin, (float)min/32);
		owner->setParameterNotifyingHost(DemoJuceFilter::kAndMax, (float)max/32);
		andRange->setText (String(min) + T("-") + String(max), false);
        //[/UserSliderCode_andSlider]
    }
    else if (sliderThatWasMoved == clearSlider)
    {
        //[UserSliderCode_clearSlider] -- add your slider handling code here..
		if (!clearToggle->getToggleState())
			return;

		const int min = (int)clearSlider->getMinValue();
		const int max = (int)clearSlider->getMaxValue();

		if (min < 1 || max > 32)
			return;

		if (min > max)
			return;

		owner->clearClearTable();

		for (int x=min; x<=max; x++)
		{
			owner->setClearBit (x);
		}

		owner->setParameterNotifyingHost(DemoJuceFilter::kClearMin, (float)min/32);
		owner->setParameterNotifyingHost(DemoJuceFilter::kClearMax, (float)max/32);
		clearRange->setText (String(min) + T("-") + String(max), false);
        //[/UserSliderCode_clearSlider]
    }
    else if (sliderThatWasMoved == setSlider)
    {
        //[UserSliderCode_setSlider] -- add your slider handling code here..
		if (!setToggle->getToggleState())
			return;

		const int min = (int)setSlider->getMinValue();
		const int max = (int)setSlider->getMaxValue();

		if (min < 1 || max > 32)
			return;

		if (min > max)
			return;

		owner->clearSetTable();

		for (int x=min; x<=max; x++)
		{
			owner->setSetBit (x);
		}

		owner->setParameterNotifyingHost(DemoJuceFilter::kSetMin, (float)min/32);
		owner->setParameterNotifyingHost(DemoJuceFilter::kSetMax, (float)max/32);
		setRange->setText (String(min) + T("-") + String(max), false);
        //[/UserSliderCode_setSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
String bitManglerEditor::getBinaryString (floatint b, int d)
{
	String r;
	while (--d >= 0)
	{
		r << String::formatted (T("%d"), ((b >> d) & 1));
	}

	return (r);
}

void bitManglerEditor::changeListenerCallback(void *ptr)
{
	if (ptr == owner)
	{
		setProgram();
	}
	if (ptr == 0)
	{
		updateBitDisplay();
	}
}

void bitManglerEditor::setProgram()
{
	owner->getCallbackLock().enter();
	const bool xorProcessing = owner->xorProcessing;
	const bool andProcessing = owner->andProcessing;
	const bool clearProcessing = owner->clearProcessing;
	const bool setProcessing = owner->setProcessing;
	const bool xorWith = owner->getXorWith();
	const bool andWith = owner->getAndWith();

	const int xorFirst = owner->getXorFirst();

	const int xorLast = owner->getXorLast();
	const int andFirst = owner->getAndFirst();
	const int andLast = owner->getAndLast();
	const int clearFirst = owner->getClearFirst();
	const int clearLast = owner->getClearLast();
	const int setFirst = owner->getSetFirst();
	const int setLast = owner->getSetLast();
	owner->getCallbackLock().exit();

	if (xorWith)
		xorBitMod->setToggleState (true, false);
	else
		xorBitMod->setToggleState (false, false);

	if (andWith)
		andBitMod->setToggleState (true, false);
	else
		andBitMod->setToggleState (false, false);

	if (xorProcessing)
		xorToggle->setToggleState (true, false);
	else
		xorToggle->setToggleState (false, false);

	if (andProcessing)
		andToggle->setToggleState (true, false);
	else
		andToggle->setToggleState (false, false);

	if (setProcessing)
		setToggle->setToggleState (true, false);
	else
		setToggle->setToggleState (false, false);

	if (clearProcessing)
		clearToggle->setToggleState (true, false);
	else
		clearToggle->setToggleState (false, false);

	xorSlider->setMaxValue (xorLast, false);
	xorSlider->setMinValue (xorFirst, false);
	xorRange->setText (String(xorFirst) + T("-") + String(xorLast), false);

	andSlider->setMaxValue (andLast, false);
	andSlider->setMinValue (andFirst, false);
	andRange->setText (String(andFirst) + T("-") + String(andLast), false);

	clearSlider->setMaxValue (clearLast, false);
	clearSlider->setMinValue (clearFirst, false);
	clearRange->setText (String(clearFirst) + T("-") + String(clearLast), false);

	setSlider->setMaxValue (setLast, false, true);
	setSlider->setMinValue (setFirst, false, true);
	setRange->setText (String(setFirst) + T("-") + String(setLast), false);
}

void bitManglerEditor::updateBitDisplay()
{
	owner->getCallbackLock().enter();
	const float currentSample = owner->getCurrentSample();
	const float currentConvertedSample = owner->getCurrentConvertedSample();
	owner->getCallbackLock().exit();

	uSample.f = currentSample;
	uConvertedSample.f = currentConvertedSample;

	String in;
	String out;

	if (uSample.i & SIGN_FLT)
	{
		in << T("-:");
	}
	else
	{
		 in << T("+:");
	}

	if (uConvertedSample.i & SIGN_FLT)
	{
		out << T("-:");
	}
	else
	{
		 out << T("+:");
	}

	uSample.i &= ~SIGN_FLT;
	e = uSample.i >> MANT_FLT;
	in << getBinaryString (e, BITS_FLT-1-MANT_FLT);
	in << T(":");

	uConvertedSample.i &= ~SIGN_FLT;
	ce = uConvertedSample.i >> MANT_FLT;
	out << getBinaryString (ce, BITS_FLT-1-MANT_FLT);
	out << T(":");

	m	= (uSample.i & (((floatint)1 << MANT_FLT) - 1));
	cm	= (uConvertedSample.i & (((floatint)1 << MANT_FLT) - 1));

	in << getBinaryString(m, MANT_FLT);
	out << getBinaryString(cm, MANT_FLT);

	bitDisplayInput->setText (in, false);
	bitDisplayOutput->setText (out, false);
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="bitManglerEditor" componentName=""
                 parentClasses="public AudioProcessorEditor, public ChangeListener"
                 constructorParams="DemoJuceFilter* const ownerFilter" variableInitialisers="AudioProcessorEditor (ownerFilter)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="1" initialWidth="380" initialHeight="155">
  <BACKGROUND backgroundColour="ffffffff">
    <IMAGE pos="0 0 381 163" resource="metal2_png" opacity="1" mode="0"/>
    <ROUNDRECT pos="8 8 360 40" cornerSize="10" fill="linear: 184 48, 184 8, 0=c2000000, 1=6c515151"
               hasStroke="0"/>
    <ROUNDRECT pos="8 108 360 40" cornerSize="10" fill="linear: 176 144, 176 104, 0=c2000000, 1=6c515151"
               hasStroke="0"/>
    <ROUNDRECT pos="13 52 315 52" cornerSize="10" fill="linear: 168 104, 168 64, 0=c2000000, 1=6c515151"
               hasStroke="0"/>
  </BACKGROUND>
  <TOGGLEBUTTON name="new toggle button" id="89a7c7b04d87537a" memberName="andBitMod"
                virtualName="" explicitFocusOrder="0" pos="136 88 40 16" txtcol="ffffffff"
                buttonText="mod" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="ab48f9e596989182" memberName="xorBitMod"
                virtualName="" explicitFocusOrder="0" pos="136 64 40 16" txtcol="ffffffff"
                buttonText="mod" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <LABEL name="Bit Display" id="ba73773ed927989c" memberName="bitDisplayInput"
         virtualName="" explicitFocusOrder="0" pos="8 8 360 40" bkgCol="ffffff"
         textCol="ff2eff3a" outlineCol="0" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="16"
         bold="1" italic="0" justification="36"/>
  <LABEL name="Bit Display" id="1b4b8d1f80207a8d" memberName="bitDisplayOutput"
         virtualName="" explicitFocusOrder="0" pos="8 108 360 40" bkgCol="ffffff"
         textCol="fffa8b8b" outlineCol="0" edTextCol="ff000000" edBkgCol="0"
         labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="16"
         bold="1" italic="0" justification="36"/>
  <IMAGEBUTTON name="Process" id="21d9e966d47b47a8" memberName="processButton"
               virtualName="" explicitFocusOrder="0" pos="336 64 32 32" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="power_off_png" opacityNormal="0.842767298" colourNormal="0"
               resourceOver="" opacityOver="1" colourOver="0" resourceDown="power_on_png"
               opacityDown="1" colourDown="0"/>
  <LABEL name="new label" id="9d0c737ceadc665c" memberName="andRange"
         virtualName="" explicitFocusOrder="0" pos="78 93 40 8" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="1-1" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="10" bold="1" italic="0" justification="36"/>
  <LABEL name="new label" id="38b7dddb6e3de352" memberName="xorRange"
         virtualName="" explicitFocusOrder="0" pos="78 69 40 8" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="1-1" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="10" bold="1" italic="0" justification="36"/>
  <LABEL name="new label" id="df82b0e597fb4365" memberName="clearRange"
         virtualName="" explicitFocusOrder="0" pos="246 69 40 8" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="1-1" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="10" bold="1" italic="0" justification="36"/>
  <LABEL name="new label" id="d4ebe68b130d3b4" memberName="setRange" virtualName=""
         explicitFocusOrder="0" pos="246 93 40 8" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="1-1" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="10"
         bold="1" italic="0" justification="36"/>
  <TOGGLEBUTTON name="new toggle button" id="bb2ce646eb272d0" memberName="xorToggle"
                virtualName="" explicitFocusOrder="0" pos="16 57 40 16" txtcol="ffffffff"
                buttonText="XOR" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="16ec5992aca7d239" memberName="andToggle"
                virtualName="" explicitFocusOrder="0" pos="16 81 40 16" txtcol="ffffffff"
                buttonText="AND" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="f2214d5d187f7022" memberName="clearToggle"
                virtualName="" explicitFocusOrder="0" pos="170 57 38 16" txtcol="ffffffff"
                buttonText="CLR" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="74eaf471efda6195" memberName="setToggle"
                virtualName="" explicitFocusOrder="0" pos="170 81 38 16" txtcol="ffffffff"
                buttonText="SET" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <SLIDER name="" id="d74bb98668a6df2a" memberName="xorSlider" virtualName=""
          explicitFocusOrder="0" pos="54 61 120 8" trackcol="ffffffff"
          min="1" max="32" int="1" style="TwoValueHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="bd43c636a56cb753" memberName="andSlider" virtualName=""
          explicitFocusOrder="0" pos="54 85 120 8" trackcol="ffffffff"
          min="1" max="32" int="1" style="TwoValueHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="14afddd09d7c6a30" memberName="clearSlider" virtualName=""
          explicitFocusOrder="0" pos="206 61 120 8" trackcol="ffffffff"
          min="1" max="32" int="1" style="TwoValueHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="6b5699ba41f0741f" memberName="setSlider" virtualName=""
          explicitFocusOrder="0" pos="206 85 120 8" trackcol="ffffffff"
          min="1" max="32" int="1" style="TwoValueHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//==============================================================================
// Binary resources - be careful not to edit any of these sections!

// JUCER_RESOURCE: lcd_bin, 5469, "lcd.bin"
static const unsigned char resource_bitManglerEditor_lcd_bin[] = { 120,156,237,92,123,156,205,229,186,95,70,228,218,72,110,149,221,133,93,185,237,80,18,153,223,251,107,139,180,25,108,68,24,236,173,101,
69,249,173,169,102,108,21,187,194,153,66,202,229,131,114,82,116,213,145,56,20,91,153,89,107,109,195,118,73,18,29,164,67,233,216,200,113,169,19,233,176,187,236,231,251,125,222,245,27,203,24,204,210,238,
162,249,203,227,119,123,223,231,251,60,207,247,125,158,231,125,215,164,223,212,38,16,8,164,111,202,118,47,13,100,136,116,89,32,123,233,92,147,25,42,111,255,173,96,255,173,104,255,173,100,255,173,108,255,
189,60,208,244,221,43,77,102,184,126,169,138,102,125,94,169,152,215,244,221,89,206,138,78,251,162,94,153,70,117,156,26,93,82,98,222,154,50,139,157,101,45,50,98,222,225,218,23,152,167,95,27,24,243,42,31,
113,204,174,81,25,177,96,120,102,240,117,103,226,173,117,163,158,188,235,228,100,236,140,64,200,227,149,73,31,175,73,43,187,248,237,168,119,241,131,47,57,153,21,118,68,189,102,127,255,202,193,149,96,184,
251,139,19,28,249,72,196,27,217,118,74,154,204,122,132,247,73,143,183,242,120,165,253,117,71,211,234,182,255,107,36,24,170,19,56,92,123,178,76,77,102,227,188,214,167,73,204,171,95,106,156,179,175,229,
149,16,42,234,149,144,211,206,217,156,157,30,243,58,239,91,238,44,217,222,35,230,125,211,175,172,57,26,73,151,169,149,107,157,109,214,205,146,135,90,78,111,109,248,218,128,215,47,49,124,45,123,233,111,
248,144,215,122,80,63,179,173,193,109,49,153,245,72,125,45,244,235,192,251,27,170,186,153,225,149,91,170,185,117,219,223,40,207,28,44,235,222,115,89,179,152,23,171,116,196,240,202,203,23,125,99,220,174,
29,99,222,194,250,149,220,131,195,123,197,188,167,158,172,225,226,74,48,188,195,171,224,2,26,62,125,77,175,206,49,175,249,209,85,42,172,155,53,223,108,25,219,55,230,109,95,51,81,175,204,203,250,173,10,
117,98,53,9,168,39,255,83,136,5,20,23,66,48,252,237,158,121,230,80,217,20,192,63,217,208,50,127,124,244,207,122,165,213,130,201,58,145,54,15,253,167,225,68,42,244,92,110,116,34,7,58,127,37,95,218,29,245,
26,214,220,42,131,172,139,122,47,158,243,154,10,219,26,60,165,183,118,126,245,186,145,129,98,94,189,161,255,67,33,24,118,187,86,214,111,247,189,103,142,250,193,216,170,77,28,94,17,135,113,56,26,158,225,
104,107,202,92,111,71,155,176,250,168,121,127,195,134,136,183,118,226,199,38,179,66,48,226,137,161,11,174,164,119,88,19,245,54,246,253,135,161,31,172,189,184,156,139,43,193,240,219,195,198,235,76,114,
50,66,58,183,172,230,101,84,128,215,241,22,188,142,147,132,65,117,146,131,15,77,210,111,175,232,228,233,104,176,49,175,116,185,47,172,163,225,25,142,38,14,109,116,180,140,222,31,26,121,48,226,117,123,
34,106,232,117,115,119,79,115,40,192,163,120,107,209,194,133,34,228,71,60,239,225,27,12,133,86,87,14,54,18,11,17,175,82,230,84,189,50,117,196,223,40,4,195,101,26,189,224,112,216,61,117,55,166,113,34,95,
124,126,79,30,175,32,14,182,140,253,85,20,193,226,188,210,164,83,212,67,172,224,74,48,116,85,96,214,203,87,136,103,95,50,249,75,167,205,67,141,99,222,5,243,199,32,140,98,252,206,229,205,26,3,254,134,206,
194,250,233,240,222,124,167,109,249,158,116,122,131,43,193,80,189,192,23,195,255,93,94,191,244,146,25,234,53,125,118,142,82,63,154,244,113,7,21,100,194,134,49,251,220,129,222,234,80,51,62,24,107,212,161,
90,84,185,200,48,176,43,31,137,56,95,78,250,223,40,208,115,230,127,179,39,202,48,162,137,231,238,174,165,38,6,176,181,203,193,196,120,154,154,137,14,14,117,29,217,182,90,46,175,64,197,35,215,252,61,234,
125,245,74,174,99,86,138,48,227,131,242,102,105,29,132,250,240,241,191,83,208,7,31,58,95,65,31,91,117,190,99,99,190,165,178,128,80,133,130,254,217,135,151,42,178,161,250,86,71,168,70,69,4,66,83,37,85,
84,147,81,85,16,172,148,151,160,44,117,108,88,179,143,213,113,89,139,233,26,25,53,186,140,50,212,113,72,122,15,21,4,89,101,58,92,225,51,223,244,123,148,202,6,195,239,111,232,170,110,180,172,197,197,234,
88,226,66,78,100,228,123,17,15,168,145,206,246,212,237,110,168,227,184,122,35,41,4,195,219,215,84,49,190,247,80,53,208,33,5,153,173,242,26,148,5,175,137,34,239,58,170,99,131,192,243,15,252,155,232,152,
154,115,135,17,110,140,122,192,138,115,4,124,20,224,252,83,71,148,137,9,178,173,196,250,149,98,222,192,85,119,83,8,134,161,173,76,86,103,116,254,211,139,163,222,176,210,151,171,48,116,243,183,142,80,65,
84,28,171,156,17,90,142,130,41,41,4,195,99,70,159,107,36,202,98,66,35,95,171,249,47,153,252,39,21,196,234,14,39,2,135,224,104,195,199,175,118,116,52,225,101,135,95,146,160,116,196,79,162,224,110,135,163,
73,132,165,81,144,91,105,227,141,204,72,162,128,15,7,67,13,3,191,154,252,165,232,216,53,229,73,69,125,118,238,80,51,98,201,222,168,39,94,165,87,170,175,232,101,218,150,175,21,19,94,24,99,54,125,42,81,
48,229,203,103,120,37,24,110,91,254,3,37,136,81,239,229,153,251,247,11,47,128,243,40,236,157,247,160,185,181,150,220,106,81,229,105,147,59,248,187,168,183,124,217,50,10,193,48,120,129,247,110,220,118,
157,62,29,114,86,58,20,196,63,148,87,122,190,181,221,225,107,96,97,125,13,19,24,240,250,140,40,167,52,102,244,232,168,87,173,85,83,189,50,234,189,52,53,63,88,232,141,25,194,43,57,187,158,80,94,9,53,178,
107,232,238,202,231,24,193,57,66,64,0,33,163,152,142,141,192,146,0,136,50,138,213,250,87,219,183,110,158,18,208,183,132,177,28,193,116,137,160,247,121,26,175,116,127,49,85,2,36,18,97,92,137,147,69,61,
24,79,95,111,28,184,111,127,170,172,83,47,77,168,230,94,56,176,91,204,251,116,218,107,134,65,12,132,104,206,135,94,122,218,68,70,86,193,50,121,46,23,19,239,187,33,53,237,170,178,187,114,142,185,250,55,
115,57,33,245,84,25,53,143,194,150,177,207,10,115,61,27,33,41,211,211,23,214,127,92,61,61,212,36,32,14,45,163,194,227,201,33,8,102,46,19,240,111,154,19,52,199,176,194,51,228,16,185,101,57,4,139,10,227,
11,42,50,190,228,94,158,127,133,196,141,103,72,220,0,70,57,100,215,168,255,214,248,146,0,50,241,57,250,241,165,196,45,9,132,66,125,217,236,21,150,157,197,193,53,154,197,212,26,205,66,52,134,209,92,245,
138,237,106,206,139,190,176,139,210,231,161,248,162,180,57,187,146,75,77,176,206,83,183,43,54,126,170,174,218,228,166,111,149,50,142,68,236,202,191,173,65,77,87,117,19,32,117,229,151,72,81,18,94,190,236,
38,21,192,29,188,117,203,171,93,148,169,68,55,53,68,168,169,69,20,83,227,24,72,19,24,32,157,250,63,163,75,241,141,219,22,25,9,246,152,87,186,198,122,125,125,245,103,59,109,2,246,215,167,158,55,139,22,
74,118,210,232,133,28,147,50,174,158,76,237,154,1,166,193,227,215,198,184,112,229,14,118,185,148,51,203,33,254,134,108,244,244,245,19,21,72,137,125,35,43,124,196,91,185,101,138,46,156,98,81,117,112,228,
18,76,215,66,215,216,57,202,103,205,205,83,36,3,194,194,197,156,8,185,29,115,34,88,29,56,144,230,137,12,22,80,69,38,189,131,69,6,89,2,1,233,188,175,141,10,224,89,222,2,243,82,181,59,63,138,39,62,181,203,
85,118,169,63,80,167,29,238,186,115,143,98,36,252,166,118,192,51,28,13,158,173,169,8,224,103,128,183,30,244,145,166,18,136,57,10,88,75,121,11,249,22,115,10,33,41,155,83,32,187,161,179,200,67,121,96,109,
114,248,230,236,119,162,76,124,24,7,240,72,177,147,248,200,245,143,252,159,177,68,63,82,163,6,33,74,255,251,60,180,202,134,232,181,22,54,97,115,117,40,225,86,85,68,240,85,69,144,37,82,17,228,141,84,4,
241,172,176,193,35,137,205,7,223,30,42,72,19,41,72,78,231,240,214,197,15,254,90,97,131,31,43,108,29,55,29,84,253,193,157,84,27,171,42,5,100,210,188,133,4,152,250,143,254,250,35,171,63,242,69,234,143,96,
99,176,32,144,24,44,184,194,96,153,157,123,88,131,101,241,219,101,108,176,12,73,223,164,161,249,250,5,185,198,79,165,40,8,254,185,188,5,42,36,52,243,178,150,90,104,154,89,104,78,18,107,227,234,149,82,
245,247,47,63,79,217,235,189,166,23,186,234,245,66,140,26,26,9,244,195,43,88,130,247,47,239,164,244,35,217,143,58,226,219,195,58,201,107,64,155,250,255,197,221,166,136,96,125,164,128,236,134,183,42,101,
86,87,104,36,161,177,208,60,112,255,255,171,142,247,206,217,170,58,206,89,191,82,227,8,204,194,168,1,215,16,26,249,162,171,81,115,157,213,81,86,85,157,191,239,254,72,170,40,96,13,82,171,65,35,170,221,
238,210,217,186,24,35,205,34,159,35,59,18,42,86,30,213,218,198,103,54,240,152,207,108,62,215,209,88,254,140,154,31,141,51,219,233,232,47,165,204,241,250,251,244,251,209,162,88,49,232,23,154,112,74,72,
11,236,36,59,40,217,203,211,185,157,250,215,102,90,2,218,136,218,34,243,98,129,173,185,133,45,73,214,0,255,112,101,66,212,18,72,20,178,4,18,174,193,96,59,1,71,249,225,143,250,147,147,149,213,57,207,207,
119,153,221,98,101,34,15,136,161,236,202,132,226,138,250,223,249,145,93,153,62,251,112,166,99,107,139,90,10,141,207,12,146,131,88,104,224,237,133,87,166,83,218,239,156,231,173,253,190,126,223,218,15,137,
34,5,89,25,143,179,159,204,84,237,23,186,222,34,218,53,165,134,34,138,2,172,8,66,65,97,66,68,51,167,86,180,136,98,173,146,204,50,230,125,88,109,133,102,24,146,56,104,134,209,224,241,55,204,237,207,84,
142,121,207,63,80,218,101,33,126,217,236,178,20,130,225,87,111,158,41,245,247,124,165,207,120,226,175,197,62,48,102,134,225,118,125,194,16,218,125,45,103,217,12,163,69,73,134,241,253,102,24,73,178,94,
168,165,53,196,191,16,154,189,243,190,209,4,115,105,157,10,174,150,82,208,150,250,151,93,92,193,165,143,1,17,10,69,99,148,52,52,39,89,71,78,230,100,73,198,225,13,54,227,71,5,251,196,27,179,181,92,150,
172,63,234,69,70,254,222,217,208,238,85,172,208,158,12,159,31,101,221,153,209,251,195,40,185,14,87,130,225,234,43,182,40,218,120,154,248,203,231,210,120,165,126,169,113,105,44,20,80,67,136,82,104,168,
236,116,228,243,178,212,182,178,163,162,164,231,168,90,139,76,194,24,65,29,117,232,230,135,116,84,36,8,28,21,41,131,142,138,37,138,197,136,140,24,0,93,219,234,38,31,69,242,116,173,74,182,206,60,96,75,
218,180,192,59,19,255,32,131,161,128,146,97,181,121,72,235,161,150,161,128,111,228,236,170,28,99,121,33,170,196,188,7,47,204,162,16,12,195,49,197,151,200,194,14,5,241,181,52,97,153,40,26,123,74,190,48,
12,5,84,187,146,126,9,103,56,129,191,117,218,39,163,34,63,76,205,217,21,245,110,127,102,173,145,58,59,42,11,196,6,135,2,84,228,45,204,85,210,199,168,36,90,255,101,32,32,28,223,81,15,71,234,77,96,145,177,
196,115,152,86,188,133,26,153,74,75,161,107,115,24,99,117,157,118,185,171,14,138,226,140,130,204,202,161,246,112,43,170,136,242,147,2,170,94,104,31,12,75,214,109,168,153,212,124,185,212,21,185,36,5,140,
10,205,216,205,164,174,232,184,42,63,186,1,41,51,37,44,131,87,29,54,157,250,75,81,240,216,179,31,168,163,227,97,10,136,70,122,60,28,141,30,143,254,158,122,60,22,83,250,55,178,99,122,60,86,37,161,239,24,
179,27,122,60,98,168,69,149,222,186,78,104,82,141,214,25,221,26,173,51,58,58,202,95,10,176,30,111,13,234,54,205,204,203,146,248,124,184,241,50,10,193,48,154,21,178,252,70,189,30,87,183,48,108,15,35,154,
216,30,70,101,77,54,190,98,227,32,229,199,158,109,198,218,70,221,90,193,149,233,213,134,118,13,212,32,96,106,94,65,203,81,219,195,191,13,212,26,120,129,0,1,151,79,236,37,11,234,121,54,44,42,234,202,141,
62,29,113,68,11,90,199,64,19,51,49,225,2,155,113,121,195,250,192,90,230,4,141,206,36,137,6,175,37,178,217,199,55,126,170,134,0,9,114,52,172,10,126,45,163,68,131,170,128,243,6,135,23,78,65,121,229,217,
142,159,40,155,226,211,74,162,73,50,126,107,219,250,70,81,71,234,22,31,209,82,200,15,62,31,72,4,168,246,242,253,142,49,94,75,12,117,48,13,51,87,224,167,26,129,214,9,18,56,52,177,9,142,28,132,176,213,109,
31,135,13,13,118,26,9,171,9,189,85,230,94,0,27,189,213,135,109,201,246,26,22,54,116,154,19,211,99,177,185,174,61,232,70,19,173,19,116,163,159,59,96,251,195,211,46,183,121,174,80,157,86,119,126,91,24,57,
144,46,112,40,230,136,36,76,66,108,53,0,215,69,25,128,188,133,0,36,200,50,146,5,249,166,192,252,49,85,109,223,134,149,179,188,229,118,220,116,173,86,135,165,2,55,106,45,71,213,38,125,92,81,85,27,146,30,
223,95,192,74,73,252,80,148,16,54,249,136,10,88,113,120,11,28,67,32,115,7,127,103,124,32,21,54,24,208,55,18,189,29,27,62,244,63,148,201,28,109,209,194,102,214,219,145,204,18,54,108,230,36,246,183,225,
18,140,45,60,67,151,64,83,64,129,148,149,74,129,20,111,83,32,159,122,242,73,37,84,188,198,91,160,241,120,107,204,34,138,144,138,251,157,154,77,146,51,53,27,8,157,5,3,194,134,5,3,82,39,92,9,134,218,88,
183,45,158,35,22,207,201,139,231,26,167,227,127,240,232,120,171,220,230,62,112,96,191,25,192,121,195,201,41,20,237,246,197,12,169,80,91,187,126,156,205,142,132,165,157,241,247,76,254,155,26,145,104,205,
82,128,181,120,203,110,71,196,226,69,173,64,115,243,153,65,227,111,161,22,134,6,107,12,173,118,2,104,146,155,108,193,22,42,114,63,127,11,149,136,156,4,209,80,59,75,63,133,247,41,11,111,70,98,203,229,184,
205,200,194,49,230,175,154,208,145,230,135,139,80,71,52,223,85,71,32,66,243,251,251,100,173,7,245,83,243,159,108,141,46,214,134,93,193,174,28,120,132,163,37,240,8,71,67,191,139,225,135,238,130,132,41,
55,168,202,187,196,22,133,78,225,141,82,110,35,244,94,183,192,250,200,45,22,191,65,221,106,41,126,120,157,64,32,160,41,160,57,203,202,21,174,193,13,42,41,145,221,83,250,72,225,109,118,236,57,104,191,11,
141,55,58,2,120,232,84,62,178,227,147,79,172,143,32,71,36,72,0,146,176,41,72,173,21,26,191,60,37,236,80,4,134,72,218,181,126,151,236,81,2,92,225,166,174,227,23,51,54,11,207,215,81,79,114,148,32,212,222,
178,63,28,154,159,246,29,26,141,88,10,232,82,240,214,253,251,215,29,239,208,241,157,123,150,160,52,8,22,22,10,98,121,245,245,66,251,253,69,237,119,211,233,124,23,75,64,86,25,62,73,62,243,217,243,116,182,
153,81,115,232,54,115,135,64,74,141,243,5,154,198,111,86,119,23,140,233,26,163,99,39,110,17,97,3,82,242,70,157,35,161,121,236,217,90,103,230,171,40,12,232,144,216,136,56,149,175,162,120,80,95,29,184,234,
51,69,100,188,217,96,108,151,104,152,41,93,99,125,148,7,31,8,100,173,173,175,154,184,211,25,225,155,72,210,190,154,110,169,254,36,124,134,226,60,177,138,42,56,246,82,44,62,43,200,34,146,227,179,80,199,
192,130,11,134,39,95,233,128,143,105,199,194,58,162,210,137,123,246,241,156,157,228,10,177,243,171,44,125,77,242,45,109,50,162,109,79,1,141,124,222,146,188,77,157,45,101,220,32,251,90,238,224,135,53,14,
243,231,102,185,54,252,6,170,208,176,102,31,151,236,209,244,221,59,152,224,11,70,67,108,28,138,143,185,4,160,107,74,15,151,144,220,61,181,131,94,105,91,190,167,139,230,30,95,179,157,131,44,27,135,104,
110,18,18,100,106,164,168,212,156,93,74,218,136,90,14,226,39,223,160,8,205,25,65,195,252,54,104,152,163,105,206,103,249,148,163,129,25,72,81,115,214,159,171,117,69,168,211,153,173,25,72,34,91,78,79,137,
177,199,76,1,89,236,170,1,142,214,158,123,234,118,215,56,162,0,61,164,180,75,62,124,127,216,53,163,179,133,230,135,77,43,227,229,84,129,33,160,81,162,33,224,25,28,22,190,162,206,230,215,39,104,251,113,
180,225,227,87,23,92,161,249,241,26,71,235,217,230,12,73,63,185,44,52,244,251,128,24,85,16,69,111,212,175,24,78,167,199,92,84,127,195,223,172,18,243,59,199,181,53,252,38,10,140,228,83,11,5,156,28,233,
127,190,148,92,104,253,104,248,36,185,253,118,98,218,179,206,86,36,217,134,186,252,68,92,171,112,140,255,76,93,43,44,47,27,169,40,35,94,249,181,211,77,207,54,99,163,222,172,151,95,54,251,151,191,27,245,
222,234,62,79,27,174,40,212,113,43,24,234,122,214,57,226,228,187,14,41,200,168,230,41,244,217,153,98,178,151,206,213,247,155,31,93,165,199,204,40,160,155,131,190,121,210,254,219,205,38,182,104,20,177,
45,132,173,53,54,138,96,53,94,129,107,197,75,174,83,31,68,61,173,211,166,197,62,255,169,136,22,62,109,122,146,131,156,5,167,77,253,52,26,73,115,17,149,154,191,160,22,52,234,126,216,52,250,214,192,166,
236,74,98,8,208,9,97,107,244,194,57,174,245,200,124,69,116,67,187,87,245,104,47,78,89,158,170,25,15,61,20,236,148,113,255,161,96,227,128,21,193,222,58,51,83,175,28,137,60,174,166,197,51,4,123,213,128,
136,5,123,204,232,209,170,254,119,67,110,83,245,113,158,131,87,208,57,103,87,61,115,234,56,69,109,88,233,231,117,143,51,212,253,212,132,232,79,246,4,137,65,177,8,177,224,168,247,153,246,2,11,19,162,159,
134,156,128,16,147,75,177,66,61,108,172,161,248,225,235,126,53,248,100,197,3,5,175,179,82,66,172,240,245,156,93,241,12,13,187,127,194,110,60,114,116,28,251,128,79,138,170,34,198,140,62,215,13,57,43,213,
88,66,14,55,240,200,22,161,217,216,119,184,41,215,250,96,196,19,179,28,175,227,95,220,190,250,16,182,80,40,192,34,115,214,175,212,83,248,124,26,219,127,20,224,80,91,103,30,144,42,226,54,91,69,252,44,204,
223,248,205,238,154,197,207,89,223,78,243,122,48,12,5,176,7,111,97,245,224,107,233,29,144,242,227,181,213,159,133,92,78,169,78,236,54,151,147,20,194,210,43,40,7,232,53,169,57,182,28,144,156,217,34,122,
243,148,17,106,118,84,8,137,197,71,249,181,25,90,124,160,84,161,217,31,189,119,168,53,59,250,173,132,196,247,209,4,246,98,28,38,148,3,10,9,86,125,26,0,73,39,163,30,157,6,174,94,240,45,78,36,238,154,50,
109,245,200,96,168,231,49,7,62,199,27,169,230,241,195,0,206,209,175,230,113,18,54,53,53,245,132,7,62,113,212,130,15,201,68,85,0,195,241,67,216,156,228,211,254,105,50,113,70,97,175,84,121,173,203,125,251,
21,118,108,146,82,216,225,61,102,228,85,61,97,79,32,177,248,83,192,209,51,89,55,196,16,89,205,31,209,195,31,48,114,226,241,82,249,118,30,30,242,122,190,245,71,61,252,81,112,188,180,151,165,40,116,231,
18,235,179,162,163,215,139,199,252,49,205,105,244,34,249,26,14,224,242,138,95,242,36,196,161,118,158,78,135,107,78,96,199,36,155,114,133,35,66,124,55,205,54,1,198,105,201,164,7,43,142,141,136,80,239,192,
181,146,81,100,134,5,22,117,17,108,9,112,133,65,176,82,192,102,55,111,97,103,156,58,74,228,219,220,13,153,206,172,151,175,192,226,255,148,154,127,232,230,135,84,104,125,240,81,26,155,27,89,60,196,131,
77,22,61,196,179,227,147,254,106,199,234,43,122,57,50,115,61,31,69,65,202,77,71,204,172,123,211,180,163,16,130,221,128,196,73,108,42,146,119,248,21,19,183,250,113,101,33,62,68,29,225,199,170,99,70,96,
111,203,89,6,231,76,223,48,163,191,238,23,19,102,154,160,170,97,143,157,2,14,65,80,53,28,138,45,232,83,37,18,26,210,42,251,195,134,124,221,247,65,91,67,23,79,255,39,27,130,95,193,57,79,186,111,66,58,175,
54,198,230,180,159,178,81,240,201,10,233,36,5,80,172,140,40,243,239,99,67,20,139,55,199,199,201,126,50,43,98,45,109,65,55,253,161,18,231,63,241,214,186,5,177,134,83,218,199,196,90,237,114,107,11,98,141,
167,180,253,88,67,11,140,96,231,207,253,194,224,12,85,48,212,215,162,86,173,213,2,253,226,228,187,134,40,88,240,117,10,88,133,8,104,60,212,131,97,252,154,133,83,195,175,137,56,89,100,131,12,49,52,222,
152,123,252,227,150,69,6,240,41,14,4,11,245,1,225,131,69,88,150,224,105,78,13,39,136,181,25,128,200,78,12,122,89,52,242,128,17,10,44,133,15,73,164,90,253,15,129,135,151,236,149,249,251,221,49,127,143,
237,180,186,99,253,75,206,1,124,207,231,0,110,47,57,7,240,175,63,7,16,44,57,7,240,61,159,3,24,80,114,14,160,24,231,0,66,37,231,0,138,58,7,112,199,47,224,28,192,192,146,115,0,103,116,14,96,80,201,57,128,
162,92,235,206,31,229,28,192,93,69,182,112,10,111,232,35,31,179,158,125,158,91,112,46,182,136,13,125,255,7,236,62,85,255,88,27,250,131,75,54,244,139,114,58,239,231,180,161,31,62,51,242,64,79,176,222,208,
58,199,152,31,197,28,95,195,47,167,89,203,191,214,231,115,243,200,46,97,97,196,62,132,96,56,53,117,130,62,132,58,157,175,229,29,190,10,199,179,117,93,227,211,88,206,40,136,27,219,14,208,207,98,31,57,179,
100,139,189,40,104,238,254,137,236,131,158,61,91,236,247,156,117,59,155,73,110,81,222,251,19,113,173,95,234,22,123,214,89,231,136,63,236,22,123,118,201,22,251,79,99,139,125,200,89,178,197,254,167,146,
45,246,162,182,216,135,254,2,182,216,239,251,81,154,2,73,166,147,216,163,147,245,36,66,175,167,128,45,98,110,246,97,39,39,177,62,195,201,249,29,222,99,242,26,118,11,249,144,56,170,195,215,48,55,10,50,
83,7,15,241,111,84,241,53,252,125,55,69,52,201,228,245,254,95,192,166,247,3,54,50,176,213,207,191,97,120,207,101,11,117,178,248,163,89,126,89,199,223,76,251,58,102,244,190,200,234,136,63,229,147,168,35,
42,78,89,36,143,209,17,191,53,166,128,78,214,43,77,206,179,85,61,225,71,85,207,57,234,95,188,107,93,212,223,208,211,37,115,216,47,96,27,250,207,167,110,96,97,35,225,190,219,7,234,102,95,199,77,217,250,
199,73,112,133,127,90,43,225,231,249,14,198,240,183,65,139,108,96,61,167,127,111,33,36,15,6,254,9,48,191,129,77,0,0};

const char* bitManglerEditor::lcd_bin = (const char*) resource_bitManglerEditor_lcd_bin;
const int bitManglerEditor::lcd_binSize = 5469;

// JUCER_RESOURCE: metal2_png, 141532, "metal2.png"
static const unsigned char resource_bitManglerEditor_metal2_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,1,124,0,0,0,162,8,6,0,0,0,66,164,118,33,0,0,0,1,115,82,71,66,0,174,206,28,233,0,
0,0,6,98,75,71,68,0,255,0,255,0,255,160,189,167,147,0,0,0,9,112,72,89,115,0,0,11,19,0,0,11,19,1,0,154,156,24,0,0,0,7,116,73,77,69,7,216,7,21,20,1,9,156,182,205,22,0,0,32,0,73,68,65,84,120,218,76,188,217,
179,29,199,157,231,247,201,181,246,115,206,93,176,131,32,72,2,32,9,130,20,23,81,82,171,165,222,236,233,110,143,237,136,25,135,215,39,191,244,216,30,143,237,232,55,191,242,31,178,39,60,237,238,118,47,106,
73,35,137,162,184,136,11,72,98,95,46,112,247,253,220,179,87,85,102,250,33,11,80,63,32,2,1,220,56,183,78,86,230,239,247,221,126,41,254,233,151,191,14,109,59,167,173,107,218,214,225,164,6,160,169,27,140,
16,104,35,80,2,148,16,84,131,101,30,172,175,241,205,207,62,230,210,133,151,57,119,237,34,78,180,40,239,80,18,172,209,216,36,161,223,63,133,233,45,177,117,124,200,227,251,183,120,114,251,75,246,190,254,
26,67,78,175,119,142,55,191,255,30,75,151,206,224,165,198,26,195,210,96,64,90,85,12,23,115,214,159,110,80,207,103,60,126,248,13,251,119,238,224,234,150,94,186,204,91,63,248,33,217,169,20,124,3,94,32,181,
65,41,129,210,26,165,21,139,89,77,150,230,148,189,62,16,112,174,101,62,95,128,119,212,77,131,16,1,137,3,60,187,187,7,108,174,237,210,91,121,129,83,47,92,160,168,250,156,59,119,26,233,107,112,11,156,175,
105,230,11,188,111,113,206,17,66,64,232,4,99,4,174,117,16,160,118,129,135,247,159,96,102,11,46,92,125,1,100,67,8,2,165,3,56,135,209,6,109,44,253,254,25,100,81,241,205,131,199,60,184,115,139,7,159,252,
18,119,180,143,17,57,111,191,243,61,94,250,238,235,228,189,12,99,44,202,100,100,69,159,160,19,214,119,246,216,95,223,97,230,27,238,124,245,17,39,79,214,8,243,134,179,103,95,224,221,31,255,30,50,87,104,
165,9,65,146,88,131,54,154,128,4,1,74,10,2,146,69,237,24,44,173,144,165,150,186,169,9,206,179,152,207,8,161,197,181,158,249,98,142,148,10,132,100,111,107,155,167,247,111,51,153,45,120,247,15,254,28,33,
19,242,126,143,213,149,30,218,55,184,118,193,108,50,162,174,231,248,0,222,181,136,32,8,82,34,9,180,206,211,44,90,180,181,120,215,32,104,105,189,135,16,176,90,160,141,1,161,233,245,151,209,121,159,7,143,
215,185,125,231,91,238,124,250,33,114,58,225,226,233,243,188,118,227,117,138,115,167,64,43,180,78,201,242,18,155,85,20,69,197,120,182,96,123,115,135,217,116,196,131,123,223,48,218,188,135,155,215,12,6,
171,92,123,227,45,202,51,203,184,214,35,141,66,4,208,218,96,140,166,109,3,70,41,154,166,197,135,192,188,110,105,131,229,202,181,43,180,243,5,245,98,202,246,250,19,126,242,215,127,197,225,240,136,241,120,
206,31,254,241,159,178,122,225,12,198,104,22,135,123,236,60,125,132,151,138,11,111,188,199,217,11,151,72,108,194,202,242,50,211,147,33,251,219,219,76,143,142,200,150,74,80,26,165,20,190,105,104,131,71,
0,174,109,241,8,164,82,72,64,74,79,219,58,132,0,31,2,73,146,145,38,5,105,94,17,164,229,225,253,251,220,186,249,27,70,123,235,148,105,201,197,23,95,164,92,93,65,40,131,181,26,97,18,210,172,79,81,14,232,
247,6,28,13,143,56,62,56,226,228,228,144,39,119,190,66,182,39,88,165,25,244,207,112,234,149,43,72,45,113,206,163,173,69,0,24,139,213,6,25,4,173,247,120,60,10,104,23,13,194,22,156,61,127,158,118,58,163,
110,27,22,109,77,51,27,227,22,53,141,15,40,163,113,222,81,207,38,236,223,189,207,167,63,253,21,181,213,252,222,255,240,223,240,242,75,215,88,233,13,168,210,148,201,240,152,245,245,199,108,238,238,112,
246,210,11,36,64,240,32,77,172,45,222,75,156,107,144,4,130,16,8,2,34,4,66,240,120,239,8,4,172,214,164,197,50,89,57,64,107,203,193,238,46,183,190,254,21,219,235,15,41,84,198,165,171,215,232,173,172,0,130,
36,77,201,138,30,105,222,35,205,75,156,111,25,15,199,180,222,51,25,15,121,112,251,11,14,215,31,210,206,23,188,124,253,93,206,92,186,132,210,2,173,52,66,9,144,6,37,20,0,129,128,18,18,148,68,4,112,77,32,
93,89,38,79,114,92,221,224,219,150,166,169,169,23,51,22,205,60,62,187,0,231,60,163,245,109,110,254,251,159,48,222,122,194,185,31,191,205,141,127,253,175,24,244,87,73,179,12,221,6,230,211,41,179,201,152,
105,93,131,12,40,17,144,90,34,144,132,0,222,5,188,107,65,170,238,115,29,50,128,140,21,13,41,20,105,94,146,15,150,72,210,30,243,89,203,238,246,14,15,110,125,198,214,147,123,12,6,61,46,190,252,50,189,165,
37,148,80,36,89,73,86,84,100,85,159,44,205,25,143,198,168,191,248,95,254,221,7,74,107,148,84,132,224,113,14,164,16,136,0,34,4,172,146,8,41,17,8,166,205,140,245,91,143,184,112,238,18,103,94,57,141,178,
18,45,4,66,128,16,129,204,90,76,82,80,244,151,152,185,134,141,39,247,185,251,213,199,236,221,190,139,9,150,149,229,75,188,250,238,59,156,126,229,60,40,73,106,115,6,131,62,121,85,49,110,91,54,55,55,57,
25,30,179,185,118,135,253,111,111,227,22,45,185,234,113,245,250,13,86,94,60,69,235,60,2,129,50,10,137,66,8,133,214,26,99,20,222,57,172,45,200,138,10,147,164,104,45,209,90,1,129,182,105,49,90,16,16,8,161,
40,138,146,249,98,193,124,62,162,110,29,137,73,168,107,71,154,101,36,137,65,116,69,76,8,1,66,34,4,16,28,74,9,124,16,248,16,152,205,27,82,109,72,151,10,164,145,8,225,145,210,34,5,120,231,209,202,144,229,
61,210,222,18,219,195,17,223,124,251,53,15,62,253,53,237,238,30,131,98,149,27,223,121,143,171,239,95,199,73,176,38,33,205,74,146,172,66,154,140,189,225,136,189,173,29,26,191,224,246,183,159,51,124,116,
23,209,180,156,89,185,192,141,247,191,139,46,19,188,247,24,99,48,214,162,181,121,254,172,4,9,66,16,130,227,100,120,194,100,210,50,88,62,133,146,10,33,37,74,9,164,84,120,239,240,206,161,149,66,74,48,89,
138,175,107,218,197,148,233,124,66,49,88,161,94,52,184,198,81,244,122,72,226,247,10,8,154,182,65,8,129,0,132,148,120,239,128,120,160,133,84,104,25,8,2,4,160,20,72,101,144,74,147,164,5,73,57,96,60,119,
60,126,252,152,47,127,254,19,252,201,9,47,158,127,145,27,223,123,135,234,236,10,32,81,198,144,100,57,89,49,32,45,74,70,211,5,219,219,59,204,231,19,30,222,191,195,240,233,29,140,10,164,42,229,202,235,55,
232,157,61,13,65,32,132,64,10,141,0,180,214,120,226,154,72,41,80,90,209,52,13,33,4,70,7,123,28,236,141,88,57,123,10,171,45,70,27,194,108,202,240,112,200,202,210,105,110,124,231,77,148,86,24,109,192,42,
180,135,227,163,93,70,135,7,200,172,36,177,41,117,211,98,139,2,37,36,69,85,161,173,194,7,143,115,30,239,61,18,249,188,128,8,1,74,197,245,247,128,6,164,84,4,15,73,90,82,84,3,146,52,167,105,26,190,248,248,
63,114,244,116,141,94,53,224,197,87,174,80,173,46,163,173,197,26,131,210,9,105,90,146,230,21,131,254,50,147,201,132,163,131,3,102,227,33,143,110,127,137,106,39,88,107,232,175,156,225,244,165,151,208,105,
138,148,26,215,122,108,247,25,66,104,132,82,72,4,4,144,66,34,186,181,219,91,123,194,193,193,144,115,175,188,68,34,20,174,245,160,45,82,107,164,144,177,32,121,135,111,91,108,94,226,166,19,246,159,110,114,
124,114,68,190,186,74,158,102,8,165,73,138,156,209,238,46,95,253,250,35,86,207,157,33,75,19,32,238,135,186,174,65,72,148,4,41,37,66,8,180,164,219,79,2,8,24,173,73,243,138,180,183,68,94,246,9,190,229,222,
55,31,115,239,219,47,232,87,203,92,125,253,117,202,165,37,148,54,36,105,70,158,151,20,229,128,36,45,144,74,113,114,60,164,241,158,225,241,17,107,247,110,50,218,121,66,104,225,133,203,215,120,225,202,21,
140,141,245,78,25,131,82,22,35,21,74,105,140,82,40,169,144,93,205,147,82,208,204,23,108,221,125,136,94,25,80,150,37,18,137,16,10,41,36,174,110,144,82,34,133,36,0,166,200,16,222,115,180,126,200,120,107,
141,214,57,122,47,156,67,120,143,78,83,148,146,248,198,197,61,32,4,224,9,62,32,67,192,123,16,66,210,58,135,20,18,169,64,43,133,210,10,188,71,72,129,77,115,178,106,64,81,13,208,38,199,213,11,190,254,232,
23,108,174,221,99,229,212,105,94,186,246,42,69,89,33,133,34,73,82,202,254,128,162,183,132,77,82,234,217,130,227,131,35,212,191,253,203,255,243,3,31,64,137,88,232,67,215,97,133,240,40,37,81,42,128,15,180,
193,113,124,48,164,234,245,41,86,10,132,146,4,20,8,143,38,110,104,147,164,20,229,18,33,177,60,90,123,200,173,223,254,154,141,155,183,8,11,197,133,115,215,184,254,131,119,25,92,90,65,91,73,106,51,6,189,
1,69,175,98,14,108,108,110,50,60,58,96,253,225,93,246,239,220,166,30,207,201,210,101,174,189,241,29,78,93,57,79,80,2,231,60,72,129,81,6,41,37,198,42,164,20,200,174,216,77,230,13,66,230,20,189,62,82,72,
148,84,24,163,17,2,66,0,144,224,227,207,102,89,134,247,45,154,6,147,149,52,206,51,26,79,176,89,65,150,36,241,51,101,108,24,72,79,8,160,164,198,249,22,215,58,156,135,36,73,80,198,34,8,40,33,208,90,33,130,
71,74,69,146,100,100,213,128,177,19,220,189,115,135,207,127,254,143,140,55,215,57,221,63,195,247,254,232,15,120,225,198,75,168,196,160,180,33,47,42,108,86,160,147,156,131,209,132,237,141,93,166,179,49,
183,110,126,198,193,157,111,209,13,44,15,78,241,253,63,252,17,249,233,62,66,40,18,99,145,186,43,226,90,227,188,199,251,128,144,130,214,57,130,16,132,224,121,250,240,9,243,133,39,171,150,176,214,116,107,
165,145,82,35,17,120,231,113,193,19,128,178,170,104,230,142,163,131,77,22,243,57,189,149,85,218,186,97,62,111,112,82,33,165,164,109,91,140,138,104,72,202,248,30,32,68,100,27,2,2,137,144,160,0,33,35,122,
147,202,160,76,4,2,94,165,236,239,110,243,155,127,250,91,56,62,230,205,235,111,114,227,247,223,71,87,57,33,40,208,6,107,82,242,106,137,164,172,104,125,96,103,107,23,218,57,247,238,126,195,240,233,3,140,
116,228,166,207,203,175,189,65,255,252,121,16,18,173,45,82,105,66,8,241,16,74,13,200,216,160,61,4,33,33,196,166,165,172,230,224,225,125,198,243,57,75,167,207,146,228,37,253,165,37,150,122,171,188,249,
238,119,176,85,70,240,129,128,195,123,72,139,146,102,50,231,248,104,159,241,201,49,197,202,41,178,196,114,180,127,132,73,51,138,44,197,133,64,144,2,92,27,247,140,8,128,71,138,216,96,165,0,41,20,82,60,
43,42,2,165,36,89,57,32,171,42,22,139,25,183,190,250,132,135,55,63,227,236,169,179,188,242,198,155,164,131,1,198,38,40,45,81,58,193,166,37,182,232,51,24,172,48,157,207,56,58,56,224,232,104,135,135,119,
191,162,153,236,98,148,164,63,56,199,153,75,47,35,147,20,109,13,90,234,8,144,148,68,42,131,144,42,50,192,16,16,74,131,160,91,183,22,109,19,214,111,126,205,206,241,144,115,47,93,38,213,9,1,1,34,22,196,
196,88,164,16,40,161,144,70,147,22,57,212,13,235,247,238,115,184,189,67,113,225,34,210,183,204,198,83,76,81,225,142,103,20,75,171,148,101,78,144,130,208,122,66,27,16,74,32,84,60,183,66,202,248,108,29,
112,84,74,129,50,100,213,50,105,90,160,180,228,235,79,126,202,205,143,63,225,204,153,11,188,246,230,13,202,193,50,90,27,180,73,72,179,2,147,87,164,69,15,171,53,251,123,7,204,231,115,142,14,119,185,119,
243,19,198,123,235,168,32,184,124,245,13,46,191,118,29,107,19,140,77,48,54,69,43,19,65,147,177,40,99,145,42,42,7,66,8,132,144,200,0,58,73,112,227,49,119,63,253,146,252,236,50,101,89,34,164,70,106,141,
73,44,90,72,124,219,198,134,166,36,249,82,31,223,74,118,31,111,48,218,218,64,244,82,146,254,128,201,112,130,76,45,89,150,33,60,120,41,98,211,69,18,66,64,33,112,2,130,0,43,65,41,137,148,18,37,36,66,72,
148,209,152,44,167,26,172,96,147,146,102,49,225,139,95,254,140,135,183,191,229,242,107,215,184,246,198,107,100,121,134,148,154,164,40,40,202,146,170,55,192,216,156,118,209,176,185,181,203,108,50,69,253,
87,255,245,255,248,65,86,230,177,112,8,9,56,164,247,93,129,244,177,11,43,137,20,26,47,52,72,73,98,36,56,23,59,178,16,72,2,73,106,73,146,30,89,111,192,246,209,46,55,63,253,53,143,190,184,133,170,45,47,
94,120,149,183,255,248,61,138,211,57,32,200,109,70,158,230,228,253,30,78,74,182,247,118,57,62,216,229,201,163,123,108,223,186,133,156,45,72,116,197,149,235,239,112,241,173,87,8,70,65,16,104,229,81,82,
98,140,66,40,34,154,52,6,79,44,232,46,72,54,214,54,177,54,195,22,37,202,218,248,243,214,32,165,194,181,11,16,18,215,58,242,34,71,120,88,204,199,204,102,11,138,94,15,239,90,22,179,38,210,236,60,141,20,
92,64,136,237,23,8,120,39,105,26,79,93,47,48,105,22,37,20,4,129,128,150,17,41,41,147,144,230,125,84,86,177,177,179,195,231,191,252,41,135,15,30,115,245,226,85,126,248,103,127,66,117,126,9,132,66,27,75,
146,101,36,89,137,78,10,78,22,13,91,79,183,168,103,19,30,63,248,154,189,175,63,199,6,201,202,202,25,110,188,255,30,197,185,83,4,65,60,32,82,129,160,67,247,18,33,21,206,69,100,27,95,139,194,59,79,81,245,
185,251,213,23,36,73,130,73,74,146,52,35,49,6,41,65,105,77,0,124,112,72,4,218,90,210,44,101,58,28,49,29,29,224,189,196,230,37,243,217,156,122,90,83,245,151,72,173,194,24,21,27,71,136,82,94,100,78,34,126,
150,239,208,117,112,29,166,139,13,48,77,11,108,94,113,56,28,242,179,191,250,247,236,63,124,202,247,127,239,135,92,188,126,5,108,138,146,50,202,48,73,74,150,22,228,69,15,143,102,103,115,151,227,227,3,118,
183,159,240,228,214,231,164,162,165,204,7,188,252,218,117,122,103,78,33,148,69,105,29,27,139,20,177,160,41,141,49,9,82,105,132,8,64,100,101,113,157,36,222,123,138,170,98,235,222,45,234,224,209,210,162,
202,62,103,95,56,139,73,162,68,168,180,166,173,27,188,15,212,117,19,129,201,100,204,248,228,128,163,163,35,138,229,83,148,105,130,66,144,245,7,88,161,168,219,184,63,69,136,212,252,217,154,60,99,31,218,
196,243,3,32,180,64,42,77,213,95,162,109,27,190,248,228,87,220,253,242,43,94,184,116,153,11,87,174,146,150,101,124,14,107,17,66,162,109,134,45,122,100,121,201,124,190,224,240,96,159,163,227,67,214,239,
223,164,25,30,145,26,197,210,242,121,78,95,190,138,205,114,180,84,72,165,81,202,16,16,72,97,64,40,164,49,40,25,207,147,143,173,41,190,75,60,65,40,242,60,225,219,159,255,130,227,217,156,211,47,190,64,146,
38,104,161,8,62,96,178,20,171,45,109,211,208,180,53,38,79,201,243,132,233,193,49,59,155,27,140,71,19,206,190,116,25,163,52,243,209,140,151,190,115,131,213,126,15,161,20,193,121,164,0,173,5,245,162,230,
100,60,34,43,226,115,106,209,109,149,14,241,43,155,83,84,75,24,99,248,246,211,15,185,251,249,87,92,186,252,10,47,94,123,25,155,231,152,36,197,24,75,146,229,36,233,179,63,9,7,7,71,140,198,83,134,199,123,
60,185,123,147,253,167,247,144,65,114,249,234,13,46,95,127,29,155,166,8,165,48,214,70,150,99,84,44,246,186,107,194,82,61,175,105,2,58,118,47,72,203,156,225,157,53,30,125,115,155,222,197,179,244,251,125,
148,82,4,23,226,57,4,66,183,207,132,86,228,43,21,227,253,19,142,247,246,152,110,111,161,151,250,36,131,8,66,109,158,146,218,20,213,201,56,129,208,129,203,248,59,181,138,251,68,171,184,79,144,17,233,75,
161,200,251,3,178,188,199,124,58,227,211,159,252,3,79,31,175,113,237,59,215,57,127,249,34,198,36,104,169,72,211,216,4,179,52,39,173,250,120,23,216,120,178,205,116,50,99,50,62,70,253,151,255,234,191,255,
128,0,89,81,69,2,26,191,111,44,114,1,2,93,129,21,10,105,18,164,0,21,4,200,168,79,18,2,186,147,103,202,222,10,181,10,220,185,245,5,223,254,242,55,136,169,225,245,55,222,225,250,31,190,135,205,99,145,176,
58,37,207,115,138,222,0,210,132,253,163,35,182,182,183,88,127,116,143,245,175,190,130,233,140,212,148,188,242,234,219,92,250,206,85,130,12,180,109,32,132,72,245,180,138,109,80,27,3,82,225,137,29,80,116,
180,42,224,120,240,245,109,150,87,79,19,132,33,203,51,148,16,24,19,169,105,219,122,234,69,141,181,150,172,200,153,78,166,204,38,35,78,78,78,72,211,18,45,20,77,221,18,148,38,47,75,186,69,64,4,73,240,1,
33,21,109,219,128,115,17,141,208,161,217,16,48,70,209,122,143,146,134,172,26,48,106,61,191,252,167,191,99,237,243,111,120,243,181,27,188,251,71,223,39,89,41,99,183,182,6,109,45,73,154,97,211,138,153,23,
172,61,217,96,111,107,131,205,141,71,172,125,241,25,105,227,56,181,116,142,27,63,248,30,217,233,85,218,16,215,65,119,69,77,25,29,15,181,182,104,157,16,31,39,34,90,1,241,103,149,197,38,146,7,55,191,166,
90,89,70,201,4,153,164,164,169,69,138,16,11,80,136,34,171,20,144,100,57,82,42,78,134,39,140,135,135,180,14,170,162,71,158,231,140,167,11,122,43,43,88,19,209,190,119,158,32,98,33,245,222,197,119,224,61,
218,104,188,107,145,74,71,6,32,53,105,89,49,91,56,254,227,223,252,13,254,240,136,239,254,224,123,156,185,122,25,47,21,214,90,132,84,24,99,72,179,156,52,239,225,141,225,201,211,13,70,199,135,108,172,63,
226,225,151,191,197,122,71,191,92,225,218,155,111,145,159,90,65,155,248,189,101,39,9,72,25,217,156,148,186,67,198,54,2,237,40,238,208,58,135,146,145,238,61,43,124,107,95,127,142,72,45,109,43,168,6,75,
228,89,65,104,35,67,146,202,160,4,36,137,37,40,73,154,88,78,142,142,25,31,236,113,114,50,103,245,197,139,164,137,161,169,91,146,178,138,178,87,112,207,207,79,100,27,29,186,87,207,154,77,64,171,120,158,
132,80,216,44,229,214,231,159,241,240,203,111,120,249,181,215,89,62,127,142,36,75,72,146,36,22,37,25,153,170,78,11,178,172,162,110,28,199,135,199,12,15,247,88,191,255,21,147,189,45,180,82,156,185,112,
153,83,151,46,147,102,5,105,150,33,181,142,239,67,202,200,64,141,33,4,72,108,130,214,145,233,57,215,70,28,67,244,98,132,243,216,44,37,180,11,110,254,226,87,108,29,29,81,156,62,77,81,86,84,54,165,109,29,
158,40,235,4,231,16,66,144,20,5,42,192,116,120,194,250,195,71,120,35,56,253,242,203,244,138,18,101,21,189,213,21,164,243,4,33,81,157,252,183,152,207,80,46,144,22,121,44,172,16,61,142,174,240,39,89,65,
217,235,115,235,211,15,121,122,251,22,87,174,95,231,236,165,11,232,196,118,5,90,119,30,77,74,86,244,73,211,148,253,237,29,102,211,57,179,201,9,15,191,253,140,221,245,123,104,149,112,237,198,187,188,114,
253,58,105,154,161,85,148,128,35,3,140,82,140,148,18,169,21,74,167,208,185,124,193,181,4,2,190,107,216,194,40,210,34,229,201,175,111,178,190,118,159,236,252,10,42,73,200,178,12,2,56,15,18,129,18,2,135,
64,37,150,36,77,25,30,140,216,223,220,96,54,60,38,57,127,134,222,202,42,161,245,100,121,134,53,54,174,97,8,8,66,183,111,60,72,213,53,228,8,148,68,8,32,163,87,89,246,151,8,30,190,250,233,79,57,58,56,228,
213,119,111,208,95,30,116,251,41,50,125,155,36,36,221,25,146,202,178,181,182,197,162,105,152,140,14,185,127,251,11,212,191,254,111,255,187,15,218,198,211,44,60,101,89,117,139,222,109,78,2,158,88,224,67,
8,177,9,116,218,118,16,242,249,203,210,210,144,151,125,68,158,114,247,254,215,124,242,247,255,72,54,47,121,251,253,239,114,245,253,87,145,169,69,34,48,90,83,21,5,69,111,128,201,75,182,135,71,172,63,89,
227,241,253,219,108,124,253,21,126,60,33,53,37,87,174,189,205,229,239,190,74,208,157,46,171,4,90,73,220,51,122,41,227,23,179,58,82,120,66,212,73,141,150,104,147,80,183,83,214,238,220,227,212,233,211,212,
11,79,86,150,24,29,13,53,219,25,71,82,4,132,148,84,253,146,233,116,70,91,143,169,23,53,69,217,199,121,199,100,58,3,173,200,211,60,30,10,17,186,131,28,205,38,173,52,66,8,124,235,176,54,10,214,62,64,83,
59,178,188,135,179,150,15,127,249,115,158,252,230,75,222,127,247,123,92,251,254,91,232,220,16,136,210,80,146,164,24,155,99,109,78,163,52,247,31,62,97,115,125,141,71,223,124,193,246,189,111,73,155,134,
243,167,95,224,205,31,255,16,185,52,96,182,104,208,82,96,77,130,73,109,212,94,101,164,233,198,22,177,40,133,142,234,136,16,117,124,223,160,148,68,167,41,110,49,229,193,173,175,209,89,138,71,18,84,66,154,
229,104,33,49,198,162,19,131,107,26,68,8,84,253,30,184,192,241,193,30,211,147,125,100,146,48,88,93,102,54,157,114,50,158,69,125,221,118,212,87,69,191,64,74,129,146,209,68,22,120,148,86,8,84,164,72,66,
48,154,183,124,241,171,95,83,121,199,91,191,247,14,217,106,31,101,162,55,164,180,64,27,137,73,50,146,188,135,176,9,143,215,54,57,222,221,229,193,157,47,217,248,246,107,196,98,193,165,139,47,113,245,237,
239,80,158,90,69,106,25,81,145,16,157,244,104,98,129,39,234,210,74,37,88,155,32,180,233,200,89,220,191,222,7,188,247,184,16,80,86,163,66,203,198,163,111,57,216,223,135,164,164,168,122,244,6,3,92,29,11,
154,49,138,186,109,32,128,78,50,170,162,100,58,28,114,184,183,206,241,112,66,57,88,138,168,119,94,199,226,39,160,109,227,57,241,190,141,38,70,136,231,196,119,154,57,2,92,16,4,239,217,89,123,196,201,246,
46,151,94,125,157,114,101,64,154,198,66,173,181,65,107,19,25,131,180,216,52,71,8,205,104,56,102,120,178,207,218,237,207,153,29,109,147,39,37,23,95,188,194,217,151,174,98,147,12,99,12,82,155,40,115,197,
78,136,144,34,50,49,231,176,73,138,212,26,39,162,57,41,156,199,249,88,116,130,119,120,33,200,123,21,97,58,227,214,71,159,178,187,191,79,121,122,149,149,213,83,20,69,142,155,45,104,9,40,21,27,9,72,108,
145,96,36,140,143,14,217,120,242,148,198,181,244,206,158,70,25,75,235,28,121,89,32,157,239,36,191,128,48,146,180,200,35,138,245,1,161,159,57,30,32,144,72,165,88,191,123,151,233,241,17,151,174,189,76,209,
47,35,59,66,160,165,38,177,9,214,26,146,52,199,230,57,147,209,148,225,184,166,169,39,220,191,249,27,14,55,158,144,103,37,111,188,247,125,94,124,237,85,146,52,37,116,210,167,124,174,211,199,253,235,156,
67,40,141,181,41,82,201,184,111,67,192,7,31,139,109,240,248,224,59,100,174,121,244,243,207,121,252,197,103,76,149,99,112,238,28,101,89,254,78,94,69,226,219,232,141,37,85,70,94,21,28,172,237,112,176,183,
203,240,96,27,187,210,199,218,156,182,105,192,106,50,155,118,236,32,238,79,217,189,171,136,48,65,105,133,111,61,42,209,40,21,37,202,187,159,124,70,16,142,75,111,188,66,158,166,157,28,20,65,147,73,226,
158,207,202,30,54,201,217,217,60,96,222,54,44,102,67,190,249,228,151,172,221,187,133,250,47,254,236,207,63,48,86,179,104,3,206,5,202,94,21,191,120,103,166,56,87,19,8,16,162,137,17,240,72,233,129,104,108,
18,2,90,27,122,131,21,54,134,123,124,242,247,255,4,199,138,247,126,244,3,46,190,126,142,58,4,4,209,17,127,70,55,146,188,98,84,47,120,240,240,33,107,247,110,179,117,235,91,252,116,142,14,9,175,189,254,
29,94,122,239,26,24,104,90,31,205,42,17,11,190,148,10,163,20,85,191,135,177,73,212,204,85,167,19,119,93,91,8,200,139,156,237,245,39,44,166,51,122,43,203,76,166,13,38,77,177,214,160,165,64,25,221,105,99,
113,145,181,177,28,238,238,226,252,130,233,100,70,213,239,225,189,227,228,100,4,40,242,170,66,17,144,29,171,209,242,25,146,19,120,34,115,241,132,206,168,83,216,44,231,206,189,251,108,124,113,155,119,191,
251,46,167,175,92,68,89,29,77,189,214,145,38,25,214,24,146,172,34,104,203,163,245,29,182,54,54,121,124,235,11,14,31,221,69,212,45,47,156,185,196,245,31,126,15,179,210,239,52,197,152,58,49,198,98,76,119,
144,145,72,36,54,45,208,137,65,27,131,16,129,224,28,136,136,106,149,208,4,2,85,175,98,49,62,97,237,254,183,28,141,102,228,121,137,214,154,188,200,145,93,81,86,34,162,118,8,244,122,21,139,217,130,209,248,
144,195,189,61,148,201,40,202,156,102,54,143,77,173,170,34,210,239,172,182,14,39,34,149,6,201,115,128,16,8,56,231,217,89,223,32,87,138,115,175,188,128,76,116,212,247,69,92,59,163,227,1,76,108,142,74,10,
14,143,70,236,239,15,121,116,231,38,235,183,190,66,53,13,151,47,94,230,181,247,223,37,233,247,80,29,16,0,209,81,241,40,105,117,60,28,144,36,105,129,53,182,99,24,145,137,137,16,117,249,224,125,39,239,8,
210,172,192,207,103,204,39,135,180,13,44,157,90,5,41,41,170,30,194,181,248,16,141,105,240,132,224,49,105,134,53,154,241,240,152,131,157,13,22,94,176,122,254,60,137,49,212,179,5,105,81,116,169,147,238,
224,134,136,244,17,160,148,142,159,21,2,18,65,179,168,193,65,177,60,192,164,9,82,122,140,53,8,4,198,152,104,244,10,137,210,25,69,53,224,224,248,132,249,252,132,7,95,126,196,252,104,151,52,41,120,249,181,
27,44,95,124,1,101,162,62,47,149,140,232,158,206,70,16,170,243,159,34,211,42,171,62,50,68,89,43,250,47,145,149,137,16,58,243,61,16,36,164,101,201,201,246,54,187,143,159,208,40,193,43,215,95,71,8,65,86,
150,184,69,141,247,14,165,37,33,120,130,20,36,101,1,117,203,238,214,54,91,79,158,146,100,150,114,121,9,218,88,43,178,178,196,57,23,229,3,215,18,2,113,223,133,240,188,41,197,117,146,44,198,99,218,166,166,
90,26,32,149,68,155,14,40,41,21,37,76,45,49,73,142,78,75,188,15,28,14,231,204,235,17,143,190,253,132,147,157,39,104,93,240,250,219,223,229,236,229,75,24,219,33,122,165,209,82,129,146,93,160,64,116,77,
216,97,109,130,146,6,209,37,117,124,7,156,188,143,239,60,116,38,96,50,168,112,163,5,123,119,30,49,222,217,102,245,181,107,84,101,137,205,114,12,2,31,60,200,103,251,44,160,203,20,37,21,59,27,187,236,29,
110,179,104,230,100,131,62,218,166,8,231,176,101,134,81,22,129,32,184,152,34,147,194,71,16,35,68,4,81,34,86,21,239,3,199,187,7,104,163,168,86,43,16,1,223,250,216,200,148,138,13,88,107,210,188,32,43,250,
204,167,13,71,163,49,77,61,226,230,135,255,145,205,135,247,233,47,45,163,254,236,79,255,232,3,16,216,212,226,218,64,93,215,148,101,17,187,97,247,75,163,169,39,99,39,14,157,65,41,163,137,170,164,196,90,
139,79,44,159,252,244,23,228,77,193,219,63,250,62,189,51,5,82,249,72,241,165,33,207,162,97,81,148,61,134,77,205,227,71,143,120,124,239,107,54,190,254,138,250,120,66,158,46,241,234,181,55,185,242,131,55,
105,165,71,16,191,8,226,153,246,23,117,71,107,53,121,94,62,127,198,182,13,4,231,209,38,22,219,232,254,43,122,203,125,54,215,159,176,179,189,141,182,5,77,211,98,210,156,36,205,98,113,211,10,165,4,109,29,
165,7,109,44,195,189,3,154,118,194,232,100,66,89,148,72,97,217,223,63,164,169,91,202,94,129,81,50,138,3,93,231,23,93,165,243,62,54,155,104,14,10,142,142,143,56,92,91,231,234,141,87,201,79,45,163,164,36,
181,18,68,100,12,177,249,164,232,188,100,119,56,98,235,233,38,247,190,248,152,221,219,223,96,131,228,242,165,151,120,251,143,255,8,209,235,161,149,33,205,18,140,86,4,192,234,78,194,81,6,169,36,94,128,
77,11,18,147,196,67,29,68,68,3,93,67,162,51,78,109,154,82,245,122,140,79,142,24,238,109,49,24,172,162,148,102,58,109,40,122,61,180,136,13,53,30,98,135,80,146,178,215,231,248,104,200,209,209,1,39,71,7,
40,163,41,11,139,107,29,211,133,167,168,122,88,99,112,62,70,87,227,249,245,248,142,89,68,153,40,50,128,44,209,100,101,137,232,210,83,145,17,40,148,142,135,217,216,148,52,235,49,119,129,135,15,31,114,251,
183,31,177,117,235,115,82,47,121,235,173,183,121,245,253,119,48,85,209,49,173,223,37,75,186,178,138,214,54,34,231,182,65,8,56,58,58,161,90,90,33,181,182,67,81,50,106,172,93,177,69,138,136,246,17,228,101,
201,124,56,100,116,180,77,43,45,89,153,51,159,206,233,45,173,160,4,56,23,186,230,17,27,163,77,115,116,8,28,238,29,176,245,244,9,94,91,86,86,87,153,45,22,56,23,168,250,131,24,89,21,252,179,125,34,80,202,
0,142,16,162,209,141,146,40,27,25,136,236,76,204,16,2,82,219,46,73,229,17,50,35,203,251,212,190,101,107,237,17,183,63,251,21,163,189,29,150,150,86,121,229,250,13,242,165,37,132,209,200,78,102,35,128,54,
150,224,233,130,21,160,2,184,224,169,155,154,237,205,93,122,167,79,147,235,4,231,218,136,209,159,201,122,29,21,145,74,163,117,66,217,175,216,121,240,152,181,111,190,97,145,37,20,85,137,71,208,91,30,32,
26,255,188,104,7,231,81,218,210,95,169,8,179,5,199,251,135,172,61,124,136,80,130,51,231,207,33,2,212,174,165,200,203,14,193,71,118,227,59,48,40,132,136,76,134,24,16,145,18,116,98,58,207,44,68,25,142,136,
208,17,50,122,77,121,133,73,51,142,14,70,28,31,237,242,237,39,255,200,104,119,139,178,92,225,198,251,63,228,212,249,115,209,95,84,10,58,249,70,116,7,54,218,233,145,225,135,16,152,157,140,152,54,53,121,
17,27,72,52,236,163,153,28,101,203,104,246,11,165,40,150,251,140,55,15,57,122,252,148,197,248,152,228,226,25,16,10,147,167,88,21,101,51,169,20,34,56,4,129,226,244,50,70,24,246,183,142,217,222,93,231,228,
120,159,114,101,128,145,81,246,212,105,138,177,113,111,137,238,28,61,75,184,117,41,131,216,129,188,71,42,129,208,208,182,45,50,196,231,180,218,160,117,100,251,105,150,147,85,125,64,115,180,127,204,238,
214,26,95,253,234,39,236,173,175,113,233,229,43,188,247,7,191,143,250,79,255,248,15,62,104,154,6,41,36,38,81,120,175,104,91,40,138,50,70,27,101,44,250,222,59,240,14,45,2,66,2,210,34,165,38,8,71,8,176,
177,177,69,30,20,23,95,189,140,29,164,72,209,196,196,134,136,52,169,40,11,178,188,192,25,203,195,167,79,121,120,239,22,79,190,248,140,118,60,37,51,43,188,241,230,59,92,126,231,10,65,71,51,67,41,13,74,
227,195,51,202,174,65,117,232,167,43,220,209,192,141,244,46,120,247,59,212,34,4,137,205,0,133,164,101,54,91,96,210,2,215,214,81,247,203,242,152,44,17,2,41,226,2,26,155,96,116,194,240,104,200,108,54,102,
49,175,233,47,47,161,180,228,100,52,234,138,126,47,54,161,224,17,93,2,67,73,201,188,110,16,66,131,140,201,24,66,64,155,78,71,86,154,52,81,72,29,80,90,96,109,130,54,6,147,148,140,219,192,253,251,15,121,
240,229,167,236,222,254,26,235,37,111,190,245,54,111,255,248,7,232,178,64,43,72,147,184,134,90,42,140,53,152,196,68,164,40,226,97,171,155,192,254,222,17,89,53,192,104,211,105,146,26,37,53,222,5,164,8,
56,239,128,168,247,27,21,165,155,163,253,61,146,170,4,47,169,235,134,180,44,48,70,63,63,252,62,248,152,228,177,54,102,205,71,39,44,38,35,146,172,192,166,73,103,10,19,101,12,21,229,21,223,182,56,223,34,
69,160,91,134,231,41,32,231,2,74,129,146,81,6,136,102,87,36,242,105,146,98,146,2,149,86,28,29,31,115,255,155,207,121,242,245,111,89,78,43,222,122,231,29,94,124,235,58,34,201,80,29,245,127,102,88,63,67,
192,82,42,132,146,136,46,251,30,8,180,139,41,79,238,61,164,90,90,38,203,138,46,8,30,117,100,136,40,47,178,16,135,11,130,36,73,25,29,236,112,180,191,143,201,123,8,239,240,1,178,170,143,145,18,215,182,8,
37,113,77,139,210,146,106,105,128,104,106,166,163,49,79,159,172,225,165,38,239,245,59,80,31,162,255,19,66,151,20,10,17,113,11,249,188,224,16,124,100,35,193,69,131,59,132,174,113,197,4,21,2,4,26,149,148,
244,123,75,212,147,33,95,126,244,19,198,123,59,84,189,85,174,190,245,38,73,175,135,148,157,63,37,34,218,142,114,150,238,10,233,51,123,198,211,184,22,1,52,243,25,15,191,185,199,217,151,95,36,183,41,174,
113,81,167,150,145,241,4,231,113,222,63,55,105,141,128,227,237,29,158,62,122,76,58,168,200,242,8,152,178,170,66,248,232,41,41,213,201,70,198,80,244,42,88,212,108,111,111,179,191,179,75,222,47,201,250,
3,130,7,165,13,89,145,71,38,28,28,194,59,162,234,45,186,179,19,58,120,29,89,145,107,27,164,238,2,23,93,250,74,43,21,227,215,121,133,144,150,217,201,46,119,62,249,37,59,79,214,56,117,246,5,174,191,243,
30,89,191,23,147,98,34,126,175,128,138,224,64,118,142,155,140,38,62,34,162,242,224,90,118,238,62,98,42,4,197,160,135,70,225,3,132,206,72,21,62,154,240,65,16,229,149,84,51,220,220,227,232,201,26,243,217,
132,252,220,41,188,23,216,34,195,40,21,67,12,207,204,121,1,89,85,160,133,102,103,99,151,195,195,125,218,102,70,182,220,199,38,41,65,40,108,146,118,96,64,224,159,205,39,132,24,66,120,102,230,54,173,199,
63,75,82,58,176,182,99,175,62,54,46,99,44,89,217,167,40,251,212,115,199,112,127,151,207,127,241,15,156,28,237,243,202,171,55,184,122,227,117,210,60,67,253,203,255,252,207,63,240,109,195,116,54,33,248,
64,146,38,248,32,88,204,106,138,126,31,105,68,140,227,53,53,180,77,191,40,144,84,0,0,32,0,73,68,65,84,135,0,37,46,40,16,1,231,22,113,72,75,39,244,78,13,208,90,197,197,9,45,190,245,88,155,144,100,25,54,
205,48,89,193,230,193,1,223,222,252,156,251,159,126,196,226,120,66,101,87,121,239,71,63,230,226,245,23,64,61,59,20,209,40,38,68,3,180,117,30,101,44,90,71,45,114,56,89,32,181,197,230,17,117,63,139,48,129,
71,72,186,28,171,36,73,51,38,163,41,214,180,209,176,83,58,14,30,161,200,178,12,41,192,152,152,117,117,109,75,94,229,72,41,57,220,219,197,55,115,154,54,80,84,21,214,88,102,211,154,214,5,6,253,94,204,218,
19,217,139,80,2,231,61,90,168,56,116,20,34,242,137,198,102,212,211,149,146,120,60,70,26,140,53,88,155,161,146,156,237,221,125,110,125,254,107,214,62,255,152,84,100,188,251,254,15,185,254,163,239,162,138,
36,250,22,90,69,19,71,91,180,53,24,109,159,27,52,162,203,49,55,45,204,103,19,30,223,125,64,217,95,70,217,148,164,115,249,69,151,67,143,166,101,220,56,69,85,225,92,96,124,114,192,222,206,46,189,229,101,
154,182,101,94,215,164,69,148,105,68,151,58,130,192,246,246,14,171,203,43,44,142,199,140,167,135,140,135,39,232,36,163,172,74,90,60,179,186,141,249,100,201,243,129,55,2,93,68,180,219,55,162,51,182,69,
148,54,132,236,36,135,78,127,79,146,130,36,235,81,123,193,237,155,159,113,243,195,95,48,48,25,239,253,222,15,57,125,237,101,164,49,93,134,60,34,117,213,33,154,72,193,59,228,22,158,197,31,197,243,66,59,
25,30,241,248,193,67,206,94,186,132,49,41,137,213,49,138,107,51,180,148,4,223,224,93,44,236,42,203,161,246,44,38,35,182,159,62,37,31,44,147,229,5,245,124,65,82,196,249,140,214,117,146,149,240,120,215,
146,229,57,169,177,236,109,110,241,228,225,67,106,231,233,45,15,80,34,102,186,243,178,194,117,8,49,184,6,100,136,146,91,164,133,72,225,241,190,237,164,140,14,216,60,43,246,82,198,180,74,111,153,214,47,
248,232,103,127,195,211,123,15,185,114,237,13,94,186,254,58,73,153,163,100,148,106,164,82,241,224,119,201,18,169,117,148,91,59,191,64,134,103,51,20,160,172,97,177,191,203,183,159,125,201,153,43,151,233,
247,122,72,4,206,183,32,2,161,109,227,176,88,112,32,32,27,244,80,1,54,238,63,228,96,115,147,149,115,167,177,105,70,91,183,20,131,1,90,104,32,196,156,190,247,40,107,41,151,123,184,241,148,253,157,93,158,
62,122,76,144,80,14,150,158,27,139,73,154,65,136,250,121,235,93,220,162,161,83,192,130,235,254,218,161,127,41,17,157,21,244,44,160,144,151,21,54,43,153,79,79,248,232,159,254,95,182,158,60,225,234,181,
27,92,185,113,131,178,170,226,58,116,76,78,72,21,229,67,165,98,156,82,198,250,228,187,255,119,93,216,64,41,201,55,63,253,21,161,204,88,61,119,6,133,192,187,24,106,136,205,167,37,132,120,46,108,153,97,
108,194,222,131,117,38,219,235,200,50,37,89,26,196,255,75,44,73,146,128,143,207,43,9,36,121,198,242,217,85,196,220,51,220,57,98,111,111,157,69,179,160,88,61,133,181,25,146,128,201,98,26,42,122,76,45,190,
147,155,35,16,16,177,222,136,24,150,9,50,128,240,52,109,219,189,111,69,146,231,244,7,167,144,58,97,124,124,192,199,127,255,55,28,237,239,241,230,119,223,231,165,107,175,128,148,76,230,45,234,127,253,223,
254,221,7,39,195,33,180,51,102,179,49,206,11,76,154,117,137,11,73,158,102,24,19,145,176,111,107,124,144,4,60,254,217,162,6,31,221,126,64,203,231,254,84,103,64,128,81,6,163,19,146,172,98,236,90,110,221,
250,138,219,31,125,72,125,48,227,204,242,75,188,243,251,63,224,204,213,51,72,29,197,51,101,4,82,11,180,54,49,41,33,21,70,131,209,6,163,36,82,194,100,60,102,127,247,152,52,239,199,56,146,137,6,106,98,147,
231,83,160,32,98,198,189,44,57,218,223,161,158,77,104,145,72,163,169,167,115,132,49,36,69,241,92,11,126,166,183,46,45,15,104,91,199,241,225,62,147,241,17,32,200,202,2,147,100,184,198,97,210,148,44,207,
163,59,239,28,222,121,218,166,69,235,248,82,92,27,15,150,12,14,239,29,70,11,140,233,226,102,58,26,139,58,235,49,169,29,95,253,246,35,190,249,240,87,12,204,128,31,255,39,127,194,229,119,174,225,186,156,
243,179,249,1,129,254,103,177,177,232,163,64,204,9,199,9,61,143,214,146,225,225,46,251,219,59,84,85,159,160,12,105,154,160,85,68,69,74,73,132,143,172,68,91,67,154,231,140,135,35,22,179,17,7,187,123,44,
157,62,131,150,130,225,112,132,52,9,105,98,159,103,238,231,179,25,110,225,120,237,205,171,204,71,11,14,15,246,24,157,28,208,180,142,162,55,192,183,129,186,118,148,85,133,18,2,239,61,222,53,132,14,165,
120,239,58,111,35,196,119,35,98,254,216,135,103,207,166,201,138,62,78,90,238,222,249,134,143,254,246,175,169,108,193,143,254,179,127,65,255,252,153,56,212,70,52,135,133,140,73,156,128,138,238,133,80,241,
112,137,128,214,113,189,218,238,119,11,17,176,69,206,225,214,83,246,182,183,168,150,87,176,73,30,245,224,214,69,205,159,22,215,54,145,149,117,178,102,112,45,227,225,62,59,235,155,244,86,79,147,101,57,
139,217,20,105,45,69,154,225,67,136,115,15,206,33,116,74,190,180,74,162,37,147,163,35,54,215,159,226,188,167,232,149,148,189,10,223,6,178,60,195,213,45,94,120,130,95,116,128,192,131,136,141,181,237,12,
225,248,174,127,215,204,149,73,176,89,31,163,37,191,252,187,255,135,227,141,109,46,95,189,206,133,43,47,99,82,139,82,207,134,2,159,177,165,136,138,149,52,104,107,64,197,97,68,239,92,199,102,92,108,194,
222,145,245,10,182,239,222,225,155,155,223,208,191,116,145,222,82,159,68,27,218,69,19,229,4,25,139,78,219,182,120,60,197,160,143,155,76,216,93,223,98,114,50,98,233,204,41,242,178,164,30,207,80,69,78,162,
77,52,238,59,125,220,230,57,189,65,15,217,56,54,119,226,124,77,211,54,164,131,126,148,55,211,148,60,203,98,113,107,91,132,247,120,25,253,192,40,161,136,206,3,33,34,123,173,9,46,70,163,179,188,34,235,45,
177,152,142,248,248,103,255,31,7,91,123,188,242,198,91,92,186,122,25,105,53,94,68,127,38,196,116,68,7,6,28,65,168,40,251,17,207,45,93,179,9,173,167,13,14,169,21,237,104,196,157,223,252,22,209,207,24,156,
94,33,209,6,87,187,200,130,164,36,132,150,166,105,240,64,210,43,104,230,11,198,187,123,156,236,239,161,10,75,82,69,191,45,132,56,200,168,186,230,43,4,168,196,208,95,93,66,183,146,195,157,35,14,246,54,
88,76,79,72,251,61,172,53,0,36,69,134,150,177,232,19,162,148,35,159,85,39,239,163,178,32,99,211,113,173,199,183,33,166,155,140,166,28,44,147,100,5,39,7,251,252,244,255,254,191,24,158,156,240,222,31,254,
152,83,103,79,225,136,222,97,211,6,212,191,249,55,127,241,65,81,229,28,31,12,113,237,156,121,189,64,42,25,227,89,66,226,92,160,40,243,231,211,180,109,219,70,35,195,181,8,17,105,186,107,61,66,42,130,240,
136,208,162,68,204,142,10,41,208,90,147,36,57,121,213,99,107,127,155,223,254,242,39,156,60,61,224,226,234,203,252,224,79,127,68,239,194,0,165,163,108,36,255,217,244,157,146,170,147,108,98,150,94,155,40,
87,248,0,73,150,178,179,177,137,95,52,120,20,54,77,163,217,37,163,121,17,59,163,39,136,78,199,70,82,47,102,28,31,29,2,130,178,44,57,25,141,241,94,146,23,85,55,17,170,80,34,210,241,106,208,35,4,193,225,
222,54,243,217,144,249,188,165,168,122,36,73,202,116,94,83,228,37,198,198,65,35,215,44,98,188,177,227,207,190,211,219,196,51,100,31,158,189,177,88,240,147,172,196,153,132,123,247,239,242,225,127,248,15,
12,100,193,31,254,217,191,224,244,149,11,208,249,0,218,232,78,122,16,72,17,101,42,221,69,209,32,160,181,120,62,168,18,229,19,79,86,102,60,189,119,151,198,57,178,188,196,123,65,154,229,145,97,72,141,214,
250,57,122,242,65,80,86,21,147,209,136,201,232,128,209,209,152,229,115,103,145,206,51,58,58,193,100,57,105,154,118,239,3,124,221,176,114,254,52,203,43,43,28,236,238,115,60,60,98,114,114,136,11,138,170,
215,199,251,152,161,174,122,37,4,104,155,120,45,133,144,16,218,88,104,156,139,72,46,184,128,20,10,223,205,56,104,173,73,139,37,30,60,124,192,199,127,251,119,220,120,245,42,87,223,122,147,234,244,10,82,
42,172,18,207,141,83,213,25,243,17,2,10,140,54,100,89,17,135,101,240,208,253,30,213,197,34,149,214,148,101,206,250,221,91,236,31,236,147,86,61,76,146,145,21,5,161,109,162,241,24,7,9,58,137,76,145,22,5,
179,241,152,209,193,14,39,155,251,244,206,156,33,43,11,166,39,99,68,146,82,22,69,44,62,64,179,104,104,90,199,224,244,42,169,148,236,110,110,114,176,187,193,104,52,165,127,230,12,70,199,225,189,52,73,34,
37,119,117,52,246,130,0,31,93,213,214,53,241,29,66,148,70,58,153,75,106,139,205,50,62,249,249,63,224,198,19,94,188,250,42,43,231,78,147,36,241,60,4,4,193,197,235,14,148,50,49,68,160,98,150,60,74,92,49,
236,16,205,64,223,185,234,157,207,34,193,230,150,181,47,190,226,219,91,183,49,43,43,84,203,75,244,242,146,102,190,32,116,205,195,55,17,237,235,196,82,20,37,245,201,136,205,141,117,240,45,253,213,21,108,
150,83,79,167,36,85,159,68,41,124,39,147,138,0,182,200,169,122,37,237,201,136,225,201,152,253,157,13,234,182,33,173,42,140,214,36,121,142,53,9,174,109,113,77,131,11,13,33,56,92,235,58,139,44,134,7,148,
20,180,181,163,110,34,75,77,123,125,140,49,252,250,239,255,150,197,108,193,181,55,223,98,176,210,143,198,175,80,191,139,231,118,200,28,126,103,12,75,165,163,146,214,73,150,173,247,29,64,113,56,17,72,178,
132,225,218,58,183,62,250,4,159,27,202,149,229,152,166,19,18,23,28,62,4,124,232,66,17,128,46,115,154,89,195,225,198,58,245,228,132,164,202,200,122,125,148,135,160,21,105,158,17,90,31,215,80,107,164,209,
84,43,61,220,204,113,184,123,192,241,225,14,117,61,35,237,71,41,80,105,67,86,149,145,53,45,218,14,188,8,92,219,196,132,151,148,4,223,226,187,43,75,188,143,5,223,216,148,178,191,194,228,232,152,95,255,
205,223,81,244,74,174,189,115,131,162,200,241,174,198,57,143,16,26,169,19,212,95,252,79,127,241,65,154,26,202,126,143,195,131,33,161,158,177,152,76,113,62,144,36,22,33,20,243,73,67,94,85,8,37,163,137,
64,96,209,180,221,245,3,224,208,52,94,32,131,68,107,137,243,162,211,18,21,89,150,147,21,125,142,22,35,62,249,217,63,178,241,245,19,94,185,116,157,239,255,217,143,72,87,138,72,143,125,139,145,10,169,37,
190,141,25,123,173,12,73,146,117,250,96,52,116,66,151,67,87,2,170,170,228,230,167,191,37,207,82,156,23,8,147,196,198,65,212,18,17,162,219,176,142,44,79,35,146,107,23,236,110,236,224,145,148,85,143,233,
120,194,108,222,144,165,9,214,118,69,209,59,36,176,180,50,64,4,207,246,198,46,139,217,144,249,100,138,77,82,108,146,83,183,158,44,207,49,90,131,119,17,17,5,8,62,106,160,49,204,26,59,113,219,250,110,191,
73,180,209,100,229,18,119,239,222,229,163,191,250,107,190,243,202,107,252,248,95,254,9,249,233,62,139,186,197,249,56,221,172,141,238,52,116,8,33,26,78,202,164,232,52,239,38,100,159,199,98,186,104,92,32,
4,200,139,130,135,183,191,101,56,58,1,19,181,126,155,20,157,177,163,16,50,26,61,74,10,178,194,162,132,96,58,155,114,188,187,205,112,231,144,149,11,231,72,140,101,56,28,227,181,165,42,114,172,181,84,131,
138,208,130,74,18,78,159,61,135,155,205,57,56,56,164,158,30,51,155,207,41,139,18,23,2,173,23,100,121,204,86,123,87,3,129,166,105,144,170,67,254,109,23,231,19,18,209,73,6,90,91,118,246,15,185,255,155,79,
120,227,250,107,92,188,126,133,124,169,138,239,81,211,173,101,156,224,85,93,218,130,238,254,21,147,88,146,60,71,27,251,59,237,190,89,116,77,62,154,187,198,104,138,34,231,96,253,1,235,143,238,17,76,134,
148,134,170,31,211,42,129,152,113,14,221,85,19,66,107,170,170,96,62,26,113,184,179,193,201,230,14,73,175,71,82,228,204,70,99,188,50,244,202,18,223,198,236,244,124,50,193,17,88,57,119,134,210,40,142,119,
15,216,222,218,96,103,127,143,180,223,39,77,44,66,105,242,44,167,109,28,174,174,159,223,191,34,69,160,113,30,25,66,103,242,6,16,138,214,57,64,242,228,238,93,84,240,44,157,59,141,78,51,178,44,141,235,17,
165,93,148,54,177,122,63,143,124,10,124,235,227,85,22,82,118,250,117,76,164,196,160,80,76,147,137,110,74,60,51,134,71,159,127,205,131,91,119,49,253,138,211,103,207,82,244,122,136,38,222,141,164,180,98,
62,157,33,132,32,47,51,202,42,231,100,119,159,245,71,107,132,102,74,111,121,153,164,172,88,76,166,168,44,35,51,54,154,155,50,54,151,164,40,88,62,179,138,88,180,28,239,239,179,189,254,132,195,131,3,150,
47,92,36,81,26,157,102,24,165,105,93,139,171,231,17,221,251,40,131,62,19,118,4,113,80,171,246,196,89,1,33,185,251,217,111,201,178,132,243,175,188,132,205,82,144,49,184,33,58,253,60,132,208,165,101,158,
213,123,31,77,108,29,175,254,16,74,196,34,239,98,177,15,193,71,255,71,107,242,165,62,91,55,239,177,177,246,132,209,108,76,190,178,196,96,117,5,67,140,215,70,143,48,74,60,42,77,41,122,5,39,187,199,28,60,
221,102,54,25,162,203,4,149,167,72,161,105,67,160,44,11,140,142,115,38,120,135,206,13,43,103,86,73,68,194,193,198,1,71,251,155,28,239,239,144,244,250,216,196,98,108,70,150,101,40,4,117,187,192,185,54,
26,201,66,224,235,5,77,219,196,107,57,156,71,232,103,51,22,154,102,54,231,203,15,63,102,233,236,18,23,95,190,128,50,42,54,251,8,103,145,214,160,164,64,253,219,255,227,47,63,16,33,198,193,138,178,224,112,
255,16,21,90,102,243,49,109,227,227,253,50,89,9,66,144,102,25,49,215,16,41,17,193,209,182,109,87,112,66,167,231,68,140,18,13,113,69,158,21,144,167,124,246,155,15,217,186,185,198,107,175,190,205,245,247,
111,144,245,77,215,165,4,70,197,98,31,15,95,52,143,148,78,72,210,60,202,33,132,248,98,124,247,248,178,27,104,177,146,135,119,238,82,244,10,218,22,148,138,131,59,162,211,47,227,53,2,93,142,214,38,204,102,
83,132,104,217,92,123,66,89,85,164,69,198,124,81,67,19,168,122,125,164,214,104,29,157,121,163,21,131,229,37,154,198,179,189,190,69,8,11,198,39,19,242,126,15,33,21,117,237,40,202,10,33,5,77,61,143,23,207,
181,93,12,177,109,227,209,242,174,163,234,161,51,141,52,227,197,130,91,31,126,204,149,139,47,114,237,123,111,160,83,19,17,172,8,36,90,162,205,179,59,111,84,151,120,161,203,131,39,113,160,72,235,110,52,
62,162,148,168,139,119,211,160,69,137,82,154,221,205,53,14,246,246,72,138,30,90,74,178,170,234,46,192,235,238,253,16,2,231,106,178,52,165,109,2,147,201,144,225,222,54,245,188,165,183,220,71,27,195,209,
193,144,164,40,201,178,244,119,197,212,57,148,53,156,57,123,134,241,241,148,195,195,61,102,147,67,230,117,67,86,245,105,235,22,163,109,68,54,190,166,233,38,85,165,136,9,163,216,176,35,51,241,62,222,203,
83,215,45,163,189,61,206,93,60,67,186,84,197,187,140,68,136,108,36,56,78,14,71,209,80,55,154,214,71,35,89,240,76,243,78,73,146,2,163,101,76,225,68,115,37,14,200,169,104,182,5,2,58,77,9,109,203,116,120,
192,100,50,38,41,42,164,52,20,189,62,70,235,78,146,211,177,33,226,227,64,151,84,140,78,70,28,30,109,49,217,59,164,127,230,44,54,75,153,142,38,200,52,163,40,50,226,93,100,241,46,35,173,12,229,82,73,174,
53,211,227,99,118,182,182,216,219,219,227,212,197,11,232,214,35,77,138,86,42,234,179,190,237,114,250,221,101,89,193,197,196,76,183,54,193,199,225,64,169,4,249,160,34,4,135,54,186,75,241,208,105,230,207,
174,21,145,93,65,143,235,169,117,74,53,88,197,40,211,69,66,121,62,192,35,0,215,13,84,10,33,201,170,18,55,159,179,179,177,201,193,225,1,131,11,231,209,70,211,27,44,161,124,68,219,214,38,113,166,131,6,221,
69,82,15,118,118,216,63,60,32,209,2,155,103,216,44,163,158,215,216,162,192,168,168,233,123,64,120,143,73,52,131,229,37,212,34,112,176,187,195,238,214,54,147,217,148,234,212,41,18,173,209,89,18,103,1,154,
154,224,28,205,115,192,36,59,157,189,43,216,93,145,157,141,166,88,107,41,123,5,222,251,110,77,227,123,11,221,253,64,81,232,142,103,199,7,31,135,206,132,160,200,203,184,23,59,221,89,117,204,39,54,132,136,
248,181,81,24,165,217,248,242,46,7,235,143,73,150,250,228,75,75,164,121,148,174,188,235,46,124,11,17,100,217,52,69,39,134,147,195,120,145,94,237,39,232,196,146,84,3,92,235,240,29,210,127,22,16,9,206,33,
173,162,183,220,67,122,193,201,193,9,163,131,61,22,211,33,42,79,72,138,60,230,233,147,148,176,88,224,219,154,32,99,35,108,93,27,27,106,55,63,16,124,192,139,64,61,171,217,91,223,166,28,244,40,151,42,130,
119,180,141,163,11,46,19,132,136,10,134,148,168,255,249,127,255,203,15,148,82,132,182,38,73,18,250,75,125,134,195,19,218,102,194,248,100,68,83,55,36,101,65,211,198,41,211,60,79,241,193,227,155,57,206,
69,205,90,132,14,129,139,40,97,8,45,104,219,22,129,196,100,25,79,214,215,217,254,226,17,215,223,126,139,139,175,191,64,86,101,128,235,226,141,93,33,224,119,52,78,10,65,211,66,98,35,194,140,211,163,190,
163,122,209,27,16,2,146,170,98,58,25,177,185,190,70,93,135,104,204,40,77,150,229,221,200,120,28,114,106,187,49,247,172,232,49,60,58,38,132,154,237,7,79,201,203,138,178,87,48,94,204,241,40,138,170,143,
150,113,42,50,222,58,41,89,89,93,65,75,205,214,214,38,245,98,204,201,241,144,60,171,208,214,50,157,45,232,245,123,184,214,49,155,140,73,19,25,59,114,119,55,13,221,112,13,221,189,50,173,247,108,61,122,
202,11,47,156,167,56,181,76,89,149,8,25,13,96,66,192,36,166,147,25,58,68,22,68,103,70,199,251,111,138,178,23,39,244,68,252,247,16,162,6,26,132,64,11,208,73,148,1,124,211,176,152,28,114,50,28,145,100,21,
109,32,222,59,146,88,164,138,177,177,102,81,243,255,51,245,94,189,146,101,105,122,222,179,214,246,54,220,49,153,217,229,134,61,67,130,0,5,8,250,9,130,116,69,128,186,17,69,145,4,13,68,65,188,16,32,137,
87,186,173,63,38,80,0,169,193,144,211,195,153,238,174,54,213,93,38,51,207,201,227,93,196,9,183,247,114,186,248,86,68,205,85,21,18,153,199,68,236,88,235,51,239,251,188,198,4,218,174,199,27,199,96,55,60,
126,248,200,126,179,229,228,179,119,36,74,243,242,180,162,108,58,170,178,144,170,221,59,217,3,148,57,111,62,251,28,183,30,121,125,121,97,187,122,100,183,222,50,127,247,51,188,115,148,77,43,203,123,59,
226,172,33,209,10,99,71,129,113,197,93,162,179,46,86,156,154,178,174,72,115,185,204,162,144,133,96,5,64,86,85,149,104,177,227,161,165,149,212,125,16,120,121,217,64,81,83,119,221,177,216,200,50,89,170,
10,55,137,104,64,131,178,233,8,70,150,213,155,205,134,180,110,241,206,145,148,53,105,154,224,140,145,81,90,170,177,46,144,87,53,121,150,113,119,255,200,221,195,45,246,117,75,51,155,82,86,37,175,203,87,
178,170,165,174,43,249,101,178,130,16,32,77,161,91,204,56,59,89,96,86,207,60,221,221,113,117,249,137,254,244,132,178,168,168,219,150,84,171,248,186,88,57,196,220,79,29,224,225,32,130,128,11,10,18,69,26,
71,131,73,146,29,189,3,42,168,8,52,19,183,46,145,188,233,117,66,72,82,150,207,75,178,182,99,218,246,242,49,195,197,215,33,74,252,226,142,84,233,132,254,100,202,238,233,137,15,63,188,231,121,245,204,244,
252,13,214,88,250,249,140,82,11,101,85,31,96,107,137,166,238,90,138,52,227,238,227,53,151,55,159,200,20,52,179,25,69,81,50,108,7,138,190,35,139,32,198,224,197,192,84,52,21,243,179,5,37,9,187,231,21,143,
183,215,60,222,222,208,189,123,3,30,186,182,39,9,135,103,196,68,131,156,23,177,129,74,240,54,8,158,34,170,223,210,44,145,66,71,71,137,39,10,157,10,26,38,83,105,52,47,33,175,145,214,56,47,11,78,107,60,
211,217,12,237,64,190,164,146,202,217,89,41,38,189,135,160,41,166,45,97,239,184,254,205,15,220,221,95,147,205,122,234,166,35,43,5,233,32,135,174,64,7,53,129,162,173,201,138,148,167,219,71,46,175,174,176,
195,134,162,171,33,175,112,163,33,75,51,242,162,140,163,60,249,189,178,42,103,241,246,140,38,43,89,191,108,88,221,223,241,114,119,77,218,70,252,73,211,146,105,141,217,237,24,15,94,168,232,59,33,142,170,
204,104,229,140,113,46,142,246,18,92,48,120,111,69,230,169,210,56,102,19,118,147,115,144,252,31,255,238,255,254,90,37,162,211,197,58,242,60,163,233,58,214,171,29,175,171,37,251,253,128,29,44,253,228,4,
99,173,44,97,243,20,59,14,132,168,112,112,78,126,23,153,157,11,119,35,143,231,212,118,48,108,238,158,249,249,223,255,83,170,89,77,170,17,32,155,10,184,195,242,46,170,106,136,173,173,82,26,157,230,212,
145,135,163,149,24,81,172,151,131,95,43,31,219,250,148,170,105,217,173,215,4,179,198,7,21,53,206,138,162,174,227,60,95,76,57,33,56,188,245,100,121,206,118,189,197,185,45,183,151,215,212,125,79,94,21,236,
54,59,172,9,84,109,67,154,29,42,82,3,74,49,153,79,208,58,229,250,227,13,33,236,120,93,190,48,59,125,75,154,100,24,227,233,39,45,222,74,107,232,149,140,42,156,147,215,212,227,133,84,137,60,88,101,85,163,
139,34,162,4,4,122,166,188,137,76,141,184,160,84,154,128,0,193,20,82,165,60,60,44,73,203,134,162,170,163,86,250,224,131,56,60,68,150,195,186,160,172,42,156,53,184,113,203,24,247,43,102,180,100,121,78,
158,229,81,46,166,112,78,70,11,147,174,193,141,142,209,109,185,249,112,129,29,28,179,179,9,90,41,214,155,129,162,18,201,166,252,44,150,113,28,113,14,206,222,157,51,239,123,30,239,30,216,174,95,88,45,159,
41,39,167,36,104,129,76,249,128,181,99,92,198,153,168,76,209,88,235,35,31,4,156,183,50,158,73,147,200,0,210,241,195,46,151,53,81,206,152,70,20,246,129,98,168,0,111,246,124,248,227,15,168,162,162,237,103,
36,113,65,167,116,116,61,198,118,61,120,71,80,154,172,174,24,119,27,246,171,123,182,38,80,183,61,251,237,158,36,43,168,235,26,239,172,232,193,163,92,47,175,107,138,36,99,249,188,228,105,249,200,250,121,
197,233,217,2,165,60,15,119,79,180,179,5,117,158,225,141,5,229,177,102,15,74,145,53,13,139,147,25,133,119,188,60,222,113,115,117,13,117,203,116,54,163,110,26,116,112,108,86,75,41,144,156,84,247,50,175,
62,120,57,162,125,44,66,1,245,161,43,10,130,190,150,181,84,10,177,48,65,41,172,13,71,115,145,217,173,249,240,205,239,168,222,188,101,49,159,225,7,19,213,40,209,233,123,64,17,71,251,126,221,148,108,30,
158,185,186,248,132,245,142,233,98,142,247,158,170,111,73,84,130,51,50,166,57,140,75,202,182,162,208,154,251,79,55,220,60,47,169,51,77,81,229,36,69,205,110,187,167,232,38,164,241,235,91,51,226,81,36,121,
74,59,159,48,157,244,12,203,13,79,119,55,92,223,220,208,158,157,209,79,231,20,89,134,119,14,107,71,124,60,180,164,30,244,184,32,110,123,25,167,128,242,22,231,227,51,131,168,228,64,254,142,80,99,69,103,
47,122,122,153,119,185,97,207,242,246,142,167,151,21,139,159,189,33,33,21,152,155,82,36,4,240,96,99,161,166,149,166,93,204,112,203,45,15,31,47,89,222,223,208,252,236,45,9,154,164,44,40,203,130,136,21,
142,197,92,160,232,58,202,180,224,225,234,158,187,187,7,2,3,237,100,66,81,214,130,56,73,115,25,25,43,77,176,178,48,78,146,132,126,49,101,50,155,176,121,88,179,124,122,225,229,225,19,62,213,100,109,77,
223,79,113,198,97,141,145,29,205,1,208,135,92,128,137,82,71,241,140,210,50,174,179,54,238,23,138,66,186,28,188,140,226,181,70,37,138,228,95,255,111,255,215,215,89,89,196,47,6,206,24,138,162,164,159,244,
172,95,7,182,235,53,187,237,11,69,86,115,122,118,198,234,117,67,81,84,8,238,193,160,148,199,216,104,204,210,113,25,135,104,245,29,9,65,105,218,190,37,43,52,69,150,144,231,128,151,197,140,243,10,107,71,
65,182,42,153,141,9,24,44,195,248,72,8,108,90,178,52,33,205,4,73,42,222,151,40,253,179,14,157,21,20,69,206,106,245,192,118,179,34,73,114,148,74,25,173,37,175,74,178,36,37,120,143,78,18,188,21,116,64,85,
148,172,215,107,124,216,114,243,227,39,186,94,70,9,219,205,14,107,61,253,108,18,185,69,30,51,142,104,157,176,88,76,56,63,63,229,246,211,29,187,253,138,213,227,19,139,55,111,100,177,88,212,228,69,206,126,
183,21,14,135,15,88,39,99,174,60,75,176,94,244,240,214,30,30,222,156,144,166,104,188,48,86,226,214,61,137,140,19,45,30,50,145,185,233,56,165,15,154,223,254,242,215,228,85,75,90,8,0,77,193,17,200,53,238,
183,152,253,142,84,107,116,146,163,18,197,118,189,98,249,244,32,59,17,173,216,237,70,124,236,128,18,141,184,151,85,64,103,138,201,124,206,126,63,240,186,89,115,255,241,71,156,85,156,124,246,22,51,24,214,
251,129,166,155,144,103,2,91,115,102,196,153,129,52,75,232,79,102,116,117,197,230,121,195,245,213,5,183,215,183,76,206,206,153,118,83,170,166,192,13,123,204,56,198,249,103,156,245,69,76,133,210,26,231,
45,105,146,224,130,44,206,133,3,164,80,222,196,139,51,42,104,178,84,222,251,67,199,3,232,84,17,236,142,223,255,151,95,49,61,63,39,207,74,178,60,149,78,64,139,108,88,33,139,92,231,156,24,118,242,146,113,
187,230,249,238,6,210,130,102,58,193,140,6,157,21,52,93,131,55,134,160,19,146,56,30,152,156,206,233,170,130,203,139,11,30,238,110,177,203,13,205,201,140,76,39,236,246,134,102,182,16,67,158,53,120,187,
143,222,12,72,203,138,197,187,55,36,163,231,233,238,150,203,15,151,76,206,207,153,206,166,52,85,142,217,109,25,141,59,138,32,164,144,81,17,187,224,162,161,207,253,173,81,169,116,68,226,65,18,149,79,18,
111,1,31,199,123,73,42,246,123,165,53,89,98,249,235,255,240,231,52,111,222,113,122,118,74,26,2,227,126,136,244,203,136,82,176,22,173,53,69,219,80,148,5,215,31,46,184,190,184,160,110,106,218,190,99,191,
27,41,154,74,112,35,251,29,36,242,61,117,170,169,39,45,169,115,220,95,93,113,117,123,77,161,2,85,219,162,211,148,221,110,199,228,100,129,50,70,170,124,103,32,4,146,76,211,45,22,76,38,61,102,179,231,254,
242,19,247,79,247,244,103,231,156,157,156,145,40,197,176,219,69,67,88,136,255,214,199,209,132,92,230,54,184,216,53,139,121,50,196,209,138,142,221,176,32,55,244,17,117,34,174,106,117,244,11,124,248,229,
55,60,239,54,188,251,211,191,67,158,100,88,227,113,209,93,172,99,247,131,138,23,212,180,229,245,246,137,231,143,151,140,118,79,185,152,70,185,108,70,93,213,113,113,162,227,200,53,163,158,54,164,65,177,
188,121,230,246,225,150,113,255,42,94,134,178,194,25,75,222,212,34,189,140,251,31,188,67,101,98,230,154,159,156,18,118,142,135,203,27,30,238,174,8,169,102,246,246,103,116,109,143,217,238,48,187,141,120,
54,84,32,120,121,15,125,112,209,109,31,9,185,30,84,240,228,105,70,240,90,212,106,145,135,150,102,5,73,128,228,31,253,143,255,226,235,178,172,41,10,97,185,19,109,193,16,152,205,103,168,68,243,250,178,98,
253,250,64,153,149,244,167,51,246,219,145,166,239,8,222,226,204,8,74,42,41,27,31,62,148,0,188,116,158,163,113,36,88,169,70,163,172,50,32,70,28,21,111,38,173,165,149,78,19,162,148,79,144,186,23,239,223,
147,101,53,42,203,201,242,76,90,219,84,31,151,114,198,200,225,90,150,5,163,181,172,31,159,176,195,142,164,200,177,14,204,104,169,171,134,52,46,44,178,36,26,118,178,140,182,175,89,175,55,12,219,23,30,222,
223,80,245,29,69,93,50,236,71,32,163,169,155,232,2,183,120,51,144,166,25,109,223,113,250,230,140,241,117,224,225,225,134,139,247,239,169,39,51,38,211,51,242,170,192,121,135,183,6,148,147,16,16,21,228,
228,14,225,104,183,150,23,217,83,36,224,189,21,35,82,52,155,36,73,122,84,162,248,160,34,64,80,49,26,139,6,82,12,191,249,229,175,152,205,79,9,36,20,85,33,142,213,68,36,103,74,39,81,134,22,104,186,6,235,
2,251,221,11,143,183,119,20,121,78,153,103,236,214,59,108,208,130,82,141,85,145,119,158,52,77,153,45,230,248,209,240,244,250,200,243,221,21,187,151,145,118,62,5,15,219,245,158,166,239,163,201,77,20,39,
214,74,64,76,209,54,124,241,39,159,131,113,220,93,95,241,250,242,204,231,63,255,57,121,29,217,50,102,135,15,78,180,239,65,100,115,62,136,57,75,84,53,114,153,31,37,181,42,28,101,178,69,81,138,49,37,203,
48,102,20,41,170,119,248,96,177,214,80,84,13,118,247,202,183,191,252,27,9,126,200,27,178,170,138,243,110,31,231,207,224,130,141,172,253,148,170,174,88,63,223,112,243,241,71,52,57,117,221,48,12,123,193,
242,214,45,42,114,118,52,30,116,70,59,159,81,101,9,171,167,39,238,111,175,48,171,13,147,211,83,210,44,97,181,220,48,59,61,139,206,74,57,148,116,84,108,233,36,163,61,153,51,171,59,94,110,110,248,248,225,
35,229,164,101,54,159,81,213,21,155,205,70,92,147,42,142,37,162,251,248,144,109,16,66,56,86,172,50,215,142,156,171,232,219,74,147,52,202,60,101,190,45,85,24,96,45,58,207,48,235,39,254,250,207,255,63,170,
179,183,156,158,157,208,181,29,102,63,224,240,71,221,188,139,8,140,180,174,105,180,230,233,230,158,171,139,75,154,182,164,237,27,134,193,18,178,140,190,237,8,214,66,154,200,1,156,36,52,147,142,90,167,
124,186,184,226,250,254,150,204,237,41,186,150,52,203,33,164,34,231,52,70,148,37,214,69,41,49,20,125,199,226,205,57,121,146,241,242,233,154,251,135,7,102,95,125,206,124,190,0,99,24,246,59,28,177,106,13,
160,18,25,211,200,206,3,112,178,203,145,176,20,135,82,145,239,69,196,166,104,145,222,58,239,56,202,114,162,131,53,203,18,126,248,79,127,197,203,126,203,236,243,119,180,77,67,230,164,224,66,171,232,153,
16,37,76,86,85,100,101,202,235,167,7,30,47,63,0,150,238,236,12,103,69,130,90,183,45,137,83,120,173,143,159,165,118,54,161,44,115,30,62,92,241,244,240,40,135,126,89,81,212,29,206,123,249,76,56,112,206,
200,217,25,228,82,47,155,154,249,219,115,210,144,242,122,183,98,249,240,68,117,50,163,63,59,165,8,96,205,24,159,225,104,104,12,242,218,164,137,204,243,19,157,197,113,167,4,46,120,31,49,22,136,52,52,203,
115,121,125,254,135,127,252,79,190,246,65,81,149,117,4,20,69,165,131,52,69,116,253,132,172,168,184,191,185,230,250,242,130,60,47,105,186,41,121,86,145,166,9,118,220,161,16,157,170,117,50,83,34,64,150,
28,164,99,22,240,224,57,74,38,71,99,165,117,245,209,82,29,13,53,26,77,162,197,14,237,67,96,52,35,223,255,230,91,230,139,83,70,43,51,106,47,224,105,153,205,89,139,117,86,220,172,85,205,122,243,138,25,95,
89,46,87,180,93,135,15,48,14,35,85,219,9,154,32,68,132,113,8,164,69,78,213,244,172,150,75,140,217,114,127,113,75,63,159,147,22,57,242,217,201,104,155,10,111,69,30,165,98,229,149,231,25,243,197,156,224,
21,119,55,55,220,95,95,241,39,127,242,115,186,201,140,52,75,24,119,91,188,149,138,214,31,180,232,78,102,223,254,0,72,82,46,186,78,99,150,141,119,178,52,140,225,31,105,150,16,156,59,222,218,105,172,172,
138,42,103,189,124,225,226,253,7,102,39,167,12,70,102,205,10,209,231,38,42,145,75,39,190,217,69,89,177,223,142,108,94,159,184,187,186,101,190,152,147,231,37,227,126,36,201,82,234,182,147,132,159,168,162,
73,51,205,226,236,148,205,114,199,114,249,194,203,237,53,102,63,242,217,207,255,148,16,20,219,209,50,155,205,72,181,88,65,84,112,4,39,174,12,149,106,22,231,11,166,109,195,167,31,126,228,254,105,201,217,
231,159,83,85,53,118,220,225,204,16,17,214,135,78,216,199,29,135,138,132,86,233,54,198,189,57,176,163,226,56,76,83,150,21,74,167,242,79,130,149,16,142,227,135,89,211,116,45,47,183,87,220,94,95,208,207,
223,48,6,69,211,79,226,76,214,31,37,179,248,64,240,22,85,228,4,227,216,173,95,120,248,120,65,89,247,52,125,199,176,217,224,67,160,155,78,8,241,0,240,214,98,189,19,109,125,85,242,112,119,203,227,243,19,
251,229,146,106,50,161,104,74,130,206,153,76,166,66,133,12,2,104,3,135,10,130,37,169,38,45,139,147,19,150,159,174,249,240,199,247,76,63,123,199,164,107,25,141,57,162,32,100,36,33,169,101,242,185,113,28,
135,250,202,31,53,43,222,123,140,117,82,36,37,25,94,37,104,149,30,0,48,145,123,159,198,124,138,140,151,203,75,190,249,203,95,82,189,125,67,183,152,209,182,29,97,140,207,180,142,21,96,4,155,157,190,123,
75,230,61,31,126,252,145,215,213,146,201,108,74,221,245,152,193,146,215,37,93,219,49,238,246,241,98,9,232,44,165,238,107,180,247,220,93,223,115,247,244,76,134,140,69,73,19,72,115,250,182,197,154,145,189,
29,226,24,86,150,169,89,149,51,61,61,161,206,51,30,223,95,242,184,124,225,244,171,47,105,243,174,73,35,74,0,0,32,0,73,68,65,84,156,221,118,35,224,191,52,35,137,148,77,21,199,59,168,228,136,13,241,113,
223,167,136,242,103,60,74,167,36,153,236,156,130,181,113,172,23,33,104,74,196,41,56,203,111,254,159,255,200,114,216,176,248,234,11,38,147,142,28,141,177,38,238,18,131,28,176,78,246,15,105,154,240,240,
227,37,219,213,11,221,219,83,202,166,197,134,64,154,229,66,252,180,62,86,250,114,33,87,211,150,52,192,234,238,137,251,167,7,178,92,147,151,5,73,33,211,135,166,107,196,195,99,204,81,240,226,188,71,103,
41,147,243,25,117,85,241,122,179,228,101,249,68,53,237,152,159,157,18,140,103,220,239,176,33,200,136,38,6,198,200,43,10,58,21,21,144,188,190,65,126,151,88,44,104,165,80,89,142,10,154,228,31,254,195,127,
244,117,240,138,16,148,88,208,19,193,40,152,253,14,111,69,137,147,87,181,140,120,86,43,62,124,251,3,101,94,240,246,139,47,40,155,6,227,197,156,19,140,124,51,81,199,68,2,159,119,34,61,51,38,194,207,148,
140,128,140,199,89,142,225,29,178,128,116,184,96,34,65,239,176,131,83,172,95,215,92,124,247,61,139,179,51,54,123,71,158,21,63,177,73,178,148,36,154,108,18,173,104,251,9,15,247,15,236,214,43,94,30,94,232,
250,22,99,70,118,187,129,52,175,100,249,168,2,58,114,105,170,50,163,106,59,150,171,87,140,93,243,233,187,15,228,85,77,85,213,140,46,144,22,21,117,35,243,112,188,19,18,158,151,173,127,51,233,56,89,156,
240,242,248,204,247,191,255,61,103,239,222,209,207,230,40,20,187,157,60,176,10,73,178,33,8,226,89,161,100,132,19,57,24,145,163,21,113,12,10,149,104,170,162,34,205,10,177,113,199,165,146,84,255,114,40,
246,179,57,143,183,55,220,94,92,48,57,57,97,59,88,210,162,34,79,51,185,80,146,3,164,205,226,131,102,177,152,179,94,174,24,135,53,215,127,188,160,157,47,40,170,146,237,102,96,111,29,211,201,156,52,74,95,
205,40,21,196,219,159,157,129,215,220,61,220,177,126,186,231,238,242,154,243,159,127,137,119,158,209,4,250,201,132,68,131,115,86,34,29,189,195,90,112,192,252,236,140,47,190,120,199,213,15,239,249,221,
223,252,158,47,254,222,159,81,215,21,195,102,25,207,221,64,150,201,238,67,22,240,50,139,12,222,73,113,160,20,105,122,144,19,122,146,36,143,104,91,233,2,157,151,248,77,229,101,28,230,163,135,162,110,42,
158,239,174,249,254,15,191,101,107,28,58,45,152,206,23,34,157,117,54,74,88,21,56,24,173,161,237,39,4,99,120,122,190,225,246,135,247,228,85,69,55,155,176,219,239,216,141,178,220,75,130,204,61,241,134,52,
205,168,167,51,78,230,51,94,238,238,184,127,188,227,241,211,29,69,83,146,22,37,46,104,166,243,25,110,28,197,131,128,194,249,65,98,54,85,138,46,43,222,124,241,142,34,4,126,255,171,223,210,158,191,101,210,
119,236,55,251,120,225,103,127,107,124,19,133,12,74,92,237,226,92,247,71,164,49,33,33,203,42,210,172,20,247,104,34,201,103,206,89,156,113,168,92,104,153,193,59,218,105,199,227,199,15,252,242,63,253,5,
54,205,41,154,138,201,201,130,82,103,152,97,136,207,151,194,153,17,85,230,52,211,22,191,89,115,117,249,137,245,203,19,139,249,156,114,210,178,223,13,132,52,99,50,153,225,6,35,214,105,103,209,105,202,228,
228,132,46,207,184,187,248,196,199,171,79,12,155,23,38,167,231,130,49,175,107,50,165,121,122,122,38,75,197,104,166,14,221,87,48,52,179,41,103,239,222,240,250,241,154,143,31,62,240,230,239,254,93,178,112,
144,175,198,9,160,78,68,29,19,199,115,105,196,99,16,17,212,114,86,136,99,57,141,248,103,89,102,139,73,244,192,9,82,241,191,121,83,99,86,43,126,247,31,254,130,31,127,120,79,255,197,59,38,39,51,170,180,
144,152,76,37,139,78,161,135,6,234,133,208,83,159,46,174,185,191,187,34,77,161,168,43,41,118,188,167,155,246,40,119,152,89,122,178,44,161,95,204,105,234,138,213,213,147,160,73,214,47,120,173,37,111,33,
207,41,203,6,101,61,206,26,140,183,56,103,177,136,87,165,158,247,44,222,188,99,125,243,196,237,135,15,76,190,120,75,221,180,140,155,13,36,68,148,134,128,44,125,240,209,81,31,167,35,33,96,6,131,11,145,
31,229,165,88,40,203,70,60,77,255,205,223,251,7,95,87,147,150,52,43,33,104,170,186,62,26,32,156,31,35,228,72,147,103,41,179,147,41,62,4,46,190,127,79,85,20,44,222,190,21,124,236,126,139,183,67,124,19,
101,126,102,173,48,57,178,36,182,142,46,136,228,209,71,153,70,112,17,219,154,145,230,5,135,93,4,33,224,188,28,114,105,26,232,167,83,110,175,46,217,191,190,50,157,47,36,172,164,233,136,46,99,84,146,226,
131,116,37,90,139,170,99,191,221,49,110,151,108,215,3,237,84,148,10,227,110,140,241,135,185,180,202,177,178,213,73,66,215,180,44,159,150,120,6,110,62,94,80,247,61,170,200,113,30,170,170,34,207,51,185,
241,141,137,135,183,195,89,67,94,54,204,223,188,101,243,244,194,31,190,249,29,111,190,248,92,150,200,155,13,163,25,226,67,38,93,147,210,154,52,83,71,70,134,78,83,212,129,198,23,91,245,36,73,41,170,26,
235,213,49,88,193,70,62,141,76,177,100,36,214,180,21,79,119,119,124,120,255,1,139,58,38,255,36,201,161,18,146,202,199,89,33,155,22,85,37,220,255,221,138,219,31,175,152,44,230,20,85,41,8,232,36,17,44,182,
246,210,30,90,131,210,48,157,207,241,38,240,178,126,97,183,126,228,250,195,13,39,231,231,145,90,32,135,175,55,99,172,160,227,7,42,154,66,178,60,227,244,237,57,218,24,62,254,241,61,179,211,83,148,31,142,
227,10,21,23,105,138,131,215,192,199,74,71,29,77,112,50,250,81,232,172,166,40,123,208,9,105,26,151,251,177,154,37,81,177,30,118,228,69,65,154,230,172,158,239,89,63,223,179,27,61,85,215,81,86,178,3,178,
198,70,28,131,84,249,73,42,46,93,179,217,243,252,114,207,243,197,13,117,55,161,234,42,118,175,27,44,25,147,233,4,37,149,137,28,186,64,59,109,232,219,14,179,27,216,236,150,124,250,225,130,118,177,160,170,
90,146,186,22,124,131,53,88,179,19,78,143,51,98,209,87,18,36,212,204,231,52,121,193,250,254,153,106,62,39,184,17,103,15,48,129,112,52,88,28,98,18,85,144,197,182,188,62,78,46,59,157,210,207,207,232,154,
238,24,178,18,14,84,206,131,147,247,56,239,79,40,202,148,231,235,27,174,47,62,97,211,36,74,146,27,10,157,139,187,54,142,120,204,48,146,100,242,186,216,205,142,171,155,91,252,184,161,173,43,242,186,101,
24,12,186,42,105,171,26,99,6,233,96,157,44,5,235,73,79,155,231,172,159,94,184,189,185,99,249,244,72,209,181,84,85,67,51,157,209,100,57,193,26,172,49,71,164,2,65,212,30,105,89,51,63,159,145,236,13,203,
229,138,162,111,16,56,123,84,19,197,229,164,82,62,30,218,81,146,124,208,107,5,79,34,115,38,154,118,70,166,179,35,9,83,50,10,164,203,38,238,70,130,18,220,193,250,250,158,187,239,126,96,185,94,146,47,78,
232,251,94,100,168,70,156,191,226,31,145,5,119,123,58,195,108,119,92,125,188,224,117,187,36,207,53,245,100,46,143,191,214,212,109,135,50,254,40,13,214,9,52,125,71,85,20,162,76,186,191,99,216,174,128,32,
153,180,85,71,149,102,24,59,96,198,65,138,29,47,153,219,193,65,82,119,116,243,14,53,26,150,79,207,148,243,9,218,27,49,215,41,41,26,143,133,193,1,244,102,61,222,70,117,83,244,46,41,16,12,123,209,73,231,
247,95,255,87,127,255,235,213,253,51,237,180,37,41,10,198,193,208,244,19,28,1,179,223,203,15,161,226,98,68,37,180,147,158,162,170,248,237,223,252,26,63,26,62,251,147,175,176,193,179,223,110,228,205,87,
68,87,101,26,33,69,81,26,23,137,155,46,222,138,49,90,128,44,19,51,147,74,114,146,68,20,28,34,1,21,190,189,214,138,186,169,184,122,255,81,12,41,121,46,243,202,36,37,203,211,24,175,151,162,130,100,109,38,
185,0,191,198,253,154,213,211,35,219,213,150,249,249,25,90,107,94,55,91,121,208,243,236,104,202,24,135,61,85,93,113,114,122,202,122,181,38,36,150,15,223,126,39,1,228,179,5,251,189,167,235,250,72,238,51,
24,35,110,73,99,198,184,120,134,147,183,11,138,60,225,219,191,254,13,205,116,66,150,167,12,187,157,68,44,38,42,26,140,126,34,56,24,27,19,134,136,20,60,125,112,208,86,148,213,132,16,34,57,241,48,148,243,
226,108,14,177,228,105,218,6,165,53,171,229,35,247,55,215,108,141,167,42,74,178,200,202,87,94,14,124,31,130,204,78,117,74,81,53,60,63,190,176,93,62,114,247,227,37,243,119,111,72,203,146,215,245,22,157,
228,180,109,35,188,146,52,193,12,123,116,146,48,61,89,208,228,21,155,205,154,245,235,3,87,31,111,56,255,242,75,8,2,167,171,202,18,239,44,198,236,177,206,225,157,229,245,101,21,77,63,48,59,159,211,84,57,
47,119,15,20,109,11,218,71,36,174,58,178,191,141,11,178,104,78,35,39,222,10,169,211,251,128,243,129,193,4,156,46,233,251,89,12,162,143,102,26,173,176,38,130,199,112,160,52,69,93,161,66,194,110,253,204,
230,249,153,164,16,121,110,86,86,228,69,129,181,163,252,251,16,211,186,210,130,166,235,24,246,91,94,150,15,188,92,222,80,180,29,221,188,103,183,25,176,73,70,219,117,4,107,64,249,40,25,116,100,85,203,244,
100,78,216,237,216,13,107,62,254,240,35,33,45,105,186,142,170,235,200,116,192,140,59,113,72,186,232,165,208,162,138,2,57,40,218,73,203,250,249,25,149,166,82,189,31,226,52,149,194,197,64,26,133,39,4,27,
63,212,178,192,116,198,17,130,98,245,178,68,87,34,164,8,113,249,171,180,38,77,50,81,184,88,19,9,174,158,180,204,40,20,172,30,239,216,172,150,84,147,41,85,89,145,148,149,0,13,119,123,188,150,207,164,181,
70,82,155,218,154,221,203,146,139,203,107,194,110,67,63,157,146,183,45,187,245,150,180,170,232,170,154,113,187,147,103,204,91,84,146,208,45,102,76,38,61,227,235,154,155,139,11,110,175,175,169,23,83,146,
162,102,50,155,225,198,1,107,246,152,253,62,226,197,163,135,192,203,161,223,157,44,72,131,23,191,71,38,123,55,229,35,224,76,135,24,191,202,79,132,79,21,225,116,206,70,121,107,192,39,41,211,179,55,164,
158,120,209,42,201,36,16,81,190,128,236,180,38,205,51,170,190,229,249,211,53,247,239,223,67,89,144,54,45,73,38,84,95,111,69,25,163,117,18,119,57,226,137,216,47,95,185,184,184,98,179,95,82,100,25,105,93,
33,199,180,204,244,157,117,34,91,183,6,157,38,180,243,41,221,164,103,123,255,202,253,245,21,207,143,183,178,47,153,76,41,187,150,224,192,142,34,211,61,140,98,189,228,135,146,102,41,221,233,156,92,43,134,
245,142,188,42,100,4,42,179,2,92,240,49,6,81,197,11,144,88,100,200,88,231,128,163,80,90,199,4,181,130,228,191,255,239,254,219,175,87,175,75,150,183,143,244,19,9,188,53,198,81,55,13,54,56,188,217,99,237,
200,24,55,222,222,5,146,170,102,126,54,227,227,15,31,216,188,108,56,121,123,202,102,187,21,157,175,74,68,106,120,224,161,43,9,12,246,94,16,12,193,27,153,221,6,5,33,165,40,91,242,136,255,149,4,169,184,
101,199,202,101,233,61,101,89,225,240,172,87,15,44,95,158,177,42,17,161,130,74,4,31,16,28,58,73,112,4,156,177,100,105,1,33,97,181,122,97,249,112,203,110,181,161,157,79,113,206,99,71,39,193,9,69,33,155,
124,39,85,64,221,86,52,125,199,118,99,24,134,29,119,23,151,52,117,67,183,56,197,90,79,221,138,188,106,183,219,224,236,128,117,22,235,130,84,112,65,160,100,147,89,199,195,245,61,89,145,69,165,77,70,154,
68,41,157,254,9,96,21,228,27,139,42,233,64,214,243,129,221,126,192,184,148,122,58,141,121,3,68,62,201,1,211,234,163,155,210,81,84,37,251,237,8,110,199,254,117,77,219,79,176,163,1,165,201,139,90,126,183,
232,107,48,198,147,87,21,121,90,178,89,63,243,186,121,226,233,227,29,221,124,70,94,104,204,232,112,42,17,54,62,135,247,73,198,32,139,179,5,179,217,130,215,213,134,205,235,19,151,31,63,208,204,79,209,89,
46,110,227,92,58,60,51,136,206,94,70,47,130,158,246,198,163,211,140,188,202,200,227,18,52,75,114,84,42,202,162,224,35,62,59,203,254,22,59,127,196,218,128,245,194,103,114,214,115,251,241,18,167,20,211,
147,51,185,100,173,193,90,185,232,157,177,210,45,132,128,245,130,129,118,163,5,55,176,124,126,32,45,106,156,21,9,92,81,212,16,97,102,73,162,177,198,18,180,162,109,106,118,219,45,247,143,247,188,222,61,
82,55,61,237,172,231,117,181,130,36,151,67,223,9,238,214,91,145,96,230,117,195,124,62,163,64,179,221,173,120,188,253,196,24,71,10,237,100,134,114,6,99,6,240,46,18,89,37,66,208,203,173,125,228,188,107,
45,89,17,10,121,95,93,228,223,136,97,38,196,189,67,192,89,119,228,17,133,160,240,193,113,245,199,63,224,243,134,55,95,124,134,50,30,227,157,152,253,14,241,233,65,172,247,193,137,235,213,155,145,231,199,
123,150,15,143,156,126,241,37,42,120,146,34,167,174,106,198,253,32,243,94,13,222,140,164,101,73,89,149,172,95,150,124,186,123,128,97,75,85,87,244,179,57,118,52,228,85,75,145,36,50,194,138,35,24,148,162,
232,90,250,147,5,236,247,188,46,31,249,240,253,15,132,170,98,122,126,78,93,86,56,51,74,60,104,150,131,115,177,63,11,36,89,14,222,147,149,57,69,158,30,181,230,7,137,110,20,133,114,72,12,17,106,164,228,
62,28,10,82,103,13,155,199,7,174,46,174,152,125,254,51,250,166,197,218,136,238,14,210,221,121,23,51,187,181,166,104,26,180,82,60,92,222,112,251,233,146,116,210,210,205,230,228,69,73,89,150,40,231,143,
249,16,110,28,229,34,236,91,204,122,199,245,229,13,131,217,146,36,154,178,237,68,154,158,164,84,101,113,92,24,251,136,96,40,186,154,233,201,156,113,181,103,249,240,204,227,245,21,59,107,105,78,22,52,77,
131,183,30,103,6,41,94,162,35,151,67,76,102,34,99,177,186,44,15,179,62,233,124,1,27,14,207,67,236,14,85,56,34,23,92,228,249,227,2,227,110,195,195,229,37,73,91,145,252,243,127,245,175,190,246,131,103,187,
123,101,245,184,226,243,175,190,100,8,48,236,45,109,223,50,14,123,198,113,64,5,123,172,112,188,149,27,189,157,52,108,215,107,134,205,136,46,83,130,49,4,157,66,150,202,76,80,197,52,250,200,215,0,79,114,
52,152,72,230,105,90,52,212,253,84,220,128,7,68,171,10,50,62,137,75,59,23,20,121,93,178,89,189,146,132,145,245,106,75,85,119,194,161,78,115,146,178,136,70,30,113,247,57,103,40,234,2,99,3,118,220,115,119,
113,137,217,14,76,223,158,96,173,193,155,64,211,79,143,178,68,162,83,81,39,9,85,221,130,11,12,195,158,143,63,254,72,93,183,116,179,25,1,69,85,213,152,97,195,56,236,177,46,196,37,44,241,255,69,93,211,207,
166,114,41,38,34,197,148,10,95,56,31,2,183,82,145,133,18,142,186,232,128,195,70,3,206,197,15,23,132,160,40,219,25,73,36,134,6,116,52,158,133,168,57,118,36,58,165,110,58,150,143,207,164,153,103,179,222,
210,182,21,131,181,98,102,170,26,57,108,226,104,104,187,31,201,138,130,170,174,101,78,189,126,230,254,251,11,22,63,123,75,72,115,54,175,59,193,96,148,101,164,160,90,81,28,37,208,205,122,230,139,5,219,
231,87,86,47,15,220,222,222,48,153,159,82,150,53,77,215,17,156,101,28,118,113,204,85,18,148,204,233,117,162,162,76,20,57,236,188,63,204,225,142,35,8,29,31,84,31,236,49,106,209,121,25,95,36,105,18,177,
27,138,223,253,151,191,166,63,61,39,175,58,210,164,64,121,119,252,90,222,137,75,210,121,121,29,179,178,100,183,222,176,125,125,102,253,186,161,159,207,177,195,0,105,70,213,180,82,237,41,57,72,188,117,
100,117,65,223,182,172,151,75,86,175,75,54,55,247,84,93,79,187,152,242,250,252,74,81,119,212,117,17,127,54,39,213,152,117,164,101,65,59,159,145,6,216,174,87,92,188,255,17,138,154,201,217,91,154,162,144,
140,228,253,94,176,182,8,214,22,37,23,184,210,9,89,154,201,107,162,142,131,28,233,142,213,79,99,11,49,101,37,113,180,227,142,248,101,165,18,210,196,243,251,95,252,130,164,155,240,179,47,62,23,39,232,96,
15,238,173,168,203,142,10,25,157,80,86,25,102,189,101,249,252,130,79,82,218,197,28,55,24,84,150,211,54,45,227,102,203,97,80,18,188,35,43,114,202,34,97,251,188,226,227,205,45,137,149,67,63,45,11,86,207,
75,170,217,130,66,107,70,107,24,199,61,65,5,236,104,168,154,150,233,76,66,131,150,247,15,220,93,125,66,55,13,103,239,190,32,5,156,29,81,58,21,184,91,84,167,229,49,189,41,196,81,141,100,1,232,35,252,237,
112,208,169,184,172,20,217,165,200,89,67,116,163,19,51,250,30,47,62,114,125,121,195,103,255,224,239,211,150,13,24,132,155,35,1,213,49,163,64,164,141,245,164,197,236,6,238,175,110,120,190,187,163,93,204,
153,159,189,65,227,201,219,26,111,12,62,68,169,116,112,228,85,73,211,84,12,207,43,110,110,111,241,218,81,104,37,180,85,32,201,11,242,52,147,56,200,224,227,62,39,144,55,37,211,249,148,36,36,188,220,220,
243,112,243,1,167,3,179,183,111,169,243,18,51,138,0,69,84,126,178,120,23,63,137,60,25,135,176,119,21,69,43,36,209,120,25,139,72,31,241,42,58,73,68,212,16,189,29,62,82,141,247,171,87,110,190,251,129,228,
95,252,203,127,254,117,51,155,226,188,103,28,95,249,244,225,138,175,254,244,43,188,133,162,172,81,105,138,27,247,216,209,130,87,140,214,198,185,153,124,227,178,173,209,41,152,97,47,97,22,90,197,10,81,
64,98,137,22,52,240,33,28,227,144,79,155,104,193,2,172,150,175,188,46,55,52,147,19,161,226,105,217,42,167,42,86,61,113,1,137,135,170,174,88,190,60,147,132,129,97,24,168,155,142,209,58,124,80,228,69,46,
154,107,37,12,27,31,179,35,181,214,216,48,112,247,225,130,97,51,80,79,123,188,21,167,93,81,214,49,121,41,224,189,193,140,123,116,154,48,59,59,165,202,50,182,175,207,92,94,124,32,120,69,222,78,169,170,
154,60,75,49,86,186,0,239,2,73,90,16,130,146,131,60,145,57,173,82,30,165,60,58,9,36,42,128,78,127,194,44,196,96,139,67,219,229,156,180,232,198,57,70,99,201,235,130,111,254,234,23,204,38,51,116,213,145,
164,121,108,239,5,43,60,26,31,21,47,65,98,1,179,140,213,114,133,49,107,214,235,45,85,211,98,246,35,163,67,144,10,28,253,33,236,119,59,186,105,71,215,79,88,173,159,88,175,238,184,254,253,5,147,179,83,138,
186,98,179,217,147,149,13,101,158,137,70,198,9,29,208,88,75,86,150,156,188,125,75,166,3,207,247,55,124,186,248,192,249,187,47,232,231,39,228,73,138,117,35,227,126,135,11,224,173,143,28,38,37,26,177,168,
224,114,78,200,158,120,41,30,124,124,70,188,243,132,160,73,19,97,243,123,79,204,158,21,153,102,82,8,218,248,63,253,251,127,79,51,153,49,157,157,72,106,80,136,75,204,24,124,98,205,32,170,163,52,163,169,
75,198,221,134,237,246,137,229,211,43,221,124,134,27,70,2,154,186,157,138,244,82,255,196,179,73,203,156,249,164,103,216,108,185,91,222,241,248,254,2,229,53,147,211,57,251,209,82,182,19,138,52,149,89,107,
112,199,36,56,227,160,238,107,38,109,207,234,238,145,15,223,253,72,209,118,156,189,125,71,170,20,214,14,248,96,241,94,19,220,54,130,246,196,238,158,101,25,214,4,217,247,104,21,17,188,254,136,202,215,58,
28,179,113,133,57,229,35,18,90,220,213,33,201,72,236,192,183,191,248,75,146,118,194,233,155,55,148,77,3,206,51,68,197,9,81,237,227,188,67,231,25,117,153,178,126,126,226,250,242,35,195,48,50,127,123,142,
51,6,175,100,233,28,6,139,59,140,146,84,160,106,58,38,211,158,213,221,3,31,175,110,24,95,159,72,85,66,209,247,120,23,104,78,23,184,245,38,126,230,29,73,42,57,16,69,85,209,77,58,170,60,103,247,252,194,
167,15,31,232,206,207,56,125,251,142,196,24,6,43,106,31,141,18,121,183,141,57,178,126,140,123,64,45,74,167,168,161,151,57,158,184,140,67,8,146,61,27,14,97,50,210,29,250,32,149,117,158,231,92,255,238,15,
188,255,225,61,237,187,51,102,139,19,146,16,4,223,32,174,44,156,29,1,41,92,155,105,135,125,221,115,123,113,201,203,227,29,147,159,189,37,81,9,227,94,194,235,51,146,35,181,211,59,71,209,214,76,231,29,187,
251,39,62,93,94,97,236,142,44,72,170,158,214,9,69,219,147,6,45,227,29,51,224,144,46,35,41,115,166,231,115,234,188,102,251,240,202,237,213,5,42,79,152,158,159,81,102,5,193,88,92,112,98,32,211,250,40,87,
70,137,160,67,214,163,71,146,22,58,34,89,8,94,84,101,17,254,232,157,141,102,76,233,158,52,138,180,40,216,63,45,73,254,201,63,253,159,191,78,210,132,186,159,226,220,200,235,203,61,203,135,37,39,231,167,
164,121,37,219,255,224,49,195,70,222,20,231,143,198,25,11,49,254,75,186,137,228,224,80,141,218,59,21,153,31,199,37,176,115,71,50,33,7,16,90,150,114,125,117,67,22,20,117,219,147,22,101,228,206,136,149,
59,120,193,47,7,39,185,169,89,81,179,122,121,98,28,119,216,64,68,139,202,173,95,53,189,72,25,209,8,48,214,145,21,25,118,116,24,179,231,225,246,6,187,27,104,103,147,8,155,74,68,118,230,44,222,88,172,25,
25,173,72,70,167,179,134,162,46,89,61,61,113,245,241,61,147,102,202,249,187,159,145,21,57,222,140,12,187,29,214,17,171,119,105,203,37,34,78,108,223,58,209,81,137,163,37,232,59,18,251,194,129,29,160,192,
153,104,48,81,113,17,108,28,105,86,146,23,25,191,254,171,255,204,249,249,91,66,72,200,138,138,44,81,113,204,34,45,155,245,150,253,222,144,100,57,73,146,179,122,121,145,249,168,113,52,117,123,172,24,218,
174,151,170,41,73,226,97,59,82,55,21,169,74,121,221,108,88,175,95,120,190,184,101,254,246,156,164,200,217,237,70,218,126,34,148,66,59,138,38,122,28,49,70,42,234,249,233,156,73,211,114,255,241,134,135,
167,123,230,111,223,209,79,102,178,15,217,190,146,168,132,36,139,70,186,104,95,119,135,29,68,148,170,234,136,2,246,145,165,116,168,218,198,232,18,84,135,75,59,38,84,141,163,69,229,5,102,187,230,195,183,
191,101,250,230,157,144,71,27,9,14,183,81,222,38,114,52,121,70,179,44,163,200,115,54,235,13,235,151,39,156,23,126,137,25,45,198,5,154,233,84,64,121,74,148,99,206,90,202,186,98,58,159,178,125,94,243,180,
124,100,121,115,69,146,148,52,179,9,163,241,180,211,57,58,88,130,119,24,179,19,212,174,245,120,239,40,218,150,197,201,28,183,90,241,195,111,126,79,123,254,134,211,243,115,156,25,177,67,132,96,69,247,175,
83,226,70,55,86,188,4,62,42,148,164,8,240,199,96,237,195,97,23,66,84,174,197,234,55,40,185,84,61,80,22,41,102,253,204,143,223,252,26,213,205,88,156,157,82,53,53,185,78,25,119,3,65,199,185,174,25,113,206,
144,21,41,101,153,179,186,123,226,238,246,6,149,102,114,208,59,135,67,211,76,103,132,193,224,188,40,64,80,65,40,144,105,198,246,229,149,79,183,55,216,221,134,186,40,152,44,78,216,110,70,230,111,206,143,
152,116,137,157,142,38,74,173,168,251,158,217,124,202,238,254,145,171,203,107,250,207,223,49,159,76,177,251,45,227,126,247,19,78,34,201,226,158,227,39,240,160,142,244,203,131,251,213,199,174,79,114,102,
15,218,251,120,9,6,169,115,5,77,146,82,86,57,223,255,197,47,120,126,126,98,246,217,207,232,166,83,234,162,98,220,238,163,188,83,97,157,37,56,217,251,53,253,132,213,245,45,247,119,55,108,215,27,230,95,
124,70,158,72,6,110,217,53,104,43,207,151,138,166,210,188,206,41,171,138,97,249,202,245,213,45,132,61,88,71,214,245,40,173,168,167,83,82,227,176,118,47,110,99,47,142,106,157,40,218,147,5,117,85,177,185,
95,241,252,120,79,61,155,50,63,127,135,118,30,103,7,169,230,227,89,113,200,236,214,209,129,175,147,67,183,239,142,210,204,68,197,76,4,125,112,221,234,232,48,182,63,57,182,99,138,88,242,63,253,179,127,
246,181,210,1,165,60,77,85,145,23,53,151,31,223,115,115,241,137,47,63,255,74,42,248,44,103,48,150,97,187,33,56,23,179,33,19,28,42,98,17,146,152,194,228,5,72,20,111,154,68,9,223,59,184,232,172,141,109,
42,72,229,230,125,64,7,71,213,54,252,230,155,95,209,55,45,58,41,200,178,130,36,207,226,3,167,35,233,79,42,136,44,47,80,73,130,27,7,198,97,43,51,209,52,97,28,44,90,103,244,147,41,120,43,15,8,14,156,165,
235,103,120,149,178,90,175,120,186,186,97,245,244,194,228,205,57,58,205,81,74,147,151,21,198,73,21,228,134,29,214,140,88,231,72,139,156,243,119,111,49,219,45,223,255,254,143,148,77,201,228,252,45,90,107,
246,195,54,58,33,137,9,74,242,90,164,137,150,63,247,162,64,248,73,82,38,123,11,149,106,198,193,200,66,254,144,4,235,28,70,110,15,240,35,85,89,241,186,126,229,215,127,249,11,190,248,147,47,81,58,37,203,
133,229,238,108,196,14,59,39,51,123,2,77,223,146,40,205,110,187,98,245,252,8,10,138,34,97,48,142,193,192,100,58,147,176,151,84,163,130,129,224,104,167,83,234,186,101,179,126,225,117,183,226,246,226,142,
190,239,40,235,138,213,122,71,85,139,234,39,4,39,65,33,65,100,169,198,58,186,249,148,207,191,250,146,215,187,7,190,249,155,191,230,236,243,47,232,38,19,236,184,227,248,139,137,34,44,122,46,132,169,226,
227,200,38,28,56,1,49,132,221,5,143,243,6,127,204,236,8,88,47,113,168,98,178,242,88,23,232,167,29,175,183,215,124,255,135,223,48,57,61,39,201,50,170,110,66,83,213,184,241,39,13,181,183,35,46,56,66,154,
225,172,103,220,190,242,116,123,141,49,138,233,108,198,56,26,140,243,212,253,36,86,250,242,161,114,46,144,213,13,111,223,156,177,127,93,241,188,89,241,124,125,35,33,47,243,57,163,113,76,230,51,240,114,
65,88,179,151,29,78,156,202,100,85,201,249,219,55,204,187,146,223,255,151,95,225,202,138,179,55,231,12,155,141,180,235,94,17,84,26,33,128,146,232,36,203,198,248,97,142,74,158,228,128,2,183,49,28,197,31,
48,8,250,8,64,83,114,123,18,148,167,170,42,182,143,119,252,240,205,175,217,144,209,78,38,100,101,73,95,87,216,221,136,9,238,136,238,246,206,145,214,57,121,146,240,116,123,199,229,251,15,40,149,48,59,63,
19,5,77,8,76,22,39,4,19,187,136,16,68,173,214,181,244,211,30,243,252,202,213,253,29,79,15,215,232,52,99,50,237,9,42,23,163,223,48,72,186,150,217,199,81,134,140,104,139,174,225,252,179,55,152,151,21,63,
252,250,183,44,254,236,207,168,178,156,113,216,31,233,197,206,201,235,1,42,34,210,53,4,29,115,143,5,53,146,103,18,52,46,203,240,40,97,141,216,246,224,29,46,46,101,101,84,156,131,177,124,255,159,127,197,
221,195,13,179,175,190,160,155,206,168,235,22,140,199,56,19,21,112,70,48,211,85,65,211,212,44,239,30,184,185,190,98,191,95,211,159,157,145,165,37,195,104,232,230,19,210,104,44,13,200,104,175,234,91,22,
167,167,12,207,27,238,175,110,88,173,30,37,61,175,173,41,138,154,178,107,228,123,153,1,51,238,143,103,95,146,36,212,211,9,139,183,231,140,207,91,110,63,94,210,188,61,149,226,108,176,200,20,38,94,126,234,
160,82,146,88,89,143,71,123,135,15,154,76,139,154,47,205,11,217,217,68,102,152,138,248,12,123,64,65,251,232,210,214,138,228,159,254,235,127,249,181,247,38,46,208,2,101,211,209,77,38,60,63,60,240,112,125,
195,155,55,111,196,126,238,28,102,216,19,172,149,229,106,164,226,29,170,28,57,220,84,92,56,17,157,134,18,171,167,179,66,2,192,93,92,60,69,249,94,162,5,99,42,127,79,241,203,255,252,11,62,255,236,51,130,
74,81,73,70,89,200,226,36,81,178,228,242,33,48,142,131,80,30,157,5,63,240,186,92,17,180,22,204,170,181,88,18,250,166,145,86,246,128,139,213,138,182,159,81,86,13,163,25,89,61,223,179,122,122,97,126,114,
130,74,179,200,252,111,48,227,158,113,191,151,88,64,39,21,75,154,166,204,78,79,72,146,132,239,126,251,123,170,162,226,236,179,207,24,205,200,48,12,2,36,138,76,19,81,34,249,99,206,170,74,244,177,61,199,
139,111,192,3,227,120,80,248,28,46,52,31,25,221,138,36,145,86,181,106,103,220,126,186,228,219,223,252,150,119,95,125,137,115,81,109,82,22,18,174,29,43,32,23,192,58,75,94,74,39,179,219,174,121,188,125,
36,203,75,250,190,97,28,70,188,74,104,251,62,162,24,132,215,98,172,37,203,51,186,110,194,227,195,51,79,203,23,158,238,238,169,250,30,157,164,140,131,103,122,50,35,88,43,15,172,29,69,231,237,188,240,82,
149,98,118,54,163,202,51,126,248,221,119,244,139,5,101,153,224,204,16,115,0,2,38,198,231,89,103,177,163,180,223,193,203,251,17,124,66,86,148,145,197,20,213,79,254,96,161,23,141,63,222,69,51,159,140,2,
211,60,167,40,51,110,63,254,200,237,213,5,84,45,193,41,178,60,167,105,27,236,40,76,117,121,38,29,227,104,105,186,134,68,9,17,244,233,250,2,116,198,226,237,169,176,131,140,167,233,123,169,242,162,166,223,
25,105,205,167,139,41,97,180,108,134,45,247,55,159,8,94,83,118,29,232,148,170,110,228,194,29,182,24,51,200,24,211,139,115,152,68,211,204,167,204,38,13,15,31,175,41,186,25,9,30,235,237,81,105,115,144,26,
90,227,36,5,11,40,139,130,16,2,89,81,136,124,53,40,84,16,85,78,196,239,201,62,38,206,185,65,197,189,71,92,226,229,154,113,249,196,247,191,253,134,124,182,160,170,43,242,170,164,239,91,236,110,16,86,86,
162,241,198,202,126,36,203,168,242,148,199,187,7,30,110,111,80,104,22,111,223,129,247,12,54,48,61,61,65,15,131,152,188,72,100,143,86,22,116,125,205,118,245,202,102,179,231,254,250,26,27,160,91,76,209,
153,224,62,252,184,199,218,1,119,196,20,200,239,151,100,5,243,243,83,170,36,225,211,251,79,244,231,231,164,90,248,53,216,159,244,228,225,96,37,61,48,236,149,68,56,38,73,74,94,87,104,31,176,118,47,221,
96,196,37,28,100,189,42,178,227,67,12,10,41,154,146,241,101,201,199,111,255,192,205,205,21,52,53,221,108,206,100,210,227,70,139,53,70,196,30,222,226,189,161,168,43,234,60,231,241,230,158,251,135,123,156,
183,156,190,123,39,152,13,244,49,214,209,199,60,94,130,64,208,186,190,195,237,13,15,55,15,44,159,238,25,198,61,147,243,55,148,121,73,81,87,184,193,224,237,225,217,148,51,66,107,49,70,78,207,22,228,58,
225,225,250,150,250,100,78,22,163,18,36,68,41,196,217,188,255,137,186,123,228,162,75,116,108,81,86,199,20,175,224,221,241,57,81,62,28,39,37,42,102,103,132,0,201,191,252,55,255,246,107,55,142,4,55,198,
121,161,135,60,227,244,221,57,207,247,183,188,255,221,15,124,249,229,87,52,211,158,221,110,131,25,118,34,137,138,68,60,103,13,168,244,39,141,115,220,76,75,156,152,166,200,51,153,79,122,135,139,85,9,206,
74,234,145,23,245,113,145,165,20,85,201,122,245,194,183,127,243,13,95,124,254,57,163,23,163,81,219,119,162,179,77,36,229,200,57,121,67,171,186,97,216,237,9,102,224,249,238,129,186,159,160,21,2,195,74,
83,218,73,47,55,155,82,199,32,129,118,50,35,132,192,56,236,184,191,189,226,233,246,137,243,207,222,177,223,203,135,60,205,115,172,117,24,179,197,249,40,245,242,1,23,52,117,215,48,155,77,120,255,219,63,
96,173,101,114,118,202,176,219,50,236,7,116,150,197,3,202,227,131,59,38,210,132,131,210,70,5,49,231,196,10,196,69,7,160,68,179,70,37,194,33,138,80,41,140,15,40,157,50,233,91,190,251,230,87,252,248,221,
119,148,147,94,114,125,117,74,211,78,142,170,22,133,19,86,13,80,55,53,187,205,150,97,183,225,246,242,19,117,215,210,116,21,155,215,13,1,57,244,101,97,149,224,141,3,111,105,250,154,233,252,132,237,234,
149,245,250,153,203,247,31,169,38,19,202,182,197,88,79,93,151,56,59,226,157,149,203,195,19,71,15,162,54,105,103,61,139,89,207,203,245,53,121,93,99,162,111,192,88,207,122,51,160,0,27,217,227,196,138,54,
201,11,146,236,48,227,79,8,94,49,140,67,180,134,251,24,52,17,151,150,62,6,198,107,45,14,225,60,39,213,25,247,87,31,121,185,191,197,39,57,77,215,146,36,57,109,219,97,71,115,140,205,243,102,20,122,103,37,
120,228,215,215,103,238,47,175,48,70,113,242,238,45,251,253,142,221,222,210,78,167,232,88,136,224,44,163,177,164,101,193,244,100,65,98,28,251,253,142,135,155,75,54,219,65,50,110,139,138,34,207,226,168,
210,68,5,15,209,55,225,209,42,35,41,10,102,167,115,246,171,37,36,58,166,194,169,24,210,226,143,26,106,34,146,33,77,83,210,50,39,201,50,50,37,193,46,62,4,134,81,252,45,251,97,71,158,137,218,105,52,163,
140,125,196,38,139,143,20,73,231,44,155,213,19,171,151,23,238,30,158,40,102,11,242,178,100,210,183,216,237,22,99,199,184,79,83,24,103,201,202,130,60,4,110,111,238,121,184,190,166,46,50,186,147,147,40,
74,80,204,78,22,236,95,95,37,170,210,154,216,57,22,204,79,22,40,231,89,62,61,242,225,199,31,112,73,34,154,243,110,130,10,178,212,54,102,207,81,1,75,34,145,156,105,66,53,155,83,164,138,113,187,39,205,179,
35,169,50,252,173,148,188,3,207,70,105,69,81,150,36,133,24,204,188,214,148,101,129,27,13,214,216,227,231,229,224,204,62,102,6,251,81,98,11,243,140,106,210,242,242,241,154,235,15,31,120,188,187,135,73,
71,90,149,204,102,115,146,200,242,146,108,88,228,208,239,27,10,157,113,127,117,207,227,195,45,89,234,169,231,176,248,65,129,0,0,32,0,73,68,65,84,115,97,48,121,75,51,237,81,163,143,221,143,20,176,89,157,
211,204,58,148,13,172,31,158,185,191,190,100,181,219,147,181,45,77,43,136,114,111,29,214,140,71,35,216,129,130,155,102,9,221,108,70,145,166,12,171,13,89,219,68,61,139,71,7,41,174,52,200,5,170,36,165,59,
40,9,68,202,242,34,230,92,164,224,68,206,170,210,244,88,52,169,40,18,57,18,137,67,32,249,95,255,247,127,247,245,56,142,184,97,144,195,40,200,4,220,7,152,78,103,228,77,193,15,191,249,35,39,39,167,100,117,
206,118,187,137,252,105,73,148,247,33,74,7,189,112,242,149,210,146,182,147,102,146,154,148,106,172,55,248,97,192,123,89,224,6,73,56,149,27,58,190,201,1,79,215,79,184,188,248,145,111,254,234,151,252,157,
191,247,167,236,141,69,145,208,118,61,49,155,92,160,108,195,128,82,158,188,44,217,110,119,56,59,112,115,121,73,85,54,164,89,38,75,191,172,160,109,59,156,119,140,206,97,246,35,74,5,202,182,163,42,74,188,
177,108,246,75,238,110,30,152,157,158,224,61,148,69,69,154,137,134,222,140,163,48,88,92,32,203,114,210,180,64,37,25,221,188,99,191,94,19,140,71,231,105,76,147,209,24,35,118,117,57,208,229,77,117,163,37,
79,115,178,188,4,20,195,238,149,36,21,94,143,76,217,132,11,116,224,156,11,41,211,71,60,108,16,76,106,158,242,225,143,223,114,243,225,35,94,59,145,78,38,5,85,221,75,171,231,93,252,251,162,102,40,235,2,
231,28,235,205,146,155,247,151,100,121,77,223,213,178,115,64,139,181,222,9,127,196,7,89,150,145,86,44,222,158,147,140,123,54,187,13,215,159,174,4,103,144,230,100,69,75,17,57,54,102,148,162,192,249,33,
234,160,227,210,45,205,200,235,146,253,110,39,140,27,35,243,202,215,213,154,178,172,36,51,33,56,156,135,36,77,201,203,10,165,50,210,172,32,205,10,30,110,239,8,209,77,108,173,140,194,14,248,4,21,63,28,
7,60,5,56,202,182,101,216,108,177,187,23,150,143,143,236,188,150,20,171,36,165,139,168,100,127,0,230,69,46,74,81,55,228,73,201,235,250,145,187,247,63,130,75,104,166,61,214,12,56,149,210,246,83,145,92,
106,73,236,114,198,136,163,122,218,83,229,41,155,215,21,207,47,183,172,214,3,89,221,209,79,166,66,177,244,86,208,17,66,240,138,220,30,25,95,169,44,139,7,88,116,121,106,125,100,226,200,159,75,140,104,213,
52,130,222,77,114,170,178,161,105,90,60,142,231,199,251,104,215,119,236,87,75,201,76,246,238,152,121,171,181,138,217,179,50,78,204,202,2,172,101,191,121,102,243,120,195,110,148,177,85,146,36,116,211,25,
196,67,7,66,76,252,242,100,69,65,65,224,249,233,145,167,187,59,240,158,201,233,25,222,88,12,138,190,107,112,99,52,89,121,79,150,87,148,93,75,213,73,224,137,221,108,185,254,240,158,141,25,233,78,226,88,
194,88,156,27,35,227,63,250,3,98,40,81,8,82,252,164,105,126,84,158,29,244,245,74,73,208,77,80,146,208,148,229,13,105,164,229,166,164,56,227,89,46,159,217,239,118,145,83,21,177,227,81,117,115,112,230,30,
178,108,181,74,72,139,140,162,46,184,187,184,225,225,241,150,215,151,103,76,8,212,147,9,253,108,74,161,83,57,40,149,18,143,131,10,84,125,77,10,60,94,221,115,123,127,11,206,208,45,22,4,39,151,117,219,119,
96,68,97,228,163,180,56,43,50,166,243,57,121,146,176,95,238,185,191,250,200,114,245,66,57,233,233,102,51,82,157,198,42,95,10,25,29,19,1,133,127,165,73,139,138,180,200,35,32,50,160,127,98,101,199,177,177,
138,216,140,156,188,168,200,138,74,242,59,18,233,8,119,235,87,241,42,16,72,98,244,37,209,188,166,18,145,122,122,111,73,254,205,191,253,63,191,14,202,99,135,45,222,91,156,11,4,23,100,33,233,37,92,183,154,
212,188,92,223,81,228,25,195,48,18,130,61,206,96,93,8,199,13,177,240,85,52,101,221,201,135,57,17,62,136,117,150,113,191,149,37,139,23,12,112,8,129,132,152,179,154,74,238,106,208,37,85,215,113,253,254,
59,238,62,94,80,53,173,196,13,162,5,43,27,129,90,196,49,129,152,149,82,214,155,13,222,236,184,185,188,166,59,157,225,163,161,35,205,75,138,86,22,53,194,216,31,208,4,202,186,161,238,26,236,56,240,250,242,
204,250,245,149,55,159,125,46,88,229,178,194,26,135,29,118,4,111,201,179,156,217,252,140,97,140,212,61,5,89,89,202,194,205,203,193,105,189,141,25,147,246,136,227,213,90,71,35,84,137,214,25,58,205,24,204,
142,251,155,91,178,36,67,233,191,245,134,198,55,198,7,123,116,28,91,43,139,239,217,108,194,118,179,225,238,234,146,229,211,139,216,232,75,249,192,36,69,65,146,164,178,47,73,16,26,40,137,120,40,246,59,
182,219,87,110,223,127,160,234,102,212,125,197,126,179,71,103,5,85,221,96,172,197,227,240,118,196,56,9,143,153,204,59,82,20,183,87,55,92,95,93,209,182,61,117,55,165,174,27,172,49,24,59,98,141,192,190,
146,36,46,202,148,102,187,31,226,112,79,197,139,95,24,74,73,150,198,103,74,178,67,243,178,33,203,43,201,26,46,91,202,186,225,187,223,253,14,63,238,73,203,130,84,107,193,248,106,45,232,90,36,3,87,210,11,
227,34,60,130,178,154,190,99,88,175,192,239,88,191,60,147,148,29,163,147,78,176,238,59,146,136,180,64,31,58,40,69,89,55,132,113,100,63,110,185,249,240,1,103,61,103,159,191,101,253,186,67,167,57,109,219,
202,97,239,61,102,220,11,156,15,168,187,154,170,168,216,60,189,112,241,225,35,131,245,156,125,241,37,109,85,225,131,197,56,73,86,59,252,156,33,74,111,125,16,167,180,138,230,23,231,4,86,166,99,245,18,148,
166,40,43,170,178,38,203,11,170,162,97,58,157,177,122,125,225,143,191,251,134,170,107,229,112,8,137,224,2,146,184,47,139,234,150,3,92,12,180,104,234,147,148,172,40,177,187,13,195,184,98,191,30,69,117,
213,136,218,171,153,202,152,74,212,62,113,196,170,32,47,115,114,21,184,186,190,229,241,254,158,50,205,153,189,125,35,220,156,162,162,171,43,198,221,94,70,76,146,220,140,11,208,47,78,168,138,130,215,251,
71,158,111,239,48,33,112,254,229,159,80,165,89,236,98,135,72,1,149,139,79,12,133,105,116,205,74,176,184,63,96,70,14,217,210,81,0,145,101,130,72,208,73,70,145,21,148,77,143,179,123,46,127,252,158,170,170,
226,69,40,161,66,135,56,80,117,48,245,73,168,246,241,115,149,183,53,218,120,238,62,221,96,140,228,51,20,211,57,65,43,250,249,148,66,73,8,78,136,8,226,67,46,113,234,225,250,234,154,229,243,11,137,246,180,
179,57,120,45,9,102,77,197,184,147,203,243,96,154,210,153,166,153,117,52,117,203,242,230,129,151,251,59,246,118,79,127,250,134,126,50,67,57,71,8,86,12,164,90,2,123,146,36,145,65,150,206,68,131,175,15,
11,234,24,11,42,117,161,252,94,73,74,94,9,34,33,205,114,242,188,162,40,74,150,119,55,108,55,107,210,76,156,217,90,29,83,85,163,104,70,198,131,40,79,242,143,255,217,255,242,117,81,214,24,231,24,246,35,
193,10,135,1,39,169,65,222,88,146,44,35,111,11,198,253,142,49,72,235,19,162,110,220,198,16,98,217,36,203,3,156,231,133,228,51,230,37,42,79,88,221,63,198,249,156,252,208,90,5,148,147,104,64,231,44,73,66,
68,1,24,138,170,166,156,180,124,247,235,191,146,116,161,164,164,110,107,172,243,148,77,71,150,229,56,47,238,204,3,99,164,170,27,130,25,8,97,224,227,183,63,210,247,253,81,37,98,172,167,169,107,153,21,123,
135,27,247,56,59,146,20,25,243,249,20,55,236,185,190,185,228,238,211,53,179,147,51,202,170,167,168,69,215,111,198,29,69,210,208,79,23,36,105,38,161,199,193,227,188,120,5,18,173,200,210,20,227,60,198,123,
134,97,39,155,250,172,36,207,27,178,178,34,73,10,242,188,38,169,26,222,127,255,7,244,104,201,170,226,248,208,19,121,59,198,186,227,124,78,255,173,37,117,192,179,56,61,99,247,186,229,233,238,158,253,184,
161,239,167,64,74,64,209,79,166,194,184,15,130,87,182,86,230,146,109,215,97,198,17,149,105,254,248,203,223,146,229,37,205,180,103,24,3,42,207,105,155,6,99,12,214,26,198,113,75,112,123,124,176,116,179,
158,197,124,193,230,241,137,31,191,251,150,201,116,202,244,228,140,188,172,32,24,201,65,192,163,226,120,73,18,148,220,177,146,56,16,70,137,61,140,55,142,36,43,164,8,40,74,202,170,101,50,157,83,182,13,
127,249,31,254,95,204,242,137,254,116,26,177,189,130,142,144,152,60,29,17,178,225,56,219,85,113,12,168,149,146,192,154,126,194,122,185,196,13,75,246,195,200,242,101,11,73,130,214,41,205,68,90,105,23,92,
228,238,203,232,163,159,77,81,104,94,215,75,30,174,46,216,175,13,147,147,153,236,85,116,74,91,55,226,124,116,3,227,184,139,201,92,160,171,156,179,55,231,36,195,158,139,31,127,96,240,142,207,126,254,167,
228,73,6,222,96,237,128,210,9,214,139,223,66,69,121,178,152,105,84,44,136,180,236,124,116,74,158,151,20,101,77,81,215,20,101,69,223,207,152,206,230,60,62,223,242,215,127,254,31,57,57,93,136,148,50,38,
96,29,42,1,173,146,24,223,24,193,89,206,31,169,179,105,146,145,20,25,90,37,172,95,94,217,237,95,120,125,94,209,206,79,73,147,156,209,123,250,233,156,44,72,124,158,28,141,94,2,218,219,134,196,90,30,31,
30,185,186,144,203,112,118,182,192,238,247,20,253,132,42,21,151,188,181,163,40,161,226,165,145,183,53,39,103,39,216,237,134,171,239,127,64,23,37,111,191,252,138,76,248,206,242,243,69,144,162,196,49,134,
163,208,225,255,103,234,189,154,37,187,210,51,189,103,249,237,210,31,91,22,168,2,208,150,211,28,114,24,49,98,72,161,63,48,67,178,73,142,20,186,144,66,87,250,29,248,79,138,144,137,25,26,145,77,178,13,208,
112,85,5,20,202,215,241,231,164,247,153,219,233,98,173,60,232,139,190,108,68,84,158,204,189,215,250,190,247,125,158,224,194,12,120,2,159,139,215,214,250,70,168,49,222,133,157,53,104,180,186,228,219,57,
159,253,234,31,232,30,244,60,40,108,199,70,186,237,48,132,174,75,85,223,202,66,234,224,223,211,90,146,118,90,136,245,150,243,171,11,198,195,33,141,102,195,83,104,149,33,235,180,112,198,250,190,130,242,
81,95,99,53,237,253,22,34,47,232,159,95,113,117,115,73,94,228,196,221,14,245,182,160,142,124,119,163,220,108,201,203,173,63,65,215,53,194,88,154,221,54,173,78,135,106,177,225,250,244,148,162,46,217,251,
224,33,177,73,124,175,160,44,188,202,224,246,36,174,130,171,57,20,200,248,225,214,35,1,45,21,198,57,180,141,110,255,103,172,67,72,201,213,251,215,12,174,47,136,91,153,151,182,135,116,96,160,76,250,238,
72,237,65,131,117,85,161,254,230,111,255,215,79,179,164,129,142,13,219,205,146,237,102,67,81,248,57,234,78,31,182,19,79,20,226,246,72,74,185,67,183,150,97,72,35,53,73,156,97,226,4,19,197,36,73,74,165,
75,222,61,121,230,67,27,129,103,46,111,25,213,129,238,39,125,177,100,7,34,42,138,146,102,51,99,189,92,50,186,60,67,74,77,214,234,250,47,68,9,54,241,105,21,81,239,34,113,57,74,130,139,98,230,243,21,69,
185,230,234,228,146,102,187,77,173,45,117,85,99,180,33,74,227,192,241,200,61,186,56,208,75,90,61,255,96,184,120,247,158,233,116,202,131,123,15,104,246,246,252,2,56,223,144,68,41,54,142,188,241,198,90,
54,219,141,223,91,212,181,95,174,25,205,118,179,34,47,74,84,13,206,24,162,36,243,154,50,27,209,104,182,145,198,240,213,151,159,49,63,59,165,181,215,65,104,115,59,202,145,66,251,31,64,120,51,251,159,160,
191,242,251,2,110,129,82,134,246,94,143,171,243,115,102,147,33,214,38,160,53,73,35,241,68,191,56,65,43,19,118,100,254,234,70,13,73,218,96,189,217,178,90,207,185,57,57,69,234,136,52,203,88,111,11,180,117,
196,206,250,68,210,118,77,29,94,226,219,109,129,138,12,7,71,7,84,155,13,103,239,79,144,214,178,127,120,132,210,138,60,95,255,1,194,218,127,63,138,98,151,58,18,1,113,28,56,56,2,180,117,68,81,130,117,49,
113,156,146,52,154,8,4,223,61,249,146,241,201,59,14,238,31,81,43,77,145,151,161,145,93,7,130,40,183,141,72,8,183,6,159,18,244,63,229,186,240,39,222,170,100,112,61,160,42,86,36,89,147,205,166,66,105,223,
201,72,26,13,244,142,131,83,213,254,20,39,4,73,154,66,153,179,41,182,12,175,175,88,47,115,26,157,38,249,182,194,100,13,223,32,173,138,80,175,247,174,225,50,184,23,218,7,123,52,93,196,251,231,47,88,148,
53,247,30,63,66,150,91,63,31,47,235,31,196,232,66,163,141,11,35,170,176,205,169,253,1,42,74,18,226,164,137,113,22,171,29,173,86,23,227,28,147,217,144,175,254,245,31,105,54,154,84,66,50,95,46,209,214,132,
171,191,68,75,225,211,112,187,125,25,59,124,178,255,30,33,65,214,18,105,20,90,43,70,151,55,204,151,83,214,203,130,168,145,161,149,164,150,130,56,203,96,235,51,223,66,248,115,112,37,124,151,69,83,51,24,
141,25,141,71,212,101,73,251,112,159,197,98,69,218,233,33,111,57,82,62,5,183,187,185,40,235,104,118,59,216,18,78,94,190,162,78,98,142,239,223,167,206,183,108,195,126,137,128,243,245,230,180,157,53,163,
14,141,243,160,97,52,97,204,167,13,218,198,52,91,93,148,50,148,249,156,47,254,229,31,104,181,219,184,36,185,205,166,239,94,124,62,254,44,188,21,12,9,162,10,125,24,175,129,172,132,64,233,224,159,61,191,
102,56,29,51,159,206,72,59,29,178,86,3,89,131,73,83,34,169,125,129,83,106,143,126,144,146,36,245,5,178,155,203,27,38,131,62,85,177,165,209,237,221,182,151,181,144,190,120,152,111,16,85,25,228,69,224,146,
136,238,126,143,114,177,229,230,242,130,90,9,246,238,220,197,10,233,199,93,97,47,69,45,195,62,179,164,172,252,115,197,79,74,194,178,91,72,92,28,163,180,69,42,255,91,138,162,152,178,132,217,205,21,175,
158,61,161,117,216,67,7,178,168,8,41,165,90,74,36,181,31,47,134,94,75,93,215,168,63,251,249,159,125,122,247,254,125,210,118,139,34,47,200,67,238,90,72,229,209,164,161,42,191,155,141,201,48,115,162,14,
127,50,81,99,117,66,154,54,72,211,38,81,154,17,167,9,155,114,201,151,255,244,255,161,114,137,109,55,61,186,83,136,219,31,170,16,2,164,111,133,41,81,7,208,147,68,162,17,148,116,15,247,89,207,103,92,157,
188,103,91,215,40,105,200,178,148,109,81,18,37,94,75,183,67,7,200,186,66,59,135,181,150,170,40,40,89,241,254,245,137,159,169,185,221,8,33,65,106,197,118,179,33,223,228,183,215,158,178,172,200,26,77,122,
157,14,195,243,75,6,131,17,31,253,248,71,216,56,37,95,111,60,51,7,63,187,147,74,177,217,172,88,109,54,62,147,43,60,124,173,40,107,20,146,52,141,137,179,166,127,152,70,9,81,214,160,168,74,158,126,249,25,
87,79,190,225,195,31,127,130,140,226,0,17,251,225,228,230,229,12,38,232,218,126,0,104,121,39,152,63,209,214,74,209,233,244,184,58,59,101,120,115,69,218,110,16,71,153,31,21,108,183,196,13,239,105,173,195,
15,104,119,60,104,183,154,20,171,45,232,154,147,87,175,16,198,17,55,50,150,147,5,46,78,209,90,179,217,110,216,230,94,144,92,20,187,217,168,228,248,193,125,178,40,226,219,175,190,66,90,199,225,241,93,242,
173,135,61,237,82,20,59,152,156,16,122,39,50,246,75,106,99,176,46,38,138,19,34,151,120,164,118,146,178,222,172,121,250,213,111,57,255,254,57,247,63,122,4,214,120,91,211,142,251,94,237,14,4,250,54,134,
88,237,146,55,59,198,140,244,39,162,186,44,112,105,138,211,17,195,155,75,54,171,41,210,198,40,101,209,74,80,149,130,40,77,177,90,133,101,89,121,59,230,105,180,26,200,188,100,157,111,152,12,47,152,76,230,
116,142,15,153,140,166,152,180,133,209,126,209,182,94,175,125,49,105,215,33,209,138,172,215,165,215,105,113,254,221,75,102,243,21,199,31,220,103,179,90,80,213,50,48,98,196,237,173,164,44,115,31,99,14,
35,140,36,107,17,69,17,74,107,92,146,210,108,117,40,69,197,235,87,47,120,241,197,191,146,69,150,180,221,197,234,31,100,245,121,145,7,111,174,14,163,29,133,12,113,59,79,161,149,62,36,177,43,107,137,26,
227,98,84,89,51,155,78,25,12,206,41,106,72,26,62,157,178,169,43,218,123,123,24,124,82,72,25,21,118,22,154,164,153,97,5,204,198,51,206,78,78,88,172,87,28,220,57,100,177,88,19,183,186,136,124,227,249,64,
181,191,177,87,37,24,227,105,157,217,94,151,72,105,78,158,61,199,116,59,52,91,77,242,213,38,196,11,5,149,8,169,180,242,86,122,141,10,41,156,56,248,152,189,19,185,201,222,254,177,151,18,205,198,60,255,
242,119,212,101,225,231,232,97,236,163,164,188,29,229,120,156,71,56,148,86,197,237,119,115,55,118,244,93,24,80,86,144,53,82,54,211,37,131,193,128,249,100,76,214,237,250,146,213,182,32,109,183,137,140,
245,189,142,128,134,81,145,165,179,223,195,20,48,238,247,233,95,157,179,220,108,200,218,109,170,162,198,53,155,254,33,158,123,48,92,69,208,14,86,126,244,219,62,222,199,148,146,203,87,239,81,141,148,246,
126,143,122,187,9,136,7,21,76,102,213,15,88,243,160,123,241,132,25,133,139,35,132,182,40,29,145,53,219,36,113,74,81,212,44,39,67,158,255,254,51,58,119,14,136,92,28,162,208,34,240,116,252,82,217,223,32,
60,71,168,14,99,77,245,243,143,126,242,233,122,177,228,254,7,15,49,214,146,231,27,214,43,111,78,50,218,87,192,149,86,62,194,36,165,39,209,133,204,176,146,21,177,142,200,178,6,81,146,145,54,154,232,200,
48,91,14,249,226,87,255,72,57,92,210,126,120,23,169,101,200,199,134,135,132,216,117,4,68,96,132,4,102,57,101,0,218,213,40,45,105,246,122,92,94,156,113,115,122,70,214,106,147,181,219,212,117,77,190,41,
112,206,243,112,60,205,206,87,244,165,214,52,178,38,155,213,154,229,98,198,229,201,5,157,110,23,151,164,204,86,43,108,20,123,171,82,81,248,17,198,109,28,181,242,155,251,189,3,102,227,9,111,95,188,230,
232,206,93,92,150,81,110,55,56,227,48,198,178,218,172,16,53,108,243,156,60,48,58,148,246,114,105,107,12,73,156,226,92,66,154,101,232,40,102,182,94,241,245,175,255,137,243,167,223,240,224,209,135,216,118,
35,16,65,66,153,34,120,49,61,134,64,133,253,137,159,243,33,9,167,100,47,120,175,170,26,19,197,100,89,131,147,215,175,153,142,6,212,74,18,103,25,86,91,106,240,139,31,229,139,110,53,176,92,174,169,42,200,
90,205,144,127,47,25,94,93,35,133,164,209,105,50,26,205,188,127,86,9,63,187,46,124,180,171,12,164,197,170,172,137,91,77,186,123,109,206,95,190,161,150,154,118,175,203,122,181,244,75,74,4,69,9,197,182,
248,3,135,176,0,161,112,81,66,156,164,196,73,131,180,209,97,83,86,156,94,156,242,245,239,126,197,236,242,148,195,253,99,42,103,253,105,42,208,5,119,72,1,163,21,214,249,204,53,129,95,35,66,188,79,238,126,
236,74,80,133,23,68,210,106,67,94,178,217,76,88,205,167,84,66,145,52,91,80,251,185,121,148,181,80,50,228,223,107,255,0,21,82,147,54,27,136,170,98,147,111,88,173,102,204,103,43,226,70,147,237,166,244,183,
38,233,91,139,249,118,29,150,243,158,114,170,66,119,163,179,215,97,61,234,179,90,87,190,116,88,150,127,32,158,128,34,47,145,114,23,219,149,88,27,17,199,9,90,89,226,56,35,109,117,88,44,151,188,123,243,
146,179,23,95,19,91,69,107,255,0,101,28,53,2,19,59,86,179,57,227,225,148,222,94,15,107,99,164,217,177,169,170,112,251,14,245,123,177,43,172,237,52,153,62,198,59,30,140,89,45,103,140,7,3,138,90,114,124,
124,23,81,85,40,99,73,218,93,68,229,21,122,30,111,225,173,89,46,78,136,148,164,216,46,185,60,125,79,127,188,96,239,248,8,17,190,75,213,198,23,20,181,10,78,217,58,164,182,132,231,64,237,237,29,48,58,61,
199,100,13,47,53,146,218,235,25,1,41,245,237,201,92,9,95,175,179,177,15,34,104,173,105,181,58,180,187,251,8,224,250,244,132,55,175,190,197,138,2,151,53,65,7,28,58,254,160,37,106,9,90,162,141,245,108,30,
126,56,68,121,123,92,88,226,138,224,150,22,158,213,223,106,118,89,245,39,12,199,125,198,163,17,89,167,131,211,150,90,64,220,108,16,105,237,11,166,97,249,95,227,119,70,78,107,150,163,9,195,203,43,134,131,
1,141,131,125,95,46,203,90,136,178,244,161,141,48,134,173,119,222,97,169,72,59,77,90,157,54,163,211,75,234,200,248,212,88,89,221,30,152,234,90,4,200,94,248,123,10,229,159,41,46,66,106,231,131,23,157,46,
145,117,172,150,11,70,131,107,250,39,47,17,26,210,86,59,224,104,110,221,74,20,149,31,185,90,27,33,133,12,169,186,220,191,96,255,247,255,227,127,251,244,230,242,138,193,233,53,15,62,121,4,74,178,152,142,
2,120,201,47,66,172,117,129,117,163,208,82,160,173,66,105,73,234,28,89,163,129,77,82,178,180,193,178,174,24,141,47,121,250,111,255,196,236,228,154,123,143,63,65,69,59,249,244,206,250,228,19,5,74,248,236,
125,89,108,145,161,64,225,171,246,62,138,183,91,230,54,154,109,174,46,46,56,125,243,218,215,198,5,104,99,40,138,0,4,115,158,255,190,217,110,168,66,110,190,209,108,7,6,208,138,233,120,68,107,239,0,101,
45,211,241,148,86,163,137,212,80,22,27,170,50,167,42,60,46,181,170,161,18,146,222,209,1,155,213,146,179,87,239,185,255,209,135,254,20,37,52,54,178,76,167,62,243,191,45,115,234,124,227,183,235,90,19,89,
71,150,166,68,81,76,179,217,164,214,150,183,23,231,124,249,143,255,192,244,205,11,14,247,246,233,124,240,144,138,31,220,189,187,68,173,49,26,109,34,164,148,108,115,95,4,241,207,135,192,202,8,122,67,207,
137,183,180,187,123,212,69,206,213,217,5,243,73,159,218,72,26,157,61,111,165,90,172,188,252,88,107,95,146,218,172,61,161,81,9,154,157,134,151,126,108,55,244,251,87,40,163,201,90,123,44,102,75,143,1,174,
43,242,141,47,156,133,26,114,208,78,130,182,150,86,183,195,106,60,242,15,104,118,47,134,157,35,213,159,70,140,241,178,228,40,78,137,92,140,139,18,154,173,46,219,10,134,253,1,223,127,243,25,249,232,130,
118,179,195,254,131,7,76,198,115,63,98,137,93,120,89,248,249,118,146,53,112,46,66,32,253,206,166,216,98,148,188,109,21,10,41,124,254,58,204,180,165,146,116,187,109,138,229,150,213,98,204,102,53,39,175,
36,46,107,250,147,185,148,196,89,3,171,20,181,240,203,245,188,242,187,170,180,217,192,9,197,120,52,98,54,25,178,94,174,72,187,93,168,20,205,118,19,202,130,155,171,27,202,18,92,164,66,178,202,195,123,133,
53,100,237,150,87,5,42,29,240,187,245,109,147,90,222,226,160,5,206,57,172,139,48,218,209,106,245,136,211,148,249,106,75,190,158,241,246,217,231,52,34,255,189,21,113,226,255,93,74,32,81,152,200,208,110,
117,136,162,4,105,125,108,211,217,24,37,5,101,181,69,171,112,123,16,62,181,67,85,135,17,144,64,104,77,175,215,65,229,37,147,225,152,193,245,13,217,254,62,173,110,211,103,235,5,62,157,148,231,97,236,226,
119,84,82,123,89,121,228,28,229,122,229,45,102,243,21,141,131,61,92,148,162,165,96,179,156,83,139,208,164,47,125,30,68,105,229,79,219,129,185,95,111,55,40,235,252,3,41,80,122,118,56,112,161,36,74,250,
37,179,86,6,237,98,186,157,125,146,52,35,47,43,54,235,37,103,239,94,144,88,143,75,87,81,12,117,29,210,40,30,75,161,180,65,41,235,151,216,198,34,149,221,109,142,110,31,246,132,182,246,174,244,36,149,240,
183,66,165,185,185,184,98,56,188,38,175,42,92,163,129,139,34,42,81,145,182,90,94,69,184,107,180,82,161,173,165,209,105,17,27,203,106,226,27,178,227,209,24,149,198,152,216,255,246,69,81,80,20,62,221,87,
139,58,200,212,189,233,207,38,25,105,171,65,62,157,97,98,63,127,47,119,69,193,144,69,241,68,9,129,150,154,40,142,49,54,198,218,132,222,193,17,18,193,122,181,102,57,157,144,111,166,204,39,67,162,78,39,
160,230,189,232,254,246,69,170,29,202,37,152,48,230,245,80,190,194,31,22,254,211,127,254,139,79,187,7,123,62,185,240,246,130,227,7,247,88,174,166,136,210,107,188,164,80,65,189,167,110,165,202,38,72,170,
163,36,37,73,82,116,146,177,32,231,187,111,191,226,233,191,253,51,155,171,62,119,30,124,76,243,206,129,151,9,104,255,240,146,66,32,148,193,57,159,48,241,101,172,13,101,25,192,71,59,244,167,82,97,153,171,
73,155,25,113,146,112,253,238,61,87,239,223,83,213,130,70,187,131,52,150,170,168,177,73,130,196,183,210,138,50,15,219,104,60,226,121,187,37,207,87,244,111,174,72,162,152,70,163,205,106,185,37,107,102,
94,106,94,238,124,162,101,184,5,214,108,55,91,210,118,155,86,187,193,251,239,95,208,72,27,184,52,165,40,182,140,70,67,174,206,79,253,34,69,43,172,179,164,46,34,73,252,92,45,106,52,217,212,53,215,195,62,
79,127,253,79,44,223,189,162,215,217,227,248,227,79,40,172,193,72,47,103,167,246,196,86,103,29,198,165,24,173,209,218,129,16,228,219,117,168,138,43,159,228,9,42,186,98,235,37,232,181,168,232,29,244,168,
203,130,243,147,83,150,147,17,243,217,28,235,82,172,54,148,155,13,205,86,55,180,21,253,21,63,207,87,148,85,69,171,211,38,146,146,201,112,204,197,197,59,230,235,53,221,131,35,140,178,164,105,138,168,61,
67,101,23,13,165,220,233,245,60,201,212,38,137,215,227,133,122,249,110,228,32,195,169,92,105,77,228,98,140,141,200,146,6,89,171,195,58,223,178,88,46,120,251,226,9,211,171,87,36,46,227,240,222,67,68,164,
113,177,163,170,74,172,177,88,103,137,226,148,56,73,208,198,146,36,77,148,178,76,198,99,180,170,48,218,107,238,180,241,181,243,50,164,49,34,23,121,167,178,132,70,171,77,181,94,147,111,22,44,23,19,42,97,
112,141,6,219,205,10,33,4,89,171,237,191,143,170,14,137,170,210,59,32,26,17,141,196,49,188,26,49,25,13,88,44,230,184,70,155,86,103,143,216,25,172,209,148,197,6,99,52,53,218,91,217,240,178,25,33,20,202,
234,112,171,170,3,242,183,162,202,139,176,208,174,137,99,255,160,55,42,166,211,59,66,198,17,179,217,156,249,124,194,171,103,159,163,235,130,44,107,35,172,99,27,122,44,126,236,167,136,194,77,73,42,141,
139,82,26,205,14,121,190,97,58,27,225,92,72,238,4,89,142,144,193,107,190,27,143,213,30,162,151,181,219,136,162,98,60,24,114,125,125,73,89,213,216,70,19,29,82,67,73,187,131,172,252,232,172,174,124,210,
73,89,77,220,106,18,219,136,106,189,230,226,253,123,110,174,134,52,14,246,105,247,246,113,90,133,185,179,103,191,212,85,141,168,5,104,137,18,30,63,172,157,245,101,159,80,46,220,129,255,132,242,253,20,
165,13,198,250,207,102,127,239,16,165,20,163,217,156,162,220,112,246,238,123,138,245,212,187,158,227,196,71,115,169,208,82,81,150,149,183,216,69,17,74,57,180,77,104,181,186,8,106,22,139,105,72,235,212,
225,166,35,110,211,94,65,26,138,148,138,184,149,225,164,100,58,24,49,184,190,228,250,234,28,211,108,162,181,5,4,105,203,115,168,138,178,10,202,195,2,161,37,89,187,73,146,36,228,179,37,253,235,115,6,151,
87,200,70,70,107,255,128,204,197,30,251,80,21,126,220,189,131,223,41,237,199,112,218,224,226,104,39,119,166,46,119,16,9,255,160,87,212,24,109,209,113,132,178,41,73,218,164,119,112,192,102,185,98,177,90,
81,151,57,249,106,204,98,112,133,140,18,180,210,222,32,167,100,176,9,26,148,139,113,214,162,173,195,186,216,251,53,10,223,8,151,82,161,254,250,111,126,249,105,94,214,68,105,76,85,109,153,222,140,48,206,
135,247,173,49,94,20,34,165,143,80,85,53,90,72,162,40,34,73,124,36,200,37,41,139,162,224,122,112,193,211,127,254,71,242,254,144,195,238,61,238,254,228,99,132,9,139,7,165,125,78,216,88,146,196,47,240,172,
241,252,251,109,190,165,216,132,40,30,254,3,170,165,65,86,101,224,135,64,214,106,17,197,17,151,39,39,44,231,115,132,115,36,73,236,103,246,213,15,167,188,162,244,80,174,109,190,165,170,42,210,44,65,84,
130,97,255,134,171,203,75,90,173,158,175,211,163,48,198,131,144,188,96,91,220,110,200,61,8,77,81,43,127,125,141,93,66,214,234,80,149,57,203,197,140,237,102,141,149,138,200,25,210,172,69,148,196,36,81,
76,148,54,153,174,182,44,103,83,222,190,249,142,243,103,223,160,49,28,222,191,79,178,223,67,43,127,67,130,26,99,20,206,58,162,40,69,25,75,154,52,40,181,98,116,115,229,21,140,66,162,110,193,239,220,10,
157,17,21,82,248,56,234,193,225,30,229,106,203,122,185,64,203,45,121,85,147,53,50,191,184,82,254,68,43,234,154,138,130,178,216,250,146,80,89,145,181,154,180,154,45,174,207,175,24,92,93,82,213,208,108,
247,104,118,187,225,212,24,176,190,162,14,87,118,29,70,112,50,40,244,244,109,230,217,132,253,142,84,30,28,103,163,8,107,99,210,40,37,106,180,152,173,55,92,246,111,184,185,185,224,228,187,47,80,40,238,
220,125,72,212,105,82,148,34,44,244,20,89,154,226,162,12,231,98,172,141,252,231,18,37,60,127,250,13,169,83,40,35,65,106,63,250,18,222,29,234,61,213,254,1,176,163,59,198,177,165,181,215,101,53,223,176,
205,87,140,250,151,244,175,134,180,122,251,190,123,160,12,105,214,8,223,201,10,45,252,156,150,26,226,44,163,215,233,176,158,46,184,60,59,99,181,217,114,247,225,135,100,205,22,86,107,148,240,50,147,48,
35,64,9,117,75,49,172,3,180,75,236,138,98,236,102,200,26,103,29,202,56,172,137,232,238,31,163,172,97,58,159,112,125,121,201,245,233,107,182,139,33,157,118,15,97,109,96,227,251,83,218,122,177,166,213,233,
249,209,146,117,56,235,104,181,187,158,202,249,234,5,105,150,220,154,159,110,35,138,161,145,206,142,159,34,20,66,43,180,209,184,52,69,44,87,220,92,93,50,26,13,88,231,21,157,110,135,42,247,122,190,172,
213,164,218,122,248,92,93,23,193,3,43,72,26,254,192,85,205,151,76,71,35,230,203,37,247,62,250,136,86,230,105,172,90,233,0,125,243,135,77,63,226,252,97,71,85,85,126,60,89,135,196,78,93,121,2,174,179,49,
54,138,48,38,226,224,224,14,46,137,88,46,103,76,230,115,230,163,62,171,233,21,26,129,178,201,237,109,184,170,42,162,56,33,107,182,48,198,34,180,35,78,91,36,89,147,237,114,198,249,251,183,94,98,47,252,
11,179,18,187,67,137,8,75,102,239,136,86,194,135,72,210,134,159,191,15,175,110,152,206,198,44,71,35,92,26,19,89,135,84,218,171,46,183,1,114,88,108,217,221,203,147,86,195,91,220,198,115,150,163,49,171,
197,156,230,209,17,7,7,135,190,9,92,5,182,125,120,24,203,160,105,84,194,255,78,148,146,200,186,66,170,93,122,171,14,29,35,141,139,18,159,102,75,154,116,218,93,54,219,53,155,229,154,77,190,37,223,206,169,
86,19,22,171,53,202,68,94,72,163,60,134,67,27,141,115,41,202,68,88,27,145,100,77,226,164,65,255,252,140,197,98,226,127,167,90,163,254,226,47,254,243,167,218,231,34,49,202,16,103,198,203,158,149,68,105,
139,210,126,25,167,180,164,170,43,26,141,148,52,245,179,106,21,71,12,231,51,38,195,1,207,191,252,45,179,247,231,100,182,201,71,255,254,23,232,86,140,14,111,119,165,21,145,243,165,18,23,197,68,145,143,
91,141,230,19,214,139,149,79,25,132,133,3,225,199,235,117,136,220,182,115,59,7,251,152,216,49,185,190,164,127,117,201,182,40,136,226,24,161,20,171,117,78,154,166,40,173,217,108,183,20,249,218,3,174,74,
104,182,90,88,109,24,92,95,242,246,245,11,162,216,191,53,163,56,166,168,43,234,224,21,45,3,239,69,132,171,216,124,54,199,74,203,166,200,73,210,24,89,195,166,216,98,164,192,25,111,137,138,179,6,113,20,
227,178,140,225,124,201,120,112,205,249,213,41,207,127,247,175,176,217,240,248,241,199,244,62,188,79,173,124,130,64,6,195,125,146,100,33,181,210,32,75,91,44,138,156,103,191,255,140,102,18,249,171,168,
242,167,16,41,212,109,94,91,74,227,71,30,218,123,127,141,113,220,125,112,31,234,154,109,177,98,50,236,83,150,146,168,145,249,248,104,37,200,154,205,32,28,169,40,183,101,96,198,23,24,103,56,190,123,135,
249,112,202,251,183,175,112,214,240,224,131,199,184,40,65,137,138,170,204,161,242,133,50,33,131,187,32,156,200,234,90,32,229,174,48,167,208,66,33,181,242,132,68,235,72,211,22,38,109,50,153,45,56,125,243,
158,139,119,111,184,126,253,132,122,179,230,224,206,3,218,7,7,228,85,5,149,63,80,164,73,236,191,79,81,68,156,164,216,164,65,33,36,191,249,251,191,163,147,104,210,118,28,56,51,248,20,137,54,24,109,48,218,
191,108,172,214,72,45,209,18,95,248,147,146,110,175,199,118,182,98,60,30,80,172,230,140,71,99,108,214,160,42,106,164,177,36,153,239,27,248,127,99,192,229,74,77,214,78,56,188,119,68,92,85,92,157,156,113,
51,154,176,127,255,1,105,154,161,217,65,252,66,87,34,124,95,171,202,167,146,20,126,28,5,53,90,234,48,198,201,176,46,193,24,71,239,224,14,203,178,98,50,26,113,122,114,194,100,120,201,118,118,67,18,39,68,
73,131,74,74,63,158,208,6,107,28,141,102,219,199,44,173,37,75,90,52,154,29,38,163,43,190,253,253,175,217,59,58,184,125,176,237,186,33,2,21,62,7,133,86,59,253,167,244,49,71,41,209,198,209,62,216,167,154,
205,152,14,250,140,134,125,132,245,55,187,186,172,192,70,1,57,144,163,68,24,45,8,110,91,235,189,189,46,166,134,171,119,239,152,173,22,220,121,252,49,105,228,99,134,85,89,128,18,126,161,28,232,189,224,
219,197,240,131,72,92,202,241,210,20,46,0,0,32,0,73,68,65,84,26,45,33,142,125,239,32,114,9,251,199,247,209,198,50,29,247,121,242,228,25,21,37,113,61,167,220,108,81,54,67,24,67,73,141,81,134,200,57,164,
177,62,160,161,19,26,205,30,205,102,139,124,61,226,233,23,159,209,222,223,131,186,66,6,156,190,148,161,208,40,85,176,219,249,89,254,238,33,44,149,164,115,208,35,18,138,121,127,196,116,218,103,124,51,64,
165,177,47,124,153,136,118,167,227,147,133,84,126,236,153,231,254,102,223,108,209,59,60,192,136,154,225,197,5,203,197,156,253,135,247,105,164,41,162,194,151,248,106,64,123,231,240,15,16,51,249,67,231,
160,250,193,183,172,140,69,71,9,198,165,52,26,93,246,247,246,153,12,39,44,54,57,203,245,130,106,57,37,95,12,153,207,102,160,13,181,0,29,199,216,208,245,73,162,4,109,92,184,5,182,145,218,114,250,252,25,
243,213,4,107,245,109,143,69,253,242,175,254,226,83,169,253,41,206,75,72,252,214,223,104,141,52,198,203,44,164,194,72,25,62,244,4,23,37,200,56,98,50,159,177,156,78,121,243,242,41,253,23,47,208,149,227,
222,7,143,216,123,112,128,12,115,37,165,188,144,195,38,41,113,156,248,17,80,28,113,118,118,194,248,252,10,212,15,173,72,255,111,223,217,177,60,155,164,14,28,8,170,138,118,175,131,181,142,201,96,192,98,
49,67,40,65,154,54,49,70,251,31,114,156,122,36,104,89,66,229,233,147,69,94,96,146,148,86,171,193,184,223,231,230,252,148,94,175,199,254,241,29,106,33,40,42,63,119,171,2,158,213,11,64,128,109,78,179,211,
193,218,136,44,206,208,70,135,17,80,73,20,150,145,81,20,35,157,227,122,54,227,252,236,130,241,184,207,235,175,62,35,159,76,56,232,28,240,240,103,63,161,210,10,173,45,90,42,162,216,17,69,49,46,74,73,146,
6,73,179,197,120,62,227,55,127,247,223,56,234,181,177,169,245,111,236,112,18,216,157,74,148,146,126,164,166,4,70,41,15,104,19,222,183,218,222,235,50,26,76,120,251,226,45,147,201,136,164,209,196,89,71,
25,228,35,113,226,117,113,85,181,69,72,159,233,213,210,99,149,187,7,251,212,219,130,235,179,83,242,170,226,224,206,61,172,177,212,59,79,49,161,205,25,98,111,69,81,178,90,174,128,26,231,92,56,221,75,63,
146,137,98,210,184,129,116,25,179,249,130,213,114,193,124,54,225,242,237,51,242,229,148,70,179,203,193,157,123,126,241,38,61,77,179,213,234,16,135,28,122,156,100,216,40,99,185,92,240,213,111,255,149,68,
212,236,223,187,235,29,199,33,113,97,156,79,142,233,176,0,221,21,87,252,194,81,160,181,67,73,60,71,168,211,102,59,93,176,222,204,89,175,166,126,191,209,108,145,111,11,182,101,69,183,215,195,4,153,186,
14,75,85,41,4,218,24,58,251,61,58,141,140,179,87,111,184,184,238,115,231,131,15,104,100,65,104,95,108,80,42,236,18,194,131,145,122,87,36,12,240,174,64,187,180,46,198,152,132,222,222,17,57,176,92,44,216,
110,22,220,92,156,178,94,12,209,210,127,127,117,20,147,231,222,245,170,181,241,216,9,109,176,38,161,211,237,97,227,152,201,228,154,39,159,253,138,78,187,227,161,92,97,85,32,181,244,29,12,229,255,166,90,
219,240,64,169,253,141,178,246,99,88,33,43,148,211,100,141,6,34,47,153,79,198,220,92,157,81,40,137,77,19,182,155,173,23,127,56,23,120,244,185,191,65,4,25,186,50,138,70,119,31,43,4,253,211,19,198,139,13,
119,31,127,128,198,227,157,119,232,102,33,5,85,48,147,237,150,240,30,53,85,6,217,139,13,55,193,132,189,131,251,212,66,178,222,172,56,121,245,146,247,111,79,136,76,1,229,10,165,29,194,152,128,19,145,104,
173,48,81,68,93,72,178,70,199,247,41,164,161,216,76,248,238,243,223,120,113,73,28,5,169,16,225,176,20,156,11,82,133,130,98,136,144,171,176,91,9,47,198,172,221,34,18,146,193,197,53,155,229,130,217,124,
130,105,52,137,146,140,56,137,137,226,152,58,207,111,121,97,50,144,103,85,226,104,237,117,209,149,98,124,126,205,100,49,99,255,225,3,226,40,190,197,172,248,11,151,162,12,101,80,127,170,151,183,251,177,
63,84,155,26,19,209,104,118,233,116,58,172,22,11,230,139,37,121,177,166,90,205,72,162,130,113,127,132,176,145,151,218,8,229,91,252,193,193,109,173,37,73,27,36,73,74,89,22,12,78,222,112,117,121,74,171,
219,242,145,221,176,231,81,255,233,63,255,229,167,82,72,180,12,164,62,165,252,85,93,5,106,157,20,104,9,78,25,178,102,27,27,167,224,12,87,253,62,203,233,156,243,203,55,156,124,249,57,213,170,224,238,189,
199,60,248,233,199,72,171,80,18,180,246,76,144,36,245,39,225,40,73,193,56,158,63,127,194,235,207,190,164,123,180,239,115,215,58,60,220,130,149,222,71,174,66,190,56,100,85,119,180,64,191,149,86,244,207,
206,24,92,92,98,157,197,69,142,186,246,45,196,70,171,69,190,205,61,232,173,242,144,177,178,244,213,250,253,163,67,150,139,57,223,63,121,194,241,241,49,221,195,35,54,219,156,50,207,217,110,22,94,23,22,
26,178,105,22,33,141,195,217,132,118,183,235,249,37,74,3,21,113,156,16,197,9,181,181,220,140,39,220,92,92,80,174,151,124,247,213,239,89,92,95,208,138,51,30,255,236,103,152,70,230,77,75,214,145,166,17,
54,78,136,92,74,35,235,80,75,205,96,52,224,215,127,255,255,208,141,83,90,135,93,255,131,144,94,237,38,195,131,206,89,255,3,169,241,35,22,173,126,56,217,177,123,64,237,29,177,89,174,185,120,119,194,104,
112,237,185,38,113,194,182,168,216,228,133,255,163,227,117,135,82,251,23,69,93,23,40,109,56,186,119,151,70,154,240,237,151,95,144,23,21,135,247,31,96,141,100,177,88,48,159,78,73,34,23,42,221,254,42,190,
158,47,144,66,98,227,8,99,124,154,198,69,9,206,165,72,155,50,91,174,153,77,103,204,166,35,94,127,251,21,235,241,53,198,56,30,62,254,24,19,199,62,129,160,52,89,214,240,87,122,109,73,179,54,91,161,24,207,
102,124,245,235,127,100,59,30,240,225,79,126,130,52,18,109,194,98,24,225,181,150,218,97,92,132,137,92,208,255,149,30,135,172,172,223,43,132,146,149,148,154,172,211,65,35,89,45,198,44,231,83,166,147,5,
210,56,242,213,146,213,186,164,221,109,123,125,93,93,162,117,56,125,41,95,212,201,58,109,218,157,6,55,111,79,56,63,187,228,238,39,31,83,151,57,101,233,221,188,190,68,104,124,52,177,246,203,61,33,180,183,
54,89,235,151,145,58,102,239,232,62,155,178,98,189,90,177,156,79,24,92,95,50,186,126,139,172,193,217,4,19,167,1,28,230,71,158,81,156,32,132,166,153,182,56,190,123,31,140,225,245,203,239,120,249,245,111,
104,164,41,237,222,94,40,185,203,29,114,198,159,16,173,195,104,223,214,44,139,210,199,134,195,152,116,183,52,181,1,64,150,117,246,96,181,100,116,125,195,233,187,55,12,70,99,176,49,73,228,80,42,242,187,
138,128,60,240,191,67,127,224,208,214,208,221,239,146,198,17,23,223,191,102,190,201,105,31,30,32,139,226,86,38,47,234,202,63,108,235,42,220,210,235,91,12,130,209,17,206,69,104,147,178,119,120,159,66,74,
22,171,5,171,245,138,58,95,99,116,1,197,2,33,45,38,74,17,40,180,181,88,227,23,222,218,197,28,221,125,64,187,211,102,179,222,176,92,77,57,127,254,21,82,40,162,102,35,252,46,234,224,184,85,225,247,236,157,
217,117,176,93,41,169,111,23,156,254,247,12,218,26,26,7,61,98,20,211,193,136,233,100,194,124,52,196,196,9,173,238,30,82,105,210,36,14,28,170,138,154,210,75,108,68,237,111,78,135,123,36,81,204,205,171,
83,214,117,197,254,253,187,232,218,219,240,118,80,55,74,31,83,18,2,68,21,38,26,65,116,162,157,223,67,164,89,155,118,187,205,98,62,103,50,153,177,94,173,201,243,5,177,94,49,190,190,161,146,17,34,32,42,
92,20,227,146,20,103,172,63,148,182,58,40,109,89,205,87,204,250,231,188,121,254,13,123,247,238,132,219,177,79,221,73,165,80,127,243,87,191,252,84,224,115,207,218,24,159,158,217,197,49,5,88,109,208,74,
146,166,13,76,156,144,43,197,77,127,200,114,50,101,60,185,230,205,151,191,101,221,31,147,184,14,143,254,248,39,8,167,112,214,159,82,147,172,69,179,213,38,73,18,132,141,88,228,91,190,123,242,57,111,62,
251,156,163,59,247,80,105,48,204,7,233,137,16,96,181,191,214,74,173,111,49,10,94,117,88,248,116,68,5,237,118,27,107,13,151,167,39,92,158,159,162,141,33,206,18,74,36,85,37,112,73,76,85,21,190,105,26,216,
217,101,157,35,165,166,183,191,143,86,138,87,79,159,17,89,71,247,206,49,121,190,101,187,153,251,8,93,24,21,236,78,5,34,108,39,235,128,42,213,82,16,197,17,152,136,203,235,33,163,235,27,138,237,134,183,
47,159,49,57,127,143,174,5,63,254,249,207,232,220,189,131,181,138,36,138,200,26,45,127,35,8,197,163,201,118,203,229,197,9,159,255,183,255,155,68,24,238,252,232,35,170,112,146,151,90,221,206,113,181,210,
36,105,226,157,4,69,142,160,240,47,65,229,23,80,162,172,208,90,81,32,57,60,218,195,41,193,240,242,138,217,164,143,54,146,102,179,203,122,189,165,46,4,205,102,131,90,148,94,29,25,94,92,2,73,93,86,68,173,
132,131,253,125,70,167,23,244,175,250,152,36,101,187,152,144,68,54,232,10,195,254,161,174,137,98,75,20,69,88,171,177,214,163,172,227,184,65,109,83,102,179,21,147,209,152,245,106,193,171,103,191,103,120,
254,6,107,83,30,60,124,68,210,109,98,141,37,105,52,112,54,38,201,50,34,23,147,54,187,204,214,91,190,255,254,91,158,253,238,95,96,57,229,225,71,31,227,178,244,7,209,78,45,194,77,194,224,34,191,228,246,
252,162,173,47,98,73,233,151,185,161,180,230,172,119,19,40,173,72,219,29,12,138,249,116,206,120,60,98,179,89,144,54,91,200,218,80,8,197,222,94,27,81,7,147,91,233,71,85,62,235,173,176,73,198,254,157,125,
84,190,228,252,228,6,151,90,156,18,183,197,156,10,129,214,210,227,175,43,239,118,144,74,97,163,148,36,109,177,127,112,151,213,54,103,177,90,80,83,113,117,246,150,171,119,223,177,89,46,136,92,68,45,20,
171,109,238,31,104,145,35,114,49,82,89,186,157,61,142,239,223,99,177,156,243,253,243,39,92,188,124,134,85,146,222,157,123,84,66,249,174,133,244,163,138,186,6,169,173,23,194,4,140,112,190,245,8,108,169,
119,201,13,121,251,2,160,246,29,137,172,153,97,133,97,124,115,195,224,230,134,217,116,70,220,110,227,108,68,20,39,126,111,183,179,18,132,84,89,21,108,100,113,214,96,255,206,1,139,171,75,86,219,146,102,
167,233,177,30,66,123,107,215,142,37,84,227,145,15,161,20,229,145,0,41,123,71,15,200,235,154,249,108,198,98,49,243,158,229,243,183,20,235,41,218,88,180,75,2,92,207,207,166,165,177,104,101,233,238,29,210,
237,180,89,204,167,156,190,123,203,232,250,61,86,129,78,50,132,212,65,243,183,75,178,11,140,141,209,214,97,2,190,160,42,243,91,151,178,220,97,152,67,68,80,41,69,218,237,144,198,49,139,254,144,241,120,
204,100,120,67,227,240,200,255,222,108,130,9,183,169,178,40,3,178,89,132,100,150,36,233,52,57,56,62,98,113,53,100,182,94,209,218,239,34,242,130,218,207,183,2,153,51,244,51,68,21,22,236,225,101,102,35,
178,86,151,86,179,197,108,62,103,189,222,120,28,201,102,74,185,236,51,26,93,179,205,21,58,178,158,15,100,99,226,212,135,27,156,77,232,118,247,161,170,153,76,150,140,111,206,56,121,245,148,180,215,37,142,
18,15,127,220,125,34,70,162,254,234,151,191,252,84,32,252,15,91,43,140,179,72,233,151,98,50,176,106,92,156,96,226,132,218,70,140,167,83,214,139,5,235,124,198,171,47,126,195,252,242,28,69,196,143,254,232,
23,184,94,11,99,13,205,44,140,44,178,12,23,197,84,70,51,152,79,249,254,219,175,248,238,87,255,204,126,235,144,230,253,99,180,241,127,8,45,13,50,252,129,157,139,176,81,236,219,127,101,30,76,81,34,212,213,
125,117,90,42,73,247,224,128,40,78,56,127,119,194,245,217,53,130,154,110,167,3,74,179,94,230,100,89,28,196,3,249,109,249,66,42,137,148,154,70,187,73,146,56,222,61,127,141,115,142,70,167,205,98,58,241,
58,190,91,156,168,196,24,127,34,17,149,79,212,84,84,56,99,48,73,204,205,116,198,106,50,165,170,11,222,189,250,150,155,215,207,169,214,107,62,122,252,49,247,127,250,35,108,20,227,92,76,187,217,34,78,252,
200,66,71,9,215,147,25,79,191,254,138,103,191,250,59,116,81,242,232,167,63,199,38,145,63,149,72,21,226,175,62,169,100,163,4,161,76,152,135,110,61,225,50,196,253,172,85,33,181,98,168,182,5,218,40,14,238,
28,226,148,98,60,232,51,24,15,169,234,218,123,96,171,26,231,34,226,88,83,230,235,64,17,245,205,102,165,188,180,38,142,29,157,195,46,229,102,201,108,48,161,209,142,209,90,221,218,118,126,200,19,248,209,
129,115,190,222,109,92,138,78,154,204,86,27,202,213,10,100,193,251,119,207,57,127,249,132,237,114,195,227,143,62,97,239,222,29,207,0,50,14,27,249,43,114,108,83,92,214,98,178,92,211,191,188,224,245,55,
191,135,237,132,163,59,15,105,31,30,82,67,88,34,251,250,187,115,17,54,206,208,206,33,141,79,199,20,158,173,28,254,29,194,63,28,194,139,73,226,251,18,82,106,218,123,109,98,169,152,12,250,44,151,83,214,
235,5,141,163,123,172,150,57,89,179,73,108,52,197,102,27,26,206,130,34,207,125,237,173,170,80,54,38,235,182,16,85,65,93,84,104,235,233,158,85,94,82,135,30,133,255,60,43,148,142,112,81,140,214,142,238,
193,29,74,161,89,174,150,172,230,83,230,227,62,231,47,159,50,30,245,49,38,229,248,206,93,150,139,45,198,104,218,157,14,214,57,180,82,220,189,247,33,237,253,30,243,249,130,193,205,21,239,190,127,74,51,
141,72,155,93,116,156,81,149,117,48,179,201,192,156,177,160,13,66,105,148,176,196,113,26,240,40,53,181,240,227,184,170,10,248,242,112,179,171,107,80,214,83,26,19,109,153,246,135,12,71,125,54,139,57,73,
111,207,55,129,211,212,63,232,203,45,224,151,210,181,119,232,133,140,191,37,105,55,16,69,25,230,210,187,134,103,8,64,148,126,103,36,149,207,196,251,125,68,194,222,225,3,132,210,204,23,51,22,179,49,139,
113,159,139,215,79,153,205,39,80,11,154,157,61,192,39,190,172,117,62,237,163,98,14,142,239,179,183,223,35,95,175,152,76,6,140,135,87,52,28,20,24,31,240,167,166,174,124,71,3,33,125,241,76,155,112,112,83,
72,225,168,138,130,74,4,170,102,136,204,214,129,202,27,68,199,52,246,186,52,226,132,217,85,159,241,116,204,100,208,199,54,91,24,237,176,105,130,69,132,67,72,64,36,239,234,195,181,192,166,41,141,48,74,
220,148,158,162,169,180,111,122,203,16,9,173,111,253,188,194,223,202,108,68,156,52,104,181,247,153,205,22,44,230,43,170,34,39,95,79,88,205,47,153,13,175,41,177,184,180,9,82,97,157,243,77,126,109,177,54,
225,248,254,61,140,150,204,103,115,182,235,5,179,225,57,181,168,125,161,140,31,94,126,66,107,191,247,250,139,191,252,235,79,149,50,190,34,29,22,180,254,138,12,177,181,68,113,134,137,82,42,237,152,206,
231,108,103,19,150,155,41,223,127,241,111,140,223,188,71,149,134,199,63,254,35,246,31,223,35,138,35,4,154,222,94,143,52,203,112,73,198,162,170,120,127,113,193,63,255,191,255,23,23,79,190,166,155,236,113,
239,103,63,70,91,137,81,97,110,170,20,214,26,92,20,97,163,20,169,140,31,245,4,145,136,84,198,159,94,42,113,123,141,173,40,105,180,90,180,247,186,204,230,115,174,46,78,168,171,146,251,31,62,38,175,5,197,
182,194,37,17,85,93,162,85,29,246,0,69,16,216,151,24,99,233,29,238,209,191,184,244,189,47,227,137,159,32,144,58,224,106,141,243,167,39,233,55,220,53,96,211,148,193,124,193,114,56,98,179,93,241,246,229,
51,206,158,124,73,49,95,241,209,163,31,241,201,159,252,2,23,91,34,103,253,8,44,201,144,218,145,163,185,234,15,121,247,230,37,175,62,251,23,212,122,201,135,159,252,148,236,112,207,19,238,140,127,217,104,
237,199,22,206,249,211,137,214,14,107,172,223,31,224,25,53,85,160,113,214,66,82,20,213,45,68,75,42,56,186,119,72,35,107,48,30,12,24,93,157,51,28,14,73,123,7,20,5,52,154,13,31,165,203,61,107,94,80,249,
180,75,136,15,214,66,225,210,24,235,60,250,215,88,227,49,22,128,14,246,33,33,37,214,56,162,184,137,113,9,58,106,48,28,206,208,212,148,229,146,175,127,255,175,188,254,230,115,242,77,193,227,71,63,225,238,
71,143,208,198,63,152,92,210,32,118,49,141,102,27,92,196,69,127,192,118,181,224,251,111,126,199,118,118,205,94,239,152,195,251,119,61,178,33,148,184,60,117,53,33,73,18,164,54,1,30,22,51,154,204,24,15,
7,36,105,20,10,130,94,66,179,35,168,148,85,137,214,26,17,246,29,89,171,193,94,171,195,228,102,192,205,213,21,163,155,107,76,148,16,167,77,178,70,138,213,21,219,205,250,150,82,88,228,57,69,233,79,184,18,
175,108,140,211,152,10,65,81,20,33,13,179,75,179,212,126,124,25,101,40,27,209,238,222,161,0,38,227,33,171,229,130,201,232,154,171,211,23,220,92,158,162,165,226,240,238,7,36,141,6,73,51,162,217,106,227,
226,20,163,99,238,63,250,8,233,44,253,225,144,209,104,192,247,223,124,78,51,49,68,73,138,182,41,66,106,202,210,223,92,140,245,167,59,109,60,64,207,154,152,86,103,143,249,124,198,116,54,246,214,53,233,
225,100,50,152,178,132,8,190,138,90,80,85,2,101,53,217,94,143,70,35,37,159,207,153,140,7,92,188,59,37,234,180,233,116,247,73,34,231,113,228,101,238,199,86,16,164,222,242,150,187,30,101,206,163,0,164,47,
78,138,91,231,174,143,137,10,225,31,82,218,38,28,220,249,0,33,53,211,217,152,233,104,200,116,120,69,255,228,37,163,193,21,82,57,246,143,143,65,249,116,147,117,17,90,107,172,109,112,255,193,135,104,103,
152,207,23,76,103,19,222,190,124,65,150,24,95,250,11,201,58,177,11,136,88,77,228,18,100,32,246,106,151,145,182,186,108,86,115,150,171,121,80,143,234,91,118,141,223,255,4,204,139,242,123,153,172,221,98,
239,96,143,245,112,193,205,245,37,131,171,11,114,33,137,219,29,186,65,176,148,7,234,168,167,7,84,225,96,4,198,250,214,176,20,62,190,92,135,3,137,255,244,252,120,203,27,170,252,97,41,109,119,232,236,237,
51,27,207,153,207,230,148,245,154,249,232,156,155,179,55,172,230,67,42,25,147,53,124,222,94,69,49,46,142,209,198,208,104,117,57,58,58,166,174,11,38,131,1,195,209,136,245,226,134,197,100,228,199,80,82,
220,90,193,132,148,193,37,145,160,126,249,95,254,203,167,254,116,111,194,226,116,247,225,105,162,56,65,187,12,25,197,204,22,51,54,139,5,203,245,144,247,207,191,230,250,187,215,80,104,238,220,255,144,31,
253,201,207,208,145,38,142,50,58,221,14,81,234,193,97,211,109,193,217,197,5,175,158,63,229,250,219,103,56,97,121,244,211,127,71,210,105,98,172,70,106,225,103,178,54,32,63,141,143,229,105,107,17,129,228,
184,35,29,202,112,237,242,33,197,220,95,23,133,160,217,106,114,120,124,204,248,234,154,241,160,79,81,86,52,15,238,32,165,37,138,93,152,93,111,189,125,39,136,53,100,56,165,8,165,252,143,184,42,66,100,203,
103,172,141,242,15,119,99,35,180,240,169,144,26,143,43,30,206,23,76,6,125,182,249,218,159,100,159,125,201,106,58,99,175,123,204,159,252,15,127,142,205,18,180,85,24,151,17,37,62,161,177,174,21,215,55,67,
86,155,25,207,62,255,53,249,104,192,126,239,152,251,63,254,136,90,138,219,197,167,214,6,103,19,108,228,31,248,46,74,176,113,198,229,249,5,171,217,20,227,204,45,154,250,54,107,44,106,164,168,110,141,70,
101,89,146,117,218,244,58,123,92,158,95,115,113,118,194,106,54,231,206,221,251,68,113,138,115,206,107,247,202,109,56,29,251,14,67,89,149,8,124,162,106,135,98,53,214,248,27,64,104,5,215,8,100,93,99,163,
12,235,82,164,78,152,45,214,254,229,97,4,111,94,125,199,219,39,95,176,158,47,121,248,240,49,15,62,126,140,48,190,30,30,167,41,54,74,72,179,6,155,170,230,242,234,154,205,98,202,219,23,79,153,92,191,35,
118,150,187,15,30,225,178,52,156,152,42,148,118,126,124,20,57,148,114,72,97,208,54,101,50,153,112,250,226,59,58,157,38,90,251,7,79,94,236,146,69,254,101,81,250,70,157,31,233,85,62,38,153,180,50,26,205,
22,219,201,130,126,255,156,60,223,176,127,247,62,237,110,15,167,21,219,237,134,178,42,216,6,101,98,93,85,30,168,21,148,139,2,63,26,161,46,110,139,60,2,255,96,181,46,197,186,152,70,107,143,90,25,166,211,
49,131,235,11,182,171,37,103,175,158,114,117,241,142,200,37,28,29,221,163,187,191,143,214,190,141,172,181,70,171,132,59,247,30,178,169,75,6,215,55,140,71,125,78,94,124,203,118,57,165,209,108,121,237,103,
88,78,35,107,156,113,56,23,121,199,170,144,68,81,147,70,171,203,232,250,156,147,147,247,184,200,120,22,186,38,200,192,131,237,170,46,41,114,159,82,17,181,199,105,75,41,189,196,163,213,98,61,154,49,25,
13,153,141,135,28,126,240,144,78,183,231,233,154,101,193,38,72,123,124,60,216,159,154,203,160,240,20,127,208,238,13,6,19,159,206,161,246,7,22,151,208,236,30,225,178,148,98,181,228,236,237,27,150,139,41,
253,139,151,204,70,125,144,134,251,15,30,160,157,243,221,131,216,71,190,147,168,201,157,251,15,17,74,178,88,204,232,15,7,156,188,252,158,44,130,237,106,75,33,12,149,12,244,80,33,81,198,98,108,226,49,11,
202,96,147,166,23,252,156,191,231,242,242,28,23,105,100,96,248,120,35,93,21,128,107,94,23,89,87,254,5,46,148,36,106,164,244,246,122,108,39,107,230,203,37,227,235,115,226,86,139,59,15,30,98,106,65,93,84,
84,181,55,146,253,208,191,8,134,191,186,12,99,89,31,58,81,187,87,100,144,143,75,165,177,81,138,141,27,180,219,61,86,203,45,171,213,156,237,122,198,240,226,29,211,225,57,211,254,13,210,38,100,173,174,79,
110,185,200,79,90,180,165,217,218,227,232,232,144,106,155,51,30,77,24,94,95,83,108,231,172,39,3,132,246,36,205,42,52,140,165,212,40,163,253,243,85,59,212,95,253,205,255,252,169,194,123,72,61,20,171,68,
81,97,172,33,78,26,8,155,48,91,121,47,232,124,218,231,197,211,223,115,253,221,183,148,133,97,191,123,135,31,253,135,159,227,154,14,171,34,218,157,150,103,98,68,49,195,229,138,241,205,128,139,211,215,188,
251,226,119,216,82,242,248,163,31,113,240,240,14,66,129,115,26,107,253,82,50,205,154,254,1,103,35,210,70,147,188,206,185,62,59,15,254,87,47,165,38,192,252,235,80,117,86,74,19,94,154,88,103,57,56,190,195,
102,181,226,237,203,111,89,77,102,28,222,185,71,163,217,38,138,29,249,122,67,85,254,240,70,150,18,63,163,20,62,39,43,66,4,212,40,113,187,48,21,66,96,77,226,65,101,2,148,51,76,183,27,70,151,23,20,235,25,
23,167,111,121,247,229,239,89,141,199,180,59,71,252,217,255,248,231,36,173,20,99,12,113,210,34,138,83,140,139,153,172,10,206,206,47,216,46,39,60,251,226,183,140,222,190,98,175,183,207,39,191,248,99,92,
234,255,219,58,20,150,226,56,193,184,8,103,125,100,211,68,9,79,159,126,195,234,230,156,172,221,12,47,187,154,170,150,212,33,245,176,147,3,21,101,17,80,179,130,138,26,23,199,28,223,61,98,60,88,240,246,
229,247,40,89,113,239,195,71,254,198,33,241,248,223,34,247,205,90,17,110,55,30,229,232,7,55,210,131,167,148,212,129,100,232,33,79,214,37,184,36,195,165,109,22,155,130,186,22,172,242,57,79,191,248,45,207,
126,253,43,22,179,9,31,125,248,9,143,254,232,167,62,79,28,57,226,44,37,138,51,180,142,89,151,130,235,171,27,54,235,21,103,239,94,114,243,246,123,156,118,220,185,255,136,164,211,10,255,158,26,173,12,198,
198,24,29,249,249,111,148,97,109,131,201,104,192,103,255,252,247,220,189,119,140,137,253,73,173,170,43,234,178,66,41,19,196,20,80,230,53,69,181,165,150,50,72,212,107,106,74,226,52,226,240,222,49,102,83,
115,126,122,198,213,245,13,7,199,119,200,218,29,68,85,144,111,214,20,249,58,72,53,194,105,94,250,168,176,144,50,240,124,124,161,109,215,45,209,214,17,197,45,226,172,139,176,41,243,233,132,203,115,47,196,
62,127,245,132,193,213,37,70,197,124,244,201,143,104,246,58,184,200,211,67,77,148,226,226,148,131,227,187,204,87,27,70,131,17,171,249,148,171,119,207,209,162,164,219,237,160,180,163,150,38,140,87,42,140,
137,253,223,67,42,234,90,209,105,239,211,108,118,185,60,123,195,243,167,95,113,120,124,136,16,69,200,173,135,195,103,88,132,73,105,110,81,1,194,103,13,61,214,66,74,178,86,155,227,7,15,136,74,193,229,187,
183,244,71,125,246,31,61,166,149,54,60,46,60,223,122,38,78,93,133,224,79,104,244,214,59,204,65,25,254,118,149,31,127,9,136,227,20,99,35,90,157,99,210,172,201,124,49,103,50,184,97,220,191,100,124,245,134,
217,100,128,137,18,142,239,222,195,196,73,200,146,199,126,7,226,26,28,220,127,200,182,44,24,77,70,12,250,55,12,206,78,105,196,96,165,96,139,162,172,118,183,117,29,22,187,14,17,12,123,173,246,62,89,218,
96,120,241,158,23,223,61,163,217,110,160,255,192,71,192,78,152,18,254,158,85,248,124,197,142,33,47,36,38,113,236,221,61,68,109,240,187,177,209,128,236,240,128,246,222,30,178,170,110,105,179,183,168,24,
239,220,162,202,183,193,97,205,173,221,202,127,254,254,213,104,108,66,148,53,233,236,31,83,109,114,86,203,37,121,185,97,53,237,115,115,250,154,233,240,6,157,52,232,30,222,195,25,131,141,98,108,156,96,
173,239,114,28,28,250,240,201,104,60,97,216,191,38,95,143,17,197,130,245,58,71,71,254,165,89,11,129,81,14,229,162,112,136,142,177,73,134,250,235,255,233,127,249,116,183,221,246,240,186,2,103,52,73,218,
194,197,41,107,74,150,243,49,243,241,21,103,175,95,114,254,244,9,155,197,150,78,235,128,31,255,233,47,72,187,41,206,58,226,216,163,94,165,137,24,46,215,140,174,174,152,79,175,249,246,215,255,66,62,157,
112,184,127,143,15,126,246,49,42,246,114,105,235,60,25,47,138,50,31,85,140,51,76,148,48,95,205,120,242,219,95,19,219,4,105,181,255,144,110,183,234,97,73,86,137,16,231,244,115,125,65,141,208,130,238,254,
62,155,245,134,23,207,158,99,169,248,228,103,63,65,104,231,117,230,197,134,162,220,6,50,157,64,104,17,26,155,190,165,168,149,194,183,212,127,224,114,199,137,7,161,73,169,88,21,37,195,126,159,237,114,76,
255,250,138,183,79,191,102,58,232,211,105,238,241,199,127,254,31,105,29,118,49,46,38,74,50,255,7,114,17,179,77,197,213,229,53,197,106,206,187,23,223,114,249,234,91,18,151,240,147,159,255,59,26,123,61,
76,100,253,98,54,74,72,27,45,172,139,60,27,61,74,217,34,120,242,245,23,92,125,255,45,199,15,239,131,86,1,165,92,221,222,110,68,200,194,123,186,100,17,118,21,202,115,238,43,95,52,218,63,62,34,139,45,151,
239,222,48,159,78,57,126,248,33,206,197,84,229,134,50,223,4,203,89,136,139,33,168,229,14,10,231,191,156,236,102,158,117,237,181,120,73,19,227,26,172,139,138,124,187,101,182,154,240,205,239,126,197,229,
243,39,108,151,115,238,222,255,128,79,126,241,51,80,154,36,73,72,178,38,38,138,137,147,38,243,77,201,232,102,128,40,183,204,71,87,156,62,127,130,168,225,222,189,135,180,142,142,188,80,69,42,172,54,62,
106,102,252,158,32,202,218,32,13,147,225,21,95,255,230,87,236,181,91,196,205,22,66,249,17,69,89,132,107,249,142,79,36,4,219,109,65,17,156,176,130,42,208,88,67,62,219,90,246,14,123,184,40,230,253,203,183,
12,6,67,186,71,71,180,219,45,170,98,197,118,237,153,73,181,240,255,31,81,9,47,99,175,253,192,72,107,95,225,175,234,18,41,52,214,102,68,105,27,105,19,86,235,13,227,193,53,23,39,111,24,95,189,103,50,188,
65,153,152,79,126,252,99,26,221,118,192,254,250,229,172,49,17,141,118,199,35,22,138,130,50,95,51,58,123,205,102,49,243,76,127,19,83,6,26,169,168,65,59,27,248,233,154,52,109,115,120,116,140,113,49,163,
235,51,158,125,241,57,157,189,46,218,236,194,14,30,112,166,118,73,25,237,168,165,160,42,182,183,69,38,159,196,249,1,163,171,172,33,235,182,105,198,150,235,247,239,185,57,191,226,232,209,35,146,216,81,
5,128,156,31,215,212,136,219,9,241,78,118,238,31,190,82,234,16,3,245,113,236,172,209,35,110,182,216,110,183,12,111,110,232,247,207,25,93,190,103,62,27,67,45,185,247,240,17,73,150,33,132,32,138,210,240,
27,106,177,127,247,62,203,245,138,217,104,194,98,62,99,114,125,134,83,57,113,164,89,109,74,202,218,219,239,140,209,225,198,99,81,202,16,199,77,122,189,3,148,84,140,251,231,124,255,244,247,52,246,59,152,
157,128,165,218,5,65,212,237,244,64,212,126,95,88,221,142,118,9,218,68,188,6,116,175,75,51,107,50,56,191,224,234,226,154,222,131,123,190,179,144,123,129,144,247,53,87,183,40,97,47,129,210,228,219,53,87,
151,125,223,251,8,135,85,99,99,226,70,135,70,107,15,132,98,187,89,51,26,92,115,125,242,154,179,183,223,49,30,220,16,183,122,28,221,255,0,167,77,248,205,165,88,27,209,235,29,209,233,180,89,207,166,12,250,
99,198,163,33,203,233,21,78,22,44,103,27,68,28,7,1,186,159,216,184,216,147,133,173,77,72,27,29,180,142,80,127,249,183,127,243,169,20,65,188,189,93,163,168,137,211,54,113,214,98,75,205,124,50,98,54,29,
112,250,250,91,46,158,62,99,57,94,18,199,7,252,201,127,247,103,52,143,219,40,109,104,180,90,184,52,67,216,132,209,114,77,255,236,146,98,51,226,251,47,127,199,236,226,138,196,180,249,209,191,255,5,105,
175,137,117,126,25,19,89,71,214,104,19,199,25,46,78,41,133,97,178,24,243,217,223,255,87,218,113,70,186,215,198,40,129,214,34,148,27,125,92,78,72,69,133,119,219,10,42,98,107,253,214,187,22,104,233,101,
204,145,179,60,249,242,11,68,94,243,240,241,35,164,139,216,228,107,47,116,240,199,117,170,90,222,98,158,229,14,120,37,118,57,15,159,157,77,147,54,181,16,172,171,154,225,96,64,145,47,57,127,247,138,211,
111,191,97,50,232,211,74,58,252,233,127,255,31,233,222,61,198,70,17,46,242,133,42,109,35,70,139,45,55,87,3,170,237,146,209,205,25,175,190,249,2,138,146,143,63,249,9,247,62,126,132,137,52,137,181,196,73,
236,27,127,54,242,15,98,101,88,229,5,95,255,254,183,156,125,253,37,143,63,254,8,155,37,183,134,48,129,194,104,21,218,117,137,79,171,20,27,63,112,216,73,31,106,188,92,70,120,223,107,247,248,144,86,179,
197,233,203,151,244,251,55,220,121,248,1,81,28,179,94,47,169,139,252,22,225,176,222,228,108,183,165,47,14,9,63,196,240,57,98,255,223,138,227,38,46,109,83,212,146,213,124,193,114,53,225,217,23,191,230,
228,219,175,216,44,150,124,248,240,49,31,255,252,103,36,173,22,85,94,146,181,59,68,113,70,28,55,24,45,182,140,110,250,72,81,209,191,124,199,249,139,167,172,87,115,122,189,67,142,62,252,16,161,21,214,88,
226,56,34,73,19,108,20,145,36,25,113,179,197,116,177,230,242,226,130,47,127,253,247,88,106,14,30,126,232,169,132,165,23,87,215,114,119,130,181,193,9,43,216,108,243,48,79,230,246,225,38,106,255,99,44,11,
47,168,105,118,58,28,29,29,179,25,141,120,243,226,45,135,143,63,198,105,201,108,54,14,174,97,225,19,56,117,233,121,46,202,81,151,57,82,239,198,22,26,231,50,92,210,34,106,116,152,173,87,92,95,188,167,127,
241,142,235,211,87,148,185,87,60,62,254,232,99,207,103,9,251,8,23,165,88,151,208,217,63,102,58,95,82,20,5,249,118,193,232,253,43,166,55,39,8,103,177,58,162,40,125,42,166,174,241,66,16,27,33,133,162,215,
59,228,224,248,14,37,240,242,251,103,124,247,205,231,52,59,29,92,26,133,209,220,174,236,27,118,94,42,16,110,203,128,148,8,124,23,81,215,84,82,248,56,41,32,234,2,169,37,105,187,73,214,232,80,142,199,92,
93,220,176,255,225,7,152,26,79,142,173,131,165,42,220,10,235,186,186,77,172,84,53,68,113,76,153,23,184,56,197,37,77,90,251,71,84,181,96,112,115,197,197,233,27,174,78,94,49,25,79,168,43,197,221,135,15,
177,177,245,116,79,227,63,151,36,238,176,183,127,204,98,189,102,189,88,146,175,151,140,174,79,144,249,18,19,41,214,155,146,220,91,190,145,66,146,37,13,207,239,81,150,102,231,128,238,254,1,235,205,154,
225,224,154,211,23,95,99,162,4,23,187,31,32,106,62,14,224,227,153,218,227,14,202,42,15,190,109,127,179,245,124,254,93,135,193,23,13,179,189,54,141,70,151,124,188,98,120,117,65,231,254,61,82,163,200,55,
75,138,170,12,141,127,25,194,16,30,232,120,125,221,103,54,95,210,233,181,80,194,79,42,226,180,67,163,183,143,117,9,117,145,51,184,60,227,242,244,45,87,111,95,112,126,118,74,171,119,196,131,199,31,97,141,
241,146,147,56,198,68,25,157,189,67,218,237,54,179,201,140,225,100,198,116,220,103,118,115,66,98,107,86,171,21,149,139,65,250,23,173,118,17,38,74,124,41,203,121,133,105,93,121,162,167,250,229,223,254,
237,167,162,246,203,81,37,42,34,155,146,180,58,148,70,50,184,190,98,62,185,224,205,119,79,56,127,250,29,235,233,140,70,118,135,159,253,135,63,229,224,209,29,92,108,73,178,14,46,73,209,46,229,102,190,96,
124,115,67,177,26,243,230,249,87,244,95,189,33,50,9,31,253,244,143,56,126,116,23,29,91,98,151,144,36,25,141,102,219,39,1,76,196,116,83,112,125,117,206,191,252,215,255,147,148,136,163,143,62,68,107,129,
150,181,199,74,7,70,209,0,0,32,0,73,68,65,84,220,86,21,86,27,108,48,60,133,59,24,85,94,161,118,25,254,208,74,149,10,58,251,61,142,143,239,242,250,197,75,6,103,151,124,240,163,143,145,218,48,159,78,111,
213,133,74,234,219,88,149,12,202,56,229,163,73,84,85,237,5,38,54,98,153,87,44,230,115,86,179,107,78,223,191,225,228,171,207,89,254,255,76,189,87,147,92,215,153,174,249,44,183,109,186,202,242,14,30,32,
9,128,36,72,137,212,105,233,168,231,76,204,196,252,219,185,152,62,19,19,221,45,215,148,40,209,3,36,188,45,20,80,46,43,189,119,219,172,185,88,27,208,185,99,32,2,1,2,149,185,247,90,223,247,190,207,51,232,
81,43,173,242,235,223,255,158,104,99,13,229,185,25,174,31,69,104,47,162,59,154,185,147,44,150,206,217,1,111,159,62,100,54,26,112,97,239,18,183,126,245,57,97,28,226,105,77,185,82,117,248,222,66,89,54,207,
5,111,78,206,120,122,239,39,142,126,185,203,229,171,87,168,239,110,162,141,70,23,11,37,163,149,243,158,250,33,90,187,40,90,154,185,147,44,239,138,106,133,70,45,47,216,56,182,16,80,111,95,186,192,168,221,
230,237,171,67,182,46,93,32,89,46,201,211,164,48,174,187,5,176,251,50,24,164,200,11,152,159,123,80,122,126,76,84,170,147,98,152,76,167,44,146,57,247,191,251,7,199,143,127,33,91,100,92,190,124,131,107,
159,221,38,138,3,124,223,80,174,173,184,68,78,188,194,104,182,164,223,110,35,100,74,191,117,66,235,229,67,250,189,30,107,171,219,92,190,126,21,175,28,225,41,67,92,174,226,251,14,29,28,70,21,100,80,162,
209,110,243,252,241,3,94,63,252,145,64,89,118,46,94,70,122,166,96,238,23,35,63,165,221,8,200,248,136,130,181,50,159,77,201,178,148,60,183,36,73,82,44,230,156,126,208,230,142,143,175,180,196,196,62,235,
123,187,132,210,242,250,233,1,97,181,196,114,62,117,108,251,130,126,41,77,161,167,203,45,218,184,81,151,131,248,5,4,113,149,176,188,194,104,58,231,188,113,194,209,243,7,52,223,190,98,58,158,17,6,49,187,
23,46,83,93,95,117,41,35,223,115,191,199,175,16,175,172,209,234,15,177,121,74,182,152,48,106,188,161,119,118,64,162,37,81,84,33,195,81,14,149,84,4,126,224,90,148,126,204,214,246,62,235,219,27,12,7,61,
30,220,187,75,231,228,53,97,24,18,84,171,197,14,210,153,141,132,117,59,47,45,117,17,47,118,141,206,197,114,81,160,49,236,123,14,146,128,66,76,84,236,182,132,196,4,17,171,59,155,164,147,33,205,194,36,151,
44,166,110,105,155,165,239,113,0,89,158,163,148,87,224,64,100,177,208,54,4,165,117,170,107,91,216,60,103,52,108,113,124,240,148,179,215,207,24,116,219,68,113,153,189,139,23,9,75,161,195,181,104,151,98,
243,195,18,235,219,123,12,199,19,150,179,25,233,98,74,191,117,76,50,106,131,150,164,137,192,42,141,204,221,159,29,134,49,97,41,198,40,195,214,238,101,42,43,21,198,227,17,7,47,158,49,27,156,3,57,94,169,
82,168,151,242,247,216,113,41,21,218,4,88,109,144,72,7,211,203,146,247,221,134,220,185,215,139,17,234,63,15,128,165,106,141,181,189,45,146,225,152,230,201,9,229,205,13,210,229,220,45,112,139,197,111,158,
23,73,32,44,179,241,20,163,12,81,201,89,239,162,218,42,229,218,26,113,92,37,203,114,186,205,83,94,191,120,76,187,121,200,114,54,97,99,231,2,23,175,92,37,240,180,43,107,6,17,198,11,217,216,218,35,142,75,
12,135,67,70,163,17,195,110,155,97,235,16,223,179,204,230,11,48,17,86,10,180,241,138,98,108,224,186,63,229,42,27,235,27,100,203,132,126,191,199,225,147,7,104,91,196,182,180,181,24,223,35,170,84,49,97,
196,96,54,100,50,108,243,246,197,19,154,47,158,179,28,205,49,106,133,219,255,237,11,54,46,110,33,53,72,225,97,188,16,116,72,127,182,96,210,237,162,237,146,211,211,151,180,94,188,36,75,44,123,87,46,115,
233,195,43,68,165,144,76,10,2,223,33,126,181,231,179,20,154,238,120,198,209,225,43,158,124,247,87,150,237,49,123,255,250,41,70,43,140,113,141,56,155,89,164,86,4,97,140,212,138,249,98,233,230,201,74,226,
5,198,105,239,178,119,31,190,12,173,37,169,213,68,245,58,183,190,188,195,233,171,35,190,253,247,63,114,231,127,252,22,19,134,164,201,162,72,6,73,210,220,34,114,141,146,238,106,151,230,174,62,109,180,143,
231,249,228,82,49,155,142,201,22,67,142,14,94,114,244,236,17,203,233,152,56,92,225,179,223,254,142,104,115,3,107,193,83,174,237,166,165,199,112,158,48,236,142,64,88,198,131,14,103,47,159,50,238,118,217,
168,174,113,243,147,143,41,215,74,14,67,224,135,152,32,112,95,57,29,208,159,39,28,190,121,195,131,111,254,206,236,248,13,23,118,246,89,221,221,46,216,233,5,103,29,223,85,250,117,232,152,37,184,219,137,
40,168,123,54,253,39,95,63,75,220,41,206,22,16,167,119,31,230,75,55,175,50,106,245,120,254,195,61,234,123,27,24,173,156,80,93,100,24,93,168,4,133,19,57,144,187,172,185,241,35,194,184,70,174,125,250,221,
33,73,50,231,254,79,238,100,191,156,78,185,116,249,58,31,222,185,5,69,92,210,243,163,98,238,88,101,48,153,49,236,246,16,100,116,26,71,116,15,159,49,232,117,241,76,204,254,197,203,120,113,136,167,92,64,
96,177,76,208,218,195,143,42,36,66,51,104,117,56,121,115,200,249,193,19,124,149,179,185,117,21,47,242,144,194,98,11,101,160,150,166,72,93,24,242,92,98,19,192,42,44,206,208,68,241,210,114,139,91,77,158,
45,138,95,203,73,23,174,48,100,133,79,105,115,29,229,141,105,190,57,38,46,249,24,5,66,59,121,116,150,56,171,155,80,57,66,154,194,60,37,8,194,50,81,169,78,111,184,96,58,238,115,244,236,33,131,198,27,166,
179,41,165,168,202,238,222,30,113,53,70,43,225,226,133,129,107,222,198,181,58,231,237,30,203,229,28,155,205,25,54,142,25,55,15,233,79,151,172,172,174,162,164,71,154,187,191,91,16,184,107,185,49,33,23,
47,95,195,47,199,156,119,219,52,142,142,24,119,91,84,43,14,34,182,88,44,240,141,231,90,195,121,94,20,174,84,177,236,5,41,61,162,56,98,185,156,146,229,41,14,40,94,80,44,149,130,220,181,214,108,58,119,8,
4,13,243,36,167,186,187,137,157,204,232,158,156,17,87,34,132,77,65,186,57,119,150,190,187,233,216,226,132,236,138,72,158,9,156,24,94,43,150,163,17,135,207,158,112,250,246,57,147,65,135,82,80,99,255,226,
46,210,115,115,127,207,56,164,70,16,149,89,219,222,97,60,158,176,88,44,201,243,5,163,238,57,147,214,91,82,37,240,148,194,143,66,7,239,243,60,140,54,248,198,32,81,108,238,238,83,46,71,12,199,35,58,237,
54,97,32,81,158,199,120,10,144,190,119,194,190,243,35,27,227,33,181,34,23,14,177,45,149,135,181,115,247,239,145,217,247,251,143,119,55,36,164,68,100,0,9,153,205,168,95,217,35,29,140,56,125,113,64,165,
30,21,46,221,98,116,86,136,94,144,146,245,141,213,247,44,126,223,143,8,162,26,65,88,34,73,150,12,59,109,142,95,191,162,223,61,101,57,157,80,95,219,118,165,71,223,115,228,217,192,137,164,170,43,27,68,81,
204,112,48,102,50,158,50,232,52,25,52,142,9,116,206,116,178,64,248,78,224,36,132,196,243,125,39,94,210,46,33,184,177,181,197,108,48,98,178,88,208,111,158,49,233,55,209,89,154,97,242,12,227,251,68,113,
21,47,174,48,155,13,25,181,143,57,120,241,136,198,211,151,164,147,132,122,109,143,143,127,243,5,149,189,58,202,19,24,47,38,8,74,40,223,103,52,157,209,239,246,16,217,132,147,183,47,56,188,255,11,233,60,
101,103,243,50,215,238,220,166,84,117,52,73,29,248,8,105,80,126,192,210,74,222,52,154,188,62,120,206,131,175,254,68,144,11,238,124,254,5,149,181,42,130,20,163,117,193,181,118,118,118,227,133,238,218,110,
60,150,233,2,147,186,153,170,0,132,150,14,204,100,37,105,98,49,6,148,175,201,180,207,245,207,110,50,238,244,120,248,253,15,108,237,111,227,123,238,135,157,166,22,97,37,82,90,151,39,200,242,162,146,14,
218,15,240,162,50,179,52,103,50,232,242,242,201,93,142,30,62,98,185,152,179,179,186,203,157,127,249,13,222,90,5,155,167,238,198,82,170,160,140,207,40,201,105,159,182,208,50,103,216,57,229,232,233,125,
90,39,167,148,163,42,95,254,254,119,84,182,87,29,101,51,8,209,126,64,142,34,149,134,110,111,68,179,209,224,241,221,239,152,157,31,17,87,98,174,222,185,133,95,9,209,170,96,96,72,237,176,167,133,143,0,101,
222,95,165,197,124,90,36,101,20,136,12,50,208,74,147,75,39,1,145,133,24,154,60,39,69,16,173,174,224,41,67,158,37,44,210,12,41,18,114,84,209,80,117,204,28,1,36,75,167,183,244,131,152,76,250,116,123,35,
38,211,1,191,124,243,55,154,47,158,34,129,219,159,124,194,213,79,62,114,153,80,139,75,31,68,85,252,176,196,36,181,180,27,77,12,75,218,141,55,180,15,158,211,108,157,19,68,53,110,220,188,77,84,143,93,188,
208,15,10,182,144,71,16,151,24,205,19,58,189,14,131,78,147,147,151,247,33,159,82,94,217,167,180,186,234,246,54,100,228,86,35,181,247,94,226,226,170,242,30,126,16,208,104,157,51,31,77,9,60,87,116,113,183,
66,55,194,83,66,50,95,44,139,27,145,45,70,55,238,239,239,69,6,109,65,136,204,9,62,82,183,236,21,184,190,130,86,178,208,224,21,169,156,160,68,127,186,96,177,156,241,234,241,93,250,103,111,200,51,203,197,
221,235,212,119,54,72,210,212,1,171,116,128,242,2,140,41,81,89,217,224,244,172,205,120,54,65,139,37,203,238,25,147,198,107,134,139,37,81,92,193,15,42,228,82,224,121,134,208,15,65,106,130,160,194,254,181,
235,36,210,210,60,57,230,248,237,107,210,97,143,237,237,85,150,105,234,236,73,64,150,38,88,20,198,215,120,50,112,49,102,171,240,131,50,229,234,10,71,111,94,146,36,75,148,116,174,131,127,202,118,36,214,
166,110,41,91,228,145,140,167,223,239,184,132,31,0,48,95,140,241,148,231,10,68,46,178,227,240,27,69,79,36,35,39,136,170,148,106,155,120,58,64,166,25,7,79,238,210,120,253,8,145,38,172,111,110,179,185,187,
253,142,104,95,104,30,203,24,191,196,250,246,5,150,203,132,201,112,204,124,49,101,57,235,211,59,126,198,120,54,36,46,175,19,4,145,27,253,40,141,31,134,14,243,18,86,216,185,116,21,165,4,103,141,115,206,
26,167,72,22,68,190,100,216,91,56,105,188,117,123,5,89,140,112,60,19,33,85,177,43,242,98,42,113,204,249,217,91,103,107,203,11,172,50,133,172,133,162,40,101,173,251,94,89,103,232,35,203,241,86,171,144,
75,242,116,233,220,187,194,177,113,50,251,14,208,34,144,218,39,207,150,104,47,38,40,213,136,194,18,195,222,0,100,206,193,211,159,57,63,62,32,203,151,108,239,94,164,190,185,233,14,175,164,40,47,198,243,
34,170,181,117,202,149,21,122,157,1,211,233,132,97,247,156,81,231,20,210,1,227,44,71,135,117,180,231,136,164,129,31,225,123,33,90,7,172,111,108,81,93,169,49,233,15,104,52,59,116,186,231,244,207,14,48,
129,70,11,225,252,141,198,243,241,130,50,139,100,78,179,117,194,235,167,247,57,123,252,12,82,73,173,190,207,71,95,220,33,222,114,46,85,169,124,252,160,140,242,125,38,73,194,168,211,69,88,23,83,124,251,
240,17,201,212,82,173,238,242,193,231,119,240,194,0,173,156,235,86,26,13,218,103,154,100,180,58,61,142,143,14,121,253,203,247,132,185,101,111,239,50,219,23,182,138,37,173,42,24,41,154,208,139,156,8,92,
27,199,221,200,103,228,105,241,131,209,186,136,13,102,100,54,199,72,64,106,148,114,167,90,103,3,18,84,86,107,4,139,196,205,214,114,139,205,221,21,44,131,130,122,104,49,198,49,124,140,118,183,156,69,110,
25,14,123,188,120,250,11,173,23,207,176,185,101,99,125,135,95,253,235,239,16,81,136,180,197,205,163,20,161,60,159,165,85,180,206,79,144,217,156,97,191,203,233,171,71,180,142,143,240,84,192,167,95,252,
154,234,206,26,82,43,180,239,174,91,82,107,166,75,65,187,211,167,217,56,163,113,114,196,248,244,4,95,72,174,221,248,0,191,28,185,5,181,40,52,103,94,136,52,142,29,46,164,36,23,134,193,112,64,243,232,152,
40,54,239,201,123,88,183,231,200,180,19,76,128,123,25,42,33,177,10,52,26,107,115,146,220,130,85,72,235,210,61,66,230,133,28,6,146,44,71,147,131,213,24,175,76,16,87,233,140,103,12,135,3,126,250,219,31,
233,157,28,225,41,159,79,239,220,102,245,226,182,203,103,167,130,176,20,16,196,101,180,142,152,45,115,90,173,14,129,17,12,123,61,58,71,47,105,156,159,33,85,192,165,171,55,40,175,186,5,163,54,62,158,23,
22,5,191,50,157,241,132,65,183,199,112,52,228,232,229,99,196,114,70,28,85,168,172,173,145,147,189,47,128,105,229,246,19,82,106,132,212,120,58,196,132,33,175,95,189,164,215,58,161,190,90,115,238,99,237,
92,169,34,79,73,151,69,219,209,138,34,138,235,78,184,89,81,11,205,138,56,93,158,91,7,145,179,162,24,122,100,88,105,221,28,52,207,80,210,224,7,37,114,233,177,152,205,121,122,239,91,134,205,35,66,47,96,
101,117,157,189,171,87,89,36,75,84,178,64,74,141,54,30,233,18,86,86,87,152,204,23,228,203,37,42,93,50,233,188,101,214,57,161,51,30,19,68,85,226,114,21,109,28,100,207,4,30,130,127,62,236,151,89,74,243,
188,69,175,221,100,212,62,103,125,37,114,208,191,204,146,22,14,9,169,156,234,80,10,15,171,36,74,5,84,87,214,40,213,42,28,190,120,66,191,211,34,46,5,216,172,200,200,75,222,51,234,243,34,85,34,181,33,77,
150,5,36,79,253,211,15,155,231,104,161,255,151,216,101,129,50,151,146,100,57,115,105,25,175,68,92,169,83,170,174,32,181,228,213,147,123,188,125,253,12,1,212,87,183,169,172,213,92,47,34,167,200,200,199,
104,47,100,125,107,159,101,146,51,232,15,88,166,51,150,227,54,157,183,79,25,77,134,4,81,157,74,173,94,36,183,60,87,244,83,62,113,121,133,245,237,93,82,155,113,126,214,162,117,214,100,54,233,179,94,11,
232,54,186,72,223,20,225,6,23,25,213,90,163,140,135,84,10,163,124,252,82,141,32,140,56,62,120,204,120,50,196,243,52,90,22,73,155,226,247,216,127,214,150,138,241,232,59,132,123,254,142,121,86,188,44,115,
114,43,11,255,176,131,7,101,54,47,146,58,146,32,44,19,87,215,48,202,80,41,69,60,188,247,13,157,243,35,176,150,173,237,139,84,87,87,221,152,16,208,158,27,239,70,149,58,113,101,133,193,96,204,112,216,99,
58,232,48,233,156,144,140,187,36,88,188,168,130,9,60,23,241,52,33,42,8,80,38,164,190,190,69,169,82,102,54,154,208,106,117,232,182,26,204,135,109,178,44,37,94,169,161,125,1,158,241,8,162,42,137,132,222,
160,201,163,95,126,164,249,252,25,249,92,177,185,177,207,141,59,31,81,222,170,226,25,215,200,13,195,50,126,24,179,200,51,6,173,54,89,50,166,113,126,200,139,159,190,39,25,47,136,188,117,62,254,252,14,155,
151,182,208,202,161,14,116,224,131,242,232,142,231,116,218,93,70,163,1,175,238,125,203,228,172,201,90,125,155,235,31,127,136,23,155,194,16,228,154,149,8,199,137,144,70,163,188,144,193,108,206,155,87,135,
148,61,137,48,46,171,237,132,214,69,148,80,73,44,218,137,213,73,11,202,163,187,126,42,207,96,149,44,220,154,153,187,208,102,22,171,5,228,105,209,65,80,132,113,21,225,5,204,134,35,30,222,253,134,198,131,
95,80,8,174,236,95,229,226,199,31,33,226,24,163,157,28,57,46,85,241,188,128,68,106,26,103,13,88,204,153,77,58,156,190,120,196,241,193,1,249,76,240,47,255,231,111,216,185,126,145,36,179,196,133,136,216,
10,197,60,147,156,53,187,244,90,45,122,131,38,111,31,255,12,179,25,123,55,62,100,227,194,14,74,186,196,137,86,110,219,238,249,81,209,28,52,228,82,211,108,182,120,244,205,55,92,188,178,143,49,138,36,75,
73,147,28,163,5,162,152,193,91,155,162,165,117,196,209,130,4,42,115,87,40,202,115,55,231,87,242,157,60,189,248,0,139,28,105,133,51,26,233,136,168,92,103,105,53,167,205,35,126,249,219,159,152,181,206,216,
92,219,224,198,173,15,136,215,86,138,114,15,24,237,22,152,198,139,72,165,230,252,164,193,98,58,162,211,61,163,251,246,9,103,39,199,88,124,174,94,255,128,234,214,58,82,43,132,240,72,19,80,38,64,5,37,218,
131,49,227,65,31,178,37,173,183,47,201,167,125,74,229,10,59,187,23,209,161,239,10,149,82,17,133,78,228,44,149,139,241,249,81,5,161,61,94,61,127,200,203,135,63,115,225,242,126,129,131,118,195,88,167,67,
4,132,118,139,199,204,193,214,132,144,197,127,187,69,119,94,24,142,164,187,67,144,227,208,193,121,154,224,225,147,73,75,150,9,194,160,76,169,182,206,121,171,205,189,159,254,65,255,232,53,107,171,53,214,
87,55,88,191,120,9,165,53,121,65,15,115,221,142,128,90,117,141,217,50,99,58,29,35,77,202,232,232,13,163,147,151,52,199,99,162,234,26,149,149,85,199,25,50,174,247,161,149,71,169,92,103,243,226,69,134,243,
25,243,225,144,94,187,65,247,228,152,56,54,164,89,198,50,179,142,199,95,80,24,181,118,73,21,80,120,38,100,115,231,18,65,28,242,228,231,111,56,61,122,67,109,109,141,52,205,80,10,100,46,176,153,120,223,
73,113,72,100,215,201,144,66,190,135,192,217,244,29,150,91,96,165,70,200,226,21,32,112,75,112,235,218,187,82,251,132,97,149,114,117,3,200,248,241,111,255,201,219,87,207,169,4,33,171,219,123,196,213,138,
99,226,103,22,169,5,94,16,99,188,18,235,91,251,8,163,233,158,55,89,76,251,76,218,103,12,78,158,211,27,143,137,107,107,212,183,183,112,56,45,141,23,198,40,237,83,174,174,177,181,123,145,217,124,74,251,
164,65,183,219,100,212,109,177,187,183,73,186,152,161,60,67,102,243,226,36,239,225,123,78,193,168,77,132,241,35,162,82,29,173,53,47,31,125,79,187,211,161,182,82,65,144,145,166,142,199,245,78,96,35,10,
43,159,181,142,62,107,11,159,178,209,186,56,48,232,34,68,146,187,242,162,203,3,98,83,135,62,206,115,141,9,202,68,213,85,106,245,85,198,157,38,79,239,223,117,212,94,163,216,190,116,197,33,220,139,56,181,
244,60,66,191,68,88,94,97,101,99,139,97,167,79,183,219,166,223,111,177,104,159,48,238,156,176,100,73,169,190,67,88,174,98,133,112,56,241,48,196,55,17,107,91,187,148,74,49,163,254,128,225,104,72,187,121,
134,77,103,136,108,65,188,178,226,176,21,90,123,248,65,140,140,124,218,189,38,143,239,255,72,227,201,43,72,61,246,119,174,114,227,87,31,98,202,26,131,197,83,154,176,84,34,140,203,36,74,208,235,245,73,
146,57,39,167,135,28,252,252,19,233,112,78,96,106,124,250,235,47,216,184,188,129,214,174,172,100,130,8,171,12,253,89,194,121,227,156,233,120,204,225,139,135,76,78,79,240,117,200,205,219,183,9,43,161,67,
202,122,6,33,52,65,88,2,229,33,133,38,51,30,163,197,146,7,223,127,75,44,61,252,106,13,41,37,201,210,205,34,149,51,146,144,36,57,90,65,158,107,200,19,172,114,15,61,50,119,245,204,10,70,53,86,32,68,234,
92,163,54,123,31,35,243,189,152,184,180,66,99,208,231,238,183,127,163,241,224,23,98,19,113,233,198,13,118,175,95,34,215,170,200,240,59,78,71,24,151,81,126,72,227,172,137,157,78,153,79,6,28,191,124,74,
227,240,0,157,121,220,250,242,51,182,174,95,64,24,137,150,30,94,232,68,22,163,101,206,89,179,73,50,26,177,152,15,57,120,248,51,249,100,196,246,250,46,187,215,175,97,188,144,220,42,66,47,162,84,138,156,
169,94,107,172,246,152,47,5,135,175,15,121,240,237,215,236,175,175,225,249,210,45,158,177,24,233,144,195,121,158,163,149,41,228,219,22,69,238,138,34,5,141,85,105,72,151,238,154,154,167,255,156,81,22,129,
84,135,144,181,194,49,128,74,101,206,59,29,126,250,211,191,51,111,157,243,225,135,31,113,249,131,171,200,64,145,164,25,198,83,72,4,126,24,227,249,37,172,9,57,111,119,89,76,135,116,207,143,104,31,60,166,
211,109,97,115,205,7,55,111,177,190,191,231,200,142,90,23,139,186,24,25,148,104,117,6,204,39,99,22,201,148,206,241,107,250,141,35,202,149,10,245,213,117,116,24,224,105,69,96,140,203,174,7,17,57,18,227,
133,248,113,5,155,89,14,158,254,204,227,31,191,103,239,242,69,247,192,205,50,148,150,100,105,10,82,191,55,184,89,171,88,218,148,36,77,144,74,187,36,142,117,172,166,220,130,205,210,247,200,90,43,108,241,
101,183,36,89,142,77,50,130,160,68,165,186,134,242,52,135,47,30,208,124,253,148,157,245,45,54,54,215,40,213,215,200,242,140,217,104,202,114,185,68,153,128,184,84,165,84,89,33,247,2,6,237,14,243,105,143,
193,233,43,6,167,175,105,116,122,212,214,183,89,95,95,47,172,77,10,207,115,189,131,106,241,176,107,245,186,76,39,83,210,233,152,193,233,27,108,58,7,91,34,73,157,73,142,188,32,101,6,126,241,18,149,212,
87,183,92,185,203,215,28,60,185,199,219,23,207,168,172,174,144,167,25,74,8,178,119,8,203,226,102,147,187,140,51,89,90,88,169,10,76,66,90,20,145,108,102,201,133,123,185,56,100,121,254,30,183,155,165,75,
247,231,123,33,213,181,13,202,229,136,167,119,191,230,236,197,19,42,113,133,173,189,61,76,228,187,189,82,209,1,8,189,10,65,80,102,101,117,11,19,148,232,116,154,204,71,93,70,231,111,24,156,30,210,159,12,
41,175,110,176,186,230,16,27,72,137,31,148,138,164,84,72,169,182,198,104,48,160,211,237,50,108,55,153,14,26,212,42,62,201,108,196,124,158,146,10,91,24,192,60,124,223,71,43,141,148,30,113,188,66,101,101,
149,212,194,225,195,31,57,59,58,98,117,111,23,37,115,119,162,151,202,141,70,149,42,110,63,178,88,252,231,239,65,142,239,188,179,194,226,36,240,5,238,56,43,186,7,74,72,172,116,29,1,165,61,162,242,26,235,
91,123,176,152,242,243,215,127,165,209,60,161,92,173,178,182,185,78,16,5,100,73,226,94,76,202,21,87,131,184,70,125,125,139,229,100,202,176,215,101,212,105,48,107,31,49,238,156,49,73,22,84,55,182,41,85,
86,220,223,169,224,14,25,63,102,109,123,31,223,211,244,123,125,122,253,46,253,118,131,197,124,128,200,22,88,89,40,67,81,232,192,11,9,74,101,6,179,33,143,238,127,207,219,123,15,80,11,143,75,151,62,224,
250,23,183,208,161,65,216,20,163,149,147,15,148,43,100,218,208,235,118,88,12,251,156,55,223,240,236,222,247,36,157,62,145,191,202,245,143,62,101,243,218,62,129,239,92,140,65,84,70,168,128,222,36,161,209,
108,146,206,70,244,58,167,180,95,62,197,44,5,215,62,188,70,125,127,131,52,19,4,198,213,127,141,113,100,205,204,74,6,179,148,233,100,200,79,223,254,29,53,28,115,225,211,155,24,45,222,211,35,133,54,238,
164,111,52,82,166,164,89,130,20,146,89,154,161,176,69,57,201,17,17,173,16,216,220,73,35,156,95,51,47,26,182,10,133,33,138,107,136,192,231,209,215,119,57,188,123,151,205,74,149,91,159,125,198,218,229,93,
150,105,134,200,18,2,45,240,131,136,32,174,161,130,136,118,183,79,190,156,145,44,199,28,62,252,137,214,217,9,201,52,227,206,175,62,230,250,157,143,80,70,99,148,33,46,85,80,218,103,150,75,142,206,154,36,
227,17,54,95,184,4,79,179,65,189,182,206,205,95,125,194,202,122,5,105,12,90,249,148,202,49,65,28,99,115,137,85,30,189,209,140,126,175,199,189,175,254,64,61,10,88,223,91,39,12,2,39,136,206,45,152,220,17,
19,113,177,185,100,153,97,179,165,187,227,40,16,185,179,103,57,210,95,142,219,85,231,36,217,59,83,82,145,172,206,50,140,23,19,149,107,204,211,140,239,191,254,27,89,111,192,103,159,126,202,238,135,87,80,
90,145,36,75,178,36,195,147,25,81,201,117,54,130,82,133,86,111,66,50,29,211,109,31,211,57,120,76,179,125,14,86,115,251,227,79,216,188,188,143,149,210,137,170,195,144,40,138,80,81,133,86,119,200,114,226,
170,239,157,147,3,154,111,95,128,149,172,212,235,148,107,21,140,150,148,74,1,65,84,117,204,24,29,224,249,17,210,184,189,66,235,228,13,79,126,254,7,245,90,157,168,20,185,93,4,130,60,77,145,86,32,188,130,
140,40,156,22,48,201,50,114,151,194,43,120,40,185,75,228,88,23,167,179,239,111,142,238,180,43,81,228,105,78,42,192,15,107,196,213,50,247,239,126,207,139,95,238,177,189,182,201,250,214,6,202,51,204,39,
35,230,211,25,74,107,108,146,161,3,77,92,174,18,148,171,156,55,154,100,243,17,189,163,87,116,143,95,208,25,142,88,169,111,177,181,181,3,202,9,134,130,48,68,73,73,181,92,103,115,119,159,102,183,67,175,
213,38,75,103,76,219,167,36,211,190,99,90,101,239,102,211,194,1,184,188,208,45,104,133,98,123,239,50,213,213,53,82,114,94,60,248,129,163,23,79,40,85,75,197,13,246,221,2,83,21,188,32,133,210,33,66,56,95,
66,142,43,223,9,153,99,133,194,10,83,156,224,223,205,246,29,150,193,153,154,132,43,182,33,144,202,39,136,87,216,216,222,225,217,47,127,231,254,247,223,177,178,190,73,117,117,21,109,180,123,49,21,29,18,
55,174,88,161,182,182,73,181,86,167,215,235,209,235,54,233,158,188,98,210,120,195,104,58,39,174,213,89,221,218,42,228,239,18,237,135,24,229,225,133,101,170,235,59,204,39,83,70,253,62,147,233,144,65,251,
152,56,246,192,102,76,167,51,178,98,204,36,132,196,247,140,235,215,104,159,245,205,125,226,114,153,249,34,161,119,118,200,241,171,103,14,109,108,151,69,231,66,185,23,93,241,60,112,139,92,11,139,34,122,
42,5,105,230,218,201,86,216,2,27,238,226,226,73,178,116,136,18,41,10,156,187,19,174,248,97,137,149,205,29,164,77,121,248,237,223,104,156,29,178,178,182,202,202,250,6,202,20,135,145,34,42,170,131,16,29,
150,169,109,238,2,48,155,76,25,116,207,233,157,191,97,222,63,103,186,92,82,94,223,166,82,91,117,169,43,47,112,97,138,160,196,206,254,5,124,223,167,223,238,210,106,181,153,78,251,204,122,45,140,204,153,
167,57,38,116,146,115,23,217,140,202,36,210,242,248,254,15,188,253,249,33,161,168,242,233,111,127,197,234,149,93,164,202,145,164,104,79,18,133,37,226,82,29,97,66,6,131,33,163,78,131,211,211,151,60,191,
251,19,203,246,16,67,196,173,223,124,193,206,245,11,84,171,37,194,208,199,143,99,50,225,51,156,44,105,157,183,201,151,35,58,157,51,94,255,252,35,217,116,198,149,107,183,184,241,235,143,208,30,88,107,240,
253,10,94,80,114,37,9,101,24,206,150,52,58,77,238,127,243,87,102,39,29,62,255,239,191,195,120,10,109,68,241,208,118,88,91,43,2,80,138,133,157,185,19,154,204,138,154,183,32,207,18,247,101,176,57,22,119,
162,55,158,129,92,189,207,83,91,4,126,88,66,6,1,79,158,62,228,197,183,223,179,187,185,203,175,127,251,107,194,90,153,212,58,75,149,14,156,223,55,12,34,194,184,74,123,178,96,208,235,50,236,156,112,246,
242,5,221,163,67,72,37,95,254,230,183,92,255,252,22,210,247,208,38,164,84,170,128,241,25,47,45,71,103,39,100,227,25,66,101,28,62,250,153,222,241,1,129,246,248,228,206,109,214,246,54,240,3,39,76,215,126,
132,231,199,32,20,211,76,208,234,244,56,61,124,197,179,31,255,65,72,206,197,235,183,8,3,31,207,40,55,63,212,14,217,234,249,206,237,153,229,150,44,91,22,11,89,247,162,75,18,71,46,180,54,71,21,227,10,132,
196,43,240,190,214,186,95,75,115,73,181,180,74,42,52,127,252,183,127,99,214,108,242,251,255,235,127,199,47,121,160,112,106,64,1,65,224,58,21,81,169,70,88,89,167,55,156,48,234,181,104,157,190,226,248,209,
61,199,186,9,202,92,255,224,38,235,151,118,145,10,151,202,136,171,197,173,178,198,121,187,207,124,60,100,185,156,48,62,59,162,125,240,132,233,98,201,229,43,31,176,181,179,133,212,138,114,185,140,231,135,
136,194,97,26,148,107,204,82,215,126,124,112,247,91,134,231,71,212,87,234,108,236,108,162,157,125,221,209,95,165,68,75,183,220,117,30,218,28,114,183,220,148,66,33,108,138,200,5,89,102,201,211,220,129,
191,112,172,152,36,205,221,146,208,179,142,142,153,186,168,99,101,173,206,221,31,190,231,249,79,223,113,237,218,53,130,82,232,18,63,73,230,176,174,54,33,203,12,158,95,194,215,33,165,218,10,221,193,152,
249,98,204,217,235,199,180,142,94,208,29,78,216,92,223,102,107,111,23,91,140,125,188,192,32,165,199,202,218,22,235,219,251,52,90,45,70,221,54,203,73,135,101,239,140,217,160,13,186,68,16,85,200,0,93,8,
193,195,40,2,169,8,226,42,251,151,174,225,69,1,231,231,103,60,249,229,103,152,181,136,162,16,171,220,11,200,102,130,204,8,236,34,113,100,92,79,21,75,112,156,51,53,73,16,50,119,183,61,33,65,228,104,207,
32,150,89,225,78,117,251,14,249,62,156,227,48,230,190,23,177,186,190,206,131,31,255,234,94,130,23,246,9,203,129,243,181,230,9,74,133,78,79,104,138,66,93,24,19,85,106,140,167,238,161,214,62,120,68,251,
248,37,179,116,193,218,230,69,86,55,234,133,201,75,96,130,0,99,66,202,181,53,214,119,246,105,53,206,25,180,91,206,62,55,108,145,207,7,228,81,157,101,226,58,178,2,137,167,125,180,9,29,116,47,168,178,179,
127,25,169,5,163,209,136,211,195,215,12,154,175,9,171,33,94,232,241,110,158,249,190,144,165,125,23,51,85,194,129,227,242,196,233,80,115,39,36,202,114,119,227,203,133,3,181,229,121,230,180,153,210,129,
25,37,130,204,166,104,237,94,108,129,145,252,244,167,255,201,219,215,111,217,189,114,133,48,46,147,101,83,178,92,22,49,88,89,20,80,203,84,215,183,80,198,48,31,141,104,28,191,166,249,250,49,163,94,131,
204,243,168,175,111,81,94,93,43,56,67,190,195,44,120,33,187,251,23,16,66,210,57,111,211,239,118,152,244,123,140,58,71,132,190,101,190,76,209,81,217,97,162,149,70,185,177,150,207,235,227,3,94,222,125,68,
85,173,113,243,179,143,89,187,178,129,214,14,170,165,141,155,35,151,43,85,188,184,76,111,50,100,50,104,115,124,114,192,193,207,63,147,116,7,120,170,194,141,143,62,102,243,234,62,38,52,104,207,224,199,
37,80,62,195,89,66,175,61,192,230,75,134,163,6,175,238,255,200,188,211,99,165,188,193,165,219,55,209,145,195,142,198,97,153,168,92,66,26,131,85,62,231,163,49,103,141,38,15,190,253,47,250,135,39,220,188,
117,135,202,106,21,237,185,185,179,150,238,165,160,140,70,106,67,146,193,114,153,20,81,61,215,56,117,199,56,103,217,177,82,176,92,58,35,107,150,36,206,95,155,128,103,36,158,52,132,229,10,135,39,71,124,
251,159,127,224,131,139,151,248,240,179,219,120,229,0,43,44,202,129,132,93,86,60,42,19,85,86,152,100,130,97,175,75,175,125,202,219,7,247,232,54,206,80,153,226,206,103,159,115,237,243,91,152,56,114,6,35,
227,35,140,199,210,26,206,155,231,44,135,19,68,182,164,243,230,13,205,195,151,100,105,206,173,79,111,179,115,245,34,158,103,208,38,196,11,67,148,246,176,82,49,90,88,222,30,157,242,244,233,35,206,158,252,
136,151,230,124,242,229,23,84,87,203,4,158,231,30,24,128,214,33,202,51,104,173,201,114,48,70,48,29,23,228,144,220,221,100,180,150,14,234,36,220,204,95,20,140,121,178,28,93,20,80,68,17,121,85,158,225,155,
255,250,138,32,77,248,224,183,95,226,151,52,233,98,134,20,130,197,98,233,40,136,82,19,196,37,194,82,133,121,146,50,236,15,24,118,26,188,186,127,151,197,168,143,111,98,110,126,118,135,234,90,29,41,13,34,
203,9,43,37,130,168,76,80,170,114,218,234,49,25,13,176,201,148,81,227,45,189,99,199,88,95,95,219,102,239,210,62,81,20,160,138,133,191,241,124,172,244,9,162,26,131,89,194,89,227,132,131,39,143,24,28,191,
194,243,67,182,183,183,81,70,57,70,121,241,224,246,77,128,50,190,27,233,8,129,202,115,84,121,133,249,108,70,150,164,164,110,250,234,14,4,242,159,40,230,204,90,55,3,22,2,105,37,34,203,201,211,156,184,28,
243,226,233,19,206,94,61,231,210,245,203,206,0,86,188,56,179,212,186,232,102,49,130,80,38,160,190,179,199,120,182,100,62,29,113,244,226,17,231,7,47,88,36,9,251,219,23,168,174,175,58,177,113,110,241,2,
31,163,125,162,168,198,250,246,62,237,94,159,201,96,192,98,54,98,218,62,99,210,63,39,17,146,114,201,39,77,82,39,178,241,125,180,14,64,106,60,47,230,210,141,155,100,194,114,124,122,196,139,135,143,48,204,
80,65,0,186,216,27,101,25,105,182,68,101,110,103,167,138,133,183,123,226,25,194,114,200,188,119,78,102,45,6,151,231,183,50,195,230,146,52,207,80,66,21,78,88,65,46,50,183,79,65,32,114,139,23,71,188,126,
122,159,211,87,175,216,220,217,65,249,198,1,253,210,4,241,142,120,170,61,140,241,241,253,50,213,106,157,201,200,101,237,79,158,63,164,241,230,57,211,69,194,246,238,62,171,155,155,142,13,37,64,249,238,
198,95,169,110,178,190,179,71,171,213,100,56,232,49,155,13,153,245,78,89,246,59,216,184,76,150,102,133,21,206,141,196,60,63,68,73,77,20,213,216,185,116,21,155,103,52,206,78,104,28,31,145,39,83,114,50,
252,130,111,143,125,215,220,87,24,173,49,218,43,2,35,130,28,183,56,183,89,234,100,41,202,195,230,137,219,89,88,222,135,8,222,169,55,17,14,88,102,113,6,171,114,185,194,47,255,245,7,186,221,14,59,87,46,
129,231,145,230,73,81,140,116,255,242,74,42,188,160,66,92,91,39,242,124,230,147,9,221,198,17,199,207,238,211,111,31,147,73,201,198,218,6,229,74,213,137,87,60,223,149,201,252,152,205,189,75,72,161,233,
182,59,12,7,3,230,211,33,211,206,49,249,98,196,204,26,148,95,122,79,15,48,198,161,204,245,209,249,17,119,208,194,24,100,0,0,32,0,73,68,65,84,255,235,107,118,171,251,124,248,217,135,148,106,126,81,54,176,
104,45,9,125,143,32,40,19,150,87,24,103,25,163,126,139,55,135,143,120,248,237,223,17,195,5,190,170,240,249,175,190,228,226,39,215,16,158,147,157,251,65,132,85,1,195,101,78,171,221,194,46,151,116,59,111,
120,246,211,15,116,143,154,212,75,107,220,254,242,87,148,86,99,4,130,114,169,226,176,178,158,207,18,77,163,215,231,225,163,7,60,255,254,27,210,110,151,235,151,62,224,242,135,151,241,124,65,150,166,200,
204,34,3,28,57,206,11,65,128,135,98,50,207,72,242,126,17,79,211,168,194,245,105,139,31,172,148,14,19,235,28,187,25,190,182,100,25,88,165,56,105,181,248,225,15,127,230,230,149,171,92,188,190,135,246,52,
105,146,19,4,158,227,134,32,240,188,152,114,181,206,82,249,52,27,103,156,31,191,228,201,143,255,96,120,218,36,246,35,190,252,253,255,198,238,245,125,162,74,9,33,28,32,73,251,1,147,84,112,214,236,48,27,
12,32,75,104,28,62,167,121,240,132,201,112,198,205,219,183,249,240,243,91,104,227,246,22,81,169,236,252,193,210,163,51,156,115,240,250,45,111,15,15,56,125,252,19,76,231,92,253,248,19,118,46,238,225,5,
30,82,123,78,152,108,33,42,149,144,202,161,98,179,172,192,25,231,110,60,227,172,63,174,200,230,174,62,25,42,240,89,166,73,81,169,119,246,42,149,41,150,105,66,102,225,217,163,199,212,52,84,63,185,225,82,
65,105,33,254,200,150,248,198,245,35,74,165,10,213,218,26,214,11,232,52,90,28,189,121,202,147,239,190,33,95,204,89,91,221,224,214,39,31,83,170,215,88,230,41,218,104,226,184,76,16,87,136,42,117,218,253,
49,227,126,143,60,153,50,109,29,209,126,243,156,102,187,203,230,206,5,62,188,245,1,229,74,136,49,134,184,84,66,153,8,169,67,114,227,74,109,253,94,139,163,103,143,152,180,222,16,198,17,123,187,23,136,98,
227,176,9,66,32,181,33,87,26,47,42,21,109,97,131,54,17,94,28,113,248,234,9,185,77,11,12,128,34,203,18,4,238,37,151,23,205,214,28,176,178,104,118,131,187,202,91,225,44,68,253,30,107,59,219,8,153,66,182,
132,76,144,147,177,92,166,104,229,60,14,158,23,80,95,219,33,179,138,241,176,207,253,239,255,74,235,237,43,148,80,236,239,93,32,174,213,200,132,112,22,185,192,35,240,99,162,176,198,206,181,171,156,119,
186,244,219,77,178,229,132,105,235,136,101,191,65,127,182,164,94,95,71,41,31,200,240,117,136,209,17,8,65,185,188,198,238,229,75,76,39,99,186,189,54,199,111,94,81,139,65,98,88,204,221,156,46,91,44,29,63,
95,40,148,242,81,198,115,194,32,233,81,46,175,82,173,149,121,251,250,5,214,90,12,210,89,161,164,134,180,152,83,99,223,123,37,68,230,176,203,56,60,12,169,181,116,206,207,152,207,166,212,119,54,10,38,189,
40,136,174,57,185,80,104,44,10,73,224,87,168,172,238,32,252,144,108,208,225,201,79,127,229,244,245,83,200,45,151,175,94,115,6,54,229,97,151,11,148,231,17,248,101,226,242,26,91,123,23,232,15,71,133,233,
174,207,162,115,204,178,119,206,92,24,202,129,231,40,170,66,57,254,189,31,33,149,71,92,173,179,119,241,26,54,79,232,12,59,156,159,188,37,242,44,131,209,0,227,249,136,194,242,7,41,82,104,148,150,4,129,
143,16,30,74,122,4,113,21,165,4,131,65,191,128,198,229,100,50,119,227,183,204,141,109,222,245,29,192,189,248,157,168,7,164,117,47,199,23,247,190,99,185,152,179,178,181,233,252,194,255,43,160,173,16,232,
120,81,25,191,188,66,165,190,134,180,2,230,61,30,125,255,119,250,157,19,164,31,177,181,179,79,92,46,90,180,202,137,97,60,19,178,185,119,133,208,247,105,157,183,232,246,251,76,198,29,38,167,135,100,139,
17,185,150,133,132,71,59,127,112,16,226,121,6,47,240,209,247,255,254,35,59,181,61,174,125,114,5,169,93,238,214,20,146,104,207,40,140,14,40,215,214,72,132,160,219,57,231,240,224,9,143,190,251,14,59,152,
83,42,175,243,209,173,59,92,252,228,50,218,151,78,240,17,87,48,97,137,113,146,211,106,54,72,102,99,134,195,14,207,239,253,72,231,244,20,37,34,174,223,186,205,218,254,6,158,167,8,67,247,80,148,198,103,
137,226,77,179,205,193,235,151,28,254,242,35,243,206,57,171,81,157,235,55,175,19,70,26,155,167,40,44,74,58,62,132,241,124,180,231,129,212,204,83,203,116,62,35,205,50,68,193,238,86,198,109,217,41,168,126,
8,87,39,247,149,227,243,88,225,208,165,147,249,140,215,47,14,185,117,243,6,107,27,53,148,118,2,12,163,37,90,10,114,82,60,29,18,149,171,228,38,224,188,221,227,237,235,103,60,255,254,31,204,58,109,170,113,
149,255,246,251,223,179,126,117,23,207,51,24,229,225,71,49,210,11,153,103,208,104,52,152,14,135,136,116,65,251,237,1,231,111,94,208,233,142,184,122,229,3,110,125,254,57,97,41,198,247,2,252,208,32,141,
38,179,138,243,254,132,243,147,22,231,205,19,206,223,60,35,95,140,217,223,189,200,165,235,23,49,190,70,107,77,142,19,212,24,223,129,163,114,225,162,172,227,36,225,213,227,39,132,114,129,54,5,16,42,119,
231,51,173,116,81,184,145,120,210,165,12,148,46,22,82,56,161,70,150,39,212,106,1,162,94,46,4,22,57,164,197,41,79,186,179,157,9,34,42,229,58,210,47,115,222,25,114,116,240,130,31,191,250,47,124,44,87,47,
92,224,202,135,87,9,43,37,55,198,145,154,56,46,17,149,170,4,113,141,246,96,76,171,117,78,58,31,49,57,63,98,210,60,164,217,233,80,170,172,114,233,250,13,202,213,10,198,120,120,81,228,30,246,38,38,23,30,
205,86,143,201,100,194,217,209,75,134,173,183,144,231,172,111,239,82,93,169,185,247,152,114,157,3,227,135,133,247,211,101,173,131,82,133,220,230,60,252,229,39,178,217,16,207,83,46,165,99,179,162,177,155,
34,180,135,204,115,114,41,80,105,254,174,85,239,150,119,153,112,227,65,32,136,67,119,19,200,192,166,5,115,165,88,242,102,89,142,241,3,74,229,21,194,114,149,110,127,192,221,127,252,137,113,251,140,90,169,
66,109,181,78,84,45,145,230,238,51,44,132,66,155,16,63,168,176,126,225,34,189,241,148,110,187,69,54,27,51,105,190,97,218,57,98,144,228,84,43,171,248,94,228,8,174,218,221,6,148,80,148,107,27,236,94,190,
194,34,79,25,13,70,156,159,188,37,153,14,161,228,145,22,254,8,169,21,162,128,220,105,227,35,141,1,107,8,252,152,181,237,61,226,74,204,131,31,191,97,177,112,202,80,135,217,54,148,86,234,12,123,221,98,39,
230,248,255,185,123,154,97,115,200,10,182,21,185,75,129,121,65,136,181,169,187,11,91,11,197,139,33,183,214,165,184,252,144,168,90,39,44,87,73,151,115,158,220,251,142,227,55,175,136,124,159,245,173,13,
202,181,170,91,142,146,33,61,141,231,199,196,209,10,245,213,13,134,195,17,147,209,24,107,83,22,157,19,230,237,83,6,105,78,185,94,115,159,251,220,162,124,93,176,243,13,181,213,29,214,119,182,153,47,166,
140,250,3,222,190,126,69,186,152,144,207,19,215,95,81,198,141,165,178,220,185,132,3,23,138,144,194,9,90,226,218,58,130,140,231,15,126,34,205,231,238,54,43,44,54,155,187,36,149,80,72,89,44,174,11,119,136,
219,253,100,46,194,73,206,98,58,4,145,225,149,221,104,9,172,19,237,20,81,105,33,20,74,123,4,97,153,90,117,21,146,132,197,114,198,55,127,250,35,189,238,57,65,84,97,117,111,223,217,252,112,135,147,48,140,
137,252,152,141,157,125,162,32,160,223,237,208,239,182,152,12,123,12,207,223,144,76,186,160,180,195,105,107,231,209,208,38,68,40,141,31,150,216,220,189,132,190,122,225,42,171,59,171,32,18,60,233,22,51,
238,126,235,146,20,81,28,131,239,209,238,118,120,241,226,33,63,127,245,13,249,120,193,74,117,151,27,31,127,202,165,219,251,68,177,71,150,102,84,170,85,116,88,102,146,66,179,113,78,58,28,49,156,53,121,
241,203,93,186,199,167,176,48,220,186,243,41,23,111,94,38,8,29,247,196,47,34,118,179,76,208,104,157,115,252,246,144,147,199,247,153,158,158,18,8,159,155,159,124,76,117,179,138,54,150,44,119,215,111,55,
67,119,134,118,148,97,102,5,79,158,62,64,206,167,40,95,144,164,2,82,88,102,153,147,98,8,235,230,108,202,128,178,40,105,41,72,203,46,154,8,108,111,175,23,30,89,231,194,204,115,139,103,20,25,57,70,106,226,
82,149,168,82,229,172,63,230,229,243,39,252,244,151,63,97,22,19,54,86,54,249,213,239,254,133,213,11,187,88,50,162,192,199,15,2,130,40,34,149,62,231,111,207,153,14,6,216,100,70,251,248,128,243,131,39,244,
251,99,54,55,118,248,226,95,127,205,202,70,141,48,140,241,67,87,8,153,47,225,188,55,160,113,214,96,60,26,210,56,120,194,188,117,70,236,133,220,190,115,155,184,18,190,119,97,250,158,179,229,120,65,132,
69,144,89,143,233,34,229,225,221,123,164,189,54,229,139,27,164,121,138,146,210,161,51,148,107,241,89,225,160,95,86,42,199,240,150,154,28,137,179,87,59,56,91,234,182,87,5,42,58,195,4,6,107,45,203,36,193,
51,154,48,174,225,151,170,244,166,51,158,61,250,133,111,255,244,7,98,105,185,249,225,117,174,126,116,29,97,148,211,234,25,135,117,45,173,172,226,5,21,250,179,140,78,179,67,58,29,210,63,126,205,172,113,
200,155,86,155,149,149,85,62,184,249,33,213,122,21,161,60,87,102,211,62,66,185,91,95,171,51,96,208,110,211,27,180,56,61,120,140,81,57,245,149,85,86,215,171,120,129,112,124,28,92,76,83,121,62,153,144,132,
65,149,176,92,39,201,18,238,254,227,43,230,253,62,213,149,10,121,6,202,197,112,220,21,94,10,108,150,32,172,192,83,154,188,112,161,186,64,134,75,129,9,223,157,208,180,241,241,2,205,104,216,39,151,26,242,
165,27,23,105,141,16,26,63,40,81,219,188,64,127,60,224,254,247,127,102,216,60,162,190,82,165,182,82,67,154,0,107,149,163,146,138,12,223,143,241,188,152,141,189,139,12,166,83,186,221,30,217,114,204,240,
252,53,227,179,55,244,22,51,202,181,45,130,168,228,244,163,184,255,95,33,21,171,91,23,88,219,219,99,48,30,211,159,12,56,123,115,192,108,120,78,181,20,32,144,44,151,9,90,90,146,69,82,200,209,53,82,25,180,
212,196,149,58,59,123,151,49,129,226,135,191,254,145,209,104,72,84,14,16,185,37,203,44,66,228,244,219,109,92,207,218,190,71,0,83,176,133,40,98,172,182,72,171,43,225,129,181,69,228,83,34,45,100,239,114,
234,185,69,123,30,58,40,83,174,111,98,147,148,159,190,254,79,142,15,94,80,171,198,108,172,109,96,66,253,30,73,224,107,143,32,138,241,130,50,27,123,151,176,2,38,195,14,139,217,152,254,201,43,198,167,135,
244,22,9,213,213,109,74,165,178,51,88,41,131,95,228,243,87,86,118,88,221,222,102,54,159,211,239,180,57,57,126,195,98,212,166,236,11,102,243,20,227,27,164,117,145,91,161,139,12,187,246,80,210,16,198,107,
148,86,55,32,91,240,227,87,127,70,232,12,169,21,8,215,202,21,133,42,240,29,96,241,159,120,22,151,232,121,151,115,115,28,252,37,66,218,226,115,225,22,5,121,86,88,182,172,69,75,215,40,15,171,235,132,165,
42,179,206,25,63,254,237,79,180,90,111,169,214,106,172,108,109,33,140,113,241,113,165,241,66,151,214,171,173,109,80,89,169,51,238,14,233,181,218,244,219,231,140,154,135,76,250,45,172,54,148,202,37,140,
209,8,41,221,254,67,59,24,221,214,197,107,248,198,71,87,183,87,220,155,58,115,28,104,183,118,80,78,26,236,5,152,176,204,96,60,226,241,131,123,220,253,227,159,97,98,89,91,223,231,203,223,125,73,105,187,
130,176,75,4,33,165,82,9,229,197,44,173,164,221,110,177,156,141,153,37,3,30,223,253,158,209,201,41,118,169,185,118,227,54,215,238,92,39,138,125,130,240,29,104,44,100,146,192,73,163,201,160,219,166,245,
230,5,147,163,3,84,102,185,126,253,26,27,23,55,72,150,75,164,180,152,176,132,231,5,196,113,140,242,66,82,97,104,143,38,60,190,127,15,58,67,182,46,110,177,76,102,40,192,42,183,49,183,153,69,122,18,227,
27,178,196,162,201,93,246,24,39,224,86,10,44,146,90,181,140,146,18,173,44,74,9,178,60,47,82,60,134,40,46,17,85,234,76,50,193,147,199,247,121,240,213,159,241,150,11,46,95,188,198,167,191,249,156,120,173,
134,16,214,81,30,35,23,91,205,148,207,121,103,228,78,73,201,140,214,235,167,180,222,190,224,236,172,203,206,246,5,190,248,253,23,148,86,226,66,206,29,160,60,159,121,42,56,235,140,104,53,90,44,166,99,58,
205,19,38,103,167,132,58,224,147,207,238,80,170,151,64,184,153,161,241,61,130,168,236,78,11,202,99,145,10,70,147,25,119,127,248,142,206,219,215,220,248,232,6,121,17,169,147,158,113,15,242,34,66,166,148,
195,17,144,91,119,130,85,10,105,45,139,101,238,196,200,82,146,102,238,229,231,251,255,180,244,44,151,9,50,203,241,131,18,213,250,42,75,233,113,240,234,9,223,255,229,15,172,6,30,191,250,213,199,108,236,
111,21,110,88,69,158,165,68,165,18,97,185,134,31,85,24,204,114,26,231,13,22,147,62,221,147,87,244,14,159,114,222,29,80,46,87,185,113,227,6,107,155,117,148,146,4,113,9,233,249,8,21,50,203,53,157,70,203,
161,117,7,77,26,175,158,160,178,57,113,105,149,245,173,77,124,207,43,198,109,174,148,163,180,95,68,240,106,232,184,194,114,62,231,135,191,255,137,193,249,9,59,187,123,228,202,101,158,179,44,71,27,81,164,
19,29,122,194,217,206,20,185,146,142,113,147,186,219,145,16,194,197,243,112,217,238,229,60,43,210,46,197,242,50,207,49,202,25,185,246,174,92,39,136,125,126,250,230,15,116,78,14,217,90,223,32,46,151,16,
239,25,80,41,66,138,130,111,94,97,99,247,18,9,146,225,112,76,158,140,233,29,62,101,218,61,103,56,95,186,210,84,217,145,36,149,86,4,58,68,235,144,245,157,75,172,236,110,211,25,13,24,247,122,140,70,93,230,
189,115,194,192,141,241,166,243,89,145,9,151,8,92,67,91,42,141,54,49,59,187,151,168,111,109,145,47,102,124,243,151,127,167,211,60,167,82,171,146,45,147,34,201,228,186,11,73,49,127,47,162,40,228,8,39,67,
17,32,69,1,215,203,93,212,215,226,94,122,80,140,79,197,187,186,146,116,80,188,160,74,109,99,159,192,87,252,244,215,63,113,244,234,5,27,107,171,212,214,170,5,181,210,233,61,17,218,33,57,188,152,141,221,
43,228,66,49,26,12,24,246,59,244,79,95,211,62,124,198,36,77,169,110,236,177,178,82,3,5,202,11,11,41,122,200,250,230,69,106,235,235,12,134,35,250,221,38,103,71,111,89,206,71,84,99,197,98,62,71,41,77,154,
39,100,88,76,224,163,77,228,26,236,166,68,125,109,135,90,125,149,233,100,192,221,191,254,7,203,116,70,20,56,108,130,187,246,192,187,69,207,59,178,176,117,134,23,114,155,22,30,223,34,190,106,29,95,95,40,
237,56,95,74,20,81,112,249,62,218,234,69,17,97,165,198,250,198,22,179,94,139,111,254,240,255,49,24,119,216,220,217,38,46,149,93,111,200,186,177,153,241,35,140,23,177,178,182,73,125,125,147,201,120,74,
171,121,70,243,236,13,157,183,47,153,143,187,88,79,83,169,84,138,114,153,113,61,7,19,80,170,174,178,189,127,25,128,225,96,128,214,214,101,80,145,194,13,248,115,247,134,210,74,19,196,53,166,54,227,201,
227,95,248,249,47,127,197,78,18,118,54,119,249,244,95,190,96,237,98,205,113,90,18,137,214,62,97,92,101,97,37,237,78,151,113,175,67,127,220,226,224,225,207,116,143,79,88,142,83,46,95,249,136,107,159,127,
76,169,90,122,191,101,150,218,99,156,10,142,79,27,204,70,3,186,157,115,206,94,60,101,49,26,113,113,239,3,174,124,124,3,105,36,74,187,183,105,169,84,1,165,16,38,100,154,41,38,179,57,15,238,125,207,219,
123,15,249,245,127,251,146,36,157,83,152,12,10,94,120,238,222,118,54,103,49,79,64,104,124,95,99,124,69,154,22,99,43,79,224,89,119,122,73,243,172,200,52,43,76,230,30,144,72,77,24,151,209,65,76,251,228,
148,123,95,255,141,108,48,229,147,15,111,114,235,215,31,17,84,75,104,163,48,198,160,148,193,11,35,208,1,157,209,156,243,179,38,211,73,159,206,209,43,78,95,61,161,217,236,178,81,219,225,55,191,253,53,155,
123,235,248,126,76,84,170,160,189,144,20,205,89,171,75,175,211,69,102,9,221,94,139,179,231,143,201,23,11,174,126,124,131,237,11,91,228,89,238,70,36,65,136,9,66,71,126,204,13,195,25,76,38,19,30,252,252,
3,47,127,250,145,219,31,223,196,247,13,74,226,226,170,197,98,201,226,154,167,14,54,230,57,33,70,182,116,36,82,227,33,200,73,19,139,84,158,123,9,224,246,138,218,72,172,80,133,131,64,81,42,215,49,97,149,
131,215,71,124,251,199,63,176,91,46,243,249,23,159,178,182,183,66,110,21,139,36,71,2,97,16,81,173,173,161,131,18,227,92,114,214,60,231,228,205,27,146,222,41,211,198,33,199,205,54,113,84,231,246,39,159,
80,91,95,115,183,150,176,132,54,30,82,135,76,150,146,110,167,205,120,208,39,77,231,52,14,159,50,31,247,168,86,42,172,173,109,226,249,1,121,150,227,25,141,31,196,40,19,34,165,71,88,93,197,170,128,249,108,
198,195,31,255,202,201,203,39,92,185,116,213,45,180,201,176,210,181,176,133,11,238,186,209,141,118,126,95,169,4,54,21,197,45,192,25,61,114,155,33,149,34,75,151,144,41,55,6,64,144,23,165,134,44,119,39,
255,114,121,21,47,244,249,241,155,175,104,188,122,206,222,230,134,203,224,203,119,36,86,23,137,12,130,0,207,68,212,86,54,241,74,101,186,221,14,221,214,49,179,230,49,253,198,27,230,137,96,101,125,13,63,
10,177,18,119,248,210,30,38,8,89,223,190,72,117,123,155,225,120,194,124,52,197,46,230,140,155,39,40,177,64,138,144,116,158,145,90,71,3,149,66,18,134,37,231,19,208,49,23,110,220,160,82,171,177,92,44,248,
238,235,255,224,240,217,115,54,246,118,139,200,36,110,156,162,148,179,52,165,153,27,255,0,194,186,19,106,154,57,149,36,188,123,225,185,8,107,150,103,216,34,165,146,91,233,216,76,238,55,162,61,143,168,
188,194,218,250,58,247,254,246,159,188,122,248,128,253,189,29,194,216,119,251,51,249,142,243,228,110,172,198,68,84,234,187,120,65,204,112,56,96,50,238,211,60,120,76,251,248,5,237,254,152,237,221,93,42,
149,216,141,224,148,38,8,220,248,98,117,99,143,234,234,26,131,254,144,86,179,73,167,125,194,116,220,165,82,50,174,145,156,91,172,77,11,54,148,70,104,175,56,5,87,217,190,112,149,48,8,153,205,166,220,255,
250,47,52,207,79,89,191,176,87,64,25,221,207,204,237,243,115,183,172,205,82,135,242,214,110,185,157,100,150,92,20,220,251,98,92,138,144,133,86,181,176,194,20,183,0,41,20,66,107,252,48,166,190,190,141,
93,142,184,247,213,127,48,24,244,217,190,184,79,20,57,17,61,194,125,58,149,103,8,195,50,113,117,133,205,173,93,72,51,70,237,30,205,211,183,52,223,60,99,220,59,71,24,195,202,202,22,97,84,2,229,98,227,158,
31,18,87,214,216,190,124,3,153,65,175,219,161,219,62,71,75,9,190,145,44,19,75,150,190,251,129,74,140,23,35,131,136,215,175,158,240,237,31,255,200,162,59,227,198,181,143,184,243,187,219,120,177,71,146,
46,8,76,72,88,45,81,170,172,32,194,10,189,78,151,65,171,73,191,119,194,211,159,127,100,112,214,36,155,10,246,247,62,228,230,231,31,19,151,3,148,244,137,203,117,84,24,210,159,229,156,54,206,153,247,186,
204,23,35,14,239,223,37,233,142,169,85,54,184,254,233,45,132,175,73,151,130,208,55,196,229,26,218,243,200,165,97,48,135,118,187,197,243,199,119,57,188,251,11,183,63,254,132,76,36,200,212,141,42,50,220,
220,217,224,10,86,74,249,248,202,195,106,215,54,21,50,35,240,220,151,93,90,253,94,239,167,45,120,26,151,111,246,5,203,36,69,43,143,176,84,225,168,213,228,207,255,239,255,67,52,79,249,226,127,252,119,46,
222,186,140,37,115,24,83,207,205,99,227,82,21,47,42,211,154,101,28,157,52,152,244,91,156,60,191,79,255,232,128,110,167,199,222,230,5,126,247,127,252,43,149,205,21,140,31,186,27,84,16,178,204,5,71,103,
29,26,167,13,74,190,166,217,109,242,252,251,175,17,203,37,87,175,94,231,234,135,215,144,129,194,24,141,86,238,100,2,134,84,248,244,22,57,163,126,155,7,63,125,205,241,163,135,220,188,113,131,250,122,5,
37,18,36,10,161,10,27,145,84,168,34,189,34,165,194,11,125,87,208,74,221,124,209,5,21,12,70,67,146,165,46,149,164,141,35,116,26,159,204,166,8,163,153,233,28,235,133,60,124,254,130,175,254,237,127,114,109,
163,206,157,47,110,35,125,93,68,97,37,81,96,240,60,133,31,184,177,207,204,26,78,78,27,244,91,13,134,71,7,244,26,111,152,205,135,172,172,108,241,201,157,79,169,174,150,209,90,83,170,172,80,170,86,81,38,
102,78,64,183,115,206,168,215,101,54,159,112,250,250,25,131,214,25,213,114,141,221,157,29,106,53,55,211,14,60,23,123,181,58,68,233,144,168,186,202,96,56,102,182,104,242,203,15,95,209,61,122,197,222,254,
85,226,106,228,228,28,40,132,212,197,131,28,39,54,65,35,50,91,20,136,124,48,130,229,34,255,167,20,59,199,125,55,132,33,119,161,109,180,81,228,137,19,193,167,105,142,9,34,54,47,236,243,221,223,254,68,231,
245,75,46,95,186,12,70,147,75,85,48,154,28,179,95,43,69,232,151,40,213,182,137,215,215,25,14,123,156,189,125,206,249,211,95,24,116,91,36,153,96,103,103,143,48,142,11,17,141,193,247,66,140,23,178,190,115,
149,234,198,26,195,126,159,217,120,76,74,66,179,249,154,209,160,77,16,148,220,2,57,207,222,123,162,67,63,66,32,41,85,214,185,242,225,135,164,54,167,221,110,241,243,183,127,225,237,147,135,172,110,239,
190,207,143,243,110,159,143,37,203,156,178,208,102,57,185,112,82,36,223,11,241,237,63,121,49,238,161,159,147,230,162,120,121,22,183,151,98,249,97,173,69,40,69,169,186,193,214,238,30,255,248,143,255,155,
230,241,91,46,94,221,71,106,77,86,228,252,115,97,177,54,65,75,141,231,69,132,149,58,97,109,149,209,100,206,164,223,230,213,189,239,56,61,124,202,108,153,176,123,241,10,181,213,42,74,187,180,74,24,149,
144,90,179,177,245,255,51,245,94,61,146,157,121,154,223,239,53,199,199,9,155,62,179,42,203,209,155,166,107,183,219,221,99,118,7,187,24,93,73,186,16,4,97,177,146,32,72,144,116,35,64,95,160,191,138,46,22,
18,180,35,104,102,208,82,207,108,247,146,211,221,100,147,69,83,85,44,239,171,210,187,200,136,200,136,200,200,136,99,222,87,23,239,201,106,1,36,239,138,100,28,243,158,191,121,158,223,115,137,70,107,142,
227,254,128,225,113,151,238,222,22,189,131,77,234,237,144,34,43,176,86,82,226,52,253,190,239,248,75,66,250,52,218,171,172,172,93,96,58,205,56,25,158,240,205,111,254,142,131,253,109,150,46,95,0,83,184,
123,119,238,187,174,184,68,57,14,131,44,149,69,10,207,169,248,108,133,109,177,213,125,70,32,180,66,152,28,83,86,136,101,97,193,150,110,132,172,98,210,206,50,186,204,249,167,191,255,27,166,197,25,87,223,
185,234,220,222,166,116,97,62,90,56,1,64,220,32,73,155,204,175,94,166,52,146,209,73,143,189,205,39,108,62,184,197,104,216,37,174,37,52,23,150,72,154,13,151,189,29,197,4,81,157,184,209,225,226,149,55,41,
206,50,142,123,199,236,111,189,96,208,63,68,207,114,199,210,145,82,130,52,24,36,202,106,252,56,101,191,127,196,205,63,126,69,214,205,120,255,195,143,121,227,131,107,120,177,171,28,20,210,37,53,69,117,
84,84,99,92,148,28,31,28,48,236,29,240,240,246,183,12,182,119,200,39,176,126,241,77,222,249,225,7,180,151,83,39,97,10,34,84,24,49,41,4,199,199,3,178,209,128,60,31,241,226,222,45,78,187,135,132,126,194,
197,107,175,227,213,53,121,145,81,75,26,4,81,29,252,128,194,104,38,165,226,232,168,203,211,71,223,243,248,219,111,88,157,91,161,49,87,3,83,80,22,22,180,99,83,139,210,32,181,51,64,88,99,241,35,141,81,206,
68,102,173,131,99,121,190,98,150,185,4,122,97,5,158,167,145,170,116,62,0,44,158,145,120,126,76,127,154,243,79,255,240,107,204,241,136,191,250,235,127,73,58,95,35,119,44,50,226,216,5,72,11,52,97,92,227,
204,40,118,118,182,24,247,14,216,125,254,144,238,246,11,38,195,83,46,174,94,229,163,31,127,76,210,110,58,39,113,156,58,247,160,240,57,232,143,57,218,63,162,156,158,114,216,31,242,232,198,55,20,147,49,
107,107,151,120,231,131,183,9,210,8,83,148,196,105,13,237,135,85,64,181,71,127,120,198,206,206,30,155,79,30,176,117,247,6,157,180,201,252,133,5,172,40,200,114,8,149,27,223,184,202,194,5,190,184,7,179,
228,44,207,221,104,40,242,41,242,12,138,63,169,86,44,110,188,129,114,215,15,37,17,198,45,119,33,99,111,239,128,91,127,248,156,31,189,247,22,107,151,87,240,124,75,94,56,98,162,86,170,130,220,5,148,56,114,
105,247,184,207,116,60,100,231,229,83,14,182,158,51,203,166,44,181,22,120,239,163,247,104,45,205,161,148,68,87,41,64,82,7,76,173,102,247,224,128,201,176,75,145,77,216,127,249,132,222,222,22,81,24,176,
176,184,72,218,170,187,241,163,144,4,113,140,242,34,116,84,71,135,41,39,147,51,246,14,118,120,241,224,123,70,7,47,104,214,219,52,219,29,74,51,171,102,169,6,165,52,166,148,104,173,40,202,204,181,218,85,
16,136,82,26,164,71,32,161,200,103,88,43,200,109,89,85,191,206,157,42,171,156,80,148,114,115,255,64,208,104,181,121,124,255,123,178,147,1,43,235,151,240,66,119,207,42,81,187,83,192,72,233,2,45,106,13,
218,139,11,76,70,67,198,253,35,118,159,62,164,219,235,82,100,5,107,171,23,9,227,184,82,23,105,151,26,229,69,116,22,47,210,89,91,99,208,63,230,116,60,164,200,39,108,63,185,71,191,119,232,100,157,74,86,
75,79,183,216,245,195,8,171,20,173,206,18,215,222,122,143,233,116,194,238,222,30,183,42,197,80,187,211,38,74,66,16,14,122,231,176,36,21,227,30,183,140,62,247,108,32,220,168,71,249,158,243,35,228,57,5,
85,0,81,21,123,104,165,68,89,151,186,44,170,138,86,9,65,45,173,243,244,254,77,38,163,17,243,43,203,216,115,36,132,182,8,147,163,132,235,90,93,192,125,76,189,189,64,54,157,114,58,30,240,224,214,117,246,
54,158,97,16,92,88,191,66,173,89,119,28,126,161,93,24,140,148,180,231,47,144,118,230,232,30,30,113,50,26,50,236,31,208,59,216,36,207,199,228,103,6,171,66,10,74,148,39,9,60,141,23,132,104,237,211,89,190,
196,242,202,26,179,179,9,253,227,3,238,94,255,130,238,238,75,90,139,139,46,52,198,218,10,168,230,58,44,42,236,120,229,96,162,48,78,149,163,149,194,128,139,59,52,198,153,216,140,68,20,51,84,21,113,72,21,
195,40,172,187,198,113,88,67,83,114,253,55,191,70,5,138,249,197,37,119,152,84,164,78,164,69,82,162,189,152,40,140,104,206,47,226,105,77,145,207,56,120,249,156,71,119,191,99,58,238,19,196,49,237,213,21,
23,168,35,64,251,1,65,152,80,171,119,88,185,112,133,226,44,163,123,120,64,247,112,143,147,147,46,227,254,33,58,168,152,36,158,148,46,156,183,20,32,2,114,37,248,226,183,159,50,61,152,240,179,191,248,11,
22,47,207,225,7,154,89,86,32,77,65,51,117,188,120,21,212,152,148,150,237,221,109,122,199,59,60,188,249,13,131,173,29,84,161,185,116,233,26,239,253,179,31,210,89,172,35,36,68,65,157,160,86,103,148,193,
225,225,49,217,217,144,98,54,228,201,237,27,28,61,125,138,39,3,174,190,247,38,23,222,90,35,203,166,196,65,66,28,197,40,47,196,138,128,227,113,198,126,119,151,39,247,110,177,115,239,38,77,47,225,234,27,
151,16,170,116,179,106,41,201,75,227,94,74,207,61,144,86,73,172,144,148,72,210,36,161,44,114,38,167,83,16,133,219,157,57,194,18,129,167,201,173,64,8,119,128,155,162,64,72,69,110,37,95,126,246,123,230,
189,136,107,127,253,151,164,237,152,205,205,93,2,47,164,221,170,33,129,64,7,68,105,131,92,7,108,109,29,48,238,30,242,232,206,183,236,63,126,74,172,37,235,23,174,241,163,63,255,9,81,26,161,253,152,56,73,
137,211,22,133,145,236,31,143,216,223,59,160,156,142,153,78,78,184,247,205,23,140,122,61,150,23,214,120,251,253,183,8,210,152,34,43,136,163,20,225,69,160,67,10,149,176,119,56,96,111,103,155,71,119,190,
165,191,245,156,70,152,240,198,59,111,226,5,26,83,58,85,129,99,137,84,9,95,170,26,81,33,152,206,166,236,237,30,19,168,136,119,222,190,130,82,138,217,52,195,228,238,80,148,152,10,185,122,78,84,116,215,
182,180,46,252,253,224,217,75,62,254,224,29,230,23,27,248,158,100,150,85,180,206,170,194,9,60,159,40,174,115,50,154,177,189,215,229,240,240,128,187,55,190,226,229,131,187,4,82,240,218,213,203,188,255,
254,91,248,105,132,177,150,36,172,17,215,27,72,157,48,45,61,246,14,14,233,117,247,201,79,79,216,123,246,136,254,241,17,72,201,242,202,26,115,75,115,88,161,240,194,26,161,231,19,70,117,252,40,165,240,19,
122,39,67,54,95,62,231,217,221,27,148,147,99,130,32,164,213,234,128,157,57,152,158,14,160,82,200,72,81,96,132,64,150,158,11,120,145,194,45,199,130,24,41,37,133,150,175,62,128,69,89,80,154,18,223,247,156,
140,79,85,160,172,210,160,61,137,201,4,195,147,30,211,225,9,205,133,121,231,70,165,116,230,157,10,194,37,177,206,121,30,166,180,22,87,56,203,102,28,119,247,249,254,235,223,211,63,218,165,22,248,172,93,
92,67,248,49,133,177,120,90,225,251,17,65,16,209,90,184,192,220,133,139,28,117,143,56,61,57,161,200,134,108,61,190,77,239,96,23,29,133,36,81,66,89,90,148,192,161,169,61,215,237,44,175,93,101,233,202,58,
147,179,49,27,47,158,115,239,251,239,232,110,60,36,140,82,210,180,233,80,27,231,254,3,170,81,104,149,201,10,142,57,101,45,196,181,132,80,251,204,242,25,214,211,78,149,50,45,42,208,88,149,189,80,148,85,
42,152,203,108,16,8,48,146,227,253,77,166,211,41,105,187,77,54,61,171,22,192,2,105,92,231,32,164,116,88,142,40,165,209,90,224,108,60,37,183,25,95,127,250,255,210,221,223,33,14,61,86,151,87,157,58,74,128,
214,1,113,45,197,11,2,210,214,50,11,171,171,116,187,199,244,142,15,57,25,236,211,221,124,201,217,116,76,218,168,163,101,64,97,172,251,115,222,185,89,41,102,105,229,10,75,235,235,76,79,199,236,108,190,
224,250,239,126,203,248,120,155,133,213,53,162,90,236,148,56,85,124,163,35,226,27,148,117,248,104,9,20,182,196,8,159,32,136,220,162,91,187,235,150,103,51,138,162,172,212,58,229,43,0,157,235,238,92,10,
153,239,71,120,10,30,127,251,21,42,242,8,131,0,91,100,100,214,113,71,141,165,250,80,56,118,80,148,182,9,162,4,176,116,55,159,112,243,250,239,41,242,17,113,163,65,103,105,193,125,248,112,28,165,40,78,73,
234,29,86,175,188,134,201,13,189,222,49,71,135,251,12,143,119,24,28,236,226,5,10,173,42,103,162,84,78,150,135,16,88,45,185,119,247,62,254,41,252,236,47,127,142,159,106,98,207,61,228,70,41,103,100,65,225,
7,117,140,31,178,179,181,205,209,254,54,183,174,127,193,104,103,159,64,132,92,126,237,109,222,251,233,199,248,117,31,1,164,181,6,65,146,146,73,159,131,131,99,198,131,19,242,105,151,103,15,238,176,247,
236,9,218,134,92,184,250,38,11,151,150,40,113,138,18,23,23,152,130,31,115,52,154,178,183,187,205,227,7,119,217,191,127,143,80,10,174,190,123,13,47,177,110,161,86,90,167,181,87,142,20,40,149,118,0,50,233,
212,58,89,225,156,137,94,232,92,103,89,126,134,18,14,34,85,228,110,14,103,133,101,54,5,101,45,86,89,206,102,37,39,39,251,172,53,83,58,111,174,59,57,31,37,173,185,121,148,45,137,107,161,67,174,250,33,218,
143,217,234,14,217,223,221,229,246,183,215,57,124,242,144,72,251,188,246,218,235,188,251,241,187,212,59,77,132,84,4,65,76,92,175,99,145,236,13,38,28,110,239,33,77,70,150,157,242,252,246,55,12,143,122,
180,90,109,222,251,224,29,130,90,204,104,60,161,217,156,35,72,106,232,32,34,199,103,111,255,152,151,27,47,120,114,251,59,138,193,62,186,44,121,243,173,55,168,119,82,242,220,226,249,10,165,37,190,118,228,
197,243,249,162,43,54,52,182,176,72,124,86,215,214,16,149,68,45,8,36,165,132,225,48,115,85,176,116,179,108,135,141,118,138,27,99,12,103,163,33,171,75,77,162,36,70,84,215,22,235,2,164,165,40,240,60,159,
180,222,32,110,206,51,85,83,246,55,118,248,238,219,175,120,113,247,54,11,141,136,43,151,46,243,238,15,222,68,7,158,115,255,41,143,56,77,241,130,144,66,133,28,236,118,25,30,31,83,142,186,28,111,188,100,
112,184,11,218,99,117,121,145,118,59,197,10,65,24,132,36,105,138,167,61,194,180,73,161,66,186,199,61,158,63,121,196,222,179,199,152,105,23,1,204,207,45,225,5,158,51,194,40,133,144,22,207,211,213,44,86,
187,181,162,39,95,49,134,78,39,19,188,184,205,124,179,195,116,114,226,102,251,185,36,66,82,230,46,112,197,215,46,194,15,105,64,43,114,11,165,201,32,19,68,181,4,99,11,48,142,85,84,218,18,45,85,53,222,240,
8,147,26,141,230,60,133,84,140,135,61,110,94,255,3,167,189,67,90,105,157,86,187,133,23,38,24,235,170,70,237,5,104,63,34,74,59,204,93,184,200,224,116,196,112,112,204,108,60,228,224,229,3,186,251,219,160,
61,154,141,150,147,65,42,139,174,34,33,125,63,102,97,237,50,243,235,107,12,135,35,246,54,159,115,231,198,215,140,187,91,4,97,72,103,97,174,82,159,57,86,190,168,116,230,18,23,137,9,21,212,206,0,0,32,0,
73,68,65,84,152,85,168,241,146,18,41,20,147,225,144,246,181,183,137,139,156,225,73,159,153,181,248,190,171,236,203,34,163,48,89,69,22,117,31,170,106,101,73,153,103,228,195,162,218,121,202,138,71,175,171,
116,17,139,48,32,60,31,47,168,17,54,230,152,90,159,34,155,112,251,171,207,56,218,219,166,211,108,208,106,53,137,210,216,85,218,202,175,58,227,152,70,115,153,133,149,139,244,122,3,246,119,54,25,14,186,
244,54,159,115,210,59,34,104,214,209,74,185,226,79,104,162,36,118,172,120,175,198,210,197,43,204,47,46,49,30,246,121,246,232,1,95,255,254,159,224,172,75,218,168,227,199,53,242,188,192,61,25,10,165,108,
133,27,146,168,32,160,200,103,14,212,104,157,131,59,8,35,148,210,76,199,67,176,37,34,144,152,51,87,64,150,69,230,62,22,133,121,181,62,151,66,97,16,156,244,14,41,100,137,144,170,130,246,185,56,81,71,227,
172,64,113,65,72,16,165,196,245,57,178,201,140,222,193,54,127,248,245,175,200,153,210,106,214,105,118,154,72,79,99,141,139,190,12,195,26,81,109,142,149,245,171,8,11,163,193,144,209,73,143,225,209,46,135,
123,47,8,2,133,41,5,26,41,49,182,32,207,93,16,66,89,150,204,206,134,20,163,51,222,248,232,29,252,88,35,40,168,98,162,94,153,50,164,138,209,81,141,110,191,207,214,214,75,238,222,248,138,193,214,33,1,30,
151,95,127,155,183,126,244,62,126,226,225,75,233,244,163,181,38,133,23,112,216,237,51,25,12,200,206,70,60,127,112,155,189,71,15,48,83,195,226,197,21,86,175,172,86,40,91,69,218,168,147,52,218,136,48,161,
59,28,179,177,185,197,198,211,187,28,63,123,132,42,50,46,94,122,147,246,218,2,150,220,181,234,194,160,181,162,180,2,95,251,46,52,164,40,64,10,194,202,68,21,197,77,140,157,162,188,28,93,104,76,94,48,203,
206,208,158,155,99,78,51,135,52,53,72,172,145,140,71,19,180,167,168,47,183,9,194,136,178,116,241,112,113,232,150,118,82,88,16,1,50,72,24,228,134,173,205,77,238,124,123,157,131,135,119,104,196,17,151,46,
191,198,123,159,124,72,212,240,145,90,18,134,49,126,144,98,241,233,77,44,7,187,93,76,158,147,77,79,120,122,227,43,246,54,182,105,164,45,222,121,231,109,90,75,109,140,133,56,137,73,235,13,148,31,50,37,
96,247,176,203,243,71,143,217,120,252,16,57,236,18,42,193,252,197,75,204,175,205,33,133,227,11,233,170,2,21,149,132,204,24,1,70,161,3,199,133,183,6,242,233,49,71,71,125,210,206,60,74,101,136,34,71,107,
69,84,192,233,168,79,89,56,169,161,181,134,89,150,185,106,223,10,194,200,119,185,166,128,167,92,220,164,193,185,83,165,114,31,191,48,105,48,201,4,135,189,33,223,127,255,29,79,111,223,98,177,145,242,193,
187,239,177,114,105,133,168,230,178,90,131,32,36,78,82,116,16,97,116,202,209,241,152,147,193,49,211,241,49,251,207,159,112,210,221,39,43,13,171,107,23,89,92,93,66,251,26,95,41,162,184,134,22,62,94,220,
96,38,66,198,227,9,135,187,219,28,237,188,192,78,143,177,165,161,213,90,36,76,98,130,192,3,105,171,143,139,114,10,34,43,80,158,166,44,203,170,2,119,206,108,41,12,47,31,222,67,188,243,17,115,237,54,226,
116,0,156,34,164,36,65,86,153,174,133,131,170,149,6,147,231,228,133,169,94,216,74,105,82,186,208,153,87,250,125,220,14,197,37,17,213,136,154,115,244,250,71,220,254,246,75,38,39,125,58,141,38,245,86,19,
225,121,104,47,196,20,165,251,144,69,49,113,173,201,252,242,42,131,147,19,70,39,3,178,233,144,131,231,247,57,218,219,166,144,176,52,191,64,105,133,131,230,5,78,158,171,253,128,165,139,151,73,231,150,232,
247,135,244,122,71,244,7,61,108,54,70,41,65,171,189,92,73,52,157,7,67,158,63,40,80,121,48,156,78,92,10,170,48,15,75,73,198,211,91,55,184,244,241,143,89,89,79,57,218,217,99,50,155,184,190,197,248,100,179,
9,179,34,119,170,157,210,169,116,172,208,8,172,219,111,120,94,133,112,176,80,241,171,132,1,171,36,97,21,13,26,196,77,242,201,152,239,191,252,140,126,239,128,133,78,155,86,187,131,213,162,146,99,107,116,
16,184,220,231,250,60,243,203,235,204,206,114,246,182,183,57,58,56,100,184,251,140,201,73,15,233,7,52,235,77,172,112,199,172,91,96,38,4,65,141,213,75,215,168,183,219,156,14,135,60,123,112,151,155,95,127,
133,204,123,232,32,160,214,89,112,163,89,65,181,195,168,20,57,149,175,32,203,139,243,221,43,146,18,83,204,216,221,216,96,229,141,55,105,181,150,56,25,244,153,101,19,60,47,164,48,5,102,230,150,188,2,1,
133,117,210,78,37,176,121,6,249,140,178,180,228,89,70,84,189,147,166,44,225,28,239,224,71,168,48,161,214,89,70,88,193,225,222,115,190,251,221,167,20,230,140,102,167,73,163,213,70,107,183,27,18,58,32,140,
107,4,65,141,185,165,85,242,172,224,108,122,198,209,193,54,71,135,219,28,108,61,195,170,28,107,5,165,2,109,77,238,150,48,210,162,109,197,139,151,130,185,165,54,250,21,56,23,172,180,100,69,142,175,60,180,
246,72,154,45,70,217,140,157,237,231,220,255,238,91,38,135,125,58,245,5,174,92,189,204,213,247,175,145,212,3,148,50,132,126,68,82,111,80,106,77,183,63,98,210,31,112,58,61,97,227,209,45,182,31,60,160,152,
20,44,175,93,230,202,187,111,18,164,17,82,6,212,106,45,106,105,11,252,132,238,104,200,246,230,38,207,239,222,98,248,242,25,161,49,180,58,75,92,126,235,50,69,57,163,44,140,235,56,164,116,54,101,229,33,
76,137,22,154,92,158,227,4,96,120,50,224,209,253,199,92,125,235,13,132,210,104,145,97,164,164,192,64,81,80,150,5,82,56,117,67,105,156,254,182,150,6,238,67,40,124,202,210,16,250,170,82,107,216,106,94,234,
218,209,12,143,141,205,29,110,126,117,157,253,199,143,232,212,155,188,243,193,251,204,173,95,194,79,82,87,41,148,130,48,74,48,210,103,48,45,217,221,239,66,62,229,116,50,228,193,151,127,96,116,188,71,156,
68,124,248,163,143,88,189,188,130,84,154,56,170,81,111,183,8,162,58,227,76,177,183,223,227,248,232,128,225,209,30,226,180,139,39,13,245,230,60,235,175,93,38,207,157,230,61,12,20,58,12,201,11,7,116,146,
82,224,161,220,75,46,21,165,117,51,201,165,165,38,183,111,221,1,21,176,126,229,138,91,208,146,163,130,18,49,141,49,170,172,52,216,142,220,146,23,153,51,211,32,221,2,183,10,201,150,90,35,68,134,178,18,
43,37,81,146,98,189,132,227,163,33,119,190,189,206,147,239,190,227,173,181,85,62,254,225,251,52,22,155,206,19,96,45,129,31,16,215,234,248,113,157,105,169,56,25,159,112,124,116,204,217,176,203,246,211,
251,140,186,123,24,36,171,43,171,172,172,46,226,199,49,97,16,81,111,180,209,113,138,242,35,78,75,201,112,208,101,118,54,226,104,119,131,98,220,195,20,25,205,246,2,243,43,11,14,57,225,41,180,246,43,169,
160,211,185,9,169,221,92,214,26,140,243,100,59,115,144,210,180,91,9,119,191,248,140,55,126,252,207,184,176,182,134,119,122,194,104,56,116,121,9,210,144,23,174,242,205,243,12,99,4,214,186,206,9,225,84,
44,101,233,170,98,229,105,215,5,96,92,101,154,52,88,88,190,4,30,220,186,254,25,163,110,151,213,165,54,113,148,58,119,41,64,89,162,180,168,84,108,41,107,215,94,163,20,130,105,175,199,105,255,128,231,247,
111,146,77,134,168,208,103,190,179,128,210,33,182,204,241,181,79,224,71,132,94,194,242,250,85,162,102,155,147,209,152,147,222,33,219,47,31,177,253,228,62,249,233,25,11,171,139,168,64,33,132,135,212,190,
67,135,75,137,18,85,74,150,144,148,14,159,10,202,73,46,181,85,24,33,17,106,204,205,127,248,21,31,252,235,255,132,43,111,190,197,193,238,46,147,241,152,220,204,48,214,237,41,242,233,140,60,47,80,158,170,
20,46,165,75,77,43,206,33,181,78,189,35,113,160,50,47,8,73,226,22,139,23,94,135,242,140,251,55,255,200,160,183,207,124,187,69,156,70,20,182,112,145,155,214,117,166,94,144,160,162,58,157,149,117,166,69,
201,209,222,54,155,79,31,114,114,184,131,201,79,137,155,41,65,24,184,124,0,225,145,164,117,23,131,24,213,89,187,242,22,73,26,115,210,235,211,221,223,226,229,211,123,216,188,79,224,123,164,237,37,148,246,
171,216,198,106,239,231,242,48,43,151,189,99,48,157,83,135,16,22,83,102,20,179,51,238,125,246,91,222,249,171,191,102,113,117,141,254,225,33,227,179,17,162,204,33,40,200,114,243,106,175,98,172,129,50,163,
44,92,129,42,181,135,39,203,87,17,52,72,40,13,248,190,79,20,37,116,22,47,208,105,117,216,123,252,144,235,191,249,53,185,153,49,191,208,34,76,235,206,15,97,156,132,56,140,107,4,81,157,165,245,215,137,253,
136,147,193,9,47,95,62,165,123,184,205,112,247,57,86,24,2,63,130,42,134,82,58,104,144,67,14,216,10,34,36,144,174,5,214,231,250,81,77,158,149,80,186,255,193,48,168,161,194,144,23,155,27,124,127,253,27,
198,71,93,98,63,230,157,15,222,231,218,135,175,33,164,37,208,154,48,8,168,183,154,4,73,194,240,172,224,164,219,103,58,59,101,243,217,67,118,31,61,32,59,203,105,52,231,185,250,238,155,4,181,0,132,166,222,
104,81,171,55,145,113,157,147,201,25,199,251,7,140,142,143,201,134,199,136,124,134,144,30,23,222,120,29,17,122,72,43,221,226,81,203,87,122,94,79,43,167,253,245,125,135,130,205,157,142,58,169,69,108,190,
124,194,206,139,109,140,72,16,58,65,234,144,48,72,240,163,8,161,60,39,168,170,22,85,69,150,147,101,5,101,238,102,163,74,253,73,89,39,165,131,120,105,29,226,69,53,142,6,39,60,185,123,155,151,119,111,211,
142,235,124,252,147,159,114,225,141,43,68,73,132,242,32,8,3,146,90,29,233,197,204,172,228,224,160,75,54,30,211,27,117,121,112,227,75,14,246,119,241,253,26,239,190,253,3,22,215,22,92,87,18,197,180,58,29,
162,90,131,211,28,14,14,251,20,179,41,38,207,24,31,31,162,173,171,156,214,175,174,19,212,2,180,231,150,170,194,211,21,26,86,161,181,83,203,40,207,233,226,207,153,239,165,129,192,243,121,253,141,139,220,
250,227,63,49,56,62,226,44,87,24,25,185,177,64,84,171,228,124,178,2,131,57,51,150,51,35,185,170,118,114,150,49,203,10,151,2,36,92,168,122,16,198,46,68,167,20,60,184,123,155,7,223,93,231,195,215,174,240,
147,127,254,1,157,149,54,74,41,23,64,130,11,59,9,147,6,42,172,49,154,25,142,143,143,57,27,30,178,241,232,62,199,123,187,100,70,48,191,176,204,218,197,53,162,36,70,75,69,84,75,241,163,26,81,210,98,106,
125,38,163,25,227,126,151,222,209,1,195,238,38,249,217,0,79,7,204,47,206,227,249,30,194,211,46,76,71,59,89,157,193,58,214,188,118,173,176,187,161,194,133,96,11,137,239,123,4,129,36,73,20,55,62,251,15,
12,134,3,162,180,69,189,237,14,87,180,118,82,69,33,177,40,74,36,86,123,8,229,97,243,130,34,47,156,252,207,184,108,96,93,229,196,106,47,162,62,183,128,240,36,95,253,254,183,140,123,125,150,23,23,73,234,
13,172,242,93,144,184,116,139,96,79,135,248,126,194,252,202,37,10,161,24,14,71,12,142,247,217,120,116,151,217,248,4,229,105,218,173,86,229,98,45,8,99,231,110,87,94,200,252,234,101,162,86,135,193,201,144,
98,58,102,50,238,211,219,123,193,105,175,75,163,153,18,198,17,74,185,231,68,87,7,189,148,110,153,47,229,121,103,40,16,194,189,51,10,137,169,184,217,210,15,8,35,197,119,255,240,15,116,199,51,22,86,86,105,
206,47,80,75,26,46,124,70,7,248,129,143,167,42,39,170,56,199,33,227,118,37,82,160,117,72,24,37,149,247,195,57,162,211,185,101,90,237,148,135,55,190,228,96,119,155,229,229,121,194,52,116,179,119,99,17,
198,34,164,196,15,34,124,47,161,221,154,39,159,76,56,233,247,56,233,31,50,62,222,229,108,220,197,143,125,226,40,116,94,19,229,227,135,177,235,168,195,26,203,235,175,17,37,9,147,225,136,238,222,14,59,155,
207,24,30,238,32,138,140,184,222,70,249,161,115,4,59,161,185,219,77,84,105,104,84,130,14,71,82,5,75,129,41,93,190,49,74,33,77,206,215,127,255,183,12,242,83,230,150,22,105,54,218,132,158,83,85,249,94,84,
161,215,29,100,240,213,190,195,128,45,157,193,213,84,218,124,41,92,49,233,133,53,226,230,60,203,23,175,112,118,180,195,119,127,252,20,33,74,230,231,58,232,192,115,89,203,214,146,151,37,82,123,248,65,76,
99,110,133,180,209,194,2,167,253,62,59,207,159,113,188,179,65,110,166,104,223,71,250,190,163,136,106,141,250,47,255,139,255,236,151,198,56,136,84,97,206,127,178,114,25,170,66,185,25,168,117,28,58,97,113,
15,111,123,129,222,217,136,235,127,248,140,237,71,207,89,172,47,240,193,7,239,177,112,121,137,194,64,16,70,68,161,38,172,53,240,195,58,163,194,176,241,114,147,126,191,203,189,239,175,179,123,239,30,229,
120,70,103,97,149,119,62,249,144,230,66,3,223,243,233,116,230,169,183,230,81,81,202,193,112,68,119,111,159,201,176,207,222,243,251,140,119,182,73,252,152,43,111,158,147,23,157,186,72,107,133,167,60,172,
117,46,87,207,11,80,18,148,174,218,209,162,116,164,75,41,136,107,49,183,190,185,193,252,252,2,210,79,92,168,72,101,138,200,115,199,247,54,166,164,52,57,166,44,200,173,99,230,123,62,40,237,90,115,89,221,
180,178,40,168,213,59,100,50,224,243,207,63,227,206,31,62,231,205,181,139,252,197,191,254,25,201,124,203,101,238,122,144,38,81,37,149,106,144,201,136,151,187,93,78,122,199,244,142,119,249,238,179,255,
192,248,112,151,52,169,243,131,15,63,230,202,59,87,93,101,31,215,104,207,45,16,214,154,140,51,201,238,65,143,114,118,202,209,209,30,27,247,111,145,13,14,136,194,132,215,222,122,139,214,210,28,88,235,36,
158,158,143,242,20,198,56,100,128,146,30,126,16,86,17,109,238,240,22,214,113,129,149,18,4,190,70,43,120,248,224,33,194,11,136,107,13,148,23,162,165,131,59,97,93,72,248,108,54,69,9,65,94,24,138,194,5,139,
120,210,93,55,91,133,171,72,33,8,195,24,227,39,252,211,239,191,224,222,231,159,243,241,251,111,242,209,143,223,198,122,14,115,80,150,37,190,118,121,190,113,173,142,159,212,217,61,26,177,191,123,192,184,
119,192,131,155,223,114,114,180,13,82,178,126,225,18,23,175,92,37,76,34,252,32,166,217,104,209,108,118,240,211,54,227,28,78,6,35,198,131,99,70,195,30,187,79,238,146,159,14,8,189,144,213,75,23,8,147,128,
56,14,240,188,8,95,41,12,238,133,82,149,91,82,7,26,45,117,21,62,237,94,58,107,74,178,89,230,64,95,126,200,108,122,198,227,251,247,89,184,112,17,63,174,17,70,9,121,158,81,100,25,194,58,69,140,169,48,203,
86,26,10,83,225,183,109,69,227,212,206,148,35,148,38,170,213,169,119,230,248,244,215,127,207,233,113,151,75,151,46,227,199,49,133,144,8,223,71,105,71,115,245,125,15,63,174,145,118,150,81,65,192,116,114,
198,176,127,192,189,111,190,192,148,83,162,56,166,213,232,184,104,79,33,9,124,159,32,136,241,194,26,43,235,175,17,181,219,140,134,67,70,39,125,142,143,246,120,249,224,22,199,219,47,105,207,47,209,90,88,
116,217,191,202,171,18,229,156,50,79,73,229,24,46,66,162,124,23,169,168,168,164,132,213,184,75,85,99,13,21,122,152,209,49,119,191,191,75,235,210,53,58,115,109,194,56,194,100,25,101,133,165,64,184,44,234,
162,44,220,159,17,110,159,230,41,15,97,64,107,39,255,70,41,90,115,171,204,205,119,248,226,215,127,71,255,104,159,249,197,54,86,171,87,73,83,72,133,80,190,187,254,73,147,206,226,26,86,40,10,11,199,187,
207,121,122,239,22,39,253,125,162,36,162,217,108,97,125,15,43,52,81,82,167,150,214,137,194,6,107,151,223,32,105,214,25,247,7,108,191,124,206,214,139,135,236,111,62,162,204,206,104,205,47,18,165,169,211,
201,11,137,167,188,87,78,218,243,68,43,229,121,78,141,117,30,39,90,82,225,34,44,197,108,138,16,150,233,225,1,143,110,223,163,121,245,18,11,243,243,46,133,207,148,46,4,7,65,89,228,175,178,127,157,178,169,
138,84,23,213,63,172,155,24,8,169,73,26,243,92,124,237,109,198,59,47,249,205,223,252,31,156,140,6,44,173,47,99,164,243,141,56,73,149,59,135,93,80,202,26,157,133,21,242,233,140,241,120,200,211,135,183,
56,218,123,70,150,79,168,53,26,4,97,228,192,112,126,68,146,54,81,255,213,191,249,55,191,116,157,238,57,40,74,80,150,142,156,171,172,35,15,106,81,37,184,88,65,82,235,32,146,136,111,190,250,156,151,55,31,
176,182,176,206,15,126,250,62,237,165,196,185,57,133,170,24,57,53,146,180,69,38,53,47,182,247,56,27,158,240,226,233,93,182,239,221,35,200,45,173,206,10,111,125,236,8,152,161,239,211,168,183,169,53,59,
16,214,56,30,77,93,240,117,97,216,223,121,193,209,211,71,88,235,177,178,126,149,181,215,46,226,7,14,210,134,173,162,203,124,167,150,245,252,0,173,60,148,150,175,108,223,156,167,110,42,89,141,166,74,30,
223,125,192,250,229,203,88,169,145,58,116,45,126,21,17,104,255,127,55,40,207,221,210,71,42,231,96,148,82,184,185,175,41,17,194,135,32,225,206,163,231,220,250,236,119,188,123,233,50,159,252,217,39,248,
245,192,57,116,173,37,8,2,194,56,70,249,49,214,139,217,218,61,162,127,112,196,222,254,38,119,175,127,193,244,184,71,179,209,225,131,143,63,226,194,213,139,238,67,25,135,52,59,115,4,73,157,211,82,178,187,
127,204,217,100,204,217,120,224,198,90,135,187,4,218,227,194,165,171,172,92,90,70,123,18,223,243,17,194,195,247,125,180,95,141,110,138,2,99,133,195,10,11,40,138,162,146,100,158,195,192,44,166,180,132,
177,207,168,63,96,112,220,39,172,53,176,40,116,16,59,121,165,53,14,53,96,161,44,10,39,7,45,75,103,192,145,14,9,155,231,5,165,113,247,93,250,49,247,31,62,227,209,87,215,249,193,187,111,176,118,117,197,
89,216,133,211,48,251,158,195,2,132,113,68,92,107,49,56,51,236,237,117,25,141,250,220,249,246,58,167,131,30,73,146,112,113,237,2,151,95,187,74,20,71,40,79,145,36,13,106,105,147,160,214,98,98,20,221,227,
62,39,253,30,131,254,33,71,155,143,153,142,123,248,210,99,101,125,157,168,22,161,149,75,140,114,193,18,234,21,235,223,152,210,169,89,116,224,216,41,82,145,231,69,85,117,229,174,64,40,77,133,212,214,228,
167,99,6,221,67,70,185,33,78,91,212,27,77,200,10,71,101,197,82,154,210,29,108,198,184,229,158,192,165,167,73,133,181,21,83,70,107,154,141,54,247,111,220,160,156,158,50,183,60,143,14,130,42,93,172,194,
49,91,80,74,19,4,49,73,163,131,136,18,132,210,140,6,93,110,126,253,7,176,25,81,232,220,236,86,184,96,114,207,247,137,146,58,65,24,51,191,124,153,122,123,142,201,233,132,254,201,49,251,123,91,116,183,159,
115,114,180,77,84,107,48,183,180,132,80,194,197,39,42,7,26,83,234,92,170,75,165,169,183,200,192,175,184,250,78,150,233,246,54,46,59,226,188,0,244,253,128,179,65,143,239,191,187,69,153,212,153,91,89,162,
85,111,34,242,146,172,200,93,26,150,133,179,217,89,101,60,210,232,192,221,147,188,204,40,202,162,98,188,4,204,175,92,224,209,141,111,201,166,19,146,102,234,240,30,82,85,24,115,135,31,150,218,229,84,68,
81,19,21,36,40,21,144,77,122,220,250,242,247,76,70,61,106,105,141,102,179,131,149,202,133,133,135,49,73,82,199,15,98,150,214,95,167,214,108,48,25,14,217,223,124,193,230,198,99,122,123,47,57,27,14,104,
207,45,16,213,157,204,83,106,15,37,149,219,77,10,167,206,57,31,235,120,190,143,18,14,177,45,109,149,142,102,170,101,174,176,152,220,146,116,154,12,158,111,241,248,241,99,84,167,69,152,212,168,215,106,
85,128,74,238,156,221,166,112,239,100,233,112,107,66,84,69,67,149,21,80,88,135,97,88,92,187,68,62,232,115,253,211,127,196,175,135,132,73,224,184,80,86,96,133,118,166,73,237,17,85,74,191,214,194,42,229,
44,199,247,4,143,111,125,203,139,39,247,40,178,9,113,45,33,136,107,142,134,171,60,106,181,58,181,90,19,245,95,255,55,255,195,47,149,167,220,236,158,178,186,224,213,11,82,229,92,106,229,96,158,165,241,
104,205,205,243,240,249,67,190,255,244,75,222,126,237,77,222,253,201,123,120,129,227,197,91,20,73,228,35,148,71,45,105,225,213,82,94,238,236,209,61,60,224,206,173,175,216,184,127,15,191,128,133,229,139,
188,253,209,7,44,173,205,227,251,146,122,218,36,105,180,208,73,157,163,147,17,39,253,62,189,94,151,189,141,167,108,223,189,137,42,12,243,139,107,188,254,193,155,68,105,136,144,198,101,119,74,141,210,26,
132,66,43,65,158,27,226,184,134,244,207,33,96,198,49,82,164,114,85,121,89,80,175,167,76,198,167,28,29,236,163,252,4,35,53,202,11,9,130,128,210,150,231,65,149,213,53,16,20,38,119,236,124,161,240,60,201,
44,119,25,176,165,209,108,31,14,184,251,249,231,124,252,222,91,188,241,131,215,136,210,192,101,229,230,214,225,72,171,27,227,69,117,246,142,135,236,236,236,176,185,179,193,253,47,190,160,28,141,232,180,
155,188,255,225,7,188,253,209,59,248,145,123,225,235,205,54,65,210,96,82,40,118,246,186,244,143,187,28,108,191,224,229,195,219,12,246,118,208,82,112,229,210,85,94,127,239,26,194,147,85,171,28,160,164,
194,243,21,66,185,5,98,94,20,20,86,35,133,71,24,134,24,11,179,153,155,33,22,165,171,242,203,178,64,0,129,31,112,116,212,99,119,123,155,179,172,64,235,0,207,11,137,146,26,101,89,84,170,10,67,94,228,40,
105,29,196,78,169,87,75,225,210,90,102,89,201,225,241,9,7,207,95,240,222,187,87,105,204,165,72,97,41,10,123,158,21,142,31,56,249,88,156,180,176,42,98,255,120,68,111,208,229,250,167,159,50,57,233,209,168,
213,184,118,249,10,235,87,46,226,135,62,170,218,99,68,245,182,115,125,151,146,195,222,9,167,131,3,122,71,123,244,118,95,48,29,30,34,44,172,95,185,70,163,147,2,170,186,246,10,223,215,78,66,137,83,107,153,
210,45,17,149,23,85,47,180,91,193,21,101,73,150,205,200,139,130,178,44,41,203,18,161,52,181,52,101,122,58,162,187,187,73,142,34,109,182,105,118,218,104,161,153,78,38,110,188,103,4,101,49,171,82,94,43,
137,227,57,99,221,130,244,2,78,135,39,148,249,148,164,217,112,137,110,90,57,240,86,85,144,128,196,211,1,65,144,16,196,117,164,31,146,103,19,110,94,255,29,54,63,163,145,36,52,27,117,100,149,103,236,251,
62,97,16,57,32,214,133,171,180,150,87,24,78,70,12,142,15,56,220,221,162,191,179,65,62,233,17,5,17,237,197,85,148,31,58,110,80,224,70,30,94,53,106,82,158,68,107,151,144,38,253,152,40,168,225,121,129,11,
199,17,110,175,1,231,75,93,233,194,61,252,128,200,151,12,15,119,185,125,243,14,101,148,178,126,249,18,141,118,27,138,146,50,159,185,115,163,172,220,165,85,24,137,243,52,184,32,112,91,141,23,166,195,1,
103,167,167,232,164,86,205,76,221,248,88,9,233,148,45,74,17,69,13,226,180,69,173,189,128,31,215,33,31,243,245,239,254,145,162,60,35,14,66,234,237,142,19,155,8,240,116,72,173,222,32,142,235,44,94,184,76,
189,217,102,50,30,177,183,245,130,199,247,111,59,195,223,168,79,163,53,71,99,110,1,43,180,147,90,42,151,139,44,165,75,190,19,234,79,7,178,23,38,120,186,74,19,171,138,76,33,4,166,44,25,141,39,248,113,140,
151,36,248,74,179,251,228,9,251,27,91,16,199,52,23,22,169,213,82,68,225,14,115,33,164,51,129,81,86,7,190,120,5,222,179,142,74,71,16,37,68,82,240,244,206,109,8,125,132,118,193,56,231,65,241,66,10,148,231,
225,7,9,81,173,69,173,189,130,214,17,181,52,226,241,205,111,184,119,251,6,82,89,210,102,155,40,74,92,215,166,125,146,52,37,173,55,153,95,189,130,250,31,255,231,255,229,151,210,117,79,206,93,86,125,141,
140,113,176,49,165,171,5,76,229,214,60,26,244,121,252,205,29,222,122,253,13,22,174,174,32,148,193,22,165,107,149,133,114,176,50,21,146,52,59,28,13,71,108,237,108,241,224,251,27,28,61,122,132,46,4,139,
139,171,188,245,201,123,164,237,6,181,90,72,20,165,212,155,109,8,99,250,147,140,222,209,17,217,217,41,155,79,30,112,240,236,33,102,58,163,211,94,230,7,63,250,144,160,225,57,249,152,80,4,65,80,33,73,245,
171,196,249,194,10,26,141,38,218,11,93,204,93,133,7,54,66,81,148,46,175,84,0,245,102,157,221,237,93,70,39,3,71,86,172,42,142,48,10,29,154,65,88,132,116,78,219,241,120,130,167,20,186,58,76,141,17,204,102,
57,211,162,96,111,99,139,245,75,139,180,23,218,149,201,203,86,47,145,131,23,105,79,19,212,90,156,89,197,139,141,109,54,159,63,225,241,55,95,18,22,134,86,171,205,79,127,246,83,46,189,117,5,47,116,28,238,
90,90,39,170,53,200,133,207,214,206,17,253,222,49,71,187,155,108,61,185,207,233,209,62,18,184,184,178,198,219,31,191,139,10,189,10,224,228,59,54,71,160,49,198,224,123,158,235,68,138,146,220,106,162,90,
235,79,179,205,42,147,212,148,5,70,56,135,40,64,16,248,175,102,207,39,253,99,154,157,14,89,102,209,126,128,31,134,152,194,197,188,89,107,41,179,220,45,107,133,34,43,205,171,216,200,162,52,148,89,78,187,
149,18,215,66,167,208,112,39,6,74,8,180,212,149,86,184,78,80,107,113,48,152,242,114,115,147,63,126,250,91,38,199,251,44,180,91,188,241,218,53,214,46,175,160,60,199,114,10,226,152,164,222,198,139,235,20,
42,164,223,63,97,56,56,98,111,123,131,163,141,231,100,103,125,180,146,172,172,94,100,110,113,209,1,172,148,135,146,178,26,247,249,149,98,198,93,15,132,36,203,13,94,220,164,222,154,163,200,115,138,34,119,
207,70,81,186,46,166,52,238,35,37,20,133,177,100,103,51,180,18,152,217,41,94,148,226,71,17,73,163,78,24,132,204,70,103,148,101,238,88,60,149,2,232,188,90,40,171,148,36,139,155,69,123,213,232,70,10,92,
87,84,22,142,212,105,93,206,66,28,39,44,174,172,163,226,26,131,147,46,223,252,225,63,50,155,156,210,72,99,218,173,38,86,58,169,160,231,121,4,97,66,16,214,220,98,111,245,2,147,179,51,250,71,251,236,108,
60,229,104,247,37,161,103,8,180,162,222,156,195,42,133,144,110,79,33,181,118,236,24,89,21,6,82,97,75,83,69,30,106,58,43,235,164,181,26,101,110,42,131,81,117,184,85,203,76,43,42,166,140,242,73,162,152,
193,225,1,219,155,187,116,46,94,64,43,69,163,213,193,147,138,50,203,206,253,73,175,66,231,173,205,221,189,168,14,184,178,52,46,117,75,235,42,115,184,120,21,103,104,141,91,238,6,81,141,184,214,98,113,245,
10,126,144,48,234,239,113,243,143,191,101,48,236,210,168,167,164,181,58,185,117,74,60,79,251,164,245,38,81,148,178,176,114,137,122,107,129,179,209,152,221,237,151,188,124,114,159,113,127,15,59,29,17,215,
154,116,22,171,195,94,85,174,122,85,33,211,149,172,124,40,21,205,82,249,180,230,87,72,107,117,39,175,20,188,42,116,48,22,207,15,220,1,28,70,85,132,96,201,254,206,14,253,238,33,245,229,37,130,40,166,209,
238,56,12,71,158,87,201,97,174,235,65,138,106,215,99,207,195,164,17,148,140,250,93,10,41,157,202,200,24,231,144,175,70,76,162,138,146,12,226,58,237,197,139,180,218,139,132,161,199,198,221,155,60,184,115,
3,207,131,52,169,163,131,16,131,27,107,71,73,141,52,109,176,176,114,137,229,11,87,80,255,221,255,244,191,254,50,240,29,149,13,165,201,178,204,181,115,210,171,102,214,37,194,226,44,214,66,210,59,56,98,
105,126,142,250,66,19,45,44,74,148,104,237,176,187,66,107,151,11,155,54,201,164,102,103,103,155,239,191,253,138,253,135,143,9,116,192,202,202,69,62,254,231,63,98,126,165,141,231,41,210,180,78,173,217,
70,133,53,78,166,5,251,123,187,244,186,123,60,127,120,151,238,147,251,200,233,148,36,110,242,214,199,31,50,183,214,166,44,45,190,239,126,140,231,107,60,207,171,100,135,231,17,100,130,70,103,185,194,131,
74,135,56,246,66,183,169,180,78,41,99,40,8,163,128,89,14,190,146,100,217,148,40,138,41,13,8,161,137,227,152,162,204,171,237,172,203,250,20,74,187,16,99,227,102,139,89,150,35,5,248,97,128,82,138,32,244,
209,90,86,89,170,231,35,36,69,24,213,240,146,14,219,135,93,238,223,185,199,253,235,191,199,156,14,89,91,90,227,227,159,254,144,11,111,172,227,249,18,79,199,196,181,180,202,10,14,217,61,236,211,235,246,
233,29,237,241,252,193,45,38,221,3,36,150,11,171,151,121,247,147,15,177,158,160,44,36,97,229,144,214,85,150,105,89,186,5,151,197,141,158,6,253,17,227,113,73,103,105,13,107,140,155,205,123,62,214,42,242,
60,71,8,67,150,149,104,45,73,235,49,167,195,9,81,4,179,233,148,48,174,185,80,15,165,169,165,13,231,198,181,46,8,196,148,57,2,40,133,192,148,6,173,125,242,210,141,120,124,95,84,221,145,68,202,170,154,19,
2,63,112,72,235,56,237,80,168,152,141,173,29,254,240,219,127,164,183,189,193,197,229,69,222,122,251,13,230,150,22,240,3,135,174,22,210,39,174,53,9,146,38,185,245,233,13,199,100,167,35,186,7,219,108,60,
186,141,44,78,49,185,101,105,105,141,165,149,53,84,160,43,30,185,112,251,22,235,146,170,138,194,80,24,200,10,67,81,186,46,101,127,103,151,48,157,163,61,191,200,236,108,74,62,203,94,149,230,110,142,111,
201,243,130,162,112,174,235,56,242,153,77,199,140,135,39,132,105,29,43,21,65,92,35,73,98,70,131,1,165,53,120,202,29,116,121,145,191,250,205,66,56,231,42,82,160,180,143,60,39,180,150,238,157,18,165,155,
113,251,81,66,187,179,194,242,229,107,236,108,61,231,155,47,62,99,116,124,196,98,167,77,167,213,124,149,121,170,165,118,152,225,56,165,214,152,99,225,226,101,178,60,103,212,59,102,243,217,3,182,159,62,
160,56,29,224,7,1,73,163,233,198,123,194,21,31,74,105,60,165,93,210,149,148,72,237,146,210,76,53,49,167,200,233,30,246,136,231,150,88,88,88,32,159,78,221,152,1,229,14,121,83,98,165,171,108,133,210,248,
90,19,121,146,163,253,61,250,39,35,210,86,3,223,243,168,183,218,4,90,51,155,78,49,194,96,74,48,230,252,250,86,220,156,106,103,32,149,174,222,95,192,22,231,2,89,167,228,81,154,90,173,73,123,241,2,75,107,
235,28,110,63,231,250,239,126,77,191,123,64,187,217,162,145,166,46,125,75,187,196,173,52,169,19,199,9,205,185,85,231,214,205,114,6,221,61,158,61,126,72,119,239,5,138,169,67,66,47,45,35,181,231,66,106,
228,249,50,217,157,35,162,26,115,217,202,69,13,150,211,147,33,81,103,142,78,123,14,91,165,154,137,106,217,237,134,51,238,147,102,0,47,73,152,158,140,233,117,123,76,203,140,185,229,53,124,173,72,210,58,
228,46,66,82,73,137,41,11,132,53,85,183,67,213,105,26,202,60,171,100,177,198,25,183,132,64,121,202,225,201,1,229,5,212,210,38,245,206,50,151,95,123,19,206,102,220,249,250,15,220,251,238,75,32,39,73,235,
72,223,39,47,13,202,147,36,73,141,90,189,73,123,97,141,197,11,87,16,198,160,254,211,255,252,223,254,50,142,82,130,56,116,203,78,65,133,30,176,20,22,242,44,3,161,94,105,116,147,90,132,244,170,177,207,43,
178,186,168,226,186,2,146,180,73,212,108,242,124,103,135,111,62,255,3,91,119,239,227,161,120,251,245,183,249,248,103,31,225,215,99,34,47,34,73,18,130,168,134,31,167,12,103,134,238,97,151,65,191,203,147,
59,223,51,216,120,130,46,12,245,116,142,159,254,249,47,72,87,58,142,237,226,123,238,191,85,65,157,60,173,42,25,156,112,20,63,165,121,249,124,159,230,220,18,158,159,224,41,69,24,133,104,95,99,5,76,167,
51,247,72,41,141,242,3,122,199,125,2,101,41,243,156,210,8,166,179,156,178,20,52,235,13,199,23,169,50,46,61,37,42,121,153,37,175,70,62,74,56,217,162,231,85,4,60,4,158,118,122,218,40,78,16,50,160,222,88,
96,106,4,247,238,222,230,198,239,126,131,56,155,242,222,27,111,243,243,127,245,115,218,75,45,188,208,67,9,143,40,138,136,107,13,140,78,216,57,60,225,96,127,159,254,201,17,143,239,220,100,188,183,133,22,
146,149,197,53,62,252,231,63,38,105,212,153,230,16,6,62,74,73,148,62,127,113,220,65,18,248,33,101,97,40,139,18,33,44,7,187,123,140,70,103,180,23,87,209,231,40,96,225,76,149,84,252,114,23,10,163,72,226,
144,211,241,4,37,115,172,1,63,72,92,192,183,144,196,181,58,182,116,188,239,178,178,149,91,83,34,5,72,45,192,228,85,103,228,6,230,90,58,223,134,172,116,221,218,143,104,207,45,161,147,54,221,254,128,223,
253,227,175,24,110,110,242,225,155,175,241,254,15,223,37,105,213,240,60,133,210,30,158,239,226,225,210,90,3,17,212,57,236,15,232,30,237,243,226,233,67,118,158,220,39,148,83,148,31,176,178,188,198,226,
234,34,210,171,58,80,33,152,21,185,163,158,122,62,69,110,40,75,135,252,53,38,39,207,75,242,204,32,149,230,249,253,187,196,141,6,107,23,175,98,141,32,159,77,171,241,85,53,190,48,214,21,20,210,125,196,131,
64,82,228,99,70,39,35,60,207,93,227,176,150,178,184,184,192,233,241,9,133,41,65,41,202,194,85,252,149,203,200,125,120,12,72,45,95,45,211,141,16,88,83,184,61,79,24,147,36,77,214,223,120,135,172,156,242,
31,255,254,127,199,76,198,172,175,174,82,75,99,148,231,225,233,160,234,24,125,226,196,169,148,22,47,93,35,183,134,163,189,45,54,158,61,96,227,241,125,236,217,136,208,15,152,95,90,65,121,1,94,149,106,165,
148,235,54,221,179,162,156,33,200,84,186,111,235,244,226,198,26,108,153,245,83,193,124,0,0,32,0,73,68,65,84,241,226,251,59,212,47,92,225,242,107,215,16,133,33,203,102,142,199,36,156,130,175,200,254,148,
223,170,181,64,149,5,7,123,91,140,166,57,97,92,71,73,69,173,221,38,14,125,242,233,12,65,233,36,188,101,137,91,7,139,106,254,237,128,141,46,155,215,117,58,174,3,80,40,5,73,45,165,57,191,198,133,215,223,
161,56,61,230,203,223,252,45,131,238,49,43,107,171,52,154,233,171,3,58,136,34,162,40,38,74,234,212,155,203,180,150,46,50,155,206,24,30,31,112,247,214,215,108,62,189,203,108,112,76,173,214,98,110,121,5,
229,123,142,80,171,93,222,173,150,85,215,163,130,234,125,114,76,125,113,206,3,178,37,91,119,238,17,44,46,51,191,184,136,40,161,52,165,35,82,84,152,18,99,220,92,223,15,35,146,180,198,232,232,136,253,253,
93,242,178,160,189,180,2,214,16,55,91,120,66,97,141,33,207,114,12,198,225,24,172,219,127,41,233,200,0,206,15,226,174,175,82,21,128,205,90,148,246,136,107,77,230,22,214,184,120,237,45,146,208,227,222,151,
191,227,214,55,127,192,11,61,154,11,157,234,92,180,248,65,72,154,54,168,213,59,164,157,37,150,86,175,160,172,228,116,60,68,253,219,255,246,191,255,101,81,26,60,63,112,46,68,91,160,100,181,180,1,202,220,
184,234,93,186,118,199,34,177,214,225,82,101,117,209,133,21,4,190,79,156,164,52,58,243,12,179,156,155,223,124,197,147,27,223,146,200,152,31,188,247,3,62,250,217,135,132,73,128,175,165,203,187,141,19,162,
164,65,166,2,182,246,246,233,31,237,243,252,241,3,14,95,60,69,205,102,212,147,14,239,124,242,9,115,151,22,241,148,172,16,240,174,253,114,227,37,129,80,1,6,129,150,30,37,142,199,93,148,57,219,207,55,89,
90,91,199,42,207,89,155,173,123,201,207,102,25,2,131,210,146,108,154,209,104,52,232,29,29,19,215,2,206,206,102,14,27,161,221,162,175,150,52,176,101,137,180,214,45,182,172,11,103,48,198,1,144,60,229,150,
185,90,42,148,170,160,85,162,34,142,10,77,20,181,144,97,194,198,238,54,95,254,246,31,153,245,6,124,248,238,15,248,209,159,127,66,80,11,16,74,224,123,17,97,28,187,176,20,47,230,112,56,101,127,255,144,131,
237,45,110,127,251,5,163,221,23,4,90,179,178,122,145,79,126,254,99,226,102,236,126,183,168,164,132,90,35,21,40,93,181,233,82,82,216,106,33,91,57,31,235,141,26,247,238,220,165,94,75,9,107,77,148,246,171,
48,6,55,102,49,165,155,201,151,198,184,101,184,146,12,122,93,138,124,202,89,54,67,41,143,44,207,29,154,162,209,36,155,77,220,130,79,184,209,144,168,14,71,172,227,169,72,43,48,214,160,149,27,5,154,202,
176,151,214,219,68,245,22,103,86,243,233,175,127,197,246,227,7,252,232,163,119,185,246,222,85,164,116,150,115,237,249,4,81,224,130,116,226,6,50,76,232,158,156,210,59,238,114,176,189,201,246,147,251,104,
50,180,23,179,176,184,202,226,202,18,104,13,22,124,63,164,40,139,63,45,223,148,87,185,72,13,69,225,94,44,83,86,41,76,101,129,86,134,253,173,151,212,231,22,168,183,231,80,126,72,126,118,74,145,229,72,169,
40,172,131,100,41,29,160,195,128,114,150,33,149,100,118,54,38,51,182,34,117,130,14,34,154,173,22,167,195,161,227,242,88,199,97,17,182,194,112,87,149,98,81,24,76,145,189,226,207,136,210,32,148,32,140,82,
22,46,92,193,144,243,219,255,231,255,162,60,61,101,121,121,5,63,142,43,53,141,155,109,107,229,189,202,77,104,45,95,32,71,210,239,238,177,245,236,33,7,155,207,80,54,35,138,99,86,214,47,163,163,192,85,161,
218,199,216,63,141,154,140,21,120,74,33,132,198,224,156,192,165,113,17,141,2,71,143,21,228,108,61,122,72,184,184,198,218,133,53,180,112,239,138,169,88,66,174,34,47,157,82,196,247,209,74,48,27,79,56,62,
234,226,197,41,113,154,34,128,40,109,16,249,33,179,179,83,87,220,203,42,53,202,80,1,12,169,48,229,2,85,201,66,149,148,238,217,241,125,234,245,14,203,23,174,18,7,146,127,248,247,255,27,189,238,17,23,214,
215,9,147,216,141,58,148,118,185,12,129,203,78,72,210,14,245,197,85,164,231,49,234,29,241,228,193,247,236,60,187,143,204,39,180,90,115,44,95,88,199,143,67,167,74,242,170,67,222,243,220,161,234,121,21,
3,74,185,204,12,23,25,228,58,70,173,240,180,224,233,215,55,73,47,172,176,182,122,17,81,226,58,94,1,66,251,213,120,46,119,18,101,79,19,106,201,224,224,152,209,240,132,18,75,82,111,224,41,69,144,212,80,
149,40,196,24,151,186,230,150,220,246,21,130,252,156,181,47,206,157,241,210,45,144,181,31,82,111,45,50,183,122,137,185,185,57,30,126,245,5,55,174,127,78,220,168,209,158,235,32,171,241,187,231,123,4,81,
76,88,75,73,210,22,237,249,21,144,30,179,211,49,91,207,158,162,254,229,95,253,139,95,154,82,98,114,139,242,92,64,183,227,142,72,140,41,156,122,165,52,72,173,177,184,182,216,228,133,227,55,4,110,153,105,
141,107,33,154,173,5,68,24,113,227,214,119,124,247,217,167,212,101,194,47,254,236,103,188,253,201,53,116,160,220,34,205,243,209,129,211,122,23,42,98,231,168,203,246,230,6,207,31,223,99,247,209,3,116,9,
105,125,137,31,255,226,231,44,93,93,116,144,44,237,254,46,139,12,165,53,158,14,81,58,192,90,197,44,203,9,2,191,242,46,8,226,154,207,209,225,17,221,173,61,230,214,214,49,202,175,92,105,210,89,222,139,18,
165,93,85,27,133,190,83,169,12,70,196,181,128,211,225,169,155,199,122,33,88,73,189,209,68,72,251,106,14,108,108,213,209,84,55,130,234,58,105,37,241,149,172,226,5,65,123,41,113,115,142,189,193,128,191,
251,119,255,14,51,24,242,87,127,249,11,222,248,232,13,140,48,4,65,128,167,67,162,36,113,212,204,184,206,222,224,140,173,173,61,118,54,95,242,224,251,239,24,109,110,16,107,159,107,87,222,224,157,159,252,
136,70,59,37,47,10,180,210,148,22,167,166,192,144,23,134,32,140,241,188,160,146,140,186,109,97,81,58,199,166,246,52,97,232,243,252,209,3,234,141,38,202,143,209,65,132,244,52,90,73,167,126,147,238,218,
2,196,113,192,217,100,70,183,219,197,154,156,217,217,25,216,146,50,51,76,51,75,163,217,194,228,174,37,21,82,186,235,41,45,121,158,187,80,149,42,5,72,41,85,69,75,90,172,242,73,91,115,100,120,252,234,255,
254,27,14,159,60,229,39,63,252,144,139,111,92,32,71,17,248,193,171,74,52,8,19,226,122,3,225,197,108,236,245,57,57,25,240,248,193,109,246,158,221,71,151,19,146,176,198,234,218,58,243,203,43,21,214,89,87,
11,40,89,205,65,165,91,26,74,141,86,30,165,197,189,92,101,225,14,93,91,25,156,148,130,162,228,229,211,71,212,219,115,36,173,14,141,214,28,38,207,153,142,207,208,218,241,200,133,146,100,211,9,179,89,134,
16,130,211,201,144,211,147,19,178,188,36,140,99,242,162,196,79,98,154,157,57,102,195,97,53,32,169,36,155,166,160,52,238,99,67,145,187,162,192,128,164,202,190,85,130,206,194,5,146,118,202,111,254,246,255,
164,24,143,88,190,120,17,207,247,43,118,186,172,150,172,10,63,8,209,126,66,163,179,76,46,61,166,211,83,54,158,222,103,231,249,67,164,201,168,167,53,58,157,37,180,239,208,214,2,129,17,10,37,28,6,192,10,
80,82,187,116,57,63,168,130,236,29,2,219,173,173,148,91,82,250,33,229,217,144,251,223,221,36,152,91,96,229,194,5,210,70,74,49,113,210,75,85,21,28,214,184,196,43,79,251,40,107,152,140,134,76,78,167,248,
73,236,84,114,82,225,39,169,219,9,204,102,78,51,103,138,170,8,48,85,1,233,198,128,84,191,211,41,234,28,15,104,110,105,157,217,217,144,79,255,238,223,51,153,78,89,186,184,236,162,9,165,192,147,78,145,230,
7,30,81,84,35,140,91,68,205,37,138,194,208,219,221,228,197,211,251,236,109,60,132,124,66,187,179,196,202,197,117,252,56,168,194,72,170,142,184,114,210,74,225,70,37,126,20,35,43,55,185,45,243,138,135,227,
20,76,58,8,176,147,33,183,126,255,37,245,139,171,172,92,88,35,240,99,202,172,192,96,93,167,100,44,69,158,97,133,37,105,214,97,154,177,191,183,79,183,123,132,142,93,97,135,53,132,141,38,62,138,178,156,
185,121,126,5,94,19,234,252,195,167,171,176,38,249,202,31,98,45,248,97,66,103,249,34,203,203,43,220,251,221,167,220,248,230,11,230,86,230,168,87,35,63,173,21,190,167,241,2,183,11,76,26,109,58,11,107,96,
93,119,118,176,241,130,167,247,111,162,126,241,243,95,252,82,89,72,234,41,121,97,240,180,79,148,36,175,228,102,162,154,223,157,107,70,165,0,173,53,158,231,82,237,101,117,227,180,10,104,206,47,243,120,
227,5,159,255,234,215,52,68,194,159,255,139,159,177,112,121,222,125,201,165,118,225,26,190,143,31,212,208,113,141,167,155,187,108,111,109,242,252,193,29,14,30,63,197,156,157,209,76,90,188,247,225,71,204,
95,93,113,202,14,93,209,23,149,247,42,252,35,8,34,132,31,86,252,105,55,245,179,66,84,173,145,192,15,3,158,62,122,68,168,61,226,180,78,97,149,211,56,123,46,183,82,42,119,88,154,162,36,12,35,102,89,198,
224,184,135,210,130,188,82,149,40,165,40,12,68,81,82,165,253,84,149,137,45,161,116,33,22,178,82,7,41,45,240,60,191,146,115,65,24,53,56,153,230,252,238,215,191,70,15,199,252,236,207,126,202,226,250,156,
11,28,151,238,80,59,15,117,246,163,26,71,227,25,47,158,189,100,119,207,193,231,250,91,47,168,135,17,87,175,92,227,147,95,252,136,168,22,186,127,183,242,156,244,76,107,60,207,45,143,74,35,9,194,26,94,16,
84,114,192,106,105,88,186,145,142,49,134,40,10,49,166,160,127,124,68,89,185,74,117,152,160,61,31,107,75,247,17,245,125,55,159,55,16,39,33,211,233,172,154,111,143,41,74,104,117,90,152,74,182,91,171,187,
232,67,183,236,119,21,125,105,156,17,76,216,18,93,181,163,2,129,149,30,37,18,47,76,248,250,139,235,76,143,142,120,251,253,55,105,45,117,42,164,129,192,147,110,161,232,5,161,243,2,248,17,27,123,3,198,163,
9,79,31,221,97,243,209,29,68,54,163,89,175,179,126,241,146,11,0,23,184,195,30,235,116,241,200,202,253,235,112,9,202,11,42,21,145,227,220,91,83,82,22,182,90,204,186,249,168,14,66,132,205,57,216,221,228,
52,43,137,210,58,105,187,195,116,58,114,70,195,162,64,85,133,134,169,212,59,10,73,81,204,24,159,116,65,73,124,207,163,180,2,229,135,164,141,58,211,225,192,201,60,75,83,181,250,134,50,119,68,86,37,37,66,
59,226,166,235,52,3,252,56,230,238,215,95,225,73,225,94,222,42,109,238,156,154,168,165,64,123,62,90,7,132,141,14,165,244,65,88,54,159,220,103,255,249,99,108,126,70,90,75,105,54,231,81,65,132,213,194,85,
177,66,34,61,31,173,60,172,41,171,81,149,114,1,223,74,87,89,0,96,140,147,13,158,79,147,13,22,29,4,152,217,41,247,110,222,100,140,71,115,174,195,220,220,28,202,226,188,11,82,56,125,125,149,188,230,249,
62,210,150,140,6,125,14,14,14,208,158,135,176,22,37,21,81,82,39,244,61,178,233,89,181,252,181,85,81,32,171,241,49,14,139,34,165,91,10,155,146,32,170,17,213,82,238,94,255,28,207,83,52,231,218,142,227,238,
254,66,107,129,246,36,202,15,73,146,38,126,210,113,96,193,124,202,198,227,251,236,189,124,72,62,29,49,55,191,194,220,210,34,158,23,184,241,98,53,250,116,226,5,42,199,170,69,121,161,187,38,85,167,99,94,
101,213,58,105,109,105,13,81,28,51,57,232,114,231,219,27,20,81,72,220,105,209,104,54,49,89,94,141,101,68,149,13,224,150,187,181,52,194,76,166,28,119,143,152,140,78,144,190,194,87,10,33,20,81,179,129,174,
76,174,252,127,76,189,87,175,101,91,122,158,247,140,57,102,158,43,238,84,185,78,236,196,142,36,69,138,109,137,20,108,192,134,109,9,144,1,194,176,117,33,25,150,100,195,134,229,11,251,198,128,175,206,159,
49,12,9,50,108,201,148,8,83,20,69,72,144,68,178,3,217,205,238,211,221,39,135,170,218,57,172,52,211,72,190,248,198,218,135,23,133,6,10,56,187,122,175,53,231,24,95,120,223,231,85,146,41,176,255,25,137,138,
184,233,68,58,65,1,32,166,148,205,140,7,143,159,241,225,247,255,132,247,127,241,19,22,15,150,228,85,21,199,96,82,116,10,83,167,161,153,29,48,153,158,160,178,134,34,207,184,121,241,49,63,253,225,31,113,
241,249,207,208,191,241,157,95,121,71,110,93,75,89,53,56,149,160,139,156,60,47,100,20,130,164,255,160,228,165,209,49,211,84,41,40,82,73,14,130,148,186,154,178,182,3,127,248,59,191,203,131,114,201,95,254,
173,95,227,232,201,146,209,72,229,88,53,21,121,81,144,232,156,106,118,192,203,203,91,62,255,252,51,222,255,233,143,56,125,247,199,184,93,199,98,114,196,175,255,214,119,121,252,214,83,92,146,160,148,39,
213,42,166,210,203,114,37,209,9,101,89,145,232,130,60,43,40,242,76,42,111,229,176,70,86,80,105,154,82,54,37,31,253,226,231,162,83,47,167,16,52,85,45,35,145,132,32,220,29,235,196,125,153,167,236,118,29,
110,236,240,193,48,14,189,132,131,132,4,99,3,147,233,84,46,181,68,248,233,193,217,251,42,63,205,36,95,22,165,163,35,15,70,7,63,248,227,63,165,118,158,95,254,141,111,50,89,54,114,24,199,240,11,157,229,
16,82,38,139,25,157,75,120,239,253,207,56,59,61,229,221,31,252,9,155,151,159,82,106,197,55,191,241,109,190,243,155,191,70,57,47,35,142,64,209,27,79,223,143,52,17,92,38,69,138,232,230,171,162,136,7,160,
28,192,214,89,33,67,106,77,146,64,93,215,152,113,228,252,226,140,235,219,13,90,139,33,108,50,157,145,40,47,23,107,112,56,99,48,198,48,157,212,172,87,59,198,113,100,236,91,214,155,150,96,71,249,61,146,
140,102,177,64,35,5,65,112,49,51,85,199,170,52,170,156,136,21,147,181,150,87,159,191,34,25,123,158,188,246,148,170,201,73,32,30,68,210,70,231,121,78,217,204,168,166,51,174,238,6,174,215,3,47,62,251,144,
159,125,255,223,227,135,150,227,229,33,95,249,165,111,176,56,94,10,30,87,107,209,57,71,242,217,30,82,38,31,140,166,46,101,169,71,36,30,90,235,98,176,135,188,92,196,84,51,145,180,90,238,206,95,176,27,2,
101,221,112,120,124,204,98,58,103,117,121,137,177,163,60,227,65,84,53,73,28,109,14,67,203,230,118,37,166,28,132,205,147,86,53,117,213,48,108,186,216,105,249,72,213,148,133,167,214,50,159,13,126,255,50,
167,220,221,92,202,161,94,230,81,242,199,61,83,94,199,16,147,188,172,201,171,57,197,236,16,143,231,226,243,15,248,240,23,127,198,176,91,115,116,112,194,226,80,212,56,137,78,165,74,188,87,198,196,149,162,
247,132,68,138,152,73,189,192,143,150,16,85,58,17,249,79,80,46,202,4,19,116,158,83,55,21,195,234,154,247,126,242,19,58,149,243,240,209,9,211,197,130,66,167,140,195,0,90,70,87,242,89,106,138,34,103,108,
59,97,247,92,93,51,157,77,193,121,92,146,80,206,230,52,121,73,223,247,50,183,119,163,140,48,66,244,190,40,200,98,200,183,115,178,224,190,252,236,19,145,60,150,153,244,76,209,220,151,196,113,102,154,149,
84,245,156,114,122,66,82,45,168,167,21,231,159,254,130,143,127,254,3,134,118,197,225,241,3,142,31,61,67,231,5,42,85,145,25,164,239,199,82,162,201,72,32,64,86,52,148,101,45,197,67,220,65,133,56,254,19,
98,172,39,201,50,154,101,195,229,199,159,242,163,31,252,128,142,192,195,55,223,224,96,177,20,233,165,51,130,211,144,233,38,42,213,52,211,154,225,110,195,234,230,26,231,122,154,166,20,41,116,38,25,27,89,
72,226,179,224,227,200,88,69,83,100,46,59,201,68,16,217,74,9,150,229,250,197,103,92,158,126,70,125,48,35,207,83,201,44,32,144,166,25,105,154,147,230,5,117,51,103,114,240,16,149,206,41,167,83,124,119,199,
247,255,240,247,121,245,217,207,112,36,232,191,242,221,239,190,19,236,32,122,118,239,41,171,134,209,90,18,82,234,102,34,88,215,52,193,217,65,22,47,137,200,188,36,2,48,187,255,71,73,52,63,250,254,247,120,
178,88,242,246,183,222,162,168,75,193,165,58,79,145,150,164,69,74,8,208,76,150,92,108,59,62,253,228,51,222,123,247,199,188,252,217,79,240,237,192,195,163,39,252,218,95,251,171,60,126,243,33,89,38,26,233,
60,77,238,95,48,157,236,221,141,30,235,51,138,122,74,154,102,232,60,197,163,24,134,62,102,104,90,180,86,84,77,205,208,143,236,110,175,233,123,71,162,50,72,83,234,102,38,172,107,37,244,67,103,13,33,88,
170,186,161,109,183,164,137,98,187,89,99,251,30,20,184,160,99,136,196,60,222,166,66,213,84,62,16,18,145,35,42,196,184,230,66,192,152,129,203,139,107,22,117,201,131,103,39,168,68,228,126,65,37,18,110,158,
151,100,121,74,51,157,225,210,154,247,63,121,197,197,233,41,239,254,224,143,185,121,241,17,85,146,243,237,111,255,50,95,255,203,191,2,177,138,87,104,28,41,171,117,43,41,63,149,32,106,85,240,244,22,188,
202,41,203,10,216,179,187,69,119,30,136,160,42,68,249,130,10,36,120,218,221,10,173,68,190,233,17,24,153,119,142,60,149,246,218,58,11,202,82,54,83,110,238,182,16,44,253,118,195,208,203,223,147,40,130,202,
153,77,167,81,82,38,139,185,253,33,165,163,161,40,68,64,136,247,134,44,77,41,155,138,68,121,25,105,68,201,159,214,217,189,161,167,104,230,216,144,241,242,252,150,143,63,122,143,63,251,119,127,64,191,185,
227,245,199,79,248,250,183,191,69,49,157,160,116,4,161,37,105,148,181,137,68,110,127,192,2,56,99,9,105,205,193,195,71,130,199,112,1,111,70,89,152,89,131,71,140,100,118,28,133,148,169,83,234,82,177,91,
223,145,86,83,178,60,163,154,205,56,56,60,166,187,219,96,199,142,61,12,93,37,194,216,48,195,200,237,205,45,206,180,36,186,0,143,20,32,117,195,100,62,163,93,221,137,218,34,46,211,247,12,226,224,165,112,
218,87,143,251,84,165,16,156,92,150,81,155,109,189,18,14,84,146,81,215,75,78,158,190,197,232,29,159,125,252,115,222,253,254,191,101,108,91,158,62,121,206,100,177,36,209,242,14,136,218,47,8,171,38,78,133,
247,1,149,90,254,17,202,201,146,163,147,19,92,103,4,6,167,191,120,118,85,144,203,38,196,42,124,82,215,108,111,111,248,236,163,143,57,122,254,134,228,102,228,37,117,221,96,250,1,167,156,116,5,78,146,173,
170,178,100,183,94,115,119,119,203,102,181,33,45,115,180,10,232,52,103,178,92,146,170,4,51,12,114,128,6,43,207,171,18,15,208,61,182,43,120,140,21,217,176,140,5,21,214,5,84,28,191,200,242,186,32,175,167,
148,147,37,147,197,35,172,243,124,244,179,31,242,179,239,253,107,198,190,229,225,227,231,204,15,143,69,70,157,132,248,140,169,88,132,68,122,169,74,98,78,68,66,94,205,88,30,30,146,4,21,163,79,163,100,210,
75,48,16,49,17,79,103,25,101,153,243,234,227,23,156,191,58,101,241,232,1,77,51,101,178,60,164,208,25,118,28,72,18,72,241,88,63,146,149,25,147,166,97,115,121,199,213,249,41,155,221,142,188,158,162,80,164,
121,193,100,54,23,134,145,143,196,223,104,128,74,226,184,73,10,73,113,110,247,93,71,63,116,232,50,39,213,73,148,2,39,164,137,22,163,97,154,145,85,21,205,242,152,233,225,99,178,172,160,189,121,201,247,
254,224,119,121,245,226,35,188,135,229,179,103,232,191,251,247,254,206,59,231,167,103,18,111,39,121,55,148,197,132,160,18,202,170,33,205,51,188,55,224,45,193,143,128,0,255,67,144,155,197,227,113,206,179,
221,182,204,234,138,249,225,244,11,249,153,87,98,136,136,21,64,154,87,248,162,230,189,15,62,226,227,15,223,227,163,31,126,31,183,235,120,254,232,77,126,253,183,254,50,71,207,142,201,139,84,20,56,89,18,
219,62,5,58,65,39,69,156,135,6,218,94,209,52,75,210,44,19,185,101,92,66,202,128,52,206,197,188,103,50,157,112,126,118,197,108,94,201,151,156,231,88,227,152,78,103,164,90,90,74,235,92,124,152,2,69,93,114,
126,126,137,194,49,244,99,156,47,122,116,94,145,229,5,101,221,72,117,31,85,14,206,57,81,132,164,9,206,75,0,136,138,42,32,165,99,37,19,3,147,147,68,218,185,44,203,64,39,148,245,140,203,213,192,123,239,
127,200,79,191,255,199,220,189,252,148,130,140,223,252,173,255,128,175,253,218,183,208,121,38,110,103,173,32,36,164,121,70,211,212,18,91,87,74,71,17,124,96,28,44,31,125,248,130,7,79,159,161,210,76,14,
95,37,151,164,179,123,87,176,44,130,170,42,167,219,14,20,85,193,118,115,7,186,144,185,99,80,212,179,69,60,180,101,214,221,245,178,176,109,154,154,179,87,167,24,211,211,247,91,148,87,120,103,208,69,73,
64,20,70,105,34,213,161,55,54,66,202,16,168,88,72,240,74,228,141,222,121,233,4,226,97,151,231,18,0,173,18,113,72,151,141,64,160,76,200,249,244,179,143,249,183,191,247,207,240,237,134,175,190,245,22,223,
252,229,175,83,206,106,217,81,56,31,225,91,250,222,200,131,146,165,104,8,30,107,37,125,232,230,236,140,49,104,30,189,246,6,248,64,187,89,75,165,77,192,59,199,229,205,173,140,133,144,192,147,68,67,130,
229,226,252,12,210,2,51,56,234,197,140,131,227,19,118,183,43,172,25,216,83,210,156,181,104,37,243,239,160,12,221,118,67,146,22,100,185,32,115,211,170,162,200,114,250,245,150,40,191,32,120,19,71,6,68,84,
73,204,132,141,227,194,176,15,220,112,226,86,21,5,137,38,47,166,28,156,60,225,240,249,83,62,255,240,39,188,251,253,127,199,208,13,60,127,237,13,166,81,77,150,36,113,55,225,149,152,134,180,28,102,42,136,
180,120,143,4,9,193,113,119,125,201,16,114,222,248,218,151,9,221,128,49,61,169,78,200,210,244,254,179,241,193,73,30,130,22,71,238,234,230,146,179,243,75,234,197,2,2,76,230,7,44,102,83,186,245,70,46,147,
68,225,131,228,70,103,137,198,116,29,171,213,45,219,205,150,249,225,17,193,58,116,85,49,93,44,72,131,98,28,6,130,113,145,180,42,18,68,228,107,148,247,200,131,138,158,17,34,178,57,4,153,255,139,226,40,
167,158,28,176,124,240,26,211,249,130,87,239,253,152,239,253,203,127,78,223,141,60,123,237,185,152,192,180,92,24,90,73,193,22,21,187,226,145,65,114,121,247,207,234,102,189,98,187,27,120,242,230,27,96,
28,227,32,5,154,8,82,130,44,57,226,197,153,215,21,218,7,238,110,174,89,173,111,41,151,75,81,91,205,102,84,121,46,221,143,82,81,186,156,200,179,144,151,220,93,222,176,186,187,37,40,152,46,166,4,235,73,
116,70,49,105,192,184,61,163,90,68,51,169,190,247,187,137,59,222,75,154,86,228,28,201,248,71,76,115,206,10,165,53,43,50,202,122,206,193,131,103,76,154,41,55,159,127,202,31,253,139,223,225,244,229,7,28,
30,31,243,228,205,55,56,58,62,64,255,221,191,247,223,190,83,212,13,167,159,190,192,187,145,221,238,14,59,12,52,205,84,0,92,121,78,86,22,251,109,160,72,215,162,9,39,32,52,60,173,82,20,9,69,81,136,180,40,
64,154,132,251,91,178,40,4,253,90,212,11,62,57,191,226,39,127,250,67,222,255,222,159,48,110,123,94,127,254,54,127,237,175,255,39,212,71,13,38,50,57,108,176,24,235,228,182,77,53,206,4,172,147,27,79,41,
197,221,122,199,110,51,210,204,15,35,144,75,139,85,94,39,56,39,0,43,188,35,205,82,234,233,140,179,151,175,80,137,165,107,91,81,157,140,150,217,242,136,188,40,80,56,210,60,35,73,37,195,116,50,155,114,250,
249,185,240,172,131,176,215,9,138,180,40,104,187,129,73,35,25,182,62,56,180,10,95,224,27,146,132,113,24,24,70,135,86,9,198,74,242,150,204,58,147,123,207,128,74,21,105,214,64,81,115,118,117,195,143,254,
253,191,230,243,159,255,148,71,203,35,254,211,191,254,31,243,250,215,95,71,66,166,84,4,162,229,247,146,207,52,77,169,202,140,68,37,12,131,69,165,41,195,96,169,171,148,31,253,240,93,14,30,60,35,201,170,
232,23,248,162,190,19,39,169,0,159,116,154,210,109,123,178,28,206,79,207,168,170,9,129,4,27,130,176,54,16,57,154,78,50,172,181,52,117,206,241,201,9,175,62,191,160,109,183,12,67,139,71,33,16,205,82,98,
236,154,217,189,68,87,100,137,1,149,10,206,98,28,70,172,145,160,235,189,210,202,199,42,75,48,70,129,52,205,153,76,151,100,205,130,15,62,254,128,223,255,39,255,152,38,56,126,253,87,191,195,151,191,241,
37,116,153,67,208,56,151,196,139,51,193,26,145,198,201,129,47,219,106,227,93,148,202,201,110,224,244,147,79,89,173,118,188,254,213,175,83,53,19,108,219,98,172,39,73,114,186,177,21,150,120,28,25,142,163,
165,204,27,202,204,240,234,179,87,146,207,138,71,23,21,39,207,158,209,175,55,140,99,143,78,66,196,39,128,206,52,221,182,227,118,115,203,208,173,98,158,107,64,233,132,201,193,17,69,145,179,89,175,132,38,
25,189,29,225,30,250,225,247,126,27,121,79,130,244,68,42,42,210,210,68,28,149,211,249,17,175,255,210,215,57,127,249,17,255,234,119,254,31,10,173,121,227,141,215,41,107,9,4,81,17,76,166,18,193,139,200,
184,85,199,145,87,100,29,165,242,57,43,209,18,114,246,225,251,244,62,231,75,223,252,38,133,214,140,125,127,223,45,237,35,63,194,126,124,82,164,4,111,89,95,95,114,115,117,75,53,153,96,140,129,44,231,224,
240,24,219,13,56,60,105,154,226,173,65,151,25,147,186,198,182,45,151,23,23,220,109,55,148,85,137,25,70,242,102,194,108,121,4,214,8,123,39,88,49,245,5,238,11,35,209,1,39,242,153,69,71,234,254,243,82,9,
164,89,70,53,93,114,248,240,53,14,30,62,225,226,227,63,231,123,127,240,207,80,105,202,219,95,123,155,122,214,200,8,200,121,146,52,137,163,96,25,67,167,89,38,129,71,137,138,159,190,92,36,74,43,214,103,
175,248,252,197,57,175,125,237,107,228,73,198,96,134,24,72,174,4,163,225,36,15,55,77,51,38,179,134,208,182,124,246,217,167,172,111,87,212,243,25,222,7,138,233,140,166,172,112,189,137,41,113,10,23,60,205,
98,194,116,82,114,115,126,201,234,230,134,97,28,169,38,13,202,131,206,75,38,243,133,76,12,98,231,25,188,141,50,99,238,3,225,247,241,164,178,32,150,130,192,57,49,87,233,60,165,168,231,28,60,124,141,227,
7,79,105,175,206,249,222,31,254,46,151,23,47,121,244,250,51,142,159,62,69,103,25,222,58,244,223,250,91,255,213,59,121,150,83,54,21,23,103,167,36,9,12,227,136,183,142,201,98,65,80,9,121,90,136,205,215,
7,172,29,69,78,20,228,139,200,148,28,22,187,126,36,85,160,180,23,44,175,10,168,92,36,69,90,105,138,122,142,213,57,31,124,244,62,63,253,163,63,198,238,12,223,248,234,55,248,229,223,248,21,170,163,37,195,
96,176,54,196,202,45,1,196,104,34,198,8,141,139,149,68,136,135,235,139,87,175,192,56,234,249,161,72,169,66,144,67,50,205,4,240,117,207,173,16,103,108,112,61,171,187,59,130,11,100,69,33,220,252,178,68,
103,41,214,140,50,43,35,160,147,192,108,54,229,234,242,26,235,58,116,94,50,155,78,72,34,130,54,160,40,139,34,114,52,220,189,28,139,36,193,152,65,242,75,99,75,156,38,162,148,17,66,97,26,143,196,140,217,
252,144,213,104,248,147,127,243,111,248,232,199,63,230,245,135,143,249,171,255,209,95,225,224,217,9,198,73,126,106,26,191,72,231,194,61,208,105,47,99,115,62,46,141,83,113,74,234,4,238,110,111,184,120,
121,202,201,195,167,4,157,201,3,18,36,148,221,58,47,252,118,239,201,146,64,94,102,180,219,142,44,85,92,95,221,80,20,66,219,28,123,71,61,93,144,105,161,41,134,24,99,151,21,57,139,197,130,243,211,43,118,
187,150,193,88,84,128,44,139,232,136,162,162,40,11,18,172,140,200,226,202,203,89,135,25,122,84,146,224,125,136,6,151,4,99,198,56,231,79,72,208,76,166,115,234,197,17,103,151,215,252,147,255,243,255,128,
126,224,47,253,234,119,120,237,237,231,144,40,156,147,99,210,123,35,11,205,56,186,73,117,26,193,83,145,107,51,58,89,174,70,184,93,162,2,183,151,231,160,51,30,60,127,157,122,58,103,236,123,134,161,167,
200,115,210,0,214,244,132,168,236,81,64,146,130,31,183,172,110,54,20,77,67,94,148,24,167,56,126,252,136,177,237,176,102,136,51,101,8,137,84,210,182,31,216,117,59,204,184,67,103,37,214,65,53,159,50,157,
207,73,28,12,125,119,239,94,223,19,19,247,7,191,143,206,110,129,148,9,203,41,81,226,252,108,38,51,30,191,241,37,46,175,95,240,135,255,244,159,146,233,148,7,143,31,162,211,44,174,42,66,172,94,247,97,219,
98,10,146,144,122,33,130,250,136,60,223,239,5,64,145,23,154,87,31,188,135,213,57,79,223,124,147,60,207,241,163,193,89,75,166,35,95,199,199,131,63,136,18,39,140,35,231,167,167,120,227,41,107,145,70,122,
157,178,56,58,194,237,58,172,179,114,96,7,200,203,44,206,244,91,110,111,110,232,135,145,188,168,72,180,34,175,42,38,179,217,189,73,77,57,127,159,8,21,246,64,162,224,226,216,84,46,116,7,241,29,8,228,229,
148,217,242,1,199,79,94,227,246,236,99,254,197,255,253,143,200,171,146,231,111,190,78,94,228,162,213,211,153,96,210,163,144,67,197,228,55,157,102,194,193,137,14,215,125,250,150,119,242,140,191,252,249,
123,220,182,45,207,190,244,22,69,86,96,199,61,206,88,10,72,235,12,206,25,18,173,105,166,13,219,235,91,86,235,91,145,29,79,231,224,19,116,85,210,212,149,116,187,81,121,67,240,148,101,65,150,104,54,55,119,
220,220,222,96,140,161,90,44,72,117,74,86,87,84,101,33,239,104,112,127,129,228,26,49,38,137,96,183,241,196,160,42,249,152,246,148,211,44,47,153,30,60,224,209,107,111,81,120,195,31,254,147,127,204,197,
213,41,79,94,127,141,197,193,18,149,168,152,196,21,208,255,221,127,255,247,223,193,91,234,166,34,45,115,206,95,188,34,211,176,235,59,240,158,233,124,41,220,15,37,97,5,33,4,145,89,41,57,124,93,144,214,
197,56,131,143,65,208,42,4,209,60,35,240,177,44,173,104,14,79,248,224,229,167,252,235,223,249,127,25,111,91,190,253,157,95,229,91,223,253,54,73,33,137,83,131,17,135,162,15,154,128,164,33,161,11,156,19,
135,40,202,163,83,29,177,169,158,186,169,248,243,31,255,152,217,116,78,86,207,200,242,82,228,136,214,200,101,163,68,77,49,142,150,217,124,198,102,181,37,83,150,235,155,91,97,117,164,154,174,29,68,214,
85,84,224,61,105,158,17,188,101,210,148,76,167,83,78,95,93,208,109,55,172,55,43,70,99,208,42,97,50,159,17,72,169,202,66,28,185,97,188,159,205,238,15,159,224,3,90,121,204,62,12,218,7,116,38,70,169,233,
116,129,205,107,254,232,223,255,17,127,254,135,255,138,175,191,245,54,255,225,127,246,91,84,203,154,113,16,108,132,138,47,218,158,92,173,212,62,107,53,197,186,32,14,195,189,156,45,4,156,55,212,77,197,
233,139,207,232,119,59,102,139,67,72,50,242,44,143,106,29,169,0,199,97,192,185,17,103,45,169,206,216,110,215,180,237,154,235,139,107,202,170,2,157,176,235,6,170,233,2,173,19,188,55,20,89,130,53,134,162,
44,121,112,114,200,233,203,51,250,110,199,208,14,146,100,148,37,212,243,5,36,41,77,153,139,97,111,108,165,19,68,232,154,1,135,247,58,50,126,2,73,34,135,29,145,169,50,63,124,196,249,205,29,191,251,15,255,
33,71,117,205,175,252,165,239,112,112,178,128,4,172,151,54,63,184,47,150,90,50,182,18,8,154,74,82,97,27,25,177,234,123,31,205,86,17,30,167,211,132,207,63,122,159,52,77,201,103,51,142,30,62,33,9,9,235,
171,75,98,144,173,128,173,92,220,181,56,69,89,105,250,237,138,205,245,134,114,54,103,50,153,210,14,35,15,159,61,199,118,61,99,39,188,24,175,2,169,74,200,179,2,55,142,116,99,203,118,189,194,4,37,32,188,
106,194,108,185,96,104,59,172,53,24,51,202,247,17,226,11,29,185,59,73,72,162,34,78,221,35,13,116,154,115,252,248,57,221,184,227,223,253,222,255,199,100,58,225,241,147,7,81,193,17,11,0,244,189,50,43,81,
73,236,22,4,248,181,191,92,65,76,77,73,172,16,181,146,220,130,4,199,233,7,63,167,179,138,163,103,79,153,31,30,146,132,192,216,245,160,17,113,134,151,81,93,154,229,20,89,198,208,110,57,59,125,73,158,165,
52,147,26,188,199,120,88,62,56,198,246,173,236,4,226,142,43,47,75,170,58,163,111,91,86,215,87,220,222,221,196,162,71,51,61,60,162,105,26,76,215,99,237,32,69,83,60,220,67,220,9,168,72,145,220,243,226,173,
183,40,165,168,167,11,30,62,127,155,211,15,223,229,123,127,248,251,84,85,197,193,163,135,194,77,10,9,74,9,18,59,73,37,186,210,17,34,74,66,147,102,165,196,8,198,241,171,143,84,131,125,148,99,94,36,188,
255,253,31,178,26,7,94,251,242,151,153,76,166,104,27,68,54,25,65,115,50,242,10,232,188,160,41,75,110,206,174,185,189,185,166,40,82,170,73,35,135,118,154,50,153,76,241,214,236,27,109,116,170,153,45,231,
84,121,193,213,171,115,214,183,87,140,163,161,92,72,250,93,51,155,201,20,192,11,86,218,152,158,96,133,189,99,237,222,237,25,159,254,168,158,84,74,140,90,213,124,201,131,103,111,67,223,241,7,255,215,63,
226,236,250,156,71,111,190,70,51,153,16,130,195,57,65,127,104,165,209,255,227,255,240,15,222,201,114,13,222,82,87,21,89,89,112,241,234,21,206,143,108,54,27,148,135,166,153,97,28,84,85,37,227,6,229,101,
166,25,28,33,88,156,139,219,101,37,51,118,27,15,25,235,2,137,74,89,44,79,184,234,182,252,155,223,253,231,152,155,142,95,250,198,55,249,234,119,190,138,77,160,107,7,145,71,41,153,3,18,103,246,74,107,234,
170,33,77,11,124,176,66,123,116,162,59,87,104,202,34,67,23,25,31,254,236,125,22,179,92,137,168,141,0,0,32,0,73,68,65,84,25,94,103,114,232,195,125,38,167,117,1,19,151,117,77,51,225,110,189,38,75,61,87,
23,215,20,101,137,78,51,156,117,228,89,65,213,52,98,200,73,53,214,90,38,147,138,249,114,206,249,217,5,195,110,77,187,218,66,8,52,211,57,58,21,46,117,89,230,24,99,100,169,23,156,192,183,140,141,141,187,
199,218,125,124,153,44,81,81,9,197,116,201,15,254,244,199,188,247,199,223,227,55,255,202,175,243,181,95,254,10,89,83,208,143,70,110,96,29,171,189,44,187,167,84,170,68,0,74,121,33,135,114,170,83,185,20,
188,193,196,185,120,32,165,170,115,206,95,126,198,216,245,232,188,146,252,204,178,138,221,142,195,123,4,113,108,60,69,41,35,155,4,79,183,93,115,119,181,166,154,79,241,120,76,111,168,155,185,200,87,181,
24,67,156,177,168,52,163,174,39,108,87,107,186,118,77,215,110,24,140,161,42,43,82,149,147,150,21,69,158,18,172,163,239,132,51,99,141,69,33,200,102,29,101,173,54,72,120,138,53,18,198,62,56,248,163,223,
255,151,60,58,168,121,251,107,175,209,76,27,156,115,216,125,229,238,3,193,17,131,165,101,238,107,61,120,164,179,11,177,74,116,65,76,113,206,216,200,33,17,110,139,86,129,235,203,151,220,93,173,169,15,230,
44,31,28,51,159,206,217,174,214,24,107,196,75,98,93,100,255,199,101,103,10,155,187,43,134,109,15,105,142,206,53,131,241,28,62,122,140,235,7,204,48,64,176,4,25,162,82,166,57,99,215,209,118,29,55,87,87,
244,131,37,47,115,170,233,132,166,153,50,110,119,152,113,20,79,64,116,56,7,220,61,116,205,5,135,71,180,223,73,146,144,23,13,36,138,119,127,248,125,102,203,57,205,180,34,73,164,16,8,65,197,144,243,191,
160,56,81,123,129,3,100,69,65,30,153,66,73,34,3,145,160,220,61,203,134,191,48,230,56,255,228,3,206,47,111,105,142,78,56,126,248,136,34,43,24,118,157,40,140,18,192,237,141,82,154,52,9,172,215,43,238,110,
110,200,117,122,63,150,240,42,101,113,120,140,139,78,118,89,136,58,210,170,166,41,114,76,183,99,117,123,203,118,215,66,12,201,169,235,146,60,43,113,227,24,193,106,17,17,28,199,115,42,230,12,123,229,241,
209,149,172,147,148,122,182,100,108,183,188,255,227,63,101,121,116,68,61,157,202,204,27,73,208,74,148,104,55,247,191,167,236,91,165,210,79,99,126,247,94,186,44,179,241,16,115,125,5,143,158,132,192,79,
191,255,35,94,92,94,83,30,28,113,244,232,33,69,146,227,198,33,142,186,116,188,216,28,69,85,146,171,148,187,203,11,186,161,163,169,10,116,150,227,140,67,85,37,243,102,134,55,67,68,206,203,220,189,154,77,
41,178,156,118,181,97,123,119,71,183,107,209,89,70,90,100,228,205,132,76,37,96,44,206,12,224,29,198,123,112,114,25,170,88,245,239,11,189,16,213,97,147,131,7,148,105,198,15,126,239,247,48,137,101,249,240,
144,60,23,69,144,16,57,165,224,11,42,69,255,207,255,235,255,246,142,243,30,141,28,222,147,73,141,83,9,175,62,251,28,211,27,76,215,83,151,13,203,147,35,172,11,148,85,35,177,119,237,14,252,136,181,1,227,
66,204,74,181,178,84,136,173,107,8,80,230,21,217,108,206,191,250,189,63,32,217,12,124,247,183,126,147,215,222,122,2,201,40,244,70,132,121,163,84,134,78,69,107,239,73,72,85,66,89,100,81,246,40,10,29,231,
221,189,203,83,41,79,154,101,220,174,239,56,251,248,19,170,201,20,19,96,58,153,137,107,114,28,239,41,141,227,48,138,129,42,4,118,235,13,206,246,172,174,238,40,171,130,172,44,112,78,81,52,162,101,215,241,
230,12,193,82,151,37,147,197,1,231,231,151,140,253,142,182,219,137,76,179,105,36,56,35,203,72,115,141,29,7,188,27,99,139,40,21,119,136,179,84,235,157,0,223,116,194,104,28,47,94,221,112,254,193,251,124,
245,107,111,243,244,141,39,100,165,60,128,227,56,146,37,41,214,218,72,233,148,252,1,227,144,139,80,167,34,155,245,42,114,251,61,206,152,123,201,161,179,142,44,2,227,236,216,242,234,244,156,180,148,32,
136,217,116,17,71,29,54,98,159,71,156,29,40,138,148,93,187,195,97,184,187,184,194,116,150,188,204,32,149,195,45,203,74,178,84,188,6,193,89,172,29,153,205,39,60,122,250,128,245,205,53,221,110,71,215,111,
217,172,91,38,139,37,30,241,35,100,105,194,208,181,120,59,198,231,83,228,170,62,72,91,58,140,6,146,4,231,60,131,177,124,246,225,135,28,46,38,44,79,14,208,153,140,87,198,113,196,197,223,203,13,35,169,82,
120,149,128,87,248,24,161,148,23,141,40,75,148,128,253,156,145,214,215,26,49,59,9,48,77,198,26,26,143,27,55,172,218,129,188,170,57,60,62,97,185,56,100,117,117,45,151,170,146,78,194,122,135,247,49,75,33,
88,218,203,43,156,11,20,83,113,73,182,163,229,232,201,19,108,219,198,5,157,143,42,53,164,250,118,162,50,57,125,245,138,237,110,96,54,95,144,197,224,20,219,245,56,63,96,198,65,178,134,247,64,58,31,83,96,
125,228,208,43,49,6,174,110,46,40,74,49,21,58,235,162,250,137,251,136,201,189,222,94,114,58,196,206,170,18,197,116,126,68,154,100,113,183,36,126,145,123,48,231,126,116,130,48,124,76,223,210,174,206,57,
191,90,177,124,252,148,122,182,96,82,215,12,187,86,230,220,42,230,96,40,144,194,16,110,174,174,105,183,91,234,102,74,86,151,120,227,80,153,96,189,199,174,149,203,93,139,137,168,174,10,170,162,192,59,195,
221,237,45,119,87,215,36,105,74,61,105,72,203,138,52,73,240,214,197,108,2,89,98,135,88,121,171,68,52,241,42,68,212,121,146,224,71,195,245,217,43,202,105,131,206,210,72,28,141,105,236,209,12,25,212,95,
24,113,241,197,168,171,200,10,217,99,40,121,55,241,225,11,227,148,19,197,81,209,212,116,215,215,124,244,222,123,92,175,238,152,63,124,196,252,224,144,186,168,176,195,72,208,62,70,89,58,124,80,212,211,
26,215,119,92,157,95,97,77,39,85,122,89,144,162,8,169,136,26,188,49,4,217,192,162,208,52,243,9,85,158,179,187,186,102,125,119,69,187,89,147,207,102,148,85,73,89,68,79,128,15,140,227,32,4,223,40,146,217,
7,206,123,231,227,118,78,131,146,105,200,39,127,246,103,152,36,80,76,106,18,181,71,56,251,72,248,20,249,182,74,52,250,31,252,47,255,251,59,105,22,185,40,241,3,155,205,38,148,211,37,183,215,183,140,166,
101,181,90,81,228,21,179,249,140,174,31,168,155,26,231,70,140,105,241,206,227,98,90,22,81,82,38,178,71,209,137,154,16,248,228,211,23,148,6,222,254,198,151,40,26,105,21,141,113,24,35,75,165,72,1,16,247,
104,124,136,53,80,150,53,117,83,221,51,77,172,115,216,193,220,183,226,4,79,85,150,92,93,93,208,174,214,4,180,180,180,101,197,116,50,17,195,88,28,47,5,239,196,172,145,106,198,97,96,236,123,118,235,157,
132,58,16,112,22,170,122,70,150,167,168,32,54,242,224,60,85,153,241,240,225,3,110,111,110,217,174,86,172,110,110,25,186,129,147,71,143,104,187,129,60,207,73,18,197,208,247,40,47,138,37,19,153,41,214,26,
9,74,215,9,195,56,50,140,142,113,215,243,232,233,3,170,186,146,131,52,81,152,113,148,67,106,175,140,80,138,60,75,101,57,147,138,244,51,203,39,148,205,52,166,109,9,249,210,89,135,49,18,81,169,227,156,63,
47,11,186,221,150,36,25,185,185,89,145,101,53,105,150,146,151,13,89,154,75,21,25,96,187,222,144,0,229,164,102,104,71,124,112,220,157,94,96,54,45,229,100,34,50,93,20,69,57,33,207,36,57,75,41,48,221,142,
50,203,120,246,250,83,198,193,112,123,117,75,191,185,99,179,89,243,248,217,115,250,209,144,21,21,169,38,30,218,163,116,65,102,100,189,105,25,141,180,235,163,113,24,43,163,145,170,168,72,139,2,84,34,173,
182,247,113,55,21,49,26,177,2,86,42,21,165,150,11,56,171,80,121,195,241,147,167,242,243,134,49,82,84,43,140,233,238,231,213,123,125,115,146,36,156,60,60,162,95,95,115,119,189,146,36,160,170,230,201,107,
175,209,238,58,134,97,136,68,81,117,143,97,80,33,208,154,145,237,245,181,4,110,87,57,4,203,232,21,15,158,61,165,95,173,9,206,203,97,165,115,138,52,37,207,75,240,142,113,232,184,120,245,130,182,55,28,62,
124,196,100,50,145,89,234,96,48,99,23,23,112,50,238,11,123,191,64,16,5,146,204,176,101,220,21,162,218,70,235,123,104,183,72,114,85,92,228,197,234,149,32,102,40,148,38,173,166,60,124,246,26,202,68,156,
68,4,126,201,172,92,254,236,67,237,117,150,225,93,79,123,123,74,219,58,145,15,79,166,204,151,75,108,63,72,152,139,146,78,211,171,32,7,82,240,92,94,95,211,110,86,100,169,24,195,172,53,120,93,176,88,46,
177,131,20,60,140,35,14,79,81,215,76,103,11,194,48,50,116,119,220,92,222,224,85,194,242,228,132,188,40,37,92,103,236,36,52,196,59,236,158,49,29,190,88,106,239,71,59,206,185,88,173,106,2,14,149,200,1,168,
181,44,173,247,17,133,62,200,231,146,36,73,236,152,27,78,30,62,149,229,104,52,52,169,68,38,27,62,18,79,3,9,74,43,38,243,25,171,87,87,188,252,244,83,17,51,44,102,212,179,57,205,100,130,31,69,177,168,19,
81,95,37,90,209,204,166,184,126,224,244,229,75,140,237,200,116,66,146,203,152,47,173,26,170,178,20,28,69,16,36,121,154,42,38,203,41,77,211,208,173,58,140,233,217,94,93,161,138,146,98,58,165,40,27,82,20,
227,40,93,242,158,218,30,130,80,70,131,218,171,186,100,199,214,110,182,140,24,148,14,98,48,140,251,58,31,164,128,9,241,131,244,62,160,255,206,223,255,159,222,41,138,34,222,62,254,94,134,148,103,57,205,
98,198,229,217,5,125,187,99,179,222,240,252,217,107,228,77,69,215,246,84,77,141,25,229,69,54,214,196,202,193,198,121,149,56,5,251,81,36,126,121,154,51,57,156,238,133,182,140,70,198,10,126,31,18,129,71,
102,7,73,212,244,137,178,100,58,93,80,214,181,160,17,116,148,196,69,153,146,36,210,72,170,147,210,154,171,179,51,116,176,204,15,102,216,160,98,142,104,67,215,245,104,37,21,118,223,117,20,121,138,113,30,
103,6,198,97,71,123,189,37,175,132,122,233,92,32,75,115,178,52,151,110,34,102,87,230,89,194,252,104,193,118,179,163,221,110,24,135,22,149,102,156,60,126,140,25,161,174,43,140,49,180,219,29,4,81,139,120,
35,134,180,189,20,111,63,143,204,242,148,84,169,168,42,18,249,168,177,98,193,151,118,94,46,178,44,151,125,5,10,172,87,156,158,93,83,20,83,38,211,153,76,38,227,226,111,232,71,188,53,24,111,9,94,12,101,
89,158,227,140,1,239,104,119,61,58,43,208,169,166,153,206,177,214,162,131,40,152,60,1,229,60,85,89,209,119,61,198,236,184,57,59,39,203,43,170,178,162,104,106,6,227,197,131,224,5,167,224,156,137,232,99,
207,193,193,18,173,52,235,205,154,221,118,205,104,28,7,15,30,19,130,166,42,83,134,182,21,234,162,19,236,176,179,145,90,26,100,215,67,236,238,66,236,220,8,65,50,85,189,7,183,15,160,225,30,182,37,28,255,
200,112,10,142,221,118,71,219,13,188,249,149,175,2,105,148,127,14,88,107,226,136,192,221,235,253,131,115,168,36,101,58,175,216,174,175,217,118,242,179,178,178,224,193,163,199,152,222,208,237,118,34,79,
12,251,80,132,132,224,6,218,97,71,127,119,71,240,9,197,180,193,25,75,90,54,28,28,29,210,174,214,88,103,169,155,26,27,177,190,101,81,80,100,26,149,56,174,46,207,185,91,111,121,248,244,57,211,233,12,55,
140,152,190,139,242,203,16,213,40,177,138,85,82,161,179,135,175,121,153,63,167,69,37,243,220,125,55,19,133,11,33,70,89,10,80,66,76,111,40,207,106,117,199,237,245,29,95,250,229,239,160,130,162,223,181,
113,220,33,63,219,121,191,183,5,144,102,82,36,233,196,209,174,239,48,72,60,97,86,214,76,151,7,216,93,135,11,54,86,222,14,157,37,228,69,134,179,150,211,179,115,198,174,99,210,76,4,189,226,68,169,50,105,
26,134,221,6,235,70,76,148,179,230,101,69,85,23,36,193,211,110,55,92,158,159,98,117,198,242,228,1,147,70,240,11,118,28,228,128,219,147,101,130,39,120,241,210,107,181,55,122,133,88,161,43,146,232,108,151,
33,95,136,252,25,161,197,38,137,70,138,91,249,93,251,221,142,243,243,107,158,124,229,107,84,89,17,51,137,93,44,80,197,87,36,161,229,10,149,106,234,186,224,242,244,130,187,213,138,144,137,209,47,155,76,
88,204,151,140,93,135,19,69,3,193,5,161,167,54,21,253,237,138,179,139,43,188,55,84,85,35,211,131,160,40,234,134,82,167,114,177,16,162,232,66,83,54,53,69,145,211,175,54,108,111,46,217,174,238,200,231,75,
138,82,254,222,89,67,176,54,78,12,212,94,40,41,36,205,88,32,219,184,83,8,193,11,199,234,62,208,35,236,57,168,241,178,143,139,235,255,242,191,254,219,239,184,0,193,201,178,71,37,123,178,160,165,204,11,
14,15,15,216,172,214,220,221,220,112,123,121,203,219,95,253,50,104,69,81,76,64,193,110,183,35,24,35,109,4,50,111,242,222,238,247,11,209,216,34,156,14,23,68,174,72,228,105,128,180,95,251,195,124,159,175,
233,113,232,48,112,250,242,148,233,100,73,90,212,17,241,138,232,183,131,108,175,9,98,170,41,203,130,126,28,24,218,29,187,118,71,154,230,36,73,70,90,84,212,179,69,92,158,248,184,224,114,212,85,46,51,96,
111,216,221,173,104,215,45,69,145,68,254,74,78,61,155,199,7,65,50,91,135,190,35,77,180,140,181,70,203,221,237,29,167,103,47,113,163,227,248,225,83,116,81,145,103,25,93,223,75,90,150,119,196,39,21,99,109,
228,211,91,188,117,113,22,39,5,168,74,228,197,118,206,160,85,42,151,151,23,153,162,247,142,68,167,210,238,91,79,154,43,254,252,207,222,165,42,27,166,7,39,209,7,36,7,124,8,129,190,239,80,78,186,165,188,
204,196,245,107,59,186,118,205,182,29,98,104,139,162,158,205,68,213,228,70,170,66,184,43,89,6,179,249,140,245,106,135,87,134,243,207,62,35,37,167,168,74,66,208,140,30,154,233,28,55,26,1,197,225,48,125,
11,193,115,112,114,44,75,205,93,203,231,31,127,196,171,87,231,60,124,244,132,217,114,73,166,83,118,155,53,227,190,131,241,65,246,8,222,69,133,153,188,156,193,142,162,168,114,86,210,184,124,96,52,99,188,
8,136,176,60,241,117,224,28,206,199,252,3,103,184,189,56,231,242,242,154,111,124,231,87,41,202,134,110,187,197,140,131,84,133,97,159,171,42,255,110,215,118,164,69,65,81,36,220,93,93,49,198,46,66,231,57,
79,222,120,147,177,235,25,218,93,228,173,8,10,88,43,57,108,238,54,43,118,215,87,248,209,147,100,41,206,66,49,157,113,244,240,1,55,103,167,244,125,39,89,185,209,106,153,231,37,117,93,227,156,140,32,62,
253,252,21,207,190,252,85,78,30,156,176,91,175,24,134,62,186,212,137,115,112,80,169,104,199,189,15,146,89,27,169,140,105,150,10,30,2,69,150,167,209,255,145,161,85,12,199,136,93,201,94,84,169,8,108,111,
206,121,117,118,205,91,223,252,6,245,100,134,239,71,172,181,162,203,191,95,246,203,136,47,205,82,148,202,240,182,227,234,236,148,180,156,72,133,168,50,150,15,31,192,56,98,134,30,157,100,4,175,72,50,17,
45,248,174,227,236,236,130,190,107,201,115,77,146,230,56,235,40,231,75,170,34,195,246,93,196,117,248,8,91,75,169,103,115,202,52,33,140,61,175,62,249,152,219,237,142,147,231,111,48,171,107,134,190,165,
239,186,248,91,252,5,89,102,130,184,205,5,252,20,139,3,112,193,222,227,85,20,200,119,149,136,23,65,10,240,88,192,10,177,13,103,90,222,255,209,207,120,244,229,47,209,212,141,64,3,173,145,221,71,144,209,
168,143,197,71,49,109,152,149,21,23,167,103,220,156,95,208,44,230,56,59,146,84,53,203,131,99,24,7,92,240,120,45,27,187,52,215,204,151,11,118,215,215,156,190,60,195,186,129,188,44,41,203,2,107,161,152,
205,73,131,56,114,173,181,247,5,96,57,171,152,46,150,152,214,208,223,174,184,120,249,9,62,79,153,28,157,80,233,156,113,28,24,251,54,190,23,242,44,107,45,187,71,137,164,85,177,107,139,23,157,150,139,210,
6,21,253,6,196,157,74,92,30,255,141,255,252,111,188,147,231,21,185,22,243,139,40,22,12,102,48,168,16,72,117,202,241,131,135,116,125,199,233,203,207,89,93,222,50,157,47,153,206,15,201,203,130,113,28,24,
186,93,252,80,29,129,4,227,44,222,137,255,114,176,177,138,117,194,174,209,113,179,236,35,247,57,137,113,109,123,149,129,142,142,56,63,140,164,89,194,135,239,127,204,209,241,67,137,221,75,146,123,28,105,
26,47,17,239,246,149,90,201,122,181,65,133,145,221,110,135,78,53,58,147,164,167,249,108,113,143,81,22,247,158,163,170,107,140,11,12,166,99,123,119,71,191,221,145,87,41,73,94,144,102,37,101,61,33,248,128,
25,13,227,208,209,247,35,131,113,212,205,132,201,108,206,221,213,29,103,47,63,1,231,121,248,244,57,58,203,8,94,176,12,102,236,229,82,114,226,38,9,222,163,19,141,243,33,194,189,252,61,44,202,26,39,65,36,
129,136,103,21,229,133,243,73,92,58,122,8,142,36,46,126,222,123,247,23,60,124,252,132,144,85,36,200,168,72,100,102,242,34,216,200,138,41,235,138,113,176,164,58,97,179,219,48,182,3,86,222,33,170,102,78,
85,85,12,198,136,65,204,59,178,84,49,157,205,217,109,90,118,221,150,237,205,13,143,159,190,78,61,159,50,12,61,168,132,122,50,69,97,100,76,211,119,152,209,225,188,104,129,23,147,146,161,239,57,63,63,197,
57,203,243,55,223,166,40,50,198,110,67,187,221,73,224,121,172,62,246,142,66,239,140,196,226,249,47,218,213,253,226,206,120,169,214,210,66,82,196,188,145,153,164,15,14,27,23,185,214,57,50,157,112,115,118,
74,55,14,60,122,246,156,249,241,17,198,56,250,182,187,151,221,73,172,163,132,142,140,189,137,225,238,158,203,243,11,116,82,202,18,46,81,60,120,250,12,77,194,110,189,133,84,176,25,206,56,113,60,6,79,55,
14,236,214,43,178,68,163,155,6,157,166,228,117,108,205,215,91,172,237,240,94,76,59,105,170,73,51,77,130,166,72,19,86,215,23,236,118,61,175,127,237,43,228,73,66,191,221,49,142,67,148,106,198,130,135,68,
208,227,251,182,125,255,188,120,217,39,168,56,228,34,154,251,100,44,179,223,151,253,5,210,98,212,156,95,189,252,140,213,122,195,155,95,251,58,179,229,1,193,6,134,190,69,37,65,102,204,222,96,157,141,108,
41,121,194,76,183,229,234,252,146,106,50,195,58,143,245,138,249,201,9,116,194,106,15,137,72,20,147,84,83,22,37,214,116,92,221,174,177,99,79,158,102,120,5,198,5,166,7,135,104,133,60,59,222,74,151,96,157,
176,164,234,9,69,89,97,251,158,187,203,11,208,25,79,222,120,147,96,44,102,48,88,39,207,180,116,45,234,94,101,70,76,41,219,123,95,66,8,17,254,22,187,190,125,54,132,108,109,69,231,239,221,189,89,52,73,53,
237,221,45,239,253,244,125,30,125,229,43,28,31,28,162,156,147,179,46,145,61,144,242,238,222,191,82,205,106,66,55,112,119,125,73,215,238,152,78,103,40,47,140,162,217,193,1,182,235,238,121,56,222,57,116,
81,48,155,78,24,87,59,46,46,175,112,99,71,94,149,194,108,74,82,234,197,2,101,172,168,201,172,145,142,48,154,42,235,249,20,157,40,118,215,183,220,92,93,82,45,23,44,142,143,73,92,96,28,58,241,62,236,135,
51,169,164,253,121,103,163,140,221,11,57,87,197,253,150,223,199,187,138,102,63,218,242,101,241,253,107,223,250,206,59,89,90,80,207,231,120,20,85,51,101,24,70,9,241,30,59,188,21,205,247,193,131,3,148,214,
188,247,222,187,172,206,46,121,246,244,57,147,131,67,66,162,216,110,183,178,105,247,14,227,32,4,209,138,250,72,224,115,198,147,102,178,44,49,86,152,227,238,62,252,58,126,145,177,85,27,186,81,248,246,193,
67,34,7,216,231,239,125,44,78,210,172,65,101,57,237,110,199,62,120,125,52,241,75,13,129,122,50,227,246,234,134,34,211,172,214,43,105,251,116,70,149,215,212,243,133,252,46,222,196,131,212,48,155,215,116,
253,200,56,12,172,86,119,236,86,91,138,82,12,47,169,206,40,154,41,198,12,210,61,244,81,73,96,13,179,249,132,178,44,113,227,192,39,31,188,207,100,210,112,248,240,41,105,89,48,244,45,67,183,186,15,251,150,
207,33,200,151,17,66,188,165,239,125,228,209,28,19,85,5,90,145,100,57,40,45,202,36,31,24,7,161,44,58,235,73,147,140,182,219,114,254,249,231,28,28,157,64,86,80,148,37,125,111,232,123,169,226,141,181,140,
195,200,104,6,202,82,14,225,68,25,46,207,206,33,9,49,196,196,73,184,72,89,98,134,65,14,52,23,72,82,152,46,38,236,214,29,87,183,215,188,248,232,83,166,211,5,245,98,194,174,237,73,84,70,51,153,49,246,45,
227,56,96,157,97,52,10,111,13,101,145,51,91,78,193,6,62,124,239,61,134,97,228,233,107,111,160,19,197,208,182,180,237,6,191,135,101,161,8,86,210,166,228,82,4,227,61,214,69,204,114,112,247,236,120,21,23,
152,65,41,121,192,125,192,25,185,244,147,200,45,73,51,205,237,213,57,163,49,28,159,60,98,121,242,128,166,105,216,172,214,146,236,164,181,116,132,200,136,192,249,32,41,86,227,150,235,243,43,178,188,160,
239,59,172,74,56,124,244,4,229,28,187,237,38,82,54,247,89,174,21,137,246,92,222,200,236,218,143,150,106,54,133,68,179,120,248,8,77,96,88,183,130,140,78,51,202,201,148,113,236,201,179,148,34,47,168,242,
148,211,79,63,230,226,234,142,175,124,235,91,248,193,208,239,58,209,87,71,61,181,40,139,164,26,147,125,139,143,90,125,135,10,178,187,72,34,135,61,81,82,12,184,192,125,215,181,31,69,5,228,16,170,242,140,
187,139,207,88,109,215,60,122,254,58,179,195,35,50,149,209,173,215,132,96,228,32,13,16,156,252,187,193,57,156,113,220,92,157,178,89,237,162,161,200,225,66,194,195,167,175,227,205,128,53,70,174,134,224,
201,138,140,186,41,177,93,207,229,229,45,187,245,70,156,242,9,248,36,99,178,88,162,189,151,61,147,25,191,192,0,43,113,36,55,77,141,239,59,94,126,252,49,245,124,201,241,163,39,184,97,96,232,58,25,117,41,
162,219,61,30,241,65,69,190,126,192,5,69,18,15,91,216,179,244,37,224,71,103,121,12,12,23,153,173,212,146,114,81,84,77,193,237,203,207,248,232,163,207,121,250,229,183,57,56,58,65,39,50,126,76,246,202,32,
235,238,29,207,211,229,140,126,181,225,250,226,10,239,44,243,131,5,222,88,198,0,243,195,35,24,69,159,47,103,152,39,47,51,102,139,41,171,139,107,110,175,47,105,119,107,146,44,167,168,26,180,210,52,211,
41,182,237,113,193,226,204,40,99,202,224,209,153,166,158,207,200,243,130,245,213,29,119,183,183,28,63,122,192,100,190,100,216,109,113,102,140,249,208,224,141,141,209,43,113,69,149,164,164,89,142,55,162,
2,75,146,36,74,77,67,196,173,40,137,78,246,1,253,149,55,95,123,199,140,61,117,93,83,84,13,74,107,138,170,194,57,207,216,155,8,143,146,151,165,153,86,76,38,115,46,207,95,113,253,234,148,147,135,143,152,
28,30,50,154,129,161,237,99,160,181,128,180,124,144,160,128,68,167,49,138,144,251,23,72,22,169,78,218,105,149,144,231,133,168,56,92,228,87,4,39,193,8,193,209,76,74,206,46,47,184,125,121,198,201,211,39,
64,74,213,76,24,58,25,19,152,24,57,104,6,49,61,165,85,46,58,112,111,104,55,173,104,79,75,89,250,206,150,7,113,121,33,138,164,224,130,232,129,125,160,235,58,182,235,53,183,87,215,76,166,83,38,139,131,8,
133,18,47,128,29,7,84,24,200,51,8,214,146,23,5,7,71,7,232,36,225,167,127,246,19,130,53,60,126,254,6,206,123,73,65,138,128,53,169,50,229,97,144,69,100,148,173,70,45,189,195,199,128,99,79,176,10,157,229,
248,144,226,29,140,214,97,134,49,142,55,68,83,92,79,106,182,155,45,237,246,142,162,154,160,84,198,226,96,129,53,163,152,226,66,192,88,39,139,105,51,144,165,58,74,35,61,87,103,87,100,121,142,141,223,67,
213,76,105,154,9,54,154,75,140,25,80,65,179,56,92,96,13,92,221,221,112,254,233,199,164,73,78,61,153,10,88,171,106,36,224,123,28,25,186,157,208,22,131,84,250,214,88,38,211,134,197,124,193,47,126,250,46,
215,151,55,188,249,181,175,49,142,3,171,219,27,89,62,121,217,245,140,206,98,45,160,53,94,37,4,175,98,101,6,222,202,156,217,59,135,242,78,22,249,17,32,39,106,45,31,37,117,49,172,103,239,51,232,214,172,
87,27,210,178,161,89,46,88,46,15,105,215,91,70,59,198,4,52,73,2,27,141,193,90,143,210,9,253,110,199,250,234,142,188,148,239,121,52,142,135,207,158,145,4,232,214,119,226,33,112,142,52,203,37,156,37,211,
108,187,29,55,87,151,12,221,192,124,49,39,47,74,38,7,135,168,0,237,110,131,29,123,198,161,139,118,248,132,36,194,225,154,186,225,250,213,25,55,235,45,207,191,244,38,253,122,45,242,230,36,160,147,60,142,
44,84,52,239,69,117,73,12,142,23,185,162,56,44,163,234,152,50,47,133,82,154,166,113,68,16,193,112,81,60,161,35,79,127,117,249,138,171,171,59,210,102,198,244,248,152,217,108,65,187,222,200,51,154,200,21,
97,221,126,212,168,233,219,29,119,151,23,180,219,78,248,246,78,65,81,176,60,58,70,25,131,245,1,157,165,184,177,39,43,43,1,240,5,199,249,249,57,237,118,39,168,222,58,39,175,106,150,71,15,192,140,152,177,
199,251,168,156,243,78,104,171,58,97,122,120,64,157,21,188,248,224,35,84,85,113,120,114,196,216,173,101,215,148,102,209,88,22,165,154,81,42,186,159,229,239,131,233,197,190,32,127,151,101,25,121,33,121,
210,193,89,36,44,202,65,12,38,87,73,66,93,151,188,248,217,207,121,255,163,79,168,142,143,153,45,15,88,204,231,244,219,29,22,35,1,39,120,18,2,90,43,154,121,195,230,234,150,213,221,10,239,29,69,93,49,244,
3,42,203,89,28,30,194,104,239,11,21,99,60,20,57,203,249,4,179,235,185,189,186,98,183,217,160,116,66,57,153,162,146,132,201,108,138,29,70,156,25,132,222,26,3,3,148,82,20,211,154,233,124,198,238,226,134,
155,155,107,230,39,71,20,58,101,232,218,123,80,160,11,225,94,90,74,84,239,72,86,181,141,221,134,185,135,231,105,37,234,49,249,44,65,127,247,215,190,245,206,221,205,29,99,107,153,204,102,140,131,33,215,
57,69,89,97,140,197,24,217,212,15,70,98,223,154,186,224,224,120,193,197,213,53,31,255,252,3,158,189,246,156,188,174,88,111,214,152,161,143,142,180,112,255,127,202,9,58,37,154,98,28,152,16,231,201,50,87,
77,211,132,170,44,69,129,17,192,217,30,239,141,204,183,93,52,110,149,37,159,126,252,9,97,24,89,28,29,161,179,146,249,226,64,198,23,118,64,41,145,94,246,227,128,214,41,195,96,80,206,210,238,58,116,146,
221,99,6,210,172,20,77,244,216,71,43,183,84,138,85,61,1,149,50,246,29,109,187,229,230,226,138,249,114,73,221,8,118,32,207,115,204,216,51,118,45,74,201,22,124,95,113,204,150,53,85,211,240,222,207,126,142,
31,29,79,222,124,157,237,118,131,233,214,2,157,139,124,144,16,53,229,222,58,84,146,145,106,249,242,140,113,24,43,28,26,133,38,175,38,184,32,72,9,51,90,198,56,123,181,78,14,85,1,58,121,118,119,183,220,
92,221,160,211,18,18,197,131,7,143,0,24,134,225,62,52,161,239,4,0,231,189,102,24,6,130,239,185,57,191,164,168,170,24,80,159,81,148,83,170,74,150,206,222,7,76,63,144,166,138,249,114,9,163,97,24,90,46,207,
79,193,39,204,15,15,5,175,155,22,40,165,24,135,45,125,183,17,221,123,12,137,119,206,147,151,13,71,71,7,188,250,244,19,110,110,86,156,60,126,196,250,230,246,254,32,83,73,130,183,1,167,116,84,198,232,123,
69,141,78,51,172,49,81,189,2,121,89,145,100,197,30,13,42,151,100,228,31,73,136,135,252,145,84,41,232,118,183,188,124,241,2,146,140,195,135,15,89,30,29,209,239,186,123,106,171,132,160,136,155,57,196,197,
96,183,217,48,172,182,84,139,169,64,213,72,57,124,252,24,237,2,237,118,75,146,136,70,60,236,3,227,149,98,219,110,216,92,223,209,111,91,102,71,135,228,101,67,61,157,210,109,238,228,242,53,189,132,203,196,
224,28,180,84,250,69,93,113,119,117,67,219,13,156,60,121,200,110,189,22,46,250,94,74,24,29,191,82,197,139,57,107,159,27,12,242,123,59,231,201,235,41,89,90,83,100,121,20,48,236,227,81,67,92,116,203,173,
160,179,20,111,29,171,187,115,94,188,120,137,215,37,205,114,201,225,225,33,99,219,138,111,36,73,80,193,73,97,166,19,8,130,33,185,185,188,66,171,132,106,82,49,140,29,198,5,14,31,61,193,108,119,88,43,10,
44,103,45,137,86,148,85,142,242,150,245,122,203,102,189,34,77,83,116,81,146,215,83,234,170,146,37,238,56,200,222,34,213,120,235,8,65,130,61,166,71,71,228,202,243,201,251,239,177,124,244,84,80,129,169,
38,203,107,156,29,72,180,18,21,26,129,144,72,183,167,246,10,172,125,71,24,132,204,154,103,162,239,255,2,53,241,5,179,72,17,37,166,185,166,72,225,147,95,124,192,135,31,126,76,243,240,17,245,100,198,193,
98,129,105,123,140,115,241,146,113,17,209,146,81,231,5,171,155,59,214,155,59,18,21,221,198,194,54,96,126,116,130,239,13,46,200,156,221,91,71,211,200,193,221,221,222,114,119,115,77,183,91,147,213,53,85,
93,11,253,52,81,34,75,183,38,22,212,50,186,179,206,137,202,112,49,97,123,179,226,230,234,150,227,231,207,112,237,128,11,6,162,138,113,31,201,169,98,100,164,119,38,122,109,34,245,52,196,180,53,165,72,243,
38,230,41,167,232,191,249,55,255,139,119,198,93,203,245,213,37,187,213,150,227,71,79,8,58,37,203,11,146,92,50,110,135,182,37,184,225,190,135,8,65,113,112,114,200,232,12,239,254,201,159,242,248,228,17,
73,153,178,91,93,19,188,17,162,166,74,113,33,136,173,223,39,210,186,56,143,39,193,121,39,152,80,103,41,178,92,100,124,121,134,142,97,12,206,57,64,240,13,198,43,225,181,151,37,159,124,240,46,215,167,87,
204,79,142,32,72,58,187,66,51,70,164,129,181,158,113,24,133,143,226,60,73,98,184,56,125,69,149,55,194,251,80,18,128,112,112,244,0,99,162,145,203,73,219,60,157,78,208,121,206,56,180,172,183,107,94,126,
244,146,71,79,31,139,45,60,47,73,179,140,126,180,116,253,6,111,156,220,168,70,182,232,117,83,113,112,178,224,213,167,159,115,117,113,77,61,153,224,198,86,110,227,24,15,169,162,177,68,39,2,77,242,200,118,
127,28,7,225,137,88,139,206,10,14,78,158,96,173,187,87,194,184,224,239,221,125,222,137,212,42,213,26,99,29,169,242,92,94,188,98,215,118,212,147,9,245,244,128,34,47,216,172,215,140,99,143,15,208,181,45,
214,73,133,235,157,72,2,175,63,191,96,118,120,76,51,155,209,89,79,89,78,200,211,168,150,193,211,247,59,0,150,135,71,104,165,88,111,86,188,248,236,115,214,119,107,158,188,241,26,65,105,202,162,194,88,35,
163,144,209,226,237,40,250,122,93,136,143,34,43,89,30,76,232,183,27,86,55,43,116,161,24,141,145,249,125,236,120,130,80,178,164,114,119,210,130,14,67,139,247,38,254,174,80,77,23,124,249,171,223,70,43,45,
218,126,47,243,74,217,219,249,168,58,177,247,139,203,186,41,73,113,124,254,201,167,228,121,77,217,76,121,240,228,17,125,219,211,109,91,18,173,228,79,12,5,87,56,12,35,237,102,69,127,187,163,154,86,56,27,
48,65,241,248,173,55,241,131,97,24,173,196,100,70,52,118,89,54,52,85,13,58,225,230,230,130,203,235,91,166,7,135,20,245,132,60,77,25,182,91,140,27,238,247,52,81,76,25,99,7,51,102,243,25,193,12,114,153,
68,24,152,10,177,138,79,246,216,222,61,84,205,197,2,73,216,76,251,56,189,106,118,192,27,95,249,37,240,137,64,242,34,80,75,169,47,244,253,247,220,249,36,21,119,179,91,115,246,217,41,62,45,153,30,30,176,
56,62,97,108,123,25,199,42,169,188,189,21,83,94,10,116,187,150,235,203,11,148,51,52,179,57,110,180,12,198,179,124,248,16,215,237,162,220,89,254,232,92,211,76,26,210,20,218,221,154,179,151,167,180,219,
94,164,151,245,148,60,215,146,40,102,122,25,205,33,23,127,8,242,14,150,117,201,124,190,224,250,244,140,172,174,73,83,133,29,58,146,36,128,11,113,76,164,208,65,161,73,226,222,106,175,194,145,159,163,210,
146,199,111,126,149,166,158,227,221,40,115,108,37,177,142,206,70,67,164,146,207,38,111,42,82,31,248,228,253,143,233,70,207,100,57,163,104,26,102,7,71,168,126,184,31,233,36,65,130,91,234,73,69,83,23,92,
189,58,99,189,221,224,173,161,153,74,129,160,170,134,233,242,0,63,26,217,45,142,3,33,9,36,69,206,226,240,0,219,25,86,215,215,108,110,46,25,129,249,242,144,186,153,130,115,152,177,139,157,185,147,113,96,
36,200,38,58,163,156,84,40,47,151,111,94,229,145,130,155,68,193,71,84,223,120,123,255,89,36,42,46,187,131,20,51,46,120,202,233,1,143,159,189,65,26,52,164,41,250,111,255,55,127,231,157,68,231,140,67,199,
106,117,77,226,2,143,158,60,142,120,24,153,175,119,187,13,102,232,162,100,211,202,2,46,40,170,170,162,104,74,206,95,156,161,83,141,25,183,81,85,145,224,67,26,117,180,34,143,243,94,164,64,206,201,23,164,
148,4,151,148,197,132,195,147,71,132,68,178,44,133,142,169,25,187,30,231,247,134,12,40,242,28,235,29,99,191,193,90,75,86,150,216,193,177,56,56,196,5,104,55,107,192,99,198,145,209,24,146,84,51,236,70,178,
212,243,226,163,23,148,69,142,210,25,105,94,144,150,37,101,221,208,119,59,20,158,113,28,241,174,167,42,82,148,78,177,67,207,182,223,112,249,242,146,71,143,30,163,139,130,170,110,176,110,100,108,59,198,
81,84,76,130,81,80,17,177,160,168,38,19,92,112,209,144,179,87,152,6,156,9,49,48,90,19,194,254,74,39,54,136,0,0,32,0,73,68,65,84,191,147,217,190,55,46,118,0,142,193,58,146,180,230,193,147,215,216,236,58,
172,233,227,45,46,216,103,183,231,190,160,200,210,20,103,12,89,158,112,123,117,35,210,201,160,105,166,19,210,52,103,187,109,197,5,237,29,118,148,36,30,173,115,108,144,81,204,250,226,142,201,124,78,154,
231,177,203,145,172,128,209,74,110,169,72,110,101,249,155,229,41,195,48,114,115,123,197,237,229,13,7,199,199,164,121,137,206,50,250,118,43,242,75,51,96,172,72,76,131,19,64,153,117,14,157,202,98,209,5,
129,211,133,24,16,65,92,210,114,191,128,243,81,150,25,71,126,81,71,220,181,59,214,235,53,95,254,214,183,201,139,138,161,237,239,195,58,238,121,40,65,114,149,69,197,154,50,153,214,84,133,226,230,118,77,
150,87,20,117,197,225,201,67,188,245,34,189,204,83,156,151,195,52,70,206,51,152,129,110,179,162,95,119,204,142,230,162,182,74,10,14,78,142,25,118,45,169,142,207,137,23,29,120,86,228,98,116,195,113,123,
125,202,217,233,37,199,79,158,48,91,30,160,2,140,93,71,112,30,103,251,104,44,76,238,99,235,148,226,62,125,137,24,24,35,178,92,217,49,236,145,224,242,197,199,84,175,176,7,195,9,139,167,107,183,92,93,173,
248,250,111,124,151,50,205,216,109,118,194,86,10,126,143,97,185,15,199,14,158,24,215,152,97,134,150,237,186,69,231,21,105,94,176,60,17,0,218,30,92,232,157,100,41,100,121,129,86,41,155,221,154,245,221,
138,140,140,98,62,141,9,102,25,203,227,35,204,118,27,133,19,70,68,17,58,161,170,106,242,52,197,140,61,55,215,215,140,163,101,186,92,208,204,150,4,211,227,76,143,25,135,47,24,66,209,246,159,23,57,73,18,
40,202,44,238,111,12,74,121,225,11,121,41,12,84,236,200,3,9,40,89,246,11,142,66,56,75,214,56,238,174,110,57,122,254,38,203,249,129,96,34,148,32,145,21,10,235,6,145,58,71,243,89,53,109,216,221,172,120,
249,249,11,214,235,59,33,87,234,140,197,209,17,97,52,152,113,36,36,94,118,27,4,202,166,164,76,83,46,79,47,216,118,59,148,15,100,101,33,235,246,188,160,105,38,120,99,24,205,32,108,161,96,201,242,140,249,
193,12,101,3,221,122,205,234,226,28,93,55,148,179,41,211,233,28,31,165,237,34,189,12,95,236,97,162,153,48,175,197,156,38,210,245,248,235,40,133,242,82,197,139,115,219,199,164,44,249,172,124,80,247,151,
7,30,138,201,140,227,71,79,73,60,232,223,254,237,223,126,167,154,76,152,206,23,172,238,174,57,125,241,130,82,85,60,127,251,53,218,65,56,230,195,216,210,117,109,212,213,202,104,198,216,32,25,162,58,65,
151,9,99,219,202,172,57,126,65,42,134,37,135,61,227,25,21,209,181,14,231,228,127,109,116,209,173,110,55,60,127,253,45,156,202,24,186,65,182,234,74,242,47,195,56,74,149,27,2,245,100,202,174,109,25,183,
107,172,53,204,102,51,148,74,152,206,230,88,18,186,174,35,75,18,60,129,161,151,27,122,176,142,128,225,213,199,47,200,11,209,236,103,105,70,217,52,20,205,132,182,237,68,69,212,183,160,28,69,149,147,23,
21,166,27,89,175,111,185,187,94,241,198,91,111,145,148,37,89,154,211,237,90,218,190,103,24,70,76,52,9,217,32,234,18,227,21,121,94,146,196,108,129,189,158,216,123,81,66,128,44,200,188,18,51,149,51,78,12,
108,78,198,58,193,195,245,205,13,195,174,231,203,95,255,38,222,39,180,155,53,89,158,161,179,146,68,41,134,62,42,65,112,240,255,51,245,94,77,150,93,233,153,222,179,220,182,199,167,175,170,172,42,20,128,
66,55,186,233,134,28,13,37,138,38,36,253,0,69,144,17,210,141,34,20,161,137,144,189,212,15,192,159,146,98,66,12,114,40,138,77,14,201,102,163,217,6,166,0,148,205,74,159,121,252,217,126,111,93,124,235,28,
244,29,76,161,42,113,206,222,107,125,230,125,159,87,27,154,178,164,223,15,184,184,186,33,112,226,28,78,210,62,113,218,99,62,159,75,235,219,182,212,141,112,105,172,182,100,249,154,245,98,206,205,219,119,
244,39,123,36,253,17,29,150,100,56,38,223,100,20,121,38,75,89,47,151,76,135,41,73,146,208,213,21,23,231,239,185,185,188,165,63,217,39,233,245,49,93,195,122,179,36,203,132,91,212,181,74,46,230,198,243,
105,58,113,144,214,77,37,29,75,93,83,151,149,0,206,124,181,223,120,109,126,215,108,249,246,70,216,41,30,53,176,89,205,121,251,242,45,191,251,135,255,57,147,163,19,242,44,167,44,43,175,74,241,182,117,36,
156,164,170,107,234,170,198,57,3,77,193,253,253,92,22,225,218,113,244,232,33,90,25,178,108,179,75,219,106,187,70,24,43,186,99,83,20,20,139,5,235,233,156,120,16,203,179,107,29,135,199,71,172,238,103,178,
203,105,165,243,208,90,161,173,224,60,2,221,49,159,94,241,221,55,111,24,236,31,113,114,250,136,98,177,148,67,180,105,188,81,78,156,177,93,211,97,67,231,255,218,227,157,77,67,91,43,31,214,210,250,136,70,
227,115,7,240,232,129,214,203,238,44,198,202,184,97,189,156,241,238,245,25,63,248,253,223,99,114,112,72,190,201,165,27,247,23,160,84,181,237,46,152,29,192,6,154,205,114,206,114,149,97,131,136,206,56,246,
142,78,48,93,39,33,215,70,42,90,140,37,8,52,206,40,150,243,57,247,211,91,168,107,146,126,95,226,44,195,30,227,201,88,60,32,117,225,93,213,66,205,140,211,24,103,29,186,107,184,187,185,224,238,118,74,58,
222,99,60,217,163,44,55,212,133,100,251,250,44,37,58,165,232,106,65,172,200,40,70,132,34,118,91,185,251,81,96,91,111,93,180,157,127,191,60,69,172,21,129,68,167,44,198,192,139,207,127,137,221,219,231,225,
147,167,80,213,148,101,46,42,21,164,210,215,219,119,210,89,6,227,1,211,235,27,238,174,175,216,100,27,180,11,8,146,62,163,131,125,76,11,85,89,163,149,0,252,208,134,36,141,49,93,195,229,217,37,235,205,134,
174,169,101,231,89,84,168,32,36,116,1,117,145,209,180,146,31,162,180,40,245,134,7,99,140,178,228,203,53,103,223,125,67,214,118,76,30,60,32,9,67,154,178,160,172,42,129,81,26,231,113,237,74,82,175,140,243,
57,222,91,191,105,187,131,218,181,91,153,166,151,175,74,165,175,104,58,73,43,212,218,209,214,53,211,139,75,242,182,225,244,227,79,48,127,254,231,255,237,103,116,13,54,8,72,82,161,9,190,125,253,146,42,
43,57,126,248,136,40,76,208,206,82,100,107,242,205,90,102,111,173,204,211,218,90,110,219,78,73,251,208,250,132,37,97,55,88,130,40,166,246,228,66,99,172,143,126,147,237,185,200,159,228,230,206,139,156,
108,177,230,244,217,135,152,32,38,47,10,170,50,151,23,210,203,18,235,170,194,90,69,24,89,105,205,149,44,216,146,52,165,165,163,63,24,18,197,49,43,191,88,193,103,153,42,163,161,110,232,76,193,249,171,119,
66,200,12,29,161,147,61,69,16,132,204,103,115,154,170,162,172,74,170,170,196,217,128,48,137,168,171,154,219,219,43,174,47,46,57,56,216,103,180,119,64,219,117,228,217,134,172,40,232,154,142,182,85,104,
160,233,58,52,110,167,40,192,239,41,36,64,219,103,101,122,211,139,70,83,86,53,29,181,239,124,196,248,81,181,146,241,249,246,229,183,196,54,224,248,241,83,108,24,179,94,173,200,178,156,188,148,159,175,
172,196,127,208,180,16,134,145,140,151,202,13,119,119,119,162,169,54,134,184,215,99,56,28,177,94,109,118,154,254,186,148,214,61,114,9,85,83,178,90,46,89,94,220,177,127,114,68,60,28,210,212,45,131,241,
152,245,114,78,89,84,20,89,73,81,228,82,233,40,33,4,106,37,100,206,171,139,115,30,62,58,101,114,120,194,116,62,39,207,50,234,162,250,13,51,187,247,24,212,53,77,85,249,23,102,75,224,148,239,189,109,59,
58,35,214,111,173,12,157,55,117,53,93,179,115,73,203,152,67,145,109,50,222,189,121,195,179,231,207,153,28,63,196,89,71,185,217,208,250,248,192,110,135,12,16,192,85,20,198,36,105,72,190,153,179,90,9,13,
213,24,77,50,28,18,134,33,171,249,76,126,239,78,94,44,109,28,166,133,197,122,202,106,190,32,95,102,132,105,15,109,29,38,136,152,236,237,177,89,173,60,227,171,246,149,84,231,35,59,3,2,165,88,76,239,185,
189,187,227,193,211,15,216,223,155,144,175,54,212,141,191,152,84,183,155,61,75,200,188,252,156,157,15,111,233,60,33,178,5,191,231,49,216,40,162,233,90,234,162,240,105,76,22,19,56,25,137,120,238,211,253,
197,27,46,46,47,121,254,219,255,134,253,163,19,84,211,177,94,174,104,59,81,195,181,109,231,25,61,190,11,66,252,44,139,187,59,90,101,209,93,75,167,29,253,189,3,172,82,20,121,177,139,30,84,170,195,25,141,
53,134,251,233,140,197,252,30,170,22,215,19,4,113,152,246,233,15,251,20,203,165,112,147,154,198,227,24,52,54,180,4,129,165,45,115,238,111,174,89,172,86,156,126,244,9,137,87,147,212,181,236,209,180,146,
14,75,43,232,124,88,201,22,173,167,189,161,202,47,53,118,99,60,221,117,219,84,96,161,156,250,174,167,245,251,146,174,206,249,242,243,95,51,122,252,152,195,147,135,152,78,147,175,51,161,121,122,148,66,
231,37,190,46,10,136,93,200,252,110,202,108,118,75,103,13,113,16,128,113,244,70,19,76,211,80,215,165,92,196,77,67,139,140,119,140,82,92,157,95,178,201,54,168,166,193,165,41,206,88,146,209,152,208,24,138,
205,134,182,45,125,6,132,36,142,165,195,1,81,20,82,44,150,220,95,93,129,181,236,61,56,145,216,204,178,146,34,199,239,83,212,150,157,189,53,14,122,85,227,14,24,177,125,102,218,239,223,43,49,240,201,103,
177,13,141,234,104,105,186,154,187,87,111,153,45,215,152,191,248,139,191,248,44,207,115,186,86,225,66,71,175,159,178,206,150,124,251,197,175,233,242,134,39,143,63,160,191,55,97,157,109,216,172,214,126,
225,41,182,8,97,219,200,31,86,215,210,250,104,173,113,81,34,169,61,141,180,52,117,211,80,182,50,163,106,234,202,227,131,133,19,211,180,29,65,24,240,254,236,12,83,119,60,120,250,152,116,48,164,170,91,178,
205,218,219,220,101,233,91,87,21,65,104,81,214,176,89,45,164,163,104,36,186,205,185,136,52,78,113,73,196,106,181,220,225,142,155,186,2,99,61,29,175,229,230,253,185,104,108,147,84,162,220,146,62,29,157,
28,114,121,65,213,148,20,69,65,139,34,136,83,52,112,249,254,29,243,155,91,30,158,62,102,116,116,194,122,181,102,181,92,80,22,107,49,153,105,175,142,238,16,8,92,139,56,6,91,223,14,182,173,44,9,59,97,189,
200,216,67,230,229,219,224,148,198,59,77,187,182,197,197,142,127,253,233,79,25,13,70,28,63,124,194,112,111,143,182,105,201,55,43,249,239,171,146,178,172,100,185,173,64,53,18,160,220,86,5,121,81,209,52,
45,198,72,98,217,120,111,143,229,98,46,15,67,43,175,146,182,6,107,29,171,205,134,205,250,158,219,183,231,28,63,126,132,9,66,154,78,147,198,41,155,229,66,190,243,108,37,192,181,186,161,213,134,48,14,8,
173,230,238,250,146,245,98,201,147,79,126,136,115,142,217,244,94,220,189,90,194,43,240,139,178,166,211,84,173,120,33,229,162,87,84,254,57,16,103,177,240,89,132,65,84,10,211,102,91,233,123,229,137,70,19,
165,9,175,191,254,146,187,219,91,62,249,193,167,140,246,14,72,146,30,203,197,66,58,74,37,213,241,214,169,89,85,13,65,16,226,2,195,221,205,45,202,56,234,182,65,25,199,112,180,71,24,196,108,150,75,89,130,
183,149,68,52,6,1,206,24,102,235,5,203,233,140,205,116,78,220,239,97,131,144,116,56,161,223,239,147,173,86,116,77,73,221,86,114,169,209,74,38,170,11,136,172,102,126,123,197,245,213,45,207,127,231,119,
9,148,33,91,44,168,60,243,136,86,201,226,189,83,50,18,244,139,183,45,38,160,107,100,185,95,55,13,24,131,11,237,206,12,68,215,209,106,188,92,186,148,160,116,143,72,184,61,63,231,110,58,229,233,243,143,
25,239,31,16,4,33,155,197,202,135,194,8,210,188,174,107,153,211,123,166,74,85,174,152,222,222,17,246,250,84,101,65,81,119,236,63,120,72,104,13,217,114,187,168,110,208,70,249,113,31,220,79,239,185,191,
191,135,178,34,26,244,177,65,140,139,19,156,49,84,69,65,93,231,180,181,4,3,117,200,101,152,246,122,232,186,229,246,234,61,184,144,7,31,124,12,101,78,89,228,30,231,162,119,139,124,229,63,81,189,45,6,216,
22,74,236,46,74,165,149,236,82,253,133,171,128,188,40,101,28,106,12,186,107,81,214,80,111,86,188,248,226,5,39,207,62,228,209,147,167,56,27,80,172,51,97,37,1,117,35,23,174,162,35,233,69,196,65,192,226,
110,70,182,90,18,245,122,226,75,208,134,193,222,62,22,77,145,231,24,143,152,80,86,209,27,164,152,6,238,174,238,200,189,115,58,26,14,112,218,16,141,38,80,86,94,57,227,25,91,141,196,121,70,253,148,56,78,
200,22,107,110,46,47,73,71,67,246,14,68,201,212,212,165,16,74,101,230,135,179,193,46,214,245,123,167,181,48,131,58,63,85,232,80,187,209,29,221,182,120,16,79,15,254,98,20,239,66,195,219,47,190,196,252,
249,127,247,223,127,86,151,5,69,177,161,42,4,231,25,197,49,105,47,225,187,23,47,40,23,107,158,253,224,7,216,36,98,181,152,177,94,46,4,142,100,157,200,233,26,207,117,104,101,230,216,162,176,70,164,81,85,
85,146,103,153,140,133,178,92,22,148,205,118,22,217,74,69,224,29,100,46,12,248,250,139,47,152,164,61,70,7,71,76,38,251,24,235,200,242,130,166,169,169,219,138,170,44,132,71,174,180,48,115,186,6,23,58,214,
107,81,68,88,23,208,31,140,232,15,71,82,93,121,45,170,162,35,72,122,212,117,131,182,13,239,95,189,163,107,90,246,247,15,8,226,132,40,233,81,212,53,203,249,148,44,203,124,228,88,67,215,214,216,40,162,63,
232,51,155,222,242,254,229,75,62,248,240,57,81,127,192,124,122,75,182,206,104,235,130,170,105,233,144,128,113,79,117,245,168,93,185,16,235,166,243,10,22,81,25,84,94,66,217,117,130,30,150,25,168,144,64,
219,182,67,91,71,211,181,124,241,249,207,57,62,58,36,25,142,153,76,246,113,65,68,94,252,134,20,178,108,168,171,82,44,211,24,148,109,40,138,13,69,241,253,2,40,233,201,142,100,189,92,137,252,179,21,140,
176,9,28,73,146,176,201,150,108,242,53,151,111,207,73,6,3,66,27,138,186,34,142,184,159,78,41,138,146,50,23,221,112,93,122,114,165,9,24,14,251,220,92,188,231,213,139,239,120,254,227,223,162,169,107,22,
139,185,103,203,136,169,132,78,201,1,92,55,36,97,32,106,173,90,42,113,235,3,157,173,150,116,176,170,150,116,176,157,252,78,109,93,10,30,188,70,77,154,166,188,124,241,21,139,229,146,147,211,71,4,73,159,
227,7,15,200,55,25,217,102,237,29,221,30,169,208,121,197,146,81,104,42,238,111,166,116,218,82,22,37,173,182,236,31,61,32,73,83,150,243,25,90,227,133,4,13,46,12,137,67,75,85,149,44,231,51,230,55,119,68,
189,148,222,112,68,50,24,209,181,53,235,181,124,150,117,237,59,52,207,189,116,97,76,154,198,172,166,55,188,127,127,197,147,79,158,147,175,87,114,32,248,128,139,174,147,78,174,243,146,203,102,135,4,246,
21,100,219,10,195,93,41,249,28,139,66,70,75,126,20,68,235,35,28,189,16,160,243,1,214,171,155,119,204,102,83,142,31,63,33,136,82,246,142,79,40,150,25,69,153,121,213,142,24,126,20,29,141,135,215,109,150,
75,102,179,57,81,154,64,35,218,238,222,193,17,206,40,202,77,38,126,149,166,166,241,103,66,28,89,230,179,25,211,217,29,155,217,130,116,56,198,6,33,81,127,136,170,27,202,50,167,46,51,249,52,60,234,67,107,
195,112,210,167,23,68,92,188,126,67,94,53,60,250,224,41,217,122,67,85,230,98,28,67,251,218,91,125,191,219,242,85,184,168,249,186,157,171,84,219,72,138,155,109,156,101,139,119,70,11,58,98,171,88,138,146,
152,229,229,57,175,94,188,196,245,135,140,143,142,152,236,29,202,204,188,172,61,89,181,161,42,101,214,222,27,14,209,77,195,244,246,158,229,114,73,111,216,147,91,193,88,122,163,61,66,235,40,75,81,4,118,
30,202,55,24,15,136,3,199,244,250,150,205,106,67,190,89,225,250,3,80,154,254,254,1,77,81,210,86,21,109,83,208,182,141,60,123,77,139,141,99,122,195,1,109,94,112,125,254,158,222,100,76,175,63,164,204,50,
170,70,12,86,74,137,140,187,169,69,166,222,248,144,156,109,70,241,214,124,216,105,49,236,181,141,151,50,251,80,116,188,170,12,4,255,224,162,144,192,89,204,255,240,63,253,207,159,21,155,140,60,175,68,159,
220,72,98,145,177,1,105,63,225,253,251,51,230,23,119,60,255,241,167,100,109,195,252,254,222,231,192,250,101,137,103,225,72,53,224,252,50,174,242,104,93,67,158,9,20,169,242,174,194,206,243,158,217,6,32,
251,86,204,89,135,75,66,190,248,217,47,121,120,124,68,52,26,49,24,140,136,123,41,235,213,70,200,144,170,163,40,75,170,90,254,172,178,40,160,205,89,174,86,104,36,245,202,216,128,193,104,68,156,164,172,
55,75,9,21,175,74,20,154,254,96,64,87,215,56,219,113,113,118,1,53,60,120,242,8,173,45,97,154,114,63,157,147,109,54,52,117,43,75,203,186,146,217,32,154,131,253,49,117,13,95,255,226,215,156,126,240,148,
166,107,88,76,167,20,77,237,9,124,66,121,20,195,85,231,91,198,214,171,44,36,122,209,185,80,240,195,85,37,232,3,207,246,111,118,128,55,25,147,181,93,77,24,39,228,217,146,111,127,249,5,167,143,159,208,25,
195,104,239,128,225,104,204,98,58,167,109,234,157,114,167,172,101,57,171,218,134,48,132,249,116,134,49,161,79,95,178,132,113,202,120,111,159,108,181,246,7,85,73,81,102,88,103,73,123,61,170,44,103,182,
188,103,113,63,231,209,211,39,168,32,68,105,249,46,87,203,25,101,89,130,79,38,106,188,57,167,235,228,243,204,86,51,222,124,247,154,15,62,126,206,244,254,222,203,223,100,255,210,54,162,52,209,64,224,90,
168,107,26,4,158,231,194,88,24,221,198,238,100,187,116,236,156,164,219,48,116,221,249,72,238,182,150,185,176,49,124,243,229,23,20,101,205,241,131,19,180,13,152,28,28,82,215,53,85,93,19,4,33,117,93,248,
120,199,206,75,210,59,242,205,130,245,34,103,48,158,80,122,212,243,104,239,0,107,53,249,102,227,17,22,210,97,132,81,66,224,44,117,157,179,88,47,184,185,184,227,232,241,67,140,115,164,253,33,249,122,237,
125,8,25,85,229,191,223,86,70,38,198,10,43,126,61,157,113,117,117,203,147,15,63,98,53,159,82,87,34,89,237,124,120,144,224,51,202,29,38,64,249,16,22,173,148,215,76,203,34,95,27,243,189,127,69,105,241,81,
148,133,4,240,116,157,44,36,181,161,173,43,242,197,29,183,179,57,7,143,78,177,46,102,116,180,71,147,21,172,55,235,29,155,167,170,115,217,171,40,49,204,221,94,94,176,90,101,12,198,99,186,186,5,12,195,253,
35,104,27,138,44,251,254,253,12,29,73,20,19,6,178,39,185,187,189,99,147,229,236,159,28,226,108,68,58,24,80,101,107,202,98,45,105,113,194,28,216,37,69,197,189,148,52,142,184,121,251,142,46,136,72,123,17,
197,122,237,37,206,34,63,173,59,25,145,54,254,64,211,126,59,67,167,197,139,97,37,232,188,106,196,181,43,43,32,73,181,2,133,246,33,246,198,219,172,226,56,32,95,173,120,241,197,175,24,156,60,36,140,18,6,
7,7,24,15,183,147,85,192,86,102,109,136,211,136,50,223,48,191,95,208,212,37,253,209,8,163,13,117,211,210,223,223,71,213,173,76,12,16,189,189,54,134,120,216,67,183,45,203,217,146,205,102,65,81,22,244,199,
35,146,164,79,20,37,148,107,145,45,215,149,92,44,221,54,171,87,181,12,38,99,108,221,114,241,246,156,193,201,9,186,174,40,202,28,99,132,16,80,119,202,231,52,136,187,188,83,218,171,111,26,127,153,58,130,
32,145,225,87,211,248,184,73,189,3,193,121,205,140,108,111,186,14,151,68,152,255,245,127,255,63,63,203,138,156,205,122,67,81,172,169,138,130,170,170,169,235,14,23,69,12,15,198,92,223,95,115,245,221,25,
31,124,244,17,243,108,35,122,218,90,20,14,109,35,224,179,186,110,68,250,165,164,130,213,74,19,5,33,42,8,228,80,242,172,108,145,228,225,25,16,66,151,164,21,169,102,146,196,108,234,140,159,253,237,79,120,
244,232,17,74,91,70,227,17,227,189,67,58,16,79,64,211,208,121,89,100,167,59,154,178,198,153,150,171,171,27,113,140,34,243,224,209,120,34,240,180,205,18,133,241,157,129,1,45,81,95,46,132,203,243,247,88,
101,56,121,124,74,158,85,68,113,194,106,62,103,179,94,138,238,184,110,169,59,168,155,146,251,171,75,142,30,60,162,179,240,237,175,190,228,232,248,1,203,205,156,186,146,7,175,170,171,93,32,113,75,71,89,
21,62,200,160,148,20,34,103,233,165,67,218,70,198,76,141,55,199,116,254,162,16,168,210,174,206,161,106,59,146,48,98,122,127,195,139,95,253,43,189,241,24,23,197,132,113,159,241,222,1,121,94,80,150,185,
76,50,155,150,162,42,61,92,169,161,105,75,238,47,111,112,97,64,93,137,147,54,233,245,25,77,246,88,47,23,116,77,69,94,200,197,134,13,69,38,216,116,204,102,119,124,243,213,183,28,63,120,132,137,19,180,13,
105,235,138,50,203,40,171,66,16,190,126,132,167,148,24,202,108,156,160,187,134,235,119,103,28,28,31,179,246,85,190,242,72,137,70,41,106,143,124,208,65,224,101,114,86,102,227,70,232,150,46,136,201,10,41,
12,84,199,46,126,91,102,62,157,7,161,201,223,186,48,38,116,134,139,119,223,113,121,121,195,96,50,38,142,99,246,142,30,82,87,53,211,251,123,180,218,198,113,54,210,229,213,242,98,111,214,83,102,151,183,
132,73,40,21,168,50,140,14,142,49,29,108,22,11,145,9,122,41,108,152,38,146,255,160,90,86,197,138,215,95,191,38,25,140,112,73,204,112,56,98,121,127,43,9,72,173,104,209,217,130,171,148,66,105,71,16,135,
168,186,98,49,91,16,6,150,162,42,104,124,247,23,246,250,184,40,162,42,37,20,165,110,106,148,213,88,159,233,96,163,136,56,78,8,227,132,34,207,105,75,73,79,210,40,108,96,104,138,234,251,118,190,109,232,
148,112,100,186,182,37,219,220,240,230,187,87,108,154,150,36,29,114,244,248,3,84,93,145,173,54,40,35,135,126,93,53,208,201,158,192,104,197,249,217,5,171,213,154,116,48,240,84,76,24,30,158,160,219,150,
170,200,209,6,234,178,68,41,25,239,36,81,132,234,26,174,47,46,57,123,247,158,209,241,1,214,4,130,235,88,174,196,191,227,119,104,69,85,123,85,141,33,78,98,70,123,125,102,55,119,96,157,127,70,106,207,69,
242,223,85,227,243,145,59,129,215,105,165,208,65,64,18,165,212,157,28,114,218,167,190,161,244,14,255,187,53,172,53,109,139,178,50,38,115,161,165,206,151,188,253,238,53,47,191,123,73,255,225,35,194,192,
146,140,38,4,24,234,162,160,245,159,65,227,247,74,131,209,128,98,189,226,238,250,138,213,122,197,248,232,80,4,39,13,12,246,246,161,170,101,28,231,139,16,104,233,77,38,36,161,35,159,47,88,222,220,48,155,
207,25,237,239,19,246,250,88,227,40,54,107,170,186,244,227,57,49,56,106,109,208,218,146,142,135,164,73,196,237,229,37,113,63,161,204,197,248,213,248,212,190,206,143,182,84,43,207,71,211,84,180,13,24,23,
17,186,208,167,94,41,255,157,250,209,102,187,53,37,122,2,241,238,159,119,152,255,241,223,255,47,159,25,23,48,95,46,40,178,53,117,93,237,208,178,218,64,167,52,113,146,82,118,21,55,111,206,72,199,125,22,
203,5,77,85,238,184,213,85,85,237,2,162,181,22,14,118,16,134,168,78,97,77,72,20,57,138,114,35,115,44,60,215,222,163,6,132,153,1,218,200,109,230,130,144,213,242,158,55,47,94,208,31,143,73,251,3,92,32,142,
182,205,114,45,44,16,79,156,107,234,70,184,60,85,77,219,22,44,166,75,180,145,160,227,48,73,24,77,246,177,65,200,114,54,163,44,115,242,205,90,248,36,86,62,4,231,20,111,207,206,176,56,30,127,248,148,202,
227,26,166,243,57,69,81,72,232,71,215,249,192,115,135,54,22,155,196,216,208,178,154,207,69,117,210,52,168,246,251,96,132,170,22,25,100,219,52,4,46,22,13,180,11,176,198,209,235,13,137,147,148,205,90,0,
95,26,60,255,162,245,114,59,124,240,132,204,190,219,182,33,30,164,204,238,46,185,57,127,79,127,208,39,8,2,34,95,177,151,69,77,81,150,126,105,92,75,52,100,39,177,147,157,42,185,189,184,33,142,83,1,102,
105,77,20,247,73,146,152,213,98,245,125,114,142,103,145,36,105,2,117,203,124,49,229,237,171,183,140,247,39,164,189,62,189,52,97,189,201,169,155,109,10,79,229,131,218,53,104,141,113,78,2,90,172,162,172,
10,175,92,242,210,178,6,148,95,230,151,165,60,240,202,59,171,181,14,136,194,148,201,193,49,198,105,22,179,251,239,213,9,74,20,96,248,159,142,142,93,39,169,128,40,77,89,205,103,44,102,183,172,179,28,23,
132,164,189,148,241,193,33,86,105,150,203,153,15,231,233,168,171,130,170,106,124,60,102,203,102,117,207,236,226,134,254,120,34,172,164,186,97,124,112,64,215,180,100,121,38,223,97,37,62,0,165,13,97,16,
10,19,38,223,112,121,126,78,218,159,16,247,7,104,165,200,54,107,218,170,17,245,153,231,183,43,45,244,197,206,67,217,118,92,151,102,75,4,21,216,89,85,249,217,110,215,226,162,136,40,72,8,195,68,226,234,
70,251,124,240,241,39,148,213,154,133,239,154,182,90,86,235,130,223,8,107,223,58,76,107,255,25,129,82,53,109,181,226,252,245,59,178,206,18,37,9,147,227,135,104,58,178,229,66,242,158,145,61,80,219,181,
88,27,97,140,230,246,242,154,124,147,17,199,33,52,45,218,58,38,135,199,116,149,20,107,117,91,179,13,29,211,86,19,58,139,82,29,139,217,140,233,221,130,104,48,96,184,127,128,106,107,170,60,23,105,98,93,
130,14,182,90,66,239,75,80,36,105,44,123,50,47,98,40,235,210,251,111,188,250,164,107,81,198,126,159,234,102,28,40,77,20,143,56,62,126,68,87,103,100,69,46,56,113,79,41,209,157,236,70,64,237,80,192,45,13,
73,175,79,155,229,220,221,92,49,189,187,103,177,94,99,163,132,189,195,67,34,23,10,224,77,131,209,29,77,85,208,117,50,6,93,78,231,220,221,223,161,141,225,225,147,167,164,97,200,38,47,233,77,38,52,121,65,
227,169,172,162,132,50,196,131,144,48,8,200,215,25,235,217,45,55,211,5,201,100,34,114,233,170,162,42,114,81,229,249,98,87,155,192,59,108,65,7,142,32,10,233,154,173,231,194,171,254,188,25,178,235,228,76,
53,70,11,236,205,132,244,251,9,73,108,49,54,38,237,141,168,243,66,168,8,59,105,231,150,190,42,221,92,231,209,29,230,223,255,111,255,199,103,85,81,99,194,144,197,114,73,93,228,30,246,216,122,85,77,75,224,
66,48,66,161,155,207,102,158,89,46,51,233,218,39,92,117,141,212,239,198,88,130,56,145,234,79,57,198,163,49,157,133,229,124,78,89,74,238,101,215,181,30,160,38,91,233,118,139,254,244,49,131,46,137,185,124,
247,146,139,183,175,9,162,30,253,94,143,32,8,24,238,237,139,242,165,200,125,76,153,199,10,27,135,211,26,165,106,110,46,239,112,206,97,173,195,26,199,100,111,159,77,89,146,109,86,158,215,34,157,70,171,
52,65,16,145,173,215,188,123,245,138,80,7,12,246,247,232,143,70,172,214,107,105,243,171,18,109,52,85,221,9,0,105,91,81,104,77,211,148,223,135,149,52,162,68,106,124,117,178,93,66,42,237,8,194,128,36,238,
49,26,238,51,57,58,225,230,226,140,205,106,33,149,185,113,30,111,42,140,12,181,91,196,121,204,104,215,17,70,41,198,58,102,183,55,220,221,94,211,97,24,13,135,24,23,176,127,116,76,94,20,2,168,218,58,155,
219,22,171,12,70,65,89,151,220,93,92,19,36,61,58,165,48,206,17,165,3,210,180,199,106,181,246,65,40,21,81,20,210,41,69,16,132,244,210,152,219,187,59,94,189,120,193,104,56,228,232,244,49,105,191,79,150,
109,200,54,43,143,97,216,190,136,130,60,176,214,9,240,173,150,3,89,130,229,149,175,176,43,186,14,1,142,185,16,173,141,28,244,147,67,62,252,248,57,121,190,230,237,203,23,50,95,238,58,58,173,189,134,28,
105,233,59,124,0,6,59,149,70,93,213,164,113,76,91,149,204,167,247,220,220,79,233,15,134,88,107,56,60,62,34,10,18,54,171,140,86,181,222,237,45,113,118,206,57,90,106,242,124,197,252,106,134,137,66,154,174,
196,6,33,123,199,199,228,171,149,152,187,170,198,59,52,197,113,25,56,177,165,183,109,201,203,111,190,197,197,125,30,127,244,156,38,203,40,179,141,223,199,248,194,69,91,31,210,227,175,39,165,118,135,25,
108,217,64,50,242,10,2,139,81,134,32,76,72,147,62,113,210,99,239,232,33,159,252,232,71,92,190,251,142,179,55,47,101,94,45,233,49,34,219,115,110,103,226,83,158,141,180,205,146,104,105,80,173,161,42,75,
84,87,112,125,126,67,209,116,244,6,35,246,142,79,72,194,132,197,116,10,106,139,99,182,196,73,130,49,146,139,124,117,113,193,122,185,166,63,30,73,49,102,28,7,15,78,168,242,146,50,95,211,52,165,31,165,116,
184,32,196,57,89,224,47,238,239,185,189,185,37,25,77,152,236,31,209,20,25,69,190,161,242,151,146,168,74,228,100,46,242,13,46,12,69,136,81,87,34,90,64,209,214,157,63,3,240,5,138,21,9,170,9,177,54,98,184,
247,144,15,63,122,206,245,217,183,92,221,94,121,195,222,150,87,37,3,140,78,183,219,63,70,84,91,74,58,147,222,168,199,242,250,142,233,253,53,179,235,27,208,33,253,193,128,116,52,38,142,34,202,205,70,184,
61,30,97,108,67,199,160,159,144,79,87,92,158,191,103,118,123,131,142,34,217,187,104,203,104,111,66,181,222,120,101,146,32,13,170,186,194,36,17,233,160,7,85,203,106,62,101,62,95,144,140,198,12,39,123,116,
69,37,59,153,218,115,112,140,243,158,7,145,124,74,214,131,218,145,93,219,78,237,28,253,74,137,146,175,246,233,119,218,69,104,58,172,214,124,248,163,31,211,108,86,220,221,223,81,250,207,211,31,38,104,204,
46,80,166,237,100,36,100,254,139,223,249,195,207,70,147,9,163,241,132,77,149,11,22,160,200,119,21,69,215,118,88,109,49,90,73,245,234,111,31,49,174,40,226,48,246,202,17,209,236,71,97,130,179,17,65,144,
112,112,116,200,60,155,113,241,242,59,170,102,107,186,218,250,14,61,229,206,88,159,96,36,11,155,166,41,113,198,144,244,135,220,95,95,81,231,5,97,26,97,93,136,81,154,163,147,135,148,13,187,124,214,202,
207,106,131,40,164,42,55,148,85,198,114,182,36,8,35,73,95,114,150,189,189,125,242,170,33,91,174,168,138,146,186,22,9,84,221,66,20,167,148,69,206,183,95,189,64,119,29,15,31,61,34,233,13,89,46,23,52,181,
220,202,91,76,43,40,9,65,240,25,168,157,55,129,108,219,168,182,109,49,70,201,255,127,28,17,39,9,253,116,200,193,254,49,147,227,67,126,241,211,127,102,113,127,67,163,124,53,136,18,253,50,45,198,167,66,
109,205,21,141,87,182,208,105,92,24,162,105,153,222,221,178,94,101,130,57,142,82,130,36,102,180,55,161,105,26,242,205,70,90,211,186,146,67,223,90,116,7,101,93,112,119,113,35,21,188,86,36,105,159,94,127,
72,213,84,108,214,27,242,124,67,89,230,148,121,237,45,229,154,126,26,81,172,151,156,189,121,203,222,222,62,79,158,125,72,211,52,204,167,183,52,181,236,67,148,21,157,182,106,59,177,109,27,243,27,240,46,
175,176,169,101,14,227,194,144,40,73,177,206,17,69,9,15,30,60,225,233,243,143,184,185,185,228,215,63,253,39,80,94,153,210,249,64,28,175,191,223,210,214,182,129,214,157,18,234,159,6,186,78,24,229,119,183,
247,180,45,104,23,209,212,181,92,176,131,1,113,175,207,114,190,68,121,8,151,44,181,192,25,225,164,223,207,239,89,221,221,145,12,199,116,13,216,48,98,116,112,72,182,90,83,20,107,154,170,248,30,214,70,135,
177,142,208,6,80,103,92,157,159,49,156,28,113,250,228,9,171,217,140,210,199,223,181,157,112,216,101,36,45,81,132,91,249,220,150,106,169,61,203,9,109,113,198,17,196,145,28,248,189,1,15,79,31,243,224,233,
19,222,189,252,53,223,252,234,151,30,167,33,73,87,218,7,58,41,99,119,121,16,85,35,140,37,237,23,121,198,104,58,12,85,153,131,170,177,6,148,137,192,134,40,173,24,238,237,211,79,18,138,213,114,139,27,163,
172,75,234,166,32,116,14,165,106,102,179,57,89,150,17,71,49,90,105,108,156,50,222,223,35,187,189,167,174,5,202,39,0,186,198,119,141,17,166,131,124,185,226,246,246,138,253,135,143,25,141,198,148,155,245,
78,73,179,61,239,149,81,132,161,165,109,36,135,88,20,88,120,245,146,15,187,209,62,132,221,58,2,23,145,164,3,158,124,252,35,158,126,244,140,151,63,255,7,174,46,206,124,55,83,123,69,143,193,26,227,33,106,
187,72,224,221,46,168,173,42,202,22,70,163,30,179,235,91,202,162,100,255,201,41,195,129,140,49,131,36,37,142,18,154,162,164,17,178,21,93,83,225,162,136,180,159,80,174,114,238,174,174,41,178,53,195,201,
30,189,40,161,85,134,184,223,167,92,175,229,191,104,90,202,82,248,76,54,10,72,71,125,186,162,100,122,115,205,106,185,102,124,114,194,160,63,16,21,96,45,163,81,31,213,134,234,244,46,182,83,126,120,153,
193,183,181,116,58,2,254,19,245,159,9,34,194,32,34,74,123,236,31,61,226,232,232,148,155,183,111,57,59,123,75,222,148,222,171,225,241,28,157,207,167,244,190,40,81,248,24,204,241,112,244,89,96,67,126,248,
227,31,19,244,83,238,110,111,200,214,27,137,135,147,95,69,167,244,174,157,163,145,121,80,211,121,87,236,22,25,160,12,113,154,18,4,9,251,123,7,28,28,29,49,207,238,248,213,79,254,158,32,136,104,181,112,
96,228,183,148,69,157,204,153,58,207,15,241,230,27,58,58,109,233,143,134,148,101,201,245,217,59,92,24,83,55,21,81,16,18,4,129,216,152,59,69,230,111,230,182,169,209,198,137,154,167,46,216,108,54,220,94,
222,50,28,92,139,243,160,0,0,32,0,73,68,65,84,15,233,13,135,68,54,100,180,191,207,106,189,246,23,90,33,137,244,62,16,60,73,18,140,106,56,123,253,146,200,6,252,214,239,255,91,42,165,196,69,154,103,158,
73,33,204,151,178,169,252,75,236,59,26,165,104,154,154,174,171,133,193,239,36,247,53,74,98,250,201,128,135,167,79,25,238,237,241,15,127,251,31,89,188,127,75,216,75,60,42,193,203,170,252,12,174,227,251,
48,152,214,195,229,118,234,218,78,19,245,122,108,150,43,238,46,47,72,82,193,203,70,81,136,14,2,70,147,125,10,79,253,244,74,110,234,70,220,198,109,81,83,117,25,183,87,51,6,227,1,157,214,184,48,161,63,26,
145,173,124,108,99,145,11,15,103,171,163,54,150,225,104,64,149,173,56,123,253,134,131,227,19,78,30,158,178,92,44,201,55,153,184,252,20,62,116,194,138,171,176,21,253,47,219,67,205,203,193,92,224,8,162,
4,103,67,122,233,144,39,31,124,196,195,15,158,113,125,117,206,63,255,237,95,99,172,168,81,172,179,222,201,237,19,160,182,36,71,37,15,174,152,77,58,47,159,140,4,148,21,8,178,99,54,157,139,158,58,77,169,
202,14,99,21,73,127,64,20,197,100,203,204,47,185,182,122,234,78,52,252,117,73,158,175,184,187,188,21,94,188,18,86,251,100,111,143,219,235,75,81,66,85,114,9,118,77,135,234,156,200,89,93,64,91,20,156,189,
125,195,227,231,159,48,153,140,185,187,189,150,121,171,18,206,139,86,70,230,245,62,159,214,108,255,218,143,172,58,165,176,97,128,179,33,198,57,6,253,9,143,63,250,1,167,79,159,114,246,234,43,190,249,213,
231,212,77,75,235,127,207,109,184,121,167,148,48,108,124,88,187,40,208,26,233,42,182,217,96,222,137,89,215,13,129,133,170,232,176,65,228,177,205,48,156,28,210,79,82,22,179,169,188,107,85,233,151,197,34,
109,238,186,138,217,205,45,217,106,67,58,26,136,98,40,140,232,165,9,217,98,41,85,123,83,83,55,160,172,36,109,217,32,32,112,134,229,237,29,171,229,154,135,31,61,199,1,101,41,174,218,109,44,35,218,160,58,
77,211,125,63,198,236,124,247,213,250,207,42,140,82,180,53,132,65,204,104,114,204,243,79,127,151,71,143,31,113,246,226,95,249,250,171,175,4,67,174,252,248,166,85,222,156,38,99,52,173,172,87,177,120,7,
182,119,151,91,99,8,211,132,200,88,110,175,175,185,191,189,145,11,55,12,41,202,146,116,60,164,151,166,172,103,115,121,134,59,129,201,5,73,76,24,25,54,243,25,247,119,183,84,89,70,127,127,79,138,63,23,146,
70,137,40,126,26,49,19,214,77,35,206,96,191,164,182,104,110,47,174,193,104,30,60,62,69,249,48,19,17,189,64,211,136,138,137,29,175,94,14,121,249,17,218,173,240,17,173,28,46,116,132,97,196,104,255,132,167,
207,127,196,179,31,124,74,126,117,205,151,191,250,25,181,239,10,232,188,233,117,107,102,219,181,197,157,215,242,131,249,175,255,155,255,234,179,55,47,95,161,242,134,103,63,248,1,141,82,204,238,239,101,
217,231,103,191,198,89,63,46,240,76,15,255,120,181,64,221,54,56,37,135,220,96,48,230,96,255,144,254,254,30,87,119,103,252,243,95,254,63,244,162,62,241,72,164,74,157,18,72,148,117,22,237,51,57,205,111,
100,123,110,227,200,182,115,95,231,132,183,125,241,250,13,77,221,162,93,64,20,199,40,20,15,78,30,208,40,77,190,94,209,181,45,69,145,83,215,13,96,49,198,210,212,25,211,155,25,90,25,14,14,15,208,86,227,
194,136,251,251,123,113,122,214,149,132,80,171,150,166,233,124,69,30,243,250,219,87,80,86,60,255,209,143,88,172,215,44,103,83,186,86,0,81,18,196,96,5,187,140,149,155,83,177,35,250,89,23,146,196,9,113,
24,177,55,57,224,240,193,41,54,116,252,228,111,254,146,229,197,59,122,71,251,20,149,31,99,249,255,71,185,236,91,180,183,223,135,129,204,196,203,178,222,49,88,180,150,5,228,248,96,159,245,124,202,236,234,
146,116,48,160,238,90,92,24,162,58,205,222,209,33,117,219,145,101,107,175,133,110,105,26,45,8,218,174,166,234,74,174,222,95,96,140,33,8,99,154,166,163,63,26,73,82,85,145,83,85,133,232,212,91,47,255,211,
210,205,80,149,252,234,103,191,96,255,193,9,131,189,125,230,211,59,209,36,27,97,180,160,12,198,56,159,46,229,195,56,60,243,35,140,99,130,32,34,142,98,14,14,142,249,240,249,15,25,28,28,114,246,230,5,159,
255,228,175,72,2,77,137,162,44,197,89,89,213,173,0,214,124,5,100,156,217,101,223,110,113,176,173,82,30,164,38,44,125,231,66,172,86,220,223,92,248,101,120,67,215,26,148,117,140,15,246,72,7,35,150,179,123,
241,126,128,15,43,55,68,198,120,43,122,197,213,251,43,180,115,66,88,52,1,189,94,159,229,108,33,138,166,170,220,250,93,100,92,21,134,196,113,196,122,57,231,213,171,215,60,250,232,35,186,170,32,91,175,188,
82,68,44,67,70,59,143,247,149,67,169,237,36,8,92,40,150,18,180,227,130,144,131,195,83,62,254,241,239,48,24,247,185,120,251,130,55,95,253,156,166,105,40,170,109,192,182,4,192,183,157,151,98,2,78,59,239,
48,245,177,231,218,183,240,59,206,138,68,96,214,85,67,91,231,44,166,119,52,157,161,170,106,76,16,146,142,71,164,81,196,122,185,144,171,84,130,82,65,43,226,56,194,154,134,217,108,202,237,245,61,233,176,
143,85,10,215,235,137,75,123,179,65,105,33,163,214,173,64,250,234,166,145,164,171,209,144,197,245,13,239,223,157,241,236,211,79,233,170,130,124,181,146,58,222,79,9,186,109,172,163,95,204,74,29,46,138,
190,56,73,137,163,152,56,238,243,240,244,35,62,254,173,223,98,208,31,112,249,234,87,124,243,235,95,160,67,75,103,140,236,0,145,52,48,57,16,13,198,89,156,54,158,211,227,51,2,26,81,251,96,36,14,50,29,12,
232,138,130,249,252,158,245,114,65,81,214,4,81,44,124,164,222,136,36,142,201,243,76,166,6,126,231,226,162,152,209,168,71,177,88,113,119,123,205,237,245,53,241,120,140,209,138,176,63,192,32,254,152,170,
44,232,154,154,202,239,210,170,186,37,236,15,72,211,132,219,119,103,228,117,205,131,39,79,209,173,34,223,100,52,72,54,183,92,150,129,44,203,61,253,114,187,219,83,70,225,108,64,28,37,36,189,1,199,143,63,
226,217,243,31,177,119,112,192,205,183,95,241,243,127,254,123,116,162,105,60,121,87,172,235,157,223,165,106,57,83,182,177,179,226,72,196,252,209,159,254,217,103,81,18,241,254,205,27,170,121,193,199,191,
253,67,110,111,111,201,215,75,191,64,147,153,163,242,21,168,66,121,3,135,136,251,227,48,34,10,83,210,116,192,193,193,17,233,100,200,253,226,146,47,126,242,215,4,181,34,61,152,80,214,62,74,204,191,0,181,
79,129,178,38,6,221,210,109,185,15,158,158,168,140,129,90,218,232,116,216,103,181,156,51,191,190,33,233,165,40,163,233,167,3,140,117,12,70,19,202,170,34,203,86,82,121,208,18,198,9,113,18,99,232,200,242,
21,215,87,215,28,29,31,19,68,33,235,77,142,11,220,142,223,95,215,149,151,50,73,142,108,220,75,25,140,7,188,249,238,13,229,114,201,233,135,31,115,125,125,45,1,229,219,118,209,47,158,148,175,44,64,230,181,
198,6,18,11,24,198,28,28,157,48,57,62,161,51,138,127,249,187,191,225,234,219,23,140,143,247,105,140,68,146,25,163,81,70,251,101,91,39,28,12,27,64,211,122,245,145,162,174,106,89,232,24,207,246,22,182,48,
81,18,176,89,10,198,185,172,27,202,178,34,12,2,194,52,165,63,24,9,22,57,203,196,228,214,150,212,64,24,137,29,188,170,10,110,174,174,216,155,236,145,12,198,204,103,75,146,184,71,94,122,250,161,231,3,213,
101,181,109,230,112,113,76,20,57,94,126,245,21,39,71,39,52,109,203,38,219,176,29,170,43,37,23,157,180,159,236,136,152,97,24,251,239,34,101,50,57,224,233,199,159,80,183,45,47,95,124,201,139,95,252,163,
68,82,120,87,165,11,2,242,117,41,202,22,132,95,111,141,69,27,71,167,53,93,93,129,150,14,64,249,46,104,203,220,1,8,195,128,192,40,98,187,237,18,229,128,137,130,152,184,215,39,138,66,54,75,81,74,116,158,
38,168,77,128,181,1,97,20,162,44,156,191,125,207,120,127,143,36,9,169,27,133,214,29,217,58,163,174,69,67,221,121,7,105,231,121,46,97,154,98,186,142,243,55,111,121,242,225,135,108,150,43,159,100,180,251,
177,132,86,105,245,46,116,93,91,139,113,22,99,2,156,139,120,248,228,35,62,248,193,39,52,180,188,248,226,95,185,124,247,45,170,41,89,174,75,90,159,19,173,157,221,161,163,149,210,88,27,160,172,165,241,123,
176,110,171,67,87,114,240,201,101,35,151,46,74,81,228,146,73,61,159,207,101,60,208,136,135,102,184,183,79,18,198,172,231,115,81,238,52,165,236,0,148,84,146,214,24,22,203,57,215,151,55,164,227,49,81,20,
97,93,68,87,215,20,69,70,150,229,116,181,4,197,43,107,69,12,225,156,196,125,110,150,108,214,57,227,253,61,22,243,185,92,118,62,193,203,11,106,252,120,78,186,65,23,196,4,113,136,181,1,233,96,196,163,103,
159,240,232,131,167,40,5,119,151,239,120,255,242,75,242,188,194,134,49,129,51,228,197,118,73,174,37,41,206,185,93,177,40,35,19,37,145,139,109,189,11,80,209,202,208,52,173,204,216,203,138,217,253,148,162,
42,120,248,244,3,246,71,3,170,170,198,245,70,132,129,35,95,175,69,74,94,203,115,102,66,71,154,196,148,235,13,203,249,156,249,116,78,111,50,18,244,178,11,41,243,92,64,140,117,65,93,181,66,12,174,37,207,
194,134,49,105,63,101,121,117,131,77,132,168,186,89,206,197,119,161,60,51,9,118,153,24,218,87,230,74,43,76,16,18,197,9,123,147,3,78,62,248,152,211,39,31,17,58,199,234,230,156,207,127,242,215,152,200,81,
53,45,121,38,75,239,78,121,245,92,39,24,109,171,157,116,198,245,182,251,86,152,255,236,15,255,232,51,227,66,162,52,225,242,242,61,171,139,27,78,158,61,102,54,93,160,90,237,219,54,153,255,168,45,201,161,
109,133,99,239,2,194,176,199,104,48,230,228,193,67,84,207,241,234,213,215,252,250,111,255,138,106,177,230,224,241,19,26,39,21,74,67,43,78,50,37,252,148,32,140,113,214,160,116,75,81,73,128,128,86,26,163,
37,104,187,245,108,107,148,162,55,232,179,94,206,185,62,63,19,251,121,7,189,52,5,173,152,28,236,83,183,29,155,229,146,170,174,201,139,156,170,174,136,211,1,109,153,65,87,243,238,221,59,142,143,143,49,
65,76,91,119,24,231,216,172,22,180,109,233,131,194,125,186,84,45,246,247,116,50,96,118,119,77,177,218,16,166,17,89,150,237,76,15,170,245,146,210,86,230,204,86,91,162,40,34,8,35,6,233,144,7,39,167,12,143,
15,185,186,189,225,255,251,15,255,23,171,243,215,28,28,31,211,197,9,85,37,92,14,163,148,87,38,105,172,118,4,97,140,54,154,48,8,216,228,50,35,165,221,222,204,10,234,90,148,64,13,160,29,253,193,128,98,61,
163,218,204,41,219,154,166,129,40,20,167,241,112,111,95,242,1,202,138,170,105,169,61,232,45,8,44,129,182,180,170,226,245,235,215,12,134,99,134,251,135,96,132,235,82,20,153,79,26,106,36,27,179,147,113,
83,167,53,88,75,146,134,156,191,121,75,210,79,169,234,194,95,120,72,92,34,45,40,153,199,26,163,101,153,23,197,36,113,194,195,7,79,56,126,248,144,101,182,226,23,255,242,143,188,253,242,115,34,103,49,65,
68,163,228,197,68,91,162,40,32,176,14,163,21,54,8,209,198,226,92,76,210,75,41,51,81,120,169,93,102,167,246,139,92,159,134,4,232,32,66,204,133,27,242,44,103,58,93,97,148,44,144,123,227,125,210,36,102,179,
90,249,152,69,241,46,216,48,20,190,76,40,157,201,235,215,175,137,211,30,253,241,144,48,78,105,138,146,186,40,168,219,194,47,163,197,4,164,149,197,24,71,156,166,36,81,200,124,177,196,90,9,88,175,155,70,
208,16,10,90,37,41,93,93,211,10,174,35,78,68,81,148,140,249,248,7,63,230,228,241,41,155,245,146,159,255,244,31,169,86,183,232,186,226,238,126,37,120,117,100,204,98,173,165,109,21,198,6,187,93,137,50,142,
48,112,84,101,129,209,29,202,138,58,75,33,255,94,132,42,26,99,53,10,203,244,110,206,213,237,45,235,205,70,42,255,186,67,217,128,209,193,17,161,181,114,192,161,80,58,144,252,10,165,5,59,98,52,77,181,230,
229,119,175,232,237,31,146,36,61,194,56,161,92,175,36,238,79,67,221,53,208,25,65,71,119,50,226,11,146,132,182,204,169,170,70,168,151,141,20,120,218,88,143,202,144,220,92,180,120,14,130,56,166,151,244,
24,79,142,248,248,211,223,101,56,26,179,89,47,248,238,139,95,178,154,95,115,123,117,37,193,230,90,240,32,149,79,206,50,198,18,68,9,198,56,2,27,96,209,66,2,240,217,182,210,29,107,104,68,186,42,160,54,199,
96,60,36,155,206,88,205,102,76,111,111,232,66,73,220,171,218,142,254,104,143,196,6,20,235,156,170,21,99,99,85,213,152,40,100,56,28,160,186,150,245,108,198,197,217,57,147,39,79,176,214,146,246,199,116,
101,69,93,123,220,138,1,141,197,25,79,184,180,134,222,100,143,245,116,42,158,216,170,166,106,69,145,164,141,147,142,204,122,204,135,18,48,98,20,197,164,233,128,225,232,128,167,63,252,109,38,123,135,52,
85,193,229,155,111,248,249,223,255,45,141,110,169,187,206,47,124,193,250,195,94,107,81,193,57,235,36,118,82,25,154,186,161,85,210,193,153,63,254,163,63,254,44,10,132,169,173,3,71,94,230,212,171,2,21,40,
170,109,222,227,118,9,226,23,79,129,182,184,40,36,14,83,70,253,9,7,15,143,169,76,203,155,87,95,243,205,127,250,27,76,1,123,15,79,81,105,72,211,129,85,194,112,86,88,172,13,176,198,98,141,35,142,19,34,223,
70,121,58,15,46,144,164,159,166,22,206,70,224,213,49,233,176,199,236,246,134,124,181,160,215,239,211,2,105,218,167,46,27,246,15,14,200,138,92,120,46,149,108,205,203,186,195,185,128,166,108,88,111,22,92,
156,95,242,193,147,15,72,198,99,130,48,34,207,10,47,127,170,176,90,170,202,214,171,186,154,182,67,59,97,200,183,77,69,229,15,119,237,31,36,237,15,25,107,21,46,8,9,130,152,36,234,113,114,250,132,104,56,
224,230,230,154,127,253,135,255,151,242,242,61,131,201,128,120,127,159,186,17,54,136,84,28,18,76,17,4,17,65,16,98,108,192,100,124,192,254,254,62,235,141,135,163,9,10,80,120,24,187,164,32,185,44,109,16,
16,5,82,233,215,101,78,217,72,66,82,24,69,24,23,50,28,77,200,54,25,69,46,28,156,166,150,195,95,89,139,179,154,170,42,249,238,187,215,40,58,70,7,7,164,189,30,170,105,41,139,141,116,51,29,187,228,37,237,
191,43,180,193,133,17,85,157,251,209,141,28,42,214,138,60,207,40,133,213,142,56,238,225,108,72,20,199,60,122,244,1,189,189,3,178,108,205,187,215,223,112,241,221,87,68,145,193,152,80,56,246,104,12,162,
131,222,85,245,161,195,104,71,146,244,121,240,224,49,206,106,86,139,57,202,171,46,240,102,163,109,41,221,41,137,174,3,48,214,81,172,55,212,101,78,150,45,176,46,194,134,33,29,138,222,120,76,96,44,203,197,
220,243,199,133,88,89,148,57,170,246,180,210,98,205,251,119,103,216,180,79,218,31,50,25,143,201,86,75,169,242,125,148,38,74,152,248,116,178,132,68,75,216,124,231,73,176,248,46,164,219,150,71,117,131,49,
150,56,237,227,130,144,48,236,241,163,223,251,125,246,142,14,88,173,231,156,191,253,134,197,244,134,56,48,44,102,75,202,90,212,34,162,52,147,10,222,6,142,208,57,180,13,72,147,17,31,60,123,78,219,201,243,
174,180,140,166,48,110,151,163,70,219,236,34,238,180,113,244,251,125,22,247,247,204,166,51,180,11,232,141,132,232,169,173,102,176,127,128,110,27,242,108,37,60,35,90,9,194,81,134,32,8,208,86,209,150,21,
239,95,157,161,163,136,209,209,9,73,28,82,102,43,161,160,54,210,13,122,77,131,116,17,90,118,20,104,37,135,172,2,173,221,54,129,219,155,168,28,81,152,16,70,9,81,146,178,119,248,128,135,79,62,36,76,82,178,
205,134,205,226,22,167,74,230,183,23,228,181,36,92,53,77,69,213,8,98,59,8,132,123,239,66,135,181,1,253,193,30,123,147,61,145,94,119,226,86,110,61,190,164,243,177,133,206,41,233,170,233,232,15,4,147,49,
91,46,200,54,5,97,191,79,93,8,122,187,63,26,139,23,166,148,140,234,182,170,229,146,177,1,81,28,209,84,57,217,122,197,98,182,32,26,244,137,251,61,9,26,42,43,121,119,219,86,158,73,191,100,55,218,72,87,23,
218,239,159,147,237,126,39,144,127,191,157,166,88,109,136,226,132,56,237,49,62,56,230,244,163,31,210,79,135,64,199,244,253,59,222,124,253,11,154,118,3,214,80,183,13,70,139,211,26,37,114,115,231,4,199,
16,68,9,105,58,166,151,166,130,16,81,222,119,241,199,127,244,95,126,182,205,181,52,198,73,138,189,134,182,42,197,61,232,113,197,29,130,183,13,180,33,138,34,194,48,102,208,31,115,252,248,17,157,238,184,
159,93,243,235,191,251,43,212,106,65,127,112,64,114,116,40,138,158,70,22,178,90,91,226,56,37,136,69,155,62,26,236,113,244,232,132,245,102,193,102,181,20,37,131,39,250,181,218,74,235,105,36,228,64,42,153,
128,94,191,207,252,254,150,213,124,198,160,63,196,104,75,127,52,2,52,147,131,35,54,155,156,117,38,114,202,198,75,148,226,84,178,105,47,206,222,241,242,155,87,28,238,31,49,26,13,233,141,39,228,121,70,153,
173,189,194,66,28,105,98,107,247,179,214,192,73,106,151,111,153,69,101,161,49,90,82,100,194,32,38,140,99,122,189,1,39,15,30,227,210,62,203,229,140,87,95,255,146,171,151,95,19,134,142,253,71,143,169,149,
28,138,45,10,167,12,214,105,92,16,225,194,148,40,74,56,57,62,101,48,25,115,254,238,157,128,185,186,214,99,32,204,142,5,169,181,245,10,99,145,87,57,23,226,172,101,54,191,99,54,157,114,244,224,17,97,44,
122,229,32,140,24,140,198,172,150,115,234,166,162,170,229,69,169,154,22,99,67,146,48,96,126,119,203,217,171,87,116,77,203,227,71,143,25,237,29,48,155,77,105,27,161,153,42,45,35,4,231,66,191,14,20,252,
109,24,58,186,78,32,111,146,195,224,231,238,70,17,132,33,81,20,19,39,41,79,158,126,68,60,152,176,94,175,185,58,123,195,171,47,63,167,169,50,20,18,225,216,116,29,129,15,239,208,26,140,115,88,107,9,92,200,
120,124,200,167,63,250,109,150,171,41,175,95,126,43,122,101,63,211,236,58,233,198,140,81,62,33,202,236,184,243,218,19,26,151,211,57,55,119,247,148,101,77,210,239,97,53,88,19,50,28,143,189,57,105,67,83,
21,148,121,233,25,60,18,6,111,129,205,114,197,197,217,5,54,12,121,246,209,199,88,173,88,45,215,94,151,223,238,246,80,2,79,212,223,3,208,84,71,235,23,240,205,246,192,245,151,182,115,1,218,31,74,191,253,
111,254,29,65,18,178,156,223,243,250,187,175,185,124,255,14,167,161,220,108,88,151,13,157,178,146,107,139,38,78,122,66,74,245,236,163,253,195,83,126,231,247,255,45,55,151,111,57,127,251,134,6,80,30,81,
161,180,162,211,62,190,116,203,86,241,124,33,101,3,194,192,176,186,95,114,125,123,203,106,179,196,70,162,114,138,226,84,92,164,85,73,182,94,210,148,57,141,199,29,183,77,131,209,6,103,21,217,114,198,245,
229,21,209,112,196,195,103,31,97,202,138,124,189,246,191,198,251,15,180,37,76,82,154,166,193,98,118,208,47,107,141,255,158,189,71,38,112,132,81,44,93,96,58,224,224,240,132,199,207,158,19,216,128,229,98,
206,221,213,25,206,212,204,110,206,153,206,86,152,80,46,216,178,172,64,43,156,9,8,163,4,163,44,54,8,57,60,121,194,233,233,99,222,191,254,134,77,150,97,141,80,113,69,253,38,65,40,214,143,109,5,23,45,168,
129,94,47,102,117,59,229,254,254,142,188,40,24,239,141,5,134,168,53,189,209,16,211,54,20,69,46,68,208,170,164,172,75,26,165,72,251,125,108,219,112,127,123,205,245,249,25,42,30,112,242,232,17,182,174,5,
141,208,249,61,150,210,210,173,106,249,14,141,214,146,43,189,29,51,105,69,96,69,175,104,181,197,58,75,146,166,164,189,62,123,135,143,120,246,252,83,226,56,166,174,10,166,151,239,185,189,122,203,122,126,
135,50,142,170,219,142,242,196,200,152,38,17,90,203,168,48,237,141,152,28,63,225,244,241,99,238,47,206,201,171,220,75,132,53,230,79,254,244,207,62,83,62,224,86,27,237,183,229,221,142,184,182,163,174,117,
45,214,40,156,139,113,54,102,48,24,115,252,240,33,155,106,195,114,122,197,139,159,253,3,229,213,57,46,30,208,63,121,68,217,202,50,178,211,50,246,24,12,198,244,250,35,140,14,216,159,28,112,124,122,194,
87,95,252,140,229,124,78,215,8,101,211,250,246,198,120,101,70,219,214,180,117,187,147,92,89,27,146,246,6,220,94,95,48,191,189,97,52,25,139,114,34,12,209,192,222,225,17,155,245,138,186,46,169,10,201,186,
173,155,154,48,76,72,210,62,183,151,55,92,188,123,195,131,7,15,120,244,193,83,26,5,171,197,156,182,174,118,82,55,163,141,223,47,24,47,92,83,223,39,191,27,255,240,24,67,24,167,132,113,76,146,12,120,112,
250,4,29,197,220,221,92,242,230,219,47,120,249,139,159,65,11,251,39,15,105,195,216,111,222,91,180,81,4,161,140,112,162,40,98,50,60,224,244,201,51,106,213,242,197,231,255,44,21,186,113,116,74,126,173,115,
14,163,36,237,39,114,238,55,152,234,34,225,140,147,4,173,12,211,219,107,174,174,47,73,210,84,2,64,92,136,209,154,48,138,36,245,190,200,233,234,198,235,114,101,204,177,183,55,161,173,75,238,174,46,81,45,
124,242,163,31,163,93,192,102,185,164,107,106,140,159,201,27,35,11,49,89,64,90,90,213,250,80,13,237,231,245,29,129,117,132,65,64,16,197,196,201,128,211,199,207,192,133,44,151,11,206,223,190,226,237,55,
95,208,85,43,48,1,81,42,46,211,173,50,100,52,25,130,50,88,27,18,6,49,167,143,159,243,193,199,207,121,243,250,5,47,190,248,133,44,248,149,4,118,111,149,59,198,136,252,81,89,33,181,106,255,179,109,37,144,
214,106,242,69,198,106,61,167,42,11,70,147,125,255,207,3,198,147,3,49,130,21,146,172,214,121,121,97,215,65,16,198,36,161,165,171,114,230,247,183,36,131,17,207,158,127,66,182,222,80,230,153,15,251,208,
222,37,41,90,164,173,156,24,45,47,95,167,132,109,210,181,18,126,110,156,67,187,144,131,163,71,252,248,247,254,0,29,88,166,183,87,156,191,123,203,229,217,27,76,87,210,86,53,171,77,65,211,105,249,238,209,
56,235,48,129,140,203,162,184,207,211,103,159,242,227,223,255,93,190,250,213,191,240,246,155,47,69,229,230,115,5,148,6,101,244,86,233,135,82,22,229,225,129,90,201,65,231,194,128,36,9,153,77,111,153,222,
223,179,90,174,9,130,128,192,90,76,16,51,62,56,164,88,45,101,236,234,67,129,148,31,185,68,189,148,36,8,232,202,140,251,219,43,38,135,15,56,57,125,68,54,155,9,24,176,21,215,125,96,141,23,52,176,83,35,25,
131,140,22,144,234,223,88,75,16,133,196,73,143,56,29,112,242,240,3,78,78,31,147,101,5,121,182,230,236,187,175,208,186,164,92,94,179,156,103,212,29,18,172,67,139,209,150,56,140,177,70,186,220,225,254,17,
79,63,252,49,39,15,14,248,245,63,253,13,211,249,157,55,94,42,140,83,88,223,121,88,211,237,112,21,98,68,234,160,51,132,105,76,191,31,179,156,46,200,55,75,238,175,47,177,113,68,24,90,180,49,12,199,251,180,
69,137,238,90,223,249,122,163,148,118,196,195,1,78,25,242,245,156,245,106,206,232,232,1,251,7,135,20,185,100,97,80,87,59,19,170,112,126,188,73,206,47,213,141,17,67,167,210,226,237,9,195,144,48,136,24,
12,70,28,60,56,229,201,71,63,164,45,43,54,235,37,215,239,222,176,158,93,51,191,57,243,176,69,97,230,40,37,198,214,32,137,229,82,113,1,201,112,159,167,31,127,202,201,225,17,95,253,244,31,88,100,51,113,
149,119,62,19,225,79,255,228,79,63,211,202,200,67,108,141,119,122,74,213,160,181,199,104,107,69,160,12,214,133,88,23,51,28,140,56,124,244,128,178,41,89,175,103,124,247,213,207,185,255,230,107,172,138,
232,31,62,66,37,161,143,75,147,67,43,138,83,194,40,165,151,14,56,56,56,32,25,245,249,151,159,254,29,205,98,133,141,34,31,162,44,7,139,66,201,82,211,47,119,148,250,62,52,66,41,48,129,44,71,47,46,222,115,
125,126,142,139,98,89,46,134,18,64,16,38,49,235,197,130,162,40,80,157,79,16,210,150,36,73,25,239,13,89,76,239,184,124,247,158,103,79,159,178,119,116,194,124,62,23,56,88,93,75,142,174,222,182,98,178,232,
209,106,155,133,137,191,137,13,65,24,18,132,17,105,210,231,193,233,19,90,173,89,173,151,92,158,191,225,187,95,126,78,179,201,24,12,70,36,147,49,109,39,225,208,206,56,194,40,194,5,17,81,152,112,48,57,230,
209,179,143,201,139,140,127,250,171,255,192,48,141,176,105,226,91,100,63,194,233,36,92,90,90,109,196,94,111,12,46,112,162,78,48,154,32,138,112,38,224,230,252,130,187,235,107,170,186,147,217,114,218,39,
29,244,8,131,136,108,45,75,86,213,138,187,184,85,29,218,6,12,250,3,84,83,113,126,246,22,227,44,79,159,255,144,34,207,41,115,169,220,196,184,104,132,188,135,84,62,242,16,251,156,80,63,226,114,206,17,38,
9,105,50,228,241,147,15,233,130,128,217,124,206,236,246,138,235,179,151,100,203,41,218,24,194,164,71,24,70,84,126,198,237,130,80,46,32,27,146,196,3,62,254,228,83,142,79,31,243,254,205,75,190,252,252,31,
9,227,216,47,249,68,190,38,156,25,43,29,146,150,142,64,233,14,103,13,70,203,82,84,90,247,144,65,47,166,204,215,100,197,134,139,243,27,202,162,4,221,145,246,196,17,186,89,175,189,75,178,254,190,18,244,
200,7,23,72,80,200,251,215,111,57,124,120,202,195,167,143,185,191,190,221,161,117,183,32,247,206,179,91,148,115,254,133,82,222,152,230,101,152,86,100,186,147,189,71,252,238,31,252,1,85,221,176,94,76,57,
127,247,134,187,155,43,154,58,195,116,13,155,172,162,213,86,164,133,198,224,76,176,139,126,28,12,246,249,237,63,248,119,60,122,242,148,239,190,252,41,175,190,252,181,16,36,189,11,85,35,207,41,90,162,92,
172,177,98,167,55,198,99,240,253,24,82,107,194,48,34,13,3,242,101,198,98,190,96,189,217,16,164,49,129,11,137,122,61,6,131,62,217,106,225,93,206,91,197,148,2,221,17,69,61,34,231,200,22,51,230,119,119,28,
156,62,97,208,235,81,100,98,200,146,164,38,255,222,122,211,128,177,26,103,172,191,60,252,206,202,10,219,41,12,19,142,31,124,192,225,195,83,154,174,163,88,45,184,187,58,103,57,191,71,147,179,152,46,201,
138,18,140,246,86,90,77,20,69,242,236,219,128,131,227,103,60,254,248,19,38,195,62,223,254,236,39,92,93,191,151,98,73,155,93,182,111,211,116,94,77,102,118,133,155,246,59,32,107,164,88,137,146,152,94,24,
48,191,185,39,47,132,130,171,130,72,10,166,52,165,63,24,82,101,146,145,173,144,223,79,43,141,118,1,105,154,18,59,203,236,118,202,98,57,227,248,201,19,226,64,112,36,157,55,120,106,45,123,41,173,157,31,
71,118,187,207,202,57,187,123,238,162,36,33,77,83,142,30,62,229,225,233,51,148,118,52,121,198,217,203,111,88,23,43,218,124,202,114,182,164,148,23,198,23,93,14,23,70,88,107,177,46,100,114,244,136,199,207,
127,200,254,254,30,223,254,167,159,112,51,191,20,51,90,43,188,37,107,192,252,201,159,253,201,103,74,73,130,207,118,30,100,181,149,219,93,75,85,105,180,194,186,0,23,165,140,251,35,142,30,157,144,213,107,
238,110,47,184,61,123,197,249,175,254,149,98,93,48,122,240,132,248,96,79,44,247,218,96,131,208,39,224,132,140,250,251,236,159,28,81,219,150,159,254,221,95,178,124,247,158,116,111,76,209,117,242,162,25,
189,179,2,27,35,150,246,206,231,88,10,239,220,19,22,181,166,55,28,208,27,12,184,187,186,228,236,213,119,20,69,73,63,73,137,147,148,48,138,177,97,72,190,89,161,104,176,170,195,58,145,130,182,70,51,154,
236,177,202,150,252,226,159,254,133,135,7,135,28,62,251,144,251,217,148,162,216,160,149,194,5,145,72,2,253,65,171,245,118,49,216,17,90,43,163,148,32,38,141,123,156,156,62,165,209,150,197,244,134,106,51,
227,235,207,255,137,252,238,86,230,111,15,78,80,46,196,58,141,177,138,56,238,201,108,46,74,121,240,240,49,147,227,99,174,46,222,241,47,255,241,255,38,116,10,215,139,41,139,141,44,151,148,232,149,141,86,
56,171,137,226,20,27,136,123,86,107,176,90,145,134,17,202,88,170,174,35,29,244,136,195,136,229,244,134,233,245,37,235,205,90,70,49,202,208,104,77,18,39,208,213,104,90,140,97,151,15,219,2,113,47,33,12,
2,126,254,211,159,99,128,167,31,125,196,114,185,164,170,74,217,109,104,237,127,121,135,177,118,55,246,50,74,99,181,84,162,65,20,211,239,141,120,244,228,67,8,28,183,55,151,220,95,158,113,115,249,142,251,
243,215,24,3,97,210,195,4,241,14,135,43,217,184,1,214,132,28,238,159,240,252,211,31,99,131,128,151,95,254,130,95,127,254,19,226,254,80,124,87,158,18,168,181,194,57,139,66,19,24,71,152,246,232,140,198,
208,201,72,65,137,76,212,6,1,86,27,48,50,66,108,170,138,213,242,142,249,116,70,135,198,120,191,70,63,29,248,96,17,191,244,178,130,206,208,128,141,99,210,180,199,122,181,224,203,95,252,146,254,254,17,199,
255,63,83,239,217,99,217,149,94,105,62,219,28,127,189,137,184,225,35,210,211,85,73,165,146,212,13,12,6,232,110,149,128,254,87,245,95,6,3,12,48,51,24,76,55,166,91,221,173,146,212,85,164,170,68,22,89,36,
211,103,100,120,115,111,92,239,253,57,103,62,236,29,65,125,224,23,154,100,102,220,115,207,126,247,122,215,122,214,102,141,217,124,74,28,175,209,210,48,241,145,166,149,40,177,73,96,211,116,148,224,104,
15,215,113,80,174,199,198,230,1,63,255,171,191,38,78,99,6,253,46,173,250,37,245,155,11,102,227,30,233,98,70,26,43,86,66,163,28,179,112,245,252,200,14,42,14,123,135,79,248,236,47,254,130,76,206,231,236,
195,75,206,223,191,178,36,210,212,14,36,182,28,68,154,23,171,171,29,148,163,12,167,41,77,80,202,96,13,238,59,142,165,148,4,97,64,46,19,48,26,14,24,12,122,244,123,125,124,223,67,11,65,172,29,60,55,32,94,
76,31,96,107,74,27,141,28,82,220,192,224,142,167,189,46,31,222,125,96,239,147,79,240,180,98,49,157,65,28,255,84,187,167,148,121,94,237,161,37,148,68,59,38,201,237,249,25,194,40,195,230,246,1,219,123,71,
44,87,75,134,189,54,231,231,39,12,7,93,68,60,98,216,235,35,148,75,156,164,40,139,37,113,93,15,215,245,201,228,202,60,122,254,57,7,143,159,160,181,226,195,215,255,192,205,245,37,74,41,86,233,189,29,81,
220,19,22,16,66,35,93,207,154,200,141,116,120,127,83,190,55,26,120,81,72,169,92,96,218,157,48,159,142,233,118,218,160,77,248,75,123,25,92,207,35,93,175,237,46,2,92,215,177,41,231,53,81,33,67,177,80,224,
238,226,134,70,179,193,238,163,39,56,82,155,14,105,204,32,109,112,9,230,37,143,0,237,152,189,139,84,194,34,164,179,100,178,5,54,119,30,179,123,244,140,213,114,197,124,58,225,252,221,75,134,195,30,34,30,
209,109,181,136,133,36,70,161,29,147,7,241,252,16,199,113,9,163,136,253,231,159,179,127,244,20,185,90,242,253,63,254,29,173,238,45,142,175,33,53,137,100,165,140,65,66,253,187,127,255,239,126,45,82,179,
25,22,214,21,162,44,149,78,88,8,149,227,26,215,69,20,100,40,110,110,176,78,86,76,250,109,134,221,38,167,63,126,199,172,63,194,207,230,41,237,108,145,42,179,108,50,14,158,8,199,245,41,102,43,148,118,54,
153,44,198,188,249,230,75,6,167,231,228,55,107,196,54,130,175,76,48,26,45,149,145,49,28,215,252,230,164,225,201,220,247,114,166,196,246,180,6,47,8,240,195,128,113,191,67,183,213,68,88,55,143,231,251,198,
142,42,21,139,249,220,224,26,148,50,112,36,251,69,201,100,34,198,243,37,231,239,63,178,93,219,68,135,62,147,161,177,167,73,165,173,188,229,60,92,107,165,48,255,157,86,14,142,23,226,123,17,91,187,251,224,
56,12,122,109,198,195,14,39,199,239,105,93,94,32,132,166,186,187,131,19,4,150,211,111,192,79,202,247,200,101,138,236,30,28,146,186,30,173,70,157,31,190,252,239,136,120,73,177,182,69,108,108,213,86,159,
244,30,22,77,158,239,225,7,190,185,121,217,90,63,105,167,3,215,247,140,228,161,20,153,92,22,165,20,227,65,143,241,168,203,116,54,37,151,47,33,29,31,164,66,203,148,36,94,62,200,83,218,126,206,41,2,55,8,
240,131,128,198,213,37,171,197,138,173,131,61,198,163,193,131,12,117,47,121,152,162,229,216,122,159,45,51,201,245,240,195,44,59,123,71,56,126,200,116,58,100,216,185,227,230,242,148,238,221,37,171,229,
10,63,136,112,195,200,222,28,83,220,32,68,43,141,231,133,236,108,31,177,253,232,17,147,217,140,179,227,55,156,188,254,14,215,13,16,142,103,192,124,73,98,116,105,97,14,31,199,245,240,195,16,237,186,6,35,
189,90,226,10,131,100,144,54,189,44,93,247,1,187,172,149,98,57,155,176,152,205,152,142,135,172,82,65,38,155,53,193,65,207,37,89,174,236,36,6,142,118,108,146,215,28,248,126,152,37,142,215,92,158,124,100,
251,209,17,73,28,51,159,142,16,118,169,158,36,246,139,236,184,56,158,67,156,172,12,42,193,117,81,142,71,177,180,197,159,255,242,175,137,211,132,65,191,195,168,123,71,175,213,98,208,110,154,223,183,31,
48,95,27,196,173,82,218,112,114,226,20,207,245,121,241,179,63,231,241,243,39,196,203,57,47,191,251,154,110,253,130,197,100,194,108,25,219,125,155,45,14,113,12,99,197,113,93,164,54,144,50,108,64,237,94,
26,21,247,177,44,101,224,130,174,239,145,139,251,83,10,141,0,0,32,0,73,68,65,84,34,230,227,9,221,126,159,241,120,64,146,74,42,149,10,82,184,102,56,138,19,226,212,52,54,9,105,62,3,37,204,13,196,143,178,
196,139,57,173,122,139,141,253,3,226,217,216,118,13,216,229,163,252,169,148,93,200,127,149,59,112,60,28,47,100,115,251,9,213,157,125,86,171,5,253,86,131,179,247,111,233,119,26,8,49,99,53,91,224,249,33,
171,216,186,74,44,158,196,241,124,114,133,77,30,61,255,148,114,165,200,100,56,164,115,125,202,245,217,91,3,111,140,77,71,180,186,55,27,72,101,6,10,199,51,117,146,54,184,39,149,50,123,56,92,179,99,176,
210,129,31,26,151,219,108,60,100,52,154,176,156,47,205,119,35,10,240,195,28,90,10,210,100,245,224,243,79,86,247,150,79,141,235,185,100,11,89,150,163,9,131,225,152,210,230,6,98,109,170,7,173,97,138,52,
53,214,116,173,36,142,118,145,74,160,181,67,24,68,248,126,150,234,246,1,59,7,143,16,105,194,114,50,226,252,253,43,218,237,6,82,46,233,212,235,72,71,19,11,112,29,7,215,245,13,174,58,8,41,148,170,236,61,
251,148,82,174,76,154,172,185,125,247,35,215,87,31,209,129,71,146,24,87,155,177,62,123,104,173,80,255,225,111,254,230,215,198,255,25,155,7,194,22,41,219,218,101,28,237,16,101,114,68,97,158,74,173,198,
44,158,210,109,223,210,239,52,57,127,249,35,163,86,27,199,207,176,253,248,49,210,117,140,116,225,6,248,161,135,231,4,108,108,236,144,169,149,184,184,185,224,253,191,252,142,206,135,247,228,171,27,56,185,
44,137,213,204,239,235,220,92,199,197,9,12,2,32,112,60,82,145,26,44,114,154,216,110,84,137,16,137,117,7,196,230,15,157,201,48,155,140,104,215,235,44,22,115,246,118,15,208,174,199,114,117,207,2,138,89,
39,43,251,240,11,72,99,148,80,68,249,136,92,57,207,241,235,215,100,194,0,100,202,122,185,124,88,64,73,97,180,192,36,190,39,88,90,141,55,202,83,219,222,1,215,101,52,232,48,159,143,57,126,251,138,235,183,
102,250,170,109,239,16,150,203,72,41,240,92,159,32,19,225,56,30,249,108,145,173,189,125,198,235,53,199,239,222,242,250,203,127,194,33,33,83,221,100,109,98,171,32,36,113,26,179,90,174,16,210,72,55,90,251,
134,216,185,52,110,34,71,25,223,121,138,52,165,197,113,140,86,160,29,151,32,27,17,250,62,131,78,135,233,160,199,120,50,101,123,239,16,233,250,104,237,146,198,75,195,244,38,126,144,103,76,198,23,194,40,
32,155,47,208,105,181,108,16,202,64,185,132,109,36,50,220,242,196,120,225,165,64,105,15,47,200,224,122,17,135,143,94,32,92,159,209,160,199,124,50,164,117,215,224,230,244,61,203,249,148,76,152,33,83,42,
227,104,109,218,147,28,15,207,51,160,176,199,79,62,33,91,169,210,106,182,120,245,167,175,105,158,125,32,8,28,148,246,204,203,194,110,210,181,149,217,28,207,35,112,125,132,246,140,86,139,128,149,105,148,
50,18,134,49,25,104,173,205,77,41,93,35,181,198,115,50,176,90,211,239,118,185,185,189,101,149,10,118,15,246,89,35,209,10,88,155,102,162,117,178,36,78,82,67,149,180,157,162,81,38,36,10,28,186,77,99,169,
35,54,105,221,56,21,164,210,184,207,164,150,182,105,47,125,224,10,149,54,182,248,179,95,254,91,82,41,24,116,155,220,221,94,113,119,125,65,171,113,195,106,185,32,10,51,166,225,76,59,184,142,99,44,200,72,
178,153,18,63,251,171,191,166,178,89,162,63,232,242,234,187,111,144,203,33,171,217,152,225,100,5,210,56,188,144,102,53,171,29,7,87,185,40,109,184,60,247,54,217,52,77,30,178,18,169,5,184,165,73,242,16,
30,12,66,179,180,156,79,103,180,59,93,6,253,62,65,38,79,121,107,131,84,105,28,41,76,126,32,49,156,29,137,52,75,115,140,205,48,151,207,35,147,53,189,246,16,47,23,26,57,84,96,13,13,218,122,194,37,142,163,
112,149,113,231,57,94,64,121,243,144,157,71,79,89,44,151,244,91,13,174,79,63,208,105,220,176,156,245,89,205,231,100,114,37,226,52,69,216,91,190,103,111,198,229,218,30,207,63,251,140,76,232,211,106,52,
184,185,60,102,218,190,102,126,159,134,22,194,12,63,169,64,104,51,12,184,174,139,235,186,104,109,62,167,120,181,50,59,48,11,133,76,164,121,97,223,151,172,4,89,143,108,33,207,180,55,97,52,25,51,159,79,
77,22,168,144,71,106,23,165,28,20,214,208,98,169,168,88,37,192,245,28,114,133,28,201,98,198,100,60,39,200,4,36,43,35,235,184,158,135,74,239,205,43,230,121,113,29,67,23,245,130,12,249,205,29,246,14,30,
19,199,176,156,142,56,123,255,154,250,237,5,105,50,101,220,105,227,70,1,40,135,40,202,17,101,178,132,97,22,47,8,40,110,108,243,248,197,23,248,158,199,164,215,227,221,183,127,224,228,221,15,68,133,28,201,
250,190,55,76,24,187,114,98,134,52,245,55,127,251,31,127,173,72,13,28,13,105,29,15,38,104,21,120,1,94,16,17,6,89,10,229,42,171,116,78,253,250,194,44,226,222,191,161,127,119,135,16,14,181,195,67,130,92,
100,174,140,65,128,19,248,184,110,192,102,109,15,29,120,52,218,117,62,126,255,53,211,171,115,194,176,64,118,103,139,84,41,187,108,210,198,139,174,29,92,223,183,83,130,38,19,70,196,241,138,249,98,102,175,
69,86,86,80,218,56,15,44,109,211,241,60,138,149,50,131,254,128,246,221,29,18,65,174,90,69,42,77,152,137,88,44,151,196,235,185,77,239,26,40,150,153,24,205,13,198,139,124,38,195,225,3,219,198,0,188,204,
52,115,31,184,209,18,92,55,196,245,178,212,118,246,73,148,160,223,109,51,234,181,185,60,57,225,234,237,107,214,171,37,27,219,187,148,182,54,205,228,235,56,248,81,136,227,248,38,129,188,189,203,112,60,
225,238,230,134,243,239,191,69,173,151,84,119,183,209,153,200,2,211,20,74,154,150,27,199,245,112,125,15,215,245,8,252,12,165,98,25,229,40,102,243,177,157,241,205,23,222,36,157,19,251,105,153,67,33,8,67,
114,185,44,227,209,152,155,250,53,157,102,151,170,229,198,71,81,134,133,197,40,220,115,55,30,130,173,214,241,18,100,67,214,203,153,173,151,91,155,47,58,137,45,22,73,31,252,212,158,23,226,123,33,123,251,
135,120,97,196,112,208,167,217,108,208,111,53,57,251,240,134,241,160,131,235,121,20,43,155,184,174,143,64,225,250,70,111,204,102,10,28,60,126,65,34,37,253,110,143,219,139,143,244,238,206,8,60,15,225,56,
160,148,77,145,152,51,250,222,130,39,180,121,217,229,242,21,170,27,53,146,100,197,116,60,182,14,17,5,105,108,37,39,97,125,206,9,42,21,72,37,9,51,33,164,208,106,181,184,107,220,160,189,136,48,147,167,80,
44,27,220,119,252,83,153,137,120,56,224,204,111,195,117,124,115,235,18,9,74,171,7,22,187,1,22,67,26,175,136,147,53,74,42,195,92,47,108,240,103,191,252,107,98,82,154,141,43,110,46,206,232,54,110,232,181,
154,204,103,19,194,48,66,184,174,89,200,107,7,161,52,73,42,201,102,43,252,229,255,242,191,226,5,62,195,225,128,219,203,19,102,227,46,46,9,253,225,220,74,57,202,166,76,133,189,37,121,104,109,14,139,32,
42,178,189,187,207,114,49,101,181,88,242,175,188,188,118,134,147,182,107,192,124,240,202,209,228,242,57,88,173,25,244,6,180,91,29,214,36,68,133,34,249,66,129,116,62,55,128,66,76,226,87,72,147,6,87,246,
112,213,190,135,235,152,176,151,32,177,63,51,187,184,181,63,119,33,82,208,30,174,23,81,220,56,228,224,233,11,22,179,49,189,86,157,243,227,215,244,154,87,140,134,29,226,36,166,80,44,19,167,70,130,242,61,
31,215,55,193,189,218,206,99,182,119,119,73,82,24,116,251,212,175,78,241,221,132,201,176,207,104,50,51,7,154,85,4,192,100,8,238,119,101,142,27,144,201,149,201,132,1,227,81,223,104,50,113,74,42,18,59,245,
75,219,185,141,233,31,112,28,138,197,34,241,124,193,100,56,162,223,110,179,78,193,141,114,68,217,60,46,38,192,104,138,106,238,97,138,70,122,92,167,2,47,12,140,34,96,157,99,6,99,109,185,7,82,27,199,149,
84,120,158,139,118,2,42,181,67,14,30,63,37,142,13,163,255,228,229,247,52,234,87,196,203,33,211,225,8,199,15,81,246,224,242,253,144,48,202,224,123,33,155,251,135,236,238,63,66,8,197,98,58,230,230,227,123,
174,207,222,227,70,193,67,58,251,30,162,38,164,113,5,106,71,161,126,245,239,255,246,215,72,51,205,167,63,161,230,80,66,19,70,121,124,63,36,87,44,19,171,132,126,175,65,187,113,205,221,213,41,163,250,13,
73,170,217,59,120,70,102,163,140,188,47,142,136,34,148,242,216,172,237,162,66,151,65,191,203,229,217,123,6,39,111,241,157,128,226,222,33,194,243,108,81,179,89,60,104,199,181,19,142,192,211,1,91,181,109,
150,233,154,233,120,0,113,130,231,250,40,71,25,107,92,106,210,142,22,50,99,166,58,37,200,23,202,76,23,83,78,222,189,99,54,158,80,44,86,41,149,202,224,104,22,243,153,45,141,184,127,244,83,171,81,26,191,
174,116,149,177,77,41,109,61,218,201,67,129,137,18,224,123,17,142,27,176,187,181,135,159,207,211,233,119,184,187,190,226,250,252,132,171,55,175,88,76,39,148,171,53,118,30,63,70,185,198,177,226,7,17,202,
245,168,148,170,228,42,27,116,122,93,250,253,54,167,175,126,96,49,236,16,101,50,100,42,21,227,253,79,237,149,89,74,130,192,84,47,58,218,35,151,45,178,179,191,79,183,219,161,223,237,62,188,152,227,7,222,
199,218,104,148,105,108,203,78,204,237,204,9,3,99,97,237,143,184,187,185,100,220,31,82,219,222,102,107,103,159,245,122,101,88,255,171,165,185,41,89,98,169,68,146,88,77,56,181,47,6,101,167,180,244,222,
247,110,23,216,190,31,226,250,17,59,187,71,100,242,37,6,227,1,157,230,45,227,65,159,139,143,239,233,52,111,240,188,128,202,230,6,110,224,147,201,100,145,218,36,103,163,76,158,71,47,62,37,150,138,102,171,
77,243,246,140,230,213,71,146,120,133,35,29,164,231,147,88,204,132,9,169,105,227,94,210,14,142,114,41,149,55,57,122,246,132,203,139,19,90,141,91,139,76,176,9,101,187,72,189,239,54,21,216,190,92,165,144,
42,37,200,100,80,34,97,49,158,210,168,95,147,10,201,243,79,127,134,239,251,76,38,19,214,171,165,145,63,238,221,47,169,36,85,32,133,9,161,9,37,30,146,186,166,194,211,192,205,164,84,144,154,219,75,174,184,
201,207,127,241,151,164,74,49,28,116,57,123,255,154,97,183,77,175,85,103,54,153,16,6,33,94,54,52,186,182,212,164,194,224,41,54,106,7,252,249,191,253,183,36,241,154,94,175,205,237,229,57,253,230,29,161,
151,210,233,244,89,174,126,138,208,59,22,119,162,93,31,169,52,174,31,81,170,236,242,232,197,11,174,207,63,208,239,247,12,189,86,60,188,239,237,97,118,31,157,76,31,44,125,158,231,81,40,101,241,28,77,167,
211,162,223,105,226,135,25,246,143,158,225,43,193,114,54,49,9,240,212,48,142,148,114,144,218,49,233,95,165,108,98,220,220,2,148,252,201,194,125,127,219,50,139,197,12,249,210,22,187,79,158,130,72,233,222,
53,56,63,126,75,167,85,103,220,111,178,92,45,41,87,55,140,77,87,107,180,99,222,9,110,16,81,219,123,204,193,225,35,86,243,41,221,118,139,250,205,57,81,160,232,223,213,233,13,71,44,31,56,87,198,133,226,
135,25,130,40,99,25,78,25,74,27,187,100,163,144,250,197,169,253,172,172,149,216,34,89,239,217,57,74,73,195,251,73,83,92,223,33,87,200,194,122,69,171,213,162,223,105,128,80,148,119,119,200,5,30,235,249,
194,182,157,253,132,19,73,48,67,155,41,97,178,232,139,212,240,139,176,7,181,148,158,73,193,58,62,218,117,201,149,119,56,122,250,9,42,73,24,245,187,92,28,191,231,174,126,205,124,218,103,212,239,163,131,
44,110,16,154,91,170,31,226,7,230,175,234,206,33,187,7,143,137,231,107,186,221,54,55,231,199,212,47,143,73,132,65,103,172,238,203,35,164,52,3,181,235,225,58,30,218,113,80,191,250,155,95,253,90,105,253,
240,101,73,109,136,38,10,115,248,153,60,97,54,139,112,5,173,230,53,55,151,231,52,206,78,24,93,223,176,94,173,57,58,122,206,230,147,199,196,164,104,229,26,222,186,151,161,182,179,199,34,141,105,54,26,92,
159,127,160,253,241,29,241,116,65,121,231,16,39,159,183,11,39,97,125,215,190,185,210,106,159,92,198,188,224,122,163,14,215,239,222,26,105,69,10,164,118,108,253,219,210,188,236,239,193,109,24,23,137,16,
41,218,113,40,151,202,136,52,225,226,228,20,25,167,28,61,123,66,105,163,198,112,60,37,94,46,204,151,213,228,239,236,214,94,155,147,216,70,154,149,212,172,211,229,3,25,83,164,169,33,95,250,17,27,27,219,
148,54,171,52,218,119,52,206,207,185,187,189,224,230,228,61,243,201,136,242,230,38,59,143,31,33,61,15,173,60,130,40,50,141,67,133,10,65,174,192,77,227,142,105,183,197,233,219,151,140,235,87,4,81,72,113,
107,155,69,106,110,28,90,73,92,223,197,15,50,56,158,97,163,151,203,27,108,238,236,240,238,253,27,26,103,39,120,81,96,190,112,34,181,55,21,249,176,204,52,252,24,243,224,174,214,214,117,162,93,54,55,170,
32,52,55,87,231,248,18,30,63,255,132,32,155,103,49,157,177,92,204,13,241,211,238,105,64,34,149,99,112,6,54,104,151,38,6,27,129,176,64,51,36,174,235,224,7,33,155,181,61,178,229,77,198,227,49,55,151,167,
180,154,117,94,191,252,142,94,243,142,108,144,161,186,181,131,31,4,102,137,234,104,164,114,41,22,43,236,61,126,65,187,63,160,223,106,211,184,58,161,121,123,130,86,41,139,89,130,190,119,97,96,100,28,207,
49,183,29,41,53,190,159,97,255,209,115,118,142,246,121,249,221,239,185,189,60,55,73,210,212,248,222,99,187,132,118,164,185,158,199,233,79,232,81,129,120,208,201,115,185,60,217,124,150,97,175,69,167,213,
164,80,44,113,244,244,57,179,233,140,245,98,110,14,143,85,108,115,19,216,73,222,88,62,227,196,52,152,25,222,147,157,8,69,138,148,46,218,243,137,162,60,159,254,236,23,120,129,71,183,213,228,250,236,3,157,
230,53,205,250,21,163,201,136,108,54,139,151,201,152,150,94,101,16,222,66,186,28,28,61,231,243,63,251,115,250,131,33,237,198,37,245,203,19,6,189,14,66,172,88,205,23,76,166,235,7,196,134,214,198,219,173,
29,99,172,8,162,18,135,143,62,227,232,233,99,126,248,250,119,52,235,55,8,17,147,196,43,210,196,52,171,137,212,150,8,166,137,77,228,218,116,178,146,15,33,192,76,46,131,239,104,102,195,41,195,126,159,124,
165,204,222,227,199,204,71,35,86,235,197,67,54,35,177,191,142,76,165,73,245,166,166,233,203,56,115,76,213,169,176,184,59,169,28,60,47,34,44,108,112,240,226,51,100,10,131,110,155,203,143,111,24,15,187,
140,122,13,86,203,25,149,141,93,3,88,76,36,174,31,152,44,71,148,99,239,240,83,182,118,15,24,246,187,220,221,94,115,117,118,140,235,73,214,179,33,253,222,128,185,101,48,41,109,92,51,65,152,49,60,158,48,
36,147,43,83,221,57,192,211,41,47,191,254,29,113,106,170,3,77,201,144,37,81,74,7,101,177,37,41,70,246,129,212,120,229,165,34,202,101,209,66,177,156,47,25,245,219,228,10,5,182,119,247,17,113,66,188,50,
183,58,251,166,48,182,97,101,177,225,118,39,153,218,97,202,200,201,10,165,77,120,46,140,178,100,10,155,28,188,248,20,207,113,88,206,103,188,253,246,27,234,183,23,204,167,61,198,195,1,65,54,143,31,184,
164,34,197,143,178,120,158,71,46,87,100,247,209,39,108,109,237,178,152,45,104,55,110,56,121,243,35,131,246,13,171,229,228,1,183,158,162,30,66,88,247,178,152,23,68,100,202,91,168,255,240,171,95,253,90,
218,2,97,210,4,145,128,231,251,120,94,68,174,80,197,205,5,116,251,77,234,151,231,220,93,157,211,189,186,96,181,76,168,108,108,176,121,116,128,242,124,16,154,192,15,9,130,12,229,205,109,38,201,130,110,
171,65,235,238,150,250,187,31,80,211,9,185,226,38,225,102,213,48,64,204,211,134,239,7,120,190,139,86,46,229,114,141,210,118,141,203,171,15,188,252,234,159,45,12,108,253,128,12,53,100,202,123,127,175,41,
57,70,216,147,204,250,180,19,4,185,82,1,215,117,104,222,214,145,164,28,61,121,130,118,3,230,211,9,171,165,105,204,146,246,69,105,243,85,214,235,110,37,4,91,65,39,237,77,192,15,178,20,10,101,170,91,59,
140,103,19,206,236,4,91,63,121,207,108,48,36,95,40,179,255,252,25,218,122,232,61,63,196,243,124,138,197,42,110,24,113,215,104,49,238,118,232,52,46,233,94,158,19,56,46,27,7,7,56,65,4,169,57,168,92,207,
51,9,85,55,32,8,51,84,54,182,201,149,43,156,124,120,203,217,143,63,144,47,101,45,39,59,37,73,205,159,83,8,129,144,247,45,246,154,216,244,214,89,0,147,213,34,164,32,87,44,147,164,80,191,186,96,50,24,113,
240,244,41,218,117,153,142,135,166,111,54,77,144,182,176,195,80,63,99,187,198,185,71,29,155,159,179,76,204,164,236,5,25,10,197,77,182,119,15,153,45,230,116,155,13,198,195,30,111,222,189,162,117,125,69,
62,200,114,240,248,8,63,27,153,110,209,192,148,122,228,114,37,182,143,30,211,233,143,233,118,154,12,155,183,220,93,156,225,105,240,60,159,32,140,208,158,135,107,61,238,190,231,155,137,68,106,114,133,10,
143,158,125,74,182,152,227,248,237,15,92,188,121,141,227,27,98,166,76,133,189,233,217,146,107,107,109,140,109,194,51,149,210,162,124,109,10,53,149,184,161,249,255,205,198,99,206,143,63,146,43,22,57,122,
242,140,94,183,109,234,17,147,165,53,198,222,247,233,222,35,190,204,242,45,73,226,7,160,154,20,18,229,5,104,29,242,252,179,95,176,177,189,193,176,223,225,236,253,123,6,221,54,221,187,27,166,211,33,185,
40,71,16,230,204,238,69,59,22,250,230,82,219,121,196,243,207,191,96,56,26,210,237,220,209,171,95,49,232,52,113,93,69,186,94,50,95,152,210,109,237,106,163,143,107,109,236,167,66,146,43,108,242,201,23,191,
160,90,171,240,242,219,175,168,95,158,216,129,40,121,224,231,155,105,222,46,82,45,117,243,97,160,177,127,63,177,143,190,31,4,228,115,17,163,110,139,219,155,27,138,181,61,42,149,10,243,209,152,36,93,241,
208,153,151,166,198,247,47,82,115,96,252,43,174,148,176,157,5,8,80,78,72,144,41,178,247,232,5,174,235,50,30,116,185,60,125,71,227,250,156,97,167,193,116,50,161,80,222,32,12,3,83,52,228,186,248,65,136,
231,103,169,29,60,165,84,217,96,50,27,115,123,118,74,253,234,146,85,50,35,112,214,12,187,125,230,75,83,176,174,93,23,199,117,200,132,25,162,76,14,207,15,41,213,246,168,212,118,73,87,19,126,248,242,31,
89,97,248,85,113,106,142,240,251,29,193,125,57,205,125,195,154,176,237,115,41,177,189,41,66,182,92,160,144,207,209,175,183,184,107,221,81,216,220,166,88,42,27,9,48,94,218,197,125,108,7,79,73,26,39,6,255,
145,154,215,190,177,241,138,7,108,120,16,101,8,179,57,118,30,61,165,144,203,178,154,77,249,240,242,59,110,110,174,88,46,71,140,250,93,130,76,134,40,202,128,48,133,55,97,152,37,10,179,28,60,255,25,213,
106,141,249,116,198,221,205,5,167,31,222,48,28,182,89,207,39,8,199,220,22,133,148,56,74,225,122,62,129,111,236,227,65,16,225,250,17,149,157,3,212,223,254,234,111,127,109,170,6,99,203,11,145,120,110,72,
46,87,194,47,100,24,141,90,92,157,125,228,246,244,3,221,203,19,146,88,82,219,222,167,118,116,128,112,3,226,36,53,218,146,23,81,217,217,97,48,155,210,235,52,233,119,238,168,191,127,77,50,28,225,70,89,42,
143,142,16,142,178,147,189,135,239,6,104,199,195,247,34,182,183,247,241,114,17,103,167,175,120,249,229,63,81,42,109,32,61,101,49,185,234,1,42,100,74,10,124,164,165,77,90,182,166,169,151,75,214,246,75,
154,146,201,101,137,138,5,94,255,248,154,222,245,45,207,127,254,51,214,66,153,226,145,245,130,84,88,182,134,48,147,164,118,28,219,75,250,211,4,167,165,64,185,33,249,92,149,237,189,61,150,233,146,147,227,
119,92,124,124,71,227,195,123,230,163,1,185,82,153,163,79,94,224,5,1,142,212,120,97,136,231,71,228,75,21,82,223,231,174,209,96,62,29,209,111,221,114,247,225,13,90,192,214,209,1,78,38,34,198,88,46,179,
81,134,32,147,197,243,2,194,168,64,109,219,116,202,126,120,249,29,55,111,191,167,186,83,35,81,218,178,173,237,14,66,43,203,137,113,81,82,145,198,9,113,178,54,19,155,180,80,51,91,166,32,36,20,202,101,170,
181,77,78,63,30,211,188,188,230,209,139,79,136,147,132,249,108,242,208,253,106,246,163,102,73,157,218,52,34,226,167,184,126,98,187,3,114,249,10,135,79,158,179,140,19,198,195,62,205,187,6,191,255,242,31,
24,54,235,84,242,89,118,14,15,8,115,6,171,235,7,1,158,159,37,147,41,178,181,119,68,189,209,166,219,109,48,110,213,233,222,92,176,156,15,205,244,17,102,209,142,194,209,10,100,76,224,27,23,143,114,124,170,
27,251,28,126,242,25,210,117,120,251,253,191,112,241,225,13,217,124,193,44,31,237,52,185,254,73,170,182,33,49,243,197,139,99,3,176,138,17,136,36,54,47,192,52,69,136,24,207,51,102,132,213,106,201,213,241,
71,194,92,142,221,131,125,70,131,62,171,197,130,52,182,173,111,194,88,79,239,119,3,105,138,221,101,200,135,155,139,116,66,14,31,63,231,240,201,1,227,65,159,215,63,252,145,155,235,11,198,195,54,233,122,
78,54,140,112,253,44,107,169,112,92,223,18,76,53,71,143,63,227,241,103,159,51,24,13,24,52,235,180,235,231,12,154,183,8,153,146,164,43,38,211,57,72,109,164,71,192,117,92,19,236,82,30,143,159,254,140,79,
62,255,156,32,10,57,123,247,29,183,103,199,44,227,181,169,189,74,133,173,3,212,144,38,104,41,45,179,229,167,23,207,125,248,72,106,11,121,83,134,76,234,6,46,158,235,50,30,78,185,58,59,99,115,111,159,124,
38,195,120,50,36,73,86,246,101,102,53,125,33,172,251,196,26,8,108,192,16,97,58,139,131,48,207,225,167,63,167,92,169,176,24,245,121,255,234,79,220,213,175,24,118,174,153,77,166,108,108,31,18,68,33,73,106,
80,12,126,24,225,7,57,246,158,124,65,185,186,65,167,211,227,246,242,156,250,213,9,179,73,159,108,36,153,15,167,204,86,160,92,77,54,19,144,47,148,200,229,74,228,11,5,10,165,42,219,251,79,40,148,170,136,
120,201,15,191,253,175,204,214,115,148,235,218,227,250,190,230,195,30,128,202,193,209,118,163,121,239,129,123,0,223,153,183,139,227,40,194,92,72,33,159,99,220,53,253,205,197,237,109,10,249,60,235,249,
140,249,124,110,2,127,66,60,220,134,239,177,242,247,65,171,212,150,19,121,81,142,108,105,147,173,253,39,132,190,207,122,57,231,228,205,15,92,158,31,51,29,181,24,117,239,136,114,121,194,76,198,228,73,92,
159,32,202,146,41,86,120,252,249,95,80,41,111,48,25,13,185,57,59,225,195,219,151,76,70,61,210,213,196,88,96,181,38,240,93,114,153,44,217,124,150,76,38,34,204,132,20,202,53,54,119,159,80,40,110,18,105,
129,250,155,255,240,171,95,39,137,97,111,155,135,202,39,151,171,144,45,22,152,45,71,92,158,30,115,245,225,13,131,171,43,136,37,219,123,135,84,247,119,144,190,103,253,177,1,153,40,207,198,214,46,253,229,
152,241,160,203,120,208,161,126,246,158,101,251,14,199,203,82,222,59,196,205,152,40,180,82,202,208,27,181,67,33,87,166,82,219,38,214,130,139,227,215,188,255,253,151,100,163,60,153,114,233,193,147,111,
61,77,38,172,160,61,131,106,78,98,226,181,57,93,133,117,34,36,182,128,196,104,244,49,142,227,81,172,84,25,13,134,116,174,174,216,61,60,96,177,94,49,157,76,88,91,126,127,154,164,172,211,149,185,53,36,247,
15,108,106,175,206,30,126,96,74,41,18,153,114,252,241,29,231,199,239,104,28,127,96,49,153,82,40,111,112,248,252,185,145,33,28,109,117,195,144,124,161,140,155,201,210,109,183,89,204,38,140,186,13,90,23,
167,196,171,5,229,218,22,217,106,217,20,101,32,201,100,66,180,31,224,186,158,249,153,151,42,140,39,51,206,63,252,200,205,251,63,17,101,35,116,104,150,141,169,52,211,172,18,166,97,74,107,7,165,93,19,162,
79,99,51,209,25,234,154,73,127,218,47,183,41,52,78,112,92,143,114,181,194,100,56,230,250,244,140,163,103,79,152,12,122,172,151,134,172,105,159,86,148,163,30,150,215,38,197,105,113,191,142,75,20,229,56,
124,252,140,84,72,70,195,33,167,239,95,243,227,183,95,51,234,220,145,207,68,108,237,239,226,5,17,66,24,204,130,210,14,133,194,38,213,205,109,58,195,33,211,113,143,97,231,142,65,243,154,229,180,15,218,
104,250,142,231,88,144,156,113,59,8,225,160,221,128,157,131,167,228,55,170,116,251,125,222,255,240,29,119,23,199,104,173,113,124,215,176,151,44,99,40,77,65,89,208,216,61,14,66,57,134,117,110,186,22,76,
44,53,73,77,127,170,64,32,181,241,37,103,243,5,162,32,228,252,195,7,50,249,34,218,117,152,207,205,207,36,185,191,57,152,35,208,182,122,45,72,82,235,248,66,162,221,128,234,246,33,79,158,61,99,57,155,240,
225,205,143,92,157,127,96,58,236,179,94,172,8,3,31,233,121,102,25,169,29,99,17,84,46,187,123,143,121,252,233,11,250,253,62,131,78,131,102,227,130,89,183,201,114,185,66,74,35,43,45,214,54,251,32,37,158,
23,32,132,194,243,179,124,246,103,191,100,103,127,151,249,124,206,251,87,223,51,234,214,153,79,39,44,150,177,193,159,139,251,61,156,109,37,211,218,186,207,204,243,144,216,103,196,224,41,120,184,33,25,
218,38,184,110,64,177,82,194,117,92,110,206,47,40,215,54,73,108,109,161,169,38,21,22,247,33,193,78,180,82,152,194,120,132,9,110,6,81,137,141,221,199,148,43,85,214,235,37,103,239,127,228,236,228,152,241,
224,142,249,104,68,165,186,75,152,203,152,48,163,227,227,5,230,80,60,120,250,57,249,82,137,126,183,75,167,221,96,57,25,50,238,53,113,28,65,188,90,34,132,66,187,14,249,92,142,92,46,75,38,202,225,249,46,
81,190,76,109,247,49,174,163,25,15,58,156,190,250,35,253,94,7,237,186,230,103,96,43,91,165,146,72,105,36,100,67,217,52,238,165,56,193,118,18,155,96,157,4,214,169,1,43,18,27,121,170,88,41,33,215,9,205,
155,91,114,213,10,146,148,197,124,110,6,77,105,29,16,169,33,3,8,91,74,67,98,88,245,218,245,201,85,107,212,118,142,240,61,159,233,100,204,205,217,9,151,31,223,51,159,246,233,183,218,68,133,18,217,92,100,
255,140,62,97,148,33,12,35,30,127,241,151,148,75,85,150,211,9,183,39,199,156,28,191,99,60,106,35,89,24,217,44,200,16,101,124,50,217,28,65,20,25,244,141,31,144,43,239,80,174,29,144,201,228,73,22,83,94,
255,238,55,104,33,37,233,210,188,44,29,237,16,248,89,178,165,18,203,116,198,245,197,9,23,239,223,210,190,184,66,227,176,177,189,195,230,225,1,177,140,145,66,163,253,0,223,207,80,217,218,97,28,207,25,181,
90,76,38,67,110,47,62,48,186,189,65,199,146,202,81,141,76,54,99,139,8,52,202,51,176,176,48,200,82,172,213,24,46,38,188,253,225,143,116,95,255,136,118,66,114,155,27,160,120,88,28,58,246,195,114,28,199,
234,237,6,122,149,204,205,103,131,148,15,109,66,142,82,166,220,24,73,66,138,114,53,149,221,26,163,78,151,31,190,252,138,237,103,143,140,157,47,198,78,242,49,74,184,38,232,34,36,171,100,105,2,43,82,226,
120,17,181,237,29,82,25,83,191,189,226,227,143,63,210,189,62,37,73,22,148,55,170,60,253,226,11,116,16,177,92,206,112,252,0,237,250,228,115,101,100,152,165,81,191,99,53,27,49,238,182,104,158,188,97,210,
31,80,222,220,166,188,83,35,85,10,87,72,51,197,250,62,74,249,84,43,123,232,76,68,179,213,230,245,183,95,179,238,93,145,203,229,8,178,57,187,24,178,254,114,101,146,148,142,235,217,100,178,131,88,73,187,
108,188,231,139,43,179,68,83,130,117,98,95,134,164,176,158,147,166,154,234,238,38,163,254,128,55,223,124,131,87,200,252,132,188,78,99,18,204,13,44,77,215,38,85,40,215,36,169,68,72,23,207,207,176,81,219,
101,21,39,44,102,3,206,79,143,249,250,203,255,137,22,43,74,133,60,219,123,251,56,145,135,18,26,199,117,201,132,57,180,151,161,186,187,79,175,103,66,62,131,118,157,97,227,154,97,167,9,90,83,204,23,204,
193,96,9,143,218,243,32,21,184,126,134,199,47,126,206,90,10,206,47,207,56,255,240,22,166,61,60,47,64,59,46,235,197,202,252,190,149,113,133,56,202,65,75,151,84,36,70,222,83,30,171,213,220,28,86,169,32,
89,175,16,10,100,34,72,69,66,146,8,132,112,240,61,135,217,98,134,8,125,54,253,42,39,175,190,167,186,187,67,26,175,76,28,29,97,108,154,247,198,220,52,177,128,43,205,50,77,112,156,0,63,204,243,228,201,51,
214,235,37,119,245,43,26,87,231,140,123,93,146,68,226,123,218,90,72,149,117,251,120,40,28,118,246,158,113,244,236,25,221,118,155,81,183,69,171,121,205,180,219,102,54,236,33,29,15,18,205,108,185,4,165,
77,57,183,118,136,147,148,124,177,202,23,191,252,43,178,249,136,118,243,150,227,119,239,40,229,52,131,217,136,241,124,105,40,182,82,89,140,52,182,176,197,65,166,169,193,42,187,46,241,120,128,52,15,133,
117,113,24,199,207,125,198,194,36,117,215,136,84,146,211,14,113,146,240,254,229,75,106,59,53,51,37,167,49,202,210,122,82,11,137,211,182,242,210,60,55,138,192,207,147,47,237,80,217,220,98,57,91,208,109,
93,242,241,205,75,134,237,58,241,106,193,214,254,33,94,16,152,58,65,237,224,184,46,190,159,101,99,251,17,249,114,133,126,187,77,183,211,164,125,253,145,94,179,1,172,9,2,143,48,159,71,105,69,96,77,3,158,
231,224,184,1,97,174,66,121,251,128,120,189,224,250,236,132,235,179,119,172,39,125,194,76,104,110,119,242,62,155,96,18,253,218,245,13,241,212,113,13,106,123,21,67,60,71,136,196,26,87,204,68,110,110,188,
54,83,160,205,98,183,186,183,203,106,60,229,242,205,91,182,14,247,204,103,179,188,103,214,173,238,251,222,128,181,45,94,20,8,45,241,162,28,165,234,182,1,61,14,6,204,250,29,46,223,191,162,63,108,49,27,
142,40,213,182,9,162,16,169,192,113,3,147,223,201,228,120,244,217,95,80,46,150,136,23,115,110,78,63,242,241,195,91,250,189,38,142,54,50,82,54,159,35,8,67,28,37,81,174,201,220,8,225,82,221,121,68,177,188,
205,100,52,165,125,125,193,15,95,253,3,235,116,134,94,175,12,186,148,84,227,123,89,50,133,18,179,197,132,118,251,130,15,223,255,145,81,189,137,148,14,187,187,71,148,118,55,73,20,136,68,225,250,17,97,80,
96,99,115,139,249,106,65,191,215,102,52,236,211,188,61,163,115,121,134,90,40,138,187,123,68,149,18,169,50,147,134,227,187,56,202,39,202,149,200,85,203,180,123,109,206,78,222,114,247,246,21,129,246,40,
29,236,89,188,130,189,114,90,240,148,118,61,72,82,27,33,246,241,28,193,114,62,99,181,94,216,48,133,124,224,144,43,97,184,47,230,131,91,177,88,45,200,150,138,164,201,154,187,219,107,108,235,156,229,70,
11,243,146,73,98,19,168,72,141,223,216,113,51,228,242,101,132,235,210,108,53,248,241,155,111,232,156,159,144,174,215,28,29,61,38,191,189,65,170,77,250,215,15,51,104,55,32,10,139,120,249,34,237,118,135,
245,108,204,184,215,161,125,113,202,120,48,196,15,179,84,119,182,65,72,60,41,113,194,208,180,64,185,89,202,149,77,82,55,224,230,234,138,147,119,175,152,220,157,18,250,62,185,114,137,88,106,155,238,51,
225,52,161,52,78,96,14,137,251,98,4,41,161,49,159,129,197,70,35,165,53,105,166,104,33,72,81,86,151,92,35,228,154,117,156,18,101,3,68,146,178,158,79,205,46,228,161,131,21,146,181,217,155,152,69,176,153,
110,61,173,41,148,54,72,149,195,114,185,224,248,221,27,254,229,183,191,65,44,87,100,202,121,54,119,107,230,11,156,26,198,144,227,184,56,94,134,173,253,199,52,91,109,70,195,30,195,230,45,195,214,45,211,
126,219,208,43,131,12,97,24,152,224,157,20,56,94,136,146,14,126,166,192,254,209,99,150,192,205,205,5,103,31,94,33,38,125,92,237,24,238,186,76,13,23,72,42,139,191,85,246,37,37,17,82,147,45,86,40,150,139,
220,92,157,177,152,26,1,227,190,36,99,157,38,214,54,152,144,164,49,171,4,243,37,183,55,197,108,49,195,108,60,180,139,99,245,192,16,151,105,108,155,148,140,102,191,78,19,51,56,184,33,7,143,158,145,196,
75,134,157,22,63,252,241,159,25,180,234,172,23,107,50,133,18,210,85,6,105,157,74,148,227,225,234,144,218,238,33,207,62,253,132,94,183,71,247,174,78,191,115,195,180,219,102,185,152,128,99,144,4,227,233,
10,176,127,46,36,73,2,197,202,14,63,255,229,95,1,43,206,79,143,185,62,255,136,36,102,50,88,208,239,79,137,73,238,3,212,230,54,236,104,148,227,217,34,25,159,76,177,74,185,82,228,228,237,143,164,43,195,
141,74,176,21,123,66,90,223,166,145,247,180,227,24,245,80,129,239,248,4,190,111,167,107,99,68,53,54,98,139,10,191,183,52,97,2,97,218,13,8,10,85,74,181,109,64,208,239,212,121,249,205,215,116,155,117,164,
18,236,29,28,162,2,31,18,115,155,116,188,16,63,204,178,251,232,19,138,149,13,90,119,77,58,237,58,131,187,107,70,157,59,214,139,41,126,232,145,205,102,240,3,141,86,166,135,215,28,254,30,249,205,3,242,133,
18,171,197,156,250,237,37,253,78,29,157,174,136,29,243,188,200,36,53,225,177,84,32,85,128,235,5,8,173,173,221,55,34,147,205,211,137,83,150,243,153,213,4,65,165,198,6,174,49,100,79,97,37,78,99,34,81,56,
229,34,222,98,201,124,60,69,56,22,34,152,172,137,215,107,75,199,20,54,56,105,36,157,32,204,82,172,108,83,173,214,136,151,11,166,163,1,31,126,9,254,86,169,0,0,32,0,73,68,65,84,248,142,86,235,154,36,141,
169,212,106,132,185,188,65,117,88,116,75,24,102,121,244,233,95,176,189,179,199,162,63,228,226,228,152,143,239,95,49,234,223,17,47,38,72,225,145,43,22,112,93,129,86,194,184,2,29,15,225,4,84,183,31,147,
203,23,89,204,230,116,239,110,56,254,225,91,150,241,136,48,159,67,107,109,180,43,223,205,83,40,109,144,104,193,104,216,225,248,229,15,12,110,110,9,252,60,213,237,93,170,123,53,150,233,2,17,175,208,78,
132,239,103,40,149,43,224,74,250,245,54,163,126,143,118,227,138,246,213,57,171,201,138,234,206,62,229,131,29,51,165,8,97,166,48,229,146,43,86,240,179,17,237,78,147,171,171,11,26,239,223,161,147,148,210,
118,141,48,151,101,181,90,153,171,151,148,40,237,225,40,199,106,140,154,74,185,134,242,53,23,199,239,140,39,89,42,27,113,190,39,19,42,99,33,76,19,91,57,40,237,244,104,44,160,90,11,150,171,37,105,188,178,
118,72,88,47,150,36,201,218,120,103,73,80,142,79,148,45,80,40,150,152,205,103,188,249,225,79,52,79,63,178,152,205,216,170,109,81,172,109,178,150,10,149,152,127,223,117,2,162,48,71,182,82,165,209,188,99,
62,24,49,159,246,105,95,125,164,219,184,198,11,35,118,30,29,25,127,172,157,42,60,55,64,41,159,205,205,29,86,40,110,234,55,220,158,159,48,108,92,160,210,148,92,177,68,34,140,13,213,0,180,36,190,239,161,
92,31,237,104,148,19,82,200,151,240,252,128,151,223,126,77,18,47,112,92,163,69,74,145,128,210,70,230,1,147,176,197,80,38,211,244,161,105,193,86,78,38,134,179,47,18,86,171,21,74,249,120,129,207,106,53,
7,20,105,18,163,148,79,190,80,165,88,169,162,181,224,159,191,252,39,222,126,247,29,174,78,40,111,109,80,222,40,225,120,142,73,41,219,88,187,239,4,236,28,30,209,30,246,233,118,234,76,7,93,198,205,6,147,
94,147,241,124,78,121,99,155,66,217,180,6,41,169,76,48,6,65,190,80,97,99,255,17,171,36,166,126,115,201,197,251,87,172,38,93,34,207,72,129,210,90,220,144,2,169,132,209,207,133,107,253,205,30,59,7,143,201,
22,179,124,255,205,239,89,204,6,214,145,21,219,14,214,228,129,199,132,48,216,94,145,104,36,2,87,73,184,47,111,193,148,107,75,33,48,200,31,211,240,102,170,71,99,84,162,1,137,163,67,182,247,14,40,150,203,
140,6,119,124,255,199,127,102,210,111,163,210,24,63,151,69,185,6,15,172,148,217,19,9,207,163,186,179,205,179,47,62,161,223,31,208,107,54,104,53,175,152,245,154,164,243,49,194,115,81,177,102,97,139,170,
197,253,207,37,21,108,239,61,231,179,159,125,193,124,62,167,219,186,227,250,242,20,173,214,40,150,52,110,123,44,109,139,26,247,232,13,199,69,58,22,205,225,70,236,28,189,160,88,202,242,242,235,223,178,
92,44,30,112,210,34,49,201,83,91,253,101,16,38,202,74,85,210,180,140,9,82,76,11,159,176,37,60,182,13,247,158,11,99,252,93,230,229,166,20,97,84,160,188,125,68,148,47,162,146,5,175,191,249,138,94,231,22,
229,104,106,219,53,82,105,184,244,198,29,228,226,56,33,27,219,71,20,203,21,166,147,9,157,219,115,250,189,22,163,230,13,179,249,16,233,122,228,203,101,132,22,32,28,164,107,56,67,78,144,165,88,221,38,200,
22,137,215,43,90,119,55,180,234,215,36,203,17,139,213,210,166,186,141,115,72,216,164,169,27,134,38,165,44,53,158,159,35,91,169,209,191,189,96,56,234,146,40,155,76,182,134,142,181,69,57,167,201,218,72,
96,66,216,144,104,130,76,18,82,173,64,25,163,67,156,198,182,146,80,226,96,17,204,182,118,209,117,125,50,165,26,213,157,61,163,112,176,230,244,229,159,104,54,174,145,66,82,168,84,240,92,135,56,89,227,104,
195,198,113,253,28,187,207,254,140,237,189,67,214,179,25,23,167,199,156,30,191,101,208,185,99,54,234,160,125,135,82,174,128,171,140,49,72,57,14,202,113,240,194,2,229,221,71,56,169,96,48,24,208,185,185,
228,228,237,107,166,227,14,97,54,143,235,121,104,169,52,113,34,201,231,75,8,95,49,28,52,249,241,15,191,163,115,125,75,38,172,176,243,232,144,160,82,32,150,130,116,97,38,238,40,200,82,42,84,80,153,144,
250,205,37,227,126,147,102,227,154,155,227,247,36,179,37,155,155,7,236,189,120,102,164,31,20,129,103,56,55,249,226,38,78,46,162,222,106,208,170,223,112,249,242,79,164,179,49,249,242,14,65,177,240,208,
234,164,133,169,50,244,131,200,208,230,132,79,185,186,201,60,153,243,199,47,255,145,108,62,99,108,78,18,211,64,100,11,59,28,165,141,133,48,149,102,233,38,204,75,45,141,77,93,224,98,25,35,236,148,119,175,
249,167,44,30,48,182,174,235,18,100,242,228,75,21,38,139,17,127,248,221,111,105,126,60,198,241,53,181,221,167,248,153,12,177,52,32,8,169,36,126,152,35,10,115,148,183,118,184,107,119,24,118,90,44,167,67,
26,23,31,233,92,95,35,133,203,193,147,167,4,249,2,32,240,173,140,227,5,121,74,181,61,102,235,152,102,227,150,250,245,41,245,227,151,248,105,76,161,182,133,151,207,27,207,176,50,220,28,223,15,108,73,138,
75,16,68,148,170,219,76,231,51,190,250,251,255,134,31,184,184,97,64,42,86,220,135,137,133,72,17,137,137,236,139,212,92,44,83,227,102,37,33,33,89,27,153,40,78,204,63,51,184,26,77,156,196,6,47,203,125,60,
221,33,147,47,177,115,248,136,217,106,198,151,95,254,142,87,223,252,158,106,54,164,80,222,162,186,85,101,157,172,205,196,132,196,117,67,194,48,199,238,209,115,6,211,41,221,122,131,126,243,150,73,183,201,
160,217,96,45,215,132,153,2,217,76,214,252,250,90,33,93,141,86,1,197,234,14,91,7,143,104,247,122,52,239,26,156,191,255,145,116,49,33,202,249,104,229,161,133,36,73,99,228,195,0,96,219,176,128,92,177,204,
147,23,159,163,61,205,239,126,243,119,172,151,115,35,197,216,101,156,41,87,50,146,87,108,41,176,73,34,72,23,75,18,105,128,120,144,62,148,61,223,255,186,233,125,1,52,230,153,73,133,134,52,197,247,35,202,
27,7,60,122,250,140,86,253,130,223,252,151,255,4,235,37,129,43,17,97,17,180,107,211,183,130,52,85,8,237,81,44,108,241,226,211,159,49,28,14,105,54,27,204,39,61,228,122,194,100,208,67,57,18,47,21,44,19,
112,131,8,223,117,89,44,214,56,142,207,222,147,207,121,242,233,11,198,147,49,183,23,39,12,123,93,132,88,17,184,41,189,206,196,240,129,236,45,64,42,195,153,55,128,47,151,114,117,159,253,167,159,224,251,
130,223,255,253,127,97,60,25,226,56,242,161,51,88,202,212,90,75,181,197,43,75,227,223,79,76,16,83,91,128,159,145,87,239,27,182,98,51,84,136,251,22,59,101,9,187,14,65,148,167,118,240,130,221,131,35,6,205,
115,126,255,219,223,48,157,247,201,231,114,228,75,69,214,235,181,145,92,83,129,10,60,194,108,158,205,157,231,108,31,62,102,218,239,113,115,121,76,227,250,140,197,176,195,100,212,65,233,144,106,173,98,
17,13,14,74,7,120,110,136,23,230,169,108,61,66,186,14,227,241,136,250,229,25,141,155,43,50,1,76,134,35,98,33,112,149,66,107,1,86,98,244,131,44,142,235,26,38,79,80,36,83,218,226,242,213,31,57,61,123,143,
27,184,22,5,113,239,205,74,209,66,26,155,132,184,127,134,236,231,153,152,65,74,41,139,25,73,214,200,56,54,186,191,252,9,223,130,48,55,242,32,42,80,219,123,76,190,80,100,57,25,241,230,219,223,115,117,241,
6,55,112,41,86,106,166,23,98,109,112,210,78,144,193,9,2,14,94,252,156,189,253,35,166,189,62,23,199,111,56,126,253,146,113,239,142,209,176,141,10,2,170,181,45,60,215,236,189,60,63,143,235,68,120,81,133,
173,199,159,224,105,151,126,227,142,203,147,99,174,47,63,178,94,12,241,67,15,161,37,113,146,160,149,144,68,153,44,65,46,67,163,119,203,171,175,191,162,123,121,69,20,228,57,124,241,156,160,16,177,140,215,
136,84,25,143,121,16,145,201,22,201,148,139,52,122,109,6,253,54,119,183,87,52,207,79,88,76,38,228,179,27,108,63,123,66,34,18,136,215,56,190,209,163,138,133,42,58,27,210,104,214,233,182,154,220,158,191,
103,57,104,19,101,74,20,183,107,36,182,153,70,43,141,231,26,6,143,227,4,68,81,158,48,95,96,178,154,240,135,255,241,223,136,60,207,22,95,36,196,137,176,196,66,129,210,54,85,102,181,86,173,76,144,136,212,
20,149,75,145,90,141,87,217,226,243,248,33,173,155,38,177,101,83,135,20,242,101,98,153,242,135,223,254,142,250,201,71,242,153,144,218,254,46,94,20,209,105,117,200,228,18,187,84,9,8,131,12,165,141,26,221,
254,128,94,187,201,180,223,163,117,123,74,247,246,154,52,149,28,125,250,20,183,144,49,156,112,223,197,13,66,92,55,164,84,221,97,186,90,211,188,185,162,223,110,209,56,253,200,114,50,37,95,173,80,40,151,
205,194,213,250,163,131,32,52,13,54,174,79,16,22,204,97,52,159,241,245,111,127,195,106,57,33,147,55,90,168,171,4,137,178,21,202,210,180,29,173,150,107,86,107,243,226,147,18,139,137,192,132,222,82,115,
88,26,191,186,182,220,15,129,74,83,226,123,246,189,31,82,217,216,66,122,154,127,254,199,223,114,252,253,159,216,173,150,201,21,11,100,243,101,214,137,97,160,167,194,53,105,84,47,100,123,247,0,237,135,
116,110,111,233,119,27,12,154,183,140,186,29,230,139,37,165,74,145,66,190,132,235,105,132,208,56,110,6,137,160,80,221,166,178,127,68,119,56,162,209,184,165,115,123,197,98,210,35,159,51,61,170,82,40,82,
37,33,49,192,119,19,116,18,200,68,81,219,123,196,225,179,23,36,172,248,195,63,253,119,70,131,14,185,98,129,116,186,130,100,13,66,146,172,140,167,94,73,97,172,226,177,121,249,43,18,52,218,104,187,72,235,
48,177,93,177,169,48,120,239,123,76,56,9,34,49,240,181,92,97,131,207,126,246,115,86,139,17,95,253,230,191,33,150,83,194,32,180,83,159,105,16,19,137,57,92,181,118,9,162,60,95,252,226,23,172,211,152,81,
191,199,122,50,98,88,191,161,219,56,99,182,94,147,115,74,204,87,166,20,92,43,211,219,170,148,224,232,197,207,216,125,244,140,246,93,203,184,222,174,46,33,93,17,250,130,110,123,193,112,60,199,82,119,13,
183,73,123,8,41,241,252,28,213,221,71,60,253,236,51,164,92,243,199,191,255,255,152,142,251,6,199,107,117,123,97,147,204,230,144,192,234,121,63,57,122,69,98,202,236,73,99,251,162,19,196,15,160,58,245,96,
103,49,121,111,133,235,6,228,74,53,118,31,63,98,49,184,227,203,191,251,79,116,251,29,54,42,37,124,223,55,150,95,12,0,81,105,159,48,147,167,84,221,102,231,224,128,213,114,78,187,113,193,221,245,57,227,
78,157,217,120,128,112,20,155,27,85,195,113,74,4,74,184,134,82,27,20,168,29,60,67,59,46,195,225,128,171,211,15,220,94,93,224,57,48,158,207,17,24,134,146,82,2,207,117,208,110,136,246,76,242,223,247,50,
228,203,53,132,19,210,190,248,192,135,183,175,200,20,67,179,43,116,76,65,83,106,195,89,137,237,135,77,98,179,156,22,82,34,238,77,33,54,163,97,202,78,210,251,121,209,72,140,74,26,44,9,130,32,204,82,217,
222,99,99,115,147,69,175,195,215,255,248,95,185,190,57,165,144,47,18,229,51,70,102,69,26,136,154,231,162,180,199,198,238,99,182,182,119,89,207,167,52,46,78,56,123,255,138,81,239,142,249,180,143,112,60,
170,181,45,211,124,230,104,252,32,196,245,34,130,252,6,59,79,62,193,209,30,203,233,152,203,147,99,110,174,207,88,47,71,166,152,200,119,113,28,99,20,209,66,106,50,185,60,243,245,132,143,63,252,145,230,
217,5,187,155,251,84,15,118,241,114,33,75,59,29,167,113,76,198,207,145,203,148,217,220,217,163,59,234,208,190,57,165,126,249,145,198,217,5,203,241,152,173,210,54,59,159,60,39,113,20,235,120,77,232,103,
240,188,136,124,105,131,212,247,168,55,110,24,246,123,52,47,143,25,93,94,144,113,34,182,247,14,17,142,66,88,52,177,231,71,182,220,195,167,88,220,64,7,1,157,78,131,63,253,238,239,113,82,65,80,201,27,134,
185,250,201,238,164,132,52,83,138,130,120,189,66,220,79,114,82,60,48,172,215,201,250,33,102,108,92,26,174,193,186,198,230,239,105,229,18,132,89,50,197,18,95,253,246,239,185,121,247,158,173,106,153,205,
253,109,156,48,98,189,94,81,217,172,152,66,8,199,39,12,178,148,54,54,89,36,9,237,187,58,195,246,29,245,211,247,12,91,13,36,154,131,103,79,201,150,11,214,234,230,224,123,134,129,81,174,110,211,30,142,233,
116,155,76,218,45,110,206,143,25,181,238,168,110,84,168,110,215,72,149,68,11,129,114,125,3,141,114,60,124,47,36,95,218,194,137,114,244,251,61,254,244,213,223,179,28,247,41,111,239,162,53,8,17,35,181,99,
172,152,105,130,80,26,207,241,72,226,33,235,181,133,61,165,246,203,110,157,55,166,152,6,83,40,98,179,17,70,235,142,153,47,19,2,29,145,47,213,168,110,109,240,207,191,251,138,247,223,126,199,206,86,133,
234,102,217,244,15,72,193,58,78,76,35,147,22,120,158,73,87,251,217,34,141,155,107,90,55,103,116,234,151,244,235,117,134,211,5,155,155,85,242,165,13,124,215,177,254,124,131,117,174,214,246,40,239,29,210,
238,118,104,221,92,208,172,95,50,109,53,8,125,35,227,165,169,117,81,144,160,164,99,150,109,66,161,220,144,195,39,159,80,222,217,99,189,154,241,187,223,252,103,6,173,59,130,32,203,116,52,70,201,212,44,
118,147,148,56,94,155,230,46,237,178,90,204,13,254,55,49,50,77,18,67,44,238,247,64,230,203,155,74,137,136,99,107,6,48,211,109,178,78,145,26,178,249,10,207,62,251,130,32,35,248,239,255,251,255,195,168,
119,71,62,151,1,71,147,10,83,162,34,101,10,177,241,66,123,126,158,207,126,254,111,240,194,144,171,179,83,110,206,142,233,55,46,233,119,26,172,98,40,149,11,36,210,51,251,32,33,73,226,4,153,104,62,253,179,
95,178,125,116,200,93,179,78,227,250,148,217,160,199,124,212,34,204,132,172,22,9,253,193,152,56,198,186,182,52,82,9,82,37,8,162,34,47,126,254,75,54,247,118,88,78,71,28,191,254,154,201,176,99,90,166,148,
201,44,164,152,229,229,67,142,64,58,36,233,10,33,36,113,188,226,190,66,37,53,245,227,255,106,105,125,31,68,179,22,105,251,226,151,142,67,152,169,240,232,147,159,147,206,135,252,207,255,244,127,49,29,141,
216,222,220,68,58,138,88,8,132,76,13,251,72,187,68,217,34,185,220,38,251,143,63,7,160,219,188,230,242,244,45,189,219,27,186,221,59,156,40,195,193,206,22,142,35,81,218,236,133,194,40,34,204,148,216,58,
124,142,212,218,176,188,142,223,115,119,123,73,156,44,77,177,144,150,184,174,97,229,123,158,71,16,230,64,58,144,42,178,165,109,138,229,26,235,24,186,183,167,124,243,213,111,200,87,139,184,158,105,21,115,
181,45,212,65,225,58,30,9,41,171,197,28,185,72,184,207,57,10,233,32,18,88,39,43,36,247,174,30,99,34,65,66,130,68,75,139,115,119,34,178,165,26,251,207,62,71,45,103,124,251,15,255,133,171,171,51,42,155,
85,124,139,253,190,103,221,104,215,228,158,74,155,219,60,125,254,57,58,77,105,220,92,241,230,219,175,233,182,235,44,87,35,18,169,168,110,110,227,185,46,90,90,130,174,159,33,83,217,98,231,232,19,196,42,
166,215,109,112,241,238,13,151,23,31,137,151,35,214,73,66,84,46,227,184,18,207,53,14,54,29,6,89,18,153,114,242,250,123,26,231,215,236,108,237,179,117,176,67,44,19,22,211,233,195,18,208,117,93,188,48,164,
88,169,50,89,142,184,171,95,112,125,126,76,227,236,156,213,100,73,165,178,199,206,243,71,104,223,49,214,46,207,199,243,35,42,213,29,68,232,113,215,188,97,220,235,209,110,94,211,189,56,67,37,130,202,222,
1,42,227,145,198,107,180,210,248,81,198,84,31,122,38,137,154,104,135,122,253,146,87,127,248,159,172,71,99,138,7,251,15,13,236,105,188,50,192,36,233,225,184,46,142,31,178,94,27,132,66,188,142,205,203,62,
182,214,61,187,100,74,82,3,99,67,26,180,175,21,41,145,82,227,248,1,97,62,195,251,183,223,115,241,230,13,219,91,91,212,14,182,16,90,178,182,107,120,33,52,142,246,240,194,136,74,165,6,142,71,235,234,146,
78,227,154,230,197,41,195,214,45,164,154,195,167,143,40,108,86,13,195,219,13,241,131,44,158,159,33,87,169,209,159,207,233,117,238,152,245,187,220,93,159,209,187,189,34,240,67,202,91,91,56,190,135,148,
166,154,209,243,2,148,231,226,232,144,194,198,46,75,4,205,155,11,78,95,126,195,98,208,162,180,85,195,243,28,164,76,72,214,70,186,82,66,33,220,0,71,185,72,71,192,220,33,77,230,15,197,24,177,93,117,24,33,
199,160,8,164,229,128,8,235,138,138,227,4,133,32,12,50,84,183,182,248,246,235,111,248,241,95,190,228,112,127,155,194,198,6,218,49,110,132,100,29,147,10,133,171,28,124,55,36,151,171,80,216,216,160,221,
233,114,123,125,70,235,250,156,187,122,3,37,97,163,86,162,92,46,225,58,134,70,233,122,62,74,123,108,238,28,82,220,222,161,217,105,113,119,117,193,168,125,203,180,213,32,93,45,17,97,100,101,10,35,61,57,
202,51,77,89,9,228,242,37,30,189,248,12,180,75,235,238,154,179,183,223,50,108,223,162,84,64,156,174,73,151,70,119,87,194,68,222,149,114,81,218,97,189,198,68,255,215,43,195,251,79,77,248,46,177,78,30,153,
38,196,72,210,24,238,237,217,66,74,107,81,53,65,165,82,181,70,24,40,254,223,255,227,127,227,238,250,150,92,190,132,246,60,150,241,26,45,18,82,76,11,150,214,14,74,121,60,126,254,25,165,205,10,173,86,157,
235,139,119,116,110,206,24,246,91,204,230,43,170,181,109,148,227,176,74,98,75,187,52,124,149,39,159,253,130,173,163,61,250,3,115,8,142,123,93,198,221,59,164,88,177,156,78,88,46,19,187,95,72,109,97,143,
6,161,41,85,246,248,217,95,254,27,60,95,51,27,15,184,120,247,3,227,97,151,249,98,101,100,153,196,236,88,210,251,23,182,109,77,147,2,86,107,44,170,3,51,56,8,140,155,199,180,163,163,132,36,78,76,133,142,
120,16,188,18,146,52,197,245,66,170,251,71,120,114,201,255,248,191,255,79,6,163,17,155,219,27,32,237,149,1,105,160,111,218,200,22,217,92,153,237,163,167,72,165,232,223,93,113,241,238,37,245,139,83,198,
163,1,218,207,178,123,240,8,207,21,134,238,232,122,184,126,22,55,40,176,117,240,9,34,89,211,109,182,12,194,227,238,150,233,176,71,152,245,240,93,15,223,119,81,74,17,70,17,202,11,16,202,65,74,159,66,101,
135,66,101,131,229,98,69,167,126,198,159,190,250,71,242,197,136,208,55,72,234,52,177,78,165,84,130,163,209,126,100,242,5,241,154,213,82,178,22,49,234,190,125,221,218,163,147,196,236,60,18,97,246,102,82,
216,108,144,82,32,20,65,54,195,198,222,17,110,178,226,95,254,238,63,115,219,184,101,115,103,203,54,113,221,99,162,52,90,75,252,76,68,97,99,155,163,231,95,48,239,246,152,140,135,188,249,246,95,104,220,
158,51,155,15,241,194,136,205,205,26,65,228,225,186,14,142,31,224,121,25,114,197,77,118,142,62,71,146,50,232,53,248,240,242,7,238,26,55,44,230,61,72,214,20,55,54,241,125,199,72,155,66,131,116,209,126,
24,112,126,241,129,211,31,223,178,183,181,67,190,90,50,149,16,107,227,169,85,169,169,81,11,130,28,165,210,6,169,39,104,92,95,114,242,254,13,245,143,31,97,30,83,174,108,178,247,232,144,212,115,12,82,84,
107,2,207,132,116,116,46,50,211,108,191,67,191,123,71,227,248,45,233,98,197,198,230,62,153,114,137,36,137,113,181,67,16,100,81,202,37,240,2,170,187,7,12,87,11,78,223,190,230,242,135,111,88,141,6,108,237,
238,91,204,169,32,145,198,11,44,133,192,243,205,151,89,43,77,18,59,134,9,196,202,220,230,149,113,210,144,10,226,196,164,70,227,36,65,146,176,78,204,148,43,181,68,166,41,65,16,113,91,191,225,251,47,191,
226,232,232,144,92,185,12,34,182,87,182,251,74,63,133,31,70,100,114,21,50,197,255,159,168,55,107,178,228,58,207,245,158,53,228,156,185,231,189,107,158,186,171,187,49,139,0,7,233,48,78,88,161,11,219,225,
59,159,136,227,63,224,240,133,255,128,111,29,186,241,95,113,88,210,57,162,36,138,20,9,138,20,1,144,32,166,6,26,61,85,119,215,60,15,123,215,92,123,206,204,229,139,149,85,228,13,131,65,160,129,222,93,59,
115,173,239,123,223,231,105,112,116,114,76,231,96,135,189,181,21,250,167,103,4,65,192,244,194,18,205,153,73,82,192,213,214,58,239,56,1,229,198,4,151,55,93,58,71,251,12,187,215,92,28,237,211,217,94,5,163,
152,94,152,37,42,71,136,60,199,213,22,156,166,93,31,199,181,173,193,238,112,204,218,198,42,187,207,190,65,141,110,168,181,234,184,190,139,192,190,216,172,20,221,146,18,29,215,67,73,199,162,4,164,99,17,
169,153,65,139,12,100,94,180,104,149,133,70,81,44,48,185,197,233,102,119,38,157,56,46,177,250,250,21,223,127,241,39,22,230,103,8,146,8,161,32,77,135,197,201,132,59,190,120,92,169,50,49,51,203,245,197,
21,103,71,123,28,109,173,210,57,220,35,27,231,180,166,38,41,215,170,246,202,170,20,142,235,162,93,159,90,107,154,218,204,28,71,71,199,180,15,118,184,60,61,230,250,232,136,241,184,139,27,68,56,94,82,112,
196,77,81,73,151,72,28,42,141,41,30,188,243,62,215,253,27,218,219,91,172,174,124,135,206,123,86,48,33,11,251,148,201,45,240,171,128,147,105,79,147,143,109,196,212,113,67,134,195,1,72,219,188,212,5,222,
216,178,120,44,255,68,24,85,124,30,150,151,115,199,74,49,138,74,53,230,215,255,242,15,156,30,29,19,87,202,160,21,163,113,106,103,186,5,170,66,105,59,150,169,77,204,48,255,240,17,189,254,13,123,235,43,
28,111,173,209,189,57,103,156,231,52,90,147,248,81,169,88,68,143,113,149,70,74,205,131,247,126,200,236,210,50,151,151,39,28,237,108,97,198,41,215,157,35,6,253,75,130,192,35,55,130,225,56,71,223,245,49,
92,80,14,83,139,111,241,225,79,126,130,148,176,183,187,197,193,238,6,1,93,174,206,206,73,51,131,212,69,210,168,128,225,106,165,11,168,157,141,112,34,28,75,149,45,204,98,183,193,9,114,101,247,62,183,173,
119,116,113,83,72,237,119,73,106,146,82,131,80,195,111,254,219,223,97,200,153,158,153,40,52,143,162,96,228,3,34,195,247,35,226,82,149,198,204,50,65,156,112,117,118,204,250,203,239,216,89,123,201,217,89,
27,63,174,242,232,221,183,44,210,56,31,226,56,33,126,146,88,40,220,226,219,104,5,157,163,19,54,215,95,115,222,62,226,234,244,4,191,228,227,123,46,149,114,140,210,2,41,93,148,27,226,56,30,82,135,52,166,
239,17,39,37,174,174,175,57,92,95,227,205,139,63,161,156,156,74,37,33,207,5,89,129,69,80,74,32,28,23,229,6,104,233,216,246,186,26,144,231,54,237,102,247,49,185,93,220,75,141,36,3,105,19,91,228,57,90,254,
25,227,145,25,65,84,174,17,122,138,79,255,241,255,227,170,127,77,99,186,113,231,136,54,198,98,199,165,16,248,97,68,82,153,96,225,193,59,84,226,132,171,254,128,157,213,21,246,55,94,211,237,94,224,197,17,
51,243,51,54,210,123,187,212,117,124,194,234,36,11,239,252,0,223,241,56,61,220,231,213,211,239,56,216,223,102,212,191,36,29,103,84,39,107,132,174,197,194,59,158,143,227,120,128,131,62,106,239,113,244,
102,147,165,135,111,33,28,27,237,19,133,53,70,73,187,233,15,130,128,90,173,142,95,10,57,236,236,177,186,242,140,163,213,117,84,38,152,152,158,99,250,193,125,132,86,24,147,225,106,159,192,143,168,212,38,
137,26,85,78,142,14,45,29,239,180,205,222,250,43,6,215,125,154,173,105,106,51,19,8,149,227,10,69,20,197,72,215,33,10,43,212,167,166,184,28,15,89,127,253,140,245,167,223,161,186,3,106,173,9,162,106,25,
200,80,194,98,70,29,165,240,188,0,71,123,32,36,190,27,144,36,85,218,102,76,247,106,96,227,98,185,69,2,24,45,109,41,235,214,87,203,173,139,213,32,139,27,192,197,229,25,251,27,59,204,47,45,17,149,3,114,
51,182,17,180,66,20,172,164,70,123,154,168,84,161,209,106,114,117,101,151,76,111,190,127,76,239,226,156,82,28,177,240,224,1,126,165,198,88,216,93,68,82,46,227,250,17,245,214,12,189,220,208,105,159,208,
191,60,227,226,228,128,253,205,53,178,44,103,122,113,129,82,181,130,200,82,60,199,74,30,180,242,136,162,50,65,165,201,249,245,13,235,171,43,236,191,126,14,195,11,226,82,149,164,100,151,192,121,54,46,114,
232,150,19,239,5,145,253,178,234,0,63,46,147,229,154,155,235,107,180,233,23,21,123,197,120,156,34,181,229,143,24,3,89,46,44,139,72,91,94,76,158,102,40,45,105,119,142,57,220,59,230,222,195,37,180,171,200,
71,197,23,62,19,160,5,38,179,90,182,32,46,209,154,158,71,185,1,162,219,227,112,119,147,227,131,93,60,207,163,209,74,168,214,43,5,76,202,194,197,112,60,26,205,89,166,150,150,57,56,58,230,116,127,151,139,
206,62,215,71,251,140,71,55,136,194,133,96,175,36,41,210,184,184,197,15,235,236,210,3,38,23,238,113,211,189,97,229,217,247,236,109,188,38,116,115,50,43,197,181,120,233,177,61,221,187,218,74,69,44,228,
204,160,164,75,169,84,163,209,168,241,122,229,188,120,56,91,236,130,25,15,145,70,22,105,21,59,179,205,242,156,92,217,48,128,40,40,100,97,18,242,221,87,95,48,236,13,41,213,107,228,169,45,103,229,153,101,
234,8,33,237,169,27,65,92,106,241,240,253,15,232,247,186,236,111,188,226,245,147,175,25,246,110,80,74,210,168,182,48,174,139,246,180,197,122,224,97,208,44,45,191,199,204,210,2,157,206,1,251,91,107,92,
28,239,211,63,111,51,30,247,208,142,75,110,20,227,193,45,14,90,91,36,178,227,177,240,240,7,188,243,195,191,96,60,232,241,252,249,19,14,15,247,104,86,60,218,199,39,244,250,163,130,235,2,185,204,81,216,
191,71,187,14,24,112,195,50,213,250,4,233,232,134,237,245,87,150,255,162,185,51,122,73,33,44,111,198,110,120,64,88,196,178,214,14,34,77,45,127,42,29,242,237,31,126,143,19,184,72,153,145,155,172,208,63,
230,40,165,139,194,152,79,185,90,35,172,78,81,107,212,233,93,93,176,183,250,140,55,207,30,211,235,222,208,156,152,100,113,105,6,169,13,198,140,81,218,33,72,18,92,191,196,196,226,35,92,223,229,120,111,
131,221,205,77,46,79,219,92,157,30,162,181,34,14,2,170,149,50,82,89,8,157,235,39,56,126,136,118,35,26,211,247,241,252,128,155,139,51,94,60,254,138,235,243,125,132,201,168,213,75,150,192,91,28,218,181,
180,56,25,233,4,72,105,195,17,202,245,144,50,224,234,234,134,156,28,73,129,95,49,170,24,239,88,186,176,82,10,153,103,184,174,67,14,133,101,203,197,145,240,221,239,254,141,235,180,79,82,43,163,164,65,230,
246,70,116,203,220,113,92,159,164,54,197,196,220,125,42,149,38,82,24,58,123,91,188,126,242,53,215,189,11,146,90,153,86,179,133,150,154,28,240,188,16,55,136,137,171,147,44,189,243,23,184,64,123,127,135,
213,231,223,113,124,176,77,247,188,131,84,130,74,163,65,228,121,244,122,35,156,40,68,106,23,199,11,41,55,166,209,215,157,14,173,153,105,208,194,42,223,114,108,66,196,220,202,80,28,162,168,140,31,199,244,
6,87,188,122,246,132,189,87,171,120,185,164,57,57,205,204,242,34,153,186,149,147,128,239,187,196,113,141,82,163,206,241,249,49,215,23,29,186,55,231,236,173,191,228,186,115,73,173,58,197,212,210,18,66,
219,180,184,91,200,85,92,63,161,58,49,197,101,191,203,246,238,22,155,207,190,37,191,58,167,84,110,81,109,53,144,142,75,158,13,193,80,96,97,3,180,235,225,185,49,158,31,83,110,213,89,91,93,225,230,234,146,
108,108,121,239,153,201,44,239,58,77,237,131,62,79,139,211,169,85,178,75,84,129,77,78,185,185,190,160,218,170,34,20,140,199,99,28,165,49,133,187,213,254,25,57,4,65,137,56,42,147,229,57,71,135,187,60,253,
242,11,210,171,115,106,245,58,51,11,11,248,165,178,93,120,101,16,149,202,118,201,90,105,49,70,112,180,189,197,160,123,78,247,188,67,123,111,147,110,247,154,153,217,123,76,206,206,22,58,0,141,19,132,40,
199,35,12,171,68,149,38,23,189,62,251,91,27,28,172,189,66,142,187,104,63,164,84,171,128,42,150,144,194,94,181,45,250,212,67,20,144,177,160,92,231,184,125,194,222,214,58,146,20,45,205,221,109,71,21,250,
1,147,91,214,149,80,150,9,174,212,45,99,197,37,75,51,250,55,55,180,166,26,100,5,137,210,243,44,163,126,144,165,118,44,224,8,130,40,166,217,154,34,142,43,92,117,47,249,244,119,31,211,217,219,36,142,2,170,
213,58,126,28,219,56,163,16,40,199,67,249,62,73,210,96,106,225,62,167,23,215,156,119,142,184,185,238,208,235,216,184,89,238,250,148,130,24,215,117,25,103,99,2,207,198,80,181,227,210,154,188,199,244,210,
61,174,123,55,108,239,108,112,176,181,65,224,228,72,229,217,63,235,172,96,200,20,82,117,187,175,144,72,233,226,123,101,222,250,224,7,8,145,242,244,187,175,200,141,29,79,8,97,200,37,228,227,113,161,182,
148,164,121,142,204,138,104,100,102,103,220,227,241,24,33,93,206,79,59,182,117,236,185,54,138,39,236,137,79,96,108,38,221,228,133,12,37,97,249,209,123,120,94,192,233,225,22,223,126,254,31,12,7,61,60,215,
35,138,124,139,244,208,86,209,24,68,33,131,155,49,141,233,37,150,223,125,151,179,179,54,7,91,107,92,118,142,232,158,30,50,24,246,237,40,68,41,134,131,113,33,117,209,133,187,194,227,193,7,63,100,241,193,
35,134,253,30,187,27,175,217,222,218,100,162,21,115,125,118,74,175,59,42,220,193,182,68,100,189,204,46,66,88,218,165,95,174,243,240,189,15,185,185,56,224,233,203,87,197,174,35,69,230,118,212,97,195,248,
246,20,111,140,141,101,42,81,152,215,4,133,147,85,208,189,108,227,6,186,152,249,219,226,95,154,102,4,129,139,82,118,46,30,38,49,97,169,65,105,98,14,45,225,242,100,159,231,223,60,102,208,239,81,107,180,
88,186,55,135,18,134,44,27,219,36,96,82,181,50,238,233,251,4,81,66,247,188,205,193,214,6,87,231,39,92,156,236,145,51,36,42,53,169,150,147,34,197,227,18,132,17,202,113,113,253,50,181,233,123,104,165,185,
186,56,227,205,211,111,185,56,59,162,123,121,74,115,162,129,171,237,98,151,204,94,119,60,55,188,27,51,26,225,17,215,166,112,148,228,197,250,27,242,34,98,73,46,48,210,78,222,157,226,187,146,141,139,174,
75,177,27,212,82,98,68,6,38,229,108,127,19,229,40,34,17,160,149,3,140,139,34,96,110,61,195,218,161,84,173,83,174,181,168,79,207,33,76,206,197,193,1,95,124,250,91,206,111,218,212,27,117,154,205,22,66,56,
40,165,139,223,87,72,152,212,88,124,248,46,42,77,185,190,185,98,237,197,83,218,135,187,92,95,30,97,164,193,143,74,248,174,44,144,23,182,183,228,184,1,181,233,37,102,231,151,208,218,245,172,33,42,203,237,
91,146,12,105,108,218,195,83,14,165,82,131,82,181,78,111,220,229,201,183,95,178,249,237,19,18,47,98,238,254,60,149,169,38,70,21,205,204,92,18,151,42,148,146,58,181,70,157,206,121,155,243,195,125,78,59,
199,28,110,190,164,215,185,32,9,234,60,120,231,109,112,4,210,228,68,65,132,118,61,162,184,70,80,111,210,233,94,112,180,189,205,206,234,51,178,243,19,28,55,160,50,217,68,56,10,147,219,101,146,210,46,65,
224,163,148,135,231,197,212,39,236,114,249,139,79,127,71,54,236,22,240,47,251,163,103,3,40,57,150,229,36,139,121,190,77,238,8,141,93,38,217,122,42,90,187,228,169,185,123,96,72,101,13,55,82,187,72,36,110,
224,147,196,53,220,36,226,205,235,87,124,241,239,31,195,120,192,228,212,52,83,75,115,104,223,195,100,198,58,4,180,67,20,37,148,202,53,6,2,14,118,54,185,57,239,112,213,182,251,139,110,239,138,230,228,20,
83,11,115,22,202,229,106,130,208,50,188,75,213,22,94,92,231,228,236,156,131,189,29,118,87,87,24,156,181,137,75,1,245,102,3,180,34,75,51,28,109,19,35,126,24,162,148,143,214,62,229,202,52,181,137,105,86,
94,126,199,218,179,239,112,67,199,142,180,148,160,176,122,218,209,71,110,151,180,185,176,110,89,161,29,43,104,55,2,207,49,140,201,139,225,254,24,153,23,37,35,149,147,165,105,225,80,213,4,81,137,90,99,
138,234,196,20,157,179,19,126,251,171,95,114,125,188,67,179,150,16,68,33,218,245,201,51,75,36,209,174,213,177,149,227,42,247,223,126,143,211,243,75,14,15,119,57,61,218,166,123,180,199,85,251,132,76,75,
74,126,96,219,143,6,28,71,35,29,13,120,44,46,191,79,125,106,138,139,203,75,118,182,86,217,120,245,156,192,73,45,228,78,91,164,117,62,30,219,197,160,99,109,87,86,233,230,49,179,240,136,119,127,240,17,167,
237,3,62,249,205,199,214,104,85,40,56,199,249,8,51,54,22,179,129,205,230,51,206,236,2,206,228,228,70,144,153,212,126,39,178,194,211,234,41,187,251,185,173,87,26,59,209,118,252,128,81,127,132,23,148,152,
189,247,54,245,214,4,87,23,29,62,253,205,47,17,217,128,106,146,216,165,168,177,162,115,149,103,12,186,3,164,116,169,213,103,121,247,135,63,230,180,115,194,222,198,26,167,39,123,92,159,236,145,141,122,
160,3,180,246,25,12,83,164,176,173,98,165,53,126,80,225,237,31,254,148,230,84,147,235,171,43,14,182,87,217,217,89,163,94,242,24,93,95,208,189,238,146,102,118,17,107,148,64,233,208,122,39,28,31,55,40,49,
189,240,144,185,251,247,88,123,241,21,207,190,249,202,106,14,29,105,227,167,89,134,81,2,89,252,187,230,134,194,28,7,74,217,164,138,212,18,145,102,150,138,41,0,37,113,180,5,180,101,89,134,239,59,72,147,
219,150,118,16,18,38,13,146,198,28,174,227,80,89,62,0,0,32,0,73,68,65,84,86,28,109,191,230,211,95,253,156,81,62,98,254,222,34,83,19,13,75,177,20,138,216,119,209,126,133,176,84,165,54,189,76,82,171,115,
213,62,97,245,197,19,206,142,247,57,59,222,103,48,28,82,105,52,104,212,42,133,160,69,225,250,46,142,227,163,188,58,205,249,7,100,89,202,249,233,9,175,159,124,205,217,197,9,89,255,146,40,137,136,34,15,
200,138,147,184,135,118,45,250,220,8,133,19,212,40,183,230,208,34,227,243,127,251,39,140,206,108,180,179,64,105,100,216,155,75,46,20,218,72,164,206,11,207,173,46,14,84,22,113,158,141,199,8,161,172,252,
104,60,198,24,27,112,144,74,35,115,43,138,9,146,18,113,169,206,212,226,35,124,229,208,222,94,229,55,63,251,123,174,250,231,204,205,205,147,84,74,54,241,131,196,139,125,124,63,33,42,55,185,255,222,135,
84,42,101,218,91,219,172,60,255,142,189,173,53,206,143,246,24,155,49,149,122,147,164,20,219,222,65,16,145,184,1,110,16,51,189,252,30,147,19,179,140,6,125,27,65,54,6,76,102,217,27,185,178,133,31,41,176,
105,148,48,34,147,134,103,79,30,179,253,108,133,82,82,101,97,126,145,234,116,131,241,120,84,252,125,2,63,10,137,147,42,213,230,20,221,116,192,89,251,132,78,251,144,253,205,85,174,79,58,196,110,153,7,111,
191,141,151,132,244,186,215,4,161,37,184,133,113,133,176,94,231,252,230,156,147,253,109,14,118,54,184,57,62,66,73,143,230,244,28,78,228,89,96,152,176,150,24,207,247,241,220,0,55,46,83,107,205,146,9,195,
151,127,248,29,215,39,71,148,154,117,210,241,200,130,21,178,98,91,110,148,93,224,146,223,41,199,114,176,245,243,187,38,142,157,99,106,109,105,121,82,21,151,88,41,16,6,92,215,35,12,75,132,73,204,155,215,
47,121,252,135,63,32,243,140,169,249,25,38,167,167,80,174,29,135,40,109,127,13,55,180,120,87,233,7,116,118,118,232,159,159,114,121,188,67,123,103,147,139,179,75,154,83,45,102,230,23,48,34,67,73,135,208,
79,112,181,71,28,215,209,73,149,227,179,51,78,143,246,233,28,108,115,118,184,71,173,20,80,173,85,240,188,0,35,44,55,72,24,129,171,93,91,70,209,33,173,233,251,248,73,194,218,235,231,188,124,252,37,229,
114,84,228,235,20,82,218,47,101,150,142,81,210,41,56,52,216,246,161,177,87,77,165,64,11,69,38,236,239,219,246,184,4,194,113,208,194,150,112,114,41,17,202,160,28,135,74,165,202,196,244,28,163,52,227,139,
223,127,76,239,236,136,169,70,149,48,41,21,104,12,133,52,18,165,12,158,111,115,208,115,203,111,115,221,31,210,62,58,160,179,191,205,205,241,54,87,23,29,134,66,82,175,212,8,162,200,142,151,92,23,215,15,
112,156,152,133,185,101,226,90,157,211,243,83,118,214,222,176,191,181,142,166,79,150,9,144,154,209,120,96,113,209,82,20,248,14,91,240,83,218,227,225,187,31,50,57,59,199,89,231,128,79,62,254,249,157,96,
60,187,205,215,23,1,128,52,203,17,74,66,70,65,36,77,17,90,146,231,118,164,137,84,8,99,5,229,142,239,147,231,99,210,193,24,138,168,161,114,124,187,240,212,138,36,105,112,255,209,35,206,59,187,124,241,217,
239,8,29,16,194,99,156,101,118,222,91,240,86,68,6,94,224,225,7,85,30,253,224,35,122,189,46,39,71,251,156,30,239,114,221,62,96,208,191,65,59,46,113,20,49,24,14,145,162,192,35,8,137,31,213,248,224,163,255,
76,121,162,193,229,197,57,39,251,187,236,110,190,193,13,12,233,120,68,239,106,192,40,205,173,207,84,72,187,180,118,172,104,37,136,27,44,189,245,62,83,139,75,180,119,95,241,237,231,127,68,187,218,162,0,
114,235,2,54,119,32,193,59,61,70,129,227,54,228,105,97,140,42,108,100,50,179,165,70,147,218,118,187,84,2,71,233,66,41,106,227,134,65,148,80,174,206,80,42,197,28,174,191,230,179,143,127,78,110,50,22,230,
167,137,146,224,142,255,164,28,7,63,169,226,250,101,74,245,105,194,164,68,239,234,138,237,213,23,116,14,183,56,221,219,97,152,14,137,202,101,154,173,82,225,234,245,209,94,130,227,68,56,81,141,184,218,
162,223,191,161,127,125,201,171,239,190,166,211,57,70,100,93,164,171,169,215,18,242,212,38,203,164,178,82,22,169,92,164,246,136,42,45,42,245,22,74,73,190,250,229,47,24,100,125,124,87,99,10,12,180,40,144,
18,249,237,193,17,89,136,79,192,20,105,192,172,160,181,218,15,166,64,80,11,201,40,179,234,84,37,11,126,190,235,225,39,21,234,179,203,196,73,194,233,250,43,126,251,79,255,64,119,112,197,236,236,52,65,224,
219,210,165,180,80,52,63,44,19,132,101,166,238,191,69,224,250,12,111,174,217,94,125,197,209,206,22,103,251,187,244,134,55,84,38,166,240,66,223,254,60,250,246,182,162,189,152,217,7,239,211,104,78,209,187,
233,114,178,179,131,166,152,211,25,101,151,146,50,47,200,153,70,19,197,49,65,185,204,218,214,11,54,95,188,32,241,34,30,60,122,64,88,45,51,202,45,123,197,144,18,121,33,73,82,166,214,154,38,85,130,147,227,
35,142,14,54,217,125,179,194,117,231,12,79,122,44,220,91,198,75,60,198,163,46,73,232,19,68,17,113,185,65,80,107,114,124,122,194,245,217,25,135,251,7,156,108,174,225,166,25,147,139,139,132,149,200,206,
17,17,132,174,135,231,5,248,190,79,92,157,36,168,77,208,27,245,120,252,249,239,56,89,93,101,225,209,131,98,97,166,200,211,66,128,33,52,10,131,16,185,93,206,40,105,175,222,121,86,240,67,236,53,85,20,39,
60,41,5,158,212,246,134,144,91,131,143,22,46,174,27,81,169,54,73,179,148,175,255,240,123,242,126,159,251,247,23,169,54,107,5,203,167,216,185,43,65,24,132,132,97,153,184,212,224,176,211,230,242,244,152,
139,163,125,142,183,214,232,117,251,212,39,38,89,92,190,111,19,57,74,82,42,85,112,60,251,226,211,113,149,195,131,99,206,142,247,56,239,180,217,124,253,134,196,135,184,106,69,202,228,22,93,124,135,19,214,
46,97,220,160,49,181,64,166,92,214,95,61,227,243,223,253,138,70,179,105,37,21,233,176,144,61,20,17,60,165,49,153,197,8,72,93,188,236,114,115,231,60,181,200,9,123,250,181,32,186,49,18,23,215,113,73,179,
17,70,58,100,153,33,140,98,42,141,41,188,192,229,147,95,252,11,199,27,235,180,38,106,148,39,154,56,202,103,52,236,217,133,158,50,120,65,130,23,150,89,186,255,22,153,118,57,57,216,228,96,127,141,171,253,
61,206,78,15,72,13,76,76,206,160,93,151,204,24,2,207,183,34,29,55,100,118,233,33,149,230,4,199,237,3,14,118,182,57,63,218,103,220,59,183,45,83,199,179,77,200,177,213,46,106,199,69,41,23,99,32,169,77,241,
246,7,63,160,212,168,177,183,181,193,231,255,254,75,70,195,33,129,239,129,20,246,225,44,11,255,170,49,246,236,54,204,239,72,144,198,128,24,27,219,170,212,154,209,192,178,138,178,212,144,245,123,164,233,
216,214,232,165,61,40,57,210,238,56,156,160,196,135,63,253,41,152,30,159,253,230,95,24,117,111,8,28,151,44,23,160,236,205,40,55,6,149,223,58,70,19,222,249,240,199,104,79,211,222,222,166,189,191,201,249,
193,54,227,113,223,102,242,181,149,89,24,33,112,157,0,71,249,56,126,194,71,63,253,31,41,213,18,218,157,19,206,143,246,185,58,111,163,229,136,172,223,167,155,9,6,131,148,44,179,72,96,173,11,152,156,116,
168,77,44,242,222,143,254,138,168,146,112,178,245,154,143,255,251,223,161,125,175,32,70,10,50,99,11,71,18,67,150,22,24,115,37,254,156,80,41,176,13,38,183,179,106,219,107,204,80,74,35,181,13,54,228,169,
61,241,42,153,163,100,134,27,36,84,154,179,76,222,123,192,201,218,83,126,255,175,255,136,27,6,60,90,154,193,209,146,156,98,153,238,41,226,36,34,8,42,248,149,9,146,218,4,221,171,107,78,246,214,217,90,123,
197,197,225,62,215,189,107,74,205,22,83,179,147,68,161,139,214,1,81,185,134,80,46,81,117,154,164,218,224,252,244,156,155,235,11,246,183,86,57,222,223,65,41,171,240,172,199,33,227,225,152,44,23,248,126,
100,83,112,218,65,251,101,154,51,203,148,43,85,76,54,224,243,127,253,25,7,237,3,170,245,200,158,12,85,110,153,63,78,193,40,202,193,145,202,46,242,115,109,247,35,210,22,223,40,132,59,66,25,180,44,118,98,
70,130,204,109,235,89,75,210,28,252,216,22,199,166,230,151,56,122,254,148,223,254,236,239,24,234,156,197,123,115,246,208,93,20,187,132,144,4,81,68,24,150,104,46,60,160,53,57,141,28,13,121,253,244,57,175,
95,62,225,244,112,135,222,168,79,185,217,34,74,74,64,134,118,66,130,48,198,9,98,150,222,249,136,122,115,146,108,56,226,244,96,143,213,151,79,209,90,89,242,93,150,25,155,219,43,144,193,129,227,19,149,203,
28,181,119,121,245,205,99,106,97,153,185,165,121,84,224,50,28,142,48,69,173,87,10,183,80,197,53,145,129,75,251,248,128,189,141,87,236,189,121,69,239,252,156,106,92,97,126,233,30,113,163,196,56,31,227,
72,31,223,143,9,163,42,97,181,201,233,213,57,39,7,251,12,186,215,156,108,173,194,120,68,165,53,73,92,47,219,235,183,201,9,93,159,48,178,156,249,82,109,14,183,90,227,226,234,146,231,95,127,202,225,202,
10,19,211,83,150,133,147,154,187,211,152,210,118,156,145,231,25,74,104,180,114,144,74,145,166,99,27,190,54,182,24,35,138,164,177,228,86,170,114,107,10,178,133,136,76,8,252,48,33,21,134,63,252,238,183,
248,57,204,61,120,64,84,137,237,137,38,179,229,19,85,80,235,60,63,161,92,155,228,162,219,227,170,221,230,104,107,141,206,193,54,131,110,143,90,173,197,204,242,18,210,177,148,203,82,169,102,141,80,229,
6,58,46,211,62,62,225,100,111,155,222,205,57,27,47,95,225,144,211,154,104,18,39,165,98,109,150,225,184,17,65,16,226,184,30,213,250,44,97,115,134,155,222,128,147,189,87,60,249,211,239,72,124,23,207,119,
73,211,204,126,14,146,34,62,39,45,55,165,40,19,73,124,164,35,200,70,163,98,216,3,121,150,146,229,133,150,237,150,160,168,52,185,176,169,19,145,103,184,174,160,92,174,82,42,151,249,253,175,127,201,222,
234,10,243,139,51,68,73,98,199,34,2,208,26,147,101,40,237,17,197,9,147,211,243,184,229,18,167,103,167,156,236,110,112,188,249,134,97,191,135,244,98,106,81,72,24,71,246,36,234,184,56,110,136,118,19,238,
63,124,15,55,73,56,62,109,179,183,190,202,205,197,41,253,171,19,92,37,64,6,96,52,54,122,101,247,3,174,23,128,145,204,221,127,139,7,239,127,128,144,154,195,157,53,190,249,244,55,244,111,46,9,227,216,158,
192,82,123,114,149,69,78,53,47,72,135,121,106,83,44,82,22,192,52,97,155,148,131,222,144,60,29,131,178,56,224,188,208,214,201,130,242,128,144,140,70,3,92,29,240,246,251,63,194,152,62,191,249,217,223,147,
118,123,184,202,97,156,101,54,94,106,28,140,178,129,216,40,177,100,213,183,62,252,49,81,18,112,117,222,230,104,119,157,246,246,26,151,151,103,40,87,81,139,42,164,25,164,131,17,113,185,132,200,21,65,82,
231,253,31,255,148,168,154,112,124,124,192,206,250,107,46,59,71,100,163,30,174,11,100,134,110,119,64,158,219,22,173,214,54,212,224,120,49,179,247,223,229,173,15,254,2,129,161,189,189,198,199,255,240,255,
50,22,6,95,91,232,89,134,70,26,73,54,78,17,164,197,78,195,222,10,165,246,208,82,50,206,51,52,166,104,155,254,249,179,202,178,33,194,72,242,76,224,104,205,56,27,23,196,86,69,41,42,83,159,94,160,179,181,
194,111,127,254,175,196,141,10,211,173,82,97,108,179,152,114,173,172,66,212,11,74,120,73,141,114,115,6,16,244,46,58,236,188,126,78,103,111,139,94,175,71,109,162,197,252,124,11,207,181,75,250,32,41,161,
116,64,84,153,164,62,181,64,255,234,130,222,213,57,219,171,47,57,59,61,134,108,128,49,210,238,230,140,32,75,65,186,158,189,61,122,33,97,101,130,214,194,67,66,63,192,100,35,62,255,245,63,179,177,189,78,
101,170,105,119,15,185,157,44,40,129,29,137,202,162,204,137,45,28,106,41,24,143,45,161,84,22,63,16,38,183,118,48,101,236,127,91,75,153,141,23,27,33,145,202,144,84,26,52,166,231,56,120,250,13,159,254,234,
223,48,145,195,84,173,138,49,99,50,147,23,174,100,129,246,109,214,190,50,57,79,163,53,13,105,198,209,230,26,79,190,254,156,253,221,77,242,124,68,109,162,69,92,42,225,56,14,90,71,184,65,140,27,86,88,122,
251,3,26,141,73,250,55,93,14,54,214,121,253,252,9,23,231,39,104,141,38,21,198,226,119,111,5,27,82,18,6,33,55,227,46,223,127,241,5,141,168,206,212,252,4,70,194,56,179,191,97,105,44,123,60,240,35,146,82,
21,183,92,230,226,188,205,206,214,27,54,94,188,32,191,190,33,241,202,220,127,231,61,130,114,5,147,13,8,92,167,16,129,215,40,183,102,57,185,236,112,122,114,64,255,230,146,221,55,43,140,207,47,169,213,170,
180,102,90,246,202,148,229,132,177,71,224,219,22,103,117,122,158,84,7,156,156,28,241,250,217,55,108,127,255,29,141,122,139,168,90,102,60,236,89,22,8,6,165,125,140,73,139,22,174,194,72,137,163,4,174,171,
25,41,219,24,204,205,173,156,128,130,229,93,176,189,177,186,63,35,140,213,214,73,203,195,254,242,179,223,51,184,188,228,225,163,135,118,182,108,236,13,64,202,2,205,235,216,106,121,92,170,51,204,115,174,
47,207,216,223,124,197,225,230,26,34,79,105,54,155,76,205,207,161,61,133,116,92,194,48,196,11,2,130,164,138,27,215,56,238,116,56,57,216,161,119,115,206,246,234,42,38,237,209,154,153,162,84,169,33,149,
221,45,248,158,143,23,197,184,174,79,125,98,30,191,210,226,252,226,138,211,195,93,158,254,233,63,144,249,152,82,189,102,181,157,121,122,103,33,18,66,223,209,30,49,41,162,176,154,57,218,3,229,144,165,35,
178,177,69,7,167,217,184,24,122,41,219,194,77,199,5,90,215,22,91,140,80,36,229,58,127,252,236,247,28,110,111,49,191,52,71,24,134,246,186,111,114,210,241,0,147,219,180,86,82,178,124,166,74,107,154,211,
211,51,78,246,55,217,122,245,148,193,205,53,66,59,84,170,21,124,223,3,9,174,118,112,130,8,223,15,88,120,240,54,113,173,197,193,209,46,219,155,175,233,157,158,209,189,60,65,146,146,27,23,37,52,194,228,
164,89,102,85,120,174,71,24,149,153,89,124,192,242,59,239,115,121,125,77,255,186,195,215,159,124,76,239,242,148,32,138,236,34,49,183,233,29,51,30,91,80,152,48,100,6,100,46,139,156,189,149,175,8,192,104,
1,163,212,206,100,141,192,145,142,253,50,143,82,171,218,148,210,46,189,11,149,92,16,87,104,77,86,248,248,31,255,129,222,205,133,205,215,167,25,142,42,14,20,74,128,49,56,142,67,158,66,107,246,30,245,153,
41,70,253,75,54,87,190,103,253,217,19,206,47,78,241,125,143,40,244,24,166,25,89,158,227,251,1,228,14,218,11,249,232,63,255,13,81,181,196,241,225,1,135,59,155,220,156,159,209,187,62,35,8,20,38,19,244,186,
3,198,105,138,146,158,21,172,56,62,142,151,240,224,253,191,98,225,225,3,198,195,1,237,189,53,62,251,213,63,211,79,251,132,113,196,104,60,182,39,252,98,68,147,21,55,66,89,40,34,37,144,230,25,142,244,208,
64,150,217,131,18,153,125,32,146,91,184,67,102,50,75,177,45,124,31,185,177,214,181,168,58,201,233,238,6,127,248,248,215,52,39,203,248,161,102,156,142,200,82,83,224,184,29,27,159,117,125,180,95,38,174,
207,32,140,96,56,238,243,230,233,215,236,172,191,225,166,219,165,218,108,49,55,63,133,235,218,49,149,231,219,100,142,87,154,164,54,189,196,120,52,230,228,104,159,237,205,85,206,218,7,12,6,215,4,190,71,
28,135,144,167,24,229,88,176,95,16,224,120,62,113,115,158,233,251,111,225,74,201,101,251,152,151,95,127,194,202,243,239,169,76,77,224,200,220,198,81,115,11,21,69,216,148,30,100,228,197,67,29,114,92,63,
65,58,144,167,67,242,212,186,127,101,193,25,202,165,64,25,97,163,208,74,218,207,36,205,81,174,79,109,230,62,23,59,27,124,254,239,31,227,150,99,2,101,108,9,20,99,251,18,197,77,66,59,30,126,169,78,109,102,
1,145,229,156,119,246,120,252,217,39,236,109,173,146,229,41,205,169,105,146,36,68,42,23,207,241,240,226,8,47,76,184,255,222,135,76,52,167,232,158,95,176,245,250,21,27,111,94,114,121,126,194,168,127,137,
86,142,99,249,242,5,49,80,11,67,138,33,21,25,187,207,94,176,56,57,141,95,142,236,156,51,203,138,150,157,37,227,185,210,165,82,105,18,150,202,92,95,93,176,186,242,140,149,239,190,38,47,156,178,115,75,247,
8,42,49,134,28,215,117,9,163,50,113,92,33,153,154,230,188,127,201,249,209,33,163,222,21,187,111,94,208,109,183,137,194,18,19,115,51,182,238,45,44,1,174,92,170,224,6,49,65,101,138,110,38,56,61,220,98,237,
217,99,58,27,107,148,195,136,214,226,156,125,48,9,251,80,178,176,180,220,94,169,84,70,150,23,99,27,35,9,180,131,175,29,82,229,48,76,135,140,198,227,162,133,74,33,64,182,241,58,101,138,44,79,158,35,20,
188,121,241,28,39,79,89,94,94,180,69,157,212,70,53,13,121,193,34,147,184,158,45,88,165,6,174,207,143,173,172,99,229,25,73,16,80,111,205,81,107,213,112,29,15,81,8,154,131,48,196,143,42,132,149,38,39,237,
99,58,135,123,244,111,174,216,93,127,205,245,197,25,19,83,19,84,106,37,251,89,144,226,123,33,190,159,224,185,17,213,169,5,156,184,202,209,89,155,181,103,223,179,191,250,28,87,228,84,106,85,132,22,246,
101,137,93,80,171,98,246,122,171,98,51,72,210,44,39,144,242,206,189,41,140,45,92,153,60,199,228,118,6,41,148,66,43,131,36,47,198,23,41,185,16,120,174,199,202,179,239,232,157,93,178,244,96,1,37,50,70,195,
140,52,203,200,115,139,85,150,66,225,57,62,174,31,211,152,94,160,219,239,115,180,191,193,119,127,252,148,238,229,57,165,114,201,46,180,92,15,229,56,56,202,58,59,131,32,97,105,249,29,194,90,157,78,231,
144,189,141,215,116,79,143,184,58,57,4,153,227,121,145,205,62,143,70,22,18,230,250,184,174,131,231,70,60,122,255,199,212,38,39,56,105,31,177,185,182,194,238,155,103,164,253,43,92,63,38,151,14,227,116,
128,22,210,142,243,180,213,217,101,217,168,40,209,88,162,166,114,109,17,41,27,141,236,243,79,71,56,190,2,115,117,231,202,85,5,43,61,207,108,195,84,228,134,12,69,115,178,206,191,255,243,223,51,26,103,4,
97,66,58,30,163,36,228,185,221,26,229,89,102,13,94,174,71,115,238,1,247,223,123,143,209,160,203,246,234,11,222,60,127,194,40,29,146,68,17,65,20,146,229,216,69,164,182,89,121,63,40,241,131,159,254,53,97,
18,112,209,62,230,120,103,147,171,179,54,87,237,125,80,41,249,216,99,56,28,49,74,51,251,89,122,30,66,59,196,229,41,222,254,232,47,153,158,159,166,219,189,228,104,103,147,79,127,249,223,49,217,128,82,169,
76,106,10,41,251,173,238,163,96,4,228,38,103,156,203,162,113,107,245,165,121,110,15,66,23,221,11,194,208,35,205,178,98,253,149,23,74,76,123,64,203,242,49,169,178,116,82,164,203,245,89,155,173,87,207,153,
152,179,15,210,209,32,37,55,130,52,5,237,8,28,97,240,253,24,215,139,112,226,38,66,59,220,92,118,120,249,245,31,121,249,228,11,122,163,49,247,150,150,153,152,172,218,165,176,80,132,73,131,32,138,241,163,
22,173,133,101,198,131,27,14,183,214,216,94,123,201,121,251,128,139,243,142,181,96,69,85,124,215,126,63,131,48,193,243,3,132,23,83,158,184,199,236,242,3,204,120,204,217,241,33,95,252,251,191,178,181,190,
66,181,89,199,15,52,178,0,49,74,45,10,10,43,69,11,207,22,166,198,105,70,174,21,26,133,171,173,8,125,156,218,239,79,142,33,77,13,90,228,100,69,187,93,24,9,169,101,91,185,81,149,179,141,117,94,191,120,138,
87,43,65,158,146,231,197,212,65,42,164,85,134,225,6,1,113,185,206,204,253,247,241,133,66,230,35,158,127,254,41,171,171,47,64,194,212,244,20,110,16,88,145,146,163,9,146,152,48,174,48,247,232,125,26,245,
9,6,87,215,172,61,127,193,250,250,138,109,117,143,111,112,92,141,22,194,46,22,164,201,237,201,86,218,127,185,254,245,53,245,122,29,173,4,169,201,239,226,93,138,219,211,163,38,14,203,68,165,10,41,134,189,
221,13,158,127,249,21,140,71,52,107,13,102,150,44,33,210,100,54,10,25,71,53,130,184,76,220,154,228,170,223,165,125,116,192,205,117,155,189,141,53,46,142,142,241,221,128,233,133,89,148,171,17,185,192,143,
173,112,35,8,171,68,19,83,220,140,114,182,183,214,216,122,246,132,235,131,45,180,17,52,166,38,237,228,57,27,254,25,13,112,235,214,228,54,23,109,137,145,202,241,168,183,102,233,118,175,25,12,122,72,71,
33,196,144,116,60,188,171,141,11,97,147,42,82,216,33,71,38,12,105,110,57,53,193,68,243,110,196,116,71,78,148,138,140,12,229,104,92,47,68,59,30,189,238,21,79,190,249,134,173,151,47,136,67,143,230,68,157,
106,171,98,83,35,74,225,56,30,65,232,227,7,17,113,173,193,217,245,53,157,206,9,195,238,37,199,155,111,232,157,117,168,85,203,76,76,86,241,124,123,157,244,220,18,129,23,18,196,21,42,19,115,100,94,192,222,
209,46,207,191,253,134,110,123,23,145,246,9,170,53,92,223,35,199,70,86,179,113,175,232,26,200,63,251,123,132,29,97,9,33,241,194,132,56,41,51,28,244,25,231,41,158,200,25,10,139,160,48,185,53,68,25,20,153,
1,37,51,178,204,46,122,251,163,1,24,67,189,85,195,136,49,121,106,115,232,119,106,92,97,239,232,110,16,209,156,154,65,72,197,197,201,17,95,125,250,9,89,239,138,56,10,40,197,9,42,240,113,80,56,194,193,245,
35,28,47,96,118,254,62,165,70,147,246,217,41,237,163,93,110,78,79,184,58,58,100,156,245,81,94,136,144,138,52,179,241,199,64,217,135,115,156,216,74,127,210,108,208,57,235,240,226,233,99,142,54,95,225,171,
20,33,53,174,31,50,204,82,76,102,1,97,210,78,227,237,194,86,10,68,46,236,130,209,72,162,48,161,53,57,201,241,193,33,227,241,24,47,116,233,94,92,112,187,107,21,121,206,56,183,201,12,233,184,36,229,10,215,
231,103,72,3,251,155,107,244,251,150,68,153,14,237,45,74,144,218,135,183,176,54,41,165,93,220,160,194,253,247,222,195,113,28,118,55,95,242,229,103,191,71,107,67,18,7,144,10,134,153,149,199,107,169,112,
156,16,199,141,120,248,225,15,41,55,42,156,28,238,211,57,218,227,178,189,207,209,206,6,185,73,137,227,144,60,205,24,14,199,40,173,209,110,136,212,14,97,169,201,95,252,213,79,73,106,85,206,59,39,108,173,
191,226,205,179,175,201,178,30,126,16,49,206,44,126,220,122,139,139,151,158,200,145,114,108,83,109,66,145,166,41,8,77,185,80,7,246,187,215,148,146,216,62,148,50,43,33,178,47,122,59,210,204,114,27,217,
149,153,195,32,55,192,128,246,225,14,94,224,34,76,198,56,181,242,21,3,72,237,20,237,112,219,31,241,146,6,218,139,200,179,17,219,43,223,243,221,87,95,48,206,114,150,30,60,96,170,89,197,209,118,76,235,134,
9,126,224,227,70,53,90,75,111,161,133,225,228,248,136,189,173,117,46,58,109,78,79,142,209,174,166,82,173,216,78,64,46,136,74,21,220,32,64,59,49,165,137,37,234,83,51,100,195,62,71,155,235,60,253,226,143,
236,110,190,192,143,75,68,113,84,196,87,111,3,31,220,193,208,12,185,61,221,27,203,210,10,66,235,114,32,237,99,164,66,187,30,233,160,143,73,51,132,49,152,84,98,200,72,133,180,216,24,33,200,114,73,255,230,
146,203,195,3,84,232,216,176,129,200,209,202,88,216,163,177,60,126,229,132,214,51,50,123,143,36,46,147,246,111,120,246,249,39,124,253,213,31,16,158,160,85,111,22,162,32,208,142,131,31,68,56,94,200,244,
242,187,76,78,205,99,70,35,14,182,182,216,217,90,227,178,115,72,191,123,142,23,135,132,65,132,150,70,88,167,165,80,54,115,43,44,159,92,80,188,253,71,197,15,184,176,87,26,129,193,17,26,223,245,9,43,37,
134,58,103,125,245,37,207,190,248,19,202,228,52,39,90,44,44,206,130,118,236,175,33,21,65,16,17,198,85,42,205,105,110,242,140,211,147,35,110,46,58,108,189,121,193,197,254,49,90,57,204,47,223,167,84,43,
219,127,190,86,196,73,108,227,154,141,105,174,6,3,182,55,214,249,238,171,63,145,159,117,240,117,78,125,106,1,55,137,24,12,71,104,101,185,43,82,106,164,178,204,8,171,178,51,56,210,144,1,233,104,200,217,
233,57,247,222,126,151,118,231,128,254,69,7,71,10,6,3,195,104,156,22,196,200,226,63,133,177,70,23,218,179,91,124,175,201,109,89,11,73,241,7,164,112,149,34,246,75,36,165,6,151,189,46,79,31,127,197,214,
171,21,202,97,196,220,220,52,165,70,66,154,74,76,110,155,176,113,165,66,148,84,168,77,206,115,118,125,67,247,252,130,254,229,57,219,175,158,115,209,62,34,42,151,153,156,152,32,10,34,4,18,223,245,9,226,
136,48,44,211,152,93,102,32,4,187,187,91,60,255,250,107,142,183,215,137,189,148,48,170,80,170,84,44,220,73,41,148,54,48,182,16,53,138,133,172,77,36,73,203,25,202,12,199,199,135,56,58,98,254,225,187,28,
110,173,210,191,60,197,40,137,209,194,154,141,242,140,44,27,34,177,12,254,44,77,49,38,39,179,79,48,123,154,55,153,61,233,74,187,140,148,69,239,33,137,42,52,39,102,136,42,13,246,118,215,249,143,95,127,
140,25,143,73,146,18,165,114,108,185,63,6,148,171,112,3,219,2,156,152,89,162,54,51,207,249,249,57,221,171,75,206,14,247,184,56,58,160,219,237,17,36,46,158,235,48,26,91,4,135,231,7,120,142,79,169,90,231,
221,31,253,148,160,92,225,240,112,151,175,255,248,41,71,219,155,248,121,143,212,247,80,126,76,106,122,40,71,225,9,167,112,35,219,7,154,5,168,73,228,45,183,60,207,184,236,28,19,71,37,254,242,111,254,134,
181,103,47,233,156,236,163,132,66,186,129,61,24,8,155,106,202,141,101,75,141,70,3,219,176,53,41,89,110,179,213,119,138,201,130,82,154,35,108,83,221,15,8,226,50,15,63,250,17,94,160,216,89,127,206,231,191,
251,13,129,163,240,148,157,5,231,183,59,23,97,64,57,120,126,194,242,7,63,98,230,222,50,221,203,14,237,131,125,142,15,119,105,239,188,34,205,70,248,97,132,64,208,29,140,172,161,205,15,81,174,79,117,114,
137,15,126,252,87,4,190,226,172,115,200,218,203,239,89,249,254,107,242,81,151,48,8,241,125,43,238,185,203,218,155,162,14,107,140,125,216,27,59,187,183,179,234,49,71,187,219,44,127,248,83,202,181,38,107,
175,86,72,34,223,74,210,129,60,235,217,195,129,41,48,20,74,22,55,108,201,160,223,195,241,3,100,94,40,23,139,23,89,58,78,17,210,242,139,220,40,198,15,27,148,90,11,140,7,93,94,252,225,51,30,127,241,71,188,
208,229,222,220,34,149,82,92,76,32,52,190,31,18,199,33,210,171,208,156,123,132,16,112,176,181,193,250,171,167,116,246,54,233,156,28,34,28,77,171,217,192,115,181,117,82,199,9,129,31,160,189,132,218,204,
125,226,114,157,116,56,226,104,99,131,47,63,249,15,206,142,55,8,195,136,82,37,190,179,231,33,76,225,203,176,59,74,155,109,200,238,88,75,96,232,28,238,51,251,246,15,8,157,42,55,167,39,228,166,135,235,249,
72,6,244,7,67,82,99,151,216,38,29,217,112,139,210,100,100,244,187,87,128,193,21,197,104,204,152,59,75,159,245,125,251,248,97,76,99,246,1,141,137,5,242,97,143,111,127,253,11,190,252,234,51,130,216,167,
209,168,224,184,126,65,197,5,47,136,8,226,50,211,203,239,51,53,183,4,227,49,59,175,86,120,245,252,9,71,123,107,244,251,231,184,190,79,228,107,114,51,66,253,207,255,211,255,242,183,38,207,138,40,86,118,
199,31,201,76,161,15,44,72,112,200,63,191,249,28,229,80,173,77,16,212,170,236,31,238,241,221,231,159,99,198,99,230,103,102,152,158,157,68,123,22,36,37,148,32,12,99,162,184,76,185,57,69,170,37,231,157,
35,122,87,103,108,190,122,206,233,254,1,90,56,44,222,187,71,165,105,31,246,158,235,17,198,37,202,229,9,194,218,4,55,195,62,135,123,59,108,175,189,98,116,214,65,229,57,165,74,157,250,252,108,161,37,203,
209,18,91,80,208,78,241,90,182,41,28,89,164,207,77,129,121,189,56,59,69,231,138,229,247,127,64,106,4,233,56,197,228,150,104,104,111,167,217,221,232,227,182,38,109,255,151,149,31,43,89,144,243,44,159,0,
37,53,65,24,83,106,76,33,253,128,175,191,252,140,221,215,171,52,147,128,197,165,25,202,245,26,105,17,237,243,92,143,56,74,136,194,152,74,107,142,238,40,227,234,180,205,176,119,197,198,139,239,57,59,62,
198,241,92,38,167,167,72,202,101,148,148,68,65,68,16,149,136,226,42,213,201,121,6,185,228,248,228,144,141,55,175,57,216,88,229,242,236,20,87,187,204,204,205,217,86,169,201,209,90,145,141,71,40,97,225,
78,66,106,203,241,46,8,137,118,4,101,191,108,157,163,83,154,147,83,204,220,91,102,56,24,145,165,67,251,255,97,227,169,86,66,147,221,217,144,76,158,89,169,196,109,186,69,112,55,207,20,216,253,79,224,39,
212,234,77,166,22,150,232,156,29,243,201,175,126,65,62,232,82,77,34,226,36,177,120,227,2,225,236,106,151,48,74,168,212,167,89,120,240,22,221,225,128,155,171,115,206,79,118,217,125,179,66,247,230,18,29,
4,132,65,68,110,36,74,8,66,63,192,243,34,170,141,105,30,189,255,17,78,20,208,57,235,240,252,187,175,185,108,239,35,198,125,242,60,39,74,42,54,26,234,104,198,227,180,200,163,219,93,136,42,22,245,118,111,
147,223,37,193,16,134,243,179,54,72,201,135,63,249,75,4,146,94,175,103,113,210,202,202,114,132,146,5,94,218,48,30,13,201,178,20,33,4,90,107,148,182,126,97,187,73,42,88,61,66,161,148,198,11,19,166,22,223,
98,249,237,135,108,188,121,202,147,47,255,128,54,99,60,173,24,141,51,114,164,77,251,228,57,218,241,240,252,132,249,71,31,112,239,189,247,233,119,111,216,221,122,195,209,222,38,103,123,155,12,134,215,68,
65,72,224,5,12,135,169,29,175,186,30,174,27,81,159,92,224,237,143,126,66,20,121,156,182,15,89,125,249,148,205,149,231,244,47,58,246,175,241,253,130,150,106,31,244,183,55,62,123,40,176,11,126,97,84,113,
89,179,55,68,41,37,39,59,123,148,39,231,89,92,94,198,100,25,233,104,100,81,99,82,218,207,160,104,214,218,243,82,86,28,52,76,81,130,51,5,129,242,150,215,99,159,37,142,23,81,105,76,209,88,120,11,45,114,
94,126,243,71,94,124,247,21,126,228,51,61,51,129,235,88,176,159,16,25,174,235,17,68,101,148,87,166,62,187,12,70,208,191,62,103,237,249,99,142,118,54,57,109,31,131,130,102,171,73,18,248,8,169,8,226,132,
32,76,112,188,152,202,228,2,229,70,11,210,148,139,227,125,94,124,247,21,157,163,29,180,132,218,68,211,126,183,133,44,104,160,246,207,77,160,172,38,18,203,207,185,109,44,230,198,70,121,183,215,214,9,155,
147,212,234,13,242,113,102,137,160,198,198,62,243,236,54,24,66,49,247,23,228,194,216,200,59,20,159,75,126,231,98,182,241,1,129,19,132,212,166,230,184,255,222,143,72,175,47,249,238,183,191,230,241,55,127,
160,220,40,83,169,148,236,83,190,112,87,251,81,136,27,148,169,78,46,50,119,255,33,10,201,197,225,33,79,191,254,146,131,253,13,186,189,51,92,215,165,92,42,217,177,179,235,163,254,215,255,242,95,255,214,
144,145,166,163,130,253,109,151,20,89,102,69,216,80,108,153,11,102,139,64,224,123,33,181,137,25,122,163,62,143,63,255,132,225,213,53,247,102,102,153,152,154,0,97,147,45,174,163,113,61,135,36,174,16,85,
26,232,114,149,78,231,152,139,246,1,43,223,127,203,201,214,14,26,151,133,123,247,105,78,79,96,242,20,215,245,73,146,42,165,114,131,184,53,207,245,120,196,89,231,132,203,206,41,199,155,27,152,65,31,207,
243,153,127,235,161,149,96,8,83,44,33,149,109,157,106,101,75,45,210,86,207,69,49,98,144,194,86,228,115,105,56,216,223,163,18,38,204,191,245,54,58,138,25,15,135,119,127,56,194,26,66,138,188,237,173,248,
192,20,51,202,188,72,37,217,207,33,207,45,37,175,84,105,16,55,90,124,255,253,99,94,127,255,45,173,106,137,197,123,51,248,81,136,73,115,180,18,104,45,8,66,159,40,42,81,105,206,50,66,114,122,114,194,229,
217,49,171,79,159,112,184,179,129,31,4,204,206,207,82,170,85,80,66,17,135,209,159,95,150,19,115,164,218,229,226,226,140,171,243,83,54,86,87,216,221,222,64,25,193,242,195,37,188,48,176,185,91,45,10,144,
147,40,180,133,150,17,34,239,12,96,133,104,217,88,196,176,80,134,173,55,171,204,47,46,50,113,239,1,198,8,134,131,62,198,20,121,245,226,97,152,165,195,2,186,102,243,203,133,207,173,0,113,221,38,157,236,
136,43,142,202,204,222,123,139,177,200,249,244,215,255,194,224,234,156,74,185,66,20,69,104,101,211,35,66,56,40,20,97,28,83,170,180,184,247,214,123,140,140,161,125,120,200,241,238,58,155,47,191,231,250,
162,141,116,92,170,149,42,90,7,228,25,4,65,132,27,4,148,26,147,188,251,195,159,224,70,1,23,231,151,28,28,236,115,113,188,131,24,93,35,138,5,170,41,240,191,66,40,164,114,240,3,223,202,199,243,220,162,142,
139,52,151,49,249,221,36,202,228,96,132,225,236,240,0,237,123,252,232,167,255,3,218,247,233,247,187,246,1,153,219,84,80,158,167,32,10,138,162,177,82,249,44,203,139,120,174,177,11,90,4,178,64,245,186,158,
79,92,153,226,199,127,253,215,220,156,31,240,251,127,251,5,233,176,143,148,144,166,22,189,107,127,169,12,71,59,196,229,6,141,233,123,188,253,209,143,49,228,236,111,173,113,188,183,198,222,218,27,110,122,
215,184,94,64,236,187,140,210,28,233,8,92,47,192,113,124,234,147,75,188,255,151,252,218,137,14,0,0,32,0,73,68,65,84,255,9,71,43,206,79,59,172,60,125,194,241,238,38,215,167,123,184,158,75,16,39,197,139,
59,183,249,115,105,81,35,70,106,251,10,52,185,93,240,231,185,77,223,20,152,72,41,20,90,228,172,175,188,98,254,209,59,76,207,47,96,164,178,13,229,226,6,131,177,163,50,138,159,7,237,56,5,138,193,20,135,
1,203,213,55,8,156,66,23,24,151,170,212,231,30,48,181,176,200,203,63,254,134,199,95,124,74,173,81,97,162,86,195,8,129,35,181,13,69,220,45,92,99,234,115,111,17,148,106,164,253,107,54,86,158,178,249,230,
57,199,135,187,0,180,90,45,226,200,181,13,230,48,38,8,75,4,81,149,82,107,30,233,4,100,227,140,206,193,22,107,43,207,216,93,125,65,58,26,82,107,54,240,124,133,148,10,41,84,193,253,81,69,161,74,34,237,12,
155,188,120,44,155,188,24,228,99,200,211,33,235,43,107,204,189,243,46,213,90,157,113,154,218,249,126,102,71,63,121,102,63,71,99,110,93,219,242,110,252,105,81,47,5,141,85,64,158,217,5,118,88,154,96,233,
253,31,83,79,202,124,243,203,159,241,253,183,95,209,154,159,32,78,98,11,44,44,52,155,202,241,240,130,132,234,212,34,179,11,15,144,70,48,238,221,240,253,231,159,179,177,254,130,155,110,7,229,58,84,171,
37,251,123,209,30,97,28,163,254,183,255,242,95,255,86,146,91,118,72,58,46,78,186,69,108,77,252,89,5,104,27,150,54,203,94,169,182,16,190,203,87,159,127,194,232,252,134,7,203,247,169,212,43,140,114,67,90,
100,117,3,215,37,240,34,146,106,11,21,151,56,60,57,228,226,100,151,87,79,31,115,186,127,128,231,250,220,127,184,76,107,166,69,150,165,104,229,81,46,87,40,85,91,36,173,41,174,135,61,218,135,7,156,157,156,
208,217,223,229,186,125,130,163,4,179,139,115,232,192,199,164,118,176,122,123,138,66,22,38,122,161,80,218,189,243,88,202,162,77,106,31,232,22,229,187,250,226,21,243,51,115,212,167,102,136,42,53,178,116,
76,158,142,144,202,158,92,173,14,176,0,131,155,220,190,229,133,99,79,140,82,222,141,125,226,40,166,54,57,203,235,205,53,158,127,245,53,179,205,38,243,11,211,72,45,10,140,129,237,1,184,142,67,28,151,137,
43,45,50,199,167,115,116,66,251,248,144,87,79,191,230,244,240,8,199,243,89,152,159,165,86,175,20,62,0,143,184,146,224,135,117,170,83,75,140,128,238,213,37,55,87,167,108,111,172,178,242,228,9,90,192,91,
143,150,41,87,203,128,198,13,44,8,75,75,109,31,102,66,88,55,175,227,88,89,123,58,42,132,230,150,135,47,138,91,143,32,227,112,111,143,233,153,57,42,205,41,252,168,196,168,119,131,200,179,162,179,144,147,
165,197,117,214,216,211,158,49,134,108,60,42,190,2,226,110,71,224,58,154,198,196,2,94,37,230,215,255,252,223,232,93,92,208,168,215,112,61,183,64,47,91,143,162,148,18,215,115,9,147,42,243,203,111,49,150,
138,243,211,19,214,87,190,103,243,249,19,122,221,75,60,63,38,42,149,65,121,152,52,195,241,93,188,48,162,218,152,96,249,253,31,34,124,159,238,229,13,7,187,27,92,156,236,211,61,59,68,11,112,220,16,83,96,
80,131,56,177,35,57,41,139,223,195,109,82,70,219,47,92,113,125,55,198,82,39,115,105,238,22,145,151,103,29,140,144,44,62,120,72,163,209,164,215,27,216,230,181,178,173,5,147,223,186,128,13,74,75,68,102,
112,61,23,117,251,107,147,163,93,203,5,242,195,132,247,126,248,151,220,92,30,242,219,159,255,12,51,30,227,250,1,169,41,94,149,166,8,65,56,14,165,74,131,198,204,18,15,63,248,1,72,56,61,217,103,253,197,
55,28,110,189,161,63,232,18,68,101,202,165,136,209,200,254,124,57,94,132,235,134,180,38,151,121,251,71,127,9,142,230,236,228,144,141,87,47,233,116,14,25,92,158,224,40,69,152,84,72,199,121,49,250,148,86,
22,132,44,22,145,246,214,170,149,46,140,86,86,242,33,238,248,122,214,220,37,197,136,221,141,45,234,19,51,76,78,207,218,49,175,0,169,204,157,248,222,220,77,69,229,29,19,82,144,91,43,89,65,221,180,253,0,
143,242,196,34,51,139,15,120,254,233,175,249,246,171,47,104,78,212,136,67,159,113,150,22,47,8,27,253,244,195,8,47,44,81,153,90,38,174,77,144,103,67,14,214,223,240,250,197,99,142,247,247,144,174,102,102,
118,154,114,24,64,241,215,7,73,5,63,172,81,153,94,192,15,75,72,33,56,221,221,224,245,203,167,28,108,189,97,216,239,82,159,108,21,52,73,139,84,86,183,101,169,98,215,67,113,187,201,139,226,167,45,147,101,
197,33,33,71,57,14,102,216,227,233,55,223,83,95,92,160,86,111,97,80,152,52,39,203,198,228,70,20,178,153,219,131,180,41,36,242,246,115,202,236,137,212,246,73,132,66,249,33,243,143,62,160,81,41,243,205,
47,254,137,55,107,43,84,155,37,180,35,73,139,20,157,80,246,128,225,135,101,146,234,4,15,63,250,79,36,126,200,232,250,154,87,95,127,201,171,23,143,185,184,60,33,136,60,170,229,146,253,61,104,141,23,197,
68,81,5,245,191,255,31,255,231,223,166,163,30,202,24,132,118,172,29,42,203,45,218,84,137,66,237,37,139,83,34,56,74,147,84,43,124,255,228,91,250,167,151,44,63,184,135,27,122,246,13,40,20,142,163,113,181,
194,213,14,73,169,142,136,34,174,111,174,185,60,109,243,252,219,111,56,221,219,37,112,60,22,23,151,152,156,157,188,3,19,197,81,133,56,169,82,106,206,48,200,115,206,59,199,92,93,93,210,222,223,227,108,
111,19,145,166,204,45,204,18,150,18,59,202,185,21,152,23,188,27,235,37,176,15,56,223,213,5,123,107,100,151,185,133,152,216,22,107,5,70,75,118,214,214,153,155,155,195,77,42,120,97,136,86,154,44,29,217,
91,204,221,6,210,220,45,115,111,161,194,82,81,168,137,13,229,106,131,246,117,151,199,159,127,206,252,228,36,173,169,26,152,204,62,4,132,194,209,10,165,173,233,42,41,181,24,203,144,235,110,151,179,206,
33,175,159,60,230,226,180,77,24,4,44,46,46,80,174,196,56,90,225,56,1,97,28,227,199,21,170,19,179,12,165,166,123,117,201,96,216,227,245,202,11,30,127,249,21,249,160,207,242,210,2,211,115,147,128,198,113,
125,92,247,207,12,75,41,108,19,80,57,174,141,147,25,251,16,202,11,197,97,110,138,107,53,160,180,96,212,239,51,232,94,82,111,78,224,6,9,97,82,38,77,115,204,104,132,42,36,232,38,203,172,20,68,105,187,11,
200,111,193,115,5,175,62,79,113,221,136,198,204,44,191,254,197,207,25,223,92,51,209,170,35,149,87,156,112,108,155,89,169,98,166,29,196,180,102,22,81,190,207,96,56,100,111,227,181,245,173,146,227,123,46,
113,82,70,40,107,34,210,142,69,72,84,107,45,30,190,247,33,202,143,232,95,95,115,117,125,78,231,112,155,206,222,54,102,60,46,100,44,250,238,65,236,186,62,217,104,100,29,173,5,23,95,20,130,119,199,241,236,
146,44,151,40,105,44,109,181,120,192,140,70,99,164,128,110,247,10,237,186,84,27,45,42,141,38,105,38,25,14,122,144,141,109,26,204,136,130,10,105,53,138,185,40,172,89,153,197,228,42,199,65,107,135,218,212,
34,81,164,248,228,87,255,134,31,132,197,129,160,184,45,22,184,92,79,41,124,47,196,9,98,38,231,150,81,158,143,38,103,253,217,151,108,172,174,32,204,136,168,136,173,102,105,138,18,10,215,117,113,253,152,
114,109,158,247,126,242,83,164,163,184,58,63,101,109,229,57,167,167,199,92,157,238,32,178,140,176,84,33,43,216,119,82,137,162,161,74,81,184,179,15,102,33,40,10,84,214,234,100,253,173,110,97,14,181,41,
38,237,122,144,141,57,218,223,161,210,154,34,174,214,41,149,203,12,122,61,140,49,104,199,82,215,148,177,153,115,43,38,114,239,26,235,226,86,12,110,12,110,144,48,187,252,62,111,30,255,145,151,223,127,75,
163,85,198,115,5,163,98,9,44,176,251,12,169,28,130,168,66,92,157,38,168,205,90,76,193,77,135,239,62,251,29,7,251,59,160,52,179,179,179,84,42,9,194,100,120,126,72,24,151,112,252,18,181,233,101,148,114,
64,73,46,79,246,88,91,121,78,251,112,135,238,85,135,82,163,73,18,135,214,113,172,148,21,179,8,64,232,34,206,157,33,149,192,245,60,155,108,43,122,26,153,201,72,17,133,239,25,60,47,224,226,240,144,215,175,
223,208,92,92,164,92,169,227,121,62,227,209,240,238,48,100,176,180,222,52,79,139,155,2,197,247,79,254,121,111,136,36,169,79,112,111,249,109,190,253,229,47,217,218,219,32,46,7,8,97,133,68,38,203,201,132,
213,186,250,94,68,92,170,49,243,232,125,66,47,66,105,201,197,222,14,95,126,250,91,218,23,135,68,161,71,173,94,69,8,235,122,190,237,61,213,230,150,81,255,215,255,253,255,252,173,86,14,249,168,143,150,210,
106,3,243,172,208,150,221,18,226,204,221,44,79,74,197,73,167,67,222,31,48,61,59,85,120,31,109,138,199,2,132,20,74,74,146,114,133,184,92,163,151,166,156,158,181,249,234,147,79,185,233,116,136,131,50,111,
61,122,64,125,186,201,109,180,38,12,42,148,43,85,170,19,179,92,103,41,103,199,7,244,186,87,236,111,172,211,222,221,64,229,48,51,53,67,105,162,201,56,43,96,69,66,222,141,154,164,46,150,147,57,68,65,132,
87,188,181,101,161,95,179,38,163,226,193,111,4,97,24,49,28,13,217,122,179,74,165,90,37,44,87,41,213,154,40,71,99,70,3,180,16,197,73,214,190,252,12,170,72,93,20,239,64,44,95,100,144,230,172,191,94,99,113,
110,154,176,228,161,141,45,146,128,205,149,75,161,112,60,143,164,92,71,70,117,70,5,116,237,171,207,62,97,212,189,38,138,99,102,103,167,169,212,42,182,248,165,28,130,48,177,208,168,137,69,198,202,177,115,
254,254,53,155,27,175,249,234,179,63,50,238,117,121,244,96,145,197,165,73,12,22,248,37,72,145,183,125,218,98,193,100,114,251,235,57,142,131,231,74,28,173,139,145,68,134,200,237,215,28,108,214,219,113,
28,187,227,184,60,101,52,6,63,42,81,107,78,49,6,134,195,30,162,104,227,98,82,251,136,80,5,219,232,118,247,99,108,133,237,255,103,234,205,126,45,59,178,244,190,95,68,236,121,159,249,206,247,230,60,48,147,
89,85,172,42,85,151,37,183,108,65,176,12,52,108,235,69,134,13,91,128,13,248,209,16,224,23,1,182,223,12,250,209,255,134,97,192,22,44,181,172,238,106,73,173,238,46,117,13,93,197,34,155,83,146,73,102,146,
204,100,50,147,57,222,233,220,51,239,33,34,252,176,226,92,54,1,130,36,152,153,247,222,179,99,71,172,88,235,251,126,95,222,27,240,249,39,119,73,181,162,236,118,132,109,163,53,90,73,128,136,156,184,17,89,
218,97,180,181,71,119,123,31,107,27,190,249,242,30,31,191,247,14,157,50,161,76,19,178,52,71,71,81,184,165,200,28,104,48,218,230,141,31,253,20,29,71,44,166,103,188,124,246,53,247,62,124,143,241,243,135,
248,166,38,41,50,76,156,210,54,130,207,80,26,108,227,80,106,221,106,145,88,190,72,41,226,40,150,16,10,223,134,37,104,136,179,130,209,230,6,245,114,129,54,113,80,229,180,76,78,143,56,124,61,166,24,12,57,
184,116,133,44,79,57,59,58,197,54,33,26,211,55,82,33,159,191,43,130,225,86,225,182,24,197,57,27,91,35,238,190,247,46,69,145,133,20,37,119,190,249,154,96,98,53,81,66,20,165,236,92,253,30,131,189,125,138,
50,227,179,15,127,195,39,31,221,165,40,19,114,19,163,128,170,170,72,117,76,20,199,164,105,201,96,235,18,63,248,59,127,151,40,209,156,28,189,228,179,143,222,229,245,171,39,52,179,87,184,106,69,209,223,
8,131,88,169,12,9,32,53,66,110,174,10,89,193,198,68,100,121,78,146,102,196,73,114,30,130,178,206,41,94,223,100,210,36,198,54,43,190,188,247,33,181,78,233,111,238,48,216,220,10,3,92,49,251,57,56,15,143,
209,74,7,241,128,124,46,132,119,55,43,7,140,95,62,227,245,243,111,40,186,89,184,149,73,10,27,90,50,176,85,20,209,233,13,40,251,219,164,189,109,178,222,0,99,167,252,226,143,254,144,111,95,124,77,154,164,
92,186,176,43,45,25,87,19,167,226,188,205,138,77,54,46,223,166,63,220,196,224,121,249,205,151,220,251,224,93,94,190,120,204,242,236,144,222,104,139,225,198,40,12,154,9,185,190,242,61,59,11,214,138,222,
30,109,4,33,237,99,193,179,56,249,255,206,27,148,55,216,86,170,245,188,147,113,248,236,25,31,189,247,30,217,198,136,225,206,54,157,206,0,215,180,242,243,132,89,163,181,150,117,172,180,214,193,228,233,
45,88,208,81,194,206,193,5,30,190,251,46,39,211,99,226,34,193,43,104,218,70,110,167,74,232,197,81,218,37,43,122,236,94,255,62,195,141,61,138,162,100,252,237,99,126,254,179,127,193,201,228,37,163,205,33,
253,78,143,214,105,26,167,201,58,5,69,103,192,193,205,31,112,253,205,31,96,254,201,255,244,79,223,206,138,146,40,73,104,22,51,121,40,78,74,104,227,245,185,213,122,93,229,186,144,108,223,237,116,2,63,66,
30,16,40,9,21,81,138,60,73,233,13,55,113,113,202,203,215,175,184,251,215,191,99,114,244,154,110,103,200,27,183,110,208,223,234,135,138,83,44,227,121,41,129,194,62,203,56,62,121,205,248,248,53,95,126,254,
25,227,167,95,99,44,108,110,236,178,117,249,34,206,24,90,215,18,155,56,0,176,130,124,74,25,209,151,42,197,198,214,30,101,111,20,36,137,16,233,24,71,35,125,75,45,174,98,111,61,89,150,178,156,79,89,44,166,
232,40,33,45,123,228,69,151,172,40,104,151,115,169,4,149,196,220,105,100,144,169,180,252,51,10,85,74,93,55,20,69,76,100,52,216,246,187,129,143,214,196,81,140,137,20,101,49,36,235,110,81,105,205,203,151,
223,242,225,59,191,193,47,231,244,203,14,7,151,14,200,139,156,72,11,219,60,203,10,242,238,144,254,206,1,42,205,89,206,166,204,23,51,238,63,184,207,135,239,252,142,122,49,231,194,193,46,111,220,190,38,
73,85,42,146,104,199,117,112,117,100,193,155,192,244,240,36,89,135,237,221,75,161,23,43,55,48,141,167,109,45,81,224,127,56,247,93,168,119,28,27,78,38,103,248,86,147,247,122,140,118,247,80,218,176,92,44,
176,78,218,125,104,45,106,157,182,69,35,235,68,121,209,107,175,150,43,124,219,146,197,209,121,104,70,167,95,82,87,21,202,57,140,142,136,147,148,222,96,147,221,203,55,80,113,204,55,79,190,228,195,223,252,
154,78,102,72,76,68,154,119,49,113,6,222,18,69,17,73,154,211,27,109,113,245,141,239,83,116,59,140,143,95,243,226,249,99,190,188,127,143,241,139,111,168,151,11,210,180,36,235,14,136,179,28,215,182,161,
90,213,33,183,85,214,45,193,57,92,150,125,118,15,174,209,54,98,254,241,174,13,73,107,9,171,213,146,170,105,136,34,193,42,219,214,209,233,150,36,177,229,229,203,35,134,27,35,134,155,59,116,7,67,78,15,143,
104,218,38,108,98,235,76,1,39,114,95,183,142,255,51,164,101,193,116,124,42,253,90,13,174,109,165,106,14,18,60,29,252,35,73,192,215,30,188,249,22,89,158,242,228,254,135,124,252,215,239,146,231,49,221,56,
194,89,79,107,21,218,196,36,113,74,156,231,20,253,45,238,252,222,223,161,232,150,156,158,158,240,248,139,79,120,241,228,27,92,117,6,182,10,244,200,24,219,186,243,248,79,165,180,180,26,149,120,17,52,18,
15,218,29,108,208,29,110,201,65,164,37,170,79,171,245,65,175,209,177,200,88,77,8,140,119,174,225,233,227,135,44,173,161,187,177,65,167,63,64,121,79,91,175,100,243,246,54,184,181,69,0,224,145,16,34,148,
152,183,234,70,6,244,4,76,183,14,10,25,57,156,53,81,44,3,253,188,51,98,116,112,131,44,239,16,235,134,247,254,252,95,243,228,201,35,226,52,101,127,119,147,56,10,110,216,40,165,40,75,178,124,192,240,226,
45,58,253,1,182,173,121,249,228,75,238,125,252,30,199,175,94,178,156,158,82,244,71,12,135,67,129,36,106,233,221,175,219,76,206,169,144,15,32,134,205,188,51,34,203,251,33,13,77,14,45,231,60,214,90,249,
27,49,238,69,81,66,146,68,76,142,94,243,252,233,51,210,141,77,250,253,1,121,183,135,107,45,46,232,122,173,179,96,197,243,34,209,141,210,218,113,129,180,186,156,76,152,207,103,168,44,19,87,175,111,2,10,
69,5,20,118,70,81,14,24,237,93,230,194,205,239,145,229,25,139,163,23,252,250,223,252,140,215,71,207,24,142,122,100,73,42,200,143,48,91,233,244,70,108,95,188,193,205,31,252,136,60,78,48,255,253,127,243,
63,188,157,149,5,89,167,79,90,20,212,171,5,42,132,132,104,44,38,12,180,36,100,99,125,210,27,25,60,132,161,158,49,234,188,93,98,140,97,56,216,36,27,140,120,250,250,57,127,253,235,95,50,126,125,72,191,236,
115,251,141,235,116,71,93,92,35,108,137,36,149,65,102,127,115,55,196,247,29,243,234,219,167,60,250,226,51,38,223,62,5,219,178,189,181,195,254,205,171,52,202,211,86,210,162,49,58,10,137,244,230,124,195,
87,129,69,61,95,46,216,222,58,96,231,202,53,234,186,194,232,144,10,164,12,62,196,28,122,47,67,229,40,54,180,245,146,214,86,120,231,41,187,61,146,178,75,222,233,179,88,45,194,96,69,210,144,214,10,37,19,
94,110,188,28,126,90,155,112,53,150,62,165,82,46,84,145,130,42,30,108,93,64,119,251,124,254,249,61,222,251,245,175,176,179,41,91,163,1,251,151,246,200,242,4,148,112,85,138,50,39,45,123,108,236,94,128,
172,224,248,232,53,147,211,83,30,126,245,57,247,63,254,136,249,120,194,193,222,14,63,248,193,237,192,145,137,136,98,33,102,74,96,67,43,44,15,165,3,247,95,177,90,214,40,149,112,227,251,191,135,247,145,
184,249,2,163,220,59,104,219,38,180,119,196,240,97,219,134,225,176,100,58,95,226,67,112,194,112,99,155,172,232,50,157,76,176,56,156,147,150,135,183,50,231,176,118,173,232,210,18,155,168,100,152,174,35,
131,183,208,172,150,129,206,169,80,81,76,86,244,184,122,251,45,76,167,228,163,15,222,225,227,223,254,21,169,105,25,246,135,164,113,74,235,108,0,146,69,164,89,135,162,236,115,227,205,31,210,223,220,102,
58,62,226,197,243,167,60,126,248,5,135,47,190,161,94,205,72,203,1,189,254,48,204,115,164,157,66,48,127,41,101,130,161,78,214,170,86,154,166,174,200,242,156,183,254,246,239,211,212,142,249,108,33,113,141,
85,69,181,146,1,126,91,215,204,230,21,81,20,97,155,150,162,204,80,118,197,201,233,4,147,102,116,250,35,182,15,46,50,62,60,166,94,45,69,60,160,180,28,130,74,5,116,71,96,19,69,134,56,78,176,117,37,70,62,
31,212,78,74,28,170,42,50,164,105,66,119,184,195,143,254,238,63,0,95,241,249,199,239,240,241,239,126,67,26,107,186,101,9,218,208,84,53,58,18,174,81,154,22,244,54,119,184,243,123,255,49,229,176,199,108,
114,202,147,7,247,120,250,248,33,167,175,190,193,55,45,69,167,36,142,82,218,182,65,235,56,28,44,90,224,114,113,28,90,54,146,133,171,148,161,106,106,246,175,221,100,103,239,2,213,82,124,45,73,146,200,175,
13,239,23,74,120,81,73,18,99,157,226,244,248,152,71,143,30,179,177,191,71,22,137,47,33,77,114,218,186,22,214,128,92,168,131,156,59,24,250,66,219,218,182,77,96,229,139,41,82,107,31,102,6,162,120,202,243,
156,178,187,193,198,133,27,12,54,182,24,31,62,227,175,254,237,255,199,215,143,190,164,219,205,57,216,217,192,185,6,109,98,140,73,40,251,27,20,221,33,131,131,27,20,189,62,182,169,56,252,250,43,62,255,228,
3,94,124,251,136,122,57,163,236,245,217,218,217,11,98,15,69,20,199,66,176,52,114,240,41,183,118,26,203,129,183,90,86,244,182,47,178,177,181,75,179,92,137,16,32,18,50,102,211,52,184,243,126,140,37,207,
115,104,28,211,211,51,230,211,9,163,11,151,72,146,148,78,127,32,170,45,231,67,75,181,13,248,150,112,51,246,234,220,36,89,215,117,240,135,72,182,136,38,4,197,107,1,231,229,221,77,118,47,95,227,242,173,
31,146,152,136,151,95,61,224,223,253,243,255,139,215,167,47,24,13,123,232,40,194,41,79,28,101,152,36,165,236,141,216,190,112,149,27,63,252,61,114,157,208,212,13,230,251,55,222,124,59,15,138,144,188,219,
35,42,10,154,229,2,109,91,12,22,231,91,156,247,196,90,174,215,54,144,243,252,58,157,93,7,206,132,146,211,63,79,75,134,91,187,140,235,37,119,223,255,29,179,215,71,236,14,71,220,190,253,6,81,22,211,88,49,
165,68,113,76,167,236,81,244,54,41,55,37,80,228,240,213,11,190,120,112,143,211,231,79,72,129,205,141,109,46,220,188,137,139,99,113,250,186,70,146,167,34,145,26,154,88,96,104,70,11,150,213,59,241,14,28,
189,62,225,210,254,101,6,123,7,180,214,98,171,138,56,249,78,149,161,66,181,165,35,35,15,174,105,88,44,100,147,75,243,14,113,214,161,236,143,168,151,11,105,91,0,202,182,178,88,65,236,210,120,8,61,50,231,
229,196,142,130,126,215,104,69,146,164,148,253,45,134,251,151,121,250,252,27,222,251,213,47,240,213,138,139,23,182,185,112,229,2,38,150,228,160,36,201,72,179,156,178,59,160,55,218,37,239,142,56,157,156,
113,244,234,5,175,158,63,229,253,119,222,97,53,155,115,97,111,151,239,253,224,38,73,150,202,34,8,45,45,165,28,38,146,255,246,97,248,230,29,161,170,208,76,102,19,108,213,240,198,143,126,140,210,49,182,
150,86,68,154,164,33,219,85,92,145,74,139,145,190,90,44,233,111,116,56,57,57,161,90,85,104,21,81,118,187,116,6,35,38,147,137,180,251,66,240,187,15,207,221,135,97,151,11,189,95,130,164,79,88,55,82,201,
70,81,68,156,149,236,92,188,206,181,59,183,249,252,211,143,185,247,238,239,200,35,24,14,134,152,40,13,179,245,160,10,137,18,58,253,33,23,175,223,100,115,111,159,197,106,193,195,7,159,241,224,179,79,56,
125,249,156,44,130,94,127,192,214,246,78,144,193,57,104,93,240,134,202,102,230,61,226,37,113,224,131,194,161,181,142,233,217,17,77,213,240,214,127,248,119,137,147,140,213,98,137,173,197,52,149,22,57,222,
203,97,24,199,154,186,22,196,64,154,197,84,171,5,103,147,169,88,217,203,46,219,123,59,204,231,11,89,39,107,116,133,82,120,37,47,184,15,55,167,186,109,80,218,174,119,63,217,56,252,186,111,46,161,29,119,
126,242,251,92,188,126,129,247,127,245,23,60,252,236,35,226,8,242,216,96,235,70,60,37,70,90,43,73,154,147,151,35,174,124,239,71,108,236,237,80,207,103,60,255,250,75,190,184,255,41,147,163,23,36,218,211,
29,142,136,163,4,239,140,40,183,76,36,142,109,147,16,199,17,198,196,178,78,141,14,206,116,67,18,27,94,191,124,73,209,223,228,198,237,59,184,214,157,115,96,34,19,178,161,245,218,207,225,66,213,105,24,159,
156,50,93,172,232,116,186,82,21,247,250,228,121,78,93,45,207,233,180,34,215,12,115,131,160,63,255,155,194,144,112,25,59,151,134,198,113,66,217,27,50,218,185,204,198,238,5,142,158,63,225,131,95,254,57,
79,159,62,98,119,111,147,97,39,163,174,37,113,42,78,51,81,228,116,6,244,183,46,51,220,187,132,182,45,167,47,159,241,224,238,7,60,121,252,53,171,229,132,65,127,200,238,254,62,73,36,207,32,138,5,185,162,
84,152,98,168,117,26,99,140,210,50,187,211,74,241,236,241,55,216,162,199,165,43,55,101,211,118,173,160,161,189,252,251,186,21,133,86,228,101,65,53,155,49,62,124,141,201,11,118,247,118,105,154,150,162,
59,192,120,104,234,85,232,108,200,13,200,157,59,250,130,126,83,185,64,245,181,231,104,152,117,1,149,166,37,121,217,231,210,155,63,98,119,119,151,71,239,255,142,95,254,233,31,179,106,167,12,250,165,204,
214,80,161,237,35,106,182,193,214,1,215,223,250,41,163,193,136,102,54,227,249,163,175,48,63,188,117,243,237,229,178,166,223,27,48,216,220,34,74,115,146,178,164,174,22,184,182,69,43,123,94,53,161,215,121,
152,158,198,181,194,174,9,65,41,222,9,63,191,219,223,32,233,247,184,251,241,187,188,248,250,9,7,59,123,92,186,124,128,78,34,49,172,160,136,227,132,78,209,163,236,142,232,110,110,50,89,205,120,249,236,
41,95,61,248,156,163,111,158,18,89,199,246,246,30,23,111,221,162,141,36,165,73,242,59,101,67,48,198,132,202,67,218,6,58,180,146,188,10,108,115,223,242,232,193,23,220,249,225,143,40,183,246,48,58,194,215,
11,98,163,2,9,210,226,189,244,175,147,56,97,58,155,145,197,17,179,217,12,234,150,188,51,192,196,41,189,225,144,229,114,78,219,182,56,43,105,91,18,73,39,178,62,135,162,177,114,240,201,217,183,70,60,104,
242,94,159,206,104,151,165,117,188,243,151,63,103,252,234,53,215,174,92,97,247,210,190,80,43,157,163,72,83,178,60,39,205,59,20,189,45,58,163,109,166,211,9,175,158,63,229,225,231,159,241,249,39,31,225,
170,154,253,189,109,222,252,254,77,138,50,195,43,77,213,122,25,48,26,117,62,133,247,110,61,148,22,52,171,15,125,245,40,73,120,249,236,41,137,50,92,249,254,91,36,69,151,186,90,225,234,58,180,59,84,232,
249,55,178,137,59,139,246,142,254,176,195,120,50,197,58,135,138,18,6,163,45,202,225,136,201,233,169,84,236,33,204,65,41,251,93,232,181,119,226,83,8,84,79,23,6,117,120,79,156,164,116,135,155,220,254,241,
127,192,55,95,63,224,157,95,252,123,82,165,24,12,186,152,84,84,87,34,167,133,200,36,20,101,143,173,221,3,46,222,184,77,93,45,120,248,229,61,238,221,125,159,217,241,33,73,100,200,146,130,209,214,46,74,
197,56,215,200,139,20,120,48,81,148,72,133,237,148,84,129,235,16,81,47,235,200,123,205,124,114,2,222,242,214,79,255,54,69,127,192,217,217,132,186,170,40,59,5,94,41,154,170,150,92,91,165,168,171,134,36,
49,196,137,97,185,152,161,189,193,68,41,89,153,177,183,127,145,201,120,76,181,92,138,233,200,75,74,154,24,209,180,64,184,180,14,137,98,254,59,55,50,22,19,173,81,11,55,248,225,79,127,202,195,187,239,240,
219,127,255,239,72,35,67,154,164,56,43,125,115,127,174,108,202,232,244,7,108,95,126,131,11,55,111,209,172,102,60,127,252,85,144,38,62,36,141,20,253,193,64,2,236,157,108,156,218,40,226,40,17,231,110,150,
18,199,6,99,100,179,54,145,36,47,69,38,108,20,145,225,229,211,111,24,110,239,114,225,234,13,80,17,213,82,228,163,177,49,231,131,119,188,38,203,162,160,228,81,28,191,58,162,169,91,6,27,27,68,38,38,45,123,
164,121,65,189,20,183,183,10,109,64,21,64,117,202,135,22,91,136,22,92,135,12,173,85,118,89,167,199,112,235,128,11,55,127,64,164,42,126,243,179,127,201,183,223,62,229,234,181,203,20,185,145,125,68,25,162,
36,161,236,14,40,186,125,58,27,251,12,246,175,18,27,197,241,179,39,60,186,247,1,95,125,241,57,171,213,25,221,254,136,221,189,29,162,36,34,142,35,9,110,49,25,74,199,196,137,48,162,148,17,207,142,81,242,
188,156,247,56,39,123,206,253,15,63,164,127,225,10,219,7,7,248,182,197,54,50,212,119,65,204,176,46,10,77,44,217,223,211,211,51,142,95,61,103,89,55,100,69,70,148,230,100,221,30,218,182,180,77,35,202,71,
23,168,172,97,96,235,206,215,5,65,234,44,145,154,107,92,76,86,12,216,185,113,135,107,183,222,100,242,232,33,191,252,147,63,164,85,21,221,94,87,152,71,81,76,164,35,105,249,101,29,138,222,64,228,157,163,
109,234,201,25,223,126,121,159,143,126,247,27,204,143,223,186,243,182,109,26,142,14,79,40,146,146,162,215,33,141,82,242,209,6,139,249,228,60,209,199,5,28,178,88,245,67,26,150,17,195,134,115,210,151,44,
203,46,253,173,45,62,185,255,17,15,63,253,140,75,123,251,236,30,236,224,148,48,92,34,35,41,244,89,146,81,116,122,164,131,33,243,122,197,243,167,79,248,250,171,7,60,253,234,1,202,54,236,239,237,113,225,
198,53,84,28,203,128,54,240,185,21,130,238,53,38,38,75,51,89,132,74,54,29,29,212,68,40,136,163,136,165,173,248,246,254,87,92,189,126,141,124,180,77,146,247,164,138,67,90,82,96,113,86,204,22,113,154,49,
62,61,165,223,203,89,53,53,237,106,69,86,148,36,105,78,127,99,139,122,185,194,123,113,22,138,87,65,7,97,149,80,107,76,208,11,43,175,206,35,34,251,163,61,146,78,159,127,243,199,255,138,197,241,9,223,251,
254,45,6,155,35,132,70,239,48,81,68,156,166,196,105,78,119,180,73,214,221,100,190,92,242,252,219,39,60,252,234,62,95,126,246,57,109,221,112,249,226,1,183,191,119,139,36,139,195,64,76,134,166,74,199,210,
67,183,138,52,77,136,162,248,156,243,47,231,64,136,230,115,142,36,209,188,124,246,140,94,81,48,218,61,160,191,177,41,206,206,170,18,182,249,90,147,228,189,220,164,112,212,85,69,81,228,76,166,51,9,246,
72,115,193,34,143,54,88,204,38,216,102,21,98,22,221,185,154,73,92,155,225,118,129,145,64,111,109,129,136,172,40,185,116,243,77,78,199,135,252,249,207,254,8,156,99,56,26,146,36,153,28,76,90,6,124,113,18,
145,230,5,253,205,29,246,174,221,160,109,27,158,60,124,192,253,79,238,50,59,124,73,153,68,244,250,35,202,225,6,171,101,35,36,75,43,131,211,117,146,151,241,235,86,133,184,127,113,46,152,234,20,222,133,
176,105,173,105,171,37,85,235,184,124,237,38,187,23,47,179,156,47,57,59,62,161,13,115,128,181,86,218,57,203,106,181,10,41,90,13,147,233,20,31,18,178,242,110,151,75,87,175,179,156,205,153,79,166,114,3,
181,173,40,42,76,140,87,66,63,140,34,19,250,181,107,7,174,67,17,209,31,237,243,183,254,163,191,199,103,239,254,130,95,254,233,159,209,233,200,186,51,81,132,49,158,40,132,148,71,73,74,150,119,24,238,92,
228,224,141,219,184,118,206,201,203,103,60,125,244,128,215,79,31,129,181,244,251,35,210,76,16,20,38,206,68,212,128,124,237,40,142,206,231,68,145,209,130,200,214,242,30,71,145,38,82,162,208,137,140,231,
235,47,239,147,247,6,236,238,95,36,43,58,97,56,47,166,76,165,85,168,80,21,38,17,55,253,124,54,101,54,155,137,82,39,216,253,203,254,136,162,40,169,151,203,32,119,94,87,251,107,93,58,196,177,17,161,72,148,
160,165,97,136,67,209,27,237,176,119,229,14,182,94,241,23,255,252,159,241,122,124,194,193,197,93,146,36,10,121,187,154,44,203,41,202,146,254,104,155,110,127,155,114,243,18,94,41,38,47,191,229,211,15,126,
203,227,175,238,179,92,76,217,220,222,102,127,127,63,12,198,99,153,207,24,131,81,94,50,112,149,38,203,203,112,35,140,67,187,214,133,155,135,38,78,12,89,162,249,224,175,126,71,103,123,135,189,11,87,72,
162,140,186,109,68,204,18,102,97,30,141,119,142,172,200,72,163,152,195,23,207,25,159,156,8,126,218,24,146,76,14,107,188,19,33,4,26,173,194,112,56,120,94,164,96,115,162,102,211,70,12,165,218,99,226,130,
205,253,203,220,126,235,39,28,126,246,41,255,246,159,255,51,40,60,69,150,225,144,120,82,163,197,124,151,22,5,195,173,109,246,174,220,102,231,226,117,252,106,197,215,119,63,226,222,221,247,121,254,244,
1,230,63,255,131,127,240,246,228,244,140,36,141,152,79,167,244,59,125,242,110,151,60,43,136,58,37,203,249,20,229,218,96,31,151,202,178,13,213,164,81,114,114,187,240,0,203,222,144,215,167,71,60,254,228,
62,87,47,95,164,55,236,132,27,129,150,107,165,214,162,9,206,187,196,189,1,139,182,101,185,156,241,249,199,31,243,252,155,71,168,166,229,96,119,159,43,215,175,66,146,126,119,2,42,27,78,95,35,242,176,56,
33,47,122,36,137,68,177,153,191,33,185,196,203,162,204,242,148,151,175,95,82,157,78,185,246,230,45,136,51,209,34,87,43,112,205,121,95,223,182,173,36,229,24,197,217,169,12,145,230,179,185,244,65,123,61,
201,214,44,59,172,86,115,188,23,208,145,240,242,125,8,133,22,89,104,221,182,161,74,240,196,38,167,24,110,242,222,95,191,207,242,228,132,171,215,47,209,237,22,178,97,59,11,74,147,166,25,73,150,80,118,251,
164,229,136,179,217,146,241,248,152,207,63,249,144,175,191,124,128,107,45,23,247,119,120,227,206,77,226,36,200,101,131,90,202,72,121,33,45,20,101,200,178,140,56,151,56,64,239,100,147,243,62,200,71,181,
56,251,148,214,52,139,25,195,193,144,172,51,100,48,218,66,167,41,203,197,20,19,80,183,162,31,55,208,90,218,166,165,90,45,104,93,205,124,190,148,207,41,205,232,246,251,116,122,3,198,39,39,50,120,116,162,
219,150,141,76,157,115,137,188,90,191,8,114,0,14,55,118,33,78,248,229,159,253,41,121,150,208,239,247,137,20,96,91,34,29,194,174,181,34,205,100,158,52,218,187,132,142,99,22,211,99,62,121,255,119,156,190,
120,70,164,52,221,110,143,178,215,39,138,51,49,204,133,3,216,133,34,222,24,201,67,48,113,34,85,146,212,0,193,131,160,207,123,209,70,199,216,198,209,182,43,180,134,205,205,109,70,187,187,152,40,229,240,
249,115,172,173,195,175,3,215,88,185,174,4,180,180,109,87,76,231,83,234,170,33,142,13,189,193,144,173,189,29,102,227,9,171,213,2,235,106,201,134,61,191,177,123,180,73,113,190,21,159,68,176,96,42,101,184,
122,231,71,28,62,127,196,111,254,242,231,228,101,130,49,2,216,91,51,91,52,90,90,77,121,65,167,191,77,119,251,18,73,158,49,31,191,228,225,253,79,249,246,171,251,88,87,49,24,110,144,229,153,100,172,42,19,
12,119,146,8,166,149,15,114,76,67,154,165,100,121,33,45,65,100,35,246,56,89,187,202,75,8,80,107,121,249,237,183,244,2,6,164,51,220,160,94,44,229,125,52,162,146,243,86,54,197,44,139,168,87,75,22,139,25,
71,175,143,201,59,37,174,93,145,231,57,89,94,144,164,57,117,181,56,47,150,4,213,45,79,194,4,217,119,100,196,81,75,144,88,247,70,251,20,101,201,47,255,248,15,89,212,21,187,251,155,24,37,115,15,19,199,196,
113,66,156,37,116,7,27,244,71,91,144,245,80,105,7,213,84,60,188,251,62,95,124,250,62,139,249,148,237,189,125,182,182,55,164,130,215,210,21,48,65,146,106,116,152,75,95,142,90,187,0,0,32,0,73,68,65,84,104,
72,210,140,44,142,113,182,149,97,51,65,131,174,164,77,156,164,25,205,98,193,253,123,247,232,239,95,160,219,237,83,116,7,52,171,133,12,235,215,169,96,222,138,172,56,79,105,23,53,179,201,140,249,116,66,
86,118,100,130,17,39,228,101,231,188,72,146,139,158,13,243,39,225,244,174,221,201,58,152,59,37,82,179,224,194,237,183,152,61,121,196,175,254,244,95,227,83,71,156,132,12,143,40,28,14,113,68,154,102,164,
157,130,225,206,101,250,187,151,73,146,152,249,235,103,124,242,155,95,241,228,241,103,162,244,249,71,255,217,127,241,118,28,27,142,79,142,176,190,97,252,250,136,126,111,64,214,237,144,68,41,105,111,200,
124,58,149,158,149,181,84,117,205,58,15,193,89,139,183,34,95,114,161,101,123,248,226,25,7,251,59,36,121,46,204,20,109,208,42,34,77,12,17,158,44,201,200,250,3,106,34,92,91,243,232,139,251,124,115,255,115,
116,211,112,245,194,101,174,222,188,138,143,214,113,132,146,193,106,145,74,64,41,131,142,52,105,156,82,150,93,137,53,11,155,190,242,90,48,0,107,221,188,135,188,211,229,233,147,175,57,125,117,200,104,115,
147,188,211,167,191,181,35,70,164,166,17,128,147,164,57,16,43,104,240,44,198,51,210,52,102,58,57,195,91,75,167,39,234,143,78,127,131,249,124,129,114,173,4,170,180,226,66,92,27,138,180,54,226,208,13,87,
211,103,47,159,209,204,103,92,188,176,77,154,74,250,147,164,104,201,45,39,142,34,202,78,159,180,51,162,106,21,117,93,241,233,7,239,243,213,231,159,72,207,253,202,101,174,221,186,142,73,34,89,32,254,59,
19,139,168,11,4,85,108,76,76,209,233,211,201,83,18,99,164,47,235,61,109,96,223,104,47,217,157,113,28,81,181,21,203,197,148,147,211,41,81,154,177,177,183,71,167,59,98,190,156,75,111,210,136,73,164,113,
13,202,120,230,243,138,213,124,142,173,42,86,171,21,77,93,145,36,37,101,175,199,96,115,155,241,233,49,254,60,95,192,133,48,17,2,91,71,62,31,201,249,212,152,36,227,254,167,159,82,22,25,121,158,226,195,
32,239,60,123,64,199,68,38,34,206,115,54,118,46,50,216,216,194,54,51,126,243,139,191,224,235,47,190,36,137,12,131,209,144,188,211,15,138,19,39,137,83,109,35,133,68,156,8,159,189,21,210,165,137,101,176,
175,228,138,40,76,27,173,136,80,232,40,193,33,7,92,153,231,224,151,124,251,244,25,105,183,100,247,210,21,54,183,119,153,142,207,168,86,11,84,136,251,76,242,20,219,8,245,114,185,90,49,30,159,176,90,44,
105,86,43,136,12,81,90,176,127,229,26,179,201,25,139,233,12,173,69,147,47,183,4,77,156,136,30,29,39,82,60,175,53,121,127,196,114,126,194,195,79,62,161,40,74,89,27,65,89,36,51,21,136,163,24,29,199,68,105,
135,173,43,119,232,108,238,224,171,49,31,252,250,231,60,127,252,8,133,98,180,185,75,154,22,178,105,162,48,105,129,247,45,113,156,138,18,199,196,24,35,217,199,121,209,15,33,55,210,27,182,206,7,71,57,104,
28,145,49,36,89,206,114,54,227,225,131,143,25,79,151,36,221,62,187,251,23,137,162,152,166,90,162,181,19,84,130,107,193,27,138,50,197,59,199,98,185,228,232,248,136,78,191,135,91,85,44,171,154,164,236,145,
167,121,112,107,203,225,178,62,157,189,114,231,34,8,121,66,160,76,66,148,117,120,240,238,111,80,73,68,175,95,96,92,43,107,223,24,210,36,33,75,34,202,222,128,193,104,131,40,29,97,242,1,89,172,248,250,227,
223,242,233,187,191,98,81,45,216,191,124,133,205,205,13,226,40,34,214,50,19,138,98,13,33,100,124,237,90,177,14,76,210,145,245,162,205,57,86,194,6,58,170,71,225,189,166,51,40,57,59,58,225,238,251,239,179,
50,138,206,112,192,112,99,23,227,160,109,42,226,56,28,32,78,126,79,119,208,167,109,86,140,143,79,88,206,23,164,69,78,164,13,94,69,148,189,33,6,141,107,218,176,249,139,250,10,163,207,11,73,65,161,200,140,
161,232,13,176,147,51,238,127,248,46,166,80,68,177,224,58,196,192,102,2,52,207,144,151,93,6,59,23,217,186,116,155,110,183,79,117,244,146,119,255,244,103,60,124,120,143,180,147,179,123,241,18,230,31,254,
167,255,201,219,121,158,96,189,227,108,124,138,199,177,56,155,209,201,187,244,134,67,116,20,145,228,5,243,233,68,128,83,225,5,119,110,237,170,243,223,5,37,27,19,244,205,4,41,83,208,240,155,128,25,85,138,
60,239,224,147,140,201,98,206,221,15,127,199,163,79,239,18,121,195,245,171,87,216,191,188,47,233,49,136,218,71,92,146,70,180,253,65,9,163,136,48,81,204,222,197,43,36,69,23,219,214,242,107,140,145,151,
201,90,105,59,41,71,100,164,58,58,59,57,164,94,46,233,142,54,136,146,156,222,198,6,78,25,170,197,12,165,93,248,25,26,146,36,163,110,45,171,217,25,40,199,244,108,130,178,142,162,215,23,237,118,89,178,156,
79,240,206,81,55,45,120,47,129,16,222,3,14,239,173,180,190,156,44,222,78,153,6,142,134,244,43,149,209,36,145,244,17,211,52,167,59,216,194,37,37,211,201,152,123,119,63,224,209,253,79,48,206,115,245,234,
37,174,220,184,36,3,199,16,83,24,107,105,123,24,99,164,215,169,67,5,167,98,182,119,47,146,101,157,112,24,16,170,117,176,182,13,170,29,121,20,58,206,197,190,159,104,14,15,143,73,179,148,114,56,162,236,
143,88,206,87,120,91,75,80,132,151,231,155,197,17,171,249,138,186,89,176,108,42,150,203,5,174,117,20,101,143,188,211,33,43,114,38,227,19,225,141,123,27,134,174,74,20,58,109,27,54,116,121,158,211,249,148,
60,73,72,210,88,110,3,218,8,211,69,201,1,161,131,90,169,191,117,192,112,103,23,107,43,222,255,205,175,121,242,232,33,10,207,246,246,38,69,217,19,5,131,179,52,77,27,218,141,65,231,173,116,88,155,142,52,
201,185,242,198,155,120,175,69,47,15,65,137,1,182,105,104,109,27,52,243,14,167,21,73,172,201,10,205,227,175,159,97,226,148,225,198,22,163,173,109,22,211,57,213,98,134,15,190,131,181,146,66,5,103,250,114,
49,199,89,68,118,106,34,202,78,143,205,173,109,206,78,79,105,234,74,144,9,182,145,6,104,36,40,101,185,229,5,237,189,246,76,207,78,64,75,240,183,49,90,144,212,145,62,215,172,107,19,17,103,29,118,174,220,
98,243,226,37,108,61,231,238,111,254,156,175,191,248,12,180,97,103,255,34,198,104,90,87,75,162,155,82,146,129,224,5,233,177,54,89,105,173,137,242,14,27,187,7,216,186,149,172,225,40,98,141,12,84,1,69,225,
156,151,77,68,43,234,202,114,248,242,91,198,243,134,222,104,68,214,233,145,229,37,213,98,78,235,37,227,22,39,170,175,44,77,104,86,11,206,198,99,94,191,60,162,232,148,216,122,133,138,82,138,78,95,224,119,
171,133,24,245,218,21,218,7,9,179,9,27,37,46,176,141,96,53,155,226,181,39,142,20,120,43,183,52,173,136,99,193,166,155,56,165,51,216,38,45,71,100,253,109,52,158,23,15,238,242,254,175,126,206,108,185,226,
202,27,111,178,177,49,32,210,162,14,195,72,161,24,153,53,4,209,159,67,238,76,214,165,63,218,17,82,112,144,29,163,20,180,46,204,193,8,115,8,79,81,36,140,95,29,242,226,233,55,196,189,1,157,222,128,162,215,
71,59,145,153,174,103,28,214,182,130,73,40,114,150,147,41,147,211,99,102,179,25,157,193,80,212,60,120,178,78,137,107,27,129,16,42,112,237,74,14,80,199,185,231,169,245,30,167,192,214,11,38,199,135,248,
56,204,41,77,64,160,107,33,12,104,19,19,197,25,157,193,14,59,215,238,80,150,93,116,61,231,163,191,248,51,190,186,127,151,188,95,48,28,13,112,90,99,254,203,127,248,7,111,59,235,40,203,156,85,85,49,57,61,
195,170,150,195,23,47,217,26,109,81,244,123,100,89,129,74,51,230,179,41,77,83,73,200,197,249,144,161,149,124,81,180,12,206,66,206,167,247,235,13,58,152,163,180,33,50,25,221,225,54,227,213,146,207,239,
126,196,227,207,239,17,43,195,247,110,221,98,239,210,30,118,61,194,208,158,72,199,129,211,33,11,210,132,1,163,209,6,231,27,206,142,207,184,113,243,77,226,206,64,2,45,124,43,213,144,38,108,186,162,36,73,
178,148,213,98,142,171,151,216,214,98,162,4,147,228,12,55,182,48,105,70,51,61,37,50,130,50,245,206,83,102,41,211,197,148,166,90,66,228,152,78,38,120,107,233,141,182,40,202,146,36,239,81,205,231,193,16,
209,162,149,12,2,173,181,56,111,229,1,133,91,143,144,21,237,121,127,91,41,69,28,25,146,36,38,47,123,228,131,29,78,166,11,222,123,231,215,60,249,234,51,34,15,183,111,223,230,194,213,139,50,172,243,242,
240,163,40,14,144,183,136,200,68,232,200,4,134,191,39,50,134,215,175,143,217,187,116,157,114,184,67,83,183,50,120,213,74,232,153,235,195,198,139,75,207,89,75,18,203,162,89,205,22,152,84,172,255,91,219,
123,204,23,115,156,147,208,101,108,11,94,139,62,125,94,225,92,67,85,213,84,43,193,35,23,221,14,253,209,54,113,154,51,57,57,22,77,191,13,193,50,190,193,43,57,56,116,48,228,104,101,130,37,221,75,170,82,
64,243,138,228,79,145,196,25,105,222,231,141,183,126,202,116,54,225,183,191,248,247,60,249,234,11,178,40,98,111,239,128,162,44,130,218,39,198,183,45,254,111,40,36,156,107,207,35,249,36,138,208,178,88,
44,249,201,239,255,61,210,78,159,233,116,10,214,133,248,56,127,110,115,199,91,154,85,203,124,89,211,239,119,72,51,195,209,235,99,34,147,160,226,136,131,75,215,88,44,23,44,38,51,121,126,97,0,157,228,5,
202,65,181,90,82,173,102,180,173,163,173,87,196,81,74,119,52,98,107,103,143,241,209,56,220,114,220,119,28,125,165,197,124,163,108,104,133,233,243,207,109,173,121,143,163,4,165,99,148,119,68,38,37,138,
83,70,123,87,185,253,227,223,99,124,248,156,223,254,217,207,184,127,239,46,131,254,144,237,157,237,240,99,184,208,243,23,95,70,164,229,6,105,98,21,144,32,114,192,218,186,70,233,140,203,183,222,164,90,
46,104,93,40,90,162,56,16,102,3,204,203,89,49,12,69,17,227,241,140,47,191,248,138,238,104,128,179,144,100,29,58,157,62,109,83,73,160,185,54,120,39,88,137,56,79,153,159,77,152,157,157,49,62,155,144,102,
25,56,43,0,188,110,151,72,105,154,170,193,68,45,56,41,6,149,94,139,154,197,93,43,209,152,10,21,69,40,219,4,5,92,20,90,182,162,143,79,139,62,197,96,135,162,191,69,181,92,242,244,243,143,248,245,191,251,
99,26,165,184,126,231,14,253,65,8,55,71,7,30,142,57,151,161,170,48,32,246,129,124,89,55,142,170,134,221,75,87,197,100,233,85,144,102,174,19,224,92,96,251,59,105,37,25,205,203,111,159,115,114,120,196,246,
254,158,244,237,67,65,232,234,74,214,164,150,25,73,18,39,20,221,146,201,217,25,227,147,83,86,213,66,120,67,14,226,34,167,232,244,105,86,18,153,233,108,45,146,221,144,165,189,30,110,43,15,77,91,159,139,
101,36,255,87,46,213,168,181,47,34,33,47,135,92,254,254,79,217,63,184,202,201,183,223,240,238,159,253,140,207,239,190,71,185,209,165,55,28,4,69,161,194,252,119,255,245,127,245,182,195,225,106,25,210,213,
109,195,217,217,20,107,45,243,201,132,110,217,35,45,75,58,189,62,196,134,229,108,138,109,155,224,52,92,95,81,197,69,166,35,131,117,237,119,156,17,21,12,23,40,162,40,165,219,27,145,245,250,124,249,229,
199,60,250,236,83,182,6,91,220,121,243,54,253,205,65,8,218,22,219,190,94,187,244,130,121,71,250,187,70,160,76,129,19,211,58,199,171,167,207,184,126,243,22,249,112,7,107,229,230,17,199,65,42,104,101,80,
231,156,35,203,82,22,243,25,117,83,51,61,59,35,54,17,113,94,146,20,37,73,209,101,53,159,73,247,89,121,188,109,200,243,140,197,170,166,90,204,193,120,150,139,5,70,41,122,195,13,242,162,131,143,18,154,229,
12,124,139,109,106,161,202,6,151,109,107,117,144,152,9,35,101,77,217,116,78,174,175,81,20,147,230,61,202,193,22,105,209,229,254,39,31,113,255,227,247,233,21,37,111,222,190,201,246,238,150,88,162,195,6,
165,76,132,119,98,194,142,99,29,212,49,82,157,106,37,3,40,165,225,235,135,15,185,120,233,10,27,23,174,210,214,13,174,169,131,219,81,170,38,167,36,132,27,175,168,151,53,69,145,112,54,159,113,122,120,140,
81,17,69,167,195,198,246,54,117,109,105,171,25,70,201,203,103,219,150,180,83,48,155,46,168,234,138,182,169,131,97,203,209,233,246,233,140,54,0,69,189,92,208,218,230,252,51,87,193,69,232,48,34,195,179,
45,54,56,128,69,190,185,118,219,136,188,52,203,123,92,189,245,3,182,247,183,248,240,183,127,201,195,207,239,209,45,75,246,14,14,136,210,4,127,30,207,40,51,3,173,162,224,195,208,231,18,71,209,223,35,1,
27,77,197,201,241,49,119,126,252,19,54,247,47,179,156,78,169,170,101,80,130,200,186,149,234,74,14,207,186,174,233,118,82,234,106,193,235,215,175,80,113,68,94,150,92,186,118,29,172,103,50,62,9,151,37,79,
211,182,184,166,37,138,53,203,197,146,197,98,33,213,124,107,73,147,140,254,198,38,131,225,128,211,195,67,108,35,185,194,214,75,69,237,156,147,207,1,153,115,40,37,168,229,181,119,160,117,65,230,167,52,
73,148,147,20,3,126,244,251,127,159,94,105,248,203,159,253,11,158,124,243,152,205,173,29,54,183,71,40,23,2,74,18,185,253,173,67,179,117,224,74,41,68,141,35,100,108,13,218,114,122,248,138,249,162,230,123,
63,249,219,64,196,114,57,5,237,37,153,203,123,41,216,194,236,197,68,50,28,245,109,205,87,95,61,166,204,37,140,221,235,136,193,198,54,182,170,3,82,93,230,28,105,28,147,103,18,232,62,155,78,153,78,231,116,
58,93,233,221,71,137,144,43,35,131,183,162,170,146,182,227,58,134,84,110,244,109,43,235,199,227,195,220,106,173,223,151,228,182,40,41,232,140,118,217,218,191,206,230,206,54,15,223,253,53,239,254,250,231,
168,60,231,218,141,27,148,69,10,109,37,127,198,90,54,29,204,85,210,109,48,231,168,143,117,143,98,124,248,156,103,47,15,185,254,253,31,98,144,131,28,229,190,107,29,74,117,139,194,147,101,25,88,203,201,
171,87,140,231,83,202,162,160,174,91,138,110,151,78,128,49,174,49,203,222,123,162,36,161,200,10,150,103,83,166,103,99,208,242,174,213,213,138,162,63,36,207,114,92,221,224,3,172,78,50,9,204,249,90,39,200,
123,191,19,72,72,248,142,117,50,192,142,210,148,162,219,103,251,242,13,46,223,184,133,155,141,121,231,79,254,21,95,62,184,203,104,103,139,78,175,35,200,15,161,161,97,254,219,127,252,143,223,214,74,236,
196,202,57,202,178,203,116,190,96,54,25,211,98,153,159,78,217,219,221,167,236,247,40,251,3,150,213,146,182,90,72,192,134,147,26,203,218,117,37,47,39,169,90,227,63,189,208,7,35,29,147,21,29,138,209,136,
111,95,60,230,147,119,222,33,211,25,223,123,243,13,202,94,30,146,146,100,48,96,146,20,107,91,98,45,253,95,29,137,50,199,175,217,47,38,16,16,181,103,50,159,50,126,113,200,245,55,191,71,210,29,130,86,216,
106,25,114,121,53,208,72,143,62,144,45,23,139,25,109,152,146,151,89,78,86,20,116,122,35,226,188,100,49,157,0,237,121,59,166,200,50,206,38,11,234,213,28,109,12,243,249,130,36,138,24,110,237,98,210,132,
186,169,177,181,84,249,54,36,134,57,231,113,202,72,138,82,120,113,228,65,217,32,73,51,68,38,161,55,218,100,184,125,129,207,238,125,194,95,255,250,87,148,69,193,157,59,183,24,12,58,193,79,224,207,57,246,
24,131,236,141,82,97,36,70,6,148,225,148,193,57,13,206,209,186,21,47,31,63,229,198,237,219,244,182,118,65,197,44,22,11,233,147,70,209,119,183,46,99,208,70,177,152,79,232,118,59,28,190,62,98,53,91,144,
21,57,38,73,232,244,7,52,85,75,83,173,2,50,67,158,101,154,167,156,77,231,84,243,57,117,83,227,108,13,173,103,99,123,135,206,96,196,170,170,168,230,115,108,91,225,90,1,171,89,43,70,45,23,140,39,222,233,
115,134,143,15,67,49,29,162,22,183,182,47,112,235,173,31,240,206,47,255,45,31,191,247,30,73,154,178,179,187,29,42,27,37,142,88,165,207,45,240,132,182,86,180,110,233,224,241,190,9,77,70,9,193,89,45,230,
204,206,38,220,249,225,143,217,186,120,153,85,213,48,159,156,9,190,87,113,174,171,182,174,197,24,49,89,101,121,204,241,241,49,203,101,45,18,183,52,103,243,226,5,156,85,76,199,99,8,173,29,223,186,115,211,
223,98,53,151,80,29,165,196,168,213,235,48,218,216,160,40,187,188,122,246,92,16,22,182,22,160,31,129,197,239,100,222,225,21,178,241,161,206,161,119,162,89,143,200,138,62,151,239,252,136,107,55,47,242,
235,63,249,67,238,126,120,151,205,173,77,122,221,28,21,25,209,175,107,145,241,69,38,14,24,3,69,20,71,114,163,10,135,160,15,170,26,231,33,137,13,199,47,159,98,125,204,141,59,119,136,146,130,229,124,46,
67,230,208,118,12,150,49,137,146,84,144,231,41,71,175,94,114,58,153,210,237,21,24,29,145,116,6,244,135,27,180,171,5,38,72,115,173,181,164,69,76,158,103,204,166,115,230,179,51,102,243,57,105,150,161,156,
163,55,218,32,239,246,177,85,69,83,213,88,103,49,10,172,179,1,113,46,162,6,31,246,19,25,182,219,0,121,147,181,155,119,70,108,236,93,229,224,226,101,94,61,248,152,159,255,155,63,34,234,245,185,249,198,
13,242,196,224,109,21,208,222,90,240,22,38,146,0,121,45,193,141,193,219,42,108,27,43,185,186,113,164,57,252,230,107,142,102,13,87,111,223,38,214,134,182,174,68,117,166,140,92,70,90,43,183,95,37,204,163,
229,108,198,248,232,136,214,58,58,189,146,182,245,196,69,135,44,45,168,151,43,48,173,100,38,135,130,51,54,154,241,201,41,147,179,49,77,93,97,178,88,156,232,195,13,210,56,22,246,142,183,96,215,90,124,29,
28,191,30,167,124,64,53,139,112,160,181,14,29,11,170,219,196,17,197,96,155,155,63,250,41,209,114,193,95,253,203,63,228,155,167,15,233,111,15,72,203,66,126,86,43,232,21,239,192,252,47,255,251,255,241,182,
40,113,108,160,70,58,58,253,46,173,107,57,62,124,205,124,49,103,49,157,177,181,179,67,183,219,35,237,118,89,46,87,184,102,73,219,52,162,117,14,170,140,214,133,152,188,160,217,215,74,54,175,216,72,69,240,
234,244,53,31,252,242,151,148,89,135,11,151,46,82,246,68,105,177,118,232,42,175,207,77,41,107,101,79,89,102,68,81,28,216,54,18,172,32,118,104,136,99,197,171,195,67,166,223,190,98,255,198,13,138,193,38,
113,222,163,169,42,180,178,242,18,139,242,31,157,200,240,102,53,61,99,185,170,169,103,75,140,137,40,251,67,210,78,135,188,215,101,53,157,74,47,83,71,120,219,210,239,117,152,206,87,76,206,38,52,174,102,
114,50,161,83,20,20,221,30,253,209,22,85,99,105,155,21,77,189,68,227,37,4,3,141,117,54,48,55,130,30,62,64,59,132,159,95,210,221,216,227,155,39,143,121,231,47,254,140,157,173,109,110,221,190,78,146,68,
231,172,141,36,206,112,225,122,41,220,26,137,94,204,243,66,52,246,206,97,109,168,80,188,32,14,98,163,153,175,230,60,251,230,41,219,91,59,244,183,118,40,6,163,16,102,82,19,41,133,197,8,197,15,143,81,154,
106,181,162,200,99,94,191,58,164,90,204,36,121,40,237,176,121,112,137,186,181,98,147,119,45,202,53,68,26,186,189,146,229,124,201,106,49,225,100,124,134,179,158,52,205,216,218,222,162,55,216,98,50,57,163,
90,44,105,155,85,160,46,234,192,208,97,221,165,13,86,253,80,205,120,153,177,116,122,35,174,127,239,14,31,188,251,75,62,122,255,93,210,162,195,104,115,147,44,205,136,34,197,119,127,133,0,233,16,68,226,
91,39,189,113,165,130,177,10,116,136,173,241,94,216,235,214,54,84,139,5,123,23,46,112,225,250,27,36,121,33,109,203,182,146,12,86,91,131,85,212,117,77,181,154,11,116,45,141,56,121,125,68,219,88,154,218,
177,108,225,226,181,107,196,81,194,233,225,43,97,175,40,240,182,66,107,67,150,165,84,139,21,213,106,129,109,91,170,85,69,127,115,147,209,246,54,74,43,206,78,78,209,30,90,91,135,141,119,45,72,208,18,45,
233,215,183,19,209,131,123,215,98,162,148,237,131,171,220,124,243,38,127,250,127,255,159,220,189,247,25,195,173,77,138,78,41,144,179,181,249,78,105,192,97,18,113,21,199,145,248,92,76,36,81,125,54,228,
107,40,101,240,180,104,35,210,215,167,143,190,164,170,90,246,175,92,167,63,218,198,89,207,170,154,227,181,151,2,193,59,188,111,194,252,13,188,215,28,189,126,201,178,106,232,228,57,145,210,168,40,145,247,
96,185,8,49,154,210,58,76,179,132,188,40,88,76,103,204,206,198,140,79,79,33,80,70,203,254,64,100,167,206,98,155,10,219,46,177,182,165,69,48,31,130,158,248,78,17,229,215,12,47,64,71,57,27,251,87,56,184,
124,131,175,63,248,13,63,255,217,31,97,122,125,9,92,114,53,109,107,105,145,40,65,19,9,13,52,54,6,163,98,188,142,137,35,131,115,237,185,103,35,48,23,65,41,58,221,130,175,62,252,152,147,179,25,87,110,189,
73,222,29,74,166,132,171,137,141,248,41,156,13,81,149,105,76,209,45,24,191,62,228,248,240,53,113,158,146,103,41,94,69,100,101,143,162,232,208,172,22,231,60,33,176,228,189,156,36,138,152,157,30,113,50,
62,165,169,90,146,36,21,137,105,175,143,65,97,219,86,16,200,161,93,233,195,90,113,182,1,215,124,55,55,213,210,73,1,69,217,27,113,229,206,223,98,84,228,252,226,255,249,127,185,255,244,11,70,59,35,105,49,
33,126,16,229,141,20,93,202,96,254,231,255,245,127,123,219,100,57,179,201,89,32,41,74,143,169,223,235,179,168,43,198,71,71,204,87,11,108,213,176,181,189,67,94,22,100,101,193,236,244,148,186,94,73,223,
86,107,148,142,165,58,214,38,84,111,124,7,95,210,6,31,69,124,246,193,135,108,14,71,92,188,116,129,162,76,49,202,97,157,69,171,56,40,42,92,64,31,184,144,148,39,160,179,40,201,68,89,112,174,24,23,192,155,
209,144,23,37,95,61,126,66,226,61,195,173,29,178,162,79,209,31,82,215,21,206,213,210,2,209,2,194,74,34,67,109,173,112,60,230,115,188,109,101,128,154,117,200,243,156,40,45,88,45,102,152,243,62,177,39,207,
83,86,171,21,139,201,140,214,53,172,230,11,250,253,62,163,205,45,84,156,177,154,79,105,234,37,182,105,68,181,132,165,105,219,32,213,146,216,56,197,90,174,105,40,202,62,227,197,138,143,255,234,61,46,95,
62,96,123,111,75,176,4,50,49,147,141,42,12,187,149,82,216,160,91,142,226,68,190,71,35,76,159,245,38,1,107,227,147,34,138,19,206,206,38,88,215,210,237,13,201,187,125,250,163,45,102,179,25,202,54,120,237,
65,71,212,77,19,52,235,13,190,105,105,189,101,124,116,138,115,45,81,150,97,138,146,193,104,139,122,85,83,175,230,161,74,244,24,28,69,153,49,159,46,89,44,103,44,86,21,109,85,81,20,37,195,205,77,146,44,
101,50,30,11,167,166,105,130,202,33,184,114,3,198,90,197,90,178,55,156,151,170,43,138,57,184,124,133,39,143,191,226,193,231,247,216,222,221,167,204,10,98,37,237,5,229,17,43,166,246,231,249,6,130,187,144,
163,60,50,137,120,43,130,2,198,133,53,226,195,103,98,180,33,142,29,171,249,130,238,96,196,112,99,147,173,253,3,94,191,120,77,93,173,80,190,193,43,233,37,183,109,77,181,170,165,215,239,42,206,78,38,97,
216,39,118,250,173,253,3,20,48,29,31,7,223,66,27,226,253,34,48,49,77,211,80,87,11,218,218,209,186,154,222,112,131,173,237,45,22,139,37,171,249,28,223,138,59,212,186,86,94,226,160,108,242,136,118,93,188,
2,130,128,72,242,14,215,223,124,147,15,127,245,231,28,31,157,80,246,2,77,53,138,195,172,66,138,1,99,52,54,220,226,130,19,159,40,203,69,118,168,194,139,30,194,106,132,119,47,216,97,229,61,199,135,47,88,
44,150,116,7,27,148,189,13,140,209,212,43,169,188,163,200,224,125,35,201,77,145,65,89,112,77,195,100,60,33,207,11,226,216,224,172,167,241,158,238,96,19,219,44,69,0,225,45,206,58,138,34,35,75,99,102,147,
49,203,69,197,114,177,68,133,131,170,55,24,16,197,9,190,173,4,219,109,157,204,208,172,13,224,198,240,252,148,8,110,189,247,120,173,73,178,46,59,7,151,120,249,232,1,31,191,255,62,253,157,13,250,189,44,
204,65,100,10,96,66,210,158,86,230,156,91,239,45,168,72,64,130,90,235,144,221,44,179,53,123,126,211,212,196,169,230,193,39,159,81,121,199,230,222,1,105,217,39,214,64,91,11,218,57,8,6,192,147,21,41,145,
82,76,198,83,230,103,19,242,78,73,146,36,56,171,136,139,146,52,203,176,181,60,99,103,45,214,89,58,221,46,89,156,50,57,29,51,159,79,168,219,10,29,39,164,105,78,89,116,195,230,46,159,73,235,90,145,112,7,
57,177,246,98,144,92,123,92,214,195,249,205,189,43,108,109,108,243,238,159,252,140,215,147,19,242,126,22,156,209,33,79,89,233,64,220,148,131,219,252,143,255,228,159,190,173,163,136,162,59,100,185,16,249,
165,173,87,224,45,27,27,219,120,163,57,62,126,193,233,241,132,84,39,108,95,58,96,181,92,17,197,185,232,180,27,79,146,247,2,223,37,92,161,220,58,250,78,133,171,158,227,248,232,144,209,160,79,209,205,136,
35,141,81,158,198,182,210,91,242,58,196,207,169,64,165,20,110,79,28,103,20,253,13,146,172,56,199,151,42,165,206,3,148,149,50,36,145,34,41,19,62,122,247,67,84,235,24,237,236,80,20,93,186,27,155,84,117,
3,109,37,129,37,222,226,173,68,228,85,85,69,85,87,156,28,159,80,45,102,96,45,101,111,64,217,27,18,229,5,179,179,35,180,242,52,173,40,50,250,253,130,197,178,101,118,54,101,62,155,176,90,174,216,220,218,
129,56,70,233,148,122,57,195,54,85,96,211,8,88,73,210,128,132,159,97,91,105,69,225,21,141,131,39,15,31,178,183,183,73,222,201,69,81,211,6,151,43,160,77,66,100,130,194,198,203,194,55,222,147,151,162,144,
136,140,88,229,85,152,11,180,214,162,34,104,172,69,155,136,188,72,57,59,61,225,108,124,134,210,226,228,60,184,112,133,22,77,189,154,129,109,165,170,9,161,229,214,91,188,173,89,46,231,204,206,102,52,213,
146,36,74,49,81,202,214,222,62,117,45,135,156,40,8,196,224,214,31,12,104,90,203,108,54,99,54,158,178,152,207,41,203,18,29,165,36,121,206,98,114,70,211,172,206,83,212,26,90,129,78,185,224,74,116,109,112,
27,130,73,98,102,211,9,175,159,63,167,59,232,147,36,197,57,158,218,107,161,107,174,245,246,235,60,6,156,152,253,210,178,75,86,228,216,186,14,153,5,42,88,214,101,190,165,140,84,187,171,197,146,94,63,227,
201,227,39,56,52,197,112,200,229,171,215,88,173,86,204,207,206,194,64,221,73,198,9,38,48,130,90,150,171,5,179,241,4,163,100,30,209,162,216,187,116,21,131,230,236,228,4,141,108,222,58,142,131,25,208,176,
172,42,154,122,206,116,34,81,118,157,193,38,131,141,77,230,103,51,234,106,41,183,104,43,215,125,214,1,231,161,183,227,157,76,227,4,122,213,227,245,211,111,24,31,31,99,98,185,237,198,38,128,35,148,56,136,
209,30,111,195,205,0,31,156,193,154,56,239,98,156,7,35,12,122,33,198,202,96,216,89,9,208,136,98,141,183,45,47,159,63,229,244,232,20,162,140,193,206,62,253,222,144,106,53,147,32,19,163,195,77,204,17,167,
162,50,170,218,86,110,194,8,7,191,181,16,231,61,186,253,13,104,86,129,15,35,27,106,167,44,41,59,61,170,186,194,217,138,217,120,66,93,11,212,45,206,11,76,154,227,219,150,122,181,164,181,13,206,123,57,12,
61,56,47,192,50,235,229,54,11,30,21,25,230,167,103,124,251,244,27,250,91,3,34,35,115,55,235,2,10,33,18,179,146,86,81,104,159,249,0,95,87,36,121,65,146,70,130,11,63,111,1,74,184,209,154,112,154,231,25,
202,89,30,220,189,199,147,231,223,146,245,7,12,70,187,228,121,135,118,181,194,104,113,211,106,28,182,113,100,157,2,188,231,248,240,144,201,100,74,150,103,196,169,193,122,77,214,221,32,203,11,92,189,196,
249,6,219,54,68,198,208,27,13,201,76,194,106,54,103,54,155,48,157,206,137,226,152,98,216,19,5,143,11,7,68,211,134,217,215,186,40,144,89,134,252,172,210,30,245,94,147,119,251,124,243,225,251,156,85,103,
168,216,7,83,93,132,117,149,16,103,49,224,53,94,43,98,165,49,255,232,15,254,209,219,221,254,128,36,205,136,178,148,213,114,14,182,17,61,115,99,41,203,146,56,137,57,57,62,228,228,232,144,189,237,3,210,
178,196,152,20,167,161,90,44,80,38,10,225,0,162,4,105,218,90,146,223,93,248,80,157,12,172,196,4,163,130,234,169,13,161,192,225,58,27,28,133,231,87,67,13,38,74,217,187,116,3,157,166,129,182,40,242,58,231,
215,61,110,193,134,198,177,166,197,49,62,62,66,185,150,78,175,139,137,98,186,253,33,86,25,170,229,236,187,74,19,77,156,23,44,166,83,92,91,203,34,108,26,34,163,233,246,135,228,101,23,21,167,172,102,51,
172,19,206,142,86,138,78,89,160,180,230,108,124,202,108,126,70,158,100,108,239,29,80,59,137,11,180,117,77,83,47,133,152,27,170,7,31,6,69,42,36,209,183,78,136,121,121,145,139,46,193,138,17,167,105,234,
181,37,72,164,117,70,240,15,10,143,10,138,155,52,203,216,191,114,19,231,117,128,111,137,84,205,89,1,65,41,172,84,204,161,234,195,87,28,157,28,97,140,166,223,235,209,29,108,226,117,68,189,152,163,177,88,
21,220,167,218,135,54,131,229,236,108,70,51,91,200,166,96,20,121,183,203,112,180,37,155,216,114,17,90,36,146,126,213,45,114,60,158,229,114,201,116,49,102,62,93,112,112,249,10,38,21,195,220,114,62,149,
69,235,43,188,21,121,169,183,254,59,164,178,82,184,240,117,171,213,146,36,145,144,148,182,90,226,218,150,198,182,97,70,225,80,206,157,207,53,196,184,38,235,227,226,165,27,148,253,109,188,115,52,213,34,
0,65,99,214,208,22,109,12,206,54,130,191,64,177,183,63,224,229,243,87,84,214,210,45,74,246,46,93,193,19,49,159,76,208,70,135,214,153,198,107,241,151,136,12,115,197,114,58,147,246,143,179,88,52,27,123,
251,104,52,211,179,99,137,131,180,45,177,94,99,67,164,29,210,84,75,78,78,78,25,142,54,201,202,130,52,8,7,154,186,193,218,58,88,233,215,225,24,97,77,59,185,197,56,229,176,117,75,83,215,168,72,7,121,166,
188,55,250,111,168,140,100,94,38,66,6,185,229,120,180,74,216,186,120,29,69,104,33,41,49,29,9,23,203,5,130,168,1,19,176,192,104,142,95,31,114,116,54,165,55,28,82,118,123,244,6,27,84,171,133,28,76,231,196,
118,79,154,38,84,171,57,243,233,25,199,135,135,68,73,66,20,27,172,83,164,101,151,52,239,208,86,43,57,204,195,224,52,43,50,58,157,148,249,124,9,174,230,236,228,148,198,123,134,163,13,34,29,97,140,193,182,
43,234,160,112,177,86,42,216,182,117,88,223,6,244,182,204,10,189,245,180,77,77,146,69,184,70,24,67,46,64,234,116,20,159,167,141,201,173,62,176,123,140,244,194,203,193,46,105,146,7,101,161,68,217,123,199,
185,232,68,190,130,166,236,148,44,167,130,122,89,172,106,122,195,33,105,209,163,211,233,82,85,194,194,209,42,160,16,80,148,101,202,106,190,100,182,88,208,84,53,73,158,146,23,5,177,49,68,105,142,241,224,
155,26,144,121,129,247,154,110,191,71,158,25,150,147,9,171,249,140,179,179,83,178,78,151,36,205,72,210,92,210,171,218,26,219,54,40,37,237,167,214,187,176,209,123,185,145,134,1,125,61,95,208,216,85,184,
217,126,55,255,115,214,19,197,38,220,118,109,128,95,26,204,79,110,223,121,59,54,41,253,209,136,56,47,136,242,156,229,244,76,88,51,77,141,86,242,33,68,169,225,248,240,37,175,30,63,227,194,133,139,68,61,
137,223,91,173,230,216,70,12,19,18,64,1,245,114,18,204,56,1,64,224,60,104,89,208,132,111,84,90,245,34,53,250,174,31,169,206,7,71,4,61,235,236,116,194,245,55,127,132,206,11,218,102,21,54,54,19,250,160,
22,148,199,120,79,183,83,50,153,79,152,159,141,229,74,217,237,18,23,37,157,254,6,10,77,189,90,74,53,96,61,174,149,254,217,124,49,99,62,159,48,159,76,193,90,162,40,38,47,75,6,27,155,52,64,51,155,162,104,
113,190,65,105,79,183,204,65,27,166,167,103,188,126,254,140,126,81,178,119,245,34,85,171,241,202,83,47,39,162,63,247,208,134,30,100,64,137,201,97,166,13,235,134,246,250,80,88,207,65,132,127,211,98,84,
180,238,116,7,59,186,69,71,49,22,77,189,180,92,121,243,7,52,68,216,70,78,112,109,162,112,168,218,192,236,22,206,71,181,92,144,198,138,179,241,25,6,67,146,231,116,7,35,76,44,27,143,82,194,18,18,185,167,
84,111,139,197,138,179,227,49,216,150,38,12,50,139,206,128,141,221,93,38,227,83,92,219,210,134,205,88,41,77,167,211,1,101,88,45,43,170,197,18,19,197,92,188,124,133,172,211,99,190,88,80,45,231,34,227,12,
48,1,156,144,53,37,49,138,144,165,42,153,170,113,36,240,167,182,109,69,252,229,130,14,218,174,241,219,242,114,171,224,182,198,193,217,233,152,91,223,251,62,251,87,175,113,122,122,74,219,84,146,190,20,
156,223,206,75,15,86,43,67,83,91,226,36,162,63,204,121,246,248,17,78,197,100,113,194,222,165,107,152,36,227,248,232,53,206,203,161,41,195,54,89,151,214,89,234,229,130,166,110,136,163,88,122,252,121,193,
197,235,55,168,170,138,229,66,110,77,107,101,218,186,112,169,235,37,182,93,114,122,50,102,103,255,128,94,111,68,156,36,204,39,103,180,97,51,212,193,161,233,254,70,64,15,90,170,121,19,203,215,146,57,175,
23,96,95,136,222,243,225,208,211,6,140,138,112,218,161,12,34,95,244,134,170,118,220,122,235,39,88,39,136,140,53,202,99,61,176,12,213,136,188,71,214,98,189,231,232,213,75,86,171,134,56,49,228,221,17,221,
225,167,18,114,210,0,0,7,144,73,68,65,84,22,205,114,133,179,21,74,251,48,232,86,152,68,210,151,22,211,9,243,217,138,52,137,49,10,234,170,193,228,37,69,183,75,91,45,81,94,102,130,141,149,161,229,112,216,
99,181,180,104,215,50,62,126,141,138,18,54,119,247,48,81,140,86,158,106,57,167,105,106,233,93,59,73,178,67,7,62,190,93,51,102,228,245,105,154,10,231,131,247,35,228,187,58,39,200,111,41,22,165,239,47,157,
3,240,182,165,94,213,236,92,186,70,18,69,52,173,13,224,180,117,236,96,43,198,210,32,60,233,244,59,76,207,38,188,122,246,130,40,13,28,162,178,43,9,108,65,111,239,145,121,131,210,134,162,83,48,155,206,56,
57,60,98,62,155,19,165,70,58,37,182,37,233,12,136,140,198,54,161,93,229,44,90,91,210,50,167,44,74,154,186,162,90,204,24,143,39,116,134,35,242,178,32,74,82,124,35,42,65,161,199,138,239,67,35,251,166,6,
17,95,4,158,151,243,86,102,31,225,40,243,180,130,106,48,177,8,62,252,26,174,168,48,119,174,221,120,187,94,174,216,24,109,48,220,222,164,236,13,104,129,122,54,199,181,43,176,13,109,11,89,26,211,237,117,
121,254,242,5,159,127,248,49,253,162,207,112,115,155,238,104,196,244,236,20,239,26,150,243,51,86,139,177,200,169,220,122,16,21,194,81,214,74,13,31,22,250,121,63,94,201,134,100,162,117,34,90,88,216,154,
40,242,84,171,37,175,159,188,228,230,247,223,34,27,110,10,253,178,109,197,58,174,149,152,126,4,8,64,153,103,140,207,38,44,231,83,102,167,99,186,221,62,89,209,97,180,185,131,142,83,150,179,147,243,107,
191,194,210,239,117,57,155,175,168,86,75,230,103,19,172,109,136,116,74,167,215,167,236,15,37,159,178,90,97,109,139,179,21,206,9,6,181,215,239,178,108,26,30,220,187,71,189,168,216,186,120,145,193,198,38,
179,233,148,182,90,74,62,112,208,71,187,144,5,187,150,86,217,64,11,93,199,224,157,59,131,213,119,3,36,239,37,204,37,10,47,245,122,30,50,153,76,152,28,142,185,245,227,159,162,178,14,77,221,208,182,77,72,
252,146,63,211,187,16,106,18,25,234,101,77,158,37,188,122,245,26,239,44,101,183,79,111,180,69,57,216,96,114,122,138,246,205,121,117,159,102,49,145,49,52,109,197,201,171,19,84,235,240,70,7,24,83,193,104,
107,135,217,120,74,91,47,66,182,166,197,97,137,98,77,150,166,88,239,56,62,124,201,225,225,17,163,205,13,250,219,187,252,255,77,157,91,111,219,198,22,133,191,153,33,69,81,164,46,118,235,38,118,78,227,4,
65,155,222,208,2,69,209,135,2,231,233,252,177,254,200,162,13,138,22,45,26,199,177,29,91,178,68,82,188,205,165,15,123,36,156,39,189,74,20,72,238,89,123,173,111,181,85,77,223,236,25,157,37,53,137,148,166,
196,246,159,67,203,143,128,67,20,54,50,246,131,243,34,119,68,107,171,86,230,255,2,86,135,250,188,184,199,113,150,187,155,91,206,62,121,202,215,63,252,68,215,141,236,31,183,178,196,140,142,15,23,93,87,
206,246,236,155,142,121,145,145,37,154,235,171,247,244,253,72,86,148,156,93,60,99,190,88,178,185,191,23,215,142,179,224,35,110,58,81,88,215,211,236,42,198,110,148,233,210,123,146,172,224,217,243,151,236,
183,59,113,120,69,105,33,56,143,215,48,203,103,34,243,141,45,215,87,239,152,151,43,78,158,60,197,59,75,179,219,226,173,61,106,215,68,114,165,80,27,117,36,91,30,0,120,114,163,31,38,209,131,125,216,232,
68,172,169,81,184,16,123,171,216,249,154,122,205,187,171,119,252,248,223,255,81,206,79,104,154,134,113,28,163,196,42,180,206,56,51,11,104,78,105,242,114,198,250,238,134,174,237,228,101,151,102,124,252,
228,25,174,31,226,9,84,40,151,198,40,146,169,160,118,235,106,75,253,184,33,155,205,208,42,48,140,150,201,108,65,145,23,140,93,29,251,144,7,9,149,37,154,249,162,20,201,173,239,185,191,185,165,31,60,229,
201,138,124,86,226,199,129,238,232,73,63,244,46,68,2,159,140,234,81,246,146,118,53,21,75,86,156,181,210,218,21,165,25,167,116,100,101,249,168,235,75,138,119,104,43,254,124,243,39,151,95,126,75,89,46,132,
151,20,144,221,144,138,229,36,225,0,65,203,152,205,166,244,117,205,237,251,59,146,73,42,35,216,100,202,242,228,99,130,117,88,239,100,140,241,30,51,73,41,139,146,182,170,217,60,174,105,119,53,179,197,28,
163,3,131,243,148,167,159,96,2,241,25,98,177,65,22,176,233,52,163,44,11,76,208,244,109,205,253,205,13,58,207,41,150,75,166,89,134,109,123,8,14,107,237,17,186,23,66,188,54,62,136,109,218,91,233,220,245,
30,148,71,235,128,29,173,88,88,15,167,156,56,88,40,21,48,175,95,189,248,185,111,27,236,104,57,59,59,39,95,44,72,178,41,195,56,50,182,13,110,236,24,71,73,38,234,16,88,158,44,105,218,154,223,127,121,195,
197,211,115,158,94,94,98,177,84,31,174,233,247,59,194,241,24,24,223,55,58,145,47,25,84,140,14,187,163,117,83,5,209,8,39,233,68,38,220,24,114,211,58,50,37,98,35,207,195,230,129,253,253,150,203,175,190,
34,95,156,136,118,221,139,54,31,148,240,99,134,209,30,145,199,109,211,208,246,45,237,126,79,158,229,20,243,37,243,213,18,146,9,77,181,37,53,224,172,200,44,69,49,167,106,27,154,106,77,191,235,0,47,92,239,
60,167,92,157,210,238,91,108,223,17,108,47,101,4,241,232,156,78,102,212,251,150,55,191,253,202,106,86,240,242,213,107,152,102,180,187,45,67,91,69,187,31,199,134,27,140,188,141,157,29,162,93,206,71,91,
158,196,78,196,103,30,131,69,158,200,148,143,83,159,10,49,56,165,184,189,187,195,12,142,231,159,125,206,116,241,17,67,215,225,198,54,246,199,9,167,219,89,193,233,170,104,249,155,76,51,30,62,60,128,147,
223,86,204,231,76,139,5,205,118,71,176,45,113,120,19,64,155,242,108,171,29,205,102,203,249,197,115,178,178,100,236,45,203,213,138,98,181,96,125,255,1,220,200,48,244,241,248,237,72,181,4,180,154,253,158,
183,111,175,104,171,61,175,191,248,146,100,154,179,185,191,101,136,242,96,240,14,188,38,104,29,161,120,241,46,53,169,44,153,156,143,97,44,47,215,37,22,198,171,67,170,208,71,103,82,212,172,81,138,52,155,
112,253,207,95,188,124,245,138,23,95,124,67,154,205,216,172,63,8,119,220,200,155,210,71,112,154,119,129,110,63,144,101,19,92,24,217,62,238,8,193,145,23,11,138,229,9,243,249,138,199,181,120,231,149,66,
60,227,94,78,24,110,180,52,85,197,56,58,33,77,26,77,190,92,113,241,159,75,110,223,253,19,253,246,18,230,82,177,42,81,107,35,206,145,161,231,239,191,254,230,236,201,57,23,159,126,202,195,251,91,134,161,
149,176,145,15,226,36,83,234,168,211,42,21,142,4,70,249,239,85,236,150,182,248,200,224,73,82,137,212,31,130,117,58,114,127,8,30,165,29,77,181,97,253,240,200,235,239,190,103,121,250,132,166,222,49,244,
93,76,243,138,60,21,144,124,134,49,114,47,78,116,224,230,250,142,105,158,9,99,199,36,156,158,157,227,134,129,97,236,209,218,31,23,186,38,73,232,219,142,170,222,210,108,119,164,233,84,130,85,94,246,22,
105,146,96,199,94,166,90,219,199,192,25,228,101,142,39,208,85,13,55,87,111,241,202,112,254,236,57,90,27,198,190,19,146,107,8,120,167,197,217,163,252,177,217,205,197,2,246,32,164,194,8,31,149,79,163,18,
148,49,66,32,141,174,34,239,173,64,209,34,99,201,181,53,191,254,242,7,159,125,243,45,101,49,7,219,19,220,72,98,164,11,58,132,131,171,69,145,101,41,137,54,172,239,238,217,108,31,89,158,46,227,210,61,97,
126,242,17,97,24,36,119,18,45,195,147,137,33,203,18,234,199,134,166,169,25,246,45,38,203,72,141,66,233,9,197,106,133,235,123,188,27,165,159,214,201,32,60,153,166,228,197,12,156,103,183,217,112,115,125,
77,185,58,101,177,90,161,188,197,58,203,224,70,148,143,144,72,109,208,24,100,173,37,80,201,160,136,57,166,104,233,77,50,33,103,70,12,139,60,26,2,70,41,254,5,10,89,140,11,245,67,86,34,0,0,0,0,73,69,78,
68,174,66,96,130,0,0};

const char* bitManglerEditor::metal2_png = (const char*) resource_bitManglerEditor_metal2_png;
const int bitManglerEditor::metal2_pngSize = 141532;

// JUCER_RESOURCE: power_off_png, 3278, "power_off.png"
static const unsigned char resource_bitManglerEditor_power_off_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,48,0,0,0,48,8,6,0,0,0,87,2,249,135,0,0,0,1,115,82,71,66,0,174,206,28,233,0,
0,0,6,98,75,71,68,0,255,0,255,0,255,160,189,167,147,0,0,0,9,112,72,89,115,0,0,11,19,0,0,11,19,1,0,154,156,24,0,0,0,7,116,73,77,69,7,216,6,17,20,0,21,35,174,30,255,0,0,12,78,73,68,65,84,104,222,237,89,
123,108,84,247,149,254,126,247,49,51,247,225,121,120,198,246,216,198,6,131,227,52,134,144,218,91,3,33,212,118,66,210,150,5,66,218,70,219,135,18,117,217,85,165,253,47,85,87,187,85,168,20,85,187,77,155,
170,90,105,171,236,127,43,181,43,209,52,73,75,160,137,189,171,130,146,54,217,45,193,20,26,35,200,98,192,15,108,131,31,243,158,185,115,223,207,254,225,220,95,141,180,155,98,66,218,84,226,72,87,119,52,51,
154,57,223,57,223,57,231,251,157,11,220,177,59,118,199,254,172,141,220,206,31,123,252,137,39,249,106,165,126,95,165,92,234,247,92,231,46,6,104,34,132,68,60,207,183,2,160,196,241,145,233,100,99,250,108,
50,213,112,238,149,23,14,59,31,9,0,95,248,202,223,144,220,114,97,135,81,175,125,85,20,98,143,38,19,13,233,214,108,11,50,153,12,100,89,6,195,48,176,44,11,213,106,21,185,92,14,139,75,203,80,234,90,217,113,
189,145,120,99,250,223,91,219,155,222,126,233,71,255,17,252,73,0,60,248,233,253,219,28,75,255,110,107,115,230,193,254,190,143,147,205,155,55,163,163,163,3,169,84,10,177,88,12,60,207,131,16,2,223,247,97,
219,54,84,85,69,161,80,192,149,43,87,48,62,62,142,243,231,223,13,20,205,248,117,67,170,241,31,223,58,241,159,99,127,52,0,159,253,210,147,209,194,242,242,179,45,233,212,215,134,6,119,177,3,3,3,232,232,
232,64,67,67,3,56,142,3,195,48,96,24,6,132,220,248,243,190,239,195,243,60,88,150,133,82,169,132,137,137,9,188,249,230,155,56,253,155,51,158,237,145,231,219,214,119,30,122,245,165,31,27,31,42,128,61,143,
253,85,179,169,42,175,245,223,183,101,251,167,62,245,8,238,190,251,110,196,227,113,240,60,79,29,7,0,66,8,189,0,32,8,2,122,249,190,79,179,146,203,229,112,234,212,41,140,140,140,226,218,82,254,55,233,230,
214,3,39,70,142,44,223,172,63,236,90,156,127,100,255,231,219,125,219,124,107,247,240,174,251,246,237,219,139,238,238,110,72,146,68,163,29,58,27,190,62,126,252,56,158,122,234,41,196,227,113,116,119,119,
83,32,225,157,16,2,81,20,209,214,214,134,246,246,86,148,139,249,246,217,217,171,143,110,254,248,182,159,207,76,78,40,183,21,192,190,199,191,148,244,76,253,245,7,135,30,232,221,189,123,55,218,218,218,192,
243,60,117,104,181,133,145,30,27,27,131,40,138,16,69,17,189,189,189,55,100,32,188,123,158,7,66,8,18,137,36,178,217,44,74,197,124,122,126,126,126,207,95,220,255,201,151,175,92,188,160,223,22,0,95,248,202,
65,82,43,149,127,50,208,119,239,240,208,208,16,178,217,44,24,134,129,239,251,32,132,220,16,213,213,87,169,84,130,235,186,232,232,232,192,250,245,235,111,112,222,243,60,120,158,7,215,117,225,186,46,60,
207,131,44,203,72,165,82,88,188,62,223,180,184,152,187,119,199,224,240,139,19,23,206,189,111,135,98,110,6,64,110,185,248,215,29,109,205,159,237,235,235,67,42,149,130,239,251,112,28,7,158,231,193,182,109,
56,142,3,199,113,224,186,46,125,29,126,30,58,23,58,186,218,97,219,182,97,154,38,76,211,132,227,56,240,125,31,93,93,93,24,30,30,134,24,101,247,44,47,46,253,237,7,206,192,190,199,191,220,64,92,123,100,219,
64,191,180,113,227,70,136,162,120,3,21,60,207,163,81,85,20,5,47,190,248,34,158,127,254,121,184,174,139,88,44,134,98,177,136,100,50,137,51,103,206,224,185,231,158,67,62,159,71,103,103,39,24,134,129,235,
186,176,109,27,182,109,83,80,12,195,64,146,36,84,171,21,204,94,157,221,217,183,227,129,31,78,78,188,171,223,50,128,108,107,199,55,218,179,233,125,155,55,111,70,50,153,188,161,16,125,223,135,235,186,240,
125,31,99,99,99,120,230,153,103,144,203,229,208,217,217,137,68,34,1,81,20,81,44,22,17,143,199,81,173,86,225,56,14,206,159,63,143,151,95,126,25,233,116,26,205,205,205,176,44,139,130,88,29,140,32,8,48,53,
121,89,172,213,53,127,97,254,234,27,183,4,224,192,23,159,136,24,245,218,143,55,117,173,111,88,93,180,190,239,223,0,224,196,137,19,56,124,248,48,250,250,250,48,52,52,132,189,123,247,162,183,183,23,115,
115,115,40,20,10,136,199,227,24,28,28,196,150,45,91,144,72,36,64,8,193,232,232,40,92,215,197,186,117,235,160,235,58,52,77,131,97,24,176,44,139,82,48,151,203,97,113,113,249,99,247,239,26,254,183,75,23,
47,184,255,151,143,220,251,1,80,170,245,221,129,103,183,241,60,15,85,85,17,137,68,168,211,142,227,128,97,24,92,188,120,17,35,35,35,216,190,125,59,6,7,7,209,213,213,5,85,85,161,105,26,116,93,135,101,89,
48,77,19,229,114,25,158,231,97,235,214,173,72,167,211,224,121,30,199,143,31,135,40,138,232,233,233,65,189,94,135,109,219,96,24,6,28,199,65,215,117,196,227,113,184,182,145,41,85,170,159,1,112,108,205,25,
72,53,54,125,141,103,252,109,141,141,141,180,183,135,41,118,93,23,154,166,225,133,23,94,64,79,79,15,118,238,220,137,76,38,131,92,46,7,69,81,160,105,26,242,249,60,74,165,18,149,21,154,166,161,92,46,35,
22,139,33,147,201,64,215,117,140,141,141,161,171,171,11,154,166,161,90,173,66,85,85,168,170,10,195,48,80,169,84,176,176,112,29,166,229,24,7,191,250,196,107,39,223,58,185,182,12,24,186,58,204,68,89,20,
139,69,234,60,0,120,158,7,142,227,112,254,252,121,196,227,113,180,181,181,65,146,36,204,206,206,194,178,44,184,238,74,182,171,213,42,116,93,71,189,94,199,194,194,2,60,207,3,203,178,224,121,30,77,77,77,
104,111,111,71,161,80,192,219,111,191,141,141,27,55,210,122,112,156,21,161,90,175,215,65,8,129,161,171,187,190,247,79,223,11,214,68,161,207,125,241,137,216,185,223,158,237,226,9,143,98,177,8,0,212,177,
88,44,6,150,101,49,51,51,3,73,146,208,210,210,130,169,169,41,74,153,32,8,224,56,14,116,93,135,174,235,168,213,106,148,215,60,207,67,16,4,40,138,130,84,42,5,65,16,144,203,229,144,76,38,97,89,22,52,77,67,
173,86,3,195,48,20,136,101,89,235,63,247,229,39,227,71,127,114,88,185,105,0,134,101,55,17,4,98,52,26,133,36,73,224,56,14,134,97,32,151,203,81,32,142,227,128,16,130,197,197,69,84,42,21,152,166,9,195,48,
194,63,5,199,113,48,77,19,170,170,66,81,20,10,222,48,12,56,142,3,65,16,192,48,12,130,32,192,220,220,28,92,215,133,97,24,176,109,27,137,68,2,209,104,20,162,40,162,170,168,188,90,215,27,1,220,60,0,130,160,
53,76,119,60,30,71,60,30,7,203,178,240,125,159,22,41,203,174,148,208,196,196,4,141,186,97,24,180,199,55,52,52,192,52,77,104,154,70,65,187,174,11,69,81,232,247,68,81,4,199,113,80,20,133,214,153,36,73,16,
4,129,2,230,57,14,12,75,186,0,204,222,52,128,192,7,199,115,28,56,142,163,162,139,101,89,216,182,13,158,231,193,113,28,60,207,131,97,24,212,185,80,141,6,65,64,7,146,97,24,96,89,22,170,170,66,16,4,4,65,
128,72,36,66,131,97,24,6,56,142,131,36,73,8,130,0,60,207,195,247,125,42,203,163,209,40,125,111,77,53,192,48,168,115,28,143,104,52,10,66,8,189,51,12,67,117,127,189,94,71,173,86,67,34,145,0,199,113,240,
125,31,177,88,140,214,2,33,4,123,247,238,197,169,83,167,168,3,177,88,12,97,87,171,213,106,168,84,42,144,101,25,146,36,81,74,134,45,26,0,120,158,71,36,18,1,1,41,174,17,0,89,228,120,62,224,121,158,132,195,
75,150,101,248,190,143,104,52,10,203,178,192,48,12,114,185,28,4,65,64,58,157,166,67,200,182,109,16,66,80,169,84,112,228,200,17,4,65,0,65,16,192,113,28,100,89,134,40,138,224,249,149,230,96,154,38,214,173,
91,7,65,16,168,46,18,69,17,182,109,211,137,207,114,92,16,139,242,165,53,1,24,121,229,167,165,129,237,15,44,177,44,219,198,243,60,109,129,177,88,12,190,239,67,16,4,200,178,140,203,151,47,163,88,44,162,
183,183,151,242,59,156,21,97,22,88,150,133,32,8,104,110,110,70,58,157,94,137,40,33,152,155,155,131,231,121,104,109,109,165,197,31,170,219,176,166,124,223,7,195,178,229,87,127,246,210,226,154,39,113,0,
156,11,130,160,141,231,121,170,129,24,134,1,203,178,96,89,22,146,36,33,155,205,98,106,106,10,179,179,179,216,178,101,11,56,142,3,207,243,176,109,27,178,44,211,218,144,101,25,137,68,2,178,44,131,101,89,
140,143,143,163,90,173,162,171,171,11,77,77,77,40,151,203,96,89,150,78,225,104,52,74,85,44,192,140,255,127,62,190,47,0,134,101,223,48,12,243,47,195,35,160,227,56,180,152,195,34,28,30,30,198,194,194,2,
206,158,61,139,84,42,133,246,246,118,196,98,49,216,182,189,242,7,239,53,1,65,16,32,8,2,8,33,152,158,158,198,201,147,39,145,78,167,49,56,56,8,0,84,166,132,65,10,179,96,219,14,8,195,188,126,75,231,129,84,
42,126,76,51,45,207,52,77,90,92,97,127,23,4,1,44,203,34,157,78,227,225,135,31,134,44,203,24,29,29,197,59,239,188,131,88,44,134,84,42,69,219,97,56,71,8,33,56,125,250,52,142,29,59,6,89,150,241,208,67,15,
161,185,185,153,102,141,227,86,226,25,141,70,233,32,211,77,203,79,38,227,199,110,73,141,78,79,94,169,182,180,182,125,82,136,70,54,134,206,132,173,146,231,121,176,44,11,211,52,177,97,195,6,164,82,41,204,
207,207,99,106,106,10,231,206,157,163,252,119,28,7,165,82,9,23,46,92,192,232,232,40,102,102,102,144,201,100,176,127,255,126,244,247,247,67,85,85,170,112,77,211,132,235,186,32,132,80,1,88,173,171,255,115,
242,173,95,253,203,45,111,37,134,118,63,188,199,54,173,255,250,88,79,55,90,90,90,232,6,130,231,87,90,108,120,172,12,59,212,200,200,8,46,93,186,4,77,211,96,219,246,74,17,50,12,34,145,8,68,81,196,61,247,
220,131,3,7,14,64,146,36,40,138,66,23,95,161,136,179,109,27,134,97,160,80,40,96,106,250,42,184,72,228,177,255,254,213,27,175,222,82,13,0,64,58,149,248,197,236,220,245,95,23,10,197,93,177,88,12,209,104,
148,14,52,215,117,41,53,138,197,34,34,145,8,14,30,60,8,203,178,48,57,57,137,107,215,174,193,48,12,8,130,128,246,246,118,108,218,180,9,130,32,96,105,105,9,213,106,21,97,115,176,44,11,186,174,83,169,174,
170,42,74,165,50,76,219,62,187,161,61,59,242,129,247,66,143,236,249,116,95,33,87,58,125,215,166,46,62,155,205,34,153,76,210,232,135,84,34,132,208,137,42,138,34,26,26,26,32,138,34,34,145,8,108,219,70,189,
94,71,165,82,161,82,217,113,28,202,249,176,65,24,134,1,85,85,145,207,231,49,57,125,213,205,52,53,238,124,253,248,137,51,31,120,43,49,51,53,189,220,221,115,23,147,207,23,134,133,88,148,238,127,126,223,
230,64,123,118,72,41,215,117,233,96,50,12,131,158,182,52,77,131,162,40,52,131,225,21,58,95,42,149,48,53,115,21,146,36,62,247,230,47,127,121,248,15,249,198,225,38,173,165,57,243,236,194,226,242,142,43,
83,211,159,217,228,121,112,28,135,202,234,80,38,175,62,164,135,26,38,92,191,132,128,234,245,58,12,195,160,83,54,236,54,166,105,162,90,173,98,122,102,22,145,8,127,34,219,218,242,173,219,186,216,154,184,
56,225,127,98,160,255,53,203,178,134,151,150,115,29,33,247,67,205,18,70,62,60,248,132,59,80,211,52,233,33,37,60,236,132,59,33,207,243,168,90,45,149,202,152,154,185,10,65,136,156,206,102,155,14,28,61,114,
84,191,173,0,0,224,210,196,101,123,96,219,39,126,234,251,254,214,235,11,139,61,174,235,130,97,126,191,3,13,41,21,210,105,245,146,43,220,94,172,222,9,25,134,1,69,81,176,180,180,140,249,235,11,104,108,140,
255,162,185,57,243,216,207,143,190,90,251,80,118,163,43,153,184,100,239,184,255,254,151,120,158,181,202,149,202,174,124,190,200,185,174,3,255,189,149,200,234,101,86,184,38,89,205,243,144,235,181,90,13,
185,124,30,179,243,215,96,217,150,157,205,54,253,115,38,147,249,187,87,126,118,244,195,221,78,175,182,71,31,123,180,87,81,148,239,151,43,181,61,174,227,18,89,146,144,76,36,32,203,18,213,252,171,11,222,
113,28,212,85,21,149,74,13,170,166,130,227,216,160,177,49,121,188,161,161,225,31,238,189,119,235,255,126,231,219,207,174,249,65,199,7,126,66,243,245,191,255,58,153,158,153,238,215,52,253,160,174,235,159,
87,85,45,187,34,167,195,103,4,43,170,208,123,143,82,145,8,7,89,150,115,130,32,28,149,36,233,135,93,27,54,188,243,131,127,253,129,255,71,127,66,51,62,62,78,250,250,250,104,196,158,254,230,33,178,184,184,
200,215,106,213,94,219,182,7,28,199,233,246,61,47,11,32,2,66,92,134,97,150,121,158,159,140,70,163,191,21,69,233,221,206,206,78,251,187,207,126,39,192,71,213,14,29,58,116,67,112,158,62,244,52,193,29,187,
99,31,81,123,229,181,35,119,248,249,167,178,223,1,155,177,97,84,103,203,85,192,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* bitManglerEditor::power_off_png = (const char*) resource_bitManglerEditor_power_off_png;
const int bitManglerEditor::power_off_pngSize = 3278;

// JUCER_RESOURCE: power_on_png, 3724, "power_on.png"
static const unsigned char resource_bitManglerEditor_power_on_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,48,0,0,0,48,8,6,0,0,0,87,2,249,135,0,0,0,1,115,82,71,66,0,174,206,28,233,0,0,
0,6,98,75,71,68,0,255,0,255,0,255,160,189,167,147,0,0,0,9,112,72,89,115,0,0,11,19,0,0,11,19,1,0,154,156,24,0,0,0,7,116,73,77,69,7,216,6,17,20,0,12,71,197,182,63,0,0,14,12,73,68,65,84,104,222,237,154,123,
172,101,117,117,199,63,191,199,126,157,199,125,223,185,51,119,96,134,25,1,65,137,101,70,28,180,88,29,81,162,160,182,22,173,37,105,137,154,94,107,210,54,165,209,164,134,49,49,181,169,37,54,109,45,177,127,
180,141,181,169,52,169,80,71,69,196,138,175,138,21,45,40,12,21,124,49,220,225,61,115,223,231,181,207,126,254,30,253,227,12,86,71,24,102,6,38,214,164,191,100,103,159,100,159,179,206,250,236,181,246,239,
183,214,239,187,225,255,199,207,119,136,211,101,120,193,239,255,25,219,31,21,111,246,255,167,1,142,113,90,252,196,249,73,199,253,115,13,35,78,131,243,242,168,93,113,140,125,127,244,112,79,130,60,23,16,
226,39,239,218,169,26,60,106,67,100,255,112,79,184,246,245,197,11,187,107,235,47,182,182,62,71,34,102,133,32,116,206,151,222,251,117,165,195,197,241,233,233,111,207,188,242,121,7,154,239,218,93,1,254,
217,66,136,99,115,245,100,12,46,248,253,162,252,204,3,226,241,143,221,249,178,188,215,125,103,163,145,188,113,124,178,61,181,121,126,51,83,179,211,52,219,45,164,148,148,101,73,191,219,99,117,105,153,35,
79,44,209,239,166,27,181,49,159,27,155,158,249,232,182,133,151,222,241,241,55,237,115,207,6,64,158,74,126,46,248,253,98,241,245,255,188,167,46,178,235,182,108,154,217,187,107,247,133,226,188,23,158,207,
150,51,183,210,156,28,67,197,1,66,43,16,2,188,195,85,150,50,205,233,174,109,240,208,3,15,242,223,247,220,203,125,223,189,223,247,211,252,27,237,169,169,247,222,254,239,159,251,214,169,2,168,99,114,244,
184,16,11,126,191,232,252,225,23,163,229,239,63,244,193,185,233,201,107,94,241,138,75,212,238,139,46,98,254,204,173,196,237,6,86,67,45,61,181,116,24,225,112,120,36,130,0,69,224,36,129,21,248,210,208,95,
239,114,240,135,63,226,235,95,187,157,187,238,252,182,173,172,248,200,252,182,109,251,110,254,196,191,228,207,6,128,227,61,96,11,126,191,56,124,213,39,55,229,27,221,155,119,93,248,194,139,47,187,236,53,
156,253,252,115,105,140,181,16,129,164,150,158,74,58,114,81,83,8,67,41,44,30,144,8,66,175,136,189,38,241,154,200,73,180,19,248,210,178,182,178,202,93,223,186,147,91,63,119,43,143,29,94,185,107,230,140,
173,111,186,237,147,55,30,57,81,0,181,251,79,126,83,62,213,133,123,62,112,211,207,56,255,232,91,110,220,106,211,225,215,46,125,213,203,127,233,242,215,95,193,89,103,239,36,106,38,24,233,169,132,165,144,
134,33,21,169,168,25,136,138,123,14,126,143,79,126,254,102,124,164,24,159,153,192,63,25,228,163,39,33,5,141,70,194,214,249,173,108,157,223,66,103,109,101,235,195,139,15,189,241,130,61,47,189,249,208,15,
191,223,63,17,128,99,157,127,218,220,95,126,219,103,38,124,150,221,186,119,239,37,231,238,189,244,82,230,230,55,131,150,100,182,36,243,37,3,95,210,243,5,93,10,58,62,103,131,156,14,25,91,94,184,131,158,
44,233,248,156,142,207,232,82,208,243,5,169,47,201,124,69,225,13,50,210,156,115,254,121,92,249,214,183,240,162,11,206,59,183,179,116,228,182,95,189,250,234,217,19,5,240,199,58,126,108,250,92,253,233,235,
228,112,165,243,177,221,187,46,120,209,158,139,247,48,62,53,65,229,13,169,41,24,250,138,158,43,232,249,156,142,27,57,217,33,163,227,115,228,100,66,48,219,66,78,37,116,69,65,71,140,224,122,20,116,125,78,
223,21,164,174,32,115,21,70,120,206,216,190,141,215,94,113,57,59,182,205,159,191,252,240,227,31,191,234,250,107,213,137,70,192,31,47,247,31,251,251,111,190,253,204,45,179,111,186,112,215,46,198,38,39,
168,177,163,59,79,69,207,229,116,125,206,134,207,233,48,58,186,20,244,41,40,66,143,137,37,101,224,232,83,210,163,160,67,198,6,217,232,187,46,163,99,50,122,38,99,232,74,42,111,216,182,99,59,175,120,213,
43,105,68,234,117,143,221,114,239,239,60,85,73,114,236,51,112,220,53,224,141,111,127,219,152,200,242,207,190,100,207,238,230,89,59,119,16,53,19,42,225,40,164,101,40,106,82,81,49,144,53,169,170,233,216,
33,63,122,226,33,22,151,30,197,4,224,66,137,193,65,160,232,167,125,30,60,116,136,222,112,64,152,68,56,1,198,25,140,49,212,166,198,26,139,179,14,37,21,173,102,139,126,183,203,35,135,30,254,101,254,99,233,
159,30,184,239,187,217,211,1,232,103,154,243,123,143,175,254,209,246,173,51,179,51,179,179,32,5,105,145,225,132,162,86,146,220,91,82,111,200,113,60,177,182,194,131,135,31,33,28,111,16,77,52,49,210,163,
4,56,225,113,194,97,133,39,154,104,210,233,15,184,227,190,239,112,246,150,237,156,49,57,71,236,33,242,16,90,136,173,34,113,10,25,106,158,127,254,243,185,255,190,251,167,87,31,63,242,158,5,191,255,218,
167,243,243,184,57,118,229,53,239,138,134,75,107,55,236,220,185,189,189,101,235,60,50,210,24,229,41,148,37,15,28,67,109,73,85,205,226,234,99,60,188,118,132,241,185,105,198,166,39,25,159,156,32,142,35,
234,178,194,214,6,37,20,237,102,139,70,35,33,8,67,148,86,44,173,44,83,148,37,113,35,161,174,106,170,162,164,46,74,234,162,194,213,53,166,50,172,46,175,112,248,137,35,231,37,119,247,254,246,7,119,31,168,
159,50,2,199,3,232,28,92,126,181,183,213,124,16,134,164,217,16,153,135,168,208,97,67,77,105,37,185,245,28,78,55,56,220,93,101,98,110,154,177,169,9,226,40,194,25,11,53,200,220,66,81,35,173,66,42,135,247,
158,102,210,32,80,26,33,36,203,171,27,104,173,153,13,199,16,117,137,30,214,196,57,196,70,81,20,57,237,241,49,76,93,204,172,62,188,252,58,224,83,39,29,129,201,169,153,107,2,229,247,76,205,76,35,180,196,
133,146,58,240,84,161,39,15,28,169,172,89,92,126,140,214,204,56,99,147,227,68,58,192,22,53,20,22,89,90,76,63,167,238,101,132,78,18,162,112,198,97,141,65,42,137,142,2,0,214,55,54,104,196,49,38,175,200,
251,67,138,126,70,222,79,41,210,156,238,122,135,35,143,63,78,94,84,197,59,22,126,235,230,59,110,191,227,228,34,144,15,211,189,210,107,214,55,214,17,177,198,196,130,177,182,130,26,42,171,57,178,209,37,
104,70,68,73,140,150,138,106,80,32,74,131,40,44,190,242,216,126,138,25,164,248,49,48,133,199,104,240,145,194,39,26,213,8,9,147,152,176,89,178,220,93,103,220,69,96,74,252,112,136,221,200,16,195,154,52,
29,32,132,160,24,166,151,172,127,96,15,252,233,73,164,208,149,87,253,118,124,239,61,119,239,8,3,63,2,72,52,166,33,49,19,33,50,106,98,163,136,180,204,208,19,13,194,48,164,72,51,252,176,194,15,42,68,90,
227,135,21,85,90,80,13,82,170,212,225,91,37,38,20,136,118,132,28,143,168,157,65,135,26,21,104,202,116,72,97,193,150,57,229,160,199,224,200,42,98,80,81,165,163,201,167,44,203,237,157,223,189,117,12,232,
157,48,64,94,86,179,2,223,8,195,136,102,179,137,10,2,202,170,164,219,239,97,85,14,170,129,75,70,229,64,89,148,152,97,129,235,22,212,107,41,190,91,80,111,164,200,218,83,229,37,65,238,200,67,5,173,0,109,
90,40,233,176,190,70,38,225,168,90,21,208,31,166,152,126,143,172,211,161,24,12,104,88,77,24,69,52,26,13,58,157,65,48,88,31,76,157,20,128,80,204,43,165,8,130,128,118,187,77,187,221,70,182,98,156,146,20,
214,96,203,2,217,106,0,48,76,83,124,86,99,122,67,202,181,46,110,61,163,90,79,73,208,148,89,129,54,163,53,65,212,49,81,36,33,240,56,66,164,183,40,37,17,82,82,85,21,166,174,17,66,144,196,9,177,81,120,87,
19,197,49,129,214,72,216,1,60,116,194,0,190,246,42,208,10,173,245,200,104,146,32,226,136,74,73,148,244,56,49,90,196,173,181,120,239,241,214,33,188,7,231,113,149,65,24,71,28,133,228,101,138,52,158,188,
202,73,154,33,222,122,180,144,72,53,234,21,172,177,8,15,90,42,80,154,32,138,49,129,65,123,129,8,5,81,20,17,4,1,206,185,19,42,230,254,247,130,100,160,117,64,20,69,8,4,81,16,18,40,77,24,4,196,65,72,28,132,
72,4,166,54,72,41,209,129,70,7,1,141,102,131,48,142,16,74,33,164,224,149,123,247,226,5,163,74,84,10,130,32,32,105,54,136,227,24,165,20,214,88,164,135,56,140,72,194,136,40,8,137,116,128,16,2,188,39,208,
154,48,12,16,142,213,147,90,7,164,20,135,181,14,124,160,181,240,222,227,156,35,9,34,148,150,200,88,83,134,10,164,167,50,21,78,43,162,40,196,37,22,155,24,84,18,18,141,53,24,244,115,190,116,251,87,64,75,
146,169,246,104,230,105,39,168,40,64,69,33,85,93,224,106,67,172,66,2,41,48,82,83,187,17,76,149,13,241,110,84,122,43,173,125,28,5,235,39,5,112,203,254,155,214,95,114,241,37,71,148,82,243,129,214,88,99,
81,66,162,130,8,169,21,82,43,84,172,72,135,5,117,85,209,26,111,34,218,146,186,242,248,188,38,84,154,42,12,144,205,16,21,6,68,227,77,218,115,83,196,19,45,136,3,156,146,228,253,28,103,44,141,36,194,123,
139,68,33,85,128,23,22,47,53,53,6,231,28,82,170,141,155,255,237,19,135,79,122,37,246,130,123,189,247,243,90,107,112,30,172,67,121,65,224,37,66,104,194,48,33,42,6,100,166,38,47,115,198,154,77,164,27,117,
96,46,137,136,198,91,224,28,82,43,194,177,6,225,100,19,57,22,227,18,69,63,79,49,117,77,44,53,13,29,99,68,141,147,1,90,135,148,148,132,65,136,21,21,198,24,16,242,192,211,22,115,199,173,181,149,250,106,
158,229,87,120,235,240,214,98,202,154,208,9,132,147,8,43,49,149,99,243,228,44,15,175,29,166,223,239,19,76,5,36,237,136,88,43,124,51,65,24,135,68,130,20,168,36,64,52,66,92,36,25,86,25,221,110,23,237,5,
115,211,51,168,204,33,156,192,163,48,40,106,15,30,129,119,142,170,172,16,82,126,229,68,59,178,159,46,37,38,198,62,53,44,74,91,228,5,194,11,76,89,81,231,37,129,151,196,104,2,3,77,21,177,105,124,26,41,36,
171,107,171,116,179,1,180,66,212,116,19,49,213,128,169,24,49,21,227,90,1,54,150,108,164,61,150,87,87,145,8,102,199,167,105,233,152,192,8,66,35,208,86,32,140,35,84,1,18,65,93,215,100,69,233,38,166,39,62,
253,180,253,192,241,0,22,15,62,208,157,155,159,255,149,36,142,118,54,91,45,226,70,130,84,18,161,21,58,212,136,64,81,59,67,107,172,141,212,146,44,207,201,138,156,254,112,48,234,3,180,192,42,40,189,161,
151,167,172,108,172,145,229,57,129,84,108,158,156,101,83,107,10,145,86,232,220,35,115,139,237,231,216,172,66,24,79,153,21,108,172,173,211,237,15,254,243,142,175,126,245,47,79,41,133,0,218,99,237,15,47,
175,172,189,102,114,106,146,102,187,73,220,76,112,121,69,213,19,8,34,168,5,149,179,76,180,155,180,206,104,242,196,234,18,195,60,163,63,232,211,235,123,188,247,71,103,53,137,68,48,150,52,57,99,118,11,177,
215,248,94,65,88,122,68,225,48,89,13,149,67,121,137,169,13,89,154,178,182,222,161,213,106,125,248,120,254,61,35,192,25,11,151,124,225,7,127,253,133,111,172,174,172,189,60,74,18,194,36,34,14,20,118,88,
226,189,67,216,0,105,29,117,105,160,169,57,103,203,118,106,28,253,225,128,172,200,177,206,162,164,34,137,99,218,73,139,80,40,202,94,70,153,101,68,21,248,220,227,250,37,85,47,195,151,6,91,214,164,131,148,
245,181,13,138,178,250,206,185,191,126,209,45,124,229,203,207,110,115,247,178,55,92,190,123,117,105,237,191,206,57,103,103,48,55,191,153,241,233,73,130,86,140,9,4,178,21,66,35,192,37,10,26,1,170,25,33,
147,0,157,132,168,64,35,149,194,29,157,0,170,172,192,12,75,220,176,194,103,21,65,5,178,112,136,188,198,166,21,229,32,99,216,237,179,186,180,194,193,131,135,204,204,166,169,75,190,252,249,219,238,58,110,
79,124,34,0,151,254,232,67,75,253,27,15,168,149,149,213,189,73,20,35,142,114,59,99,112,198,34,28,184,202,64,237,16,198,163,157,64,86,126,212,23,20,6,145,91,200,106,68,90,227,186,57,229,250,0,215,47,240,
105,133,75,75,124,94,83,244,51,134,189,1,27,43,107,60,184,120,136,102,179,241,161,179,191,248,123,55,28,187,63,117,202,219,235,111,125,239,59,131,71,191,249,131,91,170,170,122,237,243,118,238,96,98,102,
138,184,153,32,163,128,160,17,161,146,16,17,41,8,53,65,35,66,199,163,8,8,41,240,206,227,106,67,93,84,20,253,33,85,154,227,43,139,168,28,210,121,76,94,81,12,115,122,235,29,22,23,31,34,8,244,151,182,93,
124,222,27,110,250,171,127,172,158,113,103,238,68,1,94,246,141,247,121,245,181,71,62,91,14,242,189,71,150,150,207,12,148,70,34,144,8,132,243,120,99,145,14,148,1,42,11,133,193,14,75,236,160,192,14,43,252,
176,58,250,121,148,66,54,171,112,69,77,49,200,201,250,41,235,43,235,60,184,120,136,36,10,239,220,114,214,150,95,155,252,187,43,179,103,186,251,39,45,112,44,248,253,162,243,142,155,218,171,143,46,255,235,
218,218,198,21,155,54,109,98,110,110,150,246,120,155,184,217,24,229,124,160,145,74,18,68,71,159,1,41,17,8,156,181,120,235,142,54,239,21,69,158,83,102,57,195,193,144,213,149,53,150,87,86,153,153,153,184,
109,102,235,166,171,166,62,126,85,239,68,183,249,79,90,161,89,240,251,69,126,253,183,228,202,23,191,251,222,213,149,181,247,91,235,163,185,185,77,76,77,77,210,108,53,9,162,8,165,71,125,68,16,6,40,173,
17,8,188,119,212,101,69,89,148,20,89,78,58,72,217,232,116,88,94,94,65,73,81,205,206,78,95,55,253,178,115,255,172,245,254,75,237,201,104,20,167,44,49,45,248,253,98,229,55,110,120,65,191,211,253,139,141,
78,239,114,99,172,104,181,154,76,140,79,208,106,53,8,195,17,136,16,163,191,176,198,80,215,53,131,65,74,167,211,35,29,166,104,37,253,212,212,196,109,237,241,241,63,222,249,251,151,125,239,250,87,255,193,
73,11,29,207,90,35,123,247,123,222,45,22,31,57,244,226,225,96,248,246,108,152,189,57,29,14,55,87,85,141,16,114,180,106,31,149,248,172,29,109,171,132,161,162,213,108,45,39,141,228,83,205,70,243,99,59,206,
58,235,158,235,255,230,250,83,87,104,78,245,135,7,14,28,16,187,118,237,250,113,168,175,125,223,62,113,248,240,225,160,215,235,190,160,170,171,61,117,93,63,207,89,187,25,8,17,194,72,41,151,2,29,28,140,
162,232,238,70,163,121,255,182,109,219,170,235,62,248,231,207,94,169,92,240,251,197,177,199,115,161,90,238,219,183,239,167,236,92,187,239,218,211,162,73,63,233,176,56,93,58,238,233,30,199,106,186,63,134,
121,174,34,241,243,0,56,173,175,32,156,22,128,214,192,63,165,186,254,139,16,5,13,136,180,45,120,138,215,2,126,33,198,255,0,39,218,97,37,100,120,205,143,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* bitManglerEditor::power_on_png = (const char*) resource_bitManglerEditor_power_on_png;
const int bitManglerEditor::power_on_pngSize = 3724;
