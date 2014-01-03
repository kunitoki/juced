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

#include "XCompPlugin.h"
#include "XCompComponent.h"
#include "XCompGlobals.h"

#define PREG(n,p)  registerParameter((int)n, &p)

//==============================================================================
int SAMPLE_RATE = 44100;
int SOUND_BUFFER_SIZE = 512;

//==============================================================================
int XCompPlugin::numInstances = 0;

//==============================================================================
XCompPlugin::XCompPlugin()
  : inputs (1,1),
    buffers (1,1)
{
    for (int i = 0; i < 3; i++)
    {
        equalizer[i] = new EffectMgr (1, &dummy);
        compressor[i] = new EffectMgr (1, &dummy);
    }

    // GAIN
    PREG((int) PAR_GAIN, params[PAR_GAIN].id (PAR_GAIN).name (T("Gain")).unit (T("%"))
                                  .set (MakeDelegate (this, &XCompPlugin::setGain))
                                  .get (MakeDelegate (this, &XCompPlugin::getGain)));

    // DRY WET
    PREG((int) PAR_DRYWET, params[PAR_DRYWET].id (PAR_DRYWET).name (T("Dry/Wet")).unit (T("%"))
                                    .set (MakeDelegate (this, &XCompPlugin::setDryWet))
                                    .get (MakeDelegate (this, &XCompPlugin::getDryWet)));

    // BW
    PREG((int) PAR_BW, params[PAR_BW].id (PAR_BW).name (T("BW")).unit (T("%"))
                                .set (MakeDelegate (this, &XCompPlugin::setBw))
                                .get (MakeDelegate (this, &XCompPlugin::getBw)));

    // BAND 1 GAIN
    PREG((int) PAR_BAND1GAIN, params[PAR_BAND1GAIN].id (PAR_BAND1GAIN).part (0).name (T("B1 Gain")).unit (T("%"))
                                       .set (MakeDelegate (this, &XCompPlugin::setBandGain))
                                       .get (MakeDelegate (this, &XCompPlugin::getBandGain)));

    PREG((int) PAR_BAND1ATTACK, params[PAR_BAND1ATTACK].id (PAR_BAND1ATTACK).part (0).name (T("B1 Attack")).unit (T("%"))
                                         .set (MakeDelegate (this, &XCompPlugin::setBandAttack))
                                         .get (MakeDelegate (this, &XCompPlugin::getBandAttack)));

    PREG((int) PAR_BAND1RELEASE, params[PAR_BAND1RELEASE].id (PAR_BAND1RELEASE).part (0).name (T("B1 Release")).unit (T("%"))
                                          .set (MakeDelegate (this, &XCompPlugin::setBandRelease))
                                          .get (MakeDelegate (this, &XCompPlugin::getBandRelease)));

    PREG((int) PAR_BAND1THRESOLD, params[PAR_BAND1THRESOLD].id (PAR_BAND1THRESOLD).part (0).name (T("B1 Thresold")).unit (T("%"))
                                           .set (MakeDelegate (this, &XCompPlugin::setBandThresold))
                                           .get (MakeDelegate (this, &XCompPlugin::getBandThresold)));

    PREG((int) PAR_BAND1RATIO, params[PAR_BAND1RATIO].id (PAR_BAND1RATIO).part (0).name (T("B1 Ratio")).unit (T("%"))
                                        .set (MakeDelegate (this, &XCompPlugin::setBandRatio))
                                        .get (MakeDelegate (this, &XCompPlugin::getBandRatio)));

    PREG((int) PAR_BAND1KNEE, params[PAR_BAND1KNEE].id (PAR_BAND1KNEE).part (0).name (T("B1 Knee")).unit (T("%"))
                                       .set (MakeDelegate (this, &XCompPlugin::setBandKnee))
                                       .get (MakeDelegate (this, &XCompPlugin::getBandKnee)));

    PREG((int) PAR_BAND1MAKEUP, params[PAR_BAND1MAKEUP].id (PAR_BAND1MAKEUP).part (0).name (T("B1 Makeup")).unit (T("%"))
                                         .set (MakeDelegate (this, &XCompPlugin::setBandMakeup))
                                         .get (MakeDelegate (this, &XCompPlugin::getBandMakeup)));

    // BAND FREQ SPLIT
    PREG((int) PAR_BAND12SPLIT, params[PAR_BAND12SPLIT].id (PAR_BAND12SPLIT).part (0).name (T("B12 Split")).unit (T("%"))
                                         .set (MakeDelegate (this, &XCompPlugin::setBandFreq))
                                         .get (MakeDelegate (this, &XCompPlugin::getBandFreq)));

    // BAND 2 GAIN
    PREG((int) PAR_BAND2GAIN, params[PAR_BAND2GAIN].id (PAR_BAND2GAIN).part (1).name (T("B2 Gain")).unit (T("%"))
                                       .set (MakeDelegate (this, &XCompPlugin::setBandGain))
                                       .get (MakeDelegate (this, &XCompPlugin::getBandGain)));

    PREG((int) PAR_BAND2ATTACK, params[PAR_BAND2ATTACK].id (PAR_BAND2ATTACK).part (1).name (T("B2 Attack")).unit (T("%"))
                                         .set (MakeDelegate (this, &XCompPlugin::setBandAttack))
                                         .get (MakeDelegate (this, &XCompPlugin::getBandAttack)));

    PREG((int) PAR_BAND2RELEASE, params[PAR_BAND2RELEASE].id (PAR_BAND2RELEASE).part (1).name (T("B2 Release")).unit (T("%"))
                                          .set (MakeDelegate (this, &XCompPlugin::setBandRelease))
                                          .get (MakeDelegate (this, &XCompPlugin::getBandRelease)));

    PREG((int) PAR_BAND2THRESOLD, params[PAR_BAND2THRESOLD].id (PAR_BAND2THRESOLD).part (1).name (T("B2 Thresold")).unit (T("%"))
                                           .set (MakeDelegate (this, &XCompPlugin::setBandThresold))
                                           .get (MakeDelegate (this, &XCompPlugin::getBandThresold)));

    PREG((int) PAR_BAND2RATIO, params[PAR_BAND2RATIO].id (PAR_BAND2RATIO).part (1).name (T("B2 Ratio")).unit (T("%"))
                                        .set (MakeDelegate (this, &XCompPlugin::setBandRatio))
                                        .get (MakeDelegate (this, &XCompPlugin::getBandRatio)));

    PREG((int) PAR_BAND2KNEE, params[PAR_BAND2KNEE].id (PAR_BAND2KNEE).part (1).name (T("B2 Knee")).unit (T("%"))
                                       .set (MakeDelegate (this, &XCompPlugin::setBandKnee))
                                       .get (MakeDelegate (this, &XCompPlugin::getBandKnee)));

    PREG((int) PAR_BAND2MAKEUP, params[PAR_BAND2MAKEUP].id (PAR_BAND2MAKEUP).part (1).name (T("B2 Makeup")).unit (T("%"))
                                         .set (MakeDelegate (this, &XCompPlugin::setBandMakeup))
                                         .get (MakeDelegate (this, &XCompPlugin::getBandMakeup)));

    // BAND FREQ SPLIT
    PREG((int) PAR_BAND23SPLIT, params[PAR_BAND23SPLIT].id (PAR_BAND23SPLIT).part (1).name (T("B23 Split")).unit (T("%"))
                                         .set (MakeDelegate (this, &XCompPlugin::setBandFreq))
                                         .get (MakeDelegate (this, &XCompPlugin::getBandFreq)));

    // BAND 3 GAIN
    PREG((int) PAR_BAND3GAIN, params[PAR_BAND3GAIN].id (PAR_BAND3GAIN).part (2).name (T("B3 Gain")).unit (T("%"))
                                       .set (MakeDelegate (this, &XCompPlugin::setBandGain))
                                       .get (MakeDelegate (this, &XCompPlugin::getBandGain)));

    PREG((int) PAR_BAND3ATTACK, params[PAR_BAND3ATTACK].id (PAR_BAND3ATTACK).part (2).name (T("B3 Attack")).unit (T("%"))
                                         .set (MakeDelegate (this, &XCompPlugin::setBandAttack))
                                         .get (MakeDelegate (this, &XCompPlugin::getBandAttack)));

    PREG((int) PAR_BAND3RELEASE, params[PAR_BAND3RELEASE].id (PAR_BAND3RELEASE).part (2).name (T("B3 Release")).unit (T("%"))
                                          .set (MakeDelegate (this, &XCompPlugin::setBandRelease))
                                          .get (MakeDelegate (this, &XCompPlugin::getBandRelease)));

    PREG((int) PAR_BAND3THRESOLD, params[PAR_BAND3THRESOLD].id (PAR_BAND3THRESOLD).part (2).name (T("B3 Thresold")).unit (T("%"))
                                           .set (MakeDelegate (this, &XCompPlugin::setBandThresold))
                                           .get (MakeDelegate (this, &XCompPlugin::getBandThresold)));

    PREG((int) PAR_BAND3RATIO, params[PAR_BAND3RATIO].id (PAR_BAND3RATIO).part (2).name (T("B3 Ratio")).unit (T("%"))
                                        .set (MakeDelegate (this, &XCompPlugin::setBandRatio))
                                        .get (MakeDelegate (this, &XCompPlugin::getBandRatio)));

    PREG((int) PAR_BAND3KNEE, params[PAR_BAND3KNEE].id (PAR_BAND3KNEE).part (2).name (T("B3 Knee")).unit (T("%"))
                                       .set (MakeDelegate (this, &XCompPlugin::setBandKnee))
                                       .get (MakeDelegate (this, &XCompPlugin::getBandKnee)));

    PREG((int) PAR_BAND3MAKEUP, params[PAR_BAND3MAKEUP].id (PAR_BAND3MAKEUP).part (2).name (T("B3 Makeup")).unit (T("%"))
                                         .set (MakeDelegate (this, &XCompPlugin::setBandMakeup))
                                         .get (MakeDelegate (this, &XCompPlugin::getBandMakeup)));

    // initialise effect section
    initialiseToDefault ();
}

XCompPlugin::~XCompPlugin()
{
    for (int i = 0; i < 3; i++)
    {
        deleteAndZero (equalizer[i]);
        deleteAndZero (compressor[i]);
    }

    if (--XCompPlugin::numInstances == 0)
    {
        delete[] denormalkillbuf;
    }
}

//==============================================================================
float XCompPlugin::getGain (int n)
{
    return outputGain;
}

void XCompPlugin::setGain (int n, float value)
{
    outputGain = value;
}

//==============================================================================
float XCompPlugin::getDryWet (int n)
{
    return outputDryWet;
}

void XCompPlugin::setDryWet (int n, float value)
{
    outputDryWet = value;
}

//==============================================================================
float XCompPlugin::getBw (int n)
{
    return (equalizer[0]->getEffectParameter (0 * 5 + 13) / 127.0f);
}

void XCompPlugin::setBw (int n, float value)
{
    int v = (int) (value * 127.0f);
    equalizer[0]->setEffectParameter ((0 * 5 + 13), v); // bw
    equalizer[1]->setEffectParameter ((0 * 5 + 13), v); // bw
    equalizer[1]->setEffectParameter ((1 * 5 + 13), v); // bw
    equalizer[2]->setEffectParameter ((0 * 5 + 13), v); // bw
}

//==============================================================================
float XCompPlugin::getBandGain (int band)
{
    return equalizer[band]->getEffectParameter (0) / 127.0f;
//    return equalizer[band]->getEffectParameter ((0 * 5 + 12)) / 127.0f;
}

void XCompPlugin::setBandGain (int band, float value)
{
    equalizer[band]->setEffectParameter (0, (int) (value * 127.0f));
//    equalizer[band]->setEffectParameter ((0 * 5 + 12), (int) (value * 127.0f));
//    equalizer[band]->setEffectParameter ((1 * 5 + 12), (int) (value * 127.0f));
}

//==============================================================================
float XCompPlugin::getBandFreq (int band)
{
    if (band == 0)
        return equalizer[0]->getEffectParameter ((0 * 5 + 11)) / 127.0f;
    else if (band == 1)
        return equalizer[2]->getEffectParameter ((0 * 5 + 11)) / 127.0f;
    else
        return 0.0f;
}

void XCompPlugin::setBandFreq (int band, float value)
{
    if (band == 0)
    {
        equalizer[0]->setEffectParameter ((0 * 5 + 11), (int) (value * 127.0f)); // freq
        equalizer[1]->setEffectParameter ((0 * 5 + 11), (int) (value * 127.0f)); // freq
    }
    else if (band == 1)
    {
        equalizer[1]->setEffectParameter ((1 * 5 + 11), (int) (value * 127.0f)); // freq
        equalizer[2]->setEffectParameter ((0 * 5 + 11), (int) (value * 127.0f)); // freq
    }
}

//==============================================================================
float XCompPlugin::getBandBw (int band)
{
    return equalizer[band]->getEffectParameter ((band * 5 + 13)) / 127.0f;
}

void XCompPlugin::setBandBw (int band, float value)
{
    equalizer[band]->setEffectParameter ((band * 5 + 13), (int) (value * 127.0f));
}

//==============================================================================
float XCompPlugin::getBandAttack (int band)
{
    return compressor[band]->getEffectParameter (3) / 127.0f;
}

void XCompPlugin::setBandAttack (int band, float value)
{
    compressor[band]->setEffectParameter (3, (int) (value * 127.0f));
}

//==============================================================================
float XCompPlugin::getBandRelease (int band)
{
    return compressor[band]->getEffectParameter (4) / 127.0f;
}

void XCompPlugin::setBandRelease (int band, float value)
{
    compressor[band]->setEffectParameter (4, (int) (value * 127.0f));
}

//==============================================================================
float XCompPlugin::getBandThresold (int band)
{
    return compressor[band]->getEffectParameter (5) / 127.0f;
}

void XCompPlugin::setBandThresold (int band, float value)
{
    compressor[band]->setEffectParameter (5, (int) (value * 127.0f));
}

//==============================================================================
float XCompPlugin::getBandRatio (int band)
{
    return compressor[band]->getEffectParameter (6) / 127.0f;
}

void XCompPlugin::setBandRatio (int band, float value)
{
    compressor[band]->setEffectParameter (6, (int) (value * 127.0f));
}

//==============================================================================
float XCompPlugin::getBandKnee (int band)
{
    return compressor[band]->getEffectParameter (7) / 127.0f;
}

void XCompPlugin::setBandKnee (int band, float value)
{
    compressor[band]->setEffectParameter (7, (int) (value * 127.0f));
}

//==============================================================================
float XCompPlugin::getBandMakeup (int band)
{
    return compressor[band]->getEffectParameter (8) / 127.0f;
}

void XCompPlugin::setBandMakeup (int band, float value)
{
    compressor[band]->setEffectParameter (8, (int) (value * 127.0f));
}


//==============================================================================
void XCompPlugin::initialiseToDefault ()
{
    outputGain = 1.0f;
    outputDryWet = 1.0f;

    // prepare effect
    int eq, band;

    eq = 0;
    equalizer[eq]->changeEffect (7); // EQ
    equalizer[eq]->setEffectParameter (0, 96);
    {
        band = 0;
        equalizer[eq]->setEffectParameter ((band * 5 + 10), 3);  // lowpass
        equalizer[eq]->setEffectParameter ((band * 5 + 11), 32); // freq
        equalizer[eq]->setEffectParameter ((band * 5 + 12), 64); // gain
        equalizer[eq]->setEffectParameter ((band * 5 + 13), 64); // bw
        equalizer[eq]->setEffectParameter ((band * 5 + 14), 2);  // stages
    }

    eq = 1;
    equalizer[eq]->changeEffect (7); // EQ
    equalizer[eq]->setEffectParameter (0, 96);
    {
        band = 0;
        equalizer[eq]->setEffectParameter ((band * 5 + 10), 4);  // hipass
        equalizer[eq]->setEffectParameter ((band * 5 + 11), 32); // freq
        equalizer[eq]->setEffectParameter ((band * 5 + 12), 64); // gain
        equalizer[eq]->setEffectParameter ((band * 5 + 13), 64); // bw
        equalizer[eq]->setEffectParameter ((band * 5 + 14), 2);  // stages
        band = 1;
        equalizer[eq]->setEffectParameter ((band * 5 + 10), 3);  // lowpass
        equalizer[eq]->setEffectParameter ((band * 5 + 11), 96); // freq
        equalizer[eq]->setEffectParameter ((band * 5 + 12), 64); // gain
        equalizer[eq]->setEffectParameter ((band * 5 + 13), 64); // bw
        equalizer[eq]->setEffectParameter ((band * 5 + 14), 2);  // stages
    }

    eq = 2;
    equalizer[eq]->changeEffect (7); // EQ
    equalizer[eq]->setEffectParameter (0, 96);
    {
        band = 0;
        equalizer[eq]->setEffectParameter ((band * 5 + 10), 4);  // hipass
        equalizer[eq]->setEffectParameter ((band * 5 + 13), 96); // bw
        equalizer[eq]->setEffectParameter ((band * 5 + 11), 96); // freq
        equalizer[eq]->setEffectParameter ((band * 5 + 14), 2);  // stages
    }

    // prepare compressors
    int comp;

    comp = 0;
    compressor[comp]->changeEffect (9); // COMPRESSOR
    {
        compressor[comp]->setEffectParameter (2, 0);   // rms/peak
        compressor[comp]->setEffectParameter (3, 8);   // attack
        compressor[comp]->setEffectParameter (4, 32);  // release
        compressor[comp]->setEffectParameter (5, 80);  // thresold
        compressor[comp]->setEffectParameter (6, 0);   // ratio
        compressor[comp]->setEffectParameter (7, 0);   // knee
        compressor[comp]->setEffectParameter (8, 0);   // makeup
    }

    comp = 1;
    compressor[comp]->changeEffect (9); // COMPRESSOR
    {
        compressor[comp]->setEffectParameter (2, 0);   // rms/peak
        compressor[comp]->setEffectParameter (3, 8);   // attack
        compressor[comp]->setEffectParameter (4, 32);  // release
        compressor[comp]->setEffectParameter (5, 80);  // thresold
        compressor[comp]->setEffectParameter (6, 0);   // ratio
        compressor[comp]->setEffectParameter (7, 0);   // knee
        compressor[comp]->setEffectParameter (8, 0);   // makeup
    }

    comp = 2;
    compressor[comp]->changeEffect (9); // COMPRESSOR
    {
        compressor[comp]->setEffectParameter (2, 0);   // rms/peak
        compressor[comp]->setEffectParameter (3, 8);   // attack
        compressor[comp]->setEffectParameter (4, 32);  // release
        compressor[comp]->setEffectParameter (5, 80);  // thresold
        compressor[comp]->setEffectParameter (6, 0);   // ratio
        compressor[comp]->setEffectParameter (7, 0);   // knee
        compressor[comp]->setEffectParameter (8, 0);   // makeup
    }
}

//==============================================================================
void XCompPlugin::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    SAMPLE_RATE = (int) sampleRate;

    inputs.setSize (6, samplesPerBlock * 2, false, false, false);
    inputs.clear ();

    buffers.setSize (2, samplesPerBlock * 2, false, false, false);
    buffers.clear ();

    for (int i = 3; --i >= 0;)
    {
        equalizer [i]->clean();
        compressor [i]->clean();
    }
}

void XCompPlugin::releaseResources()
{
    for (int i = 3; --i >= 0;)
    {
        equalizer [i]->clean();
        compressor [i]->clean();
    }
}

void XCompPlugin::processBlock (AudioSampleBuffer& buffer,
                                MidiBuffer& midiMessages)
{
//    dummy.enter ();

    // process incoming midi
    midiAutomatorManager.handleMidiMessageBuffer (midiMessages);

    // get samples informations
    int blockSamples = buffer.getNumSamples();

//    float leftRMS = input.getRMSLevel (0, 0, blockSize);
//    float leftRMS = input.getRMSLevel (1, 0, blockSize);
    float* inL = buffer.getSampleData (0);
    float* inR = buffer.getSampleData (1);
    float* outL = buffer.getSampleData (0);
    float* outR = buffer.getSampleData (1);

    // this is needed when using jack buffers directly
    inputs.copyFrom (0, 0, inL, blockSamples);
    inputs.copyFrom (1, 0, inR, blockSamples);
    inputs.copyFrom (2, 0, inL, blockSamples);
    inputs.copyFrom (3, 0, inR, blockSamples);
    inputs.copyFrom (4, 0, inL, blockSamples);
    inputs.copyFrom (5, 0, inR, blockSamples);

    // process equalizers
    equalizer[0]->out (inputs.getSampleData (0, 0),
                       inputs.getSampleData (1, 0),
                       blockSamples);

    equalizer[1]->out (inputs.getSampleData (2, 0),
                       inputs.getSampleData (3, 0),
                       blockSamples);

    equalizer[2]->out (inputs.getSampleData (4, 0),
                       inputs.getSampleData (5, 0),
                       blockSamples);

    // process compressors
    compressor[0]->out (equalizer[0]->efxoutl,
                        equalizer[0]->efxoutr,
                        blockSamples);

    compressor[1]->out (equalizer[1]->efxoutl,
                        equalizer[1]->efxoutr,
                        blockSamples);

    compressor[2]->out (equalizer[2]->efxoutl,
                        equalizer[2]->efxoutr,
                        blockSamples);

    // mixing
    buffers.clear ();

    float* bufferL = buffers.getSampleData (0);
    float* bufferR = buffers.getSampleData (1);

    for (int j = 0; j < 3; j++)
    {
        buffers.addFrom (0, 0, compressor[j]->efxoutl, blockSamples);
        buffers.addFrom (1, 0, compressor[j]->efxoutr, blockSamples);
    }

    // final stage
    if (outputDryWet == 0.0f)
    {
        for (int i = 0; i < blockSamples; i++)
        {
            outL[i] = inL[i] * outputGain;
            outR[i] = inR[i] * outputGain;
        }
    }
    else if (outputDryWet == 1.0f)
    {
        for (int i = 0; i < blockSamples; i++)
        {
            outL[i] = bufferL[i] * outputGain;
            outR[i] = bufferR[i] * outputGain;
        }
    }
    else
    {
        float dw = outputDryWet,
              idw = 1.0f - outputDryWet;

        for (int i = 0; i < blockSamples; i++)
        {
            outL[i] = (bufferL[i] * dw + inL[i] * idw) * outputGain;
            outR[i] = (bufferR[i] * dw + inR[i] * idw) * outputGain;
        }
    }

//    dummy.exit ();
}

//==============================================================================
void XCompPlugin::getStateInformation (MemoryBlock& destData)
{
/*
    try
    {
        MemoryBlock tempBlock;
        XmlElement xml ("main");

        dummy.enter ();
            equalizer[0]->addToXML (&xml);
            equalizer[1]->addToXML (&xml);
            equalizer[2]->addToXML (&xml);
            equalizer[3]->addToXML (&xml);
        dummy.exit ();

        String xmlString = xml.createDocument (String::empty);
        tempBlock.append ((const char*) xmlString, xmlString.length ());

        xmlString = tempBlock.toBase64Encoding ();
        destData.append ((const char*) xmlString, xmlString.length());
    }
    catch (...)
    {
        AlertWindow::showMessageBox (AlertWindow::WarningIcon,
                                     T("Error !"),
                                     T("Something bad occurred while saving presets data !"));
    }
*/
}

void XCompPlugin::setStateInformation (const void* data, int sizeInBytes)
{
/*
    try
    {
        suspendProcessing (true);

        if (data && sizeInBytes > 0)
        {
            MemoryBlock mb;
            mb.fromBase64Encoding (String ((char*) data));

            XmlDocument xmlDoc (mb.toString ());
            XmlElement* xml = xmlDoc.getDocumentElement();

            if (xml == 0 || ! xml->hasTagName (T("main")))
            {
                String errString = xmlDoc.getLastParseError();
                std::cout << (const char*) errString << std::endl;
            }
            else
            {
                dummy.enter ();
                    equalizer[0]->updateFromXML (xml);
                    equalizer[1]->updateFromXML (xml);
                    equalizer[2]->updateFromXML (xml);
                    equalizer[3]->updateFromXML (xml);
                dummy.exit ();

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
    finally
    {
        suspendProcessing (false);
    }
*/
}

//==============================================================================
EffectMgr* XCompPlugin::getEqualizer (const int numBand)
{
    return equalizer [numBand];
}

EffectMgr* XCompPlugin::getCompressor (const int numBand)
{
    return compressor [numBand];
}

XCompComponent* XCompPlugin::getEditor()
{
    return (XCompComponent*) getActiveEditor();
}

AudioProcessorEditor* XCompPlugin::createEditor()
{
    return new XCompComponent (this);
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter (const String& createArgs)
{
    if (XCompPlugin::numInstances++ == 0)
    {
        SAMPLE_RATE = 44100;
        SOUND_BUFFER_SIZE = 4096;

        if (! denormalkillbuf)
            denormalkillbuf = new REALTYPE [SOUND_BUFFER_SIZE];

        for (int i = 0; i < SOUND_BUFFER_SIZE; i++)
            denormalkillbuf[i] = (RND - 0.5) * 1e-16;
    }

    return new XCompPlugin();
}

