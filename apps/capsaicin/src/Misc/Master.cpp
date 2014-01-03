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

#include "Master.h"

#include <iostream>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

//==============================================================================
Master::Master()
{
    fft = new FFTWrapper (OSCIL_SIZE);

    tmpmixl = new REALTYPE[SOUND_BUFFER_SIZE];
    tmpmixr = new REALTYPE[SOUND_BUFFER_SIZE];
    audiooutl = new REALTYPE[SOUND_BUFFER_SIZE];
    audiooutr = new REALTYPE[SOUND_BUFFER_SIZE];

    shutup = 0;
    ksoundbuffersample = -1; // this is only time when this is -1; this means that the GetAudioOutSamples was never called

#if defined (RESAMPLE_METHOD_INTERNAL)
    ksoundbuffersamplelow = 0.0;
    oldsamplel = 0.0;
    oldsampler = 0.0;
#elif defined (RESAMPLE_METHOD_LIBSAMPLERATE)
    int error;
    src_state_l = src_new (SRC_SINC_FASTEST, 1, &error);
    src_state_r = src_new (SRC_SINC_FASTEST, 1, &error);
#endif

    for (int npart = 0; npart < NUM_MIDI_PARTS; npart++)
    {
        vuoutpeakpart[npart] = 1e-9;
        fakepeakpart[npart] = 0;
    }

    for (int i = 0; i < SOUND_BUFFER_SIZE; i++)
    {
        audiooutl[i] = 0.0;
        audiooutr[i] = 0.0;
    }

    // Parts init
    for (int npart = 0; npart < NUM_MIDI_PARTS; npart++)
        part[npart] = new Part (&microtonal, fft, &mutex);

    // Insertion Effects init
    for (int nefx = 0; nefx < NUM_INS_EFX; nefx++)
        insefx[nefx] = new EffectMgr (1, &mutex);

    // System Effects init
    for (int nefx = 0; nefx < NUM_SYS_EFX; nefx++)
        sysefx[nefx] = new EffectMgr (0, &mutex);

    defaults();
}

Master::~Master()
{
    for (int i = 0; i < NUM_MIDI_PARTS; i++) delete part[i];
    for (int i = 0; i < NUM_INS_EFX; i++) delete insefx[i];
    for (int i = 0; i < NUM_SYS_EFX; i++) delete sysefx[i];

    delete [] audiooutl;
    delete [] audiooutr;
    delete [] tmpmixl;
    delete [] tmpmixr;
    delete (fft);

#if defined (RESAMPLE_METHOD_INTERNAL)
#elif defined (RESAMPLE_METHOD_LIBSAMPLERATE)
    src_state_l = src_delete (src_state_l);
    src_state_r = src_delete (src_state_r);
#endif
}

//==============================================================================
void Master::defaults()
{
    volume = 1.0;
    setPvolume (80);
    setPkeyshift (64);
    Psolopart = 0; // no solo

    // Parts init
    for (int npart = 0; npart < NUM_MIDI_PARTS; npart++)
    {
        part[npart]->defaults();
        part[npart]->Prcvchn = npart % NUM_MIDI_CHANNELS;
    }
    partonoff (0, 1); // enable the first

    // Insert effects init
    for (int nefx = 0; nefx < NUM_INS_EFX; nefx++)
    {
        insefx[nefx]->defaults();
        Pinsparts[nefx] = -1;
    }

    // System effects init
    for (int nefx = 0; nefx < NUM_SYS_EFX; nefx++)
    {
        sysefx[nefx]->defaults();
        for (int npart = 0; npart < NUM_MIDI_PARTS; npart++)
        {
            if (nefx == 0) setPsysefxvol (npart, nefx, 64);
            else           setPsysefxvol (npart, nefx, 0);
        }

        for (int nefxto = 0; nefxto < NUM_SYS_EFX; nefxto++)
            setPsysefxsend (nefx, nefxto, 0);
    }
//    sysefx[0]->changeEffect (9); // Limiter ?
//    sysefx[0]->changeEffect (1); // GReverb ?
//    sysefx[0]->changeEffect (10); // GReverb ?

    ShutUp ();
}

 //==============================================================================
void Master::NoteOn (uint8 chan, uint8 note, uint8 velocity)
{
    if (velocity != 0)
    {
        for (int npart = 0; npart < NUM_MIDI_PARTS; npart++)
        {
            if (chan == part[npart]->Prcvchn)
            {
                fakepeakpart[npart] = velocity * 2;
                if (part[npart]->Penabled != 0)
                    part[npart]->NoteOn (note, velocity, keyshift);
            }
        }
    }
    else
    {
        NoteOff (chan, note);
    }
}

//==============================================================================
void Master::NoteOff (uint8 chan, uint8 note)
{
    for (int npart = 0; npart < NUM_MIDI_PARTS; npart++)
    {
        if ((chan == part[npart]->Prcvchn) && (part[npart]->Penabled != 0))
            part[npart]->NoteOff (note);
    }
}

//==============================================================================
void Master::SetController (uint8 chan, uint type, int par)
{
/*
    if ((type == C_dataentryhi)
        || (type == C_dataentrylo)
        || (type == C_nrpnhi)
        || (type == C_nrpnlo))
    {
        // Process RPN and NRPN by the Master (ignore the chan)
        ctl.setparameternumber (type, par);

        int parhi = -1, parlo = -1,valhi = -1, vallo = -1;
        if (ctl.getnrpn (&parhi, &parlo, &valhi, &vallo) == 0)
        {
            // this is NRPN
            // fprintf(stderr,"rcv. NRPN: %d %d %d %d\n",parhi,parlo,valhi,vallo);
            switch (parhi)
            {
            case 0x04: // System Effects
                if (parlo < NUM_SYS_EFX)
                    sysefx[parlo]->seteffectpar_nolock (valhi, vallo);
                break;
            case 0x08: // Insertion Effects
                if (parlo < NUM_INS_EFX)
                    insefx[parlo]->seteffectpar_nolock(valhi,vallo);
                break;
            }
        }
    }
    else
*/
    {
        //other controllers
        for (int npart = 0; npart < NUM_MIDI_PARTS; npart++)
        {
            //Send the controller to all part assigned to the channel
            if ((chan == part[npart]->Prcvchn) && (part[npart]->Penabled != 0))
                part[npart]->SetController (type, par);
        }
    }
}

//==============================================================================
void Master::ShutUp()
{
    for (int npart = 0; npart < NUM_MIDI_PARTS; npart++)
    {
        part[npart]->cleanup();
        fakepeakpart[npart] = 0;
    }

    for (int nefx = 0; nefx < NUM_INS_EFX; nefx++) insefx[nefx]->clean();
    for (int nefx = 0; nefx < NUM_SYS_EFX; nefx++) sysefx[nefx]->clean();

    vuresetpeaks();
    shutup = 0;
}

//==============================================================================
void Master::partonoff (int npart, int what)
{
    if (npart >= NUM_MIDI_PARTS) return;
    if (what == 0)
    {
        //disable part
        fakepeakpart[npart] = 0;
        part[npart]->Penabled = 0;
        part[npart]->cleanup();
        for (int nefx = 0; nefx < NUM_INS_EFX; nefx++)
            if (Pinsparts[nefx] == npart) insefx[nefx]->clean();
    }
    else
    {
        //enabled
        part[npart]->Penabled = 1;
        fakepeakpart[npart] = 0;
    }
}

//==============================================================================
void Master::vuresetpeaks()
{
    vuoutpeakl = 1e-9;
    vuoutpeakr = 1e-9;
    vumaxoutpeakl = 1e-9;
    vumaxoutpeakr = 1e-9;
    vuclipped = 0;
}

//==============================================================================
void Master::PartAudioOut (Part* p)
{
    p->ComputePartSmps();

    REALTYPE newvol_l = p->volume;
    REALTYPE newvol_r = p->volume;
    REALTYPE oldvol_l = p->oldvolumel;
    REALTYPE oldvol_r = p->oldvolumer;
    REALTYPE pan = p->panning;
    if (pan < 0.5) newvol_l *= pan * 2.0;
    else           newvol_r *= (1.0 - pan) * 2.0;

    if (ABOVE_AMPLITUDE_THRESHOLD (oldvol_l, newvol_l)
        || ABOVE_AMPLITUDE_THRESHOLD (oldvol_r, newvol_r))
    {
        // the volume or the panning has changed and needs interpolation
        for (int i = 0; i < SOUND_BUFFER_SIZE; i++)
        {
            REALTYPE vol_l = INTERPOLATE_AMPLITUDE (oldvol_l, newvol_l, i, SOUND_BUFFER_SIZE);
            REALTYPE vol_r = INTERPOLATE_AMPLITUDE (oldvol_r, newvol_r, i, SOUND_BUFFER_SIZE);
            p->partoutl[i] *= vol_l;
            p->partoutr[i] *= vol_r;
        }
        p->oldvolumel = newvol_l;
        p->oldvolumer = newvol_r;
    }
    else
    {
        for (int i = 0; i < SOUND_BUFFER_SIZE; i++)
        {
            // the volume did not changed
            p->partoutl[i] *= newvol_l;
            p->partoutr[i] *= newvol_r;
        }
    }
}

//==============================================================================
void Master::MasterAudioOut (REALTYPE *outl, REALTYPE *outr)
{
    int i, npart, nefx;

    // Clean up the output samples
    zeromem (outl, sizeof (float) * SOUND_BUFFER_SIZE);
    zeromem (outr, sizeof (float) * SOUND_BUFFER_SIZE);

    // Compute part samples and store them part[npart]->partoutl,partoutr
    if (Psolopart > 0)
    {
        PartAudioOut (part [Psolopart - 1]);
    }
    else
    {
        for (npart = 0; npart < NUM_MIDI_PARTS; npart++)
        {
            Part* p = part [npart];
            if (p->Penabled != 0)
                PartAudioOut (part [npart]);
        }
    }

/*
    // Insertion effects
    for (nefx=0;nefx<NUM_INS_EFX;nefx++){
        if (Pinsparts[nefx]>=0) {
            int efxpart=Pinsparts[nefx];
            if (part[efxpart]->Penabled!=0)
            insefx[nefx]->out(part[efxpart]->partoutl,part[efxpart]->partoutr);
        };
    };
*/

    // System effects
    for (nefx = 0; nefx < NUM_SYS_EFX; nefx++)
    {
        if (sysefx[nefx]->getEffect() == 0) continue; //the effect is disabled

        // Clean up the samples used by the system effects
        zeromem (tmpmixl, sizeof (float) * SOUND_BUFFER_SIZE);
        zeromem (tmpmixr, sizeof (float) * SOUND_BUFFER_SIZE);

        // Mix the channels according to the part settings about System Effect
        if (Psolopart > 0)
        {
            // We are in solo mode !
            int npart = Psolopart - 1;

            // the output volume of each part to system effect
            REALTYPE vol = sysefxvol[nefx][npart];
            for (i = 0; i < SOUND_BUFFER_SIZE; i++)
            {
                tmpmixl[i] += part[npart]->partoutl[i] * vol;
                tmpmixr[i] += part[npart]->partoutr[i] * vol;
            }
        }
        else
        {
            // We are in normal (solo-disabled) mode !
            for (npart = 0; npart < NUM_MIDI_PARTS; npart++)
            {
                // skip if the part has no output to effect
                if (Psysefxvol[nefx][npart] == 0) continue;

                // skip if the part is disabled
                if (part[npart]->Penabled == 0) continue;

                // the output volume of each part to system effect
                REALTYPE vol = sysefxvol[nefx][npart];
                for (i = 0; i < SOUND_BUFFER_SIZE; i++)
                {
                    tmpmixl[i] += part[npart]->partoutl[i] * vol;
                    tmpmixr[i] += part[npart]->partoutr[i] * vol;
                }
            }
        }

        // system effect send to next ones
        for (int nefxfrom = 0; nefxfrom < nefx; nefxfrom++)
        {
            if (Psysefxsend[nefxfrom][nefx] != 0)
            {
                REALTYPE v = sysefxsend[nefxfrom][nefx];
                for (i = 0; i < SOUND_BUFFER_SIZE; i++)
                {
                    tmpmixl[i] += sysefx[nefxfrom]->efxoutl[i] * v;
                    tmpmixr[i] += sysefx[nefxfrom]->efxoutr[i] * v;
                }
            }
        }

        sysefx[nefx]->out (tmpmixl, tmpmixr, SOUND_BUFFER_SIZE);

        // Add the System Effect to sound output
        REALTYPE outvol = sysefx[nefx]->sysefxgetvolume();
        for (i = 0; i < SOUND_BUFFER_SIZE; i++)
        {
            outl[i] += tmpmixl[i] * outvol;
            outr[i] += tmpmixr[i] * outvol;
        }
    }

    // Mix all parts
    if (Psolopart > 0 )
    {
        // Solo mode
        int npart = Psolopart - 1;
        for (i = 0; i < SOUND_BUFFER_SIZE; i++)
        {
            outl[i] += part[npart]->partoutl[i];
            outr[i] += part[npart]->partoutr[i];
        }
    }
    else
    {
        // All parts playing
        for (npart = 0; npart < NUM_MIDI_PARTS; npart++)
        {
            if (part[npart]->Penabled != 0)
                for (i = 0; i < SOUND_BUFFER_SIZE; i++)
                {
                    outl[i] += part[npart]->partoutl[i];
                    outr[i] += part[npart]->partoutr[i];
                }
        }
    }

/*
    //Insertion effects for Master Out
    for (nefx=0;nefx<NUM_INS_EFX;nefx++){
        if (Pinsparts[nefx] == -2)
            insefx[nefx]->out(outl,outr);
    };
*/

    // Master Volume & Peak computation (for vumeters)
    REALTYPE foutl, foutr;
    REALTYPE newvol = volume;
    REALTYPE oldvol = oldvolume;
    vuoutpeakl = 1e-12;
    vuoutpeakr = 1e-12;
    if (ABOVE_AMPLITUDE_THRESHOLD (oldvol, newvol))
    {
        // Interpolate
        for (i = 0; i < SOUND_BUFFER_SIZE; i++)
        {
            REALTYPE vol = INTERPOLATE_AMPLITUDE (oldvol, newvol, i, SOUND_BUFFER_SIZE);
            outl[i] *= vol;
            outr[i] *= vol;

            foutl = fabs (outl[i]);
            foutr = fabs (outr[i]);
            if (foutl > vuoutpeakl) vuoutpeakl = foutl;
            if (foutr > vuoutpeakr) vuoutpeakr = foutr;
        }
        oldvolume = volume;
    }
    else
    {
        // Do not interpolate
        for (i = 0; i < SOUND_BUFFER_SIZE; i++)
        {
            outl[i] *= volume;
            outr[i] *= volume;

            foutl = fabs (outl[i]);
            foutr = fabs (outr[i]);
            if (foutl > vuoutpeakl) vuoutpeakl = foutl;
            if (foutr > vuoutpeakr) vuoutpeakr = foutr;
        }
    }
    // @XXX - these lines probably are unneeded
    // if ((vuoutpeakl > 1.0) || (vuoutpeakr > 1.0)) vuclipped = 1;
    // if (vumaxoutpeakl < vuoutpeakl) vumaxoutpeakl = vuoutpeakl;
    // if (vumaxoutpeakr < vuoutpeakr) vumaxoutpeakr = vuoutpeakr;

/*
    // RMS Peak computation (for vumeters)
    vurmspeakl = 1e-12;
    vurmspeakr = 1e-12;
    for (i = 0; i < SOUND_BUFFER_SIZE; i++)
    {
        vurmspeakl += outl[i] * outl[i];
        vurmspeakr += outr[i] * outr[i];
    }
    // vurmspeakl = sqrt (vurmspeakl / SOUND_BUFFER_SIZE); // @XXX - do this on gui instead !!
    // vurmspeakr = sqrt (vurmspeakr / SOUND_BUFFER_SIZE); // @XXX - do this on gui instead !!
*/

    // Part Peak computation (for Part vumeters or fake part vumeters)
    for (npart = 0; npart < NUM_MIDI_PARTS; npart++)
    {
        vuoutpeakpart[npart] = 1.0e-12;
        if (part[npart]->Penabled != 0)
        {
            REALTYPE *left = part[npart]->partoutl,
                     *right = part[npart]->partoutr;

            for (i = 0; i < SOUND_BUFFER_SIZE; i++)
            {
                REALTYPE tmp = fabs (left[i] + right[i]);
                if (tmp > vuoutpeakpart[npart]) vuoutpeakpart[npart] = tmp;
            }
            vuoutpeakpart[npart] *= volume;
        }
        else
        {
            if (fakepeakpart[npart] > 1) fakepeakpart[npart]--;
        }
    }

    // Shutup if it is asked (with fade-out)
    if (shutup != 0)
    {
        REALTYPE bufSizeDivider = 1.0f / (REALTYPE) SOUND_BUFFER_SIZE;
        for (i = 0; i < SOUND_BUFFER_SIZE; i++)
        {
            REALTYPE tmp = (SOUND_BUFFER_SIZE - i) * bufSizeDivider;
            outl[i] *= tmp;
            outr[i] *= tmp;
        }
        ShutUp();
    }

    // update the LFO's time
    LFOParams::time++;
}

//==============================================================================
void Master::GetAudioOutSamples (int nsamples,
                                 int samplerate,
                                 REALTYPE *outl,
                                 REALTYPE *outr)
{
    if (ksoundbuffersample == -1)
    {
        //first time
        MasterAudioOut (&audiooutl[0], &audiooutr[0]);
        ksoundbuffersample = 0;
    }

    if (samplerate == SAMPLE_RATE)
    {
        // No resample
        int ksample = 0;
        while (ksample < nsamples)
        {
            outl[ksample] = audiooutl[ksoundbuffersample];
            outr[ksample] = audiooutr[ksoundbuffersample];

            ksample++;
            ksoundbuffersample++;
            if (ksoundbuffersample >= SOUND_BUFFER_SIZE)
            {
                MasterAudioOut (&audiooutl[0], &audiooutr[0]);
                ksoundbuffersample = 0;
            }
        }
    }
    else
    {
        // Resample
#if defined (RESAMPLE_METHOD_INTERNAL)
        int ksample = 0;
        REALTYPE srinc = SAMPLE_RATE / (REALTYPE) samplerate;
        while (ksample < nsamples)
        {
            if (ksoundbuffersample != 0)
            {
                outl[ksample] = audiooutl[ksoundbuffersample] * ksoundbuffersamplelow
                                + audiooutl[ksoundbuffersample-1] * (1.0 - ksoundbuffersamplelow);
                outr[ksample] = audiooutr[ksoundbuffersample] * ksoundbuffersamplelow
                                + audiooutr[ksoundbuffersample-1] * (1.0 - ksoundbuffersamplelow);
            }
            else
            {
                outl[ksample] = audiooutl[ksoundbuffersample] * ksoundbuffersamplelow
                                + oldsamplel * (1.0 - ksoundbuffersamplelow);
                outr[ksample] = audiooutr[ksoundbuffersample] * ksoundbuffersamplelow
                                + oldsampler * (1.0 - ksoundbuffersamplelow);
            }

            ksample++;

            ksoundbuffersamplelow += srinc;
            if (ksoundbuffersamplelow >= 1.0)
            {
                ksoundbuffersample += (int) floor (ksoundbuffersamplelow);
                ksoundbuffersamplelow = ksoundbuffersamplelow - floor (ksoundbuffersamplelow);
            }

            if (ksoundbuffersample >= SOUND_BUFFER_SIZE)
            {
                oldsamplel = audiooutl[SOUND_BUFFER_SIZE-1];
                oldsampler = audiooutr[SOUND_BUFFER_SIZE-1];
                MasterAudioOut (&audiooutl[0], &audiooutr[0]);
                ksoundbuffersample = 0;
            }
        }
#elif defined (RESAMPLE_METHOD_LIBSAMPLERATE)
        int ksample = 0;
        REALTYPE sr_inc = (1.0f * samplerate) / (REALTYPE) SAMPLE_RATE;

        SRC_DATA dataL;
        dataL.end_of_input = 0;
        dataL.src_ratio = sr_inc;

        SRC_DATA dataR;
        dataR.end_of_input = 0;
        dataR.src_ratio = sr_inc;

        while (ksample < nsamples)
        {
            if (ksoundbuffersample >= SOUND_BUFFER_SIZE)
            {
                MasterAudioOut (&audiooutl[0], &audiooutr[0]);
                ksoundbuffersample = 0;
            }

            // process left
            dataL.data_in = &audiooutl[ksoundbuffersample];
            dataL.input_frames = SOUND_BUFFER_SIZE - ksoundbuffersample;
            dataL.data_out = &outl [ksample];
            dataL.output_frames = nsamples - ksample;
            src_process (src_state_l, &dataL);

            // process right
            dataR.data_in = &audiooutr[ksoundbuffersample];
            dataR.input_frames = SOUND_BUFFER_SIZE - ksoundbuffersample;
            dataR.data_out = &outr [ksample];
            dataR.output_frames = nsamples - ksample;
            src_process (src_state_r, &dataR);

            // update frames
            ksoundbuffersample += dataR.input_frames_used;
            ksample += dataR.output_frames_gen;
        }
#endif
    }
}

//==============================================================================
void Master::setPvolume (char Pvolume_)
{
    Pvolume = Pvolume_;
    volume = dB2rap ((Pvolume - 96.0) / 96.0 * 40.0);
}

void Master::setPkeyshift (char Pkeyshift_)
{
    Pkeyshift = Pkeyshift_;
    keyshift = (int) Pkeyshift - 64;
}

void Master::setPsysefxvol (int Ppart, int Pefx, char Pvol)
{
    Psysefxvol[Pefx][Ppart] = Pvol;
    sysefxvol[Pefx][Ppart] = pow (0.1, (1.0 - Pvol / 96.0) * 2.0);
}

void Master::setPsysefxsend (int Pefxfrom, int Pefxto, char Pvol)
{
    Psysefxsend[Pefxfrom][Pefxto] = Pvol;
    sysefxsend[Pefxfrom][Pefxto] = pow (0.1, (1.0 - Pvol / 96.0) * 2.0);
}

//==============================================================================
bool Master::loadXML (File xmlToLoad)
{
    XmlDocument xmlDoc (xmlToLoad);
    XmlElement* xml = xmlDoc.getDocumentElement();

    if (xml == 0 || ! xml->hasTagName (T("main")))
    {
        String errString = xmlDoc.getLastParseError();
        std::cout << (const char*) errString << std::endl;

        return false;
    }
    else
    {
        mutex.enter ();
        updateFromXML (xml);
        mutex.exit ();

        delete xml;

        return true;
    }
}

bool Master::saveXML (File xmlToSave)
{
    XmlElement xml ("main");

    mutex.enter ();
    addToXML (&xml);
    mutex.exit ();

    return xmlToSave.replaceWithText (xml.createDocument (String::empty));
}

//==============================================================================
void Master::addToXML (XmlElement* xml)
{
    xml->setAttribute (T("vol"), Pvolume);
    xml->setAttribute (T("shf"), Pkeyshift);
    xml->setAttribute (T("solo"), Psolopart);

    for (int npart = 0; npart < NUM_MIDI_PARTS; npart++)
    {
        XmlElement* e = new XmlElement (T("part") + String (npart));
        part[npart]->addToXML (e);
        xml->addChildElement (e);
    }

/*

    xml->beginbranch("SYSTEM_EFFECTS");
    for (int nefx=0;nefx<NUM_SYS_EFX;nefx++){
        xml->beginbranch("SYSTEM_EFFECT",nefx);
        xml->beginbranch("EFFECT");
            sysefx[nefx]->add2XML(xml);
        xml->endbranch();

        for (int pefx=0;pefx<NUM_MIDI_PARTS;pefx++){
            xml->beginbranch("VOLUME",pefx);
            xml->addpar("vol",Psysefxvol[nefx][pefx]);
            xml->endbranch();
        };

        for (int tonefx=nefx+1;tonefx<NUM_SYS_EFX;tonefx++){
            xml->beginbranch("SENDTO",tonefx);
            xml->addpar("send_vol",Psysefxsend[nefx][tonefx]);
            xml->endbranch();
        };
        xml->endbranch();
    };
    xml->endbranch();

    xml->beginbranch("INSERTION_EFFECTS");
    for (int nefx=0;nefx<NUM_INS_EFX;nefx++){
        xml->beginbranch("INSERTION_EFFECT",nefx);
        xml->addpar("part",Pinsparts[nefx]);

        xml->beginbranch("EFFECT");
            insefx[nefx]->add2XML(xml);
        xml->endbranch();
        xml->endbranch();
    };

    xml->endbranch();
*/
}

void Master::updateFromXML (XmlElement* xml)
{
    setPvolume (xml->getIntAttribute (T("vol"), Pvolume));
    setPkeyshift (xml->getIntAttribute (T("shf"), Pkeyshift));
    Psolopart = xml->getIntAttribute (T("solo"), Psolopart);

    for (int npart = 0; npart < NUM_MIDI_PARTS; npart++)
    {
        XmlElement* e = xml->getChildByName (T("part") + String (npart));
        if (e) part [npart]->updateFromXML (e);
    }

/*
    sysefx[0]->changeeffect(0);
    if (xml->enterbranch("SYSTEM_EFFECTS")){
    for (int nefx=0;nefx<NUM_SYS_EFX;nefx++){
        if (xml->enterbranch("SYSTEM_EFFECT",nefx)==0) continue;
        if (xml->enterbranch("EFFECT")){
            sysefx[nefx]->getfromXML(xml);
            xml->exitbranch();
        };

        for (int partefx=0;partefx<NUM_MIDI_PARTS;partefx++){
            if (xml->enterbranch("VOLUME",partefx)==0) continue;
            setPsysefxvol(partefx,nefx,xml->getpar127("vol",Psysefxvol[partefx][nefx]));
            xml->exitbranch();
        };

        for (int tonefx=nefx+1;tonefx<NUM_SYS_EFX;tonefx++){
            if (xml->enterbranch("SENDTO",tonefx)==0) continue;
            setPsysefxsend(nefx,tonefx,xml->getpar127("send_vol",Psysefxsend[nefx][tonefx]));
            xml->exitbranch();
        };
        xml->exitbranch();
    };
    xml->exitbranch();
    };


    if (xml->enterbranch("INSERTION_EFFECTS")){
    for (int nefx=0;nefx<NUM_INS_EFX;nefx++){

        if (xml->enterbranch("INSERTION_EFFECT",nefx)==0) continue;
        Pinsparts[nefx]=xml->getpar("part",Pinsparts[nefx],-1,NUM_MIDI_PARTS);

        if (xml->enterbranch("EFFECT")){
            insefx[nefx]->getfromXML(xml);
            xml->exitbranch();
        };
        xml->exitbranch();

    };

    xml->exitbranch();
    };
*/

}

//==============================================================================
void Master::getStateInformation (MemoryBlock& destData)
{
#ifdef USE_PRESET_COMPRESSION
    MemoryOutputStream memoryStream (4096, 16384);
    GZIPCompressorOutputStream compressedXml (&memoryStream);
#endif

    MemoryBlock tempBlock;
    XmlElement xml ("main");

    mutex.enter ();
    addToXML (&xml);
    mutex.exit ();

    String xmlString = xml.createDocument (String::empty);
    tempBlock.append ((const char*) xmlString, xmlString.length ());

#ifdef USE_PRESET_COMPRESSION
    compressedXml.writeString (tempBlock.to64BitEncoding ());
    compressedXml.flush ();
    destData.append (memoryStream.getData (), memoryStream.getDataSize ());
#else
    xmlString = tempBlock.toBase64Encoding ();
    destData.append ((const char*) xmlString, xmlString.length());
#endif
}

void Master::setStateInformation (const void* data, int sizeInBytes)
{
    MemoryBlock mb;

#ifdef USE_PRESET_COMPRESSION
    MemoryInputStream memoryStream (data, sizeInBytes, false);
    GZIPDecompressorInputStream compressedXml (&memoryStream, false);
    BufferedInputStream bufferedStream (&compressedXml, 65536, false);
    mb.fromBase64Encoding (bufferedStream.readEntireStreamAsString ());
#else
    mb.fromBase64Encoding (String ((char*) data));
#endif

    XmlDocument xmlDoc (mb.toString ());
    XmlElement* xml = xmlDoc.getDocumentElement();

    if (xml == 0 || ! xml->hasTagName (T("main")))
    {
        String errString = xmlDoc.getLastParseError();
        std::cout << (const char*) errString << std::endl;
    }
    else
    {
        mutex.enter ();
        updateFromXML (xml);
        mutex.exit ();

        delete xml;
    }
}

