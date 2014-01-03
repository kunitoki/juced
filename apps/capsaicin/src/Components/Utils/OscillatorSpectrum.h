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

#ifndef __JUCETICE_XSYNTHOSCILLATORSPECTRUM_HEADER__
#define __JUCETICE_XSYNTHOSCILLATORSPECTRUM_HEADER__

#include "../../StandardHeader.h"
#include "../../Misc/Master.h"


//==============================================================================
/**

    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!

*/
class OscillatorSpectrum  : public Component
{
public:
    //==============================================================================
    OscillatorSpectrum (Master* const master_)
      : master (master_),
        oscillator (0),
        oscbase (0)
    {
    }

    ~OscillatorSpectrum()
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

        const int maxdb = 60; // must be multiple of 10
        int GX = 2;
        int n = lx / GX - 1;
        if (n > OSCIL_SIZE / 2) n = OSCIL_SIZE / 2;

        REALTYPE x;
        REALTYPE spc[n];
        for (int i = 0; i < n; i++) spc[i] = 0.0;

        master->mutex.enter ();
        if (oscbase == 0) oscillator->getspectrum (n, spc, 0);
        else oscillator->getspectrum (n, spc, 1);
        master->mutex.exit ();

        //normalize
        REALTYPE max = 0;
        for (int i = 0; i < n; i++)
        {
           x = fabs (spc[i]);
           if (max < x) max = x;
        }
        if (max < 0.000001) max = 1.0;
        max = max * 1.05;

        g.fillAll (Colours::black);

/*
        g.setColour (Colours::blue);

        for (int i = 1; i < maxdb / 10; i++)
        {
            int ky = (int)((REALTYPE)i * ly * 10.0 / maxdb) / 2;
            ky *= 2;
            g.drawLine (ox,
                        oy + ky - 1,
                        ox + lx - 2,
                        oy + ky - 1);
        }

        for (int i = 2; i < n; i++)
        {
            int tmp = i * GX - 2;
            if (i % 10 == 1) g.setColour (Colours::black);
            else g.setColour (Colours::blue);
            g.drawLine (ox + tmp,
                        oy + 2,
                        ox + tmp,
                        oy + ly - 2);
        }
*/

        g.setColour (Colours::lightblue);

        //draws the spectrum
        for (int i = 0; i < n; i+=2)
        {
           int tmp = i * GX + 2;
           x = spc[i] / max;

           if (x > dB2rap (-maxdb))
               x = rap2dB (x) / maxdb + 1;
           else
               x = 0;

           int val = (int) ((ly - 2) * x);
           if (val > 0)
               g.drawLine (ox + tmp,
                           oy + ly - 2 - val,
                           ox + tmp,
                           oy + ly - 2, 2.0);
        }

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
};


#endif   // __JUCETICE_XSYNTHOSCILLATORSPECTRUM_HEADER__
