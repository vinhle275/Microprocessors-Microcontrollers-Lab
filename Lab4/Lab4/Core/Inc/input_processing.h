/*
 * input_processing.h
 *
 *  Created on: Oct 2, 2025
 *      Author: Vinh Le
 */

#ifndef INC_INPUT_PROCESSING_H_
#define INC_INPUT_PROCESSING_H_


void setup_newstate();

void immediately_press_handler(int idx);
void immediately_1s_press(int idx);
void continuously_press_handler(int idx);

void button_processing(void);

#endif /* INC_INPUT_PROCESSING_H_ */
