/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2008 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2008 by Julian Storer.

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

   @author  haydxn
   @tweaker Lucio Asnaghi

 ==============================================================================
*/

#include "DocumentDataElement.h"

int DocumentDataElement::count = 0;

DocumentDataElement::DocumentDataElement (const String& elementIdentifier)
:	elementName (elementIdentifier),
	parentElement (0),
	isDocumentElement (false)
{
	// output instantiation info...
	DBG (T("Document: ") + elementName + T(" CREATED, (") 
		+ String(++count) + T(")"));
}

DocumentDataElement::~DocumentDataElement ()
{
	// output destruction info...
	DBG (T("Document: ") + elementName + T(" DESTROYED, (")
		+ String(--count) + T(")"));
}

//===================================================================
void DocumentDataElement::setParentElement (DocumentDataElement* parent)
{
	parentElement = parent;
}

DocumentDataElement* DocumentDataElement::getParentElement ()
{
	return parentElement;
}

DocumentDataElement* DocumentDataElement::getDocumentElement ()
{
	// if this IS the document element...
	if (isDocumentElement) return this;

	// otherwise, if we have a parent...
	if (parentElement)
	{
		// ... ask it to perform this same search...
		return parentElement->getDocumentElement ();
	}
	else
	{
		jassertfalse;	// This element has no parent, and it is
						// not the designated root - you must make
						// sure that every document data element is
						// assigned a parent, and that your root
						// element is flagged as the document element
						// (using 'setDocumentElementStatus(true)')
		return 0;
	}
}

void DocumentDataElement::setDocumentElementStatus (bool isTheRoot)
{
	isDocumentElement = isTheRoot;
}

//===================================================================
bool DocumentDataElement::processXml (XmlElement* tag)
{
	// check that the tag has the right name...
	if (hasElementName (tag->getTagName ()))
	{
		readDataFromXmlElement (tag);
		return true;	// success
	}
	else return false;	// failure
}

XmlElement* DocumentDataElement::xml ()
{
	// create a new Xml tag...
	XmlElement* tag = new XmlElement (elementName);
	// add all the data from this element to the tag...
	addDataToXmlElement (tag);
	return tag;		// return the tag to the caller
}

//===================================================================
bool DocumentDataElement::hasElementName (const String& name)
{
	return (name == elementName);
}
