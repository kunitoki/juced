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

#ifndef __JUCETICE_VEXCSYNTMODULE_HEADER__
#define __JUCETICE_VEXCSYNTMODULE_HEADER__

#include "../StandardHeader.h"
#include "cVoice.h"

class cSyntModule 
{public:

	cSyntModule(float* P)
	{
		SampleRate = 44100;
		Benchwarmer = 0;
		playCount = 1;
		outPtrL = 0;
		outPtrR = 0;
		part1 = part2 = part3 = false;
		wr1 = new waveRenderer();
		wr2 = new waveRenderer();
		wr3 = new waveRenderer();
		par = P;

		for(int i = 0; i < nv; i++)
		{ 
			vo1[i] = new cVoice( par, 0, wr1);
			vo2[i] = new cVoice( par, 24, wr2);
			vo3[i] = new cVoice( par, 48, wr3);
		}
	}

	~cSyntModule()
	{
		delete wr1;
		delete wr2;
		delete wr3;
		for(int i = 0; i<nv; i++)
		
		{
			delete vo1[i];
			delete vo2[i];
			delete vo3[i];
		}
	}

	void doProcess(	AudioSampleBuffer * obf, AudioSampleBuffer * assbf, AudioSampleBuffer * ebf1, AudioSampleBuffer * ebf2, AudioSampleBuffer * ebf3)
	{
		int numSamples = obf->getNumSamples();

		outPtrL = assbf->getSampleData(0,0);
		outPtrR = assbf->getSampleData(1,0);
	
		if( part1 ) 
		{
			float Right	= par[86] * par[83];
			float Left = par[86] * (1.0f - par[83]);
				for(int i = 0; i < nv; i++)
				{
					if( vo1[i]->getIsOn() )
					{
						vo1[i]->doProcess(outPtrL, outPtrR, numSamples);
						obf->addFrom(0, 0, *assbf, 0,0,numSamples, Left);
						obf->addFrom(1, 0, *assbf, 1,0,numSamples, Right);
						ebf1->addFrom(0, 0, *assbf, 0,0,numSamples,  par[22] * Left);
						ebf1->addFrom(1, 0, *assbf, 1,0,numSamples,  par[22] * Right);
						ebf2->addFrom(0, 0, *assbf, 0,0,numSamples, par[23] * Left);
						ebf2->addFrom(1, 0, *assbf, 1,0,numSamples, par[23] * Right);
						ebf3->addFrom(0, 0, *assbf, 0,0,numSamples, par[24] * Left);
						ebf3->addFrom(1, 0, *assbf, 1,0,numSamples, par[24] * Right);

					}
				}
			}
		if( part2 ) 
		{
			float Right	= par[87] * par[84];
			float Left = par[87] * (1.0f - par[84]);
				for(int i = 0; i < nv; i++)
				{
					if( vo2[i]->getIsOn() )
					{
						vo2[i]->doProcess(outPtrL, outPtrR, numSamples);
						obf->addFrom(0, 0, *assbf, 0,0,numSamples, Left);
						obf->addFrom(1, 0, *assbf, 1,0,numSamples, Right);
						ebf1->addFrom(0, 0, *assbf, 0,0,numSamples,  par[22 + 24] * Left);
						ebf1->addFrom(1, 0, *assbf, 1,0,numSamples,  par[22 + 24] * Right);
						ebf2->addFrom(0, 0, *assbf, 0,0,numSamples, par[23 + 24] * Left);
						ebf2->addFrom(1, 0, *assbf, 1,0,numSamples, par[23 + 24] * Right);
						ebf3->addFrom(0, 0, *assbf, 0,0,numSamples, par[48] * Left);
						ebf3->addFrom(1, 0, *assbf, 1,0,numSamples, par[48] * Right);
					}
				}
			}
		if( part3 ) 
		{
			float Right	= par[88] * par[85];
			float Left = par[88] * (1.0f - par[85]);
				for(int i = 0; i < nv; i++)
				{
					if( vo3[i]->getIsOn() )
					{
						vo3[i]->doProcess(outPtrL, outPtrR, numSamples);
						obf->addFrom(0, 0, *assbf, 0,0,numSamples, Left);
						obf->addFrom(1, 0, *assbf, 1,0,numSamples, Right);
						ebf1->addFrom(0, 0, *assbf, 0,0,numSamples,  par[22 + 48] * Left);
						ebf1->addFrom(1, 0, *assbf, 1,0,numSamples,  par[22 + 48] * Right);
						ebf2->addFrom(0, 0, *assbf, 0,0,numSamples, par[23 + 48] * Left);
						ebf2->addFrom(1, 0, *assbf, 1,0,numSamples, par[23 + 48] * Right);
						ebf3->addFrom(0, 0, *assbf, 0,0,numSamples, par[48 + 24] * Left);
						ebf3->addFrom(1, 0, *assbf, 1,0,numSamples, par[48 + 24] * Right);
					}
				}
			}
		}

	void setSampleRate(double s){
		SampleRate = s;
	}

	void updateParameterPtr(float* P)
	{
		par = P;
		for(int i = 0; i < nv; i++){
			vo1[i]->updateParameterPtr(par);
			vo2[i]->updateParameterPtr(par);
			vo3[i]->updateParameterPtr(par);
		}
	}

	void playNote(int note, int vel, int preroll, const int part) 
	{
		cVoice ** v =  NULL;
		switch(part)
		{
		case 1:
			if (!part1) return;
			v = vo1;	
			break;
		case 2:		
			if (!part2) return;
			v = vo2;
			break;
		case 3:
			if (!part3) return;
			v = vo3;
			break;
		}
		int OldestOn = nv;
		int OldestOff = nv;
		int OldestReleased = nv;

		int tmpOn = 100000000;
		//int tmpOff = 100000000;
		int tmpReleased = 100000000;
		for(int i = 0; i < nv; i++)
		{
			if (i == Benchwarmer){ continue; }
			if (!v[i]->getIsOn())
			{
				OldestOff = i;
				break;
			}
			if (vo1[i]->getIsReleased())
			{
				OldestReleased = (v[i]->getOrdinal() < tmpReleased) ? i : OldestReleased;
				tmpReleased = v[OldestReleased]->getOrdinal();
				continue;
			}
			OldestOn = (v[i]->getOrdinal() < tmpOn) ? i : OldestOn;
			tmpOn = v[OldestOn]->getOrdinal();
		}

		note = note + 12;
		float noteInHertz = (float)MidiMessage::getMidiNoteInHertz(note);
		playCount++;
		if (OldestOff < nv)
		{
			v[OldestOff]->start(noteInHertz, float(vel / 127.0f), note, preroll, SampleRate, playCount);
			return;
		}
		if (OldestReleased < nv)
		{
			v[Benchwarmer]->start(noteInHertz, float(vel / 127.0f), note, preroll, SampleRate, playCount);
			Benchwarmer = OldestReleased;
			v[OldestReleased]->quickRelease();
			return;
		}
		if (OldestOn < nv)
		{
			v[Benchwarmer]->start(noteInHertz, float(vel / 127.0f), note, preroll, SampleRate, playCount);
			Benchwarmer = OldestOn;
			v[OldestReleased]->quickRelease();
			return;
		}
	}
	
	void releaseNote(int note, int preroll, int part )
	{
		cVoice ** v =  NULL;
		switch(part)
		{
		case 1:
			if (!part1) return;
			v = vo1;	
			break;
		case 2:		
			if (!part2) return;
			v = vo2;
			break;
		case 3:
			if (!part3) return;
			v = vo3;
			break;
		}

		note = note + 12;
		for(int i = 0; i < nv; i++)
		{
			if (v[i]->getNote() == note)
			{
				v[i]->release(preroll);
			}
		}
	}

	void releaseAll(int p)
	{
		for(int i = 0; i < nv; i++)
		{
			vo1[i]->release(p);
			vo2[i]->release(p);
			vo3[i]->release(p);
		}
	}

    void kill(int what = 0)
	{
		switch(what)
		{
		case 0:
			for(int i = 0; i < nv; i++)
			{
				vo1[i]->kill();
				vo2[i]->kill();
				vo3[i]->kill();
			}
		break;
		case 1:
			for(int i = 0; i < nv; i++)
			{
				vo1[i]->kill();
			}	
		break;
		case 2:
			for(int i = 0; i < nv; i++)
			{
				vo2[i]->kill();
			}	
		break;
		case 3:
			for(int i = 0; i < nv; i++)
			{
				vo3[i]->kill();
			}	
		break;
		}
    }

	void  setWave(int part, const String& waveName)
	{
		switch(part)
		{
		case 1:
			wr1->setWave(waveName);
			kill(1);
		break;
		case 2:
			wr2->setWave(waveName);
			kill(2);
		break;
		case 3:
			wr3->setWave(waveName);
			kill(3);
		break;
		}
	}
	
	void update(int index)
	{

		if (index == 89)
		{ 
			part1 = (par[89] > 0.9f);
			return;
		}
		if (index == 90)
		{ 
			part2 = (par[90] > 0.9f);
			return;
		}
		if (index == 91)
		{ 
			part3 = (par[91] > 0.9f);
			return;
		}

		for(int i = 0; i < nv; i++){
			vo1[i]->update(index);
			vo2[i]->update(index);
			vo3[i]->update(index);
		}
	}
    
    juce_UseDebuggingNewOperator

private:

	double SampleRate;
	
	int Benchwarmer;
	static const int nv = 8;
	cVoice * vo1[nv];
	cVoice * vo2[nv];
	cVoice * vo3[nv];

	long playCount;
	bool part1, part2, part3;

	waveRenderer* wr1;	
	waveRenderer* wr2;
	waveRenderer* wr3;

	float* par;

	float* outPtrL;
	float* outPtrR;
};

#endif
