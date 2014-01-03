/*  Compressor model implementation
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

#include "freeverb/compmodel.hpp"
#include "freeverb/fv3_type_float.h"
#include "freeverb/fv3_ns_start.h"

FV3_(compmodel)::FV3_(compmodel)()
{
  currentfs = 48000;
  mute();
  currentGain = 1;
}

FV3_(compmodel)::FV3_(~compmodel)()
{
  ;
}

long FV3_(compmodel)::getCurrentFs()
{
  return currentfs;
}

void FV3_(compmodel)::setCurrentFs(long fs)
{
  currentfs = fs;
  update();
  updateNRT();
  mute();
}

fv3_float_t FV3_(compmodel)::getRMS()
{
  return RMS;
}

void FV3_(compmodel)::setRMS(fv3_float_t msec)
{
  RMS = msec;
  updateNRT();
}

fv3_float_t FV3_(compmodel)::getLookahead()
{
  return Lookahead;
}

void FV3_(compmodel)::setLookahead(fv3_float_t msec)
{
  Lookahead = msec;
  updateNRT();
}

fv3_float_t FV3_(compmodel)::getAttack()
{
  return Attack;
}

void FV3_(compmodel)::setAttack(fv3_float_t msec)
{
  Attack = msec;
  update();
}

fv3_float_t FV3_(compmodel)::getRelease()
{
  return Release;
}

void FV3_(compmodel)::setRelease(fv3_float_t msec)
{
  Release = msec;
  update();
}

fv3_float_t FV3_(compmodel)::getThreshold()
{
  return Threshold;
}

void FV3_(compmodel)::setThreshold(fv3_float_t dB)
{
  Threshold = dB;
  update();
}

fv3_float_t FV3_(compmodel)::getSoftKnee()
{
  return SoftKnee;
}

void FV3_(compmodel)::setSoftKnee(fv3_float_t dB)
{
  SoftKnee = dB;
  update();
}

fv3_float_t FV3_(compmodel)::getRatio()
{
  return Ratio;
}

void FV3_(compmodel)::setRatio(fv3_float_t value)
{
  Ratio = value;
  update();
}

long FV3_(compmodel)::getLatency()
{
  return 0;
}

void FV3_(compmodel)::updateNRT()
{
  compL.setRMS(FV3_(utils)::ms2sample(RMS,currentfs));
  compR.setRMS(FV3_(utils)::ms2sample(RMS,currentfs));
  lookaL.setsize(FV3_(utils)::ms2sample(Lookahead,currentfs));
  lookaR.setsize(FV3_(utils)::ms2sample(Lookahead,currentfs));
}

void FV3_(compmodel)::update()
{
  compL.setThreshold(FV3_(utils)::dB2R(Threshold));
  compR.setThreshold(FV3_(utils)::dB2R(Threshold));
  compL.setSoftKnee(SoftKnee);
  compR.setSoftKnee(SoftKnee);
  compL.setRatio(Ratio);
  compR.setRatio(Ratio);
  compL.setAttack(FV3_(utils)::ms2sample(Attack,currentfs));
  compR.setAttack(FV3_(utils)::ms2sample(Attack,currentfs));
  compL.setRelease(FV3_(utils)::ms2sample(Release,currentfs));
  compR.setRelease(FV3_(utils)::ms2sample(Release,currentfs));
}

void FV3_(compmodel)::mute()
{
  compL.mute();
  compR.mute();
  lookaL.mute();
  lookaR.mute();
}

fv3_float_t FV3_(compmodel)::getCGain()
{
  return currentGain;
}

void FV3_(compmodel)::processreplace(fv3_float_t *inputL,
				     fv3_float_t *inputR,
				     fv3_float_t *outputL,
				     fv3_float_t *outputR,
				     long numsamples)
{
  float gainL, gainR;
  for(long i = 0;i < numsamples;i ++)
    {
      gainL = compL.process(inputL[i]);
      gainR = compR.process(inputR[i]);
      if(gainL > gainR) currentGain = gainR;
      else currentGain = gainL;
      outputL[i] = lookaL.process(inputL[i])*currentGain;
      outputR[i] = lookaR.process(inputR[i])*currentGain;
    }
}

fv3_float_t FV3_(compmodel)::getEnv()
{
  return compL.getEnv();
}

void FV3_(compmodel)::printconfig()
{
  fprintf(stderr, "*** compmodel config ***\n");
  fprintf(stderr, "Fs=%ld[Hz]\n",currentfs);
  fprintf(stderr,
	  "Attack %1.2fms Release %1.2fms Threshold %1.2fdB Ratio %1.2f:1 ",
	  Attack, Release, Threshold, Ratio);
  fprintf(stderr, "SoftKnee %1.2f\n", SoftKnee);
  fprintf(stderr,
	  "Attack %ld Release %ld Threshold %1.2f Ratio %1.2f:1 ",
	  compL.getAttack(), compL.getRelease(),
	  compL.getThreshold(), compL.getRatio());
  fprintf(stderr, "SoftKnee %1.2f\n", compL.getSoftKnee());
}

#include "freeverb/fv3_ns_end.h"
