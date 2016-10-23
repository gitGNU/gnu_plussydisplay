/*
	Plussy Display
	Copyright (C) 2016  Christian Carlowitz <chca@cmesh.de>

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

#ifndef SRC_CMD_H_
#define SRC_CMD_H_

#include <inttypes.h>

struct plussy_params
{
	uint8_t* rgbData;
	uint8_t* rgbDataManual;
	uint16_t rgbDataLen;

	uint8_t brightnessScale;
	int animSel;
	int animSelMax;
	uint16_t compTime;
};

void cmd_setup(void);
void cmd_proc(struct plussy_params* p);

#endif /* SRC_CMD_H_ */
