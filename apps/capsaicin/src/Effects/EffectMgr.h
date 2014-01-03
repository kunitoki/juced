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

#ifndef __JUCETICE_XSYNTHEFFECTMGR_HEADER__
#define __JUCETICE_XSYNTHEFFECTMGR_HEADER__

#include "Effect.h"
#include "Reverb.h"
#include "Echo.h"
#include "Chorus.h"
#include "Phaser.h"
#include "Alienwah.h"
#include "Distorsion.h"
#include "EQ.h"
#include "DynamicFilter.h"
#include "GReverb.h"
#include "SC4Compressor.h"
#include "../Params/FilterParams.h"
#include "../Params/Presets.h"


class EffectMgr : public Presets
{
public:

    EffectMgr (int insertion_, CriticalSection *mutex_);
    ~EffectMgr();

    void defaults();

    void addToXML (XmlElement* xml);
    void updateFromXML (XmlElement *xml);

    void out (REALTYPE *smpsl, REALTYPE *smpsr, const int numSamples);
    void clean();

    void setdryonly(bool value);

    // get the output(to speakers) volume of the systemeffect
    REALTYPE sysefxgetvolume();

    void changeEffect (int nefx_);
    int getEffect ();
    void changePreset (uint8 npreset);
    void changePresetNoLock (uint8 npreset);
    uint8 getPreset ();
    void setEffectParameter (int npar, uint8 value);
    void setEffectParameterNoLock (int npar, uint8 value);
    uint8 getEffectParameter (int npar);
    int insertion;//1 if the effect is connected as insertion effect
    REALTYPE *efxoutl,*efxoutr;

    //used by UI
    REALTYPE getEQfreqresponse(REALTYPE freq);

    FilterParams *filterpars;

private:
    int nefx;
    Effect *efx;
    CriticalSection *mutex;
    bool dryonly;
};


#endif
