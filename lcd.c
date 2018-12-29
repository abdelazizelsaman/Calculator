#include "TM4C123GH6PM.h"
#include <stdint.h>
#include "lcd.h"

#define LCD_DATA GPIOB
#define LCD_CTRL GPIOA
#define RS 0x20 /* PORTA BIT5 mask */
#define RW 0x40 /* PORTA BIT6 mask */
#define EN 0x80 /* PORTA BIT7 mask */
void LCD_command(unsigned char cmnd);
void delayUs(uint32_t n)
{
int i, j;
for(i = 0 ; i < n; i++)
for(j = 0; j < 3; j++)
{} /* do nothing for 1 us */
}
void LCD_init(void)
{
SYSCTL_RCGCGPIO_R |= 0x01; /* enable clock to GPIOA */
SYSCTL_RCGCGPIO_R |= 0x02; /* enable clock to GPIOB */
GPIO_PORTA_DIR_R |= 0xE0; /* set PORTA pin 7-5 as output for control */
GPIO_PORTA_DEN_R |= 0xE0; /* set PORTA pin 7-5 as digital pins */
GPIO_PORTB_DIR_R = 0xFF; /* set all PORTB pins as output for data */
GPIO_PORTB_DEN_R = 0xFF; /* set all PORTB pins as digital pins */
delayMs(20); /* initialization sequence */
LCD_command(0x30);
delayMs(5);
LCD_command(0x30);
delayUs(100);
LCD_command(0x30);
LCD_command(0x38); /* set 8-bit data, 2-line, 5x7 font */
LCD_command(0x06); /* move cursor right */
LCD_command(0x01); /* clear screen, move cursor to home */
LCD_command(0x0F); /* turn on display, cursor blinking */
}
void LCD_command(unsigned char cmnd)
{
GPIO_PORTA_DATA_R = 0; /* RS = 0, R/W = 0 */
GPIO_PORTB_DATA_R = cmnd;
GPIO_PORTA_DATA_R = EN; /* pulse E */
delayUs(0);
GPIO_PORTA_DATA_R = 0;
if (cmnd < 4)
delayMs(2); /* command 1 and 2 needs up to 1.64ms */
else
delayUs(40); /* all others 40 us */
}
void lcd_data(unsigned char data)
{
GPIO_PORTA_DATA_R = RS; /* RS = 1, R/W = 0 */
GPIO_PORTB_DATA_R = data;
GPIO_PORTA_DATA_R = EN | RS; /* pulse E */
delayUs(0);
GPIO_PORTA_DATA_R = 0;
delayUs(40);
}
void lcd_clear()
{
    LCD_command(1);    //clear the lcd.
    LCD_command(0x80);
}