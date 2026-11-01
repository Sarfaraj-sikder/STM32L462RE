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

	//Enable timer
	TIM15->CR1 = CR1_CEN;
}
