/*
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
*/

#ifndef COMMON_H_
#define COMMON_H_

#include <stdint.h>

//#############################################################################
//# Utility functions
//#############################################################################

// convert hue to rgb
void h2rgb(uint8_t* rgb, uint8_t h); // h = HSV with hue only, integer approximation
void hsv2rgb_f(uint8_t* rgb, float h, float s, float v); // true HSV with floats

// LUT-based functions
uint8_t sin4(uint8_t x); // 1/4 of sine function ( = floor(sin(0:pi/2/255:pi/2)*255) in GNU octave )


//#############################################################################
//# Animation Definitions
//#############################################################################

// animations
struct anim_t
{
	const char* name;
	void (*func)(uint8_t*, uint16_t);
};

// (1) add your declaration here:
void anim_test(uint8_t* data, uint16_t len);
void anim_green(uint8_t* data, uint16_t len);
void anim_constgreen(uint8_t* data, uint16_t len);

#ifdef PLUSSYUC_C_

// (2) add your function to this table:
struct anim_t animTable[] = {
	{ "Test Animation", &anim_test },
	{ "Green", &anim_green },
	{ "Constant Green", &anim_constgreen },
	{ 0, 0 } // end-of-table flag
};


#endif

#endif
