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
#define INIT 0
#define RED 1
#define GREEN 2
#define YELLOW 3

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
void red_1_led(uint8_t n);
void yellow_1_led(uint8_t n);
void green_1_led(uint8_t n);
void red_2_led(uint8_t n);
void yellow_2_led(uint8_t n);
void green_2_led(uint8_t n);
void a_led(uint8_t n);
void b_led(uint8_t n);
void c_led(uint8_t n);
void d_led(uint8_t n);
void e_led(uint8_t n);
void f_led(uint8_t n);
void g_led(uint8_t n);

void display7SEG(int num);
void rgy_control(
    uint8_t colour,
	uint8_t* pstate,
	uint16_t* pcount,
    void (*red_led)(uint8_t),
    void (*yellow_led)(uint8_t),
    void (*green_led)(uint8_t),
	void (*dis7SEG)(int num)
);


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
  uint8_t state[2] = {INIT, INIT};
  uint16_t count[2] = {100, 100};

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  rgy_control(RED, &state[0], &count[0], red_1_led, yellow_1_led, green_1_led, display7SEG);
	  rgy_control(GREEN, &state[1], &count[1], red_2_led, yellow_2_led, green_2_led, NULL);

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
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, RED_1_LED_Pin|YELLOW_1_LED_Pin|GREEN_1_LED_Pin|RED_2_LED_Pin
                          |YELLOW_2_LED_Pin|GREEN_2_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, A_LED_Pin|B_LED_Pin|C_LED_Pin|D_LED_Pin
                          |E_LED_Pin|F_LED_Pin|G_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : RED_1_LED_Pin YELLOW_1_LED_Pin GREEN_1_LED_Pin RED_2_LED_Pin
                           YELLOW_2_LED_Pin GREEN_2_LED_Pin */
  GPIO_InitStruct.Pin = RED_1_LED_Pin|YELLOW_1_LED_Pin|GREEN_1_LED_Pin|RED_2_LED_Pin
                          |YELLOW_2_LED_Pin|GREEN_2_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : A_LED_Pin B_LED_Pin C_LED_Pin D_LED_Pin
                           E_LED_Pin F_LED_Pin G_LED_Pin */
  GPIO_InitStruct.Pin = A_LED_Pin|B_LED_Pin|C_LED_Pin|D_LED_Pin
                          |E_LED_Pin|F_LED_Pin|G_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void red_1_led(uint8_t n) {
	HAL_GPIO_WritePin(RED_1_LED_GPIO_Port, RED_1_LED_Pin, n);
}
void yellow_1_led(uint8_t n) {
	HAL_GPIO_WritePin(YELLOW_1_LED_GPIO_Port, YELLOW_1_LED_Pin, n);
}
void green_1_led(uint8_t n) {
	HAL_GPIO_WritePin(GREEN_1_LED_GPIO_Port, GREEN_1_LED_Pin, n);
}
void red_2_led(uint8_t n) {
	HAL_GPIO_WritePin(RED_2_LED_GPIO_Port, RED_2_LED_Pin, n);
}
void yellow_2_led(uint8_t n) {
	HAL_GPIO_WritePin(YELLOW_2_LED_GPIO_Port, YELLOW_2_LED_Pin, n);
}
void green_2_led(uint8_t n) {
	HAL_GPIO_WritePin(GREEN_2_LED_GPIO_Port, GREEN_2_LED_Pin, n);
}
void a_led(uint8_t n){
	HAL_GPIO_WritePin(A_LED_GPIO_Port, A_LED_Pin, n);
}
void b_led(uint8_t n){
	HAL_GPIO_WritePin(B_LED_GPIO_Port, B_LED_Pin, n);
}
void c_led(uint8_t n){
	HAL_GPIO_WritePin(C_LED_GPIO_Port, C_LED_Pin, n);
}
void d_led(uint8_t n){
	HAL_GPIO_WritePin(D_LED_GPIO_Port, D_LED_Pin, n);
}
void e_led(uint8_t n){
	HAL_GPIO_WritePin(E_LED_GPIO_Port, E_LED_Pin, n);
}
void f_led(uint8_t n){
	HAL_GPIO_WritePin(F_LED_GPIO_Port, F_LED_Pin, n);
}
void g_led(uint8_t n){
	HAL_GPIO_WritePin(G_LED_GPIO_Port, G_LED_Pin, n);
}

void display7SEG(int num){

	switch(num % 10){
	case 0:
		a_led(ON);
		b_led(ON);
		c_led(ON);
		d_led(ON);
		e_led(ON);
		f_led(ON);
		g_led(OFF);
		break;
	case 1:
		a_led(OFF);
		b_led(ON);
		c_led(ON);
		d_led(OFF);
		e_led(OFF);
		f_led(OFF);
		g_led(OFF);
		break;
	case 2:
		a_led(ON);
		b_led(ON);
		c_led(OFF);
		d_led(ON);
		e_led(ON);
		f_led(OFF);
		g_led(ON);
		break;
	case 3:
		a_led(ON);
		b_led(ON);
		c_led(ON);
		d_led(ON);
		e_led(OFF);
		f_led(OFF);
		g_led(ON);
		break;
	case 4:
		a_led(OFF);
		b_led(ON);
		c_led(ON);
		d_led(OFF);
		e_led(OFF);
		f_led(ON);
		g_led(ON);
		break;
	case 5:
		a_led(ON);
		b_led(OFF);
		c_led(ON);
		d_led(ON);
		e_led(OFF);
		f_led(ON);
		g_led(ON);
		break;
	case 6:
		a_led(ON);
		b_led(OFF);
		c_led(ON);
		d_led(ON);
		e_led(ON);
		f_led(ON);
		g_led(ON);
		break;
	case 7:
		a_led(ON);
		b_led(ON);
		c_led(ON);
		d_led(OFF);
		e_led(OFF);
		f_led(OFF);
		g_led(OFF);
		break;
	case 8:
		a_led(ON);
		b_led(ON);
		c_led(ON);
		d_led(ON);
		e_led(ON);
		f_led(ON);
		g_led(ON);
		break;
	case 9:
		a_led(ON);
		b_led(ON);
		c_led(ON);
		d_led(ON);
		e_led(OFF);
		f_led(ON);
		g_led(ON);
		break;
	default:
		break;

	}
}
void rgy_control(
    uint8_t colour,
	uint8_t* pstate,
	uint16_t* pcount,
    void (*red_led)(uint8_t),
    void (*yellow_led)(uint8_t),
    void (*green_led)(uint8_t),
	void (*dis7SEG)(int num)
){

	if(dis7SEG){
		if(*pstate == INIT) dis7SEG(8);
		else dis7SEG(*pcount / 100);
	}
	switch(*pstate){
	case INIT:
		red_led(ON);
		green_led(ON);
		yellow_led(ON);

		if(*pcount == 0){
		  *pstate = colour;
		  switch(colour){
		  case RED:
			  *pcount = 500;
			  break;
		  case GREEN:
			  *pcount = 300;
			  break;
		  case YELLOW:
			  *pcount = 200;
			  break;
		  }
		}
		break;
	case RED:
		red_led(ON);
		green_led(OFF);
		yellow_led(OFF);

		if(*pcount == 0){
		  *pstate = GREEN;
		  *pcount = 300;
		}
		break;
	case GREEN:
		red_led(OFF);
		green_led(ON);
		yellow_led(OFF);

		if(*pcount == 0){
		  *pstate = YELLOW;
		  *pcount = 200;
		}
		break;
	case YELLOW:
		red_led(OFF);
		green_led(OFF);
		yellow_led(ON);

		if(*pcount == 0){
		  *pstate = RED;
		  *pcount = 500;
		}
		break;

	}
	--*pcount;

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
