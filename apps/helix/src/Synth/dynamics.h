// I disabled dynamics for now... either I do them better, cheaper or something..

//#ifndef Dynamics_INCLUDED
//#define Dynamics_INCLUDED
//
//// Copyright (c) 2007, Nils Jonas Norberg, See COPYING.txt for details
//
//#include "types.h"
//#include <math.h>
//#include <assert.h>
//
//class Synth;
//class Params;
//
//class DynamicsSettings
//{
//public:
//	DynamicsSettings(){};
//	void fillParams( Params* p );
//	float on;
//
//	// compressor?
//
//	// limiter
//	float lim_attack; // s
//	float lim_release; // s
//	float lim_tresh;
//	float lim_knee;
//
//	// softclip
//	float clip_tresh;
//	float clip_knee;
//};
//
//class EnvFollow
//{
//public:
//	EnvFollow( float att, float rel )
//		:attack(att)
//		,release(rel)
//	{
//		for (int i = 0 ; i != POLES ; ++i)
//			env[i] = 0;
//	}
//
//	__forceinline void UpdateRMS( float smp )
//	{
//		// if smp > env
//		smp = fabsf(smp);
//		assert( 0.f <= smp && smp < 40.f );
//
//		float blend = (smp > env[0])?attack:release;
//		env[0] += (smp - env[0]) * blend;
//		for (int i = 1 ; i != POLES ; ++i )
//		{
//			blend = (env[i-1] > env[i])?attack:release;
//			env[i] += (env[i-1] - env[i]) * blend;
//			assert( 0.f <= env[i] && env[i] < 40.f );
//		}
//	}
//
//	__forceinline void UpdatePeak( float smp )
//	{
//		// if smp > env
//		smp = fabsf(smp);
//		assert( 0.f <= smp && smp < 40.f );
//
//		float blend = (smp > env[0])?1.f:release; // first is special to make sure we catch the peaks...
//		env[0] += (smp - env[0]) * blend;
//		for (int i = 1 ; i != POLES ; ++i )
//		{
//			blend = (env[i-1] > env[i])?attack:release;
//			env[i] += (env[i-1] - env[i]) * blend;
//			assert( 0.f <= env[i] && env[i] < 40.f );
//		}
//	}
//
//	__forceinline float GetEnv()
//	{
//		return env[POLES-1];
//	}
//
//	enum {POLES = 2};
//	float env[POLES];
//	float attack;
//	float release;
//};
//
//class DynamicsInstance
//{
//public:
//	DynamicsInstance()
//		:synth(0)
//		,FollowL(1.f,1.f)
//		,FollowR(1.f,1.f)
//	{}
//
//	void reset( Synth* v, DynamicsSettings* dyn );
//	void processReplace(float* outlr, int count );
//private:
//	EnvFollow FollowL;
//	EnvFollow FollowR;
//
//	DynamicsSettings* dynamics;
//	Synth* synth;
//};
//
//#endif
