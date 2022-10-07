#include "real_time.h"
#include "menu.h"
#include "main.h"

#define CHECKING_REAL_TIME_CYCLE	5000	// in ms

extern I2C_HandleTypeDef hi2c2;

DS3231_HandleTypeDef hds3231;
REALTIME_DATA_HandleTypeDef REALTIME_Data;

#ifdef USING_EXTERNAL_RTC
RTC_TimeTypeDef Time;
RTC_DateTypeDef Date;
extern RTC_HandleTypeDef hrtc;
#endif

static uint32_t timer = 0;

void REALTIME_Init(){
	DS3231_Init(&hds3231, &hi2c2);
	REALTIME_Data.system_day = 1;
	REALTIME_Data.system_hour = 0;
	REALTIME_Data.system_minute = 0;
	REALTIME_Data.system_date = 1;
	REALTIME_Data.system_month = 1;
	REALTIME_Data.system_year = 0;

//	DS3231_Set_Time(&hds3231, 19, 54, 0, 6);
//	DS3231_Set_Date(&hds3231, 2, 9, 22);

#ifdef USING_EXTERNAL_RTC
	HAL_RTC_GetTime(&hrtc, &Time, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &Date, RTC_FORMAT_BIN);
	REALTIME_Data.system_day = Date.WeekDay;
	REALTIME_Data.system_hour = Time.Hours;
	REALTIME_Data.system_minute = Time.Minutes;
	REALTIME_Data.system_date = Date.Date;
	REALTIME_Data.system_month = Date.Month;
	REALTIME_Data.system_year = Date.Year;
#else
	if(DS3231_Get_Time(&hds3231) == DS3231_FAIL || DS3231_Get_Date(&hds3231) == DS3231_FAIL){
		return;
	}

	REALTIME_Data.system_day = hds3231.current_day;
	REALTIME_Data.system_hour = hds3231.current_hour;
	REALTIME_Data.system_minute = hds3231.current_minute;
	REALTIME_Data.system_date = hds3231.current_date;
	REALTIME_Data.system_month = hds3231.current_month;
	REALTIME_Data.system_year = hds3231.current_year;
#endif
}

void REALTIME_Handle(){
	if(HAL_GetTick() - timer > CHECKING_REAL_TIME_CYCLE){
#ifdef USING_EXTERNAL_RTC
		HAL_RTC_GetTime(&hrtc, &Time, RTC_FORMAT_BIN);
		HAL_RTC_GetDate(&hrtc, &Date, RTC_FORMAT_BIN);
		REALTIME_Data.system_day = Date.WeekDay;
		REALTIME_Data.system_hour = Time.Hours;
		REALTIME_Data.system_minute = Time.Minutes;
		REALTIME_Data.system_date = Date.Date;
		REALTIME_Data.system_month = Date.Month;
		REALTIME_Data.system_year = Date.Year;
#else
		if(DS3231_Get_Time(&hds3231) == DS3231_FAIL || DS3231_Get_Date(&hds3231) == DS3231_FAIL){
			return;
		}

		if(REALTIME_Data.system_minute != hds3231.current_minute){
			if(MENU_Data.menu_type == MAIN_MENU){
				MAIN_MENU_Update_Value();
			}
		}

		REALTIME_Data.system_day = hds3231.current_day;
		REALTIME_Data.system_hour = hds3231.current_hour;
		REALTIME_Data.system_minute = hds3231.current_minute;
		REALTIME_Data.system_date = hds3231.current_date;
		REALTIME_Data.system_month = hds3231.current_month;
		REALTIME_Data.system_year = hds3231.current_year;
#endif
	}
}

void REALTIME_Set_New_Realtime(REALTIME_DATA_HandleTypeDef *p_new_realtime){
#ifdef USING_EXTERNAL_RTC
	REALTIME_Data.system_day = p_new_realtime->system_day;
	REALTIME_Data.system_hour = p_new_realtime->system_hour;
	REALTIME_Data.system_minute = p_new_realtime->system_minute;
	REALTIME_Data.system_date = p_new_realtime->system_date;
	REALTIME_Data.system_month = p_new_realtime->system_month;
	REALTIME_Data.system_year = p_new_realtime->system_year;

	Time.Hours = REALTIME_Data.system_hour;
	Time.Minutes = REALTIME_Data.system_minute;
	Time.Seconds = 0;
	Date.WeekDay = REALTIME_Data.system_day;
	Date.Date = REALTIME_Data.system_date;
	Date.Month = REALTIME_Data.system_month;
	Date.Year = REALTIME_Data.system_year;

	if(HAL_RTC_SetTime(&hrtc, &Time, RTC_FORMAT_BIN) != HAL_OK) Error_Handler();
	if(HAL_RTC_SetDate(&hrtc, &Date, RTC_FORMAT_BIN) != HAL_OK) Error_Handler();
#else
	DS3231_Set_Time(&hds3231, p_new_realtime->system_hour, p_new_realtime->system_minute, 0, p_new_realtime->system_day);
	DS3231_Set_Date(&hds3231, p_new_realtime->system_date, p_new_realtime->system_month, p_new_realtime->system_year);

	REALTIME_Data.system_day = p_new_realtime->system_day;
	REALTIME_Data.system_hour = p_new_realtime->system_hour;
	REALTIME_Data.system_minute = p_new_realtime->system_minute;
	REALTIME_Data.system_date = p_new_realtime->system_date;
	REALTIME_Data.system_month = p_new_realtime->system_month;
	REALTIME_Data.system_year = p_new_realtime->system_year;
#endif
}
