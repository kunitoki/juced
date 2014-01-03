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

#ifndef __JUCETICE_XSYNTHBANK_HEADER__
#define __JUCETICE_XSYNTHBANK_HEADER__

/*

#include "../globals.h"
#include "XMLwrapper.h"
#include "Part.h"

#define BANK_SIZE 160

#define MAX_NUM_BANKS 400


class Bank{
    public:
	Bank();
	~Bank();
	char *getname(unsigned int ninstrument);
	char *getnamenumbered(unsigned int ninstrument);
	void setname(unsigned int ninstrument,const char *newname,int newslot);//if newslot==-1 then this is ignored, else it will be put on that slot
	bool isPADsynth_used(unsigned int ninstrument);

	//returns 0 if the slot is not empty or 1 if the slot is empty
	int emptyslot(unsigned int ninstrument);

	void clearslot(unsigned int ninstrument);
	void savetoslot(unsigned int ninstrument,Part *part);
	void loadfromslot(unsigned int ninstrument,Part *part);

	void swapslot(unsigned int n1,unsigned int n2);

	int loadbank(const char *bankdirname);
	int newbank(const char *newbankdirname);

	char *bankfiletitle; //this is shown on the UI of the bank (the title of the window)
	int locked();

	void rescanforbanks();

	struct bankstruct{
	    char *dir;
	    char *name;
	};

	bankstruct banks[MAX_NUM_BANKS];

    private:

	//it adds a filename to the bank
	//if pos is -1 it try to find a position
	//returns -1 if the bank is full, or 0 if the instrument was added
	int addtobank(int pos,const char* filename,const char* name);

	void deletefrombank(int pos);

	void clearbank();

	char defaultinsname[PART_MAX_NAME_LEN];
	char tmpinsname[BANK_SIZE][PART_MAX_NAME_LEN+20];//this keeps the numbered names

	struct ins_t{
	    bool used;
	    char name[PART_MAX_NAME_LEN+1];
	    char *filename;
	    struct{
		bool PADsynth_used;
	    } info;
	}ins[BANK_SIZE];

	char *dirname;

	void scanrootdir(char *rootdir);//scans a root dir for banks
};

*/

#endif

