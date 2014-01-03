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

#ifndef __JUCETICE_VEXSLIDERFIELDCOMPONENT_HEADER__
#define __JUCETICE_VEXSLIDERFIELDCOMPONENT_HEADER__

#include "../StandardHeader.h"


class SliderFieldComponent	:	public Component, public ChangeBroadcaster{
private:
     int numSliders;
     int SliderWidth;
     int lastSlider;     // last cell clicked, for outside interaction
     int activeLength; // How much of the grid should be usable vs greyed

    float* array;  //  SizeX

public:

     SliderFieldComponent() : Component( T("Slider Field Component") ){
          array = new float[16];
          lastSlider = -1;          // -1, not to test against really
          SliderWidth = -1;    // but it makes fuckups more visible
          numSliders = 16;
          activeLength = 8;

          for(int i = 0; i < numSliders; i++){ //empty out the array.. to make sure
                array[i] = 0.5f;
          }

	}


	~SliderFieldComponent(){
		delete [] array;
		deleteAllChildren ();
	}



     void paint(Graphics& g){
          //cell size -recalculate in case of resizing
          SliderWidth = getWidth() / numSliders;

          int middle = int(getHeight() * 0.5f);

          //Draw bars
          g.setColour(Colour(50,50,50));
          for(int i = 0; i < numSliders; i++){
               if(array[i] > 0.0f){
                    g.fillRect(i * SliderWidth + 2, getHeight() - int(array[i] * getHeight()), SliderWidth - 4, int(getHeight() * array[i])) ;
               }
          }

          g.setColour(Colour(100,100,130));

          //Grey stuff out
          g.setColour(Colour(uint8(170),170,170,.7f));
          g.fillRect(SliderWidth*activeLength,0,getWidth(),getHeight());

          //bevel outline for the entire draw area
          g.drawBevel(0, 0, getWidth(), getHeight(), 1, Colours::black, Colours::white, 0);
     }



     void mouseDrag(const MouseEvent &  e ){
          if ((e.y < getHeight()-1) && (e.x < getWidth()-1)){ //this avoids false triggers along the rims

               float height = (float) getHeight();
               int index = (e.x-1)/SliderWidth;
               float value = ((height - e.y -1.0f) / height);

               if (index < activeLength){  //if the click was on the greyed out portion, we dont do jack
                    lastSlider = index;
                    array[index]= value;
                    repaint();
                    sendChangeMessage(this);
               }
          }
     }


     void mouseDown(const MouseEvent &  e ){
          if ((e.y < getHeight()-1) && (e.x < getWidth()-1)){ //this avoids false triggers along the rims

               float height = (float) getHeight();
               int index = (e.x-1)/SliderWidth;
               float value = ((height - e.y ) / height);

               if (index < activeLength){  //if the click was on the greyed out portion, we dont do jack
                    lastSlider = index;
                    array[index]= value;
                    repaint();
                    sendChangeMessage(this);
               }
          }
     }

     int getLastSlider(){
          return lastSlider;
     }

     float getValue(int i){
          return array[i];
     }

     void setValue(int i, float v){
          array[i] = v;
     }

    int getLength(){
        return activeLength;
    }

    void setLength(int l){
        activeLength = jmin(l, numSliders);
        activeLength = jmax(activeLength, 1);
        repaint();
    }

     void reset(){
          for(int i = 0; i < numSliders; i++){ //empty out the array.. to make sure
                array[i] = 0.0f;
          }
          repaint();
     }
};

#endif //_SLIDERFIELDCOMPONENT_H_

