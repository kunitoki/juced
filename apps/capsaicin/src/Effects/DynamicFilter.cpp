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

#include <cmath>
#include <cstdio>

#include "DynamicFilter.h"


//==============================================================================
DynamicFilter::DynamicFilter (int insertion_, REALTYPE *efxoutl_, REALTYPE *efxoutr_)
{
    efxoutl = efxoutl_;
    efxoutr = efxoutr_;

    insertion = insertion_;

    Ppreset = 0;
    filterl = NULL;
    filterr = NULL;
    filterpars = new FilterParams(0, 64, 64);
    setPreset (Ppreset);
    clean();
}

DynamicFilter::~DynamicFilter()
{
    delete (filterpars);
    delete (filterl);
    delete (filterr);
}

//==============================================================================
void DynamicFilter::out (REALTYPE *smpsl, REALTYPE *smpsr, const int numSamples)
{
    int i;
    if (filterpars->changed)
    {
        filterpars->changed = false;
        clean();
    }

    REALTYPE lfol, lfor;
    lfo.effectlfoout (&lfol, &lfor);
    lfol *= depth * 5.0;
    lfor *= depth * 5.0;
    REALTYPE freq = filterpars->getfreq();
    REALTYPE q = filterpars->getq();

    for (i = 0; i < numSamples; i++)
    {
        efxoutl[i] = smpsl[i];
        efxoutr[i] = smpsr[i];

        REALTYPE x = (fabs (smpsl[i]) + fabs (smpsr[i])) * 0.5;
        ms1 = ms1 * (1.0 - ampsmooth) + x * ampsmooth + 1e-10;
    }

    REALTYPE ampsmooth2 = pow (ampsmooth, 0.2) * 0.3;
    ms2 = ms2 * (1.0 - ampsmooth2) + ms1 * ampsmooth2;
    ms3 = ms3 * (1.0 - ampsmooth2) + ms2 * ampsmooth2;
    ms4 = ms4 * (1.0 - ampsmooth2) + ms3 * ampsmooth2;
    REALTYPE rms = (sqrt (ms4)) * ampsns;

    REALTYPE frl = filterl->getrealfreq (freq + lfol + rms);
    REALTYPE frr = filterr->getrealfreq (freq + lfor + rms);

    filterl->setfreq_and_q (frl, q);
    filterr->setfreq_and_q (frr, q);

    filterl->filterout (efxoutl, numSamples);
    filterr->filterout (efxoutr, numSamples);

    //panning
    for (i = 0; i < numSamples; i++)
    {
        efxoutl[i] *= panning;
        efxoutr[i] *= (1.0 - panning);
    }
}

//==============================================================================
void DynamicFilter::clean()
{
    reinitfilter();
    ms1 = 0.0;
    ms2 = 0.0;
    ms3 = 0.0;
    ms4 = 0.0;
}

//==============================================================================
void DynamicFilter::setParameter (int npar, uint8 value)
{
    switch (npar)
    {
    case 0: setvolume (value);
            break;
    case 1: setpanning (value);
            break;
    case 2: lfo.Pfreq = value;
            lfo.updateparams();
            break;
    case 3: lfo.Prandomness = value;
            lfo.updateparams();
            break;
    case 4: lfo.PLFOtype = value;
            lfo.updateparams();
            break;
    case 5: lfo.Pstereo = value;
            lfo.updateparams();
            break;
    case 6: setdepth (value);
            break;
    case 7: setampsns (value);
            break;
    case 8: Pampsnsinv = value;
            setampsns (Pampsns);
            break;
    case 9: Pampsmooth = value;
            setampsns (Pampsns);
            break;
    }
}

uint8 DynamicFilter::getParameter (int npar)
{
    switch (npar)
    {
    case 0: return(Pvolume);           break;
    case 1: return(Ppanning);          break;
    case 2: return(lfo.Pfreq);         break;
    case 3: return(lfo.Prandomness);   break;
    case 4: return(lfo.PLFOtype);      break;
    case 5: return(lfo.Pstereo);       break;
    case 6: return(Pdepth);            break;
    case 7: return(Pampsns);           break;
    case 8: return(Pampsnsinv);        break;
    case 9: return(Pampsmooth);        break;
    default:return (0);
    }
}

//==============================================================================
void DynamicFilter::setdepth (uint8 Pdepth)
{
    this->Pdepth = Pdepth;
    depth = pow ((Pdepth / 127.0), 2.0);
}

void DynamicFilter::setvolume (uint8 Pvolume)
{
    this->Pvolume = Pvolume;
    outvolume = Pvolume / 127.0;
    if (insertion == 0) volume = 1.0;
    else                volume = outvolume;
}

void DynamicFilter::setpanning (uint8 Ppanning)
{
    this->Ppanning = Ppanning;
    panning = Ppanning / 127.0;
}

void DynamicFilter::setampsns (uint8 Pampsns)
{
    ampsns = pow (Pampsns / 127.0, 2.5) * 10.0;
    if (Pampsnsinv != 0) ampsns = -ampsns;
    ampsmooth = exp (-Pampsmooth / 127.0 * 10.0) * 0.99;
    this->Pampsns = Pampsns;
}

void DynamicFilter::reinitfilter()
{
    if (filterl != NULL) delete (filterl);
    if (filterr != NULL) delete (filterr);
    filterl = new Filter (filterpars);
    filterr = new Filter (filterpars);
}

//==============================================================================
void DynamicFilter::setPreset (uint8 npreset)
{
    const int PRESET_SIZE=10;
    const int NUM_PRESETS=5;

    uint8 presets[NUM_PRESETS][PRESET_SIZE]={
        //WahWah
        {110,64,80,0,0,64,0,90,0,60},
        //AutoWah
        {110,64,70,0,0,80,70,0,0,60},
        //Sweep
        {100,64,30,0,0,50,80,0,0,60},
        //VocalMorph1
        {110,64,80,0,0,64,0,64,0,60},
        //VocalMorph1
        {127,64,50,0,0,96,64,0,0,60}
    };

    if (npreset >= NUM_PRESETS) npreset = NUM_PRESETS - 1;
    for (int n = 0; n < PRESET_SIZE; n++) setParameter (n, presets[npreset][n]);

    filterpars->defaults();
    switch (npreset)
    {
    case 0:
        filterpars->Pcategory=0;
        filterpars->Ptype=2;
        filterpars->Pfreq=45;
        filterpars->Pq=64;
        filterpars->Pstages=1;
        filterpars->Pgain=64;
        break;
    case 1:
        filterpars->Pcategory=2;
        filterpars->Ptype=0;
        filterpars->Pfreq=72;
        filterpars->Pq=64;
        filterpars->Pstages=0;
        filterpars->Pgain=64;
        break;
    case 2:
        filterpars->Pcategory=0;
        filterpars->Ptype=4;
        filterpars->Pfreq=64;
        filterpars->Pq=64;
        filterpars->Pstages=2;
        filterpars->Pgain=64;
        break;
    case 3:
        filterpars->Pcategory=1;
        filterpars->Ptype=0;
        filterpars->Pfreq=50;
        filterpars->Pq=70;
        filterpars->Pstages=1;
        filterpars->Pgain=64;

        filterpars->Psequencesize=2;
        // "I"
        filterpars->Pvowels[0].formants[0].freq=34;
        filterpars->Pvowels[0].formants[0].amp=127;
        filterpars->Pvowels[0].formants[0].q=64;
        filterpars->Pvowels[0].formants[1].freq=99;
        filterpars->Pvowels[0].formants[1].amp=122;
        filterpars->Pvowels[0].formants[1].q=64;
        filterpars->Pvowels[0].formants[2].freq=108;
        filterpars->Pvowels[0].formants[2].amp=112;
        filterpars->Pvowels[0].formants[2].q=64;
        // "A"
        filterpars->Pvowels[1].formants[0].freq=61;
        filterpars->Pvowels[1].formants[0].amp=127;
        filterpars->Pvowels[1].formants[0].q=64;
        filterpars->Pvowels[1].formants[1].freq=71;
        filterpars->Pvowels[1].formants[1].amp=121;
        filterpars->Pvowels[1].formants[1].q=64;
        filterpars->Pvowels[1].formants[2].freq=99;
        filterpars->Pvowels[1].formants[2].amp=117;
        filterpars->Pvowels[1].formants[2].q=64;
        break;
    case 4:
        filterpars->Pcategory=1;
        filterpars->Ptype=0;
        filterpars->Pfreq=64;
        filterpars->Pq=70;
        filterpars->Pstages=1;
        filterpars->Pgain=64;

        filterpars->Psequencesize=2;
        filterpars->Pnumformants=2;
        filterpars->Pvowelclearness=0;

        filterpars->Pvowels[0].formants[0].freq=70;
        filterpars->Pvowels[0].formants[0].amp=127;
        filterpars->Pvowels[0].formants[0].q=64;
        filterpars->Pvowels[0].formants[1].freq=80;
        filterpars->Pvowels[0].formants[1].amp=122;
        filterpars->Pvowels[0].formants[1].q=64;

        filterpars->Pvowels[1].formants[0].freq=20;
        filterpars->Pvowels[1].formants[0].amp=127;
        filterpars->Pvowels[1].formants[0].q=64;
        filterpars->Pvowels[1].formants[1].freq=100;
        filterpars->Pvowels[1].formants[1].amp=121;
        filterpars->Pvowels[1].formants[1].q=64;
        break;
    }

    if (insertion == 0) setParameter (0, presets[npreset][0] / 2); //lower the volume if this is system effect
    Ppreset=npreset;

    reinitfilter();
}

