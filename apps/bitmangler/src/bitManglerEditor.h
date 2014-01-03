/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  18 Jan 2010 11:19:40 am

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_BITMANGLEREDITOR_BITMANGLEREDITOR_7171188F__
#define __JUCER_HEADER_BITMANGLEREDITOR_BITMANGLEREDITOR_7171188F__

//[Headers]     -- You can add your own extra header files here --
#include "bitMangler.h"
#include "bitFloat.h"

#define BITS_FLT 32
#define MANT_FLT 23
#define SIGN_FLT ((floatint)1<<(BITS_FLT-1))

#if ( ULONG_MAX/2+1 != (1UL << (BITS_FLT-1)) ) && ( UINT_MAX/2+1 != (1U << (BITS_FLT-1)) )
typedef unsigned long int floatint;
#endif
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
   An auto-generated component, created by the Jucer.

   Describe your class and how it works here!
                                                                    //[/Comments]
*/
class bitManglerEditor  : public AudioProcessorEditor,
                          public ChangeListener,
                          public ButtonListener,
                          public SliderListener
{
public:
    //==============================================================================
    bitManglerEditor (DemoJuceFilter* const ownerFilter);
    ~bitManglerEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
       String getBinaryString (floatint b, int d);
       void changeListenerCallback(void *ptr);
       void textEditorTextChanged (TextEditor &editor);
       void textEditorReturnKeyPressed (TextEditor &editor);
       void textEditorEscapeKeyPressed (TextEditor &editor);
       void textEditorFocusLost (TextEditor &editor);
       void setProgram();

       enum operations
       {
               XOR,
               AND,
               OR,
               CLEAR,
               SET
       };

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void sliderValueChanged (Slider* sliderThatWasMoved);

    // Binary resources:
    static const char* lcd_bin;
    static const int lcd_binSize;
    static const char* metal2_png;
    static const int metal2_pngSize;
    static const char* power_off_png;
    static const int power_off_pngSize;
    static const char* power_on_png;
    static const int power_on_pngSize;

    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
       DemoJuceFilter *owner;
       void updateBitDisplay();
       union
       {
               floatint i;
               float f;
       }uSample, uConvertedSample;

       floatint e;
       floatint m;
       floatint ce;
       floatint cm;
       Font *lcdBigFont;
       Font *lcdSmallFont;
    //[/UserVariables]

    //==============================================================================
    ToggleButton* andBitMod;
    ToggleButton* xorBitMod;
    Label* bitDisplayInput;
    Label* bitDisplayOutput;
    ImageButton* processButton;
    Label* andRange;
    Label* xorRange;
    Label* clearRange;
    Label* setRange;
    ToggleButton* xorToggle;
    ToggleButton* andToggle;
    ToggleButton* clearToggle;
    ToggleButton* setToggle;
    Slider* xorSlider;
    Slider* andSlider;
    Slider* clearSlider;
    Slider* setSlider;
    Image* cachedImage_metal2_png;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    bitManglerEditor (const bitManglerEditor&);
    const bitManglerEditor& operator= (const bitManglerEditor&);
};


#endif   // __JUCER_HEADER_BITMANGLEREDITOR_BITMANGLEREDITOR_7171188F__
