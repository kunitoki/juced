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

#include "Presets.h"
#include <string.h>


Presets::Presets()
{
    type[0]=0;
    nelement=-1;
}

Presets::~Presets(){
}

void Presets::setpresettype(const char *type){
    strcpy(this->type,type);
}

void Presets::copy (const char *name)
{
/*
    XMLwrapper *xml=new XMLwrapper();

    //used only for the clipboard
    if (name==NULL) xml->minimal=false;

    char type[MAX_PRESETTYPE_SIZE];
    strcpy(type,this->type);
    if (nelement!=-1) strcat(type,"n");
    if (name==NULL) {
	if (strstr(type,"Plfo")!=NULL) strcpy(type,"Plfo");
    };

    xml->beginbranch(type);
    if (nelement==-1) add2XML(xml);
	else add2XMLsection(xml,nelement);
    xml->endbranch();

    if (name==NULL) presetsstore.copyclipboard(xml,type);
	else presetsstore.copypreset(xml,type,name);

    delete(xml);
    nelement=-1;
*/
}

void Presets::paste(int npreset)
{
/*
    char type[MAX_PRESETTYPE_SIZE];
    strcpy(type,this->type);
    if (nelement!=-1) strcat(type,"n");
    if (npreset==0){
	if (strstr(type,"Plfo")!=NULL) strcpy(type,"Plfo");
    };

    XMLwrapper *xml=new XMLwrapper();
    if (npreset==0){
	if (!checkclipboardtype()) {
	    nelement=-1;
	    delete(xml);
	    return;
	};
	if (!presetsstore.pasteclipboard(xml)) {
	    delete(xml);
	    nelement=-1;
	    return;
	};
    } else {
	if (!presetsstore.pastepreset(xml,npreset)) {
	    delete(xml);
	    nelement=-1;
	    return;
	};
    };

    if (xml->enterbranch(type)==0) {
	nelement=-1;
	return;
    };
	if (nelement==-1) {
	    defaults();
	    getfromXML(xml);
	} else {
	    defaults(nelement);
	    getfromXMLsection(xml,nelement);
	};
    xml->exitbranch();

    delete(xml);
    nelement=-1;
*/
}

bool Presets::checkclipboardtype(){
/*
    char type[MAX_PRESETTYPE_SIZE];
    strcpy(type,this->type);
    if (nelement!=-1) strcat(type,"n");

    return(presetsstore.checkclipboardtype(type));
*/
    return false;
}

void Presets::setelement(int n){
//    nelement=n;
}

void Presets::rescanforpresets(){
//    presetsstore.rescanforpresets(type);
}

void Presets::deletepreset(int npreset){
//    presetsstore.deletepreset(npreset);
}
