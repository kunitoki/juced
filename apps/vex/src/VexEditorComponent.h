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

   @author  rockhardbuns
   @tweaker Lucio Asnaghi

 ==============================================================================
*/

#ifndef __JUCETICE_VEXPLUGINEDITOR_HEADER__
#define __JUCETICE_VEXPLUGINEDITOR_HEADER__

#include "StandardHeader.h"
#include "VexFilter.h"
#include "PeggyViewComponent.h"

#include "gui/SnappingSlider.h"
#include "resources/Resources.h"
#include "lookandfeel/MyLookAndFeel.h"


class VexEditorComponent : public ComboBoxListener,
						   public SliderListener,
						   public ButtonListener,
						   public ChangeListener,
						   public AudioProcessorEditor
{
public:

    VexEditorComponent (VexFilter* const ownerFilter);
    ~VexEditorComponent();

    void changeListenerCallback (void* source);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void buttonClicked (Button* buttonThatWasClicked);

    void paint (Graphics& g);
    void resized();

	juce_UseDebuggingNewOperator

private:

    void updateParametersFromFilter(bool all);

	ComboBox* comboBox;
    ComboBox* comboBox2;
    ComboBox* comboBox3;

    SnappingSlider* sliders[89];  

    TextButton* TB;
    TextButton* TB2;
    TextButton* TB3;
    TextButton* TB4;
    TextButton* TB5;
    TextButton* TB6;
    Image* internalCachedImage1;

	PeggyViewComponent* p1;
	PeggyViewComponent* p2;
	PeggyViewComponent* p3;

	MyLookAndFeel mlaf;

    VexFilter* getFilter() const throw()       { return (VexFilter*) getAudioProcessor(); }
};

#endif

