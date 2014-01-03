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

#ifndef __JUCETICE_XSYNTHAUDIOSCOPE_HEADER__
#define __JUCETICE_XSYNTHAUDIOSCOPE_HEADER__

#include "../../StandardHeader.h"
#include "../../Misc/Master.h"


//==============================================================================
/**

*/
class AudioScope  : public Component,
                    public Timer
{
public:

    AudioScope (Master* const master_, const int partNumber_ = 0)
        : master (master_),
          partNumber (partNumber_)
    {
        bufferPos = 0;
        bufferSize = 512;
        maxBufferSize = 1024;
        circularBuffer = (float*) juce_calloc (sizeof (float) * maxBufferSize);
        currentInputLevel = 0.0f;
        numSamplesIn = 0;

        setOpaque (true);
        startTimer (50);  // repaint every 1/50 of a second
    }

    ~AudioScope()
    {
        stopTimer ();
        juce_free (circularBuffer);
    }

    void setPartNumber (const int newPartNumber)
    {
        clearSamples ();
        partNumber = newPartNumber;
    }

    void paint (Graphics& g)
    {
        g.fillAll (Colours::black);

        g.setColour (Colours::lightgreen);

        const float halfHeight = getHeight() * 0.5f;
        int bp = bufferPos;

        for (int x = getWidth(); --x >= 0;)
        {
            const int samplesAgo = getWidth() - x;
            const float level = circularBuffer [(bp + bufferSize - samplesAgo) % bufferSize];

            if (level > 0.01f)
                g.drawLine ((float) x, halfHeight - halfHeight * level,
                            (float) x, halfHeight + halfHeight * level);
        }

        g.drawBevel (0, 0,
                     getWidth(), getHeight(),
                     2,
                     Colour (0xff827474).darker (0.5f),
                     Colour (0xff827474).brighter (0.5f),
                     true);
    }

    void timerCallback()
    {
//        master->mutex.enter ();

        addSamples (master->part[partNumber]->partoutl,
                    master->part[partNumber]->partoutr,
                    SOUND_BUFFER_SIZE);

//        master->mutex.exit ();

        repaint ();
    }

    void addSamples (const float* inl,
                     const float* inr,
                     int numSamples)
    {
        const int samplesToAverage = 64;

        for (int i = 0; i < numSamples; ++i)
        {
            const float sample = (inl[i] + inr[i]) * 0.5;

            currentInputLevel += fabsf (sample);

            if (++numSamplesIn > samplesToAverage)
            {
                circularBuffer [bufferPos++ % bufferSize] = currentInputLevel / samplesToAverage * 2.0;

                numSamplesIn = 0;
                currentInputLevel = 0.0f;
            }
        }
    }

    void clearSamples ()
    {
        zeromem (circularBuffer, sizeof (float) * bufferSize);
    }

private:

    Master* master;
    int partNumber;

    float* circularBuffer;
    float currentInputLevel;
    int volatile bufferPos,
                 bufferSize,
                 maxBufferSize,
                 numSamplesIn;
};

#endif // __JUCETICE_XSYNTHAUDIOSCOPE_HEADER__

