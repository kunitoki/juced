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


#ifndef __PARAMPARTITIONWISDOM_H__
#define __PARAMPARTITIONWISDOM_H__


enum CONST_PARAMPARTITIONWISDOM {
    NUM_PARTITIONWISDOM_ENTRIES = 10
};


class ParamPartitionWisdom
{
public:
    ParamPartitionWisdom()
    {
        for (int i = 0; i < NUM_PARTITIONWISDOM_ENTRIES; i++)
        {
            t_const[i]  = 1.0;
            t_linear[i] = 1.0;
        }
    }

    ParamPartitionWisdom(const ParamPartitionWisdom &other)
    {
        for (int i = 0; i < NUM_PARTITIONWISDOM_ENTRIES; i++)
        {
            t_const[i]  = other.t_const[i];
            t_linear[i] = other.t_linear[i];
        }
    }

    ~ParamPartitionWisdom()
    {
    }

    ParamPartitionWisdom & operator = (const ParamPartitionWisdom &other)
    {
        for (int i = 0; i < NUM_PARTITIONWISDOM_ENTRIES; i++)
        {
            t_const[i]  = other.t_const[i];
            t_linear[i] = other.t_linear[i];
        }
        return *this;
    }

    double t_const[NUM_PARTITIONWISDOM_ENTRIES];
    double t_linear[NUM_PARTITIONWISDOM_ENTRIES];
};


#endif   // __PARAMPARTITIONWISDOM_H__
