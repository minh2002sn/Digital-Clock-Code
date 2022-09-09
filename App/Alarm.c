#include "Alarm.h"
#include "real_time.h"
#include "Timeline_Manage.h"

#define BUZZER_RUNNING_TIME			20000
#define BUZZER_SHORT_CYCLE		100
#define BUZZER_LONG_CYCLE		500

ALARM_DATA_t ALARM_Data;

static void __buzzer_on(){
	HAL_GPIO_WritePin(ALARM_Data.buzzer_port, ALARM_Data.buzzer_pin, 0);
}

static void __buzzer_off(){
	HAL_GPIO_WritePin(ALARM_Data.buzzer_port, ALARM_Data.buzzer_pin, 1);
}

static void __finding_next_timeline(){
	if(TIMELINE_Data.len != 0){
		for(int i = 0; i < TIMELINE_Data.len; i++){
			if(TIMELINE_Data.flash_data[i].timeline_state == TIMELINE_OFF) continue;
			uint8_t t_system_time = REALTIME_Data.system_hour * 60 + REALTIME_Data.system_minute;
			uint8_t t_alarm_time = TIMELINE_Data.flash_data[i].hour * 60 + TIMELINE_Data.flash_data[i].minute;
			if(t_system_time < t_alarm_time && ((0x01 << (REALTIME_Data.system_day - 1)) & TIMELINE_Data.flash_data[i].day) != 0){
				ALARM_Data.next_timeline_index = i;
				ALARM_Data.state = WAITING_FOR_TIMELINE;
				break;
			}
		}
	}
}

static void __waiting_for_timeline(){
	uint8_t t_system_time = REALTIME_Data.system_hour * 60 + REALTIME_Data.system_minute;
	uint8_t t_alarm_time = TIMELINE_Data.flash_data[ALARM_Data.next_timeline_index].hour * 60 + TIMELINE_Data.flash_data[ALARM_Data.next_timeline_index].minute;
	if(TIMELINE_Data.flash_data[ALARM_Data.next_timeline_index].timeline_state == TIMELINE_OFF){
		ALARM_Data.state = FINDING_NEXT_TIMELINE;
		return;
	}
	if(t_system_time == t_alarm_time){
		ALARM_Data.state = ALARM_RUNNING;
		ALARM_Data.buzzer_running_timer = HAL_GetTick();
		ALARM_Data.buzzer_cycle_timer = HAL_GetTick();
	}
}

static void __alarm_running(){
	static uint8_t buzzer_counter = 0;
	if(HAL_GetTick() - ALARM_Data.buzzer_running_timer < BUZZER_RUNNING_TIME){
		if(buzzer_counter <= 2){
			if(buzzer_counter % 2 == 0)
				__buzzer_on();
			else
				__buzzer_off();
			if(HAL_GetTick() - ALARM_Data.buzzer_cycle_timer >= BUZZER_SHORT_CYCLE){
				buzzer_counter++;
				ALARM_Data.buzzer_cycle_timer = HAL_GetTick();
			}
		}

		if(buzzer_counter == 3){
			__buzzer_off();
			if(HAL_GetTick() - ALARM_Data.buzzer_cycle_timer >= BUZZER_LONG_CYCLE){
				buzzer_counter = 0;
				ALARM_Data.buzzer_cycle_timer = HAL_GetTick();
			}
		}
	} else{
		ALARM_Data.state = FINDING_NEXT_TIMELINE;
		__buzzer_off();
	}
}

void ALARM_Init(GPIO_TypeDef *p_buzzer_port, uint16_t p_buzzer_pin){
	ALARM_Data.state = FINDING_NEXT_TIMELINE;
	ALARM_Data.buzzer_port = p_buzzer_port;
	ALARM_Data.buzzer_pin = p_buzzer_pin;
	__buzzer_off();
}

void ALARM_Handle(){
	switch(ALARM_Data.state){
		case FINDING_NEXT_TIMELINE:
			__finding_next_timeline();
			break;
		case WAITING_FOR_TIMELINE:
			__waiting_for_timeline();
			break;
		case ALARM_RUNNING:
			__alarm_running();
			break;
		default:
			break;
	}
}

void ALARM_Stop_Buzzer(){
	if(ALARM_Data.state == ALARM_RUNNING){
		ALARM_Data.state = FINDING_NEXT_TIMELINE;
	}
}

uint8_t ALARM_Is_Buzzer_Running(){
	return (ALARM_Data.state == ALARM_RUNNING) ? 1 : 0;
}

void ALARM_Recheck(){
	if(ALARM_Data.state == WAITING_FOR_TIMELINE){
		ALARM_Data.state = FINDING_NEXT_TIMELINE;
	}
}
