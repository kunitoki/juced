/*  Allpass filter declaration
 *
 *  Copyright (C) 2000-2006 Jezar at Dreampoint, Teru KAMOGASHIRA
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

#include "freeverb/allpass.hpp"
#include "freeverb/fv3_type_float.h"
#include "freeverb/fv3_ns_start.h"

FV3_(allpass)::FV3_(allpass)()
{
  bufsize = 0;
  bufidx = 0;
}

FV3_(allpass)::FV3_(~allpass)()
{
  if(bufsize != 0)
    {
      delete[] buffer;
    }
}

long FV3_(allpass)::getsize()
{
  return bufsize;
}

void FV3_(allpass)::setsize(long size)
{
#ifdef DEBUG
  fprintf(stderr, "FV3_(allpass)::setsize(%ld)\n", size);
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
      fprintf(stderr, "FV3_(allpass)::setsize(%ld) bad_alloc\n", size);
      delete[] buffer;
      bufsize = 0;
      throw std::bad_alloc();
    }
  bufsize = size;
  bufidx = 0;
}

void FV3_(allpass)::mute()
{
  FV3_(utils)::mute(buffer, bufsize);
}

void FV3_(allpass)::setfeedback(fv3_float_t val) 
{
  feedback = val;
}

fv3_float_t FV3_(allpass)::getfeedback() 
{
  return feedback;
}

fv3_float_t FV3_(allpass)::process(fv3_float_t input)
{
  if(bufsize == 0)
    {
      return input;
    }  
  fv3_float_t bufout = buffer[bufidx];
  buffer[bufidx] = input + (bufout * feedback);
  bufidx ++;
  if(bufidx >= bufsize)
    {
      bufidx = 0;
    }
  return (bufout - input);
}

#include "freeverb/fv3_ns_end.h"
