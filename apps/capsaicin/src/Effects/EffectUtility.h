/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2007 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2007 by Julian Storer.

 ------------------------------------------------------------------------------

 JUCE and JUCETICE can be redistributed and/or modified under the terms of
 the GNU Lesser General Public License, as published by the Free Software
 Foundation; either version 2 of the License, or (at your option) any later
 version.

 JUCE and JUCETICE are distributed in the hope that they will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with JUCE and JUCETICE; if not, visit www.gnu.org/licenses or write to
 Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 Boston, MA 02111-1307 USA

 ==============================================================================

   @author  Paul Nasca
   @tweaker Lucio Asnaghi

 ==============================================================================
*/

#ifndef __JUCETICE_XSYNTHEFFECTUTILITY_HEADER__
#define __JUCETICE_XSYNTHEFFECTUTILITY_HEADER__

//==============================================================================
typedef union {
        float f;
        int32_t i;
} ls_pcast32;

#define f_round(f) lrintf(f)

static inline float flush_to_zero(float f)
{
    ls_pcast32 v;

    v.f = f;

    // original: return (v.i & 0x7f800000) == 0 ? 0.0f : f;
    // version from Tim Blechmann
    return (v.i & 0x7f800000) < 0x08000000 ? 0.0f : f;
}

static inline void round_to_zero(volatile float *f)
{
    *f += 1e-18;
    *f -= 1e-18;
}

/* A set of branchless clipping operations from Laurent de Soras */

static inline float f_max(float x, float a)
{
    x -= a;
    x += fabs(x);
    x *= 0.5;
    x += a;

    return x;
}

static inline float f_min(float x, float b)
{
    x = b - x;
    x += fabs(x);
    x *= 0.5;
    x = b - x;

    return x;
}

static inline float f_clamp(float x, float a, float b)
{
    const float x1 = fabs(x - a);
    const float x2 = fabs(x - b);

    x = x1 + a + b;
    x -= x2;
    x *= 0.5;

    return x;
}

static inline int f_trunc (float f)
{
    return f_round(floorf(f));
}

static inline float lin_interp (const float f,
                                const float a,
                                const float b)
{
    return((a) + (f) * ((b) - (a)));
}

static inline float cube_interp (const float fr,
                                 const float inm1,
                                 const float in,
                                 const float inp1,
                                 const float inp2)
{
    return in + 0.5f * fr * (inp1 - inm1 +
     fr * (4.0f * inp1 + 2.0f * inm1 - 5.0f * in - inp2 +
     fr * (3.0f * (in - inp1) - inm1 + inp2)));
}


//==============================================================================
#define RMSSIZE 64

typedef struct {
        float        buffer[RMSSIZE];
        unsigned int pos;
        float        sum;
} rms_env;

static inline rms_env * rms_env_new ()
{
    return (rms_env *)calloc(1, sizeof(rms_env));
}

static inline void rms_env_free (rms_env *r)
{
    free(r);
}

static inline void rms_env_reset (rms_env *r)
{
    for (int i = 0; i < RMSSIZE; i++)
        r->buffer[i] = 0.0f;

    r->pos = 0;
    r->sum = 0.0f;
}

static inline float rms_env_process (rms_env *r, const float x)
{
    r->sum -= r->buffer[r->pos];
    r->sum += x;
    r->buffer[r->pos] = x;
    r->pos = (r->pos + 1) & (RMSSIZE - 1);

    return sqrt (r->sum / (float)RMSSIZE);
}


//==============================================================================
#define DB_TABLE_SIZE    1024
#define DB_MIN           -60.0f
#define DB_MAX           24.0f
#define LIN_TABLE_SIZE   1024
#define LIN_MIN          0.0000000002f
#define LIN_MAX          9.0f
#define DB_DEFAULT_CUBE

#ifdef DB_DEFAULT_CUBE
  #define db2lin(a) f_db2lin_cube(a)
  #define lin2db(a) f_lin2db_cube(a)
#else
  #define db2lin(a) f_db2lin_lerp(a)
  #define lin2db(a) f_lin2db_lerp(a)
#endif

static float db_data[DB_TABLE_SIZE];
static float lin_data[LIN_TABLE_SIZE];

static inline void db_init()
{
    unsigned int i;

    for (i=0; i<LIN_TABLE_SIZE; i++) {
        lin_data[i] = powf(10.0f, ((DB_MAX - DB_MIN) *
            (float)i/(float)LIN_TABLE_SIZE + DB_MIN) / 20.0f);
    }

    for (i=0; i<DB_TABLE_SIZE; i++) {
        db_data[i] = 20.0f * log10f((LIN_MAX - LIN_MIN) *
            (float)i/(float)DB_TABLE_SIZE + LIN_MIN);
    }
}

static inline float f_db2lin_cube(float db)
{
    float scale = (db - DB_MIN) * (float)LIN_TABLE_SIZE / (DB_MAX - DB_MIN);
    int base = f_round(scale - 0.5f);
    float ofs = scale - base;

    if (base < 1) {
        return 0.0f;
    } else if (base > LIN_TABLE_SIZE - 3) {
        return lin_data[LIN_TABLE_SIZE - 2];
    }
    return cube_interp(ofs, lin_data[base-1], lin_data[base], lin_data[base+1], lin_data[base+2]);
}

static inline float f_db2lin_lerp(float db)
{
    float scale = (db - DB_MIN) * (float)LIN_TABLE_SIZE / (DB_MAX - DB_MIN);
    int base = f_round(scale - 0.5f);
    float ofs = scale - base;

    if (base < 1) {
        return 0.0f;
    } else if (base > LIN_TABLE_SIZE - 3) {
        return lin_data[LIN_TABLE_SIZE - 2];
    }
    return (1.0f - ofs) * lin_data[base] + ofs * lin_data[base+1];
}

static inline float f_lin2db_cube(float lin)
{
    float scale = (lin - LIN_MIN) * (float)DB_TABLE_SIZE / (LIN_MAX - LIN_MIN);
    int base = f_round(scale - 0.5f);
    float ofs = scale - base;

    if (base < 2) {
        return db_data[2] * scale * 0.5f - 23 * (2.0f - scale);
    } else if (base > DB_TABLE_SIZE - 3) {
        return db_data[DB_TABLE_SIZE - 2];
    }
    return cube_interp(ofs, db_data[base-1], db_data[base], db_data[base+1], db_data[base+2]);
}

static inline float f_lin2db_lerp(float lin)
{
    float scale = (lin - LIN_MIN) * (float)DB_TABLE_SIZE / (LIN_MAX - LIN_MIN);
    int base = f_round(scale - 0.5f);
    float ofs = scale - base;

    if (base < 2) {
        return db_data[2] * scale * 0.5f - 23.0f * (2.0f - scale);
    } else if (base > DB_TABLE_SIZE - 2) {
        return db_data[DB_TABLE_SIZE - 1];
    }
    return (1.0f - ofs) * db_data[base] + ofs * db_data[base+1];
}


#endif
