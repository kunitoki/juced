#!/bin/bash

sed 's/$/\&#10;/g' << EOF | tr -d \\n > about_text_jucer.txt

  About Me and HybridReverb2:

  As a research associate at the Institute of Communication
  Acoustics, Ruhr-Universit&#228;t Bochum, Germany, I'm currently
  persuing a Dr.-Ing. degree in electrical engineering.
  I benefited from free and open source software for so many
  years that I felt that I should give something back to the
  community. As I'm working in the field of virtual acoustics
  and spatial audio, writing a room effect plugin kind of
  suggested itself. I hope you enjoy the sound as much as I
  do!

  Best regards,
  Christian Bor&#223; <christian.borss@rub.de>


  Credits:

  - Julian Storer for his JUCE library
  - The development team of the Jucetice project (jost, juced,
    etc.)
  - Matteo Frigo, Steven G. Johnson, and anybody else who
    contributed to the FFTW library
  - Prof. Rainer Martin for supporting my research
  - Bj&#246;rn Kapteina for the implementation of the Windows
    installer


  References:

  Bor&#223;, C., Martin, R. (2009). &#34;An Improved Parametric Model
  for Perception-Based Design of Virtual Acoustics&#34;, AES 35th
  Int. Conference, London, UK, Feb. 2009.

  Bor&#223;, C. (2009). &#34;A Novel Approach for Optimally Matching a
  Late Reverberation Model to an Image Source Model - Or:
  What Does a Football Have to Do With Shoebox Shaped
  Rooms?&#34;, Auralization Symposium of the European Acoustics
  Association, Espoo, Finland, Jun. 2009.

  Bor&#223;, C. (2009). &#34;A VST Reverberation Effect Plugin Based on
  Synthetic Room Impulse Responses&#34;, 12th Int. Conference
  on Digital Audio Effects (DAFx-09), Como, Italy, Sep. 2009.
EOF