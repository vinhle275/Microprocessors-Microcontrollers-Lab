/*
 * global.c
 *
 *  Created on: Oct 31, 2025
 *      Author: Vinh Le
 */
#include "global.h"

int state = INIT;
int traffic_state = RED1_GREEN2;
int config_state = WAITING;

int led_idx = 0;

int new_time = 1;
int new_red = 0;
int new_green = 0;
int new_amber = 0;
int time_red = 5;
int time_amber = 2;
int time_green = 3;

int counter_rgy1 = 0;
int counter_rgy2 = 0;
