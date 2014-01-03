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


#include "LagrangeInterpolator.h"
#include "gui/TabTimbre.h"
#include <math.h>


LagrangeInterpolator::LagrangeInterpolator(float *y, int n, float x, float r)
    : data(0),
      num(n + 4),
      first(x / r),
      ratio(r)
{
    data = new float[num];
    update(y);
}

LagrangeInterpolator::~LagrangeInterpolator()
{
    delete[] data;
    data = 0;
    num = 0;
}


////////////////////////////////////////////////////////////////
//
//    public methods
//

void LagrangeInterpolator::update(float *y)
{
    int n = num - 4;

    data[0] = 2.0 * y[0] - y[1];
    data[1] = data[0];
    for (int i = 0; i < n; i++)
        data[i + 2] = y[i];
    data[num - 2] = 2.0 * y[n - 1] - y[n - 2];
    data[num - 1] = data[num - 2];
}


float LagrangeInterpolator::interpolate (float x)
{
    float pos = logf(x / first) / logf(ratio);
    if (pos <= 0.0)
    {
        return data[0];
    }
    if (pos >= num - 3)
    {
        return data[num - 1];
    }
    int n = (int)floor(pos);
    float lambda   = pos - n;
    float lambda_2 = lambda * lambda;
    float lambda_3 = lambda * lambda_2;
    float c_0 = data[n+1];
    float c_1 = data[n+2] - data[n] * C_3 - data[n+1] * C_2 - data[n+3] * C_6;
    float c_2 = (data[n+2] + data[n]) * C_2 - data[n+1];
    float c_3 = (data[n+3] - data[n]) * C_6 + (data[n+1] - data[n+2]) * C_2;

    return c_3 * lambda_3 + c_2 * lambda_2 + c_1 * lambda + c_0;
}
