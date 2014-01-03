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

#include "juce_JackBridgeFilterStreamer.h"
#include "../juce_IncludeCharacteristics.h"

//==============================================================================
static char default_bridge[] = "jostbridge";

//==============================================================================
JackBridgeFilterStreamer::JackBridgeFilterStreamer ()
    : Thread ("JACKBridgeThread"),
      timeHasChanged (false),
      beatsPerMinute (120.0),
      ticksPerBeat (960.0 /*PPQ*/),
      beatsPerBar (4),
      beatType (4),
      filter (0),
      editor (0),
      isPlaying (false),
      sampleRate (0),
      blockSize (0),
      midiInput (0),
      midiOutput (0),
      holdTransport (false),
      inputBuffers (1, 1),
      outputBuffers (1, 1),
      emptyBuffer (1, 32)
{
    DBG ("JackBridgeFilterStreamer::JackBridgeFilterStreamer");

    jassert (JucePlugin_MaxNumInputChannels <= 64);   // your filter have more input channels
                                                      // than the maximum allowed to be handle by this bridge !
    jassert (JucePlugin_MaxNumOutputChannels <= 64);  // your filter have more input channels
                                                      // than the maximum allowed to be handle by this streamer !
}

JackBridgeFilterStreamer::~JackBridgeFilterStreamer()
{
    DBG ("JackBridgeFilterStreamer::~JackBridgeFilterStreamer");

    setFilter (0, false);
}

//==============================================================================
void JackBridgeFilterStreamer::setFilter (AudioProcessor* filterToUse,
                                          const bool checkForServer,
                                          const bool connectToPhysicalInputs,
                                          const bool connectToPhysicalOutputs)
{
    DBG ("JackAudioFilterStreamer::setFilter");

    if (filter && editor != 0)
        filter->editorBeingDeleted (editor);

    audioPluginStopped ();
    closeClient ();

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
bool JackBridgeFilterStreamer::activateClient ()
{
    jassert (filter);  // you should have already attached a filter,
                       // if not, how would this streamer works ?

    sampleRate = 0;
    blockSize = 0;

    int handle;
    char name[65];
    float *memblock;

    snprintf (name, 64, "%s::%s", default_bridge, "info");
    if ((handle = shm_open (name, O_RDWR, 0666)) == -1) 
    {
       printf ("failed to open shm info. Is jack client running? \n");
       return false;
    }

    ftruncate (handle, sizeof(InfoBlock));
    infoblock = (InfoBlock *) mmap (0, sizeof(InfoBlock),
                                    PROT_READ | PROT_WRITE, MAP_SHARED, handle, 0);

    close (handle);

    sampleRate = (double) infoblock->sample_rate;
    blockSize = infoblock->buffer_frames;
    inputs = infoblock->inputs;
    outputs = infoblock->outputs;

    DBG ("info block allocated");

    snprintf(name, 64, "%s::%s", default_bridge, "buffer");
    if ((handle = shm_open (name, O_RDWR, 0666)) == -1)
    {
       printf ("failed to open shm buffers. Is jack client running? \n");
       return false;
    }
    
    ftruncate (handle, sizeof(float)* blockSize * (inputs + outputs));
    memblock = (float *) mmap (0, sizeof(float) * blockSize * (inputs + outputs),
                               PROT_READ | PROT_WRITE, MAP_SHARED, handle, 0);
    close (handle);

    DBG ("mem block allocated");

    inputblock = memblock;
    outputblock = memblock + inputs * blockSize;

    snprintf (name, 64, "%s::%s", default_bridge, "sem1");
    semaphore1 = sem_open (name, O_RDWR);
    snprintf (name, 64, "%s::%s", default_bridge, "sem2");
    semaphore2 = sem_open (name, O_RDWR);

    // resize input/output buffers
    inputBuffers.setSize (inputs, blockSize);
    outputBuffers.setSize (outputs, blockSize);

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
    midiCollector.reset (sampleRate);

    // update samplerate and block size before we just activate the client
    audioPluginStarted ((double) sampleRate, (int)    blockSize);

    // start the thread !
    startThread (10);

    return true;
}

void JackBridgeFilterStreamer::closeClient ()
{
    DBG ("JackBridgeFilterStreamer::closeClient");

    stopThread (5000);

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
void JackBridgeFilterStreamer::run ()
{
    unsigned int i, j;
    float *in, *out;
    float *buffer;
    char name[65];

    struct sched_param attr;

    attr.__sched_priority = infoblock->priority - 1;
    sched_setscheduler (0, SCHED_FIFO, &attr);

    while (! threadShouldExit ())
    {
        /* wait to be woken up by the Jack callback thread */
        infoblock->running = 1;
        sem_wait (semaphore1);
        
        memset (outputblock, 0, 
                sizeof(float) * blockSize * outputs);

        // get the input data from JACK and copy it to the filter buffers
        for (i = 0; i < inputs; i++) {
            in = inputblock + i * blockSize;
            inputBuffers.copyFrom (i, 0, in, blockSize);
        }

        // process the filter
        audioPluginIOCallback (blockSize);

        // get the input data from the filter buffers and copy it to the bridge
        for (i = 0; i < outputs; i++)
        {
            buffer = outputBuffers.getSampleData (i, 0);
            out = outputblock + i * blockSize;

            for (j = 0; j < (uint) blockSize; j++)
                out[j] = buffer[j];
        }

        sem_post (semaphore2);
    }

    infoblock->running = 0;
    snprintf (name, 64, "%s::%s", default_bridge, "buffer");
    unlink (name);

    snprintf (name, 64, "%s::%s", default_bridge, "info");
    unlink (name);

    sem_post (semaphore2);
}

void JackBridgeFilterStreamer::audioPluginIOCallback (int numSamples)
{
    if (filter == 0 || numSamples <= 0)
        return;

    int i, numActiveInChans = 0, numActiveOutChans = 0;
    int numOutsWanted = outputs;
    const int numInsWanted = inputs;

    for (i = 0; i < numInsWanted; ++i)
    {
        float* in = inputBuffers.getSampleData (i);

        if (in != 0)
            inChans [numActiveInChans++] = (float*) in;
    }

    while (numActiveInChans < numInsWanted)
        inChans [numActiveInChans++] = emptyBuffer.getSampleData (0, 0);

    for (i = 0; i < numOutsWanted; ++i)
    {
        float* out = outputBuffers.getSampleData (i);

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
        MidiMessage message (0,0);
        MidiBuffer::Iterator eventIterator (midiBuffer);
        while (eventIterator.getNextEvent (message, samplePos))
            midiOutput->sendMessageNow (message);
    }
#endif
}

void JackBridgeFilterStreamer::sampleRateCallback (int newSampleRate)
{
    sampleRate = (double) newSampleRate;
}

void JackBridgeFilterStreamer::blockSizeCallback (int newBlockSize)
{
    blockSize = newBlockSize;
}

void JackBridgeFilterStreamer::audioPluginStarted (double newSampleRate, int newBlockSize)
{
    if (filter && ! isPlaying)
    {
        sampleRate = newSampleRate;
        blockSize = newBlockSize;

        DBG ("JackBridgeFilterStreamer::audioPluginStarted");

        emptyBuffer.setSize (1 + filter->getNumOutputChannels(),
                             jmax (2048, blockSize * 2));
        emptyBuffer.clear();

        midiCollector.reset (sampleRate);

        filter->prepareToPlay (sampleRate, blockSize);

        isPlaying = true;

        suspendProcessing (false);
    }
}

void JackBridgeFilterStreamer::audioPluginStopped()
{
    if (filter && isPlaying)
    {
        DBG ("JackBridgeFilterStreamer::audioPluginStopped");

        suspendProcessing (true);

        isPlaying = false;

        filter->releaseResources();

        midiCollector.reset (sampleRate);

        emptyBuffer.setSize (1, 32);
    }
}

//==============================================================================
void JackBridgeFilterStreamer::handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message)
{
#if JucePlugin_WantsMidiInput
    midiCollector.addMessageToQueue (message);
#endif
}

bool JackBridgeFilterStreamer::getCurrentPosition (AudioPlayHead::CurrentPositionInfo& info)
{
/*
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
*/
    return false;
}

//==============================================================================
void JackBridgeFilterStreamer::startCheckForServer ()
{
    DBG ("JackBridgeFilterStreamer::startCheckForServer");

    startTimer (1000);
}

void JackBridgeFilterStreamer::timerCallback ()
{
    DBG ("checking for jack bridge");

    if (activateClient())
    {
        stopTimer();
    }
}

//==============================================================================
bool JackBridgeFilterStreamer::grabTransport (const bool conditionalGrab)
{
/*
    if (client)
    {
        DBG ("JackBridgeFilterStreamer::grabTransport");

        return (holdTransport = (jack_set_timebase_callback (client,
                                                             (conditionalGrab ? 1 : 0),
                                                             juce_internalJackTimebaseCallback,
                                                             this) == 0));
    }
    else
*/
    {
        return false;
    }
}

void JackBridgeFilterStreamer::releaseTransport ()
{
/*
    if (client && holdTransport)
    {
        DBG ("JackBridgeFilterStreamer::releaseTransport");

        jack_release_timebase(client);
    }
*/
}

//==============================================================================
void JackBridgeFilterStreamer::playTransport ()
{
/*
    if (client && holdTransport)
    {
        DBG ("JackAudioFilterStreamer::playTransport");

        jack_transport_start(client);
    }
*/
}

void JackBridgeFilterStreamer::stopTransport ()
{
/*
    if (client && holdTransport)
    {
        DBG ("JackAudioFilterStreamer::stopTransport");

        jack_transport_stop(client);
    }
*/
}

void JackBridgeFilterStreamer::seekTransportToFrame (const int frameToSeekAt)
{
/*
    if (client && holdTransport)
    {
        DBG ("JackAudioFilterStreamer::seekTransportToFrame");

        jack_nframes_t frameNumber = 0;

        if (frameToSeekAt >= 0)
            frameNumber = frameToSeekAt;

        jack_transport_locate (client, frameNumber);
    }
*/
}

//==============================================================================
void JackBridgeFilterStreamer::setTempo (const double bpmToSet)
{
/*
    if (bpmToSet > 0.0)
    {
        if (beatsPerMinute != bpmToSet)
        {
            DBG ("JackAudioFilterStreamer::setTempo");

            beatsPerMinute = bpmToSet;
            timeHasChanged = true;
        }
    }
*/
}

void JackBridgeFilterStreamer::setSyncTimeout (const double secondsTimeout)
{
/*
    if (client && holdTransport)
    {
        DBG ("JackAudioFilterStreamer::setSyncTimeout");

        double timeout = 2.0;

        if (secondsTimeout > 0)
            timeout = secondsTimeout;

        jack_set_sync_timeout (client, (jack_time_t) (timeout * 1000000));
    }
*/
}

//==============================================================================
void JackBridgeFilterStreamer::suspendProcessing (const bool suspend)
{
    if (filter)
    {
        DBG ("JackAudioFilterStreamer::suspendProcessing");

        filter->suspendProcessing (suspend);
    }
}

//==============================================================================
AudioProcessorEditor* JackBridgeFilterStreamer::createFilterEditorIfNeeded ()
{
    editor = (filter != 0) ? filter->createEditorIfNeeded() : 0;
    
    return editor;
}

//==============================================================================
/*
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
        filterStreamer->closeClient ();
        
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

*/
