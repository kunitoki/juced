/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-7 by Raw Material Software ltd.

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

#ifndef __JUCE_JUCE_EXTENDED_INCLUDES_INCLUDEFILES__
#define __JUCE_JUCE_EXTENDED_INCLUDES_INCLUDEFILES__

#ifndef __JUCETICE_STANDARDHEADER_HEADER__
 #include "extended/jucetice_StandardHeader.h"
#endif
#ifndef __JUCETICE_MATHCONSTANTS_HEADER__
 #include "extended/jucetice_MathConstants.h"
#endif
#ifndef __JUCETICE_AUDIOPARAMETER_HEADER__
 #include "extended/jucetice_AudioParameter.h"
#endif
#ifndef __JUCETICE_AUDIOPROGRAM_HEADER__
 #include "extended/jucetice_AudioProgram.h"
#endif
#ifndef __JUCETICE_AUDIOPLUGIN_HEADER__
 #include "extended/jucetice_AudioPlugin.h"
#endif
#ifndef __JUCETICE_AUDIOPROCESSINGBUFFER_HEADER__
 #include "extended/jucetice_AudioProcessingBuffer.h"
#endif
#ifndef __JUCETICE_EXTERNALTRANSPORT_HEADER__
 #include "extended/jucetice_ExternalTransport.h"
#endif

#ifndef __JUCETICE_BEATDETECTOR_HEADER__
 #include "extended/audio/beat/jucetice_BeatDetector.h"
#endif
#ifndef __JUCETICE_FFTWRAPPER_HEADER__
 #include "extended/audio/fft/jucetice_FFTWrapper.h"
#endif
#ifndef __JUCETICE_MPCAUDIOFORMAT_HEADER__
 #include "extended/audio/formats/jucetice_MADAudioFormat.h"
#endif
#ifndef __JUCETICE_MPCAUDIOFORMAT_HEADER__
 #include "extended/audio/formats/jucetice_MPCAudioFormat.h"
#endif
#ifndef __JUCETICE_LASHMANAGER_HEADER__
 #include "extended/audio/lash/jucetice_LashManager.h"
#endif
#ifndef __JUCETICE_MIDIAUTOMATORMANAGER_HEADER__
 #include "extended/audio/midi/jucetice_MidiAutomatorManager.h"
#endif
#ifndef __JUCETICE_MIDIFILTER_HEADER__
 #include "extended/audio/midi/jucetice_MidiFilter.h"
#endif
#ifndef __JUCETICE_MIDITRANSFORM_HEADER__
 #include "extended/audio/midi/jucetice_MidiTransform.h"
#endif
#ifndef __JUCETICE_MIDIMANIPULATOR_HEADER__
 #include "extended/audio/midi/jucetice_MidiManipulator.h"
#endif
#ifndef __JUCETICE_TUNINGMAP_HEADER__
 #include "extended/audio/midi/jucetice_TuningMap.h"
#endif
#ifndef __JUCETICE_OPENSOUNDBASE_HEADER__
 #include "extended/audio/osc/jucetice_OpenSoundBase.h"
#endif
#ifndef __JUCETICE_OPENSOUNDBUNDLE_HEADER__
 #include "extended/audio/osc/jucetice_OpenSoundBundle.h"
#endif
#ifndef __JUCETICE_OPENSOUNDCONTROLLER_HEADER__
 #include "extended/audio/osc/jucetice_OpenSoundController.h"
#endif
#ifndef __JUCETICE_OPENSOUNDMESSAGE_HEADER__
 #include "extended/audio/osc/jucetice_OpenSoundMessage.h"
#endif
#ifndef __JUCETICE_OPENSOUNDTIMETAG_HEADER__
 #include "extended/audio/osc/jucetice_OpenSoundTimeTag.h"
#endif
#ifndef __JUCETICE_UDPSOCKET_HEADER__
 #include "extended/audio/osc/jucetice_UDPSocket.h"
#endif
#ifndef __JUCETICE_AUDIOSOURCEPROCESSOR_HEADER__
 #include "extended/audio/processors/jucetice_AudioSourceProcessor.h"
#endif

#ifndef __JUCETICE_SQLITE_HEADER__
 #include "extended/database/jucetice_Sqlite.h"
#endif

#ifndef __JUCETICE_HASH_HEADER__
 #include "extended/containers/jucetice_Hash.h"
#endif
#ifndef __JUCETICE_OWNEDHASH_HEADER__
 #include "extended/containers/jucetice_OwnedHash.h"
#endif
#ifndef __JUCETICE_CIRCULARBUFFER_HEADER__
 #include "extended/containers/jucetice_CircularBuffer.h"
#endif
#ifndef __JUCETICE_LOCKFREEFIFO_HEADER__
 #include "extended/containers/jucetice_LockFreeFifo.h"
#endif
#ifndef __JUCETICE_LOOKUPTABLE_HEADER__
 #include "extended/containers/jucetice_LookupTable.h"
#endif
#ifndef __JUCETICE_SHAREDPOINTER_HEADER__
 #include "extended/containers/jucetice_SharedPointer.h"
#endif

#ifndef __JUCETICE_FASTDELEGATES_HEADER__
 #include "extended/utils/jucetice_FastDelegate.h"
#endif
#ifndef __JUCETICE_COMMANDLINETOKENIZER_HEADER__
 #include "extended/utils/jucetice_CommandLineTokenizer.h"
#endif
#ifndef __JUCETICE_TESTAPPLICATION_HEADER__
 #include "extended/utils/jucetice_TestApplication.h"
#endif
#ifndef __JUCETICE_FASTDELEGATES_HEADER__
 #include "extended/utils/jucetice_FastDelegate.h"
#endif
#ifndef __JUCETICE_GNUPLOTINTERFACE_HEADER__
 #include "extended/utils/jucetice_GnuplotInterface.h"
#endif
#ifndef __JUCETICE_SERIALIZABLE_HEADER__
 #include "extended/utils/jucetice_Serializable.h"
#endif

#ifndef __JUCETICE_IMAGESLIDER_HEADER__
 #include "extended/controls/jucetice_ImageSlider.h"
#endif
#ifndef __JUCETICE_IMAGEKNOB_HEADER__
 #include "extended/controls/jucetice_ImageKnob.h"
#endif
#ifndef __JUCETICE_JOYSTICK_HEADER__
 #include "extended/controls/jucetice_Joystick.h"
#endif
#ifndef __JUCETICE_PARAMETERTOGGLEBUTTON_HEADER__
 #include "extended/controls/jucetice_ParameterToggleButton.h"
#endif
#ifndef __JUCETICE_PARAMETERLEDBUTTON_HEADER__
 #include "extended/controls/jucetice_ParameterLedButton.h"
#endif
#ifndef __JUCETICE_PARAMETERCOMBOBOX_HEADER__
 #include "extended/controls/jucetice_ParameterComboBox.h"
#endif
#ifndef __JUCETICE_PARAMETERSLIDER_HEADER__
 #include "extended/controls/jucetice_ParameterSlider.h"
#endif
#ifndef __JUCETICE_PARAMETERJOYSTICK_HEADER__
 #include "extended/controls/jucetice_ParameterJoystick.h"
#endif
#ifndef __JUCETICE_DOCK_HEADER__
 #include "extended/controls/layout/jucetice_Dock.h"
#endif
#ifndef __JUCETICE_COMPONENTLAYOUTEDITOR_HEADER__
 #include "extended/controls/layout/jucetice_ComponentLayoutEditor.h"
#endif
#ifndef __JUCETICE_VIEWPORTNAVIGATOR_HEADER__
 #include "extended/controls/layout/jucetice_ViewportNavigator.h"
#endif
#ifndef __JUCETICE_DECIBELSCALE_HEADER__
 #include "extended/controls/meter/jucetice_DecibelScale.h"
#endif
#ifndef __JUCETICE_METERCOMPONENT_HEADER__
 #include "extended/controls/meter/jucetice_MeterComponent.h"
#endif
#ifndef __JUCETICE_HIGHQUALITYMETER_HEADER__
 #include "extended/controls/meter/jucetice_HighQualityMeter.h"
#endif
#ifndef __JUCETICE_PIANOGRID_HEADER__
 #include "extended/controls/grid/jucetice_PianoGrid.h"
#endif
#ifndef __JUCETICE_PIANOGRIDHEADER_HEADER__
 #include "extended/controls/grid/jucetice_PianoGridHeader.h"
#endif
#ifndef __JUCETICE_PIANOGRIDINDICATOR_HEADER__
 #include "extended/controls/grid/jucetice_PianoGridIndicator.h"
#endif
#ifndef __JUCETICE_PIANOGRIDKEYBOARD_HEADER__
 #include "extended/controls/grid/jucetice_PianoGridKeyboard.h"
#endif
#ifndef __JUCETICE_PIANOGRIDNOTE_HEADER__
 #include "extended/controls/grid/jucetice_PianoGridNote.h"
#endif
#ifndef __JUCETICE_GRAPHNODELISTENER_HEADER__
 #include "extended/controls/graph/jucetice_GraphNodeListener.h"
#endif
#ifndef __JUCETICE_GRAPHNODECOMPONENT_HEADER__
 #include "extended/controls/graph/jucetice_GraphNodeComponent.h"
#endif
#ifndef __JUCETICE_GRAPHCONNECTORCOMPONENT_HEADER__
 #include "extended/controls/graph/jucetice_GraphConnectorComponent.h"
#endif
#ifndef __JUCETICE_GRAPHLINKCOMPONENT_HEADER__
 #include "extended/controls/graph/jucetice_GraphLinkComponent.h"
#endif
#ifndef __JUCETICE_PRESETSELECTORCOMPONENT_HEADER__
 #include "extended/controls/selector/jucetice_PresetSelectorComponent.h"
#endif
#ifndef __JUCETICE_DRAWABLEPAD_HEADER__
 #include "extended/controls/pads/jucetice_DrawablePad.h"
#endif
#ifndef __JUCETICE_MIDIPAD_HEADER__
 #include "extended/controls/pads/jucetice_MidiPad.h"
#endif
#ifndef __JUCETICE_PLAYERCOMPONENT_HEADER__
 #include "extended/controls/player/jucetice_PlayerComponent.h"
#endif
#ifndef __JUCETICE_DIGITALDISPLAYCOMPONENT_HEADER__
 #include "extended/controls/player/jucetice_DigitalDisplayComponent.h"
#endif

#ifndef __JUCETICE_JUCETICELOOKANDFEEL_HEADER__
 #include "extended/lookandfeel/jucetice_JuceticeLookAndFeel.h"
#endif

#ifndef __JUCETICE_NET_HEADER__
 #include "extended/network/jucetice_Net.h"
#endif

#ifndef __JUCETICE_SCRIPTABLEENGINE_HEADER__
 #include "extended/scripting/jucetice_ScriptableEngine.h"
#endif

#ifndef __JUCETICE_TESTINGFRAMEWORK_HEADER__
 #include "extended/testing/jucetice_TestingFramework.h"
#endif

#endif
