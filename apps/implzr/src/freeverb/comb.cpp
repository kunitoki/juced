/*  Comb filter implementation
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

#include "freeverb/comb.hpp"
#include "freeverb/fv3_type_float.h"
#include "freeverb/fv3_ns_start.h"

FV3_(comb)::FV3_(comb)()
{
  bufsize = 0;
  filterstore = 0;
  bufidx = 0;
}

FV3_(comb)::FV3_(~comb)()
{
  if(bufsize != 0)
    {
      delete[] buffer;
    }
}

long FV3_(comb)::getsize()
{
  return bufsize;
}

void FV3_(comb)::setsize(long size)
{
#ifdef DEBUG
  fprintf(stderr, "FV3_(comb)::setsize(%ld)\n", size);
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
      fprintf(stderr, "FV3_(comb)::setsize(%ld) bad_alloc\n", size);
      delete[] buffer;
      bufsize = 0;
      throw std::bad_alloc();
    }
  bufsize = size;
  bufidx = 0;
}

void FV3_(comb)::mute()
{
  FV3_(utils)::mute(buffer, bufsize);
}

void FV3_(comb)::setdamp(fv3_float_t val) 
{
  damp1 = val; 
  damp2 = 1-val;
}

fv3_float_t FV3_(comb)::getdamp() 
{
  return damp1;
}

void FV3_(comb)::setfeedback(fv3_float_t val) 
{
  feedback = val;
}

fv3_float_t FV3_(comb)::getfeedback() 
{
  return feedback;
}

fv3_float_t FV3_(comb)::process(fv3_float_t input)
{
  if(bufsize == 0)
    {
      return input;
    }
  fv3_float_t output = buffer[bufidx];
  filterstore = (output * damp2) + (filterstore * damp1);
  buffer[bufidx] = input + (filterstore * feedback);
  bufidx ++;
  if(bufidx >= bufsize)
    {
      bufidx = 0;
    }
  return output;
}

#include "freeverb/fv3_ns_end.h"
