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

#ifndef __JUCETICE_JOSTMIXERSTRIPCOMPONENT_HEADER__
#define __JUCETICE_JOSTMIXERSTRIPCOMPONENT_HEADER__

#include "../../Config.h"
#include "../../model/Host.h"

class MixerComponent;


//==============================================================================
/**
     A mixer strip component
*/
class MixerStripComponent  : public Component,
                             public SliderListener,
                             public ButtonListener,
                             public LabelListener
{
public:

    //==============================================================================
    MixerStripComponent (HostFilterComponent* owner,
                         MixerComponent* mixer,
                         BasePlugin* plugin);

    ~MixerStripComponent();

    //==============================================================================
    bool isNarrow () const                                    { return narrow; }
    void setNarrow (const bool wantsNarrow);

    //==============================================================================
    void computeMeters ();

    //==============================================================================
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void buttonClicked (Button* buttonThatWasClicked);
    void labelTextChanged (Label *labelThatHasChanged);

    //==============================================================================
    /** @internal */
    void mouseDown (const MouseEvent& e);
    /** @internal */
    void mouseDrag (const MouseEvent& e);
    /** @internal */
    void mouseDoubleClick (const MouseEvent& e);
    /** @internal */
    void paint (Graphics& g);
    /** @internal */
    void resized ();

protected:

    HostFilterComponent* owner;
    MixerComponent* mixer;
    BasePlugin* plugin;

    Label* dynamicLabel;
    ImageSlider* volumeSlider;
    Slider* panSlider;

    ToggleButton* muteButton;
    ToggleButton* bypassButton;
    ToggleButton* soloButton;

    DecibelScaleComponent* scale;
    HighQualityMeter* meter;

    ComponentDragger dragger;
    ComponentBoundsConstrainer draggerConstraint; 

    bool narrow    : 1,
         peakMode  : 1;
};


#endif // __JUCETICE_JOSTMIXERSTRIPCOMPONENT_HEADER__
