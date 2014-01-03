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

#include "FilterParams.h"


FilterParams::FilterParams(unsigned char Ptype_,unsigned char Pfreq_,unsigned  char Pq_):Presets(){
    setpresettype("Pfilter");
    Dtype=Ptype_;
    Dfreq=Pfreq_;
    Dq=Pq_;

    changed=false;
    defaults();
};

FilterParams::~FilterParams(){
};


void FilterParams::defaults(){
    Ptype=Dtype;
    Pfreq=Dfreq;
    Pq=Dq;

    Pstages=0;
    Pfreqtrack=64;
    Pgain=64;
    Pcategory=0;

    Pnumformants=3;
    Pformantslowness=64;
    for (int j=0;j<FF_MAX_VOWELS;j++){
	defaults(j);
    };

    Psequencesize=3;
    for (int i=0;i<FF_MAX_SEQUENCE;i++) Psequence[i].nvowel=i%FF_MAX_VOWELS;

    Psequencestretch=40;
    Psequencereversed=0;
    Pcenterfreq=64;//1 kHz
    Poctavesfreq=64;
    Pvowelclearness=64;
};

void FilterParams::defaults(int n){
    int j=n;
	for (int i=0;i<FF_MAX_FORMANTS;i++){
	    Pvowels[j].formants[i].freq=(int)(RND*127.0);//some random freqs
	    Pvowels[j].formants[i].q=64;
	    Pvowels[j].formants[i].amp=127;
	};
};


/*
 * Get the parameters from other FilterParams
 */

void FilterParams::getfromFilterParams(FilterParams *pars){
    defaults();

    if (pars==NULL) return;

    Ptype=pars->Ptype;
    Pfreq=pars->Pfreq;
    Pq=pars->Pq;

    Pstages=pars->Pstages;
    Pfreqtrack=pars->Pfreqtrack;
    Pgain=pars->Pgain;
    Pcategory=pars->Pcategory;

    Pnumformants=pars->Pnumformants;
    Pformantslowness=pars->Pformantslowness;
    for (int j=0;j<FF_MAX_VOWELS;j++){
    	for (int i=0;i<FF_MAX_FORMANTS;i++){
    	    Pvowels[j].formants[i].freq=pars->Pvowels[j].formants[i].freq;
    	    Pvowels[j].formants[i].q=pars->Pvowels[j].formants[i].q;
    	    Pvowels[j].formants[i].amp=pars->Pvowels[j].formants[i].amp;
    	};
    };

    Psequencesize=pars->Psequencesize;
    for (int i=0;i<FF_MAX_SEQUENCE;i++) Psequence[i].nvowel=pars->Psequence[i].nvowel;

    Psequencestretch=pars->Psequencestretch;
    Psequencereversed=pars->Psequencereversed;
    Pcenterfreq=pars->Pcenterfreq;
    Poctavesfreq=pars->Poctavesfreq;
    Pvowelclearness=pars->Pvowelclearness;
};


/*
 * Parameter control
 */
REALTYPE FilterParams::getfreq(){
    return((Pfreq/64.0-1.0)*5.0);
};

REALTYPE FilterParams::getq(){
    return(exp(pow((REALTYPE) Pq/127.0,2)*log(1000.0))-0.9);
};
REALTYPE FilterParams::getfreqtracking(REALTYPE notefreq){
    return(log(notefreq/440.0)*(Pfreqtrack-64.0)/(64.0*double_Log2));
};

REALTYPE FilterParams::getgain(){
    return((Pgain/64.0-1.0)*30.0);//-30..30dB
};

/*
 * Get the center frequency of the formant's graph
 */
REALTYPE FilterParams::getcenterfreq(){
    return(10000.0*pow(10,-(1.0-Pcenterfreq/127.0)*2.0));
};

/*
 * Get the number of octave that the formant functions applies to
 */
REALTYPE FilterParams::getoctavesfreq(){
    return(0.25+10.0*Poctavesfreq/127.0);
};

/*
 * Get the frequency from x, where x is [0..1]
 */
REALTYPE FilterParams::getfreqx(REALTYPE x){
    if (x>1.0) x=1.0;
    REALTYPE octf=pow(2.0,getoctavesfreq());
    return(getcenterfreq()/sqrt(octf)*pow(octf,x));
};

/*
 * Get the x coordinate from frequency (used by the UI)
 */
REALTYPE FilterParams::getfreqpos(REALTYPE freq){
    return((log(freq)-log(getfreqx(0.0)))/log(2.0)/getoctavesfreq());
};


/*
 * Get the freq. response of the formant filter
 */
void FilterParams::formantfilterH(int nvowel,int nfreqs,REALTYPE *freqs){
    REALTYPE c[3],d[3];
    REALTYPE filter_freq,filter_q,filter_amp;
    REALTYPE omega,sn,cs,alpha;

    for (int i=0;i<nfreqs;i++) freqs[i]=0.0;

    //for each formant...
    for (int nformant=0;nformant<Pnumformants;nformant++){
	//compute formant parameters(frequency,amplitude,etc.)
	filter_freq=getformantfreq(Pvowels[nvowel].formants[nformant].freq);
	filter_q=getformantq(Pvowels[nvowel].formants[nformant].q)*getq();
	if (Pstages>0) filter_q=(filter_q>1.0 ? pow(filter_q,1.0/(Pstages+1)) : filter_q);

	filter_amp=getformantamp(Pvowels[nvowel].formants[nformant].amp);


	if (filter_freq<=(SAMPLE_RATE/2-100.0)){
	    omega=2*double_Pi*filter_freq/SAMPLE_RATE;
	    sn=sin(omega);
    	    cs=cos(omega);
	    alpha=sn/(2*filter_q);
	    REALTYPE tmp=1+alpha;
	    c[0]=alpha/tmp*sqrt(filter_q+1);
	    c[1]=0;
	    c[2]=-alpha/tmp*sqrt(filter_q+1);
	    d[1]=-2*cs/tmp*(-1);
	    d[2]=(1-alpha)/tmp*(-1);
	} else continue;


	for (int i=0;i<nfreqs;i++) {
	    REALTYPE freq=getfreqx(i/(REALTYPE) nfreqs);
	    if (freq>SAMPLE_RATE/2) {
		for (int tmp=i;tmp<nfreqs;tmp++) freqs[tmp]=0.0;
		break;
	    };
	    REALTYPE fr=freq/SAMPLE_RATE*double_Pi*2.0;
	    REALTYPE x=c[0],y=0.0;
    	    for (int n=1;n<3;n++){
    		x+=cos(n*fr)*c[n];
		y-=sin(n*fr)*c[n];
	    };
	    REALTYPE h=x*x+y*y;
	    x=1.0;y=0.0;
	    for (int n=1;n<3;n++){
		x-=cos(n*fr)*d[n];
		y+=sin(n*fr)*d[n];
	    };
	    h=h/(x*x+y*y);

	    freqs[i]+=pow(h,(Pstages+1.0)/2.0)*filter_amp;
	};
    };
    for (int i=0;i<nfreqs;i++) {
	if (freqs[i]>0.000000001) freqs[i]=rap2dB(freqs[i])+getgain();
	else freqs[i]=-90.0;
    };

};

/*
 * Transforms a parameter to the real value
 */
REALTYPE FilterParams::getformantfreq(unsigned char freq){
    REALTYPE result=getfreqx(freq/127.0);
    return(result);
};

REALTYPE FilterParams::getformantamp(unsigned char amp){
    REALTYPE result=pow(0.1,(1.0-amp/127.0)*4.0);
    return(result);
};

REALTYPE FilterParams::getformantq(unsigned char q){
    //temp
    REALTYPE result=pow(25.0,(q-32.0)/64.0);
    return(result);
};


void FilterParams::addToXML (XmlElement* xml)
{
    xml->setAttribute (T("cat"), Pcategory);
    xml->setAttribute (T("type"), Ptype);
    xml->setAttribute (T("freq"), Pfreq);
    xml->setAttribute (T("q"), Pq);
    xml->setAttribute (T("stgs"), Pstages);
    xml->setAttribute (T("frqtrk"), Pfreqtrack);
    xml->setAttribute (T("vol"), Pgain);

    //formant filter parameters
    if (Pcategory == 1)
    {
        XmlElement* e = new XmlElement (T("fmtflt"));
        e->setAttribute (T("nfmts"), Pnumformants);
        e->setAttribute (T("fmtsl"), Pformantslowness);
        e->setAttribute (T("vwcl"), Pvowelclearness);
        e->setAttribute (T("cntfrq"), Pcenterfreq);
        e->setAttribute (T("octfrq"), Poctavesfreq);

        for (int i = 0; i < FF_MAX_VOWELS; i++)
        {
            XmlElement* ev = new XmlElement (T("vw"));
            addToXMLSection (ev, i);
            e->addChildElement (ev);
        }

        e->setAttribute (T("sqsize"), Psequencesize);
        e->setAttribute (T("sqstrt"), Psequencestretch);
        e->setAttribute (T("sqrev"), Psequencereversed);
        for (int i = 0; i < FF_MAX_SEQUENCE; i++)
        {
            XmlElement* es = new XmlElement (T("s"));
            es->setAttribute (T("id"), Psequence[i].nvowel);
            e->addChildElement (es);
        }

        xml->addChildElement (e);
    }
}

void FilterParams::addToXMLSection (XmlElement* xml, int section)
{
    for (int nformant = 0; nformant < FF_MAX_FORMANTS; nformant++)
    {
        XmlElement* e = new XmlElement (T("fmt"));
        e->setAttribute (T("frq"), Pvowels[section].formants[nformant].freq);
        e->setAttribute (T("amp"), Pvowels[section].formants[nformant].amp);
        e->setAttribute (T("q"), Pvowels[section].formants[nformant].q);
        xml->addChildElement (e);
    }
}

void FilterParams::updateFromXML (XmlElement *xml)
{
    //filter parameters
    Pcategory = xml->getIntAttribute (T("cat"), Pcategory);
    Ptype = xml->getIntAttribute (T("type"), Ptype);
    Pfreq = xml->getIntAttribute (T("frq"), Pfreq);
    Pq = xml->getIntAttribute (T("q"), Pq);
    Pstages = xml->getIntAttribute (T("stgs"), Pstages);
    Pfreqtrack = xml->getIntAttribute (T("frqtrk"), Pfreqtrack);
    Pgain = xml->getIntAttribute (T("gain"), Pgain);

    //formant filter parameters
    XmlElement* e = xml->getChildByName (T("fmtflt"));
    if (e)
    {
        Pnumformants = xml->getIntAttribute (T("nfmts"), Pnumformants);
        Pformantslowness = xml->getIntAttribute (T("fmtsl"), Pformantslowness);
        Pvowelclearness = xml->getIntAttribute (T("vwcl"), Pvowelclearness);
        Pcenterfreq = xml->getIntAttribute (T("cntfrq"), Pcenterfreq);
        Poctavesfreq = xml->getIntAttribute (T("octfrq"), Poctavesfreq);

        int nvowel = 0;
        forEachXmlChildElement (*xml, ev)
        {
            if (nvowel >= FF_MAX_VOWELS) break;
            if (ev->hasTagName (T("vw")))
                updateFromXMLSection (ev, nvowel++);
        }

        Psequencesize = xml->getIntAttribute (T("sqsize"), Psequencesize);
        Psequencestretch = xml->getIntAttribute (T("sqstrt"), Psequencestretch);
        Psequencereversed = xml->getIntAttribute (T("sqrev"), Psequencereversed); // 0..1

        int nseq = 0;
        forEachXmlChildElement (*xml, es)
        {
            if (nseq >= FF_MAX_SEQUENCE) break;
            if (es->hasTagName (T("s")))
            {
                Psequence [nseq].nvowel = es->getIntAttribute (T("id"), Psequence[nseq].nvowel); // 0, FF_MAX_VOWELS-1
                nseq++;
            }
        }
    }
}

void FilterParams::updateFromXMLSection (XmlElement *xml, int section)
{
    int nformant = 0;
    forEachXmlChildElement (*xml, e)
    {
        if (nformant >= FF_MAX_FORMANTS)
            break;

        if (e->hasTagName (T("fmt")))
        {
            Pvowels[section].formants[nformant].freq = e->getIntAttribute (T("frq"), Pvowels[section].formants[nformant].freq);
            Pvowels[section].formants[nformant].amp = e->getIntAttribute (T("amp"), Pvowels[section].formants[nformant].amp);
            Pvowels[section].formants[nformant].q = e->getIntAttribute (T("q"), Pvowels[section].formants[nformant].q);

            nformant++;
        }
    }
}




