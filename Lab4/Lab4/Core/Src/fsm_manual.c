/*
 * fsm_manual.c
 *
 *  Created on: Oct 31, 2025
 *      Author: Vinh Le
 */
#include "global.h"
#include "fsm_manual.h"
#include "led_display.h"

void fsm_manual(void){
    switch(state){
    case INIT:
    	init_handler();
    	break;

    case NORMAL:
    	break;

    case SET_RED:
    	red_handler();
    	break;

    case SET_AMBER:
    	amber_handler();
    	break;

    case SET_GREEN:
    	green_handler();
    	break;

    case ERROR_G:
    	errorG_handler();
    	break;

    case ERROR_RY:
    	errorRY_handler();
    	break;

    default:
    	break;
    }

    if(state != INIT){
        if(led_idx == 4) led_idx = 0;
        update7SEG(led_idx++);
    }
}

void init_handler(){
	set_rgy1( 0b000 );
	set_rgy2( 0b000 );

	update7SEG(-1);
}

//void normal_handler(){
//    updateLEDBuffer1(counter_rgy1--);
//    updateLEDBuffer2(counter_rgy2--);
//}

void red_handler(){
	if(config_state == ACCEPT)
		updateLEDBuffer2(-1);
	else
		updateLEDBuffer2(new_time);

	toggle_rgy(0b011);
}

void amber_handler(){
	if(config_state == ACCEPT)
		updateLEDBuffer2(-1);
	else
		updateLEDBuffer2(new_time);

	toggle_rgy(0b110);
}

void green_handler(){
	if(config_state == ACCEPT)
		updateLEDBuffer2(-1);
	else
		updateLEDBuffer2(new_time);

	toggle_rgy(0b101);
}


void errorG_handler(){
	toggle_rgy(0b101);
}

void errorRY_handler(){
	toggle_rgy(0b010);
}
