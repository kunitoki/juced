/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-7 by Raw Material Software ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the
   GNU General Public License, as published by the Free Software Foundation;
   either version 2 of the License, or (at your option) any later version.

   JUCE is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with JUCE; if not, visit www.gnu.org/licenses or write to the
   Free Software Foundation, Inc., 59 Temple Place, Suite 330,
   Boston, MA 02111-1307 USA

  ------------------------------------------------------------------------------

   If you'd like to release a closed-source product which uses JUCE, commercial
   licenses are also available: visit www.rawmaterialsoftware.com/juce for
   more information.

  ==============================================================================
*/

#ifndef __JUCE_STANDALONEFILTERAPPLICATION_JUCEHEADER__
#define __JUCE_STANDALONEFILTERAPPLICATION_JUCEHEADER__

#include "juce_AudioFilterStreamer.h"
#include "juce_StandaloneFilterWindow.h"


//==============================================================================
/**
    A class that can be used to run a simple standalone application containing your filter.

    Just create one of these objects in your JUCEApplication::initialise() method, and
    let it do its work. It will create your filter object using the same createFilter() function
    that the other plugin wrappers use.
*/
class StandaloneFilterApplication : public JUCEApplication
{
public:

    //==============================================================================
    StandaloneFilterApplication();
    ~StandaloneFilterApplication();

    //==============================================================================
    void initialise (const String& commandLine);
    void shutdown();

    //==============================================================================
    void systemRequestedQuit();
    void unhandledException (const std::exception* e,
                             const String& sourceFilename,
                             const int lineNumber);

    //==============================================================================
    const String getApplicationName();
    const String getApplicationVersion();

    //==============================================================================
    bool moreThanOneInstanceAllowed();

private:

    StandaloneFilterWindow* window;

    StandaloneFilterApplication (const StandaloneFilterApplication&);
    const StandaloneFilterApplication& operator= (const StandaloneFilterApplication&);
};

#endif   // __JUCE_STANDALONEFILTERAPPLICATION_JUCEHEADER__
