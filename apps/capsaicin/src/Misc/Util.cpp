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

#include "Util.h"

#include <math.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


/*
 * Transform the velocity according the scaling parameter (velocity sensing)
 */
REALTYPE VelF (REALTYPE velocity, uint8 scaling)
{
    REALTYPE x;
    x = pow (VELOCITY_MAX_SCALE, (64.0 - scaling) / 64.0);
    if ((scaling == 127) || (velocity > 0.99)) return (1.0);
    else                                       return (pow (velocity, x));
}

/*
 * Get the detune in cents
 */
REALTYPE getdetune (uint8 type, uint16 coarsedetune, uint16 finedetune)
{
    REALTYPE det = 0.0,
             octdet = 0.0,
             cdet = 0.0,
             findet = 0.0;

    // Get Octave
    int octave = coarsedetune / 1024;
    if (octave >= 8) octave -= 16;
    octdet = octave * 1200.0;

    // Coarse and fine detune
    int cdetune = coarsedetune % 1024;
    if (cdetune > 512) cdetune -= 1024;

    int fdetune=finedetune-8192;

    switch (type){
//  case 1: // is used for the default (see below)
    case 2:
        cdet = fabs (cdetune * 10.0);
        findet = fabs (fdetune / 8192.0) * 10.0;
        break;
    case 3:
        cdet = fabs (cdetune * 100);
        findet = pow (10, fabs (fdetune / 8192.0) * 3.0) / 10.0 - 0.1;
        break;
    case 4:
        cdet = fabs (cdetune * 701.95500087); //perfect fifth
        findet = (pow (2, fabs (fdetune / 8192.0) * 12.0) - 1.0) / 4095 * 1200;
        break;
    // case ...: // need to update N_DETUNE_TYPES, if you'll add more
    default:
        cdet = fabs (cdetune * 50.0);
        findet = fabs (fdetune / 8192.0) * 35.0;
        break;
    }
    if (finedetune < 8192) findet = -findet;
    if (cdetune < 0) cdet = -cdet;

    det = octdet + cdet + findet;
    return (det);
}

/*
 * Used by the fft wrapper
 */
void newFFTFREQS (FFTFrequencies *f, int size)
{
    f->c = new float[size];
    f->s = new float[size];
    for (int i = 0; i < size; i++)
    {
        f->c[i] = 0.0;
        f->s[i] = 0.0;
    }
}

void deleteFFTFREQS (FFTFrequencies *f)
{
    delete[] (f->c);
    delete[] (f->s);
    f->c = f->s = NULL;
}

