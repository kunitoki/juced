#ifndef SYNTH_H_INCLUDED
#define SYNTH_H_INCLUDED

// Copyright (c) 2007, Nils Jonas Norberg, See COPYING.txt for details

#include "osc.h"
#include "eg.h"
#include "voice.h"
#include "delay.h"
#include "reverb.h"
#include "dynamics.h"

class Params;

// FIXME layers or scenes?

class Synth
{
public:
	Synth();
	~Synth();

    // gui and params
    void FillParams();

	// events
    bool LikesRawMidi(int status, int midi1, int midi2 ); // ask if we should queue up this midi message at all?
    void RawMidi(int status, int midi1, int midi2 );
	void noteOn (char note, float velocity/*0..1*/);
	void noteOff (char note);
	void noteOffAll ();

	// process
	void process( float* l, float* r, int count, bool accum );

	void setSampleRate(float sr);
	float getSampleRate() const { return sample_rate; }
	int getKeysPressed() const { return keyCount; }
	float getLastPitch(){ return last_pitch; }

	Params* getParams() { return params; }
	const Params* getParams() const { return params; }

	const VoiceSettings& GetVoices() const { return voices; }

    float GetVu() const { return vuMeter; }

    static const int VOICEMAX = 32;
    const VoiceInstance* GetVoiceInstances() const { return voiceFarm; }
    int GetVoiceInstanceCount() const { return voiceCount; }
private:

	void noteOnPoly(char note, float velocity/*0..1*/);
	void noteOnMonoRetune(char note, float velocity/*0..1*/);
	void noteOnMonoReset(char note, float velocity/*0..1*/);

	VoiceInstance voiceFarm[VOICEMAX];
	int voiceCount;

    // track if we can disable the entire synth...
    float vuMeter;

	float synth_audio[ABUFS * 2]; // the temporary audio for the synth (interleaved stereo )

	VoiceSettings voices;
	DelaySettings delays;
	ReverbSettings reverbs;

	DelayInstance delayi;
	ReverbInstance reverbi;

	float sample_rate;

    // used when in mono mode... sorted keys (either by pitch or chronological)
    enum { MAXKEYS = 256 };
    char keyDown[MAXKEYS];
    int keyCount;

    float last_pitch; // used for glide

	Params *params;

	// mod-src
	EGSettings egs[EG_PER_SYNTH];
	LFOSettings lfos[LFO_PER_SYNTH];
	SEQSettings seqs[SEQ_PER_SYNTH];
	MidiCCSettings  midiccs[CC_PER_SYNTH];

    EGInstance egi[EG_PER_SYNTH];
	LFOInstance lfoi[LFO_PER_SYNTH];
	SEQInstance seqi[SEQ_PER_SYNTH];
	MidiCCInstance  midicci[CC_PER_SYNTH];
};

#endif // SYNTH_H_INCLUDED
