/* nekobee DSSI software synthesizer GUI
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

#ifndef _GUI_DATA_H
#define _GUI_DATA_H

#include <stdio.h>

#include "nekobee_types.h"
#include "nekobee_voice.h"

#define XSYNTH_OLD_PATCH_SIZE_PACKED     209  /* Steve Brookes' original patch save file format */
#define XSYNTH_OLD_PATCH_SIZE_WITH_NAME  224  /* the above followed by 15 characters of name */

/* nekobee_data.c */
extern nekobee_patch_t nekobee_init_voice;

#endif /* _GUI_DATA_H */
