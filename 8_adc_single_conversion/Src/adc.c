/*
 * adc.c
 *
 *  Created on: Oct 12, 2026
 *      Author: md.sarfarajsikder
 */

#include "stm32l4xx.h"
#include "adc.h"


#define ADCEN				(1U<<13)
#define GPIOCEN				(1U<<2)
#define ADC_CH1				(1U<<6) 	//binary 1
#define CR_ADEN				(1U<<0)
#define CR_ADSTART			(1U<<2)
#define ISR_EOC				(1U<<2)

#define ADC_DEEPPWD  		(1U << 29)
#define ADC_ADVREGEN 		(1U << 28)
#define ADC_ADCAL    		(1U << 31)
#define ADC_ADRDY    		(1U << 0)


void pc0_adc_init(void)
{
    //Enable clocks for GPIOC and ADC
    RCC->AHB2ENR |= GPIOCEN;
    RCC->AHB2ENR |= ADCEN;

    //Select SYSCLK as the ADC clock for conversion
    RCC->CCIPR |=  (1U << 28);
    RCC->CCIPR |=  (1U << 29);

    //Set PC0 to analog mode
    GPIOC->MODER |=  (1U << 0);
    GPIOC->MODER |=  (1U << 1);

    //Exit ADC deep-power-down mode
    ADC1->CR &= ~ADC_DEEPPWD;

    //Enable the ADC's internal voltage regulator
    ADC1->CR |= ADC_ADVREGEN;

    // Wait for the regulator to start.
    for (volatile uint32_t i = 0; i < 100U; i++)
    {
    }

    //Calibrate the ADC for accurate reading and wait for calibration to finish
    ADC1->CR |= ADC_ADCAL;
    while (ADC1->CR & ADC_ADCAL)
    {
    }

    //Select channel 1 (PC0), with a one-channel sequence
    ADC1->SQR1 = ADC_CH1;

    //Clear the ready flag, enable ADC, and wait until it's ready
    ADC1->ISR = ADC_ADRDY;
    ADC1->CR |= CR_ADEN;

    while (!(ADC1->ISR & ADC_ADRDY))
    {
    }
}

void start_conversion (void)
{
	//Start the ADC conversion
	ADC1->CR |= CR_ADSTART;

}

uint32_t adc_read (void)
{
	//Wait for conversion to be complete
	while (!(ADC1->ISR & ISR_EOC))
	{

	}
	//read converted result
	return (ADC1->DR);
}
