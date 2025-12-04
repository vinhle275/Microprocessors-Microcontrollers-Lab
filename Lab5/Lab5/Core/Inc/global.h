/*
 * global.h
 *
 *  Created on: Nov 25, 2025
 *      Author: Vinh Le
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdio.h"
#include "string.h"

#define MAX_BUFFER_SIZE 30
#define CMD_RST 1
#define CMD_OK  2


typedef enum{
	WAIT,
	START,

	STATE_O,
	STATE_OK,
	END_OK,

	STATE_R,
	STATE_RS,
	STATE_RST,
	END_RST,

	STATE_IGNORE,
	END_IGNORE
}CommandParserState;

typedef enum{
	WAIT_RST,
	READ_AND_SEND,
	WAIT_OK,
}UartCommunicationState;

extern CommandParserState command_parser_state;
extern UartCommunicationState uart_communication_state;

extern int temp;
extern int buffer[MAX_BUFFER_SIZE];
extern int index_buffer;
extern int buffer_flag;
extern int command_flag;



//
//
//
//
//// Trạng thái phân tích lệnh (Command Parser)
//uint8_t command_flag = 0; // 1: RST, 2: OK

//
//// Biến cho giao tiếp UART
//uint32_t ADC_value = 0;
char str_transmit[50]; // Buffer để gửi dữ liệu đi
//
//// Khai báo các biến Timer cho FSM
//uint32_t current_timer = 0;
//
//// Handles (được CubeMX sinh ra)
extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart2;

#endif /* INC_GLOBAL_H_ */
