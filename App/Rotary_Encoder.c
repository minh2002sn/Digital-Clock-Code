#include "Rotary_Encoder.h"
#include "button.h"
#include "Encoder.h"
#include "Menu.h"
#include "Alarm.h"

BUTTON_HandleTypedef h_encoder_button;
ENCODER_HandleTypeDef h_encoder;
extern TIM_HandleTypeDef htim2;

void BTN_Short_Pressing_Callback(BUTTON_HandleTypedef *p_ButtonX){
	if(p_ButtonX == &h_encoder_button){
		if(ALARM_Is_Buzzer_Running()){
			ALARM_Stop_Buzzer();
			return;
		}
	}

	if(p_ButtonX == &h_encoder_button){
		switch(MENU_Data.menu_type){
			case MAIN_MENU:
				SETTING_MENU_Set_State();
				break;
			case SETTING_MENU:
				if(SETTING_MENU_Data.current_pointer == 0){
					SETTING_MENU_Change_Working_State();
				} else if(SETTING_MENU_Data.current_pointer == 1){
					TL_MENU_Set_State();
				} else if(SETTING_MENU_Data.current_pointer == 2){
					SR_MENU_Set_State();
				}
				break;
			case SETTING_REALTIME_MENU:
				SR_MENU_Change_Setting_State(INCREASE);
				break;
			case TIMELINE_LIST_MENU:
				if(TL_MENU_Data.current_pointer == 0){
					ST_MENU_Set_State();
				} else{
					TL_MENU_Change_Working_State();
				}
				break;
			case SETTING_TIMELINE_MENU:
				ST_MENU_Change_Setting_State(INCREASE);
				break;
			default:
				break;
		}
	}
}

void BTN_Long_Pressing_Callback(BUTTON_HandleTypedef *p_ButtonX){
	if(p_ButtonX == &h_encoder_button){
		if(ALARM_Is_Buzzer_Running()){
			ALARM_Stop_Buzzer();
			return;
		}
	}

	if(p_ButtonX == &h_encoder_button){
		switch(MENU_Data.menu_type){
			case MAIN_MENU:

				break;
			case SETTING_MENU:
				if(SETTING_MENU_Data.is_setting_time_format == 1){
					SETTING_MENU_Change_Working_State();
				} else{
					MAIN_MENU_Set_State();
				}
				break;
			case SETTING_REALTIME_MENU:
				SR_MENU_Change_Setting_State(DECREASE);
				break;
			case TIMELINE_LIST_MENU:
				if(TL_MENU_Data.woking_state == NORMAL_STATE){
					SETTING_MENU_Set_State();
				} else{
					TL_MENU_Change_Working_State();
				}
				break;
			case SETTING_TIMELINE_MENU:
				ST_MENU_Change_Setting_State(DECREASE);
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
			case SETTING_MENU:
				if(SETTING_MENU_Data.is_setting_time_format == 1){
					SETTING_MENU_Config_Time_Format();
				} else{
					SETTING_MENU_Change_Pointer(INCREASE);
				}
				break;
			case SETTING_REALTIME_MENU:
				SR_MENU_Set_Value(INCREASE);
				break;
			case TIMELINE_LIST_MENU:
				if(TL_MENU_Data.woking_state == NORMAL_STATE)
					TL_MENU_Change_Pointer(INCREASE);
				else
					TL_MENU_Config_Timeline(INCREASE);
				break;
			case SETTING_TIMELINE_MENU:
				ST_MENU_Set_Value(INCREASE);
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
			case SETTING_MENU:
				if(SETTING_MENU_Data.is_setting_time_format == 1){
					SETTING_MENU_Config_Time_Format();
				} else{
					SETTING_MENU_Change_Pointer(DECREASE);
				}
				break;
			case SETTING_REALTIME_MENU:
				SR_MENU_Set_Value(DECREASE);
				break;
			case TIMELINE_LIST_MENU:
				if(TL_MENU_Data.woking_state == NORMAL_STATE)
					TL_MENU_Change_Pointer(DECREASE);
				else
					TL_MENU_Config_Timeline(DECREASE);
				break;
			case SETTING_TIMELINE_MENU:
				ST_MENU_Set_Value(DECREASE);
				break;
			default:
				break;
		}
	}
}

void ROTARY_ENCODER_Init(){
	BUTTON_Init(&h_encoder_button, GPIOB, GPIO_PIN_4);
	BUTTON_Set_Callback_Function(NULL, NULL, BTN_Short_Pressing_Callback, BTN_Long_Pressing_Callback);
	ENCODER_Init(&h_encoder, &htim2);
	ENCODER_Set_Callback_Function(ENCODER_Forward_Callback, ENCODER_Backward_Callback);
}

void ROTARY_ENCODER_Handle(){
	BUTTON_Handle(&h_encoder_button);
	ENCODER_Handle(&h_encoder);
}

