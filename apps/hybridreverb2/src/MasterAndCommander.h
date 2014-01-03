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


#ifndef __MASTERANDCOMMANDER_H__
#define __MASTERANDCOMMANDER_H__


#include "juce_amalgamated.h"
#include "ParamGainDelay.h"
#include "ParamEnvelope.h"
#include "ParamTimbre.h"
#include "ParamPreset.h"
#include "ParamPreferences.h"
#include "ParamPartitionWisdom.h"
#include <vector>


// forward declarations
class EditorComponent;
class TabMain;
class TabModulation;
class TabTimbre;
class TabPresetEditor;
class TabPreferences;
class TabAbout;
class IRPlot;
class FreqPlot;
class SampleData;
class PresetManager;
class HybridReverb2Processor;
class SystemConfig;


class MasterAndCommander
{
public:
    MasterAndCommander(HybridReverb2Processor *ap);
    ~MasterAndCommander();

    // common methods
    void onGuiReady(void);
    void print(String msg);
    const String & getBasedir();
    const String & getUserdir();
    const String & getDBdir();
    const ParamPreferences & getPreferences();
    const ParamPartitionWisdom & getPartitionWisdom();

    // "Main" component methods
    void registerEditorComponent(EditorComponent *comp);

    // "Main" tab methods
    void registerTabMain(TabMain *tab);
    void onValueChangedPresetNum(int value, bool force = false);
    void onValueChangedGainDelay(ParamGainDelay *param);
    void onValueChangedEnvelope(ParamEnvelope *param);

    // "Modulation" tab methods
    void registerTabModulation(TabModulation *tab);

    // "Timbre" tab methods
    void registerTabTimbre(TabTimbre *tab);
    void onValueChangedTimbre(ParamTimbre *param);

    // "Preset Editor" tab methods
    void registerTabPresetEditor(TabPresetEditor *tab);
    void setPresetDB(const std::vector<ParamPreset> & newPresetDB,
                     bool updateManager = true);
    void savePresetDB(const std::vector<ParamPreset> & newPresetDB);
    void savePresetDBas(const std::vector<ParamPreset> & newPresetDB,
                        const String & presetFile);

    // "Preferences" tab methods
    void registerTabPreferences(TabPreferences *tab);
    void onValueChangedPreferences(const ParamPreferences & param);

    // "About" tab methods
    void registerTabAbout(TabAbout *tab);

    // "IRPlot" component methods
    void registerIRPlot(IRPlot *plot);

    // "FreqPlot" component methods
    void registerFreqPlot(FreqPlot *plot);


private:
    EditorComponent   *compMain;
    TabMain           *tabMain;
    TabModulation     *tabModulation;
    TabTimbre         *tabTimbre;
    TabPresetEditor   *tabPresetEditor;
    TabPreferences    *tabPreferences;
    TabAbout          *tabAbout;
    IRPlot            *irPlot;
    FreqPlot          *freqPlot;
    SampleData        *dataOriginal;
    SampleData        *dataTimbre;
    SampleData        *dataModulation;
    SampleData        *dataGainDelay;
    SampleData        *dataEnvelope;
    ParamGainDelay    *paramGainDelay;
    ParamEnvelope     *paramEnvelope;
    ParamTimbre       *paramTimbre;
    ParamPreset       preset;
    ParamPreferences  paramPreferences;
    SystemConfig      *systemConfig;
    PresetManager     *presetManager;
    HybridReverb2Processor      *audioPlugin;
    String           logMessage;
    bool             changeFilter;
    bool             enabledTimbre;
    bool             enabledModulation;
    bool             enabledGainDelay;
    bool             enabledEnvelope;
    int              currentPreset;

    void updateOriginal(void);
    void updateTimbre(void);
    void updateModulation(void);
    void updateGainDelay(void);
    void updateEnvelope(void);
    void updateFinal(void);

};


#endif   // __MASTERANDCOMMANDER_H__
