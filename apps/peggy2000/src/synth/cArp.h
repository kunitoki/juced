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

#ifndef CARP_H
#define CARP_H


class cArp
{

private:
     int BitTable[32];
     bool dead, NotesPlaying, doSync, parSync, swingStep;
     bool bGrid[80];
     char cKeysDown[10];
     char cNotesToKill[10];
     float velocities[16];
     char nextStep, length, timeSig;
     float sustain, swing;
     int SamplesPerStep, SampleCount, SampleRate, numSamples;
     int longStep, shortStep;
     bool isPlaying;
     double ppqPosition;
     double ppqPositionOfLastBarStart;
     double bpm;
     ParMan * Pars;

     int meter[4];

public:

     cArp(ParMan * P)
     {
          //lookup table for encoding bools in a float
          BitTable[0] = 2;
          BitTable[1] = 4;
          BitTable[2] = 8;
          BitTable[3] = 16;
          BitTable[4] = 32;
          BitTable[5] = 64;
          BitTable[6] = 128;
          BitTable[7] = 256;
          BitTable[8] = 512;
          BitTable[9] = 1024;
          BitTable[10] = 2048;
          BitTable[11] = 4096;
          BitTable[12] = 8192;
          BitTable[13] = 16384;
          BitTable[14] = 32768;
          BitTable[15] = 65536;
          BitTable[16] = 131072;
          BitTable[17] = 262144;
          BitTable[18] = 524288;
          BitTable[19] = 1048576;

          for(int i = 0; i<10; i++){
               cKeysDown[i] = 0;
               cNotesToKill[i] = 0;
          }

          for(int i = 0; i<16; i++){
               velocities[i] = 0.5f;
          }

          Pars = P;

          nextStep = 0;
          sustain = 0.5f;
          length = 8;
          timeSig = 16;

          meter[0] = 4;
          meter[1] = 8;
          meter[2] = 16;
          meter[3] = 32;

          SamplesPerStep = 11025;
          longStep = shortStep = 11025;
          swingStep = false;

          SampleCount = 0;
          SampleRate = 44100;
          numSamples = 0;
          isPlaying = 0;
          ppqPosition = 0.0;
          ppqPositionOfLastBarStart = 0.0;
          bpm  = 120.0;

          SamplesPerStep = (int(60 / bpm) * SampleRate * 4) / timeSig;


          SampleCount = SamplesPerStep;
          dead =  true;
          parSync = false;
          doSync = true;
     }

     void processMidi(MidiBuffer&  inMidiBuffer, int s,bool ip, double ppqPos, double ppqPOLBS, double b, int ns)
     {
          numSamples = ns;

          for(int i = 0; i<16; i++){
               velocities[i] = Pars->getParameter(ParMan::g_f1 + i);
          }

          swing =  Pars->getParameter(ParMan::g_swn) * 0.5f;
          sustain = Pars->getParameter(ParMan::g_sus);
          length = (int)Pars->getParameter(ParMan::g_len);
          timeSig = meter[(int)Pars->getParameter(ParMan::g_tempo) - 1];
          parSync = ((Pars->getParameter(ParMan::g_mode) - 1) == 1.0f);

          SampleRate = s;
          isPlaying = ip;
          ppqPosition = ppqPos;
          ppqPositionOfLastBarStart = ppqPOLBS;
          bpm  = b;

          MidiBuffer outMidiBuffer; //tmp buffer for keeping the midi output

          //*************************** DONE
          // Loop though the midibuffer, take away note on/off, let the rest pass
          MidiBuffer::Iterator inBufferIterator(inMidiBuffer);
          MidiMessage midi_message(0xf4);
          int sample_number;
          while(inBufferIterator.getNextEvent(midi_message,sample_number)){
               if( midi_message.isNoteOn())   {
                    addNote(char(midi_message.getNoteNumber())); //Adds note to the note array
               }else if( midi_message.isNoteOff()){
                    dropNote(char(midi_message.getNoteNumber())); //drops note from the array
                    //outMidiBuffer.addEvent(MidiMessage::noteOff(1, midi_message.getNoteNumber()), sample_number);
               }else {
                    outMidiBuffer.addEvent(midi_message, sample_number);//pass on anything else
               }
          }
         //***************************


          // BarSync
          //***************************
          SamplesPerStep = int((60 / bpm) * SampleRate * 4) / timeSig;
          if (isPlaying && parSync){
               if(doSync){
                    SampleCount = int((ppqPosition - ppqPositionOfLastBarStart) * ((60 / bpm) * SampleRate)); //offset sample count
                    nextStep = SampleCount / SamplesPerStep; //offset step count
                    //Cycle the counts
                    SampleCount = (SampleCount % SamplesPerStep) + SamplesPerStep -10;
                    nextStep = nextStep % length;
               }
               doSync = false;
          } else {
               doSync = true;
          }

         //***************************

          longStep =  int((1.0f + swing) * SamplesPerStep);
          shortStep = int((1.0f - swing) * SamplesPerStep);
          SamplesPerStep = swingStep ? shortStep : longStep;



         //*************************** DONE
         if (cKeysDown[0]){ //Keys are down

             dead = false;
             SampleCount += numSamples;

             //***
             if(SampleCount >= SamplesPerStep){ //Play step
                 int offset = numSamples - (SampleCount - SamplesPerStep);
                 //***
                 for(int i = 0; i < 5; i++){
                     if((cKeysDown[i]!= 0) && (bGrid[nextStep*5 + i])){ //do we have a note to play?
                         NotesPlaying = true;
                         KillThisNoteLater(cKeysDown[i]);
                         outMidiBuffer.addEvent(MidiMessage::noteOn(1, cKeysDown[i], uint8((velocities[nextStep] * 126) + 1)), offset);
                     }
                 }
                 swingStep = !swingStep;
                 SampleCount -= SamplesPerStep;
                 nextStep++;
                 nextStep = nextStep % length; //Cycle the steps over pattern length
             }
             //***
             if ((SampleCount >= (SamplesPerStep * sustain)) && NotesPlaying){ //Mute step
                 int offset = numSamples - (SampleCount - int(SamplesPerStep*sustain));
                 //***
                 for(int i = 0; i < 10; i++){
                     if(cNotesToKill[i] != 0){ //do we have a note to kill?
                         outMidiBuffer.addEvent(MidiMessage::noteOff(1, cNotesToKill[i]), offset);
                         cNotesToKill[i] = 0;
                     }
                 }
                 NotesPlaying = false;
             }

         //***
         } else if (!dead){ //No keys pressed - kill em all
             for(int i = 0; i < 10; i++){
                 if(cNotesToKill[i] != 0){ //do we have a note to kill?
                     outMidiBuffer.addEvent(MidiMessage::noteOff(1, cNotesToKill[i]), 0);
                     cNotesToKill[i] = 0;
                 }
             }
             nextStep = 0;
             SampleCount = SamplesPerStep;
             dead = true; swingStep = false;
         }
         //***************************

         inMidiBuffer.clear();
         inMidiBuffer = outMidiBuffer; //copy the temp buffer to the main one
     }


     //encode a float to represent 20 bools from the grid
     float getSegment(int seg){
         int iOut = 0;
         seg--;
         for(int i = 0 ; i < 20 ; i++){
             iOut |= (BitTable[i] * bGrid[(seg*20) + i ]);
         }
         return (float)iOut;
     }


     //set a grid segment by decoding a float..
     void setSegment(int seg, float f){
         //AlertWindow::showMessageBox( AlertWindow::NoIcon,T("Whop"), String(f) );
         int val = (int)f;
         seg--;
         for(int i = 0 ; i < 20 ; i++){
             bGrid[(seg*20) + i] = ((val & BitTable[i]) != 0);
         }
     }


     //Add a note to the array, shuffle the notes so they are sorted
     void addNote(char note){
         char tmp = 0;
         for(int i = 0; i < 10; i++){
             if ((note < cKeysDown[i]) || (cKeysDown[i] == 0)){
                 tmp = cKeysDown[i]; cKeysDown[i] = note; note = tmp;
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

};


#endif
