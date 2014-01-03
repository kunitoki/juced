/*  Impulse Response Processor model implementation
 *
 *  Copyright (C) 2008 Teru KAMOGASHIRA
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

#include "freeverb/irmodels.hpp"
#include "freeverb/fv3_type_float.h"
#include "freeverb/fv3_ns_start.h"

FV3_(irmodels)::FV3_(irmodels)()
{
  delayL = delayR = impulseL = impulseR = NULL;
  impulseSize = 0;
  current = impulseSize;
  wetdB = 0.0f;
  wet = FV3_(utils)::dB2R(wetdB);
  drydB = 0.0f;
  dry = FV3_(utils)::dB2R(drydB);
  width = 1.0f;
  update();
}

FV3_(irmodels)::FV3_(~irmodels)()
{
  freeImpulse();
}

void FV3_(irmodels)::unloadImpulse()
{
  freeImpulse();
}

void FV3_(irmodels)::loadImpulse(fv3_float_t * inputL, fv3_float_t * inputR,
				long size)
{
  loadImpulse(inputL, inputR, size, 0);
}

void FV3_(irmodels)::loadImpulse(fv3_float_t * inputL, fv3_float_t * inputR,
				long size, unsigned fftflags)
{
  impulseSize = size;
  allocImpulse(size);
  memcpy(impulseL, inputL, sizeof(fv3_float_t)*size);
  memcpy(impulseR, inputR, sizeof(fv3_float_t)*size);
  muteAll();
}

long FV3_(irmodels)::getSampleSize()
{
  return impulseSize;
}

long FV3_(irmodels)::getLatency()
{
  return 0;
}

void FV3_(irmodels)::processreplace(fv3_float_t *inputL, fv3_float_t *inputR,
				   fv3_float_t *outputL, fv3_float_t *outputR,
				   long numsamples, unsigned options)
{
  if(numsamples == 0||impulseSize == 0)
    {
      return;
    }
  for(long i = 0;i < numsamples;i ++)
    {
      fv3_float_t * offsetL = delayL + current;
      fv3_float_t * offsetR = delayR + current;
      fv3_float_t L = 0, R = 0;
      offsetL[0] = inputL[i]; offsetR[0] = inputR[i];
      
      for(long j = 0;j < impulseSize;j ++)
	L += impulseL[j]*offsetL[j];
      for(long j = 0;j < impulseSize;j ++)
	R += impulseR[j]*offsetR[j];
      
      if(current == 0)
	{
	  current = impulseSize;
	  memmove(delayL+impulseSize+1, delayL,
		  sizeof(fv3_float_t)*(impulseSize-1));
	  memmove(delayR+impulseSize+1, delayR,
		  sizeof(fv3_float_t)*(impulseSize-1));
	}
      else
	current --;
      
      if((options & FV3_IR2_SKIP_FILTER) == 0)
	{
	  L = filter.processL(L);
	  R = filter.processR(R);
	}
      
      outputL[i] = outputR[i] = 0;
      if((options & FV3_IR2_MUTE_DRY) == 0)
	{
	  outputL[i] += inputL[i]*dry;
	  outputR[i] += inputR[i]*dry;
	}
      if((options & FV3_IR2_MUTE_WET) == 0)
	{
	  outputL[i] += L*wet1+R*wet2;
	  outputR[i] += R*wet1+L*wet2;
	}
    }
}

void FV3_(irmodels)::muteAll()
{
  if(impulseSize == 0)
    return;
  FV3_(utils)::mute(delayL, impulseSize*2);
  FV3_(utils)::mute(delayR, impulseSize*2);
  current = impulseSize;
}

void FV3_(irmodels)::allocImpulse(long size)
{
  freeImpulse();
  try
    {
      impulseL = new fv3_float_t[size];
      impulseR = new fv3_float_t[size];
      delayL = new fv3_float_t[size*2];
      delayR = new fv3_float_t[size*2];
    }
  catch(std::bad_alloc)
    {
      fprintf(stderr, "FV3_(irmodels)::allocImpulse(%ld) bad_alloc\n", size);
      delete[] impulseL;
      delete[] impulseR;
      delete[] delayL;
      delete[] delayR;
      throw std::bad_alloc();
    }
  impulseSize = size;
}

void FV3_(irmodels)::freeImpulse()
{
  if(impulseSize != 0)
    {
      delete[] impulseL;
      delete[] impulseR;
      impulseL = impulseR = NULL;
      impulseSize = 0;
    }
}

void FV3_(irmodels)::update()
{
  wet1 = wet*(width/2 + 0.5f);
  wet2 = wet*((1-width)/2);
}

void FV3_(irmodels)::setwet(fv3_float_t db)
{
  wetdB = db;
  wet = FV3_(utils)::dB2R(wetdB);
  update();
}

fv3_float_t FV3_(irmodels)::getwet()
{
  return wetdB;
}

void FV3_(irmodels)::setdry(fv3_float_t db)
{
  drydB = db;
  dry = FV3_(utils)::dB2R(drydB);
}

fv3_float_t FV3_(irmodels)::getdry()
{
  return drydB;
}

void FV3_(irmodels)::setwidth(fv3_float_t value)
{
  width = value;
  update();
}

fv3_float_t FV3_(irmodels)::getwidth()
{
  return width;
}

void FV3_(irmodels)::setLPF(fv3_float_t value)
{
  filter.setLPF(value);
}

fv3_float_t FV3_(irmodels)::getLPF()
{
  return filter.getLPF();
}

void FV3_(irmodels)::setHPF(fv3_float_t value)
{
  filter.setHPF(value);
}

fv3_float_t FV3_(irmodels)::getHPF()
{
  return filter.getHPF();
}

#include "freeverb/fv3_ns_end.h"
