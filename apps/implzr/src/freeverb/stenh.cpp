/*  Stereo Enhancer
 *
 *  Copyright (C) 2007 Teru KAMOGASHIRA
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

#include "freeverb/stenh.hpp"
#include "freeverb/fv3_type_float.h"
#include "freeverb/fv3_ns_start.h"

FV3_(stenh)::FV3_(stenh)()
{
  compS.setRMS(0);
  compS.setAttack(0);
  compS.setRelease(0);
  compS.setRatio(3);
  compS.setSoftKnee(10);
  compD.setRMS(0);
  compD.setAttack(0);
  compD.setRelease(0);
  compD.setRatio(3);
  compD.setSoftKnee(10);
  mute();
}

FV3_(stenh)::FV3_(~stenh)()
{
  ;
}

long FV3_(stenh)::getCurrentFs()
{
  return currentfs;
}

void FV3_(stenh)::setCurrentFs(long fs)
{
  currentfs = fs;
  updateNRT();
  mute();
}

void FV3_(stenh)::mute()
{
  delayV.mute();
  delayU.mute();
  delayF.mute();
  compS.mute();
  compD.mute();
}

void FV3_(stenh)::processreplace(fv3_float_t *inputL, fv3_float_t *inputR,
				 fv3_float_t *outputL, fv3_float_t *outputR,
				 long numsamples)
{
  long count = numsamples;
  while(count --)
    {
      fv3_float_t diff = chvL*(*inputL) - chvR*(*inputR);
      fv3_float_t directS = delayU.process(bpf.processL(diff));
      fv3_float_t delayS = diffusion *
	delayV.process(lpf.processL(diff) + hpf.processL(diff));

      fv3_float_t sumS = directS + delayS;
      fv3_float_t gainS = compS.process(levelSum);
      fv3_float_t gainD = compD.process(levelDiff);
      fv3_float_t vcaFactor = gainS > gainD ? gainD : gainS;
      vcaFactor *= width;
      sumS = delayF.process(sumS);
      
      *outputL = dry*(*inputL) - vcaFactor*sumS;
      *outputR = dry*(*inputR) + vcaFactor*sumS;
      
      // Feedback Level Detector
      levelSum = *outputL + *outputR;
      levelDiff = *outputL - *outputR;
      inputL ++; inputR ++;
      outputL ++; outputR ++;
    }
}

void FV3_(stenh)::setChValL(fv3_float_t value)
{
  chvL = value;
}

void FV3_(stenh)::setChValR(fv3_float_t value)
{
  chvR = value;
}

void FV3_(stenh)::setBPF_LPF(fv3_float_t value)
{
  bpf.setLPF(value);
}

void FV3_(stenh)::setBPF_HPF(fv3_float_t value)
{
  bpf.setHPF(value);
}

void FV3_(stenh)::setBRF_LPF(fv3_float_t value)
{
  lpf.setLPF(value);
}

void FV3_(stenh)::setBRF_HPF(fv3_float_t value)
{
  hpf.setHPF(value);
}

void FV3_(stenh)::setBPFDepth(fv3_float_t msec)
{
  Depth1 = msec;
  updateNRT();
}

void FV3_(stenh)::setBRFDepth(fv3_float_t msec)
{
  Depth2 = msec;
  updateNRT();
}

void FV3_(stenh)::setOverallDepth(fv3_float_t msec)
{
  Depth3 = msec;
  updateNRT();
}

void FV3_(stenh)::setDiffusion(fv3_float_t value)
{
  diffusion = value;
}

void FV3_(stenh)::setWidth(fv3_float_t value)
{
  width = value;
}

void FV3_(stenh)::setDry(fv3_float_t value)
{
  dry = value;
}

void FV3_(stenh)::setThreshold(fv3_float_t dB)
{
  compS.setThreshold(FV3_(utils)::dB2R(dB));
  compD.setThreshold(FV3_(utils)::dB2R(dB));
}

void FV3_(stenh)::updateNRT()
{
  delayU.setsize(FV3_(utils)::ms2sample(Depth1,currentfs));
  delayV.setsize(FV3_(utils)::ms2sample(Depth2,currentfs));
  delayF.setsize(FV3_(utils)::ms2sample(Depth3,currentfs));
}

#include "freeverb/fv3_ns_end.h"
