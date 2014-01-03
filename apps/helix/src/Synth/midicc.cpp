
// Copyright (c) 2007, Nils Jonas Norberg, See COPYING.txt for details

#include "midicc.h"

#include "params.h"
#include "fastmath.inl"

MidiCCSettings::MidiCCSettings()
{
}

void MidiCCSettings::fillParams( int i, Params* p )
{
	// char tmp[256];

	//_snprintf(tmp,255,"CC%d|CC %d",i,i);
	//p->data.push_back(Params::Param(cc,"on", &on, x += PARAM_XSTEP, y, Params::Param::INTEGER, 63.5f, 63.f ));
}

bool MidiCCSettings::Likes( int status, int m1, int m2 ) const
{
    // only handle pitchbend..
    return ( status & 0xF0 ) == 0xE0;
}

MidiCCInstance::MidiCCInstance()
{
}

void MidiCCInstance::RawMidi( int status, int m1, int m2, const MidiCCSettings* s, bool reset )
{
    int value = (m2 << 7) | m1;
    value -= 8192;
    mValue = value / 8192.f;
}

void MidiCCInstance::processReplace(float* buff, int count)
{
    for ( ; count ; --count, ++buff )
    {
        *buff = mValue;
    }
}

