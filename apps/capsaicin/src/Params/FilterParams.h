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

#ifndef __JUCETICE_XSYNTHFILTERPARAMS_HEADER__
#define __JUCETICE_XSYNTHFILTERPARAMS_HEADER__

#include "Presets.h"


class FilterParams : public Presets
{
public:
	FilterParams(unsigned char Ptype_,unsigned char Pfreq,unsigned char Pq_);
	~FilterParams();

    void defaults();

    void addToXML (XmlElement* xml);
    void addToXMLSection (XmlElement* xml, int section);
    void updateFromXML (XmlElement *xml);
    void updateFromXMLSection (XmlElement *xml, int section);

	void getfromFilterParams(FilterParams *pars);

	REALTYPE getfreq();
	REALTYPE getq();
	REALTYPE getfreqtracking(REALTYPE notefreq);
	REALTYPE getgain();

    unsigned char Pcategory;//Filter category (Analog/Formant/StVar)
	unsigned char Ptype;// Filter type  (for analog lpf,hpf,bpf..)
	unsigned char Pfreq;// Frequency (64-central frequency)
	unsigned char Pq;   // Q parameters (resonance or bandwidth)
	unsigned char Pstages; //filter stages+1
	unsigned char Pfreqtrack;//how the filter frequency is changing according the note frequency
	unsigned char Pgain;//filter's output gain

	//Formant filter parameters
	unsigned char Pnumformants;//how many formants are used
	unsigned char Pformantslowness;//how slow varies the formants
	unsigned char Pvowelclearness;//how vowels are kept clean (how much try to avoid "mixed" vowels)
	unsigned char Pcenterfreq,Poctavesfreq;//the center frequency of the res. func., and the number of octaves

	struct {
	    struct {
		unsigned char freq,amp,q;//frequency,amplitude,Q
	    }formants[FF_MAX_FORMANTS];
	}Pvowels[FF_MAX_VOWELS];


	unsigned char Psequencesize;//how many vowels are in the sequence
	unsigned char Psequencestretch;//how the sequence is stretched (how the input from filter envelopes/LFOs/etc. is "stretched")
	unsigned char Psequencereversed;//if the input from filter envelopes/LFOs/etc. is reversed(negated)
	struct {
	    unsigned char nvowel;//the vowel from the position
	} Psequence[FF_MAX_SEQUENCE];

	REALTYPE getcenterfreq();
	REALTYPE getoctavesfreq();
	REALTYPE getfreqpos(REALTYPE freq);
	REALTYPE getfreqx(REALTYPE x);

	void formantfilterH(int nvowel,int nfreqs,REALTYPE *freqs);//used by UI

	REALTYPE getformantfreq(unsigned char freq);
	REALTYPE getformantamp(unsigned char amp);
	REALTYPE getformantq(unsigned char q);

	bool changed;

private:
	void defaults(int n);

	//stored default parameters
	unsigned char Dtype;
	unsigned char Dfreq;
	unsigned char Dq;
};

#endif

