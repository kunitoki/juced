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

#ifndef __JUCETICE_NOTEMAP_HEADER__
#define __JUCETICE_NOTEMAP_HEADER__

#include "StandardHeader.h"
#include "DocumentDataElement.h"

class SingleNoteMap	:	public DocumentDataElement
{
public:

	SingleNoteMap ()
		: DocumentDataElement (T("N"))
	{
	}

	void setTargetNote (int noteNumber)
	{
		jassert (noteNumber < 128);
		note = noteNumber;
	}

	int getTargetNote ()
	{
		return note;
	}

	void setTargetChannel (int chan)
	{
		jassert ((chan > 0) && (chan < 17));
		channel = chan;
	}

	int getTargetChannel ()
	{
		return channel;
	}

	friend class NoteMap;

private:

	void addDataToXmlElement (XmlElement* tag)
	{
		tag->setAttribute (T("outNote"), note);
		tag->setAttribute (T("outChan"), channel);
	}

	void readDataFromXmlElement (XmlElement* tag)
	{
		note = tag->getIntAttribute (T("outNote"));
		channel = tag->getIntAttribute (T("outChan"), 1);
	}

	int channel;
	int note;
};

class NoteMap	:	public DocumentDataElement
{
public:

	NoteMap ()
		:	DocumentDataElement (T("NoteMap"))
	{
	}

	void resetAll (int channelNumber)
	{
		channel = channelNumber;
		for (int i=0; i<128; i++)
		{
			map [i].setTargetNote (i);
			map [i].setTargetChannel (channel);
		}
	}

	SingleNoteMap& getMap (int inputNoteNumber)
	{
		jassert (inputNoteNumber < 128);
		return map [inputNoteNumber];
	}

	int getOutputNoteFor (int inputNoteNumber)
	{
		jassert (inputNoteNumber < 128);
		return map [inputNoteNumber].getTargetNote ();
	}

	int getOutputChannelFor (int inputNoteNumber)
	{
		jassert (inputNoteNumber < 128);
		return map [inputNoteNumber].getTargetChannel ();
	}

	void setOutputNoteFor (int inputNoteNumber, int output)
	{
		jassert ((inputNoteNumber < 128) && (output < 128));
		map [inputNoteNumber].setTargetNote (output);
	}

	void setOutputChannelFor (int inputNoteNumber, int output)
	{
		jassert ((inputNoteNumber < 128) && (output > 0) && (output < 17));
		map [inputNoteNumber].setTargetChannel (output);
	}

private:

	void addDataToXmlElement (XmlElement* tag)
	{
		tag->setAttribute (T("Channel"), channel);
		for (int i=0; i<128; i++)
		{
			if (map[i].getTargetNote () != i)
			{
				XmlElement* mapTag = new XmlElement (T("Map"));
				mapTag->setAttribute (T("inNote"), i);
				map[i].addDataToXmlElement (mapTag);
				tag->addChildElement (mapTag);
			}
		}
	}

	void readDataFromXmlElement (XmlElement* tag)
	{
		channel = tag->getIntAttribute (T("Channel"), 1);
		XmlElement* mapTag = tag->getFirstChildElement ();
		while (mapTag)
		{
			if (mapTag->hasTagName (T("Map")))
			{
				int i = mapTag->getIntAttribute (T("inNote"));
				map[i].readDataFromXmlElement (mapTag);
			}
			mapTag = mapTag->getNextElement ();
		}
	}

	SingleNoteMap map [128];
	int channel;
};

class SixteenChannelMaps	:	public DocumentDataElement
{
public:

	SixteenChannelMaps ()
		:	DocumentDataElement (T("InputChannels"))
	{
		for (int channel=1; channel<17; channel++)
		{
			maps[channel-1].resetAll (channel);
		}
	}

	NoteMap& getMapForChannel (int channel)
	{
		jassert ((channel > 0) && (channel < 17));
		return maps [channel-1];
	}

private:

	void addDataToXmlElement (XmlElement* tag)
	{
		for (int i=0; i<16; i++)
		{
			tag->addChildElement (maps[i].xml ());
		}
	}

	void readDataFromXmlElement (XmlElement* tag)
	{
		XmlElement* chTag = tag->getFirstChildElement ();
		while (chTag)
		{
			maps[chTag->getIntAttribute (T("Channel"),1)-1].processXml (chTag);
			chTag = chTag->getNextElement ();
		}
	}

	NoteMap maps [16];
};

#endif//_NOTEMAP_H_
