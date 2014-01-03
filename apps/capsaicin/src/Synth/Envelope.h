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

#ifndef __JUCETICE_XSYNTHENVELOPE_HEADER__
#define __JUCETICE_XSYNTHENVELOPE_HEADER__

#include "../globals.h"
#include "../Params/EnvelopeParams.h"


//==============================================================================
/**
    Envelope DSP class. This is instantiated in the voice/note section
    and is responsible to evaluate envelope output
*/
class Envelope
{
public:

    //==============================================================================
    /** Construct an envelope */
    Envelope (EnvelopeParams *envpars, REALTYPE basefreq);

    /** Destructor */
    ~Envelope();

    //==============================================================================
    /** Compute envelope output, typically linear */
    REALTYPE envout();

    /** Compute envelope output in decible, usually for multiplying amplitudes */
    REALTYPE envout_dB();

    //==============================================================================
    /** Release the envelope, cause someone tell us to release */
    void relasekey()
    {
        if (keyreleased == 1) return;
        keyreleased = 1;
        if (forcedrelase != 0) t = 0.0;
    }

    /** Return 1 if the envelope is finished */
    int finished()
    {
        return envfinish;
    }

    //==============================================================================
    /** Total number of envelope points */
    int envpoints;

    /** Index of sustain point, -1 means disabled */
    int envsustain;

    /** Envelope points time in milliseconds */
    REALTYPE envdt [MAX_ENVELOPE_POINTS];

    /** Envelope points value, expressed in 0.0..1.0 */
    REALTYPE envval [MAX_ENVELOPE_POINTS];

    /** Total amount of strect time */
    REALTYPE envstretch;

    /** If the envelope is linear or logaritmic */
    int linearenvelope;

private:

    int currentpoint;   // current envelope point (starts from 1)
    int forcedrelase;   // if the envelope has to force the release
    char keyreleased;   // if the key was released
    char envfinish;     // the envelope has finished ?
    REALTYPE t, inct;   // time from last point, increment
    REALTYPE envoutval; // used to do the forced release
};


#endif
