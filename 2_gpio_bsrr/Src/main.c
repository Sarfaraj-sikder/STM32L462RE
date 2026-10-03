//Using the header file
#include "stm32l4xx.h"


#define GPIOBEN					(1U<<1)
#define PIN14					(1U<<14)
#define BLUE_LED				PIN14

int main (void)
{
	RCC->AHB2ENR |= GPIOBEN;

	GPIOB->MODER |= (1U<<28);
	GPIOB->MODER &= ~(1U<<29);

	while (1)
	{
		GPIOB->BSRR = BLUE_LED;
		for (int i=0; i<100000; i++){}

		GPIOB->BSRR = (1U<<30);
		for (int i=0; i<200000; i++){}
	}
}
