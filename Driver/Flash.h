#ifndef FLASH_MEMORY_H
#define FLASH_MEMORY_H
#include "STM32_reg.h"
#define Flash_Start_Address 0x40023C00UL

typedef struct {
    uint64_t ACR;       // Flash control register
    uint64_t KEYR;     // Flash key register
    uint64_t OPTKEYR;  // Flash option key register
    uint64_t SR;
    uint64_t CR;       // Flash status register
    uint64_t OPTCR;    // Flash option control register
} Flash_TypeDef;    
#define FLASH ((Flash_TypeDef *) Flash_Start_Address)
#define FLASH_SR_BSY (1 << 16)  // Flash busy flag
#define FLASH_SR_EOP (1 << 0)   // Flash end of operation flag
#define FLASH_CR_PG (1 << 0)    // Flash programming bit
#define FLASH_CR_SER (1 << 1)   // Flash sector erase bit
#define FLASH_CR_PSIZE (3 << 8) // Flash program size bits
#define FLASH_CR_SNB (7 << 3)   // Flash sector number bits
#define FLASH_CR_STRT (1 << 16) // Flash start bit
#define FLASH_CR_LOCK (1 << 31) // Flash lock bit
#define FLASH_KEY1 0x45670123UL
#define FLASH_KEY2 0xCDEF89ABUL
#define FLASH_SECTOR 7
#define FLASH_SECTOR_ADDRESS 0x08060000UL 
#endif // FLASH_MEMORY_H
void Flash_EraseSector(uint32_t sector);
void Flash_ProgramWord(uint32_t address, uint32_t data);
uint64_t Flash_read(uint32_t address);