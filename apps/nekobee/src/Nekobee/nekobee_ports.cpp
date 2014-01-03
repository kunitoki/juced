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

#include "nekobee_ports.h"

struct nekobee_port_descriptor nekobee_port_description[XSYNTH_PORTS_COUNT] = {

#define PD_OUT     (LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO)
#define PD_IN      (LADSPA_PORT_INPUT | LADSPA_PORT_CONTROL)
#define HD_MIN     (LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_MINIMUM)
#define HD_LOW     (LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_LOW)
#define HD_MID     (LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_MIDDLE)
#define HD_HI      (LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_HIGH)
#define HD_MAX     (LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_MAXIMUM)
#define HD_440     (LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_DEFAULT_440)
#define HD_LOG     (LADSPA_HINT_LOGARITHMIC)
#define HD_DETENT  (LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_INTEGER | LADSPA_HINT_DEFAULT_MINIMUM)
#define HD_SWITCH  (LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE | LADSPA_HINT_INTEGER | LADSPA_HINT_TOGGLED )
#define XPT_LIN    XSYNTH_PORT_TYPE_LINEAR
#define XPT_LOG    XSYNTH_PORT_TYPE_LOGARITHMIC
#define XPT_DETE   XSYNTH_PORT_TYPE_DETENT
#define XPT_ONOFF  XSYNTH_PORT_TYPE_ONOFF
#define XPT_VCF    XSYNTH_PORT_TYPE_VCF_MODE
  {PD_OUT, "Output", 		0, 0.0f, 0.0f, 0, 0., 0., 0.},
  {PD_IN, "Waveform", 		HD_MIN, 0.0f, 1.0f, XPT_LIN, 0.01, 10., 0},
  {PD_IN, "Tuning", 		HD_MID | HD_LOG, 0.5f, 2.0f, XPT_LOG, 1., 1.33484, 2.},
  {PD_IN, "Cutoff Freq", 	HD_LOW, 0.0f, 40.0f, XPT_LIN, 25., 15.0, 0 /*.5*/},
  {PD_IN, "VCF Resonance", 	HD_LOW, 0.0f, .95f, XPT_LIN, 0.0001, 0.95, 0.},
  {PD_IN, "Env Mod", 		HD_MID, 0.0f, 1.0f, XPT_LIN, .5, .5, 0.},
  {PD_IN, "Decay",			HD_HI | HD_LOG, 0.000009f, 0.0005f, XPT_LOG, 0.0005, 3., -4.},
  {PD_IN, "Accent", 		HD_LOW, 0.0f, 1.0f, XPT_LIN, .5, .5, 0.},
  {PD_IN, "Volume", 		HD_MID, 0.0f, 1.0f, XPT_LIN, .01, 1, 0.},
#undef PD_OUT
#undef PD_IN
#undef HD_MIN
#undef HD_LOW
#undef HD_MAX
#undef HD_440
#undef HD_LOG
#undef HD_DETENT
#undef HD_SWITCH
#undef XPT_LIN
#undef XPT_LOG
#undef XPT_DETE
#undef XPT_ONOFF
#undef XPT_VCF
};
