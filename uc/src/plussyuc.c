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

#define PLUSSYUC_C_

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/flash.h>
#include <libopencm3/stm32/gpio.h>
#include <stdio.h>
#include <string.h>

#include "boot.h"
#include "hwinit.h"
#include "ws2811.h"
#include "util.h"
#include "usart.h"
#include "usb.h"
#include "cmd.h"
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

const struct rcc_clock_scale clock_config =
{ // 48MHz
	.pllm = 12,
	.plln = 96,
	.pllp = 2,
	.pllq = 2,
	.pllr = 0,
	.hpre = RCC_CFGR_HPRE_DIV_NONE,
	.ppre1 = RCC_CFGR_PPRE_DIV_2,
	.ppre2 = RCC_CFGR_PPRE_DIV_2,
	.power_save = 1,
	.flash_config = FLASH_ACR_ICE | FLASH_ACR_DCE |
			FLASH_ACR_LATENCY_3WS,
	.ahb_frequency  = 48000000,
	.apb1_frequency = 24000000,
	.apb2_frequency = 24000000,
};


int main(void)
{
#ifdef BOOT
	boot_check();
	boot_setup();
#else
	// non-bootloader: move vector table to user space
	scb_move_vector_table(0x10000);
#endif

	rcc_clock_setup_hse_3v3(&clock_config);
	gpio_setup();
	hwversion_setup();
	btn_setup();
	tmr_setup();
	usart_setup();
	cmd_setup();
	
	struct plussy_params p;

	p.rgbDataLen = WS2811_NLEDS*3;

	// data before mapping, first non-pcb variant
	uint8_t rgbData[p.rgbDataLen];
	uint8_t rgbDataManual[p.rgbDataLen];
	p.rgbData = rgbData;
	p.rgbDataManual = rgbDataManual;

	// data mapped to device version
	uint8_t rgbDataDev[p.rgbDataLen];

	// initialize data
	for(int i = 0; i < p.rgbDataLen; i++)
		rgbData[i] = 0;
	for(int i = 0; i < p.rgbDataLen; i++)
		rgbDataManual[i] = 0;
	for(int i = 0; i < p.rgbDataLen; i++)
		rgbDataDev[i] = 0;

	// options
	p.brightnessScale = 0xff;

	// animation table
	p.animSel = -1;
	p.animSelMax = -1;

	while(animTable[p.animSelMax+1].name) // find end of table
		p.animSelMax++;

	// detect hardware version
	tmr_delay_us(10000);
	tmr_wait();
	uint8_t hwver = hwversion_detect();
	void (*hwmap)(uint8_t*, uint8_t*) = hwversion_remap_none; // args: src,dest
	uint8_t ws2811_options = WS2811_OPTION_INVPOLARITY;
	
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
	case 7: // rev7 is PCB labeled "lightctrl v1" with 8 channels and RS485 drivers connected to WS2812B SMD LEDs
		ws2811_options &= ~WS2811_OPTION_INVPOLARITY; // has no inverting transistor driver
		break;
	default: // unknown revision, assume no mapping
		break;
	}
	
	// init usb
	if(hwver >= 2)
		usb_setup();

	// init led driver
	ws2811_setup(ws2811_options);

	// main loop
	p.compTime = 0;
	uint8_t btnLastPressed = 0;


#ifdef BOOT
	ws2811_update(rgbDataDev);
#endif

	while (1)
	{
#ifdef BOOT
		if(tmr_done())
		{
			// toggle LED
			gpio_toggle(GPIOA, GPIO5);
			// configure toggle led timer
			tmr_delay_ms(200);
		}
#else
		// toggle LED
		gpio_toggle(GPIOA, GPIO5);
		// configure display update timer with period per frame (100 Hz)
		tmr_delay_us(10000);
#endif
		
		// check for commands
		if(hwver >= 2)
			usb_poll();
		cmd_proc(&p);

		// check if button pressed (de-bouncing through 10ms loop delay)
		if(!btnLastPressed && btn_pressed())
		{
			#ifndef BOOT
			if(p.animSel == p.animSelMax)
				p.animSel = -1;
			else
				p.animSel++;
			#endif
			btnLastPressed = 1;
		}
		else if(!btn_pressed())
		{
			btnLastPressed = 0;
		}

#ifndef BOOT
		// calculate next frame
		if(p.animSel >= 0)
			animTable[p.animSel].func(p.rgbData, p.rgbDataLen);
		// remap data
		if(p.animSel < 0)
			hwmap(p.rgbDataManual, rgbDataDev);
		else
			hwmap(p.rgbData, rgbDataDev);
		// scale brightness
		for(uint8_t i = 0; i < WS2811_NLEDS; i++)
			bscale(rgbDataDev+3*i, p.brightnessScale);
		// determine how much time has passed
		p.compTime = tmr_get_status(); // TODO: ouput to serial port?
		// wait if frame time has not yet passed
		while(!tmr_done())
			usb_poll();
		// trigger display update
		ws2811_update(rgbDataDev);
#endif
	}

	return 0;
}

