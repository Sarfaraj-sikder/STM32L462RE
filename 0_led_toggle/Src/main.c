/*LED Toggle*/
/*Green LED*/
//User LED 1 Port: C
//User LED 1 PIN: 6

/*RED LED*/
//User LED 2 Port: B
//User LED 2 PIN: 15

/*Blue LED*/
//User LED 3 Port: B
//User LED 3 PIN: 14

//GPIO Ports are connected to AHB2 80 Mhz

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

#define AHB2EN_R_OFFSET			(0x4CUL)
#define RCC_AHB2EN_R			(*(volatile unsigned int *)(RCC_BASE + AHB2EN_R_OFFSET)) //Typecasting regiters to volatile int pointer then deference for using it in code

//GPIOx Output Register
#define OD_R_OFFSET				(0x14UL)
#define GPIOB_OD_R				(*(volatile unsigned int *)(GPIOB_BASE + OD_R_OFFSET))
#define GPIOC_OD_R				(*(volatile unsigned int *)(GPIOC_BASE + OD_R_OFFSET))

//Mode Register
#define MODE_R_OFFSET 			(0x00UL)
#define GPIOB_MODE_R			(*(volatile unsigned int *)(GPIOB_BASE + MODE_R_OFFSET))
#define GPIOC_MODE_R			(*(volatile unsigned int *)(GPIOC_BASE + MODE_R_OFFSET))


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



int main (void)
{
	/*Enable CLK to GPIOB & GPIOC*/
	RCC_AHB2EN_R |= GPIOBEN;
	RCC_AHB2EN_R |= GPIOCEN;

	/*SET PIN B14, B15 & C6 as output modes*/
	//PIN14
	GPIOB_MODE_R |= (1U<<28); //set pin to 1
	GPIOB_MODE_R &= ~(1U<<29); //set pin to 0

	//PIN15
	GPIOB_MODE_R |= (1U<<30);
	GPIOB_MODE_R &= ~(1U<<31);

	//PIN6
	GPIOC_MODE_R |= (1U<<12);
	GPIOC_MODE_R &= ~(1U<<13);

	while (1)
		{
		/*Toggle C6*/
		GPIOC_OD_R ^= GREEN_LED;
		for(int i=0; i<10000; i++) {}
		/*Toggle B14*/
		GPIOB_OD_R ^= BLUE_LED;
		for(int i=0; i<20000; i++) {}

		/*Toggle B15*/
		GPIOB_OD_R ^= RED_LED;
		for(int i=0; i<5000; i++) {}

	}
}
