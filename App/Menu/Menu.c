#include "Menu.h"

MENU_DATA_t MENU_Data;

#define BLINKING_CYCLE		1000

void MENU_Init(LCD_I2C_HandleTypeDef *p_hlcd){
	MENU_Data.hlcd = p_hlcd;
	MENU_Data.changed = 0;
	MENU_Data.is_changing_menu = 1;
	MENU_Data.menu_type = MAIN_MENU;
	MENU_Data.blinking_timer = 0;
	MENU_Data.blink_state = 1;
	MAIN_MENU_Init();
	SR_MENU_Init();
	TL_MENU_Init();
	ST_MENU_Init();
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
				break;
			case SETTING_MENU:
				SETTING_MENU_Display();
				break;
			case SETTING_REALTIME_MENU:
				SR_MENU_Display();
				break;
			case TIMELINE_LIST_MENU:
				TL_MENU_Display();
				break;
			case SETTING_TIMELINE_MENU:
				ST_MENU_Display();
				break;
			default:
				break;
		}
		MENU_Data.changed = 1;
	}

	if(HAL_GetTick() - MENU_Data.blinking_timer > BLINKING_CYCLE){
		if(MENU_Data.menu_type == MAIN_MENU){
			MENU_Data.changed = 0;
			MENU_Data.blink_state = !MENU_Data.blink_state;
		}
		MENU_Data.blinking_timer = HAL_GetTick();
	}

}
