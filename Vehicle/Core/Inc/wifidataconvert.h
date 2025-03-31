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

#ifndef INC_WIFIDATACONVERT_H_
#define INC_WIFIDATACONVERT_H_

#include <stdio.h>
#include <string.h>

//extern ADC_HandleTypeDef hadc1;	  // Obsługa ADC dla joysticka
extern TIM_HandleTypeDef htim2;

#define ADC_MAX 4096       		 // Maksymalna wartość ADC (12-bitowa rozdzielczość)
#define SCALE_FACTOR 4.095   	 // Skalowanie ADC do zakresu 0-1000
#define BUFFER_SIZE 5			 // Liczba próbek w buforze

typedef struct wifidataconv{

	uint16_t posX;
	uint16_t posY;


}Wifidataconv;




//extern Wifidataconv wifidataconv;

void convertwifidata(Wifidataconv *wifidataconv);
void joystick_run(Wifidataconv *wifidataconv);
void joystick_printconv(Wifidataconv *wifidataconv);
void joystick_conv(Wifidataconv *wifidataconv);

#endif /* INC_WIFIDATACONVERT_H_ */
