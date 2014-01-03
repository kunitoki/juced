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

   @author  Paul Nasca
   @tweaker Lucio Asnaghi

 ==============================================================================
*/

#include "EffectLFO.h"


//==============================================================================
EffectLFO::EffectLFO()
{
    xl=0.0;
    xr=0.0;
    Pfreq=40;
    Prandomness=0;
    PLFOtype=0;
    Pstereo=96;

    updateparams();

    ampl1=(1-lfornd)+lfornd*RND;
    ampl2=(1-lfornd)+lfornd*RND;
    ampr1=(1-lfornd)+lfornd*RND;
    ampr2=(1-lfornd)+lfornd*RND;
}

EffectLFO::~EffectLFO()
{
}

//==============================================================================
void EffectLFO::updateparams()
{
    REALTYPE lfofreq = (pow (2, Pfreq / 127.0 * 10.0) - 1.0) * 0.03;
    incx = fabs (lfofreq) * (REALTYPE) SOUND_BUFFER_SIZE / (REALTYPE) SAMPLE_RATE;
    if (incx > 0.49999999) incx = 0.499999999; // Limit the Frequency

    lfornd = Prandomness / 127.0;
    if (lfornd < 0.0) lfornd = 0.0; else if (lfornd > 1.0) lfornd = 1.0;

    if (PLFOtype > 1) PLFOtype = 1; // This has to be updated if more lfo's are added
    lfotype = PLFOtype;

    xr = fmod (xl + (Pstereo - 64.0) / 127.0 + 1.0, 1.0);
}

//==============================================================================
inline REALTYPE EffectLFO::getlfoshape (REALTYPE x)
{
    REALTYPE out;
    switch (lfotype)
    {
    case 0: // EffectLFO_SINE
        out = cos (x * 2 * double_Pi); // EffectLFO_SINE
        break;
    case 1: // EffectLFO_TRIANGLE
        if ((x > 0.0) && (x < 0.25))     out = 4.0 * x;
        else if ((x > 0.25) && (x<0.75)) out = 2 - 4 * x;
        else                             out = 4.0 * x - 4.0;
        break;
    //more to be added here; also ::updateparams() need to be updated (to allow more lfotypes)
    default:
        out = 0.0;
    }
    return out;
}

//==============================================================================
void EffectLFO::effectlfoout (REALTYPE *outl,REALTYPE *outr)
{
    REALTYPE out;

    out = getlfoshape (xl);
    if ((lfotype == 0) || (lfotype == 1)) out *= (ampl1 + xl * (ampl2 - ampl1));
    xl += incx;
    if (xl > 1.0)
    {
        xl -= 1.0;
        ampl1 = ampl2;
        ampl2 = (1.0 - lfornd) + lfornd * RND;
    }
    *outl = (out + 1.0) * 0.5;

    out = getlfoshape (xr);
    if ((lfotype == 0) || (lfotype == 1)) out *= (ampr1 + xr * (ampr2 - ampr1));
    xr += incx;
    if (xr > 1.0)
    {
        xr -= 1.0;
        ampr1 = ampr2;
        ampr2 = (1.0 - lfornd) + lfornd * RND;
    }
    *outr = (out + 1.0) * 0.5;
}

