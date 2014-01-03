#ifndef KBD_INCLUDED
#define KBD_INCLUDED

// Copyright (c) 2007, Nils Jonas Norberg, See COPYING.txt for details

class Params;
class VoiceInstance;

class KBDSettings
{
public:
	KBDSettings();
	void fillParams( int i, Params* p );
	enum GlideMode
	{
		EXP,
		CONST_TIME,
		CONST_SPEED,
		MODE_COUNT
	};

	float on;
	float glide_mode;
	float reset_on_first;
	float glide; // time, speed, halflife-time
	float vel_sens;
};

class KBDInstance
{
public:
	void noteOn(float key, float vel , const KBDSettings* KBD, const VoiceInstance* v, bool use_current_freq = false);
	float getOriginalKey();
	void noteOff(){};
	void processReplace(float* out, int count);
private:
	const KBDSettings* kbd;
	const VoiceInstance* voice;
	float value;
	float target_value;
	float original_target_value;
	float blend; // used when exp
	int frame_count;
};

#endif
