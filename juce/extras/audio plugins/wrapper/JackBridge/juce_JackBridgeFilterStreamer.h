/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2008 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2008 by Julian Storer.

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

    @author  drumfix
    
    @tweaker kRAkEn/gORe

 ==============================================================================
*/

#ifndef __JUCE_JACKBRIDGEFILTERSTREAMER_H__
#define __JUCE_JACKBRIDGEFILTERSTREAMER_H__

#include "../juce_PluginHeaders.h"

#include <sched.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>

#include "common.h"

//==============================================================================
/**
    A class that wraps an AudioFilterBase as an JackBridgeConnectionKit client,
    using a shared memory mapped file for streaming audio.

    To use it, just create an instance of this for your filter, and that's it.

    @code

        DemoFilter* myFilter = new DemoFilter ();
        JackBridgeFilterStreamer* myStreamer = new JackBridgeFilterStreamer ();

        myStreamer->setFilter (myFilter, true);

    @endcode
*/
class JackBridgeFilterStreamer  : public Timer,
                                  public Thread,
                                  public MidiInputCallback,
                                  public AudioPlayHead,
                                  public ExternalTransport
{
public:
    //==============================================================================
    JackBridgeFilterStreamer ();
    ~JackBridgeFilterStreamer();

    //==============================================================================
    /**
        Sets on the fly a new filter to be runned by this streamer

        It is useful if you need to change the filter being played at runtime, and
        this will take care of deactivating the old JACK client and create a new
        one based on the filter you passed to it.

        @param filterToUse          the new filter to stream
        @param checkForServer       starts immediately checking if a jack
                                    server is present
    */
    void setFilter (AudioProcessor* filterToUse,
                    const bool checkForServer = true,
                    const bool connectToPhysicalInputs = false,
                    const bool connectToPhysicalOutputs = false);

    /**
        Calling this after you have created a filter streamer will start checking
        for some JACK server daemon in background. If a server is found and running,
        then your client filter will be activated.

        @see activateClient
    */
    void startCheckForServer ();

    //==============================================================================
    /**
        Will suspend the jack thread temporarily, just in case you need to stop
        the jack audio thread from outside the plugin
    */
    void suspendProcessing (const bool suspend);

    //==============================================================================
    /**
        Try to make this client grab main JACK transport

        If you want to control transport from your filter, you should try to
        grab it by using this function.

        @param conditionalGrab      if true, you can grab the transport ONLY if
                                    no other jack applications have grabbed already.
                                    if false, you are forcing grab of the transport

        @return true if your client grabbed transport correctly
    */
    bool grabTransport (const bool conditionalGrab = true);

    /**
        Release this client grabbing the main JACK transport

        This works only if you already grabbed the transport over all the other
        JACK clients.
    */
    void releaseTransport ();

    /**
        Play the transport

        This will call the server to notify all the other attached clients that
        are listening for transport states. This only works if you already taken
        the transport.
    */
    void playTransport ();

    /**
        Stop main transport

        This will call the server to notify all the other attached clients that
        are listening for transport states. This only works if you already taken
        the transport.
    */
    void stopTransport ();

    /**
        Seek the transport to a specified frame number

        This will call the server to notify all the other attached clients that
        are listening for transport states. This only works if you already taken
        the transport.
    */
    void seekTransportToFrame (const int frameToSeekAt);

    /**
        Set JACK main tempo in beats per seconds
    */
    void setTempo (const double bpmToSet);

    /**
        Set JACK sync timeout in seconds
    */
    void setSyncTimeout (const double secondsTimeout);

    //==============================================================================
    /**
        Create the editor using createEditorInternal of the AudioFilterBase.

        This is needed cause we need to simulate to be a HOST application that
        is trying to create the window for the Editor. And since a lot of
        properties and useful functions are private in the AudioFilterBase, then
        we need to wrap the creation of the editor with this function.

        @see AudioProcessor::createEditorIfNeeded()
    */
    AudioProcessorEditor* createFilterEditorIfNeeded ();

    //==============================================================================
    /** @internal */
    bool activateClient ();
    /** @internal */
    void closeClient ();
    /** @internal */
    void audioPluginAboutToStart (AudioIODevice* device)        { }
    /** @internal */
    void audioPluginStarted (double newSampleRate, int newBlockSize);
    /** @internal */
    void audioPluginStopped();
    /** @internal */
    void audioPluginIOCallback (int numSamples);
    /** @internal */
    void sampleRateCallback (int newSampleRate);
    /** @internal */
    void blockSizeCallback (int newBlockSize);
    /** @internal */
    void handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message);
    /** @internal */
    bool getCurrentPosition (AudioPlayHead::CurrentPositionInfo& info);
    /** @internal */
    void timerCallback ();
    /** @internal */
    void run ();

    //==============================================================================
    juce_UseDebuggingNewOperator

    //==============================================================================
    // TODO - these should be part of the ExternalTransport
    volatile bool timeHasChanged;
    double beatsPerMinute;
    double ticksPerBeat;
    float beatsPerBar;     // numerator
    float beatType;        // denominator

private:

    //==============================================================================
    AudioProcessor* filter;
    AudioProcessorEditor* editor;
    bool isPlaying;
    double sampleRate;
    int blockSize;
    MidiMessageCollector midiCollector;

    float* outChans [128];
    float* inChans [128];

    MidiInput* midiInput;
    MidiOutput* midiOutput;

    sem_t *semaphore1;
    sem_t *semaphore2;
    char *jackbridge;
    InfoBlock *infoblock;
    unsigned int inputs;
    unsigned int outputs;
    float *inputblock;
    float *outputblock;
    
    bool holdTransport;
    AudioSampleBuffer inputBuffers;
    AudioSampleBuffer outputBuffers;
    AudioSampleBuffer emptyBuffer;
};

#endif
