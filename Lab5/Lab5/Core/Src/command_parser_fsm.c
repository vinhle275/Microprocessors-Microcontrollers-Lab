/*
 * command_parser_fsm.c
 *
 *  Created on: Nov 25, 2025
 *      Author: Vinh Le
 */
#include "global.h"

void command_parser_fsm() {
	if(buffer_flag != 1) return;
	buffer_flag = 0;
  int curr_idx = (index_buffer == 0) ? MAX_BUFFER_SIZE - 1 : index_buffer - 1;
  int data = buffer[curr_idx];


  switch (command_parser_state) {
    case WAIT:
      if (data == '!') command_parser_state = START;
      break;
    case START:
      if (data == 'R') command_parser_state = STATE_R;
      else if (data == 'O') command_parser_state = STATE_O;
      else command_parser_state = STATE_IGNORE;
      break;

    // --- RST ---
    case STATE_R:
      if (data == 'S') command_parser_state = STATE_RS;
      else command_parser_state = STATE_IGNORE;
      break;
    case STATE_RS:
      if (data == 'T') command_parser_state = STATE_RST;
      else command_parser_state = STATE_IGNORE;
      break;
    case STATE_RST:
      if (data == '#'){
    	  command_flag = CMD_RST;
    	  command_parser_state = WAIT;
      }
      else command_parser_state = STATE_IGNORE;
      break;

    // --- OK ---
    case STATE_O:
      if (data == 'K') command_parser_state = STATE_OK;
      else command_parser_state = STATE_IGNORE;
      break;
    case STATE_OK:
      if (data == '#') {
        command_flag = CMD_OK;
        command_parser_state = WAIT;
      } else command_parser_state = STATE_IGNORE;
      break;
      // --- IGNORE ---
    case STATE_IGNORE:
      if (data == '#') {
        command_parser_state = WAIT;
      }
      break;

    default:
    	command_parser_state = WAIT;
      break;
  }
}
