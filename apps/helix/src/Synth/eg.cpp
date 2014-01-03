
// Copyright (c) 2007, Nils Jonas Norberg, See COPYING.txt for details

#include "eg.h"
#include "synth.h"
#include "params.h"

#include "fastmath.inl"

#include <math.h>

// Envelope-Generator

void EGSettings::fillParams( int i, Params* p )
{
	char tmp[256];

    if ( i == 0 )
    {
        p->AddLayoutDirective( Params::LAYOUT_VGROUP_BEGIN, "" );

        p->AddLayoutDirective( Params::LAYOUT_MAKE_SPACE, "", 42, 17 );

        p->AddLayoutDirective( Params::LAYOUT_LABEL, "A Time", 42, 17 );
        p->AddLayoutDirective( Params::LAYOUT_LABEL, "A Shape", 42, 17 );
        p->AddLayoutDirective( Params::LAYOUT_LABEL, "A Level", 42, 17 );
        p->AddLayoutDirective( Params::LAYOUT_LABEL, "D Time 1", 42, 17 );
        p->AddLayoutDirective( Params::LAYOUT_LABEL, "D Shape 1", 42, 17 );
   	    p->AddLayoutDirective( Params::LAYOUT_LABEL, "D Level 1", 42, 17 );
        p->AddLayoutDirective( Params::LAYOUT_LABEL, "D Time 2", 42, 17 );
        p->AddLayoutDirective( Params::LAYOUT_LABEL, "D Shape 2", 42, 17 );
   	    p->AddLayoutDirective( Params::LAYOUT_LABEL, "S Level", 42, 17 );
  	    p->AddLayoutDirective( Params::LAYOUT_LABEL, "R Time 1", 42, 17 );
        p->AddLayoutDirective( Params::LAYOUT_LABEL, "R Shape 1", 42, 17 );
	    p->AddLayoutDirective( Params::LAYOUT_LABEL, "R Level", 42, 17 );
	    p->AddLayoutDirective( Params::LAYOUT_LABEL, "R Time 2", 42, 17 );
        p->AddLayoutDirective( Params::LAYOUT_LABEL, "R Shape 2", 42, 17 );
	    p->AddLayoutDirective( Params::LAYOUT_LABEL, "A Vel S", 42, 17 );
	    p->AddLayoutDirective( Params::LAYOUT_LABEL, "D Vel S", 42, 17 );
	    p->AddLayoutDirective( Params::LAYOUT_LABEL, "L Vel S", 42, 17 );

        p->AddLayoutDirective( Params::LAYOUT_GROUP_END, "" );
    }

    p->AddLayoutDirective( Params::LAYOUT_VGROUP_BEGIN, "" );

    if ( i == 100 )
    {
       p->AddLayoutDirective( Params::LAYOUT_LABEL, "G", 17, 17 );
    }
    else
    {
    	snprintf(tmp,256,"%d",i);
        p->AddLayoutDirective( Params::LAYOUT_LABEL, tmp, 17, 17 );
    }

	snprintf(tmp,256,"EG%dAT|Envelope Generator %d Attack Time",i,i);
	p->data.push_back(Params::Param( 17, 17, tmp,"s",&time[0], Params::Param::POW2, .1f, 6.f ));

  	snprintf(tmp,255,"EG%dAS|Envelope Generator %d Attack Shape",i, i);
	p->data.push_back(Params::Param( 17, 17, tmp,"shape", &shape[0], Params::Param::INTEGER, 1.5f, 1.5f ));
	p->data.back().SetEnums( "/|S|E|L" );

	snprintf(tmp,256,"EG%dAL|Envelope Generator %d Attack Level",i,i);
    p->data.push_back(Params::Param( 17, 17, tmp,"",&level[0], Params::Param::LINJ, 0.f, 1.f ));

	snprintf(tmp,256,"EG%dDT1|Envelope Generator %d Decay Time 1",i,i);
	p->data.push_back(Params::Param( 17, 17, tmp,"s",&time[1], Params::Param::POW2, .25f, 5.f ));

  	snprintf(tmp,255,"EG%dDS1|Envelope Generator %d Delay Shape 1",i, i);
	p->data.push_back(Params::Param( 17, 17, tmp,"shape", &shape[1], Params::Param::INTEGER, 1.5f, 1.5f ));
	p->data.back().SetEnums( "/|S|E|L" );

	snprintf(tmp,256,"EG%dDL1|Envelope Generator %d Decay Level",i,i);
	p->data.push_back(Params::Param( 17, 17, tmp,"",&level[1], Params::Param::LINJ, 0.f, 1.f));

	snprintf(tmp,256,"EG%dDT2|Envelope Generator %d Decay Time 2",i,i);
	p->data.push_back(Params::Param( 17, 17, tmp,"s",&time[2], Params::Param::POW2, .25f, 5.f ));

    snprintf(tmp,255,"EG%dDS2|Envelope Generator %d Delay Shape 2",i, i);
	p->data.push_back(Params::Param( 17, 17, tmp,"shape", &shape[2], Params::Param::INTEGER, 1.5f, 1.5f ));
	p->data.back().SetEnums( "/|S|E|L" );

	snprintf(tmp,256,"EG%dS|Envelope Generator %d Sustain Level",i,i);
	p->data.push_back(Params::Param( 17, 17, tmp,"",&level[2], Params::Param::LINJ, 0.f, 1.f));

	snprintf(tmp,256,"EG%dRT1|Envelope Generator %d Release Time 1",i,i);
	p->data.push_back(Params::Param( 17, 17, tmp,"s",&time[3], Params::Param::POW2, .25f, 5.f ));

    snprintf(tmp,255,"EG%dRS1|Envelope Generator %d Release Shape 1",i, i);
	p->data.push_back(Params::Param( 17, 17, tmp,"shape", &shape[3], Params::Param::INTEGER, 1.5f, 1.5f ));
	p->data.back().SetEnums( "/|S|E|L" );

	snprintf(tmp,256,"EG%dRL|Envelope Generator %d Release Level",i,i);
	p->data.push_back(Params::Param( 17, 17, tmp,"s",&level[3], Params::Param::LINJ, 0.f, 1.f));

	snprintf(tmp,256,"EG%dRT2|Envelope Generator %d Release Time 2",i,i);
	p->data.push_back(Params::Param( 17, 17, tmp,"s",&time[4], Params::Param::POW2, .25f, 5.f ));

    snprintf(tmp,255,"EG%dRS2|Envelope Generator %d Release Shape 2",i, i);
	p->data.push_back(Params::Param( 17, 17, tmp,"shape", &shape[4], Params::Param::INTEGER, 1.5f, 1.5f ));
	p->data.back().SetEnums( "/|S|E|L" );

	snprintf(tmp,256,"EG%dAVS|Envelope Generator %d Attack Velocity Sensitivity",i,i);
	p->data.push_back(Params::Param( 17, 17, tmp,"", &time1_velocity ) );

	snprintf(tmp,256,"EG%dDKT|Envelope Generator %d Decay Velocity Sensitivity",i,i);
	p->data.push_back(Params::Param( 17, 17, tmp,"", &time23_kbdtrack ) );

	snprintf(tmp,256,"EG%dLVS|Envelope Generator %d Level Velocity Sensitivity",i,i);
	p->data.push_back(Params::Param( 17, 17, tmp,"", &level_velocity ) );

    p->AddLayoutDirective( Params::LAYOUT_GROUP_END, "" );
}

EGInstance::EGInstance()
{
    settings = 0;
    currentValue = 0.f;

    timeInState = 1;
	state = 0;

	for (int i = 0 ; i != 5 ; ++i )
    {
        time[i] = 0;
    	level[i] = 0;
    }

}

void EGInstance::noteOff()
{
    float curVal = 0;
    processReplace( &curVal, 1 );
    currentValue = curVal;

	state = RELEASE0;
    timeInState = 1;
}

void EGInstance::noteOn(float key /*0..1*/ , float vel /*0..1*/, const EGSettings* e, const Synth* s, bool reset )
{
    settings = e;

    if ( !reset )
    {
        float curVal = 0;
        processReplace( &curVal, 1 );
        currentValue = curVal;
    }
    else
    {
        currentValue = 0.f;
    }

    timeInState = 1;
	state = 0;

	float sr = s->getSampleRate();
	// times
	float attack_mul = powf( 1.f / 16.f, (vel - .5f) * 6.f * e->time1_velocity );
	float decay_mul = powf( 1.f / 16.f, (.5f - key) * 6.f * e->time23_kbdtrack );
	if (e->time[0] < .002f )
		time[0] = 0;
	else
		time[0] = (int)(e->time[0] * attack_mul * sr / ACSCALE);

	for (int i = 1 ; i != 5 ; ++i )
		time[i] = (int)(e->time[i] * decay_mul * sr / ACSCALE);

	// values
	float level_mul = 1.f - ((1.f - vel) * e->level_velocity);
	level[0] = e->level[0] * level_mul;
	level[1] = e->level[1] * level_mul;
	level[2] = e->level[2] * level_mul;
	level[3] = e->level[3] * level_mul;
	level[4] = 0;
}


void EGInstance::processReplace(float* buff, int count)
{
	while (count)
	{
        int index = state;
		switch (state)
		{
   		case RELEASE0:
		case RELEASE1:
            --index; // break intentionally left out
		case ATTACK:
		case DECAY0:
		case DECAY1:
			{
                float targetValue = level[index];

                int timeLeft = 1 + (time[index] - timeInState);

                int counter = count;
				if (timeLeft < counter)
					counter = timeLeft;

                count -= counter;

                int iShape = fast_ftol1023( settings->shape[index] + .5f );
                switch ( iShape )
                {
                case EGSettings::Linj:
                    {
                        // SHOULD BE OPTIMIZED...
				        for ( ; counter ; ++buff, --counter, ++timeInState)
				        {
                            float x = (float)timeInState / (float)time[index];
                            float t = x;
					        *buff = currentValue + ( targetValue - currentValue ) * t;
				        }
                    }
                    break;

                case EGSettings::Smooth:
                    {
                        for ( ; counter ; ++buff, --counter, ++timeInState)
                        {
                            float x = (float)timeInState / (float)time[index];
                            float t = (3.f*x - 2.f*x*x)*x;
					        *buff = currentValue + ( targetValue - currentValue ) * t;
                        }
                    }
                    break;

                case EGSettings::Early:
                    {
                        for ( ; counter ; ++buff, --counter, ++timeInState)
                        {
                            float x = (float)timeInState / (float)time[index];
                            float t = .5f*1.11f * x / ( .11f + x) + .5f*1.03f * x*x / (.03f+x*x);
                            *buff = currentValue + ( targetValue - currentValue ) * t;
                        }
                    }
                    break;

                case EGSettings::Late:
                    {
                        for ( ; counter ; ++buff, --counter, ++timeInState)
                        {
                            float x = (float)timeInState / (float)time[index];
                            float t = x*x;
                            *buff = currentValue + ( targetValue - currentValue ) * t;
                        }
                    }
                    break;

                }

                if (timeInState > time[index] )
                {
                    currentValue = level[index];
                    timeInState = 1; // reset to 1 to make sure we're never one sample "behind"
					++state;
                }
			}
			break;

		case SUSTAIN: // sustain (keypressed)
			{
				for ( ; count ; ++buff, --count)
                {
					*buff = currentValue;
                }
			}
			break;

		default: // dead?
			{
				memset(buff,0,count * sizeof(float) );
				count = 0;
			}
			break;
		}
	}
}
