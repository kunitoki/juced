/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2007 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2007 by Julian Storer.

 ------------------------------------------------------------------------------

 JUCE and JUCETICE can be redistributed and/or modified under the terms of
 the GNU Lesser General Public License, as published by the Free Software
 Foundation; either version 2 of the License, or (at your option) any later
 version.

 JUCE and JUCETICE are distributed in the hope that they will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with JUCE and JUCETICE; if not, visit www.gnu.org/licenses or write to
 Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 Boston, MA 02111-1307 USA

 ==============================================================================

   @author  Paul Nasca
   @tweaker Lucio Asnaghi

 ==============================================================================
*/

#ifndef __JUCETICE_XSYNTHEFFECT_HEADER__
#define __JUCETICE_XSYNTHEFFECT_HEADER__

#include "../globals.h"
#include "../Misc/Util.h"
#include "../Params/FilterParams.h"


class Effect
{
public:
      virtual ~Effect() {}

      virtual void setPreset (uint8 presetNumber) {}

      virtual void setParameter (int parameterNumber, uint8 parameterValue) {}
      virtual uint8 getParameter (int parameterNumber) { return 0; }

      virtual void out (REALTYPE *smpsl, REALTYPE *smpsr, const int numSamples) {}
      virtual void clean () {}

      // this is only used for EQ (for user interface)
      virtual REALTYPE getFrequencyResponse (REALTYPE freq) { return 0; }

      uint8 Ppreset;
      REALTYPE *efxoutl;
      REALTYPE *efxoutr;
      REALTYPE volume;
      REALTYPE outvolume; // This is the volume of effect and is public because need it in system effect.
                          // The out volume of such effects are always 1.0, so this setting tells me how is
                          // the volume to the Master Output only.

      FilterParams *filterpars;

protected:

      int insertion;//1 for insertion effect
};


#endif // __JUCETICE_XSYNTHEFFECT_HEADER__
