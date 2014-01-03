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

#ifndef CTBLLFO_H
#define CTBLLFO_H

#include "lfo_tables.h"



class cTblLFO {
private:
    float phase, phaseInc;

    int TableSize;
    float *table, *deltaTbl;

public:

    cTblLFO()
    {
        TableSize = 256;
        phase = 0;
        phaseInc = (float)TableSize / (44100.0f/10.0f);

        table =     (float*)malloc(TableSize * sizeof(float));
        deltaTbl =  (float*)malloc(TableSize * sizeof(float));

        setLFOTbl(1);
    }


    ~cTblLFO()
    {
        free(table);
        free(deltaTbl);
    }

    float doProcess(int size)
    {
        int i1 = 0;
        float alpha1 = 0;

        for (int i=0; i < size; i++)
        {
            i1 = truncate(phase);
            alpha1 = phase - (float)i1;

            phase += phaseInc;
            if (phase >= (float)TableSize){ phase -= (float)TableSize;}
        }

        return (table[i1] + (deltaTbl[i1] * alpha1));
    }

    void setLFOTbl(int wave)
    {
        float *tmpTblPtr;

        switch(wave){
            case 1:  tmpTblPtr = (float*)lfo_tables::saw_raw; break;
            case 2:  tmpTblPtr = (float*)lfo_tables::sqr_raw; break;
            default:  tmpTblPtr = (float*)lfo_tables::sin_raw; break;
        }

        for(int i = 0; i < TableSize; i++){
            table[i] = tmpTblPtr[i];
        }

        for(int i = 0; i < TableSize; i++){
            deltaTbl[i] = table[(i+1) % TableSize] - table[i];
        }
    }

    void reset(){
        phase = 0;
    }

    void setSpeed(float speed, float s){
        phaseInc = (float)TableSize / (s / (speed * 256));
    }

    inline int truncate(float flt){
        return roundFloatToInt (flt - 0.5f);
    }
};

#endif

