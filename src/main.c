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

void main(void);                                                   //COMPULSORY
void display_on_LCD(uint8_t value); //  Question 1.1.

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
