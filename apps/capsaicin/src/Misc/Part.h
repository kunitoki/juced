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

#ifndef __JUCETICE_XSYNTHPART_HEADER__
#define __JUCETICE_XSYNTHPART_HEADER__

#include "../globals.h"
#include "../Params/ADnoteParameters.h"
#include "../Synth/ADnote.h"
#include "../Params/Controller.h"
#include "../Effects/EffectMgr.h"

class Part
{
public:

    Part (TuningMap *microtonal_, FFTWrapper *fft_, CriticalSection *mutex_);
    ~Part();

    /* Midi commands implemented */
    void NoteOn (unsigned char note, unsigned char velocity, int masterkeyshift);
    void NoteOff (unsigned char note);
    void AllNotesOff ();//panic
    void SetController (unsigned int type,int par);
    void RelaseSustainedKeys();//this is called when the sustain pedal is relased
    void RelaseAllKeys();//this is called on AllNotesOff controller

    /* The synthesizer part output */
    void ComputePartSmps();//Part output

    //instrumentonly: 0 - save all, 1 - save only instrumnet, 2 - save only instrument without the name(used in bank)

    //saves the instrument settings to a XML file
    //returns 0 for ok or <0 if there is an error
    void defaults();
    void defaultsinstrument();
    void cleanup();

    int saveXML (const char *filename);
    int loadXMLinstrument (const char *filename);

    void addToXML (XmlElement* xml);
    void addToXMLInstrument (XmlElement* xml);
    void updateFromXML (XmlElement *xml);
    void updateFromXMLInstrument (XmlElement *xml);

    //the part's kit
    struct {
        String Pname;
        uint8 Penabled;
        uint8 Pmuted;
        uint8 Pminkey;
        uint8 Pmaxkey;
        uint8 Padenabled;
        uint8 Psendtoparteffect;
        ADnoteParameters *adpars;
    } kit[NUM_KIT_ITEMS];

    //Part parameters
    void setkeylimit (unsigned char Pkeylimit);
    void setkititemstatus (int kititem, int Penabled_);

    void setPvolume (char Pvolume);
    void setPpanning (char Ppanning);

    uint8 Penabled;   // if the part is enabled
    uint8 Pvolume;    // part volume
    uint8 Pminkey;    // the minimum key that the part receives noteon messages
    uint8 Pmaxkey;    // the maximum key that the part receives noteon messages
    uint8 Pkeyshift;  // part keyshift
    uint8 Prcvchn;    // from what midi channel it receive commands
    uint8 Ppanning;   // part panning
    uint8 Pvelsns;    // velocity sensing (amplitude velocity scale)
    uint8 Pveloffs;   // velocity offset
    uint8 Pnoteon;    // if the part receives NoteOn messages
    uint8 Pkitmode;   // if the kitmode is enabled
    uint8 Pdrummode;  // if all keys are mapped and the system is 12tET (used for drums)
    uint8 Ppolymode;  // Part mode - 0=monophonic , 1=polyphonic
    uint8 Pkeylimit;  // how many keys are alowed to be played same time (0=off), the older will be relased
    int   Pctrl[4];   // 4 dynamic controls

    String Pname; //name of the instrument
    struct { //instrument additional information
        uint8 Ptype;
        String Pauthor;
        String Pcomments;
    } info;

    REALTYPE *partoutl;//Left channel output of the part
    REALTYPE *partoutr;//Right channel output of the part

    REALTYPE *partfxinputl[NUM_PART_EFX+1],*partfxinputr[NUM_PART_EFX+1];//Left and right signal that pass thru part effects; partfxinput l/r [NUM_PART_EFX] is for "no effect" buffer

    enum NoteStatus{KEY_OFF,KEY_PLAYING,KEY_RELASED_AND_SUSTAINED,KEY_RELASED};

    REALTYPE volume,oldvolumel,oldvolumer;//this is applied by Master
    REALTYPE panning;//this is applied by Master, too

    Controller ctl;//Part controllers

    EffectMgr *partefx[NUM_PART_EFX];//insertion part effects (they are part of the instrument)
    uint8 Pefxroute[NUM_PART_EFX];//how the effect's output is routed(to next effect/to out)
    bool Pefxbypass[NUM_PART_EFX];//if the effects are bypassed

    CriticalSection *mutex;

    int lastnote;

private:
    void KillNotePos(int pos);
    void RelaseNotePos(int pos);
    int killallnotes; //is set to 1 if I want to kill all notes

    struct PartNotes{
        NoteStatus status;
        int note; //if there is no note playing, the "note"=-1
        int itemsplaying;
        struct {
            ADnote *adnote;
            int sendtoparteffect;
        } kititem[NUM_KIT_ITEMS];
        int time;
    };

    PartNotes partnote[POLIPHONY];

    REALTYPE *tmpoutl;
    REALTYPE *tmpoutr;

    REALTYPE oldfreq; //this is used for portamento
    TuningMap* microtonal;
    FFTWrapper *fft;
};

#endif

