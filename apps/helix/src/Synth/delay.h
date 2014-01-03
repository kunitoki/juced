#ifndef Delay_INCLUDED
#define Delay_INCLUDED

// Copyright (c) 2007, Nils Jonas Norberg, See COPYING.txt for details

#include "types.h"

class Synth;
class Params;


class DelaySettings
{
public:

    enum Mode
    {
        StereoCross,
        LeftCross,
        RightCross,
        Stereo,
        ModeCount
    };

	DelaySettings(){};
	void fillParams( Params* p );
	float on;
	float mode;
	float timeL;
	float timeR;
	float feedback;
	float lp;
	float hp;
	float mixKeyDown;
	float mixKeyUp;
};

class DelayInstance
{
public:
	DelayInstance()
		:synth(0)
	{}

	void reset( Synth* s, DelaySettings* delay );
	void processReplace(float* outlr, int count ); // interleaved stereo
private:

    // one for each mode
   	void processStereoCross(float* outlr, int count ); // interleaved stereo
   	void processLeftCross(float* outlr, int count ); // interleaved stereo
   	void processRightCross(float* outlr, int count ); // interleaved stereo
   	void processStereo(float* outlr, int count ); // interleaved stereo

	static const int DLY_BUFSIZE = 44100;
	float lbuffer[DLY_BUFSIZE];
	float rbuffer[DLY_BUFSIZE];
	float llp;
	float rlp;
	float lhp;
	float rhp;
	int runner;

	float mix;
	Synth* synth; // FIXME!!! should be part/scene
	DelaySettings* delay;
};

#endif
