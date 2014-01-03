/*  FIR 3 band splitter
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

#include "freeverb/fir3bandsplit.hpp"
#include "freeverb/fv3_type_float.h"
#include "freeverb/fv3_ns_start.h"

FV3_(fir3bandsplit)::FV3_(fir3bandsplit)()
{
  currentfs = 48000;
  fragmentSize = FV3_IR3_DFragmentSize;
  factor = FV3_IR3_DefaultFactor;
  WINDOW = FV3_W_BLACKMAN;
  fcLow = 145;
  fcHigh = 2500;
  trBand = 500;
  filterLength = 0;
  lpfF = bpfF = bpfF = NULL;
  lpfM = hpfM = NULL;
  allocIR(FV3_3BSPLIT_IR_IR2);
  update();
  mute();
}

FV3_(fir3bandsplit)::FV3_(~fir3bandsplit)()
{
  freeFilter();
  freeIR();
}

void FV3_(fir3bandsplit)::splitR(fv3_float_t *inputL, fv3_float_t *inputR,
				 fv3_float_t *outputL1, fv3_float_t *outputR1,
				 fv3_float_t *outputL2, fv3_float_t *outputR2,
				 fv3_float_t *outputL3, fv3_float_t *outputR3,
				 long numsamples)
{
  unsigned o = FV3_IR2_DEFAULT|FV3_IR2_MUTE_DRY|FV3_IR2_SKIP_FILTER;
  lpfM->processreplace(inputL, inputR, outputL1, outputR1, numsamples, o);
  // bpfM.processreplace(inputL, inputR, outputL2, outputR2, numsamples, o);
  hpfM->processreplace(inputL, inputR, outputL3, outputR3, numsamples, o);
  // build the rest band
  for(long s = 0;s < numsamples;s ++)
    {
      outputL2[s] = groupDelayL.process(inputL[s]);
      outputL2[s] -= (outputL1[s] + outputL3[s]);
      outputR2[s] = groupDelayR.process(inputR[s]);
      outputR2[s] -= (outputR1[s] + outputR3[s]);
    }
}

void FV3_(fir3bandsplit)::mergeR(fv3_float_t *inputL1, fv3_float_t *inputR1,
				 fv3_float_t *inputL2, fv3_float_t *inputR2,
				 fv3_float_t *inputL3, fv3_float_t *inputR3,
				 fv3_float_t *outputL, fv3_float_t *outputR,
				 fv3_float_t f1, fv3_float_t f2,
				 fv3_float_t f3, long numsamples)
{
  for(long i = 0;i < numsamples;i ++)
    {
      outputL[i] = inputL1[i]*f1 + inputL2[i]*f2 + inputL3[i]*f3;
      outputR[i] = inputR1[i]*f1 + inputR2[i]*f2 + inputR3[i]*f3;
    }
}

void FV3_(fir3bandsplit)::mute()
{
  lpfM->muteAll();
  // bpfM.muteAll();
  hpfM->muteAll();
  groupDelayL.mute();
  groupDelayR.mute();
}

void FV3_(fir3bandsplit)::allocFilter(long length)
{
  freeFilter();
  filterLength = length;
  try
    {
      lpfF = new fv3_float_t[length];
      bpfF = new fv3_float_t[length];
      hpfF = new fv3_float_t[length];
    }
  catch(std::bad_alloc)
    {
      fprintf(stderr, "fir3bandsplit::allocFilter(%ld) bad_alloc\n", length);
      freeFilter();
    }
}

void FV3_(fir3bandsplit)::freeFilter()
{
  lpfM->unloadImpulse();
  // bpfM.unloadImpulse();
  hpfM->unloadImpulse();
  if(filterLength > 0)
    {
      delete[] lpfF;
      delete[] bpfF;
      delete[] hpfF;
      lpfF = bpfF = bpfF = NULL;
    }
}

void FV3_(fir3bandsplit)::setCurrentFs(long fs)
{
  currentfs = fs;
  update();
}

long FV3_(fir3bandsplit)::getCurrentFs()
{
  return currentfs;
}

void FV3_(fir3bandsplit)::setWindow(long w)
{
  WINDOW = w;
  update();
}

long FV3_(fir3bandsplit)::getWindow()
{
  return WINDOW;
}

void FV3_(fir3bandsplit)::setLowFreqDivider(fv3_float_t fc)
{
  fcLow = fc;
  update();
}

fv3_float_t FV3_(fir3bandsplit)::getLowFreqDivider()
{
  return fcLow;
}

void FV3_(fir3bandsplit)::setHighFreqDivider(fv3_float_t fc)
{
  fcHigh = fc;
  update();
}

fv3_float_t FV3_(fir3bandsplit)::getHighFreqDivider()
{
  return fcHigh;
}

void FV3_(fir3bandsplit)::setTransitionBand(fv3_float_t fc)
{
  trBand = fc;
  update();
}

fv3_float_t FV3_(fir3bandsplit)::getTransitionBand()
{
  return trBand;
}

void FV3_(fir3bandsplit)::setParameter(fv3_float_t p)
{
  param = p;
  update();
}

fv3_float_t FV3_(fir3bandsplit)::getParameter()
{
  return param;
}

void FV3_(fir3bandsplit)::setFragmentSize(long size)
{
  if(size > 0)
    {
      fragmentSize = size;
      update();
    }
}

long FV3_(fir3bandsplit)::getFragmentSize()
{
  return fragmentSize;
}

void FV3_(fir3bandsplit)::setFactor(long val)
{
  if(val > 0)
    {
      factor = val;
      update();
    }
}

long FV3_(fir3bandsplit)::getFactor()
{
  return factor;
}

long FV3_(fir3bandsplit)::predictN(long w, fv3_float_t fc)
{
  long N = 4096;
  switch(w)
    {
    case FV3_W_SQUARE:
      N = (long)ceil((1.8*M_PI)/(fc*M_PI))+1;
      break;
    case FV3_W_BLACKMAN:
      N = (long)ceil((11*M_PI)/(fc*M_PI))+1;
      break;
    case FV3_W_HANNING:
      N = (long)ceil((6.2*M_PI)/(fc*M_PI))+1;
      break;
    case FV3_W_HAMMING:
      N = (long)ceil((6.6*M_PI)/(fc*M_PI))+1;
      break;
    case FV3_W_KAISER:
      //if(attenuation <= 21)
      N = (long)ceil(0.9222/fc)+1;
      //else
      //N = (long)ceil((attenuation-7.95)/(14.36*fc))+1;
      break;
    case FV3_W_COSRO:
      break;
    default:
      break;
    }
  return N;
}

void FV3_(fir3bandsplit)::update()
{
  fv3_float_t fc1, fc2, fcband;
  long N;
  if(fcLow < fcHigh)
    {
      fc1 = fcLow/(fv3_float_t)currentfs;
      fc2 = fcHigh/(fv3_float_t)currentfs;
    }
  else
    {
      fc2 = fcLow/(fv3_float_t)currentfs;
      fc1 = fcHigh/(fv3_float_t)currentfs;
    }
  fcband = trBand/(fv3_float_t)currentfs;
  N = predictN(WINDOW, fcband);
  // N is an odd number.
  if(N % 2 == 0) N ++;
  groupDelayL.setsize((N-1)/2+lpfM->getLatency());
  groupDelayR.setsize((N-1)/2+lpfM->getLatency());
  allocFilter(N);
  FV3_(firfilter)::lpf(lpfF, N, WINDOW, fc1, param);
  //> FV3_(firfilter)::bpf(bpfF, N, WINDOW, fc1,fc2, param);
  FV3_(firfilter)::hpf(hpfF, N, WINDOW, fc2, param);
  ///lpfM.loadImpulse(lpfF, lpfF, N, fragmentSize, factor);
  lpfM->loadImpulse(lpfF, lpfF, N);
  //> bpfM.loadImpulse(bpfF, bpfF, N, fragmentSize, factor);
  ///hpfM.loadImpulse(hpfF, hpfF, N, fragmentSize, factor);
  hpfM->loadImpulse(hpfF, hpfF, N);
  mute();
}

void FV3_(fir3bandsplit)::setIR(unsigned o)
{
  allocIR(o);
  update();
}

void FV3_(fir3bandsplit)::allocIR(unsigned o)
{
  switch(o)
    {
    case FV3_3BSPLIT_IR_IR3:
      lpfM = new FV3_(irmodel3);
      hpfM = new FV3_(irmodel3);
      break;
    case FV3_3BSPLIT_IR_IR2:
    default:
      lpfM = new FV3_(irmodel2);
      hpfM = new FV3_(irmodel2);
      break;
    }
  lpfM->setwet(0);
  // bpfM.setwet(0);
  hpfM->setwet(0);
}

void FV3_(fir3bandsplit)::freeIR()
{
  if(lpfM != NULL)
    {
      delete lpfM;
      delete hpfM;
      lpfM = hpfM = NULL;
    }
}

long FV3_(fir3bandsplit)::getLatency()
{
  return (filterLength-1)/2+lpfM->getLatency();
}

long FV3_(fir3bandsplit)::getGroupDelay()
{
  return (filterLength-1)/2;
}

long FV3_(fir3bandsplit)::getFilterLength()
{
  return filterLength;
}

#include "freeverb/fv3_ns_end.h"
