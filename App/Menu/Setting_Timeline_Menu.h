#ifndef SETTING_TIMELINE_MENU_H
#define SETTING_TIMELINE_MENU_H

#include "stdint.h"
#include "Timeline_Manage.h"

enum{
	IS_CHANGING_EXIT_TIMELINE,
	IS_ADDING_NEW_TIMELINE,
};

typedef enum{
	SETTING_ALARM_HOUR,
	SETTING_ALARM_MINUTE,
	SETTING_ALARM_SUNDAY,
	SETTING_ALARM_MONDAY,
	SETTING_ALARM_TUESDAY,
	SETTING_ALARM_WEDNESDAY,
	SETTING_ALARM_THUESDAY,
	SETTING_ALARM_FRIDAY,
	SETTING_ALARM_SATURDAY,
	CHECKING_ALARM_AGAIN,
}SETTING_ALARM_STATE_t;

typedef struct{
	SETTING_ALARM_STATE_t state;
	FLASH_DATA_t timeline_data;

	// use for setting day
	uint8_t current_day_state;
}ST_MENU_Data_HandleTypeDef;

void ST_MENU_Init();
void ST_MENU_Set_State();
void ST_MENU_Change_Setting_State(uint8_t p_is_increase);
void ST_MENU_Set_Value(uint8_t p_is_increase);
void ST_MENU_Set_Day();
void ST_MENU_Display();

extern ST_MENU_Data_HandleTypeDef ST_MENU_Data;

#endif
