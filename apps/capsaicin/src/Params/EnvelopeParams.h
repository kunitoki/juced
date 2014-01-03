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

#ifndef __JUCETICE_XSYNTHENVELOPEPARAMS_HEADER__
#define __JUCETICE_XSYNTHENVELOPEPARAMS_HEADER__

#include "Presets.h"


class EnvelopeParams : public Presets
{
public:

    EnvelopeParams (unsigned char Penvstretch_,unsigned char Pforcedrelease_);
    ~EnvelopeParams ();

    void ADSRinit (char A_dt,char D_dt,char S_val,char R_dt);
    void ADSRinit_dB (char A_dt,char D_dt,char S_val,char R_dt);
    void ASRinit (char A_val,char A_dt,char R_val,char R_dt);
    void ADSRinit_filter (char A_val,char A_dt,char D_val,char D_dt,char R_dt,char R_val);
    void ASRinit_bw (char A_val,char A_dt,char R_val,char R_dt);
    void converttofree ();
    void defaults ();

    void addToXML (XmlElement* xml);
    void updateFromXML (XmlElement *xml);

    REALTYPE getdt (char i);

    // MIDI Parameters
    unsigned char Pfreemode; // 0..1 if free mode
    unsigned char Penvpoints;
    unsigned char Penvsustain; // 127
    unsigned char Penvdt[MAX_ENVELOPE_POINTS];
    unsigned char Penvval[MAX_ENVELOPE_POINTS];
    unsigned char Penvstretch; //64=normal stretch (piano-like), 0=no stretch
    unsigned char Pforcedrelease; //0 - OFF, 1 - ON
    unsigned char Plinearenvelope; //if the amplitude envelope is linear

    unsigned char PA_dt,PD_dt,PR_dt,
                  PA_val,PD_val,PS_val,PR_val;

    int Envmode; // 1 for ADSR parameters (linear amplitude)
                 // 2 for ADSR_dB parameters (dB amplitude)
                 // 3 for ASR parameters (frequency LFO)
                 // 4 for ADSR_filter parameters (filter parameters)
                 // 5 for ASR_bw parameters (bandwidth parameters)

private:

    void store2defaults();

    // Default parameters
    unsigned char Denvstretch;
    unsigned char Dforcedrelease;
    unsigned char Dlinearenvelope;
    unsigned char DA_dt,DD_dt,DR_dt,
                  DA_val,DD_val,DS_val,DR_val;
};


#endif

