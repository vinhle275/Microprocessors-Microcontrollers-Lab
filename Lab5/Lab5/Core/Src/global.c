/*
 * global.c
 *
 *  Created on: Nov 25, 2025
 *      Author: Vinh Le
 */

#include "global.h"

CommandParserState command_parser_state = WAIT;
UartCommunicationState uart_communication_state = WAIT_RST;

int temp = 0;
int buffer[MAX_BUFFER_SIZE];
int index_buffer = 0;
int buffer_flag = 0;
int command_flag = 0;
