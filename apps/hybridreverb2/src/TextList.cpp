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


#include "TextList.h"
#include "gui/TabTimbre.h"
#include <math.h>


TextList::TextList()
{
}

TextList::~TextList()
{
}


////////////////////////////////////////////////////////////////
//
//    public methods
//

void TextList::clear(void)
{
    textVector.clear();
}

int TextList::getPos(const String & entry)
{
    int size = textVector.size();

    for (int i = 0; i < size; i++)
    {
        if (textVector[i] == entry)
            return i;
    }
    textVector.push_back(entry);

    return size;
}


const String & TextList::getEntry(int pos)
{
    return textVector.at(pos);
}


const std::vector<String> & TextList::getList(void)
{
    return textVector;
}
