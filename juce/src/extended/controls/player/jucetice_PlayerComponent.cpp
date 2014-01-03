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

#if 0

BEGIN_JUCE_NAMESPACE

#include "jucetice_PlayerComponent.h"

#include "../../audio/formats/jucetice_MADAudioFormat.h"
#include "../../audio/formats/jucetice_MPCAudioFormat.h"


//==============================================================================
PlayerComponent::PlayerComponent ()
    : backLabel (0),
      filenameLabel (0),
      browseButton (0),
      playButton (0),
      stopButton (0),
      timeSlider (0),
      loopButton (0),
      _timeDisplay (0),
      _fileReaderSource(0),
      _totalTime(0),
      _currentMinute(-1),
      _currentSecond(-1),
      _timeSliderIsBeingDragged(false),
      _lastWorkingDirectory(File::getCurrentWorkingDirectory())
{
    addAndMakeVisible (backLabel = new Label (T("Background"), String::empty));
    backLabel->setFont (Font (15.0000f, Font::plain));
    backLabel->setEditable (false, false, false);
    backLabel->setColour (Label::backgroundColourId, Colour (0x4e6d6d6d));
    backLabel->setWantsKeyboardFocus(false);

    addAndMakeVisible (filenameLabel = new Label (T("Filename"), String::empty));
    filenameLabel->setFont (Font (13.0000f, Font::bold));
    filenameLabel->setJustificationType (Justification::centredLeft);
    filenameLabel->setEditable (false, false, false);
    filenameLabel->setColour (Label::backgroundColourId, Colour (0xaf6d6d6d));
    filenameLabel->setColour (Label::textColourId, Colours::white);
    filenameLabel->setColour (TextEditor::textColourId, Colours::black);
    filenameLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
    filenameLabel->setWantsKeyboardFocus(false);

    addAndMakeVisible (browseButton = new TextButton (T("Browse")));
    browseButton->setButtonText (T("browse"));
    browseButton->setConnectedEdges (Button::ConnectedOnLeft);
    browseButton->addButtonListener (this);
    browseButton->setWantsKeyboardFocus(false);


    addAndMakeVisible (loopButton = new ToggleButton(T("loop track")));
    loopButton->setToggleState(false, false);
    loopButton->addButtonListener (this);
    loopButton->setWantsKeyboardFocus(false);

    addAndMakeVisible (playButton = new TextButton (T("Play")));
    playButton->setButtonText (T("play / pause"));
    playButton->setConnectedEdges (Button::ConnectedOnRight);
    playButton->addButtonListener (this);
    playButton->setWantsKeyboardFocus(false);

    addAndMakeVisible (stopButton = new TextButton (T("Stop")));
    stopButton->setButtonText (T("stop"));
    stopButton->setConnectedEdges (Button::ConnectedOnLeft);
    stopButton->addButtonListener (this);
    stopButton->setWantsKeyboardFocus(false);

    addAndMakeVisible (timeSlider = new Slider (T("Time Slider")));
    timeSlider->setRange (0, 10, 0);
    timeSlider->setSliderStyle (Slider::LinearHorizontal);
    timeSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    timeSlider->setChangeNotificationOnlyOnRelease(true);
    timeSlider->addListener (this);
    timeSlider->setWantsKeyboardFocus(false);

    addAndMakeVisible (_timeDisplay = new DigitalDisplayComponent (T("TimeDisplay"), T("---:--")));
//    _timeDisplay->setFont (Font (13.0000f, Font::bold));
//    _timeDisplay->setJustificationType (Justification::centredLeft);
    _timeDisplay->setMakeStroke(false);
    _timeDisplay->setEditable (false, false, false);
//    _timeDisplay->setColour (Label::backgroundColourId, Colour (0xaf6d6d6d));
//    _timeDisplay->setColour (Label::textColourId, Colours::white);
//    _timeDisplay->setColour (TextEditor::textColourId, Colours::black);
//    _timeDisplay->setColour (TextEditor::backgroundColourId, Colour (0x0));
    _timeDisplay->setWantsKeyboardFocus(false);

	_audioDeviceManager.initialise(0, 2, 0, true);
    _audioDeviceManager.addAudioCallback(&_sourcePlayer);
    _sourcePlayer.setSource(&_transportSource);
	_audioFormatManager.registerBasicFormats();
	_audioFormatManager.registerFormat(new MADAudioFormat, false);
	_audioFormatManager.registerFormat(new MPCAudioFormat, false);

	_transportSource.addChangeListener(this);
}

PlayerComponent::~PlayerComponent()
{
    deleteAndZero (backLabel);
    deleteAndZero (filenameLabel);
    deleteAndZero (browseButton);
    deleteAndZero (loopButton);
    deleteAndZero (playButton);
    deleteAndZero (stopButton);
    deleteAndZero (timeSlider);
    deleteAndZero (_timeDisplay);

    _audioDeviceManager.removeAudioCallback(&_sourcePlayer);
    _sourcePlayer.setSource(0);
    _transportSource.setSource(0);

    delete _fileReaderSource;
}

//==============================================================================
void PlayerComponent::paint (Graphics& g)
{
    g.fillAll(Colour(0xffd6d6d6));
}

void PlayerComponent::resized()
{
    backLabel->setBounds (8, 48, 480, 16);
    filenameLabel->setBounds (8, 8, 416, 16);
    browseButton->setBounds (424, 8, 64, 16);
    loopButton->setBounds (8, 48, 100, 16);
    playButton->setBounds (184, 48, 64, 16);
    stopButton->setBounds (248, 48, 64, 16);
    timeSlider->setBounds (8, 32, 416, 8);
    _timeDisplay->setBounds (424, 24, 64, 24);
}

void PlayerComponent::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == browseButton)
    {
    	FileChooser fileChooser(T("Select an audio file to open..."),
								_lastWorkingDirectory,
								_audioFormatManager.getWildcardForAllFormats(),
								false);

		if(fileChooser.browseForFileToOpen())
		{
			File audioFile(fileChooser.getResult());
			_lastWorkingDirectory = audioFile.getParentDirectory();

			AudioFormatReader *fileReader = _audioFormatManager.createReaderFor(audioFile);

			if(fileReader)
			{
				_transportSource.stop();
				_transportSource.setSource(0);

				filenameLabel->setText(audioFile.getFileName(), false);

				delete _fileReaderSource;
				_fileReaderSource = new AudioFormatReaderSource(fileReader, true);
				_fileReaderSource->setLooping(loopButton->getToggleState());
				_transportSource.setSource(_fileReaderSource, 32768, fileReader->sampleRate);
				_transportSource.setPosition(.0f);

				_totalTime = double(fileReader->lengthInSamples) / double(fileReader->sampleRate);
				timeSlider->setRange(.0, _totalTime, 1.);
				timeSlider->setValue(.0, false, false);

				setCurrentTime();
			}
		}
    }
    else if (buttonThatWasClicked == playButton)
    {
    	if(_transportSource.isPlaying())
			_transportSource.stop();
		else
			_transportSource.start();
    }
    else if (buttonThatWasClicked == stopButton)
    {
    	_transportSource.stop();
    	_transportSource.setPosition(0);

    	setCurrentTime();
    }
    else if (buttonThatWasClicked == loopButton)
    {
    	if(_fileReaderSource)
			_fileReaderSource->setLooping(loopButton->getToggleState());
    }
}

void PlayerComponent::sliderValueChanged (Slider* slider)
{
    if (slider == timeSlider)
    {
    	_transportSource.setPosition(slider->getValue());

    	if(!_transportSource.isPlaying())
			setCurrentTime();
    }
}

void PlayerComponent::sliderDragStarted(Slider *slider)
{
    if (slider == timeSlider)
		_timeSliderIsBeingDragged = true;
}

void PlayerComponent::sliderDragEnded(Slider *slider)
{
    if (slider == timeSlider)
		_timeSliderIsBeingDragged = false;
}

void PlayerComponent::timerCallback()
{
	setCurrentTime();
}

void PlayerComponent::setCurrentTime()
{
	double time_ = _transportSource.getCurrentPosition();
	double showTime_ = (_totalTime - time_) + .5f;

	int currentMinute_ = int(showTime_) / 60;
	int currentSecond_ = int(showTime_) % 60;

	if(_currentMinute != currentMinute_ || _currentSecond != currentSecond_)
	{
		_currentMinute = currentMinute_;
		_currentSecond = currentSecond_;

		_timeDisplay->setText (String::formatted(T("-%02d:%02d"), _currentMinute, _currentSecond), false);
	}

	if(!_timeSliderIsBeingDragged)
		timeSlider->setValue(time_, false, false);
}

void PlayerComponent::changeListenerCallback(void *objectThatHasChanged)
{
	if(&_transportSource == objectThatHasChanged)
	{
		if(_transportSource.isPlaying())
			startTimer(100);
		else
			stopTimer();
	}
}

END_JUCE_NAMESPACE

#endif

