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

#define PLUSSYUC_C_

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <stdio.h>
#include <string.h>

#include "ws2811.h"
#include "util.h"
#include "usart.h"
#include "animations/common.h"

static void gpio_setup(void)
{
	rcc_periph_clock_enable(RCC_GPIOA);
	gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO5);
}

int main(void)
{
	rcc_clock_setup_hse_3v3(&hse_12mhz_3v3[CLOCK_3V3_84MHZ]);
	gpio_setup();
	tmr_setup();
	ws2811_setup();
	usart_setup();
	
	const uint16_t rgbDataLen = WS2811_NLEDS*3;
	uint8_t rgbData[rgbDataLen];
	uint8_t rgbDataManual[rgbDataLen];

	for(int i = 0; i < rgbDataLen; i++)
		rgbData[i] = 0;
	for(int i = 0; i < rgbDataLen; i++)
		rgbDataManual[i] = 0;

	const int usartDataLen = 256+1;
	char usartData[usartDataLen];
	
	int animSel = -1;
	int animSelMax = -1;

	while(animTable[animSelMax+1].name) // find end of table
		animSelMax++;

	uint16_t compTime = 0;
	int debugCnt = 0;

	while (1)
	{
		// toggle LED
		gpio_toggle(GPIOA, GPIO5);
		// configure display update timer with period per frame (100 Hz)
		tmr_delay_us(10000);
		
		// check for commands
		if(usart_rx_ready())
		{
			int len = usart_get_read(usartData, usartDataLen);

			if(len < 1)
			{
				usart_write("?");
			}
			else
			{
				int sel = 0;
				switch(usartData[0])
				{
				case 'e': // [e]cho test
					sprintf(usartData, "E%d", debugCnt++);
					usart_write(usartData);
					break;
				case 'c': // [c]omputation time
					sprintf(usartData, "C%d", compTime);
					usart_write(usartData);
					break;
				case 's': // [s]top animations
					animSel = -1;
					memset(rgbData, 0, rgbDataLen);
					usart_write("S");
					break;
				case 'a': // [a]nimation selection
					sscanf(usartData+1, "%02x", &sel);
					if(sel <= animSelMax)
						animSel = sel;
					sprintf(usartData, "A%c", animSel==sel ? '1':'0');
					usart_write(usartData);
					break;
				case 'l': // [l]ist query
					sscanf(usartData+1, "%02x", &sel);
					sprintf(usartData, "L%s", sel > animSelMax ? "" : animTable[sel].name);
					usart_write(usartData);
					break;
				case 'm': // [m]anual led set
					animSel = -1;
					sscanf(usartData+1, "%02x", &sel);
					if(sel < (rgbDataLen/3))
						sscanf(usartData+3, "%02hhx%02hhx%02hhx", rgbDataManual+3*sel, rgbDataManual+3*sel+1, rgbDataManual+3*sel+2);
					usartData[0] = 'M';
					for(int i = 0; i < rgbDataLen; i++)
						sprintf(usartData+1+i*2, "%02x", rgbDataManual[i]);
					usart_write(usartData);
					break;
				case 'r': // [r]ead complete led matrix
					usartData[0] = 'R';
					for(int i = 0; i < rgbDataLen; i++)
						sprintf(usartData+1+i*2, "%02x", rgbDataManual[i]);
					usart_write(usartData);
					break;
				case 'w': // [w]rite complete led matrix
					animSel = -1;
					if(len != (1+2*rgbDataLen)) // 1 char command, 6 chars per LED
					{
						usart_write("?");
					}
					else
					{
						for(int i = 0; i < (rgbDataLen/3); i++)
							sscanf(usartData+1+6*i, "%02hhx%02hhx%02hhx", rgbDataManual+3*i, rgbDataManual+3*i+1, rgbDataManual+3*i+2);
						usart_write("W");
					}
					break;
				default:
					usart_write("?");
				}
			}
		}
		
		// calculate next frame
		if(animSel >= 0)
			animTable[animSel].func(rgbData, rgbDataLen);
		// determine how much time has passed
		compTime = tmr_get_status(); // TODO: ouput to serial port?
		// wait if frame time has not yet passed
		tmr_wait();
		// trigger display update
		if(animSel < 0)
			ws2811_update(rgbDataManual);
		else
			ws2811_update(rgbData);
	}

	return 0;
}
