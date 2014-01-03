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

#ifndef __JUCETICE_MIDINOTEMAPEDITOR_HEADER__
#define __JUCETICE_MIDINOTEMAPEDITOR_HEADER__

#include "MidiNoteMapFilter.h"
#include "NoteMapHandler.h"

//==============================================================================
/**
    This is the Component that our filter will use as its UI.

    One or more of these is created by the MidiNoteMapFilter::createEditor() method,
    and they will be deleted at some later time by the wrapper code.

    To demonstrate the correct way of connecting a filter to its UI, this
    class is a ChangeListener, and our demo filter is a ChangeBroadcaster. The
    editor component registers with the filter when it's created and deregisters
    when it's destroyed. When the filter's parameters are changed, it broadcasts
    a message and this editor responds by updating its display.
*/
class MidiNoteMapEditor   : public AudioProcessorEditor,
                            public ChangeListener,
                            public ButtonListener
{
public:
    /** Constructor.

        When created, this will register itself with the filter for changes. It's
        safe to assume that the filter won't be deleted before this object is.
    */
    MidiNoteMapEditor (MidiNoteMapFilter* const ownerFilter);

    /** Destructor. */
    ~MidiNoteMapEditor();

    //==============================================================================
    /** Our demo filter is a ChangeBroadcaster, and will call us back when one of
        its parameters changes. We'll also get callbacks here from our Slider object
        when the user moves it.
    */
    void changeListenerCallback (void* source);

    //==============================================================================
    /** Standard Juce paint callback. */
    void paint (Graphics& g);

    /** Standard Juce resize callback. */
    void resized();

    void buttonClicked (Button* button);

private:
    //==============================================================================

    NoteMapHandler* noteMapHandler;

    void updateParametersFromFilter();

    // handy wrapper method to avoid having to cast the filter to a MidiNoteMapFilter
    // every time we need it..
    MidiNoteMapFilter* getFilter() const throw()       { return (MidiNoteMapFilter*) getAudioProcessor(); }
};


#endif
