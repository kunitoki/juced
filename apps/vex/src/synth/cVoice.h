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

#ifndef __JUCETICE_VEXCVOICE_HEADER__
#define __JUCETICE_VEXCVOICE_HEADER__

#include "../StandardHeader.h"
#include "cWaveRenderer.h"
#include "cADSR.h"      


class cVoice
{
public:

	cVoice(float* P, int po, waveRenderer* w, float sr = 44100);
	~cVoice();

	void doProcess(float * outBufferL, float * outBufferR, int bufferSize);
	void start(float f, float v, int n, int preroll, double s, long o);
	void release(int p);
    void quickRelease();

	void updateParameterPtr(float* P);

	int getOrdinal();

	void kill();
    void update(int index);

	int getNote();
	bool getIsOn();
	bool getIsReleased();

	float convertPitch (float pitch);
    float bipolar (float in)	{	return in * 2.0f - 1.0f;	}

private:

	oscSet* oL;
	oscSet* oR;
	waveRenderer* wr;

	cADSR * aadsr;
	cADSR * fadsr;

	bool isOn,  isReleased;
	int note;

	long Ordinal;

	float Avelocity;
	float Fvelocity;
	double SampleRate; 
	float BaseFrequency;
	int poff;
	float* pra;
	float lfoC, LFOA, LFOP, LFOF;
	float lfoS[2];
	float lowL, bandL, highL, lowR, bandR, highR, q, cut;
};


#endif
