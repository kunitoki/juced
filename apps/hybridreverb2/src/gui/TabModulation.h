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


#ifndef __JUCER_HEADER_TABMODULATION_TABMODULATION_EBE3143E__
#define __JUCER_HEADER_TABMODULATION_TABMODULATION_EBE3143E__

//[Headers]     -- You can add your own extra header files here --
#include "juce_amalgamated.h"

// forward declarations
class MasterAndCommander;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TabModulation  : public Component
{
public:
    //==============================================================================
    TabModulation (MasterAndCommander *m);
    ~TabModulation();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    MasterAndCommander* master;
    //[/UserVariables]

    //==============================================================================
    GroupComponent* groupComponent;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    TabModulation (const TabModulation&);
    const TabModulation& operator= (const TabModulation&);
};


#endif   // __JUCER_HEADER_TABMODULATION_TABMODULATION_EBE3143E__
