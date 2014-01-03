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

#include "xMonEditor.h"

//==============================================================================
DemoEditorComponent::DemoEditorComponent (DemoJuceFilter* const ownerFilter)
    : AudioProcessorEditor (ownerFilter)
{
    // add the triangular resizer component for the bottom-right of the UI
    addAndMakeVisible (resizer = new ResizableCornerComponent (this, &resizeLimits));
    resizeLimits.setSizeLimits (150, 150, 800, 800);

	addAndMakeVisible (midiOutputEditor = new TextEditor (String::empty));
	midiOutputEditor->setReadOnly(true);
	midiOutputEditor->setMultiLine (true, true);

    // set our component's initial size to be the last one that was stored in the filter's settings
    setSize (ownerFilter->lastUIWidth,
             ownerFilter->lastUIHeight);

    // register ourselves with the filter - it will use its ChangeBroadcaster base
    // class to tell us when something has changed, and this will call our changeListenerCallback()
    // method.
    ownerFilter->addChangeListener (this);
}

DemoEditorComponent::~DemoEditorComponent()
{
    getFilter()->removeChangeListener (this);

    deleteAllChildren();
}

//==============================================================================
void DemoEditorComponent::paint (Graphics& g)
{
    // just clear the window
    g.fillAll (Colour::greyLevel (0.9f));
}

void DemoEditorComponent::resized()
{
	midiOutputEditor->setBounds (16, 16, getWidth() - 32, getHeight() - 16 - 35);

    resizer->setBounds (getWidth() - 16, getHeight() - 16, 16, 16);

    // if we've been resized, tell the filter so that it can store the new size
    // in its settings
    getFilter()->lastUIWidth = getWidth();
    getFilter()->lastUIHeight = getHeight();
}

//==============================================================================
void DemoEditorComponent::changeListenerCallback (void* source)
{
    // this is the filter telling us that it's changed, so we'll update our
    // display of the time, midi message, etc.
    updateParametersFromFilter();
}


//==============================================================================
void DemoEditorComponent::updateParametersFromFilter()
{
	MidiBuffer tmpBuffer;
	String strTmp;
	String data;

    DemoJuceFilter* const filter = getFilter();

    // we use this lock to make sure the processBlock() method isn't writing to the
    // lastMidiMessage variable while we're trying to read it, but be extra-careful to
    // only hold the lock for a minimum amount of time..
    filter->getCallbackLock().enter();

	tmpBuffer = filter->incomingMidiMessages;

    // ..release the lock ASAP
    filter->getCallbackLock().exit();

	if (!tmpBuffer.isEmpty())
	{
		const uint8* midiEventData;
		int midiEventSize, midiEventPosition;
		MidiBuffer::Iterator i (tmpBuffer);

		if (!tmpBuffer.isEmpty())
		{
			while (i.getNextEvent (midiEventData, midiEventSize, midiEventPosition))
			{
				strTmp.printf (T("[%d] - 0x"), midiEventSize);

				for (int x=0; x<midiEventSize; x++)
				{
					if (x==0)
						data.printf (T("%.2x"), midiEventData[x]);
					else
						data.printf (T(":%.2x"), midiEventData[x]);

					strTmp = strTmp + data;
				}

				midiOutputEditor->insertTextAtCursor (strTmp + T("\n"));
			}
		}
	}
    setSize (filter->lastUIWidth,
             filter->lastUIHeight);
}

