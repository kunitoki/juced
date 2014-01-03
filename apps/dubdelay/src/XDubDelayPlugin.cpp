/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004 by Julian Storer.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the
   GNU General Public License, as published by the Free Software Foundation;
   either version 2 of the License, or (at your option) any later version.

   JUCE is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with JUCE; if not, visit www.gnu.org/licenses or write to the
   Free Software Foundation, Inc., 59 Temple Place, Suite 330,
   Boston, MA 02111-1307 USA

  ------------------------------------------------------------------------------

   If you'd like to release a closed-source product which uses JUCE, commercial
   licenses are also available: visit www.rawmaterialsoftware.com/juce for
   more information.

  ==============================================================================
*/

#include "XDubDelayPlugin.h"
#include "XDubDelayComponent.h"

#define PREG(n,p)           registerParameter ((int)n, &p);

//==============================================================================
int XDubDelayPlugin::numInstances = 0;

//==============================================================================
XDubDelayPlugin::XDubDelayPlugin()
{
    size = 323766; //705600; //95998; //32766;  //set max delay time at max sample rate
	buffer = new float[size + 2]; //spare just in case!
    ipos = 0;
    fil0 = 0.0f;
    env  = 0.0f;
    phi  = 0.0f;
    dlbuf= 0.0f;
    sr   = 44100.0f;

    setNumParameters((int)NUM_PARAMETERS);

    // DELAY
    PREG (PAR_DELAY, params[PAR_DELAY].id (PAR_DELAY).name (T("Delay")).unit (T("ms"))
                                  .set (MakeDelegate (this, &XDubDelayPlugin::setDelay))
                                  .get (MakeDelegate (this, &XDubDelayPlugin::getDelay)));

    // FEEDBACK
    PREG (PAR_FEEDBACK, params[PAR_FEEDBACK].id (PAR_FEEDBACK).name (T("Feedback")).unit (T("Sat<>Lim"))
                                  .set (MakeDelegate (this, &XDubDelayPlugin::setFeedback))
                                  .get (MakeDelegate (this, &XDubDelayPlugin::getFeedback)));

    // TONE
    PREG (PAR_TONE, params[PAR_TONE].id (PAR_TONE).name (T("Tone")).unit (T("Lo <> Hi"))
                                  .set (MakeDelegate (this, &XDubDelayPlugin::setTone))
                                  .get (MakeDelegate (this, &XDubDelayPlugin::getTone)));

    // LFODEPTH
    PREG (PAR_LFODEPTH, params[PAR_LFODEPTH].id (PAR_LFODEPTH).name (T("LfoDepth")).unit (T("%"))
                                  .set (MakeDelegate (this, &XDubDelayPlugin::setLfoDepth))
                                  .get (MakeDelegate (this, &XDubDelayPlugin::getLfoDepth)));

    // LFOSPEED
    PREG (PAR_LFOSPEED, params[PAR_LFOSPEED].id (PAR_LFOSPEED).name (T("LfoSpeed")).unit (T("sec."))
                                  .set (MakeDelegate (this, &XDubDelayPlugin::setLfoSpeed))
                                  .get (MakeDelegate (this, &XDubDelayPlugin::getLfoSpeed)));

    // DRYWET
    PREG (PAR_DRYWET, params[PAR_DRYWET].id (PAR_DRYWET).name (T("Dry/Wet")).unit (T("%"))
                                  .set (MakeDelegate (this, &XDubDelayPlugin::setDryWet))
                                  .get (MakeDelegate (this, &XDubDelayPlugin::getDryWet)));

    // OUTPUT
    PREG (PAR_OUTPUT, params[PAR_OUTPUT].id (PAR_OUTPUT).name (T("Output")).unit (T("dB"))
                                  .set (MakeDelegate (this, &XDubDelayPlugin::setOutput))
                                  .get (MakeDelegate (this, &XDubDelayPlugin::getOutput)));


    // initialise effect section
    initialiseToDefault ();
}

XDubDelayPlugin::~XDubDelayPlugin()
{
    if(buffer) delete [] buffer;
}

//==============================================================================
void XDubDelayPlugin::initialiseToDefault ()
{
    // Set default params
    setParameter (PAR_DELAY,    0.30f); 
    setParameter (PAR_FEEDBACK, 0.70f); 
    setParameter (PAR_TONE,     0.30f); 
    setParameter (PAR_LFODEPTH, 0.00f); 
    setParameter (PAR_LFOSPEED, 0.50f); 
    setParameter (PAR_DRYWET,   0.33f); 
    setParameter (PAR_OUTPUT,   0.50f); 

    memset (buffer, 0, size * sizeof(float));
}

//==============================================================================
float XDubDelayPlugin::getDelay (int n)
{
    return fParam0;
}

void XDubDelayPlugin::setDelay (int n, float value)
{
    fParam0 = value;
    
    del = fParam0 * fParam0 * (float)size;
    mod = 0.049f * fParam3 * del;
}

//==============================================================================
float XDubDelayPlugin::getFeedback (int n)
{
    return fParam1;
}

void XDubDelayPlugin::setFeedback (int n, float value)
{
    fParam1 = value;

    fbk = (float)fabs(2.2f * fParam1 - 1.1f);
    if (fParam1>0.5f) rel=0.9997f; else rel=0.8f; //limit or clip
}

//==============================================================================
float XDubDelayPlugin::getTone (int n)
{
    return fParam2;
}

void XDubDelayPlugin::setTone (int n, float value)
{
    fParam2 = value;

    fil = fParam2;
    if(fParam2>0.5f)  //simultaneously change crossover frequency & high/low mix
    {
        fil = 0.5f * fil - 0.25f; 
        lmix = -2.0f * fil;
        hmix = 1.0f;
    }
    else 
    { 
        hmix = 2.0f * fil; 
        lmix = 1.0f - hmix;
    }
    fil = (float)exp(-6.2831853f * pow(10.0f, 2.2f + 4.5f * fil) / sr);
}

//==============================================================================
float XDubDelayPlugin::getLfoDepth (int n)
{
    return fParam3;
}

void XDubDelayPlugin::setLfoDepth (int n, float value)
{
    fParam3 = value;

    mod = 0.049f * fParam3 * del;
}

//==============================================================================
float XDubDelayPlugin::getLfoSpeed (int n)
{
    return fParam4;
}

void XDubDelayPlugin::setLfoSpeed (int n, float value)
{
    fParam4 = value;

    dphi = 628.31853f * (float)pow(10.0f, 3.0f * fParam4 - 2.0f) / sr; //100-sample steps
}

//==============================================================================
float XDubDelayPlugin::getDryWet (int n)
{
    return fParam5;
}

void XDubDelayPlugin::setDryWet (int n, float value)
{
    fParam5 = value;

    wet = 1.0f - fParam5;
    wet = fParam6 * (1.0f - wet * wet); //-3dB at 50% mix
    dry = fParam6 * 2.0f * (1.0f - fParam5 * fParam5);
}

//==============================================================================
float XDubDelayPlugin::getOutput (int n)
{
    return fParam6;
}

void XDubDelayPlugin::setOutput (int n, float value)
{
    fParam6 = value;

    wet = 1.0f - fParam5;
    wet = fParam6 * (1.0f - wet * wet); //-3dB at 50% mix
    dry = fParam6 * 2.0f * (1.0f - fParam5 * fParam5);
}

//==============================================================================
void XDubDelayPlugin::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    memset (buffer, 0, size * sizeof(float));
    
    sr = sampleRate;
}

void XDubDelayPlugin::releaseResources()
{
}

void XDubDelayPlugin::processBlock (AudioSampleBuffer& sampleBuffer,
                                    MidiBuffer& midiMessages)
{
    // overall samples to process    
    int sampleFrames = sampleBuffer.getNumSamples();

    // process incoming midi
    midiAutomatorManager.handleMidiMessageBuffer (midiMessages);

	float *in1 = sampleBuffer.getSampleData (0);
	float *in2 = sampleBuffer.getSampleData (1);
	float *out1 = sampleBuffer.getSampleData (0);
	float *out2 = sampleBuffer.getSampleData (1);

	float a, b, ol, w=wet, y=dry, fb=fbk, dl=dlbuf, db=dlbuf, ddl=0.0f;
    float lx=lmix, hx=hmix, f=fil, f0=fil0, tmp;
    float e=env, g, r=rel; //limiter envelope, gain, release
    float twopi=6.2831853f;
    long  i=ipos, l, s=size, k=0;

	--in1;	
	--in2;	
	--out1;
	--out2;

    while(--sampleFrames >= 0)
	{
		a = *++in1;
        b = *++in2;

        if(k==0) //update delay length at slower rate (could be improved!)
        {
          db += 0.01f * (del - db - mod - mod * (float)sin(phi)); //smoothed delay+lfo
          ddl = 0.01f * (db - dl); //linear step
          phi+=dphi; if(phi>twopi) phi-=twopi;
          k=100;
        }
        k--;
        dl += ddl; //lin interp between points
     
        i--; if(i<0) i=s;                         //delay positions
        
        l = (long)dl;
        tmp = dl - (float)l; //remainder
        l += i; if(l>s) l-=(s+1);
        
        ol = *(buffer + l);                       //delay output
        
        l++; if(l>s) l=0; 
        ol += tmp * (*(buffer + l) - ol); //lin interp

        tmp = a + fb * ol;                        //mix input (left only!) & feedback

        f0 = f * (f0 - tmp) + tmp;                //low-pass filter
        tmp = lx * f0 + hx * tmp;
        
        g =(tmp<0.0f)? -tmp : tmp;                //simple limiter
        e *= r; if(g>e) e = g;
        if(e>1.0f) tmp /= e;

        *(buffer + i) = tmp;                      //delay input
        
        ol *= w;                                  //wet

        *++out1 = y * a + ol;                     //dry
		*++out2 = y * b + ol; 
	}
    
    ipos = i;
    dlbuf = dl;
  
    if(fabs(f0)<1.0e-10) { fil0=0.0f; env=0.0f; } else { fil0=f0; env=e; } //trap denormals
}


//==============================================================================
void XDubDelayPlugin::getStateInformation (MemoryBlock& destData)
{
#ifndef JUCE_DEBUG
    try
    {
#endif

        XmlElement xml ("main");
        // xml.setAttribute (T("version"), JucePlugin_VersionCode);

        for (int i = 0; i < getNumParameters (); i++)
        {
            XmlElement* e = new XmlElement (T("p"));
            e->setAttribute (T("key"), i);
            e->setAttribute (T("value"), (double) getParameter (i));
            xml.addChildElement (e);
        }

        String xmlString = xml.createDocument (String::empty);
        destData.append ((const char*) xmlString, xmlString.length());

#ifndef JUCE_DEBUG
    }
    catch (...)
    {
        AlertWindow::showMessageBox (AlertWindow::WarningIcon,
                                     T("Error !"),
                                     T("Something bad occurred while saving presets data !"));
    }
#endif
}

void XDubDelayPlugin::setStateInformation (const void* data, int sizeInBytes)
{
    suspendProcessing (true);

#ifndef JUCE_DEBUG
    try
    {
#endif
        if (data && sizeInBytes > 0)
        {
            XmlDocument xmlDoc ((char*) data);
            XmlElement* xml = xmlDoc.getDocumentElement();

            if (xml == 0 || ! xml->hasTagName (T("main")))
            {
                String errString = xmlDoc.getLastParseError();
                printf ("Error restoring preset: %s \n", (const char*) errString);
            }
            else
            {
                forEachXmlChildElement (*xml, e)
                {
                    int key = e->getIntAttribute (T("key"), -1);
                    double value = e->getDoubleAttribute (T("value"), 0.0f);
                    
                    if (key >= 0 && key < getNumParameters ())
                        setParameter (key, (float) value);
                }

                delete xml;
            }

            sendChangeMessage (this);
        }
#ifndef JUCE_DEBUG
    }
    catch (...)
    {
        AlertWindow::showMessageBox (AlertWindow::WarningIcon,
                                     T("Error !"),
                                     T("Something bad occurred while restoring presets data !"));
    }
#endif

    suspendProcessing (false);
}

//==============================================================================
XDubDelayComponent* XDubDelayPlugin::getEditor()
{
    return (XDubDelayComponent*) getActiveEditor();
}

AudioProcessorEditor* XDubDelayPlugin::createEditor()
{
    return new XDubDelayComponent (this);
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter (const String& createArgs)
{
    return new XDubDelayPlugin();
}

