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

#include "DetunerPlugin.h"
#include "DetunerEditor.h"


//==============================================================================
DetunerPlugin::DetunerPlugin()
{
	//Create parameter manager
	Pars = new DetunerParMan();

	///initialise...
	buf = new float[BUFMAX];
	win = new float[BUFMAX];
	buflen=0;

	magnus=0;

	cp = 0;
	temppr=1;
	setCurrentProgram(cp);
	

	ProgName[0] = "Phantom";
	ProgName[1] = "Little";
	ProgName[2] = "Heavy";
}

DetunerPlugin::~DetunerPlugin()
{
	 delete Pars;
	 if(buf) delete [] buf;
	 if(win) delete [] win;
}

//==============================================================================
int DetunerPlugin::getNumParameters()
{
	return Pars->getNumPars();
}

float DetunerPlugin::getParameter (int index)
{
	return Pars->getParameter(index);
}

void DetunerPlugin::setParameter (int index, float newValue)
{

	if (Pars->getParameter(index) != newValue) {Pars->setParameter(index,newValue);}

	 //calcs here
	recalc();	
  
}

const String DetunerPlugin::getParameterName (int index)
{
    switch (index)
	{
     case 0: return String("fine");  break;
     case 1: return String("mix");  break;
	 case 2: return String("output");  break;
	 case 3: return String("chunk");  break;
	}

    return String::empty;
}

const String DetunerPlugin::getParameterText (int index)
{  
	return String(Pars->getParameter(index));
}

//==============================================================================
void DetunerPlugin::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // do your pre-playback setup stuff here..
    keyboardState.reset();
	recalc();
	
}

void DetunerPlugin::releaseResources()
{
    memset(buf, 0, BUFMAX * sizeof(float));
    pos0 = 0; pos1 = pos2 = 0.0f;
}
void DetunerPlugin::recalc()
{

	semi = 3.0f * getParameter(0) * getParameter(0) * getParameter(0);
  dpos2 = (float)pow(1.0594631f, semi);
  dpos1 = 1.0f / dpos2;

  wet = (float)pow(10.0f, 2.0f * getParameter(2) - 1.0f);
  dry = wet - wet * getParameter(1) * getParameter(1);
  wet = (wet + wet - wet * getParameter(1)) * getParameter(1);

  int tmp = 1 << (8 + (int)(4.9f * getParameter(3)));

  if(tmp!=buflen) //recalculate crossfade window
  {
    buflen = tmp;
    bufres = 1000.0f * (float)buflen / getSampleRate();

    int i; //hanning half-overlap-and-add
    double p=0.0, dp=6.28318530718/buflen;
    for(i=0;i<buflen;i++) { win[i] = (float)(0.5 - 0.5 * cos(p)); p+=dp; }
  }

}

void DetunerPlugin::detune (AudioSampleBuffer* buffer, AudioSampleBuffer* out, int sampleFrames)
{

  float *in1 = buffer->getSampleData (0);
  float *in2 = buffer->getSampleData (1);
  float *out1 = out->getSampleData (0);
  float *out2 = out->getSampleData (1);
  float a, b, c, d;
  float x, w=wet, y=dry, p1=pos1, p1f, d1=dpos1;
  float                  p2=pos2,      d2=dpos2;
  int  p0=pos0, p1i, p2i;
  int  l=buflen-1, lh=buflen>>1;
  float lf = (float)buflen;

  --in1;
  --in2;
  --out1;
  --out2;
  while(--sampleFrames >= 0)  //had to disable optimization /Og in MSVC++5!
  {
    a = *++in1;
    b = *++in2;

    c = y * a;
    d = y * b;

    --p0 &= l;     
    *(buf + p0) = w * (a + b);      //input

    p1 -= d1;
    if(p1<0.0f) p1 += lf;           //output
    p1i = (int)p1;
    p1f = p1 - (float)p1i;
    a = *(buf + p1i);
    ++p1i &= l;
    a += p1f * (*(buf + p1i) - a);  //linear interpolation

    p2i = (p1i + lh) & l;           //180-degree ouptut
    b = *(buf + p2i);
    ++p2i &= l;
    b += p1f * (*(buf + p2i) - b);  //linear interpolation

    p2i = (p1i - p0) & l;           //crossfade
    x = *(win + p2i);
    //++p2i &= l;
    //x += p1f * (*(win + p2i) - x); //linear interpolation (doesn't do much)
    c += b + x * (a - b);

    p2 -= d2;  //repeat for downwards shift - can't see a more efficient way?
    if(p2<0.0f) p2 += lf;           //output
    p1i = (int)p2;
    p1f = p2 - (float)p1i;
    a = *(buf + p1i);
    ++p1i &= l;
    a += p1f * (*(buf + p1i) - a);  //linear interpolation

    p2i = (p1i + lh) & l;           //180-degree ouptut
    b = *(buf + p2i);
    ++p2i &= l;
    b += p1f * (*(buf + p2i) - b);  //linear interpolation

    p2i = (p1i - p0) & l;           //crossfade
    x = *(win + p2i);
    //++p2i &= l;
    //x += p1f * (*(win + p2i) - x); //linear interpolation (doesn't do much)
    d += b + x * (a - b);

    *++out1 = c;
    *++out2 = d;
  }
  pos0=p0; pos1=p1; pos2=p2;
	

}

void DetunerPlugin::processBlock (AudioSampleBuffer& buffer,
                                   MidiBuffer& midiMessages)
{
	
	int blockSamples = buffer.getNumSamples();
	detune(inputBuffer, outputBuffer, blockSamples);
	
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
AudioProcessorEditor* DetunerPlugin::createEditor()
{
    return new DetunerEditor (this);
}

//==============================================================================
void DetunerPlugin::getStateInformation (MemoryBlock& destData)
{
    // you can store your parameters as binary data if you want to or if you've got
    // a load of binary to put in there, but if you're not doing anything too heavy,
    // XML is a much cleaner way of doing it - here's an example of how to store your
    // params as XML..

    // create an outer XML element..
    XmlElement xmlState (T("DETUNERSETTINGS"));

    // add some attributes to it..
    xmlState.setAttribute (T("pluginVersion"), 1);
  //  xmlState.setAttribute (T("gainLevel"), gain);
	xmlState.setAttribute (T("fine"), getParameter(DetunerParMan::fine));
	xmlState.setAttribute (T("mix"), getParameter(DetunerParMan::mix));
	xmlState.setAttribute (T("output"), getParameter(DetunerParMan::output));
	xmlState.setAttribute (T("chunk"), getParameter(DetunerParMan::chunk));
	xmlState.setAttribute (T("default"), 0);

    // then use this helper function to stuff it into the binary blob and return it..
    copyXmlToBinary (xmlState, destData);
}

void DetunerPlugin::setStateInformation (const void* data, int sizeInBytes)
{
    // use this helper function to get the XML from this binary blob..
    XmlElement* const xmlState = getXmlFromBinary (data, sizeInBytes);

    if (xmlState != 0)
    {
        // check that it's the right type of xml..
        if (xmlState->hasTagName (T("DETUNERSETTINGS")))
        {
			
			setParameter(DetunerParMan::fine,(float) xmlState->getDoubleAttribute (T("fine"), 
				getParameter(DetunerParMan::fine)));
			setParameter(DetunerParMan::mix,(float) xmlState->getDoubleAttribute (T("mix"), 
				getParameter(DetunerParMan::mix)));
			setParameter(DetunerParMan::output,(float) xmlState->getDoubleAttribute (T("output"), 
				getParameter(DetunerParMan::output)));
			setParameter(DetunerParMan::chunk,(float) xmlState->getDoubleAttribute (T("chunk"), 
				getParameter(DetunerParMan::chunk)));
			//temppr = xmlState->getIntAttribute(T("default"));


            sendChangeMessage (this);
        }

        delete xmlState;
    }
	
}
void DetunerPlugin::initToDefault()
{
	Pars->loadPreset(0);
}
void DetunerPlugin::setCurrentProgram(int index)
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

void DetunerPlugin::setMagnus(float val)
{
	magnus = val;
}

float DetunerPlugin::getMagnus()
{
	return magnus;
}
