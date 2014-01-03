Peggy 2000 : Total Peggination

(c) Joakim Karrstrom a.k.a Rock Hardbuns


Build with the JUCE library, and JUCE Audio Plugin framework (JAP)
(c) Julian (Jules) Storer. (http://www.rawmaterialsoftware.com/juce/)


Using the VST SDK 2.4 by Steinberg.  (http://www.steinberg.de)


Code have also been inspired by, and borrowed from 
public sources, specifically the development forum 
on KvR (http://www.kvraudio.com/forum/viewforum.php?f=33)
and the MusicDSP archives (http://www.musicdsp.org/).

Thanks fellas.



Notes on Features________________________________________
Oscillators:
Wavetable with cubic interpolation, 2x oversampled.
The saw, tri, sqr and sine waveforms are what you would expect. 
Saw2 and Tri2 are mangled to work better with the faux sync feature
, or mixed with the other waveforms. 

The faux sync locks the wavetable cycle to the base frequency of the
played note. Detuning then causes the waveform to map unevenly to the
cycle which produces a range overtones and other distorsion.

Filter:
24db Chamberlin SVF, Plus a lowshelf EQ for adjusting the
bass and a saturation/distorsion step. The saturated signal is mixed
with the clean signal with the Sat knob.

Pattern Arpeggiator:
Simmilar to a phrase sequencer, except that it only uses supplied notes.
The velocity control maps directly to input note velocity and thus it's
effect is determined by the knobs in the velocity section.

The swing knob displaces every even step towards the next step.

Keysync means that the pattern resets when you play a note and holds that
sync untill all keys are up. The other option, Bar sync resets the pattern
to the bars of the host sequencer.

Delay:
The delay time is synced to host tempo in an uncommon fashion. It's 
quantized to "number 16th". I.E the time goes from 1 16th to 16 16th.
The delay can be turned off by setting it's level to zero, freeing up
some CPU time.

Chorus:
Simple stereo chorus, with linear interpolation. It can be turned off 
by setting mix to zero, freeing up some CPU time.




Notes on License____________________________________________
Peggy 2000: Total Peggination is distributed under the GNU GPL, with an
added provision. It can be redistibuted freely as long as this text is 
included.

There has been a lot of discussion with regards to whether the GPL can be
applied to something that requires the VST SDK to be built, as the VST SDK
is under a more restrictive license that does not allow redistribution.

The jury is still out, but Jules, the author of JUCE and JAP, whence 
Peggy 2000: Total Peggination inherited is GPL:ed status, has however stated
clearly that the VST SDK does not have to be included in the source 
distribution of software derived from JUCE. Therefor it can be view much as a
platform requirement which the GPL excludes from the redistribution requirment.

It should be noted though that this can cause complications if you plan to 
derrive a work from Peggy 2000: Total Peggination, AND also include code from
other GPL:ed works that do not have this provision, AND use the VST SDK.

I suggest that if you find yourself in that position, contact the authors of 
the other GPL:ed code and ask if they could accept this arrangement too. 




Notes on the source and building_____________________________

The source is here: http://hem.bredband.net/b120780/Peggy2000_src.zip

It was built with JUCE 1.36 and JAP 1.12 available here:
http://www.rawmaterialsoftware.com/juce/download.php

And the VST SDK:
http://ygrabit.steinberg.de/~ygrabit/public_html/index.html

It was built with Codeblocks IDE, using MS VS 2003 toolkit, any decent C++
compiler should work.

To compile, you will first need to build JUCE, and then set up a project to 
build the JAP DEMO plugin. Once you have achieved that, you should be able
to build Peggy 2000: Total Peggination in the same manner.



You can contact me on debois(a)mail.com, or find "Rock Hardbuns" 
on KvR or JUCE forums.





