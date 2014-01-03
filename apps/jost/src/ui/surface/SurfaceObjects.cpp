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

#include "SurfaceObjects.h"
#include "SurfaceComponent.h"



//==============================================================================
SurfaceObject::SurfaceObject (SurfaceComponent* owner_)
  : owner (owner_),
    plugin (0)
{
}

SurfaceObject::~SurfaceObject ()
{
}

void SurfaceObject::setPlugin (uint32 newPlugin)
{
    if (plugin != newPlugin)
    {
        plugin = newPlugin;
        removeAllParameters ();
    }
}

uint32 SurfaceObject::getPlugin () const
{
    return plugin;
}

void SurfaceObject::setParameter (const int index, const int n)
{
    parameters.set (index, n);
}

int SurfaceObject::getParameter (const int index) const
{
    return parameters [index];
}

void SurfaceObject::removeAllParameters ()
{
    parameters.clear ();
}

int SurfaceObject::getNumParameters () const
{
    return parameters.size ();
}

//==============================================================================
SurfaceSlider::SurfaceSlider (SurfaceComponent* owner_)
    : Slider (String::empty),
      SurfaceObject (owner_)
{
}

SurfaceSlider::~SurfaceSlider ()
{
}

void SurfaceSlider::focusGained (Component::FocusChangeType cause)
{
    owner->surfaceObjectChanged (this);
}

void SurfaceSlider::mouseDown (const MouseEvent& e)
{
    owner->surfaceObjectChanged (this);

    Slider::mouseDown (e);
}

//==============================================================================
SurfaceLabel::SurfaceLabel (SurfaceComponent* owner_)
    : Label (String::empty, "No label set"),
      SurfaceObject (owner_)
{
}

SurfaceLabel::~SurfaceLabel ()
{
}

void SurfaceLabel::focusGained (Component::FocusChangeType cause)
{
    owner->surfaceObjectChanged (this);
}

void SurfaceLabel::mouseDown (const MouseEvent& e)
{
    owner->surfaceObjectChanged (this);

    Label::mouseDown (e);
}

//==============================================================================
SurfaceJoystick::SurfaceJoystick (SurfaceComponent* owner_)
    : Joystick (),
      SurfaceObject (owner_)
{
}

SurfaceJoystick::~SurfaceJoystick ()
{
}

void SurfaceJoystick::focusGained (Component::FocusChangeType cause)
{
    owner->surfaceObjectChanged (this);
}

void SurfaceJoystick::mouseDown (const MouseEvent& e)
{
    owner->surfaceObjectChanged (this);

    Joystick::mouseDown (e);
}

