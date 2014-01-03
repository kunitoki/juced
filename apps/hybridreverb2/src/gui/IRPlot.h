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


#ifndef __IRPLOT_H__
#define __IRPLOT_H__


#include "juce_amalgamated.h"
#include "../ParamEnvelope.h"


enum IRPLOT_CONSTANTS { IRPLOT_GRID_X = 25,
                        IRPLOT_GRID_Y = 30 };


// forward declarations
class MasterAndCommander;


class IRPlot  : public Component
{
public:
    IRPlot (MasterAndCommander *m);
    ~IRPlot();

    void paint (Graphics& g);
    void resized();

    void samples2plot(float *imp1, float *imp2, float *imp3, float *imp4, int len, int fs);
    void setEnvelope(ParamEnvelope *param);

    juce_UseDebuggingNewOperator

private:
    MasterAndCommander* master;
    ParamEnvelope* paramEnvelope;
    float *plotMax,
          *plotRMS,
          *plotRMSAccu;
    int *plotRMSCounter;
    int numPlotPoints;
    int offsetX,
        offsetY;
    float lenEND;

    // (prevent copy constructor and operator= being generated..)
    IRPlot (const IRPlot&);
    const IRPlot& operator= (const IRPlot&);

    float dBfloor(float x, float f);
    float dBfloor10(float x, float f);
};


#endif   // __IRPLOT_H__
