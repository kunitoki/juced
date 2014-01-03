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
*/

#ifndef __JUCETICE_XSYNTHG2REVERB_HEADER__
#define __JUCETICE_XSYNTHG2REVERB_HEADER__

#include "Effect.h"


class Diffuser
{
private:

    friend class GReverb;

    void init (unsigned long size, float c);
    void reset (void);
    void fini (void);

    float process (float x)
    {
        float w;

        w = x - _c * _data [_i];
        x = _data [_i] + _c * w;
        _data [_i] = w;
        if (++_i == _size) _i = 0;
        return x;
    }

    float          *_data;
    unsigned long   _size;
    unsigned long   _i;      // sample index
    float           _c;      // feedback
};


class QuadFDN
{
private:

    friend class GReverb;

    void init (unsigned long size);
    void reset (void);
    void fini (void);

    void process (float *x0, float *x1)
    {
        int   j;
        long  k;

        for (j = 0; j < 4; j++)
        {
            k = _i - _d [j];
            if (k < 0) k += _size;
            _y [j] += _c * (_g [j] * _data [j][k] - _y [j]);
        }
        _data [0][_i] = x0 [0] + x1 [0] + 0.5 * ( _y [0] + _y [1] - _y [2] - _y [3]);
        _data [1][_i] = x0 [1] + x1 [1] + 0.5 * ( _y [0] - _y [1] - _y [2] + _y [3]);
        _data [2][_i] = x0 [2] + x1 [2] + 0.5 * (-_y [0] + _y [1] - _y [2] + _y [3]);
        _data [3][_i] = x0 [3] + x1 [3] + 0.5 * ( _y [0] + _y [1] + _y [2] + _y [3]);
        if (++_i == _size) _i = 0;
    }

    float          *_data [4];
    unsigned long   _size;
    float           _g [4];  // gain
    float           _y [4];  // filtered output
    unsigned long   _d [4];  // delay
    unsigned long   _i;      // input index
    float           _c;      // damping
};


class MTDelay
{
private:

    friend class GReverb;

    void init (unsigned long size);
    void reset (void);
    void fini (void);

    void process (float x)
    {
        int  j;
        long k;

        for (j = 0; j < 4; j++)
        {
            k = _i - _d [j];
            if (k < 0) k += _size;
            _y [j] = _data [k];
        }
        _z += _c * (x - _z);
        _data [_i] = _z;
        if (++_i == _size) _i = 0;
    }

    float          *_data;
    unsigned long   _size;
    float           _y [4];  // output
    unsigned long   _d [4];  // delay
    unsigned long   _i;      // input index
    float           _c;      // damping;
    float           _z;      // filter state
} ;



class GReverb : public Effect
{
public:

    enum
    {
        MIN_ROOMSIZE = 2,
        MAX_ROOMSIZE = 180,
        MIN_REVBTIME = 1,
        MAX_REVBTIME = 20
    };

    GReverb (int insertion, REALTYPE *efxoutl_, REALTYPE *efxoutr_);
    ~GReverb ();

    void setPreset (uint8 presetNumber);
    void setParameter (int parameterNumber, uint8 parameterValue);
    uint8 getParameter (int parameterNumber);
    void out (REALTYPE *smpsl, REALTYPE *smpsr, const int numSamples);
    void clean ();

private:

    // preset parameters
    uint8 Pvolume;
    uint8 Ppan;
    uint8 Proomsize;
    uint8 Prevtime;
    uint8 Pbandwidth;
    uint8 Pdamping;
    uint8 Pdrylevel;
    uint8 Preflevel;
    uint8 Ptaillevel;

    // setters
    void set_volume (float value);
    void set_roomsize (float roomsize);
    void set_revbtime (float revbtime);
    void set_ipbandw (float ipbandw);
    void set_damping (float damping);
    void set_dryslev (float refllev) { _dryslev = refllev; }
    void set_refllev (float refllev) { _refllev = refllev; }
    void set_taillev (float taillev) { _taillev = taillev; }
    void set_params ();

    // real parameters
    int            _insertion;
    float          _roomsize;
    float          _revbtime;
    float          _ipbandw;
    float          _damping;
    float          _dryslev;
    float          _refllev;
    float          _taillev;

    QuadFDN        _qfdn;
    MTDelay        _del0, _del1;
    Diffuser       _dif0, _dif1;
    Diffuser       _dif1L, _dif2L, _dif3L;
    Diffuser       _dif1R, _dif2R, _dif3R;
};


#endif
