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


#include "juce_AppConfig.h"


#ifdef HYBRIDREVERB2_VST_PLUGIN

  // We are building a VST plugin so we need to include the VST wrapper class
  #include "wrapper/VST/juce_VST_Wrapper.cpp"

#elif HYBRIDREVERB2_AU_PLUGIN

  // We are building an AU plugin so we need to include the AU wrapper class
//  #include "wrapper/AU/juce_AU_Wrapper.mm"

#else

  // We are building a Standalone plugin so we need to include the main wrapper
  // class and filter window specifically designed for standalone mode
  #include "wrapper/Standalone/juce_AudioFilterStreamer.cpp"
  #include "wrapper/Standalone/juce_StandaloneFilterWindow.cpp"
  #include "wrapper/Standalone/juce_StandaloneFilterApplication.cpp"

  START_JUCE_APPLICATION (StandaloneFilterApplication)

#endif

