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

#ifndef __JUCETICE_XSYNTHADDITIVENOTE_HEADER__
#define __JUCETICE_XSYNTHADDITIVENOTE_HEADER__

#include "../globals.h"
#include "Envelope.h"
#include "LFO.h"
#include "../DSP/Filter.h"
#include "../Params/ADnoteParameters.h"
#include "../Params/Controller.h"

// FM amplitude tune
#define FM_AMP_MULTIPLIER 14.71280603
#define OSCIL_SMP_EXTRA_SAMPLES 5

class ADnote
{
public:

    ADnote (ADnoteParameters *pars, Controller *ctl_, REALTYPE freq, REALTYPE velocity, int portamento_, int midinote_);
    ~ADnote();

    int noteout (REALTYPE *outl,REALTYPE *outr);
    void relasekey ();
    int finished ();

    /* ready - this is 0 if it is not ready (the parameters has to be computed)
       or other value if the parameters has been computed and if it is ready to output */
    char ready;

private:

    void setfreq(int nvoice,REALTYPE freq);
    void setfreqFM(int nvoice,REALTYPE freq);
    void computecurrentparameters();
    void initparameters();

    void KillVoice(int nvoice);
    void KillNote();

    inline REALTYPE getvoicebasefreq (int nvoice);
    inline REALTYPE getFMvoicebasefreq (int nvoice);

    inline void ComputeVoiceOscillator_LinearInterpolation (int nvoice);
    inline void ComputeVoiceOscillator_CubicInterpolation (int nvoice);
    inline void ComputeVoiceOscillatorMorph (int nvoice);
    inline void ComputeVoiceOscillatorRingModulation (int nvoice);
    inline void ComputeVoiceOscillatorFrequencyModulation (int nvoice, int FMmode); //FMmode=0 for phase modulation, 1 for Frequency modulation
    //  inline void ComputeVoiceOscillatorFrequencyModulation (int nvoice);
    inline void ComputeVoiceOscillatorPitchModulation (int nvoice);
    inline void ComputeVoiceNoise (int nvoice);
    inline void fadein (REALTYPE *smps);

    // GLOBALS
    ADnoteParameters *partparams;
    unsigned char stereo; //if the note is stereo (allows note Panning)
    int midinote;
    REALTYPE velocity, basefreq;

    ONOFFTYPE NoteEnabled;
    Controller *ctl;

    /*****************************************************************/
    /*                    GLOBAL PARAMETERS                          */
    /*****************************************************************/
    struct ADnoteGlobal
    {
        /***********************************
        *   FREQUENCY GLOBAL PARAMETERS    *
        ***********************************/
        REALTYPE Detune; //cents
        Envelope *FreqEnvelope;
        LFO *FreqLfo;

        /***********************************
        *   AMPLITUDE GLOBAL PARAMETERS    *
        ***********************************/
        REALTYPE Volume; // [ 0 .. 1 ]
        REALTYPE Panning; // [ 0 .. 1 ]
        Envelope *AmpEnvelope;
        LFO *AmpLfo;
        struct {
            int Enabled;
            REALTYPE initialvalue,dt,t;
        } Punch;

        /********************************
        *   FILTER GLOBAL PARAMETERS    *
        ********************************/
        Filter *GlobalFilterL,*GlobalFilterR;
        REALTYPE FilterCenterPitch; //octaves
        REALTYPE FilterQ;
        REALTYPE FilterFreqTracking;
        Envelope *FilterEnvelope;
        LFO *FilterLfo;
    }
    NoteGlobalPar;


    /***********************************************************/
    /*                    VOICE PARAMETERS                     */
    /***********************************************************/
    struct ADnoteVoice
    {
        ONOFFTYPE Enabled;  // If the voice is enabled
        int noisetype;      // Voice Type (sound/noise)
        int filterbypass;   // Filter Bypass
        int DelayTicks;     // Delay (ticks)
        REALTYPE *OscilSmp; // Waveform of the Voice

        /************************************
        *     FREQUENCY PARAMETERS          *
        ************************************/
        int fixedfreq;    // if the frequency is fixed to 440 Hz
        int fixedfreqET;  // if the "fixed" frequency varies according to the note (ET)
        REALTYPE Detune,FineDetune;  // cents = basefreq*VoiceDetune
        Envelope *FreqEnvelope;
        LFO *FreqLfo;

        /***************************
        *   AMPLITUDE PARAMETERS   *
        ***************************/
        REALTYPE Panning;  // Panning 0.0=left, 0.5 - center, 1.0 = right
        REALTYPE Volume;   // [-1.0 .. 1.0]
        Envelope *AmpEnvelope;
        LFO *AmpLfo;

        /*************************
        *   FILTER PARAMETERS    *
        *************************/
        Filter *VoiceFilter;
        REALTYPE FilterCenterPitch; // Filter center Pitch
        REALTYPE FilterFreqTracking;
        Envelope *FilterEnvelope;
        LFO *FilterLfo;

        /****************************
        *   MODULLATOR PARAMETERS   *
        ****************************/
        FMTYPE FMEnabled;
        int FMVoice;
        // Voice Output used by other voices if use this as modullator
        REALTYPE *VoiceOut;
        // Wave of the Voice
        REALTYPE *FMSmp;
        REALTYPE FMVolume;
        REALTYPE FMDetune; // in cents
        Envelope *FMFreqEnvelope;
        Envelope *FMAmpEnvelope;
    }
    NoteVoicePar [NUM_VOICES];


    /********************************************************/
    /*    INTERNAL VALUES OF THE NOTE AND OF THE VOICES     */
    /********************************************************/

    // time from the start of the note
    REALTYPE time;

    // fractional part (skip)
    REALTYPE oscposlo[NUM_VOICES], oscfreqlo[NUM_VOICES];

    // integer part (skip)
    int oscposhi[NUM_VOICES], oscfreqhi[NUM_VOICES];

    // fractional part (skip) of the Modullator
    REALTYPE oscposloFM[NUM_VOICES], oscfreqloFM[NUM_VOICES];

    // integer part (skip) of the Modullator
    unsigned short int oscposhiFM[NUM_VOICES], oscfreqhiFM[NUM_VOICES];

    // used to compute and interpolate the amplitudes of voices and modullators
    REALTYPE oldamplitude[NUM_VOICES],
             newamplitude[NUM_VOICES],
             FMoldamplitude[NUM_VOICES],
             FMnewamplitude[NUM_VOICES];

    // used by Frequency Modulation (for integration)
    REALTYPE FMoldsmp[NUM_VOICES];

    // temporary buffer
    REALTYPE *tmpwave;

    // Filter bypass samples
    REALTYPE *bypassl, *bypassr;

    // interpolate the amplitudes
    REALTYPE globaloldamplitude, globalnewamplitude;

    // 1 - if it is the fitst tick (used to fade in the sound)
    char firsttick[NUM_VOICES];

    // 1 if the note has portamento
    int portamento;

    // how the fine detunes are made bigger or smaller
    REALTYPE bandwidthDetuneMultiplier;
};

#endif




