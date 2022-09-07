#include "Encoder.h"

encoder_callback_function_t __ENCODER_Forward_Callback = NULL;
encoder_callback_function_t __ENCODER_Backward_Callback = NULL;

#ifdef _USING_LIBRARY_ENCODER_IT_FUNCTION_
extern ENCODER_HandleTypeDef h_encoder;
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
	if(h_encoder.encoder_timer->Instance == htim->Instance){
		ENCODER_IT_Handle(&h_encoder);
	}
}
#endif

void ENCODER_Init(ENCODER_HandleTypeDef *p_encoder, TIM_HandleTypeDef *p_encoder_timer){
	p_encoder->encoder_timer = p_encoder_timer;
	p_encoder->current_possition = 0;
	p_encoder->last_position = 0;
}

void ENCODER_Set_Callback_Function(encoder_callback_function_t p_forward_callback_function, encoder_callback_function_t p_backward_callback_function){
	__ENCODER_Forward_Callback = p_forward_callback_function;
	__ENCODER_Backward_Callback = p_backward_callback_function;
}

void ENCODER_IT_Handle(ENCODER_HandleTypeDef *p_encoder){
	uint32_t t_counter = __HAL_TIM_GET_COUNTER(p_encoder->encoder_timer);
	p_encoder->current_possition =  (int16_t)t_counter / 4;
}

void ENCODER_Handle(ENCODER_HandleTypeDef *p_encoder){
	if(p_encoder->current_possition > p_encoder->last_position){
		if(__ENCODER_Forward_Callback != NULL){
			__ENCODER_Forward_Callback(p_encoder);
		}
		p_encoder->last_position = p_encoder->current_possition;
	}
	if(p_encoder->current_possition < p_encoder->last_position){
		if(__ENCODER_Backward_Callback != NULL){
			__ENCODER_Backward_Callback(p_encoder);
		}
		p_encoder->last_position = p_encoder->current_possition;
	}
}
