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

#include "MidiPadsPluginEditor.h"
#include "../../../resources/Resources.h"

//==============================================================================
MidiPadsPluginEditor::MidiPadsPluginEditor (MidiPadsPlugin* owner_)
    : PluginEditorComponent (owner_),
      owner (owner_)
{
    static OldSchoolLookAndFeel myLookAndFeel;
    setLookAndFeel (&myLookAndFeel);

    setMouseClickGrabsKeyboardFocus (false);

    bool useaft = false;
    if (owner->getParameter(kSendAft)>=0.5) useaft=true;

    showdots = true;
    dontsend = false;

    bool usex[numPads];
    bool usey[numPads];
     
    for (int i = 0; i < numPads; i++)
    {
        toggled[i] = false;
        usex[i] = owner->UseX[i] >= 0.5;
        usey[i] = owner->UseY[i] >= 0.5;

        addAndMakeVisible (midiPad[i] = new MidiPad());
        midiPad[i]->setName(String(i));
        midiPad[i]->setButtonText (String::empty);
        midiPad[i]->setTriggeredOnMouseDown(false);
        midiPad[i]->addButtonListener (this);
        midiPad[i]->addMouseListener (this, true);
        midiPad[i]->setToggleState(owner->togglestate[i]); 
        if (showdots)
        {
            midiPad[i]->drawableButton->showdot=true;
            if (!usex[i]) {
                midiPad[i]->drawableButton->x=0.5f;
                midiPad[i]->drawableButton->showx=false;
            }
            else {
                midiPad[i]->drawableButton->x=owner->getParameter(i+xpos);
                midiPad[i]->drawableButton->showx=true;
            }
            if (owner->SendOff[i]) {
                midiPad[i]->drawableButton->y=owner->Ydata2[i];
            }
            else midiPad[i]->drawableButton->y=owner->getParameter(i+ypos);
        }
        midiPad[i]->drawableButton->setHex(owner->hex);

        addAndMakeVisible (vSlider[i] = new Slider (T("new slider")));
        vSlider[i]->setRange (0, 127, 1);
        vSlider[i]->setSliderStyle (Slider::LinearBar);
        vSlider[i]->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
        vSlider[i]->addListener (this);

        addAndMakeVisible (nSlider[i] = new Slider (T("note slider")));
        nSlider[i]->setRange (0, 127, 1);
        nSlider[i]->setSliderStyle (Slider::LinearBar);
        nSlider[i]->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
        nSlider[i]->addListener (this);

        addAndMakeVisible (ySlider[i] = new Slider (T("y-cc slider")));
        ySlider[i]->setRange (0, 127, 1);
        ySlider[i]->setSliderStyle (Slider::LinearBar);
        ySlider[i]->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
        ySlider[i]->addListener (this);

        addAndMakeVisible (oSlider[i] = new Slider (T("new slider")));
        oSlider[i]->setRange (0, 127, 1);
        oSlider[i]->setSliderStyle (Slider::LinearBar);
        oSlider[i]->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
        oSlider[i]->addListener (this);

        addAndMakeVisible (triggerSlider[i] = new Slider (T("new slider")));
        triggerSlider[i]->setRange (0, 127, 1);
        triggerSlider[i]->setSliderStyle (Slider::LinearBar);
        triggerSlider[i]->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
        triggerSlider[i]->addListener (this);

        addAndMakeVisible (xSlider[i] = new Slider (T("new slider")));
        xSlider[i]->setRange (0, 127, 1);
        xSlider[i]->setSliderStyle (Slider::LinearBar);
        xSlider[i]->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
        xSlider[i]->addListener (this);

        addAndMakeVisible (xoSlider[i] = new Slider (T("new slider")));
        xoSlider[i]->setRange (0, 127, 1);
        xoSlider[i]->setSliderStyle (Slider::LinearBar);
        xoSlider[i]->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
        xoSlider[i]->addListener (this);

        addAndMakeVisible (textEditor[i] = new TextEditor (T("new text editor")));
        textEditor[i]->setMultiLine (false);
        textEditor[i]->setReturnKeyStartsNewLine (false);
        textEditor[i]->setReadOnly (false);
        textEditor[i]->setScrollbarsShown (false);
        textEditor[i]->setCaretVisible (true);
        textEditor[i]->setPopupMenuEnabled (false);
        textEditor[i]->setSelectAllWhenFocused(true);
        textEditor[i]->addListener (this);

        colourSelector1[i] = new ColourSelector(ColourSelector::showColourAtTop|ColourSelector::showSliders|ColourSelector::showColourspace);
        colourSelector1[i]->setName (String(i));
        colourSelector1[i]->setCurrentColour (owner->padcolor[i]);
        colourSelector1[i]->addChangeListener (this);

        lastx[i]=0;
        lasty[i]=0;
     }

    addAndMakeVisible (slider = new Slider (T("new slider")));
    slider->setTooltip (T("Hue"));
    slider->setRange (0, 1, 0);
    slider->setSliderStyle (Slider::LinearBar);
    slider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    slider->addListener (this);
    slider->setMouseClickGrabsKeyboardFocus (false);

    addAndMakeVisible (slider2 = new Slider (T("new slider")));
    slider2->setTooltip (T("Saturation"));
    slider2->setRange (0, 1, 0);
    slider2->setSliderStyle (Slider::LinearBar);
    slider2->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    slider2->addListener (this);
    slider2->setMouseClickGrabsKeyboardFocus (false);

    addAndMakeVisible (slider3 = new Slider (T("new slider")));
    slider3->setTooltip (T("Brightness"));
    slider3->setRange (0, 1, 0);
    slider3->setSliderStyle (Slider::LinearBar);
    slider3->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    slider3->addListener (this);
    slider3->setMouseClickGrabsKeyboardFocus (false);

    addAndMakeVisible (slider4 = new Slider (T("new slider")));
    slider4->setTooltip (T("Pad Opacity"));
    slider4->setRange (0, 1, 0);
    slider4->setSliderStyle (Slider::LinearBar);
    slider4->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    slider4->addListener (this);
    slider4->setMouseClickGrabsKeyboardFocus (false);

    addAndMakeVisible (slider5 = new Slider (T("new slider")));
    slider5->setTooltip (T("Pad Roundness"));
    slider5->setRange (0, 0.5, 0);
    slider5->setSliderStyle (Slider::LinearBar);
    slider5->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    slider5->setMouseClickGrabsKeyboardFocus (false);
    slider5->addListener (this);

    addAndMakeVisible (velocitySlider = new Slider (T("new slider")));
    velocitySlider->setTooltip (T("Velocity Scale Factor"));
    velocitySlider->setRange (0, 2, 0.01);
    velocitySlider->setSliderStyle (Slider::LinearBar);
    velocitySlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    velocitySlider->setMouseClickGrabsKeyboardFocus (false);
    velocitySlider->addListener (this);

    addAndMakeVisible (valueSlider = new Slider (T("new slider")));
    valueSlider->setTooltip (T("CC Value Scale Factor"));
    valueSlider->setRange (0, 2, 0.01);
    valueSlider->setSliderStyle (Slider::LinearBar);
    valueSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    valueSlider->setMouseClickGrabsKeyboardFocus (false);
    valueSlider->addListener (this);

    addAndMakeVisible (menuButton = new TextButton(T("menu button")));
    menuButton->setButtonText (T("menu"));
    menuButton->addButtonListener (this);
    menuButton->setTriggeredOnMouseDown(true);
    menuButton->setMouseClickGrabsKeyboardFocus (false);

    addAndMakeVisible (icSlider = new Slider (T("new slider")));
    icSlider->setRange (1, 16, 1);
    icSlider->setSliderStyle (Slider::LinearBar);
    icSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    icSlider->setMouseClickGrabsKeyboardFocus (false);
    icSlider->addListener (this);

    addAndMakeVisible (cSlider = new Slider (T("new slider")));
    cSlider->setRange (1, 16, 1);
    cSlider->setSliderStyle (Slider::LinearBar);
    cSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    cSlider->setMouseClickGrabsKeyboardFocus (false);
    cSlider->addListener (this);

    squares = 16;

    owner->addChangeListener (this);
    
    // updateParametersFromFilter();
}

MidiPadsPluginEditor::~MidiPadsPluginEditor()
{
    owner->lastUIWidth = getWidth();
    owner->lastUIHeight = getHeight();

    owner->removeChangeListener (this);

    for (int i=0;i<numPads;i++) {
        owner->icon[i]=midiPad[i]->drawableButton->getName();
        owner->lastx[i]=lastx[i];
        owner->lasty[i]=lasty[i];
    }
    
    deleteAllChildren();
    setLookAndFeel (0);
}

//==============================================================================
int MidiPadsPluginEditor::getPreferredWidth ()
{
    return owner->lastUIWidth;
}

int MidiPadsPluginEditor::getPreferredHeight ()
{
    return owner->lastUIHeight;
}

bool MidiPadsPluginEditor::isResizable ()
{
    return true;
}

void MidiPadsPluginEditor::updateParameters ()
{
    updateParametersFromFilter ();
}

//==============================================================================
void MidiPadsPluginEditor::paint (Graphics& g)
{
    g.fillAll (color);
    for (int i=0;i<numPads;i++) {
        midiPad[i]->setColour(colourSelector1[i]->getCurrentColour().withAlpha(owner->contrast));
    }
}

void MidiPadsPluginEditor::resized()
{
    if (owner->hex || squares==40)
    {
        squares=40;
        for (int i=0;i<40;i++) midiPad[i]->setVisible(true);
        for (int i=40;i<numPads;i++) midiPad[i]->setVisible(false);
         midiPad[0]->setBounds (proportionOfWidth (0.0370f), proportionOfHeight (0.1504f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
         midiPad[1]->setBounds (proportionOfWidth (0.0370f), proportionOfHeight (0.3372f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
         midiPad[2]->setBounds (proportionOfWidth (0.0370f), proportionOfHeight (0.5241f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
         midiPad[3]->setBounds (proportionOfWidth (0.0370f), proportionOfHeight (0.7110f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
         midiPad[4]->setBounds (proportionOfWidth (0.1358f), proportionOfHeight (0.2438f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
         midiPad[5]->setBounds (proportionOfWidth (0.1358f), proportionOfHeight (0.4307f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
         midiPad[6]->setBounds (proportionOfWidth (0.1358f), proportionOfHeight (0.6175f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
         midiPad[7]->setBounds (proportionOfWidth (0.1358f), proportionOfHeight (0.8044f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
         midiPad[8]->setBounds (proportionOfWidth (0.2346f), proportionOfHeight (0.1504f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
         midiPad[9]->setBounds (proportionOfWidth (0.2346f), proportionOfHeight (0.3372f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
        midiPad[10]->setBounds (proportionOfWidth (0.2346f), proportionOfHeight (0.5241f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
        midiPad[11]->setBounds (proportionOfWidth (0.2346f), proportionOfHeight (0.7110f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
        midiPad[12]->setBounds (proportionOfWidth (0.3333f), proportionOfHeight (0.2438f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
        midiPad[13]->setBounds (proportionOfWidth (0.3333f), proportionOfHeight (0.4307f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
        midiPad[14]->setBounds (proportionOfWidth (0.3333f), proportionOfHeight (0.6175f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
        midiPad[15]->setBounds (proportionOfWidth (0.3333f), proportionOfHeight (0.8044f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
        midiPad[16]->setBounds (proportionOfWidth (0.4321f), proportionOfHeight (0.1504f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
        midiPad[17]->setBounds (proportionOfWidth (0.4321f), proportionOfHeight (0.3372f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
        midiPad[18]->setBounds (proportionOfWidth (0.4321f), proportionOfHeight (0.5241f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
        midiPad[19]->setBounds (proportionOfWidth (0.4321f), proportionOfHeight (0.7110f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
        midiPad[20]->setBounds (proportionOfWidth (0.5309f), proportionOfHeight (0.2438f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
        midiPad[21]->setBounds (proportionOfWidth (0.5309f), proportionOfHeight (0.4307f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
        midiPad[22]->setBounds (proportionOfWidth (0.5309f), proportionOfHeight (0.6175f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
        midiPad[23]->setBounds (proportionOfWidth (0.5309f), proportionOfHeight (0.8044f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
        midiPad[24]->setBounds (proportionOfWidth (0.6296f), proportionOfHeight (0.1504f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
        midiPad[25]->setBounds (proportionOfWidth (0.6296f), proportionOfHeight (0.3372f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
        midiPad[26]->setBounds (proportionOfWidth (0.6296f), proportionOfHeight (0.5241f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
        midiPad[27]->setBounds (proportionOfWidth (0.6296f), proportionOfHeight (0.7110f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
        midiPad[28]->setBounds (proportionOfWidth (0.7284f), proportionOfHeight (0.2438f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
        midiPad[29]->setBounds (proportionOfWidth (0.7284f), proportionOfHeight (0.4307f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
        midiPad[30]->setBounds (proportionOfWidth (0.7284f), proportionOfHeight (0.6175f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
        midiPad[31]->setBounds (proportionOfWidth (0.7284f), proportionOfHeight (0.8044f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
        midiPad[32]->setBounds (proportionOfWidth (0.8272f), proportionOfHeight (0.1504f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
        midiPad[33]->setBounds (proportionOfWidth (0.8272f), proportionOfHeight (0.3372f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
        midiPad[34]->setBounds (proportionOfWidth (0.8272f), proportionOfHeight (0.5241f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
        midiPad[35]->setBounds (proportionOfWidth (0.8272f), proportionOfHeight (0.7110f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
        midiPad[36]->setBounds (proportionOfWidth (0.1358f), proportionOfHeight (0.0584f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
        midiPad[37]->setBounds (proportionOfWidth (0.3333f), proportionOfHeight (0.0584f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
        midiPad[38]->setBounds (proportionOfWidth (0.5309f), proportionOfHeight (0.0584f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
        midiPad[39]->setBounds (proportionOfWidth (0.7284f), proportionOfHeight (0.0584f), proportionOfWidth (0.1317f), proportionOfHeight (0.1869f));
    }
    else if (squares==64)
    {
        for (int i=0;i<64;i++) midiPad[i]->setVisible(true);
         midiPad[0]->setBounds (proportionOfWidth (0.0029f), proportionOfHeight (0.1144f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
         midiPad[1]->setBounds (proportionOfWidth (0.1882f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.1144f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
         midiPad[2]->setBounds (proportionOfWidth (0.3118f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.1144f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
         midiPad[3]->setBounds (proportionOfWidth (0.4353f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.1144f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
         midiPad[4]->setBounds (proportionOfWidth (0.5000f), proportionOfHeight (0.1144f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
         midiPad[5]->setBounds (proportionOfWidth (0.6868f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.1144f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
         midiPad[6]->setBounds (proportionOfWidth (0.8118f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.1144f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
         midiPad[7]->setBounds (proportionOfWidth (0.9368f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.1144f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
         midiPad[8]->setBounds (proportionOfWidth (0.0029f), proportionOfHeight (0.2334f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
         midiPad[9]->setBounds (proportionOfWidth (0.1882f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.2334f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[10]->setBounds (proportionOfWidth (0.3118f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.2334f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[11]->setBounds (proportionOfWidth (0.4353f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.2334f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[12]->setBounds (proportionOfWidth (0.5000f), proportionOfHeight (0.2334f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[13]->setBounds (proportionOfWidth (0.6868f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.2334f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[14]->setBounds (proportionOfWidth (0.8118f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.2334f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[15]->setBounds (proportionOfWidth (0.9368f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.2334f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[16]->setBounds (proportionOfWidth (0.0029f), proportionOfHeight (0.3508f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[17]->setBounds (proportionOfWidth (0.1868f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.3508f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[18]->setBounds (proportionOfWidth (0.3103f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.3508f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[19]->setBounds (proportionOfWidth (0.4339f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.3508f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[20]->setBounds (proportionOfWidth (0.4986f), proportionOfHeight (0.3508f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[21]->setBounds (proportionOfWidth (0.6853f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.3508f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[22]->setBounds (proportionOfWidth (0.8103f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.3508f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[23]->setBounds (proportionOfWidth (0.9353f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.3508f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[24]->setBounds (proportionOfWidth (0.0014f), proportionOfHeight (0.4699f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[25]->setBounds (proportionOfWidth (0.1868f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.4699f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[26]->setBounds (proportionOfWidth (0.3103f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.4699f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[27]->setBounds (proportionOfWidth (0.4339f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.4699f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[28]->setBounds (proportionOfWidth (0.4986f), proportionOfHeight (0.4699f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[29]->setBounds (proportionOfWidth (0.6853f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.4699f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[30]->setBounds (proportionOfWidth (0.8103f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.4699f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[31]->setBounds (proportionOfWidth (0.9353f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.4699f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[32]->setBounds (proportionOfWidth (0.0043f), proportionOfHeight (0.5889f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[33]->setBounds (proportionOfWidth (0.1882f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.5889f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[34]->setBounds (proportionOfWidth (0.3118f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.5889f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[35]->setBounds (proportionOfWidth (0.4353f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.5889f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[36]->setBounds (proportionOfWidth (0.5000f), proportionOfHeight (0.5889f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[37]->setBounds (proportionOfWidth (0.6868f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.5889f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[38]->setBounds (proportionOfWidth (0.8118f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.5889f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[39]->setBounds (proportionOfWidth (0.9368f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.5889f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[40]->setBounds (proportionOfWidth (0.0029f), proportionOfHeight (0.7063f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[41]->setBounds (proportionOfWidth (0.1882f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.7063f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[42]->setBounds (proportionOfWidth (0.3118f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.7063f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[43]->setBounds (proportionOfWidth (0.4353f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.7063f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[44]->setBounds (proportionOfWidth (0.5000f), proportionOfHeight (0.7063f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[45]->setBounds (proportionOfWidth (0.6868f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.7063f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[46]->setBounds (proportionOfWidth (0.8118f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.7063f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[47]->setBounds (proportionOfWidth (0.9368f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.7063f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[48]->setBounds (proportionOfWidth (0.0029f), proportionOfHeight (0.8238f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[49]->setBounds (proportionOfWidth (0.1882f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.8238f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[50]->setBounds (proportionOfWidth (0.3118f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.8238f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[51]->setBounds (proportionOfWidth (0.4339f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.8238f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[52]->setBounds (proportionOfWidth (0.5000f), proportionOfHeight (0.8238f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[53]->setBounds (proportionOfWidth (0.6868f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.8238f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[54]->setBounds (proportionOfWidth (0.8118f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.8238f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[55]->setBounds (proportionOfWidth (0.9368f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.8238f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[56]->setBounds (proportionOfWidth (0.0029f), proportionOfHeight (0.9413f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[57]->setBounds (proportionOfWidth (0.1882f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.9413f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[58]->setBounds (proportionOfWidth (0.3118f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.9413f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[59]->setBounds (proportionOfWidth (0.4353f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.9413f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[60]->setBounds (proportionOfWidth (0.5000f), proportionOfHeight (0.9413f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[61]->setBounds (proportionOfWidth (0.6868f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.9413f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[62]->setBounds (proportionOfWidth (0.8118f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.9413f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[63]->setBounds (proportionOfWidth (0.9368f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.9413f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
    }

    else if (squares==10)
    {
        for (int i=10;i<numPads;i++) midiPad[i]->setVisible(false);
        for (int i=0;i<10;i++) midiPad[i]->setVisible(true);
        midiPad[0]->setBounds (proportionOfWidth (0.0187f), proportionOfHeight (0.1808f) - ((proportionOfHeight (0.2318f)) / 2), proportionOfWidth (0.2299f), proportionOfHeight (0.2318f));
        midiPad[1]->setBounds (proportionOfWidth (0.3779f) - ((proportionOfWidth (0.2299f)) / 2), proportionOfHeight (0.1808f) - ((proportionOfHeight (0.2318f)) / 2), proportionOfWidth (0.2299f), proportionOfHeight (0.2318f));
        midiPad[2]->setBounds (proportionOfWidth (0.6221f) - ((proportionOfWidth (0.2299f)) / 2), proportionOfHeight (0.1808f) - ((proportionOfHeight (0.2318f)) / 2), proportionOfWidth (0.2299f), proportionOfHeight (0.2318f));
        midiPad[3]->setBounds (proportionOfWidth (0.8664f) - ((proportionOfWidth (0.2299f)) / 2), proportionOfHeight (0.1808f) - ((proportionOfHeight (0.2318f)) / 2), proportionOfWidth (0.2299f), proportionOfHeight (0.2318f));
        midiPad[4]->setBounds (proportionOfWidth (0.0187f), proportionOfHeight (0.4142f) - ((proportionOfHeight (0.2318f)) / 2), proportionOfWidth (0.2299f), proportionOfHeight (0.2318f));
        midiPad[5]->setBounds (proportionOfWidth (0.3779f) - ((proportionOfWidth (0.2299f)) / 2), proportionOfHeight (0.4142f) - ((proportionOfHeight (0.2318f)) / 2), proportionOfWidth (0.2299f), proportionOfHeight (0.2318f));
        midiPad[6]->setBounds (proportionOfWidth (0.6221f) - ((proportionOfWidth (0.2299f)) / 2), proportionOfHeight (0.4142f) - ((proportionOfHeight (0.2318f)) / 2), proportionOfWidth (0.2299f), proportionOfHeight (0.2318f));
        midiPad[7]->setBounds (proportionOfWidth (0.8664f) - ((proportionOfWidth (0.2299f)) / 2), proportionOfHeight (0.4142f) - ((proportionOfHeight (0.2318f)) / 2), proportionOfWidth (0.2299f), proportionOfHeight (0.2318f));
        midiPad[8]->setBounds (proportionOfWidth (0.0187f), proportionOfHeight (0.7637f) - ((proportionOfHeight (0.4637f)) / 2), proportionOfWidth (0.4793f), proportionOfHeight (0.4637f));
        midiPad[9]->setBounds (proportionOfWidth (0.7433f) - ((proportionOfWidth (0.4720f)) / 2), proportionOfHeight (0.7637f) - ((proportionOfHeight (0.4637f)) / 2), proportionOfWidth (0.4720f), proportionOfHeight (0.4637f));
    }
    else if (squares==16)
    {
        // 16 pads
        for (int i=16;i<numPads;i++) midiPad[i]->setVisible(false);
        for (int i=0;i<16;i++) midiPad[i]->setVisible(true);
         midiPad[0]->setBounds (proportionOfWidth (0.0188f), proportionOfHeight (0.1802f) - ((proportionOfHeight (0.2313f)) / 2), proportionOfWidth (0.2293f), proportionOfHeight (0.2313f));
         midiPad[1]->setBounds (proportionOfWidth (0.3778f) - ((proportionOfWidth (0.2293f)) / 2), proportionOfHeight (0.1802f) - ((proportionOfHeight (0.2313f)) / 2), proportionOfWidth (0.2293f), proportionOfHeight (0.2313f));
         midiPad[2]->setBounds (proportionOfWidth (0.6222f) - ((proportionOfWidth (0.2293f)) / 2), proportionOfHeight (0.1802f) - ((proportionOfHeight (0.2313f)) / 2), proportionOfWidth (0.2293f), proportionOfHeight (0.2313f));
         midiPad[3]->setBounds (proportionOfWidth (0.8665f) - ((proportionOfWidth (0.2293f)) / 2), proportionOfHeight (0.1802f) - ((proportionOfHeight (0.2313f)) / 2), proportionOfWidth (0.2293f), proportionOfHeight (0.2313f));
         midiPad[4]->setBounds (proportionOfWidth (0.0187f), proportionOfHeight (0.4142f) - ((proportionOfHeight (0.2318f)) / 2), proportionOfWidth (0.2299f), proportionOfHeight (0.2318f));
         midiPad[5]->setBounds (proportionOfWidth (0.3779f) - ((proportionOfWidth (0.2299f)) / 2), proportionOfHeight (0.4142f) - ((proportionOfHeight (0.2318f)) / 2), proportionOfWidth (0.2299f), proportionOfHeight (0.2318f));
         midiPad[6]->setBounds (proportionOfWidth (0.6221f) - ((proportionOfWidth (0.2299f)) / 2), proportionOfHeight (0.4142f) - ((proportionOfHeight (0.2318f)) / 2), proportionOfWidth (0.2299f), proportionOfHeight (0.2318f));
         midiPad[7]->setBounds (proportionOfWidth (0.8664f) - ((proportionOfWidth (0.2299f)) / 2), proportionOfHeight (0.4142f) - ((proportionOfHeight (0.2318f)) / 2), proportionOfWidth (0.2299f), proportionOfHeight (0.2318f));
         midiPad[8]->setBounds (proportionOfWidth (0.0187f), proportionOfHeight (0.6476f) - ((proportionOfHeight (0.2318f)) / 2), proportionOfWidth (0.2299f), proportionOfHeight (0.2318f));
         midiPad[9]->setBounds (proportionOfWidth (0.3779f) - ((proportionOfWidth (0.2299f)) / 2), proportionOfHeight (0.6476f) - ((proportionOfHeight (0.2318f)) / 2), proportionOfWidth (0.2299f), proportionOfHeight (0.2318f));
        midiPad[10]->setBounds (proportionOfWidth (0.6221f) - ((proportionOfWidth (0.2299f)) / 2), proportionOfHeight (0.6476f) - ((proportionOfHeight (0.2318f)) / 2), proportionOfWidth (0.2299f), proportionOfHeight (0.2318f));
        midiPad[11]->setBounds (proportionOfWidth (0.8707f) - ((proportionOfWidth (0.2299f)) / 2), proportionOfHeight (0.6476f) - ((proportionOfHeight (0.2318f)) / 2), proportionOfWidth (0.2299f), proportionOfHeight (0.2318f));
        midiPad[12]->setBounds (proportionOfWidth (0.0187f), proportionOfHeight (0.8810f) - ((proportionOfHeight (0.2318f)) / 2), proportionOfWidth (0.2299f), proportionOfHeight (0.2318f));
        midiPad[13]->setBounds (proportionOfWidth (0.3779f) - ((proportionOfWidth (0.2299f)) / 2), proportionOfHeight (0.8810f) - ((proportionOfHeight (0.2318f)) / 2), proportionOfWidth (0.2299f), proportionOfHeight (0.2318f));
        midiPad[14]->setBounds (proportionOfWidth (0.6221f) - ((proportionOfWidth (0.2299f)) / 2), proportionOfHeight (0.8810f) - ((proportionOfHeight (0.2318f)) / 2), proportionOfWidth (0.2299f), proportionOfHeight (0.2318f));
        midiPad[15]->setBounds (proportionOfWidth (0.8664f) - ((proportionOfWidth (0.2299f)) / 2), proportionOfHeight (0.8810f) - ((proportionOfHeight (0.2318f)) / 2), proportionOfWidth (0.2299f), proportionOfHeight (0.2318f));
    }
    else if (squares==4)
    {
        //4 pads
        for (int i=0;i<4;i++) midiPad[i]->setVisible(true);
        midiPad[0]->setBounds (proportionOfWidth (0.2500f) - ((proportionOfWidth (0.4799f)) / 2), proportionOfHeight (0.2906f) - ((proportionOfHeight (0.4606f)) / 2), proportionOfWidth (0.4799f), proportionOfHeight (0.4606f));
        midiPad[1]->setBounds (proportionOfWidth (0.7500f) - ((proportionOfWidth (0.4799f)) / 2), proportionOfHeight (0.2906f) - ((proportionOfHeight (0.4606f)) / 2), proportionOfWidth (0.4799f), proportionOfHeight (0.4606f));
        midiPad[2]->setBounds (proportionOfWidth (0.2500f) - ((proportionOfWidth (0.4799f)) / 2), proportionOfHeight (0.7604f) - ((proportionOfHeight (0.4606f)) / 2), proportionOfWidth (0.4799f), proportionOfHeight (0.4606f));
        midiPad[3]->setBounds (proportionOfWidth (0.7500f) - ((proportionOfWidth (0.4799f)) / 2), proportionOfHeight (0.7604f) - ((proportionOfHeight (0.4606f)) / 2), proportionOfWidth (0.4799f), proportionOfHeight (0.4606f));
        for (int i=4;i<numPads;i++) midiPad[i]->setVisible(false);
    }
    else if (squares==5)
    {
        //4 sliders
        for (int i=0;i<4;i++) midiPad[i]->setVisible(true);
        midiPad[0]->setBounds (proportionOfWidth (0.0192f), proportionOfHeight (0.5253f) - ((proportionOfHeight (0.9210f)) / 2), proportionOfWidth (0.2300f), proportionOfHeight (0.9210f));
        midiPad[1]->setBounds (proportionOfWidth (0.3786f) - ((proportionOfWidth (0.2300f)) / 2), proportionOfHeight (0.5253f) - ((proportionOfHeight (0.9210f)) / 2), proportionOfWidth (0.2300f), proportionOfHeight (0.9210f));
        midiPad[2]->setBounds (proportionOfWidth (0.6214f) - ((proportionOfWidth (0.2300f)) / 2), proportionOfHeight (0.5253f) - ((proportionOfHeight (0.9210f)) / 2), proportionOfWidth (0.2300f), proportionOfHeight (0.9210f));
        midiPad[3]->setBounds (proportionOfWidth (0.8658f) - ((proportionOfWidth (0.2300f)) / 2), proportionOfHeight (0.5253f) - ((proportionOfHeight (0.9210f)) / 2), proportionOfWidth (0.2300f), proportionOfHeight (0.9210f));
        for (int i=4;i<numPads;i++) midiPad[i]->setVisible(false);
    }
    else if (squares==17)
    {
         //16 sliders
        for (int i=0;i<16;i++) midiPad[i]->setVisible(true);
         midiPad[0]->setBounds (proportionOfWidth (0.0058f), proportionOfHeight (0.5271f) - ((proportionOfHeight (0.9305f)) / 2), proportionOfWidth (0.0603f), proportionOfHeight (0.9305f));
         midiPad[1]->setBounds (proportionOfWidth (0.0675f), proportionOfHeight (0.5271f) - ((proportionOfHeight (0.9305f)) / 2), proportionOfWidth (0.0603f), proportionOfHeight (0.9305f));
         midiPad[2]->setBounds (proportionOfWidth (0.1293f), proportionOfHeight (0.5271f) - ((proportionOfHeight (0.9305f)) / 2), proportionOfWidth (0.0603f), proportionOfHeight (0.9305f));
         midiPad[3]->setBounds (proportionOfWidth (0.1911f), proportionOfHeight (0.5271f) - ((proportionOfHeight (0.9305f)) / 2), proportionOfWidth (0.0603f), proportionOfHeight (0.9305f));
         midiPad[4]->setBounds (proportionOfWidth (0.2529f), proportionOfHeight (0.5271f) - ((proportionOfHeight (0.9305f)) / 2), proportionOfWidth (0.0603f), proportionOfHeight (0.9305f));
         midiPad[5]->setBounds (proportionOfWidth (0.3147f), proportionOfHeight (0.5271f) - ((proportionOfHeight (0.9305f)) / 2), proportionOfWidth (0.0603f), proportionOfHeight (0.9305f));
         midiPad[6]->setBounds (proportionOfWidth (0.3764f), proportionOfHeight (0.5271f) - ((proportionOfHeight (0.9305f)) / 2), proportionOfWidth (0.0603f), proportionOfHeight (0.9305f));
         midiPad[7]->setBounds (proportionOfWidth (0.4382f), proportionOfHeight (0.5271f) - ((proportionOfHeight (0.9305f)) / 2), proportionOfWidth (0.0603f), proportionOfHeight (0.9305f));
         midiPad[8]->setBounds (proportionOfWidth (0.5000f), proportionOfHeight (0.5271f) - ((proportionOfHeight (0.9305f)) / 2), proportionOfWidth (0.0603f), proportionOfHeight (0.9305f));
         midiPad[9]->setBounds (proportionOfWidth (0.5618f), proportionOfHeight (0.5271f) - ((proportionOfHeight (0.9305f)) / 2), proportionOfWidth (0.0603f), proportionOfHeight (0.9305f));
        midiPad[10]->setBounds (proportionOfWidth (0.6236f), proportionOfHeight (0.5271f) - ((proportionOfHeight (0.9305f)) / 2), proportionOfWidth (0.0603f), proportionOfHeight (0.9305f));
        midiPad[11]->setBounds (proportionOfWidth (0.6853f), proportionOfHeight (0.5271f) - ((proportionOfHeight (0.9305f)) / 2), proportionOfWidth (0.0603f), proportionOfHeight (0.9305f));
        midiPad[12]->setBounds (proportionOfWidth (0.7471f), proportionOfHeight (0.5271f) - ((proportionOfHeight (0.9305f)) / 2), proportionOfWidth (0.0603f), proportionOfHeight (0.9305f));
        midiPad[13]->setBounds (proportionOfWidth (0.8089f), proportionOfHeight (0.5271f) - ((proportionOfHeight (0.9305f)) / 2), proportionOfWidth (0.0603f), proportionOfHeight (0.9305f));
        midiPad[14]->setBounds (proportionOfWidth (0.8707f), proportionOfHeight (0.5271f) - ((proportionOfHeight (0.9305f)) / 2), proportionOfWidth (0.0603f), proportionOfHeight (0.9305f));
        midiPad[15]->setBounds (proportionOfWidth (0.9325f), proportionOfHeight (0.5271f) - ((proportionOfHeight (0.9305f)) / 2), proportionOfWidth (0.0603f), proportionOfHeight (0.9305f));
        for (int i=16;i<numPads;i++) midiPad[i]->setVisible(false);
    }
    else if (squares==1)
    {
        // 1 pad
        midiPad[0]->setBounds (proportionOfWidth (0.5000f) - ((proportionOfWidth (0.9698f)) / 2), proportionOfHeight (0.5271f) - ((proportionOfHeight (0.9243f)) / 2), proportionOfWidth (0.9698f), proportionOfHeight (0.9243f));
        for (int i=1;i<numPads;i++) midiPad[i]->setVisible(false);
    }
    else if (squares==33)
    {
        //"8 channel mixer" layout
        for (int i=0;i<32;i++) midiPad[i]->setVisible(true);
         midiPad[0]->setBounds (proportionOfWidth (0.0029f), proportionOfHeight (0.1144f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
         midiPad[1]->setBounds (proportionOfWidth (0.1882f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.1144f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
         midiPad[2]->setBounds (proportionOfWidth (0.3118f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.1144f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
         midiPad[3]->setBounds (proportionOfWidth (0.4353f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.1144f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
         midiPad[4]->setBounds (proportionOfWidth (0.5000f), proportionOfHeight (0.1144f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
         midiPad[5]->setBounds (proportionOfWidth (0.6868f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.1144f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
         midiPad[6]->setBounds (proportionOfWidth (0.8118f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.1144f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
         midiPad[7]->setBounds (proportionOfWidth (0.9368f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.1144f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));

         midiPad[8]->setBounds (proportionOfWidth (0.0029f), proportionOfHeight (0.2334f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
         midiPad[9]->setBounds (proportionOfWidth (0.1882f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.2334f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[10]->setBounds (proportionOfWidth (0.3118f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.2334f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[11]->setBounds (proportionOfWidth (0.4353f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.2334f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[12]->setBounds (proportionOfWidth (0.5000f), proportionOfHeight (0.2334f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[13]->setBounds (proportionOfWidth (0.6868f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.2334f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[14]->setBounds (proportionOfWidth (0.8118f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.2334f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[15]->setBounds (proportionOfWidth (0.9368f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.2334f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));

        midiPad[16]->setBounds (proportionOfWidth (0.0029f), proportionOfHeight (0.3508f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[17]->setBounds (proportionOfWidth (0.1868f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.3508f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[18]->setBounds (proportionOfWidth (0.3103f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.3508f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[19]->setBounds (proportionOfWidth (0.4339f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.3508f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[20]->setBounds (proportionOfWidth (0.4986f), proportionOfHeight (0.3508f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[21]->setBounds (proportionOfWidth (0.6853f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.3508f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[22]->setBounds (proportionOfWidth (0.8103f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.3508f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));
        midiPad[23]->setBounds (proportionOfWidth (0.9353f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.3508f) - ((proportionOfHeight (0.1206f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.1206f));

        midiPad[24]->setBounds (proportionOfWidth (0.0014f), proportionOfHeight (0.6996f) - ((proportionOfHeight (0.5792f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.5792f));
        midiPad[25]->setBounds (proportionOfWidth (0.1866f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.6996f) - ((proportionOfHeight (0.5792f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.5792f));
        midiPad[26]->setBounds (proportionOfWidth (0.3100f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.6996f) - ((proportionOfHeight (0.5792f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.5792f));
        midiPad[27]->setBounds (proportionOfWidth (0.4334f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.6996f) - ((proportionOfHeight (0.5792f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.5792f));
        midiPad[28]->setBounds (proportionOfWidth (0.4979f), proportionOfHeight (0.6996f) - ((proportionOfHeight (0.5792f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.5792f));
        midiPad[29]->setBounds (proportionOfWidth (0.6859f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.6996f) - ((proportionOfHeight (0.5792f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.5792f));
        midiPad[30]->setBounds (proportionOfWidth (0.8107f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.6996f) - ((proportionOfHeight (0.5792f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.5792f));
        midiPad[31]->setBounds (proportionOfWidth (0.9355f) - ((proportionOfWidth (0.1207f)) / 2), proportionOfHeight (0.6996f) - ((proportionOfHeight (0.5792f)) / 2), proportionOfWidth (0.1207f), proportionOfHeight (0.5792f));
        for (int i=32;i<numPads;i++) midiPad[i]->setVisible(false);
    }

    slider->setBounds (proportionOfWidth (0.0275f), proportionOfHeight (0.0179f), proportionOfWidth (0.1100f), proportionOfHeight (0.0358f));
    slider2->setBounds (proportionOfWidth (0.1512f), proportionOfHeight (0.0179f), proportionOfWidth (0.1100f), proportionOfHeight (0.0358f));
    slider3->setBounds (proportionOfWidth (0.2749f), proportionOfHeight (0.0179f), proportionOfWidth (0.1100f), proportionOfHeight (0.0358f));
    slider4->setBounds (proportionOfWidth (0.3986f), proportionOfHeight (0.0179f), proportionOfWidth (0.1100f), proportionOfHeight (0.0358f));
    velocitySlider->setBounds (proportionOfWidth (0.5498f), proportionOfHeight (0.0179f), proportionOfWidth (0.1649f), proportionOfHeight (0.0358f));
    valueSlider->setBounds (proportionOfWidth (0.7285f), proportionOfHeight (0.0179f), proportionOfWidth (0.1649f), proportionOfHeight (0.0358f));
    menuButton->setBounds (proportionOfWidth (0.8935f), proportionOfHeight (0.0179f), proportionOfWidth (0.0962f), jmax(12,proportionOfHeight (0.0358f)));

    // if we've been resized, tell the filter so that it can store the new size
//    owner->lastUIWidth = getWidth();
//    owner->lastUIHeight = getHeight();
}

//==============================================================================
void MidiPadsPluginEditor::mouseDrag(const MouseEvent &e)
{
    bool usex[numPads];
    bool usey[numPads];
    bool useaft = false;
    if (owner->getParameter(kSendAft)>=0.5) useaft=true;

    for (int i = 0; i < jmax (1, (squares - squares % 2)); i++)
    {
        usex[i]=false;
        if (owner->UseX[i]>=0.5) usex[i]=true;

        usey[i]=false;
        if (owner->UseY[i]>=0.5) usey[i]=true;

        if (midiPad[i]->drawableButton->isMouseButtonDown())
        {
            ModifierKeys mousebutton = ModifierKeys::getCurrentModifiers();
            setWantsKeyboardFocus(false);
            
            if (mousebutton.isMiddleButtonDown() || mousebutton.isCtrlDown()) { 
                //ignore
            }
            else if (mousebutton.isPopupMenu()) {
                //ignore
            }
            else
            { 
                if (usex[i] || usey[i] || useaft)
                {
                    int x=0;
                    int y=0;
                    midiPad[i]->getMouseXYRelative(x,y);

                    //measure y from the bottom, make into range 0..1
                    float fy=1.0f-(((float)(y))/((float)(midiPad[i]->getHeight())));
                    float fx=(((float)(x))/((float)(midiPad[i]->getWidth())));
                    int newx=(int)(fx*127.1);
                    if (newx>127) {newx=127; fx=1.0f;}
                    else if (newx<0) {newx=0; fx=0.0f;}
                    if (owner->UseXPB[i]) {
                        newx=roundFloatToInt(fx*16383.0f);
                        if (newx>0x3fff) {newx=0x3fff; fx=1.0f;}
                        else if (newx<0) {newx=0; fx=0.0f;}
                    }
                    int newy=(int)(fy*127.1);
                    if (newy>127) {newy=127; fy=1.0f;}
                    else if (newy<0) {newy=0; fy=0.0f;}

                    //move the dot
                    //if (showdots) {
                        if (usex[i]) {
                            midiPad[i]->drawableButton->x=fx;
                            owner->setParameterNotifyingHost(i+xpos,fx); 
                        }
                        else {
                            midiPad[i]->drawableButton->x=0.5f;
                            owner->setParameterNotifyingHost(i+110,fx);
                        }
                        if (owner->Ytype[i]<0.5) {
                            if (useaft || owner->UseYCC[i]) {
                                midiPad[i]->drawableButton->y=fy;
                                owner->setParameterNotifyingHost(i+ypos,fy);
                            }
                        }
                        else {
                            if (usey[i]) {
                                midiPad[i]->drawableButton->y=fy;
                                owner->setParameterNotifyingHost(i+ypos,fy);
                            }
                        }
                        if (showdots) midiPad[i]->repaint();
                    //}
                    if (usex[i] && lastx[i]!=newx) {
                        owner->buttondown[i] = true;
                        lastx[i]=newx;
                    }
                    if ((owner->Ytype[i])>=0.5 && usey[i] && lasty[i]!=newy) {
                        owner->send[i]=1.0f;
                        lasty[i]=newy;
                    }
                    else if ((owner->Ytype[i])<0.5 && useaft && lasty[i]!=newy) {
                        owner->buttondown[i] = true;
                        lasty[i]=newy;
                    }
                    else if (usey[i] && (owner->Ytype[i])<0.5 && owner->UseYCC[i] && lasty[i]!=newy) {
                        owner->buttondown[i] = true;
                        lasty[i]=newy;
                    }
                }
            }
        }
    }
}

//==============================================================================
void MidiPadsPluginEditor::mouseUp (const MouseEvent&)
{
    //if (mousebutton.isPopupMenu()) {
    //    //ignore
    //}
    if (owner->usemouseup) {
        for (int i=0;i<jmax(1,(squares-squares%2));i++) {
            if (midiPad[i]->isPlaying && !owner->toggle[i] && !dontsend) {
                sendMidiOff(i);
            }
        }
    }
    dontsend=false;
}

//==============================================================================
void MidiPadsPluginEditor::buttonStateChanged (Button* buttonThatWasClicked)
{
    bool usex[numPads];
    bool usey[numPads];
    bool useycc[numPads];
    bool useoff[numPads];
    bool usexpb[numPads];
    bool toggle[numPads];
    bool editmode = false;
    if (owner->editmode) editmode=true;
    bool noteontrig = false;
    if (owner->getParameter(kNoteOnTrig)>=0.5f 
        && owner->getParameter(kUseTrigger)>=0.5f)
        noteontrig=true;

    for (int i = 0; i < jmax (1, (squares - squares % 2)); i++)
    {
        usex[i] = owner->UseX[i]>=0.5;
        usey[i] = owner->UseY[i]>=0.5;
        useycc[i] = owner->UseYCC[i];
        useoff[i] = owner->SendOff[i];
        usexpb[i] = owner->UseXPB[i];
        toggle[i] = owner->toggle[i];
        owner->icon[i]=midiPad[i]->drawableButton->getName();
        ModifierKeys mousebutton = ModifierKeys::getCurrentModifiers();
        if (buttonThatWasClicked == midiPad[i]->drawableButton)
        {
            if (midiPad[i]->drawableButton->isDown())
            {
                //middle/ctrl click midi learn
                if (mousebutton.isMiddleButtonDown() || mousebutton.isCtrlDown())
                { 
                    if (mousebutton.isAltDown() && mousebutton.isShiftDown()) 
                        owner->midilisten[i] = 0.5f; //learn x trigger (not implemented!)
                    else if (mousebutton.isShiftDown()) 
                        owner->midilisten[i] = 0.6f; //learn y trigger
                    else if (mousebutton.isAltDown()) 
                        owner->midilisten[i] = 0.8f; //learn x
                    else owner->midilisten[i] = 1.0f;
                }
                //pad menu
                else if (mousebutton.isPopupMenu())
                {
                    if (!editmode) dontsend=true;
                    if (editmode)
                    {
                        PopupMenu m, sub1, sub2, sub3;
                        m.addCustomItem (1, textEditor[i], 200 , 24, false);
                        m.addSeparator();

                        m.addItem(66,T("Clear Icon"));
                        sub1.addCustomItem (1234, colourSelector1[i], 300, 300, false);
                        m.addSubMenu (T("Color"), sub1);
                        m.addSeparator();

                        bool iscc = false;
                        if (owner->Ytype[i]>0.5f) iscc = true;
                        m.addItem(2,String(T("Note")),true,!iscc);
                        m.addItem(3,String(T("CC")),true,iscc);
                        m.addSeparator();
                        m.addItem (4, String(T("Use Y-Position")), true, usey[i]);
                        m.addItem (7, String(T("Send Y-CC with Note")), true, useycc[i]);
                        m.addItem (5, String(T("Use X-Position")), true, usex[i]);
                        m.addItem (8, String(T("X is Pitch Bend")), usex[i], usexpb[i]);
                        m.addItem (6, String(T("Send Off Values")), true, useoff[i]);
                        m.addItem (9, String(T("Toggle Mode")), true, toggle[i]);
                        m.addSeparator();
                        
                        sub2.addItem (-1, T("Note #:"),false);
                        sub2.addCustomItem (-1, nSlider[i], 64, 16, false);
                        sub2.addItem (-1, T("Y-CC #:"),false);
                        sub2.addCustomItem (-1, ySlider[i], 64, 16, false);
                        sub2.addItem (-1, T("On Value:"),false);
                        sub2.addCustomItem (-1, vSlider[i], 64, 16, false);
                        sub2.addItem (-1, T("Off Value:"),false);
                        sub2.addCustomItem (-1, oSlider[i], 64, 16, false);
                        sub2.addItem (-1, T("X-CC #:"),false);
                        sub2.addCustomItem (-1, xSlider[i], 64, 16, false);
                        sub2.addItem (-1, T("X-CC Off Value:"),false);
                        sub2.addCustomItem (-1, xoSlider[i], 64, 16, false);
                        sub2.addItem (-1, T("Trigger Note #:"),false);
                        sub2.addCustomItem (-1, triggerSlider[i], 64, 16, false);
                        m.addSubMenu (T("Values"), sub2);
                        m.addSeparator();

                        sub3.addItem (88, T("Learn Note/Y-CC"));
                        sub3.addItem (89, T("Learn Y-Off"));
                        sub3.addItem (90, T("Learn X-CC"));
                        sub3.addItem (91, T("Learn X-Off"));
                        sub3.addItem (92, T("Learn Trigger"));
                        m.addSubMenu(T("Learn"),sub3);

                        int result = m.show();
                        if (result != 0)
                        {
                            if (result==2 || result==3)
                            {
                                if (iscc) {
                                    owner->Ytype[i]=0.0f;
                                    midiPad[i]->drawableButton->y=owner->Ydata2[i];
                                    midiPad[i]->setButtonText(T("CC ") + String((int)(owner->Ydata1[i]*127.1)));
                                }
                                else {
                                    owner->Ytype[i]=1.0f;
                                    if (owner->SendOff[i]) midiPad[i]->drawableButton->y=owner->Yoff[i];
                                    else midiPad[i]->drawableButton->y=owner->Ydata2[i];
                                    midiPad[i]->setButtonText(MidiMessage::getMidiNoteName((int)(owner->Ydata1[i]*127.1),true,true,3)); 
                                }
                            }
                            else if (result==4)
                            {
                                if (usey[i]) {
                                    //turning off use y
                                    owner->UseY[i]=0.0f;
                                    if (showdots) {
                                        if (owner->SendOff[i]) {
                                            if (owner->Ytype[i]>=0.5) midiPad[i]->drawableButton->y=owner->Yoff[i];
                                            midiPad[i]->drawableButton->showy=false;
                                            midiPad[i]->repaint();
                                        }
                                        else {
                                            midiPad[i]->drawableButton->y=owner->Ydata2[i];
                                            midiPad[i]->drawableButton->showy=false;
                                            midiPad[i]->repaint();
                                        }
                                    }
                                }
                                else
                                {
                                    owner->UseY[i]=1.0f;
                                    midiPad[i]->drawableButton->showy=true;
                                    midiPad[i]->repaint();
                                }
                            }
                            else if (result==5)
                            {
                                if (usex[i])
                                {
                                    // turning off use x
                                    owner->UseX[i]=0.0f;
                                    if (showdots) {
                                        midiPad[i]->drawableButton->x=0.5f;
                                        midiPad[i]->drawableButton->showx=false;
                                        midiPad[i]->repaint();
                                    }
                                }
                                else
                                {
                                    owner->UseX[i]=1.0f;
                                    midiPad[i]->drawableButton->showx=true;
                                    midiPad[i]->repaint();
                                }
                            }
                            else if (result==6)
                            {
                                if (useoff[i])
                                {
                                    owner->SendOff[i]=0.0f;
                                    if (showdots) {
                                        midiPad[i]->drawableButton->y=owner->Ydata2[i];
                                        midiPad[i]->repaint();
                                    }
                                }
                                else
                                {
                                    owner->SendOff[i]=1.0f;
                                    if (showdots) {
                                        if (owner->Ytype[i]>=0.5) {
                                            midiPad[i]->drawableButton->y=owner->Yoff[i];
                                            midiPad[i]->repaint();
                                        }
                                    }
                                }
                            }
                            else if (result==7) {
                                if (useycc[i]) owner->UseYCC[i]=false;
                                else owner->UseYCC[i]=true;
                            }
                            else if (result==8) {
                                if (usexpb[i]) owner->UseXPB[i]=false;
                                else owner->UseXPB[i]=true;
                            }
                            else if (result==9) {
                                if (toggle[i]) owner->toggle[i]=false;
                                else owner->toggle[i]=true;
                            }

                            else if (result==66) {
                                owner->icon[i] = T("");
                                midiPad[i]->drawableButton->setImages(0);
                                midiPad[i]->drawableButton->setName(T(""));
                            }
                            else if (result==88) owner->midilisten[i] = 1.0f;
                            else if (result==89) owner->midilisten[i] = 0.9f;
                            else if (result==90) owner->midilisten[i] = 0.8f;
                            else if (result==91) owner->midilisten[i] = 0.7f;
                            else if (result==92) owner->midilisten[i] = 0.6f;
                        }
                    }
                }
                //send midi
                else if (mousebutton.isShiftDown()) { //shift-click: toggle
                    owner->lastxccvalue[i]=-1;
                    owner->lastyccvalue[i]=-1;
                    sendMidi(i, true);
                }
                else { 
                    owner->lastxccvalue[i]=-1;
                    owner->lastyccvalue[i]=-1;
                    if (!noteontrig) sendMidi(i);
                }
            }
        }
    }
}

//==============================================================================
void MidiPadsPluginEditor::changeListenerCallback (void* source)
{
    if (source==owner) {
        if (owner->trig) padTriggered();
        else {
            for (int i=0;i<jmax(1,(squares-squares%2));i++) {
                bool moved=false;
                if (owner->dotmoved[i]) {
                    dotMoved(i);
                    moved=true;
                }
                if (moved)
                    return;
            }
        }
        updateParametersFromFilter();
    }
    else {
        ColourSelector* cs = (ColourSelector*) source;
        for (int i=0;i<squares;i++) {
            if (cs->getName() == String(i)) {
                midiPad[i]->setColour(cs->getCurrentColour().withAlpha(owner->contrast));
                owner->padcolor[i] = cs->getCurrentColour();
            }
        }
    }
}

//==============================================================================
void MidiPadsPluginEditor::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == menuButton) {
        bool sendoffvalue = true;
        bool useyvalue = true;
        bool usexvalue = true;
        for (int i=0;i<jmax(1,(squares-squares%2));i++) {
            if (!owner->SendOff[i]) {
                sendoffvalue = false;
            }
            if (owner->UseY[i]<0.5f) {
                useyvalue = false;
            }
            if (owner->UseX[i]<0.5f) {
                usexvalue = false;
            }
        }
        bool triggering = false;
        if (owner->getParameter(kUseTrigger)>=0.5f) triggering = true;
        bool thru = false;
        if (owner->getParameter(kThru)>=0.5f) thru = true;
        bool useinvel = false;
        if (owner->getParameter(kUseVel)>=0.5f) useinvel = true;
        bool useaft = false;
        if (owner->getParameter(kSendAft)>=0.5f) useaft = true;
        bool monomode = false;
        if (owner->getParameter(kMono)>=0.5f) monomode = true;
        bool editmode = false;
        if (owner->editmode) editmode=true;
        bool usemouseup = false;
        if (owner->usemouseup) usemouseup=true;
        bool noteontrig = false;
        if (owner->getParameter(kNoteOnTrig)>=0.5f) noteontrig=true;

        PopupMenu m;
        m.addItem (1, String(T("Send off value")), true, sendoffvalue);
        m.addItem (2, String(T("Use Midi Triggering")), true, triggering);
        m.addItem (3, String(T("Use Input Velocity")), triggering, useinvel);
        //m.addItem (222, String(T("Piezo Mode")), triggering, noteontrig);
        m.addItem (4, String(T("Use Y-Position")), true, useyvalue);
        m.addItem (5, String(T("Use X-Position")), true, usexvalue);
        m.addItem (6, String(T("Send Aftertouch")), true, useaft);
        m.addItem (7, String(T("Show Dots")), true, showdots);
        m.addItem (8, String(T("Mono Mode")), true, monomode);
        m.addItem (9, String(T("Use mouseup anywhere")), true, usemouseup);
        m.addItem (50, String(T("Midi Thru")), true, thru);
        m.addSeparator();
        m.addItem (18, String(T("1 Pad")), true, squares==1);
        m.addItem (17, String(T("4 Pads")), true, squares==4);
        m.addItem (19, String(T("4 Sliders")), true, squares==5);
        m.addItem (10, String(T("10 Pads")), true, squares==10);
        m.addItem (20, String(T("16 Pads")), true, squares==16);
        m.addItem (21, String(T("16 Sliders")), true, squares==17);
        m.addItem (22, String(T("64 Pads")), true, squares==64);
        m.addItem (23, String(T("8 Ch Mixer")), true, squares==33);
        m.addSeparator();
        m.addItem (-1, T("Pad Roundness:"),false);
        m.addCustomItem (-1, slider5, 64, 16, false);
        m.addSeparator();
        m.addItem (33, String(T("Edit Mode")), true, editmode);
        m.addSeparator();
        m.addItem (-1, T("In Channel:"),false);
        m.addCustomItem (-1, icSlider, 64, 16, false);
        m.addItem (-1, T("Out Channel:"),false);
        m.addCustomItem (-1, cSlider, 64, 16, false);

        int result = m.showAt (menuButton);
        if (result != 0)
        {
            if (result==1) {
                if (sendoffvalue) {
                    for (int i=0;i<numPads;i++) {
                        owner->SendOff[i]=0.0f;
                        if (showdots) {
                            midiPad[i]->drawableButton->y=owner->Ydata2[i];
                            midiPad[i]->repaint();
                        }
                    }
                }
                else {
                    for (int i=0;i<numPads;i++) {
                        owner->SendOff[i]=1.0f;
                        if (showdots) {
                            if (owner->Ytype[i]>=0.5) {
                                midiPad[i]->drawableButton->y=owner->Yoff[i];
                                midiPad[i]->repaint();
                            }
                        }
                    }
                }
            }
            else if (result==9) {
                if (owner->usemouseup) {
                    owner->usemouseup=false;
                }
                else owner->usemouseup=true;
            }
            else if (result==2) {
                if (owner->getParameter(kUseTrigger)>=0.5f) {
                    owner->setParameterNotifyingHost(kUseTrigger,0.0f);
                }
                else owner->setParameterNotifyingHost(kUseTrigger,1.0f);
            }
            else if (result==222) {
                if (owner->getParameter(kNoteOnTrig)>=0.5f) {
                    owner->setParameterNotifyingHost(kNoteOnTrig,0.0f);
                }
                else owner->setParameterNotifyingHost(kNoteOnTrig,1.0f);
            }
            else if (result==3) {
                if (owner->getParameter(kUseVel)>=0.5f) {
                    owner->setParameterNotifyingHost(kUseVel,0.0f);
                }
                else owner->setParameterNotifyingHost(kUseVel,1.0f);
            }
            else if (result==4) {
                if (useyvalue) {
                    //turning off use y
                    for (int i=0;i<numPads;i++) {
                        owner->UseY[i]=0.0f;
                        if (showdots) {
                            if (owner->SendOff[i]) {
                                if (owner->Ytype[i]>=0.5) midiPad[i]->drawableButton->y=owner->Yoff[i];
                                midiPad[i]->drawableButton->showy=false;
                                midiPad[i]->repaint();
                            }
                            else {
                                midiPad[i]->drawableButton->y=owner->Ydata2[i];
                                midiPad[i]->drawableButton->showy=false;
                                midiPad[i]->repaint();
                            }
                        }
                    }
                }
                else {
                    for (int i=0;i<numPads;i++) {
                        owner->UseY[i]=1.0f;
                        midiPad[i]->drawableButton->showy=true;
                        midiPad[i]->repaint();
                    }
                }

            }
            else if (result==5) {
                if (usexvalue) {
                    // turning off use x
                    for (int i=0;i<numPads;i++) {
                        owner->UseX[i]=0.0f;
                        if (showdots) {
                            midiPad[i]->drawableButton->x=0.5f;
                            midiPad[i]->drawableButton->showx=false;
                            midiPad[i]->repaint();
                        }
                    }
                }
                else {
                    for (int i=0;i<numPads;i++) {
                        owner->UseX[i]=1.0f;
                        midiPad[i]->drawableButton->showx=true;
                        midiPad[i]->repaint();
                    }
                }

            }
            else if (result==6) {
                if (owner->getParameter(kSendAft)>=0.5f) {
                    owner->setParameterNotifyingHost(kSendAft,0.0f);
                }
                else owner->setParameterNotifyingHost(kSendAft,1.0f);
            }
            else if (result==7) {
                if (showdots) {
                    owner->showdots=false;
                    showdots=false;
                    for (int i=0;i<numPads;i++) {
                        midiPad[i]->drawableButton->showdot=false;
                        midiPad[i]->repaint();
                    }
                }
                else {
                    owner->showdots=true;
                    showdots=true;
                    for (int i=0;i<numPads;i++) {
                        midiPad[i]->drawableButton->showdot=true;
                        midiPad[i]->repaint();
                    }
                }
            }
            else if (result==8) {
                if (owner->getParameter(kMono)>=0.5f) {
                    owner->setParameterNotifyingHost(kMono,0.0f);
                }
                else owner->setParameterNotifyingHost(kMono,1.0f);
            }

            else if (result==50) {
                if (owner->getParameter(kThru)>=0.5f) {
                    owner->setParameterNotifyingHost(kThru,0.0f);
                }
                else owner->setParameterNotifyingHost(kThru,1.0f);
            }
            else if (result==18) {
                if (squares!=1) {
                    owner->squares=1;
                    squares=1;
                    resized();
                }
            }
            else if (result==17) {
                if (squares!=4) {
                    owner->squares=4;
                    squares=4;
                    resized();
                }
            }
            else if (result==19) {
                if (squares!=5) {
                    owner->squares=5;
                    squares=5;
                    resized();
                }
            }
            else if (result==10) {
                if (squares!=10) {
                    owner->squares=10;
                    squares=10;
                    resized();
                }
            }
            else if (result==20) {
                if (squares!=16) {
                    owner->squares=16;
                    squares=16;
                    resized();
                }
            }
            else if (result==21) {
                if (squares!=17) {
                    owner->squares=17;
                    squares=17;
                    resized();
                }
            }
            else if (result==22) {
                if (squares!=64) {
                    owner->squares=64;
                    squares=64;
                    resized();
                }
            }
            else if (result==23) {
                if (squares!=33) {
                    owner->squares=33;
                    squares=33;
                    resized();
                }
            }
            else if (result==33) {
                if (editmode) {
                    owner->editmode=false;
                    slider->setVisible(false);
                    slider2->setVisible(false);
                    slider3->setVisible(false);
                    slider4->setVisible(false);
                    slider5->setVisible(false);
                    velocitySlider->setVisible(false);
                    valueSlider->setVisible(false);
                }
                else {
                    owner->editmode=true;
                    slider->setVisible(true);
                    slider2->setVisible(true);
                    slider3->setVisible(true);
                    slider4->setVisible(true);
                    slider5->setVisible(true);
                    velocitySlider->setVisible(true);
                    valueSlider->setVisible(true);
                }
            }

        }
    }
    else {
        if (!dontsend) {
            for (int i=0;i<jmax(1,(squares-squares%2));i++) {
                if (buttonThatWasClicked == midiPad[i]->drawableButton) {
                    if (owner->midilisten[i]<0.5f && !owner->toggle[i]) { 
                        //only send if not learning & not in toggle mode
                        sendMidiOff(i);
                    }
                }
            }
        }
        //else dontsend=false; 
    }
}

//==============================================================================
void MidiPadsPluginEditor::sliderValueChanged (Slider * sliderThatWasMoved)
{
    if (sliderThatWasMoved == slider)
    {
        color=Colour((float)slider->getValue(),(float)slider2->getValue(),(float)slider3->getValue(),1.0f);
        color2 = color.contrasting((float)slider4->getValue());
        owner->bghue = (float)(slider->getValue());
        repaint();
    }
    else if (sliderThatWasMoved == slider2)
    {
        color=Colour((float)slider->getValue(),(float)slider2->getValue(),(float)slider3->getValue(),1.0f);
        color2 = color.contrasting((float)slider4->getValue());
        owner->bgsat = (float)(slider2->getValue());
        repaint();
    }
    else if (sliderThatWasMoved == slider3)
    {
        color=Colour((float)slider->getValue(),(float)slider2->getValue(),(float)slider3->getValue(),1.0f);
        color2 = color.contrasting((float)slider4->getValue());
        owner->bgbri = (float)slider3->getValue();
        repaint();
    }
    else if (sliderThatWasMoved == slider4)
    {
        color2 = color.contrasting((float)slider4->getValue());
        owner->contrast = (float)slider4->getValue();
        repaint();
    }

    else if (sliderThatWasMoved == slider5)
    {
        for (int i=0;i<jmax(1,(squares-squares%2));i++) {
            midiPad[i]->drawableButton->roundness=(float)slider5->getValue();
            midiPad[i]->drawableButton->repaint();
            owner->roundness=(float)slider5->getValue();
        }
    }

    else if (sliderThatWasMoved == velocitySlider)
    {
        owner->setParameterNotifyingHost(kVelOffset,((float)velocitySlider->getValue())*0.5f);
    }
    else if (sliderThatWasMoved == valueSlider)
    {
        owner->setParameterNotifyingHost(kCCOffset,((float)valueSlider->getValue())*0.5f);
    }
    else if (sliderThatWasMoved == icSlider) {
        owner->setParameterNotifyingHost(kChIn,((float)icSlider->getValue()-1)/15.0f);
    }
    else if (sliderThatWasMoved == cSlider) {
        owner->setParameterNotifyingHost(kChOut,((float)cSlider->getValue()-1.0f)/15.0f);
    }
    else {
        for (int i=0;i<jmax(1,(squares-squares%2));i++) {
            if (sliderThatWasMoved == vSlider[i]) {
                owner->Ydata2[i]=(float)vSlider[i]->getValue()/127.0f;
                if (!owner->SendOff[i] && owner->UseY[i]<0.5f) {
                    midiPad[i]->drawableButton->y=owner->Ydata2[i];
                    midiPad[i]->repaint();
                }
            }
            else if (sliderThatWasMoved == nSlider[i]) {
                owner->Ydata1[i]=(float)nSlider[i]->getValue()/127.0f;
            }
            else if (sliderThatWasMoved == ySlider[i]) {
                owner->Ycc[i]=(float)ySlider[i]->getValue()/127.0f;
            }
            else if (sliderThatWasMoved == oSlider[i]) {
                owner->Yoff[i]=(float)oSlider[i]->getValue()/127.0f;
                if (owner->SendOff[i] && owner->Ytype[i]>=0.5f) {
                    midiPad[i]->drawableButton->y=owner->Yoff[i];
                    midiPad[i]->repaint();
                }
            }
            else if (sliderThatWasMoved == triggerSlider[i]) {
                owner->trigger[i]=(float)triggerSlider[i]->getValue()/127.0f;
            }
            else if (sliderThatWasMoved == xSlider[i]) {
                owner->Xcc[i]=(float)xSlider[i]->getValue()/127.0f;
                if (!owner->SendOff[i]) {
                    midiPad[i]->drawableButton->x=owner->getParameter(i+xpos);
                    midiPad[i]->repaint();
                }
            }
            else if (sliderThatWasMoved == xoSlider[i]) {
                owner->Xoff[i]=(float)xoSlider[i]->getValue()/127.0f;
                if (owner->SendOff[i]) {
                    midiPad[i]->drawableButton->x=owner->Xoff[i];
                    midiPad[i]->repaint();
                }
            }
        }
    }
}


//==============================================================================
void MidiPadsPluginEditor::textEditorTextChanged (TextEditor &editor)
{
    for (int i=0;i<jmax(1,(squares-squares%2));i++) {
        if (&editor==textEditor[i]) {
            midiPad[i]->drawableButton->Label = textEditor[i]->getText();
            owner->text[i]=textEditor[i]->getText();
        }
    }
}

void MidiPadsPluginEditor::textEditorReturnKeyPressed (TextEditor &editor)
{
    for (int i=0;i<jmax(1,(squares-squares%2));i++) {
        if (&editor==textEditor[i]) {
            midiPad[i]->drawableButton->Label = textEditor[i]->getText();
            owner->text[i]=textEditor[i]->getText();
        }
    }
}

void MidiPadsPluginEditor::textEditorEscapeKeyPressed (TextEditor &editor) {
}

void MidiPadsPluginEditor::textEditorFocusLost (TextEditor &editor) {
}


//==============================================================================
void MidiPadsPluginEditor::sendMidi (int i, bool shiftclicked)
{
    bool usex = owner->UseX[i]>=0.5f;
    bool usey = owner->UseY[i]>=0.5f;
    if (owner->togglestate[i]) {
        owner->togglestate[i] = false;
        midiPad[i]->setToggleState(false);
        sendMidiOff(i);
        return;
    }
    if (owner->getParameter(kMono)>=0.5f) {
        for (int n=0;n<jmax(1,(squares-squares%2));n++) {
            owner->togglestate[n] = false;
            midiPad[n]->setToggleState(false);
        }
    }
    if (owner->toggle[i] || shiftclicked) {
        dontsend=true;
        owner->togglestate[i] = true;
        midiPad[i]->setToggleState(true);
    }
    midiPad[i]->isPlaying=true;
    int x=0;
    int y=0;
    if (!owner->triggered[i]) {
        midiPad[i]->getMouseXYRelative(x,y);
        //measure y from the bottom, make into range 0..1
        float fy=1.0f-(((float)(y))/((float)(midiPad[i]->getHeight())));
        float fx=(((float)(x))/((float)(midiPad[i]->getWidth())));
        if (showdots) {
            if (usex) midiPad[i]->drawableButton->x=fx;
            else midiPad[i]->drawableButton->x=0.5f;
            if (usey) midiPad[i]->drawableButton->y=fy;
            else midiPad[i]->drawableButton->y=owner->Ydata2[i];
            midiPad[i]->repaint();
        }
        if (usex) {
            owner->setParameterNotifyingHost(i+xpos,fx);
            owner->buttondown[i] = true;
            lastx[i]=(int)(fx*127.1);
        }
        owner->setParameterNotifyingHost(i+ypos,fy);
        owner->send[i] = 1.0f;
        lasty[i]=(int)(fy*127.1);
    }
}

void MidiPadsPluginEditor::sendMidiOff (int i)
{
    if (midiPad[i]->isPlaying)
    { 
        owner->sendoff[i] = 1.0f;
        bool useoffval = false;
        useoffval = owner->SendOff[i];
        midiPad[i]->isPlaying=false;
        if (showdots && useoffval) {
            if (owner->UseX[i]>=0.5f) {
                midiPad[i]->drawableButton->x=owner->Xoff[i];
                midiPad[i]->repaint();
                lastx[i]=(int)((owner->Xoff[i])*127.1);
            }
            if (owner->Ytype[i]>=0.5) {
                midiPad[i]->drawableButton->y=owner->Yoff[i];
                midiPad[i]->repaint();
                lasty[i]=(int)((owner->Yoff[i])*127.1);
            }
        }
    }
}

void MidiPadsPluginEditor::padTriggered()
{
    if(owner->getParameter(kNoteOnTrig)<0.5f)
    {
        bool triggered[numPads];

//        owner->getCallbackLock().enter();

        for (int i=0;i<jmax(1,(squares-squares%2));i++) {
            triggered[i]=owner->triggered[i];
        }

//        owner->getCallbackLock().exit();

        for (int i=0;i<jmax(1,(squares-squares%2));i++)
        {
            if (triggered[i]) {
                midiPad[i]->drawableButton->setState(Button::buttonDown);
            }
            else {
                midiPad[i]->drawableButton->setState(Button::buttonNormal);
            }

            midiPad[i]->drawableButton->repaint();
        }
    }
    else {
        for (int i=0;i<jmax(1,(squares-squares%2));i++) {
            if (midiPad[i]->drawableButton->isMouseOver()) 
                sendMidi(i);
        }
    }
    owner->trig=false;
}

void MidiPadsPluginEditor::dotMoved(int pad)
{
    float x = owner->getParameter(pad+xpos);
    float y = owner->getParameter(pad+ypos);
    if ((int)(x*127.1)!=lastx[pad] && owner->UseX[pad]>=0.5) {
        midiPad[pad]->drawableButton->x=x;
        midiPad[pad]->repaint();
    }
    if ((int)(y*127.1)!=lasty[pad] && owner->UseY[pad]>=0.5) {
        midiPad[pad]->drawableButton->y=y;
        midiPad[pad]->repaint();
    }
    owner->dotmoved[pad]=false;
}

//==============================================================================
Drawable* MidiPadsPluginEditor::createImageFromZipFile (const String& filename)
{
    if (filename == String::empty)
        return 0;

    if (iconsFromZipFile.size() == 0)
    {
        // If we've not already done so, load all the images from the zip file..
        MemoryInputStream iconsFileStream (Resource::jost_midipads, Resource::jost_midipads_size, false);
        ZipFile icons (&iconsFileStream, false);

        for (int i = 0; i < icons.getNumEntries(); ++i)
        {
            InputStream* imageFileStream = icons.createStreamForEntry (i);

            if (imageFileStream != 0)
            {
                iconNames.add (icons.getEntry(i)->filename);
                iconsFromZipFile.add (Drawable::createFromImageDataStream (*imageFileStream));

                delete imageFileStream;
            }
        }
    }

    Drawable* image = iconsFromZipFile [iconNames.indexOf (filename)];
    if (image)
    {
        return image;
    }
    else
    {
        printf ("Can't find icon '%s' in resources !", (const char*) filename);
        return 0;
    }
}

//==============================================================================
void MidiPadsPluginEditor::updateParametersFromFilter()
{
    int newMidiData[numPads];
    float newMidiType[numPads];
    int newMidiValue[numPads];
    int newOffValue[numPads];
    int newTrigger[numPads];
    int newXCC[numPads];
    int newYCC[numPads];
    int newXOff[numPads];
    float newX[numPads];
    float newY[numPads];
    float usex[numPads];
    float usey[numPads];
    float useoff[numPads];
    String t[numPads];
    String icon[numPads];
    Colour padcolor[numPads];

    // we use this lock to make sure the processBlock() method isn't writing to the
    // lastMidiMessage variable while we're trying to read it, but be extra-careful to
    // only hold the lock for a minimum amount of time..
    //filter->getCallbackLock().enter();

    // take a local copy of the info we need while we've got the lock..

    for (int i = 0; i < numPads; i++)
    {
        newMidiData[i] = (int)((owner->Ydata1[i])*127.1f);
        newMidiType[i] = (owner->Ytype[i]);
        newMidiValue[i] = (int)((owner->Ydata2[i])*127.1f);
        newOffValue[i] = (int)((owner->Yoff[i])*127.1f);
        newTrigger[i] = (int)((owner->trigger[i])*127.1f);
        newXCC[i] = (int)((owner->Xcc[i])*127.1f);
        newYCC[i] = (int)((owner->Ycc[i])*127.1f);
        newXOff[i] = (int)((owner->Xoff[i])*127.1f);
        t[i] = owner->text[i];
        icon[i] = owner->icon[i];
        padcolor[i] = owner->padcolor[i];
        newX[i] = owner->getParameter(i+xpos);
        newY[i] = owner->getParameter(i+ypos);
        usey[i] = owner->UseY[i];
        usex[i] = owner->UseX[i];
        useoff[i] = owner->SendOff[i];
    }

    const float newVelocity = owner->getParameter (kVelOffset);
    const float newCCValue = owner->getParameter (kCCOffset);
    const float newInCh = owner->getParameter (kChIn);
    const float newOutCh = owner->getParameter (kChOut);
//    const float useaft = owner->getParameter (kSendAft);

    const float hue = owner->bghue;
    const float sat = owner->bgsat;
    const float bri = owner->bgbri;
    const float contrast = owner->contrast;
    const int newsquares = owner->squares;
    const bool newdots = owner->showdots;
    const float roundness = owner->roundness;
    const bool editmode = owner->editmode;
    const bool newhex = owner->hex;
//    const bool usemouseup = owner->usemouseup;

    // ..release the lock ASAP
    //filter->getCallbackLock().exit();

    // ..and after releasing the lock, we're free to do the time-consuming UI stuff..
    showdots=newdots;
    String m[numPads];
    for (int i = 0; i < numPads; i++)
    {
        //reconstruct the full path to the icon
        Drawable* image = createImageFromZipFile (icon[i]);

        midiPad[i]->drawableButton->setImages(image);
        midiPad[i]->drawableButton->setName(icon[i]);
        midiPad[i]->drawableButton->setHex(newhex);
        midiPad[i]->drawableButton->showdot=showdots;
        midiPad[i]->setColour(padcolor[i]);
        midiPad[i]->drawableButton->roundness=roundness;

        colourSelector1[i]->setCurrentColour (padcolor[i]);

        if (showdots) {
            if (usex[i]<0.5f) {
                midiPad[i]->drawableButton->x=0.5f;
                midiPad[i]->drawableButton->showx=false;
            }
            else {
                if (useoff[i]>=0.5f) midiPad[i]->drawableButton->x=(float)newXOff[i]/127.0f;
                midiPad[i]->drawableButton->showx=true;
                if ((int)(newX[i]*127.1)!=lastx[i]) {
                    midiPad[i]->drawableButton->x=newX[i];
                    lastx[i]=(int)(newX[i]*127.1);
                }
            }
            if (usey[i]<0.5f) {
                if (useoff[i]<0.5f) midiPad[i]->drawableButton->y=(float)newMidiValue[i]/127.0f;
                else if (newMidiType[i]>=0.5f) midiPad[i]->drawableButton->y=(float)newOffValue[i]/127.0f;
                midiPad[i]->drawableButton->showy=false;
            }
            else {
                midiPad[i]->drawableButton->showy=true;
                if ((int)(newY[i]*127.1)!=lasty[i]) {
                    midiPad[i]->drawableButton->y=newY[i];
                    lasty[i]=(int)(newY[i]*127.1);
                }
            }
        }
        midiPad[i]->drawableButton->Label = t[i];
        textEditor[i]->setText(t[i],false);
        vSlider[i]->setValue(newMidiValue[i],false);
        oSlider[i]->setValue(newOffValue[i],false);
        nSlider[i]->setValue(newMidiData[i],false);
        ySlider[i]->setValue(newYCC[i],false);
        xSlider[i]->setValue(newXCC[i],false);
        xoSlider[i]->setValue(newXOff[i],false);
        triggerSlider[i]->setValue(newTrigger[i],false);
        if (newMidiType[i]>=0.5f) {
            m[i] = T("CC ") + String(newMidiData[i]);
            midiPad[i]->setButtonText(m[i]);
        }
        else {
            m[i] = MidiMessage::getMidiNoteName(newMidiData[i],true,true,3); 
            midiPad[i]->setButtonText(m[i]);
        }
    }
    
    color = Colour (hue, sat, bri, 1.0f);
    color2 = Colour (color.contrasting (contrast));

    slider->setValue (hue, false);
    slider2->setValue (sat, false);
    slider3->setValue (bri, false);
    slider4->setValue (contrast, false);
    slider5->setValue (roundness, false);

    if (! editmode) {
        owner->editmode = false;
        slider->setEnabled (false);
        slider2->setEnabled (false);
        slider3->setEnabled (false);
        slider4->setEnabled (false);
        slider5->setEnabled (false);
    }
    else {
        owner->editmode = true;
        slider->setEnabled (true);
        slider2->setEnabled (true);
        slider3->setEnabled (true);
        slider4->setEnabled (true);
        slider5->setEnabled (true);
    }

    velocitySlider->setValue (newVelocity*2.0, false);
    valueSlider->setValue (newCCValue*2.0, false);
    icSlider->setValue ((float)(1+(int)(newInCh*15.1)), false);
    cSlider->setValue ((float)(1+(int)(newOutCh*15.1)), false);

    updateOuterWindowSize (owner->lastUIWidth, owner->lastUIHeight);

    if (squares != newsquares)
    {
        squares = newsquares;
        resized ();
    }
}
