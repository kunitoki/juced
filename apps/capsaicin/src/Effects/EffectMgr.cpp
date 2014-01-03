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

#include "EffectMgr.h"


//==============================================================================
EffectMgr::EffectMgr (int insertion_, CriticalSection *mutex_)
{
    setpresettype ("effect");

    efx  = NULL;
    nefx = 0;
    insertion = insertion_;
    mutex = mutex_;
    efxoutl = new REALTYPE [SOUND_BUFFER_SIZE];
    efxoutr = new REALTYPE [SOUND_BUFFER_SIZE];
    for (int i = 0; i < SOUND_BUFFER_SIZE; i++)
    {
        efxoutl[i] = 0.0;
        efxoutr[i] = 0.0;
    }
    filterpars = NULL;
    dryonly = false;

    defaults();
}

EffectMgr::~EffectMgr()
{
    if (efx != NULL) delete (efx);
    delete[] (efxoutl);
    delete[] (efxoutr);
}

//==============================================================================
void EffectMgr::defaults()
{
    changeEffect (0);
    setdryonly (false);
}

//==============================================================================
void EffectMgr::changeEffect (int nefx_)
{
    clean();
    if (nefx == nefx_) return;
    nefx = nefx_;

    for (int i = 0; i < SOUND_BUFFER_SIZE; i++)
    {
        efxoutl[i] = 0.0;
        efxoutr[i] = 0.0;
    }

    if (efx != NULL) delete (efx);

    switch (nefx){
    case 1: efx = new Reverb (insertion, efxoutl, efxoutr); break;
    case 2: efx = new Echo (insertion, efxoutl, efxoutr); break;
    case 3: efx = new Chorus (insertion, efxoutl, efxoutr); break;
    case 4: efx = new Phaser (insertion, efxoutl, efxoutr); break;
    case 5: efx = new Alienwah (insertion, efxoutl, efxoutr); break;
    case 6: efx = new Distorsion (insertion, efxoutl, efxoutr); break;
    case 7: efx = new EQ (insertion, efxoutl, efxoutr); break;
    case 8: efx = new DynamicFilter (insertion, efxoutl, efxoutr); break;
    case 9: efx = new SC4Compressor (insertion, efxoutl, efxoutr); break;
    case 10: efx = new GReverb (insertion, efxoutl, efxoutr); break;
    // put more effect here
    default: efx = NULL; break; // no effect (thru)
    }

    if (efx != NULL) filterpars = efx->filterpars;
}

//==============================================================================
// @XXX - inline !
int EffectMgr::getEffect()
{
    return (nefx);
}

//==============================================================================
void EffectMgr::clean()
{
    if (efx != NULL) efx->clean();
}

//==============================================================================
uint8 EffectMgr::getPreset()
{
    if (efx != NULL) return (efx->Ppreset);
    else return (0);
}

void EffectMgr::changePresetNoLock (uint8 npreset)
{
    if (efx != NULL) efx->setPreset (npreset);
}

void EffectMgr::changePreset (uint8 npreset)
{
    mutex->enter();
        changePresetNoLock (npreset);
    mutex->exit();
}

//==============================================================================
uint8 EffectMgr::getEffectParameter (int npar)
{
    if (efx == NULL) return (0);
    return efx->getParameter (npar);
}

void EffectMgr::setEffectParameterNoLock (int npar, uint8 value)
{
    if (efx == NULL) return;
    efx->setParameter (npar, value);
}

void EffectMgr::setEffectParameter (int npar, uint8 value)
{
    mutex->enter();
        setEffectParameterNoLock (npar, value);
    mutex->exit();
}

//==============================================================================
void EffectMgr::out (REALTYPE *smpsl, REALTYPE *smpsr, const int numSamples)
{
    int i;
    if (efx == NULL)
    {
        if (insertion == 0)
            for (i = 0; i < numSamples; i++)
            {
                smpsl[i] = 0.0;
                smpsr[i] = 0.0;
                efxoutl[i] = 0.0;
                efxoutr[i] = 0.0;
            }
        return;
    }

    for (i = 0;i < numSamples; i++)
    {
        smpsl[i] += denormalkillbuf[i];
        smpsr[i] += denormalkillbuf[i];
        efxoutl[i] = 0.0;
        efxoutr[i] = 0.0;
    }

    REALTYPE volume = efx->volume;
    if (volume == 0) return;

    efx->out (smpsl, smpsr, numSamples);

    if (nefx == 7)
    {
        // this is need only for the EQ effect
        for (i = 0; i < numSamples; i++)
        {
            smpsl[i] = efxoutl[i];
            smpsr[i] = efxoutr[i];
        }
        return;
    }

    if (insertion != 0)
    {
        // Insertion effect
        REALTYPE v1,v2;
        if (volume < 0.5)
        {
            v1 = 1.0;
            v2 = volume * 2.0;
        }
        else
        {
            v1 = (1.0 - volume) * 2.0;
            v2 = 1.0;
        }

        if ((nefx == 1) || (nefx == 2))
            v2 *= v2; // for Reverb and Echo, the wet function is not liniar

        if (dryonly)
        {
            //this is used for instrument effect only
            for (i = 0; i < numSamples; i++)
            {
                smpsl[i] *= v1;
                smpsr[i] *= v1;
                efxoutl[i] *= v2;
                efxoutr[i] *= v2;
            }
        }
        else
        {
            // normal instrument/insertion effect
            for (i = 0; i < numSamples; i++)
            {
                smpsl[i] = smpsl[i] * v1 + efxoutl[i] * v2;
                smpsr[i] = smpsr[i] * v1 + efxoutr[i] * v2;
            }
        }

    }
    else
    {
        //System effect
        for (i = 0; i < numSamples; i++)
        {
            efxoutl[i] *= 2.0 * volume;
            efxoutr[i] *= 2.0 * volume;
            smpsl[i] = efxoutl[i];
            smpsr[i] = efxoutr[i];
        }
    }
}

//==============================================================================
REALTYPE EffectMgr::sysefxgetvolume()
{
    if (efx == NULL) return 1.0;
    else             return efx->outvolume;
}


//==============================================================================
REALTYPE EffectMgr::getEQfreqresponse (REALTYPE freq)
{
    if (nefx == 7) return efx->getFrequencyResponse (freq);
    else return 0.0;
}

//==============================================================================
void EffectMgr::setdryonly (bool value)
{
    dryonly = value;
}

//==============================================================================
void EffectMgr::addToXML (XmlElement* xml)
{
    xml->setAttribute (T("type"), getEffect());

    if (efx == NULL || getEffect() == 0) return;

    xml->setAttribute (T("prst"), efx->Ppreset);

    {
    XmlElement* e = new XmlElement (T("fxpar"));
    for (int n = 0; n < 128; n++)
    {
        int par = getEffectParameter (n);
        if (par == 0) continue;

        XmlElement* pe = new XmlElement (T("p") + String (n));
        pe->setAttribute (T("v"), par);
        e->addChildElement (pe);
    }
    xml->addChildElement (e);
    }

    if (filterpars != NULL)
    {
        XmlElement* e = new XmlElement (T("flt"));
        filterpars->addToXML (e);
        xml->addChildElement (e);
    }
}

void EffectMgr::updateFromXML (XmlElement *xml)
{
    changeEffect (xml->getIntAttribute (T("type"), getEffect()));

    if (efx == NULL || getEffect() == 0) return;

    efx->Ppreset = xml->getIntAttribute (T("prst"), efx->Ppreset);

    {
    XmlElement* e = xml->getChildByName (T("fxpar"));
    if (e)
    {
        for (int n = 0; n < 128; n++)
        {
            setEffectParameterNoLock (n, 0); // erase effect parameter

            XmlElement* pe = e->getChildByName (T("p") + String (n));
            if (pe)
                setEffectParameterNoLock (n, pe->getIntAttribute (T("v"), getEffectParameter (n)));
        }
    }
    }

    if (filterpars != NULL)
    {
        {
        XmlElement* e = xml->getChildByName (T("flt"));
        if (e) filterpars->updateFromXML (e);
        }
    }

    clean();
}
