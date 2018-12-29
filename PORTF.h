#ifndef PORTF_H
#define PORTF_H
#include <stdbool.h>
#include <stdint.h>
#include "tm4c123gh6pm.h"


#define RED 	(1U << 1) // 0000 0010
#define BLUE  	(1U << 2) // 0000 0100
#define GREEN 	(1U << 3) // 0000 1000
#define WHITE 	(1U << 1)|(1U << 2)|(1U << 3)

void PORTF_Init(void);
void Led_On(uint8_t color);
void Led_Off(uint8_t color);
bool SW1_Pressed();
bool SW2_Pressed();

#endif