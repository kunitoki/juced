#ifndef MIDICC_H_INCLUDED
#define MIDICC_H_INCLUDED

class Params;

class MidiCCSettings
{
public:
	MidiCCSettings();
	void fillParams( int i, Params* p );

    bool Likes( int status, int m1, int m2 ) const;

    // only pitchbend for now...
	float ccType; // 0-127
    float glideSpeed;
};

class MidiCCInstance
{
public:
    MidiCCInstance();
	void RawMidi( int status, int m1, int m2, const MidiCCSettings* s, bool reset = true );
    void processReplace(float* buff, int count);
    float mValue;
    const MidiCCSettings* settings;
};

#endif // MIDICC_H_INCLUDED
