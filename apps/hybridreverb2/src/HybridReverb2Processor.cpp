/***************************************************************************
 *   Copyright (C) 2009 by Christian Borss                                 *
 *   christian.borss@rub.de                                                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#include "includes.h"
#include "HybridReverb2Processor.h"
#include "MasterAndCommander.h"
#include "gui/EditorComponent.h"
#include "windows_quirks.h"


//==============================================================================
/**
    This function must be implemented to create a new instance of your
    plugin object.
*/
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HybridReverb2Processor();
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter (const String& commandLine)
{
    return new HybridReverb2Processor();
}


//==============================================================================
HybridReverb2Processor::HybridReverb2Processor()
    : master (0),
      partitioner(0),
      convolver(0),
      newConvolver(0)
{
    currentPreset = 1;
    lastUIWidth = 828;
    lastUIHeight = 548;

    master = new MasterAndCommander(this);
    paramPreferences = master->getPreferences();
    paramPartitionWisdom = master->getPartitionWisdom();
    partitioner = new Partitioner(paramPartitionWisdom);

    setLatencySamples(paramPreferences.sflen);
}

HybridReverb2Processor::~HybridReverb2Processor()
{
}

//==============================================================================
const String HybridReverb2Processor::getName() const
{
#ifdef NO_OMP
	return "HybridReverb2";
#else
    return "HybridReverb2 - OpenMP";
#endif
}

int HybridReverb2Processor::getNumParameters()
{
    return 1;
}

float HybridReverb2Processor::getParameter (int index)
{
    float ret = 0.0;
    switch (index) {
    case 0:
        ret = (currentPreset - 1.0) / 255.0;
        break;
    }
    return ret;
}

void HybridReverb2Processor::setParameter (int index, float newValue)
{
    switch (index) {
    case 0:
        int newPreset = roundf(newValue * 255.0 + 1.0);
        if (currentPreset != newPreset)
        {
            // if this is changing the preset number, broadcast a change message which
            // our editor will pick up.
            currentPreset = newPreset;
            sendChangeMessage (this);
        }
        break;
    }
}

const String HybridReverb2Processor::getParameterName (int index)
{
    if (index == 0)
        return T("preset nr.");

    return String::empty;
}

const String HybridReverb2Processor::getParameterText (int index)
{
    if (index == 0)
        return String (currentPreset);

    return String::empty;
}

const String HybridReverb2Processor::getInputChannelName (const int channelIndex) const
{
    return String (channelIndex + 1);
}

const String HybridReverb2Processor::getOutputChannelName (const int channelIndex) const
{
    return String (channelIndex + 1);
}

bool HybridReverb2Processor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool HybridReverb2Processor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool HybridReverb2Processor::acceptsMidi() const
{
    return false;
}

bool HybridReverb2Processor::producesMidi() const
{
    return false;
}

int HybridReverb2Processor::getNumPrograms()
{
    return 1; 
}

int HybridReverb2Processor::getCurrentProgram()
{ 
    return 0;
}

void HybridReverb2Processor::setCurrentProgram (int index)
{
}

const String HybridReverb2Processor::getProgramName (int index) 
{ 
    return String::empty; 
}

void HybridReverb2Processor::changeProgramName (int index, const String& newName) 
{ 
}

//==============================================================================
void HybridReverb2Processor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // do your pre-playback setup stuff here..
}

void HybridReverb2Processor::releaseResources()
{
    // when playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void HybridReverb2Processor::processBlock (AudioSampleBuffer& buffer,
                                   MidiBuffer& midiMessages)
{
    if (newConvolver != 0)
    {
        delete convolver;
        convolver = newConvolver;
        newConvolver = 0;
        for (int i = 0; i < getNumInputChannels(); ++i)
            buffer.applyGainRamp(i, 0, buffer.getNumSamples(), 0.0, 1.0);
    }

    if (convolver != 0)
    {
        convolver->process(buffer);
    }

    // in case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
}

//==============================================================================
AudioProcessorEditor* HybridReverb2Processor::createEditor()
{
    AudioProcessorEditor* ret;
    ret = new EditorComponent (this);
    master->onGuiReady();
    return ret;
}

//==============================================================================
void HybridReverb2Processor::getStateInformation (MemoryBlock& destData)
{
    // create a root element..
    XmlElement xmlState (T("HybridReverb2Settings"));

    // add some attributes to it..
    xmlState.setAttribute (T("pluginVersion"), 2);
    xmlState.setAttribute (T("presetNum"), currentPreset);
    xmlState.setAttribute (T("uiWidth"), lastUIWidth);
    xmlState.setAttribute (T("uiHeight"), lastUIHeight);

    // use this helper function to stuff it into the binary blob and return it..
    copyXmlToBinary (xmlState, destData);

    master->print(String("saving preset: ") +
                  String(currentPreset) +
                  String(" [HybridReverb2Processor::getStateInformation()]\n"));
}

void HybridReverb2Processor::setStateInformation (const void* data, int sizeInBytes)
{
    // use this helper function to get the XML from this binary blob..
    XmlElement* const xmlState = getXmlFromBinary (data, sizeInBytes);

    if (xmlState != 0)
    {
        // check that it's the right type of xml..
        if (xmlState->hasTagName (T("HybridReverb2Settings")))
        {
            // ok, now pull out our parameters..
            currentPreset = xmlState->getIntAttribute (T("presetNum"), currentPreset);

            lastUIWidth = xmlState->getIntAttribute (T("uiWidth"), lastUIWidth);
            lastUIHeight = xmlState->getIntAttribute (T("uiHeight"), lastUIHeight);

            master->print(String("restoring preset: ") +
                          String(currentPreset) +
                          String(" [HybridReverb2Processor::setStateInformation()]\n"));

            sendChangeMessage (this);
        }

        delete xmlState;
    }
}


//==============================================================================
void HybridReverb2Processor::setNewFilterSet(SampleData *impulses)
{
    int hlen, type, sflen, mflen, lflen;
    HybridConvolver *brandnewConvolver;

    master->print(T("*** updating filter ***\n"));
    paramPreferences = master->getPreferences();
    hlen = impulses->getDataLen();
    sflen = paramPreferences.sflen;
    partitioner->analyze(hlen, sflen, paramPreferences.strategy);
    mflen = partitioner->getM();
    lflen = partitioner->getL();
    type  = partitioner->getType();

    switch (type) {
    case PARTITION_TYPE_TRIPPLE:
        brandnewConvolver = new HybridConvolverTripple(sflen, mflen, lflen, impulses);
        break;
    case PARTITION_TYPE_DUAL:
        brandnewConvolver = new HybridConvolverDual(sflen, mflen, impulses);
        break;
    default:
        brandnewConvolver = new HybridConvolverSingle(sflen, impulses);
    }

    HybridConvolver *delConvolver = 0;

    // critical section
    getCallbackLock().enter();
    if (convolver == 0)
        convolver = brandnewConvolver;
    else
    {
        if (newConvolver != 0)
            delConvolver = newConvolver;
        newConvolver = brandnewConvolver;
    }
    getCallbackLock().exit();

    if (delConvolver != 0)
        delete delConvolver;
}
