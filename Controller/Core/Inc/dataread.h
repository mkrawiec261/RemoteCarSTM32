/* USER CODE BEGIN Header */
/**
  ****************************************************************************
  * @file           : dataread.c
  * @brief          :  Struktura danych i ciala funkcji do odebrania danych
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
   * @description    : Struktura danych i ciala funkcji
  */
/* USER CODE END Header */

#ifndef INC_DATAREAD_H_
#define INC_DATAREAD_H_

#define LED2_Pin GPIO_PIN_5
#define LED2_GPIO_Port GPIOA

extern UART_HandleTypeDef huart4;

typedef struct Dataread{

	//uint8_t rxbuffer[5];
	uint8_t rxbuffer[6];

}Dataread;


extern Dataread dataread;
void readwifidata(Dataread *dataread);


#endif /* INC_DATAREAD_H_ */
