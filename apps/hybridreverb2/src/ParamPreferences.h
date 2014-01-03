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


#ifndef __PARAMPREFERENCES_H__
#define __PARAMPREFERENCES_H__


enum CONST_PARAMPREFERENCES {
    STRATEGY_UNIFORM = 0,
    STRATEGY_LOWEST
};


class ParamPreferences
{
public:
    ParamPreferences()
        : presetFile(String::empty),
          sflen(64),
          strategy(STRATEGY_UNIFORM)
    {
    }

    ParamPreferences(const ParamPreferences &other)
    {
        presetFile = other.presetFile;
        sflen      = other.sflen;
        strategy   = other.strategy;
    }

    ~ParamPreferences()
    {
    }

    ParamPreferences & operator = (const ParamPreferences &other)
    {
        presetFile = other.presetFile;
        sflen      = other.sflen;
        strategy   = other.strategy;
        return *this;
    }

    String presetFile;
    int sflen;
    int strategy;
};


#endif   // __PARAMPREFERENCES_H__
