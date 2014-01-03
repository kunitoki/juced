/*  Freeverb3
 *
 *  Copyright (C) 2006 Teru KAMOGASHIRA
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef _FV3_DEFS_H
#define _FV3_DEFS_H

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define FV3_IR2_DEFAULT (0U)
#define FV3_IR2_MUTE_DRY (1U << 1)
#define FV3_IR2_MUTE_WET (1U << 2)
#define FV3_IR2_SKIP_FILTER (1U << 3)
#define FV3_IR2_MONO2STEREO (1U << 4)
#define FV3_IR2_SKIP_INIT (1U << 5)
#define FV3_IR2_ZERO_LATENCY (1U << 6)
#define FV3_IR2_SWAP_LR (1U << 7)

#define FV3_IR2_DFragmentSize 16384

#define FV3_IR3_DFragmentSize 1024
#define FV3_IR3_DefaultFactor 16

#define FV3_W_BLACKMAN 1
#define FV3_W_HANNING 2
#define FV3_W_HAMMING 3
#define FV3_W_KAISER 4
#define FV3_W_COSRO 5
#define FV3_W_SQUARE 6

#define FV3_3BSPLIT_IR_IR2 0
#define FV3_3BSPLIT_IR_IR3 1

#endif
