/* USER CODE BEGIN Header */
/**
  ****************************************************************************
  * @file           : dataread.c
  * @brief          : Funkcje do odebrania danych z uart
  ****************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  * *
  ****************************************************************************
   * @author         : [Tymoteusz Krasnowski]
   * @date           : [08.12.2024]
   * @version        : [1.0]
   * @description    : Funkcje
  */
/* USER CODE END Header */
#include "stm32f3xx_hal.h"
#include "dataread.h"


void readwifidata(Dataread *dataread){
	//HAL_UART_Receive_DMA(&huart4, dataread->rxbuffer, 5);
	HAL_UART_Receive_DMA(&huart4, dataread->rxbuffer, 6);

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if (huart->Instance == UART4) { // Sprawdzamy, czy to UART4
		        HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin); //powinna w 411 sie nazywac tak samo jak w 303
		    }
		}
