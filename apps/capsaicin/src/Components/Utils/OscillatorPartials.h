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

#ifndef __JUCETICE_XSYNTHOSCILLATORPARTIALS_HEADER__
#define __JUCETICE_XSYNTHOSCILLATORPARTIALS_HEADER__

#include "../../StandardHeader.h"
#include "../../Misc/Master.h"

static int capsaicinOscillatorPartialsOffsetX = 3;


//==============================================================================
/**

    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!

*/
class OscillatorPartials  : public Component
{
public:

    //==============================================================================
    enum VisualMode
    {
        MagnitudeMode,
        PhaseMode
    };

    //==============================================================================
    OscillatorPartials (Master* const master_)
      : master (master_),
        oscillator (0),
        visualMode (MagnitudeMode),
        lineWidth (3),
        linkedComponent (0)
    {
    }

    ~OscillatorPartials()
    {
    }

    //==============================================================================
    void setOscillator (OscilGen* newOscillator)
    {
        oscillator = newOscillator;
    }

    void setLinkedComponent (Component* newLinkedComponent)
    {
        linkedComponent = newLinkedComponent;
    }

    void setVisualMode (const int newMode = 0)
    {
        visualMode = newMode;
    }

    //==============================================================================
    int getHarmonicFromMousePosition (const int xPos)
    {
        int harmonicNumber = roundFloatToInt ((xPos - capsaicinOscillatorPartialsOffsetX) / (float) lineWidth);
        return jmin (jmax (harmonicNumber, 0), roundFloatToInt ((getWidth() - capsaicinOscillatorPartialsOffsetX) / (float) lineWidth));
    }

    int getValueFromMousePosition (const int yPos)
    {
        return (int)((jmin (jmax (yPos, 0), getHeight()) / (float) getHeight()) * 127);
    }

    //==============================================================================
    void mouseDown (const MouseEvent& e)
    {
        if (! oscillator) return;

        clickedPartial = getHarmonicFromMousePosition (e.x);

        int newValue = 64;
        if (! e.mods.isMiddleButtonDown ())
            newValue = getValueFromMousePosition (e.y);

#if 0
        master->mutex.enter();
#endif

        if (visualMode == MagnitudeMode)
            oscillator->Phmag [clickedPartial] = newValue;
        else
            oscillator->Phphase [clickedPartial] = newValue;

        oscillator->prepare();

#if 0
        master->mutex.exit();
#endif
        repaint ();
        if (linkedComponent) linkedComponent->repaint ();
    }

    //==============================================================================
    void mouseDrag (const MouseEvent& e)
    {
        if (! oscillator) return;

        if (e.mods.isRightButtonDown () ||
            e.mods.isMiddleButtonDown ())
        {
            clickedPartial = getHarmonicFromMousePosition (e.x);
        }

        int newValue = 64;
        if (! e.mods.isMiddleButtonDown ())
            newValue = getValueFromMousePosition (e.y);

#if 0
        master->mutex.enter();
#endif

        if (visualMode == MagnitudeMode)
            oscillator->Phmag [clickedPartial] = newValue;
        else
            oscillator->Phphase [clickedPartial] = newValue;

        oscillator->prepare();

#if 0
        master->mutex.exit();
#endif

        repaint ();
        if (linkedComponent) linkedComponent->repaint ();
    }

    //==============================================================================
    void mouseWheelMove    (const MouseEvent& e, float ix, float iy)
    {
        if (! oscillator) return;

        clickedPartial = getHarmonicFromMousePosition (e.x);

#if 0
        master->mutex.enter();
#endif

        if (visualMode == MagnitudeMode)
        {
            oscillator->Phmag [clickedPartial] -= (int8) (iy * 33);
            oscillator->Phmag [clickedPartial] =
                jmin (jmax ((int) oscillator->Phmag [clickedPartial], 0), 127);
        }
        else
        {
            oscillator->Phphase [clickedPartial] -= (int8) (iy * 33);
            oscillator->Phphase [clickedPartial] =
                jmin (jmax ((int) oscillator->Phphase [clickedPartial], 0), 127);
        }

        oscillator->prepare();

#if 0
        master->mutex.exit();
#endif

        repaint ();
        if (linkedComponent) linkedComponent->repaint ();
    }

    //==============================================================================
    void paint (Graphics& g)
    {
        g.fillAll (Colours::black);
        g.setColour (Colours::darkgrey);
        g.drawHorizontalLine (getHeight() / 2, 0, getWidth());

        if (oscillator)
        {
            //draws the spectrum
            if (visualMode == MagnitudeMode)
            {
                paintPhaseAndMagnitude (g,
                                        Colours::lightblue,
                                        Colour (0xffA27484).withAlpha (0.3f),
                                        true);
            }
            else if (visualMode == PhaseMode)
            {
                paintPhaseAndMagnitude (g,
                                        Colours::lightblue.withAlpha (0.3f),
                                        Colour (0xffA27484),
                                        false);
            }
        }

        g.drawBevel (0, 0,
                     getWidth(), getHeight(),
                     capsaicinOscillatorPartialsOffsetX - 1,
                     Colour (0xff827474).darker (0.5f),
                     Colour (0xff827474).brighter (0.5f),
                     true);
    }

    void paintPhaseAndMagnitude (Graphics& g,
                                 const Colour& magnitudeColour,
                                 const Colour& phaseColour,
                                 const bool firstMagThenPhase)
    {
        int offsetX = capsaicinOscillatorPartialsOffsetX;
        float y1 = getHeight() / 2;
        int numHarmonics = jmin (MAX_AD_HARMONICS, roundFloatToInt (getWidth() / (float) lineWidth));

        //draws the spectrum
        if (firstMagThenPhase)
        {
            for (int i = 0; i < numHarmonics; i++)
            {
                float x1 = offsetX + i * lineWidth;

                float deltaMag = (oscillator->Phmag [i] - 64) / 64.0f;
                float deltaPhase = (oscillator->Phphase [i] - 64) / 64.0f;

                g.setColour (magnitudeColour);
                g.drawLine (x1, y1, x1, y1 + deltaMag * y1, (float) lineWidth);
                g.setColour (phaseColour);
                g.drawLine (x1, y1, x1, y1 + deltaPhase * y1, (float) lineWidth);
            }
        }
        else
        {
            for (int i = 0; i < numHarmonics; i++)
            {
                float x1 = offsetX + i * lineWidth;

                float deltaMag = (oscillator->Phmag [i] - 64) / 64.0f;
                float deltaPhase = (oscillator->Phphase [i] - 64) / 64.0f;

                g.setColour (phaseColour);
                g.drawLine (x1, y1, x1, y1 + deltaPhase * y1, (float) lineWidth);
                g.setColour (magnitudeColour);
                g.drawLine (x1, y1, x1, y1 + deltaMag * y1, (float) lineWidth);
            }
        }
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

    int visualMode;
    int lineWidth;

    int clickedPartial;
    Component* linkedComponent;
};


#endif   // __JUCETICE_XSYNTHOSCILLATORSPECTRUM_HEADER__
