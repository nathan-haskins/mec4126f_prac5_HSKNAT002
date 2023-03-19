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

// FUNCTION DECLARATIONS -----------------------------------------------------|

void main(void);                        //COMPULSORY
void display_on_LCD(uint8_t value); 	//  Question 1.1.
void init_LEDs(void);  					//  Question 1.2.
void display_on_LEDs(uint8_t value);	//  Question 1.3.
void init_switches(void);				//  Question 1.4.

// MAIN FUNCTION -------------------------------------------------------------|

void main(void)
{

	while(1);

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
					   GPIO_MODER_MODER2); //set pins PA0 (SW0) and PA1 (SW1) to GPIO inputs
	GPIOA->PUPDR |= (GPIO_PUPDR_PUPDR1_0|
					 GPIO_PUPDR_PUPDR2_0); // enable pull-up resistors: switches HIGH when open.

}
