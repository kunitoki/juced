/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2008 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2008 by Julian Storer.

 ------------------------------------------------------------------------------

 JUCE and JUCETICE can be redistributed and/or modified under the terms of
 the GNU Lesser General Public License, as published by the Free Software
 Foundation; either version 2 of the License, or (at your option) any later
 version.

 JUCE and JUCETICE are distributed in the hope that they will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with JUCE and JUCETICE; if not, visit www.gnu.org/licenses or write to
 Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 Boston, MA 02111-1307 USA

 ==============================================================================

   @author  haydxn
   @tweaker Lucio Asnaghi

 ==============================================================================
*/

#ifndef __JUCETICE_NOTEMAPKEYBOARD_HEADER__
#define __JUCETICE_NOTEMAPKEYBOARD_HEADER__

#include "StandardHeader.h"
#include "NoteMap.h"
#include "NoteMapHandler.h"

class NoteMapKeyboard	:	public MidiKeyboardComponent
{
public:

	NoteMapKeyboard (NoteMapHandler* mapHandler, bool input)
		:	MidiKeyboardComponent (
						mapHandler->getKeyboardState (input),
						MidiKeyboardComponent::horizontalKeyboard),
			isInput (input),
			handler (mapHandler)
	{
		shouldOutputNotes = true;
//		setColours (Colours::orange.brighter (), Colours::orange, Colours::darkgrey, Colours::lightgrey);
	}

	bool mouseDownOnKey (int note, const MouseEvent& e)
	{
		if (isInput)
		{
			// This is the input keyboard, and clicking a note here
			// should select a note in the list. This is done by the
			// editor component, which listens for changes here.
			handler->selectedInputNoteChanged (note);
		}
		else
		{
			// This is the output keyboard; clicking a note here
			// should set the currently selected input note's
			// target output note.
			handler->outputNoteChanged (note);
		}
		return shouldOutputNotes;
	}

	void setMap (NoteMap* mapToUse)
	{
		map = mapToUse;
	}

	const String getWhiteNoteText (const int midiNoteNumber)
	{
		if (midiNoteNumber % 12 == 0)
			return T("C") + String (midiNoteNumber / 12 + 1 - handler->octaveMiddleC);

		return String::empty;
	}

private:

	bool isInput;
	bool shouldOutputNotes;

	NoteMap* map;
	NoteMapHandler* handler;

};

#endif//_NOTEMAPKEYBOARD_H_
