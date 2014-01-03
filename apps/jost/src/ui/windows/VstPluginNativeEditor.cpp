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

#include "VstPluginNativeEditor.h"
#include "VstPluginWindow.h"


//==============================================================================
VstPluginNativeEditor::VstPluginNativeEditor (BasePlugin* plugin_,
                                              VstPluginWindow* window_)
  : PluginEditorComponent (plugin_),
    window (window_)
{
    DBG ("VstPluginNativeEditor::VstPluginNativeEditor");

    int size = 18;
    int width = 540;
    int height = 5;
    int labelWidth = 110;
    int displayWidth = 80;

    Colour backgroundColour = window->getBackgroundColour ();

//    ImageSlider* param;
    ParameterSlider* param;
    Label* label;
    
    for (int j = 0; j < plugin->getNumParameters (); j++)
    {
        addAndMakeVisible (label = new Label (String::empty, plugin->getParameterName (j)));
        label->setFont (Font (size * 0.8f, Font::bold));
        label->setJustificationType (Justification::centredLeft);
        label->setEditable (false, false, false);
        label->setColour (TextEditor::textColourId, Colours::white);
        label->setColour (TextEditor::backgroundColourId, backgroundColour);
        label->setBounds (0, 5 + j * size, labelWidth, size - 2);
        names.add (label);

        addAndMakeVisible (param = new ParameterSlider (String (j)));
//        param->setOrientation (ImageSlider::LinearHorizontal);
        param->setRange (0, 1, 0.0001);
        param->setValue (plugin->getParameter (j));
        param->setSliderStyle (Slider::LinearBar); // LinearHorizontal
        param->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
        param->addListener (this);
        param->setBounds (labelWidth, 5 + j * size, width - labelWidth - displayWidth, size - 2);
        sliders.add (param);

        addAndMakeVisible (label = new Label (String::empty, plugin->getParameterText (j)));
        label->setFont (Font (size * 0.8f, Font::plain));
        label->setJustificationType (Justification::centredLeft);
        label->setEditable (false, false, false);
        label->setColour (TextEditor::textColourId, Colours::white);
        label->setColour (TextEditor::backgroundColourId, backgroundColour);
        label->setBounds (width - displayWidth, 5 + j * size, displayWidth - 20, size - 2);
        labels.add (label);

        height += size;
    }

    height += 5;

    // set its size
    setSize (width, height);

    // remember original sizes
    preferredWidth = width;
    preferredHeight = height;

    // attach parameters !
    plugin->getParameterLock().enter ();
    for (int j = 0; j < plugin->getNumParameters (); j++)
    {
        plugin->addListenerToParameter (j, sliders.getUnchecked (j));
        plugin->addListenerToParameter (j, this);
    }
    plugin->getParameterLock().exit ();
}

VstPluginNativeEditor::~VstPluginNativeEditor ()
{
    DBG ("VstPluginNativeEditor::~VstPluginNativeEditor");

    // detach parameters !
    plugin->getParameterLock().enter ();
    for (int j = 0; j < plugin->getNumParameters (); j++)
    {
        plugin->removeListenerToParameter (j, sliders.getUnchecked (j));
        plugin->removeListenerToParameter (j, this);
    }
    plugin->getParameterLock().exit ();

    deleteAllChildren();
}

//==============================================================================
void VstPluginNativeEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    int paramNumber = sliderThatWasMoved->getName ().getIntValue ();

    if (plugin)
    {
        plugin->setParameter (paramNumber, sliderThatWasMoved->getValue ());

        Label* label = labels[paramNumber];
        if (label) {
            label->setText (plugin->getParameterText (paramNumber), false);
        }
    }
}

void VstPluginNativeEditor::parameterChanged (AudioParameter* parameter, const int index)
{
    if (plugin)
    {
        Label* label = labels[index];
        if (label) {
            label->setText (plugin->getParameterText (index), false);
        }
    }
}

//==============================================================================
void VstPluginNativeEditor::paint (Graphics& g)
{
    g.fillAll (window->getBackgroundColour ());
}

//==============================================================================
int VstPluginNativeEditor::getPreferredWidth ()
{
    return preferredWidth;
}

int VstPluginNativeEditor::getPreferredHeight ()
{
    return preferredHeight;
}

bool VstPluginNativeEditor::isResizable ()
{
    return true;
}

//==============================================================================
void VstPluginNativeEditor::updateParameters ()
{
    DBG ("VstPluginNativeEditor::updateParameters");

    if (plugin)
    {
        for (int i = 0; i < plugin->getNumParameters (); i++)
        {
            String paramNumber = String (i);

            ParameterSlider* slider = sliders [i];
            if (slider) {
                slider->setValue (plugin->getParameter (i), false);
            }

            Label* label = labels[i];
            if (label) {
                label->setText (plugin->getParameterText (i), false);
            }
        }
    }
}


