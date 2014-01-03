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


#include "../windows_quirks.h"
#include "../MasterAndCommander.h"
#include "FreqPlot.h"
#include "TabTimbre.h"
#include "../LagrangeInterpolator.h"
#include <math.h>


FreqPlot::FreqPlot (MasterAndCommander *m)
    : master(m),
      gridX(32),
      gridY(32),
      offsetX(32),
      offsetY(32),
      numSlider(0),
      freqSlider(1.0),
      freqRate(1.0),
      numLevel(0),
      freqLevel(1.0),
      level(0),
      impulse(0),
      fs(0)
{
    setSize (776, 460);

    master->registerFreqPlot(this);
}

FreqPlot::~FreqPlot()
{
}


void FreqPlot::paint (Graphics& g)
{
    int width = getWidth();
    int height = getHeight();
    // white canvas with grey border
    g.fillAll (Colours::white);
    g.setColour (Colour(0xffa6a6a6));
    g.drawRect (0, 0, width, height);

    // plot grid
    g.setColour (Colour(0x50000000));
    for (int i = 0; i < numSlider; i++)
    {
        int x = offsetX + i * gridX;
        g.drawVerticalLine (x, offsetY, offsetY + 6 * gridY);
    }
    for (int i = 0; i < 7; i++)
    {
        int y = offsetY + i * gridY;
        g.drawHorizontalLine (y, offsetX, offsetX + gridX * (numSlider - 1));
    }

    // plot transfer function
    g.setColour (Colour(0xB0FF0000));
    double f = freqLevel;
    int startX = offsetX + round(gridX * log(f / double(freqSlider)) / log(freqRate));
    int startY = offsetY - gridY * (level[0] - 20.0) / 20.0;
    int endX;
    int endY;
    for (int n = 0; n < numLevel - 1; n++)
    {
        f = (n + 2.0) * freqLevel;
        endX = offsetX + round(gridX * log(f / double(freqSlider)) / log(freqRate));
        endY = offsetY - gridY * (level[n + 1] - 20.0) / 20.0;
        if (startX >= 8 && endX < width - 8 &&
            startY >= 8 && endY < height - 8)
            g.drawLine(startX, startY, endX, endY, 3.0);
        startX = endX;
        startY = endY;
    }

    // plot impulse response
    int offsetTimeX = offsetX;
    int offsetTimeY = offsetY + 192;
    float tTotal = 1.0 / freqLevel;
    int wMax = width - offsetTimeX - 28;
    int pixel_5ms = floor(0.005 * wMax / tTotal);
    int posOrigin = offsetTimeX + roundf(pixel_5ms * 0.5 * tTotal / 0.005);
    g.setColour (Colour(0xff000050));
    for (int n = 0; n < 2 * numLevel; n++)
    {
        float db = 20.0 * log10f(fabs(impulse[n]));
        if (db > -120.0)
        {
            float t = tTotal * float(n - numLevel) / float(2.0 * numLevel);
            int x = posOrigin + roundf(t / 0.005 * pixel_5ms);
            int startY = offsetTimeY - gridY * (db - 20.0) / 20.0;
            int endY   = offsetTimeY + 6 * gridY;
            if (x >= 0 && x < width &&
                startY >= 0 && startY <= endY)
                g.drawVerticalLine (x, startY, endY);
        }
    }

    g.setColour (Colour(0x50000000));
    g.drawVerticalLine (posOrigin, offsetTimeY, offsetTimeY + 6 * gridY);
    for (int n = 1; n * 0.005 < 0.5 * tTotal; n++)
    {
        g.drawVerticalLine (posOrigin + n * pixel_5ms, offsetTimeY,
                            offsetTimeY + 6 * gridY);
        g.drawVerticalLine (posOrigin - n * pixel_5ms, offsetTimeY,
                            offsetTimeY + 6 * gridY);
    }
    float t = -0.5 * tTotal;
    int pos1 = posOrigin + roundf(t / 0.005 * pixel_5ms);
    g.drawVerticalLine (pos1, offsetTimeY, offsetTimeY + 6 * gridY);
    t = 0.5 * tTotal;
    int pos2 = posOrigin + roundf(t / 0.005 * pixel_5ms);
    g.drawVerticalLine (pos2, offsetTimeY, offsetTimeY + 6 * gridY);
    for (int n = 0; n < 7; n++)
    {
        int y = offsetTimeY + n * gridY;
        g.drawHorizontalLine (y, pos1, pos2);
    }

}


void FreqPlot::resized()
{
}


void FreqPlot::init(int gx, int gy, int ox, int oy,
                    int nSlider, float fSlider, float fRate,
                    int nData, float fData)
{
    gridX   = gx;
    gridY   = gy;
    offsetX = ox;
    offsetY = oy;

    numSlider  = nSlider;
    freqSlider = fSlider;
    freqRate   = fRate;

    numLevel  = nData;
    freqLevel = fData;
    level     = new float[numLevel];
    for (int i = 0; i < numLevel; i++)
        level[i] = 0.0;

    impulse = new float[2 * numLevel];
    for (int i = 0; i < 2 * numLevel; i++)
        impulse[i] = 0.0;
    impulse[numLevel] = 1.0;

    repaint ();
}


void FreqPlot::setLevel(float *data)
{
    for (int i = 0; i < numLevel; i++)
        level[i] = data[i];

    repaint ();
}


void FreqPlot::setImpulse(float *data)
{
    for (int i = 0; i < 2 * numLevel; i++)
        impulse[i] = data[i];

    repaint ();
}
