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

#ifndef __JUCETICE_JACKED_DEVICE_HEADER__
#define __JUCETICE_JACKED_DEVICE_HEADER__

#include "JackedStandardHeader.h"

//==============================================================================
class JackedDevice : public GraphNodeComponent
{
public:

    //==============================================================================
    JackedDevice (const String& deviceName);
    ~JackedDevice ();

    //==============================================================================
    void addInputConnector (const String& portName, const int connectorType = 0);
    void addOutputConnector (const String& portName, const int connectorType = 0);

    int getInputConnectorByName (const String& portName) const;
    int getOutputConnectorByName (const String& portName) const;

    String getInputConnectorName (const int index) const;
    String getOutputConnectorName (const int index) const;

    //==============================================================================
    /** Free all connectors */
    void deleteConnectors (const bool freeConnectors = true);

    //==============================================================================
    /** Compares two arrays.

        Comparisons are case-sensitive.

        @returns    true only if the other array contains exactly the same strings in the same order
    */
    bool operator== (const JackedDevice& other) const throw();

    /** Compares two arrays.

        Comparisons are case-sensitive.

        @returns    false if the other array contains exactly the same strings in the same order
    */
    bool operator!= (const JackedDevice& other) const throw();    

protected:

    StringArray inputNames;
    StringArray outputNames;
};

#endif

