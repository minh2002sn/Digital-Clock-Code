#ifndef REAL_TIME_H
#define REAL_TIME_H

#include "stdint.h"
#include "DS3231.h"

typedef struct{
	uint8_t system_hour;
	uint8_t system_minute;
	uint8_t system_day;
	uint8_t system_date;
	uint8_t system_month;
	uint8_t system_year;
} REALTIME_DATA_HandleTypeDef;

void REALTIME_Init();
void REALTIME_Handle();
void REALTIME_Set_New_Realtime(REALTIME_DATA_HandleTypeDef *p_new_realtime);

extern REALTIME_DATA_HandleTypeDef REALTIME_Data;

#endif
