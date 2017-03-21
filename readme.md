<!-- using shields.io for status buttons -->
![Programming Language](https://img.shields.io/badge/Language-C++-yellow.svg)
![Status](https://img.shields.io/badge/Status-Broken-red.svg)
![Version](https://img.shields.io/badge/Version-0.0.1-blue.svg)
# MIDI Reverse

This program's aim is to reverse the information in a midi file for it to be played backwards. Currently the program's aim is to convert .asc files but will continue to make midi to midi conversions.

## How to Run
Currently you need to convert your midi file to ascii using [midicomp](https://github.com/markc/midicomp) (install instructions for linux only).
```
midicomp my-midi.mid > my-midi.asc
```
After converting, compile the MIDI Reverse repo using
```
g++ midi-rev.cpp -o midi-rev
```
and run with your ascii file
```
./midi-rev my-midi.asc
```
now go back to [midicomp](https://github.com/markc/midicomp) to convert the ascii back to midi.
```
midicomp -c my-midi.asc my-midi-rev.mid
```

## Progress
The goal is to merge with midicomp as a feature of that repo so you can go midi to reversed midi without dealing with the ascii file.