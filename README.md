# Plussy Display

This repository contains free software and hardware design components for a small LED matrix resembling FSFE's plussy mascot. It is intended to be used, e.g., as an eyecatcher for fellowship events.

# Usage
## Adding new animations

* install dependencies for simulator (gcc, python2.7 including development headers, python-pygame)
* add new animation file in uc/src/animations, e.g., by copying an existing file
* rename animation function to match file name
* register animation function in common.h for microcontroller
* run 'make' in folder sim

