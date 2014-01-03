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

#ifndef __JUCETICE_VEXCDELAY_HEADER__
#define __JUCETICE_VEXCDELAY_HEADER__

#include "../StandardHeader.h"


class cDelay
{public:

     cDelay(float* P)
     {
          SampleRate = 44100;
          bufferSize = int(SampleRate * 2);
          buffy = new AudioSampleBuffer(2, bufferSize);
          buffy->clear();
          parameters = P;
          delay = 0;

          iWrite = 0;
          iRead  = 0;
     }

     ~cDelay(){
          delete buffy;
     }


	void updateParameterPtr(float* P)
	{
		parameters = P;
	}


    void processBlock(AudioSampleBuffer * OutBuffer, double bpm)
    {
          feedback = parameters[74];
          bpm = jlimit(10.0,500.0,bpm);
          delay = jmin(int(parameters[73] * 8) * int(((60 / bpm) * SampleRate) / 4) , 44100);


          for(int i = 0; i < OutBuffer->getNumSamples() ; i++)
          {
               if( iWrite >= SampleRate ){ iWrite = 0; }
               iRead = iWrite - delay;
               if( iRead < 0 ){ iRead = (int)SampleRate + iRead; }

               *(buffy->getSampleData(0,iWrite)) = *(OutBuffer->getSampleData(0,i));
               *(buffy->getSampleData(1,iWrite)) = *(OutBuffer->getSampleData(1,i));
               *(buffy->getSampleData(1,iWrite)) +=  (*(buffy->getSampleData(0,iRead)) * feedback);
               *(buffy->getSampleData(0,iWrite)) +=  (*(buffy->getSampleData(1,iRead)) * feedback);
				
			   jassert(i < OutBuffer->getNumSamples());
               jassert(iRead < buffy->getNumSamples());
			   jassert(iWrite < buffy->getNumSamples());

			   *(OutBuffer->getSampleData(0,i)) = *(buffy->getSampleData(0,iRead));
               *(OutBuffer->getSampleData(1,i)) = *(buffy->getSampleData(1,iRead));

               iWrite++;
          }
     }

     void setSampleRate(double s){
		if (SampleRate != s)
		{
			SampleRate = (float)s;
			bufferSize = int(SampleRate * 2);
			buffy->setSize(2, bufferSize,0,0,1);
		}
     }
    
    juce_UseDebuggingNewOperator

private:

     float* parameters;
     AudioSampleBuffer * buffy;
     float SampleRate;
     float feedback, mix;
     int iWrite, iRead, bufferSize, delay;
};

#endif

