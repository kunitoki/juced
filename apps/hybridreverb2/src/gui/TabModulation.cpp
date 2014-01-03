/***************************************************************************
 *   Copyright (C) 2009 by Christian Borss                                 *
 *   christian.borss@rub.de                                                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


//[Headers] You can add your own extra header files here...
#include "../MasterAndCommander.h"
//[/Headers]

#include "TabModulation.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
TabModulation::TabModulation (MasterAndCommander *m)
    : master (m),
      groupComponent (0)
{
    addAndMakeVisible (groupComponent = new GroupComponent (T("new group"),
                                                            T("Modulation Configuration")));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (828, 548);

    //[Constructor] You can add your own custom stuff here..
//    master->print("TabModulation::TabModulation : Waiting for your commands, Sir!");
    master->registerTabModulation(this);
    //[/Constructor]
}

TabModulation::~TabModulation()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (groupComponent);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TabModulation::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xffffe000));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TabModulation::resized()
{
    groupComponent->setBounds (8, 8, 808, 500);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TabModulation" componentName=""
                 parentClasses="public Component" constructorParams="MasterAndCommander *m"
                 variableInitialisers="master (m)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330000013" fixedSize="0" initialWidth="828"
                 initialHeight="548">
  <BACKGROUND backgroundColour="ffffe000"/>
  <GROUPCOMPONENT name="new group" id="fada51a9ace7abb" memberName="groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="8 8 808 500" title="Modulation Configuration"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
