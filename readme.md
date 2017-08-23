<!-- using shields.io for status buttons -->
![Programming Language](https://img.shields.io/badge/Language-C++-red.svg)
![Version](https://img.shields.io/badge/Version-0.1-blue.svg)

# MIDI Reverse

This program's aim is to reverse the information in a midi file for it to be played backwards. Currently the program converts .asc files but will eventually be able to make midi to midi conversions.

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
The goal is to rebuild this program inside of the compiler so you can eventually go midi to reversed midi without dealing with the ascii file. But first I'm going to attempt to convert the compiler to windows so I don't have to switch OSs.