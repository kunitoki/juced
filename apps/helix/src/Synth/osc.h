#ifndef OSC_INCLUDED
#define OSC_INCLUDED

// Copyright (c) 2007, Nils Jonas Norberg, See COPYING.txt for details

#include "types.h"
#include "wavegroup.h"

class Params;
class Synth;

// fixme
class OscillatorSettings
{
	friend class OscillatorInstance;
	friend class VoiceSettings;
	friend class VoiceInstance;

public:
	OscillatorSettings();
	~OscillatorSettings();

	void fillParams( int i, Params* p );

	enum FORM
	{
		FORM_SAW,
		FORM_SQR,
		FORM_TRI,
		FORM_OLDSAW,
		FORM_OLDSQR,
		FORM_OLDTRI,
		FORM_OLDSIN,
		FORM_NOISE,
		FORM_COLOURED_NOISE,
//		FORM_SAMPLE,
		FORM_COUNT
	};

	bool isDirty() const { return wave_dirty; }
	bool isDispDirty() const { return wavedisplay_dirty; }

    enum{ WAVEGROUPS = 64 };

	void GetFreshWaveGroup() const; // will clear dirty flag if needed...
	const WaveGroup& getWaveGroup( u32 g = 0xFFFFFFFF ) const
	{
		if (g == 0xFFFFFFFF)
			g = (int)( shape_morph * (WAVEGROUPS - 1.f ));
		return wave_group[ g ];
	}
private:

	float on; // 0..1
	float form; // 0..FORM_COUNT-1

	float shape_ts0; // time shape
	float shape_ts1; // time shape

	float shape_tm0; // time-mirror
	float shape_tm1; // time-mirror

	float shape_tw0; // time-wrap
	float shape_tw1; // time-wrap

	float shape_am0; // amp-mirror
	float shape_am1; // amp-mirror

	float shape_aw0; // amp-wrap
	float shape_aw1; // amp-wrap

	float shape_ab0; // amp-br
	float shape_ab1; // amp-br

	float shape_ao0; // amp-octave
	float shape_ao1; // amp-octave

  	float shape_aop0; // amp-octave-phase
	float shape_aop1; // amp-octave-phase

	float shape_ah0; // amp-hipass
	float shape_ah1; // amp-hipass

	float shape_al0; // amp-lopass
	float shape_al1; // amp-lopass

	float shape_ac0; // amp-clip
	float shape_ac1; // amp-clip

  	float shape_ffb0; // freq-fundamentalBoost
	float shape_ffb1; // freq-fundamentalBoost

  	float shape_fcp; // freq-copyPhases

	float shape_morph;

	float amp;
	float pan;
	float oct;
	float semi;
	float detune;
	float phase; /* 0..1 */
	float free; /* 0..1 -> fixed..free*/
	float unstable;
	float unstable_speed;

	float harmonic_content; /* 0..18k */
	float stage; // 0, post f1, post S, post f2 (0..3)

	static const int SUPERCOUNT = 9;
	float superphase; // 0..1 (same as main..as far away as possible)
	float superfree; // 0..1 (same as main..)
	float supercount; // 1..SUPERCOUNT
	float superfreqspread; // 0.01 .. .1
	float superpanwidth; // 0.01 .. .1

	mutable bool wave_dirty; // needs to be recalced...
	mutable bool wavedisplay_dirty;

	mutable WaveGroup wave_group[WAVEGROUPS]; // keep all wavedata...
};

class OscillatorInstance
{
public:
	OscillatorInstance( )
		:state(STABLE)
		,current_cycle(0)
		,deltarand(0)
		,oldrandom(0)
	{}

	void noteOn(OscillatorSettings* o, bool reset );
	void processAccum( Synth* synth_in, float* controlbuffer_in, float* audiobuffer_in, int count );

private:

	void processAccumWave( Synth* synth_in, OscillatorSettings* o, float* controlbuffer_in, float* audiobuffer_in, int count, int form );
	void processAccumNoise( Synth* synth_in, OscillatorSettings* o, float* controlbuffer_in, float* audiobuffer_in, int count );
	void processAccumColouredNoise( Synth* synth_in, OscillatorSettings* o, float* controlbuffer_in, float* audiobuffer_in, int count );
//	void processAccumSample( Synth* synth_in, OscillatorSettings* o, float* controlbuffer_in, float* audiobuffer_in, int count );

	enum STATE
	{
		FIRSTFRAME,
		STABLE,
		// MIXPENDING, // waiting for zero crossing to change waveform
		MIXING // currently mixing between waveforms
	};

	STATE state;
	
	float mix; // 0..1 used when mixing 2 cycles
	
	int current_cycle_ind; // an index
	int desired_cycle_ind; // an index

	const float * current_cycle;
	const float * desired_cycle;

	float amp_l[OscillatorSettings::SUPERCOUNT];
	float amp_r[OscillatorSettings::SUPERCOUNT];

	u32 phase[OscillatorSettings::SUPERCOUNT];
	u32 add[OscillatorSettings::SUPERCOUNT];
	u32 supercount; // actually used

	float superunstable[OscillatorSettings::SUPERCOUNT]; // noise in pitch
	float superpitch[OscillatorSettings::SUPERCOUNT]; // difference in midinotes from center pitch
	float superpan[OscillatorSettings::SUPERCOUNT]; // difference in pan from center pan

	float deltarand;
	float oldrandom;
	Synth* synth;
	OscillatorSettings *osc; // cant be const since we need to touch she "settings"
};

#endif
