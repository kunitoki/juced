/***************************************************************************
 *   Copyright (C) 2009 by Christian Borss                                 *
 *   christian.borss@rub.de                                                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


//[Headers] You can add your own extra header files here...
#include "../windows_quirks.h"
#include "../MasterAndCommander.h"
#include "FreqPlot.h"
#include "../LagrangeInterpolator.h"
#include <fftw3.h>
//[/Headers]

#include "TabTimbre.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
TabTimbre::TabTimbre (MasterAndCommander *m)
    : master (m),
      groupComponent (0),
      freqPlot (0),
      sliderSmooth (0),
      Smoothing (0)
{
    addAndMakeVisible (groupComponent = new GroupComponent (T("new group"),
                                                            T("Wet Timbre")));

    addAndMakeVisible (freqPlot = new FreqPlot (master));
    freqPlot->setName (T("new component"));

    addAndMakeVisible (sliderSmooth = new Slider (T("new slider")));
    sliderSmooth->setRange (0, 8, 1);
    sliderSmooth->setSliderStyle (Slider::IncDecButtons);
    sliderSmooth->setTextBoxStyle (Slider::TextBoxLeft, false, 32, 24);
    sliderSmooth->addListener (this);

    addAndMakeVisible (Smoothing = new Label (T("new label"),
                                              T("Smoothing Factor:")));
    Smoothing->setFont (Font (15.0000f, Font::plain));
    Smoothing->setJustificationType (Justification::centredLeft);
    Smoothing->setEditable (false, false, false);
    Smoothing->setColour (TextEditor::textColourId, Colours::black);
    Smoothing->setColour (TextEditor::backgroundColourId, Colour (0x0));


    //[UserPreSize]
    gridX = 28;
    gridY = 25;
    offsetX = 52 + 40 + 8;
    offsetY = 36 + 8;

    sampleRate = 48000.0;
    numLevel = 2048;
    level = new float[numLevel];
    f0 = sampleRate / float(2 * numLevel);
    for (int n = 0; n < numLevel; n++)
    {
        float f = (n + 1.0) * f0;
        level[n] = 0.0;
    }

    int size = sizeof(float) * 2 * numLevel;
    impulse = (float *)fftwf_malloc(size);
    for (int i = 0; i < 2 * numLevel; i++)
        impulse[i] = 0.0;
    impulse[numLevel] = 1.0;

    size = sizeof(float) * 2 * numLevel;
    window = (float *)fftwf_malloc(size);
    for (int i = 0; i < 2 * numLevel; i++)
        window[i] = 1.0 / (2.0 * numLevel);

    size = sizeof(fftwf_complex) * (numLevel + 1);
    dftFreq = (fftwf_complex*)fftwf_malloc(size);
    for (int i = 0; i < numLevel + 1; i++)
    {
        dftFreq[i][0] = 1.0;
        dftFreq[i][1] = 0.0;
    }

    fft  = fftwf_plan_dft_r2c_1d(2 * numLevel, impulse, dftFreq,
                                 FFTW_ESTIMATE|FFTW_PRESERVE_INPUT);
    ifft = fftwf_plan_dft_c2r_1d(2 * numLevel, dftFreq, impulse,
                                 FFTW_ESTIMATE|FFTW_PRESERVE_INPUT);

    numSlider = 25;
    slider = new Slider*[numSlider];
    for (int i = 0; i < numSlider; i++)
    {
        addAndMakeVisible (slider[i] = new Slider (T("new slider")));
        slider[i]->setRange (-100, 20, 1);
        slider[i]->setSliderStyle (Slider::LinearVertical);
        slider[i]->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 16);
        slider[i]->setColour (Slider::thumbColourId, Colour (0xffb00000));
        slider[i]->setColour (Slider::trackColourId, Colour (0x60a08080));
        slider[i]->setColour (Slider::rotarySliderFillColourId, Colour (0x7f800000));
        slider[i]->setColour (Slider::textBoxTextColourId, Colours::maroon);
        slider[i]->setColour (Slider::textBoxHighlightColourId, Colour (0x40ff0000));
        slider[i]->setColour (Slider::textBoxOutlineColourId, Colour (0x0));
        slider[i]->addListener (this);
        slider[i]->setDoubleClickReturnValue (true, 0.0);
    }
    numLabel = 9;
    labelFreq = new Label*[numLabel];
    addAndMakeVisible (labelFreq[0] = new Label (T("new label"), T("62.5 Hz")));
    addAndMakeVisible (labelFreq[1] = new Label (T("new label"), T("125 Hz")));
    addAndMakeVisible (labelFreq[2] = new Label (T("new label"), T("250 Hz")));
    addAndMakeVisible (labelFreq[3] = new Label (T("new label"), T("500 Hz")));
    addAndMakeVisible (labelFreq[4] = new Label (T("new label"), T("1 kHz")));
    addAndMakeVisible (labelFreq[5] = new Label (T("new label"), T("2 kHz")));
    addAndMakeVisible (labelFreq[6] = new Label (T("new label"), T("4 kHz")));
    addAndMakeVisible (labelFreq[7] = new Label (T("new label"), T("8 kHz")));
    addAndMakeVisible (labelFreq[8] = new Label (T("new label"), T("16 kHz")));
    for (int i = 0; i < numLabel; i++)
    {
        labelFreq[i]->setFont (Font (15.0000f, Font::plain));
        labelFreq[i]->setJustificationType (Justification::centred);
        labelFreq[i]->setEditable (false, false, false);
        labelFreq[i]->setColour (TextEditor::textColourId, Colours::black);
        labelFreq[i]->setColour (TextEditor::backgroundColourId, Colour (0x0));
    }
    labelTime = new Label*[numLabel];
    addAndMakeVisible (labelTime[0] = new Label (T("new label"), T("-40 ms")));
    addAndMakeVisible (labelTime[1] = new Label (T("new label"), T("-30 ms")));
    addAndMakeVisible (labelTime[2] = new Label (T("new label"), T("-20 ms")));
    addAndMakeVisible (labelTime[3] = new Label (T("new label"), T("-10 ms")));
    addAndMakeVisible (labelTime[4] = new Label (T("new label"), T("0 ms")));
    addAndMakeVisible (labelTime[5] = new Label (T("new label"), T("10 ms")));
    addAndMakeVisible (labelTime[6] = new Label (T("new label"), T("20 ms")));
    addAndMakeVisible (labelTime[7] = new Label (T("new label"), T("30 ms")));
    addAndMakeVisible (labelTime[8] = new Label (T("new label"), T("40 ms")));
    for (int i = 0; i < numLabel; i++)
    {
        labelTime[i]->setFont (Font (15.0000f, Font::plain));
        labelTime[i]->setJustificationType (Justification::centred);
        labelTime[i]->setEditable (false, false, false);
        labelTime[i]->setColour (TextEditor::textColourId, Colours::black);
        labelTime[i]->setColour (TextEditor::backgroundColourId, Colour (0x0));
    }
    numLabelDb = 7;
    labelDbFreq = new Label*[numLabelDb];
    addAndMakeVisible (labelDbFreq[0] = new Label (T("new label"), T("20 dB")));
    addAndMakeVisible (labelDbFreq[1] = new Label (T("new label"), T("0 dB")));
    addAndMakeVisible (labelDbFreq[2] = new Label (T("new label"), T("-20 dB")));
    addAndMakeVisible (labelDbFreq[3] = new Label (T("new label"), T("-40 dB")));
    addAndMakeVisible (labelDbFreq[4] = new Label (T("new label"), T("-60 dB")));
    addAndMakeVisible (labelDbFreq[5] = new Label (T("new label"), T("-80 dB")));
    addAndMakeVisible (labelDbFreq[6] = new Label (T("new label"), T("-100 dB")));
    for (int i = 0; i < numLabelDb; i++)
    {
        labelDbFreq[i]->setFont (Font (15.0000f, Font::plain));
        labelDbFreq[i]->setJustificationType (Justification::centredRight);
        labelDbFreq[i]->setEditable (false, false, false);
        labelDbFreq[i]->setColour (TextEditor::textColourId, Colours::black);
        labelDbFreq[i]->setColour (TextEditor::backgroundColourId, Colour (0x0));
    }
    labelDbTime = new Label*[numLabelDb];
    addAndMakeVisible (labelDbTime[0] = new Label (T("new label"), T("20 dB")));
    addAndMakeVisible (labelDbTime[1] = new Label (T("new label"), T("0 dB")));
    addAndMakeVisible (labelDbTime[2] = new Label (T("new label"), T("-20 dB")));
    addAndMakeVisible (labelDbTime[3] = new Label (T("new label"), T("-40 dB")));
    addAndMakeVisible (labelDbTime[4] = new Label (T("new label"), T("-60 dB")));
    addAndMakeVisible (labelDbTime[5] = new Label (T("new label"), T("-80 dB")));
    addAndMakeVisible (labelDbTime[6] = new Label (T("new label"), T("-100 dB")));
    for (int i = 0; i < numLabelDb; i++)
    {
        labelDbTime[i]->setFont (Font (15.0000f, Font::plain));
        labelDbTime[i]->setJustificationType (Justification::centredRight);
        labelDbTime[i]->setEditable (false, false, false);
        labelDbTime[i]->setColour (TextEditor::textColourId, Colours::black);
        labelDbTime[i]->setColour (TextEditor::backgroundColourId, Colour (0x0));
    }

    //[/UserPreSize]

    setSize (828, 548);

    //[Constructor] You can add your own custom stuff here..
//    master->print("TabTimbre::TabTimbre : Waiting for your commands, Sir!");

    // FIXME: this is for debugging only
    float data[25];
    int   num    = 25;
    float freq   = 62.5;
    float ratio  = pow(2.0, 1.0/3.0);
    float smooth = 0.0;
    for (int i = 0; i < num; i++)
        data[i] = 0.0;
    paramTimbre = new ParamTimbre(data, num, freq, ratio, smooth);
    interpolator = new LagrangeInterpolator(data, num, freq, ratio);

    freqPlot->init(gridX, gridY, offsetX - 24, offsetY - 32 + 24,
                   numSlider, freq, ratio,
                   numLevel, f0);

    master->registerTabTimbre(this);
    //[/Constructor]
}

TabTimbre::~TabTimbre()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (groupComponent);
    deleteAndZero (freqPlot);
    deleteAndZero (sliderSmooth);
    deleteAndZero (Smoothing);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TabTimbre::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xffffe000));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TabTimbre::resized()
{
    groupComponent->setBounds (8, 8, 808, 500);
    freqPlot->setBounds (24, 32, 776, 460);
    sliderSmooth->setBounds (224, 448, 72, 24);
    Smoothing->setBounds (96, 448, 128, 24);
    //[UserResized] Add your own custom resize handling here..
    for (int i = 0; i < numSlider; i++)
    {
        int x = offsetX + i * gridX - gridX / 2;
        int y = offsetY;
        int width = gridX;
        int height = 6 * gridY + 32;
        slider[i]->setBounds (x, y, width, height);
    }
    for (int i = 0; i < numLabel; i++)
    {
        int x = offsetX + (3 * i - 1) * gridX;
        int y = offsetY + 6 * gridY + 32;
        int width = 2 * gridX;
        int height = 16;
        labelFreq[i]->setBounds (x, y, width, height);
    }
    for (int i = 0; i < numLabelDb; i++)
    {
        int x = offsetX - 72;
        int y = offsetY + i * gridY + 17;
        int width = 64;
        int height = 16;
        labelDbFreq[i]->setBounds (x, y, width, height);
    }
    int offsetTimeX = offsetX - 24;
    int offsetTimeY = offsetY - 32 + 24 + 192;
    float tTotal = 1.0 / f0;
    int wMax = 776 - offsetTimeX - 28;
    int pixel_5ms = floor(0.005 * wMax / tTotal);
    int posOrigin = offsetTimeX + roundf(pixel_5ms * 0.5 * tTotal / 0.005);
    for (int i = 0; i < numLabel; i++)
    {
        int x = posOrigin + (2 * i - 9) * pixel_5ms;
        int y = offsetTimeY + 6 * gridY + 32;
        int width = 2 * pixel_5ms;
        int height = 16;
        labelTime[i]->setBounds (x + 24, y + 8, width, height);
    }
    for (int i = 0; i < numLabelDb; i++)
    {
        int x = offsetTimeX - 48;
        int y = offsetTimeY + i * gridY + 25;
        int width = 64;
        int height = 16;
        labelDbTime[i]->setBounds (x, y, width, height);
    }
    //[/UserResized]
}

void TabTimbre::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == sliderSmooth)
    {
        //[UserSliderCode_sliderSmooth] -- add your slider handling code here..
        double expo = 0.0;
        float value = sliderThatWasMoved->getValue();
        paramTimbre->smooth = value; 
        if (value > 0.0)
            expo = pow(2.0, value - 1.0);
        for (int i = 0; i < 2 * numLevel; i++)
        {
            double alpha = 2.0 * M_PI * i / double(2 * numLevel);
            window[i] = pow(0.5 * (1.0 - cos(alpha)), expo) / (2.0 * numLevel);
        }
        //[/UserSliderCode_sliderSmooth]
    }

    //[UsersliderValueChanged_Post]
    for (int i = 0; i < numSlider; i++)
    {
        if (sliderThatWasMoved == slider[i])
        {
            paramTimbre->data[i] = sliderThatWasMoved->getValue();
            interpolator->update(paramTimbre->data);
        }
    }

    updateData();
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

float* TabTimbre::getFilter()
{
    return impulse;
}


int TabTimbre::getFilterLen()
{
    return 2 * numLevel;
}


void TabTimbre::updateData()
{
    float sign = -1.0;
    for (int n = 0; n < numLevel; n++)
    {
        float db        = interpolator->interpolate((n + 1.0) * f0);
        float gain      = powf(10.0, db / 20.0);
        dftFreq[n+1][0] = sign * gain;
        dftFreq[n+1][1] = 0.0;
        sign = -sign;
    }
    dftFreq[0][0] = -dftFreq[1][0];
    dftFreq[0][1] = 0.0;
    fftwf_execute(ifft);
    for (int n = 0; n < 2 * numLevel; n++)
    {
        impulse[n] *= window[n];
    }
    fftwf_execute(fft);
    for (int n = 0; n < numLevel; n++)
    {
        level[n] = 20.0 * log10f(fabs(dftFreq[n+1][0]));
    }

    freqPlot->setLevel(level);
    freqPlot->setImpulse(impulse);
}


void TabTimbre::setTimbre (ParamTimbre *param)
{
    paramTimbre->set(param);
    for (int i = 0; i < paramTimbre->num; i++)
    {
        slider[i]->setDoubleClickReturnValue(true, paramTimbre->data[i]);
        slider[i]->setValue (paramTimbre->data[i]);
    }
    sliderSmooth->setValue(paramTimbre->smooth);
    interpolator->update(paramTimbre->data);
    updateData();
}


void TabTimbre::sliderDragEnded (Slider* sliderThatWasMoved)
{
    master->onValueChangedTimbre(paramTimbre);
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TabTimbre" componentName=""
                 parentClasses="public Component" constructorParams="MasterAndCommander *m"
                 variableInitialisers="master (m)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330000013" fixedSize="1" initialWidth="828"
                 initialHeight="548">
  <BACKGROUND backgroundColour="ffffe000"/>
  <GROUPCOMPONENT name="new group" id="2cc4bc9befb38382" memberName="groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="8 8 808 500" title="Wet Timbre"/>
  <GENERICCOMPONENT name="new component" id="59ae0e7d51155289" memberName="freqPlot"
                    virtualName="" explicitFocusOrder="0" pos="24 32 776 460" class="FreqPlot"
                    params="master"/>
  <SLIDER name="new slider" id="f2d6b6f5cd951d81" memberName="sliderSmooth"
          virtualName="" explicitFocusOrder="0" pos="224 448 72 24" min="0"
          max="8" int="1" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="32" textBoxHeight="24" skewFactor="1"/>
  <LABEL name="new label" id="238e7bbb6d133177" memberName="Smoothing"
         virtualName="" explicitFocusOrder="0" pos="96 448 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Smoothing Factor:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
