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

#ifndef __JUCETICE_NOTEMAPHANDLER_HEADER__
#define __JUCETICE_NOTEMAPHANDLER_HEADER__

#include "StandardHeader.h"
#include "NoteMap.h"

class ChannelSelector;
class NoteMapKeyboard;

class NoteMapHandler	:	public ListBoxModel,
							public Component,
							public ChangeListener
{
public:

	NoteMapHandler (SixteenChannelMaps& allMaps);
	~NoteMapHandler ();

	void paint (Graphics& g);
	void paintOverChildren (Graphics& g);
	void resized ();
	void paintListBoxItem (int row, Graphics& g, int w, int h, bool selected);
	int getNumRows ();


	void setMap (NoteMap* mapToDisplay);
	NoteMap* getMap ();

	void selectedRowsChanged (int row);
	void selectedInputNoteChanged (int newNote);
	int getSelectedInputNote ();
	void outputNoteChanged (int newNote);

	void changeListenerCallback (void* src);

	friend class NoteMapKeyboard;

private:

	MidiKeyboardState& getKeyboardState (bool forInput);

	NoteMap* map;
	SixteenChannelMaps& channelMaps;

	NoteMapKeyboard* inputKeys;
	NoteMapKeyboard* outputKeys;

	MidiKeyboardState inputState;
	MidiKeyboardState outputState;

	ChannelSelector* inputChannel;
	ChannelSelector* outputChannel;

	int currentInputNote;

	int octaveMiddleC;

	ListBox* mapList;
};

#endif//_NOTEMAPHANDLER_H_
