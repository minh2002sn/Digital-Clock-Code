#include "Rotary_Encoder.h"
#include "button.h"
#include "Encoder.h"
#include "Menu.h"

BUTTON_HandleTypedef h_encoder_button;
ENCODER_HandleTypeDef h_encoder;
extern TIM_HandleTypeDef htim2;

void BTN_Short_Pressing_Callback(BUTTON_HandleTypedef *p_ButtonX){
	if(p_ButtonX == &h_encoder_button){
		switch(MENU_Data.menu_type){
			case MAIN_MENU:

				break;
			case SETTING_REALTIME_MENU:
				SR_MENU_Change_Setting_State(INCREASE);
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

void BTN_Long_Pressing_Callback(BUTTON_HandleTypedef *p_ButtonX){
	if(p_ButtonX == &h_encoder_button){
		switch(MENU_Data.menu_type){
			case MAIN_MENU:
				SR_MENU_Set_State();
				break;
			case SETTING_REALTIME_MENU:
				SR_MENU_Change_Setting_State(DECREASE);
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

void ENCODER_Forward_Callback(ENCODER_HandleTypeDef *p_encoder){
	if(p_encoder == &h_encoder){
		switch(MENU_Data.menu_type){
			case MAIN_MENU:

				break;
			case SETTING_REALTIME_MENU:
				SR_MENU_Set_Value(INCREASE);
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

void ENCODER_Backward_Callback(ENCODER_HandleTypeDef *p_encoder){
	if(p_encoder == &h_encoder){
		switch(MENU_Data.menu_type){
			case MAIN_MENU:

				break;
			case SETTING_REALTIME_MENU:
				SR_MENU_Set_Value(DECREASE);
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

void ROTARY_ENCODER_Init(){
	BUTTON_Init(&h_encoder_button, GPIOA, GPIO_PIN_1);
	BUTTON_Set_Callback_Function(NULL, NULL, BTN_Short_Pressing_Callback, BTN_Long_Pressing_Callback);
	ENCODER_Init(&h_encoder, &htim2);
	ENCODER_Set_Callback_Function(ENCODER_Forward_Callback, ENCODER_Backward_Callback);
}

void ROTARY_ENCODER_Handle(){
	BUTTON_Handle(&h_encoder_button);
	ENCODER_Handle(&h_encoder);
}

