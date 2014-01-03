/*  Impulse Response Processor model implementation
 *
 *  Copyright (C) 2006, 2008 Teru KAMOGASHIRA
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

#include "freeverb/irmodel.hpp"
#include "freeverb/fv3_type_float.h"
#include "freeverb/fv3_ns_start.h"

FV3_(irmodel)::FV3_(irmodel)()
{
  current = 0;
  currentProcessSampleSize = 0;
  wetdB = 0.0f;
  wet = FV3_(utils)::dB2R(wetdB);
  drydB = 0.0f;
  dry = FV3_(utils)::dB2R(drydB);
  width = 1.0f;
  update();
  sampleSize = 0;
}

FV3_(irmodel)::FV3_(~irmodel)()
{
  freeFFT();
  freeImpulse();
}

void FV3_(irmodel)::loadImpulse(fv3_float_t * inputL, fv3_float_t * inputR,
				long size)
{
  loadImpulse(inputL, inputR, size, FFTW_ESTIMATE);
}

void FV3_(irmodel)::loadImpulse(fv3_float_t * inputL, fv3_float_t * inputR,
				long size, unsigned fftflags)
{
  impulseSize = size;
  long pulse = FV3_(utils)::checkPow2(size);
#ifdef DEBUG
  fprintf(stderr, "%ld->%ld\n", size, pulse);
#endif
  allocImpulse(pulse);
  
  FV3_(utils)::mute(impulseL, 2*pulse);
  memcpy(impulseL, inputL, sizeof(fv3_float_t)*size);
  FV3_(utils)::mute(impulseR, 2*pulse);
  memcpy(impulseR, inputR, sizeof(fv3_float_t)*size);

  FFTW_(plan) planL, planR;
  planL = FFTW_(plan_r2r_1d)(2*pulse, impulseL, fftImpulseL,
			     FFTW_R2HC, FFTW_ESTIMATE);
  planR = FFTW_(plan_r2r_1d)(2*pulse, impulseR, fftImpulseR,
			     FFTW_R2HC, FFTW_ESTIMATE);
  FFTW_(execute)(planL);
  FFTW_(execute)(planR);
  FFTW_(destroy_plan)(planL);
  FFTW_(destroy_plan)(planR);

  if(currentProcessSampleSize != pulse)
    allocFFT(pulse, fftflags);

  delayL.setsize(size);
  delayR.setsize(size);
  
  muteAll();
}

void FV3_(irmodel)::unloadImpulse()
{
  freeFFT();
  freeImpulse();
}

void FV3_(irmodel)::muteAll()
{
  current = 0;
  FV3_(utils)::mute(delaylineL, impulseSize*2);
  FV3_(utils)::mute(delaylineR, impulseSize*2);
  FV3_(utils)::mute(fifoL, sampleSize*3);
  FV3_(utils)::mute(fifoR, sampleSize*3);
  delayL.mute();
  delayR.mute();
}

long FV3_(irmodel)::getSampleSize()
{
  return sampleSize;
}

long FV3_(irmodel)::getLatency()
{
  return delayL.getsize();
}

void FV3_(irmodel)::processreplace(fv3_float_t *inputL, fv3_float_t *inputR,
				   fv3_float_t *outputL, fv3_float_t *outputR,
				   long numsamples, unsigned options)
{
  if(numsamples == 0||impulseSize == 0)
    {
      return;
    }
  if(numsamples <= impulseSize)
    {
      memcpy(&(fifoL[fifoSize+impulseSize]), inputL,
	     sizeof(fv3_float_t)*numsamples);
      memcpy(&(fifoR[fifoSize+impulseSize]), inputR,
	     sizeof(fv3_float_t)*numsamples);
      if(fifoSize+numsamples >= impulseSize)
	{
	  processSquare(fifoL+impulseSize, fifoR+impulseSize,
			fifoL+impulseSize, fifoR+impulseSize);
	}
      for(long i = 0;i < numsamples;i ++)
	{
	  // replacing
	  outputL[i] = fifoL[i+fifoSize]*wet1 + fifoR[i+fifoSize]*wet2 +
	    delayL.process(inputL[i])*dry;
	  outputR[i] = fifoR[i+fifoSize]*wet1 + fifoL[i+fifoSize]*wet2 +
	    delayR.process(inputR[i])*dry;
	}
      fifoSize += numsamples;
      if(fifoSize >= impulseSize)
	{
	  memmove(fifoL, &(fifoL[impulseSize]),
		  sizeof(fv3_float_t)*2*impulseSize);
	  memmove(fifoR, &(fifoR[impulseSize]),
		  sizeof(fv3_float_t)*2*impulseSize);
	  fifoSize -= impulseSize;
	}
    }
  else
    {
      // divide
      long div = numsamples/(impulseSize);
      for(long i = 0;i < div;i ++)
	{
	  processreplace(inputL+i*impulseSize, inputR+i*impulseSize,
			 outputL+i*impulseSize, outputR+i*impulseSize,
			 impulseSize, options);
	}
      processreplace(inputL+div*impulseSize, inputR+div*impulseSize,
		     outputL+div*impulseSize, outputR+div*impulseSize,
		     numsamples%impulseSize, options);
    }
}

void FV3_(irmodel)::processSquare(fv3_float_t *inputL, fv3_float_t *inputR,
				  fv3_float_t *outputL, fv3_float_t *outputR)
{
  FV3_(utils)::mute(fftOrigL, sampleSize*2);
  FV3_(utils)::mute(fftOrigR, sampleSize*2);
  memcpy(fftOrigL, inputL, sizeof(fv3_float_t)*impulseSize);
  memcpy(fftOrigR, inputR, sizeof(fv3_float_t)*impulseSize);
  
  FFTW_(execute)(planOrigL);
  FFTW_(execute)(planOrigR);
  
  // mul
  fftRevL[0] = fftOrigL[0] * fftImpulseL[0];
  fftRevR[0] = fftOrigR[0] * fftImpulseR[0];
  fftRevL[sampleSize] = fftOrigL[sampleSize] * fftImpulseL[sampleSize];
  fftRevR[sampleSize] = fftOrigR[sampleSize] * fftImpulseR[sampleSize];
  for(long i = 1;i < sampleSize;i ++)
    {
      {
	fv3_float_t e = fftOrigL[i];
	fv3_float_t d = fftOrigL[sampleSize*2 - i];
	fv3_float_t f = fftImpulseL[i];
	fv3_float_t g = fftImpulseL[sampleSize*2 - i];
	fftRevL[2*sampleSize-i] = e*g + f*d;
	fftRevL[i] = e*f - d*g;
      }
      {
	fv3_float_t e = fftOrigR[i];
	fv3_float_t d = fftOrigR[sampleSize*2 - i];
	fv3_float_t f = fftImpulseR[i];
	fv3_float_t g = fftImpulseR[sampleSize*2 - i];
	fftRevR[2*sampleSize-i] = e*g + f*d;
	fftRevR[i] = e*f - d*g;
      }
    }
  
  FFTW_(execute)(planRevL);
  FFTW_(execute)(planRevR);
  for(long i = 0;i < impulseSize*2;i ++)
    {
      fftRevL[i] /= impulseSize*2;
      fftRevR[i] /= impulseSize*2;
    }
  
  // sigma
  // XXXXOOOO
  // OXXXXOOO
  // OOXXXXOO
  // OOOXXXXO
  // 11112222
  // -------
  // --- ----
  // ^
  //     ^
  if(current == 0)
    {
      for(long i = 0;i < impulseSize*2-1;i ++)
	{
	  delaylineL[i] += fftRevL[i];
	  delaylineR[i] += fftRevR[i];
	}

      memcpy(outputL, delaylineL, sizeof(fv3_float_t)*impulseSize);
      memcpy(outputR, delaylineR, sizeof(fv3_float_t)*impulseSize);
      FV3_(utils)::mute(delaylineL, impulseSize);
      FV3_(utils)::mute(delaylineR, impulseSize);
      current = impulseSize;
    }
  else // current == impulseSize
    {
      for(long i = 0;i < impulseSize;i ++)
	{
	  delaylineL[impulseSize+i] += fftRevL[i];
	  delaylineR[impulseSize+i] += fftRevR[i];
	}
      for(long i = 0;i < impulseSize-1;i ++)
	{
	  delaylineL[i] += fftRevL[impulseSize+i];
	  delaylineR[i] += fftRevR[impulseSize+i];
	}
      memcpy(outputL, &(delaylineL[impulseSize]),
	     sizeof(fv3_float_t)*impulseSize);
      memcpy(outputR, &(delaylineR[impulseSize]),
	     sizeof(fv3_float_t)*impulseSize);
      FV3_(utils)::mute(&(delaylineL[impulseSize]), impulseSize);
      FV3_(utils)::mute(&(delaylineR[impulseSize]), impulseSize);
      current = 0;
    }
}

void FV3_(irmodel)::allocImpulse(long numsamples)
{
  freeImpulse();
  try
    {
      impulseL = new fv3_float_t[2*numsamples];
      impulseR = new fv3_float_t[2*numsamples];
      fifoL = new fv3_float_t[3*numsamples];
      fifoR = new fv3_float_t[3*numsamples];
      delaylineL = new fv3_float_t[2*impulseSize];
      delaylineR = new fv3_float_t[2*impulseSize];
    }
  catch(std::bad_alloc)
    {
      fprintf(stderr, "FV3_(irmodel)::allocImpulse(%ld) bad_alloc\n",
	      numsamples);
      delete[] fifoL;
      delete[] fifoR;
      delete[] delaylineL;
      delete[] delaylineR;
      delete[] impulseL;
      delete[] impulseR;
      throw std::bad_alloc();
    }
  fftImpulseL = (fv3_float_t*)FFTW_(malloc)(sizeof(fv3_float_t)*2*numsamples);
  fftImpulseR = (fv3_float_t*)FFTW_(malloc)(sizeof(fv3_float_t)*2*numsamples);
  if(fftImpulseL == NULL||fftImpulseR == NULL)
    {
      fprintf(stderr, "FV3_(irmodel)::allocImpulse(%ld) fftw_malloc!\n",
	      numsamples);
      FFTW_(free)(fftImpulseL);
      FFTW_(free)(fftImpulseR);
      throw std::bad_alloc();
    }
  fifoSize = numsamples;
  sampleSize = numsamples;
}

void FV3_(irmodel)::freeImpulse()
{
  if(sampleSize != 0)
    {
      delete[] fifoL;
      delete[] fifoR;
      delete[] delaylineL;
      delete[] delaylineR;
      delete[] impulseL;
      delete[] impulseR;
      FFTW_(free)(fftImpulseL);
      FFTW_(free)(fftImpulseR);
      fifoSize = 0;
      sampleSize = 0;
    }
}

void FV3_(irmodel)::allocFFT(long numsamples, unsigned fftflags)
{
  freeFFT();
  fftRevL = (fv3_float_t*)FFTW_(malloc)(sizeof(fv3_float_t)*2*numsamples);
  fftRevR = (fv3_float_t*)FFTW_(malloc)(sizeof(fv3_float_t)*2*numsamples);
  fftOrigL = (fv3_float_t*)FFTW_(malloc)(sizeof(fv3_float_t)*2*numsamples);
  fftOrigR = (fv3_float_t*)FFTW_(malloc)(sizeof(fv3_float_t)*2*numsamples);
  if(fftRevL == NULL||fftRevR == NULL||fftOrigL == NULL||fftOrigR == NULL)
    {
      fprintf(stderr, "FV3_(irmodel)::allocFFT(%ld) fftw_malloc!\n",
	      numsamples);
      FFTW_(free)(fftRevL);
      FFTW_(free)(fftRevR);
      FFTW_(free)(fftOrigL);
      FFTW_(free)(fftOrigR);
      throw std::bad_alloc();
    }
  planOrigL = FFTW_(plan_r2r_1d)(2*numsamples, fftOrigL, fftOrigL,
				 FFTW_R2HC, fftflags);
  planOrigR = FFTW_(plan_r2r_1d)(2*numsamples, fftOrigR, fftOrigR,
				 FFTW_R2HC, fftflags);
  planRevL = FFTW_(plan_r2r_1d)(2*numsamples, fftRevL, fftRevL,
				FFTW_HC2R, fftflags);
  planRevR = FFTW_(plan_r2r_1d)(2*numsamples, fftRevR, fftRevR,
				FFTW_HC2R, fftflags);
  currentProcessSampleSize = numsamples;
  FV3_(utils)::mute(fftRevL, sampleSize*2);
  FV3_(utils)::mute(fftRevR, sampleSize*2);
  FV3_(utils)::mute(fftOrigL, sampleSize*2);
  FV3_(utils)::mute(fftOrigR, sampleSize*2);
}

void FV3_(irmodel)::freeFFT()
{
  if(currentProcessSampleSize != 0)
    {
      FFTW_(free)(fftRevL);
      FFTW_(free)(fftRevR);
      FFTW_(destroy_plan)(planRevL);
      FFTW_(destroy_plan)(planRevR);
      FFTW_(free)(fftOrigL);
      FFTW_(free)(fftOrigR);
      FFTW_(destroy_plan)(planOrigL);
      FFTW_(destroy_plan)(planOrigR);
    }
}

void FV3_(irmodel)::update()
{
  wet1 = wet*(width/2 + 0.5f);
  wet2 = wet*((1-width)/2);
}

void FV3_(irmodel)::setwet(fv3_float_t db)
{
  wetdB = db;
  wet = FV3_(utils)::dB2R(wetdB);
  update();
}

fv3_float_t FV3_(irmodel)::getwet()
{
  return wetdB;
}

void FV3_(irmodel)::setdry(fv3_float_t db)
{
  drydB = db;
  dry = FV3_(utils)::dB2R(drydB);
}

fv3_float_t FV3_(irmodel)::getdry()
{
  return drydB;
}

void FV3_(irmodel)::setwidth(fv3_float_t value)
{
  width = value;
  update();
}

fv3_float_t FV3_(irmodel)::getwidth()
{
  return width;
}

void FV3_(irmodel)::setLPF(fv3_float_t value)
{
  filter.setLPF(value);
}

fv3_float_t FV3_(irmodel)::getLPF()
{
  return filter.getLPF();
}

void FV3_(irmodel)::setHPF(fv3_float_t value)
{
  filter.setHPF(value);
}

fv3_float_t FV3_(irmodel)::getHPF()
{
  return filter.getHPF();
}

#include "freeverb/fv3_ns_end.h"
