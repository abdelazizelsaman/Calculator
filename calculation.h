#include <stdint.h>
#include <stdbool.h>
void delayMs(uint32_t n);
bool isOperand(unsigned char c);
int value( unsigned char c);
int evaluate( unsigned char *exp);
extern bool calc ;  
extern bool contact;