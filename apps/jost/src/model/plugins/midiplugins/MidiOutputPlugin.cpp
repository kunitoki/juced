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

#include "MidiOutputPlugin.h"
#include "../../../ui/plugins/PluginEditorComponent.h"

//==============================================================================
MidiOutputPlugin::MidiOutputPlugin (const int numChannels_)
  : midiOutput (0)
{
}

MidiOutputPlugin::~MidiOutputPlugin ()
{
}

//==============================================================================
void MidiOutputPlugin::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    deleteAndZero (midiOutput);

    String deviceName = T(JucePlugin_Name);

#if defined (LINUX)
    midiOutput = MidiOutput::createNewDevice (deviceName);
#endif
}

void MidiOutputPlugin::releaseResources()
{
    deleteAndZero (midiOutput);
}

void MidiOutputPlugin::processBlock (AudioSampleBuffer& buffer,
                                     MidiBuffer& midiMessages)
{
    MidiBuffer* midiBuffer = midiBuffers.getUnchecked (0);

    if (midiBuffer->getNumEvents() > 0)
    {
        int samplePos = 0;
        MidiMessage msg (0xf4, 0.0);
        MidiBuffer::Iterator eventIterator (*midiBuffer);

        while (eventIterator.getNextEvent (msg, samplePos))
            midiOutput->sendMessageNow (msg);
    }
}

//==============================================================================
AudioProcessorEditor* MidiOutputPlugin::createEditor ()
{
    return 0;
}

