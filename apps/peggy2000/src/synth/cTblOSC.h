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

#ifndef CTBLOSC_H
#define CTBLOSC_H

#include "osc_tables.h"



class cTblOSC {
private:
     float phase, phaseInc, syncPos, syncInc;
     bool sync;
     int bendRange;
     int TableSize;
     float *table, *deltaTbl1, *deltaTbl2, *deltaTbl3;

public:

     cTblOSC(int wave){
          TableSize = 512;
          phase = 0;
          phaseInc = (float)TableSize / (44100.0f/440.0f);
          sync = false;
          syncPos = 0.0f;
          syncInc = 0.0f;

          table =   new float[TableSize];
          deltaTbl1 =  new float[TableSize];
          deltaTbl2 =  new float[TableSize];
          deltaTbl3 =  new float[TableSize];

          setOscTbl(wave);
     }


     ~cTblOSC(){
          delete [] table;
          delete [] deltaTbl1;
          delete [] deltaTbl2;
          delete [] deltaTbl3;
     }

     //these two processing methods have different caps

     // Syncable, overwrites
     void doProcess(float * Buffer, int bSize)
     {
          int i1 = 0;
          float alpha = 0;

          for(int j = 0; j < bSize; j++)
          {
               i1 = truncate(phase);
               alpha = phase - (float)i1;

               Buffer[j] = ((deltaTbl1[i1]*alpha + deltaTbl2[i1])*alpha + deltaTbl3[i1])*alpha+table[i1];

               phase += phaseInc;
               if (sync){
                    syncPos += syncInc;
                    if (syncPos >= (float)TableSize){
                         phase = 0.0f;
                         syncPos = 0.0f;
                    }
               }
               if (phase >= (float)TableSize){ phase -= (float)TableSize;}
          }
     }

     // adds, mixable
     void doProcess(float * Buffer, int bSize, float mix)
     {
          float m = (mix * 0.5f) + 0.5f;
          int i1 = 0;
          float alpha = 0;
          float tmp = 0;
          for(int j = 0; j < bSize; j++)
          {
               i1 = truncate(phase);
               alpha = phase - (float)i1;

               tmp = ((deltaTbl1[i1]*alpha + deltaTbl2[i1])*alpha + deltaTbl3[i1])*alpha+table[i1];
               Buffer[j] = (Buffer[j] * (1.0f-m)) + (tmp * m);
               phase += phaseInc;
               if (phase >= (float)TableSize){ phase -= (float)TableSize;}
          }
     }


     void setOscTbl(int wave)
     {
          float *tmpTblPtr;

          switch(wave){
               case 1:  tmpTblPtr = (float*)osc_tables::saw_raw; break;
               case 2:  tmpTblPtr = (float*)osc_tables::saw2_raw; break;
               case 3:  tmpTblPtr = (float*)osc_tables::tri_raw; break;
               case 4:  tmpTblPtr = (float*)osc_tables::tri2_raw; break;
               case 5:  tmpTblPtr = (float*)osc_tables::sqr_raw; break;
               default:  tmpTblPtr = (float*)osc_tables::sin_raw; break;
          }

          for(int i = 0; i < TableSize; i++){
               table[i] = tmpTblPtr[i];
          }

          for(int i = 0; i < TableSize; i++){
               deltaTbl1[i] = (3.f*(table[i]-table[(i+1)%TableSize])-table[(i-1)%TableSize]+table[(i+2)%TableSize])/2.f;
               deltaTbl2[i] = 2.f*table[(i+1)%TableSize]+table[(i-1)%TableSize]-(5.f*table[i]+table[(i+2)%TableSize])/2.f;
               deltaTbl3[i] = (table[(i+1)%TableSize]-table[(i-1)%TableSize])/2.f;
          }
     }


     void reset(float f, float s, float sb = 1)
     {
          phase = 0;
          syncInc = (float)TableSize / (s/sb);
          phaseInc = (float)TableSize / (s/f);
     }

     void setFrequency(float f, float s, float sb = 1)
     {
          syncInc = (float)TableSize / (s/sb);
          phaseInc = (float)TableSize / (s/f);
     }

     void setSync(bool x)
     {
          sync = x;
     }

     inline int truncate(float flt)
     {
          return roundFloatToInt (flt - 0.5f);
     }
};
#endif
