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

#ifndef __JUCETICE_XSYNTHPRESETS_HEADER__
#define __JUCETICE_XSYNTHPRESETS_HEADER__

#include "PresetsStore.h"

class Presets
{
public:
    Presets();
    virtual ~Presets();

    void copy (const char *name);//if name==NULL, the clipboard is used
    void paste (int npreset);//npreset==0 for clipboard
    bool checkclipboardtype ();
    void deletepreset (int npreset);
    void setelement (int n);
    void rescanforpresets();

    char type[MAX_PRESETTYPE_SIZE];

protected:
    void setpresettype (const char *type);

private:
    virtual void addToXML (XmlElement* xml) = 0;
    virtual void addToXMLSection (XmlElement* xml, int section) {}
    virtual void updateFromXML (XmlElement *xml) = 0;
    virtual void updateFromXMLSection (XmlElement *xml, int section) {}
    virtual void defaults () = 0;
    virtual void defaults (int n) {}
    int nelement;
};

#endif

