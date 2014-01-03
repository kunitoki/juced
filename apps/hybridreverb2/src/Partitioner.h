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


#ifndef __PARTITIONER_H__
#define __PARTITIONER_H__


enum CONST_PARTITIONER {
    PARTITION_TYPE_SINGLE  = 1,
    PARTITION_TYPE_DUAL    = 2,
    PARTITION_TYPE_TRIPPLE = 3
};


#include "juce_amalgamated.h"
#include "ParamPartitionWisdom.h"


class Partitioner
{
public:
    Partitioner(const ParamPartitionWisdom & wisdom);
    ~Partitioner();

    void analyze(const int hlen, const int latency, const int strategy);
    int getType();
    int getS();
    int getM();
    int getL();


private:
    ParamPartitionWisdom paramPartitionWisdom;
    int type_best, sflen_best, mflen_best, lflen_best;
    double cpu_load_best;
};


#endif   // __PARTITIONER_H__
