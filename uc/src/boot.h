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

#ifndef INCLUDE_BOOT_H_
#define INCLUDE_BOOT_H_

#include <inttypes.h>

void scb_move_vector_table(uint32_t offset);

void boot_check(void);
void boot_setup(void);
void boot_cmd(uint8_t* bufRx, uint8_t* bufTx, uint8_t bufLen);

#endif /* INCLUDE_BOOT_H_ */
