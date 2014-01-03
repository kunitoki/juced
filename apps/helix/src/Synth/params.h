#ifndef PARAMS_INCLUDED
#define PARAMS_INCLUDED

// Copyright (c) 2007, Nils Jonas Norberg, See COPYING.txt for details

#include <vector>
#include <string>
#include <sstream>
#include <math.h>

#include "types.h"

class CDrawContext;
class guiEditor;

class Params
{
public:
	Params()
	{
	}

	struct Param
	{
		enum Mode
		{
			LINJ,
			POW2,
			POWX,
			INTEGER // linear, integers only
		};

		Param( u32 w, u32 h, const char* name, const char* unit, float* ctrl, Mode m = LINJ, float mv = .5f, float r = .5f, bool* dirty_flag = 0);
		void Reset();

		float SliderToRange( float s ) const;
		float RangeToSlider( float r ) const;

		// this is the real value like time in seconds or whatever this param controls
		void SetValueFromRangeString( const std::string& stream );
		void SetValueFromRange( float range );

		// this is from the linear slider value
		void SetValueFromSlider( float v );
		void GetDisplay( char* s ) const;
		float GetSliderValue() const;

        // this is the value that the float had when the param was created...
        float GetDefaultRangeValue() const;
        float GetDefaultSliderValue() const;

		float GetRangeValue() const;
		void GetRangeValueString( std::stringstream& str ) const;

		void GetShortName( char* s ) const;
		const std::string& GetLongName() const;
		void GetUnit( char* s ) const;
		void SetEnums( const char* s, void* dc = 0);
		const char* GetEnum( u32 i ) const;
		const std::string& GetShortName() const;
		const std::string& GetUnit() const;

		Mode GetMode() const { return mode_; }
		float GetRange() const { return range_; }
		float GetMid() const { return mid_value_; }

		u32 screenw_;
		u32 screenh_;

        // calculated
        u32 screenx_;
        u32 screeny_;

	private:
		std::string short_name_;
		std::string long_name_;
		std::string unit_;
		std::vector<std::string> enums_;
		float slider_pos_;
		float* ctrl_;
		Mode mode_;
		float mid_value_;
		float range_;
		bool* dirty_flag_; // set to true whenever value changes...

		float original_value_; // for resetting the state
	};

	std::vector<Param> data;

    enum LayoutDirectiveType
    {
        LAYOUT_HGROUP_BEGIN,
        LAYOUT_VGROUP_BEGIN,
        LAYOUT_GROUP_END,
        LAYOUT_MAKE_SPACE, // used to make room for display stuff or just to add padding
        LAYOUT_LABEL // will translate into a string on screen
    };

    // -----------------------------------------------------------------------------------

    struct LayoutDirective
    {
        LayoutDirective()
        {
            place_ = 0;
            type_ = LAYOUT_HGROUP_BEGIN;
            w_ = 1;
            h_ = 1;
        }

        u32 place_; // after what parameter
        LayoutDirectiveType type_;
        std::string name_; // to be able to find it
        u32 w_;
        u32 h_;

        // calculated
        u32 x_;
        u32 y_;
    };

    void AddLayoutDirective( LayoutDirectiveType t, const std::string& n, u32 w = 0, u32 h = 0 )
    {
        LayoutDirective l;
        l.place_ = data.size();
        l.type_ = t;
        l.name_ = n;
        l.w_ = w;
        l.h_ = h;
        layout.push_back( l );
    }

  	std::vector<LayoutDirective> layout;

	void Reset();
    bool Validate(); // make sure names are unique
};

#endif
