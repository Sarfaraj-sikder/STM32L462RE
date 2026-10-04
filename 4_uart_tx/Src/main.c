#include "stdint.h"
#include "stm32l4xx.h"

#define SYS_FREQ		4000000U //4 Mhz default freq on reset
#define APB2_CLK		SYS_FREQ

#define UART_BAUDRATE	115200

#define CR1_TE			(1U<<3)
#define CR1_UE			(1U<<0)

#define ISR_TXE			(1U<<7)

#define GPIOAEN			(1U<<0)
#define USART1EN		(1U<<14)


static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_bd (uint32_t PeriphClk, uint32_t BaudRate);
void uart1_tx_init (void);
void uart1_write(int ch);

//alternate fucn mapping AF7- PA9= USART1_TX, PA10=USART1_RX

int main (void)
{
	uart1_tx_init();

	while (1)
	{
		uart1_write('Y');

	}
}

void uart1_tx_init (void)
{
	/**Configure uart tx pin**/
	//Enable clk access to gpio
	RCC->AHB2ENR |= GPIOAEN;

	//set PA9 mode to alternate function mode
	GPIOA->MODER &=~ (1U<<18);
	GPIOA->MODER |= (1U<<19);

	//set PA9 alternate function type to UART_TX (AF7)
//	GPIOA->AFR[1] |= (1U<<4);
//	GPIOA->AFR[1] |= (1U<<5);
//	GPIOA->AFR[1] |= (1U<<6);
//	GPIOA->AFR[1] &=~ (1U<<7);
	GPIOA->AFR[1] = (GPIOA->AFR[1] & ~(0xFU << 4)) | (7U << 4);

	/**Configure uart module***/
	//Enable clk access to uart1
	RCC->APB2ENR  |= USART1EN;

	//configure baudrate
	uart_set_baudrate (USART1, APB2_CLK, UART_BAUDRATE);

	//configure the transfer direction
	USART1->CR1 = 0;
	USART1->CR1 = CR1_TE; //set in default UART mode with on TE high

	//Enable uart module
	USART1->CR1 |= CR1_UE;

}

void uart1_write(int ch)
{
	//Check transmit data register if empty
	while (!(USART1->ISR & ISR_TXE))
	{
	}
	//write to transmit data register
	USART1->TDR = (ch & 0xFF); //it can only hold 8 bits
}


static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate)
{
	USARTx->BRR = compute_uart_bd (PeriphClk, BaudRate);
}

static uint16_t compute_uart_bd (uint32_t PeriphClk, uint32_t BaudRate)
{
	return ((PeriphClk + (BaudRate/2U)) / BaudRate); //adding (BaudRate/2) for rounding up benefits
}
