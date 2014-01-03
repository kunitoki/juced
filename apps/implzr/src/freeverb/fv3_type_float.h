#ifndef _FV3_TYPE_FLOAT_H
#define _FV3_TYPE_FLOAT_H

#include "config.h"

#ifdef LIBFV3_FLOAT
typedef float fv3_float_t;
#define FV3_(name) name ## _f
#define FFTW_(name) fftwf_ ## name
#define SRC_(name) name ## _f
#else
#ifdef LIBFV3_DOUBLE
typedef double fv3_float_t;
#define FV3_(name) name ## _
#define FFTW_(name) fftw_ ## name
#define SRC_(name) name ## _
#else
#ifdef LIBFV3_LDOUBLE
typedef long double fv3_float_t;
#define FV3_(name) name ## _l
#define FFTW_(name) fftwl_ ## name
#define SRC_(name) name ## _l
#else
#ifdef LIBFV3_DEFAULT
typedef float fv3_float_t;
#define FV3_(name) name
#define FFTW_(name) fftwf_ ## name
#define SRC_(name) name ## _f
#define LIBFV3_FLOAT
#else
#error "No type was defined."
#endif
#endif
#endif
#endif

#endif
