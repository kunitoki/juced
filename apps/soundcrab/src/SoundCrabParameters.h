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

#ifndef __JUCETICE_SOUNDCRABPARAMETERS_HEADER__
#define __JUCETICE_SOUNDCRABPARAMETERS_HEADER__

#include "Synth/fluid_synth.h"
#include "StandardHeader.h"

class SoundCrabPlugin;

//==============================================================================
/** All our synth parameters */
enum
{
    PAR_GAIN = 0,
    PAR_POLY,

    PAR_PAN,
    PAR_COARSETUNE,
    PAR_FINETUNE,
    PAR_MODLFOTOPITCH,
    PAR_MODENVTOPITCH,
    PAR_FILTERFC,
    PAR_FILTERQ,
    PAR_MODLFOTOFILTERFC,
    PAR_MODENVTOFILTERFC,
//  PAR_STARTADDROFS,
//  PAR_ENDADDROFS,
//  PAR_STARTLOOPADDROFS,
//  PAR_ENDLOOPADDROFS,
//  PAR_STARTADDRCOARSEOFS,
//  PAR_ENDADDRCOARSEOFS,
//  PAR_MODLFOTOVOL,
//  PAR_UNUSED1,
//  PAR_CHORUSSEND,
//  PAR_REVERBSEND,
//  PAR_UNUSED2,
//  PAR_UNUSED3,
//  PAR_UNUSED4,
    PAR_MODLFODELAY,
    PAR_MODLFOFREQ,
//  PAR_VIBLFODELAY,
//  PAR_VIBLFOFREQ,
    PAR_MODENVATTACK,
    PAR_MODENVDECAY,
    PAR_MODENVSUSTAIN,
    PAR_MODENVRELEASE,
//  PAR_KEYTOMODENVHOLD,
//  PAR_KEYTOMODENVDECAY,
    PAR_VOLENVATTACK,
    PAR_VOLENVDECAY,
    PAR_VOLENVSUSTAIN,
    PAR_VOLENVRELEASE,
//  PAR_KEYTOVOLENVHOLD,
//  PAR_KEYTOVOLENVDECAY,
//  PAR_INSTRUMENT,
//  PAR_RESERVED1,
//  PAR_KEYRANGE,
//  PAR_VELRANGE,
//  PAR_STARTLOOPADDRCOARSEOFS,
//  PAR_KEYNUM,
//  PAR_VELOCITY,
//  PAR_ATTENUATION,
//  PAR_RESERVED2,
//  PAR_ENDLOOPADDRCOARSEOFS,
//  PAR_SAMPLEID,
//  PAR_SAMPLEMODE,
//  PAR_RESERVED3,
//  PAR_SCALETUNE,
//  PAR_EXCLUSIVECLASS,
//  PAR_OVERRIDEROOTKEY,
//  PAR_PITCH,

    TOTAL_PARAMETERS
};


//==============================================================================
/** Handy macro to register a parametetr */
#define PREG(n,p)            { plugin->registerParameter (n, &p); }


//==============================================================================
/** This class is a helper class for publishing parameters */
class SoundCrabParameters
{
public:
    /** Constructor */
    SoundCrabParameters (SoundCrabPlugin* plugin);
    /** Destructor */
    ~SoundCrabParameters ();

protected:

    /** Master getters and setters delegates */
    float get_gain (int n);
    void set_gain (int n, float value);
    float get_pan (int n);
    void set_pan (int n, float value);
    float get_poly (int n);
    void set_poly (int n, float value);

    float get_coarse_tune (int n);
    void set_coarse_tune (int n, float value);
    float get_fine_tune (int n);
    void set_fine_tune (int n, float value);
    float get_coarse_tune_lfo_depth (int n);
    void set_coarse_tune_lfo_depth (int n, float value);
    float get_coarse_tune_env_depth (int n);
    void set_coarse_tune_env_depth (int n, float value);

    float get_filter_cutoff (int n);
    void set_filter_cutoff (int n, float value);
    float get_filter_q (int n);
    void set_filter_q (int n, float value);
    float get_filter_lfo_depth (int n);
    void set_filter_lfo_depth (int n, float value);
    float get_filter_env_depth (int n);
    void set_filter_env_depth (int n, float value);

    float get_ampenv_attack (int n);
    void set_ampenv_attack (int n, float value);
    float get_ampenv_decay (int n);
    void set_ampenv_decay (int n, float value);
    float get_ampenv_sustain (int n);
    void set_ampenv_sustain (int n, float value);
    float get_ampenv_release (int n);
    void set_ampenv_release (int n, float value);

    float get_modenv_attack (int n);
    void set_modenv_attack (int n, float value);
    float get_modenv_decay (int n);
    void set_modenv_decay (int n, float value);
    float get_modenv_sustain (int n);
    void set_modenv_sustain (int n, float value);
    float get_modenv_release (int n);
    void set_modenv_release (int n, float value);

    float get_modlfo_delay (int n);
    void set_modlfo_delay (int n, float value);
    float get_modlfo_freq (int n);
    void set_modlfo_freq (int n, float value);

private:

    void registerGlobalParameters ();

    /** Internal holders */
    SoundCrabPlugin* plugin;
    fluid_synth_t** synth;

    AudioParameter p [TOTAL_PARAMETERS];
    float params [TOTAL_PARAMETERS];
};


#endif // __JUCETICE_SOUNDCRABPARAMETERS_HEADER__
