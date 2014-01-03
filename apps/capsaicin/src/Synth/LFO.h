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

#ifndef __JUCETICE_XSYNTHLFO_HEADER__
#define __JUCETICE_XSYNTHLFO_HEADER__

#include "../globals.h"
#include "../Params/LFOParams.h"


//==============================================================================
/**
    Low Frequency Oscillator DSP class. This is instantiated in the voice/note
    section and is responsible to evaluate lfo output
*/
class LFO
{
public:

    LFO (LFOParams *lfopars, REALTYPE basefreq);
    ~LFO();

    REALTYPE lfoout();
    REALTYPE amplfoout();

private:

    REALTYPE x;
    REALTYPE incx, incrnd, nextincrnd;
    REALTYPE amp1, amp2;// used for randomness
    REALTYPE lfointensity;
    REALTYPE lfornd, lfofreqrnd;
    REALTYPE lfodelay;
    char lfotype;
    int freqrndenabled;

    void computenextincrnd();
};


#endif
