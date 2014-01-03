#ifndef Shaper_INCLUDED
#define Shaper_INCLUDED

// Copyright (c) 2007, Nils Jonas Norberg, See COPYING.txt for details

class VoiceInstance;
class Params;

class ShaperSettings
{
public:
	ShaperSettings();
	void fillParams( int i, Params* p );

	enum Shape
	{
		SOFT,
		HARD,
		HF0,
		HF1,
		HF2,
		ADDSINE,
		RECTIFY,
		BITCRUSH,
		DIGITAL,
		SHAPE_COUNT
	};

	float on;
	float shape; // enum
	float drive;
	float mix;
	float postgain;
};

class ShaperInstance
{
public:
	ShaperInstance();

	void noteOn( ShaperSettings* f, VoiceInstance* v, bool reset );
	void processReplace(float* audio, int count );
private:
	float dl,dr;
	VoiceInstance* voice; // to get modulation pitch and amp from
	ShaperSettings* shaper;
};

#endif
