/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2004 by Lucio Asnaghi.

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

#ifndef __JUCETICE_XDUBDELAYPLUGIN_HEADER__
#define __JUCETICE_XDUBDELAYPLUGIN_HEADER__

#include "StandardHeader.h"
#include "JucePluginCharacteristics.h"


//==============================================================================
/**
    Parameters enum definition
*/
enum
{
    PAR_DELAY = 0,
    PAR_FEEDBACK,
    PAR_TONE,
    PAR_LFODEPTH,
    PAR_LFOSPEED,
    PAR_DRYWET,
    PAR_OUTPUT,

    NUM_PARAMETERS
};


class XDubDelayComponent;

//==============================================================================
/**
    A simple plugin filter that just applies a gain change to its input.

*/
class XDubDelayPlugin  : public AudioPlugin
{
public:

    //==============================================================================
    XDubDelayPlugin();
    ~XDubDelayPlugin();

    //==============================================================================
    const String getName() const          { return JucePlugin_Name; }
    bool acceptsMidi() const              { return JucePlugin_WantsMidiInput; }
    bool producesMidi() const             { return JucePlugin_ProducesMidiOutput; }

    //==============================================================================
    AudioProcessorEditor* createEditor();
    XDubDelayComponent* getEditor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();
    void processBlock (AudioSampleBuffer& buffer,
                       MidiBuffer& midiMessages);

    //==============================================================================
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);
    void initialiseToDefault ();

    //==============================================================================
    juce_UseDebuggingNewOperator

    //==============================================================================
    static int numInstances;

protected:

    //==============================================================================
    friend class XDubDelayComponent;

	float fParam0;
    float fParam1;
    float fParam2;
    float fParam3;
    float fParam4;
    float fParam5;
    float fParam6;

    float *buffer;               //delay
	long size, ipos;             //delay max time, pointer, left time, right time
    float wet, dry, fbk;         //wet & dry mix
    float lmix, hmix, fil, fil0; //low & high mix, crossover filter coeff & buffer
    float env, rel;              //limiter (clipper when release is instant)
    float del, mod, phi, dphi;   //lfo
    float dlbuf;                 //smoothed modulated delay
    float sr;                    //samplerate

    //==============================================================================
    float getDelay (int n);
    void setDelay (int n, float value);
    float getFeedback (int n);
    void setFeedback (int n, float value);
    float getTone (int n);
    void setTone (int n, float value);
    float getLfoDepth (int n);
    void setLfoDepth (int n, float value);
    float getLfoSpeed (int n);
    void setLfoSpeed (int n, float value);
    float getDryWet (int n);
    void setDryWet (int n, float value);
    float getOutput (int n);
    void setOutput (int n, float value);

    AudioParameter params [NUM_PARAMETERS];
};


#endif
