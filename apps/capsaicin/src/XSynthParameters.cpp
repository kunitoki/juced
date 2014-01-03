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

#include "XSynthParameters.h"
#include "XSynthPlugin.h"

//==============================================================================
XSynthParameters::XSynthParameters (XSynthPlugin* plugin_)
  : plugin (plugin_),
    master (&plugin->master)
{
    plugin->setNumParameters (TOTAL_PARAMETERS);

    // global parameter publishing
    registerGlobalParameters ();

    // parts parameter publishing
    for (int i = 0; i < NUM_MIDI_PARTS; i++)
        registerPartParameters (i);
}

XSynthParameters::~XSynthParameters ()
{
}

//==============================================================================
void XSynthParameters::registerGlobalParameters ()
{
    // Master params
    PREG (PM_GAIN, p[PM_GAIN]
          .name (T("vol")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_master_gain))
          .get (MakeDelegate (this, &XSynthParameters::get_master_gain)));

    // TODO
    PREG (PM_SOLO, p[PM_SOLO]
          .name (T("solo")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_master_solo))
          .get (MakeDelegate (this, &XSynthParameters::get_master_solo)));

    // master effect 1
    PREG (PM_FX1_0, p[PM_FX1_0]
          .name (T("fx1 0")).range (0,1).unit (T("%")));

    PREG (PM_FX1_1, p[PM_FX1_1]
          .name (T("fx1 1")).range (0,1).unit (T("%")));

    PREG (PM_FX1_2, p[PM_FX1_2]
          .name (T("fx1 2")).range (0,1).unit (T("%")));

    PREG (PM_FX1_3, p[PM_FX1_3]
          .name (T("fx1 3")).range (0,1).unit (T("%")));

    PREG (PM_FX1_4, p[PM_FX1_4]
          .name (T("fx1 4")).range (0,1).unit (T("%")));

    PREG (PM_FX1_5, p[PM_FX1_5]
          .name (T("fx1 5")).range (0,1).unit (T("%")));

    // master effect 2
    PREG (PM_FX2_0, p[PM_FX2_0]
          .name (T("fx2 0")).range (0,1).unit (T("%")));

    PREG (PM_FX2_1, p[PM_FX2_1]
          .name (T("fx2 1")).range (0,1).unit (T("%")));

    PREG (PM_FX2_2, p[PM_FX2_2]
          .name (T("fx2 2")).range (0,1).unit (T("%")));
          
    PREG (PM_FX2_3, p[PM_FX2_3]
          .name (T("fx2 3")).range (0,1).unit (T("%")));

    PREG (PM_FX2_4, p[PM_FX2_4]
          .name (T("fx2 4")).range (0,1).unit (T("%")));

    PREG (PM_FX2_5, p[PM_FX2_5]
          .name (T("fx2 5")).range (0,1).unit (T("%")));
}

//==============================================================================
void XSynthParameters::registerPartParameters (const int n)
{
    // Part specific params
    int param = 0;

    // global on off toggles
    param = PPAR(n, PP_ENABLED);
    PREG (param, p[param].part (n)
          .name (T("on")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_enabled))
          .get (MakeDelegate (this, &XSynthParameters::get_part_enabled)));

    param = PPAR(n, PP_PORTA);
    PREG (param, p[param].part (n)
          .name (T("porta")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_porta))
          .get (MakeDelegate (this, &XSynthParameters::get_part_porta)));

    param = PPAR(n, PP_POLY);
    PREG (param, p[param].part (n)
          .name (T("poly")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_poly))
          .get (MakeDelegate (this, &XSynthParameters::get_part_poly)));

    param = PPAR(n, PP_STEREO);
    PREG (param, p[param].part (n)
          .name (T("stereo")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_stereo))
          .get (MakeDelegate (this, &XSynthParameters::get_part_stereo)));

    // global gain / pan / joystick
    param = PPAR(n, PP_GAIN);
    PREG (param, p[param].part (n)
          .name (T("gain")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_gain))
          .get (MakeDelegate (this, &XSynthParameters::get_part_gain)));

    param = PPAR(n, PP_PAN);
    PREG (param, p[param].part (n)
          .name (T("pan")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_pan))
          .get (MakeDelegate (this, &XSynthParameters::get_part_pan)));

    param = PPAR(n, PP_X);
    PREG (param, p[param].part (n)
          .name (T("x-joy")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_x))
          .get (MakeDelegate (this, &XSynthParameters::get_part_x)));

    param = PPAR(n, PP_Y);
    PREG (param, p[param].part (n)
          .name (T("y-joy")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_y))
          .get (MakeDelegate (this, &XSynthParameters::get_part_y)));

    // amp envelope
    param = PPAR(n, PP_AMP_ATTACK);
    PREG (param, p[param].part (n)
          .name (T("a-a")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_amp_attack))
          .get (MakeDelegate (this, &XSynthParameters::get_part_amp_attack)));

    param = PPAR(n, PP_AMP_DECAY);
    PREG (param, p[param].part (n)
          .name (T("a-d")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_amp_decay))
          .get (MakeDelegate (this, &XSynthParameters::get_part_amp_decay)));

    param = PPAR(n, PP_AMP_SUSTAIN);
    PREG (param, p[param].part (n)
          .name (T("a-s")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_amp_sustain))
          .get (MakeDelegate (this, &XSynthParameters::get_part_amp_sustain)));

    param = PPAR(n, PP_AMP_RELEASE);
    PREG (param, p[param].part (n)
          .name (T("a-r")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_amp_release))
          .get (MakeDelegate (this, &XSynthParameters::get_part_amp_release)));

    // tone / frequency
    param = PPAR(n, PP_TONE);
    PREG (param, p[param].part (n)
          .name (T("tone")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_tone))
          .get (MakeDelegate (this, &XSynthParameters::get_part_tone)));

    param = PPAR(n, PP_FINETUNE);
    PREG (param, p[param].part (n)
          .name (T("fine")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_finetune))
          .get (MakeDelegate (this, &XSynthParameters::get_part_finetune)));

    param = PPAR(n, PP_TONE_ATTACK);
    PREG (param, p[param].part (n)
          .name (T("t-a")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_tone_attack))
          .get (MakeDelegate (this, &XSynthParameters::get_part_tone_attack)));

    param = PPAR(n, PP_TONE_ATTACKTIME);
    PREG (param, p[param].part (n)
          .name (T("t-atime")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_tone_attacktime))
          .get (MakeDelegate (this, &XSynthParameters::get_part_tone_attacktime)));

    param = PPAR(n, PP_TONE_DECAY);
    PREG (param, p[param].part (n)
          .name (T("t-d")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_tone_decay))
          .get (MakeDelegate (this, &XSynthParameters::get_part_tone_decay)));

    param = PPAR(n, PP_TONE_DECAYTIME);
    PREG (param, p[param].part (n)
          .name (T("t-dtime")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_tone_decaytime))
          .get (MakeDelegate (this, &XSynthParameters::get_part_tone_decaytime)));

    param = PPAR(n, PP_TONE_RELEASE);
    PREG (param, p[param].part (n)
          .name (T("t-r")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_tone_release))
          .get (MakeDelegate (this, &XSynthParameters::get_part_tone_release)));

    param = PPAR(n, PP_TONE_RELEASETIME);
    PREG (param, p[param].part (n)
          .name (T("t-rtime")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_tone_releasetime))
          .get (MakeDelegate (this, &XSynthParameters::get_part_tone_releasetime)));

    // noise
    param = PPAR(n, PP_NOISE);
    PREG (param, p[param].part (n)
          .name (T("noise")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_noise))
          .get (MakeDelegate (this, &XSynthParameters::get_part_noise)));

    // filter
    param = PPAR(n, PP_FILTERCUTOFF);
    PREG (param, p[param].part (n)
          .name (T("f-cut")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_filter_cutoff))
          .get (MakeDelegate (this, &XSynthParameters::get_part_filter_cutoff)));

    param = PPAR(n, PP_FILTERRESO);
    PREG (param, p[param].part (n)
          .name (T("f-reso")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_filter_reso))
          .get (MakeDelegate (this, &XSynthParameters::get_part_filter_reso)));

    // TODO - filter type
    param = PPAR(n, PP_FILTERTYPE);
    PREG (param, p[param].part (n)
          .name (T("f-type")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_filter_type ))
          .get (MakeDelegate (this, &XSynthParameters::get_part_filter_type )));

    param = PPAR(n, PP_FILTER_LFODEPTH);
    PREG (param, p[param].part (n)
          .name (T("f-lfoa")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_filter_lfodepth ))
          .get (MakeDelegate (this, &XSynthParameters::get_part_filter_lfodepth )));

    param = PPAR(n, PP_FILTER_LFOFREQ);
    PREG (param, p[param].part (n)
          .name (T("f-lfof")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_filter_lfofreq ))
          .get (MakeDelegate (this, &XSynthParameters::get_part_filter_lfofreq )));

    param = PPAR(n, PP_FILTER_LFODELAY);
    PREG (param, p[param].part (n)
          .name (T("f-lfod")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_filter_lfodelay ))
          .get (MakeDelegate (this, &XSynthParameters::get_part_filter_lfodelay )));

    param = PPAR(n, PP_FILTERTRACK);
    PREG (param, p[param].part (n)
          .name (T("f-trck")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_filter_track))
          .get (MakeDelegate (this, &XSynthParameters::get_part_filter_track)));

    param = PPAR(n, PP_FILTER_ATTACK);
    PREG (param, p[param].part (n)
          .name (T("f-a")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_filter_attack))
          .get (MakeDelegate (this, &XSynthParameters::get_part_filter_attack)));

    param = PPAR(n, PP_FILTER_ATTACKTIME);
    PREG (param, p[param].part (n)
          .name (T("f-atime")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_filter_attacktime))
          .get (MakeDelegate (this, &XSynthParameters::get_part_filter_attacktime)));

    param = PPAR(n, PP_FILTER_DECAY);
    PREG (param, p[param].part (n)
          .name (T("f-d")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_filter_decay))
          .get (MakeDelegate (this, &XSynthParameters::get_part_filter_decay)));

    param = PPAR(n, PP_FILTER_DECAYTIME);
    PREG (param, p[param].part (n)
          .name (T("f-dtime")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_filter_decaytime))
          .get (MakeDelegate (this, &XSynthParameters::get_part_filter_decaytime)));

    // chorus
    param = PPAR(n, PP_CHORUS_GAIN);
    PREG (param, p[param].part (n)
          .name (T("cho-g")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_chorus_gain))
          .get (MakeDelegate (this, &XSynthParameters::get_part_chorus_gain)));

    param = PPAR(n, PP_CHORUS_FREQ);
    PREG (param, p[param].part (n)
          .name (T("cho-fq")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_chorus_freq))
          .get (MakeDelegate (this, &XSynthParameters::get_part_chorus_freq)));

    param = PPAR(n, PP_CHORUS_DELAY);
    PREG (param, p[param].part (n)
          .name (T("cho-dl")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_chorus_delay))
          .get (MakeDelegate (this, &XSynthParameters::get_part_chorus_delay)));

    param = PPAR(n, PP_CHORUS_DEPTH);
    PREG (param, p[param].part (n)
          .name (T("cho-dp")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_chorus_depth))
          .get (MakeDelegate (this, &XSynthParameters::get_part_chorus_depth)));

    param = PPAR(n, PP_CHORUS_FEEDBACK);
    PREG (param, p[param].part (n)
          .name (T("cho-fb")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_chorus_feed))
          .get (MakeDelegate (this, &XSynthParameters::get_part_chorus_feed)));

    // drive destruct
    param = PPAR(n, PP_DRIVE_AMOUNT);
    PREG (param, p[param].part (n)
          .name (T("drv-g")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_drive))
          .get (MakeDelegate (this, &XSynthParameters::get_part_drive)));

    param = PPAR(n, PP_DRIVE_LP);
    PREG (param, p[param].part (n)
          .name (T("drv-lp")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_drive_lp))
          .get (MakeDelegate (this, &XSynthParameters::get_part_drive_lp)));

    param = PPAR(n, PP_DRIVE_HP);
    PREG (param, p[param].part (n)
          .name (T("drv-hp")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_drive_hp))
          .get (MakeDelegate (this, &XSynthParameters::get_part_drive_hp)));

    // eq
    param = PPAR(n, PP_EQ_LS_G);
    PREG (param, p[param].part (n)
          .name (T("eq1-g")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_eq1_gain))
          .get (MakeDelegate (this, &XSynthParameters::get_part_eq1_gain)));

    param = PPAR(n, PP_EQ_LS_F);
    PREG (param, p[param].part (n)
          .name (T("eq1-f")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_eq1_freq))
          .get (MakeDelegate (this, &XSynthParameters::get_part_eq1_freq)));

    param = PPAR(n, PP_EQ_LS_BW);
    PREG (param, p[param].part (n)
          .name (T("eq1-q")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_eq1_q))
          .get (MakeDelegate (this, &XSynthParameters::get_part_eq1_q)));

    param = PPAR(n, PP_EQ_PK0_G);
    PREG (param, p[param].part (n)
          .name (T("eq2-g")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_eq2_gain))
          .get (MakeDelegate (this, &XSynthParameters::get_part_eq2_gain)));

    param = PPAR(n, PP_EQ_PK0_F);
    PREG (param, p[param].part (n)
          .name (T("eq2-f")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_eq2_freq))
          .get (MakeDelegate (this, &XSynthParameters::get_part_eq2_freq)));

    param = PPAR(n, PP_EQ_PK0_BW);
    PREG (param, p[param].part (n)
          .name (T("eq2-q")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_eq2_q))
          .get (MakeDelegate (this, &XSynthParameters::get_part_eq2_q)));

    param = PPAR(n, PP_EQ_PK1_G);
    PREG (param, p[param].part (n)
          .name (T("eq3-g")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_eq3_gain))
          .get (MakeDelegate (this, &XSynthParameters::get_part_eq3_gain)));

    param = PPAR(n, PP_EQ_PK1_F);
    PREG (param, p[param].part (n)
          .name (T("eq3-f")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_eq3_freq))
          .get (MakeDelegate (this, &XSynthParameters::get_part_eq3_freq)));

    param = PPAR(n, PP_EQ_PK1_BW);
    PREG (param, p[param].part (n)
          .name (T("eq3-q")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_eq3_q))
          .get (MakeDelegate (this, &XSynthParameters::get_part_eq3_q)));

    param = PPAR(n, PP_EQ_HS_G);
    PREG (param, p[param].part (n)
          .name (T("eq4-g")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_eq4_gain))
          .get (MakeDelegate (this, &XSynthParameters::get_part_eq4_gain)));

    param = PPAR(n, PP_EQ_HS_F);
    PREG (param, p[param].part (n)
          .name (T("eq4-f")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_eq4_freq))
          .get (MakeDelegate (this, &XSynthParameters::get_part_eq4_freq)));

    param = PPAR(n, PP_EQ_HS_BW);
    PREG (param, p[param].part (n)
          .name (T("eq4-q")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_eq4_q))
          .get (MakeDelegate (this, &XSynthParameters::get_part_eq4_q)));


    // delay
    param = PPAR(n, PP_DELAY_GAIN);
    PREG (param, p[param].part (n)
          .name (T("dly-g")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_delay_gain))
          .get (MakeDelegate (this, &XSynthParameters::get_part_delay_gain)));

    param = PPAR(n, PP_DELAY_PAN);
    PREG (param, p[param].part (n)
          .name (T("dly-p")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_delay_pan))
          .get (MakeDelegate (this, &XSynthParameters::get_part_delay_pan)));

    param = PPAR(n, PP_DELAY_TIME);
    PREG (param, p[param].part (n)
          .name (T("dly-t")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_delay_time))
          .get (MakeDelegate (this, &XSynthParameters::get_part_delay_time)));

    param = PPAR(n, PP_DELAY_FEED);
    PREG (param, p[param].part (n)
          .name (T("dly-f")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_delay_feed))
          .get (MakeDelegate (this, &XSynthParameters::get_part_delay_feed)));

    param = PPAR(n, PP_DELAY_LP);
    PREG (param, p[param].part (n)
          .name (T("dly-lp")).range (0,1).unit (T("%"))
          .set (MakeDelegate (this, &XSynthParameters::set_part_delay_lp))
          .get (MakeDelegate (this, &XSynthParameters::get_part_delay_lp)));

}

//==============================================================================
float XSynthParameters::get_master_gain (int n)
{
    return master->Pvolume * float_MidiScaler;
}

void XSynthParameters::set_master_gain (int n, float value)
{
    master->setPvolume ((int) (value * 127.0f));
}

//==============================================================================
float XSynthParameters::get_master_solo (int n)
{
    // TODO
    return 0.0f; // master->Psolopart / 16.0f;
}

void XSynthParameters::set_master_solo (int n, float value)
{
    // TODO
    // master->Psolopart = (int) (0.5f + value * 16.0f);
}

//==============================================================================
float XSynthParameters::get_part_enabled (int n)
{
    return (master->part[n]->Penabled == 1) ? 1.0f : 0.0f;
}

void XSynthParameters::set_part_enabled (int n, float value)
{
    master->mutex.enter();
    master->partonoff (n, (int) (value > 0.5f));
    master->mutex.exit();
}

//==============================================================================
float XSynthParameters::get_part_porta (int n)
{
    return (master->part[n]->ctl.portamento.portamento == 1) ? 1.0f : 0.0f;
}

void XSynthParameters::set_part_porta (int n, float value)
{
    master->part[n]->ctl.portamento.portamento = (int) (value > 0.5f);
}

//==============================================================================
float XSynthParameters::get_part_poly (int n)
{
    return (master->part[n]->Ppolymode == 1) ? 1.0f : 0.0f;
}

void XSynthParameters::set_part_poly (int n, float value)
{
    master->part[n]->Ppolymode = (int) (value > 0.5f);
}

//==============================================================================
float XSynthParameters::get_part_stereo (int n)
{
    return (master->part[n]->kit[0].adpars->GlobalPar.PStereo == 1) ? 1.0f : 0.0f;
}

void XSynthParameters::set_part_stereo (int n, float value)
{
    master->part[n]->kit[0].adpars->GlobalPar.PStereo = (int) (value > 0.5f);
}

//==============================================================================
float XSynthParameters::get_part_gain (int n)
{
    return master->part[n]->Pvolume / 127.0f;
}

void XSynthParameters::set_part_gain (int n, float value)
{
    master->part[n]->setPvolume ((int)(value * 127));
}

//==============================================================================
float XSynthParameters::get_part_pan (int n)
{
    return master->part[n]->Ppanning / 127.0f;
}

void XSynthParameters::set_part_pan (int n, float value)
{
    master->part[n]->setPpanning ((int)(value * 127));
}

//==============================================================================
float XSynthParameters::get_part_x (int n)
{
    return master->part[n]->kit[0].adpars->GlobalPar.PJoyX / 127.0f;
}

void XSynthParameters::set_part_x (int n, float value)
{
    Part* part = master->part[n];

    part->kit[0].adpars->GlobalPar.PJoyX = (int) (value * 127.0f);

    float joyX = value,
          joyY =  part->kit[0].adpars->GlobalPar.PJoyY / 127.0f;

    float x0 = (1.0f - joyX) * joyY;          // top-left
    float x1 = joyX * joyY;                   // top-right
    float x2 = (1.0f - joyX) * (1.0f - joyY); // bottom-left
    float x3 = joyX * (1.0f - joyY);          // bottom-right

    part->kit[0].adpars->VoicePar[0].PVolume = (uint8) (120 * pow (x0, 0.125));
    part->kit[0].adpars->VoicePar[1].PVolume = (uint8) (120 * pow (x1, 0.125));
    part->kit[0].adpars->VoicePar[2].PVolume = (uint8) (120 * pow (x2, 0.125));
    part->kit[0].adpars->VoicePar[3].PVolume = (uint8) (120 * pow (x3, 0.125));
}

//==============================================================================
float XSynthParameters::get_part_y (int n)
{
    return 1.0f - master->part[n]->kit[0].adpars->GlobalPar.PJoyY / 127.0f;
}

void XSynthParameters::set_part_y (int n, float value)
{
    Part* part = master->part[n];

    part->kit[0].adpars->GlobalPar.PJoyY = (int) (value * 127.0f);

    float joyX = part->kit[0].adpars->GlobalPar.PJoyX / 127.0f,
          joyY = value;

    float x0 = (1.0f - joyX) * joyY;          // top-left
    float x1 = joyX * joyY;                   // top-right
    float x2 = (1.0f - joyX) * (1.0f - joyY); // bottom-left
    float x3 = joyX * (1.0f - joyY);          // bottom-right

    part->kit[0].adpars->VoicePar[0].PVolume = (uint8) (120 * pow (x0, 0.125));
    part->kit[0].adpars->VoicePar[1].PVolume = (uint8) (120 * pow (x1, 0.125));
    part->kit[0].adpars->VoicePar[2].PVolume = (uint8) (120 * pow (x2, 0.125));
    part->kit[0].adpars->VoicePar[3].PVolume = (uint8) (120 * pow (x3, 0.125));
}

//==============================================================================
float XSynthParameters::get_part_amp_attack (int n)
{
    return master->part[n]->kit[0].adpars->GlobalPar.AmpEnvelope->PA_dt / 127.0f;
}

void XSynthParameters::set_part_amp_attack (int n, float value)
{
    master->part[n]->kit[0].adpars->GlobalPar.AmpEnvelope->PA_dt = (int) (value * 127.0f);
    master->part[n]->kit[0].adpars->GlobalPar.AmpEnvelope->converttofree ();
}

//==============================================================================
float XSynthParameters::get_part_amp_decay (int n)
{
    return master->part[n]->kit[0].adpars->GlobalPar.AmpEnvelope->PD_dt / 127.0f;
}

void XSynthParameters::set_part_amp_decay (int n, float value)
{
    master->part[n]->kit[0].adpars->GlobalPar.AmpEnvelope->PD_dt = (int) (value * 127.0f);
    master->part[n]->kit[0].adpars->GlobalPar.AmpEnvelope->converttofree ();
}

//==============================================================================
float XSynthParameters::get_part_amp_sustain (int n)
{
    return master->part[n]->kit[0].adpars->GlobalPar.AmpEnvelope->PS_val / 127.0f;
}

void XSynthParameters::set_part_amp_sustain (int n, float value)
{
    master->part[n]->kit[0].adpars->GlobalPar.AmpEnvelope->PS_val = (int) (value * 127.0f);
    master->part[n]->kit[0].adpars->GlobalPar.AmpEnvelope->converttofree ();
}

//==============================================================================
float XSynthParameters::get_part_amp_release (int n)
{
    return master->part[n]->kit[0].adpars->GlobalPar.AmpEnvelope->PR_dt / 127.0f;
}

void XSynthParameters::set_part_amp_release (int n, float value)
{
    master->part[n]->kit[0].adpars->GlobalPar.AmpEnvelope->PR_dt = (int) (value * 127.0f);
    master->part[n]->kit[0].adpars->GlobalPar.AmpEnvelope->converttofree ();
}

//==============================================================================
float XSynthParameters::get_part_tone (int n)
{
    int k = master->part[n]->kit[0].adpars->GlobalPar.PCoarseDetune % 1024;
    if (k >= 512) k -= 1024;
    return (k / 127.0f) + 0.5f;
}

//==============================================================================
void XSynthParameters::set_part_tone (int n, float value)
{
    int k = (int)((value - 0.5f) * 127);
    if (k < 0) k += 1024;
    master->part[n]->kit[0].adpars->GlobalPar.PCoarseDetune =
            k + (master->part[n]->kit[0].adpars->GlobalPar.PCoarseDetune / 1024) * 1024;
}

//==============================================================================
float XSynthParameters::get_part_finetune (int n)
{
    return master->part[n]->kit[0].adpars->GlobalPar.PDetune / 16384.0f;
}

void XSynthParameters::set_part_finetune (int n, float value)
{
    master->part[n]->kit[0].adpars->GlobalPar.PDetune = (int)((value - 0.5f) * 16384) + 8192;
}

//==============================================================================
float XSynthParameters::get_part_tone_attack (int n)
{
    return master->part[n]->kit[0].adpars->GlobalPar.FreqEnvelope->PA_val / 127.0f;
}

void XSynthParameters::set_part_tone_attack (int n, float value)
{
    master->part[n]->kit[0].adpars->GlobalPar.FreqEnvelope->PA_val = (int)(value * 127);
    master->part[n]->kit[0].adpars->GlobalPar.FreqEnvelope->converttofree();
}

//==============================================================================
float XSynthParameters::get_part_tone_attacktime (int n)
{
    return master->part[n]->kit[0].adpars->GlobalPar.FreqEnvelope->PA_dt / 127.0f;
}

void XSynthParameters::set_part_tone_attacktime (int n, float value)
{
    master->part[n]->kit[0].adpars->GlobalPar.FreqEnvelope->PA_dt = (int)(value * 127);
    master->part[n]->kit[0].adpars->GlobalPar.FreqEnvelope->converttofree();
}

//==============================================================================
float XSynthParameters::get_part_tone_decay (int n)
{
    return master->part[n]->kit[0].adpars->GlobalPar.FreqEnvelope->PD_val / 127.0f;
}

void XSynthParameters::set_part_tone_decay (int n, float value)
{
    master->part[n]->kit[0].adpars->GlobalPar.FreqEnvelope->PD_val = (int)(value * 127);
    master->part[n]->kit[0].adpars->GlobalPar.FreqEnvelope->converttofree();
}

//==============================================================================
float XSynthParameters::get_part_tone_decaytime (int n)
{
    return master->part[n]->kit[0].adpars->GlobalPar.FreqEnvelope->PD_dt / 127.0f;
}

void XSynthParameters::set_part_tone_decaytime (int n, float value)
{
    master->part[n]->kit[0].adpars->GlobalPar.FreqEnvelope->PD_dt = (int)(value * 127);
    master->part[n]->kit[0].adpars->GlobalPar.FreqEnvelope->converttofree();
}

//==============================================================================
float XSynthParameters::get_part_tone_release (int n)
{
    return master->part[n]->kit[0].adpars->GlobalPar.FreqEnvelope->PR_val / 127.0f;
}

void XSynthParameters::set_part_tone_release (int n, float value)
{
    master->part[n]->kit[0].adpars->GlobalPar.FreqEnvelope->PR_val = (int)(value * 127);
    master->part[n]->kit[0].adpars->GlobalPar.FreqEnvelope->converttofree();
}

//==============================================================================
float XSynthParameters::get_part_tone_releasetime (int n)
{
    return master->part[n]->kit[0].adpars->GlobalPar.FreqEnvelope->PR_dt / 127.0f;
}

void XSynthParameters::set_part_tone_releasetime (int n, float value)
{
    master->part[n]->kit[0].adpars->GlobalPar.FreqEnvelope->PR_dt = (int)(value * 127);
    master->part[n]->kit[0].adpars->GlobalPar.FreqEnvelope->converttofree();
}

//==============================================================================
float XSynthParameters::get_part_noise (int n)
{
    return master->part[n]->kit[0].adpars->VoicePar[4].PVolume / 127.0f;
}

void XSynthParameters::set_part_noise (int n, float value)
{
    master->part[n]->kit[0].adpars->VoicePar[4].PVolume = (int)(value * 127);
}

//==============================================================================
float XSynthParameters::get_part_filter_cutoff (int n)
{
    return master->part[n]->kit[0].adpars->GlobalPar.GlobalFilter->Pfreq / 127.0f;
}

void XSynthParameters::set_part_filter_cutoff (int n, float value)
{
    master->part[n]->kit[0].adpars->GlobalPar.GlobalFilter->Pfreq = (int) (value * 127.0f);
    master->part[n]->kit[0].adpars->GlobalPar.GlobalFilter->changed = true;
}

//==============================================================================
float XSynthParameters::get_part_filter_reso (int n)
{
    return master->part[n]->kit[0].adpars->GlobalPar.GlobalFilter->Pq / 127.0f;
}

void XSynthParameters::set_part_filter_reso (int n, float value)
{
    master->part[n]->kit[0].adpars->GlobalPar.GlobalFilter->Pq = (int) (value * 127.0f);
    master->part[n]->kit[0].adpars->GlobalPar.GlobalFilter->changed = true;
}

//==============================================================================
float XSynthParameters::get_part_filter_type (int n)
{
    return (master->part[n]->kit[0].adpars->GlobalPar.GlobalFilter->Ptype - 2) / 3.0f - 0.5f;
}

void XSynthParameters::set_part_filter_type (int n, float value)
{
    master->part[n]->kit[0].adpars->GlobalPar.GlobalFilter->Ptype = (int) ((value + 0.5f) * 3) + 2;
    master->part[n]->kit[0].adpars->GlobalPar.GlobalFilter->changed = true;
}

//==============================================================================
float XSynthParameters::get_part_filter_track (int n)
{
    return master->part[n]->kit[0].adpars->GlobalPar.GlobalFilter->Pfreqtrack / 127.0f;
}

void XSynthParameters::set_part_filter_track (int n, float value)
{
    master->part[n]->kit[0].adpars->GlobalPar.GlobalFilter->Pfreqtrack = (int) (value * 127.0f);
    master->part[n]->kit[0].adpars->GlobalPar.GlobalFilter->changed = true;
}

//==============================================================================
float XSynthParameters::get_part_filter_lfodepth (int n)
{
    return master->part[n]->kit[0].adpars->GlobalPar.FilterLfo->Pintensity / 127.0f;
}

void XSynthParameters::set_part_filter_lfodepth (int n, float value)
{
    master->part[n]->kit[0].adpars->GlobalPar.FilterLfo->Pintensity = (int) (value * 127.0f);
}

//==============================================================================
float XSynthParameters::get_part_filter_lfofreq (int n)
{
    return (master->part[n]->kit[0].adpars->GlobalPar.FilterLfo->Pfreq - 0.0001) / 50.0f;
}

void XSynthParameters::set_part_filter_lfofreq (int n, float value)
{
    master->part[n]->kit[0].adpars->GlobalPar.FilterLfo->Pfreq = 0.0001 + (value * 50.0f);
}

//==============================================================================
float XSynthParameters::get_part_filter_lfodelay (int n)
{
    return master->part[n]->kit[0].adpars->GlobalPar.FilterLfo->Pdelay / 127.0f;
}

void XSynthParameters::set_part_filter_lfodelay (int n, float value)
{
    master->part[n]->kit[0].adpars->GlobalPar.FilterLfo->Pdelay = (int) (value * 127.0f);
}




//==============================================================================
float XSynthParameters::get_part_filter_attack (int n)
{
    return master->part[n]->kit[0].adpars->GlobalPar.FilterEnvelope->PA_val / 127.0f;
}

void XSynthParameters::set_part_filter_attack (int n, float value)
{
    master->part[n]->kit[0].adpars->GlobalPar.FilterEnvelope->PA_val = (int) (value * 127.0f);
    master->part[n]->kit[0].adpars->GlobalPar.FilterEnvelope->converttofree();
    master->part[n]->kit[0].adpars->GlobalPar.GlobalFilter->changed = true;
}

//==============================================================================
float XSynthParameters::get_part_filter_attacktime (int n)
{
    return master->part[n]->kit[0].adpars->GlobalPar.FilterEnvelope->PA_dt / 127.0f;
}

void XSynthParameters::set_part_filter_attacktime (int n, float value)
{
    master->part[n]->kit[0].adpars->GlobalPar.FilterEnvelope->PA_dt = (int) (value * 127.0f);
    master->part[n]->kit[0].adpars->GlobalPar.FilterEnvelope->converttofree();
    master->part[n]->kit[0].adpars->GlobalPar.GlobalFilter->changed = true;
}

//==============================================================================
float XSynthParameters::get_part_filter_decay (int n)
{
    return master->part[n]->kit[0].adpars->GlobalPar.FilterEnvelope->PD_val / 127.0f;
}

void XSynthParameters::set_part_filter_decay (int n, float value)
{
    master->part[n]->kit[0].adpars->GlobalPar.FilterEnvelope->PD_val = (int) (value * 127.0f);
    master->part[n]->kit[0].adpars->GlobalPar.FilterEnvelope->converttofree();
    master->part[n]->kit[0].adpars->GlobalPar.GlobalFilter->changed = true;
}

//==============================================================================
float XSynthParameters::get_part_filter_decaytime (int n)
{
    return master->part[n]->kit[0].adpars->GlobalPar.FilterEnvelope->PD_dt / 127.0f;
}

void XSynthParameters::set_part_filter_decaytime (int n, float value)
{
    master->part[n]->kit[0].adpars->GlobalPar.FilterEnvelope->PD_dt = (int) (value * 127.0f);
    master->part[n]->kit[0].adpars->GlobalPar.FilterEnvelope->converttofree();
    master->part[n]->kit[0].adpars->GlobalPar.GlobalFilter->changed = true;
}

//==============================================================================
float XSynthParameters::get_part_chorus_gain (int n)
{
    return master->part[n]->partefx [0]->getEffectParameter (0) / 127.0f;
}

void XSynthParameters::set_part_chorus_gain (int n, float value)
{
    master->part[n]->partefx [0]->setEffectParameter (0, (int)(value * 127));
}

float XSynthParameters::get_part_chorus_freq (int n)
{
    return master->part[n]->partefx [0]->getEffectParameter (2) / 127.0f;
}

void XSynthParameters::set_part_chorus_freq (int n, float value)
{
    master->part[n]->partefx [0]->setEffectParameter (2, (int)(value * 127));
}

float XSynthParameters::get_part_chorus_delay (int n)
{
    return master->part[n]->partefx [0]->getEffectParameter (7) / 127.0f;
}

void XSynthParameters::set_part_chorus_delay (int n, float value)
{
    master->part[n]->partefx [0]->setEffectParameter (7, (int)(value * 127));
}

float XSynthParameters::get_part_chorus_depth (int n)
{
    return master->part[n]->partefx [0]->getEffectParameter (6) / 127.0f;
}

void XSynthParameters::set_part_chorus_depth (int n, float value)
{
    master->part[n]->partefx [0]->setEffectParameter (6, (int)(value * 127));
}

float XSynthParameters::get_part_chorus_feed (int n)
{
    return master->part[n]->partefx [0]->getEffectParameter (8) / 127.0f;
}

void XSynthParameters::set_part_chorus_feed (int n, float value)
{
    master->part[n]->partefx [0]->setEffectParameter (8, (int)(value * 127));
}

//==============================================================================
float XSynthParameters::get_part_drive (int n)
{
    return (master->part[n]->partefx [1]->getEffectParameter (3) - 64.0f) / 64.0f;
}

void XSynthParameters::set_part_drive (int n, float value)
{
    master->part[n]->partefx [1]->setEffectParameter (3, (int)(value * 64.0f + 64.0f));
}

float XSynthParameters::get_part_drive_lp (int n)
{
    return master->part[n]->partefx [1]->getEffectParameter (7) / 127.0f;
}

void XSynthParameters::set_part_drive_lp (int n, float value)
{
    master->part[n]->partefx [1]->setEffectParameter (7, (int)(value * 127));
}

float XSynthParameters::get_part_drive_hp (int n)
{
    return master->part[n]->partefx [1]->getEffectParameter (8) / 127.0f;
}

void XSynthParameters::set_part_drive_hp (int n, float value)
{
    master->part[n]->partefx [1]->setEffectParameter (8, (int)(value * 127));
}

//==============================================================================
float XSynthParameters::get_part_eq1_gain (int n)
{
    int band = 0;
    return master->part[n]->partefx [2]->getEffectParameter (band * 5 + 12) / 127.0f;
}

void XSynthParameters::set_part_eq1_gain (int n, float value)
{
    int band = 0;
    master->part[n]->partefx [2]->setEffectParameter ((band * 5 + 12), (int)(value * 127));
}

float XSynthParameters::get_part_eq1_freq (int n)
{
    int band = 0;
    return master->part[n]->partefx [2]->getEffectParameter (band * 5 + 11) / 127.0f;
}

void XSynthParameters::set_part_eq1_freq (int n, float value)
{
    int band = 0;
    master->part[n]->partefx [2]->setEffectParameter ((band * 5 + 11), (int)(value * 127));
}

float XSynthParameters::get_part_eq1_q (int n)
{
    int band = 0;
    return master->part[n]->partefx [2]->getEffectParameter (band * 5 + 13) / 127.0f;
}

void XSynthParameters::set_part_eq1_q (int n, float value)
{
    int band = 0;
    master->part[n]->partefx [2]->setEffectParameter ((band * 5 + 13), (int)(value * 127));
}

float XSynthParameters::get_part_eq2_gain (int n)
{
    int band = 1;
    return master->part[n]->partefx [2]->getEffectParameter (band * 5 + 12) / 127.0f;
}

void XSynthParameters::set_part_eq2_gain (int n, float value)
{
    int band = 1;
    master->part[n]->partefx [2]->setEffectParameter ((band * 5 + 12), (int)(value * 127));
}

float XSynthParameters::get_part_eq2_freq (int n)
{
    int band = 1;
    return master->part[n]->partefx [2]->getEffectParameter (band * 5 + 11) / 127.0f;
}

void XSynthParameters::set_part_eq2_freq (int n, float value)
{
    int band = 1;
    master->part[n]->partefx [2]->setEffectParameter ((band * 5 + 11), (int)(value * 127));
}

float XSynthParameters::get_part_eq2_q (int n)
{
    int band = 1;
    return master->part[n]->partefx [2]->getEffectParameter (band * 5 + 13) / 127.0f;
}

void XSynthParameters::set_part_eq2_q (int n, float value)
{
    int band = 1;
    master->part[n]->partefx [2]->setEffectParameter ((band * 5 + 13), (int)(value * 127));
}

float XSynthParameters::get_part_eq3_gain (int n)
{
    int band = 2;
    return master->part[n]->partefx [2]->getEffectParameter (band * 5 + 12) / 127.0f;
}

void XSynthParameters::set_part_eq3_gain (int n, float value)
{
    int band = 2;
    master->part[n]->partefx [2]->setEffectParameter ((band * 5 + 12), (int)(value * 127));
}

float XSynthParameters::get_part_eq3_freq (int n)
{
    int band = 2;
    return master->part[n]->partefx [2]->getEffectParameter (band * 5 + 11) / 127.0f;
}

void XSynthParameters::set_part_eq3_freq (int n, float value)
{
    int band = 2;
    master->part[n]->partefx [2]->setEffectParameter ((band * 5 + 11), (int)(value * 127));
}

float XSynthParameters::get_part_eq3_q (int n)
{
    int band = 2;
    return master->part[n]->partefx [2]->getEffectParameter (band * 5 + 13) / 127.0f;
}

void XSynthParameters::set_part_eq3_q (int n, float value)
{
    int band = 2;
    master->part[n]->partefx [2]->setEffectParameter ((band * 5 + 13), (int)(value * 127));
}

float XSynthParameters::get_part_eq4_gain (int n)
{
    int band = 3;
    return master->part[n]->partefx [2]->getEffectParameter (band * 5 + 12) / 127.0f;
}

void XSynthParameters::set_part_eq4_gain (int n, float value)
{
    int band = 3;
    master->part[n]->partefx [2]->setEffectParameter ((band * 5 + 12), (int)(value * 127));
}

float XSynthParameters::get_part_eq4_freq (int n)
{
    int band = 3;
    return master->part[n]->partefx [2]->getEffectParameter (band * 5 + 11) / 127.0f;
}

void XSynthParameters::set_part_eq4_freq (int n, float value)
{
    int band = 3;
    master->part[n]->partefx [2]->setEffectParameter ((band * 5 + 11), (int)(value * 127));
}

float XSynthParameters::get_part_eq4_q (int n)
{
    int band = 3;
    return master->part[n]->partefx [2]->getEffectParameter (band * 5 + 13) / 127.0f;
}

void XSynthParameters::set_part_eq4_q (int n, float value)
{
    int band = 3;
    master->part[n]->partefx [2]->setEffectParameter ((band * 5 + 13), (int)(value * 127));
}


//==============================================================================
float XSynthParameters::get_part_delay_gain (int n)
{
    return master->part[n]->partefx [3]->getEffectParameter (0) / 127.0f;
}

void XSynthParameters::set_part_delay_gain (int n, float value)
{
    master->part[n]->partefx [3]->setEffectParameter (0, (int)(value * 127));
}

float XSynthParameters::get_part_delay_pan (int n)
{
    return master->part[n]->partefx [3]->getEffectParameter (1) / 127.0f;
}

void XSynthParameters::set_part_delay_pan (int n, float value)
{
    master->part[n]->partefx [3]->setEffectParameter (1, (int)(value * 127));
}

float XSynthParameters::get_part_delay_time (int n)
{
    return master->part[n]->partefx [3]->getEffectParameter (2) / 127.0f;
}

void XSynthParameters::set_part_delay_time (int n, float value)
{
    master->part[n]->partefx [3]->setEffectParameter (2, (int)(value * 127));
}

float XSynthParameters::get_part_delay_feed (int n)
{
    return master->part[n]->partefx [3]->getEffectParameter (5) / 127.0f;
}

void XSynthParameters::set_part_delay_feed (int n, float value)
{
    master->part[n]->partefx [3]->setEffectParameter (5, (int)(value * 127));
}

float XSynthParameters::get_part_delay_lp (int n)
{
    return master->part[n]->partefx [3]->getEffectParameter (6) / 127.0f;
}

void XSynthParameters::set_part_delay_lp (int n, float value)
{
    master->part[n]->partefx [3]->setEffectParameter (6, (int)(value * 127));
}
