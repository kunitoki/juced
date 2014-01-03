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


#ifndef __PARAMENVELOPE_H__
#define __PARAMENVELOPE_H__


class ParamEnvelope
{
public:
    ParamEnvelope()
        : db0ms(0.0),
          db20ms(0.0),
          db120ms(0.0),
          dbENDms(0.0)
    {
    }

    ParamEnvelope(const ParamEnvelope &other)
    {
        db0ms   = other.db0ms;
        db20ms  = other.db20ms;
        db120ms = other.db120ms;
        dbENDms = other.dbENDms;
    }

    ~ParamEnvelope()
    {
    }

    ParamEnvelope & operator = (const ParamEnvelope &other)
    {
        db0ms   = other.db0ms;
        db20ms  = other.db20ms;
        db120ms = other.db120ms;
        dbENDms = other.dbENDms;
        return *this;
    }

    float db0ms;
    float db20ms;
    float db120ms;
    float dbENDms;
};


#endif   // __PARAMENVELOPE_H__
