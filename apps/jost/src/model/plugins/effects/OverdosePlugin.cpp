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

#include "OverdosePlugin.h"
#include "OverdoseEditor.h"


//==============================================================================
OverdosePlugin::OverdosePlugin()
{
	//Create parameter manager
	Pars = new OverdoseParMan();
	
	filt1 = filt2 = 0.0f;

	cp = 0;
	temppr=1;
	setCurrentProgram(cp);

	ProgName[0] = "Phantom";
	ProgName[1] = "Nice";
	ProgName[2] = "Nasty";
}

OverdosePlugin::~OverdosePlugin()
{
	 delete Pars;
}

//==============================================================================
void OverdosePlugin::setMagnus(float val)
{
	magnus = val;
}

float OverdosePlugin::getMagnus()
{
	return magnus;
}

//==============================================================================
int OverdosePlugin::getNumParameters()
{
	return Pars->getNumPars();
}

float OverdosePlugin::getParameter (int paramNumber)
{
	return Pars->getParameter(paramNumber);
}

void OverdosePlugin::setParameter (int paramNumber, float value)
{
	if (Pars->getParameter(paramNumber) != value) {Pars->setParameter(paramNumber, value);}

	filt = (float)pow(10.0,-1.6 * Pars->getParameter(OverdoseParMan::muffle));
	gainer = (float)pow(10.0f, 2.0f * Pars->getParameter(OverdoseParMan::output) - 1.0f);
}

const String OverdosePlugin::getParameterName (int paramNumber)
{
    switch (paramNumber){
     case 0: return String("drive");  break;
     case 1: return String("muffle");  break;
	 case 2: return String("output");  break;
	}

    return String::empty;
}

const String OverdosePlugin::getParameterText (int paramNumber)
{
    
	return String(Pars->getParameter(paramNumber));
}

//==============================================================================
void OverdosePlugin::initToDefault()
{
	Pars->loadPreset(0);
}

void OverdosePlugin::setCurrentProgram(int index)
{
	switch (index)
	{
	case 0: cp = 0; Pars->loadPreset(0); 
			for (int i = 0; i < Pars->getNumPars() ; i++)
			{ setParameter(i, Pars->getParameter(i)); }
			break;

	 case 1: cp = 1; Pars->loadPreset(1); 
			for (int i = 0; i < Pars->getNumPars() ; i++)
			{ setParameter(i, Pars->getParameter(i)); }
			break;

	 case 2: cp = 2; Pars->loadPreset(2); 
			for (int i = 0; i < Pars->getNumPars() ; i++)
			{ setParameter(i, Pars->getParameter(i)); }
			break;
	}
}

//==============================================================================
void OverdosePlugin::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // do your pre-playback setup stuff here..
    keyboardState.reset();
}

void OverdosePlugin::releaseResources()
{
    // when playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void OverdosePlugin::overdose (AudioSampleBuffer* buffer, AudioSampleBuffer* out, int sampleFrames)
{
	float *in1 = buffer->getSampleData (0);
	float *in2 = buffer->getSampleData (1);
	float *out1 = out->getSampleData (0);
	float *out2 = out->getSampleData (1);


	float a, b, c, d;
    float i=Pars->getParameter(OverdoseParMan::drive), g=gainer, aa, bb;
    float f=filt, fa=filt1, fb=filt2;
  
	--in1;	
	--in2;
	--out1;
	--out2;
	while(--sampleFrames >= 0)
	{
		a = *++in1;		
		b = *++in2;
		
        aa = (a>0.0f)? (float)sqrt(a) : (float)-sqrt(-a); //overdrive
        bb = (b>0.0f)? (float)sqrt(b) : (float)-sqrt(-b); 

        fa = fa + f * (i*(aa-a) + a - fa);                //filter 
        fb = fb + f * (i*(bb-b) + b - fb);   

        c = fa * g; 
	    d = fb * g;

        *++out1 = c;	
		*++out2 = d;
	}

    if(fabs(fa)>1.0e-10) filt1 = fa; else filt1 = 0.0f; //catch denormals
    if(fabs(fb)>1.0e-10) filt2 = fb; else filt2 = 0.0f;
}

void OverdosePlugin::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{	int blockSamples = buffer.getNumSamples();

	overdose(inputBuffer, outputBuffer, blockSamples);

	setMagnus(outputBuffer->getMagnitude(0, buffer.getNumSamples()));
}

//==============================================================================
AudioProcessorEditor* OverdosePlugin::createEditor()
{
    return new OverdoseEditor (this);
}

//==============================================================================
void OverdosePlugin::getStateInformation (MemoryBlock& destData)
{
    // you can store your parameters as binary data if you want to or if you've got
    // a load of binary to put in there, but if you're not doing anything too heavy,
    // XML is a much cleaner way of doing it - here's an example of how to store your
    // params as XML..

    // create an outer XML element..
    XmlElement xmlState (T("MYPLUGINSETTINGS"));

    // add some attributes to it..
    xmlState.setAttribute (T("pluginVersion"), 1);

	xmlState.setAttribute (T("drive"), getParameter(OverdoseParMan::drive));
	xmlState.setAttribute (T("muffle"), getParameter(OverdoseParMan::muffle));
	xmlState.setAttribute (T("output"), getParameter(OverdoseParMan::output));


    // then use this helper function to stuff it into the binary blob and return it..
    copyXmlToBinary (xmlState, destData);
}

void OverdosePlugin::setStateInformation (const void* data, int sizeInBytes)
{
    // use this helper function to get the XML from this binary blob..
    XmlElement* const xmlState = getXmlFromBinary (data, sizeInBytes);

    if (xmlState != 0)
    {
        // check that it's the right type of xml..
        if (xmlState->hasTagName (T("MYPLUGINSETTINGS")))
        {

			setParameter(OverdoseParMan::drive,(float) xmlState->getDoubleAttribute (T("drive"), 
				getParameter(OverdoseParMan::drive)));
			setParameter(OverdoseParMan::muffle,(float) xmlState->getDoubleAttribute (T("muffle"), 
				getParameter(OverdoseParMan::muffle)));
			setParameter(OverdoseParMan::output,(float) xmlState->getDoubleAttribute (T("output"), 
				getParameter(OverdoseParMan::output)));



           sendChangeMessage (this);
        }

        delete xmlState;
    }
}

