/*
 * fsm_automatic.c
 *
 *  Created on: Oct 31, 2025
 *      Author: Vinh Le
 */
#include "global.h"
#include "fsm_automatic.h"
#include "timer.h"
#include "led_display.h"


void fsm_automatic(void){
	if(check_flag(1) && state == NORMAL){
	    updateLEDBuffer1(counter_rgy1--);
	    updateLEDBuffer2(counter_rgy2--);

		switch(traffic_state){
		case RED1_GREEN2:
            set_rgy1(0b011);
            set_rgy2(0b101);
            if(counter_rgy2 == 0){
				counter_rgy2 = time_amber;
				traffic_state = RED1_AMBER2;
			}
			break;

		case RED1_AMBER2:
			set_rgy1(0b011);
            set_rgy2(0b110);
            if(counter_rgy2 == 0){
				counter_rgy1 = time_green;
				counter_rgy2 = time_red;
				traffic_state = GREEN1_RED2;
			}
			break;

		case GREEN1_RED2:
			set_rgy1(0b101);
			set_rgy2(0b011);
			if(counter_rgy1 == 0){
				counter_rgy1 = time_amber;
				traffic_state = AMBER1_RED2;
			}
			break;

		case AMBER1_RED2:
			set_rgy1(0b110);
			set_rgy2(0b011);
			if(counter_rgy1 == 0){
				counter_rgy1 = time_red;
				counter_rgy2 = time_green;
				traffic_state = RED1_GREEN2;
			}
			break;

		default:
			break;
		}

	    setTimer(1, 1000);
	}
}
