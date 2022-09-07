#ifndef TIME_LIST_MENU_H
#define TIME_LIST_MENU_H

#include "stdint.h"
#include "Timeline_Manage.h"

#define NUMBER_OF_CHOICE (MAX_OPTIONS + 1)

typedef struct{
	uint8_t first_line;
	char list_str[NUMBER_OF_CHOICE][21];
	uint8_t numer_of_choices;
	int8_t current_pointer;
}TIME_LIST_MENU_DATA_HandleTypeDef;

void TL_MENU_Init();
void TL_MENU_Set_State();
void TL_MENU_Change_Pointer(uint8_t p_is_increase);
void TL_MENU_Change_Timeline_State();
void TL_MENU_Display();

extern TIME_LIST_MENU_DATA_HandleTypeDef TL_MENU_Data;

#endif
