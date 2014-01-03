#ifndef AmpPan_INCLUDED
#define AmpPan_INCLUDED

// Copyright (c) 2007, Nils Jonas Norberg, See COPYING.txt for details

class VoiceInstance;
class Params;

class AmpPanSettings
{
public:
	AmpPanSettings();
	void fillParams( Params* p );
	float amp; // multiplied with eg0
};

class AmpPanInstance
{
public:
	AmpPanInstance();

	void noteOn( AmpPanSettings* a, VoiceInstance* v, bool reset );
	void processReplace(float* lr, float* src, int count);
private:
	

	VoiceInstance* voice; // to get modulation pitch and amp from
	AmpPanSettings* amppan;

	bool firstframe;
	float amp;
};

#endif
