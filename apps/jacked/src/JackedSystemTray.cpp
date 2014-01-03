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

#include "JackedSystemTray.h"
#include "JackedWindow.h"
#include "JackedGraph.h"

JackedSystemTray::JackedSystemTray ()
{
    Image icon (Image::RGB, 20, 20, true);

    Graphics g (icon);
    g.fillAll (Colours::black);
    g.setColour (Colours::white);
    g.setFont ((float) icon.getHeight(), Font::bold);
    g.drawText (T("j"), 0, 0, icon.getWidth(), icon.getHeight(), Justification::centred, false);

    setSize (icon.getWidth(), icon.getHeight());
    setIconImage (icon);

    // setIconTooltip (JACKED_NAME);
}

JackedSystemTray::~JackedSystemTray()
{
}

void JackedSystemTray::resized ()
{
    DBG (String (getWidth()) + " " + String (getHeight()));
}

void JackedSystemTray::mouseDown (const MouseEvent& e)
{
    PopupMenu m;
    m.addItem (1, T("Quit..."));
    
    const int result = m.show();
    switch (result)
    {
    case 1:
        JUCEApplication::getInstance()->systemRequestedQuit();
        break;
    default:
        break;
    }
}


