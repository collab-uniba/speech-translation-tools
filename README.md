speech-translation-tools
========================

A collection of several instruments to collect data in experiments about speech translation. Each branch refers to a different technology.

This branch uses Skype4Java API as the communication channel (both voice and text as the back channel). ASR and MT technologies of choice
are Google's.

The voice communication channel must be always on and our prototype must be ready to identify pauses and in the stream of voice. 
From one pause to another, it would assume that one sentence is being spoken, with a dedicated thread that captures the sentences,
sends to google translate and then shares it through the textual back channel, along with the original captioned text. 
For the captured text to be played back, we are still to find a voice synthesis technology that supports English, Italian and Portugues
at once.
