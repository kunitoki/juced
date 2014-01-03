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

#include "MidiInputPlugin.h"
#include "../../../HostFilterBase.h"
#include "../../../ui/plugins/PluginEditorComponent.h"


//==============================================================================
MidiInputPlugin::MidiInputPlugin (const int numChannels_)
  : midiInput (0),
    sampleRate (44100.0)
{
}

MidiInputPlugin::~MidiInputPlugin ()
{
}

//==============================================================================
void MidiInputPlugin::prepareToPlay (double sampleRate_, int samplesPerBlock_)
{
    sampleRate = sampleRate_;

    if (midiInput)
        midiInput->stop ();
    deleteAndZero (midiInput);

    String deviceName = T(JucePlugin_Name);

#if defined (LINUX)
    midiInput = MidiInput::createNewDevice (deviceName, this);
#endif

    if (midiInput)
        midiInput->start ();

    midiCollector.reset (sampleRate);
}

void MidiInputPlugin::releaseResources()
{
    if (midiInput)
        midiInput->stop ();
    deleteAndZero (midiInput);

    midiCollector.reset (sampleRate);
}

void MidiInputPlugin::processBlock (AudioSampleBuffer& buffer,
                                    MidiBuffer& midiMessages)
{
    const int blockSize = buffer.getNumSamples ();
    
    MidiBuffer* midiBuffer = midiBuffers.getUnchecked (0);

    midiCollector.removeNextBlockOfMessages (*midiBuffer, blockSize);
}

//==============================================================================
void MidiInputPlugin::handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message)
{
    midiCollector.addMessageToQueue (message);
}

//==============================================================================
AudioProcessorEditor* MidiInputPlugin::createEditor ()
{
    return 0;
}

