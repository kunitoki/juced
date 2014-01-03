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

#ifndef __JUCETICE_VEXCARP_HEADER__
#define __JUCETICE_VEXCARP_HEADER__

#include "../StandardHeader.h"
#include "../PeggySettings.h"


class cArp
{
public:

	cArp(peggySettings** P)
	{
		memset(cKeysDown, 0, sizeof(cKeysDown));
		memset(cNotesToKill, 0, sizeof(cNotesToKill));
		memset(cKeysVelocity, 0, sizeof(cKeysVelocity));

		psp = P;
		peggySet = *psp;
		for(int i = 0; i < 80; i++)
		{
			peggySet->grid[i] = false;
		}
		//peggySet->velocities[16];

		peggySet->length = 8;
		peggySet->timeMode = 2;
		peggySet->syncMode = 1;
		peggySet->failMode = 1;
		peggySet->velMode = 1;
		peggySet->on = false;

		nextStep = 0;
		timeSig = 16;

		meter[0] = 4;
		meter[1] = 8;
		meter[2] = 16;
		meter[3] = 32;

		SamplesPerStep = 11025;

		SampleCount = 0;

		SamplesPerStep = (int(60 / 120) * 44100 * 4) / timeSig;

		SampleCount = SamplesPerStep;
		dead =  true;
		doSync = true;
	}

    MidiBuffer processMidi (MidiBuffer&  inMidiBuffer,
                            const int SampleRate, 
							const bool isPlaying, 
							const double ppqPosition, 
							const double ppqPositionOfLastBarStart, 
							const double bpm, 
							const int numSamples)
	{
		peggySet = *psp;
		timeSig = meter[peggySet->timeMode];

		MidiBuffer outMidiBuffer; //tmp buffer for keeping the midi output

		// Loop though the midibuffer, take away note on/off, let the rest pass
		MidiBuffer::Iterator inBufferIterator(inMidiBuffer);
		MidiMessage midi_message(0xf4);

		int sample_number;
        while(inBufferIterator.getNextEvent(midi_message,sample_number))
		{
			if( midi_message.isNoteOn())   
			{
				addNote(char(midi_message.getNoteNumber()), char(midi_message.getVelocity())); //Adds note to the note array
			}
			else if( midi_message.isNoteOff())
			{
				dropNote(char(midi_message.getNoteNumber())); //drops note from the array
				//outMidiBuffer.addEvent(MidiMessage::noteOff(1, midi_message.getNoteNumber()), sample_number);
			}
			else 
			{
				outMidiBuffer.addEvent(midi_message, sample_number);//pass on anything else
			}
        }
        //***************************


		// BarSync
		//***************************
		SamplesPerStep = int((60 / bpm) * SampleRate * 4) / timeSig;
		if (isPlaying && peggySet->syncMode == 2)
		{
			if(doSync)
			{
				SampleCount = int((ppqPosition - ppqPositionOfLastBarStart) * ((60 / bpm) * SampleRate)); //offset sample count
				nextStep = SampleCount / SamplesPerStep; //offset step count
				//Cycle the counts
				SampleCount = (SampleCount % SamplesPerStep) + SamplesPerStep - 10;
				nextStep = nextStep % peggySet->length;
			}
			doSync = false;
		} 
		else 
		{
			doSync = true;
		}

        //***************************
		if (cKeysDown[0])
		{ //Keys are down

			dead = false;
			SampleCount += numSamples;
			bool repeat = false;
			do{
				repeat = false;
				//***
				if(SampleCount >= SamplesPerStep)
				{ //Play step
					int offset = numSamples - (SampleCount - SamplesPerStep);
					bool doFail = true;
					for(int i = 0; i < 5; i++)
					{
						if((cKeysDown[i]!= 0) && (peggySet->grid[nextStep*5 + i]))
						{ //we have a note to play
							int vel = 127;
							switch (peggySet->velMode)
							{
							    case 1: vel = roundFloatToInt (peggySet->velocities[nextStep] * 127.0f); break;
							    case 2: vel = (int) cKeysVelocity[i]; break;
							    case 3: vel = (int) cKeysVelocity[i] + roundFloatToInt (peggySet->velocities[nextStep] * 127.0f); break;
							}				
							doFail = false;
							NotesPlaying = true;
							KillThisNoteLater(cKeysDown[i]);
							outMidiBuffer.addEvent(MidiMessage::noteOn(1, cKeysDown[i], uint8(vel)), offset);
						}

					}
					if (doFail)
					{
						switch (peggySet->failMode)
						{
						case 1: //normal
							SampleCount -= SamplesPerStep;
							nextStep++;
							nextStep = nextStep % peggySet->length;	
						break;
						case 2: //skip one
							//SampleCount -= SamplesPerStep;
							nextStep++;
							nextStep = nextStep % peggySet->length;
							repeat = true;
						break;
						case 3: //skip two
							//SampleCount -= SamplesPerStep;
							nextStep += 2;
							nextStep = nextStep % peggySet->length;
							repeat = true;
						break;
						}
					}
					else
					{
						SampleCount -= SamplesPerStep;
						nextStep++;
						nextStep = nextStep % peggySet->length; //Cycle the steps over pattern length
					}
				}
			}while(repeat);

			//***
			unsigned int NoteLength = (SamplesPerStep / 4) * 3;
			if ((SampleCount >= NoteLength) && NotesPlaying)
			{ //Mute step
				int offset = numSamples - (SampleCount - NoteLength);
				//***
				for(int i = 0; i < 10; i++)
				{
					if(cNotesToKill[i] != 0)
					{ //do we have a note to kill?
						outMidiBuffer.addEvent(MidiMessage::noteOff(1, cNotesToKill[i]), offset);
						cNotesToKill[i] = 0;
					}
				}
				NotesPlaying = false;
			}

		//***
		} 
		else if (!dead)
		{ //No keys pressed - kill 'em all
			for(int i = 0; i < 10; i++)
			{
				if(cNotesToKill[i] != 0)
				{ //do we have a note to kill?
					outMidiBuffer.addEvent(MidiMessage::noteOff(1, cNotesToKill[i]), 0);
					cNotesToKill[i] = 0;
				}
			}
			nextStep = 0;
			SampleCount = SamplesPerStep;
			dead = true;
		}
        //***************************

        //inMidiBuffer.clear();
        //inMidiBuffer = outMidiBuffer; //copy the temp buffer to the main one
		return outMidiBuffer;
	}



     //Add a note to the array, shuffle the notes so they are sorted
     void addNote(char note, char vel){
         char tmp = 0;
         for(int i = 0; i < 10; i++){
             if ((note < cKeysDown[i]) || (cKeysDown[i] == 0)){
                 tmp = cKeysDown[i]; cKeysDown[i] = note; note = tmp;
				 tmp = cKeysVelocity[i]; cKeysVelocity[i] = vel; vel = tmp;
             }
         }
         doSync = true;
     }


     //Drop a note from the array, and re-sort it
     void dropNote(char note){
         char tmp = 0;
         for(int i = 0; i < 10; i++){
             if (note == cKeysDown[i]){ cKeysDown[i] = 0; }
         }

         for(int i = 0; i < 9; i++){
             if (cKeysDown[i] == 0){
                 tmp = cKeysDown[i]; cKeysDown[i] = cKeysDown[i+1]; cKeysDown[i+1] = tmp;
             }
         }
     }


     void KillThisNoteLater(char note){
         for(int i = 0; i<10; i++){
             if(cNotesToKill[i] == 0){
                 cNotesToKill[i] = note;
                 break;
             }
         }
     }

private:

	bool dead, NotesPlaying, doSync;
	char nextStep, timeSig;
	unsigned int SamplesPerStep, SampleCount, SampleRate;
	int meter[4];
	peggySettings* peggySet;
	peggySettings** psp;
	char cKeysDown[10];
	char cKeysVelocity[10];
	char cNotesToKill[10];


};


#endif
