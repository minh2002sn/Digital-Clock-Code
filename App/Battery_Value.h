#ifndef BATERRY_VALUE_H
#define BATERRY_VALUE_H

#include "main.h"

typedef struct{
	float batterry_voltage;
	uint8_t battery_level;
	uint32_t ADC_Value;
} BATTERY_LEVEL_DATA_t;

void BATTERY_LEVEL_Init();
void BATTERY_LEVEL_Handle();

extern BATTERY_LEVEL_DATA_t BATTERY_LEVEL_Data;

#endif
