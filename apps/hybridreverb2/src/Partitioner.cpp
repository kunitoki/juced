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


#include "windows_quirks.h"
#include "Partitioner.h"
#include "ParamPreferences.h"
#include <math.h>
#include <stdio.h>


Partitioner::Partitioner(const ParamPartitionWisdom & wisdom)
    : paramPartitionWisdom(wisdom),
      type_best(PARTITION_TYPE_TRIPPLE),
      sflen_best(64),
      mflen_best(256),
      lflen_best(4096)
{
}

Partitioner::~Partitioner()
{
}


////////////////////////////////////////////////////////////////
//
//    public methods
//

void Partitioner::analyze(const int hlen, const int latency, const int strategy)
{
    const int f_s = 48000;

    int s, m, l, begin_m, end_m;
    int sflen, mflen, lflen;
    double cpu_load;
    double *c0 = &(paramPartitionWisdom.t_const[0]);
    double *c1 = &(paramPartitionWisdom.t_linear[0]);
    double tau_s, tau_m, tau_l;
    int num_s, num_m, num_l;

    s = (int)log2(latency) - 6;
    switch (strategy) {
    case STRATEGY_UNIFORM:
        begin_m = 2;
        end_m   = 3;
        break;
    default:
        begin_m = 1;
        end_m   = NUM_PARTITIONWISDOM_ENTRIES - s - 1;
    }
    sflen = latency;
    cpu_load_best = 1e12;

    // performance prediction with 3 segment lengths
    for (m = begin_m; m < end_m; m++)
    {
        for (l = 1; l+m+s < NUM_PARTITIONWISDOM_ENTRIES; l++)
        {
            mflen = sflen << m;
            lflen = mflen << l;
            num_s = mflen / sflen;
            num_m = 2 * lflen / mflen;
            num_l = ceil((hlen - num_s * sflen - num_m * mflen) / (double)lflen);
            if (num_l < 1)
                num_l = 1;
            tau_s = c0[s]     + c1[s]     * num_s;
            tau_m = c0[s+m]   + c1[s+m]   * num_m;
            tau_l = c0[s+m+l] + c1[s+m+l] * num_l;
            cpu_load = 400.0 * (tau_s * lflen / sflen + tau_m * lflen / mflen + tau_l) * f_s / (double)lflen;
            if (cpu_load < cpu_load_best)
            {
                cpu_load_best = cpu_load;
                sflen_best = sflen;
                mflen_best = mflen;
                lflen_best = lflen;
                type_best = PARTITION_TYPE_TRIPPLE;
            }
        }
    }

    // performance prediction with 2 segment lengths
    begin_m = 1;
    end_m   = NUM_PARTITIONWISDOM_ENTRIES - s;
    for (m = begin_m; m < end_m; m++)
    {
        mflen = sflen << m;
        num_s = 2 * mflen / sflen;
        num_m = ceil((hlen - num_s * sflen) / (double)mflen);
        if (num_m < 1)
            num_m = 1;
        tau_s = c0[s]   + c1[s]   * num_s;
        tau_m = c0[s+m] + c1[s+m] * num_m;
        cpu_load = 400.0 * (tau_s * mflen / sflen + tau_m) * f_s / (double)mflen;
        if (cpu_load < cpu_load_best)
        {
            cpu_load_best = cpu_load;
            sflen_best = sflen;
            mflen_best = mflen;
            type_best = PARTITION_TYPE_DUAL;
        }
    }

    // performance prediction with 1 segment length
    num_s = ceil(hlen / (double)sflen);
    tau_s = c0[s] + c1[s] * num_s;
    cpu_load = 400.0 * tau_s * f_s / (double)sflen;
    if (cpu_load < cpu_load_best)
    {
        cpu_load_best = cpu_load;
        sflen_best = sflen;
        type_best = PARTITION_TYPE_SINGLE;
    }

    switch (type_best) {
    case PARTITION_TYPE_TRIPPLE:
        printf("Best predicted CPU load (%d/%d/%d): \t%.2f %%\n", sflen_best, mflen_best, lflen_best, cpu_load_best);
        break;
    case PARTITION_TYPE_DUAL:
        printf("Best predicted CPU load (%d/%d): \t%.2f %%\n", sflen_best, mflen_best, cpu_load_best);
        break;
    case PARTITION_TYPE_SINGLE:
        printf("Best predicted CPU load (%d): \t%.2f %%\n", sflen_best, cpu_load_best);
        break;
    }
}


int Partitioner::getType()
{
    return type_best;
}


int Partitioner::getS()
{
    return sflen_best;
}


int Partitioner::getM()
{
    return mflen_best;
}


int Partitioner::getL()
{
    return lflen_best;
}
