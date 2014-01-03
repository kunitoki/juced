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

#include <stdio.h>

#include <math.h>
#include <stdlib.h>
#include "EnvelopeParams.h"

EnvelopeParams::EnvelopeParams (unsigned char Penvstretch_,
                                unsigned char Pforcedrelease_)
{
    int i;

    PA_dt = 10; PD_dt = 10; PR_dt = 10;
    PA_val = 64; PD_val = 64; PS_val = 64; PR_val = 64;

    for (i = 0; i < MAX_ENVELOPE_POINTS; i++)
    {
        Penvdt[i] = 32;
        Penvval[i] = 64;
    }

    Penvdt[0] = 0; //no used
    Penvsustain = 1;
    Penvpoints = 1;
    Envmode = 1;
    Penvstretch = Penvstretch_;
    Pforcedrelease = Pforcedrelease_;
    Pfreemode = 1;
    Plinearenvelope = 0;

    store2defaults();
}

EnvelopeParams::~EnvelopeParams()
{
}

REALTYPE EnvelopeParams::getdt(char i)
{
    REALTYPE result = (pow (2.0, Penvdt[(int) i] / 127.0 * 12.0) - 1.0) * 10.0; //miliseconds
    return (result);
}

void EnvelopeParams::ADSRinit(char A_dt,char D_dt,char S_val,char R_dt)
{
    setpresettype("ampEnvelope");
    Envmode=1;
    PA_dt=A_dt;PD_dt=D_dt;PS_val=S_val;PR_dt=R_dt;
    Pfreemode=0;
    converttofree();

    store2defaults();
}

void EnvelopeParams::ADSRinit_dB(char A_dt,char D_dt,char S_val,char R_dt)
{
    setpresettype("ampEnvelope");
    Envmode=2;
    PA_dt=A_dt;PD_dt=D_dt;PS_val=S_val;PR_dt=R_dt;
    Pfreemode=0;
    converttofree();

    store2defaults();
}

void EnvelopeParams::ASRinit(char A_val,char A_dt,char R_val,char R_dt)
{
    setpresettype("freqEnvelope");
    Envmode=3;
    PA_val=A_val;PA_dt=A_dt;PR_val=R_val;PR_dt=R_dt;
    Pfreemode=0;
    converttofree();

    store2defaults();
}

void EnvelopeParams::ADSRinit_filter(char A_val,char A_dt,char D_val,char D_dt,char R_dt,char R_val)
{
    setpresettype("filterEnvelope");
    Envmode=4;
    PA_val=A_val;PA_dt=A_dt;PD_val=D_val;PD_dt=D_dt;PR_dt=R_dt;PR_val=R_val;
    Pfreemode=0;
    converttofree();
    store2defaults();
}

void EnvelopeParams::ASRinit_bw(char A_val,char A_dt,char R_val,char R_dt)
{
    setpresettype("bwEnvelope");
    Envmode=5;
    PA_val=A_val;PA_dt=A_dt;PR_val=R_val;PR_dt=R_dt;
    Pfreemode=0;
    converttofree();
    store2defaults();
}

void EnvelopeParams::converttofree()
{
    switch (Envmode)
    {
    case 1:
        Penvpoints=4;
        Penvsustain=2;
        Penvval[0]=0;
        Penvdt[1]=PA_dt; Penvval[1]=127;
        Penvdt[2]=PD_dt; Penvval[2]=PS_val;
        Penvdt[3]=PR_dt; Penvval[3]=0;
        break;
    case 2:
        Penvpoints=4;
        Penvsustain=2;
        Penvval[0]=0;
        Penvdt[1]=PA_dt; Penvval[1]=127;
        Penvdt[2]=PD_dt; Penvval[2]=PS_val;
        Penvdt[3]=PR_dt; Penvval[3]=0;
        break;
    case 3:
/* @XXX - original
        Penvpoints=3;
        Penvsustain=1;
        Penvval[0]=PA_val;
        Penvdt[1]=PA_dt; Penvval[1]=64;
        Penvdt[2]=PR_dt; Penvval[2]=PR_val;
*/
        Penvpoints=4;
        Penvsustain=2;
        Penvval[0]=PA_val;
        Penvdt[1]=PA_dt; Penvval[1]=PD_val;
        Penvdt[2]=PD_dt; Penvval[2]=64;
        Penvdt[3]=PR_dt; Penvval[3]=PR_val;
        break;
    case 4:
        Penvpoints=4;
        Penvsustain=2;
        Penvval[0]=PA_val;
        Penvdt[1]=PA_dt; Penvval[1]=PD_val;
        Penvdt[2]=PD_dt; Penvval[2]=64;
        Penvdt[3]=PR_dt; Penvval[3]=PR_val;
        break;
    case 5:
        Penvpoints=3;
        Penvsustain=1;
        Penvval[0]=PA_val;
        Penvdt[1]=PA_dt; Penvval[1]=64;
        Penvdt[2]=PR_dt; Penvval[2]=PR_val;
        break;
    }
}

void EnvelopeParams::defaults()
{
    Penvstretch = Denvstretch;
    Pforcedrelease = Dforcedrelease;
    Plinearenvelope = Dlinearenvelope;
    PA_dt = DA_dt;
    PD_dt = DD_dt;
    PR_dt = DR_dt;
    PA_val = DA_val;
    PD_val = DD_val;
    PS_val = DS_val;
    PR_val = DR_val;
    Pfreemode = 0;

    converttofree();
}

void EnvelopeParams::store2defaults()
{
    Denvstretch = Penvstretch;
    Dforcedrelease = Pforcedrelease;
    Dlinearenvelope = Plinearenvelope;
    DA_dt = PA_dt;
    DD_dt = PD_dt;
    DR_dt = PR_dt;
    DA_val = PA_val;
    DD_val = PD_val;
    DS_val = PS_val;
    DR_val = PR_val;
}

void EnvelopeParams::addToXML (XmlElement* xml)
{
    xml->setAttribute (T("free"), Pfreemode);
    xml->setAttribute (T("envpnts"), Penvpoints);
    xml->setAttribute (T("envsust"), Penvsustain);
    xml->setAttribute (T("envstrt"), Penvstretch);
    xml->setAttribute (T("frcrel"), Pforcedrelease);
    xml->setAttribute (T("linenv"), Plinearenvelope);
    xml->setAttribute (T("at"), PA_dt);
    xml->setAttribute (T("dt"), PD_dt);
    xml->setAttribute (T("rt"), PR_dt);
    xml->setAttribute (T("av"), PA_val);
    xml->setAttribute (T("dv"), PD_val);
    xml->setAttribute (T("sv"), PS_val);
    xml->setAttribute (T("rv"), PR_val);

    if (Pfreemode != 0)
    {
        for (int i = 0; i < Penvpoints; i++)
        {
            XmlElement* e = new XmlElement (T("pnt") + String (i));
            if (i != 0) e->setAttribute (T("t"), Penvdt[i]);
            e->setAttribute (T("v"), Penvval[i]);
            xml->addChildElement (e);
        }
    }
}

void EnvelopeParams::updateFromXML (XmlElement *xml)
{
    Pfreemode = xml->getIntAttribute (T("free"), Pfreemode); // 0..1
    Penvpoints = xml->getIntAttribute (T("envpnts"), Penvpoints);
    Penvsustain = xml->getIntAttribute (T("envsust"), Penvsustain);
    Penvstretch = xml->getIntAttribute (T("envstrt"), Penvstretch);
    Pforcedrelease = xml->getIntAttribute (T("frcrel"), Pforcedrelease); // 0..1
    Plinearenvelope = xml->getIntAttribute (T("linenv"), Plinearenvelope); // 0..1

    PA_dt = xml->getIntAttribute (T("at"), PA_dt);
    PD_dt = xml->getIntAttribute (T("dt"), PD_dt);
    PR_dt = xml->getIntAttribute (T("rt"), PR_dt);
    PA_val = xml->getIntAttribute (T("av"), PA_val);
    PD_val = xml->getIntAttribute (T("dv"), PD_val);
    PS_val = xml->getIntAttribute (T("sv"), PS_val);
    PR_val = xml->getIntAttribute (T("rv"), PR_val);

    for (int i = 0; i < Penvpoints; i++)
    {
        XmlElement* e = xml->getChildByName (T("pnt") + String (i));
        if (e)
        {
            if (i != 0) Penvdt[i] = e->getIntAttribute (T("t"), Penvdt[i]);
            Penvval[i] = xml->getIntAttribute (T("v"), Penvval[i]);
        }
    }

    if (! Pfreemode) converttofree();
}

