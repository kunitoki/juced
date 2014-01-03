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

#include "nekobee_dssi.h"

static LADSPA_Descriptor *nekobee_LADSPA_descriptor = NULL;
static DSSI_Descriptor   *nekobee_DSSI_descriptor = NULL;

/* ---- mutual exclusion ---- */

inline int
dssp_voicelist_mutex_trylock(nekobee_synth_t *synth)
{
    int rc;

    /* Attempt the mutex lock */
    rc = pthread_mutex_trylock(&synth->voicelist_mutex);
    if (rc) {
        synth->voicelist_mutex_grab_failed = 1;
        return rc;
    }
    /* Clean up if a previous mutex grab failed */
    if (synth->voicelist_mutex_grab_failed) {
        nekobee_synth_all_voices_off(synth);
        synth->voicelist_mutex_grab_failed = 0;
    }
    return 0;
}

inline int
dssp_voicelist_mutex_lock(nekobee_synth_t *synth)
{
    return pthread_mutex_lock(&synth->voicelist_mutex);
}

inline int
dssp_voicelist_mutex_unlock(nekobee_synth_t *synth)
{
    return pthread_mutex_unlock(&synth->voicelist_mutex);
}

/* ---- LADSPA interface ---- */

/*
 * nekobee_instantiate
 *
 * implements LADSPA (*instantiate)()
 */
LADSPA_Handle
nekobee_instantiate(const LADSPA_Descriptor *descriptor, unsigned long sample_rate)
{
    nekobee_synth_t *synth = (nekobee_synth_t *)calloc(1, sizeof(nekobee_synth_t));
    if (!synth) return NULL;

        synth->voice = nekobee_voice_new(synth);
        if (!synth->voice) {

			// XDB_MESSAGE(-1, " nekobee_instantiate: out of memory!\n");
            nekobee_cleanup(synth);
            return NULL;
    }
    if (!(synth->patches = (nekobee_patch_t *)malloc(sizeof(nekobee_patch_t)))) {
        XDB_MESSAGE(-1, " nekobee_instantiate: out of memory!\n");
        nekobee_cleanup(synth);
        return NULL;
    }

    /* do any per-instance one-time initialization here */
    synth->sample_rate = sample_rate;
    synth->deltat = 1.0f / (float)synth->sample_rate;
    synth->polyphony = XSYNTH_DEFAULT_POLYPHONY;
    synth->voices = XSYNTH_DEFAULT_POLYPHONY;
    synth->monophonic = XSYNTH_MONO_MODE_ONCE;
    synth->glide = 0;
    synth->last_noteon_pitch = 0.0f;
    pthread_mutex_init(&synth->voicelist_mutex, NULL);
    synth->voicelist_mutex_grab_failed = 0;
    pthread_mutex_init(&synth->patches_mutex, NULL);
    synth->pending_program_change = -1;
    synth->current_program = -1;
// FIXME - all we really need to do is init the patch data once
    nekobee_data_friendly_patches(synth);
    nekobee_synth_init_controls(synth);

    return (LADSPA_Handle)synth;
}

/*
 * nekobee_connect_port
 *
 * implements LADSPA (*connect_port)()
 */
void
nekobee_connect_port(LADSPA_Handle instance, unsigned long port, LADSPA_Data *data)
{
    nekobee_synth_t *synth = (nekobee_synth_t *)instance;

    switch (port) {
      case XSYNTH_PORT_OUTPUT:			synth->output		= data;  break;
      case XSYNTH_PORT_WAVEFORM:		synth->waveform		= data;  break;
      case XSYNTH_PORT_TUNING:			synth->tuning		= data;  break;
	  case XSYNTH_PORT_CUTOFF:			synth->cutoff   = data;  break;
      case XSYNTH_PORT_RESONANCE:		synth->resonance        = data;  break;
      case XSYNTH_PORT_ENVMOD:			synth->envmod     = data;  break;
	  case XSYNTH_PORT_DECAY:			synth->decay     = data;  break;
	  case XSYNTH_PORT_ACCENT:			synth->accent     = data;  break;
	  case XSYNTH_PORT_VOLUME:			synth->volume     = data;  break;
      default:
        break;
    }
}

/*
 * nekobee_activate
 *
 * implements LADSPA (*activate)()
 */
void
nekobee_activate(LADSPA_Handle instance)
{
    nekobee_synth_t *synth = (nekobee_synth_t *)instance;

    synth->nugget_remains = 0;
    synth->note_id = 0;
    nekobee_synth_all_voices_off(synth);
}

/*
 * nekobee_ladspa_run_wrapper
 *
 * implements LADSPA (*run)() by calling nekobee_run_synth() with no events
 */
void
nekobee_ladspa_run_wrapper(LADSPA_Handle instance, unsigned long sample_count)
{
    nekobee_run_synth(instance, sample_count, NULL, 0);
}

// optional:
//  void (*run_adding)(LADSPA_Handle Instance,
//                     unsigned long SampleCount);
//  void (*set_run_adding_gain)(LADSPA_Handle Instance,
//                              LADSPA_Data   Gain);

/*
 * nekobee_deactivate
 *
 * implements LADSPA (*deactivate)()
 */
void
nekobee_deactivate(LADSPA_Handle instance)
{
    nekobee_synth_t *synth = (nekobee_synth_t *)instance;

    nekobee_synth_all_voices_off(synth);  /* stop all sounds immediately */
}

/*
 * nekobee_cleanup
 *
 * implements LADSPA (*cleanup)()
 */
void
nekobee_cleanup(LADSPA_Handle instance)
{
    nekobee_synth_t *synth = (nekobee_synth_t *)instance;
    if (! synth)
        return;

    //for (int i = 0; i < XSYNTH_MAX_POLYPHONY; i++)
    //    if (synth->voice[i]) free(synth->voice[i]);
	
	if (synth->voice) free(synth->voice);
    if (synth->patches) free(synth->patches);
    free(synth);
}

/* ---- DSSI interface ---- */

/*
 * dssi_configure_message
 */
char *
dssi_configure_message(const char *fmt, ...)
{
    va_list args;
    char buffer[256];

    va_start(args, fmt);
    vsnprintf(buffer, 256, fmt, args);
    va_end(args);
    return strdup(buffer);
}

/*
 * nekobee_configure
 *
 * implements DSSI (*configure)()
 */
char *
nekobee_configure(LADSPA_Handle instance, const char *key, const char *value)
{
    XDB_MESSAGE(XDB_DSSI, " nekobee_configure called with '%s' and '%s'\n", key, value);

    if (strlen(key) == 8 && !strncmp(key, "patches", 7)) {

//        return nekobee_synth_handle_patches((nekobee_synth_t *)instance, key, value);

  } else if (!strcmp(key, DSSI_PROJECT_DIRECTORY_KEY)) {

        return NULL; /* plugin has no use for project directory key, ignore it */

    } else if (!strcmp(key, "load")) {

        return dssi_configure_message("warning: host sent obsolete 'load' key with filename '%s'", value);

    }
    return strdup("error: unrecognized configure key");
}

/*
 * nekobee_get_program
 *
 * implements DSSI (*get_program)()
 */
const DSSI_Program_Descriptor *
nekobee_get_program(LADSPA_Handle instance, unsigned long index)
{
    nekobee_synth_t *synth = (nekobee_synth_t *)instance;
    static DSSI_Program_Descriptor pd;

    XDB_MESSAGE(XDB_DSSI, " nekobee_get_program called with %lu\n", index);

    if (index < 128) {
        nekobee_synth_set_program_descriptor(synth, &pd, 0, index);
        return &pd;
    }
    return NULL;
}

/*
 * nekobee_select_program
 *
 * implements DSSI (*select_program)()
 */
void
nekobee_select_program(LADSPA_Handle handle, unsigned long bank,
                      unsigned long program)
{
    nekobee_synth_t *synth = (nekobee_synth_t *)handle;

    XDB_MESSAGE(XDB_DSSI, " nekobee_select_program called with %lu and %lu\n", bank, program);

    /* ignore invalid program requests */
    if (bank || program >= 1)
        return;
    
    /* Attempt the patch mutex, return if lock fails. */
    if (pthread_mutex_trylock(&synth->patches_mutex)) {
        synth->pending_program_change = program;
        return;
    }

    nekobee_synth_select_program(synth, bank, program);

    pthread_mutex_unlock(&synth->patches_mutex);
}

/*
 * dssp_handle_pending_program_change
 */
inline void
dssp_handle_pending_program_change(nekobee_synth_t *synth)
{
    /* Attempt the patch mutex, return if lock fails. */
    if (pthread_mutex_trylock(&synth->patches_mutex))
        return;

    nekobee_synth_select_program(synth, 0, synth->pending_program_change);
    synth->pending_program_change = -1;

    pthread_mutex_unlock(&synth->patches_mutex);
}

/*
 * nekobee_get_midi_controller
 *
 * implements DSSI (*get_midi_controller_for_port)()
 */
int
nekobee_get_midi_controller(LADSPA_Handle instance, unsigned long port)
{
    XDB_MESSAGE(XDB_DSSI, " nekobee_get_midi_controller called for port %lu\n", port);
    switch (port) {
		case XSYNTH_PORT_TUNING:
			return DSSI_CC(MIDI_CTL_TUNING);
		case XSYNTH_PORT_WAVEFORM:
			return DSSI_CC(MIDI_CTL_WAVEFORM);
		case XSYNTH_PORT_CUTOFF:
	        return DSSI_CC(MIDI_CTL_CUTOFF);
		case XSYNTH_PORT_RESONANCE:
			return DSSI_CC(MIDI_CTL_RESONANCE);
		case XSYNTH_PORT_ENVMOD:
			return DSSI_CC(MIDI_CTL_ENVMOD);
		case XSYNTH_PORT_DECAY:
			return DSSI_CC(MIDI_CTL_DECAY);
		case XSYNTH_PORT_ACCENT:
			return DSSI_CC(MIDI_CTL_ACCENT);
		case XSYNTH_PORT_VOLUME:
			return DSSI_CC(MIDI_CTL_MSB_MAIN_VOLUME);
		
      default:
        break;
    }

    return DSSI_NONE;
}

/*
 * nekobee_handle_event
 */
inline void
nekobee_handle_event(nekobee_synth_t *synth, snd_seq_event_t *event)
{
    XDB_MESSAGE(XDB_DSSI, " nekobee_handle_event called with event type %d\n", event->type);

    switch (event->type) {
      case SND_SEQ_EVENT_NOTEOFF:
        nekobee_synth_note_off(synth, event->data.note.note, event->data.note.velocity);
        break;
      case SND_SEQ_EVENT_NOTEON:
        if (event->data.note.velocity > 0)
           nekobee_synth_note_on(synth, event->data.note.note, event->data.note.velocity);
        else
           nekobee_synth_note_off(synth, event->data.note.note, 64); /* shouldn't happen, but... */
        break;
      case SND_SEQ_EVENT_CONTROLLER:
        nekobee_synth_control_change(synth, event->data.control.param, event->data.control.value);
        break;

// somewhere in here we need to respond to NRPN
      default:
        break;
    }
}

/*
 * nekobee_run_synth
 *
 * implements DSSI (*run_synth)()
 */
void
nekobee_run_synth(LADSPA_Handle instance, unsigned long sample_count,
                 snd_seq_event_t *events, unsigned long event_count)
{
    nekobee_synth_t *synth = (nekobee_synth_t *)instance;
    unsigned long samples_done = 0;
    unsigned long event_index = 0;
    unsigned long burst_size;

    /* attempt the mutex, return only silence if lock fails. */
//    if (dssp_voicelist_mutex_trylock(synth)) {
//        memset(synth->output, 0, sizeof(LADSPA_Data) * sample_count);
//        return;
//    }

    if (synth->pending_program_change > -1)
        dssp_handle_pending_program_change(synth);

    while (samples_done < sample_count) {
        if (!synth->nugget_remains)
            synth->nugget_remains = XSYNTH_NUGGET_SIZE;

        /* process any ready events */
	while (event_index < event_count
	       && samples_done == events[event_index].time.tick) {
            nekobee_handle_event(synth, &events[event_index]);
            event_index++;
        }

        /* calculate the sample count (burst_size) for the next
         * nekobee_voice_render() call to be the smallest of:
         * - control calculation quantization size (XSYNTH_NUGGET_SIZE, in
         *     samples)
         * - the number of samples remaining in an already-begun nugget
         *     (synth->nugget_remains)
         * - the number of samples until the next event is ready
         * - the number of samples left in this run
         */
        burst_size = XSYNTH_NUGGET_SIZE;
        if (synth->nugget_remains < burst_size) {
            /* we're still in the middle of a nugget, so reduce the burst size
             * to end when the nugget ends */
            burst_size = synth->nugget_remains;
        }
        if (event_index < event_count
            && events[event_index].time.tick - samples_done < burst_size) {
            /* reduce burst size to end when next event is ready */
            burst_size = events[event_index].time.tick - samples_done;
        }
        if (sample_count - samples_done < burst_size) {
            /* reduce burst size to end at end of this run */
            burst_size = sample_count - samples_done;
        }

        /* render the burst */
        nekobee_synth_render_voices(synth, synth->output + samples_done, burst_size,
                                (burst_size == synth->nugget_remains));
        samples_done += burst_size;
        synth->nugget_remains -= burst_size;
    }
#if defined(XSYNTH_DEBUG) && (XSYNTH_DEBUG & XDB_AUDIO)
*synth->output += 0.10f; /* add a 'buzz' to output so there's something audible even when quiescent */
#endif /* defined(XSYNTH_DEBUG) && (XSYNTH_DEBUG & XDB_AUDIO) */

//    dssp_voicelist_mutex_unlock(synth);
}

// optional:
//    void (*run_synth_adding)(LADSPA_Handle    Instance,
//                             unsigned long    SampleCount,
//                             snd_seq_event_t *Events,
//                             unsigned long    EventCount);

/* ---- export ---- */

const LADSPA_Descriptor *ladspa_descriptor(unsigned long index)
{
    switch (index) {
    case 0:
        return nekobee_LADSPA_descriptor;
    default:
        return NULL;
    }
}

const DSSI_Descriptor *dssi_descriptor(unsigned long index)
{
    switch (index) {
    case 0:
        return nekobee_DSSI_descriptor;
    default:
        return NULL;
    }
}

void _init_dssi()
{
    int i;
    char **port_names;
    LADSPA_PortDescriptor *port_descriptors;
    LADSPA_PortRangeHint *port_range_hints;

    XSYNTH_DEBUG_INIT("nekobee-dssi.so");

    nekobee_init_tables();

    nekobee_LADSPA_descriptor =
        (LADSPA_Descriptor *) malloc(sizeof(LADSPA_Descriptor));
    if (nekobee_LADSPA_descriptor) {
        nekobee_LADSPA_descriptor->UniqueID = 2942;
        nekobee_LADSPA_descriptor->Label = "nekobee";
        nekobee_LADSPA_descriptor->Properties = 0;
        nekobee_LADSPA_descriptor->Name = "nekobee DSSI plugin";
        nekobee_LADSPA_descriptor->Maker = "Gordon JC Pearce - gordon@gjcp.net";
        nekobee_LADSPA_descriptor->Copyright = "GNU General Public License version 2 or later";
        nekobee_LADSPA_descriptor->PortCount = XSYNTH_PORTS_COUNT;

        port_descriptors = (LADSPA_PortDescriptor *)
                                calloc(nekobee_LADSPA_descriptor->PortCount, sizeof
                                                (LADSPA_PortDescriptor));
        nekobee_LADSPA_descriptor->PortDescriptors =
            (const LADSPA_PortDescriptor *) port_descriptors;

        port_range_hints = (LADSPA_PortRangeHint *)
                                calloc(nekobee_LADSPA_descriptor->PortCount, sizeof
                                                (LADSPA_PortRangeHint));
        nekobee_LADSPA_descriptor->PortRangeHints =
            (const LADSPA_PortRangeHint *) port_range_hints;

        port_names = (char **) calloc(nekobee_LADSPA_descriptor->PortCount, sizeof(char *));
        nekobee_LADSPA_descriptor->PortNames = (const char **) port_names;

        for (i = 0; i < XSYNTH_PORTS_COUNT; i++) {
            port_descriptors[i] = nekobee_port_description[i].port_descriptor;
            port_names[i]       = nekobee_port_description[i].name;
            port_range_hints[i].HintDescriptor = nekobee_port_description[i].hint_descriptor;
            port_range_hints[i].LowerBound     = nekobee_port_description[i].lower_bound;
            port_range_hints[i].UpperBound     = nekobee_port_description[i].upper_bound;
        }

        nekobee_LADSPA_descriptor->instantiate = nekobee_instantiate;
        nekobee_LADSPA_descriptor->connect_port = nekobee_connect_port;
        nekobee_LADSPA_descriptor->activate = nekobee_activate;
        nekobee_LADSPA_descriptor->run = nekobee_ladspa_run_wrapper;
        nekobee_LADSPA_descriptor->run_adding = NULL;
        nekobee_LADSPA_descriptor->set_run_adding_gain = NULL;
        nekobee_LADSPA_descriptor->deactivate = nekobee_deactivate;
        nekobee_LADSPA_descriptor->cleanup = nekobee_cleanup;
    }

    nekobee_DSSI_descriptor = (DSSI_Descriptor *) malloc(sizeof(DSSI_Descriptor));
    if (nekobee_DSSI_descriptor) {
        nekobee_DSSI_descriptor->DSSI_API_Version = 1;
        nekobee_DSSI_descriptor->LADSPA_Plugin = nekobee_LADSPA_descriptor;
        nekobee_DSSI_descriptor->configure = nekobee_configure;
        nekobee_DSSI_descriptor->get_program = nekobee_get_program;
        nekobee_DSSI_descriptor->select_program = nekobee_select_program;
        nekobee_DSSI_descriptor->get_midi_controller_for_port = nekobee_get_midi_controller;
        nekobee_DSSI_descriptor->run_synth = nekobee_run_synth;
        nekobee_DSSI_descriptor->run_synth_adding = NULL;
        nekobee_DSSI_descriptor->run_multiple_synths = NULL;
        nekobee_DSSI_descriptor->run_multiple_synths_adding = NULL;
    }
}

void _fini_dssi()
{
    if (nekobee_LADSPA_descriptor) {
        free((LADSPA_PortDescriptor *) nekobee_LADSPA_descriptor->PortDescriptors);
        free((char **) nekobee_LADSPA_descriptor->PortNames);
        free((LADSPA_PortRangeHint *) nekobee_LADSPA_descriptor->PortRangeHints);
        free(nekobee_LADSPA_descriptor);
    }
    if (nekobee_DSSI_descriptor) {
        free(nekobee_DSSI_descriptor);
    }
}

