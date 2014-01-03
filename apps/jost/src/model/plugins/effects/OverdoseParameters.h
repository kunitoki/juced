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

#ifndef __JUCETICE_JOSTOVERDOSEPARAMETERS_HEADER__
#define __JUCETICE_JOSTOVERDOSEPARAMETERS_HEADER__

//This class handles plugin's parameters

class OverdoseParMan {
private:
     int numPars;
     float * pars;

public:
     OverdoseParMan(){
          numPars = 3;
          pars = new float[numPars];
          loadPreset(0);
     }



     enum{
     drive, muffle, output};



     ~OverdoseParMan(){
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

     bool loadPreset(int i){

// Dump
		 switch (i)
		{
			case 0: pars[0] = 0.9f;
               pars[1] = 0.0f;
               pars[2] = 0.5f;
			   return true;
			   break;
			
			case 1: pars[0] = 0.6f;
               pars[1] = 0.0f;
               pars[2] = 0.3f;
			   return true;
			   break;

			case 2: pars[0] = 1.0f;
               pars[1] = 0.6f;
               pars[2] = 0.8f;
			   return true;
			   break;
		 }

     

return false;

     }

};


#endif
