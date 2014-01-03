// I disabled dynamics for now... either I do them better, cheaper or something..

//
//// Copyright (c) 2007, Nils Jonas Norberg, See COPYING.txt for details
//
//#include "dynamics.h"
//#include "synth.h"
//
//#include "Params.h"
//
//#include "fastmath.inl"
//
//#include <math.h>
//#include <memory.h>
//
//void DynamicsSettings::fillParams( Params* p )
//{
//	on = 0;
//	lim_attack = .0003f;
//	lim_release = .02f;
//	lim_tresh = .75f;
//	lim_knee = .25f;
//	clip_tresh = .8f;
//	clip_knee = .8f;
//
//	int x = -PARAM_XSTEP;
//	int y = 0;
//	if (!p->data.empty())
//		y = p->data.back().screeny_ + p->data.back().screenh_ + 3;
//
//	char tmp[256];
//
//	_snprintf(tmp,256,"LimOn|Limiter On");
//	p->data.push_back(Params::Param(tmp,"on", &on, x += PARAM_XSTEP, y , Params::Param::INTEGER ));
//
//	_snprintf(tmp,256,"LimA|Limiter Attack");
//	p->data.push_back(Params::Param(tmp,"attack", &lim_attack, x += PARAM_XSTEP, y, Params::Param::POW2, .01f, 6.f ));
//
//	_snprintf(tmp,256,"LimR|Limiter Release");
//	p->data.push_back(Params::Param(tmp,"release", &lim_release, x += PARAM_XSTEP, y, Params::Param::POW2, .1f, 6.f ));
//
//	_snprintf(tmp,256,"LimT|Limiter Threshold");
//	p->data.push_back(Params::Param(tmp,"tresh", &lim_tresh, x += PARAM_XSTEP, y ));
//
//	_snprintf(tmp,256,"LimK|Limiter Knee");
//	p->data.push_back(Params::Param(tmp,"knee", &lim_knee, x += PARAM_XSTEP, y ));
//
//	_snprintf(tmp,256,"ClipT|Clip Threshold");
//	p->data.push_back(Params::Param(tmp,"knee", &clip_tresh, x += PARAM_XSTEP, y, Params::Param::LINJ, .5f, .4999f ));
//
//	_snprintf(tmp,256,"ClipK|Clip Knee");
//	p->data.push_back(Params::Param(tmp,"knee", &clip_knee, x += PARAM_XSTEP, y, Params::Param::LINJ, .5f, .4999f ));
//}
//
//void DynamicsInstance::reset( Synth* s, DynamicsSettings* dyn )
//{
//	synth = s;
//	dynamics = dyn;
//}
//
//void DynamicsInstance::processReplace(float* outlr, int count )
//{
//	if (dynamics->on < .5f)
//		return;
//
//	float sr = synth->getSampleRate();
//	FollowL.attack = 1.f - powf( .5f, 1.f / (dynamics->lim_attack * sr) );
//	FollowL.release = 1.f - powf( .5f, 1.f / (dynamics->lim_release * sr) );
//
//	FollowR.release = FollowL.release;
//	FollowR.attack = FollowL.attack;
//
//	fast_clamp_in_place( FollowL.attack, 0.00001f, 0.1f );
//	fast_clamp_in_place( FollowL.release,0.00001f, 0.1f );
//	fast_clamp_in_place( FollowR.attack, 0.00001f, 0.1f );
//	fast_clamp_in_place( FollowR.release,0.00001f, 0.1f );
//
//	float tresh = dynamics->lim_tresh;
//	float ratio = dynamics->lim_knee;
//	float clip_tresh = dynamics->clip_tresh;
//	float clip_ratio = dynamics->clip_knee;
//
//	float l;
//	float r;
//	float lt; // temp
//	float rt; // temp
//	u32 lit; // temp
//	u32 rit; // temp
//
//	for ( ; count ; --count, outlr+=2 )
//	{
//		l = outlr[0];
//		r = outlr[1];
//
//		// limiter
//		FollowL.UpdateRMS(l);
//		FollowR.UpdateRMS(r);
//		float diffl = FollowL.GetEnv() - tresh;
//		float diffr = FollowR.GetEnv() - tresh;
//		diffl += fabsf(diffl); // half rect, will clamp at zero
//		diffr += fabsf(diffr); // half rect, will clamp at zero
//		diffl *= .5f;
//		diffr *= .5f;
//		float mull = ratio / (diffl + ratio);
//		float mulr = ratio / (diffr + ratio);
//		l *= mull;
//		r *= mulr;
//
//		// clip
//		lt = l;
//		rt = r;
//		
//		// take sign
//		u32& li = *((u32*)(&lt));
//		u32& ri = *((u32*)(&rt));
//		lit = li & 0x80000000;
//		rit = ri & 0x80000000;
//		lt = fabsf(lt);
//		rt = fabsf(rt);
//
//		lt -= clip_tresh;
//		rt -= clip_tresh;
//		lt += fabsf(lt);
//		rt += fabsf(rt);
//		lt *= .5f;
//		rt *= .5f;
//		lt *= clip_ratio / (lt + clip_ratio);
//		rt *= clip_ratio / (rt + clip_ratio);
//		lt += clip_tresh;
//		rt += clip_tresh;
//
//		// put sign back
//		li |= lit;
//		ri |= rit;
//
//		l = (fabsf(l)<clip_tresh)?l:lt;
//		r = (fabsf(r)<clip_tresh)?r:rt;
//
//		outlr[0] = l;
//		outlr[1] = r;
//	}
//}
