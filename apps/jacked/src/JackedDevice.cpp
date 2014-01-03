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

#include "JackedDevice.h"

//==============================================================================
JackedDevice::JackedDevice (const String& deviceName)
{
    setText (deviceName);
}

JackedDevice::~JackedDevice ()
{
}

//==============================================================================
void JackedDevice::addInputConnector (const String& portName, const int connectorType)
{
    GraphNodeComponent::addInputConnector (connectorType);

    inputNames.add (portName);
}

void JackedDevice::addOutputConnector (const String& portName, const int connectorType)
{
    GraphNodeComponent::addOutputConnector (connectorType);

    outputNames.add (portName);
}

//==============================================================================
int JackedDevice::getInputConnectorByName (const String& portName) const
{
    return inputNames.indexOf (portName);
}

int JackedDevice::getOutputConnectorByName (const String& portName) const
{
    return outputNames.indexOf (portName);
}

//==============================================================================
String JackedDevice::getInputConnectorName (const int index) const
{
    return getText () + ":" + inputNames [index];
}

String JackedDevice::getOutputConnectorName (const int index) const
{
    return getText () + ":" + outputNames [index];
}

//==============================================================================
void JackedDevice::deleteConnectors (const bool freeConnectors)
{
    GraphNodeComponent::deleteConnectors (freeConnectors);
    
    inputNames.clear ();
    outputNames.clear ();
}

//==============================================================================
bool JackedDevice::operator== (const JackedDevice& other) const throw()
{
    return getText() == other.getText ();
}

bool JackedDevice::operator!= (const JackedDevice& other) const throw()
{
    return getText() != other.getText ();
}

