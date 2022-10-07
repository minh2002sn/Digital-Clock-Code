#include "Setting_Timeline_Menu.h"
#include "Timeline_Manage.h"
#include "Menu.h"

ST_MENU_Data_HandleTypeDef ST_MENU_Data;

static uint8_t __max_value[] = {23, 59, 1, 1, 1, 1, 1, 1, 1};
extern char *__setting_type_str[6];

void ST_MENU_Init(){

}

void ST_MENU_Set_State(){
	MENU_Data.menu_type = SETTING_TIMELINE_MENU;
	MENU_Data.changed = 0;
	MENU_Data.is_changing_menu = 1;
	ST_MENU_Data.state = SETTING_ALARM_HOUR;
	FLASH_DATA_t t_timeline = {0, 0, 0, 1};
	ST_MENU_Data.timeline_data = t_timeline;
	ST_MENU_Data.current_day_state = 0;
}

void ST_MENU_Change_Setting_State(uint8_t p_is_increase){
	int8_t *t_value = (int8_t *)(&ST_MENU_Data.state);
	*t_value += ((p_is_increase == INCREASE) ? 1 : -1);
	if(*t_value > CHECKING_ALARM_AGAIN){
		*t_value = CHECKING_ALARM_AGAIN;
		TIMELINE_Add(&ST_MENU_Data.timeline_data);
		TL_MENU_Set_State();
	} else{
		if(*t_value < 0){
			*t_value = 0;
			TL_MENU_Set_State();
			return;
		}
		ST_MENU_Data.current_day_state = 0;
		MENU_Data.menu_type = SETTING_TIMELINE_MENU;
		MENU_Data.changed = 0;
	}
}

void ST_MENU_Set_Value(uint8_t p_is_increase){
	MENU_Data.menu_type = SETTING_TIMELINE_MENU;
	MENU_Data.changed = 0;
	if(ST_MENU_Data.state < CHECKING_ALARM_AGAIN){
		int8_t *t_data_ptr;
		if(ST_MENU_Data.state >= SETTING_ALARM_SUNDAY){
			t_data_ptr = (int8_t *)(&ST_MENU_Data.current_day_state);
		} else{
			t_data_ptr = (int8_t *)(&ST_MENU_Data.timeline_data) + ST_MENU_Data.state;
		}
		*t_data_ptr += ((p_is_increase == INCREASE) ? 1 : -1);
		if(*t_data_ptr > __max_value[ST_MENU_Data.state]){
			*t_data_ptr = 0;
		} else if(*t_data_ptr < 0){
			*t_data_ptr = __max_value[ST_MENU_Data.state];
		}
		if(ST_MENU_Data.state >= SETTING_ALARM_SUNDAY){
			if(*t_data_ptr){
				ST_MENU_Data.timeline_data.day |= (0x01 << (ST_MENU_Data.state - SETTING_ALARM_SUNDAY));
			} else{
				ST_MENU_Data.timeline_data.day &= ~(0x01 << (ST_MENU_Data.state - SETTING_ALARM_SUNDAY));
			}
		}
	}
}

void ST_MENU_Display(){
	if(MENU_Data.is_changing_menu){
		LCD_Clear(MENU_Data.hlcd);
		MENU_Data.is_changing_menu = 0;
	}

	LCD_Set_Cursor(MENU_Data.hlcd, 0, 1);
	LCD_Write(MENU_Data.hlcd, "Time: %02d:%02d", ST_MENU_Data.timeline_data.hour, ST_MENU_Data.timeline_data.minute);

	LCD_Set_Cursor(MENU_Data.hlcd, 0, 2);
	LCD_Write(MENU_Data.hlcd, "Day: C234567");
	LCD_Set_Cursor(MENU_Data.hlcd, 5, 3);
	for(int i = 0; i < 7; i++){
		uint8_t t_day_value = ST_MENU_Data.timeline_data.day & (1 << i);
		if(t_day_value){
			LCD_Send_Data(MENU_Data.hlcd, 0x00);
		} else{
			LCD_Send_Data(MENU_Data.hlcd, 0xFE);
		}
	}

	LCD_Set_Cursor(MENU_Data.hlcd, 0, 0);
	if(ST_MENU_Data.state < SETTING_ALARM_SUNDAY){
		LCD_Write(MENU_Data.hlcd, "  Setting : %s   ", __setting_type_str[ST_MENU_Data.state]);
		LCD_Cursor_No_Blink(MENU_Data.hlcd);
	} else if(ST_MENU_Data.state < CHECKING_ALARM_AGAIN){
		LCD_Write(MENU_Data.hlcd, "  Setting : DAY   ");
		LCD_Cursor_Blink(MENU_Data.hlcd);
		LCD_Set_Cursor(MENU_Data.hlcd, 5 + ST_MENU_Data.state - SETTING_ALARM_SUNDAY, 2);
	} else{
		LCD_Write(MENU_Data.hlcd, "   Checking again   ");
		LCD_Cursor_No_Blink(MENU_Data.hlcd);
	}
}
