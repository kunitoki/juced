/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2008 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2008 by Julian Storer.

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

   @author  rockhardbuns
   @tweaker Lucio Asnaghi

 ==============================================================================
*/

#include "JuceFilter.h"
#include "EditorComponent.h"

//==============================================================================
JuceFilter::JuceFilter()
{
     OutBuffer = 0;
     Pars = new ParMan();
     synt = new cSyntModule(Pars);
     chorus = new cChorus(Pars);
     delay = new cDelay(Pars);
     arp = new cArp(Pars);

     for (int i = 0; i < Pars->getNumPars(); i++)
          synt->update(i);

     arp->setSegment (1, Pars->getParameter(ParMan::g_g1));
     arp->setSegment (2, Pars->getParameter(ParMan::g_g2));
     arp->setSegment (3, Pars->getParameter(ParMan::g_g3));
     arp->setSegment (4, Pars->getParameter(ParMan::g_g4));
     ProgName = "Default";
}

JuceFilter::~JuceFilter()
{
    delete Pars;
    delete synt;
    delete chorus;
    delete delay;
    delete arp;
}

//==============================================================================
const String JuceFilter::getInputChannelName (const int channelIndex) const
{
    return String (channelIndex + 1);
}

const String JuceFilter::getOutputChannelName (const int channelIndex) const
{
    return String (channelIndex + 1);
}

bool JuceFilter::isInputChannelStereoPair (int index) const
{
    return false;
}

bool JuceFilter::isOutputChannelStereoPair (int index) const
{
    return true;
}

//==============================================================================
int JuceFilter::getNumParameters()
{
    return 31; // Pars->getNumPars ();
}

float JuceFilter::getParameter (int index)
{
    return Pars->getParameter(index);
}


void JuceFilter::setParameter (int index, float newValue)
{
     if (Pars->getParameter(index) != newValue) {Pars->setParameter(index,newValue);}
     synt->update(index);
     if (index == ParMan::g_on){ synt->kill(); }
     if (index == ParMan::g_g1){ arp->setSegment(1, newValue); }
     if (index == ParMan::g_g2){ arp->setSegment(2, newValue); }
     if (index == ParMan::g_g3){ arp->setSegment(3, newValue); }
     if (index == ParMan::g_g4){ arp->setSegment(4, newValue); }

}

const String JuceFilter::getParameterName (int index)
{
    switch (index)
    {
        case 0:  return String("pitch env a");     break;
        case 1:  return String("pitch env d");     break;
        case 2:  return String("pitch env s");     break;
        case 3:  return String("pitch env r");     break;
        case 4:  return String("filter env a");    break;
        case 5:  return String("filter env d");    break;
        case 6:  return String("filter env s");    break;
        case 7:  return String("filter env r");    break;
        case 8:  return String("amp env a");       break;
        case 9:  return String("amp env d");       break;
        case 10: return String("amp env s");       break;
        case 11: return String("amp env r");       break;
        case 12: return String("amp env amt");     break;
        case 13: return String("pitch lfo spd");   break;
        case 14: return String("pitch lfo amt");   break;
        case 15: return String("filter lfo spd");  break;
        case 16: return String("filter lfo amt");  break;
        case 17: return String("amp lfo spd");     break;
        case 18: return String("amp lfo amt");     break;
        case 19: return String("filter sat");      break;
        case 20: return String("filter res");      break;
        case 21: return String("filter cut");      break;
        case 22: return String("chorus spd");      break;
        case 23: return String("chorus dph");      break;
        case 24: return String("chorus mix");      break;
        case 25: return String("delay time");      break;
        case 26: return String("delay level");     break;
        case 27: return String("delay feedback");  break;
        case 28: return String("arp sustain");     break;
        case 29: return String("master vol");      break;
        case 30: return String("arp swing");       break;
    }

    return String ("Reserved");
}

const String JuceFilter::getParameterText (int index)
{
    return String(Pars->getParameter(index));
}

//==============================================================================
void JuceFilter::prepareToPlay (double sampleRate, int samplesPerBlock)
{
     deleteAndZero (OutBuffer);
     OutBuffer = new AudioSampleBuffer (2, samplesPerBlock);

     synt->setSampleRate((float)sampleRate);
     chorus->setSampleRate((float)sampleRate);
     delay->setSampleRate((float)sampleRate);
}


void JuceFilter::releaseResources()
{
     deleteAndZero (OutBuffer);
}


void JuceFilter::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
     AudioPlayHead::CurrentPositionInfo pos;
	 getPlayHead()->getCurrentPosition(pos);

     if (Pars->getParameter(ParMan::g_on))
     {
          arp->processMidi(midiMessages,
                           (int) getSampleRate(),
                           pos.isPlaying,
                           pos.ppqPosition,
                           pos.ppqPositionOfLastBarStart,
                           pos.bpm,
                           buffer.getNumSamples());
     }

     int sample_number;
     MidiBuffer::Iterator inBufferIterator(midiMessages);
     MidiMessage midi_message(0xf4);

     while (inBufferIterator.getNextEvent (midi_message, sample_number))
     {
          if (midi_message.isNoteOn())
          {
               synt->playNote (midi_message.getNoteNumber(), midi_message.getVelocity(), sample_number);
          }
          else if (midi_message.isNoteOff())
          {
               synt->releaseNote (midi_message.getNoteNumber(), sample_number);
          }
          else if (midi_message.isAllNotesOff())
          {
               synt->kill();
          }
     }

     midiMessages.clear();

/*
     if (buffer.getNumSamples() != OutBuffer->getNumSamples())
     {
          OutBuffer->setSize (2, buffer.getNumSamples(), 0, 0, 0);
     }
*/

     OutBuffer->clear();
     synt->doProcess (OutBuffer);

     OutBuffer->copyFrom (1, 0, OutBuffer->getSampleData (0, 0), OutBuffer->getNumSamples());

     if (Pars->getParameter(ParMan::ch_mix) > 0.001f) { chorus->doProcess (OutBuffer); }
     if (Pars->getParameter(ParMan::dl_lvl) > 0.001f) { delay->doProcess (OutBuffer, pos.bpm); }

     buffer.clear ();
     buffer.addFrom (0, 0, *OutBuffer, 0, 0, buffer.getNumSamples(), Pars->getParameter(ParMan::m_vol));
     buffer.addFrom (1, 0, *OutBuffer, 1, 0, buffer.getNumSamples(), Pars->getParameter(ParMan::m_vol));
}


//==============================================================================
void JuceFilter::getStateInformation (MemoryBlock& destData)
{
     XmlElement xmlState (T("PEGGY2000_SETTINGS"));

     for(int i = 0; i < Pars->getNumPars(); i++)
          xmlState.setAttribute (String(i), Pars->getParameter(i));

     copyXmlToBinary (xmlState, destData);
}

void JuceFilter::setStateInformation (const void* data, int sizeInBytes)
{
     XmlElement* const xmlState = getXmlFromBinary (data, sizeInBytes);

     if (xmlState != 0)
     {
          if (xmlState->hasTagName (T("PEGGY2000_SETTINGS")))
          {
               synt->kill();
               for(int i = 0; i < Pars->getNumPars(); i++)
               {
                    Pars->setParameter(i ,(float) xmlState->getDoubleAttribute (String(i), 0.0f));
                    synt->update(i);
               }

          }
          delete xmlState;
     }

     //Update
     arp->setSegment(1, Pars->getParameter(ParMan::g_g1));
     arp->setSegment(2, Pars->getParameter(ParMan::g_g2));
     arp->setSegment(3, Pars->getParameter(ParMan::g_g3));
     arp->setSegment(4, Pars->getParameter(ParMan::g_g4));

     sendChangeMessage (this);
}

//==============================================================================
AudioProcessorEditor* JuceFilter::createEditor()
{
    return new EditorComponent (this);
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter (const String& commandLine)
{
    return new JuceFilter();
}



