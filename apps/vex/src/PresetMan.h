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

#ifndef __JUCETICE_VEXPRESETMAN_HEADER__
#define __JUCETICE_VEXPRESETMAN_HEADER__

#include "StandardHeader.h"
#include "PeggySettings.h"


class Program
{
public:

	Program()
	{
		name =		"No Set";
        waveFile1 = "No Set";
		waveFile2 = "No Set";
		waveFile3 = "No Set";
	}

	~Program()
	{
	}

	String name;
	float parameters[92];
	peggySettings pegSet1;
	peggySettings pegSet2;
	peggySettings pegSet3;
	String waveFile1;
	String waveFile2;
	String waveFile3;
};


class PresetMan
{
public:

	PresetMan()
	{
		cp = 0;
		for(int i = 0; i < np; i++)
		{
			fooShizzle[i] = new Program();
			resetProgram(fooShizzle[i]);
		}
	}

	~PresetMan()
	{
		for(int i = 0; i < np; i++)
		{
			delete fooShizzle[i];
		}
	}

	int getNumPrograms()	{		return np;		}
	int getCurrentProgram()	{		return cp;	}
	
	String getProgramName(int i)
	{
		return fooShizzle[i]->name;
	}

	void changeProgramName (int i, const String& newName)
	{
		fooShizzle[i]->name = newName;
	}

	void setCurrentProgram(int i)
	{
		if (i < 8)
		{
			cp = i;
		}
	}

	void setPointersToCurrent(float** pars,
	                          peggySettings** p1,
	                          peggySettings** p2,
	                          peggySettings** p3)
	{
		*pars = (fooShizzle[cp]->parameters);
		*p1 = &(fooShizzle[cp]->pegSet1);
		*p2 = &(fooShizzle[cp]->pegSet2);
		*p3 = &(fooShizzle[cp]->pegSet3);
	}

	Program* getProgramStruct(int i)
	{
		return fooShizzle[i];
	}

	void setWaveName(int part, const String& newName)
	{
		if(part == 1) fooShizzle[cp]->waveFile1 = newName;
		if(part == 2) fooShizzle[cp]->waveFile2 = newName;
		if(part == 3) fooShizzle[cp]->waveFile3 = newName;
	}

	String getWaveName(int part)
	{
		if(part == 1) return fooShizzle[cp]->waveFile1;
		if(part == 2) return fooShizzle[cp]->waveFile2;
		if(part == 3) return fooShizzle[cp]->waveFile3;
		return "1k_Sine";
	}

	void resetProgram(Program* p)
	{
		p->name =		"Default";
		p->waveFile1 =	"sine";
		p->waveFile2 =	"sine";
		p->waveFile3 =	"sine";

		p->pegSet1.length	= 8;
		p->pegSet1.timeMode	= 2;
		p->pegSet1.syncMode	= 1;
		p->pegSet1.failMode	= 1;
		p->pegSet1.velMode	= 1;
		p->pegSet1.on = true;

		p->pegSet2.length	= 8;
		p->pegSet2.timeMode	= 2;
		p->pegSet2.syncMode	= 1;
		p->pegSet2.failMode	= 1;
		p->pegSet2.velMode	= 1;
		p->pegSet2.on = false;

		p->pegSet3.length	= 8;
		p->pegSet3.timeMode	= 2;
		p->pegSet3.syncMode	= 1;
		p->pegSet3.failMode	= 1;
		p->pegSet3.velMode	= 1;
		p->pegSet3.on = false;

		for(int i = 0; i < 16; i++)
		{
			p->pegSet1.velocities[i] = 0.5f;
			p->pegSet2.velocities[i] = 0.5f;
			p->pegSet3.velocities[i] = 0.5f;
		}
		
		for(int i = 0; i < 80; i++)
		{	
			p->pegSet1.grid[i] = false;
			p->pegSet2.grid[i] = false;
			p->pegSet3.grid[i] = false;
		}

		for(int i = 0; i < 3; i++)
		{	
			int offset = i * 24;
			p->parameters[offset + 1] = 0.5f;
			p->parameters[offset + 2] = 0.5f;
			p->parameters[offset + 3] = 0.5f;
			p->parameters[offset + 4] = 0.5f;
			p->parameters[offset + 5] = 0.9f;
			p->parameters[offset + 6] = 0.0f;
			p->parameters[offset + 7] = 1.0f;
			p->parameters[offset + 8] = 0.5f;
			p->parameters[offset + 9] = 0.0f;
			p->parameters[offset + 10] = 0.2f;
			p->parameters[offset + 11] = 0.0f;
			p->parameters[offset + 12] = 0.5f;
			p->parameters[offset + 13] = 0.5f;
			p->parameters[offset + 14] = 0.0f;
			p->parameters[offset + 15] = 0.3f;
			p->parameters[offset + 16] = 0.7f;
			p->parameters[offset + 17] = 0.1f;
			p->parameters[offset + 18] = 0.5f;
			p->parameters[offset + 19] = 0.5f;
			p->parameters[offset + 20] = 0.0f;
			p->parameters[offset + 21] = 0.0f;
			p->parameters[offset + 22] = 0.5f;
			p->parameters[offset + 23] = 0.5f;
			p->parameters[offset + 24] = 0.5f;
		}

		p->parameters[0] = 0.5f;
		p->parameters[73] = 0.5f;
		p->parameters[74] = 0.4f;
		p->parameters[75] = 0.5f;
		p->parameters[76] = 0.3f;
		p->parameters[77] = 0.6f;
		p->parameters[78] = 0.0f;
		p->parameters[79] = 0.6f;
		p->parameters[80] = 0.7f;
		p->parameters[81] = 0.6f;
		p->parameters[82] = 0.0f;
		p->parameters[83] = 0.5f;
		p->parameters[84] = 0.5f;
		p->parameters[85] = 0.5f;
		p->parameters[86] = 0.5f;
		p->parameters[87] = 0.5f;
		p->parameters[88] = 0.5f;
		p->parameters[89] = 0.0f;
		p->parameters[90] = 0.0f;
		p->parameters[91] = 0.0f;
	}

private:

	static const int np = 8;
	int cp;
	Program* fooShizzle[np];
};

#endif

