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

#include "JostLookAndFeel.h"
#include "../GraphComponent.h"


//==============================================================================
void JostLookAndFeel::readColourFromConfig ()
{
    Config* config = Config::getInstance ();

    setColour (PopupMenu::backgroundColourId,             config->getColour (T("popupBack"), Colours::white));
    setColour (PopupMenu::highlightedBackgroundColourId,  config->getColour (T("popupBackBright"), Colour (0x991111aa)));
    setColour (PopupMenu::textColourId,                   config->getColour (T("popupText"), Colours::black));
    setColour (PopupMenu::highlightedTextColourId,        config->getColour (T("popupTextBright"), Colours::white));

    setColour (TooltipWindow::backgroundColourId,         config->getColour (T("tooltipBack"), Colour (0xffcdcdcd)));
    setColour (TooltipWindow::textColourId,               config->getColour (T("tooltipText"), Colours::white));
    setColour (TooltipWindow::outlineColourId,            config->getColour (T("tooltipBorder"), Colours::white));

    setColour (ScrollBar::backgroundColourId,             config->getColour (T("scrollBack"), Colours::transparentBlack));
//    setColour (ScrollBar::thumbColourId,                  config->getColour (T("scrollThumb"), Colour (0xffb0b0b0)));
    setColour (ScrollBar::thumbColourId,                  config->getColour (T("mainBackground"), Colour (0xffb0b0b0)));

    setColour (TextButton::buttonColourId,                config->getColour (T("buttonColour"), Colour(0x88329aff)));
    setColour (ComboBox::buttonColourId,                  config->getColour (T("buttonColour"), Colour(0x88329aff)));
    setColour (TextEditor::focusedOutlineColourId,        config->getColour (T("buttonColour"), Colour(0x88329aff)));

    setColour (Toolbar::backgroundColourId,               config->getColour (T("toolbarBackground"), Colour (0xffb0b0b0)));
    setColour (Toolbar::buttonMouseOverBackgroundColourId,config->getColour (T("toolbarOverBackground"), Colours::aliceblue.withAlpha (0.3f)));
    setColour (Toolbar::buttonMouseDownBackgroundColourId,config->getColour (T("toolbarDownBackground"), Colours::aliceblue.withAlpha (0.5f)));
    setColour (Toolbar::editingModeOutlineColourId,       config->getColour (T("toolbarEditBackground"), Colours::black));
    setColour (Toolbar::separatorColourId,                config->getColour (T("toolbarSeparator"), Colours::black));

    setColour (HighQualityMeter::levelOverColourId,       config->getColour (T("meterOverLevel"), Colour (0xfff00014)));
    setColour (HighQualityMeter::level0dBColourId,        config->getColour (T("meter0dBLevel"), Colour (0xfff0f014)));
    setColour (HighQualityMeter::level3dBColourId,        config->getColour (T("meter3dBLevel"), Colour (0xfffafafa)));
    setColour (HighQualityMeter::level6dBColourId,        config->getColour (T("meter6dBLevel"), Colour (0xff78c8f0)));
    setColour (HighQualityMeter::level10dBColourId,       config->getColour (T("meter10dBLevel"), Colour (0xff148cdc)));
    setColour (HighQualityMeter::backgroundColourId,      config->getColour (T("meterBackground"), Colour (0xff142814)));
    setColour (HighQualityMeter::foregroundColourId,      config->getColour (T("meterForeground"), Colour (0xff787878)));

    setColour (GraphComponent::mainBackColourId,          config->getColour (T("graphBackground"), Colour (0xffb0b0b0)));
    setColour (GraphComponent::nodeBackColourId,          config->getColour (T("rackPluginBack"), Colour (0xff575757)));
    setColour (GraphComponent::nodeBackBrightColourId,    config->getColour (T("rackPluginBackBright"), Colour (0xff7d7d7d)));
    setColour (GraphComponent::nodeTextColourId,          config->getColour (T("rackPluginText"), Colour (0xffd9d9d9)));
    setColour (GraphComponent::nodeTextBrightColourId,    config->getColour (T("rackPluginTextBright"), Colour (0xffffffff)));
    setColour (GraphComponent::nodeBorderColourId,        config->getColour (T("rackPluginBorder"), Colour (0xffd9d9d9)));
    setColour (GraphComponent::nodeBorderBrightColourId,  config->getColour (T("rackPluginBorderBright"), Colour (0xffffffff)));
    setColour (GraphComponent::wireAudioColourId,         config->getColour (T("rackAudioConnector"), Colour (0xff2d5587)));
    setColour (GraphComponent::wireAudioBrightColourId,   config->getColour (T("rackAudioConnectorBright"), Colour (0xff2380d7)));
    setColour (GraphComponent::wireMidiColourId,          config->getColour (T("rackMidiConnector"), Colour (0xffdd6210)));
    setColour (GraphComponent::wireMidiBrightColourId,    config->getColour (T("rackMidiConnectorBright"), Colour (0xffe0732b)));

    setColour (PianoGrid::blackKeyColourId,               config->getColour (T("gridBlackKey"), Colour (0xffbebec4)));
    setColour (PianoGrid::blackKeyBrightColourId,         config->getColour (T("gridBlackKeyBright"), Colour (0xffd2d2d8)));
    setColour (PianoGrid::whiteKeyColourId,               config->getColour (T("gridWhiteKey"), Colour (0xffd2d2e2)));
    setColour (PianoGrid::whiteKeyBrightColourId,         config->getColour (T("gridWhiteKeyBright"), Colour (0xffe6e6f6)));
    setColour (PianoGrid::headerColourId,                 config->getColour (T("gridHeader"), Colour (0xffd2d2e2)));
    setColour (PianoGrid::backGridColourId,               config->getColour (T("gridBorder"), Colour (0xff909090)));
    setColour (PianoGrid::indicatorColourId,              config->getColour (T("gridIndicator"), Colours::red));
    setColour (PianoGrid::noteFillColourId,               config->getColour (T("gridNoteFill"), Colour (0x88ff0000)));
    setColour (PianoGrid::noteBorderColourId,             config->getColour (T("gridNoteBorder"), Colour (0xff550000)));

    setColour (LassoComponent<void*>::lassoFillColourId,  config->getColour (T("lassoFill"), Colour(0x88ccccee)));
    setColour (LassoComponent<void*>::lassoOutlineColourId,config->getColour (T("lassoBorder"), Colour(0x99111111)));
}

//==============================================================================
const Font JostLookAndFeel::getPopupMenuFont()
{
    return Font (14.0f);
}

//==============================================================================
class GlassWindowButton   : public Button
{
public:
    GlassWindowButton (const String& name, const Colour& col,
                       const Path& normalShape_,
                       const Path& toggledShape_) throw()
        : Button (name),
          colour (col),
          normalShape (normalShape_),
          toggledShape (toggledShape_)
    {
    }

    ~GlassWindowButton()
    {
    }

    void paintButton (Graphics& g, bool isMouseOverButton, bool isButtonDown)
    {
        float alpha = isMouseOverButton ? (isButtonDown ? 1.0f : 0.8f) : 0.55f;

        if (! isEnabled())
            alpha *= 0.5f;

        float x = 0, y = 0, diam;

        if (getWidth() < getHeight())
        {
            diam = (float) getWidth();
            y = (getHeight() - getWidth()) * 0.5f;
        }
        else
        {
            diam = (float) getHeight();
            y = (getWidth() - getHeight()) * 0.5f;
        }

        x += diam * 0.05f;
        y += diam * 0.05f;
        diam *= 0.9f;

        g.setGradientFill (ColourGradient(Colour::greyLevel (0.9f).withAlpha (alpha), 0, y + diam,
                                          Colour::greyLevel (0.6f).withAlpha (alpha), 0, y, false));
        g.fillEllipse (x, y, diam, diam);

        x += 2.0f;
        y += 2.0f;
        diam -= 4.0f;

        LookAndFeel::drawGlassSphere (g, x, y, diam, colour.withAlpha (alpha), 1.0f);

        Path& p = getToggleState() ? toggledShape : normalShape;

        const AffineTransform t (p.getTransformToScaleToFit (x + diam * 0.3f, y + diam * 0.3f,
                                                             diam * 0.4f, diam * 0.4f, true));

        g.setColour (Colours::black.withAlpha (alpha * 0.6f));
        g.fillPath (p, t);
    }

    juce_UseDebuggingNewOperator

private:
    Colour colour;
    Path normalShape, toggledShape;

    GlassWindowButton (const GlassWindowButton&);
    const GlassWindowButton& operator= (const GlassWindowButton&);
};

Button* JostLookAndFeel::createDocumentWindowButton (int buttonType)
{
    Path shape;
    const float crossThickness = 0.25f;

    if (buttonType == DocumentWindow::closeButton)
    {
        shape.addLineSegment (0.0f, 0.0f, 1.0f, 1.0f, crossThickness * 1.4f);
        shape.addLineSegment (1.0f, 0.0f, 0.0f, 1.0f, crossThickness * 1.4f);

        Colour colour = Config::getInstance ()->getColour (T("windowCloseButton"), Colour (0xffdd1100));

        return new GlassWindowButton ("close", colour, shape, shape);
    }
    else if (buttonType == DocumentWindow::minimiseButton)
    {
        shape.addLineSegment (0.0f, 0.5f, 1.0f, 0.5f, crossThickness);

        Colour colour = Config::getInstance ()->getColour (T("windowMinimizeButton"), Colour (0xffaa8811));

        return new GlassWindowButton ("minimise", colour, shape, shape);
    }
    else if (buttonType == DocumentWindow::maximiseButton)
    {
        shape.addLineSegment (0.5f, 0.0f, 0.5f, 1.0f, crossThickness);
        shape.addLineSegment (0.0f, 0.5f, 1.0f, 0.5f, crossThickness);

        Path fullscreenShape;
        fullscreenShape.startNewSubPath (45.0f, 100.0f);
        fullscreenShape.lineTo (0.0f, 100.0f);
        fullscreenShape.lineTo (0.0f, 0.0f);
        fullscreenShape.lineTo (100.0f, 0.0f);
        fullscreenShape.lineTo (100.0f, 45.0f);
        fullscreenShape.addRectangle (45.0f, 45.0f, 100.0f, 100.0f);
        PathStrokeType (30.0f).createStrokedPath (fullscreenShape, fullscreenShape);

        Colour colour = Config::getInstance ()->getColour (T("windowMaximizeButton"), Colour (0xff119911));

        return new GlassWindowButton ("maximise", colour, shape, fullscreenShape);
    }

    jassertfalse
    return 0;
}

//==============================================================================
int JostLookAndFeel::getFileListComponentRowHeight ()
{
    return 18;
}

void JostLookAndFeel::drawFileBrowserRow (Graphics& g, int width, int height,
                                          const String& filename, Image* icon,
                                          const String& fileSizeDescription,
                                          const String& fileTimeDescription,
                                          const bool isDirectory,
                                          const bool isItemSelected)
{
    if (isItemSelected)
        g.fillAll (findColour (DirectoryContentsDisplayComponent::highlightColourId));

    g.setColour (findColour (DirectoryContentsDisplayComponent::textColourId));
    g.setFont (height * 0.7f);

    Image* im = icon;
    Image* toRelease = 0;

    if (im == 0)
    {
        if (isDirectory)
        {
            im = getFolderImage ();
        }
        else
        {
            String ext (filename.fromLastOccurrenceOf (T("."), true, false));
            if (ext.equalsIgnoreCase (JOST_PLUGIN_EXTENSION)) 
                im = getPluginImage();
            else if (ext.equalsIgnoreCase (JOST_PRESET_EXTENSION)) 
                im = getPresetImage();
            else if (ext.equalsIgnoreCase (JOST_SESSION_EXTENSION)) 
                im = getSessionImage();
            else
                im = getFileImage();
        }
        
        toRelease = im;
    }

    const int x = 22;

    if (im != 0)
    {
        g.drawImageWithin (im, 1, 1, x - 2, height - 2,
                           RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize,
                           false);

        ImageCache::release (toRelease);
    }

    if (width > 300 && ! isDirectory)
    {
        const int sizeX = roundFloatToInt (width * 0.7f);
        const int dateX = roundFloatToInt (width * 0.8f);

        g.drawFittedText (filename,
                          x, 0, sizeX - x, height,
                          Justification::centredLeft, 1);

        g.setFont (height * 0.5f);
        g.setColour (Colours::darkgrey);

        if (! isDirectory)
        {
            g.drawFittedText (fileSizeDescription,
                              sizeX, 0, dateX - sizeX - 8, height,
                              Justification::centredRight, 1);

            g.drawFittedText (fileTimeDescription,
                              dateX, 0, width - 8 - dateX, height,
                              Justification::centredRight, 1);
        }
    }
    else
    {
        g.drawFittedText (filename,
                          x, 0, width - x, height,
                          Justification::centredLeft, 1);
    }
}

void JostLookAndFeel::layoutFileBrowserComponent (FileBrowserComponent& browserComp,
                                                  DirectoryContentsDisplayComponent* fileListComponent,
                                                  FilePreviewComponent* previewComp,
                                                  ComboBox* currentPathBox,
                                                  TextEditor* filenameBox,
                                                  Button* goUpButton)
{
    const int x = 2;
    int w = browserComp.getWidth() - x - x;
    int y = 2;

    if (previewComp != 0)
    {
        const int previewWidth = w / 3;
        previewComp->setBounds (x + w - previewWidth, y, previewWidth, browserComp.getHeight());

        w -= previewWidth + 2;
    }

    const int controlsHeight = 18;
    const int bottomSectionHeight = controlsHeight + 2;
    const int upButtonWidth = 40;

    currentPathBox->setBounds (x, y, w - upButtonWidth - 2, controlsHeight);
    goUpButton->setBounds (x + w - upButtonWidth, y, upButtonWidth, controlsHeight);

    y += controlsHeight + 2;

    Component* const listAsComp = dynamic_cast <Component*> (fileListComponent);
    listAsComp->setBounds (x, y, w, browserComp.getHeight() - y - bottomSectionHeight - 2);

    y = listAsComp->getBottom() + 2;
    filenameBox->setBounds (x + 40, y, w - 40, controlsHeight);
}

Button* JostLookAndFeel::createFileBrowserGoUpButton()
{
    DrawableButton* goUpButton = new DrawableButton ("up", DrawableButton::ImageOnButtonBackground);

    Colour backColor = findColour (TextButton::buttonColourId);
    goUpButton->setBackgroundColours (backColor, backColor);   

    Path arrowPath;
    arrowPath.addArrow (50.0f, 100.0f, 50.0f, 0.0, 40.0f, 100.0f, 50.0f);

    DrawablePath arrowImage;
    arrowImage.setFill (Colours::black.withAlpha (0.4f));
    arrowImage.setPath (arrowPath);

    goUpButton->setImages (&arrowImage);

    return goUpButton;
}

//==============================================================================
void JostLookAndFeel::drawToggleButton (Graphics& g,
                                        ToggleButton& button,
                                        bool isMouseOverButton,
                                        bool isButtonDown)
{
/*
    if (button.hasKeyboardFocus (true))
    {
        g.setColour (button.findColour (TextEditor::focusedOutlineColourId));
        g.drawRect (0, 0, button.getWidth(), button.getHeight());
    }
*/

    const int tickWidth = jmin (20, button.getHeight() - 4);

    drawTickBox (g, button, 4, (button.getHeight() - tickWidth) / 2,
                 tickWidth, tickWidth,
                 button.getToggleState(),
                 button.isEnabled(),
                 isMouseOverButton,
                 isButtonDown);

    g.setColour (button.findColour (ToggleButton::textColourId));
    g.setFont (jmin (15.0f, button.getHeight() * 0.6f));

    if (! button.isEnabled())
        g.setOpacity (0.5f);

    const int textX = tickWidth + 5;

    g.drawFittedText (button.getButtonText(),
                      textX, 4,
                      button.getWidth() - textX - 2, button.getHeight() - 8,
                      Justification::centredLeft, 10);
}

//==============================================================================
int JostLookAndFeel::getDefaultScrollbarWidth ()
{
    return 14;
}

void JostLookAndFeel::drawScrollbarButton (Graphics& g,
                                           ScrollBar& bar,
                                           int width, int height,
                                           int buttonDirection,
                                           bool isScrollbarVertical,
                                           bool isMouseOverButton,
                                           bool isButtonDown)
{
    if (isScrollbarVertical)
        width -= 2;
    else
        height -= 2;

    Path p;

    if (buttonDirection == 0)
        p.addTriangle (width * 0.5f, height * 0.2f,
                       width * 0.1f, height * 0.7f,
                       width * 0.9f, height * 0.7f);
    else if (buttonDirection == 1)
        p.addTriangle (width * 0.8f, height * 0.5f,
                       width * 0.3f, height * 0.1f,
                       width * 0.3f, height * 0.9f);
    else if (buttonDirection == 2)
        p.addTriangle (width * 0.5f, height * 0.8f,
                       width * 0.1f, height * 0.3f,
                       width * 0.9f, height * 0.3f);
    else if (buttonDirection == 3)
        p.addTriangle (width * 0.2f, height * 0.5f,
                       width * 0.7f, height * 0.1f,
                       width * 0.7f, height * 0.9f);

    if (isButtonDown)
        g.setColour (Colours::white);
    else if (isMouseOverButton)
        g.setColour (Colours::white.withAlpha (0.7f));
    else
        g.setColour (bar.findColour (ScrollBar::thumbColourId).withAlpha (0.5f));

    g.fillPath (p);

    g.setColour (Colours::black.withAlpha (0.5f));
    g.strokePath (p, PathStrokeType (0.5f));
}

void JostLookAndFeel::drawScrollbar (Graphics& g,
                                     ScrollBar& bar,
                                     int x, int y,
                                     int width, int height,
                                     bool isScrollbarVertical,
                                     int thumbStartPosition,
                                     int thumbSize,
                                     bool isMouseOver,
                                     bool isMouseDown)
{
    g.fillAll (bar.findColour (ScrollBar::backgroundColourId));

    g.setColour (bar.findColour (ScrollBar::thumbColourId)
                    .withAlpha ((isMouseOver || isMouseDown) ? 0.4f : 0.15f));

    if (thumbSize > 0.0f)
    {
        Rectangle thumb;

        if (isScrollbarVertical)
        {
            width -= 2;
            g.fillRect (x + roundFloatToInt (width * 0.35f), y,
                        roundFloatToInt (width * 0.3f), height);

            thumb.setBounds (x + 1, thumbStartPosition,
                             width - 2, thumbSize);
        }
        else
        {
            height -= 2;
            g.fillRect (x, y + roundFloatToInt (height * 0.35f),
                        width, roundFloatToInt (height * 0.3f));

            thumb.setBounds (thumbStartPosition, y + 1,
                             thumbSize, height - 2);
        }

        g.setColour (bar.findColour (ScrollBar::thumbColourId)
                        .withAlpha ((isMouseOver || isMouseDown) ? 0.95f : 0.7f));

        g.fillRect (thumb);

        g.setColour (Colours::black.withAlpha ((isMouseOver || isMouseDown) ? 0.4f : 0.25f));
        g.drawRect (thumb.getX(), thumb.getY(), thumb.getWidth(), thumb.getHeight());

        if (thumbSize > 16)
        {
            for (int i = 3; --i >= 0;)
            {
                const float linePos = thumbStartPosition + thumbSize / 2 + (i - 1) * 4.0f;
                g.setColour (Colours::black.withAlpha (0.15f));

                if (isScrollbarVertical)
                {
                    g.drawLine (x + width * 0.2f, linePos, width * 0.8f, linePos);
                    g.setColour (Colours::white.withAlpha (0.15f));
                    g.drawLine (width * 0.2f, linePos - 1, width * 0.8f, linePos - 1);
                }
                else
                {
                    g.drawLine (linePos, height * 0.2f, linePos, height * 0.8f);
                    g.setColour (Colours::white.withAlpha (0.15f));
                    g.drawLine (linePos - 1, height * 0.2f, linePos - 1, height * 0.8f);
                }
            }
        }
    }
}

//==============================================================================
static const TextLayout layoutTooltipText (const String& text)
{
    const float tooltipFontSize = 14.0f;
    const int maxToolTipWidth = 400;

    Font f (tooltipFontSize, Font::plain);
    TextLayout tl (text, f);
    tl.layout (maxToolTipWidth, Justification::left, true);

    return tl;
}

void JostLookAndFeel::getTooltipSize (const String& tipText, int& width, int& height)
{
    const TextLayout tl (layoutTooltipText (tipText));

    width = tl.getWidth() + 12;
    height = tl.getHeight() + 8;
}

void JostLookAndFeel::drawTooltip (Graphics& g, const String& text, int width, int height)
{
    g.fillAll (findColour (TooltipWindow::backgroundColourId));

    const Colour textCol (findColour (TooltipWindow::textColourId));

    g.setColour (findColour (TooltipWindow::outlineColourId));
    g.drawRect (0, 0, width, height);

    const TextLayout tl (layoutTooltipText (text));

    g.setColour (findColour (TooltipWindow::textColourId));
    tl.drawWithin (g, 0, 0, width, height, Justification::centred);
}

//==============================================================================
Image* JostLookAndFeel::getFolderImage()
{
    static const unsigned char icon_png[] = {
      137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,18,0,0,0,18,8,6,0,0,0,86,206,142,87,0,0,2,34,105,67,67,
      80,73,67,67,32,80,114,111,102,105,108,101,0,0,120,218,173,146,77,107,19,81,20,134,159,73,148,20,172,17,100,40,46,20,103,85,20,82,77,154,
      10,118,35,137,233,7,177,49,134,52,154,143,149,147,153,201,135,102,146,203,100,18,63,112,145,133,63,192,149,10,34,46,4,237,194,46,92,197,133,138,
      139,34,110,92,136,88,75,177,32,254,1,23,173,221,72,137,139,113,38,32,84,55,30,184,240,156,195,185,239,57,247,229,130,255,139,42,68,195,7,152,
      77,219,202,206,159,85,10,197,146,18,248,68,128,195,236,231,40,39,85,173,45,226,153,76,138,93,99,123,21,9,224,227,132,42,68,227,251,171,149,167,
      247,195,102,104,227,199,215,213,192,145,254,22,127,143,160,85,40,150,64,10,1,114,213,225,24,32,151,29,206,1,242,53,91,216,32,213,0,89,171,169,
      58,72,183,128,144,149,203,38,64,90,2,130,85,135,95,0,193,178,195,239,128,96,87,171,218,32,173,1,225,166,94,111,130,111,4,56,173,27,109,13,
      124,49,160,162,183,53,19,124,75,192,186,105,182,116,240,223,6,142,105,194,178,193,255,12,152,40,20,75,138,179,114,119,30,206,60,7,159,24,214,138,
      203,176,124,30,228,203,195,218,248,55,144,15,193,203,75,195,218,230,26,18,32,141,141,180,43,209,73,0,164,125,125,216,123,119,48,216,204,67,224,56,
      236,124,30,12,126,246,7,131,157,39,224,95,135,55,219,90,199,234,254,246,75,146,222,195,191,114,231,205,78,14,31,108,151,118,99,199,23,0,194,240,
      184,7,249,30,164,128,135,61,24,191,7,7,31,64,38,6,185,24,190,104,212,61,142,135,0,140,198,53,195,82,226,169,200,116,100,138,255,29,102,163,
      227,206,57,0,140,214,237,100,14,24,3,86,42,214,92,214,229,102,57,125,193,101,163,61,187,232,245,212,231,146,46,11,59,227,221,189,89,203,229,93,
      190,162,158,203,120,58,141,116,202,101,221,152,153,117,249,106,107,193,155,101,52,47,122,250,237,238,162,215,163,171,51,11,67,253,68,218,101,226,104,24,
      88,40,196,73,17,97,154,8,83,224,252,55,128,61,22,20,239,128,180,241,250,237,163,222,159,30,216,198,117,27,32,209,18,55,172,122,181,102,43,113,
      33,26,134,146,104,153,162,99,27,86,72,73,54,181,19,33,101,50,28,62,5,240,11,221,145,173,159,89,177,157,159,0,0,0,6,98,75,71,68,0,
      255,0,255,0,255,160,189,167,147,0,0,0,9,112,72,89,115,0,0,11,19,0,0,11,19,1,0,154,156,24,0,0,2,217,73,68,65,84,56,203,
      149,146,205,83,155,85,20,135,159,251,241,190,121,147,146,148,160,206,160,11,87,46,236,214,63,64,157,233,212,97,166,108,92,48,195,130,93,255,0,249,
      11,196,21,51,108,93,176,116,233,166,234,198,41,99,91,187,234,40,134,198,82,16,161,2,165,144,16,32,4,66,94,146,146,143,247,227,184,72,153,4,
      164,142,158,153,179,187,207,115,127,231,158,11,255,191,212,248,248,120,50,151,203,221,206,231,243,119,0,3,160,174,58,153,201,100,244,244,244,244,112,177,
      88,108,204,204,204,156,2,106,114,114,114,96,98,98,226,214,208,208,208,231,158,231,221,222,61,105,101,231,159,87,27,115,79,235,11,137,100,246,11,5,
      160,148,82,83,83,83,217,209,209,209,143,7,7,7,111,186,174,251,169,231,121,55,124,223,95,170,84,42,179,195,195,195,35,201,100,242,179,253,90,43,
      179,176,85,103,241,101,139,70,199,195,58,78,220,140,85,69,25,243,137,26,25,25,113,102,103,103,127,72,165,82,183,180,214,9,17,185,114,158,194,97,
      141,111,22,2,130,192,197,56,6,155,176,104,71,199,205,88,149,130,48,250,192,142,141,141,221,72,167,211,163,113,28,243,38,201,110,245,21,143,214,235,
      164,174,191,75,4,88,215,98,29,141,50,74,209,142,14,126,250,234,78,199,214,106,181,43,5,254,89,135,197,66,157,181,35,168,171,107,152,196,251,56,
      86,227,89,141,49,10,165,0,17,108,59,56,217,253,253,62,182,82,169,52,207,225,122,43,96,113,167,206,218,97,196,65,59,193,192,245,183,49,3,154,
      164,213,104,221,133,245,235,13,157,111,201,66,27,192,150,74,165,166,136,80,171,191,226,235,249,38,169,236,59,56,25,195,91,86,161,148,66,171,30,120,
      185,1,140,234,78,99,203,229,114,59,142,99,242,27,251,100,223,251,16,99,244,27,193,110,75,223,159,17,165,37,82,0,182,90,173,118,194,48,140,253,
      208,209,78,82,95,136,222,187,185,7,159,139,20,2,8,134,184,155,168,213,106,133,97,24,6,29,108,194,254,43,220,39,144,158,80,139,116,19,53,26,
      141,40,138,162,142,82,58,97,16,184,32,234,193,74,250,211,128,86,224,58,22,157,246,52,128,245,125,95,226,56,238,168,203,55,139,92,0,21,96,180,
      194,115,45,142,235,114,22,107,10,39,103,209,139,98,229,201,121,34,17,145,14,128,145,248,31,176,53,26,207,181,24,199,197,15,96,237,168,30,238,108,
      63,95,45,109,44,255,188,255,235,247,63,238,60,121,144,7,176,97,24,138,136,180,180,2,131,160,1,199,26,188,132,131,88,203,81,83,88,221,59,9,
      139,219,155,43,229,205,229,135,7,191,220,189,87,88,122,252,23,80,3,58,208,125,109,43,34,136,72,203,49,134,107,233,36,161,178,236,215,3,182,183,
      142,195,189,237,141,165,227,23,203,15,203,243,119,231,10,43,185,117,192,239,135,251,203,2,18,69,81,227,184,21,243,231,234,94,112,176,179,241,236,244,
      229,242,131,242,252,119,115,133,181,167,155,175,225,224,42,248,178,40,202,229,114,95,62,91,57,252,232,183,123,223,62,42,172,255,177,5,156,254,23,184,
      191,254,6,113,41,106,237,162,90,97,240,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

    return ImageCache::getFromMemory (icon_png, sizeof (icon_png));
}

Image* JostLookAndFeel::getFileImage()
{
    static const unsigned char icon_png[] = {
      137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,18,0,0,0,18,8,6,0,0,0,86,206,142,87,0,0,0,1,115,82,71,
      66,0,174,206,28,233,0,0,0,6,98,75,71,68,0,255,0,255,0,255,160,189,167,147,0,0,0,9,112,72,89,115,0,0,11,19,0,0,11,19,
      1,0,154,156,24,0,0,1,161,73,68,65,84,56,203,141,146,61,142,218,96,16,134,159,177,253,25,11,47,112,0,216,150,106,149,2,133,11,68,66,
      74,174,66,71,77,238,144,6,185,200,5,224,4,73,42,110,145,30,170,84,86,216,2,194,159,61,41,54,227,216,216,36,59,210,200,35,251,155,231,123,
      253,206,8,127,98,185,92,190,25,141,70,159,84,17,213,156,235,245,74,150,101,92,46,23,14,135,3,105,154,62,111,183,219,143,179,217,236,59,13,17,
      88,145,166,105,191,221,110,191,3,200,243,156,60,255,11,139,162,200,222,189,77,146,228,253,116,58,173,193,188,82,45,34,130,136,224,251,62,65,16,224,
      156,195,57,71,24,134,116,58,29,156,115,131,201,100,242,45,73,146,167,187,32,207,243,42,105,48,3,182,90,45,84,149,48,12,7,227,241,248,235,98,
      177,120,106,4,153,18,223,247,11,88,89,85,20,69,136,8,171,213,138,245,122,61,136,162,232,203,124,62,127,172,121,100,42,84,21,160,120,26,84,68,
      24,14,135,244,251,125,178,44,99,191,223,63,30,143,199,15,192,231,87,129,84,181,128,245,122,61,30,30,98,46,151,43,221,110,151,205,102,211,2,4,
      208,26,200,154,239,41,203,50,31,207,123,249,253,56,142,235,227,55,127,44,12,166,40,104,85,153,77,215,57,87,7,217,173,6,17,145,138,42,75,131,
      136,8,65,16,212,65,118,200,38,120,11,179,186,124,174,17,148,231,57,158,231,21,141,84,55,181,6,180,117,249,167,162,38,85,101,69,246,221,172,168,
      121,84,6,221,11,17,80,149,154,242,160,12,177,188,85,120,107,250,11,76,43,176,26,232,255,138,164,209,199,2,116,62,159,79,187,221,238,167,170,86,
      104,229,166,155,37,213,211,233,244,171,184,160,212,19,3,3,192,231,117,145,3,63,128,103,128,223,184,2,239,111,241,132,197,55,0,0,0,0,73,69,
      78,68,174,66,96,130,0,0};

    return ImageCache::getFromMemory (icon_png, sizeof (icon_png));
}

Image* JostLookAndFeel::getPluginImage()
{
    static const unsigned char icon_png[] = {
      137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,18,0,0,0,18,8,6,0,0,0,86,206,142,87,0,0,0,1,115,82,71,
      66,0,174,206,28,233,0,0,0,6,98,75,71,68,0,255,0,255,0,255,160,189,167,147,0,0,0,9,112,72,89,115,0,0,11,19,0,0,11,19,
      1,0,154,156,24,0,0,3,6,73,68,65,84,56,203,117,148,205,107,92,85,24,198,127,247,156,51,247,206,157,118,102,50,147,201,237,180,86,136,77,
      85,208,196,84,44,198,160,93,4,164,49,32,182,56,8,130,184,113,225,31,80,48,196,69,3,130,96,23,130,74,17,116,41,58,144,180,139,44,204,66,
      36,238,132,186,144,32,46,132,84,168,77,45,216,118,184,177,153,153,204,157,123,238,199,113,81,103,72,51,211,23,14,188,188,139,223,121,158,231,124,88,
      252,95,245,122,253,248,212,212,212,59,198,24,210,52,37,73,18,226,56,38,142,99,218,237,54,141,70,227,254,250,250,122,125,117,117,181,205,144,82,189,
      166,213,106,61,155,166,233,37,223,247,49,198,144,36,73,127,69,81,68,24,134,204,206,206,190,169,181,126,107,109,109,173,121,16,36,122,77,28,199,50,
      8,2,26,141,6,190,239,19,134,33,90,235,62,68,107,141,82,234,236,210,210,210,213,90,173,86,120,36,200,178,44,148,82,56,142,131,231,121,36,73,
      210,183,152,207,231,169,84,42,8,33,152,158,158,62,187,184,184,120,229,32,172,111,77,8,129,82,138,66,161,64,167,211,161,82,169,16,134,33,150,101,
      17,69,17,174,235,210,106,181,88,94,94,38,151,203,205,207,204,204,92,217,221,221,173,109,108,108,236,61,164,72,8,65,38,147,193,113,28,28,199,1,
      120,144,79,215,199,182,90,40,165,152,152,152,96,114,114,146,241,241,113,60,207,155,95,88,88,56,55,84,145,109,219,100,179,89,0,28,199,33,10,26,
      140,31,254,145,140,236,114,51,124,29,199,241,168,86,171,196,113,12,128,214,186,12,88,128,25,0,73,41,41,22,139,180,239,223,230,68,246,123,174,111,
      253,206,237,59,1,243,115,49,55,186,231,201,229,158,194,24,131,101,89,228,243,121,107,32,236,158,53,41,37,186,115,135,35,209,183,84,115,127,242,217,
      55,55,184,92,223,166,100,223,226,137,204,10,38,216,198,182,109,92,215,197,182,237,225,167,38,165,196,232,123,148,154,95,226,185,91,236,252,219,196,117,
      224,253,218,40,38,9,40,217,183,240,186,95,17,181,174,163,148,66,41,53,8,2,72,147,136,252,206,231,148,237,45,18,221,230,235,171,255,96,171,132,
      218,92,150,88,119,136,245,30,5,181,77,185,249,5,42,221,65,74,57,8,74,211,20,219,118,104,234,19,4,65,66,20,118,120,227,21,69,16,68,156,
      121,239,47,214,126,242,137,194,14,221,110,68,75,63,142,200,148,134,43,74,211,20,55,119,136,177,83,31,112,55,126,141,32,20,60,54,170,185,124,33,
      199,115,39,37,191,254,177,71,168,83,238,6,47,114,248,153,139,20,203,222,112,69,0,82,74,70,74,101,142,158,254,16,159,115,116,181,226,135,107,109,
      108,21,115,225,109,23,63,62,67,249,249,143,25,171,30,39,147,201,12,127,180,189,176,45,203,98,164,84,70,205,94,228,239,95,12,47,60,253,29,167,
      78,70,52,229,171,28,57,125,137,242,216,81,0,140,49,143,6,9,33,16,226,129,200,145,82,25,249,242,71,220,252,25,100,116,143,99,47,125,202,168,
      119,140,253,81,236,135,237,191,144,198,178,172,135,118,41,20,71,120,114,238,19,146,88,115,40,95,236,207,123,0,33,132,25,0,173,172,172,252,182,185,
      185,249,110,20,69,153,131,95,196,65,27,198,24,164,148,137,239,251,215,0,3,240,31,195,45,78,71,56,97,56,178,0,0,0,0,73,69,78,68,174,
      66,96,130,0,0};

    return ImageCache::getFromMemory (icon_png, sizeof (icon_png));
}

Image* JostLookAndFeel::getPresetImage()
{
    static const unsigned char icon_png[] = {
      137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,18,0,0,0,18,8,6,0,0,0,86,206,142,87,0,0,0,1,115,82,71,
      66,0,174,206,28,233,0,0,0,6,98,75,71,68,0,255,0,255,0,255,160,189,167,147,0,0,0,9,112,72,89,115,0,0,11,19,0,0,11,19,
      1,0,154,156,24,0,0,2,134,73,68,65,84,56,203,141,211,77,72,20,97,28,199,241,239,243,204,206,204,142,43,42,134,171,173,47,41,41,6,198,
      130,172,132,73,37,4,33,228,205,94,132,162,12,36,144,78,93,186,116,232,20,216,161,75,151,176,131,8,18,149,38,120,136,4,47,209,37,130,8,73,
      163,55,150,82,204,183,214,116,39,93,172,181,117,158,14,237,108,251,38,244,192,195,60,135,153,207,255,247,60,207,127,4,201,49,58,58,26,12,133,66,
      183,1,28,199,97,103,103,135,68,34,65,34,145,32,30,143,171,104,52,106,207,205,205,221,232,235,235,251,68,158,225,113,23,145,72,164,210,48,140,19,
      46,228,56,14,154,166,225,241,120,208,52,13,199,113,168,168,168,56,60,56,56,216,209,219,219,251,33,27,146,105,107,33,132,64,8,145,2,116,93,71,
      215,117,12,195,192,231,243,97,89,86,117,123,123,251,228,208,208,208,129,93,33,41,101,198,116,49,23,52,77,19,77,211,48,77,179,58,24,12,78,14,
      15,15,55,230,133,220,36,154,166,165,176,236,84,197,197,197,76,79,79,19,14,135,107,164,148,79,250,251,251,203,243,38,114,145,124,152,97,24,248,253,
      126,234,106,171,249,25,179,9,4,2,13,101,101,101,39,119,133,178,103,118,178,165,217,207,44,47,46,80,84,88,128,105,154,190,156,91,115,33,0,165,
      20,74,169,212,218,221,250,250,124,152,66,93,227,252,165,203,40,165,48,231,230,115,207,40,61,133,123,200,0,43,11,95,145,82,242,125,246,61,27,235,
      107,212,135,218,176,44,11,195,48,48,12,35,183,143,220,84,110,10,33,4,79,199,30,49,63,243,154,83,61,61,68,87,35,52,182,30,71,74,137,227,
      56,8,33,82,197,50,32,247,227,173,88,140,23,19,227,172,175,124,161,220,92,163,241,80,41,47,159,79,176,239,224,49,116,143,142,226,239,123,64,126,
      200,113,28,0,238,223,185,69,179,181,74,243,145,66,34,191,42,153,153,154,229,193,227,87,212,213,76,17,106,59,138,148,50,85,52,29,146,233,137,214,
      34,223,88,126,247,134,150,42,73,129,37,240,26,91,220,29,123,75,215,233,51,220,28,24,198,227,209,112,187,223,109,143,188,103,100,122,189,68,55,54,
      89,252,184,68,165,207,162,94,198,232,110,240,16,108,106,162,168,164,36,153,4,148,18,169,219,204,129,132,16,148,148,238,161,165,179,139,123,35,3,52,
      173,236,199,247,123,21,123,83,81,219,220,154,218,210,63,76,101,96,25,144,148,146,11,87,174,50,226,45,224,217,248,67,138,74,171,184,120,253,26,254,
      189,129,244,63,59,39,77,6,180,189,189,29,183,109,59,170,148,18,157,103,207,209,209,213,157,196,5,182,109,103,52,103,242,169,226,241,248,86,170,64,
      26,234,3,170,0,141,255,27,14,176,12,252,0,248,3,211,61,238,217,126,198,164,31,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

    return ImageCache::getFromMemory (icon_png, sizeof (icon_png));
}

Image* JostLookAndFeel::getSampleImage()
{
    static const unsigned char icon_png[] = {
      137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,18,0,0,0,18,8,6,0,0,0,86,206,142,87,0,0,0,1,115,82,71,
      66,0,174,206,28,233,0,0,0,6,98,75,71,68,0,255,0,255,0,255,160,189,167,147,0,0,0,9,112,72,89,115,0,0,11,19,0,0,11,19,
      1,0,154,156,24,0,0,2,125,73,68,65,84,56,203,141,212,205,79,19,65,24,199,241,239,204,236,43,165,86,16,138,242,150,104,210,136,38,82,19,
      18,13,92,32,24,99,226,217,139,241,202,137,63,194,27,55,255,2,67,144,51,241,162,156,56,153,112,240,224,5,162,8,24,4,95,162,66,139,216,34,
      125,219,165,157,241,226,214,66,105,226,147,108,102,46,243,217,223,204,60,187,130,191,181,176,176,48,60,50,50,242,4,64,107,77,173,86,163,90,173,82,
      173,86,9,130,192,228,114,185,252,206,206,206,227,233,233,233,15,156,81,86,52,201,102,179,125,142,227,220,141,32,173,53,74,41,44,203,66,41,133,214,
      154,222,222,222,209,217,217,217,123,83,83,83,27,167,33,217,48,23,66,8,132,16,117,192,182,109,108,219,198,113,28,98,177,24,190,239,15,140,143,143,
      47,205,205,205,13,181,132,164,148,39,158,8,139,64,215,117,81,74,225,121,222,64,58,157,94,154,159,159,191,122,38,20,37,81,74,213,177,8,177,44,
      139,208,132,28,201,34,47,150,95,178,181,181,53,168,148,90,156,153,153,233,105,58,163,40,133,49,6,128,48,12,169,232,50,43,95,222,240,58,183,74,
      153,10,161,14,105,179,124,238,12,79,82,40,20,82,149,74,229,62,240,172,37,180,247,179,196,122,152,160,43,149,227,224,243,38,61,198,166,179,253,10,
      113,171,147,237,236,54,174,235,34,165,196,243,188,88,203,68,197,82,153,239,223,10,196,99,231,176,246,47,19,232,36,15,175,77,82,85,30,149,32,100,
      247,112,15,199,113,144,82,226,186,110,243,245,71,231,19,30,215,232,138,23,56,119,126,159,160,232,96,5,54,21,60,124,219,195,247,125,60,215,37,8,
      143,241,61,23,199,113,206,188,126,164,148,56,182,69,123,71,7,137,142,4,65,16,130,214,88,10,50,153,67,50,71,25,126,151,242,24,109,234,151,208,
      148,200,24,131,16,2,41,12,2,137,109,219,124,13,54,121,181,179,204,173,139,99,172,236,127,98,181,184,72,77,91,24,254,181,70,19,164,181,70,74,
      73,91,91,27,107,107,235,20,107,5,158,231,159,146,28,114,136,247,253,160,243,130,199,224,126,138,65,127,2,173,107,173,161,40,145,235,186,164,211,55,
      120,251,238,61,19,181,7,140,15,14,208,111,12,170,55,70,143,253,136,240,227,46,201,238,142,122,175,53,65,81,83,2,36,18,9,198,70,111,51,244,
      43,69,38,123,192,70,25,228,158,160,199,15,184,116,243,250,137,126,107,130,162,239,44,194,132,16,36,147,73,186,187,187,235,137,79,143,141,88,19,116,
      186,132,16,245,109,55,142,45,127,35,97,24,6,249,124,62,103,140,57,161,53,46,58,149,202,4,65,80,170,191,176,97,77,12,232,7,20,255,87,26,
      216,5,14,1,254,0,81,49,7,109,17,186,209,132,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

    return ImageCache::getFromMemory (icon_png, sizeof (icon_png));
}

Image* JostLookAndFeel::getSessionImage()
{
    static const unsigned char icon_png[] = {
      137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,18,0,0,0,18,8,6,0,0,0,86,206,142,87,0,0,0,1,115,82,71,
      66,0,174,206,28,233,0,0,0,6,98,75,71,68,0,255,0,255,0,255,160,189,167,147,0,0,0,9,112,72,89,115,0,0,11,19,0,0,11,19,
      1,0,154,156,24,0,0,3,6,73,68,65,84,56,203,117,148,205,79,92,85,24,198,127,231,235,222,249,102,24,132,169,160,109,149,209,180,65,160,155,
      86,141,91,211,134,184,104,35,233,170,241,63,80,23,214,16,18,19,187,171,46,253,35,32,129,54,72,98,112,199,222,141,37,46,58,154,54,52,21,197,
      118,8,224,12,51,195,220,153,251,113,174,139,97,154,142,76,223,213,115,22,239,239,60,239,121,243,28,193,73,45,47,47,191,49,61,61,125,43,142,99,
      172,181,68,81,68,24,134,132,97,72,179,217,100,127,127,191,182,177,177,177,188,186,186,218,100,64,233,158,104,52,26,83,62,67,223,239,85,45,93,88,
      68,20,134,68,81,72,16,36,169,135,112,249,163,79,62,245,125,255,230,250,250,122,253,149,160,48,12,85,211,131,221,3,144,66,146,112,20,177,85,68,
      86,227,251,138,134,159,69,171,214,213,197,197,197,251,82,202,155,107,107,107,125,48,217,19,66,8,164,84,24,165,24,201,187,4,145,192,143,36,65,40,
      72,165,92,10,249,44,8,197,236,236,236,213,133,133,133,123,243,243,243,185,129,142,164,148,40,165,72,167,21,141,150,101,56,231,210,241,35,164,52,132,
      65,132,227,184,252,91,107,115,251,155,31,200,164,147,215,46,93,254,248,222,209,209,209,252,230,230,230,113,159,35,41,37,70,75,140,86,104,37,177,49,
      68,86,224,7,18,199,49,40,147,224,205,243,37,74,23,174,48,58,62,69,126,100,226,218,220,220,220,245,129,142,180,210,24,45,136,140,32,229,42,172,
      13,81,50,166,211,110,208,58,218,227,224,249,14,147,23,174,0,130,164,105,177,191,83,41,0,2,136,251,65,70,209,233,52,105,215,119,169,239,213,72,
      232,144,216,182,232,180,91,24,33,152,156,72,162,101,128,155,28,34,105,4,237,108,86,12,118,164,53,7,149,39,164,197,63,148,206,158,165,88,28,99,
      120,184,64,181,90,229,193,131,95,17,2,242,89,23,43,29,92,39,198,113,156,211,143,45,132,64,43,73,38,87,160,144,140,89,90,90,98,231,207,167,
      164,82,41,174,223,184,193,238,223,127,241,254,7,31,146,73,73,106,158,196,117,28,180,214,167,215,223,117,37,72,167,178,84,107,13,126,222,248,137,199,
      143,31,81,46,63,100,102,102,150,114,249,119,238,220,249,150,116,34,70,41,48,70,247,129,94,40,107,45,74,73,50,185,28,141,67,193,80,62,79,219,
      243,240,60,143,227,86,139,207,191,248,18,99,52,142,182,68,129,135,49,89,148,82,167,29,89,107,145,82,144,76,184,248,129,165,120,102,252,133,203,237,
      237,109,190,190,253,21,223,221,189,203,243,103,187,24,229,163,149,234,3,233,151,71,83,82,96,140,70,72,195,197,169,75,188,53,249,46,165,210,59,156,
      59,95,98,229,254,143,180,61,143,74,165,194,113,171,142,82,197,193,89,235,70,68,96,180,192,117,147,92,124,111,6,191,211,65,32,121,248,199,83,202,
      143,158,145,201,141,48,58,54,206,200,88,17,173,228,171,65,74,118,55,247,250,196,219,8,105,120,109,244,12,217,92,30,215,77,118,199,16,2,1,16,
      131,148,49,113,28,15,204,90,60,148,22,36,28,56,87,156,128,233,9,78,122,224,164,161,167,99,64,75,120,34,101,124,10,180,178,178,242,219,214,214,
      214,103,65,16,152,255,255,53,47,223,220,59,43,165,162,195,195,195,95,122,252,255,0,93,65,37,248,65,16,250,30,0,0,0,0,73,69,78,68,174,
      66,96,130,0,0};

    return ImageCache::getFromMemory (icon_png, sizeof (icon_png));
}

Image* JostLookAndFeel::getTextImage()
{
    static const unsigned char icon_png[] = {
      137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,18,0,0,0,18,8,6,0,0,0,86,206,142,87,0,0,0,1,115,82,71,
      66,0,174,206,28,233,0,0,0,6,98,75,71,68,0,255,0,255,0,255,160,189,167,147,0,0,0,9,112,72,89,115,0,0,11,19,0,0,11,19,
      1,0,154,156,24,0,0,2,105,73,68,65,84,56,203,141,146,61,110,220,58,20,70,15,37,82,164,164,129,127,128,216,133,227,52,118,27,4,134,17,
      120,1,41,140,100,45,238,220,25,200,30,210,120,26,111,192,11,48,144,188,141,188,126,26,207,43,12,225,121,60,227,17,69,137,100,138,68,74,6,114,
      128,220,138,96,113,120,248,125,87,240,115,110,111,111,223,157,158,158,126,137,17,17,99,160,235,58,188,247,180,109,203,122,189,166,170,170,197,108,54,251,
      124,121,121,249,47,47,140,236,15,85,85,189,46,138,226,3,64,8,129,16,126,193,140,49,253,221,251,233,116,250,241,226,226,98,4,75,126,59,11,33,
      4,243,249,156,197,98,193,227,227,35,171,213,138,170,170,88,46,151,196,24,137,49,30,158,159,159,255,51,157,78,223,254,17,148,36,9,73,146,16,66,
      160,174,107,234,186,166,235,58,146,36,193,57,135,181,22,231,28,89,150,29,158,157,157,125,187,190,190,126,251,34,72,8,65,154,166,24,99,200,178,140,
      16,2,49,70,164,148,196,24,41,203,146,186,174,185,185,185,225,238,238,238,80,107,253,245,234,234,234,205,40,163,222,200,123,79,8,1,109,12,123,175,
      94,81,20,197,144,215,254,254,62,39,39,39,120,239,121,126,126,126,99,173,253,4,220,140,64,82,74,142,142,142,0,250,76,54,30,217,222,222,102,50,
      41,105,219,142,173,173,45,102,179,153,6,4,16,71,70,247,247,247,125,22,120,239,81,74,17,66,192,57,135,214,154,245,122,77,158,231,20,69,65,89,
      150,227,140,210,52,69,74,137,181,22,41,37,33,4,164,148,116,93,71,219,182,8,33,232,186,14,173,53,77,211,16,99,68,41,245,98,253,195,247,210,
      52,5,24,242,234,203,112,206,225,189,71,107,77,89,150,72,41,199,160,24,35,66,8,146,228,199,85,111,161,181,70,8,65,8,129,44,203,104,93,203,
      211,211,211,96,60,106,45,132,48,232,119,93,135,148,146,182,109,105,219,22,0,165,20,59,59,59,131,161,82,106,48,223,0,197,24,73,146,132,227,227,
      227,141,141,117,206,13,89,40,165,70,109,142,64,125,14,243,249,28,99,12,0,214,218,161,189,52,77,89,46,151,100,89,198,222,222,30,121,158,243,199,
      205,238,219,179,214,98,173,69,41,69,93,215,228,121,78,211,52,236,238,238,2,240,240,240,128,16,98,48,219,48,18,66,32,132,64,41,69,158,231,172,
      86,43,140,49,120,239,241,222,15,171,113,112,112,128,49,102,3,178,1,114,206,53,139,197,226,255,201,100,34,128,225,123,89,150,1,80,20,5,49,70,
      154,166,193,90,11,16,155,166,169,7,145,223,160,37,112,8,164,252,221,4,224,63,96,1,240,29,143,61,73,226,205,163,254,224,0,0,0,0,73,69,
      78,68,174,66,96,130,0,0};

    return ImageCache::getFromMemory (icon_png, sizeof (icon_png));
}


