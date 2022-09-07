#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "stdint.h"

void MAIN_MENU_Init();
void MAIN_MENU_Display_Num(uint8_t p_number, uint8_t p_col, uint8_t p_row);
void MAIN_MENU_Display();
void MAIN_MENU_Set_State();
void MAIN_MENU_Update_Value();

#endif
