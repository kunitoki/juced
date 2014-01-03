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

#ifndef __JUCETICE_XSYNTHREVERB_HEADER__
#define __JUCETICE_XSYNTHREVERB_HEADER__

#include "Effect.h"
#include "../DSP/AnalogFilter.h"

#define REV_COMBS 8
#define REV_APS 4


class Reverb : public Effect
{
public:

    Reverb (int insertion, REALTYPE *efxoutl_, REALTYPE *efxoutr_);
    ~Reverb();

    void setPreset (uint8 npreset);
    void setParameter (int npar, uint8 value);
    uint8 getParameter (int npar);
    void out (REALTYPE *smps_l, REALTYPE *smps_r, const int numSamples);
    void clean();

private:

    uint8 Pvolume;      // Amount of the reverb,
    uint8 Ppan;         // LefT/Right Panning
    uint8 Ptime;        // duration of reverb
    uint8 Pidelay;      // Initial delay
    uint8 Pidelayfb;    // Initial delay feedback
    uint8 Prdelay;      // delay between ER/Reverbs
    uint8 Perbalance;   // EarlyReflections/Reverb Balance
    uint8 Plpf;         // HighPassFilter
    uint8 Phpf;         // LowPassFilter
    uint8 Plohidamp;    // Low/HighFrequency Damping  0..63 lpf,64=off,65..127=hpf(TODO)
    uint8 Ptype;        // Reverb type
    uint8 Proomsize;    // Room Size

    // Parameter control
    void setvolume (uint8 Pvolume);
    void setpan (uint8 Ppan);
    void settime (uint8 Ptime);
    void setlohidamp (uint8 Plohidamp);
    void setidelay (uint8 Pidelay);
    void setidelayfb (uint8 Pidelayfb);
    void sethpf (uint8 Phpf);
    void setlpf (uint8 Plpf);
    void settype (uint8 Ptype);
    void setroomsize (uint8 Proomsize);

    REALTYPE pan, erbalance;

    // Parameters
    int lohidamptype;//0=disable,1=highdamp(lowpass),2=lowdamp(highpass)
    int idelaylen, rdelaylen;
    int idelayk;
    REALTYPE lohifb, idelayfb, roomsize, rs; // rs is used to "normalise" the volume according to the roomsize
    int comblen[REV_COMBS*2];
    int aplen[REV_APS*2];

    // Internal values
    REALTYPE *comb[REV_COMBS*2];
    int combk[REV_COMBS*2];
    REALTYPE combfb[REV_COMBS*2]; // Feedback "comb"
    REALTYPE lpcomb[REV_COMBS*2]; // LowPass
    REALTYPE *ap[REV_APS*2];
    int apk[REV_APS*2];
    REALTYPE *idelay;
    AnalogFilter *lpf,*hpf; //filters
    REALTYPE *inputbuf;

    void processMono (int ch, REALTYPE *output, const int numSamples);
};


#endif
