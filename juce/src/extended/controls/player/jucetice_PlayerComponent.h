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

#ifndef __JUCETICE_PLAYERCOMPONENT_HEADER__
#define __JUCETICE_PLAYERCOMPONENT_HEADER__

#if 0

#include "../../../gui/components/juce_Component.h"
#include "../../../gui/components/buttons/juce_TextButton.h"
#include "../../../gui/components/buttons/juce_ToggleButton.h"
#include "../../../gui/components/controls/juce_Slider.h"
#include "../../../gui/components/filebrowser/juce_FileChooser.h"
#include "../../../audio/devices/juce_AudioDeviceManager.h"
#include "../../../audio/audio_sources/juce_AudioSourcePlayer.h"
#include "../../../audio/audio_sources/juce_AudioTransportSource.h"
#include "../../../audio/audio_sources/juce_AudioFormatReaderSource.h"
#include "../../../audio/audio_file_formats/juce_AudioFormatManager.h"
#include "jucetice_DigitalDisplayComponent.h"


//==============================================================================
class PlayerComponent  : public Component,
                         public ButtonListener,
                         public SliderListener,
                         public Timer,
                         public ChangeListener
{
public:

    PlayerComponent ();
    ~PlayerComponent();

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void sliderValueChanged (Slider* sliderThatWasMoved);
	void sliderDragStarted(Slider *slider);
	void sliderDragEnded(Slider *slider);
    void timerCallback();
    void changeListenerCallback(void *);

    juce_UseDebuggingNewOperator

private:

    Label *backLabel;
    Label *filenameLabel;
    TextButton *browseButton;
    TextButton *playButton;
    TextButton *stopButton;
    Slider *timeSlider;
    ToggleButton *loopButton;
    DigitalDisplayComponent *_timeDisplay;

    AudioDeviceManager _audioDeviceManager;
    AudioSourcePlayer _sourcePlayer;
	AudioFormatManager _audioFormatManager;
    AudioTransportSource _transportSource;
    AudioFormatReaderSource *_fileReaderSource;

    double _totalTime;
   	int _currentMinute;
   	int _currentSecond;
    volatile bool _timeSliderIsBeingDragged;
    File _lastWorkingDirectory;

    void setCurrentTime();

    PlayerComponent (const PlayerComponent&);
    const PlayerComponent& operator= (const PlayerComponent&);
};

#endif

#endif
