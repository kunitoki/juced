/*
  ==============================================================================

  XSynth -o- Add-Tractive delight for EnergyXT2
  Copyright 2007 by kRAkEn/gORe sounds.

  Creation:       Jan 2007
  Author:         Asnaghi Lucio
  Website:        (www.anticore.org)

  The XSynth is written with the "Jucetice library" - which is based around
  Raw Material Software ltd. "JUCE library" (Copyright 2004-7)

  ==============================================================================
*/

#ifndef __JUCETICE_XSYNTHEQGRAPH_HEADER__
#define __JUCETICE_XSYNTHEQGRAPH_HEADER__

#include "../../StandardHeader.h"
#include "../../Misc/Util.h"
#include "../../Effects/EffectMgr.h"


//==============================================================================
/**

    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!

*/
class EQGraph : public Component,
                public AudioParameterListener
{
public:

    //==============================================================================
    /** Constructor */
    EQGraph ()
      : eff (0),
        maxdB (30),
        backColour (Colours::black),
        gridColour (Colours::darkgrey),
        lineColour (Colours::lightblue),
        fillColour (Colours::lightblue.withAlpha (0.65f)),
        drawStyle (FillAndStroke),
        strokeThickness (1.5f)
    {
    }

    //==============================================================================
    void setEffectManager (EffectMgr *eff_)
    {
        eff = eff_;
    }

    //==============================================================================
    void setBackgroundColour (const Colour& colour)
    {
        backColour = colour;
    }

    void setGridColour (const Colour& colour)
    {
        gridColour = colour;
    }

    void setLineColour (const Colour& colour)
    {
        lineColour = colour;
    }

    void setFillColour (const Colour& colour)
    {
        fillColour = colour;
    }

    //==============================================================================
    enum DrawStyle
    {
        StrokeOnly    = 0,
        FillOnly      = 1,
        FillAndStroke = 2
    };

    void setDrawStyle (const DrawStyle style)
    {
        drawStyle = style;
    }

    //==============================================================================
    void setStrokeThickness (const float stroke)
    {
        strokeThickness = stroke;
    }

    //==============================================================================
    void paintFreqLine (Graphics& g, REALTYPE freq, int type)
    {
        REALTYPE freqx = getFrequencyPosition (freq);
        if (freqx > 0.0 && freqx < 1.0)
        {
            g.drawLine (0 + (int) (freqx * getWidth()),
                        0,
                        0 + (int) (freqx * getWidth()),
                        0 + getHeight());
        }
    }

    void paint (Graphics& g)
    {
        int ox = 0, oy = 0, lx = getWidth(), ly = getHeight();

        g.fillAll (backColour);

        // paint grid !
        if (gridColour != backColour)
        {
            g.setColour (gridColour);

            g.drawLine (ox + 2,
                        oy + ly / 2,
                        ox + lx - 2,
                        oy + ly / 2, 2.0f);

            REALTYPE freqx = getFrequencyPosition (1000.0);
            if (freqx > 0.0 && freqx < 1.0)
                g.drawLine (ox + (int) (freqx * lx),
                            oy,
                            ox + (int) (freqx * lx),
                            oy + ly);

            for (int i = 1; i < 10; i++)
            {
                if (i == 1)
                {
                    paintFreqLine (g, i * 100.0, 0);
                    paintFreqLine (g, i * 1000.0, 0);
                }
                else if (i == 5)
                {
                    paintFreqLine (g, i * 10.0, 2);
                    paintFreqLine (g, i * 100.0, 2);
                    paintFreqLine (g, i * 1000.0, 2);
                }
                else
                {
                    paintFreqLine (g, i * 10.0, 1);
                    paintFreqLine (g, i * 100.0, 1);
                    paintFreqLine (g, i * 1000.0, 1);
                }
            }

//            paintFreqLine (g, 10000.0, 0);
//            paintFreqLine (g, 20000.0, 1);

            int GY = 6;
            if (ly < GY * 3) GY = -1;
            for (int i = 1; i < GY; i++)
            {
                int tmp = (int)(ly / (REALTYPE) GY * i);
                g.drawLine (ox + 2,
                            oy + tmp,
                            ox + lx - 2,
                            oy + tmp);
            }
        }

        Path path;

        // draw the frequency response
        int iy, oiy = getResponse (ly, getFrequencyX (0.0));

        for (int i = 1; i < lx; i++)
        {
            REALTYPE frq = getFrequencyX (i / (REALTYPE) lx);
            if (frq > SAMPLE_RATE / 2) break;
            iy = getResponse (ly, frq);

            if (i == 1)
                path.startNewSubPath ((float)(ox + i - 1),
                                      (float)(oy + ly - oiy));

            path.lineTo ((float)(ox + i - 1),
                         (float)(oy + ly - oiy));

            path.lineTo ((float)(ox + i),
                         (float)(oy + ly - iy));
            oiy = iy;
        }

        // fill path if we want it to
        if (drawStyle != StrokeOnly)
        {
            Path pathToFill (path);

            pathToFill.lineTo ((float) getWidth(), (float) getHeight());
            pathToFill.lineTo (0.0f, (float) getHeight());
            pathToFill.closeSubPath ();

            g.setColour (fillColour);
            g.fillPath (pathToFill);
        }

        // stroke path if we want it to
        if (drawStyle == StrokeOnly
            || drawStyle == FillAndStroke)
        {
            g.setColour (lineColour);
            g.strokePath (path, PathStrokeType (strokeThickness));
        }

        // draw bevel
        g.drawBevel (0, 0,
                     getWidth(), getHeight(),
                     2,
                     Colour (0xff827474).darker (0.5f),
                     Colour (0xff827474).brighter (0.5f),
                     true);
    }

    void resized ()
    {
        repaint ();
    }

    void parameterChanged (AudioParameter* parameter,
                           const int index)
    {
        repaint ();
    }


protected:

    int getResponse (int maxy, REALTYPE freq)
    {
        if (eff == 0) return 0;

        REALTYPE dbresp = eff->getEQfreqresponse(freq);
        return (int) ((dbresp / maxdB + 1.0) * maxy / 2.0);
    }

    REALTYPE getFrequencyX (REALTYPE x)
    {
        if (x > 1.0) x = 1.0;
        return 20.0 * pow (1000.0, x);
    }

    REALTYPE getFrequencyPosition (REALTYPE freq)
    {
        if (freq < 0.00001) freq = 0.00001;
        return log (freq / 20.0) / log (1000.0);
    }

    EffectMgr *eff;
    int maxdB;

    Colour backColour;
    Colour gridColour;
    Colour lineColour;
    Colour fillColour;

    DrawStyle drawStyle;
    float strokeThickness;
};


#endif
