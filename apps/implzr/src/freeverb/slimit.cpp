/*  Simple Limiter
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

#include "freeverb/slimit.hpp"
#include "freeverb/fv3_type_float.h"
#include "freeverb/fv3_ns_start.h"

FV3_(slimit)::FV3_(slimit)()
{
  buffer = NULL;
  lookahead = bufsize = bufidx = 0;
  mute();
}

FV3_(slimit)::~FV3_(slimit)()
{
  if(bufsize > 0) delete[] buffer;
}

fv3_float_t FV3_(slimit)::process(fv3_float_t input)
{
  rmsf = Rms.process(input);

  if(lookahead > 0)
    {
      for(long i = 0;i < bufsize;i ++)
	buffer[i] += laDelta;
      buffer[bufidx] = rmsf-1;
      rmsf = 0;
      for(long i = 0;i < bufsize;i ++)
	if(rmsf < buffer[i]) rmsf = buffer[i];
      bufidx++;
      if(bufidx >= bufsize) bufidx = 0;
    }

  theta = rmsf > env ? attackDelta : releaseDelta;
  env = (1.0-theta)*rmsf + theta*env;
  if(env < 0) env = 0;
  
  // gain reduction
  gain = 1.0;
  if(env >= Threshold)
    {
#ifdef LIBFV3_FLOAT
      log_env = logf(env);
      gain = expf(R2-R1*C_T2/(log_env/R1+C_2T)-log_env);
#endif
#ifdef LIBFV3_DOUBLE
      log_env = log(env);
      gain = exp(R2-R1*C_T2/(log_env/R1+C_2T)-log_env);
#endif
#ifdef LIBFV3_LDOUBLE
      log_env = logl(env);
      gain = expl(R2-R1*C_T2/(log_env/R1+C_2T)-log_env);
#endif
      return gain;
    }
  return gain;
}

fv3_float_t FV3_(slimit)::getEnv()
{
  return env;
}

void FV3_(slimit)::mute()
{
  gain = 1;
  env = 0;
  peak = 0;
  delta = 0;
  bufidx = 0;
  if(lookahead > 0) FV3_(utils)::mute(buffer, bufsize);
  Rms.mute();
}

long FV3_(slimit)::getRMS()
{
  return Rms.getsize();
}

void FV3_(slimit)::setRMS(long value)
{
  Rms.setsize(value);
  mute();
}

long FV3_(slimit)::getLookahead()
{
  return lookahead;
}

void FV3_(slimit)::setLookahead(long value)
{
  lookahead = value;
  Lookahead = lookahead;

  bufsize = lookahead+1;
  bufidx = 0;
  laDelta = 1/Lookahead;
  
  if(bufidx > 0) delete[] buffer;
  try
    {
      buffer = new fv3_float_t[lookahead+1];
    }
  catch(std::bad_alloc)
    {
      fprintf(stderr, "FV3_(slimit)::setLa bad_alloc\n");
      delete[] buffer;
      bufsize = 0;
      throw std::bad_alloc();
    }

  mute();
}

long FV3_(slimit)::getAttack()
{
  return attack;
}

void FV3_(slimit)::setAttack(long value)
{
  Attack = attack = value;
  if(Attack > 0)
    attackDelta = exp(-1.0/Attack);
  else
    attackDelta = 0;
}

long FV3_(slimit)::getRelease()
{
  return release;
}

void FV3_(slimit)::setRelease(long value)
{
  Release = release = value;
  if(release > 0)
    releaseDelta = exp(-1.0/Release);
  else
    releaseDelta = 0.0;
}

fv3_float_t FV3_(slimit)::getThreshold()
{
  return Threshold;
}

void FV3_(slimit)::setThreshold(fv3_float_t value)
{
  Threshold = value;
  update();
}

fv3_float_t FV3_(slimit)::getCeiling()
{
  return Ceiling;
}

void FV3_(slimit)::setCeiling(fv3_float_t value)
{
  Ceiling = value;
  update();
}

void FV3_(slimit)::update()
{
  fv3_float_t db_ceil = FV3_(utils)::R2dB(Ceiling);
  fv3_float_t db_thr = FV3_(utils)::R2dB(Threshold);
  R1 = log(10.0)/20.0;
  C_T2 = (db_ceil-db_thr)*(db_ceil-db_thr);
  C_2T = db_ceil - 2*db_thr;
  R2 = R1*db_ceil;
}

#include "freeverb/fv3_ns_end.h"
