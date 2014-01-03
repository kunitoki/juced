
// Copyright (c) 2007, Nils Jonas Norberg, See COPYING.txt for details

#include <float.h>
#include <iostream>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//#include "vstgui.h"

#include "params.h"
#include "fastmath.inl"

void Params::Reset()
{
	for ( u32 i = 0 ; i != data.size() ; ++i )
		data[i].Reset();
}

bool Params::Validate()
{
#ifdef DEBUG
    int jEnd = data.size();
    int iEnd = jEnd - 1;

    for (int i = 0 ; i < iEnd ; ++i )
    {
        for (int j = i+1 ; j < jEnd ; ++j )
        {
            std::string sni = data[i].GetShortName();
            std::string snj = data[j].GetShortName();

            std::string lni = data[i].GetLongName();
            std::string lnj = data[j].GetLongName();
            if ( sni == snj || lni == lnj )
            {
                char temp[4096];
                sprintf( temp, "%s %s     %s %s\n", sni.c_str() , snj.c_str(), lni.c_str() , lnj.c_str()  );
                std::cout << temp <<std::endl;
            }
        }
    }
#endif

    return true;
}

Params::Param::Param( u32 width, u32 height, const char* name, const char* unit, float* ctrl, Mode m, float mv, float r, bool* dirty_flag )
:unit_(unit)
,slider_pos_(0)
,ctrl_(ctrl)
,mode_(m)
,mid_value_(mv)
,range_(r)
,screenw_(width)
,screenh_(height)
,screenx_(0)
,screeny_(0)
,dirty_flag_(dirty_flag)
{
	char* s = strchr( name, '|' );
	if (s)
	{
        short_name_.assign( name, s - name );
        ++s;
        int len = strlen(s);
		long_name_.assign (s, s + len);
	}
	else
	{
		short_name_ = name;
		long_name_ = name;
	}

	if (short_name_.size() > 8)
		short_name_.erase(8);

	SetValueFromRange( *ctrl_ );
	original_value_ = *ctrl_;
}

void Params::Param::Reset()
{
	SetValueFromRange( original_value_ );
}

void Params::Param::SetValueFromRangeString( const std::string& /*str*/ )
{
// FIXME!!!
}

void Params::Param::GetDisplay( char* s ) const
{
	switch( mode_ )
	{
	case LINJ:
	case POW2:
	case POWX:
	case INTEGER:
		snprintf( s, 8, "%f", *ctrl_ );
		s[7] = 0;
		break;
	}
}

void Params::Param::GetRangeValueString( std::stringstream& str ) const
{
    if (!ctrl_)
    {
	    str << "<NULL>";
        return;
    }

	// if integer and there are enums around...
	if ( mode_ == INTEGER )
	{
		int i = (int)fast_ftol1023( *ctrl_ + 512.5f ) - 512;
		if ( 0 <= i && i < enums_.size() )
		{
			str << enums_[i];
		}
        else
        {
            str << i;
        }
	}
	else
	{
		str << *ctrl_;
	}
}

void Params::Param::SetEnums( const char* in_enums, void* dc )
{
/*
    enums_.clear();
	const char* p = in_enums;
	while (*p)
	{
		p = strchr(in_enums,'|');
		if (p)
		{
			std::string e( in_enums, p );
            enums_.push_back(e);
			in_enums = p+1;
		}
		else
		{
			if (*in_enums)
			{
				std::string e( in_enums );
				enums_.push_back(e);
			}
			break;
		}
	}

    for ( u32 i = 0 ; i != enums_.size() ; ++i )
    {
        int w = enums_[i].size() * 6;
        if (dc)
            w = dc->getStringWidth( enums_[i].c_str() );

        if ( w > screenw_ )
            screenw_ = w;
    }
*/
}

const char* Params::Param::GetEnum( unsigned int i) const
{
	if (i >= enums_.size())
		return 0;
	return enums_[i].c_str();
}

float Params::Param::SliderToRange( float v ) const
{
	float newv = 0;

	switch( mode_ )
	{
	case LINJ:
		{
			newv = (mid_value_ - range_) + (range_*2 * v);
		}
		break;
	case POW2:
		{
			newv = mid_value_ * powf( 2, (v-.5f) * range_ * 2.f );
		}
		break;
	case POWX:
		{
			newv = mid_value_ + powf( (v-.5f) * 2, 3.f ) * range_;
		}
		break;
    case INTEGER:
		{
			newv = (mid_value_ - range_) + (range_*2 * v);
			newv = fast_ftol1023(newv+512.5f)-512.f;
		}
		break;
	}

	return newv;
}

float Params::Param::RangeToSlider( float range_value ) const
{
	float slider_pos = 0;
	switch(mode_)
	{
	case LINJ:
		if (fabsf(range_) > FLT_EPSILON)
			slider_pos = (range_value - (mid_value_-range_))/(2.f*range_);
		else
			slider_pos = mid_value_;
		break;
	case POW2:
		{
			float v = range_value / mid_value_;
			v = logf( v ) / logf(2.f);
			if (fabsf(range_) > FLT_EPSILON)
				v /= (range_*2);
			v += .5f;
			slider_pos = v;
		}
		break;
	case POWX:
		{
			float v = range_value - mid_value_;
			if (fabsf(range_) > FLT_EPSILON)
				v /= range_;

			if (v > 0)
				v = powf( v, 1.f / 3.f );
			else
				v = -powf( -v, 1.f / 3.f );

			v *= .5f;
			v += .5f;
			slider_pos = v;
		}
		break;
	case INTEGER:
		slider_pos = floorf( range_value + .5f );
		if (fabsf(range_) > FLT_EPSILON)
			slider_pos = ( slider_pos - (mid_value_-range_))/(2.f*range_);
		break;
	}

	return slider_pos;
}

// this is the real value like time in seconds or whatever this param controls
void Params::Param::SetValueFromRange( float range_value )
{
	float slider_pos = RangeToSlider( range_value );
	SetValueFromSlider( slider_pos );
}

// this is from the linear slider value
void Params::Param::SetValueFromSlider( float v )
{
	// funny written to handle NaN and similar
	if (v < 1.f)
	{
		if (v > 0.f)
			;
		else
			v = 0.f;
	}
	else
		v = 1.f;

	slider_pos_ = v;
	*ctrl_ = SliderToRange(v);

	// if we point to a flag set it to true...
	if (dirty_flag_)
		*dirty_flag_ = true;
}

float Params::Param::GetSliderValue() const
{
	return slider_pos_;
}

float Params::Param::GetDefaultRangeValue() const
{
	return original_value_;
}

float Params::Param::GetDefaultSliderValue() const
{
	return RangeToSlider( original_value_ );
}

float Params::Param::GetRangeValue() const
{
	return *ctrl_;
}

void Params::Param::GetShortName( char* s ) const
{
	strncpy( s, short_name_.c_str(), 31);
	s[31] = 0;
}

const std::string& Params::Param::GetShortName() const
{
	return short_name_;
}

const std::string& Params::Param::GetLongName() const
{
	return long_name_;
}

void Params::Param::GetUnit( char* s ) const
{
	strncpy( s, unit_.c_str(), 8);
	s[7] = 0;
}

const std::string& Params::Param::GetUnit() const
{
	return unit_;
}
