
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/nvic.h>
#include "util.h"

//#############################################################################
//# System Utility
//#############################################################################

void util_gpio_af(uint32_t port, uint8_t pin, uint8_t af)
{
	util_gpio_mode(port, pin, GPIO_MODE_AF);
	if(pin < 8)
		GPIO_AFRL(port) = (GPIO_AFRL(port) & ~(0xf<<(pin*4))) | (af<<(pin*4));
	else
		GPIO_AFRH(port) = (GPIO_AFRH(port) & ~(0xf<<((pin-8)*4))) | (af<<((pin-8)*4));
}

void util_gpio_mode(uint32_t port, uint8_t pin, uint8_t mode)
{
	GPIO_MODER(port) = (GPIO_MODER(port) & ~(3<<(pin*2))) | (mode<<(pin*2));
}

void util_gpio_pupd(uint32_t port, uint8_t pin, uint8_t pupd)
{
	GPIO_PUPDR(port) = (GPIO_PUPDR(port) & ~(3<<(pin*2))) | (pupd<<(pin*2));
}


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

void tmr_delay_us(uint16_t delay) // max. (2^16-1) = 65535 us
{
	TIM4_PSC = 84-1; // 1 us -> 1 step
	TIM4_CNT = 0;
	TIM4_ARR = delay;
	_tmr_done = 0;
	TIM4_CR1 |= TIM_CR1_CEN;
}

void tmr_delay_ms(uint16_t delay) // max delay: ca. 32000 ms
{
	TIM4_PSC = 42000-1;
	TIM4_CNT = 0;
	TIM4_ARR = delay*2;
	_tmr_done = 0;
	TIM4_CR1 |= TIM_CR1_CEN;
}

void tmr_wait(void)
{
	while(!_tmr_done);
}

void tim4_isr(void)
{
	TIM4_CR1 &= ~TIM_CR1_CEN;
	TIM4_SR &= ~TIM_SR_UIF;
	_tmr_done = 1;
}

/*
//#############################################################################
//# USART1 (debug)
//#############################################################################

void usart1_setup()
{
	// clock
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	// GPIO (PA9,PA10)
	GPIOA->AFR[1] = (GPIOA->AFR[1] & ~((0xf<<8)|(0xf<<4))) | (7<<8)|(7<<4);
	GPIOA->MODER = (GPIOA->MODER & ~((3<<20)|(3<<18))) |  (2<<20)|(2<<18);
	// USART
	USART1->BRR = (45<<4)|9; // 45.5625 => 115200 Baud @ 84 MHz (APB2)
	USART1->CR1 |= USART_CR1_TE | USART_CR1_RE; // enable tx and rx
	USART1->CR1 |= USART_CR1_UE; // enable USART
}

void usart1_tx(uint8_t c)
{
	while(!(USART1->SR & USART_SR_TXE));
	USART1->DR = c;
}

void usart1_txS(char* s)
{
	while(*s != 0)
	{
		usart1_tx((uint8_t)*s);
		s++;
	}
}

uint8_t usart1_rx()
{
	while(!(USART1->SR & USART_SR_RXNE));
	return USART1->DR;
}

uint8_t usart1_rxReady()
{
	return (USART1->SR & USART_SR_RXNE);
}


//#############################################################################
//# USART2 (aux)
//#############################################################################

void usart2_setup()
{
	// clock
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	// GPIO (PD5,PD6)
	GPIOD->AFR[0] = (GPIOD->AFR[0] & ~((0xf<<20)|(0xf<<24))) | (7<<20)|(7<<24);
	GPIOD->MODER = (GPIOD->MODER & ~((3<<10)|(3<<12))) |  (2<<10)|(2<<12);
	// USART
	USART2->BRR = (22<<4)|13; // 22.8125 => 115200 Baud @ 42 MHz (APB1)
	USART2->CR1 |= USART_CR1_TE | USART_CR1_RE; // enable tx and rx
	USART2->CR1 |= USART_CR1_UE; // enable USART
}

void usart2_tx(uint8_t c)
{
	while(!(USART2->SR & USART_SR_TXE));
	USART2->DR = c;
}

void usart2_txS(char* s)
{
	while(*s != 0)
	{
		usart2_tx((uint8_t)*s);
		s++;
	}
}

uint8_t usart2_rx()
{
	while(!(USART2->SR & USART_SR_RXNE));
	return USART2->DR;
}

uint8_t usart2_rxReady()
{
	return (USART2->SR & USART_SR_RXNE);
}


//#############################################################################
//# USART3 (aux)
//#############################################################################

void usart3_setup()
{
	// clock
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	// GPIO (PD8,PD9)
	gpio_af(GPIOD, 8, 7);
	gpio_af(GPIOD, 9, 7);
	gpio_mode(GPIOD, 8, GPIO_MODE_AF);
	gpio_mode(GPIOD, 9, GPIO_MODE_AF);
	// USART
	USART3->BRR = (22<<4)|13; // 22.8125 => 115200 Baud @ 42 MHz (APB1)
	USART3->CR1 |= USART_CR1_TE | USART_CR1_RE; // enable tx and rx
	USART3->CR1 |= USART_CR1_UE; // enable USART
}

void usart3_tx(uint8_t c)
{
	while(!(USART3->SR & USART_SR_TXE));
	USART3->DR = c;
}

void usart3_txS(char* s)
{
	while(*s != 0)
	{
		usart3_tx((uint8_t)*s);
		s++;
	}
}

uint8_t usart3_rx()
{
	while(!(USART3->SR & USART_SR_RXNE));
	return USART3->DR;
}

uint8_t usart3_rxReady()
{
	return (USART3->SR & USART_SR_RXNE);
}
*/
