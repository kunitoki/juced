/*  RMS
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

#include "freeverb/rms.hpp"
#include "freeverb/fv3_type_float.h"
#include "freeverb/fv3_ns_start.h"

#include <string.h>

FV3_(rms)::FV3_(rms)()
{
  sum = 0;
  bufs = bufsize = 0;
  bufidx = 0;
}

FV3_(rms)::~FV3_(rms)()
{
  if(bufsize != 0)
    {
      delete[] buffer;
    }
}

long FV3_(rms)::getsize()
{
  return bufsize;
}

void FV3_(rms)::setsize(long size)
{
#ifdef DEBUG
  fprintf(stderr, "FV3_(rms)::setsize(%ld)\n", size);
#endif
  if(bufsize != 0)
    {
      delete[] buffer;
    }
  try
    {
      buffer = new fv3_float_t[size];
    }
  catch(std::bad_alloc)
    {
      fprintf(stderr, "FV3_(rms)::setsize(%ld) bad_alloc\n", size);
      delete[] buffer;
      bufsize = 0;
      throw std::bad_alloc();
    }
  bufs = bufsize = size;
  bufidx = 0;
  mute();
}

void FV3_(rms)::mute()
{
  for (long i = 0;i < bufsize;i ++)
    buffer[i] = 0;
  sum = 0;
}

fv3_float_t FV3_(rms)::process(fv3_float_t input)
{
  if(bufsize == 0)
#ifdef LIBFV3_FLOAT
    return fabsf(input);
#endif
#ifdef LIBFV3_DOUBLE
    return fabs(input);
#endif
#ifdef LIBFV3_LDOUBLE
    return fabsl(input);
#endif
  if(bufidx == bufsize-1)
    bufidx = 0;
  else
    bufidx ++;
  sum -= buffer[bufidx];
  buffer[bufidx] = input*input;
  sum += buffer[bufidx];
  if(sum < 0) sum = 0;
#ifdef LIBFV3_FLOAT
    float ret = sqrtf(sum/bufs);
#endif
#ifdef LIBFV3_DOUBLE
    float ret = sqrt(sum/bufs);
#endif
#ifdef LIBFV3_LDOUBLE
    float ret = sqrtl(sum/bufs);
#endif
  return ret;
}

#include "freeverb/fv3_ns_end.h"
