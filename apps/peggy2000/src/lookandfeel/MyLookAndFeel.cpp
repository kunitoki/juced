

//#include "../../../../juce_core/basics/juce_StandardHeader.h"


#include "MyLookAndFeel.h"

//#include "../controls/juce_Slider.h"

//==============================================================================
MyLookAndFeel::MyLookAndFeel()
{
    setColour (TextButton::buttonColourId, Colour (0xffccccff));

    setColour (ComboBox::buttonColourId, Colour (0xffbbbbff));
//    setColour (comboBoxPopupHighlight, Colour (0x991111aa));
//    setColour (comboBoxPopupHighlightedText, comboBoxPopupBackground);
    setColour (ComboBox::outlineColourId, Colours::grey.withAlpha (0.7f));

    setColour (ScrollBar::backgroundColourId, Colours::transparentBlack);
    setColour (ScrollBar::thumbColourId, Colours::white);

    setColour (Slider::backgroundColourId, Colours::white);
    setColour (Slider::textBoxOutlineColourId, Colours::grey.withAlpha (0.7f));

    setColour (ProgressBar::backgroundColourId, Colours::white);
    setColour (ProgressBar::foregroundColourId, Colour (0xffaaaaee));

    setColour (PopupMenu::backgroundColourId, Colours::white);
    setColour (PopupMenu::highlightedTextColourId, Colours::white);
    setColour (PopupMenu::highlightedBackgroundColourId, Colours::grey.withAlpha (0.7f));

    setColour (TextEditor::focusedOutlineColourId, Colour (0xffccccff));
}

MyLookAndFeel::~MyLookAndFeel(){
}


//==============================================================================


void MyLookAndFeel::drawRotarySlider (Graphics& g,
                                    int x, int y,
                                    int width, int height,
                                    float sliderPos,
                                    const float rotaryStartAngle,
                                    const float rotaryEndAngle,
                                    Slider& slider){


     const float radius = jmin (width / 2, height / 2) - 2.0f;
     const float centreX = x + width * 0.5f;
     const float centreY = y + height * 0.5f;
     const float rx = centreX - radius;
     const float ry = centreY - radius;
     const float rw = radius * 2.0f;
     const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
     const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();

     const float zeroPos = rotaryStartAngle + fabs((float)slider.getMinimum() / ((float)slider.getMaximum() - (float)slider.getMinimum())) * (rotaryEndAngle - rotaryStartAngle);


    if (radius > 12.0f)
    {
        if (slider.isEnabled()){
            g.setColour (Colours::darkblue.withAlpha (isMouseOver ? 1.0f : 0.5f));
        }else{
            g.setColour (Colours::grey.withAlpha (0.5f));
        }

        const float thickness = 0.7f;

        Path filledArc;
        filledArc.addPieSegment (rx, ry, rw, rw, zeroPos, angle, thickness);

        g.fillPath (filledArc);

        if (thickness > 0)
        {
            const float innerRadius = radius * 0.2f;
            Path p;
            p.addTriangle (-innerRadius, 0.0f,
                        0.0f, -radius * thickness * 1.1f,
                        innerRadius, 0.0f);

            p.addEllipse (-innerRadius, -innerRadius, innerRadius * 2.0f, innerRadius * 2.0f);

            g.fillPath (p, AffineTransform::rotation (angle).translated (centreX, centreY));
        }

        g.setColour (Colours::black.withAlpha (0.4f));
        Path outlineArc;
        outlineArc.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, thickness);
        outlineArc.closeSubPath();

        g.strokePath (outlineArc, PathStrokeType (slider.isEnabled() ? (isMouseOver ? 2.0f : 1.2f) : 0.3f));
    }
    else
    {
        Path p;
        p.addEllipse (-0.4f * rw, -0.4f * rw, rw * 0.8f, rw * 0.8f);
        PathStrokeType (rw * 0.1f).createStrokedPath (p, p);

        p.addLineSegment (0.0f, 0.0f, 0.0f, -radius, rw * 0.2f);

        if (slider.isEnabled())
            g.setColour (Colours::blue.withAlpha (isMouseOver ? 0.5f : 0.35f));
        else
            g.setColour (Colours::grey.withAlpha (0.5f));

        g.fillPath (p, AffineTransform::rotation (angle).translated (centreX, centreY));
    }
}


