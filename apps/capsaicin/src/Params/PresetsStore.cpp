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

#include "PresetsStore.h"
#include "../Misc/Util.h"

PresetsStore presetsstore;

PresetsStore::PresetsStore(){
    clipboard.data=0;
    clipboard.type[0]=0;

    for (int i=0;i<MAX_PRESETS;i++){
	presets[i].file=0;
	presets[i].name=0;
    };

};

PresetsStore::~PresetsStore(){
    if (clipboard.data!=0) delete (clipboard.data);
    clearpresets();
};

//Clipboard management
/*
void PresetsStore::copyclipboard(XMLwrapper *xml,char *type){
    strcpy(clipboard.type,type);
    if (clipboard.data!=NULL) delete (clipboard.data);
    clipboard.data=xml->getXMLdata();
};

bool PresetsStore::pasteclipboard(XMLwrapper *xml){
    if (clipboard.data!=NULL) xml->putXMLdata(clipboard.data);
	else return(false);
    return(true);
};

bool PresetsStore::checkclipboardtype(char *type){
    //makes LFO's compatible
    if ((strstr(type,"Plfo")!=NULL)&&(strstr(clipboard.type,"Plfo")!=NULL)) return(true);
    return(strcmp(type,clipboard.type)==0);
};
*/

//Presets management
void PresetsStore::clearpresets(){
    for (int i=0;i<MAX_PRESETS;i++){
	if (presets[i].file!=0) {
	    delete(presets[i].file);
	    presets[i].file=0;
	};
	if (presets[i].name!=0) {
	    delete(presets[i].name);
	    presets[i].name=0;
	};
    };

};

/*
//a helper function that compares 2 presets[]
int Presets_compar(const void *a,const void *b){
    struct PresetsStore::presetstruct *p1= (PresetsStore::presetstruct *)a;
    struct PresetsStore::presetstruct *p2= (PresetsStore::presetstruct *)b;
    if (((p1->name)==NULL)||((p2->name)==NULL)) return(0);

    return(strcasecmp(p1->name,p2->name)<0);
};


void PresetsStore::rescanforpresets(char *type){
    clearpresets();
    int presetk=0;
    char ftype[MAX_STRING_SIZE];
    snprintf(ftype,MAX_STRING_SIZE,".%s.xpz",type);

    for (int i=0;i<MAX_BANK_ROOT_DIRS;i++){
	if (config.cfg.PresetsDirList[i]==NULL) continue;
	const char *dirname=config.cfg.PresetsDirList[i];
	DIR *dir=opendir(dirname);
	if (dir==NULL) continue;
	struct dirent *fn;
	while((fn=readdir(dir))){
	    const char *filename=fn->d_name;
	    if (strstr(filename,ftype)==NULL) continue;


	    presets[presetk].file=new char [MAX_STRING_SIZE];
	    presets[presetk].name=new char [MAX_STRING_SIZE];
	    char tmpc=dirname[strlen(dirname)-1];
	    char *tmps="/";
	    if ((tmpc=='/')||(tmpc=='\\')) tmps="";
	    snprintf(presets[presetk].file,MAX_STRING_SIZE,"%s%s%s",dirname,tmps,filename);
	    snprintf(presets[presetk].name,MAX_STRING_SIZE,"%s",filename);

	    char *tmp=strstr(presets[presetk].name,ftype);
	    if (tmp!=NULL) tmp[0]='\0';
	    presetk++; if (presetk>=MAX_PRESETS) return;
	};

	closedir(dir);
    };

    //sort the presets
    for (int j=0;j<MAX_PRESETS-1;j++){
	for (int i=j+1;i<MAX_PRESETS;i++){
	    if (Presets_compar(&presets[i],&presets[j])) {
		presetstruct tmp=presets[i];
		presets[i]=presets[j];
		presets[j]=tmp;
	    };
	};
    };
};


void PresetsStore::copypreset(XMLwrapper *xml,char *type, const char *name){
    char filename[MAX_STRING_SIZE],tmpfilename[MAX_STRING_SIZE];

    if (config.cfg.PresetsDirList[0]==NULL) return;

    snprintf(tmpfilename,MAX_STRING_SIZE,"%s",name);

    //make the filenames legal
    for (int i=0;i<(int) strlen(tmpfilename);i++) {
	char c=tmpfilename[i];
	if ((c>='0')&&(c<='9')) continue;
	if ((c>='A')&&(c<='Z')) continue;
	if ((c>='a')&&(c<='z')) continue;
	if ((c=='-')||(c==' ')) continue;
	tmpfilename[i]='_';
    };

    const char *dirname=config.cfg.PresetsDirList[0];
    char tmpc=dirname[strlen(dirname)-1];
    char *tmps="/";
    if ((tmpc=='/')||(tmpc=='\\')) tmps="";

    snprintf(filename,MAX_STRING_SIZE,"%s%s%s.%s.xpz",dirname,tmps,name,type);

    xml->saveXMLfile(filename);
};

bool PresetsStore::pastepreset(XMLwrapper *xml, int npreset){
    npreset--;
    if (npreset>=MAX_PRESETS) return(false);
    char *filename=presets[npreset].file;
    if (filename==NULL) return(false);
    bool result=(xml->loadXMLfile(filename)>=0);
    return(result);
};

void PresetsStore::deletepreset(int npreset){
    npreset--;
    if (npreset>=MAX_PRESETS) return;
    char *filename=presets[npreset].file;
    if (filename==NULL) return;
    remove(filename);
};
*/
