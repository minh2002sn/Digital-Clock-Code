#include "Menu.h"

SETTING_MENU_t SETTING_MENU_Data;

void SETTING_MENU_Init(){
	SETTING_MENU_Data.current_pointer = 0;
	SETTING_MENU_Data.is_setting_time_format = 0;
}

void SETTING_MENU_Set_State(){
	MENU_Data.menu_type = SETTING_MENU;
	MENU_Data.changed = 0;
	MENU_Data.is_changing_menu = 1;
	SETTING_MENU_Data.current_pointer = 0;
	SETTING_MENU_Data.is_setting_time_format = 0;
}

void SETTING_MENU_Config_Time_Format(){
	if(MAIN_MENU_Data.time_format == FORMAT_12_HOURS){
		MAIN_MENU_Data.time_format = FORMAT_24_HOURS;
	} else{
		MAIN_MENU_Data.time_format = FORMAT_12_HOURS;
	}
	MENU_Data.menu_type = SETTING_MENU;
	MENU_Data.changed = 0;
}

void SETTING_MENU_Change_Pointer(uint8_t p_is_increase){
	SETTING_MENU_Data.current_pointer += (p_is_increase) ? 1 : -1;
	if(SETTING_MENU_Data.current_pointer < 0){
		SETTING_MENU_Data.current_pointer = 0;
	}
	if(SETTING_MENU_Data.current_pointer > 2){
		SETTING_MENU_Data.current_pointer = 2;
	}
	MENU_Data.menu_type = SETTING_MENU;
	MENU_Data.changed = 0;
}

void SETTING_MENU_Change_Working_State(){
	if(SETTING_MENU_Data.current_pointer == 0){
		SETTING_MENU_Data.is_setting_time_format = !SETTING_MENU_Data.is_setting_time_format;
		MENU_Data.menu_type = SETTING_MENU;
		MENU_Data.changed = 0;
	}
}

void SETTING_MENU_Display(){
	if(MENU_Data.is_changing_menu){
		LCD_Clear(MENU_Data.hlcd);
		MENU_Data.is_changing_menu = 0;
	}
	LCD_Set_Cursor(MENU_Data.hlcd, 4, 0);
	LCD_Write(MENU_Data.hlcd, "Setting Menu");
	LCD_Set_Cursor(MENU_Data.hlcd, 0, 1);
	LCD_Write(MENU_Data.hlcd, " Time format:  %s ", (MAIN_MENU_Data.time_format == FORMAT_12_HOURS) ? "12" : "24");
	LCD_Set_Cursor(MENU_Data.hlcd, 0, 2);
	LCD_Write(MENU_Data.hlcd, " Alarm");
	LCD_Set_Cursor(MENU_Data.hlcd, 0, 3);
	LCD_Write(MENU_Data.hlcd, " Setting real-time");
	if(SETTING_MENU_Data.is_setting_time_format == 1){
		LCD_Set_Cursor(MENU_Data.hlcd, 14, 1);
		LCD_Send_Data(MENU_Data.hlcd, 0x7E);
		LCD_Set_Cursor(MENU_Data.hlcd, 17, 1);
		LCD_Send_Data(MENU_Data.hlcd, 0x7F);
	} else{
		LCD_Set_Cursor(MENU_Data.hlcd, 0, SETTING_MENU_Data.current_pointer + 1);
		LCD_Send_Data(MENU_Data.hlcd, 0x7E);
	}
}
