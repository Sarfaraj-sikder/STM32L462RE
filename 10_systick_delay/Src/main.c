#include "stm32l4xx.h"
#include <stdio.h>
#include <stdint.h>
#include "adc.h"
#include "uart.h"
#include "systick.h"

#define GPIOBEN					(1U<<1)
#define PIN14					(1U<<14)
#define BLUE_LED				PIN14

int main (void)
{

	RCC->AHB2ENR |= GPIOBEN;

	GPIOB->MODER |= (1U<<28);
	GPIOB->MODER &= ~(1U<<29);
	uart1_rxtx_init ();

	while (1)
	{

		printf ("A second passed \n\r");
		GPIOB->ODR ^=BLUE_LED;
		systickDelayMs(1000);

	}
}
