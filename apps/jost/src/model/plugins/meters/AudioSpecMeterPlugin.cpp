/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2007 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2007 by Julian Storer.

 ------------------------------------------------------------------------------

 JUCE and JUCETICE can be redistributed and/or modified under the terms of
 the GNU Lesser General Public License, as published by the Free Software
 Foundation; either version 2 of the License, or (at your option) any later
 version.

 JUCE and JUCETICE are distributed in the hope that they will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with JUCE and JUCETICE; if not, visit www.gnu.org/licenses or write to
 Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 Boston, MA 02111-1307 USA

 ==============================================================================

    Original plugin: Paul Kellett (mda-vst.com)

 ==============================================================================
*/

#include "AudioSpecMeterPlugin.h"
#include "AudioSpecMeterEditor.h"


#define SILENCE 0.00000001f

//==============================================================================
AudioSpecMeterPlugin::AudioSpecMeterPlugin ()
{
    K = counter = 0;
    kmax = 2048;
    topband = 11;
    iK = 1.0f / (float)kmax;
    den = 1.0e-8f;
    
    releaseResources ();
}

AudioSpecMeterPlugin::~AudioSpecMeterPlugin ()
{
}

//==============================================================================
void AudioSpecMeterPlugin::setParameter (int paramNumber, float value)
{
    param[paramNumber] = value;

	switch (paramNumber)
	{
		case _PARAM0: gain = (float)pow(10.0f, 2.0f * param[paramNumber] - 1.0f); break;
		default: break;
	}
}

float AudioSpecMeterPlugin::getParameter (int paramNumber)
{
    return param[paramNumber];
}

const String AudioSpecMeterPlugin::getParameterName (int paramNumber)
{
	return String (paramNumber);
}

const String AudioSpecMeterPlugin::getParameterText (int paramNumber)
{
    char string[16];
	switch (paramNumber)
	{
		case _PARAM0: sprintf (string, "%.1f", 40.0f * param[paramNumber] - 20.0f); break;
		case _PARAM1: strcpy (string, ""); break;
		default     : sprintf (string, "%.0f", 100.0f * param[paramNumber]);
	}
	string[8] = 0;
    return String (string);
}

//==============================================================================
void AudioSpecMeterPlugin::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    if(sampleRate > 64000)
    {
        topband = 12;
        kmax = 4096;
    }
    else
    {
        topband = 11;
        kmax = 2048;
    }

    iK = 1.0f / (float)kmax; 
}

void AudioSpecMeterPlugin::releaseResources()
{
    Lpeak = Rpeak = Lrms = Rrms = Corr = 0.0f;
    lpeak = rpeak = lrms = rrms = corr = 0.0f;
    Lhold = Rhold = 0.0f;
    Lmin = Rmin = 0.0000001f;

    for (long i = 0; i < 16; i++) 
    {
        band[0][i] = band[1][i] = 0.014f;
        for (long j = 0; j < 6; j++)
            lpp[j][i] = rpp[j][i] = 0.0f;
    }
}

//==============================================================================
void AudioSpecMeterPlugin::processBlock (AudioSampleBuffer& buffer,
                                         MidiBuffer& midiMessages)
{
    const int blockSize = buffer.getNumSamples ();

    float *in1  = buffer.getSampleData (0);
    float *in2  = buffer.getSampleData (1);
//  float *out1 = outputs[0];
//  float *out2 = outputs[1];

    den = -den;
    float l, r, p, q, iN = iK;
    long k=K, j0=topband, mask, j;
    int sampleFrames = blockSize;

    while(--sampleFrames >= 0)
    {
        l = *in1++;
        r = *in2++;
//    *out1++ += l;
//    *out2++ += r;

        l += den; //anti-denormal
        r += den;
    
        lrms += l * l; //RMS integrate
        rrms += r * r;

        p = (float)fabs(l); if(p > lpeak) lpeak = p; //peak detect
        q = (float)fabs(r); if(q > rpeak) rpeak = q;
/*
    if(p > 1.0e-8f && p < lmin) lmin = p; //'trough' detect
    if(q > 1.0e-8f && q < rmin) rmin = q;
*/
        if((l * r) > 0.0f) corr += iN; //measure correlation

        j = j0;
        mask = k << 1;
        
        do //polyphase filter bank
        {
            p = lpp[0][j] + 0.208f * l;
                lpp[0][j] = lpp[1][j];
                lpp[1][j] = l - 0.208f * p;

            q = lpp[2][j] + lpp[4][j] * 0.682f;
                lpp[2][j] = lpp[3][j];
                lpp[3][j] = lpp[4][j] - 0.682f * q;
                lpp[4][j] = l;
                lpp[5][j] += (float)fabs(p - q); //top octave
            l = p + q;                    //lower octaves

            p = rpp[0][j] + 0.208f * r;
                rpp[0][j] = rpp[1][j];
                rpp[1][j] = r - 0.208f * p;

            q = rpp[2][j] + rpp[4][j] * 0.682f;
                rpp[2][j] = rpp[3][j];
                rpp[3][j] = rpp[4][j] - 0.682f * q;
                rpp[4][j] = r;
                rpp[5][j] += (float)fabs(p - q); //top octave
            r = p + q;                    //lower octaves

            j--;
            mask >>= 1;
        } while(mask & 1);
    
        if(++k == kmax)
        {
            k = 0;
            counter++; //editor waits for this to change

            if(lpeak == 0.0f) Lpeak = Lrms = 0.0f; else ///add limits here!
            {
                if(lpeak > 2.0f) lpeak = 2.0f;
                if(lpeak >= Lpeak) 
                {
                  Lpeak = lpeak;
                  Lhold = 2.0f * Lpeak; 
                }
                else 
                {
                  Lhold *= 0.95f;
                  if(Lhold < Lpeak) Lpeak = Lhold;
                }
                Lmin = lmin;
                lmin *= 1.01f;
                Lrms += 0.2f * (iN * lrms - Lrms);
            }
      
            if(rpeak == 0.0f) Rpeak = Rrms = 0.0f; else
            {
                if(rpeak > 2.0f) rpeak = 2.0f;
                if(rpeak >= Rpeak) 
                {
                  Rpeak = rpeak;
                  Rhold = 2.0f * Rpeak; 
                }
                else 
                {
                  Rhold *= 0.95f;
                  if(Rhold < Rpeak) Rpeak = Rhold;
                }
                Rmin = rmin;
                rmin *= 1.01f;
                Rrms += 0.2f * (iN * rrms - Rrms);
            }
      
            rpeak = lpeak = lrms = rrms = 0.0f;
            Corr += 0.1f * (corr - Corr); //correlation
            corr = SILENCE;

            float dec = 0.09f;
            for(j=0; j<13; j++) //spectrum output
            {
                band[0][j] += dec * (iN * lpp[5][j] - band[0][j]);
                if(band[0][j] > 2.0f) band[0][j] = 2.0f; 
                else if(band[0][j] < 0.014f) band[0][j] = 0.014f;
                
                band[1][j] += dec * (iN * rpp[5][j] - band[1][j]);
                if(band[1][j] > 2.0f) band[1][j] = 2.0f; 
                else if(band[1][j] < 0.014f) band[1][j] = 0.014f;

                rpp[5][j] = lpp[5][j] = SILENCE;
                dec = dec * 1.1f;
            }
        }
    }

    K = k;
}

//==============================================================================
AudioProcessorEditor* AudioSpecMeterPlugin::createEditor ()
{
    return new AudioSpecMeterEditor (this);
}

