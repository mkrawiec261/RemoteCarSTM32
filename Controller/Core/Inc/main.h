/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "hc_sr_04.h"
#include "joystickinit.h"
#include "drv8835.h"
#include "wifidataconvert.h"
#include "dataread.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

typedef struct {
    struct {
    	uint16_t forward_backward; // Oryginalne dane osi Y (0–1000)
    	uint16_t left_right;       // Oryginalne dane osi X (0–1000)
        int16_t normalized_x;  // Normalizowane dane os X (-500 do 500)
        int16_t normalized_y;  // Normalizowane dane os Y (-500 do 500)
        int16_t base_speed;
        int16_t turn_adjust;

        uint16_t speedA;    // Prędkość silnika A (0–1000)
        uint16_t speedB;    // Prędkość silnika B (0–1000)
  //    uint8_t directionA; // Kierunek silnika A (CW lub CCW)
  //    uint8_t directionB; // Kierunek silnika B (CW lub CCW)
    } motors;

} RobotState;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define ECHO_Pin GPIO_PIN_0
#define ECHO_GPIO_Port GPIOC
#define LED_Warning_Pin GPIO_PIN_3
#define LED_Warning_GPIO_Port GPIOC
#define LED2_Pin GPIO_PIN_5
#define LED2_GPIO_Port GPIOA
#define TRIG_Pin GPIO_PIN_11
#define TRIG_GPIO_Port GPIOB
#define TRIGC8_Pin GPIO_PIN_8
#define TRIGC8_GPIO_Port GPIOC
#define MODE_Pin GPIO_PIN_8
#define MODE_GPIO_Port GPIOA
#define APHASE_Pin GPIO_PIN_9
#define APHASE_GPIO_Port GPIOA
#define BPHASE_Pin GPIO_PIN_10
#define BPHASE_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
