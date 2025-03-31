/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
 struct us_sensor_str distance_sensor;		//inicjalizacja struktury danych czujnika odleglosci

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
extern uint32_t convertedparameter[2];		//odczyt z ADC



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
  MX_DMA_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM1_Init();
  MX_TIM8_Init();
  MX_UART4_Init();
  /* USER CODE BEGIN 2 */

  initialise_monitor_handles();
  HAL_TIM_PWM_Init(&htim2);
  HAL_TIM_PWM_Init(&htim3);

  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  HAL_UART_Init(&huart4);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  	//Dataread dataread;
  	Wifidataconv wifidataconv;

  readwifidata(&dataread);

  void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

  RobotState robot = {												//instrancja struktury danych w petli
      .motors = {0, 0, 0, 0, 0, 0, 0, 0},
  };

  //Joystick joystick; 												//instancja struktury danych joysticka
  //joystick_run(&joystick);											//start DMA joysticka

  drv8835_init();													//start drivera (tryb phase/enable, CW, speed = 0)

  hc_sr_04_init(&distance_sensor, &htim1, &htim8, TIM_CHANNEL_3);	//start czujnika

  while (1)
  {
//--------------------------------------------------------------------------------- Sterowanie silnikami
	  	  convertwifidata(&wifidataconv);

	  	  //printf("%d, %d\n", wifidataconv.posX, wifidataconv.posY);


	  	  //Konwersja danych z joysticka (0-1000 dla obu osi)
	      //joystick_conv(&wifidataconv);
	      //printf("Silnik B: %d, silnik A: %d\n", wifidataconv.posX, wifidataconv.posY);
	      HAL_Delay(150);
/*

	      robot.motors.forward_backward = wifidataconv.posY; 	// Oś Y
	      robot.motors.left_right = wifidataconv.posX;       	// Oś X


	      // Normalizacja wartości do zakresu -500 do 500 (środek = 0)
	      robot.motors.normalized_y = robot.motors.forward_backward - 500;
	      robot.motors.normalized_x = robot.motors.left_right - 500;


	      // Dodanie tolerancji dla pozycji neutralnej (martwa strefa)
	      if (abs(robot.motors.normalized_x) <= 25 && abs(robot.motors.normalized_y) <= 25) {
	          drv8835_set_motorA_speed(0);
	          drv8835_set_motorB_speed(0);
	          continue; // Przejdź do następnej iteracji
	      }

	      // Obliczanie prędkości bazowej (przód/tył) i różnicy dla skrętu
	      robot.motors.base_speed = abs( robot.motors.normalized_y) * 2; 	// Prędkość w zakresie 0–1000
	      robot.motors.turn_adjust =  robot.motors.normalized_x * 2;    	// Dostosowanie prędkości dla skrętu
	      //printf("%d, %d\n", robot.motors.base_speed, robot.motors.turn_adjust);
	      //HAL_Delay(100);


	      // Ograniczanie prędkości w zakresie 0–1000
	      if (robot.motors.base_speed > 1000) robot.motors.base_speed = 1000;
	      if (robot.motors.turn_adjust > 1000) robot.motors.turn_adjust = 1000;
	      if (robot.motors.turn_adjust < -1000) robot.motors.turn_adjust = -1000;

	      // Obliczanie prędkości dla każdego silnika
	      robot.motors.speedA = robot.motors.base_speed - robot.motors.turn_adjust; // Silnik A (lewy)
	      robot.motors.speedB = robot.motors.base_speed + robot.motors.turn_adjust; // Silnik B (prawy)

	      // Ograniczanie prędkości silników w zakresie 0–1000
	      robot.motors.speedA = drv8835_limit_motor_speed(robot.motors.speedA);
	      robot.motors.speedB = drv8835_limit_motor_speed(robot.motors.speedB);

	      // Ustawianie kierunku obrotów silników
	      if (robot.motors.normalized_y <= -20) { 	// Tył
	          drv8835_set_motorA_direction(CCWA);
	          drv8835_set_motorB_direction(CCWB);
	      } else { 										// Przód
	          drv8835_set_motorA_direction(CWA);
	          drv8835_set_motorB_direction(CWB);
	      }

	      // Ustawianie prędkości PWM dla silników
	      drv8835_set_motorA_speed(robot.motors.speedA);
	      drv8835_set_motorB_speed(robot.motors.speedB);

	      // uint8_t CWA = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9);
	      //uint8_t CWB = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10);
	      // HAL_Delay(100);
	      HAL_Delay(50);*/
//--------------------------------------------------------------------------------- Sensor odleglosci
   /* if (distance_sensor.led_state)
	  {
	  	  // Zapal diodę, gdy odległość <= 30 cm
	  	 HAL_GPIO_WritePin(LED_Warning_GPIO_Port, LED_Warning_Pin, GPIO_PIN_SET);
	  }
	  	  else
	  {
	  	  // Zgaś diodę, gdy odległość > 30 cm
	  	  HAL_GPIO_WritePin(LED_Warning_GPIO_Port, LED_Warning_Pin, GPIO_PIN_RESET);
	  }
	  //printf("Measured Distance: %lu cm\n", distance_sensor.distance_cm);
*/
//---------------------------------------------------------------------------------
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_UART4|RCC_PERIPHCLK_TIM1
                              |RCC_PERIPHCLK_TIM8|RCC_PERIPHCLK_TIM2
                              |RCC_PERIPHCLK_TIM34;
  PeriphClkInit.Uart4ClockSelection = RCC_UART4CLKSOURCE_PCLK1;
  PeriphClkInit.Tim1ClockSelection = RCC_TIM1CLK_HCLK;
  PeriphClkInit.Tim8ClockSelection = RCC_TIM8CLK_HCLK;
  PeriphClkInit.Tim2ClockSelection = RCC_TIM2CLK_HCLK;
  PeriphClkInit.Tim34ClockSelection = RCC_TIM34CLK_HCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
//------------------------------------------------------------------------------------------------------------------
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)		//callback z czujnika odleglosci gdy dystans bedzie
																//bedzie mniejszy niz 30 cm
{
	if(TIM1 == htim->Instance)
	{
		uint32_t echo_us;

		echo_us = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
		distance_sensor.distance_cm = hc_sr_04_convert_us_to_cm(echo_us);

		if (distance_sensor.distance_cm <= 30)
		{
		    distance_sensor.led_state = 1;  // Zapal diodę
		}
		else
		{
		    distance_sensor.led_state = 0;  // Zgaś diodę
		}
	}
}
//------------------------------------------------------------------------------------------------------------------

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
