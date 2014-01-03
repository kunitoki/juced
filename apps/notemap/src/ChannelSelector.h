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

#ifndef __JUCETICE_CHANNELSELECTOR_HEADER__
#define __JUCETICE_CHANNELSELECTOR_HEADER__

#include "StandardHeader.h"


class ChannelSelector	:	public Component,
							public ButtonListener,
							public ChangeBroadcaster
{
public:

	ChannelSelector ()
	{
		for (int i=0; i<16; i++)
		{
			channels[i] = new TextButton (String(i+1), T("Channel ") + String(i+1));
			addAndMakeVisible (channels[i]);
			channels[i]->addButtonListener (this);
			channels[i]->setRadioGroupId (1342);
			// channels[i]->setTextColour (Colours::white);
			// channels[i]->setBackgroundColours (Colours::darkgrey.darker(0.6f), Colours::orange);
			channels[i]->setClickingTogglesState (true);

			switch (i)
			{
			case 0:
				channels[i]->setConnectedEdges (
					Button::ConnectedOnRight + Button::ConnectedOnBottom);
				break;
			case 1:
			case 2:
				channels[i]->setConnectedEdges (
					Button::ConnectedOnBottom
					+ Button::ConnectedOnLeft
					+ Button::ConnectedOnRight);
				break;
			case 3:
				channels[i]->setConnectedEdges (
					Button::ConnectedOnLeft + Button::ConnectedOnBottom);
				break;
			case 4:
			case 8:
				channels[i]->setConnectedEdges (
					Button::ConnectedOnRight
					+ Button::ConnectedOnBottom
					+ Button::ConnectedOnTop);
				break;
			case 5:
			case 6:
			case 9:
			case 10:
				channels[i]->setConnectedEdges (
					Button::ConnectedOnRight + Button::ConnectedOnBottom
					+ Button::ConnectedOnLeft + Button::ConnectedOnTop);
				break;
			case 7:
			case 11:
				channels[i]->setConnectedEdges (
					Button::ConnectedOnLeft
					+ Button::ConnectedOnBottom
					+ Button::ConnectedOnTop);
				break;
			case 12:
				channels[i]->setConnectedEdges (
					Button::ConnectedOnTop + Button::ConnectedOnRight);
				break;
			case 13:
			case 14:
				channels[i]->setConnectedEdges (
					Button::ConnectedOnTop
					+ Button::ConnectedOnRight
					+ Button::ConnectedOnLeft);
				break;
			case 15:
				channels[i]->setConnectedEdges (
					Button::ConnectedOnTop + Button::ConnectedOnLeft);
				break;
			default:
				break;
			};
		}
		selectChannel (1);
	}

	~ChannelSelector ()
	{
		deleteAllChildren ();
	}

	void resized ()
	{
		const int bw = getWidth()/4;
		const int bh = getHeight()/4;

		for (int y=0; y<4; y++)
		{
			for (int x=0; x<4; x++)
			{
				channels[4*y+x]->setBounds (x*bw,y*bh,bw,bh);
			}
		}
	}

	void buttonClicked (Button* button)
	{
		for (int i=0; i<16; i++)
		{
			if (button == channels[i])
			{
				currentChannel = i+1;
				sendChangeMessage (this);
				break;
			}
		}
	}

	void selectChannel (int channel, bool sendMessage = false)
	{
		channels [channel-1]->setToggleState (true, sendMessage);
		currentChannel = channel;
	}

	int getSelectedChannel ()
	{
		return currentChannel;
	}

private:

	TextButton* channels [16];
	int currentChannel;
};

#endif//_CHANNELSELECTOR_H_
