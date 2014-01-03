/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004 by Julian Storer.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the
   GNU General Public License, as published by the Free Software Foundation;
   either version 2 of the License, or (at your option) any later version.

   JUCE is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with JUCE; if not, visit www.gnu.org/licenses or write to the
   Free Software Foundation, Inc., 59 Temple Place, Suite 330,
   Boston, MA 02111-1307 USA

  ------------------------------------------------------------------------------

   If you'd like to release a closed-source product which uses JUCE, commercial
   licenses are also available: visit www.rawmaterialsoftware.com/juce for
   more information.

  ==============================================================================
*/

#ifndef __JUCETICE_XCOMPGLOBALS_HEADER__
#define __JUCETICE_XCOMPGLOBALS_HEADER__

// if we are running in demo mode !
// #define XCOMP_DEMO 1

REALTYPE *denormalkillbuf = 0;

#include "../../capsaicin/src/DSP/Filter.cpp"
#include "../../capsaicin/src/DSP/AnalogFilter.cpp"
#include "../../capsaicin/src/DSP/FormantFilter.cpp"
#include "../../capsaicin/src/DSP/SVFilter.cpp"

#include "../../capsaicin/src/Effects/Effect.cpp"
#include "../../capsaicin/src/Effects/EffectMgr.cpp"
#include "../../capsaicin/src/Effects/Alienwah.cpp"
#include "../../capsaicin/src/Effects/Chorus.cpp"
#include "../../capsaicin/src/Effects/Distorsion.cpp"
#include "../../capsaicin/src/Effects/DynamicFilter.cpp"
#include "../../capsaicin/src/Effects/Echo.cpp"
#include "../../capsaicin/src/Effects/EffectLFO.cpp"
#include "../../capsaicin/src/Effects/EQ.cpp"
#include "../../capsaicin/src/Effects/GReverb.cpp"
#include "../../capsaicin/src/Effects/SC4Compressor.cpp"
#include "../../capsaicin/src/Effects/Phaser.cpp"
#include "../../capsaicin/src/Effects/Reverb.cpp"

#include "../../capsaicin/src/Misc/Util.cpp"

#include "../../capsaicin/src/Params/Presets.cpp"
#include "../../capsaicin/src/Params/PresetsStore.cpp"
#include "../../capsaicin/src/Params/FilterParams.cpp"
#include "../../capsaicin/src/Params/LFOParams.cpp"


#endif
