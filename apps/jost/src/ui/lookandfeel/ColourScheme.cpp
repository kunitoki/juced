/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2007 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2007 by Julian Storer.

 ------------------------------------------------------------------------------

 JUCE and JUCETICE can be redistributed and/or modified under the terms of
 the GNU General Public License, as published by the Free Software Foundation;
 either version 2 of the License, or (at your option) any later version.

 JUCE and JUCETICE are distributed in the hope that they will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with JUCE and JUCETICE; if not, visit www.gnu.org/licenses or write to
 Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 Boston, MA 02111-1307 USA

 ==============================================================================
 */

#include "ColourScheme.h"
#include "DefaultColourScheme.h"

//==============================================================================
ColourScheme::ColourScheme (const String& schemePath)
  : path (schemePath)
{
    file = File (path);
    if (! file.existsAsFile ())
        createDefaultScheme();

    doc = new XmlDocument (file);
}

ColourScheme::~ColourScheme()
{
    deleteAndZero (doc);
}

//==============================================================================
Colour ColourScheme::getColour (const String& name, const Colour& defColour) const
{
    Colour retval = defColour;

    XmlElement *rootElement = doc->getDocumentElement();
    XmlElement *tempElement;

    if (rootElement)
    {
        if (rootElement->hasTagName(T("COLOURS")))
        {
            for (tempElement = rootElement->getChildByName(T("COLOUR"));
                 tempElement != 0;
                 tempElement = tempElement->getNextElement())
            {
                if (tempElement->getStringAttribute (T("name")) == name)
                {
                    String tempstr = tempElement->getStringAttribute (T("colour"));
                    retval = Colour (tempstr.getHexValue32());
                    break;
                }
            }
        }
        delete rootElement;
    }

    return retval;
}

void ColourScheme::setColour (const String& name, const Colour& newColour)
{
    //Make sure the file actually exists first.
    if (! file.existsAsFile () )
        createDefaultScheme();

    XmlDocument newDoc (file);
    XmlElement *rootElement = newDoc.getDocumentElement();
    XmlElement *tempElement;

    if (rootElement)
    {
        if (rootElement->hasTagName(T("COLOURS")))
        {
            for (tempElement = rootElement->getChildByName(T("COLOUR"));
                 tempElement != 0;
                 tempElement = tempElement->getNextElement())
            {
                if (tempElement->getStringAttribute (T("name")) == name)
                {
                    tempElement->setAttribute (T("colour"),
                                               String::toHexString ((int)newColour.getARGB()));
                    break;
                }
            }
            rootElement->writeToFile (file, T(""));
        }
        delete rootElement;
    }
}

//==============================================================================
void ColourScheme::createDefaultScheme() const
{
    String tempstr;
    File newFile (path);
    newFile.create();

    FileOutputStream fos (newFile);
    fos << jucetice_defaultColourScheme;
}

