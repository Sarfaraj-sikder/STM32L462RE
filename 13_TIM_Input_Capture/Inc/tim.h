/*
 * tim.h
 *
 *  Created on: Oct 22, 2026
 *      Author: md.sarfarajsikder
 */

#ifndef TIM_H_
#define TIM_H_

void tim15_1hz_init (void);
void tim15_PB14_output_compare (void);
void tim1_PE9_input_capture (void);




#define SR_UIF		(1U<<0)
#define SR_CC1IF	(1U<<1)

#endif /* TIM_H_ */
