#include "stm32l4xx.h"
#include <stdio.h>
#include <stdint.h>
#include "adc.h"
#include "uart.h"

uint32_t sensor_value;

int main (void)
{

	uart1_rxtx_init ();
	pc0_adc_init ();
	start_conversion ();

/**Quick Test with jumper wire**/
//Connect PC0 to a GND and check if the value is 0
//Connect PC0 to a 1.8V and check the value for 12 bit ADC : 2196
//Connect PC0 to a 3.3V and check the value for 12 bit ADC : 4092

	while (1)
	{

		sensor_value = adc_read();
		printf ("sensor value: %d \n\r", (int)sensor_value);

	}
}
