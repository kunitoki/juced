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

#ifndef __JUCETICE_JOSTTOOLBARMAINCOMPONENT_HEADER__
#define __JUCETICE_JOSTTOOLBARMAINCOMPONENT_HEADER__

#include "../../Config.h"


class HostFilterComponent;
class ToolbarMainItemFactory;


//==============================================================================
class MainToolbarTempoSlider : public ToolbarItemComponent,
                               public ChangeListener,
                               public SliderListener
{
public:
    MainToolbarTempoSlider (HostFilterComponent* owner, const int toolbarItemId);
    ~MainToolbarTempoSlider();

    void sliderValueChanged (Slider* sliderThatWasMoved);
    void changeListenerCallback (void *objectThatHasChanged);

    bool getToolbarItemSizes (int toolbarDepth,
                              bool isToolbarVertical,
                              int& preferredSize, int& minSize, int& maxSize);
    void paintButtonArea (Graphics&, int, int, bool, bool);
    void contentAreaChanged (const Rectangle& contentArea);

private:

    HostFilterComponent* owner;
    Slider* tempoSlider;
    Slider* loopLenSlider;
};

//==============================================================================
class MainToolbarTimeDisplay : public ToolbarItemComponent,
                               public ChangeListener,
                               public Timer
{
public:
    MainToolbarTimeDisplay (HostFilterComponent* owner, const int toolbarItemId);
    ~MainToolbarTimeDisplay();

    void changeListenerCallback (void *objectThatHasChanged);

    bool getToolbarItemSizes (int toolbarDepth,
                              bool isToolbarVertical,
                              int& preferredSize, int& minSize, int& maxSize);
    void paintButtonArea (Graphics&, int, int, bool, bool);
    void contentAreaChanged (const Rectangle& contentArea);

    void timerCallback();

private:

    void updateTimeDisplay ();

    HostFilterComponent* owner;
    Label* digitalDisplay;
};

//==============================================================================
class ToolbarMainItemFactory   : public ToolbarItemFactory
{
public:
    ToolbarMainItemFactory (HostFilterComponent* owner);
    ~ToolbarMainItemFactory ();

    //==============================================================================
    // Each type of item a toolbar can contain must be given a unique ID. These
    // are the ones we'll use in this demo.
    enum ToolbarMainItemIds
    {
        jost_play        = 1,
        jost_stop        = 2,
        jost_rec         = 3,
        jost_rev         = 4,
        jost_loop        = 5,
        jost_tempo       = 6,
        jost_digits      = 7,

        jost_new         = 10,
        jost_load        = 11,
        jost_save        = 12,
        jost_plugin      = 13,
        jost_info        = 15,
        jost_search      = 16,

        jost_browser     = 20,
        jost_favorities  = 21,
        jost_toolbar     = 22,
        jost_fullscreen  = 23,
        jost_audio       = 24
    };

    //==============================================================================
    void getAllToolbarItemIds (Array <int>& ids);
    void getDefaultItemSet (Array <int>& ids);
    ToolbarItemComponent* createItem (const int itemId);

private:

    HostFilterComponent* owner;
    StringArray iconNames;
    OwnedArray<Drawable> iconsFromZipFile;

    // This is a little utility to create a button with one of the SVG images in
    // our embedded ZIP file "icons.zip"
    ToolbarButton* createButtonFromZipFile (const int itemId,
                                            const String& text,
                                            const String& filename,
                                            const int commandID = -1);
};


#endif
