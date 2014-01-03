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

#ifndef __JUCETICE_XSYNTHDYNAMICFILTER_HEADER__
#define __JUCETICE_XSYNTHDYNAMICFILTER_HEADER__

#include "Effect.h"
#include "EffectLFO.h"
#include "../DSP/Filter.h"


class DynamicFilter : public Effect
{
public:

    DynamicFilter (int insetion_, REALTYPE *efxoutl_, REALTYPE *efxoutr_);
    ~DynamicFilter();

    void setPreset (uint8 npreset);
    void setParameter (int npar, uint8 value);
    uint8 getParameter (int npar);
    void out (REALTYPE *smpsl, REALTYPE *smpsr, const int numSamples);
    void clean();

//    void setdryonly();

private:

    EffectLFO lfo;       // lfo DynamicFilter
    uint8 Pvolume;
    uint8 Ppanning;
    uint8 Pdepth;        // the depth of the lfo of the DynamicFilter
    uint8 Pampsns;       // how the filter varies according to the input amplitude
    uint8 Pampsnsinv;    // if the filter freq is lowered if the input amplitude rises
    uint8 Pampsmooth;    // how smooth the input amplitude changes the filter

    void setvolume (uint8 Pvolume);
    void setpanning (uint8 Ppanning);
    void setdepth (uint8 Pdepth);
    void setampsns (uint8 Pampsns);

    void reinitfilter();

    int insertion;
    REALTYPE panning, depth, ampsns, ampsmooth;
    Filter *filterl, *filterr;
    REALTYPE ms1, ms2, ms3, ms4; //mean squares
};

#endif

