/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2009 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2007 by Julian Storer.

 ------------------------------------------------------------------------------

 JUCE and JUCETICE can be redistributed and/or modified under the terms of
 the GNU General Public License, as published by the Free Software Foundation;
 either version 2 of the License, or (at your option) any later version.

 JUCE and JUCETICE are distributed in the hope that they will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with JUCE and JUCETICE; if not, visit www.gnu.org/licenses or write to
 Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 Boston, MA 02111-1307 USA

 ==============================================================================

  Original Code by: braindoc

 ==============================================================================
*/

#include "../../../core/juce_StandardHeader.h"

BEGIN_JUCE_NAMESPACE

#include "jucetice_StringTools.h"

String decibelsToStringWithUnit1(double value)
{
 return String(value, 1) + String(T(" dB"));
}

String decibelsToStringWithUnit2(double value)
{
 return String(value, 2) + String(T(" dB"));
}

String hertzToStringWithUnitTotal5(double value)
{
 if( value >= 10000.0 )
  return String( (int) round(value) ) + String(T(" Hz"));
 else if( value >= 1000.0 )
  return String(value, 1) + String(T(" Hz"));
 else if( value >= 100.0 )
  return String(value, 2) + String(T(" Hz"));
 else if( value >= 10.0 )
  return String(value, 3) + String(T(" Hz"));
 else if( value >= 1.0 )
  return String(value, 4) + String(T(" Hz"));
 else
  return String(value, 5) + String(T(" Hz"));
}

String midiNoteToString(double midiNoteNumber)
{
 int intNoteNumber = (int) midiNoteNumber;
 switch( intNoteNumber )
 {
 case   0: return String(T("C-1"));
 case   1: return String(T("C#-1"));
 case   2: return String(T("D-1"));
 case   3: return String(T("D#-1"));
 case   4: return String(T("E-1"));
 case   5: return String(T("F-1"));
 case   6: return String(T("F#-1"));
 case   7: return String(T("G-1"));
 case   8: return String(T("G#-1"));
 case   9: return String(T("A-1"));
 case  10: return String(T("A#-1"));
 case  11: return String(T("B-1"));

 case  12: return String(T("C0"));
 case  13: return String(T("C#0"));
 case  14: return String(T("D0"));
 case  15: return String(T("D#0"));
 case  16: return String(T("E0"));
 case  17: return String(T("F0"));
 case  18: return String(T("F#0"));
 case  19: return String(T("G0"));
 case  20: return String(T("G#0"));
 case  21: return String(T("A0"));
 case  22: return String(T("A#0"));
 case  23: return String(T("B0"));

 case  24: return String(T("C1"));
 case  25: return String(T("C#1"));
 case  26: return String(T("D1"));
 case  27: return String(T("D#1"));
 case  28: return String(T("E1"));
 case  29: return String(T("F1"));
 case  30: return String(T("F#1"));
 case  31: return String(T("G1"));
 case  32: return String(T("G#1"));
 case  33: return String(T("A1"));
 case  34: return String(T("A#1"));
 case  35: return String(T("B1"));

 case  36: return String(T("C2"));
 case  37: return String(T("C#2"));
 case  38: return String(T("D2"));
 case  39: return String(T("D#2"));
 case  40: return String(T("E2"));
 case  41: return String(T("F2"));
 case  42: return String(T("F#2"));
 case  43: return String(T("G2"));
 case  44: return String(T("G#2"));
 case  45: return String(T("A2"));
 case  46: return String(T("A#2"));
 case  47: return String(T("B2"));

 case  48: return String(T("C3"));
 case  49: return String(T("C#3"));
 case  50: return String(T("D3"));
 case  51: return String(T("D#3"));
 case  52: return String(T("E3"));
 case  53: return String(T("F3"));
 case  54: return String(T("F#3"));
 case  55: return String(T("G3"));
 case  56: return String(T("G#3"));
 case  57: return String(T("A3"));
 case  58: return String(T("A#3"));
 case  59: return String(T("B3"));

 case  60: return String(T("C4"));
 case  61: return String(T("C#4"));
 case  62: return String(T("D4"));
 case  63: return String(T("D#4"));
 case  64: return String(T("E4"));
 case  65: return String(T("F4"));
 case  66: return String(T("F#4"));
 case  67: return String(T("G4"));
 case  68: return String(T("G#4"));
 case  69: return String(T("A4"));
 case  70: return String(T("A#4"));
 case  71: return String(T("B4"));

 case  72: return String(T("C5"));
 case  73: return String(T("C#5"));
 case  74: return String(T("D5"));
 case  75: return String(T("D#5"));
 case  76: return String(T("E5"));
 case  77: return String(T("F5"));
 case  78: return String(T("F#5"));
 case  79: return String(T("G5"));
 case  80: return String(T("G#5"));
 case  81: return String(T("A5"));
 case  82: return String(T("A#5"));
 case  83: return String(T("B5"));

 case  84: return String(T("C6"));
 case  85: return String(T("C#6"));
 case  86: return String(T("D6"));
 case  87: return String(T("D#6"));
 case  88: return String(T("E6"));
 case  89: return String(T("F6"));
 case  90: return String(T("F#6"));
 case  91: return String(T("G6"));
 case  92: return String(T("G#6"));
 case  93: return String(T("A6"));
 case  94: return String(T("A#6"));
 case  95: return String(T("B6"));

 case  96: return String(T("C7"));
 case  97: return String(T("C#7"));
 case  98: return String(T("D7"));
 case  99: return String(T("D#7"));
 case 100: return String(T("E7"));
 case 101: return String(T("F7"));
 case 102: return String(T("F#7"));
 case 103: return String(T("G7"));
 case 104: return String(T("G#7"));
 case 105: return String(T("A7"));
 case 106: return String(T("A#7"));
 case 107: return String(T("B7"));

 case 108: return String(T("C8"));
 case 109: return String(T("C#8"));
 case 110: return String(T("D8"));
 case 111: return String(T("D#8"));
 case 112: return String(T("E8"));
 case 113: return String(T("F8"));
 case 114: return String(T("F#8"));
 case 115: return String(T("G8"));
 case 116: return String(T("G#8"));
 case 117: return String(T("A8"));
 case 118: return String(T("A#8"));
 case 119: return String(T("B8"));

 case 120: return String(T("C9"));
 case 121: return String(T("C#9"));
 case 122: return String(T("D9"));
 case 123: return String(T("D#9"));
 case 124: return String(T("E9"));
 case 125: return String(T("F9"));
 case 126: return String(T("F#9"));
 case 127: return String(T("G9"));

 default: return String(T("?"));
 }
}

String percentToStringWithUnit0(double value)
{
 return String( (int) round(value) ) + String(T(" %"));
}

String percentToStringWithUnit1(double value)
{
 return String(value, 1) + String(T(" %"));
}

String ratioToString0(double value)
{
 double percentage1 = round(100.0*(1.0-value));
 double percentage2 = round(100.0*value);
 return 
  String((int) percentage1 ) + String(T("/")) + String((int) percentage2 );
}

String secondsToStringWithUnit3(double value)
{
 return String(value, 3) + String(T(" s"));
}

String secondsToStringWithUnit4(double value)
{
 return String(value, 4) + String(T(" s"));
}

String secondsToStringWithUnitTotal4(double value)
{
 if( value >= 100.0 )
  return String(value, 2) + String(T(" s"));
 else if( value >= 1.0 )
  return String(value, 3) + String(T(" s"));
 else if( value >= 0.1 )
  return String(1000*value, 1) + String(T(" ms"));
 else if( value >= 0.01 )
  return String(1000*value, 2) + String(T(" ms"));
 else if( value >= 0.001 )
  return String(1000*value, 3) + String(T(" ms"));
 else if( value >= 0.0001 )
  return String(1000*value, 3) + String(T(" ms"));
 else
  return String(1000*value, 3) + String(T(" ms")); 
}

String semitonesToStringWithUnit2(double value)
{
 return String(value, 2) + String(T(" st"));
}



String valueToStringWithTotalNumDigits(double value, int totalNumDigits, 
                                       const String& suffix)
{
 if( totalNumDigits <= 0 )
  return String( (int) round(value) ) + suffix;
 else
 {
  if( value >= pow(10.0, totalNumDigits) )
   return String( (int) round(value) ) + suffix;
  else
  {
   int tmp                  = (int) floor(log10(fabs(value)+0.00000001));
   int numDigitsBeforePoint = jmax(1, tmp+1);
   int numDigitsAfterPoint  = totalNumDigits-numDigitsBeforePoint;
   numDigitsAfterPoint      = jmax(0, numDigitsAfterPoint);
   if( numDigitsAfterPoint == 0 )
    return String( (int) round(value) ) + suffix;
   else
    return String(value, numDigitsAfterPoint) + suffix;
  }
 }
}

String valueToString0(double value)
{
 return String( (int) round(value) ) ;
}

String valueToString1(double value)
{
 return String(value, 1);
}

String valueToString2(double value)
{
 return String(value, 2);
}

String valueToString3(double value)
{
 return String(value, 3);
}

String valueToString4(double value)
{
 return String(value, 4);
}

String valueToStringTotal5(double value)
{
 if( value >= 10000.0 )
  return String( (int) round(value) );
 else if( value >= 1000.0 )
  return String(value, 1);
 else if( value >= 100.0 )
  return String(value, 2);
 else if( value >= 10.0 )
  return String(value, 3);
 else if( value >= 1.0 )
  return String(value, 4);
 else
  return String(value, 5);
}

END_JUCE_NAMESPACE

