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

#ifndef WS2811_H_
#define WS2811_H_

#include <stdint.h>

#define WS2811_NLEDS 20

#define WS2811_OPTION_INVPOLARITY (1)
#define WS2811_OPTION_FASTMODE (1<<1)

void ws2811_setup(uint8_t options);
void ws2811_update(uint8_t* rgbData); // buf length: WS2811_NLEDS*3
uint8_t ws2811_ready(void);

#endif
