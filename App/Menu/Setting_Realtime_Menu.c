#include "Setting_Realtime_Menu.h"
#include "Menu.h"
#include "LCD_I2C.h"

SR_MENU_DATA_t SR_MENU_Data;

static uint8_t __max_value[6] = {23, 59, 7, 31, 12, 99};
char *__setting_type_str[6] = {
		"Hour",
		"Minute",
		"Day",
		"Date",
		"Month",
		"Year",
};

extern char DAY_Str[7][4];

void SR_MENU_Init(){
	SR_MENU_Data.state = SETTING_HOUR;
	REALTIME_DATA_HandleTypeDef t_realtime = {0, 0, 0, 0, 0, 0};
	SR_MENU_Data.new_realtime = t_realtime;
}

void SR_MENU_Set_State(){
	SR_MENU_Data.state = SETTING_HOUR;
	REALTIME_DATA_HandleTypeDef t_realtime = {0, 0, 0, 0, 0, 0};
	SR_MENU_Data.new_realtime = t_realtime;
	MENU_Data.menu_type = SETTING_REALTIME_MENU;
	MENU_Data.changed = 0;
	MENU_Data.is_changing_menu = 1;
}

void SR_MENU_Change_Setting_State(uint8_t p_is_increase){
	if(SR_MENU_Data.state == CHECKING_AGAIN){
		REALTIME_Set_New_Realtime(&SR_MENU_Data.new_realtime);
		MAIN_MENU_Set_State();
	} else{
		SR_MENU_Data.state += ((p_is_increase == INCREASE) ? 1 : -1);
		if((int8_t)SR_MENU_Data.state < 0){
			SR_MENU_Data.state = 0;
			MAIN_MENU_Set_State();
		}
		MENU_Data.menu_type = SETTING_REALTIME_MENU;
		MENU_Data.changed = 0;
	}
}

void SR_MENU_Set_Value(uint8_t p_is_increase){
	if(SR_MENU_Data.state < CHECKING_AGAIN){
		int8_t *t_data_ptr = (int8_t *)(&SR_MENU_Data.new_realtime) + SR_MENU_Data.state;
		*t_data_ptr += ((p_is_increase == INCREASE) ? 1 : -1);
		if(*t_data_ptr > __max_value[SR_MENU_Data.state]){
			*t_data_ptr = (SR_MENU_Data.state == SETTING_DATE) ? 1 : 0;
		} else if(*t_data_ptr < 0){
			*t_data_ptr = __max_value[SR_MENU_Data.state];
		}
		if(SR_MENU_Data.state == SETTING_YEAR){
			uint8_t *t_date_ptr = &SR_MENU_Data.new_realtime.system_date;
			uint8_t *t_month_ptr = &SR_MENU_Data.new_realtime.system_month;
			uint8_t *t_year_ptr = &SR_MENU_Data.new_realtime.system_year;
			if(*t_month_ptr == 2){
				if(*t_date_ptr > ((*t_year_ptr % 4 == 0) ? 29 : 28)){
					*t_date_ptr = (*t_year_ptr % 4 == 0) ? 29 : 28;
				}
			} else if((*t_month_ptr <= 7 && *t_month_ptr % 2 == 0) || (*t_month_ptr >= 8 && *t_month_ptr % 2 == 1)){
				if(*t_date_ptr > 30){
					*t_date_ptr = 30;
				}
			}
		}
	}
	MENU_Data.menu_type = SETTING_REALTIME_MENU;
	MENU_Data.changed = 0;
}

void SR_MENU_Display(){
	if(MENU_Data.is_changing_menu){
		LCD_Clear(MENU_Data.hlcd);
		MENU_Data.is_changing_menu = 0;
	}
	LCD_Set_Cursor(MENU_Data.hlcd, 0, 0);
	if(SR_MENU_Data.state < CHECKING_AGAIN){
		LCD_Write(MENU_Data.hlcd, "  Setting : %s   ", __setting_type_str[SR_MENU_Data.state]);
	} else{
		LCD_Write(MENU_Data.hlcd, "   Checking again   ");
	}
	LCD_Set_Cursor(MENU_Data.hlcd, 3, 1);
	char t_day_string[] = "SUN";
	if(SR_MENU_Data.new_realtime.system_day > 0){
		strcpy(t_day_string, DAY_Str[SR_MENU_Data.new_realtime.system_day - 1]);
	}
	LCD_Write(MENU_Data.hlcd, "%s %02d-%02d-20%02d", t_day_string,
			SR_MENU_Data.new_realtime.system_date, SR_MENU_Data.new_realtime.system_month, SR_MENU_Data.new_realtime.system_year);

	MAIN_MENU_Display_Num(SR_MENU_Data.new_realtime.system_hour / 10, 2, 2);
	MAIN_MENU_Display_Num(SR_MENU_Data.new_realtime.system_hour % 10, 6, 2);
	LCD_Set_Cursor(MENU_Data.hlcd, 9, 2);
	LCD_Send_Data(MENU_Data.hlcd, '.');
	LCD_Set_Cursor(MENU_Data.hlcd, 9, 3);
	LCD_Send_Data(MENU_Data.hlcd, '.');
	MAIN_MENU_Display_Num(SR_MENU_Data.new_realtime.system_minute / 10, 10, 2);
	MAIN_MENU_Display_Num(SR_MENU_Data.new_realtime.system_minute % 10, 14, 2);
}
