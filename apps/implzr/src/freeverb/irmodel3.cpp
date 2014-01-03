/*  Impulse Response Processor model implementation
 *  Low Latency Version
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

#include "freeverb/irmodel3.hpp"
#include "freeverb/fv3_type_float.h"
#include "freeverb/fv3_ns_start.h"

FV3_(irmodel3)::FV3_(irmodel3)()
{
#ifdef DEBUG
  fprintf(stderr, "FV3_(irmodel3)::FV3_(irmodel3)()\n");
#endif
  sFragmentSize = FV3_IR3_DFragmentSize;
  lFragmentSize = FV3_IR3_DefaultFactor * FV3_IR3_DFragmentSize;
  impulseSize = 0;
  initialDelay = 0;
  fifoSize = 0;
  Scursor = 0;
  Lcursor = 0;
  Lstep = 0;
  wetdB = 0.0f;
  wet = FV3_(utils)::dB2R(wetdB);
  drydB = 0.0f;
  dry = FV3_(utils)::dB2R(drydB);
  width = 1.0f;
  update();
  fifoL = fifoR = NULL;
  sRevL = sRevR = lRevL = lRevR = NULL;
  sifftL = sifftR = lifftL = lifftR = NULL;
  sSwapL = sSwapR = lSwapL = lSwapR = NULL;
  restL = restR = NULL;
  lFrameL = lFrameR = NULL;
  sOnlyL = sOnlyR = NULL;
}

FV3_(irmodel3)::FV3_(~irmodel3)()
{
#ifdef DEBUG
  fprintf(stderr, "FV3_(irmodel3)::~FV3_(irmodel3)()\n");
#endif
  freeFragments();
  freeImpulse();
}

long FV3_(irmodel3)::getSFragmentSize()
{
  return sFragmentSize;
}

long FV3_(irmodel3)::getLFragmentSize()
{
  return lFragmentSize;
}

void FV3_(irmodel3)::muteAll()
{
  if(impulseSize == 0)
    return;
  sBlockDelayL.mute();
  sBlockDelayR.mute();
  lBlockDelayL.mute();
  lBlockDelayR.mute();
  
  fifoSize = sFragmentSize;
  Scursor = 0;
  Lcursor = 0;
  Lstep = 0;
  FV3_(utils)::mute(fifoL, 3*sFragmentSize);
  FV3_(utils)::mute(fifoR, 3*sFragmentSize);

  FV3_(utils)::mute(sRevL, 2*sFragmentSize);
  FV3_(utils)::mute(sRevR, 2*sFragmentSize);
  FV3_(utils)::mute(lRevL, 2*lFragmentSize);
  FV3_(utils)::mute(lRevR, 2*lFragmentSize);

  FV3_(utils)::mute(sifftL, 2*sFragmentSize);
  FV3_(utils)::mute(sifftR, 2*sFragmentSize);
  FV3_(utils)::mute(lifftL, 2*lFragmentSize);
  FV3_(utils)::mute(lifftR, 2*lFragmentSize);

  FV3_(utils)::mute(sSwapL, 2*sFragmentSize);
  FV3_(utils)::mute(sSwapR, 2*sFragmentSize);
  FV3_(utils)::mute(lSwapL, 2*lFragmentSize);
  FV3_(utils)::mute(lSwapR, 2*lFragmentSize);
  
  FV3_(utils)::mute(restL, sFragmentSize);
  FV3_(utils)::mute(restR, sFragmentSize);

  FV3_(utils)::mute(lFrameL, lFragmentSize);
  FV3_(utils)::mute(lFrameR, lFragmentSize);

  FV3_(utils)::mute(sOnlyL, sFragmentSize);
  FV3_(utils)::mute(sOnlyR, sFragmentSize);
}

void FV3_(irmodel3)::loadImpulse(fv3_float_t * inputL, fv3_float_t * inputR,
				 long size)
{
  loadImpulse(inputL, inputR, size, FFTW_ESTIMATE);
}

void FV3_(irmodel3)::loadImpulse(fv3_float_t * inputL, fv3_float_t * inputR,
				 long size, unsigned fftflags)
{
  loadImpulse(inputL, inputR, size, FFTW_ESTIMATE,
	      FV3_IR3_DFragmentSize,
	      FV3_IR3_DefaultFactor);
}

void FV3_(irmodel3)::loadImpulse(fv3_float_t * inputL, fv3_float_t * inputR,
				 long size, unsigned fftflags, long fragSize)
{
  loadImpulse(inputL, inputR, size, FFTW_ESTIMATE,
	      fragSize,
	      FV3_IR3_DefaultFactor);
}

void FV3_(irmodel3)::loadImpulse(fv3_float_t * inputL, fv3_float_t * inputR,
				 long size, unsigned fftflags, long sFragSize,
				 long factor)
{
  long sFragmentNum = 0, lFragmentNum = 0;
  long sFragmentRest = 0, lFragmentRest = 0;
#ifdef DEBUG
  fprintf(stderr, "FV3_(irmodel3)::loadImpulse(%ld)\n", size);
#endif
  freeFragments();
  
  sFragmentSize = sFragSize;
  lFragmentSize = sFragSize*factor;
  impulseSize = size;
  
  ZLdelayL.mute();
  ZLdelayR.mute();
  ZLdelayWL.mute();
  ZLdelayWR.mute();

  allocSwap(sFragmentSize, lFragmentSize);
  if(size <= lFragmentSize)
    {
      sFragmentNum = size / sFragmentSize;
      sFragmentRest = size % sFragmentSize;
      lFragmentNum = 0;
      lFragmentRest = 0;
    }
  else
    {
      sFragmentNum = factor;
      sFragmentRest = 0;
      lFragmentNum = size / lFragmentSize - 1;
      lFragmentRest = size % lFragmentSize;
    }
  
#ifdef DEBUG  
  fprintf(stderr, "FV3_(irmodel3).cpp: {%ldx%ld+%ld+%ldx%ld+%ld}\n",
	  sFragmentSize, sFragmentNum, sFragmentRest,
	  lFragmentSize, lFragmentNum, lFragmentRest);
#endif

  try
    {  
      allocFragments(&sFragments, inputL, inputR,
		     sFragmentSize, sFragmentNum, sFragmentRest,
		     fftflags);
      if(size > lFragmentSize)
	{
	  allocFragments(&lFragments,
			 inputL+lFragmentSize, inputR+lFragmentSize,
			 lFragmentSize, lFragmentNum, lFragmentRest,
			 fftflags);
	}
    }
  catch(std::bad_alloc)
    {
      fprintf(stderr, "FV3_(irmodel3)::loadImpulse(%ld) bad_alloc\n", size);
      freeFragments();
    }
  
  sBlockDelayL.setBlock(sFragmentSize*2, (long)sFragments.size());
  sBlockDelayR.setBlock(sFragmentSize*2, (long)sFragments.size());
  lBlockDelayL.setBlock(lFragmentSize*2, (long)lFragments.size());
  lBlockDelayR.setBlock(lFragmentSize*2, (long)lFragments.size());
}

void FV3_(irmodel3)::freeFragments()
{
  for(std::vector<FV3_(frag)*>::iterator i = sFragments.begin();
      i != sFragments.end();i ++)
    {
      delete *i;
    }
  sFragments.clear();
  for(std::vector<FV3_(frag)*>::iterator i = lFragments.begin();
      i != lFragments.end();i ++)
    {
      delete *i;
    }
  lFragments.clear();
}

void FV3_(irmodel3)::allocFragments(std::vector<FV3_(frag)*> *to,
				    fv3_float_t *inputL, fv3_float_t *inputR,
				    long fragSize, long num, long rest,
				    unsigned fftflags)
{
  fv3_float_t * L_ = NULL, * R_ = NULL;
  try
    {
      for(long i = 0;i < num;i ++)
	{
	  FV3_(frag) * f = new FV3_(frag);
	  f->registerImpulse(inputL+(fragSize*i), inputR+(fragSize*i),
			     fragSize, fftflags);
	  to->push_back(f);
	}
      if(rest != 0)
	{
	  L_ = new fv3_float_t[fragSize];
	  R_ = new fv3_float_t[fragSize];
	  FV3_(utils)::mute(L_, fragSize);
	  FV3_(utils)::mute(R_, fragSize);
	  memcpy(L_, inputL+(fragSize*num), sizeof(fv3_float_t)*rest);
	  memcpy(R_, inputR+(fragSize*num), sizeof(fv3_float_t)*rest);
	  FV3_(frag) * f = new FV3_(frag);
	  f->registerImpulse(L_, R_, fragSize, fftflags);
	  to->push_back(f);
	}
      delete[] L_;
      delete[] R_;
    }
  catch(std::bad_alloc)
    {
      fprintf(stderr, "FV3_(irmodel3)::allocFragments(%ld) bad_alloc\n",
	      fragSize);
      delete[] L_;
      delete[] R_;
      throw std::bad_alloc();
    }
}

void FV3_(irmodel3)::allocSwap(long ssize, long lsize)
{
  freeImpulse();
  try
    {
      fifoL = new fv3_float_t[3*ssize];
      fifoR = new fv3_float_t[3*ssize];

      sRevL = new fv3_float_t[2*ssize];
      sRevR = new fv3_float_t[2*ssize];
      lRevL = new fv3_float_t[2*lsize];
      lRevR = new fv3_float_t[2*lsize];

      sifftL = (fv3_float_t*)FFTW_(malloc)(sizeof(fv3_float_t)*2*ssize);
      sifftR = (fv3_float_t*)FFTW_(malloc)(sizeof(fv3_float_t)*2*ssize);
      lifftL = (fv3_float_t*)FFTW_(malloc)(sizeof(fv3_float_t)*2*lsize);
      lifftR = (fv3_float_t*)FFTW_(malloc)(sizeof(fv3_float_t)*2*lsize);
      
      sSwapL = (fv3_float_t*)FFTW_(malloc)(sizeof(fv3_float_t)*2*ssize);
      sSwapR = (fv3_float_t*)FFTW_(malloc)(sizeof(fv3_float_t)*2*ssize);
      lSwapL = (fv3_float_t*)FFTW_(malloc)(sizeof(fv3_float_t)*2*lsize);
      lSwapR = (fv3_float_t*)FFTW_(malloc)(sizeof(fv3_float_t)*2*lsize);

      restL = new fv3_float_t[ssize];
      restR = new fv3_float_t[ssize];

      lFrameL = new fv3_float_t[lsize];
      lFrameR = new fv3_float_t[lsize];

      sOnlyL = new fv3_float_t[ssize];
      sOnlyR = new fv3_float_t[ssize];
      
      if(sifftL == NULL||sifftR == NULL||sSwapL == NULL||sSwapR == NULL||
	 lifftL == NULL||lifftR == NULL||lSwapL == NULL||lSwapR == NULL)
	throw std::bad_alloc();
    }
  catch(std::bad_alloc)
    {
      fprintf(stderr, "FV3_(irmodel3)::allocSwap(%ld,%ld) bad_alloc\n",
	      ssize, lsize);
      freeImpulse();
      throw std::bad_alloc();
    }
  fifoSize = ssize;
  Scursor = 0;
  Lcursor = 0;
  Lstep = 0;
  FV3_(utils)::mute(fifoL, 3*ssize);
  FV3_(utils)::mute(fifoR, 3*ssize);
  FV3_(utils)::mute(sRevL, 2*ssize);
  FV3_(utils)::mute(sRevR, 2*ssize);
  FV3_(utils)::mute(restL, ssize);
  FV3_(utils)::mute(restR, ssize);
  FV3_(utils)::mute(lRevL, 2*lsize);
  FV3_(utils)::mute(lRevR, 2*lsize);
  FV3_(utils)::mute(lFrameL, lsize);
  FV3_(utils)::mute(lFrameR, lsize);
  FV3_(utils)::mute(sifftL, 2*ssize);
  FV3_(utils)::mute(sifftR, 2*ssize);
  FV3_(utils)::mute(lifftL, 2*lsize);
  FV3_(utils)::mute(lifftR, 2*lsize);
}

void FV3_(irmodel3)::unloadImpulse()
{
  if(impulseSize > 0)
    {
      freeFragments();
      freeImpulse();
      impulseSize = 0;
    }
}

void FV3_(irmodel3)::freeImpulse()
{
  if(fifoSize != 0)
    {
      fifoSize = 0;
      delete[] fifoL;
      delete[] fifoR;
      fifoL = fifoR = NULL;

      delete[] sRevL;
      delete[] sRevR;
      delete[] lRevL;
      delete[] lRevR;
      sRevL = sRevR = lRevL = lRevR = NULL;

      FFTW_(free)(sifftL);
      FFTW_(free)(sifftR);
      FFTW_(free)(lifftL);
      FFTW_(free)(lifftR);
      sifftL = sifftR = lifftL = lifftR = NULL;

      FFTW_(free)(sSwapL);
      FFTW_(free)(sSwapR);
      FFTW_(free)(lSwapL);
      FFTW_(free)(lSwapR);
      sSwapL = sSwapR = lSwapL = lSwapR = NULL;

      delete[] restL;
      delete[] restR;
      restL = restR = NULL;

      delete[] lFrameL;
      delete[] lFrameR;
      lFrameL = lFrameR = NULL;

      delete[] sOnlyL;
      delete[] sOnlyR;
      sOnlyL = sOnlyR = NULL;
    }
}

void FV3_(irmodel3)::setInitialDelay(long numsamples)
{
  initialDelay = numsamples;
  if(initialDelay >= 0)
    {
      ZLdelayL.setsize(initialDelay);
      ZLdelayR.setsize(initialDelay);
      ZLdelayWL.setsize(0);
      ZLdelayWR.setsize(0);
    }
  else
    {
      ZLdelayWL.setsize(-initialDelay);
      ZLdelayWR.setsize(-initialDelay);
      ZLdelayL.setsize(0);
      ZLdelayR.setsize(0);
    }
  ZLdelayL.mute();
  ZLdelayR.mute();
  ZLdelayWL.mute();
  ZLdelayWR.mute();
}

long  FV3_(irmodel3)::getInitialDelay()
{
  return initialDelay;
}

long FV3_(irmodel3)::getSampleSize()
{
  return impulseSize;
}

long FV3_(irmodel3)::getLatency()
{
  return 0;
}

void FV3_(irmodel3)::processreplace(fv3_float_t *inputL, fv3_float_t *inputR,
				    fv3_float_t *outputL, fv3_float_t *outputR,
				    long numsamples, unsigned options)
{
  if(numsamples <= 0||impulseSize <= 0)
    {
      return;
    }
  
  if(numsamples <= sFragmentSize)
    {
      if((options & FV3_IR2_SWAP_LR) != 0)
	{
	  fv3_float_t * swapL;
	  swapL = outputL;
	  outputL = outputR;
	  outputR = swapL;
	}
      
      fv3_float_t * fpLSp;
      fv3_float_t * fpRSp;
      long cursor = 0;
      if((sFragmentSize - Scursor) >= numsamples)
	{
	  processZL(inputL, inputR, fifoL, fifoR, numsamples, options);
	}
      else
	{
	  cursor = sFragmentSize - Scursor;
	  processZL(inputL, inputR, fifoL, fifoR,
		    (sFragmentSize - Scursor), options);
	  long div = (numsamples-cursor)/sFragmentSize;
	  for(long i = 0;i < div;i ++)
	    {
	      processZL(inputL+cursor+i*sFragmentSize,
			inputR+cursor+i*sFragmentSize,
			fifoL+cursor+i*sFragmentSize,
			fifoR+cursor+i*sFragmentSize,
			sFragmentSize, options);
	    }
	  if((numsamples-cursor)%sFragmentSize > 0)
	    {
	      processZL(inputL+cursor+div*sFragmentSize,
			inputR+cursor+div*sFragmentSize,
			fifoL+cursor+div*sFragmentSize,
			fifoR+cursor+div*sFragmentSize,
			(numsamples-cursor)%sFragmentSize, options);
	    }
	}
      fpLSp = fifoL;
      fpRSp = fifoR;

      // process output loop
      if((options & FV3_IR2_SKIP_FILTER) == 0)
	{
	  for(long i = 0;i < numsamples;i ++)
	    {
	      fpLSp[i] = filter.processL(fpLSp[i]);
	      fpRSp[i] = filter.processR(fpRSp[i]);
	    }
	}
      for(long i = 0;i < numsamples;i ++)
	{
	  fpLSp[i] = ZLdelayL.process(fpLSp[i]);
	  fpRSp[i] = ZLdelayR.process(fpRSp[i]);
	}
      if((options & FV3_IR2_SKIP_INIT) == 0)
	{
	  FV3_(utils)::mute(outputL, numsamples);
	  FV3_(utils)::mute(outputR, numsamples);
	}
      if((options & FV3_IR2_MUTE_WET) == 0)
	{
	  for(long i = 0;i < numsamples;i ++)
	    {
	      outputL[i] += fpLSp[i]*wet1 + fpRSp[i]*wet2;
	      outputR[i] += fpRSp[i]*wet1 + fpLSp[i]*wet2;
	    }
	}
      if((options & FV3_IR2_MUTE_DRY) == 0)
	{
	  for(long i = 0;i < numsamples;i ++)
	    {
	      outputL[i] += ZLdelayWL.process(inputL[i])*dry;
	      outputR[i] += ZLdelayWR.process(inputR[i])*dry;
	    }
	}
    }
  else
    {
      long div = numsamples/sFragmentSize;
      for(long i = 0;i < div;i ++)
        {
          processreplace(inputL+i*sFragmentSize,
			 inputR+i*sFragmentSize,
                         outputL+i*sFragmentSize,
			 outputR+i*sFragmentSize,
                         sFragmentSize, options);
        }
      if(numsamples%sFragmentSize > 0)
        {
          processreplace(inputL+div*sFragmentSize,
			 inputR+div*sFragmentSize,
                         outputL+div*sFragmentSize,
			 outputR+div*sFragmentSize,
                         numsamples%sFragmentSize, options);
        }
    }
  return;
}

void FV3_(irmodel3)::processZL(fv3_float_t *inputL, fv3_float_t *inputR,
			       fv3_float_t *outputL, fv3_float_t *outputR,
			       long numsamples, unsigned options)
{
  if(Lcursor == 0)
    {
      if(lFragments.size() > 0)
	{
	  FV3_(utils)::mute(lFrameL, lFragmentSize);
	  FV3_(utils)::mute(lFrameR, lFragmentSize);
	  FV3_(utils)::mute(lRevL+lFragmentSize-1, lFragmentSize+1);
	  FV3_(utils)::mute(lRevR+lFragmentSize-1, lFragmentSize+1);
	  lBlockDelayL.push(lifftL);
	  lBlockDelayR.push(lifftR);
	  lFragments[0]->processMULT(lBlockDelayL.get(0), lBlockDelayR.get(0),
				     lSwapL, lSwapR);
	  lFragments[0]->processHC2R(lSwapL, lSwapR,	lRevL, lRevR);
	  FV3_(utils)::mute(lSwapL, lFragmentSize*2);
	  FV3_(utils)::mute(lSwapR, lFragmentSize*2);
	}
    }
  
  if(Scursor == 0)
    {
      sFrameL = lFrameL+Lcursor;
      sFrameR = lFrameR+Lcursor;
      FV3_(utils)::mute(sSwapL, sFragmentSize*2);
      FV3_(utils)::mute(sSwapR, sFragmentSize*2);
      sBlockDelayL.push(sifftL);
      sBlockDelayR.push(sifftR);
      for(long i = 1;i < (long)sFragments.size();i ++)
	{
	  sFragments[i]->processMULT(sBlockDelayL.get(i-1),
				     sBlockDelayR.get(i-1),
				     sSwapL, sSwapR);
	}
    }
  
  FV3_(utils)::mute(sOnlyL, sFragmentSize);
  FV3_(utils)::mute(sOnlyR, sFragmentSize);
  
  if((options & FV3_IR2_MONO2STEREO) != 0)
    {
      for(long i = 0;i < numsamples;i ++)
	{
	  (lFrameL+Lcursor)[i] = (lFrameR+Lcursor)[i]
	    = (sOnlyL+Scursor)[i] = (sOnlyR+Scursor)[i]
	    = (inputL[i] + inputR[i])/2.0;
	}
    }
  else
    {
      memcpy(lFrameL+Lcursor, inputL, sizeof(fv3_float_t)*numsamples);
      memcpy(lFrameR+Lcursor, inputR, sizeof(fv3_float_t)*numsamples);
      memcpy(sOnlyL+Scursor, inputL, sizeof(fv3_float_t)*numsamples);
      memcpy(sOnlyR+Scursor, inputR, sizeof(fv3_float_t)*numsamples);
    }
  
  if(sFragments.size() > 0)
    {
      sFragments[0]->processR2HC(sOnlyL, sOnlyR, sifftL, sifftR);
      sFragments[0]->processMULT(sifftL, sifftR, sSwapL, sSwapR);
      FV3_(utils)::mute(sRevL, sFragmentSize*2);
      FV3_(utils)::mute(sRevR, sFragmentSize*2);
      sFragments[0]->processHC2R(sSwapL, sSwapR, sRevL, sRevR);
    }
  
  if(lFragments.size() > 0)
    {
      for(long i = 0;i < numsamples;i ++)
	{
	  outputL[i]
	    = (sRevL+Scursor)[i] + (restL+Scursor)[i] + (lRevL+Lcursor)[i];
	  outputR[i]
	    = (sRevR+Scursor)[i] + (restR+Scursor)[i] + (lRevR+Lcursor)[i];
	}
    }
  else
    {
      for(long i = 0;i < numsamples;i ++)
	{
	  outputL[i]
	    = (sRevL+Scursor)[i] + (restL+Scursor)[i];
	  outputR[i]
	    = (sRevR+Scursor)[i] + (restR+Scursor)[i];
	}
    }
  
  Scursor += numsamples;
  Lcursor += numsamples;
  
  for(long i = Lstep;
      i < (((long)lFragments.size())-1)*Lcursor/lFragmentSize;i ++)
    {
      if(((long)lFragments.size()) > i+1)
	{
	  lFragments[i+1]->processMULT(lBlockDelayL.get(i),
				       lBlockDelayR.get(i),
				       lSwapL, lSwapR);
	}
      Lstep ++;
    }

  if(Scursor == sFragmentSize&&sFragments.size() > 0)
    {
      sFragments[0]->processR2HC(sFrameL, sFrameR, sifftL, sifftR);
      memcpy(restL, sRevL+sFragmentSize,
	     sizeof(fv3_float_t)*(sFragmentSize-1));
      memcpy(restR, sRevR+sFragmentSize,
	     sizeof(fv3_float_t)*(sFragmentSize-1));
      Scursor = 0;
    }
  
  if(Lcursor == lFragmentSize)
    {
      if(lFragments.size() > 0)
	{
	  lFragments[0]->processR2HC(lFrameL, lFrameR, lifftL, lifftR);
	  memcpy(lRevL, lRevL+lFragmentSize,
		 sizeof(fv3_float_t)*(lFragmentSize-1));
	  memcpy(lRevR, lRevR+lFragmentSize,
		 sizeof(fv3_float_t)*(lFragmentSize-1));
	}
      Lcursor = 0;
      Lstep = 0;
    }
}

void FV3_(irmodel3)::update()
{
  wet1 = wet*(width/2 + 0.5f);
  wet2 = wet*((1-width)/2);
}

void FV3_(irmodel3)::setwet(fv3_float_t db)
{
  wetdB = db;
  wet = FV3_(utils)::dB2R(wetdB);
  update();
}

fv3_float_t FV3_(irmodel3)::getwet()
{
  return wetdB;
}

void FV3_(irmodel3)::setdry(fv3_float_t db)
{
  drydB = db;
  dry = FV3_(utils)::dB2R(drydB);
}

fv3_float_t FV3_(irmodel3)::getdry()
{
  return drydB;
}

void FV3_(irmodel3)::setwidth(fv3_float_t value)
{
  width = value;
  update();
}

fv3_float_t FV3_(irmodel3)::getwidth()
{
  return width;
}

void FV3_(irmodel3)::setLPF(fv3_float_t value)
{
  filter.setLPF(value);
}

fv3_float_t FV3_(irmodel3)::getLPF()
{
  return filter.getLPF();
}

void FV3_(irmodel3)::setHPF(fv3_float_t value)
{
  filter.setHPF(value);
}

fv3_float_t FV3_(irmodel3)::getHPF()
{
  return filter.getHPF();
}

void FV3_(irmodel3)::printconfig()
{
  fprintf(stderr, "*** irmodel3 config ***\n");
  fprintf(stderr, "impulseSize = %ld\n", impulseSize);
  fprintf(stderr, "short Fragment Size = %ld\n", sFragmentSize);
  fprintf(stderr, "large Fragment Size = %ld\n", lFragmentSize);
  fprintf(stderr, "short Fragment vector Size = %ld\n",
	  (long)sFragments.size());
  fprintf(stderr, "large Fragment vector Size = %ld\n",
	  (long)lFragments.size());
}

long FV3_(irmodel3)::getSFragmentCount()
{
  return (long)sFragments.size();
}

long FV3_(irmodel3)::getLFragmentCount()
{
  return (long)lFragments.size();
}

void FV3_(irmodel3)::resume()
{
  ;
}

void FV3_(irmodel3)::suspend()
{
  ;
}

#include "freeverb/fv3_ns_end.h"
