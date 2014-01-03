/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2008 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2008 by Julian Storer.

 ------------------------------------------------------------------------------

 JUCE and JUCETICE can be redistributed and/or modified under the terms of
 the GNU Lesser General Public License, as published by the Free Software
 Foundation; either version 2 of the License, or (at your option) any later
 version.

 JUCE and JUCETICE are distributed in the hope that they will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with JUCE and JUCETICE; if not, visit www.gnu.org/licenses or write to
 Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 Boston, MA 02111-1307 USA

 ==============================================================================

   @author  rockhardbuns
   @tweaker Lucio Asnaghi

 ==============================================================================
*/

#ifndef __JUCETICE_VEXCWAVERENDERER_HEADER__
#define __JUCETICE_VEXCWAVERENDERER_HEADER__

#include "../StandardHeader.h"
#include "../waverom/ResourceFile.h"

struct oscSet
{
	float phase;
	float phase_offset;
	float phaseInc;
	float phaseInc_offset;
	float cut;
	float buf[4];
};

typedef struct WaveTableNames_t {
    const char* name;
    const char* data;
} WaveTableNames;

using namespace std;


class waveRenderer
{
public:

	waveRenderer()
	{
		cycle = 256; //base pitch 86 Hz
		daTable = NULL;
		sWave = T("sine");
		loadWave = true;
	}

	~waveRenderer()
	{
		M.setSize(0);
		daTable = NULL;
	}

	void setWave(const String& waveName)
	{
		sWave = waveName;
		loadWave = true;
	}

	void actuallySetWave()
	{	
        if (sWave == T("asym_saw")) {
            daTable = (uint16*) Wavetables::asym_saw;
            TableSize = Wavetables::asym_saw_size / 2;
        } else if (sWave == T("bass_tone")) {
            daTable = (uint16*) Wavetables::bass_tone;
            TableSize = Wavetables::bass_tone_size / 2;
        } else if (sWave == T("buzz_1")) {
            daTable = (uint16*) Wavetables::buzz_1;
            TableSize = Wavetables::buzz_1_size / 2;
        } else if (sWave == T("buzz_2")) {
            daTable = (uint16*) Wavetables::buzz_2;
            TableSize = Wavetables::buzz_2_size / 2;
        } else if (sWave == T("dark_strings")) {
            daTable = (uint16*) Wavetables::dark_strings;
            TableSize = Wavetables::dark_strings_size / 2;
        } else if (sWave == T("deep_ring_1")) {
            daTable = (uint16*) Wavetables::deep_ring_1;
            TableSize = Wavetables::deep_ring_1_size / 2;
        } else if (sWave == T("deep_ring_2")) {
            daTable = (uint16*) Wavetables::deep_ring_2;
            TableSize = Wavetables::deep_ring_2_size / 2;
        } else if (sWave == T("epiano_tone")) {
            daTable = (uint16*) Wavetables::epiano_tone;
            TableSize = Wavetables::epiano_tone_size / 2;
        } else if (sWave == T("ghost_1")) {
            daTable = (uint16*) Wavetables::ghost_1;
            TableSize = Wavetables::ghost_1_size / 2;
        } else if (sWave == T("ghost_2")) {
            daTable = (uint16*) Wavetables::ghost_2;
            TableSize = Wavetables::ghost_2_size / 2;
        } else if (sWave == T("ghost_3")) {
            daTable = (uint16*) Wavetables::ghost_3;
            TableSize = Wavetables::ghost_3_size / 2;
        } else if (sWave == T("ghost_4")) {
            daTable = (uint16*) Wavetables::ghost_4;
            TableSize = Wavetables::ghost_4_size / 2;
        } else if (sWave == T("grind_1")) {
            daTable = (uint16*) Wavetables::grind_1;
            TableSize = Wavetables::grind_1_size / 2;
        } else if (sWave == T("grind_2")) {
            daTable = (uint16*) Wavetables::grind_2;
            TableSize = Wavetables::grind_2_size / 2;
        } else if (sWave == T("more_strings")) {
            daTable = (uint16*) Wavetables::more_strings;
            TableSize = Wavetables::more_strings_size / 2;
        } else if (sWave == T("multi_pulse")) {
            daTable = (uint16*) Wavetables::multi_pulse;
            TableSize = Wavetables::multi_pulse_size / 2;
        } else if (sWave == T("no_name")) {
            daTable = (uint16*) Wavetables::no_name;
            TableSize = Wavetables::no_name_size / 2;
        } else if (sWave == T("one_string")) {
            daTable = (uint16*) Wavetables::one_string;
            TableSize = Wavetables::one_string_size / 2;
        } else if (sWave == T("organ_1")) {
            daTable = (uint16*) Wavetables::organ_1;
            TableSize = Wavetables::organ_1_size / 2;
        } else if (sWave == T("organ_2")) {
            daTable = (uint16*) Wavetables::organ_2;
            TableSize = Wavetables::organ_2_size / 2;
        } else if (sWave == T("phasing_sqr")) {
            daTable = (uint16*) Wavetables::phasing_sqr;
            TableSize = Wavetables::phasing_sqr_size / 2;
        } else if (sWave == T("pulse")) {
            daTable = (uint16*) Wavetables::pulse;
            TableSize = Wavetables::pulse_size / 2;
        } else if (sWave == T("saw")) {
            daTable = (uint16*) Wavetables::saw;
            TableSize = Wavetables::saw_size / 2;
        } else if (sWave == T("sharp_1")) {
            daTable = (uint16*) Wavetables::sharp_1;
            TableSize = Wavetables::sharp_1_size / 2;
        } else if (sWave == T("sharp_2")) {
            daTable = (uint16*) Wavetables::sharp_2;
            TableSize = Wavetables::sharp_2_size / 2;
        } else if (sWave == T("sine")) {
            daTable = (uint16*) Wavetables::sine;
            TableSize = Wavetables::sine_size / 2;
        } else if (sWave == T("soft_1")) {
            daTable = (uint16*) Wavetables::soft_1;
            TableSize = Wavetables::soft_1_size / 2;
        } else if (sWave == T("soft_2")) {
            daTable = (uint16*) Wavetables::soft_2;
            TableSize = Wavetables::soft_2_size / 2;
        } else if (sWave == T("soft_3")) {
            daTable = (uint16*) Wavetables::soft_3;
            TableSize = Wavetables::soft_3_size / 2;
        } else if (sWave == T("soft_4")) {
            daTable = (uint16*) Wavetables::soft_4;
            TableSize = Wavetables::soft_4_size / 2;
        } else if (sWave == T("square")) {
            daTable = (uint16*) Wavetables::square;
            TableSize = Wavetables::square_size / 2;
        } else if (sWave == T("strings_1")) {
            daTable = (uint16*) Wavetables::strings_1;
            TableSize = Wavetables::strings_1_size / 2;
        } else if (sWave == T("strings_2")) {
            daTable = (uint16*) Wavetables::strings_2;
            TableSize = Wavetables::strings_2_size / 2;
        } else if (sWave == T("string_fuzz")) {
            daTable = (uint16*) Wavetables::string_fuzz;
            TableSize = Wavetables::string_fuzz_size / 2;
        } else if (sWave == T("syn_choir_1")) {
            daTable = (uint16*) Wavetables::syn_choir_1;
            TableSize = Wavetables::syn_choir_1_size / 2;
        } else if (sWave == T("syn_choir_2")) {
            daTable = (uint16*) Wavetables::syn_choir_2;
            TableSize = Wavetables::syn_choir_2_size / 2;
        } else if (sWave == T("syn_choir_3")) {
            daTable = (uint16*) Wavetables::syn_choir_3;
            TableSize = Wavetables::syn_choir_3_size / 2;
        } else if (sWave == T("thin_1")) {
            daTable = (uint16*) Wavetables::thin_1;
            TableSize = Wavetables::thin_1_size / 2;
        } else if (sWave == T("thin_2")) {
            daTable = (uint16*) Wavetables::thin_2;
            TableSize = Wavetables::thin_2_size / 2;
        } else if (sWave == T("two_strings")) {
            daTable = (uint16*) Wavetables::two_strings;
            TableSize = Wavetables::two_strings_size / 2;
        } else if (sWave == T("voice_1")) {
            daTable = (uint16*) Wavetables::voice_1;
            TableSize = Wavetables::voice_1_size / 2;
        } else if (sWave == T("voice_2")) {
            daTable = (uint16*) Wavetables::voice_2;
            TableSize = Wavetables::voice_2_size / 2;
        }

		loadWave = false;

#if 0
// TODO - this fails on linux (host directory not plugin one)
//		String waveName = (File::getSpecialLocation(File::currentExecutableFile)).getParentDirectory().getFullPathName();

		File location = (File::getSpecialLocation(File::userHomeDirectory)).getChildFile(".vex");
		if (! location.exists ())
		    location.createDirectory ();

		String waveName;
		waveName << location.getFullPathName()
		         << "/"
		         << sWave
		         << ".raw";

		DBG( waveName );

		File f(waveName);
		if (f.existsAsFile ())
		{
		    TableSize = int(f.getSize() / 2);
		    if (TableSize > 0)
		    {
			    M.setSize(0);
			    f.loadFileAsData(M);
			    daTable = (uint16*) M.getData();
		    }
        }
        else
        {
            TableSize = int(Wavetables::sine_size / 2);
		    if (TableSize > 0)
		    {
                M.setSize (0);
                M.append (Wavetables::sine, Wavetables::sine_size);
		        daTable = (uint16*) M.getData();
		    }
        }
		loadWave = false;
#endif		
	}

	void reset(float f, double s, oscSet* o)
	{	
		if (loadWave) actuallySetWave(); 

		s = s * 2.0;
		f = f * 2.0f * (1.0f + o->phaseInc_offset * 0.01f);
		o->cut = float(2.0 * double_Pi * 9000.0 / s);
		o->phase = o->phase_offset * TableSize * 0.5f;
		o->phaseInc = float(cycle / (s/f));
		o->buf[0] = 0.0f;
		o->buf[1] = 0.0f;
		o->buf[2] = 0.0f;
		o->buf[3] = 0.0f;
	}


	void setFrequency(float f, double s, oscSet* o)
	{
		s = s * 2.0;
		f = f * 2.0f;
		o->phaseInc = float((float)cycle / (s/f));
	}


	void fillBuffer(float* buffer, int bufferSize, oscSet* o)
	{
		for(int i = 0; i < bufferSize; i++)
		{	
			buffer[i] = 0.0f;
			{
				float tmp = 0.0f; 
				int index = roundFloatToInt(o->phase - 0.5f);
				float alpha = o->phase - (float)index;
				const float conv = 1.0f / 65535.0f;
				float sIndex =		daTable[index]						* conv - 0.5f;
				float sIndexp1 =	daTable[(index + 1) % TableSize]	* conv - 0.5f;
				tmp = sIndex + alpha * (sIndexp1 - sIndex);
				o->buf[1] = ((tmp - o->buf[1]) * o->cut) + o->buf[1];
				o->buf[2] = ((o->buf[1] - o->buf[2]) * o->cut) + o->buf[2];
				o->buf[3] = ((o->buf[2] - o->buf[3]) * o->cut) + o->buf[3];
				o->buf[0] = ((o->buf[3] - o->buf[0]) * o->cut) + o->buf[0];
				tmp = o->buf[0];
				buffer[i] += tmp;
				o->phase += o->phaseInc;
				if (o->phase > (float)TableSize)
				{
					o->phase -= (float)TableSize;
				}
				tmp = 0.0f; 
				index = roundFloatToInt(o->phase - 0.5f);
				alpha = o->phase - (float)index;
				sIndex =		daTable[index]					* conv - 0.5f;
				sIndexp1 =	daTable[(index + 1) % TableSize]	* conv - 0.5f;
				tmp = sIndex + alpha * (sIndexp1 - sIndex);
				o->buf[1] = ((tmp - o->buf[1]) * o->cut) + o->buf[1];
				o->buf[2] = ((o->buf[1] - o->buf[2]) * o->cut) + o->buf[2];
				o->buf[3] = ((o->buf[2] - o->buf[3]) * o->cut) + o->buf[3];
				o->buf[0] = ((o->buf[3] - o->buf[0]) * o->cut) + o->buf[0];
				tmp = o->buf[0];
				buffer[i] += tmp;
				o->phase += o->phaseInc;
				if (o->phase > (float)TableSize)
				{
					o->phase -= (float)TableSize;
				}
			}
		}
	}

    static String getWaveTableName (const int index);
    static int getWaveTableSize ();

private:

    static WaveTableNames waveTableNames[42];

	int cycle, TableSize;
	uint16* daTable;
	MemoryBlock M;
	String sWave;
	bool loadWave;
};

#endif

