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


#include "windows_quirks.h"
#include "SampleData.h"
#include "gui/TabMain.h"
#include <math.h>
#include <string.h>
#include <stdio.h>

extern "C" {
#include "libHybridConv/libHybridConv.h"
}


SampleData::SampleData ()
    : samplesLL(0),
      samplesLR(0),
      samplesRL(0),
      samplesRR(0),
      bufferLen(0),
      dataLen(0),
      fs(0)
{
    available[0] = false;
    available[1] = false;
    available[2] = false;
    available[3] = false;
}

SampleData::~SampleData()
{
}


////////////////////////////////////////////////////////////////
//
//    public methods
//

void SampleData::applyLoadFiles(String dir,
                                String fileLL,
                                String fileLR,
                                String fileRL,
                                String fileRR)
{
    String filename;

    dataLen = 1;

    // left -> left
    if (fileLL != String::empty)
    {
        if (File::isAbsolutePath(fileLL))
            loadSingleFile(fileLL, 0);
        else
            loadSingleFile(dir + fileLL, 0);
    }
    else
        available[0] = false;

    // left -> right
    if (fileLR != String::empty)
    {
        if (File::isAbsolutePath(fileLR))
            loadSingleFile(fileLR, 1);
        else
            loadSingleFile(dir + fileLR, 1);
    }
    else
        available[1] = false;

    // right -> left
    if (fileRL != String::empty)
    {
        if (File::isAbsolutePath(fileRL))
            loadSingleFile(fileRL, 2);
        else
            loadSingleFile(dir + fileRL, 2);
    }
    else
        available[2] = false;

    // right -> right
    if (fileRR != String::empty)
    {
        if (File::isAbsolutePath(fileRR))
            loadSingleFile(fileRR, 3);
        else
            loadSingleFile(dir + fileRR, 3);
    }
    else
        available[3] = false;
}


void SampleData::applyLoadFiles(String dir, ParamImpulseResponses *param)
{
    applyLoadFiles(dir,
                   param->ll,
                   param->lr,
                   param->rl,
                   param->rr);
}


int SampleData::loadSingleFile(String filename, int num)
{
    File audioFile(filename);
    if (audioFile.existsAsFile() == false)
    {
        available[num] = false;
        String message = JUCE_T("Error: The audio file \"") +
                         filename +
                         JUCE_T("\" does not exist!");
        AlertWindow::showMessageBox(AlertWindow::WarningIcon,
                                    JUCE_T("Error"), message);
        return -1;
    }

    AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    AudioFormatReader *reader = formatManager.createReaderFor(audioFile);
    if (reader == 0)
    {
        available[num] = false;
        String message = JUCE_T("Error: \"") +
                         filename +
                         JUCE_T("\" is not a valid audio file!");
        AlertWindow::showMessageBox(AlertWindow::WarningIcon,
                                    JUCE_T("Error"), message);
        return -1;
    }

    fs = reader->sampleRate;
    int *readBuffer = new int[reader->lengthInSamples];
    if (reader->read(&readBuffer, 1, 0, reader->lengthInSamples, false) == false)
    {
        available[num] = false;
        delete[] readBuffer;
        delete reader;
        String message = JUCE_T("Error: Reading audio data from file \"") +
                         filename +
                         JUCE_T("\" failed!");
        AlertWindow::showMessageBox(AlertWindow::WarningIcon,
                                    JUCE_T("Error"), message);
        return -1;
    }

    checkLength(reader->lengthInSamples);
    float *sampleData;
    switch (num)
    {
    case 0:
        sampleData = samplesLL;
        break;
    case 1:
        sampleData = samplesLR;
        break;
    case 2:
        sampleData = samplesRL;
        break;
    case 3:
        sampleData = samplesRR;
        break;
    }

    dataLen = reader->lengthInSamples;
    if (reader->usesFloatingPointData == true)
    {
        memcpy(sampleData, readBuffer, dataLen * sizeof(float));
    }
    else
    {
        float norm = 1.0 / 2147483648.0;
        for (int n = 0; n < dataLen; n++)
            sampleData[n] = norm * readBuffer[n];
    }

    if (num == 0 || num == 3)
        sampleData[0] = 1.0;
    else
        sampleData[0] = 0.0;

    available[num] = true;
    delete[] readBuffer;
    delete reader;
    return 0;
}


void SampleData::applyGainDelay(SampleData *source, ParamGainDelay *param)
{
    // check availability
    for (int n = 0; n < 4; n++)
    {
        if (source->getData(n) != 0)
            available[n] = true;
        else
            available[n] = false;
    }

    fs = source->getSampleRate();

    int s       = 0;
    int d       = 0;
    int s_begin = (int)roundf(fs * param->initialGap * 0.001);
    int s_end   = (int)roundf(fs * param->length);
    int pre     = (int)roundf(fs * param->preDelay * 0.001);
    if (s_begin == 0)
        s_begin = 1;    // omit direct sound
    if (s_begin > source->getDataLen())
        s_begin = source->getDataLen();
    if (s_end > source->getDataLen())
        s_end = source->getDataLen();
    if (s_end == 0)
        s_end = s_begin + 1;
    if (s_end < 0)
        s_end = source->getDataLen();
    checkLength(source->getDataLen() + pre);
    if (pre > 0)
    {
        for (d = 0; d < pre; d++)
        {
            samplesLL[d] = 0.0;
            samplesLR[d] = 0.0;
            samplesRL[d] = 0.0;
            samplesRR[d] = 0.0;
        }
    }
    else
        s -= pre;
    while (s < s_begin)
    {
        samplesLL[d] = 0.0;
        samplesLR[d] = 0.0;
        samplesRL[d] = 0.0;
        samplesRR[d] = 0.0;
        s++;
        d++;
    }

    float *sLL = source->getData(0);
    float *sLR = source->getData(1);
    float *sRL = source->getData(2);
    float *sRR = source->getData(3);

    float gain = (float)pow(10.0, (param->wetGain + param->masterGain) / 20.0);
    while (s < s_end)
    {
        if (available[0])
            samplesLL[d] = gain * sLL[s];
        else
            samplesLL[d] = 0.0;

        if (available[1])
            samplesLR[d] = gain * sLR[s];
        else
            samplesLR[d] = 0.0;

        if (available[2])
            samplesRL[d] = gain * sRL[s];
        else
            samplesRL[d] = 0.0;

        if (available[3])
            samplesRR[d] = gain * sRR[s];
        else
            samplesRR[d] = 0.0;

        s++;
        d++;
    }
    dataLen = d;

    gain = (float)pow(10.0, (param->dryGain + param->masterGain) / 20.0);
    samplesLL[0] = gain;
    samplesLR[0] = 0.0;
    samplesRL[0] = 0.0;
    samplesRR[0] = gain;
}


void SampleData::applyEnvelope(SampleData *source, ParamEnvelope *param)
{
    checkLength(source->getDataLen());
    dataLen = source->getDataLen();
    fs = source->getSampleRate();

    for (int n = 0; n < 4; n++)
    {
        if (source->getData(n) != 0)
            available[n] = true;
        else
            available[n] = false;
    }

    float *sLL = source->getData(0);
    float *sLR = source->getData(1);
    float *sRL = source->getData(2);
    float *sRR = source->getData(3);

    if (available[0])
        samplesLL[0] = sLL[0];
    else
        samplesLL[0] = 0.0;
    if (available[1])
        samplesLR[0] = sLR[0];
    else
        samplesLR[0] = 0.0;
    if (available[2])
        samplesRL[0] = sRL[0];
    else
        samplesRL[0] = 0.0;
    if (available[3])
        samplesRR[0] = sRR[0];
    else
        samplesRR[0] = 0.0;

    int n20  = (int)roundf(0.020 * fs);
    int n120 = (int)roundf(0.120 * fs);

    float c0 = param->db0ms;
    float c1 = (param->db20ms - param->db0ms) / float(n20);
    for (int d = 1; d < n20 && d < dataLen; d++)
    {
        float db = d * c1 + c0;
        float gain = (float)pow(10.0, db / 20.0);
        if (available[0])
            samplesLL[d] = gain * sLL[d];
        else
            samplesLL[d] = 0.0;

        if (available[1])
            samplesLR[d] = gain * sLR[d];
        else
            samplesLR[d] = 0.0;

        if (available[2])
            samplesRL[d] = gain * sRL[d];
        else
            samplesRL[d] = 0.0;

        if (available[3])
            samplesRR[d] = gain * sRR[d];
        else
            samplesRR[d] = 0.0;
    }

    c0 = param->db20ms;
    c1 = (param->db120ms - param->db20ms) / float(n120 - n20);
    for (int d = n20; d < n120 && d < dataLen; d++)
    {
        float db = (d - n20) * c1 + c0;
        float gain = (float)pow(10.0, db / 20.0);
        if (available[0])
            samplesLL[d] = gain * sLL[d];
        else
            samplesLL[d] = 0.0;

        if (available[1])
            samplesLR[d] = gain * sLR[d];
        else
            samplesLR[d] = 0.0;

        if (available[2])
            samplesRL[d] = gain * sRL[d];
        else
            samplesRL[d] = 0.0;

        if (available[3])
            samplesRR[d] = gain * sRR[d];
        else
            samplesRR[d] = 0.0;
    }

    c0 = param->db120ms;
    c1 = (param->dbENDms - param->db120ms) / float(dataLen - n120);
    for (int d = n120; d < dataLen; d++)
    {
        float db = (d - n120) * c1 + c0;
        float gain = (float)pow(10.0, db / 20.0);
        if (available[0])
            samplesLL[d] = gain * sLL[d];
        else
            samplesLL[d] = 0.0;

        if (available[1])
            samplesLR[d] = gain * sLR[d];
        else
            samplesLR[d] = 0.0;

        if (available[2])
            samplesRL[d] = gain * sRL[d];
        else
            samplesRL[d] = 0.0;

        if (available[3])
            samplesRR[d] = gain * sRR[d];
        else
            samplesRR[d] = 0.0;
    }
}


void SampleData::applyTimbre(SampleData *source, int filterLen, float *filter)
{
    checkLength(source->getDataLen());
    dataLen = source->getDataLen();
    fs = source->getSampleRate();

    for (int n = 0; n < 4; n++)
    {
        if (source->getData(n) != 0)
            available[n] = true;
        else
            available[n] = false;
    }

    float *sLL = source->getData(0);
    float *sLR = source->getData(1);
    float *sRL = source->getData(2);
    float *sRR = source->getData(3);

    HConvSingle hcSingle;
    hcInitSingle(&hcSingle, filter, filterLen, filterLen / 2, 1);

    if (sLL != 0)
        applySingleTimbre(&hcSingle, sLL, samplesLL, dataLen);

    if (sLR != 0)
        applySingleTimbre(&hcSingle, sLR, samplesLR, dataLen);

    if (sRL != 0)
        applySingleTimbre(&hcSingle, sRL, samplesRL, dataLen);

    if (sRR != 0)
        applySingleTimbre(&hcSingle, sRR, samplesRR, dataLen);

    hcCloseSingle(&hcSingle);
}


float *SampleData::getData(int num)
{
    if (dataLen < 1 || available[num] == false)
        return 0;
    switch (num)
    {
    case 0:
        return samplesLL;
    case 1:
        return samplesLR;
    case 2:
        return samplesRL;
    case 3:
        return samplesRR;
    }
    return 0;
}


int SampleData::getDataLen(void)
{
    return dataLen;
}


int SampleData::getSampleRate(void)
{
    return fs;
}


bool SampleData::hasData(int num)
{
    return available[num];
}


////////////////////////////////////////////////////////////////
//
//    private methods
//

void SampleData::checkLength(int len)
{
    float *newBuf;

    if (len <= bufferLen)
        return;

    bufferLen = (int)roundf(1024.0 * ceil(len / 1024.0));

    newBuf = new float[bufferLen];
    if (samplesLL)
    {
        memcpy(newBuf, samplesLL, dataLen * sizeof(float));
        delete[] samplesLL;
    }
    samplesLL = newBuf;

    newBuf = new float[bufferLen];
    if (samplesLR)
    {
        memcpy(newBuf, samplesLR, dataLen * sizeof(float));
        delete[] samplesLR;
    }
    samplesLR = newBuf;

    newBuf = new float[bufferLen];
    if (samplesRL)
    {
        memcpy(newBuf, samplesRL, dataLen * sizeof(float));
        delete[] samplesRL;
    }
    samplesRL = newBuf;

    newBuf = new float[bufferLen];
    if (samplesRR)
    {
        memcpy(newBuf, samplesRR, dataLen * sizeof(float));
        delete[] samplesRR;
    }
    samplesRR = newBuf;
}


void SampleData::applySingleTimbre(HConvSingle *hcSingle,
                                   float *in, float *out, int len)
{
    int flen = hcSingle->framelength;
    int size = sizeof(float) * (flen + 1);
    for (int i = 0; i < hcSingle->num_mixbuf; i++)
    {
        memset(hcSingle->mixbuf_freq_real[i], 0, size);
        memset(hcSingle->mixbuf_freq_imag[i], 0, size);
    }
    size = sizeof(float) * flen;
    memset(hcSingle->history_time, 0, size);

    // check if input data is long enough
    if (len < 2 * flen)
    {
        int size = len * sizeof(float);
        memcpy(out, in, len);
        return;
    }

    int posIn  = 0;
    int posOut = 0;

    // first block (dropped)
    float sav = in[0];
    in[0] = 0.0;
    hcPutSingle(hcSingle, &(in[posIn]));
    hcProcessSingle(hcSingle);
    hcGetSingle(hcSingle, &(out[posOut]));
    posIn += flen;
    in[0] = sav;

    // second block (includes direct sound)
    hcPutSingle(hcSingle, &(in[posIn]));
    hcProcessSingle(hcSingle);
    hcGetSingle(hcSingle, &(out[posOut]));
    int fadeEnd = 256;
    if (fadeEnd > flen)
        fadeEnd = flen;
    for (int i = 0; i < fadeEnd; i++)
    {
        float gain = 0.5 - 0.5 * cos(M_PI * double(i) / double(fadeEnd));
        out[i] = gain * out[i] + (1.0 - gain) * in[i];
    }
    posIn  += flen;
    posOut += flen;

    // process complete blocks
    while (len - posIn >= flen)
    {
        hcPutSingle(hcSingle, &(in[posIn]));
        hcProcessSingle(hcSingle);
        hcGetSingle(hcSingle, &(out[posOut]));
        posIn  += flen;
        posOut += flen;
    }

    // process rest
    while (posOut < len)
    {
        float* tmpIn  = new float[flen];
        float* tmpOut = new float[flen];
        for (int i = 0; i < flen; i++)
        {
            if (posIn < len)
                tmpIn[i] = in[posIn];
            else
                tmpIn[i] = 0.0;
            posIn++;
        }
        hcPutSingle(hcSingle, tmpIn);
        hcProcessSingle(hcSingle);
        hcGetSingle(hcSingle, tmpOut);
        for (int i = 0; posOut < len && i < flen; i++)
        {
            out[posOut] = tmpOut[i];
            posOut++;
        }
        delete[] tmpIn;
        delete[] tmpOut;
    }
}
