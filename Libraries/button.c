#include "button.h"

//========== btn func ==========//

button_callback_function_t __BUTTON_Pressing_Callback = NULL;
button_callback_function_t __BUTTON_Releasing_Callback = NULL;
button_callback_function_t __BUTTON_Short_Pressing_Callback = NULL;
button_callback_function_t __BUTTON_Long_Pressing_Callback = NULL;

//__weak void BTN_Pressing_Callback(BUTTON_HandleTypedef *ButtonX){
//	;
//}
//
//__weak void BTN_Releasing_Callback(BUTTON_HandleTypedef *ButtonX){
//	;
//}
//
//__weak void BTN_Short_Press_Callback(BUTTON_HandleTypedef *ButtonX){
//	;
//}
//
//__weak void BTN_Long_Press_Callback(BUTTON_HandleTypedef *ButtonX){
//	;
//}

void BUTTON_Handle(BUTTON_HandleTypedef *ButtonX){
	uint8_t state = HAL_GPIO_ReadPin(ButtonX->GPIOx, ButtonX->GPIO_Pin);
	if(state != ButtonX->BTN_Filter){
		ButtonX->BTN_Filter = state;
		ButtonX->is_debouncing = 1;
		ButtonX->time_debounce = HAL_GetTick();
	}

	if(ButtonX->is_debouncing && (HAL_GetTick() - ButtonX->time_debounce >= 15)){
		ButtonX->BTN_Current = ButtonX->BTN_Filter;
		ButtonX->is_debouncing = 0;
	}

	if(ButtonX->BTN_Current != ButtonX->BTN_Last){
		if(ButtonX->BTN_Current == 0){
			if(__BUTTON_Pressing_Callback != NULL){
				__BUTTON_Pressing_Callback(ButtonX);
			}
			ButtonX->is_press = 1;
			ButtonX->time_start_press = HAL_GetTick();
		}
		else{
			ButtonX->is_press = 0;
			if(HAL_GetTick() - ButtonX->time_start_press <= 1000){
				if(__BUTTON_Short_Pressing_Callback != NULL){
					__BUTTON_Short_Pressing_Callback(ButtonX);
				}
			}
			if(__BUTTON_Releasing_Callback != NULL){
				__BUTTON_Releasing_Callback(ButtonX);
			}
		}
		ButtonX->BTN_Last = ButtonX->BTN_Current;
	}

	if(ButtonX->is_press && (HAL_GetTick() - ButtonX->time_start_press >= 3000)){
		if(__BUTTON_Long_Pressing_Callback != NULL){
			__BUTTON_Long_Pressing_Callback(ButtonX);
		}
		ButtonX->is_press = 0;
	}
}

void BUTTON_Init(BUTTON_HandleTypedef *ButtonX, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
	ButtonX->GPIOx = GPIOx;
	ButtonX->GPIO_Pin = GPIO_Pin;
	ButtonX->BTN_Current = 1;
	ButtonX->BTN_Last = 1;
	ButtonX->BTN_Filter = 1;
	ButtonX->is_debouncing = 0;
	ButtonX->is_press = 0;
}

void BUTTON_Set_Callback_Function(button_callback_function_t p_pressing_callback_function,
								button_callback_function_t p_releasing_callback_function,
								button_callback_function_t p_short_pressing_callback_function,
								button_callback_function_t p_long_pressing_callback_function){
	__BUTTON_Pressing_Callback = p_pressing_callback_function;
	__BUTTON_Releasing_Callback = p_releasing_callback_function;
	__BUTTON_Short_Pressing_Callback = p_short_pressing_callback_function;
	__BUTTON_Long_Pressing_Callback = p_long_pressing_callback_function;
}

