#ifndef SETTING_REALTIME_MENU_H
#define SETTING_REALTIME_MENU_H

#include "stdint.h"
#include "real_time.h"

enum{
	DECREASE,
	INCREASE,
};

typedef enum{
	SETTING_HOUR,
	SETTING_MINUTE,
	SETTING_DAY,
	SETTING_DATE,
	SETTING_MONTH,
	SETTING_YEAR,
	CHECKING_AGAIN,
} SETTING_REATIME_STATE_t;

typedef struct{
	SETTING_REATIME_STATE_t state;
	REALTIME_DATA_HandleTypeDef new_realtime;
} SR_MENU_DATA_t;

void SR_MENU_Init();
void SR_MENU_Display();
void SR_MENU_Set_State();
void SR_MENU_Change_Setting_State(uint8_t p_is_increase);
void SR_MENU_Set_Value(uint8_t p_is_increase);

extern SR_MENU_DATA_t SR_MENU_Data;

#endif
