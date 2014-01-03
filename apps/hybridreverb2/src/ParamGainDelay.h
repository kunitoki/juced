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


#ifndef __PARAMGAINDELAY_H__
#define __PARAMGAINDELAY_H__


class ParamGainDelay
{
public:
    ParamGainDelay()
        : initialGap(0.0),
          length(-1.0),
          preDelay(0.0),
          dryGain(0.0),
          wetGain(0.0),
          masterGain(0.0)
    {
    }

    ParamGainDelay(const ParamGainDelay &other)
    {
        initialGap = other.initialGap;
        length     = other.length;
        preDelay   = other.preDelay;
        dryGain    = other.dryGain;
        wetGain    = other.wetGain;
        masterGain = other.masterGain;
    }

    ~ParamGainDelay()
    {
    }

    ParamGainDelay & operator = (const ParamGainDelay &other)
    {
        initialGap = other.initialGap;
        length     = other.length;
        preDelay   = other.preDelay;
        dryGain    = other.dryGain;
        wetGain    = other.wetGain;
        masterGain = other.masterGain;
        return *this;
    }

    float initialGap;
    float length;
    float preDelay;
    float dryGain;
    float wetGain;
    float masterGain;
};


#endif   // __PARAMGAINDELAY_H__
