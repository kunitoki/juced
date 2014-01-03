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
*/

#ifndef __JUCETICE_JOSTOPPRESSORPARAMETERS_HEADER__
#define __JUCETICE_JOSTOPPRESSORPARAMETERS_HEADER__

//#include "../../StandardHeader.h"
//This class handles plugin's parameters

class OppressorParMan {
private:
     int numPars;
     float * pars;

public:
     OppressorParMan(){
          numPars = 6;
          pars = new float[numPars];
          loadPreset(0);
     }



     enum{
     thresh, ratio, level, attack, release, limiter};



     ~OppressorParMan(){
          delete [] pars;
     }

     inline float getParameter(int i){
          i = jlimit(0, numPars, i);
          return pars[i];
     }

     int getNumPars(){
          return numPars;
     }

    void setParameter(int i, float v){
          i = jlimit(0, numPars, i);
          pars[i] = v;
     }

     bool loadPreset(int i = 0){
// Dump
		 switch (i)
		{
			case 0: pars[0] = 0.6f;
               pars[1] = 0.4f;
               pars[2] = 0.1f;
			   pars[3] = 0.2f;
               pars[4] = 0.5f;
			   pars[5] = 1.0f;
			   return true;
			   break;
			
			case 1: pars[0] = 0.9f;
               pars[1] = 0.4f;
               pars[2] = 0.45f;
			   pars[3] = 0.18f;
               pars[4] = 0.55f;
			   pars[5] = 0.6f;
			   return true;
			   break;

			case 2: pars[0] = 0.77f;
               pars[1] = 0.19f;
               pars[2] = 0.93f;
			   pars[3] = 0.79f;
               pars[4] = 0.06f;
			   pars[5] = 0.38f;
			   return true;
			   break;
		 }

return false;

     }

};


#endif
