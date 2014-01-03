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

#ifndef __JUCETICE_XSYNTHMASTER_HEADER__
#define __JUCETICE_XSYNTHMASTER_HEADER__

#include "../globals.h"
#include "../Effects/EffectMgr.h"
#include "Config.h"
#include "Part.h"
#include "Bank.h"
#include "Util.h"

class Master
{
public:
    Master();
    ~Master();

    // Load/Save all settings from/to a XML file
    bool loadXML (File xmlToLoad);
    bool saveXML (File xmlToSave);

    // This adds the parameters to the XML data
    void addToXML (XmlElement* xml);
    void updateFromXML (XmlElement* xml);

    // Get-Set all data to a newly allocated array (used for juce AudioFilter)
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);

    // Reset total settings to default
    void defaults();

    // Midi IN
    void NoteOn (uint8 chan, uint8 note, uint8 velocity);
    void NoteOff (uint8 chan, uint8 note);
    void SetController (uint8 chan, uint type, int par);
    void ShutUp();

    // Audio Output (part to internal buffer)
    void PartAudioOut (Part* p);
    // Audio Output
    void MasterAudioOut (REALTYPE *outl,REALTYPE *outr);
    // Audio Output (for callback mode). This allows the program to be controled by an external program
    void GetAudioOutSamples (int nsamples, int samplerate, REALTYPE *outl, REALTYPE *outr);

    // Parts
    void partonoff (int npart, int what);
    Part *part[NUM_MIDI_PARTS];

    // Parameters
    uint8 Pvolume;
    uint8 Psolopart;
    uint8 Pkeyshift;
    uint8 Psysefxvol[NUM_SYS_EFX][NUM_MIDI_PARTS];
    uint8 Psysefxsend[NUM_SYS_EFX][NUM_SYS_EFX];
    uint8 shutup; // this is not a parameter, but whatalike

    // Parameters control
    void setPvolume (char Pvolume_);
    void setPkeyshift (char Pkeyshift_);
    void setPsysefxvol (int Ppart, int Pefx, char Pvol);
    void setPsysefxsend (int Pefxfrom, int Pefxto, char Pvol);

    // Effects
    EffectMgr *sysefx[NUM_SYS_EFX]; // system
    EffectMgr *insefx[NUM_INS_EFX]; // insertion

    // Part that's apply the insertion effect; -1 to disable
    short int Pinsparts[NUM_INS_EFX];

    // Peaks for VU-meter
    void vuresetpeaks();
    int vuclipped;
    REALTYPE vuoutpeakl, vuoutpeakr,
             vumaxoutpeakl, vumaxoutpeakr,
             vurmspeakl, vurmspeakr;

    // Peaks for part VU-meters
    REALTYPE vuoutpeakpart[NUM_MIDI_PARTS];
    unsigned char fakepeakpart[NUM_MIDI_PARTS];//this is used to compute the "peak" when the part is disabled

    // Other objects
    Controller ctl;
    TuningMap microtonal;
//    Bank bank;
    FFTWrapper *fft;

    CriticalSection mutex;

private:
    int keyshift;

    REALTYPE volume, oldvolume;
    REALTYPE sysefxvol[NUM_SYS_EFX][NUM_MIDI_PARTS];
    REALTYPE sysefxsend[NUM_SYS_EFX][NUM_SYS_EFX];

    // Temporary mixing samples for part samples which is sent to system effect
    REALTYPE *tmpmixl, *tmpmixr;

    // Audio Output samples (if it used GetAudioOutSamples - eg. for Jack output; elsewhere is unused)
    REALTYPE *audiooutl, *audiooutr;

    // used to know if there is need to call AudioOut by GetAudioOutSamples method
    int ksoundbuffersample;

    // The resampler
#if defined (RESAMPLE_METHOD_INTERNAL)
    REALTYPE ksoundbuffersamplelow;  // used for resampling (eg. if Jack samplerate!= SAMPLE_RATE)
    REALTYPE oldsamplel, oldsampler; // used for resampling
#elif defined (RESAMPLE_METHOD_LIBSAMPLERATE)
    SRC_STATE* src_state_r;
    SRC_STATE* src_state_l;
#endif
};


#endif

