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

#include "../../../core/juce_StandardHeader.h"

namespace mpclibNamespace
{
#if JUCETICE_INCLUDE_MPCLIB_CODE
  extern "C" {
    #include "../../dependancies/mpc/common/crc32.c"
    #include "../../dependancies/mpc/libmpcdec/huffman.c"
    #include "../../dependancies/mpc/libmpcdec/requant.c"
    #include "../../dependancies/mpc/libmpcdec/mpc_bits_reader.c"
    #include "../../dependancies/mpc/libmpcdec/mpc_decoder.c"
    #include "../../dependancies/mpc/libmpcdec/mpc_demux.c"
    #include "../../dependancies/mpc/libmpcdec/mpc_reader.c"
    #include "../../dependancies/mpc/libmpcdec/streaminfo.c"
    #include "../../dependancies/mpc/libmpcdec/synth_filter.c"
  }
#else
  #include <mpcdec/mpcdec.h>
#endif
}

BEGIN_JUCE_NAMESPACE

#include "jucetice_MPCAudioFormat.h"

using namespace mpclibNamespace;


//==============================================================================
class MPCAudioFormatReader : public AudioFormatReader
{
public:

	MPCAudioFormatReader(InputStream* const sourceStream) :
		AudioFormatReader(sourceStream, T("MPC (Musepack) Audio Format")),
		_lastSample(0),
		_bufferPointer ((MPC_SAMPLE_FORMAT*)&_buffer),
		_samplesLeftInBuffer(0)
	{
		usesFloatingPointData = true;
		sampleRate = 0;

		_reader.read = mpcRead;
		_reader.seek = mpcSeek;
		_reader.tell = mpcTell;
		_reader.get_size = mpcGetSize;
		_reader.canseek = mpcCanseek;
		_reader.data = input;

	    _demux = mpc_demux_init(&_reader);

		if(_demux)
		{
			mpc_streaminfo si;

			mpc_demux_get_info(_demux,  &si);

			sampleRate = si.sample_freq;
			numChannels = si.channels;
			lengthInSamples = mpc_streaminfo_get_length_samples(&si);
			bitsPerSample = 32;

			_frame.buffer = _buffer;
		}
	}

	~MPCAudioFormatReader()
	{
		if(_demux)
			mpc_demux_exit(_demux);
	}

    bool readSamples (int** destSamples, int numDestChannels, int startOffsetInDestBuffer,
                      int64 startSampleInFile, int numSamples)
	{
		if(startSampleInFile >= lengthInSamples)
			return true;

		if(startSampleInFile + numSamples > lengthInSamples)
			numSamples = lengthInSamples - startSampleInFile;

		if(startSampleInFile != _lastSample)
		{
			if(mpc_demux_seek_sample(_demux, (mpc_uint64_t) startSampleInFile) != MPC_STATUS_OK)
				return true;

			_lastSample = startSampleInFile;
			_samplesLeftInBuffer = 0;
		}

		float *left_ = ((float*)destSamples[0]);
		float *right_ = ((float*)destSamples[1]);
		int numToRead_ = 0;

		while (numSamples > 0)
		{
			if(_samplesLeftInBuffer <= 0)
			{
				if(mpc_demux_decode(_demux, &_frame) != MPC_STATUS_OK)
					return true;

				_samplesLeftInBuffer = _frame.samples;
				_bufferPointer = (MPC_SAMPLE_FORMAT*)&_buffer;
			}

			numToRead_ = (_samplesLeftInBuffer <= numSamples) ? _samplesLeftInBuffer : numSamples;

			numSamples -= numToRead_;
			_samplesLeftInBuffer -= numToRead_;
			_lastSample += numToRead_;

			while(numToRead_--)
			{
				if(left_)
					(*left_++) = *_bufferPointer;

				_bufferPointer++;

				if(right_)
					(*right_++) = *_bufferPointer;

				_bufferPointer++;
			}
		}

		return true;
	}

private:

    static mpc_int32_t mpcRead(mpc_reader *p_reader, void *ptr, mpc_int32_t size)
    {
    	return (mpc_int32_t)((InputStream*) p_reader->data)->read(ptr, int(size));
    }

    static mpc_bool_t mpcSeek(mpc_reader *p_reader, mpc_int32_t offset)
    {
    	((InputStream*) p_reader->data)->setPosition(offset);

    	return MPC_TRUE;
    }

    static mpc_int32_t mpcTell(mpc_reader *p_reader)
    {
    	return (mpc_int32_t)((InputStream*) p_reader->data)->getPosition();
    }

    static mpc_int32_t mpcGetSize(mpc_reader *p_reader)
    {
    	return (mpc_int32_t)((InputStream*) p_reader->data)->getTotalLength();
    }

    static mpc_bool_t mpcCanseek(mpc_reader *p_reader)
    {
    	return MPC_TRUE;
    }

	mpc_reader _reader;
	mpc_demux* _demux;
	mpc_frame_info _frame;
	int64 _lastSample;

    MPC_SAMPLE_FORMAT _buffer[MPC_DECODER_BUFFER_LENGTH];
    MPC_SAMPLE_FORMAT *_bufferPointer;
	int _samplesLeftInBuffer;
};

//==============================================================================
static const tchar* const mpc_extensions[] = { T(".mpc"), 0 };

MPCAudioFormat::MPCAudioFormat()
    : AudioFormat(T("MPC (Musepack) Audio Format"), (const tchar**) mpc_extensions)
{
}

MPCAudioFormat::~MPCAudioFormat()
{
}

bool MPCAudioFormat::canHandleFile(const File& fileToTest)
{
	return fileToTest.hasFileExtension(T("mpc"));
}

const Array<int> MPCAudioFormat::getPossibleSampleRates()
{
    const int rates[] = { 44100, 48000, 0 };
    return Array <int>(rates);
}

const Array<int> MPCAudioFormat::getPossibleBitDepths()
{
    const int depths[] = { 16, 24, 32, 0 };
    return Array<int> (depths);
}

bool MPCAudioFormat::canDoStereo()
{
	return true;
}

bool MPCAudioFormat::canDoMono()
{
	return true;
}

bool MPCAudioFormat::isCompressed()
{
	return true;
}

//==============================================================================
AudioFormatReader* MPCAudioFormat::createReaderFor(InputStream* sourceStream, const bool deleteStreamIfOpeningFails)
{
	AudioFormatReader* r = new MPCAudioFormatReader(sourceStream);

    if (r->sampleRate == 0)
        if (!deleteStreamIfOpeningFails)
			delete r;

    return r;
}

AudioFormatWriter* MPCAudioFormat::createWriterFor(OutputStream* streamToWriteTo, double sampleRateToUse, unsigned int numberOfChannels, int bitsPerSample, const StringPairArray& metadataValues, int qualityOptionIndex)
{
	return 0;
}

END_JUCE_NAMESPACE

