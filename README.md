
# Plussy Display Introduction

This repository contains free software and hardware design components for a small LED matrix resembling FSFE's plussy mascot. It is intended to be used, e.g., as an eyecatcher for fellowship events.

## License Information

All files in this project (except some configuration files where stated in their header) are licensed under the GPLv3 license as stated in the next section (GPLv3 License Statement).

## GPLv3 License Statement

Plussy Display
Copyright (C) 2015  Christian Carlowitz <chca@cmesh.de>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

# Usage
## Adding new animations

* install dependencies for simulator (gcc, make, python2.7 including development headers, python-pygame)
* add new animation file in _uc/src/animations_, e.g., by copying an existing file
* rename animation function to match file name
* register animation function in _common.h_ for microcontroller (add declaration and _animTable_ entry)
* run `make ANIM=anim_funcname` in folder _sim_ to test

## Compiling microcontroller code

* install dependencies (gcc-arm-embedded from https://launchpad.net/gcc-arm-embedded, openocd, make)
* get libopencm3 (run `git submodule init`, enter _uc/libopencm3_, run `make`)
* run `make` or `make V=1` (verbose) in folder _uc_

## Flashing microcontroller

* find out openocd name for your JTAG adapter
* change parameter _OOCD_INTERFACE_ in file _uc/libopencm3.target.mk_ accordingly
* run `make flash` or `make flash V=1` (verbose) in folder _uc_
