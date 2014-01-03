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

#include "MidiNoteMapEditor.h"
#include "NoteMapHandler.h"

//==============================================================================
MidiNoteMapEditor::MidiNoteMapEditor (MidiNoteMapFilter* const ownerFilter)
    : AudioProcessorEditor (ownerFilter)
{
    noteMapHandler = new NoteMapHandler (getFilter()->getChannelMaps ());
    addAndMakeVisible (noteMapHandler);

    ownerFilter->addChangeListener (this);

    setSize (noteMapHandler->getWidth(), noteMapHandler->getHeight());
}

MidiNoteMapEditor::~MidiNoteMapEditor()
{
    getFilter()->removeChangeListener (this);

    deleteAllChildren();
}

//==============================================================================
void MidiNoteMapEditor::paint (Graphics& g)
{
//    g.fillAll (Colours::darkgrey);
}

void MidiNoteMapEditor::resized()
{
}

//==============================================================================
void MidiNoteMapEditor::changeListenerCallback (void* source)
{
    if (source == getFilter())
    {
        // if it's the filter telling us that it's changed, we should update our
        // display of the time, midi message, etc.
        updateParametersFromFilter();
    }
}

void MidiNoteMapEditor::buttonClicked (Button* button)
{
}

//==============================================================================
void MidiNoteMapEditor::updateParametersFromFilter()
{
#if 0
    MidiNoteMapFilter* const filter = getFilter();

    // we use this lock to make sure the processBlock() method isn't writing to the
    // lastMidiMessage variable while we're trying to read it, but be extra-careful to
    // only hold the lock for a minimum amount of time..
    filter->getCallbackLock().enter();

    // ..release the lock ASAP
    filter->getCallbackLock().exit();
#endif
}
