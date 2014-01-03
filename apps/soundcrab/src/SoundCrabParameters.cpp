/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2004 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2004 by Julian Storer.

 ------------------------------------------------------------------------------

 JUCE and JUCETICE can be redistributed and/or modified under the terms of
 the GNU General Public License, as published by the Free Software Foundation;
 either version 2 of the License, or (at your option) any later version.

 JUCE and JUCETICE are distributed in the hope that they will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with JUCE and JUCETICE; if not, visit www.gnu.org/licenses or write to
 Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 Boston, MA 02111-1307 USA

 ------------------------------------------------------------------------------

 If you'd like to release a closed-source product which uses JUCE, commercial
 licenses are also available: visit www.rawmaterialsoftware.com/juce for
 more information.

 ==============================================================================
*/
#include "SoundCrabParameters.h"
#include "SoundCrabPlugin.h"

#define SOUNDCRAB_INVERT_ENVELOPES 1

/*
        // number/name             init  scale         min        max         def
        { GEN_STARTADDROFS,           1,     1,       0.0f,     1e10f,       0.0f },
        { GEN_ENDADDROFS,             1,     1,     -1e10f,      0.0f,       0.0f },
        { GEN_STARTLOOPADDROFS,       1,     1,     -1e10f,     1e10f,       0.0f },
        { GEN_ENDLOOPADDROFS,         1,     1,     -1e10f,     1e10f,       0.0f },
        { GEN_STARTADDRCOARSEOFS,     0,     1,       0.0f,     1e10f,       0.0f },
        { GEN_MODLFOTOPITCH,          1,     2,  -12000.0f,  12000.0f,       0.0f },
        { GEN_VIBLFOTOPITCH,          1,     2,  -12000.0f,  12000.0f,       0.0f },
        { GEN_MODENVTOPITCH,          1,     2,  -12000.0f,  12000.0f,       0.0f },
        { GEN_FILTERFC,               1,     2,    1500.0f,  13500.0f,   13500.0f },
        { GEN_FILTERQ,                1,     1,       0.0f,    960.0f,       0.0f },
        { GEN_MODLFOTOFILTERFC,       1,     2,  -12000.0f,  12000.0f,       0.0f },
        { GEN_MODENVTOFILTERFC,       1,     2,  -12000.0f,  12000.0f,       0.0f },
        { GEN_ENDADDRCOARSEOFS,       0,     1,     -1e10f,      0.0f,       0.0f },
        { GEN_MODLFOTOVOL,            1,     1,    -960.0f,    960.0f,       0.0f },
        { GEN_UNUSED1,                0,     0,       0.0f,      0.0f,       0.0f },
        { GEN_CHORUSSEND,             1,     1,       0.0f,   1000.0f,       0.0f },
        { GEN_REVERBSEND,             1,     1,       0.0f,   1000.0f,       0.0f },
        { GEN_PAN,                    1,     1,    -500.0f,    500.0f,       0.0f },
        { GEN_UNUSED2,                0,     0,       0.0f,      0.0f,       0.0f },
        { GEN_UNUSED3,                0,     0,       0.0f,      0.0f,       0.0f },
        { GEN_UNUSED4,                0,     0,       0.0f,      0.0f,       0.0f },
        { GEN_MODLFODELAY,            1,     2,  -12000.0f,   5000.0f,  -12000.0f },
        { GEN_MODLFOFREQ,             1,     4,  -16000.0f,   4500.0f,       0.0f },
        { GEN_VIBLFODELAY,            1,     2,  -12000.0f,   5000.0f,  -12000.0f },
        { GEN_VIBLFOFREQ,             1,     4,  -16000.0f,   4500.0f,       0.0f },
        { GEN_MODENVDELAY,            1,     2,  -12000.0f,   5000.0f,  -12000.0f },
        { GEN_MODENVATTACK,           1,     2,  -12000.0f,   8000.0f,  -12000.0f },
        { GEN_MODENVHOLD,             1,     2,  -12000.0f,   5000.0f,  -12000.0f },
        { GEN_MODENVDECAY,            1,     2,  -12000.0f,   8000.0f,  -12000.0f },
        { GEN_MODENVSUSTAIN,          0,     1,       0.0f,   1000.0f,       0.0f },
        { GEN_MODENVRELEASE,          1,     2,  -12000.0f,   8000.0f,  -12000.0f },
        { GEN_KEYTOMODENVHOLD,        0,     1,   -1200.0f,   1200.0f,       0.0f },
        { GEN_KEYTOMODENVDECAY,       0,     1,   -1200.0f,   1200.0f,       0.0f },
        { GEN_VOLENVDELAY,            1,     2,  -12000.0f,   5000.0f,  -12000.0f },
        { GEN_VOLENVATTACK,           1,     2,  -12000.0f,   8000.0f,  -12000.0f },
        { GEN_VOLENVHOLD,             1,     2,  -12000.0f,   5000.0f,  -12000.0f },
        { GEN_VOLENVDECAY,            1,     2,  -12000.0f,   8000.0f,  -12000.0f },
        { GEN_VOLENVSUSTAIN,          0,     1,       0.0f,   1440.0f,       0.0f },
        { GEN_VOLENVRELEASE,          1,     2,  -12000.0f,   8000.0f,  -12000.0f },
        { GEN_KEYTOVOLENVHOLD,        0,     1,   -1200.0f,   1200.0f,       0.0f },
        { GEN_KEYTOVOLENVDECAY,       0,     1,   -1200.0f,   1200.0f,       0.0f },
        { GEN_INSTRUMENT,             0,     0,       0.0f,      0.0f,       0.0f },
        { GEN_RESERVED1,              0,     0,       0.0f,      0.0f,       0.0f },
        { GEN_KEYRANGE,               0,     0,       0.0f,    127.0f,       0.0f },
        { GEN_VELRANGE,               0,     0,       0.0f,    127.0f,       0.0f },
        { GEN_STARTLOOPADDRCOARSEOFS, 0,     1,     -1e10f,     1e10f,       0.0f },
        { GEN_KEYNUM,                 1,     0,       0.0f,    127.0f,      -1.0f },
        { GEN_VELOCITY,               1,     1,       0.0f,    127.0f,      -1.0f },
        { GEN_ATTENUATION,            1,     1,       0.0f,   1440.0f,       0.0f },
        { GEN_RESERVED2,              0,     0,       0.0f,      0.0f,       0.0f },
        { GEN_ENDLOOPADDRCOARSEOFS,   0,     1,     -1e10f,     1e10f,       0.0f },
        { GEN_COARSETUNE,             0,     1,    -120.0f,    120.0f,       0.0f },
        { GEN_FINETUNE,               0,     1,     -99.0f,     99.0f,       0.0f },
        { GEN_SAMPLEID,               0,     0,       0.0f,      0.0f,       0.0f },
        { GEN_SAMPLEMODE,             0,     0,       0.0f,      0.0f,       0.0f },
        { GEN_RESERVED3,              0,     0,       0.0f,      0.0f,       0.0f },
        { GEN_SCALETUNE,              0,     1,       0.0f,   1200.0f,     100.0f },
        { GEN_EXCLUSIVECLASS,         0,     0,       0.0f,      0.0f,       0.0f },
        { GEN_OVERRIDEROOTKEY,        1,     0,       0.0f,    127.0f,      -1.0f },
        { GEN_PITCH,                  1,     0,       0.0f,    127.0f,       0.0f }
};
*/


//==============================================================================
SoundCrabParameters::SoundCrabParameters (SoundCrabPlugin* plugin_)
  : plugin (plugin_),
    synth (&plugin->synth)
{
    // global parameter publishing
    registerGlobalParameters ();

    // something is going wrong with your parameters
    // jassert (TOTAL_PARAMETERS == plugin->parameterManager.getNumParameters());

    // initial preset
    zeromem (params, TOTAL_PARAMETERS * sizeof (float));

    //plugins->setParameter (PAR_GAIN, 0.5f);
    //plugins->setParameterReal (PAR_POLY, 128.0f);
}

SoundCrabParameters::~SoundCrabParameters ()
{
}

//==============================================================================
void SoundCrabParameters::registerGlobalParameters ()
{
    plugin->setNumParameters (TOTAL_PARAMETERS);

    int currentSynthChannel = plugin->currentSynthChannel;

    // Master params
    PREG (PAR_GAIN, p[PAR_GAIN]
          .name (T("gain")).range (0, 1).unit (T("%"))
          .set (MakeDelegate (this, &SoundCrabParameters::set_gain))
          .get (MakeDelegate (this, &SoundCrabParameters::get_gain)));

    PREG (PAR_POLY, p[PAR_POLY]
          .name (T("poly")).range (1, 128).unit (T("v"))
          .set (MakeDelegate (this, &SoundCrabParameters::set_poly))
          .get (MakeDelegate (this, &SoundCrabParameters::get_poly)));

    // Part params
    PREG (PAR_PAN, p[PAR_PAN]
          .name (T("pan")).range (0, 1).unit (T("%")).part (currentSynthChannel)
          .set (MakeDelegate (this, &SoundCrabParameters::set_pan))
          .get (MakeDelegate (this, &SoundCrabParameters::get_pan)));

    // Pitch params
    PREG (PAR_COARSETUNE, p[PAR_COARSETUNE]
          .name (T("tune")).range (0, 1).unit (T("%")).part (currentSynthChannel)
          .set (MakeDelegate (this, &SoundCrabParameters::set_coarse_tune))
          .get (MakeDelegate (this, &SoundCrabParameters::get_coarse_tune)));

    PREG (PAR_FINETUNE, p[PAR_FINETUNE]
          .name (T("finetune")).range (0, 1).unit (T("%")).part (currentSynthChannel)
          .set (MakeDelegate (this, &SoundCrabParameters::set_fine_tune))
          .get (MakeDelegate (this, &SoundCrabParameters::get_fine_tune)));

    PREG (PAR_MODLFOTOPITCH, p[PAR_MODLFOTOPITCH]
          .name (T("tune-lfo")).range (0, 1).unit (T("%")).part (currentSynthChannel)
          .set (MakeDelegate (this, &SoundCrabParameters::set_coarse_tune_lfo_depth))
          .get (MakeDelegate (this, &SoundCrabParameters::get_coarse_tune_lfo_depth)));

    PREG (PAR_MODENVTOPITCH, p[PAR_MODENVTOPITCH]
          .name (T("tune-env")).range (0, 1).unit (T("%")).part (currentSynthChannel)
          .set (MakeDelegate (this, &SoundCrabParameters::set_coarse_tune_env_depth))
          .get (MakeDelegate (this, &SoundCrabParameters::get_coarse_tune_env_depth)));

    // Filter Params
    PREG (PAR_FILTERFC, p[PAR_FILTERFC]
          .name (T("flt-cut")).range (0, 1).unit (T("%")).part (currentSynthChannel)
          .set (MakeDelegate (this, &SoundCrabParameters::set_filter_cutoff))
          .get (MakeDelegate (this, &SoundCrabParameters::get_filter_cutoff)));

    PREG (PAR_FILTERQ, p[PAR_FILTERQ]
          .name (T("flt-res")).range (0, 1).unit (T("%")).part (currentSynthChannel)
          .set (MakeDelegate (this, &SoundCrabParameters::set_filter_q))
          .get (MakeDelegate (this, &SoundCrabParameters::get_filter_q)));

    PREG (PAR_MODLFOTOFILTERFC, p[PAR_MODLFOTOFILTERFC]
          .name (T("flt-lfo")).range (0, 1).unit (T("%")).part (currentSynthChannel)
          .set (MakeDelegate (this, &SoundCrabParameters::set_filter_lfo_depth))
          .get (MakeDelegate (this, &SoundCrabParameters::get_filter_lfo_depth)));

    PREG (PAR_MODENVTOFILTERFC, p[PAR_MODENVTOFILTERFC]
          .name (T("flt-env")).range (0, 1).unit (T("%")).part (currentSynthChannel)
          .set (MakeDelegate (this, &SoundCrabParameters::set_filter_env_depth))
          .get (MakeDelegate (this, &SoundCrabParameters::get_filter_env_depth)));

    // Mod Lfo
    PREG (PAR_MODLFODELAY, p[PAR_MODLFODELAY]
          .name (T("lfo-dly")).range (0, 1).unit (T("%")).part (currentSynthChannel)
          .set (MakeDelegate (this, &SoundCrabParameters::set_modlfo_delay))
          .get (MakeDelegate (this, &SoundCrabParameters::get_modlfo_delay)));

    PREG (PAR_MODLFOFREQ, p[PAR_MODLFOFREQ]
          .name (T("lfo-frq")).range (0, 1).unit (T("%")).part (currentSynthChannel)
          .set (MakeDelegate (this, &SoundCrabParameters::set_modlfo_freq))
          .get (MakeDelegate (this, &SoundCrabParameters::get_modlfo_freq)));

    // Amp Envelope
    PREG (PAR_GAIN, p[PAR_GAIN]
          .name (T("volenv-a")).range (0, 1).unit (T("%")).part (currentSynthChannel)
          .set (MakeDelegate (this, &SoundCrabParameters::set_ampenv_attack))
          .get (MakeDelegate (this, &SoundCrabParameters::get_ampenv_attack)));

    PREG (PAR_VOLENVDECAY, p[PAR_VOLENVDECAY]
          .name (T("volenv-d")).range (0, 1).unit (T("%")).part (currentSynthChannel)
          .set (MakeDelegate (this, &SoundCrabParameters::set_ampenv_decay))
          .get (MakeDelegate (this, &SoundCrabParameters::get_ampenv_decay)));

    PREG (PAR_VOLENVSUSTAIN, p[PAR_VOLENVSUSTAIN]
          .name (T("volenv-s")).range (0, 1).unit (T("%")).part (currentSynthChannel)
          .set (MakeDelegate (this, &SoundCrabParameters::set_ampenv_sustain))
          .get (MakeDelegate (this, &SoundCrabParameters::get_ampenv_sustain)));

    PREG (PAR_VOLENVRELEASE, p[PAR_VOLENVRELEASE]
          .name (T("volenv-r")).range (0, 1).unit (T("%")).part (currentSynthChannel)
          .set (MakeDelegate (this, &SoundCrabParameters::set_ampenv_release))
          .get (MakeDelegate (this, &SoundCrabParameters::get_ampenv_release)));

    // Mod Envelope
    PREG (PAR_MODENVATTACK, p[PAR_MODENVATTACK]
          .name (T("modenv-a")).range (0, 1).unit (T("%")).part (currentSynthChannel)
          .set (MakeDelegate (this, &SoundCrabParameters::set_modenv_attack))
          .get (MakeDelegate (this, &SoundCrabParameters::get_modenv_attack)));

    PREG (PAR_MODENVDECAY, p[PAR_MODENVDECAY]
          .name (T("modenv-d")).range (0, 1).unit (T("%")).part (currentSynthChannel)
          .set (MakeDelegate (this, &SoundCrabParameters::set_modenv_decay))
          .get (MakeDelegate (this, &SoundCrabParameters::get_modenv_decay)));

    PREG (PAR_MODENVSUSTAIN, p[PAR_MODENVSUSTAIN]
          .name (T("modenv-s")).range (0, 1).unit (T("%")).part (currentSynthChannel)
          .set (MakeDelegate (this, &SoundCrabParameters::set_modenv_sustain))
          .get (MakeDelegate (this, &SoundCrabParameters::get_modenv_sustain)));

    PREG (PAR_MODENVRELEASE, p[PAR_MODENVRELEASE]
          .name (T("modenv-r")).range (0, 1).unit (T("%")).part (currentSynthChannel)
          .set (MakeDelegate (this, &SoundCrabParameters::set_modenv_release))
          .get (MakeDelegate (this, &SoundCrabParameters::get_modenv_release)));
}

//==============================================================================
float SoundCrabParameters::get_gain (int n)
{
    if (*synth)
        return fluid_synth_get_gain (*synth) / 2.66f;
    else
        return params [PAR_GAIN];
}

void SoundCrabParameters::set_gain (int n, float value)
{
    params [PAR_GAIN] = value;

    if (*synth)
        fluid_synth_set_gain (*synth, value * 2.66f);
}

//==============================================================================
float SoundCrabParameters::get_poly (int n)
{
    if (*synth)
        return fluid_synth_get_polyphony (*synth);
    else
        return params [PAR_POLY];
}

void SoundCrabParameters::set_poly (int n, float value)
{
    params [PAR_POLY] = value;

    if (*synth)
        fluid_synth_set_polyphony (*synth, roundFloatToInt (value));
}

//==============================================================================
float SoundCrabParameters::get_pan (int n)
{
    if (*synth)
        return fluid_synth_get_gen (*synth, n, GEN_PAN) / 1000.0f + 0.5f;
    else
        return params [PAR_PAN];
}

void SoundCrabParameters::set_pan (int n, float value)
{
    params [PAR_PAN] = value;

    if (*synth)
        fluid_synth_set_gen (*synth, n, GEN_PAN, (value - 0.5f) * 1000.0f);
}

//==============================================================================
float SoundCrabParameters::get_coarse_tune (int n)
{
    if (*synth)
        return fluid_synth_get_gen (*synth, n, GEN_COARSETUNE) / 24.0f + 0.5f;
    else
        return params [PAR_COARSETUNE];
}

void SoundCrabParameters::set_coarse_tune (int n, float value)
{
    params [PAR_COARSETUNE] = value;

    if (*synth)
        fluid_synth_set_gen (*synth, n, GEN_COARSETUNE, (value - 0.5f) * 24.0f);
}

//==============================================================================
float SoundCrabParameters::get_fine_tune (int n)
{
    if (*synth)
        return fluid_synth_get_gen (*synth, n, GEN_FINETUNE) / 198.0f + 0.5f;
    else
        return params [PAR_FINETUNE];
}

void SoundCrabParameters::set_fine_tune (int n, float value)
{
    params [PAR_FINETUNE] = value;

    if (*synth)
        fluid_synth_set_gen (*synth, n, GEN_FINETUNE, (value - 0.5f) * 198.0f);
}

//==============================================================================
float SoundCrabParameters::get_coarse_tune_lfo_depth (int n)
{
    if (*synth)
        return fluid_synth_get_gen (*synth, n, GEN_MODLFOTOPITCH) / 24000.0f + 0.5f;
    else
        return params [PAR_MODLFOTOPITCH];
}

void SoundCrabParameters::set_coarse_tune_lfo_depth (int n, float value)
{
    params [PAR_MODLFOTOPITCH] = value;

    if (*synth)
        fluid_synth_set_gen (*synth, n, GEN_MODLFOTOPITCH, (value - 0.5f) * 24000.0f);
}

//==============================================================================
float SoundCrabParameters::get_coarse_tune_env_depth (int n)
{
    if (*synth)
        return fluid_synth_get_gen (*synth, n, GEN_MODENVTOPITCH) / 24000.0f + 0.5f;
    else
        return params [PAR_MODENVTOPITCH];
}

void SoundCrabParameters::set_coarse_tune_env_depth (int n, float value)
{
    params [PAR_MODENVTOPITCH] = value;

    if (*synth)
        fluid_synth_set_gen (*synth, n, GEN_MODENVTOPITCH, (value - 0.5f) * 24000.0f);
}


//==============================================================================
float SoundCrabParameters::get_filter_cutoff (int n)
{
    if (*synth)
        return (fluid_synth_get_gen (*synth, n, GEN_FILTERFC) - 1500.0f) / 12000.0f;
    else
        return params [PAR_FILTERFC];
}

void SoundCrabParameters::set_filter_cutoff (int n, float value)
{
    params [PAR_FILTERFC] = value;

    if (*synth)
        fluid_synth_set_gen (*synth, n, GEN_FILTERFC, 1500.0f + value * 12000.0f);
}

//==============================================================================
float SoundCrabParameters::get_filter_q (int n)
{
    if (*synth)
        return fluid_synth_get_gen (*synth, n, GEN_FILTERQ) / 96.0f;
    else
        return params [PAR_FILTERQ];
}

void SoundCrabParameters::set_filter_q (int n, float value)
{
    params [PAR_FILTERQ] = value;

    if (*synth)
        fluid_synth_set_gen (*synth, n, GEN_FILTERQ, value * 96.0f);
}

//==============================================================================
float SoundCrabParameters::get_filter_lfo_depth (int n)
{
    if (*synth)
        return fluid_synth_get_gen (*synth, n, GEN_MODLFOTOFILTERFC) / 24000.0f + 0.5f;
    else
        return params [PAR_MODLFOTOFILTERFC];
}

void SoundCrabParameters::set_filter_lfo_depth (int n, float value)
{
    params [PAR_MODLFOTOFILTERFC] = value;

    if (*synth)
        fluid_synth_set_gen (*synth, n, GEN_MODLFOTOFILTERFC, (value - 0.5f) * 24000.0f);
}

//==============================================================================
float SoundCrabParameters::get_filter_env_depth (int n)
{
    if (*synth)
        return fluid_synth_get_gen (*synth, n, GEN_MODENVTOFILTERFC) / 24000.0f + 0.5f;
    else
        return params [PAR_MODENVTOFILTERFC];
}

void SoundCrabParameters::set_filter_env_depth (int n, float value)
{
    params [PAR_MODENVTOFILTERFC] = value;

    if (*synth)
        fluid_synth_set_gen (*synth, n, GEN_MODENVTOFILTERFC, (value - 0.5f) * 24000.0f);
}


//==============================================================================
float SoundCrabParameters::get_ampenv_attack (int n)
{
    if (*synth)
#ifdef SOUNDCRAB_INVERT_ENVELOPES
        return (fluid_synth_get_gen (*synth, n, GEN_MODENVATTACK) + 12000.0f) / 20000.0f;
#else
        return (fluid_synth_get_gen (*synth, n, GEN_VOLENVATTACK) + 12000.0f) / 20000.0f;
#endif
    else
        return params [PAR_VOLENVATTACK];
}

void SoundCrabParameters::set_ampenv_attack (int n, float value)
{
    params [PAR_VOLENVATTACK] = value;

    if (*synth)
#ifdef SOUNDCRAB_INVERT_ENVELOPES
        fluid_synth_set_gen (*synth, n, GEN_MODENVATTACK, value * 20000.0f - 12000.0f);
#else
        fluid_synth_set_gen (*synth, n, GEN_VOLENVATTACK, value * 20000.0f - 12000.0f);
#endif
}

//==============================================================================
float SoundCrabParameters::get_ampenv_decay (int n)
{
    if (*synth)
#ifdef SOUNDCRAB_INVERT_ENVELOPES
        return fluid_synth_get_gen (*synth, n, GEN_MODENVDECAY) / 8000.0f;
#else
        return fluid_synth_get_gen (*synth, n, GEN_VOLENVDECAY) / 8000.0f;
#endif
    else
        return params [PAR_VOLENVDECAY];
}

void SoundCrabParameters::set_ampenv_decay (int n, float value)
{
    params [PAR_VOLENVDECAY] = value;

    if (*synth)
#ifdef SOUNDCRAB_INVERT_ENVELOPES
        fluid_synth_set_gen (*synth, n, GEN_MODENVDECAY, value * 8000.0f);
#else
        fluid_synth_set_gen (*synth, n, GEN_VOLENVDECAY, value * 8000.0f);
#endif
}

//==============================================================================
float SoundCrabParameters::get_ampenv_sustain (int n)
{
    if (*synth)
#ifdef SOUNDCRAB_INVERT_ENVELOPES
        return 1.0f - fluid_synth_get_gen (*synth, n, GEN_MODENVSUSTAIN) / 1000.0f;
#else
        return 1.0f - fluid_synth_get_gen (*synth, n, GEN_VOLENVSUSTAIN) / 1440.0f;
#endif
    else
        return params [PAR_VOLENVSUSTAIN];
}

void SoundCrabParameters::set_ampenv_sustain (int n, float value)
{
    params [PAR_VOLENVSUSTAIN] = value;

    if (*synth)
#ifdef SOUNDCRAB_INVERT_ENVELOPES
        fluid_synth_set_gen (*synth, n, GEN_MODENVSUSTAIN, (1.0f - value) * 1000.0f);
#else
        fluid_synth_set_gen (*synth, n, GEN_VOLENVSUSTAIN, (1.0f - value) * 1440.0f);
#endif
}

//==============================================================================
float SoundCrabParameters::get_ampenv_release (int n)
{
    if (*synth)
#ifdef SOUNDCRAB_INVERT_ENVELOPES
        return fluid_synth_get_gen (*synth, n, GEN_MODENVRELEASE) / 6000.0f;
#else
        return fluid_synth_get_gen (*synth, n, GEN_VOLENVRELEASE) / 8000.0f;
#endif
    else
        return params [PAR_VOLENVRELEASE];
}

void SoundCrabParameters::set_ampenv_release (int n, float value)
{
    params [PAR_VOLENVRELEASE] = value;

    if (*synth)
#ifdef SOUNDCRAB_INVERT_ENVELOPES
        fluid_synth_set_gen (*synth, n, GEN_MODENVRELEASE, value * 6000.0f);
#else
        fluid_synth_set_gen (*synth, n, GEN_VOLENVRELEASE, value * 8000.0f);
#endif
}


//==============================================================================
float SoundCrabParameters::get_modenv_attack (int n)
{
    if (*synth)
#ifdef SOUNDCRAB_INVERT_ENVELOPES
        return (fluid_synth_get_gen (*synth, n, GEN_VOLENVATTACK) + 12000.0f) / 20000.0f;
#else
        return (fluid_synth_get_gen (*synth, n, GEN_MODENVATTACK) + 12000.0f) / 20000.0f;
#endif
    else
        return params [PAR_MODENVATTACK];
}

void SoundCrabParameters::set_modenv_attack (int n, float value)
{
    params [PAR_MODENVATTACK] = value;

    if (*synth)
#ifdef SOUNDCRAB_INVERT_ENVELOPES
        fluid_synth_set_gen (*synth, n, GEN_VOLENVATTACK, value * 20000.0f - 12000.0f);
#else
        fluid_synth_set_gen (*synth, n, GEN_MODENVATTACK, value * 20000.0f - 12000.0f);
#endif
}

//==============================================================================
float SoundCrabParameters::get_modenv_decay (int n)
{
    if (*synth)
#ifdef SOUNDCRAB_INVERT_ENVELOPES
        return fluid_synth_get_gen (*synth, n, PAR_VOLENVDECAY) / 6000.0f;
#else
        return fluid_synth_get_gen (*synth, n, PAR_MODENVDECAY) / 8000.0f;
#endif
    else
        return params [PAR_MODENVDECAY];
}

void SoundCrabParameters::set_modenv_decay (int n, float value)
{
    params [PAR_MODENVDECAY] = value;

    if (*synth)
#ifdef SOUNDCRAB_INVERT_ENVELOPES
        fluid_synth_set_gen (*synth, n, PAR_VOLENVDECAY, value * 6000.0f);
#else
        fluid_synth_set_gen (*synth, n, PAR_MODENVDECAY, value * 8000.0f);
#endif
}

//==============================================================================
float SoundCrabParameters::get_modenv_sustain (int n)
{
    if (*synth)
#ifdef SOUNDCRAB_INVERT_ENVELOPES
        return 1.0f - fluid_synth_get_gen (*synth, n, GEN_VOLENVSUSTAIN) / 1440.0f;
#else
        return 1.0f - fluid_synth_get_gen (*synth, n, GEN_MODENVSUSTAIN) / 1000.0f;
#endif
    else
        return params [PAR_MODENVSUSTAIN];
}

void SoundCrabParameters::set_modenv_sustain (int n, float value)
{
    params [PAR_MODENVSUSTAIN] = value;

    if (*synth)
#ifdef SOUNDCRAB_INVERT_ENVELOPES
        fluid_synth_set_gen (*synth, n, GEN_VOLENVSUSTAIN, (1.0f - value) * 1440.0f);
#else
        fluid_synth_set_gen (*synth, n, GEN_MODENVSUSTAIN, (1.0f - value) * 1000.0f);
#endif
}

//==============================================================================
float SoundCrabParameters::get_modenv_release (int n)
{
    if (*synth)
#ifdef SOUNDCRAB_INVERT_ENVELOPES
        return fluid_synth_get_gen (*synth, n, GEN_VOLENVRELEASE) / 6000.0f;
#else
        return fluid_synth_get_gen (*synth, n, GEN_MODENVRELEASE) / 8000.0f;
#endif
    else
        return params [PAR_MODENVRELEASE];
}

void SoundCrabParameters::set_modenv_release (int n, float value)
{
    params [PAR_MODENVRELEASE] = value;

    if (*synth)
#ifdef SOUNDCRAB_INVERT_ENVELOPES
        fluid_synth_set_gen (*synth, n, GEN_VOLENVRELEASE, value * 6000.0f);
#else
        fluid_synth_set_gen (*synth, n, GEN_MODENVRELEASE, value * 8000.0f);
#endif
}


//==============================================================================
float SoundCrabParameters::get_modlfo_delay (int n)
{
    if (*synth)
        return (fluid_synth_get_gen (*synth, n, GEN_MODLFODELAY) + 12000.0f) / 17000.0f;
    else
        return params [PAR_MODLFODELAY];
}

void SoundCrabParameters::set_modlfo_delay (int n, float value)
{
    params [PAR_MODLFODELAY] = value;

    if (*synth)
        fluid_synth_set_gen (*synth, n, GEN_MODLFODELAY, value * 17000.0f - 12000.0f);
}

//==============================================================================
float SoundCrabParameters::get_modlfo_freq (int n)
{
    if (*synth)
        return (fluid_synth_get_gen (*synth, n, GEN_MODLFOFREQ) + 11000.0f) / 15500.0f;
    else
        return params [PAR_MODLFOFREQ];
}

void SoundCrabParameters::set_modlfo_freq (int n, float value)
{
    params [PAR_MODLFOFREQ] = value;

    if (*synth)
        fluid_synth_set_gen (*synth, n, GEN_MODLFOFREQ, value * 15500.0f - 11000.0f);
}

