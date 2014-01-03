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

#include "Part.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

Part::Part (TuningMap *microtonal_,FFTWrapper *fft_, CriticalSection *mutex_)
{
    microtonal=microtonal_;
    fft=fft_;
    mutex=mutex_;
    partoutl=new REALTYPE [SOUND_BUFFER_SIZE];
    partoutr=new REALTYPE [SOUND_BUFFER_SIZE];
    tmpoutl=new REALTYPE [SOUND_BUFFER_SIZE];
    tmpoutr=new REALTYPE [SOUND_BUFFER_SIZE];

    for (int n=0;n<NUM_KIT_ITEMS;n++){
        kit[n].Pname=T("default kit");
        kit[n].adpars=NULL;
    }

    kit[0].adpars=new ADnoteParameters(fft);

    //Part's Insertion Effects init
    for (int nefx=0;nefx<NUM_PART_EFX;nefx++)
    {
        partefx[nefx]=new EffectMgr(1,mutex);
        Pefxbypass[nefx]=false;
    }

    for (int n=0;n<NUM_PART_EFX+1;n++)
    {
        partfxinputl[n]=new REALTYPE [SOUND_BUFFER_SIZE];
        partfxinputr[n]=new REALTYPE [SOUND_BUFFER_SIZE];
    }

    killallnotes=0;
    oldfreq=-1.0;

    for (int i=0;i<POLIPHONY;i++)
    {
      partnote[i].status=KEY_OFF;
      partnote[i].note=-1;
      partnote[i].itemsplaying=0;
      for (int j=0;j<NUM_KIT_ITEMS;j++){
        partnote[i].kititem[j].adnote=NULL;
      };
      partnote[i].time=0;
    };
    cleanup();

    Pname = T("default");

    oldvolumel=oldvolumer=0.5;
    lastnote=-1;

    defaults();
}

void Part::defaults()
{
    Penabled=0;
    Pminkey=0;
    Pmaxkey=127;
    Pnoteon=1;
    Ppolymode=1;
    setPvolume(96);
    Pkeyshift=64;
    Prcvchn=0;
    setPpanning(64);
    Pvelsns=64;
    Pveloffs=64;
    Pkeylimit=15;
    Pctrl[0] = 0;
    Pctrl[1] = 1;
    Pctrl[2] = 2;
    Pctrl[3] = 3;
    defaultsinstrument();
    ctl.defaults();
}

void Part::defaultsinstrument()
{
    Pname = T("default");

    info.Ptype=0;
    info.Pauthor = T("kRAkEn/gORe");
    info.Pcomments = T("none");

    Pkitmode=0;
    Pdrummode=0;

    for (int n=0;n<NUM_KIT_ITEMS;n++)
    {
        kit[n].Penabled=0;
        kit[n].Pmuted=0;
        kit[n].Pminkey=0;
        kit[n].Pmaxkey=127;
        kit[n].Padenabled=0;
        kit[n].Pname = T("default");
        kit[n].Psendtoparteffect=0;
        if (n!=0) setkititemstatus(n,0);
    }
    kit[0].Penabled=1;
    kit[0].Padenabled=1;
    kit[0].adpars->defaults();

    for (int nefx=0;nefx<NUM_PART_EFX;nefx++) {
        partefx[nefx]->defaults();
        Pefxroute[nefx]=0;//route to next effect
    }

}

// Cleanup the part
void Part::cleanup(){
    for (int k=0;k<POLIPHONY;k++) KillNotePos(k);
    for (int i=0;i<SOUND_BUFFER_SIZE;i++){
        partoutl[i]=denormalkillbuf[i];
        partoutr[i]=denormalkillbuf[i];
        tmpoutl[i]=0.0;
        tmpoutr[i]=0.0;
    }
    ctl.resetall();

    for (int nefx=0;nefx<NUM_PART_EFX;nefx++)
        partefx[nefx]->clean();

    for (int n=0;n<NUM_PART_EFX+1;n++) {
        for (int i=0;i<SOUND_BUFFER_SIZE;i++){
            partfxinputl[n][i]=denormalkillbuf[i];
            partfxinputr[n][i]=denormalkillbuf[i];
        }
    }
}

Part::~Part(){
    cleanup();

    for (int n=0;n<NUM_KIT_ITEMS;n++){
        if (kit[n].adpars!=NULL) delete (kit[n].adpars); kit[n].adpars=NULL;
    }

    delete[] partoutl;
    delete[] partoutr;
    delete[] tmpoutl;
    delete[] tmpoutr;
    for (int nefx=0;nefx<NUM_PART_EFX;nefx++)
        delete partefx[nefx];
    for (int n=0;n<NUM_PART_EFX+1;n++) {
        delete[] partfxinputl[n];
        delete[] partfxinputr[n];
    }
}

/*
 * Note On Messages
 */
void Part::NoteOn(unsigned char note,unsigned char velocity,int masterkeyshift)
{
    int i,pos;

    lastnote=note;
    if ((note < Pminkey) || (note > Pmaxkey)) return;

    pos=-1;
    for (i = 0; i < POLIPHONY; i++)
    {
        if (partnote[i].status == KEY_OFF)
        {
            pos=i;
            break;
        }
    }

    if (Ppolymode==0)
    {
        //if the mode is 'mono' turn off all other notes
        for (i=0;i<POLIPHONY;i++)
            if (partnote[i].status==KEY_PLAYING) NoteOff(partnote[i].note);
        RelaseSustainedKeys();
    }

    if (pos==-1)
    {
        //test
        // fprintf (stderr,"%s","NOTES TOO MANY (> POLIPHONY) - (Part.C::NoteOn(..))\n");
        DBG (T("NOTES TOO MANY (> POLIPHONY) - (Part.C::NoteOn(..))\n"));
    }
    else
    {
        if (Pnoteon != 0)
        {
            //start the note
            partnote[pos].status=KEY_PLAYING;
            partnote[pos].note=note;

            //this computes the velocity sensing of the part
            REALTYPE vel = VelF (velocity / 127.0, Pvelsns);

            //compute the velocity offset
            vel += (Pveloffs - 64.0) / 64.0;
            if (vel < 0.0) vel = 0.0; else if (vel > 1.0) vel = 1.0;

            //compute the keyshift
            int partkeyshift = (int) Pkeyshift - 64;
            int keyshift = masterkeyshift + partkeyshift;

            //initialise note frequency
            REALTYPE notebasefreq;
            if (Pdrummode == 0)
            {
                notebasefreq = microtonal->getNoteFreq (note + keyshift);
                if (notebasefreq < 0.0) return; // the key is no mapped
            }
            else
            {
                notebasefreq = 440.0 * pow (2.0, (note - 69.0) / 12.0);
            }

            //Portamento
            if (oldfreq < 1.0) oldfreq = notebasefreq;//this is only the first note is played
            int portamento = ctl.initportamento (oldfreq, notebasefreq);
            if (portamento != 0) ctl.portamento.noteusing = pos;
            oldfreq = notebasefreq;

            partnote[pos].itemsplaying=0;
            if (Pkitmode == 0)
            {
                //init the notes for the "normal mode"
                partnote[pos].kititem[0].sendtoparteffect = 0;
                if (kit[0].Padenabled != 0) partnote[pos].kititem[0].adnote = new ADnote (kit[0].adpars,
                                                                                          &ctl,
                                                                                          notebasefreq,
                                                                                          vel,
                                                                                          portamento,
                                                                                          note);
                if (kit[0].Padenabled != 0) partnote[pos].itemsplaying++;
            }
            else
            {
                //init the notes for the "kit mode"
                for (int item = 0; item < NUM_KIT_ITEMS; item++)
                {
                    if (kit[item].Pmuted != 0) continue;
                    if ((note<kit[item].Pminkey) || (note>kit[item].Pmaxkey)) continue;

                    int ci = partnote[pos].itemsplaying;//ci=current item

                    partnote[pos].kititem[ci].sendtoparteffect=( kit[item].Psendtoparteffect<NUM_PART_EFX ?
                    kit[item].Psendtoparteffect: NUM_PART_EFX);//if this parameter is 127 for "unprocessed"

                    if (kit[item].adpars != NULL && kit[item].Padenabled != 0)
                        partnote[pos].kititem[ci].adnote = new ADnote (kit[item].adpars,
                                                                       &ctl,
                                                                       notebasefreq,
                                                                       vel,
                                                                       portamento,
                                                                       note);

                    if (kit[item].adpars != NULL)
                    {
                        partnote[pos].itemsplaying++;
                        if (kit[item].Padenabled != 0 && Pkitmode == 2) break;
                    }
                }
            }
        }
    }

    //this only relase the keys if there is maximum number of keys allowed
    setkeylimit (Pkeylimit);
}

/*
 * Note Off Messages
 */
void Part::NoteOff(unsigned char note){//relase the key
    int i;
    for (i=POLIPHONY-1;i>=0;i--){ //first note in, is first out if there are same note multiple times
    if ((partnote[i].status==KEY_PLAYING)&&(partnote[i].note==note)) {
        if (ctl.sustain.sustain==0){ //the sustain pedal is not pushed
        RelaseNotePos(i);
        break;
        } else {//the sustain pedal is pushed
        partnote[i].status=KEY_RELASED_AND_SUSTAINED;
        };
    };
    };
};

/*
 * Controllers
 */
void Part::SetController(unsigned int type,int par){
    switch (type){
    case C_pitchwheel:ctl.setpitchwheel(par);
              break;
    case C_expression:ctl.setexpression(par);
              setPvolume(Pvolume);//update the volume
              break;
    case C_portamento:ctl.setportamento(par);
              break;
    case C_panning:ctl.setpanning(par);
              setPpanning(Ppanning);//update the panning
              break;
    case C_filtercutoff:ctl.setfiltercutoff(par);
              break;
    case C_filterq:ctl.setfilterq(par);
              break;
    case C_bandwidth:ctl.setbandwidth(par);
              break;
    case C_modwheel:ctl.setmodwheel(par);
              break;
    case C_fmamp:ctl.setfmamp(par);
              break;
    case C_volume:ctl.setvolume(par);
                 if (ctl.volume.receive!=0) volume=ctl.volume.volume;
                else setPvolume(Pvolume);
              break;
    case C_sustain:ctl.setsustain(par);
              if (ctl.sustain.sustain==0) RelaseSustainedKeys();
              break;
    case C_allsoundsoff:AllNotesOff();//Panic
              break;
    case C_resetallcontrollers:
              ctl.resetall();
              RelaseSustainedKeys();
                     if (ctl.volume.receive!=0) volume=ctl.volume.volume;
                    else setPvolume(Pvolume);
              setPvolume(Pvolume);//update the volume
              setPpanning(Ppanning);//update the panning

                  for (int item=0;item<NUM_KIT_ITEMS;item++){
                if (kit[item].adpars==NULL) continue;
                kit[item].adpars->GlobalPar.Reson->
                   sendcontroller(C_resonance_center,1.0);

                kit[item].adpars->GlobalPar.Reson->
                   sendcontroller(C_resonance_bandwidth,1.0);
              };
              //more update to add here if I add controllers
              break;
    case C_allnotesoff:RelaseAllKeys();
              break;
    case C_resonance_center:
            ctl.setresonancecenter(par);
                for (int item=0;item<NUM_KIT_ITEMS;item++){
                 if (kit[item].adpars==NULL) continue;
                  kit[item].adpars->GlobalPar.Reson->
                   sendcontroller(C_resonance_center,ctl.resonancecenter.relcenter);
                };
              break;
    case C_resonance_bandwidth:
            ctl.setresonancebw(par);
            kit[0].adpars->GlobalPar.Reson->
                sendcontroller(C_resonance_bandwidth,ctl.resonancebandwidth.relbw);
              break;
    };
};
/*
 * Relase the sustained keys
 */

void Part::RelaseSustainedKeys(){
    for (int i=0;i<POLIPHONY;i++)
    if (partnote[i].status==KEY_RELASED_AND_SUSTAINED) RelaseNotePos(i);
};

/*
 * Relase all keys
 */

void Part::RelaseAllKeys(){
    for (int i=0;i<POLIPHONY;i++){
    if ((partnote[i].status!=KEY_RELASED)&&
        (partnote[i].status!=KEY_OFF)) //thanks to Frank Neumann
        RelaseNotePos(i);
    };
};

/*
 * Release note at position
 */
void Part::RelaseNotePos(int pos){

    for (int j=0;j<NUM_KIT_ITEMS;j++){

     if (partnote[pos].kititem[j].adnote!=NULL)
        if (partnote[pos].kititem[j].adnote)
      partnote[pos].kititem[j].adnote->relasekey();
    };
    partnote[pos].status=KEY_RELASED;
};


/*
 * Kill note at position
 */
void Part::KillNotePos(int pos){
    partnote[pos].status=KEY_OFF;
    partnote[pos].note=-1;
    partnote[pos].time=0;
    partnote[pos].itemsplaying=0;

    for (int j=0;j<NUM_KIT_ITEMS;j++){
     if (partnote[pos].kititem[j].adnote!=NULL) {
        delete(partnote[pos].kititem[j].adnote);
        partnote[pos].kititem[j].adnote=NULL;
     };
    };
    if (pos==ctl.portamento.noteusing) {
    ctl.portamento.noteusing=-1;
    ctl.portamento.used=0;
    };
};


/*
 * Set Part's key limit
 */
void Part::setkeylimit(unsigned char Pkeylimit){
    this->Pkeylimit=Pkeylimit;
    int keylimit=Pkeylimit;
    if (keylimit==0) keylimit=POLIPHONY-5;

    //release old keys if the number of notes>keylimit
    if (Ppolymode!=0){
    int notecount=0;
    for (int i=0;i<POLIPHONY;i++){
        if ((partnote[i].status==KEY_PLAYING)||(partnote[i].status==KEY_RELASED_AND_SUSTAINED))
            notecount++;
    };
    int oldestnotepos=-1,maxtime=0;
    if (notecount>keylimit){//find out the oldest note
        for (int i=0;i<POLIPHONY;i++){
        if ( ((partnote[i].status==KEY_PLAYING)||(partnote[i].status==KEY_RELASED_AND_SUSTAINED))
           && (partnote[i].time>maxtime)){
              maxtime=partnote[i].time;
              oldestnotepos=i;
            };
        };
    };
    if (oldestnotepos!=-1) RelaseNotePos(oldestnotepos);
    };
};


/*
 * Prepare all notes to be turned off
 */
void Part::AllNotesOff(){
   killallnotes=1;
};


/*
 * Compute Part samples and store them in the partoutl[] and partoutr[]
 */
void Part::ComputePartSmps()
{
    int i,k;
    int noteplay;//0 if there is nothing activated
    for (int nefx = 0; nefx < NUM_PART_EFX + 1; nefx++)
    {
        for (i = 0; i < SOUND_BUFFER_SIZE; i++)
        {
            partfxinputl[nefx][i] = 0.0;
            partfxinputr[nefx][i] = 0.0;
        }
    }

    for (k = 0; k < POLIPHONY; k++)
    {
        if (partnote[k].status == KEY_OFF) continue;

        noteplay = 0;
        partnote[k].time++;

        //get the sampledata of the note and kill it if it's finished
        for (int item = 0; item < partnote[k].itemsplaying; item++)
        {
            int sendcurrenttofx = partnote[k].kititem[item].sendtoparteffect;

            ADnote *adnote = partnote[k].kititem[item].adnote;

            //get from the ADnote
            if (adnote != NULL)
            {
                noteplay++;
                if (adnote->ready != 0)
                {
                    adnote->noteout (&tmpoutl[0], &tmpoutr[0]);
                }
                else
                {
                    for (i=0;i<SOUND_BUFFER_SIZE;i++)
                    {
                        tmpoutl[i] = 0.0;
                        tmpoutr[i] = 0.0;
                    }
                }

                if (adnote->finished() != 0)
                {
                    delete (adnote);
                    partnote[k].kititem[item].adnote=NULL;
                }

                for (i = 0; i < SOUND_BUFFER_SIZE; i++)
                {
                    //add the ADnote to part(mix)
                    partfxinputl[sendcurrenttofx][i] += tmpoutl[i];
                    partfxinputr[sendcurrenttofx][i] += tmpoutr[i];
                }
            }
        }

        //Kill note if there is no synth on that note
        if (noteplay == 0) KillNotePos(k);
    }

    //Apply part's effects and mix them
    for (int nefx = 0; nefx < NUM_PART_EFX; nefx++)
    {
        if (!Pefxbypass[nefx])
        {
            partefx[nefx]->out (partfxinputl[nefx],
                                partfxinputr[nefx],
                                SOUND_BUFFER_SIZE);

            if (Pefxroute[nefx] == 2)
            {
                for (i = 0; i < SOUND_BUFFER_SIZE; i++)
                {
                    partfxinputl[nefx + 1][i] += partefx[nefx]->efxoutl[i];
                    partfxinputr[nefx + 1][i] += partefx[nefx]->efxoutr[i];
                }
            }
        }

        int routeto = ((Pefxroute[nefx]==0) ? (nefx + 1) : NUM_PART_EFX);

        for (i = 0; i < SOUND_BUFFER_SIZE; i++)
        {
            partfxinputl[routeto][i] += partfxinputl[nefx][i];
            partfxinputr[routeto][i] += partfxinputr[nefx][i];
        }
    }

    for (i = 0; i < SOUND_BUFFER_SIZE; i++)
    {
        partoutl[i] = partfxinputl[NUM_PART_EFX][i];
        partoutr[i] = partfxinputr[NUM_PART_EFX][i];
    }

    // Kill All Notes if killallnotes!=0
    if (killallnotes != 0)
    {
        for (i = 0; i < SOUND_BUFFER_SIZE; i++)
        {
            REALTYPE tmp = (SOUND_BUFFER_SIZE - i) / (REALTYPE) SOUND_BUFFER_SIZE;
            partoutl[i] *= tmp;
            partoutr[i] *= tmp;
            tmpoutl[i] = 0.0;
            tmpoutr[i] = 0.0;
        }

        for (int k = 0; k < POLIPHONY; k++) KillNotePos (k);
        killallnotes = 0;

        for (int nefx=0;nefx<NUM_PART_EFX;nefx++)
        {
            partefx[nefx]->clean();
        }
    }

    ctl.updateportamento();
}

/*
 * Parameter control
 */
void Part::setPvolume(char Pvolume_){
    Pvolume=Pvolume_;
    volume=dB2rap((Pvolume-96.0)/96.0*40.0)*ctl.expression.relvolume;
};

void Part::setPpanning(char Ppanning_){
    Ppanning=Ppanning_;
    panning=Ppanning/127.0+ctl.panning.pan;
    if (panning<0.0) panning=0.0;else if (panning>1.0) panning=1.0;

};

/*
 * Enable or disable a kit item
 */
void Part::setkititemstatus(int kititem,int Penabled_){
    if ((kititem==0)&&(kititem>=NUM_KIT_ITEMS)) return;//nonexistent kit item and the first kit item is always enabled
    kit[kititem].Penabled=Penabled_;

    bool resetallnotes=false;
    if (Penabled_==0){
        if (kit[kititem].adpars!=NULL) delete (kit[kititem].adpars);
        kit[kititem].adpars=NULL;
        kit[kititem].Pname = String::empty;
    } else {
        if (kit[kititem].adpars==NULL) kit[kititem].adpars=new ADnoteParameters(fft);
    };

    if (resetallnotes)     for (int k=0;k<POLIPHONY;k++) KillNotePos(k);
};


int Part::saveXML (const char *fileName)
{
    XmlElement mainElement (T("instrument"));
    addToXMLInstrument (&mainElement);

    File fileToSave (fileName);
    fileToSave.replaceWithText (mainElement.createDocument (String::empty), false, false);

    return 0;
}

int Part::loadXMLinstrument (const char *fileName)
{
    File fileToLoad (fileName);

    XmlDocument myDocument (fileToLoad);
    XmlElement* mainElement = myDocument.getDocumentElement();
    if (mainElement)
    {
        XmlElement* instrument = mainElement->getChildByName (T("instrument"));
        if (instrument)
            updateFromXMLInstrument (instrument);

        delete mainElement;
        return 0;
    }

    return -1;
}

void Part::addToXML (XmlElement* xml)
{
    xml->setAttribute (T("on"), Penabled);
    xml->setAttribute (T("vol"), Pvolume);
    xml->setAttribute (T("pan"), Ppanning);
    xml->setAttribute (T("mink"), Pminkey);
    xml->setAttribute (T("maxk"), Pmaxkey);
    xml->setAttribute (T("shift"), Pkeyshift);
    xml->setAttribute (T("rcvc"), Prcvchn);
    xml->setAttribute (T("vsns"), Pvelsns);
    xml->setAttribute (T("vofs"), Pveloffs);
    xml->setAttribute (T("noteon"), Pnoteon);
    xml->setAttribute (T("poly"), Ppolymode);
    xml->setAttribute (T("limk"), Pkeylimit);
    xml->setAttribute (T("ctrl1"), Pctrl[0]);
    xml->setAttribute (T("ctrl2"), Pctrl[1]);
    xml->setAttribute (T("ctrl3"), Pctrl[2]);
    xml->setAttribute (T("ctrl4"), Pctrl[3]);

    { XmlElement* e = new XmlElement (T("ins"));
      addToXMLInstrument (e);
      xml->addChildElement (e); }

    { XmlElement* e = new XmlElement (T("ctl"));
      ctl.addToXML (e);
      xml->addChildElement (e); }
}

void Part::addToXMLInstrument (XmlElement* xml)
{
    {
    XmlElement* e = new XmlElement (T("nfo"));
    e->setAttribute (T("name"), Pname);
    e->setAttribute (T("auth"), info.Pauthor);
    e->setAttribute (T("note"), info.Pcomments);
    e->setAttribute (T("type"), info.Ptype);
    xml->addChildElement (e);
    }

    {
    XmlElement* e = new XmlElement (T("kit"));
    e->setAttribute (T("kitmode"), Pkitmode);
    e->setAttribute (T("drummode"), Pdrummode);
    for (int i = 0; i < NUM_KIT_ITEMS; i++)
    {
        XmlElement* it = new XmlElement (T("item") + String (i));
        it->setAttribute (T("on"), kit[i].Penabled);
        it->setAttribute (T("name"), kit[i].Pname);
        it->setAttribute (T("mute"), kit[i].Pmuted);
        it->setAttribute (T("mink"), kit[i].Pminkey);
        it->setAttribute (T("maxk"), kit[i].Pmaxkey);
        it->setAttribute (T("tofx"), kit[i].Psendtoparteffect);

        it->setAttribute (T("addon"), kit[i].Padenabled);
        {
        XmlElement* ae = new XmlElement (T("kitpar"));
        if (kit[i].adpars) kit[i].adpars->addToXML (ae);
        it->addChildElement (ae);
        }

        e->addChildElement (it);
    }
    xml->addChildElement (e);
    }

    {
    XmlElement* e = new XmlElement (T("efx"));
    for (int nefx = 0; nefx < NUM_PART_EFX; nefx++)
    {
        XmlElement* fx = new XmlElement (T("fx") + String (nefx));

        fx->setAttribute (T("route"), Pefxroute[nefx]);
        partefx[nefx]->setdryonly (Pefxroute[nefx] == 2);
        fx->setAttribute (T("bypass"), Pefxbypass[nefx]);

        partefx[nefx]->addToXML (fx);

        e->addChildElement (fx);
    }
    xml->addChildElement (e);
    }
}



void Part::updateFromXML (XmlElement *xml)
{
    Penabled = xml->getIntAttribute (T("on"), Penabled);
    Pminkey = xml->getIntAttribute (T("mink"), Pminkey);
    Pmaxkey = xml->getIntAttribute (T("maxk"), Pmaxkey);
    Pkeyshift = xml->getIntAttribute (T("shift"), Pkeyshift);
    Prcvchn = xml->getIntAttribute (T("rcvc"), Prcvchn);
    Pvelsns = xml->getIntAttribute (T("vsns"), Pvelsns);
    Pveloffs = xml->getIntAttribute (T("vofs"), Pveloffs);
    Pnoteon = xml->getIntAttribute (T("noteon"), Pnoteon);
    Ppolymode = xml->getIntAttribute (T("poly"), Ppolymode);
    Pkeylimit = xml->getIntAttribute (T("limk"), Pkeylimit);
    Pctrl[0] = xml->getIntAttribute (T("ctrl1"), Pctrl[0]);
    Pctrl[1] = xml->getIntAttribute (T("ctrl2"), Pctrl[1]);
    Pctrl[2] = xml->getIntAttribute (T("ctrl3"), Pctrl[2]);
    Pctrl[3] = xml->getIntAttribute (T("ctrl4"), Pctrl[3]);

    setPvolume (xml->getIntAttribute (T("vol"), Pvolume));
    setPpanning (xml->getIntAttribute (T("pan"), Ppanning));

    forEachXmlChildElement (*xml, e)
    {
        if (e->hasTagName (T("ins"))) updateFromXMLInstrument (e);
        if (e->hasTagName (T("ctl"))) ctl.updateFromXML (e);
    }
}

void Part::updateFromXMLInstrument (XmlElement *xml)
{
    forEachXmlChildElement (*xml, e)
    {
        if (e->hasTagName (T("nfo")))
        {
            Pname = e->getStringAttribute (T("name"));
            info.Pauthor = e->getStringAttribute (T("auth"));
            info.Pcomments = e->getStringAttribute (T("note"));
            info.Ptype = e->getIntAttribute (T("type"), info.Ptype); // 0..16
        }

        if (e->hasTagName (T("kit")))
        {
            Pkitmode = e->getIntAttribute (T("kitmode"), Pkitmode);
            Pdrummode = e->getIntAttribute (T("drummode"), Pdrummode);

            setkititemstatus (0, 0);

            for (int i = 0; i < NUM_KIT_ITEMS; i++)
            {
                XmlElement* k = e->getChildByName (T("item") + String (i));
                if (k)
                {
                    setkititemstatus (i, k->getIntAttribute (T("on"), kit[i].Penabled));
                    kit[i].Pname = k->getStringAttribute (T("name"), T("unnamed"));
                    kit[i].Pmuted = k->getIntAttribute (T("mute"), kit[i].Pmuted);
                    kit[i].Pminkey = k->getIntAttribute (T("mink"), kit[i].Pminkey);
                    kit[i].Pmaxkey = k->getIntAttribute (T("maxk"), kit[i].Pmaxkey);
                    kit[i].Psendtoparteffect = k->getIntAttribute (T("tofx"), kit[i].Psendtoparteffect);

                    kit[i].Padenabled = k->getIntAttribute (T("addon"), kit[i].Padenabled);
                    {
                    XmlElement* ae = k->getChildByName (T("kitpar"));
                    if (ae && kit[i].adpars) kit[i].adpars->updateFromXML (ae);
                    }
                }
            }
        }

        if (e->hasTagName (T("efx")))
        {
            for (int nefx = 0; nefx < NUM_PART_EFX; nefx++)
            {
                XmlElement* fx = e->getChildByName (T("fx") + String (nefx));
                if (fx)
                {
                    Pefxroute[nefx] = fx->getIntAttribute (T("route"), Pefxroute[nefx]); // 0 NUM_PART_EFX
                    partefx[nefx]->setdryonly (Pefxroute[nefx] == 2);
                    Pefxbypass[nefx] = fx->getIntAttribute (T("bypass"), Pefxbypass[nefx]);

                    partefx[nefx]->updateFromXML (fx);
                }
            }
        }

    }
}
