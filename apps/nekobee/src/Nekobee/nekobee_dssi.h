/* nekobee DSSI software synthesizer plugin
 *
 * Copyright (C) 2004 Sean Bolton and others.
 *
 * Portions of this file may have come from Steve Brookes'
 * nekobee, copyright (C) 1999 S. J. Brookes.
 * Portions of this file may have come from Peter Hanappe's
 * Fluidsynth, copyright (C) 2003 Peter Hanappe and others.
 * Portions of this file may have come from Chris Cannam and Steve
 * Harris's public domain DSSI example code.
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <pthread.h>

#include "ladspa.h"
#include "dssi.h"

#include "nekobee_types.h"
#include "nekobee.h"
#include "nekobee_ports.h"
#include "nekobee_synth.h"
#include "nekobee_voice.h"

void nekobee_cleanup(LADSPA_Handle instance);
void nekobee_run_synth(LADSPA_Handle instance, unsigned long sample_count,
                       snd_seq_event_t *events, unsigned long event_count);

/* ---- LADSPA interface ---- */

/*
 * nekobee_instantiate
 *
 * implements LADSPA (*instantiate)()
 */
LADSPA_Handle
nekobee_instantiate(const LADSPA_Descriptor *descriptor, unsigned long sample_rate);

/*
 * nekobee_connect_port
 *
 * implements LADSPA (*connect_port)()
 */
void
nekobee_connect_port(LADSPA_Handle instance, unsigned long port, LADSPA_Data *data);

/*
 * nekobee_activate
 *
 * implements LADSPA (*activate)()
 */
void
nekobee_activate(LADSPA_Handle instance);

/*
 * nekobee_ladspa_run_wrapper
 *
 * implements LADSPA (*run)() by calling nekobee_run_synth() with no events
 */
void
nekobee_ladspa_run_wrapper(LADSPA_Handle instance, unsigned long sample_count);

/*
 * nekobee_deactivate
 *
 * implements LADSPA (*deactivate)()
 */
void
nekobee_deactivate(LADSPA_Handle instance);

/*
 * nekobee_cleanup
 *
 * implements LADSPA (*cleanup)()
 */
void
nekobee_cleanup(LADSPA_Handle instance);

/*
 * dssi_configure_message
 */
char *
dssi_configure_message(const char *fmt, ...);

/*
 * nekobee_configure
 *
 * implements DSSI (*configure)()
 */
char *
nekobee_configure(LADSPA_Handle instance, const char *key, const char *value);

/*
 * nekobee_get_program
 *
 * implements DSSI (*get_program)()
 */
const DSSI_Program_Descriptor *
nekobee_get_program(LADSPA_Handle instance, unsigned long index);

/*
 * nekobee_select_program
 *
 * implements DSSI (*select_program)()
 */
void
nekobee_select_program(LADSPA_Handle handle, unsigned long bank,
                       unsigned long program);

/*
 * dssp_handle_pending_program_change
 */
void
dssp_handle_pending_program_change(nekobee_synth_t *synth);

/*
 * nekobee_get_midi_controller
 *
 * implements DSSI (*get_midi_controller_for_port)()
 */
int
nekobee_get_midi_controller(LADSPA_Handle instance, unsigned long port);

/*
 * nekobee_handle_event
 */
void
nekobee_handle_event(nekobee_synth_t *synth, snd_seq_event_t *event);

/*
 * nekobee_run_synth
 *
 * implements DSSI (*run_synth)()
 */
void
nekobee_run_synth(LADSPA_Handle instance, unsigned long sample_count,
                  snd_seq_event_t *events, unsigned long event_count);

/* ---- export ---- */

const LADSPA_Descriptor *ladspa_descriptor(unsigned long index);
const DSSI_Descriptor *dssi_descriptor(unsigned long index);
void _init_dssi();
void _fini_dssi();

