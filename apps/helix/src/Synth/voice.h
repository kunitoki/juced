#ifndef Voice_INCLUDED
#define Voice_INCLUDED

// Copyright (c) 2007, Nils Jonas Norberg, See COPYING.txt for details

#include "osc.h"
#include "filter.h"
#include "shaper.h"
#include "amppan.h"

#include "eg.h"
#include "lfo.h"
#include "seq.h"
#include "kbd.h"
#include "midicc.h"

static const int OSC_PER_VOICE = 4;
static const int FILTER_PER_VOICE = 3; // hardcoded
static const int SHAPER_PER_VOICE = 3; // hardcoded

static const int EG_PER_VOICE = 3;
static const int LFO_PER_VOICE = 2;
static const int SEQ_PER_VOICE = 1;
static const int KBD_PER_VOICE = 1;

enum
{
	MODOSCDST_VOICE_AMP = 0,
	MODOSCDST_VOICE_PAN,
	MODOSCDST_VOICE_HARM,
	MODOSCDST_VOICE_MORPH,
	MODOSCDST_VOICE_PITCH,
	MODOSCDST_VOICE_SPREAD,
	MODOSCDST_VOICE_COUNT
};

enum
{
	MODFLTDST_VOICE_FREQ = 0,
	MODFLTDST_VOICE_COUNT
};


const int MOD_VOICE_DESTINATIONS = OSC_PER_VOICE * MODOSCDST_VOICE_COUNT + FILTER_PER_VOICE * MODFLTDST_VOICE_COUNT;
const int MOD_VOICE_SOURCES = EG_PER_VOICE + LFO_PER_VOICE + SEQ_PER_VOICE + KBD_PER_VOICE;


// mod sources global from synth...

static const int EG_PER_SYNTH = 1;
static const int LFO_PER_SYNTH = 1;
static const int SEQ_PER_SYNTH = 1;
static const int CC_PER_SYNTH = 1;

const int MOD_SYNTH_SOURCES = EG_PER_SYNTH + LFO_PER_SYNTH + SEQ_PER_SYNTH + CC_PER_SYNTH;

// IMPORTANT!!! make sure this names corresponds to mod sources
static const char* mod_src_names[MOD_VOICE_SOURCES + MOD_SYNTH_SOURCES] = 
{
	"EG0", 
	"EG1", 
	"EG2", 
	"LFO0",
	"LFO1",
	"SEQ0",
	"KBD0",
	"EG100", 
	"LFO100",
	"SEQ100",
	"CC100"
};

static const char* mod_dst_names[MOD_VOICE_DESTINATIONS] = 
{
	"O0-AMP", 
	"O0-PAN", 
	"O0-HARM", 
	"O0-MORPH", 
	"O0-PITCH", 
	"O0-SPREAD", 
	"O1-AMP", 
	"O1-PAN", 
	"O1-HARM", 
	"O1-MORPH", 
	"O1-PITCH", 
	"O1-SPREAD", 
	"O2-AMP", 
	"O2-PAN", 
	"O2-HARM", 
	"O2-MORPH", 
	"O2-PITCH", 
	"O2-SPREAD", 
	"O3-AMP", 
	"O3-PAN", 
	"O3-HARM", 
	"O3-MORPH", 
	"O3-PITCH", 
	"O3-SPREAD", 
	"F0-FREQ", 
	"F1-FREQ",
	"F2-FREQ"
};

class Params;

const int CBUFS = 64; // contol-buf
const int ACSCALE = 32; // control-scale (ratio that is audio and control)
const int ABUFS = CBUFS * ACSCALE;

void accumul8scale(float* dst, float* src, long count, float scale);

class VoiceSettings
{
public:
	VoiceSettings( Synth* s);

	Synth *synth;

	// mod-matrix
	float modmatrix_voice[ MOD_VOICE_SOURCES * MOD_VOICE_DESTINATIONS];
	float modmatrix_synth[ MOD_SYNTH_SOURCES * MOD_VOICE_DESTINATIONS];
	bool modmatrix_touched;

    bool modmatrix_dst_used[MOD_VOICE_DESTINATIONS];

    bool modmatrix_src_used_voice[MOD_VOICE_SOURCES];
	bool modmatrix_src_used_synth[MOD_SYNTH_SOURCES];
	void calc_used();

	enum CONFIG
	{
		CONFIG_SER_FSFS,

		CONFIG_FIRST_PARALLEL,

		CONFIG_PAR_FS_FS = CONFIG_FIRST_PARALLEL,

		CONFIG_COUNT
	};
	float config;
	// float djt; // dynamic just tuning (removed until it works properly)

	enum POLY_MODE
	{
		POLY_MODE_POLY, // normal mode
		POLY_MODE_MONO_RETUNE, // don't reset anything, but only retune
		POLY_MODE_MONO_RESET,
		POLY_MODE_COUNT
	};
	float poly_mode;

	OscillatorSettings  oscs[OSC_PER_VOICE];
	FilterSettings      filters[FILTER_PER_VOICE];
	ShaperSettings      shapers[SHAPER_PER_VOICE];
	AmpPanSettings      amppans;

	EGSettings      egs[EG_PER_VOICE];
	LFOSettings     lfos[LFO_PER_VOICE];
	SEQSettings     seqs[SEQ_PER_VOICE];
	KBDSettings     kbds[KBD_PER_VOICE];

    // this used to be static in the voice
    float voice_audio[ABUFS * 2]; // the temporary audio for this voice only (interleaved stereo
	float parallel_audio[ABUFS * 2]; // (and an extra copy for parallel configs)
    float modsrc_synth[ MOD_SYNTH_SOURCES * CBUFS ];
	float modsrc_voice[ MOD_VOICE_SOURCES * CBUFS ];

	// mod-dest
	float moddst[ MOD_VOICE_DESTINATIONS * CBUFS ];
};

// VoiceInstance
//------------------------------------------------------------------------------------------
class VoiceInstance
{
public:
	static u32 note_counter;

	// methods
	VoiceInstance();
	void noteOn( int in_key, float in_linj_freq /*0..*/, float vel/*0..1*/, VoiceSettings* vs, bool monoMode = false );
	void noteOff();
	void processAccum( float* lr, int count );

	void processAccumSer( float* lr, int count );
	void processAccumPar( float* lr, int count );

	// data-members
	enum VoiceInstanceState
	{
		Unused,
		Used, // playing
		Release // playing, but received note-off, waiting for tail to die
	};

	VoiceInstanceState state;
	int frames_in_state;
	int key;
	VoiceSettings* settings;

	// audio

	OscillatorInstance osci[OSC_PER_VOICE];
	FilterInstance filteri[FILTER_PER_VOICE];
	ShaperInstance shaperi[SHAPER_PER_VOICE];
	AmpPanInstance amppani;

	// mod-src
	EGInstance  egi[EG_PER_VOICE];
	LFOInstance lfoi[LFO_PER_VOICE];
	SEQInstance seqi[SEQ_PER_VOICE];
	KBDInstance kbdi[KBD_PER_VOICE];
};

#endif
