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

#ifndef __JUCETICE_XSYNTHALIENWAH_HEADER__
#define __JUCETICE_XSYNTHALIENWAH_HEADER__

#include "Effect.h"
#include "EffectLFO.h"

#define MAX_ALIENWAH_DELAY 100

struct COMPLEXTYPE {
    REALTYPE a,b;
};


class Alienwah : public Effect
{
public:

    Alienwah (int insertion_, REALTYPE *efxoutl_, REALTYPE *efxoutr_);
    ~Alienwah();

    void setPreset (uint8 npreset);
    void setParameter (int npar, uint8 value);
    uint8 getParameter (int npar);
    void out (REALTYPE *smpsl, REALTYPE *smpsr, const int numSamples);
    void clean();

private:

    EffectLFO lfo;
    uint8 Pvolume;
    uint8 Ppanning;
    uint8 Pdepth;      //the depth of the Alienwah
    uint8 Pfb;         //feedback
    uint8 Plrcross;    //feedback
    uint8 Pdelay;
    uint8 Pphase;

    void setvolume (uint8 Pvolume);
    void setpanning (uint8 Ppanning);
    void setdepth (uint8 Pdepth);
    void setfb (uint8 Pfb);
    void setlrcross (uint8 Plrcross);
    void setdelay (uint8 Pdelay);
    void setphase (uint8 Pphase);

    int insertion;
    REALTYPE panning,fb,depth,lrcross,phase;
    COMPLEXTYPE *oldl,*oldr;
    COMPLEXTYPE oldclfol,oldclfor;
    int oldk;
};


#endif
