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

#include "cVoice.h"


cVoice::cVoice(float* P, int po, waveRenderer* w, float sr)
{
	pra = P;
	poff = po;

	oL  = new oscSet();
	oR = new oscSet();
	wr = w;

	aadsr =		new cADSR();
	fadsr =	new cADSR();

	Ordinal = 1;
	SampleRate = sr;
	isOn = false;
	note = 0;

	lfoC = 2.f * (float)sin(float_Pi * 5.0f / SampleRate);
	
	lfoS[0] = 0.3f;
	lfoS[1] = 0.0f;

	lowL = 0.0f;
	bandL = 0.0f;
	highL = 0.0f;
	lowR = 0.0f;
	bandR = 0.0f;
	highR = 0.0f;
	q = 0.0f;
	cut =	0.0f;
}


cVoice::~cVoice()
{
	delete oL;
	delete oR;
	delete aadsr;
	delete fadsr;
}

float cVoice::convertPitch(float pitch)
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

void cVoice::doProcess(float * outBufferL, float * outBufferR, int bufferSize) 
{
	//float resAmt = 0.0;
	float A, B;
	float amod;

	wr->fillBuffer(outBufferL, bufferSize, oL);
	wr->fillBuffer(outBufferR, bufferSize, oR);

	for(int i = 0; i < bufferSize; i++)
	{ 
		//LFO
		lfoS[0] = lfoS[0] - lfoC * lfoS[1];
		lfoS[1] = lfoS[1] + lfoC * lfoS[0];
		LFOA = lfoS[0] * pra[20 + poff];
		LFOF = lfoS[0] * pra[21 + poff];

		//Filter Mod
		q = 1.1f - pra[6 + poff];
		cut =  jlimit(0.001f, 0.999f, pra[5 + poff]
										+ (fadsr->getSample() * bipolar(pra[8 + poff]))
										+ Fvelocity
										+ LFOF
										);

		amod = LFOA + Avelocity;

		//Filter
		//Left
		lowL = lowL + cut * bandL;
		highL =  outBufferL[i] - lowL - (q * bandL);
		bandL = cut * highL + bandL;
		B = (lowL  * ((q * 0.5f) + 0.5f));
		A = (highL * ((q * 0.5f) + 0.5f));
		outBufferL[i] = A + pra[7 + poff] * ( B - A );	
		outBufferL[i] += outBufferL[i] * amod;
		
		//Right
		lowR = lowR + cut * bandR;
		highR =  outBufferR[i] - lowR - (q * bandR);
		bandR = cut * highR + bandR;
		B = (lowR  * ((q * 0.5f) + 0.5f));
		A = (highR * ((q * 0.5f) + 0.5f));
		outBufferR[i] = A + pra[7 + poff] * ( B - A );
		outBufferR[i] += outBufferR[i] * amod;
	}

	aadsr->doProcess(outBufferL, outBufferR, bufferSize);
	isOn = aadsr->getState();

}

void cVoice::start(float f, float v, int n, int preroll, double s, long o)
{
	Ordinal = o;
	SampleRate = s;
	float oct = (pra[1 + poff] - 0.5f) * 4.0f;
	float cent = (pra[2 + poff] - 0.5f) * 0.1f;
	BaseFrequency = f * convertPitch(cent + oct);

	wr->reset(BaseFrequency , SampleRate, oL);
	wr->reset(BaseFrequency , SampleRate, oR);
	note = n;

	lfoS[0] = 0.5f;
	lfoS[1] = 0.0f;

	isOn = true; isReleased = false;
	v  = (v * v) - 1.0f;

	Avelocity = (v * bipolar(pra[18 + poff]));
	Fvelocity = (1.0f + v) * bipolar(pra[13 + poff]);

	aadsr->reset(preroll);
	fadsr->reset(preroll); 
}

void cVoice::release(int p)
{
	isReleased = true;
	aadsr->release(p);
	fadsr->release(p); 
}

void cVoice::quickRelease()
{
    isReleased = true;
    aadsr->quickRelease();
}

int cVoice::getOrdinal()
{
	return Ordinal;
}


void cVoice::kill()
{
	isOn = false;
}

void cVoice::update(int index)
{
    switch (index-poff) {
		case 14:
		case 15: 
		case 16: 
		case 17: aadsr->setADSR(	pra[14+poff],
										pra[15+poff],
										pra[16+poff],
										pra[17+poff],
										SampleRate);    
		break;
		case 9:
		case 10: 
		case 11: 
		case 12: fadsr->setADSR(	pra[9+poff],
										pra[10+poff],
										pra[11+poff],
										pra[12+poff],
										SampleRate);

		break;
		case 19: 
			lfoC = 2.f * (float)sin(float_Pi*(pra[19 + poff] * 10.0f) / SampleRate);
		break;
		case 3:
			{
				float p = bipolar(pra[3 + poff]);
				oL-> phase_offset	=	p > 0.0f ? p : 0.0f;
				oR->phase_offset	=	p < 0.0f ? fabs(p) : 0.0f;
			}
		break;
		case 4:
			{
				float p = bipolar(pra[4 + poff]);
				oL-> phaseInc_offset	=	p > 0.0f ? p : 0.0f;
				oR->phaseInc_offset	=	p < 0.0f ? fabs(p) : 0.0f;
			}
		break;
    }
}

int cVoice::getNote()
{
	return note;
}

bool cVoice::getIsOn()
{
	return isOn;
}

bool cVoice::getIsReleased()
{
	return isReleased;
}

void cVoice::updateParameterPtr(float* P)
{
	pra = P;
}

