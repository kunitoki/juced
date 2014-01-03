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


#ifndef __FREQPLOT_H__
#define __FREQPLOT_H__


#include "juce_amalgamated.h"


// forward declarations
class MasterAndCommander;


class FreqPlot  : public Component
{
public:
    FreqPlot (MasterAndCommander *m);
    ~FreqPlot();

    void paint (Graphics& g);
    void resized();

    void init(int gx, int gy, int ox, int oy,
              int nSlider, float fSlider, float fRate,
              int nData, float fData);

    void setLevel(float *data);
    void setImpulse(float *data);

    juce_UseDebuggingNewOperator

private:
    MasterAndCommander *master;
    int gridX;
    int gridY;
    int offsetX;
    int offsetY;
    int numSlider;
    float freqSlider;
    float freqRate;
    int numLevel;
    float freqLevel;
    float *level;
    float *impulse;
    float fs;

    // (prevent copy constructor and operator= being generated..)
    FreqPlot (const FreqPlot&);
    const FreqPlot& operator= (const FreqPlot&);
};


#endif   // __FREQPLOT_H__
