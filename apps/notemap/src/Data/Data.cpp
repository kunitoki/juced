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

#include "Data.h"
#include "DataConnection.h"

IDType Data::dataIDCounter = 0;

Data::Data ()
{
	shouldAllowMultipleUsers = true;
	shouldLockAccessToAdditionalUsers = false;
	isAboutToBeDeleted = false;

	setDataID (dataIDCounter++);
}

Data::~Data ()
{
	isAboutToBeDeleted = true;
	if (isBeingUsed()) stopBeingUsed ();
}

/** Find out if the data is currently being used. */
bool Data::isBeingUsed ()
{
	return (connections.size () > 0);
}

void Data::stopBeingUsed ()
{
	if (isBeingUsed ())
	{
		// we need to close all the connections...
		int numConnections = connections.size ();
		for (int i=numConnections;i>0;i--)
		{
			// we start at the end, because closing will
			// remove a connection from the array we're
			// stepping thru [there are other ways of course!]
			connections[i-1]->close ();
		}
	}
}

/** Get a pointer to the object currently using this Data. */
DataConnectionAgent* Data::getConnection (int index)
{
	return connections[index];
}

/** Grant access to a DataConnection if it is allowed. */
bool Data::allowConnection (DataConnectionAgent* connection)
{
	if (isAvailable ())
	{
		// store a pointer to the user...
		addConnection (connection);
		return true;
	}
	return false;
}

/** Terminate access for a DataConnection. */
void Data::releaseConnection (DataConnectionAgent* connection)
{
	removeConnection (connection);
}

bool Data::isAvailable ()
{
	// First, find out if we're currently being used...
	if (isBeingUsed ())
	{
		// If we're supposed to, we can forbid any extra
		// users from using us.
		if (shouldLockAccessToAdditionalUsers) return false;

		// If we DO have any users, we are only available if
		// we should allow multiple users...
		if (shouldAllowMultipleUsers)
		{
			return true;
		}
		// At this point, we have one (or more) users using us,
		// but we're not allowed to have multiple users, so we
		// definitely aren't available for use.
		else return false;
	}
	else
	{
		// Here, noone is currently using this data, so it's
		// all clear for being used - unless it knows that
		// it's about to be deleted.
		if (isAboutToBeDeleted) return false;
		else return true;
	}
	return true;
}

void Data::addConnection (DataConnectionAgent* connection)
{
	connections.add (connection);
}

void Data::removeConnection (DataConnectionAgent* connection)
{
	connections.removeValue (connection);
}

void Data::setDataID (IDType newID) { dataID = newID; }

IDType Data::getDataID () { return dataID; }

bool Data::hasSameDataID (Data* thisData)
{
	if (thisData)
	{
		if ((thisData->getDataID ()) == getDataID ()) return true;
	}
	return false;
}
