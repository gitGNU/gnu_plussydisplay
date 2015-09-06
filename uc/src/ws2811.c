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
#define WS2811_PERIOD 210
#define WS2811_T0H 42
#define WS2811_T1H 100

#define PWM_DATA_LEN (8*3*WS2811_NLEDS+50)

uint16_t pwmData[PWM_DATA_LEN];
uint8_t rgbData[WS2811_NLEDS*3];

static volatile uint8_t done = 1;

/*
static void h2rgb(uint8_t* rgb, uint8_t h)
{
	uint8_t i = h/43;
	uint8_t f = h%43;
	uint8_t p = 0;
	uint8_t q = 255-f*6;
	uint8_t t = f*6;
	switch(i)
	{
		case 0: rgb[0] = 255; rgb[1] = t; rgb[2] = p; break;
		case 1: rgb[0] = q; rgb[1] = 255; rgb[2] = p; break;
		case 2: rgb[0] = p; rgb[1] = 255; rgb[2] = t; break;
		case 3: rgb[0] = p; rgb[1] = q; rgb[2] = 255; break;
		case 4: rgb[0] = t; rgb[1] = p; rgb[2] = 255; break;
		default: rgb[0] = 255; rgb[1] = p; rgb[2] = q; break;
	}
}
*/

static void rgb2pwm(void)
{
	for(int i = 0; i < 20*3; i++)
	{
		uint8_t v = rgbData[i];
		for(int j = 0; j < 8; j++)
		{
			if(v & 1)
				pwmData[8*i+j] = WS2811_T0H;
			else
				pwmData[8*i+j] = WS2811_T1H;
		}
	}
}

void ws2811_setup(void)
{
	for(int i = 0; i < PWM_DATA_LEN; i++)
		pwmData[i] = 0;
	for(int i = 0; i < WS2811_NLEDS*3; i++)
		rgbData[i] = 0;
	
	// setup tim3 ch1 gpio
	rcc_periph_clock_enable(RCC_GPIOB);
	gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO4);
	gpio_set_af(GPIOB, GPIO_AF2, GPIO4);
	
	// setup timer
	rcc_periph_clock_enable(RCC_TIM3);
	TIM3_PSC = 0; // no prescaler, 84 MHz counter
	TIM3_ARR = WS2811_PERIOD; // counter period
	TIM3_CCMR1 = TIM_CCMR1_OC1M_PWM1 | TIM_CCMR1_OC1PE; // ch1 pwm mode, preload enabled
	TIM3_CCR1 = WS2811_T0H; // initial duty cycle
	TIM3_CCER = TIM_CCER_CC1E | TIM_CCER_CC1P; // enable channel 1, inverse polarity
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


void ws2811_ledctrl(uint8_t i, uint8_t r, uint8_t g, uint8_t b)
{
	if(i < WS2811_NLEDS)
	{
		rgbData[i*3] = r;
		rgbData[i*3+1] = g;
		rgbData[i*3+2] = b;
	}
}

uint8_t ws2811_ready(void)
{
	return done;
}

void ws2811_update(void)
{
	if(ws2811_ready())
	{
		// convert data
		rgb2pwm();
		// start output
		done = 0;
		DMA1_S4CR |= DMA_SxCR_EN; // DMA enable
		TIM3_CNT = 0; // reset timer
		TIM3_CR1 |= TIM_CR1_CEN; // enable timer
	}
}

