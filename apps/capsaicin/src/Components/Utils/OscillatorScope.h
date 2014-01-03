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

#ifndef __JUCETICE_XSYNTHOSCILLATORSCOPE_HEADER__
#define __JUCETICE_XSYNTHOSCILLATORSCOPE_HEADER__

#include "../../StandardHeader.h"
#include "../../Misc/Master.h"


//==============================================================================
/**

    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!

*/
class OscillatorScope  : public Component
{
public:
    //==============================================================================
    OscillatorScope (Master* const master_)
      : master (master_),
        oscillator (0),
        oscbase (0),
        phase (0)
    {
    }

    ~OscillatorScope()
    {
    }

    //==============================================================================
    void setOscillator (OscilGen* newOscillator)
    {
        oscillator = newOscillator;
    }

    //==============================================================================
    void paint (Graphics& g)
    {
        int ox = 2, oy = 1, lx = getWidth() - 4, ly = getHeight() - 2;

        REALTYPE smps[OSCIL_SIZE];

        g.fillAll (Colours::black);
        g.setColour (Colours::darkgrey);
        g.drawHorizontalLine (getHeight() / 2, 0, getWidth());

        if (! oscillator) return;

        master->mutex.enter();
        if (oscbase==0) oscillator->get (smps, -1.0);
        else oscillator->getcurrentbasefunction (smps);
        master->mutex.exit();

        //normalize
        REALTYPE max = 0;
        for (int i = 0; i < OSCIL_SIZE; i++)
           if (max < fabs (smps[i])) max = fabs (smps[i]);
        if (max < 0.00001) max = 1.0;
        max = -max * 1.05;

        //draw the function
        // fl_line(ox+2,oy+ly/2,ox+lx-2,oy+ly/2);

        Path path;

        int ph = (int)((phase - 64.0) / 128.0 * OSCIL_SIZE + OSCIL_SIZE);
        for (int i = 1; i < lx; i++)
        {
           int k1 = (int)((REALTYPE)OSCIL_SIZE * (i-1) / lx) + ph;
           int k2 = (int)((REALTYPE)OSCIL_SIZE * i / lx) + ph;
           REALTYPE y1 = smps[k1 % OSCIL_SIZE] / max;
           REALTYPE y2 = smps[k2 % OSCIL_SIZE] / max;

           if (i == 1)
               path.startNewSubPath ((float)(i - 1 + ox),
                                     (float)(y1 * ly / 2.0) + oy + ly / 2);

           path.lineTo ((float)(i - 1 + ox),
                        (float)(y1 * ly / 2.0) + oy + ly / 2);

           path.lineTo ((float)(i + ox),
                        (float)(y2 * ly / 2.0) + oy + ly / 2);
        }

        g.setColour (Colours::lightblue);
        g.strokePath (path, PathStrokeType (2.0f));

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
    OscilGen* oscillator;
    int oscbase;
    int phase;
};


#endif   // __JUCETICE_XSYNTHOSCILLATORSCOPE_HEADER__
