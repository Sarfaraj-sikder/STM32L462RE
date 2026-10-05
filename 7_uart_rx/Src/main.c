#include <stdio.h>
#include <stdint.h>
#include "stm32l4xx.h"
#include "uart.h"

char data;

#define GPIOCEN					(1U<<2)
#define PIN6					(1U<<6)
#define GREEN_LED				PIN6


int main (void)
{
	//Enable clk access to LED
	RCC->AHB2ENR |= GPIOCEN;

	//PIN6 set as output
	GPIOC->MODER |= (1U<<12);
	GPIOC->MODER &= ~(1U<<13);



	uart1_rxtx_init();

	while (1)
	{
		data = uart1_read();

		if (data == '\r' || data == '\n')
		        continue;

		    uart1_write(data); //Echo


		if (data == '1')
		{
			GPIOC->ODR |= GREEN_LED;
		}
		else {
			GPIOC->ODR &= ~GREEN_LED;
		}


	}
}

