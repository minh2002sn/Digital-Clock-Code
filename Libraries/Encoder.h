#ifndef ENCODER_H
#define ENCODER_H

#define _USING_LIBRARY_ENCODER_IT_FUNCTION_

#include "main.h"

typedef struct{
	TIM_HandleTypeDef *encoder_timer;
	int16_t current_possition;
	int16_t last_position;
} ENCODER_HandleTypeDef;

typedef void (*encoder_callback_function_t)(ENCODER_HandleTypeDef *);

void ENCODER_Init(ENCODER_HandleTypeDef *p_encoder, TIM_HandleTypeDef *p_encoder_timer);
void ENCODER_Set_Callback_Function(encoder_callback_function_t p_forward_callback_function, encoder_callback_function_t p_backward_callback_function);
void ENCODER_IT_Handle(ENCODER_HandleTypeDef *p_encoder);
void ENCODER_Handle(ENCODER_HandleTypeDef *p_encoder);

#endif
