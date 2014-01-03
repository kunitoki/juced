/*  Limiter model implementation
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

#include "freeverb/limitmodel.hpp"
#include "freeverb/fv3_type_float.h"
#include "freeverb/fv3_ns_start.h"

FV3_(limitmodel)::FV3_(limitmodel)()
{
  currentfs = 48000;
  mute();
  currentGain = 1;
}

FV3_(limitmodel)::FV3_(~limitmodel)()
{
  ;
}

long FV3_(limitmodel)::getCurrentFs()
{
  return currentfs;
}

void FV3_(limitmodel)::setCurrentFs(long fs)
{
  currentfs = fs;
  update();
  updateNRT();
  mute();
}

fv3_float_t FV3_(limitmodel)::getRMS()
{
  return RMS;
}

void FV3_(limitmodel)::setRMS(fv3_float_t msec)
{
  RMS = msec;
  updateNRT();
}

fv3_float_t FV3_(limitmodel)::getLookahead()
{
  return Lookahead;
}

void FV3_(limitmodel)::setLookahead(fv3_float_t msec)
{
  Lookahead = msec;
  updateNRT();
}

fv3_float_t FV3_(limitmodel)::getAttack()
{
  return Attack;
}

void FV3_(limitmodel)::setAttack(fv3_float_t msec)
{
  Attack = msec;
  update();
}

fv3_float_t FV3_(limitmodel)::getRelease()
{
  return Release;
}

void FV3_(limitmodel)::setRelease(fv3_float_t msec)
{
  Release = msec;
  update();
}

fv3_float_t FV3_(limitmodel)::getThreshold()
{
  return Threshold;
}

void FV3_(limitmodel)::setThreshold(fv3_float_t dB)
{
  Threshold = dB;
  update();
  mute();
}

fv3_float_t FV3_(limitmodel)::getCeiling()
{
  return Ceiling;
}

void FV3_(limitmodel)::setCeiling(fv3_float_t dB)
{
  Ceiling = dB;
  update();
}

long FV3_(limitmodel)::getLatency()
{
  return 0;
}

void FV3_(limitmodel)::updateNRT()
{
  limitL.setRMS(FV3_(utils)::ms2sample(RMS,currentfs));
  limitR.setRMS(FV3_(utils)::ms2sample(RMS,currentfs));
  limitL.setLookahead(FV3_(utils)::ms2sample(Lookahead,currentfs));
  limitR.setLookahead(FV3_(utils)::ms2sample(Lookahead,currentfs));
  lookaL.setsize(FV3_(utils)::ms2sample(Lookahead,currentfs));
  lookaR.setsize(FV3_(utils)::ms2sample(Lookahead,currentfs));
}

void FV3_(limitmodel)::update()
{
  limitL.setThreshold(FV3_(utils)::dB2R(Threshold));
  limitR.setThreshold(FV3_(utils)::dB2R(Threshold));
  limitL.setCeiling(FV3_(utils)::dB2R(Ceiling));
  limitR.setCeiling(FV3_(utils)::dB2R(Ceiling));
  limitL.setAttack(FV3_(utils)::ms2sample(Attack,currentfs));
  limitR.setAttack(FV3_(utils)::ms2sample(Attack,currentfs));
  limitL.setRelease(FV3_(utils)::ms2sample(Release,currentfs));
  limitR.setRelease(FV3_(utils)::ms2sample(Release,currentfs));
}

void FV3_(limitmodel)::mute()
{
  limitL.mute();
  limitR.mute();
  lookaL.mute();
  lookaR.mute();
}

fv3_float_t FV3_(limitmodel)::getCGain()
{
  return currentGain;
}

void FV3_(limitmodel)::processreplace(fv3_float_t *inputL,
				     fv3_float_t *inputR,
				     fv3_float_t *outputL,
				     fv3_float_t *outputR,
				     long numsamples)
{
  float gainL, gainR;
  for(long i = 0;i < numsamples;i ++)
    {
      gainL = limitL.process(inputL[i]);
      gainR = limitR.process(inputR[i]);
      if(gainL > gainR) currentGain = gainR;
      else currentGain = gainL;
      outputL[i] = lookaL.process(inputL[i])*currentGain;
      outputR[i] = lookaR.process(inputR[i])*currentGain;
    }
}

fv3_float_t FV3_(limitmodel)::getEnv()
{
  return limitL.getEnv();
}

void FV3_(limitmodel)::printconfig()
{
  fprintf(stderr, "*** limitmodel config ***\n");
  fprintf(stderr, "Fs=%ld[Hz]\n",currentfs);
  fprintf(stderr,
	  "Attack %1.2fms Release %1.2fms Threshold %1.2fdB Ceiling %1.2fdB",
	  Attack, Release, Threshold, Ceiling);
  fprintf(stderr,
	  "Attack %ld Release %ld Threshold %1.2f",
	  limitL.getAttack(), limitL.getRelease(),
	  limitL.getThreshold());
}

#include "freeverb/fv3_ns_end.h"
