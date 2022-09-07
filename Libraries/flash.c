#include "flash.h"

void FLASH_Erase(uint32_t p_page){
	HAL_FLASH_Unlock();
	uint32_t t_PageError;
	FLASH_EraseInitTypeDef eraseInit;

#ifdef __STM32F4xx_HAL_H
	eraseInit.Banks = 1;
	eraseInit.NbSectors = 1;
	eraseInit.Sector = FLASH_SECTOR_7;
	eraseInit.VoltageRange = FLASH_VOLTAGE_RANGE_3;
	eraseInit.TypeErase = FLASH_TYPEERASE_SECTORS;
#endif

#ifdef __STM32F1xx_HAL_H
	eraseInit.Banks = 1;
	eraseInit.NbPages = 1;
	eraseInit.PageAddress = FIRST_PAGE_ADD + BYTE_PER_PAGE * (p_page);
	eraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
#endif

#ifdef __STM32F0xx_HAL_H
	eraseInit.NbPages = 1;
	eraseInit.PageAddress = FIRST_PAGE_ADD + BYTE_PER_PAGE * (p_page);
	eraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
#endif

	HAL_FLASHEx_Erase(&eraseInit, &t_PageError);
	HAL_FLASH_Lock();

//	if(FLASH->CR & FLASH_CR_LOCK){
//		FLASH->KEYR = FLASH_KEY1;
//		FLASH->KEYR = FLASH_KEY2;
//	}
//	FLASH->CR |= FLASH_CR_PER;
//	FLASH->AR = p_page;
//	FLASH->CR |= FLASH_CR_STRT;
//	while(FLASH->CR & FLASH_SR_BSY);
//	FLASH->CR &= ~FLASH_CR_PER;
//	FLASH->CR &= ~FLASH_CR_STRT;
//
//	FLASH->CR |= FLASH_CR_LOCK;
}

void FLASH_Write(uint32_t p_page, uint8_t *p_data, uint16_t p_len){
	FLASH_Erase(63);
#ifdef __STM32F4xx_HAL_H
	uint32_t t_add = SECTOR_7_ADD;
#endif
#ifdef __STM32F1xx_HAL_H
	uint32_t t_add = FIRST_PAGE_ADD + BYTE_PER_PAGE * (p_page);
#endif
#ifdef __STM32F0xx_HAL_H
	uint32_t t_add = FIRST_PAGE_ADD + BYTE_PER_PAGE * (p_page);
#endif
	HAL_FLASH_Unlock();
	for(int i = 0; i < p_len; i += 2){
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, t_add + i, p_data[i] | ((uint16_t)((i+1 >= p_len) ? 0xFF : p_data[i+1]) << 8));
	}
	HAL_FLASH_Lock();

//	f(FLASH->CR & FLASH_CR_LOCK){
//		FLASH->KEYR = FLASH_KEY1;
//		FLASH->KEYR = FLASH_KEY2;
//	}
//	FLASH->CR |= FLASH_CR_PG;
//	for(int i = 0; i < p_len; i += 2){
//		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, t_add + i, p_data[i] | (uint16_t)((i+1 >= p_len) ? 0xFF : p_data[i+1]) << 8);
//	}
}

void FLASH_Read(uint32_t add, uint8_t *p_data, uint16_t p_len){
	for(int i = 0; i < p_len; i += 2){
		uint16_t t_data = *(volatile uint16_t *)(add + i);
		p_data[i] = t_data;
		p_data[i+1] = t_data >> 8;
	}
}
