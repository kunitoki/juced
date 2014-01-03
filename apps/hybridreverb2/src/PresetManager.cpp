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


#include "PresetManager.h"
#include "gui/TabTimbre.h"
#include <math.h>
#include <iostream>


PresetManager::PresetManager()
    : xmlDoc(0),
      xmlRoot(0),
      maxPresets(256),
      numPresets(0),
      currentPresetNum(1),
      defaultPresetNum(1)
{
    filename = String::empty;
    for (int i = 0; i < maxPresets; i++)
        preset.push_back( ParamPreset() );
}

PresetManager::PresetManager(int num)
    : xmlDoc(0),
      xmlRoot(0),
      maxPresets(num),
      numPresets(0),
      defaultPresetNum(0)
{
    for (int i = 0; i < 7; i++)
        preset.push_back( ParamPreset() );
}

PresetManager::~PresetManager()
{
    preset.clear();
    if (xmlDoc != 0)
    {
        delete xmlDoc;
        xmlDoc = 0;
    }
    if (xmlRoot != 0)
    {
        delete xmlRoot;
        xmlRoot = 0;
    }
}


////////////////////////////////////////////////////////////////
//
//    public methods
//

int PresetManager::getNumPresets(void)
{
    return preset.size();
}


int PresetManager::getCurrentPresetNum(void)
{
    return currentPresetNum;
}


void PresetManager::setCurrentPresetNum(int num)
{
    currentPresetNum = num;
}


int PresetManager::getDefaultPresetNum(void)
{
    return defaultPresetNum;
}


void PresetManager::setDefaultPresetNum(int num)
{
    defaultPresetNum = num;
}


const std::vector<ParamPreset> & PresetManager::getPresetDB(void)
{
    return preset;
}


void PresetManager::setPresetDB(const std::vector<ParamPreset> & newPresetDB)
{
    preset.clear();
    preset = newPresetDB;
    numPresets = preset.size();

    // reorganize "category index" for selection via the combo boxes
    vectorCat1.clear();
    vectorCat2.clear();
    vectorCat3.clear();
    vectorCat4.clear();
    for (int i = 0; i < numPresets; i++)
    {
        ParamCategory cat = preset[i].category;
        preset[i].catIndex[0] = vectorCat1.getPos(cat.cat_1);
        preset[i].catIndex[1] = vectorCat2.getPos(cat.cat_2);
        preset[i].catIndex[2] = vectorCat3.getPos(cat.cat_3);
        preset[i].catIndex[3] = vectorCat4.getPos(cat.cat_4);
    }
}


int PresetManager::readFile(const String &presetFile)
{
    File f(presetFile);
    if (f.existsAsFile() == false)
    {
        String message = JUCE_T("Error: Preset file \"") +
                         presetFile +
                         JUCE_T("\" does not exist!");
        AlertWindow::showMessageBox(AlertWindow::WarningIcon,
                                    JUCE_T("Error"), message);
        return -1;
    }
    filename = presetFile;

    xmlDoc = new XmlDocument(f);
    xmlRoot = xmlDoc->getDocumentElement();

    if (xmlRoot == 0)
    {
        String message = JUCE_T("Syntax error in preset file \"") +
                         presetFile +
                         JUCE_T("\" :\n") +
                         xmlDoc->getLastParseError();
        AlertWindow::showMessageBox(AlertWindow::WarningIcon,
                                    JUCE_T("Error"), message);
        if (xmlDoc != 0)
        {
            delete xmlDoc;
            xmlDoc = 0;
        }
        return -1;
    }

    preset.clear();
    defaultPresetNum = parseRoot(xmlRoot);
    numPresets = preset.size();

    return defaultPresetNum;
}


int PresetManager::save(void)
{
    XmlElement xmlRoot("root");

    XmlElement* xmlDefault = new XmlElement("default");
    XmlElement* textElement = XmlElement::createTextElement(String(defaultPresetNum));
    xmlDefault->addChildElement(textElement);
    xmlRoot.addChildElement(xmlDefault);

    for (int i = 0; i < preset.size(); i++)
    {
        XmlElement* xmlPreset = paramPresetToXML(preset[i], i + 1);
        xmlRoot.addChildElement(xmlPreset);
    }

    String xmlDoc = xmlRoot.createDocument(String::empty);
    File file(filename);
    if (file.hasWriteAccess() == false)
    {
        String message = JUCE_T("Preset file \"") +
                         filename +
                         JUCE_T("\" is not writable.");
        AlertWindow::showMessageBox(AlertWindow::WarningIcon,
                                    JUCE_T("Error"), message);
        return -1;
    }
    file.replaceWithText(xmlDoc);

    return 0;
}


int PresetManager::saveAs(const String &presetFile)
{
    filename = presetFile;
    return save();
}


int PresetManager::parseRoot(XmlElement *element)
{
    int ret = 1;

    if (numPresets > 0)
    {
        preset.clear();
        numPresets = 0;
    }

    forEachXmlChildElement(*element, child)
    {
        if (numPresets < maxPresets && child->hasTagName(JUCE_T("preset")))
        {
            preset.push_back(ParamPreset());
            for (int i = 0; i < 4; i++)
                catIndex[i] = -1;
            preset.at(numPresets) = parsePreset(child);
            for (int i = 0; i < 4; i++)
                preset.at(numPresets).catIndex[i] = catIndex[i];
            numPresets++;
        }
        else if (child->hasTagName(JUCE_T("default")))
        {
            String text = getSubText(child);
            ret = text.getIntValue();
        }
    }

    if (numPresets <= 0)
        return -1;

    return ret;
}


const ParamPreset & PresetManager::parsePreset(XmlElement *element)
{
    retPreset = emptyPreset;

    forEachXmlChildElement(*element, child)
    {
        if (child->hasTagName(JUCE_T("name")))
            retPreset.name = getSubText(child);
        else if (child->hasTagName(JUCE_T("impulse_responses")))
            retPreset.impulseResponses = parseImpulseResponses(child);
        else if (child->hasTagName(JUCE_T("category")))
            retPreset.category = parseCategory(child);
        else if (child->hasTagName(JUCE_T("param_envelope")))
            retPreset.envelope = parseParamEnvelope(child);
        else if (child->hasTagName(JUCE_T("param_gain_delay")))
            retPreset.gainDelay = parseParamGainDelay(child);
        else if (child->hasTagName(JUCE_T("param_timbre")))
            retPreset.timbre = parseParamTimbre(child);
        else if (child->hasTagName(JUCE_T("notes")))
            retPreset.notes = getSubText(child);
    }

    return retPreset;
}


const ParamImpulseResponses & PresetManager::parseImpulseResponses(XmlElement *element)
{
    retImpulseResponses = emptyImpulseResponses;

    forEachXmlChildElement(*element, child)
    {
        if (child->hasTagName(JUCE_T("ll")))
            retImpulseResponses.ll = getSubText(child);
        else if (child->hasTagName(JUCE_T("lr")))
            retImpulseResponses.lr = getSubText(child);
        else if (child->hasTagName(JUCE_T("rl")))
            retImpulseResponses.rl = getSubText(child);
        else if (child->hasTagName(JUCE_T("rr")))
            retImpulseResponses.rr = getSubText(child);
    }

    return retImpulseResponses;
}


const ParamCategory & PresetManager::parseCategory(XmlElement *element)
{
    retCategory = emptyCategory;

    forEachXmlChildElement(*element, child)
    {
        if (child->hasTagName(JUCE_T("cat_1")))
        {
            retCategory.cat_1 = getSubText(child);
            catIndex[0] = vectorCat1.getPos(retCategory.cat_1);
        }
        else if (child->hasTagName(JUCE_T("cat_2")))
        {
            retCategory.cat_2 = getSubText(child);
            catIndex[1] = vectorCat2.getPos(retCategory.cat_2);
        }
        else if (child->hasTagName(JUCE_T("cat_3")))
        {
            retCategory.cat_3 = getSubText(child);
            catIndex[2] = vectorCat3.getPos(retCategory.cat_3);
        }
        else if (child->hasTagName(JUCE_T("cat_4")))
        {
            retCategory.cat_4 = getSubText(child);
            catIndex[3] = vectorCat4.getPos(retCategory.cat_4);
        }
    }

    return retCategory;
}


const ParamEnvelope & PresetManager::parseParamEnvelope(XmlElement *element)
{
    retEnvelope = emptyEnvelope;
    int counter = 0;

    forEachXmlChildElement(*element, child)
    {
        if (child->hasTagName(JUCE_T("gain")))
        {
            String text = getSubText(child);
            switch (counter) {
            case 0:
                retEnvelope.db0ms = text.getFloatValue();
                break;
            case 1:
                retEnvelope.db20ms = text.getFloatValue();
                break;
            case 2:
                retEnvelope.db120ms = text.getFloatValue();
                break;
            case 3:
                retEnvelope.dbENDms = text.getFloatValue();
                break;
            }
            counter++;
        }
    }

    return retEnvelope;
}


const ParamGainDelay & PresetManager::parseParamGainDelay(XmlElement *element)
{
    retGainDelay = emptyGainDelay;

    forEachXmlChildElement(*element, child)
    {
        String text = getSubText(child);
        float value = text.getFloatValue();
        if (child->hasTagName(JUCE_T("initial_gap")))
            retGainDelay.initialGap = value;
        else if (child->hasTagName(JUCE_T("length")))
            retGainDelay.length = value;
        else if (child->hasTagName(JUCE_T("pre_delay")))
            retGainDelay.preDelay = value;
        else if (child->hasTagName(JUCE_T("dry_gain")))
            retGainDelay.dryGain = value;
        else if (child->hasTagName(JUCE_T("wet_gain")))
            retGainDelay.wetGain = value;
        else if (child->hasTagName(JUCE_T("master_gain")))
            retGainDelay.masterGain = value;
    }

    return retGainDelay;
}


const ParamTimbre & PresetManager::parseParamTimbre(XmlElement *element)
{
    retTimbre = emptyTimbre;
    int counter = 0;

    forEachXmlChildElement(*element, child)
    {
        String text = getSubText(child);
        float value = text.getFloatValue();
        if (child->hasTagName(JUCE_T("gain")) && counter < retTimbre.num)
        {
            retTimbre.data[counter] = value;
            counter++;
        }
        else if (child->hasTagName(JUCE_T("smooth")))
            retTimbre.smooth = value;
    }

    return retTimbre;
}


const ParamPreset & PresetManager::getPreset(int num)
{
    return preset.at(num - 1);
}


const String & PresetManager::getName(int num)
{
    return preset.at(num - 1).name;
}


const ParamImpulseResponses & PresetManager::getImpulseResponses(int num)
{
    return preset.at(num - 1).impulseResponses;
}


const ParamCategory & PresetManager::getCategory(int num)
{
    return preset.at(num - 1).category;
}


const ParamTimbre & PresetManager::getTimbre(int num)
{
    return preset.at(num - 1).timbre;
}


const ParamGainDelay & PresetManager::getGainDelay(int num)
{
    return preset.at(num - 1).gainDelay;
}


const ParamEnvelope & PresetManager::getEnvelope(int num)
{
    return preset.at(num - 1).envelope;
}


const String & PresetManager::getNotes(int num)
{
    return preset.at(num - 1).notes;
}


void PresetManager::setPreset(int num, const ParamPreset & param)
{
    preset.at(num - 1) = param;
}


void PresetManager::setImpulseResponses(int num, const ParamImpulseResponses & param)
{
    preset.at(num - 1).impulseResponses = param;
}


void PresetManager::setCategory(int num, const ParamCategory & param)
{
    preset.at(num - 1).category = param;
}


void PresetManager::setEnvelope(int num, const ParamEnvelope & param)
{
    preset.at(num - 1).envelope = param;
}


void PresetManager::setGainDelay(int num, const ParamGainDelay & param)
{
    preset.at(num - 1).gainDelay = param;
}


void PresetManager::setTimbre(int num, const ParamTimbre & param)
{
    preset.at(num - 1).timbre = param;
}


const std::vector<String> & PresetManager::getList(int category)
{
    switch (category) {
    case 0:
        return vectorCat1.getList();
    case 1:
        return vectorCat2.getList();
    case 2:
        return vectorCat3.getList();
    case 3:
        return vectorCat4.getList();
    }
    return vectorEmpty.getList();
}


int PresetManager::getCategoryIndex(int num, int category)
{
    return preset.at(num - 1).catIndex[category];
}


int PresetManager::getSimilarPreset(int current_preset, int cat, int cat_index)
{
    int catIndex_wish[4];
    double closest_distance = 1e16;
    int best_preset = 0;
    double penalty[4];

    penalty[3] = 1.0;
    penalty[2] = numPresets;
    penalty[1] = numPresets * numPresets;
    penalty[0] = numPresets * numPresets * numPresets;

    for (int i = 0; i < 4; i++)
        catIndex_wish[i] = preset.at(current_preset - 1).catIndex[i];
    catIndex_wish[cat] = cat_index;

    for (int p = 0; p < numPresets; p++)
    {
        int *loop_catIndex = preset.at(p).catIndex;
        if (loop_catIndex[cat] == cat_index)
        {
            double distance = 0.0;
            for (int c = 0; c < 4; c++)
                distance += abs(catIndex_wish[c] - loop_catIndex[c]) * penalty[c];
            if (distance < closest_distance)
            {
                best_preset = p;
                closest_distance = distance;
            }
        }
    }

    return best_preset + 1;
}


XmlElement* PresetManager::paramPresetToXML(const ParamPreset & param, int num)
{
    XmlElement* xmlPreset = new XmlElement("preset");

    XmlElement* xmlNum = new XmlElement("num");
    XmlElement* textElement = XmlElement::createTextElement(String(num));
    xmlNum->addChildElement(textElement);
    xmlPreset->addChildElement(xmlNum);

    XmlElement* xmlName = new XmlElement("name");
    textElement = XmlElement::createTextElement(param.name);
    xmlName->addChildElement(textElement);
    xmlPreset->addChildElement(xmlName);

    XmlElement* xmlIRs = paramImpulseResponsesToXML(param.impulseResponses);
    if (xmlIRs != 0)
        xmlPreset->addChildElement(xmlIRs);

    XmlElement* xmlCategory = paramCategoryToXML(param.category);
    if (xmlCategory != 0)
        xmlPreset->addChildElement(xmlCategory);

    XmlElement* xmlTimbre = paramTimbreToXML(param.timbre);
    if (xmlTimbre != 0)
        xmlPreset->addChildElement(xmlTimbre);

    XmlElement* xmlGainDelay = paramGainDelayToXML(param.gainDelay);
    if (xmlGainDelay != 0)
        xmlPreset->addChildElement(xmlGainDelay);

    XmlElement* xmlEnvelope = paramEnvelopeToXML(param.envelope);
    if (xmlEnvelope != 0)
        xmlPreset->addChildElement(xmlEnvelope);

    XmlElement* xmlNotes = new XmlElement("notes");
    textElement = XmlElement::createTextElement(param.notes);
    xmlNotes->addChildElement(textElement);
    xmlPreset->addChildElement(xmlNotes);

    return xmlPreset;
}


XmlElement* PresetManager::paramImpulseResponsesToXML(const ParamImpulseResponses & param)
{
    if (param.ll == String::empty &&
        param.lr == String::empty &&
        param.rl == String::empty &&
        param.rr == String::empty)
    return 0;

    XmlElement* xmlIRs = new XmlElement("impulse_responses");

    if (param.ll != String::empty)
    {
        XmlElement* xmlWav = new XmlElement("ll");
        XmlElement* textElement = XmlElement::createTextElement(param.ll);
        xmlWav->addChildElement(textElement);
        xmlIRs->addChildElement(xmlWav);
    }

    if (param.lr != String::empty)
    {
        XmlElement* xmlWav = new XmlElement("lr");
        XmlElement* textElement = XmlElement::createTextElement(param.lr);
        xmlWav->addChildElement(textElement);
        xmlIRs->addChildElement(xmlWav);
    }

    if (param.rl != String::empty)
    {
        XmlElement* xmlWav = new XmlElement("rl");
        XmlElement* textElement = XmlElement::createTextElement(param.rl);
        xmlWav->addChildElement(textElement);
        xmlIRs->addChildElement(xmlWav);
    }

    if (param.rr != String::empty)
    {
        XmlElement* xmlWav = new XmlElement("rr");
        XmlElement* textElement = XmlElement::createTextElement(param.rr);
        xmlWav->addChildElement(textElement);
        xmlIRs->addChildElement(xmlWav);
    }

    return xmlIRs;
}


XmlElement* PresetManager::paramCategoryToXML(const ParamCategory & param)
{
    if (param.cat_1 == String::empty &&
        param.cat_2 == String::empty &&
        param.cat_3 == String::empty &&
        param.cat_4 == String::empty)
    return 0;

    XmlElement* xmlCategory = new XmlElement("category");

    if (param.cat_1 != String::empty)
    {
        XmlElement* xmlWav = new XmlElement("cat_1");
        XmlElement* textElement = XmlElement::createTextElement(param.cat_1);
        xmlWav->addChildElement(textElement);
        xmlCategory->addChildElement(xmlWav);
    }

    if (param.cat_2 != String::empty)
    {
        XmlElement* xmlWav = new XmlElement("cat_2");
        XmlElement* textElement = XmlElement::createTextElement(param.cat_2);
        xmlWav->addChildElement(textElement);
        xmlCategory->addChildElement(xmlWav);
    }

    if (param.cat_3 != String::empty)
    {
        XmlElement* xmlWav = new XmlElement("cat_3");
        XmlElement* textElement = XmlElement::createTextElement(param.cat_3);
        xmlWav->addChildElement(textElement);
        xmlCategory->addChildElement(xmlWav);
    }

    if (param.cat_4 != String::empty)
    {
        XmlElement* xmlWav = new XmlElement("cat_4");
        XmlElement* textElement = XmlElement::createTextElement(param.cat_4);
        xmlWav->addChildElement(textElement);
        xmlCategory->addChildElement(xmlWav);
    }

    return xmlCategory;
}


XmlElement* PresetManager::paramTimbreToXML(const ParamTimbre & param)
{
    bool enabledTimbre = false;
    for (int i = 0; enabledTimbre == false && i < param.num; i++)
    {
        if (param.data[i] != 0.0)
            enabledTimbre = true;
    }
    if (enabledTimbre == false)
        return 0;

    XmlElement* xmlTimbre = new XmlElement("param_timbre");

    String text = String(param.smooth);
    XmlElement* xmlSmooth = new XmlElement("smooth");
    XmlElement* textElement = XmlElement::createTextElement(text);
    xmlSmooth->addChildElement(textElement);
    xmlTimbre->addChildElement(xmlSmooth);

    for (int i = 0; i < param.num; i++)
    {
        String text = String(param.data[i]);
        XmlElement* xmlGain = new XmlElement("gain");
        XmlElement* textElement = XmlElement::createTextElement(text);
        xmlGain->addChildElement(textElement);
        xmlTimbre->addChildElement(xmlGain);
    }

    return xmlTimbre;
}


XmlElement* PresetManager::paramGainDelayToXML(const ParamGainDelay & param)
{
    bool enabledGainDelay = false;
    if (fabs(param.initialGap) > 0.05)
        enabledGainDelay = true;
    if (param.length           >= 0.0)
        enabledGainDelay = true;
    if (fabs(param.preDelay)   > 0.05)
        enabledGainDelay = true;
    if (fabs(param.dryGain)    > 0.05)
        enabledGainDelay = true;
    if (fabs(param.wetGain)    > 0.05)
        enabledGainDelay = true;
    if (fabs(param.masterGain) > 0.05)
        enabledGainDelay = true;
    if (enabledGainDelay == false)
        return 0;

    XmlElement* xmlGainDelay = new XmlElement("param_gain_delay");

    if (fabs(param.initialGap) > 0.05)
    {
        String text = String(param.initialGap);
        XmlElement* xmlInitialGap = new XmlElement("initial_gap");
        XmlElement* textElement = XmlElement::createTextElement(text);
        xmlInitialGap->addChildElement(textElement);
        xmlGainDelay->addChildElement(xmlInitialGap);
    }

    if (param.length >= 0.0)
    {
        String text = String(param.length);
        XmlElement* xmlLength = new XmlElement("length");
        XmlElement* textElement = XmlElement::createTextElement(text);
        xmlLength->addChildElement(textElement);
        xmlGainDelay->addChildElement(xmlLength);
    }

    if (fabs(param.preDelay) > 0.05)
    {
        String text = String(param.preDelay);
        XmlElement* xmlPreDelay = new XmlElement("pre_delay");
        XmlElement* textElement = XmlElement::createTextElement(text);
        xmlPreDelay->addChildElement(textElement);
        xmlGainDelay->addChildElement(xmlPreDelay);
    }

    if (fabs(param.dryGain) > 0.05)
    {
        String text = String(param.dryGain);
        XmlElement* xmlDryGain = new XmlElement("dry_gain");
        XmlElement* textElement = XmlElement::createTextElement(text);
        xmlDryGain->addChildElement(textElement);
        xmlGainDelay->addChildElement(xmlDryGain);
    }

    if (fabs(param.wetGain) > 0.05)
    {
        String text = String(param.wetGain);
        XmlElement* xmlWetGain = new XmlElement("wet_gain");
        XmlElement* textElement = XmlElement::createTextElement(text);
        xmlWetGain->addChildElement(textElement);
        xmlGainDelay->addChildElement(xmlWetGain);
    }

    if (fabs(param.masterGain) > 0.05)
    {
        String text = String(param.masterGain);
        XmlElement* xmlMasterGain = new XmlElement("master_gain");
        XmlElement* textElement = XmlElement::createTextElement(text);
        xmlMasterGain->addChildElement(textElement);
        xmlGainDelay->addChildElement(xmlMasterGain);
    }

    return xmlGainDelay;
}


XmlElement* PresetManager::paramEnvelopeToXML(const ParamEnvelope & param)
{
    bool enabledEnvelope = false;
    if (fabs(param.db0ms)   > 0.05)
        enabledEnvelope = true;
    if (fabs(param.db20ms)  > 0.05)
        enabledEnvelope = true;
    if (fabs(param.db120ms) > 0.05)
        enabledEnvelope = true;
    if (fabs(param.dbENDms) > 0.05)
        enabledEnvelope = true;
    if (enabledEnvelope == false)
        return 0;

    XmlElement* xmlEnvelope = new XmlElement("param_envelope");

    String text = String(param.db0ms);
    XmlElement* xmlGain = new XmlElement("gain");
    XmlElement* textElement = XmlElement::createTextElement(text);
    xmlGain->addChildElement(textElement);
    xmlEnvelope->addChildElement(xmlGain);

    text = String(param.db20ms);
    xmlGain = new XmlElement("gain");
    textElement = XmlElement::createTextElement(text);
    xmlGain->addChildElement(textElement);
    xmlEnvelope->addChildElement(xmlGain);

    text = String(param.db120ms);
    xmlGain = new XmlElement("gain");
    textElement = XmlElement::createTextElement(text);
    xmlGain->addChildElement(textElement);
    xmlEnvelope->addChildElement(xmlGain);

    text = String(param.dbENDms);
    xmlGain = new XmlElement("gain");
    textElement = XmlElement::createTextElement(text);
    xmlGain->addChildElement(textElement);
    xmlEnvelope->addChildElement(xmlGain);

    return xmlEnvelope;
}


////////////////////////////////////////////////////////////////
//
//    private methods
//

const String & PresetManager::getSubText(XmlElement *element)
{
    forEachXmlChildElement(*element, child)
    {
        if (child->isTextElement())
        {
            retSubText = child->getText();
            return retSubText;
        }
    }
    retSubText = JUCE_T("");
    return retSubText;
}
