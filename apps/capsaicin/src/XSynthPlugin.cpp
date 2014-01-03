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
*/

#include "XSynthPlugin.h"
#include "XSynthEditor.h"

//==============================================================================
REALTYPE *denormalkillbuf = 0;
int SAMPLE_RATE = 44100;
int SOUND_BUFFER_SIZE = 512;
int OSCIL_SIZE = 512;

//==============================================================================
int XSynthPlugin::numInstances = 0;

//==============================================================================
XSynthPlugin::XSynthPlugin()
{
    parameters = new XSynthParameters (this);

    scanDirectoryForPrograms (Config::getInstance()->CurrentBankDir);

    // std::cout << (const char*) Config::getInstance()->CurrentBankDir.getFullPathName() << std::endl;

    initialiseStateToDefault ();
}

XSynthPlugin::~XSynthPlugin()
{
    deleteAndZero (parameters);

    if (--XSynthPlugin::numInstances == 0)
    {
        Config::deleteInstance ();

        delete[] denormalkillbuf;
        delete[] OscilGen::tmpsmps;
    }
}

//==============================================================================
void XSynthPlugin::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    keyboardState.reset();
}

void XSynthPlugin::releaseResources()
{
}

void XSynthPlugin::processBlock (AudioSampleBuffer& buffer,
                                 MidiBuffer& midiMessages)
{
    // get output buffers
    int blockSamples = buffer.getNumSamples();
    float *outl = buffer.getSampleData (0);
    float *outr = buffer.getSampleData (1);

    buffer.clear();

    // process incoming midi
    midiAutomatorManager.handleMidiMessageBuffer (midiMessages);

    // if any midi messages come in, use them to update the keyboard state object. This
    // object sends notification to the UI component about key up/down changes
    keyboardState.processNextMidiBuffer (midiMessages,
                                         0, blockSamples,
                                         true);

    // process midi messages
    const uint8* midiData;
    int numBytesOfMidiData, samplePosition;
    MidiBuffer::Iterator ev (midiMessages);

    // lock master
    master.mutex.enter ();

    while (ev.getNextEvent (midiData, numBytesOfMidiData, samplePosition))
    {
        int status = midiData[0] / 16;
        int cmdchan = midiData[0] & 0x0f;
        int cntl;

        switch (status)
        {
        case 0x8:
            master.NoteOff (cmdchan, midiData[1] & 0x7f);
            break;
        case 0x9:
            if (midiData[2] == 0)
                master.NoteOff (cmdchan, midiData[1] & 0x7f);
            else
                master.NoteOn (cmdchan, midiData[1] & 0x7f, midiData[2] & 0x7f);
            break;
        case 0xB:
            cntl = getMidiController (midiData[1] & 0x7f);
            master.SetController (cmdchan, cntl, midiData[2] & 0x7f);
            break;
        case 0xE:
            master.SetController (cmdchan, C_pitchwheel, midiData[1] + midiData[2] * (long int) 128 - 8192);
            break;
        }
    }

    master.GetAudioOutSamples (blockSamples, (int) getSampleRate(), outl, outr);

    // unlock master
    master.mutex.exit ();
}

int XSynthPlugin::getMidiController (uint8 b)
{
    int ctl = C_NULL;
    switch (b)
    {
        // CC
        case 1:     ctl = C_modwheel;                  //Modulation Wheel
            break;
        case 7:     ctl = C_volume;                    //Volume
            break;
        case 10:    ctl = C_panning;                   //Panning
            break;
        case 11:    ctl = C_expression;                //Expression
            break;
        case 64:    ctl = C_sustain;                   //Sustain pedal
            break;
        case 65:    ctl = C_portamento;                //Portamento
            break;
        case 71:    ctl = C_filterq;                   //Filter Q (Sound Timbre)
            break;
        case 74:    ctl = C_filtercutoff;              //Filter Cutoff (Brightness)
            break;
        case 75:    ctl = C_bandwidth;                 //BandWidth
            break;
        case 76:    ctl = C_fmamp;                     //FM amplitude
            break;
        case 77:    ctl = C_resonance_center;          //Resonance Center Frequency
            break;
        case 78:    ctl = C_resonance_bandwidth;       //Resonance Bandwith
            break;
        case 120:   ctl = C_allsoundsoff;              //All Sounds OFF
            break;
        case 121:   ctl = C_resetallcontrollers;       //Reset All Controllers
            break;
        case 123:   ctl = C_allnotesoff;               //All Notes OFF
            break;
        //RPN and NRPN
        /*
        case 0x06:  ctl = C_dataentryhi;//Data Entry (Coarse)
            break;
        case 0x26:  ctl = C_dataentrylo;//Data Entry (Fine)
            break;
        case 99:    ctl = C_nrpnhi;//NRPN (Coarse)
            break;
        case 98:    ctl = C_nrpnlo;//NRPN (Fine)
            break;
        */
        default:    ctl = C_NULL;//unknown controlleR
            break;
    }
    return ctl;
}

//==============================================================================
void XSynthPlugin::getStateInformation (MemoryBlock& destData)
{
#if ! JUCE_DEBUG
    try
    {
#endif

        master.getStateInformation (destData);

#if ! JUCE_DEBUG
    }
    catch (...)
    {
        AlertWindow::showMessageBox (AlertWindow::WarningIcon,
                                     T("Error !"),
                                     T("Something bad occurred while saving presets data !"));
    }
#endif
}

void XSynthPlugin::setStateInformation (const void* data, int sizeInBytes)
{
    suspendProcessing (true);

#if ! JUCE_DEBUG
    try
    {
#endif

        if (data && sizeInBytes > 0)
        {
            master.setStateInformation (data, sizeInBytes);

            if (getEditor())
                sendChangeMessage (this);
        }

#if ! JUCE_DEBUG
    }
    catch (...)
    {
        AlertWindow::showMessageBox (AlertWindow::WarningIcon,
                                     T("Error !"),
                                     T("Something bad occurred while restoring presets data !"));
    }
#endif

    suspendProcessing (false);
}

void XSynthPlugin::setCurrentProgram (int index)
{
    setCurrentProgram (index);

    master.shutup = 1;
}

//==============================================================================
static void defaultVoiceParameter (const int numVoice,
                                   const int voiceType,
                                   const int voiceGain,
                                   Part* part)
{
    part->kit[0].adpars->VoicePar[numVoice].Enabled = 1;
    part->kit[0].adpars->VoicePar[numVoice].Type = voiceType;
    part->kit[0].adpars->VoicePar[numVoice].PVolume = voiceGain;
}

void XSynthPlugin::initialiseStateToDefault ()
{
    for (int i = 0; i < NUM_MIDI_PARTS; i++)
    {
        Part* part = master.part[i];

        // global settings
        part->Prcvchn = i;     // midi recive channel

        // synth types
        part->kit[0].Padenabled = 1;

        // additive section voices/oscillators
        part->kit[0].adpars->GlobalPar.PStereo = 1; // stereo voices
//        part->kit[0].adpars->GlobalPar.GlobalFilter->Pcategory = 2; // SVF ?
//        part->kit[0].adpars->GlobalPar.GlobalFilter->changed = 1;

        // voice defaults
        defaultVoiceParameter (0, 0, 100, part);
        defaultVoiceParameter (1, 0, 0, part);
        defaultVoiceParameter (2, 0, 0, part);
        defaultVoiceParameter (3, 0, 0, part);
        defaultVoiceParameter (4, 1, 0,  part);

        // effects routing
        part->partefx [0]->changeEffect (3 /* chorus */);
        part->partefx [0]->setEffectParameter (0, 0);   // volume
        part->partefx [1]->changeEffect (6 /* disto */);
        part->partefx [1]->setEffectParameter (0, 72); // volume
        part->partefx [1]->setEffectParameter (5, 13);  // sigmoid disto
        part->partefx [2]->changeEffect (7 /* equalizer */);
        part->partefx [2]->setEffectParameter (0, 68); // volume
        part->partefx [2]->setEffectParameter ((0 * 5 + 10), 8); // volume
        part->partefx [2]->setEffectParameter ((1 * 5 + 10), 7); // volume
        part->partefx [2]->setEffectParameter ((2 * 5 + 10), 7); // volume
        part->partefx [2]->setEffectParameter ((3 * 5 + 10), 9); // volume

        part->partefx [3]->changeEffect (2 /* delay */);
        part->partefx [3]->setEffectParameter (0, 0);   // volume

        part->Pefxbypass [0] = 0; // enabled
        part->Pefxbypass [1] = 0; // enabled
        part->Pefxbypass [2] = 0; // enabled
        part->Pefxbypass [3] = 0; // enabled
        part->Pefxroute [0] = 0; // to next effect
        part->Pefxroute [1] = 0; // to next effect
        part->Pefxroute [2] = 0; // to next effect
        part->Pefxroute [3] = 1; // to part out

        // hack !
        setParameterNotifyingHost (PPAR (i, PP_X), 0.5f);
        setParameterNotifyingHost (PPAR (i, PP_Y), 0.5f);

        // defaults dynamic controls !
        part->Pctrl [0] = PPAR(i, PP_TONE);
        part->Pctrl [1] = PPAR(i, PP_FILTERCUTOFF);
        part->Pctrl [2] = PPAR(i, PP_FILTERRESO);
        part->Pctrl [3] = PPAR(i, PP_DRIVE_AMOUNT);
    }

//    master.sysefx[0]->changeEffect (10); // GReverb
//    master.sysefx[0]->setEffectParameter (0, 80); // volume
    master.sysefx[0]->changeEffect (0);  // noefx
}

//==============================================================================
XSynthEditor* XSynthPlugin::getEditor()
{
    return (XSynthEditor*) getActiveEditor();
}

AudioProcessorEditor* XSynthPlugin::createEditor()
{
    return new XSynthEditor (this);
}

//==============================================================================
AudioProcessor* JUCE_CALLTYPE createPluginFilter (const String& createArgs)
{
    if (XSynthPlugin::numInstances++ == 0)
    {
        Config* config = Config::getInstance ();
        config->load ();

        SAMPLE_RATE = config->SampleRate;
        SOUND_BUFFER_SIZE = config->SoundBufferSize;
        OSCIL_SIZE = config->OscilSize;

        denormalkillbuf = new REALTYPE [SOUND_BUFFER_SIZE];
        for (int i = 0; i < SOUND_BUFFER_SIZE; i++)
            denormalkillbuf[i] = (RND - 0.5) * 1e-16;

        OscilGen::tmpsmps = new REALTYPE[OSCIL_SIZE];
        newFFTFREQS (&OscilGen::outoscilFFTfreqs, OSCIL_SIZE / 2);
    }

    return new XSynthPlugin();
}

#ifdef JUCE_MAC
AudioProcessor* JUCE_CALLTYPE createPluginFilter ()
{
    return createPluginFilter(String());
}
#endif


