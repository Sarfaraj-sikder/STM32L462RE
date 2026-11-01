#include "stm32l4xx.h"
#include <stdio.h>
#include <stdint.h>
#include "adc.h"
#include "uart.h"
#include "systick.h"
#include "tim.h"



//TIM15_CH1 is connected to PB14 (Blue LED) AF14 Alternate function

int main (void)
{

	tim15_PB14_output_compare ();

	while (1)
	{


	}
}
