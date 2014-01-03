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

#include "Filter.h"


Filter::Filter (FilterParams *pars)
{
    uint8 Ftype = pars->Ptype;
    uint8 Fstages = pars->Pstages;

    category=pars->Pcategory;

    switch (category)
    {
    case 1:
            filter = new FormantFilter (pars);
            break;
    case 2:
            filter = new SVFilter (Ftype, 1000.0, pars->getq(), Fstages);
            filter->outgain = dB2rap (pars->getgain());
            if (filter->outgain > 1.0) filter->outgain = sqrt (filter->outgain);
            break;
    default:
            filter = new AnalogFilter (Ftype, 1000.0, pars->getq(), Fstages);
            if ((Ftype >= 6) && (Ftype <= 8)) filter->setgain (pars->getgain());
            else                              filter->outgain = dB2rap (pars->getgain());
            break;
    }
}

Filter::~Filter()
{
    delete (filter);
}

void Filter::filterout (REALTYPE *smp, int numSamples)
{
    filter->filterout (smp, numSamples);
}

void Filter::setfreq (REALTYPE frequency){
    filter->setfreq (frequency);
}

void Filter::setfreq_and_q (REALTYPE frequency, REALTYPE q_)
{
    filter->setfreq_and_q (frequency,q_);
}

void Filter::setq (REALTYPE q_)
{
    filter->setq (q_);
}

REALTYPE Filter::getrealfreq (REALTYPE freqpitch)
{
    if ((category==0)||(category==2)) return pow (2.0, freqpitch + 9.96578428); // log2(1000)=9.95748
    else                              return freqpitch;
}

