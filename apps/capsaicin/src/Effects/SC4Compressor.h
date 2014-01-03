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

   @author  Steve Harris
   @tweaker Lucio Asnaghi

 ==============================================================================
*/

#ifndef __JUCETICE_XSYNTHSC4COMPRESSOR_HEADER__
#define __JUCETICE_XSYNTHSC4COMPRESSOR_HEADER__

#include "Effect.h"
#include "EffectUtility.h"


class SC4Compressor : public Effect
{
public:

    SC4Compressor (int insertion_, REALTYPE *efxoutl_, REALTYPE *efxoutr_);
    ~SC4Compressor ();

    void setPreset (uint8 npreset);
    void setParameter (int npar, uint8 value);
    uint8 getParameter (int npar);
    void out (REALTYPE *smpsl, REALTYPE *smpsr, const int numSamples);
    void clean();

private:

    // preset parameters
    uint8 Pvolume;
    uint8 Ppan;
    uint8 Ppeak;
    uint8 Pattack;
    uint8 Prelease;
    uint8 Pthreshold;
    uint8 Pratio;
    uint8 Pknee;
    uint8 Pmakeup;

    void set_volume (float value);

    // real parameters
    REALTYPE rms_peak;
    REALTYPE attack;
    REALTYPE release;
    REALTYPE threshold;
    REALTYPE ratio;
    REALTYPE knee;
    REALTYPE makeup_gain;

    // internal parameter deltas
    REALTYPE ga, gr, rs, mug;
    REALTYPE knee_min, knee_max;
    REALTYPE ef_a, ef_ai;

    // private values
    int          insertion;
    float        amp;
    float *      as;
    unsigned int count;
    float        env;
    float        env_peak;
    float        env_rms;
    float        gain;
    float        gain_t;
    rms_env *    rms;
    float        sum;
};


#endif
