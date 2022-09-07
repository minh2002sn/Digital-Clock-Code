#include "Timeline_List_Menu.h"
#include "Menu.h"

TIME_LIST_MENU_DATA_HandleTypeDef TL_MENU_Data;

static void __create_day_string(char str[], uint8_t day){
	for(int i = 0; i < 7; i++){
		uint8_t t_day_value = day & (1 << i);
		if(t_day_value){
			if(t_day_value == 1){
				str[i] = 'C';
			} else{
				str[i] = '1' + i;
			}
		}
	}
}

static void __update_time_list(){
	strcpy(TL_MENU_Data.list_str[0], " Add...");
	for(int i = 1; i <= TL_MENU_Data.numer_of_choices; i++){
		char day_str[8] = {};
		__create_day_string(day_str, TIMELINE_Data.flash_data[i].day);
		sprintf(TL_MENU_Data.list_str[i], " %02d:%02d %7s %s ", TIMELINE_Data.flash_data[i].hour, TIMELINE_Data.flash_data[i].minute,
				"", (TIMELINE_Data.flash_data[i].timeline_state == TIMELINE_ON) ? "ON" : "OFF");
	}
}

void TL_MENU_Init(){
	TL_MENU_Data.first_line = 0;
	TIMELINE_Init();
	for(int i = 0; i < NUMBER_OF_CHOICE; i++){
		for(int j = 0; j < 21; j++){
			TL_MENU_Data.list_str[i][j] = 0;
		}
	}
}

void TL_MENU_Set_State(){
	MENU_Data.menu_type = TIMELINE_LIST_MENU;
	MENU_Data.changed = 0;
	MENU_Data.is_changing_menu = 1;
	TL_MENU_Data.first_line = 0;
	TL_MENU_Data.current_pointer = 0;
	TL_MENU_Data.numer_of_choices = TIMELINE_Data.len + 1;
	__update_time_list();
}

void TL_MENU_Change_Pointer(uint8_t p_is_increase){
	MENU_Data.menu_type = TIMELINE_LIST_MENU;
	MENU_Data.changed = 0;
	TL_MENU_Data.current_pointer += (p_is_increase == INCREASE) ? 1 : -1;
	if(TL_MENU_Data.current_pointer < 0){
		TL_MENU_Data.current_pointer = 0;
	} else if(TL_MENU_Data.current_pointer > TL_MENU_Data.numer_of_choices){
		TL_MENU_Data.current_pointer = TL_MENU_Data.numer_of_choices;
	}

	if(TL_MENU_Data.current_pointer > TL_MENU_Data.first_line + 3){
		TL_MENU_Data.first_line++;
	} else if(TL_MENU_Data.current_pointer < TL_MENU_Data.first_line - 3){
		TL_MENU_Data.first_line--;
	}
}

void TL_MENU_Change_Timeline_State(){
	MENU_Data.menu_type = TIMELINE_LIST_MENU;
	MENU_Data.changed = 0;
	if(TL_MENU_Data.current_pointer == 0) return;
	if(TIMELINE_Data.flash_data[TL_MENU_Data.current_pointer - 1].timeline_state == TIMELINE_ON)
		TIMELINE_Data.flash_data[TL_MENU_Data.current_pointer - 1].timeline_state = TIMELINE_OFF;
	else
		TIMELINE_Data.flash_data[TL_MENU_Data.current_pointer - 1].timeline_state = TIMELINE_ON;
}

void TL_MENU_Display(){
	if(MENU_Data.is_changing_menu == 1){
		LCD_Clear(MENU_Data.hlcd);
		MENU_Data.is_changing_menu = 0;
	}
	for(int i = 0; i < 4; i++){
		LCD_Set_Cursor(MENU_Data.hlcd, 0, i);
		LCD_Write(MENU_Data.hlcd, TL_MENU_Data.list_str[TL_MENU_Data.first_line + i]);
		if(TL_MENU_Data.current_pointer == TL_MENU_Data.first_line + i){
			LCD_Set_Cursor(MENU_Data.hlcd, 0, i);
			LCD_Send_Data(MENU_Data.hlcd, 0x7E);
		}
	}
}
