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


#ifdef _WINDOWS
#include <Windows.h>
#endif

#include "MasterAndCommander.h"
#include "ParamGainDelay.h"
#include "ParamEnvelope.h"
#include "ParamTimbre.h"
#include "ParamPreferences.h"
#include "gui/EditorComponent.h"
#include "gui/TabMain.h"
#include "gui/TabModulation.h"
#include "gui/TabTimbre.h"
#include "gui/TabPresetEditor.h"
#include "gui/TabPreferences.h"
#include "gui/TabAbout.h"
#include "gui/IRPlot.h"
#include "SampleData.h"
#include "SystemConfig.h"
#include "PresetManager.h"
#include <stdio.h>


MasterAndCommander::MasterAndCommander (HybridReverb2Processor *ap)
    : compMain(0),
      tabMain(0),
      tabModulation(0),
      tabTimbre(0),
      tabPresetEditor(0),
      tabPreferences(0),
      tabAbout(0),
      irPlot(0),
      freqPlot(0),
      dataOriginal(0),
      dataTimbre(0),
      dataModulation(0),
      dataGainDelay(0),
      dataEnvelope(0),
      paramGainDelay(0),
      paramEnvelope(0),
      paramTimbre(0),
      systemConfig(0),
      presetManager(0),
      audioPlugin(ap),
      logMessage(JUCE_T("")),
      changeFilter(true),
      enabledTimbre(false),
      enabledModulation(false),
      enabledGainDelay(true),
      enabledEnvelope(true),
      currentPreset(-1)
{
    dataOriginal   = new SampleData();
    dataTimbre     = new SampleData();
    dataModulation = new SampleData();
    dataGainDelay  = new SampleData();
    dataEnvelope   = new SampleData();

    systemConfig = new SystemConfig();
    paramPreferences = systemConfig->getPreferences();
    String presetFilename = systemConfig->getPresetFilename();
    presetManager = new PresetManager();
    currentPreset = presetManager->readFile(presetFilename);

    if (currentPreset < 0)
    {
        FileChooser fc(JUCE_T("Invalid preset file. Please choose another file to open..."),
                       systemConfig->getUserdir(),
                       JUCE_T("*.xml"),
                       true);

        if (fc.browseForFileToOpen())
        {
            File chosenFile = fc.getResult();
            paramPreferences.presetFile = chosenFile.getFullPathName();
            currentPreset = presetManager->readFile(paramPreferences.presetFile);
            systemConfig->setPreferences(paramPreferences);
        }
        else
        {
        }
    }
}

MasterAndCommander::~MasterAndCommander()
{
}


////////////////////////////////////////////////////////////////
//
//    common methods
//

void MasterAndCommander::onGuiReady(void)
{
    print(JUCE_T("MasterAndCommander::onGuiReady()\n"));
    onValueChangedPresetNum(currentPreset, true);
}


void MasterAndCommander::print(String msg)
{
#if defined(DEBUG)
    logMessage += msg;
    if (tabMain != 0)
        tabMain->setNotes(logMessage);
#endif
}


const String & MasterAndCommander::getBasedir()
{
    return systemConfig->getBasedir();
}


const String & MasterAndCommander::getUserdir()
{
    return systemConfig->getUserdir();
}


const String & MasterAndCommander::getDBdir()
{
    return systemConfig->getDBdir();
}


const ParamPreferences & MasterAndCommander::getPreferences()
{
    return systemConfig->getPreferences();
}


const ParamPartitionWisdom & MasterAndCommander::getPartitionWisdom()
{
    return systemConfig->getPartitionWisdom();
}


////////////////////////////////////////////////////////////////
//
//    "Main" component methods
//

void MasterAndCommander::registerEditorComponent(EditorComponent *comp)
{
    compMain = comp;
    print(JUCE_T("----[ EditorComponent registered ]----\n"));
}


////////////////////////////////////////////////////////////////
//
//    "Main" tab methods
//

void MasterAndCommander::registerTabMain(TabMain *tab)
{
    tabMain = tab;
    tab->setPresetManager(presetManager);
}


void MasterAndCommander::onValueChangedPresetNum(int value, bool force)
{
    print(JUCE_T("MasterAndCommander::onValueChangedPresetNum(") + String(value) + JUCE_T(", ") + String(force) + JUCE_T(") called \n"));
    changeFilter = changeFilter || (value != currentPreset);
    if (changeFilter == false && force == false)
        return;

    currentPreset = value;
    presetManager->setCurrentPresetNum(value);
    printf("Master :    new PRESET NUM value : %d\n", value);

    preset = presetManager->getPreset(value);
    paramGainDelay = &preset.gainDelay;
    paramEnvelope  = &preset.envelope;
    paramTimbre    = &preset.timbre;

    tabMain->setNum(value);
    tabMain->setID(preset.name);
    tabMain->setNotes(preset.notes);

    String dbDir = systemConfig->getDBdir();
    dataOriginal->applyLoadFiles(dbDir, &preset.impulseResponses);

    for (int i = 0; i < 4; i++)
    {
        tabMain->setComboText(i, presetManager->getList(i));
        int index = presetManager->getCategoryIndex(value, i);
        tabMain->setComboIndex(i, index);
    }

    ParamGainDelay pMin, pMax;

    pMin.initialGap = 0.0;
    pMax.initialGap = 100.0;

    pMin.length = 0.0;
    pMax.length = (float)dataOriginal->getDataLen() / 
                  (float)dataOriginal->getSampleRate();

    if (paramGainDelay->length < 0.0)
        paramGainDelay->length = pMax.length;

    pMin.preDelay = -100.0;
    pMax.preDelay =  100.0;

    pMin.dryGain = -120.0;
    pMax.dryGain =    0.0;

    pMin.wetGain = -40.0;
    pMax.wetGain =  40.0;

    pMin.masterGain = -40.0;
    pMax.masterGain =  40.0;

    tabMain->setGainDelayRange(&pMin, paramGainDelay, &pMax);

    if (pMax.length - paramGainDelay->length < 0.0005)
        paramGainDelay->length = -1.0;
    enabledGainDelay = false;
    if (fabs(paramGainDelay->initialGap) > 0.05)
        enabledGainDelay = true;
    if (paramGainDelay->length           >= 0.0)
        enabledGainDelay = true;
    if (fabs(paramGainDelay->preDelay)   > 0.05)
        enabledGainDelay = true;
    if (fabs(paramGainDelay->dryGain)    > 0.05)
        enabledGainDelay = true;
    if (fabs(paramGainDelay->wetGain)    > 0.05)
        enabledGainDelay = true;
    if (fabs(paramGainDelay->masterGain) > 0.05)
        enabledGainDelay = true;

    tabMain->setEnvelope(paramEnvelope);
    enabledEnvelope = false;
    if (fabs(paramEnvelope->db0ms)   > 0.05)
        enabledEnvelope = true;
    if (fabs(paramEnvelope->db20ms)  > 0.05)
        enabledEnvelope = true;
    if (fabs(paramEnvelope->db120ms) > 0.05)
        enabledEnvelope = true;
    if (fabs(paramEnvelope->dbENDms) > 0.05)
        enabledEnvelope = true;

    tabTimbre->setTimbre(paramTimbre);
    enabledTimbre = false;
    for (int i = 0; enabledTimbre == false && i < paramTimbre->num; i++)
    {
        if (paramTimbre->data[i] != 0.0)
            enabledTimbre = true;
    }

    updateOriginal();
    float fvalue = (float(value) - 1.0) / 255.0;
    audioPlugin->setParameter(0, fvalue);
}


void MasterAndCommander::onValueChangedGainDelay(ParamGainDelay *param)
{
    changeFilter = true;
    print(JUCE_T("MasterAndCommander::onValueChangedGainDelay() called \n("));
    printf("Master#  Gain/Delay values : %5.1f %6.3f %6.1f %5.1f %5.1f %5.1f\n",
           param->initialGap, param->length, param->preDelay,
           param->dryGain, param->wetGain, param->masterGain);

    paramGainDelay->initialGap = param->initialGap;
    paramGainDelay->length     = param->length;
    paramGainDelay->preDelay   = param->preDelay;
    paramGainDelay->dryGain    = param->dryGain;
    paramGainDelay->wetGain    = param->wetGain;
    paramGainDelay->masterGain = param->masterGain;

    float maxLength = (float)dataOriginal->getDataLen() /
                      (float)dataOriginal->getSampleRate();

    if (maxLength - paramGainDelay->length < 0.001)
        paramGainDelay->length = -1.0;

    enabledGainDelay = false;
    if (fabs(paramGainDelay->initialGap) > 0.05)
        enabledGainDelay = true;
    if (paramGainDelay->length           >= 0.0)
        enabledGainDelay = true;
    if (fabs(paramGainDelay->preDelay)   > 0.05)
        enabledGainDelay = true;
    if (fabs(paramGainDelay->dryGain)    > 0.05)
        enabledGainDelay = true;
    if (fabs(paramGainDelay->wetGain)    > 0.05)
        enabledGainDelay = true;
    if (fabs(paramGainDelay->masterGain) > 0.05)
        enabledGainDelay = true;

    presetManager->setGainDelay(currentPreset, *paramGainDelay);
    updateGainDelay();
}


void MasterAndCommander::onValueChangedEnvelope(ParamEnvelope *param)
{
    changeFilter = true;
    print(JUCE_T("MasterAndCommander::onValueChangedEnvelope() called \n("));
    printf("Master#  Envelope values : %7.2f %7.2f %7.2f %7.2f\n",
           param->db0ms, param->db20ms, param->db120ms, param->dbENDms);

    paramEnvelope->db0ms   = param->db0ms;
    paramEnvelope->db20ms  = param->db20ms;
    paramEnvelope->db120ms = param->db120ms;
    paramEnvelope->dbENDms = param->dbENDms;

    enabledEnvelope = false;
    if (fabs(paramEnvelope->db0ms)   > 0.05)
        enabledEnvelope = true;
    if (fabs(paramEnvelope->db20ms)  > 0.05)
        enabledEnvelope = true;
    if (fabs(paramEnvelope->db120ms) > 0.05)
        enabledEnvelope = true;
    if (fabs(paramEnvelope->dbENDms) > 0.05)
        enabledEnvelope = true;

    presetManager->setEnvelope(currentPreset, *param);
    updateEnvelope();
}


////////////////////////////////////////////////////////////////
//
//    "Modulation" tab methods
//

void MasterAndCommander::registerTabModulation(TabModulation *tab)
{
    tabModulation = tab;
}


////////////////////////////////////////////////////////////////
//
//    "Timbre" tab methods
//

void MasterAndCommander::registerTabTimbre(TabTimbre *tab)
{
    tabTimbre = tab;
}


void MasterAndCommander::onValueChangedTimbre(ParamTimbre *param)
{
    changeFilter = true;
    print(JUCE_T("MasterAndCommander::onValueChangedTimbre() called \n("));
    enabledTimbre = false;
    for (int i = 0; enabledTimbre == false && i < param->num; i++)
    {
        if (param->data[i] != 0.0)
            enabledTimbre = true;
    }

    paramTimbre->set(param);

    presetManager->setTimbre(currentPreset, *param);
    updateTimbre();
}


////////////////////////////////////////////////////////////////
//
//    "Preset Editor" tab methods
//

void MasterAndCommander::registerTabPresetEditor(TabPresetEditor *tab)
{
    tabPresetEditor = tab;
    tab->setPresetManager(presetManager);
}


void MasterAndCommander::setPresetDB(const std::vector<ParamPreset> & newPresetDB,
                                     bool updateManager)
{
    //FIXME: What shall we do with currentPreset?
    if (updateManager == true)
        presetManager->setPresetDB(newPresetDB);
    if (currentPreset > presetManager->getNumPresets())
        currentPreset = 1;

    // apply changes
    onValueChangedPresetNum(currentPreset, true);
}


void MasterAndCommander::savePresetDB(const std::vector<ParamPreset> & newPresetDB)
{
    setPresetDB(newPresetDB);
    presetManager->save();
}


void MasterAndCommander::savePresetDBas(const std::vector<ParamPreset> & newPresetDB,
                                        const String & presetFile)
{
    setPresetDB(newPresetDB);
    presetManager->saveAs(presetFile);
}


////////////////////////////////////////////////////////////////
//
//    "Preferences" tab methods
//

void MasterAndCommander::registerTabPreferences(TabPreferences *tab)
{
    tabPreferences = tab;
    tabPreferences->setPreferences(paramPreferences);
}


void MasterAndCommander::onValueChangedPreferences(const ParamPreferences & param)
{
    paramPreferences = param;
    systemConfig->setPreferences(param);
}


////////////////////////////////////////////////////////////////
//
//    "About" tab methods
//

void MasterAndCommander::registerTabAbout(TabAbout *tab)
{
    tabAbout = tab;
}


////////////////////////////////////////////////////////////////
//
//    "IRPlot" component methods
//
void MasterAndCommander::registerIRPlot(IRPlot *plot)
{
    irPlot = plot;
}


////////////////////////////////////////////////////////////////
//
//    "FreqPlot" component methods
//
void MasterAndCommander::registerFreqPlot(FreqPlot *plot)
{
    freqPlot = plot;
}


////////////////////////////////////////////////////////////////
//
//    private methods
//

void MasterAndCommander::updateOriginal(void)
{
    SampleData *dataCurrent = 0;

    updateTimbre();
}


void MasterAndCommander::updateTimbre(void)
{
    SampleData *dataCurrent = 0;

    dataCurrent = dataOriginal;

    printf("enabledTimbre = %d\n", enabledTimbre);
    if (enabledTimbre)
    {
        // dataCurrent -> dataTimbre
        int filterLen = tabTimbre->getFilterLen();
        float *filter = tabTimbre->getFilter();
        dataTimbre->applyTimbre(dataCurrent, filterLen, filter);
    }

    updateModulation();
}


void MasterAndCommander::updateModulation(void)
{
    SampleData *dataCurrent = 0;

    if (enabledTimbre)
        dataCurrent = dataTimbre;
    else dataCurrent = dataOriginal;

    printf("enabledModulation = %d\n", enabledModulation);
    if (enabledModulation)
    {
        // FIXME: add modulation code
        // dataCurrent -> dataModulation
    }
    updateGainDelay();
}


void MasterAndCommander::updateGainDelay(void)
{
    SampleData *dataCurrent = 0;

    if (enabledModulation)
        dataCurrent = dataModulation;
    else if (enabledTimbre)
        dataCurrent = dataTimbre;
    else dataCurrent = dataOriginal;

    printf("enabledGainDelay = %d\n", enabledGainDelay);
    if (enabledGainDelay)
    {
        // dataCurrent -> dataGainDelay
        dataGainDelay->applyGainDelay(dataCurrent, paramGainDelay);
    }
    updateEnvelope();
}


void MasterAndCommander::updateEnvelope(void)
{
    SampleData *dataCurrent = 0;

    if (enabledGainDelay)
        dataCurrent = dataGainDelay;
    else if (enabledModulation)
        dataCurrent = dataModulation;
    else if (enabledTimbre)
        dataCurrent = dataTimbre;
    else dataCurrent = dataOriginal;

    printf("enabledEnvelope = %d\n", enabledEnvelope);
    if (enabledEnvelope)
    {
        // dataCurrent -> dataEnvelope
        dataEnvelope->applyEnvelope(dataCurrent, paramEnvelope);
    }
    updateFinal();
}


void MasterAndCommander::updateFinal(void)
{
    SampleData *dataCurrent = 0;

    if (enabledEnvelope)
        dataCurrent = dataEnvelope;
    else if (enabledGainDelay)
        dataCurrent = dataGainDelay;
    else if (enabledModulation)
        dataCurrent = dataModulation;
    else if (enabledTimbre)
        dataCurrent = dataTimbre;
    else dataCurrent = dataOriginal;

    irPlot->samples2plot(dataCurrent->getData(0),
                         dataCurrent->getData(1),
                         dataCurrent->getData(2),
                         dataCurrent->getData(3),
                         dataCurrent->getDataLen(),
                         dataCurrent->getSampleRate());

    if (changeFilter == true)
    {
        changeFilter = false;
        audioPlugin->setNewFilterSet(dataCurrent);
    }
}
