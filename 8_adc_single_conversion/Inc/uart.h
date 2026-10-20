/*
 * uart.h
 *
 *  Created on: Oct 4, 2026
 *      Author: md.sarfarajsikder
 */

#ifndef UART_H_
#define UART_H_
#include <stdint.h>
#include "stm32l4xx.h"

void uart1_rxtx_init (void);
char uart1_read(void);
void uart1_write(int ch);

#endif /* UART_H_ */
