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


#ifndef __PARAMIMPULSERESPONSES_H__
#define __PARAMIMPULSERESPONSES_H__


class ParamImpulseResponses
{
public:
    ParamImpulseResponses()
        : ll(String::empty),
          lr(String::empty),
          rl(String::empty),
          rr(String::empty)
    {
    }

    ParamImpulseResponses(const ParamImpulseResponses &other)
    {
        ll = other.ll;
        lr = other.lr;
        rl = other.rl;
        rr = other.rr;
    }

    ~ParamImpulseResponses()
    {
    }

    ParamImpulseResponses & operator = (const ParamImpulseResponses &other)
    {
        ll = other.ll;
        lr = other.lr;
        rl = other.rl;
        rr = other.rr;
        return *this;
    }

    String ll;
    String lr;
    String rl;
    String rr;
};


#endif   // __PARAMIMPULSERESPONSES_H__
