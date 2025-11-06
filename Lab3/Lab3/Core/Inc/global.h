/*
 * global.h
 *
 *  Created on: Oct 31, 2025
 *      Author: Vinh Le
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#define INIT 0
#define NORMAL 1
#define SET_RED 2
#define SET_AMBER 3
#define SET_GREEN 4
#define ERROR_G 5
#define ERROR_RY 6

#define RED1_GREEN2 7
#define RED1_AMBER2 8
#define GREEN1_RED2 9
#define AMBER1_RED2 10

#define WAITING 11
#define SINGLE_INCREMENT 12
#define CONTINUOUS_INCREMENT 13
#define ACCEPT 14

extern int state;
extern int traffic_state;
extern int config_state;

extern int led_idx;

extern int new_time;
extern int new_red;
extern int new_green;
extern int new_amber;
extern int time_red;
extern int time_amber;
extern int time_green;

extern int counter_rgy1;
extern int counter_rgy2;


#endif /* INC_GLOBAL_H_ */
