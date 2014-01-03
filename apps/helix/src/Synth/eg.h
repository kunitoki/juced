#ifndef EG_H_INCLUDED
#define EG_H_INCLUDED

// Copyright (c) 2007, Nils Jonas Norberg, See COPYING.txt for details

class Synth;
class Params;
class VoiceInstance;

// look at esq1 manual for more info
class EGSettings
{
public:
	EGSettings()
	{
		level[0] = 1.f;
		level[1] = .8f;
		level[2] = .7f;
		level[3] = .01f;
		level[4] = 0.f;

		time[0] = 0.f;
		time[1] = .4f;
		time[2] = .3f;
		time[3] = .1f;
		time[4] = .2f;

   		time[0] = 0.f;
		time[1] = 0.f;
		time[2] = 0.f;
		time[3] = 0.f;
		time[4] = 0.f;

		time1_velocity = .13f;
		time23_kbdtrack = .15f;
		level_velocity = .5f;
	}

	void fillParams( int i, Params* p );

    enum Shape
    {
        Linj,
        Smooth,
        Early,
        Late,
        ShapeCount
    };

    float shape[5];
	float time[5], level[5]; // attack, d1, d2, r1, r2 (the last level is a zero)
	float time1_velocity; // does velocity scale time?
	float time23_kbdtrack; // does keyboard scale decay-time?
	float level_velocity; // does velocity scale level?
};

class EGInstance
{
public:
    EGInstance();
	void noteOn(float key /*0..1*/ , float vel /*0..1*/, const EGSettings* e, const Synth* s, bool reset = true );
	
	void noteOff();

	inline bool isSilent()
	{
		return state == SILENT;
	}

	void processReplace(float* buff, int count);
	
private:
	enum State
	{
		ATTACK,
		DECAY0,
		DECAY1,
		SUSTAIN,
		RELEASE0,
		RELEASE1,
		SILENT
	};

	float level[5]; // attack, decay1, decay2, release (times are in samples)
	int time[5];
	
	int state; // where in the EG are we?
	int timeInState;
	float currentValue;
    const EGSettings* settings;
};

#endif // EG_H_INCLUDED
