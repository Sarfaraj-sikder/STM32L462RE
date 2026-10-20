/*
 * adc.h
 *
 *  Created on: Oct 12, 2026
 *      Author: md.sarfarajsikder
 */

#ifndef ADC_H_
#define ADC_H_


void pc0_adc_init (void);
void start_conversion (void);
uint32_t adc_read (void);


#endif /* ADC_H_ */
