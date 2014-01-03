/*  Simple Compressor
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

#include <string.h>

#include "freeverb/scomp.hpp"
#include "freeverb/fv3_type_float.h"
#include "freeverb/fv3_ns_start.h"

FV3_(scomp)::FV3_(scomp)()
{
  mute();
}

FV3_(scomp)::~FV3_(scomp)()
{
  ;
}

fv3_float_t FV3_(scomp)::process(fv3_float_t input)
{
  rmsf = Rms.process(input);
  theta = rmsf > env ? attackDelta : releaseDelta;
  env = (1.0-theta)*rmsf + theta*env;
  if(env < 0) env = 0;
  
  // gain reduction
  gain = 1.0;
  if(env >= highClip)
    {
#ifdef LIBFV3_FLOAT
      gain = expf((logf(env)-threshold_log)*r);
#endif
#ifdef LIBFV3_DOUBLE
      gain = exp((log(env)-threshold_log)*r);
#endif
#ifdef LIBFV3_LDOUBLE
      gain = expl((logl(env)-threshold_log)*r);
#endif
      return gain;
    }
  if(env >= lowClip)
    {
#ifdef LIBFV3_FLOAT
      fv3_float_t dif = logf(env)-threshold_log+log_soft;
      gain = expf(dif*dif*r/4.0/log_soft);
#endif
#ifdef LIBFV3_DOUBLE
      fv3_float_t dif = log(env)-threshold_log+log_soft;
      gain = exp(dif*dif*r/4.0/log_soft);
#endif
#ifdef LIBFV3_LDOUBLE
      fv3_float_t dif = logl(env)-threshold_log+log_soft;
      gain = expl(dif*dif*r/4.0/log_soft);
#endif
      return gain;
    }
  return gain;
}

fv3_float_t FV3_(scomp)::getEnv()
{
  return env;
}

void FV3_(scomp)::mute()
{
  gain = 1;
  env = 0;
}

long FV3_(scomp)::getRMS()
{
  return Rms.getsize();
}

void FV3_(scomp)::setRMS(long value)
{
  Rms.setsize(value);
}

long FV3_(scomp)::getAttack()
{
  return attack;
}

void FV3_(scomp)::setAttack(long value)
{
  Attack = attack = value;
  if(Attack > 0)
    attackDelta = exp(-1.0/Attack);
  else
    attackDelta = 0;
}

long FV3_(scomp)::getRelease()
{
  return release;
}

void FV3_(scomp)::setRelease(long value)
{
  Release = release = value;
  if(release > 0)
    releaseDelta = exp(-1.0/Release);
  else
    releaseDelta = 0.0;
}

fv3_float_t FV3_(scomp)::getThreshold()
{
  return Threshold;
}

fv3_float_t FV3_(scomp)::getSoftKnee()
{
  return SoftKnee;
}

void FV3_(scomp)::setThreshold(fv3_float_t value)
{
  Threshold = value;
#ifdef LIBFV3_FLOAT
  threshold_log = logf(Threshold);
#endif
#ifdef LIBFV3_DOUBLE
  threshold_log = log(Threshold);
#endif
#ifdef LIBFV3_LDOUBLE
  threshold_log = logl(Threshold);
#endif
  update();
}

void FV3_(scomp)::setSoftKnee(fv3_float_t dB)
{
  SoftKnee = dB;
#ifdef LIBFV3_FLOAT
  log_soft = logf(FV3_(utils)::dB2R(SoftKnee));
#endif
#ifdef LIBFV3_DOUBLE
  log_soft = log(FV3_(utils)::dB2R(SoftKnee));
#endif
#ifdef LIBFV3_LDOUBLE
  log_soft = logl(FV3_(utils)::dB2R(SoftKnee));
#endif
  update();
}

void FV3_(scomp)::update()
{
  lowClip = Threshold*FV3_(utils)::dB2R(-SoftKnee);
  highClip = Threshold*FV3_(utils)::dB2R(SoftKnee);
}

fv3_float_t FV3_(scomp)::getRatio()
{
  return Ratio;
}

void FV3_(scomp)::setRatio(fv3_float_t value)
{
  Ratio = value;
  r = -(1-1/Ratio);
}

#include "freeverb/fv3_ns_end.h"
