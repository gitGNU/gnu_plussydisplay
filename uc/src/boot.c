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

#include "boot.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/flash.h>
#include <libopencm3/stm32/wwdg.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/cm3/scb.h>

//#############################################################################
//# Utility
//#############################################################################

void scb_move_vector_table(uint32_t offset)
{
	SCB_VTOR = 0x08000000 + offset;
}

//#############################################################################
//# Flash
//#############################################################################

void flash_setup(void);
void flash_erase(uint8_t sector);
void flash_write_word(uint32_t addr, uint32_t data);
void flash_write(uint32_t addr, uint8_t* buf, uint8_t len);  // len must be multiple of 4
void flash_read(uint32_t addr, uint8_t* buf, uint8_t len);  // len must be multiple of 4

void flash_setup(void)
{
	FLASH_KEYR = 0x45670123;
	FLASH_KEYR = 0xcdef89ab;
	FLASH_CR |= (uint32_t)0x00000200; // FLASH_CR_PSIZE_1; // x32 parallelism
}

void flash_erase(uint8_t sector)
{
	while(FLASH_SR & FLASH_SR_BSY);
	FLASH_CR |= FLASH_CR_SER;
	FLASH_CR = (FLASH_CR & ~(0xf<<3)) | ((sector&0xf)<<3);
	FLASH_CR |= FLASH_CR_STRT;
	while(FLASH_SR & FLASH_SR_BSY);
	FLASH_CR &= ~FLASH_CR_SER;
}

void flash_write_word(uint32_t addr, uint32_t data)
{
	while(FLASH_SR & FLASH_SR_BSY);
	FLASH_CR |= FLASH_CR_PG;
	*(volatile uint32_t*)addr = data;
	while(FLASH_SR & FLASH_SR_BSY);
	FLASH_CR &= ~FLASH_CR_PG;
}

void flash_write(uint32_t addr, uint8_t* buf, uint8_t len) // len must be multiple of 4
{
	for(uint8_t i = 0; i < (len>>2); i++)
		flash_write_word(addr+4*i, *(((uint32_t*)buf)+i) );
}

void flash_read(uint32_t addr, uint8_t* buf, uint8_t len) // len must be multiple of 4
{
	volatile uint8_t* data = (uint8_t*)addr;
	for(uint8_t i = 0; i < len; i++)
		buf[i] = data[i];
}

//#############################################################################
//# util
//#############################################################################

static void clearBuf(uint8_t* b, uint8_t start, uint8_t len)
{
	for(uint8_t i = start; i < len; i++)
		b[i] = 0;
}

//#############################################################################
//# boot
//#############################################################################

void boot_check(void)
{
	rcc_periph_clock_enable(RCC_GPIOC);
	gpio_mode_setup(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO13);
	for(volatile int i = 0; i < 1000; i++);

	if((RCC_CSR & RCC_CSR_SFTRSTF) || (!(GPIOC_IDR & (1<<13))))
	{
		// bootloader to be entered ...
		RCC_CSR |= RCC_CSR_RMVF;
	}
	else
	{
		RCC_CSR |= RCC_CSR_RMVF;

		// jump to application according to https://www.youtube.com/watch?v=cvKC-4tCRgw
		STK_CSR = 0;
		STK_RVR = 0;
		STK_CVR = 0;
		__asm volatile ("MSR msp, %0\n" : : "r" (0x20017fff) : "sp"); // addr: see linker script
		void (*app)(void) = (void*)(*((uint32_t*)0x08010004));
		app();
	}
}

void boot_setup(void)
{
	flash_setup();
}

void boot_cmd(uint8_t* bufRx, uint8_t* bufTx, uint8_t bufLen)
{
	for(uint8_t i = 0; i < bufLen; i++)
		bufTx[i] = 0;
	bufTx[0] = bufRx[0];

	switch(bufRx[0])
	{
	case 0x01:
		bufTx[1] = 0x2a;
		clearBuf(bufTx, 2, bufLen);
		break;
	case 0xf0:
		flash_write(*((uint32_t*)(bufRx+1)), bufRx+1+4, 32);
		break;
	case 0xf1:
		flash_erase(bufRx[1]);
		break;
	case 0xf2:
		flash_read(*((uint32_t*)(bufRx+1)), bufTx+1, 32);
		break;
	case 0xff:
		// leave bootloader with WWDG reset
		rcc_periph_clock_enable(RCC_WWDG);
		WWDG_CR |= WWDG_CR_WDGA;
		break;
	default:
		clearBuf(bufTx, 1, bufLen);
	}
}

