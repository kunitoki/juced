#ifndef FILTER_INCLUDED
#define FILTER_INCLUDED

// Copyright (c) 2007, Nils Jonas Norberg, See COPYING.txt for details

class VoiceInstance;
class Params;
class Synth;

class FilterSettings
{
public:
	FilterSettings();
	void fillParams( int i, Params* p );

	enum Mode
	{
		CB_LP,
		AN_LP3P, // tb style (2x sr for aliasing?)
		AN_LP4P, // should be close to moog-style...
		CB_BP_CONST_SKIRT,
		CB_HP,
		CB_LS,
		CB_PEQ,
		CB_HS,
		OSC_AM,
		OSC_RM,
		DLY_ST,
		DLY_ST_FB,
		MODE_COUNT
	};
	float mode;
	float on;
	float linj_cut_freq;
	float Q;
	float mixOrBoost; // for shelf and EQ its boost
	float postgain;
};

class FilterInstance
{
public:
	FilterInstance();

	void noteOn( bool reset );
	void processReplace( Synth* synth_in, FilterSettings* f, float* controlbuffer_in, float* audiobuffer_in, int count );
private:

	void processCB_LP( Synth* synth_in, FilterSettings* f, float* controlbuffer_in, float* audiobuffer_in, int count );
	void processAN_LP4P( Synth* synth_in, FilterSettings* f, float* controlbuffer_in, float* audiobuffer_in, int count );
	void processAN_LP3P( Synth* synth_in, FilterSettings* f, float* controlbuffer_in, float* audiobuffer_in, int count );
	void processCB_BP( Synth* synth_in, FilterSettings* f, float* controlbuffer_in, float* audiobuffer_in, int count );
	void processCB_HP( Synth* synth_in, FilterSettings* f, float* controlbuffer_in, float* audiobuffer_in, int count );
	void processCB_LS( Synth* synth_in, FilterSettings* f, float* controlbuffer_in, float* audiobuffer_in, int count );
	void processCB_PEQ( Synth* synth_in, FilterSettings* f, float* controlbuffer_in, float* audiobuffer_in, int count );
	void processCB_HS( Synth* synth_in, FilterSettings* f, float* controlbuffer_in, float* audiobuffer_in, int count );
	void processOSC_AM( Synth* synth_in, FilterSettings* f, float* controlbuffer_in, float* audiobuffer_in, int count );
	void processOSC_RM( Synth* synth_in, FilterSettings* f, float* controlbuffer_in, float* audiobuffer_in, int count );
	void processDLY_ST( Synth* synth_in, FilterSettings* f, float* controlbuffer_in, float* audiobuffer_in, int count );
	void processDLY_ST_FB( Synth* synth_in, FilterSettings* f, float* controlbuffer_in, float* audiobuffer_in, int count );

	// the actual filter
//	const FilterType filter_type;
	float a0, a1, a2, a3, a4; // coeffecients
	float ld0, ld1, ld2, ld3; // left-delay
	float rd0, rd1, rd2, rd3; // right-delay

	u32 phase; // for "osc" style filters
	u32 phase_add; // phase_add

   	u32 delay_pos; // counter for delay
	u32 delay_pos_delay; // fixpoint delay for delay

	bool firstframe;

	int prev_mode;

	static const u32 DELAYBITS = 11;
	static const u32 DELAYBUF = (1<<DELAYBITS);
	static const u32 DELAYBUFM = (DELAYBUF-1);
	float lr_delaybuf[DELAYBUF * 2];
};

#endif
