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

#ifndef HWVERSION_H_
#define HWVERSION_H_

void hwversion_setup(void);
uint8_t hwversion_detect(void);
void hwversion_remap_rev1(uint8_t* rgbDataSrc, uint8_t* rgbDataDest);

#endif /* HWVERSION_H_ */

