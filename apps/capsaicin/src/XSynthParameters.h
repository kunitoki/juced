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

#ifndef __JUCETICE_XSYNTHPARAMETERS_HEADER__
#define __JUCETICE_XSYNTHPARAMETERS_HEADER__

#include "StandardHeader.h"

class Master;
class XSynthPlugin;

//==============================================================================
/** All our synth parameters */
enum
{

    PM_GAIN = 0,             // global parameters start here ---------
    PM_SOLO,
    // compressor ?
    PM_FX1_0,
    PM_FX1_1,
    PM_FX1_2,
    PM_FX1_3,
    PM_FX1_4,
    PM_FX1_5,
    // reverb
    PM_FX2_0,
    PM_FX2_1,
    PM_FX2_2,
    PM_FX2_3,
    PM_FX2_4, // unused
    PM_FX2_5, // unused

    PART_PARAMETER_OFFSET,   // part parameters start here ----------

    // part parameters
    PP_ENABLED = 0,
    PP_POLY,
    PP_PORTA,
    PP_STEREO, // want to keep it out (would save some CPU cycles?)
    // amp / pan / mixing
    PP_GAIN,
    PP_PAN,
    PP_X,
    PP_Y,
    PP_AMP_ATTACK,
    PP_AMP_DECAY,
    PP_AMP_SUSTAIN,
    PP_AMP_RELEASE,
    // tone / frequency
    PP_TONE,
    PP_FINETUNE,
    PP_TONE_ATTACK,
    PP_TONE_ATTACKTIME,
    PP_TONE_DECAY,
    PP_TONE_DECAYTIME,
    PP_TONE_RELEASE,
    PP_TONE_RELEASETIME,
    // noise
    PP_NOISE,
    // filter
    PP_FILTERCUTOFF,
    PP_FILTERRESO,
    PP_FILTERTYPE,
    PP_FILTERTRACK,
    PP_FILTER_LFODEPTH,
    PP_FILTER_LFOFREQ,
    PP_FILTER_LFODELAY,
    PP_FILTER_ATTACK,
    PP_FILTER_ATTACKTIME,
    PP_FILTER_DECAY,
    PP_FILTER_DECAYTIME,
    // chorus
    PP_CHORUS_GAIN,
    PP_CHORUS_FREQ,
    PP_CHORUS_DELAY,
    PP_CHORUS_DEPTH,
    PP_CHORUS_FEEDBACK,
    // drive
    PP_DRIVE_AMOUNT,
    PP_DRIVE_LP,
    PP_DRIVE_HP,
    // TODO - chorus / compressor
    // equalizer
    PP_EQ_LS_G,
    PP_EQ_LS_F,
    PP_EQ_LS_BW,
    PP_EQ_PK0_G,
    PP_EQ_PK0_F,
    PP_EQ_PK0_BW,
    PP_EQ_PK1_G,
    PP_EQ_PK1_F,
    PP_EQ_PK1_BW,
    PP_EQ_HS_G,
    PP_EQ_HS_F,
    PP_EQ_HS_BW,
    // delay
    PP_DELAY_GAIN,
    PP_DELAY_PAN,
    PP_DELAY_TIME,
    PP_DELAY_FEED,
    PP_DELAY_LP,

    TOTAL_PART_PARAMETERS,

    // total number of parameters ------------------------------
    TOTAL_PARAMETERS = PART_PARAMETER_OFFSET
                       + TOTAL_PART_PARAMETERS * 16
};


//==============================================================================
/** Handy macro for getting a part specific parameter */
#define PPAR(n,p)           (PART_PARAMETER_OFFSET + (TOTAL_PART_PARAMETERS * n) + p)

/** Handy macro to register a parametetr */
#define PREG(n,p)           { plugin->registerParameter (n, &p); }


//==============================================================================
/** This class is a helper class for publishing parameters */
class XSynthParameters
{
public:
    /** Constructor */
    XSynthParameters (XSynthPlugin* plugin);
    /** Destructor */
    ~XSynthParameters ();

protected:

    /** Master getters and setters delegates */
    float get_master_gain (int n);
    void set_master_gain (int n, float value);
    float get_master_solo (int n);
    void set_master_solo (int n, float value);

    /** Part parameters getters and setters, taking N into account */
    float get_part_enabled (int n);
    void set_part_enabled (int n, float value);
    float get_part_porta (int n);
    void set_part_porta (int n, float value);
    float get_part_poly (int n);
    void set_part_poly (int n, float value);
    float get_part_stereo (int n);
    void set_part_stereo (int n, float value);

    float get_part_gain (int n);
    void set_part_gain (int n, float value);
    float get_part_pan (int n);
    void set_part_pan (int n, float value);
    float get_part_x (int n);
    void set_part_x (int n, float value);
    float get_part_y (int n);
    void set_part_y (int n, float value);

    float get_part_amp_attack (int n);
    void set_part_amp_attack (int n, float value);
    float get_part_amp_decay (int n);
    void set_part_amp_decay (int n, float value);
    float get_part_amp_sustain (int n);
    void set_part_amp_sustain (int n, float value);
    float get_part_amp_release (int n);
    void set_part_amp_release (int n, float value);

    float get_part_tone (int n);
    void set_part_tone (int n, float value);
    float get_part_finetune (int n);
    void set_part_finetune (int n, float value);
    float get_part_tone_attack (int n);
    void set_part_tone_attack (int n, float value);
    float get_part_tone_attacktime (int n);
    void set_part_tone_attacktime (int n, float value);
    float get_part_tone_decay (int n);
    void set_part_tone_decay (int n, float value);
    float get_part_tone_decaytime (int n);
    void set_part_tone_decaytime (int n, float value);
    float get_part_tone_release (int n);
    void set_part_tone_release (int n, float value);
    float get_part_tone_releasetime (int n);
    void set_part_tone_releasetime (int n, float value);

    float get_part_noise (int n);
    void set_part_noise (int n, float value);

    float get_part_filter_cutoff (int n);
    void set_part_filter_cutoff (int n, float value);
    float get_part_filter_reso (int n);
    void set_part_filter_reso (int n, float value);
    float get_part_filter_type (int n);
    void set_part_filter_type (int n, float value);
    float get_part_filter_track (int n);
    void set_part_filter_track (int n, float value);
    float get_part_filter_lfodepth (int n);
    void set_part_filter_lfodepth (int n, float value);
    float get_part_filter_lfofreq (int n);
    void set_part_filter_lfofreq (int n, float value);
    float get_part_filter_lfodelay (int n);
    void set_part_filter_lfodelay (int n, float value);
    float get_part_filter_attack (int n);
    void set_part_filter_attack (int n, float value);
    float get_part_filter_attacktime (int n);
    void set_part_filter_attacktime (int n, float value);
    float get_part_filter_decay(int n);
    void set_part_filter_decay (int n, float value);
    float get_part_filter_decaytime (int n);
    void set_part_filter_decaytime (int n, float value);

    float get_part_chorus_gain (int n);
    void set_part_chorus_gain (int n, float value);
    float get_part_chorus_freq (int n);
    void set_part_chorus_freq (int n, float value);
    float get_part_chorus_delay (int n);
    void set_part_chorus_delay (int n, float value);
    float get_part_chorus_depth (int n);
    void set_part_chorus_depth (int n, float value);
    float get_part_chorus_feed (int n);
    void set_part_chorus_feed (int n, float value);

    float get_part_drive (int n);
    void set_part_drive (int n, float value);
    float get_part_drive_lp (int n);
    void set_part_drive_lp (int n, float value);
    float get_part_drive_hp (int n);
    void set_part_drive_hp (int n, float value);

    float get_part_eq1_gain (int n);
    void set_part_eq1_gain (int n, float value);
    float get_part_eq1_freq (int n);
    void set_part_eq1_freq (int n, float value);
    float get_part_eq1_q (int n);
    void set_part_eq1_q (int n, float value);
    float get_part_eq2_gain (int n);
    void set_part_eq2_gain (int n, float value);
    float get_part_eq2_freq (int n);
    void set_part_eq2_freq (int n, float value);
    float get_part_eq2_q (int n);
    void set_part_eq2_q (int n, float value);
    float get_part_eq3_gain (int n);
    void set_part_eq3_gain (int n, float value);
    float get_part_eq3_freq (int n);
    void set_part_eq3_freq (int n, float value);
    float get_part_eq3_q (int n);
    void set_part_eq3_q (int n, float value);
    float get_part_eq4_gain (int n);
    void set_part_eq4_gain (int n, float value);
    float get_part_eq4_freq (int n);
    void set_part_eq4_freq (int n, float value);
    float get_part_eq4_q (int n);
    void set_part_eq4_q (int n, float value);

    float get_part_delay_gain (int n);
    void set_part_delay_gain (int n, float value);
    float get_part_delay_pan (int n);
    void set_part_delay_pan (int n, float value);
    float get_part_delay_time (int n);
    void set_part_delay_time (int n, float value);
    float get_part_delay_feed (int n);
    void set_part_delay_feed (int n, float value);
    float get_part_delay_lp (int n);
    void set_part_delay_lp (int n, float value);

private:

    void registerGlobalParameters ();
    void registerPartParameters (const int n);

    /** Internal holders */
    XSynthPlugin* plugin;
    Master* master;

    AudioParameter p [TOTAL_PARAMETERS];
};


#endif // __JUCETICE_XSYNTHPARAMETERS_HEADER__
