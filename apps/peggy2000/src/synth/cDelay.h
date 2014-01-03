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

#ifndef CDELAY_H
#define CDELAY_H

#include "../parameters.h"

class cDelay {

private:
     ParMan * Pars;
     AudioSampleBuffer * buffy;

     float SampleRate;

     float feedback, mix;

     int iWrite, iRead, bufferSize, delay;

public:

     cDelay(ParMan * P){
          SampleRate = 44100;
          bufferSize = int(SampleRate * 2);
          buffy = new AudioSampleBuffer(2, bufferSize);
          buffy->clear();
          Pars = P;
          delay = 0;

          iWrite = 0;
          iRead  = 0;
     }

     ~cDelay(){
          delete buffy;
     }

     void doProcess(AudioSampleBuffer * OutBuffer, double bpm){
          feedback = Pars->getParameter(ParMan::dl_fb);
          mix =   Pars->getParameter(ParMan::dl_lvl);
          bpm = jlimit(30.0,300.0,bpm);
          delay = jmin(int(Pars->getParameter(ParMan::dl_tme) * 8) * int(((60 / bpm) * SampleRate) / 4) , 44100);


          for(int i = 0; i < OutBuffer->getNumSamples() ; i++){

               if( iWrite >= SampleRate ){ iWrite = 0; }
               iRead = iWrite - delay;
               if( iRead < 0 ){ iRead = (int)SampleRate + iRead; }

               *(buffy->getSampleData(0,iWrite)) = *(OutBuffer->getSampleData(0,i));
               *(buffy->getSampleData(1,iWrite)) = *(OutBuffer->getSampleData(1,i));
               *(buffy->getSampleData(1,iWrite)) +=  (*(buffy->getSampleData(0,iRead)) * feedback);
               *(buffy->getSampleData(0,iWrite)) +=  (*(buffy->getSampleData(1,iRead)) * feedback);

               *(OutBuffer->getSampleData(0,i)) += *(buffy->getSampleData(0,iRead)) * mix;
               *(OutBuffer->getSampleData(1,i)) += *(buffy->getSampleData(1,iRead)) * mix;

               iWrite++;

          }
     }

     void setSampleRate(float s){
          SampleRate = s;
     }

};

#endif
