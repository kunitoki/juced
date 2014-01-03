
/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2007 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2007 by Julian Storer.

 ------------------------------------------------------------------------------

 JUCE and JUCETICE can be redistributed and/or modified under the terms of
 the GNU General Public License, as published by the Free Software Foundation;
 either version 2 of the License, or (at your option) any later version.

 JUCE and JUCETICE are distributed in the hope that they will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with JUCE and JUCETICE; if not, visit www.gnu.org/licenses or write to
 Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 Boston, MA 02111-1307 USA

 ==============================================================================
 */

#ifndef __JUCETICE_DYNAMICPARAMETERSLIDER_HEADER__
#define __JUCETICE_DYNAMICPARAMETERSLIDER_HEADER__

#include "../../StandardHeader.h"
#include "../../XSynthPlugin.h"
#include "../../XSynthParameters.h"


//==============================================================================
/**
     A parameter listener slider with dynamic set possibility
*/
class DynamicParameterSlider  : public ParameterSlider
{
public:

    //==============================================================================
    DynamicParameterSlider (const String& sliderName)
        : ParameterSlider (sliderName),
          owner (0),
          partNumber (-1),
          parameterNumber (-1),
          groupNumber (0)
    {
    }

    virtual ~DynamicParameterSlider()
    {
        resetOwner ();
    }

    //==============================================================================
    void setOwner (XSynthPlugin* const owner_,
                   const int partNumber_,
                   const int groupNumber_)
    {
        owner = owner_;
        partNumber = partNumber_;
        groupNumber = groupNumber_;
    }

    void resetOwner ()
    {
        setDynamicParameter (-1, false);

        owner = 0;
        partNumber = -1;
    }

    //==============================================================================
    void setDynamicParameter (const int result, const bool locking = true)
    {
        if (! owner) return;

        if (parameterNumber >= 0)
        {
            if (locking) owner->getParameterLock ().enter();
                owner->removeListenerToParameter (parameterNumber, this);
            if (locking) owner->getParameterLock ().exit();
        }

        if (result >= PPAR(partNumber, 0)
            && result < PPAR(partNumber, TOTAL_PART_PARAMETERS))
        {
            {
            if (locking) owner->getParameterLock ().enter();
                owner->addListenerToParameter (result, this);
            if (locking) owner->getParameterLock ().exit();
            }

            setValue (owner->getParameterMapped (result), false);
            setTooltip (owner->getParameterName (result));

            // TODO - specific part !
            Master* master = owner->getMaster ();
            master->part [partNumber]->Pctrl [groupNumber] = result;
            // TODO - specific part !
        }
        else
        {
            setValue (0.5f, false);
            setTooltip (String::empty);
        }

        parameterNumber = result;
    }

    //==============================================================================
    int getCurrentParameter ()                        { return parameterNumber; }

    void parameterChanged (AudioParameter* parameter, const int index)
    {
        setValue (parameter->getValueMapped (), false);
    }

    //==============================================================================
    void mouseDown (const MouseEvent& e)
    {
        if (e.mods.isRightButtonDown ())
        {
            PopupMenu menu;
            menu.addSectionHeader ("Select parameter for part");
            for (int i = 0; i < TOTAL_PART_PARAMETERS; i++)
            {
                int offsetParameter = PPAR(partNumber, i);

                menu.addItem (offsetParameter + 1,
                              owner->getParameterName (offsetParameter),
                              true,
                              (offsetParameter == parameterNumber) ? true : false);
            }

            const int result = menu.show();
            if (result > 0)
                setDynamicParameter (result - 1, true);
        }
        else
        {
            ParameterSlider::mouseDown (e);
        }
    }

protected:

    XSynthPlugin* owner;
    int partNumber;
    int parameterNumber;
    int groupNumber;
};


#endif // __JUCETICE_DYNAMICPARAMETERSLIDER_HEADER__
