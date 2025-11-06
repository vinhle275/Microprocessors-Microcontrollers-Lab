/*
 * led_display.c
 *
 *  Created on: Oct 5, 2025
 *      Author: Vinh Le
 */
#include "main.h"

int led_buffer[4] = {0, 0, 0, 0};
static const uint8_t SEG_TABLE[15] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10, 0x08, 0x46, 0x06, 0x4E, 0x48};

void set_rgy1(uint8_t n) {
    HAL_GPIO_WritePin(RED_1_LED_GPIO_Port, RED_1_LED_Pin, (n >> 2) & 1);
    HAL_GPIO_WritePin(GREEN_1_LED_GPIO_Port, GREEN_1_LED_Pin, (n >> 1) & 1);
    HAL_GPIO_WritePin(YELLOW_1_LED_GPIO_Port, YELLOW_1_LED_Pin, n & 1);
}
void set_rgy2(uint8_t n) {
    HAL_GPIO_WritePin(RED_2_LED_GPIO_Port, RED_2_LED_Pin, (n >> 2) & 1);
    HAL_GPIO_WritePin(GREEN_2_LED_GPIO_Port, GREEN_2_LED_Pin, (n >> 1) & 1);
    HAL_GPIO_WritePin(YELLOW_2_LED_GPIO_Port, YELLOW_2_LED_Pin, n & 1);
}

void toggle_rgy(uint8_t n){
	if(n == 0b111) HAL_GPIO_TogglePin ( RED_LED_GPIO_Port , RED_LED_Pin );

	if( !((n >> 2) & 1) ){
		HAL_GPIO_TogglePin ( RED_1_LED_GPIO_Port , RED_1_LED_Pin );
		HAL_GPIO_TogglePin ( RED_2_LED_GPIO_Port , RED_2_LED_Pin );
	}

	if( !((n >> 1) & 1) ){
		HAL_GPIO_TogglePin ( GREEN_1_LED_GPIO_Port , GREEN_1_LED_Pin );
		HAL_GPIO_TogglePin ( GREEN_2_LED_GPIO_Port , GREEN_2_LED_Pin );
	}

	if( !((n >> 0) & 1) ){
		HAL_GPIO_TogglePin ( YELLOW_1_LED_GPIO_Port , YELLOW_1_LED_Pin );
		HAL_GPIO_TogglePin ( YELLOW_2_LED_GPIO_Port , YELLOW_2_LED_Pin );
	}
}

void display7SEG(int num){


    uint8_t seg = SEG_TABLE[num];

    HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, (seg >> 0) & 1);
    HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, (seg >> 1) & 1);
    HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, (seg >> 2) & 1);
    HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, (seg >> 3) & 1);
    HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, (seg >> 4) & 1);
    HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, (seg >> 5) & 1);
    HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, (seg >> 6) & 1);

}
void update7SEG(int index){
	switch (index){
	case -1:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 0);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 0);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 0);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 0);
		display7SEG(8);
		break;
	case 0:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 0);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
		display7SEG(led_buffer[0]);
		break;
	case 1:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 0);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
		display7SEG(led_buffer[1]);
		break;
	case 2:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 0);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
		display7SEG(led_buffer[2]);
		break;
	case 3:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 0);
		display7SEG(led_buffer[3]);
		break;
	default:
		break;
	}
}
void updateLEDBuffer1(int num){
	if(num > -1){
		led_buffer[0] = num/10;
		led_buffer[1] = num%10;
		return;
	}
	if(num == -1){
		led_buffer[0] = 10;
		led_buffer[1] = 11;
		return;
	}
	if(num == -2){
		led_buffer[0] = 12;
		led_buffer[1] = 13;
		return;
	}
	if(num == -3){
		led_buffer[0] = 14;
		led_buffer[1] = 10;
		return;
	}
}
void updateLEDBuffer2(int num){
	if(num > -1){
		led_buffer[2] = num/10;
		led_buffer[3] = num%10;
		return;
	}

	if(num == -1){
		led_buffer[2] = 10;
		led_buffer[3] = 11;
		return;
	}
	if(num == -2){
		led_buffer[2] = 12;
		led_buffer[3] = 13;
		return;
	}
	if(num == -3){
		led_buffer[2] = 14;
		led_buffer[3] = 10;
		return;
	}

}





