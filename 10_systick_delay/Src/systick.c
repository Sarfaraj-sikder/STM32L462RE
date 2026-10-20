/*
 * systick.c
 *
 *  Created on: Oct 20, 2026
 *      Author: md.sarfarajsikder
 */


#include "stm32l4xx.h"


#define SYSTICK_LOAD_VAL			4000 	//cycles in 1 ms as default clk 4MHz for STM32L4
#define CTRL_ENABLE					(1U<<0)
#define CTRL_CLKSRC					(1U<<2)
#define CTRL_COUNTFLAG				(1U<<16)



void systickDelayMs (int delay)
{

	//Config systick
	//Reload with number of clk/ms
	SysTick ->LOAD = SYSTICK_LOAD_VAL;

	//Clear systick current value register
	SysTick ->VAL = 0;

	//Enable systick and and internal clk src
	SysTick ->CTRL = CTRL_ENABLE | CTRL_CLKSRC;

	for (int i=0; i<delay ; i++)
	{
		//wait until the Countflag is set

		while ((SysTick ->CTRL & CTRL_COUNTFLAG) == 0) {}

	}
	SysTick -> CTRL = 0;
}
