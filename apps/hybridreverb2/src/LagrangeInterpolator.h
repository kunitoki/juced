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


#ifndef __LAGRANGEINTERPOLATOR_H__
#define __LAGRANGEINTERPOLATOR_H__


#include "juce_amalgamated.h"


#define C_2    0.5
#define C_3    0.33333333333333333333
#define C_6    0.16666666666666666667


class LagrangeInterpolator
{
public:
    LagrangeInterpolator (float *y, int n, float x, float r);
    ~LagrangeInterpolator();

    void update (float *y);
    float interpolate (float x);


private:
    float *data;
    int num;
    float first;
    float ratio;
};


#endif   // __LAGRANGEINTERPOLATOR_H__
