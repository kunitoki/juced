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

#ifndef __JUCETICE_DOCUMENTDATAELEMENT_HEADER__
#define __JUCETICE_DOCUMENTDATAELEMENT_HEADER__

#include "StandardHeader.h"
#include "Data/Data.h"


class DocumentDataElement	:	public Data
{
public:

	/** Constructor for the element. In your subclass, you should
		initialise this base with a single-word String identifier
		for the element type it represents. This should be one word
		as it is used as the tag name in its Xml form. */
	DocumentDataElement (const String& elementIdentifier = T("unnamed"));
	virtual ~DocumentDataElement ();

	/** Set the element that this belongs to if it is nested. This
		allows a path back to the root of the Document if required. */
	void setParentElement (DocumentDataElement* parent);
	/** Retrieve a pointer to the element this one belongs to. */
	DocumentDataElement* getParentElement ();
	/** This steps up through the hierarchy to find the root element. */
	DocumentDataElement* getDocumentElement ();

	/** Calling this will return a new Xml structure representing
		the state of this Document element. It creates the tag
		using the element's identifier (set in the constructor),
		and fills with the data by calling 'addDataToXmlElement()' -
		which you define yourself. */
	XmlElement* xml ();
	/** Call this with an XmlElement to set the state of this element.
		The tag provided is checked to make sure it originated from
		this type of element (by comparing the tag name with the
		element's identifier String). It is then passed to the
		'readDataFromXmlElement()' function (which you define yourself
		to extract the data and update the state of the element). */
	bool processXml (XmlElement* tag);

	juce_UseDebuggingNewOperator;

protected:

	/** Used internally to check an identifier against the name
		given to this type of element. */
	bool hasElementName (const String& name);
	const String elementName;

	DocumentDataElement* parentElement;

	/** Used internally to set a flag indicating whether or not
		this element is the root of the Document structure. */
	void setDocumentElementStatus (bool isTheRoot = true);
	bool isDocumentElement;

private:

	/** Here you dump all your element's member data to
		a ready-prepared Xml tag.

		The Xml tag has already
		been given the correct tag name for this element type,
		so you can just set appropriate attributes to store
		the values and states of all your member variables.
		If it contains nested DocumentDataElement objects, you
		simply call 'tag->addChildElement(nestedElement->xml())',
		letting them create for you their own Xml. */
	virtual void addDataToXmlElement (XmlElement* tag) {};

	/** This is where you read data from an XmlElement representing
		this type of Document element.

		The tag name has already been checked against this element's
		name by this point, so you just need to read the data from it.
		Just do the reverse of the 'addDataToXmlElement()' function,
		reading attributes and children from the tag and using them
		to set your member variables. If you have nested
		DocumentDataElement objects, you set their state by calling
		'nestedElement->processXml ()' with a child tag. */
	virtual void readDataFromXmlElement (XmlElement* tag) {};

	static int count;

};

#endif//_DOCUMENTDATAELEMENT_H_
