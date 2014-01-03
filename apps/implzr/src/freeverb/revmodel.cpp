/*  Reverb model implementation
 *
 *  Copyright (C) 2000-2006 Jezar at Dreampoint, Teru KAMOGASHIRA
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

#include "freeverb/revmodel.hpp"
#include "freeverb/fv3_type_float.h"
#include "freeverb/fv3_ns_start.h"

FV3_(revmodel)::FV3_(revmodel)()
{
  defaultfs = 44100;
  numcombs = 0;
  numallpasses = 0;
  currentfs = defaultfs;
  setFilter(1);
  mute();
  initialDelay = 0;
  delayL.setsize(initialDelay);
  delayR.setsize(initialDelay);
  delayWL.setsize(initialDelay);
  delayWR.setsize(initialDelay);
  delayL.mute();
  delayR.mute();
  delayWL.mute();
  delayWR.mute();
}

FV3_(revmodel)::FV3_(~revmodel)()
{
  freeFilter();
}

void FV3_(revmodel)::setInitialDelay(long numsamples)
{
  initialDelay = numsamples;
  if(initialDelay >= 0)
    {
#ifdef DEBUG
      fprintf(stderr, "nrev::setInitialDelay(%ld) delayW(%ld))\n", numsamples, initialDelay);
#endif
      delayL.setsize(0);
      delayR.setsize(0);
      delayWL.setsize(initialDelay);
      delayWR.setsize(initialDelay);
    }
  else
    {
      long dryD = - initialDelay;
#ifdef DEBUG
      fprintf(stderr, "nrev::setInitialDelay(%ld) delayD(%ld))\n", numsamples, dryD);
#endif
      delayL.setsize(dryD);
      delayR.setsize(dryD);
      delayWL.setsize(0);
      delayWR.setsize(0);
    }
  delayL.mute();
  delayR.mute();
  delayWL.mute();
  delayWR.mute();
}

long FV3_(revmodel)::getInitialDelay()
{
  return initialDelay;
}

void FV3_(revmodel)::setOverSamplingFactor(long factor, long converter_type)
{
  SRC.setSRCFactor(factor, converter_type);
  resetfs(currentfs);
}

void FV3_(revmodel)::setOverSamplingFactor(long factor)
{
  SRC.setSRCFactor(factor);
}

long FV3_(revmodel)::getOverSamplingFactor()
{
  return SRC.getSRCFactor();
}

long FV3_(revmodel)::getCurrentFs()
{
  return currentfs;
}

void FV3_(revmodel)::resetfs(long fs)
{
  currentfs = fs;
  fv3_float_t tf = (fv3_float_t)currentfs*(fv3_float_t)SRC.getSRCFactor()/(fv3_float_t)defaultfs;
#ifdef DEBUG
  fprintf(stderr, "freeverb: Fs=%ld[Hz] Factor=%f SRC=%ld\n", fs, tf, SRC.getSRCFactor());
#endif
  setFilter(tf);
  setdamp(getdamp());
  setroomsize(getroomsize());
  mute();
}

long FV3_(revmodel)::getLatency()
{
  return SRC.getLatency();
}

long FV3_(revmodel)::f_(long def, fv3_float_t factor)
{
  return (long)((fv3_float_t)(def)*factor);
}

void FV3_(revmodel)::printconfig()
{
  fprintf(stderr, "*** Freeverb config ***\n");
  fprintf(stderr, "Fs=%ld[Hz] x %ld\n",currentfs,SRC.getSRCFactor());
  fprintf(stderr, "roomsize %f damp %f wet %f wet1 %f wet2 %f\n",
	  roomsize,damp,wet,wet1,wet2);
  fprintf(stderr, "dry %f width %f\n", dry,width);
}

void FV3_(revmodel)::mute()
{
  for (long i = 0;i < numcombs;i ++)
    {
      combL[i].mute();
      combR[i].mute();
    }
  for (long i = 0;i < numallpasses;i ++)
    {
      allpassL[i].mute();
      allpassR[i].mute();
    }
}

void FV3_(revmodel)::processreplace(fv3_float_t *inputL, fv3_float_t *inputR,
			      fv3_float_t *outputL, fv3_float_t *outputR,
			      long numsamples)
{
  long count = numsamples*SRC.getSRCFactor();
  fv3_float_t outL,outR,input;
  fv3_float_t *origOutL = outputL;
  fv3_float_t *origOutR = outputR;
  fv3_float_t overL[numsamples*SRC.getSRCFactor()], overR[numsamples*SRC.getSRCFactor()];
  fv3_float_t overOL[numsamples*SRC.getSRCFactor()], overOR[numsamples*SRC.getSRCFactor()];
  
  SRC.usrc(inputL, inputR, overL, overR, numsamples);
  inputL = overL;
  inputR = overR;
  outputL = overOL;
  outputR = overOR;

  while(count-- > 0)
    {
      outL = outR = 0.0;
      input = (*inputL + *inputR) * fixedgain;
      
      // Accumulate comb filters in parallel
      for(long i=0; i<numcombs; i++)
	{
	  outL += combL[i].process(input);
	  outR += combR[i].process(input);
	}
      
      // Feed through allpasses in series
      for(long i=0; i<numallpasses; i++)
	{
	  outL = allpassL[i].process(outL);
	  outR = allpassR[i].process(outR);
	}

      fv3_float_t fpL = delayWL.process(outL);
      fv3_float_t fpR = delayWR.process(outR);
      *outputL = fpL*wet1 + fpR*wet2 + delayL.process(*inputL)*dry;
      *outputR = fpR*wet1 + fpL*wet2 + delayR.process(*inputR)*dry;
      
      inputL ++;
      inputR ++;
      outputL ++;
      outputR ++;
    }
  SRC.dsrc(overOL, overOR, origOutL, origOutR, numsamples);
}

void FV3_(revmodel)::setroomsize(fv3_float_t value)
{
  roomsize = (value*scaleroom) + offsetroom;
  for(long i = 0;i < numcombs;i ++)
    {
      combL[i].setfeedback(roomsize);
      combR[i].setfeedback(roomsize);
    }
}

fv3_float_t FV3_(revmodel)::getroomsize()
{
  return (roomsize-offsetroom)/scaleroom;
}

void FV3_(revmodel)::setdamp(fv3_float_t value)
{
  damp = value;
  for(long i = 0;i < numcombs;i ++)
    {
      combL[i].setdamp(damp);
      combR[i].setdamp(damp);
    }
}

fv3_float_t FV3_(revmodel)::getdamp()
{
  return damp;
}

void FV3_(revmodel)::setwet(fv3_float_t value)
{
  wet = value*scalewet;
  wet1 = wet*(width/2 + 0.5f);
  wet2 = wet*((1-width)/2);
}

fv3_float_t FV3_(revmodel)::getwet()
{
  return wet/scalewet;
}

void FV3_(revmodel)::setdry(fv3_float_t value)
{
  dry = value*scaledry;
}

fv3_float_t FV3_(revmodel)::getdry()
{
  return dry/scaledry;
}

void FV3_(revmodel)::setwidth(fv3_float_t value)
{
  width = value;
  wet1 = wet*(width/2 + 0.5f);
  wet2 = wet*((1-width)/2);
}

fv3_float_t FV3_(revmodel)::getwidth()
{
  return width;
}

void FV3_(revmodel)::allocFilter(long ncomb, long nallpass)
{
  if(numcombs != 0||numallpasses != 0)
    freeFilter();
  try
    {
      combL = new FV3_(comb)[ncomb];
      combR = new FV3_(comb)[ncomb];
      allpassL = new FV3_(allpass)[nallpass];
      allpassR = new FV3_(allpass)[nallpass];
    }
  catch(std::bad_alloc)
    {
      fprintf(stderr, "FV3_(revmodel)::allocFilter() bad_alloc\n");
      delete[] combL;
      delete[] combR;
      delete[] allpassL;
      delete[] allpassR;
      throw std::bad_alloc();
    }
  numcombs = ncomb;
  numallpasses = nallpass;
}

void FV3_(revmodel)::freeFilter()
{
  if(numcombs != 0&&numallpasses != 0)
    {
#ifdef DEBUG
  fprintf(stderr, "FV3_(revmodel)::freeFilter()+\n");
#endif
      delete[] combL;
      delete[] combR;
      delete[] allpassL;
      delete[] allpassR;
      numcombs = 0;
      numallpasses = 0;
    }
}

void FV3_(revmodel)::setFilter(fv3_float_t factor)
{
#ifdef DEBUG
  fprintf(stderr, "FV3_(revmodel)::setBuffer(%f)\n", factor);
#endif
  const long combT[] = {1116, 1188, 1277, 1356, 1422, 1491, 1557, 1617};
  const long allpT[] = {556, 441, 341, 225};
  allocFilter(sizeof(combT)/sizeof(long), sizeof(allpT)/sizeof(long));
  for(long i = 0;i < numcombs;i ++)
    {
      combL[i].setsize(f_(combT[i],factor));
      combR[i].setsize(f_(combT[i]+stereospread441,factor));
    }
  for(long i = 0;i < numallpasses;i ++)
    {
      allpassL[i].setsize(f_(allpT[i],factor));
      allpassR[i].setsize(f_(allpT[i]+stereospread441,factor));
    }
  setAllpass();
}

void FV3_(revmodel)::setAllpass()
{
  for(long i = 0;i < numallpasses;i ++)
    {
      allpassL[i].setfeedback(0.5f);
      allpassR[i].setfeedback(0.5f);
    }
}

#include "freeverb/fv3_ns_end.h"
