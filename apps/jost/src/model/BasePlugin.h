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

#ifndef __JUCETICE_JOSTBASEPLUGIN_HEADER__
#define __JUCETICE_JOSTBASEPLUGIN_HEADER__

#include "../Config.h"

//==============================================================================
/**
    Common properties should be not-realtime options:
    - name
    - uniqueID (vst)
    - version
    - hasEditor ?
    - programsAreChunks ?
*/

#define PROP_WINDOWOPEN                       T("wOpen")
#define PROP_WINDOWPAGE                       T("wPage")
#define PROP_WINDOWXPOS                       T("wXpos")
#define PROP_WINDOWYPOS                       T("wYpos")
#define PROP_WINDOWWSIZE                      T("wWsize")
#define PROP_WINDOWHSIZE                      T("wHsize")
#define PROP_WINDOWVISIBLEMIDIKEY             T("wMidiKey")
#define PROP_GRAPHLOCKED                      T("gLock")
#define PROP_GRAPHCOLOUR                      T("gColour")
#define PROP_GRAPHSELECTED                    T("gSel")
#define PROP_GRAPHXPOS                        T("gXpos")
#define PROP_GRAPHYPOS                        T("gYpos")
#define PROP_GRAPHWSIZE                       T("gWsize")
#define PROP_GRAPHHSIZE                       T("gHsize")
#define PROP_PLUGPRESETDIR                    T("pPdir")
#define PROP_MIXERLABEL                       T("mLbl")
#define PROP_MIXERINDEX                       T("mIdx")
#define PROP_MIXERNARROW                      T("mNrw")
#define PROP_MIXERPEAK                        T("mPeak")
#define PROP_MIXERMETERON                     T("mMon")

class BasePlugin;
class PluginEditorComponent;
class HostFilterBase;

//==============================================================================
/**
    This is a common interface for all our plugins implemented in the host

    It inherits from PropertySet so we can pack common properties with every
    object and not have a lot of specific functions just to get a property.
    Also this way we can store dynamic properties from UI or specific technology
    properties.
*/
class BasePlugin : public AudioPlugin,
                   public AudioProcessingBuffer,
                   public PropertySet
{
public:

    //==============================================================================
    virtual ~BasePlugin ();

    //==============================================================================
    virtual int getType () const                           { return JOST_PLUGINTYPE_INVALID; }
    virtual int getID () const                             { return 0x00AA0000 + getType (); }

    //==============================================================================
    virtual bool loadPluginFromFile (const File& filePath) { return true; }
    virtual File getFile () const                          { return File::nonexistent; }

    //==============================================================================
    virtual bool isMidiInput () const                      { return false; }
    virtual bool isMidiOutput () const                     { return false; }

    virtual int getNumInputs () const                      { return 0; }
    virtual int getNumOutputs () const                     { return 0; }
    virtual int getNumMidiInputs () const                  { return 0; }
    virtual int getNumMidiOutputs () const                 { return 0; }
    virtual void* getLowLevelHandle ()                     { return this; }

    //==============================================================================
    virtual bool hasEditor () const                        { return false; }
    virtual bool wantsEditor () const                      { return false; }
    virtual bool isEditorInternal () const                 { return false; }

    virtual void getEditorSize (int& width, int& height) {}
    virtual void openEditor (void* handle, void* display) {}
    virtual void idleEditor () {}
    virtual void closeEditor () {}

public:

    //==============================================================================
    /** Returns the unique hash representing this plugin */

    /** Returns the unique hash representing this plugin */
    int32 getUniqueHash () const                       { return uniqueHash; }

    //==============================================================================
    void setParentHost (HostFilterBase* owner)         { parentHost = owner; }

    HostFilterBase* getParentHost () const             { return parentHost; }

    //==============================================================================
    /** Serialize internal properties to an Xml element */
    virtual void savePropertiesToXml (XmlElement* element);

    /** Deserialize internal properties from an Xml element */
    virtual void loadPropertiesFromXml (XmlElement* element);

    //==============================================================================
    /** Serialize track to an Xml element */
    virtual void savePresetToXml (XmlElement* element);

    /** Deserialize track from an Xml element */
    virtual void loadPresetFromXml (XmlElement* element);

    //==============================================================================
    /** Get the desired output gain */
    float getOutputGain () const                       { return outputGain; }

    /** Set the desired output gain */
    void setOutputGain (const float newGain)           { outputGain = newGain; }

    /** @internal */
    float getCurrentOutputGain () const                { return currentOutputGain; }
    /** @internal */
    void setCurrentOutputGain (const float newGain)    { currentOutputGain = newGain; }

    //==============================================================================
    /** Get the desired output panning

        0 means left, 0.5 means centre, 1 is right
     */
    float getOutputPanning () const                    { return outputPan; }

    /** Set the desired output gain */
    void setOutputPanning (const float newPan)         { outputPan = newPan; }

    /** @internal */
    float getCurrentOutputPanning () const             { return currentOutputPan; }
    /** @internal */
    void setCurrentOutputPanning (const float newPan)  { currentOutputPan = newPan; }

    //==============================================================================
    /** Get the desired mute state */
    bool isMuted () const                              { return mutedOutput; }

    /** Set the desired mute state */
    void setMuted (const bool muted)                   { mutedOutput = muted; }

    //==============================================================================
    /** Get the desired mute state */
    bool isBypass () const                             { return bypassOutput; }

    /** Set the desired mute state */
    void setBypass (const bool bypass)                 { bypassOutput = bypass; }

protected:

    //==============================================================================
    BasePlugin ();

    //==============================================================================
    static int32 globalUniqueCounter;
    int32 uniqueHash;

    //==============================================================================
    HostFilterBase* parentHost;

    //==============================================================================
    bool mutedOutput           : 1,
         bypassOutput          : 1;

    //==============================================================================
    float outputGain, currentOutputGain;
    float outputPan, currentOutputPan;
};


#endif
