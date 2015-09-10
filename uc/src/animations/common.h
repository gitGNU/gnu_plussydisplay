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

// convert hue to rgb
void h2rgb(uint8_t* rgb, uint8_t h); // h = HSV with hue only, integer approximation
void hsv2rgb_f(uint8_t* rgb, float h, float s, float v); // true HSV with floats

// LUT-based functions
uint8_t sin4(uint8_t x); // 1/4 of sine function ( floor(sin(0:pi/2/255:pi/2)*255) )

// animations
void anim_test(uint8_t* data, uint16_t len);

#endif
