#!/bin/bash

sed 's/$/\&#10;/g' << EOF | tr -d \\n > help_text_jucer.txt

  Preset File:

  This XML file defines the preset set.
  (default: HybridReverb2_presets.xml)


  Latency:

  HybridReverb2 convolves the input signal with room
  impulse responses which are partitioned into segments
  of different size. This option specifies the size of the
  initial segments which introduce a certain processing
  latency. A small segment size results in a lower latency
  at the cost of a higher computational complexity. An
  effect plugin for musical instruments requires signal
  processing with low latency. If the latency is not relevant
  for your application, you can choose a larger segment
  size for better performance.


  Segmentation Strategy:

  &#34;Uniform Processing Load&#34;: This strategy tries to avoid
  processing load peaks at the cost of a slightly higher
  mean processing load. This is the recommended choice
  for signal processing with low latency.
  &#34;Lowest Mean Processing Load&#34;: This strategy results in
  the best overall performance. This is the recommended
  choice for offline rendering.
EOF