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

#include "SC4Compressor.h"

#define A_TBL 256

//==============================================================================
SC4Compressor::SC4Compressor (int insertion_, REALTYPE *efxoutl_, REALTYPE *efxoutr_)
{
    efxoutl = efxoutl_;
    efxoutr = efxoutr_;
    filterpars = NULL;

    insertion = insertion_;

    // initialization
    rms = rms_env_new();
    sum = 0.0f;
    amp = 0.0f;
    gain = 0.0f;
    gain_t = 0.0f;
    env = 0.0f;
    env_rms = 0.0f;
    env_peak = 0.0f;
    count = 0;

    as = (float*) malloc (A_TBL * sizeof(float));
    as[0] = 1.0f;
    for (int i = 1; i < A_TBL; i++)
      as[i] = expf(-1.0f / (SAMPLE_RATE * (float)i / (float)A_TBL));

    db_init(); // @TODO - keep out !

    Ppreset = 0;
    setPreset (Ppreset);
}

SC4Compressor::~SC4Compressor ()
{
    rms_env_free (rms);
    free (as);
}

//==============================================================================
void SC4Compressor::clean ()
{
}

//==============================================================================
void SC4Compressor::out (REALTYPE *smpsl, REALTYPE *smpsr, const int numSamples)
{
    for (int pos = 0; pos < numSamples; pos++)
    {
      const float la = fabs (smpsl[pos]);
      const float ra = fabs (smpsr[pos]);
      const float lev_in = f_max (la, ra);
      sum += lev_in * lev_in;

      if (amp > env_rms)
        env_rms = env_rms * ga + amp * (1.0f - ga);
      else
        env_rms = env_rms * gr + amp * (1.0f - gr);
      round_to_zero (&env_rms);

      if (lev_in > env_peak)
        env_peak = env_peak * ga + lev_in * (1.0f - ga);
      else
        env_peak = env_peak * gr + lev_in * (1.0f - gr);
      round_to_zero (&env_peak);

      if ((count++ & 3) == 3)
      {
        amp = rms_env_process (rms, sum * 0.25f);
        sum = 0.0f;
        if (std::isnan (env_rms)) // This can happen sometimes, but I don't know why
          env_rms = 0.0f;

        env = lin_interp (rms_peak, env_rms, env_peak);

        if (env <= knee_min) {
          gain_t = 1.0f;
        } else if (env < knee_max) {
          const float x = -(threshold - knee - lin2db (env)) / knee;
          gain_t = db2lin (-knee * rs * x * x * 0.25f);
        } else {
          gain_t = db2lin ((threshold - lin2db (env)) * rs);
        }
      }
      gain = gain * ef_a + gain_t * ef_ai;
      efxoutl[pos] = smpsl[pos] * gain * mug;
      efxoutr[pos] = smpsr[pos] * gain * mug;
    }
}

//==============================================================================
void SC4Compressor::setParameter (int npar, uint8 value)
{
    switch (npar) {
    case 0:
        Pvolume = value;
        set_volume (value / 127.0f);
        break;
    case 1:
        Ppan = value;
//        set_pan (value / 127.0f);
        break;
    case 2:
        Ppeak = value;
        rms_peak = (value < 64) ? 0 : 1;
        break;
    case 3:
        Pattack = value;
        attack = 1.5f + (value / 127.0f) * 398.5f;
        ga = attack < 2.0f ? 0.0f : as[f_round (attack * 0.001f * (float)(A_TBL-1))];
        ef_a = ga * 0.25f;
        ef_ai = 1.0f - ef_a;
        break;
    case 4:
        Prelease = value;
        release = 2.0f + (value / 127.0f) * 798.0f;
        gr = as[f_round (release * 0.001f * (float)(A_TBL-1))];
        break;
    case 5:
        Pthreshold = value;
        threshold = -30 * (1.0f - (value / 127.0f));
        knee_min = db2lin (threshold - knee);
        knee_max = db2lin (threshold + knee);
        break;
    case 6:
        Pratio = value;
        ratio = 1.0f + (value / 127.0f) * 19.0f;
        rs = (ratio - 1.0f) / ratio;
        break;
    case 7:
        Pknee = value;
        knee = 1.0f + (value / 127.0f) * 9.0f;
        knee_min = db2lin (threshold - knee);
        knee_max = db2lin (threshold + knee);
        break;
    case 8:
        Pmakeup = value;
        makeup_gain = (value / 127.0f) * 24.0f;
        mug = db2lin (makeup_gain);
        break;
    }
}

uint8 SC4Compressor::getParameter (int npar)
{
    switch (npar) {
    case 0: return Pvolume;
    case 1: return Ppan;
    case 2: return Ppeak < 64 ? 0 : 127;
    case 3: return Pattack;
    case 4: return Prelease;
    case 5: return Pthreshold;
    case 6: return Pratio;
    case 7: return Pknee;
    case 8: return Pmakeup;
    }
    return 0; //in case of bogus parameter number
}

//==============================================================================
void SC4Compressor::set_volume (float value)
{
    if (insertion == 0) {
        outvolume = pow (0.01, (1.0-value))*4.0;
        volume = 1.0;
    } else {
        volume = outvolume = value;
        if (volume == 0) clean();
    }
}

//==============================================================================
void SC4Compressor::setPreset (uint8 npreset)
{
    const int PRESET_SIZE = 9;
    const int NUM_PRESETS = 1;

    uint8 presets[NUM_PRESETS][PRESET_SIZE] =
    {
        // basic compressor
        {100,64,127,10,44,100,80,100,24}
    };

    if (npreset >= NUM_PRESETS) npreset = NUM_PRESETS - 1;
    for (int n = 0; n < PRESET_SIZE; n++) setParameter (n, presets[npreset][n]);
    Ppreset = npreset;
}

