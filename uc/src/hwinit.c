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

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#include "hwinit.h"
#include "ws2811.h"
#include "animations/common.h"
#include "util.h"

void hwinit(struct plussy_params* p)
{
	// initialize data
	for(int i = 0; i < p->rgbDataLen; i++)
		p->rgbData[i] = 0;
	for(int i = 0; i < p->rgbDataLen; i++)
		p->rgbDataManual[i] = 0;
	for(int i = 0; i < p->rgbDataLen; i++)
		p->rgbDataDev[i] = 0;

	// options
	p->brightnessScale = 0xff;

	// animation table
	p->animSel = -1;
	p->animSelMax = -1;

	while(animTable[p->animSelMax+1].name) // find end of table
		p->animSelMax++;

	// detect hardware version
	tmr_delay_us(10000);
	tmr_wait();
	p->hwver = hwversion_detect();
	p->hwmap = hwversion_remap_none; // args: src,dest
	p->ws2811_options = WS2811_OPTION_INVPOLARITY;

	switch(p->hwver)
	{
	case 0: // inital version, LEDs connected with wires
		break;
	case 1: // rev1 is PCB labeled "LED Matrix / Plussy v0"
		p->hwmap = hwversion_remap_rev1;
		break;
	case 2: // rev2 is PCB labeled "Plussy v2 Summit Edition" with 8mm WS2811 LEDs
		p->hwmap = hwversion_remap_rev1;
		break;
	case 3: // rev3 is PCB labeled "Plussy v2 Summit Edition" with WS2812B SMD LEDs
		p->hwmap = hwversion_remap_rev2_ws2812b;
		p->ws2811_options |= WS2811_OPTION_FASTMODE;
		break;
	case 7: // rev7 is PCB labeled "lightctrl v1" with 8 channels and RS485 drivers connected to WS2812B SMD LEDs
		p->ws2811_options &= ~WS2811_OPTION_INVPOLARITY; // has no inverting transistor driver
		p->ws2811_options |= WS2811_OPTION_FASTMODE;
		break;
	default: // unknown revision, assume no mapping
		break;
	}
}

void hwversion_setup(void)
{
	rcc_periph_clock_enable(RCC_GPIOC);
	gpio_mode_setup(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO10|GPIO11|GPIO12);
}

uint8_t hwversion_detect(void)
{
	return (~(GPIOC_IDR >> 10)) & 0x7;
}

static void copy_buf(uint8_t* rgbDataSrc, uint8_t srci, uint8_t* rgbDataDest, uint8_t desti)
{
	rgbDataDest[3*desti] = rgbDataSrc[3*srci];
	rgbDataDest[3*desti+1] = rgbDataSrc[3*srci+1];
	rgbDataDest[3*desti+2] = rgbDataSrc[3*srci+2];
}

static void copy_buf_swapRG(uint8_t* rgbDataSrc, uint8_t srci, uint8_t* rgbDataDest, uint8_t desti)
{
	rgbDataDest[3*desti] = rgbDataSrc[3*srci+1];
	rgbDataDest[3*desti+1] = rgbDataSrc[3*srci];
	rgbDataDest[3*desti+2] = rgbDataSrc[3*srci+2];
}

void hwversion_remap_rev1(uint8_t* rgbDataSrc, uint8_t* rgbDataDest)
{
	for(uint8_t i = 0; i < WS2811_NLEDS; i++)
	{
		if(i<2)
			copy_buf(rgbDataSrc, i, rgbDataDest, WS2811_NLEDS-1-(1-i));
		else if((i>3)&&(i<10))
			copy_buf(rgbDataSrc, i, rgbDataDest, WS2811_NLEDS-1-(10-i+3));
		else if((i>15)&&(i<18))
			copy_buf(rgbDataSrc, i, rgbDataDest, WS2811_NLEDS-1-(18-i+15));
		else
			copy_buf(rgbDataSrc, i, rgbDataDest, WS2811_NLEDS-1-(i));
	}
}

void hwversion_remap_rev2_ws2812b(uint8_t* rgbDataSrc, uint8_t* rgbDataDest)
{
	for(uint8_t i = 0; i < WS2811_NLEDS; i++)
	{
		if(i<2)
			copy_buf_swapRG(rgbDataSrc, i, rgbDataDest, WS2811_NLEDS-1-(1-i));
		else if((i>3)&&(i<10))
			copy_buf_swapRG(rgbDataSrc, i, rgbDataDest, WS2811_NLEDS-1-(10-i+3));
		else if((i>15)&&(i<18))
			copy_buf_swapRG(rgbDataSrc, i, rgbDataDest, WS2811_NLEDS-1-(18-i+15));
		else
			copy_buf_swapRG(rgbDataSrc, i, rgbDataDest, WS2811_NLEDS-1-(i));
	}
}

void hwversion_remap_none(uint8_t* rgbDataSrc, uint8_t* rgbDataDest)
{
	for(uint8_t i = 0; i < WS2811_NLEDS; i++)
		copy_buf(rgbDataSrc, i, rgbDataDest, i);
}

