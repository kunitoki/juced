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

#include <math.h>
#include <stdio.h>
#include "../globals.h"
#include "LFOParams.h"

int LFOParams::time;

LFOParams::LFOParams(char Pfreq_,char Pintensity_,char Pstartphase_, char PLFOtype_,char Prandomness_, char Pdelay_,char Pcontinous_,char fel_):Presets(){
    switch(fel_) {
	case 0:setpresettype("Plfofrequency");
	    break;
	case 1:setpresettype("Plfoamplitude");
	    break;
	case 2:setpresettype("Plfofilter");
	    break;
    };
    Dfreq=Pfreq_;
    Dintensity=Pintensity_;
    Dstartphase=Pstartphase_;
    DLFOtype=PLFOtype_;
    Drandomness=Prandomness_;
    Ddelay=Pdelay_;
    Dcontinous=Pcontinous_;
    fel=fel_;
    time=0;

    defaults();
};

LFOParams::~LFOParams(){
};

void LFOParams::defaults(){
    Pfreq=Dfreq/127.0;
    Pintensity=Dintensity;
    Pstartphase=Dstartphase;
    PLFOtype=DLFOtype;
    Prandomness=Drandomness;
    Pdelay=Ddelay;
    Pcontinous=Dcontinous;
    Pfreqrand=0;
    Pstretch=64;
};


void LFOParams::addToXML (XmlElement* xml)
{
    xml->setAttribute (T("frq"), Pfreq);
    xml->setAttribute (T("int"), Pintensity);
    xml->setAttribute (T("phs"), Pstartphase);
    xml->setAttribute (T("typ"), PLFOtype);
    xml->setAttribute (T("ramp"), Prandomness);
    xml->setAttribute (T("rfrq"), Pfreqrand);
    xml->setAttribute (T("dly"), Pdelay);
    xml->setAttribute (T("str"), Pstretch);
    xml->setAttribute (T("con"), Pcontinous);
}

void LFOParams::updateFromXML (XmlElement *xml)
{
    Pfreq = xml->getDoubleAttribute (T("frq"), Pfreq); // 0.0,1.0
    Pintensity = xml->getIntAttribute (T("int"), Pintensity); // 0..127
    Pstartphase = xml->getIntAttribute (T("phs"), Pstartphase); // 0..127
    PLFOtype = xml->getIntAttribute (T("typ"), PLFOtype); // 0..127
    Prandomness = xml->getIntAttribute (T("ramp"), Prandomness); // 0.127
    Pfreqrand = xml->getIntAttribute (T("rfrq"), Pfreqrand); // 0..127
    Pdelay = xml->getIntAttribute (T("dly"), Pdelay); // 0..127
    Pstretch = xml->getIntAttribute (T("str"),Pstretch); // 0..127
    Pcontinous = xml->getIntAttribute (T("con"), Pcontinous); // 0..1
}
