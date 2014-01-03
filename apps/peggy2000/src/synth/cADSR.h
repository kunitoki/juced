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

#ifndef CADSR_H
#define CADSR_H


class cADSR
{
private:
    enum { DONE = 0, ATTACK, DECAY, SUSTAIN, RELEASE };

    int state;
    float attackRate, decayRate, sustainLevel, releaseRate;
    float value; //this is the current value of the envelope

    void doAttack(){
        value += attackRate;
        if (value >= 1.0f){
            state = DECAY;
            value = 1.0f;
        }
    }

    void doDecay(){
        value -= decayRate;
        if (value <= sustainLevel) { state = SUSTAIN;}
    }

    void doRelease(){
        value -= releaseRate;
        if(value <= 0.0f){
            state = DONE;
            value = 0.0f;
        }
    }

    void dontDoNuttin(){
    //dummy function to avoid crashes during testing
    }

    void (cADSR::*fpState[5])(void); //Function pointer array for the state functions

public:

    cADSR()
    {
        value = 0.0;
        attackRate = 0.0f;
        decayRate = 0.0f;
        sustainLevel = 0.0f;
        releaseRate = 0.0f;
        state = ATTACK;

        fpState[DONE] = &cADSR::dontDoNuttin;
        fpState[ATTACK] = &cADSR::doAttack;
        fpState[DECAY] = &cADSR::doDecay;
        fpState[SUSTAIN] = &cADSR::dontDoNuttin;
        fpState[RELEASE] = &cADSR::doRelease;
    }

    ~cADSR(){}


    // Process
    float doProcess(int size)
    {
       (this->*fpState[state])();
       return value*value*value;
    }

    void reset()
    {
        state = ATTACK;
        value = 0.0f;
    }

    void release()
    {
        state = RELEASE;
    }

    int getState()
    {
        return state;
    }

    void kill()
    {
        state = DONE;
    }

    void setADSR (float a, float d, float s, float r, float sr, int bs = 32)
    {
        sr = sr * 5.0f;
        bs = bs / 2;
        attackRate =   (1.0f / (sr * jmax(a,0.001f))) * bs;
        decayRate  =    (1.0f / (sr * jmax(d,0.004f))) * bs;
        releaseRate =  (1.0f / (sr * jmax(r,0.0001f))) * bs;
        sustainLevel =  s;
    }

};
#endif


