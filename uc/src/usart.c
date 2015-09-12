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
#include <libopencm3/stm32/dma.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/cm3/nvic.h>
#include <stdio.h>
#include <string.h>
#include "usart.h"

#define USART_CMDLEN 256
#define USART_BUFLEN (USART_CMDLEN+2+2)
static char txBuf[USART_BUFLEN];
static char rxBuf[USART_BUFLEN];
static unsigned int rxLen = 0;
volatile uint8_t rxReq = 0;

static void usart_rx_stream(char* buf, uint16_t n);
static void usart_tx_stream(char* buf, uint16_t n);

void usart_setup(void)
{
	// clock
	rcc_periph_clock_enable(RCC_USART2);
	rcc_periph_clock_enable(RCC_GPIOA);
	// GPIO (PA2,PA3)
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2);
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO3);
	gpio_set_af(GPIOA, GPIO_AF7, GPIO2);
	gpio_set_af(GPIOA, GPIO_AF7, GPIO3);
	// USART
	USART2_BRR = (22<<4)|13; // 22.8125 => 115200 Baud @ 42 MHz (APB1)
	USART2_CR1 |= USART_CR1_TE | USART_CR1_RE; // enable tx and rx

	// setup DMA (USART2_RX: Stream 5, Channel 4, USART2_TX: Stream 6, Channel 4)
	rcc_periph_clock_enable(RCC_DMA1);

	DMA1_S5CR = DMA_SxCR_CHSEL_4;
	DMA1_S5CR |= DMA_SxCR_MINC; // increment memory address
	DMA1_S5CR |= DMA_SxCR_DIR_PERIPHERAL_TO_MEM; // peripheral to memory
	DMA1_S5CR |= DMA_SxCR_MSIZE_8BIT | DMA_SxCR_PSIZE_8BIT; // 8 bit transfers
	DMA1_S5PAR = &USART2_DR; // peripheral address
	DMA1_S5M0AR = rxBuf; // memory address
	DMA1_S5NDTR = 1; // number of bytes to be transferred
	DMA1_S5CR |= DMA_SxCR_EN | DMA_SxCR_TCIE; // enable DMA channel + transfer complete interrupt
	USART2_CR3 |= USART_CR3_DMAR; // enable receiver DMA in USART

	DMA1_S6CR = DMA_SxCR_CHSEL_4;
	DMA1_S6CR |= DMA_SxCR_MINC; // increment memory address
	DMA1_S6CR |= DMA_SxCR_DIR_MEM_TO_PERIPHERAL; // peripheral to memory
	DMA1_S6CR |= DMA_SxCR_MSIZE_8BIT | DMA_SxCR_PSIZE_8BIT; // 8 bit transfers
	DMA1_S6PAR = &USART2_DR; // peripheral address
	DMA1_S6M0AR = txBuf; // memory address
	DMA1_S6NDTR = 0; // number of bytes to be transferred
	DMA1_S6CR |= DMA_SxCR_TCIE; // enable transfer complete interrupt
	//DMA1_S6CR |= DMA_SxCR_EN | DMA_SxCR_TCIE; // enable DMA channel + transfer complete interrupt
	
	// enable interrupts
	nvic_enable_irq(NVIC_DMA1_STREAM5_IRQ);
	nvic_enable_irq(NVIC_DMA1_STREAM6_IRQ);

	// enable USART
	USART2_CR1 |= USART_CR1_UE; // enable USART
}

static void usart_rx_stream(char* buf, uint16_t n)
{
	DMA1_S5M0AR = buf; // memory address
	DMA1_S5NDTR = n; // number of bytes to be transferred
	DMA1_HIFCR |= DMA_HIFCR_CTEIF5; // clear any errors
	DMA1_S5CR |= DMA_SxCR_EN; // enable DMA channel + transfer complete interrupt
	USART2_CR3 |= USART_CR3_DMAR; // enable receiver DMA in USART
}

static void usart_tx_stream(char* buf, uint16_t n)
{
	DMA1_S6M0AR = buf; // memory address
	DMA1_S6NDTR = n; // number of bytes to be transferred
	DMA1_HIFCR |= DMA_HIFCR_CTEIF6; // clear any errors
	USART2_SR &= ~USART_SR_TC;
	USART2_CR3 |= USART_CR3_DMAT; // enable transmitter DMA in USART
	DMA1_S6CR |= DMA_SxCR_EN; // enable DMA channel + transfer complete interrupt
}


static uint8_t rxState = 0;
#define RX_STATE_STARTOFFRAME 0
#define RX_STATE_LEN 1
#define RX_STATE_DATA 2

void dma1_stream5_isr(void) // DMA RX complete interrupt
{
	if(DMA1_HISR & DMA_HISR_TCIF5) // check for transfer complete interrupt flag
	{
		DMA1_HIFCR |= DMA_HIFCR_CTCIF5; // clear flag
		USART2_CR3 |= USART_CR3_DMAR; // disable receiver DMA in USART
		
		switch(rxState)
		{
			case RX_STATE_STARTOFFRAME:
				if(rxBuf[0] == '!')
				{
					// reconfigure stream for remaining data (cmd + end of stream flag)
					usart_rx_stream(rxBuf+1, 2);
					rxState = RX_STATE_LEN;
					rxLen = 0;
				}
				else
				{
					// reset receiver
					usart_rx_stream(rxBuf, 1);
				}
				break;
			
			case RX_STATE_LEN:
				sscanf(rxBuf+1, "%02x", &rxLen);
				if(rxLen>0)
				{
					usart_rx_stream(rxBuf+3, (uint16_t)rxLen+1);
					rxState = RX_STATE_DATA;
				}
				else
				{
					// reset receiver
					rxState = RX_STATE_STARTOFFRAME;
					usart_rx_stream(rxBuf, 1);
				}
				break;

			case RX_STATE_DATA:
				if((rxBuf[3+rxLen] == ';') && !rxReq)
				{
					rxReq = 1;
					rxState = RX_STATE_STARTOFFRAME;
				}
				else
				{
					// reset receiver
					rxState = RX_STATE_STARTOFFRAME;
					usart_rx_stream(rxBuf, 1);
				}
				break;
				
		}
	}
}

void dma1_stream6_isr(void) // DMA TX complete interrupt
{
	if(DMA1_HISR & DMA_HISR_TCIF6) // check for transfer complete interrupt flag
	{
		DMA1_HIFCR |= DMA_HIFCR_CTCIF6; // clear flag
	}
}

uint8_t usart_tx_ready(void)
{
	return (USART2_SR & USART_SR_TC) && !(DMA1_S6CR & DMA_SxCR_EN);
}

uint8_t usart_rx_ready(void)
{
	return rxReq;
}

void usart_get_read(char* str, uint16_t maxlen)
{
	for(int i = 0; (i < maxlen) && (i < (uint8_t)rxLen); i++)
	{
		*str = rxBuf[3+i];
		str++;
	}
	*str = 0;
	rxReq = 0;
	usart_rx_stream(rxBuf, 1);
}

void usart_write(char* str)
{
	sprintf(txBuf, "@%02x", strlen(str));
	int i = 3;
	while(*str != 0)
	{
		txBuf[i++] = *str;
		str++;
	}
	txBuf[i++] = ';';
	usart_tx_stream(txBuf, i);
}
