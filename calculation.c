
#include "tm4c123gh6pm.h"
#include "keypad.h"
#include "lcd.h"
#include <stdint.h>
#include <stdbool.h>

unsigned char exp[5];
bool flag = false;
int i ;
bool isOperand(unsigned char c) { 
    return (c >= '0' && c <= '9'); 
    } 
  
// utility function to find value of and operand 
int value( unsigned char c) {  
    return (c - '0'); 
    } 
  
// This function evaluates simple expressions. It returns -1 if the 
// given expression is invalid. 
int evaluate( unsigned char *exp) 
{ 
    // Base Case: Given expression is empty 
    if (*exp == '\0')  return -1; 
  
    // The first character must be an operand, find its value 
    int res = value(exp[0]); 
  
    // Traverse the remaining characters in pairs 
    for (int i = 1; exp[i]; i += 2) 
    { 
        // The next character must be an operator, and 
        // next to next an operand 
        char opr = exp[i], opd = exp[i+1]; 
  
        // If next to next character is not an operand 
        if (!isOperand(opd))  return -1; 
  
        // Update result according to the operator 
        if (opr == '+')       res += value(opd); 
        else if (opr == '-')  res -= value(opd); 
        else if (opr == '*')  res *= value(opd); 
        else if (opr == '/')  res /= value(opd); 
  
        // If not a valid operator 
        else                  return -1; 
    } 
    return res; 
}
void inttochar(int x1)
{
  int y = x1%10;
  int z = x1/10;
  if(z!=0)
  lcd_data(z+'0');
  lcd_data(y+'0');
}

void GPIO_PORTC_Handler(void){
    if(!flag)
        {
            lcd_clear();
            i=0;
            flag = true;
        }
  delayMs(200);
  unsigned char character = keypad_getkey(); 
  if( character !=0)
  {
  if ( character == '=')
    {
        exp[i]='\0';
        lcd_data(character);
        int x = evaluate(exp);
        inttochar(x);
        delayMs(1000);
        flag =false;
    }
  else 
  {
      lcd_data(character);
      exp[i] = character;
      i++;
  }
  }
}