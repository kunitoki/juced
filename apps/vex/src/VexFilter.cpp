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

#include "VexFilter.h"
#include "VexEditorComponent.h"

AudioProcessor* JUCE_CALLTYPE createPluginFilter (const String& commandLine)
{
    return new VexFilter();
}

VexFilter::VexFilter()
{
	DBG(String("*************** vex constructor called"));
	pMan =  new PresetMan();
	pMan->setPointersToCurrent(&pra, &p1, &p2, &p3);

	s1 = new cSyntModule(pra);
	c1 = new cChorus(pra);
	r1 = new cReverb(pra);
	d1 = new cDelay(pra);

	obf = NULL;
	abf = NULL;
	dbf2 = NULL;
	dbf3 = NULL;
	dbf = NULL;
	snum = 0;

	a1 = new cArp(&p1);
	a2 = new cArp(&p2);
	a3 = new cArp(&p3);

	setCurrentProgram(0);
}



VexFilter::~VexFilter()
{
	DBG(String("*************** vex destructor called"));
	delete obf;
	delete abf;
	delete dbf;
	delete dbf2;
	delete dbf3;
	delete s1;
	delete c1;
	delete r1;
	delete d1;
	delete a1;
	delete a2;
	delete a3;
	delete pMan;
}

const String VexFilter::getInputChannelName (const int channelIndex) const
{
    return String (channelIndex + 1);
}

const String VexFilter::getOutputChannelName (const int channelIndex) const
{
    return String (channelIndex + 1);
}

bool VexFilter::isInputChannelStereoPair (int index) const
{
    return false;
}

bool VexFilter::isOutputChannelStereoPair (int index) const
{
    return true;
}

float VexFilter::getParameter (int index)
{
    return pra[index];
}

void VexFilter::setParameter (int index, float newValue)
{
	if ( pra[index] != newValue )
	{
		pra[index] = newValue;
		dirtyList.push_back(index);
		sendChangeMessage(this);
	}
}

void VexFilter::setParameter (int index, float newValue, bool fromGUI)
{
	pra[index] = newValue;
	s1->update(index);
	if(index < 89)
	{
		setParameterNotifyingHost(index, newValue);
	}
}

void VexFilter::setWave(int part, const String& waveName)
{
	s1->setWave(part, waveName);
	pMan->setWaveName(part, waveName); //store in preset bank
}

String VexFilter::getWave(int part)
{
	return pMan->getWaveName(part);
}

peggySettings* VexFilter::getPeggySet(int prt)
{
	if(prt == 1) return p1;
	if(prt == 2) return p2;
	if(prt == 3) return p3;

	return 0;
}

const String VexFilter::getParameterName (int index)
{
    return String(T("Farty pants!"));
}

const String VexFilter::getParameterText (int index)
{
	return String (pra[index], 2);
}

void VexFilter::prepareToPlay (double sampleRate, int samplesPerBlock)
{	
	s1->setSampleRate(sampleRate);
	c1->setSampleRate(sampleRate);
	d1->setSampleRate(sampleRate);

	if (obf == NULL)		{obf		= new AudioSampleBuffer(2, samplesPerBlock);}
	if (abf == NULL)	{abf	= new AudioSampleBuffer(2, samplesPerBlock);}
	if (dbf == NULL)	{dbf	= new AudioSampleBuffer(2, samplesPerBlock);}
	if (dbf2 == NULL)	{dbf2	= new AudioSampleBuffer(2, samplesPerBlock);}
	if (dbf3 == NULL)	{dbf3	= new AudioSampleBuffer(2, samplesPerBlock);}
}

void VexFilter::releaseResources()
{
	delete obf;
	delete abf;
	delete dbf;
	delete dbf2;
	delete dbf3;
	obf = NULL;
	abf = NULL;
	dbf2 = NULL;
	dbf3 = NULL;
	dbf = NULL;
}

void VexFilter::processBlock ( AudioSampleBuffer& output,
                               MidiBuffer& midiMessages)
{
	AudioPlayHead::CurrentPositionInfo pos;
	getPlayHead()->getCurrentPosition(pos);

	MidiBuffer part1Midi;
	MidiBuffer part2Midi;
	MidiBuffer part3Midi;

	if (p1->on)
	{
		part1Midi = a1->processMidi(midiMessages, (int)getSampleRate(), pos.isPlaying, pos.ppqPosition, pos.ppqPositionOfLastBarStart, pos.bpm, output.getNumSamples());
	}
	else
	{
		part1Midi = midiMessages;
	}

	if (p2->on)
	{
		part2Midi = a2->processMidi(midiMessages, (int)getSampleRate(), pos.isPlaying, pos.ppqPosition, pos.ppqPositionOfLastBarStart, pos.bpm, output.getNumSamples());
	}
	else
	{
		part2Midi = midiMessages;
	}

	if (p3->on)
	{
		part3Midi = a3->processMidi(midiMessages, (int)getSampleRate(), pos.isPlaying, pos.ppqPosition, pos.ppqPositionOfLastBarStart, pos.bpm, output.getNumSamples());
	}
	else
	{
		part3Midi = midiMessages;
	}
 
	
	MidiMessage midi_message(0xf4);
	MidiBuffer::Iterator Iterator1(part1Midi);

	while(Iterator1.getNextEvent(midi_message, snum))
	{
		if( midi_message.isNoteOn())
		{
			s1->playNote(midi_message.getNoteNumber(), midi_message.getVelocity(), snum, 1);
		}
		else if( midi_message.isNoteOff())
		{
			s1->releaseNote(midi_message.getNoteNumber(), snum, 1 );
		}
		else if( midi_message.isAllSoundOff())
		{
			s1->kill();
		}
		else if( midi_message.isAllNotesOff())
		{
			s1->releaseAll(snum);
		}
	}

	MidiBuffer::Iterator Iterator2(part2Midi);

	while(Iterator2.getNextEvent(midi_message, snum))
	{
		if( midi_message.isNoteOn())
		{
			s1->playNote(midi_message.getNoteNumber(), midi_message.getVelocity(), snum, 2);
		}
		else if( midi_message.isNoteOff())
		{
			s1->releaseNote(midi_message.getNoteNumber(), snum, 2 );
		}
	}

	MidiBuffer::Iterator Iterator3(part3Midi);

	while(Iterator3.getNextEvent(midi_message, snum))
	{
		if( midi_message.isNoteOn())
		{
			s1->playNote(midi_message.getNoteNumber(), midi_message.getVelocity(), snum, 3);
		}
		else if( midi_message.isNoteOff())
		{
			s1->releaseNote(midi_message.getNoteNumber(), snum, 3 );
		}
	}

	midiMessages.clear();

	if (output.getNumSamples() != obf->getNumSamples())
	{
		obf		->setSize(2, output.getNumSamples(),0,0,1);
		abf		->setSize(2, output.getNumSamples(),0,0,1);
		dbf		->setSize(2, output.getNumSamples(),0,0,1);
		dbf2	->setSize(2, output.getNumSamples(),0,0,1);
		dbf3	->setSize(2, output.getNumSamples(),0,0,1);
	}

	obf	->clear();
	dbf	->clear();
	dbf2->clear();
	dbf3->clear();

	s1->doProcess(obf, abf, dbf, dbf2, dbf3);
	
	if (pra[75] > 0.001f) d1->processBlock(dbf, pos.bpm);
	if (pra[78] > 0.001f) c1->processBlock(dbf2);
	if (pra[82] > 0.001f) r1->processBlock(dbf3);

	output.clear();
	obf->addFrom (0, 0, *dbf, 0,0,output.getNumSamples(), pra[75]);
	obf->addFrom (1, 0, *dbf, 1,0,output.getNumSamples(), pra[75]);
	obf->addFrom (0, 0, *dbf2, 0,0,output.getNumSamples(), pra[78]);
	obf->addFrom (1, 0, *dbf2, 1,0,output.getNumSamples(), pra[78]);
	obf->addFrom (0, 0, *dbf3, 0,0,output.getNumSamples(), pra[82]);
	obf->addFrom (1, 0, *dbf3, 1,0,output.getNumSamples(), pra[82]);
	output.addFrom (0, 0, *obf, 0,0,output.getNumSamples(), pra[0]);
	output.addFrom (1, 0, *obf, 1,0,output.getNumSamples(), pra[0]);
}

AudioProcessorEditor* VexFilter::createEditor()
{
    return new VexEditorComponent (this);
}

void VexFilter::getStateInformation(MemoryBlock& destData)
{
	int cp = pMan->getCurrentProgram();

    XmlElement xmlState (T("VEXBANK"));

	for (int i = 0; i < pMan->getNumPrograms(); i++)
	{
		pMan->setCurrentProgram(i);
		
		destData.append( pMan->getProgramStruct(i)->parameters, sizeof(float) * 92 );
		destData.append( &pMan->getProgramStruct(i)->pegSet1,	sizeof(peggySettings));
		destData.append( &pMan->getProgramStruct(i)->pegSet2,	sizeof(peggySettings));
		destData.append( &pMan->getProgramStruct(i)->pegSet3,	sizeof(peggySettings));
		
		xmlState.setAttribute( String("Name")	+ String(i),	pMan->getProgramName(i));
		xmlState.setAttribute( String("W1")		+ String(i),	pMan->getWaveName(1));
		xmlState.setAttribute( String("W2")		+ String(i),	pMan->getWaveName(2));
		xmlState.setAttribute( String("W3")		+ String(i),	pMan->getWaveName(3));
	}
	xmlState.setAttribute( String("CurrentProgram"),cp);

	MemoryBlock tmp;

	copyXmlToBinary (xmlState, tmp);
	destData.append(tmp.getData(), tmp.getSize());
	
	pMan->setCurrentProgram(cp);
}

void VexFilter::setStateInformation (const void* data, int sizeInBytes)
{	
	getCallbackLock().enter();

	int f92 = sizeof(float) * 92;
	int pSize = f92 + sizeof(peggySettings) * 3;
	int xmlOffset = pSize * pMan->getNumPrograms();
	
	char* dataBytePtr = (char*)data;

    XmlElement* const xmlState = getXmlFromBinary ( &dataBytePtr[xmlOffset], sizeInBytes - xmlOffset);

    if (xmlState != 0)
    {
        if (xmlState->hasTagName (T("VEXBANK")))
        {
			for (int i = 0; i < pMan->getNumPrograms(); i++)
			{
				pMan->setCurrentProgram(i);
				pMan->changeProgramName(i, xmlState->getStringAttribute(String("Name") + String(i))); 
				pMan->setWaveName(1, xmlState->getStringAttribute(String("W1") + String(i)));
				pMan->setWaveName(2, xmlState->getStringAttribute(String("W2") + String(i)));
				pMan->setWaveName(3, xmlState->getStringAttribute(String("W3") + String(i)));

				memcpy( pMan->getProgramStruct(i)->parameters,	&dataBytePtr[pSize * i] , sizeof(float) * 92 );
				memcpy( &pMan->getProgramStruct(i)->pegSet1,	&dataBytePtr[f92 + pSize * i] , sizeof(peggySettings));
				memcpy( &pMan->getProgramStruct(i)->pegSet2,	&dataBytePtr[sizeof(peggySettings) + f92 + pSize * i] , sizeof(peggySettings));
				memcpy( &pMan->getProgramStruct(i)->pegSet3,	&dataBytePtr[2 * sizeof(peggySettings) + f92 + pSize * i] , sizeof(peggySettings));

			}
			setCurrentProgram(xmlState->getIntAttribute(String("CurrentProgram")));
        }
        delete xmlState;
	} 

	getCallbackLock().exit();
}

void VexFilter::setCurrentProgramStateInformation (const void* data, int sizeInBytes)
{
	getCallbackLock().enter();
	int cp = pMan->getCurrentProgram();
	int f92 = sizeof(float) * 92;
	int pSize = f92 + sizeof(peggySettings) * 3;
	
	char* dataBytePtr = (char*)data;

    XmlElement* const xmlState = getXmlFromBinary ( &dataBytePtr[pSize], sizeInBytes - pSize);
	
	jassert(xmlState != 0);
    if (xmlState != 0)
    {
        if (xmlState->hasTagName (T("VEXPROGRAM")))
        {

			pMan->changeProgramName(cp, xmlState->getStringAttribute(String("Name"))); 
			pMan->setWaveName(1, xmlState->getStringAttribute(String("W1")));
			pMan->setWaveName(2, xmlState->getStringAttribute(String("W2")));
			pMan->setWaveName(3, xmlState->getStringAttribute(String("W3")));

			memcpy( pMan->getProgramStruct(cp)->parameters,	dataBytePtr , sizeof(float) * 92 );
			memcpy( &pMan->getProgramStruct(cp)->pegSet1,	&dataBytePtr[f92] , sizeof(peggySettings));
			memcpy( &pMan->getProgramStruct(cp)->pegSet2,	&dataBytePtr[sizeof(peggySettings) + f92] , sizeof(peggySettings));
			memcpy( &pMan->getProgramStruct(cp)->pegSet3,	&dataBytePtr[2 * sizeof(peggySettings) + f92] , sizeof(peggySettings));

			setCurrentProgram(cp);
        }
        delete xmlState;
	} 

	getCallbackLock().exit();
}

void VexFilter::getCurrentProgramStateInformation (MemoryBlock& destData)
{
	int cp = pMan->getCurrentProgram();

    XmlElement xmlState (T("VEXPROGRAM"));
	
	destData.append( pMan->getProgramStruct(cp)->parameters, sizeof(float) * 92 );
	destData.append( &pMan->getProgramStruct(cp)->pegSet1,	sizeof(peggySettings));
	destData.append( &pMan->getProgramStruct(cp)->pegSet2,	sizeof(peggySettings));
	destData.append( &pMan->getProgramStruct(cp)->pegSet3,	sizeof(peggySettings));
	
	xmlState.setAttribute( String("Name"),	pMan->getProgramName(cp));
	xmlState.setAttribute( String("W1"),	pMan->getWaveName(1));
	xmlState.setAttribute( String("W2"),	pMan->getWaveName(2));
	xmlState.setAttribute( String("W3"),	pMan->getWaveName(3));


	MemoryBlock tmp;

	copyXmlToBinary (xmlState, tmp);
	destData.append(tmp.getData(), tmp.getSize());
	
	pMan->setCurrentProgram(cp);
}

const	String VexFilter::getProgramName(int index)	{ return pMan->getProgramName(index); }

void	VexFilter::changeProgramName(int index, const String& newName)	{ pMan->changeProgramName (index, newName);	}

int		VexFilter::getNumPrograms()					{ return pMan->getNumPrograms(); }

int		VexFilter::getCurrentProgram()				{ return pMan->getCurrentProgram(); }

void	VexFilter::setCurrentProgram(int index)	
{ 
	DBG("setCurrentProgram");
	getCallbackLock().enter();

	pMan->setCurrentProgram(index); 
	pMan->setPointersToCurrent(&pra, &p1, &p2, &p3);

	s1->setWave(1, pMan->getWaveName(1));
	s1->setWave(2, pMan->getWaveName(2));
	s1->setWave(3, pMan->getWaveName(3));

	s1->updateParameterPtr(pra);
	c1->updateParameterPtr(pra);
	d1->updateParameterPtr(pra);
	r1->updateParameterPtr(pra);

	s1->update(3);		s1->update(4);		s1->update(9);		s1->update(14);
	s1->update(27);		s1->update(28);		s1->update(33);		s1->update(38);
	s1->update(51);		s1->update(52);		s1->update(57);		s1->update(62);
	s1->update(89);		s1->update(90);		s1->update(91);

	sendChangeMessage(this);

	getCallbackLock().exit();
}

