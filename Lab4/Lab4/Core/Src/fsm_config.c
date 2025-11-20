/*
 * fsm_config.c
 *
 *  Created on: Oct 31, 2025
 *      Author: Vinh Le
 */
#include "global.h"
#include "fsm_config.h"
#include "scheduler.h"
#include "led_display.h"



void fsm_config(void){
	if(state != SET_RED && state != SET_AMBER && state != SET_GREEN) return;

	switch(config_state){
	case WAITING:
		break;

	case SINGLE_INCREMENT:
        ++new_time;
        if(new_time > 99)  new_time = 1;
        config_state = WAITING;
		break;

	case CONTINUOUS_INCREMENT:

		break;

	case ACCEPT:

		break;

	default:
		break;
	}
}


void continuous_increment_state(){
	++new_time;
	if(new_time > 99)  new_time = 1;

	if(config_state == CONTINUOUS_INCREMENT)
		SCH_Add_Task(continuous_increment_state, 100, 0);
	config_state = WAITING;
}

void accept_state(){
	config_state = WAITING;
}

