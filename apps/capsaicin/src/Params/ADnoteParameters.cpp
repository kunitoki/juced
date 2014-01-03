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

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <iostream>

#include "ADnoteParameters.h"

ADnoteParameters::ADnoteParameters (FFTWrapper *fft_)
{
    setpresettype ("capsaicin");
    fft = fft_;

    GlobalPar.FreqEnvelope = new EnvelopeParams (0, 0);
    GlobalPar.FreqEnvelope->ASRinit (64, 50, 64, 60);
    GlobalPar.FreqLfo = new LFOParams (70, 0, 64, 0, 0, 0, 0, 0);

    GlobalPar.AmpEnvelope = new EnvelopeParams (64, 1);
    GlobalPar.AmpEnvelope->ADSRinit_dB (0, 40, 127, 25);
    GlobalPar.AmpLfo = new LFOParams (80, 0, 64, 0, 0, 0, 0, 1);

    GlobalPar.GlobalFilter = new FilterParams (2,94,40);
    GlobalPar.FilterEnvelope = new EnvelopeParams (0,1);
    GlobalPar.FilterEnvelope->ADSRinit_filter (64, 40, 64, 70, 60, 64);
    GlobalPar.FilterLfo = new LFOParams (80, 0, 64, 0, 0, 0, 0, 2);
    GlobalPar.Reson = new Resonance();

    for (int nvoice = 0; nvoice < NUM_VOICES; nvoice++)
        EnableVoice (nvoice);

    defaults();
}

ADnoteParameters::~ADnoteParameters ()
{
    delete(GlobalPar.FreqEnvelope);
    delete(GlobalPar.FreqLfo);
    delete(GlobalPar.AmpEnvelope);
    delete(GlobalPar.AmpLfo);
    delete(GlobalPar.GlobalFilter);
    delete(GlobalPar.FilterEnvelope);
    delete(GlobalPar.FilterLfo);
    delete(GlobalPar.Reson);

    for (int nvoice=0;nvoice<NUM_VOICES;nvoice++)
        KillVoice(nvoice);
}

void ADnoteParameters::defaults()
{
    // Default Parameters
    // Frequency Global Parameters
    GlobalPar.PStereo=1;//stereo
    GlobalPar.PDetune=8192;//zero
    GlobalPar.PCoarseDetune=0;
    GlobalPar.PDetuneType=1;
    GlobalPar.FreqEnvelope->defaults();
    GlobalPar.FreqLfo->defaults();
    GlobalPar.PBandwidth=64;

    // Amplitude Global Parameters
    GlobalPar.PVolume=90;
    GlobalPar.PPanning=64;//center
    GlobalPar.PJoyX=64;
    GlobalPar.PJoyY=64;
    GlobalPar.PAmpVelocityScaleFunction=64;
    GlobalPar.AmpEnvelope->defaults();
    GlobalPar.AmpLfo->defaults();
    GlobalPar.PPunchStrength=0;
    GlobalPar.PPunchTime=60;
    GlobalPar.PPunchStretch=64;
    GlobalPar.PPunchVelocitySensing=72;
    GlobalPar.Hrandgrouping=0;

    // Filter Global Parameters
    GlobalPar.PFilterVelocityScale=64;
    GlobalPar.PFilterVelocityScaleFunction=64;
    GlobalPar.GlobalFilter->defaults();
    GlobalPar.FilterEnvelope->defaults();
    GlobalPar.FilterLfo->defaults();
    GlobalPar.Reson->defaults();

    for (int nvoice = 0; nvoice < NUM_VOICES; nvoice++)
        defaults (nvoice);
    VoicePar[0].Enabled=1;
}

// Defaults a voice
void ADnoteParameters::defaults (int n)
{
    int nvoice=n;
    VoicePar[nvoice].Enabled=0;
    VoicePar[nvoice].Type=0;
    VoicePar[nvoice].Pfixedfreq=0;
    VoicePar[nvoice].PfixedfreqET=0;
    VoicePar[nvoice].Presonance=0;
    VoicePar[nvoice].Pfilterbypass=0;
    VoicePar[nvoice].Pextoscil=-1;
    VoicePar[nvoice].PextFMoscil=-1;
    VoicePar[nvoice].Poscilphase=64;
    VoicePar[nvoice].PFMoscilphase=64;
    VoicePar[nvoice].PDelay=0;
    VoicePar[nvoice].PVolume=100;
    VoicePar[nvoice].PVolumeminus=0;
    VoicePar[nvoice].PPanning=64;//center
    VoicePar[nvoice].PDetune=8192;//8192=0
    VoicePar[nvoice].PCoarseDetune=0;
    VoicePar[nvoice].PDetuneType=0;
    VoicePar[nvoice].PFreqLfoEnabled=0;
    VoicePar[nvoice].PFreqEnvelopeEnabled=0;
    VoicePar[nvoice].PAmpEnvelopeEnabled=0;
    VoicePar[nvoice].PAmpLfoEnabled=0;
    VoicePar[nvoice].PAmpVelocityScaleFunction=127;
    VoicePar[nvoice].PFilterEnabled=0;
    VoicePar[nvoice].PFilterEnvelopeEnabled=0;
    VoicePar[nvoice].PFilterLfoEnabled=0;
    VoicePar[nvoice].PFMEnabled=0;

    //I use the internal oscillator (-1)
    VoicePar[nvoice].PFMVoice=-1;

    VoicePar[nvoice].PFMVolume=90;
    VoicePar[nvoice].PFMVolumeDamp=64;
    VoicePar[nvoice].PFMDetune=8192;
    VoicePar[nvoice].PFMCoarseDetune=0;
    VoicePar[nvoice].PFMDetuneType=0;
    VoicePar[nvoice].PFMFreqEnvelopeEnabled=0;
    VoicePar[nvoice].PFMAmpEnvelopeEnabled=0;
    VoicePar[nvoice].PFMVelocityScaleFunction=64;

    VoicePar[nvoice].OscilSmp->defaults();
    VoicePar[nvoice].FMSmp->defaults();

    VoicePar[nvoice].AmpEnvelope->defaults();
    VoicePar[nvoice].AmpLfo->defaults();

    VoicePar[nvoice].FreqEnvelope->defaults();
    VoicePar[nvoice].FreqLfo->defaults();

    VoicePar[nvoice].VoiceFilter->defaults();
    VoicePar[nvoice].FilterEnvelope->defaults();
    VoicePar[nvoice].FilterLfo->defaults();

    VoicePar[nvoice].FMFreqEnvelope->defaults();
    VoicePar[nvoice].FMAmpEnvelope->defaults();
}

// Init the voice parameters
void ADnoteParameters::EnableVoice (int nvoice)
{
    VoicePar[nvoice].OscilSmp=new OscilGen(fft,GlobalPar.Reson);
    VoicePar[nvoice].FMSmp=new OscilGen(fft,NULL);

    VoicePar[nvoice].AmpEnvelope=new EnvelopeParams(64,1);
    VoicePar[nvoice].AmpEnvelope->ADSRinit_dB(0,100,127,100);
    VoicePar[nvoice].AmpLfo=new LFOParams(90,32,64,0,0,30,0,1);

    VoicePar[nvoice].FreqEnvelope=new EnvelopeParams(0,0);
    VoicePar[nvoice].FreqEnvelope->ASRinit(30,40,64,60);
    VoicePar[nvoice].FreqLfo=new LFOParams(50,40,0,0,0,0,0,0);

    VoicePar[nvoice].VoiceFilter=new FilterParams(2,50,60);
    VoicePar[nvoice].FilterEnvelope=new EnvelopeParams(0,0);
    VoicePar[nvoice].FilterEnvelope->ADSRinit_filter(90,70,40,70,10,40);
    VoicePar[nvoice].FilterLfo=new LFOParams(50,20,64,0,0,0,0,2);

    VoicePar[nvoice].FMFreqEnvelope=new EnvelopeParams(0,0);
    VoicePar[nvoice].FMFreqEnvelope->ASRinit(20,90,40,80);
    VoicePar[nvoice].FMAmpEnvelope=new EnvelopeParams(64,1);
    VoicePar[nvoice].FMAmpEnvelope->ADSRinit(80,90,127,100);
}

// Kill the voice
void ADnoteParameters::KillVoice (int nvoice)
{
    delete (VoicePar[nvoice].OscilSmp);
    delete (VoicePar[nvoice].FMSmp);
    delete (VoicePar[nvoice].AmpEnvelope);
    delete (VoicePar[nvoice].AmpLfo);
    delete (VoicePar[nvoice].FreqEnvelope);
    delete (VoicePar[nvoice].FreqLfo);
    delete (VoicePar[nvoice].VoiceFilter);
    delete (VoicePar[nvoice].FilterEnvelope);
    delete (VoicePar[nvoice].FilterLfo);
    delete (VoicePar[nvoice].FMFreqEnvelope);
    delete (VoicePar[nvoice].FMAmpEnvelope);
}

// Get the Multiplier of the fine detunes of the voices
REALTYPE ADnoteParameters::getBandwidthDetuneMultiplier()
{
    REALTYPE bw = (GlobalPar.PBandwidth - 64.0) / 64.0;
    return pow (2.0, bw * pow (fabs (bw), 0.2) * 5.0);
}

void ADnoteParameters::addToXML (XmlElement* xml)
{
    xml->setAttribute (T("stereo"), GlobalPar.PStereo);

    {
    XmlElement* e = new XmlElement (T("amppar"));
    e->setAttribute (T("vol"), GlobalPar.PVolume);
    e->setAttribute (T("pan"), GlobalPar.PPanning);
    e->setAttribute (T("jx"), GlobalPar.PJoyX);
    e->setAttribute (T("jy"), GlobalPar.PJoyY);
    e->setAttribute (T("velsns"), GlobalPar.PAmpVelocityScaleFunction);
//    e->setAttribute (T("punch_strength"), GlobalPar.PPunchStrength);
//    e->setAttribute (T("punch_time"), GlobalPar.PPunchTime);
//    e->setAttribute (T("punch_stretch"), GlobalPar.PPunchStretch);
//    e->setAttribute (T("punch_velocity_sensing"), GlobalPar.PPunchVelocitySensing);
    e->setAttribute (T("hcrg"), GlobalPar.Hrandgrouping);
        {
        XmlElement* ae = new XmlElement (T("ampenv"));
        GlobalPar.AmpEnvelope->addToXML (ae);
        e->addChildElement (ae);
        }
        {
        XmlElement* ae = new XmlElement (T("amplfo"));
        GlobalPar.AmpLfo->addToXML (ae);
        e->addChildElement (ae);
        }
    xml->addChildElement (e);
    }

    {
    XmlElement* e = new XmlElement (T("freqpar"));
    e->setAttribute (T("detune"), GlobalPar.PDetune);
    e->setAttribute (T("detunetype"), GlobalPar.PDetuneType);
    e->setAttribute (T("coarse"), GlobalPar.PCoarseDetune);
    e->setAttribute (T("bw"), GlobalPar.PBandwidth);
        {
        XmlElement* ae = new XmlElement (T("freqenv"));
        GlobalPar.FreqEnvelope->addToXML (ae);
        e->addChildElement (ae);
        }
        {
        XmlElement* ae = new XmlElement (T("freqlfo"));
        GlobalPar.FreqLfo->addToXML (ae);
        e->addChildElement (ae);
        }
    xml->addChildElement (e);
    }

    {
    XmlElement* e = new XmlElement (T("fltpar"));
    e->setAttribute (T("velsnsamp"), GlobalPar.PFilterVelocityScale);
    e->setAttribute (T("velsns"), GlobalPar.PFilterVelocityScaleFunction);
        {
        XmlElement* ae = new XmlElement (T("flt"));
        GlobalPar.GlobalFilter->addToXML (ae);
        e->addChildElement (ae);
        }
        {
        XmlElement* ae = new XmlElement (T("fltenv"));
        GlobalPar.FilterEnvelope->addToXML (ae);
        e->addChildElement (ae);
        }
        {
        XmlElement* ae = new XmlElement (T("fltlfo"));
        GlobalPar.FilterLfo->addToXML (ae);
        e->addChildElement (ae);
        }
    xml->addChildElement (e);
    }

/*
    {
    XmlElement* e = new XmlElement (T("resonance"));
    GlobalPar.Reson->addToXML (e);
    xml->addChildElement (e);
    }
*/

    for (int nvoice = 0; nvoice < NUM_VOICES; nvoice++)
    {
        XmlElement* e = new XmlElement (T("vce") + String (nvoice));
        addToXMLSection (e, nvoice);
        xml->addChildElement (e);
    }
}

void ADnoteParameters::addToXMLSection (XmlElement* xml, int section)
{
    int nvoice = section;
    if (nvoice >= NUM_VOICES) return;

/*    int oscilused = 0, fmoscilused = 0;
    for (int i = 0; i < NUM_VOICES; i++)
    {
        if (VoicePar[i].Pextoscil == nvoice) oscilused = 1;
        if (VoicePar[i].PextFMoscil == nvoice) fmoscilused = 1;
    }
*/

    xml->setAttribute (T("on"), VoicePar[nvoice].Enabled);
    xml->setAttribute (T("type"), VoicePar[nvoice].Type);
    xml->setAttribute (T("dly"), VoicePar[nvoice].PDelay);
    xml->setAttribute (T("reso"), VoicePar[nvoice].Presonance);
    xml->setAttribute (T("eosc"), VoicePar[nvoice].Pextoscil);
    xml->setAttribute (T("efmos"), VoicePar[nvoice].PextFMoscil);
    xml->setAttribute (T("oscph"), VoicePar[nvoice].Poscilphase);
    xml->setAttribute (T("oscfmph"), VoicePar[nvoice].PFMoscilphase);
    xml->setAttribute (T("flton"), VoicePar[nvoice].PFilterEnabled);
    xml->setAttribute (T("fltby"), VoicePar[nvoice].Pfilterbypass);
    xml->setAttribute (T("fmon"), VoicePar[nvoice].PFMEnabled);

    {
    XmlElement* e = new XmlElement (T("osc"));
    if (VoicePar[nvoice].OscilSmp) VoicePar[nvoice].OscilSmp->addToXML (e);
    xml->addChildElement (e);
    }

    {
    XmlElement* e = new XmlElement (T("amppar"));
    e->setAttribute (T("pan"), VoicePar[nvoice].PPanning);
    e->setAttribute (T("vol"), VoicePar[nvoice].PVolume);
    e->setAttribute (T("volm"), VoicePar[nvoice].PVolumeminus);
    e->setAttribute (T("velsns"), VoicePar[nvoice].PAmpVelocityScaleFunction);

    e->setAttribute (T("ampenvon"), VoicePar[nvoice].PAmpEnvelopeEnabled);
        {
        XmlElement* ae = new XmlElement (T("ampenv"));
        VoicePar[nvoice].AmpEnvelope->addToXML (ae);
        e->addChildElement (ae);
        }
    e->setAttribute (T("amplfoon"), VoicePar[nvoice].PAmpLfoEnabled);
        {
        XmlElement* ae = new XmlElement (T("amplfo"));
        VoicePar[nvoice].AmpLfo->addToXML (ae);
        e->addChildElement (ae);
        }
    xml->addChildElement (e);
    }

    {
    XmlElement* e = new XmlElement (T("freqpar"));
    e->setAttribute (T("fixfreq"), VoicePar[nvoice].Pfixedfreq);
    e->setAttribute (T("fixfreqet"), VoicePar[nvoice].PfixedfreqET);
    e->setAttribute (T("detune"), VoicePar[nvoice].PDetune);
    e->setAttribute (T("coarse"), VoicePar[nvoice].PCoarseDetune);
    e->setAttribute (T("detunetype"), VoicePar[nvoice].PDetuneType);

    e->setAttribute (T("freqenvon"), VoicePar[nvoice].PFreqEnvelopeEnabled);
        {
        XmlElement* ae = new XmlElement (T("freqenv"));
        VoicePar[nvoice].FreqEnvelope->addToXML (ae);
        e->addChildElement (ae);
        }
    e->setAttribute (T("freqlfoon"), VoicePar[nvoice].PFreqLfoEnabled);
        {
        XmlElement* ae = new XmlElement (T("freqlfo"));
        VoicePar[nvoice].FreqLfo->addToXML (ae);
        e->addChildElement (ae);
        }
    xml->addChildElement (e);
    }

    {
    XmlElement* e = new XmlElement (T("fltpar"));
        XmlElement* ef = new XmlElement (T("flt"));
        VoicePar[nvoice].VoiceFilter->addToXML (ef);
        e->addChildElement (ef);

    e->setAttribute (T("fltenvon"), VoicePar[nvoice].PFilterEnvelopeEnabled);
        {
        XmlElement* ae = new XmlElement (T("freqenv"));
        VoicePar[nvoice].FilterEnvelope->addToXML (ae);
        e->addChildElement (ae);
        }
    e->setAttribute (T("fltlfoon"), VoicePar[nvoice].PFilterLfoEnabled);
        {
        XmlElement* ae = new XmlElement (T("fltlfo"));
        VoicePar[nvoice].FilterLfo->addToXML (ae);
        e->addChildElement (ae);
        }
    xml->addChildElement (e);
    }

/*
    {
    XmlElement* e = new XmlElement (T("fm_parameters"));
    e->setAttribute (T("input_voice"), VoicePar[nvoice].PFMVoice);
    e->setAttribute (T("volume"), VoicePar[nvoice].PFMVolume);
    e->setAttribute (T("volume_damp"), VoicePar[nvoice].PFMVolumeDamp);
    e->setAttribute (T("velocity_sensing"), VoicePar[nvoice].PFMVelocityScaleFunction);

    e->setAttribute (T("amp_envelope_enabled"), VoicePar[nvoice].PFMAmpEnvelopeEnabled);
        {
        XmlElement* ae = new XmlElement (T("amplitude_envelope"));
        VoicePar[nvoice].FMAmpEnvelope->addToXML (ae);
        e->addChildElement (ae);
        }
        {
        XmlElement* ae = new XmlElement (T("modulator"));
        ae->setAttribute (T("detune"), VoicePar[nvoice].PFMDetune);
        ae->setAttribute (T("coarse_detune"), VoicePar[nvoice].PFMCoarseDetune);
        ae->setAttribute (T("detune_type"), VoicePar[nvoice].PFMDetuneType);
        ae->setAttribute (T("freq_envelope_enabled"), VoicePar[nvoice].PFMFreqEnvelopeEnabled);
            {
            XmlElement* fe = new XmlElement (T("frequency_envelope"));
            VoicePar[nvoice].FMFreqEnvelope->addToXML (fe);
            ae->addChildElement (fe);
            }
        e->addChildElement (ae);
        }
        {
        XmlElement* ae = new XmlElement (T("oscillator"));
        VoicePar[nvoice].FMSmp->addToXML (ae);
        e->addChildElement (ae);
        }
    xml->addChildElement (e);
    }
*/
}


void ADnoteParameters::updateFromXML (XmlElement *xml)
{
    GlobalPar.PStereo = xml->getIntAttribute (T("stereo"), GlobalPar.PStereo);

    {
    XmlElement* e = xml->getChildByName (T("amppar"));
    if (e)
    {
        GlobalPar.PVolume = xml->getIntAttribute (T("vol"), GlobalPar.PVolume);
        GlobalPar.PPanning = xml->getIntAttribute (T("pan"), GlobalPar.PPanning);
        GlobalPar.PJoyX = xml->getIntAttribute (T("jx"), GlobalPar.PJoyX);
        GlobalPar.PJoyY = xml->getIntAttribute (T("jy"), GlobalPar.PJoyY);
        GlobalPar.PAmpVelocityScaleFunction = xml->getIntAttribute (T("velsns"), GlobalPar.PAmpVelocityScaleFunction);
//        GlobalPar.PPunchStrength = xml->getIntAttribute (T("punch_strength"), GlobalPar.PPunchStrength);
//        GlobalPar.PPunchTime = xml->getIntAttribute (T("punch_time"), GlobalPar.PPunchTime);
//        GlobalPar.PPunchStretch = xml->getIntAttribute (T("punch_stretch"), GlobalPar.PPunchStretch);
//        GlobalPar.PPunchVelocitySensing = xml->getIntAttribute (T("punch_velocity_sensing"), GlobalPar.PPunchVelocitySensing);
        GlobalPar.Hrandgrouping = xml->getIntAttribute (T("hcrg"), GlobalPar.Hrandgrouping);

        {
        XmlElement* ae = e->getChildByName (T("ampenv"));
        if (ae) GlobalPar.AmpEnvelope->updateFromXML (ae);
        }

        {
        XmlElement* ae = e->getChildByName (T("amplfo"));
        if (ae) GlobalPar.AmpLfo->updateFromXML (ae);
        }
    }
    }

    {
    XmlElement* e = xml->getChildByName (T("freqpar"));
    if (e)
    {
        GlobalPar.PDetune = xml->getIntAttribute (T("detune"), GlobalPar.PDetune); // 0 16383
        GlobalPar.PCoarseDetune = xml->getIntAttribute (T("coarse"), GlobalPar.PCoarseDetune); // 0 16383
        GlobalPar.PDetuneType = xml->getIntAttribute (T("detunetype"), GlobalPar.PDetuneType);
        GlobalPar.PBandwidth = xml->getIntAttribute (T("bw"), GlobalPar.PBandwidth);

        {
        XmlElement* ae = e->getChildByName (T("freqenv"));
        if (ae) GlobalPar.FreqEnvelope->updateFromXML (ae);
        }

        {
        XmlElement* ae = e->getChildByName (T("freqlfo"));
        if (ae) GlobalPar.FreqLfo->updateFromXML (ae);
        }
    }
    }

    {
    XmlElement* e = xml->getChildByName (T("fltpar"));
    if (e)
    {
        GlobalPar.PFilterVelocityScale = xml->getIntAttribute (T("velsnsamp"), GlobalPar.PFilterVelocityScale);
        GlobalPar.PFilterVelocityScaleFunction = xml->getIntAttribute (T("velsns"), GlobalPar.PFilterVelocityScaleFunction);

        {
        XmlElement* ae = e->getChildByName (T("flt"));
        if (ae) GlobalPar.GlobalFilter->updateFromXML (ae);
        }

        {
        XmlElement* ae = e->getChildByName (T("fltenv"));
        if (ae) GlobalPar.FilterEnvelope->updateFromXML (ae);
        }

        {
        XmlElement* ae = e->getChildByName (T("fltlfo"));
        if (ae) GlobalPar.FilterLfo->updateFromXML (ae);
        }
    }
    }

/*
    {
    XmlElement* e = xml->getChildByName (T("resonance"));
    if (e) GlobalPar.Reson->updateFromXML (e);
    }
*/

    for (int nvoice = 0; nvoice < NUM_VOICES; nvoice++)
    {
        XmlElement* e = xml->getChildByName (T("vce") + String (nvoice));
        if (e) updateFromXMLSection (e, nvoice);
    }
}


void ADnoteParameters::updateFromXMLSection (XmlElement *xml, int section)
{
    int nvoice = section;
    if (nvoice >= NUM_VOICES) return;

    VoicePar[nvoice].Enabled = xml->getIntAttribute (T("on"), VoicePar[nvoice].Enabled); // bool
    VoicePar[nvoice].Type = xml->getIntAttribute (T("type"), VoicePar[nvoice].Type);
    VoicePar[nvoice].PDelay = xml->getIntAttribute (T("dly"), VoicePar[nvoice].PDelay);
    VoicePar[nvoice].Presonance = xml->getIntAttribute (T("reso"), VoicePar[nvoice].Presonance); // bool
    VoicePar[nvoice].Pextoscil = xml->getIntAttribute (T("eosc"), -1); // nvoice - 1); // ??
    VoicePar[nvoice].PextFMoscil = xml->getIntAttribute (T("efmosc"), -1); // nvoice - 1); // ??
    VoicePar[nvoice].Poscilphase = xml->getIntAttribute (T("oscph"), VoicePar[nvoice].Poscilphase);
    VoicePar[nvoice].PFMoscilphase = xml->getIntAttribute (T("oscfmph"), VoicePar[nvoice].PFMoscilphase);
    VoicePar[nvoice].PFilterEnabled = xml->getIntAttribute (T("flton"), VoicePar[nvoice].PFilterEnabled);
    VoicePar[nvoice].Pfilterbypass = xml->getIntAttribute (T("fltby"), VoicePar[nvoice].Pfilterbypass);
    VoicePar[nvoice].PFMEnabled = xml->getIntAttribute (T("fmon"), VoicePar[nvoice].PFMEnabled);

    {
    XmlElement* e = xml->getChildByName (T("osc"));
    if (e) VoicePar[nvoice].OscilSmp->updateFromXML (e);
    }

    {
    XmlElement* e = xml->getChildByName (T("amppar"));
    if (e)
    {
        VoicePar[nvoice].PPanning = e->getIntAttribute (T("pan"), VoicePar[nvoice].PPanning);
        VoicePar[nvoice].PVolume = e->getIntAttribute (T("vol"), VoicePar[nvoice].PVolume);
        VoicePar[nvoice].PVolumeminus = e->getIntAttribute (T("volm"), VoicePar[nvoice].PVolumeminus);
        VoicePar[nvoice].PAmpVelocityScaleFunction = e->getIntAttribute (T("velsns"), VoicePar[nvoice].PAmpVelocityScaleFunction);

        VoicePar[nvoice].PAmpEnvelopeEnabled = e->getIntAttribute (T("ampenvon"), VoicePar[nvoice].PAmpEnvelopeEnabled);
        {
        XmlElement* ae = e->getChildByName (T("ampenv"));
        if (ae) VoicePar[nvoice].AmpEnvelope->updateFromXML (ae);
        }

        VoicePar[nvoice].PAmpLfoEnabled = e->getIntAttribute (T("amplfoon"), VoicePar[nvoice].PAmpLfoEnabled);
        {
        XmlElement* ae = e->getChildByName (T("amplfo"));
        if (ae) VoicePar[nvoice].AmpLfo->updateFromXML (ae);
        }
    }
    }

    {
    XmlElement* e = xml->getChildByName (T("freqpar"));
    if (e)
    {
        VoicePar[nvoice].Pfixedfreq = e->getIntAttribute (T("fixfreq"), VoicePar[nvoice].Pfixedfreq);
        VoicePar[nvoice].PfixedfreqET = e->getIntAttribute (T("fixfreqet"), VoicePar[nvoice].PfixedfreqET);
        VoicePar[nvoice].PDetune = e->getIntAttribute (T("detune"), VoicePar[nvoice].PDetune); // 0 16383
        VoicePar[nvoice].PCoarseDetune = e->getIntAttribute (T("coarse"), VoicePar[nvoice].PCoarseDetune); // 0 16383
        VoicePar[nvoice].PDetuneType = e->getIntAttribute (T("detunetype"), VoicePar[nvoice].PDetuneType);

        VoicePar[nvoice].PFreqEnvelopeEnabled = e->getIntAttribute (T("freqenvon"), VoicePar[nvoice].PFreqEnvelopeEnabled);
        {
        XmlElement* ae = e->getChildByName (T("freqenv"));
        if (ae) VoicePar[nvoice].FreqEnvelope->updateFromXML (ae);
        }

        VoicePar[nvoice].PFreqLfoEnabled = e->getIntAttribute (T("freqlfoon"), VoicePar[nvoice].PFreqLfoEnabled);
        {
        XmlElement* ae = e->getChildByName (T("freqlfo"));
        if (ae) VoicePar[nvoice].FreqLfo->updateFromXML (ae);
        }
    }
    }

    {
    XmlElement* e = xml->getChildByName (T("fltpar"));
    if (e)
    {
        {
        XmlElement* ef = e->getChildByName (T("flt"));
        if (ef) VoicePar[nvoice].VoiceFilter->updateFromXML (ef);
        }

        VoicePar[nvoice].PFilterEnvelopeEnabled = e->getIntAttribute (T("fltenvon"), VoicePar[nvoice].PFilterEnvelopeEnabled);
        {
        XmlElement* ef = e->getChildByName (T("fltenv"));
        if (ef) VoicePar[nvoice].FilterEnvelope->updateFromXML (ef);
        }

        VoicePar[nvoice].PFilterLfoEnabled = e->getIntAttribute (T("fltlfoon"), VoicePar[nvoice].PFilterLfoEnabled);
        {
        XmlElement* ef = e->getChildByName (T("fltenv"));
        if (ef) VoicePar[nvoice].FilterLfo->updateFromXML (ef);
        }
    }
    }

/*
    {
    XmlElement* e = xml->getChildByName (T("fm_parameters"));
    if (e)
    {
        VoicePar[nvoice].PFMVoice = xml->getIntAttribute (T("input_voice"), VoicePar[nvoice].PFMVoice); // -1 , nvoice-1
        VoicePar[nvoice].PFMVolume = xml->getIntAttribute (T("volume"), VoicePar[nvoice].PFMVolume);
        VoicePar[nvoice].PFMVolumeDamp = xml->getIntAttribute (T("volume_damp"), VoicePar[nvoice].PFMVolumeDamp);
        VoicePar[nvoice].PFMVelocityScaleFunction = xml->getIntAttribute (T("velocity_sensing"), VoicePar[nvoice].PFMVelocityScaleFunction);

        VoicePar[nvoice].PFMAmpEnvelopeEnabled = xml->getIntAttribute (T("amp_envelope_enabled"), VoicePar[nvoice].PFMAmpEnvelopeEnabled);
        {
        XmlElement* ef = xml->getChildByName (T("amplitude_envelope"));
        if (ef) VoicePar[nvoice].FMAmpEnvelope->updateFromXML (ef);
        }

        {
        XmlElement* ef = xml->getChildByName (T("modulator"));
        if (ef)
        {
            VoicePar[nvoice].PFMDetune = xml->getIntAttribute (T("detune"), VoicePar[nvoice].PFMDetune); // 0,16383
            VoicePar[nvoice].PFMCoarseDetune = xml->getIntAttribute (T("coarse_detune"), VoicePar[nvoice].PFMCoarseDetune); // 0,16383
            VoicePar[nvoice].PFMDetuneType = xml->getIntAttribute (T("detune_type"), VoicePar[nvoice].PFMDetuneType);

            VoicePar[nvoice].PFMFreqEnvelopeEnabled = xml->getIntAttribute (T("freq_envelope_enabled"), VoicePar[nvoice].PFMFreqEnvelopeEnabled);
            {
            XmlElement* ef = xml->getChildByName (T("frequency_envelope"));
            if (ef) VoicePar[nvoice].FMFreqEnvelope->updateFromXML (ef);
            }

            {
            XmlElement* ef = xml->getChildByName (T("oscillator"));
            if (ef) VoicePar[nvoice].FMSmp->updateFromXML (ef);
            }
        }
        }
    }
    }
*/
}


