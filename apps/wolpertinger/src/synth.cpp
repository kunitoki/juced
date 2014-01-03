#include "synth.h"
#include "editor.h"


AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new wolp();
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter(const String& commandLine)
{
    return new wolp();
}


// ------------------------- SynthVoice -------------------------

void wolpVoice::startNote(const int midiNoteNumber,
							 const float velocity,
							 SynthesiserSound* sound,
							 const int currentPitchWheelPosition)
{
	phase= low= band= high= 0;
	freq= synth->getnotefreq(midiNoteNumber);
	vol= velocity;
	curvol= 0.0f;
	cyclecount= 0;
	playing= true;
}

void wolpVoice::stopNote(const bool allowTailOff)
{
	if(!allowTailOff) clearCurrentNote();
	playing= false;
	vol= 0;
}



void wolpVoice::process(float* p1, float* p2, int samples)
{
	float cutoff= synth->getparam(wolp::cutoff) * freq;
	float step= freq / getSampleRate();
	float vol= this->vol * synth->getparam(wolp::gain);
	int nfilters= int(synth->getparam(wolp::nfilters));

	float msaw= synth->getparam(wolp::gsaw),
		  mrect= synth->getparam(wolp::grect),
		  mtri= synth->getparam(wolp::gtri);
	float div= msaw+mrect+mtri;
	if(div==0.0f) msaw= div= 1.0;
	div= 1.0/div;
	msaw*= div;
	mrect*= div;
	mtri*= div;

	double volstep= playing? (vol>curvol? 100: -100)*vol/getSampleRate(): -50.0/getSampleRate();

	for(int i= 0; i<samples; i++)
	{
		double vsaw= phase,
			   vrect= (phase<0.5? -1: 1),
			   vtri= (cyclecount&1? 2-(phase+1)-1: phase);

		double val= vsaw*msaw + vrect*mrect + vtri*mtri;

		phase+= step;
		if (phase > 1)
			cyclecount++,
			phase -= 2;

		val= filter.run(val, nfilters);

		curvol+= volstep;
		if(curvol<=0.0f) { clearCurrentNote(); curvol= 0; break; }
		if( (curvol>vol && volstep>0) || (curvol<vol && volstep<0) ) curvol= vol;

//		curvol+= (vol-curvol)*1000.0/getSampleRate();
//		if(curvol<0.001f && !playing) { clearCurrentNote(); curvol= 0; break; }


		p1[i]+= val*curvol;
		p2[i]+= val*curvol;

		if( !((++synth->samples_synthesized) & 31) )
		{
			synth->cutoff_filter.setparams(synth->getparam(wolp::velocity) * 10000,
										   synth->getparam(wolp::inertia) * 100);

			float cut= synth->cutoff_filter.run(cutoff, this->vol * 32.0f/getSampleRate());
			filter.setparams(getSampleRate(), cut,
							 synth->params[wolp::bandwidth]*cut, synth->params[wolp::resonance] * 2);

			synth->setParameterNotifyingHost(wolp::curcutoff, sqrt(cut/20000));
            synth->sendChangeMessage((void*)wolp::curcutoff);
		}
	}
}

void wolpVoice::renderNextBlock (AudioSampleBuffer& outputBuffer, int startSample, int numSamples)
{
	if(getCurrentlyPlayingNote()>=0)
	{
		float **outbuf= outputBuffer.getArrayOfChannels();
		process(outbuf[0]+startSample, outbuf[1]+startSample, numSamples);
	}
}




// ------------------------- Synth -------------------------

void wolp::getStateInformation (JUCE_NAMESPACE::MemoryBlock& destData)
{
	XmlElement *doc= new XmlElement(String("synth"));
	for(int i= 0; i<param_size; i++)
	{
		XmlElement *p= new XmlElement("param");
		p->setAttribute(T("name"), String(paraminfos[i].internalname));
		p->setAttribute(T("val"), params[i]);
		doc->addChildElement(p);
	}
	copyXmlToBinary(*doc, destData);
	delete doc;
}

void wolp::setStateInformation (const void* data, int sizeInBytes)
{
	XmlElement *xml= getXmlFromBinary(data, sizeInBytes);
	String errorstring;

	if(xml && xml->getTagName() == String("synth"))
	{
		forEachXmlChildElementWithTagName(*xml, param, T("param"))
		{
			const char *name= param->getStringAttribute(T("name")).toUTF8();
			const double val= param->getDoubleAttribute(T("val"));
			int i;
			for(i= 0; i<param_size; i++)
			{
				if( !strcmp(name, paraminfos[i].internalname) )
				{
					params[i]= val;
					break;
				}
			}
			if(i==param_size) errorstring+= String("Unknown parameter ") + name + "\n";
		}
	}
	else errorstring= T("XML data corrupt\n");

	if(errorstring.length())
		AlertWindow::showMessageBox(AlertWindow::WarningIcon, String("Synth2"), errorstring);

	if(xml) delete xml;
}



float wolp::getparam(int idx)
{
	float v;
	switch(idx)
	{
		case gain:
			v= sqr(sqr(params[idx]));
			break;
		case clip:
			v= sqr(params[idx]);
			break;
		case gsaw:
		case grect:
		case gtri:
			v= sqr(params[idx]);
			break;
		case cutoff:
			v= sqr(params[idx]);
			break;
		case velocity:
		case inertia:
			v= sqr(params[idx]);
			break;
		case nfilters:
			return float(int(params[idx]*paraminfos[idx].max));
		case tune:
		{
			float p= params[idx]-0.5;
			return 440.0f + (p<0? -sqr(p)*220: sqr(p)*440);
		}
		case curcutoff:
			v= sqr(params[idx]);
			break;
		default:
			v= params[idx];
			break;
	}

	const wolp::paraminfo &i= paraminfos[idx];
	return v * (i.max-i.min); // + i.min;
}


const wolp::paraminfo wolp::paraminfos[]=
{
	{ "gain", 				"Gain",		 	0.0,	4.0,	0.3 },
	{ "clip", 				"Clip",		 	0.0,	5.0,	1.0 },
	{ "saw", 				"Saw",		 	0.0,	1.0,	1.0 },
	{ "rect", 				"Rect",		 	0.0,	1.0,	0.0 },
	{ "tri", 				"Tri",		 	0.0,	1.0,	0.0 },
	{ "tune", 				"Tune",		 	0.0, 	1.0,	0.5 },
	{ "filter_cutoff", 		"Filter X",	 	0.0, 	32.0,	0.5 },
	{ "filter_reso", 		"Resonance",	0.0,	1.0,	0.4 },
	{ "filter_bandwidth", 	"Bandwidth",	0.0,	1.0,	0.4 },
	{ "filter_velocity", 	"Velocity",	 	0.0,	1.0,	0.25 },
	{ "filter_inertia", 	"Inertia",	 	0.0,	1.0,	0.25 },
	{ "filter_passes", 		"Passes",	 	0.0,	8.0,	0.5 },
	{ "filter_curcutoff", 	"Filter Freq",	0.0,	20000,	0.25 },
};


wolp::wolp()
{
	jassert(sizeof(paraminfos)/sizeof(paraminfos[0])==param_size);

	for(int i= 0; i<param_size; i++) params[i]= paraminfos[i].defval;
	samples_synthesized= 0;

	for(int i= 0; i<8 ; i++)
		addVoice(new wolpVoice(this));

	addSound(new wolpSound());

	setNoteStealingEnabled(true);
}

wolp::~wolp()
{
}


void wolp::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	float **outbuf= buffer.getArrayOfChannels();
	int size= buffer.getNumSamples();

	memset(outbuf[0], 0, size*sizeof(float));
	memset(outbuf[1], 0, size*sizeof(float));

	renderNextBlock(buffer, midiMessages, 0, size);

	float clp= getparam(clip);
	float *out0= outbuf[0], *out1= outbuf[1];
	for(int i= 0; i<size; i++)
	{
		if(out0[i]<-clp) out0[i]= -clp; else if(out0[i]>clp) out0[i]= clp;
		if(out1[i]<-clp) out1[i]= -clp; else if(out1[i]>clp) out1[i]= clp;
	}

    editor *e= (editor*)getActiveEditor();
//    if(e) e->updateparams();
}


void wolp::renderNextBlock (AudioSampleBuffer& outputBuffer,
                                   const MidiBuffer& midiData,
                                   int startSample,
                                   int numSamples)
{
    const ScopedLock sl (lock);

    MidiBuffer::Iterator midiIterator (midiData);
    midiIterator.setNextSamplePosition (startSample);
    MidiMessage m (0xf4, 0.0);

    while (numSamples > 0)
    {
        int midiEventPos;
        const bool useEvent = midiIterator.getNextEvent (m, midiEventPos)
                                && midiEventPos < startSample + numSamples;

        const int numThisTime = useEvent ? midiEventPos - startSample
                                         : numSamples;

        if (numThisTime > 0)
        {
            for (int i = voices.size(); --i >= 0;)
                voices.getUnchecked (i)->renderNextBlock (outputBuffer, startSample, numThisTime);
        }

        if (useEvent)
        {
            if (m.isNoteOn())
            {
                const int channel = m.getChannel();

                noteOn (channel,
                        m.getNoteNumber(),
                        m.getFloatVelocity());
            }
            else if (m.isNoteOff())
            {
                noteOff (m.getChannel(),
                         m.getNoteNumber(),
                         true);
            }
            else if (m.isAllNotesOff() || m.isAllSoundOff())
            {
                allNotesOff (m.getChannel(), true);
            }
            else if (m.isPitchWheel())
            {
                const int channel = m.getChannel();
                const int wheelPos = m.getPitchWheelValue();
                lastPitchWheelValues [channel - 1] = wheelPos;

                handlePitchWheel (channel, wheelPos);
            }
            else if (m.isController())
            {
                handleController (m.getChannel(),
                                  m.getControllerNumber(),
                                  m.getControllerValue());
                printf("controller: %s\n", MidiMessage::getControllerName(m.getControllerNumber()).toUTF8());
            }
            else if(m.isAftertouch())
            {
				int chan= m.getChannel();
				int note= m.getNoteNumber();
				for(int i= voices.size(); --i>=0; )
				{
					wolpVoice *v= (wolpVoice *)voices.getUnchecked(i);
					if(v->isPlayingChannel(chan) && v->getCurrentlyPlayingNote()==note)
					{
						v->setvolume(m.getAfterTouchValue()*(1.0/0x7F));
					}
				}
            }

            else
                puts("unknown message");
        }

        startSample += numThisTime;
        numSamples -= numThisTime;
    }
}


AudioProcessorEditor* wolp::createEditor()
{
	editor *e= new editor(this);

	return e;
}

