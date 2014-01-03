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

#ifndef __JUCETICE_JOSTLOOKANDFEEL_HEADER__
#define __JUCETICE_JOSTLOOKANDFEEL_HEADER__

#include "../../Config.h"


//==============================================================================
/**
    A new, slightly plasticky looking look-and-feel.

    To make this the default look for your app, just set it as the default in
    your initialisation code.

    e.g. @code
    void initialise (const String& commandLine)
    {
        static JostLookAndFeel myLook;
        LookAndFeel::setDefaultLookAndFeel (&myLook);
    }
    @endcode
*/
class JostLookAndFeel : public LookAndFeel
{
public:
    //==============================================================================
    /** Creates a JostLookAndFeel look and feel object. */
    JostLookAndFeel() {}

    /** Destructor. */
    ~JostLookAndFeel() {}

    //==============================================================================
    void readColourFromConfig ();

    //==============================================================================
    const Font getPopupMenuFont();

    //==============================================================================
/*
    void drawDocumentWindowTitleBar (DocumentWindow& window,
                                     Graphics& g, int w, int h,
                                     int titleSpaceX, int titleSpaceW,
                                     const Image* icon,
                                     bool drawTitleTextOnLeft);
*/

    Button* createDocumentWindowButton (int buttonType);

/*
    void positionDocumentWindowButtons (DocumentWindow& window,
                                        int titleBarX, int titleBarY,
                                        int titleBarW, int titleBarH,
                                        Button* minimiseButton,
                                        Button* maximiseButton,
                                        Button* closeButton,
                                        bool positionTitleBarButtonsOnLeft);
*/

    //==============================================================================
    int getFileListComponentRowHeight ();

    void drawFileBrowserRow (Graphics& g, int width, int height,
                             const String& filename, Image* icon,
                             const String& fileSizeDescription,
                             const String& fileTimeDescription,
                             const bool isDirectory,
                             const bool isItemSelected);
                                     
    void layoutFileBrowserComponent (FileBrowserComponent& browserComp,
                                     DirectoryContentsDisplayComponent* fileListComponent,
                                     FilePreviewComponent* previewComp,
                                     ComboBox* currentPathBox,
                                     TextEditor* filenameBox,
                                     Button* goUpButton);

    Button* createFileBrowserGoUpButton();

    //==============================================================================
    void drawToggleButton (Graphics& g,
                           ToggleButton& button,
                           bool isMouseOverButton,
                           bool isButtonDown);

    //==============================================================================
    int getDefaultScrollbarWidth ();

    void drawScrollbarButton (Graphics& g,
                              ScrollBar& bar,
                              int width, int height,
                              int buttonDirection,
                              bool isScrollbarVertical,
                              bool isMouseOverButton,
                              bool isButtonDown);

    void drawScrollbar (Graphics& g,
                        ScrollBar& bar,
                        int x, int y,
                        int width, int height,
                        bool isScrollbarVertical,
                        int thumbStartPosition,
                        int thumbSize,
                        bool isMouseOver,
                        bool isMouseDown);

    //==============================================================================
    void getTooltipSize (const String& tipText, int& width, int& height);
    void drawTooltip (Graphics& g, const String& text, int width, int height);

    //==============================================================================
    juce_UseDebuggingNewOperator

protected:

    Image* getFolderImage();
    Image* getFileImage();
    Image* getPluginImage();
    Image* getPresetImage();
    Image* getSampleImage();
    Image* getSessionImage();
    Image* getTextImage();
};


#endif   // __JUCETICE_JOSTLOOKANDFEEL_HEADER__
