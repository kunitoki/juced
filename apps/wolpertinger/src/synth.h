#ifndef SYNTH_H
#define SYNTH_H

#include "StandardHeader.h"
#include "filters.h"


template<typename T> T sqr(T v) { return v*v; }



class wolpSound: public SynthesiserSound
{
	public:
		bool appliesToNote(const int midiNoteNumber) { return true; }
		bool appliesToChannel(const int midiChannel) { return true; }
};

class wolpVoice: public SynthesiserVoice
{
	public:
		wolpVoice(class wolp *s): synth(s)
		{
		}

		//==============================================================================
		bool canPlaySound (SynthesiserSound* sound) { return true; }

		void startNote (const int midiNoteNumber,
						const float velocity,
						SynthesiserSound* sound,
						const int currentPitchWheelPosition);

		void stopNote (const bool allowTailOff);

		void pitchWheelMoved (const int newValue) { }

		void controllerMoved (const int controllerNumber,
							  const int newValue) { }

		//==============================================================================
		void renderNextBlock (AudioSampleBuffer& outputBuffer, int startSample, int numSamples);

		void setvolume(double v) { vol= v; }
		void setfreq(double f) { freq= f; }

	protected:
		void process(float* p1, float* p2, int samples);

		double phase, low, band, high, vol, freq;
		double vel, out;
		double curvol;
		bool playing;
		int cyclecount;

		bandpass<8> filter;

		class wolp *synth;
};



class wolp:	public AudioProcessor,
            public Synthesiser,
            public ChangeBroadcaster
{
	public:
		enum params
		{
			gain= 0,
			clip,
			gsaw,
			grect,
			gtri,
			tune,
			cutoff,
			resonance,
			bandwidth,
			velocity,
			inertia,
			nfilters,
			curcutoff,
			param_size
		};

		struct paraminfo
		{
			const char *internalname;
			const char *label;
			double min, max, defval;
		};
		static const paraminfo paraminfos[param_size];


		wolp();
		~wolp();

		const String getName() const { return "wolp"; }
		void prepareToPlay (double sampleRate, int estimatedSamplesPerBlock) { }
		void releaseResources() { }
		void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);
		const String getInputChannelName (const int channelIndex) const { return String("In") + String(channelIndex); }
		const String getOutputChannelName (const int channelIndex) const { return String("Out") + String(channelIndex); }
		bool isInputChannelStereoPair (int index) const { return true; }
		bool isOutputChannelStereoPair (int index) const { return true; }
		bool acceptsMidi() const  { return true; }
		bool producesMidi() const { return false; }
		AudioProcessorEditor* createEditor();
		int getNumParameters() { return param_size; }
		const String getParameterName (int idx) { return String(paraminfos[idx].label); }
		float getParameter (int idx)
		{
			return params[idx];
		}
		const String getParameterText (int idx)
		{
			switch(idx)
			{
				default:
					return String::formatted(JUCE_T("%.2f"), getparam(idx));
			}
		}
		void setParameter (int idx, float value)
		{
			params[idx]= value;
			if(idx==curcutoff) cutoff_filter.setvalue(getparam(idx));
			else if(idx==tune)
			{
				for(int i= voices.size(); --i>=0; )
				{
					wolpVoice *voice= (wolpVoice*)voices.getUnchecked(i);
					int note= voice->getCurrentlyPlayingNote();
					if(note>=0) voice->setfreq(getnotefreq(note));
				}
			}
		}

		//==============================================================================
		int getNumPrograms() { return 1; };
		int getCurrentProgram() { return 0; };
		void setCurrentProgram (int index) { };
		const String getProgramName (int index) { return "Default"; };
		void changeProgramName (int index, const String& newName) {}

		//==============================================================================
		void getStateInformation (JUCE_NAMESPACE::MemoryBlock& destData);
		void setStateInformation (const void* data, int sizeInBytes);

		//==============================================================================
		double getnotefreq (int noteNumber)
		{
			noteNumber -= 12 * 6 + 9; // now 0 = A440
			return getparam(tune) * pow (2.0, noteNumber / 12.0);
		}

		float getparam(int idx);

		void renderNextBlock (AudioSampleBuffer& outputAudio,
							  const MidiBuffer& inputMidi,
							  int startSample,
							  int numSamples);

	protected:

	private:
		float params[param_size];

		velocityfilter <float> cutoff_filter;

		unsigned long samples_synthesized;

		friend class wolpVoice;
};


#endif // SYNTH_H
