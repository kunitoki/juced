/*  NReverb model
 *
 *  Copyright (C) 2006,2007 Teru KAMOGASHIRA
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

#include "freeverb/nrev.hpp"
#include "freeverb/fv3_type_float.h"
#include "freeverb/fv3_ns_start.h"

void FV3_(nrev)::setOverSamplingFactor(long factor, long converter_type)
{
  SRC.setSRCFactor(factor, converter_type);
  resetfs(currentfs);
}

void FV3_(nrev)::setOverSamplingFactor(long factor)
{
  SRC.setSRCFactor(factor);
}

long FV3_(nrev)::getOverSamplingFactor()
{
  return SRC.getSRCFactor();
}

long FV3_(nrev)::getLatency()
{
  return SRC.getLatency();
}

FV3_(nrev)::FV3_(nrev)()
{
  feedback = 0.7f;
  damp2 = FV3_(utils)::dB2R(0.0);
  damp3 = FV3_(utils)::dB2R(0.0);
  numcombs = 0;
  numallpasses = 0;
  currentfs = FV3_NREV_DEFAULT_FS;
  setFilter(1);
  setDefaultFeedback();
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

FV3_(nrev)::FV3_(~nrev)()
{
  freeFilter();
}

void FV3_(nrev)::setInitialDelay(long numsamples)
{
  initialDelay = numsamples;
  if(initialDelay >= 0)
    {
#ifdef DEBUG
      fprintf(stderr, "FV3_(nrev)::setInitialDelay(%ld) delayW(%ld))\n",
	      numsamples, initialDelay);
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
      fprintf(stderr, "FV3_(nrev)::setInitialDelay(%ld) delayD(%ld))\n",
	      numsamples, dryD);
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

long FV3_(nrev)::getInitialDelay()
{
  return initialDelay;
}

long FV3_(nrev)::getCurrentFs()
{
  return currentfs;
}

void FV3_(nrev)::resetfs(long fs)
{
  currentfs = fs;
  fv3_float_t tf =
    (fv3_float_t)SRC.getSRCFactor()*(fv3_float_t)fs/
    (fv3_float_t)FV3_NREV_DEFAULT_FS;
#ifdef DEBUG
  fprintf(stderr, "freeverb: Fs=%ld[Hz] Factor=%f\n", fs, tf);
#endif
  setFilter(tf);
  setDefaultFeedback();
  setroomsize(getroomsize());
  setfeedback(getfeedback());
  setdamp(getdamp());
  setdamp2(getdamp2());
  setdamp3(getdamp3());
  mute();
}

long FV3_(nrev)::f_(long def, fv3_float_t factor)
{
  return (long)((fv3_float_t)(def)*factor);
}

long FV3_(nrev)::p_(long def, fv3_float_t factor)
{
  long base = (long)((fv3_float_t)(def)*factor);
  while(!FV3_(utils)::isPrime(base)) base++;
  return base;
}

void FV3_(nrev)::printconfig()
{
  fprintf(stderr, "*** Freeverb config ***\n");
  fprintf(stderr, "Fs=%ld[Hz] x %ld\n",currentfs,SRC.getSRCFactor());
  fprintf(stderr, "roomsize %f\n", roomsize);
  fprintf(stderr, "damp %f damp2 %f damp3 %f wet %f wet1 %f wet2 %f\n",
	  damp, damp2, damp3, wet, wet1, wet2);
  fprintf(stderr, "dry %f width %f\n", dry,width);
}

void FV3_(nrev)::mute()
{
  for (long i=0;i<numcombs;i++)
    {
      combL[i].mute();
      combR[i].mute();
    }
  for (long i=0;i<numallpasses;i++)
    {
      allpassL[i].mute();
      allpassR[i].mute();
    }
}

void FV3_(nrev)::processreplace(fv3_float_t *inputL, fv3_float_t *inputR,
			  fv3_float_t *outputL, fv3_float_t *outputR,
			  long numsamples)
{
  long count = numsamples*SRC.getSRCFactor();
  fv3_float_t outL,outR,input;
  fv3_float_t *origOutL = outputL;
  fv3_float_t *origOutR = outputR;
  fv3_float_t *overL = NULL, *overR = NULL, *overOL = NULL, *overOR = NULL;
  try
    {
      overL = new fv3_float_t[numsamples*SRC.getSRCFactor()];
      overR = new fv3_float_t[numsamples*SRC.getSRCFactor()];
      overOL = new fv3_float_t[numsamples*SRC.getSRCFactor()];
      overOR = new fv3_float_t[numsamples*SRC.getSRCFactor()];
    }
  catch(std::bad_alloc)
    {
      delete[] overL;
      delete[] overR;
      delete[] overOL;
      delete[] overOR;
      return;
    }
  
  SRC.usrc(inputL, inputR, overL, overR, numsamples);
  inputL = overL;
  inputR = overR;
  outputL = overOL;
  outputR = overOR;
  
  while(count-- > 0)
    {
      input = (*inputL + *inputR);
      outL = outR = 0.0;

      // highpass filter
      static fv3_float_t hpf = 0.0;
      fv3_float_t hpfCof = damp3;
      input = hpf = -hpfCof*hpf + (1-hpfCof)*input;
      
      // Accumulate comb filters in parallel
      for(long i=0; i<numcombs; i++)
	{
	  outL += combL[i].process(input);
	  outR += combR[i].process(input);
	}
      
      // Feed through allpasses in series
      for(long i=0; i<3; i++)
	{
	  outL = allpassL[i].process(outL);
	  outR = allpassR[i].process(outR);
	}
      
      // lowpass filter
      static fv3_float_t lpfL = 0.0, lpfR = 0.0;
      fv3_float_t lpfCof = 0.7;
      lpfCof = damp2;
      lpfL = lpfCof*lpfL + (1-lpfCof)*outL;
      lpfR = lpfCof*lpfR + (1-lpfCof)*outR;
      outL = lpfL;
      outR = lpfR;
      
      outL = allpassL[3].process(outL);
      outR = allpassR[3].process(outR);
      //outRearL = allpassL[4].process(outL);
      //outRearR = allpassR[4].process(outR);
      
      outL = allpassL[5].process(outL);
      outR = allpassL[6].process(outR);
      //outRearL = allpassL[7].process(outRearL);
      //outRearR = allpassL[8].process(outRearR);

      // replacing
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
  delete[] overL;
  delete[] overR;
  delete[] overOL;
  delete[] overOR;
}

void FV3_(nrev)::update()
{
  long i;
  wet1 = wet*(width/2 + 0.5f);
  wet2 = wet*((1-width)/2);
  fv3_float_t back = roomsize * (fv3_float_t)currentfs * (fv3_float_t)SRC.getSRCFactor();
  for(i = 0;i < numcombs;i ++)
    {
      fv3_float_t fbl = pow(10.0, -3 * (fv3_float_t)combL[i].getsize() / back);
      combL[i].setfeedback(fbl);
      fv3_float_t fbr = pow(10.0, -3 * (fv3_float_t)combR[i].getsize() / back);
      combR[i].setfeedback(fbr);
    }
  for(i = 0;i < numcombs;i ++)
    {
      combL[i].setdamp(damp);
      combR[i].setdamp(damp);
    }
}

void FV3_(nrev)::setroomsize(fv3_float_t value)
{
  roomsize = value;
  update();
}

fv3_float_t FV3_(nrev)::getroomsize()
{
  return roomsize;
}
void FV3_(nrev)::setfeedback(fv3_float_t value)
{
  feedback = value;
  for(long i=0; i<numallpasses; i++)
    {
      allpassL[i].setfeedback(value);
      allpassR[i].setfeedback(value);
    }
}

fv3_float_t FV3_(nrev)::getfeedback()
{
  return feedback;
}

void FV3_(nrev)::setdamp(fv3_float_t value)
{
  damp = value;
  update();
}

fv3_float_t FV3_(nrev)::getdamp()
{
  return damp;
}

void FV3_(nrev)::setdamp2(fv3_float_t value)
{
  damp2 = value;
}

fv3_float_t FV3_(nrev)::getdamp2()
{
  return damp2;
}

void FV3_(nrev)::setdamp3(fv3_float_t value)
{
  damp3 = value;
}

fv3_float_t FV3_(nrev)::getdamp3()
{
  return damp3;
}

void FV3_(nrev)::setwet(fv3_float_t value)
{
  wetReal = value;
  wet = FV3_(utils)::dB2R(value)*FV3_NREV_SCALE_WET;
  update();
}

fv3_float_t FV3_(nrev)::getwet()
{
  return wetReal;
}

void FV3_(nrev)::setdry(fv3_float_t value)
{
  dryReal = value;
  dry = FV3_(utils)::dB2R(value);
}

fv3_float_t FV3_(nrev)::getdry()
{
  return dryReal;
}

void FV3_(nrev)::setwidth(fv3_float_t value)
{
  width = value;
  update();
}

fv3_float_t FV3_(nrev)::getwidth()
{
  return width;
}

void FV3_(nrev)::allocFilter(long ncomb, long nallpass)
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
      fprintf(stderr, "FV3_(nrev)::allocFilter() bad_alloc\n");
      delete[] combL;
      delete[] combR;
      delete[] allpassL;
      delete[] allpassR;
      throw std::bad_alloc();
    }
  numcombs = ncomb;
  numallpasses = nallpass;
}

void FV3_(nrev)::freeFilter()
{
  if(numcombs != 0&&numallpasses != 0)
    {
#ifdef DEBUG
  fprintf(stderr, "FV3_(nrev)::freeFilter()+\n");
#endif
      delete[] combL;
      delete[] combR;
      delete[] allpassL;
      delete[] allpassR;
      numcombs = 0;
      numallpasses = 0;
    }
}

void FV3_(nrev)::setFilter(fv3_float_t factor)
{
#ifdef DEBUG
  fprintf(stderr, "FV3_(nrev)::setBuffer(%f)\n", factor);
#endif
  const long combT[] = {1433, 1601, 1867, 2053, 2251, 2399};
  const long allpT[] = {347, 113, 37, 59, 53, 43, 37, 29, 19};
  //                  (0    1    2) F3  R4  L5  R6 RL7  RR8
  
  allocFilter(sizeof(combT)/sizeof(long), sizeof(allpT)/sizeof(long));
  long back =
    f_(FV3_NREV_STEREO_SPREAD, factor*(fv3_float_t)SRC.getSRCFactor());
  for(long i = 0;i < numcombs;i ++)
    {
      combL[i].setsize(p_(combT[i],factor));
      combR[i].setsize(p_(f_(combT[i],factor) + back,1));
    }
  for(long i = 0;i < numallpasses;i ++)
    {
      allpassL[i].setsize(p_(allpT[i],factor));
      allpassR[i].setsize(p_(f_(allpT[i],factor) + back,1));
    }
}

void FV3_(nrev)::setDefault()
{
  setDefaultFeedback();
}

void FV3_(nrev)::setDefaultFeedback()
{
  for(long i = 0;i < numallpasses;i ++)
    {
      allpassL[i].setfeedback(feedback);
      allpassR[i].setfeedback(feedback);
    }
}

#include "freeverb/fv3_ns_end.h"
