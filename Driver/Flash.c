#include "Flash_memory.h"
#include "STM32_reg.h"
void Flash_Unlock(void)
{
    if (FLASH->CR & FLASH_CR_LOCK) // Check if flash is locked
    {
        FLASH->KEYR = FLASH_KEY1; // Write first key
        FLASH->KEYR = FLASH_KEY2; // Write second key
    }
}
void Flash_Lock(void)
{
    FLASH->CR |= FLASH_CR_LOCK; // Set the lock bit
}
void Flash_WaitForLastOperation(void)
{
    while (FLASH->SR & FLASH_SR_BSY); // Wait until the busy flag is cleared
}
void Flash_EraseSector(uint32_t sector)
{
    Flash_Unlock(); // Unlock the flash memory
    Flash_WaitForLastOperation(); // Wait for any ongoing operation to complete
    FLASH->CR &= ~(0xF << FLASH_CR_SNB);
    FLASH->CR |= (FLASH_SECTOR << FLASH_CR_SNB);// set the sector number to erase
    FLASH->CR |= FLASH_CR_SER; // Set the sector erase bit
    FLASH->CR |= FLASH_CR_STRT; // Start the erase operation
    Flash_WaitForLastOperation(); 
    Flash_Lock(); // Lock the flash memory after operation
}
void Flash_ProgramWord(uint32_t address, uint32_t data) // Program a word (32 bits) at the specified address
{
    Flash_Unlock(); // Unlock the flash memory
    Flash_WaitForLastOperation(); // Wait for any ongoing operation to complete
    FLASH->CR &= ~(0x3 << FLASH_CR_PSIZE); // Clear the program size bits
    FLASH->CR |= (0x2 << FLASH_CR_PSIZE); // Set the program size to 32 bits
    FLASH->CR |= FLASH_CR_PG; // Set the programming bit

    *(volatile uint32_t *)address = data; // Write the data to the specified address
    Flash_WaitForLastOperation(); // Wait for the programming operation to complete
    Flash_Lock(); // Lock the flash memory after operation
}
uint64_t Flash_read(uint32_t address)
{
    return *(volatile uint32_t *)address; // Read the data from the specified address
}