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

    Original code: Reuben a.k.a. Insertpizhere

 ==============================================================================
*/

#include "MidiPads.h"
#include "MidiPadsPluginEditor.h"


//==============================================================================
MidiPadsProgram::MidiPadsProgram ()
{
    //default values
    param[kVelOffset] = 0.5f;      // velocity offset
    param[kCCOffset] = 0.5f;       // cc value offset
    param[kChIn] = 0.0f / 15.0f;   // in channel
    param[kChOut] = 0.0f / 15.0f;  // out channel
    param[kUseTrigger] = 0.0f;     // use triggering?
    param[kNoteOnTrig] = 0.0f;     // "piezo trigger mode"
    param[kUseVel] = 1.0f;         // use trigger velocity?
    param[kThru] = 1.0f;           // midi thru?
    param[kSendAft] = 0.0f;        // send aftertouch?
    param[kMono]= 0.0f;            // mono mode

    for (int i = 0; i < numPads; i++)
    {
        Ydata1[i] = (36.0f+(float)i) * float_MidiScaler; //note
        Ycc[i] = (36.0f+(float)i) * float_MidiScaler;    //y cc
        Ytype[i] = 0.0f;    //type
        Ydata2[i]  = 1.0f;  //data2
        Yoff[i]  = 0.0f;    //off value
        trigger[i]  = 0.0f; //trigger note
        Xcc[i]  = (1.0f * float_MidiScaler); //x cc
        Xoff[i] = 0.0f;
        UseX[i] = 0.0f;     // use x-position?
        UseY[i] = 0.0f;     // use y-position?
        UseYCC[i] = false;  // (don't) send y-cc with note
        UseXPB[i] = false;  // (don't) use x as pitch bend
        toggle[i] = false;  // toggle mode off
        SendOff[i] = true;  // send off value
        param[i+xpos] = (0.5);
        param[i+ypos] = (0.5);
        icon[i] = String::empty;             //icon filename
        text[i] << T("Pad ") << String(i+1); //pad name
        padcolor[i] = Colour(0xFF000000);

        lastx[i]=64;
        if (SendOff[i]) lasty[i] = roundFloatToInt(Yoff[i]*127.0f);
        else            lasty[i] = 64;
        togglestate[i] = false;
    }

    //default GUI size
    lastUIWidth = 400;
    lastUIHeight = 400;

    //colors, etc
    bghue = 0.1f;
    bgsat = 0.1f;
    bgbri = 0.8f;
    contrast = 0.3f;
    squares = 16;
    showdots = true;
    editmode = true;
    roundness = 0.4f;
    usemouseup = true;
    hex = false;

    //program name
	name = T("Default");
}

MidiPadsProgram::~MidiPadsProgram ()
{
}

//==============================================================================
MidiPadsPlugin::MidiPadsPlugin() 
{
    init = true;

    // create built-in programs
    programs = new MidiPadsProgram [getNumPrograms()];

    for (int i = 0; i < getNumPrograms(); i++)
    { 
	    switch(i)
	    {
	    case 0: 
            programs[i].name = T("Default"); 
            programs[i].showdots = true; 
            programs[i].lastUIWidth = 400;
            programs[i].lastUIHeight = 400;
            programs[i].squares = 10;
            programs[i].name = T("Pads");
            programs[i].UseX[8] = 1.0f;
            programs[i].UseX[9] = 1.0f;
            programs[i].UseY[8] = 1.0f;
            programs[i].UseY[9] = 1.0f;
            programs[i].UseYCC[8] = true;
            programs[i].UseYCC[9] = true;
            programs[i].SendOff[8] = false;
            programs[i].SendOff[9] = false;
            programs[i].roundness = 0.2f;
            break;
        case 1: 
            programs[i].name = T("Sliders"); 
            programs[i].showdots = true; 
            programs[i].squares = 17;
            programs[i].lastUIWidth = 640;
            programs[i].lastUIHeight = 400;
            for (int pad = 0; pad < 16; pad++)
            {
                programs[i].UseY[pad] = 1.0f;
                programs[i].Ycc[pad]   = (64.0f+(float)pad)/127.0f; //data1
                programs[i].Ytype[pad] = 1.0f; //type = CC
                programs[i].icon[pad] = String::empty;
                programs[i].text[pad] = String::empty;
                programs[i].SendOff[pad] = false;
            }
            break;
        case 2: 
            programs[i].name = T("X-Y Sliders"); 
            programs[i].showdots = true; 
            programs[i].squares = 5;
            programs[i].lastUIWidth = 640;
            programs[i].lastUIHeight = 400;
            for (int pad = 0; pad < 4; pad++)
            {
                programs[i].Ycc[pad]   = (64.0f + (float)pad) / 127.0f; //data1
                programs[i].Ytype[pad] = 1.0f; //type = CC
                programs[i].Xcc[pad]  = (1.0f + (float)pad) / 127.0f; //x cc
                programs[i].UseX[pad] = 1.0f;
                programs[i].UseY[pad] = 1.0f;
                programs[i].icon[pad] = String::empty;
                programs[i].text[pad] = String::empty;
                programs[i].SendOff[pad] = false;
            }
            break;
        case 3:
            programs[i].name = T("Big X-Y Pad");
            programs[i].showdots = true;
            programs[i].squares = 1;
            programs[i].UseX[0] = 1.0f;
            programs[i].UseY[0] = 1.0f;
            programs[i].lastUIWidth = 400;
            programs[i].lastUIHeight = 400;
            programs[i].Ycc[0]   = 74.0f / 127.0f; //data1
            programs[i].Ytype[0] = 1.0f; //type = CC
            programs[i].Xcc[0]  = 1.0f / 127.0f; //x cc
            programs[i].icon[0] = String::empty;
            programs[i].text[0] = String::empty;
            programs[i].roundness = 0.05f;
            programs[i].SendOff[0] = false;
            break;
	    case 4: 
            programs[i].name = T("Mighty Pea");
            programs[i].showdots = false;
            programs[i].lastUIWidth = 400;
            programs[i].lastUIHeight = 400;
            for (int pad = 0; pad < 16; pad++)
            {
                String padicon;
                padicon << String(pad + 1) << T(".svg");
                programs[i].icon[pad] = padicon;
                programs[i].padcolor[pad] = Colour(0xFFFFFFFF);
            }
            programs[i].contrast = 0.1f;
            programs[i].bgbri = 0.3f;
            programs[i].bgsat = 0.0f;
            programs[i].roundness = 0.3f;
            programs[i].text[0] = T("Kick");
            programs[i].text[1] = T("Snare");
            programs[i].text[2] = T("HiHat C");
            programs[i].text[3] = T("HiHat O");
            programs[i].text[4] = T("Ride");
            programs[i].text[5] = T("Crash");
            programs[i].text[6] = T("Cowbell");
            programs[i].text[7] = T("Bell");
            programs[i].text[8] = T("Tom 3");
            programs[i].text[9] = T("Tom 2");
            programs[i].text[10] = T("Tom 1");
            programs[i].text[11] = T("Clap");
            programs[i].text[12] = T("");
            programs[i].text[13] = T("");
            programs[i].text[14] = T("");
            programs[i].text[15] = T("");
            break;
        case 5:
            programs[i].name=T("40 Pads");
            programs[i].squares=40;
//                programs[i].hex=true;
            programs[i].showdots=false;
            for (int pad=0;pad<40;pad++) {
                programs[i].icon[pad] = String::empty;
                programs[i].text[pad] = String::empty;
            }
            break;
        case 6:
            programs[i].name=T("64 Pads");
            programs[i].squares=64;
            programs[i].showdots=false;
            programs[i].roundness = 0.05f;
            for (int pad=0;pad<64;pad++) {
                programs[i].icon[pad] = String::empty;
                programs[i].text[pad] = String::empty;
            }
            break;
        case 7: 
            programs[i].name=T("8 Channel Mixer");
            programs[i].squares=33;
            programs[i].lastUIHeight=550;
            programs[i].lastUIWidth=550;
            programs[i].bgbri=0.3f;
            for (int pad=0;pad<32;pad++) {
                programs[i].icon[pad] = T("");
                programs[i].Ytype[pad]=1.0f;
                if (pad<8) {
                    programs[i].toggle[pad]=true;
                    programs[i].SendOff[pad]=true;
                    programs[i].padcolor[pad]=Colour(0xFFFF0000);
                    programs[i].text[pad] = T("Mute");
                }
                else if (pad<16) {
                    programs[i].toggle[pad]=true;
                    programs[i].SendOff[pad]=true;
                    programs[i].padcolor[pad]=Colour(0xFF00FF00);
                    programs[i].text[pad] = T("Solo");
                }
                else if (pad<24) {
                    programs[i].UseX[pad]=true;
                    programs[i].SendOff[pad]=false;
                    programs[i].Ydata2[pad]=0.5f;
                    programs[i].Xcc[pad]=programs[i].Ycc[pad];
                    programs[i].Ycc[pad]=1.0f/127.0f;
                    programs[i].text[pad] = T("Pan");
                    programs[i].icon[pad] = String::empty;
                }
                else {
                    programs[i].UseX[pad]=false;
                    programs[i].UseY[pad]=true;
                    programs[i].SendOff[pad]=false;
                    programs[i].text[pad] = String(pad-23);
                }
            }
            break;
        case 8:
            programs[i].name=String(T("KVR"));
            programs[i].squares=16;
            programs[i].bgsat=0.0f;
            programs[i].bgbri=0.198275864f;
            programs[i].contrast=1.0f;
            programs[i].roundness=0.1f;
            programs[i].showdots=false;
            for (int pad=0;pad<16;pad++) {
                programs[i].icon[pad] = String::empty;
                programs[i].text[pad] = String (pad + 1);
                if (pad<4) programs[i].padcolor[pad] = Colour(0xFF304050);
                else if (pad<8) programs[i].padcolor[pad] = Colour(0xFF304060);
                else if (pad<12) programs[i].padcolor[pad] = Colour(0xFF304050);
                else  programs[i].padcolor[pad] = Colour(0xFF304060);
            }
            break;
        }
    }

    //default GUI size
    lastUIWidth = 400;
    lastUIHeight = 400;
    
    // set default preset
    curProgram = 0;
    setCurrentProgram (0);

    //initialize temporary parameters
    triggervel = 0;
    for (int i = 0; i < 128; i++) isplaying[i] = false;
    for (int i = 0; i < numPads; i++)
    {
        buttondown[i] = false;
        midilisten[i] = 0.0f;
        triggered[i] = false;
        send[i] = 0.0f;
        sendoff[i] = 0.0f;
        lastx[i]=programs[curProgram].lastx[i];
        if (SendOff[i]) lasty[i] = (int)(Yoff[i]*127.1);
        else lasty[i] = programs[curProgram].lasty[i];
        lastxccvalue[i] = -1;
        lastyccvalue[i] = -1;
        dotmoved[i] = false;
    }
}

MidiPadsPlugin::~MidiPadsPlugin() 
{
    if (programs) delete [] programs;
}

//==============================================================================
void MidiPadsPlugin::prepareToPlay (double sampleRate, int samplesPerBlock)
{
}

void MidiPadsPlugin::releaseResources()
{
}

void MidiPadsPlugin::processBlock (AudioSampleBuffer& buffer,
                                   MidiBuffer& midiBuffer)
{
    MidiBuffer midiout;
    MidiBuffer* midiMessages = midiBuffers.getUnchecked (0);

    bool discard = false;
    if (param[kThru] < 0.5f) discard = true; // if midi thru is off, discard original message

    int outch = (int)(param[kChOut]*15.1f);
    float noteScale = 0.00787401574803149606299212598425197f;

    int sample_number;
    MidiMessage midi_message (0xf4, 0.0);
    MidiBuffer::Iterator mid_buffer_iter (*midiMessages);

    while (mid_buffer_iter.getNextEvent (midi_message, sample_number))
    {
        //program change
        if (midi_message.isProgramChange() ) { // && (midi_message.isForChannel(channel) || channel==0)) {
            if (midi_message.getProgramChangeNumber() < getNumPrograms()) 
                setCurrentProgram (midi_message.getProgramChangeNumber());
        }

        for (int i = 0; i < jmax (1, (squares - squares % 2)); i++)
        {
            //midi learn y
            if (midilisten[i]==1.0f)
            {
                if (midi_message.isNoteOn() && (midi_message.getVelocity() > 1))
                {
                    float bbb = (midi_message.getNoteNumber())*noteScale;
                    midilisten[i] = 0;
                    Ydata1[i]=bbb;
                    Ytype[i]=0.0f;
                    Ydata2[i]=midi_message.getVelocity()*noteScale;
                    sendChangeMessage(this);
                }
                else if (midi_message.isController())
                {
                    float ccc = (midi_message.getControllerNumber())*noteScale;
                    midilisten[i] = 0;
                    Ycc[i]=ccc;
                    Ytype[i]=1.0f;
                    Ydata2[i]=midi_message.getControllerValue()*noteScale;
                    sendChangeMessage(this);
                }
            }
            // learn y-off
            else if (midilisten[i]==0.9f)
            {
                if (midi_message.isNoteOn() && (midi_message.getVelocity() > 1))
                {
                    midilisten[i] = 0;
                    Yoff[i]=midi_message.getVelocity()*noteScale;
                    sendChangeMessage(this);
                }
                else if (midi_message.isController())
                {
                    midilisten[i] = 0;
                    Yoff[i]=midi_message.getControllerValue()*noteScale;
                    sendChangeMessage(this);
                }
            }
            // learn x
            else if (midilisten[i]==0.8f)
            {
                if (midi_message.isController())
                {
                    midilisten[i] = 0;
                    Xcc[i]=(midi_message.getControllerNumber())*noteScale;
                    sendChangeMessage(this);
                }
                else if (midi_message.isPitchWheel())
                {
                    midilisten[i] = 0;
                    UseXPB[i] = true;
                    sendChangeMessage(this);
                }
            }
            // learn x-off
            else if (midilisten[i]==0.7f)
            {
                if (midi_message.isController())
                {
                    midilisten[i] = 0;
                    Xoff[i]=(midi_message.getControllerValue())*noteScale;
                    sendChangeMessage(this);
                }
            }
            // learn trigger
            else if (midilisten[i]==0.6f)
            {
                if (midi_message.isNoteOn() && (midi_message.getVelocity() > 1)) {
                    midilisten[i] = 0;
                    trigger[i]=(midi_message.getNoteNumber())*noteScale;
                    sendChangeMessage(this);
                }
                //else if (midi_message.isController()) {
                //    midilisten[i] = 0;
                //    trigger[i]=(midi_message.getControllerNumber())*0.00787401574803149606299212598425197f;;
                //    sendChangeMessage(this);
                //}
            }
            //midi triggering
            else if (param[kUseTrigger]>=0.5f)
            {
                int inch = 1+(int)(param[kChIn]*15.1f);
                if (midi_message.isNoteOn() && (midi_message.getVelocity() > 1) && midi_message.isForChannel(inch))
                {        
                    if (param[kNoteOnTrig]>=0.5f && trigger[0]*127.1f)
                    {
                        trig=true;
                        triggervel=midi_message.getVelocity();
                        sendChangeMessage(this);
                    }
                    else if (midi_message.getNoteNumber() == (int)(trigger[i]*127.1f))
                    {
                        int note = (int)((Ydata1[i])*127.1);
                        if (Ytype[i]<0.5f)
                        {
                            if (isplaying[note])
                            {
                                MidiMessage off_message(0x80|outch,note,(int)((Yoff[i])*127.1),0); //noteoff
                                midiout.addEvent(off_message,0);
                            }
                            int vel;
                            if (param[kUseVel]>=0.5f) vel=(int)( (float)((midi_message.getVelocity())*(getParameter(kVelOffset)*2)) );
                            else vel = (int)(Ydata2[i]*127.1*(getParameter(kVelOffset)*2));
                            if (vel>127) vel=127;
                            else if (vel<1) vel=1;
                            MidiMessage output_message(0x90|outch,note,vel,0);
                            midiout.addEvent(output_message,sample_number); //noteon
                            isplaying[note]=true;
                            discard = true; //kill trigger message
                        }
                        else
                        {
                            int value = (int)(Ydata2[i]*127.1*(getParameter(kCCOffset)*2));
                            if (value>127) value=127;
                            else if (value<0) value=0;
                            MidiMessage output_message(0xB0|outch,(int)((Ycc[i])*127.1),value,0);
                            midiout.addEvent(output_message,sample_number); //on value
                            discard = true; //kill trigger message
                        }
                        triggered[i]=true;
                        trig=true;
                        sendChangeMessage(this);
                    }
                }
                else if ((midi_message.isNoteOff() || (midi_message.getVelocity()==0)) && midi_message.isForChannel(inch))
                {
                    if (midi_message.getNoteNumber() == (int)(trigger[i]*127.1f))
                    {
                        if (param[kNoteOnTrig]<0.5f)
                        {
                            if (Ytype[i]<0.5f)
                            {
                                MidiMessage output_message2(0x80|outch,(int)((Ydata1[i])*127.1),(int)((Yoff[i])*127.1),0);
                                midiout.addEvent(output_message2,sample_number); //noteoff
                                isplaying[(int)((Ydata1[i])*127.1)]=false;
                                discard = true; //kill trigger message                    
                            }
                            else
                            {
                                if (SendOff[i]) { // if sending cc off value
                                    MidiMessage output_message(0xB0|outch,(int)((Ydata1[i])*127.1),(int)((Yoff[i])*127.1),0);
                                    midiout.addEvent(output_message,sample_number); //off value
                                    discard = true; //kill trigger message
                                }
                            }
                            triggered[i]=false;
                            trig=true;
                            sendChangeMessage(this);
                        }
                    }
                }
            }
        }
        //if thru is on, copy original message
        if (!discard) midiout.addEvent(midi_message,sample_number);
    }

    //midi sending part
    for (int i = 0; i < jmax (1, (squares - squares % 2)); i++)
    {
        if (buttondown[i])
        {
            buttondown[i]=false;
            if (UseX[i]>=0.5f)
            {
                int value;
                if (UseXPB[i])
                {
                    value=roundFloatToInt( (param[i+xpos]*16383.0f)*(getParameter(kCCOffset)*2) );
                    if (value>0x3fff) value=0x3fff;
                    else if (value<0) value=0;
                    MidiMessage output_message(0xE0|outch,value & 0x007f,(value & 0x3f80)>>7,0);
                    midiout.addEvent(output_message,0);
                }
                else
                {
                    value=(int)( (param[i+xpos]*127.1)*(getParameter(kCCOffset)*2) );
                    if (value>127) value=127;
                    else if (value<0) value=0;
                    if (value!=lastxccvalue[i])
                    {
                        lastxccvalue[i]=value;
                        MidiMessage output_message(0xB0|outch,(int)(Xcc[i]*127.1),value,0);
                        midiout.addEvent(output_message,0);
                    }
                }
            }

            if (param[kSendAft]>=0.5f && Ytype[i]<0.5f)
            {
                int value;
                value=(int)(param[i+ypos]*127.1f);
                if (value>127) value=127;
                else if (value<0) value=0;
                MidiMessage output_message(0xA0|outch,(int)((Ydata1[i])*127.1),value,0);
                midiout.addEvent(output_message,0);
            }

            if (UseYCC[i] && Ytype[i]<0.5f)
            {
                int value;
                value=(int)( (param[i+ypos]*127.1)*(getParameter(kCCOffset)*2) );
                if (value>127) value=127;
                else if (value<0) value=0;
                if (value!=lastyccvalue[i])
                {
                    lastyccvalue[i]=value;
                    MidiMessage output_message(0xB0|outch,(int)((Ycc[i])*127.1),value,0);
                    midiout.addEvent(output_message,0);
                }
            }
        }

        if (send[i]>=0.5f)
        {
            send[i]=0;
            if (Ytype[i]<0.5f) // note
            {
                int vel;
                int note = (int)((Ydata1[i])*127.1);
                if (isplaying[note])
                {
                    //if (useaft>=0.5f) {
                    //    MidiMessage aft_message(0xA0|outch,note,0,0);
                    //    midiout.addEvent(aft_message,0);
                    //}
                    MidiMessage off_message(0x80|outch,note,(int)((Yoff[i])*127.1),0); //noteoff
                    midiout.addEvent(off_message,0);
                }
                if (param[kMono]>=0.5f)
                { 
                    //mono mode: kill any playing notes before starting a new one
                    for (int n=0;n<128;n++)
                    {
                        if (isplaying[n])
                        {
                            MidiMessage off_message(0x80|outch,n,0,0); //noteoff
                            midiout.addEvent(off_message,0);
                            isplaying[n]=false;
                        }
                    }
                }

                if (param[kNoteOnTrig]>=0.5f) vel=(int)(triggervel*(getParameter(kVelOffset)*2));   
                else if (UseY[i]>=0.5f) vel=(int)( (param[i+ypos]*127.1)*(getParameter(kVelOffset)*2) );
                else vel = (int)(Ydata2[i]*127.1*(getParameter(kVelOffset)*2));

                if (vel>127) vel=127;
                else if (vel<0) vel=0;

                MidiMessage output_message(0x90|outch,note,vel,0);
                midiout.addEvent(output_message,1); //noteon
                isplaying[note] = true;

                if (param[kSendAft]>=0.5f)
                {
                    int value;
                    value=(int)(param[i+ypos]*127.1f);
                    if (value>127) value=127;
                    else if (value<0) value=0;
                    MidiMessage aft_message(0xA0|outch,note,value,0);
                    midiout.addEvent(aft_message,2);
                }
                if (UseYCC[i])
                {
                    int val;
                    if (UseY[i]>=0.5f) val=(int)( (param[i+ypos]*127.1)*(getParameter(kCCOffset)*2) );
                    else val = (int)(Ydata2[i]*127.1*(getParameter(kCCOffset)*2));
                    if (val>127) val=127;
                    else if (val<0) val=0;
                    if (val!=lastyccvalue[i]) {
                        lastyccvalue[i]=val;
                        MidiMessage aft_message(0xB0|outch,(int)(Ycc[i]*127.1f),val,0);
                        midiout.addEvent(aft_message,2);
                    }
                }
            }
            else //CC
            {
                int value;
                if (UseY[i]>=0.5f)
                {
                    value=(int)( (param[i+ypos]*127.1f)*(getParameter(kCCOffset)*2) );
                    if (value>127) value=127;
                    else if (value<0) value=0;
                    if (value!=lastyccvalue[i])
                    {
                        lastyccvalue[i]=value;
                        MidiMessage output_message(0xB0|outch,(int)((Ycc[i])*127.1),value,0);
                        midiout.addEvent(output_message,0);
                    }
                }
                else
                {
                    value = (int)(Ydata2[i]*127.1*(getParameter(kCCOffset)*2));
                    if (value>127) value=127;
                    else if (value<0) value=0;
                    MidiMessage output_message(0xB0|outch,(int)((Ycc[i])*127.1),value,0);
                    midiout.addEvent(output_message,0); //on value
                }
            }
        }
        else if (sendoff[i]>=0.5f)
        {
            sendoff[i]=0;
            if (UseX[i]>=0.5 && SendOff[i])
            {
                if (UseXPB[i])
                {
                    MidiMessage output_message(0xE0|outch,0,(int)((Xoff[i])*127.1),0);
                    midiout.addEvent(output_message,0); //x-off value
                }
                else
                {
                    MidiMessage output_message(0xB0|outch,(int)((Xcc[i])*127.1),(int)((Xoff[i])*127.1),0);
                    midiout.addEvent(output_message,0); //x-off value
                }
            }
            if (Ytype[i]<0.5f)
            {
                int note = (int)((Ydata1[i])*127.1);
                if (param[kSendAft]>=0.5f)
                {
                    MidiMessage aft_message(0xA0|outch,note,0,0);
                    midiout.addEvent(aft_message,0);
                }
                if (UseYCC[i] && SendOff[i])
                {
                    MidiMessage output_message(0xB0|outch,(int)((Ycc[i])*127.1),(int)((Yoff[i])*127.1),0);
                    midiout.addEvent(output_message,0); //y-off value
                }
                MidiMessage output_message2(0x80|outch,note,(int)((Yoff[i])*127.1),0);
                midiout.addEvent(output_message2,0); //noteoff
                isplaying[note]=false;
            }
            else
            {
                if (SendOff[i])
                {
                    MidiMessage output_message(0xB0|outch,(int)((Ycc[i])*127.1),(int)((Yoff[i])*127.1),0);
                    midiout.addEvent(output_message,0); //y-off value
                }
            }
        }
    }

    midiMessages->clear();
    *midiMessages = midiout;
}

//==============================================================================
float MidiPadsPlugin::getParameter (int index) 
{
    return param[index];
}

void MidiPadsPlugin::setParameter (int index, float newValue) 
{
    MidiPadsProgram* ap = &programs[curProgram];

    if (param[index] != newValue) {
        param[index] = ap->param[index] = newValue;
        if (index>=xpos) {
            if (index>=ypos) {
                buttondown[index-ypos]=true;
                dotmoved[index-ypos]=true;
            }
            else {
                buttondown[index-xpos]=true;
                dotmoved[index-xpos]=true;
            }
        }
        sendChangeMessage (this);
    }
}

const String MidiPadsPlugin::getParameterName (int index) 
{
    for (int i = 0; i < numPads; i++)
    {
             if (index == i + xpos) return T("x pos ") + String(i+1);
        else if (index == i + ypos) return T("y pos ") + String(i+1);
    }
    
    switch (index)
    {
        case kVelOffset:    return T("velocity");           break;
        case kCCOffset:     return T("ccvalue");            break;
        case kChOut:        return T("out channel");        break;
        case kMono:         return T("mono mode");          break;
        case kUseTrigger:   return T("use trigger");        break;
        case kNoteOnTrig:   return T("ext noteon trig");    break;
        case kUseVel:       return T("use trig vel");       break;
        case kChIn:         return T("in channel");         break;
        case kThru:         return T("midi thru");          break;
        case kSendAft:      return T("send aftertouch");    break;
    }
    
    return String::empty;
}

//==============================================================================
int MidiPadsPlugin::getCurrentProgram()
{
    return curProgram;
}

void MidiPadsPlugin::setCurrentProgram (int index)
{
    //save non-parameter info to the old program, except the first time
    if (! init)
    {
        programs[curProgram].bghue = bghue;
        programs[curProgram].bgsat = bgsat;
        programs[curProgram].bgbri = bgbri;
        programs[curProgram].contrast = contrast;
        programs[curProgram].lastUIHeight = lastUIHeight;
        programs[curProgram].lastUIWidth = lastUIWidth;
        programs[curProgram].showdots = showdots;
        programs[curProgram].squares = squares;
        programs[curProgram].editmode = editmode;
        programs[curProgram].roundness = roundness;
        programs[curProgram].hex = hex;
        programs[curProgram].usemouseup = usemouseup;

        for (int i = 0; i < programs[curProgram].squares; i++)
        {
            programs[curProgram].icon[i] = icon[i];
            programs[curProgram].text[i] = text[i];
            programs[curProgram].padcolor[i] = padcolor[i];
            programs[curProgram].Ydata1[i]   = Ydata1[i];
            programs[curProgram].Ycc[i]   = Ycc[i];
            programs[curProgram].Ytype[i] = Ytype[i];
            programs[curProgram].Ydata2[i]  = Ydata2[i];
            programs[curProgram].Yoff[i]  = Yoff[i];
            programs[curProgram].trigger[i]  = trigger[i];
            programs[curProgram].Xcc[i]  = Xcc[i];
            programs[curProgram].Xoff[i]  = Xoff[i];
            programs[curProgram].SendOff[i]  = SendOff[i];
            programs[curProgram].UseX[i]  = UseX[i];
            programs[curProgram].UseY[i]  = UseY[i];
            programs[curProgram].UseYCC[i]  = UseYCC[i];
            programs[curProgram].UseXPB[i]  = UseXPB[i];
            programs[curProgram].lastx[i]  = lastx[i];
            programs[curProgram].lasty[i]  = lasty[i];
            programs[curProgram].toggle[i] = toggle[i];
            programs[curProgram].togglestate[i] = togglestate[i];
        }

        init = false;
    }

    //then set the new program
    curProgram = index;

	MidiPadsProgram* ap = &programs[index];
    for (int i = 0; i < getNumParameters(); i++)
    {
        param[i] = ap->param[i];
    }

    squares = ap->squares;
    lastUIWidth = ap->lastUIWidth;
    lastUIHeight = ap->lastUIHeight;

    for (int i = 0; i < squares; i++)
    {
        icon[i] = ap->icon[i];
        text[i] = ap->text[i];
        padcolor[i] = ap->padcolor[i];
        Ydata1[i]   = ap->Ydata1[i];
        Ycc[i]   = ap->Ycc[i];
        Ytype[i] = ap->Ytype[i];
        Ydata2[i]  = ap->Ydata2[i];
        Yoff[i]  = ap->Yoff[i];
        trigger[i]  = ap->trigger[i];
        Xcc[i]  = ap->Xcc[i];
        SendOff[i]  = ap->SendOff[i];
        UseX[i]  = ap->UseX[i];
        UseY[i]  = ap->UseY[i];
        UseYCC[i]  = ap->UseYCC[i];
        UseXPB[i]  = ap->UseXPB[i];
        lastx[i]  = ap->lastx[i];
        lasty[i]  = ap->lasty[i];
        toggle[i] = ap->toggle[i];
        togglestate[i] = ap->togglestate[i];
    }
    
    bghue = ap->bghue;
    bgsat = ap->bgsat;
    bgbri = ap->bgbri;
    contrast = ap->contrast;
    showdots = ap->showdots;
    editmode = ap->editmode;
    roundness = ap->roundness;
    usemouseup = ap->usemouseup;
    hex = ap->hex;

    sendChangeMessage (this);
}

void MidiPadsPlugin::changeProgramName (int index, const String &newName)
{
    programs[curProgram].name = newName;
}

const String MidiPadsPlugin::getProgramName (int index)
{
    return programs[index].name;
}

//==============================================================================
void MidiPadsPlugin::getCurrentProgramStateInformation (MemoryBlock& destData)
{
    // make sure the non-parameter settings are copied to the current program
    programs[curProgram].bghue = bghue;
    programs[curProgram].bgsat = bgsat;
    programs[curProgram].bgbri = bgbri;
    programs[curProgram].contrast = contrast;
    programs[curProgram].lastUIHeight = lastUIHeight;
    programs[curProgram].lastUIWidth = lastUIWidth;
    programs[curProgram].showdots = showdots;
    programs[curProgram].squares = squares;
    programs[curProgram].editmode = editmode;
    programs[curProgram].roundness = roundness;
    programs[curProgram].hex = hex;
    programs[curProgram].usemouseup = usemouseup;
    for (int i = 0; i < programs[curProgram].squares; i++)
    {
        programs[curProgram].icon[i] = icon[i];
        programs[curProgram].text[i] = text[i];
        programs[curProgram].padcolor[i] = padcolor[i];
        programs[curProgram].Ydata1[i]   = Ydata1[i];
        programs[curProgram].Ycc[i]   = Ycc[i];
        programs[curProgram].Ytype[i] = Ytype[i];
        programs[curProgram].Ydata2[i]  = Ydata2[i];
        programs[curProgram].Yoff[i]  = Yoff[i];
        programs[curProgram].trigger[i]  = trigger[i];
        programs[curProgram].Xcc[i]  = Xcc[i];
        programs[curProgram].Xoff[i]  = Xoff[i];
        programs[curProgram].SendOff[i]  = SendOff[i];
        programs[curProgram].UseX[i]  = UseX[i];
        programs[curProgram].UseY[i]  = UseY[i];
        programs[curProgram].UseYCC[i]  = UseYCC[i];
        programs[curProgram].UseXPB[i]  = UseXPB[i];
        programs[curProgram].lastx[i]  = lastx[i];
        programs[curProgram].lasty[i]  = lasty[i];
        programs[curProgram].toggle[i] = toggle[i];
        programs[curProgram].togglestate[i] = togglestate[i];
    }
    // you can store your parameters as binary data if you want to or if you've got
    // a load of binary to put in there, but if you're not doing anything too heavy,
    // XML is a much cleaner way of doing it - here's an example of how to store your
    // params as XML..

    // create an outer XML element..
    XmlElement xmlState (T("MYPLUGINSETTINGS"));

    // add some attributes to it..
    xmlState.setAttribute (T("pluginVersion"), 1);

    xmlState.setAttribute (T("program"), getCurrentProgram());
    xmlState.setAttribute (T("progname"), getProgramName (getCurrentProgram()));

    for (int i = 0; i < kNumGlobalParams; i++)
    {
        xmlState.setAttribute (String(i), param[i]);
    }

    xmlState.setAttribute (T("uiWidth"), lastUIWidth);
    xmlState.setAttribute (T("uiHeight"), lastUIHeight);
    xmlState.setAttribute (T("Hue"), bghue);
    xmlState.setAttribute (T("Sat"), bgsat);
    xmlState.setAttribute (T("Bri"), bgbri);
    xmlState.setAttribute (T("Contrast"), contrast);
    xmlState.setAttribute (T("squares"), squares);
    xmlState.setAttribute (T("showdots"), showdots);
    xmlState.setAttribute (T("editmode"), editmode);
    xmlState.setAttribute (T("roundness"), roundness);
    xmlState.setAttribute (T("hex"), hex);
    xmlState.setAttribute (T("usemouseup"), usemouseup);
    for (int i = 0; i < numPads; i++)
    {
        xmlState.setAttribute (T("icon")+String(i), icon[i]);
        xmlState.setAttribute (T("text")+String(i), text[i]);
        xmlState.setAttribute (T("padcolor")+String(i), (int)(padcolor[i].getARGB()));
        xmlState.setAttribute (T("Ydata1")+String(i), Ydata1[i]);
        xmlState.setAttribute (T("Ycc")+String(i), Ycc[i]);
        xmlState.setAttribute (T("Ytype")+String(i), Ytype[i]);
        xmlState.setAttribute (T("Ydata2")+String(i), Ydata2[i]);
        xmlState.setAttribute (T("Yoff")+String(i), Yoff[i]);
        xmlState.setAttribute (T("trigger")+String(i), trigger[i]);
        xmlState.setAttribute (T("Xcc")+String(i), Xcc[i]);
        xmlState.setAttribute (T("Xoff")+String(i), Xoff[i]);
        xmlState.setAttribute (T("SendOff")+String(i), SendOff[i]);
        xmlState.setAttribute (T("UseX")+String(i), UseX[i]);
        xmlState.setAttribute (T("UseY")+String(i), UseY[i]);
        xmlState.setAttribute (T("UseYCC")+String(i), UseYCC[i]);
        xmlState.setAttribute (T("UseXPB")+String(i), UseXPB[i]);
        xmlState.setAttribute (T("lastx")+String(i), lastx[i]);
        xmlState.setAttribute (T("lasty")+String(i), lasty[i]);
        xmlState.setAttribute (T("toggle")+String(i), toggle[i]);
        xmlState.setAttribute (T("togglestate")+String(i), togglestate[i]);
    }

    // then use this helper function to stuff it into the binary blob and return it..
    copyXmlToBinary (xmlState, destData);
}

void MidiPadsPlugin::getStateInformation (MemoryBlock &destData)
{
    // make sure the non-parameter settings are copied to the current program
    programs[curProgram].bghue = bghue;
    programs[curProgram].bgsat = bgsat;
    programs[curProgram].bgbri = bgbri;
    programs[curProgram].contrast = contrast;
    programs[curProgram].lastUIHeight = lastUIHeight;
    programs[curProgram].lastUIWidth = lastUIWidth;
    programs[curProgram].showdots = showdots;
    programs[curProgram].squares = squares;
    programs[curProgram].editmode = editmode;
    programs[curProgram].roundness = roundness;
    programs[curProgram].usemouseup = usemouseup;
    programs[curProgram].hex = hex;
    for (int i = 0; i < programs[curProgram].squares; i++)
    {
        programs[curProgram].icon[i] = icon[i];
        programs[curProgram].text[i] = text[i];
        programs[curProgram].padcolor[i] = padcolor[i];
        programs[curProgram].Ydata1[i] = Ydata1[i];
        programs[curProgram].Ycc[i] = Ycc[i];
        programs[curProgram].Ytype[i] = Ytype[i];
        programs[curProgram].Ydata2[i] = Ydata2[i];
        programs[curProgram].Yoff[i] = Yoff[i];
        programs[curProgram].trigger[i] = trigger[i];
        programs[curProgram].Xcc[i] = Xcc[i];
        programs[curProgram].Xoff[i] = Xoff[i];
        programs[curProgram].SendOff[i] = SendOff[i];
        programs[curProgram].UseX[i] = UseX[i];
        programs[curProgram].UseY[i] = UseY[i];
        programs[curProgram].UseYCC[i] = UseYCC[i];
        programs[curProgram].UseXPB[i] = UseXPB[i];
        programs[curProgram].lastx[i] = lastx[i];
        programs[curProgram].lasty[i] = lasty[i];
        programs[curProgram].toggle[i] = toggle[i];
        programs[curProgram].togglestate[i] = togglestate[i];
    }

    XmlElement xmlState (T("MYPLUGINSETTINGS"));
    xmlState.setAttribute (T("pluginVersion"), 1);
    xmlState.setAttribute (T("program"), getCurrentProgram());
    for (int p = 0; p < getNumPrograms(); p++)
    {
        String prefix = T("P") + String(p) + T("_");
        xmlState.setAttribute (prefix+T("progname"), programs[p].name);
        for (int i = 0; i < kNumGlobalParams; i++)
        {
            xmlState.setAttribute (prefix+String(i), programs[p].param[i]);
        }
        xmlState.setAttribute (prefix+T("uiWidth"), programs[p].lastUIWidth);
        xmlState.setAttribute (prefix+T("uiHeight"), programs[p].lastUIHeight);
        xmlState.setAttribute (prefix+T("Hue"), programs[p].bghue);
        xmlState.setAttribute (prefix+T("Sat"), programs[p].bgsat);
        xmlState.setAttribute (prefix+T("Bri"), programs[p].bgbri);
        xmlState.setAttribute (prefix+T("Contrast"), programs[p].contrast);
        xmlState.setAttribute (prefix+T("squares"), programs[p].squares);
        xmlState.setAttribute (prefix+T("showdots"), programs[p].showdots);
        xmlState.setAttribute (prefix+T("editmode"), programs[p].editmode);
        xmlState.setAttribute (prefix+T("roundness"), programs[p].roundness);
        xmlState.setAttribute (prefix+T("hex"), programs[p].hex);
        xmlState.setAttribute (prefix+T("usemouseup"), programs[p].usemouseup);
        for (int i = 0; i < programs[p].squares; i++)
        {
            xmlState.setAttribute (prefix+T("icon")+String(i), programs[p].icon[i]);
            xmlState.setAttribute (prefix+T("text")+String(i), programs[p].text[i]);
            xmlState.setAttribute (prefix+T("padcolor")+String(i), (int)(programs[p].padcolor[i].getARGB()));
            xmlState.setAttribute (prefix+T("Ydata1")+String(i), programs[p].Ydata1[i]);
            xmlState.setAttribute (prefix+T("Ycc")+String(i), programs[p].Ycc[i]);
            xmlState.setAttribute (prefix+T("Ytype")+String(i), programs[p].Ytype[i]);
            xmlState.setAttribute (prefix+T("Ydata2")+String(i), programs[p].Ydata2[i]);
            xmlState.setAttribute (prefix+T("Yoff")+String(i), programs[p].Yoff[i]);
            xmlState.setAttribute (prefix+T("trigger")+String(i), programs[p].trigger[i]);
            xmlState.setAttribute (prefix+T("Xcc")+String(i), programs[p].Xcc[i]);
            xmlState.setAttribute (prefix+T("Xoff")+String(i), programs[p].Xoff[i]);
            xmlState.setAttribute (prefix+T("SendOff")+String(i), programs[p].SendOff[i]);
            xmlState.setAttribute (prefix+T("UseX")+String(i), programs[p].UseX[i]);
            xmlState.setAttribute (prefix+T("UseY")+String(i), programs[p].UseY[i]);
            xmlState.setAttribute (prefix+T("UseYCC")+String(i), programs[p].UseYCC[i]);
            xmlState.setAttribute (prefix+T("UseXPB")+String(i), programs[p].UseXPB[i]);
            xmlState.setAttribute (prefix+T("lastx")+String(i), programs[p].lastx[i]);
            xmlState.setAttribute (prefix+T("lasty")+String(i), programs[p].lasty[i]);
            xmlState.setAttribute (prefix+T("toggle")+String(i), programs[p].toggle[i]);
            xmlState.setAttribute (prefix+T("togglestate")+String(i), programs[p].togglestate[i]);
        }
    }
    copyXmlToBinary (xmlState, destData);
}

void MidiPadsPlugin::setCurrentProgramStateInformation (const void* data, int sizeInBytes)
{
    // use this helper function to get the XML from this binary blob..
    XmlElement* const xmlState = getXmlFromBinary (data, sizeInBytes);

    if (xmlState != 0)
    {
        // check that it's the right type of xml..
        if (xmlState->hasTagName (T("MYPLUGINSETTINGS")))
        {
            // ok, now pull out our parameters..
            changeProgramName (getCurrentProgram (), xmlState->getStringAttribute (T("progname"), T("Default")));
            for (int i = 0; i < kNumGlobalParams; i++)
            {
                param[i] = (float) xmlState->getDoubleAttribute (String(i), param[i]);
            }
            lastUIWidth = xmlState->getIntAttribute (T("uiWidth"), lastUIWidth);
            lastUIHeight = xmlState->getIntAttribute (T("uiHeight"), lastUIHeight);
            bghue = (float) xmlState->getDoubleAttribute (T("Hue"), bghue);
            bgsat = (float) xmlState->getDoubleAttribute (T("Sat"), bgsat);
            bgbri = (float) xmlState->getDoubleAttribute (T("Bri"), bgbri);
            contrast = (float) xmlState->getDoubleAttribute (T("Contrast"), contrast);
            squares = xmlState->getIntAttribute (T("squares"), squares);
            showdots = xmlState->getBoolAttribute (T("showdots"), showdots);
            editmode = xmlState->getBoolAttribute (T("editmode"), editmode);
            roundness = (float) xmlState->getDoubleAttribute (T("roundness"), roundness);
            hex = xmlState->getBoolAttribute (T("hex"), hex);
            usemouseup = xmlState->getBoolAttribute (T("usemouseup"), usemouseup);

            for (int i=0;i<squares;i++) {
                icon[i] = xmlState->getStringAttribute (T("icon")+String(i), icon[i]);
                text[i] = xmlState->getStringAttribute (T("text")+String(i), text[i]);
                padcolor[i] = Colour(xmlState->getIntAttribute (T("padcolor")+String(i), padcolor[i].getARGB()));
                Ydata1[i] = (float) xmlState->getDoubleAttribute (T("Ydata1")+String(i), Ydata1[i]);
                Ycc[i] = (float) xmlState->getDoubleAttribute (T("Ycc")+String(i), Ycc[i]);
                Ytype[i] = (float) xmlState->getDoubleAttribute (T("Ytype")+String(i), Ytype[i]);
                Ydata2[i] = (float) xmlState->getDoubleAttribute (T("Ydata2")+String(i), Ydata2[i]);
                Yoff[i] = (float) xmlState->getDoubleAttribute (T("Yoff")+String(i), Yoff[i]);
                trigger[i] = (float) xmlState->getDoubleAttribute (T("trigger")+String(i), trigger[i]);
                Xcc[i] = (float) xmlState->getDoubleAttribute (T("Xcc")+String(i), Xcc[i]);
                Xoff[i] = (float) xmlState->getDoubleAttribute (T("Xoff")+String(i), Xoff[i]);
                SendOff[i] = xmlState->getBoolAttribute (T("SendOff")+String(i), SendOff[i]);
                UseX[i] = (float) xmlState->getDoubleAttribute (T("UseX")+String(i), UseX[i]);
                UseY[i] = (float) xmlState->getDoubleAttribute (T("UseY")+String(i), UseY[i]);
                UseYCC[i] = xmlState->getBoolAttribute (T("UseYCC")+String(i), UseYCC[i]);
                UseXPB[i] = xmlState->getBoolAttribute (T("UseXPB")+String(i), UseXPB[i]);
                lastx[i] = xmlState->getIntAttribute (T("lastx")+String(i), lastx[i]);
                lasty[i] = xmlState->getIntAttribute (T("lasty")+String(i), lasty[i]);
                toggle[i] = xmlState->getBoolAttribute (T("toggle")+String(i), toggle[i]);
                togglestate[i] = xmlState->getBoolAttribute (T("togglestate")+String(i), togglestate[i]);
            }        
            sendChangeMessage (this);
        }
        delete xmlState;
    }
}

void MidiPadsPlugin::setStateInformation (const void* data, int sizeInBytes)
{
    XmlElement* const xmlState = getXmlFromBinary (data, sizeInBytes);

    if (xmlState != 0)
    {
        if (xmlState->hasTagName (T("MYPLUGINSETTINGS")))
        {
            for (int p = 0; p < getNumPrograms (); p++) {
                String prefix = T("P") + String(p) + T("_"); 
                for (int i = 0; i < kNumGlobalParams; i++)
                {
                    programs[p].param[i] = (float) xmlState->getDoubleAttribute (prefix+String(i), programs[p].param[i]);
                }
                programs[p].lastUIWidth = xmlState->getIntAttribute (prefix+T("uiWidth"), programs[p].lastUIWidth);
                programs[p].lastUIHeight = xmlState->getIntAttribute (prefix+T("uiHeight"), programs[p].lastUIHeight);
                programs[p].bghue = (float) xmlState->getDoubleAttribute (prefix+T("Hue"), programs[p].bghue);
                programs[p].bgsat = (float) xmlState->getDoubleAttribute (prefix+T("Sat"), programs[p].bgsat);
                programs[p].bgbri = (float) xmlState->getDoubleAttribute (prefix+T("Bri"), programs[p].bgbri);
                programs[p].contrast = (float) xmlState->getDoubleAttribute (prefix+T("Contrast"), programs[p].contrast);
                programs[p].squares = xmlState->getIntAttribute (prefix+T("squares"), programs[p].squares);
                programs[p].showdots = xmlState->getBoolAttribute (prefix+T("showdots"), programs[p].showdots);
                programs[p].editmode = xmlState->getBoolAttribute (prefix+T("editmode"), programs[p].editmode);
                programs[p].roundness = (float) xmlState->getDoubleAttribute (prefix+T("roundness"), programs[p].roundness);
                programs[p].hex = xmlState->getBoolAttribute (prefix+T("hex"), programs[p].hex);
                programs[p].usemouseup = xmlState->getBoolAttribute (prefix+T("usemouseup"), programs[p].usemouseup);
                for (int i = 0; i < programs[p].squares; i++)
                {
                    programs[p].icon[i] = xmlState->getStringAttribute (prefix+T("icon")+String(i), programs[p].icon[i]);
                    programs[p].text[i] = xmlState->getStringAttribute (prefix+T("text")+String(i), programs[p].text[i]);
                    programs[p].padcolor[i] = Colour(xmlState->getIntAttribute(prefix+T("padcolor")+String(i), programs[p].padcolor[i].getARGB()));
                    programs[p].Ydata1[i] = (float) xmlState->getDoubleAttribute (prefix+T("Ydata1")+String(i), programs[p].Ydata1[i]);
                    programs[p].Ycc[i] = (float) xmlState->getDoubleAttribute (prefix+T("Ycc")+String(i), programs[p].Ycc[i]);
                    programs[p].Ytype[i] = (float) xmlState->getDoubleAttribute (prefix+T("Ytype")+String(i), programs[p].Ytype[i]);
                    programs[p].Ydata2[i] = (float) xmlState->getDoubleAttribute (prefix+T("Ydata2")+String(i), programs[p].Ydata2[i]);
                    programs[p].Yoff[i] = (float) xmlState->getDoubleAttribute (prefix+T("Yoff")+String(i), programs[p].Yoff[i]);
                    programs[p].trigger[i] = (float) xmlState->getDoubleAttribute (prefix+T("trigger")+String(i), programs[p].trigger[i]);
                    programs[p].Xcc[i] = (float) xmlState->getDoubleAttribute (prefix+T("Xcc")+String(i), programs[p].Xcc[i]);
                    programs[p].Xoff[i] = (float) xmlState->getDoubleAttribute (prefix+T("Xoff")+String(i), programs[p].Xoff[i]);
                    programs[p].SendOff[i] = xmlState->getBoolAttribute (prefix+T("SendOff")+String(i), programs[p].SendOff[i]);
                    programs[p].UseX[i] = (float) xmlState->getDoubleAttribute (prefix+T("UseX")+String(i), programs[p].UseX[i]);
                    programs[p].UseY[i] = (float) xmlState->getDoubleAttribute (prefix+T("UseY")+String(i), programs[p].UseY[i]);
                    programs[p].UseYCC[i] = xmlState->getBoolAttribute (prefix+T("UseYCC")+String(i), programs[p].UseYCC[i]);
                    programs[p].UseXPB[i] = xmlState->getBoolAttribute (prefix+T("UseXPB")+String(i), programs[p].UseXPB[i]);
                    programs[p].lastx[i] = xmlState->getIntAttribute (prefix+T("lastx")+String(i), programs[p].lastx[i]);
                    programs[p].lasty[i] = xmlState->getIntAttribute (prefix+T("lasty")+String(i), programs[p].lasty[i]);
                    programs[p].toggle[i] = xmlState->getBoolAttribute (prefix+T("toggle")+String(i), programs[p].toggle[i]);
                    programs[p].togglestate[i] = xmlState->getBoolAttribute (prefix+T("togglestate")+String(i), programs[p].togglestate[i]);
                }
                programs[p].name = xmlState->getStringAttribute (prefix+T("progname"), programs[p].name);
            }
            init=true;
            setCurrentProgram (xmlState->getIntAttribute(T("program"), 0));
        }
        delete xmlState;
    }
}


//==============================================================================
AudioProcessorEditor* MidiPadsPlugin::createEditor ()
{
    return new MidiPadsPluginEditor (this);
}


