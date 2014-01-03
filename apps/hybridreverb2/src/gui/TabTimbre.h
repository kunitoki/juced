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


#ifndef __JUCER_HEADER_TABTIMBRE_TABTIMBRE_1CFF6033__
#define __JUCER_HEADER_TABTIMBRE_TABTIMBRE_1CFF6033__

//[Headers]     -- You can add your own extra header files here --
#include "juce_amalgamated.h"
#include "../ParamTimbre.h"

#include <fftw3.h>


// forward declarations
class MasterAndCommander;

class FreqPlot;

class LagrangeInterpolator;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TabTimbre  : public Component,
                   public SliderListener
{
public:
    //==============================================================================
    TabTimbre (MasterAndCommander *m);
    ~TabTimbre();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    float* getFilter();
    int getFilterLen();
    void updateData();
    void setTimbre (ParamTimbre *param);
    void sliderDragEnded (Slider* sliderThatWasMoved);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    MasterAndCommander* master;
    ParamTimbre *paramTimbre;
    LagrangeInterpolator *interpolator;
    Label **labelFreq;
    Label **labelTime;
    int numLabel;
    Label **labelDbFreq;
    Label **labelDbTime;
    int numLabelDb;
    Slider **slider;
    int numSlider;
    int gridX;
    int gridY;
    int offsetX;
    int offsetY;
    float sampleRate;
    float *level;
    int numLevel;
    float f0;
    float *impulse;
    float *window;
    fftwf_complex *dftFreq;
    fftwf_plan fft;
    fftwf_plan ifft;
    //[/UserVariables]

    //==============================================================================
    GroupComponent* groupComponent;
    FreqPlot* freqPlot;
    Slider* sliderSmooth;
    Label* Smoothing;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    TabTimbre (const TabTimbre&);
    const TabTimbre& operator= (const TabTimbre&);
};


#endif   // __JUCER_HEADER_TABTIMBRE_TABTIMBRE_1CFF6033__
