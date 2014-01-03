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
#include "IRPlot.h"
#include <math.h>


IRPlot::IRPlot (MasterAndCommander *m)
    : master (m),
      paramEnvelope (0),
      plotMax (0),
      plotRMS (0),
      plotRMSAccu (0),
      plotRMSCounter (0),
      numPlotPoints (0),
      offsetX (64),
      offsetY (32),
      lenEND (0.0)
{
    setSize (448, 228);

    paramEnvelope = new ParamEnvelope();

    numPlotPoints = 1 + 14 * IRPLOT_GRID_X,
    plotMax        = new float[numPlotPoints];
    plotRMS        = new float[numPlotPoints];
    plotRMSAccu    = new float[numPlotPoints];
    plotRMSCounter = new int[numPlotPoints];
    for (int n = 0; n < numPlotPoints; n++)
    {
        plotMax[n]        = -999.9;
        plotRMS[n]        = 0.0;
        plotRMSAccu[n]    = 0.0;
        plotRMSCounter[n] = 0;
    }

    master->registerIRPlot(this);
}

IRPlot::~IRPlot()
{
}


void IRPlot::paint (Graphics& g)
{
    int x, y, y0, y1;

    // white canvas with grey border
    g.fillAll (Colours::white);
    g.setColour (Colour(0xffa6a6a6));
    g.drawRect (0, 0, getWidth(), getHeight());

    // plot IR (maximum)
    g.setColour (Colour(0xff0000B0));
    x = offsetX;
    y0 = offsetY + (int)round(IRPLOT_GRID_Y * (plotMax[0] / -20.0));
    y1 = offsetY + (int)round(IRPLOT_GRID_Y * (-100.0 / -20.0));
    g.drawVerticalLine (x - 1, y0, y1);
    g.drawVerticalLine (x, y0 - 1, y1);
    g.drawVerticalLine (x + 1, y0, y1);
    for (int k = 1; k < numPlotPoints && plotRMSCounter[k] != 0; k++)
    {
        x = offsetX + k;
        y0 = offsetY + (int)round(IRPLOT_GRID_Y * (plotMax[k] / -20.0));
        y1 = offsetY + (int)round(IRPLOT_GRID_Y * (-100.0 / -20.0));
        g.drawVerticalLine (x, y0, y1);
    }

    // plot IR (RMS)
    g.setColour (Colour(0xff000050));
    x = offsetX;
    y0 = offsetY + (int)round(IRPLOT_GRID_Y * (plotRMS[0] / -20.0));
    y1 = offsetY + (int)round(IRPLOT_GRID_Y * (-100.0 / -20.0));
    g.drawVerticalLine (x - 1, y0, y1);
    g.drawVerticalLine (x, y0 - 1, y1);
    g.drawVerticalLine (x + 1, y0, y1);
    for (int k = 1; k < numPlotPoints && plotRMSCounter[k] != 0; k++)
    {
        x = offsetX + k;
        y0 = offsetY + (int)round(IRPLOT_GRID_Y * (plotRMS[k] / -20.0));
        y1 = offsetY + (int)round(IRPLOT_GRID_Y * (-100.0 / -20.0));
        g.drawVerticalLine (x, y0, y1);
    }

    // plot grid
    g.setColour (Colour(0x50000000));
    for (int dB = -100; dB <= 0; dB += 20)
    {
        y = offsetY + (int)round(IRPLOT_GRID_Y * (dB / -20.0));
        g.drawHorizontalLine (y, offsetX, offsetX + IRPLOT_GRID_X * 14);
    }
    for (int i = 0; i <= 9; i++)
    {
        x = offsetX + i * IRPLOT_GRID_X;
        y0 = offsetY;
        y1 = offsetY + 5 * IRPLOT_GRID_Y;
        g.drawVerticalLine (x, y0, y1);
    }

    // plot tick labels
    g.setColour (Colour(0xff000050));
    g.setFont (Font (14.0000f, Font::plain));
    g.drawText (  T("dB"),   0,  24 + 2.5 * IRPLOT_GRID_Y, 30, 16,
                Justification::centredRight, false);
    g.drawText (   T("0"),  14,  24, 40, 16,
                Justification::centredRight, false);
    g.drawText ( T("-20"),  14,  24 + 1 * IRPLOT_GRID_Y, 40, 16,
                Justification::centredRight, false);
    g.drawText ( T("-40"),  14,  24 + 2 * IRPLOT_GRID_Y, 40, 16,
                Justification::centredRight, false);
    g.drawText ( T("-60"),  14,  24 + 3 * IRPLOT_GRID_Y, 40, 16,
                Justification::centredRight, false);
    g.drawText ( T("-80"),  14,  24 + 4 * IRPLOT_GRID_Y, 40, 16,
                Justification::centredRight, false);
    g.drawText (T("-100"),  14,  24 + 5 * IRPLOT_GRID_Y, 40, 16,
                Justification::centredRight, false);
    g.drawText (T("ms"),  offsetX - 20 + 2 * IRPLOT_GRID_X,
                22 + 6 * IRPLOT_GRID_Y, 40, 16,
                Justification::centred, false);
    g.drawText (T("ms"),  offsetX - 20 + 6.5 * IRPLOT_GRID_X,
                22 + 6 * IRPLOT_GRID_Y, 40, 16,
                Justification::centred, false);
    g.drawText (T("0"),  offsetX - 20,  22 + 5.5 * IRPLOT_GRID_Y, 40, 16,
                Justification::centred, false);
    g.drawText (T("5"),  offsetX - 20 + 1 * IRPLOT_GRID_X,
                22 + 5.5 * IRPLOT_GRID_Y, 40, 16,
                Justification::centred, false);
    g.drawText (T("10"),  offsetX - 20 + 2 * IRPLOT_GRID_X,
                22 + 5.5 * IRPLOT_GRID_Y, 40, 16,
                Justification::centred, false);
    g.drawText (T("15"),  offsetX - 20 + 3 * IRPLOT_GRID_X,
                22 + 5.5 * IRPLOT_GRID_Y, 40, 16,
                Justification::centred, false);
    g.drawText (T("20"),  offsetX - 20 + 4 * IRPLOT_GRID_X,
                22 + 5.5 * IRPLOT_GRID_Y, 40, 16,
                Justification::centred, false);
    g.drawText (T("40"),  offsetX - 20 + 5 * IRPLOT_GRID_X,
                22 + 5.5 * IRPLOT_GRID_Y, 40, 16,
                Justification::centred, false);
    g.drawText (T("60"),  offsetX - 20 + 6 * IRPLOT_GRID_X,
                22 + 5.5 * IRPLOT_GRID_Y, 40, 16,
                Justification::centred, false);
    g.drawText (T("80"),  offsetX - 20 + 7 * IRPLOT_GRID_X,
                22 + 5.5 * IRPLOT_GRID_Y, 40, 16,
                Justification::centred, false);
    g.drawText (T("100"),  offsetX - 20 + 8 * IRPLOT_GRID_X,
                22 + 5.5 * IRPLOT_GRID_Y, 40, 16,
                Justification::centred, false);
    g.drawText (T("120"),  offsetX - 20 + 9 * IRPLOT_GRID_X,
                22 + 5.5 * IRPLOT_GRID_Y, 40, 16,
                Justification::centred, false);

    // plot scalable third part
    if (lenEND > 0.0)
    {
        float grid = 0.020;
        while (lenEND / grid > 5)
        {
            grid *= 2.5;
            if (lenEND / grid > 5)
            {
                grid *= 2.0;
                if (lenEND / grid > 5)
                    grid *= 2.0;
            }
        }
        float multi = 1.0;
        int decimals = 0;
        if (grid < 0.075)    // 20..50 ms
        {
            multi = 1000.0;
        }
        else if (grid < 0.75)    // 100..500 ms
        {
            decimals = 1;
        }
        g.setColour (Colour(0xff000050));
        if (multi == 1.0)
        {
            g.drawText (T("s"),  offsetX - 20 + 11.5 * IRPLOT_GRID_X,
                        22 + 6 * IRPLOT_GRID_Y, 40, 16,
                        Justification::centred, false);
        }
        else
        {
            g.drawText (T("ms"),  offsetX - 20 + 11.5 * IRPLOT_GRID_X,
                        22 + 6 * IRPLOT_GRID_Y, 40, 16,
                        Justification::centred, false);
        }
        for (float t0 = grid; t0 - 0.120 <= lenEND; t0 += grid)
        {
            float t = t0 - 0.120;
            int x = (int)roundf(offsetX + IRPLOT_GRID_X * (9.0 + 5.0 * t / lenEND));
            if (t > 0.0)
            {
                int y0 = offsetY;
                int y1 = offsetY + 5 * IRPLOT_GRID_Y;
                g.setColour (Colour(0x50000000));
                g.drawVerticalLine (x, y0, y1);
            }
            if (x > offsetX + 9 * IRPLOT_GRID_X + 20)
            {
                String str;
                if (decimals > 0)
                    str = String(multi * t0, 1);
                else
                    str = String((int)roundf(multi * t0));
                g.setColour (Colour(0xff000050));
                g.drawText (str, x - 19, 22 + 5.5 * IRPLOT_GRID_Y, 40, 16,
                            Justification::centred, false);
            }
        }
    }

    // plot envelope
    float duty[2];
    duty[0] = 6.0;
    duty[1] = 6.0;
    g.setColour (Colour(0xB0FF0000));
    float f_x0 = offsetX;
    float f_x1 = offsetX + 4 * IRPLOT_GRID_X;
    float f_y0 = offsetY - IRPLOT_GRID_Y * (paramEnvelope->db0ms / 20.0 - 1.0);
    float f_y1 = offsetY - IRPLOT_GRID_Y * (paramEnvelope->db20ms / 20.0 - 1.0);
    g.drawDashedLine(f_x0, f_y0, f_x1, f_y1, duty, 2, 3.0);
    f_x0 = f_x1;
    f_y0 = f_y1;
    f_x1 = offsetX + 9 * IRPLOT_GRID_X;
    f_y1 = offsetY - IRPLOT_GRID_Y * (paramEnvelope->db120ms / 20.0 - 1.0);
    g.drawDashedLine(f_x0, f_y0, f_x1, f_y1, duty, 2, 3.0);
    f_x0 = f_x1;
    f_y0 = f_y1;
    f_x1 = offsetX + 14 * IRPLOT_GRID_X;
    f_y1 = offsetY - IRPLOT_GRID_Y * (paramEnvelope->dbENDms / 20.0 - 1.0);
    g.drawDashedLine(f_x0, f_y0, f_x1, f_y1, duty, 2, 3.0);
}


void IRPlot::resized()
{
}


void IRPlot::samples2plot(float *imp1, float *imp2, float *imp3, float *imp4, int len, int fs)
{
    for (int n = 0; n < numPlotPoints; n++)
    {
        plotMax[n]        = -999.9;
        plotRMS[n]        = 0.0;
        plotRMSAccu[n]    = 0.0;
        plotRMSCounter[n] = 0;
    }

    for (int i = 0; i < 4; i++)
    {
        float *imp = 0;
        float dB;
        switch (i)
        {
        case 0:
            imp = imp1;
            break;
        case 1:
            imp = imp2;
            break;
        case 2:
            imp = imp3;
            break;
        case 3:
            imp = imp4;
            break;
        }
        if (imp == 0)
            break;

        float stretch = 1;
        int k    = 0;
        int n    = 0;
        int N20  = (int)round(0.020 * fs);
        int N120 = (int)round(0.120 * fs);

        // 0..20 ms
        stretch = IRPLOT_GRID_X / (0.005 * fs);
        for (n = 0; n < N20 && n < len; n++)
        {
            k = (int)roundf(n * stretch);
            dB = dBfloor(imp[n], -100.0);
            if (dB > plotMax[k])
                plotMax[k] = dB;
            plotRMSAccu[k]    += imp[n] * imp[n];
            plotRMSCounter[k] += 1;
        }

        // 20..120 ms
        stretch = IRPLOT_GRID_X / (0.020 * fs);
        for (; n < N120 && n < len; n++)
        {
            k = (int)roundf((n - N20) * stretch) + 4 * IRPLOT_GRID_X;
            dB = dBfloor(imp[n], -100.0);
            if (dB > plotMax[k])
                plotMax[k] = dB;
            plotRMSAccu[k]    += imp[n] * imp[n];
            plotRMSCounter[k] += 1;
        }

        // 120.. ms
        lenEND = (float)len / (float)fs - 0.120;
        stretch = 5 * IRPLOT_GRID_X / (lenEND * fs);
        for (; n < len; n++)
        {
            k = (int)roundf((n - N120) * stretch) + 9 * IRPLOT_GRID_X;
            if (k >= numPlotPoints)
                break;
            dB = dBfloor(imp[n], -100.0);
            if (dB > plotMax[k])
                plotMax[k] = dB;
            plotRMSAccu[k]    += imp[n] * imp[n];
            plotRMSCounter[k] += 1;
        }

        // rest
        for (; k < numPlotPoints; k++)
        {
            plotMax[k] = -100.0;
        }
    }

    // calculate mean values
    for (int k = 0; k < numPlotPoints; k++)
    {
        if (plotRMSCounter[k] != 0)
        {
            plotRMS[k] = dBfloor10(plotRMSAccu[k] / plotRMSCounter[k], -100.0);
        }
    }

    repaint ();
}


void IRPlot::setEnvelope(ParamEnvelope *param)
{
    paramEnvelope->db0ms   = param->db0ms;
    paramEnvelope->db20ms  = param->db20ms;
    paramEnvelope->db120ms = param->db120ms;
    paramEnvelope->dbENDms = param->dbENDms;
    repaint ();
}


inline float IRPlot::dBfloor(float x, float f)
{
    float dB = 20.0 * log10f(fabs(x));
    if (dB < f)
        return f;
    return dB;
}


inline float IRPlot::dBfloor10(float x, float f)
{
    float dB = 10.0 * log10f(fabs(x));
    if (dB < f)
        return f;
    return dB;
}
