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


#include "HybridConvolver.h"
#include "HybridConvolverDual.h"
#include <stdio.h>
#include <string.h>

#ifndef NO_OMP
#include <omp.h>
#endif

#ifdef _WINDOWS
#include <malloc.h>
#define alloca _alloca
#else
#include <alloca.h>
#endif


HybridConvolverDual::HybridConvolverDual(int lenShort,
                                         int lenMedium,
                                         SampleData *impulses)
{
    m_bufpos    = 0;
    m_lenShort  = lenShort;
    m_lenMedium = lenMedium;
    m_numFilter = 0;

    for (int i = 0; i < 4; i++)
        if (impulses->hasData(i) == true)
            m_numFilter++;

    m_inbuf  = new float[m_numFilter * lenShort];
    m_outbuf = new float[m_numFilter * lenShort];
    memset(m_inbuf,  0, m_numFilter * lenShort * sizeof(float));
    memset(m_outbuf, 0, m_numFilter * lenShort * sizeof(float));

    m_filter = new HConvDual[m_numFilter];

    m_routeIn  = new int[m_numFilter];
    m_routeOut = new int[m_numFilter];

    int hlen = impulses->getDataLen();
    int k = 0;
    for (int i = 0; i < 4; i++)
    {
        if (impulses->hasData(i) == true)
        {
            m_routeIn[k]  = (i / 2) & 1;
            m_routeOut[k] = i & 1;
            hcInitDual(&(m_filter[k]), impulses->getData(i), hlen, m_lenShort, m_lenMedium);
            m_filter[k].step = k % m_filter[k].maxstep;
            k++;
        }
    }
}

HybridConvolverDual::~HybridConvolverDual(void)
{
    for (int i = 0; i < m_numFilter; i++)
    {
        hcCloseDual(&(m_filter[i]));
    }
    delete[] m_filter;
    m_filter = NULL;

    delete[] m_routeIn;
    delete[] m_routeOut;
    m_routeIn  = NULL;
    m_routeOut = NULL;

    delete[] m_inbuf;
    delete[] m_outbuf;
    m_inbuf  = NULL;
    m_outbuf = NULL;
}


void HybridConvolverDual::process(float** inputs, float** outputs, int numOutput, int numSamples)
{
    int pos, new_pos;

    // allocate buffer for SMP processing on the stack
    float **outputSMP = (float**)alloca(m_numFilter * sizeof(float*));
    for (int f = 0; f < m_numFilter; f++)
    {
        outputSMP[f] = (float*)alloca(numSamples * sizeof(float));;
    }

#ifndef NO_OMP
    omp_set_num_threads(m_numFilter);
#pragma omp parallel for private(pos)
#endif
    for (int f = 0; f < m_numFilter; f++)
    {
        pos = m_bufpos;
        float *in  = inputs[m_routeIn[f]];
        float *out = outputSMP[f];
        float *buf_in  = &(m_inbuf[f * m_lenShort]);
        float *buf_out = &(m_outbuf[f * m_lenShort]);
        for (int s = 0; s < numSamples; s++)
        {
            buf_in[pos] = in[s];
            out[s] = buf_out[pos];
            pos++;
            if (pos == m_lenShort)
            {
                hcProcessDual(&(m_filter[f]), buf_in, buf_out);
                pos = 0;
            }
        }
        new_pos = pos;
    }

    m_bufpos = new_pos;

    // clear output buffers
    for (int o = 0; o < numOutput; o++)
        memset(outputs[o], 0, numSamples * sizeof(float));

    for (int f = 0; f < m_numFilter; f++)
        for (int s = 0; s < numSamples; s++)
            outputs[m_routeOut[f]][s] += outputSMP[f][s];
}
