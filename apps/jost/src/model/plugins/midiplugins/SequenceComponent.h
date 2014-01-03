/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2007 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2007 by Julian Storer.

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
*/

#ifndef __JUCETICE_JOSTSUPERSEQUENCECOMPONENT_HEADER__
#define __JUCETICE_JOSTSUPERSEQUENCECOMPONENT_HEADER__

#include "../../../Config.h"
#include "../../../HostFilterComponent.h"
#include "MidiSequencePlugin.h"
#include "../../../ui/plugins/PluginEditorComponent.h"

class NoteEditComponent;
class AutomationEditComponent;

//==============================================================================
/**
    An editor for midi sequence + automation sequence plugin.
*/
class SequenceComponent : public PluginEditorComponent,
                          public Timer,
                          public ChangeListener,
                          public ButtonListener,
                          public ComboBoxListener,
                          public SliderListener,
						  public FileDragAndDropTarget
{
public:
    //==============================================================================
    SequenceComponent (MidiSequencePluginBase* plugin);
    ~SequenceComponent ();

    //==============================================================================
    int getPreferredWidth ()                        { return 580; }
    int getPreferredHeight ()                       { return 390; }
    bool isResizable ()                             { return true; }
    void updateParameters ();

    //==============================================================================
    /** Implemented from SliderListener interface */
    void sliderValueChanged (Slider* sliderThatWasMoved);

    /** Implemented from ButtonListener interface */
    void buttonClicked (Button* buttonThatWasChanged);

    /** Implemented from ComboBoxListener interface */
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);

    /** Implemented from ChangeListener interface */
    void changeListenerCallback (void *objectThatHasChanged);

    //==============================================================================
    virtual bool getMenuBarNames(StringArray& names);
    virtual bool getMenuForMenuName(const String& menuName, PopupMenu& menu);
    virtual void menuItemSelected(const String& menuName, int menuItemID);
                                       
    //==============================================================================
    void importMidiFile();
    void exportMidiFile();
    void importMidiFile(const File& file);
    void exportMidiFile(const File& file);
    void importMidiSequence(const MidiMessageSequence* midiSeq);

    //==============================================================================
    /** @internal */
    void timerCallback ();
    /** @internal */
    void mouseWheelMove (const MouseEvent& e, float incrementX, float incrementY);
    /** @internal */
    void resized ();
    /** @internal */
    void filesDropped (const StringArray &files, int x, int y);
    /** @internal */
    bool isInterestedInFileDrag (const StringArray& files);

protected:

    /** Handy function that returns the type casted plugin */
    MidiSequencePlugin* getPlugin () const        { return (MidiSequencePlugin*) plugin; }

    Transport* transport;

	ToggleButton* enabledButton;

    ImageSlider* zoomSlider;
    Slider* barSlider;

    ComboBox* quantizeBox;
    ComboBox* noteLengthBox;

	StretchableLayoutManager myLayout;
	StretchableLayoutResizerBar* layoutResizer;

	NoteEditComponent* noteEditor;
	AutomationEditComponent* automationEditor;
};


#endif
