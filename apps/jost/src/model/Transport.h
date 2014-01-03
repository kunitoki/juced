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

#ifndef __JUCETICE_JOSTTRANSPORT_HEADER__
#define __JUCETICE_JOSTTRANSPORT_HEADER__

#include "../Config.h"
#include "../Commands.h"
#include "PluginLoader.h"

#include "plugins/VstPlugin.h"

//==============================================================================
/**
    Global transport class.

    This class is a singleton, instantiated when the filter get created.
    It is available to every class that needs to know something about the global
    tempo of the host, and it work in the background for updating timing and
    keep GUI objects updated.

    You can register to it, and it will notify about every change on its side

    Also, it is used in the HostCallback to provide VstTimeInfo to vst plugins
    that ask for it.
*/
class Transport : public ChangeBroadcaster
{
public:

    //==============================================================================
    /** Construct a transport class */
    Transport (HostFilterBase* owner);

    /** Destructor */
    ~Transport ();

    //==============================================================================
#if JOST_USE_VST
    /** Returns the global time info for the whole host

        This is shared for all plugins calling it: but if one plugin mess it up
        due to the lack of "constness", the next plugins will receive a messed
        up structure (so it is dangerous to a have only one instance).
    */
    const VstTimeInfo* getTimeInfo ()       { return &timeInfo; }

#endif

    //==============================================================================
    /** This is called when the host is first activated, and before the callback */
    void prepareToPlay (double sampleRate, int samplesPerBlock);

    /** Called when the host is released: the audio setup is reset or changed */
    void releaseResources();

    /** Useful for external synchronization */
    void processIncomingMidi (MidiBuffer& midiMessages);
    
    /** Useful for VST synchronization */ 
    void processAudioPlayHead (AudioPlayHead* head);

    /** This will update the current block */
    void processBlock (const int blockSize);

    //==============================================================================
    /** Set an external transport */
    void setExternalTransport (ExternalTransport* externalTransport);

    //==============================================================================
    /** Try to play the transport

        All listeners will be notified about the change. If the transport is
        already playing, nothing will be done.

        @see stop, isPlaying
    */
    void play ();

    /** Try to stop the transport

        All listeners will be notified about the change. If the transport is
        not already playing, nothing will be done. Also, if we are in recording
        mode, then we will notified to stop recording (so willStopRecord will be
        true).

        @see play, isPlaying, willStopRecord
    */
    void stop ();

    /** Activate/deactivate recording

        Regardless of the transport state, we will activate recording: it will be
        immediate if we are playing (so permitting live record), or it will be
        delayed to the next play if we are stopped.

        @see play, stop, isRecording
    */
    void record ();

    /** Rewind the transport to its left locator

        This will rewind the transport to the left locator.
    */
    void rewind ();

    /** Notify transport listeners that we need to stop every voice

        This will communicate to stop voices, if we are listening about it.
        In fact every plugin that listen to the transport should put this in their
        processBlock function

        @code
            if (transport->willSendAllNotesOff ())
                midiBuffer.addEvent (noteOffMessage, blockSize - 1)
        @endcode
    */
    void allNotesOff ();

    /** Do a hard reset of recording

        This should flush all recording regardless of doing it in the gui thread.

        Be careful about using this !
    */
    void resetRecording ();

    //==============================================================================
    bool isPlaying () const                          { return playing; }
    bool isRecording () const                        { return recording; }
    bool isLooping () const                          { return looping; }

    void setLooping (const bool newValue)            {  looping = newValue; }

    //==============================================================================
    bool willStopRecord () const                     { return doStopRecord; }
    bool willSendAllNotesOff () const                { return doAllNotesOff; }
    bool willRewind () const                         { return doRewind; }

    //==============================================================================
    void setTimeSignature (const int bpmTempo,
                           const int barsCount,
                           const int timeDenominator);

    int getNumBars () const                          { return numBars; }
    int getTimeDenominator () const                  { return divDenominator; }

    //==============================================================================
    float getSampleRate () const                     { return sampleRate; }

    //==============================================================================
    void setTempo (const int newTempo);
    int getTempo () const                            { return bpmTempo; }

    //==============================================================================
    void setLeftLocator (const float beatNumber);
    float getLeftLocator () const                    { return leftLocator / (float) framesPerBeat; }

    void setRightLocator (const float beatNumber);
    float getRightLocator () const                   { return rightLocator / (float) framesPerBeat; }

    //==============================================================================
    int getDurationInFrames () const                 { return sequenceDurationFrames; }
    int getFramesPerBeat () const                    { return framesPerBeat; }

    //==============================================================================
    void setPositionInFrames (const int newPos)      { sequencePositionCounter = newPos; }
    int getPositionInFrames () const                 { return sequencePositionCounter; }

    void setPositionAbsolute (const float newPos);
    float getPositionAbsolute () const               { return sequencePositionCounter / (float) sequenceDurationFrames; }

	double getPositionInBeats()                      { return static_cast<double>(sequencePositionCounter) / framesPerBeat; }
	
    //==============================================================================
    void loadFromXml (XmlElement* xml);
    void saveToXml (XmlElement* xml);

private:

    HostFilterBase* owner;

    int sequencePositionCounter;
    int sequenceDurationFrames;
    int framesPerBeat;

    int leftLocator;
    int rightLocator;

    float sampleRate;
    int bpmTempo;
    int numBars;
    int divDenominator;

    // internal state bitflags
    bool playing        : 1,
         looping        : 1,
         recording      : 1,
         doStopRecord   : 1,
         doRewind       : 1,
         doAllNotesOff  : 1;

#if JOST_USE_VST
    // vst internal timeinfo
    VstTimeInfo timeInfo;
#endif

    // if we get passed an external transport, we will try to control it
    // TODO - this could be done in a better way, at least we could try to
    //        make all these classes a single interface
    ExternalTransport* externalTransport;
};


#endif

