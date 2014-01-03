#ifndef Reverb_INCLUDED
#define Reverb_INCLUDED

// Copyright (c) 2007, Nils Jonas Norberg, See COPYING.txt for details

#include "types.h"

class Synth;
class Params;

class ReverbSettings
{
public:
	ReverbSettings(){};
	void fillParams( Params* p );
	float on;
	float predelay;
	float prelp;
	float prehp;
	float lp;
	float hp;
	float damp;
	float mix;
	bool dirty;
};

#define REVERB_STAGES 8

class ReverbInstance
{
public:
	ReverbInstance()
		:synth(0)
	{}

	void reset( Synth* v, ReverbSettings* rev );
	void processReplace(float* outlr, int count );
private:
	// for pre delay
	static const int PRE_DLY_BUFSIZE = 16*1024;
	static const int PRE_DLY_BUFMASK = (PRE_DLY_BUFSIZE-1);
	float pre_buffer[PRE_DLY_BUFSIZE]; // for 2 channels
	u32 pre_runner;

    s32 modulationP;
    s32 modulationV;

    // for feedback delay network...
	static const int DLY_BUFSIZE = 2048;
	static const int DLY_BUFMASK = 2047;
	float buffer[REVERB_STAGES * DLY_BUFSIZE];

    float inlp[2];
    float inhp[2];

	int delaytime[REVERB_STAGES]; // how far back we should feedback
	float x[REVERB_STAGES]; // to realise lowpass
	u32 runner; // the "now" sample
	ReverbSettings* reverb;
	Synth* synth;
};

#endif
