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

#include "freeverb/irmodel2.hpp"
#include "freeverb/fv3_type_float.h"
#include "freeverb/fv3_ns_start.h"

FV3_(irmodel2)::FV3_(irmodel2)()
{
#ifdef DEBUG
  fprintf(stderr, "FV3_(irmodel2)::FV3_(irmodel2)()\n");
#endif
  fragmentSize = FV3_IR2_DFragmentSize;
  impulseSize = 0;
  initialDelay = 0;
  fifoSize = 0;

  ZLstart = 0;
  
  wetdB = 0.0f;
  wet = FV3_(utils)::dB2R(wetdB);
  drydB = 0.0f;
  dry = FV3_(utils)::dB2R(drydB);
  width = 1.0f;
  update();
}

FV3_(irmodel2)::FV3_(~irmodel2)()
{
#ifdef DEBUG
  fprintf(stderr, "FV3_(irmodel2)::~FV3_(irmodel2)()\n");
#endif
  freeFragments();
  freeImpulse();
}

long FV3_(irmodel2)::getFragmentSize()
{
  return fragmentSize;
}

void FV3_(irmodel2)::freeFragments()
{
  for(std::vector<FV3_(frag)*>::iterator i = fragments.begin();
      i != fragments.end();i ++)
    {
      delete *i;
    }
  fragments.clear();
}

void FV3_(irmodel2)::muteAll()
{
  if(impulseSize == 0)
    return;
  bdL.setBlock(fragmentSize*2, (long)fragments.size());
  bdR.setBlock(fragmentSize*2, (long)fragments.size());
  fifoSize = fragmentSize;
  ZLstart = 0;
  FV3_(utils)::mute(fifoL, 3*fragmentSize);
  FV3_(utils)::mute(fifoR, 3*fragmentSize);
  FV3_(utils)::mute(revL, 2*fragmentSize);
  FV3_(utils)::mute(revR, 2*fragmentSize);
  FV3_(utils)::mute(restL, fragmentSize);
  FV3_(utils)::mute(restR, fragmentSize);
  FV3_(utils)::mute(ZLframeL, fragmentSize);
  FV3_(utils)::mute(ZLframeR, fragmentSize);
  FV3_(utils)::mute(ifftL, 2*fragmentSize);
  FV3_(utils)::mute(ifftR, 2*fragmentSize);
  
  delayL.mute();
  delayR.mute();
  delayWL.mute();
  delayWR.mute();
}

void FV3_(irmodel2)::loadImpulse(fv3_float_t * inputL, fv3_float_t * inputR,
				 long size)
{
  loadImpulse(inputL, inputR, size, FFTW_ESTIMATE);
}

void FV3_(irmodel2)::loadImpulse(fv3_float_t * inputL, fv3_float_t * inputR,
				 long size, unsigned fftflags)
{
  loadImpulse(inputL, inputR, size, FFTW_ESTIMATE,
	      FV3_IR2_DFragmentSize);
}

void FV3_(irmodel2)::loadImpulse(fv3_float_t * inputL, fv3_float_t * inputR,
				 long size, unsigned fftflags, long fragSize)
{
#ifdef DEBUG
  fprintf(stderr, "FV3_(irmodel2)::loadImpulse(%ld)\n", size);
#endif
  freeFragments();

  // optimize fragmentSize if fragSize >> (impulse)size
  if(FV3_(utils)::checkPow2(size)/2 < fragSize)
    fragmentSize = FV3_(utils)::checkPow2(size)/2;
  else
    fragmentSize = fragSize;
  
  delayL.setsize(fragmentSize);
  delayR.setsize(fragmentSize);
  delayWL.setsize(0);
  delayWR.setsize(0);
  delayL.mute();
  delayR.mute();
  delayWL.mute();
  delayWR.mute();

  ZLdelayL.setsize(0);
  ZLdelayR.setsize(0);
  ZLdelayWL.setsize(0);
  ZLdelayWR.setsize(0);
  
  impulseSize = size;
  allocImpulse(fragmentSize);
  long fragment_num = size / fragmentSize;
  long fragment_rest = size - fragmentSize * fragment_num;
  fv3_float_t * L_ = NULL, * R_ = NULL;

#ifdef DEBUG  
  fprintf(stderr, "FV3_(irmodel2).cpp: {%ldx%ld+%ld}\n",
	  fragmentSize, fragment_num, fragment_rest);
#endif
  try
    {
      for(long i = 0;i < fragment_num;i ++)
	{
	  FV3_(frag) * f = new FV3_(frag);
	  f->registerImpulse(inputL+(fragmentSize*i), inputR+(fragmentSize*i),
			     fragmentSize, fftflags);
	  fragments.push_back(f);
	}
      if(fragment_rest != 0)
	{
	  L_ = new fv3_float_t[fragmentSize];
	  R_ = new fv3_float_t[fragmentSize];
	  FV3_(utils)::mute(L_, fragmentSize);
	  FV3_(utils)::mute(R_, fragmentSize);
	  memcpy(L_, inputL+(fragmentSize*fragment_num),
		 sizeof(fv3_float_t)*fragment_rest);
	  memcpy(R_, inputR+(fragmentSize*fragment_num),
		 sizeof(fv3_float_t)*fragment_rest);
	  FV3_(frag) * f = new FV3_(frag);
	  f->registerImpulse(L_, R_, fragmentSize, fftflags);
	  fragments.push_back(f);
	}
      delete[] L_;
      delete[] R_;
    }
  catch(std::bad_alloc)
    {
      fprintf(stderr, "FV3_(irmodel2)::loadImpulse(%ld) bad_alloc\n", size);
      freeFragments(); 
      delete[] L_;
      delete[] R_;
      throw std::bad_alloc();
    }
  bdL.setBlock(fragmentSize*2, (long)fragments.size());
  bdR.setBlock(fragmentSize*2, (long)fragments.size());
}

void FV3_(irmodel2)::allocImpulse(long size)
{
  freeImpulse();
  try
    {
      fifoL = new fv3_float_t[3*size];
      fifoR = new fv3_float_t[3*size];
      revL = new fv3_float_t[2*size];
      revR = new fv3_float_t[2*size];
      restL = new fv3_float_t[size];
      restR = new fv3_float_t[size];
      ZLonlyL = new fv3_float_t[size];
      ZLonlyR = new fv3_float_t[size];
      ZLframeL = new fv3_float_t[size];
      ZLframeR = new fv3_float_t[size];
      ifftL = (fv3_float_t*)FFTW_(malloc)(sizeof(fv3_float_t)*2*size);
      ifftR = (fv3_float_t*)FFTW_(malloc)(sizeof(fv3_float_t)*2*size);
      swapL = (fv3_float_t*)FFTW_(malloc)(sizeof(fv3_float_t)*2*size);
      swapR = (fv3_float_t*)FFTW_(malloc)(sizeof(fv3_float_t)*2*size);
      if(ifftL == NULL||ifftR == NULL||swapL == NULL||swapR == NULL)
	throw std::bad_alloc();
    }
  catch(std::bad_alloc)
    {
      fprintf(stderr, "FV3_(irmodel2)::allocImpulse(%ld) bad_alloc\n", size);
      delete[] fifoL;
      delete[] fifoR;
      delete[] revL;
      delete[] revR;
      delete[] restL;
      delete[] restR;
      delete[] ZLonlyL;
      delete[] ZLonlyR;
      delete[] ZLframeL;
      delete[] ZLframeR;
      throw std::bad_alloc();
    }
  fifoSize = size;
  ZLstart = 0;
  FV3_(utils)::mute(fifoL, 3*size);
  FV3_(utils)::mute(fifoR, 3*size);
  FV3_(utils)::mute(revL, 2*size);
  FV3_(utils)::mute(revR, 2*size);
  FV3_(utils)::mute(restL, size);
  FV3_(utils)::mute(restR, size);
  FV3_(utils)::mute(ZLframeL, size);
  FV3_(utils)::mute(ZLframeR, size);
  FV3_(utils)::mute(ifftL, 2*size);
  FV3_(utils)::mute(ifftR, 2*size);
}

void FV3_(irmodel2)::unloadImpulse()
{
  if(impulseSize > 0)
    {
      freeImpulse();
      impulseSize = 0;
    }
}

void FV3_(irmodel2)::freeImpulse()
{
  if(fifoSize != 0)
    {
      fifoSize = 0;
      delete[] fifoL;
      delete[] fifoR;
      delete[] revL;
      delete[] revR;
      delete[] restL;
      delete[] restR;
      delete[] ZLonlyL;
      delete[] ZLonlyR;
      delete[] ZLframeL;
      delete[] ZLframeR;
      FFTW_(free)(ifftL);
      FFTW_(free)(ifftR);
      FFTW_(free)(swapL);
      FFTW_(free)(swapR);
    }
}

void FV3_(irmodel2)::setInitialDelay(long numsamples)
{
  initialDelay = numsamples;
  if(initialDelay >= 0)
    {
#ifdef DEBUG
      fprintf(stderr, "FV3_(irmodel2)::setInitialDelay(%ld) delayW(%ld))\n",
	      numsamples, initialDelay);
#endif
      delayL.setsize(fragmentSize);
      delayR.setsize(fragmentSize);
      delayWL.setsize(initialDelay);
      delayWR.setsize(initialDelay);
    }
  else if(fragmentSize - initialDelay >= 0)
    {
      long dryD = fragmentSize - initialDelay;
#ifdef DEBUG
      fprintf(stderr, "FV3_(irmodel2)::setInitialDelay(%ld) delayD(%ld))\n",
	      numsamples, dryD);
#endif
      delayL.setsize(dryD);
      delayR.setsize(dryD);
      delayWL.setsize(0);
      delayWR.setsize(0);
    }
  else
    {
      fprintf(stderr, "FV3_(irmodel2)::setInitialDelay(%ld) unknown samples\n",
	      numsamples);
      delayL.setsize(0);
      delayR.setsize(0);
      delayWL.setsize(0);
      delayWR.setsize(0);
    }
  delayL.mute();
  delayR.mute();
  delayWL.mute();
  delayWR.mute();

  // ZL
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

long  FV3_(irmodel2)::getInitialDelay()
{
  return initialDelay;
}

long FV3_(irmodel2)::getSampleSize()
{
  return impulseSize;
}

long FV3_(irmodel2)::getLatency()
{
  return fragmentSize;
}

void FV3_(irmodel2)::processreplace(fv3_float_t *inputL, fv3_float_t *inputR,
				    fv3_float_t *outputL, fv3_float_t *outputR,
				    long numsamples, unsigned options)
{
  if(numsamples <= 0||impulseSize <= 0||(long)fragments.size() <= 0)
    {
      return;
    }
  
  if(numsamples <= fragmentSize)
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
      if((options & FV3_IR2_ZERO_LATENCY) != 0)
	{
	  long cursor = 0;
	  if((fragmentSize - ZLstart) >= numsamples)
	    {
	      processZL(inputL, inputR, fifoL, fifoR, numsamples, options);
	    }
	  else
	    {
	      cursor = fragmentSize - ZLstart;
	      processZL(inputL, inputR, fifoL, fifoR,
			(fragmentSize - ZLstart), options);
	      long div = (numsamples-cursor)/fragmentSize;
	      for(long i = 0;i < div;i ++)
		{
		  processZL(inputL+cursor+i*fragmentSize,
			    inputR+cursor+i*fragmentSize,
			    fifoL+cursor+i*fragmentSize,
			    fifoR+cursor+i*fragmentSize,
			    fragmentSize, options);
		}
	      if((numsamples-cursor)%fragmentSize > 0)
		{
		  processZL(inputL+cursor+div*fragmentSize,
			    inputR+cursor+div*fragmentSize,
			    fifoL+cursor+div*fragmentSize,
			    fifoR+cursor+div*fragmentSize,
			    (numsamples-cursor)%fragmentSize, options);
		}
	    }
	  fpLSp = fifoL;
	  fpRSp = fifoR;
	}
      else
	{  
	  memcpy(&(fifoL[fifoSize+fragmentSize]), inputL,
		 sizeof(fv3_float_t)*numsamples);
	  memcpy(&(fifoR[fifoSize+fragmentSize]), inputR,
		 sizeof(fv3_float_t)*numsamples);
	  if(fifoSize+numsamples >= fragmentSize)
	    {
	      processSquare(fifoL+fragmentSize, fifoR+fragmentSize,
			    fifoL+fragmentSize, fifoR+fragmentSize,
			    options);
	    }
	  fpLSp = fifoL+fifoSize;
	  fpRSp = fifoR+fifoSize;
	}

      // process output loop
      if((options & FV3_IR2_SKIP_FILTER) == 0)
	{
	  for(long i = 0;i < numsamples;i ++)
	    {
	      fpLSp[i] = filter.processL(fpLSp[i]);
	      fpRSp[i] = filter.processR(fpRSp[i]);
	    }
	}

      if((options & FV3_IR2_ZERO_LATENCY) != 0)
	{
	  for(long i = 0;i < numsamples;i ++)
	    {
	      fpLSp[i] = delayWL.process(fpLSp[i]);
	      fpRSp[i] = delayWR.process(fpRSp[i]);
	    }
	}
      else
	{
	  for(long i = 0;i < numsamples;i ++)
	    {
	      fpLSp[i] = ZLdelayL.process(fpLSp[i]);
	      fpRSp[i] = ZLdelayR.process(fpRSp[i]);
	    }
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
	  if((options & FV3_IR2_ZERO_LATENCY) != 0)
	    {
	      for(long i = 0;i < numsamples;i ++)
		{
		  outputL[i] += ZLdelayWL.process(inputL[i])*dry;
		  outputR[i] += ZLdelayWR.process(inputR[i])*dry;
		}
	    }
	  else
	    {
	      for(long i = 0;i < numsamples;i ++)
		{
		  outputL[i] += delayL.process(inputL[i])*dry;
		  outputR[i] += delayR.process(inputR[i])*dry;
		}
	    }
	}

      // in Non ZL mode, move the block.
      if((options & FV3_IR2_ZERO_LATENCY) == 0)
	{
	  fifoSize += numsamples;
	  if(fifoSize >= fragmentSize)
	    {
	      memmove(fifoL, fifoL+fragmentSize,
		      sizeof(fv3_float_t)*2*fragmentSize);
	      memmove(fifoR, fifoR+fragmentSize,
		      sizeof(fv3_float_t)*2*fragmentSize);
	      fifoSize -= fragmentSize;
	    }
	}
    }
  // If the fragment size is too big, split the data.
  else
    {
      long div = numsamples/fragmentSize;
      for(long i = 0;i < div;i ++)
	{
	  processreplace(inputL+i*fragmentSize, inputR+i*fragmentSize,
			 outputL+i*fragmentSize, outputR+i*fragmentSize,
			 fragmentSize, options);
	}
      if(numsamples%fragmentSize > 0)
	{
	  processreplace(inputL+div*fragmentSize, inputR+div*fragmentSize,
			 outputL+div*fragmentSize, outputR+div*fragmentSize,
			 numsamples%fragmentSize, options);
	}
    }
  return;
}

void FV3_(irmodel2)::processZL(fv3_float_t *inputL, fv3_float_t *inputR,
			       fv3_float_t *outputL, fv3_float_t *outputR,
			       long numsamples, unsigned options)
{
  if(ZLstart == 0)
    {
      FV3_(utils)::mute(ZLframeL, fragmentSize);
      FV3_(utils)::mute(ZLframeR, fragmentSize);
      FV3_(utils)::mute(revL+fragmentSize-1, fragmentSize+1);
      FV3_(utils)::mute(revR+fragmentSize-1, fragmentSize+1);  
      FV3_(utils)::mute(swapL, fragmentSize*2);
      FV3_(utils)::mute(swapR, fragmentSize*2);
      for(long i = 1;i < (long)fragments.size();i ++)
	{
	  fragments[i]->processMULT(bdL.at(ifftL, i-1), bdR.at(ifftR, i-1),
				    swapL, swapR);
	}
    }
  
  FV3_(utils)::mute(ZLonlyL, fragmentSize);
  FV3_(utils)::mute(ZLonlyR, fragmentSize);
  if((options & FV3_IR2_MONO2STEREO) != 0)
    {
      for(long i = 0;i < numsamples;i ++)
	{
	  (ZLframeL+ZLstart)[i] = (ZLframeR+ZLstart)[i]
	    = (ZLonlyL+ZLstart)[i] = (ZLonlyR+ZLstart)[i]
	    = (inputL[i] + inputR[i])/2.0;
	}
    }
  else
    {
      memcpy(&(ZLframeL[ZLstart]), inputL, sizeof(fv3_float_t)*numsamples);
      memcpy(&(ZLframeR[ZLstart]), inputR, sizeof(fv3_float_t)*numsamples);
      memcpy(&(ZLonlyL[ZLstart]), inputL, sizeof(fv3_float_t)*numsamples);
      memcpy(&(ZLonlyR[ZLstart]), inputR, sizeof(fv3_float_t)*numsamples);
    }

  fragments[0]->processR2HC(ZLonlyL, ZLonlyR, ifftL, ifftR);
  fragments[0]->processMULT(ifftL, ifftR, swapL, swapR);
  FV3_(utils)::mute(revL, fragmentSize*2);
  FV3_(utils)::mute(revR, fragmentSize*2);
  fragments[0]->processHC2R(swapL, swapR, revL, revR);
  
  for(long i = 0;i < numsamples;i ++)
    {
      outputL[i] = (revL+ZLstart)[i] + (restL+ZLstart)[i];
      outputR[i] = (revR+ZLstart)[i] + (restL+ZLstart)[i];
    }
  
  ZLstart += numsamples;
  
  if(ZLstart == fragmentSize)
    {
      fragments[0]->processR2HC(ZLframeL, ZLframeR, ifftL, ifftR);
      memcpy(restL, revL+fragmentSize, sizeof(fv3_float_t)*(fragmentSize-1));
      memcpy(restR, revR+fragmentSize, sizeof(fv3_float_t)*(fragmentSize-1));
      ZLstart = 0;
    }
}

void FV3_(irmodel2)::processSquare(fv3_float_t *inputL, fv3_float_t *inputR,
				   fv3_float_t *outputL, fv3_float_t *outputR,
				   unsigned options)
{
  if((options & FV3_IR2_MONO2STEREO) != 0)
    {
      for(long i = 0;i < fragmentSize;i ++)
	inputL[i] = inputR[i] = (inputL[i] + inputR[i])/2.0;
    }
  fragments[0]->processR2HC(inputL, inputR, ifftL, ifftR);
  FV3_(utils)::mute(swapL, fragmentSize*2);
  FV3_(utils)::mute(swapR, fragmentSize*2);
  for(long i = 0;i < (long)fragments.size();i ++)
    {
      fragments[i]->processMULT(bdL.at(ifftL, i), bdR.at(ifftR, i),
				   swapL, swapR);
    }
  fragments[0]->processHC2R(swapL, swapR, revL, revR);
  memcpy(outputL, revL, sizeof(fv3_float_t)*fragmentSize);
  memcpy(revL, revL+fragmentSize, sizeof(fv3_float_t)*(fragmentSize-1));
  FV3_(utils)::mute(revL+fragmentSize-1, fragmentSize+1);
  
  memcpy(outputR, revR, sizeof(fv3_float_t)*fragmentSize);
  memcpy(revR, revR+fragmentSize, sizeof(fv3_float_t)*(fragmentSize-1));
  FV3_(utils)::mute(revR+fragmentSize-1, fragmentSize+1);  
}

void FV3_(irmodel2)::update()
{
  wet1 = wet*(width/2 + 0.5f);
  wet2 = wet*((1-width)/2);
}

void FV3_(irmodel2)::setwet(fv3_float_t db)
{
  wetdB = db;
  wet = FV3_(utils)::dB2R(wetdB);
  update();
}

fv3_float_t FV3_(irmodel2)::getwet()
{
  return wetdB;
}

void FV3_(irmodel2)::setdry(fv3_float_t db)
{
  drydB = db;
  dry = FV3_(utils)::dB2R(drydB);
}

fv3_float_t FV3_(irmodel2)::getdry()
{
  return drydB;
}

void FV3_(irmodel2)::setwidth(fv3_float_t value)
{
  width = value;
  update();
}

fv3_float_t FV3_(irmodel2)::getwidth()
{
  return width;
}

void FV3_(irmodel2)::setLPF(fv3_float_t value)
{
  filter.setLPF(value);
}

fv3_float_t FV3_(irmodel2)::getLPF()
{
  return filter.getLPF();
}

void FV3_(irmodel2)::setHPF(fv3_float_t value)
{
  filter.setHPF(value);
}

fv3_float_t FV3_(irmodel2)::getHPF()
{
  return filter.getHPF();
}

#include "freeverb/fv3_ns_end.h"
