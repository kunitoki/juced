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

#ifndef __JUCETICE_JOST_VSTPLUGINNATIVEEDITOR_HEADER__
#define __JUCETICE_JOST_VSTPLUGINNATIVEEDITOR_HEADER__

#include "../plugins/PluginEditorComponent.h"


class VstPluginWindow;


//==============================================================================
class VstPluginNativeEditor : public PluginEditorComponent,
                              public AudioParameterListener,
                              public SliderListener
{
public:

    //==============================================================================
    /** Constructor for native GUI */
    VstPluginNativeEditor (BasePlugin* plugin_,
                           VstPluginWindow* parent_);

    /** Destructor */
    ~VstPluginNativeEditor ();

    //==============================================================================
    /** SliderListener method

        Since we have this editor part of a series of sliders, we need to respond
        to these sliders in order to set parameters for our plugin.
    */
    void sliderValueChanged (Slider* sliderThatWasMoved);

    //==============================================================================
    /** Parameter listener callback */
    void parameterChanged (AudioParameter* parameter, const int index);

    //==============================================================================
    /** Paint method */
    void paint (Graphics& g);

    //==============================================================================
    /** Get last width */
    int getLastWidth ();

    /** Get last height  */
    int getLastHeight ();

    //==============================================================================
    int getPreferredWidth ();
    int getPreferredHeight ();
    bool isResizable ();

    /** Someone told us to update the sliders

        Probably there is a preset change command, so we need to update the
        sliders' position.

        TODO - at some point we should make each slider respond to a single update
    */
    void updateParameters ();

protected:

    VstPluginWindow* window;

    Array<Label*> names;
    Array<Label*> labels;
    Array<ParameterSlider*> sliders;
    
    int preferredWidth, preferredHeight;
    int lastWidth, lastHeight;
};

#endif
