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

#ifndef CAMPADSR_H
#define CAMPADSR_H


//Process every sample in a buffer
class cAmpADSR{
private:
    enum { DONE = 0, ATTACK, DECAY, SUSTAIN, RELEASE, QRELEASE };

    int state;
    float attackRate, decayRate, sustainLevel, releaseRate;
    int postCount, preCount; //counter to delay release to sync with the sampleframe
    float value; //this is the current value of the envelope


//******  State functions
    void attack(){
        preCount--;
        value += attackRate * bool(preCount < 1);
        if (value >= 1.0f){
            state = DECAY;
            value = 1.0f;
        }
    }

    void decay(){
        value -= decayRate;
        if (value <= sustainLevel) { state = SUSTAIN;}
    }

    void release(){
        postCount--;
        value -= releaseRate * bool(postCount < 1);
        postCount -= int(postCount > 0);
        if(value <= 0.0f){
            state = DONE;
            value = 0.0f;
        }
    }

    void qrelease(){
        value -= 0.006f;
        if(value <= 0.0f){
            state = DONE;
            value = 0.0f;
        }
    }

    void dontDoNuttin(){
    //dummy function to avoid crashes during testing
    }
//******


    void (cAmpADSR::*fpState[6])(void); //Function pointer array for the state functions


public:
    cAmpADSR(){
        preCount = 0;
        postCount = 0;
        value = 0.0;
        attackRate = 0.0f;
        decayRate = 0.0f;
        sustainLevel = 0.5f;
        releaseRate = 0.0f;
        state = ATTACK;

        fpState[DONE] = &cAmpADSR::dontDoNuttin;
        fpState[ATTACK] = &cAmpADSR::attack;
        fpState[DECAY] = &cAmpADSR::decay;
        fpState[SUSTAIN] = &cAmpADSR::dontDoNuttin;
        fpState[RELEASE] = &cAmpADSR::release;
        fpState[QRELEASE] = &cAmpADSR::qrelease;
    }

    ~cAmpADSR(){}


    // Process a buffer
    void doProcess (float * Buffer, int bSize)
    {
        for(int i = 0; i < bSize; i++){
            (this->*fpState[state])();
            Buffer[i] *= value * value;
        }
    }

    void reset(int p)
    {
        preCount = p;
        state = ATTACK;
        value = 0.0f;
    }

    void release(int p)
    {
        postCount = p;
        state = RELEASE;
    }

    void quickRelease()
    {
        state = QRELEASE;
    }

    bool getState()
    {
        return (state != DONE);
    }

    void kill(){
        state = DONE;
    }

    void setADSR( float a, float d, float s, float r, float sr)
    {
        sr = sr * 5.0f;
        attackRate =   (1.0f / (sr * jmax(a,0.001f)));
        decayRate =    (1.0f / (sr * jmax(d,0.005f)));
        releaseRate =  (1.0f / ((sr * 4) * jmax(r,0.0002f)));
        sustainLevel =  s;
    }
};

#endif


