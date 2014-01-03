/***************************************************************************
 *   Copyright (C) 2009 by Christian Borss                                 *
 *   christian.borss@rub.de                                                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#ifndef __JUCER_HEADER_TABMAIN_TABMAIN_FF5AE30C__
#define __JUCER_HEADER_TABMAIN_TABMAIN_FF5AE30C__

//[Headers]     -- You can add your own extra header files here --
#include "juce_amalgamated.h"
#include "../ParamGainDelay.h"
#include "../ParamEnvelope.h"
#include "../TextList.h"
#include <vector>

// forward declarations
class MasterAndCommander;
class PresetManager;

class IRPlot;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TabMain  : public Component,
                 public SliderListener,
                 public ComboBoxListener
{
public:
    //==============================================================================
    TabMain (MasterAndCommander *m);
    ~TabMain();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void setPresetManager (PresetManager *man);
    void setGainDelayRange (ParamGainDelay *min,
                            ParamGainDelay *value,
                            ParamGainDelay *max);
    void setEnvelope (ParamEnvelope *param);
    void setNum(int num);
    void setID(const String &id);
    void setNotes(const String &notes);
    void addNotes(const String &notes);
    void setComboText(int num, const std::vector<String> & items);
    void setComboIndex(int num, int index);
    void sliderDragEnded (Slider* sliderThatWasMoved);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void sliderValueChanged (Slider* sliderThatWasMoved);


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    MasterAndCommander* master;
    PresetManager* presetManager;
    ParamGainDelay paramGainDelay;
    ParamEnvelope paramEnvelope;
    //[/UserVariables]

    //==============================================================================
    GroupComponent* groupComponentNotes;
    GroupComponent* groupComponentMainControl;
    Label* labelPresetNum;
    GroupComponent* groupComponentPresetSelector;
    Label* labelPresetText;
    ComboBox* comboBox;
    ComboBox* comboBox2;
    ComboBox* comboBox3;
    ComboBox* comboBox4;
    TextEditor* textEditorNotes;
    GroupComponent* groupComponentIRPlot;
    Slider* sliderInitialGap;
    Label* labelInitialGap;
    Slider* sliderLength;
    Label* labelLength;
    Slider* sliderPreDelay;
    Label* labelPreDelay;
    Slider* sliderDryGain;
    Label* labelDryGain;
    Slider* sliderWetGain;
    Slider* sliderMasterGain;
    Label* labelWetGain;
    Label* labelMasterGain;
    Slider* sliderPresetIncDec;
    IRPlot* irPlot;
    Slider* slider0ms;
    Slider* slider20ms;
    Slider* slider120ms;
    Slider* sliderENDms;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    TabMain (const TabMain&);
    const TabMain& operator= (const TabMain&);
};


#endif   // __JUCER_HEADER_TABMAIN_TABMAIN_FF5AE30C__
