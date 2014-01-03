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

#ifndef __JUCETICE_XSYNTHSVFILTER_HEADER__
#define __JUCETICE_XSYNTHSVFILTER_HEADER__

#include "../globals.h"
#include "BaseFilter.h"


class SVFilter : public BaseFilter
{
public:

    SVFilter (unsigned char Ftype, REALTYPE Ffreq, REALTYPE Fq, unsigned char Fstages);
    ~SVFilter();

    void filterout (REALTYPE *smp, int numSamples);
    void setfreq (REALTYPE frequency);
    void setfreq_and_q (REALTYPE frequency,REALTYPE q_);
    void setq (REALTYPE q_);

    void settype (int type_);
    void setgain (REALTYPE dBgain);
    void setstages (int stages_);
    void cleanup ();

 private:
    struct fstage{
      REALTYPE low,high,band,notch;
    } st[MAX_FILTER_STAGES+1];

    struct parameters{
        REALTYPE f,q,q_sqrt;
    }par,ipar;

    void singlefilterout (REALTYPE *smp, fstage &x, parameters &par, int numSamples);
    void computefiltercoefs ();

    int type;//The type of the filter (LPF1,HPF1,LPF2,HPF2...)
    int stages;//how many times the filter is applied (0->1,1->2,etc.)
    REALTYPE freq;//Frequency given in Hz
    REALTYPE q; //Q factor (resonance or Q factor)
    REALTYPE gain;//the gain of the filter (if are shelf/peak) filters

    int abovenq;//this is 1 if the frequency is above the nyquist
    int oldabovenq;
    int needsinterpolation,firsttime;
};


#endif

