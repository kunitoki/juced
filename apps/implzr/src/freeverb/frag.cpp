/*  FFT impulse fragment square multiplier
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

#include "freeverb/frag.hpp"
#include "freeverb/fv3_type_float.h"
#include "freeverb/fv3_ns_start.h"

FV3_(frag)::FV3_(frag)()
{
  isFFTValid = 0;
  sampleSize = 0;
}

FV3_(frag)::FV3_(~frag)()
{
  freeImpulse();
  freeFFT();
}

void FV3_(frag)::registerImpulse(fv3_float_t * L, fv3_float_t * R, long size)
{
  registerImpulse(L, R, size, FFTW_ESTIMATE);
}

void FV3_(frag)::registerImpulse(fv3_float_t * L, fv3_float_t * R,
				 long size, unsigned fftflags)
{
#ifdef DEBUG
  fprintf(stderr, "FV3_(frag)::registerImpulse(%ld)\n", size);
#endif
  allocImpulse(size);
  //memcpy(impulseL, L, sizeof(fv3_float_t)*size);
  //memcpy(impulseR, R, sizeof(fv3_float_t)*size);
  for(long i = 0;i < size;i ++)
    {
      impulseL[i] = L[i] / (fv3_float_t)(size*2);
      impulseR[i] = R[i] / (fv3_float_t)(size*2);
    }
  FFTW_(plan) planL, planR;
  fv3_float_t * fftIL
    = (fv3_float_t*)FFTW_(malloc)(sizeof(fv3_float_t)*2*size);
  fv3_float_t * fftIR
    = (fv3_float_t*)FFTW_(malloc)(sizeof(fv3_float_t)*2*size);
  planL
    = FFTW_(plan_r2r_1d)(2*size, impulseL, fftIL, FFTW_R2HC, FFTW_ESTIMATE);
  planR
    = FFTW_(plan_r2r_1d)(2*size, impulseR, fftIR, FFTW_R2HC, FFTW_ESTIMATE);
  FFTW_(execute)(planL);
  FFTW_(execute)(planR);
  FFTW_(destroy_plan)(planL);
  FFTW_(destroy_plan)(planR);

  convertR2SIMD(fftIL, fftImpulseL, size);
  convertR2SIMD(fftIR, fftImpulseR, size);

  FFTW_(free)(fftIL);
  FFTW_(free)(fftIR);
  allocFFT(size, fftflags);
}

void FV3_(frag)::convertR2SIMD(fv3_float_t * in, fv3_float_t * out,
			       long halfsize)
{
  long n = halfsize*2;
#ifdef LIBFV3_FLOAT
#ifdef ENABLE_3DNOW
  out[0] = in[0]; // r0
  out[1] = in[1]; // r1
  out[2] = in[n/2]; // r(n/2)
  out[3] = in[n-1]; // i1
  for(long t = 1;t < n/4;t ++)
    {
      out[4*t+0] = in[2*t];
      out[4*t+1] = in[2*t+1];
      out[4*t+2] = in[n-2*t];
      out[4*t+3] = in[n-2*t-1];
    }
  return;
#endif
#ifdef ENABLE_SSE
  out[0] = in[0]; // r0
  out[1] = in[1]; // r1
  out[2] = in[2]; // r2
  out[3] = in[3]; // r3
  out[4+0] = in[n/2]; // r(n/2)
  out[4+1] = in[n-1]; // i1
  out[4+2] = in[n-2]; // i2
  out[4+3] = in[n-3]; // i3
  for(long t = 1;t < n/8;t ++)
    {
      out[8*t+0] = in[4*t];
      out[8*t+1] = in[4*t+1];
      out[8*t+2] = in[4*t+2];
      out[8*t+3] = in[4*t+3];
      out[8*t+4+0] = in[n-4*t];
      out[8*t+4+1] = in[n-4*t-1];
      out[8*t+4+2] = in[n-4*t-2];
      out[8*t+4+3] = in[n-4*t-3];
    }
  return;
#endif
#endif
#ifdef LIBFV3_DOUBLE
#ifdef ENABLE_SSE2
  out[0] = in[0]; // r0
  out[1] = in[1]; // r1
  out[2] = in[n/2]; // r(n/2)
  out[3] = in[n-1]; // i1
  for(long t = 1;t < n/4;t ++)
    {
      out[4*t+0] = in[2*t];
      out[4*t+1] = in[2*t+1];
      out[4*t+2] = in[n-2*t];
      out[4*t+3] = in[n-2*t-1];
    }
  return;
#endif
#endif
  out[0] = in[0];
  out[1] = in[halfsize];
  for(long t = 1;t < halfsize;t ++)
    {
      out[2*t+0] = in[t];
      out[2*t+1] = in[2*halfsize-t];
    }
}

void FV3_(frag)::processR2HC(fv3_float_t * iL, fv3_float_t * iR,
			     fv3_float_t * oL, fv3_float_t * oR)
{
  if(isFFTValid == 0||sampleSize == 0)
    return;
  
  FV3_(utils)::mute(&(fftOrigL[sampleSize]), sampleSize);
  memcpy(fftOrigL, iL, sizeof(fv3_float_t)*sampleSize);
  FFTW_(execute)(planOrigL);
  convertR2SIMD(fftOrigL, oL, sampleSize);

  FV3_(utils)::mute(&(fftOrigR[sampleSize]), sampleSize);
  memcpy(fftOrigR, iR, sizeof(fv3_float_t)*sampleSize);
  FFTW_(execute)(planOrigR);
  convertR2SIMD(fftOrigR, oR, sampleSize);
}

void FV3_(frag)::convertSIMD2R(fv3_float_t * in, fv3_float_t * out,
			       long halfsize)
{
  long n = halfsize*2;
#ifdef LIBFV3_FLOAT
#ifdef ENABLE_3DNOW
  out[0] = in[0]; // r0
  out[1] = in[1]; // r1
  out[n/2] = in[2]; // r(n/2)
  out[n-1] = in[3]; // i1
  for(long t = 1;t < n/4;t ++)
    {
      out[2*t] = in[4*t+0];
      out[2*t+1] = in[4*t+1];
      out[n-2*t] = in[4*t+2];
      out[n-2*t-1] = in[4*t+3];
    }
  return;
#endif
#ifdef ENABLE_SSE
  out[0] = in[0]; // r0
  out[1] = in[1]; // r1
  out[2] = in[2]; // r2
  out[3] = in[3]; // r3
  out[n/2] = in[4+0]; // r(n/2)
  out[n-1] = in[4+1]; // i1
  out[n-2] = in[4+2]; // i2
  out[n-3] = in[4+3]; // i3
  for(long t = 1;t < n/8;t ++)
    {
      out[4*t] = in[8*t+0];
      out[4*t+1] = in[8*t+1];
      out[4*t+2] = in[8*t+2];
      out[4*t+3] = in[8*t+3];
      out[n-4*t] = in[8*t+4+0];
      out[n-4*t-1] = in[8*t+4+1];
      out[n-4*t-2] = in[8*t+4+2];
      out[n-4*t-3] = in[8*t+4+3];
    }
  return;
#endif
#endif

#ifdef LIBFV3_DOUBLE
#ifdef ENABLE_SSE2
  out[0] = in[0]; // r0
  out[1] = in[1]; // r1
  out[n/2] = in[2]; // r(n/2)
  out[n-1] = in[3]; // i1
  for(long t = 1;t < n/4;t ++)
    {
      out[2*t] = in[4*t+0];
      out[2*t+1] = in[4*t+1];
      out[n-2*t] = in[4*t+2];
      out[n-2*t-1] = in[4*t+3];
    }
  return;
#endif
#endif
  out[0] = in[0];
  out[halfsize] = in[1];
  for(long t = 1;t < halfsize;t ++)
    {
      out[t] = in[2*t+0];
      out[2*halfsize-t] = in[2*t+1];
    }
}

void FV3_(frag)::processHC2R(fv3_float_t * iL, fv3_float_t * iR,
			     fv3_float_t * oL, fv3_float_t * oR)
{
  if(isFFTValid == 0||sampleSize == 0)
      return;

  convertSIMD2R(iL, fftOrigL, sampleSize);
  FFTW_(execute)(planRevL);
  convertSIMD2R(iR, fftOrigR, sampleSize);
  FFTW_(execute)(planRevR);
  for(long i = 0;i < sampleSize*2;i ++)
    {
      //oL[i] += fftOrigL[i] / (fv3_float_t)(sampleSize*2);
      oL[i] += fftOrigL[i];
      //oR[i] += fftOrigR[i] / (fv3_float_t)(sampleSize*2);
      oR[i] += fftOrigR[i];
    }
}

void FV3_(frag)::multMONO(fv3_float_t * iL, fv3_float_t * fL,
			  fv3_float_t * oL, long count)
{
#ifdef LIBFV3_FLOAT
#ifdef ENABLE_3DNOW
  __asm__ __volatile__ ("femms");
  __asm__ __volatile__ ("multMONO_3dnow__: \n\t"
			"prefetch 0x60(%1) \n\t"
			"movq  (%1), %%mm0 \n\t"
			"movq  %%mm0, %%mm2 \n\t"
			"prefetch 0x60(%2) \n\t"
			"movq  (%2), %%mm1 \n\t"
			"pfmul %%mm1, %%mm0 \n\t"
			"movq  0x8(%1), %%mm4 \n\t"
			"movq  %%mm4, %%mm3 \n\t"
			"pfmul %%mm1, %%mm3 \n\t"
			"movq  0x8(%2), %%mm5 \n\t"
			"pfmul %%mm5, %%mm4 \n\t"
			"pfsub %%mm4, %%mm0 \n\t"
			"pfmul %%mm5, %%mm2 \n\t"
			"prefetchw 0x60(%0) \n\t"
			"pfadd (%0), %%mm0 \n\t"
			"movq  %%mm0, (%0) \n\t"
			"pfadd %%mm3, %%mm2 \n\t"
			"pfadd 0x8(%0), %%mm2 \n\t"
			"movq  %%mm2, 0x8(%0) \n\t"
			"add   $0x10, %0 \n\t"
			"add   $0x10, %1 \n\t"
			"add   $0x10, %2 \n\t"
                        "dec   %3 \n\t"
			"jne   multMONO_3dnow__"
			:
			: "q"(oL), "q"(iL), "q"(fL), "r"(count)
			:);
  __asm__ __volatile__ ("femms");
  return;
#endif
#ifdef ENABLE_SSE
  __asm__ __volatile__ ("multMONO_sse__: \n\t"
			"prefetchnta 0x60(%1) \n\t"
			"movaps (%1), %%xmm0 \n\t"
			"movaps %%xmm0, %%xmm2 \n\t"
			"prefetchnta 0x60(%2) \n\t"
			"movaps (%2), %%xmm1 \n\t"
			"mulps  %%xmm1, %%xmm0 \n\t"
			"movaps 0x10(%1), %%xmm4 \n\t"
			"movaps %%xmm4, %%xmm3 \n\t"
			"mulps  %%xmm1, %%xmm3 \n\t"
			"movaps 0x10(%2), %%xmm5 \n\t"
			"mulps  %%xmm5, %%xmm4 \n\t"
			"subps  %%xmm4, %%xmm0 \n\t"
			"mulps  %%xmm5, %%xmm2 \n\t"
			"prefetcht2 0x60(%0) \n\t"
			"addps  (%0), %%xmm0 \n\t"
			"movaps %%xmm0, (%0) \n\t"
			"addps  %%xmm3, %%xmm2 \n\t"
			"addps  0x10(%0), %%xmm2 \n\t"
			"movaps %%xmm2, 0x10(%0) \n\t"
			"add    $0x20, %0 \n\t"
			"add    $0x20, %1 \n\t"
			"add    $0x20, %2 \n\t"
                        "dec    %3 \n\t"
			"jne    multMONO_sse__"
			:
			: "q"(oL), "q"(iL), "q"(fL), "r"(count)
			:);
  return;
#endif
#endif

#ifdef LIBFV3_DOUBLE
#ifdef ENABLE_SSE2
  __asm__ __volatile__ ("multMONO_sse2__: \n\t"
			"prefetchnta 0x60(%1) \n\t"
			"movapd (%1), %%xmm0 \n\t"
			"movapd %%xmm0, %%xmm2 \n\t"
			"prefetchnta 0x60(%2) \n\t"
			"movapd (%2), %%xmm1 \n\t"
			"mulpd  %%xmm1, %%xmm0 \n\t"
			"movapd 0x10(%1), %%xmm4 \n\t"
			"movapd %%xmm4, %%xmm3 \n\t"
			"mulpd  %%xmm1, %%xmm3 \n\t"
			"movapd 0x10(%2), %%xmm5 \n\t"
			"mulpd  %%xmm5, %%xmm4 \n\t"
			"subpd  %%xmm4, %%xmm0 \n\t"
			"mulpd  %%xmm5, %%xmm2 \n\t"
			"prefetcht2 0x60(%0) \n\t"
			"addpd  (%0), %%xmm0 \n\t"
			"movapd %%xmm0, (%0) \n\t"
			"addpd  %%xmm3, %%xmm2 \n\t"
			"addpd  0x10(%0), %%xmm2 \n\t"
			"movapd %%xmm2, 0x10(%0) \n\t"
			"add    $0x20, %0 \n\t"
			"add    $0x20, %1 \n\t"
			"add    $0x20, %2 \n\t"
                        "dec    %3 \n\t"
			"jne    multMONO_sse2__"
			:
			: "q"(oL), "q"(iL), "q"(fL), "r"(count)
			:);
  return;
#endif
#endif
  // normal FPU code
  for(long i = 0;i < count;i ++)
    {
      fv3_float_t e = iL[2*i+0];
      fv3_float_t d = iL[2*i+1];
      fv3_float_t f = fL[2*i+0];
      fv3_float_t g = fL[2*i+1];
      oL[2*i+0] += e*f - d*g;
      oL[2*i+1] += e*g + f*d;
    }
  return;
}

void FV3_(frag)::processMULT(fv3_float_t * iL, fv3_float_t * iR,
			     fv3_float_t * oL, fv3_float_t * oR)
{
  if(isFFTValid == 0||sampleSize == 0)
    return;
  
#ifdef LIBFV3_FLOAT
#ifdef ENABLE_3DNOW
  {
    fv3_float_t tL0 = oL[0] + iL[0] * fftImpulseL[0];
    fv3_float_t tL2 = oL[2] + iL[2] * fftImpulseL[2];
    fv3_float_t tR0 = oR[0] + iR[0] * fftImpulseR[0];
    fv3_float_t tR2 = oR[2] + iR[2] * fftImpulseR[2];
#pragma omp parallel
#pragma omp sections
#pragma omp section
    multMONO(iL, fftImpulseL, oL, sampleSize/2);
#pragma omp section
    multMONO(iR, fftImpulseR, oR, sampleSize/2);
#pragma omp barrier
    oL[0] = tL0;
    oL[2] = tL2;
    oR[0] = tR0;
    oR[2] = tR2;
    return;
  }
#endif
#ifdef ENABLE_SSE
  {
    fv3_float_t tL0 = oL[0] + iL[0] * fftImpulseL[0];
    fv3_float_t tL4 = oL[4] + iL[4] * fftImpulseL[4];
    fv3_float_t tR0 = oR[0] + iR[0] * fftImpulseR[0];
    fv3_float_t tR4 = oR[4] + iR[4] * fftImpulseR[4];
#pragma omp parallel
#pragma omp sections
#pragma omp section
    multMONO(iL, fftImpulseL, oL, sampleSize/4);
#pragma omp section
    multMONO(iR, fftImpulseR, oR, sampleSize/4);
#pragma omp barrier
    oL[0] = tL0;
    oL[4] = tL4;
    oR[0] = tR0;
    oR[4] = tR4;
    return;
  }
#endif
#endif
  
#ifdef LIBFV3_DOUBLE
#ifdef ENABLE_SSE2
  {
    fv3_float_t tL0 = oL[0] + iL[0] * fftImpulseL[0];
    fv3_float_t tL2 = oL[2] + iL[2] * fftImpulseL[2];
    fv3_float_t tR0 = oR[0] + iR[0] * fftImpulseR[0];
    fv3_float_t tR2 = oR[2] + iR[2] * fftImpulseR[2];
#pragma omp parallel
#pragma omp sections
#pragma omp section
    multMONO(iL, fftImpulseL, oL, sampleSize/2);
#pragma omp section
    multMONO(iR, fftImpulseR, oR, sampleSize/2);
#pragma omp barrier
    oL[0] = tL0;
    oL[2] = tL2;
    oR[0] = tR0;
    oR[2] = tR2;
    return;
  }
#endif
#endif

  // normal FPU code  
  {
    fv3_float_t tL0 = oL[0] + iL[0] * fftImpulseL[0];
    fv3_float_t tL1 = oL[1] + iL[1] * fftImpulseL[1];
    fv3_float_t tR0 = oR[0] + iR[0] * fftImpulseR[0];
    fv3_float_t tR1 = oR[1] + iR[1] * fftImpulseR[1];
#pragma omp parallel
#pragma omp sections
#pragma omp section
    multMONO(iL, fftImpulseL, oL, sampleSize);
#pragma omp section
    multMONO(iR, fftImpulseR, oR, sampleSize);
#pragma omp barrier
    oL[0] = tL0;
    oL[1] = tL1;
    oR[0] = tR0;
    oR[1] = tR1;
    return;
  }
}

long FV3_(frag)::getSampleSize()
{
  return sampleSize;
}

void FV3_(frag)::allocImpulse(long size)
{
  freeImpulse();
  impulseL = (fv3_float_t*)FFTW_(malloc)(sizeof(fv3_float_t)*2*size);
  impulseR = (fv3_float_t*)FFTW_(malloc)(sizeof(fv3_float_t)*2*size);
  fftImpulseL = (fv3_float_t*)FFTW_(malloc)(sizeof(fv3_float_t)*2*size);
  fftImpulseR = (fv3_float_t*)FFTW_(malloc)(sizeof(fv3_float_t)*2*size);
  if(fftImpulseL == NULL||fftImpulseR == NULL||
     impulseL == NULL||impulseR == NULL)
    {
      fprintf(stderr, "FV3_(frag)::allocImpulse(%ld) fftw_malloc!\n", size);
      FFTW_(free)(impulseL);
      FFTW_(free)(impulseR);
      FFTW_(free)(fftImpulseL);
      FFTW_(free)(fftImpulseR);
      throw std::bad_alloc();
    }
  FV3_(utils)::mute(impulseL, size*2);
  FV3_(utils)::mute(impulseR, size*2);
  FV3_(utils)::mute(fftImpulseL, size*2);
  FV3_(utils)::mute(fftImpulseR, size*2);
  sampleSize = size;
}

void FV3_(frag)::freeImpulse()
{
  if(sampleSize != 0)
    {
      FFTW_(free)(impulseL);
      FFTW_(free)(impulseR);
      FFTW_(free)(fftImpulseL);
      FFTW_(free)(fftImpulseR);
      sampleSize = 0;
    }
}

void FV3_(frag)::allocFFT(long size, unsigned fftflags)
{
  freeFFT();
  fftOrigL = (fv3_float_t*)FFTW_(malloc)(sizeof(fv3_float_t)*2*size);
  fftOrigR = (fv3_float_t*)FFTW_(malloc)(sizeof(fv3_float_t)*2*size);
  if(fftOrigL == NULL||fftOrigR == NULL)
    {
      fprintf(stderr, "FV3_(frag)::allocFFT(%ld) malloc!\n", size);
      FFTW_(free)(fftOrigL);
      FFTW_(free)(fftOrigR);
      throw std::bad_alloc();
    }
  planOrigL
    = FFTW_(plan_r2r_1d)(2*size, fftOrigL, fftOrigL, FFTW_R2HC, fftflags);
  planOrigR
    = FFTW_(plan_r2r_1d)(2*size, fftOrigR, fftOrigR, FFTW_R2HC, fftflags);
  planRevL
    = FFTW_(plan_r2r_1d)(2*size, fftOrigL, fftOrigL, FFTW_HC2R, fftflags);
  planRevR
    = FFTW_(plan_r2r_1d)(2*size, fftOrigR, fftOrigR, FFTW_HC2R, fftflags);
  FV3_(utils)::mute(fftOrigL, size*2);
  FV3_(utils)::mute(fftOrigR, size*2);
  isFFTValid = 1;
}

void FV3_(frag)::freeFFT()
{
  if(isFFTValid != 0)
    {
      FFTW_(destroy_plan)(planRevL);
      FFTW_(destroy_plan)(planRevR);
      FFTW_(free)(fftOrigL);
      FFTW_(free)(fftOrigR);
      FFTW_(destroy_plan)(planOrigL);
      FFTW_(destroy_plan)(planOrigR);
      isFFTValid = 0;
    }
}

#include "freeverb/fv3_ns_end.h"
