/*  one-pole/one-zero LPF/HPF filter
 *
 *  Copyright (C) 2006 Teru KAMOGASHIRA
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include "freeverb/efilter.hpp"
#include "freeverb/fv3_type_float.h"
#include "freeverb/fv3_ns_start.h"

FV3_(efilter)::FV3_(efilter)()
{
  lpfCof = 0.0f;
  hpfCof = 0.0f;
  updateP(&lpfL, lpfCof);
  updateP(&lpfR, lpfCof);
  updateZ(&hpfL, hpfCof);
  updateZ(&hpfR, hpfCof);
}

FV3_(efilter)::FV3_(~efilter)()
{
  ;
}

void FV3_(efilter)::setLPF(fv3_float_t val)
{
  lpfCof = val;
  updateP(&lpfL, lpfCof);
  updateP(&lpfR, lpfCof);
}

void FV3_(efilter)::setHPF(fv3_float_t val)
{
  hpfCof = val;
  updateZ(&hpfL, hpfCof);
  updateZ(&hpfR, hpfCof);
}

fv3_float_t FV3_(efilter)::getLPF()
{
  return lpfCof;
}

fv3_float_t FV3_(efilter)::getHPF()
{
  return hpfCof;
}

fv3_float_t FV3_(efilter)::processL(fv3_float_t input)
{
  return processP(&hpfL,processZ(&lpfL,input));
}

fv3_float_t FV3_(efilter)::processR(fv3_float_t input)
{
  return processP(&hpfR,processZ(&lpfR,input));
}

// one-pole

void FV3_(efilter)::updateP(IIR * iir, fv3_float_t pole)
{
  iir->a_[0] = iir->a_[1] = 1.0f;
  iir->b_[0] = 0.1f;

  iir->a_[1] = -pole;
  if (pole > 0.0)
    iir->b_[0] = 1.0f - pole;
  else
    iir->b_[0] = 1.0f + pole;
}

fv3_float_t FV3_(efilter)::processP(IIR * iir, fv3_float_t input)
{
  iir->inputs_[0] = input;
  iir->outputs_[0] = iir->b_[0] * iir->inputs_[0] - iir->a_[1] * iir->outputs_[1];
  iir->outputs_[1] = iir->outputs_[0];
  return iir->outputs_[0];
}

// one-zero

void FV3_(efilter)::updateZ(IIR * iir, fv3_float_t zero)
{
  iir->a_[0] = 1.0f;
  iir->b_[0] = iir->b_[1] = 0.5f;
  
  if (zero > 0.0)
    iir->b_[0] = 1.0f / (1.0f + zero);
  else
    iir->b_[0] = 1.0f / (1.0f - zero);

  iir->b_[1] = -zero * iir->b_[0];
}

fv3_float_t FV3_(efilter)::processZ(IIR * iir, fv3_float_t input)
{
  iir->inputs_[0] = input;
  iir->outputs_[0] =
    iir->b_[1] * iir->inputs_[1] + iir->b_[0] * iir->inputs_[0];
  iir->inputs_[1] = iir->inputs_[0];
  return iir->outputs_[0];
}

#include "freeverb/fv3_ns_end.h"
