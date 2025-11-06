/*
 * fsm_manual.h
 *
 *  Created on: Oct 31, 2025
 *      Author: Vinh Le
 */

#ifndef INC_FSM_MANUAL_H_
#define INC_FSM_MANUAL_H_


void init_handler();
void red_handler();
void amber_handler();
void green_handler();
void errorG_handler();
void errorRY_handler();

void fsm_manual(void);

#endif /* INC_FSM_MANUAL_H_ */
