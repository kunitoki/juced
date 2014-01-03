
#ifndef __MYLOOKANDFEEL_JUCEHEADER__
#define __MYLOOKANDFEEL_JUCEHEADER__

#include "juce.h"

class JUCE_API  MyLookAndFeel  : public LookAndFeel{
public:

    MyLookAndFeel();


    ~MyLookAndFeel();

     void drawRotarySlider (Graphics& g,
                                   int x, int y,
                                   int width, int height,
                                   float sliderPosProportional,
                                   const float rotaryStartAngle,
                                   const float rotaryEndAngle,
                                   Slider& slider);


    juce_UseDebuggingNewOperator

};


#endif   // __JUCE_SHINYLOOKANDFEEL_JUCEHEADER__
