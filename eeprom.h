#define EEPROM_INIT_OK     0
#define EEPROM_INIT_RETRY  1
#define EEPROM_INIT_ERROR  2

#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "driverlib/sysctl.h"

uint32_t EEPROM_init(void);
uint32_t EEPROM_write(uint32_t *data, uint32_t addr, uint32_t count);
void EEPROM_read(uint32_t *data, uint32_t addr, uint32_t count);
uint32_t * read_contacts();
void eeprom_storeContacts();



