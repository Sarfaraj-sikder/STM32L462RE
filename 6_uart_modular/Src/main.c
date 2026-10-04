#include <stdio.h>
#include <stdint.h>
#include "stm32l4xx.h"
#include "uart.h"


int main (void)
{
	uart1_tx_init();

	while (1)
	{
		printf ("Hello world \n\r");
	}
}

