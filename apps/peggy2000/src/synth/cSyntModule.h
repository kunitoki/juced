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

#ifndef CSYNTMODULE_H
#define CSYNTMODULE_H

#include "cVoice.h"
#include "../parameters.h"

/*
This class handles parameters and voices. Most of the actual magic happens
in the voice objects.
*/
class cSyntModule {
private:

     ParMan * Pars;

     float SampleRate;
     int Benchwarmer;
     int numVoices;
     cVoice * voices[9];

     int playCount;

     int numSamples;
     float * outPtr;
     int tmp;

public:

     cSyntModule(ParMan * P)
     {
          numVoices = 9;
          Pars = P;
          SampleRate = 44100;

          Benchwarmer = 8;
          playCount = 1;

          numSamples = 0;
          outPtr = 0;
          tmp = 0;

          for(int i = 0; i < numVoices; i++){ //make voices
               voices[i] = new cVoice(Pars);
          }
     }

     ~cSyntModule()
     {
          for(int i = 0; i<numVoices; i++){
               delete voices[i];
          }
     }

     void doProcess (AudioSampleBuffer* output)
     {
        // Since we dont know how large the out-buffer is
        // and the voice objects work in chunks of 16 samples
        // we need to buffer and keep samples between calls.

        numSamples = output->getNumSamples();                    //total samples we need to write
        outPtr = output->getSampleData(0, 0); //move past what we already filled from the buffers

        voices[0]->doProcess (&outPtr[0], numSamples);
        voices[1]->doProcess (&outPtr[0], numSamples);
        voices[2]->doProcess (&outPtr[0], numSamples);
        voices[3]->doProcess (&outPtr[0], numSamples);
        voices[4]->doProcess (&outPtr[0], numSamples);
        voices[5]->doProcess (&outPtr[0], numSamples);
        voices[6]->doProcess (&outPtr[0], numSamples);
        voices[7]->doProcess (&outPtr[0], numSamples);
        voices[8]->doProcess (&outPtr[0], numSamples);
    }

    void setSampleRate(float s){
        SampleRate = s;
    }

    // note as midi number, velocity as 0-127,
    // preroll: the number of samples that should pass before it starts
    void playNote(int note, int vel, int preroll )
    {
          note = note + 12;
          playCount++;
          int OldestOn = numVoices;
          int OldestOff = numVoices;
          int OldestReleased = numVoices;

          int tmpOn = 100000000;
          int tmpOff = 100000000;
          int tmpReleased = 100000000;
          for(int i = 0; i < numVoices; i++)
          {
          //find the oldest voice
               if (i == Benchwarmer){ continue; }
               if (!voices[i]->getIsOn()){
                    OldestOff = i;
                    break;
               }
               if (voices[i]->getIsReleased()){
                    OldestReleased = (voices[i]->getOrdinal() < tmpReleased) ? i : OldestReleased;
                    tmpReleased = voices[OldestReleased]->getOrdinal();
                    continue;
               }
               OldestOn = (voices[i]->getOrdinal() < tmpOn) ? i : OldestOn;
               tmpOn = voices[OldestOn]->getOrdinal();
          }
          //a free voice
          if (OldestOff < numVoices){
               voices[OldestOff]->start(float(MidiMessage::getMidiNoteInHertz(note)), float(vel / 127.0f), note, preroll, SampleRate, playCount);
               return;
          }
          //the oldest released voice
          if (OldestReleased < numVoices){
               voices[Benchwarmer]->start(float(MidiMessage::getMidiNoteInHertz(note)), float(vel / 127.0f), note, preroll, SampleRate, playCount++);
               Benchwarmer = OldestReleased;
               voices[OldestReleased]->quickRelease();
               return;
          }
          //the oldest playing voice
          if (OldestOn < numVoices){
               voices[Benchwarmer]->start(float(MidiMessage::getMidiNoteInHertz(note)), float(vel / 127.0f), note, preroll, SampleRate, playCount++);
               Benchwarmer = OldestOn;
               voices[OldestOn]->quickRelease();
               return;
          }
    }

    // note as midi number,
    // preroll: the number of samples that should pass before it starts
    void releaseNote(int note, int preroll )
    {
        note = note + 12;
        for(int i = 0; i < numVoices; i++)
        {
            if (voices[i]->getNote() == note)
                voices[i]->release(preroll);
        }
    }

    void kill()
    {
        for(int i = 0; i < numVoices; i++)
            voices[i]->kill();
    }

    // When params change, some classes need to do some recalculating
    // This is how we tell them they need to do it, and which param
    void update(int index)
    {
        for(int i = 0; i < numVoices; i++)
              voices[i]->update(index);
    }

};

#endif
