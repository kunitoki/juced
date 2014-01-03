/*
  ==============================================================================

   Utility to turn a font into binary file so it can be included in a 
   binary executable with the binarybuilder app.

   Copyright 2009 by Asnaghi Lucio.
   
   Uses code portions from Niall Moody.

   Use this code at your own risk! It carries no warranty!

  ==============================================================================
    
   After you have binarized this font, and included in a cpp file with the
   binarybuilder application you can create a new font like this:

     MemoryInputStream fontStream (serialised, serialised_size, false);
     Typeface* newTypeface = new Typeface (fontStream);
     Font* newFont = new Font (*newTypeface);
     delete newTypeface;

  ==============================================================================
*/

#include "juce_AppConfig.h"
#include "../../juce_amalgamated.h"

using namespace juce;

//==============================================================================
static bool addFont (const String& fontName, 
                     OutputStream& outputStream)
{
    Typeface* font = new Typeface (fontName, false, false);  
    if (! font)
    {
        printf ("Error opening typeface %s \n", (const char*) fontName);
        return false;
    }

    try
    {
        for (int i = 0; i < 256; ++i)
            font->getGlyph (i);

    	font->serialise (outputStream);
    	delete font;

        return true;
    }
    catch (...)
    {
        printf ("Error writing typeface %s \n", (const char*) fontName);
    }

	delete font;

    return false;
}


//==============================================================================
int main (int argc, char* argv[])
{
    // If you're running a command-line app, you need to initialise juce manually 
    // before calling any Juce functionality..
    initialiseJuce_NonGUI();

    printf ("\nFontSerialiser! Copyright 2009 by Asnaghi Lucio - www.anticore.org\n\n");

    if (argc < 2 || argc > 3)
    {
        printf ("  Usage: FontSerialiser typefacename [outputfilename]\n\n");

        return 0;
    }

    const String fontName = String (argv[1]).unquoted();
    const String fontExtension = ".bcf";
    const File currentDir = File::getCurrentWorkingDirectory();
    File outputFile (currentDir.getChildFile (fontName + fontExtension));

    if (argc == 3)
        outputFile = currentDir.getChildFile (String (argv[2]).unquoted() + fontExtension);

    OutputStream* outputStream = outputFile.createOutputStream();
    if (outputStream)
    {
        addFont (fontName, *outputStream);

        delete outputStream;
    }

    shutdownJuce_NonGUI();

    return 0;
}
