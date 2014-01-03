/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2007 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2007 by Julian Storer.

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

   @author  Paul Nasca
   @tweaker Lucio Asnaghi

 ==============================================================================
*/

#ifndef __JUCETICE_XSYNTHRESONANCE_HEADER__
#define __JUCETICE_XSYNTHRESONANCE_HEADER__

#include "../globals.h"
#include "../Misc/Util.h"
#include "../Params/Presets.h"

#define N_RES_POINTS 256

class Resonance : public Presets
{
public:
	Resonance();
	~Resonance();
	void setpoint(int n,unsigned char p);
	void applyres(int n,FFTFrequencies fftdata,REALTYPE freq);
	void smooth();
	void interpolatepeaks(int type);
	void randomize(int type);

    void defaults();

    void addToXML (XmlElement* xml);
    void updateFromXML (XmlElement* xml);

	REALTYPE getfreqpos(REALTYPE freq);
	REALTYPE getfreqx(REALTYPE x);
	REALTYPE getfreqresponse(REALTYPE freq);
	REALTYPE getcenterfreq();
	REALTYPE getoctavesfreq();
	void sendcontroller(MidiControllers ctl,REALTYPE par);

    //parameters
    unsigned char Penabled;			//if the ressonance is enabled
    unsigned char Prespoints[N_RES_POINTS];	//how many points define the resonance function
    unsigned char PmaxdB;			//how many dB the signal may be amplified
    unsigned char Pcenterfreq,Poctavesfreq;     //the center frequency of the res. func., and the number of octaves
    unsigned char Pprotectthefundamental;       //the fundamental (1-st harmonic) is not damped, even it resonance function is low

    //controllers
    REALTYPE ctlcenter;//center frequency(relative)
    REALTYPE ctlbw;//bandwidth(relative)
};

#endif // JUCETICE_XSYNTHRESONANCE_HEADER__
