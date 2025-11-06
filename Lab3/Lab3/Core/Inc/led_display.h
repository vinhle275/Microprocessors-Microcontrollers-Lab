/*
 * led_display.h
 *
 *  Created on: Oct 5, 2025
 *      Author: Vinh Le
 */

#ifndef INC_LED_DISPLAY_H_
#define INC_LED_DISPLAY_H_

#include "main.h"

void set_rgy1(uint8_t n);
void set_rgy2(uint8_t n);

void toggle_rgy(uint8_t n);

void display7SEG(int num);
void update7SEG(int index);
void updateLEDBuffer1(int num);
void updateLEDBuffer2(int num);

#endif /* INC_LED_DISPLAY_H_ */
