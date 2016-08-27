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

#include "hwversion.h"
#include "ws2811.h"
#include "util.h"
#include "usart.h"
#include "animations/common.h"

static void gpio_setup(void)
{
	rcc_periph_clock_enable(RCC_GPIOA);
	gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO5);
}

static void btn_setup(void)
{
	rcc_periph_clock_enable(RCC_GPIOC);
	gpio_mode_setup(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO13);
}

static uint8_t btn_pressed(void)
{
	return (GPIOC_IDR & (1<<13)) ? 0 : 1;
}

int main(void)
{
	rcc_clock_setup_hse_3v3(&rcc_hse_12mhz_3v3[RCC_CLOCK_3V3_84MHZ]);
	gpio_setup();
	hwversion_setup();
	btn_setup();
	tmr_setup();
	ws2811_setup();
	usart_setup();
	
	const uint16_t rgbDataLen = WS2811_NLEDS*3;

	// data before mapping, first non-pcb variant
	uint8_t rgbData[rgbDataLen];
	uint8_t rgbDataManual[rgbDataLen];

	// data mapped to device version
	uint8_t rgbDataDev[rgbDataLen];

	// initialize data
	for(int i = 0; i < rgbDataLen; i++)
		rgbData[i] = 0;
	for(int i = 0; i < rgbDataLen; i++)
		rgbDataManual[i] = 0;

	const int usartDataLen = 256+1;
	char usartData[usartDataLen];
	
	// options
	uint8_t brightnessScale = 0xff;

	// animation table
	int animSel = -1;
	int animSelMax = -1;

	while(animTable[animSelMax+1].name) // find end of table
		animSelMax++;

	// detect hardware version
	tmr_delay_us(10000);
	tmr_wait();
	uint8_t hwver = hwversion_detect();
	void (*hwmap)(uint8_t*, uint8_t*) = hwversion_remap_none; // args: src,dest
	
	switch(hwver)
	{
	case 0: // inital version, LEDs connected with wires
		break;
	case 1: // rev1 is PCB labeled "LED Matrix / Plussy v0"
		hwmap = hwversion_remap_rev1;
		break;
	case 2: // rev2 is PCB labeled "Plussy v2 Summit Edition" with 8mm WS2811 LEDs
		hwmap = hwversion_remap_rev1;
		break;
	case 3: // rev3 is PCB labeled "Plussy v2 Summit Edition" with WS2812B SMD LEDs
		hwmap = hwversion_remap_rev2_ws2812b;
		break;
	default: // unknown revision, assume no mapping
		break;
	}
	
	// main loop
	uint16_t compTime = 0;
	int debugCnt = 0;
	uint8_t btnLastPressed = 0;

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
				case 'b': // [b]rightness scale setting
					sscanf(usartData+1, "%02x", &sel);
					brightnessScale = (uint8_t)sel;
					usart_write("B");
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
					{
						int r,g,b;
						sscanf(usartData+3, "%02x%02x%02x", &r, &g, &b);
						rgbDataManual[3*sel] = r;
						rgbDataManual[3*sel+1] = g;
						rgbDataManual[3*sel+2] = b;
					}
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
						{
							int r,g,b;
							sscanf(usartData+3, "%02x%02x%02x", &r, &g, &b);
							rgbDataManual[3*sel] = r;
							rgbDataManual[3*sel+1] = g;
							rgbDataManual[3*sel+2] = b;
						}
						usart_write("W");
					}
					break;
				default:
					usart_write("?");
				}
			}
		}
		else if(!btnLastPressed && btn_pressed())
		{
			if(animSel == animSelMax)
				animSel = -1;
			else
				animSel++;
			btnLastPressed = 1;
		}
		else if(!btn_pressed())
		{
			btnLastPressed = 0;
		}
		
		// calculate next frame
		if(animSel >= 0)
			animTable[animSel].func(rgbData, rgbDataLen);
		// remap data
		if(animSel < 0)
			hwmap(rgbDataManual, rgbDataDev);
		else
			hwmap(rgbData, rgbDataDev);
		// scale brightness
		for(uint8_t i = 0; i < WS2811_NLEDS; i++)
			bscale(rgbDataDev+3*i, brightnessScale);
		// determine how much time has passed
		compTime = tmr_get_status(); // TODO: ouput to serial port?
		// wait if frame time has not yet passed
		tmr_wait();
		// trigger display update
		ws2811_update(rgbDataDev);
	}

	return 0;
}

