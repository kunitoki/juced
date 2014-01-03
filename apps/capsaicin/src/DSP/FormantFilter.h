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

#ifndef __JUCETICE_XSYNTHFORMANTFILTER_HEADER__
#define __JUCETICE_XSYNTHFORMANTFILTER_HEADER__

#include "../globals.h"
#include "BaseFilter.h"
#include "AnalogFilter.h"
#include "../Params/FilterParams.h"


class FormantFilter : public BaseFilter
{
public:

    FormantFilter (FilterParams *pars);
    ~FormantFilter();

    void filterout (REALTYPE *smp, int numSamples);
    void setfreq (REALTYPE frequency);
    void setfreq_and_q (REALTYPE frequency, REALTYPE q_);
    void setq (REALTYPE q_);

    void cleanup();

private:
    AnalogFilter *formant[FF_MAX_FORMANTS];
    REALTYPE *inbuffer,*tmpbuf;

    struct {
        REALTYPE freq, amp, q; // frequency, amplitude, Q
    } formantpar[FF_MAX_VOWELS][FF_MAX_FORMANTS],
      currentformants[FF_MAX_FORMANTS];

    struct {
        uint8 nvowel;
    } sequence [FF_MAX_SEQUENCE];

    REALTYPE oldformantamp[FF_MAX_FORMANTS];

    int sequencesize,numformants,firsttime;
    REALTYPE oldinput,slowinput;
    REALTYPE Qfactor,formantslowness,oldQfactor;
    REALTYPE vowelclearness,sequencestretch;

    void setpos(REALTYPE input);
};


#endif

