#ifndef FASTMATH_INCLUDED
#define FASTMATH_INCLUDED

// Copyright (c) 2007, Nils Jonas Norberg, See COPYING.txt for details

#include <math.h>
#include <stdlib.h>
#include "types.h"

#define __forceinline inline

__forceinline float note2freq(float n)
{
	// replace with small table or something
	return 8.17579891563687f * powf( 1.059463094359f , n );
}

// a little collection of fast functions
__forceinline float frand(float amp)
{
	return -amp + amp*(float)rand()/(float)(RAND_MAX>>1);
}

__forceinline float fake_sin(float x) // whole cycle is -2..2 0..1 results in 0..1
{
	return x*(2.f - fabsf(x));
}

__forceinline float fake_sin2(float x) // whole cycle is -1..1 -> 0..-1..0..1..0
{
	return 4.f*x*(1.f - fabsf(x));
}

__forceinline float smooth(float x) // whole cycle is 0..1 -> 0..1
{
	return (3-2*x)*x*x;
}

__forceinline float fast_max(float a, float b)
{
	return .5f * (a+b+fabsf(a-b));
}

__forceinline float fast_min(float a, float b)
{
	return .5f * (a+b-fabsf(a-b));
}

__forceinline void fast_clamp_in_place(float& x, float min, float max)
{
	float x1 = fabsf(x-min);
	float x2 = fabsf(x-max);
	x = x1+min+max-x2;
	x *= 0.5f;
}

__forceinline float fast_clamp_mul2(float x, float min, float max)
{
	float x1 = fabsf(x-min);
	float x2 = fabsf(x-max);
	x = x1+min+max-x2;
	return x;
}

// v = f / sr
__forceinline float FreqToCoef( float v )
{
    v = 1.f - expf( -6.28318530717959f * v );
	fast_clamp_in_place( v, .0001f, .9999f );
    return v;
}

// it's never faster than this, 32bit phase -> [-1.f..1.f)
__forceinline float fast_bipolar( u32 phase )
{
	phase >>= (32 - 23); // shift to mantissa (clears)
	phase |= 0x40000000; // add a hardcoded sign and exponent to make phase be a float in the range [2..4)
	return *((float*)(&phase)) - 3.f; // subtract to make [-1..1)
}

// 32bit phase -> [0.f..1.f)
__forceinline float fast_phase2float( u32 phase )
{
	phase >>= (32 - 23); // shift to mantissa (clears)
	phase |= 0x3F800000; // add a hardcoded sign and exponent to make phase be a float in the range [1..2)
	return *((float*)(&phase)) - 1.f; // subtract to make [0..1)
}

// will convert 0..1023 -> 0..1023
__forceinline u32 fast_ftol1023( float v /* 0..1023 */ )
{
	v += 1024.f; // make range [1024..2047)
	int r = *((int*)(&v));
	r &= ~0xFF800000; // remove exponent
	r >>= (23-10); // had 23 bits of precision, want 10
	return r;
}

#endif // FASTMATH_INCLUDED
