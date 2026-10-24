#include "stm32l4xx.h"
#include <stdio.h>
#include <stdint.h>
#include "adc.h"
#include "uart.h"
#include "systick.h"
#include "tim.h"

#define GPIOBEN					(1U<<1)
#define PIN14					(1U<<14)
#define BLUE_LED				PIN14

int main (void)
{

	RCC->AHB2ENR |= GPIOBEN;

	GPIOB->MODER |= (1U<<28);
	GPIOB->MODER &= ~(1U<<29);

	uart1_rxtx_init ();
	tim15_1hz_init ();

	while (1)
	{
		//wait for UIF
		while (!(TIM15->SR & SR_UIF)){

		}

		//Clear UIF
		TIM15->SR &=~SR_UIF;

		printf ("A second passed \n\r");
		GPIOB->ODR ^=BLUE_LED;


	}
}
