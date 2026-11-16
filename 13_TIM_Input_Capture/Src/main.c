#include "stm32l4xx.h"
#include <stdio.h>
#include <stdint.h>
#include "adc.h"
#include "uart.h"
#include "systick.h"
#include "tim.h"


int timestamp = 0;


int main (void)
{
/*Set jumper wire from PB14 & PE9*/
	tim15_PB14_output_compare ();
	tim1_PE9_input_capture ();


	while (1)
	{

		//wait until edge is captured
		while((TIM1->SR & SR_CC1IF)){}

		//read capture value
		timestamp = TIM1->CCR1;
	}
}
