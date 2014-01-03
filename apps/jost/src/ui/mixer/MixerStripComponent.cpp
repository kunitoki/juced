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

#include "MixerStripComponent.h"
#include "../../HostFilterComponent.h"


//==============================================================================
MixerStripComponent::MixerStripComponent (HostFilterComponent* owner_,
                                          MixerComponent* mixer_,
                                          BasePlugin* plugin_)
  : owner (owner_),
    mixer (mixer_),
    plugin (plugin_),
    narrow (false),
    peakMode (true)
{
    setOpaque (true);

    Config* config = Config::getInstance ();

    // meter and scale !
    addAndMakeVisible (meter = new HighQualityMeter (1));
    addAndMakeVisible (scale = new DecibelScaleComponent ());

    // label !
    addAndMakeVisible (dynamicLabel = new Label (String::empty, String::empty));
    dynamicLabel->setFont (Font (12.0f, Font::plain));
    dynamicLabel->setJustificationType (Justification::centred);
    dynamicLabel->setEditable (false, true, true);
    dynamicLabel->addListener (this);

    String mixerLabel = plugin->getValue (PROP_MIXERLABEL);
    mixerLabel = (mixerLabel != String::empty) ? mixerLabel : plugin->getName ();
    dynamicLabel->setText (mixerLabel, true);

    // volume slider !
    addAndMakeVisible (volumeSlider = new ImageSlider (String::empty));
    volumeSlider->setOrientation (ImageSlider::LinearVertical);
    volumeSlider->setRange (0.000001, 1.25, 0.000001);
    volumeSlider->setSkewFactor (0.5f);
    volumeSlider->setSliderStyle (Slider::LinearVertical);
    volumeSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
//    volumeSlider->setVelocityBasedMode (true);
//    volumeSlider->setVelocityModeParameters (/*sensitivity*/1.0, /*threshold*/ 1, /*offset*/ 0.0);
    volumeSlider->setValue (plugin->getOutputGain (), false);
    volumeSlider->addListener (this);

    // pan slider !
    addAndMakeVisible (panSlider = new Slider (String::empty));
    panSlider->setRange (0, 1, 0.0001);
    panSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    panSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    panSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    panSlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x8cffffff));
//    panSlider->setValue (plugin->getOutputPanning (), false);
    panSlider->setValue (0.5f);
    panSlider->addListener (this);
    panSlider->setEnabled (false);

    // buttons !
    addAndMakeVisible (muteButton = new ToggleButton (String::empty));
    muteButton->setColour (TextButton::buttonColourId, config->getColour ("mixerMuteButton", Colour (0xffff0000)));
    muteButton->addButtonListener (this);

    addAndMakeVisible (bypassButton = new ToggleButton (String::empty));
    bypassButton->setColour (TextButton::buttonColourId, config->getColour ("mixerBypassButton", Colour (0xfffdf002)));
    bypassButton->addButtonListener (this);
    if (plugin->getType () == JOST_PLUGINTYPE_INPUT || plugin->getType () == JOST_PLUGINTYPE_OUTPUT) // TODO - keep out !
        bypassButton->setEnabled (false);

    addAndMakeVisible (soloButton = new ToggleButton (String::empty));
    soloButton->setColour (TextButton::buttonColourId, config->getColour ("mixerSoloButton", Colour (0xff148cdc)));
    soloButton->addButtonListener (this);
    soloButton->setEnabled (false);

    // properties
    peakMode = plugin->getIntValue (PROP_MIXERPEAK) == 1 ? true : false;
    setNarrow (plugin->getIntValue (PROP_MIXERNARROW) == 1 ? true : false);

    muteButton->setToggleState (plugin->isMuted (), false);
    bypassButton->setToggleState (plugin->isBypass (), false);
    meter->setEnabled (plugin->getIntValue (PROP_MIXERMETERON) == 1 ? true : false);
}

MixerStripComponent::~MixerStripComponent()
{
    deleteAllChildren ();
}

//==============================================================================
void MixerStripComponent::setNarrow (const bool wantsNarrow)
{
    narrow = wantsNarrow;

    if (narrow)
    {
        muteButton->setButtonText ("M");
        bypassButton->setButtonText ("B");
        soloButton->setButtonText ("S");
    }
    else
    {
        muteButton->setButtonText ("mute");
        bypassButton->setButtonText ("bypass");
        soloButton->setButtonText ("solo");
    }

    plugin->setValue (PROP_MIXERNARROW, narrow ? 1 : 0);

    mixer->resized ();
}


//==============================================================================
void MixerStripComponent::paint (Graphics& g)
{
    Colour backgroundColour = Config::getInstance ()->getColour ("mainBackground");

    g.setGradientFill (ColourGradient(backgroundColour.brighter (0.25f),
                                      0, 0,
                                      backgroundColour.darker (0.25f),
                                      0, getHeight (),
                                      false));
    g.fillAll ();

    g.drawBevel (0, 0, getWidth (), getHeight (), 1,
                 Colours::white.withAlpha (0.2f),
                 Colours::black.withAlpha (0.2f));
}

void MixerStripComponent::resized ()
{
    int panWidth = narrow ? 22 : 32;
    int panHeight = narrow ? 22 : 32;

    int volWidth = narrow ? 15 : 15;
    int volHeight = 127;

    int meterWidth = 6;
    int labelHeight = 14;

    int remainingWidth = (getWidth () - volWidth) / 2;

    int offsetY = (getHeight () - volHeight - labelHeight + 4);
    int totalHeight = volHeight - 7;

    int buttonsHeight = 16;
    int buttonsOffset = (getHeight () - volHeight - panHeight - labelHeight) - 5;

    muteButton->setBounds (0, buttonsOffset - buttonsHeight * 3, getWidth (), buttonsHeight);

    bypassButton->setBounds (0, buttonsOffset - buttonsHeight * 2, getWidth (), buttonsHeight);

    soloButton->setBounds (0, buttonsOffset - buttonsHeight * 1, getWidth (), buttonsHeight);

    panSlider->setBounds ((getWidth () - panWidth) / 2,
                          (getHeight () - volHeight - panHeight - labelHeight),
                          panWidth,
                          panHeight);

    volumeSlider->setBounds (remainingWidth,
                             (getHeight () - volHeight - labelHeight),
                             volWidth,
                             volHeight);

    dynamicLabel->setBounds (0,
                             getHeight () - labelHeight,
                             getWidth (),
                             labelHeight);

    if (narrow)
    {
        meter->setVisible (false);

        scale->setBounds (1,
                          offsetY,
                          remainingWidth * 2,
                          totalHeight);
    }
    else
    {
        meter->setVisible (true);

        scale->setBounds (2,
                          offsetY,
                          remainingWidth,
                          totalHeight);

        meter->setBounds ((getWidth () - remainingWidth) + (remainingWidth - meterWidth) / 2,
                          offsetY,
                          meterWidth,
                          totalHeight);
    }
    
//     draggerConstraint.setMinimumOnscreenAmounts (getHeight(),getWidth(),getHeight(),getWidth());
}

//==============================================================================
void MixerStripComponent::mouseDown (const MouseEvent& e)
{
    if (e.mods.isRightButtonDown ())
    {
        PopupMenu mainMenu;
        if (! owner->isPluginEditorWindowOpen (plugin))
            mainMenu.addItem (1, "Open editor");
        if (owner->isPluginEditorWindowOpen (plugin))
            mainMenu.addItem (2,  "Close editor");

        PopupMenu meterMenu;
        meterMenu.addItem (9, "Enable", true, meter->isEnabled ());
        meterMenu.addItem (10, "Peak mode", true, peakMode);

        mainMenu.addSeparator ();
        mainMenu.addSubMenu ("Meter", meterMenu);

        const int result = mainMenu.show();
        switch (result)
        {
        case 1:
            owner->openPluginEditorWindow (plugin);
            break;
        case 2:
            owner->closePluginEditorWindow (plugin);
            break;
        case 9:
            meter->setEnabled (! meter->isEnabled ());
            plugin->setValue (PROP_MIXERMETERON, meter->isEnabled () ? 1 : 0);
            break;
        case 10:
            peakMode = ! peakMode;
            plugin->setValue (PROP_MIXERPEAK, peakMode ? 1 : 0);
            break;
        default:
            break;
        }
    }
    else if (e.mods.isLeftButtonDown())
    {
        // dragger.startDraggingComponent (this, &draggerConstraint);
    }
}

void MixerStripComponent::mouseDrag (const MouseEvent& e)
{
    // if (e.mods.isLeftButtonDown())
    //    dragger.dragComponent (this, e);
}

void MixerStripComponent::mouseDoubleClick (const MouseEvent& e)
{
    if (e.mods.isLeftButtonDown ())
    {
        setNarrow (! narrow);
    }
}

//==============================================================================
void MixerStripComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    if (sliderThatWasMoved == volumeSlider)
    {
        plugin->setOutputGain (sliderThatWasMoved->getValue ());

//        std::cout << (const char*) plugin->getName () << " " << sliderThatWasMoved->getValue () << std::endl;
    }
    else if (sliderThatWasMoved == panSlider)
    {
        plugin->setOutputPanning (sliderThatWasMoved->getValue ());
    }
}

//==============================================================================
void MixerStripComponent::labelTextChanged (Label *labelThatHasChanged)
{
    plugin->setValue (PROP_MIXERLABEL, labelThatHasChanged->getText ());

    dynamicLabel->setText (labelThatHasChanged->getText (), false);
}

//==============================================================================
void MixerStripComponent::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == muteButton)
    {
        const bool isPluginMuted = buttonThatWasClicked->getToggleState ();

        plugin->setMuted (isPluginMuted);

        if (isPluginMuted)
        {
            meter->setValue (0, 0.0f);
            meter->peakReset ();
            meter->refresh ();
        }
    }
    else if (buttonThatWasClicked == bypassButton)
    {
        plugin->setBypass (buttonThatWasClicked->getToggleState ());
    }
    else if (buttonThatWasClicked == soloButton)
    {
        // TODO - ask the parent to solo
    }
}

//==============================================================================
void MixerStripComponent::computeMeters ()
{
    if ((meter->isVisible () && meter->isEnabled ()) && ! plugin->isMuted ())
    {
        AudioSampleBuffer* buffer = plugin->getOutputBuffers ();

        if (buffer && buffer->getNumChannels () > 0)
        {
            float absoluteVal = 0.0f;

            if (peakMode)
                absoluteVal = buffer->getMagnitude (0, buffer->getNumSamples ());
            else
                absoluteVal = buffer->getRMSLevel (0, 0, buffer->getNumSamples ());

            meter->setValue (0, absoluteVal * volumeSlider->getValue ());
            meter->refresh ();
        }
    }
}
