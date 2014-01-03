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

#ifndef CCHORUS_H
#define CCHORUS_H

#include "../parameters.h"

class cChorus {

private:
     ParMan * Pars;
     AudioSampleBuffer * buffy;

     float delay, lfoC, LFO1, LFO2, lastLFO1, lastLFO2;
     float lfoS[2];
     float SampleRate;

     float depth, speed, mix;

     int iWrite, iRead;
     int rp;
     float f, outSample,readpoint;

public:

     cChorus(ParMan * P)
     {
          SampleRate = 44100;

          delay=lfoC=LFO1=LFO2=lastLFO1=lastLFO2=0.0f;

          buffy = new AudioSampleBuffer(2,2048);
          buffy->clear();
          Pars = P;

          iWrite = 0;
          iRead = 1024;
          lfoS[0] = 0.5f;
          lfoS[1] = 0.f;
     }

     ~cChorus(){
          delete buffy;
     }

     void doProcess(AudioSampleBuffer * OutBuffer)
     {
          depth = Pars->getParameter(ParMan::ch_dph) * 0.5f;
          speed = Pars->getParameter(ParMan::ch_spd);
          mix =   Pars->getParameter(ParMan::ch_mix);

          lfoC = 2.f*(float)sin(float_Pi*(speed * 10)/SampleRate);

          for(int i = 0; i < OutBuffer->getNumSamples() ; i++)
          {
               // LFO
               lfoS[0] = lfoS[0] - lfoC*lfoS[1];
               lfoS[1] = lfoS[1] + lfoC*lfoS[0];
               lastLFO1 = LFO1;
               lastLFO2 = LFO2;
               LFO1 = (lfoS[0] + 1) * depth;
               LFO2 = (lfoS[1] + 1) * depth;

               //write to buffer
               *(buffy->getSampleData(0,iWrite)) = *(OutBuffer->getSampleData(0,i));
               *(buffy->getSampleData(1,iWrite)) = *(OutBuffer->getSampleData(1,i));
               iWrite++; //inc and cycle the write index
               iWrite = iWrite % 2048;

               //read
               readpoint = 512 * LFO1;
               rp = truncate(readpoint);
               f = readpoint - rp;

               outSample = (*(buffy->getSampleData(0,(iRead + rp) % 2048))) * f;
               outSample +=      (*(buffy->getSampleData(0,(iRead + rp -1) % 2048))) * (1.0f - f);
               *(OutBuffer->getSampleData(0,i)) += outSample * mix;

               readpoint = 512 * LFO2;
               rp = truncate(readpoint);
               f = readpoint - rp;

               outSample = (*(buffy->getSampleData(1,(iRead + rp) % 2048))) * f;
               outSample +=      (*(buffy->getSampleData(1,(iRead + rp -1) % 2048))) * (1.0f - f);
               *(OutBuffer->getSampleData(1,i)) += outSample * mix;


               iRead++; //inc and cycle the read index
               iRead = iRead % 2048;
          }
     }

     void setSampleRate(float s){
          SampleRate = s;
     }

     inline int truncate(float flt){
          return roundFloatToInt (flt);
     }

};


#endif
