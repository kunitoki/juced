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

#ifndef __JUCETICE_VEXCREVERB_HEADER__
#define __JUCETICE_VEXCREVERB_HEADER__

#include "../StandardHeader.h"
#include "freeverb/revmodel.hpp"

class cReverb
{
public:

	cReverb (float* p)
	{
		updateParameterPtr (p);
	}

	~cReverb()
	{
	}

	void updateParameterPtr (float* p)
	{
		parameters = p;

		model.setroomsize (parameters[79]);
		model.setdamp (parameters[81]);
		model.setwet (1.0f);
		model.setdry (0.0f);
		model.setwidth (parameters[80]);
	}

	void processBlock (AudioSampleBuffer * OutBuffer)
	{
#if 0
		model.setroomsize (parameters[79]);
		model.setdamp (parameters[81]);
		model.setwet (1.0f);
		model.setdry (0.0f);
		model.setwidth (parameters[80]);
#endif

		model.processreplace(OutBuffer->getSampleData(0,0),
		                     OutBuffer->getSampleData(1,0),
		                     OutBuffer->getSampleData(0,0),
		                     OutBuffer->getSampleData(1,0),
		                     OutBuffer->getNumSamples(),
		                     1);
	}

	void setSampleRate(double s)
	{
	}


private:

    revmodel	model;
    float* parameters;

};

#endif
