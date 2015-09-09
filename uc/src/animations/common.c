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

#include "common.h"

void h2rgb(uint8_t* rgb, uint8_t h) // h = HSV with hue only ;-)
{
	uint8_t i = h/43; // roughly /(255/6)
	uint8_t f = h%43;
	uint8_t p = 0;
	uint8_t q = 255-f*6;
	uint8_t t = f*6;
	switch(i)
	{
		case 0: rgb[0] = 255; rgb[1] = t; rgb[2] = p; break;
		case 1: rgb[0] = q; rgb[1] = 255; rgb[2] = p; break;
		case 2: rgb[0] = p; rgb[1] = 255; rgb[2] = t; break;
		case 3: rgb[0] = p; rgb[1] = q; rgb[2] = 255; break;
		case 4: rgb[0] = t; rgb[1] = p; rgb[2] = 255; break;
		default: rgb[0] = 255; rgb[1] = p; rgb[2] = q; break;
	}
}
