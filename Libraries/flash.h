#ifndef FLASH_H
#define FLASH_H

#include "main.h"
#include "stdint.h"

#ifdef __STM32F4xx_HAL_H
#define SECTOR_7_ADD 0x08060000
#endif

#ifdef __STM32F1xx_HAL_H
#define FIRST_PAGE_ADD 0x08000000
#define BYTE_PER_PAGE  1024
#endif

#ifdef __STM32F0xx_HAL_H
#define FIRST_PAGE_ADD 0x08000000
#define BYTE_PER_PAGE  1024
#endif

void FLASH_Erase(uint32_t p_page);
void FLASH_Write(uint32_t p_page, uint8_t *p_data, uint16_t p_len);
void FLASH_Read(uint32_t p_add, uint8_t *p_data, uint16_t p_len);

#endif
