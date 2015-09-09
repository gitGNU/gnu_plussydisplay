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
#include "ws2811.h"
#include "util.h"
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
	
	uint8_t* rgbData = 0;
	uint16_t rgbDataLen = 0;
	ws2811_get_buffer(&rgbData, &rgbDataLen);

	while (1)
	{
		// configure display update timer with period per frame (100 Hz)
		tmr_delay_ms(10);
		// toggle LED
		gpio_toggle(GPIOA, GPIO5);
		// calculate next frame
		anim_test(rgbData, rgbDataLen);
		// wait if frame time has not yet passed
		tmr_wait();
		// trigger display update
		ws2811_update();
	}

	return 0;
}
