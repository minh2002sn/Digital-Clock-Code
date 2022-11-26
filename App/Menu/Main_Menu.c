#include "Menu.h"
#include "real_time.h"
#include "DHT.h"
#include "Battery_Value.h"

extern DHT_HandleTypeDef hdht;

MAIN_MENU_t MAIN_MENU_Data;

char DAY_Str[7][4] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};

static uint8_t number_char[11][6] = {
		{0xFF, 0x00, 0xFF, 0xFF, 0x01, 0xFF},	// 0
		{0xFE, 0xFF, 0xFE, 0xFE, 0xFF, 0xFE},	// 1
		{0x00, 0x02, 0xFF, 0xFF, 0x01, 0x01},	// 2
		{0x02, 0x02, 0xFF, 0x01, 0x01, 0xFF},	// 3
		{0xFF, 0x01, 0xFF, 0xFE, 0xFE, 0xFF},	// 4
		{0xFF, 0x02, 0x02, 0x01, 0x01, 0xFF},	// 5
		{0xFF, 0x01, 0x01, 0xFF, 0x01, 0xFF},	// 6
		{0xFE, 0x00, 0xFF, 0xFE, 0xFE, 0xFF},	// 7
		{0xFF, 0x02, 0xFF, 0xFF, 0x01, 0xFF},	// 8
		{0xFF, 0x02, 0xFF, 0x01, 0x01, 0xFF},	// 9
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// Nothing
};

void MAIN_MENU_Init(){
	uint8_t num_char_0[] = {
			0b11111,
			0b11111,
			0b00000,
			0b00000,
			0b00000,
			0b00000,
			0b00000,
			0b00000,
	};
	LCD_Create_Char(MENU_Data.hlcd, 0, num_char_0);

	uint8_t num_char_1[] = {
			0b00000,
			0b00000,
			0b00000,
			0b00000,
			0b00000,
			0b00000,
			0b11111,
			0b11111,
	};
	LCD_Create_Char(MENU_Data.hlcd, 1, num_char_1);

	uint8_t num_char_2[] = {
			0b11111,
			0b11111,
			0b00000,
			0b00000,
			0b00000,
			0b00000,
			0b11111,
			0b11111,
	};
	LCD_Create_Char(MENU_Data.hlcd, 2, num_char_2);

	uint8_t thermometro[8] = {
			0b00100,
			0b01010,
			0b01010,
			0b01010,
			0b01110,
			0b11111,
			0b11111,
			0b01110
	};
	LCD_Create_Char(MENU_Data.hlcd, 3, thermometro);

	uint8_t igrasia[8] = {
			0b00100,
			0b00100,
			0b01010,
			0b01010,
			0b10001,
			0b10001,
			0b10001,
			0b01110,
	};
	LCD_Create_Char(MENU_Data.hlcd, 4, igrasia);

	uint8_t full_battery[8] = {
			0b01110,
			0b11111,
			0b11111,
			0b11111,
			0b11111,
			0b11111,
			0b11111,
			0b11111,
	};
	LCD_Create_Char(MENU_Data.hlcd, 5, full_battery);

	uint8_t half_battery[8] = {
			0b01110,
			0b10001,
			0b10001,
			0b10001,
			0b11111,
			0b11111,
			0b11111,
			0b11111,
	};
	LCD_Create_Char(MENU_Data.hlcd, 6, half_battery);

	uint8_t low_battery[8] = {
			0b01110,
			0b10001,
			0b10001,
			0b10001,
			0b10001,
			0b10001,
			0b10001,
			0b11111,
	};
	LCD_Create_Char(MENU_Data.hlcd, 7, low_battery);

	MAIN_MENU_Data.time_format = FORMAT_24_HOURS;
}

void MAIN_MENU_Display_Num(uint8_t p_number, uint8_t p_col, uint8_t p_row){
	if(p_row > 2) return;

	LCD_Set_Cursor(MENU_Data.hlcd, p_col, p_row);
	for(int i = 0; i < 3; i++){
		LCD_Send_Data(MENU_Data.hlcd, (char)number_char[p_number][i]);
	}

	LCD_Set_Cursor(MENU_Data.hlcd, p_col, p_row + 1);
	for(int i = 0; i < 3; i++){
		LCD_Send_Data(MENU_Data.hlcd, (char)number_char[p_number][i+3]);
	}

}

void MAIN_MENU_Display(){
	if(MENU_Data.is_changing_menu){
		LCD_Clear(MENU_Data.hlcd);
		MENU_Data.is_changing_menu = 0;
	}
	LCD_Set_Cursor(MENU_Data.hlcd, 3, 0);
	char t_day_string[] = "SUN";
	if(REALTIME_Data.system_day > 0){
		strcpy(t_day_string, DAY_Str[REALTIME_Data.system_day - 1]);
	}
	LCD_Write(MENU_Data.hlcd, "%s %02d-%02d-20%02d", t_day_string,
				REALTIME_Data.system_date, REALTIME_Data.system_month, REALTIME_Data.system_year);
	LCD_Set_Cursor(MENU_Data.hlcd, 2, 1);
	LCD_Send_Data(MENU_Data.hlcd, 3);
	LCD_Write(MENU_Data.hlcd, "%02dC  ", (uint8_t)hdht.temperature);
	LCD_Send_Data(MENU_Data.hlcd, 4);
	LCD_Write(MENU_Data.hlcd, "%02d%%  ", (uint8_t)hdht.huminity);
	LCD_Send_Data(MENU_Data.hlcd, BATTERY_LEVEL_Data.battery_level / 30 + 4);
	LCD_Write(MENU_Data.hlcd, "%02d%%  ", BATTERY_LEVEL_Data.battery_level);


	if(MAIN_MENU_Data.time_format == FORMAT_24_HOURS){
		MAIN_MENU_Display_Num(REALTIME_Data.system_hour / 10, 2, 2);
		MAIN_MENU_Display_Num(REALTIME_Data.system_hour % 10, 6, 2);
	} else{
		MAIN_MENU_Display_Num((REALTIME_Data.system_hour - 12) / 10, 2, 2);
		MAIN_MENU_Display_Num((REALTIME_Data.system_hour - 12) % 10, 6, 2);
		LCD_Set_Cursor(MENU_Data.hlcd, 18, 3);
		LCD_Write(MENU_Data.hlcd, "%s", (REALTIME_Data.system_hour > 12) ? "PM" : "AM");
	}

	if(MENU_Data.blink_state){
		LCD_Set_Cursor(MENU_Data.hlcd, 9, 2);
		LCD_Send_Data(MENU_Data.hlcd, '.');
		LCD_Set_Cursor(MENU_Data.hlcd, 9, 3);
		LCD_Send_Data(MENU_Data.hlcd, '.');
	} else{
		LCD_Set_Cursor(MENU_Data.hlcd, 9, 2);
		LCD_Send_Data(MENU_Data.hlcd, ' ');
		LCD_Set_Cursor(MENU_Data.hlcd, 9, 3);
		LCD_Send_Data(MENU_Data.hlcd, ' ');
	}

	MAIN_MENU_Display_Num(REALTIME_Data.system_minute / 10, 10, 2);
	MAIN_MENU_Display_Num(REALTIME_Data.system_minute % 10, 14, 2);
}

void MAIN_MENU_Set_State(){
	MENU_Data.menu_type = MAIN_MENU;
	MENU_Data.changed = 0;
	MENU_Data.is_changing_menu = 1;
}

void MAIN_MENU_Update_Value(){
	MENU_Data.menu_type = MAIN_MENU;
	MENU_Data.changed = 0;
}
