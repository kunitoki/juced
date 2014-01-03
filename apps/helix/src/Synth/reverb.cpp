
// Copyright (c) 2007, Nils Jonas Norberg, See COPYING.txt for details

#include "reverb.h"
#include "voice.h"

#include "params.h"

#include "fastmath.inl"

#include <math.h>
#include <memory.h>

void ReverbSettings::fillParams( Params* p )
{
	on = 0;
	predelay = .5f;
	prelp = .1f;
	prehp = .9f;
	lp = 1.f;
	hp = 0.f;
	damp = .01f;
	mix = .1f;
	dirty = true;

    p->AddLayoutDirective( Params::LAYOUT_VGROUP_BEGIN, "" );
    p->AddLayoutDirective( Params::LAYOUT_LABEL, "On", 42, 17 );
    p->AddLayoutDirective( Params::LAYOUT_LABEL, "P.Dly", 42, 17 );
    p->AddLayoutDirective( Params::LAYOUT_LABEL, "P.LF", 42, 17 );
   	p->AddLayoutDirective( Params::LAYOUT_LABEL, "P.HP", 42, 17 );
    p->AddLayoutDirective( Params::LAYOUT_LABEL, "LP", 42, 17 );
   	p->AddLayoutDirective( Params::LAYOUT_LABEL, "HP", 42, 17 );
  	p->AddLayoutDirective( Params::LAYOUT_LABEL, "Damp", 42, 17 );
	p->AddLayoutDirective( Params::LAYOUT_LABEL, "Mix", 42, 17 );
    p->AddLayoutDirective( Params::LAYOUT_GROUP_END, "" );

    char tmp[256];
    p->AddLayoutDirective( Params::LAYOUT_VGROUP_BEGIN, "" );
	snprintf(tmp,255,"RevOn|Reverb On");
	p->data.push_back(Params::Param( 17, 17, tmp,"on", &on, Params::Param::INTEGER, .5f, .5f, &dirty ));

   	snprintf(tmp,255,"RevPD|Reverb Pre Delay");
	p->data.push_back(Params::Param( 17, 17, tmp,"predelay", &predelay ));

   	snprintf(tmp,255,"RevPLP|Reverb Pre LPF");
	p->data.push_back(Params::Param( 17, 17, tmp,"lp", &prelp ));

	snprintf(tmp,255,"RevPHP|Reverb Pre HPF");
	p->data.push_back(Params::Param( 17, 17, tmp,"hp", &prehp ));

	snprintf(tmp,255,"RevLP|Reverb Low Pass Filter");
	p->data.push_back(Params::Param( 17, 17, tmp,"lp", &lp ));

	snprintf(tmp,255,"RevHP|Reverb High Pass Filter");
	p->data.push_back(Params::Param( 17, 17, tmp,"hp", &hp ));

	snprintf(tmp,255,"RevD|Reverb Dampen Amplitude");
	p->data.push_back(Params::Param( 17, 17, tmp,"damp", &damp ));

	snprintf(tmp,255,"Rev|Reverb Mix");
	p->data.push_back(Params::Param( 17, 17, tmp,"mix", &mix ));

    p->AddLayoutDirective( Params::LAYOUT_GROUP_END, "" );
}

// FIXME!!! parameters!!!

/* a few primes for reverb efforts
607    613    617    619    631    641    643    647    653    659
661    673    677    683    691    701    709    719    727    733
739    743    751    757    761    769    773    787    797    809
811    821    823    827    829    839    853    857    859    863
877    881    883    887    907    911    919    929    937    941
947    953    967    971    977    983    991    997   1009   1013
1019   1021   1031   1033   1039   1049   1051   1061   1063   1069
1087   1091   1093   1097   1103   1109   1117   1123   1129   1151
1153   1163   1171   1181   1187   1193   1201   1213   1217   1223
1229   1231   1237   1249   1259   1277   1279   1283   1289   1291
1297   1301   1303   1307   1319   1321   1327   1361   1367   1373
1381   1399   1409   1423   1427   1429   1433   1439   1447   1451
1453   1459   1471   1481   1483   1487   1489   1493   1499   1511
1523   1531   1543   1549   1553   1559   1567   1571   1579   1583
1597   1601   1607   1609   1613   1619   1621   1627   1637   1657
1663   1667   1669   1693   1697   1699   1709   1721   1723   1733
1741   1747   1753   1759   1777   1783   1787   1789   1801   1811
1823   1831   1847   1861   1867   1871   1873   1877   1879   1889
1901   1907   1913   1931   1933   1949   1951   1973   1979   1987
1993   1997   1999   2003   2011   2017   2027   2029   2039
*/
void ReverbInstance::reset( Synth* s, ReverbSettings* rev )
{
	synth = s;
	reverb = rev;

	memset( pre_buffer, 0, PRE_DLY_BUFSIZE * sizeof(float) );
	memset( buffer, 0, REVERB_STAGES * DLY_BUFSIZE * sizeof(float) );
	pre_runner = 0;
	runner = 0;

	delaytime[1] = 1307;
	delaytime[1] = 1427;
	delaytime[2] = 1559;
	delaytime[3] = 1619;
	delaytime[4] = 1783;
	delaytime[5] = 1861;
	delaytime[6] = 1999;
	delaytime[7] = 2039;

	for ( int i = 0; i != REVERB_STAGES ; ++i)
		x[i] = 0;

    for ( int i = 0 ; i != 2 ; ++i )
    {
        inlp[i] = 0.f;
        inhp[i] = 0.f;
    }

    modulationP = 1 << 24;
    modulationV = 0;
}

inline void noDenormal( float& f )
{
    static const float normalThresh = 1e-15f;
    if ( fabsf( f ) < normalThresh )
    {
        f = 0.f;
    }
}

void ReverbInstance::processReplace(float* outlr, int count )
{
	if (reverb->on < .5f)
		return;

	if (reverb->dirty)
	{
		reverb->dirty = false;
		reset(synth, reverb);
	}

    static const float normalThresh = 1e-15f;
    for ( int i = 0 ; i != REVERB_STAGES ; ++i )
    {
        // clamp small values to 0, o take out denormals...
        if ( fabsf( x[i] ) < normalThresh )
            x[i] = 0.f;
    }


    // clamp small values to 0
    noDenormal( x[0] );
    noDenormal( x[1] );
    noDenormal( x[6] );
    noDenormal( x[7] );

    noDenormal( inlp[0] );
    noDenormal( inlp[1] );
    noDenormal( inhp[0] );
    noDenormal( inhp[1] );

    u32 minPreDelay = 53*2+1;
	u32 pre_delay0 = minPreDelay + (u32)(reverb->predelay * (float)(PRE_DLY_BUFSIZE-minPreDelay));
	pre_delay0 &= ~1; // force even
	if (pre_delay0 > PRE_DLY_BUFSIZE-2)
		pre_delay0 = PRE_DLY_BUFSIZE-2;

	u32 pre_delay1 = pre_delay0 + 1;

    float prelp = .15f + reverb->prelp * .849f;
    float prehp = .01f + reverb->prehp * .349f;

	float lp = .15f + reverb->lp * .849f;
	float hp = .015f + reverb->hp * .349f;

    float mul = 1.f - reverb->damp*reverb->damp*reverb->damp;
    mul *= .351f;

    fast_clamp_in_place( mul, .01f, .351f );

	for ( ; count ; --count, outlr+=2, ++runner, pre_runner+=2 )
	{
        inlp[0] += ( outlr[0] - inlp[0]) * prelp;
        inlp[1] += ( outlr[1] - inlp[1]) * prelp;
        inhp[0] += ( inlp[0] - inhp[0]) * prehp;
        inhp[1] += ( inlp[1] - inhp[1]) * prehp;

		pre_buffer[ (pre_runner+pre_delay0) & PRE_DLY_BUFMASK ] = inlp[0] - inhp[0];
		pre_buffer[ (pre_runner+pre_delay1) & PRE_DLY_BUFMASK ] = inlp[1] - inhp[1];

		float in[ REVERB_STAGES ];

        modulationV -= modulationP >> 22;
        modulationP += modulationV;

        s32 modP = modulationP >> 19;

        in[0] = buffer[ (0 * DLY_BUFSIZE) + ((         runner + DLY_BUFSIZE - delaytime[0] ) & DLY_BUFMASK) ];
        in[1] = buffer[ (1 * DLY_BUFSIZE) + ((         runner + DLY_BUFSIZE - delaytime[1] ) & DLY_BUFMASK) ];
        in[2] = buffer[ (2 * DLY_BUFSIZE) + ((         runner + DLY_BUFSIZE - delaytime[2] ) & DLY_BUFMASK) ];
        in[3] = buffer[ (3 * DLY_BUFSIZE) + ((         runner + DLY_BUFSIZE - delaytime[3] ) & DLY_BUFMASK) ];
        in[4] = buffer[ (4 * DLY_BUFSIZE) + ((         runner + DLY_BUFSIZE - delaytime[4] ) & DLY_BUFMASK) ];

        // only interpolate the modulated line
        u32 ind0 = (5 * DLY_BUFSIZE) + (( modP + runner + DLY_BUFSIZE - delaytime[5] ) & DLY_BUFMASK );
        u32 ind1 = (5 * DLY_BUFSIZE) + ((ind0 + 1) & DLY_BUFMASK);
        float frac = ( ( modulationP & ((1<<19)-1))) / (float)(1<<19);
        in[5] = buffer[ ind0 ] + ( buffer[ ind1 ] - buffer[ ind0 ]) * frac;

        in[6] = buffer[ (6 * DLY_BUFSIZE) + ((         runner + DLY_BUFSIZE - delaytime[6] ) & DLY_BUFMASK) ];
        in[7] = buffer[ (7 * DLY_BUFSIZE) + ((         runner + DLY_BUFSIZE - delaytime[7] ) & DLY_BUFMASK) ];

        // reference ...

// ++++++++
// +-+-+-+-
// ++--++--
// +--++--+
// ++++----
// +-+--+-+
// ++----++
// +--+-++-

		//// calculate the feedback matrix
        float r[ REVERB_STAGES ];

        float PP______ = in[0] + in[1];
        float PM______ = in[0] - in[1];
        float __PP____ = in[2] + in[3];
        float __PM____ = in[2] - in[3];
        float ____PP__ = in[4] + in[5];
        float ____PM__ = in[4] - in[5];
        float ______PP = in[6] + in[7];
        float ______PM = in[6] - in[7];

        float PPPP____ = PP______ + __PP____;
        float ____PPPP = ____PP__ + ______PP;

        float PMPM____ = PM______ + __PM____;
        float ____PMPM = ____PM__ + ______PM;

        float PPMM____ = PP______ - __PP____;
        float ____PPMM = ____PP__ - ______PP;

        float PMMP____ = PM______ - __PM____;
        float ____PMMP = ____PM__ - ______PM;

  		r[0] = PPPP____ + ____PPPP;
        r[1] = PMPM____ + ____PMPM;
        r[2] = PPMM____ + ____PPMM;
		r[3] = PMMP____ + ____PMMP;

        r[4] = PPPP____ - ____PPPP;
		r[5] = PMPM____ - ____PMPM;
		r[6] = PPMM____ - ____PPMM;
		r[7] = PMMP____ - ____PMMP;

        // scale
   		r[0] *= mul;
        r[1] *= mul;
        r[2] *= mul;
		r[3] *= mul;
        r[4] *= mul;
		r[5] *= mul;
		r[6] *= mul;
		r[7] *= mul;

        // lowpass
        x[0] += (r[0] - x[0]) * lp;
        x[1] += (r[1] - x[1]) * lp;
        x[2] = r[2];
        x[3] = r[3];
        x[4] = r[4];
        x[5] = r[5];
        x[6] += (r[6] - x[6]) * hp;
        x[7] += (r[7] - x[7]) * hp;

		// mix the input (left and right) with the feedback
		u32 outoffset[ REVERB_STAGES ];
		outoffset[0] = (0 * DLY_BUFSIZE) + ((runner) & DLY_BUFMASK);
		outoffset[1] = (1 * DLY_BUFSIZE) + ((runner) & DLY_BUFMASK);
		outoffset[2] = (2 * DLY_BUFSIZE) + ((runner) & DLY_BUFMASK);
		outoffset[3] = (3 * DLY_BUFSIZE) + ((runner) & DLY_BUFMASK);
		outoffset[4] = (4 * DLY_BUFSIZE) + ((runner) & DLY_BUFMASK);
		outoffset[5] = (5 * DLY_BUFSIZE) + ((runner) & DLY_BUFMASK);
		outoffset[6] = (6 * DLY_BUFSIZE) + ((runner) & DLY_BUFMASK);
		outoffset[7] = (7 * DLY_BUFSIZE) + ((runner) & DLY_BUFMASK);

//      2      3      5      7     11     13     17     19     23     29
//     31     37     41     43     47     53     59     61     67     71
//     73     79     83     89     97    101    103    107    109    113
//    127    131    137    139    149    151    157    163    167    173

		buffer[ outoffset[0] ] = x[0]            + pre_buffer[ (pre_runner +  0*2+0) & PRE_DLY_BUFMASK ];
        buffer[ outoffset[1] ] = x[1]            + pre_buffer[ (pre_runner +  5*2+1) & PRE_DLY_BUFMASK ];
		buffer[ outoffset[2] ] = x[2]            + pre_buffer[ (pre_runner + 13*2+0) & PRE_DLY_BUFMASK ];
		buffer[ outoffset[3] ] = x[3]            + pre_buffer[ (pre_runner + 19*2+1) & PRE_DLY_BUFMASK ];
		buffer[ outoffset[4] ] = x[4]            + pre_buffer[ (pre_runner + 29*2+0) & PRE_DLY_BUFMASK ];
		buffer[ outoffset[5] ] = x[5]            + pre_buffer[ (pre_runner + 37*2+1) & PRE_DLY_BUFMASK ];
		buffer[ outoffset[6] ] = ( r[6] - x[6] ) + pre_buffer[ (pre_runner + 43*2+0) & PRE_DLY_BUFMASK ];
		buffer[ outoffset[7] ] = ( r[7] - x[7] ) + pre_buffer[ (pre_runner + 53*2+1) & PRE_DLY_BUFMASK ];

		// mix out
		float lout = x[4];
		float rout = x[5];

        outlr[0] += lout * reverb->mix;
		outlr[1] += rout * reverb->mix;
	}
}
