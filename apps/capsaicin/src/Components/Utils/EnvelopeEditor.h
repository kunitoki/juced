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

#ifndef __JUCETICE_XSYNTHENVELOPEEDITOR_HEADER__
#define __JUCETICE_XSYNTHENVELOPEEDITOR_HEADER__

#include "../../StandardHeader.h"
#include "../../Misc/Master.h"


//==============================================================================
/**

    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!

*/
class EnvelopeEditor  : public Component
{
public:
    //==============================================================================
    EnvelopeEditor (Master* const master_)
      : master (master_),
        envelope (0),
        bidirectional (false)
    {
    }

    ~EnvelopeEditor()
    {
    }

    //==============================================================================
    void setEnvelope (EnvelopeParams* newEnvelope, const bool bidirectional_ = false)
    {
        envelope = newEnvelope;
        bidirectional = bidirectional_;
    }

    //==============================================================================
    void paint (Graphics& g)
    {
        int ox = 2, oy = 4, lx = getWidth() - 4, ly = getHeight() - 8;

        g.fillAll (Colours::black);

        if (envelope)
        {
            uint i;
            float lastX = 0, lastY = ly;
            float sustainX = -1, sustainY = -1;
            float deltaMult = 0.0f, deltaSum = 0.0f, invSum = 0.0f;
            Path path;

            for (i = 0; i < envelope->Penvpoints; i++)
                deltaSum += envelope->Penvdt [i];
            invSum = 1.0f / deltaSum;

            // compute first point
            if (envelope->Penvpoints > 0)
            {
                deltaMult = envelope->Penvdt[0] * invSum;

                lastX = ox + lx * (deltaMult);
                lastY = oy + ly * (1.0f - (envelope->Penvval[0] / 127.0f));

                path.startNewSubPath (lastX, lastY);
            }

            // compute path steps
            for (i = 1; i < envelope->Penvpoints; i++)
            {
                deltaMult = envelope->Penvdt[i] * invSum;

                float x = lastX + lx * (deltaMult);
                float y = oy + ly * (1.0f - (envelope->Penvval[i] / 127.0f));

                if (envelope->Plinearenvelope)
                {
                    path.lineTo (x, y);
                }
                else
                {
                    if (bidirectional)
                    {
                        path.quadraticTo (x, lastY, x, y);
                    }
                    else
                    {
                        if (i == 1)
                            path.quadraticTo (x, jmax (y, lastY), x, y);
                        else
                            path.quadraticTo (lastX, jmax (y, lastY), x, y);
                    }
                }

                if (envelope->Penvsustain == i)
                {
                    sustainX = x;
                    sustainY = y;
                }

                lastX = x;
                lastY = y;
            }

            // sustain visuals
            g.setColour (Colours::lightblue.withAlpha (0.5f));
            if (bidirectional)
            {
                g.drawHorizontalLine (getHeight() / 2, 0, getWidth());
            }
            else if (sustainX != -1 && sustainY != -1)
            {
                g.drawVerticalLine ((int) sustainX, 0, getHeight());
                g.drawHorizontalLine ((int) sustainY, 0, getWidth());
            }

            // stroke envelope path
            g.setColour (Colours::lightblue);
            g.strokePath (path, PathStrokeType (2.0f));

            // milliseconds string
            /*
            double milliseconds = (pow (2.0, (deltaSum / 127.0) * 12.0) - 1.0) * 10.0 * 1000.0; // seconds
            Font font (8.0f);
            g.setColour (Colours::white);
            g.drawSingleLineText (String (milliseconds, 3),
                                  lx - font.getStringWidth (String (milliseconds, 3)),
                                  ly);
            */
        }

        // draw bevel inside
        g.drawBevel (0, 0,
                     getWidth(), getHeight(),
                     2,
                     Colour (0xff827474).darker (0.5f),
                     Colour (0xff827474).brighter (0.5f),
                     true);
    }

    //==============================================================================
    void resized()
    {
        repaint();
    }

    //==============================================================================
    juce_UseDebuggingNewOperator

protected:

    Master* master;
    EnvelopeParams* envelope;
    int oscbase;
    int phase;
    
    bool bidirectional;
};


#endif   // __JUCETICE_XSYNTHOSCILLATORSCOPE_HEADER__
