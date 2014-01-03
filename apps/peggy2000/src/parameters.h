/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2008 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2008 by Julian Storer.

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

   @author  rockhardbuns
   @tweaker Lucio Asnaghi

 ==============================================================================
*/

#ifndef __JUCETICE_PEGGY2000_PARAMETERS_HEADER__
#define __JUCETICE_PEGGY2000_PARAMETERS_HEADER__

#include "StandardHeader.h"


class ParMan
{
public:

     enum
     {
         penv_a,
         penv_d,
         penv_s,
         penv_r,
         fenv_a,
         fenv_d, 
         fenv_s,
         fenv_r,
         aenv_a,
         aenv_d,
         aenv_s,
         aenv_r,
         aenv_amt,
         plfo_spd,
         plfo_amt,
         flfo_spd,
         flfo_amt,
         alfo_spd,
         alfo_amt,
         f_sat,
         f_res,
         f_cut,
         ch_spd,
         ch_dph,
         ch_mix,
         dl_tme,
         dl_lvl,
         dl_fb,
         g_sus,
         m_vol,
         g_swn,
         penv_amt,
         fenv_amt,
         g_len,
         f_80,
         vel_filter,
         vel_pitch,
         vel_amp,
         o1_cent,
         o2_cent,
         o_mix,
         o1_semi,
         o2_semi,
         o2_wave,
         o1_wave,
         g_tempo,
         g_mode,
         f_wave,
         plfo_wave,
         flfo_wave,
         alfo_wave,
         o2_env,
         o1_env,
         o1_lfo,
         o2_lfo,
         o1_sync,
         o_env,
         o_lfo,
         g_on,
         g_g1,
         g_g2,
         g_g3,
         g_g4,
         g_f1,
         g_f2,
         g_f3,
         g_f4,
         g_f5,
         g_f6,
         g_f7,
         g_f8,
         g_f9,
         g_f10,
         g_f11,
         g_f12,
         g_f13,
         g_f14,
         g_f15,
         g_f16
     };

     ParMan(){
          numPars = 81;
          pars = new float[numPars];
          loadPreset(0);
     }

     ~ParMan(){
          delete [] pars;
     }

     inline float getParameter(int i){
          i = jlimit(0, numPars, i);
          return pars[i];
     }

     int getNumPars(){
          return numPars;
     }

     void setParameter(int i, float v){
          i = jlimit(0, numPars, i);
          pars[i] = v;
     }

     bool loadPreset(int i = 0){
          if (i == 0){
               pars[0] = 0.000000f;
               pars[1] = 0.192871f;
               pars[2] = 0.000000f;
               pars[3] = 0.000000f;
               pars[4] = 0.000000f;
               pars[5] = 0.041608f;
               pars[6] = 0.000000f;
               pars[7] = 0.000000f;
               pars[8] = 0.000000f;
               pars[9] = 0.000000f;
               pars[10] = 1.000000f;
               pars[11] = 0.000000f;
               pars[12] = 0.340000f;
               pars[13] = 0.052000f;
               pars[14] = 0.011537f;
               pars[15] = 0.000000f;
               pars[16] = 0.000000f;
               pars[17] = 0.000000f;
               pars[18] = 0.000000f;
               pars[19] = 0.000000f;
               pars[20] = 0.120000f;
               pars[21] = 0.029057f;
               pars[22] = 0.164000f;
               pars[23] = 0.320000f;
               pars[24] = 0.516000f;
               pars[25] = 0.496000f;
               pars[26] = 0.296000f;
               pars[27] = 0.144000f;
               pars[28] = 0.532000f;
               pars[29] = 0.192000f;
               pars[30] = 0.000000f;
               pars[31] = 0.000000f;
               pars[32] = 0.168000f;
               pars[33] = 8.000000f;
               pars[34] = 0.624000f;
               pars[35] = 0.696000f;
               pars[36] = 0.000000f;
               pars[37] = 0.456000f;
               pars[38] = 0.000000f;
               pars[39] = 0.000000f;
               pars[40] = 0.000000f;
               pars[41] = 0.000000f;
               pars[42] = 0.000000f;
               pars[43] = 1.000000f;
               pars[44] = 1.000000f;
               pars[45] = 3.000000f;
               pars[46] = 1.000000f;
               pars[47] = 1.000000f;
               pars[48] = 1.000000f;
               pars[49] = 0.000000f;
               pars[50] = 0.000000f;
               pars[51] = 0.000000f;
               pars[52] = 0.000000f;
               pars[53] = 0.000000f;
               pars[54] = 1.000000f;
               pars[55] = 0.000000f;
               pars[56] = 0.000000f;
               pars[57] = 0.000000f;
               pars[58] = 0.000000f;
               pars[59] = 0.000000f;
               pars[60] = 0.000000f;
               pars[61] = 0.000000f;
               pars[62] = 0.000000f;
               pars[63] = 0.000000f;
               pars[64] = 0.000000f;
               pars[65] = 0.000000f;
               pars[66] = 0.000000f;
               pars[67] = 0.000000f;
               pars[68] = 0.000000f;
               pars[69] = 0.000000f;
               pars[70] = 0.000000f;
               pars[71] = 0.000000f;
               pars[72] = 0.000000f;
               pars[73] = 0.000000f;
               pars[74] = 0.000000f;
               pars[75] = 0.000000f;
               pars[76] = 0.000000f;
               pars[77] = 0.000000f;
               pars[78] = 0.000000f;
               pars[79] = 0.000000f;
               pars[80] = 0.000000f;
               return true;
          }

        return false;
     }

private:

     int numPars;
     float * pars;
};


#endif
