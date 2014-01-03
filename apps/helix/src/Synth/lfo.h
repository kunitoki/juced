#ifndef LFO_INCLUDED
#define LFO_INCLUDED

// Copyright (c) 2007, Nils Jonas Norberg, See COPYING.txt for details

#include "types.h"

class Params;
class Synth;

class LFOSettings
{
public:
	enum FORM
	{
		SIN,
		RND,
		SQR1, // -1..1
		SQR2, // 0..1
		FORM_COUNT
	};
	void fillParams( int i, Params* p );
	float form;
	float phase;
	float period;

	// HAR
	float hold; // wait before doing anything
	float attack; // halflife
	float release; // halflife
};

class LFOInstance
{
public:
	void noteOn(const LFOSettings* lfo, const Synth* s );
	void noteOff();
	void processReplace(float* out, int count);
private:
	void processReplaceSin(float* out, int count);
	void processReplaceRnd(float* out, int count);
	void processReplaceSqr1(float* out, int count);
	void processReplaceSqr2(float* out, int count);
	void clearValues();

	const LFOSettings* lfo;
	u32 phase;
	u32 add;

	float amp;
	float att_blend;
	float rel_blend;
	int hold_smps;
	enum State { HOLD, ATTACK, RELEASE };
	State har_state;
	int smps_in_state;

	enum
	{
		VALUESBITS = 4,
		VALUES = 1<<VALUESBITS,
		VALUESMASK = VALUES - 1
	};

	float values[VALUES];
};

#endif
