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

#include "FormantFilter.h"


FormantFilter::FormantFilter(FilterParams *pars)
{
    numformants=pars->Pnumformants;
    for (int i=0;i<numformants;i++) formant[i]=new AnalogFilter(4/*BPF*/,1000.0,10.0,pars->Pstages);
    cleanup();
    inbuffer=new REALTYPE [SOUND_BUFFER_SIZE];
    tmpbuf=new REALTYPE [SOUND_BUFFER_SIZE];

    for (int j=0;j<FF_MAX_VOWELS;j++)
	for (int i=0;i<numformants;i++){
	    formantpar[j][i].freq=pars->getformantfreq(pars->Pvowels[j].formants[i].freq);
	    formantpar[j][i].amp=pars->getformantamp(pars->Pvowels[j].formants[i].amp);
	    formantpar[j][i].q=pars->getformantq(pars->Pvowels[j].formants[i].q);
	};
    for (int i=0;i<FF_MAX_FORMANTS;i++) oldformantamp[i]=1.0;
    for (int i=0;i<numformants;i++){
	currentformants[i].freq=1000.0;
	currentformants[i].amp=1.0;
	currentformants[i].q=2.0;
    };

    formantslowness=pow(1.0-(pars->Pformantslowness/128.0),3.0);

    sequencesize=pars->Psequencesize;if (sequencesize==0) sequencesize=1;
    for (int k=0;k<sequencesize;k++) sequence[k].nvowel=pars->Psequence[k].nvowel;

    vowelclearness=pow(10.0,(pars->Pvowelclearness-32.0)/48.0);

    sequencestretch=pow(0.1,(pars->Psequencestretch-32.0)/48.0);
    if (pars->Psequencereversed) sequencestretch*= -1.0;

    outgain=dB2rap(pars->getgain());

    oldinput=-1.0;
    Qfactor=1.0;oldQfactor=Qfactor;
    firsttime=1;
};

FormantFilter::~FormantFilter(){
    for (int i=0;i<numformants;i++) delete(formant[i]);
    delete (inbuffer);
    delete (tmpbuf);
};




void FormantFilter::cleanup(){
    for (int i=0;i<numformants;i++) formant[i]->cleanup();
};

void FormantFilter::setpos(REALTYPE input){
    int p1,p2;

    if (firsttime!=0) slowinput=input;
	else slowinput=slowinput*(1.0-formantslowness)+input*formantslowness;

    if ((fabs(oldinput-input)<0.001)&&(fabs(slowinput-input)<0.001)&&
	(fabs(Qfactor-oldQfactor)<0.001)) {
//	oldinput=input; daca setez asta, o sa faca probleme la schimbari foarte lente
	firsttime=0;
	return;
    } else oldinput=input;


    REALTYPE pos=fmod(input*sequencestretch,1.0);if (pos<0.0) pos+=1.0;

    F2I(pos*sequencesize,p2);
    p1=p2-1;if (p1<0) p1+=sequencesize;

    pos=fmod(pos*sequencesize,1.0);
    if (pos<0.0) pos=0.0; else if (pos>1.0) pos=1.0;
    pos=(atan((pos*2.0-1.0)*vowelclearness)/atan(vowelclearness)+1.0)*0.5;

    p1=sequence[p1].nvowel;
    p2=sequence[p2].nvowel;

    if (firsttime!=0) {
       for (int i=0;i<numformants;i++){
	    currentformants[i].freq=formantpar[p1][i].freq*(1.0-pos)+formantpar[p2][i].freq*pos;
	    currentformants[i].amp=formantpar[p1][i].amp*(1.0-pos)+formantpar[p2][i].amp*pos;
	    currentformants[i].q=formantpar[p1][i].q*(1.0-pos)+formantpar[p2][i].q*pos;
	    formant[i]->setfreq_and_q(currentformants[i].freq,currentformants[i].q*Qfactor);
	    oldformantamp[i]=currentformants[i].amp;
	};
	firsttime=0;
    } else {
	for (int i=0;i<numformants;i++){
	    currentformants[i].freq=currentformants[i].freq*(1.0-formantslowness)
		+(formantpar[p1][i].freq*(1.0-pos)+formantpar[p2][i].freq*pos)*formantslowness;

	    currentformants[i].amp=currentformants[i].amp*(1.0-formantslowness)
		+(formantpar[p1][i].amp*(1.0-pos)+formantpar[p2][i].amp*pos)*formantslowness;

	    currentformants[i].q=currentformants[i].q*(1.0-formantslowness)
		+(formantpar[p1][i].q*(1.0-pos)+formantpar[p2][i].q*pos)*formantslowness;

	    formant[i]->setfreq_and_q(currentformants[i].freq,currentformants[i].q*Qfactor);
	};
    };

    oldQfactor=Qfactor;
};

void FormantFilter::setfreq(REALTYPE frequency){
    setpos(frequency);
};

void FormantFilter::setq(REALTYPE q_){
    Qfactor=q_;
    for (int i=0;i<numformants;i++) formant[i]->setq(Qfactor*currentformants[i].q);
};

void FormantFilter::setfreq_and_q(REALTYPE frequency,REALTYPE q_){
    Qfactor=q_;
    setpos(frequency);
};


void FormantFilter::filterout (REALTYPE *smp, int numSamples)
{
    int i,j;
    for (i = 0; i < numSamples; i++)
    {
        inbuffer[i] = smp[i];
        smp[i] = 0.0;
    }

    for (j = 0; j < numformants; j++)
    {
        for (i = 0; i < numSamples; i++)
            tmpbuf[i] = inbuffer[i] * outgain;

        formant[j]->filterout (tmpbuf, numSamples);

        if (ABOVE_AMPLITUDE_THRESHOLD (oldformantamp[j], currentformants[j].amp))
            for (i = 0; i < numSamples;i++)
                smp[i] += tmpbuf[i] * INTERPOLATE_AMPLITUDE (oldformantamp[j], currentformants[j].amp, i, numSamples);
        else
            for (i = 0; i < numSamples; i++)
                smp[i] += tmpbuf[i] * currentformants[j].amp;

        oldformantamp[j]=currentformants[j].amp;
    }
}

