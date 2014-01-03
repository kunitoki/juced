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

#ifndef __JUCETICE_DATACONNECTION_HEADER__
#define __JUCETICE_DATACONNECTION_HEADER__

#include "Data.h"

//===================================================================
/** This is where the main functions for DataConnection live, but
	you won't want to use this class directly.
*/
class DataConnectionAgent
{
public:

	DataConnectionAgent ()
	{
		currentlyUsedData = 0;
		changeListener = 0;
	}

	~DataConnectionAgent () { close (); }

	/** Find out if this User is currently using any Data. */
	bool exists ()
	{
		return (currentlyUsedData != 0);
	}

	/** Stop using the currently used Data. */
	void close ()
	{
		if (exists ())
		{
			// stop the last user from listening to this data...
			if (changeListener)
				currentlyUsedData->removeChangeListener (changeListener);
			// ... and release the connection to the data...
			currentlyUsedData->releaseConnection (this);
			currentlyUsedData = 0; // clear the data pointer.
		}
	}

	/** This allows you to automatically recieve a message from a
		piece of data you connect to if it changes. This should
		be set ideally in the constructor of the class using this
		connection. */
	void setChangeListenerForFutureConnections (ChangeListener* listener)
	{
		changeListener = listener;
	}

	juce_UseDebuggingNewOperator;

protected:

	/** Try to start using a piece of Data. */
	bool open (Data* data)
	{
		if (	// if the data is not a NULL pointer...
				(data)
			&&	// AND it is different to the current data...
				(data != currentlyUsedData))
		{
			if (exists ()) close (); // close any open connection...

			if (data->allowConnection (this))
			{
				// store the data pointer...
				currentlyUsedData = data;
				// and set the changeListener if needed...
				if (changeListener)
					currentlyUsedData->addChangeListener (changeListener);
				return true;
			}
		}
		return false;
	}

	/** Get a pointer to the currently used Data. */
	Data* getData () { return currentlyUsedData; }

	friend class Data;

private:

	Data* currentlyUsedData;
	ChangeListener* changeListener;

};

//===================================================================
//	DataConnection
//===================================================================
/**	A DataConnection should be used by any part of your application
	that needs to have access to a piece of the Data.

	It is used mostly as a pointer, but it also has a few functions
	that ensure the Data isn't accessed when it doesn't exist.

	To use it in, for example, a control widget, simply give your
	object a DataConnection<MyData> member. You can then use it
	like a pointer (assignation with '=' and access with '->'). If
	you want to return a pointer to the Data, you use the data()
	function [i.e. return myDataConnection.data ();]

	The main power of this system is in the 'exists()' function.
	Simply test it in every function before you try to access the
	Data, and you will be safe from accessing a dangling pointer.

	i.e.
	@code

		class DisplayWidget	:	public Component
		{
		private:
		...
		DataConnection<MyDataType> myData;
		...
		public:
		...
		void update ()
		{
			if (myData.exists ())
			{
				setName (myData->getName ());
				setValue (myData->getValue ());
			}
			else clear ();
		}
		...

	@endcode

	You'll of course want a 'setDataSource' or similarly named function
	to simply assign the connection to a piece of Data. The Connection
	will ask the Data if it can be used, and will open a connection if
	so. If the Data closes the connection at any time (which happens
	automatically on the destruction of the Data), exists() will return
	false, so you don't accidentally use the pointer (which gets reset
	to null anyway).

	The other cool thing you can do is call the function
	setChangeListenerForFutureConnections (this) in your object's
	constructor (if it's of course a change listener). This will
	cause your object to automatically register as a ChangeListener
	with your Data whenever a connection is opened. You will then
	be notified of any changes made to the Data.

	In your changeListenerCallback, remember that to check the
	change source against the Data pointer you must use the data()
	member function. [i.e. if (source == myData.data()) { ... }] 	*/
template <class DataObject>
class DataConnection	:	public DataConnectionAgent
{
public:

	/** Connect to the specified Data object. */
	const DataConnection<DataObject>& operator=(DataObject* object)
	{
		open ((Data*) object);
		return *this;
	}

	/** Use this DataConnection as a pointer. */
	DataObject* operator->() { return (DataObject*) getData (); }
	/** Get the Data object attached to this connection. */
	DataObject* data () { return (DataObject*) getData (); }

};

#endif//_DATAUSER_H_
