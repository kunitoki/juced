/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2009 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2007 by Julian Storer.

 ------------------------------------------------------------------------------

 JUCE and JUCETICE can be redistributed and/or modified under the terms of
 the GNU General Public License, as published by the Free Software Foundation;
 either version 2 of the License, or (at your option) any later version.

 JUCE and JUCETICE are distributed in the hope that they will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with JUCE and JUCETICE; if not, visit www.gnu.org/licenses or write to
 Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 Boston, MA 02111-1307 USA

 ==============================================================================

	original author: Michel Wassink (See copyright below for more details)
	juce version:    Arlen Albert Keshabyan (ptomaine)
    tweaker:         Asnaghi Lucio (kRAkEn/gORe)

 ==============================================================================
*/

#ifndef __JUCETICE_DIGITALDISPLAYCOMPONENT_HEADER__
#define __JUCETICE_DIGITALDISPLAYCOMPONENT_HEADER__

#if 0

#include "../../../gui/components/controls/juce_Label.h"

class CDigiChar;

//==============================================================================
class DigitalDisplayComponent : public Label
{
public:

	enum
	{
		DS_SMOOTH	=  1,	// Pioneer kind of characters
		DS_STYLE14	=  2,	// use allways 14 segment display.
		DS_SZ_PROP	=  4,	// size proportional(default)
		DS_NO_OFF	=  8,	// Don't draw the off segments
		DS_SOFT		= 16	// ambient bleeding to background
	};

	DigitalDisplayComponent (const String &componentName, const String &labelText);
	~DigitalDisplayComponent ();

	void setColours (const Colour &OffColor, const Colour &OnColor);

	Colour getOnColour() const
	{
		return m_OnColor;
	}

	Colour getOffColour() const
	{
		return m_OffColor;
	}

	Colour			 setBackgrondColour (const Colour &BackColor = Colours::black);
	bool			 modifyDigiStyle (int32 dwRemove, int32 dwAdd);
	void			 setTransparent (bool bSet = true);
	void			 setMakeStroke (bool makeStroke);

	void 			 paint (Graphics &gc);
	void             textHasChanged ();

protected:

	CDigiChar*		 defineChar (tchar cChar);

	OwnedArray<CDigiChar> m_CharArray;		// digistatic is an array of characters
	Colour			      m_OffColor;		// Color of segment when off
	Colour			      m_OnColor;		// Color of segment when on
	Colour			      m_BackColor;		// Background color
	int32			      m_DispStyle;		// DS_... may be bitwise OR-red
	bool	              m_bTransparent;	// Enable/Disable transparent background
	bool			      m_bMakeStroke;

};

#endif

#endif

/*
 ==============================================================================

	Original Author

	Copyright (C) 2000 by Michel Wassink
	All rights reserved

	This is free software.
	This code may be used in compiled form in any way you desire. This
	file may be redistributed unmodified by any means PROVIDING it is
	not sold for profit without the authors written consent, and
	providing that this notice and the authors name and all copyright
	notices remains intact. If the source code in this file is used in
	any  commercial application then a statement along the lines of
	"Portions Copyright (c) 2002 Michel Wassink" must be included in
	the startup banner, "About" box or printed documentation. An email
	letting me know that you are using it would be nice as well. That's
	not much to ask considering the amount of work that went into this.

	No warrantee of any kind, expressed or implied, is included with this
	software; use at your own risk, responsibility for damages (if any) to
	anyone resulting from the use of this software rests entirely with the
	user.

	Send bug reports, bug fixes, enhancements, requests, flames, etc., and
	I'll try to keep a version up to date.  I can be reached as follows:
        micways@hotmail.com	                (private site)
	An email letting me know that you are using it would be nice.

 ==============================================================================
 */

