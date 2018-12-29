#include "PORTF.h"
#include <stdbool.h>
void PORTF_Init(void){
       // uint32_t dummy ;
        SYSCTL_RCGCGPIO_R |= 0x020 ;
       // dummy = SYSCTL_RCGCGPIO_R ;
        while((SYSCTL_PRGPIO_R&0x00000020) == 0){};
        GPIO_PORTF_LOCK_R = 0x4C4F434B ;
        GPIO_PORTF_CR_R = 0x01F ;
        GPIO_PORTF_DIR_R = 0x0E  ; //  0000 1110
        GPIO_PORTF_DIR_R &= ~0x11 ; // 0001 0001
        GPIO_PORTF_PUR_R |= 0x11 ; //changed from commented
        GPIO_PORTF_DEN_R |= 0x1F ;
}


void Led_On(uint8_t color){
      GPIO_PORTF_DATA_R |= color; 
}
void Led_Off(uint8_t color){
    GPIO_PORTF_DATA_R &= ~color; 
}
bool SW1_Pressed(){
  return !(GPIO_PORTF_DATA_R&0x10);
}
bool SW2_Pressed(){
  return !(GPIO_PORTF_DATA_R&0x01);
}