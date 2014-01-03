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

#ifndef CVOICE_H
#define CVOICE_H

#include "cTblOSC.h"
#include "cTblLFO.h"
#include "cADSR.h"      //ADSR for per buffer processing
#include "cAmpADSR.h"   //ampADSR class does buffer based per sample processing
#include "../parameters.h"

class cVoice {

private:

     ParMan * Pars;

     cTblOSC * osc1;
     cTblOSC * osc2;
     cAmpADSR * ampADSR;
     cADSR * filterADSR;
     cADSR * pitchADSR;
     cTblLFO * filterLFO;
     cTblLFO * pitchLFO;
     cTblLFO * ampLFO;

     bool isOn,  isReleased;
     int note;

     int Ordinal;

     float velocity;
     float SampleRate, BaseFrequency;

     float buf0, buf1; //for the pre-filter
     float low, f, band, high, q, notch; //main Filter
     float low1, band1, high1, notch1; //main Filter
     float a, b, c; //for the shelving-filter
     float * currentFilter;
     float * currentFilter1;

     float Buffer[32];
     float plfo;
     float padsr;
     float pitchMod;
     float cut;
     float ampMod;
     int tmpCount;
     float cutNyq;

public:

     cVoice(ParMan * P, float sr = 44100)
     {
          Pars = P;

          osc1 = new cTblOSC(1);
          osc2 = new cTblOSC(1);
          ampADSR =  new cAmpADSR();
          filterADSR = new cADSR();
          pitchADSR = new cADSR();
          filterLFO = new cTblLFO();
          pitchLFO = new cTblLFO();
          ampLFO = new cTblLFO();

          Ordinal = 1;
          SampleRate = sr;
          isOn = false;

          note = 0;

          buf0 = 0.0f;
          buf1 = 0.0f;

          low = 0.0f;
          f = 0.0f;
          band = 0.0f;
          high = 0.0f;
          q = 0.0f;
          notch = 0.0f;
          currentFilter = &low;
    }

    ~cVoice()
    {
          delete osc1;
          delete osc2;
          delete ampADSR;
          delete filterADSR;
          delete pitchADSR;
          delete filterLFO;
          delete pitchLFO;
          delete ampLFO;
    }

    void doProcess (float * outBuffer, int size)
    {
          if(!isOn){ return; }

          int over_size = size * 2;

          plfo = pitchLFO->doProcess (over_size);
          padsr = pitchADSR->doProcess (over_size);

          //Pitch Modulation*****Optimize
          pitchMod = (Pars->getParameter(ParMan::o1_cent) * 0.04f);
          pitchMod += Pars->getParameter(ParMan::o1_semi);
          pitchMod += padsr * Pars->getParameter(ParMan::penv_amt) * Pars->getParameter(ParMan::o1_env);
          pitchMod += plfo* Pars->getParameter(ParMan::plfo_amt) * Pars->getParameter(ParMan::o1_lfo);
          pitchMod += velocity * Pars->getParameter(ParMan::vel_pitch);
          osc1->setFrequency(BaseFrequency * convertPitch(pitchMod), SampleRate * 2, BaseFrequency);

          pitchMod = (Pars->getParameter(ParMan::o2_cent) * 0.04f);
          pitchMod += Pars->getParameter(ParMan::o2_semi);
          pitchMod += padsr * Pars->getParameter(ParMan::penv_amt) * Pars->getParameter(ParMan::o2_env);
          pitchMod += plfo * Pars->getParameter(ParMan::plfo_amt) * Pars->getParameter(ParMan::o2_lfo);
          pitchMod += velocity * Pars->getParameter(ParMan::vel_pitch);
          osc2->setFrequency(BaseFrequency * convertPitch(pitchMod), SampleRate * 2, BaseFrequency);

          //Render Wave
          osc1->doProcess (Buffer, over_size);
          osc2->doProcess (Buffer, over_size, Pars->getParameter(ParMan::o_mix) + (padsr * Pars->getParameter(ParMan::penv_amt) * Pars->getParameter(ParMan::o_env))  + (plfo * Pars->getParameter(ParMan::plfo_amt) * Pars->getParameter(ParMan::o_lfo)));

          //Cut frequencies
          cut =  f + filterADSR->doProcess(over_size) * Pars->getParameter(ParMan::fenv_amt) * 0.5f;
          cut += filterLFO->doProcess(over_size) * Pars->getParameter(ParMan::flfo_amt) * 0.5f;
          cut += velocity * Pars->getParameter(ParMan::vel_filter) * 0.5f;
          cut =  jlimit(0.001f, 0.999f, cut);

          ampMod = Pars->getParameter(ParMan::aenv_amt) + (ampLFO->doProcess(over_size) * Pars->getParameter(ParMan::alfo_amt));
          ampMod += (velocity - 1.0f) * 0.5f * Pars->getParameter(ParMan::vel_amp);

          //Processing Loop
          for(int i = 0; i < over_size; i++)
          {
               //Saturator
               Buffer[i] = 1e-20 + ((1.5f * Buffer[i] - 0.5f * Buffer[i] * Buffer[i] * Buffer[i]) * Pars->getParameter(ParMan::f_sat))
                           + (Buffer[i] *  (1.0f - Pars->getParameter(ParMan::f_sat)));

               //Main Filter
               low = low + cut * band;
               high =  Buffer[i] - low - q * band;
               band = cut * high + band;
               notch = high + low;
               Buffer[i] = (*currentFilter) * ((q * 0.5f) + 0.5f);

               low1 = low1 + cut * band1;
               high1 =  Buffer[i] - low1 - q * band1;
               band1 = cut * high1 + band1;
               notch1 = high1 + low1;
               Buffer[i] = (*currentFilter1) * ((q * 0.5f) + 0.5f);


               //Shelving 120hz
               //output = highpass * (input - a) + high * (a - b) + low * (b - c) + lowpass * c;
               a += (13312.0f / SampleRate) * (Buffer[i] - a);
               b += (1664.00f / SampleRate) * (Buffer[i] - b);
               c += (104.000f / SampleRate) * (Buffer[i] - c);
               Buffer[i] = 2.0f * (Buffer[i] - a) + 1.0f * (a - b) + 1.0f * (b - c) + ((Pars->getParameter(ParMan::f_80) + 1.0f) * 4.0f) * c;

               //Saturator
               Buffer[i] = ((1.5f * Buffer[i] - 0.5f * Buffer[i] * Buffer[i] * Buffer[i]) * Pars->getParameter(ParMan::f_sat))
                           + (Buffer[i] *  (1.0f - Pars->getParameter(ParMan::f_sat)));
          }

          ampADSR->doProcess (Buffer, over_size); //Apply amp envelope

          tmpCount = 0;
          cutNyq = 2 * float_Pi * (15000 / (SampleRate * 2));
          for(int i = 0; i < size; i++)
          {
               //Pre Filter /Anti-Aliasing
               buf0 = buf0 + cutNyq * (Buffer[tmpCount] - buf0);
               buf1 = buf1 + cutNyq * (buf0 - buf1);
               Buffer[tmpCount] = buf1  * ampMod + 1e-20;
               //second sample
               buf0 = buf0 + cutNyq * (Buffer[tmpCount+1] - buf0);
               buf1 = buf1 + cutNyq * (buf0 - buf1);
               Buffer[tmpCount+1] = buf1  * ampMod + 1e-20;

               outBuffer[i] += (Buffer[tmpCount] + Buffer[tmpCount+1]) * 0.5f;
               tmpCount += 2;
          }
          isOn = ampADSR->getState();
     }

     void start(float f, float v, int n, int preroll, float s, int o)
     {
          Ordinal = o;
          SampleRate = s;
          BaseFrequency = f;

          osc1->reset(BaseFrequency * convertPitch(Pars->getParameter(ParMan::o1_cent) * 0.04f) + Pars->getParameter(ParMan::o1_semi), SampleRate * 2, BaseFrequency);
          osc2->reset(BaseFrequency * convertPitch(Pars->getParameter(ParMan::o2_cent) * 0.04f) + Pars->getParameter(ParMan::o2_semi), SampleRate * 2, BaseFrequency);
          note = n;

          isOn = true; isReleased = false;
          velocity  = v;
          ampADSR->reset(preroll);
          filterADSR->reset(); pitchADSR->reset();
          filterLFO->reset(); pitchLFO->reset();
     }

     void release(int p)
     {
         isReleased = true;
         ampADSR->release(p);
         filterADSR->release(); pitchADSR->release();
     }

     void quickRelease(){
         isReleased = true;
         ampADSR->quickRelease();
     }

     int getOrdinal(){
          return Ordinal;
     }

     void kill(){
         isOn = false;
     }

     void update(int index)
     {
          switch (index) {
           case ParMan::o1_wave: osc1->setOscTbl((int)Pars->getParameter(ParMan::o1_wave)); break;
           case ParMan::o2_wave: osc2->setOscTbl((int)Pars->getParameter(ParMan::o2_wave)); break;

           case ParMan::aenv_a:
           case ParMan::aenv_d:
           case ParMan::aenv_s:
           case ParMan::aenv_r: ampADSR->setADSR(Pars->getParameter(ParMan::aenv_a), Pars->getParameter(ParMan::aenv_d), Pars->getParameter(ParMan::aenv_s), Pars->getParameter(ParMan::aenv_r), SampleRate); break;

           case ParMan::fenv_a:
           case ParMan::fenv_d:
           case ParMan::fenv_s:
           case ParMan::fenv_r: filterADSR->setADSR(Pars->getParameter(ParMan::fenv_a), Pars->getParameter(ParMan::fenv_d), Pars->getParameter(ParMan::fenv_s), Pars->getParameter(ParMan::fenv_r), SampleRate); break;

           case ParMan::penv_a:
           case ParMan::penv_d:
           case ParMan::penv_s:
           case ParMan::penv_r: pitchADSR->setADSR(Pars->getParameter(ParMan::penv_a), Pars->getParameter(ParMan::penv_d), Pars->getParameter(ParMan::penv_s), Pars->getParameter(ParMan::penv_r), SampleRate); break;

           case ParMan::alfo_wave: ampLFO->setLFOTbl(int(Pars->getParameter(ParMan::alfo_wave) * 2) + 1);break;
           case ParMan::flfo_wave: filterLFO->setLFOTbl(int(Pars->getParameter(ParMan::flfo_wave) * 2) + 1);break;
           case ParMan::plfo_wave: pitchLFO->setLFOTbl(int(Pars->getParameter(ParMan::plfo_wave) * 2) + 1); break;

           case ParMan::alfo_spd: ampLFO->setSpeed(Pars->getParameter(ParMan::alfo_spd), SampleRate * 2);       break;
           case ParMan::flfo_spd: filterLFO->setSpeed(Pars->getParameter(ParMan::flfo_spd), SampleRate * 2);    break;
           case ParMan::plfo_spd: pitchLFO->setSpeed(Pars->getParameter(ParMan::plfo_spd), SampleRate * 2);     break;

           case ParMan::f_cut:   f = Pars->getParameter(ParMan::f_cut) * 0.5f;     break;
           case ParMan::f_res:   q = 1.1f - Pars->getParameter(ParMan::f_res);     break;

           case ParMan::f_wave:
                if ((int)Pars->getParameter(ParMan::f_wave) == 1) {  currentFilter = &low; currentFilter1 = &low1;      }
                if ((int)Pars->getParameter(ParMan::f_wave) == 2) {  currentFilter = &high; currentFilter1 = &high1;     }
                if ((int)Pars->getParameter(ParMan::f_wave) == 3) {  currentFilter = &band; currentFilter1 = &band1;     }
                if ((int)Pars->getParameter(ParMan::f_wave) == 4) {  currentFilter = &notch;currentFilter1 = &notch1;    }
               break;
           case ParMan::o1_sync: osc1->setSync((Pars->getParameter(ParMan::o1_sync) > 0.5f)); break;
           case ParMan::f_80: break;
          }
     }

     int getNote(){
         return note;
     }

     bool getIsOn(){
         return isOn;
     }

     bool getIsReleased(){
         return isReleased;
     }

     inline float convertPitch(float pitch)
     {
          long convert;
          float *p=(float *)&convert;
          float fl,fr,warp,out;

          fl = floor(pitch);
          fr = pitch - fl;
          warp = fr*0.696f + fr*fr*0.225f + fr*fr*fr*0.079f; // chebychev approx

          out = fl+warp;
          out *= 8388608.0; //2^23;
          out += 127.0 * 8388608.0; //2^23;

          convert = (long)out; //magic

          return *p;
     }
};

#endif
