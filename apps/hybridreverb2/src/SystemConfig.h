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


#ifndef __SYSTEMCONFIG_H__
#define __SYSTEMCONFIG_H__


#ifdef _WINDOWS
#include <Windows.h>
#include <crtdbg.h>
#include <tchar.h>
#endif

#include "juce_amalgamated.h"
#include "ParamPreferences.h"
#include "ParamPartitionWisdom.h"


class SystemConfig
{
public:
    SystemConfig ();
    ~SystemConfig();

    const String & getBasedir();
    const String & getUserdir();
    const String & getDBdir();
    String getPresetFilename();
    const ParamPreferences & getPreferences();
    void readPreferencesFile();
    void setPreferences(const ParamPreferences & param);
    const ParamPartitionWisdom & getPartitionWisdom();
    void readPartitionWisdomFile();

private:
    String basedir;
    String userdir;
    String dbdir;
    ParamPreferences paramPreferences;
    ParamPartitionWisdom paramPartitionWisdom;
#ifdef _WINDOWS
    void extractBasedirWindows();
    void extractUserdirWindows();
#else
    void extractBasedirUnix();
    void extractUserdirUnix();
#endif

    String getSubText(XmlElement *element);

};


#endif   // __SYSTEMCONFIG_H__
