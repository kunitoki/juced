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


#ifndef __HybridConvolver__
#define __HybridConvolver__


#include "SampleData.h"
#include "juce_amalgamated.h"

extern "C" {
#include "libHybridConv/libHybridConv.h"
}


class HybridConvolver
{
public:
    HybridConvolver(void);
    virtual ~HybridConvolver(void);

    virtual void process(float** inputs,
                         float** outputs,
                         int numOutput,
                         int numSamples);
    void process(AudioSampleBuffer& buffer);

protected:
    float *m_inbuf;
    float *m_outbuf;
    int m_bufpos;
    int m_lenShort;
    int m_lenMedium;
    int m_lenLong;
    int m_numFilter;
    int *m_routeIn;
    int *m_routeOut;
};


#endif // __HybridConvolver__
