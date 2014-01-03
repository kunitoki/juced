
// Copyright (c) 2007, Nils Jonas Norberg, See COPYING.txt for details

#define _USE_MATH_DEFINES
#include <math.h>

#include "fastmath.inl"

#include "osc.h"
#include "wavegroup.h"
#include "synth.h"
#include "params.h"

#include <float.h>

#include <memory.h>
#include <stdlib.h>
#include <assert.h>

// FIXME!!! unstable should look in a table and "slowly" swiwel PER SUPER OSC

// simple refcount to automatically setup-destroy waves
OscillatorSettings::OscillatorSettings()
{
	form = 0;

	shape_ts1 = shape_ts0 = 0.f;
	shape_tw1 = shape_tw0 = 0.f;
	shape_tm1 = shape_tm0 = 0.f;

    shape_aw1 = shape_aw0 = 0.f;
	shape_am1 = shape_am0 = 0.f;
	shape_ab1 = shape_ab0 = 0.f;
	shape_ao1 = shape_ao0 = 0.f; // amp-octave
	shape_aop1 = shape_aop0 = 0.f; // amp-octave-phase
	shape_ah1 = shape_ah0 = 0.f;
	shape_al1 = shape_al0 = 0.f;
	shape_ac1 = shape_ac0 = 0.f;

    shape_ffb0 = shape_ffb1 = 0.f;

    shape_fcp = 0;
    shape_morph = 0;

	oct = 0;
	semi = 0;
	detune = 0;
	phase = 0.f;
	free = 0;
	harmonic_content = 182.f;

	stage = 0;

	supercount = 2;
	superphase = .1f;
    superfree = .2f;
	superfreqspread = .028f;
	superpanwidth = .8f;

	unstable = 0;
    unstable_speed = .15f;
	on = 0;
	amp = 0.25f;
	pan = 0.5f;

	wave_dirty = true;
	wavedisplay_dirty = true;
}

OscillatorSettings::~OscillatorSettings()
{
}

void OscillatorSettings::fillParams( int i, Params* p )
{
	char tmp[256];

//    FIX MORE ADVANCED GROUPS FOR THE OSCILLATORS ESP. THE WAVESHAPERS

    // add labels to first row
    if ( i == 0 )
    {
        p->AddLayoutDirective( Params::LAYOUT_VGROUP_BEGIN, "" );

        p->AddLayoutDirective( Params::LAYOUT_LABEL, "On", 42, 17 );
        p->AddLayoutDirective( Params::LAYOUT_LABEL, "Stage", 42, 17 );
        p->AddLayoutDirective( Params::LAYOUT_LABEL, "Amp", 42, 24 );
        p->AddLayoutDirective( Params::LAYOUT_LABEL, "Pan", 42, 17 );
   	    p->AddLayoutDirective( Params::LAYOUT_LABEL, "Harm", 42, 17 );

        p->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, "", 1, 1 );

        p->AddLayoutDirective( Params::LAYOUT_LABEL, "Oct", 42, 17 );
        p->AddLayoutDirective( Params::LAYOUT_LABEL, "Semi", 42, 17 );
        p->AddLayoutDirective( Params::LAYOUT_LABEL, "Det.", 42, 17 );

        p->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, "", 1, 1 );

        p->AddLayoutDirective( Params::LAYOUT_LABEL, "Phase", 42, 17 );
        p->AddLayoutDirective( Params::LAYOUT_LABEL, "Free", 42, 17 );
        p->AddLayoutDirective( Params::LAYOUT_LABEL, "Un.", 42, 17 );
        p->AddLayoutDirective( Params::LAYOUT_LABEL, "Un-Spd.", 42, 17 );

        p->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, "", 1, 1 );

        p->AddLayoutDirective( Params::LAYOUT_LABEL, "Cnt", 42, 17 );
        p->AddLayoutDirective( Params::LAYOUT_LABEL, "Phase", 42, 17 );
        p->AddLayoutDirective( Params::LAYOUT_LABEL, "Free", 42, 17 );
        p->AddLayoutDirective( Params::LAYOUT_LABEL, "Sprd", 42, 17 );
        p->AddLayoutDirective( Params::LAYOUT_LABEL, "Wide", 42, 17 );

        p->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, "", 1, 1 );

        p->AddLayoutDirective( Params::LAYOUT_LABEL, "Frm", 42, 17 );

        p->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, "", 1, 1 );

        p->AddLayoutDirective( Params::LAYOUT_LABEL, "t.shp", 42, 12 );
        p->AddLayoutDirective( Params::LAYOUT_LABEL, "t.mir", 42, 12 );
        p->AddLayoutDirective( Params::LAYOUT_LABEL, "t.wrp", 42, 12 );
        p->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, "", 1, 1 );
        p->AddLayoutDirective( Params::LAYOUT_LABEL, "a.mir", 42, 12 );
        p->AddLayoutDirective( Params::LAYOUT_LABEL, "a.wrp", 42, 12 );
        p->AddLayoutDirective( Params::LAYOUT_LABEL, "a.bit", 42, 12 );
        p->AddLayoutDirective( Params::LAYOUT_LABEL, "a.oct", 42, 12 );
        p->AddLayoutDirective( Params::LAYOUT_LABEL, "a.ocp", 42, 12 );
        p->AddLayoutDirective( Params::LAYOUT_LABEL, "a.hp", 42, 12 );
        p->AddLayoutDirective( Params::LAYOUT_LABEL, "a.lp", 42, 12 );
        p->AddLayoutDirective( Params::LAYOUT_LABEL, "a.clp", 42, 12 );

        p->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, "", 1, 1 );

        p->AddLayoutDirective( Params::LAYOUT_LABEL, "f.fb", 42, 12 );
        p->AddLayoutDirective( Params::LAYOUT_LABEL, "f.cp", 42, 12 );

        p->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, "", 1, 1 );

        p->AddLayoutDirective( Params::LAYOUT_LABEL, "Morph", 42, 17 );

        p->AddLayoutDirective( Params::LAYOUT_GROUP_END, "" );
    }

    p->AddLayoutDirective( Params::LAYOUT_VGROUP_BEGIN, "" );

    snprintf(tmp,255,"O%dOn|Oscillator %d On",i,i);
	p->data.push_back(Params::Param( 17, 17, tmp,"on", &on , Params::Param::INTEGER ));

   	snprintf(tmp,255,"O%dSTG|Oscillator %d Stage",i, i);
	p->data.push_back(Params::Param( 17, 17, tmp,"target", &stage, Params::Param::INTEGER, 3.f, 3.f ));
	p->data.back().SetEnums( "A|B|C|D|E|F|G" );

    snprintf(tmp,255,"O%dAmp|Oscillator %d Amplitude",i,i);
	p->data.push_back(Params::Param( 17, 24, tmp,"amp", &amp, Params::Param::LINJ, 0.f, 1.f ));

	snprintf(tmp,255,"O%dPan|Oscillator %d Panorama",i,i);
	p->data.push_back(Params::Param( 17, 17, tmp,"pan", &pan ));

   	snprintf(tmp,255,"O%dHMCS|Oscillator %d Harmonics",i,i);
	p->data.push_back(Params::Param( 17, 17, tmp,"", &harmonic_content, Params::Param::LINJ, 0.f, 1172.f ));

        p->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, "", 1, 1 );

	snprintf(tmp,255,"O%dOcs|Oscillator %d Transpose Octaves",i,i);
	p->data.push_back(Params::Param( 17, 17, tmp,"oct", &oct ,Params::Param::INTEGER, 0, 6 ));

	snprintf(tmp,255,"O%dSemi|Oscillator %d Transpose Semi",i,i);
	p->data.push_back(Params::Param( 17, 17, tmp,"semi", &semi ,Params::Param::INTEGER, 0, 17 ));

	snprintf(tmp,255,"O%dDet|Oscillator %d Detune",i,i);
	p->data.push_back(Params::Param( 17, 17, tmp,"semi", &detune,Params::Param::LINJ,0.f,1.f) );

        p->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, "", 1, 1 );

	snprintf(tmp,255,"O%dPhase|Oscillator %d Phase",i,i);
	p->data.push_back(Params::Param( 17, 17, tmp,"frac", &phase));

	snprintf(tmp,255,"O%dFree|Oscillator %d Free",i,i);
	p->data.push_back(Params::Param( 17, 17, tmp,"free", &free, Params::Param::LINJ ));

	snprintf(tmp,255,"O%dUS|Oscillator %d Unstable",i,i);
	p->data.push_back(Params::Param( 17, 17, tmp,"unstable", &unstable, Params::Param::LINJ, 6.f, 6.f ));

   	snprintf(tmp,255,"O%dUSS|Oscillator %d Unstable Speed",i,i);
	p->data.push_back(Params::Param( 17, 17, tmp,"unstable speed", &unstable_speed, Params::Param::POW2, 0.0075f, 7.f ));

        p->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, "", 1, 1 );

    snprintf(tmp,255,"O%dS-C|Oscillator %d Super Count",i, i);
	p->data.push_back(Params::Param( 17, 17, tmp,"s-count", &supercount, Params::Param::INTEGER, (SUPERCOUNT)*.5f, (SUPERCOUNT-1.f)*.5f));

	snprintf(tmp,255,"O%dS-P|Oscillator %d Super Phase",i,i);
	p->data.push_back(Params::Param( 17, 17, tmp,"s-phase", &superphase ));

   	snprintf(tmp,255,"O%dS-F|Oscillator %d Super Free",i,i);
	p->data.push_back(Params::Param( 17, 17, tmp,"s-free", &superfree ));

	snprintf(tmp,255,"O%dS-S|Oscillator %d Super Spread",i,i);
	p->data.push_back(Params::Param( 17, 17, tmp,"s-sprd", &superfreqspread, Params::Param::POW2, .005f, 9.5f ) );

	snprintf(tmp,255,"O%dS-W|Oscillator %d Super Wide",i,i);
	p->data.push_back(Params::Param( 17, 17, tmp,"s-wide", &superpanwidth ));

        p->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, "", 1, 1 );

   	snprintf(tmp,255,"O%dForm|Oscillator %d Form",i,i);
	p->data.push_back(Params::Param( 17, 17, tmp,"form", &form , Params::Param::INTEGER, (FORM_COUNT-1.f)*.5f, (FORM_COUNT-1.f)*.5f, &wave_dirty ));
    p->data.back().SetEnums( "N|#|^|N2|#2|^2|S|*|*2" );

        p->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, "", 1, 1 );

    p->AddLayoutDirective( Params::LAYOUT_HGROUP_BEGIN, "", 0, 0 );
    p->AddLayoutDirective( Params::LAYOUT_VGROUP_BEGIN, "", 0, 0 );


	// time shape
	snprintf(tmp,255,"O%dShpTb|Oscillator %d Shape Time Bend",i,i);
	p->data.push_back(Params::Param( 8, 12, tmp,"sp time shape", &shape_ts0, Params::Param::LINJ, .5f, .5f, &wave_dirty ));

	snprintf(tmp,255,"O%dShpTm|Oscillator %d Shape Time Mirror",i,i);
	p->data.push_back(Params::Param( 8, 12, tmp,"sp time mirror", &shape_tm0 , Params::Param::LINJ, 2.5f, 1.5f, &wave_dirty ));


	snprintf(tmp,255,"O%dShpTw|Oscillator %d Shape Time Wrap",i,i);
	p->data.push_back(Params::Param( 8, 12, tmp,"sp time wrap", &shape_tw0 , Params::Param::LINJ, 2.5f, 1.5f, &wave_dirty ));

    p->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, "", 1, 1 );

	// amp shape
	snprintf(tmp,255,"O%dShpAm|Oscillator %d Shape Amp Mirror",i,i);
	p->data.push_back(Params::Param( 8, 12, tmp,"sp amp mirror", &shape_am0 , Params::Param::LINJ, 1.5f, .5f, &wave_dirty ));

	snprintf(tmp,255,"O%dShpAw|Oscillator %d Shape Amp Wrap",i,i);
	p->data.push_back(Params::Param( 8, 12, tmp,"sp amp wrap", &shape_aw0 , Params::Param::LINJ, 1.5f, .5f, &wave_dirty ));

	snprintf(tmp,255,"O%dShpAb|Oscillator %d Shape Amp Bitreduce",i,i);
	p->data.push_back(Params::Param( 8, 12, tmp,"sp amp bitreduce", &shape_ab0 , Params::Param::LINJ, .5f, .5f, &wave_dirty ));

	snprintf(tmp,255,"O%dShpAo|Oscillator %d Shape Amp Octave",i,i);
	p->data.push_back(Params::Param( 8, 12, tmp,"sp amp octave", &shape_ao0 , Params::Param::LINJ, 0.f, 2.f, &wave_dirty ));

  	snprintf(tmp,255,"O%dShpAop|Oscillator %d Shape Amp Octave Phase",i,i);
	p->data.push_back(Params::Param( 8, 12, tmp,"sp amp octave", &shape_aop0 , Params::Param::LINJ, .5f, .5f, &wave_dirty ));

	snprintf(tmp,255,"O%dShpAh|Oscillator %d Shape Amp High Pass",i,i);
	p->data.push_back(Params::Param( 8, 12, tmp,"sp amp hp", &shape_ah0 , Params::Param::LINJ, .5f, .5f, &wave_dirty ));

	snprintf(tmp,255,"O%dShpAl|Oscillator %d Shape Amp Low Pass",i,i);
	p->data.push_back(Params::Param( 8, 12, tmp,"sp amp lp", &shape_al0 , Params::Param::LINJ, .5f, .5f, &wave_dirty ));

    snprintf(tmp,255,"O%dShpAc|Oscillator %d Shape Amp Clip",i,i);
	p->data.push_back(Params::Param( 8, 12, tmp,"sp amp clip", &shape_ac0 , Params::Param::LINJ, .5f, .5f, &wave_dirty ));

    p->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, "", 1, 1 );

    snprintf(tmp,255,"O%dShpFfb|Oscillator %d Shape Freq Fundamental Boost",i,i);
	p->data.push_back(Params::Param( 8, 12, tmp,"sp freq fundamental boost", &shape_ffb0 , Params::Param::LINJ, .5f, .5f, &wave_dirty ));

    p->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, "", 8, 12 ); // copy phases..

    p->AddLayoutDirective( Params::LAYOUT_GROUP_END, "" );
    p->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, "", 1, 1 );
    p->AddLayoutDirective( Params::LAYOUT_VGROUP_BEGIN, "", 0, 0 );

    // time shape
	snprintf(tmp,255,"O%dShpTb1|Oscillator %d Shape 1 Time Bend",i,i);
	p->data.push_back(Params::Param( 8, 12, tmp,"sp time shape", &shape_ts1 , Params::Param::LINJ, .5f, .5f, &wave_dirty ));

   	snprintf(tmp,255,"O%dShpTm1|Oscillator %d Shape 1 Time Mirror",i,i);
	p->data.push_back(Params::Param( 8, 12, tmp,"sp time mirror", &shape_tm1 , Params::Param::LINJ, 2.5f, 1.5f, &wave_dirty ));

   	snprintf(tmp,255,"O%dShpTw1|Oscillator %d Shape 1 Time Wrap",i,i);
	p->data.push_back(Params::Param( 8, 12, tmp,"sp time wrap", &shape_tw1,  Params::Param::LINJ, 2.5f, 1.5f, &wave_dirty ));

        p->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, "", 1, 1 );

	// amp shape
	snprintf(tmp,255,"O%dShpAm1|Oscillator %d Shape 1 Amp Mirror",i,i);
	p->data.push_back(Params::Param( 8, 12, tmp,"sp amp mirror", &shape_am1,  Params::Param::LINJ, 1.5f, .5f, &wave_dirty ));

	snprintf(tmp,255,"O%dShpAw1|Oscillator %d Shape 1 Amp Wrap",i,i);
	p->data.push_back(Params::Param( 8, 12, tmp,"sp amp wrap", &shape_aw1,  Params::Param::LINJ, 1.5f, .5f, &wave_dirty ));

    snprintf(tmp,255,"O%dShpAb1|Oscillator %d Shape 1 Amp Bitreduce",i,i);
	p->data.push_back(Params::Param( 8, 12, tmp,"sp amp bitreduce", &shape_ab1,  Params::Param::LINJ, .5f, .5f, &wave_dirty ));

   	snprintf(tmp,255,"O%dShpAo1|Oscillator %d Shape 1 Amp Octave",i,i);
	p->data.push_back(Params::Param( 8, 12, tmp,"sp amp octave", &shape_ao1,  Params::Param::LINJ, 0.f, 2.f, &wave_dirty ));

   	snprintf(tmp,255,"O%dShpAop1|Oscillator %d Shape 1 Amp Octave Phase",i,i);
	p->data.push_back(Params::Param( 8, 12, tmp,"sp amp octave", &shape_aop1 , Params::Param::LINJ, .5f, .5f, &wave_dirty ));

    snprintf(tmp,255,"O%dShpAh1|Oscillator %d Shape 1 Amp High Pass",i,i);
	p->data.push_back(Params::Param( 8, 12, tmp,"sp amp hp", &shape_ah1,  Params::Param::LINJ, .5f, .5f, &wave_dirty ));

    snprintf(tmp,255,"O%dShpAl1|Oscillator %d Shape 1 Amp Low Pass",i,i);
	p->data.push_back(Params::Param( 8, 12, tmp,"sp amp lp", &shape_al1,  Params::Param::LINJ, .5f, .5f, &wave_dirty ));

	snprintf(tmp,255,"O%dShpAc1|Oscillator %d Shape 1 Amp Clip",i,i);
	p->data.push_back(Params::Param( 8, 12, tmp,"sp amp clip", &shape_ac1, Params::Param::LINJ, .5f, .5f, &wave_dirty ));

    p->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, "", 1, 1 );

    snprintf(tmp,255,"O%dShpFfb1|Oscillator %d Shape 1 Freq Fundamental Boost",i,i);
	p->data.push_back(Params::Param( 8, 12, tmp,"sp freq fundamental boost", &shape_ffb1 , Params::Param::LINJ, .5f, .5f, &wave_dirty ));

    snprintf(tmp,255,"O%dShpFcp1|Oscillator %d Shape 1 Freq Copy Phases",i,i);
	p->data.push_back(Params::Param( 8, 12, tmp,"sp freq copy phases", &shape_fcp , Params::Param::INTEGER, .5f, .5f, &wave_dirty ));

    p->AddLayoutDirective( Params::LAYOUT_GROUP_END, "" );
    p->AddLayoutDirective( Params::LAYOUT_GROUP_END, "" );

        p->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, "", 1, 1 );

	snprintf(tmp,255,"O%dShpMrph|Oscillator %d Shape Morph",i,i);
	p->data.push_back(Params::Param( 17, 17, tmp,"sp amp clip", &shape_morph, Params::Param::LINJ, .5f, .5f, &wavedisplay_dirty ));

    p->AddLayoutDirective( Params::LAYOUT_GROUP_END, "" );
}


void OscillatorSettings::GetFreshWaveGroup() const
{
	if (!wave_dirty)
		return;

	wave_dirty = false;
	float* tempwave = WaveGroup::tempwave;

    // to store the original phases...
    kiss_fft_cpx originalPhases[FREQ_DATALEN];

	for ( int group = 0 ; group != WAVEGROUPS ; ++ group )
	{
		float morph = (float)group / (WAVEGROUPS-1);
		float shape_ts = shape_ts0 + ( shape_ts1 - shape_ts0 ) * morph;
		float shape_tw = shape_tw0 + ( shape_tw1 - shape_tw0 ) * morph;
		float shape_tm = shape_tm0 + ( shape_tm1 - shape_tm0 ) * morph;
		float shape_aw = shape_aw0 + ( shape_aw1 - shape_aw0 ) * morph;
		float shape_am = shape_am0 + ( shape_am1 - shape_am0 ) * morph;
		float shape_ab = shape_ab0 + ( shape_ab1 - shape_ab0 ) * morph;
		float shape_ao = shape_ao0 + ( shape_ao1 - shape_ao0 ) * morph;
		float shape_aop = shape_aop0 + ( shape_aop1 - shape_aop0 ) * morph;
		float shape_ah = shape_ah0 + ( shape_ah1 - shape_ah0 ) * morph;
		float shape_al = shape_al0 + ( shape_al1 - shape_al0 ) * morph;
		float shape_ac = shape_ac0 + ( shape_ac1 - shape_ac0 ) * morph;
		float shape_ffb = shape_ffb0 + ( shape_ffb1 - shape_ffb0 ) * morph;

		float n = powf(2, (.5f - shape_ts) * 10.f  );
		for (int i = 0 ; i != CYCLELEN ; ++i)
		{
			// first warp time
			float x = ((float)i / CYCLELEN);
			x = (n+1.f)*x/(x+(n));

			//// then mirror
			x *= shape_tm;
			x = fmod(x,2.f);
			if (x > 1.f)
				x = 2.f - x;

			//// amd wrap
			x *= shape_tw;
			x = fmod(x,1.f);

			tempwave[i] = x;
		}

		int iform = fast_ftol1023( form + .5f );

		switch (iform)
		{
		case FORM_SAW:
			for (int i = 0 ; i != CYCLELEN ; ++i )
				tempwave[i] = tempwave[i] - .5f;
			break;

		case FORM_SQR:
			for (int i = 0 ; i != CYCLELEN ; ++i )
				tempwave[i] = (tempwave[i] < .5f) ? -.5f : .5f;
			break;

		case FORM_TRI:
			for (int i = 0 ; i != CYCLELEN ; ++i )
			{
				tempwave[i] = .5f - 2.f * fabs( .5f - tempwave[i] );
			}
			break;

		case FORM_OLDSAW:
			for (int i = 0 ; i != CYCLELEN ; ++i )
			{
				float x = tempwave[i];
				x -= .5f;
				tempwave[i] = x * ( 2.f - fabsf( x * 2.f ));
			}
			break;

		case FORM_OLDSQR:
			for (int i = 0 ; i != CYCLELEN ; ++i )
			{
				float x = tempwave[i];
				if (x<.5f)
				{
					tempwave[i] = x - .5f;
				}
				else
					tempwave[i] = 1.f - x;
			}
			break;

		case FORM_OLDTRI:
			for (int i = 0 ; i != CYCLELEN ; ++i )
			{
				float x = tempwave[i];
				tempwave[i] = fabsf(1.f-2*x*x) - .5f;
			}
			break;

		case FORM_OLDSIN:
			for (int i = 0 ; i != CYCLELEN ; ++i )
			{
				float x = tempwave[i];
				x = x * 2.f - 1.f;
				tempwave[i] = x * ( 2.f - fabsf( x * 2.f ));
			}
			break;
		}

		for (int i = 0 ; i != CYCLELEN ; ++i)
		{
			float x = tempwave[i];

			// then mirror
			x *= shape_am;
			if (x > .5f)
				x = 1.f - x;
			else if (x < -.5)
				x = -1.f - x;

			// amd wrap
			x *= shape_aw;
			if (x > .5f)
				x = -1.f + x;
			else if (x < -.5f)
				x = 1.f + x;


			tempwave[i] = x;
		}

		if (shape_ab > FLT_EPSILON)
		{
			float a = 1.f - shape_ab;
			a *= a*a;
			a = 1.f + 255.f * a;
			float b = 1.f / a;
			for (int i = 0 ; i != CYCLELEN; ++i)
			{
				float l = tempwave[i] * a;
				int li = fast_ftol1023( l + 512.f ) - 512;
				tempwave[i] = li * b;
			}
		}

		if (fabsf(shape_ao) > FLT_EPSILON)
		{
			static const int oct_len = CYCLELEN>>1;
			float octave[oct_len];
			for (int i = 0 ; i!= oct_len ; ++i)
				octave[i] = (tempwave[i*2] + tempwave[(i*2+1) & CYCLEMASK]) * .5f;

            int offset = fast_ftol1023( shape_aop * oct_len + .5f );
			for (int i = 0 ; i!= CYCLELEN ; ++i)
				tempwave[(i + offset) & CYCLEMASK] += shape_ao * octave[i & (oct_len-1)];

		}

		if ( shape_ah > 0.f )
		{
			float mul = shape_ah * shape_ah;
			mul *= .5f;
			float c = 0;
			for (int i = CYCLELEN-1 ; i != -1  ; --i)
			{
				c += (tempwave[i]-c)*mul;
				tempwave[i] -= c;
			}

			for (int i = CYCLELEN-1 ; i != -1  ; --i)
			{
				c += (tempwave[i]-c)*mul;
				tempwave[i] -= c;
			}
		}

		if ( shape_al > 0.f )
		{
			float mul = (1.f - shape_al) * (1.f - shape_al);
			mul *= .99f;
			mul += .01f;
			float c = tempwave[0];
			for (int i = CYCLELEN-1 ; i != -1  ; --i)
			{
				c += (tempwave[i]-c)*mul;
				tempwave[i] = c;
			}
			float add = (1.f - mul) / CYCLELEN;
			for (int i = CYCLELEN-1 ; i != -1  ; --i)
			{
				c += (tempwave[i]-c)*mul;
				tempwave[i] = c;
				mul += add;
			}
		}

		n = powf(2, (.5f - shape_ac) * 10.f  );
		for (int i = 0 ; i != CYCLELEN ; ++i)
		{
			float x = tempwave[i];
			x = (n+1.f)*x/(abs((int) x)+(n));
			tempwave[i] = x;
		}

        if ( !shape_fcp )
        {
       		wave_group[ group ].set( tempwave, shape_ffb, 0 );
        }
        else
        {
            if ( group == 0 )
            {
           		wave_group[ 0 ].set( tempwave, shape_ffb, 0 );
                memcpy( originalPhases, wave_group[0].GetFreqs(), FREQ_DATALEN * sizeof(kiss_fft_cpx) );
                // normalize
                for (int i = 1 ; i != FREQ_DATALEN ; ++i )
                {
                    kiss_fft_cpx& f = originalPhases[i];
                    float magSqr = f.i*f.i + f.r*f.r;
                    if ( magSqr > FLT_EPSILON*FLT_EPSILON )
                    {
                        float mul = 1.f / sqrtf( magSqr );
                        f.r *= mul;
                        f.i *= mul;
                    }
                    else
                    {
                        f.r = 1.f;
                        f.i = 0.f;
                    }
                }
            }
            else
            {
           		wave_group[ group ].set( tempwave, shape_ffb, originalPhases );
            }
        }
	}

	return;
}

float freq2cycle( float freq /* 0..1 */, float roof )
{
	if (freq < FLT_EPSILON)
		return 0.f;

	float ind = (roof-freq) / freq;

	if (ind < 0)
		return 0.f;
	if (ind > (GROUPCYCLES-1))
		return (GROUPCYCLES-1);
	return ind;
}

// it's never faster than this
__forceinline float fast_fraction( u32 phase )
{
	phase &= FRACMASK; // remove integer part
	phase >>= (FRACBITS - 23); // 23 bits of precision
	phase |= 0x3F800000; // add a hardcoded sign and exponent to make phase be a float in the range [1..2)
	return *((float*)(&phase)) - 1.f;
}

__forceinline float fast_fraction17( u32 phase )
{
	phase &= ((1<<17)-1); // remove integer part
	phase <<= (23 - 17); // 23 bits of precision
	phase |= 0x3F800000; // add a hardcoded sign and exponent to make phase be a float in the range [1..2)
	return *((float*)(&phase)) - 1.f;
}

// will convert from 0..1 -> 0..FRACMASK
//__forceinline u32 fast_ftol( float v /* 0..1 */ )
//{
//	v += 1.f; // make range [1..2)
//	int& r = *((int*)(&v));
//	r &= ~0xFF800000; // remove exponent + sign
//	r <<= (FRACBITS - 23); // only had... 23 bits of precision
//	return r;
//}



void OscillatorInstance::noteOn(OscillatorSettings* o, bool reset )
{
    if ( !reset )
    {
        return;
    }

    osc = o;

	current_cycle = 0;

	state = FIRSTFRAME;
	supercount = (u32)osc->supercount;

	phase[0] = (u32)(osc->phase*4294000000.f); // 32 bits;

	// should be full random right?
	// assert( RAND_MAX == 0x7fff );

	// how free?
	phase[0] += (u32)frand( osc->free * 2147000000.f );

	for ( u32 i = 1 ; i != supercount ; ++i)
	{
		phase[i] = (u32)(phase[i-1] + ((osc->superphase * 4294000000.f) / supercount));
		phase[i] += (u32)frand( osc->superfree * 2147000000.f );
	}

	// never free when playing samples...
//	if (o->form == OscillatorSettings::FORM_SAMPLE)
//		phase[0] = 0;

	// set the different pitches (will introduce some randomness here... and every other keydown thing)

    if ( supercount < 2 )
    {
        superpitch[0] = 0;
    }
    else
    {
        for (u32 i = 0 ; i != supercount ; ++i)
        {
            // generate btw -1 and 1
            superpitch[i] = -1.f + 2.f * ((float)i / ((float)supercount-1.f) );
            superpitch[i] *= 1.f+frand(.03f);
        }

        for (u32 i = 0 ; i != supercount/4 ; ++i)
        {
            u32 ind = i*2+1;
            superpitch[ind] = -superpitch[ind];
            superpitch[supercount-1-ind] = -superpitch[supercount-1-ind];
        }
    }

    for (u32 i = supercount ; i != OscillatorSettings::SUPERCOUNT; ++i)
    {
        superpitch[i] = 0;
    }

	superpan[0] = 0;
	for (u32 i = 0 ; i != supercount ; ++i)
	{
		// spread as much as sylenth...
		if (supercount > 1)
        {
            u32 i2 = i*2;
            if ( i2 == (supercount-1) )
            {
                superpan[i] = 0;
            }
            else if (i2 < (supercount-1) )
            {
    			superpan[i] = -osc->superpanwidth * (1.f+frand(.02f));
            }
            else
            {
    			superpan[i] = osc->superpanwidth * (1.f+frand(.02f));
            }
        }

		// swap every other note (shoud swap every other osc too)
		//if (VoiceInstance::note_counter & 1)
		//	superpan[i] = -superpan[i];
	}

    // set the noise
    for (u32 i = 0 ; i != OscillatorSettings::SUPERCOUNT ; ++i)
	{
        superunstable[i] = frand( osc->unstable ) * osc->unstable_speed;
    }

	desired_cycle_ind = 0;

	int DUMMY = 0;
	const WaveGroup& wg = osc->getWaveGroup( DUMMY );
	desired_cycle = wg.get_wave( desired_cycle_ind );
	current_cycle_ind = desired_cycle_ind;
	current_cycle = desired_cycle;
}



void OscillatorInstance::processAccum( Synth* synth, float* controlbuffer, float* audiobuffer, int count )
{
	if (osc->on < .5f)
		return;

	int form = fast_ftol1023( osc->form + .5f );

	switch( form )
	{
	case OscillatorSettings::FORM_SAW:
	case OscillatorSettings::FORM_SQR:
	case OscillatorSettings::FORM_TRI:
	case OscillatorSettings::FORM_OLDSAW:
	case OscillatorSettings::FORM_OLDSQR:
	case OscillatorSettings::FORM_OLDTRI:
	case OscillatorSettings::FORM_OLDSIN:
		processAccumWave( synth, osc, controlbuffer, audiobuffer, count, form );
		break;
	case OscillatorSettings::FORM_NOISE:
		processAccumNoise( synth, osc, controlbuffer, audiobuffer, count );
		break;
	case OscillatorSettings::FORM_COLOURED_NOISE:
		processAccumColouredNoise( synth, osc, controlbuffer, audiobuffer, count );
		break;
	//case OscillatorSettings::FORM_SAMPLE:
	//	processAccumSample( synth, osc, controlbuffer, audiobuffer, count );
		break;
	}

}

void OscillatorInstance::processAccumNoise( Synth* synth, OscillatorSettings* osc, float* controlbuffer, float* audiobuffer, int count )
{
	float* out = audiobuffer;
	float* amp_in = controlbuffer;
	float* pan_in = amp_in + CBUFS;
	float* harm_in = pan_in + CBUFS;
	float* pitch_in = harm_in + CBUFS;
//	float* spread_in = pitch_in + CBUFS;

	float sr = synth->getSampleRate();

	float floating_midi_key = (*pitch_in) + (osc->oct * 12.f) + osc->semi + osc->detune;
	float pitch_target = note2freq( floating_midi_key ) / sr;

	u32 add = (u32)(pitch_target * 2.f*8192.f*1024.f); // 16 bits
	float tamp = *amp_in + osc->amp;

	// FIXME!!! PAN AND VOL WORKS
	for ( ; count ; --count, out+=2 )
	{
		int i0 = phase[0] >> 17;
		phase[0] += add;
		int i1 = phase[0] >> 17;
		if (i0 != i1)
			oldrandom = frand(tamp);

		out[0] += oldrandom;
		out[1] += oldrandom;
	}
}

void OscillatorInstance::processAccumColouredNoise( Synth* synth, OscillatorSettings* osc, float* controlbuffer, float* audiobuffer, int count )
{
	float* out = audiobuffer;
	float* amp_in = controlbuffer;
	float* pan_in = amp_in + CBUFS;
	float* harm_in = pan_in + CBUFS;
	float* morph_in = harm_in + CBUFS;
	float* pitch_in = morph_in + CBUFS;
//	float* spread_in = pitch_in + CBUFS;

	float sr = synth->getSampleRate();

	float floating_midi_key = (*pitch_in) + (osc->oct * 12.f) + osc->semi + osc->detune;
	float pitch_target = note2freq( floating_midi_key ) / sr;

	u32 add = (u32)(pitch_target * 2.f*8192.f*1024.f); // 16 bits

	float tamp = *amp_in + osc->amp;
	float lpamp = (*harm_in + osc->harmonic_content) / 200.f;
	lpamp = 1.f - lpamp;
	lpamp = 1.5f * fast_clamp_mul2( lpamp, 0.f, 1.f );

	float lpamp2 = lpamp - 1.f;

	// FIXME!!! PAN AND VOL WORKS
	for ( ; count ; --count, out+=2 )
	{
		int i0 = phase[0] >> 17;
		phase[0] += add;
		int i1 = phase[0] >> 17;
		if (i0 != i1)
		{
			oldrandom += deltarand;
			deltarand = frand(tamp) - oldrandom;
		}

		float x = fast_fraction17( phase[0] );

		float mix = lpamp*x*x - lpamp2*x*x*x;

		float r = oldrandom + mix * deltarand;
		out[0] += r;
		out[1] += r;
	}
}

static float* sample = 0;

//void OscillatorInstance::processAccumSample( Synth* synth, OscillatorSettings* /*o*/, float* controlbuffer, float* audiobuffer, int count )
//{
//	if (sample == 0)
//	{
//		FILE* f = fopen("C:\\Program Files\\Steinberg\\VstPlugins\\sample.raw", "rb" );
//		if (f)
//		{
//			sample = new float[0x8000];
//			fread(sample, 0x8000, 4, f );
//			fclose(f);
//		}
//		else
//			return;
//	}
//
//	float* amp_in = controlbuffer;
//	float* pan_in = amp_in + CBUFS;
//	float* harm_in = pan_in + CBUFS;
//	float* morph_in = harm_in + CBUFS;
//	float* pitch_in = morph_in + CBUFS;
////	float* spread_in = pitch_in + CBUFS;
//
//	float sr = synth->getSampleRate();
//
//	float floating_midi_key = (*pitch_in) + (osc->oct * 12.f) + osc->semi + osc->detune;
//	float pitch_target = note2freq( floating_midi_key ) / sr;
//
//	u32 add = (u32)(pitch_target * 2.f*8192.f*1024.f); // 16 bits
//
//	// use pitch as fixp 15:17
//	float* out = audiobuffer;
//	for ( ; count ; --count, out+=2 )
//	{
//		int ind = phase[0]>>17;
//		float frac = fast_fraction17( phase[0] );
//		float v0 = sample[ ind ];
//		float v1 = sample[ (ind+1) & 0x7fff ];
//		float v = v0 + (v1-v0)*frac;
//		out[0] += v;
//		out[1] += v;
//		phase[0] += add;
//	}
//}


// **   **   ***   **   ** *******
// **   **  *****  **   ** **
// ** * ** **   ** **   ** ****
// ******* *******  *****  **
// *** *** **   **    *    *******


void OscillatorInstance::processAccumWave( Synth* synth, OscillatorSettings* osc, float* controlbuffer, float* audiobuffer, int count, int /*form*/ )
{
	// do we need to recalc waves?
	osc->GetFreshWaveGroup();

	float* out = audiobuffer;
	float* amp_in = controlbuffer;
	float* pan_in = amp_in + CBUFS;
	float* harm_in = pan_in + CBUFS;
	float* morph_in = harm_in + CBUFS;
	float* pitch_in = morph_in + CBUFS;
	float* spread_in = pitch_in + CBUFS;

	float sr = synth->getSampleRate();

	// will be calculated
	float pitch_target = 1.f; // init. ed only to take out warning
	u32 add_target[OscillatorSettings::SUPERCOUNT];
	s32 add_add[OscillatorSettings::SUPERCOUNT];
	float amp_ladd[OscillatorSettings::SUPERCOUNT];
	float amp_radd[OscillatorSettings::SUPERCOUNT];

	int scalecount = 0; // countdown to next increase of ctrl

	while (count)
	{
		switch (state)
		{
		case FIRSTFRAME:
		case STABLE:
			{
				while (count && (state != MIXING ))
				{
					// handle changes in stuff every ACSCALE samples
					if (scalecount == 0)
					{
						scalecount = ACSCALE;

						// setup pitch
						for (u32 i = 0 ; i != supercount ; ++i)
						{
                            superunstable[i] += ( frand( osc->unstable ) - superunstable[i]) * osc->unstable_speed;
							float floating_midi_key = (*pitch_in) + (osc->oct * 12) + osc->semi + osc->detune + superpitch[i] * (osc->superfreqspread + *spread_in);
                            floating_midi_key += superunstable[i];
							pitch_target = note2freq( floating_midi_key ) / sr;

							add_target[i] = (u32)(pitch_target * 4294967296.f); // 32 bits
						}

						float roof = note2freq( *harm_in + osc->harmonic_content );
						if (roof > 18000.f )
							roof = 18000.f;
						roof /= sr;
						desired_cycle_ind = fast_ftol1023( freq2cycle( pitch_target, roof ) );

						int morph = (int) (fast_clamp_mul2( osc->shape_morph + *morph_in, 0.f, 1.f) * .5f * (OscillatorSettings::WAVEGROUPS - 1.f ));
						desired_cycle = osc->wave_group[morph].get_wave( desired_cycle_ind );

						//setup amp
						float amp_ltarget[OscillatorSettings::SUPERCOUNT];
						float amp_rtarget[OscillatorSettings::SUPERCOUNT];
						for (u32 i = 0 ; i != supercount ; ++i)
						{
							float tamp = *amp_in + osc->amp;
							float tpan = *pan_in + osc->pan + superpan[i];
							fast_clamp_in_place(tpan,0.f,1.f);
							amp_ltarget[i] = tamp * fake_sin(1.f - tpan);
							amp_rtarget[i] = tamp * fake_sin(tpan);
						}

						if (state == FIRSTFRAME)
						{
							// if first frame set values directly
							state = STABLE;
							for (u32 i = 0 ; i != supercount ; ++i)
							{
								add[i] = add_target[i];
								// ok, this clicks when attack=0 but thats desired right? else set phase to .5
								amp_l[i] = amp_ltarget[i];
								amp_r[i] = amp_rtarget[i];
							}
							current_cycle_ind = desired_cycle_ind;
							current_cycle = desired_cycle;
						}

						// calc the "add"s
						for (u32 i = 0 ; i != supercount ; ++i)
						{
							amp_ladd[i] = (amp_ltarget[i] - amp_l[i]) / ACSCALE;
							amp_radd[i] = (amp_rtarget[i] - amp_r[i]) / ACSCALE;
							add_add[i] = (s32)(add_target[i] - add[i]) / ACSCALE;
						}

						amp_in++;
						pan_in++;
						harm_in++;
						morph_in++;
						pitch_in++;
						spread_in++;

						if (desired_cycle != current_cycle)
						{
							// setup mixing
							mix = 0;
							state = MIXING;
							current_cycle_ind = desired_cycle_ind;
							break;
						}
					}

					int tempcount = count;
					if (scalecount < tempcount)
						tempcount = scalecount;

					count -= tempcount;
					scalecount -= tempcount;

					float* outc = 0;// only init. ed to take out warning
					for ( int superc = supercount-1 ; superc != -1  ; --superc )
					{
						u32 tempcountc = tempcount;

						float ampl = amp_l[superc];
						float ampr = amp_r[superc];
						float ampladd = amp_ladd[superc];
						float ampradd = amp_radd[superc];

						u32 addc = add[superc];
						u32 addaddc = add_add[superc];
						outc = out;

						u32 ph = phase[superc];

						// FIXME!!! UNROLL at least x4
						for ( ; tempcountc ; --tempcountc, outc+=2, ph+=addc, ampl+=ampladd, ampr+=ampradd, addc+=addaddc )
						{
							int ind = ph >> CYCLESHIFT;
							float blend = fast_fraction( ph );
							float v0 = current_cycle[ ind ];
							float v1 = current_cycle[ (ind + 1) & CYCLEMASK ];
							float v = v0 + (v1-v0) * blend;
							outc[0] += v * ampl;
							outc[1] += v * ampr;
						}

						phase[superc] = ph;
						amp_l[superc] = ampl;
						amp_r[superc] = ampr;
						add[superc] = addc;
					}

					// save back values
					out = outc;
				}
			}
			break;

		case MIXING:
			{
				while (count && state == MIXING)
				{
					float mix_time = 0.03f; // seconds (around 1024 samples)
					if (scalecount == 0)
					{
						scalecount = ACSCALE;

						// setup pitch
						for (u32 i = 0 ; i != supercount ; ++i)
						{
                            superunstable[i] += ( frand( osc->unstable ) - superunstable[i]) * osc->unstable_speed;
							float floating_midi_key = (*pitch_in) + (osc->oct * 12) + osc->semi + osc->detune + superpitch[i] * (osc->superfreqspread + *spread_in);
                            floating_midi_key += superunstable[i];
							pitch_target = note2freq( floating_midi_key ) / sr;
							add_target[i] = (u32)(pitch_target * 4294967296.f); // 32 bits
						}

						// calculate desired cycle to speed up mixing if neccesary
						float roof = note2freq( *harm_in + osc->harmonic_content );
						if (roof > 18000.f )
							roof = 18000.f;
						roof /= sr;
						desired_cycle_ind = fast_ftol1023( freq2cycle( pitch_target, roof ) );
						int ind_diff = abs(current_cycle_ind - desired_cycle_ind);
						mix_time /= 1.f + (float)ind_diff; // FIXME!!! make up a smart scale here
						if (mix_time < 0.0008f)
							mix_time = 0.0008f;

						//setup amp
						float amp_ltarget[OscillatorSettings::SUPERCOUNT];
						float amp_rtarget[OscillatorSettings::SUPERCOUNT];
						for (u32 i = 0 ; i != supercount ; ++i)
						{
							float tamp = *amp_in + osc->amp;
							float tpan = *pan_in + osc->pan + superpan[i];
							fast_clamp_in_place(tpan,0.f,1.f);
							amp_ltarget[i] = tamp * fake_sin(1.f - tpan);
							amp_rtarget[i] = tamp * fake_sin(tpan);
						}


						// calc the "add"s
						for (u32 i = 0 ; i != supercount ; ++i)
						{
							amp_ladd[i] = (amp_ltarget[i] - amp_l[i]) / ACSCALE;
							amp_radd[i] = (amp_rtarget[i] - amp_r[i]) / ACSCALE;
							add_add[i] = (s32)(add_target[i] - add[i]) / ACSCALE;
						}

						amp_in++;
						pan_in++;
						harm_in++;
						pitch_in++;
						spread_in++;
					}

					float mix_smp = mix_time * synth->getSampleRate();
					float mix_add = 1.f / mix_smp;
					float mix_left = 1.f - mix;
					int tempcount = (int)(mix_left * mix_smp) + 1;
					if (count < tempcount)
						tempcount = count;

					if (scalecount < tempcount)
						tempcount = scalecount;

					count -= tempcount;
					scalecount -= tempcount;



					float mixc = 0.f; // only init.ed because of warning
					float* outc = 0;
					for ( int superc = supercount-1 ; superc != -1  ; --superc )
					{
						u32 tempcountc = tempcount;
						mixc = mix;

						float ampl = amp_l[superc];
						float ampr = amp_r[superc];
						float ampladd = amp_ladd[superc];
						float ampradd = amp_radd[superc];

						u32 addc = add[superc];
						u32 addaddc = add_add[superc];
						outc = out;

						u32 ph = phase[superc];

						// FIXME!!! UNROLL at least x4
						for ( ; tempcountc ; --tempcountc, outc+=2, ph+=addc, mixc+=mix_add, ampl+=ampladd, ampr+=ampradd, addc+=addaddc )
						{
							int ind = ph >> CYCLESHIFT;
							float blend = fast_fraction( ph );

							float v0a = current_cycle[ ind ];
							float v1a = current_cycle[ (ind + 1) & CYCLEMASK ];
							float va = v0a + (v1a-v0a) * blend;

							float v0b = desired_cycle[ ind ];
							float v1b = desired_cycle[ (ind + 1) & CYCLEMASK ];
							float vb = v0b + (v1b-v0b) * blend;

							float smooth_mix = (3 - 2*mixc)*mixc*mixc;
							float v = va + (vb - va) * smooth_mix;
							outc[0] += v * ampl;
							outc[1] += v * ampr;
						}

						phase[superc] = ph;
						amp_l[superc] = ampl;
						amp_r[superc] = ampr;
						add[superc] = addc;
					}

					// save back values
					out = outc;
					mix = mixc;

					if (mix > 1.f-FLT_EPSILON)
					{
						state = STABLE;
						current_cycle = desired_cycle;
					}
				}
			}
			break;
		}
	}
}
