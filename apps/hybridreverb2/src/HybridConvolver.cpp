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


HybridConvolver::HybridConvolver() :
    m_bufpos(0),
    m_lenShort(256),
    m_lenMedium(1024),
    m_lenLong(4096),
    m_numFilter(0)
{
}


HybridConvolver::~HybridConvolver(void)
{
}


void HybridConvolver::process(float** inputs, float** outputs, int numOutput, int numSamples)
{
}


void HybridConvolver::process(AudioSampleBuffer& buffer)
{
    int numSamples = buffer.getNumSamples();
    int numChannels = buffer.getNumChannels();
    float **data = new float*[numChannels];
    for (int i = 0; i < numChannels; i++)
        data[i] = buffer.getSampleData(i);
    process(data, data, numChannels, numSamples);
    delete[] data;
}
