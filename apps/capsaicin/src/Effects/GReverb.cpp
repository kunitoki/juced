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

#include "GReverb.h"


//==============================================================================
void Diffuser::init (unsigned long size, float c)
{
    _size = size;
    _data = new float [size];
    _c = c;
    reset ();
}

void Diffuser::reset (void)
{
    memset (_data, 0, _size * sizeof (float));
    _i = 0;
}

void Diffuser::fini (void)
{
    delete[] _data;
}

//==============================================================================
void QuadFDN::init (unsigned long size)
{
    _size = size;
    for (int j = 0; j < 4; j++)
    {
        _data [j] = new float [size];
        _g [j] = 0;
        _d [j] = 0;
    }
    _c = 1;
    reset ();
}

void QuadFDN::reset (void)
{
    for (int j = 0; j < 4; j++)
    {
        memset (_data [j], 0, _size * sizeof (float));
        _y [j] = 0;
    }
    _i = 0;
}

void QuadFDN::fini (void)
{
    for (int j = 0; j < 4; j++) delete[] _data [j];
}

//==============================================================================
void MTDelay::init (unsigned long size)
{
    _size = size;
    _data = new float [size];
    for (int j = 0; j < 4; j++) _d [j] = 0;
    _c = 1;
    reset ();
}

void MTDelay::reset (void)
{
    memset (_data, 0, _size * sizeof (float));
    for (int j = 0; j < 4; j++) _y [j] = 0;
    _z = 0;
    _i = 0;
}

void MTDelay::fini (void)
{
    delete[] _data;
}


//==============================================================================
GReverb::GReverb (int insertion_, REALTYPE *efxoutl_, REALTYPE *efxoutr_) :
    _roomsize (0.0),
    _revbtime (0.0),
    _ipbandw (0.8),
    _damping (0.2),
    _refllev (0.3),
    _taillev (0.3)
{
    efxoutl = efxoutl_;
    efxoutr = efxoutr_;
    _insertion = insertion_;

    uint n;
    n = (uint)(SAMPLE_RATE * 0.015);
    _dif0.init (n, 0.450);
    _dif1.init (n, 0.450);
    _qfdn.init ((uint)(SAMPLE_RATE * MAX_ROOMSIZE / 340));
    n = (uint)(_qfdn._size * 0.450);
    _del0.init (n);
    _del1.init (n);
    n = (uint)(SAMPLE_RATE * 0.124);
    _dif1L.init ((uint)(n * 0.2137), 0.5);
    _dif2L.init ((uint)(n * 0.3753), 0.5);
    _dif3L.init (n - _dif1L._size - _dif2L._size, 0.5);
    _dif1R.init ((uint)(n * 0.1974), 0.5);
    _dif2R.init ((uint)(n * 0.3526), 0.5);
    _dif3R.init (n - _dif1R._size - _dif2R._size, 0.5);

    set_ipbandw (0.4);
    set_damping (0.1);
    set_roomsize (80.0);
    set_revbtime (3.0);
    set_dryslev (0.0f);
    set_refllev (0.1f);
    set_taillev (0.1f);
    set_volume (1.0f);
}

GReverb::~GReverb ()
{
    _dif0.fini ();
    _dif1.fini ();
    _qfdn.fini ();
    _del0.fini ();;
    _del1.fini ();;
    _dif1L.fini ();
    _dif2L.fini ();
    _dif3L.fini ();
    _dif1R.fini ();
    _dif2R.fini ();
    _dif3R.fini ();
}

//==============================================================================
void GReverb::clean ()
{
    // Clear all delay lines and filter states.
    // Current parameters are preserved.
    _dif0.reset ();
    _dif1.reset ();
    _qfdn.reset ();
    _del0.reset ();
    _del1.reset ();
    _dif1L.reset ();
    _dif2L.reset ();
    _dif3L.reset ();
    _dif1R.reset ();
    _dif2R.reset ();
    _dif3R.reset ();
}

//==============================================================================
void GReverb::out (REALTYPE *smpsl, REALTYPE *smpsr, const int numSamples)
{
    float z, z0, z1;

    for (int i = 0; i < numSamples; i++)
    {
        _del0.process (_dif0.process (smpsl[i] * volume + float_Denormal));
        _del1.process (_dif1.process (smpsr[i] * volume + float_Denormal));
        _qfdn.process (_del0._y, _del1._y);
        z = _taillev * (_qfdn._y [0] + _qfdn._y [1] + _qfdn._y [2] + _qfdn._y [3]);
        z0 = _refllev * (_del0._y [0] - _del0._y [1] + _del0._y [2] - _del0._y [3]);
        z1 = _refllev * (_del1._y [0] - _del1._y [1] + _del1._y [2] - _del1._y [3]);
        efxoutl[i] = _dif3L.process (_dif2L.process (_dif1L.process (z + z0))) + _dryslev * (smpsl[i]);
        efxoutr[i] = _dif3R.process (_dif2R.process (_dif1R.process (z + z1))) + _dryslev * (smpsr[i]);
    }
}

//==============================================================================
void GReverb::setParameter (int npar, uint8 value)
{
    switch (npar)
    {
    case 0: Pvolume = value;
            set_volume (value / 127.0f);
            break;
    case 1: Ppan = value;
            // setpan(value);
            break;
    case 2: Proomsize = value;
            set_roomsize (MIN_ROOMSIZE + (value / 127.0f) * (MAX_ROOMSIZE - MIN_ROOMSIZE));
            break;
    case 3: Prevtime = value;
            set_revbtime (MIN_REVBTIME + (value / 127.0f) * (MAX_REVBTIME - MIN_REVBTIME));
            break;
    case 4: Pbandwidth = value;
            set_ipbandw (0.1 + (value / 127.0f) * 0.9f);
            break;
    case 5: Pdamping = value;
            set_damping ((value / 127.0f) * 0.9f);
            break;
    case 6: Pdrylevel = value;
            set_dryslev (value / 127.0f);
            break;
    case 7: Preflevel = value;
            set_refllev (value / 127.0f);
            break;
    case 8: Ptaillevel = value;
            set_taillev (value / 127.0f);
            break;
    }
}

uint8 GReverb::getParameter (int npar)
{
    switch (npar)
    {
    case 0: return Pvolume;
    case 1: return Ppan;
    case 2: return Proomsize;
    case 3: return Prevtime;
    case 4: return Pbandwidth;
    case 5: return Pdamping;
    case 6: return Pdrylevel;
    case 7: return Preflevel;
    case 8: return Ptaillevel;
    }
    return 0;
}

//==============================================================================
void GReverb::set_volume (float value)
{
    if (_insertion == 0) {
        outvolume = pow (0.01, (1.0-value))*4.0;
        volume = 1.0;
    } else {
        volume = outvolume = value;
        if (volume == 0) clean();
    }
}

void GReverb::set_roomsize (float R)
{
    if (R > MAX_ROOMSIZE) R = MAX_ROOMSIZE;
    if (R < MIN_ROOMSIZE) R = MIN_ROOMSIZE;
    if (fabs (_roomsize - R) < 0.5) return;
    _roomsize = R;
    _qfdn._d [0] = (uint)(SAMPLE_RATE * R / 340.0);
    _qfdn._d [1] = (uint)(_qfdn._d [0] * 0.816490);
    _qfdn._d [2] = (uint)(_qfdn._d [0] * 0.707100);
    _qfdn._d [3] = (uint)(_qfdn._d [0] * 0.632450);

    _del0._d [0] = (uint)(_qfdn._d [0] * 0.100);
    _del0._d [1] = (uint)(_qfdn._d [0] * 0.164);
    _del0._d [2] = (uint)(_qfdn._d [0] * 0.270);
    _del0._d [3] = (uint)(_qfdn._d [0] * 0.443);

    _del1._d [0] = (uint)(_qfdn._d [0] * 0.087);
    _del1._d [1] = (uint)(_qfdn._d [0] * 0.149);
    _del1._d [2] = (uint)(_qfdn._d [0] * 0.256);
    _del1._d [3] = (uint)(_qfdn._d [0] * 0.440);
    set_params ();
}

void GReverb::set_revbtime (float T)
{
    if (T > MAX_REVBTIME) T = MAX_REVBTIME;
    if (T < MIN_REVBTIME) T = MIN_REVBTIME;
    if (fabs (_revbtime - T) < 0.05) return;
    _revbtime = T;
    set_params ();
}

void GReverb::set_ipbandw (float B)
{
    if (B < 0.1) B = 0.1;
    if (B > 1.0) B = 1.0;
    _del1._c = _del0._c = _ipbandw = B;
}

void GReverb::set_damping (float D)
{
    if (D < 0.0) D = 0.0;
    if (D > 0.9) D = 0.9;
    _damping = D;
    _qfdn._c = 1.0 - _damping;
}

void GReverb::set_params ()
{
    double a = pow (0.001, 1.0 / (SAMPLE_RATE * _revbtime));
    for (int j = 0; j < 4; j++)
    {
        _qfdn._g [j] = pow (a, (double)(_qfdn._d [j]));
    }
}

//==============================================================================
void GReverb::setPreset (uint8 presetNumber)
{
}

