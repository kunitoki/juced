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

#include "ToolbarMainComponent.h"
#include "../../Commands.h"
#include "../../resources/Resources.h"
#include "../../HostFilterBase.h"
#include "../../HostFilterComponent.h"


//==============================================================================
MainToolbarTempoSlider::MainToolbarTempoSlider (HostFilterComponent* owner_,
                                                const int toolbarItemId)
  : ToolbarItemComponent (toolbarItemId, T("Tempo"), false),
    owner (owner_)
{
    Transport* transport = owner->getFilter()->getTransport();

    addAndMakeVisible (tempoSlider = new Slider (String::empty));
    tempoSlider->setRange (20, 999, 1);
    tempoSlider->setSliderStyle (Slider::IncDecButtons);
    tempoSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    tempoSlider->setValue (transport->getTempo (), false);
    tempoSlider->setTooltip (T("Tempo"));
    tempoSlider->addListener (this);
    
    addAndMakeVisible (loopLenSlider = new Slider (String::empty));
    loopLenSlider->setRange (1, 999, 1);
    loopLenSlider->setSliderStyle (Slider::IncDecButtons);
    loopLenSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    loopLenSlider->setValue (transport->getNumBars(), false);
    loopLenSlider->setTooltip (T("Loop Length"));
    loopLenSlider->addListener (this);
    
    transport->addChangeListener (this);
}

MainToolbarTempoSlider::~MainToolbarTempoSlider()
{
    Transport* transport = owner->getFilter()->getTransport();
    transport->removeChangeListener (this);

    deleteAndZero (tempoSlider);
}

void MainToolbarTempoSlider::sliderValueChanged (Slider* sliderThatWasMoved)
{
    Transport* transport = owner->getFilter()->getTransport();
    if (sliderThatWasMoved == tempoSlider)
    transport->setTempo (roundFloatToInt (tempoSlider->getValue ()));
	else if (sliderThatWasMoved == loopLenSlider)
		transport->setTimeSignature (transport->getTempo(), loopLenSlider->getValue(), transport->getTimeDenominator());
}

void MainToolbarTempoSlider::changeListenerCallback (void *objectThatHasChanged)
{
    Transport* transport = owner->getFilter()->getTransport();

    DBG ("Setting tempo to: " + String (transport->getTempo ()) + " bpm");

    if (tempoSlider)
        tempoSlider->setValue (transport->getTempo (), false);
    if (loopLenSlider)
        loopLenSlider->setValue (transport->getNumBars(), false);
}

bool MainToolbarTempoSlider::getToolbarItemSizes (int toolbarDepth,
                                                  bool isToolbarVertical,
                                                  int& preferredSize, int& minSize, int& maxSize)
{
    if (isToolbarVertical)
        return false;

    preferredSize = 120;
    minSize = 120;
    maxSize = 120;
    return true;
}

void MainToolbarTempoSlider::paintButtonArea (Graphics&, int, int, bool, bool)
{
}

void MainToolbarTempoSlider::contentAreaChanged (const Rectangle& contentArea)
{
    tempoSlider->setSize ((contentArea.getWidth() / 2) - 2,
                          jmin (contentArea.getHeight() - 2, 22));

    tempoSlider->setCentrePosition (contentArea.getCentreX() - contentArea.getWidth() / 4, contentArea.getCentreY());

    loopLenSlider->setSize ((contentArea.getWidth() / 2) - 2,
                          jmin (contentArea.getHeight() - 2, 22));
	
    loopLenSlider->setCentrePosition (contentArea.getCentreX() + contentArea.getWidth() / 4, contentArea.getCentreY());
}

//==============================================================================
MainToolbarTimeDisplay::MainToolbarTimeDisplay (HostFilterComponent* owner_,
                                                const int toolbarItemId)
  : ToolbarItemComponent (toolbarItemId, T("Display"), false),
    owner (owner_)
{
    Transport* transport = owner->getFilter()->getTransport();

    addAndMakeVisible (digitalDisplay = new Label (String::empty, "001:001:000"));
    digitalDisplay->setFont (Font (Font::getDefaultMonospacedFontName (), 14, Font::plain));
    digitalDisplay->setColour (Label::backgroundColourId, Colours::white);

    transport->addChangeListener (this);
}

MainToolbarTimeDisplay::~MainToolbarTimeDisplay()
{
    Transport* transport = owner->getFilter()->getTransport();
    transport->removeChangeListener (this);

    deleteAndZero (digitalDisplay);
}

void MainToolbarTimeDisplay::changeListenerCallback (void *objectThatHasChanged)
{
    Transport* transport = owner->getFilter()->getTransport();

    if (transport->isPlaying ())
        startTimer (50);
    else
        stopTimer ();

    updateTimeDisplay ();
}

bool MainToolbarTimeDisplay::getToolbarItemSizes (int toolbarDepth,
                                                  bool isToolbarVertical,
                                                  int& preferredSize, int& minSize, int& maxSize)
{
    if (isToolbarVertical)
        return false;

    preferredSize = 84;
    minSize = 84;
    maxSize = 84;
    return true;
}

void MainToolbarTimeDisplay::paintButtonArea (Graphics&, int, int, bool, bool)
{
}

void MainToolbarTimeDisplay::contentAreaChanged (const Rectangle& contentArea)
{
    int width = jmax (0, contentArea.getWidth());
    int height = jmax (0, jmin (contentArea.getHeight(), 18));

    digitalDisplay->setFont (Font (Font::getDefaultMonospacedFontName (), height - 4, Font::plain));

    digitalDisplay->setSize (width, height);
    digitalDisplay->setCentrePosition (contentArea.getCentreX(), contentArea.getCentreY());
}

void MainToolbarTimeDisplay::updateTimeDisplay ()
{
    Transport* t = owner->getFilter()->getTransport();
    
    int positionFrame = t->getPositionInFrames ();
    int framesPerBeat = t->getFramesPerBeat ();
    int denominator = t->getTimeDenominator ();
    // float sampleRate = t->getSampleRate ();

    if (framesPerBeat > 0 && denominator != 0)
    {
        int ticks = (positionFrame % framesPerBeat) / 100;
        int beat = 1 + (positionFrame / framesPerBeat) % denominator;
        int bars = 1 + (positionFrame / framesPerBeat) / denominator;

        digitalDisplay->setText (String::formatted(T("%03d:%03d:%03d"), bars, beat, ticks), false);
    }
    else
    {
        digitalDisplay->setText ("001:001:000", false);
    }
}

void MainToolbarTimeDisplay::timerCallback()
{
	updateTimeDisplay ();
}

//==============================================================================
ToolbarMainItemFactory::ToolbarMainItemFactory (HostFilterComponent* owner_)
  : owner (owner_)
{
}

ToolbarMainItemFactory::~ToolbarMainItemFactory ()
{
}

void ToolbarMainItemFactory::getAllToolbarItemIds (Array <int>& ids)
{
    ids.add (jost_play);
    ids.add (jost_stop);
    ids.add (jost_rec);
    ids.add (jost_rev);
    ids.add (jost_loop);
    ids.add (jost_tempo);
    ids.add (jost_digits);

    ids.add (jost_new);
    ids.add (jost_load);
    ids.add (jost_save);
    ids.add (jost_plugin);
    ids.add (jost_info);
    ids.add (jost_search);

    ids.add (jost_browser);
    ids.add (jost_favorities);
    ids.add (jost_toolbar);
    ids.add (jost_fullscreen);
    ids.add (jost_audio);

    // If you're going to use separators
    ids.add (separatorBarId);
    ids.add (spacerId);
    ids.add (flexibleSpacerId);
}

void ToolbarMainItemFactory::getDefaultItemSet (Array <int>& ids)
{
    // This returns an ordered list of the set of items that make up a
    // toolbar's default set. Not all items need to be on this list, and
    // items can appear multiple times (e.g. the separators used here).
    ids.add (jost_new);
    ids.add (jost_load);
    ids.add (jost_save);
    ids.add (separatorBarId);

    ids.add (jost_plugin);
    ids.add (separatorBarId);

    ids.add (jost_rev);
    ids.add (jost_play);
    ids.add (jost_stop);
    ids.add (jost_rec);
    ids.add (jost_loop);
    ids.add (separatorBarId);

    ids.add (jost_digits);
    ids.add (separatorBarId);

    ids.add (jost_tempo);
    ids.add (separatorBarId);

    ids.add (flexibleSpacerId);

    ids.add (separatorBarId);
    ids.add (jost_fullscreen);
    ids.add (jost_favorities);
    ids.add (jost_browser);
    ids.add (jost_toolbar);
    ids.add (jost_audio);

    ids.add (separatorBarId);
    ids.add (jost_info);
}

ToolbarItemComponent* ToolbarMainItemFactory::createItem (const int itemId)
{
    switch (itemId)
    {
    case jost_new:
        return createButtonFromZipFile (itemId, T("new"), T("jost_new.png"), CommandIDs::sessionNew);
    case jost_load:
        return createButtonFromZipFile (itemId, T("load"), T("jost_load.png"), CommandIDs::sessionLoad);
    case jost_save:
        return createButtonFromZipFile (itemId, T("save"), T("jost_save.png"), CommandIDs::sessionSave);
    case jost_plugin:
        return createButtonFromZipFile (itemId, T("plugin"), T("jost_plugin.png"), CommandIDs::pluginOpen);

    case jost_audio:
        return createButtonFromZipFile (itemId, T("audio"), T("jost_audio.png"), CommandIDs::audioOptions);
    case jost_play:
        return createButtonFromZipFile (itemId, T("play"), T("jost_play.png"), CommandIDs::audioPlay);
    case jost_stop:
        return createButtonFromZipFile (itemId, T("stop"), T("jost_stop.png"), CommandIDs::audioStop);
    case jost_rec:
        return createButtonFromZipFile (itemId, T("rec"), T("jost_rec.png"), CommandIDs::audioRecord);
    case jost_rev:
        return createButtonFromZipFile (itemId, T("rewind"), T("jost_rev.png"), CommandIDs::audioRewind);
    case jost_loop:
        return createButtonFromZipFile (itemId, T("loop"), T("jost_loop.png"), CommandIDs::audioLoop);

    case jost_info:
        return createButtonFromZipFile (itemId, T("info"), T("jost_info.png"), CommandIDs::appAbout);
    case jost_search:
        return createButtonFromZipFile (itemId, T("search"), T("jost_search.png"), -1);

    case jost_fullscreen:
        return createButtonFromZipFile (itemId, T("fullscreen"), T("jost_fullscreen.png"), CommandIDs::appFullScreen);
    case jost_favorities:
        return createButtonFromZipFile (itemId, T("favorities"), T("jost_favorities.png"), -1);
    case jost_browser:
        return createButtonFromZipFile (itemId, T("browser"), T("jost_browse.png"), CommandIDs::appBrowser);
    case jost_toolbar:
        return createButtonFromZipFile (itemId, T("toolbar"), T("jost_toolbar.png"), CommandIDs::appToolbar);

    case jost_tempo:
        return new MainToolbarTempoSlider (owner, itemId);
    case jost_digits:
        return new MainToolbarTimeDisplay (owner, itemId);

//    case juceLogoButton:
//        return new ToolbarButton (itemId, T("juce!"), Drawable::createFromImageData (BinaryData::juce_png, BinaryData::juce_pngSize), 0);

    default:
        break;
    }

    return 0;
}

ToolbarButton* ToolbarMainItemFactory::createButtonFromZipFile (const int itemId,
                                                                const String& text,
                                                                const String& filename,
                                                                const int commandID)
{
    if (iconsFromZipFile.size() == 0)
    {
        // If we've not already done so, load all the images from the zip file..
        MemoryInputStream iconsFileStream (Resource::jost_icons, Resource::jost_icons_size, false);
        ZipFile icons (&iconsFileStream, false);

        for (int i = 0; i < icons.getNumEntries(); ++i)
        {
            InputStream* pngFileStream = icons.createStreamForEntry (i);

            if (pngFileStream != 0)
            {
                iconNames.add (icons.getEntry(i)->filename);
                iconsFromZipFile.add (Drawable::createFromImageDataStream (*pngFileStream));

                delete pngFileStream;
            }
        }
    }

    Drawable* image = iconsFromZipFile [iconNames.indexOf (filename)];
    if (image)
    {
        DrawableImage* imageToggled = dynamic_cast<DrawableImage*> (image->createCopy());
        imageToggled->setOverlayColour (Colours::yellow.withAlpha (0.6f));

        ToolbarButton* button = new ToolbarButton (itemId, text, image->createCopy(), imageToggled);
        if (commandID >= 0)
            button->setCommandToTrigger (CommandManager::getInstance(), commandID, true);
        else
            button->setEnabled (false);

        return button;
    }
    else
    {
        printf ("Can't find icon %s in resources !", (const char*) filename);
        return 0;
    }
}


