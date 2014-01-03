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

#ifndef __JUCE_POSITIONABLERESAMPLINGAUDIOSOURCE_JUCEHEADER__
#define __JUCE_POSITIONABLERESAMPLINGAUDIOSOURCE_JUCEHEADER__

#include "juce_PositionableAudioSource.h"


//==============================================================================
/**
    A type of AudioSource that takes an input source and changes its sample rate.

    @see AudioSource
*/
class JUCE_API  PositionableResamplingAudioSource  : public PositionableAudioSource
{
public:
    //==============================================================================
    /** Creates a ResamplingAudioSource for a given input source.

        @param inputSource              the input source to read from
        @param deleteInputWhenDeleted   if true, the input source will be deleted when
                                        this object is deleted
    */
    PositionableResamplingAudioSource (PositionableAudioSource* const inputSource,
                                       const bool deleteInputWhenDeleted);

    /** Destructor. */
    ~PositionableResamplingAudioSource();

    /** Changes the resampling ratio.

        (This value can be changed at any time, even while the source is running).

        @param samplesInPerOutputSample     if set to 1.0, the input is passed through; higher
                                            values will speed it up; lower values will slow it
                                            down. The ratio must be greater than 0
    */
    void setResamplingRatio (const double samplesInPerOutputSample);

    /** Returns the current resampling ratio.

        This is the value that was set by setResamplingRatio().
    */
    double getResamplingRatio() const throw()                   { return ratio; }

    //==============================================================================
    /** Toggles loop-mode.

        If set to true, it will continuously loop the input source. If false,
        it will just emit silence after the source has finished.

        @see isLooping
    */
    void setLooping (const bool shouldLoop) throw();

    /** Returns whether loop-mode is turned on or not. */
    bool isLooping() const;

    //==============================================================================
    /** Implementation of the AudioSource method. */
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate);

    /** Implementation of the AudioSource method. */
    void releaseResources();

    /** Implementation of the AudioSource method. */
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill);

    //==============================================================================
    /** Implements the PositionableAudioSource method. */
    void setNextReadPosition (int newPosition);

    /** Implements the PositionableAudioSource method. */
    int getNextReadPosition() const;

    /** Implements the PositionableAudioSource method. */
    int getTotalLength() const;

    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    PositionableAudioSource* const input;
    const bool deleteInputWhenDeleted;
    double ratio, lastRatio;
    AudioSampleBuffer buffer;
    int bufferPos, sampsInBuffer;
    double subSampleOffset;
    double coefficients[6];

    int volatile nextPlayPos;
    bool volatile looping;

    void setFilterCoefficients (double c1, double c2, double c3, double c4, double c5, double c6);
    void createLowPass (const double proportionalRate);

    struct FilterState
    {
        double x1, x2, y1, y2;
    };

    FilterState filterStates[2];
    void resetFilters();

    void applyFilter (float* samples, int num, FilterState& fs);

    PositionableResamplingAudioSource (const PositionableResamplingAudioSource&);
    const PositionableResamplingAudioSource& operator= (const PositionableResamplingAudioSource&);
};


#endif   // __JUCE_RESAMPLINGAUDIOSOURCE_JUCEHEADER__
