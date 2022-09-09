#ifndef ALARM_H
#define ALARM_H

#include "main.h"
#include "stdint.h"

typedef enum{
	FINDING_NEXT_TIMELINE,
	WAITING_FOR_TIMELINE,
	ALARM_RUNNING,
} ALARM_STATE_t;

typedef struct{
	ALARM_STATE_t state;
	uint8_t next_timeline_index;
	uint32_t buzzer_running_timer;
	uint32_t buzzer_cycle_timer;
	GPIO_TypeDef *buzzer_port;
	uint16_t buzzer_pin;
} ALARM_DATA_t;

void ALARM_Init(GPIO_TypeDef *p_buzzer_port, uint16_t p_buzzer_pin);
void ALARM_Handle();
void ALARM_Stop_Buzzer();
uint8_t ALARM_Is_Buzzer_Running();
void ALARM_Recheck();

extern ALARM_DATA_t ALARM_Data;

#endif
