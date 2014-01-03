/* nekobee DSSI software synthesizer plugin and GUI
 *
 * Copyright (C) 2004 Sean Bolton and others.
 *
 * Portions of this file may have come from Steve Brookes'
 * nekobee, copyright (C) 1999 S. J. Brookes.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the Free
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307, USA.
 */

#ifndef _XSYNTH_PORTS_H
#define _XSYNTH_PORTS_H

#include "ladspa.h"

#define XSYNTH_PORT_OUTPUT		0
#define XSYNTH_PORT_WAVEFORM	1
#define XSYNTH_PORT_TUNING		2
#define XSYNTH_PORT_CUTOFF		3
#define XSYNTH_PORT_RESONANCE	4
#define XSYNTH_PORT_ENVMOD		5
#define XSYNTH_PORT_DECAY		6
#define XSYNTH_PORT_ACCENT		7
#define XSYNTH_PORT_VOLUME		8

#define XSYNTH_PORTS_COUNT  9

#define XSYNTH_PORT_TYPE_LINEAR       0
#define XSYNTH_PORT_TYPE_LOGARITHMIC  1
#define XSYNTH_PORT_TYPE_DETENT       2
#define XSYNTH_PORT_TYPE_ONOFF        3
#define XSYNTH_PORT_TYPE_VCF_MODE     4

struct nekobee_port_descriptor {

    LADSPA_PortDescriptor          port_descriptor;
    char *                         name;
    LADSPA_PortRangeHintDescriptor hint_descriptor;
    LADSPA_Data                    lower_bound;
    LADSPA_Data                    upper_bound;
    int                            type;
    float                          a, b, c;  /* scaling parameters for continuous controls */

};

extern struct nekobee_port_descriptor nekobee_port_description[];

#endif /* _XSYNTH_PORTS_H */
