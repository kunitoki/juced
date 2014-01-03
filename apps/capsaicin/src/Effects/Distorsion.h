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

#ifndef __JUCETICE_XSYNTHDISTORSION_HEADER__
#define __JUCETICE_XSYNTHDISTORSION_HEADER__

#include "../globals.h"
#include "../DSP/AnalogFilter.h"
#include "Effect.h"


// Waveshaping (called by Distorsion effect and waveshape from OscilGen)
void waveshapesmps (int n, REALTYPE *smps, uint8 type, uint8 drive);


class Distorsion : public Effect
{
public:
    Distorsion (int insertion, REALTYPE *efxoutl_, REALTYPE *efxoutr_);
    ~Distorsion();

    void setPreset (uint8 npreset);
    void setParameter (int npar, uint8 value);
    uint8 getParameter (int npar);
    void out (REALTYPE *smpsl, REALTYPE *smpr, const int numSamples);
    void clean();

    void applyfilters (REALTYPE *efxoutl, REALTYPE *efxoutr, int numSamples);

private:

    uint8 Pvolume;       // Volumul or E/R
    uint8 Ppanning;      // Panning
    uint8 Plrcross;      // L/R Mixing
    uint8 Pdrive;        // the input amplification
    uint8 Plevel;        // the ouput amplification
    uint8 Ptype;         // Distorsion type
    uint8 Pnegate;       // if the input is negated
    uint8 Plpf;          // lowpass filter
    uint8 Phpf;          // highpass filter
    uint8 Pstereo;       // 0=mono,1=stereo
    uint8 Pprefiltering; // if you want to do the filtering before the distorsion

    void setvolume (uint8 Pvolume);
    void setpanning (uint8 Ppanning);
    void setlrcross (uint8 Plrcross);
    void setdrive (uint8 Pdrive);
    void setlevel (uint8 Plevel);
    void setlpf (uint8 Plpf);
    void sethpf (uint8 Phpf);

    REALTYPE panning,lrcross;
    REALTYPE inputvol, level;
    AnalogFilter *lpfl,*lpfr,*hpfl,*hpfr;
};


#endif
