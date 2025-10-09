/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define ON 0
#define OFF 1
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
void led_0(uint8_t n);
void led_1(uint8_t n);
void led_2(uint8_t n);
void led_3(uint8_t n);
void led_4(uint8_t n);
void led_5(uint8_t n);
void led_6(uint8_t n);
void led_7(uint8_t n);
void led_8(uint8_t n);
void led_9(uint8_t n);
void led_10(uint8_t n);
void led_11(uint8_t n);

void clearAllClock();
void setNumberOnClock(int num);
void clearNumberOnClock(int num);
void display_clock(uint16_t* pcount);
void init_state();

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  uint16_t count[1] = {100};
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  init_state();
	  display_clock(&count[0]);
	  HAL_Delay(10);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_0_Pin|LED_1_Pin|LED_2_Pin|LED_3_Pin
                          |LED_4_Pin|LED_5_Pin|LED_6_Pin|LED_7_Pin
                          |LED_8_Pin|LED_9_Pin|LED_10_Pin|LED_11_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_0_Pin LED_1_Pin LED_2_Pin LED_3_Pin
                           LED_4_Pin LED_5_Pin LED_6_Pin LED_7_Pin
                           LED_8_Pin LED_9_Pin LED_10_Pin LED_11_Pin */
  GPIO_InitStruct.Pin = LED_0_Pin|LED_1_Pin|LED_2_Pin|LED_3_Pin
                          |LED_4_Pin|LED_5_Pin|LED_6_Pin|LED_7_Pin
                          |LED_8_Pin|LED_9_Pin|LED_10_Pin|LED_11_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void led_0(uint8_t n){
	HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, n);
}
void led_1(uint8_t n){
	HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, n);
}
void led_2(uint8_t n){
	HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, n);
}
void led_3(uint8_t n){
	HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, n);
}
void led_4(uint8_t n){
	HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, n);
}
void led_5(uint8_t n){
	HAL_GPIO_WritePin(LED_5_GPIO_Port, LED_5_Pin, n);
}
void led_6(uint8_t n){
	HAL_GPIO_WritePin(LED_6_GPIO_Port, LED_6_Pin, n);
}
void led_7(uint8_t n){
	HAL_GPIO_WritePin(LED_7_GPIO_Port, LED_7_Pin, n);
}
void led_8(uint8_t n){
	HAL_GPIO_WritePin(LED_8_GPIO_Port, LED_8_Pin, n);
}
void led_9(uint8_t n){
	HAL_GPIO_WritePin(LED_9_GPIO_Port, LED_9_Pin, n);
}
void led_10(uint8_t n){
	HAL_GPIO_WritePin(LED_10_GPIO_Port, LED_10_Pin, n);
}
void led_11(uint8_t n){
	HAL_GPIO_WritePin(LED_11_GPIO_Port, LED_11_Pin, n);
}

void clearAllClock (){
	led_0(OFF);
	led_1(OFF);
	led_2(OFF);
	led_3(OFF);
	led_4(OFF);
	led_5(OFF);
	led_6(OFF);
	led_7(OFF);
	led_8(OFF);
	led_9(OFF);
	led_10(OFF);
	led_11(OFF);
}
void setNumberOnClock(int num){
	switch(num){
	case 0:
		led_0(ON);
		break;
	case 1:
		led_1(ON);
		break;
	case 2:
		led_2(ON);
		break;
	case 3:
		led_3(ON);
		break;
	case 4:
		led_4(ON);
		break;
	case 5:
		led_5(ON);
		break;
	case 6:
		led_6(ON);
		break;
	case 7:
		led_7(ON);
		break;
	case 8:
		led_8(ON);
		break;
	case 9:
		led_9(ON);
		break;
	case 10:
		led_10(ON);
		break;
	case 11:
		led_11(ON);
		break;
	}


}
void clearNumberOnClock(int num){
	switch(num){
	case 0:
		led_0(OFF);
		break;
	case 1:
		led_1(OFF);
		break;
	case 2:
		led_2(OFF);
		break;
	case 3:
		led_3(OFF);
		break;
	case 4:
		led_4(OFF);
		break;
	case 5:
		led_5(OFF);
		break;
	case 6:
		led_6(OFF);
		break;
	case 7:
		led_7(OFF);
		break;
	case 8:
		led_8(OFF);
		break;
	case 9:
		led_9(OFF);
		break;
	case 10:
		led_10(OFF);
		break;
	case 11:
		led_11(OFF);
		break;
	}


}

void display_clock(uint16_t* pcount){
	static int sec = 0, min = 50, hour = 7;


	if(*pcount == 0){
		clearAllClock();
		setNumberOnClock(sec/5);
		setNumberOnClock(min/5);
		setNumberOnClock(hour);

		*pcount = 2;
		++sec;
	}
	if(sec == 60){
		sec = 0;
		++min;
	}
	if(min == 60){
		min = 0;
		++hour;
	}
	if(hour == 12) hour = 0;

	--*pcount;


}

void init_state(){
	static uint8_t init = 0;
	if(init == 0){
		++init;
		led_0(ON);
		led_1(ON);
		led_2(ON);
		led_3(ON);
		led_4(ON);
		led_5(ON);
		led_6(ON);
		led_7(ON);
		led_8(ON);
		led_9(ON);
		led_10(ON);
		led_11(ON);
	}
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
