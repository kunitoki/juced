/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2008 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2008 by Julian Storer.

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

   @author  rockhardbuns
   @tweaker Lucio Asnaghi

 ==============================================================================
*/

#ifndef CFILTER_H
#define CFILTER_H


class cFilter {
private:
    float buf0, buf1;
    float cutoff;
    float res;

public:

    cFilter()
    {
        cutoff = 0.9f;
        res = 0;
        buf0 = 0; buf1 = 0;
    }

    ~cFilter(){}

    void setFilter(float f, float r)
    {
        cutoff = f;
        res = r;
    }

    void setCutOff(float f)
    {
        cutoff = f;
    }

    void setResonance(float r)
    {
        res = r;
    }

    float doProcess( float in, float f, float r)
    {
        cutoff = f - ((f >= 0.99f) * (f - 0.99f)) ;
        res = r;
        float fb = res + res /(1.0 - (cutoff));
        buf0 = buf0 + cutoff * (in - buf0 + fb * (buf0 - buf1));
        buf1 = buf1 + cutoff * (buf0 - buf1);
        return buf1;
    }
};

#endif

