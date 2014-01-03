JUCETICE / SoundCrab v0.2.4 / SoundFont2 Player

Original plugin - FluidSynth - Copyright (C) Josh Green
JUCE Port - Copyright (C) 2008 kRAkEn/gORe (www.anticore.org/jucetice)


Information-------------------------------------------------------------

SoundCrab is a complex and clean instrument for playing back your
favourite sound font sample packs. It is fully polyphonic and is very
light on CPU, even if we used high order interpolation in sample
playback. It presents a lot of controls typically used on high end
hardware synths: tone controls, amplifier / modulation envelopes,
filter, panning.


Changelog --------------------------------------------------------------

Version [0.2.4] - 2009-xx-xx

Version [0.2.3] - 2009-06-26
+ aligned to latest juce in svn repository
+ now jucetice is compiled as an external standalone library via amalgama
~ fixed to work with QTractor (latest cvs) and Renoise (i hope finally...)
~ fixed jack and alsa dependancies for VST version

Version [0.2.2] - 2008-04-07
+ aligned to latest juce in svn repository (1.45)
~ fixed a problem in preset restore with RENOISE
~ fixed problem of midi channels > 0 playing default sound
~ improved Vst class in library

Version [0.2.1] - 2007-05-22
~ fixed problems loading some preset with big soundfonts
~ optimized a bit gui paint method (was filling it two times)

Version [0.2.0] - 2007-05-18
+ poly mode (actually 1-128 voices) with selectable slider
+ panning interpolation to avoid clicking
+ hermite interpolation in sample playback
+ 4 stage amplitude envelope for each voice
+ global modulation lfo and envelope to follow soundfont 2.0 standard
+ svf lowpass filter with resonance (lfo/env modulation amount)
+ controls for coarse and fine tune (lfo/env modulation amount)
+ controls for master gain and pan
+ support for drag and drop of soundfont directly over editor
~ fixed couple of bugs when freeing the plugin
~ fixed a memory access error when no soundfont was loaded
~ fixed some variables were not initialized correctly
~ fixed now last soundfonts / last browsing directory are saved in config
~ config file changed to XML

Version [0.1.0] - 2007-04-20
* Initial release
