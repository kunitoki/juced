/*  Utility
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

#include "freeverb/utils.hpp"
#include "freeverb/fv3_type_float.h"
#include "freeverb/fv3_ns_start.h"

fv3_float_t FV3_(utils)::dB2R(fv3_float_t dB)
{
  return pow(10, dB/20);
}

fv3_float_t FV3_(utils)::R2dB(fv3_float_t real)
{
  return 20*log(real)/log(10.0f);
}

long FV3_(utils)::ms2sample(fv3_float_t msec, long fs)
{
  return (long)(msec*(fv3_float_t)fs/1000);
}

void FV3_(utils)::mute(fv3_float_t * f, long t)
{
  memset(f, 0, sizeof(fv3_float_t)*t);
}

long FV3_(utils)::checkPow2(long i)
{
  long p = 2;
  while(p < i)
    p *= 2;
  return p;
}

bool FV3_(utils)::isPrime(long number)
{
  if(number == 2) return true;
  if(number & 1)
    {
      for (long i=3; i<(long)sqrt((double)number)+1; i+=2)
	if ( (number % i) == 0) return false;
      return true; // prime
    }
  else
    return false; // even
}

#include "freeverb/fv3_ns_end.h"
