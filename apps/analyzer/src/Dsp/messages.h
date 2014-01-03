//  ----------------------------------------------------------------------------
//
//  Copyright (C) 2004-2008 Fons Adriaensen <fons@kokkinizita.net>
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
//  ----------------------------------------------------------------------------


#ifndef __MESSAGES_H
#define __MESSAGES_H

#if 0

#include <clthreads.h>


#define  EV_MESG   0
#define  EV_X11    16
#define  EV_TRIG   29
#define  EV_JACK   30
#define  EV_EXIT   31

#define  MT_AUDIO  1
#define  MT_BUFFP  2
#define  MT_INPUT  3


class M_audio : public ITC_mesg
{
public:

    M_audio (int fsamp, int ncapt, int nplay, const char *name) :
        ITC_mesg (MT_AUDIO), _fsamp (fsamp), _ncapt (ncapt), _nplay (nplay), _name (name) {}

    int         _fsamp;
    int         _ncapt;
    int         _nplay;
    const char *_name;
};

class M_buffp : public ITC_mesg
{
public:

    M_buffp (float *dataA, float *dataB, int size, int step) : 
	ITC_mesg (MT_BUFFP), _dataA (dataA), _dataB (dataB), _size (size), _step (step) {}

    float    *_dataA;
    float    *_dataB;
    int       _size;
    int       _step;
};

class M_input : public ITC_mesg
{
public:

    M_input (int inputA, int inputB) :
        ITC_mesg (MT_INPUT), _inputA (inputA), _inputB (inputB) {}

    int       _inputA;
    int       _inputB;
};

#endif

#endif
