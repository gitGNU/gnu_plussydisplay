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

#ifndef UTIL_H_
#define UTIL_H_

//#############################################################################
//# Delay Timer (using TIM4)
//#############################################################################

void tmr_setup(void);
void tmr_delay_us(uint16_t delay); // max. (2^16-1) = 65535 us
void tmr_delay_ms(uint16_t delay); // max delay: 2^16/10-1 = 6552 ms
uint8_t tmr_done(void);
void tmr_wait(void);
uint16_t tmr_get_status(void);

//#############################################################################
//# ASCII Utilities
//#############################################################################

uint8_t asciichar2halfbyte(uint8_t val);
uint8_t halfbyte2asciichar(uint8_t halfint);
void ascii_decode(uint8_t* bufIn, int lenIn);
void ascii_encode(uint8_t* bufOut, int lenOut);

#endif /* UTIL_H_ */
