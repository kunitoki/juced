/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2004 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2004 by Julian Storer.

 ------------------------------------------------------------------------------

 JUCE and JUCETICE can be redistributed and/or modified under the terms of
 the GNU General Public License, as published by the Free Software Foundation;
 either version 2 of the License, or (at your option) any later version.

 JUCE and JUCETICE are distributed in the hope that they will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with JUCE and JUCETICE; if not, visit www.gnu.org/licenses or write to
 Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 Boston, MA 02111-1307 USA

 ------------------------------------------------------------------------------

 If you'd like to release a closed-source product which uses JUCE, commercial
 licenses are also available: visit www.rawmaterialsoftware.com/juce for
 more information.

 ==============================================================================
*/

#ifndef __JUCETICE_JOSTAUDIOBUFFERDISPLAY_HEADER__
#define __JUCETICE_JOSTAUDIOBUFFERDISPLAY_HEADER__

#include "../../StandardHeader.h"


//==============================================================================
/**

*/
class AudioBufferDisplay
{
public:

    //==============================================================================
    AudioBufferDisplay (AudioSampleBuffer* input,
                        const float resampleRatio)
      : sample (input),
        ratio (resampleRatio)
    {
    }

    //==============================================================================
    void paintAudioBuffer (Graphics& g,
                           const int x,
                           const int y,
                           const int width,
                           const int height,
                           const int channel = 0)
    {
        jassert (sample);

        const float halfHeight = height * 0.5f;

        float* sampleBuffer = sample->getSampleData (channel);
        const int sampleLength = roundFloatToInt (sample->getNumSamples () / ratio);

        for (int i = 0; i < width; i++)
        {
            const int sampleToDo = (int) ((sampleLength * i) / (float) width);
            const int sampleNext = (int) ((sampleLength * (i + 1)) / (float) width);

            float level = fabsf (sampleBuffer [sampleToDo]);

            for (int j = sampleToDo + 1; j < jmin (sampleNext, sampleLength - 1); j++)
            {
//                level = jmax (level, fabsf (sampleBuffer [j]));
                level = (level + fabsf (sampleBuffer [j])) * 0.5f;
            }

            if (level > 0.01f)
                g.drawLine ((float) x + i, (y + halfHeight) - (y + halfHeight) * level,
                            (float) x + i, (y + halfHeight) + (y + halfHeight) * level, 0.8f);
        }
    }


private:

    AudioSampleBuffer* sample;
    float ratio;
};

#endif // __JUCETICE_AUDIOSCOPECOMPONENT_H

