//Using the header file
#include "stm32l4xx.h"


#define GPIOBEN					(1U<<1)
#define GPIOCEN					(1U<<2)


#define PIN14					(1U<<14)
#define PIN13					(1U<<13)
#define BLUE_LED				PIN14
#define BTN_PIN					PIN13

int main (void)
{
	//Enable clk access
	RCC->AHB2ENR |= GPIOBEN | GPIOCEN;

	//Set P14 as output PIN
	GPIOB->MODER |= (1U<<28);
	GPIOB->MODER &= ~(1U<<29);

	//Set PC13 as Input PIN
	GPIOC->MODER &= ~(1U<<26);
	GPIOC->MODER &= ~(1U<<27);

	while (1)
	{

		//Check if BTN is pressed from input data register; BTN is active low
		if (GPIOC->IDR & BTN_PIN)	//by default should be true
		{
			//Turn on LED
		GPIOB->BSRR = BLUE_LED;
		}
		else
		{
			//Turn OFF LED
		GPIOB->BSRR = (1U<<30);
		}
	}
}
