#ifndef MENU_H
#define MENU_H

#include "main.h"
#include "LCD_I2C.h"
#include "stdint.h"
#include "Main_Menu.h"
#include "Setting_Realtime_Menu.h"
#include "Timeline_List_Menu.h"
#include "Setting_Timeline_Menu.h"

typedef enum{
	MAIN_MENU,
	SETTING_REALTIME_MENU,
	TIMELINE_LIST_MENU,
	SETTING_TIMELINE_MENU,
} MENU_t;

typedef struct{
	MENU_t menu_type;
	LCD_I2C_HandleTypeDef *hlcd;
	uint8_t changed;
	uint8_t is_changing_menu;
	uint32_t blinking_timer;
	uint8_t blink_state;
} MENU_DATA_t;

void MENU_Init(LCD_I2C_HandleTypeDef *p_hlcd);
void MENU_Handle();

extern MENU_DATA_t MENU_Data;

#endif
