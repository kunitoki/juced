/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2007 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2007 by Julian Storer.

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
*/

#include "BasePlugin.h"

//==============================================================================
int32 BasePlugin::globalUniqueCounter = 1;

//==============================================================================
BasePlugin::BasePlugin ()
    : PropertySet (false), // do not ignore case of key names
      uniqueHash (BasePlugin::globalUniqueCounter++),
      parentHost (0),
      mutedOutput (false),
      bypassOutput (false),
      outputGain (1.0f),
      currentOutputGain (1.0f)
{
    keyboardState.reset();

    // default
    setValue (PROP_MIXERPEAK, 1);
    setValue (PROP_MIXERMETERON, 1);
    
    // must we set this here ?
    setParametersChangeChecksPerSecond (50);
}

BasePlugin::~BasePlugin ()
{
}

//==============================================================================
void BasePlugin::savePropertiesToXml (XmlElement* xml)
{
    xml->setAttribute (PROP_GRAPHSELECTED,           getIntValue (PROP_GRAPHSELECTED, 0));
    xml->setAttribute (PROP_GRAPHLOCKED,             getIntValue (PROP_GRAPHLOCKED, 0));
    xml->setAttribute (PROP_GRAPHCOLOUR,             getValue (PROP_GRAPHCOLOUR, T("0xff808080")));
    xml->setAttribute (PROP_GRAPHXPOS,               getIntValue (PROP_GRAPHXPOS, -1));
    xml->setAttribute (PROP_GRAPHYPOS,               getIntValue (PROP_GRAPHYPOS, -1));
    xml->setAttribute (PROP_GRAPHWSIZE,              getIntValue (PROP_GRAPHWSIZE, -1));
    xml->setAttribute (PROP_GRAPHHSIZE,              getIntValue (PROP_GRAPHHSIZE, -1));
    xml->setAttribute (PROP_WINDOWXPOS,              getIntValue (PROP_WINDOWXPOS, -1));
    xml->setAttribute (PROP_WINDOWYPOS,              getIntValue (PROP_WINDOWYPOS, -1));
    xml->setAttribute (PROP_WINDOWWSIZE,             getIntValue (PROP_WINDOWWSIZE, -1));
    xml->setAttribute (PROP_WINDOWHSIZE,             getIntValue (PROP_WINDOWHSIZE, -1));
    xml->setAttribute (PROP_WINDOWPAGE,              getIntValue (PROP_WINDOWPAGE, 0));
    xml->setAttribute (PROP_WINDOWOPEN,              getIntValue (PROP_WINDOWOPEN, 0));
    xml->setAttribute (PROP_WINDOWVISIBLEMIDIKEY,    getIntValue (PROP_WINDOWVISIBLEMIDIKEY, 1));
    xml->setAttribute (PROP_PLUGPRESETDIR,           getValue (PROP_PLUGPRESETDIR, String::empty));
    xml->setAttribute (PROP_MIXERLABEL,              getValue (PROP_MIXERLABEL, String::empty));
    xml->setAttribute (PROP_MIXERINDEX,              getIntValue (PROP_MIXERINDEX, 0));
    xml->setAttribute (PROP_MIXERNARROW,             getIntValue (PROP_MIXERNARROW, 0));
    xml->setAttribute (PROP_MIXERPEAK,               getIntValue (PROP_MIXERPEAK, 1));
    xml->setAttribute (PROP_MIXERMETERON,            getIntValue (PROP_MIXERMETERON, 1));
}

void BasePlugin::loadPropertiesFromXml (XmlElement* xml)
{
    setValue (PROP_GRAPHSELECTED,                    xml->getIntAttribute (PROP_GRAPHSELECTED, 0));
    setValue (PROP_GRAPHLOCKED,                      xml->getIntAttribute (PROP_GRAPHLOCKED, 0));
    setValue (PROP_GRAPHCOLOUR,                      xml->getStringAttribute (PROP_GRAPHCOLOUR, T("0xff808080")));
    setValue (PROP_GRAPHXPOS,                        xml->getIntAttribute (PROP_GRAPHXPOS, -1));
    setValue (PROP_GRAPHYPOS,                        xml->getIntAttribute (PROP_GRAPHYPOS, -1));
    setValue (PROP_GRAPHWSIZE,                       xml->getIntAttribute (PROP_GRAPHWSIZE, 50));
    setValue (PROP_GRAPHHSIZE,                       xml->getIntAttribute (PROP_GRAPHHSIZE, 50));
    setValue (PROP_WINDOWXPOS,                       xml->getIntAttribute (PROP_WINDOWXPOS, -1));
    setValue (PROP_WINDOWYPOS,                       xml->getIntAttribute (PROP_WINDOWYPOS, -1));
    setValue (PROP_WINDOWWSIZE,                      xml->getIntAttribute (PROP_WINDOWWSIZE, -1));
    setValue (PROP_WINDOWHSIZE,                      xml->getIntAttribute (PROP_WINDOWHSIZE, -1));
    setValue (PROP_WINDOWPAGE,                       xml->getIntAttribute (PROP_WINDOWPAGE, 0));
    setValue (PROP_WINDOWOPEN,                       xml->getIntAttribute (PROP_WINDOWOPEN, 0));
    setValue (PROP_WINDOWVISIBLEMIDIKEY,             xml->getIntAttribute (PROP_WINDOWVISIBLEMIDIKEY, 1));
    setValue (PROP_PLUGPRESETDIR,                    xml->getStringAttribute (PROP_PLUGPRESETDIR, String::empty));
    setValue (PROP_MIXERLABEL,                       xml->getStringAttribute (PROP_MIXERLABEL, String::empty));
    setValue (PROP_MIXERINDEX,                       xml->getIntAttribute (PROP_MIXERINDEX, 0));
    setValue (PROP_MIXERNARROW,                      xml->getIntAttribute (PROP_MIXERNARROW, 0));
    setValue (PROP_MIXERPEAK,                        xml->getIntAttribute (PROP_MIXERPEAK, 1));
    setValue (PROP_MIXERMETERON,                     xml->getIntAttribute (PROP_MIXERMETERON, 1));
}

//==============================================================================
void BasePlugin::savePresetToXml (XmlElement* xml)
{
    xml->setAttribute (T("gain"), outputGain);
    xml->setAttribute (T("mute"), mutedOutput);
    xml->setAttribute (T("bypass"), bypassOutput);

    MemoryBlock mb;
    getStateInformation (mb);

    XmlElement* chunk = new XmlElement (T("data"));
    chunk->addTextElement (mb.toBase64Encoding ());
    xml->addChildElement (chunk);

    XmlElement* params = new XmlElement (T("parameters"));
    writeParametersToXmlElement (params);
    xml->addChildElement (params);
}    

void BasePlugin::loadPresetFromXml (XmlElement* xml)
{
    // default vst values
    outputGain =  xml->getDoubleAttribute (T("gain"), 1.0);
    mutedOutput = xml->getBoolAttribute (T("mute"), 0);
    bypassOutput = xml->getBoolAttribute (T("bypass"), 0);

    // current preset
    XmlElement* chunk = xml->getChildByName (T("data"));
    if (chunk)
    {
        MemoryBlock mb;
        mb.fromBase64Encoding (chunk->getAllSubText ());
        setStateInformation (mb.getData(), mb.getSize ());
    }

    XmlElement* params = xml->getChildByName (T("parameters"));
    if (params)
    {
        readParametersFromXmlElement (params, false);
    }
}

