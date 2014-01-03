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


#ifndef __PARAMTIMBRE_H__
#define __PARAMTIMBRE_H__


#include <math.h>


class ParamTimbre
{
public:
    ParamTimbre()
        : data(0)
    {
        num    = 25;
        freq   = 62.5;
        ratio  = pow(2.0, 1.0/3.0);
        smooth = 0.0;
        data = new float[num];
        for (int i = 0; i < num; i++)
            data[i] = 0.0;
    }

    ParamTimbre(const ParamTimbre &other)
        : data(0)
    {
        set(other.data,
            other.num,
            other.freq,
            other.ratio,
            other.smooth);
    }

    ParamTimbre(float *y, int n, float f, float r, float s)
        : data(0)
    {
        set(y, n, f, r, s);
    }

    ~ParamTimbre()
    {
        if (data)
            delete[] data;
        data = 0;
    }

    ParamTimbre & operator = (const ParamTimbre &other)
    {
        set(other.data,
            other.num,
            other.freq,
            other.ratio,
            other.smooth);
        return *this;
    }

    void set(float *y, int n, float f, float r, float s)
    {
        if (data)
            delete[] data;
        data = new float[n];
        for (int i = 0; i < n; i++)
            data[i] = y[i];
        num    = n;
        freq   = f;
        ratio  = r;
        smooth = s;
    }

    void set(ParamTimbre *param)
    {
        set(param->data, param->num, param->freq, param->ratio, param->smooth);
    }

    float *data;
    int num;
    float freq;
    float ratio;
    float smooth;
};


#endif   // __PARAMTIMBRE_H__
