#include <stdint.h>
void LCD_command(unsigned char cmnd);
void LCD_init(void);
void LCD_command(unsigned char cmnd);
void lcd_data(unsigned char data);
void delayUs(uint32_t n);
void delayMs(uint32_t n);
void lcd_clear();
void lcdNextLine();

