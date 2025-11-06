/*
 * fsm_config.c
 *
 *  Created on: Oct 31, 2025
 *      Author: Vinh Le
 */
#include "global.h"
#include "fsm_config.h"
#include "timer.h"
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
	    if(check_flag(1)){
	    	++new_time;
	    	if(new_time > 99)  new_time = 1;
	    	config_state = WAITING;
	    	setTimer(1, 100);
	    }
		break;

	case ACCEPT:
	    if(check_flag(2)){
	    	config_state = WAITING;
	    	return;
	    }
		break;

	default:
		break;
	}


}

