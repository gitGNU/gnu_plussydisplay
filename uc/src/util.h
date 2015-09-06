#ifndef UTIL_H_
#define UTIL_H_


//#############################################################################
//# System Utility
//#############################################################################

#define UTIL_GPIO_MODE_IN 0
#define UTIL_GPIO_MODE_OUT 1
#define UTIL_GPIO_MODE_AF 2
#define UTIL_GPIO_MODE_ANALOG 3
#define UTIL_GPIO_PUPD_NONE 0
#define UTIL_GPIO_PUPD_UP 1
#define UTIL_GPIO_PUPD_DN 2

void util_gpio_af(uint32_t port, uint8_t pin, uint8_t af);
void util_gpio_mode(uint32_t port, uint8_t pin, uint8_t mode);
void util_gpio_pupd(uint32_t port, uint8_t pin, uint8_t pupd);

#define util_gpio_set(port,pin) (port)->ODR |= P(pin)
#define util_gpio_clr(port,pin) (port)->ODR &= ~P(pin)
#define util_gpio_tgl(port,pin) (port)->ODR ^= P(pin)

//#############################################################################
//# Delay Timer (using TIM4)
//#############################################################################

void tmr_setup(void);
void tmr_delay_us(uint16_t delay); // max. (2^16-1) = 65535 us
void tmr_delay_ms(uint16_t delay); // max delay: 2^16/10-1 = 6552 ms
void tmr_wait(void);

//#############################################################################
//# USART1 (debug)
//#############################################################################

void usart1_setup(void);
void usart1_tx(uint8_t c);
void usart1_txS(char* s);
uint8_t usart1_rx(void);
uint8_t usart1_rxReady(void);

//#############################################################################
//# USART2 (aux)
//#############################################################################

void usart2_setup(void);
void usart2_tx(uint8_t c);
void usart2_txS(char* s);
uint8_t usart2_rx(void);
uint8_t usart2_rxReady(void);



#endif /* UTIL_H_ */
