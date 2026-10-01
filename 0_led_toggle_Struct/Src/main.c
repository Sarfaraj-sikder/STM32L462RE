
#include <stdint.h>

//Peripheral base starts at:
#define PERIPH_BASE				(0x40000000UL)

//Starting address place holders
#define AHB1PERIPH_OFFSET		(0x020000UL)
#define AHB2PERIPH_OFFSET		(0x08000000UL)

#define AHB2PERIPH_BASE			(PERIPH_BASE + AHB2PERIPH_OFFSET)
#define AHB1PERIPH_BASE			(PERIPH_BASE + AHB1PERIPH_OFFSET)

#define GPIOB_OFFSET			(0x0400UL)
#define GPIOB_BASE				(AHB2PERIPH_BASE + GPIOB_OFFSET)

#define GPIOC_OFFSET			(0x0800UL)
#define GPIOC_BASE				(AHB2PERIPH_BASE + GPIOC_OFFSET)

#define RCC_OFFSET				(0x01000UL)
#define RCC_BASE				(AHB1PERIPH_BASE + RCC_OFFSET)


//Need to set EN pins high in AHB2 bus to enable GPIO CLK
#define GPIOBEN					(1U<<1)
#define GPIOCEN					(1U<<2)

//GPOI_OD_R
#define PIN6					(1U<<6)
#define GREEN_LED				PIN6

#define PIN14					(1U<<14)
#define BLUE_LED				PIN14

#define PIN15					(1U<<15)
#define RED_LED					PIN15

#define RCC			((RCC_TypeDef *) RCC_BASE)
#define GPIOB		((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC		((GPIO_TypeDef *) GPIOC_BASE)


//Struct is 32 bits
typedef struct
{
	volatile uint32_t	MODER;	//GPIO Port mode register, address offset: 0x00. Each member of the struct has 32 bit containing 4 bytes
//	__IO unit32_t	OTYPER;
//	.....
//	....
	volatile uint32_t	DUMMY [4]; // Replacing the other registers which are not needed for this project. It is a array of 4 containing 32 bits each
	volatile uint32_t 	ODR;  //GPIO port output data register, address offset: 0x14

	//any register below the ODR can be deleted as it is not needed, no dummy register is needed

}GPIO_TypeDef;


typedef struct
{
	volatile uint32_t	DUMMY[19];
	volatile uint32_t	AHB2ENR;
} RCC_TypeDef;



int main (void)
{
	/*Enable CLK to GPIOB & GPIOC*/
	RCC->AHB2ENR |=	GPIOBEN;
	RCC->AHB2ENR |=	GPIOCEN;

	/*SET PIN B14, B15 & C6 as output modes*/
	//PIN14
	GPIOB->MODER |= (1U<<28);
	GPIOB->MODER &= ~(1U<<29);

	//PIN15
	GPIOB->MODER |= (1U<<30);
	GPIOB->MODER &= ~(1U<<31);

	//PIN6
	GPIOC->MODER |= (1U<<12);
	GPIOC->MODER &= ~(1U<<13);

	while (1)
		{
		/*Toggle C6*/
		GPIOC->ODR ^= GREEN_LED;
		for(int i=0; i<10000; i++) {}

		/*Toggle B14*/
		GPIOB->ODR ^= BLUE_LED;
		for(int i=0; i<20000; i++) {}

		/*Toggle B15*/
		GPIOB->ODR ^= RED_LED;
		for(int i=0; i<5000; i++) {}

	}
}
