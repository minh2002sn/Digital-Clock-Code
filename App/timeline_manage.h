#ifndef TIME_MANAGE_H
#define TIME_MANAGE_H

#define MAX_OPTIONS 14

//#include "control.h"
#include "flash.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct{
	uint32_t value			:24;
} __attribute__((packed)) uint24_t;

enum{
	TIMELINE_OFF,
	TIMELINE_ON,
};

typedef struct{
	uint8_t day				:7;
	uint8_t hour			:5;
	uint8_t minute			:6;
	uint8_t timeline_state	:6;
} __attribute__((packed)) FLASH_DATA_HandleTypeDef;

typedef struct{
	uint32_t add;
	FLASH_DATA_HandleTypeDef flash_data[MAX_OPTIONS];
	uint8_t len;
}TIMELINE_DATA_HandleTypdeDef;

void TIMELINE_Init();
void TIMELINE_Add(uint8_t p_day, uint8_t p_hour, uint8_t p_minute, uint16_t p_timeline_state);
void TIMELINE_Change(uint8_t p_index, uint8_t p_day, uint8_t p_hour, uint8_t p_minute, uint16_t p_timeline_state);
void TIMELINE_Delete(uint8_t p_index);
void TIMELINE_Sort();
void TIMELINE_Store_To_Flash();
void TIMELINE_UART_Display();

extern TIMELINE_DATA_HandleTypdeDef TIMELINE_Data;

#endif
