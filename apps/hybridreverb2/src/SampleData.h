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


#ifndef __SAMPLEDATA_H__
#define __SAMPLEDATA_H__


#include "juce_amalgamated.h"
#include "ParamGainDelay.h"
#include "ParamEnvelope.h"
#include "ParamImpulseResponses.h"

extern "C" {
#include "libHybridConv/libHybridConv.h"
}


class SampleData
{
public:
    SampleData ();
    ~SampleData();

    void applyLoadFiles(String dir,
                        String fileLL,
                        String fileLR,
                        String fileRL,
                        String fileRR);
    void applyLoadFiles(String dir, ParamImpulseResponses *param);
    int loadSingleFile(String filename, int num);
    void applyGainDelay(SampleData *source, ParamGainDelay *param);
    void applyEnvelope(SampleData *source, ParamEnvelope *param);
    void applyTimbre(SampleData *source, int filterLen, float *filter);
    float *getData(int num);
    int getDataLen(void);
    int getSampleRate(void);
    bool hasData(int num);


private:
    float *samplesLL,
          *samplesLR,
          *samplesRL,
          *samplesRR;
    int bufferLen;    // number of samples which fit into the sample buffers
    int dataLen;    // number of samples in the sample buffers
    int fs;
    bool available[4];

    void checkLength(int len);
    void applySingleTimbre(HConvSingle *hcSingle, float *in, float *out, int len);
};


#endif   // __SAMPLEDATA_H__
