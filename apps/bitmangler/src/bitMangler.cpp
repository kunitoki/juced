#include "bitMangler.h"
#include "bitManglerEditor.h"

AudioProcessor* JUCE_CALLTYPE createPluginFilter (const String& commandLine)
{
    return new DemoJuceFilter();
}

DemoJuceFilter::DemoJuceFilter()
{
    zeromem (&lastPosInfo, sizeof (lastPosInfo));
    lastPosInfo.timeSigNumerator = 4;
    lastPosInfo.timeSigDenominator = 4;
    lastPosInfo.bpm = 120;
	editor = 0;
	processing = true;
	xorProcessing = andProcessing = clearProcessing = setProcessing = false;
	currentSample = 0.0f;
	bufferCycle = 0;
	clearTable();
}

DemoJuceFilter::~DemoJuceFilter()
{
}

const String DemoJuceFilter::getName() const
{
    return "bitMangler";
}

int DemoJuceFilter::getNumParameters()
{
    return (kParams);
}

float DemoJuceFilter::getParameter (int index)
{
	return (0.0);
}

void DemoJuceFilter::setParameter (int index, float newValue)
{
}

const String DemoJuceFilter::getParameterName (int index)
{
	return (String::empty);
}

const String DemoJuceFilter::getParameterText (int index)
{
	return (String::empty);
}

const String DemoJuceFilter::getInputChannelName (const int channelIndex) const
{
    return String (channelIndex + 1);
}

const String DemoJuceFilter::getOutputChannelName (const int channelIndex) const
{
    return String (channelIndex + 1);
}

bool DemoJuceFilter::isInputChannelStereoPair (int index) const
{
    return false;
}

bool DemoJuceFilter::isOutputChannelStereoPair (int index) const
{
    return false;
}

bool DemoJuceFilter::acceptsMidi() const
{
    return false;
}

bool DemoJuceFilter::producesMidi() const
{
    return false;
}

void DemoJuceFilter::prepareToPlay (double sampleRate, int samplesPerBlock)
{
}

void DemoJuceFilter::releaseResources()
{
	clearTable();
}

void DemoJuceFilter::processBlock (AudioSampleBuffer& buffer,
                                   MidiBuffer& midiMessages)
{
	if (!isProcessing())
		return;

	for (int channel = 0; channel < getNumInputChannels(); ++channel)
	{
		float *p = buffer.getSampleData (channel);
		int size = buffer.getNumSamples() / buffer.getNumChannels();

		for (int x=0; x<size; x++)
		{
			currentSample = *(p+x);

			/* conversion */

			*(p+x) = currentConvertedSample = process (*(p+x));

			if (x == 2 && channel == 0 && bufferCycle == 0 && editor)
			{
				sendChangeMessage (0);
			}
		}
	}

	bufferCycle++;

	if (bufferCycle == 20)
		bufferCycle = 0;
}

AudioProcessorEditor* DemoJuceFilter::createEditor()
{
    return (editor = new bitManglerEditor (this));
}

void DemoJuceFilter::getStateInformation (MemoryBlock& destData)
{
    XmlElement xmlState (T("BITMUNGLER"));
    xmlState.setAttribute (T("pluginVersion"), 1);

	xmlState.setAttribute (T("xorBits"), serializeArray (xorBits));
	xmlState.setAttribute (T("xorWith"), xorWith);
	xmlState.setAttribute (T("xorProcessing"), xorProcessing);

	xmlState.setAttribute (T("andBits"), serializeArray (andBits));
	xmlState.setAttribute (T("andWith"), andWith);
	xmlState.setAttribute (T("andProcessing"), andProcessing);

	xmlState.setAttribute (T("clearBits"), serializeArray (clearBits));
	xmlState.setAttribute (T("clearProcessing"), clearProcessing);

	xmlState.setAttribute (T("setBits"), serializeArray (setBits));
	xmlState.setAttribute (T("setProcessing"), setProcessing);

	Logger::writeToLog (xmlState.createDocument (String::empty));

    copyXmlToBinary (xmlState, destData);
}

void DemoJuceFilter::setStateInformation (const void* data, int sizeInBytes)
{
    XmlElement* const xmlState = getXmlFromBinary (data, sizeInBytes);
    if (xmlState != 0)
    {
        if (xmlState->hasTagName (T("BITMUNGLER")))
        {
			Logger::writeToLog (xmlState->createDocument (String::empty));

			xorProcessing = xmlState->getBoolAttribute (T("xorProcessing"));
			andProcessing = xmlState->getBoolAttribute (T("andProcessing"));
			clearProcessing = xmlState->getBoolAttribute (T("clearProcessing"));
			setProcessing = xmlState->getBoolAttribute (T("setProcessing"));

			unserializeArray (xmlState->getStringAttribute (T("xorBits")), xorBits);
			xorWith = xmlState->getBoolAttribute (T("xorWith"));

			unserializeArray (xmlState->getStringAttribute (T("andBits")), andBits);
			andWith = xmlState->getBoolAttribute (T("andWith"));

			unserializeArray (xmlState->getStringAttribute (T("setBits")), setBits);
			unserializeArray (xmlState->getStringAttribute (T("clearBits")), clearBits);
        }
        delete xmlState;
    }

	sendChangeMessage (this);
}

float DemoJuceFilter::getCurrentSample()
{
	return (currentSample);
}

float DemoJuceFilter::getCurrentConvertedSample()
{
	return (currentConvertedSample);
}

void DemoJuceFilter::stopProcessing()
{
	processing = false;
	Logger::writeToLog (T("stopProcessing()"));
}

void DemoJuceFilter::startProcessing()
{
	processing = true;
	Logger::writeToLog (T("startProcessing()"));
}

bool DemoJuceFilter::isProcessing()
{
	return (processing);
}

float DemoJuceFilter::process(float sample)
{
	if (!isProcessing())
	{
		return (sample);
	}

	myFloat.setValue(sample);

	for (int x=0; x<32; x++)
	{
		if (xorBits[x] && xorProcessing)
		{
			myFloat.xorbit (x, xorWith);
		}
		if (andBits[x] && andProcessing)
		{
			myFloat.andbit (x, andWith);
		}
		if (setBits[x] && setProcessing)
		{
			myFloat.setbit (x);
		}
		if (clearBits[x] && clearProcessing)
		{
			myFloat.clearbit (x);
		}

	}

	return (myFloat.getValue());
}

void DemoJuceFilter::setXorBit (int pos, bool bit)
{
	if (pos == 0)
		pos=1;

	xorBits.set (pos-1, true);
	xorWith = bit;
}

void DemoJuceFilter::setAndBit (int pos, bool bit)
{
	if (pos == 0)
		pos=1;

	andBits.set (pos-1, true);
	andWith = bit;
}

void DemoJuceFilter::setClearBit (int pos)
{
	if (pos == 0)
		pos=1;

	clearBits.set (pos-1, true);
}

void DemoJuceFilter::setSetBit (int pos)
{
	if (pos == 0)
		pos=1;

	setBits.set (pos-1, true);
}

void DemoJuceFilter::clearXorTable()
{
	for (int x=0; x<32; x++)
	{
		xorBits.set (x, false);
		xorWith = false;
	}
}

void DemoJuceFilter::clearAndTable()
{
	for (int x=0; x<32; x++)
	{
		andBits.set (x, false);
		andWith = false;
	}
}

void DemoJuceFilter::clearSetTable()
{
	for (int x=0; x<32; x++)
	{
		setBits.set (x, false);
	}
}

void DemoJuceFilter::clearClearTable()
{
	for (int x=0; x<32; x++)
	{
		clearBits.set (x, false);
	}
}

void DemoJuceFilter::clearTable()
{
	for (int x=0; x<32; x++)
	{
		xorBits.set (x, false);
		xorWith = false;
		andBits.set (x, false);
		andWith = false;
		clearBits.set (x, false);
		setBits.set (x, false);
	}
}

void DemoJuceFilter::setProcess (int processDef, bool b)
{
	switch (processDef)
	{
		case bitManglerEditor::XOR:
			xorProcessing = b;
			break;
		
		case bitManglerEditor::AND:
			andProcessing = b;
			break;

		case bitManglerEditor::CLEAR:
			clearProcessing = b;
			break;

		case bitManglerEditor::SET:
			setProcessing = b;
			break;

		default:
			break;
	}
}

String DemoJuceFilter::serializeArray (Array <bool>a)
{
	String str;

	for (int x=0; x<a.size(); x++)
	{
		if (x==0)
			str << a[x];
		else
			str <<T(",")<< a[x];
	}

	return (str);
}

void DemoJuceFilter::unserializeArray (String data, Array <bool>&a)
{
	StringArray ar;
	ar.addTokens (data, T(","), String::empty);

	for (int x=0; x<ar.size(); x++)
	{
		const int k = ar[x].getIntValue();
		bool b;

		if (k == 1)
			b = true;
		else
			b = false;
		
		a.set (x, b);
	}

//	for (int x=0; x<32; x++)
//	{
//		const int k = (int)a[x];
//	}
}

int DemoJuceFilter::getXorFirst()
{
	int x;
//	for (x=0; x<32; x++)
//	{
//		const int k = (int)xorBits[x];
//	}

	for (x=0; x<32; x++)
	{
		if (xorBits[x])
			return (x+1);
	}

	return (0);
}

int DemoJuceFilter::getXorLast()
{
	for (int x=31; x>=0; x--)
	{
		if (xorBits[x])
			return (x+1);
	}

	return (0);
}

int DemoJuceFilter::getAndFirst()
{
	for (int x=0; x<32; x++)
	{
		if (andBits[x])
			return (x+1);
	}

	return (0);
}

int DemoJuceFilter::getAndLast()
{
	for (int x=31; x>=0; x--)
	{
		if (andBits[x])
			return (x+1);
	}

	return (0);
}

int DemoJuceFilter::getClearFirst()
{
	for (int x=0; x<32; x++)
	{
		if (clearBits[x])
			return (x+1);
	}

	return (0);
}

int DemoJuceFilter::getClearLast()
{
	for (int x=31; x>=0; x--)
	{
		if (clearBits[x])
			return (x+1);
	}

	return (0);
}

int DemoJuceFilter::getSetFirst()
{
	for (int x=0; x<32; x++)
	{
		if (setBits[x])
			return (x+1);
	}

	return (0);
}

int DemoJuceFilter::getSetLast()
{
	for (int x=31; x>=0; x--)
	{
		if (setBits[x])
			return (x+1);
	}

	return (0);
}

bool DemoJuceFilter::getXorWith()
{
	return (xorWith);
}

bool DemoJuceFilter::getAndWith()
{
	return (andWith);
}

void DemoJuceFilter::setXorWith(bool b)
{
	xorWith = b;
}

void DemoJuceFilter::setAndWith(bool b)
{
	andWith = b;
}

