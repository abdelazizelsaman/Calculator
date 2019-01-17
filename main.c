//This project is made by:Hesham Salah Abdelfattah,Karim Amr,Mina Yousry Halim.

//the code is about making a simple calculator using an lcd and 4x4 keypad.
//the connection is (RS,RW,En)->(PA5,PA6,PA7) respectively and the remnained eight pins of the lcd to PB0->PB7.
//for the keypad the 4 pins of the rows to PE0->PE3 and the 4 pins of the columns to PD0->PD3. 

/*the RGB led should be lightened in blue when a number is pressed and turns off when a sign is pressed and again
turns on in blue when another input is pressed.Finally,if the result is calculated well it blinks the green led and any error
results in red led blinking*/

#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "lcd.h"
#include "math.h"
#include "calculation.h"
#include "keypad.h"
#include "eeprom.h"
void welcomeMessage()
{
    lcd_clear();
  lcd_data('p');
  lcd_data('r');
  lcd_data('e');
  lcd_data('s');
  lcd_data('s');
  lcd_data(' ');
  lcd_data('1');
  lcd_data(' ');
  lcd_data('f');
  lcd_data('o');
  lcd_data('r');
  lcd_data(' ');
  lcd_data('c');
  lcd_data('a');
  lcd_data('l');
  lcd_data('c');
  delayMs(2000);
 lcd_clear();
  lcd_data('2');
  lcd_data(' ');
  lcd_data('f');
  lcd_data('o');
  lcd_data('r');
  lcd_data(' ');
  lcd_data('c');
  lcd_data('o');
  lcd_data('n');
  lcd_data('t');
  lcd_data('a');
  lcd_data('c');
  lcd_data('t');
  lcd_data('s');
}
void calcMessage()
{
  lcd_clear();

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
        delayMs(2000);
        LCD_command(1);    //clear the lcd.
}
void displayContacts()
{
  uint32_t *contacts = read_contacts();
    lcd_clear();
    int i=0;
  for(;;i++)
  {
    if(contacts[i]== '@')
    {
      i++;
      break;
    }
    lcd_data(contacts[i]);
  }
  lcdNextLine();
  for(;;i++)
  {
   if(contacts[i]== '@')
   break;
    lcd_data(contacts[i]);
  }
}

int main(void)
{
 __asm("CPSIE  I");

	      LCD_init();
        keypad_init();
      
	      
        
    while (1)
    {
      if(!calc && !contact)
        welcomeMessage();
      if(calc)
        calcMessage();
        if(contact)
          displayContacts();
    }
}
