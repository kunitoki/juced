/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2008 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2008 by Julian Storer.

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

   @author  rockhardbuns
   @tweaker Lucio Asnaghi

 ==============================================================================
*/

#include "EditorComponent.h"
#include "bg.h"

//==============================================================================
EditorComponent::EditorComponent (JuceFilter* const ownerFilter)
    : AudioProcessorEditor (ownerFilter)
{
     //lookup table for encoding bools in a float
     BitTable[0] = 2;
     BitTable[1] = 4;
     BitTable[2] = 8;
     BitTable[3] = 16;
     BitTable[4] = 32;
     BitTable[5] = 64;
     BitTable[6] = 128;
     BitTable[7] = 256;
     BitTable[8] = 512;
     BitTable[9] = 1024;
     BitTable[10] = 2048;
     BitTable[11] = 4096;
     BitTable[12] = 8192;
     BitTable[13] = 16384;
     BitTable[14] = 32768;
     BitTable[15] = 65536;
     BitTable[16] = 131072;
     BitTable[17] = 262144;
     BitTable[18] = 524288;
     BitTable[19] = 1048576;


     internalCachedImage1 = ImageCache::getFromMemory (bg::bg_png, bg::bg_pngSize);


     static MyLookAndFeel* MyLook = 0;
     if (MyLook == 0){ MyLook = new MyLookAndFeel(); }
     LookAndFeel::setDefaultLookAndFeel (MyLook);


//sliders
     for(int i = 0; i < numSliders; i++){
          addAndMakeVisible (Sliders[i] = new SnappingSlider (T("a")));
          Sliders[i]->setRange (0, 1.0f, 0);
          Sliders[i]->setSliderStyle (Slider::RotaryVerticalDrag);
          Sliders[i]->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
          Sliders[i]->addListener (this);
          Sliders[i]->setSnap(0.0f , 0.05f);
     }

     Sliders[penv_amt]->setRange (-1, 1, 0);
     Sliders[fenv_amt]->setRange (-1, 1, 0);
     Sliders[f_80]->setRange (-1, 1, 0);
     Sliders[vel_filter]->setRange (-1, 1, 0);
     Sliders[vel_pitch]->setRange (-1, 1, 0);
     Sliders[o1_semi]->setRange (-1, 1, 0);
     Sliders[o2_semi]->setRange (-1, 1, 0);
     Sliders[o1_cent]->setRange (-1, 1, 0);
     Sliders[o2_cent]->setRange (-1, 1, 0);
     Sliders[o_mix]->setRange (-1, 1, 0);
     Sliders[g_len]->setRange (0, 16, 1);
     Sliders[g_len]->setValue (8);
     Sliders[vel_amp]->setRange (-1, 1, 0);

     Sliders[penv_a]->setBounds (428, 28, 32, 32); Sliders[penv_a]->setSkewFactor(0.7); Sliders[penv_a]->setSnap(0.0f , 0.0f);
     Sliders[penv_d]->setBounds (460, 28, 32, 32); Sliders[penv_d]->setSkewFactor(0.7); Sliders[penv_d]->setSnap(0.0f , 0.0f);
     Sliders[penv_s]->setBounds (492, 28, 32, 32); Sliders[penv_s]->setSnap(0.0f , 0.0f);
     Sliders[penv_r]->setBounds (524, 28, 32, 32); Sliders[penv_r]->setSkewFactor(0.7); Sliders[penv_r]->setSnap(0.0f , 0.0f);
     Sliders[penv_amt]->setBounds (556, 12, 32, 32);
     Sliders[fenv_a]->setBounds (428, 104, 32, 32); Sliders[fenv_a]->setSkewFactor(0.7); Sliders[fenv_a]->setSnap(0.0f , 0.0f);
     Sliders[fenv_d]->setBounds (460, 104, 32, 32); Sliders[fenv_d]->setSkewFactor(0.7); Sliders[fenv_d]->setSnap(0.0f , 0.0f);
     Sliders[fenv_s]->setBounds (492, 104, 32, 32); Sliders[fenv_s]->setSnap(0.0f , 0.0f);
     Sliders[fenv_r]->setBounds (524, 104, 32, 32); Sliders[fenv_r]->setSkewFactor(0.7); Sliders[fenv_r]->setSnap(0.0f , 0.0f);
     Sliders[fenv_amt]->setBounds (556, 88, 32, 32);
     Sliders[aenv_a]->setBounds (428, 180, 32, 32); Sliders[aenv_a]->setSkewFactor(0.7); Sliders[aenv_a]->setSnap(0.0f , 0.0f);
     Sliders[aenv_d]->setBounds (460, 180, 32, 32); Sliders[aenv_d]->setSkewFactor(0.7); Sliders[aenv_d]->setSnap(0.0f , 0.0f);
     Sliders[aenv_s]->setBounds (492, 180, 32, 32); Sliders[aenv_s]->setSnap(0.0f , 0.0f);
     Sliders[aenv_r]->setBounds (524, 180, 32, 32); Sliders[aenv_r]->setSkewFactor(0.7); Sliders[aenv_r]->setSnap(0.0f , 0.0f);
     Sliders[aenv_amt]->setBounds (556, 164, 32, 32);
     Sliders[plfo_spd]->setBounds (340, 28, 32, 32);Sliders[plfo_spd]->setSkewFactor(0.7);Sliders[plfo_spd]->setSnap(0.0f , 0.0f);
     Sliders[plfo_amt]->setBounds (376, 28, 32, 32);Sliders[plfo_amt]->setSkewFactor(0.7); Sliders[plfo_amt]->setSnap(0.0f , 0.01f);
     Sliders[flfo_spd]->setBounds (340, 104, 32, 32);Sliders[flfo_spd]->setSkewFactor(0.7);Sliders[flfo_spd]->setSnap(0.0f , 0.0f);
     Sliders[flfo_amt]->setBounds (376, 104, 32, 32);Sliders[flfo_amt]->setSkewFactor(0.7); Sliders[flfo_amt]->setSnap(0.0f , 0.01f);
     Sliders[alfo_spd]->setBounds (340, 180, 32, 32);Sliders[alfo_spd]->setSkewFactor(0.7);Sliders[alfo_spd]->setSnap(0.0f , 0.0f);
     Sliders[alfo_amt]->setBounds (376, 180, 32, 32);Sliders[alfo_amt]->setSkewFactor(0.7); Sliders[alfo_amt]->setSnap(0.0f , 0.01f);
     Sliders[f_res]->setBounds (160, 136, 32, 32);   Sliders[f_res]->setSnap(0.0f , 0.01f);
     Sliders[f_80]->setBounds (208, 136, 32, 32);
     Sliders[f_cut]->setBounds (124, 136, 32, 32); Sliders[f_cut]->setSkewFactor(0.7); Sliders[f_cut]->setSnap(0.0f , 0.0f);
     Sliders[ch_mix]->setBounds (328, 252, 36, 32);
     Sliders[ch_spd]->setBounds (328, 300, 36, 32);
     Sliders[ch_dph]->setBounds (328, 348, 36, 32);
     Sliders[dl_tme]->setBounds (400, 300, 36, 32);
     Sliders[dl_lvl]->setBounds (400, 348, 36, 32);
     Sliders[dl_fb]->setBounds (400, 252, 36, 32);
     Sliders[vel_filter]->setBounds (472, 300, 36, 32);
     Sliders[vel_pitch]->setBounds (472, 252, 36, 32);
     Sliders[o1_semi]->setBounds (12, 32, 32, 32);
     Sliders[o2_semi]->setBounds (12, 68, 32, 32);
     Sliders[o1_cent]->setBounds (44, 32, 32, 32);
     Sliders[o2_cent]->setBounds (44, 68, 32, 32);
     Sliders[o_mix]->setBounds (232, 20, 32, 32);
     Sliders[f_sat]->setBounds (244, 136, 32, 32);Sliders[f_sat]->setSnap(0.0f , 0.0f);
     Sliders[g_sus]->setBounds (260, 281, 36, 32);
     Sliders[g_len]->setBounds (220, 281, 32, 32);
     Sliders[g_swn]->setBounds (220, 238, 32, 32);
     Sliders[m_vol]->setBounds (544, 348, 36, 32);
     Sliders[vel_amp]->setBounds (472, 348, 36, 32);

//*****

//combobox

     addAndMakeVisible (Combos[o2_wave] = new ComboBox (T("o2_wave")));
     Combos[o2_wave]->setEditableText (false);
     Combos[o2_wave]->setJustificationType (Justification::centredLeft);
     Combos[o2_wave]->setTextWhenNothingSelected (T("SAW"));
     Combos[o2_wave]->setTextWhenNoChoicesAvailable (String::empty);
     Combos[o2_wave]->addItem (T("SAW"), 1);
     Combos[o2_wave]->addItem (T("SAW 2"), 2);
     Combos[o2_wave]->addItem (T("TRI"), 3);
     Combos[o2_wave]->addItem (T("TRI 2"), 4);
     Combos[o2_wave]->addItem (T("SQR"), 5);
     Combos[o2_wave]->addItem (T("SIN"), 6);
     Combos[o2_wave]->addListener (this);
     Combos[o2_wave]->setBounds (80, 72, 64, 24);


     addAndMakeVisible (Combos[o1_wave] = new ComboBox (T("o1_wave")));
     Combos[o1_wave]->setEditableText (false);
     Combos[o1_wave]->setJustificationType (Justification::centredLeft);
     Combos[o1_wave]->setTextWhenNothingSelected (T("SAW"));
     Combos[o1_wave]->setTextWhenNoChoicesAvailable (String::empty);
     Combos[o1_wave]->addItem (T("SAW"), 1);
     Combos[o1_wave]->addItem (T("SAW 2"), 2);
     Combos[o1_wave]->addItem (T("TRI"), 3);
     Combos[o1_wave]->addItem (T("TRI 2"), 4);
     Combos[o1_wave]->addItem (T("SQR"), 5);
     Combos[o1_wave]->addItem (T("SIN"), 6);
     Combos[o1_wave]->addListener (this);
     Combos[o1_wave]->setBounds (80, 36, 64, 24);

     addAndMakeVisible (Combos[g_tempo] = new ComboBox (T("g_tempo")));
     Combos[g_tempo]->setEditableText (false);
     Combos[g_tempo]->setJustificationType (Justification::centredLeft);
     Combos[g_tempo]->setTextWhenNothingSelected (T("1/16"));
     Combos[g_tempo]->setTextWhenNoChoicesAvailable (T("(no choices)"));
     Combos[g_tempo]->addItem (T("1/4"), 1);
     Combos[g_tempo]->addItem (T("1/8"), 2);
     Combos[g_tempo]->addItem (T("1/16"), 3);
     Combos[g_tempo]->addItem (T("1/32"), 4);
     Combos[g_tempo]->addListener (this);
     Combos[g_tempo]->setBounds (212, 360, 88, 24);


     addAndMakeVisible (Combos[g_mode] = new ComboBox (T("g_mode")));
     Combos[g_mode]->setEditableText (false);
     Combos[g_mode]->setJustificationType (Justification::centredLeft);
     Combos[g_mode]->setTextWhenNothingSelected (T("Key Sync"));
     Combos[g_mode]->setTextWhenNoChoicesAvailable (T("(no choices)"));
     Combos[g_mode]->addItem (T("Key Sync"), 1);
     Combos[g_mode]->addItem (T("Bar Sync"), 2);
     Combos[g_mode]->addListener (this);
     Combos[g_mode]->setBounds (212, 328, 88, 24);

     addAndMakeVisible (Combos[f_wave] = new ComboBox (T("f_wave")));
     Combos[f_wave]->setEditableText (false);
     Combos[f_wave]->setJustificationType (Justification::centredLeft);
     Combos[f_wave]->setTextWhenNothingSelected (T("LowPass"));
     Combos[f_wave]->setTextWhenNoChoicesAvailable (T("(no choices)"));
     Combos[f_wave]->addItem (T("LowPass"), 1);
     Combos[f_wave]->addItem (T("HighPass"), 2);
     Combos[f_wave]->addItem (T("BandPass"), 3);
     Combos[f_wave]->addItem (T("Notch"), 4);
     Combos[f_wave]->addListener (this);
     Combos[f_wave]->setBounds (12, 144, 100, 24);

//******
     addAndMakeVisible (g_reset = new TextButton (T("g_reset")));
     g_reset->setButtonText (T("R"));
     g_reset->addButtonListener (this);
// TODO -     g_reset->setBackgroundColours (Colour (0x98f20000), Colours::white);
     g_reset->setBounds (267, 239, 24, 24);

     DaGrid = new BoolGridComponent();
     DaGrid->setBounds (12, 256, 193, 63);
     DaGrid->addChangeListener (this);
     addAndMakeVisible (DaGrid);

     DaField = new SliderFieldComponent();
     DaField->setBounds (12, 324, 193, 63);
     DaField->addChangeListener (this);
     addAndMakeVisible (DaField);
//******

// Toggles

     for(int i = 0 ; i < numToggles ; i++){
          addAndMakeVisible (Toggles[i] = new ToggleButton (T("t")));
          Toggles[i]->setClickingTogglesState(false);
          Toggles[i]->addButtonListener (this);
          Toggles[i]->setWantsKeyboardFocus(false);
     }

     Toggles[plfo_wave1]->setButtonText (T("Saw"));
     Toggles[plfo_wave3]->setButtonText (T("Sin"));
     Toggles[plfo_wave2]->setButtonText (T("Sqr"));
     Toggles[flfo_wave1]->setButtonText (T("Saw"));
     Toggles[flfo_wave3]->setButtonText (T("Sin"));
     Toggles[flfo_wave2]->setButtonText (T("Sqr"));
     Toggles[alfo_wave1]->setButtonText (T("Saw"));
     Toggles[alfo_wave3]->setButtonText (T("Sin"));
     Toggles[alfo_wave2]->setButtonText (T("Sqr"));
     Toggles[o2_env]->setButtonText (T("Env"));
     Toggles[o1_env]->setButtonText (T("Env"));
     Toggles[o1_lfo]->setButtonText (T("LFO"));
     Toggles[o2_lfo]->setButtonText (T("LFO"));
     Toggles[o1_sync]->setButtonText (T("Sync"));
     Toggles[o_env]->setButtonText (T("Env"));
     Toggles[o_lfo]->setButtonText (T("LFO"));
     Toggles[g_on]->setButtonText (String::empty);


     Toggles[o_env]->setBounds (224, 68, 48, 22);
     Toggles[o_lfo]->setBounds (224, 84, 48, 22);
     Toggles[plfo_wave1]->setBounds (292, 20, 48, 22);
     Toggles[plfo_wave3]->setBounds (292, 52, 48, 22);
     Toggles[plfo_wave2]->setBounds (292, 36, 48, 22);
     Toggles[flfo_wave1]->setBounds (292, 96, 48, 22);
     Toggles[flfo_wave3]->setBounds (292, 128, 48, 22);
     Toggles[flfo_wave2]->setBounds (292, 112, 48, 22);
     Toggles[alfo_wave1]->setBounds (292, 172, 48, 22);
     Toggles[alfo_wave3]->setBounds (292, 204, 48, 22);
     Toggles[alfo_wave2]->setBounds (292, 188, 48, 22);

     Toggles[o2_env]->setBounds (148, 68, 48, 22);
     Toggles[o1_env]->setBounds (148, 28, 48, 22);
     Toggles[o1_lfo]->setBounds (148, 44, 48, 22);
     Toggles[o2_lfo]->setBounds (148, 84, 48, 22);
     Toggles[o1_sync]->setBounds (148, 12, 52, 22);
     Toggles[g_on]->setBounds (72, 228, 24, 32);

//*****
     updateParametersFromFilter();
     setSize (600,400);
    // register ourselves with the filter - it will use its ChangeBroadcaster base
    ownerFilter->addChangeListener (this);
}



EditorComponent::~EditorComponent()
{
     ImageCache::release (internalCachedImage1);

     getFilter()->removeChangeListener (this);

     deleteAllChildren();
}


//==============================================================================
void EditorComponent::paint (Graphics& g)
{
     g.setTiledImageFill (*internalCachedImage1, 0, 0, 1.0000f);
     g.fillAll ();
}

//==============================================================================
void EditorComponent::changeListenerCallback (void* caller)
{
     if (caller == getFilter()){   updateParametersFromFilter(); }

     if (caller == DaGrid){
     //Update filter grid from boolGrid
          int tmp = DaGrid->getLastChanged();
          tmp = (tmp / 20) + 1;
          getFilter()->setParameterNotifyingHost(tmp + 58, getGridSegment(tmp));
     }

     if (caller == DaField){
          int index = DaField->getLastSlider();
          getFilter()->setParameterNotifyingHost(index + 63, DaField->getValue(index));
     }
}

void EditorComponent::comboBoxChanged (ComboBox* caller)
{
     for(int i = 0; i < numCombos; i++){
          if(Combos[i] == caller){
               getFilter()->setParameterNotifyingHost (i + numSliders, (float) caller->getSelectedId ());
               return;
          }
     }
}

void EditorComponent::buttonClicked (Button* caller)
{
      if(caller == Toggles[plfo_wave1]) {
           Toggles[plfo_wave1]->setToggleState(1,0);
           Toggles[plfo_wave2]->setToggleState(0,0);
           Toggles[plfo_wave3]->setToggleState(0,0);
           getFilter()->setParameterNotifyingHost (ParMan::plfo_wave, 0.0f);
      }
      if(caller == Toggles[plfo_wave2]) {
           Toggles[plfo_wave1]->setToggleState(0,0);
           Toggles[plfo_wave2]->setToggleState(1,0);
           Toggles[plfo_wave3]->setToggleState(0,0);
           getFilter()->setParameterNotifyingHost (ParMan::plfo_wave, 0.5f);
      }
      if(caller == Toggles[plfo_wave3]) {
           Toggles[plfo_wave1]->setToggleState(0,0);
           Toggles[plfo_wave2]->setToggleState(0,0);
           Toggles[plfo_wave3]->setToggleState(1,0);
           getFilter()->setParameterNotifyingHost (ParMan::plfo_wave, 1.0f);
      }
//***
      if(caller == Toggles[flfo_wave1]) {
           Toggles[flfo_wave1]->setToggleState(1,0);
           Toggles[flfo_wave2]->setToggleState(0,0);
           Toggles[flfo_wave3]->setToggleState(0,0);
           getFilter()->setParameterNotifyingHost (ParMan::flfo_wave, 0.0f);
      }
      if(caller == Toggles[flfo_wave2]) {
           Toggles[flfo_wave1]->setToggleState(0,0);
           Toggles[flfo_wave2]->setToggleState(1,0);
           Toggles[flfo_wave3]->setToggleState(0,0);
           getFilter()->setParameterNotifyingHost (ParMan::flfo_wave, 0.5f);
      }
      if(caller == Toggles[flfo_wave3]) {
           Toggles[flfo_wave1]->setToggleState(0,0);
           Toggles[flfo_wave2]->setToggleState(0,0);
           Toggles[flfo_wave3]->setToggleState(1,0);
           getFilter()->setParameterNotifyingHost (ParMan::flfo_wave, 1.0f);
      }
//***
      if(caller == Toggles[alfo_wave1]) {
           Toggles[alfo_wave1]->setToggleState(1,0);
           Toggles[alfo_wave2]->setToggleState(0,0);
           Toggles[alfo_wave3]->setToggleState(0,0);
           getFilter()->setParameterNotifyingHost (ParMan::alfo_wave, 0.0f);
      }
     if(caller == Toggles[alfo_wave2]) {
           Toggles[alfo_wave1]->setToggleState(0,0);
           Toggles[alfo_wave2]->setToggleState(1,0);
           Toggles[alfo_wave3]->setToggleState(0,0);
           getFilter()->setParameterNotifyingHost (ParMan::alfo_wave, 0.5f);
      }
      if(caller == Toggles[alfo_wave3]) {
           Toggles[alfo_wave1]->setToggleState(0,0);
           Toggles[alfo_wave2]->setToggleState(0,0);
           Toggles[alfo_wave3]->setToggleState(1,0);
           getFilter()->setParameterNotifyingHost (ParMan::alfo_wave, 1.0f);
      }
//***

      if(caller == Toggles[o2_env]) {
           Toggles[o2_env]->setToggleState( !(Toggles[o2_env]->getToggleState()), 0);
           getFilter()->setParameterNotifyingHost(ParMan::o2_env, float(Toggles[o2_env]->getToggleState()));
      }
      if(caller == Toggles[o1_env]) {
           Toggles[o1_env]->setToggleState( !(Toggles[o1_env]->getToggleState()), 0);
           getFilter()->setParameterNotifyingHost(ParMan::o1_env, float(Toggles[o1_env]->getToggleState()));
      }
      if(caller == Toggles[o1_lfo]) {
           Toggles[o1_lfo]->setToggleState( !(Toggles[o1_lfo]->getToggleState()), 0);
           getFilter()->setParameterNotifyingHost(ParMan::o1_lfo, float(Toggles[o1_lfo]->getToggleState()));
      }
      if(caller == Toggles[o2_lfo]) {
           Toggles[o2_lfo]->setToggleState( !(Toggles[o2_lfo]->getToggleState()), 0);
           getFilter()->setParameterNotifyingHost(ParMan::o2_lfo, float(Toggles[o2_lfo]->getToggleState()));
      }
      if(caller == Toggles[o1_sync]) {
           Toggles[o1_sync]->setToggleState( !(Toggles[o1_sync]->getToggleState()), 0);
           getFilter()->setParameterNotifyingHost(ParMan::o1_sync, (Toggles[o1_sync]->getToggleState() ? 1.0f : 0.0f));
      }
      if(caller == Toggles[o_env]) {
           Toggles[o_env]->setToggleState( !(Toggles[o_env]->getToggleState()), 0);
           getFilter()->setParameterNotifyingHost(ParMan::o_env, float(Toggles[o_env]->getToggleState()));
      }
      if(caller == Toggles[o_lfo]) {
           Toggles[o_lfo]->setToggleState( !(Toggles[o_lfo]->getToggleState()), 0);
           getFilter()->setParameterNotifyingHost(ParMan::o_lfo, float(Toggles[o_lfo]->getToggleState()));
      }
      if(caller == Toggles[g_on]) {
           Toggles[g_on]->setToggleState( !(Toggles[g_on]->getToggleState()), 0);
           getFilter()->setParameterNotifyingHost(ParMan::g_on, float(Toggles[g_on]->getToggleState()));
      }
//***

      if(caller == g_reset) {
           DaGrid->reset();
           DaField->reset();
           getFilter()->setParameterNotifyingHost(ParMan::g_g1, 0.0f);
           getFilter()->setParameterNotifyingHost(ParMan::g_g2, 0.0f);
           getFilter()->setParameterNotifyingHost(ParMan::g_g3, 0.0f);
           getFilter()->setParameterNotifyingHost(ParMan::g_g4, 0.0f);
           for(int i = 0; i < 16; i++){
                getFilter()->setParameterNotifyingHost(ParMan::g_f1 + i, 0.0f);
           }
      }
}

void EditorComponent::sliderValueChanged (Slider* caller)
{
     if (caller == Sliders[g_len]){
          DaGrid->setLength((int)caller->getValue());
          DaField->setLength((int)caller->getValue());
          getFilter()->setParameterNotifyingHost (ParMan::g_len, (float) caller->getValue());
          return;
     }


     for(int i = 0 ; i < numSliders ; i++){
          if(Sliders[i] == caller){
               getFilter()->setParameterNotifyingHost (i, (float) caller->getValue());
               return;
          }
     }
}

//==============================================================================
void EditorComponent::updateParametersFromFilter()
{
    JuceFilter* const filter = getFilter();
    filter->getCallbackLock().enter();

     for(int i = 0 ; i < numSliders ; i++){
          Sliders[i]->setValue(filter->getParameter(i));
          if (i == g_len){
               DaGrid->setLength((int)Sliders[i]->getValue());
               DaField->setLength((int)Sliders[i]->getValue());
          }
     }

     for(int i = 0; i < numCombos; i++){
          Combos[i]->setSelectedId((int)filter->getParameter(i + numSliders));
     }


     for(int i = 0; i < numToggles; i++){ //Zero all toggles
          Toggles[i]->setToggleState(0,0);
     }

     float tmp = filter->getParameter(ParMan::plfo_wave);
     if (tmp == 0.0f) {Toggles[plfo_wave1]->setToggleState(1,0);}
     if (tmp == 0.5f) {Toggles[plfo_wave2]->setToggleState(1,0);}
     if (tmp == 1.0f) {Toggles[plfo_wave3]->setToggleState(1,0);}

     tmp = filter->getParameter(ParMan::flfo_wave);
     if (tmp == 0.0f) {Toggles[flfo_wave1]->setToggleState(1,0);}
     if (tmp == 0.5f) {Toggles[flfo_wave2]->setToggleState(1,0);}
     if (tmp == 1.0f) {Toggles[flfo_wave3]->setToggleState(1,0);}

     tmp = filter->getParameter(ParMan::alfo_wave);
     if (tmp == 0.0f) {Toggles[alfo_wave1]->setToggleState(1,0);}
     if (tmp == 0.5f) {Toggles[alfo_wave2]->setToggleState(1,0);}
     if (tmp == 1.0f) {Toggles[alfo_wave3]->setToggleState(1,0);}

     if (filter->getParameter(ParMan::o2_env) == 1.0f) {Toggles[o2_env]->setToggleState(1,0);}
     if (filter->getParameter(ParMan::o1_env) == 1.0f) {Toggles[o1_env]->setToggleState(1,0);}
     if (filter->getParameter(ParMan::o1_lfo) == 1.0f) {Toggles[o1_lfo]->setToggleState(1,0);}
     if (filter->getParameter(ParMan::o2_lfo) == 1.0f) {Toggles[o2_lfo]->setToggleState(1,0);}
     if (filter->getParameter(ParMan::o1_sync) == 1.0f) {Toggles[o1_sync]->setToggleState(1,0);}
     if (filter->getParameter(ParMan::o_env) == 1.0f) {Toggles[o_env]->setToggleState(1,0);}
     if (filter->getParameter(ParMan::o_lfo) == 1.0f) {Toggles[o_lfo]->setToggleState(1,0);}
     if (filter->getParameter(ParMan::g_on) == 1.0f) {Toggles[g_on]->setToggleState(1,0);}

     setGridSegment(1, filter->getParameter(ParMan::g_g1));
     setGridSegment(2, filter->getParameter(ParMan::g_g2));
     setGridSegment(3, filter->getParameter(ParMan::g_g3));
     setGridSegment(4, filter->getParameter(ParMan::g_g4));

     for(int i = 0; i < 16 ; i++){
          DaField->setValue(i, getFilter()->getParameter(i + ParMan::g_f1)) ;
     }
    // ..release the lock ASAP
    filter->getCallbackLock().exit();
}


//***********   Two methods for converting grid parts to and from floats
//***********   Has a pair of very simmilar siblings in the filter thread
float EditorComponent::getGridSegment(int seg)
{
    int iOut = 0;
    seg--;
    for(int i = 0 ; i < 20 ; i++){
        iOut |= int(BitTable[i] * DaGrid->getCellState(i + (seg*20)));
    }
    return (float)iOut;
}

void EditorComponent::setGridSegment(int seg, float f)
{
    int val = (int)f;
    seg--;

    for(int i = 0 ; i < 20 ; i++){
        DaGrid->setCellState( i + (seg*20) ,   ((val & BitTable[i]) != 0));
    }
}
//**********

