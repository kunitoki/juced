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

#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "Echo.h"

//==============================================================================
Echo::Echo (int insertion_, REALTYPE *efxoutl_, REALTYPE *efxoutr_)
{
    efxoutl = efxoutl_;
    efxoutr = efxoutr_;
    filterpars = NULL;

    insertion = insertion_;

    //default values
    Ppreset = 0;
    Pvolume = 90;
    Ppanning = 64;
    Pdelay = 30;
    Plrdelay = 64;
    Plrcross = 64;
    Pfb = 60;
    Phidamp = 20;

    //what if the sample_rate changes ?
    int maxDelaySize = (int) (SAMPLE_RATE * 5.0);
    ldelay = new REALTYPE [maxDelaySize];
    rdelay = new REALTYPE [maxDelaySize];
    lrdelay = 0;

    setPreset (Ppreset);
    clean ();
}

Echo::~Echo()
{
    delete[] ldelay;
    delete[] rdelay;
}

//==============================================================================
void Echo::clean()
{
    int i;
    for (i = 0; i < dl; i++) ldelay[i] = 0.0;
    for (i = 0; i < dr; i++) rdelay[i] = 0.0;
    oldl = 0.0;
    oldr = 0.0;
}

//==============================================================================
void Echo::initdelays()
{
    kl = 0;
    kr = 0;
    dl = delay - lrdelay; if (dl < 1) dl = 1;
    dr = delay + lrdelay; if (dr < 1) dr = 1;

    clean();
}

//==============================================================================
void Echo::out (REALTYPE *smpsl, REALTYPE *smpsr, const int numSamples)
{
    int i;
    REALTYPE l,r,ldl,rdl /*,hdl,hdr */;

    for (i = 0; i < numSamples; i++)
    {
        ldl = ldelay[kl];
        rdl = rdelay[kr];
        l = ldl * (1.0 - lrcross) + rdl * lrcross;
        r = rdl * (1.0 - lrcross) + ldl * lrcross;
        ldl = l;
        rdl = r;

        efxoutl[i] = ldl * 2.0;
        efxoutr[i] = rdl * 2.0;
        ldl = smpsl[i] * panning - ldl * fb;
        rdl = smpsr[i] * (1.0 - panning) - rdl * fb;

        //LowPass Filter
        ldelay[kl] = ldl = ldl * hidamp + oldl * (1.0 - hidamp);
        rdelay[kr] = rdl = rdl * hidamp + oldr * (1.0 - hidamp);

        oldl = ldl;
        oldr = rdl;

        if (++kl >= dl) kl = 0;
        if (++kr >= dr) kr = 0;
    }
}

//==============================================================================
void Echo::setParameter (int npar, uint8 value)
{
    switch (npar) {
    case 0: setvolume (value);   break;
    case 1: setpanning (value);  break;
    case 2: setdelay (value);    break;
    case 3: setlrdelay (value);  break;
    case 4: setlrcross (value);  break;
    case 5: setfb (value);       break;
    case 6: sethidamp (value);   break;
    }
}

uint8 Echo::getParameter (int npar)
{
    switch (npar) {
    case 0: return (Pvolume);
    case 1: return (Ppanning);
    case 2: return (Pdelay);
    case 3: return (Plrdelay);
    case 4: return (Plrcross);
    case 5: return (Pfb);
    case 6: return (Phidamp);
    }
    return 0; //in case of bogus parameter number
}

//==============================================================================
void Echo::setvolume (uint8 Pvolume)
{
    this->Pvolume = Pvolume;

    if (insertion == 0)
    {
        outvolume = pow (0.01, (1.0 - Pvolume / 127.0)) * 4.0;
        volume = 1.0;
    }
    else
    {
        volume = outvolume = Pvolume / 127.0;
    }
    if (Pvolume == 0) clean();
}

void Echo::setpanning (uint8 Ppanning)
{
    this->Ppanning = Ppanning;
    panning = (Ppanning + 0.5) / 127.0;
}

void Echo::setdelay (uint8 Pdelay)
{
    this->Pdelay = Pdelay;
    delay = 1 + (int) (Pdelay / 127.0 * SAMPLE_RATE * 2.5); //0 .. 2.5 sec
    initdelays();
}

void Echo::setlrdelay (uint8 Plrdelay)
{
    REALTYPE tmp;
    this->Plrdelay = Plrdelay;
    tmp = (pow (2, fabs (Plrdelay - 64.0) / 64.0 * 9) - 1.0) / 1000.0 * SAMPLE_RATE;
    if (Plrdelay < 64.0) tmp = -tmp;
    lrdelay =(int) tmp;
    initdelays();
}

void Echo::setlrcross (uint8 Plrcross)
{
    this->Plrcross = Plrcross;
    lrcross = Plrcross / 127.0 * 1.0;
}

void Echo::setfb (uint8 Pfb)
{
    this->Pfb = Pfb;
    fb = Pfb / 128.0;
}

void Echo::sethidamp (uint8 Phidamp)
{
    this->Phidamp = Phidamp;
    hidamp = 1.0 - Phidamp / 127.0;
}

//==============================================================================
void Echo::setPreset (uint8 npreset)
{
    const int PRESET_SIZE = 7;
    const int NUM_PRESETS = 9;

    uint8 presets[NUM_PRESETS][PRESET_SIZE] =
    {
        //Echo 1
        {81,64,22,64,30,59,0},
        //Echo 2
        {67,64,21,64,30,59,0},
        //Echo 3
        {67,75,60,64,30,59,10},
        //Simple Echo
        {67,60,44,64,30,0,0},
        //Canyon
        {67,60,102,50,30,82,48},
        //Panning Echo 1
        {67,64,44,17,0,82,24},
        //Panning Echo 2
        {81,60,46,118,100,68,18},
        //Panning Echo 3
        {81,60,26,100,127,67,36},
        //Feedback Echo
        {62,64,28,64,100,90,55}
    };

    if (npreset >= NUM_PRESETS) npreset = NUM_PRESETS - 1;
    for (int n = 0; n < PRESET_SIZE; n++) setParameter (n, presets[npreset][n]);
//    if (insertion!=0) changepar(0,presets[npreset][0]/2);//lower the volume if this is insertion effect
    Ppreset = npreset;
}

