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

#ifndef SRC_USB_H_
#define SRC_USB_H_

#include <stdint.h>

void usb_setup(void);
void usb_poll(void);
uint8_t usb_rx_ready(void);
int usb_get_read(char* str, uint16_t maxlen);
void usb_write(char* str);


#endif /* SRC_USB_H_ */
