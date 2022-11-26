#include "Battery_Value.h"

extern ADC_HandleTypeDef hadc1;

BATTERY_LEVEL_DATA_t BATTERY_LEVEL_Data;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc){
	if(hadc->Instance == hadc1.Instance){
		BATTERY_LEVEL_Data.ADC_Value = HAL_ADC_GetValue(&hadc1);
		BATTERY_LEVEL_Data.batterry_voltage = BATTERY_LEVEL_Data.ADC_Value * 3.3 / 4096.0 * 3.2;
		BATTERY_LEVEL_Data.battery_level = (8.4 - BATTERY_LEVEL_Data.batterry_voltage) / 1.0 * 100;
	}
}

void BATTERY_LEVEL_Init(){
	BATTERY_LEVEL_Data.batterry_voltage = 0.0;
	BATTERY_LEVEL_Data.battery_level = 100;
	BATTERY_LEVEL_Data.ADC_Value = 0;
	HAL_ADC_Start_IT(&hadc1);
}

void BATTERY_LEVEL_Handle(){
	static uint32_t adc_conversion_timer = 0;
	if(HAL_GetTick() - adc_conversion_timer > 10000){
		HAL_ADC_Start_IT(&hadc1);
		adc_conversion_timer = HAL_GetTick();
	}
}
