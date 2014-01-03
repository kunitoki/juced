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

#ifndef __JUCETICE_DATA_HEADER__
#define __JUCETICE_DATA_HEADER__

#include "../StandardHeader.h"

typedef short int IDType;

class DataConnectionAgent;

//===================================================================
//	Data
//===================================================================
/**	This is a base class for all program Data, and has built in
	access control and security. It can make user/data interaction
	a lot safer and easier.

	All parts of your program interface (all widgets and displays)
	should access the Data using a DataConnection. This allows the
	Data to decide at any time whether or not the connection should
	be terminated. It also allows you to automatically recieve
	change messages from your data subclass (call dataChanged() where
	you would like any connections to be notified).

	See the DataConnection class for more information about how it
	should be used. */
class Data	:	public ChangeBroadcaster
{
public:

	Data ();
	~Data ();

	/** Find out if the data is currently being used. */
	bool isBeingUsed ();
	void stopBeingUsed ();
	/** Get a pointer to the object currently using this Data. */
	DataConnectionAgent* getConnection (int index);

	/** Set a custom identifier for this Data. On instantiation,
		each piece of Data will automatically be given a unique
		ID, so you only need to use this if you need your Data to
		have a specific ID. */
	void setDataID (IDType id);
	/** Get the current ID for this Data. */
	IDType getDataID ();
	bool hasSameDataID (Data* thisData);

	inline void dataChanged () { sendChangeMessage (this); }

	friend class DataConnectionAgent;

	juce_UseDebuggingNewOperator;

private:

	Data (const Data&) {}

	/** Grant access to a DataConnection. */
	bool allowConnection (DataConnectionAgent* thisUser);
	/** Terminate access for a DataConnection. */
	void releaseConnection (DataConnectionAgent* thisUser);
	/** Indicate whether or not this Data can be used. */
	bool isAvailable ();

	void addConnection (DataConnectionAgent* thisUser);
	void removeConnection (DataConnectionAgent* thisUser);

	Array<DataConnectionAgent*> connections;

	// This is used to identify a piece of data...
	IDType dataID;
	// This is used to ensure each piece of data has a unique identifier...
	static IDType dataIDCounter;

	bool shouldLockAccessToAdditionalUsers;
	bool shouldAllowMultipleUsers;
	bool isAboutToBeDeleted;
};

#endif//_DATA_H_
