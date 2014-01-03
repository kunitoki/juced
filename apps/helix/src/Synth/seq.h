#ifndef SEQ_INCLUDED
#define SEQ_INCLUDED

// Copyright (c) 2007, Nils Jonas Norberg, See COPYING.txt for details

class Params;
class Synth;

class SEQSettings
{
public:
    SEQSettings();
	void fillParams( int i, Params* p );

// TODO!!! wouldn't it be awesome if you could define the step count?
// TODO!!!    wouldn't it be awesome if you could step once per noteOn?

	enum { STEP_COUNT = 16, STEP_MASK = 15 };
	float steps[STEP_COUNT];
	float period;
	float lagging; // 1pole lowpass...

    float loopBegin;
    float loopEnd;

};

class SEQInstance
{
public:
	void noteOn( const SEQSettings* SEQ, const Synth* s);
	void noteOff(){};
	void processReplace(float* out, int count);
private:
	const SEQSettings* seq;
	const Synth* synth;
	int samples_left_on_step; // samples left on step
	int currstep; // what is the current step
	float currval; // the lagging value...
	float blendval;
};

#endif
