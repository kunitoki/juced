/* nekobee DSSI software synthesizer plugin and GUI
 *
 * Copyright (C) 2004 Sean Bolton and others.
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

#include "nekobee_voice.h"

nekobee_patch_t nekobee_init_voice = {
    1.0f,	// tuning
	0,		// waveform
	5.0f,	// cutoff
    0.8f,	// resonance
	0.3f,	// envmod
	0.0002f, // decay
    0.3,	// accent
	0.75	// volume
};
