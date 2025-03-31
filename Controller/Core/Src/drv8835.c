/*
 * drv8835.c
 *
 *  Created on: Nov 6, 2024
 *      Author: Marcin Krawiec
 *      Plik konfiguracyjny drivera PWM do dwoch silnikow DC 5V.
 *      Inicjalizacja i funkcje sterujace
 */

#include "drv8835.h"
#include "tim.h"      // Aby użyć konfiguracji PWM i zmiennej `htim2` i 'htim3'
#include "gpio.h"     // Aby użyć portów i pinów GPIO
#include <stdint.h>   // Dołączenie nagłówka dla `uint8_t`

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

//---------------------------------------------------------------------------------
void drv8835_mode_control(DRV8835_Mode mode)					//Funkcja wyboru trybow pracy drivera,
{																//korzystamy z Phase_Enable_Mode
	if(mode == Phase_Enable_Mode)
		HAL_GPIO_WritePin(MODE_GPIO_Port, MODE_Pin, SET);
	else if(mode == In_In_Mode)
		HAL_GPIO_WritePin(MODE_GPIO_Port, MODE_Pin, RESET);
}
//---------------------------------------------------------------------------------

void drv8835_set_motorA_direction(DRV8835_DirectionA dir)		//Funkcja wybor kierunku obrotu prawego silnika
{
	if(dir == CCWA)
		HAL_GPIO_WritePin(APHASE_GPIO_Port, APHASE_Pin, SET);
	else if(dir == CWA)
		HAL_GPIO_WritePin(APHASE_GPIO_Port, APHASE_Pin, RESET);
}
//---------------------------------------------------------------------------------
void drv8835_set_motorB_direction(DRV8835_DirectionB dir)		//Funkcja wybor kierunku obrotu lewego silnika
{
	if(dir == CCWB)
		HAL_GPIO_WritePin(BPHASE_GPIO_Port, BPHASE_Pin, SET);
	else if(dir == CWB)
		HAL_GPIO_WritePin(BPHASE_GPIO_Port, BPHASE_Pin, RESET);
}
//---------------------------------------------------------------------------------
void drv8835_set_motorA_speed(uint16_t speedA)					//Ustawianie predkosci prawego silnika
{																//PWM max 1000, ustawienie wybranego wypelnienia
	TIM2->CCR2 = speedA;
}
//---------------------------------------------------------------------------------
void drv8835_set_motorB_speed(uint16_t speedB)					//Ustawianie predkosci lewego silnika
{																//PWM max 1000, ustawienie wybranego wypelnienia

	TIM3->CCR1 = speedB;
}
//---------------------------------------------------------------------------------
void drv8835_init()												//Inicjalizacja drivera: tryb phase/enable, obrot zgodnie z ruchem
{																//wskazowek zegara, poczatkowa predkosc 0
	drv8835_mode_control(Phase_Enable_Mode);
	drv8835_set_motorA_direction(CWA);
	drv8835_set_motorB_direction(CWB);
	drv8835_set_motorA_speed(0);
	drv8835_set_motorB_speed(0);
}
//---------------------------------------------------------------------------------
uint16_t drv8835_limit_motor_speed(int16_t speed)				// Funkcja ograniczajaca maks prędkośc silnika do maks wypelnienia PWM
{
    if (speed > 1000) return 1000; // Maksymalna wartość PWM
    if (speed < 0) return 0;       // Minimalna wartość PWM
    return (uint16_t)speed;
}
