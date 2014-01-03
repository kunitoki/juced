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

#include "XAnalyzerPlugin.h"
#include "XAnalyzerComponent.h"

//==============================================================================
int XAnalyzerPlugin::numInstances = 0;

//==============================================================================
XAnalyzerPlugin::XAnalyzerPlugin()
  : _inputA (-1),
    _inputB (-1),
    _dataA (0),
    _dataB (0),
    _frand (0),
    _out1 (0),
    _out2 (0)
{
    DBG ("XAnalyzerPlugin::XAnalyzerPlugin");

    int   i;
    float s;

    _rngen.init (0);
    _frand = new float [LRAND];
    s = 0.0f;

    for (i = 0; i < LRAND; i++)
        s += _frand [i] = 0.5f * _rngen.grandf (); 
    s /= LRAND;

    for (i = 0; i < LRAND; i++)
        _frand [i] -= s;
    _b0 = _b1 = _b2 = _b3 = _b4 = _b5 = _b6 = 0.0f;

    // initialize parameters
    setNumParameters (NUM_PARAMETERS);

    registerParameter (PAR_GAIN, &params[PAR_GAIN].name (T("Gain")).unit (T("%"))
                                 .set (MakeDelegate (this, &XAnalyzerPlugin::setGain))
                                 .get (MakeDelegate (this, &XAnalyzerPlugin::getGain)));

    // initialise effect section
    initialiseToDefault ();
}

XAnalyzerPlugin::~XAnalyzerPlugin()
{
    DBG ("XAnalyzerPlugin::~XAnalyzerPlugin");

    delete[] _frand;
    delete[] _out1;
    delete[] _out2;
}

//==============================================================================
float XAnalyzerPlugin::getGain (int n) { return 0.0f; }
void XAnalyzerPlugin::setGain (int n, float value) { }

//==============================================================================
void XAnalyzerPlugin::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    DBG ("XAnalyzerPlugin::prepareToPlay");

    _fsamp = sampleRate;
    _fsize = samplesPerBlock;
    _dind  = 0;
    _scnt  = 0;
}

void XAnalyzerPlugin::releaseResources()
{
    DBG ("XAnalyzerPlugin::releaseResources");
}

void XAnalyzerPlugin::processBlock (AudioSampleBuffer& buffer,
                                    MidiBuffer& midiMessages)
{
    // process incoming midi
    midiAutomatorManager.handleMidiMessageBuffer (midiMessages);

    // overall samples to process    
    unsigned int nframes = buffer.getNumSamples();

#if 0
    generateNoise (nframes, 
                   buffer.getSampleData (0),
                   buffer.getSampleData (1));
#endif

    unsigned int  m, n;
    float  *pA, *pB;

    if (_dataA)
    {
        pA = (_inputA >= 0) ? buffer.getSampleData (0) : 0;
        pB = (_inputB >= 0) ? buffer.getSampleData (1) : 0;

    	m = nframes;
        n = _size - _dind;

        if (m >= n)
	    {
            if (pA) memcpy (_dataA + _dind, pA, sizeof(float) * n);
	        else    memset (_dataA + _dind, 0,  sizeof(float) * n);

            if (pB) memcpy (_dataB + _dind, pB, sizeof(float) * n);
	        else    memset (_dataB + _dind, 0,  sizeof(float) * n);

            m -= n;
            pA += n;
            pB += n;
            _dind = 0;
        }

        if (m)
	    {
            if (pA) memcpy (_dataA + _dind, pA, sizeof(float) * m);
	        else    memset (_dataA + _dind, 0,  sizeof(float) * m);

            if (pB) memcpy (_dataB + _dind, pB, sizeof(float) * m);
	        else    memset (_dataB + _dind, 0,  sizeof(float) * m);

            _dind += m;
    	}
        _scnt += nframes;
    }

    if (_dataA)
    {
        int k = _scnt / _step;
        if (k) _scnt -= k * _step;
    }
    
    buffer.clear ();
}

void XAnalyzerPlugin::setDataBuffer (float* a, float* b, int ipsize, int ipstep)
{
    suspendProcessing (true);

    _dataA = a;
    _dataB = b;
    
    _inputA = a != 0;
    _inputB = b != 0;

    _size  = ipsize;
    _step  = ipstep; 
    _dind  = 0;
    _scnt  = 0;

    suspendProcessing (false);
}

void XAnalyzerPlugin::generateNoise (int n, float *op1, float *op2)
{
    float x;

    while (n--)
    {
        x  = _frand [_rngen.irand () & MRAND]
           + _frand [_rngen.irand () & MRAND]
           + _frand [_rngen.irand () & MRAND]
           + _frand [_rngen.irand () & MRAND];

	    *op1++ = 0.07071f * x;       	   
            x *= 0.023f;
            _b0 = 0.99886f * _b0 + 0.0555179f * x;
            _b1 = 0.99332f * _b1 + 0.0750759f * x;
            _b2 = 0.96900f * _b2 + 0.1538520f * x;
            _b3 = 0.86650f * _b3 + 0.3104856f * x;
            _b4 = 0.55000f * _b4 + 0.5329522f * x;
            _b5 = -0.7616f * _b5 - 0.0168980f * x;
            *op2++ = _b0 + _b1 + _b2 + _b3 + _b4 + _b5 + _b6 + x * 0.5362f;
            _b6 = x * 0.115926f;
    }
}


//==============================================================================
void XAnalyzerPlugin::getStateInformation (MemoryBlock& destData)
{
    DBG ("XAnalyzerPlugin::getStateInformation");

    try
    {
        MemoryBlock tempBlock;
        XmlElement xml ("main");

        String xmlString = xml.createDocument (String::empty);
        destData.append ((const char*) xmlString, xmlString.length());
    }
    catch (...)
    {
        AlertWindow::showMessageBox (AlertWindow::WarningIcon,
                                     T("Error !"),
                                     T("Something bad occurred while saving presets data !"));
    }
}

void XAnalyzerPlugin::setStateInformation (const void* data, int sizeInBytes)
{
    DBG ("XAnalyzerPlugin::setStateInformation");

    suspendProcessing (true);

    try
    {
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
                delete xml;
            }

            sendChangeMessage (this);
        }
    }
    catch (...)
    {
        AlertWindow::showMessageBox (AlertWindow::WarningIcon,
                                     T("Error !"),
                                     T("Something bad occurred while restoring presets data !"));
    }

    suspendProcessing (false);
}

//==============================================================================
void XAnalyzerPlugin::initialiseToDefault ()
{
}


//==============================================================================
XAnalyzerComponent* XAnalyzerPlugin::getEditor()
{
    return (XAnalyzerComponent*) getActiveEditor();
}

AudioProcessorEditor* XAnalyzerPlugin::createEditor()
{
    return new XAnalyzerComponent (this);
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter (const String& createArgs)
{
    return new XAnalyzerPlugin();
}

