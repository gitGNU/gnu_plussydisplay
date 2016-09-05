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
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/nvic.h>
#include "util.h"


//#############################################################################
//# Delay Timer (using TIM4)
//#############################################################################

volatile uint8_t _tmr_done = 0;

void tmr_setup(void)
{
	RCC_APB1ENR |= RCC_APB1ENR_TIM4EN; // enable TIM4 clock
	TIM4_DIER |= TIM_DIER_UIE;
	nvic_enable_irq(NVIC_TIM4_IRQ);
}

#define TMR_PSC_US 48-1
#define TMR_PSC_MS 24000-1

void tmr_delay_us(uint16_t delay) // max. (2^16-1) = 65535 us
{
	TIM4_PSC = TMR_PSC_US; // 1 us -> 1 step
	TIM4_CNT = 0;
	TIM4_ARR = delay;
	_tmr_done = 0;
	TIM4_CR1 |= TIM_CR1_CEN;
}

void tmr_delay_ms(uint16_t delay) // max delay: ca. 32000 ms
{
	TIM4_PSC = TMR_PSC_MS;
	TIM4_CNT = 0;
	TIM4_ARR = delay*2;
	_tmr_done = 0;
	TIM4_CR1 |= TIM_CR1_CEN;
}

uint8_t tmr_done(void)
{
	return _tmr_done;
}

void tmr_wait(void)
{
	while(!_tmr_done);
}

uint16_t tmr_get_status(void)
{
	if(TIM4_PSC == TMR_PSC_MS)
		return TIM4_CNT/2;
	else
		return TIM4_CNT;
}

void tim4_isr(void)
{
	TIM4_CR1 &= ~TIM_CR1_CEN;
	TIM4_SR &= ~TIM_SR_UIF;
	_tmr_done = 1;
}

//#############################################################################
//# ASCII Utilities
//#############################################################################

uint8_t asciichar2halfbyte(uint8_t val)
{
	if(val >= 48 && val <= 57)
		return val - 48;
	else if(val >= 65 && val <= 70)
		return val - 65 + 10;
	else if(val >= 97 && val <= 102)
		return val - 97 + 10;
	else
		return 0;
}

uint8_t halfbyte2asciichar(uint8_t halfint)
{
	if(halfint < 10)
		return halfint + 48;
	else
		return halfint - 10 + 65;
}



void ascii_decode(uint8_t* bufIn, int lenIn)
{
	for(int i = 0; i < (lenIn>>1); i++)
	{
		bufIn[i] = (asciichar2halfbyte(bufIn[i<<1]) << 4)
				| asciichar2halfbyte(bufIn[(i<<1)+1]);
	}
}

void ascii_encode(uint8_t* bufOut, int lenOut)
{
	int lenDec = lenOut>>1;
	for(int i = 0; i < lenDec; i++)
	{
		bufOut[((lenDec-1-i)<<1)+1] = halfbyte2asciichar(bufOut[lenDec-1-i] & 0xF);
		bufOut[(lenDec-1-i)<<1] = halfbyte2asciichar(bufOut[lenDec-1-i] >> 4);
	}
}


