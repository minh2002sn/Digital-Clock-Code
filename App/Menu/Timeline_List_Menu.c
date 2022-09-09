#include "Timeline_List_Menu.h"
#include "Menu.h"
#include "Timeline_Manage.h"
#include "Alarm.h"

TIME_LIST_MENU_DATA_HandleTypeDef TL_MENU_Data;

static void __create_day_string(char str[], uint8_t day){
	uint8_t t_num_of_day = 0;
	for(int i = 0; i < 7; i++){
		uint8_t t_day_value = day & (1 << i);
		if(t_day_value){
			if(t_day_value == 1){
				str[t_num_of_day++] = 'C';
			} else{
				str[t_num_of_day++] = '1' + i;
			}
		}
	}
}

void TL_MENU_Init(){
	TL_MENU_Data.first_line = 0;
	TL_MENU_Data.numer_of_choices = 0;
	TL_MENU_Data.current_pointer = 0;
	TL_MENU_Data.woking_state = NORMAL_STATE;
	TIMELINE_Init();
//	for(int i = 0; i < NUMBER_OF_CHOICE; i++){
//		for(int j = 0; j < 21; j++){
//			TL_MENU_Data.list_str[i][j] = 0;
//		}
//	}
}

void TL_MENU_Set_State(){
	MENU_Data.menu_type = TIMELINE_LIST_MENU;
	MENU_Data.changed = 0;
	MENU_Data.is_changing_menu = 1;
	TL_MENU_Data.first_line = 0;
	TL_MENU_Data.current_pointer = 0;
	TL_MENU_Data.numer_of_choices = TIMELINE_Data.len + 1;
	TL_MENU_Data.woking_state = NORMAL_STATE;
}

void TL_MENU_Change_Working_State(){
	if(TL_MENU_Data.current_pointer == 0) return;
	if(TL_MENU_Data.woking_state == NORMAL_STATE){
		TL_MENU_Data.woking_state = CONFIG_TIMELINE_STATE;
		TL_MENU_Data.timeline_state = TIMELINE_Data.flash_data[TL_MENU_Data.current_pointer - 1].timeline_state;
	} else{
		TL_MENU_Data.woking_state = NORMAL_STATE;
		if(TL_MENU_Data.timeline_state == DELETE_TIMELINE && !ALARM_Is_Buzzer_Running()){
			TIMELINE_Delete(TL_MENU_Data.current_pointer - 1);
			TL_MENU_Data.numer_of_choices--;
			if(TL_MENU_Data.current_pointer > TL_MENU_Data.numer_of_choices - 1){
				TL_MENU_Data.current_pointer = TL_MENU_Data.numer_of_choices - 1;
			}
		} else{
			TIMELINE_Data.flash_data[TL_MENU_Data.current_pointer - 1].timeline_state = TL_MENU_Data.timeline_state;
			TIMELINE_Store_To_Flash();
		}
	}
	MENU_Data.menu_type = TIMELINE_LIST_MENU;
	MENU_Data.changed = 0;
}

void TL_MENU_Change_Pointer(uint8_t p_is_increase){
	MENU_Data.menu_type = TIMELINE_LIST_MENU;
	MENU_Data.changed = 0;
	TL_MENU_Data.current_pointer += (p_is_increase == INCREASE) ? 1 : -1;
	if(TL_MENU_Data.current_pointer < 0){
		TL_MENU_Data.current_pointer = 0;
	} else if(TL_MENU_Data.current_pointer >= TL_MENU_Data.numer_of_choices){
		TL_MENU_Data.current_pointer = TL_MENU_Data.numer_of_choices - 1;
	}

	if(TL_MENU_Data.current_pointer > TL_MENU_Data.first_line + 3){
		TL_MENU_Data.first_line++;
	} else if(TL_MENU_Data.current_pointer < TL_MENU_Data.first_line){
		TL_MENU_Data.first_line--;
	}
}

void TL_MENU_Config_Timeline(uint8_t p_is_increase){
	MENU_Data.menu_type = TIMELINE_LIST_MENU;
	MENU_Data.changed = 0;

	TL_MENU_Data.timeline_state += (p_is_increase == INCREASE) ? 1 : -1;
	if((int8_t)TL_MENU_Data.timeline_state < 0){
		TL_MENU_Data.timeline_state = 2;
	} else if(TL_MENU_Data.timeline_state > 2){
		TL_MENU_Data.timeline_state = 0;
	}
}

void TL_MENU_Display(){
	if(MENU_Data.is_changing_menu == 1){
		LCD_Clear(MENU_Data.hlcd);
		MENU_Data.is_changing_menu = 0;
	}
	for(int i = 0; i < 4; i++){
		uint8_t t_index = TL_MENU_Data.first_line + i;
		LCD_Set_Cursor(MENU_Data.hlcd, 0, i);
		if(t_index == 0){
			LCD_Write(MENU_Data.hlcd, " Add...             ");
		} else if(t_index - 1 < TIMELINE_Data.len){
			char day_str[8] = {};
			__create_day_string(day_str, TIMELINE_Data.flash_data[t_index - 1].day);
			LCD_Write(MENU_Data.hlcd, " %02d:%02d %7s  %s ", TIMELINE_Data.flash_data[t_index - 1].hour, TIMELINE_Data.flash_data[t_index - 1].minute,
					day_str, (TIMELINE_Data.flash_data[t_index - 1].timeline_state == TIMELINE_ON) ? " ON" : "OFF");
		} else{
			LCD_Write(MENU_Data.hlcd, "                    ");
		}
		if(TL_MENU_Data.current_pointer == t_index){
			if(TL_MENU_Data.woking_state == NORMAL_STATE){
				LCD_Set_Cursor(MENU_Data.hlcd, 0, i);
				LCD_Send_Data(MENU_Data.hlcd, 0x7E);
			} else{
				LCD_Set_Cursor(MENU_Data.hlcd, 15, i);
				LCD_Send_Data(MENU_Data.hlcd, 0x7E);
				if(TL_MENU_Data.timeline_state == TURN_OFF_TIMELINE){
					LCD_Write(MENU_Data.hlcd, "OFF");
				} else if(TL_MENU_Data.timeline_state == TURN_ON_TIMELINE){
					LCD_Write(MENU_Data.hlcd, " ON");
				} else if(TL_MENU_Data.timeline_state == DELETE_TIMELINE){
					LCD_Write(MENU_Data.hlcd, "DEL");
				}
				LCD_Send_Data(MENU_Data.hlcd, 0x7F);
			}
		}
	}
}
