#ifndef SETTING_MENU_H
#define SETTING_MENU_H

typedef struct{
	int8_t current_pointer;
	uint8_t is_setting_time_format;
} SETTING_MENU_t;

void SETTING_MENU_Init();
void SETTING_MENU_Set_State();
void SETTING_MENU_Display();
void SETTING_MENU_Change_Working_State();
void SETTING_MENU_Config_Time_Format();
void SETTING_MENU_Change_Pointer(uint8_t p_is_increase);

extern SETTING_MENU_t SETTING_MENU_Data;

#endif
