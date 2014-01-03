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

#ifndef __JOST_HOSTFILTERBASE_HEADER__
#define __JOST_HOSTFILTERBASE_HEADER__

#include "Config.h"
#include "Commands.h"
#include "model/BasePlugin.h"
#include "model/Host.h"
#include "model/Transport.h"


//==============================================================================
/**
    The main host processor. It is built as plugin to let it become a vst
    plugin afterwards (and let be loaded for instance by eXT2).
*/
class HostFilterBase  : public AudioPlugin
{
public:

    //==============================================================================
    /** Constructor */
    HostFilterBase (const String& commandLine);

    /** Destructor */
    ~HostFilterBase ();

    //==============================================================================
    const String getName() const          { return JucePlugin_Name; }
    bool acceptsMidi() const              { return JucePlugin_WantsMidiInput; }
    bool producesMidi() const             { return JucePlugin_ProducesMidiOutput; }

    //==============================================================================
    /** This is called internally when we need to use the editor */
    AudioProcessorEditor* createEditor ();

    /** Handy function to return the typecast editor */
    HostFilterComponent* getEditor ();

    //==============================================================================
    /** Handy function to return the real host */
    Host* getHost ()                                        { return host; }
    
    /** Handy function to return the real transport */
    Transport* getTransport ()                              { return transport; }

    //==============================================================================
    /** This is called when the host is first activated, and before the callback */
    void prepareToPlay (double sampleRate, int samplesPerBlock);

    /** Called when the host is released: the audio setup is reset or changed */
    void releaseResources();

    /** This is the audio/midi callback.

        You will process audio and midi, calling every loaded effect.
    */
    void processBlock (AudioSampleBuffer& buffer,
                       MidiBuffer& midiMessages);

    //==============================================================================
    /** This is called when we need to save our internal host session state */
    void getStateInformation (MemoryBlock& destData);

    /** Called to restore host session state */
    void setStateInformation (const void* data, int sizeInBytes);

    //==============================================================================
    /** This is used to set an external transport, if any */
    void setExternalTransport (ExternalTransport* externalTransport);

    //==============================================================================
    juce_UseDebuggingNewOperator

    //==============================================================================
    static int numInstances;          /** Running instances (plugin only) */

protected:

    //==============================================================================
    friend class HostFilterComponent;

    // a dummy parameter
    // TODO - make parameters array to follow plugin parameters
    AudioParameter dummyParameter;

    // our real plugin host
    Host* host;
    
    // the real transport
    Transport* transport;

#if JUCE_LASH
    // if we choose to use lash we will have this set
    LashManager* lashManager;
#endif

};


#endif
