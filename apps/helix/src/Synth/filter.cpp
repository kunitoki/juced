
// Copyright (c) 2007, Nils Jonas Norberg, See COPYING.txt for details

#define _USE_MATH_DEFINES
#include <math.h>

#include "fastmath.inl"

#include "filter.h"
#include "voice.h"
#include "params.h"
#include "synth.h"

#include <string.h>
#include <assert.h>

// FIXME!!! create table for pow(2,x)


FilterSettings::FilterSettings()
{
	linj_cut_freq = 12*5.f;
	Q = 1.f;
	on = 0.f;
}

void FilterSettings::fillParams( int i, Params* p )
{
	linj_cut_freq = 0.7f;
	Q = 1.f;
	mixOrBoost = 1.f;
	postgain = 1.f;

	char tmp[256];

    snprintf(tmp,256,"FILTER %d", i );
    p->AddLayoutDirective( Params::LAYOUT_HGROUP_BEGIN, tmp );

	snprintf( tmp, 255, "F%dO|Filter %d On", i, i );
	p->data.push_back(Params::Param( 8, 13, tmp,"on", &on , Params::Param::INTEGER ));

	snprintf( tmp, 255, "F%dM|Filter %d Mode", i, i );
	p->data.push_back(Params::Param( 8, 13, tmp,"mode", &mode , Params::Param::INTEGER, (FilterSettings::MODE_COUNT-1.f)*.5f, (FilterSettings::MODE_COUNT-1.f)*.5f) );
	p->data.back().SetEnums( "LP|LP3|LP4|BP|HP|LS|PEQ|HS|AM|RM|DLY|DLYFB" );

	snprintf( tmp, 255, "F%dF|Filter %d Frequency", i, i );
	p->data.push_back(Params::Param( 8, 13, tmp,"octaves", &linj_cut_freq, Params::Param::LINJ, 0.f, 182.f));

	snprintf( tmp, 255, "F%dQ|Filter %d Q", i, i );
	p->data.push_back(Params::Param( 8, 13, tmp,"", &Q, Params::Param::POW2, .125f, 3.f ));

	snprintf(tmp,255,"F%dMx|Filter %d Mix",i,i);
	p->data.push_back(Params::Param( 8, 13, tmp,"", &mixOrBoost, Params::Param::LINJ, 0.f, 1.f ));

	snprintf(tmp,255,"F%dG|Filter %d Gain",i,i);
	p->data.push_back(Params::Param( 8, 13, tmp,"", &postgain, Params::Param::POW2, 1.f, 4.f ));

    p->AddLayoutDirective( Params::LAYOUT_GROUP_END, "" );
}

FilterInstance::FilterInstance()
{
    	prev_mode = -1;
}

void FilterInstance::noteOn( bool reset )
{
	if (reset)
	{
		// reset history
		ld0 = ld1 = ld2 = ld3 = 0;
		rd0 = rd1 = rd2 = rd3 = 0;

		// reset all coeffs
		a0 = a1 = a2 = a3 = a4 = 0.f;

		phase = 0xC0000000;
		phase_add = 0;

   		delay_pos = 0;
		delay_pos_delay = 0;

		firstframe = true;
    	prev_mode = -1;
	}
}

void FilterInstance::processReplace( Synth* synth, FilterSettings* filter, float* controlbuffer, float* audiobuffer, int count )
{
	if (filter->on < .5f)
		return;

	int mode = fast_ftol1023( filter->mode + .5f );

	// reset filters if changed from the outside...
	if (mode != prev_mode)
	{
		ld0 = ld1 = ld2 = ld3 = 0.f;
		rd0 = rd1 = rd2 = rd3 = 0.f;
		a0 = a1 = a2 = a3 = a4 = 0.f;
		prev_mode = mode;
		phase = 0;
        delay_pos = 0;
        delay_pos_delay = 0;
		firstframe = true;
	}

	switch ( mode )
	{
	case FilterSettings::CB_LP:
		processCB_LP( synth, filter, controlbuffer, audiobuffer, count );
		break;

	case FilterSettings::CB_BP_CONST_SKIRT:
		processCB_BP( synth, filter, controlbuffer, audiobuffer, count );
		break;

	case FilterSettings::CB_PEQ:
		processCB_PEQ( synth, filter, controlbuffer, audiobuffer, count );
		break;

	case FilterSettings::AN_LP4P:
		processAN_LP4P( synth, filter, controlbuffer, audiobuffer, count );
		break;

	case FilterSettings::CB_HP:
		processCB_HP( synth, filter, controlbuffer, audiobuffer, count );
		break;

	case FilterSettings::AN_LP3P:
		processAN_LP3P( synth, filter, controlbuffer, audiobuffer, count );
		break;

	case FilterSettings::CB_LS:
		processCB_LS( synth, filter, controlbuffer, audiobuffer, count );
		break;

	case FilterSettings::CB_HS:
		processCB_HS( synth, filter, controlbuffer, audiobuffer, count );
		break;

	case FilterSettings::OSC_AM:
		processOSC_AM( synth, filter, controlbuffer, audiobuffer, count );
		break;

	case FilterSettings::OSC_RM:
		processOSC_RM( synth, filter, controlbuffer, audiobuffer, count );
		break;

	case FilterSettings::DLY_ST:
		processDLY_ST( synth, filter, controlbuffer, audiobuffer, count );
		break;

	case FilterSettings::DLY_ST_FB:
		processDLY_ST_FB( synth, filter, controlbuffer, audiobuffer, count );
		break;

    default:
		// ASSERT(false)
		return;
	}
}

void FilterInstance::processCB_LP( Synth* synth, FilterSettings* filter, float* controlbuffer, float* audiobuffer, int count )
{
	float fmix = filter->mixOrBoost;
	float smix = 1.f - fabsf(fmix);
	fmix *= filter->postgain;
	smix *= filter->postgain;


	float* out = audiobuffer;

	float signlin;
	float signlout;
	float signrin;
	float signrout;

	float* f_in = controlbuffer;

	int scalecount = 0;

	float sr = synth->getSampleRate();

	while (count)
	{
		if (scalecount == 0)
		{
			float f_target = *f_in + filter->linj_cut_freq;
			float roof = note2freq( f_target );
			fast_clamp_in_place(roof, 1.f, 18000.f );
			roof /= sr;

			float omega = (float)(2 * M_PI * roof );
			float sn = sinf(omega);
			float cs = cosf(omega);
			float alpha = sn * sinhf((float)M_LN2 /2.f * filter->Q * omega /sn);
			float lb0 = (1 - cs) /2;
			float lb1 = 1 - cs;
			float lb2 = (1 - cs) /2;
			float la0 = 1 + alpha;
			float la1 = -2 * cs;
			float la2 = 1 - alpha;

			/* precompute the coefficients */
			a0 = lb0 /la0;
			a1 = lb1 /la0;
			a2 = lb2 /la0;
			a3 = la1 /la0;
			a4 = la2 /la0;

			//			cut_add = (f_target - cut) / ACSCALE;
			scalecount = ACSCALE;
			f_in++;
		}

		// only render ACSCALE samples at a time
		int tempcount = count;
		if (scalecount < tempcount)
			tempcount = scalecount;

		count -= tempcount;
		scalecount -= tempcount;

		for ( ; tempcount ; --tempcount, out+=2 /*, cut += cut_add*/ )
		{
			// could also be unrolled
			signlin = out[0];
			signrin = out[1];

			signlout = a0*signlin + ld0;
			signrout = a0*signrin + rd0;

			ld0 = a1*signlin - a3*signlout + ld1;
			rd0 = a1*signrin - a3*signrout + rd1;
			ld1 = a2*signlin - a4*signlout;
			rd1 = a2*signrin - a4*signrout;

			out[0] = fmix * signlout + signlin * smix;
			out[1] = fmix * signrout + signrin * smix;
		}

	}
}

void FilterInstance::processCB_HP( Synth* synth, FilterSettings* filter, float* controlbuffer, float* audiobuffer, int count )
{
	float fmix = filter->mixOrBoost;
	float smix = 1.f - fabsf(fmix);
	fmix *= filter->postgain;
	smix *= filter->postgain;

	float* out = audiobuffer;

	float signlin;
	float signlout;
	float signrin;
	float signrout;

	float* f_in = controlbuffer;

	int scalecount = 0;

	float sr = synth->getSampleRate();

	while (count)
	{
		if (scalecount == 0)
		{
			float f_target = *f_in + filter->linj_cut_freq;
			float roof = note2freq( f_target );
			fast_clamp_in_place(roof, 1.f, 18000.f );
			roof /= sr;

            //b0 =  (1 + cos(w0))/2
            //b1 = -(1 + cos(w0))
            //b2 =  (1 + cos(w0))/2
            //a0 =   1 + alpha
            //a1 =  -2*cos(w0)
            //a2 =   1 - alpha

			float omega = (float)(2 * M_PI * roof );
			float sn = sinf(omega);
			float cs = cosf(omega);
			float alpha = sn * sinhf((float)M_LN2 /2.f * filter->Q * omega /sn);
			float lb0 =  (1 + cs) /2;
			float lb1 = -(1 + cs);
			float lb2 =  (1 + cs) /2;
			float la0 =  1 + alpha;
			float la1 = -2 * cs;
			float la2 =  1 - alpha;

			/* precompute the coefficients */
			a0 = lb0 /la0;
			a1 = lb1 /la0;
			a2 = lb2 /la0;
			a3 = la1 /la0;
			a4 = la2 /la0;

			//			cut_add = (f_target - cut) / ACSCALE;
			scalecount = ACSCALE;
			f_in++;
		}

		// only render ACSCALE samples at a time
		int tempcount = count;
		if (scalecount < tempcount)
			tempcount = scalecount;

		count -= tempcount;
		scalecount -= tempcount;

		for ( ; tempcount ; --tempcount, out+=2 /*, cut += cut_add*/ )
		{
			// could also be unrolled
			signlin = out[0];
			signrin = out[1];

			signlout = a0*signlin + ld0;
			signrout = a0*signrin + rd0;

			ld0 = a1*signlin - a3*signlout + ld1;
			rd0 = a1*signrin - a3*signrout + rd1;
			ld1 = a2*signlin - a4*signlout;
			rd1 = a2*signrin - a4*signrout;

			out[0] = fmix * signlout + signlin * smix;
			out[1] = fmix * signrout + signrin * smix;
		}

	}
}

void FilterInstance::processCB_BP( Synth* synth, FilterSettings* filter, float* controlbuffer, float* audiobuffer, int count )
{
	float fmix = filter->mixOrBoost;
	float smix = 1.f - fabsf(fmix);
	fmix *= filter->postgain;
	smix *= filter->postgain;

	float* out = audiobuffer;

	float signlin;
	float signlout;
	float signrin;
	float signrout;

	float* f_in = controlbuffer;

	int scalecount = 0;

	float sr = synth->getSampleRate();

	while (count)
	{
		if (scalecount == 0)
		{
			float f_target = *f_in + filter->linj_cut_freq;
			float roof = note2freq( f_target );
			fast_clamp_in_place(roof, 1.f, 18000.f );
			roof /= sr;

			float lb0;
			float lb1;
			float lb2;
			float la0;
			float la1;
			float la2;

			float omega = (float)(2 * M_PI * roof );
			float sn = sinf(omega);
			float cs = cosf(omega);
			float alpha = sn * sinhf((float)M_LN2 /2.f * filter->Q * omega /sn);
			lb0 = sn / 2.f;
			lb1 = 0;
			lb2 = -sn / 2.f;
			la0 = 1.f + alpha;
			la1 = -2.f*cs;
			la2 = 1.f - alpha;

			/* precompute the coefficients */
			a0 = lb0 /la0;
			a1 = lb1 /la0; // always 0
			a2 = lb2 /la0;
			a3 = la1 /la0;
			a4 = la2 /la0;

			//			cut_add = (f_target - cut) / ACSCALE;
			scalecount = ACSCALE;
			f_in++;
		}

		// only render ACSCALE samples at a time
		int tempcount = count;
		if (scalecount < tempcount)
			tempcount = scalecount;

		count -= tempcount;
		scalecount -= tempcount;

		for ( ; tempcount ; --tempcount, out+=2 /*, cut += cut_add*/ )
		{
			// could also be unrolled
			signlin = out[0];
			signrin = out[1];

			signlout = a0*signlin + ld0;
			signrout = a0*signrin + rd0;

			// minor opt since a1 is always 0
			ld0 = /* a1*signlin */ -a3*signlout + ld1;
			rd0 = /* a1*signrin */ -a3*signrout + rd1;
			ld1 = a2*signlin - a4*signlout;
			rd1 = a2*signrin - a4*signrout;

			out[0] = fmix * signlout + signlin * smix;
			out[1] = fmix * signrout + signrin * smix;
		}
	}
}

void FilterInstance::processCB_PEQ( Synth* synth, FilterSettings* filter, float* controlbuffer, float* audiobuffer, int count )
{
	float fgain = filter->postgain;

	float* out = audiobuffer;

	float signlin;
	float signlout;
	float signrin;
	float signrout;

	float* f_in = controlbuffer;

	int scalecount = 0;

	float sr = synth->getSampleRate();

	while (count)
	{
		if (scalecount == 0)
		{
			float f_target = *f_in + filter->linj_cut_freq;
			float roof = note2freq( f_target );
			fast_clamp_in_place(roof, 1.f, 18000.f );
			roof /= sr;

			float lb0;
			float lb1;
			float lb2;
			float la0;
			float la1;
			float la2;

			float A = powf( 2.f, 3.f * filter->mixOrBoost );
			float omega = (float)(2 * M_PI * roof );
			float sn = sinf(omega);
			float cs = cosf(omega);
			float alpha = sn * sinhf((float)M_LN2 /2.f * filter->Q * omega /sn);
			lb0 = 1.f + alpha*A;
			lb1 = -2.f*cs;
			lb2 = 1.f - alpha*A;
			la0 = 1.f + alpha/A;
			la1 = -2.f*cs;
			la2 = 1.f - alpha/A;

			/* precompute the coefficients */
			a0 = lb0 /la0;
			a1 = lb1 /la0;
			a2 = lb2 /la0;
			a3 = la1 /la0;
			a4 = la2 /la0;

			//			cut_add = (f_target - cut) / ACSCALE;
			scalecount = ACSCALE;
			f_in++;
		}

		// only render ACSCALE samples at a time
		int tempcount = count;
		if (scalecount < tempcount)
			tempcount = scalecount;

		count -= tempcount;
		scalecount -= tempcount;

		for ( ; tempcount ; --tempcount, out+=2  )
		{
			// could also be unrolled
			signlin = out[0];
			signrin = out[1];

			signlout = a0*signlin + ld0;
			signrout = a0*signrin + rd0;

			ld0 = a1*signlin - a3*signlout + ld1;
			rd0 = a1*signrin - a3*signrout + rd1;
			ld1 = a2*signlin - a4*signlout;
			rd1 = a2*signrin - a4*signrout;

			out[0] = fgain * signlout;
			out[1] = fgain * signrout;
		}
	}
}

__forceinline float sigmoid( float x )
{
    return 2.f * x / (2.f + fabsf(x));
}

void FilterInstance::processAN_LP4P( Synth* synth, FilterSettings* filter, float* controlbuffer, float* audiobuffer, int count )
{
	float fmix = filter->mixOrBoost;
	float smix = 1.f - fabsf(fmix);
	fmix *= filter->postgain;
	smix *= filter->postgain;

	float* out = audiobuffer;

	float signlin;
	float signrin;


	float* f_in = controlbuffer;

	int scalecount = 0;

	float sr = synth->getSampleRate();

	while (count)
	{
		if (scalecount == 0)
		{
			float f_target = *f_in + filter->linj_cut_freq;
			float roof = note2freq( f_target );
			fast_clamp_in_place(roof, 1.f, 18000.f );
			roof /= sr;

			roof /= 2.f; // because of 2xSampling...

			{
				float kfc = 2.0f * roof;
				float kf = roof;

				// float kfcr  =  1.8730f*(kfc*kfc*kfc) + 0.4955f*(kfc*kfc) - 0.6490f*kfc + 0.9988f;
				float kacr  = -3.9364f*(kfc*kfc)     + 1.8409f*kfc       + 0.9968f;

				float expout = expf( -2.0f * (float)M_PI * kf );

				// stage gain
				a0 = (1.f-expout);

				// !!FIXME!! check out what Q is...
				a1 = 4.f * (1.f-filter->Q) * kacr;
			}

			//			cut_add = (f_target - cut) / ACSCALE;
			scalecount = ACSCALE;
			f_in++;
		}

		// only render ACSCALE samples at a time
		int tempcount = count;
		if (scalecount < tempcount)
			tempcount = scalecount;

		count -= tempcount;
		scalecount -= tempcount;

		float lin, rin;

// FIXME!! case for mix == 1
			for ( ; tempcount ; --tempcount, out+=2 /*, cut += cut_add*/ )
			{
				// could also be unrolled
				signlin = out[0];
				signrin = out[1];

// a0 = mK2VG
// a1 = mFeedback
//
// ld3 = mVC4
// ld2 = mVC3
// ld1 = mVC2
// ld0 = mVC1

// lt0 = mT1
// lt1 = mT2
// lt2 = mT3
// lt3 = mT4

				lin = signlin - a1 * sigmoid( ld3 );
				ld0 += a0 * sigmoid(lin - ld0);
				ld1 += a0 * sigmoid(ld0 - ld1);
				ld2 += a0 * (ld1 - ld2);
				ld3 += a0 * (ld2 - ld3);

				lin = signlin - a1 * ld3;
				ld0 += a0 * sigmoid(lin - ld0);
				ld1 += a0 * sigmoid(ld0 - ld1);
				ld2 += a0 * (ld1 - ld2);
				ld3 += a0 * (ld2 - ld3);

				rin = signrin - a1 * sigmoid( rd3 );
				rd0 += a0 * sigmoid(rin - rd0);
				rd1 += a0 * sigmoid(rd0 - rd1);
				rd2 += a0 * (rd1 - rd2);
				rd3 += a0 * (rd2 - rd3);

				rin = signrin - a1 * rd3;
				rd0 += a0 * sigmoid(rin - rd0);
				rd1 += a0 * sigmoid(rd0 - rd1);
				rd2 += a0 * (rd1 - rd2);
				rd3 += a0 * (rd2 - rd3);

				out[0] = fmix * ld3 + smix * signlin;
				out[1] = fmix * rd3 + smix * signrin;
			}
	}
}

void FilterInstance::processAN_LP3P( Synth* synth, FilterSettings* filter, float* controlbuffer, float* audiobuffer, int count )
{
	float fmix = filter->mixOrBoost;
	float smix = 1.f - fabsf(fmix);
	fmix *= filter->postgain;
	smix *= filter->postgain;

	float* out = audiobuffer;

	float signlin;
	float signrin;


	float* f_in = controlbuffer;

	int scalecount = 0;

	float sr = synth->getSampleRate();

	float lt;
	float rt;

	// FIXME!!! SOMEHOW SCALE q to a1
	a1 = (1.f-filter->Q);

	while (count)
	{
		if (scalecount == 0)
		{
			float f_target = *f_in + filter->linj_cut_freq;
			float roof = note2freq( f_target );
			fast_clamp_in_place(roof, 1.f, 18000.f );
			roof /= sr;

			a0 = FreqToCoef( roof );

			//			cut_add = (f_target - cut) / ACSCALE;
			scalecount = ACSCALE;
			f_in++;
		}

		// only render ACSCALE samples at a time
		int tempcount = count;
		if (scalecount < tempcount)
			tempcount = scalecount;

		count -= tempcount;
		scalecount -= tempcount;

		for ( ; tempcount ; --tempcount, out+=2 /*, cut += cut_add*/ )
		{
			// could also be unrolled
			signlin = out[0];
			signrin = out[1];

//cutoff = a0
//res = a1
//lo = ld2
//bp = ld1
//hi = ld0

			//{
			//	float *stop = b + count;
			//	float in;
			//	float t;

			//	while( b < stop ){
			//		in = *b;
			//		t=lo+cutoff*bp;
			//		hi=in-lo-((float)1.8-res*(float)1.8)*bp;
			//		bp+=cutoff*hi;
			//		if (t < -amp) lo = -amp; else if (t > amp) lo = amp; else lo = t;
			//		bs=lo+hi;
			//		*b = lo;
			//		b++;
			//	}
			//}

		// Left
		lt = ld2 + a0 * ld1;
		ld0 = signlin - ld2 - (1.8f - a1 * 1.8f) * ld1;
		ld1 += a0 * ld0;
		ld2 = sigmoid( lt );

		// right
		rt = rd2 + a0 * rd1;
		rd0 = signlin - rd2 - (1.8f - a1 * 1.8f) * rd1;
		rd1 += a0 * rd0;
		rd2 = sigmoid ( rt );

		out[0] = fmix * ld2 + smix * signlin;
		out[1] = fmix * rd2 + smix * signrin;
		}
	}
}

void FilterInstance::processCB_LS( Synth* synth, FilterSettings* filter, float* controlbuffer, float* audiobuffer, int count )
{
	float fgain = filter->postgain;

	float* out = audiobuffer;

	float signlin;
	float signlout;
	float signrin;
	float signrout;

	float* f_in = controlbuffer;

	int scalecount = 0;

	float sr = synth->getSampleRate();

	while (count)
	{
		if (scalecount == 0)
		{
			float f_target = *f_in + filter->linj_cut_freq;
			float roof = note2freq( f_target );
			fast_clamp_in_place(roof, 1.f, 18000.f );
			roof /= sr;

			float lb0;
			float lb1;
			float lb2;
			float la0;
			float la1;
			float la2;

			float A = powf( 2.f, 6.f * (filter->mixOrBoost - .5f) );
			float omega = (float)(2 * M_PI * roof );
			float sn = sinf(omega);
			float cs = cosf(omega);
			float alpha = sn * sinhf((float)M_LN2 /2.f * filter->Q * omega /sn);
			float sqrta = sqrtf(A);

			// FIXME!!! optimize
			lb0 =       A * ( (A+1.f) - (A-1.f)*cs + 2.f * sqrta * alpha );
			lb1 = 2.f * A * ( (A-1.f) - (A+1.f)*cs                       );
			lb2 =       A * ( (A+1.f) - (A-1.f)*cs - 2.f * sqrta * alpha );
			la0 =             (A+1.f) + (A-1.f)*cs + 2.f * sqrta * alpha  ;
			la1 =-2.f *     ( (A-1.f) + (A+1.f)*cs                       );
			la2 =             (A+1.f) + (A-1.f)*cs - 2.f * sqrta * alpha  ;

			/* precompute the coefficients */
			a0 = lb0 /la0;
			a1 = lb1 /la0;
			a2 = lb2 /la0;
			a3 = la1 /la0;
			a4 = la2 /la0;

			//			cut_add = (f_target - cut) / ACSCALE;
			scalecount = ACSCALE;
			f_in++;
		}

		// only render ACSCALE samples at a time
		int tempcount = count;
		if (scalecount < tempcount)
			tempcount = scalecount;

		count -= tempcount;
		scalecount -= tempcount;

		for ( ; tempcount ; --tempcount, out+=2  )
		{
			// could also be unrolled
			signlin = out[0];
			signrin = out[1];

			signlout = a0*signlin + ld0;
			signrout = a0*signrin + rd0;

			ld0 = a1*signlin - a3*signlout + ld1;
			rd0 = a1*signrin - a3*signrout + rd1;
			ld1 = a2*signlin - a4*signlout;
			rd1 = a2*signrin - a4*signrout;

			out[0] = fgain * signlout;
			out[1] = fgain * signrout;
		}
	}
}



void FilterInstance::processCB_HS( Synth* synth, FilterSettings* filter, float* controlbuffer, float* audiobuffer, int count )
{
	float fgain = filter->postgain;

	float* out = audiobuffer;

	float signlin;
	float signlout;
	float signrin;
	float signrout;

	float* f_in = controlbuffer;

	int scalecount = 0;

	float sr = synth->getSampleRate();

	while (count)
	{
		if (scalecount == 0)
		{
			float f_target = *f_in + filter->linj_cut_freq;
			float roof = note2freq( f_target );
			fast_clamp_in_place(roof, 1.f, 18000.f );
			roof /= sr;

			float lb0;
			float lb1;
			float lb2;
			float la0;
			float la1;
			float la2;

			float A = powf( 2.f, 3.f * filter->mixOrBoost );
			float omega = (float)(2 * M_PI * roof );
			float sn = sinf(omega);
			float cs = cosf(omega);
			float alpha = sn * sinhf((float)M_LN2 /2.f * filter->Q * omega /sn);
			float sqrta = sqrtf(A);

			// FIXME!!! optimize
			lb0 =       A * ( (A+1.f) + (A-1.f)*cs + 2.f * sqrta * alpha );
			lb1 =-2.f * A * ( (A-1.f) + (A+1.f)*cs                       );
			lb2 =       A * ( (A+1.f) + (A-1.f)*cs - 2.f * sqrta * alpha );
			la0 =             (A+1.f) - (A-1.f)*cs + 2.f * sqrta * alpha  ;
			la1 = 2.f *     ( (A-1.f) - (A+1.f)*cs                       );
			la2 =             (A+1.f) - (A-1.f)*cs - 2.f * sqrta * alpha  ;

			/* precompute the coefficients */
			a0 = lb0 /la0;
			a1 = lb1 /la0;
			a2 = lb2 /la0;
			a3 = la1 /la0;
			a4 = la2 /la0;

			//			cut_add = (f_target - cut) / ACSCALE;
			scalecount = ACSCALE;
			f_in++;
		}

		// only render ACSCALE samples at a time
		int tempcount = count;
		if (scalecount < tempcount)
			tempcount = scalecount;

		count -= tempcount;
		scalecount -= tempcount;

		for ( ; tempcount ; --tempcount, out+=2  )
		{
			// could also be unrolled
			signlin = out[0];
			signrin = out[1];

			signlout = a0*signlin + ld0;
			signrout = a0*signrin + rd0;

			ld0 = a1*signlin - a3*signlout + ld1;
			rd0 = a1*signrin - a3*signrout + rd1;
			ld1 = a2*signlin - a4*signlout;
			rd1 = a2*signrin - a4*signrout;

			out[0] = fgain * signlout;
			out[1] = fgain * signrout;
		}
	}
}

void FilterInstance::processOSC_AM( Synth* synth, FilterSettings* filter, float* controlbuffer, float* audiobuffer, int count )
{
	float fmix = filter->mixOrBoost;
	float smix = 1.f - fabsf(fmix);
	fmix *= filter->postgain;
	smix *= filter->postgain;

	float signlin;
	float signlout;
	float signrin;
	float signrout;

	float* out = audiobuffer;
	float* f_in = controlbuffer;

	float sr = synth->getSampleRate();

	u32 phase_addadd = 0;

	int scalecount = 0;

	while (count)
	{
		if (scalecount == 0)
		{
			float f_target = *f_in + filter->linj_cut_freq;
			float roof = note2freq( f_target );
			fast_clamp_in_place(roof, 1.f, 18000.f );
			roof /= sr;

			// desired add
			u32 desired_add = (u32)(roof * 4294967296.f); // 32 bits

			if (firstframe)
			{
				phase_add = desired_add;
				firstframe = false;
			}

			phase_addadd = (s32)(desired_add - phase_add) / ACSCALE;

			scalecount = ACSCALE;
			f_in++;
		}

		// only render ACSCALE samples at a time
		int tempcount = count;
		if (scalecount < tempcount)
			tempcount = scalecount;

		count -= tempcount;
		scalecount -= tempcount;

		for ( ; tempcount ; --tempcount, out+=2, phase += phase_add, phase_add += phase_addadd )
		{
			// could also be unrolled
			signlin = out[0];
			signrin = out[1];

			float phasef = fast_bipolar( phase );
			float v = .5f + .5f*fake_sin2( phasef );

			signlout = signlin * v;
			signrout = signrin * v;

			out[0] = fmix * signlout + signlin * smix;
			out[1] = fmix * signrout + signrin * smix;
		}

	}
}

void FilterInstance::processOSC_RM( Synth* synth, FilterSettings* filter, float* controlbuffer, float* audiobuffer, int count )
{
	float fmix = filter->mixOrBoost;
	float smix = 1.f - fabsf(fmix);
	fmix *= filter->postgain;
	smix *= filter->postgain;

	float signlin;
	float signlout;
	float signrin;
	float signrout;

	float* out = audiobuffer;
	float* f_in = controlbuffer;

	float sr = synth->getSampleRate();

	u32 phase_addadd = 0;

	int scalecount = 0;

	while (count)
	{
		if (scalecount == 0)
		{
			float f_target = *f_in + filter->linj_cut_freq;
			float roof = note2freq( f_target );
			fast_clamp_in_place(roof, 1.f, 18000.f );
			roof /= sr;

			// desired add
			u32 desired_add = (u32)(roof * 4294967296.f); // 32 bits

			if (firstframe)
			{
				phase_add = desired_add;
				firstframe = false;
			}

			phase_addadd = (s32)(desired_add - phase_add) / ACSCALE;

			scalecount = ACSCALE;
			f_in++;
		}

		// only render ACSCALE samples at a time
		int tempcount = count;
		if (scalecount < tempcount)
			tempcount = scalecount;

		count -= tempcount;
		scalecount -= tempcount;

		for ( ; tempcount ; --tempcount, out+=2, phase += phase_add, phase_add += phase_addadd )
		{
			// could also be unrolled
			signlin = out[0];
			signrin = out[1];

			float phasef = fast_bipolar( phase );
			float v = fake_sin2( phasef );

			signlout = signlin * v;
			signrout = signrin * v;

			out[0] = fmix * signlout + signlin * smix;
			out[1] = fmix * signrout + signrin * smix;
		}

	}
}

__forceinline float fast_fraction21( u32 phase )
{
	phase &= ((1<<21)-1); // remove integer part
	phase <<= (23 - 21); // 23 bits of precision
	phase |= 0x3F800000; // add a hardcoded sign and exponent to make phase be a float in the range [1..2)
	return *((float*)(&phase)) - 1.f;
}

void FilterInstance::processDLY_ST( Synth* synth, FilterSettings* filter, float* controlbuffer, float* audiobuffer, int count )
{
	float fmix = filter->mixOrBoost;
	float smix = 1.f - fabsf(fmix);
	fmix *= filter->postgain;
	smix *= filter->postgain;

	float signlin;
	float signlout;
	float signrin;
	float signrout;

	float* out = audiobuffer;
	float* f_in = controlbuffer;

	float sr = synth->getSampleRate();

	s32 delay_pos_delay_add = 0;

	int scalecount = 0;

	while (count)
	{
		if (scalecount == 0)
		{
			float f_target = *f_in + filter->linj_cut_freq;
			float roof = note2freq( f_target );
			fast_clamp_in_place(roof, 1.f, 18000.f );

			float delay_samples = sr / roof;
			fast_clamp_in_place(delay_samples, 0.5f, (float)DELAYBUFM );

			// desired add
			u32 desired_delay = (u32)(delay_samples * (float)(1<<(32-DELAYBITS))); // DELAYBITS:rest

			if (firstframe)
			{
				delay_pos = 0;
				delay_pos_delay = desired_delay;
				memset( lr_delaybuf, 0, DELAYBUF * 2 * sizeof(float) );
				firstframe = false;
			}

			delay_pos_delay_add = (s32)(desired_delay - delay_pos_delay) / ACSCALE;

			scalecount = ACSCALE;
			f_in++;
		}

		// only render ACSCALE samples at a time
		int tempcount = count;
		if (scalecount < tempcount)
			tempcount = scalecount;

		count -= tempcount;
		scalecount -= tempcount;

		for ( ; tempcount ; --tempcount, out+=2, delay_pos = (delay_pos-1)&DELAYBUFM, delay_pos_delay += delay_pos_delay_add )
		{
			// FIXME!!! SUPPORT DIFFERENT DELAY ON LEFT AND RIGHT.. would be groovy

			// read from delayline
			u32 indexl0 = delay_pos_delay >> (32-DELAYBITS);
			indexl0 += delay_pos;
			indexl0 &= DELAYBUFM;
			u32 indexl1 = (indexl0 + 1) & DELAYBUFM;

			indexl0 <<= 1;
			indexl1 <<= 1;

			float frac = fast_fraction21(delay_pos_delay);

			signlout = lr_delaybuf[ indexl0 ];
			signlout += ( lr_delaybuf[ indexl1 ] - signlout) * frac;

			signrout = lr_delaybuf[ indexl0 | 1 ];
			signrout += ( lr_delaybuf[ indexl1 | 1 ] - signrout) * frac;

			// could also be unrolled
			signlin = out[0];
			signrin = out[1];

			// write to buffer
			u32 write_indexl0 = delay_pos << 1;
			lr_delaybuf[write_indexl0] = signlin;
			lr_delaybuf[write_indexl0 | 1] = signrin;

			out[0] = fmix * signlout + signlin * smix;
			out[1] = fmix * signrout + signrin * smix;
		}
	}
}

void FilterInstance::processDLY_ST_FB( Synth* synth, FilterSettings* filter, float* controlbuffer, float* audiobuffer, int count )
{
	float fmix = filter->mixOrBoost;
	float smix = 1.f - fabsf(fmix);
	fmix *= filter->postgain;
	smix *= filter->postgain;

	float signlin;
	float signlout;
	float signrin;
	float signrout;

	float* out = audiobuffer;
	float* f_in = controlbuffer;

	float sr = synth->getSampleRate();

    float fb = filter->Q;

	s32 delay_pos_delay_add = 0;

	int scalecount = 0;

	while (count)
	{
		if (scalecount == 0)
		{
			float f_target = *f_in + filter->linj_cut_freq;
			float roof = note2freq( f_target );
			fast_clamp_in_place(roof, 1.f, 18000.f );

			float delay_samples = sr / roof;
			fast_clamp_in_place(delay_samples, 0.5f, (float)DELAYBUFM );

			// desired add
			u32 desired_delay = (u32)(delay_samples * (float)(1<<(32-DELAYBITS))); // DELAYBITS:rest

			if (firstframe)
			{
				delay_pos = 0;
				delay_pos_delay = desired_delay;
				memset( lr_delaybuf, 0, DELAYBUF * 2 * sizeof(float) );
				firstframe = false;
			}

			delay_pos_delay_add = (s32)(desired_delay - delay_pos_delay) / ACSCALE;

			scalecount = ACSCALE;
			f_in++;
		}

		// only render ACSCALE samples at a time
		int tempcount = count;
		if (scalecount < tempcount)
			tempcount = scalecount;

		count -= tempcount;
		scalecount -= tempcount;

		for ( ; tempcount ; --tempcount, out+=2, delay_pos = (delay_pos-1)&DELAYBUFM, delay_pos_delay += delay_pos_delay_add )
		{
			// FIXME!!! SUPPORT DIFFERENT DELAY ON LEFT AND RIGHT.. would be groovy

			// read from delayline
			u32 indexl0 = delay_pos_delay >> (32-DELAYBITS);
			indexl0 += delay_pos;
			indexl0 &= DELAYBUFM;
			u32 indexl1 = (indexl0 + 1) & DELAYBUFM;

			indexl0 <<= 1;
			indexl1 <<= 1;

			float frac = fast_fraction21(delay_pos_delay);

			signlout = lr_delaybuf[ indexl0 ];
			signlout += ( lr_delaybuf[ indexl1 ] - signlout) * frac;

			signrout = lr_delaybuf[ indexl0 | 1 ];
			signrout += ( lr_delaybuf[ indexl1 | 1 ] - signrout) * frac;

			// could also be unrolled
			signlin = out[0];
			signrin = out[1];

			// write to buffer
			u32 write_indexl0 = delay_pos << 1;
			lr_delaybuf[write_indexl0] = signlin + signlout * fb;;
			lr_delaybuf[write_indexl0 | 1] = signrin + signrout * fb;;

			out[0] = fmix * signlout + signlin * smix;
			out[1] = fmix * signrout + signrin * smix;
		}
	}
}

