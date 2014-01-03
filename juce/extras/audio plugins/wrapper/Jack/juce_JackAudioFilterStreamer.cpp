/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-6 by Raw Material Software ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the
   GNU General Public License, as published by the Free Software Foundation;
   either version 2 of the License, or (at your option) any later version.

   JUCE is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with JUCE; if not, visit www.gnu.org/licenses or write to the
   Free Software Foundation, Inc., 59 Temple Place, Suite 330,
   Boston, MA 02111-1307 USA

  ------------------------------------------------------------------------------

   If you'd like to release a closed-source product which uses JUCE, commercial
   licenses are also available: visit www.rawmaterialsoftware.com/juce for
   more information.

  ==============================================================================
*/

#include "juce_JackAudioFilterStreamer.h"
#include "../juce_IncludeCharacteristics.h"

//==============================================================================
static void juce_internalJackThreadInitCallback (void *arg);
static void juce_internalJackOnShutdownCallback (void *arg);
static int juce_internalJackProcessCallback (jack_nframes_t nframes, void* arg);
//static int juce_internalJackXRunCallback (void *arg);
//static int juce_internalJackBufferSizeCallback (jack_nframes_t nframes, void *arg);
//static int juce_internalJackSampleRateCallback (jack_nframes_t nframes, void *arg);
// static void juce_internalJackPortRegistrationCallback (jack_port_id_t port, int, void *arg);
// static void juce_internalJackFreewheelCallback (int starting, void *arg);
// static int juce_internalJackGraphOrderCallback (void *arg);
// static int juce_internalJackSyncCallback (jack_transport_state_t state, jack_position_t *pos, void *arg);
static void juce_internalJackTimebaseCallback (jack_transport_state_t state,
                                               jack_nframes_t nframes,
                                               jack_position_t *pos,
                                               int new_pos,
                                               void *arg);




//==============================================================================
JackAudioFilterStreamer::JackAudioFilterStreamer ()
    : timeHasChanged (false),
      beatsPerMinute (120.0),
      ticksPerBeat (960.0 /*PPQ*/),
      beatsPerBar (4),
      beatType (4),
      filter (0),
      editor (0),
      isPlaying (false),
      autoConnectInputs (false),
      autoConnectOutputs (false),
      sampleRate (0),
      blockSize (0),
      midiInput (0),
      midiOutput (0),
      client (0),
      holdTransport (false),
      emptyBuffer (1, 32)
{
    DBG ("JackAudioFilterStreamer::JackAudioFilterStreamer");
}

JackAudioFilterStreamer::~JackAudioFilterStreamer()
{
    DBG ("JackAudioFilterStreamer::~JackAudioFilterStreamer");

    setFilter (0, false);
}

//==============================================================================
void JackAudioFilterStreamer::setFilter (AudioProcessor* filterToUse,
                                         const bool checkForServer,
                                         const bool connectToPhysicalInputs,
                                         const bool connectToPhysicalOutputs)
{
    DBG ("JackAudioFilterStreamer::setFilter");

    audioPluginStopped ();
    closeClient ();

    autoConnectInputs = connectToPhysicalInputs;
    autoConnectOutputs = connectToPhysicalOutputs;

    if (filter && editor != 0)
        filter->editorBeingDeleted (editor);

    filter = filterToUse;
    if (filter)
    {
        filter->setPlayConfigDetails (JucePlugin_MaxNumInputChannels,
                                      JucePlugin_MaxNumOutputChannels, 0, 0);
        filter->setPlayHead (this);

        if (checkForServer)
            startCheckForServer ();
    }
}

//==============================================================================
bool JackAudioFilterStreamer::activateClient ()
{
    jassert (filter);  // you should have already attached a filter,
                       // if not, how would this streamer works ?
    sampleRate = 0;
    blockSize = 0;

    // create the jack client
    jack_status_t status;
    client = jack_client_open (JucePlugin_Name, JackNoStartServer, &status);
    if (client == 0)
    {
		if (status & JackServerFailed) {
			DBG ("Unable to connect to JACK server");
		}
    
        return false;
    }

    DBG ("JackAudioFilterStreamer::activateClient");

    // setup callbacks
    jack_set_thread_init_callback (client, juce_internalJackThreadInitCallback, this);
    jack_on_shutdown (client, juce_internalJackOnShutdownCallback, this);
//    jack_set_buffer_size_callback (client, juce_internalJackBufferSizeCallback, this);
//    jack_set_sample_rate_callback (client, juce_internalJackSampleRateCallback, this);
//    jack_set_port_registration_callback (client, juce_internalJackPortRegistrationCallback, this);
//    jack_set_graph_order_callback (client, juce_internalJackGraphOrderCallback, this);
//    jack_set_freewheel_callback (client, juce_internalJackFreewheelCallback, this);
    jack_set_process_callback (client, juce_internalJackProcessCallback, this);
//    jack_set_xrun_callback (client, juce_internalJackXRunCallback, this);
//    jack_set_sync_callback (client, juce_internalJackSyncCallback, this);

#ifdef JUCE_DEBUG
//    jack_set_error_function (default_jack_error_callback);
#endif

    jassert (JucePlugin_MaxNumInputChannels <= 64);   // your filter have more input channels
                                                      // than the maximum allowed to be handle by this streamer !
    jassert (JucePlugin_MaxNumOutputChannels <= 64);  // your filter have more input channels
                                                      // than the maximum allowed to be handle by this streamer !

    // register input ports
    for (int i = 0; i < JucePlugin_MaxNumInputChannels; i++)
    {
        String inputName;
        inputName << "in_" << (i+1);

        jack_port_t* input =
                jack_port_register (client, (const char*) inputName, JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);

        inputPorts.add (input);
    }

    // register output ports
    for (int i = 0; i < JucePlugin_MaxNumOutputChannels; i++)
    {
        String outputName;
        outputName << "out_" << (i+1);

        jack_port_t* output =
                jack_port_register (client, (const char*) outputName, JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);

        jack_port_set_latency (output, filter->getLatencySamples ());

        outputPorts.add (output);
    }

    // autoconnect to physical inputs ports
    if (autoConnectInputs)
    {
        const char** ports = jack_get_ports (client, 0, 0,
                                             JackPortIsPhysical | JackPortIsOutput);
        if (ports && ports[0])
        {
            for (int i = 0, j = 0; i < JucePlugin_MaxNumInputChannels; ++i) {
                if (jack_connect (client, jack_port_name ((jack_port_t*) inputPorts[i]), ports[j])) {
                    printf ("Cannot connect input port %d (%s)\n", i, ports[j]);
                }
                if (! ports[++j]) j = 0;
            }
            free(ports);
        }
    }

    // autoconnect to physical outputs ports
    if (autoConnectOutputs)
    {
        const char** ports = jack_get_ports (client, 0, 0,
                                             JackPortIsPhysical | JackPortIsInput);
        if (ports && ports[0])
        {
            for (int i = 0, j = 0; i < JucePlugin_MaxNumOutputChannels; ++i) {
                if (jack_connect (client, jack_port_name ((jack_port_t*) outputPorts[i]), ports[j])) {
                    printf ("Cannot connect output port %d (%s)\n", i, ports[j]);
                }
                if (! ports[++j]) j = 0;
            }
            free(ports);
        }
    }

    // create midi devices
#if JucePlugin_WantsMidiInput
    if (midiInput)
        midiInput->stop ();
    deleteAndZero (midiInput);
    midiInput = MidiInput::createNewDevice (JucePlugin_Name, this);
    if (midiInput)
        midiInput->start ();
#endif

#if JucePlugin_ProducesMidiOutput
    deleteAndZero (midiOutput);
    midiOutput = MidiOutput::createNewDevice (JucePlugin_Name);
#endif

    // reset midi collector before we start
    midiCollector.reset (jack_get_sample_rate (client));

    // update samplerate and block size before we just activate the client
    audioPluginStarted ((double) jack_get_sample_rate (client),
                        (int)    jack_get_buffer_size (client));

    // activate jack client
    jack_activate (client);

    return true;
}

void JackAudioFilterStreamer::deactivateClient ()
{
    DBG ("JackAudioFilterStreamer::deactivateClient");

    if (client)
    {
        const ScopedLock sl (filter->getCallbackLock());

        jack_deactivate (client);
        jack_on_shutdown (client, juce_internalJackOnShutdownCallback, 0);
        jack_set_process_callback (client, juce_internalJackProcessCallback, 0);
        
        client = 0;
    }

#if JucePlugin_WantsMidiInput
    if (midiInput)
        midiInput->stop ();    deleteAndZero (midiInput);
#endif

#if JucePlugin_ProducesMidiOutput
    deleteAndZero (midiOutput);
#endif    
}

void JackAudioFilterStreamer::closeClient ()
{
    DBG ("JackAudioFilterStreamer::closeClient");

    if (client)
    {
        const ScopedLock sl (filter->getCallbackLock());

        jack_deactivate (client);
        jack_on_shutdown (client, juce_internalJackOnShutdownCallback, 0);
        jack_set_process_callback (client, juce_internalJackProcessCallback, 0);

/**
        DO NOT EVER CALL jack_client_close HERE !!

        it causes:
            cannot complete execution of the processing graph (Resource temporarily unavailable)
            zombified - calling shutdown handler

        jack_client_close (client);

*/
        client = 0;
    }

#if JucePlugin_WantsMidiInput
    if (midiInput)
        midiInput->stop ();
    deleteAndZero (midiInput);
#endif

#if JucePlugin_ProducesMidiOutput
    deleteAndZero (midiOutput);
#endif
}

//==============================================================================
void JackAudioFilterStreamer::audioPluginIOCallback (int numSamples)
{
    if (filter == 0 || client == 0 || numSamples <= 0)
        return;

    int i, numActiveInChans = 0, numActiveOutChans = 0;
    int numOutsWanted = JucePlugin_MaxNumOutputChannels;
    const int numInsWanted = JucePlugin_MaxNumInputChannels;

    for (i = 0; i < numInsWanted; ++i)
    {
        jack_default_audio_sample_t *in =
            (jack_default_audio_sample_t *) jack_port_get_buffer (
                                                    (jack_port_t*) inputPorts.getUnchecked(i), numSamples);
        if (in != 0)
            inChans [numActiveInChans++] = (float*) in;
    }

    while (numActiveInChans < numInsWanted)
        inChans [numActiveInChans++] = emptyBuffer.getSampleData (0, 0);

    for (i = 0; i < numOutsWanted; ++i)
    {
        jack_default_audio_sample_t *out =
            (jack_default_audio_sample_t *) jack_port_get_buffer (
                                                    (jack_port_t*) outputPorts.getUnchecked(i), numSamples);
        if (out != 0)
            outChans [numActiveOutChans++] = (float*) out;
    }

    i = 0;
    while (numActiveOutChans < numOutsWanted)
        outChans [numActiveOutChans++] = emptyBuffer.getSampleData (++i, 0);

    AudioSampleBuffer input (inChans, jmin (numInsWanted, numActiveInChans), numSamples);
    AudioSampleBuffer output (outChans, jmin (numOutsWanted, numActiveOutChans), numSamples);

    MidiBuffer midiBuffer;
#if JucePlugin_WantsMidiInput
    midiCollector.removeNextBlockOfMessages (midiBuffer, numSamples);
#endif

    {
        const ScopedLock sl (filter->getCallbackLock());

        if (filter->isSuspended())
        {
            output.clear();
        }
        else
        {
            for (int i = jmin (output.getNumChannels(), input.getNumChannels()); --i >= 0;)
                output.copyFrom (i, 0, input, i, 0, numSamples);

            filter->processBlock (output, midiBuffer);
        }
    }

    while (numOutsWanted < numActiveOutChans)
        zeromem (outChans[numOutsWanted++], sizeof (float) * numSamples);

#if JucePlugin_ProducesMidiOutput
    if (midiOutput)
    {
        int samplePos = 0;
        MidiMessage message (0xf4, 0.0);
        MidiBuffer::Iterator eventIterator (midiBuffer);
        while (eventIterator.getNextEvent (message, samplePos))
            midiOutput->sendMessageNow (message);
    }
#endif
}

void JackAudioFilterStreamer::sampleRateCallback (int newSampleRate)
{
    sampleRate = (double) newSampleRate;
}

void JackAudioFilterStreamer::blockSizeCallback (int newBlockSize)
{
    blockSize = newBlockSize;
}

void JackAudioFilterStreamer::audioPluginStarted (double newSampleRate, int newBlockSize)
{
    if (filter && ! isPlaying)
    {
        sampleRate = newSampleRate;
        blockSize = newBlockSize;

        DBG ("JackAudioFilterStreamer::audioPluginStarted");

        emptyBuffer.setSize (1 + filter->getNumOutputChannels(),
                             jmax (2048, blockSize * 2));
        emptyBuffer.clear();

        midiCollector.reset (sampleRate);

        filter->prepareToPlay (sampleRate, blockSize);

        isPlaying = true;

        suspendProcessing (false);
    }
}

void JackAudioFilterStreamer::audioPluginStopped()
{
    if (filter && isPlaying)
    {
        DBG ("JackAudioFilterStreamer::audioPluginStopped");

        suspendProcessing (true);

        isPlaying = false;

        filter->releaseResources();

        midiCollector.reset (sampleRate);

        emptyBuffer.setSize (1, 32);
    }
}

//==============================================================================
void JackAudioFilterStreamer::handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message)
{
#if JucePlugin_WantsMidiInput
    midiCollector.addMessageToQueue (message);
#endif
}

bool JackAudioFilterStreamer::getCurrentPosition (AudioPlayHead::CurrentPositionInfo& info)
{
    jack_position_t pos;
    jack_transport_state_t state = jack_transport_query (client, &pos);

#if 0
    printf ("valid %d\n", (pos.valid & JACK_POSITION_MASK));
    printf ("beat_type %f\n", pos.beat_type);
    printf ("beats_per_minute %f\n", pos.beats_per_minute);
    printf ("beats_per_bar %f\n", pos.beats_per_bar);
    printf ("frame_time %f\n", pos.frame_time);
    printf ("tick %d\n", pos.tick);
    printf ("bar_start_tick %f\n", pos.bar_start_tick);
    printf ("rolling %d\n\n", (state & JackTransportRolling));
#endif

    if ((pos.valid & JACK_POSITION_MASK)
        && (pos.beat_type > 0 && pos.beats_per_minute > 0))
    {
        info.bpm = pos.beats_per_minute;
        info.timeSigNumerator = roundFloatToInt (pos.beats_per_bar);
        info.timeSigDenominator = roundFloatToInt (pos.beat_type);
        info.timeInSeconds = pos.usecs / 1000000.0;
        info.editOriginTime = 0; // ???
        info.ppqPosition = pos.tick;
        info.ppqPositionOfLastBarStart = pos.bar_start_tick;
        switch (pos.frame_rate) {
        case 24:   info.frameRate = AudioPlayHead::fps24; break;
        case 25:   info.frameRate = AudioPlayHead::fps25; break;
        case 29:   info.frameRate = AudioPlayHead::fps2997; break;
        case 30:   info.frameRate = AudioPlayHead::fps30; break;
        default:   info.frameRate = AudioPlayHead::fpsUnknown; break;
        }
        info.isPlaying = (state & JackTransportRolling);
        info.isRecording = false;
        return true;
    }
    return false;
}

//==============================================================================
void JackAudioFilterStreamer::startCheckForServer ()
{
    DBG ("JackAudioFilterStreamer::startCheckForServer");

    if (! activateClient())
    {
        startTimer (1000);
    }
}

void JackAudioFilterStreamer::timerCallback ()
{
    if (activateClient())
    {
        stopTimer();
    }
}

//==============================================================================
bool JackAudioFilterStreamer::grabTransport (const bool conditionalGrab)
{
    if (client)
    {
        DBG ("JackAudioFilterStreamer::grabTransport");

        return (holdTransport = (jack_set_timebase_callback (client,
                                                             (conditionalGrab ? 1 : 0),
                                                             juce_internalJackTimebaseCallback,
                                                             this) == 0));
    }
    else
    {
        return false;
    }
}

void JackAudioFilterStreamer::releaseTransport ()
{
    if (client && holdTransport)
    {
        DBG ("JackAudioFilterStreamer::releaseTransport");

        jack_release_timebase(client);
    }
}

//==============================================================================
void JackAudioFilterStreamer::playTransport ()
{
    if (client && holdTransport)
    {
        DBG ("JackAudioFilterStreamer::playTransport");

        jack_transport_start(client);
    }
}

void JackAudioFilterStreamer::stopTransport ()
{
    if (client && holdTransport)
    {
        DBG ("JackAudioFilterStreamer::stopTransport");

        jack_transport_stop(client);
    }
}

void JackAudioFilterStreamer::seekTransportToFrame (const int frameToSeekAt)
{
    if (client && holdTransport)
    {
        DBG ("JackAudioFilterStreamer::seekTransportToFrame");

        jack_nframes_t frameNumber = 0;

        if (frameToSeekAt >= 0)
            frameNumber = frameToSeekAt;

        jack_transport_locate (client, frameNumber);
    }
}

//==============================================================================
void JackAudioFilterStreamer::setTempo (const double bpmToSet)
{
    if (bpmToSet > 0.0)
    {
        if (beatsPerMinute != bpmToSet)
        {
            DBG ("JackAudioFilterStreamer::setTempo");

            beatsPerMinute = bpmToSet;
            timeHasChanged = true;
        }
    }
}

void JackAudioFilterStreamer::setSyncTimeout (const double secondsTimeout)
{
    if (client && holdTransport)
    {
        DBG ("JackAudioFilterStreamer::setSyncTimeout");

        double timeout = 2.0;

        if (secondsTimeout > 0)
            timeout = secondsTimeout;

        jack_set_sync_timeout (client, (jack_time_t) (timeout * 1000000));
    }
}

//==============================================================================
void JackAudioFilterStreamer::suspendProcessing (const bool suspend)
{
    if (filter)
    {
        DBG ("JackAudioFilterStreamer::suspendProcessing");

        filter->suspendProcessing (suspend);
    }
}

//==============================================================================
AudioProcessorEditor* JackAudioFilterStreamer::createFilterEditorIfNeeded ()
{
    editor = (filter != 0) ? filter->createEditorIfNeeded() : 0;
    
    return editor;
}

//==============================================================================
static void juce_internalJackThreadInitCallback (void *arg)
{
    DBG ("jack started");
}

static void juce_internalJackOnShutdownCallback (void* arg)
{
    DBG ("jack shutdown");
    
    JackAudioFilterStreamer* filterStreamer = (JackAudioFilterStreamer*) arg;
    
    if (filterStreamer)
    {
        filterStreamer->audioPluginStopped ();
        filterStreamer->deactivateClient ();
        
        filterStreamer->startCheckForServer ();
    }
}

static int juce_internalJackProcessCallback (jack_nframes_t nframes, void* arg)
{
    JackAudioFilterStreamer* filterStreamer = (JackAudioFilterStreamer*) arg;

    if (filterStreamer)
        filterStreamer->audioPluginIOCallback (nframes);

    return 0;
}

/*
static int  juce_internalJackXRunCallback (void *arg)
{
    DBG ("jack xrun");
    return 0;
}

static int juce_internalJackBufferSizeCallback (jack_nframes_t nframes, void* arg)
{
    DBG ("jack blocksize changed");
    JackAudioFilterStreamer* filter = (JackAudioFilterStreamer*) arg;
    filter->blockSizeCallback (nframes);
    return 0;
}

static int juce_internalJackSampleRateCallback (jack_nframes_t nframes, void* arg)
{
    DBG ("jack samplerate changed");
    JackAudioFilterStreamer* filter = (JackAudioFilterStreamer*) arg;
    filter->sampleRateCallback (nframes);
    return 0;
}

static void juce_internalJackPortRegistrationCallback (jack_port_id_t port, int, void* arg)
{
    DBG ("server port registration callback");
//  JackAudioFilterStreamer* filterStreamer = (JackAudioFilterStreamer*) arg;
}

static void juce_internalJackFreewheelCallback (int starting, void *arg)
{
    DBG ("server freewheel changed");
}

static int juce_internalJackGraphOrderCallback (void *arg)
{
//    JackAudioFilterStreamer* filterStreamer = (JackAudioFilterStreamer*) arg;
//    filterStreamer->audioPluginStopped ();
//    printf ("graph reorder\n");
    return 0;
}

static int juce_internalJackSyncCallback (jack_transport_state_t state, jack_position_t *pos, void *arg)
{
    printf ("sync: %d:%d %d %3.1f/%3.1f %f %f\n",
            pos->beat, pos->bar, pos->tick, pos->beats_per_bar, pos->beat_type, pos->ticks_per_beat, pos->beats_per_minute );
    return 0;
}
*/

static void juce_internalJackTimebaseCallback (jack_transport_state_t state,
                                               jack_nframes_t nframes,
                                               jack_position_t *pos,
                                               int new_pos,
                                               void *arg)
{
  double min;         // minutes since frame 0
  long abs_tick;      // ticks since frame 0
  long abs_beat;      // beats since frame 0

  DBG ("jack timebase");

  JackAudioFilterStreamer* filterStreamer = (JackAudioFilterStreamer*) arg;

  if (new_pos || filterStreamer->timeHasChanged)
  {
      pos->valid = JackPositionBBT;
      pos->beats_per_bar = filterStreamer->beatsPerBar;
      pos->beat_type = filterStreamer->beatType;
      pos->ticks_per_beat = filterStreamer->ticksPerBeat;
      pos->beats_per_minute = filterStreamer->beatsPerMinute;

      min = pos->frame / ((double) pos->frame_rate * 60.0);
      abs_tick = roundDoubleToInt (min * pos->beats_per_minute * pos->ticks_per_beat);
      abs_beat = roundDoubleToInt (abs_tick / pos->ticks_per_beat);

      pos->bar = roundFloatToInt (abs_beat / pos->beats_per_bar);
      pos->beat = roundFloatToInt (abs_beat - (pos->bar * pos->beats_per_bar) + 1);
      pos->tick = roundFloatToInt (abs_tick - (abs_beat * pos->ticks_per_beat));
      pos->bar_start_tick = roundFloatToInt (pos->bar * pos->beats_per_bar * pos->ticks_per_beat);
      ++pos->bar;

      filterStreamer->timeHasChanged = false; // time change complete
  }
  else
  {
      // Compute BBT info based on previous period.
      pos->tick += roundDoubleToInt (nframes * pos->ticks_per_beat * pos->beats_per_minute / (pos->frame_rate * 60));

      while (pos->tick >= pos->ticks_per_beat)
      {
          pos->tick -= roundDoubleToInt (pos->ticks_per_beat);
          if (++pos->beat > pos->beats_per_bar)
          {
              pos->beat = 1;
              ++pos->bar;
              pos->bar_start_tick += pos->beats_per_bar * pos->ticks_per_beat;
          }
      }
  }
}

