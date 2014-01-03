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

#ifndef __JUCETICE_PEGGY2000_EDITOR_HEADER__
#define __JUCETICE_PEGGY2000_EDITOR_HEADER__

#include "JuceFilter.h"
#include "parameters.h"
#include "gui/BoolGridComponent.h"
#include "gui/SliderFieldComponent.h"
#include "gui/SnappingSlider.h"
#include "lookandfeel/MyLookAndFeel.h"


//==============================================================================
class EditorComponent : public AudioProcessorEditor,
                        public ComboBoxListener,
                        public ChangeListener,
                        public SliderListener,
                        public ButtonListener
{
public:

     EditorComponent (JuceFilter* const ownerFilter);
     ~EditorComponent();

     void changeListenerCallback (void* source);
     void sliderValueChanged (Slider*);
     void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
     void buttonClicked (Button* buttonThatWasClicked);
     void paint (Graphics& g);

 //    static const char* bg1_png;
 //   static const int bg1_pngSize;


private:
     enum {    penv_a, penv_d, penv_s, penv_r,
               fenv_a, fenv_d,  fenv_s, fenv_r,
               aenv_a, aenv_d, aenv_s, aenv_r, aenv_amt,
               plfo_spd, plfo_amt,
               flfo_spd, flfo_amt,
               alfo_spd, alfo_amt,
               f_sat, f_res, f_cut,
               ch_spd, ch_dph, ch_mix,
               dl_tme, dl_lvl,dl_fb,
               g_sus, m_vol,g_swn,

               penv_amt,  fenv_amt,
               g_len, f_80,
               vel_filter, vel_pitch, vel_amp,
               o1_cent, o2_cent, o_mix, o1_semi, o2_semi};

     enum{o2_wave, o1_wave, g_tempo, g_mode, f_wave};
     enum{ plfo_wave1,plfo_wave3,plfo_wave2,
          flfo_wave1,flfo_wave3,flfo_wave2,
          alfo_wave1,alfo_wave3,alfo_wave2,
          o2_env,o1_env,o1_lfo,o2_lfo,o1_sync,o_env,o_lfo,g_on
          };


     const static int numSliders = 43;
     const static int numCombos = 5;
     const static int numToggles = 17;

     SnappingSlider*     Sliders[numSliders];
     ComboBox*           Combos[numCombos];
     ToggleButton*       Toggles[numToggles];

     TextButton* g_reset;
     BoolGridComponent* DaGrid;
     SliderFieldComponent* DaField;

     int BitTable[32];
     void  setGridSegment(int seg, float f);
     float getGridSegment(int seg);

     Image* internalCachedImage1;

     void updateParametersFromFilter();

     // handy wrapper method to avoid having to cast the filter to a DemoJuceFilter
     // every time we need it..
     JuceFilter* getFilter() const throw()       { return (JuceFilter*) getAudioProcessor(); }
};


#endif
