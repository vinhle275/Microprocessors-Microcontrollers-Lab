/*
 * uart_communiation_fsm.c
 *
 *  Created on: Nov 25, 2025
 *      Author: Vinh Le
 */


#include "global.h"
#include "main.h"
#include "scheduler.h"
#include "uart_communiation_fsm.h"

long unsigned int saved_ADC_value = 0;

void uart_communication_fsm() {
  switch (uart_communication_state) {
    case WAIT_RST:
      if (command_flag == CMD_RST) {
        command_flag = 0;
        uart_communication_state = READ_AND_SEND;
      }
      break;

    case READ_AND_SEND:
      saved_ADC_value = HAL_ADC_GetValue(&hadc1);

      sprintf(str_transmit, "\r\n!ADC=%lu#", saved_ADC_value);
      HAL_UART_Transmit(&huart2, (uint8_t*)str_transmit, strlen(str_transmit), 1000);

      SCH_Add_Task(send_again, 3000, 3000);
      uart_communication_state = WAIT_OK;
      break;

    case WAIT_OK:
      if (command_flag == CMD_OK) {
        command_flag = 0;
        int ID = SCH_Get_TaskID(send_again);
        SCH_Delete_Task(ID);
        uart_communication_state = WAIT_RST;
      }
      break;

    default:
    	uart_communication_state = WAIT_RST;
      break;
  }
}

void send_again(){
	HAL_UART_Transmit(&huart2, (uint8_t*)str_transmit, strlen(str_transmit), 1000);
}
