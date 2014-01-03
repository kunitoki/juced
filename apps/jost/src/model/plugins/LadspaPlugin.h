/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2007 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2007 by Julian Storer.

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
*/

#ifndef __JUCETICE_JOSTLADSPAPLUGIN_HEADER__
#define __JUCETICE_JOSTLADSPAPLUGIN_HEADER__

#include "../BasePlugin.h"


#ifdef JOST_USE_LADSPA

#include <ladspa.h>


//==============================================================================
class LadspaPlugin : public BasePlugin
{
public:

    //==============================================================================
    LadspaPlugin ();
    ~LadspaPlugin ();

    //==============================================================================
    int getType () const                               { return JOST_PLUGINTYPE_LADSPA; }

    //==============================================================================
    bool loadPluginFromFile (const File& filePath);
    File getFile () const                              { return pluginFile; }

    //==============================================================================
    const String getName () const;
    int getID () const;
    int getNumInputs () const;
    int getNumOutputs () const;
    int getNumMidiInputs () const;
    int getNumMidiOutputs () const;
    void* getLowLevelHandle ();

    //==============================================================================
    bool wantsEditor () const;

    //==============================================================================
    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();

    //==============================================================================
    void setParameterReal (int paramNumber, float value);
    float getParameterReal (int paramNumber);
    const String getParameterTextReal (int partNumber, float value);

    //==============================================================================
    int getNumPrograms ();
    void setCurrentProgram (int programNumber);
    int getCurrentProgram ();
    const String getProgramName (int programNumber);
    const String getCurrentProgramName ();

private:

    //==============================================================================
    File pluginFile;

    void* ptrLibrary;
    const LADSPA_Descriptor* ptrPlug;
    LADSPA_Handle plugin;

    Array<int> ins, outs, pars;

    float* params;
    float* normalized;

    float samplingRate;
};

#endif

#endif // __JUCETICE_JOSTLADSPAPLUGIN_HEADER__
