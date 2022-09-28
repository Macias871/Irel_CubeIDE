#ifndef __EEPROM_H
#define __EEPROM_H

#ifdef __cplusplus
	extern "C" {
#endif

#include "stm32l1xx_hal.h"
#include "cmsis_os.h"
#include "../../config.h"
#include "stm32l1xx_hal_flash_ex.h"





typedef enum {
	EEPROM_COMPLETE = 0,
	EEPROM_TIMEOUT  = 1
} EEPROM_Status;



// Data EEPROM start and end address
#define DATA_EEPROM_START_ADDR     0x08080000
#define DATA_EEPROM_END_ADDR       0x08080FF0

// Timeout value for EEPROM operations
#define EEPROM_PRG_TIMEOUT         (uint32_t)0x8000


// Function prototypes
void EEPROM_Unlock(void);
void EEPROM_Lock(void);
EEPROM_Status EEPROM_WaitForLastOperation(uint32_t Timeout);
EEPROM_Status EEPROM_Write(uint32_t Address, uint16_t Data);
uint16_t EEPROM_Read(uint32_t address);

void ReadBuffer_EEPROM(uint32_t addr, volatile uint16_t *buffer, uint16_t len);
void SaveBuffer_EEPROM(uint32_t addr, volatile uint16_t *buffer, uint16_t len);




#ifdef __cplusplus
	}
#endif

#endif /* __EEPROM_H */
