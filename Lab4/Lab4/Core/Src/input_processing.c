/*
 * input_processing.c
 *
 *  Created on: Oct 2, 2025
 *      Author: Vinh Le
 */


#include <led_display.h>
#include "scheduler.h"
#include "main.h"
#include "input_reading.h"
#include "global.h"
#include "input_processing.h"
#include "fsm_config.h"

enum ButtonState {BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_PRESSED_MORE_THAN_1_SECOND};
enum ButtonState buttonState[3] = {BUTTON_RELEASED, BUTTON_RELEASED, BUTTON_RELEASED};

void button_processing(void){
	for (int i = 0; i < 3; ++i) {
		switch(buttonState[i]){
			case BUTTON_RELEASED:
				if(is_button_pressed(i)){
					buttonState[i] = BUTTON_PRESSED;
					immediately_press_handler(i);
				}
				break;

			case BUTTON_PRESSED:
				if(!is_button_pressed(i)){
					buttonState[i] = BUTTON_RELEASED;
					//after_short_press
				} else {
					if(is_button_pressed_1s(i)){
						buttonState[i] = BUTTON_PRESSED_MORE_THAN_1_SECOND;
						//immediately_1s_press

						immediately_1s_press(i);
					}
				}
				break;

			case BUTTON_PRESSED_MORE_THAN_1_SECOND:
				if(!is_button_pressed(i)){
					buttonState[i] = BUTTON_RELEASED;
					// after_long_press
				}
				// liên tục kích

				continuously_press_handler(i);
				break;
		}
	}
}

void setup_newstate(){

	led_idx = 0;
	set_rgy1( 0b111 );
	set_rgy2( 0b111 );



	switch(state){
	case NORMAL:
		if(new_red && new_green && new_amber){
			time_red = new_red;
			time_green = new_green;
			time_amber = new_amber;
		}

		new_red = 0;
		new_green = 0;
		new_amber = 0;

		counter_rgy1 = time_red;
		counter_rgy2 = time_green;
		traffic_state = RED1_GREEN2;
		break;

	case SET_RED:
		config_state = WAITING;
		updateLEDBuffer1(2);
		new_time = 1;
		break;

	case SET_AMBER:
		config_state = WAITING;
		updateLEDBuffer1(3);
		new_time = 1;
		break;

	case SET_GREEN:
		config_state = WAITING;
		updateLEDBuffer1(4);
		new_time = 1;
		break;

	case ERROR_RY:
		set_rgy1( 0b110 );
		set_rgy2( 0b110 );

		updateLEDBuffer1(-2);
		updateLEDBuffer2(-3);
		break;

	case ERROR_G:
		updateLEDBuffer1(-2);
		updateLEDBuffer2(new_red - new_amber);
		return;
		break;

	default:
		break;
	}
}

void immediately_press_handler(int idx){

	switch(idx){
	case 0:
		switch(state){
		case INIT:
			state = NORMAL;
			break;

		case NORMAL:
			state = SET_RED;
			break;

		case SET_RED:
			state = SET_AMBER;
			break;

		case SET_AMBER:
			state = SET_GREEN;
			break;

		case SET_GREEN:
			state = NORMAL;
			break;

		case ERROR_G:
			state = SET_RED;
			break;

		case ERROR_RY:
			state = SET_RED;
			break;

		default:
			break;
		}
		setup_newstate();
		break;

	case 1:
		if(state == SET_RED || state == SET_GREEN || state == SET_AMBER){
			config_state = SINGLE_INCREMENT;
		}
		break;

	case 2:
		switch(state){
		case SET_RED:
			SCH_Add_Task(accept_state, 2000, 0);
			new_red = new_time;
			config_state = ACCEPT;
			break;

		case SET_AMBER:
			if(new_time < new_red || new_red == 0){
				SCH_Add_Task(accept_state, 2000, 0);
				new_amber = new_time;
				config_state = ACCEPT;
			}else{
				state = ERROR_RY;
				setup_newstate();
			}

			break;

		case SET_GREEN:
			if(new_time == new_red - new_amber || new_red == 0 || new_amber == 0){
				SCH_Add_Task(accept_state, 2000, 0);
				new_green = new_time;
				config_state = ACCEPT;
			}else{
				state = ERROR_G;
				setup_newstate();
			}

			break;

		case ERROR_G:
			new_green = new_red - new_amber;
			state = NORMAL;
			setup_newstate();
			break;

		case ERROR_RY:
			break;

		default:
			break;
		}
	}

}
void immediately_1s_press(int idx){
	if(idx != 1) return;
	SCH_Add_Task(continuous_increment_state, 100, 0);
}

void continuously_press_handler(int idx){
	if(idx != 1) return;
	config_state = CONTINUOUS_INCREMENT;
}







