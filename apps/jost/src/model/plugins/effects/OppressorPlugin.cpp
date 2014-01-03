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

#include "OppressorPlugin.h"
#include "OppressorEditor.h"

//==============================================================================
OppressorPlugin::OppressorPlugin()
{
	// Create parameter manager
	Pars = new OppressorParMan();

	magnus = 0;

	cp = 0;
	temppr=1;
	setCurrentProgram(cp);

	ProgName[0] = "Preset1";
	ProgName[1] = "Preset2";
	ProgName[2] = "Preset3";

}

OppressorPlugin::~OppressorPlugin()
{
	 delete Pars;
}


//==============================================================================
int OppressorPlugin::getNumParameters()
{
	return Pars->getNumPars();
}

float OppressorPlugin::getParameter (int index)
{
	return Pars->getParameter(index);
}

void OppressorPlugin::setParameter (int index, float newValue)
{
	if (Pars->getParameter(index) != newValue) {Pars->setParameter(index,newValue);}

	//calcs here
    mode=0;
    thr = (float)pow(10.f, 2.f * Pars->getParameter(OppressorParMan::thresh) - 2.f);
    rat = 2.5f * Pars->getParameter(OppressorParMan::ratio) - 0.5f; 
    if(rat>1.0) { rat = 1.f + 16.f*(rat-1.f) * (rat - 1.f); mode = 1; }
    if(rat<0.0) { rat = 0.6f*rat; mode=1; }
    trim = (float)pow(10.f, 2.f * Pars->getParameter(OppressorParMan::level)); //was  - 1.f);
    att = (float)pow(10.f, -0.002f - 2.f * Pars->getParameter(OppressorParMan::attack));
    rel = (float)pow(10.f, -2.f - 3.f * Pars->getParameter(OppressorParMan::release));

    if(Pars->getParameter(OppressorParMan::limiter)>0.98)
    {
       lthr = 0.f; //limiter
    }
    else
    {
       lthr = 0.99f*(float)pow(10.0f,int(30.0*Pars->getParameter(OppressorParMan::limiter) - 20.0)/20.f); 
       mode = 1; 
    } 

    if(rat<0.0f && thr<0.1f) rat *= thr*15.f;
}

const String OppressorPlugin::getParameterName (int index)
{
    switch (index){
     case 0: return String("thresh");  break;
     case 1: return String("ratio");  break;
	 case 2: return String("level");  break;
	 case 3: return String("attack");  break;
     case 4: return String("release");  break;
	 case 5: return String("limiter");  break;
	}

    return String::empty;
}

const String OppressorPlugin::getParameterText (int index)
{
    
	return String(Pars->getParameter(index));
}

//==============================================================================
void OppressorPlugin::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // do your pre-playback setup stuff here..
    keyboardState.reset();
}

void OppressorPlugin::releaseResources()
{

}

void OppressorPlugin::oppressor (AudioSampleBuffer* buffer, AudioSampleBuffer* out, int sampleFrames)
{
	float *in1 = buffer->getSampleData (0);
	float *in2 = buffer->getSampleData (1);
	float *out1 = out->getSampleData (0);
	float *out2 = out->getSampleData (1);

	float a, b, i, j, g, e=env, e2=env2, ra=rat, re=(1.f-rel), at=att;
	float tr=trim, th=thr, lth=lthr; // , xth=xthr;  
	
	--in1;	
	--in2;	
	--out1;
	--out2;

	if(mode) //comp/gate/lim
	{
		if(lth==0.f) lth=1000.f;
		while(--sampleFrames >= 0)
		{
			a = *++in1;
			b = *++in2;

			i = (a<0.f)? -a : a;
			j = (b<0.f)? -b : b;
			i = (j>i)? j : i;

			e = (i>e)? e + at * (i - e) : e * re;
			e2 = (i>e)? i : e2 * re; //ir;

			g = (e>th)? tr / (1.f + ra * ((e/th) - 1.f)) : tr;

			if(g<0.f) g=0.f; 
			if(g*e2>lth) g = lth/e2; //limit 

			//  ge = (e>xth)? ge + ga - ga * ge : ge * xrat; //gate

			*++out1 = a * (g);	
			*++out2 = b * (g);	
		}
	}
	else //compressor only
	{
		while(--sampleFrames >= 0)
		{
		a = *++in1;
		b = *++in2;

		i = (a<0.f)? -a : a;
		j = (b<0.f)? -b : b;
		i = (j>i)? j : i; //get peak level

		e = (i>e)? e + at * (i - e) : e * re; //envelope
		g = (e>th)? tr / (1.f + ra * ((e/th) - 1.f)) : tr; //gain

		*++out1 = a * (g); //vca
		*++out2 = b * (g);	
		}
	}

	if(e <1.0e-10) env =0.f; else env =e;
	if(e2<1.0e-10) env2=0.f; else env2=e2;
	// if(ge<1.0e-10) genv=0.f; else genv=ge;
}

void OppressorPlugin::processBlock (AudioSampleBuffer& buffer,
                                    MidiBuffer& midiMessages)
{
	int blockSamples = buffer.getNumSamples();
	oppressor(inputBuffer, outputBuffer, blockSamples);

	setMagnus(outputBuffer->getMagnitude(0, buffer.getNumSamples()));


    // in case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }

    // if any midi messages come in, use them to update the keyboard state object. This
    // object sends notification to the UI component about key up/down changes
    keyboardState.processNextMidiBuffer (midiMessages,
                                         0, buffer.getNumSamples(),
                                         true);

    // have a go at getting the current time from the host, and if it's changed, tell
    // our UI to update itself.
    AudioPlayHead::CurrentPositionInfo pos;

    if (getPlayHead() != 0 && getPlayHead()->getCurrentPosition (pos))
    {
        if (memcmp (&pos, &lastPosInfo, sizeof (pos)) != 0)
        {
            lastPosInfo = pos;
            sendChangeMessage (this);
        }
    }
    else
    {
        zeromem (&lastPosInfo, sizeof (lastPosInfo));
        lastPosInfo.timeSigNumerator = 4;
        lastPosInfo.timeSigDenominator = 4;
        lastPosInfo.bpm = 120;
    }
}

//==============================================================================
AudioProcessorEditor* OppressorPlugin::createEditor()
{
    return new OppressorEditor (this);
}

//==============================================================================
void OppressorPlugin::getStateInformation (MemoryBlock& destData)
{
    
    // create an outer XML element..
    XmlElement xmlState (T("OPPRESSORSETTINGS"));

    // add some attributes to it..
    xmlState.setAttribute (T("pluginVersion"), 1);

	xmlState.setAttribute (T("thresh"), getParameter(OppressorParMan::thresh));
	xmlState.setAttribute (T("ratio"), getParameter(OppressorParMan::ratio));
	xmlState.setAttribute (T("level"), getParameter(OppressorParMan::level));
	xmlState.setAttribute (T("attack"), getParameter(OppressorParMan::attack));
	xmlState.setAttribute (T("release"), getParameter(OppressorParMan::release));
	xmlState.setAttribute (T("limiter"), getParameter(OppressorParMan::limiter));

	xmlState.setAttribute (T("default"), 0);

    // then use this helper function to stuff it into the binary blob and return it..
    copyXmlToBinary (xmlState, destData);
}

void OppressorPlugin::setStateInformation (const void* data, int sizeInBytes)
{
    // use this helper function to get the XML from this binary blob..
    XmlElement* const xmlState = getXmlFromBinary (data, sizeInBytes);

    if (xmlState != 0)
    {
        // check that it's the right type of xml..
        if (xmlState->hasTagName (T("OPPRESSORSETTINGS")))
        {
            // ok, now pull out our parameters..
     //       gain = (float) xmlState->getDoubleAttribute (T("gainLevel"), gain);
			setParameter(OppressorParMan::thresh,(float) xmlState->getDoubleAttribute (T("thresh"), 
				getParameter(OppressorParMan::thresh)));
			setParameter(OppressorParMan::ratio,(float) xmlState->getDoubleAttribute (T("ratio"), 
				getParameter(OppressorParMan::ratio)));
			setParameter(OppressorParMan::level,(float) xmlState->getDoubleAttribute (T("level"), 
				getParameter(OppressorParMan::level)));
			setParameter(OppressorParMan::attack,(float) xmlState->getDoubleAttribute (T("attack"), 
				getParameter(OppressorParMan::attack)));
			setParameter(OppressorParMan::release,(float) xmlState->getDoubleAttribute (T("release"), 
				getParameter(OppressorParMan::release)));
			setParameter(OppressorParMan::limiter,(float) xmlState->getDoubleAttribute (T("limiter"), 
				getParameter(OppressorParMan::limiter)));

            sendChangeMessage (this);
        }

        delete xmlState;
    }
}

void OppressorPlugin::initToDefault()
{
	Pars->loadPreset(0);
}

void OppressorPlugin::setCurrentProgram(int index)
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

void OppressorPlugin::setMagnus(float val)
{
	magnus = val;
}

float OppressorPlugin::getMagnus()
{
	return magnus;
}

