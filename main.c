//This project is made by:Hesham Salah Abdelfattah,Karim Amr,Mina Yousry Halim.

//the code is about making a simple calculator using an lcd and 4x4 keypad.
//the connection is (RS,RW,En)->(PA5,PA6,PA7) respectively and the remnained eight pins of the lcd to PB0->PB7.
//for the keypad the 4 pins of the rows to PE0->PE3 and the 4 pins of the columns to PD0->PD3. 

/*the RGB led should be lightened in blue when a number is pressed and turns off when a sign is pressed and again
turns on in blue when another input is pressed.Finally,if the result is calculated well it blinks the green led and any error
results in red led blinking*/

#include "TM4C123GH6PM.h"
#include <stdint.h>
#include "prototypes.h"
#include "math.h"


// these are general variables common used between all the functions. 
uint8_t sign=0;    //to store the input sign +,-,/,*
uint32_t i=0;      //index for the array of no[4]
uint8_t z=1;      // to check that no signs can come after each other ex; ++,+= and intialized with 1 to prevent begining with any sign.
uint8_t x=0;      // to calculate the operands.
uint8_t no[5];    //array to store the numbers of the operand
uint8_t key;      //to recieve the returned character
uint32_t sum;   // for the result.
uint32_t op=0;   //used in the operand calculation.


int main(void)
{
 __asm("CPSIE  I");
/* enable clock to GPIOF at clock gating control register */
SYSCTL_RCGCGPIO_R |= 0x20;
/* enable the GPIO pins for the LED (PF3, 2 1) as output */
GPIO_PORTF_DIR_R = 0x0E;
/* enable the GPIO pins for digital function */
GPIO_PORTF_DEN_R = 0x0E;
        
	      LCD_init();
        keypad_init();
      
	      LCD_command(1);    //clear the lcd.
               LCD_command(0x80); /* lcd cursor location */

        lcd_data('J');
        lcd_data('u');
        lcd_data('s');
        lcd_data('t');
        lcd_data(' ');
	      lcd_data('2');
	      lcd_data(' ');
        lcd_data('O');
        lcd_data('p');
        lcd_data('e');
        lcd_data('r');
				lcd_data('a');
        lcd_data('n');
        lcd_data('d');
        lcd_data('s');
        delayMs(3000);
        LCD_command(1);    //clear the lcd.
         while (1)
    {
    //
    // Processor enters Sleep Mode to save Power instead of Looping
    // Once Interrupt happens, Processor goes directly into Run mode
    //      
      __asm("      wfi\n");
    }
}
