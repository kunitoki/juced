/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2009 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2007 by Julian Storer.

 ------------------------------------------------------------------------------

 JUCE and JUCETICE can be redistributed and/or modified under the terms of
 the GNU General Public License, as published by the Free Software Foundation;
 either version 2 of the License, or (at your option) any later version.

 JUCE and JUCETICE are distributed in the hope that they will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with JUCE and JUCETICE; if not, visit www.gnu.org/licenses or write to
 Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 Boston, MA 02111-1307 USA

 ==============================================================================
*/

#ifndef __JUCETICE_MADAUDIOFORMAT_HEADER__
#define __JUCETICE_MADAUDIOFORMAT_HEADER__

#include "../../../audio/audio_file_formats/juce_AudioFormat.h"

//==============================================================================
/**
    Reads and Writes MP3 format audio files.

    @see AudioFormat
*/
class MADAudioFormat : public AudioFormat
{
public:

	MADAudioFormat();
    ~MADAudioFormat();

	bool canHandleFile(const File& fileToTest);

    const Array<int> getPossibleSampleRates();
    const Array<int> getPossibleBitDepths();

    bool canDoStereo();
    bool canDoMono();
    bool isCompressed();

	void start();
	void stop();

    AudioFormatReader* createReaderFor(InputStream* sourceStream,
                                       const bool deleteStreamIfOpeningFails);


    AudioFormatWriter* createWriterFor (OutputStream* streamToWriteTo,
                                        double sampleRateToUse,
										unsigned int numberOfChannels,
										int bitsPerSample,
										const StringPairArray& metadataValues,
										int qualityOptionIndex);
};
#endif

