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


#include <math.h>


#if defined(_WINDOWS)
#define _USE_MATH_DEFINES
#endif

#if defined(_WINDOWS) && !defined(DEF_ROUND)
#define DEF_ROUND 1
static inline double round(double val) { return floor(val + 0.5); }
#endif

#if defined(_WINDOWS) && !defined(DEF_ROUNDF)
#define DEF_ROUNDF 1
static inline float roundf(float val) { return floorf(val + 0.5); }
#endif

#if defined(_WINDOWS) && !defined(DEF_LOG2)
#define DEF_LOG2 1
static inline double log2(double val) { return log(val) / log(2.0); }
#endif
