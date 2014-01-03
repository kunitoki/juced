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

#include "EQ.h"


//==============================================================================
EQ::EQ (int insertion_, REALTYPE *efxoutl_, REALTYPE *efxoutr_)
{
    efxoutl = efxoutl_;
    efxoutr = efxoutr_;
    insertion = insertion_;
    filterpars = NULL;

    for (int i = 0; i < MAX_EQ_BANDS; i++)
    {
        filter[i].Ptype = 0;
        filter[i].Pfreq = 64;
        filter[i].Pgain = 64;
        filter[i].Pq = 64;
        filter[i].Pstages = 0;
        filter[i].l = new AnalogFilter (6, 1000.0, 1.0, 0);
        filter[i].r = new AnalogFilter (6, 1000.0, 1.0, 0);
    }

    //default values
    Ppreset = 0;
    Pvolume = 0;
    Pdrywet = 127;

    setPreset (Ppreset);
    clean();
}

EQ::~EQ()
{
}

//==============================================================================
void EQ::clean()
{
    for (int i = 0; i < MAX_EQ_BANDS; i++)
    {
        filter[i].l->cleanup();
        filter[i].r->cleanup();
    }
}

//==============================================================================
void EQ::out (REALTYPE *smpsl, REALTYPE *smpsr, const int numSamples)
{
    int i;
    for (i = 0; i < numSamples; i++)
    {
        efxoutl[i] = smpsl[i] * volume;
        efxoutr[i] = smpsr[i] * volume;
    }

    for (i = 0; i < MAX_EQ_BANDS; i++)
    {
        if (filter[i].Ptype == 0) continue;
        filter[i].l->filterout (efxoutl, numSamples);
        filter[i].r->filterout (efxoutr, numSamples);
    }

    for (i = 0; i < numSamples; i++)
    {
        efxoutl[i] = smpsl[i] * (1.0f - drywet) + efxoutl[i] * drywet;
        efxoutr[i] = smpsr[i] * (1.0f - drywet) + efxoutr[i] * drywet;
    }
}

//==============================================================================
void EQ::setParameter (int npar, uint8 value)
{
    switch (npar)
    {
    case 0: setvolume(value); break;
    case 1: setdrywet(value); break;
    }
    if (npar < 10) return;

    int nb = (npar - 10) / 5; //number of the band (filter)
    if (nb >= MAX_EQ_BANDS) return;
    int bp = npar % 5; //band paramenter

    REALTYPE tmp;
    switch (bp)
    {
    case 0: if (value > 9) value = 0; // has to be changed if more filters will be added
            filter[nb].Ptype = value;
            if (value != 0)
            {
                filter[nb].l->settype (value - 1);
                filter[nb].r->settype (value - 1);
            }
            break;
    case 1: filter[nb].Pfreq = value;
            tmp = 600.0 * pow (30.0,(value - 64.0) / 64.0);
            filter[nb].l->setfreq (tmp);
            filter[nb].r->setfreq (tmp);
            break;
    case 2: filter[nb].Pgain = value;
            tmp = 30.0 * (value - 64.0) / 82.0; // original was: - 64.0) / 64.0
            filter[nb].l->setgain (tmp);
            filter[nb].r->setgain (tmp);
            break;
    case 3: filter[nb].Pq = value;
            tmp = pow (30.0, (value - 64.0) / 64.0);
            filter[nb].l->setq (tmp);
            filter[nb].r->setq (tmp);
            break;
    case 4: if (value>=MAX_FILTER_STAGES) value=MAX_FILTER_STAGES-1;
            filter[nb].Pstages=value;
            filter[nb].l->setstages (value);
            filter[nb].r->setstages (value);
            break;
    }
}

uint8 EQ::getParameter (int npar)
{
    switch (npar)
    {
    case 0: return(Pvolume);  break;
    case 1: return(Pdrywet);  break;
    }

    if (npar < 10) return (0);

    int nb = (npar - 10) / 5; //number of the band (filter)
    if (nb >= MAX_EQ_BANDS) return(0);
    int bp = npar % 5; //band paramenter

    switch (bp)
    {
    case 0: return(filter[nb].Ptype);      break;
    case 1: return(filter[nb].Pfreq);      break;
    case 2: return(filter[nb].Pgain);      break;
    case 3: return(filter[nb].Pq);         break;
    case 4: return(filter[nb].Pstages);    break;
    }

    return (0); //in case of bogus parameter number
}

//==============================================================================
void EQ::setvolume (uint8 Pvolume)
{
    this->Pvolume=Pvolume;

    outvolume = pow (0.005, (1.0 - Pvolume / 127.0)) * 10.0;
    if (insertion == 0)
    {
        volume = 1.0;
    }
    else
    {
        volume = outvolume;
    }
}

//==============================================================================
void EQ::setdrywet (uint8 Pdrywet)
{
    this->Pdrywet=Pdrywet;
    drywet = Pdrywet / 127.0f;
}

//==============================================================================
void EQ::setPreset (uint8 npreset)
{
    const int PRESET_SIZE = 2;
    const int NUM_PRESETS = 2;
    uint8 presets[NUM_PRESETS][PRESET_SIZE] = {
        //EQ 1
        {64, 127},
        //EQ 2
        {64, 127}
    };

    if (npreset >= NUM_PRESETS) npreset = NUM_PRESETS - 1;
    for (int n = 0; n < PRESET_SIZE; n++) setParameter (n, presets[npreset][n]);
    Ppreset = npreset;
}

//==============================================================================
REALTYPE EQ::getFrequencyResponse (REALTYPE freq)
{
    REALTYPE resp = 1.0;

    for (int i = 0; i < MAX_EQ_BANDS; i++)
    {
        if (filter[i].Ptype == 0) continue;
        resp *= filter[i].l->H (freq);
    }
    return rap2dB (resp * outvolume);
}
