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


#include "SystemConfig.h"
#include "gui/TabTimbre.h"
#include <math.h>
#include <stdlib.h>


SystemConfig::SystemConfig()
    : basedir(String::empty),
      userdir(String::empty)
{
#ifdef _WINDOWS
    extractBasedirWindows();
    extractUserdirWindows();
    dbdir = basedir + String(JUCE_T("\\RIR_Database\\"));
#else
    extractBasedirUnix();
    extractUserdirUnix();
    dbdir = basedir + String(JUCE_T("/RIR_Database/"));
#endif

    File dstDir(userdir);
    if (dstDir.isDirectory() == false)
    {
        dstDir.createDirectory();
    }

#ifdef _WINDOWS
    String filenameDst = userdir + String(JUCE_T("\\preferences.xml"));
    String filenameSrc = basedir + String(JUCE_T("\\preferences.xml"));
#else
    String filenameDst = userdir + String(JUCE_T("/preferences.xml"));
    String filenameSrc = basedir + String(JUCE_T("/preferences.xml"));
#endif
    File preferencesDst(filenameDst);
    if (preferencesDst.existsAsFile() == false)
    {
        File preferencesSrc(filenameSrc);
        if (preferencesSrc.existsAsFile() == false)
        {
            String message = JUCE_T("Error: Preferences template file \"") +
                             filenameSrc +
                             JUCE_T("\" does not exist!");
            AlertWindow::showMessageBox(AlertWindow::WarningIcon,
                                        JUCE_T("Error"), message);
            return;
        }
        String content = preferencesSrc.loadFileAsString();
        preferencesDst.create();
        preferencesDst.replaceWithText(content);
    }

#ifdef _WINDOWS
    filenameDst = userdir + String(JUCE_T("\\HybridReverb2_presets.xml"));
    filenameSrc = basedir + String(JUCE_T("\\HybridReverb2_presets.xml"));
#else
    filenameDst = userdir + String(JUCE_T("/HybridReverb2_presets.xml"));
    filenameSrc = basedir + String(JUCE_T("/HybridReverb2_presets.xml"));
#endif
    File presetsDst(filenameDst);
    if (presetsDst.existsAsFile() == false)
    {
        File presetsSrc(filenameSrc);
        if (presetsSrc.existsAsFile() == false)
        {
            String message = JUCE_T("Error: Preset template file \"") +
                             filenameSrc +
                             JUCE_T("\" does not exist!");
            AlertWindow::showMessageBox(AlertWindow::WarningIcon,
                                        JUCE_T("Error"), message);
            return;
        }
        String content = presetsSrc.loadFileAsString();
        presetsDst.create();
        presetsDst.replaceWithText(content);
    }

    readPreferencesFile();
    readPartitionWisdomFile();
}

SystemConfig::~SystemConfig()
{
}


////////////////////////////////////////////////////////////////
//
//    public methods
//

const String & SystemConfig::getBasedir()
{
    return basedir;
}


const String & SystemConfig::getUserdir()
{
    return userdir;
}


const String & SystemConfig::getDBdir()
{
    return dbdir;
}


String SystemConfig::getPresetFilename()
{
    String filename = paramPreferences.presetFile;
    File *file = new File(filename);
    if (file->existsAsFile() == false)
    {
#ifdef _WINDOWS
        filename = userdir + String(JUCE_T("\\")) + paramPreferences.presetFile;
#else
        filename = userdir + String(JUCE_T("/")) + paramPreferences.presetFile;
#endif
        delete file;
        file = new File(filename);
    }
    if (file->existsAsFile() == false)
        filename = paramPreferences.presetFile;

    delete file;
    return filename;
}


const ParamPreferences & SystemConfig::getPreferences()
{
    return paramPreferences;
}


void SystemConfig::readPreferencesFile()
{
#ifdef _WINDOWS
    String filename = userdir + String(JUCE_T("\\preferences.xml"));
#else
    String filename = userdir + String(JUCE_T("/preferences.xml"));
#endif
    File preferencesFile(filename);
    if (preferencesFile.existsAsFile() == false)
    {
        String message = JUCE_T("Error: Preferences file \"") +
                         filename +
                         JUCE_T("\" does not exist!");
        AlertWindow::showMessageBox(AlertWindow::WarningIcon,
                                    JUCE_T("Error"), message);
        return;
    }

    XmlDocument xmlDoc(preferencesFile);
    XmlElement *element = xmlDoc.getDocumentElement();

    if (element == 0)
    {
        String message = JUCE_T("Syntax error in preferences file \"") +
                         filename +
                         JUCE_T("\" :\n") +
                         xmlDoc.getLastParseError();
        AlertWindow::showMessageBox(AlertWindow::WarningIcon,
                                    JUCE_T("Error"), message);
        return;
    }

    forEachXmlChildElement(*element, child)
    {
        if (child->hasTagName(JUCE_T("presetFile")))
        {
            paramPreferences.presetFile = getSubText(child);
        }
        else if (child->hasTagName(JUCE_T("sflen")))
        {
            String text = getSubText(child);
            paramPreferences.sflen = text.getIntValue();
        }
        else if (child->hasTagName(JUCE_T("strategy")))
        {
            String text = getSubText(child);
            paramPreferences.strategy = text.getIntValue();
        }
    }
}


void SystemConfig::setPreferences(const ParamPreferences & param)
{
    paramPreferences = param;

#ifdef _WINDOWS
    String filename = userdir + String(JUCE_T("\\preferences.xml"));
#else
    String filename = userdir + String(JUCE_T("/preferences.xml"));
#endif
    File preferencesFile(filename);
    if (preferencesFile.existsAsFile() == false)
    {
        String message = JUCE_T("Error: Preferences file \"") +
                         filename +
                         JUCE_T("\" does not exist!");
        AlertWindow::showMessageBox(AlertWindow::WarningIcon,
                                    JUCE_T("Error"), message);
        return;
    }
    String content = String(JUCE_T("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n")) +
                     String(JUCE_T("<preferences>\n")) +
                     String(JUCE_T("  <presetFile>")) + paramPreferences.presetFile       + String(JUCE_T("</presetFile>\n")) +
                     String(JUCE_T("  <sflen>"))      + String(paramPreferences.sflen)    + String(JUCE_T("</sflen>\n"))      +
                     String(JUCE_T("  <strategy>"))   + String(paramPreferences.strategy) + String(JUCE_T("</strategy>\n"))   +
                     String(JUCE_T("</preferences>"));
    preferencesFile.replaceWithText(content);
}


const ParamPartitionWisdom & SystemConfig::getPartitionWisdom()
{
    return paramPartitionWisdom;
}


void SystemConfig::readPartitionWisdomFile()
{
#ifdef _WINDOWS
    String filename = basedir + String(JUCE_T("\\partition_wisdom.xml"));
#else
    String filename = basedir + String(JUCE_T("/partition_wisdom.xml"));
#endif
    File partitionWisdomFile(filename);
    if (partitionWisdomFile.existsAsFile() == false)
    {
        String message = JUCE_T("Error: Partition wisdom file \"") +
                         filename +
                         JUCE_T("\" does not exist!");
        AlertWindow::showMessageBox(AlertWindow::WarningIcon,
                                    JUCE_T("Error"), message);
        return;
    }

    XmlDocument xmlDoc(partitionWisdomFile);
    XmlElement *element = xmlDoc.getDocumentElement();

    if (element == 0)
    {
        String message = JUCE_T("Syntax error in partition wisdom file \"") +
                         filename +
                         JUCE_T("\" :\n") +
                         xmlDoc.getLastParseError();
        AlertWindow::showMessageBox(AlertWindow::WarningIcon,
                                    JUCE_T("Error"), message);
        return;
    }

    int num_const = 0;
    int num_linear = 0;
    forEachXmlChildElement(*element, child)
    {
        if (child->hasTagName(JUCE_T("const")) &&
            num_const < NUM_PARTITIONWISDOM_ENTRIES)
        {
            String value = getSubText(child);
            paramPartitionWisdom.t_const[num_const] = value.getDoubleValue();
            num_const++;
        }
        else if (child->hasTagName(JUCE_T("linear")) &&
                 num_linear < NUM_PARTITIONWISDOM_ENTRIES)
        {
            String value = getSubText(child);
            paramPartitionWisdom.t_linear[num_linear] = value.getDoubleValue();
            num_linear++;
        }
    }
}


////////////////////////////////////////////////////////////////
//
//    private methods
//

#ifdef _WINDOWS

void SystemConfig::extractBasedirWindows()
{
    TCHAR *programmfiles;
    size_t len;
    _tdupenv_s(&programmfiles, &len, _T("ProgramFiles"));
    len = _tcslen(programmfiles) + _tcslen(_T("\\HybridReverb2")) + 1;
    TCHAR *defaultDir = new TCHAR[len];
    defaultDir[0] = '\0';
    _tcscat_s(defaultDir, len, programmfiles);
    _tcscat_s(defaultDir, len, _T("\\HybridReverb2"));
    const String regkey(JUCE_T("HKEY_LOCAL_MACHINE\\Software\\HybridReverb2\\BaseDir"));
	basedir = PlatformUtilities::getRegistryValue(regkey, defaultDir);
    delete[] defaultDir;
    delete[] programmfiles;
}


void SystemConfig::extractUserdirWindows()
{
    TCHAR *appdata;
    size_t len;
    _tdupenv_s(&appdata, &len, _T("APPDATA"));
    char *cs = new char[len + 1];
    for (unsigned int i = 0; i < len; i++)
    cs[i] = (CHAR)appdata[i];
    cs[len] = '\0';
    userdir = String(cs) + _T("\\HybridReverb2");
    delete[] cs;
    delete[] appdata;
}

#else

void SystemConfig::extractBasedirUnix()
{
    String configFilename = JUCE_T("/etc/HybridReverb2/HybridReverb2.conf");

    File configFile(configFilename);
    if (configFile.existsAsFile() == false)
    {
        String message = JUCE_T("Error: Global configuration file \"") +
                         configFilename +
                         JUCE_T("\" does not exist!");
        AlertWindow::showMessageBox(AlertWindow::WarningIcon,
                                    JUCE_T("Error"), message);
        return;
    }

    FileInputStream configStream(configFile);
    String configLine;
    while (configStream.isExhausted() == false)
    {
        configLine = configStream.readNextLine();
        int pos = configLine.indexOfChar(JUCE_T('#'));
        if (pos >= 0)
            configLine = configLine.substring(0, pos);
        pos = configLine.indexOfChar(JUCE_T('='));
        if (pos >= 0)
        {
            String variable = configLine.substring(0, pos).trim();
            String value = configLine.substring(pos + 1, configLine.length());
            if (variable == JUCE_T("basedir") || variable == JUCE_T("BaseDir"))
                basedir = value.trim();
        }
    }
}


void SystemConfig::extractUserdirUnix()
{
    userdir = String(getenv("HOME")) + JUCE_T("/.HybridReverb2");
}

#endif


String SystemConfig::getSubText(XmlElement *element)
{
    forEachXmlChildElement(*element, child)
    {
        if (child->isTextElement())
        {
            return child->getText();
        }
    }
    return String::empty;
}
