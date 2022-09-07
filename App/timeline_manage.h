#ifndef TIMELINE_MANAGE_H
#define TIMELINE_MANAGE_H

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
	uint8_t hour;
	uint8_t minute;
	uint8_t day;
	uint8_t timeline_state;
} __attribute__((packed)) FLASH_DATA_t;

typedef struct{
	uint32_t add;
	FLASH_DATA_t flash_data[MAX_OPTIONS];
	uint8_t len;
}TIMELINE_DATA_HandleTypdeDef;

void TIMELINE_Init();
void TIMELINE_Add(FLASH_DATA_t *p_new_timeline);
void TIMELINE_Change(FLASH_DATA_t *p_des_timeline, FLASH_DATA_t *p_new_timeline);
void TIMELINE_Delete(uint8_t p_index);
void TIMELINE_Sort();
void TIMELINE_Store_To_Flash();
void TIMELINE_UART_Display();

extern TIMELINE_DATA_HandleTypdeDef TIMELINE_Data;

#endif
