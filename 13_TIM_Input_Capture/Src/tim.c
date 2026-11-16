/*
 * tim.c
 *
 *  Created on: Oct 22, 2026
 *      Author: md.sarfarajsikder
 */


#include "stm32l4xx.h"

#define TIM15EN			(1U<<16)
#define CR1_CEN			(1U<<0)

#define OC1M_CLEAR 		((1U<<6) | (1U<<5) | (1U<<4))
#define CC1S_CLEAR 		((1U<<1) | (1U<<0))
#define OC_TOGGLE		((1U<<4) | (1U<<5))
#define CCER_CC1E		(1U<<0)

#define GPIOBEN			(1U<<1)
#define PIN14			(1U<<14)
#define BLUE_LED		PIN14

#define AFR14_MASK  	((1U<<27) | (1U<<26) | (1U<<25) | (1U<<24))
#define AFR14_TIM 		((1U<<27) | (1U<<26) | (1U<<25))
#define MOE				(1U<<15)


#define GPIOEEN			(1U<<4)
#define TIM1EN			(1U<<11)
#define AFR9_MASK  		((1U<<7) | (1U<<6) | (1U<<5) | (1U<<4))
#define AFR9_TIM 		(1U<<4)

#define CCMR_CC1S		(1U<<0)

#define TIM_CC1E    	(1U << 0)



//timer for 1 s
void tim15_1hz_init (void)
{
	//Enable clk access to tim15
	RCC->APB2ENR |= TIM15EN;

	//set prescaler value
	TIM15->PSC = 400 - 1; // 4 000 000/ 4 00 = 10 000

	//set auto-reload value
	TIM15->ARR = 10000 -1; // 10 000 / 10 000 =1Hz

	//clear counter
	TIM15-> CNT =0;

	//Enable timer
	TIM15->CR1 = CR1_CEN;
}

void tim15_PB14_output_compare (void)
{
	//Enable clk to GPIOB
	RCC->AHB2ENR |= GPIOBEN;
	//Enable clk access to tim15
	RCC->APB2ENR |= TIM15EN;

	//PB14 Alternate function mode
	GPIOB->MODER |= (1U<<29);
	GPIOB->MODER &= ~(1U<<28);

	//Set PB14 alternate function type to TIM15_CH1 (AF14)
	GPIOB->AFR[1] &= ~AFR14_MASK; //clear the bits
	GPIOB->AFR[1] |= AFR14_TIM;

	//Enable clk access to tim15
	RCC->APB2ENR |= TIM15EN;

	//set prescaler value
	TIM15->PSC = 400 - 1; // 4 000 000/ 4 00 = 10 000

	//set auto-reload value
	TIM15->ARR = 4999; // 10 kHz / (4999+1) =2 complete counter periods per sec
	TIM15->CCR1 = 2500;

	//Set the output compare toggle mode 011
	TIM15->CCMR1 &= ~(OC1M_CLEAR | CC1S_CLEAR);
	TIM15->CCMR1 |= OC_TOGGLE;

	//Enable tim15 ch1 in compare mode
	TIM15->CCER |= CCER_CC1E;
	TIM15->BDTR |= MOE;

	//clear counter
	TIM15-> CNT =0;

	//Set Event Generation Register
	TIM15->EGR = 1U;

	//Enable timer 15
	TIM15->CR1 = CR1_CEN;
}



void tim1_PE9_input_capture (void)
{
	//Enable clk to GPIOE
	RCC->AHB2ENR |= GPIOEEN;
	//Enable clk access to tim1
	RCC->APB2ENR |= TIM1EN;

	//PE9 Alternate function mode
	GPIOE->MODER |= (1U<<19);
	GPIOE->MODER &= ~(1U<<18);

	//No internal pull-up or pull-down registers
	GPIOE->PUPDR &= ~(1U << 18);
	GPIOE->PUPDR &= ~(1U << 19);

	//Set PE9 alternate function type to TIM1_CH1 (AF1)
	GPIOE->AFR[1] &= ~AFR9_MASK; //clear the bits
	GPIOE->AFR[1] |= AFR9_TIM;

	//set prescaler value
	TIM1->CR1 = 0;       // Keep the timer stopped while configuring it.
	TIM1->PSC = 400 - 1; // 4 000 000/ 4 00 = 10 000
	TIM1->ARR = 0xFFFF;  // Count up to the largest 16-bit value, then wrap to 0.

	//Set CH1 to capture at every edge
	TIM1->CCMR1 = CCMR_CC1S;

	//Set CH1 to capture at rising edge
	// CC1P is bit 1 and CC1NP is bit 3; both are 0 for rising edges.
	TIM1->CCER &= ~(1U << 1);
	TIM1->CCER &= ~(1U << 3);

	// Apply the prescaler setting and clear any old timer flags.
	TIM1->EGR = (1U << 0);  // Generate an update event to load the prescaler.
	TIM1->SR = 0;           // Clear pending status flags.

	//Enable TIM1
	TIM1->CCER |= TIM_CC1E;
	TIM1->CR1  |= CR1_CEN;


}
