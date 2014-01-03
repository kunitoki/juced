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

#include "NoteMapHandler.h"
#include "NoteMapKeyboard.h"
#include "ChannelSelector.h"

NoteMapHandler::NoteMapHandler (SixteenChannelMaps& allMaps)
    : channelMaps (allMaps)
{
    const int border = 10;

    const int inKeyX = border;
    const int inKeyY = border + 30;
    const int keyW = 130;
    const int keyH = 40;
    const int keyGap = 20;

    const int chW = keyW-40;
    const int chH = 80;
    const int inChX = inKeyX+20;
    const int inChY = inKeyY + keyH + keyGap;

    const int listX = inKeyX + keyW + keyGap;
    const int listY = border;
    const int listW = 130;
    const int listH = 192;

    const int outKeyX = listX + listW + keyGap;
    const int outKeyY = inKeyY;

    const int outChX = outKeyX + 20;
    const int outChY = inChY;

    const int totalW = outKeyX + keyW + border;
    const int totalH = border + listH + border;

    const float whiteKeyW = (keyW-25) / 7.0f;

    octaveMiddleC = 3;

    inputKeys = new NoteMapKeyboard (this, true);
    addAndMakeVisible (inputKeys);
    outputKeys = new NoteMapKeyboard (this, false);
    addAndMakeVisible (outputKeys);
    mapList = new ListBox (T("MapList"), this);
    addAndMakeVisible (mapList);

    inputChannel = new ChannelSelector;
    addAndMakeVisible (inputChannel);
    inputChannel->addChangeListener (this);
    outputChannel = new ChannelSelector;
    addAndMakeVisible (outputChannel);
    outputChannel->addChangeListener (this);

    setSize (totalW, totalH);

    inputKeys->setKeyWidth (whiteKeyW);
    outputKeys->setKeyWidth (whiteKeyW);
    inputKeys->setBounds (inKeyX, inKeyY, keyW, keyH);
    outputKeys->setBounds (outKeyX, outKeyY, keyW, keyH);
    inputChannel->setBounds (inChX, inChY, chW, chH);
    outputChannel->setBounds (outChX, outChY, chW, chH);
    mapList->setBounds (listX, listY, listW, listH);
    mapList->setRowHeight (listH / 12);

    setMap (&(channelMaps.getMapForChannel (1)));
    mapList->selectRow (0);
}

NoteMapHandler::~NoteMapHandler ()
{
    deleteAllChildren ();
}

void NoteMapHandler::paintOverChildren (Graphics& g)
{
// g.setColour (Colours::lightgrey);
// g.drawLine (215,10,215,getHeight()-10,2.0f);
}

void NoteMapHandler::paint (Graphics& g)
{
//    GradientBrush b (Colours::darkgrey.darker (0.8f),0,0,Colours::lightgrey,340,0,false);
//    g.setBrush (&b);
//    g.fillRect (0,0,300,212);
//    g.setBrush (0);

    g.fillAll (Colours::grey);

    g.setColour (Colours::black);
    g.fillRoundedRectangle (10,10,130,20,10.0f);
    g.fillRoundedRectangle (310,10,130,20,10.0f);
    g.setColour (Colours::white.withAlpha (0.5f));
    g.drawRoundedRectangle (10,10,130,20,10.0f,1.0f);
    g.drawRoundedRectangle (310,10,130,20,10.0f,1.0f);

    g.setColour (Colours::white);
    g.setFont (Font(15.0f));
    g.drawFittedText (T("Input"),10,10,130,20, Justification::centred, 1);
    g.drawFittedText (T("Output"),310,10,130,20, Justification::centred, 1);

//    g.setColour (Colours::lightgrey.withAlpha (0.5f));
//    g.setFont (Font (11.0f));
//    g.drawFittedText (T("xhMidiNoteMap VST"),310,190,130,20,Justification::centredRight, 1);
}

void NoteMapHandler::resized ()
{
}

void NoteMapHandler::setMap (NoteMap* mapToDisplay)
{
    map = mapToDisplay;
    mapList->updateContent ();
}

NoteMap* NoteMapHandler::getMap ()
{
    return map;
}

void NoteMapHandler::paintListBoxItem (int row, Graphics& g, int w, int h, bool selected)
{
    if (map)
    {
        g.setFont (Font(11.0f));
        String inName = MidiMessage::getMidiNoteName (row, true,true,octaveMiddleC);
        String inCh = String(inputChannel->getSelectedChannel ());
        String outName = MidiMessage::getMidiNoteName (map->getOutputNoteFor (row), true,true,octaveMiddleC);
        String outCh = String(map->getOutputChannelFor (row));
        if (inName.contains (T("#")))
        {
            g.setColour (Colours::darkgrey);
            g.fillRect  (0,0,w/2,h);
            g.setColour (Colours::white);
        }
        else g.setColour (Colours::black);
        g.drawFittedText (inName,20,0,w/2-20,h,Justification::centred,1);
        g.drawFittedText (inCh,0,0,20,h,Justification::centred,1);

        if (outName.contains (T("#")))
        {
            g.setColour (Colours::darkgrey);
            g.fillRect  (w/2,0,w/2,h);
            g.setColour (Colours::white);
        }
        else g.setColour (Colours::black);
        g.drawFittedText (outName,w/2,0,w/2-20,h,Justification::centred,1);
        g.drawFittedText (outCh,w-20,0,20,h,Justification::centred,1);

        if (selected) g.fillAll (Colours::orange.withAlpha (0.3f));
    }
}

int NoteMapHandler::getNumRows () { return 128; }

void NoteMapHandler::selectedRowsChanged (int row)
{
    currentInputNote = row;
    outputChannel->selectChannel (map->getOutputChannelFor (currentInputNote));
}

void NoteMapHandler::selectedInputNoteChanged (int newNote)
{
    float p = mapList->getRowHeight () * 128.0f;
    // find octave base for note...
    int octBase = (int) (newNote / 12) * 12;
    p = (octBase * 12 * 128.0f) / p;
//    mapList->setVerticalPosition (p);

    mapList->scrollToEnsureRowIsOnscreen (octBase + 12);
    mapList->scrollToEnsureRowIsOnscreen (octBase);

    currentInputNote = newNote;
    mapList->selectRow (newNote, true);

    outputChannel->selectChannel (map->getOutputChannelFor (currentInputNote));
}

int NoteMapHandler::getSelectedInputNote ()
{
    return currentInputNote;
}

void NoteMapHandler::outputNoteChanged (int newNote)
{
    if (map)
    {
        map->setOutputNoteFor (
            currentInputNote,
            newNote);
        mapList->updateContent ();
    }
}

MidiKeyboardState& NoteMapHandler::getKeyboardState (bool forInput)
{
    if (forInput) return inputState;
    else return outputState;
}

void NoteMapHandler::changeListenerCallback (void* src)
{
    if (src == inputChannel)
    {
        // change the map in use...
        setMap (&(channelMaps.getMapForChannel (inputChannel->getSelectedChannel ())));
        selectedInputNoteChanged (currentInputNote);
    }
    else if (src == outputChannel)
    {
        // set the output channel of the current input note...
        map->setOutputChannelFor (
            currentInputNote,
            outputChannel->getSelectedChannel ());

        mapList->updateContent ();
        mapList->repaint ();
    }
}
