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

#ifndef __JUCETICE_XSYNTHLFOPARAMS_HEADER__
#define __JUCETICE_XSYNTHLFOPARAMS_HEADER__

#include "Presets.h"

class LFOParams : public Presets
{
public:

    LFOParams (char Pfreq_,
               char Pintensity_,
               char Pstartphase_,
               char PLFOtype_,
               char Prandomness_,
               char Pdelay_,
               char Pcontinous_,
               char fel_);

    ~LFOParams();

    void defaults ();

    void addToXML (XmlElement* xml);
    void updateFromXML (XmlElement *xml);

    // Parametrii MIDI
    REALTYPE Pfreq;              // frequency
    unsigned char Pintensity;    // intensity
    unsigned char Pstartphase;   // start phase (0=random)
    unsigned char PLFOtype;      // LFO type (sin,triangle,square,ramp,...)
    unsigned char Prandomness;   // randomness (0=off)
    unsigned char Pfreqrand;     // frequency randomness (0=off)
    unsigned char Pdelay;        // delay (0=off)
    unsigned char Pcontinous;    // 1 if LFO is continous
    unsigned char Pstretch;      // how the LFO is "stretched" according the note frequency (64=no stretch)

    int fel;                     //what kind is the LFO (0 - frequency, 1 - amplitude, 2 - filter)
    static int time;             //is used by Pcontinous parameter

private:

    // Default parameters
    unsigned char Dfreq;
    unsigned char Dintensity;
    unsigned char Dstartphase;
    unsigned char DLFOtype;
    unsigned char Drandomness;
    unsigned char Ddelay;
    unsigned char Dcontinous;
};

#endif
