/*  Reverb model tuning values
 *
 *  Copyright (C) 2000-2006 Jezar at Dreampoint, Teru KAMOGASHIRA
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

#ifndef _TUNING_H
#define _TUNING_H

const float muted		= 0.0f;
const float fixedgain		= 0.015f;
const float scalewet		= 3.0f;
const float scaledry		= 2.0f;
const float scaledamp		= 0.4f;
const float scaleroom		= 0.28f;
const float offsetroom		= 0.7f;
const float initialroom		= 0.5f;
const float initialdamp		= 0.5f;
const float initialwet	        = 1/scalewet;
const float initialdry		= 0.0f;
const float initialwidth	= 1.0f;
const int   stereospread441	= 23;

#endif
