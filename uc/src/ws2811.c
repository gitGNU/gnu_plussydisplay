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
#include <libopencm3/stm32/dma.h>
#include <libopencm3/cm3/nvic.h>

#include "ws2811.h"

// prescaler /1: 2.5us period
#define WS2811_SLOW_PERIOD 105
#define WS2811_SLOW_T0H 21
#define WS2811_SLOW_T1H 50
#define WS2811_FAST_PERIOD 60
#define WS2811_FAST_T0H 12
#define WS2811_FAST_T1H 29

#define PWM_DATA_LEN (8*3*WS2811_NLEDS+50)
// => total time: ~1.3ms

uint16_t pwmData[PWM_DATA_LEN];
static uint8_t ws2811_options = 0;

static volatile uint8_t done = 1;

static void rgb2pwm(uint8_t* rgbData)
{
	for(int i = 0; i < 20*3; i++)
	{
		uint8_t v = rgbData[i];
		for(int j = 0; j < 8; j++)
		{
			if(v & 1)
				pwmData[8*i+7-j] = ws2811_options & WS2811_OPTION_FASTMODE ?
						WS2811_FAST_T1H : WS2811_SLOW_T1H;
			else
				pwmData[8*i+7-j] = ws2811_options & WS2811_OPTION_FASTMODE ?
						WS2811_FAST_T0H : WS2811_SLOW_T0H;
			v >>= 1;
		}
	}
}

void ws2811_setup(uint8_t options)
{
	for(int i = 0; i < PWM_DATA_LEN; i++)
		pwmData[i] = 0;
	ws2811_options = options;
	
	// setup tim3 ch1 gpio
	rcc_periph_clock_enable(RCC_GPIOB);
	gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO4);
	gpio_set_af(GPIOB, GPIO_AF2, GPIO4);
	
	// setup timer
	rcc_periph_clock_enable(RCC_TIM3);
	TIM3_PSC = 0; // no prescaler, 42 MHz counter
	TIM3_ARR = ws2811_options & WS2811_OPTION_FASTMODE ?
			WS2811_FAST_PERIOD : WS2811_SLOW_PERIOD; // counter period
	TIM3_CCMR1 = TIM_CCMR1_OC1M_PWM1 | TIM_CCMR1_OC1PE; // ch1 pwm mode, preload enabled
	TIM3_CCR1 = ws2811_options & WS2811_OPTION_FASTMODE ?
			WS2811_FAST_T0H : WS2811_SLOW_T0H; // initial duty cycle
	TIM3_CCER = TIM_CCER_CC1E | ((options & WS2811_OPTION_INVPOLARITY) ? TIM_CCER_CC1P : 0); // enable channel 1, inverse polarity
	TIM3_CR1 = TIM_CR1_ARPE; // ARR preload
	TIM3_DIER = TIM_DIER_CC1DE; // enable ch1 DMA request
	
	// setup dma
	rcc_periph_clock_enable(RCC_DMA1);
	DMA1_S4CR = DMA_SxCR_CHSEL_5; // channel 5
	DMA1_S4CR |= DMA_SxCR_MINC; // increment memory address
	DMA1_S4CR |= DMA_SxCR_DIR_MEM_TO_PERIPHERAL; // memory to peripheral
	DMA1_S4CR |= DMA_SxCR_MSIZE_16BIT | DMA_SxCR_PSIZE_16BIT; // 16 bit transfers
	DMA1_S4PAR = &TIM3_CCR1; // peripheral address
	DMA1_S4M0AR = pwmData; // memory address
	DMA1_S4NDTR = PWM_DATA_LEN; // number of word to be transferred
	DMA1_S4CR |= DMA_SxCR_EN | DMA_SxCR_TCIE; // enable DMA channel + transfer complete interrupt

	// enable interrupt
	nvic_enable_irq(NVIC_DMA1_STREAM4_IRQ);
}

void dma1_stream4_isr(void)
{
	if(DMA1_HISR & DMA_HISR_TCIF4) // check for transfer complete interrupt flag
	{
		DMA1_HIFCR |= DMA_HIFCR_CTCIF4; // clear flag
		TIM3_CR1 &= ~TIM_CR1_CEN; //disable timer
		done = 1;
	}
}

uint8_t ws2811_ready(void)
{
	return done;
}

void ws2811_update(uint8_t* rgbData)
{
	if(ws2811_ready())
	{
		// convert data
		rgb2pwm(rgbData);
		// start output
		done = 0;
		DMA1_S4CR |= DMA_SxCR_EN; // DMA enable
		TIM3_CNT = 0; // reset timer
		TIM3_CR1 |= TIM_CR1_CEN; // enable timer
	}
}

