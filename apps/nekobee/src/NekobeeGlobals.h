/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2008 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2004 by Julian Storer.

 ------------------------------------------------------------------------------

 JUCE and JUCETICE can be redistributed and/or modified under the terms of
 the GNU General Public License, as published by the Free Software Foundation;
 either version 2 of the License, or (at your option) any later version.

 JUCE and JUCETICE are distributed in the hope that they will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with JUCE and JUCETICE; if not, visit www.gnu.org/licenses or write to
 Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 Boston, MA 02111-1307 USA

 ------------------------------------------------------------------------------

 If you'd like to release a closed-source product which uses JUCE, commercial
 licenses are also available: visit www.rawmaterialsoftware.com/juce for
 more information.

 ==============================================================================
*/

#ifndef __JUCETICE_NEKOBEEGLOBALS_HEADER__
#define __JUCETICE_NEKOBEEGLOBALS_HEADER__

#include "StandardHeader.h"
#include "JucePluginCharacteristics.h"

#include "Nekobee/nekobee.h"
#include "Nekobee/nekobee_types.h"
#include "Nekobee/nekobee_synth.h"
#include "Nekobee/nekobee_voice.h"
#include "Nekobee/nekobee_ports.h"
#include "Nekobee/nekobee_dssi.h"
#include "Nekobee/gui_data.h"

#include "src/extended/dependancies/dssi-1.0.0/dssi/dssi.h"
#include <alsa/asoundlib.h>

//==============================================================================
/**
    This is a helper class, that will help our poor vst plugin understand
    its wacky vst event structure.
*/
class DssiPluginMidiManager
{
public:

    //==============================================================================
    DssiPluginMidiManager ()
        : maxEventSize (16 * 1024),
          currentMidiCount (0)
    {
        snd_midi_event_new (maxEventSize, &midiParser);
    }
    
    ~DssiPluginMidiManager ()
    {
        snd_midi_event_free (midiParser);
    }

    //==============================================================================
    void convertMidiMessages (MidiBuffer& midiMessages, const int blockSamples)
    {
        const uint8* data;
        int numBytesOfMidiData,
            samplePosition;
        MidiBuffer::Iterator it (midiMessages);

        currentMidiCount = 0;

        while (it.getNextEvent (data,
                                numBytesOfMidiData,
                                samplePosition))
        {
            if (numBytesOfMidiData > maxEventSize)
            {
                maxEventSize = numBytesOfMidiData;
                snd_midi_event_free (midiParser);
                snd_midi_event_new (maxEventSize, &midiParser);
            }

            snd_seq_event_t* event = & midiEventsBuffer [currentMidiCount];
            snd_seq_ev_clear (event);

            snd_midi_event_encode (midiParser,
                                   data,
                                   numBytesOfMidiData,
                                   event);

            if (++currentMidiCount >= 2048)
                break;
        }

        snd_midi_event_reset_encode (midiParser);
    }

    //==============================================================================
    snd_seq_event_t* getMidiEvents () { return (snd_seq_event_t*) &midiEventsBuffer[0]; }
    int getMidiEventsCount () const   { return currentMidiCount; }

protected:

    // internal midi event buffer
    snd_seq_event_t midiEventsBuffer [2048];
    snd_midi_event_t* midiParser;
    int maxEventSize;
    int currentMidiCount;
};


#endif
