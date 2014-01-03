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


#ifndef __PRESETMANAGER_H__
#define __PRESETMANAGER_H__


#include "juce_amalgamated.h"
#include "ParamCategory.h"
#include "ParamEnvelope.h"
#include "ParamGainDelay.h"
#include "ParamImpulseResponses.h"
#include "ParamPreset.h"
#include "ParamTimbre.h"
#include "TextList.h"
#include <vector>


class PresetManager
{
public:
    PresetManager();
    PresetManager(int num);
    ~PresetManager();

    int getNumPresets(void);
    int getCurrentPresetNum(void);
    void setCurrentPresetNum(int num);
    int getDefaultPresetNum(void);
    void setDefaultPresetNum(int num);
    const std::vector<ParamPreset> & getPresetDB(void);
    void setPresetDB(const std::vector<ParamPreset> & newPresetDB);
    int readFile(const String &presetFile);
    int save(void);
    int saveAs(const String &presetFile);
    int parseRoot(XmlElement *element);
    const ParamPreset & parsePreset(XmlElement *element);
    const ParamImpulseResponses & parseImpulseResponses(XmlElement *element);
    const ParamCategory & parseCategory(XmlElement *element);
    const ParamEnvelope & parseParamEnvelope(XmlElement *element);
    const ParamGainDelay & parseParamGainDelay(XmlElement *element);
    const ParamTimbre & parseParamTimbre(XmlElement *element);

    const ParamPreset           & getPreset(int num);
    const String                & getName(int num);
    const ParamImpulseResponses & getImpulseResponses(int num);
    const ParamCategory         & getCategory(int num);
    const ParamTimbre           & getTimbre(int num);
    const ParamGainDelay        & getGainDelay(int num);
    const ParamEnvelope         & getEnvelope(int num);
    const String                & getNotes(int num);

    void setPreset           (int num, const ParamPreset & param);
    void setImpulseResponses (int num, const ParamImpulseResponses & param);
    void setCategory         (int num, const ParamCategory & param);
    void setEnvelope         (int num, const ParamEnvelope & param);
    void setGainDelay        (int num, const ParamGainDelay & param);
    void setTimbre           (int num, const ParamTimbre & param);

    const std::vector<String> & getList(int category);
    int getCategoryIndex(int num, int category);
    int getSimilarPreset(int current_preset, int cat, int cat_index);

    XmlElement* paramPresetToXML           (const ParamPreset           & param, int num);
    XmlElement* paramImpulseResponsesToXML (const ParamImpulseResponses & param);
    XmlElement* paramCategoryToXML         (const ParamCategory         & param);
    XmlElement* paramTimbreToXML           (const ParamTimbre           & param);
    XmlElement* paramGainDelayToXML        (const ParamGainDelay        & param);
    XmlElement* paramEnvelopeToXML         (const ParamEnvelope         & param);

private:
    const String & getSubText(XmlElement *element);

    String filename;
    String retSubText;
    XmlDocument *xmlDoc;
    XmlElement *xmlRoot;
    int maxPresets;
    std::vector<ParamPreset> preset;
    int numPresets;
    int currentPresetNum;
    int defaultPresetNum;

    ParamPreset           emptyPreset;
    ParamImpulseResponses emptyImpulseResponses;
    ParamCategory         emptyCategory;
    ParamEnvelope         emptyEnvelope;
    ParamGainDelay        emptyGainDelay;
    ParamTimbre           emptyTimbre;

    ParamPreset           retPreset;
    ParamImpulseResponses retImpulseResponses;
    ParamCategory         retCategory;
    ParamEnvelope         retEnvelope;
    ParamGainDelay        retGainDelay;
    ParamTimbre           retTimbre;

    TextList vectorCat1;
    TextList vectorCat2;
    TextList vectorCat3;
    TextList vectorCat4;
    TextList vectorEmpty;
    int catIndex[4];
};


#endif   // __PRESETMANAGER_H__
