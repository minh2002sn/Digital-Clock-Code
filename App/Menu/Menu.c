#include "Menu.h"

#include "Main_Menu.h"

MENU_DATA_t MENU_Data;

void MENU_Init(LCD_I2C_HandleTypeDef *p_hlcd){
	MENU_Data.hlcd = p_hlcd;
	MENU_Data.changed = 0;
	MENU_Data.is_changing_menu = 1;
	MENU_Data.menu_type = MAIN_MENU;
	MAIN_MENU_Init();
}

//void test_big_number(){
//	static uint32_t timer = 0;
//	static uint8_t count;
//
//	if(HAL_GetTick() - timer > 5000){
//		for(int i = 0; i < 5; i++){
//			MAIN_MENU_Display_Num(i + (count % 2)*5, (i*4), 2);
//		}
//		timer = HAL_GetTick();
//		count ++;
//	}
//}

void MENU_Handle(){
	if(!MENU_Data.changed){
		switch(MENU_Data.menu_type){
			case MAIN_MENU:
				MAIN_MENU_Display();
				MENU_Data.changed = 1;
				break;
			case SETTING_REALTIME_MENU:
				SR_MENU_Display();
				MENU_Data.changed = 1;
				break;
			case TIMELINE_LIST_MENU:

				break;
			case SETTING_TIMELINE_MENU:

				break;
			default:
				break;
		}
	}
}
