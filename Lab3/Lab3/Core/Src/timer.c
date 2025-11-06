/*
 * timer.c
 *
 *  Created on: Oct 2, 2025
 *      Author: Vinh Le
 */


#include "main.h"
#include "input_reading.h"

#define TIMER_INTERRUPT_DURATION_MS 10

int timer_counter[3] = {TIMER_INTERRUPT_DURATION_MS, 0, 0};
int timer_flag[3] = {0, 0, 0};



void setTimer(int index, int duration) {
    timer_counter[index] = duration / TIMER_INTERRUPT_DURATION_MS;
    timer_flag[index] = 0;
}

int check_flag(int index){
	if(timer_flag[index] == 1) return 1;
	else return 0;
}

void timer_run(){
	for(uint8_t i = 0 ; i < 3 ; ++i){
		if(timer_counter[i] > 0){
			timer_counter[i]--;
			if(timer_counter[i] == 0) timer_flag[i] = 1;
		}
	}
}

 void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
 {
	 timer_run();
	 button_reading();
 }
