/*
 * tim.c
 *
 *  Created on: Oct 22, 2026
 *      Author: md.sarfarajsikder
 */


#include "stm32l4xx.h"

#define TIM15EN			(1U<<16)
#define CR1_CEN			(1U<<0)

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
