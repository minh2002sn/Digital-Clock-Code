#include "timeline_manage.h"

//#define DATA_FRAME_SIZE 4 // in byte
#define DATA_FRAME_SIZE_BYTE 	(sizeof(FLASH_DATA_HandleTypeDef))	// in byte
#define DATA_FRAME_SIZE_BIT		(DATA_FRAME_SIZE_BYTE * 8)			// in bit
//#define DAY_DATA_MASK			0x0000007F
//#define HOUR_DATA_MASK			0x00000F80
//#define MINUTE_DATA_MASK		0x0003F000
//#define MASS_DATA_MASK			0xFFFC0000

TIMELINE_DATA_HandleTypdeDef TIMELINE_Data;

void TIMELINE_UART_Display(){
//	if(TIMELINE_Data.len == 0){
//		HAL_UART_Transmit(&huart2, (uint8_t *)"No data\n", 8, 1000);
//	} else{
//		for(int i = 0; i < TIMELINE_Data.len; i++){
//			char Tx_Buffer[30] = {};
//			sprintf(Tx_Buffer, "%d, %dh%dm: %d (g)\n", TIMELINE_Data.flash_data[i].day, TIMELINE_Data.flash_data[i].hour,
//					TIMELINE_Data.flash_data[i].minute, TIMELINE_Data.flash_data[i].mass);
//			HAL_UART_Transmit(&huart2, (uint8_t *)Tx_Buffer, strlen(Tx_Buffer), 1000);
//		}
//	}
}

void TIMELINE_Init(){
#ifdef __STM32F0xx_HAL_H
	TIMELINE_Data.add = FIRST_PAGE_ADD + BYTE_PER_PAGE * 63;
#endif
#ifdef __STM32F1xx_HAL_H
	TIMELINE_Data.add = FIRST_PAGE_ADD + BYTE_PER_PAGE * 63;
#endif
#ifdef __STM32F4xx_HAL_H
	TIMELINE_Data.add = SECTOR_7_ADD;
#endif

	TIMELINE_Data.len = 0;
	for(int i = 0; i < MAX_OPTIONS; i++){
		uint8_t t_data[DATA_FRAME_SIZE_BYTE];
		FLASH_Read(TIMELINE_Data.add + i*DATA_FRAME_SIZE_BYTE, t_data, DATA_FRAME_SIZE_BYTE);
		if(((uint24_t *)t_data)->value == 0xFFFFFF){
			((uint24_t *)(TIMELINE_Data.flash_data + i))->value = 0xFFFFFF;
		} else{
			TIMELINE_Data.flash_data[i] = *((FLASH_DATA_HandleTypeDef *)t_data);
			TIMELINE_Data.len++;
		}
	}
}

void TIMELINE_Add(uint8_t p_day, uint8_t p_hour, uint8_t p_minute, uint16_t p_timeline_state){
	if(TIMELINE_Data.len < MAX_OPTIONS){
		TIMELINE_Data.flash_data[TIMELINE_Data.len].day = p_day;
		TIMELINE_Data.flash_data[TIMELINE_Data.len].hour = p_hour;
		TIMELINE_Data.flash_data[TIMELINE_Data.len].minute = p_minute;
		TIMELINE_Data.flash_data[TIMELINE_Data.len].timeline_state = p_timeline_state;
		TIMELINE_Data.len++;
		TIMELINE_Sort();
		TIMELINE_Store_To_Flash();
	}
}

void TIMELINE_Change(uint8_t p_index, uint8_t p_day, uint8_t p_hour, uint8_t p_minute, uint16_t p_timeline_state){
	TIMELINE_Data.flash_data[p_index].day = p_day;
	TIMELINE_Data.flash_data[p_index].hour = p_hour;
	TIMELINE_Data.flash_data[p_index].minute = p_minute;
	TIMELINE_Data.flash_data[p_index].timeline_state = p_timeline_state;
	TIMELINE_Sort();
	TIMELINE_Store_To_Flash();
}

void TIMELINE_Delete(uint8_t p_index){
	if(TIMELINE_Data.len >= 0){
		for(int i = p_index; i < TIMELINE_Data.len - 1; i++){
			FLASH_DATA_HandleTypeDef t_temp = TIMELINE_Data.flash_data[i];
			TIMELINE_Data.flash_data[i] = TIMELINE_Data.flash_data[i+1];
			TIMELINE_Data.flash_data[i+1] = t_temp;
		}
		*(uint32_t *)(TIMELINE_Data.flash_data + TIMELINE_Data.len - 1) = 0xFFFFFFFF;
		TIMELINE_Data.len--;
		TIMELINE_Store_To_Flash();
//		CONTROL_Recheck_Time();
	}
}

void TIMELINE_Sort(){
	for(int i = 0; i < TIMELINE_Data.len; i++){
		for(int j = i + 1; j < TIMELINE_Data.len; j++){
			uint16_t t_data_i = TIMELINE_Data.flash_data[i].hour * 60 + TIMELINE_Data.flash_data[i].minute;
			uint16_t t_data_j = TIMELINE_Data.flash_data[j].hour * 60 + TIMELINE_Data.flash_data[j].minute;
			if(t_data_i > t_data_j){
				FLASH_DATA_HandleTypeDef t_temp;
				t_temp = TIMELINE_Data.flash_data[i];
				TIMELINE_Data.flash_data[i] = TIMELINE_Data.flash_data[j];
				TIMELINE_Data.flash_data[j] = t_temp;
			}
		}
	}
}

void TIMELINE_Store_To_Flash(){
	FLASH_DATA_HandleTypeDef *t_flash_data;
	t_flash_data = (FLASH_DATA_HandleTypeDef *)malloc(TIMELINE_Data.len * DATA_FRAME_SIZE_BIT);
	for(int i = 0; i < TIMELINE_Data.len; i++){
		*(t_flash_data + i) = *(TIMELINE_Data.flash_data + i);
	}
	FLASH_Write(63, (uint8_t *)t_flash_data, TIMELINE_Data.len * DATA_FRAME_SIZE_BYTE);
	free(t_flash_data);
}
