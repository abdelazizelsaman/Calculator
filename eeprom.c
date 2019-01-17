
//#define EEPROM_EESIZE_R         (*((volatile unsigned long *)0x400AF000))
//#define EEPROM_EEBLOCK_R        (*((volatile unsigned long *)0x400AF004))
//#define EEPROM_EEOFFSET_R       (*((volatile unsigned long *)0x400AF008))
//#define EEPROM_EERDWR_R         (*((volatile unsigned long *)0x400AF010))
//#define EEPROM_EERDWRINC_R      (*((volatile unsigned long *)0x400AF014))
//#define EEPROM_EEDONE_R         (*((volatile unsigned long *)0x400AF018))
//#define EEPROM_EESUPP_R         (*((volatile unsigned long *)0x400AF01C))
//#define EEPROM_EEUNLOCK_R       (*((volatile unsigned long *)0x400AF020))
//#define EEPROM_EEPROT_R         (*((volatile unsigned long *)0x400AF030))
//#define EEPROM_EEPASS0_R        (*((volatile unsigned long *)0x400AF034))
//#define EEPROM_EEPASS1_R        (*((volatile unsigned long *)0x400AF038))
//#define EEPROM_EEPASS2_R        (*((volatile unsigned long *)0x400AF03C))
//#define EEPROM_EEINT_R          (*((volatile unsigned long *)0x400AF040))
//#define EEPROM_EEHIDE_R         (*((volatile unsigned long *)0x400AF050))
//#define EEPROM_EEDBGME_R        (*((volatile unsigned long *)0x400AF080))
//#define EEPROM_PP_R             (*((volatile unsigned long *)0x400AFFC0))

//#define EEPROM_EEDONE_WORKING   0x00000001  // EEPROM Working

//#define SYSCTL_SREEPROM_R       (*((volatile unsigned long *)0x400FE558))
//#define SYSCTL_RCGCEEPROM_R     (*((volatile unsigned long *)0x400FE658))
//#define SYSCTL_RCGCEEPROM_R0    0x00000001  // EEPROM Module Run Mode Clock
//#define EEPROM_EESUPP_PRETRY    0x00000008  // Programming Must Be Retried
//#define EEPROM_EESUPP_ERETRY    0x00000004  // Erase Must Be Retried                                          // Gating Control

#define EEPROM_INIT_OK     0
#define EEPROM_INIT_RETRY  1
#define EEPROM_INIT_ERROR  2
#define OFFSET_FROM_ADDR(x) (((x) >> 2) & 0x0F)
#define EEPROMBlockFromAddr(ui32Addr) ((ui32Addr) >> 6)
#include "eeprom.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "tm4c123gh6pm.h"
#include "driverlib/sysctl.h"
//#include "driverlib/eeprom.h"
  uint32_t pwData[] = {'m','o','h','a','m','e','d','@','0','1','2','7','8','4','4','4','4','@'}; 

uint32_t EEPROM_init(void){
  uint32_t ui32Status;
  
  SysCtlDelay(2);  
  //SYSCTL_RCGCEEPROM_R = 0x00000001;
  while(EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING);
  ui32Status = EEPROM_EESUPP_R;
  
  if(ui32Status & (EEPROM_EESUPP_PRETRY | EEPROM_EESUPP_ERETRY))
  {
    SYSCTL_SREEPROM_R = 0x00000001;
    SysCtlDelay(2);
    SYSCTL_SREEPROM_R = 0x00000000;

    while(EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING);
    ui32Status = EEPROM_EESUPP_R;
    if(ui32Status & (EEPROM_EESUPP_PRETRY | EEPROM_EESUPP_ERETRY))
      return EEPROM_INIT_ERROR;
    else
      return EEPROM_INIT_RETRY;
  }
  
  return EEPROM_INIT_OK;
}

uint32_t EEPROM_write(uint32_t *data, uint32_t addr, uint32_t count){
  
  uint32_t ui32Status;
  
  do{
    ui32Status = EEPROM_EEDONE_R;
  }
  while(ui32Status & EEPROM_EEDONE_WORKING);
  
  EEPROM_EEBLOCK_R = EEPROMBlockFromAddr(addr);
  EEPROM_EEOFFSET_R = OFFSET_FROM_ADDR(addr);
  
  while(count){
    EEPROM_EERDWR_R = *data;
     do{
    ui32Status = EEPROM_EEDONE_R;
    }
    while(ui32Status & EEPROM_EEDONE_WORKING);
  
    data++;
    count--;
    EEPROM_EEOFFSET_R++;
    
    if(EEPROM_EEOFFSET_R == 0)
      EEPROM_EEBLOCK_R += 1;   
  }
  
return EEPROM_EEDONE_R;
}

void EEPROM_read(uint32_t *data, uint32_t addr, uint32_t count){
  
  EEPROM_EEBLOCK_R = EEPROMBlockFromAddr(addr);
  EEPROM_EEOFFSET_R = OFFSET_FROM_ADDR(addr);
  
  while(count){   
    *data = EEPROM_EERDWR_R;
    data++;
    count--;
    EEPROM_EEOFFSET_R++;    
    if(EEPROM_EEOFFSET_R == 0)
      EEPROM_EEBLOCK_R += 1;   
  }    
  
}
void eeprom_storeContacts()
{
 uint32_t Status;
  
  uint32_t addr = 0x100;
  uint32_t count = 4;
  
  SYSCTL_RCGCEEPROM_R = 0x00000001;
  
   Status = EEPROM_init();

   
   Status = EEPROM_write(pwData, addr, sizeof(pwData));
   
}

uint32_t * read_contacts()
{
  uint32_t addr = 0x100;
  static uint32_t prData[4];

   EEPROM_read(prData, addr, sizeof(pwData));
   
   printf("prData[0] = %x\n", prData[0]);
   printf("prData[1] = %x\n", prData[1]);
   printf("prData[2] = %x\n", prData[2]);
   printf("prData[3] = %x\n", prData[3]);
   return prData ;
}