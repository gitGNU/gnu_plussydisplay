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

void anim_constgreen(uint8_t* data, uint16_t len)
{
	uint16_t nLeds = len/3;
	
	for(int i = 0; i < nLeds; i++)
	{
		data[3*i+0] = 0x00;
		data[3*i+1] = 0x10;
		data[3*i+2] = 0x00;
	}
}
