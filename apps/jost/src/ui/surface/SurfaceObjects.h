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

#ifndef __JUCETICE_JOSTSURFACEOBJECTS_HEADER__
#define __JUCETICE_JOSTSURFACEOBJECTS_HEADER__

#include "../../Config.h"
#include "../../model/Host.h"

class SurfaceComponent;
class InternalSurfaceComponent;


//==============================================================================
class SurfaceObject
{
public:

    virtual ~SurfaceObject ();

    virtual int getMaximumParameters () const = 0;

    void setPlugin (uint32 newPlugin);
    uint32 getPlugin () const;

    void setParameter (const int index, const int n);
    int getParameter (const int index) const;
    void removeAllParameters ();
    int getNumParameters () const;

protected:
    
    SurfaceObject (SurfaceComponent* owner_);

    SurfaceComponent* owner;
    uint32 plugin;
    Array<int> parameters;
};


//==============================================================================
class SurfaceSlider : public Slider, 
                      public SurfaceObject
{
public:

    SurfaceSlider (SurfaceComponent* owner);
    ~SurfaceSlider ();

    int getMaximumParameters () const                        { return 1; }

    void focusGained (Component::FocusChangeType cause);
    void mouseDown (const MouseEvent& e);

protected:
};


//==============================================================================
class SurfaceLabel : public Label, 
                     public SurfaceObject
{
public:

    SurfaceLabel (SurfaceComponent* owner);
    ~SurfaceLabel ();

    int getMaximumParameters () const                        { return 0; }

    void focusGained (Component::FocusChangeType cause);
    void mouseDown (const MouseEvent& e);

protected:
};


//==============================================================================
class SurfaceJoystick : public Joystick, 
                        public SurfaceObject
{
public:

    SurfaceJoystick (SurfaceComponent* owner);
    ~SurfaceJoystick ();

    int getMaximumParameters () const                        { return 2; }

    void focusGained (Component::FocusChangeType cause);
    void mouseDown (const MouseEvent& e);

protected:
};


#endif // __JUCETICE_JOSTSURFACEOBJECTS_HEADER__

