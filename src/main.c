// Description----------------------------------------------------------------|
/*
 *
 */
// DEFINES AND INCLUDES-------------------------------------------------------|

#define STM32F051												   //COMPULSORY
#include "stm32f0xx.h"											   //COMPULSORY
#include "lcd_stm32f0.h"
#include <stdio.h> // For sprintf function Question 1.1.

// GLOBAL VARIABLES ----------------------------------------------------------|

uint8_t count = 0; // Q1.5. declare and initialise the count variable to 0

// FUNCTION DECLARATIONS -----------------------------------------------------|

void main(void);                        //COMPULSORY
void display_on_LCD(uint8_t value); 	//  Question 1.1.
void init_LEDs(void);  					//  Question 1.2.
void display_on_LEDs(uint8_t value);	//  Question 1.3.
void init_switches(void);				//  Question 1.4.
void init_external_interrupts(void);    //  Question 2.1.

// MAIN FUNCTION -------------------------------------------------------------|

void main(void)
{
	init_LEDs();
	init_switches();
	init_LCD();
	display_on_LCD(count); // display the initial value of count on the LCD on RESET

	while(1)
	{
		if(!(GPIOA->IDR & GPIO_IDR_1)) // check if SW1 is pressed
		{
			while((GPIOA->IDR & GPIO_IDR_1) == 0); // wait until button SW1 is released
			count += 1;
			display_on_LCD(count);
			display_on_LEDs(count);
		}

		if(!(GPIOA->IDR & GPIO_IDR_2)) // check if SW2 is pressed
		{
			while((GPIOA->IDR & GPIO_IDR_2) == 0); // wait until button SW1 is released
			count -= 1;
			display_on_LCD(count);
			display_on_LEDs(count);
		}
	}

}

// OTHER FUNCTIONS -----------------------------------------------------------|

// Question 1.1.
void display_on_LCD(uint8_t value){
	 char buffer[4]; // C strings are null terminated: they end with null character ('\0') hence an 4 element array
	 sprintf(buffer, "%u", value); // Convert the value to a string using %u for unsigned decimal integer
	 lcd_command(CLEAR);
	 lcd_putstring(buffer);
}

// Question 1.2.
void init_LEDs(void){
	RCC -> AHBENR |= RCC_AHBENR_GPIOBEN; // enable clock for port B -LEDS
	GPIOB -> MODER |= (GPIO_MODER_MODER0_0|
					   GPIO_MODER_MODER1_0|
					   GPIO_MODER_MODER2_0|
					   GPIO_MODER_MODER3_0|
					   GPIO_MODER_MODER4_0|
					   GPIO_MODER_MODER5_0|
					   GPIO_MODER_MODER6_0|
					   GPIO_MODER_MODER7_0); // set pins PB0-PB7 as output

}

// Question 1.3.
void display_on_LEDs(uint8_t value){
	GPIOB -> ODR &= ~(GPIOB -> ODR); // resets the pins of current ODR in port B
	GPIOB -> ODR = value;
}

// Question 1.4
void init_switches(void){
	RCC -> AHBENR |= RCC_AHBENR_GPIOAEN; // enable clock for port A - switches
	GPIOA-> MODER &= ~(GPIO_MODER_MODER1|
					   GPIO_MODER_MODER2|
	  	  	  	  	   GPIO_MODER_MODER3); // set pins PA0 (SW0) and PA1 (SW1) to GPIO inputs (not strictly nessasary but included for completeness and readability).
	GPIOA->PUPDR |= (GPIO_PUPDR_PUPDR1_0|
					 GPIO_PUPDR_PUPDR2_0|
	 	 	 	 	 GPIO_PUPDR_PUPDR3_0); // enable pull-up resistors: switches HIGH when open.
}

// Question 2.1.
void init_external_interrupts(void){
	RCC -> APB2ENR |= RCC_APB2ENR_SYSCFGCOMPEN; // enable clock for sysconfig

	SYSCFG -> EXTICR[0] |= SYSCFG_EXTICR1_EXTI3_PA; // route PA3 to EXTI1 register (which is at position zero in EXTICR[x])
	EXTI-> IMR |= EXTI_IMR_MR3; // unmask the line (interrupt) connected to PA3
	EXTI -> FTSR |= EXTI_FTSR_TR3; // falling edge trigger for PA3

	NVIC_EnableIRQ(EXTI2_3_IRQn);
}
