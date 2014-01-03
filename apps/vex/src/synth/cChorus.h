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

#ifndef __JUCETICE_VEXCCHORUS_HEADER__
#define __JUCETICE_VEXCCHORUS_HEADER__

#include "../StandardHeader.h"

class cChorus
{
public:

	cChorus(float* p)
	{
		lfoC=LFO1=LFO2=lastLFO1=lastLFO2=0.0f;
		cycle = 44100 / 32;
		buffy = new AudioSampleBuffer(2, cycle);
		buffy->clear();
		parameters = p;
		iWrite = 0;
		iRead = int(cycle * 0.5f);
		lfoS[0] = 0.5f;
		lfoS[1] = 0.f;
		SampleRate = 44100.0f;
	}

	~cChorus()
	{
		delete buffy;
	}


	void updateParameterPtr(float* P)
	{
		parameters = P;
	}


	void processBlock(AudioSampleBuffer * OutBuffer)
	{
		int numSamples = OutBuffer->getNumSamples();
		
		depth = parameters[77] * 0.2f;
		speed = parameters[76] * parameters[94];
		delay = int(cycle * 0.5f);

		lfoC = 2.f*(float)sinf(float_Pi*(speed * 5) / SampleRate);

		float* bufferL = buffy->getSampleData(0,0);
		float* bufferR = buffy->getSampleData(1,0);
		float* outBufferL = OutBuffer->getSampleData(0,0);
		float* outBufferR = OutBuffer->getSampleData(1,0);

		for(int i = 0; i < numSamples ; i++)
		{
			// LFO
			lfoS[0] = lfoS[0] - lfoC*lfoS[1];
			lfoS[1] = lfoS[1] + lfoC*lfoS[0];
			lastLFO1 = LFO1;
			lastLFO2 = LFO2;
			LFO1 = (lfoS[0] + 1) * depth;
			LFO2 = (lfoS[1] + 1) * depth;

			//write to buffer
			bufferL[iWrite] = outBufferL[i];
			bufferR[iWrite] = outBufferR[i];
			iWrite++; //inc and cycle the write index
			iWrite = iWrite % cycle;
			
			iRead = iWrite + delay; //cycle the read index
			iRead = iRead % cycle;

			//read
			//Left
			readpoint = cycle * LFO1 * 0.5f;
			rp = roundFloatToInt(readpoint - 0.5f);
			alpha = readpoint - rp;
			float A = bufferL[(iRead + rp -1) % cycle];
			float B = bufferL[(iRead + rp) % cycle];
			outBufferL[i] = A + alpha * ( B - A );

			
			//Right
			readpoint = cycle * LFO2 * 0.5f;
			rp = roundFloatToInt(readpoint - 0.5f);
			alpha = readpoint - rp;
			A = bufferR[(iRead + rp -1) % cycle];
			B = bufferR[(iRead + rp) % cycle];
			outBufferR[i] = A + alpha * ( B - A );
		}
	}

	void setSampleRate(double s)
	{
		if (SampleRate != s)
		{
			SampleRate = (float)s;
			cycle =  int(SampleRate / 32);
			buffy->setSize(2, cycle,0,0,1);
			buffy->clear();
			iRead = int(cycle * 0.5f);
		}
	}

private:

	AudioSampleBuffer * buffy;

	float lfoC, LFO1, LFO2, lastLFO1, lastLFO2;
	float lfoS[2];

	float depth, speed;
	float* parameters;
	int iWrite, iRead;
	int rp, cycle, delay;
	float alpha, outSample, readpoint;
	float SampleRate;

};

#endif
