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

   @author  Paul Nasca
   @tweaker Lucio Asnaghi

 ==============================================================================
*/

#ifndef __JUCETICE_XSYNTHCONFIG_HEADER__
#define __JUCETICE_XSYNTHCONFIG_HEADER__

#include "../globals.h"
#include "../JucePluginCharacteristics.h"

//==============================================================================
#ifdef JUCE_WIN32
  #define CONFIG_DIRECTORY      T("capsaicin")
#elif defined JUCE_LINUX
  #define CONFIG_DIRECTORY      T(".capsaicin")
#elif defined JUCE_MAC
  #define CONFIG_DIRECTORY      T(".capsaicin")
#endif

#define CONFIG_FILENAME         T("default")
#define CONFIG_FILEEXT          T("conf")


//==============================================================================
class Config
{
public:

    //==============================================================================
    int PluginVersion;
    int SampleRate;
    int SoundBufferSize;
    int OscilSize;
    int LastOpenedPage;
    int LastOpenedPart;
    int IsKeyboardVisible;
    File CurrentBankDir;

    //==============================================================================
    Config();
    ~Config();

    //==============================================================================
    void load();
    void save();

    //==============================================================================
    juce_DeclareSingleton (Config, false)

private:

    PropertiesFile* configFile;
};


#endif // __JUCETICE_XSYNTHCONFIG_HEADER__
