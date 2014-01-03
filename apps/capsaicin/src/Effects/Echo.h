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

#ifndef __JUCETICE_XSYNTHECHO_HEADER__
#define __JUCETICE_XSYNTHECHO_HEADER__

#include "Effect.h"


class Echo : public Effect
{
public:

    Echo (int insertion, REALTYPE *efxoutl_, REALTYPE *efxoutr_);
    ~Echo();

    void setPreset (uint8 presetNumber);
    void setParameter (int parameterNumber, uint8 parameterValue);
    uint8 getParameter (int parameterNumber);
    void out (REALTYPE *smpsl, REALTYPE *smpr, const int numSamples);
    void clean();

    void setdryonly();

private:

    uint8 Pvolume;//Volumul or E/R
    uint8 Ppanning;//Panning
    uint8 Pdelay;
    uint8 Plrdelay;// L/R delay difference
    uint8 Plrcross;// L/R Mixing
    uint8 Pfb;//Feed-back-ul
    uint8 Phidamp;

    void setvolume (uint8 Pvolume);
    void setpanning (uint8 Ppanning);
    void setdelay (uint8 Pdelay);
    void setlrdelay (uint8 Plrdelay);
    void setlrcross (uint8 Plrcross);
    void setfb (uint8 Pfb);
    void sethidamp (uint8 Phidamp);

    //Parametrii reali
    REALTYPE panning,lrcross,fb,hidamp;
    int dl,dr,delay,lrdelay;

    void initdelays();
    REALTYPE *ldelay,*rdelay;
    REALTYPE oldl,oldr;//pt. lpf
    int kl,kr;
};


#endif


